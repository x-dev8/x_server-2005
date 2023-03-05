#ifndef __CHATDEFINE_H__
#define __CHATDEFINE_H__

#include <vector>
#include <algorithm>
#include "CountryDefine.h"

namespace ChatDefine
{
    enum EConstDefine
    {
        ItemDataLength = 400,                // ������Ʒ�ĳ���
        MaxItemCount = 3,                    // ÿ�������Է���3����Ʒ������
        ChatItemDataTime = 5 * 60000,        // ��Ʒ���ӱ���5����
        UpdateSpaceTime = 30000,             // ÿ30�����һ��
        MaxItemDataCount = 300,              // ÿ���������ͱ���200��
        ////////////////////////////////////////////////////////////////
        // ϵͳ��������
        BroadcastPlayer = 0,   // ���˹㲥
        BroadcastServer,       // �����㲥
        BroadcastWorld,        // ����㲥
        BroadcastContry,       // ���ҹ㲥
        BroadcastStage,        // �����㲥
    };

    class ChatItem
    {
    public:
        ChatItem() : m_nItemBagType( 0 ), m_nItemID( 0 ), m_n64ItemGuid( 0 ) {}

        unsigned char GetBagType() const { return m_nItemBagType; }
        unsigned int GetItemID() const { return m_nItemID; }
        __int64 GetItemGuid() const { return m_n64ItemGuid; }

        void SetBagType( unsigned char nValue ) { m_nItemBagType = nValue; }
        void SetItemID( unsigned int nValue ) { m_nItemID = nValue; }
        void SetItemGuid( __int64 n64Value ) { m_n64ItemGuid = n64Value; }

        bool IsEmpty() const { return m_nItemID == 0 || m_n64ItemGuid == 0; }
        void Clear() { m_nItemID = 0; m_n64ItemGuid = 0; }

    private:
        unsigned char m_nItemBagType;    // ��Ʒ��������
        unsigned int m_nItemID;        // ��ƷID
        __int64 m_n64ItemGuid;   // ��Ʒguid
    };

    class ChatItemData
    {
    public:
        ChatItemData() : m_nBagType( 0 ), m_n64Guid( 0 )
        {
            memset( m_szItemData, 0, sizeof( m_szItemData ) );
        }

        friend bool operator == ( const ChatItemData& xData, __int64 n64Guid ) { return xData.GetGuid() == n64Guid; }

        unsigned char GetBagType() const { return m_nBagType; }
        void SetBagType( unsigned char nValue ) { m_nBagType = nValue; }

        __int64 GetGuid() const { return m_n64Guid; }
        void SetGuid( __int64 n64Value ) { m_n64Guid = n64Value; }

        char* GetItemData() { return m_szItemData; }
        void AddItemData( char* pItemData, int nLength ) 
        { 
            if ( nLength > sizeof( m_szItemData ) )
            { return; }
    
            memcpy_s( m_szItemData, sizeof( m_szItemData ), pItemData, nLength );
        }

    private:
        unsigned char m_nBagType;               // ��Ʒ��������
        __int64 m_n64Guid;
        char m_szItemData[ ItemDataLength ];
    };

    class ChatItemDataList
    {
    public:
        ChatItemDataList() : m_nItemDataIndex( 0 )
        {
            m_vecItemData.clear();
        }

        void AddChatItemData( ChatItemData& xItemData );
        ChatItemData* GetChatItemData( __int64 n64Value );

    private:
        typedef std::vector< ChatItemData > ChatItemDataVector;
        typedef ChatItemDataVector::iterator ChatItemDataVectorIter;
        
        ChatItemDataVector m_vecItemData;

        // ��ӵ�����
        unsigned int m_nItemDataIndex;
    };

    inline void ChatItemDataList::AddChatItemData( ChatItemData& xItemData )
    {
        if ( m_vecItemData.empty() )
        { m_vecItemData.resize( MaxItemDataCount ); }

        // �Ȱ�ԭ�����ڵĸ��ǵ�
        for ( ChatItemDataVectorIter iter = m_vecItemData.begin(); iter != m_vecItemData.end(); ++iter )
        {
            if ( iter->GetGuid() != xItemData.GetGuid() )
            { continue; }

            *iter = xItemData;
        }

        if ( m_nItemDataIndex >= m_vecItemData.size() )
        { m_nItemDataIndex = 0; }

        m_vecItemData[ m_nItemDataIndex ] = xItemData;
        ++m_nItemDataIndex;
    }

    inline ChatItemData* ChatItemDataList::GetChatItemData( __int64 n64Value )
    {
        ChatItemDataVectorIter iter = std::find( m_vecItemData.begin(), m_vecItemData.end(), n64Value );
        if ( iter == m_vecItemData.end() )
        { return NULL; }

        return &( *iter );
    }

    class CountryChatItemDataList
    {
    public:
        CountryChatItemDataList()
        {
            m_vecCountryItemData.resize( CountryDefine::Country_Max );
        }

        void AddChatItemData( unsigned char nCountryID, ChatItemData& xItemData );
        ChatItemData* GetChatItemData( unsigned char nCountryID, __int64 n64Value );

    private:

        typedef std::vector< ChatItemDataList > CountryChatItemDataListVector;
        typedef CountryChatItemDataListVector::iterator CountryChatItemDataListVectorIter;

        CountryChatItemDataListVector m_vecCountryItemData;
    };

    inline void CountryChatItemDataList::AddChatItemData( unsigned char nCountryID, ChatItemData& xItemData )
    {
        if ( nCountryID >= m_vecCountryItemData.size() )
        { return; }

        m_vecCountryItemData[ nCountryID ].AddChatItemData( xItemData );
    }

    inline ChatItemData* CountryChatItemDataList::GetChatItemData( unsigned char nCountryID, __int64 n64Value )
    {
        if ( nCountryID >= m_vecCountryItemData.size() )
        { return NULL; }

        return m_vecCountryItemData[ nCountryID ].GetChatItemData( n64Value );
    }
}

#endif