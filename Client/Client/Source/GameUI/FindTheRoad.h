/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Zxc\3Guo_Client_10.19\3Guo_Client_10.19\Data\Ui\FindTheRoad.h
*********************************************************************/

/*
 *	Author 2012-11-2 zhuxincong
 *	DESC: 需求不能
 */

#pragma once
#include "MeUi/MeUi.h"
#include <string>
#include <map>
#include <vector>
#include "UIBase.h"
#include "Kwamemap.h"


#ifndef ID_FRAME_FindRoad
#define ID_FRAME_FindRoad		"ID_FRAME_FindRoad"
#endif  ID_FRAME_FindRoad
#ifndef ID_TEXT_Qidian
#define ID_TEXT_Qidian		"ID_TEXT_Qidian"
#endif  ID_TEXT_Qidian
#ifndef ID_TEXT_Yidongluji
#define ID_TEXT_Yidongluji		"ID_TEXT_Yidongluji"
#endif  ID_TEXT_Yidongluji
#ifndef ID_TEXT_FindRoad1
#define ID_TEXT_FindRoad1		"ID_TEXT_FindRoad1"
#endif  ID_TEXT_FindRoad1
#ifndef ID_TEXT_FindRoad2
#define ID_TEXT_FindRoad2		"ID_TEXT_FindRoad2"
#endif  ID_TEXT_FindRoad2
#ifndef ID_TEXT_FindRoad3
#define ID_TEXT_FindRoad3		"ID_TEXT_FindRoad3"
#endif  ID_TEXT_FindRoad3
#ifndef ID_TEXT_Zhongdian
#define ID_TEXT_Zhongdian		"ID_TEXT_Zhongdian"
#endif  ID_TEXT_Zhongdian
#ifndef ID_CHECKBOX_ChuanSong
#define ID_CHECKBOX_ChuanSong		"ID_CHECKBOX_ChuanSong"
#endif  ID_CHECKBOX_ChuanSong
#ifndef ID_TEXT_FindRoad4
#define ID_TEXT_FindRoad4		"ID_TEXT_FindRoad4"
#endif  ID_TEXT_FindRoad4
#ifndef	ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif
#ifndef ID_BUTTON_Begin    
#define ID_BUTTON_Begin  "ID_BUTTON_Begin"
#endif

#define MAX_TEXT_COUNT 4

class CUI_ID_FRAME_FindRoad : public CUIBase 
{
	// Member
public:	
	 CUI_ID_FRAME_FindRoad();
	 ControlFrame*	m_pID_FRAME_FindRoad;
	 ControlText*	m_pID_TEXT_Qidian;
	 ControlText*	m_pID_TEXT_Yidongluji;
	 ControlText*	m_pID_TEXT_FindRoad[MAX_TEXT_COUNT];
	 ControlText*	m_pID_TEXT_Zhongdian;
	 ControlCheckBox*	m_pID_CHECKBOX_ChuanSong;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlButton* m_pID_BUTTON_Begin;
	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_ChuanSongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool  ID_BUTTON_BeginOnButtonClick(ControlObject* pSender);

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	//bool findline(int targetid,int startid,int nNpcId = NULL);

	void Refresh();
	bool RefreshChuansongdian(int targetid,int startid,int nNpcId = NULL);
	void CloseText();

	//////////////////////////////////////////////////////////////////////////////////
	void SetTargetInfo(int startid,int tragetid,float targetx,float targety,int target_npcid = -1);
	bool RefreshRoadInfo(bool bCheck = false,bool _value = false);
	bool ProcessMultMoving();                                                //处理跨多地图自动寻路
	bool IsMultMove(){return bIsMultMove;}
	void ResetRoadInfo();

	void RefreshWalkLineText();//刷新行走路线的路线信息
	void RefreshTransmitLineText();//刷新传送路线的路线信息
private:
	//bool check_npcid;
	//int ntargetid,nstartid,nTheNpcID;
	string strRoadMapname[MAX_TEXT_COUNT];
	bool bIsMultMove;

	CKwamemap::SWalkLine _WalkLine;
	CKwamemap::STransmitLine _TransmitLine;

	int target_npc_id;
	int start_id;           //当前地图ID 
	int target_id;          //最终的MAPID
	float ftarget_X;			//最终的X坐标
	float ftarget_Y;			//最终的Y坐标
};
extern CUI_ID_FRAME_FindRoad s_CUI_ID_FRAME_FindRoad;