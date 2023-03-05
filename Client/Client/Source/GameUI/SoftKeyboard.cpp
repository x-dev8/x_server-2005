/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\SoftKeyboard.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SoftKeyboard.h"
#include <ctype.h>
#include "Login.h"

// 策划定的软键盘随机出现范围		added by ZhuoMeng.Hu		[8/31/2010]
#define POSAREA_XLEFT	0.467
#define POSAREA_XRIGHT	0.545
#define POSAREA_YTOP	0.764
#define POSAREA_YBOTTOM	0.843


static char s_lowerKeyNames[39][4] = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0", // 10
	"-",
	"q",
	"w",
	"e",
	"r",
	"t",
	"y",
	"u",
	"i",
	"o", // 20
	"p",
	"a",
	"s",
	"d",
	"f",
	"g",
	"h",
	"j",
	"k",
	"l", // 30
	";",
	"z",
	"x",
	"c",
	"v",
	"b",
	"n",
	"m",
	".", // 39
};

static char s_upperKeyNames[39][4] = {
	"!",
	"@",
	"#",
	"$",
	"%",
	"^",
	"&",
	"*",
	"(",
	")", // 10
	"_",
	"Q",
	"W",
	"E",
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O", // 20
	"P",
	"A",
	"S",
	"D",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L", // 30
	":",
	"Z",
	"X",
	"C",
	"V",
	"B",
	"N",
	"M",
	">", // 39
};

CUI_ID_FRAME_SoftKeyboard s_CUI_ID_FRAME_SoftKeyboard;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SoftKeyboard, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SoftKeyboard, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_BackSpaceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_CapsOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_5OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_6OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_7OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_8OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_9OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_10OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_11OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_12OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_13OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_14OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_15OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_16OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_17OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_18OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_19OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_20OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_21OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_22OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_23OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_24OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_25OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_26OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_27OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_28OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_29OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_30OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_31OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_32OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_33OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_34OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_35OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_36OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_37OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_38OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_BUTTON_39OnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftLeftOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftRightOnCheckBoxCheck )
CUI_ID_FRAME_SoftKeyboard::CUI_ID_FRAME_SoftKeyboard()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_SoftKeyboard::ResetMembers()
{
	m_pID_FRAME_SoftKeyboard = NULL;
	m_pID_BUTTON_1 = NULL;
	m_pID_BUTTON_BackSpace = NULL;
	m_pID_BUTTON_Caps = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_2 = NULL;
	m_pID_BUTTON_3 = NULL;
	m_pID_BUTTON_4 = NULL;
	m_pID_BUTTON_5 = NULL;
	m_pID_BUTTON_6 = NULL;
	m_pID_BUTTON_7 = NULL;
	m_pID_BUTTON_8 = NULL;
	m_pID_BUTTON_9 = NULL;
	m_pID_BUTTON_10 = NULL;
	m_pID_BUTTON_11 = NULL;
	m_pID_BUTTON_12 = NULL;
	m_pID_BUTTON_13 = NULL;
	m_pID_BUTTON_14 = NULL;
	m_pID_BUTTON_15 = NULL;
	m_pID_BUTTON_16 = NULL;
	m_pID_BUTTON_17 = NULL;
	m_pID_BUTTON_18 = NULL;
	m_pID_BUTTON_19 = NULL;
	m_pID_BUTTON_20 = NULL;
	m_pID_BUTTON_21 = NULL;
	m_pID_BUTTON_22 = NULL;
	m_pID_BUTTON_23 = NULL;
	m_pID_BUTTON_24 = NULL;
	m_pID_BUTTON_25 = NULL;
	m_pID_BUTTON_26 = NULL;
	m_pID_BUTTON_27 = NULL;
	m_pID_BUTTON_28 = NULL;
	m_pID_BUTTON_29 = NULL;
	m_pID_BUTTON_30 = NULL;
	m_pID_BUTTON_31 = NULL;
	m_pID_BUTTON_32 = NULL;
	m_pID_BUTTON_33 = NULL;
	m_pID_BUTTON_34 = NULL;
	m_pID_BUTTON_35 = NULL;
	m_pID_BUTTON_36 = NULL;
	m_pID_BUTTON_37 = NULL;
	m_pID_BUTTON_38 = NULL;
	m_pID_BUTTON_39 = NULL;
	m_pID_CHECKBOX_ShiftLeft = NULL;
	m_pID_CHECKBOX_ShiftRight = NULL;

}
// Frame
bool CUI_ID_FRAME_SoftKeyboard::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SoftKeyboard::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_1OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_BackSpaceOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
   s_CUI_ID_FRAME_LOGIN.DelCharEditPas();
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_CapsOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	ToggleCaps();
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	s_CUI_ID_FRAME_LOGIN.ID_BUTTON_OKOnButtonClick(NULL);
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_3OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_4OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_5OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_6OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_7OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_8OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_9OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_10OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_11OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_12OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_13OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_14OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_15OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_16OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_17OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_18OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_19OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_20OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_21OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_22OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_23OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_24OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_25OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_26OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_27OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_28OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_29OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_30OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_31OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_32OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_33OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_34OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_35OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_36OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_37OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_38OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SoftKeyboard::ID_BUTTON_39OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
   s_CUI_ID_FRAME_LOGIN.AddCharEditPas((int)((ControlButton*)pSender)->GetCaption()[0]);
	return true;
}
// CheckBox
void CUI_ID_FRAME_SoftKeyboard::ID_CHECKBOX_ShiftLeftOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return;
	m_pID_CHECKBOX_ShiftRight->SetCheck(*pbChecked);
	if (*pbChecked)
		ToggleUpperCase();
	else
		ToggleLowerCase();
	ToggleCaps();
}
// CheckBox
void CUI_ID_FRAME_SoftKeyboard::ID_CHECKBOX_ShiftRightOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SoftKeyboard )
		return;
	m_pID_CHECKBOX_ShiftLeft->SetCheck(*pbChecked);
	if (*pbChecked)
		ToggleUpperCase();
	else
		ToggleLowerCase();
	ToggleCaps();
}

// 装载UI
bool CUI_ID_FRAME_SoftKeyboard::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SoftKeyboard.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SoftKeyboard.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SoftKeyboard::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SoftKeyboard, s_CUI_ID_FRAME_SoftKeyboardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SoftKeyboard, s_CUI_ID_FRAME_SoftKeyboardOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_1, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_1OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_BackSpace, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_BackSpaceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_Caps, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_CapsOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_Enter, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_2, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_3, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_3OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_4, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_4OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_5, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_5OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_6, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_6OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_7, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_7OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_8, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_8OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_9, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_9OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_10, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_10OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_11, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_11OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_12, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_12OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_13, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_13OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_14, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_14OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_15, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_15OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_16, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_16OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_17, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_17OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_18, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_18OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_19, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_19OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_20, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_20OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_21, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_21OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_22, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_22OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_23, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_23OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_24, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_24OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_25, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_25OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_26, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_26OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_27, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_27OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_28, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_28OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_29, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_29OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_30, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_30OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_31, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_31OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_32, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_32OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_33, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_33OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_34, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_34OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_35, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_35OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_36, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_36OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_37, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_37OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_38, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_38OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, ID_BUTTON_39, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_39OnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftLeft, s_CUI_ID_FRAME_SoftKeyboardID_CHECKBOX_ShiftLeftOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftRight, s_CUI_ID_FRAME_SoftKeyboardID_CHECKBOX_ShiftRightOnCheckBoxCheck );

	m_pID_FRAME_SoftKeyboard = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SoftKeyboard );
	m_pID_BUTTON_1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_1 );
	m_pID_BUTTON_BackSpace = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_BackSpace );
	m_pID_BUTTON_Caps = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_Caps );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_Enter );
	m_pID_BUTTON_2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_2 );
	m_pID_BUTTON_3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_3 );
	m_pID_BUTTON_4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_4 );
	m_pID_BUTTON_5 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_5 );
	m_pID_BUTTON_6 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_6 );
	m_pID_BUTTON_7 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_7 );
	m_pID_BUTTON_8 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_8 );
	m_pID_BUTTON_9 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_9 );
	m_pID_BUTTON_10 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_10 );
	m_pID_BUTTON_11 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_11 );
	m_pID_BUTTON_12 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_12 );
	m_pID_BUTTON_13 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_13 );
	m_pID_BUTTON_14 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_14 );
	m_pID_BUTTON_15 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_15 );
	m_pID_BUTTON_16 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_16 );
	m_pID_BUTTON_17 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_17 );
	m_pID_BUTTON_18 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_18 );
	m_pID_BUTTON_19 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_19 );
	m_pID_BUTTON_20 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_20 );
	m_pID_BUTTON_21 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_21 );
	m_pID_BUTTON_22 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_22 );
	m_pID_BUTTON_23 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_23 );
	m_pID_BUTTON_24 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_24 );
	m_pID_BUTTON_25 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_25 );
	m_pID_BUTTON_26 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_26 );
	m_pID_BUTTON_27 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_27 );
	m_pID_BUTTON_28 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_28 );
	m_pID_BUTTON_29 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_29 );
	m_pID_BUTTON_30 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_30 );
	m_pID_BUTTON_31 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_31 );
	m_pID_BUTTON_32 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_32 );
	m_pID_BUTTON_33 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_33 );
	m_pID_BUTTON_34 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_34 );
	m_pID_BUTTON_35 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_35 );
	m_pID_BUTTON_36 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_36 );
	m_pID_BUTTON_37 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_37 );
	m_pID_BUTTON_38 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_38 );
	m_pID_BUTTON_39 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_BUTTON_39 );
	m_pID_CHECKBOX_ShiftLeft = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftLeft );
	m_pID_CHECKBOX_ShiftRight = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, ID_CHECKBOX_ShiftRight );
	assert( m_pID_FRAME_SoftKeyboard );
	assert( m_pID_BUTTON_1 );
	assert( m_pID_BUTTON_BackSpace );
	assert( m_pID_BUTTON_Caps );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_2 );
	assert( m_pID_BUTTON_3 );
	assert( m_pID_BUTTON_4 );
	assert( m_pID_BUTTON_5 );
	assert( m_pID_BUTTON_6 );
	assert( m_pID_BUTTON_7 );
	assert( m_pID_BUTTON_8 );
	assert( m_pID_BUTTON_9 );
	assert( m_pID_BUTTON_10 );
	assert( m_pID_BUTTON_11 );
	assert( m_pID_BUTTON_12 );
	assert( m_pID_BUTTON_13 );
	assert( m_pID_BUTTON_14 );
	assert( m_pID_BUTTON_15 );
	assert( m_pID_BUTTON_16 );
	assert( m_pID_BUTTON_17 );
	assert( m_pID_BUTTON_18 );
	assert( m_pID_BUTTON_19 );
	assert( m_pID_BUTTON_20 );
	assert( m_pID_BUTTON_21 );
	assert( m_pID_BUTTON_22 );
	assert( m_pID_BUTTON_23 );
	assert( m_pID_BUTTON_24 );
	assert( m_pID_BUTTON_25 );
	assert( m_pID_BUTTON_26 );
	assert( m_pID_BUTTON_27 );
	assert( m_pID_BUTTON_28 );
	assert( m_pID_BUTTON_29 );
	assert( m_pID_BUTTON_30 );
	assert( m_pID_BUTTON_31 );
	assert( m_pID_BUTTON_32 );
	assert( m_pID_BUTTON_33 );
	assert( m_pID_BUTTON_34 );
	assert( m_pID_BUTTON_35 );
	assert( m_pID_BUTTON_36 );
	assert( m_pID_BUTTON_37 );
	assert( m_pID_BUTTON_38 );
	assert( m_pID_BUTTON_39 );
	assert( m_pID_CHECKBOX_ShiftLeft );
	assert( m_pID_CHECKBOX_ShiftRight );

	m_vecKeyButtons.clear();

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_BUTTON_%d", index);
	ControlButton* pBtn = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, buf );
	while (pBtn)
	{
		theUiManager.OnButtonClick( ID_FRAME_SoftKeyboard, buf, s_CUI_ID_FRAME_SoftKeyboardID_BUTTON_39OnButtonClick );
		m_vecKeyButtons.push_back(pBtn);

		++index;
		sprintf(buf, "ID_BUTTON_%d", index);
		pBtn = (ControlButton*)theUiManager.FindControl( ID_FRAME_SoftKeyboard, buf );
	}

	for (int i = 0; i < m_vecKeyButtons.size(); ++i)
	{
		m_vecKeyButtons[i]->SetCaption(s_lowerKeyNames[i]);
	}

	SetVisable(false);
	
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SoftKeyboard::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\SoftKeyboard.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SoftKeyboard::_IsVisable()
{
	if( !m_pID_FRAME_SoftKeyboard )
		return false;
	return m_pID_FRAME_SoftKeyboard->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SoftKeyboard::_SetVisable( const bool bVisable )
{
	if (NULL == m_pID_FRAME_SoftKeyboard)
	{
		return;
	}
	m_pID_FRAME_SoftKeyboard->SetVisable( bVisable );

	/*RECT rc;
	rc.left = 10 * ControlObject::GetSCALE(m_pID_FRAME_SoftKeyboard);
	rc.right = rc.left + m_pID_FRAME_SoftKeyboard->GetWidth() * 0.5f;
	rc.top = SCREEN_HEIGHT / 2 - m_pID_FRAME_SoftKeyboard->GetHeight();
	rc.bottom = SCREEN_HEIGHT / 2 + m_pID_FRAME_SoftKeyboard->GetHeight();

	int nDivide = rc.right - rc.left;
	if( nDivide == 0 )
		nDivide = 1;
	int x = rc.left + rand() % nDivide;
	nDivide = rc.bottom - rc.top;
	if( nDivide == 0 )
		nDivide = 1;
	int y = rc.top + rand() % nDivide;*/

	//added by ZhuoMeng.Hu		[8/31/2010]
	RECT rc;
	rc.left = SCREEN_WIDTH / 2 - m_pID_FRAME_SoftKeyboard->GetWidth() / 2;	
	rc.top = SCREEN_HEIGHT / 2 - m_pID_FRAME_SoftKeyboard->GetHeight() / 2;
	

	int nVal = rand() % 100;
	int x = 0;
	int y = 0;
	if (nVal < 50)
	{
		x = rc.left + rand() % rc.left;
	}
	else
	{
		x = rc.left - rand() % rc.left;
	}
	
	nVal = rand() % 100;
	if (nVal < 50)
	{
		y = rc.top + rand() % (rc.top / 3);
	}
	else
	{
		y = rc.top - rand() % rc.top;
	}
	

	m_pID_FRAME_SoftKeyboard->SetPos(x, y);
/*
	int nDivide = SCREEN_WIDTH * ( POSAREA_XRIGHT - POSAREA_XLEFT );
	nDivide = nDivide == 0 ? 1 : nDivide;
	int x = rand() % nDivide + SCREEN_WIDTH * POSAREA_XLEFT - SCREEN_WIDTH / 2
		- m_pID_FRAME_SoftKeyboard->GetWidth() * ControlObject::GetSCALE( m_pID_FRAME_SoftKeyboard ) / 2;
	nDivide = SCREEN_HEIGHT * ( POSAREA_YBOTTOM - POSAREA_YTOP );
	nDivide = nDivide == 0 ? 1 : nDivide;
	int y = rand() % nDivide + SCREEN_HEIGHT * POSAREA_YTOP - m_pID_FRAME_SoftKeyboard->GetHeight() 
		* ControlObject::GetSCALE( m_pID_FRAME_SoftKeyboard ) / 2;;
	m_pID_FRAME_SoftKeyboard->SetScreenPos( x, y );
	*/
}

void CUI_ID_FRAME_SoftKeyboard::ToggleLowerCase()
{
	for (int i = 0; i < m_vecKeyButtons.size(); ++i)
	{
		if (m_vecKeyButtons[i]->GetCaption()[0] >= 'a' && m_vecKeyButtons[i]->GetCaption()[0] <= 'z')
			continue;
		if (m_vecKeyButtons[i]->GetCaption()[0] >= 'A' && m_vecKeyButtons[i]->GetCaption()[0] <= 'Z')
			continue;

		m_vecKeyButtons[i]->SetCaption(s_lowerKeyNames[i]);
	}
}

void CUI_ID_FRAME_SoftKeyboard::ToggleUpperCase()
{
	for (int i = 0; i < m_vecKeyButtons.size(); ++i)
	{
		if (m_vecKeyButtons[i]->GetCaption()[0] >= 'a' && m_vecKeyButtons[i]->GetCaption()[0] <= 'z')
			continue;
		if (m_vecKeyButtons[i]->GetCaption()[0] >= 'A' && m_vecKeyButtons[i]->GetCaption()[0] <= 'Z')
			continue;

		m_vecKeyButtons[i]->SetCaption(s_upperKeyNames[i]);
	}
}

void CUI_ID_FRAME_SoftKeyboard::ToggleCaps()
{
	if (islower(m_vecKeyButtons[11]->GetCaption()[0]) )
	{ // 小写变大写
		for (int i = 11; i < m_vecKeyButtons.size(); ++i)
		{
			char s[2] = {0};
			s[0] = toupper(m_vecKeyButtons[i]->GetCaption()[0]);
			m_vecKeyButtons[i]->SetCaption(s);
		}
	}
	else
	{ // 大写变小写
		for (int i = 11; i < m_vecKeyButtons.size(); ++i)
		{
			char s[2] = {0};
			s[0] = tolower(m_vecKeyButtons[i]->GetCaption()[0]);
			m_vecKeyButtons[i]->SetCaption(s);
		}
	}
}
