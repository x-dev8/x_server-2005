/********************************************************************
    Filename:     Stage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_STAGE_H__
#define __GATESERVER_STAGE_H__

#pragma once

#include "BigTile.h"
#include "Memory_Pool.h"

class CGateStage //: INHERIT_POOL( CGateStage )
{
public:
    CGateStage();
    virtual ~CGateStage();

    bool InitStage( int iWidth, int iHeight);

    void SetStageId( DWORD dwStageId ){ m_dwStageID = dwStageId; }
    DWORD GetStageId(){ return m_dwStageID; }

    void SetMapCfgId( DWORD dwMapCfgId ){ m_dwMapCfgID = dwMapCfgId; }
    DWORD GetMapCfgId(){ return m_dwMapCfgID; }

    // 返回Tile编号
    int AddToTile( GameObjectId stID, short stTileID );
    void RemoveFromTile( GameObjectId stID,short stTileID );

    // 广播 BR_View * BR_View 的范围
    void SendMsgToView( GameObjectId stID,short stArea, Msg *pMsg,bool bExceptMe = false );

    // 广播 BR_Region * BR_Region 的范围
    void SendMsgToRegion( GameObjectId id, short stArea, Msg *pMsg );

    // 广播 一小块地图 More_nMapSize / dr_stageAreaSize = 8 (8 * 8)的区域
    void SendMsgToArea( Msg* pMsg, int nX, int nY );

    // 广播 全Stage 范围
    void SendMsgToStage( Msg* pMsg );

    // 广播 全Stage 范围 固定国家
    void SendCountryMsgToStage( Msg* pMsg, TCountryId country, uint16 uchLevel, uint16 stExceptID );

private:
    enum BroadcastRange
    { // 奇数
        BR_View = 3,
        BR_Region = 17,
    };

    DWORD m_dwMapCfgID; // 地图Id,对应MapSetting中的MapId
    DWORD m_dwStageID;  // 对应实际的Id

    BigTile* _pTiles;
    
    int m_iWidth;  // 场景长
    int m_iHeight; // 场景宽

    int m_iAreaCol; // Area的列数
    int m_iAreaRow; // Area的行数
    int m_iAreaMax;
};

#endif // __GATESERVER_STAGE_H__
