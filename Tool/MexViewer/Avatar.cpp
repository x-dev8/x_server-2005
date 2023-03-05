#include "StdAfx.h"
#include "Avatar.h"

#include "ModelObj.h"
#include "Utility.h"

extern int GetVertexStride( DWORD dwFvf );

#define INTENSIFY_FILENAME_PREFIX "Intensify_Star_"

const char *AttachmentNames[] =
{
	"____.Hair",
	"____.Helmet",
	"____.Face",
	//"attc.LeftShoulder",
	//"attc.RightShoulder",
	"____.Armour",
	"attc.Shoulder",
	"attc.LeftHand",
	"attc.RightHand",
	"____.Glove",
	//"attc.RightBack",
	//"attc.LeftBack",
	"attc.Shield",
	"____.Shoes",
	//"attc.Trousers",
	//"attc.BackShield"
};

Avatar::Component::Component()
{
	this->Reset();
}

Avatar::Component::~Component()
{
	ReplaceableTextureProj.UnRegisterTextures();
	LuminanceTextureProj.UnRegisterTextures();

	ReplaceableTextureProj.Loaded(FALSE);
	LuminanceTextureProj.Loaded(FALSE);
}

void Avatar::Component::Reset()
{
	IsAttachment = FALSE;

	ModelObject = NULL;
	MtrlAnims = NULL;

	SpecularTexID = -1;

	AvatarSetting = NULL;

	if (ReplaceableTextureProj.IsLoaded())
	{
		ReplaceableTextureProj.UnRegisterTextures();
		ReplaceableTextureProj.Loaded(FALSE);
	}

	if (LuminanceTextureProj.IsLoaded())
	{
		LuminanceTextureProj.UnRegisterTextures();
		LuminanceTextureProj.Loaded(FALSE);
	}

	Chunks.clear();
	Flags.clear();
}

Avatar::Avatar(ModelObj *parent)
{
	mParent = parent;
	if (parent->model->GetMex() != NULL)
	{
		IMexAttachments *atts = parent->model->GetMex()->GetAttachments();
		if (atts != NULL)
		{
			if (atts != NULL)
			{
				for (int i = 0; i < 10; ++i)
				{
					mAttachments.push_back(atts->FindAttachment(AttachmentNames[i]));
				}
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			mComponents.insert(std::make_pair(i, new Component));
		}
	}
}

Avatar::~Avatar()
{
	for (AvatarComponentsIter iter = mComponents.begin(); iter != mComponents.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void Avatar::ChangeAvatarComponent(ComponentType componentType, ModelObj *obj)
{
	if ((componentType >= 0 && componentType <= Avatar::Shoes) && obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
	{
		return;
	}

	AvatarComponentsIter iter = mComponents.find(componentType);
	if (iter == mComponents.end())
	{
		return;
	}

	Component *component = iter->second;
	component->Reset();
	component->ModelObject = obj;

	switch (componentType)
	{
	case Avatar::Hat:
	case Avatar::LeftHand:
	case Avatar::RightHand:
		component->IsAttachment = TRUE;
		break;
	}

	IMexGeometry *geometry = obj->model->GetMex()->GetGeometry();
	if (geometry != NULL)
	{
		for( int i = 0; i < geometry->GetChunkCount(); i++ )
		{
			IRenderable *chunk = geometry->GetChunk(i);
			if (chunk == NULL)
				continue;

			chunk->SetAvatarComponent();

			const char *pszName = chunk->GetName();
			if (pszName == NULL)
				continue; 

			DWORD dwFlags = 0;
			if (strnicmp(pszName, "rback.", 5) == 0)
			{
				dwFlags |= eItem_RBack;
			}
			else if (strnicmp(pszName, "lback.", 5) == 0)
			{
				dwFlags |= eItem_LBack;
			}
			else if (strnicmp(pszName, "rh.", 3) == 0)
			{
				dwFlags |= eItem_RightHand;
			}
			else if (strnicmp(pszName, "lh.", 3) == 0)
			{
				dwFlags |= eItem_LeftHand;
			}
			else if (strnicmp(pszName, "ground.", 7) == 0)
			{
				dwFlags |= eItem_Ground;
			}
			else if (strnicmp(pszName, "lshield.", 8) == 0)
			{
				dwFlags |= eItem_Shield;
			}
			else if (strnicmp(pszName, "lbshield.", 9) == 0)
			{
				dwFlags |= eItem_BackShield;
			}
			// billboard
			else if (strnicmp(pszName, "bbrd.rback.", 11) == 0)
			{
				dwFlags |= eItem_RBack;
			}
			else if (strnicmp(pszName, "bbrd.lback.", 11) == 0)
			{
				dwFlags |= eItem_LBack;
			}
			else if (strnicmp(pszName, "bbrd.rh.", 8) == 0)
			{
				dwFlags |= eItem_RightHand;
			}
			else if (strnicmp(pszName, "bbrd.lh.", 8) == 0)
			{
				dwFlags |= eItem_LeftHand;
			}

			component->Chunks.push_back(chunk);
			component->Flags.push_back(dwFlags);
		}
	}

	const char *skin = "Default";
	component->AvatarSetting = mexCfg->m_AvatarSettings.FindByName(skin);
	if (component->AvatarSetting == NULL)
		return;

	component->ReplaceableTextureProj.SetTextureCount(component->AvatarSetting->m_vectorReplaceableTexture.size());
	component->LuminanceTextureProj.SetTextureCount(component->AvatarSetting->m_vectorReplaceableTexture.size());

	for (int i = 0; i < component->AvatarSetting->m_vectorReplaceableTexture.size(); ++i)
	{
		MexCfgAvatarSetting::ReplaceableTexture *replaceableTexture = &component->AvatarSetting->m_vectorReplaceableTexture[i];

		int renderTextureID = -1;
		if ((componentType != Avatar::LeftHand && componentType != Avatar::RightHand)
			|| strncmp(
				replaceableTexture->szFileName,
				INTENSIFY_FILENAME_PREFIX, sizeof(INTENSIFY_FILENAME_PREFIX) / sizeof(char) - 1) != 0)
		{
			renderTextureID = component->ReplaceableTextureProj.RegisterTexture(obj->model->GetMex()->GetFilename(),
				replaceableTexture->szFileName, TRUE);
		}
		component->ReplaceableTextureProj.SetRenderTextureID(i, renderTextureID);

		wxFileName fn(replaceableTexture->szFileName);
		wxString filePath = fn.GetPath();

		wxString luminanceTexFileName;
		if (filePath.IsEmpty())
			luminanceTexFileName = wxString::Format(wxT("%s-lum.png"), fn.GetName());
		else
			luminanceTexFileName = wxString::Format(wxT("%s/%s-lum.png"), fn.GetName());
		
		int nLuminanceTextureID = component->LuminanceTextureProj.RegisterTexture(
			obj->model->GetMex()->GetFilename(), luminanceTexFileName.mb_str(), TRUE);
		component->LuminanceTextureProj.SetRenderTextureID(i, nLuminanceTextureID);
	}

	component->ReplaceableTextureProj.Loaded(TRUE);
	component->LuminanceTextureProj.Loaded(TRUE);
}

void Avatar::Render(MexAnimCtrl *parent)
{
	DWORD time = HQ_TimeGetTime();
	IRenderer *r = mParent->GetRenderer();

	int componentType;
	for (AvatarComponentsIter iter = mComponents.begin(); iter != mComponents.end(); ++iter)
	{
		componentType = iter->first;
		Component *component = iter->second;
		if (component->ModelObject == NULL)
			continue;

		IMexAttachment *att = NULL;
		if (mAttachments.size() > 0 && componentType >= 0 && componentType <= mAttachments.size() - 1)
			att = mAttachments[componentType];

		if (component->IsAttachment && att != NULL)
		{
			/*
			 * 渲染Attachment, 如左右手武器
			 */
			if (component->IsAttachment)
			{
				int nAttachBoneID = att->GetAttachBoneID();
				float *matHelperInit = att->GetInitMatrix();
				component->ModelObject->model->UpdateAsAnimComponent(time, parent, nAttachBoneID, matHelperInit);
			}
			component->ModelObject->Render();
		}
		else
		{
			D3DXMATRIX transformMatrix;
			component->ModelObject->model->CalcTransformMatrix((MeMatrix *) &transformMatrix);
			component->ModelObject->model->Update(HQ_TimeGetTime(), (MeMatrix *) &transformMatrix);	
			component->ModelObject->model->UpdateComponents(HQ_TimeGetTime(), (MeMatrix *) &transformMatrix);

			/*
			 * 渲染其它Avatar组件
			 */
			for (int i = 0; i < component->Chunks.size(); ++i)
			{
				IRenderable* pChunk = component->Chunks[i];
				if (pChunk == NULL)
					continue;

				DWORD dwFlags = component->Flags[i];
				if (dwFlags == eItem_LBack || dwFlags == eItem_LeftHand)
				{
					continue;
				}

				r->SetLayerCount(1);
				DWORD dwFvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
				r->SetSurfaceFVF(dwFvf);
				r->SetVertexStride(GetVertexStride(dwFvf));

				MtlAnim *mtrlAnim = component->MtrlAnims;
				if (mtrlAnim != NULL)
				{
					if (mtrlAnim->m_bHasSpecular)
					{
						r->SetMtlSpecular( 
							mtrlAnim->m_fSpecularPower,
							1.0,
							mtrlAnim->m_fSpecularRed,
							mtrlAnim->m_fSpecularGreen,
							mtrlAnim->m_fSpecularBlue);
						r->EnableSpecular(TRUE);
					}
					if (mtrlAnim->m_nLayerCount == 2)
					{
						r->SetLayerCount(2);
						MtlAnim::SSetting setting;

						mtrlAnim->GetSetting(HQ_TimeGetTime(), &setting);
						r->SetGlobalUOffset(1, setting.fUOffset);
						r->SetGlobalVOffset(1, setting.fVOffset);

						r->SetTextureId(setting.nTextureId, 1);
						dwFvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2;
						r->SetVertexStride(GetVertexStride(dwFvf));
						r->SetSurfaceFVF(dwFvf);
					}
				}
				if (component->SpecularTexID != -1)
				{
					r->SetLayerCount(2);
					r->SetTextureId(component->SpecularTexID, 1);
					dwFvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2;
					r->SetVertexStride(GetVertexStride(dwFvf));
					r->EnableSpecular(TRUE);
				}

				r->SetMaterial(&component->Material);

				RenderParams *params = CRenderParamsMgr::Instance()->RetriveRenderParams();
				if (params != NULL)
				{
					params->pMex = component->ModelObject->model->GetMex();
					params->pMatrices = (float *) parent->GetMatrices();
					params->pReplaceableTextureProj = &component->ReplaceableTextureProj;
					params->fAlpha = 1.0f;//fAlpha;
					params->bMustUseAlphaBlend = false;//bMustUseAlphaBlend;
					if (component->SpecularTexID != -1)
						params->nSpecularTexID = component->SpecularTexID;
					else
						params->nSpecularTexID = -1;//m_SpecularTexID;
					params->material = &component->Material;
					params->nFrameId = parent->GetFrameId();

					int numOfVertex, numOfFace;
					pChunk->Render(params, false, &component->LuminanceTextureProj, &numOfVertex, &numOfFace);
				}
			}
		}
	}
}