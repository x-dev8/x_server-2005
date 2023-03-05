#include <assert.h>

#include "Stdcharskeleton.h"
#include "WordParser.h"
#include "FuncPerformanceLog.h"
/*
 *	纸娃娃系统输出流程
 *	注意:纸娃娃是不输出动画信息的
 *	启动
 *	过滤数据，滤掉不必要的网格，动画，材质等等，
 *	弹出菜单:是否生成纸娃娃
 *		是:
 *			弹出骨架预览框，初始化界面，统计错误
 *			弹出菜单:是否可以生成纸娃娃
 *				是:
 *					对骨骼进行排序，生成标准骨骼顺序的骨架
 *					对网格进行排序和分组，生成换装数据
 *				否:返回
 *		否:
 *			生成非纸娃娃角色动画
 */

/*
	[Hair]		
		Head
	[Helmet]	
		Head
	[Face]		
		Head
	[Armour]	
		Bip01	
		Neck	
		Spine	
		Pelvis	
		L_Clavicle	
		R_Clavicle	
		L_UpperArm	
		R_UpperArm	
		L_Thigh	
		R_Thigh	
		Tail Tail1
	[Glove]		
		L_ForeArm	
		R_ForeArm	
		L_Hand	
		R_Hand
	[Shoe]
		L_Calf
		R_Calf
		L_Foot
		R_Foot
		L_Toe0
		R_Toe0
*/


// CStdCharSkeleton g_stdCharSkeleton;
static const char* gs_pszPartNames[eKeyAll_Max];
static const unsigned int gs_uiConfigStringCount = 39;
static const char* gs_pszConfigString[gs_uiConfigStringCount];

//int CStdCharSkeleton::ms_aPartsMasks[eMaxPart];

char* GetPartNames( int nType )
{
	guardfunc;
	if(nType < 0 || nType > eKeyAll_Max)
		return NULL;
	return (char*)gs_pszPartNames[nType];
	unguard;
}

const char** CStdCharSkeleton::GetPartNames()
{
	guardfunc;
	return gs_pszPartNames;
	unguard;
}
CStdCharSkeleton::CStdCharSkeleton()
{
	guardfunc;	
	/*m_pfInitializePartMask = 0;*/
	memset( gs_pszConfigString, 0, sizeof( gs_pszConfigString ) );
	memset( gs_pszPartNames, 0x00, sizeof( gs_pszPartNames ) );
	/*memset( ms_aPartsMasks, 0, sizeof( ms_aPartsMasks ) );*/
	unguard;
}
CStdCharSkeleton::~CStdCharSkeleton()
{
	guardfunc;
	for( int i = 0; i < m_vectorBone.size(); i++ )
	{
		if( m_vectorBone[i] )
		{
			delete m_vectorBone[i];
			m_vectorBone[i] = NULL;
		}
	}
	unguard;
}

void CStdCharSkeleton::Init()
{	
	/*if( m_pfInitializePartMask )
		m_pfInitializePartMask();
	else
		assert( 0 && "initialize function must not be null!!!");*/

	//add by yanli  2010-9-27
	gs_pszPartNames[eKeyAll_Hair]			= "Hair";
	gs_pszPartNames[eKeyAll_Helmet]		= "Helmet";
	gs_pszPartNames[eKeyAll_Face]			= "Face";
	gs_pszPartNames[eKeyAll_Armour]		= "Armour";
	gs_pszPartNames[eKeyAll_Glove]			= "Glove";
	gs_pszPartNames[eKeyAll_Shoe]			= "Shoe";
	gs_pszPartNames[eKeyAll_RHandItem]	= "RightHandItem";
	gs_pszPartNames[eKeyAll_LHandItem]	= "LeftHandItem";
	gs_pszPartNames[eKeyAll_WeaponMinor]	= "WeaponMinor";
	gs_pszPartNames[eKeyAll_Badge]		= "Badge";
	gs_pszPartNames[eKeyAll_Ring1]			= "Ring1";
	gs_pszPartNames[eKeyAll_Ring2]			= "Ring2";
	gs_pszPartNames[eKeyAll_Bangle1]		= "Bangle1";
	gs_pszPartNames[eKeyAll_Bangle2]		= "Bangle2";
	gs_pszPartNames[eKeyAll_Shoulder]    = "Shoulder";
	gs_pszPartNames[eKeyAll_Necklace]    = "Necklace";
	gs_pszPartNames[eKeyAll_Sash]			= "Sash";
	gs_pszPartNames[eKeyAll_LeaderCard]	= "LeaderCard";
	gs_pszPartNames[eKeyAll_Amulet]		= "Amulet";
	gs_pszPartNames[eKeyAll_AecorativeGoods]		= "AecorativeGoods";
	gs_pszPartNames[eKeyAll_AecorativeClothing]		= "AecorativeClothing";
	gs_pszPartNames[eKeyAll_Trousers] = "Trousers";

	BOOL bAllPartHasName = TRUE;
	for( int i = 0; i < eKeyAll_Max; i++ )
	{
		if( gs_pszPartNames[i] == NULL )
		{
			bAllPartHasName = FALSE;
			break;
		}
	}
	assert( bAllPartHasName && "some part has no name" );

	//取代MoreSkeleton.cfg

	gs_pszConfigString[0] = "[Part] Hair";
	gs_pszConfigString[1] = "[Part] Helmet";
	gs_pszConfigString[2] = "[Part] Face";
	gs_pszConfigString[3] = "[Part] Armour";
	gs_pszConfigString[4] = "[Part] Glove";
	gs_pszConfigString[5] = "[Part] Shoe";
	gs_pszConfigString[6] = "[Part] Cape";
	gs_pszConfigString[7] = "[Part] LeftHandItem";
	gs_pszConfigString[8] = "[Part] RightHandItem";
	gs_pszConfigString[9] = "[BoneCount] 29";
	gs_pszConfigString[10] = "[Bone]	Head		[ID]	0	[Part]	Hair";
	gs_pszConfigString[11] = "[Bone]	Ponytail1	[ID]	1	[Part]	Hair";
	gs_pszConfigString[12] = "[Bone]	Ponytail11	[ID]	2	[Part]	Hair";
	gs_pszConfigString[13] = "[Bone]	Ponytail2	[ID]	3	[Part]	Hair";
	gs_pszConfigString[14] = "[Bone]	Ponytail21	[ID]	4	[Part]	Hair";
	gs_pszConfigString[15] = "[Bone]	Bip01		[ID]	5	[Part]	Armour";
	gs_pszConfigString[16] = "[Bone]	Neck		[ID]	6	[Part]	Armour";
	gs_pszConfigString[17] = "[Bone]	Spine		[ID]	7	[Part]	Armour";
	gs_pszConfigString[18] = "[Bone]	Pelvis		[ID]	8	[Part]	Armour";
	gs_pszConfigString[19] = "[Bone]	L_Clavicle	[ID]	9	[Part]	Armour";
	gs_pszConfigString[20] = "[Bone]	R_Clavicle	[ID]	10	[Part]	Armour";
	gs_pszConfigString[21] = "[Bone]	L_UpperArm	[ID]	11	[Part]	Armour";
	gs_pszConfigString[22] = "[Bone]	R_UpperArm	[ID]	12	[Part]	Armour";
	gs_pszConfigString[23] = "[Bone]	L_Thigh		[ID]	13	[Part]	Armour";
	gs_pszConfigString[24] = "[Bone]	R_Thigh		[ID]	14	[Part]	Armour";
	gs_pszConfigString[25] = "[Bone]	Tail		[ID]	15	[Part]	Armour";
	gs_pszConfigString[26] = "[Bone]	Tail1		[ID]	16	[Part]	Armour";
	gs_pszConfigString[27] = "[Bone]	L_ForeArm	[ID]	17	[Part]	Glove";
	gs_pszConfigString[28] = "[Bone]	R_ForeArm	[ID]	18	[Part]	Glove";
	gs_pszConfigString[29] = "[Bone]	L_Hand		[ID]	19	[Part]	Glove";
	gs_pszConfigString[30] = "[Bone]	R_Hand		[ID]	20	[Part]	Glove";
	gs_pszConfigString[31] = "[Bone]	L_Calf		[ID]	21	[Part]	Shoe";
	gs_pszConfigString[32] = "[Bone]	R_Calf		[ID]	22	[Part]	Shoe";
	gs_pszConfigString[33] = "[Bone]	L_Foot		[ID]	23	[Part]	Shoe";
	gs_pszConfigString[34] = "[Bone]	R_Foot		[ID]	24	[Part]	Shoe";
	gs_pszConfigString[35] = "[Bone]	L_Toe0		[ID]	25	[Part]	Shoe";
	gs_pszConfigString[36] = "[Bone]	R_Toe0		[ID]	26	[Part]	Shoe";
	gs_pszConfigString[37] = "[Bone]	L_HandItem	[ID]	27	[Part]	LeftHandItem";
	gs_pszConfigString[38] = "[Bone]	R_HandItem	[ID]	28	[Part]	RightHandItem";
}

const char* CStdCharSkeleton::GetBoneNameById( int nBoneId )
{
	guardfunc;
	if( nBoneId < 0 || nBoneId >= m_vectorBone.size() )
		return "";
	return m_vectorBone[nBoneId]->szName;
	unguard;
}
CStdCharSkeleton::Bone*	CStdCharSkeleton::GetBone( int i )
{ 
	guardfunc;
	if( i < 0 || i >= m_vectorBone.size() )
		return NULL;
	return m_vectorBone[i]; 
	unguard;
}
CStdCharSkeleton::Bone*	CStdCharSkeleton::GetBoneByName( const char* pszBoneName )
{
	guardfunc;
	return (Bone*)m_BoneFinder.GetDstByName( pszBoneName );
	unguard;
}
int CStdCharSkeleton::GetBoneIdByName( const char* pszBonename )
{
	guardfunc;
	Bone* pBone = (Bone*)m_BoneFinder.GetDstByName( pszBonename );
	if( pBone )
		return pBone->nId;
	return -1;
	unguard;
}
int CStdCharSkeleton::GetPartIdByPartName( const char* pszPartName )
{
	guardfunc;
	for( int nPart = 0; nPart < eKeyAll_Max; nPart++ )
	{
		if( stricmp( pszPartName, gs_pszPartNames[nPart] ) == 0 )
			return nPart;
	}
	return -1;
	unguard;
}
int CStdCharSkeleton::GetPartIdByBoneName( const char* pszBoneName )
{
	guardfunc;
	Bone* pBone = GetBoneByName( pszBoneName );
	if( pBone )
	{
		return pBone->nPartId;
	}
	assert( false );
	return -1;
	unguard;
}
BOOL CStdCharSkeleton::CanCreate( char* pszBonenames[], int nBoneCount )
{
	guardfunc;
	if( nBoneCount != m_vectorBone.size() )
		return FALSE;

	std::vector<BOOL> vectorFound;
	vectorFound.reserve( nBoneCount );
	vectorFound.resize( nBoneCount );

	memset( &vectorFound[0], 0x00, sizeof( BOOL )*nBoneCount );
	
	for( int i = 0; i < m_vectorBone.size(); i++ )
	{
		int nBoneId = GetBoneIdByName( pszBonenames[i] );
		// not found
		if( nBoneId == -1 )
			return FALSE;
		// has same name
		if( vectorFound[nBoneId] )
			return FALSE;
		
		vectorFound[nBoneId] = TRUE;
	}
	return TRUE;
	unguard;
}
//const char* CStdCharSkeleton::GetPartName( int nPartId )
//{
//	guardfunc;
//	if( nPartId < 0 || nPartId >= eKeyAll_Max )
//		return NULL;
//	return gs_pszPartNames[nPartId];
//	unguard;
//}
CStdCharSkeleton::Part* CStdCharSkeleton::GetPart( const char* pszPartName )
{
	guardfunc;
	for( int i = 0; i < eKeyAll_Max; i++ )
	{
		if( stricmp( pszPartName, gs_pszPartNames[i] ) == 0 )
		{
			return &m_parts[i];
		}
	}
	return NULL;
	unguard;
}
BOOL CStdCharSkeleton::LoadCfg()
{
	guardfunc;
	//while( fgets( buf, 1024, fp ) )
	for( unsigned int ui = 0 ; ui < gs_uiConfigStringCount ; ++ ui )
	{
		WordParser words;
		if( words.Parse( gs_pszConfigString[ui] ) == 0 )continue;
		if( words.Compare( 0, "[Part]" ) )
		{
			Part* pPart = GetPart( words.GetWord( 1 ) );
			
			if( !pPart )
			{
				assert( "std char skeleton load cfg error, invalid part" );
			}
			else
			{
				pPart->nPartId = GetPartIdByPartName( words.GetWord(1) );
				if( pPart->bEnable )
				{
					assert( "std char skeleton load cfg error, part duplicate" );
				}
				else
				{
					pPart->bEnable = TRUE;
				}
			}
		}
		else if( words.Compare( 0, "[BoneCount]" ) )
		{
            assert( m_vectorBone.size() == 0 && "std char skeleton load cfg error, bone count duplicate" );
			assert( words.IsNumber( 1 ) && "std char skeleton load cfg error, bone count is string" );

			int nBoneCount = atoi( words.GetWord( 1 ) );
			assert( nBoneCount > 0 && "std char skeleton load cfg error, bone count must 0" );
			m_vectorBone.resize( nBoneCount );
			m_vectorBone.reserve( nBoneCount );
			for( int i = 0; i < nBoneCount; i++ )
				m_vectorBone[i] = NULL;
		}
		// [Bone]	Ponytail21	[ID]	4	[Part]	Hair
		else if( words.Compare( 0, "[Bone]" ) )
		{
			const char* pszBoneName = words.GetWord( 1 );
			if( !words.IsNumber( 3 ) )
			{
				assert( false && "std char skeleton load cfg error, bone id must be number" );
				continue;
			}
			
			int nBoneId = atoi( words.GetWord( 3 ) );
			if( nBoneId < 0 || nBoneId >= m_vectorBone.size() )
			{
				assert( false && nBoneId < m_vectorBone.size() && "std char skeleton load cfg error, bone id out of range" );
				continue;
			}
			
			const char* pszPart = words.GetWord( 5 );
			Part* pPart = GetPart( pszPart );
			if( !pPart )
			{
				assert( false && "std char skeleton load cfg error, unknown part" );
				continue;
			}
			if( !pPart->bEnable )
			{
				assert( false && "std char skeleton load cfg error, bone's part is disable" );
				continue;
			}
			//pPart->nPartId = GetPartIdByPartName( pszPart );
			if( pPart->nPartId == -1 )
			{
				assert( false && "std char skeleton load cfg error, part name is invalid" );
				continue;
			}
			if( m_vectorBone[nBoneId] )
			{
				assert( false && "std char skeleton load cfg error, bone duplicate" );
				continue;
			}

			Bone* bone = MeNew Bone;
			bone->nId = nBoneId;
			bone->nPartId = pPart->nPartId;
			strcpy( bone->szName, pszBoneName );
			m_vectorBone[nBoneId] = bone;
			
			pPart->vectorBone.push_back( bone );
			m_BoneFinder.Register( pszBoneName, bone );
		}
	}

	return TRUE;
	unguard;
}
int CStdCharSkeleton::GetBoneCount()
{ 
	guardfunc;
	return m_vectorBone.size(); 
	unguard;
}

//void CStdCharSkeleton::SetInitializeFunction( CStdCharSkeleton::funcInitializePartMask pf )
//{
//	m_pfInitializePartMask = pf;
//}

//int CStdCharSkeleton::GetPartMask( EPartId ePart )
//{
//	if( ePart >= 0 && ePart < eMaxPart )
//		return ms_aPartsMasks[ePart];
//
//	return -1;
//}
//void CStdCharSkeleton::SetPartMask( EPartId ePart, int nValue )
//{
//	if( ePart < 0 || ePart >= eMaxPart )
//		return;
//
//	ms_aPartsMasks[ePart] = nValue;	
//}