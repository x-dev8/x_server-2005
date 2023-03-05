#include "RouteManager.h"
#include "FuncPerformanceLog.h"
#include "CfgFileLoader.h"
#include "ItemDetail.h"
#include "Tinyxml/tinyxml.h"
#include "tstring.h"

RouteManager& GetRouteManager()
{
    static RouteManager theTrafficManager;
    return theTrafficManager;
}

RouteManager::RouteManager()
{
    for( int i = 0; i < const_MaxTrafficRoute; i++ )
    {
        m_veTrafficRoute[i].clear();
    }
}

RouteManager::~RouteManager()
{
    for( int i = 0; i < const_MaxTrafficRoute; i++ )
    {
        m_veTrafficRoute[i].clear();
    }
}

bool RouteManager::LoadTrafficRoute()
{
    for( int i = 0; i<GettheItemDetail().GetTrafficNumber(); ++i )
    {
        ItemDefine::STraffic* trafficInfo = GettheItemDetail().GetTraffic(i);
        if ( !trafficInfo)
            return false;

        SRoute route;
        bool bResult = GetRouteInfo( trafficInfo->nMapID, trafficInfo->nRouteID, route );
        if ( !bResult)
            return false;
    }

    return true;
}

bool RouteManager::GetCurTrafficRoute( int nTrafficID, bool bBack, uint16& dwRouteStep, float& fSpeed, D3DXVECTOR3& vNextRoutePos, float& fErrDistance, SMovePos& xRouteMovePos )
{
    ItemDefine::STraffic* trafficInfo = GettheItemDetail().GetTraffic( nTrafficID );
    if ( !trafficInfo)
    { return false; }

    SRoute sRoute;
    bool bResult = GetRouteInfo( trafficInfo->nMapID, trafficInfo->nRouteID, sRoute );
    if ( !bResult)
    { return false; }

    int nSize = sRoute.allMovePos.size();
    if ( dwRouteStep >= nSize)
    { return false; }

    D3DXVECTOR3 vRoutePos;
    if( bBack )
    {
        vRoutePos.x = sRoute.allMovePos[nSize - 1 - dwRouteStep].fX;
        vRoutePos.y = sRoute.allMovePos[nSize - 1 - dwRouteStep].fY;
        if ( sRoute.flyRoute )
        { vRoutePos.z   = sRoute.allMovePos[nSize - 1 - dwRouteStep].fZ; }
        fSpeed          = sRoute.allMovePos[nSize - 1 - dwRouteStep].fV;
        xRouteMovePos   = sRoute.allMovePos[nSize - 1 - dwRouteStep] ;
    }
    else
    {
        vRoutePos.x = sRoute.allMovePos[dwRouteStep].fX;
        vRoutePos.y = sRoute.allMovePos[dwRouteStep].fY;
        if ( sRoute.flyRoute )
        { vRoutePos.z   = sRoute.allMovePos[dwRouteStep].fZ; }
        fSpeed          = sRoute.allMovePos[dwRouteStep].fV;
        xRouteMovePos   = sRoute.allMovePos[dwRouteStep] ;
    }

    if ( !sRoute.flyRoute )
    {
        vRoutePos.z     = 0;
        vNextRoutePos.z = 0;
    }

    float fDistance = D3DXVec3Length( &( vNextRoutePos - vRoutePos ) );

    if( fDistance < fSpeed )
    {
        DWORD dwNextRouteStep = dwRouteStep + 1;
        if ( !( xRouteMovePos.dwTime > 0 || xRouteMovePos.stSceneId > 0 ) )
        {
            for( ; dwNextRouteStep < nSize; ++dwNextRouteStep )
            {
                SMovePos xTempMovePos;
                if( bBack )
                {
                    vRoutePos.x = sRoute.allMovePos[nSize - 1 - dwNextRouteStep].fX;
                    vRoutePos.y = sRoute.allMovePos[nSize - 1 - dwNextRouteStep].fY;
                    vRoutePos.z = sRoute.allMovePos[nSize - 1 - dwNextRouteStep].fZ;
                    xTempMovePos= sRoute.allMovePos[nSize - 1 - dwNextRouteStep]   ;
                }
                else
                {
                    vRoutePos.x = sRoute.allMovePos[dwNextRouteStep].fX;
                    vRoutePos.y = sRoute.allMovePos[dwNextRouteStep].fY;
                    vRoutePos.z = sRoute.allMovePos[dwNextRouteStep].fZ;
                    xTempMovePos= sRoute.allMovePos[dwNextRouteStep]   ;
                }

                fDistance = D3DXVec3Length( &( vNextRoutePos - vRoutePos ) );

                if ( xTempMovePos.dwTime > 0 || xTempMovePos.stSceneId > 0 )
                { break; }

                if( fDistance > fSpeed )
                { break; }
            }
        }
        dwRouteStep   = dwNextRouteStep;
        vNextRoutePos = vRoutePos;
        return true;
    }
    else
    {
        fErrDistance = fDistance;
        vNextRoutePos = vRoutePos;
        return true;
    }
    return false;
}

bool RouteManager::LoadRouteInfo( const char* szFileName )
{
    if ( !szFileName)
        return false;

    TiXmlDocument doc;
    if( !doc.LoadFile( szFileName ) )
        return false;

    TiXmlElement* pRoot = doc.FirstChildElement("NPCRoute");
    if ( !pRoot)
        return false;

    TiXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
    while (pMapNode)
    {
        int mapId = 0;
        pMapNode->QueryIntAttribute("id",&mapId);

        TiXmlElement* pNPCRoute = pMapNode->FirstChildElement( "NPCRoute");
        while (pNPCRoute)
        {
            SRoute route;

            int routeIndex = 0,nextMapId = 0,nextRouteId = 0,flyRoute = 0 ;
            pNPCRoute->QueryIntAttribute("NPCRouteIndex",   &routeIndex     );
            pNPCRoute->QueryIntAttribute("NextMapId",       &nextMapId      );
            pNPCRoute->QueryIntAttribute("NextRouteId",     &nextRouteId    );
            pNPCRoute->QueryIntAttribute("FlyRoute",        &flyRoute       );
            route.mapId         = mapId;
            route.routeId       = routeIndex;
            route.nextMapId     = nextMapId;
            route.nextRouteId   = routeIndex;
            route.flyRoute      = flyRoute;

            int x = 0;
            while( true ) 
            {
                char strRoutePoint[65] = {0};
                sprintf_s( strRoutePoint, sizeof(strRoutePoint)-1, "RoutePoint%d", x );

                TiXmlElement* pRoutePoint = pNPCRoute->FirstChildElement( strRoutePoint);
                if ( !pRoutePoint)
                    break;

                SMovePos movePos;

                float posX; float posY; float posZ;float WalkLength;float WalkSpeed;int nStayTime;int nSceneID;
                pRoutePoint->QueryFloatAttribute("PosX",&posX);
                pRoutePoint->QueryFloatAttribute("PosY",&posY);
                if ( TIXML_SUCCESS != pRoutePoint->QueryFloatAttribute("PosZ",&posZ))
                { posZ = WORLD_HEIGHT;}

                pRoutePoint->QueryFloatAttribute("WalkSpeed",&WalkSpeed);
                pRoutePoint->QueryFloatAttribute("WalkLength",&WalkLength);
                pRoutePoint->QueryIntAttribute("StayTime",&nStayTime);
                pRoutePoint->QueryIntAttribute("SceneID",&nSceneID);

                Common::_tstring strActionName;
                strActionName.fromUTF8( pRoutePoint->Attribute("Action") );
                if ( atoi( strActionName.c_str() ) != -1 )
                { sprintf_s( movePos.szActionName, sizeof(movePos.szActionName)-1, strActionName.c_str() ); }

                movePos.fX      = posX;
                movePos.fY      = posY;
                movePos.fZ      = posZ;
                movePos.fV      = WalkSpeed;
                movePos.fStep   = WalkLength;
                movePos.dwTime  = nStayTime;
                movePos.stSceneId = nSceneID;

                route.allMovePos.push_back( movePos );
                ++x;
            } 

            _MapRoutes.insert( MapRoute::value_type(mapId, route));

            pNPCRoute = pNPCRoute->NextSiblingElement( "NPCRoute");
        }


        pMapNode = pMapNode->NextSiblingElement("Map");
    }
    return true;
}

bool RouteManager::GetRouteInfo( DWORD dwMapId, unsigned long routeId, SRoute& resultRoute )
{
    RangeResult result = _MapRoutes.equal_range( dwMapId );

    MapRoute::iterator it = result.first;
    bool bFind = false;
    for ( ; it != result.second; ++it)
    {
        if ( it->second.routeId == routeId)
        {
            resultRoute = it->second;
            bFind = true;
        }
    }

    return bFind;
}

SRoute* RouteManager::GetRouteInfo( DWORD dwMapId, unsigned long nRouteId )
{
    RangeResult result = _MapRoutes.equal_range( dwMapId );

    MapRoute::iterator it = result.first;
    for ( ; it != result.second; ++it )
    {
        if ( it->second.routeId == nRouteId )
        { return &( it->second ); }
    }

    return NULL;
}

void RouteManager::ClearRouteConfig()
{
    _MapRoutes.clear();

    for ( int i = 0; i < const_MaxTrafficRoute; ++i )
    {
        m_veTrafficRoute[i].clear();
    }
}

D3DXVECTOR3 RouteManager::GetLastRoutePoint( int nTrafficID )
{
	D3DXVECTOR3 vRoutePos = D3DXVECTOR3( 0, 0, 0 );

	ItemDefine::STraffic* trafficInfo = GettheItemDetail().GetTraffic(nTrafficID);
	if ( !trafficInfo)
		return vRoutePos;

	SRoute sRoute;
	bool bResult = GetRouteInfo( trafficInfo->nMapID, trafficInfo->nRouteID, sRoute );
	if ( !bResult)
		return vRoutePos;

	int nSize = sRoute.allMovePos.size();
	vRoutePos.x = sRoute.allMovePos[ nSize - 1 ].fX;
	vRoutePos.y = sRoute.allMovePos[ nSize - 1 ].fY;
	if ( sRoute.flyRoute )
	{ vRoutePos.z = sRoute.allMovePos[ nSize - 1 ].fZ; }

	return vRoutePos;
}
