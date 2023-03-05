#ifndef __MONSTERSTATUS_H__
#define __MONSTERSTATUS_H__

/************************************************************************
        特殊怪物类型配置, 怪物可对话, 
        然后状态改变, 成为可攻击状态等....

************************************************************************/
#include <string>
#include <map>
#include "vector"
#define theMonsterStatusConfig MonsterStatusConfig::Instance()

class MonsterStatusConfig
{
public:
	struct StatusSect 
	{
		StatusSect()
			:m_nKeepTime(0),m_StringId(-1)
		{

		}
		int		m_nKeepTime;
		int			m_StringId;
		std::string m_strAction;    // 动作
		std::string m_strEffect;    // 播放的特效
	};
    class StatusSetting
    {
    public:
        StatusSetting() : m_nStatus( 0 ), m_nNextStatus( 0 ), m_nSpaceTime( 0 ), m_nModelID( 0 ), m_strEffect( "" ), m_nScriptEnter( 2 ){}

        int GetStatus() const { return m_nStatus; }
        int GetNextStatus() const { return m_nNextStatus; }
        int GetSpaceTime() const { return m_nSpaceTime; }
        int GetScriptEnter() const { return m_nScriptEnter; }
        int GetModelID() const { return m_nModelID; }
        const char* GetEffect() const { return m_strEffect.c_str(); }
		float GetStartAlpha() const{ return m_fStartAlpha; }
		float GetEndAlpha() const{ return m_fEndAlph ; }
		float GetStartScale() const{ return m_fStartScale; }
		float GetEndScale() const{ return m_fEndScale; }
		float GetStartOffsetX() const{ return m_fStartOffsetX; }
		float GetEndOffsetX() const{ return m_fEndOffsetX; }
		float GetStartOffsetY() const{ return m_fStartOffsetY; }
		float GetEndOffsetY() const{ return m_fEndOffsetY; }
		float GetStartOffsetZ() const{return m_fStartOffsetZ; }
		float GetEndOffsetZ() const{return m_fEndOffsetZ; }

        void SetStatus( int nValue ) { m_nStatus = nValue; }
        void SetNextStatus( int nValue ) { m_nNextStatus = nValue; }
        void SetSpaceTime( int nValue ) { m_nSpaceTime = nValue; }
        void SetScriptEnter( int nValue ) { m_nScriptEnter = nValue; }
        void SetModelID( int nValue ) { m_nModelID = nValue; }
        void SetEffect( const char* szValue ) { m_strEffect = szValue; }
		void SetStartAlpha( float fValue ) { m_fStartAlpha = fValue; }
		void SetEndAlpha( float fValue ) { m_fEndAlph = fValue; }
		void SetStartScale( float fValue ) { m_fStartScale = fValue; }
		void SetEndScale( float fValue ) { m_fEndScale = fValue; }
		void SetStartOffsetX( float fValue ) { m_fStartOffsetX = fValue; }
		void SetEndOffsetX( float fValue ) { m_fEndOffsetX = fValue; }
		void SetStartOffsetY( float fValue ) { m_fStartOffsetY = fValue; }
		void SetEndOffsetY( float fValue ) { m_fEndOffsetY = fValue; }
		void SetStartOffsetZ( float fValue ) { m_fStartOffsetZ = fValue; }
		void SetEndOffsetZ( float fValue ) { m_fEndOffsetZ = fValue; }


		std::vector<StatusSect>& GetArrStatusSect() { return m_ArrStatusSect; }
		const std::vector<StatusSect>& GetArrStatusSect() const { return m_ArrStatusSect; }

    private:
        int m_nStatus;              // 当前状态
        int m_nNextStatus;          // 下一个状态
        int m_nSpaceTime;           // 改变到下一个状态的间隔时间( 单位 : 毫秒 )
        int m_nScriptEnter;         // 脚本入口
        int m_nModelID;             // 该状态模型ID( 不需要改变填成0 )
		float m_fStartAlpha;		// 开始时的Alpha值
		float m_fEndAlph;			// 结束时的Alpha值
		float m_fStartScale;		// 开始时的缩放值
		float m_fEndScale;			// 结束时的缩放值
		float m_fStartOffsetX;		// 开始时的偏移X
		float m_fEndOffsetX;		// 结束时的偏移X
		float m_fStartOffsetY;		// 开始时的偏移Y
		float m_fEndOffsetY;		// 结束时的偏移Y
		float m_fStartOffsetZ;		// 开始时的偏移Z
		float m_fEndOffsetZ;		// 结束时的偏移Z

        std::string m_strEffect;    // 播放的特效
		std::vector<StatusSect>				m_ArrStatusSect;
	};

    class StatusData
    {
    public:
        StatusData() : m_nMonsterID( 0 ), m_nMonsterType(0), m_nInitStatus ( 0 ) {}

        int GetMonsterID() const { return m_nMonsterID; }
        int GetMonsterType() const { return m_nMonsterType; }
        int GetInitStatus() const { return m_nInitStatus; }

        void SetMonsterID( int nValue ) { m_nMonsterID = nValue; }
        void SetMonsterType( int nValue ) { m_nMonsterType = nValue; }
        void SetInitStatus( int nValue ) { m_nInitStatus = nValue; }

        void AddStatusSetting( const StatusSetting& xSetting )
        {
            m_mapStatusSetting[ xSetting.GetStatus() ] = xSetting;
        }

        const StatusSetting* GetStatusSetting( int nStatus ) const
        {
             StatusSettingMapIter iter = m_mapStatusSetting.find( nStatus );
             if ( iter == m_mapStatusSetting.end() )
             { return NULL; }

             return &( iter->second );
        }

    protected:
        typedef std::map< int , StatusSetting > StatusSettingMap;
        typedef StatusSettingMap::const_iterator StatusSettingMapIter;
    private:
        int m_nMonsterID;       // 怪物ID
        int m_nMonsterType;     // 怪物类型
        int m_nInitStatus;      // 初始状态
        StatusSettingMap m_mapStatusSetting;    // 特效路径
    };

    void AddStatusData( const StatusData &xConfig )
    {
         m_mapStatusConfig[ xConfig.GetMonsterID() ] = xConfig;
    }

    void AddStatusDataByType( const StatusData &xConfig )
    {
        m_mapStatusTypeConfig[ xConfig.GetMonsterType() ] = xConfig;
    }

    const StatusData* GetStatusData ( int nMonsterID ) const;
    const StatusData* GetStatusDataByType( int nMonsterType ) const;

    bool LoadConfig( const char* szFile );

    static MonsterStatusConfig& Instance()
    {
        static MonsterStatusConfig s_xConfig;
        return s_xConfig;
    }

protected:

    MonsterStatusConfig(){}

    typedef std::map< int, StatusData > StatusDataMap;
    typedef StatusDataMap::const_iterator StatusDataMapIter;

private:
    StatusDataMap m_mapStatusConfig;
    StatusDataMap m_mapStatusTypeConfig;
};

#endif