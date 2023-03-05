/********************************************************************
    Filename:     NetControl.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_NETCONTROL_H__
#define __GAMESERVER_NETCONTROL_H__

#pragma once

#include "IBaseControl.h"
#include "Memory_Pool.h"
#include "NewWithDebug.h"
//#include "MeNetwork.h"
#include "network.h"
#include "MessageDefine.h"
#include "MsgQueue.h"

using namespace network;

class NetControl : public IBaseControl
{
public:
    enum EConstDefine
    {
       const_iInSize         = 50 * 50 ,
       const_iOutSize        = 200 * 50,
       const_iMaxQueueMsgNum = 1000,
    };

    virtual ~NetControl(){};
    virtual Msg* GetMsg();               // 会进行消息合包 大于 MSGMAXSIZE
    virtual void Push2In  ( Msg* pMsg ); // 会进行消息切割 大于 MSGMAXSIZE

    virtual Msg* GetMsgEx();             // 不会进行消息合包 大于 MSGMAXSIZE
    virtual void Push2InEx( Msg* pMsg ); // 不会进行消息切割 大于 MSGMAXSIZE

    virtual void OnCriticalError(){}

protected:
    MsgQueueNotLock m_in;
};

//////////////////////////////////////////////////////////////////////////
class CItemControl : public NetControl, INHERIT_POOL_PARAM( CItemControl, 50 )
{
public:
    DECLARE_POOL_FUNC( CItemControl )

    virtual bool Process() { return true; }

    CItemControl();
    virtual ~CItemControl() {}
};

//////////////////////////////////////////////////////////////////////////
// 电脑接管控制类
class CAICharacterControl : public NetControl
{
public:
    static CAICharacterControl* CreateInstance() { return CNewWithDebug<CAICharacterControl>::Alloc(1, "CAICharacterControl::CreateInstance中创建CAICharacterControl实例");}
    virtual void Release()                       { CNewWithDebug<CAICharacterControl>::Free(this);}
    virtual void OnCriticalError()               { }
};

//////////////////////////////////////////////////////////////////////////
class CEffectControl : public NetControl
{
public:
    static CEffectControl* CreateInstance() { return CNewWithDebug<CEffectControl>::Alloc(1, "CEffectControl::CreateInstance中创建CEffectControl实例");}
    virtual void Release()                  { CNewWithDebug<CEffectControl>::Free(this);}

	virtual bool Process() { return true; }
	virtual void Run(DWORD dwCostTime){}

	CEffectControl(){}
	virtual ~CEffectControl()
	{}
};

//////////////////////////////////////////////////////////////////////////
class CNpcCtrl : public IBaseControl
{ // NPC没有消息处理
public:
    static CNpcCtrl* CreateInstance() { return CNewWithDebug<CNpcCtrl>::Alloc(1, "CNpcCtrl::CreateInstance中创建CNpcCtrl实例"); }
    virtual void Release() { CNewWithDebug<CNpcCtrl>::Free(this); }

    virtual void Push2In( Msg*pMsg )    {}
    virtual void Push2InEx( Msg* pMsg ) {}
    virtual bool Process(){ return true; };
};
//////////////////////////////////////////////////////////////////////////
class NetControlEx : public NetControl, INHERIT_POOL_PARAM( NetControlEx,50 )
{
public:
    enum EConstDefine
    {
        const_iErrTimeout = 500
    };

public:
    DECLARE_POOL_FUNC(NetControlEx)
    //static NetControlEx* CreateInstance() {return CNewWithDebug<NetControlEx>::Alloc(1, "NetControlEx::CreateInstance中创建NetControlEx实例");}
    //virtual void Release() {CNewWithDebug<NetControlEx>::Free(this);}

    NetControlEx();
    virtual ~NetControlEx();
    
    /*IMeSocket*/Socketer* GetSock(){ return m_sock; }
    
    void RecvMsg();       // 接收，由外部调用，必须判断select通过
    void TrySendAllMsg(); // 将消息队列中的消息发送出去，由外部调用，select通过
    
    void AddErrorTimeout( int iData = 1 ); //错误超时
    void GetPeerName( char *szName,int iLen );
    
    virtual bool Process(){ return true; }
    virtual bool IsNetworkCtrl(){return true;}
    virtual void OnCriticalError(void){ OnConnectError();}

    //unsigned short GetLifeCode(){ return m_ustLifeCode; }
private:
    //请使用GettheServer().SendMsg
    //假设pChar->GetControl()->SendMsg
    //改为GettheServer().SendMsg( pChar,pMsg,sendrange_single );
    virtual void SendMsg( Msg *pMsg );  //发送

    //将收到的数据组成包
    void PushBuf2Msg( char*sBuf,int iSize );
    bool SendRest();

    void OnConnectError();    
private:
    /*IMeSocket*/Socketer* m_sock;    
    MsgQueue   m_out; //输出队列
    
    int  m_iSendRestSize;  //发送，保存上次发送调用未发送完的数据    
    int  m_iSendRestStart; //剩余数据的起始位置
    char m_sSendRest[ MSGMAXSIZE ];

    int  m_iRecvRestSize;//接收到的数据，没有组成包
    char m_sRecvRest[ MSGMAXSIZE ];

    int  m_iErrTimeout;
};

#endif // __GAMESERVER_NETCONTROL_H__
