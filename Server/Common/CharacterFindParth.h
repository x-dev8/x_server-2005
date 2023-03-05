#ifndef __CHARACTER_FIND_PARTH_H__
#define __CHARACTER_FIND_PARTH_H__

#include "GlobalDef.h"
#include "SwMap.h"
#include <deque>


class GameParthFinder;
class CharacterFindParth
{
public:
	//寻路状态
	enum FindParthState
	{
		FPS_None,		// 不在寻路
		FPS_Line,		// 直线寻路
		FPS_AStar,		// A*寻路
		FPS_Pos,		// 寻路到的位置不是目标位置,可能是因为目标位置不可达
	};

	// 动态阻挡状态
	enum DynamicBlockState
	{
		DBS_Close,		// 关闭动态阻挡
		DBS_Open,		// 开启动态阻挡
		DBS_TempClose,	// 暂时关闭动态阻挡
	};

	typedef std::deque< swVec2f >	FindParth;
	typedef FindParth::iterator		ItrFindParth;

	friend class GameParthFinder;

public:
	CharacterFindParth();

	// 初始化寻路信息
	void		InitFindParth( GameObjectId nCharID, bool blIsFindParth, bool blIsDynamicBlock );

	// 重新初始化
	void		ReInitFindParth( bool blIsFindParth, bool blIsDynamicBlock );

	// 是否开启寻路
	bool		IsFindParth() const	{ return _blIsFindParth; }

	// 动态阻挡是否关闭
	bool		IsDynamicBlockClosed()	{ return _nDynamicBlockState == DBS_Close; }

	// 寻找下一个目标位置,等待线程寻路时返回false,不支持跨地图寻路
	bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, const D3DXVECTOR3& vSelfPos, unsigned int nMapID );

	// 移动后
	void		AfterMoveToPos( const D3DXVECTOR3& posMoveTo, unsigned int nMapID );

	// 到达一个目标位置时检查是否寻路结束,还有后续路点则返回true
	bool		CheckReachPos();

	// 是否当前路点为路径中的最后一个路点
	bool		IsTheLastPointInParth()	{ return _findParth.size() == 1; }

private:
	// 是否开启动态阻挡
	bool		IsDynamicBlockOpen()	{ return DBS_Open == _nDynamicBlockState; }

	// 清空寻路相关
	void		ClearFindParth();

	// 设置是否开启寻路
	void		SetIsFindParth( bool blIsFindParth )	{ _blIsFindParth = blIsFindParth; }

	// 设置寻路状态
	void		SetFindParthState( unsigned char nFindParthState )	{ _nFinParthState = nFindParthState; }

	// 是否A*路径
	bool		IsAStarParth()	{ return FPS_AStar == _nFinParthState; }

	// 是否位置路径
	bool		IsPosParth()	{ return FPS_Pos == _nFinParthState; }

	// 得到对目标位置寻路路径上的当前目标路点,目标位置变化时会重新寻路,寻路失败则返回目标位置
	swVec2f		GetCurPointInParth( const swVec2f &targetPos, const swVec2f& selfPos, unsigned int nMapID );

	// 取下一路点,如果是最后一个路点则返回false
	bool		NextPointInParth();

	// 设置动态阻挡状态
	void		SetDynamicBlockState( unsigned char nState )	{ _nDynamicBlockState = nState; }

	// 是否暂时关闭动态阻挡
	bool		IsDynamicBlockTempClosed()	{ return DBS_TempClose == _nDynamicBlockState; }

	// 关闭动态阻挡
	void		CloseDynamicBlock( unsigned int nMapID, const swVec2f& point );

	// 暂时关闭动态阻挡
	void		TempCloseDynamicBlock( unsigned int nMapID, const swVec2f& point );

	// 将坐标设为阻挡点
	void		SetBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder );

	// 将坐标设为非阻挡点,需要对比原始阻挡图来保证不破坏阻挡信息
	void		ClearBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder );

	// 主线程中使用的寻路器,需要对比原始阻挡图来保证不破坏阻挡信息
	SwMap*		GetStageParthFinder( unsigned int nMapID );

	// 寻路器,寻路线程中使用
	SwMap*		GetStageThreadParthFinder( unsigned int nMapID );

	// 设置寻路线程的寻路结果
	void		SetFindParth( const std::vector< swVec2f >& parth, unsigned char nFindParthState, unsigned int nMapID, const D3DXVECTOR3& selfPos );

	// 清空路径
	void		ClearParth()	{ _findParth.clear(); }

private:
	GameObjectId	_nCharID;				// 角色ID
	unsigned int	_nCharMapID;			// 角色场景ID
	D3DXVECTOR3		_charPos;				// 角色坐标
	FindParth		_findParth;				// 路点列表
	bool			_blIsFindParth;			// 是否开启寻路
	unsigned char	_nFinParthState;		// 寻路状态,参见enum FindParthState
	unsigned char	_nDynamicBlockState;	// 动态阻挡状态
	bool			_blIsFindParthInThread;	// 是否在寻路器线程中寻路
};

#endif