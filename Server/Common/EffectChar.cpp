#include "EffectChar.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GameTime.h"
#include "Formula.h"
#include "GamePlayer.h"
#include "D3DFunction.h"
#include "MessageDefine.h"
#include "GlobalDef.h"


#define EFFECTLOGICTIME 200 //�߼�֡��ʱ��
#define OFFSET 0.05        //float�ȴ�С��ƫ��ֵ
#define ONDEADDISTINCE 2  //��������

CEffectChar::CEffectChar()
{
    SetObjType( Object_Effect );
	m_NearAttackTargetID = -1;
	m_bDead = false;
	m_AttackTargetPos = D3DXVECTOR3(0,0,0);
	m_BeAttackedCnt = 0;
}

CEffectChar::~CEffectChar()
{

}

void CEffectChar::Init(BaseCharacter *pCharCaster,int iSkillID, int iSkillLevel)
{    
    //ȡ�ü��ܵ�ָ��
    m_pSkill = GettheItemDetail().GetSkillByID(iSkillID, iSkillLevel);
    if( !m_pSkill )
        return;

	theEffectCharConfig.FindEffectCharConfigBySkillID(m_EffectCharConfig,iSkillID);

    DWORD dwNowTime = HQ_TimeGetTime();
    //��������ʱ��
    m_dwDeathTime = dwNowTime;
    m_dwDeathTime += m_pSkill->iDurationTime;
    //�ϴν����ʱ�䣬Ĭ��Ϊ0 ,һ������Ͻ���
    m_dwLastCaluTime = 0;
    //�����ʱ����
    m_dwEffectInterval = m_pSkill->iDamageBalanceDelay;

    //m_dwEffectInterval = m_pSkill->ustAttackInterval;

    //ȡ�ý����
    m_iSkillID = iSkillID;
    m_iSkillLevel = iSkillLevel;
    //
    //
    m_pCaster = pCharCaster;
    m_stCasterID = pCharCaster->GetControl()->GetID();
    m_ustCasterLifeCode = pCharCaster->GetLifeCode();
    int nExact = m_pSkill->ustStatusHitRate;

    //TODO ħ������������ô����
    /*SetMagicAttMax(pCharCaster->GetMagicAttMax()->final);
    SetMagicAttMin(pCharCaster->GetMagicAttMin()->final);
    SetPhysicAttMax(pCharCaster->GetPhysicAttMax()->final);
    SetPhysicAttMin(pCharCaster->GetPhysicAttMin()->final);*/
    //SetMagicAtt(pCharCaster->GetMagicAtt()->final);
    //SetPhysicAtt(pCharCaster->GetPhysicAtt()->final);

    //�ͷ����߹���һ��
    SetCountry( m_pCaster->GetCountry() );
	SetForce(m_pCaster->GetForce());	
	SetFightCamp( m_pCaster->GetFightCamp() );
	SetMasterID ( m_pCaster->GetID() );
	SetMoveSpeed(m_EffectCharConfig.moveSpeed);


	 //lyhtexiaoguai++
	  SCharHeroInfo sHeroAddAttr; //���˵�����
	SCharFightAttr * attr = NULL;
	if (m_pCaster->IsPlayer()) //����ͷŵ� �ٻ���
	{
		attr = ((GamePlayer*)m_pCaster)->GetCharFightAttr();
	}else if (m_pCaster->IsMonster())
	{
		attr = ((AiCharacter*)m_pCaster)->GetCharFightAttr();
	}
	
	
	if(!attr) return;

	 //������ = ���ǵĹ����� * ���ܱ����õ��˺��� ��Ҫ�������� �������˹������� �ٷֱ��˺�����
     m_FightAttr.attackMagic.final = attr->attackMagic.final  * m_pSkill->fDamageRate;
	 m_FightAttr.attackPhysics.final = attr->attackPhysics.final * m_pSkill->fDamageRate;
 
	 //һЩԪ���˺� �Ƽ� ��
	 m_FightAttr.breakStrike.final =  m_pSkill->breakStrike;
	 m_FightAttr.stabStrike.final =  m_pSkill->stabStrike;
	 m_FightAttr.elementStrike.final =  m_pSkill->elementStrike;
	 m_FightAttr.toxinStrike.final =  m_pSkill->toxinStrike;
	 m_FightAttr.spiritStrike.final =  m_pSkill->spiritStrike;

	 m_xLogicTimer.StartTimer( HQ_TimeGetTime(), EFFECTLOGICTIME ); 
	 m_WaitTimer.StartTimer(HQ_TimeGetTime(), m_EffectCharConfig.WaitTime);

	  
}

void CEffectChar::DoDamageEX()
{

	//switch(m_EffectCharConfig.AiType)
	//{
	//case AI_FlowMaster:
	//case AI_FlowAttackTarget:
	//case AI_FindNearTarget:
	//	{
 //    

	//	DoDamage();
	//	}
	//	break;
	//default:
	//	{
 //         DoDamage();
	//	  return;
	//	}
	//}
}

void CEffectChar::OnDeadDoDamage(unsigned short ustSkillID, unsigned short ustSkillLevel ,float ToTargetDistance)
{

	if(m_EffectCharConfig.bOnceAttack)
	{
		if(ToTargetDistance <= ONDEADDISTINCE)
		{

			if (ustSkillID == -1 || ustSkillLevel==-1)
			{
				m_bDead = true;
				return;
			}

			GamePlayer *pCharMaster = NULL;
			//
			pCharMaster = (GamePlayer *)theRunTimeData.GetCharacterByIDAndLifecode(m_stCasterID, m_ustCasterLifeCode);
			if ( !pCharMaster || !pCharMaster->IsPlayer() )
				return;

			SAttackTarget target;
			target.bIsCharTarget = false;
			target.vPos.x = GetFloatX();//lyh++
			target.vPos.y = GetFloatY();
			SkillDischarge( &target,ustSkillID,ustSkillLevel,pCharMaster );

			m_bDead = true;

		}
	}
	return;
}

void CEffectChar::DoDamage(void)
{
    GamePlayer *pCharMaster = NULL;
    //
    pCharMaster = (GamePlayer *)theRunTimeData.GetCharacterByIDAndLifecode(m_stCasterID, m_ustCasterLifeCode);
    if ( !pCharMaster /*|| !pCharMaster->IsPlayer()*/ )
        return;

    SAttackTarget target;
    target.bIsCharTarget = false;
	target.vPos.x = GetFloatX();//lyh++
	target.vPos.y = GetFloatY();
    SkillDischarge( &target,m_iSkillID,m_iSkillLevel,pCharMaster );
    return;

    ////
    ////�ж����Լ��Ľ��㷶Χ���Ƿ���npc
    //ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(m_iSkillID, m_iSkillLevel);
    ////�ж��Ϸ���
    //if (NULL == pSkill)
    //    return;
    ////
    //CFormula formula;
    //CFormula::SResult *pResult;
 //   CFormula::SResult *pSrcResult;
    ////ȡ�ã�������Ŀ��npc
    //if (!pCharMaster->FindAttackTarget(formula, &target, pSkill))
    //    return;
    ////
    //int iTargetNum = formula.GetTargetNum();
    //if (iTargetNum <= 0)
    //    return;
    ////����Ϣ֪ͨ�ͻ��˿�����ĳ���ܵ����˺�
    //BaseCharacter *pCharTarget = NULL;
    ////
    //char szBuf[MsgSeeDamage::const_iMaxMsgSeeMDamage];
    //MsgSeeDamage *pSeeDamage = (MsgSeeDamage *)szBuf;
    //pSeeDamage->MsgSeeDamage::MsgSeeDamage();
    //pSeeDamage->header.stID = GetControl( )->GetID( );

    //SAttTargetResult result;
    //result.stAttackerWho    = pCharMaster->GetControl( )->GetID( );

    ////-------------------�˺�����----------------------

    ////���ó�ʼ����
    //formula.SetAttacker(pCharMaster);
    //formula.SetSkill(pSkill);

    ////������
    //formula.BalanceAttack();

    ////Ӧ�ý��
    //for (int i=0; i<iTargetNum; i++)
    //{
    //    pCharTarget = formula.GetTarget(i);
    //    if( !pCharTarget )
    //        continue;

    //    pResult = formula.GetTargetLastResult(i);
    //    if( !pResult )
    //        continue;
 //       pSrcResult = formula.GetSrcLastResult( i );
 //       if( !pSrcResult )
 //           continue;

    //    //��������Ǵ�����˺�����
    //    if (pSkill->ustDamageBalanceType==CItemDetail::balancetype_phydamage
    //    ||    pSkill->ustDamageBalanceType==CItemDetail::balancetype_magdamage)
    //    {
    //        //�������˵ĸı�
    //        if (!ApplyAttackDamage(0, pCharTarget, pCharMaster, pResult, &result))
    //            continue;
    //    }
    //    //�����Źֵļ�������
    //    else
    //    {
    //        //�������˵ĸı�
    //        if (!ApplyNonAttackDamage(0, pCharTarget, pCharMaster, pResult, &result))
    //            continue;
    //    }

    //    //�ͻ��˵�֪ͨ
    //    pSeeDamage->AddResult(result.stTargetWho, result.stAttackerWho,result.stTagNum,result.stSrcNum,result.cBalanceType,result.ucStatus,result.ustTagHp,result.ustSrcHp);
    //}

    ////������Ϣ���ĳ���
    //pSeeDamage->CaluLength();

    ////����Ϣ
    //GettheServer().SendMsg(this, pSeeDamage, sendrange_view);
}

void CEffectChar::Run(DWORD dwCostTime)
{
    //
    BEGINFUNCPERLOG( "CEffectChar->Run" );
    BOOL    dead_flag = FALSE;
    DWORD    dwCurTick, dwTick;
    //
    IBaseControl *pCtrl = GetControl();
    if (pCtrl != NULL)
    {
        pCtrl->Process();
    }
 
    //��������ǲ����ڵģ������������Ч��
    if (NULL == m_pSkill)
    {
        //�Զ���ʧ
        dead_flag = TRUE;
        goto EXIT_LOOP;
    }

	dwCurTick = HQ_TimeGetTime();

	ProcessMoveToCasterLockTarget(dwCurTick);
	ProcessMoveToMaster(dwCurTick);
	ProcessMoveToNearMeTarget(dwCurTick);
	ProcessMoveToAttackPos(dwCurTick);

    //
    if (m_dwDeathTime < dwCurTick)
    {
        //����ά�ּ��ܵ�CEffectChar
        //�����Լ�ɾ��
        //ֱ��������Ϣ����
        if( !m_pSkill->bHoldSkill )
        {
            dead_flag = TRUE;            
        }    
        goto EXIT_LOOP;
    }

	 if(m_bDead) //����ɾ��
	 {
        dead_flag = TRUE; 
		goto EXIT_LOOP;
	 }

    //
    dwTick = dwCurTick - m_dwLastCaluTime;
    //�ж��Ƿ��˽����ʱ����
    if (dwTick > m_dwEffectInterval)
    {
        //
        m_dwLastCaluTime = dwTick;
        //ȡ�÷������ͷ���
        BaseCharacter*  pCharCaster = (BaseCharacter*)theRunTimeData.GetCharacterByIDAndLifecode( m_stCasterID, m_ustCasterLifeCode );
        //ʩ��������
        if (!pCharCaster)
        {
            //����ͷ��߲������ˣ�����ҲӦ����ʧ
            dead_flag = TRUE;
            goto EXIT_LOOP;
        }

		//�ͷ���������Ч����ʧ
		if (pCharCaster->IsDead())
		{
			dead_flag = TRUE;
			goto EXIT_LOOP;
		}
        //��ֵ����
		
		//�Ƿ��ƶ����ķ�����
       DoDamage();
        //
        m_dwLastCaluTime = dwCurTick;
    }

EXIT_LOOP:

    //��Ϣ����
    Msg *pMsg;
    while( pMsg = pCtrl->GetMsg() )
    {
        if( !ProcessMsg( pMsg ) )
        {
            ENDFUNCPERLOG( "CEffectChar->Run" );
            return;
        }
    }
    //    
    if (dead_flag)
    {
        //���ˣ�Ӧ�ý�����
        MsgExit exit;
        exit.header.stID = pCtrl->GetID();
        OnExit( &exit );

        ENDFUNCPERLOG( "CEffectChar->Run" );
        return;
    }

    ENDFUNCPERLOG( "CEffectChar->Run" );
}

//�ҵĵ�һ��ӡ��
Msg* CEffectChar::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    if (nBuffSize < sizeof(MsgEffectEnterMySight))
    { return NULL; }

    //����delete��new
    MsgEffectEnterMySight* pMsg = new (szMsgBuffer) MsgEffectEnterMySight;
    pMsg->header.stID = GetControl()->GetID();
    //    
    pMsg->nMapID = GetMapID();
    pMsg->x = GetFloatX() ; //GetTileX();
    pMsg->y = GetFloatY() ; //GetTileY();
    pMsg->ustSkillID = m_iSkillID;
    pMsg->ustSkillLevel = m_iSkillLevel;
	pMsg->MasterID = m_stCasterID; //����id �����ͻ���
    return pMsg;
}

void CEffectChar::OnExit( Msg*pMsg, unsigned char exitType/* = ET_ExitGame*/)
{
    GameObjectId stID = GetControl()->GetID();
    GettheServer().SendMsgToView( pMsg, GetID(), false );
    theGameWorld.GlobalMessage( GameWorld::ExtMsg_DelCharacter,stID );
    theRunTimeData.ReleaseObject( stID , __FILE__, __LINE__);
}

bool CEffectChar::ProcessMsg(Msg*pMsg)
{  
    if( MSG_EXIT == pMsg->GetType() )
    {
        OnExit( pMsg );
        //�������������Ϣ
        return false;
    }
    return true;
}


void CEffectChar::CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
   if(!pSkillConfig) return;

   //��Ҫ������ ����ͷŵļ��� �������Ч��Χ��
   //BaseCharacter::CalcEnmity(pCharTarget,pSkillConfig,nDamage); 

	// ���ܲ������ֵ
	if ( pSkillConfig->stEnmity == 0 )
	{  return; }

	GamePlayer* pMaster = (GamePlayer*)m_pCaster;
	if ( pMaster == NULL  )
	{  return; }

	// ����ҹ����˶Է�
	pMaster->AddAttackTarget( pCharTarget->GetID() );

	// ���ֵ
	int nEnmity = (nDamage + pSkillConfig->stEnmity) / 2;
	if ( nEnmity >= 0 )
	{ 
		pCharTarget->AddEnmity( pMaster->GetID(), nEnmity, nDamage, GetEnmityRate() );
	}
	else
	{ 
		// ���ٳ�޲��ܼ��ٵ�0
		pCharTarget->DecEnmity( pMaster->GetID(), abs( nEnmity ) );
		pCharTarget->AddEnmity( pMaster->GetID(), 1, nDamage, GetEnmityRate() );
	}
}

//��Ч�ָ�������
void CEffectChar::ProcessMoveToMaster(DWORD CurTime)
{

	if (m_EffectCharConfig.AiType != AI_FlowMaster)
	    return ;
	
	 if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	 { return; }

	 if (!m_pCaster) return;
	

	// ����ͬһ����ͼ, �Ͳ�����
	if ( m_pCaster->GetMapID() != GetMapID() )
	{     
		IBaseControl *pCtrl = GetControl();
		MsgExit exit;
	    exit.header.stID = pCtrl->GetID();
	    OnExit( &exit );
	    return;
	 }

   theGameWorld.OnRefreshNewArea( GetID() );

	D3DXVECTOR3 vMasterPos = m_pCaster->GetPos();
	D3DXVECTOR3 vCurPos    = GetPos();

	////// ֻ�ж�ƽ��λ��
	D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance );

	//�������
	float distanceBeginFollow = m_fBodySize + m_pCaster->GetBodySize() + 1.0f;

	//// �����ɢ��������120����������
	const float fAngle = D3DX_PI / 1.5f;
	//// ���˳���
	D3DXVECTOR3 vSummonerDir = D3DXVECTOR3( m_pCaster->GetDirX(), m_pCaster->GetDirY(), 0 );
	float fCorrect = m_pCaster->GetBodySize() + m_fBodySize + 0.5;

	D3DXVECTOR3 _curPos = GetTargetPos(m_pCaster->GetPos(), vSummonerDir,  fCorrect, distanceBeginFollow);


	//GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
	//if( pStage == NULL )
	//{ return ; } 

	//

	//D3DXVECTOR3 vPos = GetPos();

	//int nX = FloatToTile( vPos.x );
	//int nY = FloatToTile( vPos.y );

	//int nCurArea = pStage->TestAreaNumber( nX, nY );

	//SetCurArea( nCurArea );
	//SendSyncCharPosToGate(); // ����ͬ����Ϣ��Gate



	if(FloatInRect(_curPos.x,_curPos.y))
		return;


	MsgUnPlayerMovingToPos xMoveTo;                    
	xMoveTo.header.stID = GetID();
	xMoveTo.vStartPos.x = GetFloatX();
	xMoveTo.vStartPos.y = GetFloatY();
	xMoveTo.vStartPos.z = WORLD_HEIGHT;
	xMoveTo.vEndPos     = _curPos;
	GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
	SetFloatXF(_curPos.x);
	SetFloatYF(_curPos.y);

	
}

//��Ч���ƶ�����ɫ��ѡ��Ŀ��
void CEffectChar::ProcessMoveToCasterLockTarget(DWORD CurTime)
{
	if (m_EffectCharConfig.AiType != AI_FlowAttackTarget)
		return ;

	if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	{ return; }

	if(m_EffectCharConfig.WaitTime)
	{
		//��ʱ������ ���� ʱ�䵽�� ��ֹͣԭ�ش���
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
		{
			m_WaitTimer.StopTimer();
		}

		//�ȴ���ʱ������������ ������ȴ�
		if(m_WaitTimer.IsStart()) 
			return ;
	}


	//// �ҵ�����Ŀ��
	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_pCaster->GetLockID() );
	if ( pTarget == NULL )
	{ return; }

	if(pTarget == m_pCaster)
		return;

	// ����ͬһ����ͼ, �Ͳ�����
	if ( pTarget->GetMapID() != GetMapID() )
	{     
		IBaseControl *pCtrl = GetControl();
		MsgExit exit;
		exit.header.stID = pCtrl->GetID();
		OnExit( &exit );
		return;
	}

	D3DXVECTOR3 TargetPos = pTarget->GetPos();
	D3DXVECTOR3 vCurPos    = GetPos();

	////// ֻ�ж�ƽ��λ��
	D3DXVECTOR3 vecDistance( TargetPos.x - vCurPos.x, TargetPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //�ƶ�����


	D3DXVECTOR3 _curPos = vCurPos + m_EffectCharConfig.moveSpeed * dir;

	D3DXVECTOR3 curDistance( TargetPos.x - _curPos.x, TargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	if ( curfDistance <= m_EffectCharConfig.moveSpeed)
	{
		MsgUnPlayerMovingToPos xMoveTo;                    
		xMoveTo.header.stID = GetID();
		xMoveTo.vStartPos.x = GetFloatX();
		xMoveTo.vStartPos.y = GetFloatY();
		xMoveTo.vStartPos.z = WORLD_HEIGHT;
		xMoveTo.vEndPos     = _curPos;
		GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
		SetFloatXF(_curPos.x);
		SetFloatYF(_curPos.y);

		OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);
		return;
	}

    //һ�ι���������
	OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);

	if(FloatInRect(TargetPos.x,TargetPos.y))
		return;

	MsgUnPlayerMovingToPos xMoveTo;                    
	xMoveTo.header.stID = GetID();
	xMoveTo.vStartPos.x = GetFloatX();
	xMoveTo.vStartPos.y = GetFloatY();
	xMoveTo.vStartPos.z = WORLD_HEIGHT;
	xMoveTo.vEndPos     = _curPos;
	GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
	SetFloatXF(_curPos.x);
	SetFloatYF(_curPos.y);
}

//�����ƶ�
void CEffectChar::ProcessMoveToNearMeTarget(DWORD CurTime)
{

	if (m_EffectCharConfig.bOnceFindeNearTarget)
      return;

	if (m_EffectCharConfig.AiType != AI_FindNearTarget)
		return  ;

	if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	{ return ; }

	if(m_EffectCharConfig.WaitTime)
	{
		//��ʱ������ ���� ʱ�䵽�� ��ֹͣԭ�ش���
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
			m_WaitTimer.StopTimer();
		
		//�ȴ���ʱ������������ ������ȴ�
		if(m_WaitTimer.IsStart()) 
			return ;
	}

	if(m_NearAttackTargetID == -1)
		return;

	// �ҵ�����Ŀ��
	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_NearAttackTargetID );
	if ( pTarget == NULL )
	{ return; }

	// ����ͬһ����ͼ, �Ͳ�����
	if ( pTarget->GetMapID() != GetMapID() )
	{     
		IBaseControl *pCtrl = GetControl();
		MsgExit exit;
		exit.header.stID = pCtrl->GetID();
		OnExit( &exit );
		return;
	}

	//�ƶ�������Ŀ��
	D3DXVECTOR3 TargetPos = pTarget->GetPos();
	D3DXVECTOR3 vCurPos    = GetPos();

	////// ֻ�ж�ƽ��λ��
	D3DXVECTOR3 vecDistance( TargetPos.x - vCurPos.x, TargetPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //�ƶ�����

	D3DXVECTOR3 _curPos = vCurPos + m_EffectCharConfig.moveSpeed * dir;


	D3DXVECTOR3 curDistance( TargetPos.x - _curPos.x, TargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	if ( curfDistance <= m_EffectCharConfig.moveSpeed)
	{
		MsgUnPlayerMovingToPos xMoveTo;                    
		xMoveTo.header.stID = GetID();
		xMoveTo.vStartPos.x = GetFloatX();
		xMoveTo.vStartPos.y = GetFloatY();
		xMoveTo.vStartPos.z = WORLD_HEIGHT;
		xMoveTo.vEndPos     = _curPos;
		GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
		SetFloatXF(_curPos.x);
		SetFloatYF(_curPos.y);

		OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);
		return;
	}


	//һ�ι���������			
	OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);

	if(FloatInRect(TargetPos.x,TargetPos.y))
		return;

	MsgUnPlayerMovingToPos xMoveTo;                    
	xMoveTo.header.stID = GetID();
	xMoveTo.vStartPos.x = GetFloatX();
	xMoveTo.vStartPos.y = GetFloatY();
	xMoveTo.vStartPos.z = WORLD_HEIGHT;
	xMoveTo.vEndPos     = _curPos;
	GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
	SetFloatXF(_curPos.x);
	SetFloatYF(_curPos.y);

}

void CEffectChar::ProcessMoveToAttackPos(DWORD CurTime)
{

	if (!m_EffectCharConfig.bOnceFindeNearTarget)
		return;

	if (m_EffectCharConfig.AiType != AI_FindNearTarget)
		return  ;

	if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	{ return ; }

	if(m_EffectCharConfig.WaitTime)
	{
		//��ʱ������ ���� ʱ�䵽�� ��ֹͣԭ�ش���
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
			m_WaitTimer.StopTimer();

		//�ȴ���ʱ������������ ������ȴ�
		if(m_WaitTimer.IsStart()) 
			return ;
	}

	if (m_NearAttackTargetID == -1)
	   return; //��û�п�ʼ��Ŀ��

	D3DXVECTOR3 MePos    =  GetPos();

	////// ֻ�ж�ƽ��λ��
	D3DXVECTOR3 vecDistance( m_AttackTargetPos.x - MePos.x, m_AttackTargetPos.y - MePos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //�ƶ�����

	D3DXVECTOR3 _curPos = MePos + m_EffectCharConfig.moveSpeed * dir;

	D3DXVECTOR3 curDistance( m_AttackTargetPos.x - _curPos.x, m_AttackTargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //Ŀ����Լ�֮��ľ���
	if ( curfDistance <= m_EffectCharConfig.moveSpeed)
	{
		MsgUnPlayerMovingToPos xMoveTo;                    
		xMoveTo.header.stID = GetID();
		xMoveTo.vStartPos.x = GetFloatX();
		xMoveTo.vStartPos.y = GetFloatY();
		xMoveTo.vStartPos.z = WORLD_HEIGHT;
		xMoveTo.vEndPos     = _curPos;
		GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
		SetFloatXF(_curPos.x);
		SetFloatYF(_curPos.y);

		OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);
		return;
	}

	//һ�ι���������			
	OnDeadDoDamage(m_EffectCharConfig.OnDeadUseSkill,m_EffectCharConfig.OnDeadUseSkillLevel,fDistance);

	if(FloatInRect(m_AttackTargetPos.x,m_AttackTargetPos.y))
		return;

	MsgUnPlayerMovingToPos xMoveTo;                    
	xMoveTo.header.stID = GetID();
	xMoveTo.vStartPos.x = GetFloatX();
	xMoveTo.vStartPos.y = GetFloatY();
	xMoveTo.vStartPos.z = WORLD_HEIGHT;
	xMoveTo.vEndPos     = _curPos;
	GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); 
	SetFloatXF(_curPos.x);
	SetFloatYF(_curPos.y);

}

//���ù���Ŀ�� ��������һֱ����
void CEffectChar::SetAttackTarget(GameObjectId TargetID)
{

	if (m_NearAttackTargetID != -1)
	{
		if (m_EffectCharConfig.bOnceFindeNearTarget) //ֻ��һ��Ŀ��
		{
			return;
		}
	}

	m_NearAttackTargetID = TargetID;

	if (m_EffectCharConfig.bOnceFindeNearTarget)
	{
		BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_NearAttackTargetID );
		if ( pTarget == NULL )
		{ return; }

		m_AttackTargetPos = pTarget->GetPos();
	}	
}

 void CEffectChar::OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig )
 {
	 if (!pAttacker)
	 { return; }

	 m_BeAttackedCnt++;

	 if (m_BeAttackedCnt >= m_EffectCharConfig.BeAttackDeadCnt )
	 {
		 m_bDead = true;
	 }

 }

  uint8 CEffectChar::CheckCanAttackResult( BaseCharacter* pTarget )
 {
	 //���������ж�
     if (!m_pCaster)
		 return CheckAttack::AttackUnknow;
 
	 uint8 nCheckResult = BaseCharacter::CheckCanAttackResult( pTarget );
	 if (m_pCaster->IsMonster())
	 {
		 return nCheckResult;
	 }


	 switch ( nCheckResult )
	 {
	 case CheckAttack::CanNotAttack:
	 case CheckAttack::EnmityFightCamp:
	 case CheckAttack::EnmityForce:
	 case CheckAttack::EnmityTarget:
		 {
			 return nCheckResult;
		 }
		 break;
	 case CheckAttack::EnmityCountry:
		 {
			 if ( pTarget->IsNpc() )
			 { return nCheckResult; }
		 }
		 break;
	 default:
		 break;
	 }

	 // NPC ���ܱ�����
	 if ( pTarget->IsNpc() )
	 { return CheckAttack::CanNotAttack; }

	 // ��������
	 if ( pTarget->IsPlayer())
	 {
		 GamePlayer* pPlayer = static_cast< GamePlayer* >( pTarget );
		 return ((GamePlayer*) m_pCaster)->CheckCanAttackPlayer( pPlayer );
	 }

	 if(pTarget->IsEffectChar())
	 {
		 BaseCharacter * Caster = ((CEffectChar*) pTarget)->GetCaster();
		 if (Caster)
		 {
			 return ((GamePlayer*) m_pCaster)->CheckCanAttackPlayer( ((GamePlayer*)Caster) );
		 }
	 }

	 // ���жϳ���
	 GamePlayer* pMaster = pTarget->GetMasterPlayer();
	 if ( pMaster != NULL )
	 { return ((GamePlayer*) m_pCaster)->CheckCanAttackPlayer( pMaster ); }

	 // �ж�ר������Ϣ
	 int nSpecialType = pTarget->GetSpecialType();
	 switch ( nSpecialType )
	 {
	 case MonsterDefine::SpecialPlayerAttack:
		 {
			 if ( pTarget->GetSpecialValue() == ((GamePlayer*) m_pCaster)->GetDBCharacterID() )
			 { return CheckAttack::EnmityTarget; }
		 }
		 break;
	 case MonsterDefine::SpecialTeamAttack:
		 {
			 if ( pTarget->GetSpecialValue() == ((GamePlayer*) m_pCaster)->GetTeamID() )
			 { return CheckAttack::EnmityTarget; }
		 }
		 break;
	 default:
		 break;
	 }
	 return CheckAttack::AttackUnknow;
 }


 //���ù���λ�� ���ƶ���λ�ú�ը����


bool CEffectChar::FloatInRect(float x,float y)
{
	D3DXVECTOR3 vCurPos    = GetPos();
	if (vCurPos.x > x + OFFSET)
		return false;

	if (vCurPos.x < x - OFFSET)
		return false;

	if (vCurPos.y > y + OFFSET)
		return false;

	if (vCurPos.y < y - OFFSET)
		return false;

	return true;
}