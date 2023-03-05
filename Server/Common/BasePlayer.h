/********************************************************************
    Filename:     BasePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_BASEPLAYER_H__
#define __GAMESERVER_BASEPLAYER_H__

#include "BaseCharacter.h"
#include "ScriptVM.h"
#include "ItemBag.h"
#include "GraphicCodeCheck.h"
#include "Dxsdk/d3dx9math.h"

//#define PLAYERCHAR_MAX_VAR    4096

#define PLAYERCHAR_MAX_PET    4

#define CHECKMOVINGRATE 20

class BasePlayer;

extern void PlayerLogFunc(BasePlayer* pPlayer, const char* szFormat, ...);

class BasePlayer : public BaseCharacter
{ // 基础玩家类
//////////////////////////////////////////////////////////////////////////
// 结构体
protected:
    struct SPick
    {
        short stPickX;
        short stPickY;
        short stItemCharID;        
        bool  bSet; //是否有效
    };

//////////////////////////////////////////////////////////////////////////
// 方法
public:    
    BasePlayer();
    virtual ~BasePlayer() {};

    // 发消息给玩家 系统右边框的消息
    virtual void ShowInfo( bool bTile, int type, const char* string, ... );
    virtual void ShowInfo( const char* string, bool bTile = false, int type = 282 );
    virtual void ShowInfo(  bool bTile, int type, unsigned short ustStringID, UnionParam* pParam = NULL, int nCount = 0 );
    static  void ShowInfoToWorld( bool bTile, int type, const char* string, ... );

    void SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir ); // 地图跳转
public:
    virtual bool ProcessMsg(Msg* pMsg);
    virtual void OnDeath(void);
    virtual bool IsCanSwitchStage(); 
    virtual Msg* FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);    
    virtual void SendVerifyPos(void); // 发送矫正坐标消息
    virtual void PlaySubSkill(short stSkillID, short* pSubSkill, short* pSubSkillLevel, int     * pSubcount);
    void SetDeathWaitForRelive( bool bFlag ) { m_bDeathAndWaitForRelive = bFlag; }
    virtual void TellClient( const char* string, ... );   
    virtual void TellClient( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 );
    virtual void ShowFormatInfo( const char* szFormat, ... );
    virtual void ShowMsgBox( const char* string, ... );

    void Log     ( const char* szFormat, ...); // Log
    void DebugLog( const char* szFormat, ...); // Log

    void ShoppingLog( const char* szFormat, ...); // 商城购物日志
    void DoAssaultMoving();                      // 正在冲锋移动

    bool DoHitch( int nTrafficID, bool bBack, bool bGoOn );  // 进行搭乘移动
    void DoHitchMoving( int nTrafficID );        // 进行搭乘移动
    void CancelHitchMoving();                    // 结束搭乘移动

    int  GetCurTrafficID();                      // 获取当前路线的ID    
    long TryRespondChangeStage();                // 尝试响应客户端切场景效应

    void CheckCheatLog( const char* szFormat, ... );    // 外挂LOG

public:
    BOOL CheckMoving();                 // 检测移动消息的合法性
    bool CheckPosRightful();            // 检测位置的正确性
    void CheckCredit();                 // 检测荣誉值是否正确
    bool CheckMovingMsgSendTime( DWORD dwSendTime ); // 检测移动消息上发时间的正确性
    void ResetCheckMoving();                         // 重置要测试的移动信息(开始新一轮的移动测试)
    void SendVerifyPos( float fx, float fy );        // 矫正坐标    
    bool IsNeedFixWorldCoordinate( int GridX, int nGridY); // 传入新的格子坐标 判断是否需要纠正客户端世界坐标系坐标 float
    char* GetSessionKey(){ return _szSessionKey;}
    bool  SetSessionKey ( const char* szSessionKey );

    void IntonateInterrupt( int8 nType );           // 吟唱打断

protected:
    // 消息
    void OnQueryMove();
    void OnQueryDisplayName(Msg *pMsg);
    void OnSeeAttack( Msg* pMsg );
    void OnWhoDie( Msg* pMsg );    
    void OnQueryAllGameProperty( Msg* pMsg );
    void OnAckAllGameProperty( Msg* pMsg );
    void OnGetLag();
    virtual void OnGetPlayerInfo(Msg*pMsg);     // 客户端发过来的请求知道莫个npc的数据

    // 处理玩家移动的逻辑
    void OnMsgPlayerMovingPos( const Msg* pMsg );
    void OnMsgPlayerMovingPosToDir( const Msg* pMsg );
    void OnMsgPlayerPos( const Msg* pMsg );
    void OnMsgPlayerDir( const Msg* pMsg );
    void OnMsgPlayerPosAndDir( const Msg* pMsg );
    void OnMsgIntonateInterrupt( const Msg* pMsg );
    void OnMsgJump( const Msg* pMsg );
    void OnMsgDrawWeapon( const Msg* pMsg );
    void OnMsgDrawInWeapon( const Msg* pMsg );
    void OnMsgReadytoUseSpecialSkill();
    virtual void OnReqChangeDir( const Msg* pMsg );
    virtual void OnQueryCharAround( const Msg* pMsg );    
    virtual void OnPingMsg( const Msg* pMsg ); //对客户端法送过来的PING消息的处理

    void SendRefreshChar();             //复生
    void Dieing();                      // 死亡状态时的处理程序
    void LogOnlineInfo();

public:
    CGraphicCodeCheck m_graphiccodecheck;

//////////////////////////////////////////////////////////////////////////
// 成员变量
protected:
    //D3DXVECTOR3 m_vLastSavedVerifyPos;         // 最后一次记录的矫正坐标
    //D3DXVECTOR3 m_vLastSavedVerifyDir;         // 最后一次记录的矫正方向
    DWORD m_dwStartReadytoSendVerifyPosMsgTime;  // 开始准备发送矫正消息的时间
    DWORD m_dwLastSendHitchMoveMsgTime;          // 上次发送搭乘移动消息的时间
    //DWORD m_dwLastSendPlayerMovingMsgTime;     // 最后发送移动消息的时间
    int   m_nCredit;                             // 记录玩家的信誉值
    bool  m_bPosDebugOpen;                       // 自己的位置显示开关
    int   m_nKickCount;                          // 记录踢的次数
    DWORD m_dwEnterWorldClientTime;              // 记录玩家进入游戏世界的客户端时间
    DWORD m_dwEnterWorldServerTime;              // 记录玩家进入游戏世界的服务端时间
    DWORD m_dwClientLastSendMovingMsgTime;       // 记录客户端最后发送给服务器移动消息的时间
    DWORD m_dwClientLastSendMovingMsgServerTime; // 客户端最后发送给服务器移动消息的服务器时间
    bool  m_bHitchMoving;                        // 搭乘移动
    bool  m_bHitchBack;                          // 是否是沿路搭乘回来
    int   m_nTrafficID;                          // 搭乘路线的ID
    DWORD m_dwRouteStep;                   
    short m_shCheckMovingCount;                  // 检测移动消息的次数
    short m_shCheckMovingIndex;                  // 检测本次移动的索引
    bool  m_bAssaultMovingProcess;               // 冲锋技能的特殊处理
    DWORD m_dwClientPassedTimePerCheck;          // 每次测试时候 客户端累计的经过的时间长度
    float m_fLastMoveSpeedPerCheck;              // 每次检测保存的上一次的移动速度，为冲锋 坚决状态加速的判定
    D3DXVECTOR3 m_vStartMovingPosPerCheck;       // 每次检测时记录的坐标
    D3DXVECTOR3 m_vMovingBufPerCheck;            // 每次的移动量保存器
    bool  m_bDeathAndWaitForRelive;              // 是否角色已经死亡，等待复生
    char  m_szLoginName[ dr_MaxNameString ];
    char  m_szLoginIP[ dr_MaxNameString ];
    char  m_cMoveSerial; //移动序列号
    unsigned char m_ucCharStatus;
    bool          IsLoadAccountNameSucc;
    char          _szSessionKey[32+1];
};

//////////////////////////////////////////////////////////////////////////
// inline
inline bool BasePlayer::SetSessionKey ( const char* szSessionKey )
{
    if ( NULL == szSessionKey)
    { return false; }
    strncpy_s( _szSessionKey,sizeof(_szSessionKey),szSessionKey,sizeof(_szSessionKey)-1);
    return true;
}

#endif // __GAMESERVER_BASEPLAYER_H__
