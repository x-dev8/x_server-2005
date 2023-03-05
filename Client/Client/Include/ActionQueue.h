#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
#include "MsgBase.h"
#include "ItemDetail.h"

class CPlayer;
// class CWalkPath;
class CPlayerAnim;
// 动作序列， 动作的还原播放式,
// 现有动作[移动，攻击]
//   added 2003.10.25
#define MAX_ATTACKINFO_RECORD dr_MaxAttackTarget

struct SAttackInfoRecord
{
	DWORD dwState;		//技能附加的状态
	int	iBalanceType;	//结算参数
	int iTagNum;     	//被攻击者显示的数字
	int	iTagHp;			//被攻击者的HP
    int iSrcHpNum;      //攻击者血量变化的数字
	int	iTagMp;			//被攻击者的MP
	int iSrcMpNum;      //攻击者MP变化的数字
	int iTagMpNum;      //被攻击者MP变化的数字
	int nTargetID;		//目标的ID
    short stTagBackAttackNum; // 目标受背击跳出的数值
    int   nShieldHp;          // 魔法盾吸收HP
};

struct SAttackInfo : public MeCommonAllocObj<SAttackInfo>
{
	short stSrcX, stSrcY;//攻击者的位置
	int iSkill;			// 技能编号
	int	iSkillLevel;	//使用的技能的等级
	DWORD dwHoldTime;
	DWORD dwActionTime;

	int	iSrcHp;			//攻击者的HP
	int	iSrcMp;			//攻击者的MP
	int	iSrcNum;		//攻击者显示的HP数字
	int	iSrcMpNum;		//攻击者显示的MP数字
	int	nSrcId;
	DWORD dwSerialNo;

	bool bIsCharTarget;			//是否角色目标

	FPos3 pos;			// 目标点( point aoe用 )

	int nTargetId;					//目标坐标

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

//吟唱结束后的施展法动作
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

//看到表情动作
struct ExpressionInfo
{
	DWORD dwSerialNo;
	//
	int iActionID;    //行为动作的时间
};
//呤唱需要的数据
struct IntonateInfo
{
	int	iSkillNo;
	int iSkillLevel;
	//
	DWORD	dwDelayTime; //持续的时间
	//
	CPlayer* pSrc;		//攻击者
	CPlayer* pDst;		//攻击目标
	//
	DWORD dwSerialNo;
	//当前吟唱进度
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
		
		A_STARTHOLDSKILL,		// 开始持续技能				A_INTINATE_END
		//A_HOLDSKILLONEHIT,		// 持续技能的一次命中
		A_ENDHOLDSKILL,			// 结束持续技能
		A_CANCELSKILL,

		A_SEEHOLDSKILL			//看到持续技能

		,A_BEATTACKED			//被击动作
	};	

	struct SAction
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

		// 动作入列时间
		DWORD dwPushTime;
		char sData[const_iMaxActionSize];

		// 经处理的次数
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
	
	// 技能使用类
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
