/********************************************************************
    Filename:    MountManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MOUNTMANAGER_H__
#define __GAMESERVER_MOUNTMANAGER_H__

#pragma once

#include "GlobalDef.h"
#include "Bag/SkillBag.h"
#include "GameTimer.h"
#include "ItemDetail.h"

class GamePlayer;

class MountManager
{
public:
    enum EConstDefine
    {
        CD_MOUNT_HP_MAX_VALUE      = 100,
        CD_MOUNT_HP_CONSUME_TIME   = 1000 * 60 * 60,
        CD_UPLEVEL_BASEATTRPOINT   = 1,                 //每提升1级全部属性提升1点
        CD_UPLEVEL_POTENTIALPOINT  = 2,                 //每提升1级增加的潜力点
        CD_MOUNT_LEVEL_OVERTOP_MAX = 5,                 //坐骑等级超过玩家5级后，将不再获得潜能点 
        CD_MAXPLAYERCOUNT          = 8,                 //最大承载的角色个数
    };

    enum EActionType
    {
        AT_NotActive, // 不出战
        AT_Active,    // 出战
    };

public: // 方法
    MountManager();
    ~MountManager(){}

    bool          CreateFromData( GamePlayer* pOwn, SMountItem* pMountItems, int nMountCount ); // 初始化数据
    bool          InitMountAttribute( SMountItem& mountItem );
    bool          InitMountSkill    ( SMountItem& mountItem );
    bool          RandMountQuality  ( SMountItem& mountItem );     // 随即洗马的品质 返回新的马的ID

    void          Update( unsigned long elapsTime );               // 有多块跑多块
    void          RefreshMountData( unsigned long elapsTime );     // 每一秒调用一次

    __int64       GetNewBigID();                                   // 得到可用的BigId
    int           GetActiveMountIndex()     { return _activeIndex; }
    unsigned long GetAccumulateActionTime() { return _accumulateActionTime; }
    int           GetActiveMountId();                                 // 得到出战坐骑的Id
    int           GetMountEmptyCount();                               // 得到空位数

    SMountItem*   GetMountByGuid( __int64 nBigId );                   // 根据guid得到坐骑
    int           GetMountIndexByGuid( __int64 nBigId );              // 根据guid得到坐骑位置

    SMountItem*   GetActiveMount();                                   // 得到出战的坐骑
    SMountItem*   GetMountByIndex( int nIndex );                      // 得到指定Index的坐骑

    void          SetAccumulateActionTime(unsigned long dwTime);      // 设置累计激活时间
    long          SetMountActiveStatus( int nIndex, bool bActive );   // 设置出战
    bool          SetActiveBeRiding( bool bBeRiding );                // 设置出战的坐骑被骑   
    bool          GetActiveBeRiding() { return _activeMountBeRiding; }// 判断是否骑马
                  
    long          PushMount( const SMountItem& mountItem );           // 加入一只坐骑
    long          PopMount ( int nIndex, bool& isActiveIndex );       // 删除一只坐骑
    long          PopMountByBigId( __int64 nBigId, bool& bActiveIndex ); // 删除一个坐骑
    void          AddActiveMountExp( int iRewardExp );                // 增加经验值
    bool          AddMountExp( int nIndex, int iRewardExp );          // 增加经验值
	bool		  IsMountFull();

    void          UpdateActiveIndex();                                // 更新出战的Index
    void          UpdateMountHP(short nIndex);                        // 更新坐骑的生命  
    void          UpdateActiveSkillBag();                             // 更新出战的坐骑的技能
    void          ClearPassiveSkillAffect();                          // 清除坐骑被动技能
    void          RemoveActiveSkillBag();                             // 移除出战坐骑技能

    void          ApplyMountAttributeToChar( bool bInit = false, bool bSendMessage = true ); // 更新出战坐骑属性到人物属性

    int           RestoreMountHP(bool bIsNeedMoney = true);           // 治疗坐骑
    bool          AddMountHp( int nIndex, int hp );                   // 增加坐骑生命

    int           MountBreed( int64 masterGuid, int64 assistantGuid );      // 坐骑繁殖

    bool          SetInitiativeSkill( int nIndex, uint8 num);               // 设置主动技能个数
    bool          ForgetInitiativeSkill( int nIndex, uint8 nSkillIndex);    // 遗忘主动技能

    int           GetActiveMountLevel();                // 获得出战坐骑等级

    bool          ClearMountPotential( int nIndex );    // 清除坐骑已分配点数 

    int           GetMountCount() { return _nMountCount; }
    void          SetMountCount(int nValue) { _nMountCount = nValue; }

    bool          HasMount( uint16 nMountId );

    void          SetLastRidePos( int mapId, int posX, int posY );
    bool          IsInRideRange ( int nRange );
	bool          GetLastRidePos(int &mapId , int &posX, int &posY)
	{
		mapId = _mapId ;
		posX  = _posX ;
		posY  = _posY ;

		return mapId==0&&posX==0&&posY==0;
	}

    ItemDefine::SDrome* GetActiveMountConfig() { return _pMountConfig; }
    void          SetActiveMountConfig( ItemDefine::SDrome* pMountConfig ) { _pMountConfig = pMountConfig; }

    bool          ApplyMountStatusToMaster();
    void          ClearMountStatusToMaster();

    //////////////////////////////////////////////////////////////////////////
    //              
    //              多人坐骑相关函数
    //
    //////////////////////////////////////////////////////////////////////////

    void          InitMultiMount( int nCarryNum );                       // 初始化多人坐骑
    void          SendBeCarryPlayersTo( GamePlayer* pTarget );           // 发送在坐骑上的角色信息给看到他的Player
    uint32        GotOnMultiMount ( GameObjectId playerId );            // 上坐骑
    uint32        GotOffMultiMount( GameObjectId playerId );            // 下坐骑
	void        GotOffMultiMountExcludeDriver();            //除司机其他的所有人下多人坐骑，不清空
    void          AllPlayerGotOffMultiMount();     // 所有人下马 ,并且清空
    void          OnMultiMountMoving();                                  // 移动
    bool          IsDriveMultiMount();                                   // 是否驾驶多人载具
    bool          IsRideMultiMount();


private: // 变量
    friend class GamePlayer;
    typedef std::vector<GameObjectId> PlayerContainer;
    typedef PlayerContainer::iterator  PlayerContainerItr;

    PlayerContainer _players ;           // 被装载的角色
    int             _nMaxCarryNum;       // 最大承载人数
    int             _nCurCarryNum;       // 当前承载人数

    int           _nMountCount;          // 坐骑的最大个数
    SMountItem*   _pMountItems;          // 指向实际的数组
    GamePlayer*   _pGamePlayer;          // 指向坐骑的主人
    int           _activeIndex;          // 出战的坐骑的下标位置
    bool          _activeMountBeRiding;  // 出战的坐骑是否被骑着
    SkillBag      _activeSkillBag;       // 出战的宠物的技能背包
    unsigned long _accumulateActionTime; // 出战的坐骑累积的时间

    int           _mapId;                //
    int           _posX ;                //
    int           _posY ;                //
    GameTimerEx   _xTimer;               //
    DWORD         _dwUnRideTime;         // 
    DWORD         _dwLastTipsTime;       //

    ItemDefine::SDrome* _pMountConfig;  //
};

#endif // __GAMESERVER_MOUNTMANAGER_H__
