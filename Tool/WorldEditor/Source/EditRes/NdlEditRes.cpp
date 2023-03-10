/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlRes.cpp
* Date: 	03/18/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "EditRes/NdlEditRes.h"
#include "Me3d/Utility.h"
#include "MeTerrain/SwRender.h"
#include "tstring.h"
#include "ndl/NdlHelper.h"
#include "ModelConfig.h"
#include "ItemDetailConfig.h"

CNdlLineRes::CNdlLineRes()
{
	m_line = MeNew swChunckLine();
}

CNdlLineRes::~CNdlLineRes()
{
	delete m_line;
	m_line = 0;
}

void CNdlLineRes::Render()
{
	IRenderer* r = GetEngine()->GetRenderer();
	r->DirectPushSurface(
		-1,				
		-1,				
		-1,
		D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
		sizeof( swChunckLineVertex ),
		(BYTE*)(&m_line->kVertex),
		2*WORLD_TILE_CHUNK_UNIT_NUM+1,
		0,
		8,eLightingDisable, D3DPT_LINELIST );
}

void CNdlLineRes::setColor( DWORD color )
{
	for(int i=0;i<2*WORLD_TILE_CHUNK_UNIT_NUM+1;++i)
	{
		m_line->kVertex[i].color = color;
	}
}
////////////////////////////////////////////////////////////////////////////////
CMeshLineRes::CMeshLineRes()
{
	m_nSize = 0;
	memset(m_pVertex , 0, MESH_SIZE * sizeof(D3DXVECTOR3 ));
}

CMeshLineRes::~CMeshLineRes()
{

}

void CMeshLineRes::Clean()
{
	m_nSize = 0;
	memset(m_pVertex , 0, MESH_SIZE * sizeof(D3DXVECTOR3 ));
}

void CMeshLineRes::Render()
{
	IRenderer* r = GetEngine()->GetRenderer();
	r->DirectPushSurface(
		-1,				
		-1,				
		-1,
		D3DFVF_XYZ,
		sizeof( D3DXVECTOR3 ),
		(BYTE*)(m_pVertex),
		m_nSize,
		0,
		m_nSize / 2, eLightingDisable, D3DPT_LINELIST);
}

//--------------------------------------------------------------------

CTransportEditRes::CTransportEditRes()
{
	m_model = NULL;
}

CTransportEditRes::~CTransportEditRes()
{
	DetachModel();	
}



void CTransportEditRes::AttachModel()
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	helper->AttachHelper((TObjectEditInfo*)GetModel());
	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,GetPosX(), GetPosY(),0,&bInFloor);

	if (GetModel() != NULL)
	{
		GetModel()->model->SetPosition( GetPosX(), GetPosY(), height	);
		ApplyTransform();
	}
	view->UpdateRoot();

}

void CTransportEditRes::DetachModel()
{
	if (m_model != NULL)
	{
		if (NULL == CWorldEditDoc::GetActiveMapDoc())
		{
			return;
		}
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->DetachHelper((TObjectEditInfo*)m_model);
		SAFE_DELETE(m_model);
		view->UpdateRoot();
	}
}

void CTargetEditRes::AttachModel()
{	

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	helper->AttachHelper((TObjectEditInfo*)GetModel());
	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,GetPosX(), GetPosY(),0,&bInFloor); 
	GetModel()->model->SetPosition( GetPosX(), GetPosY(), height	);
	ApplyTransform();
	view->UpdateRoot();

}

void CTargetEditRes::DetachModel()
{
	if (m_model != NULL)
	{
		if (NULL == CWorldEditDoc::GetActiveMapDoc())
		{
			return;
		}
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->DetachHelper((TObjectEditInfo*)m_model);
		SAFE_DELETE(m_model);
		view->UpdateRoot();
	}
}


void CTransportEditRes::ApplyTransform()
{
// 	NiMatrix3 matRot = NiMatrix3::IDENTITY;
// 	NiMatrix3 matScl = NiMatrix3::IDENTITY;
// 	float scale = Sqrt((m_fRight - m_fLeft)*(m_fTop - m_fBottom));
// 	matScl.SetRow( 0, (m_fRight - m_fLeft)/scale, 0.0f, 0.0f );
// 	matScl.SetRow( 1, 0.0f, (m_fTop - m_fBottom)/scale, 0.0f );
// 	matScl.SetRow( 2, 0.0f, 0.0f,  (m_fRight - m_fLeft + m_fTop - m_fBottom)/(2.f*scale ));

	//to do,jiayi
	// 	NiMatrix3 matTrans = matRot * matScl;
	// 	GetModel()->SetRotate( matTrans );
	m_model->model->SetScaleXYZ( (m_fRight - m_fLeft)/2, (m_fTop - m_fBottom)/2, (m_fRight - m_fLeft + m_fTop - m_fBottom)/3.f);

	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,GetPosX(), GetPosY(),0,&bInFloor); 
// 	flt32 height; 
// 	SwGlobal::GetWorldPicker()->GetHeight(GetPosX(), GetPosY(), height);
	GetModel()->model->SetPosition( GetPosX(), GetPosY(), height );
	GetModel()->Update(0.0f);	

}

TObjectInfo* CTransportEditRes::GetModel()
{
	if (m_model == NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		m_model = (TObjectInfo*)(helper->GetHelper(HT_Transport)->pObject->Clone());
		if(!m_model)
		{
			SAFE_DELETE(m_model);
			return 0;
		}
		((TObjectEditInfo*)m_model)->ApplyTransform();
	}
	return m_model;
}

TObjectInfo* CTargetEditRes::GetModel()
{
	if (m_model == NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		m_model = (TObjectInfo*)(helper->GetHelper(HT_Target)->pObject->Clone());
		if(!m_model)
		{
			SAFE_DELETE(m_model);
			return 0;
		}
		((TObjectEditInfo*)m_model)->ApplyTransform();
	}
	return m_model;
}

void CTargetEditRes::ApplyTransform()
{
// 	NiMatrix3 matRot = NiMatrix3::IDENTITY;
// 	matRot.FromEulerAnglesXYZ(0.f,0.f,m_fTargetDir);
// 	NiMatrix3 matScl = NiMatrix3::IDENTITY;

	//to do jiayi,rotate
	GetModel()->model->SetRotationZ(m_fTargetDir);
	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,GetPosX(), GetPosY(),0,&bInFloor); 
// 	flt32 height; 
// 	SwGlobal::GetWorldPicker()->GetHeight(GetPosX(), GetPosY(), height);
	GetModel()->model->SetPosition( GetPosX(), GetPosY(), height );
	GetModel()->Update(0.0f);	
}



CRouteRes::CRouteRes( )
{
}

// CFlyRouteRes::CFlyRouteRes()
// {
// }

CRouteRes::~CRouteRes()
{
	ClearRoutePoint();
	ClearModel();
}



void CRouteRes::ApplyTransform(int index)
{
	if (index >= m_RoutePointModelList.size())
	{
		return;
	}
	if (index >= m_RoutePointList.size())
	{
		return;
	}
	Vector* pVec = m_RoutePointList[index];
	TObjectEditInfo* info = m_RoutePointModelList[index];
	info->model->SetPosition( pVec->x, pVec->y, pVec->z);
	info->Update(0.0f);	

}

bool CRouteRes::CreatePoint(float x_, float y_, float z_, Vector* &_point)
{
	_point = MeNew Vector(x_, y_, z_);
	return true;
}

bool CRouteRes::PushPoint(int index_, Vector *pPoint_, bool bShow_)
{
	TObjectEditInfo* node = RetrievePointModel();
	node->model->SetPosition(pPoint_->x, pPoint_->y, pPoint_->z);
	node->Update(0.f);
	m_RoutePointModelList.insert(m_RoutePointModelList.begin() + index_, node);
	m_RoutePointList.insert(m_RoutePointList.begin() + index_, pPoint_);

	if(bShow_)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->AttachHelper(node);
	}

	return true;
}

bool CRouteRes::PopPoint(int index_)
{
	if(index_ < 0 || index_ >= GetPointCount())
		return false;

	m_RoutePointList.erase(m_RoutePointList.begin() + index_);
	TObjectEditInfo *pModel = m_RoutePointModelList[index_];
	if(pModel != NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->DetachHelper(pModel);
		SAFE_DELETE(pModel);
	}
	m_RoutePointModelList.erase(m_RoutePointModelList.begin() + index_);

	return true;
}

bool CRouteRes::GetPoint(int index_, Vector* &_pPoint)
{
	if(index_ < 0 || index_ >= GetPointCount())
		return false;

	_pPoint = m_RoutePointList[index_];
	return true;
}

void CRouteRes::AddRoutePoint( float x,float y ,float z ,bool bShow)
{
	Vector* point = MeNew Vector(x,y,z);
	m_RoutePointList.push_back(point);
	if (bShow)
	{
		TObjectEditInfo* node = RetrievePointModel();
		node->model->SetPosition( point->x, point->y, point->z);
		node->Update(0.f);
		m_RoutePointModelList.push_back(node);
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->AttachHelper(node);
	}
}

void CRouteRes::ClearRoutePoint()
{
	for (int i = 0; i < m_RoutePointList.size();++i)
	{
		delete m_RoutePointList[i];
	}
	m_RoutePointList.clear();
}

void CRouteRes::DetachModel()
{
	if (NULL == CWorldEditDoc::GetActiveMapDoc())
	{
		return;
	}
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	for (int i = 0; i < m_RoutePointModelList.size();++i)
	{
		helper->DetachHelper(m_RoutePointModelList[i]);
		SAFE_DELETE(m_RoutePointModelList[i]);

	}
	view->UpdateRoot();
}

void CRouteRes::ClearModel()
{
	if (NULL == CWorldEditDoc::GetActiveMapDoc())
	{
		return;
	}
	DetachModel();
	for (int i = 0; i < m_RoutePointModelList.size();++i)
	{
		m_RoutePointModelList[i] = NULL;
	}
	m_RoutePointModelList.clear();
}

TObjectEditInfo* CRouteRes::RetrievePointModel()
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	TObjectEditInfo* helperObj = helper->GetHelper(HT_FlyRoute)->pObject;
	TObjectEditInfo* pObjectInfo = (TObjectEditInfo*)helperObj->Clone();
	if(!pObjectInfo)
	{
		SAFE_DELETE(pObjectInfo);
		return 0;
	}
	pObjectInfo->ApplyTransform();
	return pObjectInfo;
}

void CRouteRes::ShowRoutePoint( bool bShow )
{
	if (bShow)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();

		if (m_RoutePointModelList.size() == 0)
		{
			for (int i = 0; i < m_RoutePointList.size();++i)
			{
				Vector* tmp = m_RoutePointList[i];
				TObjectEditInfo* node = RetrievePointModel();
				if (!IsFlyRoute())
				{
					BOOL bInFloor = FALSE;
					tmp->z = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,tmp->x,tmp->y,0,&bInFloor);
				}
				node->model->SetPosition( tmp->x, tmp->y, tmp->z);
				node->Update(0.f);
				m_RoutePointModelList.push_back(node);
			}
		}
		for (int i = 0; i < m_RoutePointModelList.size();++i)
		{
			helper->AttachHelper(m_RoutePointModelList[i]);
		}
	}
	else
	{
		DetachModel();
	}
}

void CRouteRes::SetRoutePoint( int index,float x,float y ,float z )
{
	if (index >= m_RoutePointList.size())
	{
		return;
	}
	Vector* pVec = m_RoutePointList[index];
	pVec->x = x;
	pVec->y = y;
	pVec->z = z;
	ApplyTransform(index);
}

flt32 CRouteRes::GetPosX( int index ) const
{
	Assert(index < m_RoutePointList.size());
	return m_RoutePointList[index]->x;
}

flt32 CRouteRes::GetPosY( int index ) const
{
	Assert(index < m_RoutePointList.size());
	return m_RoutePointList[index]->y;

}

flt32 CRouteRes::GetPosZ( int index ) const
{
	Assert(index < m_RoutePointList.size());
	return m_RoutePointList[index]->z;

}

void CRouteRes::SetPosX( int index,flt32 val )
{
	Assert(index < m_RoutePointList.size());
	SetRoutePoint(index,val,GetPosY(index),GetPosZ(index));
}

void CRouteRes::SetPosY( int index,flt32 val )
{
	Assert(index < m_RoutePointList.size());
	SetRoutePoint(index,GetPosX(index),val,GetPosZ(index));
}

void CRouteRes::SetPosZ( int index,flt32 val )
{
	Assert(index < m_RoutePointList.size());
	SetRoutePoint(index,GetPosX(index),GetPosY(index),val);
}

void CRouteRes::DeleteRoutePoint( int index )
{
	Assert(index < m_RoutePointList.size());
	std::vector<Vector* >::iterator iter = m_RoutePointList.begin();
	iter += index;
	delete (*iter);
	m_RoutePointList.erase(iter);
	DeleteRoutePointModel(index);
}

void CRouteRes::DeleteRoutePointModel( int index )
{
	if (index >= m_RoutePointModelList.size())
	{
		return;
	}
	std::vector<TObjectEditInfo* >::iterator iter = m_RoutePointModelList.begin();
	iter += index;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	helper->DetachHelper((*iter));
	delete (*iter);
	m_RoutePointModelList.erase(iter);
	view->UpdateRoot();

}


CNPCRouteRes::CNPCRouteRes()
{
	m_nNextMapID		= -1;
	m_nNextRouteID		= -1;
	m_bFlyRoute = false;
}

CNPCRouteRes::~CNPCRouteRes()
{
	ClearRoutePoint();
}

float CNPCRouteRes::GetWalkSpeed( int index ) const
{
	Assert(index < m_NpcRoutePointList.size());
	return m_NpcRoutePointList[index]->mWalkSpeed;
}

void CNPCRouteRes::SetWalkSpeed( int index,float val )
{
	Assert(index < m_NpcRoutePointList.size());
	m_NpcRoutePointList[index]->mWalkSpeed = val;
}

float CNPCRouteRes::GetWalkLength( int index ) const
{
	Assert(index < m_NpcRoutePointList.size());
	return m_NpcRoutePointList[index]->mWalkLenght;
}

void CNPCRouteRes::SetWalkLength( int index,float val )
{
	Assert(index < m_NpcRoutePointList.size());
	m_NpcRoutePointList[index]->mWalkLenght = val;
}

sInt32 CNPCRouteRes::GetStayTime( int index ) const
{
	Assert(index < m_NpcRoutePointList.size());
	return m_NpcRoutePointList[index]->mStayTime;
}

void CNPCRouteRes::SetStayTime( int index,sInt32 val )
{
	Assert(index < m_NpcRoutePointList.size());
	m_NpcRoutePointList[index]->mStayTime = val;
}

bool CNPCRouteRes::CreatePoint(float x_, float y_, float z_, SNpcRoutePoint* &_npcPoint, Vector* &_point)
{
	if(!CRouteRes::CreatePoint(x_, y_, z_, _point))
		return false;

	_npcPoint = MeDefaultNew SNpcRoutePoint;
	return true;
}

bool CNPCRouteRes::PushPoint(int index_, SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_)
{
	if(index_ < 0)
		return false;

	if(!CRouteRes::PushPoint(index_, pPoint_, bShow_))
		return false;

	m_NpcRoutePointList.insert(m_NpcRoutePointList.begin() + index_, pNpcPoint_);
	return true;
}

bool CNPCRouteRes::PopPoint(int index_)
{
	if(index_ < 0 || index_ >= GetPointCount())
		return false;

	if(!CRouteRes::PopPoint(index_))
		return false;

	m_NpcRoutePointList.erase(m_NpcRoutePointList.begin() + index_);
	return true;
}

bool CNPCRouteRes::GetPoint(int index_, SNpcRoutePoint* &_pNpcPoint, Vector* &_pPoint)
{
	if(index_ < 0 || index_ >= GetPointCount())
		return false;

	if(!CRouteRes::GetPoint(index_, _pPoint))
		return false;

	_pNpcPoint = m_NpcRoutePointList[index_];
	return true;
}

void CNPCRouteRes::AddRoutePoint( float x,float y ,float z ,bool bShow )
{
	CRouteRes::AddRoutePoint(x,y,z,bShow);
	SNpcRoutePoint* pNpcPoint = MeDefaultNew SNpcRoutePoint;
	m_NpcRoutePointList.push_back(pNpcPoint);
}

bool CNPCRouteRes::GenerateCloseRoute(bool bShow_)
{
	size_t count = m_NpcRoutePointList.size();
	if(count <= 2)
		return false;

	//反方向生成路线
	for(int i = count - 2; i > 0; --i)
	{
		AddRoutePoint(GetPosX(i), GetPosY(i), GetPosZ(i), bShow_);
		m_NpcRoutePointList.back() = m_NpcRoutePointList[i];
	}

	return true;
}

bool CNPCRouteRes::CancelCloseRoute()
{
	size_t count = m_NpcRoutePointList.size();
	if(count <= 4)
		return false;
	
	for(int i = count - 1; i > count/2; --i)
	{
		DeleteRoutePoint(i);
	}

	return true;
}

void CNPCRouteRes::DeleteRoutePoint( int index )
{
	CRouteRes::DeleteRoutePoint(index);
	Assert(index < m_NpcRoutePointList.size());
	std::vector<SNpcRoutePoint* >::iterator iter = m_NpcRoutePointList.begin();
	iter += index;
	delete (*iter);
	m_NpcRoutePointList.erase(iter);
}

void CNPCRouteRes::ClearRoutePoint()
{
	CRouteRes::ClearRoutePoint();
	for (int i = 0; i < m_NpcRoutePointList.size();++i)
	{
		delete m_NpcRoutePointList[i];
	}
	m_NpcRoutePointList.clear();

}

sInt32 CNPCRouteRes::GetStayAction( int index ) const
{
	Assert(index < m_NpcRoutePointList.size());
	return m_NpcRoutePointList[index]->mStayAction;

}

void CNPCRouteRes::SetStayAction( int index,sInt32 val )
{
	Assert(index < m_NpcRoutePointList.size());
	m_NpcRoutePointList[index]->mStayAction = val;
}

sInt32 CNPCRouteRes::GetSceneID(int index)
{
	Assert(index < m_NpcRoutePointList.size());
	return m_NpcRoutePointList[index]->mSceneID;
}

void CNPCRouteRes::SetSceneID(int index, sInt32 val)
{
	Assert(index < m_NpcRoutePointList.size());
	m_NpcRoutePointList[index]->mSceneID = val;
}

void CNPCRouteRes::SetNpcRoutePoint(int index_, const SNpcRoutePoint &npcPoint_)
{
	if(index_ < 0 || index_ >= m_NpcRoutePointList.size())
		return;

	*m_NpcRoutePointList[index_] = npcPoint_;
}

CNPCRouteRes::SNpcRoutePoint *CNPCRouteRes::GetRoutePoint(int index_)
{
	if(index_ < 0 || index_ >= m_NpcRoutePointList.size())
		return NULL;

	return m_NpcRoutePointList[index_];
}

CTargetEditRes::CTargetEditRes(  )
{
	m_model = NULL;
}

CTargetEditRes::CTargetEditRes(bool bRelive)
:CTargetRes(bRelive)
{
}

CTargetEditRes::~CTargetEditRes()
{
	DetachModel();	
}

CMonsterQuadRes::CMonsterQuadRes()
{
	// Zone Info
	{
		memset(m_szZoneName, 0, RES_NAME_LEN);

		m_fLeft = m_fRight = m_fBottom = m_fTop = 0.0f;

		m_nAIStep = 0;
		m_nPKMode = PKMode::PKMode_Normal;
		m_bCanStall = false;
		m_bCanDuel = true;

		memset(m_szEnterScript, 0, RES_NAME_LEN);
		memset(m_szLeaveScript, 0, RES_NAME_LEN);
	}

	// Monster Info
	{
		m_bRandRange = false;

		m_nDir = 0;
		m_nMonsterId = 0;
		m_nNumber = 1;
		m_nRelife = 60000;	// 1分钟
		m_nCountry = 0;

		m_bEnable = true;
		m_bHide = false;

		memset(m_szDeadScript, 0, RES_NAME_LEN);
		memset(m_szAIScript, 0, RES_NAME_LEN);

		m_nAIValue = 0;
		m_nCamp = 1;
		m_nForce = 0;

		m_nPath = -1;

		m_bIsOnePoint = true;
	}

	m_model = NULL;
	mMonsterModel = NULL;
}

CMonsterQuadRes::~CMonsterQuadRes()
{
	SAFE_DELETE(mMonsterModel);
}

void CMonsterQuadRes::Update(float x, float y, float w, float h)
{
	float width, height;
	if (w == 0 && h == 0)
	{
		width = this->GetWidth();
		height = this->GetHeight();
		if (width == 0 || height == 0)
		{
			width = 1;
			height = 1;
		}
	}
	else
	{
		width = w;
		height = h;
	}

	m_fLeft = x - width / 2;
	m_fTop = y + height / 2;

	m_fRight = m_fLeft + width;
	m_fBottom = m_fTop - height;
}

void CMonsterQuadRes::ApplyTransform()
{
	GetModel()->model->SetScaleXYZ(GetWidth()/2, GetHeight()/2, 3.0f);

	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f, GetPosX(), GetPosY(), 0, &bInFloor); 
	GetModel()->model->SetPosition(GetPosX(), GetPosY(), height);
	GetModel()->Update(0.0f);
}

void CMonsterQuadRes::AttachModelToNdlHelper()
{
	CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper *helper = view->GetHelper();
	helper->AttachHelper(GetModel());
	ApplyTransform();
	view->UpdateRoot();
}

void CMonsterQuadRes::DetachModelFromNdlHelper()
{
	if (m_model != NULL)
	{
		CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper *helper = view->GetHelper();
		helper->DetachHelper(m_model);
		SAFE_DELETE(m_model);
		view->UpdateRoot();
	}
}

void CMonsterQuadRes::UpdateMonsterModel()
{
	CItemDetail::SMonster *monster = theItemDetailConfig.GetMonsterById(m_nMonsterId);
	if (monster == NULL)
		return;

	int modelId = monster->iModelID;

	ModelConfig::ModelData *model = theModelConfig.GetModelDataById(modelId);
	if (model == NULL)
		return;

	if (mMonsterModel != NULL)
	{
		SAFE_DELETE(mMonsterModel);
	}

	mMonsterModel = MeNew TObjectEditInfo();
	mMonsterModel->LoadFromFile(model->FilePath.c_str());

	D3DXVECTOR3 scale(GetWidth(), GetHeight(), (GetWidth() + GetHeight()) / 3.f);
	scale /= 20;

	mMonsterModel->model->SetScaleXYZ(scale.x, scale.y, scale.z);
}

void CMonsterQuadRes::RenderMonsterModel()
{
	if (mMonsterModel == NULL || m_nNumber <= 0)
		return;

	BOOL bInFloor = false;
	flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f, GetPosX(), GetPosY(), 0, &bInFloor); 
	mMonsterModel->model->SetPosition(GetPosX(), GetPosY(), height);
	mMonsterModel->model->SetRotationZ(D3DXToRadian(m_nDir));
	mMonsterModel->Update(0.0f);

	mMonsterModel->Render(1.0f);
}

TObjectEditInfo * CMonsterQuadRes::GetModel()
{
	if (m_model == NULL)
	{
		CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper *helper = view->GetHelper();
		m_model = (TObjectEditInfo *) (helper->GetHelper(HT_MonsterQuad)->pObject->Clone());
		if (m_model != NULL)
			m_model->ApplyTransform();
	}
	return m_model;
}

#include "ui/Custom/ReachableMapGenerate.h"

#include "Edit\ToolManager.h"
#include "Edit\ToolVertex.h"

void CMonsterQuadRes::DrawView( float radius )
{
	if ( m_bIsOnePoint == false )
	{
		//如果不是单点刷怪的就没必要显示视野了
		return;
	}
	Vector2 viewSize;
	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(NULL == pView)
		return;

	CToolVertex *pTool = (CToolVertex *)(pView->GetToolManager()->GetTool(TOOL_VERTEX));
	if(pTool != NULL)
	{
		flt32 origin[2] = {GetPosX(), GetPosY()};
		pTool->UpdateBrushShape(origin, radius, radius);
		pTool->Render();
	}
}

CSoundPointEditRes::CSoundPointEditRes()
{
	m_SoundPointPointModel = NULL;
}
CSoundPointEditRes::~CSoundPointEditRes()
{
	DetachModel();

}


TObjectEditInfo* CSoundPointEditRes::RetrievePointModel()
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CNdlHelper* helper = view->GetHelper();
	TObjectEditInfo* helperObj = helper->GetHelper(HT_SoundPoint)->pObject;
	TObjectEditInfo* pObjectInfo = (TObjectEditInfo*)helperObj->Clone();
	if(!pObjectInfo)
	{
		SAFE_DELETE(pObjectInfo);
		return 0;
	}
	pObjectInfo->ApplyTransform();
	return pObjectInfo;

}

void CSoundPointEditRes::ApplyTransform(  )
{
	Vector* pVec = &m_SoundPointPoint;
	TObjectEditInfo* info = m_SoundPointPointModel;
	if (info)
	{
		info->model->SetPosition( pVec->x, pVec->y, pVec->z);
		info->Update(0.0f);	
	}

}

void CSoundPointEditRes::ShowSoundPointPoint( bool bShow )
{
	if (bShow)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();

		if (m_SoundPointPointModel == NULL)
		{
			{
				Vector* tmp = &m_SoundPointPoint;
				m_SoundPointPointModel= RetrievePointModel();
				m_SoundPointPointModel->model->SetPosition( tmp->x, tmp->y, tmp->z);
				m_SoundPointPointModel->Update(0.f);
			}
		}
		{
			helper->AttachHelper(m_SoundPointPointModel);
		}
	}
	else
	{
		DetachModel();
	}
}

void CSoundPointEditRes::DetachModel()
{
	if (NULL == CWorldEditDoc::GetActiveMapDoc())
	{
		return;
	}
	if (m_SoundPointPointModel)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CNdlHelper* helper = view->GetHelper();
		helper->DetachHelper(m_SoundPointPointModel);
		SAFE_DELETE(m_SoundPointPointModel);
		view->UpdateRoot();
	}

}

CNpcRes::CNpcRes()
{
    m_model = NULL;
    pPosModel = NULL;
}

CNpcRes::~CNpcRes()
{
    SAFE_DELETE(m_model);

	SAFE_DELETE(pPosModel);
}

void CNpcRes::AttachModel()
{
    CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    CNdlHelper* helper = view->GetHelper();

    if(helper)
    {
        if(m_model == NULL)
        {
            ModelConfig::ModelData *pModelData = theModelConfig.GetModelDataById(m_npc->modelId);
            assert(pModelData != NULL);
            if(!pModelData)
                return;

            if(!LoadModel(pModelData->FilePath.c_str()))
            {
                assert(1);
                return;
            }
        }

        helper->AttachHelper(m_model);

        BOOL bInFloor = false;
        flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,m_npc->x, m_npc->y,0,&bInFloor); 
        height += 0.2f;
        m_npc->z = height;
        m_model->model->SetPosition( m_npc->x, m_npc->y, height);
        m_model->model->SetScale(m_npc->bodyScale * GetMe3dConfig()->m_fMdlSpaceScale);

        m_model->model->SetRotationZ(float(m_npc->direction + 90) * PI/180.0f);
        m_model->Update(0.f);
    }
}

void CNpcRes::DetachModel()
{
    CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    CNdlHelper* helper = view->GetHelper();

    if(helper)
    {
        helper->DetachHelper(m_model);
        SAFE_DELETE(m_model);
    }
}


bool CNpcRes::LoadModel(const char* pszFileName)
{
    assert(pszFileName != NULL);
    if(pszFileName == NULL)
        return false;

    char path[MAX_PATH*2];

#if _MSC_VER >= 1400
    //sprintf_s( path, MAX_PATH*2, "..\\%s", pszFileName ); //modify by yanli 2010-7-9
	sprintf_s( path, MAX_PATH*2, "%s", pszFileName );
#else
    sprintf( path, "%s",  pszFileName );
#endif
    _strlwr(path);
    Trace( "Load doodad file[%s] \n", pszFileName );

    TObjectEditInfo* pkObject = MeNew TObjectEditInfo();
    if ( strstr( path, ".mex" ) )
    {
        if( !pkObject->LoadFromFile( path ) )
        {
            return false;
        }
    }

    if( NULL == pkObject ) {		
        Trace( "Fail to load doodad [%s] \n", pszFileName );
        delete pkObject;
        return false;
    }

    m_model = pkObject;
    return true;
}

flt32 CNpcRes::GetPosX()
{
    return m_npc->x;
}

flt32 CNpcRes::GetPosY()
{
    return m_npc->y;
}

flt32 CNpcRes::GetPosZ()
{
    return m_npc->z;
}

int CNpcRes::GetDirection()
{
    return m_npc->direction;
}

flt32 CNpcRes::GetBodyScale()
{
    return m_npc->bodyScale;
}


void  CNpcRes::SetPosX(flt32 fValue)
{
    m_npc->x = fValue;
    if(m_model)
        m_model->model->SetPosition(m_npc->x,m_npc->y,m_npc->z);
}

void CNpcRes::SetPosY(flt32 fValue)
{
    m_npc->y = fValue;
    if(m_model)
        m_model->model->SetPosition(m_npc->x,m_npc->y,m_npc->z);
}


void CNpcRes::SetPosZ(flt32 fValue)
{
    m_npc->z = fValue;
}


void CNpcRes::SetDirection(int nvalue)
{
    m_npc->direction = nvalue;
    if(m_model)
        m_model->model->SetRotationZ(float(m_npc->direction + 90) * PI/180.0f);
}


void  CNpcRes::SetScale(flt32 fValue)
{
    m_npc->bodyScale = fValue;
    m_model->model->SetScale(m_npc->bodyScale * GetMe3dConfig()->m_fMdlSpaceScale);
}

const char* CNpcRes::GetNpcName()
{
    return m_npc->name.c_str();
}

void  CNpcRes::SetModelId(sInt32 id)
{
    m_npc->modelId = id;
    DestroyPointer();
}

void CNpcRes::SetNpc(NpcInfo::Npc *pNpc)
{
    m_npc = pNpc;
    SetNpcPosition();
}

void CNpcRes::DrawAABB()
{
    GetDrawer()->DrawBox3D( m_model->model->GetWorldBBox(), 0xffffffff );
}

#include "Edit\ToolManager.h"
#include "Edit\ToolVertex.h"

void CNpcRes::DrawView(void)
{
	if(NULL == m_model || NULL == m_npc)
		return;

	if(0 == m_npc->fightData.size())
		return;

	float radius = m_npc->fightData.begin()->view;

	//m_model->pos的信息怎么是无效的呢？？？？
	//GetDrawer()->DrawCircle3D(GetPosX(), GetPosY(), GetPosZ() + 0.1f, m_npc->fightData.begin()->view, 64, 0xffff0000);

	Vector2 viewSize;
	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(NULL == pView)
		return;

	CToolVertex *pTool = (CToolVertex *)(pView->GetToolManager()->GetTool(TOOL_VERTEX));
	if(pTool != NULL)
	{
		flt32 origin[2] = {GetPosX(), GetPosY()};
		pTool->UpdateBrushShape(origin, radius, radius);
		pTool->Render();
	}
}

void  CNpcRes::DrawFindPointer()
{
    if(!pPosition)
        return;

    if(pPosModel == NULL)
    {
        TObjectEditInfo *pObjectInfo = MeNew TObjectEditInfo;
        if(!pObjectInfo->LoadFromFile("Required\\Helper\\monsterPoint.mex"))
        {
            SAFE_DELETE(pObjectInfo);
        }
        pPosModel = pObjectInfo;
    }
    else
    {
        CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
        CNdlHelper* helper = view->GetHelper();

        helper->AttachHelper(pPosModel);
        BOOL bInFloor = false;
        flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,pPosition->x, pPosition->y,0,&bInFloor);

        pPosModel->model->SetPosition( pPosition->x, pPosition->y, height);
        pPosModel->Update(0.0f);
    }
}

void CNpcRes::SetNpcPosition()
{
    assert(m_npc != NULL);
    if(m_npc == NULL)
        return;

     pPosition = thePositionInfo.GetPositionById(m_npc->id);
}

void  CNpcRes::AddFindPointer(flt32 x,flt32 y)
{
    PositionInfo::Position pos;
    pos.id    = m_npc->id;
    pos.name  = m_npc->name;
    pos.mapId = m_npc->mapId;
    pos.x     = m_npc->x;
    pos.y     = m_npc->y;
    thePositionInfo.positions_.insert(make_pair(pos.id,pos));

    SetNpcPosition();
}

void CNpcRes::AddFindPointer(const PositionInfo::Position &position_)
{
	PositionInfo::Position *p = thePositionInfo.GetPositionById(position_.id);
	if(NULL == p)
	{
		thePositionInfo.positions_.insert(make_pair(position_.id, position_));
	}
	else
	{
		*p = position_;
	}

	SetNpcPosition();
}

bool  CNpcRes::DestroyPointer()
{
	if(NULL == pPosModel)
		return false;

    CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    CNdlHelper* helper = view->GetHelper();

    if(helper)
    {
        helper->DetachHelper(pPosModel);
    }

	SAFE_DELETE(pPosModel);

    return false;
}

flt32 CNpcRes::GetMapId()
{
    if(m_npc != NULL)
        return m_npc->mapId;

    return -1;
}

TObjectEditInfo* CNpcRes::GetObjectInfo()
{
    return m_model;
}

bool CNpcRes::UpdateFindPointer(int nType, flt32 x, flt32 y, bool bShow)
{
    assert(pPosition != NULL);
    if(pPosition != NULL)
    {
        pPosition->type = nType;
        pPosition->x    = x;
        pPosition->y    = y;
        pPosition->isShow = bShow;
        return true;
    }
    return false;
}

bool CNpcRes::DelFindPointer()
{
   DestroyPointer();

    PositionInfo::Positions::iterator it = thePositionInfo.positions_.find(m_npc->id);
    if(it != thePositionInfo.positions_.end())
    {
         thePositionInfo.positions_.erase(it);
         pPosition = NULL;
         return true;
    }
    return false;
}

CNdlNpcLineRes::CNdlNpcLineRes()
{
    m_LineSet.clear();
}

CNdlNpcLineRes::~CNdlNpcLineRes()
{
    int nSize = m_LineSet.size();
    for (int i = 0;i < nSize;++i)
    {
        swChunckLine* pChunk = m_LineSet[i];
        SAFE_DELETE(pChunk);
    }
}

void CNdlNpcLineRes::Render()
{
    IRenderer* r = GetEngine()->GetRenderer();
    int nSize = m_LineSet.size();
    for (int i = 0;i < nSize;++i)
    {
        swChunckLine *line = m_LineSet[i];
        r->DirectPushSurface(
            -1,				
            -1,				
            -1,
            D3DFVF_XYZ|D3DFVF_DIFFUSE,
            sizeof( swLineVertex ),
            (BYTE*)(&line->kVertex),
            2 * 15 + 1,
            0,
            15,eLightingDisable, D3DPT_LINELIST );

    }
}

void CNdlNpcLineRes::CreateLine(CWorldTile* pTile)
{
    int nWidth = static_cast<int>(pTile->GetWidth());
    int nHeight = static_cast<int>(pTile->GetDepth());

    const int nDistance = 30;
    for (int w = 0; w < nWidth;w += 30)
    {
        for (int h = 0; h < nWidth;h += 30)
        {
            BOOL bInFloor = false;
            int id = 0;
            swChunckLine *pLine = MeNew swChunckLine;
            for( sInt32 i = 0; i < 30; i += 2 )
            {
                pLine->kVertex[id].p.x		= w + i;	
                pLine->kVertex[id].p.y		= h;
                flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,pLine->kVertex[id].p.x, pLine->kVertex[id].p.y,0,&bInFloor); 
                height += 0.3f;
                pLine->kVertex[id].p.z		= height;
                pLine->kVertex[id].color    = 0x000000ff;
                id++;
            }

            for( sInt32 j = 0; j < 30; j += 2 )
            {
                pLine->kVertex[id].p.x		= w + 30;
                pLine->kVertex[id].p.y		= h + j;
                flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,pLine->kVertex[id].p.x, pLine->kVertex[id].p.y,0,&bInFloor); 
                height += 0.3f;
                pLine->kVertex[id].p.z		= height;
                pLine->kVertex[id].color	= 0x00ff0000;
                id++;
            }
            pLine->kVertex[id].p.x		= w + 30;		
            pLine->kVertex[id].p.y		= h + 30;
            flt32 height = SwGlobal::GetWorldPicker()->GetZByXY(10000.f,pLine->kVertex[id].p.x, pLine->kVertex[id].p.y,0,&bInFloor); 
            height += 0.3f;
            pLine->kVertex[id].p.z		= height;
            pLine->kVertex[id].color    = 0x000000ff;

            m_LineSet.push_back(pLine);
        }
    }
}

