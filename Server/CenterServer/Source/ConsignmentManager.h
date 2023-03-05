#ifndef __CONSIGNMENT_H__
#define __CONSIGNMENT_H__
/************************************************************************
            FileName : Consignment.h

            ����ϵͳ
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include <vector>
#include "ConsignmentDefine.h"
#include "Singleton.h"
#include "GameTimer.h"
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"

#define theConsignmentManager ConsignmentManager::Instance()

struct Msg;

class ConsignmentManager : public ISingletion< ConsignmentManager >
{
protected:
    // �ʺ��б�
    class Account : public ConsignmentAccount, INHERIT_POOL( Account )
    {
    public:
        DECLARE_POOL_FUNC(Account)

        Account() : ConsignmentAccount(), m_bIsWaitProcess( false ) {}

        bool IsWaitProcess() const { return m_bIsWaitProcess; }
        void SetWaitPorcess( bool bValue ) { m_bIsWaitProcess = bValue; }
    private:
        bool m_bIsWaitProcess;
    };

    class Consignment : public ConsignmentBase
    {
    public:
        Consignment() : ConsignmentBase(), m_bIsWaitProcess( false ) {}

        bool IsWaitProcess() const { return m_bIsWaitProcess; }
        void SetWaitPorcess( bool bValue ) { m_bIsWaitProcess = bValue; }
    private:
        bool m_bIsWaitProcess;
    };

    // ���۽�
    class SellRMB : public Consignment, INHERIT_POOL_PARAM( SellRMB, 50 )
    {
    public:
        DECLARE_POOL_FUNC(SellRMB);
    };

    // �չ���
    class BuyRMB : public Consignment, INHERIT_POOL_PARAM( BuyRMB, 50 )
    {
    public:
        DECLARE_POOL_FUNC(BuyRMB);
    };

    // ������Ʒ
    class SellItem : public Consignment, INHERIT_POOL_PARAM( SellItem, 50 )
    {
    public:
        DECLARE_POOL_FUNC(SellItem);
    };

    // �չ���Ʒ
    class BuyItem : public Consignment, INHERIT_POOL_PARAM( BuyItem, 50 )
    {
    public:
        DECLARE_POOL_FUNC(BuyItem);
    };

    // ���չ�������ʷ��¼
    class RMBHistroy : public ConsignmentHistroy, INHERIT_POOL ( RMBHistroy )
    {
    public:
        DECLARE_POOL_FUNC(RMBHistroy);
    };

    // ��Ʒ�չ�������ʷ��¼
    class ItemHistroy : public ConsignmentHistroy, INHERIT_POOL ( ItemHistroy )
    {
    public:
        DECLARE_POOL_FUNC(ItemHistroy);
    };

    // �����ʺ���Ϣ
    typedef std::map< unsigned long, Account* > MapAccount;   
    typedef MapAccount::iterator MapAccountIter;

    // ����𶧼�����Ϣ
    typedef std::map< __int64, SellRMB* > SellRMBMap;
    typedef SellRMBMap::iterator SellRMBMapIter;
    typedef std::pair< __int64, SellRMB* > SellRMBPair;

    typedef std::vector< SellRMB* > SellRMBVector;
    typedef SellRMBVector::iterator SellRMBVectorIter;

    // ������չ���Ϣ
    typedef std::map< __int64, BuyRMB* > BuyRMBMap;
    typedef BuyRMBMap::iterator BuyRMBMapIter;
    typedef std::pair< __int64, BuyRMB* > BuyRMBPair;

    typedef std::vector< BuyRMB* > BuyRMBVector;
    typedef BuyRMBVector::iterator BuyRMBVectorIter;

    // ������Ʒ������Ϣ
    typedef std::map< __int64, SellItem* > SellItemMap;
    typedef SellItemMap::iterator SellItemMapIter;

    // ������Ʒ�չ���Ϣ
    typedef std::map< __int64, BuyItem* > BuyItemMap;
    typedef BuyItemMap::iterator BuyItemMapIter;

    // �������ʷ��¼
    typedef std::vector< RMBHistroy* > RMBHistroyVector;
    typedef RMBHistroyVector::iterator RMBHistroyVectorIter;
    typedef RMBHistroyVector::const_iterator RMBHistroyVectorConstIter;
    typedef std::map< unsigned long, RMBHistroyVector > RMBHistroyMap;
    typedef RMBHistroyMap::iterator RMBHistroyMapIter;

    // ������Ʒ��ʷ��¼
    typedef std::vector< ItemHistroy* > VectorItemHistroy;
    typedef VectorItemHistroy::iterator VectorItemHistroyIter;
    typedef std::map< unsigned long, VectorItemHistroy > MapItemHistroy;
    typedef MapItemHistroy::iterator ItemHistroyMapIter;

public:
    ConsignmentManager();
    ~ConsignmentManager();
    
    // ִ�и���
    void RunUpdate( unsigned long nCurrentTime );

    // ���ü��سɹ�
    void SetLoadSuccess( bool bValue );

    // ����Ƿ���سɹ�
    bool GetLoadSuccess() const { return m_bLoadSuccess; }

    // ���ü����ʺ��б����
    void SetLoadConsignmentAccount( bool bValue ){ m_bLoadAccount = bValue; }
    
    // ���ü��ؼ��۵��б����
    void SetLoadConsignmentMoneyList( bool bValue ) { m_bLoadBuyRMB = m_bLoadSellRMB = bValue; }

    // ���ü��ؼ�����ʷ��¼���
    void SetLoadConsignmentMoneyHistroy( bool bValue ) { m_LoadRMBHistory = bValue; }
    
    // �������ض�ʱ��
    void StartLoadTimer( unsigned int nCurrentTime );

    // ֹͣ���ض�ʱ��
    void StopLoadTimer(){ m_xLoadTimer.StopTimer(); }

    // ��ʼ�������˻�
    void InitConsignmentAccount( const ConsignmentAccount* pAccount, int nCount ); // ��ʼ���ʺ��б�

    // ��ü����˻���Ϣ
    Account* GetConsignmentAccount( unsigned long dwPlayerID );   // ����ʺ���Ϣ

    // ��ʼ�����۽��б�
    void InitConsignmentMoneyList( const ConsignmentBase* pConsignment, int nCount );     // ��ʼ���𶧼����б�

    // ��ʼ��������Ʒ�б�
    void InitConsignmentItemList( const ConsignmentData* pConsignment, int nCount );      // ��ʼ���𶧼����б�

    // ��ʼ��������ʷ��¼
    void InitConsignmentHistoryList( const ConsignmentHistroy* pHistroy, int nCount );    // ��ʼ�����׼�¼

    // ���һ�����۵�
    bool AddConsignment( const ConsignmentBase* pConsignment );

    // ɾ��һ�����۵�
    void RemoveConsignment( __int64 n64ID, unsigned char uchType );

    // ���һ�����۵�
    Consignment* GetConsignmentMoney( __int64 n64ID, unsigned char uchType );

    // ���һ�����۽���ʷ��¼
    void AddRMBHistroy( const ConsignmentHistroy* pHistroy );

    // ���һ��������Ʒ��ʷ��¼
    void AddItemHistroy( const ConsignmentHistroy* pHistroy );

    // �����ҵļ��۽�������ʷ��¼
    const RMBHistroyVector* GetRMBHistroy( unsigned int nPlayerID );

    // ������ĳ�����۵���ʷ��¼
    RMBHistroy* GetRMBHistory( unsigned int nPlayerID, __int64 nConsignmentID );

    // ������۽������߼�
    void ProcessSortSellRMB( unsigned char uchSortType, int nValue = 0 );

    // �����չ��������߼�
    void ProcessSortBuyRMB( unsigned char uchSortType, int nValue = 0 );

    // ��������˻�
    void ProcessGameAccountOperate( unsigned int nPlayerID, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney );

    // ����DB����������˻�
    void ProcessDBAccountOperate( const ConsignmentAccount& xAccount, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney );

    // ������۵�
    void ProcessGameConsignmentMoney( unsigned int nPlayerID, ConsignmentBase& xConsignment, unsigned int nCostValue );

	//���������Ʒ
	void ProcessGameConsignmentItem( unsigned int nPlayerID, ConsignmentData& xConsignment, unsigned int nCostValue );

    // ��ѯ���۵���ʷ��¼
    void ProcessQueryMoneyHistroy( unsigned int nPlayerID );

    // �����������
    void ProcessConsignmentOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate );

    // db��������۵�����
    void ProcessDBConsignmentmoneyOperate( const ConsignmentAccount& xOperateAccount, const ConsignmentAccount& xSellerAccount, __int64 nConsignmentID, unsigned char uchEndStatus, 
                                                __int64 n64EndTime, const ConsignmentHistroy& xNewHistroy );

    // ���ͼ����ʺ���Ϣ
    void SendAccountMessage( unsigned int nPlayerID );
    void SendAccountMessage( const Account* pAccount );
    
    // ���ͼ����˻����ڵȴ�����
    void SendOperateMessage( unsigned int nPlayerID, bool bProcess );

    // ���ͼ��۵��б���Ϣ
    void SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType );
    void SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType, unsigned char uchSortType, int nValue = 0 );

protected:

    // �����������
    void ProcessLoadConsignmentData( unsigned int nCurrentTime );

    // ������Ϣ���������
    void SendMessageToPlayer( unsigned int nPlayerID, Msg* pMessage, bool bDirect );

    // ����ĳ�˷�����һ�����۵�
    void SendConsignmentMoneyToWorld( const ConsignmentBase& xConsignment );

    // ������۵�����
    void ProcessConsignmentMoneyOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate );

    // ������ۼ��۵���ʱ
    void ProcessSellRMBTimeOut();

    // �����չ����۵���ʱ
    void ProcessBuyRMBTimeOut();

    // �������۵�ID
    __int64 CreateConsigmentID( unsigned int nPlayerID, __int64 n64Time );

private:
    MapAccount     m_mapAccount;      // �����û����˺���Ϣ
    SellRMBMap     m_mapSellRMB;      // �𶧼��۵��б�
    BuyRMBMap      m_mapBuyRMB;       // ���չ����б�
    SellItemMap    m_mapSellItem;     // ��Ʒ���۵��б�
    BuyItemMap     m_mapBuyItem;      // ��Ʒ�չ����б�
    RMBHistroyMap  m_mapRMBHistroy;   // ����ʷ���׼�¼
    MapItemHistroy m_mapItemHistroy;  // ��Ʒ��ʷ���׼�¼

    bool m_bIsStartLoad;
    bool m_bLoadSuccess;
    bool m_bLoadAccount;
    bool m_bLoadSellRMB;
    bool m_bLoadBuyRMB;
    bool m_bLoadSellItem;
    bool m_bLoadBuyItem;
    bool m_LoadRMBHistory;
    bool m_LoadItemHistory;

    GameTimerEx m_xUpdateTimer;     // ���¶�ʱ��
    GameTimerEx m_xLoadTimer;       // ���ض�ʱ��

    SellRMBVector m_vecSellRMB;
    BuyRMBVector m_vecBuyRMB;
};

#endif