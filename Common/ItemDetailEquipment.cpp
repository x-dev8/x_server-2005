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

#pragma warning( push, 0 )


//////////////////////////////////////////////////////////////////////////
//  ���� Slk �ļ�װ�����߹�����������
//////////////////////////////////////////////////////////////////////////

void CItemDetail::ReadCanEquipData( CSlkReader &pReader, ItemDefine::SItemCanEquip* pEquip, const char* szFileName )
{    
    int         iValue = 0;
    float       fValue = 0.0f;
    std::string strValue;

    // ��װ���Ĳ�λ
    SLK_GET_STRING( strValue, "CanEquipPart");
    SetCanEquipByString( pEquip->arrayCanEquip,strValue.c_str() );

    // �Ƿ�ͨ��
    SLK_GET_INT( pEquip->isCommon, "Common");


    // �滻��Ƥ��
    SLK_GET_STRING( strValue, "Skin");
    if ( strValue.empty())
        strValue = "Default";

    pEquip->dwReplaceSkinAddr = AllocStringCopy( strValue.c_str() );

    // �Ƿ������Ч��
    SLK_GET_INT( pEquip->isSpecular, "IsSpecular" );

    // �Ƿ����
    SLK_GET_INT( pEquip->isCanDistortion, "IsCanDistortion");

    // ���ε�id
    for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_DistortionIdCount; ++i)
    {
        char szTmp[65] = { 0 };
        sprintf_s(szTmp, sizeof(szTmp) - 1, "DistortionId%d",i+1);
        SLK_GET_INT( pEquip->arrayDistortionId[i], szTmp );
    }

    // �Ա�����
    SLK_GET_STRING( strValue, "GenderNeed");
    if ( strValue.empty()   || strValue == "" || strValue == "NULL" || strValue == "null")
        pEquip->cEquipSexReq = -1;
    else
        pEquip->cEquipSexReq = HelperFunc::GetIDByConstString( (char*)strValue.c_str() ,ItemDefine::g_szSexType,sizeof( ItemDefine::g_szSexType )/sizeof(char*) );

    // ��������
    for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
    {
        pEquip->arrayEquipArmsReq[ iLoop ] = false;
    }

    SLK_GET_STRING( strValue, "ArmsNeed");
    if ( strValue.empty())
    {
        for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
        {    
            pEquip->arrayEquipArmsReq[ iLoop ] = true;
        }
    }
    else
    {  
        //���ö��ְҵ
        char *szSpn = ",";
        char *szStr;
        int iEquip;
        szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
        while( szStr )
        {

            iEquip = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
            if( iEquip >= 0 && iEquip < EArmType_MaxSize )
            {
                pEquip->arrayEquipArmsReq[ iEquip ] = true;
            }
            szStr = strtok( NULL,szSpn );
        }
    }

    // �ȼ�����
    SLK_GET_INT( pEquip->stEquipLevelReq,    "LevelNeed");

    // pkֵ����
    SLK_GET_INT( pEquip->nPkValueNeed,       "PKValueNeed");

    // �ƺ�
    SLK_GET_INT( pEquip->nTitleNeed,         "TitleNeed");

    // �۸�
    SLK_GET_INT( pEquip->stRepairPrice,      "RepairPrice");

    // �;ö�
    SLK_GET_INT( pEquip->stHPMax,            "Durability");

    // ״̬������(����)
    SLK_GET_FLOAT( pEquip->fStatusRate,      "HitChanceOfStatus(enemy)");

    // ״̬������(��)
    SLK_GET_FLOAT( pEquip->fMyStatusRate,    "HitChanceOfStatus(self)");

    // ����״̬(����)
    SLK_GET_INT( pEquip->stAddStatus,        "AdditionalStatus(enemy)" );    

    // ״̬�ȼ�(����)
    SLK_GET_INT( pEquip->stAddStatusLevel,   "StatusLevel(enemy)" );

    // ״̬������ʽ(����)
    SLK_GET_INT( pEquip->nAddStatusTrigger,  "StatusTrigger(enemy)" );

    // ����״̬(��)
    SLK_GET_INT( pEquip->stMyAddStatus,      "AdditionalStatus(self)" );

    // ״̬�ȼ�(��)
    SLK_GET_INT( pEquip->stMyAddStatusLevel, "StatusLevel(self)" );

    // ״̬������ʽ(��)
    SLK_GET_INT( pEquip->nMyAddStatusTrigger,"StatusTrigger(self)" );

    // �������
//modified by junyi.chen begin
//    SLK_GET_INT( pEquip->additiveRandCount, "AdditiveRandCount" );
	SLK_GET_INT( pEquip->bRandWhenCreate, "RandWhenCreate" );

	for ( int i = 0; i < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i )
	{
		pEquip->additiveRandCountRates[i] = 0;
	}

	SLK_GET_STRING( strValue, "AdditiveRandCountRate" );

	if ( !strValue.empty() && strValue != "" )
	{
		char *szSpn = ",";
		char *szStr;
		int i = 0;
		szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
		while( szStr )
		{
			if ( atoi(szStr) > 0 )
			{
				pEquip->additiveRandCountRates[i] = atoi(szStr);
			}
			szStr = strtok( NULL,szSpn );
			++i;
		}
	}

	//����������Եȼ�����
	SLK_GET_INT( pEquip->additiveRandLvLowerLimit, "AdditiveRandLvLowerLimit" );

	//����������Եȼ�����
	SLK_GET_INT( pEquip->additiveRandLvUpperLimit, "AdditiveRandLvUpperLimit" );

	//����ɸѡ
	for ( int i = 0; i < pEquip->typeFilter.GetSize(); ++i )
	{
		pEquip->typeFilter[i] = 0;
	}

	SLK_GET_STRING( strValue, "TypeFilter" );

	if ( !strValue.empty() && strValue != "" )
	{
		char *szSpn = ",";
		char *szStr;
		int i = 0;
		szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
		while( szStr )
		{
			if ( atoi(szStr) > 0 )
			{
				pEquip->typeFilter[i] = atoi(szStr);
			}
			szStr = strtok( NULL,szSpn );
			++i;
		}
	}
//end

	//hero����ɸѡ
	//for ( int i = 0; i < pEquip->typeFilter_hero.GetSize(); ++i )
	//{
	//	pEquip->typeFilter_hero[i] = 0;
	//}

	//SLK_GET_STRING( strValue, "TypeFilter_Hero" );

	//if ( !strValue.empty() && strValue != "" )
	//{
	//	char *szSpn = ",";
	//	char *szStr;
	//	int i = 0;
	//	szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
	//	while( szStr )
	//	{
	//		if ( atoi(szStr) > 0 )
	//		{
	//			pEquip->typeFilter_hero[i] = atoi(szStr);
	//		}
	//		szStr = strtok( NULL,szSpn );
	//		++i;
	//	}
	//}
	//end

    // �����ʾ
    for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
    {
        pEquip->additiveRandFlags[i]  = 0;
//modified by junyi.chen begin
//        pEquip->additiveRandValues[i]  = 0;
//end
    }

    SLK_GET_STRING( strValue, "AdditiveRandFlags");

    if ( !strValue.empty()  && strValue != "" )
    {   
        char *szSpn = ",";
        char *szStr;
        int i = 0;
        szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
        while( szStr )
        {
            if ( atoi(szStr) > 0 )
            {
                pEquip->additiveRandFlags[i] = atoi(szStr);
            }
            szStr = strtok( NULL,szSpn );
            ++i;
        }
    }
//modified by junyi.chen begin
//     // ���ֵ
//     for ( int i=0; i<SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
//     {
//         char szTmp[65] = { 0 };
//         sprintf_s(szTmp, sizeof(szTmp) - 1, "AdditiveRandValue%d",i+1);
//         SLK_GET_INT( pEquip->additiveRandValues[i], szTmp );
//     }
//end
    //��ɫ�����������
    SLK_GET_INT( pEquip->purpleRandCount, "PurpleRandCount" );

    //��ɫ���������ʾ
    for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++i)
    {
        pEquip->purpleRandFlags[i]  = 0;
        pEquip->purpleRandValues[i]  = 0;
    }

    SLK_GET_STRING( strValue, "PurpleRandFlags");

    if ( !strValue.empty()  && strValue != "" )
    {   
        char *szSpn = ",";
        char *szStr;
        int i = 0;
        szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
        while( szStr )
        {
            if ( atoi(szStr) > 0 )
            {
                pEquip->purpleRandFlags[i] = atoi(szStr);
            }
            szStr = strtok( NULL,szSpn );
            ++i;
        }
    }

    //��ɫ�������ֵ
    for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++i)
    {
        char szTmp[65] = { 0 };
        sprintf_s(szTmp, sizeof(szTmp) - 1, "PurpleRandValue%d",i+1);
        SLK_GET_INT( pEquip->purpleRandValues[i], szTmp );
    }

    // �Ƿ���ʱװ
    SLK_GET_INT( pEquip->bFashion, "IsFashion" );

    // ����
    SLK_GET_STRING( strValue, "SoundPrefix");        
    pEquip->dwSoundAddr = AllocStringCopy( strValue.c_str() );

    // ��������
    SLK_GET_FLOAT( pEquip->attackPhysics, "PhysicsAttack");

    // ħ��������
    SLK_GET_FLOAT( pEquip->attackMagic,   "MagicAttack");

    // �����ٶ�
    SLK_GET_FLOAT( pEquip->attackSpeed, "AttackSpeed");

    // ������
    SLK_GET_FLOAT( pEquip->exact,       "Exact");

    // ������
    SLK_GET_FLOAT( pEquip->dodge,       "Dodge");

    // ������
    SLK_GET_FLOAT( pEquip->critical,    "Critical");

    // ����
    SLK_GET_FLOAT( pEquip->tenacity,    "Tenacity");

	//Ԫ������
	SLK_GET_FLOAT( pEquip->breakStrike,    "BreakStrike");
	SLK_GET_FLOAT( pEquip->breakResist,    "BreakResist");
	SLK_GET_FLOAT( pEquip->stabStrike,	   "StabStrike");
	SLK_GET_FLOAT( pEquip->stabResist,     "StabResist");
	SLK_GET_FLOAT( pEquip->elementStrike,  "ElementStrike");
	SLK_GET_FLOAT( pEquip->elementResist,  "ElementResist");
	SLK_GET_FLOAT( pEquip->toxinStrike,    "ToxinStrike");
	SLK_GET_FLOAT( pEquip->toxinResist,    "ToxinResist");
	SLK_GET_FLOAT( pEquip->spiritStrike,   "SpiritStrike");
	SLK_GET_FLOAT( pEquip->spiritResist,   "SpiritResist");

    // ����ID
    SLK_GET_INT( pEquip->skillId,         "skillId");

    // ���ܵȼ�
    SLK_GET_INT( pEquip->skillLevel,      "skillLevel");

    // ��������
    SLK_GET_INT( pEquip->uchRepairType,   "RepairType" );

    // ����ֵ
    SLK_GET_INT( pEquip->nRepairValue,    "RepairValue" );

    // ��װ�������
    SLK_GET_INT( pEquip->sPartCount,      "SuitNum" );

    // ������װID
    SLK_GET_INT( pEquip->sSuitID,         "SuitID" ); 

    // �Ƿ�������װ
    SLK_GET_INT( pEquip->bIsElements,     "IsElements" );

	// �Ƿ�������װ
	SLK_GET_INT( pEquip->nHeroID,     "HeroID" );
	
	//�������
	SLK_GET_INT( pEquip->unBindCount,     "UnBindCount" );
}

bool CItemDetail::AddWeaponItem( const char *szFileName )
{

    //const char* szFileName = "Weapon.slk";

    CSlkReader pReader;
    OutputSlkLoadingMessage( "���ڷ���%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "�Ҳ���%s�ļ�\r\n",szFileName);
        return false;
    }

    int offset = 3;
    int iRet;

    std::string strValue;
    std::string strSound;
    int         iValue     = 0;
    float       fValue     = 0.0f;


    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"ItemID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  ����:��ȡ ItemID �����к� %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON)
        {
            OutputSlkLoadingMessage( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemWeapon *pItemWeapon = (ItemDefine::SItemWeapon *)pCommon;

        // װ������ �϶�������
        pItemWeapon->ustEquipType = ItemDefine::equip_Weapon;        

        //////////////////////////////////////////////////////////////////////////
        //  ��ȡװ�����߹�������
        //////////////////////////////////////////////////////////////////////////

        ReadCanEquipData( pReader, pItemWeapon, "Weapon.slk");

        //////////////////////////////////////////////////////////////////////////

        // ����ģ��ID
        SLK_GET_INT(pItemWeapon->ustModelID[0],  "LeftHandModelID"  );  

        // ����ģ��ID
        SLK_GET_INT(pItemWeapon->ustModelID[1],  "RightHandModelID"  ); 

        // ����ID
        SLK_GET_INT(pItemWeapon->ustIdleModelID, "TakeBackID"  );       

        // ��������
        SLK_GET_STRING( strValue, "WeaponType");
        if ( strValue.empty())
        {
            pItemWeapon->stWeaponType = eWeaponType_Combat;
        }
        else
        {
            int nType = GetIDByConstString( strValue.c_str(),ItemDefine::g_szWeaponType,sizeof(ItemDefine::g_szWeaponType)/sizeof(char*) );
            pItemWeapon->stWeaponType = nType;
            if ( nType == -1)
            {
                OutputSlkLoadingMessage( "\tError:weapon.slk[�������Ͳ�����]ʧ��\r\n" );
                pItemWeapon->stWeaponType = eWeaponType_Combat;
            }
        }

        // �����Ӷ��ٶ�
        SLK_GET_FLOAT( pItemWeapon->fWeaponAttackRate , "WeaponSwingSpeed");

        // �Ƿ���˫������
        SLK_GET_INT( pItemWeapon->bTwoHandWeapon, "IfDoubleWeapon(0/1)");

        // ������Χ
        SLK_GET_FLOAT( pItemWeapon->fAtkRange, "AttackRange");

        // ������Ч
        SLK_GET_INT( pItemWeapon->iShotEffectID, "LaunchEffectId" );       

        m_vecWeaponItem.push_back(pItemWeapon) ;
    }

    return true;

}


bool CItemDetail::AddArmourItem( const char *szFileName )
{
    //const char* szFileName = "Armour.slk";

    CSlkReader pReader;
    OutputSlkLoadingMessage( "���ڷ���%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "�Ҳ���%s�ļ�\r\n",szFileName);
        return false;
    }

    int offset = 3;
    int iRet;

    std::string strValue;
    std::string strSound;
    int         iValue;
    float       fValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"ItemID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  ����:��ȡ ItemID �����к� %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
        {
            OutputSlkLoadingMessage( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemArmour *pItemArmour = (ItemDefine::SItemArmour *)pCommon;

        // װ������
        SLK_GET_STRING( strValue, "EquipType");
        if ( !strValue.empty())
        {
            iValue = HelperFunc::GetIDByConstString( (char*)strValue.c_str(), ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );

            if( -1 == iValue )
                iValue = 1;
            pItemArmour->ustEquipType = 1;
            pItemArmour->ustEquipType <<= iValue;
        }

        //////////////////////////////////////////////////////////////////////////
        //  ���ؿ�װ�����߹�������
        //////////////////////////////////////////////////////////////////////////

        ReadCanEquipData( pReader,pItemArmour, "Armour.slk" );

        //////////////////////////////////////////////////////////////////////////

        // �Ƿ�Ϊ����
        SLK_GET_INT( pItemArmour->isCape, "Ifcloth" );

        // �Ƿ�Ϊͷ��
        SLK_GET_INT( pItemArmour->isHeadWear, "Ifheadwear" );

        //ģ��ID
        SLK_GET_INT( iValue, "ModelID" );        
        for( int i=0;i<EArmType_MaxSize;i++ )
        {
            pItemArmour->ustModelID[i][0][0] = iValue;
            pItemArmour->ustModelID[i][0][1] = iValue;
            pItemArmour->ustModelID[i][1][0] = iValue;
            pItemArmour->ustModelID[i][1][1] = iValue;
        }

        //װ������ǿ���ж�
        SLK_GET_STRING( strValue, "IntensifyType");
        if ( !strValue.empty())
        {
            iValue = HelperFunc::GetIDByConstString( (char*)strValue.c_str(),ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );

            if( -1 == iValue )
                iValue = 1;
            pItemArmour->stTypeForInGem = iValue;
        }

        //�������
        SLK_GET_FLOAT( pItemArmour->defendPhysics, "PhysicsDefend");

        ////Զ�̷���
        //SLK_GET_FLOAT( pItemArmour->defendLong, "LongDefend");

        //ħ������
        SLK_GET_FLOAT( pItemArmour->defendMagic, "MagicDefend");

		//HP
		SLK_GET_INT( pItemArmour->Hp, "HP" );
		//MP
		SLK_GET_INT( pItemArmour->Mp, "MP" );

        int iTemp;
        int iArmourValue, iGloveValue, iShoeValue, iCapValue;

        iTemp = HelperFunc::GetIDByConstString( "armour",
            ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
        iArmourValue = 1;
        iArmourValue <<= iTemp;

        iTemp = HelperFunc::GetIDByConstString( "glove",
            ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
        iGloveValue = 1;
        iGloveValue <<= iTemp;

        iTemp = HelperFunc::GetIDByConstString( "shoe",
            ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
        iShoeValue = 1;
        iShoeValue <<= iTemp;

        iTemp = HelperFunc::GetIDByConstString( "helmet",
            ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
        iCapValue = 1;
        iCapValue <<= iTemp;

        if(pItemArmour->ustEquipType==iArmourValue)
        {
            m_vecArmourItem.push_back(pItemArmour);
        }
        if(pItemArmour->ustEquipType==iGloveValue)
        {
            m_vecGloveItem.push_back(pItemArmour);
        }
        if(pItemArmour->ustEquipType==iShoeValue)
        {
            m_vecShoeItem.push_back(pItemArmour);
        }
        if(pItemArmour->ustEquipType==iCapValue)
        {
            m_vecCapItem.push_back(pItemArmour);
        }
    }

    return true;

}


//װ�����������ͷ���
bool CItemDetailConfig::LoadEquipmentItem  ( MeXmlDocument *pXmlDoc, int mode )
{
    if ( pXmlDoc == NULL )
    { return false; }

    MeXmlElement *pRoot = pXmlDoc->FirstChildElement("Project");
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement *pItemsTree = pRoot->FirstChildElement("Items");
    if( pItemsTree == NULL )
    { return false; }

    MeXmlElement *pItemsType = pItemsTree->FirstChildElement("Type");
    if( pItemsType == NULL )
    { return false; }

    MeXmlElement *pItemElement = pItemsType->FirstChildElement("Item");
    if( pItemElement == NULL )
    { return false; }

    int iValue = -1;
    double dValue = 0.0F;

    while ( pItemElement != NULL )
    {
        int itemId = 0;
        pItemElement->Attribute("Id", &itemId);

        ItemDefine::SItemCanEquip *pEquipment = NULL;

        Common::_tstring strItemType;
        strItemType.fromUTF8( pItemElement->Attribute("ItemType") );
        bool isWeaponEquip = (strItemType.MakeLower() == "weapon" );

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            if (isWeaponEquip)
            { pEquipment =  (ItemDefine::SItemWeapon*)GetItemByID(itemId); }
            else
            { pEquipment =  (ItemDefine::SItemArmour*)GetItemByID(itemId); }
        }

        if ( NULL == pEquipment )
        {
            if (isWeaponEquip)
            { pEquipment =  (ItemDefine::SItemWeapon*)AllocItem( 0, sizeof( ItemDefine::SItemWeapon ) ); }
            else
            { pEquipment =  (ItemDefine::SItemArmour*)AllocItem( 0, sizeof( ItemDefine::SItemArmour ) ); }
        }

        if( !pEquipment )
        {
            OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
            GetErrorLog()->logString( "Error:�ڴ�������!" );
            return false;    
        }

        pEquipment->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pEquipment->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "���ݴ� ItemType��"  );
            return false;
        }

        pEquipment->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pEquipment->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pEquipment->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pEquipment->byUserTarget = iValue;

        //�����������
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pEquipment->ustLevel = iValue;

        pEquipment->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pEquipment->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pEquipment->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pEquipment->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pEquipment->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pEquipment->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pEquipment->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pEquipment->nStackNum = iValue;

        //���ؼ۸�����
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pEquipment->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pEquipment->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pEquipment->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pEquipment->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pEquipment->dwSpecialCost = iValue;

        //���ز�������
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pEquipment->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pEquipment->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pEquipment->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pEquipment->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pEquipment->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pEquipment->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pEquipment->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pEquipment->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pEquipment->bIsCanSplit = iValue;

        //������Ч����
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pEquipment->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pEquipment->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pEquipment->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pEquipment->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pEquipment->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pEquipment->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pEquipment->bCanSingingInterrupt = iValue;

        //������ֵ����
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pEquipment->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pEquipment->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pEquipment->nDropMaxCount = iValue;

        //////////////////////////////////////////////////////////////////////////
        //                      װ�����߹����ֶ�˵��
        //////////////////////////////////////////////////////////////////////////

        //����װ�����߹����������
        Common::_tstring strEquipType;
        strEquipType.fromUTF8( pAppearanceAttr->Attribute("EquipType") );
        if (isWeaponEquip)
        {
            pEquipment->ustEquipType = ItemDefine::equip_Weapon;
        }
        else
        {
            iValue = HelperFunc::GetIDByConstString( (char*)strEquipType.c_str(), 
				ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );

            if( -1 == iValue )
                iValue = 1;
            pEquipment->ustEquipType = 1;
            pEquipment->ustEquipType <<= iValue;
        }

        Common::_tstring strEquipPart;
        strEquipPart.fromUTF8( pAppearanceAttr->Attribute("CanEquipPart") );
        SetCanEquipByString( pEquipment->arrayCanEquip, strEquipPart.c_str() );

        pAppearanceAttr->Attribute("Common", &iValue);
        pEquipment->isCommon = iValue;

        Common::_tstring strSkin;
        strSkin.fromUTF8( pAppearanceAttr->Attribute("Skin") );
        pEquipment->dwReplaceSkinAddr = AllocStringCopy( strSkin.c_str() );

        pAppearanceAttr->Attribute("IsSpecular", &iValue);
        pEquipment->isSpecular = iValue;

        pAppearanceAttr->Attribute("IsCanDistortion", &iValue);
        pEquipment->isCanDistortion = iValue;

        for (int i=0; i<ItemDefine::SItemCanEquip::ECD_DistortionIdCount; ++i)
        {
            char szTmp[37] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "DistortionId%d", i+1);
            pAppearanceAttr->Attribute(szTmp, &iValue);
            pEquipment->arrayDistortionId[i] = iValue;
        }

        pAppearanceAttr->Attribute("IsFashion", &iValue);
        pEquipment->bFashion = iValue;

        //����װ�����߹�����Ч����
        Common::_tstring strSoundPrefix;
        strSoundPrefix.fromUTF8( pEffectAttr->Attribute("SoundPrefix") );
        pEquipment->dwSoundAddr = AllocStringCopy( strSoundPrefix.c_str() );

        //����װ�����߹���״̬���
        MeXmlElement *pStatusAttr = pItemElement->FirstChildElement("Status");

        pStatusAttr->Attribute("HitChanceOfStatusEnemy", &dValue);
        pEquipment->fStatusRate = dValue;

        pStatusAttr->Attribute("HitChanceOfStatusSelf", &dValue);
        pEquipment->fMyStatusRate = dValue;

        pStatusAttr->Attribute( "AdditionalStatusEnemy", &iValue );
        pEquipment->stAddStatus = iValue;

        pStatusAttr->Attribute( "StatusTriggerEnemy", &iValue );
        pEquipment->nAddStatusTrigger = iValue;

        pStatusAttr->Attribute("StatusLevelEnemy", &iValue);
        pEquipment->stAddStatusLevel = iValue;

        pStatusAttr->Attribute("AdditionalStatusSelf", &iValue);
        pEquipment->stMyAddStatus = iValue;

        pStatusAttr->Attribute("StatusLevelSelf", &iValue);
        pEquipment->stMyAddStatusLevel = iValue;

        pStatusAttr->Attribute( "StatusTriggerSelf", &iValue );
        pEquipment->nMyAddStatusTrigger = iValue;

        //����װ�����߹�����������
        MeXmlElement *pRequirementAttr = pItemElement->FirstChildElement("Requirement");

        Common::_tstring strGenderNeed;
        strGenderNeed.fromUTF8(pRequirementAttr->Attribute("SexNeed"));
        pEquipment->cEquipSexReq = HelperFunc::GetIDByConstString( (char*)strGenderNeed.c_str() ,
			ItemDefine::g_szSexType,sizeof( ItemDefine::g_szSexType )/sizeof(char*) );

        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        {
            pEquipment->arrayEquipArmsReq[ iLoop ] = false;
        }
        Common::_tstring strArmsNeed;
        strArmsNeed.fromUTF8( pRequirementAttr->Attribute("ArmsNeed") );
        if ( strArmsNeed.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pEquipment->arrayEquipArmsReq[ iLoop ] = true;
            }
        }
        else
        {  
            //���ö��ְҵ
            char *szSpn = " ,";
            char *szStr;
            int iEquip;
            szStr = strtok( const_cast<char*>(strArmsNeed.c_str()),szSpn );
            while( szStr )
            {             
                iEquip = HelperFunc::GetIDByConstString( szStr, 
					ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iEquip >= 0 && iEquip < EArmType_MaxSize )
                {
                    pEquipment->arrayEquipArmsReq[ iEquip ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        pRequirementAttr->Attribute("LevelNeed", &iValue);
        pEquipment->stEquipLevelReq = iValue;

        pRequirementAttr->Attribute("PKValueNeed", &iValue);
        pEquipment->nPkValueNeed = iValue;

        pRequirementAttr->Attribute("TitleNeed", &iValue);
        pEquipment->nTitleNeed = iValue;

        //����װ�����߹�����������
        MeXmlElement *pSkillAttr = pItemElement->FirstChildElement("Skill");

        pSkillAttr->Attribute("skillId", &iValue);
        pEquipment->skillId = iValue;

        pSkillAttr->Attribute("skillLevel", &iValue);
        pEquipment->skillLevel = iValue;

        //����װ�����߹���ά������
        MeXmlElement *pRepairAttr = pItemElement->FirstChildElement("Repair");

        pRepairAttr->Attribute("RepairType", &iValue);
        pEquipment->uchRepairType = iValue;

        pRepairAttr->Attribute("RepairValue", &iValue);
        pEquipment->nRepairValue = iValue;

        pRepairAttr->Attribute("RepairPrice", &iValue);
        pEquipment->stRepairPrice = iValue;

        pRepairAttr->Attribute("Durability", &iValue);
        pEquipment->stHPMax = iValue;

        //����װ�����߹�����������
        MeXmlElement *pAttackAttr = pItemElement->FirstChildElement("Attack");

        pAttackAttr->Attribute("PhysicsAttack", &iValue);
        pEquipment->attackPhysics = iValue;

        pAttackAttr->Attribute("MagicAttack", &iValue);
        pEquipment->attackMagic = iValue;

        pAttackAttr->Attribute("AttackSpeed", &iValue);
        pEquipment->attackSpeed = iValue;

        pAttackAttr->Attribute("Exact", &iValue);
        pEquipment->exact = iValue;

        pAttackAttr->Attribute("Dodge", &iValue);
        pEquipment->dodge = iValue;

        pAttackAttr->Attribute("Critical", &iValue);
        pEquipment->critical = iValue;

        pAttackAttr->Attribute("Tenacity", &iValue);
        pEquipment->tenacity = iValue;

		//Ԫ������
		pAttackAttr->Attribute("BreakStrike", &iValue);
		pEquipment->breakStrike = iValue;
		pAttackAttr->Attribute("BreakResist", &iValue);
		pEquipment->breakResist = iValue;
		pAttackAttr->Attribute("StabStrike", &iValue);
		pEquipment->stabStrike = iValue;
		pAttackAttr->Attribute("StabResist", &iValue);
		pEquipment->stabResist = iValue;
		pAttackAttr->Attribute("ElementStrike", &iValue);
		pEquipment->elementStrike = iValue;
		pAttackAttr->Attribute("ElementResist", &iValue);
		pEquipment->elementResist = iValue;
		pAttackAttr->Attribute("ToxinStrike", &iValue);
		pEquipment->toxinStrike = iValue;
		pAttackAttr->Attribute("ToxinResist", &iValue);
		pEquipment->toxinResist = iValue;
		pAttackAttr->Attribute("SpiritStrike", &iValue);
		pEquipment->spiritStrike = iValue;
		pAttackAttr->Attribute("SpiritResist", &iValue);
		pEquipment->spiritResist = iValue;

        //����װ�����߹����������
        MeXmlElement *pAdditiveRandAttr = pItemElement->FirstChildElement("AdditiveRand");

//modified by junyi.chen begin
//         pAdditiveRandAttr->Attribute("AdditiveRandCount", &iValue);
//         pEquipment->additiveRandCount = iValue;
		pAdditiveRandAttr->Attribute("RandWhenCreate",&iValue);
		pEquipment->bRandWhenCreate = iValue;

		for ( int i=0; i< ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
		{
			pEquipment->additiveRandCountRates[i]  = 0;
		}
		Common::_tstring strAdditiveCount;
		strAdditiveCount.fromUTF8(pAdditiveRandAttr->Attribute("AdditiveCountRate"));
		if ( !strAdditiveCount.empty())
		{   
			char *szSpn = ",";
			char *szStr;
			int i = 0;

			szStr = strtok( const_cast<char*>(strAdditiveCount.c_str()),szSpn );
			while( szStr )
			{
				if ( atoi(szStr) > 0 )
				{
					pEquipment->additiveRandCountRates[i] = atoi(szStr);
				}
				szStr = strtok( NULL,szSpn );
				++i;
			}
		}
//end
        for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
        {
            pEquipment->additiveRandFlags[i]  = 0;
//modified by junyi.chen begin
//            pEquipment->additiveRandValues[i] = 0;
//end
        }
        Common::_tstring strAdditiveTag;
        strAdditiveTag.fromUTF8(pAdditiveRandAttr->Attribute("AdditiveRandFlags"));
        if ( !strAdditiveTag.empty())
        {   
            char *szSpn = ",";
            char *szStr;
            int i = 0;

            szStr = strtok( const_cast<char*>(strAdditiveTag.c_str()),szSpn );
            while( szStr )
            {
                if ( atoi(szStr) > 0 )
                {
                    pEquipment->additiveRandFlags[i] = atoi(szStr);
                }
                szStr = strtok( NULL,szSpn );
                ++i;
            }
        }
//modified by junyi.chen begin
//         for ( int i=0; i<SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
//         {
//             char szTmp[65] = { 0 };
//             sprintf_s(szTmp, sizeof(szTmp) - 1, "AdditiveRandValue%d",i+1);
//             pAdditiveRandAttr->Attribute(szTmp, &iValue);
//             pEquipment->additiveRandValues[i] = iValue;
//         }
		pAdditiveRandAttr->Attribute("AdditiveRandLvLowerLimit",&iValue);
		pEquipment->additiveRandLvLowerLimit = iValue;

		pAdditiveRandAttr->Attribute("AdditiveRandLvUpperLimit",&iValue);
		pEquipment->additiveRandLvUpperLimit = iValue;

		for ( int i = 0; i < pEquipment->typeFilter.GetSize(); ++i )
		{
			pEquipment->typeFilter[i] = 0;
		}
		Common::_tstring strAdditiveTypeFilter;
		strAdditiveTypeFilter.fromUTF8(pAdditiveRandAttr->Attribute("TypeFilter"));
		if ( !strAdditiveTypeFilter.empty())
		{   
			char *szSpn = ",";
			char *szStr;
			int i = 0;

			szStr = strtok( const_cast<char*>(strAdditiveTypeFilter.c_str()),szSpn );
			while( szStr )
			{
				if ( atoi(szStr) > 0 )
				{
					pEquipment->typeFilter[i] = atoi(szStr);
				}
				szStr = strtok( NULL,szSpn );
				++i;
			}
		}
//end
		/*for ( int i = 0; i < pEquipment->typeFilter_hero.GetSize(); ++i )
		{
			pEquipment->typeFilter_hero[i] = 0;
		}
		Common::_tstring strAdditiveTypeFilter_Hero;
		strAdditiveTypeFilter_Hero.fromUTF8(pAdditiveRandAttr->Attribute("TypeFilter_Hero"));
		if ( !strAdditiveTypeFilter_Hero.empty())
		{   
			char *szSpn = ",";
			char *szStr;
			int i = 0;

			szStr = strtok( const_cast<char*>(strAdditiveTypeFilter_Hero.c_str()),szSpn );
			while( szStr )
			{
				if ( atoi(szStr) > 0 )
				{
					pEquipment->typeFilter_hero[i] = atoi(szStr);
				}
				szStr = strtok( NULL,szSpn );
				++i;
			}
		}*/
		//end

        //����װ�����߹�����ɫ�������
        MeXmlElement *pPurpleRandAttr = pItemElement->FirstChildElement("PurpleRand");

        pPurpleRandAttr->Attribute("PurpleRandCount", &iValue);
        pEquipment->purpleRandCount = iValue;

        for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++i)
        {
            pEquipment->purpleRandFlags[i]  = 0;
            pEquipment->purpleRandValues[i] = 0;
        }

        Common::_tstring strPurpleTag;
        strPurpleTag.fromUTF8(pPurpleRandAttr->Attribute("PurpleRandFlags"));
        if ( !strPurpleTag.empty())
        {   
            char *szSpn = ",";
            char *szStr;
            int i = 0;

            szStr = strtok( const_cast<char*>(strPurpleTag.c_str()),szSpn );
            while( szStr )
            {
                if ( atoi(szStr) > 0 )
                {
                    pEquipment->purpleRandFlags[i] = atoi(szStr);
                }
                szStr = strtok( NULL,szSpn );
                ++i;
            }
        }

        for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "PurpleRandValue%d",i+1);
            pPurpleRandAttr->Attribute(szTmp, &iValue);
            pEquipment->purpleRandValues[i] = iValue;
        }

        //��װ����
        MeXmlElement *pSuitAttr = pItemElement->FirstChildElement("Suit");

        pSuitAttr->Attribute("SuitNum", &iValue);
        pEquipment->sPartCount = iValue;

        pSuitAttr->Attribute("SuitID", &iValue);
        pEquipment->sSuitID = iValue;

        pSuitAttr->Attribute("IsElements", &iValue);
        pEquipment->bIsElements = iValue;

		pSuitAttr->Attribute("HeroID", &iValue);
		pEquipment->nHeroID = iValue;

		//��ֵ�����ļ���װ�����Ĵ���
		pSuitAttr->Attribute("UnBindCount", &iValue);
		pEquipment->unBindCount = iValue;//Ĭ��ֵΪ0

        //////////////////////////////////////////////////////////////////////////
        //  �ֱ���� �����ͷ��ߵ�����
        //////////////////////////////////////////////////////////////////////////

        if ( pEquipment->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
        {//����

            ItemDefine::SItemWeapon *pWeapon = (ItemDefine::SItemWeapon *)pEquipment;

            //�������
            pAppearanceAttr->Attribute("LeftHandModelID", &iValue);
            pWeapon->ustModelID[0] = iValue;

            pAppearanceAttr->Attribute("RightHandModelID", &iValue);
            pWeapon->ustModelID[1] = iValue;

            pAppearanceAttr->Attribute("TakeBackID", &iValue);
            pWeapon->ustIdleModelID = iValue;

            pAppearanceAttr->Attribute("IfDoubleWeapon", &iValue);
            pWeapon->bTwoHandWeapon = iValue;

            //��Ч����
            pEffectAttr->Attribute("LaunchEffectId", &iValue);
            pWeapon->iShotEffectID = iValue;

            //��������
            Common::_tstring weaponType;
            weaponType.fromUTF8( pAttackAttr->Attribute("WeaponType") );
            pWeapon->stWeaponType =  GetIDByConstString( weaponType.c_str(),ItemDefine::g_szWeaponType,sizeof(ItemDefine::g_szWeaponType)/sizeof(char*) );

            pAttackAttr->Attribute("WeaponSwingSpeed", &dValue);
            pWeapon->fWeaponAttackRate = dValue;

            pAttackAttr->Attribute("IfDoubleWeapon", &iValue);
            pWeapon->bTwoHandWeapon = iValue;

            pAttackAttr->Attribute("AttackRange", &dValue);
            pWeapon->fAtkRange = dValue;



            AddItemToContainer(pWeapon);
            m_vecWeaponItem.push_back( pWeapon );

        }
        else
        {//����

            ItemDefine::SItemArmour *pArmour = (ItemDefine::SItemArmour *)pEquipment;

            //�������
            pAppearanceAttr->Attribute("Ifcloth", &iValue);
            pArmour->isCape = iValue;

            pAppearanceAttr->Attribute("Ifheadwear", &iValue);
            pArmour->isHeadWear = iValue;

            pAppearanceAttr->Attribute("ModelID", &iValue);
            for( int i=0;i<EArmType_MaxSize;i++ )
            {            
                pArmour->ustModelID[i][0][0] = iValue;
                pArmour->ustModelID[i][0][1] = iValue;
                pArmour->ustModelID[i][1][0] = iValue;
                pArmour->ustModelID[i][1][1] = iValue;
            }

            Common::_tstring strIntensifyType;
            strIntensifyType.fromUTF8( pAppearanceAttr->Attribute("IntensifyType") );
            if ( !strIntensifyType.empty())
            {
                iValue = HelperFunc::GetIDByConstString( (char*)strIntensifyType.c_str(),ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );

                if( -1 == iValue )
                    iValue = 1;
                pArmour->stTypeForInGem = iValue;
            }

            //��������
            MeXmlElement *pDefendAttr = pItemElement->FirstChildElement("Defend");

            pDefendAttr->Attribute("PhysicsDefend", &dValue);
            pArmour->defendPhysics = dValue;

            pDefendAttr->Attribute("MagicDefend", &dValue);
            pArmour->defendMagic = dValue;

			pDefendAttr->Attribute("HP", &dValue);
			pArmour->Hp = dValue;
			pDefendAttr->Attribute("MP", &dValue);
			pArmour->Mp = dValue;

            int iTemp;
            int iArmourValue, iGloveValue, iShoeValue, iCapValue;

            iTemp = HelperFunc::GetIDByConstString( "armour",
                ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
            iArmourValue = 1;
            iArmourValue <<= iTemp;

            iTemp = HelperFunc::GetIDByConstString( "glove",
                ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
            iGloveValue = 1;
            iGloveValue <<= iTemp;

            iTemp = HelperFunc::GetIDByConstString( "shoe",
                ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
            iShoeValue = 1;
            iShoeValue <<= iTemp;

            iTemp = HelperFunc::GetIDByConstString( "helmet",
                ItemDefine::g_szEquipType, sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
            iCapValue = 1;
            iCapValue <<= iTemp;

            if(pArmour->ustEquipType==iArmourValue)
            {
                m_vecArmourItem.push_back(pArmour);
            }
            if(pArmour->ustEquipType==iGloveValue)
            {
                m_vecGloveItem.push_back(pArmour);
            }
            if(pArmour->ustEquipType==iShoeValue)
            {
                m_vecShoeItem.push_back(pArmour);
            }
            if(pArmour->ustEquipType==iCapValue)
            {
                m_vecCapItem.push_back(pArmour);
            }

            AddItemToContainer(pArmour);

        }

        pItemElement = pItemElement->NextSiblingElement();
    }

    return true;
}


bool CItemDetailConfig::SaveEquipmentItem   ( const char *szFileName )//+����װ��
{
    if (szFileName == NULL )
    { return false; }

    MeXmlDocument MeXmlDoc;
    MeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = MeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pItems = pRoot->InsertEndChild(("Items"))->ToElement();
    if (pItems == NULL)
    { return false; }

    MeXmlElement *pEquipmentType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pEquipmentType == NULL)
    { return false; }

    pEquipmentType->SetAttribute("Id", ItemDefine::ITEMTYPE_WEAPON);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL || !(*iterBegin)->IsCanEquip() )
        { continue; }

        ItemDefine::SItemCanEquip *pEquipmentIter = (ItemDefine::SItemCanEquip *)*iterBegin;

        MeXmlElement *pItem = pEquipmentType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pEquipmentIter->ustItemID);
        Common::_tstring strName = pEquipmentIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pEquipmentIter->ucItemType]);
        Common::_tstring strDescription = pEquipmentIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pEquipmentIter->nUseTime);
        pItem->SetAttribute("UserTarget", pEquipmentIter->byUserTarget);


        //�������
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pEquipmentIter->ustLevel);
        pAppearance->SetAttribute("Rare", pEquipmentIter->cItemClass);
        pAppearance->SetAttribute("Weight", pEquipmentIter->fWeight);
        pAppearance->SetAttribute("IconID", pEquipmentIter->ustIconId);
        Common::_tstring strIconFile = pEquipmentIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pEquipmentIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pEquipmentIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pEquipmentIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pEquipmentIter->nStackNum);

        int index = -1;
        for ( int i=0; i<sizeof(pEquipmentIter->ustEquipType)*8; ++i)
        {
            if ( pEquipmentIter->ustEquipType >> i & 1)
            {
                index = i;
                break;
            }
        }
        if ( index != -1 )
        {
            pAppearance->SetAttribute("EquipType", ItemDefine::g_szEquipType[index]);//װ������
        }
        int nEquipIndex = pEquipmentIter->GetCanEquipIndex();
        pAppearance->SetAttribute("CanEquipPart", ItemDefine::g_szCanEquip[nEquipIndex] );
        pAppearance->SetAttribute("Common", pEquipmentIter->IsCommon());
        Common::_tstring strSkin = pEquipmentIter->GetReplaceSkin();
        pAppearance->SetAttribute("Skin", strSkin.toUTF8().c_str() );
        pAppearance->SetAttribute("IsSpecular", pEquipmentIter->IsSpecular());
        pAppearance->SetAttribute("IsCanDistortion", pEquipmentIter->isCanDistortion);
        for (int i=0; i<ItemDefine::SItemCanEquip::ECD_DistortionIdCount; ++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp), "DistortionId%d", i+1);
            pAppearance->SetAttribute( szTmp, pEquipmentIter->arrayDistortionId[i] );
        }
        pAppearance->SetAttribute("IsFashion", pEquipmentIter->bFashion);


        //�۸�����
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pEquipmentIter->nBill);
        pPrice->SetAttribute("CostType", pEquipmentIter->costType);
        pPrice->SetAttribute("Cost", pEquipmentIter->dwCost);
        pPrice->SetAttribute("CostItemID", pEquipmentIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pEquipmentIter->dwSpecialCost);

        //��������
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pEquipmentIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pEquipmentIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pEquipmentIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pEquipmentIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pEquipmentIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pEquipmentIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pEquipmentIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pEquipmentIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pEquipmentIter->bIsCanSplit);

        //��Ч����
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pEquipmentIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pEquipmentIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pEquipmentIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pEquipmentIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pEquipmentIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pEquipmentIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pEquipmentIter->bCanSingingInterrupt);

        Common::_tstring strSoundPrefix = pEquipmentIter->GetSound();
        pEffect->SetAttribute("SoundPrefix", strSoundPrefix.c_str());

        //��ֵ����
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pEquipmentIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pEquipmentIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pEquipmentIter->nDropMaxCount);


        //״̬���
        MeXmlElement *pStatus = pItem->InsertEndChild(("Status"))->ToElement();
        if (pStatus == NULL)
        { continue; }

        pStatus->SetDoubleAttribute("HitChanceOfStatusEnemy", pEquipmentIter->fStatusRate);
        pStatus->SetDoubleAttribute("HitChanceOfStatusSelf", pEquipmentIter->fMyStatusRate);
        pStatus->SetAttribute("AdditionalStatusEnemy", pEquipmentIter->stAddStatus);
        pStatus->SetAttribute("StatusLevelEnemy", pEquipmentIter->stAddStatusLevel);
        pStatus->SetAttribute("StatusTriggerEnemy", pEquipmentIter->nAddStatusTrigger);
        pStatus->SetAttribute("AdditionalStatusSelf", pEquipmentIter->stMyAddStatus);
        pStatus->SetAttribute("StatusLevelSelf", pEquipmentIter->stMyAddStatusLevel);
        pStatus->SetAttribute("StatusTriggerSelf", pEquipmentIter->nMyAddStatusTrigger);

        //��������
        MeXmlElement *pRequirement = pItem->InsertEndChild(("Requirement"))->ToElement();
        if (pRequirement == NULL)
        { continue; }

        if(pEquipmentIter->cEquipSexReq == -1)
        { pRequirement->SetAttribute("SexNeed",""); }
        else
        { pRequirement->SetAttribute("SexNeed", ItemDefine::g_szSexType[pEquipmentIter->cEquipSexReq]); }

        Common::_tstring strArmsNeed;
        Common::_tstring strSpn = ",";
        for (int i=0; i<EArmType_MaxSize; ++i)
        {
            if (pEquipmentIter->arrayEquipArmsReq[i] == true)
            {
                strArmsNeed = strArmsNeed + string(ItemDefine::g_szProfessionType[i]);
                strArmsNeed = strArmsNeed + strSpn ;
            }
        } 
        pRequirement->SetAttribute("ArmsNeed" , strArmsNeed.substr(0,strArmsNeed.length() - 1).c_str());
        pRequirement->SetAttribute("LevelNeed", pEquipmentIter->stEquipLevelReq);
        pRequirement->SetAttribute("PKValueNeed", pEquipmentIter->nPkValueNeed);
        pRequirement->SetAttribute("TitleNeed", pEquipmentIter->nTitleNeed);

        //��������
        MeXmlElement *pSkill = pItem->InsertEndChild(("Skill"))->ToElement();
        if (pSkill == NULL)
        { continue; }

        pSkill->SetAttribute("skillId", pEquipmentIter->skillId);
        pSkill->SetAttribute("skillLevel", pEquipmentIter->skillLevel);

        //ά������
        MeXmlElement *pRepair = pItem->InsertEndChild(("Repair"))->ToElement();
        if (pRepair == NULL)
        { continue; }

        pRepair->SetAttribute("RepairType", pEquipmentIter->uchRepairType);
        pRepair->SetAttribute("RepairValue", pEquipmentIter->nRepairValue);
        pRepair->SetAttribute("RepairPrice", pEquipmentIter->stRepairPrice);
        pRepair->SetAttribute("Durability", pEquipmentIter->stHPMax);

        //��������
        MeXmlElement *pAttack = pItem->InsertEndChild(("Attack"))->ToElement();
        if (pAttack == NULL)
        { continue; }

        pAttack->SetDoubleAttribute("PhysicsAttack", pEquipmentIter->attackPhysics);
        pAttack->SetDoubleAttribute("MagicAttack", pEquipmentIter->attackMagic);
        pAttack->SetDoubleAttribute("AttackSpeed", pEquipmentIter->attackSpeed);
        pAttack->SetDoubleAttribute("Exact", pEquipmentIter->exact);
        pAttack->SetDoubleAttribute("Dodge", pEquipmentIter->dodge);
        pAttack->SetDoubleAttribute("Critical", pEquipmentIter->critical);
        pAttack->SetDoubleAttribute("Tenacity", pEquipmentIter->tenacity);
		//Ԫ������
		pAttack->SetDoubleAttribute("BreakStrike", pEquipmentIter->breakStrike);
		pAttack->SetDoubleAttribute("BreakResist", pEquipmentIter->breakResist);
		pAttack->SetDoubleAttribute("StabStrike", pEquipmentIter->stabStrike);
		pAttack->SetDoubleAttribute("StabResist", pEquipmentIter->stabResist);
		pAttack->SetDoubleAttribute("ElementStrike", pEquipmentIter->elementStrike);
		pAttack->SetDoubleAttribute("ElementResist", pEquipmentIter->elementResist);
		pAttack->SetDoubleAttribute("ToxinStrike", pEquipmentIter->toxinStrike);
		pAttack->SetDoubleAttribute("ToxinResist", pEquipmentIter->toxinResist);
		pAttack->SetDoubleAttribute("SpiritStrike", pEquipmentIter->spiritStrike);
		pAttack->SetDoubleAttribute("SpiritResist", pEquipmentIter->spiritResist);
        
        //��ɫ�����������
        MeXmlElement *pPurpleRand = pItem->InsertEndChild(("PurpleRand"))->ToElement();
        if (pPurpleRand == NULL)
        { continue; }

        char szVal[8];

        pPurpleRand->SetAttribute("PurpleRandCount", pEquipmentIter->purpleRandCount);

        Common::_tstring strPurpleRandFlags;
        for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++i)
        {
            sprintf_s(szVal,sizeof(szVal),"%d",pEquipmentIter->purpleRandFlags[i]);
            if(i == (ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount - 1))
                strPurpleRandFlags = strPurpleRandFlags + string(szVal);
            else
                strPurpleRandFlags = strPurpleRandFlags + string(szVal) +",";
        }
        pPurpleRand->SetAttribute("PurpleRandFlags", strPurpleRandFlags.c_str());

        for (int i=0;i<ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount;++i)
        {
            char szTmp[65] = {0};
            sprintf_s(szTmp, sizeof(szTmp) - 1, "PurpleRandValue%d", i+1);
            pPurpleRand->SetAttribute(szTmp, pEquipmentIter->purpleRandValues[i]);
        }

        //�������
        MeXmlElement *pAdditiveRand = pItem->InsertEndChild(("AdditiveRand"))->ToElement();
        if (pAdditiveRand == NULL)
        { continue; }
//modified by junyi.chen begin
//        pAdditiveRand->SetAttribute("AdditiveRandCount", pEquipmentIter->additiveRandCount);
		pAdditiveRand->SetAttribute("RandWhenCreate",pEquipmentIter->bRandWhenCreate);

		Common::_tstring strAdditiveRandCountRates;
		for ( int i=0; i< ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
		{
			sprintf_s(szVal, sizeof(szVal), "%d", pEquipmentIter->additiveRandCountRates[i]);
			if( i == (ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - 1) )
				strAdditiveRandCountRates = strAdditiveRandCountRates + string(szVal);
			else
				strAdditiveRandCountRates = strAdditiveRandCountRates + string(szVal) +",";
		}
		pAdditiveRand->SetAttribute("AdditiveCountRate", strAdditiveRandCountRates.c_str());

		pAdditiveRand->SetAttribute("AdditiveRandLvLowerLimit",pEquipmentIter->additiveRandLvLowerLimit);

		pAdditiveRand->SetAttribute("AdditiveRandLvUpperLimit",pEquipmentIter->additiveRandLvUpperLimit);

		Common::_tstring strAdditiveTypeFilter;
		for ( int i=0; i< pEquipmentIter->typeFilter.GetSize(); ++i)
		{
			sprintf_s(szVal, sizeof(szVal), "%d", pEquipmentIter->typeFilter[i]);
			if( i == (pEquipmentIter->typeFilter.GetSize() - 1) )
				strAdditiveTypeFilter = strAdditiveTypeFilter + string(szVal);
			else
				strAdditiveTypeFilter = strAdditiveTypeFilter + string(szVal) +",";
		}
		pAdditiveRand->SetAttribute("TypeFilter", strAdditiveTypeFilter.c_str());
//end
		/*Common::_tstring strAdditiveTypeFilter_Hero;
		for ( int i=0; i< pEquipmentIter->typeFilter_hero.GetSize(); ++i)
		{
			sprintf_s(szVal, sizeof(szVal), "%d", pEquipmentIter->typeFilter_hero[i]);
			if( i == (pEquipmentIter->typeFilter_hero.GetSize() - 1) )
				strAdditiveTypeFilter_Hero = strAdditiveTypeFilter_Hero + string(szVal);
			else
				strAdditiveTypeFilter_Hero = strAdditiveTypeFilter_Hero + string(szVal) +",";
		}
		pAdditiveRand->SetAttribute("TypeFilter_Hero", strAdditiveTypeFilter_Hero.c_str());*/
		//end
        Common::_tstring strAdditiveRandFlags;
        for ( int i=0; i<ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i)
        {
            sprintf_s(szVal,sizeof(szVal),"%d",pEquipmentIter->additiveRandFlags[i]);
            if(i == (ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - 1))
                strAdditiveRandFlags = strAdditiveRandFlags + string(szVal);
            else
                strAdditiveRandFlags = strAdditiveRandFlags + string(szVal) +",";
        }
        pAdditiveRand->SetAttribute("AdditiveRandFlags", strAdditiveRandFlags.c_str());
//modified by junyi.chen begin
//         for (int i=0;i<SItemCanEquip::ECD_AdditiveRandAttrCount;++i)
//         {
//             char szTmp[65] = {0};
//             sprintf_s(szTmp, sizeof(szTmp) - 1, "AdditiveRandValue%d", i+1);
//             pAdditiveRand->SetAttribute(szTmp, pEquipmentIter->additiveRandValues[i]);
//         }
//end
        //��װ����
        MeXmlElement *pSuit = pItem->InsertEndChild(("Suit"))->ToElement();
        if (pSuit == NULL)
        { continue; }

        pSuit->SetAttribute("SuitNum", pEquipmentIter->sPartCount);
        pSuit->SetAttribute("SuitID", pEquipmentIter->sSuitID);
        pSuit->SetAttribute("IsElements", pEquipmentIter->bIsElements);
		pSuit->SetAttribute("HeroID", pEquipmentIter->nHeroID);
		pSuit->SetAttribute("UnBindCount",pEquipmentIter->unBindCount);
        //////////////////////////////////////////////////////////////////////////

        if ( (*iterBegin)->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
        {

            ItemDefine::SItemWeapon *pWeaponIter = (ItemDefine::SItemWeapon *)*iterBegin;

            //�������
            pAppearance->SetAttribute("LeftHandModelID", pWeaponIter->ustModelID[0]);
            pAppearance->SetAttribute("RightHandModelID", pWeaponIter->ustModelID[1]);
            pAppearance->SetAttribute("TakeBackID", pWeaponIter->ustIdleModelID);
            pAppearance->SetAttribute("IfDoubleWeapon", pWeaponIter->bTwoHandWeapon);

            //��Ч����
            pEffect->SetAttribute("LaunchEffectId", pWeaponIter->iShotEffectID);

            //��������
            pAttack->SetAttribute("WeaponType", ItemDefine::g_szWeaponType[pWeaponIter->stWeaponType]);
            pAttack->SetDoubleAttribute("WeaponSwingSpeed", pWeaponIter->fWeaponAttackRate);
            pAttack->SetDoubleAttribute("AttackRange", pWeaponIter->fAtkRange);

        }
        else
        {
            ItemDefine::SItemArmour *pArmourIter = (ItemDefine::SItemArmour *)*iterBegin;

            //�������
            pAppearance->SetAttribute("Ifcloth", pArmourIter->IsCape());        //�Ƿ�Ϊ����
            pAppearance->SetAttribute("Ifheadwear", pArmourIter->isHeadWear);   //�Ƿ�Ϊͷ��
            pAppearance->SetAttribute("IntensifyType", ItemDefine::g_szEquipType[pArmourIter->stTypeForInGem]); //ǿ�������ж�
            pAppearance->SetAttribute("ModelID", pArmourIter->ustModelID[0][0][0]); //ģ��ID �����ڶ���ͬһֵ

            //��������
            MeXmlElement *pDefend = pItem->InsertEndChild(("Defend"))->ToElement();
            if (pDefend == NULL)
            { continue; }

            pDefend->SetDoubleAttribute("PhysicsDefend", pArmourIter->defendPhysics);
            pDefend->SetDoubleAttribute("MagicDefend", pArmourIter->defendMagic);

			pDefend->SetAttribute("HP", pArmourIter->Hp);
			pDefend->SetAttribute("MP", pArmourIter->Mp);

        }
    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )