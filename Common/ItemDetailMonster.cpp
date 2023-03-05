#include "ItemDetailConfig.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"

#pragma warning( push, 0 )

int CItemDetail::FindMonsterIndexByName( const char *szName )
{
    Name2IndexMonsterContainer::iterator it = _Name2IndexMonsters.find( szName );
    if( it == _Name2IndexMonsters.end() )
        return -1;
    return it->second;
}

int CItemDetail::FindMonsterIndexById( int nId )
{
    Id2IndexMonsterContainer::iterator it = _Id2IndexMonsters.find( nId );
    if( it == _Id2IndexMonsters.end() )
        return -1;
    return it->second;
}

ItemDefine::SMonster* CItemDetail::GetMonster( int nIndex )
{
    if( _MonsterInfos.empty() )
        return NULL;
    if( nIndex < 0 || nIndex >= (int)_MonsterInfos.size() )
        return NULL;

    return _MonsterInfos[ nIndex ];
}

ItemDefine::SMonster* CItemDetail::GetMonsterById( int nId )
{
    int nIndex = FindMonsterIndexById(nId);
    if ( nIndex == -1)
        return NULL;

    return GetMonster(nIndex);
}

ItemDefine::SMonster* CItemDetail::GetMonsterByName( const char* szName )
{ 
    int nIndex = FindMonsterIndexByName( szName );
    if ( nIndex == -1 )
        return NULL;

    return GetMonster( nIndex ); 
}

bool CItemDetail::LoadSlkMonster( const char *szFile )
{
    CSlkReader reader;
    if( !reader.ReadFromFile( szFile ) )
        return false;

    int   iRow   = 3;
    int   iCol   = 0;
    int   iRet   = 0;
    int   iValue = 0;
    float fValue = 0.0f;

    std::string strTemp;
    std::string strCreatureSound;
    std::string strMonsterName;
    std::string strMonsterNamePrefix;
    std::string strMonsterSkin;
    std::string strDeadScript;
    std::string strAILuaScript;
    std::string strWeaponSound;
    std::string strArmourSound;

    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        ItemDefine::SMonster* pMonster = (ItemDefine::SMonster*)AllocItem( 0, sizeof( ItemDefine::SMonster ) );
        if( !pMonster )
        {
            OutputSlkLoadingMessage( "Error:分配Monster需要的内存出错 [%d]\r\n", iRow );
            return false;
        }

        if( !reader.GetIntFieldByName("MonsterID", iValue) )
        { // 怪物索引ID
            OutputSlkLoadingMessage( "\t  载入怪物索引ID出错!\r\n" );
            goto load_error;
        }
        pMonster->stMonsterId = iValue;

        if( !reader.GetStringFieldByName( "MonsterPrefix",strMonsterNamePrefix ) )
        { // 怪物名前缀
            /*OutputSlkLoadingMessage( "\t  载入-怪物名前缀-出错!\r\n" );
            goto load_error;*/
			strMonsterNamePrefix.clear();
        }
        pMonster->dwNamePrefix = AllocStringCopy( strMonsterNamePrefix.c_str() );

        if( !reader.GetStringFieldByName( "MonsterName",strMonsterName) )
        { // 怪物名字
            OutputSlkLoadingMessage( "\t  载入怪物名字出错!\r\n" );
            goto load_error;
        }
        pMonster->dwNameAddr = AllocStringCopy( strMonsterName.c_str() );
        OutputSlkLoadingMessage( "Load Monster(%s)", strMonsterName.c_str() );

        //怪物职业
        pMonster->stProfession = EArmType_Monster;

        if( !reader.GetIntFieldByName("ModelID",iValue ) )
        { //模型ID
            OutputSlkLoadingMessage( "\t  载入怪物模型ID出错!\r\n" );
            goto load_error;
        }
        pMonster->iModelID = iValue;

        if( !reader.GetStringFieldByName( "MonsterSound", strCreatureSound ) )
        { // 怪物声音模板
            OutputSlkLoadingMessage( "\t  载入怪物声音模板出错!\r\n" );
            goto load_error;
        }
        pMonster->dwCreatureSoundAddr = AllocStringCopy( strCreatureSound.c_str() );

        if( !reader.GetStringFieldByName( "MonsterType", strTemp ))
        { //怪物类别
            OutputSlkLoadingMessage( "\t  载入怪物类别出错!\r\n" );
            goto load_error;
        }
        pMonster->stMonsterType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(), ItemDefine::g_szMonsterType, sizeof(ItemDefine::g_szMonsterType)/sizeof( char* ) );

        if( !reader.GetFloatFieldByName( "BodyModify", fValue ) )
        { // 体型修正
            OutputSlkLoadingMessage( "\t载入-体型修正-出错!\r\n" );
            goto load_error;
        }
        pMonster->fBodySize = fValue;

        if( !reader.GetFloatFieldByName( "BodyLengthSize", fValue ) )
        {
            OutputSlkLoadingMessage( "\t载入-体型修正-出错!\r\n" );
            goto load_error;
        }
        pMonster->fBodyLengthSize = fValue;

        if( !reader.GetIntFieldByName( "MonsterLv",iValue ) )
        { // 级别
            OutputSlkLoadingMessage( "\t 载入怪物级别出错!\r\n" );
            goto load_error;
        }
        pMonster->stLevel = iValue;

        if( !reader.GetIntFieldByName( "MonsterExp",iValue ) )
        { // 经验值
            OutputSlkLoadingMessage( "\t 载入经验值出错!\r\n" );
            goto load_error;
        }
        pMonster->nRewardExp = iValue;

        if( !reader.GetIntFieldByName( "MonsterReputation",iValue ) )
        { // 经验值
            OutputSlkLoadingMessage( "\t 载入声望值出错!\r\n" );
            goto load_error;
        }
        pMonster->nRewardReputation = iValue;

        if( !reader.GetIntFieldByName( "MonsterExploit",iValue ) )
        { // 经验值
            OutputSlkLoadingMessage( "\t 载入功勋值出错!\r\n" );
            goto load_error;
        }
        pMonster->nRewardExploit = iValue;

        if( !reader.GetIntFieldByName( "RewardFriendly",iValue ) )
        { // 经验值
            OutputSlkLoadingMessage( "\t 载入奖励好友度出错!\r\n" );
            goto load_error;
        }
        pMonster->nRewardFriendly = iValue;

        if( !reader.GetIntFieldByName( "Daoxing",iValue ) )
        { // 道行
            OutputSlkLoadingMessage( "\t 载入道行出错!\r\n" );
            goto load_error;
        }
        pMonster->nDaoxing = iValue;

        if( !reader.GetIntFieldByName( "RewardDaoxing",iValue ) )
        { // 奖励道行
            OutputSlkLoadingMessage( "\t 载入奖励道行出错!\r\n" );
            goto load_error;
        }
        pMonster->nRewardDaoxing = iValue;

        if( !reader.GetIntFieldByName( "MaxHP",iValue ) )
        { // 最大HP(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-最大HP(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->nHPMax = iValue;

        if( !reader.GetIntFieldByName( "MaxMP",iValue ) )
        { // 最大MP(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-最大MP(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stMPMax = iValue;

        if( !reader.GetIntFieldByName( "RecoverHP",iValue ) )
        { // HP恢复速度(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-HP恢复速度(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stHPRestore = iValue;

        if( !reader.GetIntFieldByName( "RecoverMP",iValue ) )
        { // MP恢复速度(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-MP恢复速度(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stMPRestore = iValue;

        if( !reader.GetIntFieldByName( "Hit",iValue ) )
        { // 精确值(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-精确值(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stExact = iValue;

        if( !reader.GetIntFieldByName("Dodge",iValue ) )
        { // 躲避率(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-躲避率(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stDodge = iValue;

        if( !reader.GetFloatFieldByName( "PhyAtk", fValue ))
        { // 物攻(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-理攻(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->fPhysicAtt = fValue;

        if( !reader.GetFloatFieldByName( "MagicAtk", fValue ))
        { // 法攻(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-法攻(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->fMagicAtt = fValue;        

        if( !reader.GetIntFieldByName( "AtkSpeed", iValue ))
        { // 攻击速度(基础)
            OutputSlkLoadingMessage( "\t  载入怪物-攻击速度(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stAttackRate = iValue;

        if( !reader.GetFloatFieldByName( "PhyDef", fValue ))
        { // 物防
            OutputSlkLoadingMessage( "\t  载入怪物-物防(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->fPhysicDef = fValue;

        if( !reader.GetFloatFieldByName( "MagicDef", fValue ))
        { // 法防
            OutputSlkLoadingMessage( "\t  载入怪物-法防(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->fMagicDef = fValue;

        if( !reader.GetFloatFieldByName( "Critical", fValue ))
        { // 暴击率
            OutputSlkLoadingMessage( "\t  载入怪物-暴击率(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->critical = fValue;

        if( !reader.GetIntFieldByName( "CriticalIntensity", iValue ))
        { // 暴击伤害
            OutputSlkLoadingMessage( "\t  载入怪物-暴击伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->criticalIntensity = iValue;

        if( !reader.GetIntFieldByName( "Tenacity", iValue ))
        { // 韧性
            OutputSlkLoadingMessage( "\t  载入怪物-韧性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->tenacity = iValue;

        if( !reader.GetIntFieldByName( "BackStrike", iValue ))
        { // 背击伤害
            OutputSlkLoadingMessage( "\t  载入怪物-背击伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->backStrike = iValue;

        if( !reader.GetIntFieldByName( "BackStrikeResist", iValue ))
        { // 背击抗性
            OutputSlkLoadingMessage( "\t  载入怪物-背击抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->backStrikeResist = iValue;

        if( !reader.GetIntFieldByName( "BreakStrike", iValue ))
        { // 破甲伤害
            OutputSlkLoadingMessage( "\t  载入怪物-破甲伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->breakStrike = iValue;

        if( !reader.GetIntFieldByName( "StabStrike", iValue ))
        { // 贯穿伤害
            OutputSlkLoadingMessage( "\t  载入怪物-韧性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stabStrike  = iValue;

        if( !reader.GetIntFieldByName( "ElementStrike", iValue ))
        { // 元素伤害
            OutputSlkLoadingMessage( "\t  载入怪物-元素伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->elementStrike = iValue;

        if( !reader.GetIntFieldByName( "ToxinStrike", iValue ))
        { // 毒素伤害
            OutputSlkLoadingMessage( "\t  载入怪物-毒素伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->toxinStrike = iValue;

        if( !reader.GetIntFieldByName( "SpiritStrike", iValue ))
        { // 精神伤害
            OutputSlkLoadingMessage( "\t  载入怪物-精神伤害(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->spiritStrike = iValue;

        if( !reader.GetIntFieldByName( "BreakResist", iValue ))
        { // 破甲抗性
            OutputSlkLoadingMessage( "\t  载入怪物-破甲抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->breakResist = iValue;

        if( !reader.GetIntFieldByName( "StabResist", iValue ))
        { // 破甲抗性
            OutputSlkLoadingMessage( "\t  载入怪物-破甲抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->stabResist = iValue;

        if( !reader.GetIntFieldByName( "ElementResist", iValue ))
        { // 元素抗性
            OutputSlkLoadingMessage( "\t  载入怪物-元素抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->elementResist = iValue;

        if( !reader.GetIntFieldByName( "ToxinResist", iValue ))
        { // 毒素抗性
            OutputSlkLoadingMessage( "\t  载入怪物-毒素抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->toxinResist = iValue;

        if( !reader.GetIntFieldByName( "SpiritResist", iValue ))
        { // 精神抗性
            OutputSlkLoadingMessage( "\t  载入怪物-精神抗性(基础)-出错!\r\n" );
            goto load_error;
        }
        pMonster->spiritResist = iValue;
        
        if( !reader.GetIntFieldByName( "EyeShot", iValue ))
        { // 视野
            OutputSlkLoadingMessage( "\t  载入怪物视野出错!\r\n" );
            goto load_error;
        }
        pMonster->stView = iValue;

        if( !reader.GetIntFieldByName( "FightShot", iValue ))
        { // 战斗视野
            OutputSlkLoadingMessage( "\t  载入怪物战斗视野出错!\r\n" );
            goto load_error;
        }
        pMonster->stFightView = iValue;

        if( !reader.GetFloatFieldByName( "AttackPhysicsMod", fValue ))
        { //物攻系数
            OutputSlkLoadingMessage( "\t  载入物功系数出错!\r\n" );
            goto load_error;
        }
        pMonster->fAttackPhysicsMod = fValue;

        if( !reader.GetFloatFieldByName( "AttackMagicMod", fValue ))
        { //法攻系数
            OutputSlkLoadingMessage( "\t  载入法功系数出错!\r\n" );
            goto load_error;
        }
        pMonster->fAttackMagicMod = fValue;

        if( !reader.GetFloatFieldByName( "DefendPhysicsMod", fValue ))
        { //物防系数
            OutputSlkLoadingMessage( "\t  载入物防系数出错!\r\n" );
            goto load_error;
        }
        pMonster->fDefendPhysicsMod = fValue;

        if( !reader.GetFloatFieldByName( "DefendMagicMod", fValue ))
        { //法防系数
            OutputSlkLoadingMessage( "\t  载入法防系数出错!\r\n" );
            goto load_error;
        }
        pMonster->fDefendMagicMod = fValue;

        if( !reader.GetIntFieldByName( "AttackFloatMin", iValue ))
        { //攻击最小系数
            OutputSlkLoadingMessage( "\t  载入攻击最小系数出错!\r\n" );
            goto load_error;
        }
        pMonster->nAttackFloatMin = iValue;

        if( !reader.GetIntFieldByName( "AttackFloatMax", iValue ))
        { //攻击最大系数
            OutputSlkLoadingMessage( "\t  载入攻击最大系数出错!\r\n" );
            goto load_error;
        }
        pMonster->nAttackFloatMax = iValue;

        if( !reader.GetIntFieldByName( "ChaseTime", iValue ))
        { //怪物的追击时间
            OutputSlkLoadingMessage( "\t  载入追击时间出错!\r\n" );
            goto load_error;
        }
        pMonster->dwCatchTime = iValue;

        if( !reader.GetFloatFieldByName( "MoveSpeed", fValue ))
        { //怪物的移动速度
            OutputSlkLoadingMessage( "\t 载入怪物移动速度出错!\r\n" );
            goto load_error;
        }
        pMonster->fMoveSpeed = fValue;

        char szBuffer[129] = {0};
        for ( int i=0; i < ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i )
        {            
            sprintf_s( szBuffer, sizeof( szBuffer ) - 1, "UseSkill%d", i+1);

            //可能使用的技能
            if( !reader.GetIntFieldByName( szBuffer, iValue ))
            { 
                OutputSlkLoadingMessage( "\t  载入怪物可能使用的技能%d出错!\r\n", i );
                goto load_error;
            }
            if (iValue > 0)
                pMonster->iSkillID[i] = iValue;
            else
                pMonster->iSkillID[i] = InvalidLogicNumber;

            //技能等级
            sprintf_s( szBuffer, sizeof( szBuffer ) - 1, "Skill%dLv", i+1);
            if( !reader.GetIntFieldByName( szBuffer, iValue ))
            {
                OutputSlkLoadingMessage( "\t  载入技能%d等级出错!\r\n", i );
                goto load_error;
            }
            pMonster->stSkillLevel[ i ] = iValue;

            //技能使用概率
            sprintf_s( szBuffer, sizeof( szBuffer ) - 1, "ChanceOfSkill%d", i+1);
            if( !reader.GetIntFieldByName( szBuffer, iValue ))
            {
                OutputSlkLoadingMessage( "\t  载入技能%d使用概率出错!\r\n", i );
                goto load_error;
            }
            pMonster->stSkillRate[ i ] = iValue;
        }

        if( !reader.GetIntFieldByName( "MinDropMoney", iValue ))
        { //掉落金钱最小
            OutputSlkLoadingMessage( "\t  载入掉落金钱最小出错!\r\n" );
            goto load_error;
        }
        pMonster->stDropMinMoney = iValue;

        if( !reader.GetIntFieldByName( "MaxDropMoney", iValue ))
        { //掉落金钱最大
            OutputSlkLoadingMessage( "\t  载入掉落金钱最大出错!\r\n" );
            goto load_error;
        }
        pMonster->stDropMaxMoney = iValue;

        if( !reader.GetFloatFieldByName( "DropItemRate", fValue ))
        { //物品掉落倍率
            OutputSlkLoadingMessage( "\t  载入物品掉落倍率出错!\r\n" );
            goto load_error;
        }
        pMonster->fItemDropMultipleRate = fValue;

        if( !reader.GetIntFieldByName( "IfInitiative", iValue ))
        { //是否主动怪
            OutputSlkLoadingMessage( "\t  载入是否主动怪出错!\r\n" );
            goto load_error;
        }
        pMonster->nIsInitiative = iValue;

        if( !reader.GetStringFieldByName( "MonsterSkin", strMonsterSkin ) )
        { //怪物皮肤
            OutputSlkLoadingMessage( "\t  载入怪物皮肤出错!\r\n" );
            goto load_error;
        }
        pMonster->dwSkinAddr = AllocStringCopy( strMonsterSkin.c_str() );

        if( !reader.GetFloatFieldByName( "MonsterAlpha", fValue ))
        { //怪物透明度
            OutputSlkLoadingMessage( "\t  载入[怪物透明度]出错!\r\n" );
            goto load_error;
        }
        pMonster->fAlpha = fValue;

        if( !reader.GetIntFieldByName( "ReviveTime", iValue ))
        { //复活时间
            OutputSlkLoadingMessage( "\t  载入怪物复活时间出错!\r\n" );
            goto load_error;
        }
        pMonster->nReliveTime = iValue;

        if( !reader.GetIntFieldByName( "IfDisappear", iValue ))
        { //是否消失
            OutputSlkLoadingMessage( "\t  怪物载入是否消失出错!\r\n" );
            goto load_error;
        }
        pMonster->bIsDisappear = iValue;

        if( !reader.GetIntFieldByName( "DisappearTime", iValue ))
        { //消失时间
            OutputSlkLoadingMessage( "\t  载入怪物消失时间出错!\r\n" );
            goto load_error;
        }
        pMonster->dwDisappearTime = iValue;


        strDeadScript = "";
        if( !reader.GetStringFieldByName( "DeathScript",strDeadScript ) )
        { //默认死亡脚本
        }
        pMonster->dwDeadScriptAddr = AllocStringCopy( strDeadScript.c_str() );

        if( !reader.GetStringFieldByName( "AIScript",strAILuaScript ) )
        { //默认AI脚本
            OutputSlkLoadingMessage( "\t 载入-怪物AI脚本 [%s]-出错!\r\n", strAILuaScript.c_str() );
            goto load_error;
        }
        pMonster->dwAILuaScriptAddr = AllocStringCopy( strAILuaScript.c_str() );

        if( !reader.GetStringFieldByName( "MonsterWeaponSoundPrefix", strWeaponSound ))
        { //怪物武器音效前缀
            OutputSlkLoadingMessage( "\t  载入-怪物武器音效前缀-出错!\r\n" );
            goto load_error;
        }
        pMonster->dwWeaponSoundAddr = AllocStringCopy( strWeaponSound.c_str() );

        if( !reader.GetStringFieldByName( "MonsterArmorSoundPrefix", strArmourSound ))
        { //怪物防具音效前缀
            OutputSlkLoadingMessage( "\t  载入-怪物防具音效前缀-出错!\r\n" );
            goto load_error;
        }
        pMonster->dwArmourSoundAddr = AllocStringCopy( strArmourSound.c_str() );


        if( !reader.GetFloatFieldByName( "RunStep", fValue ) )
        { //怪物奔跑步长
            OutputSlkLoadingMessage( "\t 载入怪物-奔跑步长-出错!\r\n" );
            goto load_error;
        }
        pMonster->fRunStep = fValue;


        if( !reader.GetFloatFieldByName( "WalkStep", fValue ) )
        { //怪物行走步长
            OutputSlkLoadingMessage( "\t 载入怪物-行走步长-出错!\r\n" );
            goto load_error;
        }
        pMonster->fMovingStep = fValue;

        if( !reader.GetIntFieldByName( "IfHalfLengthMonster", iValue ) )
        { //是否上下半身怪物
            OutputSlkLoadingMessage( "\t 载入怪物-是否上下半身怪物-出错!\r\n" );
            goto load_error;
        }
        pMonster->nIsHaveTwoHalfBody = iValue;

        if( !reader.GetIntFieldByName( "IfFourFeetMonster", iValue ) )
        { //是否四足怪物
            OutputSlkLoadingMessage( "\t 载入怪物-是否四足怪物-出错!\r\n" );
            goto load_error;
        }
        pMonster->nIsHaveFourFoot = iValue;

        if( !reader.GetIntFieldByName( "MonsterSide", iValue ) )
        { //所属阵营
            OutputSlkLoadingMessage( "\t 载入怪物-怪物阵营-出错!\r\n" );
            goto load_error;
        }
        pMonster->nMonsterSide = iValue;

        if (!reader.GetIntFieldByName("EnemityRate", iValue))
        { // 仇恨比率
            OutputSlkLoadingMessage( "\t 载入怪物-仇恨比率-出错!\r\n" );
            goto load_error;
        }
        pMonster->nEnmityRate = iValue;

        if (!reader.GetIntFieldByName("InitialEnemity", iValue))
        { // 视野触发仇恨
            OutputSlkLoadingMessage( "\t 载入怪物-视野触发仇恨初值-出错!\r\n" );
            goto load_error;
        }
        pMonster->nEnmity = iValue;

        if (!reader.GetIntFieldByName("ResistUnmovable", iValue))
        { // 不能移动被抵抗
            OutputSlkLoadingMessage( "\t 载入怪物-不能被抵抗1-出错!\r\n" );
            goto load_error;
        }
        pMonster->nResistMove = iValue;

        if (!reader.GetIntFieldByName("ResistUnatkable", iValue))
        { // 不能攻击被抵抗
            OutputSlkLoadingMessage( "\t 载入怪物-不能被抵抗2-出错!\r\n" );
            goto load_error;
        }
        pMonster->nResistAtt = iValue;

        if (!reader.GetIntFieldByName("ResistUncastable", iValue))
        { // 不能施法被抵抗
            OutputSlkLoadingMessage( "\t 载入怪物-不能被抵抗3-出错!\r\n" );
            goto load_error;
        }
        pMonster->nResistMagic = iValue;

        if (!reader.GetIntFieldByName("ResistUnitemusable", iValue))
        { // 不能用道具被抵抗
            OutputSlkLoadingMessage( "\t 载入怪物-不能被抵抗4-出错!\r\n" );
            GetErrorLog()->logString( "pMonster->slk  载入怪物-不能被抵抗4-出错!");
            goto load_error;
        }
        pMonster->nResistTools = iValue;

        if (!reader.GetIntFieldByName("ExtraSkillExp", iValue))
        { // 额外技能经验
            OutputSlkLoadingMessage( "\t 载入怪物-额外技能经验-出错!\r\n" );
            goto load_error;
        }
        pMonster->nSuperfluitySkillExp = iValue;

        if (!reader.GetIntFieldByName("MaxActArea", iValue))
        { // 最大活动范围
            OutputSlkLoadingMessage( "\t 载入怪物-最大活动范围-出错!\r\n" );
            goto load_error;
        }
        pMonster->nMaxRange = iValue;

        if (!reader.GetIntFieldByName("ChangePassive", iValue))
        { // 战斗中变为被动怪
            OutputSlkLoadingMessage( "\t 载入怪物-战斗中变为被动怪-出错!\r\n" );
            goto load_error;
        }
        pMonster->nChangePassive = iValue;

        if (!reader.GetIntFieldByName("PassiveTime", iValue))
        { // 战斗结束被动持续秒数
            OutputSlkLoadingMessage( "\t 载入怪物-战斗结束被动持续秒数-出错!\r\n" );
            goto load_error;
        }
        pMonster->nPassiveTime = iValue;

        if (!reader.GetIntFieldByName("BaseEnmityRange", iValue))
        { // 基础仇恨保持范围
            OutputSlkLoadingMessage( "\t 载入怪物-基础仇恨保持范围-出错!\r\n" );
            goto load_error;
        }
        pMonster->nBaseEnmityRange = iValue;

        if (!reader.GetFloatFieldByName("IdleMoveSpeed", fValue))
        { // 空闲移动速度
            OutputSlkLoadingMessage( "\t 载入怪物-空闲移动速度-出错!\r\n" );
            goto load_error;
        }
        pMonster->fIdleMoveSpeed = fValue;

        if (!reader.GetIntFieldByName("citymonster", iValue))
        { // 城市怪(不能被守城方攻击)
            OutputSlkLoadingMessage( "\t 城市怪(不能被守城方攻击)-出错!\r\n" );
            goto load_error;
        }
        pMonster->bIsCityMonster = iValue;

        if (!reader.GetIntFieldByName("citydefmonster", iValue))
        { // 城市防守怪(只攻击攻城的)
            OutputSlkLoadingMessage( "\t 城市防守怪(只攻击攻城的)-出错!\r\n" );
            goto load_error;
        }
        pMonster->bIsCityDefMonster = iValue;


        strTemp.clear();
        if (!reader.GetStringFieldByName("MonsterTitle", strTemp))
        { // 怪物称号
        }        
        pMonster->strTitleAddress = AllocStringCopy( strTemp.c_str() );

        strTemp = "";
        if( !reader.GetStringFieldByName( "FrontFoot",strTemp ) )
        { //
        }
        pMonster->dwFrontFootPrintAddr = AllocStringCopy( strTemp.c_str() );

        strTemp = "";
        if( !reader.GetStringFieldByName( "BackFoot",strTemp ) )
        { //
        }
        pMonster->dwBackFootPrintAddr = AllocStringCopy( strTemp.c_str() );

        pMonster->nRelativeQuest = 0;
        if ( reader.GetIntFieldByName("NeedQuest", iValue))
        { pMonster->nRelativeQuest = iValue;}

        pMonster->visualType = ItemDefine::EMVT_Normal;
        if ( reader.GetIntFieldByName("VisualType", iValue))
        { pMonster->visualType = iValue;}

        if ( !reader.GetIntFieldByName("IdleMoveRate", iValue))
        { goto load_error; }
        pMonster->nIdleMoveRate = iValue;

        if ( !reader.GetIntFieldByName("BornProtectTime", iValue))
        { goto load_error; }
        pMonster->dwBornProtectTime = iValue;

        if ( !reader.GetIntFieldByName("RestoreSpaceTime", iValue))
        { goto load_error; }
        pMonster->dwRestoreSpaceTime = iValue;

        if ( !reader.GetIntFieldByName("CashMoney", iValue))
        { goto load_error; }
        pMonster->nCashMoney = iValue;

        if ( !reader.GetIntFieldByName("RewardStatusID", iValue))
        { goto load_error; }
        pMonster->nRewardStatusID = iValue;

        if ( !reader.GetIntFieldByName("RewardMulType", iValue))
        { goto load_error; }
        pMonster->nRewardMulType = iValue;

        if ( !reader.GetIntFieldByName("RewardMulValue", iValue))
        { goto load_error; }
        pMonster->nRewardMulValue = iValue;

		if ( !reader.GetIntFieldByName("IsFindParth", iValue))
		{ goto load_error; }
		pMonster->blIsFindParth = iValue == 0 ? false : true;

		if ( !reader.GetIntFieldByName("IsDynamicBlock", iValue))
		{ goto load_error; }
		pMonster->blIsDynamicBlock = iValue == 0 ? false : true;

        if ( !reader.GetIntFieldByName("CatchPetID", iValue))
        { goto load_error; }
        pMonster->nCatchPetID = iValue;

        if ( !reader.GetIntFieldByName("CatchBaseRate", iValue))
        { goto load_error; }
        pMonster->nCatchBaseRate = iValue;

        if ( !reader.GetIntFieldByName("PetQuality", iValue))
        { goto load_error; }
        pMonster->nPetQuality = iValue;

        if( !reader.GetIntFieldByName("Phyle",iValue ) )
        { goto load_error; }
        pMonster->phyle = iValue;

        if( !reader.GetIntFieldByName("FiveElements",iValue ) )
        { goto load_error; }
        pMonster->element = iValue;

		if( !reader.GetIntFieldByName("GroupID",iValue ) )
		{ goto load_error; }
		pMonster->nGroupID = iValue;

		if( !reader.GetIntFieldByName("DropType",iValue ) )
		{ goto load_error; }
		pMonster->nDropType = iValue;

		pMonster->iMonsterContainerIndex = _MonsterInfos.size();

        //加入查找
        _Name2IndexMonsters.insert( Name2IndexMonsterContainer::value_type( pMonster->GetName(), pMonster->iMonsterContainerIndex ) );
        _Id2IndexMonsters.insert( Id2IndexMonsterContainer::value_type( pMonster->stMonsterId, pMonster->iMonsterContainerIndex) );

        //加入队列
        _MonsterInfos.push_back( pMonster );
        continue;

load_error:
        OutputSlkLoadingMessage( "\tmonster.slk 第 %d 行载入失败!\r\n",iRow-1 );
        return false;
    }
    return true;
}

bool CItemDetail::LoadXmlMonster( const char *szFile )
{
    if (szFile == NULL)
    { return false; }

    MeXmlDocument mMeXmlDoc;
    if (!mMeXmlDoc.LoadFile(szFile))
    { return false; }

    MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pMonsterTree = pRoot->FirstChildElement("Monsters");
    if (pMonsterTree == NULL)
    { return false; }

    MeXmlElement *pElement = pMonsterTree->FirstChildElement("Monster");

    int iValue = 0;
    double dValue = 0.000000;

    while(pElement != NULL)
    {
        ItemDefine::SMonster* pMonster = (ItemDefine::SMonster*)AllocItem( 0, sizeof( ItemDefine::SMonster ) );

        if (pElement->Attribute("MonsterID", &pMonster->stMonsterId) == NULL)
        {
            return false;
        }
        Common::_tstring strMonsterNamePrefix;
        strMonsterNamePrefix.fromUTF8(pElement->Attribute("MonsterPrefix"));
        pMonster->dwNamePrefix = AllocStringCopy(strMonsterNamePrefix.c_str());

        Common::_tstring strMonsterName;
        strMonsterName.fromUTF8(pElement->Attribute("MonsterName"));
        pMonster->dwNameAddr = AllocStringCopy(strMonsterName.c_str());

        pElement->Attribute("ModelID", &iValue);
        pMonster->iModelID = iValue;

        Common::_tstring strCreatureSound;
        strCreatureSound.fromUTF8(pElement->Attribute("MonsterSound"));
        pMonster->dwCreatureSoundAddr = AllocStringCopy(strCreatureSound.c_str());

        pElement->Attribute("MonsterType", &iValue);
        pMonster->stMonsterType = iValue;

        pElement->Attribute("BodyModify", &dValue);
        pMonster->fBodySize = dValue;

        pElement->Attribute("BodyLengthSize", &dValue);
        pMonster->fBodyLengthSize = dValue;

        pElement->Attribute("MonsterLv", &iValue);
        pMonster->stLevel = iValue;

        pElement->Attribute("MonsterExp", &iValue);
        pMonster->nRewardExp = iValue;

        pElement->Attribute("MaxHP", &iValue);
        pMonster->nHPMax = iValue;

        pElement->Attribute("PhyAtk", &dValue);
        pMonster->fPhysicAtt = dValue;

        pElement->Attribute("MagicAtk", &dValue);
        pMonster->fMagicAtt = dValue;

        pElement->Attribute("PhyDef", &dValue);
        pMonster->fPhysicDef = dValue;

        pElement->Attribute("MagicDef", &dValue);
        pMonster->fMagicDef = dValue;

        pElement->Attribute("Critical", &dValue);
        pMonster->critical = dValue;

        pElement->Attribute("CriticalIntensity", &iValue);
        pMonster->criticalIntensity = iValue;

        pElement->Attribute("Tenacity", &iValue);
        pMonster->tenacity = iValue;

        pElement->Attribute("BackStrike", &iValue);
        pMonster->backStrike = iValue;

        pElement->Attribute("BackStrikeResist", &iValue);
        pMonster->backStrikeResist = iValue;

        pElement->Attribute("BreakStrike", &iValue);
        pMonster->breakStrike = iValue;

        pElement->Attribute("StabStrike", &iValue);
        pMonster->stabStrike = iValue;

        pElement->Attribute("ElementStrike", &iValue);
        pMonster->elementStrike = iValue;

        pElement->Attribute("ToxinStrike", &iValue);
        pMonster->toxinStrike = iValue;

        pElement->Attribute("SpiritStrike", &iValue);
        pMonster->spiritStrike = iValue;

        pElement->Attribute("BreakResist", &iValue);
        pMonster->breakResist = iValue;

        pElement->Attribute("StabResist", &iValue);
        pMonster->stabResist = iValue;

        pElement->Attribute("ElementResist", &iValue);
        pMonster->elementResist = iValue;

        pElement->Attribute("ToxinResist", &iValue);
        pMonster->toxinResist = iValue;

        pElement->Attribute("SpiritResist", &iValue);
        pMonster->spiritResist = iValue;
        
        pElement->Attribute("MaxMP", &iValue);
        pMonster->stMPMax = iValue;

        pElement->Attribute("RecoverHP", &iValue);
        pMonster->stHPRestore = iValue;

        pElement->Attribute("RecoverMP", &iValue);
        pMonster->stMPRestore = iValue;

        pElement->Attribute("Hit", &iValue);
        pMonster->stExact = iValue;

        pElement->Attribute("Dodge", &iValue);
        pMonster->stDodge = iValue;

        pElement->Attribute("AtkSpeed", &iValue);
        pMonster->stAttackRate = iValue;

        pElement->Attribute("EyeShot", &iValue);
        pMonster->stView = iValue;

        pElement->Attribute("FightShot", &iValue);
        pMonster->stFightView = iValue;

        pElement->Attribute("AttackPhysicsMod", &dValue);
        pMonster->fAttackPhysicsMod = dValue;

        pElement->Attribute("AttackMagicMod", &dValue);
        pMonster->fAttackMagicMod = dValue;

        pElement->Attribute("DefendPhysicsMod", &dValue);
        pMonster->fDefendPhysicsMod = dValue;

        pElement->Attribute("DefendMagicMod", &dValue);
        pMonster->fDefendMagicMod = dValue;

        pElement->Attribute("AttackFloatMin", &iValue);
        pMonster->nAttackFloatMin = iValue;

        pElement->Attribute("AttackFloatMax", &iValue);
        pMonster->nAttackFloatMax = iValue;

        pElement->Attribute("ChaseTime", &iValue);
        pMonster->dwCatchTime = iValue;

        pElement->Attribute("MoveSpeed", &dValue);
        pMonster->fMoveSpeed = dValue;

        for (int i = 0; i < ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i)
        {
            char szTmpBuffer[129] = {0};

            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "UseSkill%d", i+1);
            pElement->Attribute(szTmpBuffer, &iValue);
            if (iValue > 0)
                pMonster->iSkillID[i] = iValue;
            else
                pMonster->iSkillID[i] = ErrorUnsignedShortID;

            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "Skill%dLv",i+1);
            pElement->Attribute(szTmpBuffer, &iValue);
            pMonster->stSkillLevel[i] = iValue;

            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "ChanceOfSkill%d", i+1);
            pElement->Attribute(szTmpBuffer, &iValue);
            pMonster->stSkillRate[i] = iValue;
        }

        pElement->Attribute("MinDropMoney", &iValue);
        pMonster->stDropMinMoney = iValue;

        pElement->Attribute("MaxDropMoney", &iValue);
        pMonster->stDropMaxMoney = iValue;

        pElement->Attribute("DropItemRate", &dValue);
        pMonster->fItemDropMultipleRate = dValue;

        pElement->Attribute("IfInitiative",&iValue);
        pMonster->nIsInitiative = iValue;

        Common::_tstring strMonsterSkin;
        strMonsterSkin.fromUTF8(pElement->Attribute("MonsterSkin"));
        pMonster->dwSkinAddr = AllocStringCopy(strMonsterSkin.c_str());

        pElement->Attribute("MonsterAlpha", &dValue);
        pMonster->fAlpha = dValue;

        pElement->Attribute("ReviveTime", &iValue);
        pMonster->nReliveTime = iValue;

        pElement->Attribute("IfDisappear", &iValue);
        pMonster->bIsDisappear = iValue;

        pElement->Attribute("DisappearTime", &dValue);
        pMonster->dwDisappearTime = dValue;

        Common::_tstring strDeadScript;
        strDeadScript.fromUTF8(pElement->Attribute("DeathScript"));
        pMonster->dwDeadScriptAddr = AllocStringCopy(strDeadScript.c_str());

        Common::_tstring strAILuaScript;
        strAILuaScript.fromUTF8(pElement->Attribute("AIScript"));
        pMonster->dwAILuaScriptAddr = AllocStringCopy(strAILuaScript.c_str());

        Common::_tstring strWeaponSound;
        strWeaponSound.fromUTF8(pElement->Attribute("MonsterWeaponSoundPrefix"));
        pMonster->dwWeaponSoundAddr = AllocStringCopy(strWeaponSound.c_str());

        Common::_tstring strArmourSound;
        strArmourSound.fromUTF8(pElement->Attribute("MonsterArmorSoundPrefix"));
        pMonster->dwArmourSoundAddr = AllocStringCopy(strArmourSound.c_str());

        pElement->Attribute("RunStep", &dValue);
        pMonster->fRunStep = dValue;

        pElement->Attribute("WalkStep", &dValue);
        pMonster->fMovingStep = dValue;

        pElement->Attribute("IfHalfLengthMonster", &iValue);
        pMonster->nIsHaveTwoHalfBody = iValue;

        pElement->Attribute("IfFourFeetMonster", &iValue);
        pMonster->nIsHaveFourFoot = iValue;

        pElement->Attribute("MonsterSide", &iValue);
        pMonster->nMonsterSide = iValue;

        pElement->Attribute("EnemityRate",&iValue);
        pMonster->nEnmityRate = iValue;

        pElement->Attribute("InitialEnemity", &iValue);
        pMonster->nEnmity = iValue;

        pElement->Attribute("ResistUnmovable", &iValue);
        pMonster->nResistMove = iValue;

        pElement->Attribute("ResistUnatkable",&iValue);
        pMonster->nResistAtt = iValue;

        pElement->Attribute("ResistUncastable",&iValue);
        pMonster->nResistMagic = iValue;

        pElement->Attribute("ResistUnitemusable",&iValue);
        pMonster->nResistTools = iValue;

        pElement->Attribute("ExtraSkillExp", &iValue);
        pMonster->nSuperfluitySkillExp = iValue;

        pElement->Attribute("MaxActArea", &iValue);
        pMonster->nMaxRange = iValue;

        pElement->Attribute("ChangePassive", &iValue);
        pMonster->nChangePassive = iValue;

        pElement->Attribute("PassiveTime", &iValue);
        pMonster->nPassiveTime = iValue;

        pElement->Attribute("BaseEnmityRange", &iValue);
        pMonster->nBaseEnmityRange = iValue;

        pElement->Attribute("IdleMoveSpeed", &dValue);
        pMonster->fIdleMoveSpeed = dValue;

        pElement->Attribute("Citymonster", &iValue);
        pMonster->bIsCityMonster = iValue;

        pElement->Attribute("Citydefmonster", &iValue);
        pMonster->bIsCityDefMonster = iValue;

        Common::_tstring strTitle;
        strTitle.fromUTF8(pElement->Attribute("MonsterTitle"));
        pMonster->strTitleAddress = AllocStringCopy(strTitle.c_str());

        Common::_tstring strFrontFootPrint;
        strFrontFootPrint.fromUTF8(pElement->Attribute("FrontFoot"));
        pMonster->dwFrontFootPrintAddr = AllocStringCopy(strFrontFootPrint.c_str());

        Common::_tstring strBackFootPrint;
        strBackFootPrint.fromUTF8(pElement->Attribute("BackFoot"));
        pMonster->dwBackFootPrintAddr = AllocStringCopy(strBackFootPrint.c_str());

        pElement->Attribute("NeedQuest", &iValue);
        pMonster->nRelativeQuest = iValue;

        pElement->Attribute("MonsterReputation", &iValue);
        pMonster->nRewardReputation = iValue;

        pElement->Attribute("MonsterExploit",&iValue);
        pMonster->nRewardExploit = iValue;

        pElement->Attribute("RewardFriendly", &iValue);
        pMonster->nRewardFriendly = iValue;

        pElement->Attribute("Daoxing", &iValue);
        pMonster->nDaoxing = iValue;

        pElement->Attribute("RewardDaoxing", &iValue);
        pMonster->nRewardDaoxing = iValue;

        pElement->Attribute("VisualType", &iValue);
        pMonster->visualType = iValue;

        pElement->Attribute("IdleMoveRate", &iValue);
        pMonster->nIdleMoveRate = iValue;

        pElement->Attribute("BornProtectTime", &iValue);
        pMonster->dwBornProtectTime = iValue;

        pElement->Attribute("RestoreSpaceTime", &iValue);
        pMonster->dwRestoreSpaceTime = iValue;

        pElement->Attribute("CashMoney", &iValue);
        pMonster->nCashMoney = iValue;

        pElement->Attribute("RewardStatusID", &iValue);
        pMonster->nRewardStatusID = iValue;

        pElement->Attribute("RewardMulType", &iValue);
        pMonster->nRewardMulType = iValue;

        pElement->Attribute("RewardMulValue", &iValue);
        pMonster->nRewardMulValue = iValue;

		pElement->Attribute("IsFindParth", &iValue);
		pMonster->blIsFindParth = iValue == 0 ? false : true;

		pElement->Attribute("IsDynamicBlock", &iValue);
		pMonster->blIsDynamicBlock = iValue == 0 ? false : true;

        pElement->Attribute("CatchPetID", &iValue);
        pMonster->nCatchPetID = iValue;

        pElement->Attribute("CatchBaseRate", &iValue);
        pMonster->nCatchBaseRate = iValue;

        pElement->Attribute("PetQuality", &iValue);
        pMonster->nPetQuality = iValue;

        pElement->Attribute("Phyle", &iValue);
        pMonster->phyle = iValue;

        pElement->Attribute("FiveElements", &iValue);
        pMonster->element = iValue;

		pElement->Attribute("GroupID", &iValue);
		pMonster->nGroupID = iValue;

		pElement->Attribute("DropType", &iValue);
		pMonster->nDropType = iValue;	

		pMonster->iMonsterContainerIndex = _MonsterInfos.size();

        _Id2IndexMonsters.insert( Id2IndexMonsterContainer::value_type( pMonster->stMonsterId, pMonster->iMonsterContainerIndex) );
        _Name2IndexMonsters.insert( Name2IndexMonsterContainer::value_type( pMonster->GetName(), pMonster->iMonsterContainerIndex ) );

        _MonsterInfos.push_back( pMonster );

        pElement = pElement->NextSiblingElement();
    }

    return true;
}

bool CItemDetail::SaveXMLMonster( const char *szFile)
//保存XML怪物的相关信息
{
    if (szFile == NULL || *szFile == 0)
    {
        return false;
    }

    MeXmlDocument saveMonsterMeXml;
    saveMonsterMeXml.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = saveMonsterMeXml.InsertEndChild(("Project"))->ToElement();

    pRoot->SetAttribute("Type", "Monster");

    SYSTEMTIME xSystemTime;
    ::GetLocalTime(&xSystemTime);
    char szTime[50] = "";
    sprintf_s(szTime, sizeof(szTime) -1 , "%d-%d-%d %d:%d:%d", 
        xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay, xSystemTime.wHour, xSystemTime.wMinute, xSystemTime.wSecond);
    pRoot->SetAttribute("Value", szTime);
    pRoot->SetAttribute("Count", _MonsterInfos.size());

    MeXmlElement* pMonsters = pRoot->InsertEndChild(("Monsters"))->ToElement();
    if(pMonsters == NULL)  
        return false;
    MonsterInfoContainer::iterator iter = _MonsterInfos.begin();//std::vector<SMonster*>   MonsterInfoContainer
    MonsterInfoContainer::iterator end = _MonsterInfos.end();

    for (; iter != end; ++iter)
    {
        ItemDefine::SMonster* pMonsterIter = *iter;

        MeXmlElement* pMonster = pMonsters->InsertEndChild(("Monster"))->ToElement();
        if ( pMonster == NULL )
        { continue; }

        pMonster->SetAttribute("MonsterID", pMonsterIter->stMonsterId);             //Id

        Common::_tstring MonsterPrefix = pMonsterIter->GetNamePrefix();
        pMonster->SetAttribute("MonsterPrefix", MonsterPrefix.toUTF8().c_str());    //怪物名前缀

        Common::_tstring MonsterName = pMonsterIter->GetName();
        pMonster->SetAttribute("MonsterName", MonsterName.toUTF8().c_str());        //怪物名

        pMonster->SetAttribute("ModelID", pMonsterIter->iModelID);                  //模型Id

        Common::_tstring MonsterSound = pMonsterIter->GetCreatureSound();
        pMonster->SetAttribute("MonsterSound", MonsterSound.toUTF8().c_str());          //怪物声音模板

        pMonster->SetAttribute("MonsterType", pMonsterIter->stMonsterType); //怪物类别
        pMonster->SetDoubleAttribute("BodyModify", pMonsterIter->fBodySize);//体型修正
        pMonster->SetDoubleAttribute("BodyLengthSize", pMonsterIter->fBodyLengthSize);  //体型大小
        pMonster->SetAttribute("MonsterLv", pMonsterIter->stLevel);         //等级
        pMonster->SetAttribute("MonsterExp", pMonsterIter->nRewardExp);     //经验值
        pMonster->SetAttribute("MaxHP", pMonsterIter->nHPMax);              //最大HP
        pMonster->SetDoubleAttribute("PhyAtk", pMonsterIter->fPhysicAtt);   //物攻
        pMonster->SetDoubleAttribute("MagicAtk", pMonsterIter->fMagicAtt);  //法攻
        pMonster->SetDoubleAttribute("PhyDef", pMonsterIter->fPhysicDef);   //物防
        pMonster->SetDoubleAttribute("MagicDef", pMonsterIter->fMagicDef);  //法防

        pMonster->SetDoubleAttribute("Critical", pMonsterIter->critical);
        pMonster->SetAttribute("CriticalIntensity", pMonsterIter->criticalIntensity) ;
        pMonster->SetAttribute("Tenacity", pMonsterIter->tenacity) ;

        pMonster->SetAttribute("BackStrike", pMonsterIter->backStrike) ;
        pMonster->SetAttribute("BackStrikeResist", pMonsterIter->backStrikeResist) ;
        pMonster->SetAttribute("BreakStrike", pMonsterIter->breakStrike) ;
        pMonster->SetAttribute("StabStrike", pMonsterIter->stabStrike) ;
        pMonster->SetAttribute("ElementStrike", pMonsterIter->elementStrike) ;
        pMonster->SetAttribute("ToxinStrike", pMonsterIter->toxinStrike) ;
        pMonster->SetAttribute("SpiritStrike", pMonsterIter->spiritStrike) ;
        pMonster->SetAttribute("BreakResist", pMonsterIter->breakResist) ;
        pMonster->SetAttribute("StabResist", pMonsterIter->stabResist) ;
        pMonster->SetAttribute("ElementResist", pMonsterIter->elementResist) ;
        pMonster->SetAttribute("ToxinResist", pMonsterIter->toxinResist) ;
        pMonster->SetAttribute("SpiritResist", pMonsterIter->spiritResist) ;

        pMonster->SetAttribute("MaxMP", pMonsterIter->stMPMax) ;        //最大MP
        pMonster->SetAttribute("RecoverHP", pMonsterIter->stHPRestore); //HP回复
        pMonster->SetAttribute("RecoverMP", pMonsterIter->stMPRestore); //MP回复
        pMonster->SetAttribute("Hit", pMonsterIter->stExact);           //精确值
        pMonster->SetAttribute("Dodge", pMonsterIter->stDodge);         //回避率
        pMonster->SetAttribute("AtkSpeed", pMonsterIter->stAttackRate); //攻击速度
        pMonster->SetAttribute("EyeShot", pMonsterIter->stView);        //视野
        pMonster->SetAttribute("FightShot", pMonsterIter->stFightView); //战斗视野
        pMonster->SetDoubleAttribute("AttackPhysicsMod", pMonsterIter->fAttackPhysicsMod);  //物攻系数
        pMonster->SetDoubleAttribute("AttackMagicMod", pMonsterIter->fAttackMagicMod);      //法攻系数
        pMonster->SetDoubleAttribute("DefendPhysicsMod", pMonsterIter->fDefendPhysicsMod);  //物防系数
        pMonster->SetDoubleAttribute("DefendMagicMod", pMonsterIter->fDefendMagicMod);      //法防系数
        pMonster->SetAttribute("AttackFloatMin", pMonsterIter->nAttackFloatMin);            //
        pMonster->SetAttribute("AttackFloatMax", pMonsterIter->nAttackFloatMax);            //

        pMonster->SetAttribute("ChaseTime", pMonsterIter->dwCatchTime);         //追击时间
        pMonster->SetDoubleAttribute("MoveSpeed", pMonsterIter->fMoveSpeed);    //移动速度

        for (int i=0; i<ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i)                     //技能
        {
            char szTmpBuffer[65] = {0};
            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "UseSkill%d", i+1);
            pMonster->SetAttribute(szTmpBuffer, pMonsterIter->iSkillID[i]);
        }
        for (int i=0; i<ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i)                     //技能等级
        {
            char szTmpBuffer[65] = {0};
            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "Skill%dLv", i+1);
            pMonster->SetAttribute(szTmpBuffer, pMonsterIter->stSkillLevel[i]);
        }
        for (int i=0; i<ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i)//技能概率
        {
            char szTmpBuffer[65] = {0};
            sprintf_s(szTmpBuffer, sizeof(szTmpBuffer) - 1, "ChanceOfSkill%d", i+1);
            pMonster->SetAttribute(szTmpBuffer, pMonsterIter->stSkillRate[i]);
        }

        pMonster->SetAttribute("MinDropMoney", pMonsterIter->stDropMinMoney);//最小掉落金钱
        pMonster->SetAttribute("MaxDropMoney", pMonsterIter->stDropMaxMoney);//最大掉落金钱
        pMonster->SetDoubleAttribute("DropItemRate", pMonsterIter->fItemDropMultipleRate);//物品掉落率
        pMonster->SetAttribute("IfInitiative", pMonsterIter->nIsInitiative);//是否为主动怪

        Common::_tstring monsterSkin = pMonsterIter->GetSkin();
        pMonster->SetAttribute("MonsterSkin", monsterSkin.toUTF8().c_str());//怪物皮肤

        pMonster->SetDoubleAttribute("MonsterAlpha", pMonsterIter->fAlpha);//怪物透明度
        pMonster->SetAttribute("ReviveTime", pMonsterIter->nReliveTime);//复活时间
        pMonster->SetAttribute("IfDisappear", pMonsterIter->bIsDisappear);//是否消失
        pMonster->SetAttribute("DisappearTime", pMonsterIter->dwDisappearTime);//消失时间

        Common::_tstring deathScript = pMonsterIter->GetDeadScript();
        pMonster->SetAttribute("DeathScript",deathScript.toUTF8().c_str());//死亡脚本

        Common::_tstring AIScript = pMonsterIter->GetAILuaScript();
        pMonster->SetAttribute("AIScript", AIScript.toUTF8().c_str());//AI脚本

        Common::_tstring weaponSonudPrefix = pMonsterIter->GetWeaponSound();
        pMonster->SetAttribute("MonsterWeaponSoundPrefix", weaponSonudPrefix.toUTF8().c_str());//武器音效前缀

        Common::_tstring ArmorSoundPrefix = pMonsterIter->GetArmourSound();
        pMonster->SetAttribute("MonsterArmorSoundPrefix", ArmorSoundPrefix.toUTF8().c_str());//防具音效前缀

        pMonster->SetDoubleAttribute("RunStep", pMonsterIter->fRunStep);//奔跑步长
        pMonster->SetDoubleAttribute("WalkStep", pMonsterIter->fMovingStep);//行走步长
        pMonster->SetAttribute("IfHalfLengthMonster", pMonsterIter->nIsHaveTwoHalfBody);//是否上下半身怪
        pMonster->SetAttribute("IfFourFeetMonster", pMonsterIter->nIsHaveFourFoot);//是否四足怪
        pMonster->SetAttribute("MonsterSide", pMonsterIter->nMonsterSide); //阵营
        pMonster->SetAttribute("EnemityRate", pMonsterIter->nEnmityRate);//仇恨比率
        pMonster->SetAttribute("InitialEnemity", pMonsterIter->nEnmity);//视野触发仇恨初值
        pMonster->SetAttribute("ResistUnmovable", pMonsterIter->nResistMove);//移动抵抗
        pMonster->SetAttribute("ResistUnatkable", pMonsterIter->nResistAtt);//攻击抵抗
        pMonster->SetAttribute("ResistUncastable", pMonsterIter->nResistMagic);//施法抵抗
        pMonster->SetAttribute("ResistUnitemusable", pMonsterIter->nResistTools);//道具抵抗
        pMonster->SetAttribute("ExtraSkillExp", pMonsterIter->nSuperfluitySkillExp);//额外的技能经验
        pMonster->SetAttribute("MaxActArea", pMonsterIter->nMaxRange);//最大活动范围
        pMonster->SetAttribute("ChangePassive", pMonsterIter->nChangePassive);//战斗中是否变为被动怪
        pMonster->SetAttribute("PassiveTime", pMonsterIter->nPassiveTime);//被动持续时间
        pMonster->SetAttribute("BaseEnmityRange", pMonsterIter->nBaseEnmityRange);//基础仇恨保持区域
        pMonster->SetDoubleAttribute("IdleMoveSpeed", pMonsterIter->fIdleMoveSpeed);//空闲移动速度
        pMonster->SetAttribute("Citymonster", pMonsterIter->bIsCityMonster);//城市怪
        pMonster->SetAttribute("Citydefmonster", pMonsterIter->bIsCityDefMonster);//城市防守怪

        Common::_tstring MonsterTitle = pMonsterIter->GetTitle();
        pMonster->SetAttribute("MonsterTitle", MonsterTitle.toUTF8().c_str());//怪物称号

        Common::_tstring MonsterFrontFoot = pMonsterIter->GetFrontFootPrintPath();
        pMonster->SetAttribute("FrontFoot", MonsterFrontFoot.toUTF8().c_str());//怪物前脚印

        Common::_tstring MonsterBackFoot = pMonsterIter->GetBackFootPrintPath();
        pMonster->SetAttribute("BackFoot", MonsterBackFoot.toUTF8().c_str());//怪物后脚印

        pMonster->SetAttribute("NeedQuest",pMonsterIter->nRelativeQuest);//关联任务
        pMonster->SetAttribute("MonsterReputation", pMonsterIter->nRewardReputation);//名望
        pMonster->SetAttribute("MonsterExploit", pMonsterIter->nRewardExploit);//功勋
        pMonster->SetAttribute("RewardFriendly", pMonsterIter->nRewardFriendly);//好友度
        pMonster->SetAttribute("Daoxing", pMonsterIter->nDaoxing);//道行
        pMonster->SetAttribute("RewardDaoxing", pMonsterIter->nRewardDaoxing);//奖励道行
        pMonster->SetAttribute("VisualType", pMonsterIter->visualType);//可视类型

        pMonster->SetAttribute("IdleMoveRate", pMonsterIter->nIdleMoveRate);
        pMonster->SetAttribute("BornProtectTime", pMonsterIter->dwBornProtectTime);
        pMonster->SetAttribute("RestoreSpaceTime", pMonsterIter->dwRestoreSpaceTime);

        pMonster->SetAttribute("CashMoney", pMonsterIter->nCashMoney);
        pMonster->SetAttribute("RewardStatusID", pMonsterIter->nRewardStatusID);
        pMonster->SetAttribute("RewardMulType", pMonsterIter->nRewardMulType);
        pMonster->SetAttribute("RewardMulValue", pMonsterIter->nRewardMulValue);

		pMonster->SetAttribute("IsFindParth", pMonsterIter->blIsFindParth ? 1 : 0);
		pMonster->SetAttribute("IsDynamicBlock", pMonsterIter->blIsDynamicBlock ? 1 : 0);

        pMonster->SetAttribute("CatchPetID",    pMonsterIter->nCatchPetID   );
        pMonster->SetAttribute("CatchBaseRate", pMonsterIter->nCatchBaseRate);
        pMonster->SetAttribute("PetQuality",    pMonsterIter->nPetQuality   );
        pMonster->SetAttribute("Phyle", pMonsterIter->phyle); 
        pMonster->SetAttribute("FiveElements", pMonsterIter->element);  
		pMonster->SetAttribute("GroupID", pMonsterIter->nGroupID);  
		pMonster->SetAttribute("DropType", pMonsterIter->nDropType);  

	}
    return saveMonsterMeXml.SaveFile(szFile);
}

#pragma warning( pop )