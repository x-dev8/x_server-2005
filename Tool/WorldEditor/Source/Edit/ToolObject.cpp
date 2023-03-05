/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolObject.cpp
* Date: 	03/20/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "ToolObject.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/ToolModel.h"
#include "Me3d/Model/Mex2.h"
#include "ndl/NdlHelper.h"


////////////////////////////////////////////////////////////////////////////////
CToolObject::CToolObject()
{
	m_wndModelDlg	= NULL;
	//m_isPickObj		= false;
	m_isLock		= false;
	//m_selModelId	= RES_INVALID_ID;
	m_isShowPreview	= false;
	m_modelList.clear();
	// 	memset( m_position, 0, 3*sizeof(flt32) );
	// 	memset( m_offset, 0, 3*sizeof(flt32) );
	// 	memset( m_rotate, 0, 3*sizeof(flt32) );

	//m_scale[0] = m_scale[1] = m_scale[2] = 1.0f;

	//m_selObject		= NULL;
	m_selPmpModel	= 0;
	m_lParam		= 1;
	//m_objIndex		= 0;

	//added by zilong.
	//SetRectSelect(true);
	//SetRectSelect(false);
}

CToolObject::~CToolObject()
{
	//m_selModelId	= RES_INVALID_ID;
	for( size_t i=0; i<m_modelList.size(); i++ ) {
		SAFE_DELETE( m_modelList[i] );
	}
	m_modelList.clear();
	m_wndModelDlg	= NULL;
	//m_selObject		= NULL;

	SAFE_DELETE(m_selPmpModel);
}

bool CToolObject::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );

	m_selectingVisitor.SetToolObject(this);
	m_pickingVisitor.SetToolObject(this);
	m_transformingVisitor.SetToolObject(this);

	char file[MAX_PATH*2];
	sprintf_s( file, "%s\\Required\\Model\\Box.mex", CWorld::GetAppCharDir() );

	SAFE_DELETE(m_selPmpModel);
	m_selPmpModel = MeNew TObjectEditInfo();
	if(!m_selPmpModel->LoadFromFile( file ))
		return false;

	if(!m_transformingVisitor.Create())
		return false;

	return true;
}

void CToolObject::Reset()
{
	//m_selObject		= NULL;
	//m_selModelId	= RES_INVALID_ID;
	for( size_t i=0; i<m_modelList.size(); i++ ) {
		SAFE_DELETE( m_modelList[i] );
	}
	m_modelList.clear();

	m_selectingVisitor.Reset();
	m_pickingVisitor.Reset();
	m_transformingVisitor.Reset();
}

void CToolObject::Bind( CToolModel* modelDlg )
{
	m_wndModelDlg = modelDlg;
}

void CToolObject::EnumFile( LPCTSTR strDir, bool isRecursion )
{
	CFileFind ff;
	CString strPath( strDir );
	strPath += _T("\\*.*");
	BOOL bFound = ff.FindFile(strPath);
	if (!bFound) 
		return;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots())
			continue;

		strPath = ff.GetFilePath();
		if (ff.IsDirectory()) {
			if( isRecursion ) {
				EnumFile( strPath, isRecursion );
			}
		}
		else
		{
			strPath.MakeLower();
			int nMexPos = strPath.Find(_T(".mex"));
			if((-1 == nMexPos || (nMexPos != strPath.GetLength() - 4 ))) 
			{
				continue;
			}

			char localName[MAX_PATH*2];
			GetRelativePath(strPath,localName);

			if( RES_INVALID_ID == FindModelName( localName ) ) {
				PushModelName( localName );	 
			}
		}
	}	
}

CNdlStaticModelRes* CToolObject::GetModelFromId( sInt32 modelId )
{
	if( modelId < 0 || modelId > m_modelList.size() )
		return NULL;

	return m_modelList[modelId];
}

bool CToolObject::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag		= true;
	m_oldPos		= point; 

	if(m_pickingVisitor.IsToPaste())
	{
		//插入新的model
		m_pickingVisitor.InsertModels(point);
	}
	else
	{
		int count = 0;
		if(m_transformingVisitor.IsTransformed())
		{
			count = m_transformingVisitor.SelectAxis(point);
		}

		if(0 == count)
		{

			if(0 == m_selectingVisitor.ClickModels(point))
			{
				if(0 == (nFlags & MK_CONTROL))
				{//要加上这个判断条件，因为进行增选减选时，很可能点一下没有点中任何目标。
					//如果没有这个条件，以前选择的就会置空

					if(m_selectingVisitor.CanRectSelect())
					{
						m_selectingVisitor.SetRectSelectStart(point);
					}
				}
			}
			else
			{
				if((nFlags & MK_CONTROL) != 0)
				{//按住ctrl进行增、减选
					m_selectingVisitor.ClickedModels2SelectModels(false);
				}
				else
				{
					//如果鼠标点击所选中的models_A有上一轮被框选的models_B，则认为接下来的动作是针对models_B的，
					//否则是针对models_A的，此时应该吧models_B替换为models_A
					if(!m_selectingVisitor.IsClickedModelsExist())
					{
						m_selectingVisitor.ClickedModels2SelectModels(true);
					}
				}

			}
		}
	}

	/*
	if( m_isPickObj ) 
	{
	//if(m_selObject) //如果已经选择了物体
	if(!m_selectModels.empty())
	{
	m_pickAxis = GetSelectAxis(point);
	if(m_pickAxis != enum_None)
	{
	return true;
	}
	}

	m_pickResult.Reset();
	if( GetMe3dConfig()->m_RenderHelper )	// Pick碰撞模型
	view->PickWorldTerrain( point, emPT_FloorObj | emPT_CollisionObj);
	else
	view->PickWorldTerrain( point, emPT_ObjBBox);
	CalPickResult(view->GetPickResult());

	//emPT_CollisionObj目前移植后未实现
	// 		view->PickWorldTerrain( point, emPT_CollisionObj );
	// 		CalPickResult(view->GetPickResult());

	m_wndModelDlg->UpdatePickedModelList(m_pickResult);

	return SetPickedModelIndex(0);

	}
	else
	{
	if( 0 != (nFlags&MK_CONTROL) ) {
	m_rotate[2] += 10.0f;
	}
	else if( 0 != (nFlags&MK_SHIFT) ){
	m_rotate[2] += 90.0f;
	}
	}

	}
	*/

	return true;
}

bool CToolObject::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;
	//m_pickAxis = enum_None;


	{
		if(m_selectingVisitor.CanRectSelect())
		{
			if(m_selectingVisitor.IsRectSelectStart())
			{
				m_selectingVisitor.SetRectSelectStop(point);

				//计算该矩形框内的model，都设置成被选择的model
				m_selectingVisitor.SelectModels();
			}
		}
	}

	return true;
}

bool CToolObject::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolObject::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_bRightDragMove = false;
	m_oldPos = point; 

	//CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	//view->PickWorld( point );
	//const TPickResult& pickResult = view->GetPickResult();
	//if( pickResult.isCollided ) { 
	//flt32 scale = 1.0f;
	//if( 0 != (nFlags&MK_CONTROL) ) {
	//	m_rotate[2] += 10.0f;
	//}
	//else if( 0 != (nFlags&MK_SHIFT) ){
	//	m_rotate[2] += 90.0f;
	//}
	//}

	return true;
}

bool CToolObject::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	if(!m_bRightDragMove && !m_selectingVisitor.m_selectModels.empty())
	{//弹出菜单
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_model_transform));
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		if(CTransformingVisitor::e_trans_move ==  m_transformingVisitor.m_tranType)
			pPopup->CheckMenuItem( ID_POP_model_move, MF_CHECKED | MF_BYCOMMAND);
		else if(CTransformingVisitor::e_trans_rotate ==  m_transformingVisitor.m_tranType)
			pPopup->CheckMenuItem( ID_POP_model_rotate, MF_CHECKED | MF_BYCOMMAND);
		else if(CTransformingVisitor::e_trans_scale ==  m_transformingVisitor.m_tranType)
			pPopup->CheckMenuItem( ID_POP_model_scale, MF_CHECKED | MF_BYCOMMAND);

		pPopup->TrackPopupMenu( TPM_NONOTIFY | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this->m_wndModelDlg);
	}

	return true;
}

void CToolObject::RefreshUI()
{
	if( NULL != m_wndModelDlg )
		m_wndModelDlg->RefreshInfo();
}

/*
void CToolObject::ApplyTransform(TObjectEditInfo *_pModel, const flt32 *position_)
{
ASSERT(_pModel != NULL);

memcpy(_pModel->pos, position_, sizeof(_pModel->pos));
memcpy(_pModel->offset, m_offset, sizeof(_pModel->offset));
memcpy(_pModel->rotate, m_rotate, sizeof(_pModel->rotate));
memcpy(_pModel->scale, m_scale, sizeof(_pModel->scale));

_pModel->ApplyTransform();
}
*/

bool CToolObject::OnMouseMove( UINT nFlags, CPoint point )
{

	if( m_isRDrag )
	{	
		m_bRightDragMove = true;

		SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
		CPoint delta = point - m_oldPos;

		// move
		CameraAdjust(point, nFlags);
		camera->Update( 0.0f, 0.0f );

		//只有调整相机后才需要更新轴的信息
		m_transformingVisitor.UpdateAxisInfo();

	}
	//else if( m_isLDrag ) 
	else if((nFlags & MK_LBUTTON) != 0)
	{
		//这里有时候这个m_isLDrag不管用，为什么？？
		//m_isLDrag = true;

		if(m_selectingVisitor.m_selectModels.empty())
		{
			m_selectingVisitor.OnMouseMove(nFlags, point);
		}
		else
		{
			//启用model的鼠标拖动功能
			if(m_transformingVisitor.IsTransformed())
			{
				m_transformingVisitor.OnMouseMove(nFlags, point);
			}
		}



		/*
		//if(m_selObject)
		if(!m_selectModels.empty())
		{
		float newValue = Sqrt(float(point.x * point.x + point.y * point.y));
		float oldValue = Sqrt(float(m_oldPos.x * m_oldPos.x + m_oldPos.y * m_oldPos.y));

		float fDelta = (newValue - oldValue)/32.0f;
		if(m_pickAxis == enum_AxisX)
		m_position[enum_AxisX] += fDelta;
		else if(m_pickAxis == enum_AxisY)
		m_position[enum_AxisY] -= fDelta;
		else if(m_pickAxis == enum_AxisZ)
		m_position[enum_AxisZ] -= fDelta;

		RefreshUI();
		UpdateModel();
		}
		*/

		//m_oldPos = point;
	}
	else 
	{
		m_isShowPreview = true;

		if(m_pickingVisitor.IsToPaste())
			m_pickingVisitor.OnMouseMove(nFlags, point);
	}

	m_oldPos = point;

	return true;
}

bool CToolObject::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolObject::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if( nChar == VK_DELETE ) 
	{
		m_selectingVisitor.DeleteModel();
	}
	else if(nChar == VK_ESCAPE)
	{//清空当前鼠标捡起的model
		m_selectingVisitor.Reset();
		m_pickingVisitor.Reset();
		m_transformingVisitor.Reset();
	}
	else if('c' == nChar || 'C' == nChar)
	{//copy
		if((nFlags & MK_CONTROL) != 0)
		{
			if(m_selectingVisitor.m_selectModels.size() > 0)
			{
				//复制当前选择的目标
				m_pickingVisitor.PickModels(m_selectingVisitor.m_selectModels);
			}
		}
	}
	else if('v' == nChar || 'V' == nChar)
	{//paste
		if((nFlags & MK_CONTROL) != 0)
		{
			//清空当前选择的目标
			m_selectingVisitor.Reset();

			//置标志位，使得当前捡起的目标可以显示和粘帖
			m_pickingVisitor.SetPaste();
		}
	}
	else
	{
		if(!m_selectingVisitor.m_selectModels.empty())
			m_transformingVisitor.OnKeyUp(nChar, nRepCnt, nFlags);
		else
			m_pickingVisitor.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	return true;
}

void CToolObject::Render()
{
	m_selectingVisitor.Render();
	m_pickingVisitor.Render();
	if(!m_selectingVisitor.m_selectModels.empty() && !m_pickingVisitor.IsToPaste())
		m_transformingVisitor.Render();

	/*	if( !m_isShowPreview ) {

	//if( m_isPickObj && NULL != m_selPmpModel ) {
	//	m_selPmpModel->Render( 1.f );
	//}
	return;
	}

	if( RES_INVALID_ID == m_selModelId ) 
	return;

	if (!m_isPickObj)
	{
	CNdlStaticModelRes* modelInfo = (CNdlStaticModelRes*	)m_modelList[m_selModelId];
	if( !modelInfo->IsLoad() ) 
	return;

	//NiCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera()->GetNiCamera();
	//g_render->RenderSingleModel( modelInfo->GetNode(), camera,modelInfo->ActorMgr() );
	DWORD curTime	= HQ_TimeGetTime();
	modelInfo->GetModel()->UpdateByParam( curTime );
	modelInfo->GetModel()->UseTexture();
	modelInfo->GetModel()->Render( 0.7f );	// 传入alpha值
	}
	*/
}

void CToolObject::SetModelId( LPCTSTR fullModelName )
{
	m_isShowPreview = false;

	char localName[MAX_PATH*2];
	GetRelativePath(fullModelName, localName);

	sInt32 modelId = FindModelName(localName);
	if( modelId<0 && modelId>=m_modelList.size() ) {
		//m_selModelId = RES_INVALID_ID;	
		return;
	}
	//m_selModelId = modelId;
	CNdlStaticModelRes* modelRes = m_modelList[modelId];
	if( !modelRes->IsLoad() ) {
		if( !modelRes->LoadModel(true) ) {

			Trace( "Unknown model file format!\n" );
		}
	}

	// 	IMex* pMex = modelRes->GetModel()->GetMex();
	// 	if (NULL != pMex->GetGeometry())
	// 	{
	// 		for( int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++ )
	// 		{
	// 			Mex2GeoChunk* pChunk = (Mex2GeoChunk*)pMex->GetGeometry()->GetChunk(nChunk);
	// 
	// 			char lwrName[MAX_PATH] = {0};
	// 			const char* pszName = pChunk->GetName();
	// 			strncpy( lwrName, pszName, MAX_PATH );
	// 			strlwr(lwrName);
	// 			// rcoli也是collision
	// 			if( strstr(lwrName, "rcoli") )
	// 			{
	// 				pChunk->SetCollision();
	// 			}
	//             else if( strstr(lwrName, "rfloor") )
	//             {
	//                 pChunk->SetFloor();
	//             }
	// 		}
	// 	}

	// 仅仅是为了在视图中预览模型.
	if( modelRes->IsLoad() )
	{
		modelRes->GetModel()->SetAni(TRUE);
		m_transformingVisitor.ApplyTransform( modelRes );
	}

	m_isShowPreview = true;
	m_pickingVisitor.PickModel(modelId);
}

sInt32 CToolObject::FindModelName( const char* modelName )
{
	for( size_t i = 0; i < m_modelList.size(); i++ ) {
		CNdlStaticModelRes* p = m_modelList[i];
		if( strcmp( p->GetName(), modelName ) == 0 ) {
			return p->GetId();
		}
	}
	return RES_INVALID_ID;
}

sInt32 CToolObject::PushModelName( const char* modelName )
{
	sInt32 id = FindModelName( modelName );
	if( RES_INVALID_ID != id )
		return id;

	CNdlStaticModelRes* res = MeNew CNdlStaticModelRes();

	res->SetId( m_modelList.size() );
	res->SetName( modelName );
	m_modelList.push_back( res );
	return m_modelList.size()-1;
}

void CToolObject::ShowPmpModel()
{
	/*
	if(m_selectModels.empty())
	return;

	TObjectEditInfo *pSelModel = (TObjectEditInfo *)m_selectModels[0];

	if( NULL != m_selPmpModel ) {
	flt32 scale = 1.0f;
	MexAnimCtrl* model = NULL;
	if( emPT_ObjBBox == m_pickResult.pickResultInfo[m_objIndex].resultType) 
	{
	model = pSelModel->model;
	}
	else
	{
	//Assert(emPT_CollisionObj == m_pickResult.pickResultInfo[m_objIndex].resultType);
	//commented out by jiayi
	//model = &m_selObject->obstacleModel;
	}
	if( model != NULL ) 
	{
	Box* bBox = model->GetWorldBBox();
	Vector l1 = bBox->v[0] - bBox->v[7];
	Vector l2 = bBox->v[0] - bBox->v[2];
	scale = sqrt(l1.length()*l2.length());
	Vector l3 = bBox->v[0] - bBox->v[6];

	scale = sqrt(l3.length()* scale )* 0.5 ;
	}

	m_selPmpModel->model->SetRotationX( pSelModel->rotate[0]*PI/180.0f );
	m_selPmpModel->model->SetRotationY( pSelModel->rotate[1]*PI/180.0f );
	m_selPmpModel->model->SetRotationZ( pSelModel->rotate[2]*PI/180.0f );
	m_selPmpModel->model->SetPosition( pSelModel->pos[0] + pSelModel->offset[0], 
	pSelModel->pos[1] + pSelModel->offset[1], 
	pSelModel->pos[2] + pSelModel->offset[2]);
	m_selPmpModel->model->SetScale( scale );
	//m_selPmpModel->UpdateNodeBound();
	m_selPmpModel->Update(0.0f);
	}
	*/
}

void CToolObject::RefreshUIShow(TObjectEditInfo* objInfo)
{
	m_transformingVisitor.UpdateInfo(objInfo);

	m_wndModelDlg->RefreshInfo();
}

void CToolObject::SyncOffset2WorldPos()
{
	//当且仅当只有一个选择model时才能用坐标面板操作目标
	if(1 == m_selectingVisitor.m_selectModels.size())
	{
		TObjectEditInfo *pModel = m_selectingVisitor.m_selectModels.begin()->pModel;

		pModel->SyncOffset2WorldPos();;
		RefreshUIShow(pModel);
	}
}

void CToolObject::LockHeight(bool bFlag)
{
	/*
	if( !m_isPickObj )
	return;
	if( NULL == m_selObject )
	return;
	if( RES_INVALID_ID == m_selModelId )
	return;
	m_selObject->m_bLockHeight = bFlag;
	*/

	TModels &selModels = m_selectingVisitor.m_selectModels;
	for(TModels::iterator it = selModels.begin(); it != selModels.end(); ++it)
	{
		TObjectEditInfo *pModel = it->pModel;
		pModel->m_bLockHeight = bFlag;
	}
}

bool CToolObject::IsLockHeight()
{
	TModels &selModels = m_selectingVisitor.m_selectModels;

	if(selModels.empty())
		return false;

	TObjectEditInfo *pModel = selModels.begin()->pModel;
	if(NULL == pModel)
		return false;

	return pModel->m_bLockHeight;
}



/*
sInt16  CToolObject::GetSelectAxis(CPoint point)
{
sInt16 nResult = enum_None;

CWorldEditView* view  = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
SwCamera* pCamera = view->GetActiveCamera();
CEditCamera* pEditCamera = dynamic_cast<CEditCamera*>(pCamera);
if(!pEditCamera)
return nResult;

Vector rayPt, rayDir;
pEditCamera->ScreenToWorldRay( Vector2(point.x, point.y), rayPt, rayDir );

float fDist = 9999.0f;

for (int i = 0;i < 3;++i)
{
float fTmp = 0;
if(m_Axis[i]->model->GetWorldBBox()->Intersect(rayPt,rayDir,&fTmp))
{
//             Vector vHit;
//             if(m_Axis[i]->model->IntersectRay(&rayPt,&rayDir,&vHit))
{
//                 Vector l = vHit - rayPt;
if(fDist > fTmp)
{
nResult = i;
fDist = fTmp;
}
}

}
}
return nResult;
}
*/

CToolObject::CSelectingVisitor::CSelectingVisitor()
{
	SetRectSelect(true);
}

CToolObject::CSelectingVisitor::~CSelectingVisitor()
{

}

bool CToolObject::CSelectingVisitor::SetSelectingModelIndex( sInt32 objIndex )
{
	ASSERT(objIndex >= 0 && objIndex < m_pickResult.pickResultCount);

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();	
	if( NULL == resMgr )
		return false;

	CString strPmt;
	if(m_pickResult.pickResultInfo[objIndex].resultId != RES_INVALID_ID &&
		resMgr->FindStaticModelInUsed(m_pickResult.pickResultInfo[objIndex].resultId)) 
	{
		TObjectEditInfo* pModel = (TObjectEditInfo*)m_pickResult.pickResultInfo[objIndex].resultObjInfo;
		//ASSERT(pModel != NULL);

		m_selectModels.clear();
		m_selectModels.push_back(SSelectingModelInfo(pModel, m_pickResult.pickResultInfo[objIndex].resultId));
		CEditRender_M *pRender = (CEditRender_M *)g_render;
		pRender->ClearSelModel();
		pRender->PushSelModel(pModel);

		UpdateInfo(pModel);

		// 		if(pModel != NULL)
		// 		{
		// 			/*
		// 	 		if(m_Axis)
		// 	 		{
		// 	 			Vector pos = GetAxisPos(objInfo->model->GetWorldMin(),objInfo->model->GetWorldMax());
		// 	 			SetModelAxisPos(pos);
		// 	 		}
		// 			*/
		// 
		// 
		// 			m_pToolObject->RefreshUIShow(pModel);
		// 
		// 			/*
		// 			ShowPmpModel();
		// 			CWorldRes* Res	= resMgr->GetStaticModelRefList()[pModel->id];
		// 			strPmt.Format( _T("当前选中物体[%hs]"), Res->GetName() );
		// 			theApp.SetPromptText( strPmt );
		// 			*/
		// 		}

	}
	else 
	{

		/*
		if( NULL != m_selPmpModel ) {
		m_selPmpModel->model->SetPosition( 0.0f, 0.0f, 0.0f );
		m_selPmpModel->Update(0.0f);
		}
		strPmt.Format( _T("没有选中物体") );
		theApp.SetPromptText( strPmt );
		*/

	}
	return true;
}

bool CToolObject::CSelectingVisitor::SetSelectingModel(sInt32 modelID_, bool bSelected)
{
	for(int i=0; i<m_pickResult.pickResultCount; ++i)
	{
		if(modelID_ == m_pickResult.pickResultInfo[i].resultId)
		{
			if(bSelected)
			{
				return PushSelectedModel(SSelectingModelInfo((TObjectEditInfo *)m_pickResult.pickResultInfo[i].resultObjInfo, 
					m_pickResult.pickResultInfo[i].resultId));
			}
			else
			{
				return PopSelectedModel((TObjectEditInfo *)m_pickResult.pickResultInfo[i].resultObjInfo);
			}
		}
	}

	return false;
}

/*
TObjectEditInfo *CToolObject::CSelectingVisitor::SetSelectingModel(sInt32 objIndex)
{
if(objIndex < 0 || objIndex >= MAX_PICK_OBJ_COUNT)
return NULL;

CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();	
if( NULL == resMgr )
return NULL;

TObjectEditInfo* pModel = NULL;
if(m_pickResult.pickResultInfo[objIndex].resultId != RES_INVALID_ID
&& resMgr->FindStaticModelInUsed(m_pickResult.pickResultInfo[objIndex].resultId)) 
{
pModel = (TObjectEditInfo*)m_pickResult.pickResultInfo[objIndex].resultObjInfo;

m_selectModels.clear();
m_selectModels.push_back(SSelectingModelInfo(pModel, m_pickResult.pickResultInfo[objIndex].resultId));
CEditRender_M *pRender = (CEditRender_M *)g_render;
pRender->ClearSelModel();
pRender->PushSelModel(pModel);
}

return pModel;
}
*/

// void CToolObject::CSelectingVisitor::PushModel(TObjectEditInfo *pModel_)
// {
// 	if(IsFull())
// 		return;
// 
// 	m_selectModels.push_back()
// }

bool CToolObject::CSelectingVisitor::PushSelectedModel(const SSelectingModelInfo &info_)
{
	if(IsFull())
		return false;

	for(TModels::iterator it = m_selectModels.begin(); it != m_selectModels.end(); ++it)
	{
		if(info_.pModel == it->pModel)
		{
			ASSERT(info_.id == it->id);

			return true;
		}
	}

	m_selectModels.push_back(info_);
	CEditRender_M *pRender = (CEditRender_M *)g_render;
	if(pRender)
		pRender->PushSelModel(info_.pModel);

	return true;
}

bool CToolObject::CSelectingVisitor::PushSelectedModel(const SSelectingModelInfo &info_, const TPickResultInfo &resultInfo_)
{
	// 	if(IsFull())
	// 		return false;
	// 
	// 	for(TModels::iterator it = m_selectModels.begin(); it != m_selectModels.end(); ++it)
	// 	{
	// 		if(info_.pModel == it->pModel)
	// 		{
	// 			ASSERT(info_.id == it->id);
	// 
	// 			return true;
	// 		}
	// 	}
	// 
	// 	m_selectModels.push_back(info_);
	// 	CEditRender_M *pRender = (CEditRender_M *)g_render;
	// 	if(pRender)
	// 		pRender->PushSelModel(info_.pModel);

	if(!PushSelectedModel(info_))
		return false;

	if(PushPickResult(m_pickResult, resultInfo_))
		return true;

	return false;
}

bool CToolObject::CSelectingVisitor::PopSelectedModel(TObjectEditInfo *pModel_)
{
	for(TModels::iterator it = m_selectModels.begin(); it != m_selectModels.end(); ++it)
	{
		if(pModel_ == it->pModel)
		{
			m_selectModels.erase(it);

			//这块代码不用放到循环外了，因为这里的m_selectModels和render总是保持一致的
			CEditRender_M *pRender = (CEditRender_M *)g_render;
			if(pRender)
				pRender->PopModel(pModel_);

			return true;
		}
	}

	return true;
}

bool CToolObject::CSelectingVisitor::IsFull(void)
{
	if(m_selectModels.size() >= MAX_PICK_OBJ_COUNT || m_pickResult.pickResultCount >= MAX_PICK_OBJ_COUNT)
	{

		CString msg;
		msg.Format(_T("选择的model过多，请重新选择，最多不能超过%d个！"), MAX_PICK_OBJ_COUNT);
		AfxMessageBox(msg);

		return true;
	}

	return false;
}

void CToolObject::CSelectingVisitor::SetRectSelectStart(const CPoint &point_)
{
	Reset();
	m_pickResult.Reset();

	m_bRectSelect |= RectSelect_Start;

	m_selectedArea.left = point_.x;
	m_selectedArea.top = point_.y;

	m_selectedArea.right = m_selectedArea.left;
	m_selectedArea.bottom = m_selectedArea.top;
}

void CToolObject::CSelectingVisitor::SetRectSelectStop(const CPoint &point_)
{
	m_bRectSelect &= ~RectSelect_Start;

	m_selectedArea.right = point_.x;
	m_selectedArea.bottom = point_.y;
}

bool CToolObject::CSelectingVisitor::ReplaceModel(sInt32 objIndex, LPCTSTR modelName)
{
	char localName[MAX_PATH*2];
	m_pToolObject->GetRelativePath(modelName, localName);
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();	
	if( NULL == resMgr )
		return false;

	if( -1 == objIndex 
		|| !resMgr->FindStaticModelInUsed(m_pickResult.pickResultInfo[objIndex].resultId)) 
	{
		return false;
	}
	CWorldRes* oldRes	= resMgr->GetStaticModelRefList()[m_pickResult.pickResultInfo[objIndex].resultObjInfo->id];
	int nnewId = resMgr->PushRefStaticModel( localName );
	CWorldRes* newRes = resMgr->GetStaticModelRefList()[nnewId];
	resMgr->ReplaceModelId(newRes,oldRes);
	for (sInt32 j = 0; j < m_pickResult.pickResultCount; ++j)
	{
		if ( m_pickResult.pickResultInfo[j].resultId != RES_INVALID_ID 
			&& m_pickResult.pickResultInfo[objIndex].resultObjInfo->id == m_pickResult.pickResultInfo[j].resultObjInfo->id)
		{
			//CString strName;
			//strName			= m_pickResult.pickResultInfo[j].resultObjInfo->model->GetName();
			//m_wndModelDlg->RefreshPickedModelName(j,strName);
			CString strName;
			CWorldRes* Res_j	= resMgr->GetStaticModelRefList()[m_pickResult.pickResultInfo[j].resultObjInfo->id];
			strName			= Res_j->GetName();
			m_pToolObject->m_wndModelDlg->RefreshPickedModelName(j,strName);

		}
	}
	CWorldTile* curTile = CURRENTTILE;
	curTile->CreateFloorAndCollision();
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( curTile );
	return true;
}

void CToolObject::CSelectingVisitor::DeleteModel()
{
	/*
	if( !m_isPickObj )
	return;
	if( NULL == m_selObject )
	return;
	if( RES_INVALID_ID == m_selModelId )
	return;

	if( theApp.GetWorldEditor()->DeleteStaticModel( m_selModelId,true ) )
	{
	for (sInt32 j = 0; j < m_pickResult.pickResultCount; ++j)
	{
	if (m_selModelId == m_pickResult.pickResultInfo[j].resultId)
	{
	m_pickResult.pickResultInfo[j].resultId = RES_INVALID_ID;
	m_wndModelDlg->RefreshPickedModelName(j,_T("已删除"));
	}
	}
	m_selModelId	= RES_INVALID_ID;	
	m_selObject     = NULL;
	g_render->SetSelModel( NULL );

	if( NULL != m_selPmpModel ) {
	m_selPmpModel->model->SetPosition( 0.0f, 0.0f, 0.0f );
	m_selPmpModel->Update( 0.0f );
	}
	CString strPmt;
	strPmt.Format( _T("删除成功!") );
	theApp.SetPromptText( strPmt );


	}
	else {
	CString strPmt;
	strPmt.Format( _T("删除失败!") );
	theApp.SetPromptText( strPmt );
	}
	*/

	for(TModels::iterator it = m_selectModels.begin(); it != m_selectModels.end(); ++it)
	{
		TObjectEditInfo *pModel = it->pModel;
		if(pModel)
		{
			if( theApp.GetWorldEditor()->DeleteStaticModel(it->id, true) )
			{
				for(int index = 0; index < m_pickResult.pickResultCount; ++index)
				{
					if(it->id == m_pickResult.pickResultInfo[index].resultId)
					{
						m_pickResult.pickResultInfo[index].resultId = RES_INVALID_ID;
						m_pToolObject->m_wndModelDlg->RefreshPickedModelName(index, _T("已删除"));
					}
				}

				CString strPmt;
				strPmt.Format( _T("删除成功!") );
				theApp.SetPromptText( strPmt );
			}
			else
			{
				CString strPmt;
				strPmt.Format( _T("删除失败!") );
				theApp.SetPromptText( strPmt );
			}

		}
	}

	Reset();
	m_pToolObject->m_wndModelDlg->UpdatePickedModelList(m_pickResult);
	m_pToolObject->RefreshUIShow(NULL);
}

void CToolObject::CSelectingVisitor::Render()
{
	if(CanRectSelect() && IsRectSelectStart())
	{
		if(m_pToolObject->m_isLDrag)
			NHelper::DrawRect(m_selectedArea, RGB(255, 0, 0));

		if(!IsRectSelectStart())
			NHelper::DrawPolygon3D(m_selectPolygon, RGB(0, 0, 255));
	}
}

bool CToolObject::CSelectingVisitor::OnMouseMove( UINT nFlags, CPoint point )
{
	if(CanRectSelect())
	{
		if(IsRectSelectStart())
		{
			m_selectedArea.right = point.x;
			m_selectedArea.bottom = point.y;	
		}
	}

	return true;
}

void CToolObject::CSelectingVisitor::Reset(void)
{
	m_selectModels.clear();
	CEditRender_M *pRender = (CEditRender_M *)g_render;
	if(pRender)
	{
		pRender->ClearSelModel();
	}

	//m_pickResult.Reset();
}

void CToolObject::CSelectingVisitor::CalPickResult(const TPickResult &pickResult )
{
	for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) 
	{
		PushPickResult(m_pickResult, pickResult.pickResultInfo[i]);

		/*
		if( emPT_ObjBBox == pickResult.pickResultInfo[i].resultType 
		|| emPT_CollisionObj == pickResult.pickResultInfo[i].resultType
		|| emPT_FloorObj == pickResult.pickResultInfo[i].resultType
		|| emPT_CameraCollisionObj == pickResult.pickResultInfo[i].resultType ) 
		{
		bool bFind = false;
		for (sInt32 j = 0; j < m_pickResult.pickResultCount; ++j)
		{
		if (m_pickResult.pickResultInfo[j].resultObjInfo == pickResult.pickResultInfo[i].resultObjInfo)
		{
		bFind = true;
		break;
		}
		}
		if (!bFind)
		{
		m_pickResult.pickResultInfo[m_pickResult.pickResultCount] = pickResult.pickResultInfo[i];
		++m_pickResult.pickResultCount;
		}
		}
		*/
	}
}

bool CToolObject::CSelectingVisitor::PushPickResult(TPickResult &_pickResult, const TPickResultInfo &info_)
{
	ASSERT(_pickResult.pickResultCount < MAX_PICK_OBJ_COUNT);

	if( emPT_ObjBBox == info_.resultType 
		|| emPT_CollisionObj == info_.resultType
		|| emPT_FloorObj == info_.resultType
		|| emPT_CameraCollisionObj == info_.resultType ) 
	{
		for (sInt32 j = 0; j < _pickResult.pickResultCount; ++j)
		{
			if (_pickResult.pickResultInfo[j].resultObjInfo == info_.resultObjInfo)
			{
				return true;
			}
		}

		//未找到的话就插入
		_pickResult.pickResultInfo[_pickResult.pickResultCount] = info_;
		++_pickResult.pickResultCount;
	}

	return true;
}

bool CToolObject::CSelectingVisitor::PopPickResult(TPickResult &_pickResult, sInt32 resultId_)
{
	ASSERT(_pickResult.pickResultCount < MAX_PICK_OBJ_COUNT);

	for (sInt32 j = 0; j < _pickResult.pickResultCount; ++j)
	{
		if (_pickResult.pickResultInfo[j].resultId == resultId_)
		{
			_pickResult.pickResultInfo[j].Reset();

			//把后面的item往前移，保证有效item是连续的
			for(sInt32 index = j+1; index < _pickResult.pickResultCount; ++index)
			{
				_pickResult.pickResultInfo[index - 1] = _pickResult.pickResultInfo[index];
			}
			_pickResult.pickResultInfo[_pickResult.pickResultCount - 1].Reset();

			--_pickResult.pickResultCount;
			return true;
		}
	}

	return false;
}

/*
bool CToolObject::CSelectingVisitor::PopPickResult(const TPickResult &_pickResult, const TPickResultInfo &info_)
{

}
*/

void CToolObject::CSelectingVisitor::UpdateInfo(TObjectEditInfo *pModel_)
{
	// 	TObjectEditInfo *pModel = NULL;
	// 	
	// 	if(!m_selectModels.empty())
	// 		pModel = m_selectModels.begin()->pModel;

	//更新位置信息
	m_pToolObject->RefreshUIShow(pModel_);

	//更新坐标轴的位置
	if(pModel_&&pModel_->model)
	{
		// 		flt32 *pos = pModel_->pos;
		// 		m_pToolObject->m_transformingVisitor.SetAxisPos(Vector(pos[0], pos[1], pos[2] + 10));

		Vector vec = m_pToolObject->m_transformingVisitor.GetAxisPos(pModel_->model->GetWorldMin() ,pModel_->model->GetWorldMax());
		m_pToolObject->m_transformingVisitor.SetAxisPos(vec);
	}
}

bool CToolObject::CSelectingVisitor::IsClickedModelsExist(void)
{
	for(TModels::const_iterator it_click = m_clickedModels.begin(); it_click != m_clickedModels.end(); ++it_click)
	{
		for(TModels::const_iterator it_select = m_selectModels.begin(); it_select != m_selectModels.end(); ++it_select)
		{
			if(it_click->pModel == it_select->pModel)
				return true;
		}
	}

	return false;
}

void CToolObject::CSelectingVisitor::ReselectModels(const TModels &models_, const TPickResult &result_)
{
	ASSERT(models_.size() < MAX_PICK_OBJ_COUNT && 
		models_.size() == result_.pickResultCount);

	//复制当前选择结果，用于失败时回滚
	TModels destModels = m_selectModels;
	TPickResult destResult;
	destResult.pickResultCount = m_pickResult.pickResultCount;
	for(int i=0; i < destResult.pickResultCount; ++i)
	{
		destResult.pickResultInfo[i] = m_pickResult.pickResultInfo[i];
	}

	//开始增选或减选
	int index = 0;
	for(TModels::const_iterator it = models_.begin(); it != models_.end(); ++it, ++index)
	{
		ASSERT(it->pModel != NULL);

		TModels::iterator it_select = m_selectModels.begin();
		for(; it_select != m_selectModels.end(); ++it_select)
		{
			if(it->pModel == it_select->pModel)
			{
				break;
			}
		}

		if(it_select != m_selectModels.end())		
		{//如果已经是选中目标，则减选
			PopSelectedModel(it->pModel);

			//删除对应的pickresult信息
			PopPickResult(m_pickResult, it_select->id);

		}
		else
		{//如果不是选中目标，则增选
			if(!PushSelectedModel(*it, result_.pickResultInfo[index]))
			{
				//发生错误，则回滚
				m_selectModels = destModels;
				m_pickResult.Reset();
				m_pickResult.pickResultCount = destResult.pickResultCount;
				for(int i=0; i < destResult.pickResultCount; ++i)
				{
					m_pickResult.pickResultInfo[i] = destResult.pickResultInfo[i];
				}
			}
		}
	}
}

void CToolObject::CSelectingVisitor::ClickedModels2SelectModels(bool bReplace/* = true*/)
{
	ASSERT(m_clickedModels.size() < MAX_PICK_OBJ_COUNT && m_clickResult.pickResultCount < MAX_PICK_OBJ_COUNT);

	int index = 0;
	if(bReplace)
	{
		Reset();
		m_pickResult.Reset();

		for(TModels::const_iterator it = m_clickedModels.begin(); it != m_clickedModels.end(); ++it)
		{
			ASSERT(it->pModel != NULL);

			m_pickResult.pickResultInfo[index] = m_clickResult.pickResultInfo[index];
			++index;
		}

		m_pickResult.pickResultCount = m_clickResult.pickResultCount;
		SetSelectingModelIndex(0);

		m_pToolObject->m_transformingVisitor.ResetAxis();
	}
	else
	{
		ReselectModels(m_clickedModels, m_clickResult);

		if(!m_selectModels.empty())
			UpdateInfo(m_selectModels.begin()->pModel);

	}

	//更新UI界面
	m_pToolObject->m_wndModelDlg->UpdatePickedModelList(m_pickResult);
}

int CToolObject::CSelectingVisitor::ClickModels(const CPoint &point_)
{
	m_clickedModels.clear();
	m_clickResult.Reset();

	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(NULL == pView)
		return m_clickedModels.size();

	if( GetMe3dConfig()->m_RenderHelper )	// Pick碰撞模型
		pView->PickWorldTerrain(point_, emPT_FloorObj | emPT_CollisionObj);
	else
		pView->PickWorldTerrain(point_, emPT_ObjBBox);

	//存放点击结果
	const TPickResult &pickResult = pView->GetPickResult();
	sInt32 i = 0;
	for(; i < pickResult.pickResultCount; i++ ) 
		//for(; i < 1; i++ )	//这里改为只需要一个目标
	{
		if( emPT_ObjBBox == pickResult.pickResultInfo[i].resultType 
			|| emPT_CollisionObj == pickResult.pickResultInfo[i].resultType
			|| emPT_FloorObj == pickResult.pickResultInfo[i].resultType
			|| emPT_CameraCollisionObj == pickResult.pickResultInfo[i].resultType ) 
		{
			m_clickResult.pickResultInfo[i] = pickResult.pickResultInfo[i];

			m_clickedModels.push_back(SSelectingModelInfo((TObjectEditInfo *)m_clickResult.pickResultInfo[i].resultObjInfo, 
				m_clickResult.pickResultInfo[i].resultId));
		}
	}
	m_clickResult.pickResultCount = i;

	return m_clickedModels.size();
}

int CToolObject::CSelectingVisitor::SelectModels(bool bReset_ /*= true*/)
{
	NHelper::TransformRect(m_selectedArea);

	return SelectModels(m_selectedArea, bReset_);
}

int CToolObject::CSelectingVisitor::SelectModels(const RECT &area_, bool bReset_/* = true*/)
{
	if(bReset_)
	{
		//重置选择状态
		Reset();
		m_pickResult.Reset();
	}

	if((area_.right - area_.left) < 2 && (area_.bottom - area_.top) < 2)
	{	//若area_是一个点

		CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		if(NULL == pView)
			return m_selectModels.size();

		if( GetMe3dConfig()->m_RenderHelper )	// Pick碰撞模型
			pView->PickWorldTerrain(CPoint(area_.right, area_.bottom), emPT_FloorObj | emPT_CollisionObj);
		else
			pView->PickWorldTerrain(CPoint(area_.right, area_.bottom), emPT_ObjBBox);
		CalPickResult(pView->GetPickResult());

		if(m_pickResult.pickResultCount > 0)
		{
			SetSelectingModelIndex(0);
		}
	}
	else
	{

		TChunks chunks;
		//选择chunks
		NHelper::SelectChunks(area_, chunks);
		if(0 == chunks.size())
			return m_selectModels.size();

		//开始进行可视化判断
		//选择目标时是根据矩形所对应的可视体，还是根据xy平面区域呢？
		// 	FrustumEx frustum;
		// 	//建立可视体
		// 	if(!BuildFrustum(area_, frustum))
		// 		return _models.size();

		/*
		float minX = 999999.f;
		float maxX = -minX;
		float minY = minX;
		float maxY = -minX;
		{
		Vector pos;
		ScreenToWorld(CPoint(area_.left, area_.top), pos);
		if(minX > pos.x)
		minX = pos.x;
		if(maxX < pos.x)
		maxX = pos.x;
		if(minY > pos.y)
		minY = pos.y;
		if(maxY < pos.y)
		maxY = pos.y;

		ScreenToWorld(CPoint(area_.right, area_.top), pos);
		if(minX > pos.x)
		minX = pos.x;
		if(maxX < pos.x)
		maxX = pos.x;
		if(minY > pos.y)
		minY = pos.y;
		if(maxY < pos.y)
		maxY = pos.y;

		ScreenToWorld(CPoint(area_.left, area_.bottom), pos);
		if(minX > pos.x)
		minX = pos.x;
		if(maxX < pos.x)
		maxX = pos.x;
		if(minY > pos.y)
		minY = pos.y;
		if(maxY < pos.y)
		maxY = pos.y;

		ScreenToWorld(CPoint(area_.right, area_.bottom), pos);
		if(minX > pos.x)
		minX = pos.x;
		if(maxX < pos.x)
		maxX = pos.x;
		if(minY > pos.y)
		minY = pos.y;
		if(maxY < pos.y)
		maxY = pos.y;
		}
		*/
		NHelper::SPolygon polygon;
		{//生成屏幕矩形在世界坐标系中对应的四边形, z = 0
			Vector pos;
			NHelper::ScreenToWorld(CPoint(area_.left, area_.top), pos);
			polygon.push_back(CPoint(pos.x, pos.y));

			NHelper::ScreenToWorld(CPoint(area_.left, area_.bottom), pos);
			polygon.push_back(CPoint(pos.x, pos.y));

			NHelper::ScreenToWorld(CPoint(area_.right, area_.bottom), pos);
			polygon.push_back(CPoint(pos.x, pos.y));

			NHelper::ScreenToWorld(CPoint(area_.right, area_.top), pos);
			polygon.push_back(CPoint(pos.x, pos.y));

			NHelper::CopyPolygon(m_selectPolygon, polygon);
		}

		CEditRender_M *pRender = (CEditRender_M *)g_render;
		CWorldBuffer *pWorldBuffer = theApp.GetWorld()->GetWorldBuffer();	
		if(NULL == pWorldBuffer)
			return NULL;

		CWorldTile *pTile = pWorldBuffer->GetActiveTile();
		if(NULL == pTile)
			return NULL;

		int index = 0;

		for(TChunks::iterator it = chunks.begin(); it != chunks.end(); ++it)
		{
			std::vector<sInt32> modelList = (*it)->GetStaticModelList();
			for( size_t i=0; i<modelList.size(); i++ ) {
				sInt32 id = modelList[i];
				TObjectEditInfo* objInfo = (TObjectEditInfo*)pTile->GetCResMgr()->GetStaticModel( id );
				if(NULL != objInfo) 
				{
					//因为一个model可能跨越多个chunk，所以要先看是否已经插入
					TModels::iterator it = m_selectModels.begin();
					for(; it != m_selectModels.end(); ++it)
					{
						if(objInfo == it->pModel)
							break;
					}
					if(it != m_selectModels.end())
						continue;

					// 可视剪裁
					/*
					{
					Box* pWorldBBox = objInfo->model->GetWorldBBox();
					SBBox kMMBox;	// 记录世界坐标系的最大和最小值
					kMMBox.vecMin = D3DXVECTOR3(10000.f, 10000.f, 10000.f);
					kMMBox.vecMax = D3DXVECTOR3(-10000.f, -10000.f, -10000.f);
					for(int i=0; i<8; i++)
					{
					kMMBox.vecMin.x = min(kMMBox.vecMin.x, pWorldBBox->v[i].x);
					kMMBox.vecMin.y = min(kMMBox.vecMin.y, pWorldBBox->v[i].y);
					kMMBox.vecMin.z = min(kMMBox.vecMin.z, pWorldBBox->v[i].z);
					kMMBox.vecMax.x = max(kMMBox.vecMax.x, pWorldBBox->v[i].x);
					kMMBox.vecMax.y = max(kMMBox.vecMax.y, pWorldBBox->v[i].y);
					kMMBox.vecMax.z = max(kMMBox.vecMax.z, pWorldBBox->v[i].z);
					}
					if( !pRender->IsObjectVisible( kMMBox, frustum) )
					continue;
					}
					*/

					/*				{
					if(objInfo->pos[0] < minX || objInfo->pos[0] > maxX ||
					objInfo->pos[1] < minY || objInfo->pos[1] > maxY)
					continue;
					}			
					*/
					{
						Box* pWorldBBox = objInfo->model->GetWorldBBox();
						SBBox kMMBox;	// 记录世界坐标系的最大和最小值
						kMMBox.vecMin = D3DXVECTOR3(10000.f, 10000.f, 10000.f);
						kMMBox.vecMax = D3DXVECTOR3(-10000.f, -10000.f, -10000.f);
						for(int i=0; i<8; i++)
						{
							kMMBox.vecMin.x = min(kMMBox.vecMin.x, pWorldBBox->v[i].x);
							kMMBox.vecMin.y = min(kMMBox.vecMin.y, pWorldBBox->v[i].y);
							kMMBox.vecMin.z = min(kMMBox.vecMin.z, pWorldBBox->v[i].z);
							kMMBox.vecMax.x = max(kMMBox.vecMax.x, pWorldBBox->v[i].x);
							kMMBox.vecMax.y = max(kMMBox.vecMax.y, pWorldBBox->v[i].y);
							kMMBox.vecMax.z = max(kMMBox.vecMax.z, pWorldBBox->v[i].z);
						}

						//left top
						flt32 point[2] = {kMMBox.vecMin.x, kMMBox.vecMin.y};
						if(!NHelper::IsInPolygon(polygon, CPoint(point[0], point[1])))
							continue;

						//right top
						point[0] = kMMBox.vecMax.x;
						point[1] = kMMBox.vecMin.y;
						if(!NHelper::IsInPolygon(polygon, CPoint(point[0], point[1])))
							continue;

						//left bottom
						point[0] = kMMBox.vecMin.x;
						point[1] = kMMBox.vecMax.y;
						if(!NHelper::IsInPolygon(polygon, CPoint(point[0], point[1])))
							continue;

						//right bottom
						point[0] = kMMBox.vecMax.x;
						point[1] = kMMBox.vecMax.y;
						if(!NHelper::IsInPolygon(polygon, CPoint(point[0], point[1])))
							continue;
					}

					if(IsFull())
					{
						Reset();
						goto ExitPoint;
					}

					m_selectModels.push_back(SSelectingModelInfo(objInfo, id));

					//保存结果用于UI更新
					{
						m_pickResult.pickResultInfo[index].resultType = emPT_ObjBBox;
						m_pickResult.pickResultInfo[index].resultId = id;
						m_pickResult.pickResultInfo[index].resultObjInfo = objInfo;
						++index;
					}
				}
			}
		}

		m_pickResult.pickResultCount = m_selectModels.size();

		//设置render的当前被选择的models
		{
			CEditRender_M *pRender = (CEditRender_M *)g_render;
			pRender->ClearSelModel();
			for(TModels::iterator it = m_selectModels.begin(); it != m_selectModels.end(); ++it)
			{
				pRender->PushSelModel(it->pModel);
			}
		}

		if(m_selectModels.size() > 0)
		{
			UpdateInfo(m_selectModels.begin()->pModel);
		}
	}

ExitPoint:
	//更新UI界面
	m_pToolObject->m_wndModelDlg->UpdatePickedModelList(m_pickResult);

	m_pToolObject->m_transformingVisitor.ResetAxis();

	TRACE("tool object: [SelectModels] m_selectModels.size() = %u \n", m_selectModels.size());
	return m_selectModels.size();
}

CToolObject::CPickingVisitor::CPickingVisitor():
m_bToPaste(false)
{

}

CToolObject::CPickingVisitor::~CPickingVisitor()
{
	Reset();
}

bool CToolObject::CPickingVisitor::PickModels(const TModels &srcModels_)
{
	Reset();

	for(TModels::const_iterator it = srcModels_.begin(); it != srcModels_.end(); ++it)
	{
		TObjectEditInfo *pSrcModel = it->pModel;
		if(pSrcModel != NULL)
		{
			TObjectEditInfo *pModel = (TObjectEditInfo *)pSrcModel->CloneAll();
			ASSERT(pModel != NULL);

			UPickedModelInfo info;
			info.pModel = pModel;
			m_pickedModels.push_back(info);
		}
	}

	m_pickStatus.SetPickFromSelect();

	return true;
}

bool CToolObject::CPickingVisitor::PickModel(sInt32 id_)
{
	m_pToolObject->m_selectingVisitor.Reset();
	Reset();

	UPickedModelInfo info;
	info.id = id_;
	m_pickedModels.push_back(info);

	m_pickStatus.SetPickFromResource();
	return true;
}

bool CToolObject::CPickingVisitor::InsertModels(const CPoint &point_)
{
	if(!m_pickStatus.IsPickFromSelect() && !m_pickStatus.IsPickFromResource())
		return true;

	m_bToPaste = false;

	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	sInt32 pickId = view->PickWorldTerrain( point_, emPT_Terrain );
	if(-1 == pickId)
		return true;

	const TPickResult& pickResult = view->GetPickResult();


	//得到世界坐标
	flt32 pos[3];
	if(!NHelper::ScreenToWorld(point_, pos))
		return false;

	//开始往当前地图中增加模型
	if(m_pickStatus.IsPickFromResource())
	{
		//理论上此时只能选择一个模型，但这里还是按多个模型处理
		for(TPickModels::iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			CNdlStaticModelRes* modelInfo = m_pToolObject->GetModelFromId(it->id);
			if( NULL != modelInfo ) 
			{
				theApp.GetWorldEditor()->PutStaticModel(pos, 
					m_pToolObject->m_transformingVisitor.m_offset, 
					m_pToolObject->m_transformingVisitor.m_rotate, 
					m_pToolObject->m_transformingVisitor.m_scale, 
					modelInfo->GetName());
			}
		}
	}
	else if(m_pickStatus.IsPickFromSelect())
	{
		//这里需要计算一个偏移量，即每个model相对于pos(鼠标所在点)的偏移量
		bool bValid = false;;	//指示偏移量是否有效。
		Vector offset;
		for(TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			TObjectEditInfo *pModel = it->pModel;
			ASSERT(pModel != NULL);

			//计算偏移量
			if(!bValid)
			{
				offset.x = pos[0] - pModel->pos[0];
				offset.y = pos[1] - pModel->pos[1];
				offset.z = pos[2] - pModel->pos[2];

				bValid = true;
			}

			flt32 worldPos[3];
			worldPos[0] = pModel->pos[0] + offset[0];
			worldPos[1] = pModel->pos[1] + offset[1];
			worldPos[2] = pModel->pos[2] + offset[2];
			//theApp.GetWorldEditor()->PutStaticModel(worldPos, m_offset, m_rotate, m_scale, pModel);
			theApp.GetWorldEditor()->PutStaticModel(worldPos, pModel->offset, pModel->rotate, pModel->scale, pModel);
		}
	}

	//以后要加上把当前粘帖到地图上的model设置为被选择的model

	return true;
}

void CToolObject::CPickingVisitor::Render()
{
	if(!IsToPaste())
		return;

	float alpha = 0.7f;
	if(m_pickStatus.IsPickFromSelect())
	{
		for(TPickModels::iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			TObjectEditInfo *pModel = it->pModel;
			if(pModel != NULL)
				pModel->Render(alpha);
		}
	}
	else if(m_pickStatus.IsPickFromResource())
	{
		for(TPickModels::iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			CNdlStaticModelRes* pModel = m_pToolObject->GetModelFromId(it->id);
			if(pModel != NULL)
			{
				if( !pModel->IsLoad() ) 
					continue;

				DWORD curTime	= HQ_TimeGetTime();
				MexAnimCtrl *pMex = pModel->GetModel();
				pMex->UpdateByParam( curTime );
				pMex->UseTexture();
				pMex->Render(alpha);
			}
		}
	}
}

void CToolObject::CPickingVisitor::SetPaste()
{
	m_bToPaste = true;

	//m_pToolObject->m_selectingVisitor.Reset();
}

bool CToolObject::CPickingVisitor::IsToPaste()
{
	return m_bToPaste || m_pickStatus.IsPickFromResource();
}

bool CToolObject::CPickingVisitor::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( nChar == VK_DOWN ) 
	{
		m_pToolObject->m_wndModelDlg->SelectNextModelInModelTree();
	}
	else if( nChar == VK_UP ) 
	{
		m_pToolObject->m_wndModelDlg->SelectPreModelInModelTree();
	}

	return true;
}

bool CToolObject::CPickingVisitor::OnMouseMove( UINT nFlags, CPoint point )
{
	flt32 pos[3];
	if(!NHelper::ScreenToWorld(point, pos))
		return false;

	//更新鼠标位置
	m_pToolObject->m_transformingVisitor.UpdateMousePosition(pos);

	//让当前复制的Model随鼠标移动
	if(m_pickStatus.IsPickFromResource())
	{
		//设置当前位置
		// 		m_position[0] = pos[0];
		// 		m_position[1] = pos[1];
		// 		m_position[2] = pos[2];

		//理论上此时只能选择一个模型，但这里还是按多个模型处理
		for(TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			CNdlStaticModelRes* pModel = m_pToolObject->GetModelFromId(it->id);
			if(pModel != NULL && pModel->IsLoad()) 
			{

				m_pToolObject->m_transformingVisitor.ApplyTransform(pModel);
			}
		}
	}
	else if(m_pickStatus.IsPickFromSelect())
	{
		//设置当前位置
		// 		m_position[0] = pos[0];
		// 		m_position[1] = pos[1];
		// 		m_position[2] = pos[2];

		//这里需要计算一个偏移量，即每个model相对于pos(鼠标所在点)的偏移量
		bool bValid = false;;	//指示偏移量是否有效。
		Vector offset;
		for(TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			TObjectEditInfo *pModel = it->pModel;
			ASSERT(pModel != NULL);

			//计算偏移量
			if(!bValid)
			{
				offset.x = pos[0] - pModel->pos[0];
				offset.y = pos[1] - pModel->pos[1];
				offset.z = pos[2] - pModel->pos[2];

				bValid = true;
			}

			flt32 position[3];
			position[0] = pModel->pos[0] + offset[0];
			position[1] = pModel->pos[1] + offset[1];
			position[2] = pModel->pos[2] + offset[2];
			//ApplyTransform(pModel, position);
			{
				memcpy(pModel->pos, position, sizeof(pModel->pos));
				pModel->ApplyTransform();
			}
		}
	}

	//m_pToolObject->RefreshUIShow()

	return true;
}

void CToolObject::CPickingVisitor::Reset(void)
{
	TRACE("tool object: [FreePickModels] m_pickedModels.size() = %u\n", m_pickedModels.size());

	if(m_pickStatus.IsPickFromSelect())
	{
		for(TPickModels::iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
		{
			TObjectEditInfo *pModel = it->pModel;
			if(pModel != NULL)
			{
				//delete pModel;
				MeDelete pModel;
			}
		}
	}

	m_pickedModels.clear();
	m_pickStatus.SetPickNothing();
	m_bToPaste = false;
}

CToolObject::CTransformingVisitor::CTransformingVisitor():
m_tranType(e_trans_none)
{
	m_Axis[0] = NULL;
	m_Axis[1] = NULL;
	m_Axis[2] = NULL;
	//m_pickAxis = enum_None;

	m_bPickedAxis[0] = false;
	m_bPickedAxis[1] = false;
	m_bPickedAxis[2] = false;

	const int dim = 3;
	fill_n(m_position, dim, 0.0f);
	fill_n(m_offset, dim, 0.0f);
	fill_n(m_rotate, dim, 0.0f);
	fill_n(m_scale, dim, 1.0f);
	fill_n(m_mousePos, dim, 0.0f);
}

CToolObject::CTransformingVisitor::~CTransformingVisitor()
{
	SAFE_DELETE(m_Axis[enum_AxisX]);
	SAFE_DELETE(m_Axis[enum_AxisY]);
	SAFE_DELETE(m_Axis[enum_AxisZ]);
}

void CToolObject::CTransformingVisitor::UpdateAxisInfo()
{
	/*
	if(e_trans_move == m_tranType)
	{
	m_axis2XY[enum_AxisX] = e_axis2XY_x;
	m_axis2XY[enum_AxisY] = e_axis2XY_y;
	m_axis2XY[enum_AxisZ] = e_axis2XY_y;
	}
	else if(e_trans_rotate == m_tranType)
	{
	m_axis2XY[enum_AxisX] = e_axis2XY_y;
	m_axis2XY[enum_AxisY] = e_axis2XY_x;
	m_axis2XY[enum_AxisZ] = e_axis2XY_x;
	}
	else if(e_trans_scale == m_tranType)
	{
	m_axis2XY[enum_AxisX] = e_axis2XY_y;
	m_axis2XY[enum_AxisY] = e_axis2XY_x;
	m_axis2XY[enum_AxisZ] = e_axis2XY_x;
	}
	*/
}

void CToolObject::CTransformingVisitor::UpdateMousePosition(const flt32 *pos_)
{
	ASSERT(pos_ != NULL);

	//memcpy(m_mousePos, pos_, sizeof(m_mousePos));

	memcpy(m_position, pos_, sizeof(m_position));
}

bool CToolObject::CTransformingVisitor::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags)
{
	flt32 delta = 0.1f;
	bool bChanged = false;
	if( 0 != (nFlags&MK_CONTROL) ) {
		delta	= 0.5f;
	}
	if( nChar == VK_LEFT ) {
		m_offset[0] -= delta;
		bChanged = true;
	}
	else if( nChar == VK_RIGHT ) {
		m_offset[0] += delta;
		bChanged = true;
	}
	else if( nChar == VK_DOWN ) {
		m_offset[1] -= delta;
		bChanged = true;
	}
	else if( nChar == VK_UP ) {
		m_offset[1] += delta;
		bChanged = true;
	}
	else if( nChar == VK_NEXT ) {
		m_offset[2] -= delta;
		bChanged = true;
	}
	else if( nChar == VK_PRIOR ) {
		m_offset[2] += delta;
		bChanged = true;
	}
	else if(nChar == VK_OEM_COMMA)	//','
	{//绕z轴顺时针旋转
		if(0 != (nFlags & MK_CONTROL))	//此时按ctrl不起作用？
			m_rotate[2] += 90;
		else
			m_rotate[2] += 10;

		bChanged = true;
	}
	else if(nChar == VK_OEM_PERIOD)	//'.'
	{//绕z轴逆时针旋转
		if(0 != (nFlags & MK_CONTROL))	//此时按ctrl不起作用？
			m_rotate[2] -= 90;
		else
			m_rotate[2] -= 10;

		bChanged = true;
	}

	if(bChanged)
	{
		UpdateModel();
	}

	return true;
}

void CToolObject::CTransformingVisitor::Move(Axis axis_, flt32 offset_)
{
	//m
}

//用camera的角度来判断
bool CToolObject::CTransformingVisitor::OnMouseMove( UINT nFlags, CPoint point)
{
	CPoint deltaPoint = point - m_pToolObject->m_oldPos;

	Vector2 viewSize;
	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(NULL == pView)
		return false;
	pView->GetViewSize( viewSize.x, viewSize.y );
	SwCamera* pCamera	= pView->GetActiveCamera();
	if(NULL == pCamera)
		return false;
	// 	if( viewSize.x < 1 || viewSize.y < 1 )
	// 		return false;	
	// 
	// 		deltaRot.x	= delta.y / viewSize.y * PI;
	// 		deltaRot.y  = 0.f;
	// 		deltaRot.z	= /*-*/delta.x / viewSize.x * PI;
	// 
	// 	const Vector &rot = pCamera->GetRot();
	// 	TRACE(_T("tool object: [OnMouseMove] rotation(%f, %f, %f).\n"), rot.x, rot.y, rot.z);

	// 	static Vector oldWorldPos;
	// 	if(!NHelper::ScreenToWorld(m_pToolObject->m_oldPos, oldWorldPos))
	// 		return false;
	// 
	// 	Vector worldPos;
	// 	if(!NHelper::ScreenToWorld(point, worldPos))
	// 		return false;
	// 
	// 	flt32 distance = (worldPos.x - oldWorldPos.x) * (worldPos.x - oldWorldPos.x) + (worldPos.y - oldWorldPos.y) * (worldPos.y - oldWorldPos.y);

	Vector delta(0.0f, 0.0f, 0.0f);
	if(e_trans_move == m_tranType)
	{
		flt32 xDelta = deltaPoint.x / viewSize.x * 64.0f;
		flt32 yDelta = deltaPoint.y / viewSize.y * 64.0f;	//y轴的正方向由纸面向内

		//有个地方不明白为什么原点用(0.0f, 0.0f, 0.0f)不行
		Vector origin(m_Axis[0]->pos[0], m_Axis[0]->pos[1], m_Axis[0]->pos[2]);
		//Vector origin(0.0f, 0.0f, 0.0f);
		const int len = 1.0f;
		flt32 ori_x, ori_y;

		if(!pCamera->WorldToScreen(origin, &ori_x, &ori_y, viewSize.x, viewSize.y))
			return false;

		flt32 *pField = NULL;

		for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
		{
			if(!m_bPickedAxis[i])
				continue;

			Vector axis = origin;
			flt32 axis_x, axis_y;

			char axisName[2] = {0, 0};

			flt32 *pField = NULL;
			switch(i)
			{
			case enum_AxisX:
				axisName[0] = 'x';
				axis.x += len;
				pField = &delta.x;
				break;
			case enum_AxisY:
				axisName[0] = 'y';
				axis.y += len;
				pField = &delta.y;
				break;
			case enum_AxisZ:
				axisName[0] = 'z';
				axis.z += len;
				pField = &delta.z;
			}

			if(!pCamera->WorldToScreen(axis, &axis_x, &axis_y, viewSize.x, viewSize.y))
				return false;

			axis_x -= ori_x;
			axis_y -= ori_y;

			flt32 dis_axis = sqrt(axis_x * axis_x + axis_y * axis_y);
			flt32 cos_axis = axis_x / dis_axis;
			flt32 sin_axis = axis_y / dis_axis;

			flt32 angle = acos(cos_axis) / PI;	//[0, PI]
			if(cos_axis > 0.0f && sin_axis < 0.0f)
			{//第四象限
				angle = -angle + 2.0f;
			}
			else if(cos_axis < 0.0f && sin_axis > 0.0f)
			{//二
				//angle = PI - angle;
			}
			else if(cos_axis < 0.0f && sin_axis < 0.0f)
			{//三
				angle = 2.0f - angle;
			}


			TRACE(_T("tool object: [OnMouseMove] %s 轴 cos: %f, sin: %f, angle: %f Pi.\n"), 
				axisName, cos_axis, sin_axis, angle);

			*pField += xDelta * cos_axis + yDelta * sin_axis;
		}

		/*
		for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
		{
		if(!m_bPickedAxis[i])
		continue;

		Vector axis(0.0f, 0.0f, 0.0f);
		flt32 axis_x, axis_y;

		flt32 *pField = NULL;
		switch(i)
		{
		case enum_AxisX:
		axis.x = 1.0f;
		pField = &delta.x;
		break;
		case enum_AxisY:
		axis.y = 1.0f;
		pField = &delta.y;
		break;
		case enum_AxisZ:
		axis.z = 1.0f;
		pField = &delta.z;
		}

		if(!pCamera->WorldToScreen(axis, &axis_x, &axis_y, viewSize.x, viewSize.y))
		return false;

		axis_x -= viewSize.x / 2;
		axis_y -= viewSize.y / 2;

		flt32 dis_axis = sqrt(axis_x * axis_x + axis_y * axis_y);
		flt32 cos_axis = axis_x / dis_axis;
		flt32 sin_axis = axis_y / dis_axis;

		*pField += xDelta * cos_axis + yDelta * sin_axis;
		}
		*/

		/*
		for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
		{
		if(!m_bPickedAxis[i])
		continue;

		flt32 *pField = NULL;
		switch(i)
		{
		case enum_AxisX:
		pField = &delta.x;
		break;
		case enum_AxisY:
		pField = &delta.y;
		break;
		case enum_AxisZ:
		pField = &delta.z;
		}

		if(m_bPickedAxis[i])
		{	
		if(e_axis2XY_x == m_axis2XY[i])
		{
		*pField = xDelta;
		}
		else if(e_axis2XY_x_neg == m_axis2XY[i])
		{
		*pField = -xDelta;
		}
		else if(e_axis2XY_y == m_axis2XY[i])
		{
		*pField = yDelta;
		}
		else if(e_axis2XY_y_neg == m_axis2XY[i])
		{
		*pField = -yDelta;
		}
		}
		}
		*/

		/*
		if(m_bPickedAxis[enum_AxisX])
		{
		delta.x = worldPos.x - oldWorldPos.x;
		}
		if(m_bPickedAxis[enum_AxisY])
		{
		delta.y = worldPos.y - worldPos.y;
		}
		if(m_bPickedAxis[enum_AxisZ])
		{
		delta.z = sqrt(distance * distance - delta.x * delta.x - delta.y * delta.y);
		if(worldPos.x - oldWorldPos.x < 0 && worldPos.y - worldPos.y < 0)
		delta.z = -delta.z;
		else
		{
		if(delta.x < 0)
		{
		if(worldPos.y - worldPos.y > -delta.x)
		delta.z = -delta.z;
		}
		else if(delta.y < 0)
		{
		if(worldPos.x - oldWorldPos.x > -delta.y)
		delta.z = -delta.z;
		}
		}
		}
		*/
		m_position[0] += delta.x;
		m_position[1] += delta.y;
		m_position[2] += delta.z;
	}
	else if(e_trans_rotate == m_tranType)
	{
		flt32 xDelta = deltaPoint.x / viewSize.x * 64 * 0.05 / PI * 180;
		flt32 yDelta = deltaPoint.y / viewSize.y * 64 * 0.05 / PI * 180;

		//有个地方不明白为什么原点用(0.0f, 0.0f, 0.0f)不行
		Vector origin(m_Axis[0]->pos[0], m_Axis[0]->pos[1], m_Axis[0]->pos[2]);
		//Vector origin(0.0f, 0.0f, 0.0f);
		const int len = 1.0f;
		flt32 ori_x, ori_y;

		if(!pCamera->WorldToScreen(origin, &ori_x, &ori_y, viewSize.x, viewSize.y))
			return false;

		flt32 *pField = NULL;

		for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
		{
			if(!m_bPickedAxis[i])
				continue;

			Vector axis = origin;
			flt32 axis_x, axis_y;

			char axisName[2] = {0, 0};

			flt32 *pField = NULL;
			switch(i)
			{
			case enum_AxisX:
				axisName[0] = 'x';
				axis.x += len;
				pField = &delta.x;
				break;
			case enum_AxisY:
				axisName[0] = 'y';
				axis.y += len;
				pField = &delta.y;
				break;
			case enum_AxisZ:
				axisName[0] = 'z';
				axis.z += len;
				pField = &delta.z;
			}

			if(!pCamera->WorldToScreen(axis, &axis_x, &axis_y, viewSize.x, viewSize.y))
				return false;

			axis_x -= ori_x;
			axis_y -= ori_y;

			flt32 dis_axis = sqrt(axis_x * axis_x + axis_y * axis_y);
			flt32 cos_axis = axis_x / dis_axis;
			flt32 sin_axis = axis_y / dis_axis;

			flt32 angle = acos(cos_axis) / PI;	//[0, PI]
			if(cos_axis > 0.0f && sin_axis < 0.0f)
			{//第四象限
				angle = -angle + 2.0f;
			}
			else if(cos_axis < 0.0f && sin_axis > 0.0f)
			{//二
				//angle = PI - angle;
			}
			else if(cos_axis < 0.0f && sin_axis < 0.0f)
			{//三
				angle = 2.0f - angle;
			}

			TRACE(_T("tool object: [OnMouseMove] %s 轴 cos: %f, sin: %f, angle: %f Pi.\n"), 
				axisName, cos_axis, sin_axis, angle);

			// 			switch(i)
			// 			{
			// 			case enum_AxisX:
			// 				break;
			// 			case enum_AxisY:
			// 				break;
			// 			case enum_AxisZ:
			// 				swap(cos_axis, sin_axis);
			// 				cos_axis = -cos_axis;
			// 				sin_axis = -sin_axis;
			// 			}


			*pField += xDelta * cos_axis + yDelta * sin_axis;
		}

		const flt32 PIPI = 360.0f;
		m_rotate[0] += delta.x;
		while(m_rotate[0] >= PIPI)
		{
			m_rotate[0] -= PIPI;
		}
		while(m_rotate[0] < 0.0f)
		{
			m_rotate[0] += PIPI;
		}

		m_rotate[1] += delta.y;
		while(m_rotate[1] >= PIPI)
		{
			m_rotate[1] -= PIPI;
		}
		while(m_rotate[1] < 0.0f)
		{
			m_rotate[1] += PIPI;
		}

		m_rotate[2] += delta.z;
		while(m_rotate[2] >= PIPI)
		{
			m_rotate[2] -= PIPI;
		}
		while(m_rotate[2] < 0.0f)
		{
			m_rotate[2] += PIPI;
		}
	}
	else if(e_trans_scale)
	{
		flt32 xDelta = deltaPoint.x / viewSize.x * 64 * 0.02;
		flt32 yDelta = deltaPoint.y / viewSize.y * 64 * 0.02;

		//有个地方不明白为什么原点用(0.0f, 0.0f, 0.0f)不行
		Vector origin(m_Axis[0]->pos[0], m_Axis[0]->pos[1], m_Axis[0]->pos[2]);
		//Vector origin(0.0f, 0.0f, 0.0f);
		const int len = 1.0f;
		flt32 ori_x, ori_y;

		if(!pCamera->WorldToScreen(origin, &ori_x, &ori_y, viewSize.x, viewSize.y))
			return false;

		flt32 *pField = NULL;

		for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
		{
			if(!m_bPickedAxis[i])
				continue;

			Vector axis = origin;
			flt32 axis_x, axis_y;

			char axisName[2] = {0, 0};

			flt32 *pField = NULL;
			switch(i)
			{
			case enum_AxisX:
				axisName[0] = 'x';
				axis.x += len;
				pField = &delta.x;
				break;
			case enum_AxisY:
				axisName[0] = 'y';
				axis.y += len;
				pField = &delta.y;
				break;
			case enum_AxisZ:
				axisName[0] = 'z';
				axis.z += len;
				pField = &delta.z;
			}

			if(!pCamera->WorldToScreen(axis, &axis_x, &axis_y, viewSize.x, viewSize.y))
				return false;

			axis_x -= ori_x;
			axis_y -= ori_y;

			flt32 dis_axis = sqrt(axis_x * axis_x + axis_y * axis_y);
			flt32 cos_axis = axis_x / dis_axis;
			flt32 sin_axis = axis_y / dis_axis;

			flt32 angle = acos(cos_axis) / PI;	//[0, PI]
			if(cos_axis > 0.0f && sin_axis < 0.0f)
			{//第四象限
				angle = -angle + 2.0f;
			}
			else if(cos_axis < 0.0f && sin_axis > 0.0f)
			{//二
				//angle = PI - angle;
			}
			else if(cos_axis < 0.0f && sin_axis < 0.0f)
			{//三
				angle = 2.0f - angle;
			}

			TRACE(_T("tool object: [OnMouseMove] %s 轴 cos: %f, sin: %f, angle: %f Pi.\n"), 
				axisName, cos_axis, sin_axis, angle);

			*pField += xDelta * cos_axis + yDelta * sin_axis;
		}

		const flt32 minLimit = 0.1f;

		flt32 temp = m_scale[0] + delta.x;
		if(temp > 0.1f)
			m_scale[0] = temp;

		temp = m_scale[1] + delta.y;
		if(temp > 0.1f)
			m_scale[1] = temp;

		temp = m_scale[2] + delta.z;
		if(temp > 0.1f)
			m_scale[2] = temp;

		//美术要求model的3个方向的scale一致
		{
			flt32 *pField = NULL;
			for(int i=(int)enum_AxisX; i<(int)enum_None; ++i)
			{
				if(!m_bPickedAxis[i])
					continue;

				pField = m_scale + i;
			}

			if(pField != NULL)
			{
				fill_n(m_scale, 3, *pField);
			}
		}

	}

	UpdateModel();


	return true;
}

void CToolObject::CTransformingVisitor::ApplyTransform( CNdlStaticModelRes* modelRes)
{
	if(NULL == modelRes)
		return;

	modelRes->GetModel()->SetPosition( m_position[0]+m_offset[0], m_position[1]+m_offset[1], m_position[2]+m_offset[2] );
	//modelRes->GetModel()->SetPosition( m_mousePos[0]+m_offset[0], m_mousePos[1]+m_offset[1], m_mousePos[2]+m_offset[2] );
	modelRes->GetModel()->SetRotationX( m_rotate[0]*PI/180.0f );
	modelRes->GetModel()->SetRotationY( m_rotate[1]*PI/180.0f );
	modelRes->GetModel()->SetRotationZ( m_rotate[2]*PI/180.0f );
	modelRes->GetModel()->SetScaleXYZ(m_scale[0],m_scale[1],m_scale[2]);
}

void CToolObject::CTransformingVisitor::UpdateInfo(const TObjectEditInfo *pModel_)
{
	const int dim = 3;

	if(pModel_ != NULL)
	{
		for( sInt32 i=0; i<dim; i++ ) 
		{
			m_position[i]	= pModel_->pos[i];
			m_offset[i]		= pModel_->offset[i];
			m_rotate[i]		= pModel_->rotate[i];
			m_scale[i]		= pModel_->scale[i];
		}
	}
	else
	{
		fill_n(m_position, dim, 0.0f);
		fill_n(m_offset, dim, 0.0f);
		fill_n(m_rotate, dim, 0.0f);
		fill_n(m_scale, dim, 1.0f);
	}
}

void CToolObject::CTransformingVisitor::UpdateModel()
{
	// 	if(m_pickStatus.IsPickFromSelect() || m_pickStatus.IsPickFromResource())
	// 		return;

	TModels &selModels = m_pToolObject->m_selectingVisitor.m_selectModels;
	if(selModels.empty())
		return;

	//设置被选择的model的位置
	{
		//这里需要计算一个偏移量，即每个model相对于pos(鼠标所在点)的偏移量
		bool bValid = false;;	//指示偏移量是否有效。
		flt32 posOffset[3]/*, offsetOffset[3], rotOffset[3], scaleOffset[3]*/;

		for(TModels::iterator it = selModels.begin(); it != selModels.end(); ++it)
		{
			TObjectEditInfo *pModel = it->pModel;
			ASSERT(pModel != NULL);

			//计算偏移量，第一个model的位移
			if(!bValid)
			{
				posOffset[0] = m_position[0] - pModel->pos[0];
				posOffset[1] = m_position[1] - pModel->pos[1];
				posOffset[2] = m_position[2] - pModel->pos[2];

				// 				offsetOffset[0] = m_offset[0] - pModel->offset[0];
				// 				offsetOffset[1] = m_offset[1] - pModel->offset[1];
				// 				offsetOffset[2] = m_offset[2] - pModel->offset[2];
				// 
				// 
				// 				rotOffset[0] = m_rotate[0] - pModel->rotate[0];
				// 				rotOffset[1] = m_rotate[1] - pModel->rotate[1];
				// 				rotOffset[2] = m_rotate[2] - pModel->rotate[2];
				// 
				// 				scaleOffset[0] = m_scale[0] / pModel->scale[0];
				// 				scaleOffset[1] = m_scale[1] / pModel->scale[1];
				// 				scaleOffset[2] = m_scale[2] / pModel->scale[2];

				bValid = true;
			}

			// 			flt32 offset[3] = {pModel->offset[0] + offsetOffset[0], 
			// 								pModel->offset[1] + offsetOffset[1], 
			// 								pModel->offset[2] + offsetOffset[2]};
			// 
			// 			flt32 rotate[3] = {pModel->rotate[0] + rotOffset[0],
			// 								pModel->rotate[1] + rotOffset[1],
			// 								pModel->rotate[2] + rotOffset[2]};
			// 
			// 			flt32 scale[3] = {pModel->scale[0] + scaleOffset[0],
			// 								pModel->scale[1] + scaleOffset[1],
			// 								pModel->scale[2] + scaleOffset[2]};

			pModel->pos[0] = pModel->pos[0] + posOffset[0];
			pModel->pos[1] = pModel->pos[1] + posOffset[1];
			pModel->pos[2] = pModel->pos[2] + posOffset[2];

			//theApp.GetWorldEditor()->ModifyStaticModel(it->id, offset, rotate, scale );
			//theApp.GetWorldEditor()->ModifyStaticModel(it->id, m_offset, m_rotate, m_scale );
			//目前支持的变化模式：
			//1、支持多个物体同时移动
			//2、支持单个物体旋转、缩放，不支持多个物体同时旋转、缩放。
			if(1 == selModels.size())
			{
				theApp.GetWorldEditor()->ModifyStaticModel(it->id, m_offset, m_rotate, m_scale );
			}
			else
			{
				theApp.GetWorldEditor()->ModifyStaticModel(it->id, pModel->offset, pModel->rotate, pModel->scale);
			}

			pModel->SyncOffset2WorldPos();

		}
	}

	TObjectEditInfo *pModel = selModels.begin()->pModel;
	m_pToolObject->m_selectingVisitor.UpdateInfo(pModel);

	/*
	bool b_isRotateModified = false;
	for( sInt32 i=0; i<3; i++ ) {
	if (m_selectModels[0]->rotate[i]	!= m_rotate[i])
	{
	b_isRotateModified = true;
	}
	}

	ShowPmpModel();
	if (b_isRotateModified)
	{
	//RefreshUIShow(m_selObject);
	RefreshUIShow((TObjectEditInfo *)m_selectModels[0]);
	}
	*/
}


bool CToolObject::CTransformingVisitor::Create()
{
	SAFE_DELETE(m_Axis[enum_AxisX]);
	SAFE_DELETE(m_Axis[enum_AxisY]);
	SAFE_DELETE(m_Axis[enum_AxisZ]);

	char file[MAX_PATH*2];
	sprintf_s(file,"%s\\Required\\Helper\\x.mex", CWorld::GetAppCharDir());
	m_Axis[enum_AxisX] = MeNew TObjectEditInfo();
	if(!m_Axis[enum_AxisX]->LoadFromFile(file))
		return false;
	//m_Axis[enum_AxisX]->model->SetRotationZ(PI * 0.5f);
	m_Axis[enum_AxisX]->rotate[2] = 90.0f;

	sprintf_s(file,"%s\\Required\\Helper\\y.mex", CWorld::GetAppCharDir());
	m_Axis[enum_AxisY] = MeNew TObjectEditInfo();
	if(!m_Axis[enum_AxisY]->LoadFromFile(file))
		return false;
	//m_Axis[enum_AxisY]->rotate[2] = -45.0f;

	sprintf_s(file,"%s\\Required\\Helper\\z.mex", CWorld::GetAppCharDir());
	m_Axis[enum_AxisZ] = MeNew TObjectEditInfo();
	if(!m_Axis[enum_AxisZ]->LoadFromFile(file))
		return false;

	m_Axis[enum_AxisX]->model->SetScale(GetMe3dConfig()->m_fMdlSpaceScale * 20.0f);
	m_Axis[enum_AxisY]->model->SetScale(GetMe3dConfig()->m_fMdlSpaceScale * 20.0f);
	m_Axis[enum_AxisZ]->model->SetScale(GetMe3dConfig()->m_fMdlSpaceScale * 20.0f);

	ResetAxis();

	//这里应该加上根据camera的rotation调整坐标轴的角度

	return true;
}

void CToolObject::CTransformingVisitor::Reset()
{

}

void CToolObject::CTransformingVisitor::ResetAxis()
{
	SetTransformType(e_trans_move);
	fill_n(m_bPickedAxis, 3, false);
}

void CToolObject::CTransformingVisitor::Render()
{
	// 选中和不选中都改为1.0alpha [2012.4.7] wangshuai
	float pickingAlpha = 1.0f;
	float noPickingAlpha = 1.0f;
	m_Axis[enum_AxisX]->model->UpdateByParam(HQ_TimeGetTime());
	if(m_bPickedAxis[enum_AxisX])
		m_Axis[enum_AxisX]->model->Render(pickingAlpha);
	else
		m_Axis[enum_AxisX]->model->Render(noPickingAlpha);

	m_Axis[enum_AxisY]->model->UpdateByParam(HQ_TimeGetTime());
	if(m_bPickedAxis[enum_AxisY])
		m_Axis[enum_AxisY]->model->Render(pickingAlpha);
	else
		m_Axis[enum_AxisY]->model->Render(noPickingAlpha);

	m_Axis[enum_AxisZ]->model->UpdateByParam(HQ_TimeGetTime());
	if(m_bPickedAxis[enum_AxisZ])
		m_Axis[enum_AxisZ]->model->Render(pickingAlpha);
	else
		m_Axis[enum_AxisZ]->model->Render(noPickingAlpha);
}

int CToolObject::CTransformingVisitor::GetSelectedAxis()
{
	int count = 0;
	for(int i=0; i<enum_None; ++i)
	{
		if(m_bPickedAxis[i])
			++count;
	}

	return count;
}

void CToolObject::CTransformingVisitor::SetTransformType(ETransformType type_)
{
	m_tranType = type_; 
	UpdateAxisInfo();

	int maxCount = 1;
	if(e_trans_move == m_tranType)
		maxCount = 2;

	{
		int index = (int)enum_AxisX;
		while(GetSelectedAxis() > maxCount && index < (int)enum_None)
		{
			m_bPickedAxis[index] = false;
		}

		ASSERT(GetSelectedAxis() <= maxCount);
	}
}

int CToolObject::CTransformingVisitor::SelectAxis(const CPoint &point_)
{
	int maxCount = 1;
	// 	if(e_trans_move == m_tranType)
	// 		maxCount = 2;

	// 	{
	// 		int index = (int)enum_AxisX;
	// 		while(GetSelectedAxis() > maxCount && index < (int)enum_None)
	// 		{
	// 			m_bPickedAxis[index] = false;
	// 		}
	// 
	// 		ASSERT(GetSelectedAxis() <= maxCount);
	// 	}

	ASSERT(GetSelectedAxis() <= maxCount);

	int count = 0;

	/*
	if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisX]))
	{
	TRACE(_T("CToolObject: [SelectAxis] is picking x axis. \n"));
	if(m_bPickedAxis[enum_AxisX])
	m_bPickedAxis[enum_AxisX] = false;
	else
	{
	if(GetSelectedAxis() < maxCount)
	m_bPickedAxis[enum_AxisX] = true;
	}

	++count;
	}

	if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisY]))
	{
	TRACE(_T("CToolObject: [SelectAxis] is picking y axis. \n"));
	if(m_bPickedAxis[enum_AxisY])
	m_bPickedAxis[enum_AxisY] = false;
	else
	{
	if(GetSelectedAxis() < maxCount)
	m_bPickedAxis[enum_AxisY] = true;
	}

	++count;
	}

	if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisZ]))
	{
	TRACE(_T("CToolObject: [SelectAxis] is picking z axis.\n"));
	if(m_bPickedAxis[enum_AxisZ])
	m_bPickedAxis[enum_AxisZ] = false;
	else
	{
	if(GetSelectedAxis() < maxCount)
	m_bPickedAxis[enum_AxisZ] = true;
	}

	++count;
	}
	*/
	if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisX]))
	{
		TRACE(_T("CToolObject: [SelectAxis] is picking x axis. \n"));

		m_bPickedAxis[enum_AxisX] = true;
		m_bPickedAxis[enum_AxisY] = false;
		m_bPickedAxis[enum_AxisZ] = false;

		++count;
	}
	else if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisY]))
	{
		TRACE(_T("CToolObject: [SelectAxis] is picking y axis. \n"));

		m_bPickedAxis[enum_AxisX] = false;
		m_bPickedAxis[enum_AxisY] = true;
		m_bPickedAxis[enum_AxisZ] = false;

		++count;
	}
	else if(NHelper::IsPickingModel(point_, *m_Axis[enum_AxisZ]))
	{
		TRACE(_T("CToolObject: [SelectAxis] is picking z axis.\n"));

		m_bPickedAxis[enum_AxisX] = false;
		m_bPickedAxis[enum_AxisY] = false;
		m_bPickedAxis[enum_AxisZ] = true;

		++count;
	}

	ASSERT(GetSelectedAxis() <= maxCount);

	return count;
}

void CToolObject::CTransformingVisitor::SetAxisPos(const Vector &pos_)
{
	flt32 position[3] = {pos_.x, pos_.y, pos_.z};
	memcpy(m_Axis[0]->pos, position, sizeof(m_Axis[0]->pos));
	//m_Axis[0]->pos[2] += 10.0f;
	memcpy(m_Axis[1]->pos, position, sizeof(m_Axis[1]->pos));
	//m_Axis[1]->pos[2] += 10.0f;
	memcpy(m_Axis[2]->pos, position, sizeof(m_Axis[2]->pos));
	//m_Axis[2]->pos[2] += 10.0f;
	m_Axis[0]->ApplyTransform();
	m_Axis[1]->ApplyTransform();
	m_Axis[2]->ApplyTransform();
}

Vector CToolObject::CTransformingVisitor::GetAxisPos(Vector& minVec,Vector& maxVec)
{
	Vector pos(0.0f,0.0f,0.0f);

	Vector half;
	half.x = (minVec.x + maxVec.x)/2;
	half.y = (minVec.y + maxVec.y)/2;
	half.z = (minVec.z + maxVec.z)/2;

	pos.x = half.x;
	pos.y = half.y;
	//pos.z = maxVec.z + 0.2f;
	pos.z = maxVec.z + 4.0f;
	return pos;
}

namespace NHelper
{

	bool BuildFrustum(const RECT &area_, FrustumEx &_frustum)
	{


		CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		if(NULL == pView)
			return false;

		Vector2 viewSize;
		pView->GetViewSize( viewSize.x, viewSize.y );
		if(viewSize.x < 1 || viewSize.y < 1)
			return false;

		SwCamera* pCamera = pView->GetActiveCamera();
		if(NULL == pCamera)
			return false;

		D3DXMATRIX matView = pCamera->GetViewMatrix();
		D3DXMATRIX matProj = pCamera->GetProjMatrix();

		const int origin[2] = {viewSize.x / 2, viewSize.y / 2};

		enum E_Pos
		{
			e_left = 0,
			e_top,
			e_right,
			e_bottom,
		};
		const float pos[4] = {(float)(area_.left - origin[0]) / (float)origin[0], (float)(area_.top - origin[1]) / (float)origin[1], 
			(float)(area_.right - origin[0]) / (float)origin[0], (float)(area_.bottom - origin[1]) / (float)origin[1]};


		D3DXMATRIX mat;

		D3DXMatrixMultiply( &mat, &matView,&matProj  );
		D3DXMatrixInverse( &mat, NULL, &mat );


		D3DXVECTOR3 veFrustumEx[8];
		//运算取得视锥的8个定点
		//vec * view * proj = 屏幕点
		//取逆
		veFrustumEx[0] = D3DXVECTOR3(pos[e_left], pos[e_bottom],  0.0f); // xyz
		veFrustumEx[1] = D3DXVECTOR3(pos[e_right], pos[e_bottom],  0.0f); // Xyz
		veFrustumEx[2] = D3DXVECTOR3(pos[e_left],  pos[e_top],  0.0f); // xYz
		veFrustumEx[3] = D3DXVECTOR3(pos[e_right],  pos[e_top],  0.0f); // XYz
		veFrustumEx[4] = D3DXVECTOR3(pos[e_left], pos[e_bottom],  1.0f); // xyZ
		veFrustumEx[5] = D3DXVECTOR3(pos[e_right], pos[e_bottom],  1.0f); // XyZ
		veFrustumEx[6] = D3DXVECTOR3(pos[e_left],  pos[e_top],  1.0f); // xYZ
		veFrustumEx[7] = D3DXVECTOR3(pos[e_right],  pos[e_top],  1.0f); // XYZ

		for( UINT i = 0; i < 8; i++ )
			D3DXVec3TransformCoord( &veFrustumEx[i], &veFrustumEx[i], &mat );

		_frustum.BuildFrustum(veFrustumEx[0], veFrustumEx[7]);

		return true;
	}

	int SelectChunks(const RECT &area_, TChunks &_chunks)
	{
		//这个类仅仅是为了导出两个CWorldChunk的数据m_chunk。
		class CWorldChunk_M: public CWorldChunk
		{
		public:
			void GetChunkPos(sInt32 &_x, sInt32 &_y)
			{
				_x = m_chunk[0];
				_y = m_chunk[1];
			}
		};

		_chunks.clear();

		sInt32 pos[4][2];

		int index = 0;
		//top, left
		CPoint point(area_.left, area_.top);
		CWorldChunk_M *pChunk = (CWorldChunk_M *)GetWorldChunk(point);
		if(NULL == pChunk)
			return _chunks.size();
		pChunk->GetChunkPos(pos[index][0], pos[index][1]);
		++index;

		//top, right
		point = CPoint(area_.right, area_.top);
		pChunk = (CWorldChunk_M *)GetWorldChunk(point);
		if(NULL == pChunk)
			return _chunks.size();
		pChunk->GetChunkPos(pos[index][0], pos[index][1]);
		++index;

		//bottom, left
		point = CPoint(area_.left, area_.bottom);
		pChunk = (CWorldChunk_M *)GetWorldChunk(point);
		if(NULL == pChunk)
			return _chunks.size();
		pChunk->GetChunkPos(pos[index][0], pos[index][1]);
		++index;

		//bottom, right
		point = CPoint(area_.right, area_.bottom);
		pChunk = (CWorldChunk_M *)GetWorldChunk(point);
		if(NULL == pChunk)
			return _chunks.size();
		pChunk->GetChunkPos(pos[index][0], pos[index][1]);

		sInt32 minX = 99999;
		sInt32 maxX = -1;
		sInt32 minY = 99999;
		sInt32 maxY = -1;
		for(int i = 0; i< 4; ++i)
		{
			sInt32 value = pos[i][0];
			if(minX > value)
				minX = value;

			if(maxX < value)
				maxX = value;

			value = pos[i][1];
			if(minY > value)
				minY = value;

			if(maxY < value)
				maxY = value;

		}

		CWorldBuffer *pWorldBuffer = theApp.GetWorld()->GetWorldBuffer();	
		//这里可以不检查了
		// 	if(NULL == pWorldBuffer)
		// 		return _chunks.size();

		CWorldTile *pTile = pWorldBuffer->GetActiveTile();
		//这里可以不检查了
		// 	if(NULL == pTile)
		// 		return _chunks.size();

		for(sInt32 y = minY; y <= maxY; ++y)
		{
			for(sInt32 x = minX; x <= maxX; ++x)
			{
				CWorldChunk *pChunk = pTile->GetChunk(x, y);
				if(pChunk != NULL)
					_chunks.push_back(pChunk);
			}
		}

		return _chunks.size();
	}

	bool ScreenToWorld(const CPoint &point_, flt32 *_pos)
	{
		ASSERT(_pos != NULL);

		Vector worldPos;
		if(ScreenToWorld(point_, worldPos))
		{
			_pos[0] = worldPos.x;
			_pos[1] = worldPos.y;
			_pos[2] = worldPos.z;
			return true;
		}

		return false;
	}

	bool ScreenToWorld(const CPoint &point_, Vector &_worldPos)
	{
		CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		if(NULL == pView)
			return false;

		sInt32 pickId = pView->PickWorldTerrain( point_, emPT_Terrain );
		if(-1 == pickId)
			return false;

		const TPickResult& pickResult = pView->GetPickResult();

		for( sInt32 i=0; i<2; i++ ) 
		{
			sInt32 glVert =( ZnFloor2Int( ((pickResult.pickResultInfo[pickId].point[i])+WORLDORIGIN(i))/WORLD_VERTSIZE ) );
			_worldPos[i] = ( (glVert) * WORLD_VERTSIZE - WORLDORIGIN(i) );
			if( (_worldPos[i] - pickResult.pickResultInfo[pickId].point[i]) > (WORLD_UNITSIZE * 0.25f) ) 
			{
				_worldPos[i] += (WORLD_UNITSIZE * 0.5f);
			}
		}

		pView->GetWorldPicker()->GetHeight(_worldPos.x, _worldPos.y, _worldPos.z);

		//要验证坐标吗？

		return true;
	}

	CWorldChunk *GetWorldChunk(const CPoint &point_)
	{

		Vector worldPos;
		if(!ScreenToWorld(point_, worldPos))
			return NULL;

		CWorldBuffer *pWorldBuffer = theApp.GetWorld()->GetWorldBuffer();	
		if(NULL == pWorldBuffer)
			return NULL;

		CWorldTile *pTile = pWorldBuffer->GetActiveTile();
		if(NULL == pTile)
			return NULL;

		CWorldChunk *pChunk = pTile->GetChunkFromPos(worldPos.x, worldPos.y);

		return pChunk;
	}

	bool IsPickingModel(const CPoint &point_, const TObjectInfo &model_)
	{
		CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		if(NULL == pView)
			return false;

		SwCamera* pCamera = pView->GetActiveCamera();
		CEditCamera* pEditCamera = dynamic_cast<CEditCamera*>(pCamera);
		if(NULL == pEditCamera)
			return false;

		// 	Vector pos		= GetActiveCamera()->GetPos();
		// 	UpdateHorizontal( pos );

		//setup ray
		Vector rayPt, rayDir;
		pEditCamera->ScreenToWorldRay( Vector2(point_.x, point_.y), rayPt, rayDir );

		if(model_.model->GetWorldBBox()->Intersect(rayPt,rayDir))
			return true;

		return false;
	}

	void DrawRect(const RECT &area_, DWORD color_)
	{
		CBaseGraphics::DrawRect2D(const_cast<RECT &>(area_), color_);
	}

	void DrawPolygon3D(const SPolygon &polygon_, DWORD color_)
	{
		int size = polygon_.size();
		//ASSERT(size >= 3);
		if(size < 3)
			return;

		CBaseGraphics *pDrawer = GetDrawer();
		if(NULL == pDrawer)
			return;

		for(int i=0; i<size - 1; ++i)
		{
			GetDrawer()->DrawLine3D(D3DXVECTOR3(polygon_[i].x, polygon_[i].y, 0), D3DXVECTOR3(polygon_[i+1].x, polygon_[i+1].y, 0), color_);
		}

		GetDrawer()->DrawLine3D(D3DXVECTOR3(polygon_[size - 1].x, polygon_[size - 1].y, 0), D3DXVECTOR3(polygon_[0].x, polygon_[0].y, 0), color_);
	}

	void TransformRect(RECT &_area_)
	{
		if(_area_.left > _area_.right)
			std::swap(_area_.left, _area_.right);

		if(_area_.top > _area_.bottom)
			std::swap(_area_.top, _area_.bottom);
	}

	void CopyPolygon(SPolygon &_destPolygon, const SPolygon &srcPolygon_)
	{
		_destPolygon.clear();

		_destPolygon = srcPolygon_;
	}

	int Multiply(CPoint p1_, CPoint p2_, CPoint p0_)
	{
		return ( (p1_.x - p0_.x) * (p2_.y - p0_.y) - (p2_.x - p0_.x) * (p1_.y - p0_.y));
	}

	bool IsOnline(const TPoint &point_, const SLineSegment &line_)
	{
		return( ( Multiply(line_.pt1, line_.pt2, point_)< 0 ) &&
			( ( point_.x - line_.pt1.x ) * ( point_.x - line_.pt2.x ) <= 0 ) &&
			( ( point_.y - line_.pt1.y ) * ( point_.y - line_.pt2.y ) <= 0 ) );
	}

	bool Intersect(const SLineSegment &L1_, const SLineSegment &L2_)
	{
		return( (max(L1_.pt1.x, L1_.pt2.x) >= min(L2_.pt1.x, L2_.pt2.x)) &&
			(max(L2_.pt1.x, L2_.pt2.x) >= min(L1_.pt1.x, L1_.pt2.x)) &&
			(max(L1_.pt1.y, L1_.pt2.y) >= min(L2_.pt1.y, L2_.pt2.y)) &&
			(max(L2_.pt1.y, L2_.pt2.y) >= min(L1_.pt1.y, L1_.pt2.y)) &&
			(Multiply(L2_.pt1, L1_.pt2, L1_.pt1) * Multiply(L1_.pt2, L2_.pt2, L1_.pt1) >= 0) &&
			(Multiply(L1_.pt1, L2_.pt2, L2_.pt1) * Multiply(L2_.pt2, L1_.pt2, L2_.pt1) >= 0)
			);
	}

	/*----------------------------------------------------------
	desc	: 射线法
	----------------------------------------------------------*/
	bool IsInPolygon(const SPolygon &polygon_, const TPoint &point_)
	{
		int n = polygon_.size();
		int count = 0;
		SLineSegment line;
		line.pt1 = point_;
		line.pt2.y = point_.y;
		line.pt2.x = 0; //向左的水平射线
		SLineSegment side;
		for( int i = 0; i < n; i++ )
		{
			// 得到多边形的一条边
			side.pt1 = polygon_[i];
			side.pt2 = polygon_[(i + 1) % n];
			if( IsOnline(point_, side)) 
				return true;

			// 如果side平行x轴则不作考虑
			if(side.pt1.y == side.pt2.y)
				continue;
			if( IsOnline(side.pt1, line) ) 
			{
				if( side.pt1.y > side.pt2.y ) 
					++count;
			} 
			else if( IsOnline(side.pt2, line) ) 
			{
				if( side.pt2.y > side.pt1.y ) 
					++count;
			} 
			else if( Intersect(line, side) ) 
			{
				++count;
			}
		}
		if ( count % 2) 
			return true; //奇数
		else
			return false; //偶数
	}

}


