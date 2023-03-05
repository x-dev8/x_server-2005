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

    // ����Tile���
    int AddToTile( GameObjectId stID, short stTileID );
    void RemoveFromTile( GameObjectId stID,short stTileID );

    // �㲥 BR_View * BR_View �ķ�Χ
    void SendMsgToView( GameObjectId stID,short stArea, Msg *pMsg,bool bExceptMe = false );

    // �㲥 BR_Region * BR_Region �ķ�Χ
    void SendMsgToRegion( GameObjectId id, short stArea, Msg *pMsg );

    // �㲥 һС���ͼ More_nMapSize / dr_stageAreaSize = 8 (8 * 8)������
    void SendMsgToArea( Msg* pMsg, int nX, int nY );

    // �㲥 ȫStage ��Χ
    void SendMsgToStage( Msg* pMsg );

    // �㲥 ȫStage ��Χ �̶�����
    void SendCountryMsgToStage( Msg* pMsg, TCountryId country, uint16 uchLevel, uint16 stExceptID );

private:
    enum BroadcastRange
    { // ����
        BR_View = 3,
        BR_Region = 17,
    };

    DWORD m_dwMapCfgID; // ��ͼId,��ӦMapSetting�е�MapId
    DWORD m_dwStageID;  // ��Ӧʵ�ʵ�Id

    BigTile* _pTiles;
    
    int m_iWidth;  // ������
    int m_iHeight; // ������

    int m_iAreaCol; // Area������
    int m_iAreaRow; // Area������
    int m_iAreaMax;
};

#endif // __GATESERVER_STAGE_H__
