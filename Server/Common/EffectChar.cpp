#include "EffectChar.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GameTime.h"
#include "Formula.h"
#include "GamePlayer.h"
#include "D3DFunction.h"
#include "MessageDefine.h"
#include "GlobalDef.h"


#define EFFECTLOGICTIME 200 //逻辑帧定时器
#define OFFSET 0.05        //float比大小的偏移值
#define ONDEADDISTINCE 2  //死亡距离

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
    //取得技能的指针
    m_pSkill = GettheItemDetail().GetSkillByID(iSkillID, iSkillLevel);
    if( !m_pSkill )
        return;

	theEffectCharConfig.FindEffectCharConfigBySkillID(m_EffectCharConfig,iSkillID);

    DWORD dwNowTime = HQ_TimeGetTime();
    //生成死亡时间
    m_dwDeathTime = dwNowTime;
    m_dwDeathTime += m_pSkill->iDurationTime;
    //上次结算的时间，默认为0 ,一帮会马上结算
    m_dwLastCaluTime = 0;
    //结算的时间间隔
    m_dwEffectInterval = m_pSkill->iDamageBalanceDelay;

    //m_dwEffectInterval = m_pSkill->ustAttackInterval;

    //取得结算的
    m_iSkillID = iSkillID;
    m_iSkillLevel = iSkillLevel;
    //
    //
    m_pCaster = pCharCaster;
    m_stCasterID = pCharCaster->GetControl()->GetID();
    m_ustCasterLifeCode = pCharCaster->GetLifeCode();
    int nExact = m_pSkill->ustStatusHitRate;

    //TODO 魔法的命中率怎么体现
    /*SetMagicAttMax(pCharCaster->GetMagicAttMax()->final);
    SetMagicAttMin(pCharCaster->GetMagicAttMin()->final);
    SetPhysicAttMax(pCharCaster->GetPhysicAttMax()->final);
    SetPhysicAttMin(pCharCaster->GetPhysicAttMin()->final);*/
    //SetMagicAtt(pCharCaster->GetMagicAtt()->final);
    //SetPhysicAtt(pCharCaster->GetPhysicAtt()->final);

    //和发送者国家一致
    SetCountry( m_pCaster->GetCountry() );
	SetForce(m_pCaster->GetForce());	
	SetFightCamp( m_pCaster->GetFightCamp() );
	SetMasterID ( m_pCaster->GetID() );
	SetMoveSpeed(m_EffectCharConfig.moveSpeed);


	 //lyhtexiaoguai++
	  SCharHeroInfo sHeroAddAttr; //主人的属性
	SCharFightAttr * attr = NULL;
	if (m_pCaster->IsPlayer()) //玩家释放的 召唤怪
	{
		attr = ((GamePlayer*)m_pCaster)->GetCharFightAttr();
	}else if (m_pCaster->IsMonster())
	{
		attr = ((AiCharacter*)m_pCaster)->GetCharFightAttr();
	}
	
	
	if(!attr) return;

	 //攻击力 = 主角的攻击力 * 技能表配置的伤害率 主要用来计算 附加主人攻击力的 百分比伤害结算
     m_FightAttr.attackMagic.final = attr->attackMagic.final  * m_pSkill->fDamageRate;
	 m_FightAttr.attackPhysics.final = attr->attackPhysics.final * m_pSkill->fDamageRate;
 
	 //一些元素伤害 破甲 等
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
    ////判断在自己的结算范围内是否有npc
    //ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(m_iSkillID, m_iSkillLevel);
    ////判定合法性
    //if (NULL == pSkill)
    //    return;
    ////
    //CFormula formula;
    //CFormula::SResult *pResult;
 //   CFormula::SResult *pSrcResult;
    ////取得，攻击的目标npc
    //if (!pCharMaster->FindAttackTarget(formula, &target, pSkill))
    //    return;
    ////
    //int iTargetNum = formula.GetTargetNum();
    //if (iTargetNum <= 0)
    //    return;
    ////发消息通知客户端看到，某人受到了伤害
    //BaseCharacter *pCharTarget = NULL;
    ////
    //char szBuf[MsgSeeDamage::const_iMaxMsgSeeMDamage];
    //MsgSeeDamage *pSeeDamage = (MsgSeeDamage *)szBuf;
    //pSeeDamage->MsgSeeDamage::MsgSeeDamage();
    //pSeeDamage->header.stID = GetControl( )->GetID( );

    //SAttTargetResult result;
    //result.stAttackerWho    = pCharMaster->GetControl( )->GetID( );

    ////-------------------伤害结算----------------------

    ////设置初始数据
    //formula.SetAttacker(pCharMaster);
    //formula.SetSkill(pSkill);

    ////算出结果
    //formula.BalanceAttack();

    ////应用结果
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

    //    //如果技能是纯粹的伤害类型
    //    if (pSkill->ustDamageBalanceType==CItemDetail::balancetype_phydamage
    //    ||    pSkill->ustDamageBalanceType==CItemDetail::balancetype_magdamage)
    //    {
    //        //服务器端的改变
    //        if (!ApplyAttackDamage(0, pCharTarget, pCharMaster, pResult, &result))
    //            continue;
    //    }
    //    //其它古怪的技能类型
    //    else
    //    {
    //        //服务器端的改变
    //        if (!ApplyNonAttackDamage(0, pCharTarget, pCharMaster, pResult, &result))
    //            continue;
    //    }

    //    //客户端的通知
    //    pSeeDamage->AddResult(result.stTargetWho, result.stAttackerWho,result.stTagNum,result.stSrcNum,result.cBalanceType,result.ucStatus,result.ustTagHp,result.ustSrcHp);
    //}

    ////计算消息包的长度
    //pSeeDamage->CaluLength();

    ////发消息
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
 
    //如果技能是不存在的，结束这个法术效果
    if (NULL == m_pSkill)
    {
        //自动消失
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
        //不是维持技能的CEffectChar
        //才能自己删除
        //直接跳到消息处理
        if( !m_pSkill->bHoldSkill )
        {
            dead_flag = TRUE;            
        }    
        goto EXIT_LOOP;
    }

	 if(m_bDead) //死亡删除
	 {
        dead_flag = TRUE; 
		goto EXIT_LOOP;
	 }

    //
    dwTick = dwCurTick - m_dwLastCaluTime;
    //判断是否到了结算的时间了
    if (dwTick > m_dwEffectInterval)
    {
        //
        m_dwLastCaluTime = dwTick;
        //取得法术的释放者
        BaseCharacter*  pCharCaster = (BaseCharacter*)theRunTimeData.GetCharacterByIDAndLifecode( m_stCasterID, m_ustCasterLifeCode );
        //施法者死亡
        if (!pCharCaster)
        {
            //如果释放者不存在了，法术也应该消失
            dead_flag = TRUE;
            goto EXIT_LOOP;
        }

		//释放者死亡特效怪消失
		if (pCharCaster->IsDead())
		{
			dead_flag = TRUE;
			goto EXIT_LOOP;
		}
        //数值结算
		
		//是否移动中四方技能
       DoDamage();
        //
        m_dwLastCaluTime = dwCurTick;
    }

EXIT_LOOP:

    //消息处理
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
        //死了，应该结束了
        MsgExit exit;
        exit.header.stID = pCtrl->GetID();
        OnExit( &exit );

        ENDFUNCPERLOG( "CEffectChar->Run" );
        return;
    }

    ENDFUNCPERLOG( "CEffectChar->Run" );
}

//我的第一眼印象
Msg* CEffectChar::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    if (nBuffSize < sizeof(MsgEffectEnterMySight))
    { return NULL; }

    //无需delete的new
    MsgEffectEnterMySight* pMsg = new (szMsgBuffer) MsgEffectEnterMySight;
    pMsg->header.stID = GetControl()->GetID();
    //    
    pMsg->nMapID = GetMapID();
    pMsg->x = GetFloatX() ; //GetTileX();
    pMsg->y = GetFloatY() ; //GetTileY();
    pMsg->ustSkillID = m_iSkillID;
    pMsg->ustSkillLevel = m_iSkillLevel;
	pMsg->MasterID = m_stCasterID; //主人id 发到客户端
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
        //不处理后续的消息
        return false;
    }
    return true;
}


void CEffectChar::CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
   if(!pSkillConfig) return;

   //主要作用于 玩家释放的技能 在这个特效范围内
   //BaseCharacter::CalcEnmity(pCharTarget,pSkillConfig,nDamage); 

	// 技能不带仇恨值
	if ( pSkillConfig->stEnmity == 0 )
	{  return; }

	GamePlayer* pMaster = (GamePlayer*)m_pCaster;
	if ( pMaster == NULL  )
	{  return; }

	// 添加我攻击了对方
	pMaster->AddAttackTarget( pCharTarget->GetID() );

	// 仇恨值
	int nEnmity = (nDamage + pSkillConfig->stEnmity) / 2;
	if ( nEnmity >= 0 )
	{ 
		pCharTarget->AddEnmity( pMaster->GetID(), nEnmity, nDamage, GetEnmityRate() );
	}
	else
	{ 
		// 减少仇恨不能减少到0
		pCharTarget->DecEnmity( pMaster->GetID(), abs( nEnmity ) );
		pCharTarget->AddEnmity( pMaster->GetID(), 1, nDamage, GetEnmityRate() );
	}
}

//特效怪跟随主人
void CEffectChar::ProcessMoveToMaster(DWORD CurTime)
{

	if (m_EffectCharConfig.AiType != AI_FlowMaster)
	    return ;
	
	 if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	 { return; }

	 if (!m_pCaster) return;
	

	// 不在同一个地图, 就不跟随
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

	////// 只判断平面位置
	D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance );

	//跟随距离
	float distanceBeginFollow = m_fBodySize + m_pCaster->GetBodySize() + 1.0f;

	//// 宠物分散在玩家身后120°左右两侧
	const float fAngle = D3DX_PI / 1.5f;
	//// 主人朝向
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
	//SendSyncCharPosToGate(); // 发送同步消息到Gate



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

//特效怪移动到角色的选择目标
void CEffectChar::ProcessMoveToCasterLockTarget(DWORD CurTime)
{
	if (m_EffectCharConfig.AiType != AI_FlowAttackTarget)
		return ;

	if ( !m_xLogicTimer.DoneTimer( CurTime ) )
	{ return; }

	if(m_EffectCharConfig.WaitTime)
	{
		//计时器开启 并且 时间到了 则停止原地待命
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
		{
			m_WaitTimer.StopTimer();
		}

		//等待计时器正在运行中 则继续等待
		if(m_WaitTimer.IsStart()) 
			return ;
	}


	//// 找到攻击目标
	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_pCaster->GetLockID() );
	if ( pTarget == NULL )
	{ return; }

	if(pTarget == m_pCaster)
		return;

	// 不在同一个地图, 就不跟随
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

	////// 只判断平面位置
	D3DXVECTOR3 vecDistance( TargetPos.x - vCurPos.x, TargetPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //移动方向


	D3DXVECTOR3 _curPos = vCurPos + m_EffectCharConfig.moveSpeed * dir;

	D3DXVECTOR3 curDistance( TargetPos.x - _curPos.x, TargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
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

    //一次攻击后死亡
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

//处理移动
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
		//计时器开启 并且 时间到了 则停止原地待命
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
			m_WaitTimer.StopTimer();
		
		//等待计时器正在运行中 则继续等待
		if(m_WaitTimer.IsStart()) 
			return ;
	}

	if(m_NearAttackTargetID == -1)
		return;

	// 找到攻击目标
	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_NearAttackTargetID );
	if ( pTarget == NULL )
	{ return; }

	// 不在同一个地图, 就不跟随
	if ( pTarget->GetMapID() != GetMapID() )
	{     
		IBaseControl *pCtrl = GetControl();
		MsgExit exit;
		exit.header.stID = pCtrl->GetID();
		OnExit( &exit );
		return;
	}

	//移动到攻击目标
	D3DXVECTOR3 TargetPos = pTarget->GetPos();
	D3DXVECTOR3 vCurPos    = GetPos();

	////// 只判断平面位置
	D3DXVECTOR3 vecDistance( TargetPos.x - vCurPos.x, TargetPos.y - vCurPos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //移动方向

	D3DXVECTOR3 _curPos = vCurPos + m_EffectCharConfig.moveSpeed * dir;


	D3DXVECTOR3 curDistance( TargetPos.x - _curPos.x, TargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
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


	//一次攻击后死亡			
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
		//计时器开启 并且 时间到了 则停止原地待命
		if(m_WaitTimer.IsStart() && m_WaitTimer.DoneTimer(CurTime))
			m_WaitTimer.StopTimer();

		//等待计时器正在运行中 则继续等待
		if(m_WaitTimer.IsStart()) 
			return ;
	}

	if (m_NearAttackTargetID == -1)
	   return; //还没有开始找目标

	D3DXVECTOR3 MePos    =  GetPos();

	////// 只判断平面位置
	D3DXVECTOR3 vecDistance( m_AttackTargetPos.x - MePos.x, m_AttackTargetPos.y - MePos.y, 0 );
	float fDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir,&vecDistance); //移动方向

	D3DXVECTOR3 _curPos = MePos + m_EffectCharConfig.moveSpeed * dir;

	D3DXVECTOR3 curDistance( m_AttackTargetPos.x - _curPos.x, m_AttackTargetPos.y - _curPos.y, 0 );
	float curfDistance = D3DXVec3Length( &vecDistance ); //目标和自己之间的距离
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

	//一次攻击后死亡			
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

//设置攻击目标 可以做到一直跟随
void CEffectChar::SetAttackTarget(GameObjectId TargetID)
{

	if (m_NearAttackTargetID != -1)
	{
		if (m_EffectCharConfig.bOnceFindeNearTarget) //只找一次目标
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
	 //拿主人来判断
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

	 // NPC 不能被攻击
	 if ( pTarget->IsNpc() )
	 { return CheckAttack::CanNotAttack; }

	 // 如果是玩家
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

	 // 先判断宠物
	 GamePlayer* pMaster = pTarget->GetMasterPlayer();
	 if ( pMaster != NULL )
	 { return ((GamePlayer*) m_pCaster)->CheckCanAttackPlayer( pMaster ); }

	 // 判断专属怪信息
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


 //设置攻击位置 ，移动到位置后爆炸死亡


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