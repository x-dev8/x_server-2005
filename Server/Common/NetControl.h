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
    virtual Msg* GetMsg();               // �������Ϣ�ϰ� ���� MSGMAXSIZE
    virtual void Push2In  ( Msg* pMsg ); // �������Ϣ�и� ���� MSGMAXSIZE

    virtual Msg* GetMsgEx();             // ���������Ϣ�ϰ� ���� MSGMAXSIZE
    virtual void Push2InEx( Msg* pMsg ); // ���������Ϣ�и� ���� MSGMAXSIZE

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
// ���Խӹܿ�����
class CAICharacterControl : public NetControl
{
public:
    static CAICharacterControl* CreateInstance() { return CNewWithDebug<CAICharacterControl>::Alloc(1, "CAICharacterControl::CreateInstance�д���CAICharacterControlʵ��");}
    virtual void Release()                       { CNewWithDebug<CAICharacterControl>::Free(this);}
    virtual void OnCriticalError()               { }
};

//////////////////////////////////////////////////////////////////////////
class CEffectControl : public NetControl
{
public:
    static CEffectControl* CreateInstance() { return CNewWithDebug<CEffectControl>::Alloc(1, "CEffectControl::CreateInstance�д���CEffectControlʵ��");}
    virtual void Release()                  { CNewWithDebug<CEffectControl>::Free(this);}

	virtual bool Process() { return true; }
	virtual void Run(DWORD dwCostTime){}

	CEffectControl(){}
	virtual ~CEffectControl()
	{}
};

//////////////////////////////////////////////////////////////////////////
class CNpcCtrl : public IBaseControl
{ // NPCû����Ϣ����
public:
    static CNpcCtrl* CreateInstance() { return CNewWithDebug<CNpcCtrl>::Alloc(1, "CNpcCtrl::CreateInstance�д���CNpcCtrlʵ��"); }
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
    //static NetControlEx* CreateInstance() {return CNewWithDebug<NetControlEx>::Alloc(1, "NetControlEx::CreateInstance�д���NetControlExʵ��");}
    //virtual void Release() {CNewWithDebug<NetControlEx>::Free(this);}

    NetControlEx();
    virtual ~NetControlEx();
    
    /*IMeSocket*/Socketer* GetSock(){ return m_sock; }
    
    void RecvMsg();       // ���գ����ⲿ���ã������ж�selectͨ��
    void TrySendAllMsg(); // ����Ϣ�����е���Ϣ���ͳ�ȥ�����ⲿ���ã�selectͨ��
    
    void AddErrorTimeout( int iData = 1 ); //����ʱ
    void GetPeerName( char *szName,int iLen );
    
    virtual bool Process(){ return true; }
    virtual bool IsNetworkCtrl(){return true;}
    virtual void OnCriticalError(void){ OnConnectError();}

    //unsigned short GetLifeCode(){ return m_ustLifeCode; }
private:
    //��ʹ��GettheServer().SendMsg
    //����pChar->GetControl()->SendMsg
    //��ΪGettheServer().SendMsg( pChar,pMsg,sendrange_single );
    virtual void SendMsg( Msg *pMsg );  //����

    //���յ���������ɰ�
    void PushBuf2Msg( char*sBuf,int iSize );
    bool SendRest();

    void OnConnectError();    
private:
    /*IMeSocket*/Socketer* m_sock;    
    MsgQueue   m_out; //�������
    
    int  m_iSendRestSize;  //���ͣ������ϴη��͵���δ�����������    
    int  m_iSendRestStart; //ʣ�����ݵ���ʼλ��
    char m_sSendRest[ MSGMAXSIZE ];

    int  m_iRecvRestSize;//���յ������ݣ�û����ɰ�
    char m_sRecvRest[ MSGMAXSIZE ];

    int  m_iErrTimeout;
};

#endif // __GAMESERVER_NETCONTROL_H__
