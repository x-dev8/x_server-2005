#ifndef __COMMON_MAPCONFIG_H__
#define __COMMON_MAPCONFIG_H__

#include <string>
#include <map>
#include <vector>

#define MapErrorId 0xffff
typedef unsigned short ushort;
typedef unsigned long  ulong;
typedef unsigned char  uchar;

#define theMapConfig MapConfig::Instance()                //ʵ���ӿ�

class MapConfig
{
public:
    //����Ŀ���
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

    //���͵�
    struct TransportPosition
    {
        TransportPosition() : Id(MapErrorId), TargetMapId(MapErrorId), TargetId(MapErrorId), MinX(0.0f), MaxX(0.0f), MinY(0.0f), MaxY(0.0f) { }

        ushort Id;
        ushort TargetMapId;                //���͵���Ŀ���ͼ
        ushort TargetId;                //Ŀ���ͼ�ϵĴ���Ŀ���Id
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
        Relive_Default    = 0x1,        //Ĭ��
        Relive_RedName    = 0x2,        //����������
        Relive_Attack    = 0x4,        //����������
        Relive_Guard    = 0x8,        //�س�������
    };
    /////////////////////////////////////////////////////
    //��վ��ʱ���ȿ��ǳ�վ����������, �޳�վ�ſ��Ǻ���
    ///////////////////////////////////////////////////////////

    //������
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
        // ǰ4λ(1-15)Ϊ��ͼ����
        MT_NormalMap      = 0,    // ��ͨ��ͼ
        MT_SingleTeam     = 1,    // �����鸱��
        MT_MultiPlayer    = 2,    // ���˸���
        MT_Period         = 3,    // ���ڸ���
        MT_MultiTeam      = 4,    // ����鸱��
        MT_SingleGuild    = 5,    // �����ɸ���
        MT_SinglePlayer   = 6,    // ���˸���
        MT_MultiGuild     = 7,    // ����ɸ���

        eMaxEcypteMapType = 15,

        // ��28λΪ����flag
        eCreateNewMap     = 1 << 4,    // ��ͼ������ʱ����
        eLifeTimeLimit    = 1 << 5,    // ��ʱ�����Ƶĸ���
        eCountLimit       = 1 << 6,    // �е�ͼ��������
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
			m_fBrightnessOffset = 0.f;		// ����ƫ��
			m_fContrastOffsetR = 1.f;		// �Աȶ�Rƫ��
			m_fContrastOffsetG = 1.f;		// �Աȶ�Gƫ��
			m_fContrastOffsetB = 1.f;		// �Աȶ�Bƫ��
			m_bGrassDestBlendOne = 0;
        }

        enum MapPKMode
        {
			EPKM_None_PK		= -1,    // ��PKģʽ
            EPKM_UnAllow_PK     =  0,    // ���Խ�ֹPK
            EPKM_Critical_PK    =  1,    // ֻ�����ģʽPK
            EPKM_Allow_PK       =  2,    // ֻ�����ģʽPK��PKģʽ
            EPKM_Normal_PK      =  3,    // ��PK������PK��PKģʽ
            EPKM_Group_PK       =  4,    // ��ӪPK
            EPKM_Guild_PK       =  5,    // ����ս��
            EPKM_Free_PK        =  6,    // ����PK
            EPKM_Team_PK        =  7,    // С�ӻ�ս
            EPKM_Challenge_PK   =  8,    // ������̨��ͼ
            EPKM_Contend_PK     =  9,    // ����սPK
            EPKM_CrossServer_PK =  10,   // ���PKս
            EPKM_WorldBattle_PK =  11,	 // ����ս��PKģʽ

            EPKM_End = 0xF,
        };

        ushort      Id                  ; // ��ͼId  ����Ϊ��
        ushort      CountryID           ; // ���ڵĹ���ID
        std::string FilePath            ; // ��ͼmew�ļ�·��
        std::string MonsterFilePath     ; // ��ͼ�����ļ�·��
        std::string ClientReachableMap  ; // �ͻ���Ѱ·��ͼ
        std::string MapName             ; // ��ͼ����
        ushort      Row                 ; // ����
        ushort      Column              ; // ����
        bool        ShowFootPrint       ; // �Ƿ���ʾ��ӡ
        ulong       Type                ; // ��ͼ����
        ushort      MinPlayerLevel      ; // ���������С�ȼ�
        ushort      Order               ; // ����
        int         CanPk               ; // �Ƿ���PK,PK����
		bool         CanDuel               ; // �Ƿ���PK,PK����
        bool        CanRide             ; // �Ƿ�������
		bool		CanPet				; // �Ƿ����ٻ�����
        ulong       Duration            ; // ������ͼά��ʱ�� // 0 ������,����Ϊ����
        ushort      Count               ; // ����������ͼ���� // 0 ������,����Ϊ������������
        ushort      UnitCount           ; // ������ٵ�λ�������븱����ͼ (���˸�����ͼ:��Ҹ���, �ŶӸ�����ͼ:�ŶӸ���)
        std::string SkyBox              ; // SkyBox·��
        std::string EffectPath          ; // ��Ч·��
        bool        SystemCreate        ; // �Ƿ���ϵͳ�����ĸ��� ( ˵�鳡֮��ĸ�����ͼ )
        int         m_nRegionOffsetX    ; // �����ͼxƫ��
        int         m_nRegionOffsetY    ; // �����ͼyƫ��
        int         m_nRegionEdge       ; // �����ͼ�߳�����λ����
        std::string MapNameColor        ; // ��ͼ���ֵ���ʾ��ɫ
        std::string MapTip              ; // ��ͼ��Tip
		float       m_BloomScale        ; // Bloom���� ģ������
		float       m_Luminance         ; // Bloom���� ����ǿ��
		float       m_fBrightnessOffset ; // ����ƫ��
		float       m_fContrastOffsetR  ; // �Աȶ�Rƫ��
		float       m_fContrastOffsetG  ; // �Աȶ�Gƫ��
		float       m_fContrastOffsetB  ; // �Աȶ�Bƫ��
		bool	    m_bGrassDestBlendOne; // ��Ƥ���Ʋ���		
		bool        m_bSunLightRender   ; // �Ƿ���Ⱦ̫����
        float       ExpRate             ; // ����ӳɱ���
        std::string ScriptFile          ; // �ű�·�� ��ʽ��MonsterFilePath����
        
        std::map<ushort, TransportDestination> mapTransportDestinations; // ����Ŀ���
        std::map<ushort, TransportPosition>    mapTransportPositions;    // ���͵�
        std::map<ushort, RelivePosition>       mapRelivePositions;       // ������
		std::map<ushort, SpecRelivePosition>   mapSpecRelivePositions;	 // ��������������㣬���ȸ������ĸ����
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
        TransportPosition* GetTransportPositionByPositon(float x, float y, float fDis = 1.f);    //���������Ĵ��͵�
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        inline ushort RelivePositionCount() { return static_cast<ushort>(mapRelivePositions.size()); }
        bool AddRelivePosition(RelivePosition& xRelive, bool bReplace = false);
		bool AddSpecRelivePosition(SpecRelivePosition& xRelive);
        bool RemoveRelivePosition(ushort Id);        
        RelivePosition* GetRelivePositionById(ushort Id);
        RelivePosition* GetRelivePositionByIndex(ushort nIndex);
        RelivePosition* GetRelivePositionByPosition(float x, float y);            //������ĸ����
        RelivePosition* GetRelivePositionByState(bool bPlayerDead = false);
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        const char* GetMapFilePath();        //��ó���Ŀ¼
        const char* GetMapMonsterDataFile(); //���ˢ���ļ�
        const char* GetMapScriptFile();      //��ȡ�ű��ļ�   
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        inline EMapType GetMapType() { return (EMapType)(Type & 0x0000000F); }
        inline bool IsEctypeMap() { return GetMapType() != MT_NormalMap; }
        inline bool IsCreateNewMap() { return (Type & eCreateNewMap) == eCreateNewMap; }
        inline bool IsPlayerLimitMap() { return GetMapType() == MT_MultiPlayer; }
        inline bool IsLifeTimeLimitMap() { return Duration > 0;/*(Type & eLifeTimeLimit) != 0;*/ }          // ʱ�����Ƹ���
        inline bool IsMapCountLimitMap() { return Count > 0;/*(Type & eCountLimit) != 0;*/ }
        inline bool IsUnitCountLimitMap() { return UnitCount > 0; }     // �����Ƶ�λ�����ĵ�ͼ
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

    bool LoadMapConfig(const char* szFile);													//���ص�ͼ��Ϣ
    bool SaveMapConfig(const char *szWorldPath,
		const char *szMapFolder = NULL, int tile_id = -1);									//�����ͼ��Ϣ

    inline void Clear(){ m_vecMapData.clear(); }                                            //���
    inline bool IsEmpty() { return m_vecMapData.empty(); }                                    //�Ƿ�Ϊ��
    /////////////////////////////////////////////////////////////
    inline ushort MapDataCount() { return static_cast<ushort>(m_vecMapData.size()); }        //��ͼ����
    bool AddMapData(MapData& xMapData, bool bReplace = false);                                //��ӵ�ͼ
    bool RemoveMapData(ushort Id);                                                            //ɾ����ͼ

    MapData* GetMapDataById(ushort Id);                                                        //Id����
    MapData* GetMapDataByIndex(ushort nIndex);                                                //��������

    //�༭ʱ�� ����bEdit = true;
    MapData* GetMapDataByName(const char* szName, bool bEdit = false);                        //���ֲ��� 
    MapData* GetMapDataByDir(const char* szDir, bool bEdit = false);                        //·������    

    void GetMapDataSortByLevel(std::vector<int>& vecMapId);                            //��ð���ͼ�ȼ������ĵ�ͼId

    RelivePosition* GetRelivePostionByMapID( ushort ustMapID );                     // ��ñ��ǵ�ĳ����ȫ��

private:
    void AddNameMap( const std::string& Name, ushort nIndex); // ������ֹ���
    int  GetNameMapIndex( const std::string& Name);            //

    void AddPathMap( const std::string& Path, ushort nIndex); // ���·������
    int  GetPathMapIndex( const std::string& Path);

    bool   AddIdToIndex( ushort Id, ushort nIndex ); // ���Id����
    ushort GetIdToIndex( ushort Id );

    void AddMapSortByLevel(ushort Level, ushort Id);        //��ӵȼ�����

    void AddMapRelivePostion( ushort ustMapID, RelivePosition& xRelive );
protected:
    std::vector<MapData> m_vecMapData;
    std::map<std::string, ushort> m_mapNameIndex;     // ���ֹ���Index
    std::multimap<ushort, ushort> m_mapIdSortbyLevel; // �ȼ�����
    std::map<std::string, ushort> m_mapPathIndex;     // ·������Index
    std::map<ushort, ushort>      m_mapIdToIndex;     // Id����Index

    RelivePositionMap m_mapRelivePostion;     // ĳһ����ͼ�ϵ�������
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
#define CanPet_Key						"CanPet"		//add:2012.08.27 �����Ƿ��ܳ�ս
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