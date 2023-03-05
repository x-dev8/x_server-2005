#ifndef __GAME_BLOCK_MAP_H__
#define __GAME_BLOCK_MAP_H__

/************************************************************************/
/* ������ʹ�õ��赲ͼ,�������ƽ�ɫ�Ļ����                            */
/************************************************************************/

#include <map>
#include "Dxsdk\d3dx9math.h"
#include "Mutex.h"
#include "SwMap.h"

// �赲ͼ������ģ��
class BlockMapManager
{
public:
	typedef unsigned short	MapID;
	typedef std::map< MapID , SwMap* >		BlockMapContainer;
	typedef BlockMapContainer::iterator		ItrBlockMapContainer;

public:
	~BlockMapManager();

	// ��ʼ��һ���赲ͼ
	long InitBlockMap( unsigned short nMapID, const std::string& strFileName );

	// �������Ŀɴ���
	bool IsPointReachable( unsigned short nMapID, float fX, float fY );

	// ����Ƿ���Դ�һ��ֱ���ƶ�����һ��
	bool CanMoveByLine( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd );

	// �ж��Ƿ����ֱ�߿�����
	bool IsLineCanMove( unsigned short nMapID, float fXStart, float fYStart, float fXEnd, float fYEnd );

private:
	BlockMapContainer	_blockMapContainer;
};
BlockMapManager& GetBlockMapManager();


// ����ƶ��Ϸ��Է���
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
	// �����߳�
	static void PlayerMoveAnalysisThreadFunc( void* pVoid );

	// ��ӷ���������Ϣ
	void AddReqAnalysisMsg( ReqAnalysisMsg& req );

private:
	void AnalysisMove( D3DXVECTOR3 &vOldPos, D3DXVECTOR3 &vNewPos );

private:
	ReqMsgQueue			_reqMsgQueue;
	CSemiAutoIntLock	_lockReqQueue;
};
PlayerMoveAnalysis& GetPlayerMoveAnalysis();

#endif