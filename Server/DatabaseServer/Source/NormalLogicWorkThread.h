/********************************************************************
    Filename:    NormalLogicWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASE_NORMALLOGICWORKTHREAD_H__
#define __DATABASE_NORMALLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"
#include "CharChunkWR.h"

// 正常逻辑的Sql存储线程
class NormalLogicWorkThread : public MySqlWorkThread
{
public:
    NormalLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~NormalLogicWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetOtherQueueSize() > 0; }

    virtual uint32 Update();
    virtual void OnQueryCreateChar     ( BaseSqlMessage* pSqlMessage ); 
    virtual void OnQueryCreateCheckName( BaseSqlMessage* pSqlMessage );
    virtual void OnQueryAccountChar    ( BaseSqlMessage* pSqlMessage ); 
    virtual void OnQueryCharEnterWorld ( BaseSqlMessage* pSqlMessage ); 
    virtual void OnQuerySaveChar       ( BaseSqlMessage* pSqlMessage ); 
    virtual void OnQueryDelChar        ( BaseSqlMessage* pSqlMessage );
    virtual void OnQueryCancelDelChar  ( BaseSqlMessage* pSqlMessage );
    virtual void OnQueryPetBreed       ( BaseSqlMessage* pSqlMessage );
	virtual void OnQueryChangeName		( BaseSqlMessage* pSqlMessage );
	virtual void OnUpdateAccountYuanBao ( BaseSqlMessage* pSqlMessage );
	virtual void OnUpdatePlayerPoint    ( BaseSqlMessage* pSqlMessage );
protected:
    bool LoadItems( const uint32 dwCharacterId, SCharItem* pItem, const int nBagSize ,int nBagPos );
    bool LoadMount( uint32 dwCharacterId, SMountItem* pMountItem, int nCount ,int nBagPos );
    bool LoadPets ( uint32 dwCharacterId, SPetItem*   pPetItem  , int nCount ,int nBagPos );

    void SaveGmInfo(){}
    void _TryLoadGmInfo();

private:
    CharChunkWR _charDataWR;
    typedef std::map<std::string, GMINFO> GmContainer;
    typedef GmContainer::iterator         ItrGmContainer;
    GmContainer gmlist;
    bool        _bHaveLoadGmInfo;
}; 

#endif // __DATABASE_NORMALLOGICWORKTHREAD_H__
