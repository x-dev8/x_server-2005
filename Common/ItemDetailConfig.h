/********************************************************************
Filename:     ItemDetail.h
MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ITEMDETAIL_CONFIG_H__
#define __COMMON_ITEMDETAIL_CONFIG_H__

#pragma once

#include "GlobalDef.h"
#include "MapStrToID.h"
#include "ProcessCharInfo.h"
#include "Array.h"
#include "Dxsdk/D3DX9Math.h"
// #include "Tinyxml\tinyxml.h"
#include "RapidXml\MeRapidXml.h"
#include "ItemDetail.h"

#define ITEM_UPDATE_SIGNAL  "UpdateSignal"

class ConfigReloader;
class CItemDetailConfig : public CItemDetail
{
public:
    enum EConfigLoadMode 
    { 
        ConfigLoadMode_Normal   ,   //�������� 
        ConfigLoadMode_Append   ,   //׷�Ӽ���
        ConfigLoadMode_Reload   ,   //���¼���
        ConfigLoadMode_Unknow   ,   //δ֪
    };

    uint8 nReloadSignal;
    int8 nSwitch;

public:

    bool LoadRestoreItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//�ָ���Ʒ
    bool LoadEquipmentItem  ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//װ��
    bool LoadSkillItem      ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadStatusItem     ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//״̬
    bool LoadActionItem     ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//��������
    bool LoadMaterialItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadGemItem        ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//��ʯ
    //void LoadCreateItemRule ( MeXmlDocument *pXmlDoc);//�ϳ��䷽
    bool LoadTaskItem       ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadOtherItem      ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadReelItem       ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadTreasureBoxItem( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
    bool LoadCheckUpItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//��������������һЩ��Ʒ
    //bool LoadRealAwardItem  ( MeXmlDocument *pXmlDoc);//��ʵ����
    bool LoadGuildBoxItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//���ᱦ��
    bool LoadSpecialItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//������Ʒ
    bool LoadTalismanItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����
	bool LoadPetEquipItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//����װ��
    
    bool SaveItemTypes       ( const char *szFileName );//+�����������
    bool SaveRestoreItem     ( const char *szFileName );//+����ָ���Ʒ
    bool SaveEquipmentItem   ( const char *szFileName );//+����װ��
    bool SaveSkillItem       ( const char *szFileName );//+���漼��
    bool SaveStatusItem      ( const char *szFileName );//+����״̬
    bool SaveActionItem      ( const char *szFileName );//+�����������
    bool SaveMaterialItem    ( const char *szFileName );//+�������
    bool SaveGemItem         ( const char *szFileName );//+���汦ʯ
    //void SaveCreateItemRule ( const char *szFileName);//+����ϳ��䷽
    bool SaveTaskItem        ( const char *szFileName );//+��������
    bool SaveOtherItem       ( const char *szFileName );//+��������
    bool SaveReelItem        ( const char *szFileName );//+�������
    bool SaveTreasureBoxItem ( const char *szFileName );//+���汦��
    bool SaveCheckUpItem     ( const char *szFileName );//+�����������������һЩ��Ʒ
    //bool SaveRealAwardItem   ( const char *szFileName );//+������ʵ����
    bool SaveGuildBoxItem    ( const char *szFileName );//+���湤�ᱦ��
    bool SaveSpecialItem     ( const char *szFileName );//+����������Ʒ
    bool SaveTalismanItem    ( const char *szFileName );//+���淨��
	bool SavePetEquipItem	 ( const char *szFileName );// ���渱��װ��

    CItemDetailConfig();
    ~CItemDetailConfig();

	//added by zilong. 2011-02-12. ----------------------------------------------------------
	bool LoadSkillItem(const char *fileName_, int mode_ = ConfigLoadMode_Normal);
	//bool LoadEffectFile(int skillID_, int level_);
	//added by zilong. end. -----------------------------------------------------------------

public:
    inline static CItemDetailConfig& GetInstance ()
    {
		if ( NULL == m_s_pInstance )
		{
			m_s_pInstance = new CItemDetailConfig;
		}
		return	*m_s_pInstance;
    }

    bool LoadItemDetailConfig( const char *szPath ,int mode = ConfigLoadMode_Normal );
    bool SaveItemDetailConfig( const char *szPath );

    bool CheckReload( const char *szPath );
    void ClearItemDetailConfig();

    bool InitItemDetail();
private:
	friend class ConfigReloader;

	static CItemDetailConfig* m_s_pInstance;

	// �������������õ�
	void SetInstance( CItemDetailConfig* pConfig )
	{
		if ( m_s_pInstance )
		{ delete m_s_pInstance; }
		m_s_pInstance = pConfig;
	}
};

extern CItemDetailConfig& GetItemDetailConfig();

#define theItemDetailConfig GetItemDetailConfig()

#endif // __COMMON_ITEMDETAIL_CONFIG_H__
