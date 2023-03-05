/********************************************************************
    Filename:    RouteManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ROUTEMANAGER_H__
#define __COMMON_ROUTEMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GlobalDef.h"
#include "Dxsdk/d3dx9math.h"

#define theRouteManager GetRouteManager()

class RouteManager
{
private:
    enum EConstDefine
    {
        const_MaxTrafficRoute = 1024
    };
        
public:
    RouteManager();
    ~RouteManager();

    bool LoadTrafficRoute(); // 加载交通路线
    void ClearRouteConfig(); // 清空Route信息

    // 获取路线点 nTrafficID 交通路径Id, dwRouteStep 到达第几步, fSpeed 移动速度, vNextRoutePos 下一个路点 fErrDistance 错误距离
    bool GetCurTrafficRoute( int nTrafficID, bool bBack, uint16& dwRouteStep,  float& fSpeed, D3DXVECTOR3& vNextRoutePos,  float& fErrDistance, SMovePos& xRouteMovePos  );

    bool LoadRouteInfo( const char* szFileName ); // 加载路点信息
    bool GetRouteInfo( DWORD dwMapId, unsigned long uRouteId, SRoute& resultRoute );
    SRoute* GetRouteInfo( DWORD dwMapId, unsigned long nRouteId );
	D3DXVECTOR3 GetLastRoutePoint( int nTrafficID );

private:
    typedef std::multimap<unsigned long, SRoute> MapRoute;
    typedef MapRoute::iterator                   ItrMapRoute;
    typedef std::pair<ItrMapRoute, ItrMapRoute>  RangeResult;

    MapRoute _MapRoutes;

    typedef std::vector<D3DXVECTOR3> TrafficRoutePoss;
    TrafficRoutePoss m_veTrafficRoute[const_MaxTrafficRoute]; // 最大交通路线数
};

RouteManager& GetRouteManager();

#endif // __COMMON_GAMETRAFFIC_H__
