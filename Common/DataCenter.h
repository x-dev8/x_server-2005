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
    // ��Ϸ�����߼�����
    float   fSpeedMove              ;
    short   sSpeedNormalAttack      ;

    uint16  exactMin                ;       // ��С������
    uint16  exactModulus            ;       // ����ϵ��

    uint16  attackModulus           ;       // ����ϵ��
    uint16  defendModulus           ;       // ����ϵ��

    uint16  backStrikeModulus       ;       // ����ϵ��

    uint16  criticalMin             ;       // ��С������
    uint16  criticalModulus         ;       // ����ϵ��

    uint16  criticalIntensityModulus;       // �����˺�ϵ��

    uint16  damageMinValue          ;       // ��С�˺�ֵ

    uint16  attackMonsterModulus    ;       // ���������˺�ϵ��
    uint16  attackPlayerModulus     ;       // ��������˺�ϵ��

    std::vector<SBaseAttrPotential> vecBaseAttrPotential;   // Ǳ����

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
    AN_LIC_small_bugle      = 0,  // С����
    AN_LIC_microphone       = 1,  // ��˷�
    AN_LIC_loudhailer       = 2,  // ��˷�
    AN_LIC_bywaynews1       = 3,  // С����Ϣ1
    AN_LIC_bywaynews2       = 4,  // С����Ϣ2
    AN_LIC_bywaynews3       = 5,  // С����Ϣ3
    AN_LIC_bywaynews4       = 6,  // С����Ϣ4
    AN_LIC_bywaynews5       = 7,  // С����Ϣ5
    AN_LIC_bywaynews6       = 8,  // С����Ϣ6
    AN_LIC_bywaynews7       = 9,  // С����Ϣ7
    AN_LIC_bywaynews8       = 10, // С����Ϣ8
    AN_LIC_bywaynews9       = 11, // С����Ϣ9
    AN_LIC_bywaynews10      = 12, // С����Ϣ10
    AN_LIC_XinShouID        = 13, // �������
    AN_LIC_XinShouItemID    = 14, // ���ֵ���
    AN_LIC_ChangeNameItemID = 15, // ��������

    AN_LIC_TTJYLK           = 16, // <!-- ������Ȩ��Ӣ�� -->
    AN_LIC_QQBH             = 17, // <!-- ��ʧʱ��50��������5000���ڣ�������5000 -->
    AN_LIC_BHBG             = 18, // <!-- ��ʧʱ��50�� ����5000���ϰ���5000 -->
    AN_LIC_17173TQK         = 19, // <!-- 17173��Ȩ��      -->
    AN_LIC_SCCZLB           = 20, // <!-- �״γ�ֵ���     -->
    AN_LIC_30CZLB           = 21, // <!-- 30Ԫ��ֵ���     -->
    AN_LIC_100CZLB          = 22, // <!-- 100Ԫ��ֵ���    -->
    AN_LIC_300CZLB          = 23, // <!-- 300Ԫ��ֵ���    -->
    AN_LIC_1000CZLB         = 24, // <!-- 1000Ԫ��ֵ���   -->

    AN_LIC_ZZVIP1           = 25, // <!-- ����VIP1 -->
    AN_LIC_ZZVIP2           = 26, // <!-- ����VIP2 -->
    AN_LIC_ZZVIP3           = 27, // <!-- ����VIP3 -->
    AN_LIC_ZZVIP4           = 28, // <!-- ����VIP4 -->
    AN_LIC_ZZVIP5           = 29, // <!-- ����VIP5 -->
    AN_LIC_ZZVIP6           = 30, // <!-- ����VIP6 -->
    
    AN_LIC_TTJYLK_1         = 31, // <!-- ������Ȩ��Ӣ�� -->
    AN_LIC_32               = 32, // <!-- ��ʧʱ��40�� δ����/���� -->
    AN_LIC_33               = 33, // <!-- ��ʧʱ��40������< 50�� ����10Ԫ���� -->
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
    VS_LaoWanJiaFanhui = 0, // ����ҷ���
    VS_MAX,
};

//////////////////////////////////////////////////////////////////////////
#define theDataCenter DataCenter::GetInstance()

class DataCenter
{
public:    
    static DataCenter& GetInstance();

    // ���ֲ���
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
    // ���ֵ�ϵ��
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
