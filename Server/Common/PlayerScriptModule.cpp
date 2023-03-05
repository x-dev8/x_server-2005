#include "GamePlayer.h"
#include "Dxsdk/d3dx9math.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "mathlib.h"
#include "DBMessageDefine.h"
#include "ServerVarInterface.h"
#include "ScriptCompiler.h"
#include "ScriptVarMgr.h"
#include "ItemCharacter.h"
#include "ItemDetail.h"
#include "ExpStage.h"
#include "Configure.h"
#include "MissionList.h"
#include "DatabaseConnectors.h"
#include "TimeClock.h"
#include "WordParser.h"
#include "AvatarSystemSetting.h"
#include "QuestManager.h"
#include "WordParser.h"
#include "RestoreColdDown.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "NpcBaseEx.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "DropQuestItem.h"
#include "ShareData.h"
#include "DataChunkWriter.h"
#include "ServerVarInterface.h"
#include "Helper.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "TeamManager.h"
#include "GlobalFunction.h"
#include "CountryConfig.h"

extern IScriptInterface* GetScriptInterface();

void GamePlayer::Script_SetInt( int nInt, int nOp )        // 智力
{
    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Luck].final;
    switch( nOp ) 
    {
    case SKW_SETADD:
    *pVal += nInt;
    break;
    case SKW_SETSUB:
    *pVal -= nInt;
    break;
    case SKW_SET:
    *pVal = nInt;
    break;
    default:
    GetErrorLog()->logString("Error:Script_SetInt");
    return;
    }
    SendCharArrtChange( CharAttr_Intelligence, (short)*pVal );*/
}

void GamePlayer::Script_SetMgc( int nMgc, int nOp )        // 魔力
{    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Spirit].final;
     switch( nOp ) 
     {
     case SKW_SETADD:
     *pVal += nMgc;
     break;
     case SKW_SETSUB:
     *pVal -= nMgc;
     break;
     case SKW_SET:
     *pVal = nMgc;
     break;
     default:
     GetErrorLog()->logString("Error:Script_SetMgc");
     return;
     }
     SendCharArrtChange( CharAttr_Spirit, (short)*pVal );*/
}

void GamePlayer::Script_SetLky( int nLky, int nOp )        // 魅力
{
    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Luck].final;
    switch( nOp ) 
    {
    case SKW_SETADD:
    *pVal += nLky;
    break;
    case SKW_SETSUB:
    *pVal -= nLky;
    break;
    case SKW_SET:
    *pVal = nLky;
    break;
    default:
    GetErrorLog()->logString("Error:Script_SetLky");
    return;
    }
    SendCharArrtChange( CharAttr_Luck, (short)*pVal );*/
}

void GamePlayer::Script_SetHp( int nHp, int nOp )
{
    switch( nOp ) 
    {
    case SKW_SETADD:
        SetHP( GetHP()+nHp );
        break;
    case SKW_SETSUB:
        SetHP( GetHP()-nHp );
        break;
    case SKW_SET:
        SetHP( nHp );
        break;
    default:
        return;
    }
    ChangeAttr( CharAttr_HP, (DWORD)GetHP() );
}

void GamePlayer::Script_SetEnergy( int value, int nOp )
{
    switch( nOp ) 
    {
    case SKW_SETADD:
        gCharInfoServer.baseinfo.liveinfo.activity += value;
        break;
    case SKW_SETSUB:
        {
            if (gCharInfoServer.baseinfo.liveinfo.activity < value)
            { gCharInfoServer.baseinfo.liveinfo.activity = 0; } // 如果当前的活力值不够，客户端和脚本都有预先判断，为防止外挂，直接设为0
            else
            { gCharInfoServer.baseinfo.liveinfo.activity -= value; }
        }
        break;
    case SKW_SET:
        gCharInfoServer.baseinfo.liveinfo.activity = value;
        break;
    }

    if (gCharInfoServer.baseinfo.liveinfo.activity > GetActivityMax())
    { gCharInfoServer.baseinfo.liveinfo.activity = GetActivityMax(); }
    ChangeAttr( CharAttr_Energy, gCharInfoServer.baseinfo.liveinfo.activity, true );
}

void GamePlayer::Script_SetVigor( int nValue, int nOp )
{
    switch( nOp ) 
    {
    case SKW_SETADD:
        gCharInfoServer.baseinfo.liveinfo.vigor += nValue;
        break;
    case SKW_SETSUB:
        {
            if (gCharInfoServer.baseinfo.liveinfo.vigor < nValue)
            { gCharInfoServer.baseinfo.liveinfo.vigor = 0; }
            else
            { gCharInfoServer.baseinfo.liveinfo.vigor -= nValue; }
        }
        break;
    case SKW_SET:
        gCharInfoServer.baseinfo.liveinfo.vigor = nValue;
        break;
    }

    if (gCharInfoServer.baseinfo.liveinfo.vigor > GetVigorMax())
    { gCharInfoServer.baseinfo.liveinfo.vigor = GetVigorMax(); }
    ChangeAttr( CharAttr_Vigor, gCharInfoServer.baseinfo.liveinfo.vigor, true );
}


void GamePlayer::Script_SetVigorMax( int value, int nOp )
{
    switch( nOp ) 
    {
    case SKW_SETADD:
        gCharInfoServer.baseinfo.liveinfo.vigorMax += value;
        break;
    case SKW_SETSUB:
        gCharInfoServer.baseinfo.liveinfo.vigorMax -= value;
        break;
    case SKW_SET:
        gCharInfoServer.baseinfo.liveinfo.vigorMax = value;
        break;
    }
    FIX_NORMAL_ZERO( gCharInfoServer.baseinfo.liveinfo.vigorMax );

    ChangeAttr( CharAttr_VigorMax, gCharInfoServer.baseinfo.liveinfo.vigorMax, true );
}

void GamePlayer::Script_SetSkillPoint( int nType, int nValue, int nOp )
{
    if ( nType >= ERT_MaxType )
    { return; }

    switch( nOp ) 
    {
    case SKW_SETADD:
        gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ nType ] += nValue;
        break;
    case SKW_SETSUB:
        gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ nType ]  -= nValue;
        break;
    case SKW_SET:
        gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ nType ]  = nValue;
        break;
    }
    FIX_NORMAL_ZERO( gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ nType ] );

    unsigned short nWhich = GetCharAttrByRecipeType( nType );

    ChangeAttr( nWhich, gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ nType ] , true );
}

void GamePlayer::Script_SetMp( int nMp, int nOp )
{ 
    switch( nOp ) 
    {
    case SKW_SETADD:
        SetMP( GetMP()+nMp );
        break;
    case SKW_SETSUB:
        SetMP( GetMP()-nMp );
        break;
    case SKW_SET:
        SetMP( nMp );
        break;
    default:
        return;
    }

    ChangeAttr( CharAttr_MP, (DWORD)GetMP() );
}

int GamePlayer::Script_GetExp( ) // 经验
{
    return GetPlayerExpUnUsed();
}

int GamePlayer::Script_GetSkillExp( )        // 经验
{
    return GetSkillExp();
}

int GamePlayer::Script_GetCon( )        // 体质
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Stamina].final;
}

int GamePlayer::Script_GetStr( )        // 力量
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Strength].final;
}

int GamePlayer::Script_GetDex( )        // 敏捷
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Agility].final;
}

int GamePlayer::Script_GetInt( )        // 智力
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Intelligence].final;
}

int GamePlayer::Script_GetMgc( )        // 魔力
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Spirit].final;
}

int GamePlayer::Script_GetLky( )        // 魅力
{
    return 0; //gCharInfoServer.baseinfo.BaseAttr[BATTR_Luck].final;
}

int GamePlayer::Script_GetHp( )
{
    return GetHP( );
}

//int GamePlayer::Script_GetTp()
//{
//    return GetTP( );
//}

int GamePlayer::Script_GetMp( )
{
    return GetMP( );
}

//设置出生点
void GamePlayer::Script_SetBornPoint( DWORD dwMapID, int iPosX, int iPosY )
{
    gCharInfoServer.otherdata.sBornPos.dwMapID = dwMapID;
    gCharInfoServer.otherdata.sBornPos.stX     = iPosX;
    gCharInfoServer.otherdata.sBornPos.stY     = iPosY;
}

void GamePlayer::Script_Skill( int iWhichSkill , int nOp ) // 技能
{   
    switch( nOp ) 
    {
    case SKW_SETADD:
        LearnSkill( iWhichSkill );
        break;
    case SKW_SETSUB:
        ForgetSkill( iWhichSkill );
        break;
    }
}

void GamePlayer::Script_AddRecipe( unsigned short ustRecipeID )
{
    MsgAddRecipeAck xAck;
    xAck.ustRecipeID = ustRecipeID;

    RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRuleId( ustRecipeID );
    if ( pRecipe == NULL )
    {
        xAck.chResult = MsgAddRecipeAck::Result_NoThisRecipe;
    }
    else
    {
        if ( _recipeManager.IsExistRecipe(ustRecipeID) )  
        {
            xAck.chResult = MsgAddRecipeAck::Result_AlreadyExist;
        }
        else
        {
            if ( !_recipeManager.AddRecipe(ustRecipeID) )
            {
                xAck.chResult = MsgAddRecipeAck::Result_Full;
            }
        }
    }


    GettheServer().SendMsgToSingle( &xAck, this );
}

//
// 修理物品
//
//bool GamePlayer::Script_MendItem( SCharItem &Item, int nVal )
//{
//    Item.equipdata.usHP += nVal;
//    if( Item.equipdata.usHP > Item.equipdata.usHpMax )
//        Item.equipdata.usHP = Item.equipdata.usHpMax;
//    return true;
//}

void GamePlayer::Script_SetProfession( int nProfession )
{ // 职业
    SetProfession( nProfession );
    MsgProfessionChangeInfo profession;
    profession.stProfession = nProfession;
    GettheServer().SendMsgToSingle( &profession, this );
}


void GamePlayer::Script_SetCon( int nCon, int nOp )        // 体质
{
    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Stamina].final;
    switch( nOp ) 
    {
    case SKW_SETADD:
    *pVal += nCon;
    break;
    case SKW_SETSUB:
    *pVal -= nCon;
    break;
    case SKW_SET:
    *pVal = nCon;
    break;
    default:
    GetErrorLog()->logString("Error:Script_SetCon");
    return;
    }
    SendCharArrtChange( CharAttr_Stamina, (short)*pVal );*/
}

void GamePlayer::Script_SetStr( int nStr, int nOp )        // 力量
{
    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Strength].final;
    switch( nOp ) 
    {
    case SKW_SETADD:
    *pVal += nStr;
    break;
    case SKW_SETSUB:
    *pVal -= nStr;
    break;
    case SKW_SET:
    *pVal = nStr;
    break;
    default:
    GetErrorLog()->logString("Error:Script_SetStr");
    return;
    }
    SendCharArrtChange( CharAttr_Strength, (short)*pVal );*/
}

void GamePlayer::Script_SetDex( int nDex, int nOp )        // 敏捷
{
    /*short *pVal = &gCharInfoServer.baseinfo.BaseAttr[BATTR_Agility].final;
    switch( nOp ) 
    {
    case SKW_SETADD:
    *pVal += nDex;
    break;
    case SKW_SETSUB:
    *pVal -= nDex;
    break;
    case SKW_SET:
    *pVal = nDex;
    break;
    default:
    GetErrorLog()->logString("Error:Script_SetDex");
    return;
    }
    SendCharArrtChange( CharAttr_Agility, (short)*pVal );*/
}

void GamePlayer::SetScriptSleepTime( DWORD dwTime )
{
    m_dwScriptSleep = dwTime;
    m_dwScriptSleepStartTime = HQ_TimeGetTime();
}

void GamePlayer::CheckScriptSleep()
{
    if( m_dwScriptSleep == 0 )
    {  return; }

    if ( GameTime::IsPassCurrentTime( m_dwScriptSleepStartTime, m_dwScriptSleep ) )
    {
        m_dwScriptSleep          = 0;
        m_dwScriptSleepStartTime = 0;
        SScript* pScript = GetScript();
        if ( !pScript )
        { return; }
        GetScriptMgr()->ExecuteVM( ST_UNKNOW, -1, this );
    }
}

bool GamePlayer::Script_IsInArea(int Lx,int Ly,int Rx,int Ry)
{
    int selfx = GetFloatX();
    int selfy = GetFloatY();
    if (selfx > max(Lx,Rx) || selfx < min(Lx,Rx) )
    {
        return false;
    }
    if (selfy > max(Ly,Ry) || selfy < min(Ly,Ry) )
    {
        return false;
    }
    return true;
}

int GamePlayer::Script_SelfPosX()
{
    return static_cast<int>( GetFloatX() );
}

int GamePlayer::Script_SelfPosY()
{
    return static_cast<int>( GetFloatY() );
}

void GamePlayer::Script_DropItemOnMonsterDead(int ItemId,int ItemNum,bool nobelong)
{
    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(ItemId);
    if (NULL == pItem)
    { return; }

    SCharItem item;
	if ( !theRunTimeData.CreateItem( this, pItem->ustItemID, ItemNum, HelperFunc::CreateID(), item) )
	{ return; }

	item.itembaseinfo.ustItemCount = 1;
    if ( !pItem->IsExclusive() ) 
    {
        //if( ItemDefine::ITEMTYPE_RESTORE )
        //{   
        //    item.itembaseinfo.ustItemCount = 99;
        //}
        //else 
        {
            item.itembaseinfo.ustItemCount = ItemNum;
        }
    }
    char szItem[101] = {0};
    memset( szItem, 0, sizeof(szItem));
    sprintf_s( szItem, sizeof( szItem ) - 1, "%s", pItem->GetItemName());

    //需要改成怪物死亡时候的坐标
	theGameWorld.CreateItemNpc( szItem,GetMapID(),GetFloatX(),GetFloatY(),0,item, -1, 0);
	/*if (nobelong)
	{
		theGameWorld.CreateItemNpc( szItem,GetMapID(),GetFloatX(),GetFloatY(),0,item, -1, 0);
	}
	else
		theGameWorld.CreateItemNpc( szItem,GetMapID(),GetFloatX(),GetFloatY(),0,item, GetID(), 0);*/    
}

void GamePlayer::SetAreaRepulation( SAreaRepulation& xArea )
{
    int i = 0;
    for ( ; i < MAX_AREAREPULATION_COUNT; ++i )
    {
        if ( gCharInfoServer.baseinfo.liveinfo.xArea[i].nMapID == -1 )
        { break; }

        if ( gCharInfoServer.baseinfo.liveinfo.xArea[i].nMapID == xArea.nMapID )
        {
            gCharInfoServer.baseinfo.liveinfo.xArea[i] = xArea;
            return;
        }
    }

    if ( i == MAX_AREAREPULATION_COUNT )
    { return; }

    gCharInfoServer.baseinfo.liveinfo.xArea[i] = xArea;
}

SAreaRepulation* GamePlayer::GetAreaRepulation( int nMapID )
{
    for ( int i = 0; i < MAX_AREAREPULATION_COUNT; ++i )
    {
        if ( gCharInfoServer.baseinfo.liveinfo.xArea[i].nMapID == nMapID )
        {
            return &gCharInfoServer.baseinfo.liveinfo.xArea[i];
        }
    }

    return NULL;
}

void GamePlayer::Script_SetAreaCurrentReputation( int nMapID, int nValue, int nOp )
{
    int nCurrentValue = 1;
    int nMaxValue = SAreaRepulation::ECD_Max_Value;
    SAreaRepulation* pArea = GetAreaRepulation( nMapID );
    if ( pArea != NULL )
    {
        nCurrentValue = pArea->nCurrentReputation;
        nMaxValue = pArea->nMaxReputation;
    }

    switch ( nOp )
    {
    case SKW_SET:
        nCurrentValue = nValue;
        break;
    case SKW_SETADD:
        nCurrentValue += nValue;
        break;
    case SKW_SETSUB:
        nCurrentValue -= nValue;
        break;
    default:
        return;
    }

    if ( nCurrentValue < 1 )
        nCurrentValue = 1;
    if ( nCurrentValue > nMaxValue )
        nCurrentValue = nMaxValue;

    SAreaRepulation xArea;
    xArea.nMapID             = nMapID;
    xArea.nCurrentReputation = nCurrentValue;
    xArea.nMaxReputation     = nMaxValue;
    SetAreaRepulation( xArea );

    // 地区声望改变
    ChangeAttr( CharAttr_AreaRepulation, ProcessAreaReputation::SetAreaRepulation( xArea.nMapID, xArea.nCurrentReputation, xArea.nMaxReputation ), true );
}

int GamePlayer::Script_GetAreaCurrentReputation( int nMapID )
{
    int nValue = 0;
    SAreaRepulation* pArea = GetAreaRepulation( nMapID );
    if ( pArea != NULL )
    {
        nValue = pArea->nCurrentReputation;
    }

    return nValue;
}

void GamePlayer::Script_SetAreaMaxReputation( int nMapID, int nValue, int nOp )
{
    int nCurrentValue = 1;
    int nMaxValue = SAreaRepulation::ECD_Max_Value;
    SAreaRepulation* pArea = GetAreaRepulation( nMapID );
    if ( pArea != NULL )
    {
        nCurrentValue = pArea->nCurrentReputation;
        nMaxValue = pArea->nMaxReputation;
    }

    switch ( nOp )
    {
    case SKW_SET:
        nMaxValue = nValue;
        break;
    case SKW_SETADD:
        nMaxValue += nValue;
        break;
    case SKW_SETSUB:
        nMaxValue -= nValue;
        break;
    default:
        return;
    }

    if ( nMaxValue < SAreaRepulation::ECD_Max_Value )
        nMaxValue = SAreaRepulation::ECD_Max_Value;

    SAreaRepulation xArea;
    xArea.nMapID             = nMapID;
    xArea.nCurrentReputation = nCurrentValue;
    xArea.nMaxReputation     = nMaxValue;
    SetAreaRepulation( xArea );

    // 地区声望改变
    ChangeAttr( CharAttr_AreaRepulation, ProcessAreaReputation::SetAreaRepulation( xArea.nMapID, xArea.nCurrentReputation, xArea.nMaxReputation ), true );
}

int GamePlayer::Script_GetAreaMaxReputation( int nMapID )
{
    int nValue = 0;
    SAreaRepulation* pArea = GetAreaRepulation( nMapID );
    if ( pArea != NULL )
    {
        nValue = pArea->nMaxReputation;
    }

    return nValue;
}

//检测是否升级
void GamePlayer::Script_SetExp( __int64 nExp, int nOp, char* szFunction, int nLine )        // 经验
{   
    switch( nOp ) 
    {
    case SKW_SETADD:
        {
            IncreaseExp( nExp, 0 );

				Log( theXmlString.GetString( eLog_Exp_1 ), szFunction, nLine, nExp );
		}
        break;
    case SKW_SETSUB:
        {
            if ( nExp > GetPlayerExpUnUsed() )
                SetPlayerExpUnUsed( 0 );
            else
                SetPlayerExpUnUsed(GetPlayerExpUnUsed() - nExp );

              Log( theXmlString.GetString( eLog_Exp_2 ), szFunction, nLine, nExp );
        }

        break;
    case SKW_SET:
        {
            SetPlayerExpUnUsed( nExp );
            Log( theXmlString.GetString( eLog_Exp_3 ), szFunction, nLine, nExp );
        }
        break;
    default:
        return;
    }
}

//检测是否升级
void GamePlayer::Script_SetSkillExp( int nExp, int nOp )        // 经验
{       
    switch( nOp ) 
    {
    case SKW_SETADD:
        ChangeAttr( CharAttr_CurGetSkillExp , nExp, true);
        SetSkillExpUnUsed( nExp + GetSkillExpUnUsed() );
        break;
    case SKW_SETSUB:
        if ( nExp > GetSkillExpUnUsed() )
            SetSkillExpUnUsed( 0 );
        else
            SetSkillExpUnUsed(GetSkillExpUnUsed() - nExp);
        break;
    case SKW_SET:
        SetSkillExpUnUsed( nExp );
        break;
    default:
        GetErrorLog()->logString("Error:Script_SetSkillExp");
        return;
    }   

    ChangeAttr( CharAttr_SkillExpNotUsed, GetSkillExpUnUsed(), true);
}

bool GamePlayer::Script_IsThisItemEquipped( /*SCharItem &Item */unsigned short ustItemId)
{
    for( int i=0; i<EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pCharItem = GetVisualEquipItem( i );
        if ( pCharItem == NULL )
        { continue; }

        if ( pCharItem->itembaseinfo.ustItemID == ustItemId)
        { return true; }
    }
    return false;
}

bool GamePlayer::Script_IsThisSkillActived( unsigned short ustSkillItemID,unsigned short ustSkillLevel )
{   
    if (  NULL == _SkillBag.GetSkillByID( ustSkillItemID ) )
        return false;

    return true;
}
int GamePlayer::Script_GetWeekKillNum()
{
	return gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum;
}
int GamePlayer::Script_GetAllKillNum()
{
	return gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;
}
int GamePlayer::Script_GetSeriesKillNum()
{
	return m_KillPlayerMap.m_KillAddSum;
}
void GamePlayer::Script_ProcTimeStep(int StringID,int TimeStep)
{
	SendProcessTimeToClient(StringID,TimeStep);
}
