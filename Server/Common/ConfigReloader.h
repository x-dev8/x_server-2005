#ifndef __CONFIG_RELOADER_H__
#define __CONFIG_RELOADER_H__

#include "Mutex.h"


class CItemDetailConfig;
class ICfgSingletionBase;
// ��Դ�ȼ����� ��ע:�������������ļ���֧���ȼ���
class ConfigReloader
{
public:
	//==================����������Ϣ=================
	struct ReloadReqMsg
	{
		int nReloadType;	// ������Դ����
	};
	typedef std::vector< ReloadReqMsg >		ReloadReqMsgQueue;
	typedef ReloadReqMsgQueue::iterator		ItrReloadReqMsgQueue;
	//==============================================

	//==================������ɻظ���Ϣ==============
	struct AckReloadMsg
	{
		int		nReloadType;		// ������Դ����
	};
	typedef std::vector< AckReloadMsg >		AckReloadMsgQueue;
	typedef AckReloadMsgQueue::iterator		ItrAckReloadMsgQueue;
	//==============================================

	typedef std::map<int,ICfgSingletionBase*>	CfgSingletionsMap;
	typedef CfgSingletionsMap::iterator		    ItrCfgSingletionsMap;
public:
	// �����̺߳���
	static void ConfigReloaderThreadFunc( void* pVoid );

	// ���̸߳������
	void Update();

	// ʹ������������������������Ϣ
	void AddConfigReloadReqMsg( ReloadReqMsg& reqMsg );

	// ʹ��������������������ɻظ���Ϣ
	void AddConfigReloadAckMsg( AckReloadMsg& ackMsg );

	// ע�� �ص� ���̵߳���
	void OnReloadFinishedForRegister(int nType,ICfgSingletionBase* pCfgSingl);

private:
	// ��ʱ�ȷ��� ����...
	//bool ReloadItemDetail( CItemDetailConfig* pConfigInst );

private:
	ReloadReqMsgQueue	_reqQueue;		// ����������Ϣ����
	CSemiAutoIntLock	_lockReqQueue;	// ��Ϣ������

	AckReloadMsgQueue	_ackQueue;		// ������ɻظ���Ϣ����
	CSemiAutoIntLock	_lockAckQueue;	// ��Ϣ������

	CfgSingletionsMap   m_mapCfgSingletions;
};
ConfigReloader& GetConfigReloader();

#define theConfigReloader GetConfigReloader()

#endif