/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\LoginCheck.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_LoginCheck
#define ID_FRAME_LoginCheck		"ID_FRAME_LoginCheck"
#endif  ID_FRAME_LoginCheck

#ifndef ID_PICTURE_Code
#define ID_PICTURE_Code		"ID_PICTURE_Code"
#endif  ID_PICTURE_Code
#ifndef ID_BUTTON_Check
#define ID_BUTTON_Check		"ID_BUTTON_Check"
#endif  ID_BUTTON_Check
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_PICTURE_CodeCheckWall
#define ID_PICTURE_CodeCheckWall		"ID_PICTURE_CodeCheckWall"
#endif  ID_PICTURE_CodeCheckWall
#ifndef ID_EDIT_CodeCheck
#define ID_EDIT_CodeCheck		"ID_EDIT_CodeCheck"
#endif  ID_EDIT_CodeCheck

#include "UiBase.h"
class CUI_ID_FRAME_LoginCheck :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_LoginCheck();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CheckOnButtonClick( ControlObject* pSender );
	void ID_EDIT_CodeCheckOnEditEnter( ControlObject* pSender, const char* szData );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void SetStreamInfo( DWORD dwTime, unsigned char* pucBitStream );
	void Uncompress(const unsigned char* bitstream, unsigned char* background);
    static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

    ControlFrame* GetFrame(){if(!m_pID_FRAME_LoginCheck) return NULL; return m_pID_FRAME_LoginCheck;}

protected:
	unsigned char m_aucUncompressedBitsstream[MsgReqGraphicCode::ECD_BisstreamMaxSize * 8];
	unsigned char  m_acGlyphBuf[MsgReqGraphicCode::ECD_GlyphBufMaxSize];
	DWORD m_dwTime;
	wchar_t m_awcGlyph[MsgReqGraphicCode::ECD_GlyphBufMaxSize / 2];
	LPDIRECT3DTEXTURE9 m_pCodeTexture;	
	DWORD m_dwLastTime;

    ControlFrame*	m_pID_FRAME_LoginCheck;
    ControlPicture*	m_pID_PICTURE_Code;
    ControlButton*	m_pID_BUTTON_Check;
    ControlText*	m_pID_TEXT_Time;
    ControlPicture*	m_pID_PICTURE_CodeCheckWall;
    ControlEdit*	m_pID_EDIT_CodeCheck;
};
extern CUI_ID_FRAME_LoginCheck s_CUI_ID_FRAME_LoginCheck;
