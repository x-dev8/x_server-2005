/********************************************************************
    Filename:     GameZone.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEZONE_H__
#define __GAMESERVER_GAMEZONE_H__

#include "GlobalDef.h"
#include "DataBuffer.h"

class GamePlayer;

// 触发区块类
class GameZone : INHERIT_POOL_PARAM( GameZone, 10 )
{
public:
    enum EConstDefine
    {
        constMaxHideMonsters = 50                      // 区块内最大的隐藏怪
    };

public:
    DECLARE_POOL_FUNC( GameZone )

    GameZone();
    virtual ~GameZone();
        
    int* GetZoneCoveredArea(){ return m_pstCoveredArea; }  // 获取Zone覆盖的Area区域
    
    void ClearCurPlayerList();
    void AddCurPlayer2List(DWORD dwID);
    void UpdateLastPlayerList();

    void SetCoveredAreaCount( int stCount){ m_stCoveredAreaCount = stCount; }
    int  GetCoveredAreaCount(){ return m_stCoveredAreaCount; }

    void SetCoveredArea( int i, int stwhich )
    { 
        if (i >= 0 && i < dr_zoneMaxCoveredArea)
        {
            m_stCoveredArea[i] = stwhich; 
        }
    }

    int GetCoveredArea( int i )
    {
        if (i < 0|| i>= dr_zoneMaxCoveredArea)
            return -1;
        return m_stCoveredArea[i]; 
    }

    void SetOutZone( RECT OutZone ){ m_OutZone = OutZone; }
    void SetInZone( RECT InZone ){ m_InZone = InZone; }
    RECT GetOutZone(){ return m_OutZone; }
    RECT GetInZone(){ return m_InZone; }

    void SetCoveredAreaCharCount( int CharCount ){ m_stCoveredAreaCharCount = CharCount; }
    int  GetCoveredAreaCharCount(){ return m_stCoveredAreaCharCount; }

    void SetCoveredAreaHasPlayer( bool bIsHasPlayer ){ m_bCoveredAreaHasPlayer = bIsHasPlayer; }
    bool GetCoveredAreaHasPlayer(){ return m_bCoveredAreaHasPlayer; }

    void  SetIntoAreaScript( const char* sz );
    void  SetLeaveAreaScript( const char* sz );

    void  SetZoneName( const char* sz ){ m_strZoneName = sz; }
    const char* GetZoneName(){ return m_strZoneName.c_str(); }

    void SetMapXY( int x, int y ) { m_nMapX = x; m_nMapY = y; }
    int  GetMapX()                { return m_nMapX; }
    int  GetMapY()                { return m_nMapY; }
 
    void SetZoneID( int nID ) { m_nZoneID = nID; }
    void SetZonePKMode( int nPKMode ) { m_nPKMode = nPKMode;}
	bool IsPrivateShopEnable()	{ return m_bPrivateShopEnable; }
    void SetPrivateShopEnable( bool bPrivateShopEnable );
    //void SetCanFreePk( bool bflag ) { m_bIsCanFreePK = bflag; }

    int GetZonePKMode() { return m_nPKMode; }

	void SetZoneCanDuel( bool bCanDuel ) { m_bCanDuel = bCanDuel;}
	bool GetZoneCanDuel() { return m_bCanDuel; }

    // 添加ObjectId
    bool AddCharacterToList( GameObjectId dwID );

    // 删除ObjectId
    bool DelCharacterFromList( GameObjectId dwID );

    // 清空ObjectId
    void ClearCharacterList(){ _objectIds.clear(); }

    // 获得隐藏怪的列表
    GameObjectIdTPL(constMaxHideMonsters)* GetHideMonsterIndexTable() 
    { return &m_HideMonsterIndexTable; }

    // 添加隐藏怪到隐藏怪列表中
    BOOL AddHideMonsterToList( int nID );

    // 遍历得到Id
    GameObjectId GetNextCurPlayerBId( bool bFirst );

    // 遍历得到Id
    GameObjectId GetNextLastPlayerBId( bool bFirst );

private:
    bool PlayerEnterZone( GamePlayer* pPlayer );
    bool PlayerLeaveZone( GamePlayer* pPlayer );

private:
    int         m_nZoneID;
    int         m_stCoveredArea[ dr_zoneMaxCoveredArea ];
    std::string m_strIntoAreaScript;  // 进入
    std::string m_strLeaveAreaScript;
    std::string m_strZoneName;
    int         m_nIntoAreaVMId;
    int         m_nLeaveAreaVMId;
    bool        m_bAreaStartup;
    int         m_nPKMode;
	bool        m_bCanDuel;
    bool        m_bPrivateShopEnable;
    RECT        m_OutZone;
    RECT        m_InZone;
    int         m_stCoveredAreaCount;
    int         m_stCoveredAreaCharCount;
    bool        m_bCoveredAreaHasPlayer;
    int         m_nMapX;
    int         m_nMapY;
    //bool        m_bIsCanFreePK;
    int*        m_pstCoveredArea;

    GameObjectIDSet                       _objectIds             ; // player Npc Monster Item 等
    GameObjectIDSetItr                    _curObjectIdItr        ; // 光标
    GameObjectIdTPL(constMaxHideMonsters) m_HideMonsterIndexTable; // 隐藏怪物的索引

    bool                           _bUpdateInOut          ; // 是否更新进出Zone的Id信息
    GameObjectIDSet                _curPlayerIds          ; // 当前player Npc Monster Item 等
    GameObjectIDSetItr             _curPlayerIdItr        ; // 光标
    GameObjectIDSet                _lastPlayerIds         ; // 上一次player Npc Monster Item 等
    GameObjectIDSetItr             _lastPlayerIdItr       ; // 光标
};

//////////////////////////////////////////////////////////////////////////
//inline
inline bool GameZone::AddCharacterToList( GameObjectId dwID )
{
    return _objectIds.insert( dwID ).second;
}

inline void GameZone::SetPrivateShopEnable( bool bPrivateShopEnable )
{
    m_bPrivateShopEnable = bPrivateShopEnable;
    if ( m_bPrivateShopEnable )
    {
        _bUpdateInOut = true;
    }
}

#endif // __GAMESERVER_GAMEZONE_H__
