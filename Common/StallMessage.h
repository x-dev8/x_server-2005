#ifndef __STALLMESSAGE_H__
#define __STALLMESSAGE_H__

/************************************************************************
            ��̯��Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "StallDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum StallMessageDefine
{
    MSG_ADDSELLDATAREQ = GAMEWORD_STALLMSG_BEGIN,
    MSG_ADDSELLDATAACK,
    MSG_ADDBUYDATAREQ,
    MSG_ADDBUYDATAACK,
    MSG_UPDATESTALLDATA,
    MSG_MOVESELLDATAREQ,
    MSG_REMOVESELLDATAREQ,
    MSG_STARTSTALLREQ,
    MSG_STARTSTALLACK,
    MSG_TELLSTARTSTALL,
    MSG_CLOSESTALLREQ,
    MSG_TELLCLOSESTALL,
    MSG_OPENSTALLREQ,
    MSG_SHOWSTALLDATA,
    MSG_BUYSTALLREQ,
    MSG_SELLSTALLREQ,
    MSG_BUYORSELLSTALLACK,
    MSG_TELLBUYORSELLSTALLDATA,
    MSG_TELLSTALLDATACOUNT,
    MSG_CHANGESTALLTITLEREQ,
    MSG_TELLSTALLTITLETOVIEW,
    MSG_CHANGESTALLPRICEREQ,
    MSG_TELLSTALLPRICE,
    MSG_TELLTOTALSTALLDATA,
	MSG_STALLQUERY,
	MSG_ACKSTALLQUERY,
};

struct MsgStallModule : public Msg
{
    MsgStallModule()
    {
        SetModuleType( EMessageModule_Stall );
    }
};

// ���һ�����۵���Ʒ
struct MsgAddSellDataReq : public MsgStallModule
{
    MsgAddSellDataReq()
    {
        header.dwType   = MSG_ADDSELLDATAREQ;
        header.stLength = sizeof( MsgAddSellDataReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchBagType;       // ��Ʒ����
    unsigned char uchBagIndex;      // ��������
    __int64 n64Guid;                // guid
    unsigned int nGameMoneyPrice;   // ��Ϸ�ҵ���
    unsigned int nRMBMoneyPrice;    // �𶧵���
    unsigned char uchCount;         // ����

    unsigned char uchStallIndex;    // �ƶ���̯λ��λ��( �����ǿ�λ�� )
};

// ���һ���չ�����Ʒ
struct MsgAddSellDataAck : public MsgStallModule
{
    MsgAddSellDataAck()
    {
        header.dwType   = MSG_ADDSELLDATAACK;
        header.stLength = sizeof( MsgAddSellDataAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_ErrorStallIndex,    // �����̯λ����
        ECD_ErrorBagType,       // ����ı�������
        ECD_ErrorItem,          // ����ĵ���
        ECD_ErrorCount,         // ���������
        ECD_BoundItem,          // ����, ��, ��������Ʒ���ܰ�̯����
        ECD_AlreadyHaveData,    // ̯λ��λ���е��߳���, �������
        ECD_AlreadySellItem,    // �õ����Ѿ���̯λ����
    };

    unsigned char uchResult;
};

// ���һ���չ�����Ʒ
struct MsgAddBuyDataReq : public MsgStallModule
{
    MsgAddBuyDataReq()
    {
        header.dwType   = MSG_ADDBUYDATAREQ;
        header.stLength = sizeof( MsgAddBuyDataReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchBagType;       // ��Ʒ����
    unsigned short ustItemID;       // �չ�����ƷID
    unsigned int nGameMoneyPrice;   // ��Ϸ�ҵ���
    unsigned int nRMBMoneyPrice;    // �𶧵���
    unsigned char uchCount;         // ����
    unsigned char uchStallIndex;    // �ƶ���̯λ��λ��( �����ǿ�λ�� )
};

// ��������չ���Ʒ�Ĵ�����Ϣ
struct MsgAddBuyDataAck : public MsgStallModule
{
    MsgAddBuyDataAck()
    {
        header.dwType   = MSG_ADDBUYDATAACK;
        header.stLength = sizeof( MsgAddBuyDataAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_ErrorStallIndex,    // �����̯λ����
        ECD_ErrorBagType,       // ����ı�������
        ECD_ErrorItem,          // ����ĵ���ID
        ECD_AlreadyHaveData,    // ̯λ��λ���е��߳���, �������
    };

    unsigned char uchResult;
};


// ����̯λ����Ϣ���ͻ��� ( ���̯λ��Ʒ, �Ƴ�̯λ��Ʒ, ����ʹ�������Ϣ )
struct MsgUpdateStallData : public MsgStallModule
{
    MsgUpdateStallData()
    {
        header.dwType   = MSG_UPDATESTALLDATA;
        header.stLength = sizeof( MsgUpdateStallData );
    }

    unsigned char uchIndex;           // ̯λ������
    StallData xData;                
};

// �ƶ�̯λ�ϵ���Ʒ
struct MsgMoveStallDataReq : public MsgStallModule
{
    MsgMoveStallDataReq()
    {
        header.dwType   = MSG_MOVESELLDATAREQ;
        header.stLength = sizeof( MsgMoveStallDataReq );
    }

    unsigned char uchSrcIndex;      // Դ
    unsigned char uchDestIndex;     // Ŀ��
};

// �Ƴ�̯λ�ϵ���Ʒ
struct MsgRemoveStallDataReq : public MsgStallModule
{
    MsgRemoveStallDataReq()
    {
        header.dwType   = MSG_REMOVESELLDATAREQ;
        header.stLength = sizeof( MsgRemoveStallDataReq );
    }

    unsigned char uchIndex;      
};

//��ʼ��̯����
struct MsgStartStallReq : public MsgStallModule
{
    MsgStartStallReq()
    {
        header.dwType   = MSG_STARTSTALLREQ;
        header.stLength = sizeof( MsgStartStallReq );
    }

    enum EConstDefine
    {
        TypeOpenWindow = 1,     // �򿪰�̯����
        TypeStartStall,         // ����ʼ��̯
		TypeStartOfflineStall,  // ����ʼ���߰�̯
    };

    unsigned char uchOpenType;  // ���涨��
    char szTitle[ StallDefine::MaxStallTitle ];     // ̯λ����    
};

// ������̯����
struct MsgStartStallAck : public MsgStallModule
{
    MsgStartStallAck()
    {
        header.dwType   = MSG_STARTSTALLACK;
        header.stLength = sizeof( MsgStartStallAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_PKModeCritical,         // ��ģʽ���ܰ�̯
        ECD_ChangeMosterBuffer,     // ӵ�б���״̬���ܰ�̯
        ECD_InProtectLockTime,      // �Ʋ�����ʱ���ڲ��ܰ�̯
        ECD_IsBargainingNow,        // ���ڽ��ײ��ܰ�̯
        ECD_LessPrivateShopLevel,   // С�ڰ�̯�ȼ�
        ECD_SelfMaxMoneyLimit,      // Я����Ǯ��������
        ECD_EmptyStall,             // ���ܿ���һ����̯λ
        ECD_OnRide,                 // ����״̬�²��ܰ�̯
        ECD_ErrorStallTitle,        // ������̵����
        ECD_InFighting,             // ս��״̬���ܰ�̯
        ECD_NotEnoughMoneyBuy,      // û���㹻�Ľ�Ǯ�չ�̯λ�ϵ���Ʒ
        ECD_NotEnoughEmptyBagCount, // û���㹻�İ����ռ��չ����е���Ʒ
		ECD_NotInStallZone,         // û�д��ڿɰ�̯����
		ECD_LackOfStallFee,			// ȱ�ٰ�̯��Ҫ�Ľ�Ǯ�����
		ECD_StallDistance,		    // ��̯��������
        ECD_Death,                  // �������ܰ�̯
    };

    unsigned char uchResult;
};

// ֪ͨ�������, ĳ�˰�̯��
struct MsgTellStartStall : public MsgStallModule
{
    MsgTellStartStall()
    {
        header.dwType   = MSG_TELLSTARTSTALL;
        header.stLength = sizeof( MsgTellStartStall );
    }

    GameObjectId  nPlayerID;								// ��̯���ID
    unsigned	  int nModelID;                             // ģ��ID
    char		  szTitle[ StallDefine::MaxStallTitle ];    // ̯λ����    
	bool		  blIsOffline;								// �Ƿ����߰�̯
};

// ����ر�̯λ
struct MsgCloseStallReq : public MsgStallModule
{
    MsgCloseStallReq()
    {
        header.dwType   = MSG_CLOSESTALLREQ;
        header.stLength = sizeof( MsgCloseStallReq );
    }
};

// ֪ͨ������ҹر�̯λ
struct MsgTellCloseStall : public MsgStallModule
{
    MsgTellCloseStall()
    {
        header.dwType   = MSG_TELLCLOSESTALL;
        header.stLength = sizeof( MsgTellCloseStall );
    }

    GameObjectId nPlayerID;    // ��̯��Ҷ�̬ID
};

// �����һ��̯λ
struct MsgOpenStallReq : public MsgStallModule
{
    MsgOpenStallReq()
    {
        header.dwType   = MSG_OPENSTALLREQ;
        header.stLength = sizeof( MsgOpenStallReq );
    }
    
    GameObjectId nPlayerID;   // ��̯��Ҷ�̬ID
};

// ����̯λ���ݵ��ͻ���
struct MsgShowStallData : public MsgStallModule
{
    MsgShowStallData()
    {
        header.dwType   = MSG_SHOWSTALLDATA;
        header.stLength = sizeof( MsgShowStallData ) - sizeof( xSellData );

        uchBuyDataCount  = 0;
        uchSellDataCount = 0;
		IsOffLineStall = false;
    }

	bool	IsOffLineStall; //�Ƿ����߰�̯
    unsigned char uchBuyDataCount;
    BuyDataToClient xBuyData[ StallDefine::MaxBuyCount ]; 

    unsigned char uchSellDataCount;
    SellDataToClient xSellData[ StallDefine::MaxSellCount ]; 

    void AddBuyData( BuyDataToClient& xData )
    {
        if ( uchBuyDataCount >= StallDefine::MaxBuyCount )
        { return; }

        xBuyData[ uchBuyDataCount ] = xData;
        ++uchBuyDataCount;
    }

    void AddSellData( SellDataToClient& xData )
    {
        if ( uchSellDataCount >= StallDefine::MaxSellCount )
        { return; }

        xSellData[ uchSellDataCount ] = xData;
        ++uchSellDataCount;

        header.stLength += sizeof( SellDataToClient );
    }
};

// �ͻ���������һ����Ʒ
struct MsgBuyStallReq : public MsgStallModule
{
    MsgBuyStallReq()
    {
        header.dwType   = MSG_BUYSTALLREQ;
        header.stLength = sizeof( MsgBuyStallReq );
    }

    GameObjectId  nPlayerID;       // ̯����ID
    unsigned char uchIndex;        // ̯λ������
    unsigned int nGameMoneyPrice;  // ��Ϸ�ҵ���( ��̯λʱ���͸��ͻ��˵� )
    unsigned int nRMBMoneyPrice;   // �𶧵���( ��̯λʱ���͸��ͻ��˵� )
    unsigned char uchCount;        // ���������
    __int64 n64Guid;               // ̯λ��Ʒ��guid, ���ͻ�����У����
};

// �ͻ����������һ����Ʒ��̯λ
struct MsgSellStallReq : public MsgStallModule
{
    MsgSellStallReq()
    {
        header.dwType   = MSG_SELLSTALLREQ;
        header.stLength = sizeof( MsgSellStallReq );
    }

    GameObjectId  nPlayerID;        // ̯����ID
    unsigned char uchStallIndex;    // ̯λ������
    unsigned int nGameMoneyPrice;   // ��Ϸ�ҵ���( ��̯λʱ���͸��ͻ��˵� )
    unsigned int nRMBMoneyPrice;    // �𶧵���( ��̯λʱ���͸��ͻ��˵� )
    unsigned char uchBagType;       // ��������
    unsigned char uchBagIndex;      // ������Ʒ������
    unsigned char uchCount;         // ���۵�����
    __int64 n64Guid;                // �����г�����Ʒ��guid
};

// ����������߳��۵Ĵ���
struct MsgBuyOrSellStallAck : public MsgStallModule
{
    MsgBuyOrSellStallAck()
    {
        header.dwType   = MSG_BUYORSELLSTALLACK;
        header.stLength = sizeof( MsgBuyOrSellStallAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // �ɹ�
        ECD_PlayerOutLine,      // ̯���Ѿ���������
        ECD_StallNotStart,      // �Ѿ����ڰ�̯��
        ECD_StallDataError,     // ̯λ���ݲ���ȷ, ��ˢ��̯λ
        ECD_StallItemError,     // ����Ʒ����,�����Ѿ�������, ���ܹ���
        ECD_NotEnoughMoney,     // û���㹻����Ϸ��
        ECD_NotEnoughRMB,       // û���㹻�Ľ�
        ECD_StallPriceError,    // ̯λ��Ǯ�Ѿ�������
        ECD_ItemPackFull,       // ��������, ���ܹ���
        ECD_MountPackFull,      // ���ﱳ������, ���ܹ���
        ECD_PetPackFull,        // ���ﱳ������, ���ܹ���
        ECD_StallCountError,    // ̯λ��������ȷ
        ECD_StallerNotMoney,    // ̯��û���㹻����Ϸ�ҽ�Ǯ�չ���
        ECD_StallerNotRMB,      // ̯��û���㹻�Ľ��չ���
        ECD_SellErrorItem,      // ���۸�̯λ����Ʒ���ݲ���ȷ
        ECD_StallerPackFull,    // ̯����������
        ECD_SellItemBound,      // ���� or �� or ��������Ʒ���ܳ���
        ECD_SellMountActive,    // ��ս�����ܳ���
        ECD_StallerMountFull,   // ̯��������������, �����չ�
        ECD_SellPetActive,      // ��ս�����ܳ���
        ECD_StallerPetFull,     // ̯��������������, �����չ�
        ECD_SystemBusy,         // ������æ, ���Ժ�.( ��Ҫ����Ϊ��ֹ˫�����ڵȴ����ݿ����ʱ, ���ˢ������bug )
    };

    unsigned char uchResult;
};

// ֪̯ͨ�� ��� ���� ���� ���۸��Լ�����
struct MsgTellBuyOrSellStallData : public MsgStallModule
{
    MsgTellBuyOrSellStallData()
    {
        header.dwType   = MSG_TELLBUYORSELLSTALLDATA;
        header.stLength = sizeof( MsgTellBuyOrSellStallData );

        memset( szPlayer, 0, sizeof( szPlayer ) );
        memset( szItemName, 0, sizeof( szItemName ) );
    }

    char szPlayer[ StallDefine::MaxNameLength ];    // ��ҵ�����
    unsigned char uchStallType;                     // ���� or ����
    char szItemName[StallDefine::MaxNameLength ];   // ��Ʒ����
    unsigned char uchCount;                         // ����
    unsigned int nGameMoney;                        // �˴ν��׻�� or ʧȥ����Ǯ
    unsigned int nRmbMoney;                         // �˴ν��׻�� or ʧȥ���ٽ�
};

// ֪ͨ�򿪰�̯�����������������, ��ǰĳ��λ�õ����� 0 = ����û����
struct MsgTellStallDataCount : public MsgStallModule
{
    MsgTellStallDataCount()
    {
        header.dwType   = MSG_TELLSTALLDATACOUNT;
        header.stLength = sizeof( MsgTellStallDataCount );
    }

    unsigned char uchIndex;
    unsigned char uchCount;
};

// �ͻ�������ı�̯λ����
struct MsgChangeStallTitleReq : public MsgStallModule
{
    MsgChangeStallTitleReq()
    {
        header.dwType   = MSG_CHANGESTALLTITLEREQ;
        header.stLength = sizeof( MsgChangeStallTitleReq );
    }
    
    char szTitle[ StallDefine::MaxStallTitle ]; // ̯λ����
};

// ֪ͨ��Χ���ĳ��ҵ�̯λ����ı���
struct MsgTellStallTitleToView : public MsgStallModule
{
    MsgTellStallTitleToView()
    {
        header.dwType   = MSG_TELLSTALLTITLETOVIEW;
        header.stLength = sizeof( MsgTellStallTitleToView );
    }

    GameObjectId ustPlayerID;     // ��ҵĶ�̬id
    char szTitle[ StallDefine::MaxStallTitle ]; // ̯λ����
};

// �޸�̯λ�ļ�Ǯ ( �����ڰ�̯�������޸� )
struct MsgChangeStallPriceReq : public MsgStallModule
{
    MsgChangeStallPriceReq()
    {
        header.dwType   = MSG_CHANGESTALLPRICEREQ;
        header.stLength = sizeof( MsgChangeStallPriceReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchStallIndex;    // ̯λ��λ��( �����ǳ��� �� �չ� , ����������Ʒ )
    unsigned int nGameMoneyPrice;   // ��Ϸ�ҵ���
    unsigned int nRMBMoneyPrice;    // �𶧵���
};

// ֪̯ͨλ��ĳ����Ʒ��Ǯ
struct MsgTellStallPrice : public MsgStallModule
{
    MsgTellStallPrice()
    {
        header.dwType   = MSG_TELLSTALLPRICE;
        header.stLength = sizeof( MsgTellStallPrice );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchStallIndex;    // ̯λ��λ��
    unsigned int nGameMoneyPrice;   // ��Ϸ�ҵ���
    unsigned int nRMBMoneyPrice;    // �𶧵���
};

// ֪̯ͨ��, �Լ�̯λ�ϵ�������Ϣ
struct MsgTellTotalStallData : public MsgStallModule
{
    MsgTellTotalStallData()
    {
        header.dwType   = MSG_TELLTOTALSTALLDATA;
        header.stLength = sizeof( MsgTellTotalStallData ) - sizeof( xStallData );

        uchCount = 0;
        memset( szStallTitle, 0, sizeof( szStallTitle ) );
    }

    struct StallDataToClient
    {
        unsigned char uchStallIndex;    // ̯λ����
        StallData xData;
    };

    char szStallTitle[ StallDefine::MaxStallTitle ];    // ̯λ����
    unsigned char uchCount; // ̯λ��Ʒ����
    StallDataToClient xStallData[ StallDefine::MaxStallCount ]; // ̯λ��Ʒ����

    void AddData( unsigned char uchIndex, StallData& xData )
    {
        if ( uchCount >= StallDefine::MaxStallCount )
        { return; }

        xStallData[ uchCount ].uchStallIndex = uchIndex;
        xStallData[ uchCount ].xData = xData;
        ++uchCount;

        header.stLength += sizeof( StallDataToClient );
    }

};


//��̯��ѯ��ǰ��ͼ�Ͼ����ؼ���ɸѡ��̯λ��Ϣ
struct MsgStallQuery : public MsgStallModule
{
	//�ؼ��������ֶ�
	enum ESearchField
	{
		ESF_NONE,			//��������
		ESF_StallName,		//��̯λ��������
		ESF_ChaName,		//�ڽ�ɫ��������
//		ESF_StallOrChaName,	//��̯λ���ͽ�ɫ��������
	};

	MsgStallQuery()
	{
		header.dwType = MSG_STALLQUERY;
		header.stLength = sizeof( MsgStallQuery );

		nSearchField = ESF_NONE;
		memset( szKeyWord, 0, sizeof(szKeyWord) );
	}

	uint8	nSearchField;	//�����ֶ�����
	char	szKeyWord[ StallDefine::MaxStallTitle ];	//�����ؼ���
};

//��̯��ѯ�Ľ��
struct MsgAckStallQuery : public MsgStallModule
{
	enum EConstDefine
	{
		ECD_PageSize = 10,	//��̯��ѯ���һҳ�Ĵ�С
	};

	MsgAckStallQuery()
	{
		Clear();
	}

	bool AddData( StallDefine::SStallInfo& data )
	{
		if ( nStallCount >= ECD_PageSize )
		{ return false; }

		xData[ nStallCount ] = data;
		++nStallCount;

		header.stLength += sizeof( StallDefine::SStallInfo );
		return true;
	}

	void Clear()
	{
		header.dwType   = MSG_ACKSTALLQUERY;
		header.stLength = sizeof( MsgAckStallQuery ) - sizeof( xData );

		blTheLast = false;
		nStallCount = 0;
	}

	bool IsTheLast() { return blTheLast; }
	void SetTheLast() { blTheLast = true; }

	bool blTheLast;		//�Ƿ��б����
	int nStallCount;	//̯λ��
	StallDefine::SStallInfo xData[ ECD_PageSize ];	//̯λ��Ϣ�б�
};

#pragma pack( pop )

#endif