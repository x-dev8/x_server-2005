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
        ConfigLoadMode_Normal   ,   //启动加载 
        ConfigLoadMode_Append   ,   //追加加载
        ConfigLoadMode_Reload   ,   //重新加载
        ConfigLoadMode_Unknow   ,   //未知
    };

    uint8 nReloadSignal;
    int8 nSwitch;

public:

    bool LoadRestoreItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//恢复物品
    bool LoadEquipmentItem  ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//装备
    bool LoadSkillItem      ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//技能
    bool LoadStatusItem     ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//状态
    bool LoadActionItem     ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//基本动作
    bool LoadMaterialItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//材料
    bool LoadGemItem        ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//宝石
    //void LoadCreateItemRule ( MeXmlDocument *pXmlDoc);//合成配方
    bool LoadTaskItem       ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//任务
    bool LoadOtherItem      ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//其他
    bool LoadReelItem       ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//卷轴
    bool LoadTreasureBoxItem( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//宝箱
    bool LoadCheckUpItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//鉴定或者其他的一些物品
    //bool LoadRealAwardItem  ( MeXmlDocument *pXmlDoc);//真实奖励
    bool LoadGuildBoxItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//工会宝箱
    bool LoadSpecialItem    ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//特殊物品
    bool LoadTalismanItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//法宝
	bool LoadPetEquipItem   ( MeXmlDocument *pXmlDoc, int mode = ConfigLoadMode_Normal);//副将装备
    
    bool SaveItemTypes       ( const char *szFileName );//+保存道具类型
    bool SaveRestoreItem     ( const char *szFileName );//+保存恢复物品
    bool SaveEquipmentItem   ( const char *szFileName );//+保存装备
    bool SaveSkillItem       ( const char *szFileName );//+保存技能
    bool SaveStatusItem      ( const char *szFileName );//+保存状态
    bool SaveActionItem      ( const char *szFileName );//+保存基本动作
    bool SaveMaterialItem    ( const char *szFileName );//+保存材料
    bool SaveGemItem         ( const char *szFileName );//+保存宝石
    //void SaveCreateItemRule ( const char *szFileName);//+保存合成配方
    bool SaveTaskItem        ( const char *szFileName );//+保存任务
    bool SaveOtherItem       ( const char *szFileName );//+保存其他
    bool SaveReelItem        ( const char *szFileName );//+保存卷轴
    bool SaveTreasureBoxItem ( const char *szFileName );//+保存宝箱
    bool SaveCheckUpItem     ( const char *szFileName );//+保存鉴定或者其他的一些物品
    //bool SaveRealAwardItem   ( const char *szFileName );//+保存真实奖励
    bool SaveGuildBoxItem    ( const char *szFileName );//+保存工会宝箱
    bool SaveSpecialItem     ( const char *szFileName );//+保存特殊物品
    bool SaveTalismanItem    ( const char *szFileName );//+保存法宝
	bool SavePetEquipItem	 ( const char *szFileName );// 保存副将装备

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

	// 给配置热重载用的
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
