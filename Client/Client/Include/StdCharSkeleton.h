#ifndef _stdcharskeleton_h
#define _stdcharskeleton_h
#include "Me3d/Me3d.h"
#include "Singleton.h"
#include "MapStrToID.h"
#include "EquipEnum.h"
#define ADD_BONE(a) { m_mapStdCharBoneName[a] = #a; }
class CStdCharSkeleton : public Singleton<CStdCharSkeleton>
{
public:
	typedef void (*funcInitializePartMask)();
	enum enumBoneId
	{
	//	// --------------------------------------
	//	// 头部
		Head,			// 头部

	//	Ponytail1,
	//	Ponytail11,
	//	Ponytail2,
	//	Ponytail21,		// 马尾辫

	//	// --------------------------------------
	//	// 盔甲部
	//	Bip01,			// root
	//	Neck,			// 颈
	//	Spine,			// 胸部
	//	Pelvis,			// 骨盆
	//	L_Clavicle,		
	//	R_Clavicle,		// 锁骨
	//	L_UpperArm,
	//	R_UpperArm,		// 大臂
	//	L_Thigh,
	//	R_Thigh,		// 大腿

	//	Tail,
	//	Tail1,			// 衣摆
	//	
	//	// --------------------------------------
	//	// 手套部
	//	L_ForeArm,
	//	R_ForeArm,		// 前臂
	//	L_Hand,
	//	R_Hand,			// 手

	//	// --------------------------------------
	//	// 鞋部
	//	L_Calf,
	//	R_Calf,			// 小腿
	//	L_Foot,
	//	R_Foot,			// 脚
	//	L_Toe0,
	//	R_Toe0,			// 脚尖

	//	// --------------------------------------
	//	// 道具
		L_HandItem,
		R_HandItem,		// 道具
	//	
		eMaxBone,
	};
	//enum EPartId
	//{
 //       eHairPartMask,		    //头发
 //       eHelmetPartMask,		    //头盔
 //       eFacePartMask	,	    //脸
 //       eArmourPartMask	,	    //甲
 //       eGlovePartMask   ,       //手套
 //       eShoePartMask	,	    //鞋子
 //       eRightHandItemPartMask,  //右手武器
 //       eLeftHandItemPartMask ,  //左手武器
 //       eBadgeMask			,	//徽章
 //       eLeftHandShieldPartMask,	//盾
 //       eShoulderPartMask	,	//护肩
 //       eTrousersPartMask	,	//裤子
 //       //eGemBagMask		,	//宝囊					宝囊替换为披风		modified by ZhuoMeng.Hu		[9/2/2010]		
	//	eCloakMask			,	//披风
 //       eRightRingMask		,	//右手戒指
 //       //eLeftRing		    //左手戒指	
 //       erBangleMask		,	//手镯
 //       eNecklaceMask		,	
 //       eSashMask			,	//腰带
 //       eHonorMask			,	//勋章
 //       eMaxPart			
	//};
	//enum enumMaxVisul 
	//{
	//	eMaxVisualItem = eMaxPart
	//};
	struct Bone : public MeCommonAllocObj<CStdCharSkeleton::Bone>
	{
		int nId;
		int nPartId;
		char szName[256];
	};
	struct Part
	{
		BOOL	bEnable;
		int		nPartId;
		std::vector<Bone*> vectorBone;
		Part()
		{
			nPartId = -1;
			bEnable = FALSE;
		}
	};
public:
	CStdCharSkeleton();
	virtual ~CStdCharSkeleton();
	void Init();
	const char* GetBoneNameById( int nBoneId );
	int GetBoneIdByName( const char* pszBonename );

	const char** GetPartNames();
	const char* GetPartName( int nPartId );
	int GetPartIdByBoneName( const char* pszBoneName );
	int GetPartIdByPartName( const char* pszPartName );

	BOOL CanCreate( char* pszBonenames[], int nBoneCount );
	BOOL LoadCfg();
	int		GetBoneCount();
	Bone*	GetBone( int i );
	Bone*	GetBoneByName( const char* pszBoneName );

	Part*	GetPart( int nPartId );
	Part*	GetPart( const char* pszPartName );

	void SetInitializeFunction( CStdCharSkeleton::funcInitializePartMask pf );

public:
	//static int GetPartMask( EPartId ePart );
	//static void SetPartMask( EPartId ePart, int nValue );
protected:	
	/*static int ms_aPartsMasks[eMaxPart];*/

protected:
	//std::map< DWORD, char* > m_mapStdCharBoneName;
	//Bone	m_bones[eMaxBone];
	
	/*Part	m_parts[eMaxPart];*/
	Part	m_parts[eKeyAll_Max];
	std::vector<Bone*> m_vectorBone;
	CMapStrToIDMgr m_BoneFinder;

	/*CStdCharSkeleton::funcInitializePartMask m_pfInitializePartMask;*/
};
// extern CStdCharSkeleton g_stdCharSkeleton;
extern char* GetPartNames( int nType );
#endif