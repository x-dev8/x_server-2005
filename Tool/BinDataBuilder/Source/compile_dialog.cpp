// CompileDlg.cpp : 实现文件
#include "stdafx.h"
#include "BinDataBuilder.h"
#include "compile_dialog.h"
#include "SlkReader.h"
#include "ItemDetailConfig.h"
#include "ItemDetail.h" // 客户端打包二进制文件
#include "WordParser.h"
#include "ResourcePath.h"
#include "XmlStringLanguage.h"

BOOL g_bConverting = FALSE;
BOOL g_bComplieData = FALSE;
extern CCompileDlg* GetCompileDlg();
extern void (*g_pfnSlkLoadingCallBack)( const char* pszString );


void OutputLoadingMessage( const char* pszString )
{
//	EnterCriticalSection(&cs);
	//strcpy( g_szAppResString, pszString );
	if( strlen( pszString ) > 2 ) 
	{
		if( strnicmp( pszString, "/l", 2 ) == 0 )
		{
			GetCompileDlg()->m_text.SetWindowText( &pszString[2] );
			return;
		}
		else if( strstr( pszString, "找不到" ) || 
			     strstr( pszString, "未填写" ) ||
				 strstr( pszString, "数据错" ) ||
				 strstr( pszString, "状态没有" ) ||
				 strstr( pszString, "出错" ) ||
                 strstr( pszString, "警告" ) ||
				 strstr( pszString, "失败" ) ||
				 strstr( pszString, "错误" ) ||
				 strstr( pszString, "不存在" ) ||
				 strstr( pszString, "error" ) || 
				 strstr( pszString, "Error" ))
		{
			GetCompileDlg()->m_lbError.AddString( pszString );
			return;
		}
		else if( strstr( pszString, "/record" ) )
		{
			WordParser w;
			w.Parse( pszString );
			GetCompileDlg()->m_progress.SetRange( 0, atoi( w.GetWord(1) ) );
			return;
		}
		else if( strstr( pszString, "/process" ) )
		{
			WordParser w;
			w.Parse( pszString );
			GetCompileDlg()->m_progress.SetPos( atoi( w.GetWord(1) ) );
			return;
		}
	}
	GetCompileDlg()->m_lbOutput.AddString( pszString );
	int n = GetCompileDlg()->m_lbOutput.GetCount();
	GetCompileDlg()->m_lbOutput.SetCurSel(n-1);
//	LeaveCriticalSection(&cs);
}
#include "StringLanguageTranslator.h"



//UINT CompileStringSLK()
//{
//	theXmlString.LoadStringFile( ".\\data\\slk\\string.slk" );
//	theXmlString.SaveBinFile( ".\\data\\string.dat" );	
//	return 0;
//}

UINT CompileSlk( LPVOID p )
{
	g_bConverting = TRUE;
	g_pfnSlkLoadingCallBack = OutputLoadingMessage;

    theItemDetailConfig.ClearItemDetailConfig();

	//g_pDlgHRPConvert->m_staticProgress.SetWindowText( s );
	//GetCompileDlg()->m_progress.SetPos(0);
#if (UseStringLanguage==1)
    StringLanguageTranslator::Instance().LoadStringLanguageInfo( STRING_LANGUAGE_FILENAME );
#endif
     CString strContent;

    if (!theItemDetailConfig.LoadSlkItemDetail("..\\Data\\Config"))
    {
        strContent.Format("加载 Item Slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }


    if (!theItemDetailConfig.LoadSlkRand("..\\Data\\Config\\EquipmentRandom.slk"))
    {
        strContent.Format("加载 EquipmentRandom.slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkMount("..\\Data\\Config\\Mount.slk"))
    {
        strContent.Format("加载 Mount.slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkMonster("..\\Data\\Config\\Monster.slk"))
    {
        strContent.Format("加载 Monster.slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkPetMonster("..\\Data\\Config\\Pet.slk"))
    {
        strContent.Format("加载 Pet.slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkCreatureSound("..\\Data\\Config\\CreatureSound.slk"))
    {
        strContent.Format("加载 CreatureSound.slk 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    CString strFolderPath = "..\\Data\\Config\\Item" ;

    // 判断路径是否存在 
    OutputSlkLoadingMessage( "创建 Item 目录 \r\n"  );
    if (!PathIsDirectory(strFolderPath) ) 
    {  CreateDirectory(strFolderPath, NULL ); } 
    OutputSlkLoadingMessage( "创建目录完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 Item Config 文件... \r\n" );
    if (!theItemDetailConfig.SaveItemDetailConfig("..\\Data\\Config\\Item"))
    {
        strContent.Format("生成 Item Config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Item Config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 EquipmentRandom.config 文件... \r\n" );
    if (!theItemDetailConfig.SaveXmlRand("..\\Data\\Config\\EquipmentRandom.config"))
    {
        strContent.Format("生成 EquipmentRandom.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 EquipmentRandom.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 Mount.config 文件... \r\n" );
    if (!theItemDetailConfig.SaveXmlMount("..\\Data\\Config\\Mount.config"))
    {
        strContent.Format("生成 Mount.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Mount.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 Monster.config 文件... \r\n" );
    if (!theItemDetailConfig.SaveXMLMonster("..\\Data\\Config\\Monster.config"))
    {
        strContent.Format("生成 Monster.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Monster.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 Pet.config 文件... \r\n" );
    if (!theItemDetailConfig.SaveXMLPetMonster("..\\Data\\Config\\Pet.config"))
    {
        strContent.Format("生成 Pet.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Pet.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "正在生成 CreatureSound.config 文件... \r\n" );
    if (!theItemDetailConfig.SaveXmlCreatureSound("..\\Data\\Config\\CreatureSound.config"))
    {
        strContent.Format("生成 CreatureSound.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 CreatureSound.config 文件完成 \r\n" );

    strContent.Format("数据编译完成， 生成成功！");
    AfxMessageBox( strContent.GetBuffer() );

    // Data.Config-output
    theItemDetailConfig.ClearItemDetailConfig();

    //读取道具相关配置信息
    if (!theItemDetailConfig.InitItemDetail())
    {
        OutputSlkLoadingMessage("Read %s [Error] ",ITEMDETAILDIRECTORY );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",ITEMDETAILDIRECTORY );
    }

    //加载怪物数据
    if (!theItemDetailConfig.LoadXmlMonster(MONSTERCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",MONSTERCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MONSTERCONFIG_FILEPATH );
    }

    //加载宠物数据
    if (!theItemDetailConfig.LoadXmlPetMonster(PETCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",PETCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",PETCONFIG_FILEPATH );
    }

    //加载怪物声音
    if (!theItemDetailConfig.LoadXmlCreatureSound(MONSTERSOUNDCFG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",MONSTERSOUNDCFG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MONSTERSOUNDCFG_FILEPATH );
    }

    //加载坐骑属性
    if (!theItemDetailConfig.LoadXmlMount(MOUNTCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage( "Read %s [Error] ",MOUNTCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MOUNTCONFIG_FILEPATH );
    }

    //加载装备随机属性
    if (!theItemDetailConfig.LoadXmlRand(EQUIPMENTRANDOM_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",EQUIPMENTRANDOM_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage( "Read %s [OK] ",EQUIPMENTRANDOM_FILEPATH );
    }

    if (!theItemDetailConfig.SaveBinFile(OUTPUT_BINDATAPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",OUTPUT_BINDATAPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage( "Read %s [OK] ",OUTPUT_BINDATAPATH );
    }

    CString strSaveData("二进制文件编译完成！");
    AfxMessageBox( strSaveData.GetBuffer() );

	g_bConverting = FALSE;
	return 0;
}

//UINT BuildObj(LPVOID p)
//{
//	g_pfnSlkLoadingCallBack = OutputLoadingMessage;
//	return 0;
//}

IMPLEMENT_DYNAMIC(CCompileDlg, CDialog)
CCompileDlg::CCompileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompileDlg::IDD, pParent)
{
	//gs_pCompileDlg = this;
}

CCompileDlg::~CCompileDlg()
{
}

void CCompileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_lbOutput);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_STATIC_STATE, m_text);
	DDX_Control(pDX, IDC_LIST_ERROR, m_lbError);
}


BEGIN_MESSAGE_MAP(CCompileDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COMPILE, OnBnClickedButtonCompile)
	ON_BN_CLICKED(IDC_BUTTON_BUILDOBJ, OnBnClickedButtonBuildObj)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClearObj)
	
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCompileDlg 消息处理程序

void CCompileDlg::OnBnClickedButtonCompile()
{
	// TODO: 在此添加控件通知处理程序代码
	if( g_bConverting )
		return;
	m_lbOutput.ResetContent();
	CWinThread* thd = AfxBeginThread(CompileSlk,NULL);
	//HANDLE hThd=thd->m_hThread;
	GetDlgItem( IDC_BUTTON_COMPILE )->EnableWindow( FALSE );
}

void CCompileDlg::OnBnClickedButtonClearObj()
{
	DeleteFile( "Data\\SCENEOBJS\\Build.cache" );
	AfxMessageBox("清理成功");
}

UINT CompareXml(LPVOID p)
{
    g_bConverting = TRUE;
    g_pfnSlkLoadingCallBack = OutputLoadingMessage;

    theItemDetailConfig.ClearItemDetailConfig();

    CString strContent;
    OutputSlkLoadingMessage( "\t 正在加载 Item Config 文件 ...\r\n" );
    if (!theItemDetailConfig.LoadItemDetailConfig("..\\Data\\Config\\Item"))
    {
        strContent.Format("加载 Item Config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t 正在加载 EquipmentRandom.config 文件 ...\r\n" );
    if (!theItemDetailConfig.LoadXmlRand("..\\Data\\Config\\EquipmentRandom.config"))
    {
        strContent.Format("加载 EquipmentRandom.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t 正在加载 Mount.config 文件 ...\r\n" );
    if (!theItemDetailConfig.LoadXmlMount("..\\Data\\Config\\Mount.config"))
    {
        strContent.Format("加载 Mount.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t 正在加载 Monster.config 文件 ...\r\n" );
    if (!theItemDetailConfig.LoadXmlMonster("..\\Data\\Config\\Monster.config"))
    {
        strContent.Format("加载 Monster.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t 正在加载 CreatureSound.config 文件 ...\r\n" );
    if (!theItemDetailConfig.LoadXmlCreatureSound("..\\Data\\Config\\CreatureSound.config"))
    {
        strContent.Format("加载 CreatureSound.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    CString strFolderPath = "..\\Data\\Config\\Compare" ;

    // 判断路径是否存在 
    if (!PathIsDirectory(strFolderPath) ) 
    {  CreateDirectory(strFolderPath, NULL ); } 

    OutputSlkLoadingMessage( "\t 正在生成 Compare Config 文件 ...\r\n" );
    if (!theItemDetailConfig.SaveItemDetailConfig("..\\Data\\Config\\Compare"))
    {
        strContent.Format("生成对比 Item Config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Compare Config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "\t 正在生成 Compare EquipmentRandom.config 文件 ...\r\n" );
    if (!theItemDetailConfig.SaveXmlRand("..\\Data\\Config\\Compare\\EquipmentRandom.config"))
    {
        strContent.Format("生成对比 EquipmentRandom.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Compare EquipmentRandom.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "\t 正在生成 Compare Mount.config 文件 ...\r\n" );
    if (!theItemDetailConfig.SaveXmlMount("..\\Data\\Config\\Compare\\Mount.config"))
    {
        strContent.Format("生成对比 Mount.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Compare Mount.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "\t 正在生成 Compare Monster.config 文件 ...\r\n" );
    if (!theItemDetailConfig.SaveXMLMonster("..\\Data\\Config\\Compare\\Monster.config"))
    {
        strContent.Format("生成对比 Monster.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Compare Monster.config 文件完成 \r\n" );

    OutputSlkLoadingMessage( "\t 正在生成 Compare CreatureSound.config 文件 ...\r\n" );
    if (!theItemDetailConfig.SaveXmlCreatureSound("..\\Data\\Config\\Compare\\CreatureSound.config"))
    {
        strContent.Format("生成对比 CreatureSound.config 文件出错！");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "生成 Compare CreatureSound.config 文件完成 \r\n" );

    strContent.Format("数据编译文件完成， 生成对比文件！");
    AfxMessageBox( strContent.GetBuffer() );

    g_bConverting = FALSE;
    return 0;
}

void CCompileDlg::OnBnClickedButtonBuildObj()
{
	// TODO: 在此添加控件通知处理程序代码
	if( g_bConverting )
		return;
	m_lbOutput.ResetContent();
	
	//BOOL bHas = FALSE;
	//FILE *pf = fopen( "Data\\SCENEOBJS\\Build.cache", "rb" );
	//if( pf )
	//{
	//	bHas = TRUE;
	//	fclose( pf );
	//}
	//if(bHas)
	//{
	//	if( GetFileAttributes( "Data\\SCENEOBJS\\Build.cache" ) & FILE_ATTRIBUTE_READONLY)
	//	{
	//		AfxMessageBox("文件为只读,不能构建");
	//		return;
	//	}
	//}

	//DeleteFile( "Data\\SCENEOBJS\\Build.cache" );


	CWinThread* thd = AfxBeginThread(CompareXml,NULL);
	//HANDLE hThd=thd->m_hThread;
	GetDlgItem( IDC_BUTTON_BUILDOBJ )->EnableWindow( FALSE );;

}

void CCompileDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default

    CDialog::OnClose();
    ::SendMessage( GetParent()->m_hWnd, WM_CLOSE, 0, 0);
}