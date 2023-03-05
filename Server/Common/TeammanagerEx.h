#ifndef __TEAMMANAGER_H__
#define __TEAMMANAGER_H__

/************************************************************************

    һ�������24����, ����4��С��,    һ��С��6����,

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
    struct TeamMember // ��Ա����
    {
        TeamMember() { Clear(); }
        ~TeamMember(){ }
        inline void Clear()
        {
            dwDataBaseId = ErrorUnsignedLongID;
            strName.clear();
            stManipleId = 0;            // Ĭ���ڵ�һ��С��
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
        DWORD dwDataBaseId;                 // ��ԱID
        std::string strName;                // ��Ա����
        short stManipleId;                  // ����С�ӵ�Id
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

    inline bool IsCorpsTeam() { return m_bCorps; }                           // �Ƿ�����
    inline void SetCorpsTeam(bool bCorps) { m_bCorps = bCorps; }
    bool UpdateTeamToCorps();                                                // ���������䵽��
    inline unsigned int TeamMemberCount() { return static_cast<unsigned int>(m_listTeamMember.size()); }
    bool IsTeamFull();
    bool IsInTeam(DWORD dwDataBaseId);                            //�Ƿ��ڶ�����    
    bool IsManipleHeader(DWORD dwDataBaseId);                    //�Ƿ���С�ӳ�
    short GetManiple(DWORD dwDataBaseId);
    bool IsTeamHeader(DWORD dwDataBaseId);                        //�Ƿ��Ǵ�ӳ�(�ų�)
    DWORD GetTeamHeaderDataBaseId();                            //����ų�ID

    bool SetTeamHeader(DWORD dwDataBaseId, bool bQuickUpdate = true);                    //���ô�ӳ�
    bool SetManipleHeader(DWORD dwDataBaseId);                                            //����С�ӳ�
    bool ChangeTeamMemberManiple(DWORD dwDataBaseId, short stManipleId);                //������ԱС��id
    bool ExChangeTeamMeberManiple(DWORD dwSrcDataBaseId, DWORD dwDestDataBaseId);        //��ԱС��Id ����

    TeamMember* GetManipleHeader(short stManipleId);                                    //���ĳС�ӵ�С�ӳ�
    TeamMember* GetTeamMember(DWORD dwDataBaseId);                                        //
    TeamMember* GetTeamHeader();
    TeamMember* GetTeamMemberByIndex(unsigned int nIndex);                //������Ա
    DWORD GetTeamMemberDataBaseIdByIndex(unsigned int nIndex);

    unsigned short GetTeamTotalLevel();

    bool IsAllTeamMemberHaveQuest( int nQuestID, unsigned long &dwID );
    bool IsAllTeamMemberGreaterMapLevel(unsigned int nLevel);
    void GetTeamMemberInMapArea(unsigned int nMapID, float fX, float fY, std::vector<uint32>& vecTeamMemberID);
    unsigned int GetTeamMemberCountInMap(unsigned int nMapId, float fX, float fY);        //ĳ����ͼ�ڵĶ�Ա����
    unsigned int GetTeamMemberLevelDistance(unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel);
    float GetTeamExpPercent(unsigned int nTeamCount, bool bIsEcType);           //��ö��龭��ٷֱ�
    bool CallAllTeamPlayerFlyToMapReq(unsigned int nMapID, float fX, float fY, float fDir = 0.0f);
    bool CallAllTeamPlayerChangeToMap( GameStage* pGameStage, int nTileX, int nTileY, float dir );

    DWORD GetCurrentAssignIndex();                                            //�����Ʒ����Ķ�Ա

    inline void SetAssignModeType(uint8 nModeType) { m_nAssignModeType = nModeType; }        //���÷���ģʽ
    inline uint8 GetAssignModeType() { return m_nAssignModeType; }                        //������÷���ģʽ

    void SetTeamAssiginItemLevel(uint8 chItemLevel) { m_chAssignItemLevel = chItemLevel; }
    uint8 GetTeamAssiginItemLevel() { return m_chAssignItemLevel; }
    
    bool AddTeamMember( TeamMember& xMember, bool bIsTeamHeader );                                // ��Ӷ�Ա
    bool RemoveTeamMember(DWORD dwDataBaseId);                                                    // ɾ����Ա
    bool DisbandTeam();                                                                           // ��ɢ����

    void SendChatMessageToTeamMember(const char* chat, DWORD dwExcept = ErrorUnsignedLongID, bool bSendToCenter = true);                    //���������ȫ��  (��ȥstExcept id��Ա)
    void SendMessageToTeamMember(Msg *pMsg,DWORD dwExcept = ErrorUnsignedLongID, bool bCenterServerAck = true);                                //�����ж�Ա������Ϣ
    void SendMemberInfoToTeamMember(Msg *pMsg, DWORD dwExcept, bool bSendToCenter = true);
    bool RunTeamUpdate(bool bQuickUpdate = false);                                                                        //����TeamEx��Ϣ

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned long IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration );
    bool RecordTeamTime( int nVarId );
    void ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    void UpdateManipleCount(short stManipleId, bool bAdd = true);                            //���С�Ӷ�Ա����
    unsigned int GetManipleCount(short stManipleId);                                        //���С�Ӷ�Ա����
    bool IsManipleFull(short stManipleId);

private:
    uint32 m_dwNextUpdateSelfTime;                              // ������ʱ��
    uint32 m_dwStopUpdateTeamMemberTime;                        // �������ʱ��ֹͣ���¶�Ա��Ϣ
    uint32 m_dwSessionId;                                       // �����ʹ�õ�sessionid
    bool m_bCorps;                                              // �Ƿ�����
    uint8 m_nAssignModeType;                                    // ��ǰ����ķ���ģʽ

    uint32 m_dwTeamHeaderID;                                    // �ӳ��� ID
    uint32 m_dwNextUpdateTime;                                  // �´�TeamEx����ʱ��

    uint32 m_nAssignIndex;                                      // �ôε�����Ʒ���䵽ĳ����Ա���� (���������)
    
    std::list<TeamMember> m_listTeamMember;                     // ��Ա�б�
    std::map<short, unsigned int> m_mapManipleCount;            // 4��С��,ÿ��С�ӵ�����
    DWORD m_dwNextUpdateToCenterTime;                           // �´�ͬ����centerserver ��ʱ��
    uint8 m_chAssignItemLevel;                                  // �������ʱ,��Ʒ�ĵȼ�,(>=�õȼ�,��Ҫ��ɸ����������Ʒ����˭)

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
    bool DisbandTeam( uint32 dwSessionID , uint32 dwTeamHeaderId );                                //��ɢ����
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
