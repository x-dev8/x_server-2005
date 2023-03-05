#include "stdafx.h"
#include "ToolNpc.h"
#include "WorldEditorView.h"
#include "ndl\NdlHelper.h"
#include "rollback\INpctoolOperation.h"

CToolNpc::CToolNpc(void)
{
	m_eoptMode = optMode_NPC;
	m_transportDlg = NULL;
	m_CurrNpc = NULL;
	m_bShowLine = false;
}

CToolNpc::~CToolNpc(void)
{

}

void CToolNpc::Bind( CDlgNpcEditor* dlg )
{
	m_transportDlg = dlg;
}

void CToolNpc::Reset()
{
	m_CurrNpc = NULL;
	SetOptMode(optMode_NPC);
}


bool CToolNpc::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );
// 	char path[MAX_PATH*2];
// 	sprintf_s( path, "%s\\Required\\Model\\Box.mex", CWorld::GetAppCharDir() );
    
	return true;

}

void CToolNpc::SetActive( bool isActive/* = true */)
{
	CBaseTool::SetActive(isActive);
	CWorldTile* pTile = CURRENTTILE;
	if (NULL == pTile)
	{
		return;
	}
	if (isActive)
	{
		SetOptMode(optMode_NPC);
		GetResMgr()->AttachAllNpc();
	}
	else
	{
		ClearSelectedNpc();

		GetResMgr()->DetachAllNpc();
	}
}

void CToolNpc::SetOptMode( optMode eMode )
{
 	m_eoptMode = eMode;
 	switch (m_eoptMode)
 	{
 	case optMode_NPC:
		{
// 		   m_pmpMonsterQuad.AttachModel();
		}
 		break;
 	case optMode_Pick:
		{
// 		   m_pmpMonsterQuad.DetachModel();
		}
 		break;
 	}
// 	m_pmpMonsterQuad.GetModel()->Update( 0.f );
}

CResEditMgr* CToolNpc::GetResMgr()
{
	return (CResEditMgr*)CURRENTTILE->GetCResMgr();
}

void CToolNpc::Render()
{
	CWorldTile* pTile = CURRENTTILE;
	if (NULL == pTile)
	{
		return;
	}
	if(m_bShowLine)
	{
		std::vector<CNdlNpcLineRes*> set = GetResMgr()->GetNpcLineList();
		for (int i = 0;i < set.size();++i)
		{
			set[i]->Render();
		}
	}

	if(m_CurrNpc)
	{
		m_CurrNpc->DrawAABB();
		m_CurrNpc->DrawFindPointer();

		m_CurrNpc->DrawView();
	}
}


bool CToolNpc::OnLMouseDown( UINT nFlags, CPoint point )
{	
	m_isLDrag	= true;
	m_oldPos	= point; 

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	sInt32 pickId = view->PickWorldTerrain( point,emPT_NPC|emPT_Terrain/*|emPT_FloorObj */);

	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		if( optMode_Pick == m_eoptMode ) 
		{
			if(m_npcPointer.m_PointerMode == NpcPointer::optMode_AddPointer)
			{
				if(m_CurrNpc != NULL)
				{
					int close_id = GetCloseIndex(pickResult,emPT_NPC);
					flt32 pos[3];
					for( sInt32 i=0; i<3; i++ ) 
					{
						pos[i] = pickResult.pickResultInfo[close_id].point[i];
					}

					//m_CurrNpc->AddFindPointer(pos[0],pos[1]);
					DoAddNpcPostion(pos[0],pos[1]);

					m_transportDlg->RefreshNpc(m_CurrNpc);
				}
			}
			else if(m_npcPointer.m_PointerMode == NpcPointer::optMode_None)
			{
				sInt32 objId	= -1;
				CString strPmt;
				strPmt.Format( _T("没有选中物体") );

				for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) {
					if( emPT_NPC == pickResult.pickResultInfo[i].resultType ) {
						objId = i;
						break;
					}
				}
				CResEditMgr* resMgr = GetResMgr();	
				if( NULL == resMgr )
					return false;

				if( -1 != objId ) 
				{
					m_CurrNpc = GetResMgr()->GetNpcRes(pickResult.pickResultInfo[objId].resultId);
					if( NULL != m_CurrNpc ) 
					{
						//m_transportDlg->RefreshNpc(m_CurrNpc);
						strPmt.Format( _T("选中NPC:%s"),m_CurrNpc->GetNpcName());
					}
				}
				else
				{
					if(m_CurrNpc != NULL)
					{
						m_CurrNpc->DestroyPointer();
						m_CurrNpc = NULL;
					}
				}

				theApp.SetPromptText( strPmt );

				SetSelectedNpc();
			}
		}
		else
		{
			int close_id=GetCloseIndex(pickResult,emPT_NPC);
			flt32 pos[3];
			for( sInt32 i=0; i<3; i++ ) 
			{
				pos[i] = pickResult.pickResultInfo[close_id].point[i];
			}

			/*
			CNpcRes* pRes = NULL;
			if (optMode_NPC == m_eoptMode)
			{
				
				pRes = GetResMgr()->AddNpc(pos[0],pos[1],pos[2]);
				if(pRes != NULL)
				{
					m_transportDlg->InsertNewItem(pRes);
			       pRes->AttachModel();
				}
			}

			m_CurrNpc = pRes;
			*/

			if (optMode_NPC == m_eoptMode)
			{
				if(m_CurrNpc != NULL)
				{
					m_CurrNpc->DestroyPointer();
					m_CurrNpc = NULL;
				}

				DoAddNpc(pos[0],pos[1],pos[2]);
			}

			SetSelectedNpc();
		}
	}
	return true;
}

bool CToolNpc::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;
	return true;
}

bool CToolNpc::OnLMouseDblClk( UINT nFlags, CPoint point )
{	return true;

}

bool	CToolNpc::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 
    return true;
}

bool CToolNpc::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	return true;
}

bool  CToolNpc::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	if( m_isRDrag ){	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag ) {
		m_oldPos = point;
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point ,emPT_Terrain|emPT_FloorObj);
		if( -1 != pickId ) 
		{ 
			const TPickResult& pickResult = view->GetPickResult();
// 			int close_id=GetCloseIndex(pickResult,emPT_MonsterQuad);
// 			if( 		 optMode_Pick != m_eoptMode  ) 
// 			{
// 				flt32 pos[3];
// 				for( sInt32 i=0; i<3; i++ ) 
// 				{
// 					pos[i] = pickResult.pickResultInfo[close_id].point[i];
// 				}
// 				if (optMode_AddMonsterQuad == m_eoptMode)
// 				{
// 					ApplyMonsterQuad(pos[1] + 0.5f,pos[0] - 0.5f,pos[0] + 0.5f,pos[1] - 0.5f);
// 				}
// 			}
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolNpc::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (NULL == m_CurrNpc)
	{
		return false;
	}
	if( nChar == VK_DELETE )
	{
		//DeleteModel();  //删除模型
		DoDeleteNpc();
		return true;
	}
	if( optMode_Pick == m_eoptMode ) {
		flt32 delta = 0.1f;
		if(nFlags&MK_CONTROL ) 
		{
			delta	= 0.5f;
		}
		if( nChar == VK_LEFT ) 
		{
			m_CurrNpc->SetPosX(m_CurrNpc->GetPosX() - delta);
		}
		else if( nChar == VK_RIGHT ) 
		{
			m_CurrNpc->SetPosX(m_CurrNpc->GetPosX() + delta);
		}
		else if( nChar == VK_DOWN )
		{
			m_CurrNpc->SetPosY(m_CurrNpc->GetPosY() - delta);
		}
		else if( nChar == VK_UP )
		{
			m_CurrNpc->SetPosY(m_CurrNpc->GetPosY() + delta);
		}
		m_transportDlg->RefreshNpc(m_CurrNpc);
	}

	return true;
}

bool CToolNpc::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	return true;
}


void CToolNpc::DeleteModel()
{
	m_transportDlg->DelItem(m_CurrNpc);
	sInt32 id = m_CurrNpc->GetNpcResId();
    sInt32 mapId = m_CurrNpc->GetMapId();
    if(mapId == -1)
        return;
	m_CurrNpc->DetachModel();
	GetResMgr()->DelNpc(id,mapId);  //删除NPC
    DelNpcPointer();               //删除NPC寻路点
	m_CurrNpc = NULL;
}

void CToolNpc::SetCameraByNpcId(sInt32 npcId)
{
	int nAmount = GetResMgr()->GetNpcListCount();
	for (int i = 0;i < nAmount;++i)
	{
		CNpcRes* pNpcRes = GetResMgr()->GetNpcRes(i);
		if(pNpcRes->GetNpcId() == npcId)
		{
			CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
			
			SwCamera* camera	= view->GetActiveCamera();


			Vector worldPos = pNpcRes->GetObjectInfo()->model->GetPosition();

			//worldPos.x -= 3.0f;
		    worldPos.z += 3.0f;
			camera->SetPos( worldPos );

			
// 			const D3DXVECTOR3 &dir = camera->GetDir();
// 			const Vector &lookAt = worldPos;
// 			Vector eye(lookAt.x - dir.x, lookAt.y - dir.y, lookAt.z - dir.z);
// 			eye += Vector(dir.x, dir.y, dir.z) * (-7.5 * 6);
// 			camera->SetPos(eye);
			
            camera->Update(0.f,0.f);
			theApp.GetWorld()->SetActivePos( worldPos.x, worldPos.y );

			m_CurrNpc = pNpcRes;
		}
	}
}

bool  CToolNpc::UpdateNpcPointer(int nType,float x,float y,bool bShow)
{
	if(m_CurrNpc == NULL)
	{
		MessageBox(NULL,"请选择NPC","Warnning",MB_OK);
		return false;
	}

	return m_CurrNpc->UpdateFindPointer(nType,x,y,bShow);
}

void CToolNpc::DelNpcPointer()
{
	if(m_CurrNpc == NULL)
	{
		MessageBox(NULL,"请选择NPC","Warnning",MB_OK);
		return;
	}

	m_CurrNpc->DelFindPointer();
}

void CToolNpc::SetSelectedNpc(bool bRefreshUI/* = true*/)
{
	if(m_CurrNpc != NULL)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		if(view)
		{
			CNdlHelper* helper = view->GetHelper();
			if(helper)
			{
				helper->ClearSelModel();
				helper->PushSelModel(m_CurrNpc->GetObjectInfo());
			}
		}

		if(bRefreshUI && m_transportDlg)
		{
			m_transportDlg->RefreshNpc(m_CurrNpc);
			m_transportDlg->SetSelectedNpc(m_CurrNpc->GetNpcId());
		}
	}
}

void CToolNpc::ClearSelectedNpc()
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(view)
	{
		CNdlHelper* helper = view->GetHelper();
		if(helper)
		{
			helper->ClearSelModel();
		}
	}
}

void CToolNpc::Redo(void)
{
	m_opManager.Roll();
}

void CToolNpc::Undo(void)
{
	m_opManager.Rollback();
}

bool CToolNpc::CanRedo(void)
{
	return m_opManager.CanRoll();
}
bool CToolNpc::CanUndo(void)
{
	return m_opManager.CanRollback();
}

bool CToolNpc::DoChangeNpcModel(int modelId_)
{
	if(NULL == m_CurrNpc)
		return false;

	NToolNpc::CChangeNpcModel *mydo = new NToolNpc::CChangeNpcModel(this);
	//mydo->SetData(m_CurrNpc, modelId_);
	mydo->SetData(m_CurrNpc->GetNpcId(), modelId_);
	NToolNpc::CChangeNpcModel *undo = new NToolNpc::CChangeNpcModel(this);
	//undo->SetData(m_CurrNpc, m_CurrNpc->GetModelId());
	undo->SetData(m_CurrNpc->GetNpcId(), m_CurrNpc->GetModelId());

	COpertaionPair *op = new COpertaionPair(mydo, undo);

	return m_opManager.Excute(op);
}

bool CToolNpc::ChangeNpcModel(int npcId_, int modelId_)
{
	CNpcRes *pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pRes->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	pNpc->modelId = modelId_;

	pRes->DetachModel(); //取消模型
	pRes->SetModelId(modelId_);  //设置模型ID
	pRes->AttachModel();

	//同步UI-----------------------

	//-----------------------------

	return true;
}

/*
bool CToolNpc::ChangeNpcModel(CNpcRes *_pRes_, int modelId_)
{
	assert(_pRes_ != NULL);
	if(NULL == _pRes_)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(_pRes_->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	pNpc->modelId = modelId_;

	_pRes_->DetachModel(); //取消模型
	_pRes_->SetModelId(modelId_);  //设置模型ID
	_pRes_->AttachModel();

	//同步UI-----------------------

	//-----------------------------

	return true;
}
*/

bool CToolNpc::DoChangeNpcPos(float x_, float y_, float z_, int dir_, float scale_)
{
	if(NULL == m_CurrNpc)
		return false;

	NToolNpc::CChangeNpcPos *mydo = new NToolNpc::CChangeNpcPos(this);
	//mydo->SetData(m_CurrNpc, x_, y_, z_, dir_, scale_);
	mydo->SetData(m_CurrNpc->GetNpcId(), x_, y_, z_, dir_, scale_);
	NToolNpc::CChangeNpcPos *undo = new NToolNpc::CChangeNpcPos(this);
// 	undo->SetData(m_CurrNpc, m_CurrNpc->GetPosX(), m_CurrNpc->GetPosY(), m_CurrNpc->GetPosZ(),
// 		m_CurrNpc->GetDirection(), m_CurrNpc->GetBodyScale());
	undo->SetData(m_CurrNpc->GetNpcId(), m_CurrNpc->GetPosX(), m_CurrNpc->GetPosY(), m_CurrNpc->GetPosZ(),
		m_CurrNpc->GetDirection(), m_CurrNpc->GetBodyScale());

	COpertaionPair *op = new COpertaionPair(mydo, undo);

	return m_opManager.Excute(op);
}

bool CToolNpc::ChangeNpcPos(int npcId_, float x_, float y_, float z_, int dir_, float scale_)
{
	CNpcRes *pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pRes->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	pRes->SetPosX(x_);
	pRes->SetPosY(y_);
	pRes->SetPosZ(z_);
	pRes->SetDirection(dir_);
	pRes->SetScale(scale_);

	pNpc->x = x_;
	pNpc->y = y_;
	pNpc->z = z_;
	pNpc->direction = dir_;
	pNpc->bodyScale = scale_;

	//同步UI-----------------------
	// 	if(m_transportDlg)
	// 	{
	// 		m_transportDlg->RefreshNpcPos(_res_);
	// 	}
	//-----------------------------

	return true;
}

/*
bool CToolNpc::ChangeNpcPos(CNpcRes *_res_, float x_, float y_, float z_, int dir_, float scale_)
{
	assert(_res_ != NULL);
	if(NULL == _res_)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(_res_->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	_res_->SetPosX(x_);
	_res_->SetPosY(y_);
	_res_->SetPosZ(z_);
	_res_->SetDirection(dir_);
	_res_->SetScale(scale_);

	pNpc->x = x_;
	pNpc->y = y_;
	pNpc->z = z_;
	pNpc->direction = dir_;
	pNpc->bodyScale = scale_;

	//同步UI-----------------------
// 	if(m_transportDlg)
// 	{
// 		m_transportDlg->RefreshNpcPos(_res_);
// 	}
	//-----------------------------

	return true;
}
*/

bool CToolNpc::DoDeleteNpc()
{
	if(NULL == m_CurrNpc)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_CurrNpc->GetNpcId());
	if(NULL == pNpc)
		return false;

	PositionInfo::Position *pPosition = thePositionInfo.GetPositionById(pNpc->id);

	NToolNpc::CDeleteNpc *mydo = new NToolNpc::CDeleteNpc(this);
	mydo->SetData(m_CurrNpc->GetNpcId());

	NpcInfo::Npc *pMyNpc = new NpcInfo::Npc;
	*pMyNpc = *pNpc;

	PositionInfo::Position *pMyPos = NULL;
	if(pPosition != NULL)
	{
		pMyPos = new PositionInfo::Position;
		*pMyPos = *pPosition;
	}

	NToolNpc::CAddNpc *undo = new NToolNpc::CAddNpc(this);
	undo->SetData(pMyNpc, pMyPos);
	
	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolNpc::DeleteNpc(/*int resId_, */int npcId_)
{
	CNpcRes *pRes = NULL;
// 	if(resId_ < 0)
// 	{
		pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
//	}
// 	else
// 	{
// 		pRes = GetResMgr()->GetNpcRes(resId_);
// 	}

	assert(pRes != NULL);
	if(NULL == pRes)
		return false; 

	if(pRes == m_CurrNpc)
		m_CurrNpc = NULL;

	sInt32 id = pRes->GetNpcResId();
	sInt32 mapId = pRes->GetMapId();
	if(mapId == -1)
		return false;

	//同步UI-----------------------
	if(m_transportDlg)
	{
		m_transportDlg->DelItem(pRes);
	}
	//-----------------------------

	pRes->DetachModel();
	//删除NPC寻路点
	pRes->DelFindPointer();
	//删除NPC
	GetResMgr()->DelNpc(id,mapId);  

	return true;
}

bool CToolNpc::DoAddNpc(float x_, float y_, float z_)
{
	NpcInfo::Npc *pNpc = new NpcInfo::Npc;
	GetResMgr()->InitNpc(x_, y_, z_, *pNpc);

	NToolNpc::CAddNpc *mydo = new NToolNpc::CAddNpc(this);
	mydo->SetData(pNpc, NULL);

	NToolNpc::CDeleteNpc *undo = new NToolNpc::CDeleteNpc(this);
	undo->SetData(pNpc->id);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolNpc::AddNpc(NpcInfo::Npc *pNpc_, PositionInfo::Position *pPos_)
{
	if(NULL == pNpc_)
		return false;

	theNpcInfo.AddNpc(*pNpc_);

	if(pPos_ != NULL)
	{
		thePositionInfo.InsertPos(*pPos_);
	}

	//CNpcRes *pRes = GetResMgr()->AddNpc(pNpc_);
	NpcInfo::Npc *pRealNpc = theNpcInfo.GetNpcByStaticId(pNpc_->id);
	assert(pRealNpc != NULL);
	CNpcRes *pRes = GetResMgr()->AddNpc(pRealNpc);
	assert(pRes != NULL);
	pRes->AttachModel();

	//同步UI-----------------------
	if(m_transportDlg)
	{
		m_transportDlg->InsertNewItem(pRes);
	}
	//-----------------------------

	return true;
}

bool CToolNpc::DoAddNpcPostion(float x, float y)
{
	if(NULL == m_CurrNpc)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_CurrNpc->GetNpcId());
	if(NULL == pNpc)
		return false;

	PositionInfo::Position *pPosition = thePositionInfo.GetPositionById(pNpc->id);
	if(pPosition != NULL)
		return false;

	PositionInfo::Position pos;
	pos.id    = pNpc->id;
	pos.name  = pNpc->name;
	pos.mapId = pNpc->mapId;
	pos.x     = pNpc->x;
	pos.y     = pNpc->y;

	NToolNpc::CAddNpcPosition *mydo = new NToolNpc::CAddNpcPosition(this);
	mydo->SetData(pNpc->id, pos);
	NToolNpc::CDeleteNpcPosition *undo = new NToolNpc::CDeleteNpcPosition(this);
	undo->SetData(pNpc->id);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolNpc::AddNpcPostion(int npcId_, const PositionInfo::Position &pos_)
{
	CNpcRes *pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pRes->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	pRes->AddFindPointer(pos_);

	return true;
}

bool CToolNpc::DoDeleteNpcPosition()
{
	if(NULL == m_CurrNpc)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_CurrNpc->GetNpcId());
	if(NULL == pNpc)
		return false;

	PositionInfo::Position *pPosition = thePositionInfo.GetPositionById(pNpc->id);
	if(!pPosition)
		return false;

	MessageBox(NULL,"删除成功","Warning",MB_OK);

	NToolNpc::CDeleteNpcPosition *mydo = new NToolNpc::CDeleteNpcPosition(this);
	mydo->SetData(pNpc->id);
	NToolNpc::CAddNpcPosition *undo = new NToolNpc::CAddNpcPosition(this);
	undo->SetData(pNpc->id, *pPosition);


	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolNpc::DeleteNpcPosition(int npcId_)
{
	CNpcRes *pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pRes->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	pRes->DelFindPointer();

	return true;
}

bool CToolNpc::DoChangeNpcPosition(int nType,flt32 x,flt32 y,bool bShow)
{
	if(NULL == m_CurrNpc)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_CurrNpc->GetNpcId());
	if(NULL == pNpc)
		return false;

	PositionInfo::Position *pPosition = thePositionInfo.GetPositionById(pNpc->id);
	if(!pPosition)
		return false;

	PositionInfo::Position pos;
	pos.id    = pNpc->id;
	pos.name  = pNpc->name;
	pos.mapId = pNpc->mapId;
	pos.x     = x;
	pos.y     = y;
	pos.type = nType;
	pos.isShow = bShow;

	NToolNpc::CChangeNpcPosition *mydo = new NToolNpc::CChangeNpcPosition(this);
	mydo->SetData(pNpc->id, pos);
	NToolNpc::CChangeNpcPosition *undo = new NToolNpc::CChangeNpcPosition(this);
	undo->SetData(pNpc->id, *pPosition);

	COpertaionPair *op = new COpertaionPair(mydo, undo);
	return m_opManager.Excute(op);
}

bool CToolNpc::ChangeNpcPosition(int npcId_, const PositionInfo::Position &pos_)
{
	CNpcRes *pRes = GetResMgr()->GetNpcResByNpcId(npcId_);
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(pRes->GetNpcId());
	assert(pNpc != NULL);
	if(NULL == pNpc)
		return false;

	//限制只能改变这几个属性
	pRes->UpdateFindPointer(pos_.type, pos_.x, pos_.y, pos_.isShow);

	return true;
}
