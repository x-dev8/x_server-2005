/********************************************************************
	created:	2004/06/15
	created:	15:6:2004   17:58
	filename: 	e:\UITest\HRUI\UI\.
	file path:	e:\UITest\HRUI\UI
	file base:	ControlData
	file ext:	h
	author:		 
	
	purpose:	�������ݽṹ
*********************************************************************/
#pragma once

#include <MeFoundation/MeFoundationPCH.h>
//#include "..\..\UIEditor\stdafx.h"
#include "RapidXml/MeRapidXml.h"

// Ver1
#define UI_VER				"20040625a"		// �汾��
#define CONTROLS_COUNT_MAX	64				// �ؼ������
// Ver2
#define UI_VER2				"20070327a"
#define CONTROLS_COUNT_MAX2	200				// �ؼ������

#define TAB_CONTROL_MAX		5				// ����ҳ���ҳ��


//////////////////////////////////////////////////////////////////////////
// �ؼ�����
enum E_ControlType
{
	Type_Normal = 0
	,Type_Frame				// ���
	,Type_Button			// ��ť
	,Type_CheckBox			// ��ѡ��
	,Type_Edit				// �༭��
	,Type_Text				// �ı���
	,Type_List				// �ı��б�
	,Type_ListImg			// ͼ���б�
	,Type_ScrollBar			// ������
	,Type_ComboBox			// ������
	,Type_Picture			// ͼ��
	,Type_Progress			// ������
	,Type_Tab				// ����ҳ
	,Type_ListEx			// �б����չ
	,Type_ScrollBarEx		// ������
};

const static char* szDrawModeName[] = 
{
	"Left",
	"Top",
	"Right",
	"Bottom",
	"Middle"
};
// ����ģʽ
enum E_DrawMode
{
	DrawModeNormal = 0
	,DrawModeTile
	,DrawModeStrectch
};

// ����ģʽ
enum E_AlignMode
{
	AlignMode_LeftTop = 0
	,AlignMode_RightTop
	,AlignMode_LeftBottom
	,AlignMode_RightBottom
	,AlignMode_Left
	,AlignMode_Top
	,AlignMode_Right
	,AlignMode_Bottom
	,AlignMode_Middle
	,AlignMode_TopMiddle
	,AlignMode_LeftMiddle
	,AlignMode_BottomMiddle
	,AlignMode_RightMiddle
};

// ����ģʽ
enum E_ArrayMode
{
	ArrayMode_Normal = 0
	,ArrayMode_Top
	,ArrayMode_Bottom
	,ArrayMode_SingleModal		// ��ȫģ̬��ֻ��Ӧһ�Σ���ǰֻ��һ��UI��������Ϊ������
};

enum E_Event_Type
{
	EET_Button_OnClick = 0,
	EET_Button_MouseOn,
	EET_CheckBox_OnCheck,
	EET_ComboBox_OnChange,
	EET_ComboBox_ShowList,
	EET_Edit_OnEnter,
	EET_Edit_OnTab,
	EET_Edit_OnLBtnDown,
	EET_Edit_OnLBtnUp,
	EET_Edit_DelByte,
	EET_Frame_OnClick,
	EET_Frame_OnRBtnDown,
	EET_Frame_OnMouseMoveOn,
	EET_Frame_OnMouseMoveLeave,
	EET_Frame_OnFrameMove,
	EET_Frame_Run,
	EET_Frame_Render,
	EET_Frame_OnTab,
	EET_List_SelectChange,
	EET_List_LDBClick,
	EET_List_LRBClick,
	EET_List_ShiftRBClick,
	EET_List_ShiftLBClick,
	EET_List_HyberClick,
	EET_List_HyberRBClick,
	EET_List_HyberItemClick,
	EET_ListEx_DrawInfo,
	EET_Picture_OnClick,
	EET_Picture_MouseOn,
	EET_Picture_MouseLeave,
	EET_Picture_LDBClick,
	EET_Text_HyberClick,

	EET_MAX,
};
// ���ƻ���

// #ifdef UI_EDITOR
// #define MeNew new
// 
// struct S_BaseData
// #else
struct S_BaseData : public MeCommonAllocObj<S_BaseData>
// #endif
{
	enum
	{
		Mode_Left = 0
		,Mode_Top
		,Mode_Right
		,Mode_Bottom
		,Mode_Middle

		,Mode_Max
	};

	struct S_Pic
	{
		S_Pic()
		{
			memset( &m_rcFrame, 0, sizeof(m_rcFrame) );
			memset( &m_rcClient, 0, sizeof(m_rcClient) );
			memset( m_szPicName, 0, sizeof(m_szPicName) );
		}
		void SetPicStruct( const char* szName, const RECT* prcFrame, const RECT* prcClient );
		RECT	m_rcFrame;
		RECT	m_rcClient;
		char	m_szPicName[MAX_PATH];
	};

	S_BaseData();

	int		m_nType;				// �ؼ�����
	int		m_nAlignMode;			// ����ģʽ
	RECT	m_rcRealSize;			// ��ܵ�RECT
	int		m_nDrawMode[Mode_Max];	// ����ģʽ
	char	m_szID[64];				// �ؼ���ID
	S_Pic	m_stBackPic;			// �ؼ�����ͼƬ
	S_Pic	m_stDisablePic;			// �ؼ�Disable����ͼƬ
	char	m_szCaption[128];		// ����
	char	m_szTips[256];		// Tips
	char	m_szFont[32];			// ����
	int		m_nFontSize;			// �����С
	COLORREF m_colFont;				// ������ɫ
    BOOL    m_isFontBold;           // �����Ƿ����
};

//////////////////////////////////////////////////////////////////////////
// ���
struct S_FrameData : public S_BaseData
{
	S_FrameData();

	int		m_nArrayMode;			// ����ģʽ
	bool	m_bMoveable;			// �Ƿ�ɱ��ƶ�
};

//////////////////////////////////////////////////////////////////////////
// ��ť
struct S_ButtonData : public S_BaseData
{
	S_Pic	m_stMoveOnPic;
	S_Pic	m_stPressPic;
    S_Pic	m_stDisabledPic;
    
#ifndef UPGRADE_UI // �����ɰ汾UI����

    char	m_szText[128];			    // �ı�

    char	m_szFontNormal[32];			// ����
    int		m_nFontSizeNormal;			// �����С
    COLORREF m_colFontNormal;			// ������ɫ
    BOOL    m_isFontBoldNormal;         // �����Ƿ����

    //char	m_szFontMoveOn[32];			// ����
    int		m_nFontSizeMoveOn;			// �����С
    COLORREF m_colFontMoveOn;			// ������ɫ
    BOOL    m_isFontBoldMoveOn;         // �����Ƿ����

   // char	m_szFontPress[32];			// ����
    int		m_nFontSizePress;			// �����С
    COLORREF m_colFontPress;			// ������ɫ
    BOOL    m_isFontBoldPress;          // �����Ƿ����

   // char	m_szFontDisabled[32];		// ����
    int		m_nFontSizeDisabled;		// �����С
    COLORREF m_colFontDisabled;			// ������ɫ
    BOOL    m_isFontBoldDisabled;       // �����Ƿ����

    S_ButtonData()
    {
        memset( m_szText, 0 ,sizeof(m_szText) );

        strcpy_s(m_szFontNormal, sizeof(m_szFontNormal), "����");
        m_nFontSizeNormal = 12;
        m_colFontNormal = RGB(255,255,255);
        m_isFontBoldNormal = FALSE;

        //strcpy_s(m_szFontMoveOn, sizeof(m_szFontMoveOn), "����");
        m_nFontSizeMoveOn = 12;
        m_colFontMoveOn = RGB(255,255,255);
        m_isFontBoldMoveOn = FALSE;

        //strcpy_s(m_szFontPress, sizeof(m_szFontPress), "����");
        m_nFontSizePress = 12;
        m_colFontPress = RGB(255,255,255);
        m_isFontBoldPress = FALSE;

       // strcpy_s(m_szFontDisabled, sizeof(m_szFontDisabled), "����");
        m_nFontSizeDisabled = 12;
        m_colFontDisabled = RGB(255,255,255);
        m_isFontBoldDisabled = FALSE;
    }
#endif

	//const char*		m_szOnClickName;
	//const char*		m_szMouseOnName;
};

//////////////////////////////////////////////////////////////////////////
// ѡ���
struct S_CheckBoxData : public S_BaseData
{
	S_CheckBoxData();

	bool			m_bChecked;
	S_ButtonData	m_stChecked;
};

//////////////////////////////////////////////////////////////////////////
// ������
struct S_ScrollBarData : public S_BaseData
{
	S_ButtonData	m_stUp;
	S_ButtonData	m_stDown;
	S_ButtonData	m_stBar;
};

// ������
struct S_ScrollBarExData : public S_ScrollBarData
{
};


//////////////////////////////////////////////////////////////////////////
// �ı���
struct S_TextData : public S_BaseData
{
	S_TextData();

	bool	m_bRightScrollBar;
	bool	m_bSingleLine;
	int		m_nTextAlign;
	S_ScrollBarData	m_stScrollBar;
	char	m_szText[128];			    // �ı�
};

//////////////////////////////////////////////////////////////////////////
// �༭��
struct S_EditData : public S_TextData
{
	S_EditData();

	bool	m_bReadOnly;
	bool	m_bPassword;
	bool	m_bIsNumber;
};

//////////////////////////////////////////////////////////////////////////
// �ı��б�
struct S_ListData : public S_BaseData
{
	S_ListData();

	COLORREF m_colSelBar;
	int		m_nItemHeight;
	S_ScrollBarData	m_stScrollBar;
};

//////////////////////////////////////////////////////////////////////////
// ͼ���б�
struct S_ListImgData : public S_BaseData
{
	S_ListImgData();

	int		m_nIconSize;
	int		m_nOffsetWidth;
	int		m_nOffsetHeight;
	int		m_nMaxHeightCount;
	bool	m_bCanbePick;
	bool	m_bShowSelFrame;
	COLORREF m_colSelFrame;
	S_ScrollBarData	m_stScrollBar;
};

//////////////////////////////////////////////////////////////////////////
// ������
struct S_ComboBoxData : public S_BaseData
{
	S_ComboBoxData()
	{
		m_stEdit.m_bReadOnly = true;
	}
	S_EditData	m_stEdit;
	S_ListData	m_stList;
	S_ButtonData m_stButton;
};

//////////////////////////////////////////////////////////////////////////
// ͼƬ
struct S_PictureData : public S_BaseData 
{
};

//////////////////////////////////////////////////////////////////////////
// ������
struct S_ProgressData : public S_BaseData
{
    // added by ZhuoMeng.Hu     [12/31/2010]
    S_ProgressData()
    {
        memset( m_szAniPath, 0, sizeof( m_szAniPath ) );
        m_bAniOnly = false;
        m_bAutoPlay = true;
        m_bVertical = false;
        m_bReverse = false;
    }
    bool    m_bVertical;
    bool    m_bReverse;
    char    m_szAniPath[MAX_PATH];
    bool    m_bAniOnly;
    bool    m_bAutoPlay;
};

//////////////////////////////////////////////////////////////////////////
// ����ҳ
struct S_TabData : public S_BaseData
{
	S_TabData();
	S_ButtonData	m_btnTab[TAB_CONTROL_MAX];
	S_FrameData		m_frame;
	char			m_szFrameFileName[TAB_CONTROL_MAX][64];
	int				m_nTabCount;
};

//////////////////////////////////////////////////////////////////////////
// �б����չ
struct S_ListExData : public S_BaseData
{
	S_ListExData();

	COLORREF	m_colSelBar;
	int			m_nItemHeight;
	int			m_nItemWidth;
	int			m_nOffsetWidth;
	int			m_nOffsetHeight;
	int			m_nMaxHeightCount;
	bool		m_bCanbePick;
	S_ScrollBarData	m_stScrollBar;
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
struct S_UIData
{
	struct SVer
	{
		SVer()
		{
			memset( m_szVer, 0, sizeof(m_szVer) );
		}
		char 		m_szVer[10];
	};
	struct S_UIHead
	{
		S_UIHead()
		{
			memset( m_nControlsType, 0, sizeof(m_nControlsType) );
			strcpy( m_stVer.m_szVer, UI_VER);
			m_nControlsCount = 0;
			m_dwCreatedDate = 0;
		}
		SVer		m_stVer;
		DWORD		m_dwCreatedDate;
		S_FrameData	m_stFrameData;
		int			m_nControlsCount;
		int			m_nControlsType[CONTROLS_COUNT_MAX];
	};
	//
	struct S_UIHead2
	{
		S_UIHead2()
		{
			memset( m_nControlsType, 0, sizeof(m_nControlsType) );
			strcpy( m_stVer.m_szVer, UI_VER2);
			m_nControlsCount = 0;
			m_dwCreatedDate = 0;
		}
		SVer		m_stVer;
		DWORD		m_dwCreatedDate;
		S_FrameData	m_stFrameData;
		int			m_nControlsCount;
		int			m_nControlsType[CONTROLS_COUNT_MAX2];
	};

	S_UIData();
	~S_UIData();
	void Release();
	void SetEventFunName( int index, E_Event_Type type, const char* name );
	DWORD LoadFile( const char* pszFileName );
    //Tony
    DWORD LoadUnit( void *psData);
    //
    DWORD LoadUnitXML(void *psData);

	DWORD SaveFile( const char* pszFileName );
	static S_BaseData* NewData( int nType );

	void	LoadFile_XML( const char* fileName );
    //Tony
    void	LoadUnit_XML( void *buf,long length);

    void Load_XML(MeXmlDocument &doc);

    void    LoadHead2_XML( MeXmlElement* pXmlUI, S_UIHead2* data );
	bool	LoadFrame2_XML( MeXmlElement* pXmlUI, S_FrameData* data );
	bool	LoadBaseAttribute2_XML( MeXmlElement* pXmlUI, S_BaseData* data );
	void	LoadPic_BaseAttribute2_XML( MeXmlElement* pXmlUI, S_BaseData::S_Pic* data );
	bool	LoadScrollBar2_XML( MeXmlElement* pXmlUI, S_ScrollBarData* data );
	bool	LoadListImg2_XML( MeXmlElement* pXmlUI, S_ListImgData* data );
	bool	LoadList2_XML( MeXmlElement* pXmlUI, S_ListData* data );
	bool	LoadText2_XML( MeXmlElement* pXmlUI, S_TextData* data );
	bool	LoadTab2_XML( MeXmlElement* pXmlUI, S_TabData* data );
	bool	LoadListEx2_XML( MeXmlElement* pXmlUI, S_ListExData* data );
	bool	LoadScrollBarEx2_XML( MeXmlElement* pXmlUI, S_ScrollBarExData* data );
	bool	LoadProgress2_XML( MeXmlElement* pXmlUI, S_ProgressData* data );
	bool	LoadPicture2_XML( MeXmlElement* pXmlUI, S_PictureData* data );
	bool	LoadComboBox2_XML( MeXmlElement* pXmlUI, S_ComboBoxData* data );
	bool	LoadEdit2_XML( MeXmlElement* pXmlUI, S_EditData* data );
	bool	LoadCheckBox2_XML( MeXmlElement* pXmlUI, S_CheckBoxData* data );
	bool	LoadButton2_XML( MeXmlElement* pXmlUI, S_ButtonData* data );

    void    writeHead_XML(MeXmlElement *pXmlUI, S_UIHead2* data);
	void	writeControlBase_XML(MeXmlElement *pXmlUI, S_BaseData* data);
	void	writeScrollbarEx_XML( MeXmlElement *pXmlUI, S_ScrollBarExData* data );
	void	writeListEx_XML( MeXmlElement *pXmlUI, S_ListExData* data );
	void	writeTab_XML( MeXmlElement *pXmlUI, S_TabData* data );
	void	writeProgress_XML( MeXmlElement *pXmlUI, S_ProgressData* data );
	void	writePicture_XML( MeXmlElement *pXmlUI, S_PictureData* data );
	void	writeComboBox_XML( MeXmlElement *pXmlUI, S_ComboBoxData* data );
	void	writeScrollBar_XML( MeXmlElement *pXmlUI, S_ScrollBarData* data );
	void	writeListImg_XML( MeXmlElement *pXmlUI, S_ListImgData* data );
	void	writeList_XML( MeXmlElement *pXmlUI, S_ListData* data );
	void	writeText_XML( MeXmlElement *pXmlUI, S_TextData* data );
	void	writeEdit_XML( MeXmlElement *pXmlUI, S_EditData* data );
	void	writeCheckBox_XML( MeXmlElement *pXmlUI, S_CheckBoxData* data );
	void	writeButton_XML( MeXmlElement *pXmlUI, S_ButtonData* data );
	void	writeFrame_XML( MeXmlElement *pXmlUI, S_FrameData* data );
	void	writeUI_XML(MeXmlElement *pXmlUI);
	void	SaveFile_XML( const char* pszFileName );

	void	UpdateScaledFontSize( int& nFontSize );

	S_UIHead2	m_stHead;
	//S_BaseData	*m_pstControlData[CONTROLS_COUNT_MAX2];
	std::vector<S_BaseData*>	m_pstControlData;

	const char*		m_szControlEventName[CONTROLS_COUNT_MAX2][EET_MAX];

	// added, [9/25/2010 zhangjiayi]
	// ���õĿؼ��������������Ϊ����

private:
	bool	IsBadData( const RECT& rcRect );
};

extern S_UIData stUIData;
