#include "itemdetail.h"
#include <assert.h>
#include "cfgItemDesc.h"
#include "slkReader\slkReader.h"
#include "Helper.h"
#include "ArabicNightsAction.h"
#include "..\common\XSanguo.h"
#include "../Common/Official.h"
#include "../Common/SystemConfig.h"
#include "ErrorLog.h"
#include "../Common/FuncPerformanceLog.h"

extern CfgItemDesc g_CfgItemDesc;
//extern void (*g_pfnSlkLoadingCallBack)( const char* pszString );
extern void OutputSlkLoadingMessage( char* pszString, ... );
//using namespace std;

enum
{
	ITEMNO_HPMAX = -1,
};
static char* (g_szWeaponAttackRate[]) = 
{
	"slow"				//����
		,"normal"			//��ͨ
		,"fast"				//����
};


static char* (g_szWeaponType[]) = 
{
		"unarm"							//ͽ��������ȭ��
		,"blade"						//��
		,"sword"						//��
		,"twohand-blade"				//˫�ֵ�
		,"twohand-sword"				//˫�ֽ�
		,"magicstick"					//ħ����
		,"dagger"						//ذ��
		,"bow"							//��
		,"twohand-magicstick"			//˫����
		,"shield"						//��

};

const char* GetWeaponTypeNamed(int nIdx)
{
	return g_szWeaponType[nIdx];
}
static char* (g_szItemType[CItemDetail::ITEMTYPE_MAX]) =
{
	"restore"
		,"weapon"
		,"armour"
		,"skill"
		,"other"
		,"stone"
		,"status"
		,"action"
		,"reel"
		,"material"
		,"medal"
		,"task"
		//	,"magicitem"
		,"tool"
		//	,"jewelry"
		,"gem"
		,"createitemrule"
		,"card"
		,"crystal"
};

static const int g_iItemTypeSize = sizeof(g_szItemType)/sizeof(char*);
enum enumFile
{
	file_item = 0
	,file_restore
	,file_weapon
	,file_armour
	,file_skill
	,file_other
	,file_stone
	,file_status
	,file_action
	,file_reel
	,file_material
	,file_medal
	,file_task
	//	,file_magicitem
	,file_tool
	//	,file_JEWELRY
	,file_gem
	,file_createrule
	,file_card
	,file_crystal
	,file_max
};

static char *(g_szItemFile[file_max])=
{
	"item.slk"
		,"restore.slk"
		,"weapon.slk"
		,"armour.slk"
		,"skill.slk"
		,""				//Ŀǰ����Ҫ�ļ��洢(other)
		,"stone.slk"
		,"status.slk"
		,"gameaction.slk"
		,"reel.slk"
		,""				//Ŀǰ����Ҫ�ļ��洢(material)
		,""				//Ŀǰ����Ҫ�ļ��洢(medal)
		,""				//Ŀǰ����Ҫ�ļ��洢(task)
		//	,"magicitem.slk"
		,""				//Ŀǰ����Ҫ�ļ��洢(tool)
		//	,""
		,"gem.slk"
		,"createitemrule.slk"
		,""				// card
		//,"profession.slk"
		,"crystal.slk"
};

static char *(g_szCanEquip[])=
{
	"hair"
		,"helmet"			//ͷ��
		,"face"
		,"armour"			//����
		,"glove"			//����
		,"shoe"				//Ь��
		,"Cape"
	//	,"handitem",			//2�ֶ�����
		,"lhanditem"			//������Ʒ
		,"rhanditem"    		//������Ʒ
		,"headwear"				//ͷ��
		,"HandShiedld"			//��
		,"Shoulder"				//����
		,"Trousers"				//����
		,"accouterment"    		//	
		,"rring"					//���ֽ�ָ
		,"lring"					//���ֽ�ָ
		,"bangle"				//���� 
};

static char*(g_szTargetString[])=
{
	"target_no"				//��Ŀ��
		,"target_myself"		//�� ��ֻ���Լ���
		,"target_friend"		//���ѣ�ֻ�Զ��ѣ�	
		,"target_normalplayer"	//��ͨ��ң�������Ұ����Լ����˵��ˣ�
		,"target_enemy"			//���ˣ�ֻ�ܶԵ��ˣ�
		,"target_dead"			//����Ŀ�ֻ꣨�����ˣ�
		,"target_herb"			//Ŀ���ҩ
		,"target_mine"			//Ŀ���
		,"target_all"			//�����˶�����
};

static char*(g_szEffectCenter[])=
{
	"center_no"			//û�г�����Ч��
		,"center_metotarget"//���Լ�������
		,"center_me"		//���Լ���ǰλ��Ϊ����
		,"center_target"	//��Ŀ��λ��Ϊ����
};

//װ������
char*(g_szEquipType[ CItemDetail::const_iEquipTypeNum ])=
{
	"helmet" //ͷ��
		,"armour" //����
		,"glove"  //����
		,"shoe"   //Ь��
		,"cape"	  //����
		,"weapon" //����
		,"shield" //����
		,"accounterment"//��Ʒ
		,"ring"			//��ָ
		,"bangel"		//����
		,"Shoulder"				//����
		,"Trousers"		//����
};

char* (g_szSkillType[])=
{
	"skilltype_action",		//�ڶ������Ž��������ģ�����
		"skilltype_magic_hit",	//�ڶ������Ž�������㣬�ͷų�һ���������
		"skilltype_magic_npc",	//�ڶ������Ž������ͷų�һ������npc
		"skilltype_passive"		//��������
};

char* (g_szSkillGeneralType[])=
{
	"generaltype_action",	//����Action����
		"generaltype_magic",	//����Magic����
		"generaltype_sequence",	//�������м���
		"generaltype_passive"	//��������
};

class IObjest111
{
public:
	IObjest111()
	{
		int i = 0;
		i++;
	}
protected:
private:
};
static IObjest111 g_Object1;
//char* (g_szAiType[ ])=
//{
//	"aitype_initiative",
//		"aitype_passive",
//		"aitype_frightened",
//		"aitype_angry",
//		"aitype_thief"
//		"aitype_leader",
//};

char* (g_szMonsterType[])=
{
	"monstertype_normal",
		"monstertype_leader",
		"monstertype_boss",
		"monstertype_god",
		"monstertype_herb",
		"monstertype_mine",
};

//char* (g_szMonsterHateEnemy[])=
//{
//	"enemy_beginner",//������
//		"enemy_knight",	//��ʿ
//		"enemy_knifeman",//����
//		"enemy_swordMan",//����
//		"enemy_rabbi",	//��ʦ
//		"enemy_churchman",//��ʦ
//		"enemy_wizard,"  //��ʦ
//		"enemy_all",	//������
//};
//char* (g_szMonsterFightBackEnemy[])=
//{
//	"fb_hpmin",	//hp��С
//		"fb_hpmax",	//hp���
//		"fb_hurtmin",//�˺�����С
//		"fb_hurtmax",//�˺������
//		"fb_levelmin",//�ȼ���С
//		"fb_levelmax",//�ȼ����
//		"fb_profession_beginner",//������
//		"fb_profession_knight",	//��ʿ
//		"fb_profession_knifeman",//����
//		"fb_profession_swordMan",//����
//		"fb_profession_rabbi", //��ʦ
//		"fb_profession_churchman",//��ʦ
//		"fb_profession_wizard"//��ʦ
//};

char* (g_szBalanceType[])=
{
	"balancetype_none",					//û���κν���
		"balancetype_phydamage",			//�����˺�����
		"balancetype_magdamage",			//ħ���˺�����
		"balancetype_restorehp",			//��HP����
		"balancetype_relive",				//�������
		"balancetype_addextrahp",			//˲����Ѫ
		//"balancetype_restoretp",			//��TP����
		"balancetype_damagemp",				// �˺�MP
		"balancetype_dispelbadstatus"		//��ɢ����״̬
		"balancetype_Frost",
		"balancetype_Blaze",
		"balancetype_Thunder",
		"balancetype_Poison",

};

//״̬�Ľ��㹫ʽ����
char* (g_szStatusBalanceType[])=
{
	"balance_status_type_none",
		"balance_status_type_1",
		"balance_status_type_life_stolen",//͵Ѫ
		"balance_status_type_life_trans",	//��Ѫ
		"balance_status_type_manaburn"
};

//��������
char* (g_szActionType[])=
{
	"baseaction"
		,"communityaction"
		,"socialaction"
};

//�Ա�
char* (g_szSexType[])=
{
	"male"
		,"female"
};

//ְҵ
char* (g_szProfessionType[])=
{

	//����
	"robber"
		//��ʿ
		,"warrior"
		//����
		,"archer"
		//��ʿ
		,"Taoist"

		//��ʦ
		,"wizard"
};

//char* (g_szProfessionType[])=
//{
//	//��ʿ��ѧ��
//	"Warrior_Beginner"
//	//��ʦ��ѧ��
//	,"Wizard_Beginner"
//	//�й���ʿ
//	,"China_Warrior"
//	//�й���ʦ
//	,"China_Wizard"
//	//�ж���ʿ
//	,"MiddleEast_Warrior"
//	//�ж���ʦ
//	,"MiddleEast_Wizard"
//	//������ʿ
//	,"West_Warrior"
//	//������ʦ
//	,"West_Wizard"
//};

//����������
char* (g_szSkillPower[])=
{
	"zhaoshi"
		,"bishaji"
		,"magic"
};

//ʩ��Ŀ�꣬�ͻ���
//����Ƕ��Լ�ʹ�ã���ô����Ҫ���ָ�򹥻�Ŀ�ֱ꣬��ȡ��ɫ��ǰλ��
//�������Ҫ����ʹ�ã���ô����Ŀ������ǽ�ɫ
//�����λ��ʹ�ã���ô����Ŀ��Ϊλ�ã����ָ���ɫ��ȡ��ɫλ�ã�
char* (g_szSkillCastTarget[])=
{
	"casttarget_me"
		,"casttarget_friendlive"
		,"casttarget_enemylive"
		,"casttarget_live"
		,"casttarget_pos"
		,"casttarget_friendcorpse"
		,"casttarget_enemycorpse"
		,"casttarget_corpse"
		,"casttarget_herb"						//�Բ�ҩΪĿ��
		,"casttarget_mine"						//�Կ�ΪĿ��
};

int GetIDByConstString( const char* szString,char**pszString,int iHowManyString )
{
	strlwr( const_cast<char*>(szString) );
	int iLoop;
	int iBlack = ' ';

	//ȥ��ǰ��ͺ���Ŀո�
	char *szFind = NULL;
	while( szFind = (char*)strchr( szString,iBlack ) )
	{
		if( szString == szFind )
			szString ++;
		else
			break;
	}

	szFind = 0;
	//int iLen;
	while( szFind = (char*)strrchr( szString,iBlack  ) )
	{	
		if( 1 == strlen( szFind ) )
		{
			szFind[0] = 0;
		}
		else
			break;
	}

	//
	for( iLoop = 0 ; iLoop < iHowManyString ; iLoop ++)
	{
		if( 0 == strcmp( szString,pszString[iLoop] ) )
			return iLoop;
	}
	return -1;
}


CItemDetail theItemDetail;

BYTE* CItemDetail::GetAddrPointer( DWORD dwAddr )
{
	if( m_pbyGlobalBuffer == NULL )
	{
		assert( false );
		return NULL;
	}
	if( dwAddr >= m_dwGlobalBufferSize ||
		dwAddr >= m_dwGlobalBufferUsed )
	{
		assert( false );
		return NULL;
	}
	return &m_pbyGlobalBuffer[dwAddr];
}
const char* CItemDetail::GetString( DWORD dwAddr )
{
	BYTE* pbyPointer = GetAddrPointer(dwAddr);
	if( pbyPointer )
		return (const char*)pbyPointer;
	//return (const char*)GetAddrPointer(dwAddr);
	return "";
}
BOOL CItemDetail::AllocStringCopy( const char* pszString )
{
	if( !pszString )
	{
		assert( false );
		return FALSE;
	}
	int nLength = strlen( pszString )+1;
	DWORD dwAddr = AllocGlobalBuffer( nLength );
	HelperFunc::SafeNCpy( (char*)GetAddrPointer(dwAddr), pszString, nLength );
	return dwAddr;
}
const char* CItemDetail::SItemCommon::GetItemName()
{
	return theItemDetail.GetString( dwItemNameAddr );
}
const char* CItemDetail::SItemCommon::GetItemDesc()
{
	return theItemDetail.GetString( dwItemDescAddr );
}
const char* CItemDetail::SItemCommon::GetIconInItemBag()
{
	return theItemDetail.GetString( dwIconInItemBagAddr );
}
const char* CItemDetail::SItemCommon::GetIconTile()
{
	return theItemDetail.GetString( dwIconTileAddr );
}
const char* CItemDetail::SProfession::GetName()
{
	return theItemDetail.GetString( dwNameAddr );
}
const char* CItemDetail::SMonster::GetName()
{
	return theItemDetail.GetString( dwNameAddr );
}
const char* CItemDetail::SMonster::GetCreatureSound()
{
	return theItemDetail.GetString( dwCreatureSoundAddr );
}
const char* CItemDetail::SMonster::GetSkin()
{
	return theItemDetail.GetString( dwSkinAddr );
}
const char* CItemDetail::SCharModulus::GetProfessionName()
{
	return theItemDetail.GetString( dwProfessionNameAddr );
}
const char* CItemDetail::SItemSkill::GetSkillName()
{
	return theItemDetail.GetString( dwSkillNameAddr );
}
CItemDetail::CItemDetail(void):
m_pbyGlobalBuffer(NULL),
m_dwGlobalBufferSize(0),
m_dwGlobalBufferUsed(0)
{
	//m_bClientMode = true;
	//m_pMemAllocer = &g_normalAllocer;
	m_vectorItem.resize(10000);
	m_vectorGems[ gem_ruby ].resize( 5 );
	m_vectorGems[ gem_beryl ].resize( 5 );
	m_vectorGems[ gem_sapphire ].resize( 5 );
	m_vectorGems[ gem_diamond ].resize( 5 );

	//AllocGlobalBuffer( 1024 );
	m_dwGlobalBufferSize = 1024*1024*2;
	m_pbyGlobalBuffer = new BYTE[m_dwGlobalBufferSize];
	memset( m_pbyGlobalBuffer, 0x00, m_dwGlobalBufferSize );

	m_ItemFinder.SupportSameNameElement( TRUE );

	//LoadBinFile( "c:\\1.slkbin" );
}

CItemDetail::~CItemDetail(void)
{
	int iLoop;

	//for(int i=0;i<(int)m_BakupItem.size();i++)
	//{
	//	delete m_BakupItem[i];
	//}
	if( m_pbyGlobalBuffer )
	{
		delete[] m_pbyGlobalBuffer;
		m_pbyGlobalBuffer = NULL;
	}

	////vectoritem
	//for( iLoop=0; iLoop< (int)m_vectorItem.size( ); iLoop++ )
	//{
	//	if( m_vectorItem[iLoop] != NULL )
	//	{
	//		Safe_DeleteArray(m_vectorItem[iLoop]->pszIconInItembag);
	//		Safe_DeleteArray(m_vectorItem[iLoop]->pszItemDesc);
	//		Safe_DeleteArray(m_vectorItem[iLoop]->pszItemName);
	//		delete m_vectorItem[iLoop];
	//		m_vectorItem[iLoop] = NULL;
	//	}
	//}

	//charmodulus
	for( iLoop=0; iLoop<(int)m_vecCharModulus.size( ); iLoop++ )
	{
		if( m_vecCharModulus[iLoop] != NULL )
		{
			//delete m_vecCharModulus[iLoop];
			m_vecCharModulus[iLoop] = NULL;
		}
	}

	//StoneSkill
	//iterStoneSkill stoneskill;
	//stoneskill = m_mapStoneSkill.begin( );
	//for( ;stoneskill!=m_mapStoneSkill.end( ); stoneskill++ )
	//{
	//	if( stoneskill->second != NULL )
	//	{
	//		delete stoneskill->second;
	//		stoneskill->second = NULL;
	//	}
	//}

	//SkillToSkill
	//iterSkillToSkill skilltoskill;
	//skilltoskill = m_mapSkillToSkill.begin( );
	//for( ;skilltoskill!=m_mapSkillToSkill.end( ); skilltoskill++ )
	//{
	//	if( skilltoskill->second != NULL )
	//	{
	//		delete skilltoskill->second;
	//		skilltoskill->second = NULL;
	//	}
	//}

	//Produce Item
	//for( iLoop=0; iLoop<(int)m_vecProduceItem.size( ); iLoop++ )
	//{
	//	if( m_vecProduceItem[iLoop] != NULL )
	//	{
	//		delete m_vecProduceItem[iLoop];
	//		m_vecProduceItem[iLoop] = NULL;
	//	}
	//}
}

DWORD CItemDetail::AllocGlobalBuffer( DWORD dwBufferSize )
{
	if( m_dwGlobalBufferUsed+dwBufferSize > m_dwGlobalBufferSize )
	{
		assert( false );
		return 0;
	}
	//while( m_dwGlobalBufferUsed+dwBufferSize > m_dwGlobalBufferSize )
	//{
	//	if( m_dwGlobalBufferSize == 0 )
	//	{
	//		m_dwGlobalBufferSize = dwBufferSize;
	//	}
	//	else
	//	{
	//		m_dwGlobalBufferSize *= 2;
	//	}
	//	BYTE* pbyBuffer = new  BYTE[m_dwGlobalBufferSize]; 
	//	memset( pbyBuffer, 0x00, m_dwGlobalBufferSize );
	//	if( m_dwGlobalBufferUsed > 0 )
	//		memcpy( pbyBuffer, m_pbyGlobalBuffer, m_dwGlobalBufferUsed );
	//	if( m_pbyGlobalBuffer )
	//	{
	//		delete[] m_pbyGlobalBuffer;
	//		m_pbyGlobalBuffer = NULL;
	//	}
	//	m_pbyGlobalBuffer = pbyBuffer;
	//}
	BYTE* pbyAllocBuffer = &m_pbyGlobalBuffer[m_dwGlobalBufferUsed];
	DWORD dwAddr = m_dwGlobalBufferUsed;
	m_dwGlobalBufferUsed += dwBufferSize;
	return dwAddr;
	//return pbyAllocBuffer;
}
BYTE* CItemDetail::AllocItem( DWORD dwItemType, DWORD dwSize )
{
	if( dwSize == 0 )
	{
		assert( false );
	}
	DWORD dwAddr = AllocGlobalBuffer( dwSize );
	return GetAddrPointer( dwAddr );
	//return AllocGlobalBuffer( dwSize );
	//return NULL;
}
//////����˺�
//int RandAtt(int Max,int Min)
//{	
//	return  Min + rand()% Max;
//}

bool CItemDetail::GetIntField( CSlkReader *pReader,int iCol,int &iValue )
{
	return pReader->GetIntField( iCol,iValue );
}

bool CItemDetail::GetFloatField( CSlkReader *pReader, int iCol, float &fValue )
{
	return pReader->GetFloatField( iCol, fValue );
}

bool CItemDetail::GetStringField( CSlkReader *pReader,int iCol,std::string& strRetValue )
{	
	return pReader->GetStringField( iCol,strRetValue);
}

static int GetItemTypeByString( const char *szStrItemType )
{
	int i;
	for( i = 0 ; i < g_iItemTypeSize ; i ++ )
	{
		if( 0 != strstr( szStrItemType,g_szItemType[i] ) )
			return i;	  
	}
	return -1;
}


bool CItemDetail::LoadFromSlk( const char *szPath,FILE */*fpOutput*/ )
{
	//int b = 0;
	//int k = 1024/b;
	//char s[2565];
	//sprintf( s, "%ld", k );
	//MessageBox( NULL, s, s, MB_OK );
	//HelperFunc::SetOutputFile( fpOutput );

	static bool bOnlyOne = false;	
	assert( !bOnlyOne );
	//����Ŀǰ���Ϊֻ�ܱ�����һ��
	if( bOnlyOne )
		return false;
	bOnlyOne = true;

	char szFile[ MAX_PATH ];

	//////ְҵ�Ķ���
	//sprintf( szFile, "%s\\%s", szPath, "Profession.slk" );
	//OutputSlkLoadingMessage( "����%s\r\n",szFile );
	//if( !LoadProfession( szFile ) )
	//{
	//	//�������� slk
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	GetErrorLog()->logString( "�Ҳ���profession.slk" );
	//	return false;
	//}

	////���������
	//sprintf( szFile,"%s\\%s",szPath,"monster.slk" );
	//OutputSlkLoadingMessage( "����%s\r\n",szFile );
	//if( !LoadMonster( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	GetErrorLog()->logString( "�Ҳ���monster.slk" );
	//	return false;
	//}	

	//sprintf( szFile,"%s\\%s",szPath,"WorldMapCfg.slk" );
	//OutputSlkLoadingMessage( "����%s\r\n",szFile );
	//if( !m_WorldMapConfig.Load( szFile ) )
	//	return false;
	//// <

	////��ɫϵ��
	//sprintf( szFile,"%s\\%s",szPath,"charmodulus.slk");
	//OutputSlkLoadingMessage( "����%s\r\n",szFile );
	//if( !LoadCharModulus( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	GetErrorLog()->logString( "�Ҳ���charmodulus.slk" );
	//	return false;
	//}	

	/*sprintf( szFile,"%s\\%s",szPath,"WeaponRand.slk");
	OutputSlkLoadingMessage( "����%s\r\n",szFile );
	if( !LoadWeaponRand( szFile ) )
	{
		OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
		GetErrorLog()->logString( "�Ҳ���WeaponRand.slk" );
		return false;
	}	

	sprintf( szFile,"%s\\%s",szPath,"ArmourRand.slk");
	OutputSlkLoadingMessage( "����%s\r\n",szFile );
	if( !LoadArmourRand( szFile ) )
	{
		OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
		GetErrorLog()->logString( "�Ҳ���ArmourRand.slk" );
		return false;
	}	*/

	//sprintf( szFile,"%s\\%s",szPath,"UpBaseAttr.slk");
	//OutputSlkLoadingMessage( "����%s\r\n",szFile );
	//if( !LoadBaseAttr( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	GetErrorLog()->logString( "�Ҳ���UpBaseAttr.slk" );
	//	return false;
	//}

	/*sprintf( szFile,"%s\\%s",szPath,"Formulamodulus.slk");
	if( !LoadFormulamodulus( szFile ) )
	{
	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	assert( false && "�Ҳ���Formulamodulus.slk" );
	return false;
	}*/

	////��ʯ�뼼�ܵĶ�Ӧ
	//sprintf( szFile, "%s\\%s", szPath, "stoneskill.slk" );
	//if( !LoadStoneSkill( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	assert( false && "�Ҳ���stoneskill.slk" );
	//	return false;
	//}

	////��ʽƬ���뼼�ܵĶ�Ӧ
	//sprintf( szFile, "%s\\%s", szPath, "skilltoskill.slk" );
	//if( !LoadSkillToSkill( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	assert( false && "�Ҳ���skilltoskill.slk" );
	//	return false;
	//}

	////��Ʒ����,ԭ�����Ʒ�Ķ�Ӧ��ϵ
	//sprintf( szFile, "%s\\%s", szPath, "produceitem.slk" );
	//if( !LoadProduceItem( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "�Ҳ���%s\r\n",szFile );
	//	assert( false && "�Ҳ���produceitem.slk" );
	//	return false;
	//}

	CSlkReader slkItem;
	CSlkReader slkChildItem[ g_iItemTypeSize ];
	//	
	sprintf( szFile,"%s\\%s",szPath,g_szItemFile[0] );	
	OutputSlkLoadingMessage( "����%s\r\n",szFile );
	if( !slkItem.ReadFromFile( szFile ) )
	{		
		OutputSlkLoadingMessage( "�Ҳ���%s�ļ�\r\n",szFile);
		GetErrorLog()->logString( "�Ҳ���item.slk" );
		return false;
	}

	int i;
	//no "other" file Now
	for( i = 0 ; i < g_iItemTypeSize; i ++ )
	{
		sprintf( szFile,"%s\\%s",szPath,g_szItemFile[ i+file_restore ] );
		OutputSlkLoadingMessage( "���ڷ���%s\r\n",szFile );
		if( !slkChildItem[ i ].ReadFromFile( szFile ) )
		{
			if( file_other != i + file_restore )
			{
				OutputSlkLoadingMessage( "�Ҳ���%s�ļ�\r\n",szFile);
				//assert( false && "ĳ���ֱ�ȱ��.��status.slk,skill.slk��" );
			}
			//return false;
		}
	}



	SItemCommon common;

	i = 2;
	int iCol;	
	char *pszItemType = 0;
	int iValue;
	int iRet;
	std::string strTemp;
	static int line = 0;

	DWORD dwTime = HQ_TimeGetTime();
	int d = 0;

	while ( CSlkReader::ret_readover != ( iRet = slkItem.GotoNextLine( i++ ) ) ) 
	{
		line ++;

		//if( HQ_TimeGetTime()-dwTime > 200 )
		//{
		//	dwTime = HQ_TimeGetTime();
		//	switch( d++%4 )
		//	{
		//	case 0:
		//		OutputSlkLoadingMessage("/L����");
		//		break;
		//	case 1:
		//		OutputSlkLoadingMessage("/L����.");
		//		break;
		//	case 2:
		//		OutputSlkLoadingMessage("/L����..");
		//		break;
		//	case 3:
		//		OutputSlkLoadingMessage("/L����...");
		//		break;
		//	}
		//}





		if( CSlkReader::ret_nothisline == iRet )
		{
			continue;
		}
		common.cItemClass = ItemClass_Normal;
		//��ƷID
		iCol = 1;
		if( !slkItem.GetIntFieldByName( "id", iValue ) )
		{
			//assert( false );
			continue;
		}
		common.ustItemID = iValue;

		std::string strItemName;

		//if( !slkItem.GetStringFieldByName( "��Ʒ����", common.szItemName ) )
		if( !slkItem.GetStringFieldByName( "��Ʒ����", strItemName ) )
		{
			assert( FALSE );
			continue;
		}
		OutputSlkLoadingMessage( "������Ʒ(%s)", strItemName.c_str() );
		//common.dwItemNameAddr = AllocGlobalBuffer( strItemName.length()+1 );
		common.dwItemNameAddr = AllocStringCopy( strItemName.c_str() );
		//HelperFunc::SafeNCpy( )

		std::string strItemDesc;
		//if( !slkItem.GetStringFieldByName( "��Ʒ����", common.szItemDesc ) )
		if( !slkItem.GetStringFieldByName( "��Ʒ����", strItemDesc ) )
		{
		}
		common.dwItemDescAddr = AllocStringCopy( strItemDesc.c_str() );

		if( !slkItem.GetIntFieldByName( "��ֵ", iValue  ) )
		{
			assert( false );
			continue;
		}
		common.dwCost = iValue;

		if( !slkItem.GetIntFieldByName( "Ʒ�ʵȼ�", iValue  ) )
		{
			assert( false );
			continue;
		}

		common.ustLevel = iValue;

		if( !slkItem.GetStringFieldByName( "��Ʒ����", strTemp ) )
		{
			assert( FALSE );
			continue;
		}
		common.ucItemType = GetItemTypeByString( strTemp.c_str());

		if( common.ucItemType < 0 || common.ucItemType >=ITEMTYPE_MAX )
		{
			OutputSlkLoadingMessage( "\tError:��Ʒ���ʹ���\r\n"  );		
			char string[256];
			sprintf(string, "item.slk(%d)���Ҳ�����Ʒ����",common.ustItemID);
			MessageBox( NULL, string, "warning", MB_OK );
			continue;
		}

		std::string strIconInItemBag;
		//if( !slkItem.GetStringFieldByName( "��Ʒ����Ʒ���е�icon�ļ�", common.szIconInItembag ) )
		if( !slkItem.GetStringFieldByName( "��Ʒ����Ʒ���е�icon�ļ�", strIconInItemBag ) )
		{
			assert( FALSE );
			continue;
		}
		common.dwIconInItemBagAddr = AllocStringCopy( strIconInItemBag.c_str() );

		//		if( !slkItem.GetStringFieldByName( "��Ʒ����Ʒ���е�iconռλ�ļ�", common.szIconTile ) )
		//		{
		////			common.szIconTile = "UI\\ICON\\Null.tga";
		//			assert( FALSE );
		//			continue;
		//		}

		if( !slkItem.GetIntFieldByName( "��Ʒ���ڵ���ʱ��ģ���ļ�id", iValue ) )
		{
			assert( false );
			continue;
		}
		common.ustModelIDOverGround = iValue;

		if( slkItem.GetIntFieldByName( "ϡ�ж�", iValue ) )
		{
			common.cItemClass = iValue;
		}
		else
		{
			common.cItemClass = ItemClass_Normal;
		}
		if( slkItem.GetIntFieldByName( "�Ƿ���ʾװ����Ч", iValue ) )
		{
			iValue = 1;
		}
		common.bShowEquipEffect = iValue>0?true:false;
		// �ɷ��ƶ�
		iCol++;
		// �ɷ���
		iCol++;
		// �ɷ�����
		iCol++;
		// �ɷ���
		iCol++;
		// �ɷ�����
		iCol++;
		// ռ���
		//if ( !GetIntField(&slkItem, iCol++, iValue) )
		//{
		//	iValue = 1;
		//}
		if( !slkItem.GetIntFieldByName( "ռ���", iValue ) )
		{
			iValue = 1;
		}
		common.ustItemW = iValue;
		// ռ����
		//if ( !GetIntField(&slkItem, iCol++, iValue) )
		//{
		//	iValue = 1;
		//}
		if( !slkItem.GetIntFieldByName( "ռ���", iValue ) )
		{
			iValue = 1;
		}
		common.ustItemH = iValue;
		//
		//GetStringField( &slkItem,iCol++,common.szIconTile );

		switch( common.ucItemType) 
		{
		case ITEMTYPE_RESTORE:
			AddRestoreItem( &slkChildItem[common.ucItemType] ,common);
			break;
		case ITEMTYPE_WEAPON:
			AddWeaponItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_ARMOUR:
			AddArmourItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_SKILL:
			AddSkillItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_OTHER:
			AddOtherItem(&slkChildItem[common.ucItemType],common);
			break;
			//case ITEMTYPE_STONE:
			//	AddStoneItem(&slkChildItem[common.ucItemType],common);
			//	break;
		case ITEMTYPE_STATUS:
			AddStatusItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_ACTION:
			AddActionItem(&slkChildItem[common.ucItemType],common);
			break;
			/*case ITEMTYPE_REEL:
			AddReelItem(&slkChildItem[common.ucItemType],common);
			break;*/
			//case ITEMTYPE_MAGICITEM:	//ħ������
			//	AddMagicItem(&slkChildItem[common.ucItemType],common);
			//	break;
		case ITEMTYPE_MATERIAL:		//ԭ��
			AddMaterialItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_TASK:			//����
			AddTaskItem(&slkChildItem[common.ucItemType],common);
			break;
			//case ITEMTYPE_TOOL:			//����
			//	AddToolItem(&slkChildItem[common.ucItemType],common);
			//	break;
		case ITEMTYPE_GEM:			//Gem
			AddGemItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_CREATEITEMRULE://createitemrule
			AddCreateItemRule(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_CARD:
			AddCardItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_CRYSTAL:
			AddCrystalItem(&slkChildItem[common.ucItemType],common);
			break;

		default:
			assert(false);
			break;
		}
	}

	//OutputSlkLoadingMessage( "\t��ʼ�������ܵ�����ʹ������\r\n\r\n" );
	//ProduceAllSkillConditions( &slkChildItem[ file_skill - file_restore ] );


	return true;
}
BOOL CItemDetail::LoadBinFile( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( !fp )
		return FALSE;	
	int nItemCount = 0;
	fread( &nItemCount, sizeof(int), 1, fp );
	std::vector<int> vectorItemAddr;
	if( nItemCount > 0 )
	{
		vectorItemAddr.reserve( nItemCount );
		vectorItemAddr.resize( nItemCount );
		fread( &vectorItemAddr[0], sizeof(int)*nItemCount, 1, fp );
	}
	fread( &m_dwGlobalBufferUsed, sizeof(DWORD), 1, fp );
	if( m_dwGlobalBufferUsed > 0 )
	{
		fread( m_pbyGlobalBuffer, m_dwGlobalBufferUsed*sizeof(BYTE), 1, fp );
	}
	fclose( fp );
	for( int nItem = 0; nItem < nItemCount; nItem++ )
	{
		SItemCommon* pItem = (SItemCommon*)&m_pbyGlobalBuffer[vectorItemAddr[nItem]];
		AddToMap( pItem );
		switch(pItem->ucItemType)
		{
		case ITEMTYPE_SKILL:
			{//����һ��������ƷID��������ŵ� ת��
				SItemSkill *pSkill = NULL;
				pSkill = (SItemSkill *)pItem;
				m_mapSkillNO.insert( mapSkillNO::value_type( pSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
				m_vecSkill.push_back( pSkill->ustItemID );

				//����һ����������(ֻ�޷���)
				if(pSkill->ustItemID>=StartID_Skill)
				{
					int index;
					index = pSkill->ustItemID-StartID_Skill;
					m_SkillArray[index][pSkill->ustLevel] = *pSkill;

					if(pSkill->ustLevel==1)
					{
						m_SkillArray[index][ 0 ] = *pSkill;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	return TRUE;
}
BOOL CItemDetail::SaveBinFile( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "wb" );
	if( !fp )
		return FALSE;	
	int nItemCount = m_BakupItem.size();
	fwrite( &nItemCount, sizeof(int), 1, fp );

	DWORD dwTime = HQ_TimeGetTime();
	int d = 0;
	for( int nItem = 0; nItem < nItemCount; nItem++ )
	{
		//if( HQ_TimeGetTime()-dwTime > 200 )
		//{
		//	dwTime = HQ_TimeGetTime();
		//	switch( d++%4 )
		//	{
		//	case 0:
		//		OutputSlkLoadingMessage("/Lд��");
		//		break;
		//	case 1:
		//		OutputSlkLoadingMessage("/Lд��.");
		//		break;
		//	case 2:
		//		OutputSlkLoadingMessage("/Lд��..");
		//		break;
		//	case 3:
		//		OutputSlkLoadingMessage("/Lд��...");
		//		break;
		//	}
		//}
		SItemCommon* pItem = m_BakupItem[nItem];

		DWORD dwOffset = (BYTE*)pItem-m_pbyGlobalBuffer;
		fwrite( &dwOffset, sizeof(DWORD), 1, fp );
	}
	fwrite( &m_dwGlobalBufferUsed, sizeof(int), 1, fp );
	if( m_dwGlobalBufferUsed > 0 )	
		fwrite( m_pbyGlobalBuffer, m_dwGlobalBufferUsed, 1, fp );

	if( fp )
		fclose( fp );
	return TRUE;
}
void CItemDetail::AddToMap( SItemCommon *pItem )
{
	/*if( pItem->ustItemID == 1300 )
	{
		int k = 0;
	}
	char s[256];
	sprintf( s, "item %ld\n", pItem->ustItemID );
	OutputDebugString( s );*/
	//����Item�ĵȼ�������Ӧ��Vector��
	if( pItem->ustLevel>=1 && pItem->ustLevel<100 )
		m_vectorLevelItem[pItem->ustLevel].push_back(pItem);

	m_BakupItem.push_back(pItem);
	//��¼ItemID
	m_vectorItemID.push_back( pItem->ustItemID );

	if( pItem->ustItemID >= m_vectorItem.size() )
	{
		m_vectorItem.resize( pItem->ustItemID + pItem->ustItemID );		
	}
	m_vectorItem[pItem->ustItemID] = pItem;	

	m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem );
	//if( m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem ) == 0 )
	//{
	//	OutputSlkLoadingMessage( "�������� %s", (char*)GetAddrPointer(pItem->dwItemNameAddr) );
	//}
	//m_ItemFinder
	//mapNameItem::iterator itName;
	//itName = m_mapNameItem.find( std::string(pItem->szItemName.c_str()) );
	//itName = m_mapNameItem.find( std::string((char*)GetAddrPointer(pItem->dwItemNameAddr)) );
	//if( itName == m_mapNameItem.end() )
	//{
	//	//m_mapNameItem.insert( mapNameItem::value_type(pItem->szItemName.c_str(),pItem ) );
	//	m_mapNameItem.insert( mapNameItem::value_type((char*)GetAddrPointer(pItem->dwItemNameAddr),pItem ) );
	//}
}

#define CopyCommon( pItemDest,common ) *(SItemCommon*)pItemDest = common;


void CItemDetail::AddRestoreItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemRestore *pItemRestore;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Restore || common.ustItemID > EndID_Restore )
	{
		GetErrorLog()->logString( "restore id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:restore.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "restore.slk���Ҳ�����ƷID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:restore.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "restore.slk���Ҳ�����ƷID" );
		return;
	}
	//pItemRestore = new SItemRestore;//m_pMemAllocer->Malloc( sizeof(SItemRestore) );
	pItemRestore = (SItemRestore*)AllocItem( 0, sizeof( SItemRestore ) );
	if( !pItemRestore )
	{
		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
		GetErrorLog()->logString( "restore.slk���ڴ�������" );
		return;	
	}
	CopyCommon( pItemRestore,common );

	bool bReadSucc = true;
	int iCol;

	int iValue;
	while( bReadSucc )
	{
		bReadSucc = false;
		iCol = 3;

		//����HP
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ��addHP���ݴ�!\r\n" );
			GetErrorLog()->logString( "restore.slk��addHP���ݴ�" );
			continue;
		}
		pItemRestore->dwAddHP = iValue;
		iCol ++;

		//����MP
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ��addMP���ݴ�!\r\n" );
			GetErrorLog()->logString( "restore.slk��addMP���ݴ�" );
			continue;
		}
		pItemRestore->dwAddMP = iValue;
		iCol ++;
		iCol++;
		////����TP
		//if( !GetIntField( pReader, iCol, iValue ) )
		//{
		//	OutputSlkLoadingMessage( "\tError:ҩƷ��addTP���ݴ�!\r\n" );
		//	assert( false && "restore.slk��addTP���ݴ�" );
		//	continue;
		//}
		//pItemRestore->dwAddTP = iValue;
		//iCol++;

		//����Exp
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ��addExp���ݴ�!\r\n" );
			GetErrorLog()->logString( "restore.slk��addExp���ݴ�" );
			continue;
		}
		pItemRestore->dwAddExp = iValue;
		iCol ++;

		//����hunger
		/*if( !GetIntField( pReader,iCol,iValue ) )
		{
		OutputSlkLoadingMessage( "\tError:ҩƷ������hunger���ݴ�!\r\n" );
		assert( false && "restore.slk������hunger���ݴ�" );
		continue;
		}
		pItemRestore->stSubHunger = iValue;*/
		iCol ++;

		//���״̬	
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ�Ľ��״̬û��!\r\n" );
			pItemRestore->ustSubStatusID = ArabicNights::ErrorUnsignedShortID;
		}
		else
		{
			pItemRestore->ustSubStatusID = iValue;
		}
		iCol++;

		//����״̬	
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ�ĵ���״̬û��!\r\n" );
			pItemRestore->ustAddStatusID = ArabicNights::ErrorUnsignedShortID;
		}
		else
		{
			pItemRestore->ustAddStatusID = iValue;
		}
		iCol++;

		//����״̬�ȼ�
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ҩƷ�ĵ���״̬�ȼ�Ĭ��1!\r\n" );
			pItemRestore->ustAddStatusLevel = 1;
		}
		else
		{
			pItemRestore->ustAddStatusLevel = iValue;
		}
		iCol++;

		// ColdDown
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:ColdDownĬ��0!\r\n" );
			pItemRestore->dwColdDown = 0;
		}
		else
		{
			pItemRestore->dwColdDown = iValue;
		}
		iCol++;

		// type
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:typeĬ��0!\r\n" );
			pItemRestore->stColdDownType = -1;
		}
		else
		{
			pItemRestore->stColdDownType = iValue;
		}
		iCol++;

		bReadSucc = true;
		break;
	}
	if( bReadSucc )
	{
		//��ӵ���Ʒ������
		AddToMap( pItemRestore );
	}
	else
	{
		//		delete( pItemRestore );
	}
}
//
//void CItemDetail::AddStoneItem( CSlkReader *pReader,SItemCommon &common )
//{
//	SSymbolStone *pItemStone;
//	int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );
//
//	//ID���Ƿ��ڹ涨��Χ��
//	if( common.ustItemID < StartID_Stone || common.ustItemID > EndID_Stone )
//	{
//		assert( false && "stone id error" );
//		return;
//	}
//
//	if( -1 == iLineNo )
//	{
//		OutputSlkLoadingMessage( "\tError:stone.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
//		assert( false && "stone.slk���Ҳ���ID" );
//		return;
//	}
//
//	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
//	{
//		OutputSlkLoadingMessage( "\tError:stone.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
//		assert( false && "stone.slk���Ҳ���ID" );
//		return;
//	}
//
//	//pItemStone = new SSymbolStone;//m_pMemAllocer->Malloc( sizeof(SSymbolStone) );
//	pItemStone = (SSymbolStone*)AllocItem( 0, sizeof(SSymbolStone) );
//
//	if(!pItemStone)
//	{
//		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//		assert( false && "stone.slk���ڴ�������" );
//		return;	
//	}
//
//	CopyCommon( pItemStone, common );
//
//	//
//	bool bReadSucc = true;
//	int iCol;
//
//	int iValue;
//	while( bReadSucc )
//	{
//		bReadSucc = false;
//		iCol = 3;
//
//		//��ʯ����
//		if( !GetIntField( pReader, iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\tError:��ʯ�������ݴ�!\r\n" );
//			assert( false && "��ʯ�������ݴ�" );
//			continue;
//		}
//		pItemStone->stStoneType = iValue;
//		iCol++;
//
//		bReadSucc = true;
//		break;
//	}
//
//	if( bReadSucc )
//	{
//		//��ӵ���ʯ������
//		AddToMap( pItemStone );
//	}
//	else
//	{
//		delete( pItemStone );
//	}
//}

void SetCanEquipByString( char *szDst,const char *pszEquip )
{
	strlwr( const_cast<char*>(pszEquip) );
	for( int i = 0 ; i < ArabicNights::VISUAL_MAX ; i ++ )
	{
		if( 0 == _stricmp(pszEquip,g_szCanEquip[i] ))
		{
			//	if( NULL != strstr( pszEquip,g_szCanEquip[i] ) )

			szDst[i] = 1;
		}
		else
		{
			szDst[i] = 0;
		}
	}
}

//װ�ض�������
void CItemDetail::AddActionItem( CSlkReader *pReader, SItemCommon &common )
{
	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_GameAction || common.ustItemID > EndID_GameAction )
	{
		GetErrorLog()->logString( "game action id error" );
		return;
	}


	SItemAction *pItemAction;
	int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );


	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:gameaction.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gameaction.slk���Ҳ�����ƷID" );
		return;
	}

	if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:gameaction.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gameaction.slk���Ҳ�����ƷID" );
		return;
	}

	//pItemAction = new SItemAction;//m_pMemAllocer->Malloc( sizeof(SItemAction) );
	pItemAction = (SItemAction*)AllocItem( 0, sizeof( SItemAction ) );
	if(!pItemAction)
	{
		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
		GetErrorLog()->logString( "gameaction.slk���ڴ�������" );
		return;	
	}
	CopyCommon( pItemAction, common );
	//
	bool bReadSucc = true;
	int iCol;
	int iValue;
	std::string strTemp;

	while( bReadSucc )
	{
		bReadSucc = false;
		iCol = 3;

		//����ID
		if(!GetStringField( pReader, iCol, strTemp ))
		{
			OutputSlkLoadingMessage( "Error:��ȡ�������Ƴ���!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ�������Ƴ���!" );
			continue;
		}
		pItemAction->ustActionID = ArabicNightsAction::FindActionIdByName( strTemp.c_str() );

		iCol++;

		//�������ͣ�0���������� 1����Ⱥ���� 2���罻������
		if(!GetStringField(pReader,iCol,strTemp))
		{
			OutputSlkLoadingMessage( "Error:��ȡ�������ͳ���!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ�������ͳ���!" );
			continue;
		}
		pItemAction->stType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
			g_szActionType, sizeof(g_szActionType)/sizeof(char *) );

		if( -1 == pItemAction->stType )
		{
			OutputSlkLoadingMessage( "Error:��ȡ�������ͳ���!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ�������ͳ���!" );
			continue;
		}
		iCol ++;

		//���β���ʱ��
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:��ȡ���β���ʱ�����!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ���β���ʱ�����!" );
			continue;
		}
		pItemAction->stSinglePlayTime = iValue;
		iCol++;

		//��������ʱ��
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:��ȡ��������ʱ�����!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ��������ʱ�����!" );
			continue;
		}
		pItemAction->stLastingPlayTime = iValue;
		iCol++;

		//�������һ֡
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:��ȡ�������һ֡����!\r\n" );
			GetErrorLog()->logString( "gameaction.slk�ж�ȡ�������һ֡����!" );
			continue;
		}
		if(0 == iValue)
			pItemAction->bLastFrameRemain = false;//????
		else 
			pItemAction->bLastFrameRemain = true;
		iCol++;

		bReadSucc = true;
		break;
	}

	if( bReadSucc )
	{

		//��ӵ���ʯ������
		AddToMap( pItemAction );
	}
	else
	{
		//		delete( pItemAction );
	}
}

//װ�ؾ�������
/*void CItemDetail::AddReelItem( CSlkReader *pReader, SItemCommon &common )
{
SItemReel *pItemReel;
int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );

//ID���Ƿ��ڹ涨��Χ��
if( (common.ustItemID < StartID_SkillReel || common.ustItemID > EndID_SkillReel)
&&  (common.ustItemID < StartID_StoneReel || common.ustItemID > EndID_StoneReel) )
{
assert( false && "reel id error" );
return;
}

if( -1==iLineNo )
{
OutputSlkLoadingMessage( "\tError:reel.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
assert( false && "reel.slk���Ҳ�����ƷID" );
return;
}

if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
{
OutputSlkLoadingMessage( "\tError:reel.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
assert( false && "reel.slk���Ҳ�����ƷID" );
return;
}

pItemReel = new SItemReel;//m_pMemAllocer->Malloc( sizeof(SItemReel) );
if(!pItemReel)
{
OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
assert( false && "reel.slk���ڴ�������" );
return;	
}

CopyCommon( pItemReel, common );

//
bool bReadSucc = true;
int iCol;
int iValue;
std::string strTemp;

while( bReadSucc )
{
bReadSucc = false;
iCol = 3;

//���ӷ�ʯID
if(!GetIntField(pReader,iCol,iValue))
{
OutputSlkLoadingMessage( "Error:��ȡ���ӷ�ʯIDĬ��0xffff!\r\n" );
pItemReel->ustAddStoneID = 0xffff;
}
else
{
pItemReel->ustAddStoneID = iValue;
}
iCol++;

//���Ӽ���ID
if(!GetIntField(pReader,iCol,iValue))
{
OutputSlkLoadingMessage( "Error:��ȡ���Ӽ���IDĬ��0xffff!\r\n" );
pItemReel->ustAddSkillID = 0xffff;
}
else
{
pItemReel->ustAddSkillID = iValue;
}
iCol++;

//����ʹ��ְҵ������
int iLoop;
for( iLoop=0; iLoop < ArabicNights::Profession_Max; iLoop++ )
{
pItemReel->abEquipProfessionReq[iLoop] = false;
}

if( !pReader->GetStringField( iCol,strTemp) )
{
OutputSlkLoadingMessage( "\tWarning:����û�ж�������ȱʡ����ְҵ������ʹ��\r\n" );		
for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
pItemReel->abEquipProfessionReq[ iLoop ] = true;
}
else
{
//���ö��ְҵ
char *szSpn = " ,";
char *szStr;
int iEquip;
szStr = strtok( const_cast<char*>(strTemp.c_str()),szSpn );
while( szStr )
{
iEquip = HelperFunc::GetIDByConstString( szStr
,g_szProfessionType,sizeof( g_szProfessionType )/sizeof(char*) );
if( iEquip >= 0 && iEquip < ArabicNights::Profession_Max )
{
pItemReel->abEquipProfessionReq[ iEquip ] = true;
}
szStr = strtok( NULL,szSpn );
}			

}
//
iCol ++;

bReadSucc = true;
break;
}

if( bReadSucc )
{
//��ӵ����������
AddToMap( pItemReel );
}
else
{
delete( pItemReel );
}
}*/

////��ħ������
//void CItemDetail::AddMagicItem( CSlkReader *pReader, SItemCommon &common )
//{
//	SItemMagic *pItemMagic;
//	int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );
//
//	if( -1==iLineNo )
//	{
//		OutputSlkLoadingMessage( "\tError:magicitem.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
//		assert( false && "magicitem.slk���Ҳ�����ƷID" );
//		return;
//	}
//
//	if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
//	{
//		OutputSlkLoadingMessage( "\tError:magicitem.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
//		assert( false && "magicitem.slk���Ҳ�����ƷID" );
//		return; 
//	}
//
//	pItemMagic = new SItemMagic;
//	if(!pItemMagic)
//	{
//		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//		assert( false && "magicitem.slk���ڴ�������" );
//		return;	
//	}
//	
//	CopyCommon( pItemMagic, common );
//
////
//	bool bReadSucc = true;
//	int iCol;
//	int iValue;
//
//	while( bReadSucc )
//	{
//		bReadSucc = false;
//		iCol = 3;
//
//		//�����ɹ�����
//		if(!GetIntField(pReader,iCol,iValue))
//		{
//			OutputSlkLoadingMessage( "Error:��ȡ�ɹ�����Ĭ��1000!\r\n" );
//			pItemMagic->ustSuccessRate = 1000;
//		}
//		else
//		{
//			pItemMagic->ustSuccessRate = iValue;
//		}
//		iCol++;
//
//		//�������Եľ�����ֵ
//		int i;
//		for( i=0;i<7;i++ )
//		{
//			//�����Եĳ��ָ���
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ�ɹ�����Ĭ��0!\r\n" );
//				pItemMagic->ustSpecialRate[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustSpecialRate[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ����������Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ����������СֵĬ��0!\r\n" );
//				pItemMagic->ustAffectWeaponMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectWeaponMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ�����������ֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ�����������ֵĬ��0!\r\n" );
//				pItemMagic->ustAffectWeaponMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectWeaponMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ���·���Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ���·���СֵĬ��0!\r\n" );
//				pItemMagic->ustAffectClothesMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectClothesMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ���·����ֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ���·����ֵĬ��0!\r\n" );
//				pItemMagic->ustAffectClothesMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectClothesMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ��Ь����Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ��Ь����СֵĬ��0!\r\n" );
//				pItemMagic->ustAffectShoeMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectShoeMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ��Ь�����ֵ	
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ��Ь�����ֵĬ��0!\r\n" );
//				pItemMagic->ustAffectShoeMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectShoeMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ��������Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ��������СֵĬ��0!\r\n" );
//				pItemMagic->ustAffectGloveMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectGloveMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ���������ֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ���������ֵĬ��0!\r\n" );
//				pItemMagic->ustAffectGloveMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectGloveMax[ i ] = iValue;
//			}
//			iCol++;
//
//
//			//������Ӱ��ͷ����Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ��ͷ����СֵĬ��0!\r\n" );
//				pItemMagic->ustHeadPieceMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustHeadPieceMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ��ͷ�����ֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ��ͷ�����ֵĬ��0!\r\n" );
//				pItemMagic->ustHeadPieceMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustHeadPieceMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ����Ʒ��Сֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ����Ʒ��СֵĬ��0!\r\n" );
//				pItemMagic->ustDecorateMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustDecorateMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//������Ӱ����Ʒ���ֵ
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:��ȡ����Ӱ����Ʒ���ֵĬ��0!\r\n" );
//				pItemMagic->ustDecorateMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustDecorateMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//��ȡ���һ������ʱ,�����ٶ�һ��״̬����,����ר�����������.
//			if(i==6)
//			{
//				//Ӱ��״̬�ļ���
//				if(!GetIntField(pReader,iCol,iValue))
//				{
//					OutputSlkLoadingMessage( "Error:��ȡӰ��״̬�ļ���Ĭ��0!\r\n" );
//					pItemMagic->ustStatusRate = 0;
//				}
//				else
//				{
//					pItemMagic->ustStatusRate = iValue;
//				}
//				iCol++;
//			}
//		}
//
//		bReadSucc = true;
//		break;
//	}
//
//	if( bReadSucc )
//	{
//		//��ӵ�ħ�����϶�����
//		AddToMap( pItemMagic );
//	}
//	else
//	{
//		delete( pItemMagic );
//	}
//}

//��ԭ��
void CItemDetail::AddMaterialItem( CSlkReader *pReader, SItemCommon &common )
{
	SCreateMaterial *pItemMaterial = 0;
	//int iValue;
	//int iCol;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Material || common.ustItemID > EndID_Material )
	{
		GetErrorLog()->logString( "material id error" );
		return;
	}

	/*int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID ); 

	if( -1 == iLineNo )
	{
	OutputSlkLoadingMessage( "\tError:material.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
	assert( false && "gem.slk���Ҳ�����ƷID" );
	return;
	}

	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
	OutputSlkLoadingMessage( "\tError:material.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
	assert( false && "gem.slk���Ҳ�����ƷID" );
	return;
	}*/
	//
	pItemMaterial = (SCreateMaterial*)AllocItem( 0, sizeof( SItemCommon ) );
	if( !pItemMaterial )
	{
		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
		GetErrorLog()->logString( "material.slk���ڴ�������" );
		return;	
	}

	CopyCommon( pItemMaterial, common );

	//iCol = 3;
	//
	//if (!pReader->GetIntFieldByName("����PAtt",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usPAtt = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("����MAtt",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usMAtt = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("����PDef",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usPDef = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("����MDef",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usMDef = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("��ͨ���ӹ���״̬",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usStatusID = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("��ͨ����״̬�ȼ�",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usStatusLevel = iValue;
	//iCol++;

	//��ӵ���Ʒ������
	AddToMap( pItemMaterial );
}

//���������
void CItemDetail::AddTaskItem( CSlkReader *pReader, SItemCommon &common )
{
	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Task || common.ustItemID > EndID_Task )
	{
		GetErrorLog()->logString( "task id error" );
		return;
	}

	SItemCommon *pItemTask;
	//pItemTask = new SItemCommon;
	pItemTask = (SItemCommon*)AllocItem( 0, sizeof( SItemCommon ) );
	if( !pItemTask )
	{
		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
		GetErrorLog()->logString( "task.slk���ڴ�������" );
		return;	
	}
	CopyCommon( pItemTask, common );

	//��ӵ���Ʒ������
	AddToMap( pItemTask );
}

//�ӹ���
//void CItemDetail::AddToolItem( CSlkReader *pReader, SItemCommon &common )
//{
//	//ID���Ƿ��ڹ涨��Χ��
//	if( common.ustItemID < StartID_Tool || common.ustItemID > EndID_Tool )
//	{
//		assert( false && "tool id error" );
//		return;
//	}
//
//	SItemCommon *pItemTool;
//	pItemTool = new SItemCommon;
//	if( !pItemTool )
//	{
//		OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//		assert( false && "tool.slk���ڴ�������" );
//		return;	
//	}
//	CopyCommon( pItemTool, common );
//
//	//��ӵ���Ʒ������
//	AddToMap( pItemTool );
//}

bool CItemDetail::GetGemTypeAndSubID( int iGemID,int &iGemType,int &iGemSubID )
{
	iGemType = iGemID;
	iGemType &= 0xf0;
	iGemType >>= 4;
	if( iGemType < 0 || iGemType >= CItemDetail::gem_max )
		return false;
	iGemSubID = iGemID;
	iGemSubID &= 0x0f;
	if( iGemSubID < 1 || iGemSubID > 5 )
		return false;
	return true;
}

//���ݱ�ʯ������뵽��ȷ��vector
bool CItemDetail::AddToGems( SItemGem *pGem )
{
	int iGemType,iGemSubID;
	if( !GetGemTypeAndSubID( pGem->ucGemID,iGemType,iGemSubID ) )
		return false;
	iGemSubID --;
	(m_vectorGems[ iGemType ])[iGemSubID] = pGem;
	return true;
}

//���ݱ�ʯ����õ��ṹ
CItemDetail::SItemGem* CItemDetail:: GetGemByGemCode( int iGemID )
{
	int iGemType,iGemSubID;
	if( !GetGemTypeAndSubID( iGemID,iGemType,iGemSubID ) )
		return 0;
	iGemSubID --;
	return (m_vectorGems[ iGemType ])[iGemSubID];
}

void CItemDetail::AddGemItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemGem *pItemGem = 0;
	int iValue;
	int iCol;	

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gem.slk���Ҳ�����ƷID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:gem.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gem.slk���Ҳ�����ƷID" );
		return;
	}

	//pItemGem = new SItemGem;
	pItemGem = (SItemGem*)AllocItem( 0, sizeof( SItemGem ) );

	if( !pItemGem )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,�����ڴ�ʧ��!\r\n",common.ustItemID );
		goto error_ret;
	}

	CopyCommon( pItemGem,common );

	//skip itemID ��Ʒ����
	iCol = 3;

	//��ʯID
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ ��ʯID����!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ucGemID = iValue;

	//+PhyAtt
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ +PhyAtt��!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustAddPhyAtt = iValue;

	//+PhyDef
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ +PhyDef��!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Physics] = iValue;

	//+MagAtt
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ +MagAtt��!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustAddMagAtt = iValue;

	//+�����ٶ�
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"+AttSpeed" );
		goto error_ret;
	}
	pItemGem->usAttSpeed = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"������" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Frost] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"����" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Blaze] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"�׿���" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Thunder] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"������" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Poison] = iValue;

	//��ͨ���ӹ���״̬
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"��ͨ���ӹ���״̬" );
		goto error_ret;
	}
	pItemGem->ustNormalAttackStatusID = iValue;


	//��ͨ���ӹ���״̬�ȼ�
	if( !pReader->GetIntField( iCol ++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"��ͨ���ӹ���״̬�ȼ�" );
		goto error_ret;
	}
	pItemGem->ustNormalAttackStatusLevel = iValue;

	//�Ƿ�����Ƕ
	if( !pReader->GetIntField( iCol ++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,��ȡ%s��!\r\n",common.ustItemID,"��ͨ���ӹ���״̬�ȼ�" );
		goto error_ret;
	}
	if (iValue == 0)
		pItemGem->bIn = false;
	else 
		pItemGem->bIn = true;



	if( !AddToGems( pItemGem ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk��IDΪ:%d����Ʒ,�����GemID:%d!\r\n",common.ustItemID,pItemGem->ucGemID );
		goto error_ret;
	}
	AddToMap( pItemGem );
	return;
error_ret:
	//	if( pItemGem )
	//	delete pItemGem;
	return;
}

void CItemDetail::AddCreateItemRule( CSlkReader *pReader,SItemCommon &common )
{
	//�������ʱ�����ݲ�������ѡ�����ID
	SItemCreateItemRule *pItemRule = 0;
	int iValue;
	float fValue;
	int iCol;	
	std::string strTemp;
	SItemCommon *pItem;
	int iLoop;	

	if( common.ustItemID < StartID_CreateItemRule || common.ustItemID > EndID_CreateItemRule )
	{
		GetErrorLog()->logString( "CreateItemRule id error" );
		return;
	}


	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "createitemrule.slk���Ҳ�����ƷID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "createitemrule.slk���Ҳ�����ƷID" );
		return;
	}

	//pItemRule = new SItemCreateItemRule;
	pItemRule = (SItemCreateItemRule*)AllocItem( 0, sizeof( SItemCreateItemRule ) );
	if( !pItemRule )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,�����ڴ�ʧ��!\r\n",common.ustItemID );
		return;
	}

	CopyCommon( pItemRule,common );

	for( iLoop = 0 ; iLoop < 4 ; iLoop ++ )
	{
		pItemRule->material[ iLoop ].ustItemID = -1;
		pItemRule->material[ iLoop ].pItem = 0;
	}
	pItemRule->iMaterialNum = 0;

	iCol = 3;
	//�ϳ�Ŀ������
	if( pReader->GetStringField( iCol++,strTemp ) )
		//{
		//	/*OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡ%s����!\r\n",common.ustItemID,"�ϳ�Ŀ������" );
		//	goto error_ret;*/
		//	continue;
		//}
		//else
	{
		pItem = GetItemByName( (char*)strTemp.c_str() );
		if( !pItem )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,�����%s:%s!\r\n",common.ustItemID,"�ϳ�Ŀ������",
				strTemp.c_str() );
			goto error_ret;
		}
		pItemRule->ustTargetItemID = pItem->ustItemID;
		pItemRule->pItemTarget = pItem;
	}

	for( iLoop = 0 ; iLoop < 4 ; iLoop ++ )
	{
		//�ϳ�ԭ��iLoop
		if( !pReader->GetStringField( iCol++,strTemp ) )
		{
			if( 0 == iLoop )
			{
				//����һ��ԭ�϶�û��
				OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡ%s����!\r\n",common.ustItemID,"ԭ��1" );
				goto error_ret;
			}
			else
			{
				//skip ԭ�ϸ���
				iCol ++;
				continue;
			}
		}
		pItem = GetItemByName( (char*)strTemp.c_str() );
		if( !pItem )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡ%s:%s����!\r\n",common.ustItemID,"ԭ��",
				strTemp .c_str());
			goto error_ret;
		}

		pItemRule->material[ pItemRule->iMaterialNum ].pItem = pItem;
		pItemRule->material[ pItemRule->iMaterialNum ].ustItemID = pItem->ustItemID;

		if( !pReader->GetIntField( iCol ++,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡԭ��%d��������!\r\n",common.ustItemID,iLoop );
			goto error_ret;
		}
		pItemRule->material[ pItemRule->iMaterialNum ].ustCount = iValue;

		pItemRule->iMaterialNum ++;
	}

	if( !pReader->GetFloatField( iCol ++,fValue ) )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡ�ϳɼ��ʳ���!\r\n",common.ustItemID );
		goto error_ret;
	}

	fValue *= 1000;
	pItemRule->iCreateSuccRate = fValue;
	iCol++;

	if( !pReader->GetIntFieldByName( "ǿ��",iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk��IDΪ:%d����Ʒ,��ȡ�ϳɼ��ʳ���!\r\n",common.ustItemID );
		goto error_ret;
	}

	pItemRule->bIntensify = iValue;

	//OutputSlkLoadingMessage( "�ϳ��䷽��%s �ϳ�Ŀ��:%s ԭ��%d��\r\n",
	//	pItemRule->szItemName.c_str(),pItemRule->pItemTarget->szItemName.c_str(),pItemRule->iMaterialNum );

	AddToMap( pItemRule );
	m_vectorCreateItemRule.push_back(pItemRule);
	return;
error_ret:
	//if( pItemRule )
	//	delete pItemRule;
	return;
}


//�Ա�
//ְҵ
//�ȼ�
void CItemDetail::ReadEquipReq( CSlkReader *pReader,SItemCanEquip *pEquip,int &iCol )
{
	std::string strTemp;
	//if( !pReader->GetStringField( iCol,strTemp))
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ�����Ա�����ȱʡ=-1\r\n" );
	//	pEquip->cEquipSexReq = -1;
	//}
	if( !pReader->GetStringFieldByName( "װ���Ա�����", strTemp ) )
	{
		pEquip->cEquipSexReq = -1;
	}
	else
	{
		pEquip->cEquipSexReq = HelperFunc::GetIDByConstString( (char*)strTemp.c_str()
			,g_szSexType,sizeof( g_szSexType )/sizeof(char*) );
	}

	iCol ++;


	int iLoop;
	for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
		pEquip->abEquipProfessionReq[ iLoop ] = false;
	if( !pReader->GetStringFieldByName( "װ��ְҵ����", strTemp ) )
	{
		for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
			pEquip->abEquipProfessionReq[ iLoop ] = true;
	}

	//if( !pReader->GetStringField( iCol,strTemp))
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ��û�ж�������ȱʡ����ְҵ������װ��\r\n" );		
	//	for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
	//		pEquip->abEquipProfessionReq[ iLoop ] = true;
	//}
	else
	{
		//pEquip->cEquipProfessionReq = HelperFunc::GetIDByConstString( szTmp
		//	,g_szProfessionType,sizeof( g_szProfessionType )/sizeof(char*) );
		//���ö��ְҵ
		char *szSpn = " ,";
		char *szStr;
		int iEquip;
		szStr = strtok( const_cast<char*>(strTemp.c_str()),szSpn );
		while( szStr )
		{

			iEquip = HelperFunc::GetIDByConstString( szStr
				,g_szProfessionType,sizeof( g_szProfessionType )/sizeof(char*) );
			if( iEquip >= 0 && iEquip < ArabicNights::Profession_Max )
			{
				pEquip->abEquipProfessionReq[ iEquip ] = true;
			}
			szStr = strtok( NULL,szSpn );
		}			

	}
	iCol ++;

	int iValue;
	//if( !pReader->GetIntField( iCol,iValue) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ���ĵȼ�����ȱʡ=-1\r\n" );
	//	pEquip->stEquipLevelReq = -1;
	//}
	//else
	//{
	//	pEquip->stEquipLevelReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "װ����������", iValue ) )
	{
		pEquip->stEquipLevelReq = -1;
	}
	else
	{
		pEquip->stEquipLevelReq = iValue;
	}
	iCol ++;	

	////�������Ե�����
	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ������������ȱʡ=0\r\n" );
	//	pEquip->stStrengthReq = 0;
	//}
	//else
	//{
	//	pEquip->stStrengthReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "װ����������", iValue ) )
	{
		pEquip->stStrengthReq = 0;
	}
	else
	{
		pEquip->stStrengthReq = iValue;
	}
	iCol++;

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ������������ȱʡ=0\r\n" );
	//	pEquip->stConstitutionReq = 0;
	//}
	//else
	//{
	//	pEquip->stConstitutionReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "װ����������", iValue ) )
	{
		pEquip->stConstitutionReq = 0;
	}
	else
	{
		pEquip->stConstitutionReq = iValue;
	}

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ������������ȱʡ=0\r\n" );
	//	pEquip->stAgilityReq = 0;
	//}
	//else
	//{
	//	pEquip->stAgilityReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "װ����������", iValue ) )
	{
		pEquip->stAgilityReq = 0;
	}
	else
	{
		pEquip->stAgilityReq = iValue;
	}

	iCol++;

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ������������ȱʡ=0\r\n" );
	//	pEquip->stIntelligenceReq = 0;
	//}
	//else
	//{
	//	pEquip->stIntelligenceReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "װ���ǻ�����", iValue ) )
	{
		pEquip->stIntelligenceReq = 0;
	}
	else
	{
		pEquip->stIntelligenceReq = iValue;
	}



	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ����ħ������ȱʡ=0\r\n" );
	//	pEquip->stMagicReq = 0;
	//}
	//else
	//{
	//	pEquip->stMagicReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "װ��ħ������", iValue ) )
	{
		pEquip->stMagicReq = 0;
	}
	else
	{
		pEquip->stMagicReq = iValue;
	}

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:װ������������ȱʡ=0\r\n" );
	//	pEquip->stCharmReq = 0;
	//}
	//else
	//{
	//	pEquip->stCharmReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "װ����������", iValue ) )
	{
		pEquip->stCharmReq = 0;
	}
	else
	{
		pEquip->stCharmReq = iValue;
	}

	iCol++;
}

void CItemDetail::AddWeaponItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemWeapon *pItemWeapon;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Weapon || common.ustItemID > EndID_Weapon )
	{
		GetErrorLog()->logString( "weapon id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:weapon.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "weapon.slk���Ҳ�����ƷID" );
		return;
	}

	/*for (int loop = 0; loop <5;loop++)
	{*/
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:weapon.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "weapon.slk���Ҳ�����ƷID(loop)" );
		return;
	}

	//pItemWeapon = new SItemWeapon;
	pItemWeapon = (SItemWeapon*)AllocItem( 0, sizeof( SItemWeapon ) );
	//pItemWeapon = SLK_NEW(ITEM_WEAPON);
	//pItemWeapon = (WEAPON*)buffer[offset];
	//offset += sizeof(WEAPON);
	if( !pItemWeapon )
	{
		OutputSlkLoadingMessage( "\tError:�����ڴ����!\r\n"  );
		GetErrorLog()->logString( "weapon.slk�з����ڴ����" );
		return;	
	}


	CopyCommon( pItemWeapon,common );

	bool bReadSucc = true;
	int iCol;

	static int line = 0;
	std::string strTemp;
	int iValue;
	float fValue;
	while( bReadSucc )
	{
		/////////////////////////////////////////////////////////////////////////
#define WeaponGetFieldInt( p, msg ) \
	if( !GetIntField( pReader, iCol, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "Error:��ȡWeapon.slk�ֶ�["msg"]����" ); \
		GetErrorLog()->logString( "Error:��ȡWeapon.slk�ֶ�["msg"]����" ); \
		continue; \
		} \
		p = iValue; \
		iCol++;

#define WeaponGetFieldBool( p, msg ) \
	if( !Get ( pReader, iCol, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "Error:��ȡWeapon.slk�ֶ�["msg"]����" ); \
		GetErrorLog()->logString( "Error:��ȡWeapon.slk�ֶ�["msg"]����" ); \
		continue; \
		} \
		if( 0 == iValue ) \
		p = false; \
	else \
	p = true; \
	iCol++;

		/////////////////////////////////////////////////////////////////////////////////////////


		line++;
		bReadSucc = false;
		iCol = 3;

		//WeaponGetFieldInt(pItemWeapon->ustLevel ,             "�����ȼ�"  );
		WeaponGetFieldInt(pItemWeapon->ustModelID[0],          "����ģ��ID"  );
		WeaponGetFieldInt(pItemWeapon->ustModelID[1],          "����ģ��ID"  );
		WeaponGetFieldInt(pItemWeapon->ustIdleModelID,          "����ID"  );


		//if( !pReader->GetStringFieldByName( "��������(old)", strTemp ) )
		//{
		//	assert( false );
		//	continue;
		//}
		//pItemWeapon->ustWeaponType 
		//	= GetIDByConstString( strTemp.c_str(),g_szWeaponType,sizeof(g_szWeaponType)/sizeof(char*) );
		//iCol ++;

		if( !pReader->GetStringFieldByName( "��װ����λ", strTemp ) )
		{
			assert( false );
			continue;
		}
		SetCanEquipByString( pItemWeapon->szCanEquip,strTemp.c_str() );
		iCol ++;


		if (!pReader->GetIntFieldByName("�Ƿ�˫������(0/1)",iValue))
		{
			assert(false);
			continue;
		}
		if (iValue == 0)
		{
			pItemWeapon->bTwoHandWeapon = false;
		}
		else
		{
			pItemWeapon->bTwoHandWeapon = true;
		}
		iCol++;

		//WeaponGetFieldBool(pItemWeapon->bTwoHandWeapon,"�Ƿ�˫������(0/1)");



		if( !pReader->GetStringFieldByName( "�����Ӷ��ٶ�", strTemp ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->ustWeaponAttackRate
			= GetIDByConstString(strTemp.c_str(),g_szWeaponAttackRate,sizeof(g_szWeaponAttackRate)/sizeof(char*) );
		iCol ++;

		//װ���ƺ�����
		iCol++;

		//��ż����
		iCol++;



		//��������������
		iCol++;
		//װ��������
		ReadEquipReq( pReader,pItemWeapon,iCol );
		//װ������
		//�϶�������
		pItemWeapon->ustEquipType = equip_weapon;

		//////////////////////////////////////////////////////////////////////////

#define WeaponMacroGetInt( p, name ) \
	if( !pReader->GetIntFieldByName( name, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "\tError:��ȡ["name"]ʧ��\r\n" ); \
		GetErrorLog()->logString( "\tError:��ȡ["name"]ʧ��\r\n" ); \
		} \
		else \
		p = iValue;

		//////////////////////////////////////////////////////////////////////////
		WeaponMacroGetInt( pItemWeapon->stAtkRange,         "������Χ" );
		WeaponMacroGetInt( pItemWeapon->stAddStatus,        "����״̬(����)" );
		WeaponMacroGetInt( pItemWeapon->stMyAddStatus,        "����״̬(��)" );
		WeaponMacroGetInt( pItemWeapon->stAddStatusLevel,   "״̬�ȼ�(����)" );
		WeaponMacroGetInt( pItemWeapon->stMyAddStatusLevel,   "״̬�ȼ�(��)" );
		std::string strWeaponType;
		if( !pReader->GetStringFieldByName( "��������", strWeaponType ) ) 
		{
			OutputSlkLoadingMessage( "\tError:��ȡ[��������]ʧ��\r\n" );
			GetErrorLog()->logString( "\tError:��ȡ[��������]ʧ��\r\n" );
		}
		else
		{
			pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Combat;
			if( strWeaponType == "Combat" )//ȭͷ
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Combat;   
			else if( strWeaponType == "SingleHandBlade" )//���ֽ�
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_SingleHandBlade;
			//else if( strWeaponType == "LeftHandBlade" )//���ֽ�
			//	pItemWeapon->stWeaponType = XSanGuo::eWeaponType_LeftHandBlade;
			else if( strWeaponType == "DoubleHandBlade" )//˫�ֽ�
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_DoubleHandBlade;
			else if( strWeaponType == "LongBow" )//����
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_LongBow;	
			else if( strWeaponType == "Gun" )//ǹ����
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Gun;     
			else if( strWeaponType == "Stick" )//����
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Stick;
			else if (strWeaponType == "Dagger")//ذ��
				pItemWeapon->stWeaponType = XSanGuo::eWeaponTyoe_Dagger;
			else
			{
				OutputSlkLoadingMessage( "\tError:[�������Ͳ�����]ʧ��\r\n" );
				assert( false );
			}
		}

		if( pReader->GetIntFieldByName( "������Чid",iValue ) )
			pItemWeapon->iShotEffectID = iValue;
		else
			pItemWeapon->iShotEffectID = -1;

		if (!pReader->GetFloatFieldByName("״̬���м���",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fStatusRate = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ٶȼӳ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->stAtkSpeedAdd = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("��������ϵ��",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fWeaponHitMod = fValue;
		iCol++;



		if (!pReader->GetIntFieldByName("�;ö�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->stHPMax = iValue;
		iCol++;



		if( !pReader->GetIntFieldByName( "����۸�/��", iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:��ȡ���ߵ�����۸�/��Ĭ��0!\r\n" );
			pItemWeapon->stRepairPrice = 0;
		}
		else
		{
			pItemWeapon->stRepairPrice = iValue;
		}
		iCol++;

		if (!pReader->GetIntFieldByName("���������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustPhysicAttMax = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("��С������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustPhysicAttMin = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("���ħ������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustMagicAttMax = iValue;
		iCol++;


		//if (!pReader->GetIntFieldByName("��Сħ������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//pItemWeapon->ustMagicAttMin = iValue;
		//iCol++;



		///////���Թ���////////////////////////////////////////////////////////
		//��
		if( !pReader->GetIntFieldByName( "������", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Frost = iValue;
		iCol ++;	

		//��
		if( !pReader->GetIntFieldByName( "�𹥻�", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Blaze = iValue;
		iCol ++;	


		//��
		if( !pReader->GetIntFieldByName( "�׹���", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Thunder = iValue;
		iCol ++;	

		//��
		if( !pReader->GetIntFieldByName( "������", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Poison = iValue;
		iCol ++;

		if (!pReader->GetIntFieldByName("������Լ���1",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->iRandRate1 = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("������Լ���2",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->iRandRate2 = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("ħ����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Magic] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�繥����",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("���������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�繥���ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Frost] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�׵��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�׶��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sExact = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sCritical = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("������������",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fCriticalmultiple = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttSpeed = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sIntonateSpeed = iValue;	
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAddLuck = iValue;	
		iCol++;

		////////////////////////////////////////////////////////////////////
		bReadSucc = true;
		break;
	}
	//if( bReadSucc )
	//{

	//	//��ӵ���Ʒ������
	//	AddToMap( pItemWeapon );

	//	//����һ��״̬����
	//	if(pItemWeapon->ustItemID>=StartID_Weapon)
	//	{
	//		int index;
	//		index = pItemWeapon->ustItemID-StartID_Weapon;
	//		m_WeaponArray[index][pItemWeapon->ustLevel] = *pItemWeapon;

	//		if(pItemWeapon->ustLevel==1)
	//		{
	//			m_WeaponArray[index][ 0 ] = *pItemWeapon;
	//		}
	//	}
	//}

	if( bReadSucc )
	{
		//��ӵ���Ʒ������
		AddToMap( pItemWeapon );

		//����һ��ר�ŵ�vector���Weapon
		m_vectorWeaponItem.push_back( pItemWeapon );
	}
	else
	{
		//			delete( pItemWeapon );
	}
	//}
}

void CItemDetail::AddArmourItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemArmour *pItemArmour;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Armour || common.ustItemID > EndID_Armour )
	{
		GetErrorLog()->logString( "armour id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:armour.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "armour.slk���Ҳ�����ƷID" );
		return;
	}

	//for (int loop = 0;loop <5;loop++)
	//{
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:armour.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "armour.slk���Ҳ�����ƷID" );
		return;
	}
	//pItemArmour = new SItemArmour;
	pItemArmour = (SItemArmour*)AllocItem( 0, sizeof( SItemArmour ) );
	if( !pItemArmour )
	{
		OutputSlkLoadingMessage( "\tError:�����ڴ�ʧ��!\r\n" );
		GetErrorLog()->logString( "armour.slk�з����ڴ�ʧ��" );
		return;	
	}
	CopyCommon( pItemArmour,common );

	bool bReadSucc = true;
	int iCol;

	std::string strTemp;
	int iValue;
	float fValue;
	static int line = 0;
	while( bReadSucc )
	{
		line++;
		bReadSucc = false;
		iCol = 3;
		if( !pReader->GetStringFieldByName( "��װ����λ", strTemp ) )
		{
			assert( false );
			continue;
		}
		SetCanEquipByString( pItemArmour->szCanEquip,strTemp.c_str() );
		iCol ++;

		if( !pReader->GetIntFieldByName( "ģ��ID", iValue ) )
		{
			assert( false );
			continue;
		}
		for( int i=0;i<ArabicNights::Profession_Max;i++ )
		{
			pItemArmour->ustModelID[i][0][0] = iValue;
			pItemArmour->ustModelID[i][0][1] = iValue;
			pItemArmour->ustModelID[i][1][0] = iValue;
			pItemArmour->ustModelID[i][1][1] = iValue;
		}

		if( !pReader->GetStringFieldByName( "װ������", strTemp ) )
		{
			assert( false );
			continue;
		}
		iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
			g_szEquipType,sizeof(g_szEquipType)/sizeof(char*) );

		if( -1 == iValue )
			continue;
		pItemArmour->ustEquipType = 1;//
		pItemArmour->ustEquipType <<= iValue;
		iCol ++;

		//װ��������
		ReadEquipReq( pReader,pItemArmour,iCol );

		//װ����������
		iCol++;

		//װ���ƺ�����
		iCol++;

		//װ����ż����
		iCol++;

		//װ������ƺ�����
		iCol++;



		//����۸�/��
		//if( !GetIntField( pReader, iCol, iValue ) )
		if( !pReader->GetIntFieldByName( "����۸�/��", iValue ) )
		{
			//OutputSlkLoadingMessage( "\tError:��ȡ���ߵ�����۸�/��Ĭ��0!\r\n" );
			pItemArmour->stRepairPrice = 0;
		}
		else
		{
			pItemArmour->stRepairPrice = iValue;
		}
		iCol++;

		//�;ö�Max
		//if( !GetIntField( pReader, iCol, iValue ))
		if( !pReader->GetIntFieldByName( "�;ö�", iValue ))
		{
			//	OutputSlkLoadingMessage( "\tError:��ȡ���ߵ��;ö�MaxĬ��-1!\r\n" );
			pItemArmour->stHPMax = ITEMNO_HPMAX;
		}
		else
		{
			pItemArmour->stHPMax = iValue;
		}
		iCol++;


		if( !pReader->GetIntFieldByName( "����״̬(����)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stAddStatus  = iValue;
		iCol ++;	

		if( !pReader->GetIntFieldByName( "����״̬(��)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stMyAddStatus  = iValue;
		iCol ++;	


		if( !pReader->GetIntFieldByName( "����״̬�ȼ�(����)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stAddStatusLevel = iValue;
		iCol ++;	

		if( !pReader->GetIntFieldByName( "����״̬�ȼ�(��)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stMyAddStatusLevel = iValue;
		iCol ++;	



		if( !pReader->GetFloatFieldByName( "״̬���м���", fValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->fStatusRate = fValue;
		iCol ++;	

		//��С�������
		if (!pReader->GetIntFieldByName("�������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->ustPhysicDef = iValue;
		iCol++;

		/////////���Է���///////////////////////////////////

		//��
		if( !pReader->GetIntFieldByName( "������", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Frost = iValue;
		iCol ++;	

		//��
		if( !pReader->GetIntFieldByName( "�����", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Blaze = iValue;
		iCol ++;	

		////��
		//if( !pReader->GetIntFieldByName( "�����", iValue ) )
		//{
		//	assert( false );
		//	continue;
		//}
		//pItemArmour->stFengDef = iValue;
		//iCol ++;	

		//��
		if( !pReader->GetIntFieldByName( "�׷���", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Thunder = iValue;
		iCol ++;	

		//��
		if( !pReader->GetIntFieldByName( "������", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Poison = iValue;
		iCol ++;

#define ArmourMacroGetFieldInt( t, msg ) \
	if( !pReader->GetIntFieldByName( msg, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "Error:��ȡArmour.slk�ֶ�["msg"]����\r\n" ); \
		GetErrorLog()->logString( "Error:��ȡArmour.slk�ֶ�["msg"]����" ); \
		continue; \
		} \
		t = iValue; \
		iCol ++;

		//�ؼ�
		//eMaxEquip
		ArmourMacroGetFieldInt( pItemArmour->sPartCount,								"��װ�������" );
		ArmourMacroGetFieldInt( pItemArmour->sSuitID,									"������װID" );

		ArmourMacroGetFieldInt( pItemArmour->iRandRate1,								"������Լ���1" );
		ArmourMacroGetFieldInt( pItemArmour->iRandRate2,								"������Լ���2" );
		//////////////////////////////////////////////////////////////////////////////
		if (!pReader->GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("ħ����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Magic] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�繥����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("���������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�繥���ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Frost] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�׵��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�׶��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sExact = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDodge = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sCritical = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sCriticalmultiple = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttSpeed = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sIntonateSpeed = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("�ƶ��ٶ�",fValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->fMoveSpeed = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("�����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Max] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("���濹������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�׵翹������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Thunder] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�׶���������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Poison] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("��������ı�����%",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDefPer[ePlayDef_Physics] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�������ֵ����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpMax = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("ħ�����ֵ����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpMax = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�������ֵ����(%)",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpMaxPer = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("ħ�����ֵ����%",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpMaxPer = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�����ָ�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpRestore = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("ħ���ָ�����",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpRestore = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sReboundRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("�ϳɼ�������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sComposeRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sProficiencyRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("ǿ����������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sStrengthenRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("��Ƕ��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sEnchaseRate = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAddLuck = iValue;
		iCol++;


		//////////////////////////////////////////////////////////////////

		bReadSucc = true;
		break;
	}
	if( bReadSucc )
	{
		//��ӵ���Ʒ������
		AddToMap( pItemArmour );

		//����һ��ר�ŵ�vector�����aromour, glove, shoe
		int iTemp;
		int iArmourValue, iGloveValue, iShoeValue, iCapValue;

		iTemp = HelperFunc::GetIDByConstString( "armour",
			g_szEquipType, sizeof(g_szEquipType)/sizeof(char*) );
		iArmourValue = 1;
		iArmourValue <<= iTemp;

		iTemp = HelperFunc::GetIDByConstString( "glove",
			g_szEquipType, sizeof(g_szEquipType)/sizeof(char*) );
		iGloveValue = 1;
		iGloveValue <<= iTemp;

		iTemp = HelperFunc::GetIDByConstString( "shoe",
			g_szEquipType, sizeof(g_szEquipType)/sizeof(char*) );
		iShoeValue = 1;
		iShoeValue <<= iTemp;

		iTemp = HelperFunc::GetIDByConstString( "helmet",
			g_szEquipType, sizeof(g_szEquipType)/sizeof(char*) );
		iCapValue = 1;
		iCapValue <<= iTemp;

		if(pItemArmour->ustEquipType==iArmourValue)
		{
			m_vectorArmourItem.push_back(pItemArmour);
		}
		if(pItemArmour->ustEquipType==iGloveValue)
		{
			m_vectorGloveItem.push_back(pItemArmour);
		}
		if(pItemArmour->ustEquipType==iShoeValue)
		{
			m_vectorShoeItem.push_back(pItemArmour);
		}
		if(pItemArmour->ustEquipType==iCapValue)
		{
			m_vectorCapItem.push_back(pItemArmour);
		}
	}
	else
	{
		//		delete( pItemArmour );
	}
	// }
}

//ȡ�ü�����������
//
static char* (g_strKey[]) =
{
	"profession"
		,"skillused"
};
static char* g_strSpn = " ,\r\n";

bool CItemDetail::GetProfessionCondition( SSkillProfessionCondition *pCondition
										 ,char *szProfession,char *szLevel )
{
	if( !pCondition || !szProfession || !szLevel )
		return false;
	pCondition->stProfessionID = GetProfessionID( szProfession );
	if( -1 == pCondition->stProfessionID )
	{
		OutputSlkLoadingMessage( "\t����ְҵ������������ʹ������:�Ҳ���ְҵ:%s\r\n",szProfession );
		return false;
	}
	pCondition->stNeedLevel = atoi( szLevel );
	return true;
}

//bool CItemDetail::GetSkillUsedCondition( SSkillUsedCondition *pCondition
//						   ,char *szSkill,char *szMinUsed,char *szMaxUsed )
//{
//	if( !pCondition || !szSkill || !szMinUsed || !szMaxUsed )
//		return false;
//	SItemCommon *pItem = GetItemByName( szSkill );
//	if( !pItem )
//	{
//		OutputSlkLoadingMessage( "\t����ְҵ�������������Ҳ�������:%s\r\n",szSkill );
//		return false;
//	}
//	pCondition->ustSkillID = pItem->ustItemID;
//	pCondition->ustMinUsed = atoi( szMinUsed );
//	pCondition->ustMaxUsed = atoi( szMaxUsed );
//	return true;
//}

//void CItemDetail::GetSkillUnderstandConditionFromString( SItemSkill *pSkill
//														,char *szStr )
//{	
//	char *szToken;
//	int iNum;
//	char *szProfession;
//	char *szLevel;
//	char *szSkill;
//	char *szMinUsed;
//	char *szMaxUsed;
//	
//	szToken = strtok( szStr,g_strSpn );
//	while( szToken )
//	{
//		//ְҵ����
//		if( 0 == strcmp( g_strKey[0],szToken ) )
//		{
//			iNum = pSkill->skillunderstand.iProfessionNum;
//			if( iNum < const_iSkillUnderstandPCondition )
//			{
//				szProfession = strtok(NULL,g_strSpn);
//				szLevel = strtok( NULL,g_strSpn);
//				szToken = szLevel;
//				if( GetProfessionCondition( 
//					&pSkill->skillunderstand.profession[ iNum ],
//					szProfession,szLevel  ) )
//				{
//					pSkill->skillunderstand.iProfessionNum ++;
//				}
//				else
//				{
//					OutputSlkLoadingMessage( "\t����%d\r\n",pSkill->ustItemID );
//				}
//			}
//		}
//		else
//		//����ʹ������
//		if( 0 == strcmp( g_strKey[1],szToken ) )
//		{
//			iNum = pSkill->skillunderstand.iSkillUsedNum;
//			if( iNum < const_iSkillUnderstandSCondition )
//			{
//				szSkill = strtok(NULL,g_strSpn);
//				szMinUsed = strtok(NULL,g_strSpn);
//				szMaxUsed = strtok(NULL,g_strSpn);
//				szToken = szMaxUsed;
//
//				if( GetSkillUsedCondition(
//					&pSkill->skillunderstand.skillused[ iNum ],
//					szSkill,szMinUsed,szMaxUsed ) )
//				{
//					pSkill->skillunderstand.iSkillUsedNum ++;
//				}
//				else
//				{
//					OutputSlkLoadingMessage( "\t����%d\r\n",pSkill->ustItemID );
//				}
//			}
//		}
//
//		szToken = strtok( NULL,g_strSpn );
//	}
//}
//
//void CItemDetail::GetSkillUsingConditionFromString( SItemSkill *pSkill,char *szStr )
//{
//	char *szToken;
//	int iNum;
//	char *szProfession;
//	char *szLevel;
//
//	szToken = strtok( szStr,g_strSpn );
//	while( szToken )
//	{
//		//ְҵ����
//		if( 0 == strcmp( g_strKey[0],szToken ) )
//		{
//			iNum = pSkill->skillusing.iProfessionNum;
//			if( iNum < const_iSkillUnderstandPCondition )
//			{
//				szProfession = strtok(NULL,g_strSpn);
//				szLevel = strtok( NULL,g_strSpn);
//				szToken = szLevel;
//				if( GetProfessionCondition( 
//					&pSkill->skillusing.profession[ iNum ],
//					szProfession,szLevel  ) )
//				{
//					pSkill->skillusing.iProfessionNum ++;
//				}
//				else
//				{
//					OutputSlkLoadingMessage( "\t����%d\r\n",pSkill->ustItemID );
//				}
//			}
//		}
//
//		szToken = strtok( NULL,g_strSpn );
//	}
//}

void CItemDetail::AddSkillItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemSkill *pItemSkill;
	float fValue;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Skill || common.ustItemID > EndID_Skill )
	{
		GetErrorLog()->logString( "skill id error" );
		return;
	}

	int iLineNo = pReader->FindFirstLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "Error:�ڼ��ܱ����Ҳ�����Ʒ:%d\r\n",common.ustItemID );
		char string[256];
		sprintf(string, "�ڼ��ܱ����Ҳ�����Ʒ:%d",common.ustItemID);
		//
		return;
	}

	//ÿ�����ܶ���ʮ���ȼ�
	for( int iLoop = 0;iLoop<10;iLoop++ )
	{
		if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo+iLoop ))
		{
			OutputSlkLoadingMessage( "Error:�ڼ��ܱ����Ҳ�����Ʒ:%d\r\n",common.ustItemID );
			GetErrorLog()->logString( "skill.slk�Ҳ�����ƷID" );
			return;
		}

		//pItemSkill = new SItemSkill;
		pItemSkill = (SItemSkill*)AllocItem( 0, sizeof( SItemSkill ) );
		if( !pItemSkill )
		{
			OutputSlkLoadingMessage( "Error:����skill��Ҫ���ڴ����\r\n",common.ustItemID );
			char string[256];
			sprintf(string, "����skill��Ҫ���ڴ����:%d",common.ustItemID);
			MessageBox( NULL, string, "warning", MB_OK );
			return;	
		}

		CopyCommon( pItemSkill,common );

		bool bReadSucc = true;
		int iCol;

		std::string strTemp;
		int   iValue;
		while( bReadSucc )
		{
			bReadSucc = false;
			iCol = 3;

			//////////////////////////////////////////////////////////////////////////

#define SkillMacroGetFieldInt( t, msg ) \
	if( !pReader->GetIntFieldByName( msg, iValue ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:��ȡskill.slk�ֶ�["msg"]����\r\n" ); \
			GetErrorLog()->logString( "Error:��ȡskill.slk�ֶ�["msg"]����" ); \
			continue; \
			} \
			t = iValue; \
			iCol++;

#define SkillMacroGetFiledAction( t, msg ) \
	if( !pReader->GetStringFieldByName( msg, strTemp ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:��ȡskill.slk�ֶ�["msg"]����\r\n" ); \
			char string[256]; \
			sprintf(string, "��ȡskill.slk�ֶ�["msg"]����!%d",common.ustItemID); \
			MessageBox( NULL, string, "warning", MB_OK ); \
			assert( false ); \
			continue; \
			} \
			t = ArabicNightsAction::FindActionIdByName( strTemp.c_str() ); \
			iCol++;

			//////////////////////////////////////////////////////////////////////////
			if ( !pReader->GetStringFieldByName( "��������", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡskill.slk�ֶ�[��������]����\r\n" );
				char string[256];
				sprintf(string, "��ȡskill.slk�ֶ�[��������]����!%d",common.ustItemID);
				MessageBox( NULL, string, "warning", MB_OK );
				assert( false ); 
			}
			//pItemSkill->szSkillName = strTemp;
			pItemSkill->dwSkillNameAddr = AllocStringCopy( strTemp.c_str() );
			iCol++;

			//////////////////////////////////////////////////////////////////////////
			SkillMacroGetFiledAction( pItemSkill->ustIDSkillAction[0],      "���ܶ�������1" );
			SkillMacroGetFiledAction( pItemSkill->ustIDSkillAction[1],      "���ܶ�������2" );
			SkillMacroGetFieldInt( pItemSkill->ustLevel,                    "���ܵȼ�" );
			SkillMacroGetFieldInt( pItemSkill->ustPrepTime,                 "����ʱ��(ms)" );
			SkillMacroGetFiledAction( pItemSkill->ustIDPrepAction,          "������������" );
			SkillMacroGetFieldInt( pItemSkill->iIntonateEffect,             "������Ч" );
			SkillMacroGetFieldInt( pItemSkill->iAttackedEffect,             "���Ч��" );
			SkillMacroGetFieldInt( pItemSkill->ustSkillEffect,              "����Ч��" );
			SkillMacroGetFieldInt( pItemSkill->iAttackedEffect,             "Ŀ��Ч��" );
			SkillMacroGetFiledAction( pItemSkill->ustIDTargetHitAction,     "Ŀ�걻������" );
			SkillMacroGetFieldInt( pItemSkill->stTargetHitActionRate,       "������������" );
			SkillMacroGetFieldInt( pItemSkill->ustMeAddStatusID,            "����״̬(��)" );
			SkillMacroGetFieldInt( pItemSkill->ustMeAddStatusLevel,         "���ӵȼ�(��)" );
			SkillMacroGetFieldInt( pItemSkill->ustDstAddStatusID,           "����״̬(�Է�)" );
			SkillMacroGetFieldInt( pItemSkill->ustDstAddStatusLevel,        "���ӵȼ�(�Է�)" );
			SkillMacroGetFieldInt( pItemSkill->ustStatusHitRate,            "״̬���м���" );
			SkillMacroGetFieldInt( pItemSkill->dwSubComboStatus,            "���״̬" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_0],            "���״̬0" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_1],            "���״̬1" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_2],            "���״̬2" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_3],            "���״̬3" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_4],            "���״̬4" );

			//SkillMacroGetFieldInt( pItemSkill->dwSubComboStatus,            "���״̬" );
			//            SkillMacroGetFieldInt( pItemSkill->ustPhysicAdd,                "�������ӳ�" );
			//          SkillMacroGetFieldInt( pItemSkill->ustMagicAdd,                 "ħ�������ӳ�" );
			//        SkillMacroGetFieldInt( pItemSkill->ustPhysicAtt,                "��������" );
			//      SkillMacroGetFieldInt( pItemSkill->ustMagicAtt,                 "ħ��������" );
			SkillMacroGetFieldInt( pItemSkill->ustHoldTime,                 "��Ӳʱ��" );

			if( !pReader->GetStringFieldByName( "ʹ�ý��㹫ʽ", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡʹ�ý��㹫ʽ����!\r\n" );
				GetErrorLog()->logString( "skill.slk��ʹ�ý��㹫ʽ����" );
				continue;
			}
			pItemSkill->ustDamageBalanceType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szBalanceType, sizeof(g_szBalanceType)/sizeof( char *) );

			if( -1==pItemSkill->ustDamageBalanceType )
			{
				OutputSlkLoadingMessage( "Error:��ȡʹ�ý��㹫ʽ����!\r\n" );
				GetErrorLog()->logString( "skill.slk��ʹ�ý��㹫ʽ����" );
				continue;
			}
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->ustSkillActionSpeed, "�����ٶ�" );
			SkillMacroGetFieldInt( pItemSkill->ustCostHP,           "����HP" );
			SkillMacroGetFieldInt( pItemSkill->ustCostHPPer,        "����HP(%)" );
			SkillMacroGetFieldInt( pItemSkill->ustCostMP,           "����MP" );
			SkillMacroGetFieldInt( pItemSkill->ustCostMPPer,         "����MP(%)" );
			//SkillMacroGetFieldInt( pItemSkill->ustCostTP,           "����TP" );

			if( !pReader->GetStringFieldByName( "���ܵ�����", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�������ͳ���!\r\n" );
				GetErrorLog()->logString( "skill.slk�м������ͳ���" );
				continue;
			}
			pItemSkill->stSkillType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
				g_szSkillType,sizeof(g_szSkillType)/sizeof( char* ) );

			if( -1 == pItemSkill->stSkillType )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�������ͳ���!\r\n" );
				GetErrorLog()->logString( "skill.slk�м������ͳ���" );
				continue;
			}
			iCol ++;

			if( !pReader->GetStringFieldByName( "�����������", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�����������������!\r\n" );
				GetErrorLog()->logString( "skill.slk�м����������������" );
				continue;
			}
			pItemSkill->stGeneralType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
				g_szSkillGeneralType, sizeof(g_szSkillGeneralType)/sizeof( char* ) );

			if( -1 == pItemSkill->stGeneralType )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�����������������!\r\n" );
				GetErrorLog()->logString( "skill.slk�м����������������" );
				continue;
			}
			iCol++;

			if( !pReader->GetStringFieldByName( "Ŀ������", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�������ö������!\r\n" );
				GetErrorLog()->logString( "skill.slk�м������ö������" );
				continue;
			}
			//��string�õ���������
			iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szTargetString,sizeof(g_szTargetString)/sizeof(char*) );		

			if( -1 == iValue )
			{
				OutputSlkLoadingMessage( "Error:��ȡ�����������ͳ���!\r\n" );
				GetErrorLog()->logString( "skill.slk�м����������ͳ���" );
				continue;
			}
			pItemSkill->stTargetType = iValue;		
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->iDurationTime,       "����ʱ��" );
			SkillMacroGetFieldInt( pItemSkill->iDamageBalanceDelay, "������" );

			if( !pReader->GetStringFieldByName( "������������", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡ���ܳ����������ͳ���!\r\n" );
				GetErrorLog()->logString( "skill.slk�м��ܳ����������ͳ���" );
				continue;
			}
			//��string�õ������������� 12
			iValue = GetIDByConstString( strTemp.c_str(),g_szEffectCenter,sizeof(g_szEffectCenter)/sizeof(char*) );

			if( -1 == iValue )
			{
				OutputSlkLoadingMessage( "Error:��ȡ���ܳ����������ͳ���!\r\n" );
				GetErrorLog()->logString( "skill.slk�м��ܳ����������ͳ���" );
				continue;
			}
			pItemSkill->stEffectCenterType = iValue;		
			iCol ++;

			//SkillMacroGetFieldInt( pItemSkill->ustAttackInterval,                       "�����������(ms)" );
			SkillMacroGetFieldInt( pItemSkill->cLearnProfessionReq,                     "ѧϰְҵ����" );
			SkillMacroGetFieldInt( pItemSkill->stLearnLevelReq,                         "ѧϰ�ȼ�����" );
			SkillMacroGetFieldInt( pItemSkill->stStopSkillPrepRate,                     "�����������(%)" );
			SkillMacroGetFieldInt( pItemSkill->stRangeCanCast,                          "ʩ������" );
			SkillMacroGetFieldInt( pItemSkill->stDamageEffectDistance,                  "�˺���Ч����" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.cRangeType,             "���ܷ�Χ��״" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.radius,     "���÷�Χ" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 0 ].x, "ƫ������1x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 0 ].y, "ƫ������1y" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 1 ].x, "ƫ������2x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 1 ].y, "ƫ������2y" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 2 ].x, "ƫ������3x" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 2 ].y, "ƫ������3y" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 3 ].x, "ƫ������4x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 3 ].y, "ƫ������4y" );

			if(!pReader->GetIntFieldByName( "�Ƿ���Ҫ����", iValue ))
			{
				OutputSlkLoadingMessage( "Error:��ȡ�Ƿ���Ҫ��������!\r\n" );
				GetErrorLog()->logString( "skill.slk�м����Ƿ���Ҫ��������" );
				continue;
			}
			pItemSkill->bNeedWeapon = iValue?true:false;
			iCol++;

			SkillMacroGetFieldInt( pItemSkill->stUseItem,								"����Ҫ��" );
			if(!pReader->GetIntFieldByName( "�Ƿ�ά�ּ���", iValue ))
			{
				//ȱʡΪfalse
				iValue = 0;
			}
			pItemSkill->bHoldSkill = iValue>0?true:false;
			iCol++;

			//ά�ֶ���
			if(!pReader->GetStringFieldByName( "ά�ֶ���", strTemp ))
			{
				OutputSlkLoadingMessage( "Error:��ȡ����ά�ֶ�������!\r\n" );
				GetErrorLog()->logString( "skill.slk����ά�ֶ�������" );
				continue;
			}
			pItemSkill->ustIDHoldAction = ArabicNightsAction::FindActionIdByName( strTemp.c_str() );
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->ustHoldEffect,       "ά����Ч" );
			SkillMacroGetFieldInt( pItemSkill->dwSkillColddownTime, "������ȴʱ��(Colddown)" );

			if(!pReader->GetStringFieldByName( "ʩ��Ŀ������", strTemp ))
			{
error_casttarget:
				OutputSlkLoadingMessage( "Error:��ȡʩ��Ŀ�����Գ���!\r\n" );
				GetErrorLog()->logString( "skill.slkʩ��Ŀ�����Գ���" );				
			}
			else
			{			
				iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
					g_szSkillCastTarget,sizeof(g_szSkillCastTarget)/sizeof( char* ) );
				if( iValue < 0 )
					goto error_casttarget;
				pItemSkill->ustCastTarget = iValue;
			}
			iCol ++;


			//����easyusedata;
			pItemSkill->easyusedata.SEasyUseData::SEasyUseData();		

			if( target_friend == pItemSkill->stTargetType )
				pItemSkill->easyusedata.bApplyToFriend = true;

			//��ͨ������ ����Ŀ��϶��ǵ���
			if (IsNormalAttack( pItemSkill->ustItemID ) )
				pItemSkill->easyusedata.bApplyToFriend = false;
			//�ж��Ƿ��ǹ���
			if (IsNormalAttack( pItemSkill->ustItemID ))
				pItemSkill->easyusedata.bSkillWithDamage = true;
			switch (pItemSkill->ustDamageBalanceType)
			{
			case balancetype_phydamage:// = 1,	//�����˺�����
			case balancetype_magdamage:// = 2,	//ħ���˺�����
			case balancetype_addextrahp://= 5,//˲����Ѫ
				pItemSkill->easyusedata.bSkillWithDamage = true;
				break;
			case balancetype_none:// = 0,		//û���κν���
			case balancetype_restorehp:// = 3,	//��HP����
			case balancetype_relive://	  = 4,	//�������
				//case balancetype_restoretp:// = 6,	//��TP����
			case balancetype_damagemp:          // �˺�MP
			default:
				break;
			}

			//SkillMacroGetFieldInt( pItemSkill->stPassivePhyAtkAdd ,         "��������������" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveMPMaxAdd ,          "��ħ��ֵ����" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveHPMaxAdd ,          "����������" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveAutoRestoreHP ,     "�������ظ�" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveHitAdd ,            "��������" );
			//SkillMacroGetFieldInt( pItemSkill->stCurHpSet ,                 "��ǰ����" );
			//SkillMacroGetFieldInt( pItemSkill->stCurMPSet ,                 "��ǰħ��ֵ" );
			SkillMacroGetFieldInt( pItemSkill->stSkillNeed ,                "��������" );
			SkillMacroGetFieldInt( pItemSkill->stRankNeed ,                 "�ٽ�����" );
			SkillMacroGetFieldInt( pItemSkill->stMoneyNeed,                 "ѧϰ�����Ǯ" );
			SkillMacroGetFieldInt( pItemSkill->stSkillLevelNeed,            "ѧϰǣ�Ƽ��ܵȼ�" );  


			SkillMacroGetFieldInt( pItemSkill->stSTRNeed,                   "����Ҫ��" );
			SkillMacroGetFieldInt( pItemSkill->stVITNeed,                   "����Ҫ��" );
			SkillMacroGetFieldInt( pItemSkill->stAGINeed,                   "����Ҫ��" );
			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "����Ҫ��" );

			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "ħ��Ҫ��" );
			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "����Ҫ��" );

			if( !pReader->GetStringFieldByName( "������������", strTemp ) )
			{
				//assert( false && "skill.slk ��������Ҫ��" );
				pItemSkill->stWeaponNeed = -1;
			}
			pItemSkill->stWeaponNeed
				= GetIDByConstString( strTemp.c_str(),g_szWeaponType,sizeof(g_szWeaponType)/sizeof(char*) );


			SkillMacroGetFieldInt( pItemSkill->stEnmity,                   "���ֵ" );



			if( pReader->GetFloatFieldByName( "����",fValue ) )
				pItemSkill->fBonusFactor = fValue;
			else
				pItemSkill->fBonusFactor = 1.0f;
			iCol++;

			bReadSucc = true;
			break;
		}
		if( bReadSucc )
		{
			//��ӵ���Ʒ������
			AddToMap( pItemSkill );

			//����һ��������ƷID��������ŵ� ת��
			m_mapSkillNO.insert( mapSkillNO::value_type( pItemSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
			m_vecSkill.push_back( pItemSkill->ustItemID );

			//����һ����������(ֻ�޷���)
			if(pItemSkill->ustItemID>=StartID_Skill)
			{
				int index;
				index = pItemSkill->ustItemID-StartID_Skill;
				m_SkillArray[index][pItemSkill->ustLevel] = *pItemSkill;

				if(pItemSkill->ustLevel==1)
				{
					m_SkillArray[index][ 0 ] = *pItemSkill;
				}
			}
		}
		else
		{
			//delete pItemSkill;
		}
	}
}

void CItemDetail::AddOtherItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemOther *pItemOther;
	//pItemOther = new SItemOther;
	pItemOther = (SItemOther*)AllocItem( 0, sizeof( SItemOther ) );
	if( !pItemOther )
		return;	

	CopyCommon( pItemOther,common );
	AddToMap( pItemOther );
}

void CItemDetail::AddCardItem( CSlkReader *pReader,SItemCommon &common )
{
	SItemCard *pItemCard;
	//pItemCard = new SItemCard;
	pItemCard = (SItemCard*)AllocItem( 0, sizeof( SItemCard ) );
	if( !pItemCard )
		return;	

	CopyCommon( pItemCard,common );
	AddToMap( pItemCard );
}

void CItemDetail::AddStatusItem( CSlkReader *pReader, SItemCommon &common )
{
	SItemStatus *pItemStatus;

	//ID���Ƿ��ڹ涨��Χ��
	if( common.ustItemID < StartID_Status 
		|| common.ustItemID > EndID_Status )
	{
		GetErrorLog()->logString( "status id error" );
		return;
	}

	//int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );
	int iLineNo = pReader->FindFirstLineByIntField( 1, common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "Error:��״̬�����Ҳ�����Ʒ:%d\r\n",common.ustItemID );
		GetErrorLog()->logString( "status.slk���Ҳ�����ƷID" );

		char buffer[128];
		sprintf(buffer,"itemid=%d",common.ustItemID);
		MessageBox(NULL,buffer,"test",MB_OK);

		return;
	}

	//ÿ��״̬����ʮ���ȼ�
	for( int iLoop = 0;iLoop<10;iLoop++ )
	{
		if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo+iLoop ))
		{
			OutputSlkLoadingMessage( "Error:��״̬�����Ҳ�����Ʒ:%d\r\n",common.ustItemID );
			GetErrorLog()->logString( "status.slk���Ҳ�����ƷID(loop)" );
			return;
		}

		//pItemStatus =new SItemStatus;
		pItemStatus = (SItemStatus*)AllocItem( 0, sizeof( SItemStatus ) );
		if( !pItemStatus )
		{
			OutputSlkLoadingMessage( "Error:����status��Ҫ���ڴ����\r\n",common.ustItemID );
			GetErrorLog()->logString( "status.slk�з�����Ҫ���ڴ����" );
			return;	
		}

		CopyCommon( pItemStatus, common );

		bool bReadSucc = true;
		int iCol;

		int   iValue;
		float fValue;
		std::string strTemp;
		while( bReadSucc )
		{

			//////////////////////////////////////////////////////////////////////////
			// MacroGetFieldInt
#define MacroGetFieldInt( t, msg ) \
	if( !GetIntField( pReader, iCol, iValue ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			GetErrorLog()->logString( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			continue; \
			} \
			t = iValue; \
			iCol++;

#define MacroGetFieldBool( t, msg ) \
	if( !GetIntField( pReader, iCol, iValue ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			GetErrorLog()->logString( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			continue; \
			} \
			if( 0 == iValue ) \
			t = false; \
		else \
		t = true; \
		iCol++;

#define MacroGetFieldFloat( t, msg ) \
	if( !GetFloatField( pReader, iCol, fValue ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			GetErrorLog()->logString( "Error:��ȡstatus.slk�ֶ�["msg"]����" ); \
			continue; \
			} \
			t = fValue; \
			iCol++;

			//////////////////////////////////////////////////////////////////////////

			bReadSucc = false;
			iCol = 3;

			//״̬�ȼ�
			if(!GetIntField( pReader, iCol, iValue ))
			{
				OutputSlkLoadingMessage( "Warning:��״̬ȱʡ�ȼ�=1!\r\n" );	
				pItemStatus->ustLevel = 1;
			}
			else
				pItemStatus->ustLevel = iValue;
			iCol++;		


			MacroGetFieldInt( pItemStatus->ustEffectID,             "״̬ģ��ID" );
			MacroGetFieldInt( pItemStatus->iDurationTime,           "״̬����ʱ��(ms)" );
			MacroGetFieldInt( pItemStatus->iBalanceDelayTime,       "Ӱ����ʱ��" );
			MacroGetFieldInt( pItemStatus->stType,                  "״̬����" );
			MacroGetFieldInt( pItemStatus->stPriority,              "���ȼ���" );

			//ʹ�ý��㹫ʽ
			if( !GetStringField( pReader, iCol, strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:��ȡʹ�ý��㹫ʽ����!\r\n" );
				GetErrorLog()->logString( "status.slk�ж�ȡʹ�ý��㹫ʽ����" );
				continue;
			}
			pItemStatus->stBalanceType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szStatusBalanceType, sizeof(g_szStatusBalanceType)/sizeof(char*) );
			iCol ++;

			MacroGetFieldInt( pItemStatus->stBalanceParam,						"����ʹ�õĲ���" );	//1
			MacroGetFieldBool( pItemStatus->bAttckedNoStatus,						"�ܵ�������ʱ���Ƿ�����״̬" );			//2
			MacroGetFieldBool( pItemStatus->bAttckNoStatus,							"������ʱ���Ƿ�����״̬" );			//2

			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_STRENGTH],			"�ı�ǿ׳" );//3
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_CONSTITUTION],		"�ı�����" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_AGILITY],			"�ı�����" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_MAGIC],				"�ı�ħ��" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_INTELLIGENCE],		"�ı��֪" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_CHARM],				"�ı�����" );
			MacroGetFieldFloat( pItemStatus->fChanged_ExpMul,						"����ֵ�ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Physics],		"�������ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Magic],		"ħ��ǿ�ȸı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Frost],		"���������ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Blaze],		"���湥���ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Thunder],		"�׵繥���ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Poison],		"�׶������ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Physics],		"�������ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Magic],		"ħ��ǿ�ȸı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Frost],		"���������ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Blaze],		"���湥���ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Thunder],		"�׵繥���ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Poison],		"�׶������ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_PhysicsDefPer,				"��������ı�%" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Physics],		"��������ı�" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Frost],		"��������" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Blaze],		"���濹��" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Thunder],		"�׵翹��" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Poison],		"�׶�����" );
			MacroGetFieldInt( pItemStatus->stChangWeapon_Attribute,				"�������Ըı�" );
			MacroGetFieldInt( pItemStatus->stChangWeapon_Only,					"����ר��״̬" );
			MacroGetFieldInt( pItemStatus->stChanged_FianHurtPer,				"�˺��ı�(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_FianHurt,					"�˺��ı�" );			
			MacroGetFieldInt( pItemStatus->stMagic_FreeHurtPer,					"ħ��ֵ�ֿ��˺�(%)" );
			MacroGetFieldInt( pItemStatus->stMagic_FreeHurt,					"ħ��ֵ�ֿ��˺�" );	
			MacroGetFieldInt( pItemStatus->stChanged_HPMaxPer,					"�������ֵ(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_HPMax,						"�������ֵ" );
			MacroGetFieldInt( pItemStatus->stChanged_MPMaxPer,					"ħ�����ֵ(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_MPMax,						"ħ�����ֵ" ); 
			MacroGetFieldInt( pItemStatus->stResume_HP,							"�����ָ�" );
			MacroGetFieldInt( pItemStatus->stResume_MP,							"ħ���ָ�" ); 
			MacroGetFieldInt( pItemStatus->stChanged_HP,						"�ı�����" );
			MacroGetFieldInt( pItemStatus->stChanged_MP,						"�ı�ħ��" ); 
			MacroGetFieldInt( pItemStatus->stChanged_AttRect,					"�ı乥������" );
			MacroGetFieldInt( pItemStatus->stChanged_Hit,						"��������" ); 
			MacroGetFieldInt( pItemStatus->stChanged_Hedge,						"��������" );
			MacroGetFieldInt( pItemStatus->stChanged_FrenzyPer,					"��������" ); 
			MacroGetFieldFloat( pItemStatus->fChanged_FrenzyVal,					"��������" );
			MacroGetFieldInt( pItemStatus->stChanged_ReboundVal,				"�˺�����" ); 
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Physics],	"�����˺�����" );	
			//MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Magic],	"�����˺�����" );	
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Frost],		"�����˺�����" );			
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Blaze],		"�����˺�����" );
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Thunder],	"�׵��˺�����" );		
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Poison],		"�׶��˺�����" );		
			MacroGetFieldInt( pItemStatus->stStatusFree,							"״̬����" ); 
			MacroGetFieldInt( pItemStatus->stChanged_StatusHitPer,					"״̬�ֿ�" ); 
			MacroGetFieldBool( pItemStatus->bHedgeNull,								"���ӻر�" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraHPRate,						"��Ѫ����" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraHPVal,						"��Ѫֵ" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraMPRate,						"��ħ����" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraMPVal,						"��ħֵ" ); 
			MacroGetFieldFloat( pItemStatus->fMoveSpeedChanged,						"�ƶ��ٶ�" ); 
			MacroGetFieldInt( pItemStatus->stAttSpeedChanged,						"�����ٶ�" ); 
			MacroGetFieldBool( pItemStatus->bIsMoveAtt,								"�ƶ�����" ); 
			MacroGetFieldInt( pItemStatus->stPrepSpeedChanged,						"�����ٶ�" ); 
			MacroGetFieldBool( pItemStatus->bIsMove,								"�����ƶ�" ); 
			MacroGetFieldBool( pItemStatus->bIsAtt,									"����������" ); 
			MacroGetFieldBool( pItemStatus->bIsUsingMagic,							"����ʹ�÷���" ); 
			MacroGetFieldBool( pItemStatus->bIsUsingTools,							"����ʹ�õ���" ); 
			MacroGetFieldBool( pItemStatus->bIsRandWalk,							"�������" ); 
			MacroGetFieldBool( pItemStatus->bCanFindByMonster,						"���﷢��" ); 
			MacroGetFieldInt( pItemStatus->stChanged_MonsterView,					"������ä" ); 
			MacroGetFieldInt( pItemStatus->stChanged_MonsterEnmity,					"����������" ); 
			MacroGetFieldInt( pItemStatus->stAttNumFree,							"���������" ); 
			MacroGetFieldBool( pItemStatus->bConfusionMonster,						"ʹ�ù��ﻥ��" ); 
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Frost],			"�����˺�" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Blaze],			"�����˺�" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Thunder],		"�׵��˺�" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Poison],			"�׶��˺�" );

			//MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Frost],			"�����˺�" );

			MacroGetFieldInt( pItemStatus->stComposeOdds,	"�ϳɼ���" );
			MacroGetFieldInt( pItemStatus->stRefineOdds,	"��������" );
			MacroGetFieldInt( pItemStatus->stIntensifyOdds,	"ǿ������" );
			MacroGetFieldInt( pItemStatus->stInlayOdds,		"��Ƕ����" );

			MacroGetFieldInt( pItemStatus->stChangedPhy_Hurt,			"�����˺�" );
			MacroGetFieldInt( pItemStatus->stChangedPhy_HurtPer,			"�����˺�(%)" );

			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Frost],			"�����˺�(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Blaze],			"�����˺�(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Thunder],		"�׵��˺�(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Poison],			"�׶��˺�(%)" );

			bReadSucc = true;
			break;
		}

		if( bReadSucc )
		{
			//��ӵ���Ʒ������
			AddToMap( pItemStatus );

			//����һ��״̬����
			if(pItemStatus->ustItemID>=StartID_Status)
			{
				int index;
				index = pItemStatus->ustItemID-StartID_Status;
				m_StatusArray[index][pItemStatus->ustLevel] = *pItemStatus;

				if(pItemStatus->ustLevel==1)
				{
					m_StatusArray[index][ 0 ] = *pItemStatus;
				}
			}
		}
		else
		{
			//			delete( pItemStatus );
		}
	}
}

CItemDetail::SItemCommon *CItemDetail::GetItemByID( unsigned short ustItemID )
{
	/*	mapNameItem::iterator it;
	it = m_mapNameItem.find( ustItemID );
	if( it == m_mapNameItem.end() )
	return 0;

	return (*it).second;*/
	if( ustItemID >= m_vectorItem.size() )
		return 0;
	return m_vectorItem[ ustItemID ];
}

//ȡ�ö�Ӧ���ߵ�����
unsigned char	CItemDetail::GetItemType( unsigned short ustItemID)
{
	SItemCommon *pItem = GetItemByID( ustItemID );
	if( pItem )
	{
		return pItem->ucItemType;
	}
	return ITEMTYPE_MAX;
}

CItemDetail::SItemCommon *CItemDetail::GetItem( unsigned short ustItemID,int iItemType )
{
	SItemCommon *pItem = GetItemByID( ustItemID );
	if( pItem )
	{
		if( iItemType != pItem->ucItemType )
			return 0;
	}
	return pItem;
}
CItemDetail::SItemCommon *CItemDetail::GetItemByNameAndLevel( char*szItemName, int nLevel )
{
	CMapStrToIDMgr::RecordSet* pSet = m_ItemFinder.GetRecordSetByName( szItemName );
	if( !pSet )
		return NULL;
	for( int nRecord = 0; nRecord < pSet->vectorRecord.size(); nRecord++ )
	{
		CMapStrToIDMgr::Record* pRecord = &pSet->vectorRecord[nRecord];

		if( stricmp( pRecord->pszName, szItemName ) == 0 )
		{
			SItemCommon* pItem = (SItemCommon*)pRecord->pDst;
			if( pItem &&
				pItem->ustLevel == nLevel )
			{
				return pItem;
			}
		}
	}
	return NULL;
}

CItemDetail::SItemCommon *CItemDetail::GetItemByName( char*szItemName )
{
	return (CItemDetail::SItemCommon *)m_ItemFinder.GetDstByName( szItemName );
	//mapNameItem::iterator itName;
	//std::string strFind = szItemName;

	//itName = m_mapNameItem.find( strFind );
	//if( itName == m_mapNameItem.end() )
	//	return 0;

	//return (*itName).second;
	return NULL;
}

//ĳ��ITEM(��������Ʒ)Ӧ�÷����ĸ�����
short CItemDetail::GetItemBelongBag( unsigned short ustItemID )
{
	GetErrorLog()->logString( "�ú�������!!!!!!" );

	//CItemDetail::SItemCommon *pItem;
	//pItem = GetItemByID( ustItemID );
	//if(!pItem)
	//	return -1;

	//switch(pItem->ucItemType)
	//{
	////case ITEMTYPE_REEL:
	////	return ArabicNights::BagTypeReel;
	////	break;
	////case ITEMTYPE_MATERIAL:
	////	return ArabicNights::BagTypeMaterial;
	////	break;
	////case ITEMTYPE_MEDAL:
	////	return ArabicNights::BagTypeMedal;
	////	break;
	////case ITEMTYPE_TASK:
	////case ITEMTYPE_MAGICITEM:
	////	return ArabicNights::BagTypeOther;
	////	break;
	////case ITEMTYPE_RESTORE:
	////	return ArabicNights::BagTypeUse;
	////	break;
	////case ITEMTYPE_WEAPON:
	////case ITEMTYPE_ARMOUR:
	////	return ArabicNights::BagTypeEquip;
	////	break;
	//case ITEMTYPE_REEL:
	//case ITEMTYPE_MATERIAL:
	//case ITEMTYPE_MEDAL:
	//case ITEMTYPE_TASK:
	//case ITEMTYPE_MAGICITEM:
	//case ITEMTYPE_RESTORE:
	//case ITEMTYPE_WEAPON:
	//case ITEMTYPE_ARMOUR:
	//	return ArabicNights::BagTypePack;
	//	break;

	//case ITEMTYPE_SKILL:
	//	return ArabicNights::BagTypeSkill;
	//	break;

	//case ITEMTYPE_OTHER:
	//	return -1;
	//	break;

	//case ITEMTYPE_STONE:
	//	return ArabicNights::BagTypeSymbolstone;
	//	break;

	//case ITEMTYPE_ACTION:
	//	{
	//		SItemAction *pAction = (SItemAction *)pItem;
	//		switch(pAction->stType)
	//		{
	//		case 0:
	//			return ArabicNights::BagTypeBaseaction;
	//			break;
	//		//case 1:
	//		//	return ArabicNights::BagTypeCommunityaction;
	//		//	break;
	//		//case 2:
	//		//	return ArabicNights::BagTypeSocialaction;
	//		//	break;
	//		}
	//	}
	//	break;
	//}
	return -1;
}

//Get Modulus
CItemDetail::SCharModulus *CItemDetail::GetCharModulusByName( const char *szProfessionName )
{
	mapCharModulus::iterator itModulus;
	std::string strFind = szProfessionName;

	itModulus = m_mapCharModulus.find( strFind );
	if( itModulus == m_mapCharModulus.end( ) )
		return NULL;

	return (*itModulus).second;
}

bool CItemDetail::LoadProfession( char *szFile )
{
	CSlkReader reader;
	if( !reader.ReadFromFile( szFile ) )
	{
		GetErrorLog()->logString( "profession.slk not find");
		return false;
	}

	int iCol;
	//int iValue;
	int iRet;
	SProfession profession;

	int iRow = 2;
	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;

		iCol = 1;

		//ְҵ����	
		std::string strProfessionName;
		//if( !reader.GetStringField( iCol,profession.szName) )
		if( !reader.GetStringField( iCol,strProfessionName) )
		{
			GetErrorLog()->logString( "ְҵ����ȱʧ");
			continue;
		}
		profession.dwNameAddr = AllocStringCopy( strProfessionName.c_str() );
		iCol ++;

		std::string strProfessionDesc;
		//if( !reader.GetStringField( iCol,profession.szDesc))
		if( !reader.GetStringField( iCol,strProfessionDesc))
		{
			GetErrorLog()->logString( "profession desc not find" );
			continue;
		}
		profession.dwDescAddr = AllocStringCopy( strProfessionDesc.c_str() );
		iCol ++;

		profession.stType = ProfessionType_Normal;

		if( !m_mapProfession.insert( 
			//mapProfession::value_type(profession.szName.c_str(),(short)m_vecProfession.size() ) ).second )
			mapProfession::value_type(profession.GetName(),(short)m_vecProfession.size() ) ).second )
		{
			OutputSlkLoadingMessage( "\tְҵ������%s\r\n", profession.GetName() );// profession.szName );
			GetErrorLog()->logString( "prefession name redefine!" );
			continue;
		}
		m_vecProfession.push_back( profession );
	}
	return true;
}

CItemDetail::SProfession *CItemDetail::GetProfession( int iIndex )
{
	if( iIndex < 0 || iIndex >= (int )m_vecProfession.size() )
		return 0;
	return &m_vecProfession[ iIndex ];
}

int	CItemDetail::GetProfessionNum( void )
{
	return (int)m_vecProfession.size();
}

int CItemDetail::GetProfessionID( char *szName )
{
	mapProfession::iterator it;
	it = m_mapProfession.find( szName ); 
	if( m_mapProfession.end() == it )
	{
		return -1;
	}
	return (*it).second;
}

CItemDetail::SProfession	*CItemDetail::GetProfession( char *szName )
{
	return GetProfession( GetProfessionID( szName) );
}

int CItemDetail::GetSkillIndexByID( unsigned short ustSkillItemID )
{
	mapSkillNO::iterator it;
	it = m_mapSkillNO.find( ustSkillItemID );
	if( it == m_mapSkillNO.end() )
		return -1;
	return it->second;
}

CItemDetail::SItemSkill * CItemDetail::GetSkillByIndex( int iIndex )
{
	if( iIndex < 0 || iIndex >= (int)m_vecSkill.size() )
		return 0;
	SItemCommon * pCommon = GetItemByID( m_vecSkill[ iIndex ] );
	if( !pCommon || pCommon->ucItemType != ITEMTYPE_SKILL )
		return 0;
	return (SItemSkill*)pCommon;
}
//----
//----
CItemDetail::SItemSkill * CItemDetail::GetSkillByID(unsigned short ustSkillItemID,  unsigned short ustSkillLevel)
{
	if( !GetItemByID( ustSkillItemID ) )
		return NULL;
	if(ustSkillItemID<StartID_Skill)
		return NULL;

	int index;
	index = ustSkillItemID-StartID_Skill;
	//
	if (index<0 || index>=MaxNum_Skill)
		return 0;

	if (ustSkillLevel<0 || ustSkillLevel>=MaxLevel_Skill)
		return 0;
	//
	return &(m_SkillArray[index][ustSkillLevel]);
}
//��ȡ״̬����غ���
CItemDetail::SItemStatus* CItemDetail::GetStatusByID( SItemSkill *pSkill )
{
	if( pSkill )
	{
		if( pSkill->ustMeAddStatusID != -1 )
			return GetStatusByID( pSkill->ustMeAddStatusID, pSkill->ustMeAddStatusLevel );

		if( pSkill->ustDstAddStatusID != -1 )
			return GetStatusByID( pSkill->ustDstAddStatusID, pSkill->ustDstAddStatusLevel );
	}

	return NULL;
}
//��ȡ״̬����غ���
CItemDetail::SItemStatus* CItemDetail::GetStatusByID( unsigned short ustStatusItemID, unsigned short ustStatusLevel )
{
	if( ustStatusItemID < StartID_Status )
		return NULL;

	int index;
	index = ustStatusItemID - StartID_Status;

	if( index < 0 || index >= MaxNum_Status )
		return 0;

	if( ustStatusLevel < 0 || ustStatusLevel >= MaxLevel_Status )
		return 0;

	return &(m_StatusArray[index][ustStatusLevel]);
}

int CItemDetail::FindMonsterIndexByName( char *szName )
{
	mapMonster::iterator it;
	it = m_mapMonster.find( szName );
	if( m_mapMonster.end() == it )
		return -1;
	return it->second;
}

CItemDetail::SMonster *CItemDetail::GetMonster( int iIndex )
{
	if( iIndex < 0 || iIndex >= (int)m_vecMonster.size() )
		return 0;
	assert( iIndex == m_vecMonster[ iIndex ].iMonsterID );
	return &m_vecMonster[ iIndex ];
}

bool CItemDetail::LoadMonster( char *szFile )
{
	CSlkReader reader;
	if( !reader.ReadFromFile( szFile ) )
	{
		//ȡ�µ�slk��Դ
		GetErrorLog()->logString( "monster.slk not find" );
		return false;
	}

	int iRow = 2;
	int iCol;
	int iRet;
	int iValue;
	float fValue;
	SMonster monster;
	std::string strTemp;

	std::string strCreatureSound;
	std::string strMonsterName;
	std::string strMonsterSkin;

	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;

		iCol = 1;

		//��������

		//if( !reader.GetStringField( iCol,monster.strName) )
		if( !reader.GetStringField( iCol,strMonsterName) )
		{
			OutputSlkLoadingMessage( "\t  ����������ֳ���!\r\n" );
			GetErrorLog()->logString( " monster.slk ����������ֳ���");
			goto load_error;
		}
		monster.dwNameAddr = AllocStringCopy( strMonsterName.c_str() );
		iCol ++;

		//ģ��ID
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  �������ģ��ID����!\r\n" );
			GetErrorLog()->logString( "monster.slk �������ģ��ID����");
			goto load_error;
		}
		monster.iModelID = iValue;
		iCol ++;

		//��������ģ��

		//if( !reader.GetStringField( iCol,monster.strCreatureSound ) )
		if( !reader.GetStringField( iCol, strCreatureSound ) )
		{
			OutputSlkLoadingMessage( "\t  �����������ģ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk �����������ģ�����");
			goto load_error;
		}
		monster.dwCreatureSoundAddr = AllocStringCopy( strCreatureSound.c_str() );

		iCol ++;

		//�������
		if( !GetStringField( &reader, iCol, strTemp ))
		{
			OutputSlkLoadingMessage( "\t  �������������!\r\n" );
			GetErrorLog()->logString( "monster.slk �������������");
			goto load_error;
		}
		monster.stMonsterType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
			g_szMonsterType, sizeof(g_szMonsterType)/sizeof( char* ) );
		iCol ++;

		//��������
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ����������������!\r\n" );
			GetErrorLog()->logString( "monster.slk ����������������");
			goto load_error;
		}
		monster.stBodySize = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t ������Ｖ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk ������Ｖ�����");
			goto load_error;
		}
		monster.stLevel = iValue;
		iCol ++;

		//����ֵ
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t ���뾭��ֵ����!\r\n" );
			GetErrorLog()->logString( "monster.slk ���뾭��ֵ����");
			goto load_error;
		}
		monster.stRewardExp = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t ������������!\r\n" );
			GetErrorLog()->logString( "monster.slk ��������ֵ����");
			goto load_error;
		}
		monster.stStrength = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t �������ʳ���!\r\n" );
			GetErrorLog()->logString("monster.slk �������ʳ���");
			goto load_error;
		}
		monster.stConstitution = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t �������ݳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk �������ݳ���");
			goto load_error;
		}
		monster.stAgility = iValue;
		iCol ++;

		//ħ��
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t ����ħ������!\r\n" );
			GetErrorLog()->logString( "monster.slk ����ħ������");
			goto load_error;
		}
		monster.stMagic = iValue;
		iCol ++;

		//��֪
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t �����֪����!\r\n" );
			GetErrorLog()->logString( "monster.slk �����֪����");
			goto load_error;
		}
		monster.stIntelligence = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t ������������!\r\n" );
			GetErrorLog()->logString( "monster.slk ������������");
			goto load_error;
		}
		monster.stCharm = iValue;
		iCol ++;

		//���HP
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ����������HP����!\r\n" );
			GetErrorLog()->logString( "monster.slk ����������HP����!");
			goto load_error;
		}
		monster.stHPMax = iValue;
		iCol ++;

		//���MP
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ����������MP����!\r\n" );
			GetErrorLog()->logString( "monster.slk ����������MP����!");
			goto load_error;
		}
		monster.stMPMax = iValue;
		iCol ++;

		// HP�ָ��ٶ�
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ��������HP����!\r\n" );
			GetErrorLog()->logString( "monster.slk ��������HP����!");
			goto load_error;
		}
		monster.stHPRestore = iValue;
		iCol ++;

		// MP�ָ��ٶ�
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ��������MP����!\r\n" );
			GetErrorLog()->logString( "monster.slk ��������MP����!");
			goto load_error;
		}
		monster.stMPRestore = iValue;
		iCol ++;

		//��ȷֵ
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ������������ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ������������ʳ���!");
			goto load_error;
		}
		monster.stExact = iValue;
		iCol ++;

		//�����
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  ����������ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����������ʳ���!");
			goto load_error;
		}
		monster.stDodge = iValue;
		iCol ++;

		//��Ұ
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������Ұ����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������Ұ����!");
			goto load_error;
		}
		monster.stView = iValue;
		iCol ++;

		//��С������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ������С����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ������С����������!");
			goto load_error;
		}
		monster.stPhysicAttMin = iValue;
		iCol ++;

		//���������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �����������������!\r\n" );
			GetErrorLog()->logString( "monster.slk  �����������������!");
			goto load_error;
		}
		monster.stPhysicAttMax = iValue;
		iCol ++;

		//��Сħ������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ������Сħ����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ������Сħ����������!");
			goto load_error;
		}
		monster.stMagicAttMin = iValue;
		iCol ++;

		//���ħ������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �������ħ����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  �������ħ����������!");
			goto load_error;
		}
		monster.stMagicAttMax = iValue;
		iCol ++;

		//�����ٶ�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���빥���ٶȳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���빥���ٶȳ���!");
			goto load_error;
		}
		monster.stAttackRate = iValue;
		iCol ++;

		//��������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뱩�����ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뱩�����ʳ���!");
			goto load_error;
		}
		monster.stCriticalRate = iValue;
		iCol ++;

		//�������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������������!");
			goto load_error;
		}
		monster.stPhysicDef = iValue;
		iCol ++;

		//ħ������
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����ħ����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����ħ����������!");
			goto load_error;
		}

		monster.stMagicDef = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  �����������!");
			goto load_error;
		}
		monster.stFrostAtt = iValue;
		iCol ++;

		//��
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����𹥳���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����𹥳���!");
			goto load_error;
		}
		monster.stBlazeAtt = iValue;
		iCol ++;

		//�׹�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �����׹�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  �����׹�����!");
			goto load_error;
		}
		monster.stThunderAtt = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���붾������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���붾������!");
			goto load_error;
		}
		monster.stPoisonAtt = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  �����������!");
			goto load_error;
		}
		monster.stFrostDef = iValue;
		iCol ++;

		//���
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����������!");
			goto load_error;
		}
		monster.stBlazeDef = iValue;
		iCol ++;

		//�׷�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  �����׷�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  �����׷�����!");
			goto load_error;
		}
		monster.stThunderDef = iValue;
		iCol ++;

		//����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���붾������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���붾������!");
			goto load_error;
		}
		monster.stPoisonDef = iValue;
		iCol ++;

		//�����׷��ʱ��
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����׷��ʱ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����׷��ʱ�����!");
			goto load_error;
		}
		monster.dwCatchTime = iValue * 1000;
		iCol ++;

		//������ƶ��ٶ�
		if( !reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ��������ƶ��ٶȳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ��������ƶ��ٶȳ���!");
			goto load_error;
		}
		monster.fMoveSpeed = fValue;
		iCol ++;

		//����ʹ�õļ���1
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����������ʹ�õļ���1����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����������ʹ�õļ���1����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 0 ] = iValue;
		else
			monster.iSkillID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//����ʹ�õļ���2
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����������ʹ�õļ���2����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����������ʹ�õļ���2����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 1 ] = iValue;
		else
			monster.iSkillID[ 1 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//����ʹ�õļ���3
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ����������ʹ�õļ���3����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ����������ʹ�õļ���3����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 2 ] = iValue;
		else
			monster.iSkillID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//����1�ȼ�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��1�ȼ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��1�ȼ�����!");
			goto load_error;
		}
		monster.stSkillLevel[ 0 ] = iValue;
		iCol ++;

		//����2�ȼ�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��2�ȼ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��2�ȼ�����!");
			goto load_error;
		}
		monster.stSkillLevel[ 1 ] = iValue;
		iCol ++;

		//����3�ȼ�
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��3�ȼ�����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��3�ȼ�����!");
			goto load_error;
		}
		monster.stSkillLevel [ 2 ] = iValue;
		iCol ++;

		//����1ʹ�ø���
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��1ʹ�ø��ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��1ʹ�ø��ʳ���!");
			goto load_error;
		}
		monster.stSkillRate[ 0 ] = iValue;
		iCol ++;

		//����2ʹ�ø���
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��2ʹ�ø��ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��2ʹ�ø��ʳ���!");
			goto load_error;
		}
		monster.stSkillRate[ 1 ] = iValue;
		iCol ++;

		//����3ʹ�ø���
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���뼼��3ʹ�ø��ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���뼼��3ʹ�ø��ʳ���!");
			goto load_error;
		}
		monster.stSkillRate[ 2 ] = iValue;
		iCol ++;

		//���ܵ������Ʒ1
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ1����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ1����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 0 ] = iValue;
		else
			monster.stGoodDropID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//���ܵ������Ʒ1����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ1���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ1���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 0 ] = iValue;
		iCol ++;

		//���ܵ������Ʒ2
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ2����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ2����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 1 ] = iValue;
		else
			monster.stGoodDropID[ 1 ] = ArabicNights::ErrorUnsignedShortID;

		iCol ++;

		//���ܵ������Ʒ2����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ2���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ2���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 1 ] = iValue;
		iCol ++;

		//���ܵ������Ʒ3
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ3����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ3����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 2 ] = iValue;
		else
			monster.stGoodDropID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//���ܵ������Ʒ3����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ3���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ3���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 2 ] = iValue;
		iCol ++;

		//���ܵ������Ʒ4
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ4����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ4����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 3 ] = iValue;
		else
			monster.stGoodDropID[ 3 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//���ܵ������Ʒ4����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ4���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ4���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 3 ] = iValue;
		iCol++;

		//���ܵ������Ʒ5
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ5����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ5����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 4 ] = iValue;
		else
			monster.stGoodDropID[ 4 ] = ArabicNights::ErrorUnsignedShortID;

		iCol ++;

		//���ܵ������Ʒ5����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ5���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ5���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 4 ] = iValue;
		iCol ++;

		//���ܵ������Ʒ6
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ6����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ6����!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 5 ] = iValue;
		else
			monster.stGoodDropID[ 5 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//���ܵ������Ʒ6����
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ���������ܵ������Ʒ6���ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ���������ܵ������Ʒ6���ʳ���!");
			goto load_error;
		}
		monster.stGoodDropRate[ 5 ] = iValue;
		iCol ++;

		//�����Ǯ��С
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ��������Ǯ��С����!\r\n" );
			GetErrorLog()->logString( "monster.slk  ��������Ǯ��С����!");
			goto load_error;
		}
		monster.stDropMinMoney = iValue;
		iCol ++;

		//�����Ǯ���
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  ��������Ǯ������!\r\n" );
			GetErrorLog()->logString( "monster.slk  ��������Ǯ������!");
			goto load_error;
		}
		monster.stDropMaxMoney = iValue;
		iCol ++;

		//��Ʒ���䱶��
		if( !reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t  ������Ʒ���䱶�ʳ���!\r\n" );
			GetErrorLog()->logString( "monster.slk  ������Ʒ���䱶�ʳ���!");
			goto load_error;
		}
		monster.fItemDropMultipleRate = fValue;
		iCol ++;

		//����Ƥ��
		if( !reader.GetStringField( iCol,strMonsterSkin ) )
		{
			OutputSlkLoadingMessage( "\t  �������Ƥ������!\r\n" );
			GetErrorLog()->logString( " monster.slk �������Ƥ������");
			goto load_error;
		}
		monster.dwSkinAddr = AllocStringCopy( strMonsterSkin.c_str() );
		iCol ++;




		////Reset 
		//monster.stGoodDropID[ 6 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 7 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 8 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 9 ] = ArabicNights::ErrorUnsignedShortID;

		////׷����Χ	
		//if( !reader.GetIntField( iCol, iValue ))
		//{
		//	OutputSlkLoadingMessage( "\t  �������׷����Χ����!\r\n" );
		//	assert(false && "monster.slk  �������׷����Χ����!");
		//	goto load_error;
		//}
		//monster.stCatchArea = iValue;
		//iCol ++;

		//AI����
		//if( !GetStringField( &reader, iCol, strTemp) )
		//{
		//	OutputSlkLoadingMessage( "Error:�������AI���ͳ���!\r\n" );
		//	assert(false && "monster.slk  �������AI���ͳ���!");
		//	continue;
		//}
		//monster.stAI = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szAiType, sizeof(g_szAiType)/sizeof( char* ) );

		//if( monster.stAI == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:�������AI���ͳ���!\r\n" );
		//	assert(false && "monster.slk  �������AI���ͳ���!");
		//	continue;
		//}
		//iCol ++;

		//////��������
		////if( !GetStringField( &reader, iCol, strTemp ))
		////{
		////	OutputSlkLoadingMessage( "Error:����������ͳ���!\r\n" );
		////	assert(false && "monster.slk  ����������ͳ���!");
		////	continue;
		////}
		////monster.stMonsterType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		////	g_szMonsterType, sizeof(g_szMonsterType)/sizeof( char* ) );

		//if( monster.stMonsterType == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:����������ͳ���!\r\n" );
		//	assert(false && "monster.slk  ����������ͳ���!");
		//	continue;
		//}
		//iCol++;

		////���������ְҵ
		//if( !GetStringField( &reader, iCol, strTemp ))
		//{
		//	OutputSlkLoadingMessage( "Error:������������ְҵ����!\r\n" );
		//	assert(false && "monster.slk  ������������ְҵ����!");
		//	continue;
		//}
		//monster.stHateProfession = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szMonsterHateEnemy, sizeof(g_szMonsterHateEnemy)/sizeof( char* ) );

		//if( monster.stHateProfession == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:������������ְҵ����!\r\n" );
		//	assert(false && "monster.slk  ������������ְҵ����!");
		//	continue;
		//}
		//iCol ++;

		////���ﷴ�������ȼ���
		//if( !GetStringField( &reader, iCol, strTemp ))
		//{
		//	OutputSlkLoadingMessage( "Error:������ﷴ�������ȼ������!\r\n" );
		//	assert(false && "monster.slk  ������ﷴ�������ȼ������!");
		//	continue;
		//}
		//monster.stFightBackType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szMonsterFightBackEnemy, sizeof(g_szMonsterFightBackEnemy)/sizeof( char* ) );

		//if( monster.stFightBackType == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:������ﷴ�������ȼ������!\r\n" );
		//	assert(false && "monster.slk  ������ﷴ�������ȼ������!");
		//	continue;
		//}
		//iCol ++;

		////TC����
		//iCol ++;

		//if( !reader.GetIntFieldByName( "�����Ǯ��С", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk �����Ǯ��С\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stDropMinMoney = iValue;

		//if( !reader.GetIntFieldByName( "�����Ǯ���", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk �����Ǯ���\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stDropMaxMoney = iValue;

		//if( !reader.GetIntFieldByName( "���ļ���", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk ���ļ���\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stCriticalRate = iValue;

		//if( !reader.GetIntFieldByName( "BOSS���", iValue ) )
		//{
		//	OutputSlkLoadingMessage( "Error:����BOSS������!\r\n" );
		//	assert(false && "monster.slk  ����BOSS������!");
		//	continue;
		//}
		//iCol ++;
		//monster.bBoss = iValue == 1 ? true : false;

		//if( !reader.GetIntFieldByName( "��ʾ��������", iValue ) )
		//{
		//	OutputSlkLoadingMessage( "Error:������ʾ�������ͳ���!\r\n" );
		//	assert(false && "monster.slk  ������ʾ�������ͳ���!");
		//	continue;
		//}
		//iCol ++;
		//monster.stDisplayNameType = iValue;

		//if( !reader.GetStringFieldByName( "��Ʒ����ģ��", strTemp ) )
		//{
		//	monster.strItemDropTemplate = "<void>";
		//}
		//else
		//{
		//	monster.strItemDropTemplate = strTemp;
		//}
		//iCol ++;

		//if( !reader.GetFloatFieldByName( "��Ʒ���䱶��", fValue) )
		//{
		//	monster.fItemDropMultipleRate = 0.0f;
		//}
		//else
		//{
		//	monster.fItemDropMultipleRate = fValue;
		//}
		//iCol ++;

		//if ( !reader.GetIntFieldByName( "��С������" ,iValue) )	
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicAttMin = iValue;
		//iCol++;

		//if(!reader.GetIntFieldByName( "���������" , iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicAttMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("��С�������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicDefMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("����������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicDefMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("��Сħ������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicAttMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("���ħ������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicAttMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("��Сħ������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicDefMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("���ħ������",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicDefMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("��׼",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stExact = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("����",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stDodge = iValue;
		//iCol++;

		monster.iMonsterID = m_vecMonster.size();

		//�������
		//m_mapMonster.insert( mapMonster::value_type( monster.strName.c_str(),(short)m_vecMonster.size() ) );
		m_mapMonster.insert( mapMonster::value_type( monster.GetName(),(short)m_vecMonster.size() ) );
		//����vector
		m_vecMonster.push_back( monster );
		continue;
load_error:
		OutputSlkLoadingMessage( "\tmonster.slk �� %d ������ʧ��!\r\n",iRow-1 );
		continue;
	}

	return true;
}

bool IsNormalAttack( unsigned short ustSkillID )
{
	//if( ustSkillID >= ArabicNights::const_ustNormalAttack0 
	//	&& ustSkillID <= ArabicNights::const_ustNormalAttack6 )
	//	return true;
	switch( ustSkillID )
	{
	case ArabicNights::const_ustNormalAttack0:
		//case ArabicNights::const_ustNormalAttack1:
		//case ArabicNights::const_ustNormalAttack2:
		//case ArabicNights::const_ustNormalAttack3:
		//case ArabicNights::const_ustNormalAttack5:
		//case ArabicNights::const_ustNormalAttack6:
		//case ArabicNights::const_ustMonsterAttack0:
		//case ArabicNights::const_ustMonsterAttack2:
		//case ArabicNights::const_ustMonsterAttack3:
		//case ArabicNights::const_ustMonsterAttack4:
		//case ArabicNights::const_ustMonsterAttack5: 
		return true;
	default:
		break;
	}
	return false;
}

DWORD CItemDetail::GetSkillHoldTime(unsigned short ustSkillID, unsigned short ustSkillLevel)
{
	return GetSkillHoldTime( GetSkillByID( ustSkillID, ustSkillLevel));
}

DWORD CItemDetail::GetSkillHoldTime(SItemSkill *pSkill)
{
	//
	if (NULL == pSkill)
		return 0;
	//
	return (pSkill->ustHoldTime);
}


bool CItemDetail::SItemCommon::IsExclusive()
{
	// �Ƿ��ռ
	switch( ucItemType )
	{
	case CItemDetail::ITEMTYPE_RESTORE:
	case CItemDetail::ITEMTYPE_MATERIAL:
	case CItemDetail::ITEMTYPE_GEM:
	case CItemDetail::ITEMTYPE_CREATEITEMRULE:
	case CItemDetail::ITEMTYPE_CRYSTAL:
	case CItemDetail::ITEMTYPE_TASK:
	//case CItemDetail::ITEMTYPE_WEAPON:
	//case CItemDetail::ITEMTYPE_ARMOUR:

		return false;
	}		
	return true;
}

CItemDetail::SItemCommon* CItemDetail::GetWeaponItem( int iIndex )
{
	return m_vectorWeaponItem[iIndex];
}

CItemDetail::SItemCommon* CItemDetail::GetArmourItem( int iIndex )
{
	return m_vectorArmourItem[iIndex];
}

CItemDetail::SItemCommon* CItemDetail::GetGloveItem( int iIndex )
{
	return m_vectorGloveItem[iIndex];
}

CItemDetail::SItemCommon* CItemDetail::GetShoeItem( int iIndex )
{
	return m_vectorShoeItem[iIndex];
}

CItemDetail::SItemCommon* CItemDetail::GetCapItem( int iIndex )
{
	return m_vectorCapItem[iIndex];
}

int CItemDetail::GetWeaponNumber( )
{
	return (int)m_vectorWeaponItem.size( );
}

int CItemDetail::GetArmourNumber( )
{
	return (int)m_vectorArmourItem.size( );
}

int CItemDetail::GetGloveNumber( )
{
	return (int)m_vectorGloveItem.size( );
}

int	CItemDetail::GetShoeNumber( )
{
	return (int)m_vectorShoeItem.size( );
}

int CItemDetail::GetCapNumber( )
{
	return (int)m_vectorCapItem.size( );
}

bool CItemDetail::LoadCharModulus( char *szFile )
{
	CSlkReader reader;
	if(!reader.ReadFromFile( szFile ))
	{
		//ȡ�µ�slk��Դ
		GetErrorLog()->logString( "charmodulus.slk not find" );
		return false;
	}

	int iRow = 2;
	int iCol;
	int iRet;
	int iValue;
	float fValue;

	while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
	{
		if(CSlkReader::ret_nothisline==iRet)
			continue;

		SCharModulus *pCharModulus;
		//pCharModulus = new SCharModulus;
		pCharModulus = (SCharModulus*)AllocItem( 0, sizeof( SCharModulus ) ) ;
		if(!pCharModulus)
		{
			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk�ڴ�������" );
			return false;
		}

		iCol = 1;
		std::string strProfessionName;
		//if(!reader.GetStringField( iCol, pCharModulus->szProfessionName))
		if(!reader.GetStringField( iCol, strProfessionName))
		{
			OutputSlkLoadingMessage( "\t  ����ְҵ���ֳ���!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ְҵ���ֳ���" );
			goto load_error;
		}
		pCharModulus->dwProfessionNameAddr = AllocStringCopy( strProfessionName.c_str() );
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ְҵ���г�ʼֵ����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ְҵ���г�ʼֵ����" );
			goto load_error;
		}
		pCharModulus->fHit = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ְҵ�رܳ�ʼֵ����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ְҵ���г�ʼֵ����" );
			goto load_error;
		}
		pCharModulus->fDodge = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ְҵHP��ʼֵ����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ְҵ���г�ʼֵ����" );
			goto load_error;
		}
		pCharModulus->fHp = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ְҵMP��ʼֵ����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ְҵ���г�ʼֵ����" );
			goto load_error;
		}
		pCharModulus->fMp = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��4����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��4����" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��5����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��5����" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fMagAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fMagAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fMagAttMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������ϵ��4����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������ϵ��4����" );
			goto load_error;
		}
		pCharModulus->fMagAttMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������ϵ��5����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������ϵ��5����" );
			goto load_error;
		}
		pCharModulus->fMagAttMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����Ԫ�ع���ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����Ԫ�ع���ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fElementMod1 = fValue;
		iCol++;		

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����������ϵ��4����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����������ϵ��4����" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod4 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fExactMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fExactMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fExactMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fExactMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ر���ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ر���ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fDodgeMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ر���ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ر���ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fDodgeMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ر���ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ر���ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fDodgeMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ر���ϵ��4����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ر���ϵ��4����" );
			goto load_error;
		}
		pCharModulus->fDodgeMod4 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ر���ϵ��5����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ر���ϵ��5����" );
			goto load_error;
		}
		pCharModulus->fDodgeMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ȼ�����ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fLvDefMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HPϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HPϵ��1����" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HPϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HPϵ��2����" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HPϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HPϵ��3����" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����MPϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����MPϵ��1����" );
			goto load_error;
		}
		pCharModulus->fMpMaxMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����MPϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����MPϵ��1����" );
			goto load_error;
		}
		pCharModulus->fMpMaxMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HP�ָ�ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HP�ָ�ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HP�ָ�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HP�ָ�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod2 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����HP�ָ�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����HP�ָ�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����MP�ָ�ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����MP�ָ�ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����MP�ָ�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����MP�ָ�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod2 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����MP�ָ�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����MP�ָ�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��3����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��3����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��4����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��4����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��5����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��5����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��6����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��6����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod6 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ������ϵ��7����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ������ϵ��7����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod7 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����˺�ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����˺�ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fDamMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �����˺�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����˺�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fDamMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fHitRateMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fHitRateMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ��ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ��ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������һ��ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������һ��ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fCriticalAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����ȼ���ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ȼ���ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fLevelDisMod1 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���뾭��ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���뾭��ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fExpMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥���ٶ�ϵ��1����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥���ٶ�ϵ��1����" );
			goto load_error;
		}
		pCharModulus->fAttSpeedMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥���ٶ�ϵ��2����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥���ٶ�ϵ��2����" );
			goto load_error;
		}
		pCharModulus->fAttSpeedMod2 = fValue;
		iCol++;


		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t ������������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ������������" );
			goto load_error;
		}
		pCharModulus->sStrength = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t �������ݳ���!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������ݳ���" );
			goto load_error;
		}
		pCharModulus->sAgility = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t �������ʳ���!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������ʳ���" );
			goto load_error;
		}
		pCharModulus->sConstitution = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t �����֪����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �����֪����" );
			goto load_error;
		}
		pCharModulus->sIntelligence = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t ����ħ������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����ħ������" );
			goto load_error;
		}
		pCharModulus->sMagic = iValue;
		iCol++;


		if( !reader.GetIntFieldByName( "����", iValue ) )
		{
			assert( false );
			continue;
		}
		pCharModulus->sCharm  = iValue;
		iCol ++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ����������ȷֵ����ʼ������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ����������ȷֵ����ʼ������" );
			goto load_error;
		}
		pCharModulus->fWeaponExact = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������ֹ���ϵ������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������ֹ���ϵ������" );
			goto load_error;
		}
		pCharModulus->fRAttMod = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t �������ֹ���ϵ������!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk �������ֹ���ϵ������" );
			goto load_error;
		}
		pCharModulus->fLAttMod = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥��ʱ��ϵ��4(d2)!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥��ʱ��ϵ��4(d2)����" );
			goto load_error;
		}
		pCharModulus->fTimeMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥��ʱ��ϵ��4(d2)����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥��ʱ��ϵ��4(d2)����" );
			goto load_error;
		}
		pCharModulus->fTimeMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥��ʱ��ϵ��4(d2)����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥��ʱ��ϵ��4(d2)����" );
			goto load_error;
		}
		pCharModulus->fTimeMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t ���빥��ʱ��ϵ��4(d2)����!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk ���빥��ʱ��ϵ��4(d2)����" );
			goto load_error;
		}
		pCharModulus->fTimeMod4 = fValue;
		iCol++;

		//�������
		//m_mapCharModulus.insert( mapCharModulus::value_type( pCharModulus->szProfessionName.c_str(), pCharModulus ) );
		m_mapCharModulus.insert( mapCharModulus::value_type( pCharModulus->GetProfessionName(), pCharModulus ) );
		//����vector
		m_vecCharModulus.push_back( pCharModulus );
		continue;

load_error:
		OutputSlkLoadingMessage( "\tcharmodulus.slk �� %d ������ʧ��!\r\n",iRow-1 );
		continue;
	}

	return true;
}
//
//bool CItemDetail::LoadStoneSkill( char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//ȱ�µ�slk��Դ
//		assert( false && "stoneskill.slk not find" );
//		return false;
//	}
//
//	int iRow = 2;
//	int iCol;
//	int iRet;
//	int iValue;
//
//	while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
//	{
//		if(CSlkReader::ret_nothisline==iRet)
//			continue;
//
//		SStoneSkill *pStoneSkill;
//		//pStoneSkill = new SStoneSkill;
//		pStoneSkill = (SStoneSkill*)AllocItem( 0, sizeof( SStoneSkill ) );
//		if(!pStoneSkill)
//		{
//			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//			assert( false && "stoneskill.slk�ڴ�������" );
//			return false;
//		}
//
//		iCol = 1;
//
//		//����ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID����!\r\n" );
//			assert( false && "stoneskill.slk���뼼��ID����" );
//			goto load_error;
//		}
//		pStoneSkill->ustSkillID = iValue;
//		iCol++;		
//
//		//��ʯID1
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t �����ʯID1����!\r\n" );
//			assert( false && "stoneskill.slk�����ʯID1����" );
//			goto load_error;
//		}
//		pStoneSkill->ustStoneID[ 0 ] = iValue;
//		iCol++;
//
//		//��ʯID2
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t �����ʯID2����!\r\n" );
//			assert( false && "stoneskill.slk�����ʯID2����" );
//			goto load_error;
//		}
//		pStoneSkill->ustStoneID[ 1 ] = iValue;
//		iCol++;
//
//		//��ʯID3
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ��ʯID3Ĭ��0xffff!\r\n" );
//			pStoneSkill->ustStoneID[ 2 ] = 0xffff;
//		}
//		else
//		{
//			pStoneSkill->ustStoneID[ 2 ] = iValue;
//		}
//		//
//		{
//			//����map
//			mapStoneSkill::iterator itStoneSkill;
//			itStoneSkill = m_mapStoneSkill.find( pStoneSkill->ustSkillID );
//			if( itStoneSkill == m_mapStoneSkill.end( ) )
//			{
//				m_mapStoneSkill.insert( mapStoneSkill::value_type(pStoneSkill->ustSkillID, pStoneSkill) );
//			}
//			continue;
//		}
//
//load_error:
//		OutputSlkLoadingMessage( "\tstoneskill.slk �� %d ������ʧ��!\r\n",iRow-1 );
//		continue;
//	}
//
//	return true;
//}
//
//CItemDetail::SStoneSkill *CItemDetail::GetStoneSkillByID( unsigned short ustSkillID )
//{
//	mapStoneSkill::iterator itStoneSkill;
//	itStoneSkill = m_mapStoneSkill.find( ustSkillID );
//
//	if( itStoneSkill == m_mapStoneSkill.end( ) )
//		return 0;
//
//	return (*itStoneSkill).second;
//}
//
////��Ż�������Ƭ�ε������Ķ�Ӧ��ϵ
//bool CItemDetail::LoadSkillToSkill( char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//ȱ�µ�slk��Դ
//		assert( false && "skilltoskill.slk not find" );
//		return false;
//	}
//
//	int iRow = 2;
//	int iCol;
//	int iRet;
//	int iValue;
//
//	while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
//	{
//		if(CSlkReader::ret_nothisline==iRet)
//			continue;
//
//		SSkillToSkill *pSkillToSkill;
//		//pSkillToSkill = new SSkillToSkill;
//		pSkillToSkill = (SSkillToSkill*)AllocItem( 0, sizeof( SSkillToSkill ) );
//		if(!pSkillToSkill)
//		{
//			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//			assert( false && "skilltoskill.slk �ڴ�������" );
//			return false;
//		}
//		iCol = 1;
//
//		//��ɱ��ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID����!\r\n" );
//			assert( false && "skilltoskill.slk ���뼼��ID����" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSkillID = iValue;
//		iCol++;		
//
//		//����ID1
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID1����!\r\n" );
//			assert( false && "skilltoskill.slk ���뼼��ID1����" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSubSkillID[ 0 ] = iValue;
//		iCol++;
//
//		//����ID2
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID2����!\r\n" );
//			assert( false && "skilltoskill.slk ���뼼��ID2����" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSubSkillID[ 1 ] = iValue;
//		iCol++;
//
//		//����ID3
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID3Ĭ��0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 2 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//����ID4
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID4Ĭ��0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 3 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 3 ] = iValue;
//		}
//		iCol++;
//
//		//����ID5
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���뼼��ID5Ĭ��0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 4 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 4 ] = iValue;
//		}
//
//		//����map
//		{
//			mapSkillToSkill::iterator itSkillToSkill;
//			itSkillToSkill = m_mapSkillToSkill.find( pSkillToSkill->ustSkillID );
//			if( itSkillToSkill == m_mapSkillToSkill.end( ) )
//			{
//				m_mapSkillToSkill.insert( mapSkillToSkill::value_type(pSkillToSkill->ustSkillID,pSkillToSkill) );
//			}
//			continue;
//		}
//
//load_error:
//		OutputSlkLoadingMessage( "\tskilltoskill.slk �� %d ������ʧ��!\r\n",iRow-1 );
//		continue;
//	}
//
//	return true;
//}
//
////Get SkillToSkill
//CItemDetail::SSkillToSkill* CItemDetail::GetSkillToSkillByID( unsigned short ustSkillID )
//{
//	mapSkillToSkill::iterator itSkillToSkill;
//	itSkillToSkill = m_mapSkillToSkill.find( ustSkillID );
//
//	if(itSkillToSkill==m_mapSkillToSkill.end( ))
//		return 0;
//
//	return (*itSkillToSkill).second;
//}
//
////װ��������Ʒ,ԭ�����Ʒ�Ķ�Ӧ��ϵ
//bool CItemDetail::LoadProduceItem( char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//ȱ�µ�slk��Դ
//		assert( false && "produceitem.slk not find" );
//		return false;
//	}
//
//	int iRow = 2;
//	int iCol;
//	int iRet;
//	int iValue;
//
//	while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
//	{
//		if(CSlkReader::ret_nothisline==iRet)
//			continue;
//
//		SProduceItem *pProduceItem;
//		//pProduceItem = new SProduceItem;
//		pProduceItem = (SProduceItem*)AllocItem( 0, sizeof( SProduceItem ) );
//		if(!pProduceItem)
//		{
//			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//			assert( false && "produceitem.slk �ڴ�������" );
//			return false;
//		}
//		iCol = 1;
//
//		//���ղ�ƷID��������1��
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���ղ�ƷIDĬ��0xffff!\r\n" );
//			pProduceItem->ustResultGoodID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustResultGoodID = iValue;
//		}
//		iCol += 2;	//��������
//
//		//ԭ��1��ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��1��IDĬ��0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 0 ] = iValue;
//		}
//		iCol++;
//
//		//ԭ��1����Ŀ
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��1����ĿĬ��0!\r\n" );
//			pProduceItem->ustMaterialNum[ 0 ] = 1;
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 0 ] = iValue;
//		}
//		iCol++;
//
//		//ԭ��2��ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��2��IDĬ��0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 1 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 1 ] = iValue;
//		}
//		iCol++;
//
//		//ԭ��2����Ŀ
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��2����ĿĬ��0!\r\n" );
//			pProduceItem->ustMaterialNum[ 1 ] = 1;
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 1 ] = iValue;
//		}
//		iCol++;
//
//		//ԭ��3��ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��3��IDĬ��0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//ԭ��3����Ŀ
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ԭ��3����ĿĬ��0!\r\n" );
//			pProduceItem->ustMaterialNum[ 2 ] = 1;			
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//ʹ�õĹ���ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ���빤�ߵ�IDĬ��0xffff!\r\n" );
//			pProduceItem->ustToolID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustToolID = iValue;
//		}
//		iCol++;
//
//		//��С���鼼�ܵ�Ҫ��
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����С���鼼�ܵ�IDĬ��0xffff!\r\n" );
//			pProduceItem->ustSpriteSkillID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustSpriteSkillID = iValue;
//		}
//		iCol++;
//
//		//��С���鼼�ܵȼ���Ҫ��
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����С���鼼�ܵȼ�Ҫ��Ĭ��1!\r\n" );
//			pProduceItem->ustSpriteSkillLevel = 1;
//		}
//		else
//		{
//			pProduceItem->ustSpriteSkillLevel = iValue;
//		}
//		iCol++;
//
//		//����ĳɹ���
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ��������ĳɹ���Ĭ��100!\r\n" );
//			pProduceItem->ustSuccessRate = 100;		
//		}
//		else
//		{
//			pProduceItem->ustSuccessRate = iValue;
//		}
//
//		//����vector
//		m_vecProduceItem.push_back( pProduceItem );
//		continue;
//		//
//		OutputSlkLoadingMessage( "\tproduceitem.slk �� %d ������ʧ��!\r\n",iRow-1 );
//		continue;
//	}
//
//	return true;
//}
//
////��ȡ��Ʒ����,ԭ�����Ʒ�Ķ�Ӧ��ϵ
//CItemDetail::SProduceItem* CItemDetail::GetProduceItem( int iIndex )
//{
//	return m_vecProduceItem[iIndex];
//}
//
////��ȡ��Ӧ��ϵ����Ŀ
//int	CItemDetail::GetProduceItemSize( )
//{
//	return (int)m_vecProduceItem.size( );
//}

//��ȡ���ܵ�������Ϣ
int CItemDetail::CreateSkillDesc( unsigned short ustSkillID, unsigned short ustSkillLevel, 
								 char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
{
	//��ȡ���ܵ���Ϣ
	CItemDetail::SItemSkill *pSkill;
	pSkill = theItemDetail.GetSkillByID( ustSkillID, ustSkillLevel );
	if(!pSkill)
		return 0;

	//��¼����
	int iLineCount = 0;

	//��ʱ����ɫ
	for( int i=0;i<iDescLength;i++ )
	{
		pDescColor[ i ] = 0xff000000;
	}

	//��������
	sprintf( pDesc[iLineCount++], 
		g_CfgItemDesc.m_strSkillName, 
		//pSkill->szItemName.c_str() );
		GetString( pSkill->dwItemNameAddr ) );
	if( iLineCount == iDescLength )
		return iLineCount;

	return iLineCount;	
}

//��ȡ״̬��������Ϣ
int CItemDetail::CreateStatusDesc( unsigned short ustStatusID, unsigned short ustStatusLevel,
								  char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
{
	//��ȡ״̬����Ϣ
	CItemDetail::SItemStatus *pStatus;
	pStatus = theItemDetail.GetStatusByID( ustStatusID, ustStatusLevel );
	if(!pStatus)
		return 0;

	//��¼����
	int iLineCount = 0;

	//��ʱ����ɫ
	for( int i=0;i<iDescLength;i++ )
	{
		pDescColor[ i ] = 0xff000000;
	}

	//״̬������
	sprintf( pDesc[iLineCount++], 
		g_CfgItemDesc.m_strStatusDesc, 
		//pStatus->szItemDesc.c_str() );
		GetString( pStatus->dwItemDescAddr ) );
	if( iLineCount == iDescLength )
		return iLineCount;

	return iLineCount;	
}
//���ȡ��һ���ȼ���Χ�ĵ���
unsigned short CItemDetail::GetRandomLevelRangeItem(int iMinLevel, int iMaxLevel)
{
	int level ;
	if (iMinLevel > 100)
		iMinLevel = 99;
	if (iMaxLevel <=  iMinLevel)
		level = iMinLevel;
	else
		level = rand() % (iMaxLevel - iMinLevel) + iMinLevel;
	//
	if (level < 0)
		return ArabicNights::ErrorUnsignedShortID;
	if (level >= 100)
		return ArabicNights::ErrorUnsignedShortID;
	//
	while (1)
	{
		if (m_vectorLevelItem[level].size() > 0)
			break;
		level ++;
		if (level >= iMaxLevel)
			break;
	}
	//
	if (level >= iMaxLevel)
		return ArabicNights::ErrorUnsignedShortID;
	//
	int rand_num = (int) (rand() % m_vectorLevelItem[level].size());
	//
	return m_vectorLevelItem[level][rand_num]->ustItemID;

}

bool CItemDetail::GetEquipSpecials( ArabicNights::SCharItem* pCharItem,
								   int* pnAddPhyAtt,
								   int* pnAddPhyDef,
								   int* pnAddMagAtt,
								   int* pnAddFrost ,
								   int* pnAddBlaze ,
								   int* pnAddThunder ,
								   int* pnAddPoison ,
								   int* pnNullGemCount,
								   int* pnInlayGemCount )
{
	if ( !pCharItem )
	{
		assert(false);
		return false;
	}
	if( pnNullGemCount ) (*pnNullGemCount)=0;
	if( pnInlayGemCount ) (*pnInlayGemCount)=0;
	if( pnAddPhyAtt ) (*pnAddPhyAtt)=0;
	if( pnAddPhyDef ) (*pnAddPhyDef)=0;
	if( pnAddMagAtt ) (*pnAddMagAtt)=0;
	if (pnAddFrost  ) (*pnAddFrost)=0;
	if(pnAddBlaze  )  (*pnAddBlaze)=0;
	if (pnAddThunder  ) (*pnAddThunder)=0;
	if(pnAddPoison  )  (*pnAddPoison)=0;
	//
	SItemGem* pGem = NULL;
	for( int n=0; n<ArabicNights::SCharItem::e_SpecialCount; n++ )
	{
		if ( pCharItem->extdata.equipdata.specials[n] == 0xff )
		{
			break;
		}
		else if( pCharItem->extdata.equipdata.specials[n] == 0x00 )
		{
			if( pnNullGemCount ) (*pnNullGemCount)++;
		}
		else
		{
			if( pnInlayGemCount ) (*pnInlayGemCount)++;
			//
			pGem = theItemDetail.GetGemByGemCode( pCharItem->extdata.equipdata.specials[n] );
			if ( !pGem )
			{
				assert(false);
				continue;
			}
			if( pnAddPhyAtt )
				(*pnAddPhyAtt) += pGem->ustAddPhyAtt;
			if( pnAddPhyDef )
				(*pnAddPhyDef) += pGem->ustDef[ePlayDef_Physics];
			if( pnAddMagAtt )
				(*pnAddMagAtt) += pGem->ustAddMagAtt;
			if( pnAddFrost )
				(*pnAddPhyDef) += pGem->ustDef[ePlayDef_Frost];
			if( pnAddBlaze )
				(*pnAddPhyDef) += pGem->ustDef[ePlayDef_Blaze];
			if( pnAddThunder )
				(*pnAddPhyDef) += pGem->ustDef[ePlayDef_Thunder];
			if( pnAddPoison )
				(*pnAddPhyDef) += pGem->ustDef[ePlayDef_Poison];

		}
	}
	return true;
}

bool CItemDetail::GetSkillNeedInfo( ArabicNights::SCharBaseInfo *pCharBaseInfo,
								   ArabicNights::SCharOtherDataClient *pCharOtherInfo,
								   int nId, int nLevel, char* szSkillInfo )
{
	if ( !pCharBaseInfo || !pCharOtherInfo )
	{
		assert( pCharBaseInfo );
		assert( pCharOtherInfo );
		return false;
	}
	//
	bool bResutl = true;
	char szInfo[512] = "\n";
	char szTemp[128] = "";
	//
	CItemDetail::SItemSkill *pSkill = NULL;
	pSkill = theItemDetail.GetSkillByID( nId, nLevel );
	if ( !pSkill )
	{
		assert( pSkill );
		return false;
	}
	//
	if ( pSkill->stLearnLevelReq != 0 )
	{
		if( pCharBaseInfo->ustLevel < pSkill->stLearnLevelReq )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ�ȼ�:%ld\n", pSkill->stLearnLevelReq );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stMoneyNeed != 0 )
	{
		if ( pCharBaseInfo->dwMoney < pSkill->stMoneyNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ��Ǯ:%ld\n", pSkill->stMoneyNeed );
		strcat( szInfo, szTemp );
	}
	if( pSkill->stRankNeed > 0 )
	{
		if ( pCharBaseInfo->byOfficialLevel < pSkill->stRankNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		int nCountry = pCharBaseInfo->ucCountry;
		COfficialMgr::Record* r = g_officialMgr.GetRecord( pSkill->stRankNeed );
		sprintf( szTemp, "��Ҫ����:%s\n",r->szOfficialTitle[nCountry] );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stSkillNeed != -1 && pSkill->stSkillLevelNeed != -1 )
	{
		CItemDetail::SItemSkill *pPreSkill = 
			theItemDetail.GetSkillByID( pSkill->stSkillNeed, pSkill->stSkillLevelNeed );
		if ( pPreSkill )
		{
			int nSkillLevel = -1;
			for ( int n = 0; n<ArabicNights::ArabicNights_iMaxSkillKnown; n++ )
			{
				if ( pCharOtherInfo->skills.skill[n].ustSkillID == pSkill->stSkillNeed )
				{
					nSkillLevel = pCharOtherInfo->skills.skill[n].stSkillLevel;
					break;
				}
			}
			if ( nSkillLevel < pSkill->stSkillLevelNeed )
			{
				strcat( szInfo, "<#ffff0000=" );
				bResutl = false;
			}
			sprintf( szTemp, "��Ҫ����:%ld��%s\n",
				pSkill->stSkillLevelNeed, 
				//pPreSkill->szItemName.c_str() );
				GetString( pPreSkill->dwItemNameAddr ) );
			strcat( szInfo, szTemp );
		}
	}
	if ( pSkill->stVITNeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_CONSTITUTION].ustValue < pSkill->stVITNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ����:%d\n", pSkill->stVITNeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stSTRNeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_STRENGTH].ustValue < pSkill->stSTRNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ����:%d\n", pSkill->stSTRNeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stAGINeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_AGILITY].ustValue < pSkill->stAGINeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ����:%d\n", pSkill->stAGINeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stINTNeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_INTELLIGENCE].ustValue < pSkill->stINTNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "��Ҫ����:%d\n", pSkill->stINTNeed );
		strcat( szInfo, szTemp );
	}
	if( pCharBaseInfo->stSkillPoint <= 0 )
	{
		strcat( szInfo, "<#ffff0000=" );
		bResutl = false;
	}
	strcat( szInfo, "��Ҫ1�㼼�ܵ�" );
	//
	if ( szSkillInfo )
	{
		strcpy( szSkillInfo, szInfo );
	}
	return bResutl;
}

bool CItemDetail::LoadWeaponRand(char *szFile)
{
	CSlkReader pReader;

	if(!pReader.ReadFromFile( szFile ))
	{
		//ȡ�µ�slk��Դ
		GetErrorLog()->logString( "WeaponRand.slk not find" );
		return false;
	}



	//CopyCommon( pWeaponRand,common );
	bool bReadSucc = true;
	int iRow = 2;
	int iCol;
	std::string strTemp;
	int iRet;
	int iValue;
	float fValue;

	while(CSlkReader::ret_readover!=(iRet=pReader.GotoNextLine(iRow++)))
	{
		if(CSlkReader::ret_nothisline==iRet)
			continue;


		SWeaponRand *pWeaponRand;
		//pWeaponRand = new SWeaponRand;
		pWeaponRand = (SWeaponRand*)AllocItem( 0, sizeof( SWeaponRand ) );
		if(!pWeaponRand)
		{
			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
			GetErrorLog()->logString( "WeaponRand.slk�ڴ�������" );
			return false;
		}

		iCol = 1;

		if (!pReader.GetIntFieldByName("ID",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->WeaponRandID = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->WeaponRandLevel = iValue;
		iCol++;

		if (!pReader.GetStringFieldByName("ǰ׺",strTemp))
		{
			assert(false);
			continue;
		}
		//pWeaponRand->WeaponPrefix = strTemp;
		pWeaponRand->dwWeaponPrefixAddr = AllocStringCopy( strTemp.c_str() );
		iCol++;

		iCol++;

		iCol++;

		if (!pReader.GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("ħ����������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Magic] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("�繥����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("���������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�����ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("�繥���ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Frost] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Blaze] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("�׵��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�׶��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sExact = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sCritical = iValue;
		iCol++;

		if (!pReader.GetFloatFieldByName("������������",fValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->fCriticalmultiple = fValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttSpeed = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sIntonateSpeed = iValue;	
		iCol++;

		if (!pReader.GetIntFieldByName("���ϵȼ�",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sMaterialLevel = iValue;	

		//m_mapCharModulus.insert( mapCharModulus::value_type( pWeaponRand->WeaponRandID, pWeaponRand ) );
		//����vector
		//m_vecCharModulus.push_back( pWeaponRand );
		//�������
		m_mapWeaponRand.insert( mapWeaponRand::value_type( pWeaponRand->WeaponRandID, pWeaponRand ) );
		//����vector
		m_vectorWeaponRand.push_back( pWeaponRand );

	}
	return true;
}


CItemDetail::SWeaponRand *CItemDetail::GetWeaponRandByID(short sWeaponRandID)
{
	mapWeaponRand::iterator itRand;
	short RandID = sWeaponRandID;

	for( itRand = m_mapWeaponRand.begin(); itRand != m_mapWeaponRand.end(); itRand ++ )
	{
		if( (*itRand).first == sWeaponRandID )
			return (*itRand).second;
	}
	//	itRand = m_mapWeaponRand.find( RandID );
	//	if( itRand == m_mapWeaponRand.end( ) )
	//		return 0;

	return NULL;
}




bool CItemDetail::LoadArmourRand(char *szFile)
{
	CSlkReader reader;
	if(!reader.ReadFromFile( szFile ))
	{
		//ȡ�µ�slk��Դ
		GetErrorLog()->logString( "ArmourRand.slk not find" );
		return false;
	}
	bool bReadSucc = true;
	int iRow = 2;
	int iCol;
	std::string strTemp;
	int iRet;
	int  iValue;
	float fValue;

	while(CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
	{

		if(CSlkReader::ret_nothisline==iRet)
			continue;

		SArmourRand *pArmourRand;
		//pArmourRand = new SArmourRand;
		pArmourRand = (SArmourRand*)AllocItem( 0, sizeof( SArmourRand ) );
		if(!pArmourRand)
		{
			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
			GetErrorLog()->logString( "ArmourRand.slk�ڴ�������" );
			return false;
		}

		iCol = 1;

		if (!reader.GetIntFieldByName("ID",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->ArmourRandID = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->ArmourRandLevel = iValue;
		iCol++;

		if (!reader.GetStringFieldByName("ǰ׺",strTemp))
		{
			assert(false);
			continue;
		}
		//pArmourRand->ArmourPrefix = strTemp;
		pArmourRand->dwArmourPrefixAddr = AllocStringCopy( strTemp.c_str() );
		iCol++;

		iCol++;

		iCol++;

		if (!reader.GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Physics] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("ħ����������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Magic] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�繥����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("���������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Physics] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�繥���ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�������ӣ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Frost] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�׵��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�׶��˺�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sExact = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDodge = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sCritical = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sCriticalmultiple = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttSpeed = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����ٶ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sIntonateSpeed = iValue;
		iCol++;

		if (!reader.GetFloatFieldByName("�ƶ��ٶ�",fValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->fMoveSpeed = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("�����������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Max] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("���濹������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�׵翹������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Thunder] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�׶���������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Poison] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("��������ı�����%",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDefPer[ePlayDef_Physics] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�������ֵ����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpMax = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("ħ�����ֵ����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpMax = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�������ֵ����(%)",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpMaxPer = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("ħ�����ֵ����%",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpMaxPer = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�����ָ�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpRestore = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("ħ���ָ�����",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpRestore = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("����������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sReboundRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("�ϳɼ�������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sComposeRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("������������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sProficiencyRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("ǿ����������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sStrengthenRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("��Ƕ��������",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sEnchaseRate = iValue;

		if (!reader.GetIntFieldByName("���ϵȼ�",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMaterialLevel = iValue;


		//�������
		m_mapArmourRand.insert( mapArmourRand::value_type( pArmourRand->ArmourRandID, pArmourRand ) );
		//����vector
		m_vectorArmourRand.push_back( pArmourRand );

	}
	return true;

}

CItemDetail::SArmourRand *CItemDetail::GetArmourRandByID(short sArmourRandID)
{
	mapArmourRand::iterator itRand;
	short RandID = sArmourRandID;

	for( itRand = m_mapArmourRand.begin(); itRand != m_mapArmourRand.end(); itRand ++ )
	{
		if( (*itRand).first == sArmourRandID )
			return (*itRand).second;
	}
	//	itRand = m_mapWeaponRand.find( RandID );
	//	if( itRand == m_mapWeaponRand.end( ) )
	//		return 0;

	return NULL;
}


bool CItemDetail::LoadBaseAttr(char *szFile )
{
	CSlkReader reader;
	if(!reader.ReadFromFile( szFile ))
	{
		//ȡ�µ�slk��Դ
		GetErrorLog()->logString( "UpBaseAttr.slk not find" );
		return false;
	}
	bool bReadSucc = true;
	int iRow = 2;
	int iCol;
	int iRet;
	int  iValue;

	while(CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
	{

		if(CSlkReader::ret_nothisline==iRet)
			continue;

		SUpBaseAttr *pUpBaseAttr;
		//pUpBaseAttr = new SUpBaseAttr;
		pUpBaseAttr = (SUpBaseAttr*)AllocItem( 0, sizeof( SUpBaseAttr ) );
		if(!pUpBaseAttr)
		{
			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
			GetErrorLog()->logString( "UpBaseAttr.slk�ڴ�������" );
			return false;
		}

		iCol = 1;
		////////////////////////////////////////////////////////////
#define UpBaseAttrGetFieldInt( t, str ) \
	if( !reader.GetIntFieldByName( str.c_str(), iValue ) ) \
		{ \
		char szMem[256] = {0};	\
		strcpy( szMem, ("Error:��ȡUpBaseAttr.slk�ֶ�"+str+"����\r\n").c_str() );	\
		OutputSlkLoadingMessage( szMem ); \
		GetErrorLog()->logString( ("Error:��ȡUpBaseAttr.slk�ֶ�"+str+"����").c_str() ); \
		continue; \
		} \
		t = iValue; \
		iCol++;
		/////////////////////////////////////////////////////////////
		std::string szProInfo;
		szProInfo = "�ȼ�";
		UpBaseAttrGetFieldInt( pUpBaseAttr->sLevel, szProInfo );

		for( int i=0; i<=Profession_Wizard; i++)
		{
			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( i );
			if( !pProInfo )
				continue;
			szProInfo = pProInfo->m_strProShow;
			string szTemp = szProInfo+"����";
			UpBaseAttrGetFieldInt( pUpBaseAttr->Str[i], szTemp);// szTemp.c_str() );
			szTemp = (szProInfo+"����");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Agi[i], szTemp );
			szTemp = (szProInfo+"����");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Con[i], szTemp );
			szTemp = (szProInfo+"��֪");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Int[i], szTemp );
			szTemp = (szProInfo+"ħ��");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Mag[i], szTemp );
			szTemp = (szProInfo+"����");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Charm[i], szTemp );
		}
		//�������
		m_mapUpBaseAttr.insert( mapUpBaseAttr::value_type( pUpBaseAttr->sLevel, pUpBaseAttr ) );
		//����vector
		m_vectorUpBaseAttr.push_back( pUpBaseAttr );

	}
	return true;

}

CItemDetail::SUpBaseAttr *CItemDetail::GetBaseAttrByLevel(short sLevel)
{
	mapUpBaseAttr::iterator itRand;
	short RandID = sLevel;

	for( itRand = m_mapUpBaseAttr.begin(); itRand != m_mapUpBaseAttr.end(); itRand ++ )
	{
		if( (*itRand).first == sLevel )
			return (*itRand).second;
	}

	return NULL;
}

void CItemDetail::AddCrystalItem(CSlkReader *pReader, SItemCommon &common)
{
	SItemCrystal *pCrystal = 0;
	int iValue = 0;
	int iCon = 0;

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:Crystal.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "Crystal.slk���Ҳ�����ƷID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:Crystal.slk���Ҳ���IDΪ:%d����Ʒ!\r\n",common.ustItemID );
		GetErrorLog()->logString( "Crystal.slk���Ҳ�����ƷID" );
		return;
	}

	pCrystal = (SItemCrystal*)AllocItem( 0, sizeof( SItemCrystal ) );

	if( !pCrystal )
	{
		OutputSlkLoadingMessage( "\tError:Crystal.slk��IDΪ:%d����Ʒ,�����ڴ�ʧ��!\r\n",common.ustItemID );
		assert(false);
		return;
	}

	CopyCommon( pCrystal,common );


	bool bReadSucc = true;

	while( bReadSucc )
	{
		bReadSucc = false;
		iCon = 3;
		if (!pReader->GetIntFieldByName("�ȼ�",iValue))
		{
			assert( false );
			continue;
		}
		pCrystal->usCrystalLevel = iValue;

		bReadSucc = true;
		break;
	}
	if( bReadSucc )
	{
		//��ӵ���Ʒ������
		AddToMap( pCrystal );

		m_vectorCrystalItem.push_back( pCrystal );
	}

}


//bool CItemDetail::LoadFormulamodulus(char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//ȱ�µ�slk��Դ
//		assert( false && "FormulaModule.slk not find" );
//		return false;
//	}
//
//	int iRow = 2;
//	int iCol;
//	int iRet;
//	int iValue;
//	while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
//	{
//		if(CSlkReader::ret_nothisline==iRet)
//			continue;
//
//		FormulaMod *pFormulaMod;
//		pFormulaMod = new FormulaMod;
//		if(!pFormulaMod)
//		{
//			OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
//			assert( false && " Formulamodulus.slk �ڴ�������" );
//			return false;
//		}
//		iCol = 1;
//
//		if(!reader.GetStringField( iCol, pFormulaMod->szFormulaName))
//		{
//			OutputSlkLoadingMessage( "\t  ���빫ʽ���ֳ���!\r\n" );
//			assert( false && "Formulamodulus.slk ���빫ʽ���ֳ���" );
//			goto load_error;
//		}
//		iCol++;
//       
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ϵ��1����!\r\n" );
//			assert( false && "Formulamodulus.slk ����ϵ��1����" );
//			goto load_error;
//		}
//		pFormulaMod->stMod1 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ϵ��2����!\r\n" );
//			assert( false && "Formulamodulus.slk ����ϵ��2����" );
//			goto load_error;
//		}
//		pFormulaMod->stMod2 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ϵ��3����!\r\n" );
//			assert( false && "Formulamodulus.slk ����ϵ��3����" );
//			goto load_error;
//		}
//		pFormulaMod->stMod3 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ϵ��4����!\r\n" );
//			assert( false && "Formulamodulus.slk ����ϵ��4����" );
//			goto load_error;
//		}
//		pFormulaMod->stMod4 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t ����ϵ��5����!\r\n" );
//			assert( false && "Formulamodulus.slk ����ϵ��5����" );
//			goto load_error;
//		}
//		pFormulaMod->stMod5 = iValue;
//
//		//�������
//		m_mapFormulaModulus.insert( mapFormulaModulus::value_type( pFormulaMod->szFormulaName.c_str(), pFormulaMod ) );
//		//����vector
//		m_vecFormulaModulus.push_back( pFormulaMod );
//		continue;
//
//load_error:
//		OutputSlkLoadingMessage( "\tFormulamodulus.slk �� %d ������ʧ��!\r\n",iRow-1 );
//		continue;
//	}
//
//	return true;
//}
//
//CItemDetail::FormulaMod *CItemDetail::GetFormulaModByName( char *szFormulaName )
//{
//	mapFormulaModulus::iterator itModulus;
//	std::string strFind = szFormulaName;
//
//	itModulus = m_mapFormulaModulus.find( strFind );
//	if( itModulus == m_mapFormulaModulus.end( ) )
//		return 0;
//
//	return (*itModulus).second;
//}


//
//int GetAvePhysicAtt(ArabicNights::SCharItem *pitem)
//{
//	if (NULL==pitem)
//		return false;
//	int iValue;
//	int Arry[20] = {0};
//	CItemDetail::SItemWeapon *pItemWeapon;
//	pItemWeapon	= (CItemDetail::SItemWeapon *)theItemDetail.GetItemByID(pitem->ustItemID);
//	int Max,Min;
//	int Ave,Sum;
//	int Loop;
//	Max = pItemWeapon ->ustPhysicAttMax;
//	Min = pItemWeapon ->ustPhysicAttMin;
//	Sum = Max - Min + 1;
//	for (Loop = 0 && Min;Loop < Sum && Min<Max;Loop ++ && Min++)
//	{
//		Arry[Loop]=Min;
//	}
//	iValue = rand() % 20;
//	Ave = Arry[iValue];
//	return Ave;
//}
//---------------------------------------------------------------------------
//	End.
//---------------------------------------------------------------------------
