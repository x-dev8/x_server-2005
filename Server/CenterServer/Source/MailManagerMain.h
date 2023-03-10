/********************************************************************
    Filename:    MailManagerMain.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_MAILMANAGERMAIN_H__
#define __COMMON_MAILMANAGERMAIN_H__

#pragma once

#include "GlobalDef.h"
#include "MailServer.h"
#include "CenterGameMessage.h"

// 管理直接操作数据库
class MailSystemManager
{
public:
    enum EConstDefine
    {
        ECD_CreateIDMaxCount = 3,
    };

public:
    static MailSystemManager& Instance();
    MailSystemManager();
    ~MailSystemManager();

    // 请求|回复邮件列表
    void OnGS2CSMailListReq( GS2CSMailListReq* pMessage, uint32 serverId );
    void OnCS2GSMailListAck( CS2GSMailListAck* pMessage );
	// 请求|回复能否发送某个邮件
    void OnGS2CSQueryMailCanSendReq( GS2CSQueryMailCanSendReq* pMessage, uint32 serverId );
    void OnCS2GSQueryMailCanSendAck( CS2GSQueryMailCanSendAck* pMessage );
	// 请求|回复发送某个邮件
    void OnGS2CSSendMailReq( GS2CSSendMailReq* pMessage, uint32 serverId );
    void OnCS2GSSendMailAck( CS2GSSendMailAck* pMessage );
	// 请求|回复对某个邮件的操作
    void OnGS2CSOpMailReq( GS2CSOpMailReq* pMessage, uint32 serverId );
    void OnCS2GSOpMailAck( CS2GSOpMailAck* pMessage );
};

#define theMailSystemManager MailSystemManager::Instance()

#endif // __COMMON_MAILMANAGERMAIN_H__