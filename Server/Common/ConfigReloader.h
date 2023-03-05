#ifndef __CONFIG_RELOADER_H__
#define __CONFIG_RELOADER_H__

#include "Mutex.h"


class CItemDetailConfig;
class ICfgSingletionBase;
// 资源热加载器 备注:参与编译的配置文件不支持热加载
class ConfigReloader
{
public:
	//==================重载请求消息=================
	struct ReloadReqMsg
	{
		int nReloadType;	// 重载资源类型
	};
	typedef std::vector< ReloadReqMsg >		ReloadReqMsgQueue;
	typedef ReloadReqMsgQueue::iterator		ItrReloadReqMsgQueue;
	//==============================================

	//==================重载完成回复消息==============
	struct AckReloadMsg
	{
		int		nReloadType;		// 重载资源类型
	};
	typedef std::vector< AckReloadMsg >		AckReloadMsgQueue;
	typedef AckReloadMsgQueue::iterator		ItrAckReloadMsgQueue;
	//==============================================

	typedef std::map<int,ICfgSingletionBase*>	CfgSingletionsMap;
	typedef CfgSingletionsMap::iterator		    ItrCfgSingletionsMap;
public:
	// 重载线程函数
	static void ConfigReloaderThreadFunc( void* pVoid );

	// 主线程更新替代
	void Update();

	// 使用这个函数来添加重载请求消息
	void AddConfigReloadReqMsg( ReloadReqMsg& reqMsg );

	// 使用这个函数来添加重载完成回复消息
	void AddConfigReloadAckMsg( AckReloadMsg& ackMsg );

	// 注册 回调 主线程调用
	void OnReloadFinishedForRegister(int nType,ICfgSingletionBase* pCfgSingl);

private:
	// 暂时先放着 不管...
	//bool ReloadItemDetail( CItemDetailConfig* pConfigInst );

private:
	ReloadReqMsgQueue	_reqQueue;		// 重载请求消息队列
	CSemiAutoIntLock	_lockReqQueue;	// 消息队列锁

	AckReloadMsgQueue	_ackQueue;		// 重载完成回复消息队列
	CSemiAutoIntLock	_lockAckQueue;	// 消息队列锁

	CfgSingletionsMap   m_mapCfgSingletions;
};
ConfigReloader& GetConfigReloader();

#define theConfigReloader GetConfigReloader()

#endif