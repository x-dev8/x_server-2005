/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\CodeCheck.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_CodeCheck
#define ID_FRAME_CodeCheck		"ID_FRAME_CodeCheck"
#endif  ID_FRAME_CodeCheck
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_PICTURE_Code
#define ID_PICTURE_Code		"ID_PICTURE_Code"
#endif  ID_PICTURE_Code
#ifndef ID_BUTTON_Check
#define ID_BUTTON_Check		"ID_BUTTON_Check"
#endif  ID_BUTTON_Check
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_CHECKBOX_Check1
#define ID_CHECKBOX_Check1		"ID_CHECKBOX_Check1"
#endif  ID_CHECKBOX_Check1
#ifndef ID_CHECKBOX_Check2
#define ID_CHECKBOX_Check2		"ID_CHECKBOX_Check2"
#endif  ID_CHECKBOX_Check2
#ifndef ID_CHECKBOX_Check3
#define ID_CHECKBOX_Check3		"ID_CHECKBOX_Check3"
#endif  ID_CHECKBOX_Check3
#ifndef ID_CHECKBOX_Check4
#define ID_CHECKBOX_Check4		"ID_CHECKBOX_Check4"
#endif  ID_CHECKBOX_Check4
#ifndef ID_TEXT_Answer1
#define ID_TEXT_Answer1		"ID_TEXT_Answer1"
#endif  ID_TEXT_Answer1
#ifndef ID_TEXT_Answer2
#define ID_TEXT_Answer2		"ID_TEXT_Answer2"
#endif  ID_TEXT_Answer2
#ifndef ID_TEXT_Answer3
#define ID_TEXT_Answer3		"ID_TEXT_Answer3"
#endif  ID_TEXT_Answer3
#ifndef ID_TEXT_Answer4
#define ID_TEXT_Answer4		"ID_TEXT_Answer4"
#endif  ID_TEXT_Answer4
#ifndef ID_BUTTON_Small
#define ID_BUTTON_Small		"ID_BUTTON_Small"
#endif  ID_BUTTON_Small
#ifndef ID_CHECKBOX_Check5
#define ID_CHECKBOX_Check5		"ID_CHECKBOX_Check5"
#endif  ID_CHECKBOX_Check5
#ifndef ID_TEXT_Answer5
#define ID_TEXT_Answer5		"ID_TEXT_Answer5"
#endif  ID_TEXT_Answer5
#ifndef ID_CHECKBOX_Check6
#define ID_CHECKBOX_Check6		"ID_CHECKBOX_Check6"
#endif  ID_CHECKBOX_Check6
#ifndef ID_TEXT_Answer6
#define ID_TEXT_Answer6		"ID_TEXT_Answer6"
#endif  ID_TEXT_Answer6
#include "UiBase.h"
class CUI_ID_FRAME_CodeCheck :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CodeCheck();
private:
	 ControlFrame*	m_pID_FRAME_CodeCheck;
	 ControlPicture*	m_pID_PICTURE_Title;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlPicture*	m_pID_PICTURE_Code;
	 ControlButton*	m_pID_BUTTON_Check;
	 ControlText*	m_pID_TEXT_Title;
	 ControlText*	m_pID_TEXT_Time;
	 ControlCheckBox*	m_pID_CHECKBOX_Check1;
	 ControlCheckBox*	m_pID_CHECKBOX_Check2;
	 ControlCheckBox*	m_pID_CHECKBOX_Check3;
	 ControlCheckBox*	m_pID_CHECKBOX_Check4;
	 ControlText*	m_pID_TEXT_Answer1;
	 ControlText*	m_pID_TEXT_Answer2;
	 ControlText*	m_pID_TEXT_Answer3;
	 ControlText*	m_pID_TEXT_Answer4;
	 //ControlButton*	m_pID_BUTTON_Small;
	 ControlCheckBox*	m_pID_CHECKBOX_Check5;
	 ControlText*	m_pID_TEXT_Answer5;
	 ControlCheckBox*	m_pID_CHECKBOX_Check6;
	 ControlText*	m_pID_TEXT_Answer6;

	 ControlRadioGroup m_AnswerGroup;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CheckOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_Check1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Check2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Check3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Check4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Check5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Check6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_SmallOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void SetStreamInfo( DWORD dwTime, unsigned char* pucBitStream, char* pcGlyphBuf );
	void Uncompress(const unsigned char* bitstream, unsigned char* background);	

	S_BaseData* GetData();

protected:
	void CheckTerminateable( LPDIRECT3DTEXTURE9 pTex );
	
protected:
	unsigned char m_aucUncompressedBitsstream[MsgReqGraphicCode::ECD_BisstreamMaxSize * 8];
	unsigned char  m_acGlyphBuf[MsgReqGraphicCode::ECD_GlyphBufMaxSize];
	DWORD m_dwTime;
	wchar_t m_awcGlyph[MsgReqGraphicCode::ECD_GlyphBufMaxSize / 2];
	LPDIRECT3DTEXTURE9 m_pCodeTexture;	
	DWORD m_dwLastTime;
};
extern CUI_ID_FRAME_CodeCheck s_CUI_ID_FRAME_CodeCheck;
