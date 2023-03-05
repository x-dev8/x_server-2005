#include "MountManager.h"
#include "GamePlayer.h"
#include "ExpStage.h"
#include "Configure.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"

MountManager::MountManager() : _pMountItems( NULL ), _pGamePlayer( NULL), _nMountCount( 0 ),_pMountConfig(NULL),
                               _activeIndex( -1 ), _activeMountBeRiding( false ), _accumulateActionTime( 0 )
{
    _mapId  = 0;              
    _posX   = 0;              
    _posY   = 0;   
    _dwUnRideTime = 0;
    _dwLastTipsTime = 0;
}

bool MountManager::CreateFromData( GamePlayer* pOwn, SMountItem* pMountItems, int nMountCount )
{
    if ( !pMountItems || nMountCount < 0 || !pOwn)
        return false;

    _pMountItems = pMountItems;
    _nMountCount = nMountCount;
    _pGamePlayer = pOwn;           

    // 刷新出战坐骑的Id
    UpdateActiveIndex();
    return true;
} 

typedef std::list<int> Nums;
typedef Nums::iterator ItrNums;
int GetRandNum( Nums& input, bool bRemoveHaveRandNum = true )
{   
    if ( input.empty())
    { return 0; }

    int inputSize = input.size();
    int randNum  = theRand.rand32() % inputSize;
    ItrNums it    = input.begin();
    ItrNums itEnd = input.end();
    for ( int i=0; it!=itEnd; ++i, ++it )
    {
        if ( randNum != i)
        { continue; }

        int resultNum = *it;
        if ( bRemoveHaveRandNum )
        { input.erase( it );}
        return resultNum;
    }
    return 0;
}

bool MountManager::InitMountAttribute( SMountItem& mount )
{
    ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( mount.baseInfo.id );
    if ( !pMount ) 
    { return false; }

    mount.baseInfo.ResetAttibute();

    mount.baseInfo.level        = /*1*/0;	//强化从0开始
    mount.baseInfo.exp          = 0;
    mount.baseInfo.hp           = MountManager::CD_MOUNT_HP_MAX_VALUE;
    mount.baseInfo.hpMax        = MountManager::CD_MOUNT_HP_MAX_VALUE;                 
    mount.baseInfo.savvy        = GetRand( pMount->sawyMin, pMount->sawyMax );

    mount.baseInfo.nPotentialPoint = 0;

    for ( int i=0; i<EBaseAttr_MaxSize; ++i )
    { 
        mount.baseInfo.baseAttribute[i] = GetRand( pMount->baseMin[i], pMount->baseMax[i] );

        mount.baseInfo.aptitudeAttribute[i] =  GetRand( pMount->addMin[i], pMount->addMax[i] );

        mount.baseInfo.potentialAttribute[i] = 0;
    }

    // 刷新属性
    mount.baseInfo.UpdateCurrentAttribute();
    return true;
}

typedef std::list<unsigned short> SkillIds;
typedef SkillIds::iterator        ItrSkillIds;
SkillIds GetRandSkill( const SkillIds& values, int resultCount )
{
    if ( resultCount > values.size())
        resultCount = values.size();

    SkillIds input = values;    
    SkillIds results;

    for ( int i=0; i<resultCount; ++i )
    {
        int inputSize = input.size();
        int randNum  = theRand.rand32() % inputSize;
        ItrSkillIds it    = input.begin();
        ItrSkillIds itEnd = input.end();
        for ( int i=0; it!=itEnd; ++i, ++it )
        {
            if ( randNum != i)
            { continue; }

            results.push_back( *it );
            input.erase( it );
            break;
        }
    }
    return results;
}

bool MountManager::RandMountQuality( SMountItem& mountItem )
{
    ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( mountItem.baseInfo.id );
    if ( pMount == NULL ) 
    { return false; } 

    // 先得到洗点的马的随即总和
    unsigned int nTotalProbability = 0;
    for ( int i = 0; i < pMount->arrayProbability.GetSize(); ++i )
    {
        nTotalProbability += pMount->arrayProbability[i];
    }

    if ( nTotalProbability == 0 )
    { return false; }

    // 随即一个数值
    unsigned int nRandNumber = theRand.rand32() % nTotalProbability;
    unsigned int nProbability = 0;
    for ( int i = 0; i < pMount->arrayProbability.GetSize(); ++i )
    {
        nProbability += pMount->arrayProbability[i];
        if ( nRandNumber < nProbability )
        {
            if ( pMount->arrayMountID[i] != 0 )
            {
                ItemDefine::SDrome* pRandMount = GettheItemDetail().GetDromeByID( pMount->arrayMountID[i] );
                if ( pRandMount == NULL ) 
                { return false; } 

                mountItem.baseInfo.id       = pRandMount->stId      ;
                mountItem.baseInfo.quality  = pRandMount->quality   ;
            }
            return true;
        }
    }

    return false;
}

bool MountManager::InitMountSkill( SMountItem& mount )
{
    ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( mount.baseInfo.id );
    if ( !pMount ) 
    { return false; }

    mount.skillInfo.Reset();

    // 坐骑速度技能
    mount.skillInfo.AddSkill(pMount->selfSpeedSkillId, 1, SMountItem::MICD_PassiveSkillIndex );

    int randNum = theRand.rand32() % RAND_NUM;
    if ( randNum <= pMount->selfSkillRate )
    {
        SkillIds values;
        SkillIds result;
        for ( int i=0; i<ItemDefine::SDrome::DCD_SELFSKILLIDCOUNT; ++i)
        {
            if ( pMount->selfSkillId[i] == 0)
            { break; }
            values.push_back( pMount->selfSkillId[i] );
        }

        if ( !values.empty())
        {
            result = GetRandSkill( values, pMount->selfSkillNum );

            
            for ( ItrSkillIds it = result.begin(); it != result.end(); ++it )
            {
                mount.skillInfo.AddSkill(*it, 1, SMountItem::MICD_PassiveSkillIndex );
            }
        }
    }

    randNum = theRand.rand32() % RAND_NUM;
    if ( randNum <= pMount->masterSkillRate )
    {
        SkillIds values;
        SkillIds result;
        for ( int i=0; i<ItemDefine::SDrome::DCD_MASTERSKILLIDCOUNT; ++i)
        {
            if ( pMount->masterSkillId[i] == 0)
            { break; }
            values.push_back( pMount->masterSkillId[i] );
        }        

        if ( !values.empty())
        {
            result = GetRandSkill( values, pMount->masterSkillNum );

            ItrSkillIds it    = result.begin();
            ItrSkillIds itEnd = result.end();
            for ( ; it!=itEnd; ++it )
            {
                mount.skillInfo.AddSkill(*it, 1, SMountItem::MICD_PassiveSkillIndex );
            }
        }
    }

    randNum = theRand.rand32() % RAND_NUM;
    if ( randNum <= pMount->masterUseSkillRate )
    {
        SkillIds values;
        SkillIds result;
        for ( int i=0; i<ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT; ++i)
        {
            if ( pMount->masterUseSKillId[i] == 0)
            { break; }
            values.push_back( pMount->masterUseSKillId[i] );
        }

        if ( !values.empty())
        {
            result = GetRandSkill( values, pMount->masterUseSkillNum );

            ItrSkillIds it    = result.begin();
            ItrSkillIds itEnd = result.end();
            for ( ; it!=itEnd; ++it )
            {
                mount.skillInfo.AddSkill(*it, 1, SMountItem::MICD_InitiativeSkillIndex );
            }
        }
    }
    return true;
}

void MountManager::Update( unsigned long elapsTime )
{   
    if (  _pMountItems == NULL || _pGamePlayer == NULL )
    { return; }

    if ( _pGamePlayer->GetRideId() <= InvalidLogicNumber )
    { return; }

    _activeSkillBag.Update();

    if ( _pMountConfig != NULL && _pMountConfig->stMaxRange != 0 )
    {  
        if ( !IsInRideRange( _pMountConfig->stMaxRange ) )
        {
            if ( !_xTimer.IsStart() )
            { 
                _xTimer.StartTimer( HQ_TimeGetTime(), 10 * ONE_SEC ); 
                _dwUnRideTime = HQ_TimeGetTime() + 10 * ONE_SEC;
                _dwLastTipsTime = HQ_TimeGetTime();
            }

            if ( _xTimer.DoneTimer() )
            { _pGamePlayer->DoRide( -1 ); }

            if( _xTimer.IsStart() && GameTime::IsPassCurrentTime( _dwLastTipsTime, ONE_SEC ) )
            {
                int nSec = ( _dwUnRideTime - HQ_TimeGetTime() + 200 ) / ONE_SEC;
                _pGamePlayer->SendErrorToClient( ER_MountMaxRangeTimer, nSec );
                _dwLastTipsTime = HQ_TimeGetTime();
            }
        }
        else
        {
            if ( _xTimer.IsStart() )
            {
                _pGamePlayer->SendErrorToClient( ER_MountBackMaxRange );
                _xTimer.StopTimer();
            }
        }
    }
}

void MountManager::RefreshMountData( unsigned long elapsTime )
{
    if ( _pMountItems == NULL || _pGamePlayer == NULL )
    { return; }

    if ( _activeIndex >= 0 && _activeIndex < _nMountCount )
    { // 有激活的坐骑
        _accumulateActionTime += elapsTime; 

        if ( _accumulateActionTime > CD_MOUNT_HP_CONSUME_TIME )
        {
             _accumulateActionTime = 0; // 清空
            if ( InvalidLogicNumber == _pMountItems[_activeIndex].baseInfo.id )
            { return; }

            // 开始扣坐骑生命
            if ( _pMountItems[_activeIndex].baseInfo.hp >= MOUNT_HP_CONSUME )
            { _pMountItems[_activeIndex].baseInfo.hp -= MOUNT_HP_CONSUME; }
            else
            { _pMountItems[_activeIndex].baseInfo.hp  = MOUNT_LOWEST_ACTIVE_HP; }
            
            UpdateMountHP(_activeIndex);

            if ( _pMountItems[_activeIndex].baseInfo.hp <= MOUNT_LOWEST_ACTIVE_HP )
            { // 坐骑生命小于0 
                if ( _activeMountBeRiding )
                { 
                    _pGamePlayer->DebugLog("RefreshMountData DoRide( -1 )  ");
                    _pGamePlayer->DoRide( -1 ); 
                }

                MsgChangeDrome changedrome;
                changedrome.header.stID = _pGamePlayer->GetID();
                changedrome.ucOpType    = MsgChangeDrome::EOT_UnActive;
                changedrome.nIndex      = _activeIndex;
                GettheServer().SendMsgToSingle( &changedrome, _pGamePlayer );

                //清除当前出战战马状态
                _activeSkillBag.SaveSkillColdTime();
                ClearPassiveSkillAffect();
                SetMountActiveStatus( _activeIndex, false );
                ApplyMountAttributeToChar( false, true );
            }
        }
    }
}

void MountManager::SetAccumulateActionTime(unsigned long dwTime)
{
    if ( _activeIndex >= 0)
    { _accumulateActionTime = dwTime; }
}

long MountManager::SetMountActiveStatus( int nIndex, bool bActive )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    // 下标是否超出
    if ( nIndex < 0 || nIndex >= _nMountCount )
    { return ER_IndexOutOfRange;}

    // 此位置的坐骑是否不存在
    if ( _pMountItems[nIndex].baseInfo.id == InvalidLogicNumber )
    { return ER_NullPointer; }

    if ( bActive )
    { // 出战
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pMountItems[nIndex].baseInfo.id );
        if ( pMountConfig == NULL )
        { return ER_InMountConfigNotExist; }

        if ( _pGamePlayer == NULL )
        { return ER_Failed; }

        // 主人的等级是否适合携带
        if ( _pGamePlayer->GetLevel() < pMountConfig->takeLevel )
        { return ER_MountTakeLevelNotEnough; }
        
        // 目标坐骑的坐骑生命是否足够
        if ( _pMountItems[nIndex].baseInfo.hp <= MOUNT_LOWEST_ACTIVE_HP)
        { return ER_NotEnoughEnjoyment; }

        _pMountItems[nIndex].baseInfo.isActive = AT_Active;
        _pMountItems[nIndex].baseInfo.hp -= 1;
        _activeIndex = nIndex;
    }
    else
    { // 不出战
        _pMountItems[nIndex].baseInfo.isActive = AT_NotActive;
        _activeIndex = -1;
    }

    // 纠正所有可能出战的做题
    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
        { break; }

        if ( i != nIndex )
        { _pMountItems[i].baseInfo.isActive = AT_NotActive; }
    }
    _accumulateActionTime = 0;
    return ER_Success;
}

void MountManager::UpdateMountHP(short nIndex)
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return ; }

    if (nIndex >= 0 && nIndex < ITEM_MOUNT_MAXCOUNT )
    {
        // 发属性给客户端, DWROD  0xff ffffff 低24位是活力值得 高8位是坐骑的索引值
        if (_pMountItems[nIndex].baseInfo.id != InvalidLogicNumber)
        {
            DWORD nHP = 0;
            nHP  = nIndex << 24;
            nHP |= _pMountItems[nIndex].baseInfo.hp;
            _pGamePlayer->ChangeAttr( CharAttr_CurMountHP, nHP, true );
        }
    }
}

bool MountManager::SetActiveBeRiding( bool bBeRiding )
{
    if ( bBeRiding && _activeIndex < 0 )
        return false;

    _activeMountBeRiding = bBeRiding;
    return true;
}

int MountManager::GetActiveMountId()
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return -1; }

    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
            break;
        if ( _pMountItems[i].baseInfo.isActive == AT_Active)
            return _pMountItems[i].baseInfo.id;
    }

    return -1;
}

bool MountManager::IsMountFull()
{
	for ( int i=0; i<_nMountCount; ++i )
	{
		if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
			return false;
	}

	return true;
}

long MountManager::PushMount( const SMountItem& mountItem )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
        {
            _pMountItems[i] = mountItem;
            if ( _pGamePlayer )
            { 
				//_pGamePlayer->Log("得到坐骑MountId[%d] BigId[%I64u] ", mountItem.baseInfo.id,  mountItem.baseInfo.guid );
				_pGamePlayer->Log(theXmlString.GetString(eServerLog_Getmount), mountItem.baseInfo.id,  mountItem.baseInfo.guid );
			
			}
            
            return ER_Success;
        }
    }
    return ER_Failed;
}

long MountManager::PopMount( int nIndex, bool& isActiveIndex )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return ER_Failed; }

    if ( nIndex < 0 || nIndex >= _nMountCount )
    { return ER_Failed; }

    if ( _pMountItems[ nIndex ].baseInfo.id == InvalidLogicNumber )
    { return ER_Failed; }

    // 是否放生了出战的坐骑
    if ( _pMountItems[ nIndex ].baseInfo.isActive == AT_Active )
    {
        isActiveIndex   = true;
        _activeIndex    = -1;
        SetActiveBeRiding( false );
    }

    if ( _pGamePlayer )
    { 
		//_pGamePlayer->Log("放生坐骑MountId[%d] BigId[%I64u]", _pMountItems[ nIndex ].baseInfo.id,  _pMountItems[ nIndex ].baseInfo.guid );
		_pGamePlayer->Log(theXmlString.GetString(eServerLog_Delmount), _pMountItems[ nIndex ].baseInfo.id,  _pMountItems[ nIndex ].baseInfo.guid );
	
	}

    // 删除这个位置的马
    _pMountItems[ nIndex ].baseInfo.Reset();
    _pMountItems[ nIndex ].skillInfo.Reset();

    // 整理 后面的往前靠
    for ( int i=nIndex, I=nIndex+1; i<_nMountCount; ++i, ++I )
    {  
        // 如果已经到最后了跳出 通过I来判断
        if ( I >= _nMountCount )
        { break; }

        // 如果i已经是最后一个了 通过I来判断
        if ( _pMountItems[I].baseInfo.id == InvalidLogicNumber )
        { break; }

        _pMountItems[i] = _pMountItems[I];

        // 清掉排在后面的数据
        _pMountItems[I].baseInfo.Reset();
        _pMountItems[I].skillInfo.Reset();
    }

    // 刷新一下 _activeIndex 有可能删除中间位置的坐骑 位置有移位
    UpdateActiveIndex();

    return ER_Success;
}

long MountManager::PopMountByBigId( __int64 nBigId, bool& bActiveIndex )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer  )
    { return ER_Failed; }

    // 找到对应bigId的下标
    int nIndex = -1;
    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.guid == nBigId && _pMountItems[i].baseInfo.id != InvalidLogicNumber)
        {   
            nIndex = i;
            break;
        }
    }

    if ( nIndex == -1 )
    { return ER_Failed; }

    // 删除坐骑
    return PopMount( nIndex, bActiveIndex );
}

int MountManager::GetMountEmptyCount()
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer  )
    { return 0; }

    int nEmptyCount = 0;
    for ( int i = 0; i < _nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
        { ++nEmptyCount;}
    }
    return nEmptyCount;
}

SMountItem* MountManager::GetMountByGuid( __int64 nBigId )
{  
    if ( _pMountItems == NULL || NULL == _pGamePlayer  )
    { return NULL; }

    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.guid == nBigId && _pMountItems[i].baseInfo.id != InvalidLogicNumber )
        {   
            return &_pMountItems[i];
        }
    }
    return NULL;
}

int MountManager::GetMountIndexByGuid( __int64 nBigId )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer  )
    { return -1; }

    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.guid == nBigId && _pMountItems[i].baseInfo.id != InvalidLogicNumber )
        {   
            return i;
        }
    }
    return -1;
}

__int64 MountManager::GetNewBigID()
{   
    const int nCount = 3;
    for ( int i=0; i<nCount; ++i )
    {
        __int64 nBigId = HelperFunc::CreateID();
        if ( !GetMountByGuid( nBigId ) )
        { return nBigId; }
    }
    return -1;
}

void MountManager::AddActiveMountExp( int rewardExp )
{
	return ; //不需要经验了，改成强化 lrt

    if ( _pMountItems == NULL || _activeIndex < 0 || NULL ==  _pGamePlayer)
    { return; }

    if ( _activeIndex >= _nMountCount)
    {
        _activeIndex         = -1;
        _activeMountBeRiding = false;
    }

    SMountItem* pCurrentMount = &_pMountItems[_activeIndex];

    if (pCurrentMount == NULL)
    { return; }

    //坐骑等级超过玩家5级后，将不再获得经验升级
    if ( pCurrentMount->baseInfo.level >= _pGamePlayer->GetLevel() + CD_MOUNT_LEVEL_OVERTOP_MAX )
    { return; }

    rewardExp = rewardExp * ( _pGamePlayer->GetExpChangePer()                );
    rewardExp = rewardExp * ( theRunTimeData.g_nExpPer  * DEF_PERCENT        );
    rewardExp = rewardExp * ( _pGamePlayer->_buffManager.GetExpAddMul() + 1  );

    AddMountExp( _activeIndex, rewardExp );
}

bool MountManager::AddMountExp( int nIndex, int iAddExp )
{
	return false; //不需要经验了，改成强化 lrt

    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return false; }

    if ( iAddExp <= 0 )
    { return false; }

    SMountItem* pCurrentMount = GetMountByIndex(nIndex);
    if ( pCurrentMount == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotHaveThisMount;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    //坐骑等级超过玩家5级后，将不再获得经验升级
    if ( pCurrentMount->baseInfo.level >= _pGamePlayer->GetLevel() + CD_MOUNT_LEVEL_OVERTOP_MAX )
    { return false; }

    __int64 newExp = pCurrentMount->baseInfo.exp + iAddExp;
    int nNewLevel = theExpStage.GetMountLevel( newExp );

    pCurrentMount->baseInfo.exp = newExp;
    //MsgCharAttrChanged Change;
    //Change.iChangeCount = 0;
    //Change.AddAttrInt64Change( CharAttr_MountExp,       pCurrentMount->baseInfo.exp );
    ////Change.AddAttrInt64Change( CharAttr_MountCurGetExp, rewardExp );
    //if( Change.iChangeCount > 0 )
    //{
    //    Change.header.stID = _pGamePlayer->GetID();
    //    Change.CaluLength();
    //    GettheServer().SendMsgToSingle( &Change, _pGamePlayer);
    //}

    if ( nNewLevel != pCurrentMount->baseInfo.level )
    { // 级别改变

        int nOldLevel = pCurrentMount->baseInfo.level;
        int nAddLevel = nNewLevel - nOldLevel;
        pCurrentMount->baseInfo.level += nAddLevel;

        if ( pCurrentMount->baseInfo.level > _pGamePlayer->GetLevel() + CD_MOUNT_LEVEL_OVERTOP_MAX )
        { 
            pCurrentMount->baseInfo.level = _pGamePlayer->GetLevel() + CD_MOUNT_LEVEL_OVERTOP_MAX; 
            pCurrentMount->baseInfo.exp   = theExpStage.GetMountLevelupExp(pCurrentMount->baseInfo.level) - 1;
        }

        int nAddPotentialPoint = ( pCurrentMount->baseInfo.level - nOldLevel ) * CD_UPLEVEL_POTENTIALPOINT;
        pCurrentMount->baseInfo.nPotentialPoint += nAddPotentialPoint;

        // 重新计算属性
        pCurrentMount->baseInfo.hp    = CD_MOUNT_HP_MAX_VALUE /* * nNewLevel*/;
        pCurrentMount->baseInfo.hpMax = CD_MOUNT_HP_MAX_VALUE /* * nNewLevel*/;
        pCurrentMount->baseInfo.UpdateCurrentAttribute();

        if ( nIndex == _activeIndex )
        { 
			//todo:这儿有问题，坐骑获得经验后，人物移动速度被重置了。
			_pGamePlayer->RefreshMountAttr();
			if (_activeMountBeRiding)
			{
				ItemDefine::SDrome* pItemDrome = GettheItemDetail().GetDromeByID( pCurrentMount->GetMountID() );
				_pGamePlayer->GetCharFightAttr()->moveSpeed.pet += pItemDrome->fSpeed;
				_pGamePlayer->GetCharFightAttr()->moveSpeed.UpdateFinal();
			}
			_pGamePlayer->SendCharAttibuteToClient();
			//ApplyMountAttributeToChar( false, true ); 
		}
        
        if (pCurrentMount->baseInfo.quality >= ItemDefine::EMQ_Good)
        { _pGamePlayer->_achieveManager.UpdateTriggerByValueType( EAT_MountLevel , pCurrentMount->baseInfo.level ); }
    }

    // 下发消息
    MsgUpdateMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount = *pCurrentMount;
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);

    return true;
}

void MountManager::UpdateActiveIndex()
{
    if ( _pMountItems == NULL )
    { return; }

    // 更新出战
    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber )
            break;
        if ( _pMountItems[i].baseInfo.isActive == AT_Active )
        {
            _activeIndex = i;
            UpdateActiveSkillBag();
            break;
        }
    }
}

void MountManager::UpdateActiveSkillBag()
{
    //if ( _pMountItems == NULL || _activeIndex < 0)
    //    return;

    //_activeSkillBag.Init( _pMountItems[_activeIndex].skillInfo.skills, SMountItem::MICD_MaxSkillCount, true );

    if ( _pGamePlayer->GetRideId() > InvalidLogicNumber )
    {
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
        if ( pMountConfig == NULL )
        { return; }

        for ( int i=0; i<= ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT; ++i )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pMountConfig->masterUseSKillId[i], 1 );
            if ( pSkill == NULL )
            { continue; }

            _pGamePlayer->LearnSkill( pSkill->ustItemID, 1, false, false, false );
        }
    }
}

void MountManager::RemoveActiveSkillBag()
{
    if ( _pGamePlayer->GetRideId() > InvalidLogicNumber )
    {
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
        if ( pMountConfig == NULL )
        { return; }

        for ( int i=0; i<= ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT; ++i )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pMountConfig->masterUseSKillId[i], 1 );
            if ( pSkill == NULL )
            { continue; }

            _pGamePlayer->ForgetSkill( pSkill->ustItemID, false );
        }
    }
}

void MountManager::ClearPassiveSkillAffect()
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return ; }

    if ( GetActiveMountId() > InvalidLogicNumber )
    {
        for ( int nIndex = 0; nIndex < SMountItem::MICD_MaxSkillCount; ++nIndex )
        {
            SCharSkill* pMountSkill = _activeSkillBag.GetSkillByIndex( nIndex );
            if ( pMountSkill == NULL || pMountSkill->ustSkillID == InvalidLogicNumber )
            { continue; }

            ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pMountSkill->ustSkillID, pMountSkill->stSkillLevel);
            if( pSkillConfig == NULL )
            { continue; }

            if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_MountPassive )
            { continue; }

            _pGamePlayer->GetBuffManager()->ClearBuffByBuffIdLevel( pSkillConfig->ustMeAddStatusID[0] , pSkillConfig->ustMeAddStatusLevel[0]);
            _pGamePlayer->GetBuffManager()->ClearBuffByBuffIdLevel( pSkillConfig->ustMeAddStatusID[1] , pSkillConfig->ustMeAddStatusLevel[1]);
        }

        _pGamePlayer->OnBuffStatusChanged( true );
    }
}

int MountManager::RestoreMountHP(bool bIsNeedMoney)
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return ER_Failed; }

    //是否需要金钱
    if ( bIsNeedMoney )
    {
        int nCostMoney = 0;
        for ( int i=0; i<_nMountCount; ++i )
        {
            if ( InvalidLogicNumber == _pMountItems[i].baseInfo.id )
            { break; }

            nCostMoney +=  CD_MOUNT_HP_MAX_VALUE - _pMountItems[i].baseInfo.hp ;
        }

        if ( nCostMoney == 0 )
        { return ER_Failed; }

        nCostMoney = (int) ceil( nCostMoney * MOUNT_HP_RESTORE_COST * DEF_TENTH  ) ;

        if (nCostMoney > _pGamePlayer->GetJiaoZiMoney())
        {
            MsgAckResult msg;
            msg.result = ER_NoMoneyToMountRestore;
            GettheServer().SendMsgToSingle( &msg, _pGamePlayer );
            return ER_Failed;
        }

        _pGamePlayer->OperateJiaoZi( EOT_Sub, nCostMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_RestoreMountHP );
    }

    for ( int i=0; i<_nMountCount; ++i )
    {
        if ( InvalidLogicNumber == _pMountItems[i].baseInfo.id )
        { break; }

        _pMountItems[i].baseInfo.hp = CD_MOUNT_HP_MAX_VALUE;

        MsgUpdateMount msg;
        msg.header.stID = _pGamePlayer->GetID();
        msg.mount = _pMountItems[i];
        GettheServer().SendMsgToSingle( &msg, _pGamePlayer);
    }

    return ER_Success;
}

bool MountManager::AddMountHp( int nIndex, int hp )
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return false; }

    SMountItem* pMount = GetMountByIndex(nIndex);
    if ( pMount == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotHaveThisMount;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    if (pMount->baseInfo.hp >= pMount->baseInfo.hpMax)
    { return false; }

    pMount->baseInfo.hp += hp;
    if ( pMount->baseInfo.hp > pMount->baseInfo.hpMax)
    { pMount->baseInfo.hp = pMount->baseInfo.hpMax; }

    MsgUpdateMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount = *pMount;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}

// 坐骑繁衍
int MountManager::MountBreed(int64 masterGuid,int64 assistantGuid)
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return ER_Failed; }

    if ( masterGuid == assistantGuid )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountData;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    SMountItem* pMasterMount = GetMountByGuid(masterGuid);
    SMountItem* pAssistantMount = GetMountByGuid(assistantGuid);
    if ( NULL == pMasterMount || NULL == pAssistantMount )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountData;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    ItemDefine::SDrome* pMasterDrome = GettheItemDetail().GetDromeByID( pMasterMount->baseInfo.id );
    ItemDefine::SDrome* pAssistantDrome = GettheItemDetail().GetDromeByID( pAssistantMount->baseInfo.id );
    if ( NULL == pMasterDrome || NULL == pAssistantDrome ) 
    { 
        MsgAckResult msg;
        msg.result = ER_ErrorMountData;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed; 
    }
    
    ItemDefine::SDrome* pBreedDrome = GettheItemDetail().GetDromeByID( pMasterMount->baseInfo.nextId );
    if ( NULL == pBreedDrome ) 
    { 
        MsgAckResult msg;
        msg.result = ER_ErrorMountNoNextId;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed; 
    }

    if ( !pMasterMount->IsCanBreed() || !pAssistantMount->IsCanBreed() )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountCannotBreed;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    if (pMasterMount->baseInfo.level < MOUNT_BREED_MASTER_LEVEL )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountMasterLevel;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    if (pMasterDrome->stType !=  pAssistantDrome->stType )
    {
        MsgAckResult msg;
        msg.result = ER_MountTypeCannotBreed;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    if (_pGamePlayer->GetJiaoZiMoney() < MOUNT_BREED_MONEY)
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountMasterMoney;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return ER_Failed;
    }

    ClearPassiveSkillAffect();

    SMountItem mount;
    mount.baseInfo.id           = pBreedDrome->stId;
    mount.baseInfo.guid         = GetNewBigID();
    mount.baseInfo.isActive     = MountManager::AT_NotActive;
    mount.baseInfo.generation   = pMasterMount->baseInfo.generation + 1;
    mount.baseInfo.nextId       = 0;
    mount.baseInfo.quality      = pBreedDrome->quality;
    strncpy_s( mount.baseInfo.szName, sizeof(mount.baseInfo.szName), pBreedDrome->GetName(), sizeof(mount.baseInfo.szName) -1 );    

    // 属性的初始化
    InitMountAttribute( mount );

    //2代坐骑，继承了主骑乘的资质属性+5、技能，继承副坐骑基础属性+5
    for (int i=0;i<EBaseAttr_MaxSize;++i)
    {
        mount.baseInfo.baseAttribute[i] = pAssistantMount->baseInfo.baseAttribute[i] + 5;
        mount.baseInfo.aptitudeAttribute[i] = pMasterMount->baseInfo.aptitudeAttribute[i] + 5;
    }

    mount.baseInfo.UpdateCurrentAttribute();

    // 技能
    mount.skillInfo.initiativeSkillNumber = pMasterMount->skillInfo.initiativeSkillNumber;
    for (int i=0;i<SMountItem::MICD_MaxSkillCount;++i)
    {
        mount.skillInfo.skills[i].ustSkillID   = pMasterMount->skillInfo.skills[i].ustSkillID;
        mount.skillInfo.skills[i].stSkillLevel = pMasterMount->skillInfo.skills[i].stSkillLevel;
    }

    // 删除主副坐骑
    bool bActiveIndex = false;

    MsgChangeDrome changeMasterDrome;
    changeMasterDrome.header.stID = _pGamePlayer->GetID();
    changeMasterDrome.ucOpType    = MsgChangeDrome::EOT_Discard;
    changeMasterDrome.nIndex      = GetMountIndexByGuid(pMasterMount->baseInfo.guid);
    changeMasterDrome.guid        = pMasterMount->baseInfo.guid;
	changeMasterDrome.nMountLevel = pMasterMount->baseInfo.level;

    MsgChangeDrome changeAssistantDrome;
    changeAssistantDrome.header.stID = _pGamePlayer->GetID();
    changeAssistantDrome.ucOpType    = MsgChangeDrome::EOT_Discard;
    changeAssistantDrome.nIndex      = GetMountIndexByGuid(pAssistantMount->baseInfo.guid);
    changeAssistantDrome.guid        = pAssistantMount->baseInfo.guid;
	changeAssistantDrome.nMountLevel = pAssistantMount->baseInfo.level;

    bActiveIndex = false;
    if ( PopMountByBigId( masterGuid, bActiveIndex ) == ER_Success)
    {
        GettheServer().SendMsgToSingle( &changeMasterDrome, _pGamePlayer );
    }

    bActiveIndex = false;
    if ( PopMountByBigId( assistantGuid, bActiveIndex ) == ER_Success)
    {
        GettheServer().SendMsgToSingle( &changeAssistantDrome, _pGamePlayer );
    }

    // 添加新坐骑
    int  nResult = PushMount( mount );
    if ( nResult != ER_Success )    
    { return ER_Failed; }

    //扣除金钱
    _pGamePlayer->OperateJiaoZi( EOT_Sub, MOUNT_BREED_MONEY, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_MountBreed);

    _pGamePlayer->_achieveManager.UpdateTriggerByValueType( EAT_VariationMount , pBreedDrome->takeLevel );

    MsgGetMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount       = mount;
    msg.usResult    = ER_Success;
    GettheServer().SendMsgToSingle( &msg, _pGamePlayer);

    MsgMountAckBreed ackmsg;
    msg.header.stID = _pGamePlayer->GetID();
    GettheServer().SendMsgToSingle( &ackmsg, _pGamePlayer);

    UpdateActiveSkillBag();
    ApplyMountAttributeToChar( false, true );

    return ER_Success;
}

bool MountManager::SetInitiativeSkill( int nIndex, uint8 num )
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return false ; }

    SMountItem* pMount = GetActiveMount();
    if ( NULL == pMount )
    {
        MsgAckResult msg;
        msg.result = ER_NotActiveMount;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    if ( num > ( ITEM_MOUNT_MAXCOUNT / 2) )
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountSkillNumber;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    if (pMount->skillInfo.initiativeSkillNumber >= num)
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountSkillNumber;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    pMount->skillInfo.initiativeSkillNumber = num;

    MsgUpdateMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount = *pMount;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}


bool MountManager::ForgetInitiativeSkill(  int nIndex, uint8 nSkillIndex )
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return false; }

    SMountItem* pMount = GetActiveMount();
    if ( NULL == pMount )
    {
        MsgAckResult msg;
        msg.result = ER_NotActiveMount;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    if (pMount->skillInfo.skills[nSkillIndex].ustSkillID == InvalidLogicNumber)
    {
        MsgAckResult msg;
        msg.result = ER_ErrorMountSkillForget;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    pMount->skillInfo.skills[nSkillIndex].Reset();
    
    MsgUpdateMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount = *pMount;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}

int MountManager::GetActiveMountLevel()
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return -1; }

    SMountItem* pMount = GetActiveMount();
    if ( NULL == pMount )
    { return -1; }

    return pMount->baseInfo.level;
}

bool MountManager::ClearMountPotential( int nIndex )
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return false; }

    SMountItem* pMount = GetMountByIndex(nIndex);
    if ( pMount == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotHaveThisMount;
        GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
        return false;
    }

    int nPotentialPoint = 0;

    for (int i=0;i<EBaseAttr_MaxSize;++i)
    {
        nPotentialPoint += pMount->baseInfo.potentialAttribute[i];
        pMount->baseInfo.potentialAttribute[i] = 0;
    }

    pMount->baseInfo.nPotentialPoint += nPotentialPoint;
    pMount->baseInfo.UpdateCurrentAttribute();

    MsgUpdateMount msg;
    msg.header.stID = _pGamePlayer->GetID();
    msg.mount = *pMount;
    GettheServer().SendMsgToSingle(&msg,_pGamePlayer);
    return true;
}

void MountManager::ApplyMountAttributeToChar( bool bInit, bool bSendMessage )
{
    if (NULL == _pMountItems || NULL == _pGamePlayer || _nMountCount <= 0)
    { return ; }

    _pGamePlayer->ClearAllBaseAttrByPart ( ECustomDataPart_pet );
    _pGamePlayer->ClearAllFightAttrByPart( ECustomDataPart_pet );

    if ( GetActiveMountId() > InvalidLogicNumber )
    {
        for ( int nIndex = 0; nIndex < SMountItem::MICD_MaxSkillCount; ++nIndex )
        {
            SCharSkill* pMountSkill = _activeSkillBag.GetSkillByIndex( nIndex );
            if ( pMountSkill == NULL || pMountSkill->ustSkillID == InvalidLogicNumber )
            { continue; }

            ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pMountSkill->ustSkillID, pMountSkill->stSkillLevel);
            if( pSkillConfig == NULL )
            { continue; }

            if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_MountPassive)
            { continue; }

            _pGamePlayer->ApplyBufferStatus( pSkillConfig->ustMeAddStatusID[0], pSkillConfig->ustMeAddStatusLevel[0], _pGamePlayer->GetID(), SCharBuff::StatusEventType_Mount, 0);
            _pGamePlayer->ApplyBufferStatus( pSkillConfig->ustMeAddStatusID[1], pSkillConfig->ustMeAddStatusLevel[1], _pGamePlayer->GetID(), SCharBuff::StatusEventType_Mount, 0);
        }

        // 初始化的时候只作用不Recale,因为最后会做
        if ( !bInit )
        { _pGamePlayer->OnBuffStatusChanged( bSendMessage ); }
    }

    //SMountItem* pActiveMount = GetActiveMount();
    //if ( NULL != pActiveMount )
    //{ 
    //    // 作用一级属性
    //    for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
    //    { 
    //        _pGamePlayer->GetBaseAttr(i)->pet += _pGamePlayer->_buffManager.GetAddMountBaseAttr(i);

    //        //公式为 马匹属性 * 对应资质 / 100 * 技能影响率
    //        int nMountAttr =  pActiveMount->baseInfo.currentAttribute[i] * pActiveMount->baseInfo.aptitudeAttribute[i] * DEF_PERCENT ;
    //        _pGamePlayer->GetBaseAttr(i)->pet += nMountAttr * _pGamePlayer->_buffManager.GetAddMountBaseAttrPer(i)   * DEF_PERCENT ; 

    //        // 一级属性作用二级属性
    //        ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_pet, *_pGamePlayer->GetBaseAttr( i ), _pGamePlayer->GetProfession(), *_pGamePlayer->GetCharFightAttr() );
    //    }
    //}

    if (_activeMountBeRiding)
    {
        ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( GetActiveMountId() );
        if ( pMount == NULL )
        { return; }

        _pGamePlayer->GetCharFightAttr()->moveSpeed.pet = pMount->fSpeed;
        _pGamePlayer->GetCharFightAttr()->moveSpeed.UpdateFinal();
    }
    else
    {
        _pGamePlayer->GetCharFightAttr()->moveSpeed.pet = 0;
        _pGamePlayer->GetCharFightAttr()->moveSpeed.UpdateFinal();
    }

    if ( !bInit )
    { _pGamePlayer->RecalcBaseProperty( false, BV_NotFullHp, bSendMessage ? BV_SendMessage : BV_NotSendMessage, EWRP_Skill );}
}

SMountItem* MountManager::GetActiveMount()
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer || _activeIndex < 0 )
        return NULL;

    return &_pMountItems[_activeIndex];
}

SMountItem* MountManager::GetMountByIndex( int nIndex )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer || nIndex < 0  || nIndex > ITEM_MOUNT_MAXCOUNT )
        return NULL;
    
    if ( _pMountItems[nIndex].baseInfo.id == InvalidLogicNumber || _pMountItems[nIndex].baseInfo.guid == 0 )
        return NULL;

    return &_pMountItems[nIndex];
}

bool MountManager::HasMount( uint16 nMountId )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer )
    { return false; }

    if ( nMountId == InvalidLogicNumber )
    { return false; }

    for (int i = 0; i< _nMountCount; ++i )
    {
        if ( _pMountItems[i].baseInfo.id == InvalidLogicNumber || _pMountItems[i].baseInfo.guid == 0 )
        { continue; }

        if (_pMountItems[i].baseInfo.id == nMountId)
        { return true; }
    }

    return false;
}

void MountManager::SetLastRidePos( int mapId, int posX, int posY )
{
    _mapId = mapId;
    _posX  = posX ;
    _posY  = posY ;
}

bool MountManager::IsInRideRange ( int nRange )
{
    if ( _mapId != _pGamePlayer->GetMapID() )
    { return false; }

    D3DXVECTOR3 vecDistance( _pGamePlayer->GetFloatX() - _posX, _pGamePlayer->GetFloatY() - _posY, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    if ( fDistance >= nRange  )
    { return false; }

    return true;
}

bool MountManager::ApplyMountStatusToMaster()
{
    if ( _pGamePlayer->GetRideId() > InvalidLogicNumber )
    {
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
        if ( pMountConfig == NULL )
        { return false; }

        _pGamePlayer->ApplyBufferStatus ( pMountConfig->nAddStatusID, 1, _pGamePlayer->GetID(), SCharBuff::StatusEventType_Mount, 0) ;
        _pGamePlayer->OnBuffStatusChanged( true );
        return true;
    }

    return false;
}

void MountManager::ClearMountStatusToMaster()
{
    if ( _pGamePlayer->GetRideId() > InvalidLogicNumber )
    {
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
        if ( pMountConfig == NULL )
        { return; }

        _pGamePlayer->_buffManager.ClearBuffByBuffId( pMountConfig->nAddStatusID );
        _pGamePlayer->OnBuffStatusChanged( true );
    }
}

void MountManager::InitMultiMount( int nCarryNum ) 
{ 
    _nMaxCarryNum = nCarryNum;
    _nCurCarryNum = 0;
    _players.resize( nCarryNum, InvalidGameObjectId ); 
}

void MountManager::SendBeCarryPlayersTo( GamePlayer* pTarget )
{
    char szMsgBuff[1024] = {0};

    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        GameObjectId id = (*it);
        if ( id == InvalidGameObjectId )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            *it = InvalidGameObjectId;
            continue;
        }

        GettheServer().SendMsgToSingle( pChar->FirstSightOnMe( szMsgBuff, sizeof(szMsgBuff)), pTarget );
    }
}

uint32 MountManager::GotOnMultiMount( GameObjectId playerId )
{
    //SMountItem* pMountItem = GetActiveMount();
    //if (pMountItem == NULL)
    //{ return ER_Failed; }

    if ( !IsDriveMultiMount() )
    { return ER_Failed; }

    int8 curPos = 0;
    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        if ( *it != InvalidGameObjectId )
        {
            ++curPos;
            continue;
        }

        if ( *it == playerId )
        { return ER_Failed; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( playerId );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        *it = playerId;

        GamePlayer* pPlayer = (GamePlayer*)pChar;
        pPlayer->SetRideId ( _pGamePlayer->GetRideId() );
		pPlayer->SetRideLevel( _pGamePlayer->GetRideLevel() );
        pPlayer->SetRidePos( curPos );
        pPlayer->SetRideDriverId( _pGamePlayer->GetID() );

        pPlayer->SetFloatXF( _pGamePlayer->GetFloatX() );
        pPlayer->SetFloatYF( _pGamePlayer->GetFloatY() );
        pPlayer->SetDirX( _pGamePlayer->GetDirX() );
        pPlayer->SetDirY( _pGamePlayer->GetDirY() );

        ++_nCurCarryNum;
        return ER_Success;
    }

    return ER_Failed;
}

uint32 MountManager::GotOffMultiMount( GameObjectId playerId )
{
    if ( !IsDriveMultiMount() )
    { return ER_Failed; }

    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        if ( playerId != *it )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        GamePlayer* pPlayer = (GamePlayer*)pChar;

        pPlayer->SetRideId (-1);
		pPlayer->SetRideLevel(0);
        pPlayer->SetRidePos(0);
        pPlayer->SetRideDriverId(InvalidGameObjectId);
        pPlayer->_mountManager.SetActiveBeRiding(false);

        *it = InvalidGameObjectId; 
        --_nCurCarryNum;
        return ER_Success;
    }

    return ER_Failed;
}

void MountManager::GotOffMultiMountExcludeDriver()
{
	if ( !IsDriveMultiMount() )
	{ return; }

	PlayerContainerItr it = _players.begin();
	for ( ; it!=_players.end(); ++it )
	{
		if ( _pGamePlayer->GetID() == *it )
		{ continue; }

		BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
		if ( pChar == NULL || !pChar->IsPlayer() )
		{ continue; }

		GamePlayer* pPlayer = (GamePlayer*)pChar;

		pPlayer->SetRideId (-1);
		pPlayer->SetRideLevel(0);
		pPlayer->SetRidePos(0);
		pPlayer->SetRideDriverId(InvalidGameObjectId);
		pPlayer->_mountManager.SetActiveBeRiding(false);

		*it = InvalidGameObjectId; 
		--_nCurCarryNum;	
	}
}

void MountManager::AllPlayerGotOffMultiMount()
{
    if ( !IsDriveMultiMount() )
    { return; }

    // 所有人下大载体
    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end(); ++it )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        GamePlayer* pPlayer = (GamePlayer*)pChar;

        MsgGotOnOffDrome msg;
        msg.type = MsgGotOnOffDrome::EOnOffType_Off;
        msg.driverId = _pGamePlayer->GetID();
        msg.riderId  = pPlayer->GetID();
        msg.pos      = pPlayer->GetRidePos();
        GettheServer().SendMsgToView( &msg, pPlayer->GetID() );

        pPlayer->SetRideId (-1);
		pPlayer->SetRideLevel(0);
        pPlayer->SetRidePos(0);
        pPlayer->SetRideDriverId(InvalidGameObjectId);
        pPlayer->_mountManager.SetActiveBeRiding(false);
    }

    _players.clear();
    _nMaxCarryNum = 0;
    _nCurCarryNum = 0;
}

void MountManager::OnMultiMountMoving()
{
    if ( !IsDriveMultiMount() )
    { return; }

    PlayerContainerItr it = _players.begin();
    for ( ; it!=_players.end();  )
    {
        GameObjectId id = (*it);
        if ( id == InvalidGameObjectId )
        { 
            ++it;
            continue; 
        }
 
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( id );
        if ( pChar == NULL )
        {
            it = _players.erase( it );
            continue;
        }

        if (pChar->GetID() == _pGamePlayer->GetID())
        { 
            ++it;
            continue; 
        }

        pChar->SetFloatXF( _pGamePlayer->GetFloatX() );
        pChar->SetFloatYF( _pGamePlayer->GetFloatY() );
        pChar->SetDirX( _pGamePlayer->GetDirX() );
        pChar->SetDirY( _pGamePlayer->GetDirY() );

		//lyh++ 下两句
		pChar->SetFloatX(_pGamePlayer->GetFloatX());
		pChar->SetFloatY( _pGamePlayer->GetFloatY() );

        ++it;
    }
}

bool MountManager::IsDriveMultiMount()
{
    if (_pGamePlayer == NULL /*|| !_activeMountBeRiding || _nMaxCarryNum == 0*/)
    { return false; }

    if (_pGamePlayer->GetID() != _pGamePlayer->GetRideDriverId())
    { return false; }

    if (_pGamePlayer->GetRideId() <= InvalidLogicNumber)
    { return false; }

    ItemDefine::SDrome* pItemDrome = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
    if( pItemDrome == NULL )
    { return false; }

    if ( pItemDrome->stCarry <= 1 )
    { return false; }

    return true;
};

bool MountManager::IsRideMultiMount()
{
    if (_pGamePlayer == NULL /*|| !_activeMountBeRiding || _nMaxCarryNum == 0*/)
    { return false; }

    if (_pGamePlayer->GetRideId() <= InvalidLogicNumber)
    { return false; }

    ItemDefine::SDrome* pItemDrome = GettheItemDetail().GetDromeByID( _pGamePlayer->GetRideId() );
    if( pItemDrome == NULL )
    { return false; }

    if ( pItemDrome->stCarry <= 1 )
    { return false; }

    return true;
};
