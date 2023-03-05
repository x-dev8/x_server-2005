/********************************************************************
    Filename:     LoginStage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_LOGINSTAGE_H__
#define __GAMESERVER_LOGINSTAGE_H__

#pragma once

#include "StaticArray.h"
#include "WorkThread.h"
#include "MsgBase.h"

#define theLoginStage GetTheLoginStage()

// ��¼���� ��û�н��볡����ʱ��
// ����״̬ʱ���ɽ���ҽ�ɫ���� �磺�������ȴ�����
class LoginStage
{
public:
	LoginStage();
	~LoginStage();

    void UnInit();

	bool KickCharByAccount( unsigned int dwAccount );
    void Run    ();

    bool IsExist( GameObjectId stID );
	bool Enter  ( GameObjectId stID );
    
	int  EnterQueue      ( GameObjectId stID ); // �����Ŷ�
    int  LeaveQueue      ( GameObjectId stID ); // �뿪�Ŷ�
    int  GetLoginQueuePos( GameObjectId stID ); // �õ������е�λ��

	bool IsOpenQueue()  {return m_bOpenService;}
	void SetService(bool b) {m_bOpenService = b;}
protected:
    DWORD               m_dwLastProcessTime; // ��һ�δ����ʱ��
    DWORD               m_dwCostTime;        // run�ļ������ʱ��

    typedef std::list<GameObjectId>               CharacterIdContainer;
    typedef CharacterIdContainer::iterator		   ItrCharacterIdContainer;

    CharacterIdContainer _charIDs;			 // ��¼������������ϵ���

    CharacterIdContainer _charIDQueues;		 // �Ŷӵ���

	bool                 m_bOpenService;    //�����Ŷ�
};

LoginStage& GetTheLoginStage();

#endif // __GAMESERVER_LOGINSTAGE_H__
