#include "MapConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"

MapConfig::TransportDestination& MapConfig::TransportDestination::operator = (const MapConfig::TransportDestination &xDestination)
{
    if (this != &xDestination)
    {
        Id = xDestination.Id;
        PositionX = xDestination.PositionX;
        PositionY = xDestination.PositionY;
        Direction = xDestination.Direction;
        vecWeight = xDestination.vecWeight;
    }

    return *this;
}

MapConfig::TransportPosition& MapConfig::TransportPosition::operator = (const MapConfig::TransportPosition &xPosition)
{
    if (this != &xPosition)
    {
        Id = xPosition.Id;
        TargetMapId = xPosition.TargetMapId;
        TargetId = xPosition.TargetId;
        MinX = xPosition.MinX;
        MaxX = xPosition.MaxX;
        MinY = xPosition.MinY;
        MaxY = xPosition.MaxY;
    }

    return *this;
}


MapConfig::RelivePosition& MapConfig::RelivePosition::operator = (const MapConfig::RelivePosition &xRelive)
{
    if (this != &xRelive)
    {
        Id = xRelive.Id;
        MapId = xRelive.MapId;
        PositionX = xRelive.PositionX;
        PositionY = xRelive.PositionY;
        Direction = xRelive.Direction;
        Type = xRelive.Type;
    }

    return *this;
}

bool MapConfig::MapData::AddTransportDestination(TransportDestination& xDestination, bool bReplace /* = false */)
{
    if (xDestination.Id == MapErrorId) { return false; }

    tdmapiter iter = mapTransportDestinations.find(xDestination.Id);
    if (iter != mapTransportDestinations.end())
    {
        if (bReplace)
        {
            iter->second = xDestination;
        }

        return bReplace;
    }

    mapTransportDestinations.insert(make_pair(xDestination.Id, xDestination));
    return true;
}

bool MapConfig::MapData::RemoveTransportDestination(ushort Id)
{
    tdmapiter iter = mapTransportDestinations.find(Id);
    if (iter != mapTransportDestinations.end())
    {
        mapTransportDestinations.erase(iter);

        return true;
    }

    return false;
}

MapConfig::TransportDestination* MapConfig::MapData::GetTransportDestinationByIndex(ushort nIndex)
{
    if (nIndex < 0 || nIndex >= TransportDestinationCount()) { return NULL; }

    tdmapiter iter = mapTransportDestinations.begin();

    advance( iter, nIndex );

    return &(iter->second);
}

MapConfig::TransportDestination* MapConfig::MapData::GetTransportDestinationById(ushort Id)
{
    tdmapiter iter = mapTransportDestinations.find(Id);
    if (iter != mapTransportDestinations.end())
    {
        return &(iter->second);
    }

    return NULL;
}

bool MapConfig::MapData::AddTransportPosition(TransportPosition& xPosition, bool bReplace /* = false */)
{
    if (xPosition.Id == MapErrorId) { return false; }

    tpmapiter iter = mapTransportPositions.find(xPosition.Id);
    if (iter != mapTransportPositions.end())
    {
        if (bReplace)
        {
            iter->second = xPosition;
        }

        return bReplace;
    }

    mapTransportPositions.insert(make_pair(xPosition.Id, xPosition));

    return true;
}

bool MapConfig::MapData::RemoveTransportPosition(ushort Id)
{
    tpmapiter iter = mapTransportPositions.find(Id);
    if (iter != mapTransportPositions.end())
    {
        mapTransportPositions.erase(iter);
        
        return true;
    }

    return false;
}

MapConfig::TransportPosition* MapConfig::MapData::GetTransportPositionByIndex(ushort nIndex)
{
    if (nIndex < 0 || nIndex >= TransportPositionCount()) { return NULL; }

    tpmapiter iter = mapTransportPositions.begin();
    
    advance( iter, nIndex );

    return &(iter->second);
}

MapConfig::TransportPosition* MapConfig::MapData::GetTransportPositionById(ushort Id)
{
    tpmapiter iter = mapTransportPositions.find(Id);
    if (iter != mapTransportPositions.end())
    {
        return &(iter->second);
    }

    return NULL;
}

//fDis  适当的扩大范围
MapConfig::TransportPosition* MapConfig::MapData::GetTransportPositionByPositon(float x, float y, float fDis /* = 1.f */)
{
    tpmapiter iter = mapTransportPositions.begin();
    tpmapiter end = mapTransportPositions.end();

    for ( ; iter != end; ++iter)
    {
        if (x >= iter->second.MinX - fDis && x <= iter->second.MaxX + fDis &&
            y >= iter->second.MinY - fDis && y <= iter->second.MaxY + fDis)
        {
            return &(iter->second);
        }
    }

    return NULL;
}

bool MapConfig::MapData::AddRelivePosition(RelivePosition& xRelive, bool bReplace /* = false */)
{
    if (xRelive.Id == MapErrorId) { return false; }

    rpmapiter iter = mapRelivePositions.find(xRelive.Id);
    if (iter != mapRelivePositions.end())
    {
        if (bReplace)
        {
            iter->second = xRelive;
        }

        return bReplace;
    }

    mapRelivePositions.insert(make_pair(xRelive.Id, xRelive));
    return false;
}

bool MapConfig::MapData::AddSpecRelivePosition(SpecRelivePosition& xRelive)
{
	if (xRelive.Id == MapErrorId) { return false; }
	typedef pair<std::map<ushort, SpecRelivePosition>::iterator,bool> rtPair;
	rtPair pair = mapSpecRelivePositions.insert(make_pair(xRelive.CountryId, xRelive));
	return pair.second;
}

bool MapConfig::MapData::RemoveRelivePosition(ushort Id)
{
    rpmapiter iter = mapRelivePositions.find(Id);
    if (iter != mapRelivePositions.end())
    {
        mapRelivePositions.erase(iter);

        return true;
    }

    return false;
}

MapConfig::RelivePosition* MapConfig::MapData::GetRelivePositionByIndex(ushort nIndex)
{
	//想不通为什么要这么写，用这个所谓的index也就是id做键值不是更好？
	//每个mapdata中的RelivePosition结构里难道还有相同的ID？
	
    if (nIndex < 0 || nIndex >= RelivePositionCount()) { return NULL; }

    rpmapiter iter = mapRelivePositions.begin();

    while(nIndex--) { ++iter; }

    return &(iter->second);
}

MapConfig::RelivePosition* MapConfig::MapData::GetRelivePositionById(ushort Id)
{
    rpmapiter iter = mapRelivePositions.find(Id);
    if (iter != mapRelivePositions.end())
    {
        return &(iter->second);
    }

    return NULL;
}

MapConfig::RelivePosition* MapConfig::MapData::GetRelivePositionByPosition(float x, float y)
{
    if (mapRelivePositions.empty()) { return NULL; }

    rpmapiter iter = mapRelivePositions.begin();
    rpmapiter end = mapRelivePositions.end();

    rpmapiter reiter = end;
    float fDistance = 10000.f;
    for ( ; iter != end; ++iter)
    {
        if (iter->second.MapId == -1 || iter->second.MapId == Id)
        {
            float fXoff = (iter->second.PositionX - x);
            float fYoff = (iter->second.PositionX - y);
            float fTemp = fXoff * fXoff + fYoff * fYoff;
            if (fDistance > fTemp)
            {
                fDistance = fTemp;
                reiter = iter;
            }
        }        
    }
    iter = mapRelivePositions.begin();   //没有找到就返回第一个
    return (reiter == end) ? &(iter->second) : &(reiter->second);
}


MapConfig::RelivePosition* MapConfig::MapData::GetRelivePositionByState(bool bPlayerDead /* = false */)
{
    if (RelivePositionCount() >= 2)
    {
        return GetRelivePositionByIndex(!bPlayerDead);
    }
 
    return GetRelivePositionByIndex(0);
}

const char* MapConfig::MapData::GetMapFilePath()
{
    static char s_szPath[_MAX_PATH] = "";

    _tsplitpath(FilePath.c_str(), NULL, NULL, s_szPath, NULL);

    return s_szPath;
}

const char* MapConfig::MapData::GetMapMonsterDataFile()
{
    return MonsterFilePath.c_str();
}

const char* MapConfig::MapData::GetMapScriptFile()
{
    return ScriptFile.c_str();
}

MapConfig::Status* MapConfig::MapData::GetStatusByIndex(int xIndexId)
{
    if (xIndexId < 0 || xIndexId >= Statuss.size())
        return NULL;

    return &Statuss[xIndexId];
}

bool MapConfig::MapData::SetStatus(int indexId,const MapConfig::Status &status)
{
    if (indexId < 0 || indexId >= Statuss.size())
        return false;

    Statuss[indexId].Id     = status.Id;
    Statuss[indexId].Level  = status.Level;
    return true;
}

bool MapConfig::MapData::DelStatus(int indexId)
{
    if (indexId < 0 || indexId >= Statuss.size())
        return false;
    
    statusiter statusIter = Statuss.begin();
    statusiter statusIterEnd = Statuss.end();
    for (int i = 0;statusIter != statusIterEnd;++statusIter)
    {
        if (indexId == i)
        {
            Statuss.erase(statusIter);
            break;
        }
    }
    return true;
}

const MapConfig::SpecRelivePosition* MapConfig::MapData::GetSpecRelivePositionByCountry(int CountryID)
{
	rpspecmapiter itr = mapSpecRelivePositions.find(CountryID);
	if (itr == mapSpecRelivePositions.end())
	{
		return NULL;
	}
	return &(itr->second);
}

MapConfig::MapConfig()
{
    m_vecMapData.clear();
}

MapConfig::~MapConfig()
{

}

bool MapConfig::AddMapData(MapConfig::MapData& xMapData, bool bReplace /* = false */)
{
    if (xMapData.Id == MapErrorId)
    { return false; }

    MapConfig::MapData* pMapData = GetMapDataById( xMapData.Id );
    if ( pMapData != NULL )
    { // 存在
        if ( bReplace )
        { *pMapData = xMapData; }
        return bReplace;
    }

    AddNameMap(xMapData.MapName, MapDataCount());
    AddPathMap(xMapData.FilePath, MapDataCount());
    AddMapSortByLevel(xMapData.MinPlayerLevel, xMapData.Id);
    AddIdToIndex( xMapData.Id, MapDataCount() );

    m_vecMapData.push_back( xMapData );

    return true;
}

bool MapConfig::RemoveMapData(ushort Id)
{
    mdveciter iter = find(m_vecMapData.begin(), m_vecMapData.end(), Id);
    if (iter != m_vecMapData.end())
    {
        m_vecMapData.erase(iter);

        return true;
    }

    return false;
}

MapConfig::MapData* MapConfig::GetMapDataByIndex(ushort nIndex)
{
    if (nIndex < 0 || nIndex >= MapDataCount())
    { return NULL; }

    return &m_vecMapData[nIndex];
}

MapConfig::MapData* MapConfig::GetMapDataById( ushort Id )
{
    ushort nIndex = GetIdToIndex( Id );
    if ( nIndex == MapErrorId)
    { return NULL; }
    
    return GetMapDataByIndex( nIndex );
}

MapConfig::MapData* MapConfig::GetMapDataByName(const char* szName, bool bEdit/* = false*/)
{
    if (szName == NULL || *szName == 0) { return NULL; }

    if (bEdit)
    {
        mdveciter iter = m_vecMapData.begin();
        mdveciter end = m_vecMapData.end();
        for ( ; iter != end; ++iter)
        {
            if (iter->MapName == szName){ return &(*iter); }
        }

        return NULL;
    }

    //服务器端 可以这样查找减少循环
    int nIndex = GetNameMapIndex(szName);
    return GetMapDataByIndex(nIndex);
}

MapConfig::MapData* MapConfig::GetMapDataByDir(const char* szDir, bool bEdit/* = false*/)
{
    if (szDir == NULL || *szDir == 0) { return NULL; }

    if (bEdit)
    {
        mdveciter iter = m_vecMapData.begin();
        mdveciter end = m_vecMapData.end();
        for ( ; iter != end; ++iter)
        {
            if (iter->FilePath == szDir) { return &(*iter);    }
        }

        return NULL;
    }

    //服务器端 可以这样查找减少循环
    int nIndex = GetPathMapIndex(szDir);
    return GetMapDataByIndex(nIndex);
}

void MapConfig::GetMapDataSortByLevel(std::vector<int>& vecMapId)
{
    vecMapId.clear();
        
    uumapiter iter = m_mapIdSortbyLevel.begin();
    uumapiter end = m_mapIdSortbyLevel.end();

    for ( ; iter != end; ++iter)
    {
        vecMapId.push_back(iter->second);
    }
}


/////////////////////////////////////////////////////////////////////////////private
void MapConfig::AddNameMap( const std::string& Name, ushort nIndex)
{
    if (Name.empty() || nIndex == MapErrorId ) { return; }

    m_mapNameIndex.insert(make_pair(Name, nIndex));
}

int MapConfig::GetNameMapIndex( const std::string& Name)
{
    strumapiter iter = m_mapNameIndex.find(Name);
    if (iter != m_mapNameIndex.end())
    {
        return iter->second;
    }

    return MapErrorId;
}

void MapConfig::AddPathMap( const std::string& Path, ushort nIndex)
{
    if (Path.empty() || nIndex == MapErrorId) { return; }

    m_mapPathIndex.insert(make_pair(Path, nIndex));
}

bool MapConfig::AddIdToIndex( ushort Id, ushort nIndex )
{
    if ( nIndex == MapErrorId) { return false; }

    return m_mapIdToIndex.insert( make_pair(Id, nIndex) ).second;
}

ushort MapConfig::GetIdToIndex( ushort Id )
{
    iimapiter iter = m_mapIdToIndex.find( Id );
    if (iter != m_mapIdToIndex.end())
    { return iter->second; }

    return MapErrorId;
}

int MapConfig::GetPathMapIndex( const std::string& Path)
{
    strumapiter iter = m_mapPathIndex.find(Path);
    if (iter != m_mapPathIndex.end())
    {
        return iter->second;
    }

    return MapErrorId;
}

void MapConfig::AddMapSortByLevel(ushort Level, ushort Id)
{
    if (Level < 0 || Id == MapErrorId) { return; }

    m_mapIdSortbyLevel.insert(make_pair(Level, Id));
}

MapConfig::RelivePosition* MapConfig::GetRelivePostionByMapID( ushort ustMapID )
{
    RelivePositionMapIter iter = m_mapRelivePostion.find( ustMapID );
    if ( iter == m_mapRelivePostion.end() || iter->second.empty() )
    { return NULL; }

    return &( iter->second.front() );
}

void MapConfig::AddMapRelivePostion( ushort ustMapID, RelivePosition& xRelive )
{
    RelivePositionMapIter iter = m_mapRelivePostion.find( ustMapID );
    if ( iter == m_mapRelivePostion.end() )
    {
        std::vector< RelivePosition > vecRelive;
        vecRelive.push_back( xRelive );

        m_mapRelivePostion.insert( make_pair( ustMapID, vecRelive ) );
    }
    else
    {
        for ( std::vector< RelivePosition >::iterator viter = iter->second.begin(); viter != iter->second.end(); ++viter )
        {
            if ( viter->MapId == xRelive.MapId && viter->PositionX == xRelive.PositionX && viter->PositionY == xRelive.PositionY )
            {
                return;
            }
        }

        iter->second.push_back( xRelive );
    }
}


bool MapConfig::LoadMapConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)    { return false; }

    m_vecMapData.clear();

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1)) { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement(Root_Key);
    if (pRoot == NULL) { return false; }

    //版本
    //////////////////////////////////////////////////////////
    MeXmlElement* pMaps = pRoot->FirstChildElement(Maps_Key);
    if (pMaps == NULL) { return false; }

    MeXmlElement* pMap = pMaps->FirstChildElement(Map_Key);
    while (pMap != NULL)
    {
        MapData xMapData;

        //id
        int nId;
        if (pMap->Attribute(Id_Key, &nId) == NULL || nId < 0 || nId >= MapErrorId) 
		{ 
			OutputDebugStringA( "MapError: Id_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Id = nId;

        int nCountryID;
        if ( pMap->Attribute(Country_Key, &nCountryID) != NULL )
        { xMapData.CountryID = nCountryID; }

        //FilePath
        Common::_tstring FilePath = "";
        FilePath.fromUTF8(pMap->Attribute(FilePath_Key));
        if (FilePath.empty()) 
		{
			OutputDebugStringA( "MapError: FilePath_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.FilePath = FilePath;

        //MonsterFilePath
        Common::_tstring MonsterFilePath = "";
        MonsterFilePath.fromUTF8(pMap->Attribute(MonsterFilePath_Key));
        if (MonsterFilePath.empty()) 
		{
			OutputDebugStringA( "MapError: MonsterFilePath_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.MonsterFilePath = MonsterFilePath;

        //ScriptFilePath
        Common::_tstring ScriptFilePath = "";
        ScriptFilePath.fromUTF8(pMap->Attribute(ScriptFilePath_Key));
        if (!ScriptFilePath.empty()) { xMapData.ScriptFile = ScriptFilePath; }        
        
        //ClientReachableMap
        Common::_tstring ClientReachableMap = "";
        ClientReachableMap.fromUTF8(pMap->Attribute(ClientReachableMap_Key));
        if (ClientReachableMap.empty()) 
		{
			OutputDebugStringA( "MapError: ClientReachableMap_Key." );			
		}
        xMapData.ClientReachableMap = ClientReachableMap;

        //MapName
        Common::_tstring MapName = "";
        MapName.fromUTF8(pMap->Attribute(MapName_Key));
        //if (MapName.empty()) { return false; }
        xMapData.MapName = MapName;

        //Row
        int nRow;
        if (pMap->Attribute(Row_Key, &nRow) == NULL || nRow <= 0) 
		{
			OutputDebugStringA( "MapError: Row_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Row = nRow;

        //Column
        int nColumn;
        if (pMap->Attribute(Column_Key, &nColumn) == NULL || nColumn <= 0) 
		{
			OutputDebugStringA( "MapError: Column_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Column = nColumn;

        //ShowFootPrint
        int nShowFootPrint;
        if (pMap->Attribute(ShowFootPrint_Key, &nShowFootPrint) == NULL || nShowFootPrint < 0 || nShowFootPrint > 1)
		{
			OutputDebugStringA( "MapError: ShowFottPrint_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.ShowFootPrint = nShowFootPrint;

		//GrassDestBlendOne
		int nGrassDestBlendOne;
		if (pMap->Attribute(GrassDestBlendOne_Key, &nGrassDestBlendOne) )
		{
			xMapData.m_bGrassDestBlendOne = nGrassDestBlendOne;
		}

		//Type
        int nType;
        if (pMap->Attribute(Type_Key, &nType) == NULL || nType < 0)
		{
			OutputDebugStringA( "MapError: Type_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Type = nType;

        //MinPlayerLevel
        int nMinPlayerLevel;
        if (pMap->Attribute(MinPlayerLevel_Key, &nMinPlayerLevel) == NULL || nMinPlayerLevel <= 0)
		{
			OutputDebugStringA( "MapError: MinPlayerLevel_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.MinPlayerLevel = nMinPlayerLevel;

        //RegionMapOffsetX
        int nRegionOffsetX = 0;
        if(pMap->Attribute(RegionMapOffsetX_Key, &nRegionOffsetX))
            xMapData.m_nRegionOffsetX = nRegionOffsetX;
        //RegionMapOffsetY
        int nRegionOffsetY = 0;
        if(pMap->Attribute(RegionMapOffsetY_Key, &nRegionOffsetY))
            xMapData.m_nRegionOffsetY = nRegionOffsetY;

        //RegionMapOffsetY
        int nRegionEdge = 1024;
        if(pMap->Attribute(RegionMapEdge_Key, &nRegionEdge))
        {
            xMapData.m_nRegionEdge = nRegionEdge;
        }

        //Order
        int nOrder = 0;
        if (pMap->Attribute(Order_Key, &nOrder))
        {
            xMapData.Order = nOrder;
        }

        //CanPk
        int nCanPk;
        if (pMap->Attribute(CanPk_Key, &nCanPk) == NULL || nCanPk < MapData::EPKM_UnAllow_PK || nCanPk >= MapData::EPKM_End)
		{
			OutputDebugStringA( "MapError: CanPk_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.CanPk = nCanPk;

        //lyhqiecuo
		int nCanDuel;
		if (pMap->Attribute(CanDuel_Key, &nCanDuel) == NULL)
		{
			OutputDebugStringA( "MapError: CanPk_Duel." );
			//next
			//pMap = pMap->NextSiblingElement();
			//continue;
			nCanDuel = 1; //没有找到就默认可以切磋
		}
		xMapData.CanDuel = nCanDuel > 0;

        //CanRide
        int nCanRide;
        if (pMap->Attribute(CanRide_Key, &nCanRide) == NULL || nCanRide < 0 || nCanRide > 1) 
		{
			OutputDebugStringA( "MapError: CanRide_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.CanRide = nCanRide;

		int nCanPet;
		if (pMap->Attribute(CanPet_Key, &nCanPet) == NULL || nCanPet < 0 || nCanPet > 1) 
		{
			OutputDebugStringA( "MapError: CanPet_Key." );
			//next
			//pMap = pMap->NextSiblingElement();
			nCanPet = 1;
		}
		xMapData.CanPet = nCanPet;

        //Duration
        int nDuration;
        if (pMap->Attribute(Duration_Key, &nDuration) == NULL || nDuration < 0) 
		{
			OutputDebugStringA( "MapError: Duration_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Duration = nDuration;

        //Count
        int nCount;
        if (pMap->Attribute(Count_Key, &nCount) == NULL || nCount < 0) 
		{
			OutputDebugStringA( "MapError: Count_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.Count = nCount;

        //UnitCount
        int nUnitCount;
        if (pMap->Attribute(UnitCount_Key, &nUnitCount) == NULL || nUnitCount < 0)
		{
			OutputDebugStringA( "MapError: UnitCount_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.UnitCount = nUnitCount;
    
        //SystemCreate
        int nSystemCreate;
        pMap->Attribute( SystemCreate_Key, &nSystemCreate );
        xMapData.SystemCreate = nSystemCreate;

		int nSunLightRender;
		if(pMap->Attribute( SunLightRender_Key, &nSunLightRender ))
			xMapData.m_bSunLightRender = nSunLightRender;
        Common::_tstring StrMapNameColor = "";
        StrMapNameColor.fromUTF8(pMap->Attribute(MapNameColor_Key));
        xMapData.MapNameColor = StrMapNameColor;

        Common::_tstring StrMapTip = "";
        StrMapTip.fromUTF8(pMap->Attribute(MapTip_Key));
        xMapData.MapTip = StrMapTip;

        //SkyBox
        Common::_tstring SkyBox = "";
        SkyBox.fromUTF8(pMap->Attribute(SkyBox_Key));
        xMapData.SkyBox = SkyBox;

        //EffectPath
        Common::_tstring EffectPath = "";
        EffectPath.fromUTF8(pMap->Attribute(EffectPath_Key));
        xMapData.EffectPath = EffectPath;

        //ExpRate
        float fExpRate = 1.0f;
        if (pMap->QueryFloatAttribute(ExpRate_Key, &fExpRate) != MEXML_SUCCESS ) 
		{
			OutputDebugStringA( "MapError: ExpRate_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        xMapData.ExpRate = fExpRate;

        //TransportDestinations
        MeXmlElement* pTransportDestinations = pMap->FirstChildElement(TransportDestinations_Key);
        if (pTransportDestinations == NULL) 
		{
			OutputDebugStringA( "MapError: TransportDestinations_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}

        MeXmlElement* pTransportDestination = pTransportDestinations->FirstChildElement(TransportDestination_Key);
        while(pTransportDestination != NULL)
        {
            TransportDestination xDestination;

            //Id
            int nId;
            if (pTransportDestination->Attribute(Id_Key, &nId) == NULL || nId < 0) { return false; }
            xDestination.Id = nId;

            //PositionX
            double PositionX;
            if (pTransportDestination->Attribute(PositionX_Key, &PositionX) == NULL) { return false; }
            xDestination.PositionX = PositionX;

            //PositionY
            double PositionY;
            if (pTransportDestination->Attribute(PositionY_Key, &PositionY) == NULL) { return false; }
            xDestination.PositionY = PositionY;

            //Direction
            double Direction;
            if (pTransportDestination->Attribute(Direction_Key, &Direction) == NULL) { return false; }
            xDestination.Direction = Direction;

            //Weight
            int i = 0;
            while(true)
            {
                char szIndex[21] = "";
                sprintf_s(szIndex, sizeof(szIndex) - 1,  Weight_Key, i++);

                int nWeight;
                if (pTransportDestination->QueryIntAttribute(szIndex, &nWeight) == MEXML_SUCCESS)
                {
                    xDestination.vecWeight.push_back(nWeight);
                }
                else
                {
                    break;
                }
            }

            xMapData.AddTransportDestination(xDestination);
        
            //next
            pTransportDestination = pTransportDestination->NextSiblingElement();
        }
        
        //TransportPosition
        MeXmlElement* pTransportPositions = pMap->FirstChildElement(TransportPositions_Key);
        if (pTransportPositions == NULL) 
		{
			OutputDebugStringA( "MapError: TransportPositions_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}
        
        MeXmlElement* pTransportPosition = pTransportPositions->FirstChildElement(TransportPosition_Key);
        while(pTransportPosition != NULL)
        {
            TransportPosition xPosition;

            //Id
            int nId;
            if (pTransportPosition->Attribute(Id_Key, &nId) == NULL || nId < 0) { return false; }
            xPosition.Id = nId;

            //TargetMapId
            int nTargetMapId;
            if (pTransportPosition->Attribute(TargetMapId_Key, &nTargetMapId) == NULL || nTargetMapId < 0) { return false; }
            xPosition.TargetMapId = nTargetMapId;

            //TargetId
            int nTargetId;
            if (pTransportPosition->Attribute(TargetId_Key, &nTargetId) == NULL || nTargetId < 0) { return false; }
            xPosition.TargetId = nTargetId;

            //MinX
            double dMinX;
            if (pTransportPosition->Attribute(MinX_Key, &dMinX) == NULL) { return false; }
            xPosition.MinX = dMinX;

            //MaxX
            double dMaxX;
            if (pTransportPosition->Attribute(MaxX_Key, &dMaxX) == NULL) { return false; }
            xPosition.MaxX = dMaxX;

            //MinY
            double dMinY;
            if (pTransportPosition->Attribute(MinY_Key, &dMinY) == NULL) { return false; }
            xPosition.MinY = dMinY;
    
            //MaxY
            double dMaxY;
            if (pTransportPosition->Attribute(MaxY_Key, &dMaxY) == NULL) { return false; }
            xPosition.MaxY = dMaxY;

            xMapData.AddTransportPosition(xPosition);

            //next
            pTransportPosition = pTransportPosition->NextSiblingElement();
        }

        //RelivePosition
        MeXmlElement* pRelivePositions = pMap->FirstChildElement(RelivePositions_Key);
        if (pRelivePositions == NULL) 
		{
			OutputDebugStringA( "MapError: RelivePositions_Key." );
			//next
			pMap = pMap->NextSiblingElement();
			continue;
		}

        MeXmlElement* pRelivePosition = pRelivePositions->FirstChildElement(RelivePosition_Key);
        while(pRelivePosition != NULL)
        {
            RelivePosition xRelive;
            //Id
            int nId;
            if (pRelivePosition->Attribute(Id_Key, &nId) == NULL || nId < 0) { return false; }
            xRelive.Id = nId;

            int nMapId;
            if( pRelivePosition->Attribute(TargetMapId_Key, &nMapId) == NULL || nMapId == MapErrorId ) { return false; }
            xRelive.MapId = nMapId;

            //PositionX
            double PositionX;
            if (pRelivePosition->Attribute(PositionX_Key, &PositionX) == NULL) { return false; }
            xRelive.PositionX = PositionX;

            //PositionY
            double PositionY;
            if (pRelivePosition->Attribute(PositionY_Key, &PositionY) == NULL) { return false; }
            xRelive.PositionY = PositionY;

            //Direction
            double Direction;
            if (pRelivePosition->Attribute(Direction_Key, &Direction) == NULL) { return false; }
            xRelive.Direction = Direction;

            //Type
            int nType = Relive_Default;
            if (pRelivePosition->Attribute(Type_Key, &nType) == NULL) { return false;}
            xRelive.Type = (nType == 0 ? Relive_Default : nType);

            xMapData.AddRelivePosition(xRelive);

            AddMapRelivePostion( xRelive.MapId, xRelive );          // 添加本城的复活点

            //next
            pRelivePosition = pRelivePosition->NextSiblingElement();
        }
		//新增的
		//SpecRelivePosition
		MeXmlElement* pSpecRelivePositions = pMap->FirstChildElement(SpecRelivePositions_Key);
		if (pSpecRelivePositions) 
		{
			MeXmlElement* pSpecRelivePosition = pSpecRelivePositions->FirstChildElement(SpecRelivePosition_Key);
			while(pSpecRelivePosition != NULL)
			{
				SpecRelivePosition xRelive;
				int nCountryId=-1;
				if (pSpecRelivePosition->Attribute(CountryId_Key, &nCountryId) == NULL || nCountryId < 0) { return false; }
				xRelive.CountryId = nCountryId;
				//Id
				int nId;
				if (pSpecRelivePosition->Attribute(Id_Key, &nId) == NULL || nId < 0) { return false; }
				xRelive.Id = nId;

				int nMapId;
				if( pSpecRelivePosition->Attribute(TargetMapId_Key, &nMapId) == NULL || nMapId == MapErrorId ) { return false; }
				xRelive.MapId = nMapId;

				//PositionX
				double PositionX;
				if (pSpecRelivePosition->Attribute(PositionX_Key, &PositionX) == NULL) { return false; }
				xRelive.PositionX = PositionX;

				//PositionY
				double PositionY;
				if (pSpecRelivePosition->Attribute(PositionY_Key, &PositionY) == NULL) { return false; }
				xRelive.PositionY = PositionY;

				//Direction
				double Direction;
				if (pSpecRelivePosition->Attribute(Direction_Key, &Direction) == NULL) { return false; }
				xRelive.Direction = Direction;

				//Type
				int nType = Relive_Default;
				if (pSpecRelivePosition->Attribute(Type_Key, &nType) == NULL) { return false;}
				xRelive.Type = (nType == 0 ? Relive_Default : nType);

				xMapData.AddSpecRelivePosition(xRelive);

				//AddMapRelivePostion( xRelive.MapId, xRelive );          // 添加本城的复活点

				//next
				pSpecRelivePosition = pSpecRelivePosition->NextSiblingElement();
			}
		}
        
        MeXmlElement* pStatuss_Keys = pMap->FirstChildElement(Statuss_Key);
        if (pStatuss_Keys != NULL)
        {
            MeXmlElement* pStatus_Key = pStatuss_Keys->FirstChildElement(Status_Key);
            while(pStatus_Key != NULL)
            {
                int nStatusId;
                if (pStatus_Key->Attribute(Id_Key, &nStatusId) == NULL || nStatusId < 0) { return false; }

                int nStatusLevel;
                if (pStatus_Key->Attribute(StatusLevel_Key, &nStatusLevel) == NULL || nStatusLevel < 0) { return false; }

                Status status;
                status.Id = nStatusId;
                status.Level = nStatusLevel;
                xMapData.AddStatus(status);

                //next
                pStatus_Key = pStatus_Key->NextSiblingElement();
            }
        }
		MeXmlElement* pBloom = pMap->FirstChildElement(Bloom_Key);
		if (pBloom != NULL)
		{
			double bloomscale;
			double luminance;

            if ( pBloom->Attribute(BloomScale_Key, &bloomscale) == NULL ) { return false; }
            if ( pBloom->Attribute(BloomLuminance_Key, &luminance) == NULL ) { return false; }

			xMapData.m_BloomScale = bloomscale;
			xMapData.m_Luminance = luminance;
		}

		MeXmlElement* pBrightContrast = pMap->FirstChildElement( BrightContrast_Key );
		if( pBrightContrast )
		{
			float fBrightness = 0.f, fContrastR = 1.f, fContrastG = 1.f, fContrastB = 1.f;
			pBrightContrast->Attribute( BrightnessOffset_Key, &fBrightness );
			pBrightContrast->Attribute( ContrastOffsetR_Key, &fContrastR );
			pBrightContrast->Attribute( ContrastOffsetG_Key, &fContrastG );
			pBrightContrast->Attribute( ContrastOffsetB_Key, &fContrastB );
			xMapData.m_fBrightnessOffset = fBrightness;
			xMapData.m_fContrastOffsetR = fContrastR;
			xMapData.m_fContrastOffsetG = fContrastG;
			xMapData.m_fContrastOffsetB = fContrastB;
		}
        

        //添加
        AddMapData(xMapData);

        //next
        pMap = pMap->NextSiblingElement();
    }

    return true;
}
