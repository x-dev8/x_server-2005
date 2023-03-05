#include "MeTerrain/stdafx.h"
#include "UserData.h"
#include "XmlStringLanguage.h"
#include "tstring.h"
#include "PlayerRole.h"
#include "Common.h"
#include "RapidXml/MeRapidXml.h"
#include "packet_interface.h"
#include "ui/Select.h"

#ifdef NPGUARD
//LYH NP
#include <NP/NPGameLib.h>
extern CNPGameLib *npgl;
#endif

CUserData* CUserData::ms_pThis = 0;

CUserData* CUserData::Instance()
{
    if( !ms_pThis )
        ms_pThis = MeNew CUserData;

    return ms_pThis;
}

bool CUserData::Destroy()
{
    SAFE_DELETE( ms_pThis );

    return true;
}

CUserData::CUserData( void )
{
    m_strAccount[0] = 0;
    m_strArea[0] = 0;
    m_strServer[0] = 0;
    m_strRole[0] = 0;
    m_strUserDataPath[0] = 0;
	m_nViewSet = 0;
    m_bSoftKeyboard = false;
}

BOOL CUserData::CreateUserData()
{
	char strFolder[MAX_PATH] = {0};
    CreateDirectory("UserData",NULL);
    MeSprintf_s(strFolder,sizeof(strFolder)/sizeof(char) - 1, "UserData/%s", m_strAccount);
    CreateDirectory(strFolder,NULL);
	char strFolder1[MAX_PATH] = {0};
    MeSprintf_s(strFolder1, sizeof(strFolder1)/sizeof(char) - 1,"%s/%s", strFolder, m_strArea);
    CreateDirectory(strFolder1,NULL);
	char strFolder2[MAX_PATH] = {0};
    MeSprintf_s(strFolder2,sizeof(strFolder2)/sizeof(char) - 1, "%s/%s", strFolder1, m_strServer);
    CreateDirectory(strFolder2,NULL);
	char strFolder3[MAX_PATH] = {0};
    MeSprintf_s(strFolder3,sizeof(strFolder3)/sizeof(char) - 1, "%s/%s", strFolder2, m_strRole);
    CreateDirectory(strFolder3,NULL);

    // 保存最后一次登录数据
    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/%s/Role.config", GetRootPath(), m_strAccount);

    SetFileAttributes( szPath, FILE_ATTRIBUTE_NORMAL );
    MeXmlDocument doc;
    MeXmlDeclaration decl("1.0", "UTF-8", "yes");
    doc.InsertEndChild(decl);

    MeXmlElement* pProject = doc.InsertEndChild("Project");
    pProject->SetAttribute("Name", "HeroOnline");
    pProject->SetAttribute("Version", "");

	MeXmlElement *pServer = pProject->InsertEndChild("LastLogin");
    std::wstring str = Common::_tstring::toWideString(m_strRole);
    pServer->SetAttribute("RoleName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
//     pProjectNode->InsertEndChild(pServer);

    doc.SaveFile(szPath);

	// 删除旧文件格式Role.xml
	MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "./UserData/%s/Role.xml", m_strAccount);
	::DeleteFile(szPath);

    return TRUE;
}

const char* CUserData::GetAccountDataPath()
{
	MeSprintf_s(m_strAccountDataPath,sizeof(m_strAccountDataPath)/sizeof(char) - 1, "./UserData/%s/", m_strAccount );
	return m_strAccountDataPath;
}

const char* CUserData::GetUserDataPath()
{
    MeSprintf_s(m_strUserDataPath,sizeof(m_strUserDataPath)/sizeof(char) - 1, "./UserData/%s/%s/%s/%s/", m_strAccount, m_strArea, m_strServer, m_strRole);
    return m_strUserDataPath;
}

BOOL CUserData::ReadUserData()
{
   /* char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/Role.config", GetRootPath(), m_strAccount);

    MeXmlDocument doc;
    if( !doc.LoadFile(szPath) )
    {
		MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/%s/Role.xml", GetRootPath(), m_strAccount);
		if( !doc.LoadFile(szPath) )
			return FALSE;
    }

    char* szValue = NULL;
    MeXmlElement* lpRoot = doc.FirstChildElement("Project");
    if (lpRoot)
    {
        lpRoot = lpRoot->FirstChildElement("LastLogin");
    }
    else
    {
        lpRoot = doc.FirstChildElement("LastLogin");
    }
    if ( NULL == lpRoot )
        return FALSE;

    szValue = lpRoot->Attribute( "RoleName" );
    if( szValue )
    {
        std::wstring str = Common::_tstring::UTF8towcs(szValue);
        strncpy(m_strRole, Common::_tstring::toNarrowString(str.c_str()).c_str(), 64);
    }*/

const	char* szValue  = s_CUI_ID_FRAME_Select.GetUserListBySel();
	//char* szValue = thePlayerRole.GetName();
	std::wstring str = Common::_tstring::UTF8towcs(szValue);
	strncpy(m_strRole, Common::_tstring::toNarrowString(str.c_str()).c_str(), 64);


    return TRUE;
}

BOOL CUserData::WriteLoginData()
{
    char strFolder0[MAX_PATH] = {0};
    CreateDirectory("UserData",NULL);

    MeSprintf_s(strFolder0,sizeof(strFolder0)/sizeof(char) - 1 ,"UserData/%s", m_strAccount);    
	CreateDirectory(strFolder0,NULL);

    char strFolder1[MAX_PATH] = {0};
    MeSprintf_s(strFolder1,sizeof(strFolder1)/sizeof(char) - 1, "%s/%s", strFolder0, m_strArea);
    CreateDirectory(strFolder1,NULL);

	char strFolder2[MAX_PATH] = {0};
    MeSprintf_s(strFolder2,sizeof(strFolder2)/sizeof(char) - 1, "%s/%s", strFolder1, m_strServer);
    CreateDirectory(strFolder2,NULL);
    
	char strFolder3[MAX_PATH] = {0};
	MeSprintf_s(strFolder3,sizeof(strFolder3)/sizeof(char) - 1, "%s/%s", strFolder2, m_strRole);
    CreateDirectory(strFolder3,NULL);

    // 保存最后一次登录数据
    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/Login.config", GetRootPath());

    SetFileAttributes( szPath, FILE_ATTRIBUTE_NORMAL );
    MeXmlDocument doc;
    MeXmlDeclaration decl("1.0", "UTF-8", "yes");
    doc.InsertEndChild(decl);

	MeXmlElement *pProject = doc.InsertEndChild("Project");
    pProject->SetAttribute("Name", "HeroOnline");
    pProject->SetAttribute("Version", "");
//     MeXmlNode* pProjectNode = doc.InsertEndChild(pProject);

	MeXmlElement *pServer = pProject->InsertEndChild("LastLogin");
    std::wstring str = Common::_tstring::toWideString(m_strArea);
    pServer->SetAttribute("Region", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
    str = Common::_tstring::toWideString(m_strServer);
    pServer->SetAttribute("Server", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
    str = Common::_tstring::toWideString(m_strAccount);
    pServer->SetAttribute("Account", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
    pServer->SetAttribute("SoftKeyboard", (int)m_bSoftKeyboard);
//     pProjectNode->InsertEndChild(pServer);

	#ifdef NPGUARD
	//LYH NP
	if(npgl)
	npgl->Send(m_strAccount);
    #endif

    doc.SaveFile(szPath);
    return TRUE;

}

BOOL CUserData::LoadLoginData()
{
    char szPath[MAX_PATH] = {0};
	MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/Login.config", GetRootPath());

    MeXmlDocument doc;
    if( !doc.LoadFile(szPath) )
    {
		MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/Login.xml", GetRootPath());

		MeXmlDocument doc;
		if( !doc.LoadFile(szPath) )
			return FALSE;
    }

    const char* szValue = NULL;
    MeXmlElement* lpRoot = doc.FirstChildElement("Project");
    if (lpRoot)
    {
        lpRoot = lpRoot->FirstChildElement("LastLogin");
    }
    else
    {
        lpRoot = doc.FirstChildElement("LastLogin");
    }
    if ( NULL == lpRoot )
        return FALSE;

    std::wstring str;
    szValue = lpRoot->Attribute( "Region" );
    if( szValue )
    {
        str = Common::_tstring::UTF8towcs(szValue);
        strncpy(m_strArea, Common::_tstring::toNarrowString(str.c_str()).c_str(), 64);
    }
    szValue = lpRoot->Attribute( "Server" );
    if( szValue )
    {
        str = Common::_tstring::UTF8towcs(szValue);
        strncpy(m_strServer, Common::_tstring::toNarrowString(str.c_str()).c_str(), 64);
    }
    szValue = lpRoot->Attribute( "Account" );
    if( szValue )
    {
        str = Common::_tstring::UTF8towcs(szValue);
        strncpy(m_strAccount, Common::_tstring::toNarrowString(str.c_str()).c_str(), 64);
    }
    int iValue = 0;
    if (MEXML_SUCCESS == lpRoot->QueryIntAttribute("SoftKeyboard",&iValue) )
    {
        m_bSoftKeyboard = (bool)(iValue == 1);
    }
    return TRUE;
}

BOOL CUserData::WriteViewSet()
{
	// 保存最后一次镜头设置数据
	char szPath[MAX_PATH] = {0};
	MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/ViewSet.config", GetRootPath());

	SetFileAttributes( szPath, FILE_ATTRIBUTE_NORMAL );
	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "UTF-8", "yes");
	doc.InsertEndChild(decl);

    MeXmlElement *tProject = doc.InsertEndChild("Project");
	tProject->SetAttribute("Name", "HeroOnline");
	tProject->SetAttribute("Version", "");
// 	MeXmlNode* pProjectNode = doc.InsertEndChild(tProject);

	MeXmlElement *tViewSet = tProject->InsertEndChild("ViewSet");	
	tViewSet->SetAttribute("View", m_nViewSet);	
// 	pProjectNode->InsertEndChild(tViewSet);

	doc.SaveFile(szPath);
	return TRUE;


}
BOOL CUserData::LoadViewSet()
{
	char szPath[MAX_PATH] = {0};
	MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1, "%s/Client/UserData/ViewSet.config", GetRootPath());

	MeXmlDocument doc;
	if( !doc.LoadFile(szPath) )
	{
		return FALSE;
	}

	const char* szValue = NULL;
	MeXmlElement* lpRoot = doc.FirstChildElement("Project");
	if( !lpRoot )
		return false;

	MeXmlElement* pElement = lpRoot->FirstChildElement( "ViewSet" );
	if( !pElement )
		return false;

	int nResult = pElement->QueryIntAttribute( "View", &m_nViewSet );
	return ( nResult == MEXML_SUCCESS );

}

bool CUserData::SaveSuit()
{
    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/%s/%s/%s/suit.ws",GetRootPath(),m_strAccount, m_strArea, m_strServer, m_strRole);

    FILE* fp = fopen(szPath, "wb" );
    if( !fp )
        return false;   

    //数量
    int nCount = MAXSUITNUM;
    fwrite(&nCount,sizeof(int),1,fp);
    fwrite(&m_suitSetting,sizeof(SSuitSetting),1,fp);
    fwrite(m_SuitData,sizeof(SSuit) * nCount,1,fp);      //第几套装备
    if( fp )
        fclose( fp );

#ifdef _DEBUG

    {
        char szPath[MAX_PATH] = {0};
        MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/%s/%s/%s/suit.txt",GetRootPath(),m_strAccount, m_strArea, m_strServer, m_strRole);

        FILE* fp = fopen(szPath, "wb" );
        if( !fp )
            return false; 

    for (int j  = 0; j< MAXSUITNUM;++j)
        for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
        {
            __int64 nGuid = m_SuitData[j].m_ItemGuid[i];
            fwrite(&nGuid,sizeof(__int64),1,fp);
            fwrite("\n",sizeof("\n"),1,fp);
        }

        if(fp)
            fclose(fp);
        
    }
    DebugInfo();
#endif
    return true;
}

bool CUserData::ReadSuit()
{
    InitSuit();
    char szPath[MAX_PATH] = {0};
    MeSprintf_s(szPath,sizeof(szPath)/sizeof(char) - 1,"%s/Client/UserData/%s/%s/%s/%s/suit.ws", GetRootPath(),m_strAccount, m_strArea, m_strServer, m_strRole);

    f_Handle* fp = packet_namespace::w_fopen(szPath,"rb");
    if(!fp)
        return false;

    int nCount = 0;
    packet_namespace::w_fread(&nCount,sizeof(int),1,fp);
    packet_namespace::w_fread(&m_suitSetting,sizeof(m_suitSetting),1,fp);
    packet_namespace::w_fread(m_SuitData,sizeof(SSuit) * nCount,1,fp);
 
    if(fp)
        packet_namespace::w_fclose(fp);
   return true;
}

void CUserData::InitSuit()
{
    for (int i = 0;i < MAXSUITNUM;++i)
    {
        /*m_SuitData[i].m_nIndex = -1;*/
        memset(m_SuitData[i].m_ItemGuid,0L,sizeof(m_SuitData[i].m_ItemGuid));
    }
}


//bool CUserData::AddSuit(int nIndex)
//{
//    if(nIndex >= MAXSUITNUM)
//        return false;
//
//    m_SuitData[nIndex].m_nIndex = nIndex;
//    for (int i = 0;i < EPT_TotalWearCount;++i)
//    {
//         m_SuitData[nIndex].m_ItemGuid[i] = 0;
//
//
//        if(i < EPT_MaxEquitPart)
//        {
//            if(i == EPT_RHandItem || i == EPT_Armour || i == EPT_Shoe || i == EPT_Glove
//                || i == EPT_Necklace || i == EPT_Ring || i == EPT_RBangle || i == EPT_Sash
//                || i == EPT_Trousers || i == EPT_Shoulder || i == EPT_Helmet || i == EPT_Honor
//                || i == EPT_Badge     /*|| i == EPT_GemBag*/)		// 宝囊替换为披风		modified by ZhuoMeng.Hu		[8/31/2010]
//            {
//                if(thePlayerRole.m_pVisual->GetAllSuitArray()[i].itembaseinfo.ustItemID != InvalidLogicNumber)
//                    m_SuitData[nIndex].m_ItemGuid[i] = thePlayerRole.m_pVisual->GetAllSuitArray()[i].itembaseinfo.nOnlyInt;
//                else
//                    m_SuitData[nIndex].m_ItemGuid[i] = 0;
//            }
//        }
//        else
//        {
//            if( i == EPT_MaxEquitPart + EPT_Helmet
//                || i == EPT_MaxEquitPart + EPT_Armour
//                ||i == EPT_MaxEquitPart + EPT_Glove
//                ||i == EPT_MaxEquitPart + EPT_Shoe) //鞋子
//            {
//                if(thePlayerRole.m_pVisual->GetAllSuitArray()[i].itembaseinfo.ustItemID != InvalidLogicNumber)
//                    m_SuitData[nIndex].m_ItemGuid[i] = thePlayerRole.m_pVisual->GetAllSuitArray()[i].itembaseinfo.nOnlyInt;
//                else
//                    m_SuitData[nIndex].m_ItemGuid[i] = 0;
//            }
//        }
//
//#ifdef _DEBUG
//        __int64 ii = m_SuitData[nIndex].m_ItemGuid[i];
//        char szWord[128];
//        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%ld\n",ii);
//        ::OutputDebugString(szWord);
//#endif
//    }
//    return true;
//}

//add by yanli  2010-9-27
bool CUserData::AddSuit(int nIndex)
{
	if(nIndex >= MAXSUITNUM)
		return false;

	/*m_SuitData[nIndex].m_nIndex = nIndex;*/
	for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
	{
		m_SuitData[nIndex].m_ItemGuid[i] = 0;
		if(i < EEquipPartType_MaxEquitPart)
		{
			if(thePlayerRole.m_pVisual->GetVisualArray()[i].itembaseinfo.ustItemID != InvalidLogicNumber)
				m_SuitData[nIndex].m_ItemGuid[i] = thePlayerRole.m_pVisual->GetVisualArray()[i].itembaseinfo.nOnlyInt;
			else
				m_SuitData[nIndex].m_ItemGuid[i] = 0;
		}

#ifdef _DEBUG
		__int64 ii = m_SuitData[nIndex].m_ItemGuid[i];
		char szWord[128];
		MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%ld\n",ii);
		::OutputDebugString(szWord);
#endif
	}
	return true;
}

void CUserData::ClearSuit(int nIndex)
{
    if(nIndex >= MAXSUITNUM)
        return;

    /*m_SuitData[nIndex].m_nIndex = -1;*/
    memset(m_SuitData[nIndex].m_ItemGuid,0L,sizeof(m_SuitData[nIndex].m_ItemGuid));
}

//int CUserData::GetSuitIndex(int nIndex)
//{
//    int ii = m_SuitData[nIndex].m_nIndex;
//    return m_SuitData[nIndex].m_nIndex;
//}

#ifdef _DEBUG
void CUserData::DebugInfo()
{
    for (int j  = 0; j< MAXSUITNUM;++j)
    for (int i = 0;i < EEquipPartType_MaxEquitPart;++i)
    {
        __int64 nGuid = m_SuitData[j].m_ItemGuid[i];
        int nIndex = thePlayerRole.m_bag.GetItemIndexByGUID(nGuid);
        if(nIndex != -1)
        {
            SCharItem item;
            thePlayerRole.m_bag.GetItem(nIndex,&item);
        }
    }
}
#endif