#pragma once

#include "DBMessageDefine.h"

//�����ɫ��Ϣ�ı����ļ�
//�������ͬ�汾�Ľ�ɫ��Ϣ
class CSaveCharBackFile
{
public:
	CSaveCharBackFile(void);
	~CSaveCharBackFile(void);

	//��Backup�����е���Ϣ����
	//�����Ͷ����е���Ϣ����
	void	SaveMsgToFile( DBMsgSaveCharacter *pSave );
	//���ļ����룬ֱ�����뵽DBCon::SendMsg
	void	LoadMsgFromFile( void );
};
