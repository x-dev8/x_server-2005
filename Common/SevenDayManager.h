#ifndef _SEVENDAYMANAGER_
#define _SEVENDAYMANAGER_

#include "MeRTLibs.h"

class GamePlayer;
class SevenDayManager
{
public:
	enum TaskState
	{
		TS_UnStart,		//δ����
		TS_CanGain,		//�ɽ�ȡ
		TS_UnderWay,	//������
		TS_DoneUnGet,	//����ɣ���δ��ȡ����
		TS_DoneGet,		//�����
	};

	SevenDayManager();
	virtual ~SevenDayManager();

	void SetOwner( GamePlayer* pGamePlayer ) { pOwner = pGamePlayer;}

	bool IsInTask(int taskID); //�Ƿ����������

	bool IsCanGainTask(int index); //�ܷ��ȡ

	bool GainTask(int index); //��ȡ����

	short GetTaskState(int index);
	void SetTaskState(int index, short state); //��������״̬

	short GetTaskVar(int index);
	void SetTaskVar(int index, short var);

	bool GainReward(int index); //��ȡ����

	void TriggerSevenDaysVar(int index, int nvalue = 0);

	void TriggerFirstDayVar(int index);
	void TriggerSecondDayVar(int index, int questID);
	void TriggerThirdDayVar(int index, int nvar);
	void TriggerFourthDayVar(int index);
	void TriggerFifthDayVar(int index);
	void TriggerSixthDayVar(int index);
	void TriggerSeventhDayVar(int index);

	int GetDayTime( __time64_t startTime, __time64_t nowTime ); //��ȡ���˼���

private:
	GamePlayer* pOwner;
};

#endif //_SEVENDAYMANAGER_