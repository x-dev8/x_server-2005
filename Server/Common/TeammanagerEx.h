#ifndef __TEAMMANAGER_H__
#define __TEAMMANAGER_H__

/************************************************************************

    一个团最多24个人, 包括4个小队,    一个小队6个人,

************************************************************************/
#include "GlobalDef.h"
#include "mempool\memory_pool.h"
#include "Mutex.h"

struct Msg;
class GameStage;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TeamEx : public Common::TObject_pool< TeamEx >
{
public:
    struct TeamMember // 队员属性
    {
        TeamMember() { Clear(); }
        ~TeamMember(){ }
        inline void Clear()
        {
            dwDataBaseId = ErrorUnsignedLongID;
            strName.clear();
            stManipleId = 0;            // 默认在第一个小队
            bManipleHeader = false;
        }

        bool IsError() { return ( dwDataBaseId == ErrorUnsignedLongID || strName.empty() ); }

        TeamMember( const TeamMember& xTeamMember )
        {
            *this = xTeamMember;
        }

        inline TeamMember& operator = ( const TeamMember& xTeamMember )
        {
            if (this != &xTeamMember)
            {
                dwDataBaseId   = xTeamMember.dwDataBaseId;
                strName        = xTeamMember.strName;
                stManipleId    = xTeamMember.stManipleId;
                bManipleHeader = xTeamMember.bManipleHeader;

                nFaceID        = xTeamMember.nFaceID;
                nHairID        = xTeamMember.nHairID;
                chProfession   = xTeamMember.chProfession;
                chSex          = xTeamMember.chSex;
                stLevel        = xTeamMember.stLevel;
            }

            return *this;
        }

        inline bool operator == ( uint32 dwDataBaseId) { return this->dwDataBaseId == dwDataBaseId; }
        inline bool operator == ( const char* pszName ) { return strName == pszName; }

        void SetID( uint32 dwID )             { dwDataBaseId = dwID; }
        void SetName( const char* pszName )   { strName = pszName; }
        void SetManipleID( short nID )        { stManipleId = nID; }
        void SetManipleHeader( bool bValue )  { bManipleHeader = bValue; }
        void SetFaceID( int nValue )          { nFaceID = nValue;}
        void SetHairID( int nValue )          { nHairID = nValue; }
        void SetProfession( uint8 chValue )   { chProfession = chValue; }
        void SetSex( uint8 chValue )          { chSex = chValue; }
        void SetLevel( uint16 stValue )       { stLevel = stLevel; }

        const uint32 GetMemberID() const      { return dwDataBaseId; }
        const char*  GetName() const          { return strName.c_str(); }
        const short  GetManipleID() const     { return stManipleId; }
        const bool   GetManipleHeader() const { return bManipleHeader; }
        const int    GetFaceID() const        { return nFaceID; }
        const int    GetHairID() const        { return nHairID; }
        const uint8  GetProfession() const    { return chProfession; }
        const uint8  GetSex() const           { return chSex; }
        const uint16 GetLevel() const         { return stLevel; }

    private:
        DWORD dwDataBaseId;                 // 队员ID
        std::string strName;                // 队员名字
        short stManipleId;                  // 所在小队的Id
        bool bManipleHeader;

        int nFaceID;
        int nHairID;
        uint8 chProfession;
        uint8 chSex;
        uint16 stLevel;
    };

public:
    TeamEx();
    ~TeamEx();

    inline void SetTeamSessionID(DWORD dwSessionId) { m_dwSessionId = dwSessionId; }
    inline DWORD GetTeamSessionID() { return m_dwSessionId; }
    
    uint32 GetTeamHeaderID() { return m_dwTeamHeaderID; }
    void SetTeamHeaderID( uint32 dwID) { m_dwTeamHeaderID = dwID; }

    inline bool IsCorpsTeam() { return m_bCorps; }                           // 是否是团
    inline void SetCorpsTeam(bool bCorps) { m_bCorps = bCorps; }
    bool UpdateTeamToCorps();                                                // 将队伍扩充到团
    inline unsigned int TeamMemberCount() { return static_cast<unsigned int>(m_listTeamMember.size()); }
    bool IsTeamFull();
    bool IsInTeam(DWORD dwDataBaseId);                            //是否在队伍中    
    bool IsManipleHeader(DWORD dwDataBaseId);                    //是否是小队长
    short GetManiple(DWORD dwDataBaseId);
    bool IsTeamHeader(DWORD dwDataBaseId);                        //是否是大队长(团长)
    DWORD GetTeamHeaderDataBaseId();                            //获得团长ID

    bool SetTeamHeader(DWORD dwDataBaseId, bool bQuickUpdate = true);                    //设置大队长
    bool SetManipleHeader(DWORD dwDataBaseId);                                            //设置小队长
    bool ChangeTeamMemberManiple(DWORD dwDataBaseId, short stManipleId);                //更换队员小队id
    bool ExChangeTeamMeberManiple(DWORD dwSrcDataBaseId, DWORD dwDestDataBaseId);        //队员小队Id 互换

    TeamMember* GetManipleHeader(short stManipleId);                                    //获得某小队的小队长
    TeamMember* GetTeamMember(DWORD dwDataBaseId);                                        //
    TeamMember* GetTeamHeader();
    TeamMember* GetTeamMemberByIndex(unsigned int nIndex);                //索引队员
    DWORD GetTeamMemberDataBaseIdByIndex(unsigned int nIndex);

    unsigned short GetTeamTotalLevel();

    bool IsAllTeamMemberHaveQuest( int nQuestID, unsigned long &dwID );
    bool IsAllTeamMemberGreaterMapLevel(unsigned int nLevel);
    void GetTeamMemberInMapArea(unsigned int nMapID, float fX, float fY, std::vector<uint32>& vecTeamMemberID);
    unsigned int GetTeamMemberCountInMap(unsigned int nMapId, float fX, float fY);        //某个地图内的队员个数
    unsigned int GetTeamMemberLevelDistance(unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel);
    float GetTeamExpPercent(unsigned int nTeamCount, bool bIsEcType);           //获得队伍经验百分比
    bool CallAllTeamPlayerFlyToMapReq(unsigned int nMapID, float fX, float fY, float fDir = 0.0f);
    bool CallAllTeamPlayerChangeToMap( GameStage* pGameStage, int nTileX, int nTileY, float dir );

    DWORD GetCurrentAssignIndex();                                            //获得物品分配的队员

    inline void SetAssignModeType(uint8 nModeType) { m_nAssignModeType = nModeType; }        //设置分配模式
    inline uint8 GetAssignModeType() { return m_nAssignModeType; }                        //获得设置分配模式

    void SetTeamAssiginItemLevel(uint8 chItemLevel) { m_chAssignItemLevel = chItemLevel; }
    uint8 GetTeamAssiginItemLevel() { return m_chAssignItemLevel; }
    
    bool AddTeamMember( TeamMember& xMember, bool bIsTeamHeader );                                // 添加队员
    bool RemoveTeamMember(DWORD dwDataBaseId);                                                    // 删除队员
    bool DisbandTeam();                                                                           // 解散队伍

    void SendChatMessageToTeamMember(const char* chat, DWORD dwExcept = ErrorUnsignedLongID, bool bSendToCenter = true);                    //发送聊天给全队  (除去stExcept id会员)
    void SendMessageToTeamMember(Msg *pMsg,DWORD dwExcept = ErrorUnsignedLongID, bool bCenterServerAck = true);                                //给所有队员发送消息
    void SendMemberInfoToTeamMember(Msg *pMsg, DWORD dwExcept, bool bSendToCenter = true);
    bool RunTeamUpdate(bool bQuickUpdate = false);                                                                        //更新TeamEx信息

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned long IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration );
    bool RecordTeamTime( int nVarId );
    void ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    void UpdateManipleCount(short stManipleId, bool bAdd = true);                            //添加小队队员数量
    unsigned int GetManipleCount(short stManipleId);                                        //获得小队队员数量
    bool IsManipleFull(short stManipleId);

private:
    uint32 m_dwNextUpdateSelfTime;                              // 检查队伍时间
    uint32 m_dwStopUpdateTeamMemberTime;                        // 间隔多少时间停止更新队员信息
    uint32 m_dwSessionId;                                       // 跨服间使用的sessionid
    bool m_bCorps;                                              // 是否是团
    uint8 m_nAssignModeType;                                    // 当前队伍的分配模式

    uint32 m_dwTeamHeaderID;                                    // 队长的 ID
    uint32 m_dwNextUpdateTime;                                  // 下次TeamEx更新时间

    uint32 m_nAssignIndex;                                      // 该次掉落物品分配到某个队员身上 (队伍的索引)
    
    std::list<TeamMember> m_listTeamMember;                     // 队员列表
    std::map<short, unsigned int> m_mapManipleCount;            // 4个小队,每个小队的人数
    DWORD m_dwNextUpdateToCenterTime;                           // 下次同步给centerserver 的时间
    uint8 m_chAssignItemLevel;                                  // 队伍分配时,物品的等级,(>=该等级,需要丢筛子来决定物品归属谁)

public:
    typedef std::list<TeamMember>::iterator TeamIter;
    typedef std::map<short, unsigned int>::iterator ManipleCountIter;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define theTeamManager TeamManagerEx::Instance()

class TeamManagerEx
{
protected:
    TeamManagerEx();

public:
    static TeamManagerEx& Instance()
    {
        static TeamManagerEx s_TeamManger;
        return s_TeamManger;
    }
    
    ~TeamManagerEx();

    TeamEx* GetTeam(uint32 dwTeamSessionID);
    TeamEx* CreateTeam( uint32 dwTeamSessionID, uint8 chAssignMode, uint8 chAssignItemLevel );

    bool RemoveFromTeam( uint32 dwSessionID, uint32 dwDataBaseID, bool bKick = false );
    bool KickMemberFromTeam( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwTeamMemeberId );
    bool DisbandTeam( uint32 dwSessionID , uint32 dwTeamHeaderId );                                //解散队伍
    bool ExChangeTeamMeberManiple( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwSrcId, uint32 dwDestId );
    bool ChangeTeamMemberManiple( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwTeamMemberId, short stManipleId );

    bool IsTeamHeader( uint32 dwSessionID, uint32 dwTeamMemberId );
    bool IsManipleHeader( uint32 dwSessionID, uint32 dwTeamMemberId);

    bool SetManipleHeader( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwManipleId );
    bool SetCorpsTeam( uint32 dwSessionID, uint32 dwTeamHeaderId);

    void RunTeamManagerUpdate();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool AddTeam( uint32 dwSessionID, TeamEx* pTeam );
    bool ReleaseTeam( uint32 dwSessionID );        
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


private:
    typedef std::map< uint32, TeamEx* > TeamMap;
    typedef TeamMap::iterator TeamMapIter;
    TeamMap m_mapRunTeam;
};

#endif
