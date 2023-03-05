#ifndef __CHARACTER_FIND_PARTH_H__
#define __CHARACTER_FIND_PARTH_H__

#include "GlobalDef.h"
#include "SwMap.h"
#include <deque>


class GameParthFinder;
class CharacterFindParth
{
public:
	//Ѱ·״̬
	enum FindParthState
	{
		FPS_None,		// ����Ѱ·
		FPS_Line,		// ֱ��Ѱ·
		FPS_AStar,		// A*Ѱ·
		FPS_Pos,		// Ѱ·����λ�ò���Ŀ��λ��,��������ΪĿ��λ�ò��ɴ�
	};

	// ��̬�赲״̬
	enum DynamicBlockState
	{
		DBS_Close,		// �رն�̬�赲
		DBS_Open,		// ������̬�赲
		DBS_TempClose,	// ��ʱ�رն�̬�赲
	};

	typedef std::deque< swVec2f >	FindParth;
	typedef FindParth::iterator		ItrFindParth;

	friend class GameParthFinder;

public:
	CharacterFindParth();

	// ��ʼ��Ѱ·��Ϣ
	void		InitFindParth( GameObjectId nCharID, bool blIsFindParth, bool blIsDynamicBlock );

	// ���³�ʼ��
	void		ReInitFindParth( bool blIsFindParth, bool blIsDynamicBlock );

	// �Ƿ���Ѱ·
	bool		IsFindParth() const	{ return _blIsFindParth; }

	// ��̬�赲�Ƿ�ر�
	bool		IsDynamicBlockClosed()	{ return _nDynamicBlockState == DBS_Close; }

	// Ѱ����һ��Ŀ��λ��,�ȴ��߳�Ѱ·ʱ����false,��֧�ֿ��ͼѰ·
	bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, const D3DXVECTOR3& vSelfPos, unsigned int nMapID );

	// �ƶ���
	void		AfterMoveToPos( const D3DXVECTOR3& posMoveTo, unsigned int nMapID );

	// ����һ��Ŀ��λ��ʱ����Ƿ�Ѱ·����,���к���·���򷵻�true
	bool		CheckReachPos();

	// �Ƿ�ǰ·��Ϊ·���е����һ��·��
	bool		IsTheLastPointInParth()	{ return _findParth.size() == 1; }

private:
	// �Ƿ�����̬�赲
	bool		IsDynamicBlockOpen()	{ return DBS_Open == _nDynamicBlockState; }

	// ���Ѱ·���
	void		ClearFindParth();

	// �����Ƿ���Ѱ·
	void		SetIsFindParth( bool blIsFindParth )	{ _blIsFindParth = blIsFindParth; }

	// ����Ѱ·״̬
	void		SetFindParthState( unsigned char nFindParthState )	{ _nFinParthState = nFindParthState; }

	// �Ƿ�A*·��
	bool		IsAStarParth()	{ return FPS_AStar == _nFinParthState; }

	// �Ƿ�λ��·��
	bool		IsPosParth()	{ return FPS_Pos == _nFinParthState; }

	// �õ���Ŀ��λ��Ѱ··���ϵĵ�ǰĿ��·��,Ŀ��λ�ñ仯ʱ������Ѱ·,Ѱ·ʧ���򷵻�Ŀ��λ��
	swVec2f		GetCurPointInParth( const swVec2f &targetPos, const swVec2f& selfPos, unsigned int nMapID );

	// ȡ��һ·��,��������һ��·���򷵻�false
	bool		NextPointInParth();

	// ���ö�̬�赲״̬
	void		SetDynamicBlockState( unsigned char nState )	{ _nDynamicBlockState = nState; }

	// �Ƿ���ʱ�رն�̬�赲
	bool		IsDynamicBlockTempClosed()	{ return DBS_TempClose == _nDynamicBlockState; }

	// �رն�̬�赲
	void		CloseDynamicBlock( unsigned int nMapID, const swVec2f& point );

	// ��ʱ�رն�̬�赲
	void		TempCloseDynamicBlock( unsigned int nMapID, const swVec2f& point );

	// ��������Ϊ�赲��
	void		SetBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder );

	// ��������Ϊ���赲��,��Ҫ�Ա�ԭʼ�赲ͼ����֤���ƻ��赲��Ϣ
	void		ClearBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder );

	// ���߳���ʹ�õ�Ѱ·��,��Ҫ�Ա�ԭʼ�赲ͼ����֤���ƻ��赲��Ϣ
	SwMap*		GetStageParthFinder( unsigned int nMapID );

	// Ѱ·��,Ѱ·�߳���ʹ��
	SwMap*		GetStageThreadParthFinder( unsigned int nMapID );

	// ����Ѱ·�̵߳�Ѱ·���
	void		SetFindParth( const std::vector< swVec2f >& parth, unsigned char nFindParthState, unsigned int nMapID, const D3DXVECTOR3& selfPos );

	// ���·��
	void		ClearParth()	{ _findParth.clear(); }

private:
	GameObjectId	_nCharID;				// ��ɫID
	unsigned int	_nCharMapID;			// ��ɫ����ID
	D3DXVECTOR3		_charPos;				// ��ɫ����
	FindParth		_findParth;				// ·���б�
	bool			_blIsFindParth;			// �Ƿ���Ѱ·
	unsigned char	_nFinParthState;		// Ѱ·״̬,�μ�enum FindParthState
	unsigned char	_nDynamicBlockState;	// ��̬�赲״̬
	bool			_blIsFindParthInThread;	// �Ƿ���Ѱ·���߳���Ѱ·
};

#endif