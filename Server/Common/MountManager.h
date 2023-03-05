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
        CD_UPLEVEL_BASEATTRPOINT   = 1,                 //ÿ����1��ȫ����������1��
        CD_UPLEVEL_POTENTIALPOINT  = 2,                 //ÿ����1�����ӵ�Ǳ����
        CD_MOUNT_LEVEL_OVERTOP_MAX = 5,                 //����ȼ��������5���󣬽����ٻ��Ǳ�ܵ� 
        CD_MAXPLAYERCOUNT          = 8,                 //�����صĽ�ɫ����
    };

    enum EActionType
    {
        AT_NotActive, // ����ս
        AT_Active,    // ��ս
    };

public: // ����
    MountManager();
    ~MountManager(){}

    bool          CreateFromData( GamePlayer* pOwn, SMountItem* pMountItems, int nMountCount ); // ��ʼ������
    bool          InitMountAttribute( SMountItem& mountItem );
    bool          InitMountSkill    ( SMountItem& mountItem );
    bool          RandMountQuality  ( SMountItem& mountItem );     // �漴ϴ���Ʒ�� �����µ����ID

    void          Update( unsigned long elapsTime );               // �ж���ܶ��
    void          RefreshMountData( unsigned long elapsTime );     // ÿһ�����һ��

    __int64       GetNewBigID();                                   // �õ����õ�BigId
    int           GetActiveMountIndex()     { return _activeIndex; }
    unsigned long GetAccumulateActionTime() { return _accumulateActionTime; }
    int           GetActiveMountId();                                 // �õ���ս�����Id
    int           GetMountEmptyCount();                               // �õ���λ��

    SMountItem*   GetMountByGuid( __int64 nBigId );                   // ����guid�õ�����
    int           GetMountIndexByGuid( __int64 nBigId );              // ����guid�õ�����λ��

    SMountItem*   GetActiveMount();                                   // �õ���ս������
    SMountItem*   GetMountByIndex( int nIndex );                      // �õ�ָ��Index������

    void          SetAccumulateActionTime(unsigned long dwTime);      // �����ۼƼ���ʱ��
    long          SetMountActiveStatus( int nIndex, bool bActive );   // ���ó�ս
    bool          SetActiveBeRiding( bool bBeRiding );                // ���ó�ս�����ﱻ��   
    bool          GetActiveBeRiding() { return _activeMountBeRiding; }// �ж��Ƿ�����
                  
    long          PushMount( const SMountItem& mountItem );           // ����һֻ����
    long          PopMount ( int nIndex, bool& isActiveIndex );       // ɾ��һֻ����
    long          PopMountByBigId( __int64 nBigId, bool& bActiveIndex ); // ɾ��һ������
    void          AddActiveMountExp( int iRewardExp );                // ���Ӿ���ֵ
    bool          AddMountExp( int nIndex, int iRewardExp );          // ���Ӿ���ֵ
	bool		  IsMountFull();

    void          UpdateActiveIndex();                                // ���³�ս��Index
    void          UpdateMountHP(short nIndex);                        // �������������  
    void          UpdateActiveSkillBag();                             // ���³�ս������ļ���
    void          ClearPassiveSkillAffect();                          // ������ﱻ������
    void          RemoveActiveSkillBag();                             // �Ƴ���ս���＼��

    void          ApplyMountAttributeToChar( bool bInit = false, bool bSendMessage = true ); // ���³�ս�������Ե���������

    int           RestoreMountHP(bool bIsNeedMoney = true);           // ��������
    bool          AddMountHp( int nIndex, int hp );                   // ������������

    int           MountBreed( int64 masterGuid, int64 assistantGuid );      // ���ﷱֳ

    bool          SetInitiativeSkill( int nIndex, uint8 num);               // �����������ܸ���
    bool          ForgetInitiativeSkill( int nIndex, uint8 nSkillIndex);    // ������������

    int           GetActiveMountLevel();                // ��ó�ս����ȼ�

    bool          ClearMountPotential( int nIndex );    // ��������ѷ������ 

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
    //              ����������غ���
    //
    //////////////////////////////////////////////////////////////////////////

    void          InitMultiMount( int nCarryNum );                       // ��ʼ����������
    void          SendBeCarryPlayersTo( GamePlayer* pTarget );           // �����������ϵĽ�ɫ��Ϣ����������Player
    uint32        GotOnMultiMount ( GameObjectId playerId );            // ������
    uint32        GotOffMultiMount( GameObjectId playerId );            // ������
	void        GotOffMultiMountExcludeDriver();            //��˾���������������¶�����������
    void          AllPlayerGotOffMultiMount();     // ���������� ,�������
    void          OnMultiMountMoving();                                  // �ƶ�
    bool          IsDriveMultiMount();                                   // �Ƿ��ʻ�����ؾ�
    bool          IsRideMultiMount();


private: // ����
    friend class GamePlayer;
    typedef std::vector<GameObjectId> PlayerContainer;
    typedef PlayerContainer::iterator  PlayerContainerItr;

    PlayerContainer _players ;           // ��װ�صĽ�ɫ
    int             _nMaxCarryNum;       // ����������
    int             _nCurCarryNum;       // ��ǰ��������

    int           _nMountCount;          // �����������
    SMountItem*   _pMountItems;          // ָ��ʵ�ʵ�����
    GamePlayer*   _pGamePlayer;          // ָ�����������
    int           _activeIndex;          // ��ս��������±�λ��
    bool          _activeMountBeRiding;  // ��ս�������Ƿ�����
    SkillBag      _activeSkillBag;       // ��ս�ĳ���ļ��ܱ���
    unsigned long _accumulateActionTime; // ��ս�������ۻ���ʱ��

    int           _mapId;                //
    int           _posX ;                //
    int           _posY ;                //
    GameTimerEx   _xTimer;               //
    DWORD         _dwUnRideTime;         // 
    DWORD         _dwLastTipsTime;       //

    ItemDefine::SDrome* _pMountConfig;  //
};

#endif // __GAMESERVER_MOUNTMANAGER_H__
