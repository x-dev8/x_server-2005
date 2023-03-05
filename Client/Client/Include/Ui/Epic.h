/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\Epic.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_Epic
#define ID_FRAME_Epic		"ID_FRAME_Epic"
#endif  ID_FRAME_Epic
#ifndef ID_PICTURE_Left
#define ID_PICTURE_Left		"ID_PICTURE_Left"
#endif  ID_PICTURE_Left
#ifndef ID_PICTURE_Right
#define ID_PICTURE_Right		"ID_PICTURE_Right"
#endif  ID_PICTURE_Right
#ifndef ID_PICTURE_Middle
#define ID_PICTURE_Middle		"ID_PICTURE_Middle"
#endif  ID_PICTURE_Middle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Score
#define ID_TEXT_Score		"ID_TEXT_Score"
#endif  ID_TEXT_Score
#ifndef ID_TEXT_NPC
#define ID_TEXT_NPC		"ID_TEXT_NPC"
#endif  ID_TEXT_NPC
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_CHECKBOX_Chapter0
#define ID_CHECKBOX_Chapter0		"ID_CHECKBOX_Chapter0"
#endif  ID_CHECKBOX_Chapter0
#ifndef ID_CHECKBOX_Chapter6
#define ID_CHECKBOX_Chapter6		"ID_CHECKBOX_Chapter6"
#endif  ID_CHECKBOX_Chapter6
#ifndef ID_CHECKBOX_Chapter2
#define ID_CHECKBOX_Chapter2		"ID_CHECKBOX_Chapter2"
#endif  ID_CHECKBOX_Chapter2
#ifndef ID_CHECKBOX_Chapter3
#define ID_CHECKBOX_Chapter3		"ID_CHECKBOX_Chapter3"
#endif  ID_CHECKBOX_Chapter3
#ifndef ID_CHECKBOX_Chapter4
#define ID_CHECKBOX_Chapter4		"ID_CHECKBOX_Chapter4"
#endif  ID_CHECKBOX_Chapter4
#ifndef ID_CHECKBOX_Chapter5
#define ID_CHECKBOX_Chapter5		"ID_CHECKBOX_Chapter5"
#endif  ID_CHECKBOX_Chapter5
#ifndef ID_CHECKBOX_Chapter1
#define ID_CHECKBOX_Chapter1		"ID_CHECKBOX_Chapter1"
#endif  ID_CHECKBOX_Chapter1
#ifndef ID_CHECKBOX_Chapter7
#define ID_CHECKBOX_Chapter7		"ID_CHECKBOX_Chapter7"
#endif  ID_CHECKBOX_Chapter7
#ifndef ID_CHECKBOX_Node1
#define ID_CHECKBOX_Node1		"ID_CHECKBOX_Node1"
#endif  ID_CHECKBOX_Node1
#ifndef ID_CHECKBOX_Node2
#define ID_CHECKBOX_Node2		"ID_CHECKBOX_Node2"
#endif  ID_CHECKBOX_Node2
#ifndef ID_CHECKBOX_Node3
#define ID_CHECKBOX_Node3		"ID_CHECKBOX_Node3"
#endif  ID_CHECKBOX_Node3
#ifndef ID_PICTURE_EFFECT1
#define ID_PICTURE_EFFECT1		"ID_PICTURE_EFFECT1"
#endif  ID_PICTURE_EFFECT1
#ifndef ID_PICTURE_EFFECT2
#define ID_PICTURE_EFFECT2		"ID_PICTURE_EFFECT2"
#endif  ID_PICTURE_EFFECT2
#ifndef ID_PICTURE_EFFECT3
#define ID_PICTURE_EFFECT3		"ID_PICTURE_EFFECT3"
#endif  ID_PICTURE_EFFECT3

class CUI_ID_FRAME_Epic : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_Epic();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool OnFrameRenderNeedRedraw();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_Chapter0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Chapter7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Node1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Node2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Node3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

    virtual void InitializeAtEnterWorld();
	virtual void ResetDevice( );

	ControlFrame* GetFrame(){return m_pID_FRAME_Epic;}

	void SetSelectIndex(int index){m_SelectIndex = index;}
private:
	ControlFrame*	m_pID_FRAME_Epic;
	ControlPicture*	m_pID_PICTURE_Left;
	ControlPicture*	m_pID_PICTURE_Right;
	ControlPicture*	m_pID_PICTURE_Middle;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlText*	m_pID_TEXT_Score;
	ControlText*	m_pID_TEXT_NPC;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter0;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter6;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter2;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter3;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter4;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter5;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter1;
	ControlCheckBox*	m_pID_CHECKBOX_Chapter7;
	ControlCheckBox*	m_pID_CHECKBOX_Node1;
	ControlCheckBox*	m_pID_CHECKBOX_Node2;
	ControlCheckBox*	m_pID_CHECKBOX_Node3;
	ControlPicture*	    m_pID_PICTURE_EFFECT1;
	ControlPicture*	    m_pID_PICTURE_EFFECT2;
	ControlPicture*	    m_pID_PICTURE_EFFECT3;

	ControlGroup    m_Group;
public:
	void InitAnim();
	void Update();
	int  GetMoveDis();
	void InitButtonData();
	void UpdateChapter(int nChapter);
	void UpdatePage(int nChapter,int nPage);
	void UpdateTaskPic(int nChapter,int nPage);
	void UpdateScore(int nValue);
	void DrawLeftPic(RECT &rc);
private:
	DWORD m_dwBeginTime;
	bool  m_bPlaying; //是否播放动画
	int   m_nDisLen;  //移动长度
public:
	struct Page
	{
		int nQuestId;
		std::string bgPic;   //背景图片 未接任务
		RECT        bgRect;  
		std::string SelPic;  //选中任务
		RECT        SelRect;
		std::string DisablePic; //未接任务
		RECT        DisableRect;
		std::string DesPic;  //描述行图片
		Page()
		{
			nQuestId = -1;
			bgPic.clear();
			SelPic.clear();
			DisablePic.clear();
			DesPic.clear();
		}
	};

	struct Chapter
	{
		std::vector<Page> set;
	};
	bool LoadHistory();
private:
	std::vector<Chapter> m_vecSet;
	int                  m_MoveTime; //移动时间
private:
	int m_SelectIndex;  //当前选项
	int m_nSelPage;     //当前页选项
public:
	void Init2DAniPos(int nIndex);
	void ProcessAni();
private:
	CSmartAnimation* GetCoolDownAniNotNULL();
	CSmartAnimation* m_pCoolDownAni;
	DWORD            m_dwStartTime;
};
extern CUI_ID_FRAME_Epic s_CUI_ID_FRAME_Epic;
