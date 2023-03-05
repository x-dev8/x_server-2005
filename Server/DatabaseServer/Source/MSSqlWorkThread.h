/********************************************************************
    Filename:     MSSqlWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __MSSQLWORKTHREAD_H__
#define __MSSQLWORKTHREAD_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
#include "DatabaseInterface.h"
#include "DataBase.h"
#include "helper.h"
#include "WorkTaskQueue.h"
#include "Mutex.h"
#include "SqlMessages.h"

// ToDo 重连的时间间隔
// ToDo 1500的重连 和 1小时的重连
// ToDo 重连时候的消息跳出

class DatabaseServerWorkThread : public CWorkThread
{
public:
    enum EMSsqlState
    {
        MSS_NotConneted,
        MSS_Connected,
        MSS_Reconnect,
    };

    enum EConstDefine
    {
        CD_CharBaseInfoBufferSize = 1024 * 100,
        CD_ItemInfoBufferSize     = 1024 * 40,
        CD_VisualInfoBufferSize   = 1024 * 40,
        CD_OtherInfoBufferSize    = 1024 * 400,
        CD_ExtendInfoBufferSize   = 1024 * 400,
        CD_MountInfoBufferSize    = 1024 * 40,

        ECD_ReconnectPlatformTimeInterval = 1000, // 1 秒
        ECD_MaxErrorCount = 1,

        ECD_CheckQueryTimeInterval = 1000,
    };

public:
    DatabaseServerWorkThread();
    virtual ~DatabaseServerWorkThread();

    virtual bool IsHaveTask(){ return false;}

    virtual void Update();
         
    BOOL  LockQuery();
    BOOL  UnlockQuery();
         
    BOOL  PushQuery( BaseSqlMessage* pSqlMessage );
    bool  TryConnectToDatabase();

    void  SetThreadId( DWORD dwId ){ m_dwThreadId = dwId; }
    DWORD GetThreadId(){ return m_dwThreadId; }

    // DataBase::CRecordset AccQuery( const char* pszSql );
    DataBase::CRecordset RoleQuery( const char* pszSql );

    void   OnQueryLogin          ( BaseSqlMessage* pSqlMessage ); // 暂无用
    void   OnQueryLogout         ( BaseSqlMessage* pSqlMessage ); // 暂无用
    void   OnQueryCreateChar     ( BaseSqlMessage* pSqlMessage ); // 有用
    void   OnQueryCreateCheckName( BaseSqlMessage* pSqlMessage ); // 有用
    uint32 OnQueryAccountChar    ( BaseSqlMessage* pSqlMessage ); // 有用
    uint32 OnQueryCharEnterWorld ( BaseSqlMessage* pSqlMessage ); // 有用
    uint32 OnQuerySaveChar       ( BaseSqlMessage* pSqlMessage ); // 有用
    void   OnQueryDelChar        ( BaseSqlMessage* pSqlMessage ); // 有用
    void   OnQueryCancelDelChar  ( BaseSqlMessage* pSqlMessage ); // 有用    
    void   OnQueryStorage        ( BaseSqlMessage* pSqlMessage ); // 暂无用

    //////////////////////////////////////////////////////////////////////
    // 消息
    void OnQueryReqLoadPublicMessages( BaseSqlMessage* pSqlMessage ); // 暂无用

    bool RepairItem(int nBagPos = 0);
    void SaveGmInfo();

protected:
    // 整理过的函数
    bool LoadMail( const DWORD dwCharacterId) { return true; } // 加载邮件
    bool SaveMail( const DWORD dwCharacterId ){ return true; } // 保存邮件

    bool LoadCharData    ( uint8* buffer,    uint32 bufferSize, SCharBaseInfo* pInfo );
    void LoadCharApto    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );
    void LoadCharLive    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );
    void LoadCharBaseAttr( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );

    bool WriteCharData( SCharBaseInfo* pInfo, uint32& nActualSize );

    bool LoadItems    ( const uint32 dwCharacterId, SCharItem* pItem, const int nBagSize ,int nBagPos );
    bool WriteItemData( SCharItem* pItem, uint32& nActualSize );

    bool LoadVisuals    ( uint8* buffer, uint32 bufferSize, SCharVisual* pInfo );
    bool WriteVisualData( SCharVisual* pInfo, uint32& nActualSize );
    
    bool LoadOtherData ( uint8* buffer, uint32 bufferSize, SCharOtherData* pOtherData );
    bool WriteOtherData( SCharOtherData* pOtherData, uint32& nActualSize );
    
    bool LoadExtendData ( uint8* buffer, uint32 bufferSize, SExtendData* pExtendData );
    bool WriteExtendData( SExtendData* pExtendData, uint32& nActualSize );

    bool LoadMount( uint32 dwCharacterId, SMountItem* pMountItem, int nCount );
    bool WriteMountData( SMountItem* pMount, uint32& nActualSize );
    
    const char*   GUID2String( GUID *pguid );
    const GUID    String2GUID( const char* szGUID );

    void _TryLoadGmInfo();

    void _CheckConnection();

protected:
    uint8 _charBaseInfoBuffer[ CD_CharBaseInfoBufferSize ];
    uint8 _itemDataBuffer    [ CD_ItemInfoBufferSize     ];
    uint8 _visualDataBuffer  [ CD_VisualInfoBufferSize   ];
    uint8 _otherDataBuffer   [ CD_OtherInfoBufferSize    ];
    uint8 _extendDataBuffer  [ CD_ExtendInfoBufferSize   ];
    uint8 _mountDataBuffer   [ CD_MountInfoBufferSize    ];
    
    typedef std::map<std::string, GMINFO> GmContainer;
    typedef GmContainer::iterator         ItrGmContainer;
    GmContainer gmlist;
    bool        _bHaveLoadGmInfo;

    // DataBase::CConnection m_pAccConn;  // 与账号数据库的连接
    DataBase::CConnection* _pRoleConn;    // 与角色数据库的连接
    DataBase::CConnection* _pRoleConnOld; // 与角色数据库的连接 旧的 

    uint32                 _connectState;

    WorkTaskQueue     m_taskqueue;
    CIntLock          m_csQuery;
    uint32            m_dwThreadId; // 线程编号

    uint32            _lastReconnectTime;   // 重连时间
    uint32            _checkQueryTime;
};

#endif // __MSSQLWORKTHREAD_H__
