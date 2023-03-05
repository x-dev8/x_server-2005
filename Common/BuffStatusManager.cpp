#include "BuffStatusManager.h"
#include "FuncPerformanceLog.h"
#include "TimeEx.h"
#include "XmlStringLanguage.h"
#include "ItemDetail.h"

BuffStatusManager::BuffStatusManager()
{
    pBuffEvent = NULL;
    m_pstBodyStatus  = NULL;
    buffMaxCount   = 0;
    iEnableStatusNum = 0;          
    //iChangeSight = -1;
    bMoveFlag = true;              
    bUsePhysicsSkillFlag = true;   
    bUseMagicSkillFlag = true;
    bIsBePhyAttack = true;
    bIsBeMagAttack = true;
    bHide = false;                 
    bUseItemFlag = true;                        
    bCanBeFindByMonster = true;    
    bAttackByMonsterFirst = false; 
    bClearStatusInAttack = false;  
    bAttackClearStatus = false;    
    bIsWeaponFormula = true;
	bBuoy           = false;
	bCanRide		= true;
	IsCanGetHonour	= true;
	IsCanBeGetHonour= true;

    fDamage2MpRatioPer = 0;        
    iDamage2MpRatio = 0;

    fDamageReflectRatio      = 0.0f;
    nDamageReflectProability = 0;

    iDamageChengedRate = 0;        
    fDamageChengedRatePer = 0;

    fSuckHpRate      = 0;
    nSuckHpValue     = 0;
    nSuckHpProbability = 0;
    fMPStolenRate = 0;
    iMPStolenVal  = 0;

    nChangeMonsterID = 0;

    bHedgeNull = false;

    for(int idx = 0; idx<eElement_Max; idx++ )
    {
        stChangedSkill_Hurt[idx] = 0;
        stChangedSkill_HurtPer[idx] = 0;
    }
    
    stStatusFree         = false;  //  ״̬����
    stChangedPhy_Hurt    = 0;
    stChangedPhy_HurtPer = 0;
    stSuckMax            = 0;
    hurtImmunity         = 0;

    //changeActivityMax    = 0;
    //activityMul          = 0;

    //m_ClearBodyStatus = NULL;
    for (int np = 0 ; np < BodyStatusType_Max;np ++)
    {
        m_nStatusClear[np] = 0;
        memset(&m_ClearBodyStatus[np],0,sizeof(SCharBuff));
    }

    stAddBufferID    = -1;
    stAddBufferLevel = -1;
    bAddDeBuffer     = false;
    bCsedAddBuffer   = false;    
    fExpMulAdd       = 0.0f;
    fSkillExpMulAdd  = 0.0f;
    fExpMulAddByEquip= 0.0f;
    nCurStatusAnim   = eStatusAnim_None;
    //fAddIntonateRate = 0.0f;
    memset( nAddBaseAttr, 0, sizeof(nAddBaseAttr));
    memset( nAddBaseAttrPer, 0, sizeof(nAddBaseAttrPer));
    //memset( nAddMountBaseAttr, 0, sizeof(nAddMountBaseAttr));
    //memset( nAddMountBaseAttrPer, 0, sizeof(nAddMountBaseAttrPer));
    //stComposeOdds   = 0;
    //stIntensifyOdds = 0;

    //bNeedCalcDailyPkValue = TRUE;

    bIsRandRun                    = false;
    bIsPetSupport                 = false;

    _nBackAttackDispelBuffCount = 0;
    _nMoveDispelBuffCount       = 0;
    
    for ( int i=0; i<SNT_MaxCount; ++i)
    {
        _fStatusLimitResistRatio[i] = 0.0f;
    }

    _bNextNotIntonate = false;
    nNextNotIntonateNum = 0  ;

    _timeExpMul       = 0.0f;
    bInvincible       = false;
    damagetohp        = 0;
    _bDisableCallGraphic = false;
    ifConsumeEnergy   = false;

    //reduceTax           = 0;
    deathDurabilityPer  = 0;
    deathMountHPDropPer = 0;

    addCatchPetRate     = 0;

    addMoney            = 0;
    addReputation       = 0;
    addExploit          = 0;
    addHonour           = 0;
    addMasterValue      = 0;
    addBattleScore      = 0;
    reputationMul       = 0;
    exploitMul          = 0;
    honourMul           = 0;
    masterValueMul      = 0;
    battleScoreMul      = 0;
    addHonourLimit      = 0;
	BeDamagePerHpMax	= 0;

    memset( _buffChangeRecord, 0, sizeof(_buffChangeRecord));

    memset( changeSkillIds, 0, sizeof(changeSkillIds));
    memset( changeSkillTimes, 0, sizeof(changeSkillTimes));
}

BuffStatusManager::~BuffStatusManager()
{
}

void BuffStatusManager::CreateFromData(SCharBuff* pData, int num)
{
    m_pstBodyStatus = pData; //�����������е�״̬,��¼����
    buffMaxCount = num;    //��Ŀ
}

void BuffStatusManager::CreateFromData(BuffEvent* pEvent, SCharBuff* pData, int num)
{
    pBuffEvent = pEvent;
    m_pstBodyStatus = pData;  
    buffMaxCount = num;    
}

bool BuffStatusManager::ApplyBuff( bool bStop, uint16 buffId, uint16 buffLevel, GameObjectId masterId, uint32 dwNowTime, bool bLastOne, uint32 dwDurationTime,uint32 dwMasterDbId, int eventType, int eventValue )
{
    if ( buffLevel < 0)
    { buffLevel = 0; }

    if ( buffLevel > ItemDefine::MaxLevel_Status - 1 )
    { buffLevel = ItemDefine::MaxLevel_Status - 1; }

    if ( buffId < 0)
    { buffId = 0; }

    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    ItemDefine::SItemStatus* pNewStatusConfig = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus( buffId, buffLevel );
    if ( pNewStatusConfig == NULL )
    { 
        Log( 1, buffId, buffLevel);
        return false; 
    }

    // �ж�ʱ������
    if ( pNewStatusConfig->stActualTime<=0 && pNewStatusConfig->iDurationTime<=0 && !pNewStatusConfig->IsForeverStatus() && dwDurationTime == 0 )
    { return false; }
    
    if ( dwDurationTime == 0 )
    { // ����ʱ��
        if (pNewStatusConfig->stActualTime > 0)
        { dwDurationTime = pNewStatusConfig->stActualTime * 60 * 60 * 1000; }
        else
        { dwDurationTime = pNewStatusConfig->iDurationTime; }
    }

    // �ж�������Ч��
    if ( pNewStatusConfig->stType < 0 )
    { 
        Log( 2, buffId, buffLevel);
        return false; 
    }


    bool bResult    = false;    
    int  nStatusPos = -1;
    int  nStatusNum = 0;
    ItemDefine::SItemStatus* pStatusOld = NULL;
    SCharBuff* pLastCharBuff = NULL;
    // ͨ��״̬�����ж���û����ͬ������״̬ �� �õ��м�����ͬ��
    for ( int n=0; n<buffMaxCount; ++n)
    {
        // ���buff �ж�����
        SCharBuff* pCharBuff = GetBuff( n );
        if ( pCharBuff == NULL)
        { continue; }

        pStatusOld = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatusOld == NULL )
        { continue; }

        // ���Ͳ�ͬ
        if ( pNewStatusConfig->stType != pStatusOld->stType)
        { continue; }

        // ������ͬ
        ++nStatusNum;

        // ����λ
        if ( nStatusNum == 1)
        { 
            nStatusPos = n; 
            pLastCharBuff = pCharBuff;
        }
        else
        { // �滻����ʱ����̵�״̬
            if ( pCharBuff->dwDurationTime < pLastCharBuff->dwDurationTime)
            { nStatusPos = n; }
        }
    }
    
    pStatusOld = NULL;
    pLastCharBuff = NULL;
    // �п����λ��
    if ( nStatusPos >= 0 )
    { // ����ͬ������״̬
        // �ж��Ƿ���ظ�
        if ( pNewStatusConfig->bIsCanCong )
        { 
            if ( nStatusNum < pNewStatusConfig->nSuperpositionCount )
            { // �ظ���û�����
                for ( int i=0; i<buffMaxCount; ++i)
                {
                    SCharBuff* pCharBuff = GetBuff( i );

                    // ���ھͼ�������Ҫ�ҵ���λ
                    if ( pCharBuff != NULL ) 
                    { continue; } 

                    // �п�λ
                    bResult = AddBuff( i, bStop, buffId, buffLevel, masterId, dwNowTime, bLastOne, dwDurationTime, dwMasterDbId, eventType, eventValue);
                    if ( !bResult )
                    { break; }

                    ++iEnableStatusNum;
                    //if (pNewStatusConfig->stMagicShield > -1)
                    //{ ClearSuckDamage(); }
                    break;
                }
            }
            else
            { // �ظ��������
                SCharBuff* pCharBuff = GetBuff( nStatusPos );
                if ( pCharBuff == NULL )
                { 
                    Log( 3, buffId, buffLevel);
                    goto ApplyBuffFinal; 
                }

                pStatusOld = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
                if ( pStatusOld == NULL )
                { 
                    Log( 4, buffId, buffLevel);
                    goto ApplyBuffFinal; 
                }
                
                // �ҵ�����
                bResult = AddBuff( nStatusPos, bStop, buffId,buffLevel,masterId, dwNowTime,bLastOne,dwDurationTime,dwMasterDbId, eventType, eventValue);
                if ( !bResult )
                { 
                    Log( 5, buffId, buffLevel);
                    goto ApplyBuffFinal; 
                }

                //// �����buffħ����Ч��
                //if ( pStatusOld->stMagicShield > -1 )
                //{ ClearSuckDamage(); }

                //// �����buffħ����Ч��
                //if ( pNewStatusConfig->stMagicShield > -1 )
                //{ ClearSuckDamage(); }
            }
        }
        else
        { // �������ظ�            
            nStatusPos = -1; // �����ظ��������ȼ�����
            pStatusOld = NULL;
            // �Ƚ���ͬ����״̬�����ȼ� ��λ�ø���
            for (int i=0; i<buffMaxCount; ++i)
            {
                SCharBuff* pCharBuff = GetBuff( i );
                if ( pCharBuff == NULL)
                { continue; }

                pStatusOld = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
                if ( pStatusOld == NULL )
                { continue; }
                
                // �ж�����
                if ( pNewStatusConfig->stType != pStatusOld->stType )
                { continue; }

                if (pNewStatusConfig->ustItemID != pStatusOld->ustItemID)
                {// �������һ����״̬�������ȼ����滻
                    if ( pNewStatusConfig->stPriority >= pStatusOld->stPriority)
                    {
                        nStatusPos = i;
                        break;
                    }
                }
                else
                {// �����һ����״̬���յȼ����滻
                    if ( pNewStatusConfig->ustLevel >= pStatusOld->ustLevel )
                    {
                        nStatusPos = i;
                        break;
                    }
                }
            }

            if ( nStatusPos >= 0)
            { // �ҵ���
                bResult = AddBuff( nStatusPos, bStop, buffId, buffLevel, masterId, dwNowTime, bLastOne, dwDurationTime, dwMasterDbId, eventType, eventValue );
                if ( !bResult )
                { 
                    Log( 6, buffId, buffLevel);
                    goto ApplyBuffFinal; 
                }

                //if ( pStatusOld->stMagicShield > -1 )
                //{ ClearSuckDamage(); }

                //if ( pNewStatusConfig->stMagicShield > -1 )
                //{ ClearSuckDamage(); }
            }
        }
    }
    else
    { // û����ͬ������״̬
        for ( int i=0; i<buffMaxCount; ++i)
        {
            // �ҿ�λ
            SCharBuff* pCharBuff = GetBuff( i );
            if ( pCharBuff != NULL) // ��ֵ��ʾ���λ���Ѿ�ʹ��
            { continue; }

            // �ҵ���λ
            bResult = AddBuff( i, bStop, buffId, buffLevel, masterId, dwNowTime, bLastOne, dwDurationTime, dwMasterDbId, eventType, eventValue );
            if ( !bResult )
            { break; }

            ++iEnableStatusNum;
            //if (pNewStatusConfig->stMagicShield > -1)
            //{ ClearSuckDamage(); }
            break;
        }
    }

ApplyBuffFinal:
    // ����ɫ��״̬��ֵ
    if ( bResult )
    { UpdateEffect(); }

    return bResult;
}

bool BuffStatusManager::AddBuff( int16 nPos, bool bStop, uint16 iStatusId, int iStatusLevel, GameObjectId masterId, uint32 dwNowTime,bool bLastOne,uint32 dwDurationTime,uint32 dwMasterDBID, int eventType, int eventValue)
{
    ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatus( iStatusId, iStatusLevel );
    if ( pStatusConfig == NULL )
    { return false; }

    SCharBuff* pCharBuffAddress = GetBuffAddress( nPos );
    if ( pCharBuffAddress == NULL )
    { return false; }

    pCharBuffAddress->dwPreDamage    = HQ_TimeGetTime();             // ��¼�ϴ��˺���ʱ��.����״̬�ӳٽ���
    pCharBuffAddress->dwStartTime    = dwNowTime;                    // ��¼��ʼ��ʱ��
    pCharBuffAddress->StatusID       = iStatusId;                    // ״̬���
    pCharBuffAddress->iLevel         = iStatusLevel;                 // ״̬�ȼ�
    pCharBuffAddress->bLastEffect    = bLastOne;                     // �Ƿ�����ͷŵ���Ч
    pCharBuffAddress->masterId       = masterId;                     // ��״̬���ͷ���
    pCharBuffAddress->restoreType    = pStatusConfig->restoreType;
    pCharBuffAddress->dwPlayerDBID   = dwMasterDBID;
    pCharBuffAddress->bStop          = bStop;
    pCharBuffAddress->dwDurationTime = dwDurationTime;
    pCharBuffAddress->eventType      = eventType;
    pCharBuffAddress->eventValue     = eventValue;
    pCharBuffAddress->lapoverNum     += pStatusConfig->lapoverValue;   // ���Ӵ���

    if ( pCharBuffAddress->lapoverNum > pStatusConfig->lapoverNum )
    { pCharBuffAddress->lapoverNum = pStatusConfig->lapoverNum; }

    if ( pStatusConfig->iBalanceDelayTime > 0)
    { // ������ʱ��׷���Ż� ��֤ ���� 6000ms ÿ1000ms��һ�� ���ܵ���
        uint32 count = pCharBuffAddress->dwDurationTime / pStatusConfig->iBalanceDelayTime;
        pCharBuffAddress->dwDurationTime += count * 10;
    }
    
    if ( pStatusConfig->stActualTime > 0 )
    {
        uint32 dwTime = dwDurationTime / 1000;
        TimeSpan timespan( dwTime );
        TimeEx DestTime = TimeEx::GetCurrentTime() + timespan;
        pCharBuffAddress->nInt64StartTime = DestTime.GetTime();
    }

    OnBuffHaveChanged( nPos );
    return true;
}

bool BuffStatusManager::UpdateDurationTime()
{
    uint32 currentTime = HQ_TimeGetTime();

    bool bHaveChanged = false;

    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff(i);
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( NULL == pStatusConfig )
        { continue; }

        //������������ֱ�����״̬
        if (pStatusConfig->ifStatusIntonate)
        {
            if ( nNextNotIntonateNum == 0)
            {
                ClearBuff( i , false );
                bHaveChanged = true;
                goto UpdateProcessFinal;
            }
        }

        if ( pStatusConfig->stActualTime <= 0)
        { // ������ʵ����ʱ��
            if ( pCharBuff->bStop || pStatusConfig->IsForeverStatus() )
            { continue; }   // ֹͣ ���� ������Buffer״̬

            uint32 dwPassTime = currentTime - pCharBuff->dwStartTime;
            if ( dwPassTime >= pCharBuff->dwDurationTime )
            {
                //if ( pStatusConfig->stMagicShield > -1)
                //{ ClearSuckDamage(); } // ���ħ����Ч��
                
                //ʱ�䵽������������״̬
                if (pStatusConfig->ifStatusIntonate)
                {
                    _bNextNotIntonate   = false;
                    nNextNotIntonateNum = 0;
                }

                ClearBuff( i , false );
                //���Ŀ��״̬������
                bHaveChanged = true;
            }
            else
            {
                pCharBuff->dwStartTime     = HQ_TimeGetTime();
                pCharBuff->dwDurationTime -= dwPassTime;
            }
        }
        else
        { // ��ʵʱ��
            TimeEx StatusTime(pCharBuff->nInt64StartTime);
            if (StatusTime <= TimeEx::GetCurrentTime())
            {
                ClearBuff( i, false );
                bHaveChanged = true;
            }
            else
            {
                TimeEx xEndTime( pCharBuff->nInt64StartTime );
                TimeSpan xTimeSpan = xEndTime - TimeEx::GetCurrentTime();
                pCharBuff->dwDurationTime = xTimeSpan.GetTotalSeconds()*1000;
            }
        }
    }

UpdateProcessFinal:
    if ( bHaveChanged )
    { UpdateEffect(); }

    return bHaveChanged;
}

bool BuffStatusManager::UpdateBufferOnEnterStage( DWORD stageId )
{
    bool  bChangeFlag = false;
    DWORD dwTime      = HQ_TimeGetTime();

    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }
        
        ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatus( pCharBuff->StatusID,pCharBuff->iLevel);
        if ( NULL == pStatusConfig)
        { continue; }

        if ( pStatusConfig->actionMapConfigId == InvalidLogicNumber )
        { continue; }

        bool bNeedStop = pStatusConfig->actionMapConfigId != EctypeId2MapId( stageId );

        if ( bNeedStop )
        { // ��Ҫֹͣ
            if ( pCharBuff->bStop )
            { continue; }
            else
            {
                if ( pStatusConfig->stActualTime <= 0 )
                { // ��Ϸ����ʱʱ��
                    uint32 dwPassTime = dwTime - pCharBuff->dwStartTime;
                    if ( dwPassTime >= pCharBuff->dwDurationTime )
                    {
                        //if ( pStatusConfig->stMagicShield > -1)
                        //{ ClearSuckDamage(); } // ���ħ����Ч��

                        ClearBuff( i );
                    }
                    else
                    {
                        pCharBuff->dwStartTime     = dwTime;
                        pCharBuff->dwDurationTime -= dwPassTime;
                        pCharBuff->dwPreDamage     = dwTime;
                        pCharBuff->bStop           = true;
                        OnBuffHaveChanged( i );
                    }
                    bChangeFlag = true;
                }
            } // pCharBuff->bStop
        }
        else
        { // ����Ҫֹͣ
            if ( !pCharBuff->bStop )
            { continue; }
            else
            {
                if ( pStatusConfig->stActualTime <= 0 )
                { // ��Ϸ����ʱʱ��
                    pCharBuff->dwStartTime     = dwTime;                    
                    pCharBuff->bStop           = false ;
                    OnBuffHaveChanged( i );
                    bChangeFlag = true;
                }
            }
        } // bNeedStop
    } // for(int i=0; i<iBodyStatusNum; ++i)

    return bChangeFlag;
}

bool BuffStatusManager::UpdateCounterValue()
{
    bool bIsClear = false;

    if (buffMaxCount > BodyStatusType_Max )
    { buffMaxCount = BodyStatusType_Max; }

    for(int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );        
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        // ���������˺��Ķ�
        if ( pStatus->stMagicShield == 0 && pStatus->hurtImmunity == 0 )
        { continue; }

        if ( pStatus->stMagicShield != 0 )
        {
            int nSuckMax = GetSuckDamgeMax();   
            int nSuckMaxPer = GetSuckDamgePer();

            if ( nSuckMax <= 0 && nSuckMaxPer <= 0)
            { 
                ClearBuff( i, false ); 
                bIsClear = true;
            }
        }
        else if ( pStatus->hurtImmunity > 0 )
        {
            if ( GetHurtImmunity() == 0 )
            {
                ClearBuff( i, false ); 
                bIsClear = true;
            }
        }
        
    }

	if ( bIsClear )
	{ UpdateEffect(); }

    return bIsClear;
}

bool BuffStatusManager::UpdateOnAttack()
{
    bool bClearFlag = false;

    for ( int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }
        
        ItemDefine::SItemStatus *pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
        if ( pStatus == NULL )
        { continue; }

        // �ж��Ƿ�����Ҫ������ɾ����
        if ( !pStatus->bAttckNoStatus )
        { continue; }

        ClearBuff( i, false );
        bClearFlag = true;
    }
    
    if ( bClearFlag )
    { UpdateEffect(); }

    return bClearFlag;
}

bool BuffStatusManager::UpdateOnBeAttack( const ItemDefine::SItemSkill* pSkillConfig )
{
    bool bClearFlag = false;

    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }
    
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
        if ( pStatus == NULL )
        { continue; }

        if ( pStatus->bAttckedNoStatus && pStatus->stMagicShield == 0 && pSkillConfig->sSkillCategory == ItemDefine::SCT_Attack)
        {
            // ���Ŀ��״̬������
            ClearBuff( i, false );
            bClearFlag = true;
        }
        
        if ( pStatus->stMagicShield != 0 )
        {
            int nSuckMax = GetSuckDamgeMax();   
            int nSuckMaxPer = GetSuckDamgePer();

            if ( nSuckMax <= 0 && nSuckMaxPer <= 0)
            {
                //���Ŀ��״̬������
                ClearBuff( i, false );
                bClearFlag = true;
            }
        }
    }

    if (bClearFlag)
    { UpdateEffect(); }

    return bClearFlag;
}

bool BuffStatusManager::UpdateOnBackAttack()
{
    bool bClearFlag = false;

    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }
    
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff = NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        if ( !pStatus->bBackAttckedDispel )
        { continue; }

        // ���Ŀ��״̬������
        ClearBuff( i, false );
        
        bClearFlag = true;

        if ( _nBackAttackDispelBuffCount > 0 )
        { --_nBackAttackDispelBuffCount; }
    }

    if ( bClearFlag )
    { UpdateEffect(); }

    return bClearFlag;
}

bool BuffStatusManager::UpdateOnMove()
{
    bool bClearFlag = false;

    if ( buffMaxCount > BodyStatusType_Max )
    { buffMaxCount = BodyStatusType_Max; }
    
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }
        
        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        if ( !pStatus->bMoveDispel )
        { continue; }

        //if ( pStatus->stMagicShield > -1)
        //{ // ���ħ����Ч��
        //    ClearSuckDamage();
        //}

        // ���Ŀ��״̬������
        ClearBuff( i );
        
        bClearFlag = true;

        if ( _nMoveDispelBuffCount > 0 )
        { --_nMoveDispelBuffCount; }
    }

    if ( bClearFlag )
    { UpdateEffect(); }

    return bClearFlag;
}

bool BuffStatusManager::ClearBuff( int16 index, bool needUpdate/* = true*/)
{
    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    if ( index<0 || index >=buffMaxCount)
    { return false; }

    SCharBuff* pCharBuff = GetBuff( index );
    if ( pCharBuff == NULL )
    { return false; }

    AddBuffToClearRecords( *pCharBuff );
    AddBuffIdToClearIdRecords( pCharBuff->StatusID );

    pCharBuff->Reset();

    if (iEnableStatusNum > 0)
    { --iEnableStatusNum; }

    // ����ɫ��״̬��ֵ
    if ( needUpdate )
    { UpdateEffect(); }
    
    // ��״̬�ı�
    OnBuffHaveChanged( index );
    return true;
}

bool BuffStatusManager::ClearAllBuff()
{
    if ( buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    bool bHaveChange = false;
    for( int8 i=0; i<buffMaxCount; ++i )
    {
        // ���buff �������±仯��Ӱ����ֵ ������������һ��
        if ( ClearBuff( i, false ) )
        { bHaveChange = true; }
    }

    // ��������˺�ֵ
    ClearSuckDamage();

    // ��buff���,���¼���buff��ֵ
    if ( bHaveChange )
    { UpdateEffect(); }

    return true;
}

void BuffStatusManager::ClearBuffChangedRecords()
{
    memset( _buffChangeRecord, 0, sizeof(_buffChangeRecord));
}

bool BuffStatusManager::ClearBuffByBuffId( int StatusID )
{  
	if (StatusID <= 0)
	{ return false; }
	
    if (buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    bool ret = false;
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        if ( pCharBuff->StatusID == StatusID )
        {
            ClearBuff( i, false );
            ret = true;
        }
    }

    //����ɫ��״̬��ֵ
    if( ret )
    { UpdateEffect(); }

    return ret;
}

bool BuffStatusManager::ClearBuffByMasterCharID( GameObjectId shCharID, bool IsClearDebuff)
{
    bool ret = false;
    if ( buffMaxCount > BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    for ( int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );

        if ( pCharBuff == NULL )
        { continue; }

        if ( pCharBuff->masterId != shCharID )
        { continue; }

        if ( IsClearDebuff )
        {
            ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
            if( pStatus != NULL && pStatus->bAvail)
            { continue; }
        }

        ClearBuff( i, false  );
    }

    // ����ɫ��״̬��ֵ
    if( ret )
    { UpdateEffect(); }

    return false;
}

bool BuffStatusManager::ClearAllBuffByHaveAttack( bool bNeedUpdate /* = true */ )
{
    if ( buffMaxCount > BodyStatusType_Max )
    { return false; }
    
    bool bUpdate = false;
    for( int i = 0; i < buffMaxCount; ++i )
    {
        SCharBuff* pCharBuff = GetBuff( i );

        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
        if ( pStatus == NULL )
        { continue; }

        // �ж��Ƿ����˺�״̬
        if ( pStatus->bAvail )
        { continue; }

        ClearBuff( i, false );
        bUpdate = true;
    }
    
    if ( bUpdate )
    { UpdateEffect(); }    //����ɫ��״̬��ֵ

    return true;
}

bool BuffStatusManager::ClearBuffByType( bool bIsAvail, int nType )
{
    if ( buffMaxCount > BodyStatusType_Max )
    { return false; }

    bool bUpdate = false;
    for( int i = 0; i < buffMaxCount; ++i )
    {
        SCharBuff* pCharBuff = GetBuff( i );

        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
        if ( pStatus == NULL )
        { continue; }

        // �ж��Ƿ����˺�״̬
        if ( pStatus->bAvail &&  pStatus->stType == nType )
        {  
            ClearBuff( i, false );
            bUpdate = true;
        }
        else if ( !pStatus->bAvail &&  pStatus->negativeType == nType )
        {
            ClearBuff( i, false );
            bUpdate = true;
        }
    }

    if ( bUpdate )
    { UpdateEffect(); }    //����ɫ��״̬��ֵ

    return true;
}

bool BuffStatusManager::IsHaveStatus(int iStatus)
{
    if ( iStatus <= InvalidLogicNumber)
    { return false; }

    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }
        if ( pCharBuff->StatusID == iStatus)
        { return true; }
    }

    return false;
}

bool BuffStatusManager::IsHaveNegativeStatus( uint8 nNegativeType )
{
    if ( nNegativeType >= SNT_MaxCount)
    { return false; }

    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
        if ( pStatus == NULL )
        { continue; }

        if ( pStatus->negativeType == nNegativeType)
        { return true; }
    }

    return false;
}

void BuffStatusManager::UpdateEffect()
{ //����ɫ��״̬��ֵ
    bMoveFlag             = true;  
    bUsePhysicsSkillFlag  = true;  
    bUseMagicSkillFlag    = true;  
    bIsBePhyAttack        = true;
    bIsBeMagAttack        = true;
    bHide                 = false; 
    bUseItemFlag          = true;           
    bCanBeFindByMonster   = true;   
    bAttackByMonsterFirst = false;
    bClearStatusInAttack  = false; 
    bIsWeaponFormula      = true;
	bBuoy                 = false;
	bCanRide			  = true;
	IsCanGetHonour		  = true;
	IsCanBeGetHonour	  = true;
    nCurStatusAnim        = eStatusAnim_None;
    fDamage2MpRatioPer    = 0.0f;    
    iDamage2MpRatio       = 0;
    fDamageReflectRatio   = 0.0f;  
    nDamageReflectProability = 0;
    iDamageChengedRate    = 0;       
    fDamageChengedRatePer = 0.0f; 
    //iChangeSight          = -1;            
    fSuckHpRate           = 0.0f;
    nSuckHpValue          = 0;
    nSuckHpProbability    = 0;
    fMPStolenRate         = 0.0f;
    iMPStolenVal          = 0;
    stMagicShieldKid      = 0;
    fSuckPer              = 0.0f;
    //stSuckMax             = 0;
    hurtImmunity          = 0;
    nChangeMonsterID      = 0;
    //changeActivityMax     = 0;
    //activityMul           = 0;
    fActionTimeChangMod   = 0.0f;
    bCsedAddBuffer        = false;
    bAddDeBuffer          = false;
    fExpMulAdd            = 0.0f;
    fSkillExpMulAdd       = 0.0f;
    //fAddIntonateRate      = 0.0f;
    bIsRandRun            = false;
    bIsPetSupport         = false;
    _nBackAttackDispelBuffCount = 0;
    _nMoveDispelBuffCount       = 0;
    _timeExpMul                 = 0.0f;
    bInvincible                 = false;
    damagetohp                  = 0;
    _bDisableCallGraphic        = false;
    ifConsumeEnergy             = false;
    
    for(int idx = 0; idx<eElement_Max; ++ idx )
    {
        stChangedSkill_Hurt[idx] = 0;
        stChangedSkill_HurtPer[idx] = 0;
    }

    stChangedPhy_Hurt = 0;
    stChangedPhy_HurtPer = 0;
    memset( nAddBaseAttr, 0, sizeof(nAddBaseAttr));
    memset( nAddBaseAttrPer, 0, sizeof(nAddBaseAttrPer));
    //memset( nAddMountBaseAttr, 0, sizeof(nAddMountBaseAttr));
    //memset( nAddMountBaseAttrPer, 0, sizeof(nAddMountBaseAttrPer));

    //stComposeOdds   = 0;
    //stIntensifyOdds = 0;
    //fPkvalueMulAdd  = 0;

    //bNeedCalcDailyPkValue = TRUE;

    for ( int i=0; i<SNT_MaxCount; ++i)
    {
        _fStatusLimitResistRatio[i] = 0.0f;
    }

    memset( changeSkillIds, 0, sizeof(changeSkillIds));
    memset( changeSkillTimes, 0, sizeof(changeSkillTimes));

	BeDamagePerHpMax = 0;
    
	//stSuckBuffMax
	short MaxSuckBuffMax = 0;
    for (int i=0; i<buffMaxCount; ++i)
    {   
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        if ( pStatus->bIsMove )
        { //�Ƿ����ƶ�
            bMoveFlag = false;
        }

		if ( pStatus->bIsFlyAir)
		{
			bBuoy = true;
		}

        if ( pStatus->bIsAtt )
        { //�Ƿ��ܹ���
            bUsePhysicsSkillFlag = false;
        }

        if ( pStatus->bIsUsingMagic )
        {
            bUseMagicSkillFlag = false;
        }

        if ( pStatus->bIsBePhyAttack )
        {
            bIsBePhyAttack  = false;
        }

        if ( pStatus->bIsBeMagAttack )
        {
            bIsBeMagAttack = false;
        }

        if( pStatus->bIsHide )
        {
            bHide = true;
        }

		if (!pStatus->canRide)
		{
			bCanRide = false;
		}

		if(!pStatus->canGetHonour)
		{
			IsCanGetHonour = false;
		}

		if(!pStatus->canBeGetHonour)
		{
			IsCanBeGetHonour = false;
		}

        if ( pStatus->bInvincible )
        {
            bInvincible = true;
        }

        if( pStatus->nStatusAnim > eStatusAnim_None && pStatus->nStatusAnim < eStatusAnim_Max && pStatus->nStatusAnim > nCurStatusAnim )
        {
            nCurStatusAnim = pStatus->nStatusAnim;
        }

        if ( pStatus->bIsUsingTools )
        {
            bUseItemFlag = false;
        }

        if ( pStatus->bAttckedNoStatus )
        { // �ܵ�����ʱ���״̬
            bClearStatusInAttack = true;
        }

        //if (!pStatus->bCanFindByMonster) //�жϿɷ񱻹��﷢��..
        //{
        //    bCanBeFindByMonster = false;
        //}
        //if (pStatus->stChanged_MonsterEnmity)        //�ж������ȼ��𱻹��﹥��
        //{
        //    bAttackByMonsterFirst = true;
        //}

        if ( pStatus->fSuckHpRate > 0) // ��Ѫ����
        { fSuckHpRate += pStatus->fSuckHpRate;}

        if ( pStatus->stAbsorbExtraHPVal > 0) // ��Ѫֵ
        { nSuckHpValue += pStatus->stAbsorbExtraHPVal; }

        if ( pStatus->nSuckHpProbability>0)
        { nSuckHpProbability += pStatus->nSuckHpProbability; }

        /*if( pStatus->fAbsorbExtraMPRate )
        {
            fMPStolenRate += pStatus->fAbsorbExtraMPRate;
        }
        if( pStatus->stAbsorbExtraMPVal )
        {
            iMPStolenVal  += pStatus->stAbsorbExtraMPVal; 
        }*/

        //iDamageChengedRate += pStatus->stChanged_FianHurt;        //�˺�����
        //fDamageChengedRatePer += pStatus->fChanged_FianHurtPer;    //�˺����� ��%

        //fDamage2MpRatioPer += pStatus->fMagic_FreeHurtPer;    //
        //if (fDamage2MpRatioPer)
        //    iDamage2MpRatio += pStatus->stMagic_FreeHurt;

        if ( pStatus->fChanged_ReboundVal > 0 )
        { fDamageReflectRatio += pStatus->fChanged_ReboundVal; }

        if ( pStatus->nDamageReflectProability > 0)
        { nDamageReflectProability += pStatus->nDamageReflectProability;}
        

        //if (pStatus->stChanged_MonsterView > 0)
        //{
        //    if (iChangeSight < 0)
        //        iChangeSight = 0;
        //    iChangeSight += pStatus->stChanged_MonsterView;
        //}

        ////MP�˺�
        //if (pStatus->stManaBurn != 0)
        //{
        //    iDamageMp += pStatus->stManaBurn;
        //}

        ////�Ƿ���ӻر�
        //bHedgeNull = pStatus->bHedgeNull;

        //�˺�����
        //int idx = 0;
        //for( idx=0; idx<EAttackType_Max; idx++ )
        //{
        //    bHurtImmunity[idx] = pStatus->bHurtImmunity[idx];
        //}
        //״̬����    0?û��״̬����:�ڼ�����������
        //stStatusFree = pStatus->stStatusFree;
        
        if (pStatus->bAttckNoStatus)
        { //����ʱ���״̬
            bAttackClearStatus = true;
        }

        //if (pStatus->stChangWeapon_Attribute < EAttackType_Max && pStatus->stChangWeapon_Attribute > EAttackType_Short)
        //{
        //    bIsWeaponFormula = false;
        //}

        if (pStatus->stMagicShield != 0)
        {
            stMagicShieldKid = pStatus->stMagicShield;
        }

        if (pStatus->fSuckDamagePer != 0)
        {
            fSuckPer = pStatus->fSuckDamagePer;
        }

		if (pStatus->BeDamagePerHpMax != 0)
		{
			BeDamagePerHpMax = pStatus->BeDamagePerHpMax;
		}

        if (pStatus->stSuckDamageMax != 0)
        {
			MaxSuckBuffMax = pStatus->stSuckDamageMax;
			/*IsNeedSuck = true;
			if(stSuckMax == 0)
			{
				stSuckMax = pStatus->stSuckDamageMax;
				if ( pBuffEvent != NULL ) { pBuffEvent->bXinFa = true; }
			}*/
        }

        if (pStatus->hurtImmunity != 0 )
        {
            hurtImmunity = pStatus->hurtImmunity;
        }

        //if (pStatus->stBurnMpPerDamage != 0)
        //{
        //    stPerDamageNeedMp = pStatus->stBurnMpPerDamage;
        //}

        //if (pStatus->changeActivityMax != 0)
        //{
        //    changeActivityMax = pStatus->changeActivityMax;
        //}

        //if (pStatus->activityMul != 0)
        //{
        //    activityMul = pStatus->activityMul;
        //}

        //if (pStatus->reduceTax != 0)
        //{
        //    reduceTax = pStatus->reduceTax;
        //}

        if (pStatus->deathDurabilityPer != 0)
        {
            deathDurabilityPer = pStatus->deathDurabilityPer;
        }

        if (pStatus->addCatchPetRate != 0 )
        {
            addCatchPetRate = pStatus->addCatchPetRate;
        }

        if (pStatus->deathMountHPDropPer != 0)
        {
            deathMountHPDropPer = pStatus->deathMountHPDropPer;
        }

        if ( pStatus->nChangeMonsterID > 0 )
        {
            nChangeMonsterID = pStatus->nChangeMonsterID;
        }

        //if (pStatus->fIncreaseHP != 0)
        //{
        //    fHpIncreasePer = pStatus->fIncreaseHP;
        //}

        //if (pStatus->fIncreaseMP != 0)
        //{
        //    fMpIncreasePer = pStatus->fIncreaseMP;
        //}

        if (pStatus->bIsChangActionTime == true)
        {
            fActionTimeChangMod = pStatus->fChangActionTime;
        }

        if (pStatus->bIsAddBufferBeCSed == true)
        {
            bCsedAddBuffer = true;
        }

        if (pStatus->bIsAddDeBufferToAttacker == true)
        {
            bAddDeBuffer = true;
        }

        if (pStatus->fAddExpMul > 0.0f)
        {
            fExpMulAdd += pStatus->fAddExpMul;
        }

        if (pStatus->fAddSkillExpMul > 0.0f)
        {
            fSkillExpMulAdd += pStatus->fAddSkillExpMul;
        }

        //if (pStatus->fAddIntonateRatePer != 0.0f)
        //{
        //    fAddIntonateRate += pStatus->fAddIntonateRatePer;
        //}

        //if ( pStatus->stBalanceType != CItemDetail::balance_status_type_mount )
        //{
            for (int n = 0; n < EBaseAttr_MaxSize; ++n)
            {
                nAddBaseAttr[n] += pStatus->stAddBaseAttr[n];
                nAddBaseAttrPer[n] += pStatus->stAddBaseAttrPer[n];
            }
        //}
        //else
        //{
        //    for (int n = 0; n < EBaseAttr_MaxSize; ++n)
        //    {
        //        nAddMountBaseAttr[n] += pStatus->stAddBaseAttr[n];
        //        nAddMountBaseAttrPer[n] += pStatus->stAddBaseAttrPer[n];
        //    }
        //}

        //if (pStatus->stComposeOdds != 0)
        //{
        //    stComposeOdds += pStatus->stComposeOdds;
        //}

        //if (pStatus->stIntensifyOdds != 0)
        //{
        //    stIntensifyOdds += pStatus->stIntensifyOdds;
        //}

        //if (pStatus->fAddPkValueMul > 0.0f)
        //{
        //    fPkvalueMulAdd += pStatus->fAddPkValueMul;
        //}

        //if (!pStatus->bNeedCalcDailyPkValue)
        //{
        //    bNeedCalcDailyPkValue = FALSE;
        //}

        if (pStatus->addMoney != 0)
        {
            addMoney = pStatus->addMoney;
        }

        if (pStatus->addReputation != 0)
        {          
            addReputation = pStatus->addReputation;
        }

        if (pStatus->addExploit != 0)
        { 
            addExploit = pStatus->addExploit ;
        }
        
        if (pStatus->addHonour != 0)
        { 
            addHonour = pStatus->addHonour ;
        }

        if (pStatus->addHonourLimit != 0)
        { 
            addHonourLimit = pStatus->addHonourLimit ;
        }

        if (pStatus->addMasterValue != 0)
        { 
            addMasterValue  = pStatus->addMasterValue;
        }

        if (pStatus->addBattleScore != 0)
        {
            addBattleScore  = pStatus->addBattleScore;
        }

        if (pStatus->reputationMul != 0)
        {
            reputationMul = pStatus->reputationMul;     
        }

        if (pStatus->exploitMul != 0)
        {
            exploitMul = pStatus->exploitMul;   
        }

        if (pStatus->honourMul != 0)
        {
            honourMul = pStatus->honourMul ;
        }

        if (pStatus->masterValueMul != 0)
        {
            masterValueMul = pStatus->masterValueMul;
        }

        if (pStatus->battleScoreMul != 0)
        {
            battleScoreMul = pStatus->battleScoreMul; 
        }

        if (pStatus->bIsRandRun)
        {
            bIsRandRun = true;
        }

        if (pStatus->bIsPetSupport)
        {
            bIsPetSupport = true;
        }

        if ( pStatus->bBackAttckedDispel )
        {
            ++_nBackAttackDispelBuffCount;
        }

        if ( pStatus->bMoveDispel)
        {
            ++_nMoveDispelBuffCount;
        }

        if ( pStatus->bDisableCallGraphic )
        { _bDisableCallGraphic = true; }

        _timeExpMul += pStatus->timeExpMul;

        if ( pStatus->damagetohp > 0)
        { damagetohp += pStatus->damagetohp;}
        
        //����������MP
        if (pStatus->ifConsumeEnergy)
        {
            ifConsumeEnergy = true;
        }

        //������ȴʱ��
        if (pStatus->changeSkillIds[0] != 0)
        {
            for ( int i=0; i<ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize; ++i)
            {
                changeSkillIds[i] = pStatus->changeSkillIds[i]    ;
                changeSkillTimes[i] = pStatus->changeSkillTimes[i];
            }
        }
    }

	if(MaxSuckBuffMax != stSuckBuffMax)
	{
		//�����˺�����
		stSuckBuffMax = MaxSuckBuffMax;
		stSuckMax =MaxSuckBuffMax; 
		if ( pBuffEvent != NULL ) { pBuffEvent->bXinFa = true; }
	}

    if (fDamageChengedRatePer < 0)
    { fDamageChengedRatePer = 0; }

    if (fDamageChengedRatePer > 1)
    { fDamageChengedRatePer = 1; }
    
    if (fDamage2MpRatioPer < 0)
    { fDamage2MpRatioPer = 0; }

    if (fDamage2MpRatioPer > 1)
    { fDamage2MpRatioPer = 1; }
    
    //if (fAddIntonateRate > 1.0f)
    //{ fAddIntonateRate = 1.0f; }

    // �޵�״̬��������е��к�����
    if ( bInvincible ) 
    { ClearAllBuffByHaveAttack( false ); }

    CallBuffEvent();
}

//////////////////////////////////////////////////////////////////////////
// �����¼��ص�����
//////////////////////////////////////////////////////////////////////////
void BuffStatusManager::CallBuffEvent()
{
    if (pBuffEvent == NULL)
    { return; }

    if (pBuffEvent->bHide != IsHide())
    {
        if ( IsHide() )
        { pBuffEvent->OnEnterHide(); }

        pBuffEvent->bHide = IsHide();
    }

    if (pBuffEvent->bXinFa)
    {
        pBuffEvent->OnXinFaUpdate();
        pBuffEvent->bXinFa = false ;
    }
}

void BuffStatusManager::OnBuffHaveChanged( uint16 index )
{
    if ( index > BodyStatusType_Max)
    { return; }

    _buffChangeRecord[index] = true;
}

bool BuffStatusManager::IsCanUseSkill( ItemDefine::SItemSkill* pSkillConfig )
{
    if ( IsNormalAttack( pSkillConfig->ustItemID ))
    { // ��ͨ����
        if (!IsCanUsePhysicsSkill())
        { return false; }
    }
    else
    {   
        if (!IsCanUseMagicSkill())
        {
			if (IsCollectSkill(pSkillConfig->ustItemID))
			{
				if (IsHaveNegativeStatus(SNT_GIDDY)
					||IsHaveNegativeStatus(SNT_STAND)
					||IsHaveNegativeStatus(SNT_AFRAID)
					||IsHaveNegativeStatus(SNT_SLEEP)
					||IsHaveNegativeStatus(SNT_DISTORTION)
					||IsHaveNegativeStatus(SNT_ALLURE)
					||IsHaveNegativeStatus(SNT_FROST))
				{
					return false;
				}
				return true;
			}
			if(IsHaveNegativeStatus(SNT_GIDDY) && pSkillConfig->bGiddyDischarge)
			{
				return true;
			}
			return false; 
		}
    }
    return true;
}

bool BuffStatusManager::IsCanUseSkill(  uint16 iSkillID, uint16 iSkillLevel)
{   
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(iSkillID, iSkillLevel);
    if (NULL == pSkill)
    { return false;}

    return IsCanUseSkill( pSkill );
}

//
//    ȡ���˺���ת��Ϊmp�İٷ���
//
int BuffStatusManager::GetDamageChange2MpRatio()
{
    return iDamage2MpRatio;
}

//�˺�����//
int BuffStatusManager::GetDamageChengedRate()
{
    return iDamageChengedRate;
}

//�˺�����%
float BuffStatusManager::GetDamageChengedRatePer()
{
    return fDamageChengedRatePer;
}

int BuffStatusManager::GetDamageMp ()
{
    return iDamageMp;
}

//short BuffStatusManager::GetMagicShieldKid ()
//{
//    return stMagicShieldKid;
//}

float BuffStatusManager::GetSuckDamgePer ()
{
    return fSuckPer;
}

void BuffStatusManager::ClearSuckDamage ()
{
    stSuckMax = 0;
    fSuckPer  = 0;
}

//float BuffStatusManager::GetIncreaseMp ()
//{
//    return fMpIncreasePer;
//}
//float BuffStatusManager::GetIncreaseHp ()
//{
//    return fHpIncreasePer;
//}

float BuffStatusManager::GetActionTimeMod()
{
    return fActionTimeChangMod;
}

bool BuffStatusManager::ApplyBuffsToChar( uint16 profession, SCharBaseAttr* pBase, SCharFightAttr* pFight )
{
    if( pFight == NULL )
    { return false; }

    if ( pBase )
    { pBase->ClearPart( ECustomDataPart_status ); }

    pFight->hpMax            .status = 0 ;
    pFight->mpMax            .status = 0 ;
    pFight->attackPhysics    .status = 0 ;
    pFight->attackMagic      .status = 0 ;
    pFight->defendPhysics    .status = 0 ;
    pFight->defendMagic      .status = 0 ;
    pFight->attackSpeed      .status = 0 ;
    pFight->moveSpeed        .status = 0 ;
    pFight->hpRestore        .status = 0 ;
    pFight->mpRestore        .status = 0 ;
    pFight->exact            .status = 0 ;
    pFight->dodge            .status = 0 ;
    pFight->critical         .status = 0 ;
    pFight->tenacity         .status = 0 ;
    pFight->criticalIntensity.status = 0 ;
    pFight->backStrike       .status = 0 ;
    pFight->backStrikeResist .status = 0 ;
    pFight->breakStrike      .status = 0 ;
    pFight->stabStrike       .status = 0 ;
    pFight->elementStrike    .status = 0 ;
    pFight->toxinStrike      .status = 0 ;
    pFight->spiritStrike     .status = 0 ;
    pFight->breakResist      .status = 0 ;
    pFight->stabResist       .status = 0 ;
    pFight->elementResist    .status = 0 ;
    pFight->toxinResist      .status = 0 ;
    pFight->spiritResist     .status = 0 ;
    pFight->hpMax            .statusPer = 0 ;
    pFight->mpMax            .statusPer = 0 ;
    pFight->attackPhysics    .statusPer = 0 ;
    pFight->attackMagic      .statusPer = 0 ;
    pFight->defendPhysics    .statusPer = 0 ;
    pFight->defendMagic      .statusPer = 0 ;
    pFight->attackSpeed      .statusPer = 0 ;
    pFight->moveSpeed        .statusPer = 0 ;
    pFight->hpRestore        .statusPer = 0 ;
    pFight->mpRestore        .statusPer = 0 ;
    pFight->exact            .statusPer = 0 ;
    pFight->dodge            .statusPer = 0 ;
    pFight->critical         .statusPer = 0 ;
    pFight->tenacity         .statusPer = 0 ;
    
    if ( pBase )
    {
        // ����һ������
        for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
        { 
            pBase->baseAttrValue[i].status += nAddBaseAttr[i]; 
            pBase->baseAttrValue[i].statusPer += nAddBaseAttrPer[i]; 

            // һ���������ö�������
            ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_status, pBase->baseAttrValue[i], profession, *pFight );
        }
    }

    // ���ö�������
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( NULL == pStatus )
        { continue; }

        pFight->moveSpeed.status        += pStatus->fMoveSpeedChanged;                  // �ı��ɫ���ƶ��ٶ�
        pFight->moveSpeed.statusPer     += pStatus->nMoveSpeedPer;                      // �ı��ɫ���ƶ��ٶ� %
        
        pFight->attackPhysics.status    += pStatus->changePhyAttack;                       // ������
        pFight->attackPhysics.statusPer += pStatus->changePhyAttackPer;                    // ������%
        pFight->attackMagic.status      += pStatus->changeMagAttack;                       // ������
        pFight->attackMagic.statusPer   += pStatus->changeMagAttackPer;                    // ������%

        pFight->defendPhysics.status    += pStatus->changeDefend[EDefendType_Physical];     // ���
        pFight->defendPhysics.statusPer += pStatus->changeDefendPer[EDefendType_Physical];  // ���%
        pFight->defendMagic.status      += pStatus->changeDefend[EDefendType_Magic];    // ħ��
        pFight->defendMagic.statusPer   += pStatus->changeDefendPer[EDefendType_Magic]; // ħ��%

        pFight->hpRestore.status        += pStatus->resumeHP;                           // ��ɫHP�ָ��ٶȸı�
        pFight->hpRestore.statusPer     += pStatus->resumeHPPer;                        // ��ɫHP�ָ��ٶȸı�%
        pFight->mpRestore.status        += pStatus->resumeMP;                           // ���MP�ָ��ٶȸı�
        pFight->mpRestore.statusPer     += pStatus->resumeMPPer;                        // ���MP�ָ��ٶȸı�%
        pFight->hpMax.status            += pStatus->stChanged_HPMax;                    // Ѫ�����ֵ
        pFight->hpMax.statusPer         += pStatus->changeHPMaxPer;                     // Ѫ�����ֵ%
        pFight->mpMax.status            += pStatus->stChanged_MPMax;                    // �������ֵ
        pFight->mpMax.statusPer         += pStatus->changeMPMaxPer;                     // �������ֵ%
        pFight->dodge.status            += pStatus->stChanged_Hedge ;                   // �ı�����
        pFight->exact.status            += pStatus->stChanged_Hit   ;                   // ����
        pFight->critical.status         += pStatus->changed_Critical ;                  // ������
        pFight->criticalIntensity.status+= pStatus->changed_CriticalIntensity ;         // �����˺�
        pFight->tenacity.status         += pStatus->changeTenacity;                     // �ı�����

        pFight->attackSpeed.statusPer   += pStatus->fAttSpeedPer ;                      // �����ٶ�

        pFight->breakStrike.status      += pStatus->breakStrike;           
        pFight->stabStrike.status       += pStatus->stabStrike;
        pFight->spiritStrike.status     += pStatus->spiritStrike;   
        pFight->toxinStrike.status      += pStatus->toxinStrike;    
        pFight->elementStrike.status    += pStatus->elementStrike;  

        pFight->breakResist.status      += pStatus->breakResist;           
        pFight->stabResist.status       += pStatus->stabResist;
        pFight->spiritResist.status     += pStatus->spiritResist;   
        pFight->toxinResist.status      += pStatus->toxinResist;    
        pFight->elementResist.status    += pStatus->elementResist;      
    }

    pFight->hpMax            .UpdateFinal();
    pFight->mpMax            .UpdateFinal();
    pFight->attackPhysics    .UpdateFinal();
    pFight->attackMagic      .UpdateFinal();
    pFight->defendPhysics    .UpdateFinal();
    pFight->defendMagic      .UpdateFinal();
    pFight->attackSpeed      .UpdateFinal();
    pFight->moveSpeed        .UpdateFinal();
    pFight->hpRestore        .UpdateFinal();
    pFight->mpRestore        .UpdateFinal();
    pFight->exact            .UpdateFinal();
    pFight->dodge            .UpdateFinal();
    pFight->critical         .UpdateFinal();
    pFight->tenacity         .UpdateFinal();
    pFight->criticalIntensity.UpdateFinal();
    pFight->backStrike       .UpdateFinal();
    pFight->backStrikeResist .UpdateFinal();
    pFight->breakStrike      .UpdateFinal();
    pFight->stabStrike       .UpdateFinal();
    pFight->elementStrike    .UpdateFinal();
    pFight->toxinStrike      .UpdateFinal();
    pFight->spiritStrike     .UpdateFinal();
    pFight->breakResist      .UpdateFinal();
    pFight->stabResist       .UpdateFinal();
    pFight->elementResist    .UpdateFinal();
    pFight->toxinResist      .UpdateFinal();
    pFight->spiritResist     .UpdateFinal();
    return true;
}

bool BuffStatusManager::ClearBuffByBuffIdLevel(int nStatusId,int nStatusLevel)
{
    bool bResult = false;

    ItemDefine::SItemStatus* pItemStatusNeedDel = (ItemDefine::SItemStatus*)GettheItemDetail().GetStatus(nStatusId,nStatusLevel);
    if ( NULL == pItemStatusNeedDel)
    { return false; }

    if ( buffMaxCount> BodyStatusType_Max)
    { buffMaxCount = BodyStatusType_Max; }

    for (int nloop = 0 ;nloop < buffMaxCount; ++nloop)
    {
        SCharBuff* pBodyStatus = GetBuff(nloop);
        if ( NULL == pBodyStatus)
        { continue; }

        ItemDefine::SItemStatus* pItemStatus = (ItemDefine::SItemStatus*)GettheItemDetail().GetStatus(pBodyStatus->StatusID,pBodyStatus->iLevel);        
        if ( NULL == pItemStatus)
        { continue; }

        if (pItemStatus->stType == pItemStatusNeedDel->stType)
        {
            ClearBuff(nloop);
            bResult = true;
        }
    }

    return bResult;
}

void BuffStatusManager::LogAndClearBufferClearIdArray()
{
    for (int n=0;n < BodyStatusType_Max; ++n)
    {
        int nClearStatusId = GetClearIdArrayId(n);

        if (nClearStatusId > 0)
        {
            ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( nClearStatusId, 1);
            if (pStatus)
            {
                if ( !_strCharacterName.empty())
                {
#ifndef _CLIENT_
                    LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, theXmlString.GetString(eLog_info_2slk_33), _strCharacterName.c_str(), pStatus->GetItemName());
#endif //_CLIENT_
                }
            }    
        }
    }
    ClearBuffClearIdRecords();
}

#define STATUSIDS_BUFFERSIZE 2500
#define STATUSID_BUFFERSIZE  100

void BuffStatusManager::Log( int nFailLocation, int buffId, int buffLevel )
{
#ifndef _CLIENT_
        LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, "ApplyBuff() was failed loc=%d buffId=%d buffLevel=%d", nFailLocation, buffId, buffLevel  );
#endif //_CLIENT_
}

void BuffStatusManager::LogStatus( SCharBuff* pData )
{
	if (!pData)
	{
		return;
	}
    char szStatusIds[ STATUSIDS_BUFFERSIZE +1 ] = {0};    
    char szStatusId [ STATUSID_BUFFERSIZE  +1 ] = {0};
    memset( szStatusIds, 0, sizeof(szStatusIds) );
    memset( szStatusId, 0, sizeof(szStatusId) );

    sprintf_s( szStatusIds, STATUSIDS_BUFFERSIZE, "Time[%u]StatusIds:", HQ_TimeGetTime());

    if ( pData == NULL )
    { pData = m_pstBodyStatus; }

    if ( pData )
    { // ���ݴ���
        for (int i=0; i<BodyStatusType_Max; ++i)
        {
            if ( pData[i].StatusID <= 0 || pData[i].iLevel <= 0)
            { continue; }

            ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pData[i].StatusID, pData[i].iLevel );
            if ( pItemStatus == NULL )
            { continue;}

            if ( pItemStatus->stActualTime <= 0)
            { // ������ʵʱ��
                sprintf_s( szStatusId, STATUSID_BUFFERSIZE, "%d:%d:s%u:p%u|", pData[i].StatusID, pData[i].iLevel, pData[i].dwStartTime, pData[i].dwPreDamage );
            }
            else
            {
                sprintf_s( szStatusId, STATUSID_BUFFERSIZE, "%d:%d:I%I64u:d%u|", pData[i].StatusID, pData[i].iLevel, pData[i].nInt64StartTime, pData[i].dwDurationTime );
            }

            HelperFunc::AddNCpy( szStatusIds, szStatusId, sizeof( szStatusIds ) );
        }
    }

    if ( !_strCharacterName.empty())
    {
#ifndef _CLIENT_
        LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, "[%s] [%s]", _strCharacterName.c_str(), szStatusIds );
#endif //_CLIENT_
    }
}

bool BuffStatusManager::UpdateStatusIsInCriticaled( bool bIsBeCSed )
{
    for(int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        if ( pStatus->bIsAddBufferBeCSed && bIsBeCSed )
        {
            SetBeCriticaledBufferId( pStatus->stBeCsedAddBufferMeId);
            SetBeCriticaledBufferLevel(pStatus->stBeCsedAddBufferMeLevel);
            return true;
        }
    }
    return false;
}

bool BuffStatusManager::CheckTargetIsHaveAddBufferFlag(float fAttackerHpPer)
{
    for ( int i=0; i<buffMaxCount; ++i )
    {
        SCharBuff* pCharBuff = GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }
        
        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if (pStatus == NULL)
        { continue; }

        if ( pStatus->bIsAddDeBufferToAttacker && pStatus->fAddDeBufferByHpPer >= fAttackerHpPer )
        {
            SetDeBufferID( pStatus->stAddDeBufferID);
            SetDeBufferLevel( pStatus->stAddDeBufferLevel);
            return true;
        }
    }
    return false;
}

void BuffStatusManager::AddStatusFromData( DWORD stageId, SCharBuff* pData, int num, DWORD dwCurTime, bool bFirstEnterWorld /* = false */)
{
    if (num < 0 || num > BodyStatusType_Max)
    { num = BodyStatusType_Max; }

    LogStatus( pData );

    for (int n=0; n<num; ++n ) 
    {
        if (pData[n].StatusID > 0 && pData[n].iLevel > 0)
        {
            if ( bFirstEnterWorld )
            { // ��һ�ν���Ϸ����, ����Ҫ���״̬��Ҫ����
                if ( pData[n].restoreType != ItemDefine::ESRT_Forever )
                { continue; }
            }
            else
            { // ���ǵ�һ�ν���Ϸ���� �з� ֻ��һ����������� Ҳ��Ҫ����
                if ( pData[n].restoreType == ItemDefine::ESRT_OnlyInServer )
                { continue; }
            }
            
			ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pData[n].StatusID,pData[n].iLevel );
			if ( NULL == pItemStatus )
            { continue; }

            // TODO: ��������״̬
            if ( pItemStatus->iDurationTime == -1 )
            { continue; }

            bool bNeedStop = false;
            if ( pItemStatus->actionMapConfigId != InvalidLogicNumber && pItemStatus->actionMapConfigId != EctypeId2MapId(stageId) )
            { bNeedStop = true; }

			int nTempTime = 0;
			if (pItemStatus->stActualTime <= 0)
			{ // ������ʵʱ��
                if ( bNeedStop )
                {  // ��Ҫֹͣ
                    if ( pData[n].bStop )
                    { // �Ѿ�ֹͣ
                    }
                    else
                    { // ��ûֹͣ
                        nTempTime = pData[n].dwPreDamage - pData[n].dwStartTime;
                        if ( nTempTime < 0 || pData[n].dwDurationTime <= nTempTime )
                        { continue; }

                        pData[n].dwStartTime = dwCurTime;
                        pData[n].dwDurationTime -= nTempTime;	
                        if (pData[n].dwDurationTime > pItemStatus->iDurationTime)
                        { pData[n].dwDurationTime = pItemStatus->iDurationTime; }
                        pData[n].bStop = 1;
                    }
                }
                else
                { // ����Ҫֹͣ
                    if ( !pData[n].bStop )
                    { // ����ûͣ
                        nTempTime = pData[n].dwPreDamage - pData[n].dwStartTime;
                        if ( nTempTime < 0 || pData[n].dwDurationTime <= nTempTime )
                        { continue; }

                        pData[n].dwStartTime = dwCurTime;
                        pData[n].dwDurationTime -= nTempTime;	
                        if (pData[n].dwDurationTime > pItemStatus->iDurationTime)       // ���ü��ܽ����¸�ֵ
                        {
                            pData[n].dwDurationTime = pItemStatus->iDurationTime;
                        }
                    }
                    else
                    { // ����ֹͣ
                        pData[n].dwStartTime    = dwCurTime;                        
                        if (pData[n].dwDurationTime > pItemStatus->iDurationTime)
                        { pData[n].dwDurationTime = pItemStatus->iDurationTime; }
                        pData[n].bStop = 0;
                    }
                }

                pData[n].dwPreDamage = dwCurTime;
                pData[n].masterId    = InvalidGameObjectId;

                BOOL bResult = ApplyBuff( pData[n].bStop, pData[n].StatusID, pData[n].iLevel, -1, HQ_TimeGetTime(), false, pData[n].dwDurationTime, pData[n].dwPlayerDBID, pData->eventType, pData->eventValue);
			}
			else
			{
				TimeEx StatusTime( pData[n].nInt64StartTime );
				if ( StatusTime > TimeEx::GetCurrentTime() )
				{
					TimeSpan xTimeSpan = StatusTime - TimeEx::GetCurrentTime(); 
					pData[n].dwDurationTime = xTimeSpan.GetTotalSeconds() * 1000;
					pData[n].dwPreDamage = dwCurTime;

                    BOOL bResult = ApplyBuff( pData[n].bStop, pData[n].StatusID, pData[n].iLevel, -1, HQ_TimeGetTime(), false, pData[n].dwDurationTime, pData[n].dwPlayerDBID, pData->eventType, pData->eventValue);
				}                
			}
		}
	}

    LogStatus( m_pstBodyStatus );
}

bool BuffStatusManager::UpdateOnDead()
{
    bool bHaveChange = false;

    if( buffMaxCount > BodyStatusType_Max )
    { buffMaxCount = BodyStatusType_Max; }

    for( int i=0; i<buffMaxCount; ++i )
    {
        SCharBuff* pCharBuff = GetBuff( i );

        if( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( NULL == pItemStatus )
        { continue; }
        
        if ( !pItemStatus->bIsClearByDead)
        { continue; }

        ClearBuff( i, false );
        bHaveChange = true;
    }

    ClearSuckDamage();

    //����ɫ��״̬��ֵ
    if ( bHaveChange )
    { UpdateEffect(); }

    return bHaveChange;
}

int BuffStatusManager::GetBufferStatusIndexById( int statusId )
{
    for (int i=0; i<buffMaxCount; ++i)
    {
        SCharBuff* pCharBuff = GetBuff( i );

        if( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( NULL == pStatusConfig)
        { continue; }

        if ( pStatusConfig->ustItemID == statusId )
        { return i; }
    }

    return -1;
}

int BuffStatusManager::HaveChangeChangeMonsterIDBuff()
{ 
    return nChangeMonsterID > 0;
}
