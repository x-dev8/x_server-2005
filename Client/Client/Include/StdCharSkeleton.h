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
	//	// ͷ��
		Head,			// ͷ��

	//	Ponytail1,
	//	Ponytail11,
	//	Ponytail2,
	//	Ponytail21,		// ��β��

	//	// --------------------------------------
	//	// ���ײ�
	//	Bip01,			// root
	//	Neck,			// ��
	//	Spine,			// �ز�
	//	Pelvis,			// ����
	//	L_Clavicle,		
	//	R_Clavicle,		// ����
	//	L_UpperArm,
	//	R_UpperArm,		// ���
	//	L_Thigh,
	//	R_Thigh,		// ����

	//	Tail,
	//	Tail1,			// �°�
	//	
	//	// --------------------------------------
	//	// ���ײ�
	//	L_ForeArm,
	//	R_ForeArm,		// ǰ��
	//	L_Hand,
	//	R_Hand,			// ��

	//	// --------------------------------------
	//	// Ь��
	//	L_Calf,
	//	R_Calf,			// С��
	//	L_Foot,
	//	R_Foot,			// ��
	//	L_Toe0,
	//	R_Toe0,			// �ż�

	//	// --------------------------------------
	//	// ����
		L_HandItem,
		R_HandItem,		// ����
	//	
		eMaxBone,
	};
	//enum EPartId
	//{
 //       eHairPartMask,		    //ͷ��
 //       eHelmetPartMask,		    //ͷ��
 //       eFacePartMask	,	    //��
 //       eArmourPartMask	,	    //��
 //       eGlovePartMask   ,       //����
 //       eShoePartMask	,	    //Ь��
 //       eRightHandItemPartMask,  //��������
 //       eLeftHandItemPartMask ,  //��������
 //       eBadgeMask			,	//����
 //       eLeftHandShieldPartMask,	//��
 //       eShoulderPartMask	,	//����
 //       eTrousersPartMask	,	//����
 //       //eGemBagMask		,	//����					�����滻Ϊ����		modified by ZhuoMeng.Hu		[9/2/2010]		
	//	eCloakMask			,	//����
 //       eRightRingMask		,	//���ֽ�ָ
 //       //eLeftRing		    //���ֽ�ָ	
 //       erBangleMask		,	//����
 //       eNecklaceMask		,	
 //       eSashMask			,	//����
 //       eHonorMask			,	//ѫ��
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