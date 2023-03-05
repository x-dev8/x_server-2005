#ifndef __GAME_PARTH_FINDER_H__
#define __GAME_PARTH_FINDER_H__

#include "GlobalDef.h"
#include "SwMap.h"
#include "Mutex.h"


// 管理寻路所用地图信息模板
class ParthFinderTemplates
{
public:
	~ParthFinderTemplates();

	long	InitParthFinder( uint32 nMapID, const std::string& strFileName );
	SwMap*	GetParthFinder( uint32 nMapID );

private:
	typedef std::map< uint32 , SwMap* >		ParthFinderContainer;
	typedef ParthFinderContainer::iterator	ItrParthFinderContainer;

	ParthFinderContainer	_parthFinders;	// 寻路所用地图信息模板的容器,保存了寻路器构造所需的中间数据
	CSemiAutoIntLock		_lock;
};
ParthFinderTemplates& GetParthFinderTemplates();


class MonsterBaseEx;
// 寻路线程管理
class GameParthFinder
{
public:
	// 主线程发给寻路线程的请求消息
	struct FindParthReq 
	{
		GameObjectId	nChaID;		// 请求角色ID
		uint32			nStageID;	// 场景ID
		swVec2f			startPos;	// 寻路起始点
		swVec2f			targetPos;	// 寻路目标位置
	};
	typedef std::vector< FindParthReq >		FindParthReqQueue;
	typedef FindParthReqQueue::iterator		ItrFindParthReqQueue;

	// 寻路线程发给主线程的结果
	struct AckFindParth 
	{
		GameObjectId	nChaID;						// 请求角色ID
		swVec2f			targetPos;					// 目标位置
		std::vector< swVec2f >	findParth;			// 寻路结果
		uint8			nFinParthState;				// 寻路状态,参见enum FindParthState
	};
	typedef std::vector< AckFindParth >		AckFindParthQueue;
	typedef AckFindParthQueue::iterator		ItrAckFindParthQueue;

	// 寻路线程
	static void ParthFinderThreadFunc( void* pVoid );

	// 主线程更新
	void	Update();

	// 添加消息
	void	AddFindParthReq( FindParthReq& req );
	void	AddAckFindParth( AckFindParth& ack );

private:
	// 请求消息队列
	FindParthReqQueue	_reqQueue;
	CSemiAutoIntLock	_lockReqQueue;

	// 结果消息队列
	AckFindParthQueue	_ackQueue;
	CSemiAutoIntLock	_lockAckQueue;
};
GameParthFinder& GetGameParthFinder();

#endif