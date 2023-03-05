/********************************************************************
	Filename: 	PosChangePackage.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_POSCHANGE_PACKAGE_H__
#define __GATESERVER_POSCHANGE_PACKAGE_H__

#include "GlobalDef.h"
#include "MessageDefine.h"

struct SPosChangeInfo
{
    enum EOptimizeType
    { // 优化类型
        Optimize_None = 0           , // 没有优化
        Optimize_Pos                , // 坐标优化
        Optimize_Dir                , // 朝向优化
        Optimize_PosAndDir          , // 坐标和朝向都优化
        Optimize_MovingPos          , // 移动坐标优化
        Optimize_MovingPosAndDir    , // 移动坐标和朝向优化
        Optimize_ClosingToLockTarget, // 靠近目标的优化
        Optimize_End,
    };

    SPosChangeInfo()
    {
        memset( this, 0, sizeof(*this) );
        chOptimize = Optimize_None;
    }

    GameObjectId      nID       ; // 发生位置变化的Id
    GameObjectId      nTargetID ; // 靠近的目标的Id
    uint8			   nType     ; // 组成此信息的源消息协议
    D3DXVECTOR3		   vPos      ; // 所在位置
    D3DXVECTOR3		   vEndPos   ; // 要到的位置
	char               chDirX    ; // X的方向分量
	char			   chDirY    ; // X的方向分量
	char			   chDirZ    ; // Y的方向分量
    uint8			   chOptimize; // 优化类型
};

class CPosChangePackage
{
public:
    //和消息相对应的类型
    enum EMoveType
    {
        PACK_MSG_PLAYERMOVINGPOS             = 0,
        PACK_MSG_PLAYERMOVINGPOSANDDIR          ,
        PACK_MSG_PLAYERPOS                      ,
        PACK_MSG_PLAYERDIR                      ,
        PACK_MSG_PLAYERPOSANDDIR                ,
        PACK_MSG_PLAYERVERIFYPOS                ,
        PACK_MSG_UNPLAYERMOVINGTOPOS            ,
        PACK_MSG_UNPLAYERVERIFYPOS              ,
        PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET    ,
    };

    CPosChangePackage();
    virtual ~CPosChangePackage();

    bool            MakePackMsg( MsgPosChange& msg ); // 生成一个消息包
    bool            LoadPackMsg( MsgPosChange& msg ); // 载入一个消息包

    bool            PushPosChangeInfo( const SPosChangeInfo& info );
    SPosChangeInfo* PopPosChangeInfo();

    void            SetMaxSize(unsigned int nSize);
    void            Clear();

protected:
    std::vector<SPosChangeInfo> m_msglist;
    unsigned int                m_nMaxSize;

private:
#pragma pack(push, 1)
    struct SMoveUnitHead
    {
        GameObjectId shID;
        uint8  chType;
        uint8  chOptimize;
    };

    struct tagPACK_MSG_PLAYERMOVINGPOS
    { // 移动中位置
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERMOVINGPOSANDDIR
    { // 移动中位置 方向
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERPOS
    { // 静止的位置
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERDIR
    { // 静止的方向
        char chDirX;
        char chDirY;
        char chDirZ;
    };

    struct tagPACK_MSG_PLAYERPOSANDDIR
    { // 静止的位置和方向
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERVERIFYPOS
    { // 验证位置
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_UNPLAYERMOVINGTOPOS
    { // 非玩家开始和结束位置
	    D3DXVECTOR3 vStartPos;
	    D3DXVECTOR3 vEndPos;
    };

    struct tagPACK_MSG_UNPLAYERVERIFYPOS
    { // 非玩家验证位置与方向
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };
    struct tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET
    { // 非玩家结束锁定目标
        D3DXVECTOR3   vPos;
        GameObjectId shTargetID;
    };
#pragma pack(pop)
};

#endif // __GATESERVER_POSCHANGE_PACKAGE_H__
