/********************************************************************
    Filename:    PetManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_PETMANAGER_H__
#define __GAMESERVER_PETMANAGER_H__

#pragma once

#include "GlobalDef.h"
#include "bag\SkillBag.h"

class GamePlayer;
class MonsterBaseEx;

class PetManager
{
public:
    enum EConstDefine
    {

    };

    enum EActionType
    {
        AT_NotActive, // 不出战
        AT_Active,    // 出战
    };

public: // 方法
    PetManager();
    ~PetManager(){}

    bool          CreateFromData( GamePlayer* pOwner, SPetItem* pPetItems, int nPetCount ); // 初始化数据

    bool          InitPetAttribute ( SPetItem& pet );
    bool          InitPetSkill     ( SPetItem& pet );
    bool          UpdateTalentSkill( uint16 petType, uint8 skillLevel   );
    //bool          UpdatePetAttribute ( SPetItem& pet );
    bool          RealizePetSkill  ( SPetItem& pet , std::vector<uint16>& vecNewSkill, bool bInit = false );                // 技能领悟

    int64         GetNewBigID();                                     // 得到可用的BigId
    int           GetActivePetIndex()     { return _activeIndex; }
    unsigned long GetAccumulateActionTime() { return _accumulateActionTime; }
    int           GetActivePetId();                                  // 得到出战宠物的Id
    int           GetPetEmptyCount();                                // 得到空位数
    int           GetPetNumber();                                    // 获得宠物数量
    int           GetPetMaxLevel();                                  // 获得宠物最高等级
    bool          IsHavePet( int petId );                            // 是否有宠物
    bool          IsHavePetType( int petType );                      // 是否有宠物类型

    SPetItem*     GetPetByGuid( __int64 nBigId );                    // 根据guid得到宠物
    int           GetPetIndexByGuid( __int64 nBigId );               // 根据guid得到宠物位置

    SPetItem*     GetActivePet();                                    // 得到出战的宠物
    SPetItem*     GetPetByIndex( int nIndex ) ;                      // 得到指定Index的宠物

    void          SetAccumulateActionTime(unsigned long dwTime);     // 设置累计激活时间
    long          ProcessSetPetActive( int nIndex );                 // 设置出战
                  
    long          PushPet( const SPetItem& PetItem );                // 加入一只宠物
    long          PopPet ( int nIndex, bool& isActiveIndex );        // 删除一只宠物
    long          PopPetByBigId( __int64 nBigId, bool& bActive );    // 删除一个宠物

    void          AddActivePetExp( int iRewardExp );                 // 增加经验值
    bool          AddPetExp( int nIndex, int iRewardExp );           // 增加经验值

    bool          AddPetSavvy( int nIndex );                         // 增加悟性

    void          UpdateActiveIndex();                               // 更新出战的Index
    void          UpdatePetHP(short nIndex);                         // 更新宠物的生命  
    void          UpdateActiveSkillBag();                            // 更新出战的宠物的技能
    //void          ApplyPassiveSkillToPet( SPetItem* pPetItem );      

    void          RefreshPetData( unsigned long elapsTime );

    void          LostActivePetMonster();
    void          LostActivePet( bool bIsBeKilled = false );

    void          ApplyBaseAttrToFight   ( SPetItem& pet );         // 更新出战宠物属性
    void          ApplyPetAttrToPlayer   ( bool bInit = false, bool bSendMessage = true ); // 更新出战宠物属性到人物属性
	
	

    void          CalcBattleEffectiveness( SPetItem& pet );         // 计算宠物战斗力

    int           GetPetCount() { return _nPetCount; }
    void          SetPetCount(int nValue) { _nPetCount = nValue; }

    bool          IsPetFull();
    bool          IsSelfPet( GameObjectId petCharId );
    bool          HaveActivePet();
    int           GetActivePetCharId() { return _activePetCharId; }

    MonsterBaseEx*  GetMonsterNurturePet();

    bool          AddPetHp( int nIndex, int hp );
    bool          AddPetLife( int nIndex, int life );
    bool          AddPetLoyalty( int nIndex, int loyalty );

    SPetItem*     GetBreedPet();
    bool          SetBreedPet( SPetItem *pPet );
    void          ClearBreedPet();

    SkillBag*     GetActiveSkillBag() { return &_activeSkillBag; }
	bool		  ClearPetPotential(int index);

private: // 变量
    friend class GamePlayer;
    typedef std::set<unsigned long>  PetIdentifyContainer;
    typedef PetIdentifyContainer::iterator ItrPetIdentifyContainer;

    int           _nPetCount ;              // 宠物的最大个数
    SPetItem*     _pPetItems ;              // 指向实际的数组
    GamePlayer*   _pGamePlayer  ;           // 指向宠物的主人
    int           _activeIndex  ;           // 出战宠物的下标位置
    GameObjectId  _activePetCharId;         // 出战宠物角色ID
    SkillBag      _activeSkillBag;          // 出战的宠物的技能背包
    unsigned long _accumulateActionTime;    // 出战宠物累积的时间
    unsigned long _refreshLifeTime;         // 刷新宠物寿命
    unsigned long _refreshLoyaltyTime;      // 刷新宠物快乐度

public:
	//副将的装备管理 副将只有处于出战状态才可以换装备
	bool          ChangePetEquip(__int64 nBigId,__int64 ItemOnlyID,int Index);//副将穿上装备 在指定位置如果有装备 则换下 背包满的话 提示换装备失败
	bool		  RemovePetEquip(__int64 nBigId,int Index,int bagIndex=-1);//脱下指定位置的装备 放包背包去 不涉及装备的删除	
	void		  UpdatePetInfo();
	bool		  ChangePetMode(uint32 ModeID,__int64 Time);//修改副将的模型 到指定时间限制

	void		  ChangePetAtterValue(__int64 nBigId,__int64 TargetPetID);
private:
	void		  UpdateActionPetInfo(SPetItem * pPet);
	void		  OnUpdateActionPetMode();//更新出战的副将的模型 如果在出战期间发生模型到期就强行修改副将模型 并且告诉九宫格
	void		  UpdatePetEquipTime();
};

#endif // __GAMESERVER_PETMANAGER_H__
