/********************************************************************
    Filename:     EffectChar.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_EFFECTCHAR_H__
#define __GAMESERVER_EFFECTCHAR_H__

#pragma once

#include "BaseCharacter.h"
#include "GamePlayer.h"
#include "ItemDetail.h"
#include "EffectCharConfig.h"



//特效怪的技能配置文件为 EffectCharSkill.config 以后添加

class CEffectChar : public BaseCharacter, 
                    public DEffectChar,
                    INHERIT_POOL_PARAM( CEffectChar, 10 )
{
public:
    DECLARE_POOL_FUNC( CEffectChar )

    CEffectChar();
    virtual ~CEffectChar();

    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    /*virtual SCharFightAttr* GetCharFightAttr(){ static SCharFightAttr instance; return &instance; }*/


	virtual SCharFightAttr* GetCharFightAttr(){return &m_FightAttr; }
    virtual void   SetHPMax( uint32 hpMax ){ _hpMax = hpMax; }
    virtual uint32 GetHPMax()              { return _hpMax;  }
    //////////////////////////////////////////////////////////////////////////

    virtual Msg* FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);
    virtual bool ProcessMsg(Msg*pMsg);
    virtual void OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame);    
    virtual void RefreshEnmity(){} // 刷新仇恨
    virtual void OnDeath(void){}
    virtual void Run(DWORD dwCostTime);    
    void    Init( BaseCharacter* pCharCaster,int iSkillID, int iSkillLevel);    
    GameObjectId  GetCasterID( void ){ return m_stCasterID; }
    BaseCharacter* GetCaster(){ return m_pCaster; }
	virtual bool IsEffectChar() { return true; }
	//计算仇恨
	 virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );
	 //被攻击
	 virtual void  OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig );
	 //检查是否可以攻击目标
	 virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

	virtual void ProcessMoveToCasterLockTarget(DWORD CurTime);
	virtual void ProcessMoveToMaster(DWORD CurTime);
	virtual void ProcessMoveToNearMeTarget(DWORD CurTime); 
	virtual void ProcessMoveToAttackPos(DWORD CurTime);
	virtual void SetAttackTarget(GameObjectId TargetID);
	


	

protected:
	void DoDamageEX();//综合一些逻辑的伤害结算 
	bool FloatInRect(float x,float y);
	GameTimerEx m_xLogicTimer; //逻辑定时器帧循环定时器
	GameTimerEx m_WaitTimer;   //原地等待定时器

private:
	void OnDeadDoDamage(unsigned short ustSkillID, unsigned short ustSkillLevel,float ToTargetDistance);
	void DoDamage(); // 法术技能的结算

private:
    DWORD    m_dwDeathTime;    //死亡时间
    DWORD    m_dwLastCaluTime;//上次结算的时间
    DWORD    m_dwEffectInterval;//技能效果攻击间隔
    int      m_iSkillID;        //对应的技能
    int      m_iSkillLevel;    //对应的技能等级
    ItemDefine::SItemSkill *m_pSkill;
    //记录技能的释放者..需要ID和LifeCode都一样，才能确定是正确的npc
    GameObjectId    m_stCasterID;		 //使用者的ID
    unsigned		 m_ustCasterLifeCode;//使用者的LifeCode
    BaseCharacter*	 m_pCaster;

	SCharFightAttr   m_FightAttr;
	EFFECTCHARCONFIG m_EffectCharConfig;
	GameObjectId     m_NearAttackTargetID;   
	bool             m_bDead;
	D3DXVECTOR3      m_AttackTargetPos;
	int              m_BeAttackedCnt;

};

#endif // __GAMESERVER_EFFECTCHAR_H__
