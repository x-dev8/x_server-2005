// CompileDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "BinDataBuilder.h"
#include "compile_dialog.h"
#include "SlkReader.h"
#include "ItemDetailConfig.h"
#include "ItemDetail.h" // �ͻ��˴���������ļ�
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
		else if( strstr( pszString, "�Ҳ���" ) || 
			     strstr( pszString, "δ��д" ) ||
				 strstr( pszString, "���ݴ�" ) ||
				 strstr( pszString, "״̬û��" ) ||
				 strstr( pszString, "����" ) ||
                 strstr( pszString, "����" ) ||
				 strstr( pszString, "ʧ��" ) ||
				 strstr( pszString, "����" ) ||
				 strstr( pszString, "������" ) ||
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
        strContent.Format("���� Item Slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }


    if (!theItemDetailConfig.LoadSlkRand("..\\Data\\Config\\EquipmentRandom.slk"))
    {
        strContent.Format("���� EquipmentRandom.slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkMount("..\\Data\\Config\\Mount.slk"))
    {
        strContent.Format("���� Mount.slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkMonster("..\\Data\\Config\\Monster.slk"))
    {
        strContent.Format("���� Monster.slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkPetMonster("..\\Data\\Config\\Pet.slk"))
    {
        strContent.Format("���� Pet.slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    if (!theItemDetailConfig.LoadSlkCreatureSound("..\\Data\\Config\\CreatureSound.slk"))
    {
        strContent.Format("���� CreatureSound.slk �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    CString strFolderPath = "..\\Data\\Config\\Item" ;

    // �ж�·���Ƿ���� 
    OutputSlkLoadingMessage( "���� Item Ŀ¼ \r\n"  );
    if (!PathIsDirectory(strFolderPath) ) 
    {  CreateDirectory(strFolderPath, NULL ); } 
    OutputSlkLoadingMessage( "����Ŀ¼��� \r\n" );

    OutputSlkLoadingMessage( "�������� Item Config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveItemDetailConfig("..\\Data\\Config\\Item"))
    {
        strContent.Format("���� Item Config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Item Config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "�������� EquipmentRandom.config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveXmlRand("..\\Data\\Config\\EquipmentRandom.config"))
    {
        strContent.Format("���� EquipmentRandom.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� EquipmentRandom.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "�������� Mount.config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveXmlMount("..\\Data\\Config\\Mount.config"))
    {
        strContent.Format("���� Mount.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Mount.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "�������� Monster.config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveXMLMonster("..\\Data\\Config\\Monster.config"))
    {
        strContent.Format("���� Monster.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Monster.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "�������� Pet.config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveXMLPetMonster("..\\Data\\Config\\Pet.config"))
    {
        strContent.Format("���� Pet.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Pet.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "�������� CreatureSound.config �ļ�... \r\n" );
    if (!theItemDetailConfig.SaveXmlCreatureSound("..\\Data\\Config\\CreatureSound.config"))
    {
        strContent.Format("���� CreatureSound.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� CreatureSound.config �ļ���� \r\n" );

    strContent.Format("���ݱ�����ɣ� ���ɳɹ���");
    AfxMessageBox( strContent.GetBuffer() );

    // Data.Config-output
    theItemDetailConfig.ClearItemDetailConfig();

    //��ȡ�������������Ϣ
    if (!theItemDetailConfig.InitItemDetail())
    {
        OutputSlkLoadingMessage("Read %s [Error] ",ITEMDETAILDIRECTORY );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",ITEMDETAILDIRECTORY );
    }

    //���ع�������
    if (!theItemDetailConfig.LoadXmlMonster(MONSTERCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",MONSTERCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MONSTERCONFIG_FILEPATH );
    }

    //���س�������
    if (!theItemDetailConfig.LoadXmlPetMonster(PETCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",PETCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",PETCONFIG_FILEPATH );
    }

    //���ع�������
    if (!theItemDetailConfig.LoadXmlCreatureSound(MONSTERSOUNDCFG_FILEPATH))
    {
        OutputSlkLoadingMessage("Read %s [Error] ",MONSTERSOUNDCFG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MONSTERSOUNDCFG_FILEPATH );
    }

    //������������
    if (!theItemDetailConfig.LoadXmlMount(MOUNTCONFIG_FILEPATH))
    {
        OutputSlkLoadingMessage( "Read %s [Error] ",MOUNTCONFIG_FILEPATH );
        return 0;
    }
    else
    {
        OutputSlkLoadingMessage("Read %s [OK] ",MOUNTCONFIG_FILEPATH );
    }

    //����װ���������
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

    CString strSaveData("�������ļ�������ɣ�");
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


// CCompileDlg ��Ϣ�������

void CCompileDlg::OnBnClickedButtonCompile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	AfxMessageBox("����ɹ�");
}

UINT CompareXml(LPVOID p)
{
    g_bConverting = TRUE;
    g_pfnSlkLoadingCallBack = OutputLoadingMessage;

    theItemDetailConfig.ClearItemDetailConfig();

    CString strContent;
    OutputSlkLoadingMessage( "\t ���ڼ��� Item Config �ļ� ...\r\n" );
    if (!theItemDetailConfig.LoadItemDetailConfig("..\\Data\\Config\\Item"))
    {
        strContent.Format("���� Item Config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t ���ڼ��� EquipmentRandom.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.LoadXmlRand("..\\Data\\Config\\EquipmentRandom.config"))
    {
        strContent.Format("���� EquipmentRandom.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t ���ڼ��� Mount.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.LoadXmlMount("..\\Data\\Config\\Mount.config"))
    {
        strContent.Format("���� Mount.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t ���ڼ��� Monster.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.LoadXmlMonster("..\\Data\\Config\\Monster.config"))
    {
        strContent.Format("���� Monster.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    OutputSlkLoadingMessage( "\t ���ڼ��� CreatureSound.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.LoadXmlCreatureSound("..\\Data\\Config\\CreatureSound.config"))
    {
        strContent.Format("���� CreatureSound.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }

    CString strFolderPath = "..\\Data\\Config\\Compare" ;

    // �ж�·���Ƿ���� 
    if (!PathIsDirectory(strFolderPath) ) 
    {  CreateDirectory(strFolderPath, NULL ); } 

    OutputSlkLoadingMessage( "\t �������� Compare Config �ļ� ...\r\n" );
    if (!theItemDetailConfig.SaveItemDetailConfig("..\\Data\\Config\\Compare"))
    {
        strContent.Format("���ɶԱ� Item Config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Compare Config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "\t �������� Compare EquipmentRandom.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.SaveXmlRand("..\\Data\\Config\\Compare\\EquipmentRandom.config"))
    {
        strContent.Format("���ɶԱ� EquipmentRandom.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Compare EquipmentRandom.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "\t �������� Compare Mount.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.SaveXmlMount("..\\Data\\Config\\Compare\\Mount.config"))
    {
        strContent.Format("���ɶԱ� Mount.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Compare Mount.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "\t �������� Compare Monster.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.SaveXMLMonster("..\\Data\\Config\\Compare\\Monster.config"))
    {
        strContent.Format("���ɶԱ� Monster.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Compare Monster.config �ļ���� \r\n" );

    OutputSlkLoadingMessage( "\t �������� Compare CreatureSound.config �ļ� ...\r\n" );
    if (!theItemDetailConfig.SaveXmlCreatureSound("..\\Data\\Config\\Compare\\CreatureSound.config"))
    {
        strContent.Format("���ɶԱ� CreatureSound.config �ļ�����");
        AfxMessageBox( strContent.GetBuffer() );
        return 0;
    }
    OutputSlkLoadingMessage( "���� Compare CreatureSound.config �ļ���� \r\n" );

    strContent.Format("���ݱ����ļ���ɣ� ���ɶԱ��ļ���");
    AfxMessageBox( strContent.GetBuffer() );

    g_bConverting = FALSE;
    return 0;
}

void CCompileDlg::OnBnClickedButtonBuildObj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//		AfxMessageBox("�ļ�Ϊֻ��,���ܹ���");
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