/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Bin\Client\Data\Ui\NpcTaskDialogBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Progress.h"
#include "Me3d\Vector.h"
#include "GlobalDef.h"
#include "QuestDefine.h"
#include "XmlStringLanguage.h"
#include <map>

#ifndef NpcTaskDialogBox
#define NpcTaskDialogBox		"NpcTaskDialogBox"
#endif  NpcTaskDialogBox
#ifndef ID_PICTURE_Head
#define ID_PICTURE_Head		"ID_PICTURE_Head"
#endif  ID_PICTURE_Head
#ifndef ID_PICTURE_13294
#define ID_PICTURE_13294		"ID_PICTURE_13294"
#endif  ID_PICTURE_13294
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_PICTURE_22460
#define ID_PICTURE_22460		"ID_PICTURE_22460"
#endif  ID_PICTURE_22460
#ifndef ID_BUTTON_EXIT
#define ID_BUTTON_EXIT		"ID_BUTTON_EXIT"
#endif  ID_BUTTON_EXIT
#ifndef ID_PICTURE_10169
#define ID_PICTURE_10169		"ID_PICTURE_10169"
#endif  ID_PICTURE_10169
#ifndef ID_TEXT_Accepttext
#define ID_TEXT_Accepttext		"ID_TEXT_Accepttext"
#endif  ID_TEXT_Accepttext
#ifndef ID_BUTTON_Finish
#define ID_BUTTON_Finish		"ID_BUTTON_Finish"
#endif  ID_BUTTON_Finish
#ifndef ID_BUTTON_Accept
#define ID_BUTTON_Accept		"ID_BUTTON_Accept"
#endif  ID_BUTTON_Accept
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_TEXT_Taskstate
#define ID_TEXT_Taskstate		"ID_TEXT_Taskstate"
#endif  ID_TEXT_Taskstate
#ifndef ID_BUTTON_2366
#define ID_BUTTON_2366		"ID_BUTTON_2366"
#endif  ID_BUTTON_2366
#ifndef ID_TEXT_Taskreward
#define ID_TEXT_Taskreward		"ID_TEXT_Taskreward"
#endif  ID_TEXT_Taskreward
#ifndef ID_LISTIMG_Reward
#define ID_LISTIMG_Reward		"ID_LISTIMG_Reward"
#endif  ID_LISTIMG_Reward
#ifndef ID_BUTTON_Refuse
#define ID_BUTTON_Refuse		"ID_BUTTON_Refuse"
#endif  ID_BUTTON_Refuse
#ifndef ID_TEXT_JIN
#define ID_TEXT_JIN		"ID_TEXT_JIN"
#endif  ID_TEXT_JIN
#ifndef ID_TEXT_Ying
#define ID_TEXT_Ying		"ID_TEXT_Ying"
#endif  ID_TEXT_Ying
#ifndef ID_PICTURE_jin
#define ID_PICTURE_jin		"ID_PICTURE_jin"
#endif  ID_PICTURE_jin
#ifndef ID_PICTURE_ying
#define ID_PICTURE_ying		"ID_PICTURE_ying"
#endif  ID_PICTURE_ying
#ifndef ID_TEXT_Exp2
#define ID_TEXT_Exp2		"ID_TEXT_Exp2"
#endif  ID_TEXT_Exp2
#ifndef ID_TEXT_Exp
#define ID_TEXT_Exp		"ID_TEXT_Exp"
#endif  ID_TEXT_Exp
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Item
#define ID_TEXT_Item		"ID_TEXT_Item"
#endif  ID_TEXT_Item
#ifndef ID_TEXT_Finishtext
#define ID_TEXT_Finishtext		"ID_TEXT_Finishtext"
#endif  ID_TEXT_Finishtext
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_PICTURE_NpcHead
#define ID_PICTURE_NpcHead		"ID_PICTURE_NpcHead"
#endif  ID_PICTURE_NpcHead
#ifndef ID_TEXT_TitleZ
#define ID_TEXT_TitleZ		"ID_TEXT_TitleZ"
#endif  ID_TEXT_TitleZ
#ifndef ID_TEXT_FinallyItem
#define ID_TEXT_FinallyItem		"ID_TEXT_FinallyItem"
#endif  ID_TEXT_FinallyItem
#ifndef ID_LISTIMG_FinallyReward
#define ID_LISTIMG_FinallyReward		"ID_LISTIMG_FinallyReward"
#endif  ID_LISTIMG_FinallyReward
#ifndef ID_TEXT_MingWangZ
#define ID_TEXT_MingWangZ		"ID_TEXT_MingWangZ"
#endif  ID_TEXT_MingWangZ
#ifndef ID_TEXT_MingWang
#define ID_TEXT_MingWang		"ID_TEXT_MingWang"
#endif  ID_TEXT_MingWang
#ifndef ID_TEXT_RongYuZ
#define ID_TEXT_RongYuZ		"ID_TEXT_RongYuZ"
#endif  ID_TEXT_RongYuZ
#ifndef ID_TEXT_RongYu
#define ID_TEXT_RongYu		"ID_TEXT_RongYu"
#endif  ID_TEXT_RongYu
#ifndef ID_TEXT_GongXunZ
#define ID_TEXT_GongXunZ		"ID_TEXT_GongXunZ"
#endif  ID_TEXT_GongXunZ
#ifndef ID_TEXT_GongXun
#define ID_TEXT_GongXun		"ID_TEXT_GongXun"
#endif  ID_TEXT_GongXun
#ifndef ID_LISTIMG_FinallyReward2
#define ID_LISTIMG_FinallyReward2		"ID_LISTIMG_FinallyReward2"
#endif  ID_LISTIMG_FinallyReward2
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_TEXT_TaskAim
#define ID_TEXT_TaskAim		"ID_TEXT_TaskAim"
#endif  ID_TEXT_TaskAim
#ifndef ID_TEXT_SkillExpZ
#define ID_TEXT_SkillExpZ		"ID_TEXT_SkillExpZ"
#endif  ID_TEXT_SkillExpZ
#ifndef ID_TEXT_SkillExp
#define ID_TEXT_SkillExp		"ID_TEXT_SkillExp"
#endif  ID_TEXT_SkillExp
#ifndef ID_TEXT_EspecialMoneyZ
#define ID_TEXT_EspecialMoneyZ		"ID_TEXT_EspecialMoneyZ"
#endif  ID_TEXT_EspecialMoneyZ
#ifndef ID_TEXT_EspecialMoney
#define ID_TEXT_EspecialMoney		"ID_TEXT_EspecialMoney"
#endif  ID_TEXT_EspecialMoney
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LIST_SELECT
#define ID_LIST_SELECT		"ID_LIST_SELECT"
#endif  ID_LIST_SELECT
#ifndef ID_TEXT_W_Wenhao1
#define ID_TEXT_W_Wenhao1		"ID_TEXT_W_Wenhao1"
#endif  ID_TEXT_W_Wenhao1
#ifndef ID_TEXT_W_Wenhao2
#define ID_TEXT_W_Wenhao2		"ID_TEXT_W_Wenhao2"
#endif  ID_TEXT_W_Wenhao2
#ifndef ID_TEXT_W_Wenhao3
#define ID_TEXT_W_Wenhao3		"ID_TEXT_W_Wenhao3"
#endif  ID_TEXT_W_Wenhao3
#ifndef ID_TEXT_W_Wenhao4
#define ID_TEXT_W_Wenhao4		"ID_TEXT_W_Wenhao4"
#endif  ID_TEXT_W_Wenhao4
#ifndef ID_TEXT_W_Wenhao5
#define ID_TEXT_W_Wenhao5		"ID_TEXT_W_Wenhao5"
#endif  ID_TEXT_W_Wenhao5
#ifndef ID_TEXT_W_Wenhao6
#define ID_TEXT_W_Wenhao6		"ID_TEXT_W_Wenhao6"
#endif  ID_TEXT_W_Wenhao6
#ifndef ID_TEXT_W_Wenhao7
#define ID_TEXT_W_Wenhao7		"ID_TEXT_W_Wenhao7"
#endif  ID_TEXT_W_Wenhao7
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_PICTURE_Line1
#define ID_PICTURE_Line1		"ID_PICTURE_Line1"
#endif  ID_PICTURE_Line1
#ifndef ID_PICTURE_Line2
#define ID_PICTURE_Line2		"ID_PICTURE_Line2"
#endif  ID_PICTURE_Line2
#ifndef ID_PICTURE_Line3
#define ID_PICTURE_Line3		"ID_PICTURE_Line3"
#endif  ID_PICTURE_Line3
#ifndef ID_TEXT_Dialog
#define ID_TEXT_Dialog		"ID_TEXT_Dialog"
#endif  ID_TEXT_Dialog
#ifndef ID_LISTIMG_SecondItem
#define ID_LISTIMG_SecondItem		"ID_LISTIMG_SecondItem"
#endif  ID_LISTIMG_SecondItem
#ifndef ID_LIST_Task
#define ID_LIST_Task		"ID_LIST_Task"
#endif  ID_LIST_Task
#ifndef ID_SCROLLBAR_FRAME
#define ID_SCROLLBAR_FRAME		"ID_SCROLLBAR_FRAME"
#endif  ID_SCROLLBAR_FRAME
#ifndef ID_BUTTON_RETURN
#define ID_BUTTON_RETURN		"ID_BUTTON_RETURN"
#endif  ID_BUTTON_RETURN

#include "UIBase.h"
#define MAX_SELECT_ITEM	32

class ControlSet
{
public:
	ControlSet(){}

	void Clear()
	{
		m_ControlSet.clear();
		m_RectSet.clear();
	}
	void AddControl(ControlObject *pObject)
	{
		m_ControlSet.push_back(pObject);
		RECT rc;
		pObject->GetRectSize(&rc);
		m_RectSet.push_back(rc);
	}

	void UpdateControlRect(ControlObject *pObject)
	{
		for (int i = 0;i < m_ControlSet.size();++i)
		{
			if(m_ControlSet[i] == pObject)
			{
				RECT rc;
				pObject->GetRectSize(&rc);
				m_RectSet[i].left = rc.left;
				m_RectSet[i].top = rc.top;
				m_RectSet[i].right = rc.right;
				m_RectSet[i].bottom = rc.bottom;
				break;
			}
		}		
	}

	void ChangControlPos(int nIndex,int nTop,int nLeft)
	{
		if(nIndex <0 || nIndex >= m_ControlSet.size())
			return;

		ControlObject *pObject = m_ControlSet[nIndex];
		int nWidth = pObject->GetWidth();
		int nHeight = pObject->GetHeight();

		RECT rc;
		rc.left = nLeft;
		rc.top  = nTop;
		rc.right = rc.left + nWidth;
		rc.bottom = rc.top + nHeight;

		pObject->SetRealRect(&rc);		
	}

	void ChangePos(int n)
	{
		for (int i = 0;i < m_ControlSet.size();++i)
		{
			RECT *pRc = &m_RectSet[i];
			int nTop = pRc->top;
			int nLeft = pRc->left;
			nTop -= n;

			ChangControlPos(i,nTop,nLeft);
		}
	}

private:
	std::vector<ControlObject*> m_ControlSet;
	std::vector<RECT>           m_RectSet;
	typedef std::vector<ControlObject*> Iter;
};

class CUI_NpcTaskDialogBox : public CUIBase
{
	typedef bool (*funCallbackFun)(const int nSelectIndex,void *pData);
private:
	struct S_SelectBox 
	{
		S_SelectBox()
		{
			m_pCallbackFun = NULL;
			m_bModal = true;
			m_nItemCount = 0;
			memset(m_questState, 0, sizeof(m_questState));
		}
		std::string m_strCaption;
		std::string m_strInfo;
		bool m_bModal;
		ControlList::S_List	m_stItem[MAX_SELECT_ITEM];
		int		m_nItemCount;
		funCallbackFun	m_pCallbackFun;
		int m_nQuestCount;
		int m_questState[MAX_SELECT_ITEM];
	};
public:	
	CUI_NpcTaskDialogBox();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_EXITOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FinishOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_SELECTOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_SCROLLBAR_FRAMEOnScrollBarUpdatePos( ControlObject* pSender, int n );
	bool ID_BUTTON_RETURNOnButtonClick( ControlObject* pSender );

    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
    void Show(int type, const std::string& info, short nQuestId, const std::string& title);
	//SelectBox
	void Show( const char* szText, const ControlList::S_List* pItem, const int nItemCount,
		const char* szCaption = "", const bool bModal = true,
		const funCallbackFun pFun = NULL, const int nQuestCount = 0,
		const int* questInfos = 0);
	void ShowChatDialog(const std::string& strData,const std::string &title,bool bShowNext);
	void ShowIntonateBar(DWORD dwTime,const char* pName = NULL);
	void EndIntonateBar();
	void RetrieveNpcPic();
	void UpdateSelectBox();
	void ProcessBackEndScript();  //每次脚本结束会调用这条消息
	void ShowNextQuest(short nQuestId);
	void SendAllMsg();

	void SetButtonEnable( bool bEnabel );
	bool IsHaveComQuest(short nQuestId);
    bool IsPackSpaceEnough( int nQuestId );         // 背包空间是否足够完成任务

public:
	void SetNpc(int nId,bool bShow = true);
	int  GetNpc(){return m_nNpcId;}
	bool PopSelectBox();

	void BeginNpcScript(int nNpcId);
	void EndNpcScript();

	void SortControl();  //分类控件，目的只是放置函数过长
	void CloseDialog(bool bVisable = true);  //关闭界面
	bool IsButCloseVisable();
	void ParseExpressText(std::string &strParse,int &nExpressId);
public:
	enum eUIType
	{
		UI_Select,  //对应原来的selectBox.menu界面
		UI_NpcTask, //对应原来的NPcTaskDialogBox.menu界面
		UI_NpcChat  //对应原来的NpcChatDialogBox.menu界面
	};

	void SetUIType(eUIType eType);
	eUIType GetUIType(){return m_eUIType;}
private:
	void ResetAllControlObjects();
	void SetTaskInfo(short nQuestId,std::string &strInfo);
	bool UITask_ShowInfo( ControlList::S_List* pItem, COLORREF col,std::string &strInfo);
	bool IsShowProgress(){return m_ShowProgress;}
	void RefreshSelect();
	void UpdatePos(int n);
public:
	static void Text_Taskstate_HyberClick( ControlObject* pSender, const char* szData );
	static bool UINpcTask_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);
	static bool ScriptSellectCallbackFun( const int nSelectIndex, void *pData );
	static bool ScriptShowQuestDlgCallbackFun( const int nSelectIndex, void *pData ); 
	static void ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem );
	static void OnVisibleChanged(ControlObject *pObject);
	static void ID_LIST_SELECTTASKOnListDBClient(ControlObject *pSender, ControlList::S_List *pItem);
	static void UpdateScollPos(ControlObject *pSender,int n);
	ControlScrollBar*	m_pID_SCROLLBAR_FRAME;
    ControlFrame*	m_pNpcTaskDialogBox;
private:
    ControlButton*	m_pID_BUTTON_Finish;
    ControlButton*	m_pID_BUTTON_Accept;
    ControlButton*	m_pID_BUTTON_Close;
    ControlListImage*	m_pID_LISTIMG_Reward;
    ControlButton*	m_pID_BUTTON_Refuse;
    ControlText*	m_pID_TEXT_Item;
    ControlText*	m_pID_TEXT_FinallyItem;
	ControlButton*	m_pID_BUTTON_OK;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlList*	m_pID_LIST_SELECT;
	ControlText*	m_pID_TEXT_W_Wenhao1;
	ControlText*	m_pID_TEXT_W_Wenhao2;
	ControlText*	m_pID_TEXT_W_Wenhao3;
	ControlText*	m_pID_TEXT_W_Wenhao4;
	ControlText*	m_pID_TEXT_W_Wenhao5;
	ControlText*	m_pID_TEXT_W_Wenhao6;
	ControlText*	m_pID_TEXT_W_Wenhao7;
	ControlText*	m_pID_TEXT_Info;
	ControlButton*	m_pID_BUTTON_Next;
	ControlListImage*	m_pID_LISTIMG_SecondItem;
	ControlList*	m_pID_LIST_Task;
	ControlButton*	m_pID_BUTTON_RETURN;

	ControlGroup    m_SelectBoxGroup;      //对应原来的SelectBox.meui
	ControlGroup    m_TaskDialogGroup;     //对应原来的NpcTaskDialog.meui
	ControlGroup    m_ChatDialogGroup;     //对应原来的NpcChatDialog.meui

	std::vector<ControlText*> m_TextFlagSet;


private:
	void			PlayNpcSound();
	eUIType         m_eUIType;
	funCallbackFun	m_pCurCallbackFun;
	std::vector<S_SelectBox> m_vtSelectBox;
	int             m_nNpcId;
	bool			m_bPlaySound;
//	DWORD           m_dwLastTime;
    bool            m_ShowProgress;//是否显示进度条,因为进度条是服务器主动取消脚本的，所以单独处理
	bool            m_bFinishUI;
	bool            m_bSending;  //消息发送中
	short           m_nLastNpcId; //记录上次NpcID
	short           m_nLastQuestId;  //记录上次任务ID
public:
	bool        LocalShowTask(int nNpcId,bool bShow = true,bool bReturn = false);
	static bool LocalCallBack( const int nSelectIndex, void *pData );
	bool        SendBuffMsg(); //发送缓冲的消息
	void        SetBuffItemId(int nValue){m_BuffItemId = nValue;}
	int         GetBuffItemId(){return m_BuffItemId;}
	bool        GetFinishUI(){return m_bFinishUI;}
	void        SetFinishUI(bool bValue){m_bFinishUI = bValue;}
	void        UpdateButCD(){m_dwButCD = HQ_TimeGetTime();}
	DWORD       GetButCD(){return m_dwButCD;}
	bool        IsSending(){return m_bSending;}
	void		SetSending( bool bSending ){ m_bSending = bSending; }
	void        RefreshTask(short shQuestId);
	void        SetSelecting(bool bValue){m_dwSeleting = bValue;}
	bool        IsSetSelecting(){return m_dwSeleting;}
private:
	//为了快速见到任务界面,第一部有客户端自己来显示
	//步骤如下:1.客户端根据Npc.config中Menu这个字段，本地显示
	//         2.如果选取了一个选项，这时候，发MsgRegScript这个消息,同时保存选择的ID
	//         3.客户端收到了MsgAckScript消息的时候,在发送保存的选项ID,发送过去
	int             m_BuffItemId; //保存NPCID
	DWORD           m_dwButCD;
	bool            m_dwSeleting;
public:
	//任务进度条
	struct sTaskProgress
	{
		sTaskProgress()
		{
			m_bWaitIntonate = false;
			m_dwLastIntonateTime = 0;
			m_dwIntonatePressTime = 0;
			m_nItemID = 0;
		}

		bool m_bWaitIntonate;
		DWORD m_dwLastIntonateTime;
		DWORD m_dwIntonatePressTime;
		int m_nItemID;
		void  ShowTaskProgerss(DWORD dwTime,const char *pName)
		{
			m_bWaitIntonate = true;
			m_dwLastIntonateTime = HQ_TimeGetTime();
			m_dwIntonatePressTime = dwTime;
			s_CUI_Progress.ShowByTime(m_dwLastIntonateTime,m_dwIntonatePressTime,true,1,true,true,pName);
		}

		void Run()
		{
			if(!m_bWaitIntonate)
				return;

			if(HQ_TimeGetTime() - m_dwLastIntonateTime >= m_dwIntonatePressTime)
				m_bWaitIntonate = false;
		}

		bool IsIntonating(){return m_bWaitIntonate;}
		bool CanInterrupt() const;
		void EndIntonating()
		{
			m_bWaitIntonate = false;
			m_nItemID = 0;
			//s_CUI_Progress.SetVisable(false);
			s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );
		}
	};

	sTaskProgress m_TaskProgerss;
private:
	struct taskBuff 
	{
		int type;
		std::string info;
		short nQuestId;
		std::string title;
		taskBuff()
		{
			type = 0;
			info = "";
			nQuestId = -1;
			title = "";
		}
	};
	taskBuff m_taskBuff;
	DWORD    m_LastTaskBuff;
	bool     m_Waitting;
public:
	void ProcessVisualUI();
	void SetVisualPos(Vector &pos){m_VisualPos = pos;}
	void GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem);
	void GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem);
    void ShowRewareItem(int nTop,int nLeft);
	void ShowTaskList(int nTop,int nLeft);
private:
	Vector m_VisualPos;
	ControlSet m_ControlSet;
private:
	//任务选项图标
	struct sTaskIcon
	{
		int m_nType;
		std::string m_strNone;
		std::string m_strAct;
		std::string m_strDone;
		sTaskIcon()
		{
			m_nType = 0;
			m_strDone = "{#2101}";
			m_strAct  = "{#2102}";
			m_strNone = "{#2103}";
		}
	};
	std::map<int,sTaskIcon> m_IconSet;
public:
	void LoadTaskIcon();
	void GetTaskIcon(int nType,sTaskIcon &icon);
	void SetExpHeadId( short id ) { m_shExpHeadId = id; }
	void SetNeedCancel(bool bValue){m_bNeedCancel = bValue;}
	bool IsNeedCancel(){return m_bNeedCancel;}
private:
	bool m_bReturning;  //是否在返回中

	short m_shExpHeadId;

	//std::vector<__int64>	m_vtRequestItemUUID;//暂时测试用，保存要提交的物品
	//short m_nQuestID;			//任务ID

	bool m_bNeedCancel;
};
extern CUI_NpcTaskDialogBox s_CUI_NpcTaskDialogBox;