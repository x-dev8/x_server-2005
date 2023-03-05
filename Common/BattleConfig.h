#ifndef __BATTLECONFIG_H__
#define __BATTLECONFIG_H__

#include <string>
#include <vector>

// 战场的启动信息
class StartInfo
{
public:
    void SetServerID( unsigned char uchValue )  { uchServerID = uchValue; }
    void SetDayOfWeek( unsigned char uchValue ) { uchDayOfWeek = uchValue; }
    void SetStartTime( unsigned char uchValue ) { uchStartTime = uchValue; }


    unsigned char GetServerID() const  { return uchServerID; }
    unsigned char GetDayOfWeek() const { return uchDayOfWeek; }
    unsigned char GetStartTime() const { return uchStartTime; }


private:
    unsigned char uchServerID;          // 在某个服务器上开启
    unsigned char uchDayOfWeek;         // 每周几启动
    unsigned char uchStartTime;         // 开始的具体时间
};

class BattleInfo
{
protected:
    typedef std::vector< StartInfo > StartInfoVector;
    typedef StartInfoVector::const_iterator StartInfoVectorConstIter;
public:
    BattleInfo() : uchFightMapID( -1 ), ustWaitMapID( -1 ), uchType( 0 ), uchSignTime( 0 ), ustFightTime( 0 ), strScript( "" ),
        uchUnitCount( 0 ), uchLeastUnit( 0 ), uchEachUnit( 0 ), ustLevel( 0 ), ustBroadCastID( 0 ), uchTurns( 0 ), uchCount( 0 )
    {
        vecStartInfo.clear();
    }

    void SetFightMapID( unsigned short ustValue ) { uchFightMapID = ustValue; }
    void SetWaitMapID( unsigned short ustValue )  { ustWaitMapID = ustValue; }
    void SetType( unsigned char uchValue )        { uchType = uchValue; }
    void SetTurns( unsigned char uchValue )     { uchTurns = uchValue; }
    void SetCount( unsigned char uchValue )     { uchCount = uchValue; }
    void SetSignTime( unsigned char uchValue )    { uchSignTime = uchValue; }
    void SetFightTime( unsigned char ustValue )   { ustFightTime = ustValue; }
    void SetScript( const char* szValue )         { strScript = szValue; }
    void SetUnitCount( unsigned char uchValue )   { uchUnitCount = uchValue; }
    void SetLeastUnit( unsigned char uchValue )   { uchLeastUnit = uchValue; }
    void SetEachUnit( unsigned char uchValue )    { uchEachUnit = uchValue; }
    void SetLevel( unsigned short ustValue )      { ustLevel = ustValue; }
    void SetBroadCast( unsigned short ustValue )  { ustBroadCastID = ustValue; }
    void AddStartInfo( const StartInfo& xInfo )   { vecStartInfo.push_back( xInfo ); }

    unsigned short GetFightMapID() const { return uchFightMapID; }
    unsigned short GetWaitMapID() const { return ustWaitMapID; }
    unsigned char GetType() const { return uchType; }
    unsigned char GetTurns() const     { return uchTurns; }
    unsigned char GetCount() const     { return uchCount; }
    unsigned char GetSignTime() const  { return uchSignTime; }
    unsigned char GetFightTime() const { return uchFightMapID; }
    const char* GetScript() const { return strScript.c_str(); }
    unsigned char GetUnitCount() const { return uchUnitCount; }
    unsigned char GetLeastUnit() const { return uchLeastUnit; }
    unsigned char GetEachUnit() const  { return uchEachUnit; }
    unsigned short GetLevel() const { return ustLevel; }
    const char* GetBroadCastID() const { return ustBroadCastID; }

    unsigned char GetStartInfoCount() { static_cast< unsigned char >( vecStartInfo.size() ); }
    const StartInfo* GetStartInfoByIndex( unsigned char uchIndex ) const
    {
        if ( uchIndex >= GetStartInfoCount() )
        { return NULL; }

        return &( vecStartInfo.at( uchIndex ) );
    }

private:
    unsigned short uchFightMapID;       // 战斗地图
    unsigned short ustWaitMapID;        // 等待地图
    unsigned char uchType;              // 类型 1 : 个人, 2 : 组队
    unsigned char uchSignTime;          // 报名持续时间
    unsigned char ustFightTime;         // 战斗时间
    std::string strScript;              // 脚本路径
    unsigned char uchUnitCount;         // 允许报名的最大单位
    unsigned char uchLeastUnit;         // 报名的最小单位
    unsigned char uchEachUnit;          // 每个单位的人数
    unsigned short ustLevel;            // 限制等级
    unsigned short ustBroadCastID;      // 系统公告
    unsigned char uchTurns;             // 每次有几轮战场
    unsigned char uchCount;             // 每轮战场开启几个
    StartInfoVector vecStartInfo;       // 战场的启动时间
};

#endif