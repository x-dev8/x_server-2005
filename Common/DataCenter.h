/********************************************************************
    Filename:     DataCenter.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_DATACENTER_H__
#define __COMMON_DATACENTER_H__

#pragma once

#include "GlobalDef.h"

#pragma pack( push, 1)

struct SBaseAttrPotential
{
    uint16 beginLevel;
    uint16 endLevel  ;
    uint8  potential ;
};

struct SArmsParamModulusCommon
{
    // 游戏人物逻辑参数
    float   fSpeedMove              ;
    short   sSpeedNormalAttack      ;

    uint16  exactMin                ;       // 最小命中率
    uint16  exactModulus            ;       // 命中系数

    uint16  attackModulus           ;       // 攻击系数
    uint16  defendModulus           ;       // 防御系数

    uint16  backStrikeModulus       ;       // 背击系数

    uint16  criticalMin             ;       // 最小暴击率
    uint16  criticalModulus         ;       // 暴击系数

    uint16  criticalIntensityModulus;       // 暴击伤害系数

    uint16  damageMinValue          ;       // 最小伤害值

    uint16  attackMonsterModulus    ;       // 攻击怪物伤害系数
    uint16  attackPlayerModulus     ;       // 攻击玩家伤害系数

    std::vector<SBaseAttrPotential> vecBaseAttrPotential;   // 潜力点

    float  GetMoveSpeed() { return fSpeedMove; }
    int16  GetNormalAttackSpeed() { return sSpeedNormalAttack; }

    uint16 GetExactMinValue() { return exactMin; }
    uint16 GetExactModulus () { return exactModulus ; }
    uint16 GetAttackModulus() { return attackModulus; }
    uint16 GetDefendModulus() { return defendModulus; }

    uint16 GetBackStrikeModulus() { return backStrikeModulus ; }

    uint16 GetCriticalMinValue () { return criticalMin;   }
    uint16 GetCriticalModulus  () { return criticalModulus; }
    uint16 GetCriticalIntensityModulus() { return criticalIntensityModulus  ;  }

    uint16 GetDamageMinValue(){ return damageMinValue; }

    uint16 GetAttackMonsterModulus() { return attackMonsterModulus; }
    uint16 GetAttackPlayerModulus () { return attackPlayerModulus ; }

    typedef std::vector<SBaseAttrPotential> ::iterator IterPotential;

    int GetPotentialByLevel( uint16 nLevel)
    {
        for (IterPotential iter = vecBaseAttrPotential.begin(); iter != vecBaseAttrPotential.end(); ++iter)
        {
            if ( nLevel >= iter->beginLevel && nLevel <= iter->endLevel)
            { return iter->potential; }
        }

        return 0;
    }
};

struct SBaseAttrToFightAttr
{
    float fStrengthToPhysicsAttack;
    float fIntelligenceToMagicAttack;
    float fStaminaToHPMax;
    float fStaminaToPhysicsDefend;
    float fStaminaToMagicDefend;
    float fAgilityToExact;
    float fAgilityToDodge;
    float fAgilityToCritical;
    float fAgilityToTenacity;
};

struct SArmsParamModulusExtend
{
    short armsType;
    char  armsName[MAX_NAME_STRING + 1];
    short sAttackFloating[ATTACK_FLOAT_COUNT];
    SBaseAttrToFightAttr baseFightAttr;
};

enum EItemSymbol
{
    AN_LIC_small_bugle      = 0,  // 小喇叭
    AN_LIC_microphone       = 1,  // 麦克风
    AN_LIC_loudhailer       = 2,  // 麦克风
    AN_LIC_bywaynews1       = 3,  // 小道消息1
    AN_LIC_bywaynews2       = 4,  // 小道消息2
    AN_LIC_bywaynews3       = 5,  // 小道消息3
    AN_LIC_bywaynews4       = 6,  // 小道消息4
    AN_LIC_bywaynews5       = 7,  // 小道消息5
    AN_LIC_bywaynews6       = 8,  // 小道消息6
    AN_LIC_bywaynews7       = 9,  // 小道消息7
    AN_LIC_bywaynews8       = 10, // 小道消息8
    AN_LIC_bywaynews9       = 11, // 小道消息9
    AN_LIC_bywaynews10      = 12, // 小道消息10
    AN_LIC_XinShouID        = 13, // 新手礼盒
    AN_LIC_XinShouItemID    = 14, // 新手道具
    AN_LIC_ChangeNameItemID = 15, // 改名道具

    AN_LIC_TTJYLK           = 16, // <!-- 武神特权精英礼卡 -->
    AN_LIC_QQBH             = 17, // <!-- 流失时≥50级，付费5000以内，不包含5000 -->
    AN_LIC_BHBG             = 18, // <!-- 流失时≥50级 付费5000以上包含5000 -->
    AN_LIC_17173TQK         = 19, // <!-- 17173特权卡      -->
    AN_LIC_SCCZLB           = 20, // <!-- 首次充值礼包     -->
    AN_LIC_30CZLB           = 21, // <!-- 30元充值礼包     -->
    AN_LIC_100CZLB          = 22, // <!-- 100元充值礼包    -->
    AN_LIC_300CZLB          = 23, // <!-- 300元充值礼包    -->
    AN_LIC_1000CZLB         = 24, // <!-- 1000元充值礼包   -->

    AN_LIC_ZZVIP1           = 25, // <!-- 至尊VIP1 -->
    AN_LIC_ZZVIP2           = 26, // <!-- 至尊VIP2 -->
    AN_LIC_ZZVIP3           = 27, // <!-- 至尊VIP3 -->
    AN_LIC_ZZVIP4           = 28, // <!-- 至尊VIP4 -->
    AN_LIC_ZZVIP5           = 29, // <!-- 至尊VIP5 -->
    AN_LIC_ZZVIP6           = 30, // <!-- 至尊VIP6 -->
    
    AN_LIC_TTJYLK_1         = 31, // <!-- 武神特权精英礼卡 -->
    AN_LIC_32               = 32, // <!-- 流失时≥40级 未付费/付费 -->
    AN_LIC_33               = 33, // <!-- 流失时≥40级并且< 50级 付费10元以上 -->
    AN_MI_MAX,
};

enum ETileSymbol
{
    TS_VIP1       = 1,  // 
    TS_VIP2       = 2,  // 
    TS_VIP3       = 3,  // 
    TS_VIP4       = 4,  // 
    TS_VIP5       = 5,  // 
    TS_VIP6       = 6,  // 
    TS_MAX,
};

enum EVarSymbol
{
    VS_LaoWanJiaFanhui = 0, // 老玩家返回
    VS_MAX,
};

//////////////////////////////////////////////////////////////////////////
#define theDataCenter DataCenter::GetInstance()

class DataCenter
{
public:    
    static DataCenter& GetInstance();

    // 兵种参数
    long LoadArmsParamModulus( const char* szFileName );

    SArmsParamModulusExtend* GetArmsParamModulus( unsigned char armsType );
    SArmsParamModulusCommon& GetArmsParamModulusCommon() { return _armsParamModulusCommon; }

    uint32 LoadItemSymbol( const char* szFileName );
    uint16 GetItemSymbol ( uint16 itemSymbolId    );
    uint16 GetTileSymbol ( uint16 tileSymbolId    );
    int16  GetVarSymbol  ( uint16 varSymbolId     );

protected:    
    DataCenter();
    DataCenter( const DataCenter& ){}
    DataCenter& operator=( const DataCenter& ){}

private:
    // 兵种的系数
    SArmsParamModulusCommon _armsParamModulusCommon;
    SArmsParamModulusExtend _armParamModulusExtends[EArmType_MaxSize];
    
    typedef std::map<uint16, uint16>  SymbolContainer;
    typedef SymbolContainer::iterator ItrSymbolContainer;
    SymbolContainer _itemSymbols;
    SymbolContainer _tileSymbols;

    typedef std::map<uint16, int16>      VarSymbolContainer;
    typedef VarSymbolContainer::iterator ItrVarSymbolContainer;
    VarSymbolContainer _varSymbols;
};

class CChangeItemID
{
public:
	static CChangeItemID& Instance()
	{
		static CChangeItemID changeitemid;
		return changeitemid;
	}

	struct  SProcessId
	{
		unsigned short sourceid;
		unsigned short dstid;
	};

	typedef std::map<unsigned short,SProcessId*> mapChangeItemID;
	mapChangeItemID m_changeidmap;

	bool LoadIDChangeList();
};


//////////////////////////////////////////////////////////////////////////
// inline
inline SArmsParamModulusExtend* DataCenter::GetArmsParamModulus( unsigned char armsType )
{
    if ( armsType>=EArmType_MaxSize )
        return NULL;

    return &(_armParamModulusExtends[armsType]);
}

#pragma pack( pop)

#endif // __COMMON_DATACENTER_H__
