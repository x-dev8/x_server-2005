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
		enumSendTextMail_NeedMoney	= 49,		//�����ı�Ǯ
		enumSendOtherMail_NeedMoney = 500,		//���������ʼ���ҪǮ
	};
public:
    MailPlayerManager();
    ~MailPlayerManager(){}

    void   SetOwner( GamePlayer* pGamePlayer ) { pOwner = pGamePlayer;}	  // ��������
    
    void   BeginSendMail( MsgSendMailReq* pMessage );                     // ��ʼһ����������
    void   SendValidMailToCS();                                           // ����Ч�ż����ݸ�CS
    void   SendInValidMailToClient( CS2GSQueryMailCanSendAck* pMessage ); // ����ʧ���ż���ԭ���Client
    void   EndSendValidMail();                                            // ����һ����������

protected:
    GamePlayer* pOwner;

private:
    bool           _bHaveMailProcess; // �Ƿ��Ѿ���һ���ʼ���������
    MsgSendMailReq _cacheMail;        // �������Ϣ
};

#endif // __COMMON_MAILMANAGERPLAYER_H__
