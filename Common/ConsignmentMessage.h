#ifndef __CONSIGNMENTMESSAGE_H__
#define __CONSIGNMENTMESSAGE_H__
/************************************************************************
            FileName : ConsignmentMessage.h

            ����ϵͳ��Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "ConsignmentDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum ConsignmentMessageDefine
{
    MSG_SHOWCONSIGNMENTMONEYLIST = GAMEWORD_CONSIGNMENTMSG_BEGIN,       // ��ʾ��Ǯ�����б�
    MSG_SHOWCONSIGNMENTITEMLIST,                                        // ��ʾ��Ʒ�����б�( ������Ʒ, ����, ����� )
    MSG_SHOWCONSIGNMENTACCOUNT,                                         // ��ǰ�ʺ��ʽ�
    MSG_SHOWCONSIGNMENTHISTROY,                                         // ��ʾ��ʷ��¼
    MSG_OPERATEACCOUNTREQ,                                              // ��ȡǮ����
    MSG_OPERATEACCOUNTACK,                                              // ��ȡǮ����
    MSG_CONSIGNMENTMONEYREQ,                                            // ������۽�Ǯ
    MSG_CONSIGNMENTMONEYACK,                                            // �������۽�Ǯ
    MSG_CONSIGNMENTITEMREQ,                                             // ���������Ʒ
    MSG_CONSIGNMENTITEMACK,                                             // ����������Ʒ
    MSG_CONSIGNMENTOPERATEREQ,                                          // ����������۵�
    MSG_CONSIGNMENTOPERATEACK,                                          // �����������۵�
    MSG_QUERYCONSIGNMENTLIST,                                           // ����鿴���۵�
    MSG_QUERYCONSIGNMENTACK,                                            // ����
    MSG_CONSIGNMENTMONEYHISTROYREQ,                                     // ����鿴��ʷ��¼
    MSG_CONSIGNMENTMONEYHISTROYACK,
    MSG_TELLCONSIGNMENTMONEY,                                           // ȫ���㲥, Ĭ�Ϲҵ���

    CS2DB_LOADCONSIGNMENTDATAREQ = CENTERGAME_CONSIGNMENT_BEGIN,        // �����������
    DB2CS_CONSIGNMENTACCOUNTLIST,                                       // �ʺ��б�
    DB2CS_CONSIGNMENTMONEYLIST,                                         // ��Ǯ�����б�
    DB2CS_CONSIGNMENTITELISTM,                                          // ��Ʒ�����б�
    DB2CS_CONSIGNMENTHISTROYLIST,                                       // ��ʷ���׼�¼
    GS2CS_OPERNCONSIGNMENTMONEYWINDOW,                                  // ����򿪽𶧼��۽���
    CS2GS_CONSIGNMENTCOUNT,                                             // �ʺ���Ϣ
    CS2GS_CONSIGNMENTOPERATEEND,                                        // ��������
    GS2CS_QUERYCONSIGNMENTLIST,                                         // ����鿴�����б�
    GS2CS_OPERATEMONEYREQ,                                              // �����Ǯ�ʺŲ���
    CS2GS_OPERATEMONEYACK,                                              // ������Ǯ����
    CS2DB_OPERATEMONEYREQ,                                              // �������ݿ��ʺŲ���
    DB2CS_OPERATEMONEYACK,                                              // ���ݿ����
    GS2CS_CONSIGNMENTMONEYREQ,
    CS2DB_CONSIGNMENTMONEYREQ,
    GS2CS_CONSIGNMENTMONEYHISTROYREQ,
    GS2CS_CONSIGNMENTOPERATEREQ,
    CS2DB_CONSIGNMENTMONEYOPERATEREQ,
    DB2CS_CONSIGNMENTMONEYOPERATEACK,

	GS2CS_CONSIGNMENTITEMREQ,
};

struct MsgConsignmentModule : public Msg
{
    MsgConsignmentModule()
    {
        SetModuleType( EMessageModule_Consignment );
    }
};

// �𶧼����б�
struct MsgShowConsignmentMoneyList : public MsgConsignmentModule
{
    MsgShowConsignmentMoneyList()
    {
        header.dwType = MSG_SHOWCONSIGNMENTMONEYLIST;
        header.stLength = sizeof( MsgShowConsignmentMoneyList ) - sizeof( xList );
        nCount = 0;
        uchShowType = Show_All;
    }

    enum EConstDefine
    {
        Show_SellRMB = 0,       // �����б�ˢ��
        Show_BuyRMB,            // �չ��б�ˢ��
        Show_All,               // ȫ��ˢ��
    };

    unsigned char uchShowType;          // ��ʾˢ�µ��б�

    int nCount;
    ConsignmentBase xList[ ConsignmentDefine::MaxConsignmentCount * 2 ];    // �����б�

    void AddConsignmentMoney( const ConsignmentBase* pConsignment )
    {
        if ( nCount >= ConsignmentDefine::MaxConsignmentCount * 2 )
        { return; }

        xList[ nCount ].Initialize( pConsignment );

        ++nCount;
        header.stLength += sizeof( ConsignmentBase );
    }
};

// �ʺ���Ϣ
struct MsgShowConsignmentAccount : public MsgConsignmentModule
{
    MsgShowConsignmentAccount()
    {
        header.dwType = MSG_SHOWCONSIGNMENTACCOUNT;
        header.stLength = sizeof( MsgShowConsignmentAccount );
    }
    
    uint32 nRMBMoney;       // ��
    uint32 nGameMoney;      // ��Ϸ��
};

// ��ʾ��ʷ��¼
struct MsgShowConsignmentHistroy : public MsgConsignmentModule
{
    MsgShowConsignmentHistroy()
    {
        header.dwType = MSG_SHOWCONSIGNMENTHISTROY;
        header.stLength = sizeof( MsgShowConsignmentHistroy ) - sizeof( xList );
        nCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 100,
    };

    int nCount;
    ConsignmentHistroy xList[ MaxCount ];    // �����б�

    void AddConsignmentHistroy( const ConsignmentHistroy* pHistroy )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pHistroy );

        ++nCount;
        header.stLength += sizeof( ConsignmentHistroy );
    }
};

// ��ȡǮ����
struct MsgOperateMoneyReq : public MsgConsignmentModule
{
    MsgOperateMoneyReq()
    {
        header.dwType = MSG_OPERATEACCOUNTREQ;
        header.stLength = sizeof( MsgOperateMoneyReq );

        nRMBMoney = 0;
        nGameMoney = 0;
    }
    
    uint8 uchOperate;        // ����( ��ConsignmentDefine�ж��� )
    uint32 nRMBMoney;        // ��
    uint32 nGameMoney;       // ��Ϸ��
};

// ��ȡǮ����
struct MsgOperateMoneyAck : public MsgConsignmentModule
{
    MsgOperateMoneyAck()
    {
        header.dwType = MSG_OPERATEACCOUNTACK;
        header.stLength = sizeof( MsgOperateMoneyAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughMoney = 1, // û���㹻��Ǯ
        ECD_NotEnoughJinDing,   // û���㹻�Ľ�
        ECD_TooMuchMoney,       // ��Ǯ�����ﵽ����
        ECD_TooMuchJinDing,     // �˻��������ﵽ����
        ECD_WaitProcess,        // ��һ���������ڴ�����, ���Ժ�����
        ECD_SystemBusy,         // ��ҪƵ������
		ECD_InProtectLockTime,  // �ڲƲ�����ʱ����
    };

    uint8 uchOperate;           // ����
    uint8 uchResult;
};

// ������۽�
struct MsgConsignmentMoneyReq : public MsgConsignmentModule
{
    MsgConsignmentMoneyReq()
    {
        header.dwType = MSG_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( MsgConsignmentMoneyReq );
    }

    ConsignmentBase xConsignment;       // ���۵�����
};

//liaojie
//���������Ʒ
//struct MsgConsignmentItemReq : public MsgConsignmentModule
//{
//	MsgConsignmentItemReq()
//	{
//		header.dwType = MSG_CONSIGNMENTITEMREQ;
//		header.stLength = sizeof(MsgConsignmentItemReq);
//	}
//	ConsignmentData xConsignment;		//���۵�����
//};

//  �������۹ҵ�����
struct MsgConsignmentMoneyAck : public MsgConsignmentModule
{
    MsgConsignmentMoneyAck()
    {
        header.dwType = MSG_CONSIGNMENTMONEYACK;
        header.stLength = sizeof( MsgConsignmentMoneyAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughMoney = 1,     // �˻���û���㹻����Ϸ��
        ECD_NotEnoughjinDing,       // û���㹻�Ľ� 
        ECD_ConsignmentCountLimit,  // ���ٽ���25����
        ECD_WaitProcess,            // ��һ���������ڴ�����, ���Ժ�����
        ECD_SystemBusy,             // ��ҪƵ������
        ECD_MustFriend,             // ָ������ұ�������ĺ���
    };

    uint8 uchResult;
};

//  ����������Ʒ����
struct MsgConsignmentItemAck : public MsgConsignmentModule
{
	MsgConsignmentItemAck()
	{
		header.dwType = MSG_CONSIGNMENTITEMACK;
		header.stLength = sizeof( MsgConsignmentItemAck );
	}

	enum EConstDefine
	{
		ECD_NotEnoughMoney = 1,     // �˻���û���㹻����Ϸ��
		//ECD_NotEnoughjinDing,       // û���㹻�Ľ� 
		//ECD_ConsignmentCountLimit,  // ���ٽ���25����
		ECD_NoEnoughItem,			// û���㹻����Ʒ
		ECD_WaitProcess,            // ��һ���������ڴ�����, ���Ժ�����
		ECD_SystemBusy,             // ��ҪƵ������
		ECD_MustFriend,             // ָ������ұ�������ĺ���
	};

	uint8 uchResult;
};

// ����һ������
struct MsgConsignmentOperateReq : public MsgConsignmentModule
{
    MsgConsignmentOperateReq()
    {
        header.dwType = MSG_CONSIGNMENTOPERATEREQ;
        header.stLength = sizeof( MsgConsignmentOperateReq );
    }

    uint8 uchOperate;           // ���� ( ��ConsignmentDefine�ж��� )
    __int64 n64ConsignmentID;   // ���۵�ID
    uint8 uchConsignmentType;   // ���۵�����
};

// ��������
struct MsgConsignmentOperateAck : public MsgConsignmentModule
{
    MsgConsignmentOperateAck()
    {
        header.dwType = MSG_CONSIGNMENTOPERATEACK;
        header.stLength = sizeof( MsgConsignmentOperateAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �����ɹ�, ( �б���ɾ���˶��� )
        ECD_NotEnoughMoney,     // �˻���û���㹻��Ǯ
        ECD_NotEnoughJinDing,   // �˻���û���㹻�Ľ�
        ECD_WaitProcess,        // ��һ���������ڴ�����, ���Ժ�����
        ECD_SystemBusy,         // ϵͳ��æ, ���Ժ�����
        ECD_ConsignmentSelled,  // �Ѿ���������
        ECD_ConsignmentProcess, // �������ڴ�����, ���Ժ�
        ECD_ErrorOperate,       // ����Ĳ���,( ���˳���, ��Ҫ��, �����չ�, ��Ҫ�� )
        ECD_CanNotOperateSelf,  // ���������Լ��ĵ���
        ECD_CanNotCancelOther,  // ���ܳ���������ҵĵ���
        ECD_NotAppointPlayer,   // ����ָ�����, ���ܹ�����߳���
    };

    uint8 uchResult;

    __int64 n64ConsignmentID;   // ���۵�ID
    uint8 uchConsignmentType;   // ���۵�����
    __int64 n64EndTime;         // ����ʱ��
    uint8 uchEndStatus;         // ����ʱ��״̬
};

// ��ѯ���۵�
struct MsgQueryConsignmentList : public MsgConsignmentModule
{
    MsgQueryConsignmentList()
    {
        header.dwType = MSG_QUERYCONSIGNMENTLIST;
        header.stLength = sizeof( MsgQueryConsignmentList );
    }

    uint8 uchConsignmentType;   // ���۵�����
    uint8 uchQueryType;         // ��ѯ����
    int nCount;                 // ���������, ��������
};

struct MsgQueryConsignmentListAck : public MsgConsignmentModule
{
    MsgQueryConsignmentListAck()
    {
        header.dwType = MSG_QUERYCONSIGNMENTACK;
        header.stLength = sizeof( MsgQueryConsignmentListAck );
    }

    enum EConstDefine
    {
        ECD_SystemBusy = 1, // �벻ҪƵ������
        ECD_WaitProcess,    // �ȴ�������
    };

    uint8 uchResult;
};

// ��ѯ��ʷ��¼
struct MsgConsignmentMoneyHistroyReq : public MsgConsignmentModule
{
    MsgConsignmentMoneyHistroyReq()
    {
        header.dwType = MSG_CONSIGNMENTMONEYHISTROYREQ;
        header.stLength = sizeof( MsgConsignmentMoneyHistroyReq );
    }
};

struct MsgConsignmentMoneyHistroyAck : public MsgConsignmentModule
{
    MsgConsignmentMoneyHistroyAck()
    {
        header.dwType = MSG_CONSIGNMENTMONEYHISTROYACK;
        header.stLength = sizeof( MsgConsignmentMoneyHistroyAck );
    }

    enum EConstDefine
    {
        ECD_SystemBusy = 1, // �벻ҪƵ������
        ECD_WaitProcess,    // �ȴ�������
    };

    uint8 uchResult;
};

// ֪ͨ�ͻ���ĳ�˹ҵ���
struct MsgTellConsignmentMoney : public MsgConsignmentModule
{
    MsgTellConsignmentMoney()
    {
        header.dwType = MSG_TELLCONSIGNMENTMONEY;
        header.stLength = sizeof( MsgTellConsignmentMoney );
    }
    
    uint8 uchConsignmentType;  // �ҵ�����
    uint32 nPrice;             // ��Ǯ
    uint32 nCount;             // ����
};

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
struct CS2DBLoadConsignmentDataReq : public MsgConsignmentModule
{
    CS2DBLoadConsignmentDataReq()
    {
        header.dwType = CS2DB_LOADCONSIGNMENTDATAREQ;
        header.stLength = sizeof( CS2DBLoadConsignmentDataReq );
    }
};

struct DB2CSLoadConsignmentAccount : public MsgConsignmentModule
{
    DB2CSLoadConsignmentAccount()
    {
        header.dwType = DB2CS_CONSIGNMENTACCOUNTLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 1000,
    };

    int nCount;
    ConsignmentAccount xAccount[ MaxCount ];

    void AddConsignmentAccount( unsigned long nPlayerID, unsigned long nRMBMoney, unsigned long nGameMoney )
    {
        if ( nCount >= MaxCount )
        { return; }

        xAccount[ nCount ].SetPlayerID( nPlayerID );
        xAccount[ nCount ].SetRMBMoney( nRMBMoney );
        xAccount[ nCount ].SetGameMoney( nGameMoney );

        ++nCount;
        header.stLength += sizeof( ConsignmentAccount );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentAccount ) - sizeof( xAccount );
    }
};

struct DB2CSLoadConsignmentMoneyList : public MsgConsignmentModule
{
    DB2CSLoadConsignmentMoneyList()
    {
        header.dwType = DB2CS_CONSIGNMENTMONEYLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    int nCount;
    ConsignmentBase xList[ MaxCount ];

    void AddConsignmentMoney( const ConsignmentBase* pBase )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pBase );

        ++nCount;
        header.stLength += sizeof( ConsignmentBase );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentAccount ) - sizeof( xList );
    }
};

struct DB2CSLoadConsignmentHistroy : public MsgConsignmentModule
{
    DB2CSLoadConsignmentHistroy()
    {
        header.dwType = DB2CS_CONSIGNMENTHISTROYLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    int nCount;
    ConsignmentHistroy xList[ MaxCount ];

    void AddConsignmentHistroy( const ConsignmentHistroy* pHistroy )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pHistroy );

        ++nCount;
        header.stLength += sizeof( ConsignmentHistroy );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentHistroy ) - sizeof( xList );
    }
};

struct GS2CSOpenConsignmentMoneyWindow : public MsgConsignmentModule
{
    GS2CSOpenConsignmentMoneyWindow()
    {
        header.dwType = GS2CS_OPERNCONSIGNMENTMONEYWINDOW;
        header.stLength = sizeof( GS2CSOpenConsignmentMoneyWindow );
    }

	bool bGetAll;  //�Ƿ���ȫ��������Ϣ,0:ֻ���ʺ���Ϣ
    uint32 nPlayerID;
};

struct CS2GSConsignmentAccount : public MsgConsignmentModule
{
    CS2GSConsignmentAccount()
    {
        header.dwType = CS2GS_CONSIGNMENTCOUNT;
        header.stLength = sizeof( CS2GSConsignmentAccount );
    }

    ConsignmentAccount xAcount;
    bool bProcess;
};

struct CS2GSConsignmentOperate : public MsgConsignmentModule
{
    CS2GSConsignmentOperate()
    {
        header.dwType = CS2GS_CONSIGNMENTOPERATEEND;
        header.stLength = sizeof( CS2GSConsignmentOperate );
    }

    bool bProcess;
};


struct GS2CSQueryConsignmentList : public MsgConsignmentModule
{
    GS2CSQueryConsignmentList()
    {
        header.dwType = GS2CS_QUERYCONSIGNMENTLIST;
        header.stLength = sizeof( GS2CSQueryConsignmentList );
    }

    uint32 nPlayerID;

    uint8 uchConsignmentType;   // ���۵�����
    uint8 uchQueryType;         // ��ѯ����
    int nCount;                 // ���������, ��������
};

struct GS2CSOperateMoneyReq : public MsgConsignmentModule
{
    GS2CSOperateMoneyReq()
    {
        header.dwType = GS2CS_OPERATEMONEYREQ;
        header.stLength = sizeof( GS2CSOperateMoneyReq );
    }

    uint32 nPlayerID;

    uint8 uchOperate;        // ����( ��ConsignmentDefine�ж��� )
    uint32 nRMBMoney;        // ��
    uint32 nGameMoney;       // ��Ϸ��       
};

struct CS2GSOperateMoneyAck : public MsgConsignmentModule
{
    CS2GSOperateMoneyAck()
    {
        header.dwType = CS2GS_OPERATEMONEYACK;
        header.stLength = sizeof( CS2GSOperateMoneyAck );
    }

    ConsignmentAccount xAccount;    // �ʺ���Ϣ

    uint8 uchOperate;        // ����( ��ConsignmentDefine�ж��� )
    uint32 nRMBMoney;        // ��
    uint32 nGameMoney;       // ��Ϸ��
};

struct CS2DBOperateMoneyReq : public MsgConsignmentModule
{
    CS2DBOperateMoneyReq()
    {
        header.dwType = CS2DB_OPERATEMONEYREQ;
        header.stLength = sizeof( CS2DBOperateMoneyReq );
    }

    ConsignmentAccount xAccount;    // �ʺ���Ϣ

    bool bNeedDBAck;                // �Ƿ���Ҫ���ݿ����

    uint8 uchOperate;        // ����( ��ConsignmentDefine�ж��� )
    uint32 nRMBMoney;        // ��
    uint32 nGameMoney;       // ��Ϸ��
};

struct DB2CSOperateMoneyAck : public MsgConsignmentModule
{
    DB2CSOperateMoneyAck()
    {
        header.dwType = DB2CS_OPERATEMONEYACK;
        header.stLength = sizeof( DB2CSOperateMoneyAck );
    }

    ConsignmentAccount xAccount;    // �ʺ���Ϣ

    uint8 uchOperate;        // ����( ��ConsignmentDefine�ж��� )
    uint32 nRMBMoney;        // ��
    uint32 nGameMoney;       // ��Ϸ��
};

struct GS2CSConsignmentMoneyReq : public MsgConsignmentModule
{
    GS2CSConsignmentMoneyReq()
    {
        header.dwType = GS2CS_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( GS2CSConsignmentMoneyReq );
    }

    uint32 nPlayerID;
    ConsignmentBase xConsignment;       // ���۵�����

    uint32 nCostValue;                  // ���۵ķ���( ֱ�ӷ���Center, ������ )
};

struct GS2CSConsignmentItemReq : public MsgConsignmentModule
{
	GS2CSConsignmentItemReq()
	{
		header.dwType = GS2CS_CONSIGNMENTITEMREQ;
		header.stLength = sizeof( GS2CSConsignmentItemReq );
	}

	uint32 nPlayerID;
	ConsignmentData xConsignment;       // ���۵�����

	uint32 nCostValue;                  // ���۵ķ���( ֱ�ӷ���Center, ������ )
};

struct CS2DBConsignmentMoneyReq : public MsgConsignmentModule
{
    CS2DBConsignmentMoneyReq()
    {
        header.dwType = CS2DB_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( CS2DBConsignmentMoneyReq );
    }

    ConsignmentAccount xAccount;    // �ʺ���Ϣ
    ConsignmentHistroy xConsignment;       // ���۵�����
};

struct GS2CSConsignmentMoneyHistroyReq : public MsgConsignmentModule
{
    GS2CSConsignmentMoneyHistroyReq()
    {
        header.dwType = GS2CS_CONSIGNMENTMONEYHISTROYREQ;
        header.stLength = sizeof( GS2CSConsignmentMoneyHistroyReq );
    }

    uint32 nPlayerID;
};

struct GS2CSConsignmentOperateReq : public MsgConsignmentModule
{
    GS2CSConsignmentOperateReq()
    {
        header.dwType = GS2CS_CONSIGNMENTOPERATEREQ;
        header.stLength = sizeof( GS2CSConsignmentOperateReq );
    }

    uint32 nPlayerID;
    uint8 uchOperate;           // �������� ( ��ConsignmentDefine�ж��� )
    __int64 n64ConsignmentID;   // ���۵�ID
    uint8 uchConsignmentType;   // ���۵�����
};

struct CS2DBConsignmentmoneyOperateReq : public MsgConsignmentModule
{
    CS2DBConsignmentmoneyOperateReq()
    {
        header.dwType = CS2DB_CONSIGNMENTMONEYOPERATEREQ;
        header.stLength = sizeof( CS2DBConsignmentmoneyOperateReq );
    }

    ConsignmentAccount xSellerAccount;
    ConsignmentAccount xOperaterAccount;

    __int64 nConsignmentID; // ���۵�ID
    __int64 n64EndTime;       // ����ʱ��
    uint8 uchEndStatus;     // ������״̬

    ConsignmentHistroy xNewHistroy; // �µļ�¼
};

struct DB2CSConsignmentmoneyOperateAck : public MsgConsignmentModule
{
    DB2CSConsignmentmoneyOperateAck()
    {
        header.dwType = DB2CS_CONSIGNMENTMONEYOPERATEACK;
        header.stLength = sizeof( DB2CSConsignmentmoneyOperateAck );
    }

    ConsignmentAccount xSellerAccount;
    ConsignmentAccount xOperaterAccount;

    __int64 nConsignmentID; // ���۵�ID
    __int64 n64EndTime;       // ����ʱ��
    uint8 uchEndStatus;     // ������״̬

    ConsignmentHistroy xNewHistroy; // �µļ�¼
};

#pragma pack( pop )

#endif