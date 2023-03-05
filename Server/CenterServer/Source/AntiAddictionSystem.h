/********************************************************************
    Filename:    AntiAddictionSystem.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_ANTIADDICTIONSYSTEM_H__
#define __CENTERSERVER_ANTIADDICTIONSYSTEM_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
/*
class AntiAddictionAccountInfo : public Common::TObject_pool<AntiAddictionAccountInfo>
{
public:
    static AntiAddictionAccountInfo* CreateInstance() { return CNewWithDebug<AntiAddictionAccountInfo>::Alloc(1, "Alloc AntiAddictionAccountInfo");}
    
    AntiAddictionAccountInfo();
    virtual ~AntiAddictionAccountInfo();
    virtual void Release();

public:
    uint32  accountId;        // �˺�Id
    uint32  onlineMinuteTime; // ���ߵ�λ����
    uint32  offMinuteTime;    // ���ߵ�λ����
    __int64 lastOfflineTime;  // ��ʵ���ͷ�ʱ��
};

class AntiAddictionSystem
{
public:
    enum EContainerType
    {
        ECT_OnlineContainer,  // ��������
        ECT_OfflineContainer, // ��������
    };

    enum ETimeFrequencyType
    {
        ETFT_60Minute = 60,
        ETFT_30Minute = 30,
        ETFT_15Minute = 15,
    };

    AntiAddictionSystem();
    ~AntiAddictionSystem();
    
    void Update();

    void OnMinorAccountOnline ( uint32 accountId );
    void OnMinorAccountOffline( uint32 accountId );

    void UpdateAntiAddictionAccountInfo( AntiAddictionAccountInfo* pAntiAddictionAccountInfo, unsigned char containerType );
    AntiAddictionAccountInfo* RemoveAntiAddictionAccountInfo( uint32 accountId, unsigned char containerType );
    AntiAddictionAccountInfo* GetAntiAddictionAccountInfo( uint32 accountId, unsigned char containerType );

protected:
    void _TellAntiAddictionAccountInfo( AntiAddictionAccountInfo* pAntiAddictionAccountInfo );

private:
    typedef std::map<uint32, AntiAddictionAccountInfo*> AccountInfoContainer;
    typedef AccountInfoContainer::iterator              ItrAccountInfoContainer;

    AccountInfoContainer _accountOnlineInfo;
    AccountInfoContainer _accountOfflineInfo;
    uint32               _lastUpdateTime; // ���µĸ���ʱ��
};

AntiAddictionSystem& GetAntiAddictionSystem();
*/
#endif // __CENTERSERVER_ANTIADDICTIONSYSTEM_H__
