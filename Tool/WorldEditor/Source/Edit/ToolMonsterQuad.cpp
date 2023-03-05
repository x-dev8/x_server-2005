/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	ToolMonsterQuad.cpp
* Create: 	11/04/08
* Desc:
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "ToolMonsterQuad.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/MonsterQuadDlg.h"
#include "ui/Custom/ReachableMapGenerate.h"
#include "SwMap.h"
#include "rollback\IMonsterToolOperation.h"
#include "Edit/ToolObject.h"
#include "ndl/NdlHelper.h"
////////////////////////////////////////////////////////////////////////////////
CToolMonsterQuad::CToolMonsterQuad()
{
    mMonsQuadDlg  = NULL;
    mCurQuadRes  = NULL;
    m_selPmpBox = 0;
    m_dirArrow = NULL;
    m_eoptMode	= optMode_AddMonsterQuad;
    m_reachableData  = NULL;
    m_maxRayCastDistanceBak = 0;
}

CToolMonsterQuad::~CToolMonsterQuad()
{
    SAFE_DELETE( m_selPmpBox );
    SAFE_DELETE( m_dirArrow );
}

bool CToolMonsterQuad::Create( CToolManager *toolMgr )
{
    CBaseTool::Create( toolMgr );
    char path[MAX_PATH * 2];
    sprintf_s( path, "%s\\Required\\Model\\Box.mex", CWorld::GetAppCharDir() );

    //create the pmpbox
    m_selPmpBox = MeNew TObjectEditInfo();
    if (!m_selPmpBox->LoadFromFile( path ))
        return false;

    m_dirArrow = MeNew TObjectEditInfo();
    sprintf_s( path, "%s\\Required\\Helper\\target.mex", CWorld::GetAppCharDir() );
    if ( !m_dirArrow->LoadFromFile( path ) )
    {
        return false;
    }

    m_pickingVisitor.SetToolObject(this);

    return true;
}

void CToolMonsterQuad::ShowPmpModel()
{
    if (mCurQuadRes == NULL)
    {
        return;
    }
    Assert(NULL != mCurQuadRes->GetModel());
    if ( NULL != m_selPmpBox )
    {
        flt32 scale = 1.0f;
        //set scale
        scale = mCurQuadRes->GetModel()->model->GetScale();
        m_selPmpBox->model->SetScale(scale);
        //set rotation
        float fX, fY, fZ;
        mCurQuadRes->GetModel()->model->GetRotation( fX, fY, fZ );
        m_selPmpBox->model->SetRotationX( fX );
        m_selPmpBox->model->SetRotationY( fY );
        m_selPmpBox->model->SetRotationZ( fZ );
        //set position
        m_selPmpBox->model->SetPosition( mCurQuadRes->GetModel()->model->GetPosition() );
        //update
        m_selPmpBox->Update(0.0f);
    }
}

void CToolMonsterQuad::ShowDirArrow()
{
    if (mCurQuadRes == NULL)
    {
        return;
    }
    Assert( NULL != mCurQuadRes->GetModel() );
    if ( m_dirArrow != NULL && mCurQuadRes->m_bIsOnePoint == true )
    {
        flt32 scale = 1.0f;
        //set scale
        scale = mCurQuadRes->GetModel()->model->GetScale();
        m_dirArrow->model->SetScale(scale / 2.0f);
        //set rotation
        float fX, fY, fZ;
        mCurQuadRes->GetModel()->model->GetRotation( fX, fY, fZ );
        m_dirArrow->model->SetRotationX( fX );
        m_dirArrow->model->SetRotationY( fY );
        m_dirArrow->model->SetRotationZ( fZ + PIOVER180 * ( mCurQuadRes->m_nDir + 90 ) );
        //set position
        m_dirArrow->model->SetPosition( mCurQuadRes->GetModel()->model->GetPosition() );
        //update
        m_dirArrow->Update(0.0f);
    }
}

void CToolMonsterQuad::Bind( CToolMonsterQuadDlg *dlg )
{
    mMonsQuadDlg = dlg;
}

bool CToolMonsterQuad::OnLMouseDown( UINT nFlags, CPoint point )
{
    m_isLDrag	= true;
    m_oldPos	= point;

    CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    sInt32 pickId = view->PickWorldTerrain( point, emPT_MonsterQuad | emPT_Terrain | emPT_FloorObj );
    if (pickId != -1)
    {
        const TPickResult &pickResult = view->GetPickResult();
        if (m_eoptMode == optMode_Pick) // Pick已存在的怪物Zone
        {
            mCurQuadRes = NULL;
            sInt32 objId = -1;

            CString strPmt;
            strPmt.Format(_T("没有选中物体"));
            for (sInt32 i = 0; i < pickResult.pickResultCount; ++i)
            {
                if (emPT_MonsterQuad == pickResult.pickResultInfo[i].resultType)
                {
                    objId = i;
                    break;
                }
            }
            CResEditMgr *resMgr = GetResMgr();
            if (resMgr == NULL)
                return false;

            if (objId != -1)
            {
                mCurQuadRes = GetResMgr()->MonsterQuad(pickResult.pickResultInfo[objId].resultId);
                if (mCurQuadRes != NULL)
                {
					strPmt.Format( _T("选中怪物区域点%d"), mCurQuadRes->GetId());
                    mMonsQuadDlg->Update(mCurQuadRes);
                    
					CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
					CNdlHelper *helper = view->GetHelper();
					helper->ClearSelModel();
					helper->PushSelModel(mCurQuadRes->GetModel());

					//ShowPmpModel();
                    //ShowDirArrow();
                }
                else
                {
                    CString tmpStr;
                    tmpStr.Format(_T("Monster Quad id: %d!"), pickResult.pickResultInfo[objId].resultId);
                    AfxMessageBox(tmpStr);
                }
			}
            /*else
            {
                if (m_selPmpBox != NULL)
                {
                    m_selPmpBox->model->SetPosition( 0.0f, 0.0f, 0.0f );
                    m_selPmpBox->Update(0.0f);
                }
                if (m_dirArrow != NULL)
                {
                    m_dirArrow->model->SetPosition( 0.0f, 0.0f, 0.0f );
                    m_dirArrow->Update(0.0f);
                }
            }*/
            theApp.SetPromptText( strPmt );
        }
        else if (m_eoptMode == optMode_AddMonsterQuad) // 添加怪物Zone
        {
            int close_id = GetCloseIndex(pickResult, emPT_MonsterQuad);
            flt32 pos[3];
            for (sInt32 i = 0; i < 3; ++i)
            {
                pos[i] = pickResult.pickResultInfo[close_id].point[i];
            }

			DoAddMonsterQuad(pos[1] + 0.5f, pos[0] - 0.5f, pos[0] + 0.5f, pos[1] - 0.5f);
            CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
        }
    }
    return true;
}

bool CToolMonsterQuad::OnLMouseUp( UINT nFlags, CPoint point )
{
    m_isLDrag = false;
    return true;
}

bool CToolMonsterQuad::OnLMouseDblClk( UINT nFlags, CPoint point )
{
    return true;
}

bool CToolMonsterQuad::OnRMouseDown( UINT nFlags, CPoint point )
{
    m_isRDrag = true;
    m_oldPos = point;
    return true;
}

bool CToolMonsterQuad::OnRMouseUp( UINT nFlags, CPoint point )
{
    m_isRDrag = false;
    return true;
}

bool CToolMonsterQuad::OnMouseMove( UINT nFlags, CPoint point )
{
    Vector2 viewSize;
    CWorldEditView *view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    view->GetViewSize( viewSize.x, viewSize.y );
    if ( viewSize.x < 1 || viewSize.y < 1 )
        return false;

    SwCamera *camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

    CPoint delta = point - m_oldPos;
    if (m_isRDrag) 	// move
    {
        CameraAdjust(point, nFlags);
    }
    else
	{
		sInt32 pickId = view->PickWorldTerrain( point, emPT_MonsterQuad | emPT_Terrain | emPT_FloorObj );
		if (pickId != -1)
		{
			const TPickResult &pickResult = view->GetPickResult();
			int close_id = GetCloseIndex(pickResult, emPT_MonsterQuad);
			flt32 pos[3];
			for (sInt32 i = 0; i < 3; ++i)
			{
				pos[i] = pickResult.pickResultInfo[close_id].point[i];
			}

			if (m_isLDrag && m_eoptMode == optMode_Pick && mCurQuadRes != NULL)
			{
				UpdateMonsQuad(mCurQuadRes, pos[0], pos[1], 0, 0);
			}
			else if (m_eoptMode == optMode_AddMonsterQuad)
			{
				// 让TempMonsQuad的位置跟随鼠标移动
				mTempQuadRes.Update(pos[0], pos[1], 0, 0);
				mTempQuadRes.ApplyTransform();
			}
		}
    }
    camera->Update(0.0f, 0.0f);
    return true;
}

bool CToolMonsterQuad::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if (NULL == mCurQuadRes)
    {
        return false;
    }
    if ( nChar == VK_DELETE )
    {
        DeleteModel();
        return true;
    }
    if (optMode_Pick == m_eoptMode)
    {
        flt32 delta = 0.1f;
        if (nFlags & MK_CONTROL )
        {
            delta	= 0.5f;
        }
        if ( nChar == VK_LEFT )
        {
            //mCurQuadRes->SetPosX(mCurQuadRes->GetPosX() - delta);
        }
        else if ( nChar == VK_RIGHT )
        {
            //mCurQuadRes->SetPosX(mCurQuadRes->GetPosX() + delta);
        }
        else if ( nChar == VK_DOWN )
        {
           // mCurQuadRes->SetPosY(mCurQuadRes->GetPosY() - delta);
        }
        else if ( nChar == VK_UP )
        {
            //mCurQuadRes->SetPosY(mCurQuadRes->GetPosY() + delta);
        }
        mCurQuadRes->ApplyTransform();
        ShowPmpModel();
        ShowDirArrow();
        mMonsQuadDlg->Update(mCurQuadRes);
        CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
    }

    return true;
}

bool CToolMonsterQuad::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    CBaseTool::OnKeyUp(nChar, nRepCnt, nFlags);

    if (nChar == VK_ESCAPE)		//***
    {
        //清空当前鼠标捡起的model
        m_pickingVisitor.Reset();
    }
    else if ('c' == nChar || 'C' == nChar)
    {
        //copy
        if ((nFlags & MK_CONTROL) != 0)
        {
            if (mCurQuadRes != NULL)
            {
                //复制当前选择的目标
                m_pickingVisitor.PickModels(mCurQuadRes, 1);
            }
        }
    }
    else if ('v' == nChar || 'V' == nChar)
    {
        //paste
        if ((nFlags & MK_CONTROL) != 0)
        {
            //置标志位，使得当前捡起的目标可以显示和粘帖
            m_pickingVisitor.SetPaste();
        }
    }

    return true;
}


void CToolMonsterQuad::Render()
{
	if (GetResMgr() == NULL)
		return;

	const std::vector<CMonsterQuadRes *> &quads = GetResMgr()->GetMonsterQuadList();
	for (int i = 0; i < quads.size(); ++i)
	{
		quads[i]->RenderMonsterModel();
	}
}

void CToolMonsterQuad::Reset()
{
    mCurQuadRes = NULL;
    SetOptMode(optMode_Pick);
}

CResEditMgr *CToolMonsterQuad::GetResMgr()
{
	if (CURRENTTILE != NULL)
		return (CResEditMgr *) CURRENTTILE->GetCResMgr();
	else
		return NULL;
}

void CToolMonsterQuad::SetOptMode( optMode eMode )
{
    m_eoptMode = eMode;
    switch (m_eoptMode)
    {
    case optMode_AddMonsterQuad:
        mTempQuadRes.AttachModelToNdlHelper();
        break;
    case optMode_Pick:
        mTempQuadRes.DetachModelFromNdlHelper();
        break;

    }
    mTempQuadRes.GetModel()->Update( 0.f );
}

void CToolMonsterQuad::DeleteModel()
{
    if (NULL == mCurQuadRes)
        return;

    DoDeleteMonsterQuad();

    CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
    mCurQuadRes = NULL;
}

void CToolMonsterQuad::SetActive( bool isActive /*= true */ )
{
    CBaseTool::SetActive(isActive);
    CWorldTile *pTile = CURRENTTILE;
    if (NULL == pTile)
    {
        return;
    }
    if (isActive)
    {
        SetOptMode(optMode_AddMonsterQuad);

        m_maxRayCastDistanceBak = SwGlobal::GetWorldPicker()->GetMaxRayCastDistance();
        SwGlobal::GetWorldPicker()->SetMaxRayCastDistance(2000.f);

        if ( !g_render->IsDisplayMonster())
        {
            GetResMgr()->AttachAllMonsterQuad();
        }
        if (!pTile->IsLoadReachableMap())
        {
            CReachableMapGenerate::Instance()->ReadInReachableData(pTile);
        }
        {
            m_reachableData = pTile->ReachableMap().GetMapData();
        }
    }
    else
    {
        mTempQuadRes.DetachModelFromNdlHelper();
        if (m_maxRayCastDistanceBak >= 0.1f)
        {
            SwGlobal::GetWorldPicker()->SetMaxRayCastDistance(m_maxRayCastDistanceBak);
        }
        if (!g_render->IsDisplayMonster())
        {
            GetResMgr()->DetachAllMonsterQuad();
        }
    }
}

void CToolMonsterQuad::Redo(void)
{
    mCurQuadRes = NULL;
    m_opManager.Roll();
}

void CToolMonsterQuad::Undo(void)
{
    mCurQuadRes = NULL;
    m_opManager.Rollback();
}

bool CToolMonsterQuad::CanRedo(void)
{
    return m_opManager.CanRoll();
}
bool CToolMonsterQuad::CanUndo(void)
{
    return m_opManager.CanRollback();
}

bool CToolMonsterQuad::DoDeleteMonsterQuad()
{
    if (NULL == mCurQuadRes)
        return false;

    NMonsterTool::CDeleteMonsterArea *mydo = new NMonsterTool::CDeleteMonsterArea(this);
    mydo->SetData(mCurQuadRes);
    NMonsterTool::CAddMonsterArea *undo = new NMonsterTool::CAddMonsterArea(this);
    undo->SetData(mCurQuadRes);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::DeleteMonsterQuad(CMonsterQuadRes *pRes)
{
    if (NULL == pRes)
        return false;

	//pRes->ShowMonsterPoint(false);	//detach monster point models.
    pRes->DetachModelFromNdlHelper();
    return GetResMgr()->PopMonsterQuad(pRes);
}

bool CToolMonsterQuad::DoAddMonsterQuad(float top, float left, float right, float bottom)
{
    CMonsterQuadRes *pRes = GetResMgr()->CreateMonsterQuadRes(top, left, right, bottom);
    if (NULL == pRes)
        return false;

	pRes->m_nMonsterId = mMonsQuadDlg->GetDefaultMonsterId();

    NMonsterTool::CAddMonsterArea *mydo = new NMonsterTool::CAddMonsterArea(this);
    mydo->SetData(pRes);
    NMonsterTool::CDeleteMonsterArea *undo = new NMonsterTool::CDeleteMonsterArea(this);
    undo->SetData(pRes);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::AddMonsterQuad(CMonsterQuadRes *pRes)
{
    if (NULL == pRes)
        return false;

    pRes->AttachModelToNdlHelper();
    return GetResMgr()->PushMonsterQuad(pRes);
}

bool CToolMonsterQuad::DoPasteMonsterQuad(CMonsterQuadRes *pRes_)
{
    if (NULL == pRes_)
        return false;

    CMonsterQuadRes *pRes = pRes_->Clone();
    if (NULL == pRes)
        return false;

    NMonsterTool::CAddMonsterArea *mydo = new NMonsterTool::CAddMonsterArea(this);
    mydo->SetData(pRes);
    NMonsterTool::CDeleteMonsterArea *undo = new NMonsterTool::CDeleteMonsterArea(this);
    undo->SetData(pRes);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

//bool CToolMonsterQuad::DoUpdateMonsQuad(CMonsterQuadRes *_pRes_, float x, float y, float w, float h)
//{
//    if (NULL == _pRes_)
//        return false;
//
//    NMonsterTool::CMoveMonsterArea *mydo = new NMonsterTool::CMoveMonsterArea(this);
//    mydo->SetData(_pRes_, x, y, w, h);
//
//    NMonsterTool::CMoveMonsterArea *undo = new NMonsterTool::CMoveMonsterArea(this);
//    undo->SetData(_pRes_, _pRes_->GetPosX(), _pRes_->GetPosY(), _pRes_->GetWidth(), _pRes_->GetHeight());
//
//    COpertaionPair *op = new COpertaionPair(mydo, undo);
//    return m_opManager.Excute(op);
//}

bool CToolMonsterQuad::UpdateMonsQuad(CMonsterQuadRes *_pRes_, float x, float y, float w, float h)
{
    if (NULL == _pRes_)
        return false;

	_pRes_->Update(x, y, w, h);
    _pRes_->ApplyTransform();
    return true;
}

bool CToolMonsterQuad::DoRefreshMonsterPoint(CMonsterQuadRes *_pRes_)
{
    if (NULL == _pRes_)
        return false;

    NMonsterTool::CRefreshMonsterPoint *mydo = new NMonsterTool::CRefreshMonsterPoint(this);
    mydo->SetData(_pRes_);
    NMonsterTool::CRevertMonsterPoint *undo = new NMonsterTool::CRevertMonsterPoint(this);
    undo->SetData(_pRes_);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::RefreshMonsterPoint(CMonsterQuadRes *_pRes_)
{
    if (NULL == _pRes_)
        return false;

    //return _pRes_->RefreshMonsterPoint(CURRENTTILE, GetReachableData());
	return true;
}

bool CToolMonsterQuad::RevertMonsterPoint(CMonsterQuadRes *_pRes_, const Vector2 *points_, UINT size_)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->SetMonsterPoints(points_, size_);
    return false;
}

bool CToolMonsterQuad::DoSetMonsterType(CMonsterQuadRes *_pRes_, sInt32 type_, int index_)
{
    if (NULL == _pRes_)
        return false;

    //if (index_ >= CMonsterQuadRes::MONSTERTYPETOTAL)
        return false;

    NMonsterTool::CSetMonsterType *mydo = new NMonsterTool::CSetMonsterType(this);
    mydo->SetData(_pRes_, type_, index_);
    NMonsterTool::CSetMonsterType *undo = new NMonsterTool::CSetMonsterType(this);
    //undo->SetData(_pRes_, _pRes_->GetMonsterType(index_), index_);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::SetMonsterType(CMonsterQuadRes *_pRes_, sInt32 type_, int index_)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->SetMonsterType(type_, index_);
    return true;
}

bool CToolMonsterQuad::DoSetMonsterCount(CMonsterQuadRes *_pRes_, UINT count_)
{
    if (NULL == _pRes_)
        return false;

    NMonsterTool::CSetMonsterCount *mydo = new NMonsterTool::CSetMonsterCount(this);
    mydo->SetData(_pRes_, count_);
    NMonsterTool::CSetMonsterCount *undo = new NMonsterTool::CSetMonsterCount(this);
    //undo->SetData(_pRes_, _pRes_->GetMonsterNumber());

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::SetMonsterCount(CMonsterQuadRes *_pRes_, UINT count_)
{
    if (NULL == _pRes_)
        return false;

    _pRes_->m_nNumber = count_;

    return true;
}

bool CToolMonsterQuad::DoSetMonterRatio(CMonsterQuadRes *_pRes_, float ratio_)
{
    if (NULL == _pRes_)
        return false;

    NMonsterTool::CSetMonsterRatio *mydo = new NMonsterTool::CSetMonsterRatio(this);
    mydo->SetData(_pRes_, ratio_);
    NMonsterTool::CSetMonsterRatio *undo = new NMonsterTool::CSetMonsterRatio(this);
   // undo->SetData(_pRes_, _pRes_->GetMonsterRadio());

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}
bool CToolMonsterQuad::SetMonterRatio(CMonsterQuadRes *_pRes_, float ratio_)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->SetMonsterRadio(ratio_);

    return true;
}

bool CToolMonsterQuad::DoSetMonsterInterval(CMonsterQuadRes *_pRes_, sInt32 interval_)
{
    if (NULL == _pRes_)
        return false;

    NMonsterTool::CSetMonsterInterval *mydo = new NMonsterTool::CSetMonsterInterval(this);
    mydo->SetData(_pRes_, interval_);
    NMonsterTool::CSetMonsterInterval *undo = new NMonsterTool::CSetMonsterInterval(this);
    //undo->SetData(_pRes_, _pRes_->GetMonsterInterval());

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::SetMonsterInterval(CMonsterQuadRes *_pRes_, sInt32 interval_)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->SetMonsterInterval(interval_);

    return true;
}

bool CToolMonsterQuad::DoSetEnterScript(CMonsterQuadRes *_pRes_, const char *script_)
{
    if (NULL == _pRes_ || NULL == script_)
        return false;

    NMonsterTool::CSetScript *mydo = new NMonsterTool::CSetScript(this);
    mydo->SetData(_pRes_, script_, true);
    NMonsterTool::CSetScript *undo = new NMonsterTool::CSetScript(this);
    undo->SetData(_pRes_, _pRes_->GetEnterScript(), true);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::DoSetLeaveScript(CMonsterQuadRes *_pRes_, const char *script_)
{
    if (NULL == _pRes_ || NULL == script_)
        return false;

    NMonsterTool::CSetScript *mydo = new NMonsterTool::CSetScript(this);
    mydo->SetData(_pRes_, script_, false);
    NMonsterTool::CSetScript *undo = new NMonsterTool::CSetScript(this);
    undo->SetData(_pRes_, _pRes_->GetLeaveScript(), false);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}
bool CToolMonsterQuad::SetScript(CMonsterQuadRes *_pRes_, const char *script_, bool bEnter_)
{
    if (NULL == _pRes_ || NULL == script_)
        return false;

    if (bEnter_)
    {
        _pRes_->SetEnterScript(script_);
    }
    else
    {
        _pRes_->SetLeaveScript(script_);
    }

    return true;
}

bool CToolMonsterQuad::DoAddAutoTalk(CMonsterQuadRes *_pRes_, int id_, int time_, int nextTimeId_)
{
    //if (NULL == _pRes_)
        return false;

    NMonsterTool::CAddAutoTalk *mydo = new NMonsterTool::CAddAutoTalk(this);
    //mydo->SetData(_pRes_, CMonsterQuadRes::AutoTalk(id_, time_, nextTimeId_));
    NMonsterTool::CDeleteAutoTalk *undo = new NMonsterTool::CDeleteAutoTalk(this);
    //undo->SetData(_pRes_, _pRes_->GetAutoTalkCount());

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::AddAutoTalk(CMonsterQuadRes *_pRes_, const CMonsterQuadRes::AutoTalk &talk_)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->AddAutoTalk(talk_);

    return true;
}

bool CToolMonsterQuad::DoDeleteAutoTalk(CMonsterQuadRes *_pRes_, int index_)
{
    //if (NULL == _pRes_ || index_ < 0 || index_ >= _pRes_->GetAutoTalkCount())
        return false;

    NMonsterTool::CDeleteAutoTalk *mydo = new NMonsterTool::CDeleteAutoTalk(this);
    mydo->SetData(_pRes_, index_);
    NMonsterTool::CAddAutoTalk *undo = new NMonsterTool::CAddAutoTalk(this);
    //undo->SetData(_pRes_, *_pRes_->GetAutoTalk(index_));

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}
bool CToolMonsterQuad::DeleteAutoTalk(CMonsterQuadRes *_pRes_, int index_)
{
    //if (NULL == _pRes_ || index_ < 0 || index_ >= _pRes_->GetAutoTalkCount())
        return false;

    //_pRes_->DelAutoTalk(index_);

    return true;
}

bool CToolMonsterQuad::DoModifyAutoTalk(CMonsterQuadRes *_pRes_, int index_, int id_, int time_, int nextTimeId_)
{
    //if (NULL == _pRes_ || index_ < 0 || index_ >= _pRes_->GetAutoTalkCount())
        return false;

    NMonsterTool::CModifyAutoTalk *mydo = new NMonsterTool::CModifyAutoTalk(this);
    mydo->SetData(_pRes_, index_, id_, time_, nextTimeId_);
    NMonsterTool::CModifyAutoTalk *undo = new NMonsterTool::CModifyAutoTalk(this);
    //_pRes_->GetAutoTalk(index_, id_, time_, nextTimeId_);
    undo->SetData(_pRes_, index_, id_, time_, nextTimeId_);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::ModifyAutoTalk(CMonsterQuadRes *_pRes_, int index_, int id_, int time_, int nextTimeId_)
{
    //if (NULL == _pRes_ || index_ < 0 || index_ >= _pRes_->GetAutoTalkCount())
        return false;

    //_pRes_->SetAutoTalk(index_, id_, time_, nextTimeId_);

    return true;
}

bool CToolMonsterQuad::DoAddTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int stringId_, int probability_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount())
        return false;

    NMonsterTool::CAddTalk *mydo = new NMonsterTool::CAddTalk(this);
    //mydo->SetData(_pRes_, ownerIndex_, stringId_, probability_);
    NMonsterTool::CDeleteTalk *undo = new NMonsterTool::CDeleteTalk(this);
    //undo->SetData(_pRes_, ownerIndex_, _pRes_->GetTalkCount(ownerIndex_));

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}
bool CToolMonsterQuad::AddTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int stringId_, int probability_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount())
        return false;

    //_pRes_->AddTalk(ownerIndex_, stringId_, probability_);

    return true;
}

bool CToolMonsterQuad::DoDeleteTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount() ||
    //        index_ < 0 || index_ >= _pRes_->GetTalkCount(ownerIndex_))
        return false;

    NMonsterTool::CDeleteTalk *mydo = new NMonsterTool::CDeleteTalk(this);
    mydo->SetData(_pRes_, ownerIndex_, index_);
    NMonsterTool::CAddTalk *undo = new NMonsterTool::CAddTalk(this);
    int stringId, probability;
   // _pRes_->GetTalk(ownerIndex_, index_, stringId, probability);
    undo->SetData(_pRes_, ownerIndex_, stringId, probability);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);

}

bool CToolMonsterQuad::DeleteTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount() ||
    //        index_ < 0 || index_ >= _pRes_->GetTalkCount(ownerIndex_))
        return false;

    //_pRes_->DelTalk(ownerIndex_, index_);

    return true;
}

bool CToolMonsterQuad::DoModifyTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_, int stringId_, int probability_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount() ||
    //       index_ < 0 || index_ >= _pRes_->GetTalkCount(ownerIndex_))
        return false;

    NMonsterTool::CModifyTalk *mydo = new NMonsterTool::CModifyTalk(this);
    mydo->SetData(_pRes_, ownerIndex_, index_, stringId_, probability_);
    NMonsterTool::CModifyTalk *undo = new NMonsterTool::CModifyTalk(this);
    //_pRes_->GetTalk(ownerIndex_, index_, stringId_, probability_);
    undo->SetData(_pRes_, ownerIndex_, index_, stringId_, probability_);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::ModifyTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_, int stringId_, int probability_)
{
    //if (NULL == _pRes_ || ownerIndex_ < 0 || ownerIndex_ >= _pRes_->GetAutoTalkCount() ||
    //        index_ < 0 || index_ >= _pRes_->GetTalkCount(ownerIndex_))
        return false;

    //_pRes_->SetTalk(ownerIndex_, index_, stringId_, probability_);

    return true;
}

bool CToolMonsterQuad::DoSetMonsterVisible(CMonsterQuadRes *_pRes_, bool bVisible)
{
    if (NULL == _pRes_)
        return false;

    //if (bVisible == _pRes_->IsVisible())
        return false;

    NMonsterTool::CSetMonsterVisible *mydo = new NMonsterTool::CSetMonsterVisible(this);
    mydo->SetData(_pRes_, bVisible);
    NMonsterTool::CSetMonsterVisible *undo = new NMonsterTool::CSetMonsterVisible(this);
    undo->SetData(_pRes_, !bVisible);

    COpertaionPair *op = new COpertaionPair(mydo, undo);
    return m_opManager.Excute(op);
}

bool CToolMonsterQuad::SetMonsterVisible(CMonsterQuadRes *_pRes_, bool bVisible)
{
    if (NULL == _pRes_)
        return false;

    //_pRes_->SetVisible(bVisible);

    return true;
}

CToolMonsterQuad::CPickingVisitor::CPickingVisitor():
    m_bToPaste(false)
{

}

CToolMonsterQuad::CPickingVisitor::~CPickingVisitor()
{
    Reset();
}

bool CToolMonsterQuad::CPickingVisitor::PickModels(CMonsterQuadRes *pModels_, UINT size_)
{
    if (NULL == pModels_)
        return true;

    for (UINT i = 0; i < size_; ++i)
    {
        CMonsterQuadRes *pModel = pModels_[i].Clone();
        m_pickedModels.push_back(pModel);
    }

    return true;
}

bool CToolMonsterQuad::CPickingVisitor::PasteModels(CPoint point_)
{
    UpdateModels(point_);

    for (TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
    {
        if (*it != NULL && m_pObject != NULL)
        {
            m_pObject->DoPasteMonsterQuad(*it);
        }
    }

    return true;
}

void CToolMonsterQuad::CPickingVisitor::Render()
{
    if (!IsToPaste())
        return;

    float alpha = 1.0f;
    for (TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
    {
        if (NULL == *it)
            continue;

        TObjectEditInfo *pModel = (*it)->GetModel();
        if (pModel != NULL)
            pModel->Render(alpha);
    }
}

void CToolMonsterQuad::CPickingVisitor::Reset()
{
    for (TPickModels::iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
    {
        if (*it != NULL)
        {
            MeDelete *it;
        }
    }
    m_pickedModels.clear();

    m_bToPaste = false;
}

void CToolMonsterQuad::CPickingVisitor::SetPaste()
{
    m_bToPaste = true;
}

bool CToolMonsterQuad::CPickingVisitor::IsToPaste()
{
    return m_bToPaste;
}

void CToolMonsterQuad::CPickingVisitor::UpdateModels(CPoint point_)
{
    if (m_pickedModels.empty())
        return;

    flt32 pos[3];
    if (!NHelper::ScreenToWorld(point_, pos))
        return;

    //这里需要计算一个偏移量，即每个model相对于pos(鼠标所在点)的偏移量
	/*
    bool bValid = false;;	//指示偏移量是否有效。
    float yOffset, xOffset;
    for (TPickModels::const_iterator it = m_pickedModels.begin(); it != m_pickedModels.end(); ++it)
    {
        CMonsterQuadRes *pModel = *it;
        if (NULL == pModel)
            continue;

        //计算偏移量
        if (!bValid)
        {
            yOffset = pos[1] + 0.5f - pModel->GetTop();
            xOffset = pos[0] - 0.5f - pModel->GetLeft();

            bValid = true;
        }

        pModel->m_fTop = pModel->m_fTop + yOffset;
        pModel->m_fLeft = pModel->m_fLeft + xOffset;
        pModel->m_fBottom = pModel->m_fBottom + yOffset;
        pModel->m_fRight = pModel->m_fRight + xOffset;
        pModel->ApplyTransform();
    }*/
}

bool CToolMonsterQuad::CPickingVisitor::OnMouseMove( UINT nFlags, CPoint point )
{
    UpdateModels(point);

    return true;
}



