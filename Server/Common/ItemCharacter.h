/********************************************************************
    Filename:     ItemCharacter.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_ITEMCHARACTER_H__
#define __GAMESERVER_ITEMCHARACTER_H__

#pragma once

#include "BaseCharacter.h"
#include "NetControl.h"

class ItemCharacter : public BaseCharacter,
                      public DItemChar,
                      INHERIT_POOL_PARAM(ItemCharacter, 10 )
{ // ��Ʒ��ɫ
public:    
    enum EPickResult
    {
        eResultSuccess = 0       // �ɹ�
        ,eResultNotMasterGruop   // ��������ӵ�
        ,eResultNotMasterPlayer  // ������ҵ�
        ,eResultBeenPick         // �Ѿ�����
        ,eResultTaskItem         // ������Ʒ
        ,eResultUnknow
        ,eResultIsGroupNotPlayer // �Ǳ��ӵĵ��������
        ,eResultNotTeamHeader    // �㲻�Ƕӳ� 
    };

    enum enumConstPublic
    {
        const_drop_delay     = 2,     // ���ߵ��ӳ���ʾ second
        PackageViewTimeOut   = 40000, // �鿴������ʱʱ��
        ServerBoultTimeOut   = 32000, // ��ɸ�ӵĳ�ʱʱ�� ����� 32��
        ClientBoultTimeOut   = 30000, // ��ɸ�ӵĳ�ʱʱ�� �ͻ��� 30��
        PackageViewSpaceTime = 2000,  // ����鿴��������Ϣ�ļ��ʱ��            
    };

    struct SBornDelay
    {
        short stBornDelay;
        unsigned long dwLastCheckTime;
    };

    struct SPlayerBoultNumber
    {
        uint32 dwPlayerID;
        uint16 nBoultNumber;            //ɸ�ӵ���

        bool operator == (uint32 dwID) { return dwPlayerID == dwID; }
        friend bool operator > (const SPlayerBoultNumber& xLeft, const SPlayerBoultNumber& xRight)
        {
            return xLeft.nBoultNumber > xRight.nBoultNumber;  //������ȷ���false
        }
    };

public:
    typedef std::map<__int64, std::vector<SPickAccessInfo> >    PickLevelMap;
    typedef std::map<__int64, uint32>                           BoultTimeMap;
    typedef std::map<__int64, std::vector<SPlayerBoultNumber> > BoultNumberMap;
    typedef std::vector<SPlayerBoultNumber>                     BoultNumberVector;
    typedef std::vector<SPickAccessInfo>                        PickAccessVector;
    typedef std::vector< unsigned int >                         CharIdContainer;
    typedef std::map<uint32, uint32>                            ViewTimeMap;

public:
    DECLARE_POOL_FUNC( ItemCharacter )

    ItemCharacter();
    virtual ~ItemCharacter(){}

    virtual bool IsItem() { return true; }

    // ���ܱ�����
    virtual bool CheckCanBeAttack() { return false; }

    virtual void ProcessRefreshEnmity( uint32 nCurrentTime ) {}

    virtual void OnDeath(void) {}

    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ static SCharFightAttr instance; return &instance; }
    virtual void   SetHPMax( uint32 hpMax ){ _hpMax = hpMax; }
    virtual uint32 GetHPMax()              { return _hpMax;  }

    //////////////////////////////////////////////////////////////////////////
    virtual Msg* FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);
    virtual bool ProcessMsg(Msg*pMsg);
    virtual void OnExit( Msg*pMsg, unsigned char exitType = ET_ExitGame);
    virtual void Run(DWORD dwCostTime);

    /*Luoz----- if( m_iMasterGroupID != -1 && m_iMasterGroupID == -1 )----------
                    ������һ��û�ж�����˵� ����Ϊ�����
                else if( m_iMasterGroupID == -1 && m_iMasterGroupID != -1 ) ----
                    �������Ϊ�������飬�˶�����˶�����pick
                else if( m_iMasterGroupID != -1 && m_iMasterGroupID != -1 )-----
                    Ŀǰ�������Ϊ������������� if�������40���ڲ�pick�Ļ�������Ʒ������Ϊ�˶���
                else if( m_iMasterGroupID == -1 && m_iMasterGroupID == -1 )
                    Ŀǰ������ȷ����Ʒ�Ĺ��� 
                    1>��Ҷ�û�з����Ļ� ��ʰȡ�е��漴
                    2>��Ҷ������Ļ� ��Ʒ������ ���Ϊ ���鹫��ģʽ    
                    3>���˿ͻ���20��û��ѡ��Ļ� ϵͳĬ��Ϊ���� ��Ҷ������Ļ� ��Ʒ���������Ϊ���鹫��ģʽ*/
   
    void SetItem( SCharItem &item ){ m_item = item; }
    void SetBornDelay( unsigned char ucBornDelay );

    void SetMasterGroupID(int id);
    void SetMasterID(int id);

    void ClearPickFlag(void){m_BePickFlag = false;}
    void SetTaskItem();
    SCharItem* PickItem( uint32 nGroupId, int nPlayerId, EPickResult &result );
    int GetCanPickRemainTime();
    
    void setPeopleOfTeamTime();
    void setPeopleOfTeamTime( DWORD tm);
    int  getRemainTimeIsGroupNotPlayer();
    void setItemAscriptionToGroup()        { m_iMasterNpcID = -1;  }
    void setHoldGroupId(int id);

    void setAdscription_teamHeader(bool bHeader = true);
    bool getAdscription_teamHeader() const                { return m_bAdscription_teamHeader; }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    void SetPackagePolistDeathTime();                                               // ��������Ʒʱ, ������ʧʱ��
    void SetPackageNormalDeathTime();                                               // ��������Ʒ�Ժ������ʧʱ��

    bool AddCharItem( SCharItem& xItem );                    // ���һ�����ߵ�������
    void RemoveCharItem(__int64 nItemID, uint16 nItemCount);                        // �Ӱ�����ɾ��һ������
    SCharItem* GetCharItem(__int64 nItemID);                                        // �Ӱ����л��һ������
    SCharItem* GetCharItemById(uint16 nItemID);                                     // �Ӱ����л��һ������
    SCharItem* GetCharItemByIndex(short nIndex);                                    // ���������һ������
    void GetCharItemList(std::vector<__int64>& vecItem);                            // ��ð�����������Ʒ��ID
    uint16 GetCharItemCount() { return static_cast<uint16>(m_listItem.size()); }

    bool AddPolishItem(__int64 nItemID);                                            // ���һ��������Ʒ
    SCharItem* GetPolistItemByIndex(short nIndex);                                  // ���������Ʒ����ϸ����
    void RemovePolistItem(__int64 nItemID);                                         // ɾ��һ��������Ʒ
    bool IsPolistItem(__int64 nItemID);                                             // �Ƿ���Ʒ����Ʒ       
    uint16 GetPolistItemCount() { return static_cast<uint16>(m_listPolishItem.size()); }

    void SetItemPackageAccess(uint32 dwPlayerDBID, uint8 chPickLevel);              // ���ð�����ʰȡȨ��
    uint8 GetItemPackageAccess(uint32 dwPlayerDBID);                                // ��ð�����ʰȡȨ��
    bool IsCanViewItemPackage(uint32 dwPlayerDBID);                                 // �Ƿ��ܲ鿴����
    void SetAllCanViewItemPackage();                                                // ����������Ч����ܲ鿴����
    bool IsInPackageAccessList(uint32 dwPlayerDBID);                                // �Ƿ�����Ч����б���
    uint16 GetItemPackageAccessCount() { return static_cast<uint16>(m_vecItemPackageToPlayer.size()); }
    PickAccessVector& GetItemPackageAccessList() { return m_vecItemPackageToPlayer; }

    void SetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID, uint8 chPickLevel); // ���ð�������Ʒ��ʰȡȨ��
    void RemoveItemPickLevel(__int64 nItemID);                                      // ɾ������Ʒ��Ȩ�޹���
    uint8 GetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID);                   // �����ҵ�ʰȡȨ��
    void SetAllCanPickItem(__int64 nItemID);                                        // ����������Ч�����ʰȡ(���ڶ�ɸ�ӻ������ڷ������Ʒ����)

    bool IsCanPickUpItem(__int64 nItemID, uint32 dwPlayerDBID);                     // �Ƿ���ʰȡ�����Ʒ
    bool IsCanAssignItem(__int64 nItemID, uint32 dwPlayerDBID);                     // �Ƿ��ܷ��������Ʒ(һ��ֻ�жӳ�ģʽ�²Ż�����)
   
    void SetCanPickUpAllItem();                                                     // ����������Ч�����ʰȡ�������
    void SetItemHoldByPlayer(__int64 nItemID, uint32 dwPlayerDBID);                 // ���ô���Ʒ���������

    bool IsAllPackageItemBoult(__int64 nItemID);                                    // �����Ʒ�Ƿ����ж�Ա����ɸ����
    bool IsPackageItemAbandon(__int64 nItemID);                                     // �Ƿ������˶������������Ʒ
    bool IsPlayerPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID);            // �������Ƿ񶪹�ɸ����
    void AddPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID, uint16 nNumber); // ��������Ʒ��ҵ�ɸ�ӵ���
    void ClearPackageItemBoult(__int64 nItemID);                                    // ��������Ʒ��ɸ�ӹ���
    uint32 GetMaxPackageItemBoult(__int64 nItemID);                                 // ���ɸ�ӵ����������
    void GetPackageItemBoult(__int64 nItemID, BoultNumberVector& vecBoult);         // ���ĳ��Ʒ��ɸ�ӵ���
    void PackageItemBoultEnd(__int64 nItemID);                                      // ��ɸ�ӽ���,�ж���Ʒ����
    void SetPackageItemBoultWhenTimeOut(__int64 nItemID);                           // ��ʱ,�趨����û�ж�ɸ�ӵ����

    void AddPackageItemBoultTimeOut(__int64 nItemID, uint32 dwTimeOut);             // ��Ӹ���Ʒ��ɸ�ӵĳ�ʱʱ�� 
    void RemovePackageItemBoultTimeOut(__int64 nItemID);                            // ɾ����Ʒ��ɸ�ӵĳ�ʱʱ��
    void CheckPackageItemBoultTimeOut();                                            // �ж϶�ɸ�ӳ�ʱ

    void SetPackageAlreadyBoult(bool bBoult) { m_bPackageAlreadyBoult = bBoult; }   
    bool GetPackageAlreadyBoult() { return m_bPackageAlreadyBoult; }

    void SetPackageAssignType(uint8 chType) { m_chItemAssignType = chType; }
    uint8 GetPackageAssignType() { return m_chItemAssignType; }

    void SetPackageHoldPlayerID(uint32 dwID) { m_dwPackageHoldID = dwID; }
    uint32 GetPackageHoldPlaerID() { return m_dwPackageHoldID; }

    void SetPackageAssignTeamHeaderID(uint32 dwID) { m_dwTeamHeaderID = dwID; }
    uint32 GetPackageAssignTeamHeaderID() { return m_dwTeamHeaderID; }  

    void SetPackageFristViewTimeOut(uint32 dwTimeOut) { m_dwFristPackageViewTimeOut = dwTimeOut; }
    uint32 GetPackageFristViewTimeOut() { return m_dwFristPackageViewTimeOut; }

    void SetPackageViewEnd() { m_bPackageViewEnd = true; }
    bool GetPackageViewEnd() { return m_bPackageViewEnd; }

    void SetPackageHoldType( uint8 chValue ) { m_chHoldType = chValue; }
    uint8 GetPackageHoldType() { return m_chHoldType; }
    BOOL IsPackageHoldByAll() { return m_chHoldType == eIHT_All; }
 
    void AddPackageViewTime(uint32 dwPlayerID);                                     // ��Ӳ鿴����������ʱ��,һ��Ϊ2��
    bool IsOverPackageViewLastTime(uint32 dwPlayerID);                              // �Ѿ������ٴβ鿴����ʱ��

    void ChangePackageAccessAllCanView();                                           // ʹ����ÿ����Ч��Ա���ܲ鿴
    void PackageItemAccessReq(GamePlayer* pPlayer);                                 // ��������е���ƷȨ�� 
    void SendMsgToAllPackageEffectPlayer(Msg* pMsg, uint32 dwExceptPlayerID = -1);  // ������Ϣ�����������Ч�����
    bool SendMsgToPackageTeamHeaderPlayer(Msg* pMsg);                               // ������Ϣ���ӳ�����,�������ʧ��,��Ϊ�ӳ���ʱ�����Ϸ���Ҫ��,����Ҷ�ɸ��
    
    void    SetDropItemType( uint8 uchType ) { m_nDropItemType = uchType; }
    uint8   GetDropItemType() const { return m_nDropItemType; }

    //////////////////////////////////////////////////////////////////////////////////////////
    void SetPackageDropType( uint16 uchType ) { m_uchDropType = uchType; }
    uint16 GetPackageDropType() const { return m_uchDropType; }
    //////////////////////////////////////////////////////////////////////////////////////////

	void SetbFirstEnterSight( bool bFlag ) { m_bFirstEnterSight = bFlag; }			// �Ƿ��һ�ν�����Ұ
	bool GetbFirstEnterSight() { return m_bFirstEnterSight; }

	void SetDropMonsterID(int nID) { m_nMonsterID = nID; }
	int GetDropMonsterID() { return m_nMonsterID; }

protected:
    bool m_BePickFlag;       // �жϸõ����Ƿ��Ѿ�������������

    SCharItem m_item;
    int m_iMasterGroupID;
    int m_iMasterNpcID;      // ���ߵ�����

    DWORD m_dwDropBeginTime; // ���ߵ���ģ���ʼʱ��
    DWORD m_dwDeathTime;     // ��Ʒ�����ʱ�䶪�����ϲ��ܣ����Զ���ʧ
    bool  m_bTaskItem;       // �Ƿ���������Ʒ
    bool  m_bAdscription_teamHeader;

    SBornDelay m_borndelay;

    DWORD TimePeopleOfTeam;  // �����и��˵ı���ʱ�� Ϊ��Ʒ����ʱ+40�� 40���Ժ���Ʒ�������������
                            
                             // ��������id ����:����Ա��ʼ��ɸ��ʱ ��Ʒ����ȷ������ �������ö���id��
    int   HoldGroupId;       // ���: 1>��Ҷ�ѡ���� ��������ѡ�� ��ѡ����ȷ������ ����m_iMasterNpcID �� m_iMasterGroupID
                             //       2>��Ҷ������� ���� m_iMasterGroupID 
                             //       3>��Ҷ�������ͻ��˽��� 20��û�з�Ӧ�Ļ� ϵͳĬ������Ϊ ���鹫��ģʽ ������ m_iMasterGroupID

    std::list<SCharItem> m_listItem;            // �����е���Ʒ
    std::list<__int64> m_listPolishItem;        // �����е�������Ʒ(��Ҫ��ɸ�ӻ��߶ӳ�������������)
    PickLevelMap m_mapItemToPlayer;             // ������ÿ����Ʒ��Ӧ��ҵ�Ȩ��
    PickAccessVector m_vecItemPackageToPlayer;  // ���������Ӧ��ҵ�Ȩ��

    bool m_bPackageAlreadyBoult;                // �Ƿ��Ѿ������ɸ����Ϸ��
    uint32 m_dwFristPackageViewTimeOut;         // ��һ�δ򿪵�ʱ��, 30���û�رհ���,��Ϊ��ʱ, �����˶���ʰȡ
    bool m_bPackageViewEnd;                     // �Ѿ���ӵ���߲鿴��������

    BoultTimeMap m_mapBoultTime;                // ����ɸ����Ϣ��ʱ��������ʱ
    BoultNumberMap m_mapBoultNumber;            // ɸ�ӵ�������

    uint8 m_chItemAssignType;                   // ��������ģʽ, ���ﱣ��,�Ͳ���ȥ�Ӷ���������
    uint32 m_dwPackageHoldID;                   // ���������߶ӳ�����ģʽ��, ֻ�е�ӵ�дΰ�������Ҵ��Ժ�����Ҳ���ʰȡ
    uint32 m_dwTeamHeaderID;                    // �ӳ�����ģʽ��, ����ӳ���ID,(�п��ܻ�ת�ƶӳ�, һ�������ID��������Ʒ����)
    
    //��Ԥ��
    uint8 m_chHoldType;                         // ����, �����Ǹ���, ����, ���߹���,���߸���
    uint32 m_nHoldID;                           // ����ĳID

    ViewTimeMap m_mapVewTime;                   // ��¼ÿ���˴򿪰�����ʱ��(��ֹһֱ�����,һֱ����Ϣ)
    
    uint8  m_nDropItemType;                     // ��Ʒ���䷽ʽ

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint16 m_uchDropType;                        // Ϊ�˴�log����һ��Type

	bool   m_bFirstEnterSight;					// �Ƿ��һ�ν�����Ұ
	int	   m_nMonsterID;						// �ĸ��������
};

#endif //__GAMESERVER_ITEMCHARACTER_H__
