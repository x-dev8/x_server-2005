#ifndef __GAMESTAGECONFIG_H__
#define __GAMESTAGECONFIG_H__

#include <string>
#include <map>

class StageData
{
public:
    class StageInfo
    {
    public:
        StageInfo() : nStage( 0 ), nSecond( 0 ), strString( "" ) { }
        StageInfo( const StageInfo& xInfo ) { *this = xInfo; }
        StageInfo& operator = ( const StageInfo& xInfo )
        {
            if ( this != &xInfo )
            {
                nStage    = xInfo.nStage;
                nSecond   = xInfo.nSecond;
                strString = xInfo.strString;
            }
            return *this;
        }

        void SetStage( unsigned short nValue )  { nStage = nValue; }
        void SetSecond( unsigned int nValue )   { nSecond = nValue; }
        void SetString( const char* pszString ) { strString = pszString; }

        const unsigned short GetStage() const { return nStage; }
        const unsigned int GetSecond() const  { return nSecond; }
        const char* GetString() const         { return strString.c_str(); }

    private:
        unsigned short nStage;          // 第几阶段
        unsigned int nSecond;           // 维持多少时间 单位 : 秒
        std::string strString;          // 系统提示字符串的ID
    };

protected:
    typedef std::map< unsigned short, StageInfo > MapStageInfo;
    typedef MapStageInfo::iterator MapStageInfoIter;

public:
    StageData() : nMapID( -1 ), strScriptFile( "" ) 
    {
        mapStageInfo.clear();
    }

    StageData( const StageData& xData ) { *this = xData; }
    StageData& operator = ( const StageData& xData )
    {
        if ( this != &xData )
        {
            nMapID        = xData.nMapID;
            strScriptFile = xData.strScriptFile;
            mapStageInfo  = xData.mapStageInfo;
        }
        return *this;
    }

    void SetMapID( short nValue )              { nMapID = nValue; }
    void SetScriptFile( const char* pszValue ) { strScriptFile = pszValue; }

    const short GetMapID() const      { return nMapID; }
    const char* GetScriptFile() const { return strScriptFile.c_str(); }

    bool AddStageInfo( const StageInfo& xInfo )
    {
        MapStageInfoIter iter = mapStageInfo.find( xInfo.GetStage() );
        if ( iter != mapStageInfo.end() )
        { return false; }

        return mapStageInfo.insert( std::make_pair( xInfo.GetStage(), xInfo ) ).second;
    }

    StageInfo* GetStageInfo( unsigned short nStage )
    {
        MapStageInfoIter iter = mapStageInfo.find( nStage );
        if ( iter == mapStageInfo.end() )
        { return NULL; }

        return &( iter->second );
    }

    unsigned short GetStageInfoCount() { return static_cast< unsigned short >( mapStageInfo.size() ); }
private:
    short nMapID;               // 场景的mapid
    std::string strScriptFile;  // 调用的脚本路径
    MapStageInfo mapStageInfo;  // 场景分段刷新信息
};

#define theGameStageConfig GameStageConfig::Instance()

class GameStageConfig
{
public:
    typedef std::map< short, StageData > MapStageData;
    typedef MapStageData::iterator MapStageDataIter;

public:
    static GameStageConfig& Instance()
    {
        static GameStageConfig s_xConfig;
        return s_xConfig;
    }

    bool AddStageData( const StageData& xData )
    {
        MapStageDataIter iter = m_mapStageData.find( xData.GetMapID() );
        if ( iter != m_mapStageData.end() )
        { return false; }

        return m_mapStageData.insert( std::make_pair( xData.GetMapID(), xData ) ).second; 
    }

    StageData* GetStageData( short nMapID )
    {
        MapStageDataIter iter = m_mapStageData.find( nMapID );
        if ( iter == m_mapStageData.end() )
        { return NULL; }

        return &( iter->second );
    }

    bool LoadGameStageConfig( const char* pszFile );

protected:
    GameStageConfig() { m_mapStageData.clear(); }

private:
    GameStageConfig( const GameStageConfig& );
    GameStageConfig& operator = ( const GameStageConfig& );

private:
    MapStageData m_mapStageData;
};

#endif