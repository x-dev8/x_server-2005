#include "ItemDetailConfig.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"
#include "GameDefinePet.h"

#pragma warning( push, 0 )

int CItemDetail::FindPetIndexById( int nId )
{
    Id2IndexPetMonsterContainer::iterator it = m_mapId2IndexPetMonster.find( nId );
    if( it == m_mapId2IndexPetMonster.end() )
        return -1;
    return it->second;
}

int CItemDetail::FindPetIndexByName( const char *szName )
{
    Name2IndexPetMonsterContainer::iterator it = m_mapName2IndexPetMonster.find( szName );
    if( it == m_mapName2IndexPetMonster.end() )
        return -1;
    return it->second;
}

ItemDefine::SPetMonster* CItemDetail::GetPet( int nIndex )
{
    if( m_vecPetMonster.empty() )
        return NULL;

    if( nIndex < 0 || nIndex >= (int)m_vecPetMonster.size() )
        return NULL;

    return m_vecPetMonster[ nIndex ];
}

ItemDefine::SPetMonster* CItemDetail::GetPetById( int nId )
{
    int nIndex = FindPetIndexById(nId);
    if ( nIndex == -1)
        return NULL;

    return GetPet(nIndex);
}

ItemDefine::SPetMonster* CItemDetail::GetPetByName( const char* szName )
{ 
    int nIndex = FindPetIndexByName( szName );
    if ( nIndex == -1 )
        return NULL;

    return GetPet( nIndex ); 
}

std::vector< ItemDefine::SPetMonster* >&  CItemDetail::GetPetListByType( uint16 petType )
{
    if ( petType >= MAX_PETIDENTIFY_COUNT )
    { return m_mapPetTypeList[0]; }

    return m_mapPetTypeList[petType];
}

int CItemDetail::GetTalentSkillIdByType( uint16 petType )
{
    if ( petType >= MAX_PETIDENTIFY_COUNT )
    { return InvalidLogicNumber; }

    std::vector< ItemDefine::SPetMonster* >& vecPetMonster = m_mapPetTypeList[petType];
    std::vector< ItemDefine::SPetMonster* >::iterator iter = vecPetMonster.begin();
    for ( ; iter != vecPetMonster.end(); ++iter )
    {
        return (*iter)->talentSkillId;
    }

    return InvalidLogicNumber;
}

const char* CItemDetail::GetPetTypeName( uint16 petType )
{
    if ( petType >= MAX_PETIDENTIFY_COUNT )
    { return NULL; }

    std::vector< ItemDefine::SPetMonster* >& vecPetMonster = m_mapPetTypeList[petType];
    std::vector< ItemDefine::SPetMonster* >::iterator iter = vecPetMonster.begin();
    for ( ; iter != vecPetMonster.end(); ++iter )
    {
        return (*iter)->GetPetTypeName();
    }

    return NULL;
}

bool CItemDetail::LoadSlkPetMonster( const char *szFileName )
{
    CSlkReader pReader;
    if( !pReader.ReadFromFile( szFileName ) )
        return false;

    int   iRow   = 3;
    int   iCol   = 0;
    int   iRet   = 0;
    int   iValue = 0;
    float fValue = 0.0f;

    std::string strTemp, strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        ItemDefine::SPetMonster* pPetMonster = (ItemDefine::SPetMonster*)AllocItem( 0, sizeof( ItemDefine::SPetMonster ) );
        if( !pPetMonster )
        {
            OutputSlkLoadingMessage( "Error:分配Pet需要的内存出错 [%d]\r\n", iRow );
            return false;
        }

        if( !pReader.GetIntFieldByName("PetID", iValue) )
        { // 宠物索引ID
            OutputSlkLoadingMessage( "\t  载入宠物索引ID出错!\r\n" );
            goto load_error;
        }
        pPetMonster->stMonsterId = iValue;

        ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterById( pPetMonster->stMonsterId  );
        if (pMonster == NULL)
        {
            OutputSlkLoadingMessage( "\t  载入怪物索引ID出错!\r\n" );
            goto load_error;
        }

        *(ItemDefine::SMonster*)pPetMonster = *pMonster;

        if( !pReader.GetIntFieldByName("ItemID",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入宠物物品ID出错!\r\n" );
            goto load_error;
        }
        pPetMonster->itemId = iValue;

        if( !pReader.GetStringFieldByName( "PetDesc", strTemp ))
        { 
            OutputSlkLoadingMessage( "\t  载入-宠物简介-出错!\r\n" );
            goto load_error;
        }
        pPetMonster->dwPetDescAddr = AllocStringCopy( strTemp.c_str() );

        if( !pReader.GetStringFieldByName( "BornDesc", strTemp ))
        { 
            OutputSlkLoadingMessage( "\t  载入-宠物出没简介-出错!\r\n" );
            goto load_error;
        }
        pPetMonster->dwPetBornDescAddr = AllocStringCopy( strTemp.c_str() );

        if( !pReader.GetIntFieldByName( "NameColor", iValue ))
        { 
            OutputSlkLoadingMessage( "\t  载入-宠物名字颜色-出错!\r\n" );
            goto load_error;
        }
        pPetMonster->dwNameColor = iValue;

        if( !pReader.GetIntFieldByName("PetType",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入宠物类型出错!\r\n" );
            goto load_error;
        }
        pPetMonster->petType = iValue;

        if( !pReader.GetStringFieldByName( "PetTypeName", strTemp ))
        { 
            OutputSlkLoadingMessage( "\t  载入-宠物类型名称-出错!\r\n" );
            goto load_error;
        }
        pPetMonster->dwPetTypeNameAddr = AllocStringCopy( strTemp.c_str() );

        if( !pReader.GetIntFieldByName("AberranceLv",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入变异级别出错!\r\n" );
            goto load_error;
        }
        pPetMonster->aberranceLevel = iValue;

        if( !pReader.GetIntFieldByName("CatchRank",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入捕捉品质出错!\r\n" );
            goto load_error;
        }
        pPetMonster->catchQuality = iValue;

        if( !pReader.GetIntFieldByName("CatchLv",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入捕捉等级出错!\r\n" );
            goto load_error;
        }
        pPetMonster->catchLevel = iValue;

        if( !pReader.GetIntFieldByName("CarryLv",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入携带等级出错!\r\n" );
            goto load_error;
        }
        pPetMonster->takeLevel = iValue;

        if( !pReader.GetIntFieldByName("ItsBabyID",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入宝宝ID出错!\r\n" );
            goto load_error;
        }
        pPetMonster->babyId = iValue;

        if( !pReader.GetIntFieldByName("IsAberrance",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入是否变异出错!\r\n" );
            goto load_error;
        }
        pPetMonster->bIsAberrance = iValue;

        if( !pReader.GetIntFieldByName("IsBaby",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入是否宝宝出错!\r\n" );
            goto load_error;
        }
        pPetMonster->bIsBaby = iValue;

        if( !pReader.GetStringFieldByName("Food",strTemp ) )
        {
            OutputSlkLoadingMessage( "\t  载入食物出错!\r\n" );
            goto load_error;
        }
        pPetMonster->food = HelperFunc::GetIDByConstString((char*)strTemp.c_str(), g_szPetFoodType,sizeof(g_szPetFoodType)/sizeof( char* ) );

        if( !pReader.GetIntFieldByName("Duration",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入寿命出错!\r\n" );
            goto load_error;
        }
        pPetMonster->duration = iValue;

        if( !pReader.GetIntFieldByName("AttackType",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入攻击类型出错!\r\n" );
            goto load_error;
        }
        pPetMonster->attackType = iValue;

        if( !pReader.GetIntFieldByName("RegenerateTime",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入重生时间出错!\r\n" );
            goto load_error;
        }
        pPetMonster->regenerateTime = iValue;

		if( !pReader.GetIntFieldByName("IdentifyTotal",iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入图鉴总数出错!\r\n" );
			goto load_error;
		}
		pPetMonster->identifyTotal = iValue;

        if( !pReader.GetIntFieldByName("BaseStr",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入力量资质出错!\r\n" );
            goto load_error;
        }
        pPetMonster->aptitudeAttr[EBaseAttr_Strength] = iValue;

        if( !pReader.GetIntFieldByName("BaseDex",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入敏捷资质出错!\r\n" );
            goto load_error;
        }
        pPetMonster->aptitudeAttr[EBaseAttr_Agility] = iValue;

        if( !pReader.GetIntFieldByName("BaseCon",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入耐力资质出错!\r\n" );
            goto load_error;
        }
        pPetMonster->aptitudeAttr[EBaseAttr_Stamina] = iValue;

        if( !pReader.GetIntFieldByName("BaseInt",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入灵气资质出错!\r\n" );
            goto load_error;
        }
        pPetMonster->aptitudeAttr[EBaseAttr_Intelligence] = iValue;

        if( !pReader.GetIntFieldByName("SkillNum",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入SkillNum出错!\r\n" );
            goto load_error;
        }
        pPetMonster->skillNumControl = iValue;

        if( !pReader.GetIntFieldByName("TalentSkill",iValue ) )
        {
            OutputSlkLoadingMessage( "\t  载入天赋技能出错!\r\n" );
            goto load_error;
        }
        pPetMonster->talentSkillId = iValue;

        SLK_GET_STRING( strTemp, "GrowthRate" );
        StrToIntArray( strTemp.c_str(), pPetMonster->growthRate , EPetGrowth_Count, ";"  );

        SLK_GET_STRING( strTemp, "CharacterizeRate"  );
        StrToIntArray( strTemp.c_str(), pPetMonster->characterizeRate , EPetChar_Count, ";"  );

        SLK_GET_STRING( strTemp, "LvRealizeSkill" );
        StrToIntArray( strTemp.c_str(), pPetMonster->lvRealizeSkill , ItemDefine::SPetMonster::EPet_LvRealizeCount, ";"  );

        SLK_GET_STRING( strTemp, "ManualSkill" );
        StrToIntArray( strTemp.c_str(), pPetMonster->manualSkillId  , ItemDefine::SPetMonster::EPet_RandSkillCount, ";"  );

        SLK_GET_STRING( strTemp, "ManualSkillRate" );
        StrToIntArray( strTemp.c_str(), pPetMonster->manualSkillRate, ItemDefine::SPetMonster::EPet_RandSkillCount, ";"  );

        SLK_GET_STRING( strTemp, "AutoSkill" );
        StrToIntArray( strTemp.c_str(), pPetMonster->autoSkillId    , ItemDefine::SPetMonster::EPet_RandSkillCount, ";"  );

        SLK_GET_STRING( strTemp, "AutoSkillRate"  );
        StrToIntArray( strTemp.c_str(), pPetMonster->autoSkillRate  , ItemDefine::SPetMonster::EPet_RandSkillCount, ";"  );

        SLK_GET_STRING( strTemp, "BabyListID"  );
        StrToIntArray( strTemp.c_str(), pPetMonster->babyListId     , ItemDefine::SPetMonster::EPet_BabyListIDCount, ";" );

        SLK_GET_STRING( strTemp, "BabyListIDRate"  );
        StrToIntArray( strTemp.c_str(), pPetMonster->babyListIdRate , ItemDefine::SPetMonster::EPet_BabyListIDCount, ";" );

        SLK_GET_STRING( strTemp, "DropItemIds"  );
        StrToIntArray( strTemp.c_str(), pPetMonster->dropItemIds    , ItemDefine::SPetMonster::EPet_DropItemIDCount, ";" );

        pPetMonster->iPetContainerIndex = m_vecPetMonster.size();

        //加入查找
        m_mapId2IndexPetMonster.insert( Id2IndexPetMonsterContainer::value_type( pPetMonster->stMonsterId, pPetMonster->iPetContainerIndex) );
        m_mapName2IndexPetMonster.insert( Name2IndexPetMonsterContainer::value_type( pPetMonster->GetName(), pPetMonster->iPetContainerIndex ) );

        //加入队列
        m_vecPetMonster.push_back( pPetMonster );
        continue;

load_error:
        OutputSlkLoadingMessage( "\tmonster.slk 第 %d 行载入失败!\r\n",iRow-1 );
        return false;
    }
    return true;
}

bool CItemDetail::LoadXmlPetMonster( const char *szFile )
{
    if (szFile == NULL)
    { return false; }

    MeXmlDocument mMeXmlDoc;
    if (!mMeXmlDoc.LoadFile(szFile))
    { return false; }

    MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pMonsterTree = pRoot->FirstChildElement("Pets");
    if (pMonsterTree == NULL)
    { return false; }

    MeXmlElement *pElement = pMonsterTree->FirstChildElement("Pet");

    int iValue = 0;
    double dValue = 0.000000;

    while(pElement != NULL)
    {
        ItemDefine::SPetMonster* pPetMonster = (ItemDefine::SPetMonster*)AllocItem( 0, sizeof( ItemDefine::SPetMonster ) );

        if (pElement->Attribute("PetID", &pPetMonster->stMonsterId) == NULL)
        { return false; }

        ItemDefine::SMonster *pMonster = GettheItemDetail().GetMonsterById( pPetMonster->stMonsterId  );
        if (pMonster == NULL)
        { return false; }

        *(ItemDefine::SMonster*)pPetMonster = *pMonster;

        pElement->Attribute("ItemID", &iValue);
        pPetMonster->itemId = iValue;
        
        Common::_tstring strPetDesc;
        strPetDesc.fromUTF8(pElement->Attribute("PetDesc"));
        pPetMonster->dwPetDescAddr = AllocStringCopy(strPetDesc.c_str());

        Common::_tstring strBornDesc;
        strBornDesc.fromUTF8(pElement->Attribute("PetBornDesc"));
        pPetMonster->dwPetBornDescAddr = AllocStringCopy(strBornDesc.c_str());

        Common::_tstring strPetTypeName;
        strPetTypeName.fromUTF8(pElement->Attribute("PetTypeName"));
        pPetMonster->dwPetTypeNameAddr = AllocStringCopy(strPetTypeName.c_str());

        pElement->Attribute("NameColor", &iValue);
        pPetMonster->dwNameColor = iValue;

        pElement->Attribute("PetType", &iValue);
        pPetMonster->petType = iValue;

        pElement->Attribute("AberranceLv", &iValue);
        pPetMonster->aberranceLevel = iValue;

        pElement->Attribute("CatchRank", &iValue);
        pPetMonster->catchQuality = iValue;

        pElement->Attribute("CatchLv", &iValue);
        pPetMonster->catchLevel = iValue;

        pElement->Attribute("CarryLv", &iValue);
        pPetMonster->takeLevel = iValue;

        pElement->Attribute("ItsBabyID", &iValue);
        pPetMonster->babyId = iValue;

        pElement->Attribute("IsAberrance", &iValue);
        pPetMonster->bIsAberrance = iValue;

        pElement->Attribute("IsBaby", &iValue);
        pPetMonster->bIsBaby = iValue;
        
        Common::_tstring strPetFood;
        strPetFood.fromUTF8(pElement->Attribute("Food"));
        pPetMonster->food = HelperFunc::GetIDByConstString((char*)strPetFood.c_str(), g_szPetFoodType,sizeof(g_szPetFoodType)/sizeof( char* ) );

        pElement->Attribute("Duration", &iValue);
        pPetMonster->duration = iValue;
        
        pElement->Attribute("AttackType", &iValue);
        pPetMonster->attackType = iValue;

        pElement->Attribute("RegenerateTime", &iValue);
        pPetMonster->regenerateTime = iValue;

		pElement->Attribute("IdentifyTotal", &iValue);
		pPetMonster->identifyTotal = iValue;

        pElement->Attribute("BaseStr", &iValue);
        pPetMonster->aptitudeAttr[EBaseAttr_Strength] = iValue;

        pElement->Attribute("BaseDex", &iValue);
        pPetMonster->aptitudeAttr[EBaseAttr_Agility]  = iValue;

        pElement->Attribute("BaseCon", &iValue);
        pPetMonster->aptitudeAttr[EBaseAttr_Stamina]  = iValue;

        pElement->Attribute("BaseInt", &iValue);
        pPetMonster->aptitudeAttr[EBaseAttr_Intelligence] = iValue;

        pElement->Attribute("SkillNum", &iValue);
        pPetMonster->skillNumControl = iValue;

        pElement->Attribute("TalentSkill", &iValue);
        pPetMonster->talentSkillId = iValue;

        for ( int i=0; i<EPetGrowth_Count; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "GrowthRate%d",i+1);
            pElement->Attribute(szTmp, &iValue);
            pPetMonster->growthRate[i] = iValue;
        }

        for ( int i=0; i<EPetChar_Count; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "CharacterizeRate%d",i+1);
            pElement->Attribute(szTmp, &iValue);
            pPetMonster->characterizeRate[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_LvRealizeCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "LvRealizeSkill%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->lvRealizeSkill[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "ManualSkill%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->manualSkillId[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "ManualSkillRate%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->manualSkillRate[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "AutoSkill%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->autoSkillId[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "AutoSkillRate%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->autoSkillRate[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_BabyListIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "BabyListID%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->babyListId[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_BabyListIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "BabyListIDRate%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->babyListIdRate[i] = iValue;
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_DropItemIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "DropItemID%d", i+1);
            pElement->Attribute(szTemp, &iValue);
            pPetMonster->dropItemIds[i] = iValue;
        }

        pPetMonster->iPetContainerIndex = m_vecPetMonster.size();

        //加入查找
        m_mapId2IndexPetMonster.insert( Id2IndexPetMonsterContainer::value_type( pPetMonster->stMonsterId, pPetMonster->iPetContainerIndex) );
        m_mapName2IndexPetMonster.insert( Name2IndexPetMonsterContainer::value_type( pPetMonster->GetName(), pPetMonster->iPetContainerIndex ) );
        m_mapPetTypeList[pPetMonster->petType].push_back( pPetMonster );

        //加入队列
        m_vecPetMonster.push_back( pPetMonster );

        pElement = pElement->NextSiblingElement();
    }

    return true;
}

bool CItemDetail::SaveXMLPetMonster( const char *szFile)
//保存XML怪物的相关信息
{
    if (szFile == NULL || *szFile == 0)
    { return false; }

    MeXmlDocument saveMonsterMeXml;
    saveMonsterMeXml.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = saveMonsterMeXml.InsertEndChild(("Project"))->ToElement();

    pRoot->SetAttribute("Type", "Monster");

    SYSTEMTIME xSystemTime;
    ::GetLocalTime(&xSystemTime);
    char szTime[50] = "";
    sprintf_s(szTime, sizeof(szTime) -1 , "%d-%d-%d %d:%d:%d", 
        xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);
    pRoot->SetAttribute("Value", szTime);
    pRoot->SetAttribute("Count", m_vecPetMonster.size());

    MeXmlElement* pMonsters = pRoot->InsertEndChild(("Pets"))->ToElement();
    if(pMonsters == NULL)  
    { return false; }

    PetMonsterContainer::iterator iter = m_vecPetMonster.begin();
    PetMonsterContainer::iterator end  = m_vecPetMonster.end();

    for (; iter != end; ++iter)
    {
        ItemDefine::SPetMonster* pPetIter = *iter;

        MeXmlElement* pPetElement = pMonsters->InsertEndChild(("Pet"))->ToElement();
        if ( pPetElement == NULL )
        { continue; }

        pPetElement->SetAttribute("PetID", pPetIter->stMonsterId);     
        pPetElement->SetAttribute("ItemID", pPetIter->itemId);  

        Common::_tstring strPetDesc = pPetIter->GetPetDesc();
        pPetElement->SetAttribute("PetDesc", strPetDesc.toUTF8().c_str());

        Common::_tstring strPetBornDesc = pPetIter->GetPetBornDesc();
        pPetElement->SetAttribute("PetBornDesc", strPetBornDesc.toUTF8().c_str());

        Common::_tstring strPetTypeName = pPetIter->GetPetTypeName();
        pPetElement->SetAttribute("PetTypeName", strPetTypeName.toUTF8().c_str());

        pPetElement->SetAttribute("NameColor", pPetIter->dwNameColor);  
        pPetElement->SetAttribute("PetType", pPetIter->petType);  
        pPetElement->SetAttribute("AberranceLv", pPetIter->aberranceLevel);  
        pPetElement->SetAttribute("CatchRank", pPetIter->catchQuality);  
        pPetElement->SetAttribute("CatchLv", pPetIter->catchLevel);  
        pPetElement->SetAttribute("CarryLv", pPetIter->takeLevel);  
        pPetElement->SetAttribute("ItsBabyID", pPetIter->babyId);  
        pPetElement->SetAttribute("IsAberrance", pPetIter->bIsAberrance);  
        pPetElement->SetAttribute("IsBaby", pPetIter->bIsBaby);  
        
        pPetElement->SetAttribute("Food", g_szPetFoodType[pPetIter->food]);  

        pPetElement->SetAttribute("Duration", pPetIter->duration);  
        pPetElement->SetAttribute("AttackType", pPetIter->attackType);  
        pPetElement->SetAttribute("RegenerateTime", pPetIter->regenerateTime);
		pPetElement->SetAttribute("IdentifyTotal", pPetIter->identifyTotal);
        pPetElement->SetAttribute("BaseStr", pPetIter->aptitudeAttr[EBaseAttr_Strength]);  
        pPetElement->SetAttribute("BaseDex", pPetIter->aptitudeAttr[EBaseAttr_Agility]);  
        pPetElement->SetAttribute("BaseCon", pPetIter->aptitudeAttr[EBaseAttr_Stamina]);  
        pPetElement->SetAttribute("BaseInt", pPetIter->aptitudeAttr[EBaseAttr_Intelligence]);  

        pPetElement->SetAttribute("SkillNum", pPetIter->skillNumControl);  
        pPetElement->SetAttribute("TalentSkill", pPetIter->talentSkillId);  
        
        for ( int i=0; i<EPetGrowth_Count; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "GrowthRate%d",i+1);
            pPetElement->SetAttribute(szTmp, pPetIter->growthRate[i]);  
        }

        for ( int i=0; i<EPetChar_Count; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "CharacterizeRate%d",i+1);
            pPetElement->SetAttribute(szTmp, pPetIter->characterizeRate[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_LvRealizeCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "LvRealizeSkill%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->lvRealizeSkill[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "ManualSkill%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->manualSkillId[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "ManualSkillRate%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->manualSkillRate[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "AutoSkill%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->autoSkillId[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_RandSkillCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "AutoSkillRate%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->autoSkillRate[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_BabyListIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "BabyListID%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->babyListId[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_BabyListIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "BabyListIDRate%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->babyListIdRate[i]); 
        }

        for ( int i=0; i<ItemDefine::SPetMonster::EPet_DropItemIDCount; ++i)
        {
            char szTemp[513] = {0};
            sprintf_s( szTemp, sizeof( szTemp ) - 1, "DropItemID%d", i+1);
            pPetElement->SetAttribute(szTemp, pPetIter->dropItemIds[i]); 
        }
        
    }

    return saveMonsterMeXml.SaveFile(szFile);
}

#pragma warning( pop )