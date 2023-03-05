/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlHelper.cpp
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "NdlHelper.h"
#include "WorldEditorView.h"
#include "Me3d/Engine\RendererDX.h"

////////////////////////////////////////////////////////////////////////////////
CNdlHelper::CNdlHelper()
{
	for( sInt32 i=0; i< HT_COUNT; i++ ) {
		m_helper[i] = NULL;
	}	

	m_aHelperNames[HT_Axis]			= "Required\\Helper\\axis.mex";
	m_aHelperNames[HT_VertLable]	= "Required\\Helper\\vertlabel.mex";
	m_aHelperNames[HT_Plane]		= "Required\\Helper\\horizontal.mex";
	m_aHelperNames[HT_ChunkBox]		= "Required\\Helper\\chunkBox.mex";
	m_aHelperNames[HT_TileBox]		= "Required\\Helper\\tileBox.mex";
	m_aHelperNames[HT_Transport]	= "Required\\Helper\\transport.mex";
	m_aHelperNames[HT_Target]	    = "Required\\Helper\\target.mex";
	m_aHelperNames[HT_FlyRoute]		= "Required\\Helper\\FlyRoute.mex";
	m_aHelperNames[HT_MonsterQuad]  = "Required\\Helper\\monsterQuad.mex";
	m_aHelperNames[HT_MonsterPoint] = "Required\\Helper\\monsterPoint.mex";
	m_aHelperNames[HT_Flag]			= "Required\\Helper\\flag.mex";
	m_aHelperNames[HT_SoundPoint]		= "Required\\Helper\\SoundPoint.mex";
	m_aHelperNames[HT_Flight]		= "Required\\Helper\\flight.mex";
    m_aHelperNames[HT_ModelAxis]    = "Required\\Helper\\jiantou.mex";
}

CNdlHelper::~CNdlHelper()
{
	for( sInt32 i=0; i< HT_COUNT; i++ ) {
		SAFE_DELETE(m_helper[i]);
	}
	for(int i = 0; i < m_attachedHelper.size(); ++ i)
	{
		SAFE_DELETE(m_attachedHelper[i]);			
	}
}

bool CNdlHelper::Create()
{
	if( !LoadAxis() )
		Trace( "Failed to load axis! \n" );

	if( !CreateVertLable() )
		Trace( "Failed to create vert lable! \n" );
	
	if( !LoadChunkBox() )
		Trace( "Failed to load chunk box! \n" );

	if( !LoadTileBox() )
		Trace( "Failed to load tile box! \n" );

	if( !LoadPlane() )
		Trace( "Failed to load plane! \n" );
	
	if( !LoadTransport() )
		Trace( "Failed to load transport box! \n" );

	if( !LoadTarget() )
		Trace( "Failed to load Target model! \n" );

	if( !LoadFlyRoute() )
		Trace( "Failed to load FlyRoute box! \n" );

	if( !LoadMonster() )
		Trace( "Failed to load Monster Quad box! \n" );

	if (!LoadSoundPoint())
		Trace( "Failed to load Sound Point box! \n" );

	if( !LoadFlag() )
		Trace( "Failed to load Flag model! \n" );

    if(!LoadModelAxis())
        Trace("Failed to load Flag model! \n");

	return true;
}
void CNdlHelper::Render(float fAlpha /* = 1.0f */)
{
	CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CEditRender_M *pRender = (CEditRender_M *)g_render;
	for (int i = 0; i < m_attachedHelper.size(); ++i)
	{
		if (m_attachedHelper[i] != NULL)
		{
			if (IsSelectingModel(m_attachedHelper[i]))
			{
				GetMe3dConfig()->SetRenderModelSelected(TRUE);

				if (view->IsUseDynamicLight())
					m_attachedHelper[i]->model->Render(fAlpha - 0.39, NULL);
				else
					m_attachedHelper[i]->Render(fAlpha - 0.39, TRUE);

				GetMe3dConfig()->SetRenderModelSelected(FALSE);
				GetEngine()->GetRenderer()->SetLight(LIGHT_INDEX_TERRAIN, pRender->GetLight());
			}
			else
			{
				m_attachedHelper[i]->Render(fAlpha);
			}
		}
	}

	for (int i = 0; i < HT_COUNT; ++i)
	{
		if (m_helper[i] != NULL)
			m_helper[i]->Render(fAlpha);
	}	
}

void CNdlHelper::Update(float fTime)
{
	for(int i = 0; i < HT_COUNT; ++ i)
	{
		if(m_helper[i])
			m_helper[i]->Update(fTime);
	}
	for(int i = 0; i < m_attachedHelper.size(); ++ i)
	{
		if(m_attachedHelper[i])
			m_attachedHelper[i]->Update(HQ_TimeGetTime()/*fTime*/);
	}
}

HelperObject* CNdlHelper::GetHelper( znHelperType helpType )
{
	return m_helper[helpType];
}

bool CNdlHelper::LoadHelperByType(znHelperType eType)
{
	if( HT_VertLable == eType)
	{
		m_helper[HT_VertLable] = new HelperObject();
		swVertLabel& vertLabel = m_helper[HT_VertLable]->VertLabel;

		vertLabel.kVertex[0].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.0f );
		vertLabel.kVertex[1].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.2f );
		vertLabel.kVertex[2].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.4f );
		vertLabel.kVertex[3].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.6f );
		vertLabel.kVertex[4].p	= D3DXVECTOR3(  0.0f, 0.0f, 1.0f );

		vertLabel.kVertex[0].color = 0xff0000ff;
		vertLabel.kVertex[1].color = 0xff0000ff;
		vertLabel.kVertex[2].color = 0xff0000ff;
		vertLabel.kVertex[3].color = 0xff0000ff;
		vertLabel.kVertex[4].color = 0xff0000ff;
	}

	m_helper[eType]	= new HelperObject();
	TObjectEditInfo* pObj	= MeNew TObjectEditInfo();
	//get full filename
	char file[MAX_PATH*2];
	sprintf_s( file, "%s\\%s", CWorld::GetAppCharDir(), m_aHelperNames[eType] );
	bool bLoad = pObj->LoadFromFile( file );
	if(!bLoad)
	{	
		delete m_helper[eType];
		m_helper[eType] = 0;
		return false;
	}

	m_helper[eType]->pObject = pObj;
	return true;	
}

bool CNdlHelper::LoadAxis()
{
	if(!LoadHelperByType( HT_Axis ))
		return false;	
	return true;	
}

bool CNdlHelper::LoadChunkBox()
{
	if(!LoadHelperByType( HT_ChunkBox ))
		return false;	
	m_helper[HT_ChunkBox]->pObject->model->SetPosition(4.f, -1.f, 0.f);
	m_helper[HT_ChunkBox]->pObject->Update(0.f);
	return true;
}

bool CNdlHelper::LoadTileBox()
{
	if(!LoadHelperByType( HT_TileBox ))
		return false;	
	m_helper[HT_TileBox]->pObject->model->SetPosition(6.f, -1.f, 0.f);
	m_helper[HT_TileBox]->pObject->Update(0.f);
	return true;
}

bool CNdlHelper::LoadPlane()
{
	if(!LoadHelperByType( HT_Plane ))
		return false;	
	return true;
}

bool CNdlHelper::CreateVertLable()
{
	if(!LoadHelperByType( HT_VertLable ))
		return false;	
	return true;
}

bool CNdlHelper::LoadTransport()
{
	if(!LoadHelperByType( HT_Transport ))
		return false;	

	m_helper[HT_Transport]->pObject->model->SetPosition(8.f, -1.f, 0.f);
	m_helper[HT_Transport]->pObject->Update(0.f);

	return true;
}

bool CNdlHelper::LoadFlyRoute()
{
	if(!LoadHelperByType( HT_FlyRoute ))
		return false;	

	m_helper[HT_FlyRoute]->pObject->model->SetPosition(8.f, -1.f, 0.f);
	m_helper[HT_FlyRoute]->pObject->Update(0.f);

	return true;
}

bool CNdlHelper::LoadMonster()
{
	if(!LoadHelperByType( HT_MonsterQuad ))
		return false;	

	if(!LoadHelperByType( HT_MonsterPoint ))
		return false;	

	return true;
}

bool CNdlHelper::LoadTarget()
{
	if(!LoadHelperByType( HT_Target ))
		return false;	
	return true;
}

bool CNdlHelper::LoadFlag()
{
	if(!LoadHelperByType( HT_Flag ))
		return false;	

	m_helper[HT_Flag]->pObject->model->SetPosition(10.f, -1.f, 0.f);
	m_helper[HT_Flag]->pObject->Update(0.f);

	return true;
}

void CNdlHelper::AttachHelper(TObjectEditInfo* pNode)
{
	assert(pNode != NULL);

	std::vector<TObjectEditInfo*>::iterator it = m_attachedHelper.begin();
	for(; it != m_attachedHelper.end(); ++it)
	{
		if( *it == pNode)
		{
			//already in the array
			return;
		}
	}
	m_attachedHelper.push_back( pNode );
}
void CNdlHelper::DetachHelper(TObjectEditInfo* pNode)
{
	assert(pNode != NULL);

	std::vector<TObjectEditInfo*>::iterator it = m_attachedHelper.begin();
	for(; it != m_attachedHelper.end(); ++it)
	{
		if( *it == pNode)
		{
			m_attachedHelper.erase(it);
			return;
		}
	}
}

bool CNdlHelper::LoadSoundPoint()
{
	if(!LoadHelperByType( HT_SoundPoint ))
		return false;	

	m_helper[HT_SoundPoint]->pObject->model->SetPosition(8.f, -1.f, 0.f);
	m_helper[HT_SoundPoint]->pObject->Update(0.f);

	return true;

}

bool CNdlHelper::LoadModelAxis()
{
    if(!LoadHelperByType(HT_ModelAxis))
        return false;

    m_helper[HT_ModelAxis]->pObject->model->SetPosition(8.0f,-1.0f,0.0f);
    m_helper[HT_ModelAxis]->pObject->Update(0.0f);
	return true;
}

void CNdlHelper::PushSelModel(TObjectEditInfo *pModel_)
{
	m_selModels.push_back(pModel_);
}

void CNdlHelper::PopModel(TObjectEditInfo *pModel_)
{
	for(TSelModels::iterator it = m_selModels.begin(); it != m_selModels.end(); ++it)
	{
		if(pModel_ == *it)
		{
			m_selModels.erase(it);
			return;
		}
	}
}

void CNdlHelper::ClearSelModel(void)
{
	m_selModels.clear();
}

bool CNdlHelper::IsSelectingModel(const TObjectEditInfo *pModel)
{
	for(TSelModels::iterator it = m_selModels.begin(); it != m_selModels.end(); ++it)
	{
		if(pModel == *it)
			return true;
	}

	return false;
}
