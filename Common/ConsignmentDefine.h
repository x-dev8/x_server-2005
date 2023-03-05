#ifndef __CONSIGNMENETDEFINE_H__
#define __CONSIGNMENETDEFINE_H__

/************************************************************************
            FileName : ConsignmentDefine.h

            ����ϵͳ�Ķ���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <algorithm>
#include <functional>
#include "math.h"

namespace ConsignmentDefine
{
    enum EConstDefine
    {
        // ��������
        Consignment_Init = 0,   // ��Ч����
        Consignment_SellRMB,    // ���۽�
        Consignment_SellItem,   // ������Ʒ
        Consignment_SellMount,  // ��������
        Consignment_SellPet,    // ���۳���

        Consignment_BuyRMB,     // �չ���
        Consignment_BuyItem,    // �չ���Ʒ
        Consignment_BuyMount,   // �չ�����
        Consignment_BuyPet,     // �չ�����
        Consignment_Max,        // �������

        // ��������
        Operate_Init = 0,       // ��Ч����
        Operate_Save,           // ��Ǯ
        Operate_TakeOut,        // ȡǮ
        Operate_Sell,           // ����
        Operate_Buy,            // ����
        Operate_Cancel,         // ����
        Operate_TimeOut,        // ��ʱ( ���������� )
        Operate_Max,

        // �鿴���۵�������ʽ
        Sort_Normal = 0,        // Ĭ�ϰ���������
        Sort_LessPrice,         // ����Ǯ�͵���
        Sort_GreaterPrice,      // ����Ǯ�ߵ���
        Sort_MySelf,            // �鿴�Լ����۵�
        Sort_ForMe,             // ָ�����ҵ�
        Sort_Count,             // �鿴ָ������
        Sort_LessCount,         // ������С��������
        Sort_GreaterCount,      // �����Ӵ�С����
        Sort_Date,              // ����������

        Status_Init = 0,        // ��ʼ״̬
        Status_Running,         // �ҵ���
        Status_BuySuccess,      // ����ɹ�
        Status_SellSuccess,     // ���۳ɹ�
        Status_Buyed,           // �ѹ���
        Status_Selled,          // ���۳�
        Status_Cancel,          // ���ȡ������
        Status_TimeOut,         // ��������
        Status_Max,

        // ������Ʒ�ȵ����ݳ���
        ErrorID = 0xFFFFFFFF,
        NoneID = 0,
        MaxDataLength = 500,                // ������Ʒ���ݵ���󳤶�
        MaxConsignmentCount = 10,           // �ͻ�����ʾ�����ļ����б�����
        MaxConsignmentTime = 7 * 24 * 3600, // ���ӱ������ʱ��
        UpdateSpaceTime = 60000,            // 60�����һ��
        OperateSpaceTime = 2000,            // 2��������ִ��һ��
        LoadSpaceTime = 60000 * 10,         // 10���Ӽ������ִ��һ��

        MaxAccountRMB = 99999,			    // �˺�����������ֵ9
        MaxAccountGameMoney = 999999999,	    // �����Ϸ��

        MinSellRMBCount = 15,               // ���ٽ��׽�����
    };

    // ���۽𶧴�����۽𶧵�����, �չ��𶧴��뻨����Ϸ�ҵ�����
    static unsigned int GetConsignmentCost( int nValue ) 
    {
        const static float s_fCostRate = 0.02f;

        float fValue = static_cast< float >( nValue );
        float fCost = fValue * s_fCostRate;
        return static_cast< unsigned int >( ceil( fCost ) );
    }
}

// �ʺ���Ϣ
class ConsignmentAccount
{
public:
    ConsignmentAccount( unsigned long nValue ) : nPlayerID( nValue ), nRMBMoney( 0 ), nGameMoney( 0 ){}

    ConsignmentAccount() : nPlayerID( 0 ), nRMBMoney( 0 ), nGameMoney( 0 ){}

    unsigned long GetPlayerID() const		  { return nPlayerID;	}
    unsigned long GetRMBMoney() const		  { return nRMBMoney;	}
    unsigned long GetGameMoney() const		  { return nGameMoney;	}

    void SetPlayerID( unsigned long nValue )  { nPlayerID = nValue; }
    void SetRMBMoney( unsigned long nValue )  { nRMBMoney = nValue; }
    void SetGameMoney( unsigned long nValue ) { nGameMoney = nValue;}

    bool IsErrorAccount() const				  { return nPlayerID == 0; }

    void Initialize( const ConsignmentAccount* pAccount )
    {
        SetPlayerID( pAccount->GetPlayerID() );
        SetRMBMoney( pAccount->GetRMBMoney() );
        SetGameMoney( pAccount->GetGameMoney() );
    }

protected:
    unsigned long nPlayerID;    // ���ID
    unsigned long nRMBMoney;    // ��
    unsigned long nGameMoney;   // ��Ϸ��
};

// ���۵��ṹ
class ConsignmentBase
{
public:
    ConsignmentBase() : nBuyPlayerID( 0 ), nItemID( 0 ), n64ID( 0 ){}

    __int64		  GetID() const				{ return n64ID;			}
    unsigned char GetType() const			{ return uchType;		}
    __int64		  GetStartTime() const		{ return n64StartTime;	}
    unsigned long GetSellPlayerID() const	{ return nSellPlayerID; }
    unsigned long GetBuyPlayerID() const	{ return nBuyPlayerID;	}
    unsigned long GetPrice() const			{ return nPrice;		}
    unsigned long GetCount() const			{ return nCount;		}
    unsigned short GetItemID() const		{ return nItemID;		}

    void SetID( __int64 n64Value )			{ n64ID = n64Value;		}
    void SetType( unsigned char uchValue )	{ uchType = uchValue;	}
    void SetStartTime( __int64 n64Value )	{ n64StartTime = n64Value; }
    void SetSellPlayerID( unsigned long nValue ) { nSellPlayerID = nValue; }
    void SetBuyPlayerID( unsigned long nValue )  { nBuyPlayerID = nValue;  }
    void SetPrice( unsigned long nValue )	{ nPrice = nValue;		}
    void SetCount( unsigned long nValue )	{ nCount = nValue;		}
    void SetItemID( unsigned short nValue ) { nItemID = nValue;		}

    void Initialize( const ConsignmentBase* pBase )
    {
        if ( pBase == NULL )
        { return; }

        SetID( pBase->GetID() );
        SetType( pBase->GetType() );
        SetStartTime( pBase->GetStartTime() );
        SetSellPlayerID( pBase->GetSellPlayerID() );
        SetBuyPlayerID( pBase->GetBuyPlayerID() );
        SetPrice( pBase->GetPrice() );
        SetCount( pBase->GetCount() );
        SetItemID( pBase->GetItemID() );
    }

protected:
    __int64 n64ID;                  // ����Ψһ�Ľ�����ˮ��
    unsigned char uchType;          // ���ӳ�������
    __int64 n64StartTime;           // ��ʼ�ҵ���ʱ��
    unsigned long nSellPlayerID;    // ����
    unsigned long nBuyPlayerID;     // ָ�����, û������Ϊ 0
    unsigned long nPrice;           // ����
    unsigned long nCount;           // ����

    // ������������ֻ�е��չ���Ʒ, ����, ����ʱ����Ч
    unsigned short nItemID;         // �չ���ID( ��Ʒ, ����, ����� )
};

// ������Ʒ, ����, �����
class ConsignmentData : public ConsignmentBase
{
public:
    ConsignmentData() : ConsignmentBase()
    {
        memset( szData, 0, sizeof( szData ) );
    }

    const char* GetData() const { return szData; }
    
    bool SetData( const char* szValue, int nSize )
    {
        if ( szValue == NULL || nSize > sizeof( szData ) )
        { return false; }
        memcpy_s( szData, sizeof( szData ), szValue, nSize );
        return true;
    }

    void Initialize( const ConsignmentData* pData )
    {
        if ( pData == NULL )
        { return; }
        ConsignmentBase::Initialize( pData );
        SetData( pData->GetData(), ConsignmentDefine::MaxDataLength );
    }

protected:
    char szData[ ConsignmentDefine::MaxDataLength ];     // ���۵Ķ���
};

// ��ʷ��¼
class ConsignmentHistroy : public ConsignmentBase
{
public:
    ConsignmentHistroy() : ConsignmentBase(), n64EndTime( 0 ), nOperateID( 0 ) {}

    unsigned long GetOperateID() const	{ return nOperateID; }
    unsigned char GetStatus() const		{ return uchStatus;  }
    __int64		  GetEndTime() const	{ return n64EndTime; }


    void SetOperateID( unsigned long nValue )	{ nOperateID = nValue;	}
    void SetStatus( unsigned char uchValue )	{ uchStatus = uchValue; }
    void SetEndTime( __int64 n64Value )			{ n64EndTime = n64Value;}

    void Initialize( const ConsignmentHistroy* pHistroy )
    {
        ConsignmentBase::Initialize( pHistroy );
        SetStatus( pHistroy->GetStatus() );
        SetEndTime( pHistroy->GetEndTime() );
        SetOperateID( pHistroy->GetOperateID() );
    }

    void Initialize( const ConsignmentBase* pBase )
    {
        ConsignmentBase::Initialize( pBase );
    }

private:
    unsigned long nOperateID;   // ������ID
    unsigned char uchStatus;	// ״̬
    __int64 n64EndTime;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T, class U >        // ���м��۵�
struct CopyConsignmentMoneyList : public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() != ConsignmentDefine::NoneID )
        { return; }

        m_xVector.push_back( xData.second );
    }

    CopyConsignmentMoneyList( U& xVector ) : m_xVector( xVector ) {}
    U& m_xVector;
};

template< class T, class U >        // ָ������
struct CopyConsignmentMoneyListCount: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() != ConsignmentDefine::NoneID )
        { return; }

        if ( xData.second->GetCount() != m_nCount )
        { return; }

        m_xVector.push_back( xData.second );
    }

    CopyConsignmentMoneyListCount( U& xVector, int nCount ) : m_xVector( xVector ), m_nCount( nCount ) {}
    U& m_xVector;
    int m_nCount;
};

template< class T, class U >        // ָ������
struct CopyConsignmentMoneyListForMe: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetBuyPlayerID() == m_nPlayerID )
        {
            m_xVector.push_back( xData.second );
        }
    }

    CopyConsignmentMoneyListForMe( U& xVector, int nPlayerID ) : m_xVector( xVector ), m_nPlayerID( nPlayerID ) {}
    U& m_xVector;
    int m_nPlayerID;
};

template< class T, class U >        // ���Լ�������
struct CopyConsignmentMoneyListSelf: public std::binary_function< T, U, void >
{
    void operator() ( const T& xData )
    {
        if ( xData.second->GetSellPlayerID() == m_nPlayerID )
        {
            m_xVector.push_back( xData.second );
        }
    }

    CopyConsignmentMoneyListSelf( U& xVector, int nPlayerID ) : m_xVector( xVector ), m_nPlayerID( nPlayerID ) {}
    U& m_xVector;
    int m_nPlayerID;
};

template< class T >
struct SortByDate : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetStartTime() > xRight->GetStartTime();
    }
};

template< class T >
struct SortByLessPrice : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetPrice() < xRight->GetPrice();
    }
};

template< class T >
struct SortByGreaterPrice : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetPrice() > xRight->GetPrice();
    }
};

template< class T >
struct SortByLessCount : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetCount() < xRight->GetCount();
    }
};

template< class T >
struct SortByGreaterCount : public std::unary_function< T, bool >
{
    bool operator() ( T* xLeft, T* xRight )
    {
        return xLeft->GetCount() > xRight->GetCount();
    }
};

template< class T >
struct EqualHistroy : public std::unary_function< T, bool >
{
    bool operator() ( T* pData )
    {
        return pData->GetID() == m_n64ID;
    }

    EqualHistroy( __int64 nValue ) : m_n64ID( nValue ){}
    __int64 m_n64ID;
};

#endif