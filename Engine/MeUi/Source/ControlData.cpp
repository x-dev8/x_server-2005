#include "MeUi/controldata.h"
#include <stdio.h>
#include <assert.h>
//#include <time.h>
#include "FuncPerformanceLog.h"
#include "../filepacket/packet_interface.h"
S_UIData stUIData;

//char* szDrawModeName[] = 
//{
//	"Left",
//	"Top",
//	"Right",
//	"Bottom",
//	"Middle"
//};
float g_FontSizeScale = 1.f;
//////////////////////////////////////////////////////////////////////////
S_BaseData::S_BaseData()
{
	memset( &m_rcRealSize, 0, sizeof(m_rcRealSize) );
	memset( m_nDrawMode, 0, sizeof(m_nDrawMode) );
	memset( m_szID, 0, sizeof(m_szID) );
	memset( m_szCaption, 0 ,sizeof(m_szCaption) );
	memset( m_szTips, 0 ,sizeof(m_szTips) );
	memset( m_szFont, 0, sizeof(m_szFont) );
	m_nFontSize = 12;
	m_colFont = RGB(255,255,255);
	m_nType = 0;
	m_nAlignMode = 0;
}

void S_BaseData::S_Pic::SetPicStruct( const char* szName, const RECT* prcFrame, const RECT* prcClient )
{
	strcpy( m_szPicName, szName );
	m_rcFrame = *prcFrame;
	m_rcClient = *prcClient;
}

//////////////////////////////////////////////////////////////////////////
S_FrameData::S_FrameData()
{
	m_nArrayMode = 0;
	m_bMoveable = true;
}

//////////////////////////////////////////////////////////////////////////
S_EditData::S_EditData()
{
	m_bReadOnly = false;
	m_bPassword = false;
	m_bIsNumber = false;
	m_bSingleLine = true;
}

//////////////////////////////////////////////////////////////////////////
S_TextData::S_TextData()
{
	memset( m_szText, 0 ,sizeof(m_szText) );
	m_bRightScrollBar = true;
	m_bSingleLine = false;
	m_nTextAlign = 0;
}

//////////////////////////////////////////////////////////////////////////
S_ListData::S_ListData()
{
	m_colSelBar = RGB(128,0,0);
	m_nItemHeight = 20;
}

//////////////////////////////////////////////////////////////////////////
S_ListImgData::S_ListImgData()
{
	m_nIconSize = 32;
	m_nOffsetWidth = 2;
	m_nOffsetHeight = 2;
	m_nMaxHeightCount = 20;
	m_bCanbePick = true;
	m_bShowSelFrame = true;
	m_colSelFrame = RGB(255,0,0);
}

//////////////////////////////////////////////////////////////////////////
S_CheckBoxData::S_CheckBoxData()
{
	m_bChecked = false;
}

//////////////////////////////////////////////////////////////////////////
S_TabData::S_TabData()
{
	m_nTabCount = 3;
}

//////////////////////////////////////////////////////////////////////////
S_ListExData::S_ListExData()
{
	m_colSelBar = RGB(128,0,0);
	m_nItemHeight = 32;
	m_nItemWidth = 100;
	m_nOffsetWidth = 0;
	m_nOffsetHeight = 0;
	m_nMaxHeightCount = 10;
	m_bCanbePick = false;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
S_UIData::S_UIData()
{
	for( int i = 0; i < m_pstControlData.size(); ++i )
	{
		delete m_pstControlData[i];
		m_pstControlData[i] = NULL;
	}
	m_pstControlData.clear();	
}

S_UIData::~S_UIData()
{
//	Release();
}

void S_UIData::Release()
{
	//for( int n=0; n<CONTROLS_COUNT_MAX; n++ )
	//{
	//	if ( m_pstControlData[n] )
	//	{
	//		delete m_pstControlData[n];
	//		m_pstControlData[n] = NULL;
	//	}
	//}
	for( int i = 0; i < m_pstControlData.size(); ++i )
	{
		delete m_pstControlData[i];
		m_pstControlData[i] = NULL;
	}
	m_pstControlData.clear();
}

//#define LOAD_CONTROL(type)	{ m_pstControlData[n] = MeNew type; fread( m_pstControlData[n], sizeof(type), 1, fp ); }
#define SAVE_CONTROL(type)	{ fwrite( m_pstControlData[n], sizeof(type), 1, fp ); }

S_BaseData* S_UIData::NewData( int nType )
{
	S_BaseData* pData = NULL;
	switch( nType ) 
	{
	case Type_Button:
		pData = MeNew S_ButtonData;
		break;
	case Type_CheckBox:
		pData = MeNew S_CheckBoxData;
		break;
	case Type_Edit:
		pData = MeNew S_EditData;
		break;
	case Type_Text:
		pData = MeNew S_TextData;
		break;
	case Type_List:
		pData = MeNew S_ListData;
		break;
	case Type_ListImg:
		pData = MeNew S_ListImgData;
		break;
	case Type_ScrollBar:
		pData = MeNew S_ScrollBarData;
		break;
	case Type_ScrollBarEx:
		pData = MeNew S_ScrollBarExData;
		break;
	case Type_ComboBox:
		pData = MeNew S_ComboBoxData;
		break;
	case Type_Picture:
		pData = MeNew S_PictureData;
		break;
	case Type_Progress:
		pData = MeNew S_ProgressData;
		break;
	case Type_Tab:
		pData = MeNew S_TabData;
		break;
	case Type_ListEx:
		pData = MeNew S_ListExData;
		break;
	default:
		assert( false );
		break;
	}
	return pData;
}

void S_UIData::LoadUnit_XML(void *buf,long length)
{
    //Added by WIlson;
    guardfunc;
 //   MeXmlDocument	doc;

 //   //从buffer里初始化MeXmlDocument对象
	//if( !doc.LoadFileFromBuffer(buf,length) )
	//{
	//	assert(false && "Login.cpp::LoadConfigXml 读取文件不错");		
 //       return;
	//}

 //   //读取XML内容
 //   this->Load_XML(doc);
    unguard;
}
void S_UIData::LoadFile_XML( const char* fileName )
{
	guardfunc;
	MeXmlDocument	doc;
	if( !doc.LoadFile(fileName) )
	{
		assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
		return;
	}

	const char* szValue = NULL;
	S_BaseData* pControl = NULL;
	MeXmlElement* lpRootUI = doc.FirstChildElement("UI");
	if(lpRootUI )
    {
        MeXmlElement* lpFrame = lpRootUI->FirstChildElement("head");
        if( lpFrame )
        {
            LoadHead2_XML( lpFrame, &m_stHead );
        }

		lpFrame = lpRootUI->FirstChildElement("frame");
		if( lpFrame )
		{
			if( !LoadFrame2_XML( lpFrame, &m_stHead.m_stFrameData ) )
				return;
		}
		
// 		MeXmlHandle hUI( lpRootUI );
		MeXmlElement* lpControl = lpRootUI->FirstChildElement();
		for( ; lpControl; lpControl = lpControl->NextSiblingElement() )
		{
			szValue = lpControl->name();
			if( szValue )
			{
				bool bRet = false;
				if( strcmp("button", szValue) == 0 )
				{
					pControl = NewData( Type_Button );
					if( pControl)
						bRet = LoadButton2_XML( lpControl, (S_ButtonData*)pControl );
				}
				else if( strcmp("checkBox", szValue) == 0 )
				{
					pControl = NewData( Type_CheckBox );
					if( pControl)
						bRet = LoadCheckBox2_XML( lpControl, (S_CheckBoxData*)pControl );
				}
				else if( strcmp("edit", szValue) == 0 )
				{
					pControl = NewData( Type_Edit );
					if( pControl)
						bRet = LoadEdit2_XML( lpControl, (S_EditData*)pControl );
				}
				else if( strcmp("text", szValue) == 0 )
				{
					pControl = NewData( Type_Text );
					if( pControl)
						bRet = LoadText2_XML( lpControl, (S_TextData*)pControl );
				}
				else if( strcmp("list", szValue) == 0 )
				{
					pControl = NewData( Type_List );
					if( pControl)
						bRet = LoadList2_XML( lpControl, (S_ListData*)pControl );
				}
				else if( strcmp("listImg", szValue) == 0 )
				{
					pControl = NewData( Type_ListImg );
					if( pControl)
						bRet = LoadListImg2_XML( lpControl, (S_ListImgData*)pControl );
				}
				else if( strcmp("scrollBar", szValue) == 0 )
				{
					pControl = NewData( Type_ScrollBar );
					if( pControl)
						bRet = LoadScrollBar2_XML( lpControl, (S_ScrollBarData*)pControl );
				}
				else if( strcmp("comboBox", szValue) == 0 )
				{
					pControl = NewData( Type_ComboBox );
					if( pControl)
						bRet = LoadComboBox2_XML( lpControl, (S_ComboBoxData*)pControl );
				}
				else if( strcmp("picture", szValue) == 0 )
				{
					pControl = NewData( Type_Picture );
					if( pControl)
						bRet = LoadPicture2_XML( lpControl, (S_PictureData*)pControl );
				}
				else if( strcmp("progress", szValue) == 0 )
				{
					pControl = NewData( Type_Progress );
					if( pControl)
						bRet = LoadProgress2_XML( lpControl, (S_ProgressData*)pControl );
				}
				else if( strcmp("tab", szValue) == 0 )
				{
					pControl = NewData( Type_Tab );
					if( pControl)
						bRet = LoadTab2_XML( lpControl, (S_TabData*)pControl );
				}
				else if( strcmp("listEx", szValue) == 0 )
				{
					pControl = NewData( Type_ListEx );
					if( pControl)
						bRet = LoadListEx2_XML( lpControl, (S_ListExData*)pControl );
				}
				else if( strcmp("scrollBarEx", szValue) == 0 )
				{
					pControl = NewData( Type_ScrollBarEx );
					if( pControl)
						bRet = LoadScrollBarEx2_XML( lpControl, (S_ScrollBarExData*)pControl );
				}

				if( pControl )
				{
					if( !bRet )
					{
						--m_stHead.m_nControlsCount;
						delete pControl;
					}
					else
						m_pstControlData.push_back( pControl );
				}
			}
		}
	}
	//szValue = lpRootUI->Child( 1 )->Text();
	//while()
	unguard;
}
//void S_UIData::LoadFile_XML( const char* fileName )
//{
//	guardfunc;
//	MeXmlDocument	doc;
//	if( !doc.LoadFile(fileName) )
//	{
//		assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
//		return;
//	}	
//    this->Load_XML(doc);
//	//szValue = lpRootUI->Child( 1 )->Text();
//	//while()
//	unguard;
//}
//
//void S_UIData::Load_XML(MeXmlDocument &doc)
//{
//    const char* szValue = NULL;
//	S_BaseData* pControl = NULL;
//	MeXmlElement* lpRootUI = doc.FirstChildElement("UI");
//	if(lpRootUI )
//	{
//		MeXmlElement* lpFrame = lpRootUI->FirstChildElement("frame");
//		if( lpFrame )
//		{
//			LoadFrame2_XML( lpFrame, &m_stHead.m_stFrameData );
//		}
//		MeXmlHandle hUI( lpRootUI );
//		MeXmlElement* lpControl = hUI.Child( 1 ).Element();
//		for( ; lpControl; lpControl = lpControl->NextSiblingElement() )
//		{
//			szValue = lpControl->Value();
//			if( szValue )
//			{
//				if( strcmp("button", szValue) == 0 )
//				{
//					pControl = NewData( Type_Button );
//					if( pControl)
//						LoadButton2_XML( lpControl, (S_ButtonData*)pControl );
//				}
//				else if( strcmp("checkBox", szValue) == 0 )
//				{
//					pControl = NewData( Type_CheckBox );
//					if( pControl)
//						LoadCheckBox2_XML( lpControl, (S_CheckBoxData*)pControl );
//				}
//				else if( strcmp("edit", szValue) == 0 )
//				{
//					pControl = NewData( Type_Edit );
//					if( pControl)
//						LoadEdit2_XML( lpControl, (S_EditData*)pControl );
//				}
//				else if( strcmp("text", szValue) == 0 )
//				{
//					pControl = NewData( Type_Text );
//					if( pControl)
//						LoadText2_XML( lpControl, (S_TextData*)pControl );
//				}
//				else if( strcmp("list", szValue) == 0 )
//				{
//					pControl = NewData( Type_List );
//					if( pControl)
//						LoadList2_XML( lpControl, (S_ListData*)pControl );
//				}
//				else if( strcmp("listImg", szValue) == 0 )
//				{
//					pControl = NewData( Type_ListImg );
//					if( pControl)
//						LoadListImg2_XML( lpControl, (S_ListImgData*)pControl );
//				}
//				else if( strcmp("scrollBar", szValue) == 0 )
//				{
//					pControl = NewData( Type_ScrollBar );
//					if( pControl)
//						LoadScrollBar2_XML( lpControl, (S_ScrollBarData*)pControl );
//				}
//				else if( strcmp("comboBox", szValue) == 0 )
//				{
//					pControl = NewData( Type_ComboBox );
//					if( pControl)
//						LoadComboBox2_XML( lpControl, (S_ComboBoxData*)pControl );
//				}
//				else if( strcmp("picture", szValue) == 0 )
//				{
//					pControl = NewData( Type_Picture );
//					if( pControl)
//						LoadPicture2_XML( lpControl, (S_PictureData*)pControl );
//				}
//				else if( strcmp("progress", szValue) == 0 )
//				{
//					pControl = NewData( Type_Progress );
//					if( pControl)
//						LoadProgress2_XML( lpControl, (S_ProgressData*)pControl );
//				}
//				else if( strcmp("tab", szValue) == 0 )
//				{
//					pControl = NewData( Type_Tab );
//					if( pControl)
//						LoadTab2_XML( lpControl, (S_TabData*)pControl );
//				}
//				else if( strcmp("listEx", szValue) == 0 )
//				{
//					pControl = NewData( Type_ListEx );
//					if( pControl)
//						LoadListEx2_XML( lpControl, (S_ListExData*)pControl );
//				}
//				else if( strcmp("scrollBarEx", szValue) == 0 )
//				{
//					pControl = NewData( Type_ScrollBarEx );
//					if( pControl)
//						LoadScrollBarEx2_XML( lpControl, (S_ScrollBarExData*)pControl );
//				}
//
//				if( pControl )
//				{
//					m_pstControlData.push_back( pControl );
//				}
//			}
//		}
//	}
//}

bool S_UIData::LoadButton2_XML( MeXmlElement* pXmlUI, S_ButtonData* data )
{
	guardfunc;
	const char* szValue = NULL;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}

	MeXmlElement* lpMouseOnPic = pXmlUI->FirstChildElement("moveOnPic");
	if( lpMouseOnPic )
	{
        LoadPic_BaseAttribute2_XML( lpMouseOnPic, &data->m_stMoveOnPic );

#ifndef UPGRADE_UI // 启动旧版本UI升级
//         szValue = lpMouseOnPic->Attribute("字体");
//         if( szValue )
//         {
//             strncpy( data->m_szFontMoveOn, szValue, sizeof( data->m_szFontMoveOn ) - 1 );
//         }
        lpMouseOnPic->QueryIntAttribute("字体大小", &data->m_nFontSizeMoveOn );
		UpdateScaledFontSize( data->m_nFontSizeMoveOn );
        szValue = lpMouseOnPic->Attribute("字体颜色");
        if( szValue )
        {
            int a = 0, r = 0, g = 0, b = 0;
            sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
            DWORD color = ( ((/*a &*/ 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
            data->m_colFontMoveOn = color;
        }
		int n_isFontBoldMoveOn = 0;
        lpMouseOnPic->QueryIntAttribute("粗体", &n_isFontBoldMoveOn);
		data->m_isFontBoldMoveOn = n_isFontBoldMoveOn;
#endif
	}
	MeXmlElement* lpMousePress = pXmlUI->FirstChildElement("movePress");
	if( lpMousePress )
	{
        LoadPic_BaseAttribute2_XML( lpMousePress, &data->m_stPressPic );

#ifndef UPGRADE_UI // 启动旧版本UI升级
//         szValue = lpMousePress->Attribute("字体");
//         if( szValue )
//         {
//             strncpy( data->m_szFontPress, szValue, sizeof( data->m_szFontPress ) - 1 );
//         }
        lpMousePress->QueryIntAttribute("字体大小", &data->m_nFontSizePress );
		UpdateScaledFontSize( data->m_nFontSizePress );
        szValue = lpMousePress->Attribute("字体颜色");
        if( szValue )
        {
            int a = 0, r = 0, g = 0, b = 0;
            sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
            DWORD color = ( ((/*a &*/ 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
            data->m_colFontPress = color;
        }
		int n_isFontBoldPress = 0; 
        lpMousePress->QueryIntAttribute("粗体", &n_isFontBoldPress);
		data->m_isFontBoldPress = n_isFontBoldPress;
#endif
	}
	MeXmlElement* lpDisable = pXmlUI->FirstChildElement("disable");
	if( lpDisable )
	{
        LoadPic_BaseAttribute2_XML( lpDisable, &data->m_stDisabledPic );

#ifndef UPGRADE_UI // 启动旧版本UI升级
//         szValue = lpDisable->Attribute("字体");
//         if( szValue )
//         {
//             strncpy( data->m_szFontDisabled, szValue, sizeof( data->m_szFontDisabled ) - 1 );
//         }
        lpDisable->QueryIntAttribute("字体大小", &data->m_nFontSizeDisabled );
		UpdateScaledFontSize( data->m_nFontSizeDisabled );
        szValue = lpDisable->Attribute("字体颜色");
        if( szValue )
        {
            int a = 0, r = 0, g = 0, b = 0;
            sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
            DWORD color = ( ((/*a &*/ 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
            data->m_colFontDisabled = color;
        }
		int n_isFontBoldDisabled = 0;
        lpDisable->QueryIntAttribute("粗体", &n_isFontBoldDisabled);
		data->m_isFontBoldDisabled = n_isFontBoldDisabled;
#endif
	}

#ifndef UPGRADE_UI // 启动旧版本UI升级
    szValue = pXmlUI->Attribute("文本");
    if( szValue )
    {
        strncpy( data->m_szText, szValue, sizeof( data->m_szText ) - 1 );
    }
    szValue = pXmlUI->Attribute("字体");
    if( szValue )
    {
        strncpy( data->m_szFontNormal, szValue, sizeof( data->m_szFontNormal ) - 1 );
    }
    pXmlUI->QueryIntAttribute("字体大小", &data->m_nFontSizeNormal );
	UpdateScaledFontSize( data->m_nFontSizeNormal );
    szValue = pXmlUI->Attribute("字体颜色");
    if( szValue )
    {
        int a = 0, r = 0, g = 0, b = 0;
        sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
        DWORD color = ( ((/*a &*/ 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
        data->m_colFontNormal = color;
    }
	int n_isFontBoldNormal = 0;
    pXmlUI->QueryIntAttribute("粗体", &n_isFontBoldNormal);
	data->m_isFontBoldNormal = n_isFontBoldNormal;
#endif
	return true;
	unguard;
}
bool S_UIData::LoadCheckBox2_XML( MeXmlElement* pXmlUI, S_CheckBoxData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;

	int nChecked = 0;
	pXmlUI->QueryIntAttribute( "是否选择", &nChecked );
	data->m_bChecked = nChecked;

	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpbuttonClild = pXmlUI->FirstChildElement("button");
	if( lpbuttonClild )
	{
		if( !LoadButton2_XML( lpbuttonClild, &data->m_stChecked ) )
			return false;
	}
	return true;
	unguard;
}
bool S_UIData::LoadEdit2_XML( MeXmlElement* pXmlUI, S_EditData*	data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	int nTemp = 0;
	if(MEXML_SUCCESS == pXmlUI->QueryIntAttribute( "是否多行", &nTemp))
	{
		data->m_bSingleLine = !(bool)nTemp;
	}
	if(MEXML_SUCCESS == pXmlUI->QueryIntAttribute( "滚动条右边", &nTemp))
	{
		data->m_bRightScrollBar = nTemp;
	}
	pXmlUI->QueryIntAttribute( "是否只读", &nTemp);
	data->m_bReadOnly = nTemp;
	pXmlUI->QueryIntAttribute( "是否密码显示", &nTemp);
	data->m_bPassword = nTemp;
	pXmlUI->QueryIntAttribute( "是否数字显示", &nTemp);
	data->m_bIsNumber  = nTemp;
	pXmlUI->QueryIntAttribute( "文本对齐", &data->m_nTextAlign );

	const char* szValue = pXmlUI->Attribute("说明");
	if( szValue )
	{
		strncpy( data->m_szText, szValue, sizeof( data->m_szText ) - 1 );
	}

	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	if (!data->m_bSingleLine)
	{
		MeXmlElement* lpScrollBarChild = pXmlUI->FirstChildElement("scrollBar");
		if( lpScrollBarChild )
		{
			if( !LoadScrollBar2_XML( lpScrollBarChild, &data->m_stScrollBar ) )
				return false;
		}
	}
	return true;

	unguard;
}
bool S_UIData::LoadComboBox2_XML( MeXmlElement* pXmlUI, S_ComboBoxData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpEdieChild = pXmlUI->FirstChildElement("edit");
	if( lpEdieChild )
	{
		if( !LoadEdit2_XML( lpEdieChild, &data->m_stEdit ) )
			return false;
	}
	MeXmlElement* lpListChild = pXmlUI->FirstChildElement("list");
	if( lpListChild )
	{
		if( !LoadList2_XML( lpListChild, &data->m_stList ) )
			return false;
	}
	MeXmlElement* lpbuttonClild = pXmlUI->FirstChildElement("button");
	if( lpbuttonClild )
	{
		if( !LoadButton2_XML( lpbuttonClild, &data->m_stButton ) )
			return false;
	}
	return true;
	unguard;
}
bool S_UIData::LoadPicture2_XML( MeXmlElement* pXmlUI, S_PictureData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		return LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data );
	}
	return false;
	unguard;
}

bool S_UIData::LoadProgress2_XML( MeXmlElement* pXmlUI, S_ProgressData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement( "baseAttribute" );
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, ( S_BaseData* )data ) )
        {
            return false;
        }
	}
	
    // 以下为新增功能，为兼容老版本，此字段可以没有
    MeXmlElement* pXmlType = pXmlUI->FirstChildElement( "progressType" );
    if( pXmlType )
    {
        int nTemp( 0 );
        if( MEXML_SUCCESS == pXmlType->QueryIntAttribute( "是否竖直", &nTemp ) )
        {
            data->m_bVertical = nTemp;
        }
        if( MEXML_SUCCESS == pXmlType->QueryIntAttribute( "是否反向", &nTemp ) )
        {
            data->m_bReverse = nTemp;
        }
    }

    MeXmlElement* pXmlAni = pXmlUI->FirstChildElement( "animation" );
    if( pXmlAni )
    {
        const char* szAniPath = NULL;
        int nTemp( 0 );

        szAniPath = pXmlAni->Attribute( "资源路径" );
        if( szAniPath )
        {
            strncpy_s( data->m_szAniPath, szAniPath, sizeof( data->m_szAniPath ) / sizeof( char ) - 1 );
        }
        if( MEXML_SUCCESS == pXmlAni->QueryIntAttribute( "仅为特效", &nTemp ) )
        {
            data->m_bAniOnly = nTemp;
        }
        if( MEXML_SUCCESS == pXmlAni->QueryIntAttribute( "自动播放", &nTemp ) )
        {
            data->m_bAutoPlay = nTemp;
        }
    }

    return true;
	unguard;
}

bool S_UIData::LoadScrollBarEx2_XML( MeXmlElement* pXmlUI, S_ScrollBarExData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;

    MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("scrollBar");
    if( lpBaseAttribute )
    {
        return LoadScrollBar2_XML( lpBaseAttribute, data );
    }
	return false;
	//MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	//if( lpBaseAttribute )
	//{
	//	if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) ){ return; }
	//}
	unguard;
}
bool S_UIData::LoadListEx2_XML( MeXmlElement* pXmlUI, S_ListExData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	const char* szValue = NULL;
	szValue = pXmlUI->Attribute( "选中颜色" );
	if( szValue )
	{
		int a = 0, r = 0, g = 0, b = 0;
		sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
		DWORD color = ( ((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
		data->m_colSelBar = color;
	}
	pXmlUI->QueryIntAttribute( "Item高度", &data->m_nItemHeight );
	pXmlUI->QueryIntAttribute( "Item宽度", &data->m_nItemWidth );
	pXmlUI->QueryIntAttribute( "宽度偏移量", &data->m_nOffsetWidth );
	pXmlUI->QueryIntAttribute( "高度偏移量", &data->m_nOffsetHeight );
	pXmlUI->QueryIntAttribute( "item最大数量", &data->m_nMaxHeightCount );
	int nTemp = 0;
	pXmlUI->QueryIntAttribute( "icon可以被拖", (int*)& nTemp);
	data->m_bCanbePick = nTemp;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpScrollBarChild = pXmlUI->FirstChildElement("scrollBar");
	if( lpScrollBarChild )
	{
		if( !LoadScrollBar2_XML( lpScrollBarChild, &data->m_stScrollBar ) )
			return false;
	}
	return true;
	unguard;
}
bool S_UIData::LoadTab2_XML( MeXmlElement* pXmlUI, S_TabData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	pXmlUI->QueryIntAttribute( "翻页个数", &data->m_nTabCount );
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpFrameClild = pXmlUI->FirstChildElement("frame");
	if( lpFrameClild )
	{
		if( !LoadFrame2_XML( lpFrameClild, &data->m_frame ) )
			return false;
	}
	const char* szValue = NULL;
	int i=0;
	MeXmlElement* pXmlChild = pXmlUI->FirstChildElement("tabChild");
	while( pXmlChild )
	{
		szValue = pXmlChild->Attribute("value");
		if( szValue )
			strncpy( data->m_szFrameFileName[i], szValue, sizeof(data->m_szFrameFileName[i]) - 1 );

		MeXmlElement* lpbuttonClild = pXmlUI->FirstChildElement("button");
		if( lpbuttonClild )
		{
			if( !LoadButton2_XML( lpbuttonClild, &data->m_btnTab[i] ) )
				return false;
		}
		++i;
	
		pXmlChild = pXmlChild->NextSiblingElement();
	}
	return true;

	unguard;
}
bool S_UIData::LoadText2_XML( MeXmlElement* pXmlUI, S_TextData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	pXmlUI->QueryIntAttribute( "文本对齐", &data->m_nTextAlign );

	int nTemp = 1;
	pXmlUI->QueryIntAttribute( "滚动条右边", &nTemp);
	data->m_bRightScrollBar = nTemp;
	if(MEXML_SUCCESS == pXmlUI->QueryIntAttribute( "单行显示", &nTemp))
	{
		data->m_bSingleLine = nTemp;
	}
	const char* szValue = pXmlUI->Attribute("说明");
	if( szValue )
	{
		strncpy( data->m_szText, szValue, sizeof( data->m_szText ) - 1 );
	}

	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	if (!data->m_bSingleLine)
	{
		MeXmlElement* lpScrollBarChild = pXmlUI->FirstChildElement("scrollBar");
		if( lpScrollBarChild )
		{
			if( !LoadScrollBar2_XML( lpScrollBarChild, &data->m_stScrollBar ) )
				return false;
		}
	}
	return true;
	unguard;
}
bool S_UIData::LoadList2_XML( MeXmlElement* pXmlUI, S_ListData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	const char* szValue = NULL;
	szValue = pXmlUI->Attribute("选中颜色");
	if( szValue )
	{
		int a = 0, r = 0, g = 0, b = 0;
		sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
		DWORD color = ( ((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
		data->m_colSelBar = color;
	}
	pXmlUI->QueryIntAttribute( "Item高度", &data->m_nItemHeight );
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpScrollBarChild = pXmlUI->FirstChildElement("scrollBar");
	if( lpScrollBarChild )
	{
		if( !LoadScrollBar2_XML( lpScrollBarChild, &data->m_stScrollBar ) )
			return false;
	}
	return true;
	unguard;
}
bool S_UIData::LoadListImg2_XML( MeXmlElement* pXmlUI, S_ListImgData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	const char* szValue = NULL;
	pXmlUI->QueryIntAttribute( "item图片大小", &data->m_nIconSize );
	pXmlUI->QueryIntAttribute( "宽度偏移量", &data->m_nOffsetWidth );
	pXmlUI->QueryIntAttribute( "高度偏移量", &data->m_nOffsetHeight );
	pXmlUI->QueryIntAttribute( "item最大个数", &data->m_nMaxHeightCount );
	int nTemp = 0;
	pXmlUI->QueryIntAttribute( "icon可以被拖", (int*)& nTemp);
	data->m_bCanbePick = nTemp;
	pXmlUI->QueryIntAttribute( "显示选中框", (int*)&nTemp );
	data->m_bShowSelFrame = nTemp;

	szValue = pXmlUI->Attribute("选中框颜色");
	if( szValue )
	{
		int a = 0, r = 0, g = 0, b = 0;
		sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
		DWORD color = ( ((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
		data->m_colSelFrame = color;
	}
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	MeXmlElement* lpScrollBarChild = pXmlUI->FirstChildElement("scrollBar");
	if( lpScrollBarChild )
	{
		if( !LoadScrollBar2_XML( lpScrollBarChild, &data->m_stScrollBar ) )
			return false;
	}
	return true;
	unguard;
}
bool S_UIData::LoadScrollBar2_XML( MeXmlElement* pXmlUI, S_ScrollBarData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	int iIndex = 0;
	MeXmlElement* lpbuttonClild = pXmlUI->FirstChildElement("button");
	while( lpbuttonClild )
	{
		if( iIndex == 0 )
		{
			if( !LoadButton2_XML( lpbuttonClild, &data->m_stUp ) )
				return false;
		}
		else if( iIndex == 1 )
		{
			if( !LoadButton2_XML( lpbuttonClild, &data->m_stDown ) )
				return false;
		}
		else if( iIndex == 2 )
		{
			if( !LoadButton2_XML( lpbuttonClild, &data->m_stBar ) )
				return false;
		}

		lpbuttonClild = lpbuttonClild->NextSiblingElement();

		++iIndex;
	}
	return true;
	unguard;
}
void S_UIData::LoadPic_BaseAttribute2_XML( MeXmlElement* pXmlUI, S_BaseData::S_Pic* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return;

	const char* szValue = NULL;
	szValue = pXmlUI->Attribute("资源路径");
	if( szValue )
		strncpy( data->m_szPicName, szValue, sizeof( data->m_szPicName ) - 1 );
	szValue = pXmlUI->Attribute("背景图外框");
	if( szValue )
	{
		int x = 0, y = 0, w = 0, h = 0;
		sscanf( szValue, "%d, %d, %d, %d", &x, &y, &w, &h );
		data->m_rcFrame.left = x;	data->m_rcFrame.top = y;
		data->m_rcFrame.right = w;	data->m_rcFrame.bottom = h;
	}
	szValue = pXmlUI->Attribute("背景图内框");
	if( szValue )
	{
		int x = 0, y = 0, w = 0, h = 0;
		sscanf( szValue, "%d, %d, %d, %d", &x, &y, &w, &h );
		data->m_rcClient.left = x;		data->m_rcClient.top = y;
		data->m_rcClient.right = w;		data->m_rcClient.bottom = h;
	}
	unguard;
}
void S_UIData::LoadHead2_XML( MeXmlElement* pXmlUI, S_UIHead2* data )
{
    guardfunc;
    if( !pXmlUI || !data)
        return;

	int nTemp = 0;
    pXmlUI->QueryIntAttribute("创建时间", (int*)&nTemp);
	data->m_dwCreatedDate = nTemp;
    pXmlUI->QueryIntAttribute("控件个数", (int*)&data->m_nControlsCount);

    std::string index = "控件类型";
    char buf[128] = {0};
    for (int i = 0; i < data->m_nControlsCount; ++i)
    {
        itoa(i, buf, 10);
        index += buf;
        pXmlUI->QueryIntAttribute(index.c_str(), (int*)&data->m_nControlsType[i]);
    }

    unguard;
}
bool S_UIData::LoadFrame2_XML( MeXmlElement* pXmlUI, S_FrameData* data )
{
	guardfunc;
	if( !pXmlUI || !data)
		return false;

	const char* szValue = NULL;

	szValue = pXmlUI->Attribute("排列方式");
	if( szValue )
	{
		if( strcmp("普通", szValue ) == 0 )
			data->m_nArrayMode = ArrayMode_Normal;
		else if( strcmp("置顶", szValue) == 0 )
			data->m_nArrayMode = ArrayMode_Top;
		else if( strcmp("置底", szValue) == 0 )
			data->m_nArrayMode = ArrayMode_Bottom;
	}
	int nTemp = 0;
	pXmlUI->QueryIntAttribute("是否可移动", (int*)&nTemp); 
	data->m_bMoveable = nTemp;

	MeXmlElement* lpBaseAttribute = pXmlUI->FirstChildElement("baseAttribute");
	if( lpBaseAttribute )
	{
		if( !LoadBaseAttribute2_XML( lpBaseAttribute, (S_BaseData*)data ) )
		{ return false; }
	}
	return true;

	unguard;
}
bool S_UIData::IsBadData( const RECT& rcRect )
{
	if( rcRect.left > 2000 ||
		rcRect.left < -2000 ||
		rcRect.right > 2000 ||
		rcRect.right < -2000 ||
		rcRect.top > 2000 ||
		rcRect.top < -2000 ||
		rcRect.bottom > 2000 ||
		rcRect.bottom < -2000 )
		return true;

	return false;
}
bool S_UIData::LoadBaseAttribute2_XML( MeXmlElement* pXmlUI, S_BaseData* data )
{
	guardfunc;
	if( !pXmlUI || !data )
		return false;
	const char* szValue = NULL;
	
    pXmlUI->QueryIntAttribute("控件类型", &data->m_nType);
    pXmlUI->QueryIntAttribute("对齐模式", &data->m_nAlignMode);
	//szValue = pXmlUI->Attribute("控件类型");
	//if( szValue )
	//{
	//	if( strcmp("框架", szValue) == 0 )
	//		data->m_nType = Type_Frame;
	//	else if( strcmp("按钮", szValue) == 0 )
	//		data->m_nType = Type_Button;
	//	else if( strcmp("多选框", szValue) == 0 )
	//		data->m_nType = Type_CheckBox;
	//	else if( strcmp("编辑框", szValue) == 0 )
	//		data->m_nType = Type_Edit;
	//	else if( strcmp("文本框", szValue) == 0 )
	//		data->m_nType = Type_Text;
	//	else if( strcmp("文本列表", szValue) == 0 )
	//		data->m_nType = Type_List;
	//	else if( strcmp("图像列表", szValue) == 0 )
	//		data->m_nType = Type_ListImg;
	//	else if( strcmp("滚动条", szValue) == 0 )
	//		data->m_nType = Type_ScrollBar;
	//	else if( strcmp("下拉框", szValue) == 0 )
	//		data->m_nType = Type_ComboBox;
	//	else if( strcmp("图像", szValue) == 0 )
	//		data->m_nType = Type_Picture;
	//	else if( strcmp("进条条", szValue) == 0 )
	//		data->m_nType = Type_Progress;
	//	else if( strcmp("属性页", szValue) == 0 )
	//		data->m_nType = Type_Tab;
	//	else if( strcmp("列表框扩展", szValue) == 0 )
	//		data->m_nType = Type_ListEx;
	//	else if( strcmp("滚动条扩展", szValue) == 0 )
	//		data->m_nType = Type_ScrollBarEx;
	//}
	//szValue = pXmlUI->Attribute("对齐模式");
	//if( szValue )
	//{
	//	if( strcmp("左上", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_LeftTop;
	//	else if( strcmp("右上", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_RightTop;
	//	else if( strcmp("左下", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_LeftBottom;
	//	else if( strcmp("右下", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_RightBottom;
	//	else if( strcmp("左中", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_Left;
	//	else if( strcmp("中上", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_Top;
	//	else if( strcmp("右中", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_Right;
	//	else if( strcmp("下", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_Bottom;
	//	else if( strcmp("中", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_Middle;
	//	else if( strcmp("中上", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_TopMiddle;
	//	else if( strcmp("左中", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_LeftMiddle;
	//	else if( strcmp("中下", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_BottomMiddle;
	//	else if( strcmp("右中", szValue) == 0 )
	//		data->m_nAlignMode = AlignMode_RightMiddle;
	//}
	int x = 0, y = 0, w = 0, h = 0;
	szValue = pXmlUI->Attribute("rect");
	if( szValue )
	{
		sscanf( szValue, "%d, %d, %d, %d", &x, &y, &w, &h );
		data->m_rcRealSize.left = x;
		data->m_rcRealSize.top = y;
		data->m_rcRealSize.right = w;
		data->m_rcRealSize.bottom = h;
// 		if( IsBadData( data->m_rcRealSize ) )
// 		{
// 			return false;
// 		}
	}
	szValue = pXmlUI->Attribute("id");
	if( szValue )
	{
		strncpy( data->m_szID, szValue, sizeof( data->m_szID ) - 1 );
	}
	szValue = pXmlUI->Attribute("内容");
	if( szValue )
	{
		strncpy( data->m_szCaption, szValue, sizeof( data->m_szCaption ) - 1 );
	}
	szValue = pXmlUI->Attribute("字体");
	if( szValue )
	{
		strncpy( data->m_szFont, szValue, sizeof( data->m_szFont ) - 1 );
	}
	szValue = pXmlUI->Attribute("Tips");
	if( szValue )
	{
		strncpy( data->m_szTips, szValue, sizeof(data->m_szTips) - 1 );
	}

	pXmlUI->QueryIntAttribute("字体大小", &data->m_nFontSize );
	UpdateScaledFontSize(data->m_nFontSize);
	szValue = pXmlUI->Attribute("字体颜色");
	int nFontBold = 0;
    pXmlUI->QueryIntAttribute("粗体", & nFontBold);
	data->m_isFontBold = nFontBold;
	if( szValue )
	{
		int a = 0, r = 0, g = 0, b = 0;
		sscanf( szValue, "%d, %d, %d, %d", &a, &r, &g, &b );
		DWORD color = ( ((/*a &*/ 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
		data->m_colFont = color;
	}
	MeXmlElement* lpBackPic = pXmlUI->FirstChildElement("backpicture");
	if( lpBackPic )
	{
		LoadPic_BaseAttribute2_XML( lpBackPic, &data->m_stBackPic );
	}
	MeXmlElement* lpDisableBackPic = pXmlUI->FirstChildElement("disablebackpicture");
	if( lpDisableBackPic )
	{
		LoadPic_BaseAttribute2_XML( lpDisableBackPic, &data->m_stDisablePic );
	}
	MeXmlElement* lpDrawMode = pXmlUI->FirstChildElement("绘制模式");
	if( lpDrawMode )
	{
		for( int i=0; i<S_BaseData::Mode_Max; ++i )
		{
			szValue = lpDrawMode->Attribute( szDrawModeName[i] );
			if( szValue )
			{
				if( strcmp( "普通", szValue ) == 0 )
					data->m_nDrawMode[i] = DrawModeNormal;
				else if( strcmp( "平铺", szValue ) == 0 )
					data->m_nDrawMode[i] = DrawModeTile;
				else if( strcmp( "拉伸", szValue ) == 0 )
					data->m_nDrawMode[i] = DrawModeStrectch;
			}
		}
	}
	return true;
	unguard;
}
DWORD S_UIData::LoadUnit(void *psData)
{
        for( int i = 0; i < m_pstControlData.size(); ++i )
		{
			delete m_pstControlData[i];
			m_pstControlData[i] = NULL;
		}
		m_pstControlData.clear();

        char *_psData = (char *)psData;
		// Read ver
		SVer stVer;
		//fread( &stVer, sizeof(stVer), 1, fp );
        memcpy(&stVer,_psData,sizeof(stVer));
        //_psData += sizeof(stVer);
		//fseek( fp, 0, SEEK_SET );
		//
		if ( strcmp( stVer.m_szVer, UI_VER2 ) == 0 )
		{
			//fread( &m_stHead, sizeof(m_stHead), 1, fp );
            memcpy( &m_stHead,_psData, sizeof(m_stHead));
            _psData += sizeof(m_stHead);
		}
		else if ( strcmp( stVer.m_szVer, UI_VER ) == 0 )
		{
			S_UIHead stHead;
			//fread( &stHead, sizeof(stHead), 1, fp );
            memcpy( &stHead,_psData, sizeof(stHead));
            _psData += sizeof(stHead);
			memcpy( &m_stHead, &stHead, sizeof(stHead) );
		}
		else
		{
			//fclose(fp);
			MessageBox( NULL, "读取的*.UI文件版本不一样!", "失败", MB_OK );
			return 0;
		}

		assert( m_stHead.m_nControlsCount < CONTROLS_COUNT_MAX2 );

		for( int n=0; n<m_stHead.m_nControlsCount; n++ )
		{
			S_BaseData* pControl = NewData( m_stHead.m_nControlsType[n] );
			switch( m_stHead.m_nControlsType[n] )
			{
			case Type_Button:
				//fread( pControl, sizeof(S_ButtonData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ButtonData));
                _psData += sizeof(S_ButtonData);
				break;
			case Type_CheckBox:
				//fread( pControl, sizeof(S_CheckBoxData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_CheckBoxData));
                _psData += sizeof(S_CheckBoxData);
				break;
			case Type_Edit:
				//fread( pControl, sizeof(S_EditData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_EditData));
                 _psData += sizeof(S_EditData);
				break;
			case Type_Text:
				//fread( pControl, sizeof(S_TextData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_TextData));
                 _psData += sizeof(S_TextData);
				break;
			case Type_List:
				//fread( pControl, sizeof(S_ListData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ListData));
                 _psData += sizeof(S_ListData);
				break;
			case Type_ListImg:
				//fread( pControl, sizeof(S_ListImgData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ListImgData));
                 _psData += sizeof(S_ListImgData);
				break;
			case Type_ScrollBar:
				//fread( pControl, sizeof(S_ScrollBarData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ScrollBarData));
                 _psData += sizeof(S_ScrollBarData);
				break;
			case Type_ScrollBarEx:
				//fread( pControl, sizeof(S_ScrollBarExData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ScrollBarExData));
                 _psData += sizeof(S_ScrollBarExData);
				break;
			case Type_ComboBox:
				//fread( pControl, sizeof(S_ComboBoxData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ComboBoxData));
                 _psData += sizeof(S_ComboBoxData);
				break;
			case Type_Picture:
				//fread( pControl, sizeof(S_PictureData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_PictureData));
                 _psData += sizeof(S_PictureData);
				break;
			case Type_Progress:
				//fread( pControl, sizeof(S_ProgressData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ProgressData));
                 _psData += sizeof(S_ProgressData);
				break;
			case Type_Tab:
				//fread( pControl, sizeof(S_TabData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_TabData));
                 _psData += sizeof(S_TabData);
				break;
			case Type_ListEx:
				//fread( pControl, sizeof(S_ListExData), 1, fp );
                memcpy( pControl,_psData, sizeof(S_ListExData));
                 _psData += sizeof(S_ListExData);
				break;
			default:
				assert( false );
				break;
			}
            m_pstControlData.push_back( pControl );
        }
		
        return 1;
}

/*#include "StringLanguageTranslator.h"*/

DWORD S_UIData::LoadFile( const char* pszFileName )
{
	guard(S_UIData::LoadFile);
	assert( pszFileName );
	assert( pszFileName[0] != 0 );

	//zizi load xml file
	std::string strName = pszFileName;
	std::string strExtern = strName.substr( strName.length() - 3, 3 );
	if( strcmp( strExtern.c_str(), "xml") == 0 ||
        stricmp( strName.substr( strName.length() - 4, 4 ).c_str(), "meui") == 0 )
	{
		for( int i = 0; i < m_pstControlData.size(); ++i )
		{
			delete m_pstControlData[i];
			m_pstControlData[i] = NULL;
		}
		m_pstControlData.clear();

		LoadFile_XML( pszFileName );
		return 1;
	}
    //--

	f_Handle *fp = packet_namespace::w_fopen(pszFileName, "rb" );
	if ( fp )
	{
		//
		//for( int n=0; n<CONTROLS_COUNT_MAX2; n++ )
		//{
		//	if ( m_pstControlData[n] )
		//	{
		//		delete m_pstControlData[n];
		//	}
		//}
		for( int i = 0; i < m_pstControlData.size(); ++i )
		{
			delete m_pstControlData[i];
			m_pstControlData[i] = NULL;
		}
		m_pstControlData.clear();

		// Read ver
		SVer stVer;
		packet_namespace::w_fread( &stVer, sizeof(stVer), 1, fp );
		packet_namespace::w_fseek( fp, 0, SEEK_SET );
		//
		if ( strcmp( stVer.m_szVer, UI_VER2 ) == 0 )
		{
			packet_namespace::w_fread( &m_stHead, sizeof(m_stHead), 1, fp );
		}
		else if ( strcmp( stVer.m_szVer, UI_VER ) == 0 )
		{
			S_UIHead stHead;
			packet_namespace::w_fread( &stHead, sizeof(stHead), 1, fp );
			memcpy( &m_stHead, &stHead, sizeof(stHead) );
		}
		else
		{
			packet_namespace::w_fclose(fp);
			MessageBox( NULL, "读取的*.UI文件版本不一样!", "失败", MB_OK );
			return 0;
		}

		assert( m_stHead.m_nControlsCount < CONTROLS_COUNT_MAX2 );

		for( int n=0; n<m_stHead.m_nControlsCount; n++ )
		{
			S_BaseData* pControl = NewData( m_stHead.m_nControlsType[n] );
			switch( m_stHead.m_nControlsType[n] )
			{
			case Type_Button:
				packet_namespace::w_fread( pControl, sizeof(S_ButtonData), 1, fp );
				break;
			case Type_CheckBox:
				packet_namespace::w_fread( pControl, sizeof(S_CheckBoxData), 1, fp );
				break;
			case Type_Edit:
				packet_namespace::w_fread( pControl, sizeof(S_EditData), 1, fp );
				break;
			case Type_Text:
				packet_namespace::w_fread( pControl, sizeof(S_TextData), 1, fp );
				break;
			case Type_List:
				packet_namespace::w_fread( pControl, sizeof(S_ListData), 1, fp );
				break;
			case Type_ListImg:
				packet_namespace::w_fread( pControl, sizeof(S_ListImgData), 1, fp );
				break;
			case Type_ScrollBar:
				packet_namespace::w_fread( pControl, sizeof(S_ScrollBarData), 1, fp );
				break;
			case Type_ScrollBarEx:
				packet_namespace::w_fread( pControl, sizeof(S_ScrollBarExData), 1, fp );
				break;
			case Type_ComboBox:
				packet_namespace::w_fread( pControl, sizeof(S_ComboBoxData), 1, fp );
				break;
			case Type_Picture:
				packet_namespace::w_fread( pControl, sizeof(S_PictureData), 1, fp );
				break;
			case Type_Progress:
				packet_namespace::w_fread( pControl, sizeof(S_ProgressData), 1, fp );
				break;
			case Type_Tab:
				packet_namespace::w_fread( pControl, sizeof(S_TabData), 1, fp );
				break;
			case Type_ListEx:
				packet_namespace::w_fread( pControl, sizeof(S_ListExData), 1, fp );
				break;
			default:
				assert( false );
				break;
			}
            
            // modify
            sprintf_s( pControl->m_szCaption, sizeof(pControl->m_szCaption), /*ST*/(pControl->m_szCaption) );

			m_pstControlData.push_back( pControl );
		}

		packet_namespace::w_fclose(fp);
		return 1;
	}
	return 0;
	unguard;
}
void S_UIData::SetEventFunName( int index, E_Event_Type type, const char* name )
{
	m_szControlEventName[index][type] = name;
}
void S_UIData::UpdateScaledFontSize( int& nFontSize )
{
	nFontSize *= g_FontSizeScale; 
}
//zizi add
void S_UIData::SaveFile_XML( const char* pszFileName )
{
	std::string strPath = pszFileName;
	//int nOff = 0, nResult = 0;
	//std::string strNameNoEx;
	//int nDot = 0;
	//while( 1 )
	//{
	//	nResult = strPath.find("\\", nOff+1);

	//	if( nResult == -1 )
	//	{
	//		nDot = strPath.find(".", nOff+1);
	//		strNameNoEx = strPath.substr( nOff + 1, nDot - nOff - 1);
	//		strPath.erase( nOff + 1, strPath.length() - nOff - 1);
	//		strPath += strNameNoEx.c_str();
	//		strPath += ".xml";
	//		break;
	//	}
	//	nOff = nResult;
	//}

	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "gb2312", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement*rootUI = doc.InsertEndChild("UI");
	writeUI_XML(rootUI);

	doc.SaveFile( strPath.c_str() );

}
void S_UIData::writeUI_XML(MeXmlElement *pXmlUI)
{
	//  脚本和事件一会再写
	//MeXmlElement baseAttribute("script");
	//baseAttribute.Attribute( "脚本文件", )

    writeHead_XML( pXmlUI, &m_stHead );

	writeFrame_XML( pXmlUI, &m_stHead.m_stFrameData );

	for( int i = 0; i < m_pstControlData.size(); ++i )
	{
		switch( m_pstControlData[i]->m_nType )
		{
		case Type_Button:
			writeButton_XML( pXmlUI, (S_ButtonData*)m_pstControlData[i] );
			break;
		case Type_CheckBox:
			writeCheckBox_XML(  pXmlUI, (S_CheckBoxData*)m_pstControlData[i] );
			break;
		case Type_Edit:
			writeEdit_XML(  pXmlUI, (S_EditData*)m_pstControlData[i] );
			break;
		case Type_Text:
			writeText_XML(  pXmlUI, (S_TextData*)m_pstControlData[i] );
			break;
		case Type_List:
			writeList_XML(  pXmlUI, (S_ListData*)m_pstControlData[i] );
			break;
		case Type_ListImg:
			writeListImg_XML(  pXmlUI, (S_ListImgData*)m_pstControlData[i] );
			break;
		case Type_ScrollBar:
			writeScrollBar_XML(  pXmlUI, (S_ScrollBarData*)m_pstControlData[i] );
			break;
		case Type_ComboBox:
			writeComboBox_XML(  pXmlUI, (S_ComboBoxData*)m_pstControlData[i] );
			break;
		case Type_Picture:
			writePicture_XML(  pXmlUI, (S_PictureData*)m_pstControlData[i] );
			break;
		case Type_Progress:
			writeProgress_XML(  pXmlUI, (S_ProgressData*)m_pstControlData[i] );
			break;
		case Type_Tab:
			writeTab_XML(  pXmlUI, (S_TabData*)m_pstControlData[i] );
			break;
		case Type_ListEx:
			writeListEx_XML(  pXmlUI, (S_ListExData*)m_pstControlData[i] );
			break;
		case Type_ScrollBarEx:
			writeScrollbarEx_XML(  pXmlUI, (S_ScrollBarExData*)m_pstControlData[i] );
			break;
		}
	}

}
void S_UIData::writeHead_XML(MeXmlElement *pXmlUI, S_UIHead2* data)
{
	MeXmlElement* rootHead =     pXmlUI->InsertEndChild("head");

    rootHead->SetAttribute("创建时间", data->m_dwCreatedDate);
    rootHead->SetAttribute("控件个数", data->m_nControlsCount);
    std::string index = "控件类型";
    char buf[128] = {0};
    for (int i = 0; i < data->m_nControlsCount; ++i)
    {
        itoa(i, buf, 10);
        index += buf;
        rootHead->SetAttribute(index.c_str(), data->m_nControlsType[i]);
    }
}
void S_UIData::writeFrame_XML( MeXmlElement *pXmlUI, S_FrameData* data )
{
	MeXmlElement* rootFrame =     pXmlUI->InsertEndChild("frame");

	if( ArrayMode_Normal == m_stHead.m_stFrameData.m_nArrayMode )
		rootFrame->SetAttribute( "排列方式", "普通" );
	else if( ArrayMode_Top == m_stHead.m_stFrameData.m_nArrayMode )
		rootFrame->SetAttribute( "排列方式", "置顶" );
	if( ArrayMode_Bottom == m_stHead.m_stFrameData.m_nArrayMode )
		rootFrame->SetAttribute( "排列方式", "置底" );

	rootFrame->SetAttribute( "是否可移动", m_stHead.m_stFrameData.m_bMoveable );

	writeControlBase_XML( rootFrame, (S_BaseData*)data );

}
void S_UIData::writeButton_XML( MeXmlElement *pXmlUI, S_ButtonData* data )
{
	MeXmlElement *rootButton = pXmlUI->InsertEndChild("button");

	writeControlBase_XML( rootButton, (S_BaseData*)data );

	char szRect[56] = {0};

    {
        MeXmlElement *baseAttribute_pic_moveOn = rootButton->InsertEndChild("moveOnPic");
        baseAttribute_pic_moveOn->SetAttribute( "资源路径", data->m_stMoveOnPic.m_szPicName );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stMoveOnPic.m_rcFrame.left, data->m_stMoveOnPic.m_rcFrame.top,
            data->m_stMoveOnPic.m_rcFrame.right, data->m_stMoveOnPic.m_rcFrame.bottom );
        baseAttribute_pic_moveOn->SetAttribute( "背景图外框", szRect );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stMoveOnPic.m_rcClient.left, data->m_stMoveOnPic.m_rcClient.top,
            data->m_stMoveOnPic.m_rcClient.right, data->m_stMoveOnPic.m_rcClient.bottom );
        baseAttribute_pic_moveOn->SetAttribute( "背景图内框", szRect );

#ifndef UPGRADE_UI // 启动旧版本UI升级
        //baseAttribute_pic_moveOn->SetAttribute("字体", data->m_szFontMoveOn);
        baseAttribute_pic_moveOn->SetAttribute("字体大小", data->m_nFontSizeMoveOn);
        int a = (data->m_colFontMoveOn>>24) & 0xff;
        int r = (data->m_colFontMoveOn>>16) & 0xff;
        int g = (data->m_colFontMoveOn>>8) & 0xff;
        int b = data->m_colFontMoveOn & 0xff;
        sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
        baseAttribute_pic_moveOn->SetAttribute( "字体颜色", szRect );
        baseAttribute_pic_moveOn->SetAttribute( "粗体", data->m_isFontBoldMoveOn );
#endif

    }

    {
        MeXmlElement *baseAttribute_pic_press = rootButton->InsertEndChild("movePress");
        baseAttribute_pic_press->SetAttribute( "资源路径", data->m_stPressPic.m_szPicName );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stPressPic.m_rcFrame.left, data->m_stPressPic.m_rcFrame.top,
            data->m_stPressPic.m_rcFrame.right, data->m_stPressPic.m_rcFrame.bottom );
        baseAttribute_pic_press->SetAttribute( "背景图外框", szRect );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stPressPic.m_rcClient.left, data->m_stPressPic.m_rcClient.top,
            data->m_stPressPic.m_rcClient.right, data->m_stPressPic.m_rcClient.bottom );
        baseAttribute_pic_press->SetAttribute( "背景图内框", szRect );

#ifndef UPGRADE_UI // 启动旧版本UI升级
        //baseAttribute_pic_press->SetAttribute("字体", data->m_szFontPress);
        baseAttribute_pic_press->SetAttribute("字体大小", data->m_nFontSizePress);
        int a = (data->m_colFontPress>>24) & 0xff;
        int r = (data->m_colFontPress>>16) & 0xff;
        int g = (data->m_colFontPress>>8) & 0xff;
        int b = data->m_colFontPress & 0xff;
        sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
        baseAttribute_pic_press->SetAttribute( "字体颜色", szRect );
        baseAttribute_pic_press->SetAttribute( "粗体", data->m_isFontBoldPress );
#endif

    }

    {
        MeXmlElement *baseAttribute_pic_dis = rootButton->InsertEndChild("disable");
        baseAttribute_pic_dis->SetAttribute( "资源路径", data->m_stDisabledPic.m_szPicName );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stDisabledPic.m_rcFrame.left, data->m_stDisabledPic.m_rcFrame.top,
            data->m_stDisabledPic.m_rcFrame.right, data->m_stDisabledPic.m_rcFrame.bottom );
        baseAttribute_pic_dis->SetAttribute( "背景图外框", szRect );
        sprintf( szRect, "%d, %d, %d, %d", data->m_stDisabledPic.m_rcClient.left, data->m_stDisabledPic.m_rcClient.top,
            data->m_stDisabledPic.m_rcClient.right, data->m_stDisabledPic.m_rcClient.bottom );
        baseAttribute_pic_dis->SetAttribute( "背景图内框", szRect );

#ifndef UPGRADE_UI // 启动旧版本UI升级
        //baseAttribute_pic_dis->SetAttribute("字体", data->m_szFontDisabled);
        baseAttribute_pic_dis->SetAttribute("字体大小", data->m_nFontSizeDisabled);
        int a = (data->m_colFontDisabled>>24) & 0xff;
        int r = (data->m_colFontDisabled>>16) & 0xff;
        int g = (data->m_colFontDisabled>>8) & 0xff;
        int b = data->m_colFontDisabled & 0xff;
        sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
        baseAttribute_pic_dis->SetAttribute( "字体颜色", szRect );
        baseAttribute_pic_dis->SetAttribute( "粗体", data->m_isFontBoldDisabled );
#endif

    }

#ifndef UPGRADE_UI // 启动旧版本UI升级
    rootButton->SetAttribute("文本", data->m_szText);
    rootButton->SetAttribute("字体", data->m_szFontNormal);
    rootButton->SetAttribute("字体大小", data->m_nFontSizeNormal);
    int a = (data->m_colFontNormal>>24) & 0xff;
    int r = (data->m_colFontNormal>>16) & 0xff;
    int g = (data->m_colFontNormal>>8) & 0xff;
    int b = data->m_colFontNormal & 0xff;
    sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
    rootButton->SetAttribute( "字体颜色", szRect );
    rootButton->SetAttribute( "粗体", data->m_isFontBoldNormal );
#endif

}
void S_UIData::writeCheckBox_XML( MeXmlElement *pXmlUI, S_CheckBoxData* data )
{
	MeXmlElement *rootCheckBox = pXmlUI->InsertEndChild("checkBox");

	writeControlBase_XML( rootCheckBox, (S_BaseData*)data );

	rootCheckBox->SetAttribute( "是否选择", data->m_bChecked );
	writeButton_XML( rootCheckBox, &data->m_stChecked );

}
void S_UIData::writeEdit_XML( MeXmlElement *pXmlUI, S_EditData* data )
{
	MeXmlElement *rootEdit = pXmlUI->InsertEndChild("edit");

	writeControlBase_XML( rootEdit, (S_BaseData*)data );

	rootEdit->SetAttribute( "滚动条右边", data->m_bRightScrollBar );
	rootEdit->SetAttribute( "是否多行", !data->m_bSingleLine );
	rootEdit->SetAttribute( "是否只读", data->m_bReadOnly );
	rootEdit->SetAttribute( "是否密码显示", data->m_bPassword );
	rootEdit->SetAttribute( "是否数字显示", data->m_bIsNumber );
	rootEdit->SetAttribute( "文本对齐", data->m_nTextAlign );
	rootEdit->SetAttribute("说明", data->m_szText);

	if (!data->m_bSingleLine)
	{
		writeScrollBar_XML( rootEdit, &data->m_stScrollBar );
	}

}
void S_UIData::writeText_XML( MeXmlElement *pXmlUI, S_TextData* data )
{
	MeXmlElement *rootText = pXmlUI->InsertEndChild("text");

	writeControlBase_XML( rootText, (S_BaseData*)data );

	rootText->SetAttribute( "滚动条右边", data->m_bRightScrollBar );
	rootText->SetAttribute( "单行显示", data->m_bSingleLine );
	rootText->SetAttribute( "文本对齐", data->m_nTextAlign );
	rootText->SetAttribute("说明", data->m_szText);

	if (!data->m_bSingleLine)
	{
		writeScrollBar_XML( rootText, &data->m_stScrollBar );
	}
}
void S_UIData::writeList_XML( MeXmlElement *pXmlUI, S_ListData* data )
{
	MeXmlElement *rootList = pXmlUI->InsertEndChild("list");

	writeControlBase_XML( rootList, (S_BaseData*)data );

	char szRect[56] = {0};
	int a = (data->m_colSelBar>>24) & 0xff;
	int r = (data->m_colSelBar>>16) & 0xff;
	int g = (data->m_colSelBar>>8) & 0xff;
	int b = data->m_colSelBar & 0xff;
	sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
	rootList->SetAttribute( "选中颜色", szRect );

	rootList->SetAttribute( "Item高度", data->m_nItemHeight );

	writeScrollBar_XML( rootList, &data->m_stScrollBar );

}
void S_UIData::writeListImg_XML( MeXmlElement *pXmlUI, S_ListImgData* data )
{
	MeXmlElement *rootListImg = pXmlUI->InsertEndChild("listImg");

	writeControlBase_XML( rootListImg, (S_BaseData*)data );

	rootListImg->SetAttribute( "item图片大小", data->m_nIconSize );
	rootListImg->SetAttribute( "宽度偏移量", data->m_nOffsetWidth );
	rootListImg->SetAttribute( "高度偏移量", data->m_nOffsetHeight );
	rootListImg->SetAttribute( "item最大个数", data->m_nMaxHeightCount );
	rootListImg->SetAttribute( "icon可以被拖", data->m_bCanbePick );
	rootListImg->SetAttribute( "显示选中框", data->m_bShowSelFrame );

	char szRect[56] = {0};
	int a = (data->m_colSelFrame>>24) & 0xff;
	int r = (data->m_colSelFrame>>16) & 0xff;
	int g = (data->m_colSelFrame>>8) & 0xff;
	int b = data->m_colSelFrame & 0xff;
	sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
	rootListImg->SetAttribute( "选中框颜色", szRect );

	writeScrollBar_XML( rootListImg, &data->m_stScrollBar );

}
void S_UIData::writeScrollBar_XML( MeXmlElement *pXmlUI, S_ScrollBarData* data )
{
	MeXmlElement* rootScrollBar = pXmlUI->InsertEndChild("scrollBar");

	writeControlBase_XML( rootScrollBar, (S_BaseData*)data );

	writeButton_XML( rootScrollBar, &data->m_stUp );
	writeButton_XML( rootScrollBar, &data->m_stDown );
	writeButton_XML( rootScrollBar, &data->m_stBar );

}
void S_UIData::writeComboBox_XML( MeXmlElement *pXmlUI, S_ComboBoxData* data )
{
	MeXmlElement *rootComboBox = pXmlUI->InsertEndChild("comboBox");

	writeControlBase_XML( rootComboBox, (S_BaseData*)data );

	writeEdit_XML( rootComboBox, &data->m_stEdit );
	writeList_XML( rootComboBox, &data->m_stList );
	writeButton_XML( rootComboBox, &data->m_stButton );
	
}
void S_UIData::writePicture_XML( MeXmlElement *pXmlUI, S_PictureData* data )
{
	MeXmlElement *rootPicture = pXmlUI->InsertEndChild("picture");

	writeControlBase_XML( rootPicture, (S_BaseData*)data );

}

void S_UIData::writeProgress_XML( MeXmlElement *pXmlUI, S_ProgressData* data )
{
	MeXmlElement* rootProgress = pXmlUI->InsertEndChild("progress");

	writeControlBase_XML( rootProgress, (S_BaseData*)data );

    MeXmlElement* typeChild = rootProgress->InsertEndChild( "progressType" );
    typeChild->SetAttribute( "是否竖直", data->m_bVertical );
    typeChild->SetAttribute( "是否反向", data->m_bReverse );

    MeXmlElement* aniChild = rootProgress->InsertEndChild( "animation" );
    aniChild->SetAttribute( "资源路径", data->m_szAniPath );
    aniChild->SetAttribute( "仅为特效", data->m_bAniOnly );
    aniChild->SetAttribute( "自动播放", data->m_bAutoPlay );
}

void S_UIData::writeTab_XML( MeXmlElement *pXmlUI, S_TabData* data )
{
	MeXmlElement* rootTab = pXmlUI->InsertEndChild("tab");

	writeControlBase_XML( rootTab, (S_BaseData*)data );

	rootTab->SetAttribute( "翻页个数", data->m_nTabCount );
	writeFrame_XML( rootTab, &data->m_frame );
	for( int i=0; i<data->m_nTabCount; ++i )
	{
		MeXmlElement *tabChlid  = rootTab->InsertEndChild("tabChild");

		tabChlid->SetAttribute("value", data->m_szFrameFileName[i] );
		writeButton_XML( tabChlid, &data->m_btnTab[i] );
	}

	
}
void S_UIData::writeListEx_XML( MeXmlElement *pXmlUI, S_ListExData* data )
{
	MeXmlElement* rootListEx = pXmlUI->InsertEndChild("listEx");
	
	writeControlBase_XML( rootListEx, (S_BaseData*)data );
	
	char szRect[56] = {0};
	int a = (data->m_colSelBar>>24) & 0xff;
	int r = (data->m_colSelBar>>16) & 0xff;
	int g = (data->m_colSelBar>>8) & 0xff;
	int b = data->m_colSelBar & 0xff;
	sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
	rootListEx->SetAttribute( "选中颜色", szRect );

	rootListEx->SetAttribute( "Item高度", data->m_nItemHeight );
	rootListEx->SetAttribute( "Item宽度", data->m_nItemWidth );
	rootListEx->SetAttribute( "宽度偏移量", data->m_nOffsetWidth );
	rootListEx->SetAttribute( "高度偏移量", data->m_nOffsetHeight );
	rootListEx->SetAttribute( "item最大数量", data->m_nMaxHeightCount );
	rootListEx->SetAttribute( "icon可以被拖", data->m_bCanbePick );

	writeScrollBar_XML( rootListEx, &data->m_stScrollBar );

	
}
void S_UIData::writeScrollbarEx_XML( MeXmlElement *pXmlUI, S_ScrollBarExData* data )
{
	MeXmlElement *rootScrollbarEx = pXmlUI->InsertEndChild("scrollBarEx");

    writeScrollBar_XML(rootScrollbarEx, data);
	writeControlBase_XML( rootScrollbarEx, (S_BaseData*)data );

}

void S_UIData::writeControlBase_XML(MeXmlElement *pXmlUI, S_BaseData* data)
{
	if( NULL == data )
		return;

	MeXmlElement* baseAttribute = 	pXmlUI->InsertEndChild("baseAttribute");
    baseAttribute->SetAttribute("控件类型", data->m_nType);
    baseAttribute->SetAttribute("对齐模式", data->m_nAlignMode);

	char szRect[56] = {0};
	sprintf( szRect, "%d, %d, %d, %d", data->m_rcRealSize.left, data->m_rcRealSize.top, data->m_rcRealSize.right, data->m_rcRealSize.bottom );
	baseAttribute->SetAttribute( "rect", szRect );
	baseAttribute->SetAttribute( "id", data->m_szID );
	baseAttribute->SetAttribute( "内容", data->m_szCaption );
	baseAttribute->SetAttribute( "Tips", data->m_szTips );
	baseAttribute->SetAttribute( "字体", data->m_szFont );
	baseAttribute->SetAttribute( "字体大小", data->m_nFontSize );
	int a = (data->m_colFont>>24) & 0xff;
	int r = (data->m_colFont>>16) & 0xff;
	int g = (data->m_colFont>>8) & 0xff;
	int b = data->m_colFont & 0xff;
	sprintf( szRect, "%d, %d, %d, %d", a, r,g, b );
	baseAttribute->SetAttribute( "字体颜色", szRect );
    baseAttribute->SetAttribute( "粗体", data->m_isFontBold );

	MeXmlElement *baseAttribute_pic = baseAttribute->InsertEndChild("backpicture");
	baseAttribute_pic->SetAttribute( "资源路径", data->m_stBackPic.m_szPicName );
	sprintf( szRect, "%d, %d, %d, %d", data->m_stBackPic.m_rcFrame.left, data->m_stBackPic.m_rcFrame.top,
		data->m_stBackPic.m_rcFrame.right, data->m_stBackPic.m_rcFrame.bottom );
	baseAttribute_pic->SetAttribute( "背景图外框", szRect );
	sprintf( szRect, "%d, %d, %d, %d", data->m_stBackPic.m_rcClient.left, data->m_stBackPic.m_rcClient.top,
		data->m_stBackPic.m_rcClient.right, data->m_stBackPic.m_rcClient.bottom );
	baseAttribute_pic->SetAttribute( "背景图内框", szRect );

	MeXmlElement *disableAttribute_pic = baseAttribute->InsertEndChild("disablebackpicture");
	disableAttribute_pic->SetAttribute( "资源路径", data->m_stDisablePic.m_szPicName );
	sprintf( szRect, "%d, %d, %d, %d", data->m_stDisablePic.m_rcFrame.left, data->m_stDisablePic.m_rcFrame.top,
		data->m_stDisablePic.m_rcFrame.right, data->m_stDisablePic.m_rcFrame.bottom );
	disableAttribute_pic->SetAttribute( "背景图外框", szRect );
	sprintf( szRect, "%d, %d, %d, %d", data->m_stDisablePic.m_rcClient.left, data->m_stDisablePic.m_rcClient.top,
		data->m_stDisablePic.m_rcClient.right, data->m_stDisablePic.m_rcClient.bottom );
	disableAttribute_pic->SetAttribute( "背景图内框", szRect );

	MeXmlElement* baseAttribute_drawMode = baseAttribute->InsertEndChild("绘制模式");
	for( int i=0; i<S_BaseData::Mode_Max; ++i )
	{
		if( DrawModeNormal == data->m_nDrawMode[i] )
			baseAttribute_drawMode->SetAttribute( szDrawModeName[i], "普通" );
		if( DrawModeTile == data->m_nDrawMode[i] )
			baseAttribute_drawMode->SetAttribute( szDrawModeName[i], "平铺" );
		if( DrawModeStrectch == data->m_nDrawMode[i] )
			baseAttribute_drawMode->SetAttribute( szDrawModeName[i], "拉伸" );
	}

}
//--------
DWORD S_UIData::SaveFile( const char* pszFileName )
{
	//time_t osBinaryTime;  // C run-time time (defined in <time.h>)
	//time( &osBinaryTime );
	//m_stHead.m_dwCreatedDate = (DWORD)osBinaryTime;
	assert( pszFileName );
    //
    DWORD dwVer = 0;
    for( int n=0; n<m_stHead.m_nControlsCount; n++ )
    {
        int nIdLength = strlen(m_pstControlData[n]->m_szID);
        //assert( nIdLength > 0 );
        for( int i=0; i<nIdLength; i++ )
        {
            dwVer += m_pstControlData[n]->m_szID[i];
        }
    }
    dwVer = dwVer*m_stHead.m_nControlsCount + 1;
    m_stHead.m_dwCreatedDate = dwVer;

	SaveFile_XML( pszFileName );

    return 1;


	FILE *fp = fopen( pszFileName, "w+b" );
	if ( fp )
	{
		fwrite( &m_stHead, sizeof(m_stHead), 1, fp );
		for( int n=0; n<m_stHead.m_nControlsCount; n++ )
		{
			switch( m_stHead.m_nControlsType[n] )
			{
			case Type_Button:
				SAVE_CONTROL( S_ButtonData );
				break;
			case Type_CheckBox:
				SAVE_CONTROL( S_CheckBoxData );
				break;
			case Type_Edit:
				SAVE_CONTROL( S_EditData );
				break;
			case Type_Text:
				SAVE_CONTROL( S_TextData );
				break;
			case Type_List:
				SAVE_CONTROL( S_ListData );
				break;
			case Type_ListImg:
				SAVE_CONTROL( S_ListImgData );
				break;
			case Type_ScrollBar:
				SAVE_CONTROL( S_ScrollBarData );
				break;
			case Type_ScrollBarEx:
				SAVE_CONTROL( S_ScrollBarExData );
				break;
			case Type_ComboBox:
				SAVE_CONTROL( S_ComboBoxData );
				break;
			case Type_Picture:
				SAVE_CONTROL( S_PictureData );
				break;
			case Type_Progress:
				SAVE_CONTROL( S_ProgressData );
				break;
			case Type_Tab:
				SAVE_CONTROL( S_TabData );
				break;
			case Type_ListEx:
				SAVE_CONTROL( S_ListExData );
				break;
			default:
				assert(false);
				break;
			}
		}
		fclose(fp);
		return dwVer;
	}
	return 0;
}


