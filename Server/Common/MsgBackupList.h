#pragma once

#include "MeRTLibsServer.h"

struct DBMsg;
//������Ϣ
//�����ɫ��Ϣ ����ȷ�ϱ����ݿ⴦��
//�����ݿ⴦����ǰ��������
class CMsgBackupList
{
	//��Ϣ

	std::list<DBMsg*>	m_listMsg;
public:
	CMsgBackupList(void);
	~CMsgBackupList(void);

	//������Ϣ
	bool BackupMsg( DBMsg * pDBMsg );
	//ȥ�����ݵ���Ϣ
	bool RemoveMsg( DWORD dwMsgType,int iWho,unsigned short ustLifeCode );

	//ȡ��Ϣ
	//szBuf�Ĵ�СӦ����MSGCANCUTMAXSIZE
	bool PopMsg( char *szBuf );
	int	 GetSize( void ){ return (int)m_listMsg.size(); }
};
