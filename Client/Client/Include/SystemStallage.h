/********************************************************************
            �°�̯ϵͳ        by ZhuoMeng.Hu		[12/23/2010]
*********************************************************************/

#pragma once

#include "Singleton.h"
#include "StallMessage.h"
#include "StallDefine.h"
#include "GlobalDef.h"
#include "ItemEnableChangeSysBase.h"

class CSystemStallage : public Singleton<CSystemStallage>, CItemEnableChangeSysBase
{
public:
    struct StallageItem 
    {
        StallageItem()
        {
            m_nBagType = -1;
            m_nSrcIndex = -1;
            m_nDestIndex = -1;
            m_nCount = -1;
            m_nMoneyPrice = 0;
            m_nItemId = 0;
            m_nGuid = 0;
        }
        int         m_nBagType;
        int         m_nSrcIndex;
        int         m_nDestIndex;
        int         m_nCount;
        int         m_nMoneyPrice;
        int         m_nItemId;
        __int64     m_nGuid;
    };

public:
    ~CSystemStallage();

    virtual bool IsPackItemBeUsing( __int64 nGuid );

    // ����˷�������Ϣ����
    void TellPlayerStartStall( int nPlayerId, int nModelId, const char* pTitle, bool bIsOffline_);   // ֪ͨ������ң�ĳ�˰�̯��
    void TellPlayerCloseStallage( int nPlayerId );                                  // ֪ͨ������ҹر�̯λ
    void TellPlayerTitleChange( int nPlayerId, const char* pTitle );                // ֪ͨ�������ĳ̯λ������

    void ShowSelfStallageData( const MsgTellTotalStallData* pMsg );                 // �Լ�̯λ��ʱͬ������˵�����
    void TellSelfStallageUpdate( const MsgUpdateStallData* pMsg );                  // �����Լ���̯λ��Ϣ (���ӡ��Ƴ�)
    void TellSelfGoodsPriceChange( int nIndex, int nMoneyPrice, int nGoldPrice );   // �����Լ�����Ʒ�۸�
    void AddSelfTradeRecord( MsgTellBuyOrSellStallData* pMsg );                     // �Լ���̯�Ľ��׼�¼

    void TellPlayerStallageData( MsgShowStallData* pMsg );                          // ֪ͨ���̯λ����
    void TellPlayerStallageCountChange( int nTotalIndex, int nCount );              // ���̯λ��Ʒ�����ı�

    void TellAddSellResult( int nResult );                                          // ���һ��������Ʒ����
    void TellAddBuyResult( int nResult );                                           // ���һ���ع���Ʒ����
    void TellQuestStallResult( int nResult );                                       // ��̯�������
    void TellErrorsInStall( int nErrorType );                                       // ��̯�����и��ֽ��״���

	void SendOpenStallMsg(bool bOnline_);

    // �û�UI�����������
    void OpenStallageWindow();                                                      // �򿪰�̯���棬����ͬ��̯λ����
	void OpenStallageWindow2(void);
    void MoveFromPackToGoodsSell( int nDestIndex, int nSrcIndex, int nBagType );    // �ӱ�����̯λ��Ʒ���ƶ�
    void MoveMountToSell( int nDestIndex, int nSrcIndex );                          // ��������̯λ�������ƶ�
    void MoveFromPackToGoodsBuy( int nDestIndex, int nSrcIndex, int nBagType );     // �ӱ�����̯λ�չ����ƶ�
    static bool AddItemToStallageSell( DWORD dwPrice, void *pData );                // ���۽�Ǯ�����ص�
    static bool AddItemToStallageBuy( DWORD dwPrice, int nCount, void *pData );     // �չ������ص�
    void MoveGoodsInSellSlots( int nSrcIndex, int nDestIndex );                     // ��Ʒ���������ƶ�
    void MoveMountInSellSlots( int nSrcIndex, int nDestIndex );                     // ����������Ʒ�ƶ�
    void MoveGoodsInBuySlots( int nSrcIndex, int nDestIndex );                      // �չ�������Ʒ�ƶ�
    void RemoveGoodsSell( int nIndex );                                             // ���������Ƴ���Ʒ
    void RemoveMountSell( int nIndex );                                             // ���������Ƴ���Ʒ
    void RemoveGoodsBuy( int nIndex );                                              // �չ������Ƴ���Ʒ
    void StartStallRequest();                                                       // �����ʼ��̯
    void CloseStallRequest();                                                       // �����̯
    void ChangeStallName();                                                         // �������̯λ����
    void TellStallageName( const char* pName );                                     // ���ĵ�̯λ����
    void SetItemPrice( int nIndex, bool bIsSell, bool bIsMount, __int64 nGuid );    // ������ü۸�
    static bool SelfStallageSetPrice( DWORD dwPrice, void *pData );                 // ���ü۸������ص�
    void ClearTradeRecord();                                                        // ��ս��׼�¼

    void QuerryPlayerStallageRequest( int nPlayerId );                              // ����鿴���˵�̯λ
    void LeaveMessageToVender();                                                    // ��̯������
    void GetItemFromVenderSell( int nIndex, bool bIsMount, __int64 nGuid );         // ��̯�������򶫶�
    static bool BuyItemFromVender( const char* szInputData, void *pData );          // ��̯�������򶫶���Ŀ�����ص�
    static bool SellItemToVender( const char* szInputData, void *pData );           // ����̯��������Ŀ�����ص�
    void MoveItemToVenderBuy( int nBagType, int nSrcIndex, int nDestIndex, __int64 nGuid );                     // ����Ʒ����̯���չ�����

	//���ӳ��ﵽ��̨
	void AddPetToSell(SPetItem &pet_, int srcIndex_, int destIndex_);
	//�ӹ�̨�Ƴ�����
	void RemovePetSell(int index_);
	void RemovePetSell(SPetItem &pet_);
    
    // �ӿ�
    bool IsSelfInStalling();                                                        // �Լ��Ƿ��ڰ�̯
    bool IsPlayerInStalling( int nPlayerId );                                       // ����Ƿ��ڰ�̯
    bool IsMountInStallage( __int64 nGuid );                                        // �����Ƿ���̯λ��
	bool IsPetInStallage(__int64 nGuid );
    int  GetMountIndexByGuid( __int64 nGuid );                                      // ��������һ��
    void SetCharItemEnable( __int64 nGuid, bool bEnable );                          // ������ұ������������� Enablehe �� Disable
    bool CheckMeExist();                                                            // �ж� GetPlayerMgr()->GetMe()
    bool CheckPlayerExist( int nPlayerId );                                         // �ж� GetPlayerMgr()->FindById()

    int  GetVenderId();                                                             // ��ȡ̯��ID
    void SeekSelfMountByIndex( int nIndex, __int64 nGuid );                         // �鿴�Լ�̯λ�����Guid����У��
    void SeekPlayerMountByIndex( int nIndex, __int64 nGuid );                       // �鿴̯�������Guid����У��
    const std::vector<std::string>& GetTradeRecord();                               // ��ȡ���׼�¼
    std::string GetPriceTipString( DWORD dwPrice );                                 // ��ȡTip�۸�����
    void RefreshCharItemsInStallage();                                              // ˢ����̯λ�еı�������Ʒ�� Enablehe �� Disable

    bool GetSelfItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount,
        OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount );               // ��ȡ�Լ���Ʒ�۸���Ϣ

    bool GetPlayerItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount,
        OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount );               // ��ȡ̯����Ʒ�۸���Ϣ

    // �ڲ��߼�
    void TellSelfEnterWorld();                                                      // ��ɫ��½�����ڳ�ʼ��
    int GetBuyStackNumLimit();                                                      // �չ���Ʒ�ѵ������������
    SellDataToClient* GetPlayerSellData();                                          // ��ȡ����̯����������
    BuyDataToClient* GetPlayerBuyData();                                            // ��ȡ����̯���չ�����

protected:
    int GetSubIndexByTotalIndex( int nIndex, int nUsage, int nBagType = BT_NormalItemBag );                     // ���ݷ���˵�������ȡ�ͻ��˵�
    int GetTotalIndexBySubIndex( int nIndex, int nUsage, int nBagType = BT_NormalItemBag );                     // ���ݿͻ��˵�������ȡ����˵�
    bool ClassifyByTotalIndex( IN int nTotalIndex, OUT int& nSubIndex, OUT int& nUsage, OUT bool& bIsMount );   // ���ݷ���˵�������ȡ������Ϣ

    void ClearSelfStallage();                                                       // ����Լ�����̯λ����
    void ClearPlayerStallage();                                                     // ���̯������̯λ����


private:
    friend class Singleton<CSystemStallage>;
    CSystemStallage();

public:
	enum EGoodsType
	{
		E_Goods_common = 0,
		E_Goods_pet,
		E_Goods_mount,//E_Goods_replace,
		E_Goods_replace,//E_Goods_mount,
		E_Goods_buy,
		E_Goods_end,
	};

	EGoodsType GetGoodInfo(int index_, int &_subIndex);
	bool CheckGoodIndex(int index_, EGoodsType goodType_);	//������Ʒ��totalIndex�Ƿ�Ϸ�
	void SetItemPrice(int totalIndex_);
	int GetTotalIndexBySubIndex(int subIndex_, EGoodsType goodType_);
	bool GetSelfItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count);
	bool GetPlayerItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count);
	void GetItemFromVenderSell( int totalIndex_);         // ��̯�������򶫶�

private:
    const int m_nItemSellIndexBegin;                // ��Ʒ����������ʼֵ
    const int m_nMountSellIndexBegin;               // �������������ʼֵ
    const int m_nItemBuyIndexBegin;                 // ��Ʒ�չ�������ʼֵ

	static const int m_goodsIndex[E_Goods_end + 1];

    const int m_nItemBuyStackCnt;                   // �չ���Ʒ�ѵ������������

    bool m_bStallageFirstShow;                      // ��ɫ�Ƿ��һ���Լ���̯
    int m_nVenderPlayerId;                          // ��¼̯����Id
    std::vector<std::string>    m_tradeRecordVec;   // ���׼�¼

    // �ͻ��˱���һ��̯λ����
    StallData           m_selfStallData[ StallDefine::MaxStallCount ];
    BuyDataToClient     m_playerBuyData[ StallDefine::MaxStallCount ];
    SellDataToClient    m_playerSellData[ StallDefine::MaxStallCount ];

	bool m_bOnlineStall;	//�Ƿ�Ϊ���߰�̯
};
