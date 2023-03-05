#pragma once
#include <windows.h>
#include <deque>
#include "Dxsdk/D3DX9Math.h"


class CPlayer;
// class CWalkPath;
class CPlayerAnim;

class CMoveQueue
{
public:
	enum enumMove
	{
		//M_CONTINUEMOVING				// 持续移动
		M_KEEPMOVINGTOPOS				// 保持移动状态移动到目标点
		,M_MOVINGTOPOS					// 移动到目标点停下来
		,M_MOVINGTOLOCKTARGET			// 移动到锁定目标

		//,M_PLAYERMOVINGTOPOS			// 玩家移动到某点
		,M_PLAYERMOVINGTYPE				// 玩家移动方式的变化
		,M_PLAYERMOVINGDIRANDTYPE		// 玩家方向和移动方式的变化

		,M_PLAYERKEEPMOVINGPOS			// 玩家持续移动通过某点
		,M_PLAYERKEEPMOVINGPOSANDDIR	// 玩家以某朝向持续移动通过某点
		,M_PLAYERPOS					// 玩家原地不动的所在点
		,M_PLAYERDIR					// 玩家原地不动的面朝方向
		,M_PLAYERPOSANDDIR				// 玩家原地不动的所在点和面朝方向
        ,M_PLAYERKEEPMOVINGPOSANDDIR_FINDPATH // 玩家以某朝向持续移动通过某点，需要自动寻路
	};

	struct SMove
	{
		// 类型
		short stType;

		// 是否已经失效,,当bSkip = TRUE表示该行为无效，或该行为为空的
		bool bSkip;

		// 0时间执行，即立即执行，
		bool bZeroTimeExec;

		// 指令序列编号，现在简单的用时间来标示
		// 后来的指令一定在数值上大于先前的指令
		DWORD dwSerialNo;

		//动作入列时间
		DWORD dwPushTime;

		int nTargetID; // 目标的ID
		float fKeepDistance; // 和目标保持的距离

		short shX;// 目标点X
		short shY;// 目标点Y

		D3DXVECTOR3 vTargetPos; // 目标点
		D3DXVECTOR3 vDir; // 当前的朝向

		short shMovingType;// 移动类型

		SMove():bSkip(false),
			bZeroTimeExec(false){}
	};

private:
	std::deque<SMove> m_veMove;
	BOOL Push_Move( SMove &move );

public:
	CMoveQueue(void);
	~CMoveQueue(void);

	int Size();
	void Clear();

	BOOL PopNextMove( SMove &move );
	BOOL Push_KeepMovingToPos( float x, float y, float dx, float dy );

	BOOL Push_MovingToPos( float x, float y, float dx, float dy );
	BOOL Push_MovingToTarget( int nTargetID, float fKeepDistance );

	BOOL Push_PlayerMovingType( short shMovingType);
	BOOL Push_PlayerMovingDirAndType( D3DXVECTOR3 vDir, short shMovingType );

	// 玩家保持移动状态通过某点
	BOOL PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos );
	// 玩家以某朝向保持移动状态通过某点
	// WOW只所以掉线了会看见别的玩家在原地打转，并不是因为它在移动中互发了什么:正在朝什么方向转的消息。
	// 而是因为它移动通过了一个点，而通过这个点的路径是用插值算出来的一条弧线，当它收不到下个要通过的点后，
	// 仍然以这个路径线移动，就出现了原地打转的情况
	BOOL PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );
	// 玩家以某朝向保持移动状态通过某点，自动寻路
    BOOL PushPlayerKeepMovingPassPos_TargetDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );

	// 玩家原地不动的所在点
	BOOL PushPlayerPos( D3DXVECTOR3 vPos );
	// 玩家原地不动的面朝方向
	BOOL PushPlayerDir( D3DXVECTOR3 vDir );
	// 玩家原地不动的所在点和面朝方向
	BOOL PushPlayerPosAndDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );
};