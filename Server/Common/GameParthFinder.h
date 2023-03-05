#ifndef __GAME_PARTH_FINDER_H__
#define __GAME_PARTH_FINDER_H__

#include "GlobalDef.h"
#include "SwMap.h"
#include "Mutex.h"


// ����Ѱ·���õ�ͼ��Ϣģ��
class ParthFinderTemplates
{
public:
	~ParthFinderTemplates();

	long	InitParthFinder( uint32 nMapID, const std::string& strFileName );
	SwMap*	GetParthFinder( uint32 nMapID );

private:
	typedef std::map< uint32 , SwMap* >		ParthFinderContainer;
	typedef ParthFinderContainer::iterator	ItrParthFinderContainer;

	ParthFinderContainer	_parthFinders;	// Ѱ·���õ�ͼ��Ϣģ�������,������Ѱ·������������м�����
	CSemiAutoIntLock		_lock;
};
ParthFinderTemplates& GetParthFinderTemplates();


class MonsterBaseEx;
// Ѱ·�̹߳���
class GameParthFinder
{
public:
	// ���̷߳���Ѱ·�̵߳�������Ϣ
	struct FindParthReq 
	{
		GameObjectId	nChaID;		// �����ɫID
		uint32			nStageID;	// ����ID
		swVec2f			startPos;	// Ѱ·��ʼ��
		swVec2f			targetPos;	// Ѱ·Ŀ��λ��
	};
	typedef std::vector< FindParthReq >		FindParthReqQueue;
	typedef FindParthReqQueue::iterator		ItrFindParthReqQueue;

	// Ѱ·�̷߳������̵߳Ľ��
	struct AckFindParth 
	{
		GameObjectId	nChaID;						// �����ɫID
		swVec2f			targetPos;					// Ŀ��λ��
		std::vector< swVec2f >	findParth;			// Ѱ·���
		uint8			nFinParthState;				// Ѱ·״̬,�μ�enum FindParthState
	};
	typedef std::vector< AckFindParth >		AckFindParthQueue;
	typedef AckFindParthQueue::iterator		ItrAckFindParthQueue;

	// Ѱ·�߳�
	static void ParthFinderThreadFunc( void* pVoid );

	// ���̸߳���
	void	Update();

	// �����Ϣ
	void	AddFindParthReq( FindParthReq& req );
	void	AddAckFindParth( AckFindParth& ack );

private:
	// ������Ϣ����
	FindParthReqQueue	_reqQueue;
	CSemiAutoIntLock	_lockReqQueue;

	// �����Ϣ����
	AckFindParthQueue	_ackQueue;
	CSemiAutoIntLock	_lockAckQueue;
};
GameParthFinder& GetGameParthFinder();

#endif