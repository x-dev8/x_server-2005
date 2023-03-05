/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\商城UI\ShopCenter.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "PlayerAnimCtrl.h"
#include "MessageDefine.h"
#include "TradeCenterInfo.h"
#include "Player.h"

#ifndef ID_FRAME_ShopCenter
#define ID_FRAME_ShopCenter		"ID_FRAME_ShopCenter"
#endif  ID_FRAME_ShopCenter
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_PICTURE_TitleLeftMiddle
#define ID_PICTURE_TitleLeftMiddle		"ID_PICTURE_TitleLeftMiddle"
#endif  ID_PICTURE_TitleLeftMiddle
#ifndef ID_PICTURE_TitleRightMiddle
#define ID_PICTURE_TitleRightMiddle		"ID_PICTURE_TitleRightMiddle"
#endif  ID_PICTURE_TitleRightMiddle
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_PICTURE_AllItemWall
#define ID_PICTURE_AllItemWall		"ID_PICTURE_AllItemWall"
#endif  ID_PICTURE_AllItemWall
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_GoldWall
#define ID_PICTURE_GoldWall		"ID_PICTURE_GoldWall"
#endif  ID_PICTURE_GoldWall
#ifndef ID_PICTURE_GoldWall1
#define ID_PICTURE_GoldWall1		"ID_PICTURE_GoldWall1"
#endif  ID_PICTURE_GoldWall1
#ifndef ID_TEXT_Jinyuanbao
#define ID_TEXT_Jinyuanbao		"ID_TEXT_Jinyuanbao"
#endif  ID_TEXT_Jinyuanbao
#ifndef ID_PICTURE_Yingyuanbao
#define ID_PICTURE_Yingyuanbao		"ID_PICTURE_Yingyuanbao"
#endif  ID_PICTURE_Yingyuanbao
#ifndef ID_PICTURE_money
#define ID_PICTURE_money		"ID_PICTURE_money"
#endif  ID_PICTURE_money
#ifndef ID_TEXT_Yingyuanbao
#define ID_TEXT_Yingyuanbao		"ID_TEXT_Yingyuanbao"
#endif  ID_TEXT_Yingyuanbao
#ifndef ID_TEXT_Yuanbao
#define ID_TEXT_Yuanbao		"ID_TEXT_Yuanbao"
#endif  ID_TEXT_Yuanbao
#ifndef ID_TEXT_Yuanbao22
#define ID_TEXT_Yuanbao22		"ID_TEXT_Yuanbao22"
#endif  ID_TEXT_Yuanbao22
#ifndef ID_PICTURE_InfoWall
#define ID_PICTURE_InfoWall		"ID_PICTURE_InfoWall"
#endif  ID_PICTURE_InfoWall
#ifndef ID_TEXT_ShopInfo
#define ID_TEXT_ShopInfo		"ID_TEXT_ShopInfo"
#endif  ID_TEXT_ShopInfo
#ifndef ID_CHECKBOX_Type1
#define ID_CHECKBOX_Type1		"ID_CHECKBOX_Type1"
#endif  ID_CHECKBOX_Type1
#ifndef ID_CHECKBOX_Type2
#define ID_CHECKBOX_Type2		"ID_CHECKBOX_Type2"
#endif  ID_CHECKBOX_Type2
#ifndef ID_CHECKBOX_Type3
#define ID_CHECKBOX_Type3		"ID_CHECKBOX_Type3"
#endif  ID_CHECKBOX_Type3
#ifndef ID_CHECKBOX_Type4
#define ID_CHECKBOX_Type4		"ID_CHECKBOX_Type4"
#endif  ID_CHECKBOX_Type4
#ifndef ID_CHECKBOX_Type5
#define ID_CHECKBOX_Type5		"ID_CHECKBOX_Type5"
#endif  ID_CHECKBOX_Type5
#ifndef ID_CHECKBOX_Type6
#define ID_CHECKBOX_Type6		"ID_CHECKBOX_Type6"
#endif  ID_CHECKBOX_Type6
#ifndef ID_CHECKBOX_Type7
#define ID_CHECKBOX_Type7		"ID_CHECKBOX_Type7"
#endif  ID_CHECKBOX_Type7
#ifndef ID_CHECKBOX_Type8
#define ID_CHECKBOX_Type8		"ID_CHECKBOX_Type8"
#endif  ID_CHECKBOX_Type8
#ifndef ID_PICTURE_ModelWall
#define ID_PICTURE_ModelWall		"ID_PICTURE_ModelWall"
#endif  ID_PICTURE_ModelWall
#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_BUTTON_Pay
#define ID_BUTTON_Pay		"ID_BUTTON_Pay"
#endif  ID_BUTTON_Pay
#ifndef ID_PICTURE_ItemWall1
#define ID_PICTURE_ItemWall1		"ID_PICTURE_ItemWall1"
#endif  ID_PICTURE_ItemWall1
#ifndef ID_PICTURE_ItemWall2
#define ID_PICTURE_ItemWall2		"ID_PICTURE_ItemWall2"
#endif  ID_PICTURE_ItemWall2
#ifndef ID_PICTURE_ItemWall3
#define ID_PICTURE_ItemWall3		"ID_PICTURE_ItemWall3"
#endif  ID_PICTURE_ItemWall3
#ifndef ID_PICTURE_ItemWall4
#define ID_PICTURE_ItemWall4		"ID_PICTURE_ItemWall4"
#endif  ID_PICTURE_ItemWall4
#ifndef ID_PICTURE_ItemWall5
#define ID_PICTURE_ItemWall5		"ID_PICTURE_ItemWall5"
#endif  ID_PICTURE_ItemWall5
#ifndef ID_PICTURE_ItemWall6
#define ID_PICTURE_ItemWall6		"ID_PICTURE_ItemWall6"
#endif  ID_PICTURE_ItemWall6
#ifndef ID_PICTURE_ItemWall7
#define ID_PICTURE_ItemWall7		"ID_PICTURE_ItemWall7"
#endif  ID_PICTURE_ItemWall7
#ifndef ID_PICTURE_ItemWall8
#define ID_PICTURE_ItemWall8		"ID_PICTURE_ItemWall8"
#endif  ID_PICTURE_ItemWall8
#ifndef ID_PICTURE_ItemWall9
#define ID_PICTURE_ItemWall9		"ID_PICTURE_ItemWall9"
#endif  ID_PICTURE_ItemWall9
#ifndef ID_PICTURE_ItemWall10
#define ID_PICTURE_ItemWall10		"ID_PICTURE_ItemWall10"
#endif  ID_PICTURE_ItemWall10
#ifndef ID_PICTURE_ItemWall11
#define ID_PICTURE_ItemWall11		"ID_PICTURE_ItemWall11"
#endif  ID_PICTURE_ItemWall11
#ifndef ID_PICTURE_ItemWall12
#define ID_PICTURE_ItemWall12		"ID_PICTURE_ItemWall12"
#endif  ID_PICTURE_ItemWall12
#ifndef ID_PICTURE_ItemWall13
#define ID_PICTURE_ItemWall13		"ID_PICTURE_ItemWall13"
#endif  ID_PICTURE_ItemWall13
#ifndef ID_PICTURE_ItemWall14
#define ID_PICTURE_ItemWall14		"ID_PICTURE_ItemWall14"
#endif  ID_PICTURE_ItemWall14
#ifndef ID_PICTURE_ItemWall15
#define ID_PICTURE_ItemWall15		"ID_PICTURE_ItemWall15"
#endif  ID_PICTURE_ItemWall15
#ifndef ID_BUTTON_LastPage
#define ID_BUTTON_LastPage		"ID_BUTTON_LastPage"
#endif  ID_BUTTON_LastPage
#ifndef ID_BUTTON_FirstPage
#define ID_BUTTON_FirstPage		"ID_BUTTON_FirstPage"
#endif  ID_BUTTON_FirstPage
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_LISTIMG_Item1
#define ID_LISTIMG_Item1		"ID_LISTIMG_Item1"
#endif  ID_LISTIMG_Item1
#ifndef ID_LISTIMG_Item2
#define ID_LISTIMG_Item2		"ID_LISTIMG_Item2"
#endif  ID_LISTIMG_Item2
#ifndef ID_LISTIMG_Item3
#define ID_LISTIMG_Item3		"ID_LISTIMG_Item3"
#endif  ID_LISTIMG_Item3
#ifndef ID_LISTIMG_Item4
#define ID_LISTIMG_Item4		"ID_LISTIMG_Item4"
#endif  ID_LISTIMG_Item4
#ifndef ID_LISTIMG_Item5
#define ID_LISTIMG_Item5		"ID_LISTIMG_Item5"
#endif  ID_LISTIMG_Item5
#ifndef ID_LISTIMG_Item6
#define ID_LISTIMG_Item6		"ID_LISTIMG_Item6"
#endif  ID_LISTIMG_Item6
#ifndef ID_LISTIMG_Item7
#define ID_LISTIMG_Item7		"ID_LISTIMG_Item7"
#endif  ID_LISTIMG_Item7
#ifndef ID_LISTIMG_Item8
#define ID_LISTIMG_Item8		"ID_LISTIMG_Item8"
#endif  ID_LISTIMG_Item8
#ifndef ID_LISTIMG_Item9
#define ID_LISTIMG_Item9		"ID_LISTIMG_Item9"
#endif  ID_LISTIMG_Item9
#ifndef ID_LISTIMG_Item10
#define ID_LISTIMG_Item10		"ID_LISTIMG_Item10"
#endif  ID_LISTIMG_Item10
#ifndef ID_LISTIMG_Item11
#define ID_LISTIMG_Item11		"ID_LISTIMG_Item11"
#endif  ID_LISTIMG_Item11
#ifndef ID_LISTIMG_Item12
#define ID_LISTIMG_Item12		"ID_LISTIMG_Item12"
#endif  ID_LISTIMG_Item12
#ifndef ID_LISTIMG_Item13
#define ID_LISTIMG_Item13		"ID_LISTIMG_Item13"
#endif  ID_LISTIMG_Item13
#ifndef ID_LISTIMG_Item14
#define ID_LISTIMG_Item14		"ID_LISTIMG_Item14"
#endif  ID_LISTIMG_Item14
#ifndef ID_LISTIMG_Item15
#define ID_LISTIMG_Item15		"ID_LISTIMG_Item15"
#endif  ID_LISTIMG_Item15
#ifndef ID_TEXT_Item1
#define ID_TEXT_Item1		"ID_TEXT_Item1"
#endif  ID_TEXT_Item1
#ifndef ID_TEXT_Item2
#define ID_TEXT_Item2		"ID_TEXT_Item2"
#endif  ID_TEXT_Item2
#ifndef ID_TEXT_Item3
#define ID_TEXT_Item3		"ID_TEXT_Item3"
#endif  ID_TEXT_Item3
#ifndef ID_TEXT_Item4
#define ID_TEXT_Item4		"ID_TEXT_Item4"
#endif  ID_TEXT_Item4
#ifndef ID_TEXT_Item5
#define ID_TEXT_Item5		"ID_TEXT_Item5"
#endif  ID_TEXT_Item5
#ifndef ID_TEXT_Item6
#define ID_TEXT_Item6		"ID_TEXT_Item6"
#endif  ID_TEXT_Item6
#ifndef ID_TEXT_Item7
#define ID_TEXT_Item7		"ID_TEXT_Item7"
#endif  ID_TEXT_Item7
#ifndef ID_TEXT_Item8
#define ID_TEXT_Item8		"ID_TEXT_Item8"
#endif  ID_TEXT_Item8
#ifndef ID_TEXT_Item9
#define ID_TEXT_Item9		"ID_TEXT_Item9"
#endif  ID_TEXT_Item9
#ifndef ID_TEXT_Item10
#define ID_TEXT_Item10		"ID_TEXT_Item10"
#endif  ID_TEXT_Item10
#ifndef ID_TEXT_Item11
#define ID_TEXT_Item11		"ID_TEXT_Item11"
#endif  ID_TEXT_Item11
#ifndef ID_TEXT_Item12
#define ID_TEXT_Item12		"ID_TEXT_Item12"
#endif  ID_TEXT_Item12
#ifndef ID_TEXT_Item13
#define ID_TEXT_Item13		"ID_TEXT_Item13"
#endif  ID_TEXT_Item13
#ifndef ID_TEXT_Item14
#define ID_TEXT_Item14		"ID_TEXT_Item14"
#endif  ID_TEXT_Item14
#ifndef ID_TEXT_Item15
#define ID_TEXT_Item15		"ID_TEXT_Item15"
#endif  ID_TEXT_Item15
#ifndef ID_TEXT_ItemPrice1
#define ID_TEXT_ItemPrice1		"ID_TEXT_ItemPrice1"
#endif  ID_TEXT_ItemPrice1
#ifndef ID_TEXT_ItemPrice2
#define ID_TEXT_ItemPrice2		"ID_TEXT_ItemPrice2"
#endif  ID_TEXT_ItemPrice2
#ifndef ID_TEXT_ItemPrice3
#define ID_TEXT_ItemPrice3		"ID_TEXT_ItemPrice3"
#endif  ID_TEXT_ItemPrice3
#ifndef ID_TEXT_ItemPrice4
#define ID_TEXT_ItemPrice4		"ID_TEXT_ItemPrice4"
#endif  ID_TEXT_ItemPrice4
#ifndef ID_TEXT_ItemPrice5
#define ID_TEXT_ItemPrice5		"ID_TEXT_ItemPrice5"
#endif  ID_TEXT_ItemPrice5
#ifndef ID_TEXT_ItemPrice6
#define ID_TEXT_ItemPrice6		"ID_TEXT_ItemPrice6"
#endif  ID_TEXT_ItemPrice6
#ifndef ID_TEXT_ItemPrice7
#define ID_TEXT_ItemPrice7		"ID_TEXT_ItemPrice7"
#endif  ID_TEXT_ItemPrice7
#ifndef ID_TEXT_ItemPrice8
#define ID_TEXT_ItemPrice8		"ID_TEXT_ItemPrice8"
#endif  ID_TEXT_ItemPrice8
#ifndef ID_TEXT_ItemPrice9
#define ID_TEXT_ItemPrice9		"ID_TEXT_ItemPrice9"
#endif  ID_TEXT_ItemPrice9
#ifndef ID_TEXT_ItemPrice10
#define ID_TEXT_ItemPrice10		"ID_TEXT_ItemPrice10"
#endif  ID_TEXT_ItemPrice10
#ifndef ID_TEXT_ItemPrice11
#define ID_TEXT_ItemPrice11		"ID_TEXT_ItemPrice11"
#endif  ID_TEXT_ItemPrice11
#ifndef ID_TEXT_ItemPrice12
#define ID_TEXT_ItemPrice12		"ID_TEXT_ItemPrice12"
#endif  ID_TEXT_ItemPrice12
#ifndef ID_TEXT_ItemPrice13
#define ID_TEXT_ItemPrice13		"ID_TEXT_ItemPrice13"
#endif  ID_TEXT_ItemPrice13
#ifndef ID_TEXT_ItemPrice14
#define ID_TEXT_ItemPrice14		"ID_TEXT_ItemPrice14"
#endif  ID_TEXT_ItemPrice14
#ifndef ID_TEXT_ItemPrice15
#define ID_TEXT_ItemPrice15		"ID_TEXT_ItemPrice15"
#endif  ID_TEXT_ItemPrice15
#ifndef ID_TEXT_Hot1
#define ID_TEXT_Hot1		"ID_TEXT_Hot1"
#endif  ID_TEXT_Hot1
#ifndef ID_TEXT_Hot2
#define ID_TEXT_Hot2		"ID_TEXT_Hot2"
#endif  ID_TEXT_Hot2
#ifndef ID_TEXT_Hot3
#define ID_TEXT_Hot3		"ID_TEXT_Hot3"
#endif  ID_TEXT_Hot3
#ifndef ID_TEXT_Hot4
#define ID_TEXT_Hot4		"ID_TEXT_Hot4"
#endif  ID_TEXT_Hot4
#ifndef ID_TEXT_Hot5
#define ID_TEXT_Hot5		"ID_TEXT_Hot5"
#endif  ID_TEXT_Hot5
#ifndef ID_TEXT_Hot6
#define ID_TEXT_Hot6		"ID_TEXT_Hot6"
#endif  ID_TEXT_Hot6
#ifndef ID_TEXT_Hot7
#define ID_TEXT_Hot7		"ID_TEXT_Hot7"
#endif  ID_TEXT_Hot7
#ifndef ID_TEXT_Hot8
#define ID_TEXT_Hot8		"ID_TEXT_Hot8"
#endif  ID_TEXT_Hot8
#ifndef ID_TEXT_Hot9
#define ID_TEXT_Hot9		"ID_TEXT_Hot9"
#endif  ID_TEXT_Hot9
#ifndef ID_TEXT_Hot10
#define ID_TEXT_Hot10		"ID_TEXT_Hot10"
#endif  ID_TEXT_Hot10
#ifndef ID_TEXT_Hot11
#define ID_TEXT_Hot11		"ID_TEXT_Hot11"
#endif  ID_TEXT_Hot11
#ifndef ID_TEXT_Hot12
#define ID_TEXT_Hot12		"ID_TEXT_Hot12"
#endif  ID_TEXT_Hot12
#ifndef ID_TEXT_Hot13
#define ID_TEXT_Hot13		"ID_TEXT_Hot13"
#endif  ID_TEXT_Hot13
#ifndef ID_TEXT_Hot14
#define ID_TEXT_Hot14		"ID_TEXT_Hot14"
#endif  ID_TEXT_Hot14
#ifndef ID_TEXT_Hot15
#define ID_TEXT_Hot15		"ID_TEXT_Hot15"
#endif  ID_TEXT_Hot15
#ifndef ID_BUTTON_Change
#define ID_BUTTON_Change		"ID_BUTTON_Change"
#endif  ID_BUTTON_Change
#ifndef ID_TEXT_Wait
#define ID_TEXT_Wait		"ID_TEXT_Wait"
#endif  ID_TEXT_Wait

#ifndef ID_PICTURE_Fork1
#define ID_PICTURE_Fork1		"ID_PICTURE_Fork1"
#endif  ID_PICTURE_Fork1
#ifndef ID_PICTURE_Fork2
#define ID_PICTURE_Fork2		"ID_PICTURE_Fork2"
#endif  ID_PICTURE_Fork2
#ifndef ID_PICTURE_Fork3
#define ID_PICTURE_Fork3		"ID_PICTURE_Fork3"
#endif  ID_PICTURE_Fork3
#ifndef ID_PICTURE_Fork4
#define ID_PICTURE_Fork4		"ID_PICTURE_Fork4"
#endif  ID_PICTURE_Fork4
#ifndef ID_PICTURE_Fork5
#define ID_PICTURE_Fork5		"ID_PICTURE_Fork5"
#endif  ID_PICTURE_Fork5
#ifndef ID_PICTURE_Fork6
#define ID_PICTURE_Fork6		"ID_PICTURE_Fork6"
#endif  ID_PICTURE_Fork6
#ifndef ID_PICTURE_Fork7
#define ID_PICTURE_Fork7		"ID_PICTURE_Fork7"
#endif  ID_PICTURE_Fork7
#ifndef ID_PICTURE_Fork8
#define ID_PICTURE_Fork8		"ID_PICTURE_Fork8"
#endif  ID_PICTURE_Fork8
#ifndef ID_PICTURE_Fork9
#define ID_PICTURE_Fork9		"ID_PICTURE_Fork9"
#endif  ID_PICTURE_Fork9
#ifndef ID_PICTURE_Fork10
#define ID_PICTURE_Fork10		"ID_PICTURE_Fork10"
#endif  ID_PICTURE_Fork10
#ifndef ID_PICTURE_Fork11
#define ID_PICTURE_Fork11		"ID_PICTURE_Fork11"
#endif  ID_PICTURE_Fork11
#ifndef ID_PICTURE_Fork12
#define ID_PICTURE_Fork12		"ID_PICTURE_Fork12"
#endif  ID_PICTURE_Fork12
#ifndef ID_PICTURE_Fork13
#define ID_PICTURE_Fork13		"ID_PICTURE_Fork13"
#endif  ID_PICTURE_Fork13
#ifndef ID_PICTURE_Fork14
#define ID_PICTURE_Fork14		"ID_PICTURE_Fork14"
#endif  ID_PICTURE_Fork14
#ifndef ID_PICTURE_Fork15
#define ID_PICTURE_Fork15		"ID_PICTURE_Fork15"
#endif  ID_PICTURE_Fork15
#ifndef ID_CHECKBOX_SubType1
#define ID_CHECKBOX_SubType1		"ID_CHECKBOX_SubType1"
#endif  ID_CHECKBOX_SubType1
#ifndef ID_CHECKBOX_SubType2
#define ID_CHECKBOX_SubType2		"ID_CHECKBOX_SubType2"
#endif  ID_CHECKBOX_SubType2
#ifndef ID_CHECKBOX_SubType3
#define ID_CHECKBOX_SubType3		"ID_CHECKBOX_SubType3"
#endif  ID_CHECKBOX_SubType3
#ifndef ID_CHECKBOX_SubType4
#define ID_CHECKBOX_SubType4		"ID_CHECKBOX_SubType4"
#endif  ID_CHECKBOX_SubType4
#ifndef ID_CHECKBOX_SubType5
#define ID_CHECKBOX_SubType5		"ID_CHECKBOX_SubType5"
#endif  ID_CHECKBOX_SubType5
#ifndef ID_CHECKBOX_SubType6
#define ID_CHECKBOX_SubType6		"ID_CHECKBOX_SubType6"
#endif  ID_CHECKBOX_SubType6
#ifndef ID_CHECKBOX_SubType7
#define ID_CHECKBOX_SubType7		"ID_CHECKBOX_SubType7"
#endif  ID_CHECKBOX_SubType7
#ifndef ID_CHECKBOX_SubType8
#define ID_CHECKBOX_SubType8		"ID_CHECKBOX_SubType8"
#endif  ID_CHECKBOX_SubType8
#ifndef ID_CHECKBOX_SubType9
#define ID_CHECKBOX_SubType9		"ID_CHECKBOX_SubType9"
#endif  ID_CHECKBOX_SubType9
#ifndef ID_CHECKBOX_SubType10
#define ID_CHECKBOX_SubType10		"ID_CHECKBOX_SubType10"
#endif  ID_CHECKBOX_SubType10

#ifndef ID_TEXT_IntegralShow
#define ID_TEXT_IntegralShow		"ID_TEXT_IntegralShow"
#endif  ID_TEXT_IntegralShow



#include "UiBase.h"

class CUI_ID_FRAME_ShopCenter :public CUIBase, public CUIRenderAnim
{
	// Member
private:	
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_ShopCenter;
	ControlPicture*	m_pID_PICTURE_Wall1;
	ControlPicture*	m_pID_PICTURE_TitleDi;
	ControlPicture*	m_pID_PICTURE_TitleWord;
	ControlPicture*	m_pID_PICTURE_TitleLeftMiddle;
	ControlPicture*	m_pID_PICTURE_TitleRightMiddle;
	ControlPicture*	m_pID_PICTURE_TitleLeft;
	ControlPicture*	m_pID_PICTURE_TitleRight;
	//ControlPicture*	m_pID_PICTURE_AllItemWall;
	ControlButton*	m_pID_BUTTON_Close;
	ControlButton*	m_pID_BUTTON_Help;
// 	ControlPicture*	m_pID_PICTURE_GoldWall;
// 	ControlPicture*	m_pID_PICTURE_GoldWall1;
	ControlText*	m_pID_TEXT_Jinyuanbao;
	ControlPicture*	m_pID_PICTURE_Yingyuanbao;
	ControlPicture*	m_pID_PICTURE_money;
	ControlText*	m_pID_TEXT_Yingyuanbao;
	ControlText*	m_pID_TEXT_Yuanbao;
	ControlText*	m_pID_TEXT_Yuanbao22;
 	ControlPicture*	m_pID_PICTURE_InfoWall;
// 	ControlText*	m_pID_TEXT_ShopInfo;
	ControlCheckBox*	m_pID_CHECKBOX_Type1;
	ControlCheckBox*	m_pID_CHECKBOX_Type2;
	ControlCheckBox*	m_pID_CHECKBOX_Type3;
	ControlCheckBox*	m_pID_CHECKBOX_Type4;
	ControlCheckBox*	m_pID_CHECKBOX_Type5;
	ControlCheckBox*	m_pID_CHECKBOX_Type6;
	ControlCheckBox*	m_pID_CHECKBOX_Type7;
	ControlCheckBox*	m_pID_CHECKBOX_Type8;
	ControlPicture*	m_pID_PICTURE_ModelWall;
	ControlButton*	m_pID_BUTTON_Reset;
	ControlButton*	m_pID_BUTTON_Right;
	ControlButton*	m_pID_BUTTON_Left;
	ControlButton*	m_pID_BUTTON_Pay;
	ControlPicture*	m_pID_PICTURE_ItemWall1;
	ControlPicture*	m_pID_PICTURE_ItemWall2;
	ControlPicture*	m_pID_PICTURE_ItemWall3;
	ControlPicture*	m_pID_PICTURE_ItemWall4;
	ControlPicture*	m_pID_PICTURE_ItemWall5;
	ControlPicture*	m_pID_PICTURE_ItemWall6;
	ControlPicture*	m_pID_PICTURE_ItemWall7;
	ControlPicture*	m_pID_PICTURE_ItemWall8;
	ControlPicture*	m_pID_PICTURE_ItemWall9;
	ControlPicture*	m_pID_PICTURE_ItemWall10;
	ControlPicture*	m_pID_PICTURE_ItemWall11;
	ControlPicture*	m_pID_PICTURE_ItemWall12;
	ControlPicture*	m_pID_PICTURE_ItemWall13;
	ControlPicture*	m_pID_PICTURE_ItemWall14;
	ControlPicture*	m_pID_PICTURE_ItemWall15;
	ControlButton*	m_pID_BUTTON_LastPage;
	ControlButton*	m_pID_BUTTON_FirstPage;
	ControlButton*	m_pID_BUTTON_PageDown;
	ControlButton*	m_pID_BUTTON_PageUp;
	ControlText*	m_pID_TEXT_Page;
	ControlListImage*	m_pID_LISTIMG_Item1;
	ControlListImage*	m_pID_LISTIMG_Item2;
	ControlListImage*	m_pID_LISTIMG_Item3;
	ControlListImage*	m_pID_LISTIMG_Item4;
	ControlListImage*	m_pID_LISTIMG_Item5;
	ControlListImage*	m_pID_LISTIMG_Item6;
	ControlListImage*	m_pID_LISTIMG_Item7;
	ControlListImage*	m_pID_LISTIMG_Item8;
	ControlListImage*	m_pID_LISTIMG_Item9;
	ControlListImage*	m_pID_LISTIMG_Item10;
	ControlListImage*	m_pID_LISTIMG_Item11;
	ControlListImage*	m_pID_LISTIMG_Item12;
	ControlListImage*	m_pID_LISTIMG_Item13;
	ControlListImage*	m_pID_LISTIMG_Item14;
	ControlListImage*	m_pID_LISTIMG_Item15;
	ControlText*	m_pID_TEXT_Item1;
	ControlText*	m_pID_TEXT_Item2;
	ControlText*	m_pID_TEXT_Item3;
	ControlText*	m_pID_TEXT_Item4;
	ControlText*	m_pID_TEXT_Item5;
	ControlText*	m_pID_TEXT_Item6;
	ControlText*	m_pID_TEXT_Item7;
	ControlText*	m_pID_TEXT_Item8;
	ControlText*	m_pID_TEXT_Item9;
	ControlText*	m_pID_TEXT_Item10;
	ControlText*	m_pID_TEXT_Item11;
	ControlText*	m_pID_TEXT_Item12;
	ControlText*	m_pID_TEXT_Item13;
	ControlText*	m_pID_TEXT_Item14;
	ControlText*	m_pID_TEXT_Item15;
	ControlText*	m_pID_TEXT_ItemPrice1;
	ControlText*	m_pID_TEXT_ItemPrice2;
	ControlText*	m_pID_TEXT_ItemPrice3;
	ControlText*	m_pID_TEXT_ItemPrice4;
	ControlText*	m_pID_TEXT_ItemPrice5;
	ControlText*	m_pID_TEXT_ItemPrice6;
	ControlText*	m_pID_TEXT_ItemPrice7;
	ControlText*	m_pID_TEXT_ItemPrice8;
	ControlText*	m_pID_TEXT_ItemPrice9;
	ControlText*	m_pID_TEXT_ItemPrice10;
	ControlText*	m_pID_TEXT_ItemPrice11;
	ControlText*	m_pID_TEXT_ItemPrice12;
	ControlText*	m_pID_TEXT_ItemPrice13;
	ControlText*	m_pID_TEXT_ItemPrice14;
	ControlText*	m_pID_TEXT_ItemPrice15;
	ControlText*	m_pID_TEXT_Hot1;
	ControlText*	m_pID_TEXT_Hot2;
	ControlText*	m_pID_TEXT_Hot3;
	ControlText*	m_pID_TEXT_Hot4;
	ControlText*	m_pID_TEXT_Hot5;
	ControlText*	m_pID_TEXT_Hot6;
	ControlText*	m_pID_TEXT_Hot7;
	ControlText*	m_pID_TEXT_Hot8;
	ControlText*	m_pID_TEXT_Hot9;
	ControlText*	m_pID_TEXT_Hot10;
	ControlText*	m_pID_TEXT_Hot11;
	ControlText*	m_pID_TEXT_Hot12;
	ControlText*	m_pID_TEXT_Hot13;
	ControlText*	m_pID_TEXT_Hot14;
	ControlText*	m_pID_TEXT_Hot15;
	ControlText*	m_pID_TEXT_Wait;

    ControlCheckBox*	m_pID_CHECKBOX_SubType1;
    ControlCheckBox*	m_pID_CHECKBOX_SubType2;
    ControlCheckBox*	m_pID_CHECKBOX_SubType3;
    ControlCheckBox*	m_pID_CHECKBOX_SubType4;
    ControlCheckBox*	m_pID_CHECKBOX_SubType5;
    ControlCheckBox*	m_pID_CHECKBOX_SubType6;
    ControlCheckBox*	m_pID_CHECKBOX_SubType7;
    ControlCheckBox*	m_pID_CHECKBOX_SubType8;

	ControlText* m_pID_TEXT_IntegralShow;
//     ControlCheckBox*	m_pID_CHECKBOX_SubType9;
//     ControlCheckBox*	m_pID_CHECKBOX_SubType10;
public:
	CUI_ID_FRAME_ShopCenter();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PayOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LastPageOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FirstPageOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChangeOnButtonClick( ControlObject* pSender );

    void ID_CHECKBOX_SubType1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_SubType8OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
//     void ID_CHECKBOX_SubType9OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
//     void ID_CHECKBOX_SubType10OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

    void SetSubTypeBoxCheck(ControlObject *pSender,bool *pbChecked);


	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:



	//////////////////////////////////////////////////////////////////////////
	
	void ID_CHECKBOX_TypeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_FitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BuyOnButtonClick( ControlObject* pSender );

	ControlFrame* GetFrame() { return m_pID_FRAME_ShopCenter; }

	int FindItemCount(int nId);
	std::string GetTradeItemMoneyText(const CTradeCenterInfo::cTradeItem& item, int count = 1);
	void ToggleTab(ControlObject* pSender)
	{
		if( !m_pID_FRAME_ShopCenter )
			return;
		if (pSender != m_tabs.GetSelectRadio())
			m_nCurrPageIndex = 0;
		m_tabs.ToggleRadio(static_cast<ControlCheckBox*>(pSender));
	}
	bool Buy(int nItemId);
	void UpdatePlayerAnimCtrl(int fashion_suit_item = -1, int fashion_suit_model_id = InvalidLogicNumber);

	void RefreshMoney();
	void Refresh();

	void SetItemCount(unsigned short nId, int nCount)
	{
		if( !m_pID_FRAME_ShopCenter )
			return;
		for (int i = 0; i < m_nItemCount; ++i)
		{
			if (m_itemInfo[i].id == nId)
			{
				m_itemInfo[i].count = nCount;
				break;
			}
		}
	}
	void AddShopItem(unsigned short id, int count)
	{
		if( !m_pID_FRAME_ShopCenter )
			return;
		for (int i = 0; i < MaxItem; ++i)
		{
			if (m_itemInfo[i].id == InvalidLogicNumber)
			{
				m_itemInfo[i].id = id;
				m_itemInfo[i].count = count;
				m_nItemCount += 1;
				break;
			}
		}
	}

	void SetUpdateFlag( bool b ){ m_bUpdateFlag = b; }
	void SetNeedUpdate( bool b ){ m_bNeedUpdate = b; }

    void SetFindPath(unsigned int ustItemID);
    CTradeCenterInfo::cTradeItem* FindItem(int nId,char chtype);

	ControlRadioGroup& GetControlRadioGroup(){return m_tabs;}
private:
    ControlRadioGroup m_SubTabs;  //子类型CheckBox

	static const int MaxItem = 200;

	unsigned short m_nItemCount;
	STradeItemInfo m_itemInfo[MaxItem];

	ControlRadioGroup m_tabs;
	//
	// item
	//
	std::vector<ControlListImage*> m_itemImages;
	std::vector<ControlText*> m_itemPrices;
	std::vector<ControlText*> m_itemNames;
	std::vector<ControlText*> m_itemStates;
	std::vector<ControlText*> m_itemTimeLimits;
	std::vector<ControlButton*> m_itemBuyBtns;
	std::vector<ControlPicture*> m_itemBackgrounds;
    std::vector<ControlPicture*> m_PitureFork;
	std::vector<ControlButton*> m_itemFitBtns;

	int m_nCurrPageIndex;
	int m_nPageCount;

	int m_nCurrBuyItemId;
	int m_nCurrPreviewMountID;

	static bool BuyCallback(const char* szInputData, void *pData);
	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );

	bool SetItemUI(const CTradeCenterInfo::cTradeItem& item, int nImageIndex);

	MeCamera			m_Camera;
	D3DVIEWPORT9		m_ViewPort;

	bool				m_bRotate;

	static bool CUI_ID_FRAME_ShopCenter::UI_RightLBD(INT nX, INT nY);
	static bool CUI_ID_FRAME_ShopCenter::UI_LeftLBD(INT nX, INT nY);

	//
	// broadcast
	//
	struct SMoveText
	{
		SMoveText()
		{
			m_nCount = 0;
			m_nX = m_nY = 0;
			m_fWidth = 0.f;
			m_dwColor = 0xffffffff;
		}
		std::string m_strText;
		int			m_nCount;
		int			m_nX;
		int			m_nY;
		float		m_fWidth;
		float		m_fMoveSpeed;
		DWORD		m_dwStartTime;
		DWORD		m_dwColor;
	};

	SMoveText	m_currMoveText;
	std::vector<std::string> m_broadcasts;

	void RenderBroadcast();
	
	bool m_bUpdateFlag;
	bool m_bNeedUpdate;
};
extern CUI_ID_FRAME_ShopCenter s_CUI_ID_FRAME_ShopCenter;
