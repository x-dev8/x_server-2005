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

    // ˢ�³�ս�����Id
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

    mount.baseInfo.level        = /*1*/0;	//ǿ����0��ʼ
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

    // ˢ������
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

    // �ȵõ�ϴ�������漴�ܺ�
    unsigned int nTotalProbability = 0;
    for ( int i = 0; i < pMount->arrayProbability.GetSize(); ++i )
    {
        nTotalProbability += pMount->arrayProbability[i];
    }

    if ( nTotalProbability == 0 )
    { return false; }

    // �漴һ����ֵ
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

    // �����ٶȼ���
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
    { // �м��������
        _accumulateActionTime += elapsTime; 

        if ( _accumulateActionTime > CD_MOUNT_HP_CONSUME_TIME )
        {
             _accumulateActionTime = 0; // ���
            if ( InvalidLogicNumber == _pMountItems[_activeIndex].baseInfo.id )
            { return; }

            // ��ʼ����������
            if ( _pMountItems[_activeIndex].baseInfo.hp >= MOUNT_HP_CONSUME )
            { _pMountItems[_activeIndex].baseInfo.hp -= MOUNT_HP_CONSUME; }
            else
            { _pMountItems[_activeIndex].baseInfo.hp  = MOUNT_LOWEST_ACTIVE_HP; }
            
            UpdateMountHP(_activeIndex);

            if ( _pMountItems[_activeIndex].baseInfo.hp <= MOUNT_LOWEST_ACTIVE_HP )
            { // ��������С��0 
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

                //�����ǰ��սս��״̬
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

    // �±��Ƿ񳬳�
    if ( nIndex < 0 || nIndex >= _nMountCount )
    { return ER_IndexOutOfRange;}

    // ��λ�õ������Ƿ񲻴���
    if ( _pMountItems[nIndex].baseInfo.id == InvalidLogicNumber )
    { return ER_NullPointer; }

    if ( bActive )
    { // ��ս
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( _pMountItems[nIndex].baseInfo.id );
        if ( pMountConfig == NULL )
        { return ER_InMountConfigNotExist; }

        if ( _pGamePlayer == NULL )
        { return ER_Failed; }

        // ���˵ĵȼ��Ƿ��ʺ�Я��
        if ( _pGamePlayer->GetLevel() < pMountConfig->takeLevel )
        { return ER_MountTakeLevelNotEnough; }
        
        // Ŀ����������������Ƿ��㹻
        if ( _pMountItems[nIndex].baseInfo.hp <= MOUNT_LOWEST_ACTIVE_HP)
        { return ER_NotEnoughEnjoyment; }

        _pMountItems[nIndex].baseInfo.isActive = AT_Active;
        _pMountItems[nIndex].baseInfo.hp -= 1;
        _activeIndex = nIndex;
    }
    else
    { // ����ս
        _pMountItems[nIndex].baseInfo.isActive = AT_NotActive;
        _activeIndex = -1;
    }

    // �������п��ܳ�ս������
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
        // �����Ը��ͻ���, DWROD  0xff ffffff ��24λ�ǻ���ֵ�� ��8λ�����������ֵ
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
				//_pGamePlayer->Log("�õ�����MountId[%d] BigId[%I64u] ", mountItem.baseInfo.id,  mountItem.baseInfo.guid );
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

    // �Ƿ�����˳�ս������
    if ( _pMountItems[ nIndex ].baseInfo.isActive == AT_Active )
    {
        isActiveIndex   = true;
        _activeIndex    = -1;
        SetActiveBeRiding( false );
    }

    if ( _pGamePlayer )
    { 
		//_pGamePlayer->Log("��������MountId[%d] BigId[%I64u]", _pMountItems[ nIndex ].baseInfo.id,  _pMountItems[ nIndex ].baseInfo.guid );
		_pGamePlayer->Log(theXmlString.GetString(eServerLog_Delmount), _pMountItems[ nIndex ].baseInfo.id,  _pMountItems[ nIndex ].baseInfo.guid );
	
	}

    // ɾ�����λ�õ���
    _pMountItems[ nIndex ].baseInfo.Reset();
    _pMountItems[ nIndex ].skillInfo.Reset();

    // ���� �������ǰ��
    for ( int i=nIndex, I=nIndex+1; i<_nMountCount; ++i, ++I )
    {  
        // ����Ѿ������������ ͨ��I���ж�
        if ( I >= _nMountCount )
        { break; }

        // ���i�Ѿ������һ���� ͨ��I���ж�
        if ( _pMountItems[I].baseInfo.id == InvalidLogicNumber )
        { break; }

        _pMountItems[i] = _pMountItems[I];

        // ������ں��������
        _pMountItems[I].baseInfo.Reset();
        _pMountItems[I].skillInfo.Reset();
    }

    // ˢ��һ�� _activeIndex �п���ɾ���м�λ�õ����� λ������λ
    UpdateActiveIndex();

    return ER_Success;
}

long MountManager::PopMountByBigId( __int64 nBigId, bool& bActiveIndex )
{
    if ( _pMountItems == NULL || NULL == _pGamePlayer  )
    { return ER_Failed; }

    // �ҵ���ӦbigId���±�
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

    // ɾ������
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
	return ; //����Ҫ�����ˣ��ĳ�ǿ�� lrt

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

    //����ȼ��������5���󣬽����ٻ�þ�������
    if ( pCurrentMount->baseInfo.level >= _pGamePlayer->GetLevel() + CD_MOUNT_LEVEL_OVERTOP_MAX )
    { return; }

    rewardExp = rewardExp * ( _pGamePlayer->GetExpChangePer()                );
    rewardExp = rewardExp * ( theRunTimeData.g_nExpPer  * DEF_PERCENT        );
    rewardExp = rewardExp * ( _pGamePlayer->_buffManager.GetExpAddMul() + 1  );

    AddMountExp( _activeIndex, rewardExp );
}

bool MountManager::AddMountExp( int nIndex, int iAddExp )
{
	return false; //����Ҫ�����ˣ��ĳ�ǿ�� lrt

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

    //����ȼ��������5���󣬽����ٻ�þ�������
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
    { // ����ı�

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

        // ���¼�������
        pCurrentMount->baseInfo.hp    = CD_MOUNT_HP_MAX_VALUE /* * nNewLevel*/;
        pCurrentMount->baseInfo.hpMax = CD_MOUNT_HP_MAX_VALUE /* * nNewLevel*/;
        pCurrentMount->baseInfo.UpdateCurrentAttribute();

        if ( nIndex == _activeIndex )
        { 
			//todo:��������⣬�����þ���������ƶ��ٶȱ������ˡ�
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

    // �·���Ϣ
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

    // ���³�ս
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

    //�Ƿ���Ҫ��Ǯ
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

// ���ﷱ��
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

    // ���Եĳ�ʼ��
    InitMountAttribute( mount );

    //2������̳�������˵���������+5�����ܣ��̳и������������+5
    for (int i=0;i<EBaseAttr_MaxSize;++i)
    {
        mount.baseInfo.baseAttribute[i] = pAssistantMount->baseInfo.baseAttribute[i] + 5;
        mount.baseInfo.aptitudeAttribute[i] = pMasterMount->baseInfo.aptitudeAttribute[i] + 5;
    }

    mount.baseInfo.UpdateCurrentAttribute();

    // ����
    mount.skillInfo.initiativeSkillNumber = pMasterMount->skillInfo.initiativeSkillNumber;
    for (int i=0;i<SMountItem::MICD_MaxSkillCount;++i)
    {
        mount.skillInfo.skills[i].ustSkillID   = pMasterMount->skillInfo.skills[i].ustSkillID;
        mount.skillInfo.skills[i].stSkillLevel = pMasterMount->skillInfo.skills[i].stSkillLevel;
    }

    // ɾ����������
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

    // ���������
    int  nResult = PushMount( mount );
    if ( nResult != ER_Success )    
    { return ER_Failed; }

    //�۳���Ǯ
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

        // ��ʼ����ʱ��ֻ���ò�Recale,��Ϊ������
        if ( !bInit )
        { _pGamePlayer->OnBuffStatusChanged( bSendMessage ); }
    }

    //SMountItem* pActiveMount = GetActiveMount();
    //if ( NULL != pActiveMount )
    //{ 
    //    // ����һ������
    //    for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
    //    { 
    //        _pGamePlayer->GetBaseAttr(i)->pet += _pGamePlayer->_buffManager.GetAddMountBaseAttr(i);

    //        //��ʽΪ ��ƥ���� * ��Ӧ���� / 100 * ����Ӱ����
    //        int nMountAttr =  pActiveMount->baseInfo.currentAttribute[i] * pActiveMount->baseInfo.aptitudeAttribute[i] * DEF_PERCENT ;
    //        _pGamePlayer->GetBaseAttr(i)->pet += nMountAttr * _pGamePlayer->_buffManager.GetAddMountBaseAttrPer(i)   * DEF_PERCENT ; 

    //        // һ���������ö�������
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

    // �������´�����
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

		//lyh++ ������
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
