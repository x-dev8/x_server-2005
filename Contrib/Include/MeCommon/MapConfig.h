#ifndef __COMMON_MAPCONFIG_H__
#define __COMMON_MAPCONFIG_H__

#include <string>
#include <map>
#include <vector>

#define MapErrorId 0xffff
typedef unsigned short ushort;
typedef unsigned long  ulong;
typedef unsigned char  uchar;

#define theMapConfig MapConfig::Instance()                //实例接口

class MapConfig
{
public:
    //传送目标点
    struct TransportDestination
    {
        TransportDestination() : Id(MapErrorId), PositionX(0.0f), PositionY(0.0f), Direction(0.0f) { vecWeight.clear(); }

        ushort Id;
        float PositionX;
        float PositionY;
        float Direction;
        std::vector<int> vecWeight;

        inline bool operator == (const ushort& Id) { return (this->Id == Id); }
        inline bool operator < (const TransportDestination& xDestination) { return (this->Id < xDestination.Id); }
        TransportDestination& operator = (const TransportDestination& xDestination);        
    };

    //传送点
    struct TransportPosition
    {
        TransportPosition() : Id(MapErrorId), TargetMapId(MapErrorId), TargetId(MapErrorId), MinX(0.0f), MaxX(0.0f), MinY(0.0f), MaxY(0.0f) { }

        ushort Id;
        ushort TargetMapId;                //传送到的目标地图
        ushort TargetId;                //目标地图上的传送目标点Id
        float MinX;
        float MaxX;
        float MinY;
        float MaxY;

        inline bool operator == (const ushort& Id) { return (this->Id == Id); }
        inline bool operator < (const TransportPosition& xPosition) { return (this->Id < xPosition.Id); }
        TransportPosition& operator = (const TransportPosition& xPosition);
    };
    
    struct Status
    {
        int Id;
        int Level;
    };

    enum ReliveType
    {
        Relive_Default    = 0x1,        //默认
        Relive_RedName    = 0x2,        //红名重生点
        Relive_Attack    = 0x4,        //攻城重生点
        Relive_Guard    = 0x8,        //守城重生点
    };
    /////////////////////////////////////////////////////
    //城站的时候先考虑城站重生点重生, 无城站才考虑红名
    ///////////////////////////////////////////////////////////

    //重生点
    struct RelivePosition
    {
        RelivePosition() : Id(MapErrorId), MapId(MapErrorId), PositionX(0.0f), PositionY(0.0f), Type(Relive_Default) { }

        ushort Id;
        ushort MapId;                
        float PositionX;
        float PositionY;
        float Direction;
        int Type;
        inline bool operator == (const ushort& Id) { return (this->Id == Id); }
        inline bool operator < (const RelivePosition& xRelive) { return (this->Id < xRelive.Id); }

        RelivePosition& operator = (const RelivePosition& xRelive);
    };
	struct SpecRelivePosition:public RelivePosition
	{
		SpecRelivePosition():CountryId(0){}
		int CountryId;
	};
    enum EMapType
    {
        // 前4位(1-15)为地图类型
        MT_NormalMap      = 0,    // 普通地图
        MT_SingleTeam     = 1,    // 单队伍副本
        MT_MultiPlayer    = 2,    // 多人副本
        MT_Period         = 3,    // 周期副本
        MT_MultiTeam      = 4,    // 多队伍副本
        MT_SingleGuild    = 5,    // 单帮派副本
        MT_SinglePlayer   = 6,    // 单人副本
        MT_MultiGuild     = 7,    // 多帮派副本

        eMaxEcypteMapType = 15,

        // 后28位为附加flag
        eCreateNewMap     = 1 << 4,    // 地图不存在时创建
        eLifeTimeLimit    = 1 << 5,    // 有时间限制的副本
        eCountLimit       = 1 << 6,    // 有地图数量限制
    };

    struct MapData
    {
        MapData() : Id(MapErrorId) , CountryID( 0 ), FilePath(""), ClientReachableMap(""), MapName(""), Row(0), Column(0), ShowFootPrint(false), 
                    CanPk(0), CanRide(false),CanPet(true), Duration(0), Count(0), UnitCount(0), SkyBox(""), EffectPath(""), SystemCreate( false ),
					MapNameColor(""),MapTip(""),m_bSunLightRender(true)
        {
            mapTransportDestinations.clear();
            mapTransportPositions.clear();
            mapRelivePositions.clear();
			mapSpecRelivePositions.clear();
            m_nRegionOffsetX = 0;
            m_nRegionOffsetY = 0;
            m_nRegionEdge = 1024;
            ExpRate = 1.0f;
			m_BloomScale = 0;
			m_Luminance = 0;
			m_fBrightnessOffset = 0.f;		// 亮度偏移
			m_fContrastOffsetR = 1.f;		// 对比度R偏移
			m_fContrastOffsetG = 1.f;		// 对比度G偏移
			m_fContrastOffsetB = 1.f;		// 对比度B偏移
			m_bGrassDestBlendOne = 0;
        }

        enum MapPKMode
        {
			EPKM_None_PK		= -1,    // 无PK模式
            EPKM_UnAllow_PK     =  0,    // 绝对禁止PK
            EPKM_Critical_PK    =  1,    // 只允许狂暴模式PK
            EPKM_Allow_PK       =  2,    // 只允许狂暴模式PK和PK模式
            EPKM_Normal_PK      =  3,    // 狂暴PK、国家PK、PK模式
            EPKM_Group_PK       =  4,    // 阵营PK
            EPKM_Guild_PK       =  5,    // 帮派战场
            EPKM_Free_PK        =  6,    // 任意PK
            EPKM_Team_PK        =  7,    // 小队混战
            EPKM_Challenge_PK   =  8,    // 个人擂台地图
            EPKM_Contend_PK     =  9,    // 争夺战PK
            EPKM_CrossServer_PK =  10,   // 跨服PK战
            EPKM_WorldBattle_PK =  11,	 // 世界战场PK模式

            EPKM_End = 0xF,
        };

        ushort      Id                  ; // 地图Id  不能为空
        ushort      CountryID           ; // 属于的国家ID
        std::string FilePath            ; // 地图mew文件路径
        std::string MonsterFilePath     ; // 地图怪物文件路径
        std::string ClientReachableMap  ; // 客户端寻路地图
        std::string MapName             ; // 地图名称
        ushort      Row                 ; // 行数
        ushort      Column              ; // 列数
        bool        ShowFootPrint       ; // 是否显示脚印
        ulong       Type                ; // 地图类型
        ushort      MinPlayerLevel      ; // 限制玩家最小等级
        ushort      Order               ; // 排序
        int         CanPk               ; // 是否能PK,PK设置
		bool         CanDuel               ; // 是否能PK,PK设置
        bool        CanRide             ; // 是否能骑马
		bool		CanPet				; // 是否能召唤副将
        ulong       Duration            ; // 副本地图维持时间 // 0 无限制,其他为分钟
        ushort      Count               ; // 创建副本地图数量 // 0 无限制,其他为副本创建数量
        ushort      UnitCount           ; // 允许多少单位数量进入副本地图 (个人副本地图:玩家个数, 团队副本地图:团队个数)
        std::string SkyBox              ; // SkyBox路径
        std::string EffectPath          ; // 特效路径
        bool        SystemCreate        ; // 是否是系统创建的副本 ( 说书场之类的副本地图 )
        int         m_nRegionOffsetX    ; // 区域地图x偏差
        int         m_nRegionOffsetY    ; // 区域地图y偏差
        int         m_nRegionEdge       ; // 区域地图边长，单位像素
        std::string MapNameColor        ; // 地图名字的显示颜色
        std::string MapTip              ; // 地图的Tip
		float       m_BloomScale        ; // Bloom属性 模糊参数
		float       m_Luminance         ; // Bloom属性 叠加强度
		float       m_fBrightnessOffset ; // 亮度偏移
		float       m_fContrastOffsetR  ; // 对比度R偏移
		float       m_fContrastOffsetG  ; // 对比度G偏移
		float       m_fContrastOffsetB  ; // 对比度B偏移
		bool	    m_bGrassDestBlendOne; // 草皮绘制参数		
		bool        m_bSunLightRender   ; // 是否渲染太阳光
        float       ExpRate             ; // 经验加成比率
        std::string ScriptFile          ; // 脚本路径 形式和MonsterFilePath类似
        
        std::map<ushort, TransportDestination> mapTransportDestinations; // 传送目标点
        std::map<ushort, TransportPosition>    mapTransportPositions;    // 传送点
        std::map<ushort, RelivePosition>       mapRelivePositions;       // 重生点
		std::map<ushort, SpecRelivePosition>   mapSpecRelivePositions;	 // 这个是特殊重生点，优先复活到这里的复活点
        std::vector<Status>                    Statuss;                  // StatusId
        ///////////////////////////////////////////////////////////////////////////////////////////////
        inline ushort TransportDestinationCount() { return static_cast<ushort>(mapTransportDestinations.size()); }
        bool AddTransportDestination(TransportDestination& xDestination, bool bReplace = false);
        bool RemoveTransportDestination(ushort Id);        
        TransportDestination* GetTransportDestinationById(ushort Id);    
        TransportDestination* GetTransportDestinationByIndex(ushort nIndex);
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        inline ushort TransportPositionCount() { return static_cast<ushort>(mapTransportPositions.size()); }
        bool AddTransportPosition(TransportPosition& xPosition, bool bReplace = false);
        bool RemoveTransportPosition(ushort Id);        
        TransportPosition* GetTransportPositionById(ushort Id);
        TransportPosition* GetTransportPositionByIndex(ushort nIndex);
        TransportPosition* GetTransportPositionByPositon(float x, float y, float fDis = 1.f);    //找离的最近的传送点
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        inline ushort RelivePositionCount() { return static_cast<ushort>(mapRelivePositions.size()); }
        bool AddRelivePosition(RelivePosition& xRelive, bool bReplace = false);
		bool AddSpecRelivePosition(SpecRelivePosition& xRelive);
        bool RemoveRelivePosition(ushort Id);        
        RelivePosition* GetRelivePositionById(ushort Id);
        RelivePosition* GetRelivePositionByIndex(ushort nIndex);
        RelivePosition* GetRelivePositionByPosition(float x, float y);            //找最近的复活点
        RelivePosition* GetRelivePositionByState(bool bPlayerDead = false);
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        const char* GetMapFilePath();        //获得场景目录
        const char* GetMapMonsterDataFile(); //获得刷怪文件
        const char* GetMapScriptFile();      //获取脚本文件   
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        inline EMapType GetMapType() { return (EMapType)(Type & 0x0000000F); }
        inline bool IsEctypeMap() { return GetMapType() != MT_NormalMap; }
        inline bool IsCreateNewMap() { return (Type & eCreateNewMap) == eCreateNewMap; }
        inline bool IsPlayerLimitMap() { return GetMapType() == MT_MultiPlayer; }
        inline bool IsLifeTimeLimitMap() { return Duration > 0;/*(Type & eLifeTimeLimit) != 0;*/ }          // 时间限制副本
        inline bool IsMapCountLimitMap() { return Count > 0;/*(Type & eCountLimit) != 0;*/ }
        inline bool IsUnitCountLimitMap() { return UnitCount > 0; }     // 是限制单位数量的地图
        inline bool IsSystemCreateMap() { return SystemCreate; }

        inline void SetMapCountLimitMap() { Type |= eCountLimit; }
        inline void SetLifeTimeLimitMap() { Type |= eLifeTimeLimit; }
        inline void SetCreateNewMap() { Type |= eCreateNewMap; }

        inline bool operator == (const ushort& Id) { return (this->Id == Id); }
        inline bool operator < (const MapData& xMapData) { return (this->Id < xMapData.Id); }

        MapConfig::Status* GetStatusByIndex(int xIndexId);
        int GetStatusSize(){ return (int)Statuss.size(); }
        void AddStatus(const MapConfig::Status &status){ Statuss.push_back(status); }
        bool SetStatus(int indexId,const MapConfig::Status &status);
        bool DelStatus(int indexId);
		const SpecRelivePosition* GetSpecRelivePositionByCountry(int CountryID);
    };

public:
    typedef std::map<ushort, TransportDestination> MapDestination;
    typedef std::map<ushort, TransportPosition>    MapPosition;
    typedef std::map<ushort, RelivePosition>       MapRelive;

    typedef std::vector<MapData>::iterator                   mdveciter;
    typedef std::map<ushort, TransportDestination>::iterator tdmapiter;
    typedef std::map<ushort, TransportPosition>::iterator    tpmapiter;
    typedef std::map<ushort, RelivePosition>::iterator       rpmapiter;
	typedef std::map<ushort, SpecRelivePosition>::iterator   rpspecmapiter;
    typedef std::map<std::string, ushort>::iterator          strumapiter;
    typedef std::multimap<ushort, ushort>::iterator          uumapiter;
    typedef std::vector<Status>::iterator                    statusiter;
    typedef std::map<ushort, ushort>::iterator               iimapiter;

    typedef std::map< ushort, std::vector< RelivePosition > > RelivePositionMap;
    typedef RelivePositionMap::iterator                       RelivePositionMapIter;

protected:
    MapConfig();
public:
    ~MapConfig();

public:
    inline static MapConfig& Instance()
    {
        static MapConfig s_xMapConfig;
        return s_xMapConfig;
    }

    bool LoadMapConfig(const char* szFile);													//加载地图信息
    bool SaveMapConfig(const char *szWorldPath,
		const char *szMapFolder = NULL, int tile_id = -1);									//保存地图信息

    inline void Clear(){ m_vecMapData.clear(); }                                            //清空
    inline bool IsEmpty() { return m_vecMapData.empty(); }                                    //是否为空
    /////////////////////////////////////////////////////////////
    inline ushort MapDataCount() { return static_cast<ushort>(m_vecMapData.size()); }        //地图数量
    bool AddMapData(MapData& xMapData, bool bReplace = false);                                //添加地图
    bool RemoveMapData(ushort Id);                                                            //删除地图

    MapData* GetMapDataById(ushort Id);                                                        //Id查找
    MapData* GetMapDataByIndex(ushort nIndex);                                                //索引查找

    //编辑时候 传入bEdit = true;
    MapData* GetMapDataByName(const char* szName, bool bEdit = false);                        //名字查找 
    MapData* GetMapDataByDir(const char* szDir, bool bEdit = false);                        //路径查找    

    void GetMapDataSortByLevel(std::vector<int>& vecMapId);                            //获得按地图等级排序后的地图Id

    RelivePosition* GetRelivePostionByMapID( ushort ustMapID );                     // 获得本城的某个安全点

private:
    void AddNameMap( const std::string& Name, ushort nIndex); // 添加名字关联
    int  GetNameMapIndex( const std::string& Name);            //

    void AddPathMap( const std::string& Path, ushort nIndex); // 添加路径关联
    int  GetPathMapIndex( const std::string& Path);

    bool   AddIdToIndex( ushort Id, ushort nIndex ); // 添加Id关联
    ushort GetIdToIndex( ushort Id );

    void AddMapSortByLevel(ushort Level, ushort Id);        //添加等级排序

    void AddMapRelivePostion( ushort ustMapID, RelivePosition& xRelive );
protected:
    std::vector<MapData> m_vecMapData;
    std::map<std::string, ushort> m_mapNameIndex;     // 名字关联Index
    std::multimap<ushort, ushort> m_mapIdSortbyLevel; // 等级排序
    std::map<std::string, ushort> m_mapPathIndex;     // 路径关联Index
    std::map<ushort, ushort>      m_mapIdToIndex;     // Id关联Index

    RelivePositionMap m_mapRelivePostion;     // 某一个地图上的重生点
};

/////////////////////////////////////////////////////////////////////////////////
#define Root_Key						"Project"
#define Name_Key						"Name"
#define Version_Key						"Version"
#define Maps_Key						"Maps"
#define Map_Key							"Map"
#define Id_Key							"Id"
#define CountryId_Key					"CountryId"
#define Country_Key                     "Country"
#define StatusLevel_Key                 "Level"
#define FilePath_Key					"FilePath"		
#define MonsterFilePath_Key				"MonsterFilePath"
#define ScriptFilePath_Key 				"ScriptFilePath"
#define ClientReachableMap_Key			"ClientReachableMap"
#define MapName_Key						"MapName"						
#define Row_Key							"Row"							
#define Column_Key						"Column"						
#define ShowFootPrint_Key				"ShowFootPrint"				
#define Type_Key						"Type"						
#define MinPlayerLevel_Key				"MinPlayerLevel"
#define RegionMapOffsetX_Key			"RegionMapOffsetX"
#define RegionMapOffsetY_Key			"RegionMapOffsetY"
#define MapNameColor_Key                "MapNameColor"
#define MapTip_Key                      "MapTip"
#define RegionMapEdge_Key				"RegionMapEdge"
#define Order_Key						"Order"
#define CanPk_Key						"CanPk"						
#define CanRide_Key						"CanRide"
#define CanPet_Key						"CanPet"		//add:2012.08.27 副将是否能出战
#define Duration_Key					"Duration"					
#define Count_Key						"Count"						
#define UnitCount_Key					"UnitCount"					
#define SkyBox_Key						"SkyBox"		
#define EffectPath_Key					"EffectPath"
#define SystemCreate_Key                "SystemCreate"
#define ExpRate_Key                     "ExpRate"
#define SunLightRender_Key               "SunLightRender"
#define CanDuel_Key						"CanDuel"

#define PositionX_Key					"PositionX"
#define PositionY_Key					"PositionY"
#define Direction_Key					"Direction"
#define Weight_Key						"Weight%d"
#define TargetMapId_Key					"TargetMapId"
#define TargetId_Key					"TargetId"
#define MinX_Key						"MinX"
#define MaxX_Key						"MaxX"
#define MinY_Key						"MinY"
#define MaxY_Key						"MaxY"
#define Type_Key						"Type"

#define TransportDestinations_Key		"TransportDestinations"
#define TransportDestination_Key		"TransportDestination"
#define TransportPositions_Key			"TransportPositions"
#define TransportPosition_Key			"TransportPosition"
#define RelivePositions_Key				"RelivePositions"
#define SpecRelivePositions_Key			"SpecRelivePositions"
#define RelivePosition_Key				"RelivePosition"
#define SpecRelivePosition_Key			"SpecRelivePosition"
#define Statuss_Key				        "Statuss"
#define Status_Key				        "Status"

#define Bloom_Key						"BloomSetting"
#define BloomScale_Key					"BloomScale"
#define BloomLuminance_Key				"BloomLuminance"

#define BrightContrast_Key				"BrightContrast"
#define BrightnessOffset_Key			"BrightnessOffset"
#define ContrastOffsetR_Key				"ContrastOffsetR"
#define ContrastOffsetG_Key				"ContrastOffsetG"
#define ContrastOffsetB_Key				"ContrastOffsetB"

#define GrassDestBlendOne_Key				"GrassDestBlendOne"
/////////////////////////////////////////////////////////////////////////////////

#endif // __COMMON_MAPCONFIG_H__