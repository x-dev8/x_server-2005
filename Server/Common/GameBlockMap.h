#ifndef __GAME_BLOCK_MAP_H__
#define __GAME_BLOCK_MAP_H__

/************************************************************************/
/* 服务器使用的阻挡图,用于限制角色的活动区域                            */
/************************************************************************/

#include <map>
#include "Dxsdk\d3dx9math.h"
#include "Mutex.h"
#include "SwMap.h"

// 阻挡图的配置模板
class BlockMapManager
{
public:
	typedef unsigned short	MapID;
	typedef std::map< MapID , SwMap* >		BlockMapContainer;
	typedef BlockMapContainer::iterator		ItrBlockMapContainer;

public:
	~BlockMapManager();

	// 初始化一张阻挡图
	long InitBlockMap( unsigned short nMapID, const std::string& strFileName );

	// 检测坐标的可达性
	bool IsPointReachable( unsigned short nMapID, float fX, float fY );

	// 检测是否可以从一点直线移动至另一点
	bool CanMoveByLine( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd );

	// 判断是否可以直线可以走
	bool IsLineCanMove( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd );

private:
	BlockMapContainer	_blockMapContainer;
};
BlockMapManager& GetBlockMapManager();


// 玩家移动合法性分析
class PlayerMoveAnalysis
{
public:
	struct ReqAnalysisMsg
	{
		unsigned int	nAccountID;
		char            szLoginName[32];
		char			szCharName[33];
		unsigned int	nChaDBID;
		//char            szSessionKey[32+1];
		__int64         SessionKey;
		unsigned short	nMapID;
		GameObjectId	nID;
		D3DXVECTOR3		vOldPos;
		D3DXVECTOR3		vNewPos;
	};
	typedef std::vector< ReqAnalysisMsg >		ReqMsgQueue;
	typedef ReqMsgQueue::iterator				ItrReqMsgQueue;

public:
	// 分析线程
	static void PlayerMoveAnalysisThreadFunc( void* pVoid );

	// 添加分析请求消息
	void AddReqAnalysisMsg( ReqAnalysisMsg& req );

private:
	void AnalysisMove( D3DXVECTOR3 &vOldPos, D3DXVECTOR3 &vNewPos );

private:
	ReqMsgQueue			_reqMsgQueue;
	CSemiAutoIntLock	_lockReqQueue;
};
PlayerMoveAnalysis& GetPlayerMoveAnalysis();

#endif