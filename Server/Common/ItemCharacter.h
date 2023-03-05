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
{ // 物品角色
public:    
    enum EPickResult
    {
        eResultSuccess = 0       // 成功
        ,eResultNotMasterGruop   // 不是这个队的
        ,eResultNotMasterPlayer  // 不是玩家的
        ,eResultBeenPick         // 已经被捡
        ,eResultTaskItem         // 任务物品
        ,eResultUnknow
        ,eResultIsGroupNotPlayer // 是本队的但不是你的
        ,eResultNotTeamHeader    // 你不是队长 
    };

    enum enumConstPublic
    {
        const_drop_delay     = 2,     // 道具的延迟显示 second
        PackageViewTimeOut   = 40000, // 查看包裹超时时间
        ServerBoultTimeOut   = 32000, // 丢筛子的超时时间 服务端 32秒
        ClientBoultTimeOut   = 30000, // 丢筛子的超时时间 客户端 30秒
        PackageViewSpaceTime = 2000,  // 点击查看包裹回消息的间隔时间            
    };

    struct SBornDelay
    {
        short stBornDelay;
        unsigned long dwLastCheckTime;
    };

    struct SPlayerBoultNumber
    {
        uint32 dwPlayerID;
        uint16 nBoultNumber;            //筛子点数

        bool operator == (uint32 dwID) { return dwPlayerID == dwID; }
        friend bool operator > (const SPlayerBoultNumber& xLeft, const SPlayerBoultNumber& xRight)
        {
            return xLeft.nBoultNumber > xRight.nBoultNumber;  //点数相等返回false
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

    // 不能被攻击
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
                    怪物是一个没有队伍的人的 归属为这个人
                else if( m_iMasterGroupID == -1 && m_iMasterGroupID != -1 ) ----
                    怪物归属为整个队伍，此队伍的人都可以pick
                else if( m_iMasterGroupID != -1 && m_iMasterGroupID != -1 )-----
                    目前怪物归属为这个队伍的这个人 if这个人在40秒内不pick的话，此物品将归属为此队伍
                else if( m_iMasterGroupID == -1 && m_iMasterGroupID == -1 )
                    目前还不能确定物品的归属 
                    1>大家都没有放弃的话 在拾取中的随即
                    2>大家都放弃的话 物品归属将 变更为 队伍公共模式    
                    3>有人客户端20还没有选择的话 系统默认为放弃 大家都放弃的话 物品归属将变更为队伍公共模式*/
   
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
    void SetPackagePolistDeathTime();                                               // 有优质物品时, 道具消失时间
    void SetPackageNormalDeathTime();                                               // 无优质物品以后道具消失时间

    bool AddCharItem( SCharItem& xItem );                    // 添加一个道具到包裹中
    void RemoveCharItem(__int64 nItemID, uint16 nItemCount);                        // 从包裹中删除一个道具
    SCharItem* GetCharItem(__int64 nItemID);                                        // 从包裹中获得一个道具
    SCharItem* GetCharItemById(uint16 nItemID);                                     // 从包裹中获得一个道具
    SCharItem* GetCharItemByIndex(short nIndex);                                    // 按索引获得一个道具
    void GetCharItemList(std::vector<__int64>& vecItem);                            // 获得包裹中所有物品的ID
    uint16 GetCharItemCount() { return static_cast<uint16>(m_listItem.size()); }

    bool AddPolishItem(__int64 nItemID);                                            // 添加一个优质物品
    SCharItem* GetPolistItemByIndex(short nIndex);                                  // 获得优质物品的详细属性
    void RemovePolistItem(__int64 nItemID);                                         // 删除一个优质物品
    bool IsPolistItem(__int64 nItemID);                                             // 是否是品质物品       
    uint16 GetPolistItemCount() { return static_cast<uint16>(m_listPolishItem.size()); }

    void SetItemPackageAccess(uint32 dwPlayerDBID, uint8 chPickLevel);              // 设置包裹的拾取权限
    uint8 GetItemPackageAccess(uint32 dwPlayerDBID);                                // 获得包裹的拾取权限
    bool IsCanViewItemPackage(uint32 dwPlayerDBID);                                 // 是否能查看包裹
    void SetAllCanViewItemPackage();                                                // 设置所有有效玩家能查看包裹
    bool IsInPackageAccessList(uint32 dwPlayerDBID);                                // 是否在有效玩家列表中
    uint16 GetItemPackageAccessCount() { return static_cast<uint16>(m_vecItemPackageToPlayer.size()); }
    PickAccessVector& GetItemPackageAccessList() { return m_vecItemPackageToPlayer; }

    void SetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID, uint8 chPickLevel); // 设置包裹中物品的拾取权限
    void RemoveItemPickLevel(__int64 nItemID);                                      // 删除该物品的权限关联
    uint8 GetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID);                   // 获得玩家的拾取权限
    void SetAllCanPickItem(__int64 nItemID);                                        // 设置所有有效玩家能拾取(正在丢筛子或者正在分配的物品除外)

    bool IsCanPickUpItem(__int64 nItemID, uint32 dwPlayerDBID);                     // 是否能拾取这个物品
    bool IsCanAssignItem(__int64 nItemID, uint32 dwPlayerDBID);                     // 是否能分配这个物品(一般只有队长模式下才会有用)
   
    void SetCanPickUpAllItem();                                                     // 设置所有有效玩家能拾取这个包裹
    void SetItemHoldByPlayer(__int64 nItemID, uint32 dwPlayerDBID);                 // 设置此物品归属于玩家

    bool IsAllPackageItemBoult(__int64 nItemID);                                    // 这个物品是否所有队员都丢筛子了
    bool IsPackageItemAbandon(__int64 nItemID);                                     // 是否所有人都放弃了这个物品
    bool IsPlayerPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID);            // 这个玩家是否丢过筛子了
    void AddPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID, uint16 nNumber); // 添加这个物品玩家的筛子点数
    void ClearPackageItemBoult(__int64 nItemID);                                    // 清除这个物品的筛子关联
    uint32 GetMaxPackageItemBoult(__int64 nItemID);                                 // 获得筛子点数最大的玩家
    void GetPackageItemBoult(__int64 nItemID, BoultNumberVector& vecBoult);         // 获得某物品的筛子点数
    void PackageItemBoultEnd(__int64 nItemID);                                      // 丢筛子结束,判断物品归属
    void SetPackageItemBoultWhenTimeOut(__int64 nItemID);                           // 超时,设定所有没有丢筛子的玩家

    void AddPackageItemBoultTimeOut(__int64 nItemID, uint32 dwTimeOut);             // 添加该物品丢筛子的超时时间 
    void RemovePackageItemBoultTimeOut(__int64 nItemID);                            // 删除物品丢筛子的超时时间
    void CheckPackageItemBoultTimeOut();                                            // 判断丢筛子超时

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
 
    void AddPackageViewTime(uint32 dwPlayerID);                                     // 添加查看包裹的限制时间,一般为2秒
    bool IsOverPackageViewLastTime(uint32 dwPlayerID);                              // 已经过了再次查看包裹时间

    void ChangePackageAccessAllCanView();                                           // 使包裹每个有效成员都能查看
    void PackageItemAccessReq(GamePlayer* pPlayer);                                 // 请求包裹中的物品权限 
    void SendMsgToAllPackageEffectPlayer(Msg* pMsg, uint32 dwExceptPlayerID = -1);  // 发送消息给这个包裹有效的玩家
    bool SendMsgToPackageTeamHeaderPlayer(Msg* pMsg);                               // 发送消息给队长分配,如果发送失败,认为队长此时不符合分配要求,让玩家丢筛子
    
    void    SetDropItemType( uint8 uchType ) { m_nDropItemType = uchType; }
    uint8   GetDropItemType() const { return m_nDropItemType; }

    //////////////////////////////////////////////////////////////////////////////////////////
    void SetPackageDropType( uint16 uchType ) { m_uchDropType = uchType; }
    uint16 GetPackageDropType() const { return m_uchDropType; }
    //////////////////////////////////////////////////////////////////////////////////////////

	void SetbFirstEnterSight( bool bFlag ) { m_bFirstEnterSight = bFlag; }			// 是否第一次进入视野
	bool GetbFirstEnterSight() { return m_bFirstEnterSight; }

	void SetDropMonsterID(int nID) { m_nMonsterID = nID; }
	int GetDropMonsterID() { return m_nMonsterID; }

protected:
    bool m_BePickFlag;       // 判断该道具是否已经被，拿起来了

    SCharItem m_item;
    int m_iMasterGroupID;
    int m_iMasterNpcID;      // 道具的主人

    DWORD m_dwDropBeginTime; // 道具掉落的，开始时间
    DWORD m_dwDeathTime;     // 物品如果长时间丢到地上不管，会自动消失
    bool  m_bTaskItem;       // 是否是任务物品
    bool  m_bAdscription_teamHeader;

    SBornDelay m_borndelay;

    DWORD TimePeopleOfTeam;  // 队伍中个人的保护时间 为物品掉落时+40秒 40秒以后物品将属于这个队伍
                            
                             // 保留队伍id 需求:当队员开始打筛子时 物品归属确定不了 不能设置队伍id，
    int   HoldGroupId;       // 情况: 1>大家都选择了 或者有人选择 在选择中确定归属 设置m_iMasterNpcID 和 m_iMasterGroupID
                             //       2>大家都放弃了 设置 m_iMasterGroupID 
                             //       3>大家都不点击客户端界面 20秒没有反应的话 系统默认设置为 队伍公共模式 即设置 m_iMasterGroupID

    std::list<SCharItem> m_listItem;            // 包裹中的物品
    std::list<__int64> m_listPolishItem;        // 包裹中的优质物品(需要丢筛子或者队长分配来决定的)
    PickLevelMap m_mapItemToPlayer;             // 包裹中每个物品对应玩家的权限
    PickAccessVector m_vecItemPackageToPlayer;  // 包裹本身对应玩家的权限

    bool m_bPackageAlreadyBoult;                // 是否已经玩过丢筛子游戏了
    uint32 m_dwFristPackageViewTimeOut;         // 第一次打开的时间, 30秒后还没关闭包裹,认为超时, 其他人都能拾取
    bool m_bPackageViewEnd;                     // 已径被拥有者查看过包裹了

    BoultTimeMap m_mapBoultTime;                // 发送筛子消息的时间用来超时
    BoultNumberMap m_mapBoultNumber;            // 筛子点数关联

    uint8 m_chItemAssignType;                   // 保存分配的模式, 这里保存,就不再去从队伍中找了
    uint32 m_dwPackageHoldID;                   // 队伍分配或者队长分配模式下, 只有当拥有次包裹的玩家打开以后别的玩家才能拾取
    uint32 m_dwTeamHeaderID;                    // 队长分配模式下, 保存队长的ID,(有可能会转移队长, 一样由这个ID来分配物品归属)
    
    //先预留
    uint8 m_chHoldType;                         // 类型, 可能是个人, 队伍, 后者公会,或者更多
    uint32 m_nHoldID;                           // 属于某ID

    ViewTimeMap m_mapVewTime;                   // 记录每个人打开包裹的时间(防止一直点鼠标,一直发消息)
    
    uint8  m_nDropItemType;                     // 物品掉落方式

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint16 m_uchDropType;                        // 为了打log设置一个Type

	bool   m_bFirstEnterSight;					// 是否第一次进入视野
	int	   m_nMonsterID;						// 哪个怪物掉落
};

#endif //__GAMESERVER_ITEMCHARACTER_H__
