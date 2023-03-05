/********************************************************************
    Filename:     AckEnterWorldPackage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __ACKENTERWORLD_PACKAGE_H__
#define __ACKENTERWORLD_PACKAGE_H__

#pragma once

#include "MessageDefine.h"

class CAckEnterWorldPackage
{
public:
    CAckEnterWorldPackage();
    virtual ~CAckEnterWorldPackage();

public:
    MsgAckEnterWorldPack* MakePackageMsg( MsgAckEnterWorld& msg     );
    MsgAckEnterWorld*     UnPackageMsg  ( MsgAckEnterWorldPack& msg );

protected:
    MsgAckEnterWorldPack m_pack;
    MsgAckEnterWorld     m_msg;
};

#endif //__ACKENTERWORLD_PACKAGE_H__
