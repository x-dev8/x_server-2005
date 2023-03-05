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

    bool LoadTrafficRoute(); // ���ؽ�ͨ·��
    void ClearRouteConfig(); // ���Route��Ϣ

    // ��ȡ·�ߵ� nTrafficID ��ͨ·��Id, dwRouteStep ����ڼ���, fSpeed �ƶ��ٶ�, vNextRoutePos ��һ��·�� fErrDistance �������
    bool GetCurTrafficRoute( int nTrafficID, bool bBack, uint16& dwRouteStep,  float& fSpeed, D3DXVECTOR3& vNextRoutePos,  float& fErrDistance, SMovePos& xRouteMovePos  );

    bool LoadRouteInfo( const char* szFileName ); // ����·����Ϣ
    bool GetRouteInfo( DWORD dwMapId, unsigned long uRouteId, SRoute& resultRoute );
    SRoute* GetRouteInfo( DWORD dwMapId, unsigned long nRouteId );
	D3DXVECTOR3 GetLastRoutePoint( int nTrafficID );

private:
    typedef std::multimap<unsigned long, SRoute> MapRoute;
    typedef MapRoute::iterator                   ItrMapRoute;
    typedef std::pair<ItrMapRoute, ItrMapRoute>  RangeResult;

    MapRoute _MapRoutes;

    typedef std::vector<D3DXVECTOR3> TrafficRoutePoss;
    TrafficRoutePoss m_veTrafficRoute[const_MaxTrafficRoute]; // ���ͨ·����
};

RouteManager& GetRouteManager();

#endif // __COMMON_GAMETRAFFIC_H__
