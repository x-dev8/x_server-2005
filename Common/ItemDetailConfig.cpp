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

CItemDetailConfig::CItemDetailConfig()
{
    nReloadSignal = ConfigLoadMode_Normal;
    nSwitch       = -1;
}

CItemDetailConfig::~CItemDetailConfig()
{
    ClearItemDetailConfig();
}


//////////////////////////////////////////////////////////////////////////
//  ����������õ�XML�ļ���
//////////////////////////////////////////////////////////////////////////

bool CItemDetailConfig::SaveItemTypes      ( const char *szFileName )//+���� ��������
{
    if (szFileName == NULL)
    { return false; }

    MeXmlDocument ItemMeXml;
    ItemMeXml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
    MeXmlElement *pRoot = ItemMeXml.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pItemTypes = pRoot->InsertEndChild(("ItemTypes"))->ToElement();
    if (pItemTypes == NULL)
    { return false; }
    
    // �ָ�ҩƷ
    MeXmlElement *pRestoreType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pRestoreType == NULL)
    { return false; }

    Common::_tstring strValue = "";
    

    strValue = "�ָ������" ;
    pRestoreType->SetAttribute("Id", ItemDefine::ITEMTYPE_RESTORE);
    pRestoreType->SetAttribute("Value", "Restore");
    pRestoreType->SetAttribute("Description",strValue.toUTF8().c_str() );

    //�����ͷ��ߺϲ�Ϊװ��
    MeXmlElement *pEquipmentType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pEquipmentType == NULL)
    { return false; }
    
    strValue = "װ������߰��������ͷ���" ;
    pEquipmentType->SetAttribute("Id", ItemDefine::ITEMTYPE_WEAPON);
    pEquipmentType->SetAttribute("Value", "Equipment");
    pEquipmentType->SetAttribute("Description", strValue.toUTF8().c_str());

    //����
    MeXmlElement *pSkillType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pSkillType == NULL)
    { return false; }

    strValue = "��Ҽ���" ;
    pSkillType->SetAttribute("Id", ItemDefine::ITEMTYPE_SKILL);
    pSkillType->SetAttribute("Value", "Skill");
    pSkillType->SetAttribute("Description", strValue.toUTF8().c_str());

    //״̬
    MeXmlElement *pStatusType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pStatusType == NULL)
    { return false; }
    
    strValue = "���״̬" ;
    pStatusType->SetAttribute("Id", ItemDefine::ITEMTYPE_STATUS);
    pStatusType->SetAttribute("Value", "Status");
    pStatusType->SetAttribute("Description", strValue.toUTF8().c_str());
    
    //��Ϸ����
    MeXmlElement *pActionType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pActionType == NULL)
    { return false; }

    strValue = "��Ϸ��������" ;
    pActionType->SetAttribute("Id", ItemDefine::ITEMTYPE_ACTION);
    pActionType->SetAttribute("Value", "GameAction");
    pActionType->SetAttribute("Description", strValue.toUTF8().c_str());

    //ԭ��
    MeXmlElement *pMaterialType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pMaterialType == NULL)
    { return false; }

    strValue = "ԭ��" ;
    pMaterialType->SetAttribute("Id", ItemDefine::ITEMTYPE_MATERIAL);
    pMaterialType->SetAttribute("Value", "Material");
    pMaterialType->SetAttribute("Description", strValue.toUTF8().c_str());

    //��ʯ
    MeXmlElement *pGemType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pGemType == NULL)
    { return false; }

    strValue = "��ʯ" ;
    pGemType->SetAttribute("Id", ItemDefine::ITEMTYPE_GEM);
    pGemType->SetAttribute("Value", "Gem");
    pGemType->SetAttribute("Description", strValue.toUTF8().c_str());

    //�ϳ��䷽
    MeXmlElement *pRuleType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pRuleType == NULL)
    { return false; }

    strValue = "�ϳ��䷽" ;
    pRuleType->SetAttribute("Id", ItemDefine::ITEMTYPE_CREATEITEMRULE);
    pRuleType->SetAttribute("Value", "ItemRule");
    pRuleType->SetAttribute("Description", strValue.toUTF8().c_str());

    //�������
    MeXmlElement *pTaskType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pTaskType == NULL)
    { return false; }

    strValue = "�������" ;
    pTaskType->SetAttribute("Id", ItemDefine::ITEMTYPE_TASK);
    pTaskType->SetAttribute("Value", "Task");
    pTaskType->SetAttribute("Description", strValue.toUTF8().c_str());

    //����
    MeXmlElement *pOtherType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pOtherType == NULL)
    { return false; }

    strValue = "��������" ;
    pOtherType->SetAttribute("Id", ItemDefine::ITEMTYPE_OTHER);
    pOtherType->SetAttribute("Value", "Other");
    pOtherType->SetAttribute("Description", strValue.toUTF8().c_str());

    //����
    MeXmlElement *pReelType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pReelType == NULL)
    { return false; }

    strValue = "����" ;
    pReelType->SetAttribute("Id", ItemDefine::ITEMTYPE_REEL);
    pReelType->SetAttribute("Value", "Reel");
    pReelType->SetAttribute("Description", strValue.toUTF8().c_str());

    //����
    MeXmlElement *pBoxType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pBoxType == NULL)
    { return false; }

    strValue = "����" ;
    pBoxType->SetAttribute("Id", ItemDefine::ITEMTYPE_TREASUREBOX);
    pBoxType->SetAttribute("Value", "TreasureBox");
    pBoxType->SetAttribute("Description", strValue.toUTF8().c_str());

    //���������
    MeXmlElement *pCheckupType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pCheckupType == NULL)
    { return false; }

    strValue = "���������" ;
    pCheckupType->SetAttribute("Id", ItemDefine::ITEMTYPE_CHECKUP);
    pCheckupType->SetAttribute("Value", "CheckUp");
    pCheckupType->SetAttribute("Description", strValue.toUTF8().c_str());

    //������Ʒ��
    MeXmlElement *pRealAwardType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pRealAwardType == NULL)
    { return false; }

    strValue = "������Ʒ��( ��������, ������ )" ;
    pRealAwardType->SetAttribute("Id", ItemDefine::ITEMTYPE_REALAWARD);
    pRealAwardType->SetAttribute("Value", "RealAward");
    pRealAwardType->SetAttribute("Description", strValue.toUTF8().c_str());

    //���
    MeXmlElement *pGuildType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pGuildType == NULL)
    { return false; }

    strValue = "���ѹ��������İ�����" ;
    pGuildType->SetAttribute("Id", ItemDefine::ITEMTYPE_GUILD);
    pGuildType->SetAttribute("Value", "Guild");
    pGuildType->SetAttribute("Description", strValue.toUTF8().c_str());

    //������Ʒ
    MeXmlElement *pSpecialType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pSpecialType == NULL)
    { return false; }

    strValue = "������Ʒ" ;
    pSpecialType->SetAttribute("Id", ItemDefine::ITEMTYPE_SPECIAL);
    pSpecialType->SetAttribute("Value", "Special");
    pSpecialType->SetAttribute("Description", strValue.toUTF8().c_str());

    //������Ʒ
    MeXmlElement *pTalismanType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pTalismanType == NULL)
    { return false; }

    strValue = "����" ;
    pTalismanType->SetAttribute("Id", ItemDefine::ITEMTYPE_TALISMAN);
    pTalismanType->SetAttribute("Value", "Talisman");
    pTalismanType->SetAttribute("Description", strValue.toUTF8().c_str());

	//����װ��
	MeXmlElement *pPetEquipType = pItemTypes->InsertEndChild(("Type"))->ToElement();
    if (pPetEquipType == NULL)
    { return false; }

    strValue = "����װ��" ;
    pPetEquipType->SetAttribute("Id", ItemDefine::ITEMTYPE_PETEQUIP);
    pPetEquipType->SetAttribute("Value", "PetEquip");
    pPetEquipType->SetAttribute("Description", strValue.toUTF8().c_str());


    return ItemMeXml.SaveFile(szFileName);
}


bool CItemDetailConfig::LoadItemDetailConfig( const char *szPath , int mode )
{
    char szFileName[ MAX_PATH ] = {0};

    if ( mode == ConfigLoadMode_Reload )
    { ClearItemDetailConfig(); }

    //////////////////////////////////////////////////////////////////////////
    // ������
    MeXmlDocument MeXmlRestoreDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Restore.config" );
    if(!MeXmlRestoreDoc.LoadFile(szFileName))
    { return false; }
    
    if(!LoadRestoreItem(&MeXmlRestoreDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // װ����
    MeXmlDocument MeXmlEquipmentDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Equipment.config" );
    if(!MeXmlEquipmentDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadEquipmentItem(&MeXmlEquipmentDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ������
    MeXmlDocument MeXmlSkillDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Skill.config" );
    if(!MeXmlSkillDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadSkillItem(&MeXmlSkillDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ״̬��
    MeXmlDocument MeXmlStatusDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Status.config" );
    if(!MeXmlStatusDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadStatusItem(&MeXmlStatusDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ��Ϸ����
    MeXmlDocument MeXmlActionDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "GameAction.config" );
    if(!MeXmlActionDoc.LoadFile(szFileName)   )
    { return false; }

    if(!LoadActionItem(&MeXmlActionDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ������
    MeXmlDocument MeXmlMaterialDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Material.config" );
    if(!MeXmlMaterialDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadMaterialItem(&MeXmlMaterialDoc,mode))
    { return false; }

    ///////////////////////////////////////////////////////////////////////////
    // ��ʯ��
    MeXmlDocument MeXmlGemDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Gem.config" );
    if(!MeXmlGemDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadGemItem(&MeXmlGemDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // �������
    MeXmlDocument MeXmlTaskDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Task.config" );
    if(!MeXmlTaskDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadTaskItem(&MeXmlTaskDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ����
    MeXmlDocument MeXmlOtherDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Other.config" );
    if(!MeXmlOtherDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadOtherItem(&MeXmlOtherDoc,mode))
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    // ����
    MeXmlDocument MeXmlReelDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Reel.config" );
    if(!MeXmlReelDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadReelItem(&MeXmlReelDoc,mode))
    { return false; }

	//////////////////////////////////////////////////////////////////////////
	// Special
	MeXmlDocument MeXmlSpecialDoc ;
	_snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Special.config" );
	if(!MeXmlSpecialDoc.LoadFile(szFileName))
	{ return false; }

	if(!LoadSpecialItem(&MeXmlSpecialDoc,mode))
	{ return false; }

    //////////////////////////////////////////////////////////////////////////
    // ����
    MeXmlDocument MeXmlTalismanDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Talisman.config" );
    if(!MeXmlTalismanDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadTalismanItem(&MeXmlTalismanDoc,mode))
    { return false; }

	// ����װ��
    MeXmlDocument MeXmlPetEquipDoc ;
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "PetEquip.config" );
    if(!MeXmlPetEquipDoc.LoadFile(szFileName))
    { return false; }

    if(!LoadPetEquipItem(&MeXmlPetEquipDoc,mode))
    { return false; }
    
    return true;
}

bool CItemDetailConfig::SaveItemDetailConfig( const char *szPath )
{
    char szFileName[ MAX_PATH ] = {0};
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Common.config" );
    SaveItemTypes(szFileName);
    
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Restore.config" );
    SaveRestoreItem(szFileName);
    
    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Equipment.config" );
    SaveEquipmentItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Skill.config" );
    SaveSkillItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Status.config" );
    SaveStatusItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "GameAction.config" );
    SaveActionItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Material.config" );
    SaveMaterialItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Gem.config" );
    SaveGemItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Task.config" );
    SaveTaskItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Other.config" );
    SaveOtherItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Reel.config" );
    SaveReelItem(szFileName);

    //_snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "TreasureBox.config" );
    //SaveTreasureBoxItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "CheckUp.config" );
    SaveCheckUpItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "GuildBox.config" );
    SaveGuildBoxItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Special.config" );
    SaveSpecialItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Talisman.config" );
    SaveTalismanItem(szFileName);

    _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "PetEquip.config" );
    SavePetEquipItem(szFileName);
    return true;
}

bool CItemDetailConfig::CheckReload( const char *szPath )
{
    if ( nReloadSignal != ConfigLoadMode_Reload && nReloadSignal != ConfigLoadMode_Append )
    { return false; }

    char szFileName[ MAX_PATH ] = {0};

    switch (nSwitch)
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            MeXmlDocument MeXmlRestoreDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Restore.config" );
            if(!MeXmlRestoreDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadRestoreItem(&MeXmlRestoreDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_WEAPON:
    case ItemDefine::ITEMTYPE_ARMOUR:
        {
            MeXmlDocument MeXmlEquipmentDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Equipment.config" );
            if(!MeXmlEquipmentDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadEquipmentItem(&MeXmlEquipmentDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_SKILL:
        {
            MeXmlDocument MeXmlSkillDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Skill.config" );
            if(!MeXmlSkillDoc.LoadFile(szFileName))
            { return false; }
            
            if(!LoadSkillItem(&MeXmlSkillDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_STATUS:
        {
            MeXmlDocument MeXmlStatusDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Status.config" );
            if(!MeXmlStatusDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadStatusItem(&MeXmlStatusDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_ACTION:
        {
            MeXmlDocument MeXmlActionDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "GameAction.config" );
            if(!MeXmlActionDoc.LoadFile(szFileName)   )
            { return false; }

            if(!LoadActionItem(&MeXmlActionDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_MATERIAL:
        {
            MeXmlDocument MeXmlMaterialDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Material.config" );
            if(!MeXmlMaterialDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadMaterialItem(&MeXmlMaterialDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_TASK:
        {
            MeXmlDocument MeXmlTaskDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Task.config" );
            if(!MeXmlTaskDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadTaskItem(&MeXmlTaskDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_OTHER:
        {
            MeXmlDocument MeXmlOtherDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Other.config" );
            if(!MeXmlOtherDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadOtherItem(&MeXmlOtherDoc,nReloadSignal))
            { return false; }

            break;
        }

    case ItemDefine::ITEMTYPE_REEL:
        {
            MeXmlDocument MeXmlReelDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "Reel.config" );
            if(!MeXmlReelDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadReelItem(&MeXmlReelDoc,nReloadSignal))
            { return false; }

            break;
        }
	case ItemDefine::ITEMTYPE_PETEQUIP:
        {
            MeXmlDocument MeXmlReelDoc ;
            _snprintf( szFileName, sizeof(szFileName) - 1, "%s\\%s", szPath, "PetEquip.config" );
            if(!MeXmlReelDoc.LoadFile(szFileName))
            { return false; }

            if(!LoadPetEquipItem(&MeXmlReelDoc,nReloadSignal))
            { return false; }
            break;
        }
    }

    nReloadSignal = ConfigLoadMode_Normal;
    nSwitch = -1;

    return true;
}


void CItemDetailConfig::ClearItemDetailConfig()
{
    m_vectorItem.clear();
    m_BakupItem.clear();
    m_vectorItemID.clear();

    m_vecRestoreItem.clear();
    m_vecWeaponItem.clear();

    m_vecArmourItem.clear();
    m_vecGloveItem.clear();
    m_vecShoeItem.clear();
    m_vecCapItem.clear();

    m_vecSkillItem.clear();
    m_vecStatusItem.clear();
    m_vecGameActionItem.clear();
    m_vecMaterialItem.clear();
    m_vecReelItem.clear();
    m_vecTreasureBoxItem.clear();
    m_vecCheckUpItem.clear();
    m_vecGuildBoxItem.clear();
    m_vecSpecialItem.clear();

    _MonsterInfos.clear();
    m_vecPetMonster.clear();
    _creatureSounds.clear();
    m_vecDrome.clear();
    _RandsById.clear();

	m_vecPetEquipItem.clear();
}

bool CItemDetailConfig::InitItemDetail()
{
    return LoadItemDetailConfig(ITEMDETAILDIRECTORY);
}

CItemDetailConfig* CItemDetailConfig::m_s_pInstance = NULL;

CItemDetailConfig& GetItemDetailConfig()
{
    return CItemDetailConfig::GetInstance ();
}

CItemDetail& GettheItemDetail()
{
    return GetItemDetailConfig();
}

#pragma warning( pop )