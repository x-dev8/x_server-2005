#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include <windows.h>
#include <assert.h>
#include "Me3d\include.h"
#include "Player.h"
#include "Stdcharskeleton.h"
#include "PlayerAnimCtrl.h"
#include "slkreader.h"
#include "itemdetail.h"
#include "Me3d/MoreAction.h"
#include "effect.h"
#include "globalvars.h"
#include "Me3d/Model/MexRes.h"
#include "GlobalDef.h"
#include "itemdetail.h"
#include "modelproj.h"
#include "cfg.h"
#include "ErrorLog.h"
#include "LogFileObjectNameEx.h"
#include "MultiThreadMexLoading.h"
#include "FilePath.h"
#include "Me3d/Md5Manager.h"
#include "script_manager.h"
#include "Me3d/shader.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Model/BowStringBindingConfig.h"
#include "Avatar.h"
#include "Timer.h"
#include "wsCamera.h"
#include "Common.h"
#include "Mex2LoadReq.h"
#include <MeFoundation/MeLoopThreadMan.h>
#include "PlayerInfoMgr.h"
#include "IntensifyEquipEffect.h"
extern int PlayEffect( const char* pEffectName, CPlayer* pSrcPlayer = NULL, float fScale = 0 , DWORD dwFlyTime = 0, CPlayer* pDestPlayer = NULL, int nSlot = 0 ,bool bCalDist = true );
#define LIGHTTRACKDEADRENDERTIME 618

CPlayerAnimParam* _pCurrPlayerAnimParam = NULL;
CPlayerAnim*      _pCurrPlayerAnim = NULL;

extern CHeroGame* theApp;
extern int				g_nRockTexId;
int		gs_nNunMTLoadModel = 0;
extern BOOL	g_bShowModelBBox;

extern BOOL g_bMultiThreadLoadingMex; //多线程加载mex

D3DMATERIAL9 CPlayerAnim::GlobalMaterial;

/*
挂件的处理
挂件本身的mesh什么都不知道，
只需要把挂件mex的骨骼计算正确，
问题就得到解决，

约定，
挂件本身是一个mex
其特点是，有一个名叫root的唯一根骨骼，
所有的骨骼都是root的子节点，

问题转化为，
root在依附的骨骼上，
进行了怎么样的空间变化？

我需要得到一个矩阵，

假设root在max的原点，
现在需要把root绑定在骨骼的肩部，
比如说肩甲，
很显然，
在骨骼的肩部需要一个辅助物体，
此物体就是用来计算root的变换用的，

假设root在max的空间变换是t0
肩甲辅助物体在max的空间变换是t1
显然，root到肩甲的变换是t0inv*t1

那么，意味着，
挂件绑定到肩甲部位的变换就是t0inv*t1
*/
BOOL AvatarComponentTest( BOOL bLeftHand, DWORD dwFlag, DWORD dwItemEnableFlag )
{
	if( ( dwFlag & CAvatar::eItem_RBack ) && 
		( dwItemEnableFlag & CAvatar::eItem_RBack ) == 0 )
		return FALSE;

	if( ( dwFlag & CAvatar::eItem_RightHand ) && 
		( dwItemEnableFlag & CAvatar::eItem_RightHand ) == 0 )
		return FALSE;

	if( ( dwFlag & CAvatar::eItem_LBack ) && 
		( dwItemEnableFlag & CAvatar::eItem_LBack ) == 0 )
		return FALSE;
	if( ( dwFlag & CAvatar::eItem_LeftHand ) && 
		( dwItemEnableFlag & CAvatar::eItem_LeftHand ) == 0 )
		return FALSE;

	if( ( dwFlag & CAvatar::eItem_Shield ) && 
		( dwItemEnableFlag & CAvatar::eItem_Shield ) == 0 )
		return FALSE;

	if( ( dwFlag & CAvatar::eItem_BackShield ) && 
		( dwItemEnableFlag & CAvatar::eItem_BackShield ) == 0 )
		return FALSE;
	return TRUE;
}

extern int GetVertexStride( DWORD dwFvf );

//void CPlayerAnim::InitializePartMask()
//{
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eHairPartMask, EPT_Hair );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eHelmetPartMask, EPT_Helmet );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eFacePartMask, EPT_Face );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eArmourPartMask, EPT_Armour );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eGlovePartMask, EPT_Glove );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eShoePartMask, EPT_Shoe );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eRightHandItemPartMask, EPT_RHandItem );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eLeftHandItemPartMask, EPT_LHandItem );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eBadgeMask, EPT_Badge );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eLeftHandShieldPartMask, EPT_LeftHandShieldPart );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eShoulderPartMask, EPT_Shoulder );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eTrousersPartMask, EPT_Trousers );
//	////CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eGemBagMask, EPT_GemBag );		// 宝囊替换为披风		modified by ZhuoMeng.Hu		[8/31/2010]
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eCloakMask, EPT_GemBag );			// ……
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eRightRingMask, EPT_Ring );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::erBangleMask, EPT_RBangle );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eNecklaceMask, EPT_Necklace );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eSashMask, EPT_Sash );
//	//CStdCharSkeleton::SetPartMask(CStdCharSkeleton::eHonorMask, EPT_Honor );	
//}
CPlayerAnim::~CPlayerAnim()
{
	guardfunc;
	assert( !m_pAvatar && " avatar is not null" );
	unguard;
}

CPlayerAnim::CPlayerAnim():
m_pPlayer( NULL )
,m_dwAnimType(-1)
,m_dwTargetAnimType(-1)
,m_pAvatar(NULL)
,m_pEffectAnim(NULL)
{
	guardfunc;
	static bool bInitSkeleton = false;
	if( !bInitSkeleton )
	{	
		/*CStdCharSkeleton::Instance()->SetInitializeFunction( InitializePartMask );*/
		CStdCharSkeleton::Instance()->Init();
		bInitSkeleton = true;
	}
	CAvatar* pAvatar = MeNew CAvatar;
	CAvatar::CreateParam param;
	/*param.nComponentCount = CStdCharSkeleton::eMaxPart;*/
	param.nComponentCount = eKeyAll_Max;
	param.ppszComponentNames = (char**)CStdCharSkeleton::Instance()->GetPartNames();
	pAvatar->Create( &param );
	SetAvatar( pAvatar );
	ClearAttackInfo();

	m_pEffectAnim = MeNew MexAnimCtrl;

	m_bChangeAllEquipComplete = TRUE;

	NeedLimitLocalBBox( TRUE );

#define eDefHair 2800
#define eDefFace	 2950
#define eDefArmour 12000
#define eDefGlovePart 12001
#define eDefHelmet 12002
#define eDefShoesPart 12003
#define eDefShoulder 12004
#define eDefSash /*12005*/0 // modified, [10/20/2010 zhangjiayi],没有这个模型，避免重复换装。如果有了再改可以
	//#define eDefTrousersPart 12006
	//static eMaxPart

	for (int j = 0; j < 2;j++)
	{
		for( int i=0; i< eKeyAll_Max; i++ )
		{
			DefPart[j][i] = InvalidLogicNumber;
		}
	}

#define eDefHair1 2801
#define eDefFace1	 2951
#define eDefArmour1 13010
#define eDefGlovePart1 13011
#define eDefHelmet1 13012
#define eDefShoesPart1 13013
#define eDefShoulder1 13014
#define eDefSash1 0

	DefPart[0][eKeyAll_Hair] = eDefHair;
	DefPart[0][eKeyAll_Helmet] = eDefHelmet;
	DefPart[0][eKeyAll_Face] = eDefFace;
	DefPart[0][eKeyAll_Armour] = eDefArmour;
	DefPart[0][eKeyAll_Glove] = eDefGlovePart;
	DefPart[0][eKeyAll_Shoe] = eDefShoesPart;
	DefPart[0][eKeyAll_Sash] = eDefSash;

	DefPart[1][eKeyAll_Hair] = eDefHair1;
	DefPart[1][eKeyAll_Helmet] = eDefHelmet1;
	DefPart[1][eKeyAll_Face] = eDefFace1;
	DefPart[1][eKeyAll_Armour] = eDefArmour1;
	DefPart[1][eKeyAll_Glove] = eDefGlovePart1;
	DefPart[1][eKeyAll_Shoe] = eDefShoesPart1;
	DefPart[1][eKeyAll_Sash] = eDefSash1;

	m_bIsUpperAnimWholeBody = FALSE;
	m_bIsLootAnim = FALSE;
	m_bIsIntonateAnim = FALSE;
	m_bIsHoldingFlagOnRightHand = FALSE;
	m_bNpcNeedReplayAnim = FALSE;

	unguard;
}

BOOL CPlayerAnim::LoadFromFile( const char* pszFilename )
{
	guardfunc;
	return TRUE;
	unguard;
}

int GetRoleModel( int iSex,int iArmourID,int iWeaponID );

//void CPlayerAnim::SetSpecialEquipEffect( int iPart,CPlayer_SEquipment* pEquip )
//{
//
//	guardfunc;
//	if( ( iPart !=  CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eArmourPartMask ) )
//		&& iPart != CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ) )
//	{
//		return;
//	}
//	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
//	if( !pItem )
//		return;
//
//	//1。找出最大的特殊数值
//	//2。使用一个特效文件
//	//数值0-9,无表现 10-14:0号文件  15-20:1号文件
//	// 物理攻击 火 fire
//	// 物理防御 土 earth
//	// 魔法攻击 水晶兰 crystalblue
//	// 魔法防御 水晶白 crystalwhite
//	char *szEffectFormat[] =
//	{
//		"%s\\data\\MtlAnim\\EquipEffect\\PhysicAttLv%d.mtlani"
//		,"%s\\data\\MtlAnim\\EquipEffect\\PhysicDefLv%d.mtlani"
//		,"%s\\data\\MtlAnim\\EquipEffect\\MagicAttLv%d.mtlani"
//		,"%s\\data\\MtlAnim\\EquipEffect\\MagicDefLv%d.mtlani"
//	};
//
//	int iWhichAttr=-1,iMaxValue = 0;
//	const static int SPECIAL_COUNT = 4;
//	int nSpecial[SPECIAL_COUNT];
//
//	for( int n=0; n<SPECIAL_COUNT; n++ )
//	{
//		if( nSpecial[n] > iMaxValue )
//		{
//			iWhichAttr = n;
//			iMaxValue = nSpecial[n];
//		}
//	}
//
//
//	if( -1 == iWhichAttr )
//		return;
//	if( iMaxValue > 20 )
//		iMaxValue = 20;
//	if( iMaxValue < 10 )
//		return;
//	iMaxValue -= 10;
//	iMaxValue /= 5;
//	if( iMaxValue > 1 )
//		iMaxValue = 1;
//	iMaxValue++;
//
//	char szFile[ MAX_PATH ];
//	MeSprintf_s( szFile,sizeof(szFile)/sizeof(char) - 1,szEffectFormat[ iWhichAttr ],GetRootPath(), iMaxValue );
//	
//	unguard;
//}

BOOL CPlayerAnim::MyChangeModel( int nModelId, BOOL bChangeByMultiThread /* = TRUE */, const char* pszSkin /* = NULL  */ )
{
	////////////////////////MeNew project
	guardfunc;
	// 多线程处理
	if( g_bMultiThreadLoadingMex )
	{		
		MeLoopThreadMan::Instance()->RegisterPointer( this );	
	}

	if( g_bMultiThreadLoadingMex && bChangeByMultiThread )
	{
		return TryChangeModel( nModelId, pszSkin );
	}
	else 
	{
		BOOL bChangeSuccess = MexAnimCtrl::ChangeModel( nModelId,FALSE,pszSkin );
		// 		if( bChangeSuccess && pszSkin && strcmp( pszSkin, "" ) != 0 )
		// 		{
		// 			ChangeAvatarSetting( pszSkin );
		// 		}

		return bChangeSuccess;
	}
	unguard;
}

BOOL CPlayerAnim::TryChangePartModel( CPlayerAnimParam& param, const char* pcFilename )
{
	guardfunc;
	int nType = param.nPart;
	//
	int nModelId = param.nModelId;
	const char* pszSkin =param.szSkin;

	// 	MexResMgr::Record* pRecord = GetMexResMgr()->GetRecord( nModelId );
	// 	if( !pRecord )
	// 	{
	// 		assert( false );
	// 		return FALSE;
	// 	}

	//if( pRecord->res.pMex == NULL )
	{
		MeLoopThreadReq* reqb = MeNew PlayerEquipReq;
		PlayerEquipReq* req = dynamic_cast< PlayerEquipReq* >( reqb );
		if( !req )
			return FALSE;

		SetInThread( true );
		req->m_pAnim = this;
		req->m_pPlayer = (CPlayer*)GetPlayer();
		// 		if( req->m_pPlayer )
		// 			req->m_pPlayer->AddRef();
		/*req->m_nObjectType = Mex2LoadReq::ePlayerEquip;*/
		req->m_nModelId = nModelId;
		req->m_nType = nType;
		req->m_nSpecularTexID = param.nSpecularTextureID;
		req->m_nLowestIntensity = param.LowestIntensity;

		strcpy( req->m_szSkin, DEFAULT_AVATARSETTING_NAME );
		if( pcFilename )
			strcpy( req->m_szFileName, pcFilename );

		if( pszSkin )
			strcpy( req->m_szSkin, pszSkin );

		MeLoopThreadMan::Instance()->PostMexLoadingReq( req );
	}
	return TRUE;

	// 	return ChangePartModel( param );
	unguard;
}

BOOL CPlayerAnim::ChangePartModel( CPlayerAnimParam& Param,BOOL bNoModel,BOOL bOnePart /* = FALSE  */)
{
	guardfunc;

	int nPartId = Param.nPart;
	int nModelId  = Param.nModelId;
	const char* szSkin = Param.szSkin;
	INT nSpecular = Param.nSpecularTextureID;
	if( nPartId == eKeyAll_Max - 1 )
	{
		m_bChangeAllEquipComplete = TRUE;
	}

	if( bNoModel )
	{
		return FALSE;
	}

	short stStar = 0;
	int nLocalModelId = -1;
	if (Param.pEquips != NULL)
	{
		if (Param.nPart == eKeyAll_RHandItem || Param.nPart == eKeyAll_LHandItem)
		{
			
			if (bOnePart)
			stStar = Param.pEquips->item.equipdata.ucLevel;				
			else
			stStar = Param.pEquips[nPartId].item.equipdata.ucLevel;
		
			// 如果是右手武器, 把Star覆盖为玩家身上的最低星级
			//stStar = Param.LowestIntensity;
		}

		if (bOnePart)
			nLocalModelId = Param.pEquips->iModelID;
		else
			nLocalModelId = Param.pEquips[nPartId].iModelID;

	}

	BOOL ret = ChangePartModelById( nPartId, nModelId, nLocalModelId, szSkin, nSpecular, stStar );
	if (!ret && m_pPlayer)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "");
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "MexAnimCtrl::ChangePartModel: PlayerName[%s], Profession[%d]", m_pPlayer->GetName(), m_pPlayer->GetProfession());
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "MexAnimCtrl::ChangePartModel: Part[%d], ModelId[%d]", nPartId, nModelId);
	}

	return ret;
	unguard;
}

BOOL CPlayerAnim::TryChangeModel( int nModelId, const char* pszSkin /* = NULL  */)
{
	guardfunc;
	// 	MexResMgr::Record* pRecord = GetMexResMgr()->GetRecord( nModelId );
	// 	if( !pRecord )
	// 	{
	// 		assert( false );
	// 		return FALSE;
	// 	}
	// 
	// 	if( pRecord->res.pMex == NULL )
	{
		MeLoopThreadReq* reqb = MeNew MonsterModelReq;
		MonsterModelReq* req = dynamic_cast< MonsterModelReq* >( reqb );
		if( !req )
			return FALSE;
		SetInThread( true );
		req->m_pAnim = this;
		req->m_pPlayer = (CPlayer*)GetPlayer();
		// 		if( req->m_pPlayer )
		// 			req->m_pPlayer->AddRef();
		req->m_nObjectType = LoopLoadType::eMonsterModel;
		req->m_nModelId = nModelId;

		// 		if( pRecord->szFilename )
		// 			strcpy( req.m_szFileName, pRecord->szFilename );

		if( pszSkin )
			strcpy( req->m_szSkin, pszSkin );

		MeLoopThreadMan::Instance()->PostMexLoadingReq( req );
		return FALSE;
	}

	// 	BOOL bChangeSuccess = MexAnimCtrl::ChangeModel( nModelId );
	// 	if( bChangeSuccess && pszSkin && strcmp( pszSkin, "" ) != 0 )
	// 	{
	// 		ChangeAvatarSetting( pszSkin );
	// 	}
	// 	return bChangeSuccess;
	unguard;
}

// int CPlayerAnim::GetMexResId( int nModelId, int nProfession, int nSex, int nType, int nColor /* = -1  */)
// {
// 	guardfunc;
// 	std::string szFile;
// 	if( nType == CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandItemPartMask ) )
// 	{
// 		if( nColor != -1)
// 			szFile = GetModelProjMgr()->GetFileAddress( nModelId, 
// 			CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ), 
// 			nSex, 
// 			nProfession,
// 			nColor );
// 		else
// 			szFile = GetModelProjMgr()->GetFileAddress( 
// 			nModelId, 
// 			CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eRightHandItemPartMask ), 
// 			nSex, 
// 			nProfession );
// 	}
// 	else
// 	{
// 		if( nColor != -1)
// 			szFile = GetModelProjMgr()->GetFileAddress( 
// 			nModelId,
// 			nType, 
// 			nSex, 
// 			nProfession, 
// 			nColor );
// 		else
// 			szFile = GetModelProjMgr()->GetFileAddress( 
// 			nModelId, 
// 			nType, 
// 			nSex, 
// 			nProfession );
// 	}
// 
// 	if( szFile.size() < 1 )
// 	{
// 		return -1;
// 	}
// 
// 	int nMexResId = GetMexResMgr()->GetIdByName( szFile.c_str() );
// 	if( nMexResId == -1 )
// 	{
// 		nMexResId = GetMexResMgr()->AddExternalFile( szFile.c_str() );
// 	}
// 	return nMexResId;
// 	unguard;
// }

BOOL CPlayerAnim::ChangeEquip(  CPlayerAnimParam &param /* = -1  */)
{
	guardfunc;
	// 多线程处理
	int nModelId  = param.nModelId;
	int nProfession = param.nProfession;
	int nSex = param.nSex;
	int nType = param.nPart; 
	const char* szSkin = param.szSkin;
	int nColor = param.nColor;

	if( g_bMultiThreadLoadingMex )
	{
		MeLoopThreadMan::Instance()->RegisterPointer( this );		
	}

	std::string szFile;
	if(nType == eKeyAll_LHandItem)
	{
		if( nColor != -1)
			szFile = 
			GetModelProjMgr()->GetFileAddress( nModelId, 
			eKeyAll_RHandItem, 
			nSex, 
			nProfession,
			nColor );
		else
			szFile = 
			GetModelProjMgr()->GetFileAddress( 
			nModelId, 
			eKeyAll_RHandItem, 
			nSex, 
			nProfession );
	}
	else
	{
		if( nColor != -1)
			szFile = 
			GetModelProjMgr()->GetFileAddress( 
			nModelId,
			nType, 
			nSex, 
			nProfession, 
			nColor );
		else
			szFile = 
			GetModelProjMgr()->GetFileAddress( 
			nModelId, 
			nType, 
			nSex, 
			nProfession );
	}

	if( szFile.size() < 1 )
	{	
		if( m_pPlayer )
		{
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "");
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "ChangeSkeletonAndEquipAll: PlayerName[%s], Profession[%d]", m_pPlayer->GetName(), m_pPlayer->GetProfession());
			LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "ChangeSkeletonAndEquipAll: Filename[%s], Part[%d], ModelId[%d]", szFile.c_str(), nType, nModelId);
		}
		return FALSE;
	}

	int iModelId = GetMexResMgr()->GetIdByName( szFile.c_str() );
	if( iModelId == -1 && !g_bMultiThreadLoadingMex )
	{
		iModelId = GetMexResMgr()->AddExternalFile( szFile.c_str() );
	}
	// added, [10/18/2010 zhangjiayi]
	// 与现在相同则不加载
	CAvatar::Component* pPart = m_pAvatar->GetComponent( nType );
	if( pPart )
	{
		if( pPart->nModelID == iModelId 
			&& ( pPart->stSex == nSex || pPart->stSex == -1 )  
			&& iModelId != -1 )
			return TRUE;
	}
	param.nModelId = iModelId;
	BOOL ret = FALSE;
	if( nModelId != InvalidLogicNumber )
	{
		if( g_bMultiThreadLoadingMex )
			ret = TryChangePartModel( param, szFile.c_str() );
		else 
			ret = ChangePartModel( param ,FALSE,TRUE);
	}
	else    // 如果模型ID为ErrorUnsignedShortID则直接设置加载结束
		ret = ChangePartModel( param, TRUE );

	// 不同强化级别的装备添加不同的特效 [6/5/2008 whu]
	_pCurrPlayerAnimParam = &param;
	_pCurrPlayerAnim = this;

	// 不同强化级别的装备添加不同的特效 [6/5/2008 whu]
	CAvatar::Component* pComponent = NULL;
	if ( GetAvatar() && ( pComponent = GetAvatar()->GetComponent(nType) ) )
	{
		//pComponent->material.setShader( "MexShader" );
		//pComponent->material.setTechnique( "Specular" );
	}

	if (!ret && m_pPlayer)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "");
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "ChangeSkeletonAndEquipAll: PlayerName[%s], Profession[%d]", m_pPlayer->GetName(), m_pPlayer->GetProfession());
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_INFO, "ChangeSkeletonAndEquipAll: Filename[%s]", szFile.c_str());
	}
	return ret;
	unguard;
}

BOOL CPlayerAnim::ChangeEquip(const std::string& filename, int nPart)
{	
	int iModelId = GetMexResMgr()->GetIdByName( filename.c_str() );
	if( iModelId == -1 && !g_bMultiThreadLoadingMex )
		iModelId = GetMexResMgr()->AddExternalFile( filename.c_str() );

	if (iModelId == -1)
		return FALSE;

	CPlayerAnimParam param;
	param.nModelId = iModelId;
	param.nPart = nPart;
	BOOL ret = FALSE;
	if( g_bMultiThreadLoadingMex )
		ret = TryChangePartModel( param, filename.c_str() );
	else 
		ret = ChangePartModel( param );

	return ret;
}

void CPlayerAnim::setEquipEffect( int part, const char* texFilename )
{
	guardfunc

		CAvatar::Component* pComponent = NULL;
	if ( GetAvatar() && ( pComponent = GetAvatar()->GetComponent( part ) ) )
	{
		// 纹理动画
		std::string technique( "Diffuse" );

		if (part == eKeyAll_RHandItem ||part == eKeyAll_LHandItem)
		{
			technique = "Specular";
		}

		graphics::Shader* shader = pComponent->material.setShader( "MexShader" );

		if ( texFilename != NULL && strlen( texFilename ) > 0 && shader )
		{
			int nTextureID = GetEngine()->GetTextureManager()->RegisterTexture( 
				texFilename, TRUE ,TRUE);
			try
			{
				ITexture* pTexture = NULL;
				if ( nTextureID != -1 && 
					( pTexture = GetEngine()->GetTextureManager()->GetTexture( nTextureID ) ) )
				{
					LPDIRECT3DTEXTURE9 pTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
					pComponent->material.setParameter( "animTex", pTex );
					technique = "SpecularAndAnim";
				}
			}
			catch( const std::exception& e )
			{
				assert( 0 && "设置pComponent->material出错！" );
				OutputDebugString( e.what() );
			}
		}

		pComponent->material.setTechnique( technique );
	}

	unguard
}

// void CPlayerAnim::setEquipModelEffect(const char* mexFilename )
// {
//     guardfunc
// 
//     if ( !_enableChildren )
//         return;
// 
//     // 不同强化级别的装备添加不同的特效
//     // 模型特效
//     detachChild( "EquipEffect" );
//     if ( mexFilename != NULL )
//     {
//         CFilePath path;
//         path.MakeDirectoryForFile( mexFilename );
//         std::string filename = path.GetFileName();
//         if ( filename != "" )
//         { 
//             EquipEffectMexs::iterator it = _equipEffectMexs.find( filename );
//             if ( it != _equipEffectMexs.end() )
//             {
//                 attachChild( "EquipEffect", it->second );
//             }
//             else
//             {
//                 MexAnimCtrl* pChild = MeNew MexAnimCtrl();
//                 pChild->SetScale( 1.0f );
//                 _equipEffectMexs.insert( EquipEffectMexs::value_type(filename, pChild) );
// 
//                 int nModelID = GetMexResMgr()->AddExternalFile( mexFilename );
//                 if( nModelID != -1 && pChild->ChangeModel( nModelID ) )
//                 {
//                     attachChild( "EquipEffect", pChild );
//                 }
//             }
//         }           
//     }
// 
//     unguard
// }

void CPlayerAnim::UpdateRightHardItem( bool fight_state )
{
	guardfunc;
	if (fight_state)
	{
		m_pAvatar->SetItemFlag( CAvatar::eItem_RightHand );		
	}
	else
	{
		//右手
		m_pAvatar->SetItemFlag( CAvatar::eItem_RBack|CAvatar::eItem_Ground );		
	}

	unguard;
}

void CPlayerAnim::UpdateHardItem( bool fight_state, void* pEquips0 )
{
	guardfunc;
	if ( !m_pAvatar || !pEquips0 )
	{
		return;
	}
	int iModelID;
	CPlayer_SEquipment* pEquips	 = (CPlayer_SEquipment*)pEquips0;
	CPlayer_SEquipment *pEquip	=	NULL;
	if (fight_state)
	{
		//右手
		pEquip = &pEquips[eKeyAll_RHandItem];
		iModelID = pEquip->iModelID;
		if( iModelID != InvalidLogicNumber)
		{
			m_pAvatar->SetItemFlag(CAvatar::eItem_RightHand);
		}

		//左手
		pEquip = &pEquips[eKeyAll_LHandItem];
		iModelID = pEquip->iModelID;
		if( iModelID == InvalidLogicNumber)
		{
			m_pAvatar->SetItemFlag(CAvatar::eItem_RightHand);			
		}
		else
		{
			m_pAvatar->SetItemFlag( CAvatar::eItem_RightHand|CAvatar::eItem_LeftHand );			
		}
	}
	// commented out, jiayi, [2009.4.16],非战斗状态不将武器放背上
	else
	{
		//右手
		pEquip = &pEquips[eKeyAll_RHandItem];
		iModelID = pEquip->iModelID;
		if( iModelID != InvalidLogicNumber)
		{
			m_pAvatar->SetItemFlag( CAvatar::eItem_RBack|CAvatar::eItem_Ground );
		}

		//左手
		pEquip = &pEquips[eKeyAll_LHandItem];
		iModelID = pEquip->iModelID;

		if( iModelID == InvalidLogicNumber)
		{
			m_pAvatar->SetItemFlag(CAvatar::eItem_RBack);			
		}
		else
		{
			m_pAvatar->SetItemFlag( CAvatar::eItem_RBack|CAvatar::eItem_LBack );
		}
	}
	unguard;
}

BOOL bSpecularTexLoaded = FALSE;
VOID InitSpecularTex()
{
	if( bSpecularTexLoaded )
		return;

	bSpecularTexLoaded = TRUE;

	for( int i =0; i< 10; i++ )
	{
		char szBuffer[MAX_PATH] = {0};
		MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1 ,"%s/data/texture/SpecularTex/Weapon_SpecularTex_%d.tga", GetRootPath(), i );
		INT nTex = GetEngine()->GetTextureManager()->RegisterTexture( 
			szBuffer,
			NULL,
			NULL
			);
		GSpecularTexGroup.push_back( nTex );
	}

	for( int i =0; i< 10; i++ )
	{
		char szBuffer[MAX_PATH] = {0};
		MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s/data/texture/SpecularTex/Shield_SpecularTex_%d.tga", GetRootPath(), i );
		INT nTex = GetEngine()->GetTextureManager()->RegisterTexture( 
			szBuffer,
			NULL,
			NULL
			);
		GShieldSpecularTexGroup.push_back( nTex );
	}

	for( int i =0; i< 10; i++ )
	{
		char szBuffer[MAX_PATH] = {0};
		MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s/data/texture/SpecularTex/Equip_SpecularTex_%d.tga", GetRootPath(), i );
		INT nTex = GetEngine()->GetTextureManager()->RegisterTexture( 
			szBuffer,
			NULL,
			NULL
			);
		GEquipSpecularTexGroup.push_back( nTex );
	}


}
const INT MAX_IntensifyCnt = 10;
VOID DestorySpecualrTex()
{
	return;
	if( GSpecularTexGroup.size() == 0 )
		return;

	for( int i =0; i< MAX_IntensifyCnt; i++ )
	{
		if( GSpecularTexGroup[i]!=-1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture(GSpecularTexGroup[i]);
		}
	}
	for( int i =0; i< MAX_IntensifyCnt; i++ )
	{
		if( GSpecularTexGroup[i]!=-1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture(GShieldSpecularTexGroup[i]);
		}
	}
	for( int i =0; i< MAX_IntensifyCnt; i++ )
	{
		if( GSpecularTexGroup[i]!=-1 )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture(GEquipSpecularTexGroup[i]);
		}
	}
}

//add by yanli  2010-9-27
INT GetSpecularTexID( INT nType, CPlayer_SEquipment* pEquip )
{
	guardfunc;

	if( !bSpecularTexLoaded )
		InitSpecularTex();

	ItemDefine :: SItemCanEquip* pItem 
		= (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
	if( pItem == NULL )
	{
		return -1;
	}
	/*if( !pItem->IsSpecular() )
	{
	return -1;
	}*/

	if(nType == eKeyAll_Hair || nType == eKeyAll_Face)
	{
		return -1;
	}

	pEquip->item.equipdata.gemHoleCount = 7;
	INT nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
	if( nIntensifyTime <= 0 )
		return -1;

	if( nIntensifyTime > MAX_IntensifyCnt )
		return -1;

	INT nIdx = nIntensifyTime - 1;
	if(nType == eKeyAll_RHandItem)
		return GSpecularTexGroup[nIdx];
	else if( nType == eKeyAll_LHandItem)
		return GSpecularTexGroup[nIdx];
	else	
		return GEquipSpecularTexGroup[nIdx];		
	return -1;
	unguard;
}

const char * GetSkin(int part, const char *skin, CItemHero::SItemHero* pHero)
{
	if (!pHero || (part == eKeyAll_Hair || part == eKeyAll_Face || part == eKeyAll_LHandItem || part == eKeyAll_RHandItem))
	{
		return skin;
	}
	else
	{
		return pHero->hero_fuse.c_str();
	}
}

static const char* NOEFFECT = "NULL";

void CPlayerAnim::ChangeSkeletonAndEquipAll(void* _pEquips, int iSex, int nCountry, int nColor, bool showHelmet, bool showAecorativeClothing,int nDefModelIndex, unsigned short hero_id,bool showHero,bool bSeeCheck)
{
	bool validateMD5 = Md5Manager::Instance().IsMD5Validate();
	Md5Manager::Instance().EnableMD5Validate( false );

	//是否变身
	CItemHero::SItemHero* pHero = NULL;
	if (showHero)
	{
		pHero = theItemHero.FindHeroByHeroID(hero_id);
	}

	// 换装不能多线程
	CPlayer_SEquipment* pEquips = (CPlayer_SEquipment*)_pEquips;

	// 全身已经装备上的最低强化等级, 如果有部位没有装备, 则最低为0
	int lowestIntensify = -1;
	std::vector<int> equip_item_levels;
	for(int i = 0 ; i < EEquipPartType_MaxEquitPart; ++i)
	{
		if (i == EEquipPartType_Badge || i == EEquipPartType_LeaderCard || i == EEquipPartType_Amulet
			|| i == EEquipPartType_AecorativeGoods || i == EEquipPartType_AecorativeClothing || i == EEquipPartType_Trousers || EEquipPartType_Weapon == i)//lyh++ 全身套强化效果不包括武器
			continue;

		int j = CEquipPartMap::Instance()->GetLogicPart(i);
		if (pEquips[j].item.itembaseinfo.ustItemID == InvalidLogicNumber)
		{
			lowestIntensify = 0;
			break;
		}
		equip_item_levels.push_back(pEquips[j].item.equipdata.ucLevel);
	}

	if (lowestIntensify == -1)
	{
		std::sort(equip_item_levels.begin(), equip_item_levels.end(), std::less<int>());
		lowestIntensify = equip_item_levels[0];
	}
	equip_item_levels.clear();

	// 是否拿旗子
	CPlayer_SEquipment *pRightHandEquip = &pEquips[eKeyAll_RHandItem];
	BOOL bHoldFlag = FALSE;
	if( pRightHandEquip && IsHoldingFlagOnRightHand(pRightHandEquip) )
	{
		bHoldFlag = TRUE;
	}

	CPlayer_SEquipment *pEquip = NULL;

	/*
	* 2012.7.4 wangshuai
	* 老的EArmType_Mage对应了新的 刀职业
	* 老的EArmType_Hunter对应了新的 舞职业, 根据策划要求"双持", 复制右手武器到左手	 
	*/
	/*if (nCountry == EArmType_Mage && !bHoldFlag)
	{
	pEquips[eKeyAll_LHandItem] = pEquips[eKeyAll_RHandItem];
	pEquips[eKeyAll_RHandItem].iModelID = InvalidLogicNumber;
	//pEquips[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = InvalidLogicNumber;
	pEquip = &pEquips[eKeyAll_LHandItem];
	}
	else */if (nCountry == EArmType_Hunter  && !bHoldFlag)
	{
		pEquips[eKeyAll_LHandItem] = pEquips[eKeyAll_RHandItem];
		pEquip = &pEquips[eKeyAll_LHandItem];
	}
	else
		pEquip = &pEquips[eKeyAll_RHandItem];

	if( pEquip->iModelID != InvalidLogicNumber )
	{
		ItemDefine::SItemWeapon* pWeapon = (ItemDefine::SItemWeapon*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
		if( pWeapon )
		{
			// 根据武器的类型，设置武器的射程，特效相关参数
			if( m_pPlayer )
			{
				m_pPlayer->SetWeaponAttackRange( pWeapon->fAtkRange );
				m_pPlayer->SetShotEffectID( pWeapon->iShotEffectID );
			}
		}
	}
	else
	{
		// 徒手攻击的射程是0
		if( m_pPlayer )
			m_pPlayer->SetWeaponAttackRange( 0 );
	}

	guard( test1 );
	// 根据职业和性别更换骨架
	{
		int modelIDByClassAndGender = GetActionModelId(nCountry, iSex);
		if (modelIDByClassAndGender == -1)
		{
			assert(false);
			return;
		}
		if (GetModelID() != modelIDByClassAndGender)
		{
			MyChangeModel(modelIDByClassAndGender, FALSE, NULL);
		}
	}
	unguard;

	guard(testRelease0);
	for(int i = 0; i < eKeyAll_Max; ++i)
	{
		pEquip = &pEquips[i];
		if( i == eKeyAll_Hair || 
			i == eKeyAll_Face//	|| 
			/*i == eKeyAll_Glove || 
			i == eKeyAll_Shoe || 
			i == eKeyAll_Armour	|| 
			i == eKeyAll_AecorativeClothing*/)
		{
			continue;
		}

		if( m_pAvatar )
			m_pAvatar->ReleaseComponent( i );
		/*if( pEquip->iModelID == InvalidLogicNumber )
		{
		if( m_pAvatar )
		m_pAvatar->ReleaseComponent( i );
		}*/
	}
	unguard;

	CPlayer_SEquipment helmet = pEquips[eKeyAll_Helmet];
	if (!showHelmet)
	{
		helmet.item.itembaseinfo.ustItemID = InvalidLogicNumber;
		helmet.iModelID = InvalidLogicNumber;
		helmet.iModelID2 = InvalidLogicNumber;
	}

	std::string szHelmet = DEFAULT_AVATARSETTING_NAME;
	BOOL bShowHair = TRUE;
	BOOL bDrawHelmet = TRUE;
	//Need Profession
	ItemDefine::SItemArmour* pItem = NULL;
	//(ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID(pEquip->item.itembaseinfo.ustItemID);
	int iModelID = InvalidLogicNumber;
	{
		ItemDefine::SItemArmour* pHelmet = NULL;
		INT iHelmetModelID = -1;//;
		guard( test4 );
		//头盔	或者 头饰 
		pEquip = &helmet;

		pHelmet = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID(pEquip->item.itembaseinfo.ustItemID);
		if( pHelmet )
		{
			szHelmet = GetSkin(eKeyAll_Helmet,pHelmet->GetReplaceSkin(),pHero);
			//if 是头饰，就显示头发
			if (pHelmet->isHeadWear)
			{
				bShowHair = TRUE;
				bDrawHelmet = TRUE;
			}
			else
			{
				bShowHair = FALSE;
			}
		}
		else
		{
			bDrawHelmet = FALSE;
		}
		unguard;

		guard( test5 );
		iHelmetModelID = pEquip->iModelID; 		
		if( iHelmetModelID == InvalidLogicNumber || bShowHair )
		{
			//显示头发
			pEquip = &pEquips[eKeyAll_Hair];
			{
				iModelID = pEquip->iModelID;
				//---------------------------------------------
				CPlayerAnimParam param;
				param.szSkin = DEFAULT_AVATARSETTING_NAME;
				param.nPart = eKeyAll_Hair;
				param.nProfession = nCountry;
				param.nSex = iSex;	
				/*int hairColor = 1;*/
				/*
				* Author:	2012-8-31 wangshuai
				* Desc: 	这里以前硬编码为1, 即头发mex必须是, hairxxx_1.mex
				*			现在改为-1, 头发mex不必加下划线和索引了
				*/
				param.nColor = /*hairColor*/-1;
				if( iModelID == InvalidLogicNumber)
				{
					param.nModelId = eDefHair;
				}
				else
				{
					param.nModelId = iModelID;				
				}
				// 				if ( pEquip->item.equipdata.bIsCanIntensify )
				// 					param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
				// 				else
				// 					param.nIntensifyTime = -1;
				param.pEquips = pEquip;
				BOOL ret = ChangeEquip(param);

				bDrawHelmet = !ret; // 显示头发不显示头盔
			}

			pEquip = &helmet;
			iModelID = pEquip->iModelID2; 
			if( pEquip->item.itembaseinfo.ustItemID != BackEquip[eKeyAll_Helmet].item.itembaseinfo.ustItemID )
			{
				if( iModelID != InvalidLogicNumber)
				{
					int nAddAlpha = GetSpecularTexID(eKeyAll_Helmet, pEquip);
					INT nPro = nCountry;
					pItem = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
					if(pItem && pItem->IsCommon())
					{
						nPro = EArmType_MaxSize;
					}
					//---------------------------------------------
					CPlayerAnimParam param;
					param.nModelId = iModelID;
					param.nProfession = nPro;
					param.nSex = iSex;
					param.nPart = eKeyAll_Helmet;
					param.szSkin = szHelmet.c_str();
					param.nSpecularTextureID = nAddAlpha;
					// 					if ( pEquip->item.equipdata.bIsCanIntensify )
					// 						param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
					// 					else
					// 						param.nIntensifyTime = -1;	
					param.pEquips = pEquip;
					ChangeEquip( param );
					//---------------------------------------------
				}
			}

		}
		else 
		{
			if( (pEquip->item.itembaseinfo.ustItemID != 	BackEquip[eKeyAll_Helmet].item.itembaseinfo.ustItemID) || 
				(pEquip->item.equipdata.gemHoleCount != BackEquip[eKeyAll_Helmet].item.equipdata.gemHoleCount))
			{
				int nAddAlpha = GetSpecularTexID(eKeyAll_Helmet, pEquip);
				INT nPro = nCountry;
				pItem = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
				if(pItem && pItem->IsCommon())
				{
					nPro = EArmType_MaxSize;					
				}

				CPlayerAnimParam param;
				param.nModelId = iHelmetModelID;
				param.nProfession = nPro;
				param.nSex = iSex;
				param.nPart = eKeyAll_Helmet;
				param.szSkin = szHelmet.c_str();
				param.nSpecularTextureID = nAddAlpha;
				// 				if ( pEquip->item.equipdata.bIsCanIntensify )
				// 					param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
				// 				else
				// 					param.nIntensifyTime = -1;
				param.pEquips = pEquip;
				ChangeEquip( param );				
			}
		}
		unguard;
	}

	BOOL bCape = FALSE;
	guard( test_ArmourPart );
	pEquip = &pEquips[eKeyAll_Armour];
	iModelID = pEquip->iModelID;
	pItem = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
	if ( pItem )
	{
		if( pItem->IsCape() )
		{
			bCape = TRUE;
		}
	}
	unguard;

	guard( test6 );

	int AecorativeClothingModelID = InvalidLogicNumber;
	int ArmourModelID = InvalidLogicNumber;
	int GloveModelID = InvalidLogicNumber;
	int ShoeModelID = InvalidLogicNumber;

	if (showAecorativeClothing && pEquips[eKeyAll_AecorativeClothing].iModelID != InvalidLogicNumber)
	{
		std::swap(pEquips[eKeyAll_Armour].iModelID, ArmourModelID);
		std::swap(pEquips[eKeyAll_Glove].iModelID, GloveModelID);
		std::swap(pEquips[eKeyAll_Shoe].iModelID, ShoeModelID);
	}
	else
	{
		std::swap(pEquips[eKeyAll_AecorativeClothing].iModelID, AecorativeClothingModelID);
	}

	//BOOL bIsHaveAecorativeClothing = false;
	//if (pEquips[eKeyAll_AecorativeClothing].iModelID != InvalidLogicNumber&&pEquips[eKeyAll_AecorativeClothing].iModelID != InvalidLogicNumber)
	//{
	//	bIsHaveAecorativeClothing = true;
	//}

	//if (showAecorativeClothing && bIsHaveAecorativeClothing)
	//{
	//	pEquips[eKeyAll_Armour].iModelID = InvalidLogicNumber;
	//	pEquips[eKeyAll_Glove].iModelID = InvalidLogicNumber;
	//	pEquips[eKeyAll_Shoe].iModelID = InvalidLogicNumber;
	//}
	//else
	//{
	//	std::swap(pEquips[eKeyAll_Armour].iModelID, pEquips[eKeyAll_AecorativeClothing].iModelID);
	//	std::swap(pEquips[eKeyAll_Glove].iModelID, pEquips[eKeyAll_AecorativeClothing].iModelID);
	//	std::swap(pEquips[eKeyAll_Shoe].iModelID, pEquips[eKeyAll_AecorativeClothing].iModelID);
	//  pEquips[eKeyAll_AecorativeClothing].iModelID = InvalidLogicNumber;
	//}

	for(int i = 0; i < eKeyAll_Max; ++i)
	{
		std::string szTexGroup = DEFAULT_AVATARSETTING_NAME;
		INT nAddAlpha = -1;
		if( i == eKeyAll_WeaponMinor || 
			i == eKeyAll_Ring1	|| 
			i == eKeyAll_Ring2 || 
			i == eKeyAll_Bangle1 || 
			i == eKeyAll_Bangle2 || 
			i == eKeyAll_LeaderCard	|| 
			i == eKeyAll_Amulet || 
			//			i == eKeyAll_Helmet || 
			i == eKeyAll_LHandItem ||
			i == eKeyAll_RHandItem ||
			i == eKeyAll_Badge ||
			i == eKeyAll_Hair /*|| 
							  i == eKeyAll_Armour || 
							  i == eKeyAll_AecorativeClothing*/
							  )
		{
			continue;
		}

		/*if (!showAecorativeClothing && i == eKeyAll_AecorativeClothing)
		{
		continue;
		}*/
		// added, jiayi, [2009/9/4],加腰带
		if(i == eKeyAll_Sash)
		{
			//穿袍子的时候不显示腰带
			if( bCape )
			{						
				if(m_pAvatar)
				{
					m_pAvatar->ReleaseComponent(eKeyAll_Sash);
				}
				continue;
			}
		}

		if (i == eKeyAll_Helmet && !bDrawHelmet)
			continue;
		pEquip = &pEquips[i];
		{
			iModelID = pEquip->iModelID;

			ItemDefine::SItemCanEquip* pItem = NULL;

			if (i != eKeyAll_Face)
			{
				pItem = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
			}
			else
			{
				pEquip->item.itembaseinfo.ustItemID = iModelID;
			}

			nAddAlpha = GetSpecularTexID(i, pEquip);
			//if( pEquip->item.itembaseinfo.ustItemID == InvalidLogicNumber || pEquip->iModelID == InvalidLogicNumber )
			if ((showAecorativeClothing&&pEquips[eKeyAll_AecorativeClothing].iModelID == InvalidLogicNumber&&(i == eKeyAll_Armour||i == eKeyAll_Shoe||i == eKeyAll_Glove))
				||(!showAecorativeClothing&&(pEquip->item.itembaseinfo.ustItemID == InvalidLogicNumber || pEquip->iModelID == InvalidLogicNumber)))		
			{//渲染裸模
				if(GameState.UseDefPart || i == eKeyAll_Face)
				{
					//---------------------------------------------
					CPlayerAnimParam param;
					int nPro = nCountry;
					if(pItem && pItem->IsCommon())
					{
						nPro = EArmType_MaxSize;					
					}
					if(nDefModelIndex < 0 || nDefModelIndex >= 2)
						nDefModelIndex = 0;

					int nModelId = 0;
					int iSelect = 0;
					CreateRoleSetting createRoleSetting;
					int iMaleNum = gCfg.m_MaleRoleSetting[0].GetSpaceSize();
					if( iMaleNum > EArmType_MaxSize )
						iMaleNum = EArmType_MaxSize;
					if (iSex == Sex_Male)
					{

						// 男
						for(int j=0; j<iMaleNum; ++j)
						{
							if( nPro == gCfg.m_MaleRoleSetting[nDefModelIndex].m_vCreateSetting[j].nProfession )
							{
								iSelect = j;
								break;
							}
						}

						createRoleSetting = gCfg.m_MaleRoleSetting[nDefModelIndex].m_vCreateSetting[iSelect];
					}
					else 
					{
						// 女
						for(int j=0; j<iMaleNum; ++j)
						{
							if( nPro == gCfg.m_MaleRoleSetting[nDefModelIndex].m_vCreateSetting[j].nProfession )
							{
								iSelect = j;
								break;
							}
						}

						createRoleSetting = gCfg.m_MaleRoleSetting[nDefModelIndex].m_vCreateSetting[iSelect];
					}					
					switch (i)
					{
					case eKeyAll_Hair:
						nModelId = createRoleSetting.nHeadModelId;
						break;					
					case eKeyAll_Face:
						nModelId = createRoleSetting.nFaceModelId;
						break;
					case eKeyAll_Armour:
						nModelId = createRoleSetting.nArmourModelId;
						break;
					case eKeyAll_Glove:
						nModelId = createRoleSetting.nGloveModelId;
						break;
					case eKeyAll_Shoe:
						nModelId = createRoleSetting.nShoeModelId;
						break;
					case eKeyAll_Sash:
						nModelId = createRoleSetting.nSashModelId;
						break;
					}

					param.nModelId = nModelId;
					param.nProfession = nPro;
					param.nSex = iSex;
					param.nPart = i;
					param.szSkin = GetSkin(i, szTexGroup.c_str(), pHero);
					param.nSpecularTextureID = nAddAlpha;
					// 					if ( pEquip->item.equipdata.bIsCanIntensify )
					param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
					// 					else
					// 						param.nIntensifyTime = -1;
					param.pEquips = pEquip;
					ChangeEquip( param );
				}
			}
			else
			{
				// 男女模型 ID 可以一样     modified by ZhuoMeng.Hu		[10/20/2010]
				CAvatar::Component* pPart = 0;
				if( m_pAvatar )
					pPart = m_pAvatar->GetComponent( i );
				if( pEquip->item.itembaseinfo.ustItemID != BackEquip[i].item.itembaseinfo.ustItemID || 
					i == eKeyAll_Shoe || i == eKeyAll_Glove || ( pPart && ( pPart->stSex != iSex ) && ( iSex != -1 ) ) ||
					pEquip->item.equipdata.ucLevel != BackEquip[i].item.equipdata.ucLevel	|| 
					( pEquip->item.equipdata.gemHoleCount != BackEquip[i].item.equipdata.gemHoleCount ) )
				{
					INT nPro = nCountry;
					if( pItem )
					{
						szTexGroup = GetSkin(i, pItem->GetReplaceSkin(), pHero);
						if(pItem->IsCommon())
						{
							nPro = EArmType_MaxSize;					
						}
					}

					CPlayerAnimParam param;
					param.nModelId = iModelID;
					param.nProfession = nPro;
					param.nSex = iSex;
					param.nPart = i;
					param.szSkin = szTexGroup.c_str();
					param.nSpecularTextureID = nAddAlpha;
					// 					if ( pEquip->item.equipdata.bIsCanIntensify )
					param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
					// 					else
					// 						param.nIntensifyTime = -1;
					param.pEquips = pEquip;
					ChangeEquip( param );
				}
			}
		}
	}
	unguard;

	if (showAecorativeClothing && pEquips[eKeyAll_AecorativeClothing].iModelID != InvalidLogicNumber)
	{
		std::swap(pEquips[eKeyAll_Armour].iModelID, ArmourModelID);
		std::swap(pEquips[eKeyAll_Glove].iModelID, GloveModelID);
		std::swap(pEquips[eKeyAll_Shoe].iModelID, ShoeModelID);
	}
	else
	{
		std::swap(pEquips[eKeyAll_AecorativeClothing].iModelID, AecorativeClothingModelID);
	}

	guard( test7 );
	{
		INT nAddAlpha = -1;
		pEquip = &pEquips[eKeyAll_LHandItem];
		iModelID = pEquip->iModelID;
		if (iModelID != InvalidLogicNumber)
		{
			int nPro = nCountry;
			ItemDefine::SItemCanEquip* pItem = 
				(ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
			if( pItem )
			{
				//szTexGroup = pItem->GetReplaceSkin();
			}
			nPro = EArmType_MaxSize;
			nAddAlpha = GetSpecularTexID(eKeyAll_LHandItem, pEquip);

			CPlayerAnimParam param;
			param.nModelId = iModelID;
			param.nProfession = nPro;
			param.nSex = iSex;
			param.nPart = eKeyAll_LHandItem;
			param.szSkin = DEFAULT_AVATARSETTING_NAME;
			param.nSpecularTextureID = nAddAlpha;
			// 			if ( pEquip->item.equipdata.bIsCanIntensify )
			param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
			// 			else
			// 				param.nIntensifyTime = -1;
			param.pEquips = pEquip;
			param.LowestIntensity = lowestIntensify;
			ChangeEquip( param );
		}
	}
	unguard;

	guard( test7 );
	{
		INT nAddAlpha = -1;
		pEquip = &pEquips[eKeyAll_RHandItem];
		iModelID = pEquip->iModelID;
		if (iModelID != InvalidLogicNumber)
		{
			int nPro = nCountry;
			ItemDefine::SItemCanEquip* pItem = 
				(ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
			if( pItem )
			{
				//szTexGroup = pItem->GetReplaceSkin();
			}
			nPro = EArmType_MaxSize;
			nAddAlpha = GetSpecularTexID(eKeyAll_RHandItem, pEquip);

			CPlayerAnimParam param;
			param.nModelId = iModelID;
			param.nProfession = nPro;
			param.nSex = iSex;
			param.nPart = eKeyAll_RHandItem;
			param.szSkin = DEFAULT_AVATARSETTING_NAME;
			param.nSpecularTextureID = nAddAlpha;
			//if ( pEquip->item.equipdata.bIsCanIntensify )
			param.nIntensifyTime = pEquip->item.equipdata.gemHoleCount;
			//else
			//	param.nIntensifyTime = -1;
			param.pEquips = pEquip;
			param.LowestIntensity = lowestIntensify;
			ChangeEquip( param);
		}
	}
	unguard;

	//if (showAecorativeClothing && pEquips[eKeyAll_AecorativeClothing].iModelID != InvalidLogicNumber)
	//{
	//	//显示时装
	//	INT nAddAlpha = -1;
	//	pEquip = &pEquips[eKeyAll_AecorativeClothing];
	//	iModelID = pEquip->iModelID;
	//	std::string szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//	int nPro = nCountry;
	//	ItemDefine::SItemCanEquip* pItem = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
	//	szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//	if( pItem )
	//	{
	//		szTexGroup = pItem->GetReplaceSkin();
	//	}
	//	nPro = EArmType_MaxSize;
	//	nAddAlpha = GetSpecularTexID(eKeyAll_AecorativeClothing, pEquip);
	//	//---------------------------------------------
	//	CPlayerAnimParam param;
	//	param.nModelId = iModelID;
	//	param.nProfession = nPro;
	//	param.nSex = iSex;
	//	param.nPart = eKeyAll_AecorativeClothing;
	//	param.szSkin = szTexGroup.c_str();
	//	param.nSpecularTextureID = nAddAlpha;
	//	param.pEquips = pEquip;
	//	ChangeEquip( param );
	//}
	//else //显示盔甲
	//{
	//	INT nAddAlpha = -1;
	//	pEquip = &pEquips[eKeyAll_Armour];
	//	iModelID = pEquip->iModelID;
	//	std::string szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//	if (iModelID == InvalidLogicNumber)
	//	{
	//		iModelID = DefPart[eKeyAll_Armour];
	//	}

	//	int nPro = nCountry;
	//	ItemDefine::SItemCanEquip* pItem = 
	//		(ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
	//	szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//	if( pItem )
	//	{
	//		szTexGroup = pItem->GetReplaceSkin();
	//	}
	//	nAddAlpha = GetSpecularTexID(eKeyAll_Armour, pEquip);
	//	//---------------------------------------------
	//	CPlayerAnimParam param;
	//	param.nModelId = iModelID;
	//	param.nProfession = nPro;
	//	param.nSex = iSex;
	//	param.nPart = eKeyAll_Armour;
	//	param.szSkin = szTexGroup.c_str();
	//	param.nSpecularTextureID = nAddAlpha;
	//	param.pEquips = pEquip;
	//	ChangeEquip( param );
	//	//---------------------------------------------
	//}

	//guard( test7 );
	//{
	//	if (!showAecorativeClothing)
	//	{
	//		
	//	}
	//}
	//unguard;

	//guard( test8 );
	//if (showAecorativeClothing)
	//{
	//	INT nAddAlpha = -1;
	//	pEquip = &pEquips[eKeyAll_AecorativeClothing];
	//	iModelID = pEquip->iModelID;
	//	std::string szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//	if (iModelID != InvalidLogicNumber)
	//	{
	//		int nPro = nCountry;
	//		ItemDefine::SItemCanEquip* pItem = 
	//			(ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->item.itembaseinfo.ustItemID );
	//		szTexGroup = DEFAULT_AVATARSETTING_NAME;
	//		if( pItem )
	//		{
	//			szTexGroup = pItem->GetReplaceSkin();
	//		}
	//		nPro = EArmType_MaxSize;
	//		nAddAlpha = GetSpecularTexID(eKeyAll_AecorativeClothing, pEquip);
	//		//---------------------------------------------
	//		CPlayerAnimParam param;
	//		param.nModelId = iModelID;
	//		param.nProfession = nPro;
	//		param.nSex = iSex;
	//		param.nPart = eKeyAll_AecorativeClothing;
	//		param.szSkin = szTexGroup.c_str();
	//		param.nSpecularTextureID = nAddAlpha;
	//		param.pEquips = pEquip;
	//		ChangeEquip( param );
	//	}
	//}
	//unguard;

	guard(test_copy);
	memcpy(&BackEquip, pEquips, sizeof(CPlayer_SEquipment) * eKeyAll_Max);
	if (!showHelmet)
		BackEquip[eKeyAll_Helmet] = helmet;
	unguard;

	if( bCape )
	{
		BackEquip[eKeyAll_Sash].item.itembaseinfo.ustItemID = -1;
	}

	if( !bDrawHelmet )
	{
		BackEquip[eKeyAll_Helmet].item.itembaseinfo.ustItemID = -1;
		if(m_pAvatar)
			m_pAvatar->ReleaseComponent(eKeyAll_Helmet);
	}

	if( !bShowHair )
	{
		if(m_pAvatar)
			m_pAvatar->ReleaseComponent(eKeyAll_Hair);
		BackEquip[eKeyAll_Hair].item.itembaseinfo.ustItemID = -1;
	}

	// add, jiayi, [2009.4.17]
	weaponModelId = GetWeaponActionModelId(nCountry, iSex, bHoldFlag);
	ChangeWeaponAnim(weaponModelId);
	m_bNeedCheckBindingBowString = CBowStringBindingMgr::Instance()->IsExist(weaponModelId);

	Md5Manager::Instance().EnableMD5Validate( validateMD5 );

	//if (nCountry == EArmType_Mage/*EArmType_Hunter*/ && !bHoldFlag)
	{
		// 老版的乐师左手持琴，右边弹琴
		//pEquips[eKeyAll_RHandItem] = pEquips[eKeyAll_LHandItem];
	}
	//else if (nCountry == EArmType_Assassin && !bHoldFlag)
	//{
	//	pEquips[eKeyAll_LHandItem] = pEquips[eKeyAll_RHandItem];
	//	pEquips[eKeyAll_LHandItem].iModelID = InvalidLogicNumber;
	//	//pEquips[eKeyAll_LHandItem].item.itembaseinfo.ustItemID = InvalidLogicNumber;
	//}

	//// 装备强化特效
	if(bSeeCheck) //查看装备不加载特效。
		return;
	try
	{
		
		//char szScriptFilename[MAX_PATH] = {0};
		//sprintf_s(szScriptFilename, MAX_PATH - 1,"%s/Data/Script/Intensify.lua", GetRootPath());
		//LuaPlus::LuaStateOwner luaStateOwner;
		//ScriptManager::instance().executeFile(szScriptFilename, luaStateOwner);

		//LuaFunction<const char *> GetEquipIntensifyEffectModelFunc(luaStateOwner, "GetEquipIntensifyEffectModel");
		////mEquipEffectInfo.nIntensifyModelID = GetEquipIntensifyEffectModelFunc(lowestIntensify);//lyh --
		m_pEffectAnim->ChangeModel(/*mEquipEffectInfo.nIntensifyModelID*/-1, FALSE); //lyh改为-1
		//const char * szTemp = GetEquipIntensifyEffectModelFunc(lowestIntensify);
		std::string path =  theIntensifyEffect.GetEquipIntensifyModelPath(lowestIntensify);
		const char * szTemp =path.c_str();

		if (m_pPlayer)
		{
			if (!m_pPlayer->IsMorph()&&!m_pPlayer->IsHide())
			{
				int _CurIntensifyEffectId = -1;				
				if (szTemp != NULL && strlen(szTemp) > 0 && strcmp(szTemp , "NULL") != 0 )
				{
					_CurIntensifyEffectId = PlayEffect( szTemp,  (CPlayer*)GetPlayer(), PlayerInfoMgr::Instance()->GetScaleForPlayer((CPlayer*)GetPlayer()) ,0,0,0, false);
					if( (m_pPlayer->GetEffectID() != -1 ) && m_pPlayer->GetEffectID() != _CurIntensifyEffectId) //特效有变
					{
						IEffect *pEffect = GetEffectMgr()->GetEffect( m_pPlayer->GetEffectID() ); //销毁之前的特效
						if (pEffect)
						{
							pEffect->SetDead();
							
						}
					}
					m_pPlayer->SetEffectID(_CurIntensifyEffectId,szTemp);
				}
				else
				{
					IEffect *pEffect = GetEffectMgr()->GetEffect( m_pPlayer->GetEffectID() );
					if (pEffect)
					{
						pEffect->SetDead();
					}
					m_pPlayer->SetEffectID(-1,NOEFFECT);
				}
			}
			else
			{
				m_pPlayer->SetEffectID(-1,szTemp);
			}
		}
	}
	catch (const LuaPlus::LuaException &e)
	{
		//LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, e.GetErrorMessage());
	}
}

void CPlayerAnim::ClearAttackInfo( void )
{
	guardfunc;
	m_pAttackInfo = 0;
	unguard;
}

bool CPlayerAnim::HasAttackInfo( void )
{
	guardfunc;
	if( 0 == m_pAttackInfo )
		return false;
	return true;
	unguard;
}

void CPlayerAnim::OnHitPoint( AnimTimeLine::SKey* pKey, DWORD dwFlag )
{
	guardfunc;
	//因为需要增加法术命中的hitpoint 所有，有些hitpoint的效果转移到了CPlayer中去

	if (NULL == m_pPlayer )
		return;

	SAttackInfo* pAttackInfo = m_pAttackInfo;
	if( !pAttackInfo )
		return;

	ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pAttackInfo->iSkill, pAttackInfo->iSkillLevel);
	if (NULL == pSkill)
		return;

	BOOL bLastHitPoint = TRUE;
	//miss 后没有攻击目标，不需要执行。。
	int nHitPointType = GlobalControl::eNormal;
	bool  bNeedProc = false;
	switch (pSkill->stSkillType)
	{
	case ItemDefine::skilltype_action:
		{
			//nMagicType = 0;
			// 如果是长弓，弩或者火枪
			int iSkillEffectID = m_pPlayer->GetShotEffectID();
			if( iSkillEffectID !=  -1 )
			{
				nHitPointType = GlobalControl::eMagicStartShoot;
			}
			else
				nHitPointType = GlobalControl::eNormal;
			bNeedProc = true;
		}
		break;
	case ItemDefine::skilltype_magic_hit:
		nHitPointType = GlobalControl::eMagicStartShoot;
		bNeedProc = true;
		break;
	case ItemDefine::skilltype_magic_npc:
	default:
		nHitPointType = GlobalControl::eNormal;
		bNeedProc = false;
		//魔法NPC的技能的AttackInfo中应该没有什么结算数据，
		//只是显示一下动作而已
		break;
	}
	return;

	unguard;
}
void CPlayerAnim::EndSelfEffect()
{
	guardfunc;
	unguard;
}
void CPlayerAnim::CreateSelfEffect( int nEffectId )
{
	guardfunc;

	unguard;
}

BOOL CPlayerAnim::Update( DWORD dwTime, MeMatrix* pMatrix, BOOL* bUpperbodyPlayOver/*= NULL*/ )
{
	guardfunc;
	BOOL bPreUpperBodyPlayOver = m_bUpperBodyPlayOver;
	BOOL bIsUpperBodyPlayOver = FALSE;
	BOOL bLastUpperAnimHideWeapon = IsUpperAnimHideWeapon();
	BOOL bLastLowerAnimHideWeapon = IsLowerAnimHideWeapon();
	BOOL bAnimChange = MexAnimCtrl::Update( dwTime, pMatrix, FALSE );

	if( m_pPlayer && m_pPlayer->IsNpc() && m_bNpcNeedReplayAnim )
		PlayDefaultAnimAfterChangeModel();

	if( !bPreUpperBodyPlayOver && m_bUpperBodyPlayOver )
		bIsUpperBodyPlayOver = TRUE;
	// 返回上半身动作是否播完
	if( bUpperbodyPlayOver )
	{
		*bUpperbodyPlayOver = bIsUpperBodyPlayOver;
	}

	if( bAnimChange || bIsUpperBodyPlayOver )
	{
		if( bAnimChange && m_dwAnimType == MoreActionClient::yongbao )
		{
			if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
				m_pPlayer->SetShowWeapon(TRUE);
		}
		else if( bLastUpperAnimHideWeapon || bLastLowerAnimHideWeapon )
		{
			if(( bAnimChange && !IsUpperAnimHideWeapon() )
				|| (bIsUpperBodyPlayOver && !IsLowerAnimHideWeapon() ))
			{
				if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
				{
					if( m_dwAnimType == MoreActionClient::stand )
						m_pPlayer->SetShowWeapon(TRUE, TRUE);
					else
						m_pPlayer->SetShowWeapon(TRUE);
				}
			}
		}

		// 更新AnimType
		if( bAnimChange )
		{
			m_dwAnimType = m_dwTargetAnimType;

			// 旗子动作
			TryPlayFlagAnim(m_dwAnimType);
		}
		return TRUE;
	}
	else
	{
		// 旗子动作
		TryPlayFlagAnim(m_dwAnimType);
	}

	return FALSE;
	unguard;
}

BOOL CPlayerAnim::IsAvatarLoaded()
{
	guardfunc;
	int nChunkCount = 0;
	if( m_pAvatar )
	{
		for( int nComponent = 0; nComponent < m_pAvatar->GetComponentCount(); nComponent++ )
		{
			CAvatar::Component* pComponent = m_pAvatar->GetComponent( nComponent );

			if( !pComponent )
				continue;

			if( pComponent->vectorChunk.size() > 0 )
			{
				nChunkCount++;
			}
		}
	}

	if( nChunkCount > 4 )
		return TRUE;
	else
		return FALSE;

	if( m_dwAnimPlayMode == MexAnimCtrl::eHideFrame )
		return FALSE;

	if( !m_bChangeAllEquipComplete )
		return FALSE;


	return TRUE;
	unguard;
}

BOOL CPlayerAnim::Render( float fTransparent /* = 1.0f  */, LayerDataContainer* pMeshContainer /*= NULL*/, int* pRetVertexCount/*=NULL*/, int* pRetFaceCount/*=NULL*/,
						 BOOL bRenderShadow/*=FALSE*/,
						 BOOL bRenderParticleEmitters/*=TRUE*/, bool bOverUI/* = false*/, BOOL bRenderDecal/*= TRUE*/ )
{
	guardfunc;
	BOOL bRet = FALSE;
	if( m_dwAnimPlayMode == MexAnimCtrl::eHideFrame )
		return bRet;

	if( !m_bChangeAllEquipComplete )
		return bRet;

	// 设置全局材质颜色，防止Post Process过亮，引擎结构太乱，现在只能以最快的方法实现，啊啊啊啊啊 [6/26/2008 whu]
	D3DMATERIAL9 mtrl;
	m_dwRenderFlag |= eOpModulate1X;

	IRenderer* pRenderer = GetEngine()->GetRenderer();
	if( !pRenderer )
	{
		return bRet;
	}
	if( !m_pMex )
		return bRet;

	pRenderer->GetDefaultMaterial( (BYTE*)(&mtrl) );
	pRenderer->SetDefaultMaterial( (BYTE*)(&CPlayerAnim::GlobalMaterial) );
	pRenderer->SetGlobalTransparent( fTransparent );
	pRenderer->SetGlobalDiffuse( 1, 1, 1 );
	pRenderer->SetGlobalUOffset( 0, 0.0f );
	pRenderer->SetGlobalVOffset( 0, 0.0f );
	pRenderer->SetGlobalUOffset( 1, 0.0f );
	pRenderer->SetGlobalVOffset( 1, 0.0f );

	if( m_pAvatar )
	{
		// 		if( fTransparent != 1.f )
		// 			m_bRenderRibbon = RenderAvatar( m_pAvatar, pRenderer, fTransparent, pRetVertexCount, pRetFaceCount, getwsCamera()->IsPlayerMustUseAlphaTest() || bRenderShadow, bRenderShadow, bRenderAll );
		// 		else
		m_bRenderRibbon = RenderAvatar( m_pAvatar, pRenderer, fTransparent, pRetVertexCount, pRetFaceCount, getwsCamera()->IsPlayerMustUseAlphaTest() || bRenderShadow, bRenderShadow, bRenderDecal );
		//bNeedRenderRibbon = !bRet;
		bRet = m_bRenderRibbon;
	}

	bRet |= MexAnimCtrl::Render( fTransparent, NULL, pRetVertexCount, pRetFaceCount, NULL,  getwsCamera()->IsPlayerMustUseAlphaTest() || bRenderShadow , 
		bRenderShadow, bRenderParticleEmitters, bOverUI, bRenderDecal );

	GetEngine()->GetRenderer()->SetDefaultMaterial( (BYTE*)(&mtrl) );
	return bRet;
	unguard;
}

void CPlayerAnim::RenderShadow()
{
	guardfunc;
	// 不显示
	if( m_dwAnimPlayMode == MexAnimCtrl::eHideFrame )
		return;

	if( m_pAvatar )
	{
		IRenderer* pRenderer = GetEngine()->GetRenderer();
		if( !pRenderer )
		{
			return;
		}
		RenderAvatarShadow( m_pAvatar, pRenderer );
	}

	MexAnimCtrl::RenderShadow();
	return;

	unguard;
}

BOOL CPlayerAnim::CanReEnter( DWORD dwOldAction, DWORD dwNewAction )
{
	guardfunc;
	//理论上所有的动画都是不可以从入
	return FALSE;
	unguard;
}

DWORD CPlayerAnim::ConvertAnimType( DWORD dwOldType )
{
	guardfunc;
	DWORD ani = dwOldType;
	switch( dwOldType )
	{
	case MoreActionClient::Idle:
		ani = MoreActionClient::Idle;
		break;
	case MoreActionClient::Walk:
		ani = MoreActionClient::Walk;
		break;
	case MoreActionClient::Run:
		ani = MoreActionClient::Run;
		break;
	case MoreActionClient::Attack1:
		ani = MoreActionClient::Attack1;
		break;
	case MoreActionClient::Attack2:
		ani = MoreActionClient::Attack2;
		break;
	case MoreActionClient::Dead:
		ani = MoreActionClient::Dead;
		break;
	case MoreActionClient::Tired:
		ani = MoreActionClient::Tired;
		break;
	case MoreActionClient::Hurt:
		ani = MoreActionClient::Hurt;
		break;
	case MoreActionClient::Miss1:
		ani = MoreActionClient::Miss;
		break;
	}
	return ani;
	unguard;
}
// 函数说明
// 用指定的播放模式播放第一段动画，
// 这段动画每dwOneLoopTime循环一次，
// 算法会自动缩放每一帧的间隔，
// 共循环dwLoopTimes次，
// 如果播放时间超过dwTimeOut或者循环次数计数满，
// 那么切换到第二个动画
// 当dwOneLoopTime为0，就使用当前动画正常播放需要的时间
void CPlayerAnim::PlayAnim2(	DWORD dwAnimType, 
							DWORD dwAnimPlayMode,
							DWORD dwOneLoopTime,
							DWORD dwLoopTimes, 
							DWORD dwTimeOut,
							DWORD dwTargetAnimType, 
							DWORD dwTargetAnimPlayMode )
{
	guardfunc;
	PlayAnim3(	//dwType, 
		dwAnimType,
		dwAnimPlayMode,
		dwOneLoopTime,
		dwLoopTimes, 
		dwTimeOut,
		dwTargetAnimType, 
		dwTargetAnimPlayMode );

	return;
	unguard;
}

int CPlayerAnim::GetActionModelId( int nProfession, int nSex, int /*nWeaponType*/ )
{
	guardfunc;
	if( nSex != 0 && nSex != 1 )
		return -1;

	char szPath[MAX_PATH] = {0};
	char szName[MAX_PATH] = {0};
	if( !GetModelProjMgr()->GetProfessionName(nProfession) )
		return -1;
	guard(test1);
	MeSprintf_s( szPath,sizeof(szPath)/sizeof(char) - 1, "Data\\Character\\%s\\%s.mex", ItemDefine::g_szSexType[nSex], ItemDefine::g_szSexType[nSex] );

	unguard;

	int iModelId = GetMexResMgr()->GetIdByName( szPath );
	//  	if( iModelId == -1 )
	//  	{
	//  		iModelId = GetMexResMgr()->AddExternalFile( szPath );
	//  	}

	return iModelId;
	unguard;
}

int CPlayerAnim::GetModelIDByClassAndGender(int nClass, int nGender)
{
	if (nGender != 0 && nGender != 1)
		return -1;

	static const char *CLASS_NAMES[] = { "Ji", "Dao", "Qiang", "Jian", "Wu" };

	char szCharacterPath[MAX_PATH] = {0};
	sprintf_s(szCharacterPath, MAX_PATH - 1, "DATA\\CHARACTER\\%s\\%s%s.mex",
		ItemDefine::g_szSexType[nGender], ItemDefine::g_szSexType[nGender], CLASS_NAMES[nClass]);

	return GetMexResMgr()->GetIdByName(szCharacterPath);
	/*
	if (nGender == Sex_Male)
	return CHeroGame::m_nSaveRoleID[7 + nClass];
	else
	return CHeroGame::m_nSaveRoleID[1 + nClass];
	*/
}

#pragma message( "以下函数的逻辑很有问题，要改" )
//TODO:以下代码的逻辑很有问题，要改
void CPlayerAnim::PlayAnim3(	DWORD dwAnimType, 
							DWORD dwAnimPlayMode,
							DWORD dwOneLoopTime,
							DWORD dwLoopTimes, 
							DWORD dwTimeOut,
							DWORD dwTargetAnimType, 
							DWORD dwTargetAnimPlayMode )
{
	guardfunc;
	// 判断是否在播放同一个动画
	DWORD dwLastAnimType = m_dwAnimType;
	BOOL bSameAnimType = ( m_dwAnimType == dwAnimType );

	m_dwAnimType = dwAnimType;
	m_dwTargetAnimType = dwTargetAnimType;
	m_dwAnimPlayMode = dwAnimPlayMode;
	//
	// 清除动画
	ClearAnims();

	//if (m_pPlayer)
	//    printf_s("玩家[%s]\n", m_pPlayer->GetName());

	MexAnimCtrl::SPlayTask task0, task1;
	ResetPlayTask( &task0 );
	std::string szReplaceAction0, szReplaceAction1;
	char* pszActionname0 = (char*)MoreAction::FindNameById( dwAnimType );
	assert( pszActionname0 != NULL && "cannot find action name" );

	if( pszActionname0 == NULL )
		pszActionname0 = "idle";

	szReplaceAction0 = pszActionname0;

	strcpy( task0.szActionname, szReplaceAction0.c_str() );
	task0.dwOneLoopTime = dwOneLoopTime;
	task0.dwLoopTimes = dwLoopTimes;
	task0.dwTimeOut = dwTimeOut;
	task0.dwPlayMode = dwAnimPlayMode;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();
	task0.dwNeedBlendingTime = MexAnimCtrl::eDefaultBlendingTime;

	if( dwTimeOut == MexAnimCtrl::eMaxTimeout && dwLoopTimes == MexAnimCtrl::eMaxLoopTimes )
	{
		task0.bLoopPlay = TRUE;
	}
	else
	{
		task0.bLoopPlay = FALSE;
	}

	//设置当前动画
	PushAnim( &task0 );

	char* pszActionname1 = (char*)MoreAction::FindNameById( dwTargetAnimType );
	if( pszActionname1 == NULL )
	{
		pszActionname1 = "idle";
	}
	szReplaceAction1 = pszActionname1;

	strcpy( task1.szActionname, szReplaceAction1.c_str() );
	task1.dwOneLoopTime = 0;
	task1.dwLoopTimes = MexAnimCtrl::eMaxLoopTimes;
	task1.dwTimeOut = MexAnimCtrl::eMaxTimeout;
	task1.dwPlayMode = dwTargetAnimPlayMode;
	// 将BlendingTime设置成0是为了不和死亡动画Blending(不然会出现尸体跳一下)
	// 以后应将这个函数去掉，改成传值进来
	task1.dwNeedBlendingTime = 0;

	if( dwOneLoopTime == 0 )
		task1.dwStartTime = task0.dwStartTime+GetAnimTimeLength( pszActionname1 );
	else
		task1.dwStartTime = task0.dwStartTime+dwTimeOut;

	task1.bLoopPlay = TRUE;

	//设置后备动画，（第一个动作完成后，回到的动作）
	PushAnim( &task1 );
	unguard;
}

void CPlayerAnim::PlayInsertAnim( const char* AnimName, DWORD AnimPlayMode /* = MexAnimCtrl::eNormalPlay */, DWORD OneLoopTime /* = 0 */, DWORD LoopTimes /* = 1 */, DWORD TimeOut /* = MexAnimCtrl::eMaxTimeout  */)
{
	guardfunc;

	//////////////////////
	//// 判断是否在播放同一个动画
	m_dwAnimPlayMode = AnimPlayMode;
	DWORD dwLastAnimType = m_dwTargetAnimType;
	// 清除动画
	ClearAnims();

	MexAnimCtrl::SPlayTask task0, task1;
	ResetPlayTask( &task0 );

	assert( AnimName != NULL && "cannot find action name" );
	if( AnimName == NULL )
	{
		AnimName = "idle";
	}
	strcpy( task0.szActionname, AnimName );
	task0.dwOneLoopTime = OneLoopTime;
	task0.dwLoopTimes = LoopTimes;
	task0.dwTimeOut = TimeOut;
	task0.dwPlayMode = AnimPlayMode;
	task0.dwNeedBlendingTime = MexAnimCtrl::eDefaultBlendingTime;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();

	//设置当前动画
	PushAnim( &task0 );

	char* pszActionname1 = "idle";

	strcpy( task1.szActionname, pszActionname1 );
	task1.dwOneLoopTime = 0;
	task1.dwLoopTimes = MexAnimCtrl::eMaxLoopTimes;
	task1.dwTimeOut = MexAnimCtrl::eMaxTimeout;
	task1.dwPlayMode = MexAnimCtrl::eNormalPlay;
	task1.dwNeedBlendingTime = MexAnimCtrl::eDefaultBlendingTime;

	if( OneLoopTime == 0 )
	{
		task1.dwStartTime = task0.dwStartTime+GetAnimTimeLength( pszActionname1 );
	}
	else
	{
		task1.dwStartTime = task0.dwStartTime+TimeOut;
	}
	task1.bLoopPlay = TRUE;

	//设置后备动画，（第一个动作完成后，回到的动作）
	PushAnim( &task1 );
	unguard;
}

int CPlayerAnim::PlayAnimByActionName( const char* szAnimName, DWORD dwAnimPlayMode,
									  DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime,
									  const char* szTargetAnimName, DWORD dwTargetAnimPlayMode, DWORD dwTargetOneLoopTime /* = 0 */, 
									  DWORD dwTargetLoopTimes /* = eMaxLoopTimes */, 
									  DWORD dwTargetTimeOut /* = eMaxTimeout */,
									  DWORD dwTargetBlendingTime /* = eDefaultBlendingTime  */)
{
	guardfunc;

	//////////////////////
	//// 判断是否在播放同一个动画
	assert( szAnimName != NULL && "cannot find action name" );
	if( szAnimName == NULL )
	{
		szAnimName = "idle";
	}

	DWORD dwAnimType = MoreAction::FindIdByName(szAnimName);
	if( GetCurAnimType() == dwAnimType )
		return 0;

	m_dwAnimPlayMode = dwAnimPlayMode;
	// 清除动画
	ClearAnims();

	MexAnimCtrl::SPlayTask task0, task1;
	ResetPlayTask( &task0 );

	if( dwOneLoopTime == 0 )
	{
		task0.dwOneLoopTime = GetAnimTimeLength( szAnimName );
	}
	m_dwAnimType = dwAnimType;

	strcpy( task0.szActionname, szAnimName );
	task0.dwLoopTimes = dwLoopTimes;
	task0.dwTimeOut = dwTimeOut;
	task0.dwPlayMode = dwAnimPlayMode;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();
	task0.dwNeedBlendingTime = dwBlendingTime;
	task0.bLoopPlay = TRUE;

	//设置当前动画
	PushAnim( &task0 );

	if( szTargetAnimName == NULL )
		szTargetAnimName = "idle";
	strcpy( task1.szActionname, szTargetAnimName );

	m_dwTargetAnimType = MoreAction::FindIdByName(szTargetAnimName);

	if( dwTargetOneLoopTime == 0 )
		task1.dwOneLoopTime = GetAnimTimeLength( szTargetAnimName );
	else
		task1.dwOneLoopTime = dwTargetOneLoopTime;
	task1.dwLoopTimes = dwTargetLoopTimes;
	task1.dwTimeOut = dwTargetTimeOut;
	task1.dwPlayMode = dwTargetAnimPlayMode;
	task1.dwNeedBlendingTime = dwTargetBlendingTime;

	if( dwOneLoopTime == 0 )
	{
		task1.dwStartTime = task0.dwStartTime+GetAnimTimeLength( szAnimName );
	}
	else
	{
		task1.dwStartTime = task0.dwStartTime+dwTimeOut;
	}
	task1.bLoopPlay = TRUE;

	//设置后备动画，（第一个动作完成后，回到的动作）
	PushAnim( &task1 );
	return task0.dwOneLoopTime;
	unguard;
}

void CPlayerAnim::PlayUpperAnim( DWORD dwAnimType, DWORD dwAnimPlayMode, DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, 
								DWORD dwBlendingTime, BOOL bWholeBodyAnim/* = FALSE*/, BOOL bNormalAttackAnim/* = FALSE*/ )
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
	{
		return;
	}

	ClearUpperBodyAnims();

	MexAnimCtrl::SPlayTask task;
	ResetPlayTask( &task );

	std :: string szReplaceAction0 , szReplaceAction1;
	char* pszActionname = (char*)MoreAction::FindNameById( dwAnimType );
	assert( pszActionname != NULL && "cannot find action name" );
	if( pszActionname == NULL )
	{
		pszActionname = "idle";
	}

	if( IsAnimNeedHideWeapon(pszActionname) )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(FALSE);
	}

	szReplaceAction0 = pszActionname;
	strcpy( task.szActionname, szReplaceAction0.c_str() );
	task.dwOneLoopTime = dwOneLoopTime;
	task.dwLoopTimes = dwLoopTimes;
	task.dwTimeOut = dwTimeOut;
	task.dwPlayMode = dwAnimPlayMode;
	task.dwStartTime = MexAnimCtrl::GetGameTime();
	task.dwNeedBlendingTime = dwBlendingTime;
	task.bUpperBody = TRUE;
	task.bWholeBodyAnim = bWholeBodyAnim;
	task.bNormalAttack = bNormalAttackAnim;
	if( dwTimeOut == MexAnimCtrl::eMaxTimeout && dwLoopTimes == MexAnimCtrl::eMaxLoopTimes )
	{
		task.bLoopPlay = TRUE;
	}
	else
	{
		task.bLoopPlay = FALSE;
	}

	//设置当前动画
	PushUpperBodyAnim( &task );

	// 旗子动作
	TryPlayFlagAnim(szReplaceAction0.c_str());

	unguard;
}

void CPlayerAnim::PlayUpperAnim( const char* szAnimName, DWORD dwAnimPlayMode, DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, 
								DWORD dwBlendingTime, BOOL bWholeBodyAnim/* = FALSE*/, BOOL bNormalAttackAnim/* = FALSE*/,
								BOOL bIsPlayerRole)
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
	{
		return;
	}

	if( IsAnimNeedHideWeapon(szAnimName) )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(FALSE);
	}

	// 如果正在播放技能动作, 则要等到动作播完才播放普通攻击的动作
	if (bIsPlayerRole)
	{
		SPlayTask *pTask = &m_UpperBodyPlayTask[0];
		if (pTask != NULL && szAnimName != NULL)
		{
			if (bNormalAttackAnim)
			{
				if (strstr(pTask->szActionname, "skill_") == pTask->szActionname)
				{
					DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
					DWORD dwTime = HQ_TimeGetTime();
					DWORD dwDuration = m_UpperBodyAnimTimeLine.GetOneLoopTime() * pTask->dwLoopTimes;
					if ((dwTime - dwStartTime) < dwDuration)
					{
						return;
					}
				}
			}
		}
	}

	// 清除动画
	ClearUpperBodyAnims();

	MexAnimCtrl::SPlayTask task;
	ResetPlayTask( &task );

	std :: string szReplaceAction0;
	if( szAnimName == NULL )
	{
		szAnimName = "idle";
	}

	szReplaceAction0 = szAnimName;

	strcpy( task.szActionname, szReplaceAction0.c_str() );
	task.dwOneLoopTime = dwOneLoopTime;
	task.dwLoopTimes = dwLoopTimes;
	task.dwTimeOut = dwTimeOut;
	task.dwPlayMode = dwAnimPlayMode;
	task.dwStartTime = MexAnimCtrl::GetGameTime();
	task.dwNeedBlendingTime = dwBlendingTime;
	task.bUpperBody = TRUE;
	task.bWholeBodyAnim = bWholeBodyAnim;
	task.bNormalAttack = bNormalAttackAnim;
	if( dwTimeOut == MexAnimCtrl::eMaxTimeout && dwLoopTimes == MexAnimCtrl::eMaxLoopTimes )
	{
		task.bLoopPlay = TRUE;
	}
	else
	{
		task.bLoopPlay = FALSE;
	}
	//设置当前动画
	PushUpperBodyAnim( &task );

	// 旗子动作
	TryPlayFlagAnim(szReplaceAction0.c_str());

	unguard;
}

void CPlayerAnim::PlayLowerAnim( DWORD dwAnimType, DWORD dwAnimPlayMode, DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime, DWORD dwTargetAnimType, DWORD dwTargetAnimPlayMode, DWORD dwTargetOneLoopTime /* = 0 */, DWORD dwTargetLoopTimes /* = eMaxLoopTimes */, DWORD dwTargetTimeOut /* = eMaxTimeout */, DWORD dwTargetBlendingTime /* = eDefaultBlendingTime  */)
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
	{
		return;
	}
	if( m_dwAnimType == dwAnimType )
	{
		// 非NPC则不播放重复动作
		if( m_pPlayer && !m_pPlayer->IsNpc() )
		{
			if( GetCurLowerAnimType() == dwAnimType )
				return;
		}
	}

	// 判断是否隐藏武器
	const char* szAnimName = MoreAction::FindNameById(dwAnimType);
	if( IsAnimNeedHideWeapon(szAnimName) )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(FALSE);
	}
	else if( IsCurrAnimHideWeapon() )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(TRUE);
	}

	// 清除动画
	ClearLowerBodyAnims();

	MexAnimCtrl::SPlayTask task0, task1;
	ResetPlayTask( &task0 );

	std :: string szReplaceAction0 , szReplaceAction1;
	char* pszActionname0 = (char*)MoreAction::FindNameById( dwAnimType );
	//assert( pszActionname0 != NULL && "cannot find action name" );
	// 记录要播放的动画ID
	m_dwAnimType = dwAnimType;
	if( pszActionname0 == NULL )
	{
		pszActionname0 = "idle";
		m_dwAnimType = 0;
	}

	szReplaceAction0 = pszActionname0;
	strcpy( task0.szActionname, szReplaceAction0.c_str() );
	task0.dwOneLoopTime = dwOneLoopTime;
	task0.dwLoopTimes = dwLoopTimes;
	task0.dwTimeOut = dwTimeOut;
	task0.dwPlayMode = dwAnimPlayMode;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();
	task0.dwNeedBlendingTime = dwBlendingTime;
	task0.bUpperBody = FALSE;
	if( dwTimeOut == MexAnimCtrl::eMaxTimeout && dwLoopTimes == MexAnimCtrl::eMaxLoopTimes )
	{
		task0.bLoopPlay = TRUE;
	}
	else
	{
		task0.bLoopPlay = FALSE;
	}

	//设置当前动画
	PushLowerBodyAnim( &task0 );

	// 旗子动作
	TryPlayFlagAnim(szReplaceAction0.c_str());

	char* pszActionname1 = (char*)MoreAction::FindNameById( dwTargetAnimType );
	m_dwTargetAnimType = dwTargetAnimType;
	if( pszActionname1 == NULL )
	{
		pszActionname1 = "idle";
		m_dwTargetAnimType = 0;
	}

	szReplaceAction1 = pszActionname1;

	strcpy( task1.szActionname, szReplaceAction1.c_str() );
	task1.dwOneLoopTime = dwTargetOneLoopTime;
	task1.dwLoopTimes = dwTargetLoopTimes;
	task1.dwTimeOut = dwTargetTimeOut;
	task1.dwPlayMode = dwTargetAnimPlayMode;
	task1.dwNeedBlendingTime = dwTargetBlendingTime;
	task1.dwStartTime = MexAnimCtrl::GetGameTime();
	task1.bUpperBody = FALSE;
	task1.bLoopPlay = TRUE;

	//设置后备动画，（第一个动作完成后，回到的动作）
	PushLowerBodyAnim( &task1 );
	unguard;
}

void CPlayerAnim::PlayLowerAnim( const char* szAnimName, DWORD dwAnimPlayMode, DWORD dwOneLoopTime, DWORD dwLoopTimes, DWORD dwTimeOut, DWORD dwBlendingTime, const char* szTargetAnimName, DWORD dwTargetAnimPlayMode, DWORD dwTargetOneLoopTime /* = 0 */, DWORD dwTargetLoopTimes /* = eMaxLoopTimes */, DWORD dwTargetTimeOut /* = eMaxTimeout */, DWORD dwTargetBlendingTime /* = eDefaultBlendingTime  */)
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
	{
		return;
	}

	DWORD dwAnimType;
	assert( szAnimName != NULL && "cannot find action name" );
	if( szAnimName == NULL )
	{
		szAnimName = "idle";
		dwAnimType = 0;
	}
	else
	{
		dwAnimType = MoreAction::FindIdByName(szAnimName);
		if( dwAnimType == -1 )
			dwAnimType = 0;
	}

	if( m_dwAnimType == dwAnimType )
	{
		// 非NPC则不播放重复动作
		if( m_pPlayer && !m_pPlayer->IsNpc() )
		{
			if( GetCurLowerAnimType() == dwAnimType )
				return;
		}
	}

	// 判断是否隐藏武器
	if( IsAnimNeedHideWeapon(szAnimName) )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(FALSE);
	}
	else if( IsCurrAnimHideWeapon() )
	{
		if( m_pPlayer && m_pPlayer->IsHaveWeapon() )
			m_pPlayer->SetShowWeapon(TRUE);
	}

	m_dwAnimType = dwAnimType;
	// 清除动画
	ClearLowerBodyAnims();

	std :: string szReplaceAction0, szReplaceAction1;
	MexAnimCtrl::SPlayTask task0, task1;
	ResetPlayTask( &task0 );

	szReplaceAction0 = szAnimName;

	strcpy( task0.szActionname, szReplaceAction0.c_str() );
	task0.dwOneLoopTime = dwOneLoopTime;
	task0.dwLoopTimes = dwLoopTimes;
	task0.dwTimeOut = dwTimeOut;
	task0.dwPlayMode = dwAnimPlayMode;
	task0.dwStartTime = MexAnimCtrl::GetGameTime();
	task0.dwNeedBlendingTime = dwBlendingTime;
	task0.bUpperBody = FALSE;
	if( dwTimeOut == MexAnimCtrl::eMaxTimeout && dwLoopTimes == MexAnimCtrl::eMaxLoopTimes )
	{
		task0.bLoopPlay = TRUE;
	}
	else
	{
		task0.bLoopPlay = FALSE;
	}
	//设置当前动画
	PushLowerBodyAnim( &task0 );

	// 旗子动作
	TryPlayFlagAnim(szReplaceAction0.c_str());

	//////////////////////////////
	if( szTargetAnimName == NULL )
	{
		szTargetAnimName = "idle";
		m_dwTargetAnimType = 0;
	}
	else
	{
		m_dwTargetAnimType = MoreAction::FindIdByName(szTargetAnimName);
		if( m_dwTargetAnimType == -1 )
			m_dwTargetAnimType = 0;

	}

	szReplaceAction1 = szTargetAnimName;

	strcpy( task1.szActionname, szReplaceAction1.c_str() );
	task1.dwOneLoopTime = dwTargetOneLoopTime;
	task1.dwLoopTimes = dwTargetLoopTimes;
	task1.dwTimeOut = dwTargetTimeOut;
	task1.dwPlayMode = dwTargetAnimPlayMode;
	task1.dwNeedBlendingTime = dwTargetBlendingTime;
	task1.dwStartTime = MexAnimCtrl::GetGameTime();
	task1.bUpperBody = FALSE;
	task1.bLoopPlay = TRUE;
	//设置后备动画，（第一个动作完成后，回到的动作）
	PushLowerBodyAnim( &task1 );
	unguard;
}


void CPlayerAnim::Destroy()
{
	guardfunc;
	if( g_bMultiThreadLoadingMex )
	{
		MeLoopThreadMan::Instance()->UnRegisterPointer( this );
	}

	guard(Destroy1);
	MexAnimCtrl::Destroy();
	unguard;

	// 模型特效

	guard(Destroy2);
	EquipEffectMexs::iterator it, end = _equipEffectMexs.end();
	for ( it = _equipEffectMexs.begin(); it != end; ++it )
	{
		MexAnimCtrl* pMexAnimCtrl = it->second;
		if ( NULL != pMexAnimCtrl )
		{
			pMexAnimCtrl->Destroy();
			delete pMexAnimCtrl;
			it->second = NULL;
		}
	}
	_equipEffectMexs.clear();

	if ( m_pAvatar != NULL)
	{
		MeDelete m_pAvatar;
		m_pAvatar = NULL;
	}

	if (m_pEffectAnim != NULL)
	{
		m_pEffectAnim->Destroy();
		MeDelete m_pEffectAnim;
		m_pEffectAnim = NULL;
	}
	unguard;

	unguard;
}

void CPlayerAnim::SetFightState( BOOL fight_flag )
{
	guardfunc;
	if( fight_flag )
	{
		m_pAvatar->SetItemFlag( CAvatar::eItem_RightHand );
	}
	else
	{
		m_pAvatar->SetItemFlag( CAvatar::eItem_RBack );
	}
	return;
	unguard;
}

BOOL CPlayerAnim::ChangeWeaponAnim( int nWeaponModelId )
{
	MexResMgr::Record* pWeaponRecord = GetMexResMgr()->GetRecord( nWeaponModelId );
	MexResMgr::Res* pWeaponRes = &pWeaponRecord->res;

	if( !pWeaponRecord /*|| !pWeaponRes->pMex*/ || !pWeaponRes->pMexCfg )
	{
		return FALSE;
	}
	// pWeaponRecord的动画数据已移植到通用动画数据里，所以pMex已无效，只要更新pMexCfg
	SetMexCfg(pWeaponRes->pMexCfg);
	SetCurAnimType(-1);
	return TRUE;
}

BOOL CPlayerAnim::ChangeWeaponAnim( int nProfession, int nWeaponModelId )
{
	MexResMgr::Record* pWeaponRecord = GetMexResMgr()->GetRecord( nWeaponModelId );
	MexResMgr::Res* pWeaponRes = &pWeaponRecord->res;

	if( !pWeaponRecord /*|| !pWeaponRes->pMex*/ || !pWeaponRes->pMexCfg )
	{
		return FALSE;
	}

	SetMexCfg(pWeaponRes->pMexCfg);
	SetCurAnimType(-1);
	return TRUE;
}

int CPlayerAnim::GetWeaponActionModelId( int nProfession, int nSex, BOOL bHoldFlag/* = FALSE*/ )
{
	guardfunc;
	if( nSex != 0 && nSex != 1 )
		return -1;
	char szPath[MAX_PATH] = {0};
	char szName[MAX_PATH] = {0};
	if( !GetModelProjMgr()->GetProfessionName(nProfession) )
		return -1;

	if( !bHoldFlag )
		MeSprintf_s( szName,sizeof(szName)/sizeof(char) - 1, "%s%s", ItemDefine::g_szSexType[nSex], GetModelProjMgr()->GetProfessionName(nProfession) );
	else
		MeSprintf_s( szName,sizeof(szName)/sizeof(char) - 1, "%sFlag", ItemDefine::g_szSexType[nSex] );
	MeSprintf_s( szPath,sizeof(szPath)/sizeof(char) - 1, "Data\\Character\\%s\\%s.mex", ItemDefine::g_szSexType[nSex], szName );

	int iModelId = GetMexResMgr()->GetIdByName( szPath );
	//  	if( iModelId == -1 )
	//  	{
	//  		iModelId = GetMexResMgr()->AddExternalFile( szPath );
	//  	}

	return iModelId;
	unguard;
}

void CPlayerAnim::ForceCurrAnimLoopTime(int nTimes, BOOL bUpperAnim/* = FALSE*/)
{
	if( bUpperAnim )
	{
		if( m_nNumUpperBodyPlayTask > 0 )
		{
			if( nTimes >= 0 )
				m_UpperBodyPlayTask[0].dwLoopTimes = nTimes;
			else
				m_UpperBodyPlayTask[0].dwLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( HQ_TimeGetTime() );// + 1;
		}
	}
	else if( m_nNumLowerBodyPlayTask > 1 )
	{
		if( nTimes >= 0 )
			m_LowerBodyPlayTask[0].dwLoopTimes = nTimes;
		else
			m_LowerBodyPlayTask[0].dwLoopTimes = m_LowerBodyAnimTimeLine.GetNumLooped( HQ_TimeGetTime() ) + 1;
	}
	else if( m_nNumPlayTask > 1 )
	{
		if( nTimes >= 0 )
			m_PlayTasks[0].dwLoopTimes = nTimes;
		else
			m_PlayTasks[0].dwLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( HQ_TimeGetTime() ) + 1;
	}
}

BOOL CPlayerAnim::CanSwitchIdleAnim()
{
	if( IsCurrAnimHideWeapon() )
		return FALSE;
	return TRUE;
}

BOOL CPlayerAnim::IsCurrAnimHideWeapon()
{
	if( gCfg.m_vectorHideWeaponAnims.size() )
	{
		const char *szCurrAnim = MoreAction::FindNameById( GetCurAnimType() );
		for(int i=0; i<gCfg.m_vectorHideWeaponAnims.size(); ++i)
		{
			if( szCurrAnim && !stricmp(szCurrAnim, gCfg.m_vectorHideWeaponAnims[i].c_str()) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CPlayerAnim::IsUpperAnimHideWeapon()
{
	if( !GetCurUpperAnim() )
		return FALSE;

	if( gCfg.m_vectorHideWeaponAnims.size() )
	{
		for(int i=0; i<gCfg.m_vectorHideWeaponAnims.size(); ++i)
		{
			if( !stricmp(GetCurUpperAnim(), gCfg.m_vectorHideWeaponAnims[i].c_str()) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CPlayerAnim::IsLowerAnimHideWeapon()
{
	if( !GetCurLowerAnim() )
		return FALSE;

	if( gCfg.m_vectorHideWeaponAnims.size() )
	{
		for(int i=0; i<gCfg.m_vectorHideWeaponAnims.size(); ++i)
		{
			if( !stricmp(GetCurLowerAnim(), gCfg.m_vectorHideWeaponAnims[i].c_str()) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CPlayerAnim::IsAnimNeedHideWeapon( const char* szAnimName )
{
	if( !szAnimName )
		return FALSE;

	if( gCfg.m_vectorHideWeaponAnims.size() )
	{
		for(int i=0; i<gCfg.m_vectorHideWeaponAnims.size(); ++i)
		{
			if( !stricmp(szAnimName, gCfg.m_vectorHideWeaponAnims[i].c_str()) 
				|| !stricmp(szAnimName, gCfg.m_vectorHideWeaponAnims[i].c_str()) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


BOOL CPlayerAnim::IsInteractionAnim()
{
	return (m_dwAnimType == MoreActionClient::yongbao);
}

BOOL CPlayerAnim::IsLootAnim()
{
	if( GetCurAnimType() == MoreActionClient::loot )
		return TRUE;

	return FALSE;
}

BOOL CPlayerAnim::IsIntonateAnim()
{
	if( GetCurAnimType() == MoreActionClient::Intonate )
		return TRUE;

	return FALSE;
}


BOOL CPlayerAnim::IsHoldingFlagOnRightHand(CPlayer_SEquipment *pEquip/*=NULL*/)
{
	BOOL bIsHoldingFlag = FALSE;
	// 是否拿旗子
	CPlayer_SEquipment *pRightHandEquip = (CPlayer_SEquipment *)pEquip;
	if( pRightHandEquip == NULL && m_pPlayer)
		pRightHandEquip = &m_pPlayer->GetEquip()[eKeyAll_RHandItem];
	if( pRightHandEquip && pRightHandEquip->item.itembaseinfo.ustItemID != InvalidLogicNumber )
	{
		ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pRightHandEquip->item.itembaseinfo.ustItemID );
		if( pItem )
		{
			if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
			{
				ItemDefine::SItemWeapon *pWeapon = (ItemDefine::SItemWeapon *)pItem;
				if( pWeapon->stWeaponType == eWeapontype_Flag )
					bIsHoldingFlag = TRUE;
			}
		}
	}
	// 如果m_pPlayer为空，则保存拿旗状态
	if( !m_pPlayer )
		m_bIsHoldingFlagOnRightHand = bIsHoldingFlag;

	return bIsHoldingFlag;
}

void CPlayerAnim::TryPlayFlagAnim( const char* szAnimName )
{
	if( !szAnimName )
		return;

	if( !m_pAvatar )
		return;

	CAvatar::Component* pRightHandItem = m_pAvatar->GetComponent(eKeyAll_RHandItem);
	BOOL bIsHoldingFlag = m_bIsHoldingFlagOnRightHand;
	if( !bIsHoldingFlag && m_pPlayer )
		bIsHoldingFlag = IsHoldingFlagOnRightHand();

	if( pRightHandItem && bIsHoldingFlag )
	{
		// 拿着旗子
		for( int nAnim = 0; nAnim < CAvatar::eMaxPartAnim; nAnim++ )
		{
			MexAnimCtrl* pFlagAnim = pRightHandItem->GetMexAnim(nAnim);
			if( pFlagAnim && pFlagAnim->GetMexCfg() )
			{
				MexAnimCtrl::SPlayTask* pPlayTask = pFlagAnim->GetPlayTask(0);
				if( !pPlayTask )
					continue;

				if( pFlagAnim->GetMexCfg()->GetSequence(szAnimName) )
				{
					if( stricmp(pPlayTask->szActionname, szAnimName) )
						pFlagAnim->PlayAnimByName( szAnimName, 0, TRUE );
				}
				else
				{
					if( stricmp(pPlayTask->szActionname, "single_idle") )
						pFlagAnim->PlayAnimByName( "single_idle", 0, TRUE );
				}
			}
		}
	}

}

void CPlayerAnim::TryPlayFlagAnim( DWORD dwAnimType )
{
	const char* szAnimName = MoreAction::FindNameById(dwAnimType);
	if( szAnimName /*&& IsUpperBodyAndLowerBodyMode()*/ )
		TryPlayFlagAnim(szAnimName);
}

void CPlayerAnim::SetPlayTargetAnim()
{
	m_dwAnimType = m_dwTargetAnimType;
	TryPlayFlagAnim( m_dwAnimType );
}

void CPlayerAnim::PlayDefaultAnimAfterChangeModel()
{
	if( GetMex() == NULL || GetMexCfg() == NULL )
	{
		m_bNpcNeedReplayAnim = TRUE;
		return;
	}

	if( m_bNpcNeedReplayAnim )
		m_bNpcNeedReplayAnim = FALSE;

	if( m_dwAnimType == -1 )
		return;

	SPlayTask* pCurPlayTask0 = NULL;
	SPlayTask* pCurPlayTask1 = NULL;

	if( IsUpperBodyAndLowerBodyMode() )
	{
		pCurPlayTask0 = MexAnimCtrl::GetLowerBodyPlayTask(0);
		if( m_nNumLowerBodyPlayTask > 1 )
			pCurPlayTask1 = MexAnimCtrl::GetLowerBodyPlayTask(1);
	}
	else
	{
		pCurPlayTask0 = MexAnimCtrl::GetPlayTask(0);
		if( m_nNumPlayTask > 1 )
			pCurPlayTask1 = MexAnimCtrl::GetPlayTask(1);
	}

	MexAnimCtrl::SPlayTask task0, task1;

	if( pCurPlayTask0 )
	{
		ResetPlayTask( &task0 );
		strcpy( task0.szActionname, pCurPlayTask0->szActionname );
		task0.dwOneLoopTime = pCurPlayTask0->dwOneLoopTime;
		task0.dwLoopTimes = pCurPlayTask0->dwLoopTimes;
		task0.dwTimeOut = pCurPlayTask0->dwTimeOut;
		task0.dwPlayMode = pCurPlayTask0->dwPlayMode;
		task0.dwStartTime = MexAnimCtrl::GetGameTime();
		task0.dwNeedBlendingTime = pCurPlayTask0->dwNeedBlendingTime;
		task0.bLoopPlay = pCurPlayTask0->bLoopPlay;
	}
	if( pCurPlayTask1 )
	{
		ResetPlayTask( &task1 );
		strcpy( task1.szActionname, pCurPlayTask1->szActionname );
		task1.dwOneLoopTime = pCurPlayTask1->dwOneLoopTime;
		task1.dwLoopTimes = pCurPlayTask1->dwLoopTimes;
		task1.dwTimeOut = pCurPlayTask1->dwTimeOut;
		task1.dwPlayMode = pCurPlayTask1->dwPlayMode;
		task1.dwStartTime = MexAnimCtrl::GetGameTime();
		task1.dwNeedBlendingTime = pCurPlayTask1->dwNeedBlendingTime;
		task1.bLoopPlay = pCurPlayTask1->bLoopPlay;
	}
	if( stricmp(task0.szActionname,"temp2006") == 0 )
	{
		if( m_pPlayer )
		{
			if( m_pPlayer->IsMoving() )
			{
				strcpy(task0.szActionname,"walk");
			}
			else
			{
				strcpy(task0.szActionname,"idle");
			}
		}
	}

	//设置当前动画
	if( pCurPlayTask0 || pCurPlayTask1 )
	{
		if( IsUpperBodyAndLowerBodyMode() )
		{
			ClearLowerBodyAnims();
			if( pCurPlayTask0 )
				PushLowerBodyAnim( &task0 );
			if( pCurPlayTask1 )
				PushLowerBodyAnim( &task1 );
		}
		else
		{
			ClearAnims();
			if( pCurPlayTask0 )
				PushAnim( &task0 );
			if( pCurPlayTask1 )
				PushAnim( &task1 );
		}
	}

}

void CPlayerAnim::UpdateAvatar( DWORD dwTime, float* pfModel, CAvatar* pAvatar )
{
	guardfunc;
	D3DXMATRIX matModel( pfModel );
	DWORD dwItemFlag = pAvatar->GetItemFlag();		
	BOOL bUseLightTrack = FALSE;
	if( m_pSeqUpperBody )
		bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();

	for( int nComponent = 0; nComponent < pAvatar->GetComponentCount(); nComponent++ )
	{
		CAvatar::Component* pComponent = pAvatar->GetComponent( nComponent );
		IMexSkeleton* pSkeleton = 0;
		if( pComponent->pMex )
			pSkeleton = pComponent->pMex->GetSkeleton();
		else
			pSkeleton = m_pMex->GetSkeleton();

		if( !pComponent )
			continue;

		// 更新动画模型
		if (pComponent->IsAttachment())
		{
			for (int nAnim = 0; nAnim < CAvatar::eMaxPartAnim; ++nAnim)
			{
				MexAnimCtrl *pAnim = pComponent->GetMexAnim(nAnim);
				if (pAnim != NULL)
				{
					IMexAttachment* pAttachment = NULL;
					if (nComponent == eKeyAll_Helmet)
					{					
						pAttachment = pAvatar->GetAttachment(CAvatar::HEAD_ATTACHMENT);
					}
					else if (nComponent == eKeyAll_RHandItem)
					{
						pAttachment = pAvatar->GetAttachment(CAvatar::RIGHTHAND_ATTACHMENT);
					}
					else if (nComponent == eKeyAll_LHandItem)
					{
						pAttachment = pAvatar->GetAttachment(CAvatar::LEFTHAND_ATTACHMENT);
					}

					if (pAttachment )
					{
						pAnim->SetScaleXYZ( m_fScaleX, m_fScaleY, m_fScaleZ );
						int nAttachBoneID = pAttachment->GetAttachBoneID();
						D3DXMATRIX matHelperInit = *(D3DXMATRIX*)pAttachment->GetInitMatrix();
						if (nComponent ==  eKeyAll_RHandItem)
						{
							if (nAnim == 1)
							{
								MexAnimCtrl *firstAnim = pComponent->GetMexAnim(0);
								if (firstAnim != NULL && firstAnim->GetMex() != NULL)
								{
									pAnim->UpdateFollowParent(dwTime, firstAnim, "effect.Bone002");
								}														
							}
							else
							{
								pAnim->UpdateAsAnimComponent(dwTime, this, nAttachBoneID, (float *) &matHelperInit);
							}
						}
						else
						{
							pAnim->UpdateAsComponent( dwTime, this, nAttachBoneID, (float*)&matHelperInit );
						}

						if (GetBindingBowString() && nComponent == eKeyAll_LHandItem)
						{
							int nStringIndex = 0;
							if (nStringIndex = pAnim->GetMex()->GetSkeleton()->FindBone( "BowString" ) != -1 )
							{//弓箭
								IMexAttachment* pRightAttachment = pAvatar->GetAttachment(CAvatar::RIGHTHAND_ATTACHMENT);
								int nRightAttachBoneID = pRightAttachment->GetAttachBoneID();
								D3DXMATRIX matRightHelperInit = *(D3DXMATRIX*)pRightAttachment->GetInitMatrix();
								pAnim->UpdateAsComponent( dwTime, this, nRightAttachBoneID, (float*)&matRightHelperInit,nStringIndex );
							}
						}

						// added, jiayi, [2009.4.23],更新特效
						// 特效更新
						CAvatar::EffectContainer* ec = &pComponent->m_EffectContainer;
						for( int nEffect = 0; nEffect < ec->effects.size(); nEffect++ )
						{
							CAvatar::Effect* pEffect = &ec->effects[nEffect];
							if( pEffect->part )
							{
								pEffect->part->Update( 
									dwTime, 
									pAnim->GetScale(),	/*m_fScale,*/	// 因为只能传一个scale
									(float*)(D3DXMATRIX*)pAnim->GetSrcBoneMatrices(),
									(float*)(D3DXMATRIX*)&matModel ,m_nFrameId);
							}
							if(	pEffect->pWeaponBladeRibbon &&
								pEffect->pWeaponBladeRibbon->IsEnable() )
							{
								if( pEffect->pWeaponBladeRibbon->IsDead( dwTime ) )
								{
									pEffect->pWeaponBladeRibbon->Enable( FALSE );
									pEffect->ribb->Clear();
									continue;
								}
								MeMatrix matModel = pAnim->GetModelMatrix();
								pEffect->ribb->Update(dwTime, pAnim->GetFrameId(), (float*)(D3DXMATRIX*)pAnim->GetSrcBoneMatrices(), (float*)(D3DXMATRIX*)&matModel, TRUE );

							}

						}
					}

				}

			}			
			continue;
		}

		// 装备强化特效更新 
		m_pEffectAnim->UpdateFollowParent(dwTime, this, mEquipEffectInfo.szBindBoneName);

		// 特效更新
		CAvatar::EffectContainer* ec = &pComponent->m_EffectContainer;
		for( int nEffect = 0; nEffect < ec->effects.size(); nEffect++ )
		{
			CAvatar::Effect* pEffect = &ec->effects[nEffect];
			if( pEffect->part )
			{
				IMexBone* pBone = NULL;
				pBone = pSkeleton->GetBone( pEffect->part->GetParentBoneID() );
				if( !pBone )
					continue;

				int const MAX_FRAME = 60;
				static D3DXMATRIX amatFrame[MAX_FRAME];
				int nNumFrame = m_nEndFrameId-m_nStartFrameId+1;
				if( nNumFrame > MAX_FRAME )
					nNumFrame = MAX_FRAME;	

				int nFrameID = dwTime/ONEFRAMEINTERVAL;				
				if( pComponent->pMex->GetSkeleton()->GetBone(0)->GetFrameCount() == 0 )
					nFrameID = 0;
				else
					nFrameID %= pComponent->pMex->GetSkeleton()->GetBone(0)->GetFrameCount();

				for( int i = pEffect->part->GetParentBoneID(); i < pSkeleton->GetBoneCount(); i++ )
				{
					IMexBone* pBone = pSkeleton->GetBone(i);

					// 经过这段运算,模型已经在自己的空间中带有了动作,
					// 每个点都变换到模型空间中，
					D3DXMatrixMultiply(
						(D3DXMATRIX*)&amatFrame[i], 
						(D3DXMATRIX*)pBone->GetFrame0Inv(),
						(D3DXMATRIX*)pBone->GetMatrices(nFrameID) );					
				}

				pEffect->part->Update( 
					dwTime, 
					m_fScaleZ,	/*m_fScale,*/	// 因为只能传一个scale
					(float*)m_amatBoneInModelSpace,					
					(float*)&matModel ,m_nFrameId);
			}

			//if( pEffect->ribb )
			// commented out, jiayi, [2009.4.23], /*0*/
			if(	pEffect->pWeaponBladeRibbon &&
				pEffect->pWeaponBladeRibbon->IsEnable() )
			{
				if( pEffect->pWeaponBladeRibbon->IsDead( dwTime ) )
				{
					pEffect->pWeaponBladeRibbon->Enable( FALSE );
					continue;
				}

				IMexBone* pBone = NULL;
				pBone = pSkeleton->GetBone( pEffect->ribb->GetParentBoneID() );
				if( !pBone )
					continue;

				int const MAX_FRAME = 60;
				static D3DXMATRIX amatFrame[MAX_FRAME];
				int nNumFrame = m_nEndFrameId-m_nStartFrameId+1;
				if( nNumFrame > MAX_FRAME )
					nNumFrame = MAX_FRAME;	

				for( int nFrame = 0; nFrame < nNumFrame; nFrame++ )
				{
					D3DXMatrixMultiply(
						(D3DXMATRIX*)&amatFrame[nFrame], 
						(D3DXMATRIX*)pBone->GetFrame0Inv(),
						(D3DXMATRIX*)pBone->GetMatricesFromKeyTime((nFrame+m_nStartFrameId)*ONEFRAMEINTERVAL,FRAMEPERSEC) );
					D3DXMatrixMultiply(
						(D3DXMATRIX*)&amatFrame[nFrame], 
						(D3DXMATRIX*)&amatFrame[nFrame], 
						(D3DXMATRIX*)&m_matModel );

				}
				pEffect->ribb->Update(dwTime, 0,(float*)amatFrame[nNumFrame], (float*)(D3DXMATRIX*)&m_matModel );

			}
		}
	}
	unguard;
}

BOOL CPlayerAnim::RenderAvatar( CAvatar* pAvatar, IRenderer* pRenderer, float fAlpha, int* pRetVertexCount/*=NULL*/, int* pRetFaceCount/*=NULL*/,
							   BOOL bIsHairHelmetAlphaTest/*= FALSE*/,
							   BOOL bRenderShadow/*=FALSE*/, BOOL bRenderAll/*= TRUE*/ )
{
	guardfunc;
	if( !pAvatar )
	{
		assert( false );
		return FALSE;
	}

	//if( bRenderAll )
	//{
	//	for( int nComponent = 0; nComponent < pAvatar->GetComponentCount(); nComponent++ )
	//	{
	//		CAvatar::Component* pComponent = pAvatar->GetComponent( nComponent );

	//		if( !pComponent )
	//			continue;

	//		// 有身体部件没加载完，则不渲染
	//		//if(pComponent->pMex == NULL && (/* nComponent == eKeyAll_Hair || */nComponent == eKeyAll_Armour || /*nComponent == eKeyAll_Glove || */nComponent == eKeyAll_Shoe))
	//		//	return FALSE;
	//	}
	//}

	for( int nComponent = 0; nComponent < pAvatar->GetComponentCount(); nComponent++ )
	{
		CAvatar::Component* pComponent = pAvatar->GetComponent( nComponent );

		if( !pComponent )
			continue;

		int nVertexCount = 0;
		int nFaceCount = 0;
		BOOL bToolMode = GetMe3dConfig()->m_bToolMode;

		if( !bToolMode )
		{
			if(nComponent == eKeyAll_LHandItem)
			{
				pComponent->m_bLeftHand = TRUE;
			}
			else
			{
				pComponent->m_bLeftHand = FALSE;
			}
		}

		if (pComponent->IsAttachment())
		{
			if (pComponent->IsCanSee())
				for (int nAnim = 0; nAnim < eKeyAll_Max; ++nAnim)
				{
					MexAnimCtrl *pAnim = pComponent->GetMexAnim(nAnim);
					if (pAnim != NULL)
					{
						MexCfgAvatarSetting* pOldAvatarSetting = pAnim->GetAvatarSetting();
						pAnim->SetAvatarSetting( pComponent->m_pAvatarSetting );
						pAnim->m_SpecularTexID = pComponent->m_nSpecularTexID;
						//pAnim->m_GlowTexID = pComponent->m_nGlowTexID;
						pAnim->m_pUseTextureProj = &pComponent->ReplaceableTextureProj;
						pAnim->m_pUseLuminanceTexProj = &pComponent->LuminanceTextureProj;
						pAnim->m_pUseShimmerGrayTextureProj = &pComponent->ShimmerGrayTextureProj;
						pAnim->m_pMaterial = &pComponent->material;
						// added, jiayi, [2009/7/18]
						pAnim->SetRenderFlag( m_dwRenderFlag );
						pAnim->Render( fAlpha, NULL, &nVertexCount, &nFaceCount, NULL,  bRenderShadow );
						// added, jiayi, [2009.4.23],ribbon emitter
						if( !bRenderShadow )
						{
							CAvatar::EffectContainer* ec = &pComponent->m_EffectContainer;
							for( int nEffect = 0; nEffect < ec->effects.size(); nEffect++ )
							{
								CAvatar::Effect* pEffect = &ec->effects[nEffect];

								if( !AvatarComponentTest( pComponent->m_bLeftHand, pEffect->dwFlag, pAvatar->GetItemFlag() ) )
									continue;

								if( pEffect->part )
								{
									int nLocalTextureId = pEffect->part->GetLocalTextureID();
									int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
								}

								DWORD dwCurTime = HQ_TimeGetTime();
								bool bUseLightTrack = false;
								if( m_pSeqUpperBody )
								{
									bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();
								}
								if( pEffect->pWeaponBladeRibbon && !pEffect->pWeaponBladeRibbon->IsEnable())
									continue;

								if( pEffect->ribb && ( bUseLightTrack || dwCurTime - m_dwLightTrackDeadTime < LIGHTTRACKDEADRENDERTIME ) )
								{
									float fAlpha = (float)( LIGHTTRACKDEADRENDERTIME - ( dwCurTime - m_dwLightTrackDeadTime ) )/LIGHTTRACKDEADRENDERTIME;
									if( m_fLightTrackAlpha < fAlpha )
									{
										m_fLightTrackAlpha += 0.03f ;
									}
									else
									{
										m_fLightTrackAlpha = fAlpha;
									}

									int nLocalTextureId = pEffect->ribb->GetLocalTextureID();
									int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
									pEffect->ribb->Render( NULL, nTextureId, m_fLightTrackAlpha, false, false );
								}
							}
						}

						pAnim->m_SpecularTexID = -1;
						pAnim->m_pUseTextureProj = NULL;
						pAnim->SetAvatarSetting( pOldAvatarSetting );
						pAnim->m_pUseLuminanceTexProj = NULL;
					}
				}
		}
		else
		{
			BOOL bHairHelmet = (nComponent == eKeyAll_Hair) || (nComponent == eKeyAll_Helmet);
			RenderAvatorComponent( pAvatar, pComponent, pRenderer, fAlpha, false, &nVertexCount, &nFaceCount, 
				bIsHairHelmetAlphaTest && bHairHelmet, bRenderShadow );
		}
		if( pRetVertexCount )
			*pRetVertexCount += nVertexCount;
		if( pRetFaceCount )
			*pRetFaceCount += nFaceCount;
	}

	m_pEffectAnim->Render(fAlpha);

	// 如果有发型
	if( 0 && pAvatar->HasHairStyle() )
	{
		// 得到发型
		CAvatarHairStyle* pHairStyle = pAvatar->GetHairStyle();
		// 得到hairpart的部件
		CAvatar::Component* pHair = m_pAvatar->GetComponent(eKeyAll_Hair);
		if( pHair )
		{
			for( int nMesh = 0; nMesh < CAvatarHairStyle::eMaxPart; nMesh++ )
			{
				CAvatarHairStyle::Mesh* pMesh = pHairStyle->GetMesh( nMesh );
				if( !pMesh )
					continue;
				if( !pMesh->bVisible )
					continue;
				IRenderable* pChunk = pHair->pMex->GetGeometry()->GetChunk( pMesh->nChunk );
				if( !pChunk )
					continue;
			}
		}
	}
	return TRUE;
	unguard;
}

void CPlayerAnim::RenderAvatarShadow( CAvatar* pAvatar, IRenderer* pRenderer)
{
	guardfunc;
	if( !pAvatar )
	{
		assert( false );
		return;
	}

	for( int nComponent = 0; nComponent < pAvatar->GetComponentCount(); nComponent++ )
	{
		CAvatar::Component* pComponent = pAvatar->GetComponent( nComponent );
		if( !pComponent )
			continue;
		BOOL bToolMode = GetMe3dConfig()->m_bToolMode;

		if( !bToolMode )
		{
			if(nComponent == eKeyAll_LHandItem)
			{
				pComponent->m_bLeftHand = TRUE;
			}
			else
			{
				pComponent->m_bLeftHand = FALSE;
			}
		}

		if( pComponent->IsAttachment() )
		{
			if( pComponent->IsCanSee() )
				for( int nAnim = 0; nAnim < CAvatar::eMaxPartAnim; nAnim++ )
				{
					MexAnimCtrl* pAnim = pComponent->GetMexAnim( nAnim );
					if( pAnim )
					{
						pAnim->RenderShadow();
					}
				}
		}
		else
		{
			RenderAvatorComponentShadow( pAvatar, pComponent, pRenderer, 0, false );		
		}
	}
	unguard;
}

void CPlayerAnim::RenderAvatorComponent( CAvatar* pAvatar,
										CAvatar::Component* pComponent,
										IRenderer* pRenderer,
										float fAlpha,
										bool bMustUseAlphaBlend,
										int* pRetVertexCount/*=NULL*/,
										int* pRetFaceCount/*=NULL*/,
										BOOL bIsHairHelmet/*= FALSE*/,
										BOOL bRenderShadow/*=FALSE*/ )
{
	guardfunc;
	//static D3DXMATRIX		matMatrices[64];
	D3DXMATRIX* pBoneMatrices = NULL;
	DWORD dwItemEnableFlag = pAvatar->GetItemFlag();
	pBoneMatrices = (D3DXMATRIX*)m_amatBoneInWorldSpace;

	BOOL bToolMode = GetMe3dConfig()->m_bToolMode;
	BOOL bLeftHand = pComponent->m_bLeftHand;

	//char szBuf[256];
	//_snprintf( szBuf, 256, "size = %d", pComponent->vectorChunk.size() );
	//OutputDebugString( szBuf );

	for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
	{
		IRenderable* pChunk = pComponent->vectorChunk[nChunk];
		if ( !pChunk )
			continue;

		DWORD dwFlag = pComponent->flags[nChunk];
		if( !bToolMode )
		{
			if( bLeftHand )
			{
				if( (dwFlag == CAvatar::eItem_RBack ) )
				{
					continue;
				}
				if( (dwFlag == CAvatar::eItem_RightHand ) )
				{
					continue;
				}
			}
			else
			{
				if( (dwFlag == CAvatar::eItem_LBack ) )
				{
					continue;
				}
				if( (dwFlag == CAvatar::eItem_LeftHand ) )
				{
					continue;
				}
			}
		}


		if( !AvatarComponentTest( bLeftHand, dwFlag, dwItemEnableFlag ) )
			continue;

		pRenderer->SetLayerCount( 1 );
		DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
		pRenderer->SetSurfaceFVF( dwFvf );
		pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
		MtlAnim* pMtlEffect = pComponent->pMtlEffect;
		if ( pMtlEffect != NULL)
		{
			if ( pMtlEffect->m_bHasSpecular )
			{
				pRenderer->SetMtlSpecular( 
					pMtlEffect->m_fSpecularPower,
					1.0f,
					pMtlEffect->m_fSpecularRed,
					pMtlEffect->m_fSpecularGreen,
					pMtlEffect->m_fSpecularBlue );
				pRenderer->EnableSpecular( TRUE );
			}
			if ( pMtlEffect->m_nLayerCount == 2 )
			{
				pRenderer->SetLayerCount( 2 );
				MtlAnim::SSetting setting;

				pMtlEffect->GetSetting( HQ_TimeGetTime(), &setting );
				pRenderer->SetGlobalUOffset( 1, setting.fUOffset );
				pRenderer->SetGlobalVOffset( 1, setting.fVOffset );

				pRenderer->SetTextureId( setting.nTextureId, 1 );
				dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
				pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
				pRenderer->SetSurfaceFVF( dwFvf );
			}
		}

		if ( pComponent->m_nSpecularTexID != -1 )
		{
			pRenderer->SetLayerCount( 2 );
			pRenderer->SetTextureId( pComponent->m_nSpecularTexID, 1 );
			dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
			pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
			pRenderer->EnableSpecular( TRUE );
		}
		pRenderer->SetMaterial( &pComponent->material );

		RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
		if (params != NULL)
		{
			params->pMex = pComponent->pMex;
			params->pMatrices = (float*)pBoneMatrices;
			params->pReplaceableTextureProj = &pComponent->ReplaceableTextureProj;
			params->fAlpha = fAlpha;
			params->bMustUseAlphaBlend = bMustUseAlphaBlend;
			if ( pComponent->m_nSpecularTexID != -1 )
				params->nSpecularTexID = pComponent->m_nSpecularTexID;
			else
				params->nSpecularTexID = m_SpecularTexID;
			params->pShimmerGrayTextureProj = &pComponent->ShimmerGrayTextureProj;
			params->material = &pComponent->material;
			params->nFrameId = m_nFrameId;
			params->stUseHeatShimmerTexId = pComponent->HeatShimmerTexId;

			// added, jiayi, [2009/7/18], add m_dwRenderFlag.
			pChunk->Render( params,
				bIsHairHelmet == TRUE? eAlphaTest | m_dwRenderFlag : m_dwRenderFlag,
				&pComponent->LuminanceTextureProj,
				pRetVertexCount,
				pRetFaceCount);	
		}
	}

	if ( !bRenderShadow )
	{
		CAvatar::EffectContainer* ec = &pComponent->m_EffectContainer;
		BOOL bUseLightTrack = FALSE;
		if ( m_pSeqUpperBody )
		{
			bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();
		}

		for ( int nEffect = 0; nEffect < ec->effects.size(); nEffect++ )
		{
			CAvatar::Effect* pEffect = &ec->effects[nEffect];

			if ( !AvatarComponentTest( bLeftHand, pEffect->dwFlag, dwItemEnableFlag ) )
				continue;

			if ( pEffect->part )
			{
				int nLocalTextureId = pEffect->part->GetLocalTextureID();
				int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
				pEffect->part->Render( HQ_TimeGetTime(), nTextureId, fAlpha, false ); 
			}

			DWORD dwCurTime = HQ_TimeGetTime();
			BOOL bUseLightTrack = FALSE;
			if ( m_pSeqUpperBody )
			{
				bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();
			}
			if ( !pEffect->pWeaponBladeRibbon || !pEffect->pWeaponBladeRibbon->IsEnable())
				continue;

			if ( pEffect->ribb && ( bUseLightTrack || dwCurTime - m_dwLightTrackDeadTime < LIGHTTRACKDEADRENDERTIME ) )
			{
				float fAlpha = (float)( LIGHTTRACKDEADRENDERTIME - ( dwCurTime - m_dwLightTrackDeadTime ) )/LIGHTTRACKDEADRENDERTIME;
				if ( m_fLightTrackAlpha < fAlpha )
				{
					m_fLightTrackAlpha += 0.03f ;
				}
				else
				{
					m_fLightTrackAlpha = fAlpha;
				}

				int nLocalTextureId = pEffect->ribb->GetLocalTextureID();
				int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
				pEffect->ribb->Render( NULL, nTextureId, m_fLightTrackAlpha, false, false );
			}
		}
	}
	unguard;
}

void CPlayerAnim::RenderAvatorComponentShadow( CAvatar* pAvatar, CAvatar::Component* pComponent, IRenderer* pRenderer, float fAlpha, bool bMustUseAlphaBlend )
{
	guardfunc;
	D3DXMATRIX* pBoneMatrices = NULL;
	DWORD dwItemEnableFlag = pAvatar->GetItemFlag();
	pBoneMatrices = (D3DXMATRIX*)m_amatBoneInWorldSpace;

	BOOL bToolMode = GetMe3dConfig()->m_bToolMode;
	BOOL bLeftHand = pComponent->m_bLeftHand;

	for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
	{
		IRenderable* pChunk = pComponent->vectorChunk[nChunk];

		//char szBuf[256];
		//_snprintf( szBuf, 256, "%s", pChunk->GetName() );
		//OutputDebugString( szBuf );

		if( !pChunk )
			continue;

		DWORD dwFlag = pComponent->flags[nChunk];
		if( !bToolMode )
		{
			if( bLeftHand )
			{
				if( (dwFlag == CAvatar::eItem_RBack ) )
				{
					continue;
				}
				if( (dwFlag == CAvatar::eItem_RightHand ) )
				{
					continue;
				}
			}
			else
			{
				if( (dwFlag == CAvatar::eItem_LBack ) )
				{
					continue;
				}
				if( (dwFlag == CAvatar::eItem_LeftHand ) )
				{
					continue;
				}
			}
		}

		if( !AvatarComponentTest( bLeftHand, dwFlag, dwItemEnableFlag ) )
			continue;

		{
			pRenderer->SetLayerCount( 1 );
			DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
			pRenderer->SetSurfaceFVF( dwFvf );
			pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );

			pChunk->RenderShadow( pComponent->pMex, (float*)pBoneMatrices, pRenderer, &pComponent->ReplaceableTextureProj, fAlpha, bMustUseAlphaBlend ,m_nFrameId);	
		}
	}
	unguard;
}

//-------------------------------------------------------------------------------------------------------
void CPlayerAnim::ClearBladeRibbon()
{
	if( !m_pAvatar )
		return;
	_ClearBladeRibbon(eKeyAll_RHandItem);
	_ClearBladeRibbon(eKeyAll_LHandItem);
}

void CPlayerAnim::ApplyBladeRibbon()
{
	if( !m_pAvatar )
		return;
	_ApplyBladeRibbon(eKeyAll_RHandItem);
	_ApplyBladeRibbon(eKeyAll_LHandItem);

}

void CPlayerAnim::UpdateLocalBBox()
{
	if( !m_pMex )
		return;

	if( m_pMexCfg )
	{
		if( m_pMexCfg->m_BObj.m_npBBoxWidth.GetNumber() != 0 &&
			m_pMexCfg->m_BObj.m_npBBoxHeight.GetNumber() != 0 )
		{
			int nWidth = m_pMexCfg->m_BObj.m_npBBoxWidth.GetNumber();
			int nLength = m_pMexCfg->m_BObj.m_npBBoxLength.GetNumber();
			int nHeight = m_pMexCfg->m_BObj.m_npBBoxHeight.GetNumber();
			int nLift = m_pMexCfg->m_BObj.m_npBBoxLift.GetNumber();
			m_vMin = Vector( -nWidth/2, -nLength/2, nLift );
			m_vMax = Vector( nWidth/2, nLength/2, nLift+nHeight );
			return;
		}
	}
	m_vMin = *((Mex2*)m_pMex)->GetMin();
	m_vMax = *((Mex2*)m_pMex)->GetMax();
	const float MAX_FLOAT = 10000.0f;

	if( m_pAvatar )
	{
		for( int nComponent = 0; nComponent < m_pAvatar->GetComponentCount(); nComponent++ )
		{
			CAvatar::Component* pComponent = m_pAvatar->GetComponent( nComponent );
			if( !pComponent )
				continue;
			for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
			{
				CMexChunkBase* pBase = (CMexChunkBase*)pComponent->vectorChunk[nChunk];
				m_vMin.x = min(m_vMin.x, pBase->GetMin()->x);
				m_vMin.y = min(m_vMin.y, pBase->GetMin()->y);
				m_vMin.z = min(m_vMin.z, pBase->GetMin()->z);
				m_vMax.x = max(m_vMax.x, pBase->GetMax()->x);
				m_vMax.y = max(m_vMax.y, pBase->GetMax()->y);
				m_vMax.z = max(m_vMax.z, pBase->GetMax()->z);
				// 				vectorChunk.push_back( pChunk );
			}
		}
	}

	if( m_vMin[0] == MAX_FLOAT )
		m_vMin[0] = 20.f;
	if( m_vMin[1] == MAX_FLOAT )
		m_vMin[1] = 20.f;
	if( m_vMin[2] == MAX_FLOAT )
		m_vMin[2] = 20.f;
	if( m_vMax[0] == -MAX_FLOAT )
		m_vMax[0] = -20.f;
	if( m_vMax[1] == -MAX_FLOAT )
		m_vMax[1] = -20.f;
	if( m_vMax[2] == -MAX_FLOAT )
		m_vMax[2] = -20.f;
}

BOOL CPlayerAnim::ChangePartModelById( int nPartId, int nModelId, int nLocalModelId, const char* szSkin, INT nSpecular, short stStar )
{
	guardfunc;
	if( !m_pAvatar )
	{
		assert( false );
		return FALSE;
	}
	return m_pAvatar->ChangeComponent( this, nPartId, nModelId, nLocalModelId, szSkin, nSpecular, stStar );
	unguard;
}


BOOL CPlayerAnim::ApplyPartMtlEffect( int nPartID, int nEffectID )
{
	guardfunc;
	if( !m_pAvatar )
		return FALSE;

	CAvatar::Component* pCompoent = m_pAvatar->GetComponent( nPartID );
	if( !pCompoent )
	{
		assert( false );
		return FALSE;
	}
	if( nEffectID == -1 )
		pCompoent->pMtlEffect = NULL;
	else
		pCompoent->pMtlEffect = GetMtlEffectMgr()->GetEffect( nEffectID );
	return TRUE;
	unguard;
}

void CPlayerAnim::ReleaseLastModel()
{
	guardfunc;
	ReleaseAllLastPartModel();
	//if( m_nModelId == 100000019 )
	//{
	//	int k = 0;
	//}
	GetMexResMgr()->DestroyModel( m_nModelId );
	m_nModelId = -1;
	// 	if( m_nModelId != -1 )
	// 	{
	// 	}
	// 	else
	{
		// 		if( /*m_bIsTerrainModel &&*/ m_pMex )
		// 		{
		// 			m_pMex->Release();
		// 			delete m_pMex;
		// 		}
		// 		if( /*m_bIsTerrainModel &&*/ m_pMexCfg )
		// 		{
		// 			m_pMexCfg->Destroy();
		// 			delete m_pMexCfg;
		// 		}
	}
	m_pMex		= NULL;
	m_pMexCfg	= NULL;
	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}
	m_pAvatarSetting = NULL;

	unguard;

}

void CPlayerAnim::ReleaseLastPartModel( int nPartId )
{
	guardfunc;
	if( m_pAvatar )
	{
		m_pAvatar->ReleaseComponent( nPartId );
	}
	else
	{
		assert( false );
	}
	unguard;

}
void CPlayerAnim::ReleaseAllLastPartModel()
{
	guardfunc;
	if( m_pAvatar )
	{
		m_pAvatar->ReleaseAllComponents();
	}
	unguard;
}


void CPlayerAnim::AttachEffectToComponent( int nComId, int nBoneId, IMex* pMex )
{
	if( !GetAvatar() )
		return ;

	CAvatar::Component* pCom = GetAvatar()->GetComponent( nComId );
	if( !pCom )
		return;

	AttachEffectToComponent( pCom, nBoneId, pMex );
}

void CPlayerAnim::AttachEffectToComponent( const char* pcComName, int nBoneId, IMex* pMex )
{
	if( !GetAvatar() )
		return ;

	CAvatar::Component* pCom = GetAvatar()->GetComponent( pcComName );
	if( !pCom )
		return;

	AttachEffectToComponent( pCom, nBoneId, pMex );
}

void CPlayerAnim::AttachEffectToComponent( CAvatar::Component* pComponent, int nBoneId, IMex* pMex )
{
	if( !pComponent || !pMex || !GetAvatar() )
		return;

	IMexGeometry* pGeometry = pMex->GetGeometry();
	if( pGeometry )
	{
		for( int i = 0; i < pGeometry->GetChunkCount(); i++ )
		{
			IRenderable* pChunk = pGeometry->GetChunk( i );
			if( pChunk == NULL )
				continue;

			const char* pszName = pChunk->GetName();
			if( !pszName )
				continue; 

			pComponent->vectorChunk.push_back( pChunk );
			pComponent->flags.push_back( 0 );
		}
	}

	if( pMex->GetParticleEmitters() )
	{
		int nEmitterCount = pMex->GetParticleEmitters()->GetEmitterCount();
		if( nEmitterCount > 0 )
		{
			for( int i = 0; i < nEmitterCount && i < eMaxParticleEmitter; i++ )
			{
				CAvatar::Effect effect;
				effect.part = pMex->GetParticleEmitters()->GetEmitter(i)->Clone();
				effect.dwFlag = GetAvatar()->GetEffectPart( effect.part->GetBindPartName() );
				if( effect.part )
				{
					effect.part->SetParentBoneID( nBoneId );
					effect.part->SetSrcMex( GetMex() );
				}
				//int nPart = GetEffectPart( )
				pComponent->m_EffectContainer.effects.push_back( effect );
			}
		}
	}
}
int CPlayerAnim::GetPartModelID( int nPart )
{
	guardfunc;
	CAvatar::Component* pComponent = m_pAvatar->GetComponent(nPart);

	if( pComponent )
		return pComponent->nModelID;
	else
		return -1;
	unguard;
}

void CPlayerAnim::CheckWeaponDisplay()
{
	if( GetAvatar() )
	{
		if( GetAvatar()->GetComponent(eKeyAll_RHandItem)
			&& GetAvatar()->GetComponent(eKeyAll_RHandItem)->IsCanSeeAfterBlend() )
		{
			GetAvatar()->GetComponent(eKeyAll_RHandItem)->SetCanSee(TRUE);
			GetAvatar()->GetComponent(eKeyAll_RHandItem)->SetCanSeeAfterBlend(FALSE);
		}
		if( GetAvatar()->GetComponent(eKeyAll_LHandItem) 
			&& GetAvatar()->GetComponent(eKeyAll_LHandItem)->IsCanSeeAfterBlend() )
		{
			GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSee(TRUE);
			GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSeeAfterBlend(FALSE);
		}
	}
}

bool CPlayerAnim::UpdateComponents( DWORD dwTime, MeMatrix* pMatrix )
{
	if( !MexAnimCtrl::UpdateComponents( dwTime, pMatrix ) )
		return false;
	if( m_pAvatar )
		UpdateAvatar( dwTime, (float*)&m_matModel, m_pAvatar );

	m_bUpdateComponents = TRUE;
	return true;
}
#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 1
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

extern int g_MainThreadId;

BOOL CPlayerAnim::_ChangeModel( IMex* pMex, MexCfg* pMexCfg ,const char* pszSkin )
{
	guardfunc;
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime() ;
	DWORD ThreadId = GetCurrentThreadId();
#endif

	if( pMex  == NULL )
		return FALSE;
	if( pMex->GetSkeleton() == NULL )
		return FALSE;
	if( pMexCfg == NULL )
		return FALSE;

	SetMex( pMex, pMexCfg ,pszSkin);
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(g_MainThreadId == ThreadId  && time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nMexAnimCtrlChangeModel_SetMex:%d Thread:%d\n", time_cost,ThreadId );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime() ;
#endif
	int nNumBone = pMex->GetSkeleton()->GetBoneCount();

	if( m_amatBoneInWorldSpace )
	{
		delete[] m_amatBoneInWorldSpace;
		m_amatBoneInWorldSpace = NULL;
		m_matSrcBones = NULL;
		m_amatBoneInModelSpace = NULL;
	}

	m_amatBoneInWorldSpace = MeNew MeMatrix[nNumBone*3];
	m_amatBoneInModelSpace = &m_amatBoneInWorldSpace[nNumBone];
	m_matSrcBones = &m_amatBoneInWorldSpace[nNumBone*2];
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(g_MainThreadId == ThreadId && time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nMexAnimCtrlChangeModel_New:%d Thread:%d\n", time_cost ,ThreadId);
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime() ;
#endif
	IMexBone* pBone = pMex->GetSkeleton()->GetBone(0);
	if( pBone == NULL )
		return FALSE;
	m_nFrameCount = pBone->GetFrameCount();
	//if( /*nNumBone == 1 &&*/ m_nFrameCount == 1 )
	if( nNumBone == 1 && 2 == m_nFrameCount)
	{
		m_bAni = FALSE;
	}
	else
	{
		m_bAni = TRUE;
	}
	MexCfgSequence* pIdleSeq = pMexCfg->FindIdleSequence();

	if( pBone )
	{
		if( pBone->HasKeyFrame() )
			m_bCanBlending = TRUE;
		else
			m_bCanBlending = FALSE;
	}
	else
	{
		m_bCanBlending = FALSE;
	}

	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel);
	if( m_bCanBlending && bNewKeyFrameFormat )
	{
		if( m_pKeyTimeOfBoneMatrices )
		{
			delete[] m_pKeyTimeOfBoneMatrices;
			m_pKeyTimeOfBoneMatrices = NULL;
		}
		if( m_amatBoneMatricesFromKeyTime )
		{
			delete[] m_amatBoneMatricesFromKeyTime;
			m_amatBoneMatricesFromKeyTime = NULL;
		}

		m_pKeyTimeOfBoneMatrices = new int[nNumBone];
		for(int i=0; i<nNumBone; ++i)
		{
			m_pKeyTimeOfBoneMatrices[i] = -1;
		}
		m_amatBoneMatricesFromKeyTime = MeNew MeMatrix[nNumBone];
	}

	if( m_bNeedInitUpperBodyAndLowerBody )
	{
		InitUpperBodyAndLowerBody();
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(g_MainThreadId == ThreadId && time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nMexAnimCtrlChangeModel_InitUpperBodyAndLowerBody:%d Thread:%d\n", time_cost ,ThreadId);
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime() ;
#endif

	if( m_bUpperBodyAndLowerBodyMode )
	{
		for(int i=0; i<nNumBone; i++)
		{
			BlendTransQuatsData kBlendData;
			kBlendData.kLastBlendTrans = Vector(0,0,0);
			kBlendData.kLastBlendQuats = Quaternion(0,0,0,0);
			m_vctBlendTransQuats.push_back(kBlendData);
		}
		if( m_bCanBlending && bNewKeyFrameFormat )
		{
			if( m_pTargetKeyTimeOfBoneMatrices )
			{
				delete[] m_pTargetKeyTimeOfBoneMatrices;
				m_pTargetKeyTimeOfBoneMatrices = NULL;
			}
			if( m_amatBoneMatricesTargetKeyTime )
			{
				delete[] m_amatBoneMatricesTargetKeyTime;
				m_amatBoneMatricesTargetKeyTime = NULL;
			}

			m_pTargetKeyTimeOfBoneMatrices = new int[nNumBone];
			for(int i=0; i<nNumBone; ++i)
			{
				m_pTargetKeyTimeOfBoneMatrices[i] = -1;
			}
			m_amatBoneMatricesTargetKeyTime = MeNew MeMatrix[nNumBone];
		}
	}

	if( pIdleSeq )
	{
		PlayAnimByName( pIdleSeq->m_spAnimName.GetString(), 0 );
		m_TmpSequence.m_npStartFrameId.SetNumber( pIdleSeq->m_npStartFrameId.GetNumber() );
		m_TmpSequence.m_npEndFrameId.SetNumber( pIdleSeq->m_npEndFrameId.GetNumber() );
		m_TmpSequence.m_spAnimName.SetString( "idle" );
		m_TmpSequence.m_npHasLightTrack.SetNumber( pIdleSeq->m_npHasLightTrack.GetNumber() );
	}
	else
	{
		PlayAnim( 0, m_nFrameCount - 1, 0 );
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(g_MainThreadId == ThreadId && time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nMexAnimCtrlChangeModel_PlayAnim:%d Thread:%d\n", time_cost ,ThreadId);
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime() ;
#endif

	UpdateLocalBBox();
	if( m_pAvatar )
	{
		m_pAvatar->BindAttachments( this );
	}
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(g_MainThreadId == ThreadId && time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nMexAnimCtrlChangeModel_BindAttachments:%d Thread:%d\n", time_cost ,ThreadId);
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime() ;
#endif

	return TRUE;
	unguard;
}

void CPlayerAnim::_ApplyBladeRibbon(eKeyAllPart eValue)
{
	CAvatar::Component* pRightHandItem = 
		m_pAvatar->GetComponent(eValue);
	if( pRightHandItem )	
	{
		int nNumEffect = pRightHandItem->m_EffectContainer.effects.size();
		for( int nEffect = 0; nEffect < nNumEffect; nEffect++ )
		{
			CAvatar::Effect& effect = pRightHandItem->m_EffectContainer.effects[nEffect];
			if( !effect.pWeaponBladeRibbon )
				continue;
			int nNumFrame = m_nEndFrameId-m_nStartFrameId+1;
			effect.pWeaponBladeRibbon->Create( nNumFrame );
			effect.pWeaponBladeRibbon->Enable( TRUE );
			effect.pWeaponBladeRibbon->m_dwStartTime = HQ_TimeGetTime();
			effect.pWeaponBladeRibbon->m_dwLife = nNumFrame*ONEFRAMEINTERVAL;
			if( effect.ribb )
				effect.ribb->Reset();
		}
	}
}

void CPlayerAnim::_ClearBladeRibbon(eKeyAllPart eValue)
{
	CAvatar::Component* pRightHandItem = 
		m_pAvatar->GetComponent(eValue);
	if( pRightHandItem )	
	{
		int nNumEffect = pRightHandItem->m_EffectContainer.effects.size();
		for( int nEffect = 0; nEffect < nNumEffect; nEffect++ )
		{
			CAvatar::Effect& effect = pRightHandItem->m_EffectContainer.effects[nEffect];
			if( !effect.pWeaponBladeRibbon )
				continue;
			effect.pWeaponBladeRibbon->Enable( FALSE );
		}

	}
}


namespace Equip
{
	CPlayerAnimParam* getCurrentEquipParam()
	{ 
		return _pCurrPlayerAnimParam;
	}

	CPlayerAnim* getCurrentEquipPlayerAnim()
	{ 
		return _pCurrPlayerAnim; 
	}

}
