/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\1Epic.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Epic.h"
#include "MeUi\UiRender.h"
#include "RapidXml/MeRapidXml.h"
#include "Common.h"
#include "QuestManager.h"
#include "PlayerRole.h"
#include "MeUi/Animation/XmlAnimation.h"

extern const char* GetRootPath();
CUI_ID_FRAME_Epic s_CUI_ID_FRAME_Epic;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Epic, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Epic, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Epic, OnFrameRenderNeedRedraw )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter0OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Chapter7OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Node1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Node2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Epic, ID_CHECKBOX_Node3OnCheckBoxCheck )
CUI_ID_FRAME_Epic::CUI_ID_FRAME_Epic()
{
	// Member
	m_pID_FRAME_Epic = NULL;
	m_pID_PICTURE_Left = NULL;
	m_pID_PICTURE_Right = NULL;
	m_pID_PICTURE_Middle = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Score = NULL;
	m_pID_TEXT_NPC = NULL;
	m_pID_CHECKBOX_Chapter0 = NULL;
	m_pID_CHECKBOX_Chapter6 = NULL;
	m_pID_CHECKBOX_Chapter2 = NULL;
	m_pID_CHECKBOX_Chapter3 = NULL;
	m_pID_CHECKBOX_Chapter4 = NULL;
	m_pID_CHECKBOX_Chapter5 = NULL;
	m_pID_CHECKBOX_Chapter1 = NULL;
	m_pID_CHECKBOX_Chapter7 = NULL;
	m_pID_CHECKBOX_Node1 = NULL;
	m_pID_CHECKBOX_Node2 = NULL;
	m_pID_CHECKBOX_Node3 = NULL;
	m_pID_PICTURE_EFFECT1 = NULL;
	m_pID_PICTURE_EFFECT2 = NULL;
	m_pID_PICTURE_EFFECT3 = NULL;

	m_dwBeginTime = 0;
	m_bPlaying = false;
}
// Frame
bool CUI_ID_FRAME_Epic::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_Epic::OnFrameRender()
{
	if(m_bPlaying)
	{
		Update();
	}
	DWORD dwNowTime = timeGetTime();
	if (dwNowTime-m_dwBeginTime >= 5*1000)		//根据策划要求，播放5秒后就设置隐藏
	{
		_SetVisable(false);
	}
	return true;
}

// Button
bool CUI_ID_FRAME_Epic::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(0);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(6);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(2);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(3);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(4);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(5);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(1);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Chapter7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateChapter(7);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Node1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateTaskPic(m_SelectIndex,0);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Node2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateTaskPic(m_SelectIndex,1);
}

// CheckBox
void CUI_ID_FRAME_Epic::ID_CHECKBOX_Node3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	UpdateTaskPic(m_SelectIndex,2);
}


// 装载UI
bool CUI_ID_FRAME_Epic::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Epic.MEUI",false,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Epic.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Epic::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Epic, s_CUI_ID_FRAME_EpicOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Epic, s_CUI_ID_FRAME_EpicOnFrameRender,true);
	theUiManager.OnButtonClick( ID_FRAME_Epic, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EpicID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter0, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter0OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter6, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter6OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter2, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter3, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter4, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter5, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter1, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Chapter7, s_CUI_ID_FRAME_EpicID_CHECKBOX_Chapter7OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Node1, s_CUI_ID_FRAME_EpicID_CHECKBOX_Node1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Node2, s_CUI_ID_FRAME_EpicID_CHECKBOX_Node2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Epic, ID_CHECKBOX_Node3, s_CUI_ID_FRAME_EpicID_CHECKBOX_Node3OnCheckBoxCheck );


	m_pID_FRAME_Epic = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Epic );
	m_pID_PICTURE_Left = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_Left );
	m_pID_PICTURE_Right = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_Right );
	m_pID_PICTURE_Middle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_Middle );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Epic, ID_BUTTON_CLOSE );
	m_pID_TEXT_Score = (ControlText*)theUiManager.FindControl( ID_FRAME_Epic, ID_TEXT_Score );
	m_pID_TEXT_NPC = (ControlText*)theUiManager.FindControl( ID_FRAME_Epic, ID_TEXT_NPC );
	m_pID_CHECKBOX_Chapter0 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter0 );
	m_pID_CHECKBOX_Chapter6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter6 );
	m_pID_CHECKBOX_Chapter2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter2 );
	m_pID_CHECKBOX_Chapter3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter3 );
	m_pID_CHECKBOX_Chapter4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter4 );
	m_pID_CHECKBOX_Chapter5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter5 );
	m_pID_CHECKBOX_Chapter1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter1 );
	m_pID_CHECKBOX_Chapter7 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Chapter7 );
	m_pID_CHECKBOX_Node1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Node1 );
	m_pID_CHECKBOX_Node2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Node2 );
	m_pID_CHECKBOX_Node3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Epic, ID_CHECKBOX_Node3 );
	m_pID_PICTURE_EFFECT1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_EFFECT1 );
	m_pID_PICTURE_EFFECT2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_EFFECT2 );
	m_pID_PICTURE_EFFECT3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Epic, ID_PICTURE_EFFECT3 );

	assert( m_pID_FRAME_Epic );
	assert( m_pID_PICTURE_Left );
	assert( m_pID_PICTURE_Right );
	assert( m_pID_PICTURE_Middle );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Score );
	assert( m_pID_TEXT_NPC );
	assert( m_pID_CHECKBOX_Chapter0 );
	assert( m_pID_CHECKBOX_Chapter6 );
	assert( m_pID_CHECKBOX_Chapter2 );
	assert( m_pID_CHECKBOX_Chapter3 );
	assert( m_pID_CHECKBOX_Chapter4 );
	assert( m_pID_CHECKBOX_Chapter5 );
	assert( m_pID_CHECKBOX_Chapter1 );
	assert( m_pID_CHECKBOX_Chapter7 );
	assert( m_pID_CHECKBOX_Node1 );
	assert( m_pID_CHECKBOX_Node2 );
	assert( m_pID_CHECKBOX_Node3 );
	assert( m_pID_PICTURE_EFFECT1 );
	assert( m_pID_PICTURE_EFFECT2 );
	assert( m_pID_PICTURE_EFFECT3 );

	m_Group.Clear();
	m_Group.AddControl(m_pID_CHECKBOX_Chapter0);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter1);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter2);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter3);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter4);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter5);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter6);
	m_Group.AddControl(m_pID_CHECKBOX_Chapter7);

	m_pID_FRAME_Epic->SetMsgHoldup(false); //LYH++ 不接受消息
	m_pID_FRAME_Epic->SetRenderNeedRedraw(s_CUI_ID_FRAME_EpicOnFrameRenderNeedRedraw);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_Epic::_UnLoadUI()
{
	if(m_pCoolDownAni)
	{
		delete m_pCoolDownAni;
		m_pCoolDownAni = NULL;
	}
	m_pID_FRAME_Epic = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Epic.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Epic::_IsVisable()
{
	if(!m_pID_FRAME_Epic)
		return false;

	return m_pID_FRAME_Epic->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Epic::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_Epic)
		return;

	m_pID_FRAME_Epic->SetVisable( bVisable );

	if(bVisable)
	{
		InitButtonData();
		m_dwStartTime = HQ_TimeGetTime();
	}
}

void CUI_ID_FRAME_Epic::InitAnim()
{
	if(!m_pID_FRAME_Epic)
		return;

	RECT rcLeft,rcRight;
	m_pID_PICTURE_Left->GetRectSize(&rcLeft);
	m_pID_PICTURE_Right->GetRectSize(&rcRight);

	//开始动画
	m_bPlaying = true;
	m_dwBeginTime = HQ_TimeGetTime();
	m_nDisLen = rcLeft.right - rcLeft.left + rcRight.right - rcRight.left;
}

void CUI_ID_FRAME_Epic::Update()
{
	if(!m_pID_FRAME_Epic)
		return;

	int nLen         = GetMoveDis();                  //距离

	RECT rcFrame;
	m_pID_FRAME_Epic->GetRealRect(&rcFrame);

	rcFrame.left = rcFrame.right - nLen;

	static int s_nLen = 0;
	RECT rcMiddle,rcLeft1;
	m_pID_PICTURE_Middle->GetRealRect(&rcMiddle);
	m_pID_PICTURE_Left->GetRealRect(&rcLeft1);

	//if(rcFrame.left <= rcMiddle.left - s_nLen)
	if(rcFrame.left <= rcLeft1.right)
	{
		//rcFrame.left = rcMiddle.left;
		m_pID_FRAME_Epic->GetRealRect(&rcFrame);
		m_pID_FRAME_Epic->SetWorking(rcFrame);
		m_pID_FRAME_Epic->GetFrameFather()->SetRedraw();
		m_bPlaying = false;
		return;
	}

	m_pID_FRAME_Epic->SetWorking(rcFrame);
	m_pID_FRAME_Epic->GetFrameFather()->SetRedraw();

	RECT rcLeft;
	m_pID_PICTURE_Left->GetRealRect(&rcLeft);

	RECT rc;
	rc.right  = rcFrame.left;
	rc.bottom = rcLeft.bottom;

	rc.left   = rc.right - m_pID_PICTURE_Left->GetWidth();
	rc.top    = rcLeft.top;

	DrawLeftPic(rc);	
}

int CUI_ID_FRAME_Epic::GetMoveDis()
{
	if(!m_pID_FRAME_Epic)
		return 0;

	RECT rc;
	m_pID_PICTURE_Middle->GetRealRect(&rc);
	int nWidth = rc.right - rc.left;   //获得宽度
	if(m_MoveTime == 0)
		m_MoveTime = 1;

	int nDis = nWidth/m_MoveTime;
	m_nDisLen += nDis;
	return m_nDisLen;
}

bool CUI_ID_FRAME_Epic::LoadHistory()
{
	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\Config\\Histroy.config",GetRootPath());

	MeXmlDocument MeXmlHistoryDoc ;
	if(!MeXmlHistoryDoc.LoadFile(szWord))
	{ return false; }

	MeXmlElement* pEpicElem = MeXmlHistoryDoc.FirstChildElement("Epic");
	if(!pEpicElem)
		return false;

	int nValue = 0;
	pEpicElem->Attribute("MoveTime",&nValue);
	m_MoveTime = nValue;

	MeXmlElement* pEpic = pEpicElem->FirstChildElement("Chapter");
	if(!pEpic)
		return false;

	m_vecSet.clear();
	for (;pEpic != NULL;pEpic = pEpic->NextSiblingElement())
	{
		MeXmlElement *pPageElem = pEpic->FirstChildElement("Page");
		Chapter chap;
		for (;pPageElem != NULL;pPageElem = pPageElem->NextSiblingElement())
		{
			Page page;
			int nValue = 0;
			if(pPageElem->Attribute("QuestId",&nValue) == NULL)
				return false;
			page.nQuestId = nValue;

			//未接任务
			Common::_tstring strPic = "";
			strPic.fromUTF8( pPageElem->Attribute("Pic") );
			page.bgPic = strPic;

			Common::_tstring strPicRect= "";
			strPicRect.fromUTF8(pPageElem->Attribute("PicRect"));
			if(sscanf_s(strPicRect.c_str(),"%d,%d,%d,%d",&page.bgRect.left,&page.bgRect.top,&page.bgRect.right,&page.bgRect.bottom) != 4)
				return false;

			//已经接受
			Common::_tstring strSelPic = "";
			strSelPic.fromUTF8(pPageElem->Attribute("SelectPic"));
			page.SelPic = strSelPic;

			Common::_tstring strSelPicRect= "";
			strSelPicRect.fromUTF8(pPageElem->Attribute("SelectRect"));
			if(sscanf_s(strSelPicRect.c_str(),"%d,%d,%d,%d",&page.SelRect.left,&page.SelRect.top,&page.SelRect.right,&page.SelRect.bottom) != 4)
				return false;

			//完成
			Common::_tstring strDisablePic = "";
			strDisablePic.fromUTF8(pPageElem->Attribute("DisablePic"));
			page.DisablePic = strDisablePic;

			Common::_tstring strDisablePicRect= "";
			strDisablePicRect.fromUTF8(pPageElem->Attribute("DisableRect"));
			if(sscanf_s(strDisablePicRect.c_str(),"%d,%d,%d,%d",&page.DisableRect.left,&page.DisableRect.top,&page.DisableRect.right,&page.DisableRect.bottom) != 4)
				return false;

			Common::_tstring strDisPic = "";
			strDisPic.fromUTF8(pPageElem->Attribute("DesPic"));
			page.DesPic = strDisPic;	
			chap.set.push_back(page);
		}
		m_vecSet.push_back(chap);
	}

	return true;
}

void CUI_ID_FRAME_Epic::InitButtonData()
{
	if(!m_pID_FRAME_Epic)
		return;

	if(m_vecSet.empty())
		return;

	ControlCheckBox *pCheckBox = NULL;
	int nSize = m_Group.GetControlSize();

	//默认全部灰态
	for (int i  = 0;i < nSize;++i)
	{
		pCheckBox = (ControlCheckBox*)m_Group.GetControl(i);
		pCheckBox->SetEnable(false);
	}
	
	//有任务则不是灰态
	for (int i = 0;i < nSize;++i)
	{
		if(i >= m_vecSet.size())
			break;

		Chapter *p = &m_vecSet[i];
		if(p->set.empty())
			continue;

		for (int n = 0; n < p->set.size();++n)
		{
			CPlayerRole::QuestInfo *pInfo = thePlayerRole.FindQuestInfoById(p->set[n].nQuestId);
			if(!pInfo)
				continue;

			if(theQuestManager.IsQuestDone(pInfo->chState) || theQuestManager.IsQuestActive(pInfo->chState))
			{
				pCheckBox = (ControlCheckBox*)m_Group.GetControl(i);
				pCheckBox->SetEnable(true);
				break;
			}
		}		
	}

	if(m_SelectIndex < 0 || m_SelectIndex >= m_Group.GetControlSize())
		return;

	pCheckBox = (ControlCheckBox*)m_Group.GetControl(m_SelectIndex);
	pCheckBox->SetCheck(true);


	UpdatePage(m_SelectIndex,0);
	UpdatePage(m_SelectIndex,1);
	UpdatePage(m_SelectIndex,2);
	UpdateTaskPic(m_SelectIndex,0);

	m_pID_CHECKBOX_Node1->SetCheck(true);
	m_pID_CHECKBOX_Node2->SetCheck(false);
	m_pID_CHECKBOX_Node3->SetCheck(false);

	m_nSelPage = 0;
}

void CUI_ID_FRAME_Epic::InitializeAtEnterWorld()
{
	LoadHistory();
	m_SelectIndex = 0;
	m_nSelPage = 0;
	m_pCoolDownAni = NULL;
    m_dwStartTime = 0;

	SetVisable(false);//触发加载
}


void CUI_ID_FRAME_Epic::UpdateChapter(int nChapter)
{
	if(nChapter < 0 || nChapter >= m_Group.GetControlSize())
		return;

	ControlCheckBox *pNewCheckBox = (ControlCheckBox*)m_Group.GetControl(nChapter);
	if(!pNewCheckBox)
		return;

	pNewCheckBox->SetCheck(true);
	if(nChapter == m_SelectIndex)
		return;

	ControlCheckBox *pOldCheckBox = (ControlCheckBox*)m_Group.GetControl(m_SelectIndex);
	if(!pOldCheckBox)
		return;

	pOldCheckBox->SetCheck(false);

	UpdatePage(nChapter,0);
	UpdatePage(nChapter,1);
	UpdatePage(nChapter,2);
	UpdateTaskPic(nChapter,0);

	m_pID_CHECKBOX_Node1->SetCheck(true);
	m_pID_CHECKBOX_Node2->SetCheck(false);
	m_pID_CHECKBOX_Node3->SetCheck(false);

	m_SelectIndex = nChapter;

	m_pID_FRAME_Epic->GetFrameFather()->SetRedraw();

	m_nSelPage = 0;
}

void CUI_ID_FRAME_Epic::UpdatePage(int nChapter,int nPage)
{
	if(!m_pID_FRAME_Epic)
		return;

	//设置任务按钮状态
	if(nChapter < 0 || nChapter >= m_vecSet.size())
		return;

	Chapter *pChap = &m_vecSet[nChapter];
	if(nPage < 0 || nPage >= pChap->set.size())
		return;

	Page* p = &pChap->set[nPage];   //获得页

	ControlCheckBox *pCheckBox = NULL;
	if(nPage == 0)
		pCheckBox = m_pID_CHECKBOX_Node1;
	else if(nPage == 1)
		pCheckBox = m_pID_CHECKBOX_Node2;
	else if(nPage == 2)
		pCheckBox = m_pID_CHECKBOX_Node3;
	else
		return;

	//设置按钮状态
	//获得任务状态
	CPlayerRole::QuestInfo *pInfo = thePlayerRole.FindQuestInfoById(p->nQuestId);
	if(!pInfo)
		return;

	if(!p->bgPic.empty())
	    pCheckBox->SetCheckPic(p->bgPic.c_str(), &p->bgRect, &p->bgRect );
	
	if(!p->SelPic.empty())
	    pCheckBox->SetUnCheckPic(p->SelPic.c_str(), &p->SelRect, &p->SelRect );

	if(!p->DisablePic.empty())
	    pCheckBox->SetDisablePic(p->DisablePic.c_str(), &p->DisableRect, &p->DisableRect );

	if (!theQuestManager.IsQuestDone(pInfo->chState)&&!theQuestManager.IsQuestActive(pInfo->chState))				
		pCheckBox->SetEnable(false);
	else
		pCheckBox->SetEnable(true);
	return;
}

void CUI_ID_FRAME_Epic::UpdateScore(int nValue)
{
	if(!m_pID_FRAME_Epic)
		return;

	//设置积分
	char szScore[64] = {0};
	MeSprintf_s(szScore,sizeof(szScore),"剧情积分:%d",nValue);
	m_pID_TEXT_Score->SetText(szScore);
}

void CUI_ID_FRAME_Epic::UpdateTaskPic(int nChapter,int nPage)
{
	if(!m_pID_FRAME_Epic)
		return;

	if(nChapter < 0 || nChapter >= m_vecSet.size())
		return;

	//获得章
	Chapter *pChap = &m_vecSet[nChapter];
	if(nPage < 0 || nPage >= pChap->set.size())
		return;

    //获得页
	Page* p = &pChap->set[nPage]; 
	if(p->DesPic.empty())
		return;

	char szPath[256] = {0};
	MeSprintf_s(szPath,sizeof(szPath),"Ui\\%s",p->DesPic.c_str());
	m_pID_PICTURE_Middle->SetPicName(szPath);

	switch (nPage)
	{
	case  0:
		{
			m_pID_CHECKBOX_Node1->SetCheck(true);
			m_pID_CHECKBOX_Node2->SetCheck(false);
			m_pID_CHECKBOX_Node3->SetCheck(false);
		}
		break;
	case 1:
		{
			m_pID_CHECKBOX_Node1->SetCheck(false);
			m_pID_CHECKBOX_Node2->SetCheck(true);
			m_pID_CHECKBOX_Node3->SetCheck(false);
		}
		break;
	case 2:
		{
			m_pID_CHECKBOX_Node1->SetCheck(false);
			m_pID_CHECKBOX_Node2->SetCheck(false);
			m_pID_CHECKBOX_Node3->SetCheck(true);
		}
		break;
	default:
		break;
	}

	m_nSelPage = nPage;
}

void CUI_ID_FRAME_Epic::DrawLeftPic(RECT &rc)
{
	if(!m_pID_FRAME_Epic)
		return;

	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\Ui\\%s",GetRootPath(),m_pID_PICTURE_Left->GetPic()->m_szPicName);

	S_BaseData* pData = m_pID_PICTURE_Left->GetData();
	//绘制背景
	int nPic = -1;
	theControlPictureManager.BitBlt(&nPic,szWord,&rc,&pData->m_stBackPic.m_rcFrame);
}

void CUI_ID_FRAME_Epic::Init2DAniPos(int nIndex)
{
	if(!m_pCoolDownAni)
		return;

	if(!m_pID_FRAME_Epic)
		return;

	ControlObject *pObject = NULL;
	switch(nIndex)
	{
	case 0:
		pObject = m_pID_PICTURE_EFFECT1;
		break;
	case 1:
		pObject = m_pID_PICTURE_EFFECT2;
		break;
	case 2:
		pObject = m_pID_PICTURE_EFFECT3;
		break;
	default:
		return;
	}

	RECT rc;
	pObject->GetRealRect(&rc);
	int nWidth = pObject->GetWidth();
	int nHeight = pObject->GetHeight();

	m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_X,rc.left + nWidth/2,NULL);
	m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Y,rc.top + nHeight/2,NULL);
	m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Width,nWidth,NULL);
	m_pCoolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Height,nHeight,NULL);
}


CSmartAnimation* CUI_ID_FRAME_Epic::GetCoolDownAniNotNULL()
{
	if(NULL == m_pCoolDownAni)
	{
		char szPath[256] = {0};
		MeSprintf_s(szPath,sizeof(szPath),"%s\\data\\ui\\UIAni\\Epic.2DAni", GetRootPath());
		m_pCoolDownAni = new CXmlAnimation( m_pID_FRAME_Epic->GetFrameRender() );

		MeXmlDocument doc;
		if(!doc.LoadFile(szPath))
		{
			assert(0);
			return m_pCoolDownAni;
		}

		MeXmlElement* pElement = doc.FirstChildElement("ProgressEffect");
		if(pElement)
		{
			CXmlAnimation* pSmart = (CXmlAnimation*)m_pCoolDownAni;
			pSmart->Initialize(pElement);
		}

		Init2DAniPos(m_nSelPage);
	}
	return m_pCoolDownAni;
}

void CUI_ID_FRAME_Epic::ResetDevice()
{
	Init2DAniPos(m_nSelPage);
}

void CUI_ID_FRAME_Epic::ProcessAni()
{
	DWORD dwCurTime = HQ_TimeGetTime();
	
	Init2DAniPos(m_nSelPage);
	CSmartAnimation* pCoolDownAni = GetCoolDownAniNotNULL();
	if(!pCoolDownAni->IsInAnimation())
	{
		m_pID_FRAME_Epic->GetUiAniManageNotNULL()->AddAnimation(pCoolDownAni);

		pCoolDownAni->StartAnimation(dwCurTime,dwCurTime - m_dwStartTime,true);
	}
	else
		pCoolDownAni->Redraw(dwCurTime);

}

bool CUI_ID_FRAME_Epic::OnFrameRenderNeedRedraw()
{
	ProcessAni();
	return true;
}
