/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ShadowGeometry.cpp
* Create: 	12/11/2008
* Desc:		渲染阴影
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "ShadowGeometry.h"
#include "Game/GameGlobal.h"

static float g_afBlurPixelKernel[BLUR_KERNEL_SIZE] =
{
	-4.0f,
	-3.0f,
	-2.0f,
	-1.0f,
	0.0f,
	1.0f,
	2.0f,
	3.0f,
	4.0f,
};
static float g_afBlurWeights[BLUR_KERNEL_SIZE] =
{
	0.0039f,
	0.0312f,
	0.1094f,
	0.2188f,
	0.2734f,
	0.2188f,
	0.1094f,
	0.0312f,
	0.0039f
};

//---------------------------------------------------------------------------
ShadowGeometry::ShadowGeometry(unsigned int uiMaxTriangleCount) :
    m_kCastingObjects(1024), m_pkPositionStream(0), m_pkTexCoordStream(0),
    m_pkIndexStream(0), m_bForceRender(false), m_kCuller(&m_kVisible, NULL),
    m_kVisible(1024, 1024) 
{
    // the direction of the infinite light casting the shadow.  
	m_kLightDir = NiPoint3(0.66f, -0.1f, -0.9f);
	m_kLightDir.Unitize();

    // the camera used to project the shadow caster to create the shadow mask
    // this camera is a distant perspective camera with a narrow FOV, to 
    // approximate a parallel camera.
    m_spCamera = NiNew NiCamera;
    m_spCamera->SetTranslate(0.0f, 0.0f, 500.0f);

    // Need to generate an orthonormal frame, with the X axis mapping to the
    // light direction.  The other dimensions do not matter, so long as they
    // define a right-handed orthonormal frame
    NiPoint3 kYVec = -m_kLightDir.Perpendicular();
    NiPoint3 kZVec = m_kLightDir.UnitCross(kYVec);

    // Rotate the camera based on the orthonormal frame
    NiMatrix3 kRotation(m_kLightDir, kYVec, kZVec);
    m_spCamera->SetRotate(kRotation);
    m_spCamera->Update(0.0f);

    NiFrustum kFrust = m_spCamera->GetViewFrustum();
    kFrust.m_fFar  = 1000.0f;
    kFrust.m_fNear =   1.0f;
    m_spCamera->SetViewFrustum(kFrust);

    // The following (master) properties are used to batch render the shadow
    // casting objects.  These properties ensure that the shadow casters 
    // appear opaque and flat, the color of the desired shadow.  If these 
    // were not used, the shadow could contain surface colors of the casters'
    // textures, which would look incorrect.
    m_spPropertyState = NiNew NiPropertyState;

	NiVertexColorProperty* pkVC = NiNew NiVertexColorProperty;
	pkVC->SetSourceMode(NiVertexColorProperty::SOURCE_IGNORE);
	pkVC->SetLightingMode(NiVertexColorProperty::LIGHTING_E);
	m_spPropertyState->SetProperty(pkVC);

    NiMaterialProperty* pkMat = NiNew NiMaterialProperty;
    pkMat->SetEmittance(NiColor(0.6f, 0.6f, 0.6f));
    pkMat->SetAlpha(0.6f);
    m_spPropertyState->SetProperty(pkMat);

    NiTexturingProperty* pkTex = NiNew NiTexturingProperty;
    m_spPropertyState->SetProperty(pkTex);

    //NiShadeProperty* pkShade = NiNew NiShadeProperty;
    //pkShade->SetSmooth(false);
    //m_spPropertyState->SetProperty(pkShade);

	m_spFakePropertyState = NiNew NiPropertyState;
	m_spFakePropertyState->SetProperty(pkVC);
	m_spFakePropertyState->SetProperty(pkMat);

    if (uiMaxTriangleCount == 0)
        m_uiMaxTriangleCount = TRIANGLE_COUNT;
    else
        m_uiMaxTriangleCount = uiMaxTriangleCount;
    m_uiMaxVertexCount = 3 * m_uiMaxTriangleCount;

    // Create the shadow geometry - this is a dynamic mesh that will be
    // refilled each frame to include ground (recipient) triangles that fall
    // within the shadow frustum.  It must be marked as dynamic, as both the
    // geometry and the vertex/triangle counts will change each frame
    m_spShadowGeometry = NiNew NiMesh; 
    NIASSERT(m_spShadowGeometry);
    m_spShadowGeometry->SetName("ShadowGeometry");

    m_spShadowGeometry->SetPrimitiveType(NiMesh::PRIMITIVE_TRIANGLES);

    // Create & add data streams vertices, texture coordinates, indices, for 
    // the shadow geometry 
    NiDataStreamRef* pkPositionRef = m_spShadowGeometry->AddStream(
        NiCommonSemantics::POSITION(), 0, NiDataStreamElement::F_FLOAT32_3, 
        m_uiMaxVertexCount, NiDataStream::ACCESS_CPU_READ | 
        NiDataStream::ACCESS_CPU_WRITE_MUTABLE | NiDataStream::ACCESS_GPU_READ,
        NiDataStream::USAGE_VERTEX);
    NIASSERT(pkPositionRef);

    NiDataStreamRef* pkTexCoordRef = m_spShadowGeometry->AddStream(
        NiCommonSemantics::TEXCOORD(), 0, NiDataStreamElement::F_FLOAT32_2, 
        m_uiMaxVertexCount, NiDataStream::ACCESS_CPU_READ | 
        NiDataStream::ACCESS_CPU_WRITE_MUTABLE | NiDataStream::ACCESS_GPU_READ,
        NiDataStream::USAGE_VERTEX);
    NIASSERT(pkTexCoordRef);

    NiDataStreamRef* pkIndexRef = m_spShadowGeometry->AddStream(
        NiCommonSemantics::INDEX(), 0, NiDataStreamElement::F_UINT16_1, 
        m_uiMaxTriangleCount * 3, NiDataStream::ACCESS_CPU_READ | 
        NiDataStream::ACCESS_CPU_WRITE_MUTABLE | NiDataStream::ACCESS_GPU_READ,
        NiDataStream::USAGE_VERTEX_INDEX);
    NIASSERT(pkIndexRef);

    m_pkPositionStream = pkPositionRef->GetDataStream();
    m_pkTexCoordStream = pkTexCoordRef->GetDataStream();
    m_pkIndexStream = pkIndexRef->GetDataStream();
    
    m_pkPositionStream->GetRegion(0).SetRange(0);
    m_pkTexCoordStream->GetRegion(0).SetRange(0);
    m_pkIndexStream->GetRegion(0).SetRange(0);

    // The shadow is alpha blended, so it must not write the ZBuffer.
    NiZBufferProperty* pkZ = NiNew NiZBufferProperty;
    NIASSERT(pkZ);
    pkZ->SetZBufferTest(true);
    pkZ->SetZBufferWrite(false);
    m_spShadowGeometry->AttachProperty(pkZ);

    // The shadow is a darkmap, so it multiplies the framebuffer color
    NiAlphaProperty* pAlpha = NiNew NiAlphaProperty;
    pAlpha->SetAlphaBlending(true);
    pAlpha->SetSrcBlendMode(NiAlphaProperty::ALPHA_ZERO);
    pAlpha->SetDestBlendMode(NiAlphaProperty::ALPHA_SRCCOLOR);
	m_spShadowGeometry->AttachProperty(pAlpha);

	m_pkPick	= NiNew NiPick( 1, 1 );
	m_pkPick->SetQueryType(NiPick::QUERY_ALL);
	m_pkPick->SetSortType(NiPick::SORT_OFF);
	m_pkPick->SetIntersectType(NiPick::INTERSECT_TRIANGLE);

	// Assumes model coordinates have already been transformed to world
	m_pkPick->SetCoordinateType(NiPick::COORDINATES_WORLD);
	m_pkPick->SetFrontOnly(false);
	m_pkPick->SetObserveAppCullFlag(false);
	m_pkPick->SetReturnTexture(false);
	m_pkPick->SetReturnNormal(false);
	m_pkPick->SetReturnSmoothNormal(false);
	m_pkPick->SetReturnColor(false);

	m_kCenterP = NiPoint3::ZERO;
	m_fRadius = 10.f;
	m_spCaster = NULL;
	m_spFakeCaster = NULL;
}
//----------------------------------------------------------------------------
ShadowGeometry* ShadowGeometry::Create(unsigned int uiDetail, 
    unsigned int uiMaxTriangleCount)
{
    ShadowGeometry* pkThis = NiNew ShadowGeometry(uiMaxTriangleCount);
    unsigned int uiTexWidth;
    NiRenderer* pkRenderer = 0;

    // We will create a rendered texture that will be updated each frame
    pkRenderer = NiRenderer::GetRenderer();
    NIASSERT(pkRenderer);

    // We match the texture to the depth of the backbuffer for optimal
    // performance
    NiTexture::FormatPrefs kPrefs;
    const NiRenderTargetGroup* pkRTGroup = 
        NiRenderer::GetRenderer()->GetDefaultRenderTargetGroup();
    const NiPixelFormat* pkPixelFormat = pkRTGroup->GetPixelFormat(0);
    if (pkPixelFormat->GetBitsPerPixel() == 16)
        kPrefs.m_ePixelLayout = NiTexture::FormatPrefs::HIGH_COLOR_16;
    else
        kPrefs.m_ePixelLayout = NiTexture::FormatPrefs::TRUE_COLOR_32;

    uiTexWidth = 1 << uiDetail;

    NiRenderedTexture* pkRenderedTexture = NiRenderedTexture::Create( 
        uiTexWidth, uiTexWidth, pkRenderer, kPrefs);
    pkThis->m_spTexture = pkRenderedTexture;
    pkThis->m_spRenderTargetGroup = NiRenderTargetGroup::Create(
        pkRenderedTexture->GetBuffer(), pkRenderer, true, true);

    if (!pkThis->m_spTexture)
    {
        //WorldManager::Log("Cannot create shadow texture\n");
        NiDelete pkThis;
        return NULL;
    }

    // Since we may generate texture coordinates outside of the range [0,1],
    // we must use clamping to avoid strange wrapping artifacts.
    NiTexturingProperty::Map* pkMap = NiNew NiTexturingProperty::Map(
        pkThis->m_spTexture, 0, NiTexturingProperty::CLAMP_S_CLAMP_T,
        NiTexturingProperty::FILTER_BILERP);
    NIASSERT(pkMap);
    NiTexturingProperty* pkTex = NiNew NiTexturingProperty();
    NIASSERT(pkTex);
    pkTex->SetBaseMap(pkMap);
    pkTex->SetApplyMode(NiTexturingProperty::APPLY_REPLACE);

	// 增加blur效果
	NiShaderPtr spCopyShader = NiShaderFactory::GetInstance()->
		RetrieveShader("ShadowBlur", 
		NiShader::DEFAULT_IMPLEMENTATION, true);

	NiSingleShaderMaterial* pkCopyMat = 
		NiSingleShaderMaterial::Create(spCopyShader);

	pkThis->m_spShadowGeometry->ApplyAndSetActiveMaterial(pkCopyMat);

	unsigned int ui;
	unsigned int uiTunedWidth = 512;
	unsigned int uiTunedHeight = 512;

	// Compute blur texel kernels.
	float* pfBlurTexelKernelX = NiAlloc(float, BLUR_KERNEL_SIZE * 2);
	float* pfBlurTexelKernelY = NiAlloc(float, BLUR_KERNEL_SIZE * 2);
	for (ui = 0; ui < BLUR_KERNEL_SIZE; ui++)
	{
		pfBlurTexelKernelX[ui * 2] = g_afBlurPixelKernel[ui] / uiTunedWidth;
		pfBlurTexelKernelX[ui * 2 + 1] = 0;

		pfBlurTexelKernelY[ui * 2] = 0;
		pfBlurTexelKernelY[ui * 2 + 1] = 
			g_afBlurPixelKernel[ui] / uiTunedHeight;
	}
	NiShaderFactory::UpdateGlobalShaderConstant(
		"g_vBlurWeights", BLUR_KERNEL_SIZE * sizeof(float), g_afBlurWeights);
	NiShaderFactory::UpdateGlobalShaderConstant(
		"g_vBlurTexelKernelX", BLUR_KERNEL_SIZE * sizeof(float) * 2, 
		pfBlurTexelKernelX);
	NiShaderFactory::UpdateGlobalShaderConstant(
		"g_vBlurTexelKernelY", BLUR_KERNEL_SIZE * sizeof(float) * 2, 
		pfBlurTexelKernelY);
	NiFree(pfBlurTexelKernelX);
	NiFree(pfBlurTexelKernelY);


    pkThis->m_spShadowGeometry->AttachProperty(pkTex);
	pkThis->m_spShadowGeometry->SetSortObject(false);
    pkThis->m_spShadowGeometry->UpdateProperties();

    // Clear shadow texture
    pkRenderer->BeginOffScreenFrame();
    pkRenderer->BeginUsingRenderTargetGroup(pkThis->m_spRenderTargetGroup,
        NiRenderer::CLEAR_ALL);
    pkRenderer->EndUsingRenderTargetGroup();
    pkRenderer->EndOffScreenFrame();

    // Set camera port so that outer texels are never drawn to.
    float fFraction = 2.0f / ((float)uiTexWidth);
    NiRect<float> kPort(fFraction, 1.0f - fFraction, 
        1.0f - fFraction, fFraction);

    pkThis->m_spCamera->SetViewPort(kPort);

    return pkThis;
}
//----------------------------------------------------------------------------
ShadowGeometry::~ShadowGeometry()
{
	NDL_SAFE_DELETE( m_pkPick );
}
//---------------------------------------------------------------------------
void ShadowGeometry::AddCaster(NiAVObject* pkCaster, NiCamera* camera)
{
	if( !pkCaster )
		return;

	// 如果已有caster，则移除
	if( m_spCaster )
		RecursiveStoreCasterObjects(m_spCaster,NULL,false);

    m_spCaster = pkCaster;

    // Traverse the new caster to find all of the leaf geometry objects.
    // Note that this will not clear out the list of caster geometry, and
    // will thus _add_ caster geometry to the shadow system.  However, only
    // the most recently-set caster will affect the centerpoint and bounding
    // sphere of the shadow
    
    RecursiveStoreCasterObjects(pkCaster, camera);
}
//---------------------------------------------------------------------------
void ShadowGeometry::RemoveCaster(NiAVObject* pkCaster)
{
	if( !pkCaster )
		return;

	RecursiveStoreCasterObjects(pkCaster,NULL,false);
}
//---------------------------------------------------------------------------
void ShadowGeometry::RecursiveStoreCasterObjects(NiAVObject* pkObject, NiCamera* camera/*=NULL*/, bool bAdd /*= true*/)
{
    // Find all leaf geometry objects and add them to the caster geometry 
    // list, to be rendered as a shadow
    if (NiIsKindOf(NiMesh, pkObject))
    {
		if( bAdd )
			m_kCastingObjects.Add(pkObject);
		else
		{
			for(UINT i=0; i<m_kCastingObjects.GetSize(); i++)
			{
				if( m_kCastingObjects.GetAt(i) == pkObject )
				{
					m_kCastingObjects.RemoveAt(i);
					break;
				}
			}
		}
    }
    else if (NiIsKindOf(NiNode, pkObject))
    {
        NiNode* pkNode = (NiNode*)pkObject;
		// 处理LOD
		if( NiIsKindOf(NiLODNode,pkNode) && camera )
		{
			NiLODData* pkLODData = ((NiLODNode*)pkNode)->GetLODData();
			int index = pkLODData->GetLODLevel(camera, (NiLODNode*)pkNode);
			if((index >= 0) 
				&& ((index >= (int)pkNode->GetArrayCount()) || (pkNode->GetArrayCount() == NULL)))
			{
				return;
			}
			NiAVObject* pkChild = pkNode->GetAt(index);
			if (pkChild)
				RecursiveStoreCasterObjects(pkChild, camera, bAdd);
		}
		else
		{
			for (unsigned int i = 0; i < pkNode->GetArrayCount(); i++)
			{
				NiAVObject* pkChild = pkNode->GetAt(i);
				if (pkChild)
					RecursiveStoreCasterObjects(pkChild, camera, bAdd);
			}
		}
    }
}
//----------------------------------------------------------------------------
void ShadowGeometry::Click(float fTime, NiCamera* pkSceneCamera, bool bRealShadow/* = false*/,
    bool bVisible, bool bUpdateImage)
{
    //NIASSERT(m_spCaster && m_spTexture);
	if(!(m_kCastingObjects.GetSize() && m_spTexture && m_spGroundList.size()))
		return;

	m_bRealShadow = bRealShadow;
	if( !m_bRealShadow && !m_spFakeCaster )
		return;

    // If the visible flag is false, clear out the shadow geometry and skip
    // rendering the shadow, as it won't matter to the final, rendered image.
    if (!bVisible)
    {
        m_pkPositionStream->GetRegion(0).SetRange(0);
        m_pkTexCoordStream->GetRegion(0).SetRange(0);
        m_pkIndexStream->GetRegion(0).SetRange(0);
        return;
    }

    NiUInt32 uiActiveVertexCount = m_pkPositionStream->GetRegion(0).GetRange();

    // Cull shadow geometry against the scene to avoid updating
    if (m_bForceRender)
    {
        m_bForceRender = false;
    }
    else if (pkSceneCamera && uiActiveVertexCount)
    {
        const NiFrustumPlanes& kPlanes = m_kCuller.GetFrustumPlanes();

        for (unsigned int i = NiFrustumPlanes::LEFT_PLANE;
             i < NiFrustumPlanes::MAX_PLANES; i++)
        {
            NiPlane kPlane = kPlanes.GetPlane(i);
            int iSide = m_spShadowGeometry->GetWorldBound().WhichSide(kPlane);

            if (iSide == NiPlane::NEGATIVE_SIDE) 
            {
                // Update bounds regardless to ensure proper culling
				m_kCenterP = m_spCaster->GetWorldTranslate();
                UpdateShadowGeometryBound();
                return;
            }
        }
    }

	// 假阴影更新位置
	if( !m_bRealShadow )
	{
		m_spFakeCaster->SetTranslate(m_spCaster->GetTranslate());
		m_spFakeCaster->Update(0.0f);
	}

    // move the shadow camera (and thus the apparent light)
    UpdateShadowCamera(fTime);

    if (bUpdateImage)
    {
        NiRenderer* pkRenderer = NiRenderer::GetRenderer();
        NIASSERT(pkRenderer);

        // update the background color to the renderer -- note it clears alpha
        // channel to completely transparent value to get an alpha rendered
        // texture
		NiColorA orgColor;
		pkRenderer->GetBackgroundColor(orgColor);
		pkRenderer->SetBackgroundColor(NiColor::WHITE);

        pkRenderer->BeginUsingRenderTargetGroup(m_spRenderTargetGroup,
            NiRenderer::CLEAR_ALL);

        // renderer camera port settings
        pkRenderer->SetCameraData(m_spCamera);

        NiAccumulatorPtr spSorter = pkRenderer->GetSorter();
        pkRenderer->SetSorter(NULL);

        // Render all leaf shadow caster geometry replacing their built-in 
        // render states with the single shadow state.  This will cause all of 
        // the shadow casters to be rendered as dark gray, making them look 
        // like shadows.

		if( m_bRealShadow )
		{
			for (unsigned int i = 0; i < m_kCastingObjects.GetSize(); i++)
			{
				NiMesh* pkMesh = NiDynamicCast(NiMesh, m_kCastingObjects.GetAt(i));

				if (pkMesh)
				{
					bool bOldAlphaBlending = false;
					// 如果没有NiAlphaProperty，则创建一个
					NiProperty* pkProperty = pkMesh->GetProperty(NiProperty::ALPHA);
					if( !pkProperty )
					{
						NiAlphaProperty* pAlpha = NiNew NiAlphaProperty;
						pAlpha->SetAlphaBlending( false );
						pAlpha->SetSrcBlendMode(NiAlphaProperty::ALPHA_SRCALPHA);
						pAlpha->SetDestBlendMode(NiAlphaProperty::ALPHA_INVSRCALPHA);
						pkMesh->AttachProperty(pAlpha);
					}
					else
					{
						bOldAlphaBlending = ((NiAlphaProperty*)pkProperty)->GetAlphaBlending();
						((NiAlphaProperty*)pkProperty)->SetAlphaBlending( true );
					}

					// 如果没有NiVertexColorProperty，则创建一个
					pkProperty = pkMesh->GetProperty(NiProperty::VERTEX_COLOR);
					if( !pkProperty )
					{
						NiVertexColorProperty* pkVC = NiNew NiVertexColorProperty;
						pkVC->SetSourceMode(NiVertexColorProperty::SOURCE_EMISSIVE);
						pkVC->SetLightingMode(NiVertexColorProperty::LIGHTING_E_A_D);
						pkMesh->AttachProperty(pkVC);
					}

					//pkProperty = pkMesh->GetProperty(NiProperty::SHADE);
					//if( !pkProperty )
					//{
					//	NiShadeProperty* pkShade = NiNew NiShadeProperty;
					//	pkShade->SetSmooth(true);
					//	pkMesh->AttachProperty(pkShade);
					//}
					pkMesh->UpdateProperties();

					// Swap out property state temporarily, then restore it
					NiPropertyStatePtr spOldPropertyState = pkMesh->GetPropertyState();

					// 比较Alpha值，使影子Alpha比模型小
					pkProperty = pkMesh->GetProperty(NiProperty::MATERIAL);
					NiMaterialProperty* pkMat = m_spPropertyState->GetMaterial();
					if( pkProperty && pkMat )
					{
						NiMaterialProperty* pkOldMat = (NiMaterialProperty*)pkProperty;
						float fModelAlpha = pkOldMat->GetAlpha();
						if( fModelAlpha < 0.4f )
						{
							continue;
						}
					}

					pkMesh->SetPropertyState(m_spPropertyState);
					pkMesh->RenderImmediate(pkRenderer);
					pkMesh->SetPropertyState(spOldPropertyState);

					if( !bOldAlphaBlending )
					{
						NiAlphaProperty* pkAlpha = (NiAlphaProperty*)pkMesh->GetProperty(NiProperty::ALPHA);
						pkAlpha->SetAlphaBlending(bOldAlphaBlending);
					}
					pkMesh->UpdateProperties();
				}
			}
		}
		else
		{
			// 渲染假阴影
			//NiPropertyStatePtr spOldPropertyState = m_spFakeCaster->GetPropertyState();
			//m_spFakeCaster->SetPropertyState(m_spPropertyState);
			m_spFakeCaster->RenderImmediate(pkRenderer);
			//m_spFakeCaster->SetPropertyState(spOldPropertyState);
		}

        pkRenderer->SetSorter(spSorter);
        pkRenderer->EndUsingRenderTargetGroup();
		pkRenderer->SetBackgroundColor(orgColor);
    }

    // Determine which triangles fall inside of the shadow frustum.
    UpdateShadowGeometry();
}
//---------------------------------------------------------------------------
void ShadowGeometry::UpdateShadowCamera(float fTime)
{
    // this function moves the shadow camera so that it appears to view the
    // target (caster) from infinity, facing a fixed direction.  This is done
    // by  moving the camera so the the desired fixed direction vector is
    // always coincident with the line through the caster's bounding volume
    // center and the camera location
    if (!m_spCamera)
        return;

    // get the "look at" point
	NiPoint3 kTarget;
	float fRadius;
	if( m_bRealShadow )
	{
		kTarget= m_spCaster->GetWorldBound().GetCenter();
		fRadius= m_spCaster->GetWorldBound().GetRadius();
	}
	else
	{
		fRadius= m_spFakeCaster->GetModelBound().GetRadius();
		kTarget= m_spFakeCaster->GetTranslate();
		kTarget.z += fRadius;
	}

    // translate the camera to a distant point such that the camera is looking
    // directly at the target point
    NiPoint3 kTranslate = kTarget - (m_kLightDir * 500.0f);
    m_spCamera->SetTranslate(kTranslate);

	NiPoint3 kYVec = -m_kLightDir.Perpendicular();
	NiPoint3 kZVec = m_kLightDir.UnitCross(kYVec);
	// Rotate the camera based on the orthonormal frame
	NiMatrix3 kRotation(m_kLightDir, kYVec, kZVec);
	m_spCamera->SetRotate(kRotation);
	m_spCamera->Update(fTime);

    // set the field of view of the camera to enclose the bounding sphere of 
    // the caster object.

    float fFOV =  fRadius / (kTarget - kTranslate).Length();// * 0.95f;

    NiFrustum kFrust = m_spCamera->GetViewFrustum();
    kFrust.m_fLeft = -fFOV;
    kFrust.m_fRight = fFOV;
    kFrust.m_fTop = fFOV;
    kFrust.m_fBottom = -fFOV;
    m_spCamera->SetViewFrustum(kFrust);

    m_spCamera->Update(fTime);
}
//---------------------------------------------------------------------------
void ShadowGeometry::UpdateShadowGeometry()
{
    // Reset active vertex and triangle counts
    m_pkPositionStream->GetRegion(0).SetRange(0);
    m_pkTexCoordStream->GetRegion(0).SetRange(0);
    m_pkIndexStream->GetRegion(0).SetRange(0);

    // Find the projection of the camera location onto the terrain -- it
    // represents the center of our shadow geometry -- this world space
    // point is used during texture coordinate generation in AddShadowTriangle
    
	NiPoint3 kPickPos;
	float fRadius;
	if( m_bRealShadow )
	{
		kPickPos = m_spCaster->GetWorldBound().GetCenter();
		fRadius= m_spCaster->GetWorldBound().GetRadius();
	}
	else
	{
		fRadius= m_spFakeCaster->GetModelBound().GetRadius();
		kPickPos = m_spFakeCaster->GetTranslate();
		kPickPos.z += fRadius;
	}

	float fCameraToCaster = (m_spCaster->GetTranslate() - m_spCamera->GetWorldLocation()).Length();

	for(std::vector<NiAVObjectPtr>::iterator iter = m_spGroundList.begin(); iter != m_spGroundList.end(); ++iter)
	{
		NiAVObject* pkGround = *iter;
		m_pkPick->SetTarget(pkGround);
		if( m_pkPick->PickObjects( kPickPos, m_spCamera->GetWorldDirection() ) )
		{
			const NiPick::Results& kResults = m_pkPick->GetResults();
			if( kResults.GetSize() > 0 )
			{
				bool bGet = false;
				for(UINT i=0; i<kResults.GetSize(); ++i)
				{
					NiPick::Record* pkRecord = kResults.GetAt(0);
					NiPoint3 kPoint = pkRecord->GetIntersection();
					// 如果pick点与相机距离，比人与相机距离近，则跳过
					if( (kPoint - m_spCamera->GetWorldLocation()).Length() < fCameraToCaster )
						continue;

					m_kCenterP = kPoint;
					bGet = true;
					break;
				}
				if( bGet )
					break;
			}
		}
	}

    // Calculate an approximate width for the shadow geometry -- used
    // in texture coordinate generation
    m_fOOWidth = 1.0f / (fRadius * 2.0f); 

	fAddTriangleTime = 0.f;
	fAddGeometryTime = 0.f;
	nShadowTriCount = 0;
	//static float time = SwGlobal::s_timer.GetTimeCur();

    // Traverse the ground object using frustum culling for quick outs
    // The ground geometry should ideally be diced into a quad-tree 
    // or some other data structure to allow maximum benefits from
    // frustum culling.
	for(std::vector<NiAVObjectPtr>::iterator iter = m_spGroundList.begin(); iter != m_spGroundList.end(); ++iter)
	{
		NiAVObject* pkGround = *iter;
		TraverseGroundGeometry(pkGround);
	}

	//if( SwGlobal::s_timer.GetTimeCur() - time > 1.0f )
	//{
	// 	time = SwGlobal::s_timer.GetTimeCur();
	//	Trace("Cull Shadow: %.3f, Add Shadow: %.3f, Tri Count: %d\n", fAddGeometryTime - fAddTriangleTime, fAddTriangleTime, nShadowTriCount);
	//}

    UpdateShadowGeometryBound();
}
//---------------------------------------------------------------------------
void ShadowGeometry::UpdateShadowGeometryBound()
{
    // Manually set the bounding sphere of the shadow geometry to ensure
    // it is not culled by the engine
    float fRadius;
	if( m_bRealShadow )
		fRadius= m_spCaster->GetWorldBound().GetRadius();
	else
		fRadius= m_spFakeCaster->GetModelBound().GetRadius();

    NiBound kSphere;
    kSphere.SetCenterAndRadius(m_kCenterP, fRadius * 1.05f);
    m_spShadowGeometry->SetModelBound(kSphere);

    m_spShadowGeometry->Update(0.0f);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ShadowGeometry::TraverseGroundGeometry(NiAVObject* pkObject)
{
    m_kVisible.RemoveAll();
    m_kCuller.Cull(m_spCamera, pkObject, 0);

	NiPoint3 kCasterCenter = m_spCaster->GetWorldBound().GetCenter();
	float fCasterRadius = m_spCaster->GetWorldBound().GetRadius();
	float fCasterHeadZ = m_spCaster->GetWorldTranslate().z + 1.7f;

    const unsigned int uiQuantity = m_kVisible.GetCount();
    for (unsigned int i = 0; i < uiQuantity; i++)
    {
        NiRenderObject* pkGeom = &m_kVisible.GetAt(i);
        NiMesh* pkMesh = NiVerifyStaticCast(NiMesh, pkGeom);
		if( pkMesh )
		{
			// 有交集，并且最低值在玩家头部高度以下，阴影可能投射到该模型上
			NiPoint3 kMeshCenter = pkMesh->GetWorldBound().GetCenter();
			float fMeshRadius = pkMesh->GetWorldBound().GetRadius();
			if( (kCasterCenter - kMeshCenter).Length() <= fCasterRadius + fMeshRadius
				&& kMeshCenter.z - fMeshRadius < fCasterHeadZ)
				AddToShadowGeometry(pkMesh);
		}
    }
}
//---------------------------------------------------------------------------
void ShadowGeometry::AddToShadowGeometry(NiMesh* pkMesh)
{
    NIASSERT(pkMesh);

    // This code assumes that model space vertices ARE in world space
	NiFixedString strMesh = pkMesh->GetName();
	if( pkMesh->GetPrimitiveType() == NiMesh::PRIMITIVE_TRIANGLES && strMesh.ContainsNoCase("Shape_") )
	{
		NiDataStreamElementLock kPositionsLock = NiDataStreamElementLock(pkMesh,
			NiCommonSemantics::POSITION(), 0, NiDataStreamElement::F_FLOAT32_3, 
			NiDataStream::LOCK_READ);
		NIASSERT(kPositionsLock.IsLocked());

		NiTStridedRandomAccessIterator<NiPoint3> kPositionsIter = 
			kPositionsLock.begin<NiPoint3>();

		NiUInt32  uiPositionCount = kPositionsLock.count();

		for (int row=0; row < 16; row+=2) 
		{
			int offset = ((row+1)/2)*9 + (row/2)*8;
			NiPoint3 *thisrow = &kPositionsIter[offset];
			offset = ((row+2)/2)*9 + ((row+1)/2)*8;
			NiPoint3 *nextrow = &kPositionsIter[offset];
			offset = ((row+3)/2)*9 + ((row+2)/2)*8;
			NiPoint3 *overrow = &kPositionsIter[offset];

			//float fTime = GameGlobal::s_timer.GetTimeCur();

			for(int col=0; col< 8; col++) 
			{
				CullTriAgainstCameraFrustum(overrow[col], thisrow[col], nextrow[col]);
				CullTriAgainstCameraFrustum(nextrow[col], thisrow[col], thisrow[(col + 1)]);
				CullTriAgainstCameraFrustum(overrow[(col + 1)], overrow[col], nextrow[col]);
				CullTriAgainstCameraFrustum(nextrow[col], thisrow[(col + 1)], overrow[(col + 1)]);
			}
			//fTime = (GameGlobal::s_timer.GetTimeCur() - fTime) * 1000.f;
			//fAddGeometryTime += fTime;
		}
		kPositionsLock.Unlock();
	}
	else
	{
		// First determine the format of the mesh
		// Determine if its an indexed mesh
		NiDataStreamRef* pkIndexStreamRef = 
			pkMesh->GetFirstStreamRef(NiDataStream::USAGE_VERTEX_INDEX);

		if (!pkIndexStreamRef)
		{
			NIASSERT(!"Data not appropriate to build Shadow Geometry");
			return;
		}

		// If there is an index buffer, it should always have only one element 
		// reference since interleaved index buffers do not make sense. 
		NIASSERT(pkIndexStreamRef->GetElementDescCount() == 1);

		// Get vertex data to cull against shadow volume
		// This code assumes that model space vertices ARE in world space
		NiDataStreamRef* pkPosStreamRef = pkMesh->FindStreamRef(
			NiCommonSemantics::POSITIONT(), 0, NiDataStreamElement::F_FLOAT32_3);

		NiFixedString fixedString;
		if (!pkPosStreamRef)
		{
			// 如果没有世界坐标系坐标，则用本地坐标
			fixedString = NiCommonSemantics::POSITION();
		}
		else
			fixedString = NiCommonSemantics::POSITIONT();

		NiDataStreamElementLock kPositionLock(pkMesh,
			fixedString, 0,
			NiDataStreamElement::F_FLOAT32_3, 
			NiDataStream::LOCK_READ);

		NiTStridedRandomAccessIterator<NiPoint4> kPositionIter = 
			kPositionLock.begin<NiPoint4>();

		NiUInt32 uiIndexBufferCount = pkIndexStreamRef->GetTotalCount();

		// Lock index stream 
		NiDataStreamPrimitiveLock kIndicesLock(pkMesh,
			NiDataStream::LOCK_READ);

		// Used to process one triangle at a time
		unsigned int s0;
		unsigned int s1;
		unsigned int s2;

		if (kIndicesLock.Has16BitIndexBuffer())
		{
			NiIndexedPrimitiveIterator16 kBegin = kIndicesLock.BeginIndexed16(0);
			NiIndexedPrimitiveIterator16 kEnd = kIndicesLock.EndIndexed16(0);
			NiIndexedPrimitiveIterator16 kIter = kBegin;

			int j=0;
			

			while(kIter != kEnd)
			{

				NIASSERT((*kIter).count() == 3);    // Tri-based

				s0 = (*kIter)[0];
				s1 = (*kIter)[1];
				s2 = (*kIter)[2];

				// Check for degenerates.
				if (s0 == s1 || s0 == s2 || s1 == s2)
				{
					++kIter;
					continue;
				}

				NiPoint3 kPoint[3];

				kPoint[0] = kPositionIter[s0];
				kPoint[1] = kPositionIter[s1];
				kPoint[2] = kPositionIter[s2];

				//float fTime = GameGlobal::s_timer.GetTimeCur();

				CullTriAgainstCameraFrustum(kPoint[0], kPoint[1], kPoint[2]);
				//fTime = (GameGlobal::s_timer.GetTimeCur() - fTime) * 1000.f;
				//fAddGeometryTime += fTime;

				++kIter;
			}
		}
		else
		{
			NIASSERT(kIndicesLock.Has32BitIndexBuffer());
			// Add triangles to the shadow geometry (mesh) 
			unsigned int uiTris = uiIndexBufferCount/3;
			NiIndexedPrimitiveIterator32 kIndicesIter =
				kIndicesLock.BeginIndexed32(0);
			for (unsigned int ui = 0; ui < uiTris; ui++)
			{		

				s0 = (unsigned int)kIndicesIter[ui][0];
				s1 = (unsigned int)kIndicesIter[ui][1];
				s2 = (unsigned int)kIndicesIter[ui][2];

				if (s0 == s1 || s0 == s2 || s1 == s2)
					continue;

				// Clip each world triangle to the camera's frustum
				NiPoint3 kPoint[3];

				kPoint[0] = kPositionIter[s0];
				kPoint[1] = kPositionIter[s1];
				kPoint[2] = kPositionIter[s2];

				//float fTime = GameGlobal::s_timer.GetTimeCur();
				CullTriAgainstCameraFrustum(kPoint[0], kPoint[1], kPoint[2]);
				//fTime = (GameGlobal::s_timer.GetTimeCur() - fTime) * 1000.f;
				//fAddGeometryTime += fTime;
			}
		}

		// Unlock all streams
		kIndicesLock.Unlock();
		kPositionLock.Unlock();
	}
}
//---------------------------------------------------------------------------
bool ShadowGeometry::GenerateCameraRay(unsigned int uiIndex, NiPoint3& kPt, 
    NiPoint3& kDir)
{
    const NiFrustum& kFrust = m_spCamera->GetViewFrustum();
    float fVx = (uiIndex & 0x1) ? kFrust.m_fRight :  kFrust.m_fLeft;
    float fVy = (uiIndex & 0x2) ? kFrust.m_fTop : kFrust.m_fBottom;

    // convert world view plane coordinates to ray with kDir and kOrigin
    // kDir: camera world location to view plane coordinate
    // kOrigin: camera world location
    m_spCamera->ViewPointToRay(fVx, fVy, kPt, kDir);
    return true;
}
//---------------------------------------------------------------------------
void ShadowGeometry::CullTriAgainstCameraFrustum(NiPoint3& kV0, 
    NiPoint3& kV1, NiPoint3& kV2)
{
	// 判断三个顶点到相机距离，是否都比人到相机距离近，是则剔除
	float fCameraToCaster = (m_spCaster->GetTranslate() - m_spCamera->GetWorldLocation()).Length();
	float fCameraToV0 = (kV0 - m_spCamera->GetWorldLocation()).Length();
	float fCameraToV1 = (kV1 - m_spCamera->GetWorldLocation()).Length();
	float fCameraToV2 = (kV2 - m_spCamera->GetWorldLocation()).Length();
	if( fCameraToV0 < fCameraToCaster && fCameraToV1 < fCameraToCaster && fCameraToV2 < fCameraToCaster )
		return;

    // Cull triangle vertices against camera planes.  If all three vertices
    // fall on the outside of any single plane, cull.  Skip the near and far
    // planes (indices i = 0,1).
    unsigned int i = NiFrustumPlanes::LEFT_PLANE;
    for (; i < NiFrustumPlanes::MAX_PLANES; i++)
    {
        const NiPlane& kPlane = m_kCuller.GetFrustumPlanes().GetPlane(i);

        // vert 0 in?
        if (kPlane.Distance(kV0) >= 0.0f) 
            continue;

        // vert 1 in?
        if (kPlane.Distance(kV1) >= 0.0f) 
            continue;

        // vert 2 in?
        if (kPlane.Distance(kV2) >= 0.0f) 
            continue;

        // all verts outside of a single plane - culled
        return;
    }

    NiPlane kTriPlane(kV0, kV1, kV2);
    const NiPoint3& kNorm = kTriPlane.m_kNormal;

    // we know that the ray center is the camera location
    NiPoint3 kCamRayPt = m_spCamera->GetWorldLocation();
    NiPoint3 akCamRayDirs[4];
    NiPoint3 akCamRayIntersect[4];

    // No intersection if the point is behind the triangle
    const float fDist = kTriPlane.Distance(kCamRayPt);
    if (fDist < 0.0f)
        return;

    NiPoint3 kE;

    // Next, compute the intersection points of the frustum corners with the
    // plane of the triangle.  There will be four of them if the frustum
    // goes through the triangle.  If not, there may be far fewer.  However,
    // for now, if any view frustum edge doesn't intersect the plane of the
    // triangle, we give up and add the triangle.
    for (i = 0; i < 4; i++)
    {
        NiPoint3 kTemp;
        if (!GenerateCameraRay(i, kTemp, akCamRayDirs[i]))
            goto CannotCull;
        
        // compute the intersection of the plane of the triangle with the ray
        const float fNormDot = kNorm.Dot(akCamRayDirs[i]);
        
        // if the rays are in the same direction, no intersection (backfacing)
        if (fNormDot >= -1.0e-5f)
            goto CannotCull;
        
        akCamRayIntersect[i] 
            = kCamRayPt - akCamRayDirs[i] * (fDist / fNormDot);
    }
    
    // now, test each of the frustum intersection points against each of the
    // triangle edges.  If all 4 points are on the same side of a triangle
    // edge, cull the triangle

    // We will compute the cross product of the triangle edge and the vector
    // from one of the edge vertices to the frustum point, and then compute
    // the dot of that vector with the triangle normal.  The sign of this dot
    // is the CCW/CW value
    kE = kV1 - kV0;
    for (i = 0; i < 4; i++)
    {
        // if the dot triple product ((UxV)*W) is positive, then the frustum 
        // point is on the inside of the given triangle edge, and we cannot
        // cull based on this edge.
        if (kE.Cross(akCamRayIntersect[i] - kV1).Dot(kNorm) >= 1.0e-5f)
            break;
    }
    // all points on outside of single edge - culled
    if (i == 4)
        return;

    kE = kV2 - kV1;
    for (i = 0; i < 4; i++)
    {
        // if the dot triple product ((UxV)*W) is positive, then the frustum 
        // point is on the inside of the given triangle edge, and we cannot
        // cull based on this edge.
        if (kE.Cross(akCamRayIntersect[i] - kV2).Dot(kNorm) >= 1.0e-5f)
            break;
    }
    // all points on outside of edge - culled
    if (i == 4)
        return;

    kE = kV0 - kV2;
    for (i = 0; i < 4; i++)
    {
        // if the dot triple product ((UxV)*W) is positive, then the frustum 
        // point is on the inside of the given triangle edge, and we cannot
        // cull based on this edge.
        if (kE.Cross(akCamRayIntersect[i] - kV0).Dot(kNorm) >= 1.0e-5f)
            break;
    }
    // all points on outside of edge - culled
    if (i == 4)
        return;

CannotCull:
	//float fTime = GameGlobal::s_timer.GetTimeCur();

    NiPoint3 akTri[3];
    akTri[0] = kV0;
    akTri[1] = kV1;
    akTri[2] = kV2;

    AddShadowTriangle(akTri);
	//fTime = (GameGlobal::s_timer.GetTimeCur() - fTime) * 1000.f;
	//fAddTriangleTime += fTime;
}    
//---------------------------------------------------------------------------
void ShadowGeometry::AddShadowTriangle(NiPoint3 akV[3])
{
    NiUInt32 uiVertsCount = m_pkPositionStream->GetRegion(0).GetRange();
    NiUInt32 uiTrisCount = m_spShadowGeometry->GetPrimitiveCount(0);
    
    if ((uiVertsCount + 3) <= m_uiMaxVertexCount && 
        (uiTrisCount + 1) <= m_uiMaxTriangleCount)
    {
        // For texture coordinates, generate s and t based on point Q's
        // distance along the RIGHT(R) and UP(U) relative to the 
        // projection of the camera's location(P) (assuming non-skewed
        // frustum) onto the ground geometry.
        //
        // s = (R * (Q - P)) / width - 0.5
        // t = (U * (Q - P)) / height - 0.5

        NiDataStreamElementLock kTexCoordLock = NiDataStreamElementLock(
            m_spShadowGeometry, NiCommonSemantics::TEXCOORD(), 0, 
            NiDataStreamElement::F_FLOAT32_2);
        NIASSERT(kTexCoordLock.IsLocked());

        NiTStridedRandomAccessIterator<NiPoint2> kTexCoordIter = 
            kTexCoordLock.begin<NiPoint2>();

        for (unsigned int i = 0; i < 3; i++)
        {
            NiPoint3 kDiff = akV[i] - m_kCenterP;

            kTexCoordIter[uiVertsCount + i].x = 
                (m_spCamera->GetWorldRightVector() * kDiff) * m_fOOWidth + 0.5f;
            // Negated direction is due to rendered texture being inverted
            kTexCoordIter[uiVertsCount + i].y = 
                (-m_spCamera->GetWorldUpVector() * kDiff) * m_fOOWidth + 0.5f;
        }

        // We know z-axis is up so we offset upward in z by a few inches
        const float fZOffset = 0.01f;
        akV[0].z += fZOffset;
        akV[1].z += fZOffset;
        akV[2].z += fZOffset;

        NiDataStreamElementLock kPositionsLock = NiDataStreamElementLock(
            m_spShadowGeometry, NiCommonSemantics::POSITION(), 0,
            NiDataStreamElement::F_FLOAT32_3);
        NIASSERT(kPositionsLock.IsLocked());

        NiDataStreamElementLock kIndicesLock = NiDataStreamElementLock(
            m_spShadowGeometry, NiCommonSemantics::INDEX(), 0,
            NiDataStreamElement::F_UINT16_1);
        NIASSERT(kIndicesLock.IsLocked());

        NiTStridedRandomAccessIterator<NiPoint3> kPositionsIter = 
            kPositionsLock.begin<NiPoint3>();

        NiTStridedRandomAccessIterator<NiUInt16> kIndicesIter = 
            kIndicesLock.begin<NiUInt16>();

        kPositionsIter[uiVertsCount] = akV[0];        
        kPositionsIter[uiVertsCount + 1] = akV[1];        
        kPositionsIter[uiVertsCount + 2] = akV[2];        

        NiUInt16 usBase = uiTrisCount * 3;

        kIndicesIter[usBase] = uiVertsCount;
        kIndicesIter[usBase + 1] = uiVertsCount + 1;
        kIndicesIter[usBase + 2] = uiVertsCount + 2;
        
        m_pkPositionStream->GetRegion(0).SetRange(uiVertsCount + 3);
        m_pkTexCoordStream->GetRegion(0).SetRange(uiVertsCount + 3);
        m_pkIndexStream->GetRegion(0).SetRange(uiVertsCount + 3);
		//nShadowTriCount = (int)((uiVertsCount + 3)* 1.f / 3.f);
    }
}

bool ShadowGeometry::NeedRender()
{
	return (m_kCastingObjects.GetSize() && m_spGroundList.size());
}

void ShadowGeometry::AddGroundSceneGraph(NiAVObject* pkGround)
{
	//根据与caster的距离从近到远插入m_spGroundList
	if( !m_spGroundList.size() || m_spCaster == NULL)
		m_spGroundList.push_back(pkGround);
	else
	{
		// 避免模型重复
		for(UINT i = 0; i<m_spGroundList.size(); ++i)
		{
			if( m_spGroundList[i] == pkGround )
				return;
		}

		float insertDist = (pkGround->GetWorldBound().GetCenter() - m_spCaster->GetWorldBound().GetCenter()).Length()
						- pkGround->GetWorldBound().GetRadius();
		bool bInsert = false;
		for(std::vector<NiAVObjectPtr>::iterator iter = m_spGroundList.begin(); iter != m_spGroundList.end(); ++iter)
		{
			float dist = ((*iter)->GetWorldBound().GetCenter() - m_spCaster->GetWorldBound().GetCenter()).Length()
						- (*iter)->GetWorldBound().GetRadius();
			if( dist > insertDist )
			{
				// 插入iter之前
				m_spGroundList.insert(iter, pkGround);
				bInsert = true;
				break;
			}
		}
		if( !bInsert )
		{
			m_spGroundList.push_back(pkGround);
		}
	}
}

void ShadowGeometry::SetLightDir(const NiPoint3& kLightDir)
{
	m_kLightDir = kLightDir;
	m_kLightDir.Unitize();
}

void ShadowGeometry::AddFakeCaster( NiMesh* pkFakeCaster )
{
	m_spFakeCaster = pkFakeCaster;

	NiProperty* pkProperty = m_spFakeCaster->GetProperty(NiProperty::ALPHA);
	if( !pkProperty )
	{
		NiAlphaProperty* pAlpha = NiNew NiAlphaProperty;
		pAlpha->SetAlphaBlending( true );
		pAlpha->SetSrcBlendMode(NiAlphaProperty::ALPHA_SRCALPHA);
		pAlpha->SetDestBlendMode(NiAlphaProperty::ALPHA_INVSRCALPHA);
		m_spFakeCaster->AttachProperty(pAlpha);
		m_spFakeCaster->UpdateProperties();
	}

	m_spFakeCaster->SetPropertyState(m_spFakePropertyState);
}
//---------------------------------------------------------------------------
