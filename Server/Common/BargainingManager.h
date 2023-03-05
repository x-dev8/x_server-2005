#ifndef __BARGAININGMANAGER_H__
#define __BARGAININGMANAGER_H__

/************************************************************************
            ���׹���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "GameTimer.h"
#include "Singleton.h"
#include "Memory_Pool.h"
#include "BargainingDefine.h"

// ��ҽ�����Ϣ
class BargainingInfo : INHERIT_POOL_PARAM( BargainingInfo, 10 )
{
public:
    static BargainingInfo* Instace() { return CNewWithDebug< BargainingInfo >::Alloc( 1, "����BargainingInfoʵ��" ); }
    virtual void Release() { CNewWithDebug< BargainingInfo >::Free( this ); }

    // ��ý���ID��
    unsigned int GetID() const { return m_nBargainingID; }

    // ���ý���ID��
    void SetID( unsigned int nValue ) { m_nBargainingID = nValue; }
    
    PlayerBargaining& GetPlayerBargainingA() { return m_xPlayerBargainingA; }
    PlayerBargaining& GetPlayerBargainingB() { return m_xPlayerBargainingB; }

    // �����ҽ�����Ϣ
    PlayerBargaining* GetPlayerBargaining( unsigned int nPlayerID );

    // ��öԷ�������Ϣ
    PlayerBargaining* GetTargetPlayerBargaining( unsigned int nPlayerID );

    // ɾ��������Ϣ
    void ClearBargainingData( unsigned char uchType );

    // ��鶨ʱ��
    bool CheckTimer() { return m_xBargainingTimer.DoneTimer(); }

    // ������ʱ��
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime );

protected:
    unsigned int m_nBargainingID;
    PlayerBargaining m_xPlayerBargainingA;    // �������A
    PlayerBargaining m_xPlayerBargainingB;    // �������B
    GameTimerEx m_xBargainingTimer;           // ���׶�ʱ��
};

// ��������
class BargainingInvite
{
public:
    // ������뽻�����ID
    unsigned int GetInviteID() const { return m_nInviteID; }

    // �������뽻�����ID
    void SetInviteID( unsigned int nValue ) { m_nInviteID = nValue; }

    // ������ʱ��
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime ) { m_xInviteTimer.StartTimer( nStartTime, nKeepTime ); }
    
    // ��鶨ʱ��
    bool CheckTimer() { return m_xInviteTimer.DoneTimer(); }

protected:
    unsigned int m_nInviteID;    // ������
    GameTimerEx m_xInviteTimer;  // ��ʱ��ʱ��
};

#define theBargainingManager BargainingManager::Instance()

// ���׹���
class BargainingManager : public ISingletion< BargainingManager >
{
public:
    BargainingManager();
    ~BargainingManager();

    // ����һ������
    BargainingInfo* CreateBargaining();

    // ɾ��һ������
    void RemoveBargaining( unsigned int nBargainingID, unsigned char uchRemoveType );

    // ���һ������
    BargainingInfo* GetBargaining( unsigned int nBargainingID );

    // ���һ�����������¼
    void AddBargainingInvite( unsigned int nReqID, unsigned int nAckID );

    // ɾ��һ�����׼�¼
    void RemoveBargainingInvite( unsigned int nAckID );

    // ���������ID
    unsigned int GetBargainingInvite( unsigned int nAckID );    

    // ִ�и���
    void RunUpdate( unsigned int nCurrentTime );

protected:

    // ��ý���ID��
    unsigned int GetBarganingID();

    // ���������б�
    void UpdateBargainingInvite( unsigned int nCurrentTime );

    // ���½����б�
    void UpdateBargaining( unsigned int nCurrentTime );

private:

    // �����б�
    typedef std::map< unsigned int, BargainingInfo* > BargainingMap;
    typedef BargainingMap::iterator BargainingMapIter;

    // ���������б�
    typedef std::map< unsigned int, BargainingInvite > BargainingInviteMap;
    typedef BargainingInviteMap::iterator BargainingInviteMapIter;

    unsigned int m_nBargainingID;       // ����ID
    BargainingMap m_mapBargaining;      // �����б�
    BargainingInviteMap m_mapInvite;    // �����¼
    GameTimerEx m_xUpdateTimer;         // ���׸��¶�ʱ��
};

#endif