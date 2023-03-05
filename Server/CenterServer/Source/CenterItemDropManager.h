#ifndef __CENTERITEMDROPMANAGER_H__
#define __CENTERITEMDROPMANAGER_H__

#include "GlobalDef.h"
#include "GameTimer.h"
#include "Singleton.h"

#define theCenterItemDropManager CenterItemDropManager::Instance()

class CenterItemDropManager : public ISingletion< CenterItemDropManager >
{
public:
    CenterItemDropManager();

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDorpCount );
    ItemDropControl* GetItemDropControl( uint16 nItemID );

    void AutoSaveToDataBase();

    void SendLoadMessage();
    bool GetLoadSuccess() { return m_bLoadSuccess; }
    void SetLoadSuccess( bool bValue );

    void SendDropControlToGameServer( unsigned int nServerID = 0 );

    void StartLoadTimer();
    void StopLoadTimer();
    void RunUpdate( uint32 nCurrentTime );

protected:
    typedef std::set< uint16 > SaveItemDrop;
    typedef SaveItemDrop::iterator SaveItemDropIter;

    enum EConstDefine
    {
        ECD_UpdateSaveTime = 300000,
        ECD_UpdateLoadTime = 10000,
    };

    void AddToAutoSaveSet( uint16 nItemID ) { m_setItemDrop.insert( nItemID ); }
    void ClearAutoSaveSet() { m_setItemDrop.clear(); }
    bool NeedToAutoSave() { return !m_setItemDrop.empty(); }

private:
    MapItemDropControl m_mapCenterItemDropControl;
    SaveItemDrop m_setItemDrop;         // 需要保存的信息

    GameTimerEx m_xLoadTimer;
    GameTimerEx m_xUpdateTimer;

    bool m_bHaveSendLoadMessage;
    bool m_bLoadSuccess;
    bool m_bNeedSendToGameServers;
};

#endif
