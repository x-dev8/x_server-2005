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



//��Ч�ֵļ��������ļ�Ϊ EffectCharSkill.config �Ժ����

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
    virtual void RefreshEnmity(){} // ˢ�³��
    virtual void OnDeath(void){}
    virtual void Run(DWORD dwCostTime);    
    void    Init( BaseCharacter* pCharCaster,int iSkillID, int iSkillLevel);    
    GameObjectId  GetCasterID( void ){ return m_stCasterID; }
    BaseCharacter* GetCaster(){ return m_pCaster; }
	virtual bool IsEffectChar() { return true; }
	//������
	 virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );
	 //������
	 virtual void  OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig );
	 //����Ƿ���Թ���Ŀ��
	 virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

	virtual void ProcessMoveToCasterLockTarget(DWORD CurTime);
	virtual void ProcessMoveToMaster(DWORD CurTime);
	virtual void ProcessMoveToNearMeTarget(DWORD CurTime); 
	virtual void ProcessMoveToAttackPos(DWORD CurTime);
	virtual void SetAttackTarget(GameObjectId TargetID);
	


	

protected:
	void DoDamageEX();//�ۺ�һЩ�߼����˺����� 
	bool FloatInRect(float x,float y);
	GameTimerEx m_xLogicTimer; //�߼���ʱ��֡ѭ����ʱ��
	GameTimerEx m_WaitTimer;   //ԭ�صȴ���ʱ��

private:
	void OnDeadDoDamage(unsigned short ustSkillID, unsigned short ustSkillLevel,float ToTargetDistance);
	void DoDamage(); // �������ܵĽ���

private:
    DWORD    m_dwDeathTime;    //����ʱ��
    DWORD    m_dwLastCaluTime;//�ϴν����ʱ��
    DWORD    m_dwEffectInterval;//����Ч���������
    int      m_iSkillID;        //��Ӧ�ļ���
    int      m_iSkillLevel;    //��Ӧ�ļ��ܵȼ�
    ItemDefine::SItemSkill *m_pSkill;
    //��¼���ܵ��ͷ���..��ҪID��LifeCode��һ��������ȷ������ȷ��npc
    GameObjectId    m_stCasterID;		 //ʹ���ߵ�ID
    unsigned		 m_ustCasterLifeCode;//ʹ���ߵ�LifeCode
    BaseCharacter*	 m_pCaster;

	SCharFightAttr   m_FightAttr;
	EFFECTCHARCONFIG m_EffectCharConfig;
	GameObjectId     m_NearAttackTargetID;   
	bool             m_bDead;
	D3DXVECTOR3      m_AttackTargetPos;
	int              m_BeAttackedCnt;

};

#endif // __GAMESERVER_EFFECTCHAR_H__
