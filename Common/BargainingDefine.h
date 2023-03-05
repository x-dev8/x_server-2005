#ifndef __BARGAININGDEFINE_H__
#define __BARGAININGDEFINE_H__

/************************************************************************
            �������Զ���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <vector>

namespace BargainingDefine
{
    enum EConstDefine
    {
        //////////////////////////////////////////////////////////
        NoneID = 0,
        MaxItemCount = 16,          // ��ཻ����Ʒ���� 20
		MaxPetCount = 4,			// ���ｻ������
        DataLength = 1500,          // ���׵�������BUFF�ĳ���
        MaxBargainingID = 10000000, // ���Ľ���ID
        InviteKeepTime = 60000,     // ��������1������Ч
        BargainingTime = 720000,    // ����12����ʱ������Ч
        BargainingMoneyLevel = 10,  // 10�����ϲ��ܽ��׽�Ǯ
        BargainingMountLevel = 5,   // �������ﲻ�ܳ�����ҵȼ�5��
        /////////////////////////////////////////////////////////////
        BargainingMoney = 1,        // ���׽�Ǯ
        BargainingRMB,              // ���׽�
        BargainingItem,             // ���׵���
        BargainingMount,            // ��������
        BargainingPet,              // ���׳���

        /////////////////////////////////////////////////////////////
        // ���׵�״̬
        StatusInit = 0,             // ��ʼ״̬
        StatusStart,                // ���׿�ʼ, ������Ʒ״̬
        StatusLock,                 // ������Ʒ, ����״̬
        StatusFix,                  // ������, ȷ������״̬
        /////////////////////////////////////////////////////////////
        // ���׽���
        FinishSuccess = 1,          // ���׳ɹ�
        FinishTimeOut,              // ���׳�ʱ
        FinishCancel,               // ����ȡ��
        FinishOutLine,              // �������, ����ȡ��
        //////////////////////////////////////////////////////////////
        // �������������Ϣ
        FailedSuccess = 0,          // �ͻ��˲��ô������ö��
        FailedBargaining,           // �Լ����ڽ�����
        FailedTargetBargaining,     // �Է����ڽ�����
        FailedStall,                // �Լ����ڰ�̯��
        FailedTargetStall,          // �Է����ڰ�̯��
        FailedNotInArea,            // �Է�û���ڷ�Χ��( 16����Ч )
        FailedRefuse,               // �Է��ܾ�����
        FailedRequest,              // �ѷ��ͽ�������
        FailedFighting,             // �Լ�����ս��״̬
        FailedTargetFighting,       // �Է�����ս��״̬
        //////////////////////////////////////////////////////////////////
        // ������뽻�׵���ʱ�Ĵ������
        LessMoney = 1,              // û���㹻�Ľ�Ǯ
        MoneyLevelLimit,            // 10�����²��ܽ��׽�Ǯ
        LessRMB,                    // û���㹻�Ľ�
        MaxMoney,                   // ��Ǯ����������Я��������
        DataError,                  // ���׵ĵ�����Ϣ����ȷ
        DataLocked,                 // ���׵ĵ��������������Ѱ�
        DataOverdue,                // ���׵ĵ����ѹ���
        DataAlready,                // ���׵ĵ����Ѿ��ڽ���������
        IndexAlready,               // ����Ľ������Ѿ��е�����
        CanNotTrade,                // ���׵ĵ��߲��ܱ�����
        IndexError,                 // ������λ�ô���
        NormalFull,                 // ��ͨ��������
        MaterialFull,               // ���ϱ�������
        MountFull,                  // ���ﱳ������
        PetFull,                    // ���ﱳ������
        DataChange,                 // ���׵����Ѿ����
        MountActive,                // �����ѳ�ս, ���ܽ���
        MountLevelLimit,            // ����ȼ������Է��ȼ�5������
        PetActive,                  // �����ѳ�ս, ���ܽ���
        PetLevelLimit,              // ����ȼ������Է��ȼ�5������
		PlayerPetLimit,				// �����Է���������,���ܽ���
        //////////////////////////////////////////////////////////////////
    };
}
//////////////////////////////////////////////////////////////////////////////////////

// ���׵���Ʒ����
class BargainingData
{
public:
    BargainingData() : m_ustItemCount( 0 ), m_n64ItemGuid( 0 ), m_nItemValue1( 0 ), m_nItemValue2( 0 )
    {

    }

    unsigned char GetItemBag() const { return m_uchItemBag; }
    unsigned char GetItemIndex() const { return m_uchItemIndex; }
    unsigned short GetItemCount() const { return m_ustItemCount; }
    __int64 GetItemGuid() const { return m_n64ItemGuid; }
    unsigned int GetItemValue1() const { return m_nItemValue1; }
    unsigned int GetItemValue2() const { return m_nItemValue2; }

    void SetItemBag( unsigned char uchValue ) { m_uchItemBag = uchValue; }
    void SetItemIndex( unsigned char uchValue ) { m_uchItemIndex = uchValue; }
    void SetItemCount( unsigned short ustValue ) { m_ustItemCount = ustValue; }
    void SetItemGuid( __int64 n64Value ) { m_n64ItemGuid = n64Value; }
    void SetItemValue1( unsigned short nValue ) { m_nItemValue1 = nValue; }
    void SetItemValue2( unsigned short nValue ) { m_nItemValue2 = nValue; }

    void ClearData()
    {
        m_n64ItemGuid = 0;
        m_ustItemCount = 0;
    }

protected:
    unsigned char m_uchItemBag;     // ��Ʒ����
    unsigned char m_uchItemIndex;   // ��Ʒ����
    unsigned short m_ustItemCount;  // ��Ʒ����
    __int64 m_n64ItemGuid;          // ��Ʒguid

    // ��չ������, �ȶ���
    unsigned int m_nItemValue1;
    unsigned int m_nItemValue2;
};

// ��ҽ��׵�����
class PlayerBargaining
{
public:
    PlayerBargaining() : m_uchStatus( BargainingDefine::StatusInit ), m_nPlayerID( 0 ), m_nGameMoney( 0 ), m_nRMBMoney( 0 )
    {
    }

    unsigned int GetID() const { return m_nPlayerID; }
    unsigned char GetStatus() const { return m_uchStatus; }
    unsigned int GetGameMoney() const { return m_nGameMoney; }
    unsigned int GetRMBMoney() const { return m_nRMBMoney; }


    void SetID( unsigned int nValue ) { m_nPlayerID = nValue; }
    void SetStatus( unsigned char uchValue ) { m_uchStatus = uchValue; }
    void SetGameMoney( unsigned int nValue ) { m_nGameMoney = nValue; }
    void SetRMBMoney( unsigned int nValue ) { m_nRMBMoney = nValue; }

    const BargainingData* GetBargainingData( unsigned int nIndex ) const;
    bool AddBargainingData( unsigned int nIndex, BargainingData& xData );
    void ClearBargainingData( unsigned int nIndex );

    // У�齻�׵���Ʒ�Ƿ��Ѿ����ڵ���
    bool CheckBargainingData( unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid );

protected:
    typedef std::vector< BargainingData > BargainingDataVector;
    typedef BargainingDataVector::iterator BargainingDataVectorIter;

    unsigned int m_nPlayerID;        // ���DBID
    unsigned char m_uchStatus;       // ��ǰ�Ľ���״̬
    unsigned int m_nGameMoney;       // ���׵���Ϸ��
    unsigned int m_nRMBMoney;        // ���׵Ľ�
    BargainingData xData[ BargainingDefine::MaxItemCount ];  // ���׵���Ʒ
};

inline const BargainingData* PlayerBargaining::GetBargainingData( unsigned int nIndex ) const
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return NULL; }

    return &( xData[ nIndex ] );
}

inline bool PlayerBargaining::AddBargainingData( unsigned int nIndex, BargainingData& xBargainingData )
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return false; }

    xData[ nIndex ] = xBargainingData;
    return true;
}

inline bool PlayerBargaining::CheckBargainingData( unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid )
{
    for ( int i = 0; i < BargainingDefine::MaxItemCount; ++i )
    {
        if ( xData[i].GetItemGuid() != n64Guid )
        { continue; }

        if ( xData[i].GetItemBag() != uchBagType )
        { continue; }

        if ( uchBargainingIndex != i )
        { return false; }
    }

    return true;
}

inline void PlayerBargaining::ClearBargainingData( unsigned int nIndex )
{
    if ( nIndex >= BargainingDefine::MaxItemCount )
    { return; }

    xData[ nIndex ].ClearData();
}

#endif