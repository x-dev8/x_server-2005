/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlWorldSorter.cpp
* Date: 	01/31/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "EditAccumulator.h"
////////////////////////////////////////////////////////////////////////////////

NiImplementRTTI( CEditAccumulator, SwAccumulator );
////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
CEditAccumulator::CEditAccumulator() : SwAccumulator()
{ 
	m_isWireframe			= false;

	m_dynamicEffect			= NULL;
	m_dirLight				= NULL;

	m_dynamicEffectSelected	= NULL;
	m_dirLightSelected		= NULL;

	CreatePropertyList();
	CreateLight();
}

CEditAccumulator::~CEditAccumulator() 
{
	m_dynamicEffect			= NULL;
	m_dirLight				= NULL;

	m_dynamicEffectSelected	= NULL;
	m_dirLightSelected		= NULL;

	while(!m_propertyList.IsEmpty()) {
		m_propertyList.RemoveHead();
	}
}

bool CEditAccumulator::CreatePropertyList()
{
	NiVertexColorPropertyPtr vertColor = NiNew NiVertexColorProperty();
	vertColor->SetSourceMode(NiVertexColorProperty::SOURCE_IGNORE);
	vertColor->SetLightingMode(NiVertexColorProperty::LIGHTING_E);
	m_propertyList.AddHead((NiProperty*)vertColor);

	// WHY: 打开就有内存泄漏.
	//NiMaterialPropertyPtr matProp = NiNew NiMaterialProperty();
	//matProp->SetEmittance(D3DXCOLOR(1.0f, 1.0f, 0.0f));
	//matProp->SetAlpha(1.0f);
	//m_propertyList.AddHead((NiProperty*)matProp);

	NiTexturingPropertyPtr texture = NiNew NiTexturingProperty();
	m_propertyList.AddHead((NiProperty*)texture);

	NiWireframePropertyPtr wireFrame = NiNew NiWireframeProperty();
	wireFrame->SetWireframe( true );
	m_propertyList.AddHead( (NiProperty*)wireFrame );

	NiShadePropertyPtr shade = NiNew NiShadeProperty();
	shade->SetSmooth(false);
	m_propertyList.AddHead((NiProperty*)shade);

	return true;
}

bool CEditAccumulator::CreateLight() 
{
	m_dirLight	= NiNew NiDirectionalLight();
	SetDefaultLight();

	m_dynamicEffect	= NiNew NiDynamicEffectState();
	m_dynamicEffect->AddEffect( m_dirLight );

	m_dirLightSelected	= NiNew NiDirectionalLight();
	m_dirLightSelected->SetAmbientColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f ) );
	m_dirLightSelected->SetDiffuseColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f ) );
	m_dirLightSelected->SetSpecularColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f ) );

	HR3D_Quaternion Quat1(NI_PI/3.0f, HR3D_Vector(0.0f, 0.0f, 1.0f));
	HR3D_Quaternion Quat2(NI_PI*2.0f/3.0f, HR3D_Vector(NiSin(NI_PI/3.0f), -NiCos(NI_PI/3.0f), 0.0f));
	m_dirLightSelected->SetRotate(Quat2*Quat1);
	m_dirLightSelected->SetName("Sun Light Selected!");

	m_dynamicEffectSelected	= NiNew NiDynamicEffectState();
	m_dynamicEffectSelected->AddEffect( m_dirLightSelected );

	return true;
}

void CEditAccumulator::SetWireframe( bool isWireframe )
{
	m_isWireframe = isWireframe;
}

	


//---------------------------------------------------------------------------
void CEditAccumulator::RegisterSelObjectArray(NiVisibleArray& kArray)
{
	NiRenderer* pkRenderer = NiRenderer::GetRenderer();
	Assert( NULL != pkRenderer );

	const unsigned int uiQuantity = kArray.GetCount();
	for( unsigned int i = 0; i < uiQuantity; i++ ) {
		NiRenderObject* pkObject = &kArray.GetAt(i);
		Assert( NULL != pkObject );

		if( pkObject->GetPropertyState() )
		{
			const NiAlphaProperty* pkAlpha = pkObject->GetPropertyState()->GetAlpha();
			// If alpha blended, then add to the list - otherwise,
			// draw immediately
			if( pkAlpha->GetAlphaBlending() && ( pkAlpha->GetTestRef() != 255 ) ) {
				m_alphaItemsSel.AddTail( pkObject );
			}
			else {
				NiDynamicEffectStatePtr spEffects = pkObject->GetEffectState();
				pkObject->SetEffectState( m_dynamicEffectSelected );
				pkObject->RenderImmediate( pkRenderer );
				pkObject->SetEffectState( m_dynamicEffectSelected );
			}
		}
	}
}

void CEditAccumulator::FinishAccumulating()
{
	if ( !m_pkCamera )
		return;

	NiRenderer* pkRenderer = NiRenderer::GetRenderer();
	Assert( NULL != pkRenderer );

// 	for( sInt32 i=0; i<4; i++ ) {
// 		while( m_chunkItem[i].GetSize() ) {
// 			NiRenderObject* pkObject = m_chunkItem[i].RemoveHead();
// 			pkObject->RenderImmediate( pkRenderer );
// #ifdef WORLD_EDIT
// 			if( m_isWireframe )	{
// 				pkObject->GetPropertyState()->SwapProperties( m_propertyList );
// 				pkObject->RenderImmediate( pkRenderer );
// 				pkObject->GetPropertyState()->SwapProperties( m_propertyList );
// 			}
// #endif	// WORLD_EDIT.
// 		}
// 	}
// 	while( m_alphaItems.GetSize() ) {
// 		NiRenderObject* pkObject = m_alphaItems.RemoveHead();
// 		NiDynamicEffectStatePtr spEffects = pkObject->GetEffectState();
// 
// 		pkObject->SetEffectState( m_dynamicEffect );
// 		pkObject->RenderImmediate(NiRenderer::GetRenderer());
// 		pkObject->SetEffectState(spEffects);
// 	}
// 	Assert( m_alphaItems.GetSize() == 0 );

	while( m_alphaItemsSel.GetSize() ) {
		NiRenderObject* pkObject = m_alphaItemsSel.RemoveHead();
		NiDynamicEffectStatePtr spEffects = pkObject->GetEffectState();

		pkObject->SetEffectState( m_dynamicEffectSelected );
		pkObject->RenderImmediate(NiRenderer::GetRenderer());
		pkObject->SetEffectState( m_dynamicEffectSelected );
	}
	Assert( m_alphaItemsSel.GetSize() == 0 );
	SwAccumulator::FinishAccumulating();
}

//---------------------------------------------------------------------------
// cloning
//---------------------------------------------------------------------------
void CEditAccumulator::CopyMembers( CEditAccumulator* pkDest, NiCloningProcess& kCloning )
{
	NiAccumulator::CopyMembers( pkDest, kCloning );
}

//---------------------------------------------------------------------------
// streaming
//---------------------------------------------------------------------------
void CEditAccumulator::LoadBinary( NiStream& kStream )
{
	NiAccumulator::LoadBinary( kStream );
}

//---------------------------------------------------------------------------
void CEditAccumulator::LinkObject( NiStream& kStream )
{
	NiAccumulator::LinkObject( kStream );
}

//---------------------------------------------------------------------------
bool CEditAccumulator::RegisterStreamables( NiStream& kStream )
{
	return NiAccumulator::RegisterStreamables( kStream );
}

//---------------------------------------------------------------------------
void CEditAccumulator::SaveBinary( NiStream& kStream )
{
	NiAccumulator::SaveBinary( kStream );
}

//---------------------------------------------------------------------------
bool CEditAccumulator::IsEqual( NiObject* pkObject )
{
	return NiAccumulator::IsEqual( pkObject );
}

void CEditAccumulator::SetDefaultLight()
{
	m_dirLight->SetAmbientColor( D3DXCOLOR( 0.3f, 0.3f, 0.6f ) );
	m_dirLight->SetDiffuseColor( D3DXCOLOR( 0.6f, 0.6f, 0.3f ) );
	m_dirLight->SetSpecularColor( D3DXCOLOR( 0.3f, 0.3f, 0.3f ) );

	HR3D_Vector dir = m_dirLight->GetWorldDirection();
	Trace( "Dir[%8.3f,%8.3f,%8.3f] \n", dir.x, dir.y, dir.z );

	NiMatrix3 rot;
	rot.FromEulerAnglesXYZ( 0.0f, -NI_PI*0.5f, 0.0f );
	m_dirLight->SetRotate( rot );
	m_dirLight->Update( 0.0f );

	dir = m_dirLight->GetWorldDirection();
	Trace( "Dir[%8.3f,%8.3f,%8.3f] \n", dir.x, dir.y, dir.z );

	HR3D_Quaternion Quat1(NI_PI/3.0f, HR3D_Vector(0.0f, 0.0f, 1.0f));
	HR3D_Quaternion Quat2(NI_PI*2.0f/3.0f, HR3D_Vector(NiSin(NI_PI/3.0f), -NiCos(NI_PI/3.0f), 0.0f));
	m_dirLight->SetRotate(Quat2*Quat1);
	m_dirLight->SetName("Sun Light");
}
//---------------------------------------------------------------------------

