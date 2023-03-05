#include "GamePlayer.h"
#include "ShareData.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "TeamManager.h"
#include "XinFaConfig.h"
#include "LogEventService.h"

bool GamePlayer::OnSkillLevelUp()
{       
    /*int noldlevel = GetSkillLevel();
    SetSkillLevel(theExpStage.GetSkillLevel(GetSkillExp()));
    if( GetSkillLevel() == noldlevel )
    return;
    unsigned short sLevel = GetSkillLevel();

    int iPoint = 0;
    CItemDetail::SUpBaseAttr* pUpBaseAttr = GettheItemDetail().GetBaseAttrByLevel(sLevel);
    if ( pUpBaseAttr )
    iPoint = pUpBaseAttr->stSkillPoint;*/

    SCharSkill* pCharSkill = _SkillBag.GetSkillByID( GetSkillExpForSkillID() );
    if ( !pCharSkill )
        return false;

    unsigned short ustSkillId = pCharSkill->ustSkillID;
    unsigned short ustLevel   = pCharSkill->stSkillLevel;
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(ustSkillId,ustLevel+1);
    if ( !pSkill)
        return false;

    if ( pSkill->cLearnProfessionReq != GetProfession())
        return false;

    if ( ustLevel+1 >= pSkill->ustSkillMaxLvl)
        return false;

    DWORD dwSkillExp = GetSkillExpToSkill(ustSkillId);
    if ( dwSkillExp < pSkill->nLearnNeedExp)
        return false;

    ++pCharSkill->stSkillLevel;

    if (pCharSkill->stSkillLevel == pSkill->ustSkillMaxLvl)
        SetSkillExpToSkill(0,ustSkillId);
    else
        SetSkillExpToSkill(dwSkillExp - pSkill->nLearnNeedExp,ustSkillId);

    MsgCharSkillLevelup msgSeeCharSkillLevelup;
    msgSeeCharSkillLevelup.header.stID      = GetID();
    msgSeeCharSkillLevelup.ustSkillNewLevel = pCharSkill->stSkillLevel;
    msgSeeCharSkillLevelup.ustSkillID       = pCharSkill->ustSkillID;
    GettheServer().SendMsgToSingle( &msgSeeCharSkillLevelup, this );

    MsgSkillExpUp SkillExpUp;
    SkillExpUp.header.stID  = GetID();    
    SkillExpUp.dwSkillExp   = pCharSkill->dwCurSkillExp;
    SkillExpUp.ustSkillID   = pCharSkill->ustSkillID;
    SkillExpUp.stSkilllevel = pCharSkill->stSkillLevel;
    GettheServer().SendMsgToSingle(&SkillExpUp,this);

    //LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO,theXmlString.GetStringWithName(eLog_info_2slk_60), GetCharName(), pCharSkill->ustSkillID,pCharSkill->stSkillLevel );
    Log(theXmlString.GetString(eLog_info_2slk_60)," ",pCharSkill->ustSkillID,pCharSkill->stSkillLevel );

    if( pSkill->stGeneralType == ItemDefine::generaltype_passive )
    {
        ApplyPassiveSkillsToChar();
        RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Skill );
    }

    return true;
}

SkillBag* GamePlayer::GetSkillBagBySkill( ItemDefine::SItemSkill* pSkill )
{
    if ( pSkill == NULL )
    { return  &_SkillBag; }

    SkillBag* pSkillBag = NULL;
    if ( pSkill->sSkillCategory >= ItemDefine::SCT_MountPassive  && pSkill->sSkillCategory <= ItemDefine::SCT_MountMasterInitiativeControl )
    { // ���＼��
        //pSkillBag = &_mountManager._activeSkillBag;
        pSkillBag = &_SkillBag;
    }
    else if ( pSkill->sSkillCategory >= ItemDefine::SCT_PetPassive  && pSkill->sSkillCategory <= ItemDefine::SCT_PetMasterManualControl )
    { // ���＼��
        pSkillBag = &_petManager._activeSkillBag;
    }
	else if ( pSkill->sSkillCategory >= ItemDefine::SCT_HeroPassive  && pSkill->sSkillCategory <= ItemDefine::SCT_HeroAttack )
	{
		pSkillBag = &_HeroSkillBag;
	}
    else
    { // �˼���
        pSkillBag = &_SkillBag;
    }

    return pSkillBag;
}

CDTIME GamePlayer::StartSkillCoolDown( ItemDefine::SItemSkill* pSkill )
{
    CDTIME result( 0, 0 );

    if ( pSkill == NULL )
    { return result; }

    if ( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
        if ( pTeam != NULL )
        {
            result = pTeam->StartTeamSkillCoolDown( pSkill->ustItemID, pSkill->ustLevel, pSkill->dwSkillCoolDownTime );  // ��ÿ����Ա����CDʱ��
        }
    }
    else
    {
        result = StartSkillCoolDown( pSkill->ustItemID, pSkill->ustLevel );
    }

    return result;
}

CDTIME GamePlayer::StartSkillCoolDown( unsigned short ustSkillID, short stSkillLevel )
{       
    CDTIME dwColdTimePair;
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(ustSkillID, stSkillLevel);    
    if ( NULL == pSkill)
    { return dwColdTimePair; }

    SkillBag* pSkillBag =  GetSkillBagBySkill( pSkill );

    // ���ܽ�Ӳʱ��
    if(pSkill->ustHoldTime > 0)
    { m_ExtendStatus.EnterCanNotNormalAttack(pSkill->ustHoldTime); }

    if ( pSkillBag == NULL )
        return dwColdTimePair;

    dwColdTimePair = pSkillBag->StartSkillCoolDown( _buffManager, ustSkillID, stSkillLevel );
    if( 0 == dwColdTimePair.first )
    { return dwColdTimePair; }

    Msg_Skill_BeginCoolDown begin;
    begin.header.stID   = GetID();
    begin.ustSkillID    = ustSkillID;
    begin.ustSkillLevel = stSkillLevel;
    begin.dwColdTime    = dwColdTimePair.first;
    GettheServer().SendMsgToSingle( &begin, this );
    return dwColdTimePair;
}

void GamePlayer::ClearSkillCollDown( unsigned short ustSkillID, bool bSendToClient /* = true */ )
{
    if ( _SkillBag.ClearSkillCollDown( ustSkillID ) )
    {
        if ( bSendToClient )
        {
            // �·���Ϣ���ͻ���
            MsgClearSkillCollDown xMsg;
            xMsg.ustSkillID = ustSkillID;
            GettheServer().SendMsgToSingle( &xMsg, this );
        }
    }

	{
		_HeroSkillBag.ClearSkillCollDown(ustSkillID);
	}

    if (_mountManager.GetActiveMount() != NULL)
    {
        _mountManager._activeSkillBag.ClearSkillCollDown( ustSkillID );
    }
}

bool GamePlayer::CanLearnSkill( int nSkillId, int nLevel )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillId, nLevel );
    if( pSkill == NULL )
    { return false; }

    if ( pSkill->cLearnProfessionReq != -1 && pSkill->cLearnProfessionReq != GetProfession() )
    { return false; }

    int nLearnLevelReq  = pSkill->stLearnLevelReq;
    int nMoneyNeed      = pSkill->stMoneyNeed;
    int nSkillExp       = pSkill->nLearnNeedExp;

    if (nLearnLevelReq > GetLevel())
    { return false; }

    if (nMoneyNeed > GetJiaoZiMoney() )
    { return false; }

    if (nSkillExp > GetSkillExpUnUsed())
    { return false; }

    return true;
}

bool GamePlayer::LearnSkill( int iWhichSkill, int level, bool bCheckSkillExp,bool bMessageDialog, bool bRecalc )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( iWhichSkill, level );
    if( pSkill == NULL )
    { return false; }

    if ( pSkill->cLearnProfessionReq != -1 && pSkill->cLearnProfessionReq != GetProfession())
    { return false; }

    int nLearnLevelReq  = pSkill->stLearnLevelReq;
    int nMoneyNeed      = pSkill->stMoneyNeed;
    int nSkillExp       = pSkill->nLearnNeedExp;

    //�ű��е��ò��жϵȼ������Ǯ
    if (bCheckSkillExp)
    {
        if (nLearnLevelReq > GetLevel())
        { 
            MsgAckResult msg;
            msg.result = ER_NoLevelToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return false; 
        }

        if (nMoneyNeed > GetJiaoZiMoney() )
        { 
            MsgAckResult msg;
            msg.result = ER_NoMoneyToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return false; 
        }

        if (nSkillExp > GetSkillExpUnUsed())
        { 
            MsgAckResult msg;
            msg.result = ER_NoExpToLearnSkill;
            GettheServer().SendMsgToSingle( &msg, this );
            return false; 
        }
    }

    // ��������ֻ��ѧϰ����
    if ( IsRecipeSkill(iWhichSkill) && GetCharInfo().baseinfo.liveinfo.nRecipeSkillNum >= RecipeSkillNumMax )
    {
        MsgAckResult msg;
        msg.result = ER_CanLearnMoreRecipeSkill;
        GettheServer().SendMsgToSingle( &msg, this );
        return false; 
    }

    bool bIsNewSkill = false;
    SCharSkill* pCharSkill = _SkillBag.GetSkillByID(iWhichSkill);//����Ҽ��ܱ����и��ݼ���ID��ã��Ƿ��ܵõ�����
    if ( pCharSkill != NULL )
    { pCharSkill->stSkillLevel = level; }//�õ��Ļ�����ô���ܵȼ��͸�ֵ��
    else
    {
        if ( !_SkillBag.AddSkill( iWhichSkill, level )  )
        { return false; }

        if ( IsRecipeSkill( iWhichSkill ) )//�����ǣ������ࡣ
        {
            GetCharInfo().baseinfo.liveinfo.nRecipeSkillNum++;

            _achieveManager.UpdateTriggerByValueType( EAT_RecipeSkill , iWhichSkill );
        }

        if ( IsCollectSkill( iWhichSkill ) )//�ʺϵ�˵�������ǲɼ���
        {
            _achieveManager.UpdateTriggerByValueType( EAT_RecipeSkill , iWhichSkill );
        }

        bIsNewSkill = true;
        pCharSkill  = _SkillBag.GetSkillByID(iWhichSkill);
    }

	//���������ܻ���ѧϰ����
    if ( pCharSkill)
    {
        if (bCheckSkillExp)
        {
            OperateJiaoZi  ( EOT_Sub, nMoneyNeed, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_LearnSkill);
            OperateSkillExp( EOT_Sub, nSkillExp , __FUNCTION__, __LINE__ );
        }

        MsgChangeSkill msg;
        msg.skill = *pCharSkill;
        msg.bMessageDialog = bMessageDialog;

        if ( bIsNewSkill )
        { msg.op    = MsgChangeSkill::OT_Add; }
        else
        { msg.op    = MsgChangeSkill::OT_Update; }

        //msg.nUnUsedExp = GetPlayerExpUnUsed();
        
        GettheServer().SendMsgToSingle( &msg, this );

        Log(theXmlString.GetString(eLog_info_2slk_82),pSkill->GetSkillName(), iWhichSkill);

        if ( bRecalc && pSkill->stGeneralType == ItemDefine::generaltype_passive )
        {
            ApplyPassiveSkillsToChar();
            RecalcBaseProperty( false,  BV_NotFullHp, BV_SendMessage, EWRP_Skill );
        }
    }

    return true;
}

bool GamePlayer::ForgetSkill( int iWhichSkill, bool bMessageDialog )
{ // ��������
    SCharSkill* pCharSkill = _SkillBag.GetSkillByID(iWhichSkill);
    if ( pCharSkill == NULL )
    { return false; }

    MsgChangeSkill msg;
    msg.op    = MsgChangeSkill::OT_Delete;
    msg.bMessageDialog = true;
    msg.skill = *pCharSkill;
    if( _SkillBag.RemoveSkill( iWhichSkill ) )
    {
        if ( IsRecipeSkill( iWhichSkill ) )
        {
            uint16 nRecipeType = theRecipeConfig.GetRecipeTypeBySkillId(iWhichSkill);
            _recipeManager.RemoveRecipeByType( nRecipeType );
            GetCharInfo().baseinfo.liveinfo.nRecipeSkillNum--;
        }

        if ( bMessageDialog )
        { GettheServer().SendMsgToSingle( &msg, this ); }
        
        return true;
    }
    return false;
}

bool GamePlayer::CanLearnXinFa( int nXinFaId, int nLevel )
{
    XinFaConfig::STalentXinFa* pXinFa = theXinFaConfig.GetXinFaByID( nXinFaId, nLevel );
    if( pXinFa == NULL )
    { return false; }

    if ( pXinFa->arrayProfessionReq[GetProfession()] )
    { return false; }

    int nLearnLevelReq  = pXinFa->nNeedLevel;
    int nMoneyNeed      = pXinFa->nNeedMoney;
    int nSkillExp       = pXinFa->nNeedExp;

    if (nLearnLevelReq > GetLevel())
    { return false; }

    if (nMoneyNeed > GetJiaoZiMoney() )
    { return false; }

    if (nSkillExp > GetSkillExpUnUsed())
    { return false; }

    return true;
}

bool GamePlayer::LearnXinFa   ( int iWhichXinFa, int nLevel, bool bCheckCondition, bool bMessageDialog )
{
    XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( iWhichXinFa, nLevel );
    if( pTalentXinFa == NULL )
    { return false; }

    if ( !pTalentXinFa->arrayProfessionReq[GetProfession()] )
    { 
        SendErrorToClient(ER_ProfessionToLearnXinFa);
        return false; 
    }

    SCharXinFa* pCurCharXinFa = _XinFaManager.GetXinFaByID( iWhichXinFa );

    int nLearnLevelReq  = pTalentXinFa->nNeedLevel;
    int nMoneyNeed      = pTalentXinFa->nNeedMoney;
    int nSkillExp       = pTalentXinFa->nNeedExp;

    if ( bCheckCondition )
    {
        if (pTalentXinFa->nPrevXinFa > 0)
        {
            if (_XinFaManager.GetXinFaByID(pTalentXinFa->nPrevXinFa) == NULL)
            {
                SendErrorToClient(ER_NoPrevXinFa);
                return false; 
            }
        }

        if ( pCurCharXinFa != NULL )
        {
            if (pCurCharXinFa->nXinFaLevel >= nLevel)
            {
                SendErrorToClient(ER_LearnXinFa);
                return false; 
            }

            if (pCurCharXinFa->nXinFaLevel != (nLevel - 1) )
            {
                SendErrorToClient(ER_LearnXinFa);
                return false; 
            }
        }

        if (nLearnLevelReq > GetLevel())
        { 
            SendErrorToClient(ER_NoLevelToLearnXinFa);
            return false; 
        }

        if (nMoneyNeed > GetJiaoZiMoney() )
        { 
            SendErrorToClient(ER_NoMoneyToLearnXinFa);
            return false; 
        }

        if (nSkillExp > GetPlayerExpUnUsed())
        { 
            SendErrorToClient(ER_NoExpToLearnXinFa);
            return false; 
        }
    }

    bool bAddSuccess = false;
    if ( nLevel == 1 )
    { bAddSuccess =  _XinFaManager.AddXinFa(iWhichXinFa, nLevel); }
    else
    {
        if( pCurCharXinFa == NULL )
        {
            SendErrorToClient(ER_LearnXinFa);
            return false; 
        }

        ++pCurCharXinFa->nXinFaLevel;
        bAddSuccess = true;

    }

    if ( bAddSuccess )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByID( iWhichXinFa );
        if(pCharXinFa == NULL)
        {
            SendErrorToClient(ER_LearnXinFa);
            return false; 
        }

        if ( bCheckCondition )
        {
            OperateJiaoZi  ( EOT_Sub, nMoneyNeed, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_LearnSkill);
			SetPlayerExpUnUsed(GetPlayerExpUnUsed()-nSkillExp);

			//LYH��־��� �ķ����ĵľ���
			theLogEventService.LogExp(GetAccountID(),GetDBCharacterID(),nSkillExp,0,ePlayerExp_TransSkill,GetCharName());
            //OperateSkillExp( EOT_Sub, nSkillExp , __FUNCTION__, __LINE__ );
        }

        MsgChangeXinFa msg;
		msg.header.stID = GetID();
        msg.xinfa       = *pCharXinFa;
        msg.nUnUsedExp  = GetPlayerExpUnUsed();

        if (pCharXinFa->nXinFaLevel == 1)
        { msg.op = MsgChangeXinFa::OT_Add; }
        else
        { msg.op = MsgChangeXinFa::OT_Update; }

        GettheServer().SendMsgToSingle( &msg, this);

        for (int i = 0;i < XinFaConfig::EXCD_SkillMaxCount; ++i)
        {
            XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkill(i);
            if (pXinFaSkill == NULL)
            { continue; }

            if (pXinFaSkill->nLevel != 0)
            {
                LearnSkill( pXinFaSkill->nId, pXinFaSkill->nLevel, false, true );
            }
        }

        ApplyTalentXinFaToChar  ();
        UpdateCharAllAttibute   ();
        SendCharAttibuteToClient();

        return true;
    }

    return false;
}

bool GamePlayer::ForgetXinFa  ( int iWhichXinFa )
{
    SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByID( iWhichXinFa );
    if( pCharXinFa == NULL )
    { return false; }

    XinFaConfig::STalentXinFa* pXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
    if( pXinFa == NULL )
    { return false; }

    SCharXinFa xinfa = *pCharXinFa;

    if ( !_XinFaManager.RemoveXinFa( iWhichXinFa ) )
    { return false; }
    
    MsgChangeXinFa msg;
    msg.xinfa       = xinfa ;
    msg.nUnUsedExp  = GetSkillExpUnUsed();
    msg.op          = MsgChangeXinFa::OT_Delete;
    GettheServer().SendMsgToSingle( &msg, this );

    for (int i=0;i<XinFaConfig::EXCD_SkillMaxCount;++i)
    {
        XinFaConfig::SXinFaSkill* pSkill = pXinFa->GetXinFaSkill( i );
        if ( pSkill == NULL )
        { continue; }

        SCharSkill *pCharSkill = _SkillBag.GetSkillByID(pSkill->nId);
        if ( pCharSkill == NULL )
        { continue; }

        ForgetSkill( pCharSkill->ustSkillID );
    }

    return true;
}

void GamePlayer::GetXinFaSkillEffect( uint16 nSkillId, OUT int* pSkillAttr )
{
    if ( pSkillAttr == NULL )
    { return; }

    for (int i=0; i < _XinFaManager.GetXinFaNum(); ++i )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex(i);
        if (pCharXinFa == NULL)
        { break; }

        XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
        if (pCharXinFa == NULL)
        { continue; }

        XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkillByID( nSkillId );
        if ( pXinFaSkill != NULL)
        {  
            for (int i=0;i<XinFaConfig::EXCD_EffectSkillAttr;++i)
            {
                pSkillAttr[pXinFaSkill->attrType[i]] = pXinFaSkill->attrValue[i];
            }
        }
    }

    return;
}


void GamePlayer::GetXinFaSkillEffect( const ItemDefine::SItemSkill* pSkill, OUT int* pSkillAttr )
{
    if ( pSkill == NULL || pSkillAttr == NULL )
    { return; }

    for (int i=0; i < _XinFaManager.GetXinFaNum(); ++i )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex(i);
        if (pCharXinFa == NULL)
        { break; }

        XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
        if (pCharXinFa == NULL)
        { continue; }

        XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkillByID( pSkill->ustItemID );
        if ( pXinFaSkill != NULL)
        {  
            for (int i=0;i<XinFaConfig::EXCD_EffectSkillAttr;++i)
            {
                pSkillAttr[pXinFaSkill->attrType[i]] = pXinFaSkill->attrValue[i];
            }
        }
    }

    return;
}

int GamePlayer::GetXinFaSkillEffectValue( uint16 nSkillId, int attrType )
{
    for (int i=0; i < _XinFaManager.GetXinFaNum(); ++i )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex(i);
        if (pCharXinFa == NULL)
        { break; }

        XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
        if (pCharXinFa == NULL)
        { continue; }

        XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkillByID( nSkillId );
        if ( pXinFaSkill != NULL)
        {  
            for (int i=0;i<XinFaConfig::EXCD_EffectSkillAttr;++i)
            {
                if (pXinFaSkill->attrType[i] == attrType)
                {
                    return pXinFaSkill->attrValue[i];
                }
            }
        }
    }

    return 0;
}

int GamePlayer::GetXinFaSkillEffectValue( const ItemDefine::SItemSkill* pSkill, int attrType )
{
    if ( pSkill == NULL )
    { return 0; }

    for (int i=0; i < _XinFaManager.GetXinFaNum(); ++i )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex(i);
        if (pCharXinFa == NULL)
        { break; }

        XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );
        if (pCharXinFa == NULL)
        { continue; }

        XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkillByID( pSkill->ustItemID );
        if ( pXinFaSkill != NULL)
        {  
            for (int i=0;i<XinFaConfig::EXCD_EffectSkillAttr;++i)
            {
                if (pXinFaSkill->attrType[i] == attrType)
                {
                    return pXinFaSkill->attrValue[i];
                }
            }
        }
    }

    return 0;
}

void GamePlayer::ApplyPassiveSkillToChar( const ItemDefine::SItemSkill* pSkill )
{
    if ( NULL == pSkill )
    { return; }

    short shPassiveSkillTarget = pSkill->shPassiveSkillTarget;

    if( !(shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_Self ||
        shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndAllPet ||
        shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndTargetPet) )
    { return; }

    // 1������״̬��Ϊ2������״̬
    for (int i = 0;i < ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize; ++i )
    {
        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pSkill->ustMeAddStatusID[i], pSkill->ustMeAddStatusLevel[i] );
        if( pStatus == NULL )
        { return; }

        // ����һ������
        int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;
        GetXinFaSkillEffect( pSkill, nXinFaSkillAttr )  ;

        GetBaseAttr( EBaseAttr_Strength )->skill    += pStatus->stAddBaseAttr[EBaseAttr_Strength] + nXinFaSkillAttr[SkillAttr_Strength]; 
        GetBaseAttr( EBaseAttr_Strength )->skillPer += pStatus->stAddBaseAttrPer[EBaseAttr_Strength];

        GetBaseAttr( EBaseAttr_Agility )->skill    += pStatus->stAddBaseAttr[EBaseAttr_Agility]   + nXinFaSkillAttr[SkillAttr_Agility] ;
        GetBaseAttr( EBaseAttr_Agility )->skillPer += pStatus->stAddBaseAttrPer[EBaseAttr_Agility];

        GetBaseAttr( EBaseAttr_Stamina )->skill    += pStatus->stAddBaseAttr[EBaseAttr_Stamina]   + nXinFaSkillAttr[SkillAttr_Stamina] ;
        GetBaseAttr( EBaseAttr_Stamina )->skillPer += pStatus->stAddBaseAttrPer[EBaseAttr_Stamina];

        GetBaseAttr( EBaseAttr_Intelligence )->skill    += pStatus->stAddBaseAttr[EBaseAttr_Intelligence] + nXinFaSkillAttr[SkillAttr_Intelligence]; 
        GetBaseAttr( EBaseAttr_Intelligence )->skillPer += pStatus->stAddBaseAttrPer[EBaseAttr_Intelligence];

        // ���ö�������
        GetCharFightAttr()->moveSpeed.skill        += pStatus->fMoveSpeedChanged;                      // �ƶ��ٶ�
        GetCharFightAttr()->attackSpeed.skillPer   += pStatus->fAttSpeedPer;                           // �����ٶ�
        GetCharFightAttr()->attackPhysics.skill    += pStatus->changePhyAttack + nXinFaSkillAttr[SkillAttr_PhysicsAttack]; // ��������
        GetCharFightAttr()->attackPhysics.skillPer += pStatus->changePhyAttackPer;                                         // ��������%
        GetCharFightAttr()->attackMagic.skill      += pStatus->changeMagAttack + nXinFaSkillAttr[SkillAttr_MagicAttack];   // ����������
        GetCharFightAttr()->attackMagic.skillPer   += pStatus->changeMagAttackPer;                                         // ����������%
        GetCharFightAttr()->defendPhysics.skill    += pStatus->changeDefend[EDefendType_Physical] + nXinFaSkillAttr[SkillAttr_PhysicsDefend]; // ��� 
        //GetCharFightAttr()->defendLong .skill    += pStatus->changeDefend[EDefendType_Long];         // Զ��
        GetCharFightAttr()->defendMagic.skill      += pStatus->changeDefend[EDefendType_Magic]    + nXinFaSkillAttr[SkillAttr_MagicDefend];   // ħ��
        GetCharFightAttr()->defendPhysics.skillPer += pStatus->changeDefendPer[EDefendType_Physical];  // ����%
        //GetCharFightAttr()->defendLong .skillPer += pStatus->changeDefendPer[EDefendType_Long];      // Զ��%
        GetCharFightAttr()->defendMagic.skillPer   += pStatus->changeDefendPer[EDefendType_Magic];     // ħ��%
        GetCharFightAttr()->hpRestore.skill        += pStatus->resumeHP;                               // ��ɫHP�ָ��ٶȸı�
        GetCharFightAttr()->hpRestore.skillPer     += pStatus->resumeHPPer;                            // ��ɫHP�ָ��ٶȸı�%
        GetCharFightAttr()->mpRestore.skill        += pStatus->resumeMP;                               // ���MP�ָ��ٶȸı�
        GetCharFightAttr()->mpRestore.skillPer     += pStatus->resumeMPPer;                            // ���MP�ָ��ٶȸı�%
        GetCharFightAttr()->hpMax.skill            += pStatus->stChanged_HPMax + nXinFaSkillAttr[SkillAttr_AddHPMax];// Ѫ�����ֵ
        GetCharFightAttr()->hpMax.skillPer         += pStatus->changeHPMaxPer ;// Ѫ�����ֵ%
        GetCharFightAttr()->mpMax.skill            += pStatus->stChanged_MPMax + nXinFaSkillAttr[SkillAttr_AddMPMax];// �������ֵ
        GetCharFightAttr()->mpMax.skillPer         += pStatus->changeMPMaxPer;                         // �������ֵ%
        GetCharFightAttr()->dodge.skill            += pStatus->stChanged_Hedge  + nXinFaSkillAttr[SkillAttr_Dodge];     // �ı�����
        GetCharFightAttr()->exact.skill            += pStatus->stChanged_Hit    + nXinFaSkillAttr[SkillAttr_Exact ];     // ����
        GetCharFightAttr()->critical.skill         += pStatus->changed_Critical + nXinFaSkillAttr[SkillAttr_Critical];     // ������
        GetCharFightAttr()->tenacity.skill         += pStatus->changeTenacity   + nXinFaSkillAttr[SkillAttr_Tenacity];     // ����
        GetCharFightAttr()->criticalIntensity.skill+= pStatus->changed_CriticalIntensity + nXinFaSkillAttr[SkillAttr_CriticalIntensity] ; // �����˺�

        if (pStatus->addEquipAttrType > 0)
        { ApplyPassiveSkillToCharEquip( pSkill ); }
    }
}

void GamePlayer::ApplyPassiveSkillToCharEquip( const ItemDefine::SItemSkill* pSkill )
{
    if ( NULL == pSkill )
    { return; }

    short shPassiveSkillTarget = pSkill->shPassiveSkillTarget;

    if( !(shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_Self ||
        shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndAllPet ||
        shPassiveSkillTarget == ItemDefine::PassiveSkillTarget_SelfAndTargetPet) )
    { return; }

    int nPhysicsAttack  = 0;
    int nMagicAttack    = 0;
    int nPhysicsDefend  = 0;
    int nMagicDefend    = 0;
    for(int i=0; i<EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pItem = GetVisualEquipItem( i );
        if ( NULL == pItem)
        { continue; }

        // ��Ҫɾ���������ζ���
        if( pItem->equipdata.usHP<=0 )
        { continue; }

        if ( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->GetItemGuid() == 0 )
        { continue; }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( pItemCommon == NULL ||  !pItemCommon->IsCanEquip() )
        { continue; }

        ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip* )pItemCommon;
        if( pItemCanEquip == NULL )
        { continue; }

        if ( pItemCanEquip->bFashion && pItem->IsOverdue() )
        { continue; }       // �Ѿ������˵�ʱװ

        if( pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
        {
            ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon* )pItemCommon;
            nPhysicsAttack += pItemWeapon->attackPhysics;
            nMagicAttack   += pItemWeapon->attackMagic;
        }
        else
        {
            ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour* )pItemCommon;
            nPhysicsDefend += pItemArmour->defendPhysics;
            nMagicDefend   += pItemArmour->defendMagic;
        }
    }

    for (int i = 0;i < ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize; ++i )
    {
        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pSkill->ustMeAddStatusID[i], pSkill->ustMeAddStatusLevel[i] );
        if( pStatus == NULL )
        { return; }

        if (pStatus->addEquipAttrType > 0)
        {
            switch (pStatus->addEquipAttrType)
            {
            case RT_AddPhysicsAttack:
                {
                    GetCharFightAttr()->attackPhysics.skill  += nPhysicsAttack * pStatus->addEquipAttrValuePer * DEF_PERCENT;
                }
                break;
            case RT_AddMagicAttack:
                {
                    GetCharFightAttr()->attackMagic.skill    += nMagicAttack * pStatus->addEquipAttrValuePer * DEF_PERCENT;
                }
                break;
            case RT_AddPhysicsDefend:
                {
                    GetCharFightAttr()->defendPhysics.skill  += nPhysicsDefend * pStatus->addEquipAttrValuePer * DEF_PERCENT;
                }
                break;
            case RT_AddMagicDefend:
                {
                    GetCharFightAttr()->defendMagic.skill    += nMagicDefend * pStatus->addEquipAttrValuePer * DEF_PERCENT;
                }
                break;
            default:
                break;
            }
        }
    }
}

void GamePlayer::ApplyTalentXinFaToChar()
{
    // �����������
    ClearAllFightAttrByPart( ECustomDataPart_xinfa );

    for( int iLoop=0; iLoop< _XinFaManager.GetXinFaNum() ; ++iLoop )
    {
        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex( iLoop );        
        if ( !pCharXinFa )
        { continue; }

        if (pCharXinFa->nXinFaID == InvalidLogicNumber || pCharXinFa->nXinFaLevel == 0)
        { continue; }

        XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel );              
        if( !pTalentXinFa )
        { continue; }

        for (int i = 0; i < XinFaConfig::EXCD_EffectCharAttrMax; ++i)
        {
            ApplyAttrTypeToChar( pTalentXinFa->charAttrType[i], ECustomDataPart_xinfa, pTalentXinFa->charAttrValue[i] );
        }
    }
}

void GamePlayer::ApplyPassiveSkillsToChar()
{
    // ���һ������
    ClearAllBaseAttrByPart ( ECustomDataPart_skill );

    // �����������
    ClearAllFightAttrByPart( ECustomDataPart_skill );

    // �����������ۼ�
    for( int iLoop=0; iLoop<_SkillBag.GetSkillNum(); ++iLoop )
    {
        SCharSkill* pCharSkill = _SkillBag.GetSkillByIndex( iLoop );        
        if ( !pCharSkill )
        { continue; }

        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );                
        if(!pSkill)
        { continue; }

        if ( pSkill->stGeneralType != ItemDefine::generaltype_passive )
        { // ������Ǳ�������
            continue;
        }

        if ( !pSkill->bNeedWeapon )
        { // ����Ҫ����
            ApplyPassiveSkillToChar( pSkill );
            continue;
        }

        // ��Ҫ����
        SCharItem* pCharItem = GetVisualEquipItem( EEquipPartType_Weapon );
        if ( NULL == pCharItem)
        { continue; }

        ItemDefine::SItemCommon* pItemWeaponCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
        if ( NULL == pItemWeaponCommon || pItemWeaponCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
        { continue; }

        ItemDefine::SItemWeapon* pItemWeaponRhand = (ItemDefine::SItemWeapon*)pItemWeaponCommon;
        if ( NULL == pItemWeaponRhand )
        { continue; }

        if ( pSkill->stWeaponNeed == -1 || pSkill->stWeaponNeed == pItemWeaponRhand->stWeaponType )
        { ApplyPassiveSkillToChar( pSkill ); }
    }

    // һ���������ö�������
    ApplyBaseAttrToFightAttr( true, ECustomDataPart_skill );
}
