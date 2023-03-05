/********************************************************************
    Filename:     IBaseControl.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_IBASECONTROL_H__
#define __COMMON_IBASECONTROL_H__

#pragma once

#include "MsgBase.h"
#include "GameDataType.h"

class IBaseControl
{ 
public:
    virtual ~IBaseControl(){};
    virtual bool Process()      { return false;  }
    virtual bool IsNetworkCtrl(){ return false;  }
    GameObjectId   GetID()     { return m_stID; }
    void    SetID( GameObjectId stID ) { m_stID = stID; }

    virtual Msg* GetMsg()  { return 0; }     // 会进行消息合包 大于 MSGMAXSIZE
    virtual Msg* GetMsgEx(){ return 0; }     // 不会进行消息合包 大于 MSGMAXSIZE
    virtual void Release() = 0;
    virtual void Push2In  ( Msg* pMsg ) = 0; // 会进行消息切割 大于 MSGMAXSIZE
    virtual void Push2InEx( Msg* pMsg ) = 0; // 不会进行消息切割 大于 MSGMAXSIZE

private:
    GameObjectId m_stID;  //Warning0
    virtual void SendMsg( Msg *pMsg ){}; 
};

#endif // __CONTROL_INTERFACE_H__
