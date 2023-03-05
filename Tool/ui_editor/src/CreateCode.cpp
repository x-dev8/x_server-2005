#include "StdAfx.h"
#include "createcode.h"
#include <assert.h>

//bool CreateCode2( S_UIData* pData, const char *szFileName, DWORD dwCreatedDate )
//{
//	assert(pData);
//	const int nBufferLength = 1024*100; // 100k
//	char *pBuffer = new char[nBufferLength];
//	char szName[128];
//	char szUIName[128];
//	char szHName[128];
//	char szCppName[128];
//	strcpy( szName, szFileName );
//	for( int n=(int)strlen(szName); n>0; n-- )
//	{
//		if ( szName[n] == '.' )
//		{
//			szName[n] = 0;
//			for ( int m=n-1; m>0; m-- )
//			{
//				if ( szName[m] == '\\' )
//				{
//					sprintf( szUIName, "Data\\\\UI\\\\%s.UI", &szName[m+1] );
//					break;
//				}
//			}
//			break;
//		}
//	}
//
//	sprintf( szHName, "%s.h", szName );
//	sprintf( szCppName, "%s.cpp", szName );
//
//	// Save .h
//	memset( pBuffer, 0, sizeof(char)*nBufferLength );
//	strcat( pBuffer, "/********************************************************************\n" );
//	strcat( pBuffer, "\tCreated by UIEditor.exe\n" );
//	sprintf( pBuffer,"%s\tFileName: %s\n", pBuffer, szHName );
//	strcat( pBuffer, "*********************************************************************/\n" );
//	strcat( pBuffer, "#pragma once\n" );
//	strcat( pBuffer, "#include \"../../HRUI/HR_UI_Include.h\"\n" );
//
//	strcat( pBuffer, "\n" );
//	sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer,
//			pData->m_stHead.m_stFrameData.m_szID, pData->m_stHead.m_stFrameData.m_szID );
//	sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
//		sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer
//			, pData->m_pstControlData[n]->m_szID, pData->m_pstControlData[n]->m_szID );
//		sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
//	}
//
//	strcat( pBuffer, "\n" );
//	sprintf( pBuffer,"%snamespace UI_%s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	strcat( pBuffer, "{\n" );
//
//	strcat( pBuffer, "\t// Member\n" );
//	sprintf( pBuffer, "%s\textern CHR_UI_Frame*\tm_p%s;\n",pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType )
//		{
//		case Type_Button:
//			sprintf( pBuffer, "%s\textern CHR_UI_Button*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_CheckBox:
//			sprintf( pBuffer, "%s\textern CHR_UI_CheckBox*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Edit:
//			sprintf( pBuffer, "%s\textern CHR_UI_Edit*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Text:
//			sprintf( pBuffer, "%s\textern CHR_UI_Text*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_List:
//			sprintf( pBuffer, "%s\textern CHR_UI_List*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListEx:
//			sprintf( pBuffer, "%s\textern CHR_UI_ListEx*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListImg:
//			sprintf( pBuffer, "%s\textern CHR_UI_ListImg*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBar:
//			sprintf( pBuffer, "%s\textern CHR_UI_ScrollBar*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBarEx:
//			sprintf( pBuffer, "%s\textern CHR_UI_ScrollBarEx*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ComboBox:
//			sprintf( pBuffer, "%s\textern CHR_UI_ComboBox*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Picture:
//			sprintf( pBuffer, "%s\textern CHR_UI_Picture*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Progress:
//			sprintf( pBuffer, "%s\textern CHR_UI_Progress*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Tab:
//			sprintf( pBuffer, "%s\textern CHR_UI_Tab*\tm_p%s;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		default:
//			assert( false );
//			break;
//		}
//	}
//	strcat( pBuffer, "\n" );
//
//	strcat( pBuffer, "\t// Frame\n" );
//	sprintf( pBuffer,"%s\tbool OnFrameRun();\n", pBuffer );
//	sprintf( pBuffer,"%s\tbool OnFrameRender();\n", pBuffer );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType ) 
//		{
//		case Type_Button:
//			{
//				strcat( pBuffer, "\t// Button\n" );
//				sprintf( pBuffer,"%s\tbool %sOnButtonClick( CHR_UI_Object* pSender );\n",
//							pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_CheckBox:
//			{
//				strcat( pBuffer, "\t// CheckBox\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnCheckBoxCheck( CHR_UI_Object* pSender, bool* pbChecked );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_Edit:
//			{
//				strcat( pBuffer, "\t// Edit\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnEditEnter( CHR_UI_Object* pSender, const char* szData );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_List:
//			{
//				strcat( pBuffer, "\t// List\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnListSelectChange( CHR_UI_Object* pSender, CHR_UI_List::S_List* pItem );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ListImg:
//		case Type_ListEx:
//			{
//				strcat( pBuffer, "\t// ListImg / ListEx\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconDragOn( CHR_UI_Object* pSender, CHR_UI_Object* pMe,\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItemDrag,\n" );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItemSrc );\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconDragOff( CHR_UI_Object* pSender, CHR_UI_Object* pMe,\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItem );\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconLDBClick( CHR_UI_Object* pSender, CHR_UI_IconDrag::S_ListImg* pItem );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				sprintf( pBuffer,"%s\tbool %sOnIconRButtonUp( CHR_UI_Object* pSender, CHR_UI_IconDrag::S_ListImg* pItem );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ScrollBar:
//			{
//				strcat( pBuffer, "\t// ScrollBar\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnScrollBarUpdatePos( CHR_UI_Object* pSender, int n );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ScrollBarEx:
//			{
//				strcat( pBuffer, "\t// ScrollBarEx\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnScrollBarExUpdatePos( CHR_UI_Object* pSender, int n );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ComboBox:
//			{
//				strcat( pBuffer, "\t// ComboBox\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnComboBoxChange( CHR_UI_Object* pSender, const char* szData );\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		}
//	}
//	// LoadUI() / UnLoadUI();
//	strcat( pBuffer, "\n" );
//	strcat( pBuffer, "\tbool LoadUI();\t\t\t\t// 载入UI\n" );
//	strcat( pBuffer, "\tbool DoControlConnect();\t// 关连控件\n" );
//	strcat( pBuffer, "\tbool UnLoadUI();\t\t\t// 卸载UI\n" );
//	// 是否可见
//	strcat( pBuffer, "\tbool IsVisable();\t\t\t// 是否可见\n" );
//	// SetVisable();
//	strcat( pBuffer, "\tvoid SetVisable( const bool bVisable );\t\t\t// 设置是否可视\n" );
//
//	strcat( pBuffer, "}\n" );
//
//	FILE *fp = fopen( szHName, "w+b" );
//	if ( fp )
//	{
//		fwrite( pBuffer, sizeof(char)*strlen(pBuffer), 1, fp );
//		fclose(fp);
//	}
//	else
//	{
//		assert(false);
//	}
//
//	// Save .cpp
//	for ( int n=(int)strlen(szHName); n>0; n--)
//	{
//		if ( szHName[n] == '\\' )
//		{
//			strcpy( szHName, &szHName[n+1] );
//			break;
//		}
//	}
//	memset( pBuffer, 0, sizeof(char)*nBufferLength );
//	strcat( pBuffer, "/********************************************************************\n" );
//	strcat( pBuffer, "\tCreated by UIEditor.exe\n" );
//	sprintf( pBuffer,"%s\tFileName: %s\n", pBuffer, szCppName );
//	strcat( pBuffer, "*********************************************************************/\n" );
//	strcat( pBuffer, "#include <assert.h>\n" );
//	strcat( pBuffer, "#include \"..\\..\\HRUI\\HR_UI_Mgr.h\"\n" );
//	sprintf( pBuffer, "%s#include \"%s\"\n", pBuffer, szHName );
//	strcat( pBuffer, "\n" );
//
//	sprintf( pBuffer,"%snamespace UI_%s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	strcat( pBuffer, "{\n" );
//
//	strcat( pBuffer, "\t// Member\n" );
//	sprintf( pBuffer, "%s\tCHR_UI_Frame*\tm_p%s = NULL;\n",pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType )
//		{
//		case Type_Button:
//			sprintf( pBuffer, "%s\tCHR_UI_Button*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_CheckBox:
//			sprintf( pBuffer, "%s\tCHR_UI_CheckBox*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Edit:
//			sprintf( pBuffer, "%s\tCHR_UI_Edit*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Text:
//			sprintf( pBuffer, "%s\tCHR_UI_Text*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_List:
//			sprintf( pBuffer, "%s\tCHR_UI_List*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListEx:
//			sprintf( pBuffer, "%s\tCHR_UI_ListEx*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListImg:
//			sprintf( pBuffer, "%s\tCHR_UI_ListImg*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBar:
//			sprintf( pBuffer, "%s\tCHR_UI_ScrollBar*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBarEx:
//			sprintf( pBuffer, "%s\tCHR_UI_ScrollBarEx*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ComboBox:
//			sprintf( pBuffer, "%s\tCHR_UI_ComboBox*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Picture:
//			sprintf( pBuffer, "%s\tCHR_UI_Picture*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Progress:
//			sprintf( pBuffer, "%s\tCHR_UI_Progress*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Tab:
//			sprintf( pBuffer, "%s\tCHR_UI_Tab*\tm_p%s = NULL;\n",pBuffer, pData->m_pstControlData[n]->m_szID );
//			break;
//		default:
//			assert( false );
//			break;
//		}
//	}
//
//	strcat( pBuffer, "\n" );
//
//	strcat( pBuffer, "\t// Frame\n" );
//	sprintf( pBuffer,"%s\tbool OnFrameRun()\n", pBuffer );
//	strcat( pBuffer, "\t{\n" );
//	strcat( pBuffer, "\t\treturn true;\n" );
//	strcat( pBuffer, "\t}\n" );
//	sprintf( pBuffer,"%s\tbool OnFrameRender()\n", pBuffer );
//	strcat( pBuffer, "\t{\n" );
//	strcat( pBuffer, "\t\treturn true;\n" );
//	strcat( pBuffer, "\t}\n" );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType ) 
//		{
//		case Type_Button:
//			{
//				strcat( pBuffer, "\t// Button\n" );
//				sprintf( pBuffer,"%s\tbool %sOnButtonClick( CHR_UI_Object* pSender )\n",
//							pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t\treturn true;\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_CheckBox:
//			{
//				strcat( pBuffer, "\t// CheckBox\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnCheckBoxCheck( CHR_UI_Object* pSender, bool* pbChecked )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_Edit:
//			{
//				strcat( pBuffer, "\t// Edit\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnEditEnter( CHR_UI_Object* pSender, const char* szData )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_List:
//			{
//				strcat( pBuffer, "\t// List\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnListSelectChange( CHR_UI_Object* pSender, CHR_UI_List::S_List* pItem )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_ListImg:
//		case Type_ListEx:
//			{
//				strcat( pBuffer, "\t// ListImg / ListEx\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconDragOn( CHR_UI_Object* pSender, CHR_UI_Object* pMe,\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItemDrag,\n" );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItemSrc )\n" );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t\treturn false;\n" );
//				strcat( pBuffer, "\t}\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconDragOff( CHR_UI_Object* pSender, CHR_UI_Object* pMe,\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItem )\n" );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t\treturn false;\n" );
//				strcat( pBuffer, "\t}\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconLDBClick( CHR_UI_Object* pSender, CHR_UI_IconDrag::S_ListImg* pItem )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t\treturn false;\n" );
//				strcat( pBuffer, "\t}\n" );
//				sprintf( pBuffer,"%s\tbool %sOnIconRButtonUp( CHR_UI_Object* pSender, CHR_UI_IconDrag::S_ListImg* pItem )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t\treturn false;\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_ScrollBar:
//			{
//				strcat( pBuffer, "\t// ScrollBar\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnScrollBarUpdatePos( CHR_UI_Object* pSender, int n )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_ScrollBarEx:
//			{
//				strcat( pBuffer, "\t// ScrollBarEx\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnScrollBarExUpdatePos( CHR_UI_Object* pSender, int n )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		case Type_ComboBox:
//			{
//				strcat( pBuffer, "\t// ComboBox\n" );
//				sprintf( pBuffer,"%s\tvoid %sOnComboBoxChange( CHR_UI_Object* pSender, const char* szData )\n",
//					pBuffer, pData->m_pstControlData[n]->m_szID );
//				strcat( pBuffer, "\t{\n" );
//				strcat( pBuffer, "\t}\n" );
//			}
//			break;
//		}
//	}
//	// LoadUI()
//	strcat( pBuffer, "\n" );
//	strcat( pBuffer, "\t// 装载UI\n" );
//	strcat( pBuffer, "\tbool LoadUI()\n" );
//	strcat( pBuffer, "\t{\n" );
//	char szCreatedDate[32];
//	itoa( dwCreatedDate, szCreatedDate, 10 );
//	sprintf( pBuffer,"%s\t\tDWORD dwResult = theHRUIMgr.AddFrame( \"%s\" );\n",
//		pBuffer, szUIName );
//	strcat( pBuffer,"\t\tif ( dwResult == 0 )\n" );
//	strcat( pBuffer, "\t\t{\n" );
//	sprintf( pBuffer, "%s\t\t\tMESSAGE_BOX(\"读取文件[%s]失败\")\n", pBuffer, szUIName);
//	strcat( pBuffer, "\t\t\treturn false;\n" );
//	strcat( pBuffer, "\t\t}\n" );
//	sprintf( pBuffer,"%s\t\telse if ( dwResult != %s/*文件版本号*/ )\n",
//			pBuffer, szCreatedDate );
//	strcat( pBuffer, "\t\t{\n" );
//	sprintf( pBuffer, "%s\t\t\tMESSAGE_BOX(\"读取文件[%s]与源代码版本不一样\")\n",
//			pBuffer, szUIName);
//	strcat( pBuffer, "\t\t}\n" );
//	strcat( pBuffer, "\t\treturn DoControlConnect();\n" );
//	strcat( pBuffer, "\t}\n" );
//	// DoControlConnect()
//	strcat( pBuffer, "\t// 关连控件\n" );
//	strcat( pBuffer, "\tbool DoControlConnect()\n" );
//	strcat( pBuffer, "\t{\n" );
//	sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnFrameRun( %s, OnFrameRun );\n",
//			pBuffer,
//			pData->m_stHead.m_stFrameData.m_szID );
//	sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnFrameRender( %s, OnFrameRender );\n",
//			pBuffer,
//			pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType ) 
//		{
//		case Type_Button:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnButtonClick( %s, %s, %sOnButtonClick );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_CheckBox:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnCheckBoxCheck( %s, %s, %sOnCheckBoxCheck );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_Edit:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnEditEnter( %s, %s, %sOnEditEnter );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_List:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnListSelectChange( %s, %s, %sOnListSelectChange );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ListImg:
//		case Type_ListEx:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnIconDragOn( %s, %s, %sOnIconDragOn );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnIconDragOff( %s, %s, %sOnIconDragOff );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnIconLDBClick( %s, %s, %sOnIconLDBClick );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnIconRButtonUp( %s, %s, %sOnIconRButtonUp );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ScrollBar:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnScrollBarUpdatePos( %s, %s, %sOnScrollBarUpdatePos );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ScrollBarEx:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnScrollBarExUpdatePos( %s, %s, %sOnScrollBarUpdatePos );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_ComboBox:
//			{
//				sprintf( pBuffer,"%s\t\ttheHRUIMgr.OnComboBoxChange( %s, %s, %sOnComboBoxChange );\n",
//					pBuffer,
//					pData->m_stHead.m_stFrameData.m_szID,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		case Type_Tab:
//			{
//				sprintf( pBuffer,"%s\t\tMESSAGE_BOX(\"请关连[%s]\");\t//TODO: 关连其它框架UI_%s::DoControlConnect();\n",
//					pBuffer,
//					pData->m_pstControlData[n]->m_szID,
//					pData->m_pstControlData[n]->m_szID );
//			}
//			break;
//		}
//	}
//
//	strcat( pBuffer, "\n" );
//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Frame*)theHRUIMgr.FindFrame( %s );\n",
//			pBuffer,
//			pData->m_stHead.m_stFrameData.m_szID,
//			pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		switch( pData->m_pstControlData[n]->m_nType ) 
//		{
//		case Type_Button:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Button*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_CheckBox:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_CheckBox*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Edit:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Edit*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Text:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Text*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_List:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_List*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListEx:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ListEx*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ListImg:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ListImg*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBar:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ScrollBar*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ScrollBarEx:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ScrollBarEx*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_ComboBox:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ComboBox*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Picture:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Picture*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Progress:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Progress*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		case Type_Tab:
//			sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Tab*)theHRUIMgr.FindControl( %s, %s );\n",
//				pBuffer,
//				pData->m_pstControlData[n]->m_szID,
//				pData->m_stHead.m_stFrameData.m_szID,
//				pData->m_pstControlData[n]->m_szID );
//			break;
//		default:
//			assert(false);
//			break;
//		}
//	}
//	// assert
//	sprintf( pBuffer, "%s\t\tassert( m_p%s );\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
//	{
//		sprintf( pBuffer, "%s\t\tassert( m_p%s );\n", pBuffer, pData->m_pstControlData[n]->m_szID );
//	}
//	strcat( pBuffer, "\t\treturn true;\n" );
//	strcat( pBuffer, "\t}\n" );
//	// UnLoadUI();
//	strcat( pBuffer, "\t// 卸载UI\n" );
//	strcat( pBuffer, "\tbool UnLoadUI()\n" );
//	strcat( pBuffer, "\t{\n" );
//	sprintf( pBuffer,"%s\t\treturn theHRUIMgr.RemoveFrame( \"%s\" );\n", pBuffer, szUIName );
//	strcat( pBuffer, "\t}\n" );
//
//	// IsVisable();
//	strcat( pBuffer, "\t// 是否可视\n" );
//	strcat( pBuffer, "\tbool IsVisable()\n" );
//	strcat( pBuffer, "\t{\n" );
//	sprintf( pBuffer,"%s\t\treturn m_p%s->IsVisable();\n",
//		pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	strcat( pBuffer, "\t}\n" );
//	// SetVisable();
//	strcat( pBuffer, "\t// 设置是否可视\n" );
//	strcat( pBuffer, "\tvoid SetVisable( const bool bVisable )\n" );
//	strcat( pBuffer, "\t{\n" );
//	sprintf( pBuffer,"%s\t\tm_p%s->SetVisable( bVisable );\n",
//					pBuffer, pData->m_stHead.m_stFrameData.m_szID );
//	strcat( pBuffer, "\t}\n" );
//
//	strcat( pBuffer, "}\n" );
//
//	fp = fopen( szCppName, "w+b" );
//	if ( fp )
//	{
//		fwrite( pBuffer, sizeof(char)*strlen(pBuffer), 1, fp );
//		fclose(fp);
//	}
//	else
//	{
//		assert(false);
//	}
//	
//	delete[] pBuffer;
//	return true;
//}

enum
{
	OP_NORMAL,
	OP_ICONDRAGON,
	OP_ICONDRAGOFF,
	OP_ICONLDBCLICK,
	OP_ICONRDBCLICK,
	OP_ICONBCLICK,
};
const char* GetControlEvent( int nType, int nOp = OP_NORMAL )
{
	switch( nType )
	{
	case Type_Button:
		return "OnButtonClick";
		break;
	case Type_CheckBox:
		return "OnCheckBoxCheck";
		break;
	case Type_Edit:
		return "OnEditEnter";
		break;
	case Type_Text:
		return "";
		break;
	case Type_List:
		return "OnListSelectChange";
		break;
	case Type_ListImg:
	case Type_ListEx:
		switch( nOp )
		{
		case OP_ICONDRAGON:
			return "OnIconDragOn";
			break;
		case OP_ICONDRAGOFF:
			return "OnIconDragOff";
			break;
		case OP_ICONLDBCLICK:
			return "OnIconLDBClick";
			break;
		case OP_ICONRDBCLICK:
			return "OnIconRButtonUp";
		case OP_ICONBCLICK:
			return "OnIconButtonClick";
			break;
		}
		break;
	case Type_ScrollBar:
		return "OnScrollBarUpdatePos";
		break;
	case Type_ScrollBarEx:
		return "OnScrollBarExUpdatePos";
		break;
	case Type_ComboBox:
		return "OnComboBoxChange";
		break;
	case Type_Picture:
		return "";
		break;
	case Type_Progress:
		return "";
		break;
	case Type_Tab:
		return "";
		break;
	//case Type_Tree:
	//	return "OnTreeSelectChange";
	//	break;
	}
	assert( false );
	return "";
}
const char* GetCallbackFunName( int nType, int nOp = OP_NORMAL )
{
	switch( nType )
	{
	case Type_Button:
		return "MAP_BUTTON_CLICK_CALLBACK";
		break;
	case Type_CheckBox:
		return "MAP_CHECK_BOX_CHECK_CALLBACK";
		break;
	case Type_Edit:
		return "MAP_EDIT_ENTER_CALLBACK";
		break;
	case Type_Text:
		return "";
		break;
	case Type_List:
		return "MAP_LIST_SELECT_CHANGE_CALLBACK";
		break;
	case Type_ListImg:
	case Type_ListEx:
		switch( nOp )
		{
		case OP_ICONDRAGON:
			return "MAP_ICON_DRAG_ON_CALLBACK";
			break;
		case OP_ICONDRAGOFF:
			return "MAP_ICON_DRAG_OFF_CALLBACK";
			break;
		case OP_ICONLDBCLICK:
			return "MAP_ICON_LDB_CLICK_CALLBACK";
			break;
		case OP_ICONRDBCLICK:
			return "MAP_ICON_RBUTTON_UP_CALLBACK";
		case OP_ICONBCLICK:
			return "MAP_ICON_BUTTON_CLICK_CALLBACK";
			break;
		}
		break;
	case Type_ScrollBar:
		return "MAP_SCROLL_BAR_UPDATE_POS_CALLBACK";
		break;
	case Type_ScrollBarEx:
		return "MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK";
		break;
	case Type_ComboBox:
		return "MAP_COMBO_BOX_CHANGE_CALLBACK";
		break;
	case Type_Picture:
		return "";
		break;
	case Type_Progress:
		return "";
		break;
	case Type_Tab:
		return "";
		break;
	//case Type_Tree:
	//	return "MAP_TREE_SELECT_CHANGE_CALLBACK";
	//	break;
	}
	assert( false );
	return "";
}
const char* GetControlName( int nType )
{
	switch( nType )
	{
	case Type_Button:
		return "ControlButton";
		break;
	case Type_CheckBox:
		return "ControlCheckBox";
		break;
	case Type_Edit:
		return "ControlEdit";
		break;
	case Type_Text:
		return "ControlText";
		break;
	case Type_List:
		return "ControlList";
		break;
	case Type_ListImg:
		return "ControlListImage";
		break;
	case Type_ScrollBar:
		return "ControlScrollBar";
		break;
	case Type_ScrollBarEx:
		return "ControlScrollBarEx";
		break;
	case Type_ComboBox:
		return "ControlComboBox";
		break;
	case Type_Picture:
		return "ControlPicture";
		break;
	case Type_Progress:
		return "ControlProgress";
		break;
	case Type_Tab:
		return "ControlTab";
		break;
	case Type_ListEx:
		return "ControlListEx";
		break;
	//case Type_Tree:
	//	return "CHR_UI_Tree";
	//	break;
	}
	assert( false );
	return "";
}

const char* GetControlFunctionName( int nType, const char* pszId, int nOp = OP_NORMAL )
{
	static char szBuf[1024];
	switch( nType )
	{
	case Type_Button:
		sprintf( szBuf,"bool %sOnButtonClick( ControlObject* pSender )",
			pszId );
		break;
	case Type_CheckBox:
		sprintf( szBuf,"void %sOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )",
			pszId );
		break;
	case Type_Edit:
		sprintf( szBuf ,"void %sOnEditEnter( ControlObject* pSender, const char* szData )",
			pszId );
		break;
	case Type_List:
		sprintf( szBuf,"void %sOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )",
			pszId );
		break;
	case Type_ListImg:
	case Type_ListEx:
		switch( nOp )
		{
		case OP_ICONDRAGON:
			sprintf( szBuf,"bool %sOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )",
				pszId );
			break;
		case OP_ICONDRAGOFF:
			sprintf( szBuf,"bool %sOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem )",
				pszId );
			break;
		case OP_ICONLDBCLICK:
			sprintf( szBuf ,"bool %sOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )",
				pszId );
			break;
		case OP_ICONRDBCLICK:
			sprintf( szBuf ,"bool %sOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )",
				pszId );
			break;
		case OP_ICONBCLICK:
			sprintf( szBuf, "bool %sOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )",
				pszId );
			break;
		}
		break;
	case Type_ScrollBar:
		sprintf( szBuf, "void %sOnScrollBarUpdatePos( ControlObject* pSender, int n )",
			pszId );
		break;
	case Type_ScrollBarEx:
		sprintf( szBuf, "void %sOnScrollBarExUpdatePos( ControlObject* pSender, int n )",
			pszId );
		break;
	case Type_ComboBox:
		sprintf( szBuf, "void %sOnComboBoxChange( ControlObject* pSender, const char* szData )",
			pszId );
		break;
	//case Type_Tree:
	//	sprintf( szBuf,"void %sOnTreeSelectChange( CHR_UI_Object* pSender, CHR_UI_Tree::S_List* pItem )",
	//		pszId );
	//	break;
	default:
		return "";
	}
	return szBuf;
}

bool CreateCode( S_UIData* pData, const char *szFileName, DWORD dwCreatedDate )
{
	assert(pData);
	const int nBufferLength = 1024*100; // 100k
	char *pBuffer = new char[nBufferLength];
	char szName[128];
	char szUIName[128];
	char szHName[128];
	char szCppName[128];
	strcpy( szName, szFileName );
	for( int n=(int)strlen(szName); n>0; n-- )
	{
		if ( szName[n] == '.' )
		{
			szName[n] = 0;
			for ( int m=n-1; m>0; m-- )
			{
				if ( szName[m] == '\\' )
				{
					sprintf( szUIName, "Data\\\\UI\\\\%s.meui", &szName[m+1] );
					break;
				}
			}
			break;
		}
	}

	sprintf( szHName, "%s.h", szName );
	sprintf( szCppName, "%s.cpp", szName );
	char szClassName[1024];
	sprintf( szClassName,"CUI_%s", pData->m_stHead.m_stFrameData.m_szID );

	// Save .h
	memset( pBuffer, 0, sizeof(char)*nBufferLength );
	strcat( pBuffer, "/********************************************************************\n" );
	strcat( pBuffer, "\tCreated by UIEditor.exe\n" );
	sprintf( pBuffer,"%s\tFileName: %s\n", pBuffer, szHName );
	strcat( pBuffer, "*********************************************************************/\n" );
	strcat( pBuffer, "#pragma once\n" );
	strcat( pBuffer, "#include \"MeUi/MeUi.h\"" );

	strcat( pBuffer, "\n" );
	strcat(pBuffer,"\n");
	/*
	sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer,
		pData->m_stHead.m_stFrameData.m_szID, pData->m_stHead.m_stFrameData.m_szID );
	sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
		sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer
			, pData->m_pstControlData[n]->m_szID, pData->m_pstControlData[n]->m_szID );
		sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	}
	*/
	//宏定义
	sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer,
		pData->m_stHead.m_stFrameData.m_szID, pData->m_stHead.m_stFrameData.m_szID );
	sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
		sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer
			, pData->m_pstControlData[n]->m_szID, pData->m_pstControlData[n]->m_szID );
		sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	}

	strcat( pBuffer, "\n" );
	sprintf( pBuffer,"%sclass CUI_%s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	strcat( pBuffer, "{\n" );

	strcat( pBuffer, "\t// Member\n" );
	sprintf( pBuffer, "%spublic:\t\n",pBuffer );
	
	sprintf( pBuffer,"%s\t%s();\n",pBuffer,szClassName);
	sprintf( pBuffer,"%s\tvirtual ~%s();\n",pBuffer,szClassName);

	strcat( pBuffer, "\t// Frame\n" );
	sprintf( pBuffer,"%s\tbool OnFrameRun();\n", pBuffer );
	sprintf( pBuffer,"%s\tbool OnFrameRender();\n", pBuffer );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		int nType = pData->m_pstControlData[n]->m_nType;
		const char* pszId = pData->m_pstControlData[n]->m_szID;
		switch( nType )
		{
		case Type_ListImg:
		case Type_ListEx:
			sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId, OP_ICONDRAGON ) );
			//sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId, OP_ICONDRAGOFF ) );
			sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId, OP_ICONLDBCLICK ) );
			sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId, OP_ICONRDBCLICK ) );
			sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId, OP_ICONBCLICK ));
			break;
		default:
			if ( strlen( GetControlFunctionName( nType, pszId ) ) > 0 )
				sprintf( pBuffer, "%s\t%s;\n", pBuffer, GetControlFunctionName( nType, pszId ) );
		}
	}
	// LoadUI() / UnLoadUI();
	strcat( pBuffer, "\n" );
	strcat( pBuffer, "\tbool LoadUI();\t\t\t\t// 载入UI\n" );
	strcat( pBuffer, "\tbool DoControlConnect();\t// 关连控件\n" );
	strcat( pBuffer, "\tbool UnLoadUI();\t\t\t// 卸载UI\n" );
	// 是否可见
	strcat( pBuffer, "\tbool IsVisable();\t\t\t// 是否可见\n" );
	// SetVisable();
	strcat( pBuffer, "\tvoid SetVisable( const bool bVisable );\t\t\t// 设置是否可视\n" );

	strcat( pBuffer, "\n" );
	sprintf( pBuffer, "%sprivate:\t\n",pBuffer );
	sprintf( pBuffer, "%s\t ControlFrame*\tm_p%s;\n",pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		const char* pName = GetControlName( pData->m_pstControlData[n]->m_nType );
		if( !pName )
			continue;
		sprintf( pBuffer, "%s\t %s*\tm_p%s;\n",
			pBuffer, 
			pName,
			pData->m_pstControlData[n]->m_szID );
	}

	strcat( pBuffer, "};\n" );

	sprintf(pBuffer,"%sextern %s s_%s",pBuffer,szClassName,szClassName);
	strcat(pBuffer,";\n");
	FILE *fp = fopen( szHName, "w+b" );
	if ( fp )
	{
		fwrite( pBuffer, sizeof(char)*strlen(pBuffer), 1, fp );
		fclose(fp);
	}
	else
	{
		assert(false);
	}

	// Save .cpp
	for ( int n=(int)strlen(szHName); n>0; n--)
	{
		if ( szHName[n] == '\\' )
		{
			strcpy( szHName, &szHName[n+1] );
			break;
		}
	}
	memset( pBuffer, 0, sizeof(char)*nBufferLength );
	strcat( pBuffer, "/********************************************************************\n" );
	strcat( pBuffer, "\tCreated by UIEditor.exe\n" );
	sprintf( pBuffer,"%s\tFileName: %s\n", pBuffer, szCppName );
	strcat( pBuffer, "*********************************************************************/\n" );
	strcat( pBuffer, "#include <assert.h>\n" );
	strcat( pBuffer, "#include \"MeUi/UiManager.h\"\n" );
	sprintf( pBuffer, "%s#include \"%s\"\n", pBuffer, szHName );
	strcat( pBuffer, "\n" );

	////宏定义
	//sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	//sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer,
	//	pData->m_stHead.m_stFrameData.m_szID, pData->m_stHead.m_stFrameData.m_szID );
	//sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	//for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	//{
	//	sprintf( pBuffer, "%s#ifndef %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	//	sprintf( pBuffer,"%s#define %s\t\t\"%s\"\n", pBuffer
	//		, pData->m_pstControlData[n]->m_szID, pData->m_pstControlData[n]->m_szID );
	//	sprintf( pBuffer, "%s#endif  %s\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	//}
	//strcat(pBuffer,"\n");
	////////////
	
	// 这里定义一个全局变量
	char szUIGlobalVarName[256];
	sprintf( szUIGlobalVarName, "s_%s", szClassName );
	sprintf( pBuffer, "%s%s %s;\n", pBuffer, szClassName, szUIGlobalVarName );
	strcat(pBuffer,"\n");
	//////////////////////////////////////////////////////////////////////////
	sprintf( pBuffer, "%sMAP_FRAME_RUN( %s, OnFrameRun )\n", pBuffer, szUIGlobalVarName );
	sprintf( pBuffer, "%sMAP_FRAME_RENDER( %s, OnFrameRender )\n", pBuffer, szUIGlobalVarName );
	strcat(pBuffer,"\n");
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		int nType = pData->m_pstControlData[n]->m_nType;
		switch( nType )
		{
		case Type_ListImg:
		case Type_ListEx:
			sprintf( pBuffer, "%s%s( %s, %s%s )\n", 
				pBuffer,
				GetCallbackFunName( nType, OP_ICONDRAGON ),
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONDRAGON ) );
			//sprintf( pBuffer, "%s%s( %s, %s%s )\n", 
			//	pBuffer, 
			//	GetCallbackFunName( nType, OP_ICONDRAGOFF ),
			//	szUIGlobalVarName,
			//	pData->m_pstControlData[n]->m_szID,
			//	GetControlEvent( nType, OP_ICONDRAGOFF  ) );
			sprintf( pBuffer, "%s%s( %s, %s%s )\n", 
				pBuffer, 
				GetCallbackFunName( nType, OP_ICONLDBCLICK ),
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONLDBCLICK  ) );
			sprintf( pBuffer, "%s%s( %s, %s%s )\n", 
				pBuffer, 
				GetCallbackFunName( nType, OP_ICONRDBCLICK ),
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONRDBCLICK  ) );
			sprintf( pBuffer, "%s%s( %s, %s%s )\n",
				pBuffer,
				GetCallbackFunName( nType, OP_ICONBCLICK ),
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONBCLICK ) );
			break;
		default:
			if( strlen( GetControlEvent( nType ) ) > 0 )
			sprintf( pBuffer, "%s%s( %s, %s%s )\n", 
				pBuffer, 
				GetCallbackFunName( nType ),
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType ) );
		}

	}

	//////////////////////////////////////////////////////////////////////////

	sprintf( pBuffer, "%s%s::%s()\n{\n", pBuffer, szClassName, szClassName );

	strcat( pBuffer, "\t// Member\n" ); 
	sprintf( pBuffer, "%s\tm_p%s = NULL;\n",pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		//char* pszName = GetControlName( pData->m_pstControlData[n]->m_nType );
		sprintf( pBuffer, "%s\tm_p%s = NULL;\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	}

	strcat( pBuffer, "\n}\n" );
	sprintf(pBuffer,"%s%s::~%s()\n{\n}\n",pBuffer,szClassName,szClassName);

	strcat( pBuffer, "// Frame\n" );
	sprintf( pBuffer,"%sbool %s::OnFrameRun()\n", 
		pBuffer, 
		szClassName );
	strcat( pBuffer, "{\n" );
	strcat( pBuffer, "\treturn true;\n" );
	strcat( pBuffer, "}\n" );
	sprintf( pBuffer,"%sbool %s::OnFrameRender()\n", 
		pBuffer, 
		szClassName );
	strcat( pBuffer, "{\n" );
	strcat( pBuffer, "\treturn true;\n" );
	strcat( pBuffer, "}\n" );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		switch( pData->m_pstControlData[n]->m_nType ) 
		{
		case Type_Button:
			{
				strcat( pBuffer, "// Button\n" );
				sprintf( pBuffer,"%sbool %s::%sOnButtonClick( ControlObject* pSender )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "\treturn true;\n" );
				strcat( pBuffer, "}\n" );

			}
			break;
		case Type_CheckBox:
			{
				strcat( pBuffer, "// CheckBox\n" );
				sprintf( pBuffer,"%svoid %s::%sOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_Edit:
			{
				strcat( pBuffer, "// Edit\n" );
				sprintf( pBuffer,"%svoid %s::%sOnEditEnter( ControlObject* pSender, const char* szData )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_List:
			{
				strcat( pBuffer, "// List\n" );
				sprintf( pBuffer,"%svoid %s::%sOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_ListImg:
		case Type_ListEx:
			{
				strcat( pBuffer, "// ListImg / ListEx\n" );
				sprintf( pBuffer,"%sbool %s::%sOnIconDragOn( ControlObject* pSender, ControlObject* pMe,\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\tControlIconDrag::S_ListImg* pItemDrag,\n" );
				strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\tControlIconDrag::S_ListImg* pItemSrc )\n" );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "\treturn false;\n" );
				strcat( pBuffer, "}\n" );
				//sprintf( pBuffer,"%s\tbool %s::%sOnIconDragOff( CHR_UI_Object* pSender, CHR_UI_Object* pMe,\n",
				//	pBuffer, 
				//	szClassName,
				//	pData->m_pstControlData[n]->m_szID );
				//strcat( pBuffer, "\t\t\t\t\t\t\t\t\t\t\tCHR_UI_IconDrag::S_ListImg* pItem )\n" );
				//strcat( pBuffer, "\t{\n" );
				//strcat( pBuffer, "\t\treturn false;\n" );
				//strcat( pBuffer, "\t}\n" );
				sprintf( pBuffer,"%sbool %s::%sOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "\treturn false;\n" );
				strcat( pBuffer, "}\n" );
				sprintf( pBuffer,"%sbool %s::%sOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "\treturn false;\n" );
				strcat( pBuffer, "}\n" );
				sprintf( pBuffer,"%sbool %s::%sOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "\treturn false;\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_ScrollBar:
			{
				strcat( pBuffer, "// ScrollBar\n" );
				sprintf( pBuffer,"%svoid %s::%sOnScrollBarUpdatePos( ControlObject* pSender, int n )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_ScrollBarEx:
			{
				strcat( pBuffer, "// ScrollBarEx\n" );
				sprintf( pBuffer,"%svoid %s::%sOnScrollBarExUpdatePos( ControlObject* pSender, int n )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		case Type_ComboBox:
			{
				strcat( pBuffer, "// ComboBox\n" );
				sprintf( pBuffer,"%svoid %s::%sOnComboBoxChange( ControlObject* pSender, const char* szData )\n",
					pBuffer, 
					szClassName,
					pData->m_pstControlData[n]->m_szID );
				strcat( pBuffer, "{\n" );
				strcat( pBuffer, "}\n" );
			}
			break;
		//case Type_Tree:
		//	{
		//		strcat( pBuffer, "\t// Tree\n" );
		//		sprintf( pBuffer,"%s\tvoid %s::%sOnListSelectChange( CHR_UI_Object* pSender, CHR_UI_Tree::S_List* pItem )\n",
		//			pBuffer, 
		//			szClassName,
		//			pData->m_pstControlData[n]->m_szID );
		//		strcat( pBuffer, "\t{\n" );
		//		strcat( pBuffer, "\t}\n" );
		//	}
		//	break;
		}
	}
	// LoadUI()
	strcat( pBuffer, "\n" );
	strcat( pBuffer, "// 装载UI\n" );
	char szBuf[1024];
	sprintf( szBuf, "bool %s::LoadUI()\n", szClassName );
	strcat( pBuffer, szBuf );
	strcat( pBuffer, "{\n" );
	char szCreatedDate[32];
	itoa( dwCreatedDate, szCreatedDate, 10 );
	sprintf( pBuffer,"%s\tDWORD dwResult = theUiManager.AddFrame( \"%s\" );\n",
		pBuffer, szUIName );
	strcat( pBuffer,"\tif ( dwResult == 0 )\n" );
	strcat( pBuffer, "\t{\n" );
	sprintf( pBuffer, "%s\t\tMESSAGE_BOX(\"读取文件[%s]失败\")\n", pBuffer, szUIName);
	strcat( pBuffer, "\t\treturn false;\n" );
	strcat( pBuffer, "\t}\n" );
	//sprintf( pBuffer,"%s\t\telse if ( dwResult != %s/*文件版本号*/ )\n",
		//pBuffer, szCreatedDate );
	//strcat( pBuffer, "\t\t{\n" );
	//sprintf( pBuffer, "%s\t\t\tMESSAGE_BOX(\"读取文件[%s]与源代码版本不一样\")\n",
		//pBuffer, szUIName);
	//strcat( pBuffer, "\t\t}\n" );
	strcat( pBuffer, "\treturn DoControlConnect();\n" );
	strcat( pBuffer, "}\n" );
	// DoControlConnect()
	strcat( pBuffer, "// 关连控件\n" );
	sprintf( szBuf, "bool %s::DoControlConnect()\n", szClassName );
	strcat( pBuffer, szBuf );
	strcat( pBuffer, "{\n" );
	sprintf( pBuffer,"%s\ttheUiManager.OnFrameRun( %s, %sOnFrameRun );\n",
		pBuffer,
		pData->m_stHead.m_stFrameData.m_szID,
		szUIGlobalVarName );
	sprintf( pBuffer,"%s\ttheUiManager.OnFrameRender( %s, %sOnFrameRender );\n",
		pBuffer,
		pData->m_stHead.m_stFrameData.m_szID,
		szUIGlobalVarName );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		int nType = pData->m_pstControlData[n]->m_nType;
		switch( nType )
		{
		case Type_ListImg:
		case Type_ListEx:
			sprintf( pBuffer, "%s\ttheUiManager.%s( %s, %s, %s%s%s );\n", 
				pBuffer,
				GetControlEvent( nType, OP_ICONDRAGON ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONDRAGON ) );
		/*	sprintf( pBuffer, "%stheHRUIMgr.%s( %s, %s, %s%s%s );\n", 
				pBuffer, 
				GetControlEvent( nType, OP_ICONDRAGOFF  ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONDRAGOFF  ) );*/
			sprintf( pBuffer, "%s\ttheUiManager.%s( %s, %s, %s%s%s );\n", 
				pBuffer, 
				GetControlEvent( nType, OP_ICONLDBCLICK  ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONLDBCLICK  ) );
			sprintf( pBuffer, "%s\ttheUiManager.%s( %s, %s, %s%s%s );\n", 
				pBuffer, 
				GetControlEvent( nType, OP_ICONRDBCLICK  ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONRDBCLICK  ) );
			sprintf( pBuffer, "%s\ttheUiManager.%s( %s, %s, %s%s%s );\n", 
				pBuffer, 
				GetControlEvent( nType, OP_ICONBCLICK  ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType, OP_ICONBCLICK  ) );
			break;
		default:
			if( strlen( GetControlEvent( nType ) ) > 0 )
				sprintf( pBuffer, "%s\ttheUiManager.%s( %s, %s, %s%s%s );\n", 
				pBuffer, 
				GetControlEvent( nType ),
				pData->m_stHead.m_stFrameData.m_szID,
				pData->m_pstControlData[n]->m_szID,
				szUIGlobalVarName,
				pData->m_pstControlData[n]->m_szID,
				GetControlEvent( nType ) );
		}
	}

	strcat( pBuffer, "\n" );
	sprintf( pBuffer, "%s\tm_p%s = (ControlFrame*)theUiManager.FindFrame( %s );\n",
		pBuffer,
		pData->m_stHead.m_stFrameData.m_szID,
		pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		const char* pszClassName = GetControlName( pData->m_pstControlData[n]->m_nType );
		//sprintf( pBuffer, "%s\t\tm_p%s = (%s*)
		sprintf( pBuffer, "%s\tm_p%s = (%s*)theUiManager.FindControl( %s, %s );\n",
			pBuffer,
			pData->m_pstControlData[n]->m_szID,
			pszClassName,
			pData->m_stHead.m_stFrameData.m_szID,
			pData->m_pstControlData[n]->m_szID );

		//switch( pData->m_pstControlData[n]->m_nType ) 
		//{
		//case Type_Button:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Button*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_CheckBox:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_CheckBox*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_Edit:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Edit*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_Text:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Text*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_List:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_List*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_ListEx:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ListEx*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_ListImg:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ListImg*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_ScrollBar:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ScrollBar*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_ComboBox:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_ComboBox*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_Picture:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Picture*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_Progress:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Progress*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//case Type_Tab:
		//	sprintf( pBuffer, "%s\t\tm_p%s = (CHR_UI_Tab*)theHRUIMgr.FindControl( %s, %s );\n",
		//		pBuffer,
		//		pData->m_pstControlData[n]->m_szID,
		//		pData->m_stHead.m_stFrameData.m_szID,
		//		pData->m_pstControlData[n]->m_szID );
		//	break;
		//default:
		//	assert(false);
		//	break;
		//}
	}
	// assert
	sprintf( pBuffer, "%s\tassert( m_p%s );\n", pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	for ( int n=0; n< pData->m_stHead.m_nControlsCount; n++ )
	{
		sprintf( pBuffer, "%s\tassert( m_p%s );\n", pBuffer, pData->m_pstControlData[n]->m_szID );
	}
	strcat( pBuffer, "\treturn true;\n" );
	strcat( pBuffer, "}\n" );
	// UnLoadUI();
	sprintf( szBuf, "bool %s::UnLoadUI()\n", szClassName );
	strcat( pBuffer, "// 卸载UI\n" );
	strcat( pBuffer, szBuf );
	strcat( pBuffer, "{\n" );
	sprintf( pBuffer,"%s\treturn theUiManager.RemoveFrame( \"%s\" );\n", pBuffer, szUIName );
	strcat( pBuffer, "}\n" );

	// IsVisable();
	strcat( pBuffer, "// 是否可视\n" );
	sprintf( szBuf, "bool %s::IsVisable()\n", szClassName );
	strcat( pBuffer, szBuf );
	strcat( pBuffer, "{\n" );
	sprintf( pBuffer,"%s\treturn m_p%s->IsVisable();\n",
		pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	strcat( pBuffer, "}\n" );
	// SetVisable();
	strcat( pBuffer, "// 设置是否可视\n" );
	sprintf( szBuf, "void %s::SetVisable( const bool bVisable )\n", szClassName );
	strcat( pBuffer, szBuf );
	strcat( pBuffer, "{\n" );
	sprintf( pBuffer,"%s\tm_p%s->SetVisable( bVisable );\n",
		pBuffer, pData->m_stHead.m_stFrameData.m_szID );
	strcat( pBuffer, "}\n" );

	//strcat( pBuffer, "}\n" );

	fp = fopen( szCppName, "w+b" );
	if ( fp )
	{
		fwrite( pBuffer, sizeof(char)*strlen(pBuffer), 1, fp );
		fclose(fp);
	}
	else
	{
		assert(false);
	}

	delete[] pBuffer;
	return true;
}

