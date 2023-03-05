#include "MonsterNurturePet.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "PetSettingConfig.h"

void MonsterNurturePet::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );
	_pPetItemData = xCreateData.GetPetItem();
	UpdatePetData();
}


int MonsterNurturePet::GetHP()
{
    if (_pPetItemData == NULL)
    { return 0; }

    return _pPetItemData->baseInfo.hp;
}

void MonsterNurturePet::SetHP( int nHp )
{
    if (_pPetItemData == NULL)
    { return; }

    if ( nHp >= GetHPMax() /*m_pMonsterConfig->nHPMax*/ )
    { nHp =  GetHPMax();}

    if ( _pPetItemData->baseInfo.hp < 0)
    { _pPetItemData->baseInfo.hp = 0; }

    if ( nHp> GetHPMax() )
    { _pPetItemData->baseInfo.hp = GetHPMax(); }
    else
    { _pPetItemData->baseInfo.hp = nHp; }
}

void MonsterNurturePet::OperateHP( uint8 uchOperateType, int nValue )
{
    if (_pPetItemData == NULL)
    { return; }

    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        { _pPetItemData->baseInfo.hp += nValue; }
        break;
    case EOT_Sub:
        { _pPetItemData->baseInfo.hp -= nValue; }
        break;
    case EOT_Set:
        { _pPetItemData->baseInfo.hp = nValue; }
        break;
    default:
        return;
        break;
    }

    if ( _pPetItemData->baseInfo.hp < 0)
    { _pPetItemData->baseInfo.hp = 0; }

    if ( _pPetItemData->baseInfo.hp > GetHPMax() )
    { _pPetItemData->baseInfo.hp = GetHPMax(); }

    GamePlayer* _pGamePlayer = GetMasterPlayer();
    if (_pGamePlayer != NULL)
    { _pGamePlayer->ChangeAttr( CharAttr_ActivePetHP, _pPetItemData->baseInfo.hp, true ); }
}

void  MonsterNurturePet::RefreshCharData( DWORD dwCostTime)
{
    // ����
    BaseCharacter::RefreshCharData( dwCostTime );
}

void MonsterNurturePet::SetTitleName( const char* szTitle )
{
    strncpy_s( szTitleName, szTitle, sizeof( szTitleName ) - 1);
}

Msg* MonsterNurturePet::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize )
{
    MonsterPetEx::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pEnter = reinterpret_cast< MsgNPCEnterMySight* >( szMsgBuffer );
	
    if ( strlen( szTitleName ) != 0 )
    { HelperFunc::SafeNCpy( pEnter->szTitleName, szTitleName, sizeof( pEnter->szTitleName ) ); }

	pEnter->BelongID			= GetKiller()?GetKiller()->GetID():0;

	//ȥ��ȡ�����Ĺ�������� �ṹ ��ȡ��ǰ������ģ��ID ��Ϊģ�Ϳ�����ʱ������
	pEnter->ModeID				= _pPetItemData->baseInfo.GetPetNewModeID();//��ȡģ��ID

    return pEnter;
}

void MonsterNurturePet::ApplyPassiveSkillToChar( )
{
    if ( NULL == _pPetItemData )
    { return; }

    for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        SCharSkill* pPassiveSkill = &_pPetItemData->skillInfo.skills[i];
        if ( pPassiveSkill == NULL || pPassiveSkill->ustSkillID == InvalidLogicNumber )
        { continue; }

        ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pPassiveSkill->ustSkillID, pPassiveSkill->stSkillLevel);
        if( pSkillConfig == NULL )
        { continue; }

        if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_PetPassive)
        { continue; }

        short shPassiveSkillTarget = pSkillConfig->shPassiveSkillTarget;

        if( !(shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_Self ||
            shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndAllPet ||
            shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndTargetPet) )
        { return; }

        for (int i = 0;i < ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize; ++i )
        {
            ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pSkillConfig->ustMeAddStatusID[i], pSkillConfig->ustMeAddStatusLevel[i] );
            if( pStatus == NULL )
            { return; }

            // ���ö�������
            GetCharFightAttr()->moveSpeed.skill        += pStatus->fMoveSpeedChanged;                      // �ƶ��ٶ�
            GetCharFightAttr()->attackSpeed.skillPer   += pStatus->fAttSpeedPer;                           // �����ٶ�
            GetCharFightAttr()->attackPhysics.skill    += pStatus->changePhyAttack;                        // ��������
            GetCharFightAttr()->attackPhysics.skillPer += pStatus->changePhyAttackPer;                     // ��������%
            GetCharFightAttr()->attackMagic.skill      += pStatus->changeMagAttack ;                       // ����������
            GetCharFightAttr()->attackMagic.skillPer   += pStatus->changeMagAttackPer;                     // ����������%
            GetCharFightAttr()->defendPhysics.skill    += pStatus->changeDefend[EDefendType_Physical];     // ��� 
            //GetCharFightAttr()->defendLong .skill    += pStatus->changeDefend[EDefendType_Long];         // Զ��
            GetCharFightAttr()->defendMagic.skill      += pStatus->changeDefend[EDefendType_Magic] ;       // ħ��
            GetCharFightAttr()->defendPhysics.skillPer += pStatus->changeDefendPer[EDefendType_Physical];  // ����%
            //GetCharFightAttr()->defendLong .skillPer += pStatus->changeDefendPer[EDefendType_Long];      // Զ��%
            GetCharFightAttr()->defendMagic.skillPer   += pStatus->changeDefendPer[EDefendType_Magic];     // ħ��%
            GetCharFightAttr()->hpRestore.skill        += pStatus->resumeHP;                               // ��ɫHP�ָ��ٶȸı�
            GetCharFightAttr()->hpRestore.skillPer     += pStatus->resumeHPPer;                            // ��ɫHP�ָ��ٶȸı�%
            GetCharFightAttr()->mpRestore.skill        += pStatus->resumeMP;                               // ���MP�ָ��ٶȸı�
            GetCharFightAttr()->mpRestore.skillPer     += pStatus->resumeMPPer;                            // ���MP�ָ��ٶȸı�%
            GetCharFightAttr()->hpMax.skill            += pStatus->stChanged_HPMax;                        // Ѫ�����ֵ
            GetCharFightAttr()->hpMax.skillPer         += pStatus->changeHPMaxPer;                         // Ѫ�����ֵ%
            GetCharFightAttr()->mpMax.skill            += pStatus->stChanged_MPMax;                        // �������ֵ
            GetCharFightAttr()->mpMax.skillPer         += pStatus->changeMPMaxPer;                         // �������ֵ%
            GetCharFightAttr()->dodge.skill            += pStatus->stChanged_Hedge;                        // �ı�����
            GetCharFightAttr()->exact.skill            += pStatus->stChanged_Hit;                          // ����
            GetCharFightAttr()->critical.skill         += pStatus->changed_Critical  ;                     // ������
            GetCharFightAttr()->tenacity.skill         += pStatus->changeTenacity;                         // ����
            GetCharFightAttr()->criticalIntensity.skill+= pStatus->changed_CriticalIntensity  ;            // �����˺�
        }
    }
}

void MonsterNurturePet::SetUseSkill( uint16 nSkillID, uint16 nSkillLevel )
{
    const SCharSkill *pSkill = _pPetItemData->skillInfo.GetSkill( nSkillID );
    if ( pSkill == NULL )
    { return; }

    m_xAiSkill[ AiDefine::PetMonsterSkillIndex ].SetID( pSkill->ustSkillID );
    m_xAiSkill[ AiDefine::PetMonsterSkillIndex ].SetLevel( pSkill->stSkillLevel );

    SetUseSkillIndex( AiDefine::PetMonsterSkillIndex );
}

AiSkill* MonsterNurturePet::GetCanUseSkill( uint32 nCurrentTime )
{
    // �Ѿ���ִ��Ai
    if ( !_SkillTaskManager.IsTaskEmpty() )
    { return NULL; }

    AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
    if ( pAiSkill != NULL ) // �Ѿ���ʹ�õļ���
    {
        if ( CheckCanUseSkill( pAiSkill->GetID() ) )
        { return pAiSkill; }
    }

    // ʹ����ͨ����
    SetUseSkillIndex( 0 );
    return &m_xAiSkill[ 0 ] ;
}

void MonsterNurturePet::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // ����״̬�²�����
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingFollowMaster:
        return;
        break;
    }

    if ( !HaveLockTarget() )
    {
        // �������˵Ĺ���Ŀ��
        GamePlayer* pPlayer = GetMasterPlayer();
        if ( pPlayer == NULL || pPlayer->GetLockID() == GetID() )
        { return; }

        if ( !pPlayer->IsAttackTarget( pPlayer->GetLockID() ) )
        { return; }

        SetLockID( pPlayer->GetLockID() );
    }
}


void MonsterNurturePet::UpdatePetData()
{
    SetCharName ( _pPetItemData->baseInfo.szName );
	SetLevel    ( _pPetItemData->baseInfo.level  );

	GetCharFightAttr()->hpMax        .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_HPMax)           ;
    GetCharFightAttr()->attackPhysics.base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_AttackPhysics)   ;
    GetCharFightAttr()->attackMagic  .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_AttackMagic)     ;
    GetCharFightAttr()->defendPhysics.base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_DefendPhysics)   ;
    GetCharFightAttr()->defendMagic  .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_DefendMagic)     ;

	GetCharFightAttr()->exact        .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_Exact)           ;
	GetCharFightAttr()->dodge        .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_Dodge)           ;

	GetCharFightAttr()->critical     .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_Critical)        ;
	GetCharFightAttr()->tenacity     .base = _pPetItemData->baseInfo.GetFightAttribute(CharAttr_Tenacity)        ;

    GetCharFightAttr()->hpMax        .UpdateFinal();
    GetCharFightAttr()->attackPhysics.UpdateFinal();
    GetCharFightAttr()->attackMagic  .UpdateFinal();
    GetCharFightAttr()->defendPhysics.UpdateFinal();
    GetCharFightAttr()->defendMagic  .UpdateFinal();

    GetCharFightAttr()->exact        .UpdateFinal();
    GetCharFightAttr()->dodge        .UpdateFinal();

    GetCharFightAttr()->critical     .UpdateFinal();
    GetCharFightAttr()->tenacity     .UpdateFinal();


	SetHP( _pPetItemData->baseInfo.hp );
	SetHPMax( GetCharFightAttr()->hpMax.final );

    // ��������
    ApplyPassiveSkillToChar( );

    // ����ƺ�
    PetSettingConfig::STitle* pTitle = thePetSettingConfig.GetPetTitle( _pPetItemData->baseInfo.savvy, _pPetItemData->baseInfo.growStar, _pPetItemData->baseInfo.aptitudeLevel );
    if ( pTitle != NULL )
    { SetTitleName( pTitle->strTitleName.c_str() ); }

    //������Ұ����ҿ����������ֵ
    MsgUpdatePetChar msg;
    msg.header.stID = GetID();
    msg.petLevel    = GetLevel();
    msg.hpMax       = GetHPMax();
    msg.hp          = GetHP();
    if ( strlen( szTitleName ) != 0 )
    { HelperFunc::SafeNCpy( msg.szTitleName, szTitleName, sizeof( msg.szTitleName ) ); }
    GettheServer().SendMsgToView( &msg, GetID(), true );
}
void MonsterNurturePet::UpdatePetMode()
{
	uint32 ModeID = _pPetItemData->baseInfo.GetPetNewModeID();
	MsgUpdatePetMode msg;
	msg.header.stID = GetID();
	msg.ModeID = ModeID;
	GettheServer().SendMsgToView( &msg, GetID(), true );
}
void MonsterNurturePet::ProcessPetDeath( int deathType )
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    { 
        switch( deathType )
        {
        case EPetDeathType_BeKilled:
            pMaster->_petManager.LostActivePet( true );
            break;
        case EPetDeathType_Murder:
            pMaster->_petManager.LostActivePet( false );
            break;
        default:
            break;
        }
    }

    MonsterPetEx::ProcessPetDeath( deathType );
}

void MonsterNurturePet::SetPetItemData( SPetItem* pPet )
{
    if ( pPet == NULL )
    { return; }

    _pPetItemData = pPet;
}

bool MonsterNurturePet::TryPassivenessTriggerAttack()
{
    if ( _pPetItemData == NULL )
    { return false; }

    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL )
    { return false; }

    SkillBag* pSkillBag =  pMaster->_petManager.GetActiveSkillBag();
    if ( pSkillBag == NULL )
    { return false; }

    for ( int i=0; i< SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        SCharSkill* pPetSkill = pSkillBag->GetSkillByIndex( i );
        if ( pPetSkill == NULL || pPetSkill->ustSkillID == InvalidLogicNumber )
        { continue; }

        ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pPetSkill->ustSkillID, pPetSkill->stSkillLevel);
        if( pSkillConfig == NULL )
        { continue; }

        if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_PetMasterAutoUnControl )
        { continue; }

        int nRandNum = theRand.rand32() % RAND_THOUSAND;
        int nCharacterizePer  = thePetSettingConfig.GetCharacterizeAutoSkillPer( pSkillConfig->petSkillCategory, _pPetItemData->baseInfo.characterize );
        int nSkillActionRatio = pSkillConfig->petAutoSkillTriggerRate + pSkillConfig->petAutoSkillTriggerRate * nCharacterizePer * DEF_PERCENT;
        if ( nRandNum > nSkillActionRatio )
        { continue; }

        SAttackTarget target;
        target.bIsCharTarget = false;
        target.nCharID       = GetID();
        target.vPos          = GetPos();

        bool bCanAttack = false;
        switch ( pSkillConfig->shCastType )
        {
        case ItemDefine::casttype_singletarget:
        case ItemDefine::casttype_AOETargetcirclearea: // ��ѡ��Ŀ��Ϊ���ĵ�Բ�η�Χ����
            {
                target.bIsCharTarget = true;

                switch( pSkillConfig->ustCastTarget )
                {
                case ItemDefine::casttarget_me:
                    {   
                        target.nCharID = GetID();
                        bCanAttack     = true;
                    }
                    break;
                default:
                    if ( m_nLockID != -1)
                    {
                        target.nCharID = m_nLockID;
                        bCanAttack     = true;
                    }
                    break;
                }
            }
            break;
        case ItemDefine::casttype_AOEcircleself            : // ���Լ�Ϊ���ĵ�Բ�η�Χ���� *
        case ItemDefine::casttype_AOEquartercirlcefrontage : // ����90�ȵ����ͷ�Χ����     *
        case ItemDefine::casttype_AOEhalfcirclefrontage    : // ����180�ȵİ�Բ��Χ����
        case ItemDefine::casttype_AOEquartercirlcebackage  : // ����90�ȵ����ͷ�Χ����
        case ItemDefine::casttype_AOEhalfcirclebackage     : // ����180�ȵİ�Բ��Χ����
            {
                bCanAttack = true;
            }
            break;
        default:
            break;
        }

        if( pSkillBag->IsSkillCoolDownById( pPetSkill->ustSkillID ) )
        { bCanAttack = false; }

        if ( bCanAttack )
        {   
            CDTIME cdResult = pSkillBag->StartSkillCoolDown( pPetSkill->ustSkillID, pPetSkill->stSkillLevel );
            SkillDischarge( &target, pPetSkill->ustSkillID, pPetSkill->stSkillLevel, this );
            break;
        }
    }

    return true;
}
long MonsterNurturePet::ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue)
{
	ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(iStatusID,iStatusLevel);
	if(!pStatus)
		return GLR_StatusApplyFail;
	if(pStatus->bAvail)
	{
		//����BUFF �޷����
		BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( iMaster );
		if ( pMaster == NULL || !pMaster->IsPlayer())
			return GLR_StatusApplyFail;
		GamePlayer* pPlayer = static_cast< GamePlayer* > ( pMaster );
		MsgMonsterNurtureInfo msg;
		msg.InfoID = MsgMonsterNurtureInfo::IS_BuffFiled;
		pPlayer->SendMessageToClient(&msg);
		return GLR_StatusApplyFail;
	}
	return  AiCharacter::ApplyBufferStatus(iStatusID,iStatusLevel,iMaster,eventType,eventValue);
}
bool MonsterNurturePet::CheckCanBeAttack()
{
	if(g_Cfg.isOpenPetAttacter)
	{
		return MonsterPetEx::CheckCanBeAttack();
	}
	else
		return false;
}
void MonsterNurturePet::ProcessLockTarget( int nTargetID )
{
	if(g_Cfg.isOpenPetAttacter)
	{
		MonsterPetEx::ProcessLockTarget(nTargetID);
	}
	else
		return;
}