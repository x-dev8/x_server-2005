#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
#include "MsgBase.h"
#include "ItemDetail.h"

class CPlayer;
// class CWalkPath;
class CPlayerAnim;
// �������У� �����Ļ�ԭ����ʽ,
// ���ж���[�ƶ�������]
//   added 2003.10.25
#define MAX_ATTACKINFO_RECORD dr_MaxAttackTarget

struct SAttackInfoRecord
{
	DWORD dwState;		//���ܸ��ӵ�״̬
	int	iBalanceType;	//�������
	int iTagNum;     	//����������ʾ������
	int	iTagHp;			//�������ߵ�HP
    int iSrcHpNum;      //������Ѫ���仯������
	int	iTagMp;			//�������ߵ�MP
	int iSrcMpNum;      //������MP�仯������
	int iTagMpNum;      //��������MP�仯������
	int nTargetID;		//Ŀ���ID
    short stTagBackAttackNum; // Ŀ���ܱ�����������ֵ
    int   nShieldHp;          // ħ��������HP
};

struct SAttackInfo : public MeCommonAllocObj<SAttackInfo>
{
	short stSrcX, stSrcY;//�����ߵ�λ��
	int iSkill;			// ���ܱ��
	int	iSkillLevel;	//ʹ�õļ��ܵĵȼ�
	DWORD dwHoldTime;
	DWORD dwActionTime;

	int	iSrcHp;			//�����ߵ�HP
	int	iSrcMp;			//�����ߵ�MP
	int	iSrcNum;		//��������ʾ��HP����
	int	iSrcMpNum;		//��������ʾ��MP����
	int	nSrcId;
	DWORD dwSerialNo;

	bool bIsCharTarget;			//�Ƿ��ɫĿ��

	FPos3 pos;			// Ŀ���( point aoe�� )

	int nTargetId;					//Ŀ������

	short stTargetX,stTargetY;

	bool bNew;
	int nRecordCount;
	SAttackInfoRecord records[MAX_ATTACKINFO_RECORD];
    bool bPlayHurtAnim;

	enum eAtkHand
	{
		e_rhand = 0,
		e_lhand,
		e_max
	};
	
	SAttackInfo(){ Clear(); }
	~SAttackInfo(){  }

	BOOL AddRecord( SAttackInfoRecord* pRecord )
	{
		if( nRecordCount >= MAX_ATTACKINFO_RECORD )
		{
			//assert( false && "attack info add record failed, buffer is full" );
			return FALSE;
		}
		records[nRecordCount++] = *pRecord;
		return TRUE;
	}
	void Clear()
	{
		stSrcX = 0;
		stSrcY = 0;

		iSkill = -1;
		iSkillLevel = 0;

		dwHoldTime = 0;
		dwActionTime = 0;

		iSrcHp = 0;
		iSrcNum = 0;

		nSrcId = -1;
		dwSerialNo = 0;

		bIsCharTarget = true;
		nTargetId = -1;
		stTargetX = -1;
		stTargetY = -1;

		nRecordCount = 0;
        bPlayHurtAnim = true;
		memset( records, 0x00, sizeof( records ) );
	}
};

//�����������ʩչ������
struct IntonateEndInfo
{
	unsigned short ustSkillId;
	unsigned short ustSkillLevel;
	struct EmissionTarget
	{
		DWORD dwEmissionFlyTime;
		union unionTarget
		{
			GameObjectId ustTargetID;
			struct SPos
			{
				short x,y;
			}pos;
		}target;
	};

	EmissionTarget targetList[MAXEMISSIONNUM];

	IntonateEndInfo()
	{
		ustSkillId = -1;
		ustSkillLevel = -1;
		memset(targetList,0,sizeof(targetList));
	}
};

//�������鶯��
struct ExpressionInfo
{
	DWORD dwSerialNo;
	//
	int iActionID;    //��Ϊ������ʱ��
};
//�ʳ���Ҫ������
struct IntonateInfo
{
	int	iSkillNo;
	int iSkillLevel;
	//
	DWORD	dwDelayTime; //������ʱ��
	//
	CPlayer* pSrc;		//������
	CPlayer* pDst;		//����Ŀ��
	//
	DWORD dwSerialNo;
	//��ǰ��������
	int iPercent;
};

struct SSeeHoldSkill
{
	CPlayer* pSrc;

	int iSkillID;
	int iSkillLevel;

	int iPercent;
};

class CActionQueue
{
public:
	enum enumConst
	{
		const_iMaxActionSize = 1024
	};
public:
	enum enumAction
	{
		A_EXPRESSION,
		A_INTONATE,
		A_ATTACKEX,
		A_WALK,
		A_FLASHMOVE,
		A_TALKTONPC,
		//   added 2004.08.09
		A_DEATH,
		//   added 2004.08.26
		
		A_STARTHOLDSKILL,		// ��ʼ��������				A_INTINATE_END
		//A_HOLDSKILLONEHIT,		// �������ܵ�һ������
		A_ENDHOLDSKILL,			// ������������
		A_CANCELSKILL,

		A_SEEHOLDSKILL			//������������

		,A_BEATTACKED			//��������
	};	

	struct SAction
	{	
        // ����
		short stType;

		// �Ƿ��Ѿ�ʧЧ,,��bSkip = TRUE��ʾ����Ϊ��Ч�������ΪΪ�յ�
		bool bSkip;

		// 0ʱ��ִ�У�������ִ�У�
		bool bZeroTimeExec;

		// ָ�����б�ţ����ڼ򵥵���ʱ������ʾ
		// ������ָ��һ������ֵ�ϴ�����ǰ��ָ��
		DWORD dwSerialNo;

		// ��������ʱ��
		DWORD dwPushTime;
		char sData[const_iMaxActionSize];

		// ������Ĵ���
		int nProcessedCount;

		SAction():	bSkip(false),
					bZeroTimeExec(false),
					nProcessedCount(0){}
	};

	struct SAttack
	{
		short stSkill;
		int   nDstID;
		short xDst,yDst;
		short stDamage;
	};

	struct SWalk
	{
		unsigned char ucDir;
	};
	struct SFlashMove
	{
		int a;
	};
	struct STalkToNpc
	{
		int nNpcId;
	};
	struct SDeath
	{
		DWORD dwStartTime;
		BOOL bDeadOver;
	};
	struct SHoldSkillStart
	{
		DWORD dwTmp;
	};
	struct SHoldSkillEnd
	{
		DWORD dwTmp;
	};
	struct SHoldSkillOneHit
	{
		DWORD dwTmp;
	};

	struct SCancelSkill
	{
		DWORD dwTmp;
	};


private:	
	std::deque<SAction> m_deAction;

public:
	CActionQueue(void);
	~CActionQueue(void);
	
	int	size( void ){ return m_deAction.size(); }

	void Clear(void);
	bool Push_Action( SAction & action );
	bool PushFront_Action( SAction & action );
	bool PopNextAction(SAction &action);
	bool Push_Expression(ExpressionInfo* pInfo);
	bool Push_Attack(short stSkill,short stDstID,short xDst,short yDst,short stDamage);
	bool Push_Walk(unsigned char ucDir);
	bool Push_Attack(SAttackInfo* pAttackInfo);
	bool Push_Death();
	
	// ����ʹ����
	bool Push_Intonate(IntonateInfo* pIntonate);
	bool Push_CancelSkill();
	bool Push_HoldSkillStart( IntonateEndInfo* pIntoend );
	bool Push_HoldSkillOneHit();
	bool Push_HoldSkillEnd();
	bool Push_BeAttacked();
	
	bool Push_SeeHoldSkill( SSeeHoldSkill* pSee );
	
	bool PopToAttackFromEnd();
	void SkipAllWalkAction();
	void SkipAllWalkActionBefore( DWORD dwSerialNo );

	void HoldSkillOneHit();

	int  GetAttackActionNum();
};
