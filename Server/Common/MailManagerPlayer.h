/********************************************************************
    Filename:    MailManagerPlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MAILMANAGERPLAYER_H__
#define __COMMON_MAILMANAGERPLAYER_H__

#include "GlobalDef.h"
#include "MailServer.h"
#include "MessageDefine.h"
#include "CenterGameMessage.h"

#pragma once

class GamePlayer;
class MailPlayerManager
{
	enum
	{
		enumSendTextMail_NeedMoney	= 49,		//发送文本钱
		enumSendOtherMail_NeedMoney = 500,		//发送其他邮件需要钱
	};
public:
    MailPlayerManager();
    ~MailPlayerManager(){}

    void   SetOwner( GamePlayer* pGamePlayer ) { pOwner = pGamePlayer;}	  // 设置主人
    
    void   BeginSendMail( MsgSendMailReq* pMessage );                     // 开始一个发信请求
    void   SendValidMailToCS();                                           // 发有效信件数据给CS
    void   SendInValidMailToClient( CS2GSQueryMailCanSendAck* pMessage ); // 发送失败信件的原因给Client
    void   EndSendValidMail();                                            // 结束一个发信请求

protected:
    GamePlayer* pOwner;

private:
    bool           _bHaveMailProcess; // 是否已经有一个邮件在受理中
    MsgSendMailReq _cacheMail;        // 缓存的消息
};

#endif // __COMMON_MAILMANAGERPLAYER_H__
