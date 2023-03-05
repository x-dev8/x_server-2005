/********************************************************************
	created:	2004/06/15
	created:	15:6:2004   17:58
	filename: 	e:\UITest\HRUI\UI\.
	file path:	e:\UITest\HRUI\UI
	file base:	ControlData
	file ext:	h
	author:		 
	
	purpose:	控制数据结构
*********************************************************************/
#pragma once

#include <MeFoundation/MeFoundationPCH.h>
//#include "..\..\UIEditor\stdafx.h"
#include "RapidXml/MeRapidXml.h"

// Ver1
#define UI_VER				"20040625a"		// 版本号
#define CONTROLS_COUNT_MAX	64				// 控件最大数
// Ver2
#define UI_VER2				"20070327a"
#define CONTROLS_COUNT_MAX2	200				// 控件最大数

#define TAB_CONTROL_MAX		5				// 属性页最大页数


//////////////////////////////////////////////////////////////////////////
// 控件类型
enum E_ControlType
{
	Type_Normal = 0
	,Type_Frame				// 框架
	,Type_Button			// 按钮
	,Type_CheckBox			// 多选框
	,Type_Edit				// 编辑框
	,Type_Text				// 文本框
	,Type_List				// 文本列表
	,Type_ListImg			// 图像列表
	,Type_ScrollBar			// 滚动条
	,Type_ComboBox			// 下拉框
	,Type_Picture			// 图像
	,Type_Progress			// 进条条
	,Type_Tab				// 属性页
	,Type_ListEx			// 列表框扩展
	,Type_ScrollBarEx		// 滚动条
};

const static char* szDrawModeName[] = 
{
	"Left",
	"Top",
	"Right",
	"Bottom",
	"Middle"
};
// 绘制模式
enum E_DrawMode
{
	DrawModeNormal = 0
	,DrawModeTile
	,DrawModeStrectch
};

// 对齐模式
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

// 排列模式
enum E_ArrayMode
{
	ArrayMode_Normal = 0
	,ArrayMode_Top
	,ArrayMode_Bottom
	,ArrayMode_SingleModal		// 完全模态，只响应一次，当前只有一个UI可以设置为这个标记
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
// 控制基类

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

	int		m_nType;				// 控件类型
	int		m_nAlignMode;			// 对齐模式
	RECT	m_rcRealSize;			// 框架的RECT
	int		m_nDrawMode[Mode_Max];	// 绘制模式
	char	m_szID[64];				// 控件的ID
	S_Pic	m_stBackPic;			// 控件背景图片
	S_Pic	m_stDisablePic;			// 控件Disable背景图片
	char	m_szCaption[128];		// 标题
	char	m_szTips[256];		// Tips
	char	m_szFont[32];			// 字体
	int		m_nFontSize;			// 字体大小
	COLORREF m_colFont;				// 字体颜色
    BOOL    m_isFontBold;           // 字体是否粗体
};

//////////////////////////////////////////////////////////////////////////
// 框架
struct S_FrameData : public S_BaseData
{
	S_FrameData();

	int		m_nArrayMode;			// 排列模式
	bool	m_bMoveable;			// 是否可被移动
};

//////////////////////////////////////////////////////////////////////////
// 按钮
struct S_ButtonData : public S_BaseData
{
	S_Pic	m_stMoveOnPic;
	S_Pic	m_stPressPic;
    S_Pic	m_stDisabledPic;
    
#ifndef UPGRADE_UI // 启动旧版本UI升级

    char	m_szText[128];			    // 文本

    char	m_szFontNormal[32];			// 字体
    int		m_nFontSizeNormal;			// 字体大小
    COLORREF m_colFontNormal;			// 字体颜色
    BOOL    m_isFontBoldNormal;         // 字体是否粗体

    //char	m_szFontMoveOn[32];			// 字体
    int		m_nFontSizeMoveOn;			// 字体大小
    COLORREF m_colFontMoveOn;			// 字体颜色
    BOOL    m_isFontBoldMoveOn;         // 字体是否粗体

   // char	m_szFontPress[32];			// 字体
    int		m_nFontSizePress;			// 字体大小
    COLORREF m_colFontPress;			// 字体颜色
    BOOL    m_isFontBoldPress;          // 字体是否粗体

   // char	m_szFontDisabled[32];		// 字体
    int		m_nFontSizeDisabled;		// 字体大小
    COLORREF m_colFontDisabled;			// 字体颜色
    BOOL    m_isFontBoldDisabled;       // 字体是否粗体

    S_ButtonData()
    {
        memset( m_szText, 0 ,sizeof(m_szText) );

        strcpy_s(m_szFontNormal, sizeof(m_szFontNormal), "宋体");
        m_nFontSizeNormal = 12;
        m_colFontNormal = RGB(255,255,255);
        m_isFontBoldNormal = FALSE;

        //strcpy_s(m_szFontMoveOn, sizeof(m_szFontMoveOn), "宋体");
        m_nFontSizeMoveOn = 12;
        m_colFontMoveOn = RGB(255,255,255);
        m_isFontBoldMoveOn = FALSE;

        //strcpy_s(m_szFontPress, sizeof(m_szFontPress), "宋体");
        m_nFontSizePress = 12;
        m_colFontPress = RGB(255,255,255);
        m_isFontBoldPress = FALSE;

       // strcpy_s(m_szFontDisabled, sizeof(m_szFontDisabled), "宋体");
        m_nFontSizeDisabled = 12;
        m_colFontDisabled = RGB(255,255,255);
        m_isFontBoldDisabled = FALSE;
    }
#endif

	//const char*		m_szOnClickName;
	//const char*		m_szMouseOnName;
};

//////////////////////////////////////////////////////////////////////////
// 选择框
struct S_CheckBoxData : public S_BaseData
{
	S_CheckBoxData();

	bool			m_bChecked;
	S_ButtonData	m_stChecked;
};

//////////////////////////////////////////////////////////////////////////
// 滚动条
struct S_ScrollBarData : public S_BaseData
{
	S_ButtonData	m_stUp;
	S_ButtonData	m_stDown;
	S_ButtonData	m_stBar;
};

// 滚动条
struct S_ScrollBarExData : public S_ScrollBarData
{
};


//////////////////////////////////////////////////////////////////////////
// 文本框
struct S_TextData : public S_BaseData
{
	S_TextData();

	bool	m_bRightScrollBar;
	bool	m_bSingleLine;
	int		m_nTextAlign;
	S_ScrollBarData	m_stScrollBar;
	char	m_szText[128];			    // 文本
};

//////////////////////////////////////////////////////////////////////////
// 编辑框
struct S_EditData : public S_TextData
{
	S_EditData();

	bool	m_bReadOnly;
	bool	m_bPassword;
	bool	m_bIsNumber;
};

//////////////////////////////////////////////////////////////////////////
// 文本列表
struct S_ListData : public S_BaseData
{
	S_ListData();

	COLORREF m_colSelBar;
	int		m_nItemHeight;
	S_ScrollBarData	m_stScrollBar;
};

//////////////////////////////////////////////////////////////////////////
// 图像列表
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
// 下拉框
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
// 图片
struct S_PictureData : public S_BaseData 
{
};

//////////////////////////////////////////////////////////////////////////
// 进度条
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
// 属性页
struct S_TabData : public S_BaseData
{
	S_TabData();
	S_ButtonData	m_btnTab[TAB_CONTROL_MAX];
	S_FrameData		m_frame;
	char			m_szFrameFileName[TAB_CONTROL_MAX][64];
	int				m_nTabCount;
};

//////////////////////////////////////////////////////////////////////////
// 列表框扩展
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
	// 不用的控件，坐标过大则视为无用

private:
	bool	IsBadData( const RECT& rcRect );
};

extern S_UIData stUIData;
