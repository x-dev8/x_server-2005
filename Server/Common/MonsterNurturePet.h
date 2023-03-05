/********************************************************************
    Filename:    MonsterNurturePet.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERNURTUREPET_H__
#define __GAMESERVER_MONSTERNURTUREPET_H__

#pragma once

#include "MonsterPetEx.h"

const short gMonsterDaemonPoolBatchSize = 10;

class MonsterNurturePet : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterNurturePet, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterNurturePet )

    MonsterNurturePet () : _pPetItemData(NULL), _petAIType(ePetAttackAI)
    { 
        memset( szTitleName , 0, sizeof(szTitleName) ); 
        SetObjType( Object_MonsterNurturePet );
    }

    virtual ~MonsterNurturePet() {}

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );
    virtual bool IsSummonPet() { return true; }

    void InitPetData( SPetItem* pPet ) { _pPetItemData = pPet; }
    SPetItem* GetPetItemData(){ return _pPetItemData; }
    void SetPetItemData( SPetItem* pPet );

    void UpdatePetData();
	void UpdatePetMode();//当副将模型发送变化的时候 我们需要发送到九宫格内

    //生命值
    virtual int   GetHP()          ;
    virtual void  SetHP( int nHp ) ;
    virtual void  OperateHP( uint8 uchOperateType, int nValue );

    virtual uint32 GetHPMax() { return _pPetItemData->baseInfo.GetFightAttribute(CharAttr_HPMax); }

    virtual void  RefreshCharData( DWORD dwCostTime);                // 刷新人物数据[更新频率1秒一次]
    virtual void  ApplyPassiveSkillToChar( );

    virtual void  SetAIType( uint8 nType) { _petAIType = nType; }
    virtual uint8 GetAIType() { return _petAIType; }

    void          SetTitleName( const char* szTitle );
    const char*   GetTitleName() { return szTitleName; }

    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    virtual void  SetUseSkill( uint16 nSkillID, uint16 nSkillLevel );
    virtual AiSkill* GetCanUseSkill( uint32 nCurrentTime );

    virtual bool TryPassivenessTriggerAttack();

	virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue);

	virtual bool CheckCanBeAttack();
	virtual void ProcessLockTarget( int nTargetID );
protected:

    // 处理怪物掉落
    virtual void ProcessDeathDromItem(){}

    // 阵营怪物死亡
    virtual void ProcessCampMonsterDeath(){}

    // 刷新怪物仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 处理宠物死亡, 消失后清除主人的信息
    virtual void ProcessPetDeath( int deathType ) ;

	
private:
    uint8         _petAIType    ;   // 宠物AI策略
    SPetItem*     _pPetItemData ;   // 宠物数据
    char          szTitleName  [dr_MaxPlayerName]   ; // 称号
};

#endif // __GAMESERVER_MONSTERNURTUREPET_H__
