#include "AiCharacter.h"
#include "MonsterBaseEx.h"
#include "GameWorld.h"
#include "ShareData.h"
#include "MonsterCreater.h"
#include "GameDataType.h"
#include "GamePlayer.h"

void AiCharacter::InitLuaScript()
{
    m_bLuaScriptLoaded = false;
    memset( m_nParamValue, 0, sizeof( m_nParamValue ) );

    if ( !RegisterLuaFunction() )
    { return; }


	MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >(this);
	if(pAiChar->GetMonsterID() == 100375)
	{
		int n =0;
		n++;
	}

    try
    {
        if( !m_xLuaScript->LoadFile( GetAILuaScript() ) )
        {
            m_bLuaScriptLoaded = true;
            m_xLuaScript->Call( 0, 0 );
        }
    }
    catch ( LuaPlus::LuaException &e )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script failed:%s", GetCharName(), e.GetErrorMessage() );
        m_bLuaScriptLoaded = false;
    }

    // 初始化脚本函数
    ProcessInitLuaFunction();
}

void AiCharacter::ReleaseLuaScript()
{
    try
    {
        m_xLuaScript->PushNil(); 
    }
    catch ( LuaPlus::LuaException &e )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "Monster %s AI Failed: %s", GetCharName(), e.GetErrorMessage());
        m_bLuaScriptLoaded = false;
    }
}

void AiCharacter::ProcessInitLuaFunction()
{
    if ( !m_bLuaScriptLoaded )
    { return; }

    try
    {
        LuaObject luaobject = m_xLuaScript->GetGlobal( "Event_Init" );
        if( luaobject.IsFunction() )
        { GetLuaFunction( "Event_Init" )(); }
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script Event_Init failed: %s", GetCharName(), e.GetErrorMessage() );
    }
}


void AiCharacter::ProcessLuaRunThinking()
{
	MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >(this);
	if (pAiChar->GetMonsterConfig())
	{
		if(pAiChar->GetMonsterConfig()->stMonsterId == 100375)
		{
			int n =0;
			n++;
		}
	}
	
    if( !m_bLuaScriptLoaded )
    { return; }

    try
    {
        LuaObject luaobject = m_xLuaScript->GetGlobal( "Event_Thinking" );
        if( luaobject.IsFunction() )
        { GetLuaFunction( "Event_Thinking" )(); }
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script Event_Thinking failed: %s", GetCharName(), e.GetErrorMessage() );
        m_bLuaScriptLoaded = false;
    }
}

void AiCharacter::LuaBeAttackedCallBack( GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage )
{
    if( !m_bLuaScriptLoaded )
    { return; }

    try
    {
        LuaObject luaobject = m_xLuaScript->GetGlobal( "Event_Beattacked" );
        if( luaobject.IsFunction() )
        {
            GetLuaFunction( "Event_Beattacked" )( nAttackerID, nSkillID, nSkillLevel, nDamage );
        }
    }
    catch ( LuaPlus::LuaException &e )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI Script Event_Beattacked Failed: %s", GetCharName(), e.GetErrorMessage() );
        m_bLuaScriptLoaded = false;
    }
}

void AiCharacter::LuaDeathCallBack( GameObjectId nKillerID )
{
    if( !m_bLuaScriptLoaded )
    { return; }

    try
    {
        LuaObject luaobject = m_xLuaScript->GetGlobal( "Event_Death" );
        if( luaobject.IsFunction() )
        {
            GetLuaFunction( "Event_Death" )( nKillerID );
        }
    }
    catch ( LuaPlus::LuaException &e )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI Script Event_Death Failed: %s", GetCharName(), e.GetErrorMessage() );
        m_bLuaScriptLoaded = false;
    }
}

bool AiCharacter::RegisterLuaFunction()
{
    try
    {
        LuaObject metaTableObj;
        metaTableObj = m_xLuaScript->GetGlobals().CreateTable( "MultiObjectMetaTable" );
        metaTableObj.SetObject( "__index", metaTableObj );

        metaTableObj.RegisterObjectDirect( "TimerStart",          (AiCharacter*)0, &AiCharacter::LuaTimerStart         );
        metaTableObj.RegisterObjectDirect( "TimerStop",           (AiCharacter*)0, &AiCharacter::LuaTimerStop          );
        metaTableObj.RegisterObjectDirect( "TimerDone",           (AiCharacter*)0, &AiCharacter::LuaTimerDone          );
        metaTableObj.RegisterObjectDirect( "TimerHaveStart",      (AiCharacter*)0, &AiCharacter::LuaTimerHaveStart     );
        metaTableObj.RegisterObjectDirect( "SetArray",            (AiCharacter*)0, &AiCharacter::SetParamValue         );
        metaTableObj.RegisterObjectDirect( "GetArray",            (AiCharacter*)0, &AiCharacter::GetParamValue         );
        metaTableObj.RegisterObjectDirect( "LoseHP",              (AiCharacter*)0, &AiCharacter::LoseHPInstant         );
        metaTableObj.RegisterObjectDirect( "LoseMP",              (AiCharacter*)0, &AiCharacter::LoseMPInstant         );
        metaTableObj.RegisterObjectDirect( "RestoreHP",           (AiCharacter*)0, &AiCharacter::RestoreHPInstant      );
        metaTableObj.RegisterObjectDirect( "RestoreMP",           (AiCharacter*)0, &AiCharacter::RestoreMPInstant      );
        metaTableObj.RegisterObjectDirect( "GetHP",               (AiCharacter*)0, &AiCharacter::LuaGetHP              );
        metaTableObj.RegisterObjectDirect( "GetMP",               (AiCharacter*)0, &AiCharacter::LuaGetMP              );
        metaTableObj.RegisterObjectDirect( "GetHPMax",            (AiCharacter*)0, &AiCharacter::LuaGetHPMax           );
        metaTableObj.RegisterObjectDirect( "GetMPMax",            (AiCharacter*)0, &AiCharacter::LuaGetMPMax           );
        metaTableObj.RegisterObjectDirect( "UseSkill",            (AiCharacter*)0, &AiCharacter::LuaUseSkill           );
        metaTableObj.RegisterObjectDirect( "TryAttack",           (AiCharacter*)0, &AiCharacter::LuaTryAttack          );
        metaTableObj.RegisterObjectDirect( "Say",                 (AiCharacter*)0, &AiCharacter::LuaSay                );
        metaTableObj.RegisterObjectDirect( "GetRand",             (AiCharacter*)0, &AiCharacter::GetRandNumber         );
        metaTableObj.RegisterObjectDirect( "GetTargetID",         (AiCharacter*)0, &AiCharacter::LuaGetLockID          );
        metaTableObj.RegisterObjectDirect( "GetLevel",            (AiCharacter*)0, &AiCharacter::LuaGetLevel           );
        metaTableObj.RegisterObjectDirect( "GetCharName",         (AiCharacter*)0, &AiCharacter::GetTargetName         );
        metaTableObj.RegisterObjectDirect( "GetTargetHP",         (AiCharacter*)0, &AiCharacter::GetTargetHP           );
        metaTableObj.RegisterObjectDirect( "GetTargetMP",         (AiCharacter*)0, &AiCharacter::GetTargetMP           );
        metaTableObj.RegisterObjectDirect( "GetTargetHPMax",      (AiCharacter*)0, &AiCharacter::GetTargetHPMax        );
        metaTableObj.RegisterObjectDirect( "GetTargetMPMax",      (AiCharacter*)0, &AiCharacter::GetTargetMPMax        );
        metaTableObj.RegisterObjectDirect( "GetTargetLevel",      (AiCharacter*)0, &AiCharacter::GetTargetLevel        );
        metaTableObj.RegisterObjectDirect( "GetTargetEnmity",     (AiCharacter*)0, &AiCharacter::GetTargetEnmity       );
        metaTableObj.RegisterObjectDirect( "GetTargetDamage",     (AiCharacter*)0, &AiCharacter::GetTargetDamage       );
        metaTableObj.RegisterObjectDirect( "SetTargetEnmity",     (AiCharacter*)0, &AiCharacter::SetTargetEnmity       );
        metaTableObj.RegisterObjectDirect( "GetTargetDistance",   (AiCharacter*)0, &AiCharacter::GetTargetDistance     );
        metaTableObj.RegisterObjectDirect( "GetTargetProfession", (AiCharacter*)0, &AiCharacter::GetTargetProfession   );
        metaTableObj.RegisterObjectDirect( "GetTargetPosX",       (AiCharacter*)0, &AiCharacter::LuaGetTargetPosX      );
        metaTableObj.RegisterObjectDirect( "GetTargetPosY",       (AiCharacter*)0, &AiCharacter::LuaGetTargetPosY      );
        metaTableObj.RegisterObjectDirect( "KillTarget",          (AiCharacter*)0, &AiCharacter::LuaKillTarget         );

        metaTableObj.RegisterObjectDirect( "Murder",              (AiCharacter*)0, &AiCharacter::LuaMonsterMurder      );
        metaTableObj.RegisterObjectDirect( "SummonMonster",       (AiCharacter*)0, &AiCharacter::LuaSummonMonster      );
        metaTableObj.RegisterObjectDirect( "SummonMonsterPos",    (AiCharacter*)0, &AiCharacter::LuaSummonMonsterPos   );
        metaTableObj.RegisterObjectDirect( "MAlarmWhenBeAttack",  (AiCharacter*)0, &AiCharacter::LuaMAlarmWhenBeAttack );

        metaTableObj.RegisterObjectDirect( "GetSelfID",             (AiCharacter*)0, &AiCharacter::LuaGetSelfID         );
        metaTableObj.RegisterObjectDirect( "SetLockID",             (AiCharacter*)0, &AiCharacter::LuaSetLockID         );
        
        metaTableObj.RegisterObjectDirect( "GetPlayerIdByLevel",    (AiCharacter*)0, &AiCharacter::GetPlayerIdByLevel   );
        metaTableObj.RegisterObjectDirect( "GetPlayerIdByHp",       (AiCharacter*)0, &AiCharacter::GetPlayerIdByHp      );
        metaTableObj.RegisterObjectDirect( "GetPlayerIdByMp",       (AiCharacter*)0, &AiCharacter::GetPlayerIdByMp      );
        metaTableObj.RegisterObjectDirect( "GetPlayerIdByProfession",(AiCharacter*)0,&AiCharacter::GetPlayerIdByProfession );

        metaTableObj.RegisterObjectDirect( "AddStatusBuff",         (AiCharacter*)0, &AiCharacter::LuaAddStatusBuff     );
        metaTableObj.RegisterObjectDirect( "ClearStatusBuff",       (AiCharacter*)0, &AiCharacter::LuaClearStatusBuff   );
        metaTableObj.RegisterObjectDirect( "AddTargetStatusBuff",   (AiCharacter*)0, &AiCharacter::LuaAddTargetStatusBuff   );
        metaTableObj.RegisterObjectDirect( "ClearStatusBuffByType", (AiCharacter*)0, &AiCharacter::LuaClearStatusBuffByType );
        metaTableObj.RegisterObjectDirect( "IsHaveStatus",          (AiCharacter*)0, &AiCharacter::LuaIsHaveStatus       );
        metaTableObj.RegisterObjectDirect( "IsTargetHaveStatus",    (AiCharacter*)0, &AiCharacter::LuaIsTargetHaveStatus );

        metaTableObj.RegisterObjectDirect( "PlayAnim",              (AiCharacter*)0, &AiCharacter::LuaPlayAnim );
        metaTableObj.RegisterObjectDirect( "PlayScene",             (AiCharacter*)0, &AiCharacter::LuaPlayScene );
        metaTableObj.RegisterObjectDirect( "TargetPlayAnim",        (AiCharacter*)0, &AiCharacter::LuaTargetPlayAnim );
        metaTableObj.RegisterObjectDirect( "TargetPlayScene",       (AiCharacter*)0, &AiCharacter::LuaTargetPlayScene );

        metaTableObj.RegisterObjectDirect( "GetMonsterIdByType",    (AiCharacter*)0, &AiCharacter::LuaGetMonsterIdByType    );
        metaTableObj.RegisterObjectDirect( "GetMonsterIdByID",      (AiCharacter*)0, &AiCharacter::LuaGetMonsterIdByID      );
		metaTableObj.RegisterObjectDirect( "GetIDByMonsterId",      (AiCharacter*)0, &AiCharacter::LuaGetIDByMonsterId      );

		metaTableObj.RegisterObjectDirect( "GetEnmityListIDNoExcept",       (AiCharacter*)0, &AiCharacter::LuaGetEnmityListIDNoExcept);
        metaTableObj.RegisterObjectDirect( "GetEnmityListID",       (AiCharacter*)0, &AiCharacter::LuaGetEnmityListID       );
        metaTableObj.RegisterObjectDirect( "GetMonsterListID",      (AiCharacter*)0, &AiCharacter::LuaGetMonsterListID      );

        metaTableObj.RegisterObjectDirect( "MoveToPoint",           (AiCharacter*)0, &AiCharacter::LuaMoveToPoint           );
        metaTableObj.RegisterObjectDirect( "IsInPointRange",        (AiCharacter*)0, &AiCharacter::IsInPointRange           );

        metaTableObj.RegisterObjectDirect( "ChangeMonsterStatus",   (AiCharacter*)0, &AiCharacter::LuaChangeMonsterStatus   );
        metaTableObj.RegisterObjectDirect( "DropItemPackage",       (AiCharacter*)0, &AiCharacter::LuaDropItemPackage       );

        metaTableObj.RegisterObjectDirect( "MoveBackToAttacker",    (AiCharacter*)0, &AiCharacter::LuaMoveBackToAttacker    );
		metaTableObj.RegisterObjectDirect( "GetTargetVar",			(AiCharacter*)0, &AiCharacter::GetTargetVar    );
		metaTableObj.RegisterObjectDirect( "SetTargetVar",			(AiCharacter*)0, &AiCharacter::SetTargetVar    );
		 metaTableObj.RegisterObjectDirect( "GetMasterId",          (AiCharacter*)0, &AiCharacter::LuaGetMasterId         );
        
        LuaObject CAICharacterCoreObj = m_xLuaScript->BoxPointer( this );
        CAICharacterCoreObj.SetMetaTable( metaTableObj );
        m_xLuaScript->GetGlobals().SetObject( "AI", CAICharacterCoreObj );
    }
    catch ( LuaPlus::LuaException &e )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script failed:%s", GetCharName(), e.GetErrorMessage() );
        return false;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// Lua脚本函数定义

// nSpaceTime( 单位 : 秒 )
void AiCharacter::LuaTimerStart( unsigned int nIndex, int nSpaceTime, unsigned int nStartTime )
{
    if ( nIndex >= AiDefine::LuaTimerCount )
    { return; }

    // 定时器开始时间
    if ( nStartTime == 0 )
    { nStartTime = HQ_TimeGetTime(); }

    m_xLuaTimer[ nIndex ].StartTimer( nStartTime, nSpaceTime * 1000 );
}

void AiCharacter::LuaTimerStop( unsigned int nIndex )
{
    if ( nIndex >= AiDefine::LuaTimerCount )
    { return; }

    m_xLuaTimer[ nIndex ].StopTimer();
}

bool AiCharacter::LuaTimerDone( unsigned int nIndex, int bContinue )
{
    if ( nIndex >= AiDefine::LuaTimerCount )
    { return false; }

    if ( bContinue )
    { return m_xLuaTimer[ nIndex ].DoneTimer( HQ_TimeGetTime() ); }

    return m_xLuaTimer[ nIndex ].DoneTimer();
}

bool AiCharacter::LuaTimerHaveStart( unsigned int nIndex )
{
    if ( nIndex >= AiDefine::LuaTimerCount )
    { return false; }

    return m_xLuaTimer[ nIndex ].IsStart();
}

void AiCharacter::SetParamValue( unsigned int nIndex, int nValue )
{
    if ( nIndex >= AiDefine::LuaValueArrayCount )
    { return; }

    m_nParamValue[ nIndex ] = nValue;
}

int AiCharacter::GetParamValue( unsigned int nIndex )
{
    if ( nIndex >= AiDefine::LuaValueArrayCount )
    { return 0; }

    return m_nParamValue[ nIndex ];
}

void AiCharacter::LoseHPInstant( int nValue )
{
    int nHp = GetHP();
    nHp -= nValue;

    if( nHp < 1 )
    { nHp = 1; }

    SetHP( nHp );
    ChangeAttr( CharAttr_HP, GetHP() );
}

void AiCharacter::LoseMPInstant( int nValue )
{
    int nMp = GetMP();
    nMp -= nValue;

    if( nMp < 1 )
    { nMp = 1; }

    SetMP( nMp );
    // ChangeAttr( CharAttr_MP, GetMP() );
}

void AiCharacter::RestoreHPInstant( int nValue )
{
    int nHp = GetHP();
    nHp += nValue;

    if( nHp > GetHPMax() )
    { nHp = GetHPMax(); }

    SetHP( nHp );
    ChangeAttr( CharAttr_HP, nHp );
}

void AiCharacter::RestoreMPInstant( int nValue )
{
    int nMp = GetMP();
    nMp += nValue;

    if( nMp > GetMPMax() )
    { nMp = GetMPMax(); }

    SetMP( nMp );
}

void AiCharacter::LuaUseSkill( int nSkillID, int nSkillLevel )
{
    BaseCharacter* pTarget = GetLockChar();
    if( pTarget == NULL || pTarget->IsDead() )
    { return; }

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );
    if ( pSkill == NULL )
    { return; }

    if( !IsInAttackRange( pTarget, pSkill ) )
    { return; }

    // 清除当前技能状态
    SetStatus( CS_IDLE );
    _SkillTaskManager.DoneCurTask();

    AddAiTask( pTarget->GetID(), nSkillID, nSkillLevel );
    ClearMoveTargetPoint();
}

void AiCharacter::LuaTryAttack( GameObjectId nID, int nSkillID, int nSkillLevel )
{
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( nID );
    if( pTarget == NULL || pTarget->IsDead() )
    { return; }

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );
    if ( pSkill == NULL )
    { return; }

    if( !IsInAttackRange( pTarget, pSkill ) )
    { return; }

    SAttackTarget target;
    target.bIsCharTarget = true;
    target.nCharID = pTarget->GetID();
    TryAttack(&target, pSkill, nSkillID, nSkillLevel );
}

 void AiCharacter::LuaSay( int nType, const char* szValue )
 {
    Say( nType, szValue );
 }

// 得到一个0到n的随机数
int AiCharacter::GetRandNumber( int nValue )
{
    if ( nValue == 0 )
    { return 0; }

    // 可能会有多线程, 所以不能用theRand类
    return rand() % nValue;
}

const char* AiCharacter::GetTargetName( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return ""; }

    return pTarget->GetCharName();
}

int AiCharacter::GetTargetHP( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }
    
    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetHP();
}

int AiCharacter::GetTargetMP( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetMP();
}

int AiCharacter::GetTargetHPMax( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetHPMax();
}

int AiCharacter::GetTargetMPMax( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetMPMax();
}

int AiCharacter::GetTargetLevel( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetLevel();
}

int AiCharacter::GetTargetEnmity( GameObjectId nID )
{
    EnmityData* pEnmityData = NULL;

    if ( nID == InvalidGameObjectId )
    { pEnmityData = GetEnmity( GetLockID() ); }
    else
    { pEnmityData = GetEnmity( nID ); }

    if ( pEnmityData == NULL )
    { return 0; }

    return pEnmityData->GetEnmity();
}

int AiCharacter::GetTargetDamage( GameObjectId nID )
{
    EnmityData* pEnmityData = NULL;

    if ( nID == InvalidGameObjectId )
    { pEnmityData = GetEnmity( GetLockID() ); }
    else
    { pEnmityData = GetEnmity( nID ); }

    if ( pEnmityData == NULL )
    { return 0; }

    return pEnmityData->GetDamage();
}

void AiCharacter::SetTargetEnmity( int nValue, GameObjectId nID )
{
    EnmityData* pEnmityData = NULL;

    if ( nID == InvalidGameObjectId )
    { pEnmityData = GetEnmity( GetLockID() ); }
    else
    { pEnmityData = GetEnmity( nID ); }

    if ( pEnmityData == NULL )
    { return; }

    pEnmityData->SetEnmity( nValue );
    pEnmityData->SetReduction( pEnmityData->GetEnmity() * GetEnmityRate() / AiDefine::EnmityBaseRate );
}

int AiCharacter::GetTargetDistance( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return -1; }

    D3DXVECTOR3 vTargetPos = pTarget->GetPos();
    D3DXVECTOR3 vCurPos    = GetPos();

    // 只判断平面位置
    D3DXVECTOR3 vecDistance( vTargetPos.x - vCurPos.x, vTargetPos.y - vCurPos.y, 0 );

    return D3DXVec3Length( &vecDistance );
}

int AiCharacter::GetTargetProfession( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL || !pTarget->IsPlayer() )
    { return -1; }

    return pTarget->GetProfession();
}

float AiCharacter::LuaGetTargetPosX( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetFloatX();
}

float AiCharacter::LuaGetTargetPosY( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL )
    { return 0; }

    return pTarget->GetFloatY();
}

void AiCharacter::LuaKillTarget( GameObjectId nID )
{
    BaseCharacter* pTarget =  NULL; 

    if ( nID == InvalidGameObjectId )
    { pTarget = GetLockChar(); }
    else
    { pTarget = theRunTimeData.GetCharacterByID( nID ); }

    if ( pTarget == NULL || !pTarget->IsMonster() )
    { return; }

    MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );
    pAiChar->CharacterMurder();
}

void AiCharacter::LuaSummonMonster( int nMonsterID, int nCount, float fRadius, int nFightCamp, int nCountry, int nForce, int nRouteID )
{
    MonsterCreateData xCreateData;
    xCreateData.SetMapID( GetMapID() );
    xCreateData.SetPostionX( GetFloatX() );
    xCreateData.SetPostionY( GetFloatY() );
    xCreateData.SetDirX( GetDirX() );
    xCreateData.SetDirY( GetDirY() );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetMonsterID( nMonsterID );
    xCreateData.SetCount( nCount );
    xCreateData.SetFightCamp( nFightCamp );
    xCreateData.SetCountry( nCountry );
    xCreateData.SetForce( nForce );
    xCreateData.SetRouteID( nRouteID );

    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void AiCharacter::LuaSummonMonsterPos( int nMonsterID, float fX, float fY, int nFightCamp, int nCountry, int nForce, int nRouteID )
{
    MonsterCreateData xCreateData;
    xCreateData.SetMapID( GetMapID() );
    xCreateData.SetPostionX( fX );
    xCreateData.SetPostionY( fY );
    xCreateData.SetDirX( GetDirX() );
    xCreateData.SetDirY( GetDirY() );
    xCreateData.SetMonsterID( nMonsterID );
    xCreateData.SetCount( 1 );
    xCreateData.SetFightCamp( nFightCamp );
    xCreateData.SetCountry( nCountry );
    xCreateData.SetForce( nForce );
    xCreateData.SetRouteID( nRouteID );

    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void AiCharacter::LuaMAlarmWhenBeAttack( unsigned int nDistance, bool bSameMonsterID, bool bSamePhyle )
{
    if ( GetLockID() == InvalidGameObjectId )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if ( pStage == NULL )
    { return; }

    BaseCharacter* pAttackTarget = GetLockChar();
    if ( pAttackTarget == NULL || ( !pAttackTarget->IsPlayer() && !pAttackTarget->IsPet() ) )
    { return; }

    AreaIndexTPL(Area9) list;
    pStage->Get9AreaList( list, GetCurArea() );
    for (int i = 0; i < list.Count(); ++i )
    {
        GameArea* pArea = pStage->GetArea( list[i] );
        if ( pArea == NULL )
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pArea->GetNextObjectBId( 0 == currentIndex ) ) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || !pChar->IsMonster() || !IsDistanceLess( GetTileX(), GetTileY(), pChar->GetTileX(), pChar->GetTileY(), nDistance ) )
            { continue; }

            if ( !pAttackTarget->IsPosInRange( pChar->GetFloatX(), pChar->GetFloatY(), TARGET_VIEW_DIS ) )
            { continue; }

            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pChar );
			if ( ( bSameMonsterID && pAiChar->GetMonsterID() != GetMonsterID() ) || ( bSamePhyle && pAiChar->GetPhyle() != GetPhyle() ) )
			{ continue; }

            //设置好怪物战斗视野以及战斗视野结束时间(目前程序内写死2秒后视野恢复)
            pAiChar->SetViewSight( pAiChar->GetFightViewSight() );
            pAiChar->StartIdleViewTimer( HQ_TimeGetTime() );
            pAiChar->AddAttackTarget( GetLockID() );
            pAiChar->SetEnmity( GetLockID(), 10000 );
           
        }
    }
}

// 根据职业获得玩家ID
GameObjectId  AiCharacter::GetPlayerIdByProfession( int nProfession )
{
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨衰减
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        if ( pChar->GetProfession() == nProfession )
        { return pChar->GetID(); }
    }

    return InvalidGameObjectId;
}

// 根据等级获得玩家ID
GameObjectId  AiCharacter::GetPlayerIdByLevel( int nMinLevel, int nMaxLevel )
{
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨衰减
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        if ( pChar->GetLevel() >= nMinLevel && pChar->GetLevel() <= nMaxLevel )
        { return pChar->GetID(); }
    }

    return InvalidGameObjectId;
}

// 根据血量获得玩家ID
GameObjectId  AiCharacter::GetPlayerIdByHp( int nMinHp, int nMaxHp )
{
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨衰减
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        if ( pChar->GetHP() >= nMinHp && pChar->GetHP() <= nMaxHp )
        { return pChar->GetID(); }
    }

    return InvalidGameObjectId;
}

// 根据MP获得玩家ID
GameObjectId  AiCharacter::GetPlayerIdByMp( int nMinMp, int nMaxMp )
{
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨衰减
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        if ( pChar->GetMP() >= nMinMp && pChar->GetMP() <= nMaxMp )
        { return pChar->GetID(); }
    }

    return InvalidGameObjectId;
}

// 获得周围怪物ID
GameObjectId  AiCharacter::LuaGetMonsterIdByType( int nType )
{
    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if( pStage == NULL )
    { return InvalidGameObjectId; } 

    D3DXVECTOR3 vPos = GetPos();

    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = pStage->TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return InvalidGameObjectId; }

    GameArea* pTargetPosArea = pStage->GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return InvalidGameObjectId; }

    for( int i = 0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = pStage->GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( objectId );
            if( pTargetChar == NULL || !pTargetChar->IsMonster() )
            { continue; }

            MonsterBaseEx* pMonsterChar = static_cast< MonsterBaseEx* >( pTargetChar );
            
            if ( pMonsterChar->GetMonsterType() == nType )
            { return pMonsterChar->GetID(); }
        }
    }

    return InvalidGameObjectId;
}


GameObjectId AiCharacter::LuaGetMasterId()
{
	GameObjectId _masterid = InvalidGameObjectId;
	if(HaveMaster())
	_masterid = GetMasterID();

	return _masterid;
}
int AiCharacter::LuaGetIDByMonsterId(GameObjectId ID)
{
	 BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( ID );
	 if(!pTargetChar)
		 return 0;
	 return pTargetChar->GetMonsterID();
}
GameObjectId  AiCharacter::LuaGetMonsterIdByID  ( int nID   )
{
    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if( pStage == NULL )
    { return InvalidGameObjectId; } 

    D3DXVECTOR3 vPos = GetPos();

    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = pStage->TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return InvalidGameObjectId; }

    GameArea* pTargetPosArea = pStage->GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return InvalidGameObjectId; }

    for( int i = 0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = pStage->GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( GameObjectId currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( objectId );
            if( pTargetChar == NULL || !pTargetChar->IsMonster() )
            { continue; }

            MonsterBaseEx* pMonsterChar = static_cast< MonsterBaseEx* >( pTargetChar );

            if ( pMonsterChar->GetMonsterID() == nID )
            { return pMonsterChar->GetID(); }
        }
    }

    return InvalidGameObjectId;
}


// 增加清除BUFF 
void AiCharacter::LuaAddStatusBuff ( int statusId, int statusLevel )
{
    ApplyBufferStatus( statusId, statusLevel, GetID(), SCharBuff::StatusEventType_Other, 0 );
    OnBuffStatusChanged( true );
}

void AiCharacter::LuaClearStatusBuff ( int statusId )
{
    _buffManager.ClearBuffByBuffId( statusId );
    OnBuffStatusChanged( true );
}

void AiCharacter::LuaAddTargetStatusBuff ( int statusId, int statusLevel )
{
    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( GetLockID() );
    if( pTargetChar == NULL )
    { return; }

    pTargetChar->ApplyBufferStatus( statusId, statusLevel,GetID(), SCharBuff::StatusEventType_Other, 0 );
    pTargetChar->OnBuffStatusChanged( true );
}

void AiCharacter::LuaClearStatusBuffByType ( int statusType )
{
    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( GetLockID() );
    if( pTargetChar == NULL )
    { return; }

    if ( statusType == -1 )
    {
        pTargetChar->_buffManager.ClearAllBuffByHaveAttack();
        pTargetChar->OnBuffStatusChanged( true );
    }
    else
    {

    }    
}

bool AiCharacter::LuaIsHaveStatus ( int statusId )
{
    return _buffManager.IsHaveStatus( statusId );
}


bool AiCharacter::LuaIsTargetHaveStatus ( int statusId, GameObjectId nTargetId )
{
	BaseCharacter* pTargetChar = NULL;
	if ( nTargetId != InvalidGameObjectId )
	{
		pTargetChar = theRunTimeData.GetCharacterByID( nTargetId );
	}
	else
	{
		pTargetChar = theRunTimeData.GetCharacterByID( GetLockID() );
	}

    if( pTargetChar == NULL )
    { return false; }

    return pTargetChar->_buffManager.IsHaveStatus( statusId );
}

void AiCharacter::LuaPlayAnim( const char* szName, const char* szEndName, int nTimes )
{
    MsgNpcPlayAnim msg;
    msg.header.stID = GetID();
    msg.nNpcId = GetID();
    HelperFunc::SafeNCpy( msg.szActionName, szName, MsgNpcPlayAnim::eActionNameLength );
    HelperFunc::SafeNCpy( msg.szEndActionName, szEndName, MsgNpcPlayAnim::eActionNameLength );
    msg.nLoopTimes = nTimes;
    GettheServer().SendMsgToView( &msg, GetID(), false );
}

void AiCharacter::LuaPlayScene   ( int nSceneID )
{
    MsgScenePlay  msgScene;
    msgScene.header.stID = GetID();
    msgScene.stSceneId   = nSceneID;
    GettheServer().SendMsgToView  ( &msgScene, GetID(), true );
}

void AiCharacter::LuaTargetPlayAnim  ( GameObjectId nID , const char* szName, const char* szEndName, int nTimes )
{
    BaseCharacter* pTargetChar = NULL;
    if ( nID != InvalidGameObjectId )
    {
        pTargetChar = theRunTimeData.GetCharacterByID( nID );
    }
    else
    {
        pTargetChar = theRunTimeData.GetCharacterByID( GetLockID() );
    }

    if( pTargetChar == NULL )
    { return; }

    MsgNpcPlayAnim msg;
    msg.header.stID = pTargetChar->GetID();
    msg.nNpcId = pTargetChar->GetID();
    HelperFunc::SafeNCpy( msg.szActionName, szName, MsgNpcPlayAnim::eActionNameLength );
    HelperFunc::SafeNCpy( msg.szEndActionName, szEndName, MsgNpcPlayAnim::eActionNameLength );
    msg.nLoopTimes = nTimes;
    GettheServer().SendMsgToView( &msg, pTargetChar->GetID(), false );
}

void AiCharacter::LuaTargetPlayScene   ( GameObjectId nID , int nSceneID )
{
    BaseCharacter* pTargetChar = NULL;
    if ( nID != InvalidGameObjectId )
    {
        pTargetChar = theRunTimeData.GetCharacterByID( nID );
    }
    else
    {
        pTargetChar = theRunTimeData.GetCharacterByID( GetLockID() );
    }

    if( pTargetChar == NULL )
    { return; }

    MsgScenePlay  msgScene;
    msgScene.header.stID = pTargetChar->GetID();
    msgScene.stSceneId   = nSceneID;
    GettheServer().SendMsgToView  ( &msgScene, pTargetChar->GetID(), true );
}

void AiCharacter::LuaGetEnmityListIDNoExcept ( float fDistance )
{
	int index = 1;
	LuaObject list = m_xLuaScript->GetGlobals().CreateTable( "list" );

	D3DXVECTOR3 vPos = GetPos();
	for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
	{
		// 仇恨值
		//int nEnimty = iter->second.GetEnmity();
		//if (nEnimty > 0)
		{
			BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( iter->first );
			if( pTargetChar == NULL || !pTargetChar->IsPlayer() || !CheckCanAttackTarget(pTargetChar) )
			{ continue; }

			D3DXVECTOR3 vTargetPos = pTargetChar->GetPos();

			// 只判断平面位置
			D3DXVECTOR3 vecDistance( vTargetPos.x - vPos.x, vTargetPos.y - vPos.y, 0 );

			if ( D3DXVec3Length( &vecDistance )  > fDistance  )
			{ continue; }

			list.SetInteger(index, iter->first);
			++index;
		}
	}

	m_xLuaScript->GetGlobals().SetObject( "list" , list );
}

void AiCharacter::LuaGetEnmityListID( float fDistance )
{
    int index = 1;
    LuaObject list = m_xLuaScript->GetGlobals().CreateTable( "list" );
    
    D3DXVECTOR3 vPos = GetPos();
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨值
        int nEnimty = iter->second.GetEnmity();
        if (nEnimty > 0)
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( iter->first );
            if( pTargetChar == NULL || !pTargetChar->IsMonster() || CheckCanAttackTarget(pTargetChar) )
            { continue; }

            D3DXVECTOR3 vTargetPos = pTargetChar->GetPos();

            // 只判断平面位置
            D3DXVECTOR3 vecDistance( vTargetPos.x - vPos.x, vTargetPos.y - vPos.y, 0 );

            if ( D3DXVec3Length( &vecDistance )  > fDistance  )
            { continue; }

            list.SetInteger(index, iter->first);
            ++index;
        }
    }

    m_xLuaScript->GetGlobals().SetObject( "list" , list );
}

void AiCharacter::LuaGetMonsterListID( float fDistance )
{
    int index = 1;
    LuaObject list = m_xLuaScript->GetGlobals().CreateTable( "list" );

    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if( pStage == NULL )
    { return; } 

    D3DXVECTOR3 vPos = GetPos();

    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = pStage->TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return; }

    GameArea* pTargetPosArea = pStage->GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return; }

    for( int i = 0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = pStage->GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( GameObjectId currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( objectId );
            if( pTargetChar == NULL || !pTargetChar->IsMonster() || CheckCanAttackTarget(pTargetChar) )
            { continue; }

            D3DXVECTOR3 vTargetPos = pTargetChar->GetPos();

            // 只判断平面位置
            D3DXVECTOR3 vecDistance( vTargetPos.x - vPos.x, vTargetPos.y - vPos.y, 0 );

            if ( D3DXVec3Length( &vecDistance )  > fDistance  )
            { continue; }

            list.SetInteger( index, pTargetChar->GetID() );
            ++index;
        }
    }

    m_xLuaScript->GetGlobals().SetObject( "list" , list );
}

void AiCharacter::LuaMoveToPoint(  float fX, float fY )
{
    SetMovePoint( fX, fY, 0 );
    SetAiStatus ( AiDefine::ThinkingMoveToPoint );
}

bool AiCharacter::IsInPointRange( int xPos, int yPos, float fDistance )
{
    D3DXVECTOR3 vTargetPos(xPos,yPos,0);
    D3DXVECTOR3 vCurPos    = GetPos();

    // 只判断平面位置
    D3DXVECTOR3 vecDistance( vTargetPos.x - vCurPos.x, vTargetPos.y - vCurPos.y, 0 );

    return D3DXVec3Length( &vecDistance ) <= fDistance ;
}

void AiCharacter::LuaChangeMonsterStatus( int nMonsterID, int nMonsterCount, int nMonsterStatusID )
{
    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if ( pStage == NULL )
    { return; }

    int nCount = 0;
    AreaIndexTPL(Area9) list;
    pStage->Get9AreaList( list, GetCurArea() );
    for (int i = 0; i < list.Count(); ++i )
    {
        GameArea* pArea = pStage->GetArea( list[i] );
        if ( pArea == NULL )
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pArea->GetNextObjectBId( 0 == currentIndex ) ) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || !pChar->IsMonster() )
            { continue; }

            MonsterBaseEx* pAiTarget = static_cast< MonsterBaseEx* >( pChar );

            if ( pAiTarget->GetMonsterID() != nMonsterID )
            { continue; }

            pAiTarget->ProcessMonsterStatusChange( nMonsterStatusID );
            ++nCount;
            if ( nCount >= nMonsterCount )
            { break; }
        }
    }
}

void AiCharacter::LuaDropItemPackage( int nDropPackIndex )
{
    ProcessDropItemPackage( nDropPackIndex );
}

void AiCharacter::LuaMoveBackToAttacker( GameObjectId nAttackerID, int nDistance )
{
    DECLARE_TIME_TEST

    BaseCharacter* pTarget = NULL;
    if ( nAttackerID != InvalidGameObjectId )
    {
        pTarget = theRunTimeData.GetCharacterByID( nAttackerID );
    }
    else
    {
        pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    }

    ProcessAttackMoveSpeed( 2 );

    // 寻路 此处 nDistance 如果很大会造成逃跑假象
    D3DXVECTOR3 vecTargetPos( pTarget->GetPos() );
    float fFreeRange = pTarget->GetBodySize() + nDistance;	// 技能的攻击记录和目标的体型

    BEGIN_TIME_TEST( "LogicThread FindParth" );
    bool blHasFindParth = FindTheNextPosToMove( vecTargetPos, fFreeRange );
    END_TIME_TEST_1( "LogicThread FindParth", 1 );
    if ( ! blHasFindParth )
    { return; }

    // 和目标之间的距离
    D3DXVECTOR3 vecDistance( vecTargetPos.x - GetFloatX(), vecTargetPos.y - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    // 方向
    D3DXVECTOR3 vecDir;
    D3DXVec3Normalize( &vecDir, &vecDistance );

    // 减去技能的攻击记录和目标的体型
    float fRange = fDistance - fFreeRange;

    // 设置目标点
    float fTargetX = GetFloatX() + fRange * vecDir.x;
    float fTargetY = GetFloatY() + fRange * vecDir.y;
    if ( fTargetX != m_xMoveTargetPoint.x || fTargetY != m_xMoveTargetPoint.y )
    { SetMoveTargetPoint( GetFloatX() + fRange * vecDir.x, GetFloatY() + fRange * vecDir.y, 0 ); }

    // 怪物追击时候, 坐标位置1秒同步一次
    m_xTimer[ AiDefine::AiTimer_Move ].SetSpaceTime( AiDefine::VerifyPointSpaceTime / 2 );
}

//获得某个角色的变量值
int AiCharacter::GetTargetVar(int varid,GameObjectId nID)
{
	BaseCharacter* pTarget =  NULL; 

	if ( nID == InvalidGameObjectId )
	{ pTarget = GetLockChar(); }
	else
	{ pTarget = theRunTimeData.GetCharacterByID( nID ); }

	if ( pTarget == NULL || !pTarget->IsPlayer() )
	{ return -1; }
	GamePlayer* pGamePlayer = (GamePlayer*)pTarget;
	if (!pGamePlayer)
	{
		return -1;
	}
	return pGamePlayer->GetVar(varid);
}
//设置某个角色的变量值
void AiCharacter::SetTargetVar(int varid,int _value,int nOp,int needsend,GameObjectId nID)
{
	BaseCharacter* pTarget =  NULL; 

	if ( nID == InvalidGameObjectId )
	{ pTarget = GetLockChar(); }
	else
	{ pTarget = theRunTimeData.GetCharacterByID( nID ); }

	if ( pTarget == NULL || !pTarget->IsPlayer() )
	{ return; }
	GamePlayer* pGamePlayer = (GamePlayer*)pTarget;
	if (!pGamePlayer)
	{
		return;
	}
	pGamePlayer->SetVar(varid,_value,nOp,needsend);
}