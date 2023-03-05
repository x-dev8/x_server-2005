#ifndef __STALLDEFINE_H__
#define __STALLDEFINE_H__

/************************************************************************
            ��̯���Զ���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <WinDef.h>

namespace StallDefine
{
    enum EConstDefine
    {
        StallNone = 0,              // ��Ч����
        StallSell,                  // ��̯����
        StallBuy,                   // ��̯�չ�
                             
        MaxStallCount = 40,         // ̯λ�������
        MaxSellCount  = 16,         // ��������Ʒ 25
        MaxBuyCount   =  6,         // ����չ���Ʒ
        MaxStallTitle = 25,         // ���̯λ��Ϣ
        MaxDataLength = 1500,        // �����������
        MaxNameLength = 33,         // �����������

        StallMaleModel   = 4601,    // ��̯ �е�ģ��ID
        StallFemaleModel = 4602,    // ��̯ Ů��ģ��ID

		OfflineStallMaleModel   = 4638,    // ���߰�̯ �е�ģ��ID
		OfflineStallFemaleModel = 4639,    // ���߰�̯ Ů��ģ��ID

        StallRevenue = 5,           // ��̯˰��  n%
    };

	//��̯��ѯ��Ϣ
	struct SStallInfo
	{
		unsigned int	dwMapID;							// ̯λ������ͼID
		unsigned short  nX;									// ̯λX����
		unsigned short  nY;									// ̯λY����
		char			szStallTitle[ MaxStallTitle ];		// ̯λ����
		char			szCharacterName[ MaxNameLength ];	// �������
	};
}

class StallData
{
public:
    StallData() : m_uchStallType( StallDefine::StallNone ), m_uchBagType( 0 ), m_n64Guid( 0 ), m_nGameMoneyPrice( 0 ), m_nRMBMoneyPrice( 0 ), m_uchCount( 0 ), m_nItemID( 0 )
    {

    }

    unsigned char GetStallType() const { return m_uchStallType; }
    unsigned char GetBagType() const { return m_uchBagType; }
    __int64 GetGuid() const { return m_n64Guid; }
    unsigned int GetGameMoneyPrice() const { return m_nGameMoneyPrice; }
    unsigned int GetRMBMoneyPrice() const { return m_nRMBMoneyPrice; }
    unsigned char GetCount() const { return m_uchCount; }
    unsigned int GetItemID() const { return m_nItemID; }

    void SetStallType( unsigned char uchValue ) { m_uchStallType = uchValue; }
    void SetBagType( unsigned char uchValue ) { m_uchBagType = uchValue; }
    void SetGuid( __int64 n64Value ) { m_n64Guid = n64Value; }
    void SetGameMoneyPrice( unsigned int nValue ) { m_nGameMoneyPrice = nValue; }
    void SetRMBMoneyPrice( unsigned int nValue ) { m_nRMBMoneyPrice = nValue; }
    void SetCount( unsigned char uchValue ) { m_uchCount = uchValue; }
    void SetItemID( unsigned int nValue ) { m_nItemID = nValue; }
    
    // ���̯λ��Ϣ
    void ClearStall()
    {
        m_uchBagType      = 0;
        m_n64Guid         = 0;
        m_nGameMoneyPrice = 0;
        m_nRMBMoneyPrice  = 0;
        m_uchCount        = 0;
        m_nItemID         = 0;
    }
    
    bool IsEmpty() const { return m_uchStallType == StallDefine::StallNone || m_uchCount == 0; }

protected:
    unsigned char m_uchStallType;     // ��̯���� or �չ�

    unsigned char m_uchBagType;       // ������Ʒ�ı�������
    __int64 m_n64Guid;                // ������Ʒ��guid
    unsigned int m_nGameMoneyPrice;   // ������Ʒ����Ϸ�ҵ���
    unsigned int m_nRMBMoneyPrice;    // ������Ʒ�Ľ𶧵���
    unsigned char m_uchCount;         // ������Ʒ������

    // ��̯�չ�
    unsigned int m_nItemID;           // �չ���ƷID
};

// ���۵���Ʒ
class SellDataToClient
{
public:
    SellDataToClient() : m_nGameMoneyPrice( 0 ), m_nRMBMoneyPrice( 0 )
    {
        memset( m_szData, 0, sizeof( m_szData ) );
    }

    unsigned char GetIndex() const { return m_uchIndex; }
    unsigned char GetBagType() const { return m_uchBagType; }
    unsigned int GetGameMoneyPrice() const { return m_nGameMoneyPrice; }
    unsigned int GetRMBMoneyPrice() const { return m_nRMBMoneyPrice; }
    
    void SetIndex( unsigned char uchValue ) { m_uchIndex = uchValue; }
    void SetBagType( unsigned char uchValue ) { m_uchBagType = uchValue; }
    void SetGameMoneyPrice( unsigned int nValue ) { m_nGameMoneyPrice = nValue; }
    void SetRMBMoneyPrice( unsigned int nValue ) { m_nRMBMoneyPrice = nValue; }

    bool SetData( void* pData, unsigned int nSize )
    {
        if ( pData == NULL || nSize == 0 || nSize > sizeof( m_szData ) )
        { return false; }

        memcpy_s( m_szData, sizeof( m_szData ), pData, nSize );
        return true;
    }

    bool GetData( void* pData, unsigned int nSize )
    {
        if ( pData == NULL )
        { return false; }

        memcpy_s( pData, nSize, m_szData, min( nSize, sizeof( m_szData ) ) );
        return true;
    }
    
protected:
    unsigned char m_uchIndex;                    // ̯λ������
    unsigned char m_uchBagType;                  // ������Ʒ�ı�������
    unsigned int m_nGameMoneyPrice;              // ������Ʒ����Ϸ�ҵ���
    unsigned int m_nRMBMoneyPrice;               // ������Ʒ�Ľ𶧵���
    char m_szData[ StallDefine::MaxDataLength ]; // ������Ʒ����������
};

// �չ�����Ʒ
class BuyDataToClient
{
public:
    BuyDataToClient() : m_nGameMoneyPrice( 0 ), m_nRMBMoneyPrice( 0 ), m_ustCount( 0 ) {}

    unsigned char GetIndex() const { return m_uchIndex; }
    unsigned int GetItemID() const { return m_nItemID; }
    unsigned int GetGameMoneyPrice() const { return m_nGameMoneyPrice; }
    unsigned int GetRMBMoneyPrice() const { return m_nRMBMoneyPrice; }
    unsigned short GetCount() const { return m_ustCount; }

    void SetIndex( unsigned char uchValue ) { m_uchIndex = uchValue; }
    void SetItemID( unsigned int nValue ) { m_nItemID = nValue; }
    void SetGameMoneyPrice( int nValue ) { m_nGameMoneyPrice = nValue; }
    void SetRMBMoneyPrice( unsigned int nValue ) { m_nRMBMoneyPrice = nValue; }
    void SetCount( unsigned short ustValue ) { m_ustCount = ustValue; }
protected:
    unsigned char m_uchIndex;        // ̯λ������
    unsigned int m_nItemID;          // �չ�����ƷID
    unsigned int m_nGameMoneyPrice;  // ������Ʒ����Ϸ�ҵ���
    unsigned int m_nRMBMoneyPrice;   // ������Ʒ�Ľ𶧵���
    unsigned short m_ustCount;       // �չ�������
};
#endif