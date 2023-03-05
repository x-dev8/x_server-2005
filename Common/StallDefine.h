#ifndef __STALLDEFINE_H__
#define __STALLDEFINE_H__

/************************************************************************
            摆摊属性定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <WinDef.h>

namespace StallDefine
{
    enum EConstDefine
    {
        StallNone = 0,              // 无效类型
        StallSell,                  // 摆摊出售
        StallBuy,                   // 摆摊收购
                             
        MaxStallCount = 40,         // 摊位最大数量
        MaxSellCount  = 16,         // 最大出售物品 25
        MaxBuyCount   =  6,         // 最大收购物品
        MaxStallTitle = 25,         // 最大摊位信息
        MaxDataLength = 1500,        // 数据最大类型
        MaxNameLength = 33,         // 最大的玩家名字

        StallMaleModel   = 4601,    // 摆摊 男的模型ID
        StallFemaleModel = 4602,    // 摆摊 女的模型ID

		OfflineStallMaleModel   = 4638,    // 离线摆摊 男的模型ID
		OfflineStallFemaleModel = 4639,    // 离线摆摊 女的模型ID

        StallRevenue = 5,           // 摆摊税收  n%
    };

	//摆摊查询信息
	struct SStallInfo
	{
		unsigned int	dwMapID;							// 摊位所处地图ID
		unsigned short  nX;									// 摊位X坐标
		unsigned short  nY;									// 摊位Y坐标
		char			szStallTitle[ MaxStallTitle ];		// 摊位标题
		char			szCharacterName[ MaxNameLength ];	// 玩家名字
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
    
    // 清除摊位信息
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
    unsigned char m_uchStallType;     // 摆摊出售 or 收购

    unsigned char m_uchBagType;       // 出售物品的背包类型
    __int64 m_n64Guid;                // 出售物品的guid
    unsigned int m_nGameMoneyPrice;   // 出售物品的游戏币单价
    unsigned int m_nRMBMoneyPrice;    // 出售物品的金锭单价
    unsigned char m_uchCount;         // 出售物品的数量

    // 摆摊收购
    unsigned int m_nItemID;           // 收购物品ID
};

// 出售的物品
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
    unsigned char m_uchIndex;                    // 摊位的索引
    unsigned char m_uchBagType;                  // 出售物品的背包类型
    unsigned int m_nGameMoneyPrice;              // 出售物品的游戏币单价
    unsigned int m_nRMBMoneyPrice;               // 出售物品的金锭单价
    char m_szData[ StallDefine::MaxDataLength ]; // 出售物品的数据内容
};

// 收购的物品
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
    unsigned char m_uchIndex;        // 摊位的索引
    unsigned int m_nItemID;          // 收购的物品ID
    unsigned int m_nGameMoneyPrice;  // 出售物品的游戏币单价
    unsigned int m_nRMBMoneyPrice;   // 出售物品的金锭单价
    unsigned short m_ustCount;       // 收购的数量
};
#endif