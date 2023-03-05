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
	"slow"				//缓慢
		,"normal"			//普通
		,"fast"				//快速
};


static char* (g_szWeaponType[]) = 
{
		"unarm"							//徒手武器，拳套
		,"blade"						//刀
		,"sword"						//剑
		,"twohand-blade"				//双手刀
		,"twohand-sword"				//双手剑
		,"magicstick"					//魔法杖
		,"dagger"						//匕首
		,"bow"							//弓
		,"twohand-magicstick"			//双手杖
		,"shield"						//盾

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
		,""				//目前不需要文件存储(other)
		,"stone.slk"
		,"status.slk"
		,"gameaction.slk"
		,"reel.slk"
		,""				//目前不需要文件存储(material)
		,""				//目前不需要文件存储(medal)
		,""				//目前不需要文件存储(task)
		//	,"magicitem.slk"
		,""				//目前不需要文件存储(tool)
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
		,"helmet"			//头盔
		,"face"
		,"armour"			//盔甲
		,"glove"			//手套
		,"shoe"				//鞋子
		,"Cape"
	//	,"handitem",			//2手都能用
		,"lhanditem"			//左手物品
		,"rhanditem"    		//右手物品
		,"headwear"				//头饰
		,"HandShiedld"			//盾
		,"Shoulder"				//护肩
		,"Trousers"				//护腿
		,"accouterment"    		//	
		,"rring"					//左手戒指
		,"lring"					//左手戒指
		,"bangle"				//手镯 
};

static char*(g_szTargetString[])=
{
	"target_no"				//无目标
		,"target_myself"		//我 （只对自己）
		,"target_friend"		//朋友（只对队友）	
		,"target_normalplayer"	//普通玩家（所有玩家包括自己除了敌人）
		,"target_enemy"			//敌人（只能对敌人）
		,"target_dead"			//死亡目标（只对死人）
		,"target_herb"			//目标草药
		,"target_mine"			//目标矿
		,"target_all"			//所有人都可以
};

static char*(g_szEffectCenter[])=
{
	"center_no"			//没有持续性效果
		,"center_metotarget"//以自己到敌人
		,"center_me"		//以自己当前位置为中心
		,"center_target"	//以目标位置为中心
};

//装备类型
char*(g_szEquipType[ CItemDetail::const_iEquipTypeNum ])=
{
	"helmet" //头盔
		,"armour" //盔甲
		,"glove"  //手套
		,"shoe"   //鞋子
		,"cape"	  //披风
		,"weapon" //武器
		,"shield" //盾牌
		,"accounterment"//饰品
		,"ring"			//戒指
		,"bangel"		//手镯
		,"Shoulder"				//护肩
		,"Trousers"		//护腿
};

char* (g_szSkillType[])=
{
	"skilltype_action",		//在动作播放结束后结算的，既能
		"skilltype_magic_hit",	//在动作播放结束后结算，释放出一个法术组件
		"skilltype_magic_npc",	//在动作播放结束后，释放出一个法术npc
		"skilltype_passive"		//被动技能
};

char* (g_szSkillGeneralType[])=
{
	"generaltype_action",	//属于Action技能
		"generaltype_magic",	//属于Magic技能
		"generaltype_sequence",	//属于连招技能
		"generaltype_passive"	//被动技能
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
//	"enemy_beginner",//初心者
//		"enemy_knight",	//骑士
//		"enemy_knifeman",//刀客
//		"enemy_swordMan",//剑客
//		"enemy_rabbi",	//法师
//		"enemy_churchman",//牧师
//		"enemy_wizard,"  //巫师
//		"enemy_all",	//所有人
//};
//char* (g_szMonsterFightBackEnemy[])=
//{
//	"fb_hpmin",	//hp最小
//		"fb_hpmax",	//hp最大
//		"fb_hurtmin",//伤害还最小
//		"fb_hurtmax",//伤害还最大
//		"fb_levelmin",//等级最小
//		"fb_levelmax",//等级最大
//		"fb_profession_beginner",//初心者
//		"fb_profession_knight",	//骑士
//		"fb_profession_knifeman",//刀客
//		"fb_profession_swordMan",//剑客
//		"fb_profession_rabbi", //法师
//		"fb_profession_churchman",//牧师
//		"fb_profession_wizard"//巫师
//};

char* (g_szBalanceType[])=
{
	"balancetype_none",					//没有任何结算
		"balancetype_phydamage",			//物理伤害结算
		"balancetype_magdamage",			//魔法伤害结算
		"balancetype_restorehp",			//回HP结算
		"balancetype_relive",				//复活结算
		"balancetype_addextrahp",			//瞬间吸血
		//"balancetype_restoretp",			//回TP结算
		"balancetype_damagemp",				// 伤害MP
		"balancetype_dispelbadstatus"		//驱散坏的状态
		"balancetype_Frost",
		"balancetype_Blaze",
		"balancetype_Thunder",
		"balancetype_Poison",

};

//状态的结算公式类型
char* (g_szStatusBalanceType[])=
{
	"balance_status_type_none",
		"balance_status_type_1",
		"balance_status_type_life_stolen",//偷血
		"balance_status_type_life_trans",	//传血
		"balance_status_type_manaburn"
};

//动作类型
char* (g_szActionType[])=
{
	"baseaction"
		,"communityaction"
		,"socialaction"
};

//性别
char* (g_szSexType[])=
{
	"male"
		,"female"
};

//职业
char* (g_szProfessionType[])=
{

	//盗贼
	"robber"
		//勇士
		,"warrior"
		//射手
		,"archer"
		//道士
		,"Taoist"

		//巫师
		,"wizard"
};

//char* (g_szProfessionType[])=
//{
//	//武士初学者
//	"Warrior_Beginner"
//	//法师初学者
//	,"Wizard_Beginner"
//	//中国武士
//	,"China_Warrior"
//	//中国法师
//	,"China_Wizard"
//	//中东武士
//	,"MiddleEast_Warrior"
//	//中东法师
//	,"MiddleEast_Wizard"
//	//西方武士
//	,"West_Warrior"
//	//西方法师
//	,"West_Wizard"
//};

//技能力类型
char* (g_szSkillPower[])=
{
	"zhaoshi"
		,"bishaji"
		,"magic"
};

//施放目标，客户端
//如果是对自己使用，那么不需要鼠标指向攻击目标，直接取角色当前位置
//如果是需要对人使用，那么攻击目标必须是角色
//如果对位置使用，那么攻击目标为位置（如果指向角色，取角色位置）
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
		,"casttarget_herb"						//以草药为目标
		,"casttarget_mine"						//以矿为目标
};

int GetIDByConstString( const char* szString,char**pszString,int iHowManyString )
{
	strlwr( const_cast<char*>(szString) );
	int iLoop;
	int iBlack = ' ';

	//去掉前面和后面的空格
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
//////随机伤害
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
	//函数目前设计为只能被调用一次
	if( bOnlyOne )
		return false;
	bOnlyOne = true;

	char szFile[ MAX_PATH ];

	//////职业的定义
	//sprintf( szFile, "%s\\%s", szPath, "Profession.slk" );
	//OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	//if( !LoadProfession( szFile ) )
	//{
	//	//拷贝数据 slk
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	GetErrorLog()->logString( "找不到profession.slk" );
	//	return false;
	//}

	////怪物的配置
	//sprintf( szFile,"%s\\%s",szPath,"monster.slk" );
	//OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	//if( !LoadMonster( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	GetErrorLog()->logString( "找不到monster.slk" );
	//	return false;
	//}	

	//sprintf( szFile,"%s\\%s",szPath,"WorldMapCfg.slk" );
	//OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	//if( !m_WorldMapConfig.Load( szFile ) )
	//	return false;
	//// <

	////角色系数
	//sprintf( szFile,"%s\\%s",szPath,"charmodulus.slk");
	//OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	//if( !LoadCharModulus( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	GetErrorLog()->logString( "找不到charmodulus.slk" );
	//	return false;
	//}	

	/*sprintf( szFile,"%s\\%s",szPath,"WeaponRand.slk");
	OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	if( !LoadWeaponRand( szFile ) )
	{
		OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
		GetErrorLog()->logString( "找不到WeaponRand.slk" );
		return false;
	}	

	sprintf( szFile,"%s\\%s",szPath,"ArmourRand.slk");
	OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	if( !LoadArmourRand( szFile ) )
	{
		OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
		GetErrorLog()->logString( "找不到ArmourRand.slk" );
		return false;
	}	*/

	//sprintf( szFile,"%s\\%s",szPath,"UpBaseAttr.slk");
	//OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	//if( !LoadBaseAttr( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	GetErrorLog()->logString( "找不到UpBaseAttr.slk" );
	//	return false;
	//}

	/*sprintf( szFile,"%s\\%s",szPath,"Formulamodulus.slk");
	if( !LoadFormulamodulus( szFile ) )
	{
	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	assert( false && "找不到Formulamodulus.slk" );
	return false;
	}*/

	////符石与技能的对应
	//sprintf( szFile, "%s\\%s", szPath, "stoneskill.slk" );
	//if( !LoadStoneSkill( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	assert( false && "找不到stoneskill.slk" );
	//	return false;
	//}

	////招式片断与技能的对应
	//sprintf( szFile, "%s\\%s", szPath, "skilltoskill.slk" );
	//if( !LoadSkillToSkill( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	assert( false && "找不到skilltoskill.slk" );
	//	return false;
	//}

	////物品制造,原料与产品的对应关系
	//sprintf( szFile, "%s\\%s", szPath, "produceitem.slk" );
	//if( !LoadProduceItem( szFile ) )
	//{
	//	OutputSlkLoadingMessage( "找不到%s\r\n",szFile );
	//	assert( false && "找不到produceitem.slk" );
	//	return false;
	//}

	CSlkReader slkItem;
	CSlkReader slkChildItem[ g_iItemTypeSize ];
	//	
	sprintf( szFile,"%s\\%s",szPath,g_szItemFile[0] );	
	OutputSlkLoadingMessage( "载入%s\r\n",szFile );
	if( !slkItem.ReadFromFile( szFile ) )
	{		
		OutputSlkLoadingMessage( "找不到%s文件\r\n",szFile);
		GetErrorLog()->logString( "找不到item.slk" );
		return false;
	}

	int i;
	//no "other" file Now
	for( i = 0 ; i < g_iItemTypeSize; i ++ )
	{
		sprintf( szFile,"%s\\%s",szPath,g_szItemFile[ i+file_restore ] );
		OutputSlkLoadingMessage( "正在分析%s\r\n",szFile );
		if( !slkChildItem[ i ].ReadFromFile( szFile ) )
		{
			if( file_other != i + file_restore )
			{
				OutputSlkLoadingMessage( "找不到%s文件\r\n",szFile);
				//assert( false && "某个分表缺少.如status.slk,skill.slk等" );
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
		//		OutputSlkLoadingMessage("/L计算");
		//		break;
		//	case 1:
		//		OutputSlkLoadingMessage("/L计算.");
		//		break;
		//	case 2:
		//		OutputSlkLoadingMessage("/L计算..");
		//		break;
		//	case 3:
		//		OutputSlkLoadingMessage("/L计算...");
		//		break;
		//	}
		//}





		if( CSlkReader::ret_nothisline == iRet )
		{
			continue;
		}
		common.cItemClass = ItemClass_Normal;
		//物品ID
		iCol = 1;
		if( !slkItem.GetIntFieldByName( "id", iValue ) )
		{
			//assert( false );
			continue;
		}
		common.ustItemID = iValue;

		std::string strItemName;

		//if( !slkItem.GetStringFieldByName( "物品名字", common.szItemName ) )
		if( !slkItem.GetStringFieldByName( "物品名字", strItemName ) )
		{
			assert( FALSE );
			continue;
		}
		OutputSlkLoadingMessage( "载入物品(%s)", strItemName.c_str() );
		//common.dwItemNameAddr = AllocGlobalBuffer( strItemName.length()+1 );
		common.dwItemNameAddr = AllocStringCopy( strItemName.c_str() );
		//HelperFunc::SafeNCpy( )

		std::string strItemDesc;
		//if( !slkItem.GetStringFieldByName( "物品描述", common.szItemDesc ) )
		if( !slkItem.GetStringFieldByName( "物品描述", strItemDesc ) )
		{
		}
		common.dwItemDescAddr = AllocStringCopy( strItemDesc.c_str() );

		if( !slkItem.GetIntFieldByName( "价值", iValue  ) )
		{
			assert( false );
			continue;
		}
		common.dwCost = iValue;

		if( !slkItem.GetIntFieldByName( "品质等级", iValue  ) )
		{
			assert( false );
			continue;
		}

		common.ustLevel = iValue;

		if( !slkItem.GetStringFieldByName( "物品类型", strTemp ) )
		{
			assert( FALSE );
			continue;
		}
		common.ucItemType = GetItemTypeByString( strTemp.c_str());

		if( common.ucItemType < 0 || common.ucItemType >=ITEMTYPE_MAX )
		{
			OutputSlkLoadingMessage( "\tError:物品类型错误\r\n"  );		
			char string[256];
			sprintf(string, "item.slk(%d)中找不到物品类型",common.ustItemID);
			MessageBox( NULL, string, "warning", MB_OK );
			continue;
		}

		std::string strIconInItemBag;
		//if( !slkItem.GetStringFieldByName( "物品在物品栏中得icon文件", common.szIconInItembag ) )
		if( !slkItem.GetStringFieldByName( "物品在物品栏中得icon文件", strIconInItemBag ) )
		{
			assert( FALSE );
			continue;
		}
		common.dwIconInItemBagAddr = AllocStringCopy( strIconInItemBag.c_str() );

		//		if( !slkItem.GetStringFieldByName( "物品在物品栏中的icon占位文件", common.szIconTile ) )
		//		{
		////			common.szIconTile = "UI\\ICON\\Null.tga";
		//			assert( FALSE );
		//			continue;
		//		}

		if( !slkItem.GetIntFieldByName( "物品掉在地上时的模型文件id", iValue ) )
		{
			assert( false );
			continue;
		}
		common.ustModelIDOverGround = iValue;

		if( slkItem.GetIntFieldByName( "稀有度", iValue ) )
		{
			common.cItemClass = iValue;
		}
		else
		{
			common.cItemClass = ItemClass_Normal;
		}
		if( slkItem.GetIntFieldByName( "是否显示装备特效", iValue ) )
		{
			iValue = 1;
		}
		common.bShowEquipEffect = iValue>0?true:false;
		// 可否被移动
		iCol++;
		// 可否丢弃
		iCol++;
		// 可否销毁
		iCol++;
		// 可否交易
		iCol++;
		// 可否买卖
		iCol++;
		// 占格宽
		//if ( !GetIntField(&slkItem, iCol++, iValue) )
		//{
		//	iValue = 1;
		//}
		if( !slkItem.GetIntFieldByName( "占格宽", iValue ) )
		{
			iValue = 1;
		}
		common.ustItemW = iValue;
		// 占杭高
		//if ( !GetIntField(&slkItem, iCol++, iValue) )
		//{
		//	iValue = 1;
		//}
		if( !slkItem.GetIntFieldByName( "占格高", iValue ) )
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
			//case ITEMTYPE_MAGICITEM:	//魔法材料
			//	AddMagicItem(&slkChildItem[common.ucItemType],common);
			//	break;
		case ITEMTYPE_MATERIAL:		//原料
			AddMaterialItem(&slkChildItem[common.ucItemType],common);
			break;
		case ITEMTYPE_TASK:			//任务
			AddTaskItem(&slkChildItem[common.ucItemType],common);
			break;
			//case ITEMTYPE_TOOL:			//工具
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

	//OutputSlkLoadingMessage( "\t开始分析技能的领悟使用条件\r\n\r\n" );
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
			{//建立一个技能物品ID到技能序号的 转换
				SItemSkill *pSkill = NULL;
				pSkill = (SItemSkill *)pItem;
				m_mapSkillNO.insert( mapSkillNO::value_type( pSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
				m_vecSkill.push_back( pSkill->ustItemID );

				//建立一个技能数组(只限法术)
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
		//		OutputSlkLoadingMessage("/L写入");
		//		break;
		//	case 1:
		//		OutputSlkLoadingMessage("/L写入.");
		//		break;
		//	case 2:
		//		OutputSlkLoadingMessage("/L写入..");
		//		break;
		//	case 3:
		//		OutputSlkLoadingMessage("/L写入...");
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
	//根据Item的等级放入相应的Vector中
	if( pItem->ustLevel>=1 && pItem->ustLevel<100 )
		m_vectorLevelItem[pItem->ustLevel].push_back(pItem);

	m_BakupItem.push_back(pItem);
	//记录ItemID
	m_vectorItemID.push_back( pItem->ustItemID );

	if( pItem->ustItemID >= m_vectorItem.size() )
	{
		m_vectorItem.resize( pItem->ustItemID + pItem->ustItemID );		
	}
	m_vectorItem[pItem->ustItemID] = pItem;	

	m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem );
	//if( m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem ) == 0 )
	//{
	//	OutputSlkLoadingMessage( "道具重名 %s", (char*)GetAddrPointer(pItem->dwItemNameAddr) );
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

	//ID号是否在规定范围内
	if( common.ustItemID < StartID_Restore || common.ustItemID > EndID_Restore )
	{
		GetErrorLog()->logString( "restore id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:restore.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "restore.slk中找不到物品ID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:restore.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "restore.slk中找不到物品ID" );
		return;
	}
	//pItemRestore = new SItemRestore;//m_pMemAllocer->Malloc( sizeof(SItemRestore) );
	pItemRestore = (SItemRestore*)AllocItem( 0, sizeof( SItemRestore ) );
	if( !pItemRestore )
	{
		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
		GetErrorLog()->logString( "restore.slk中内存分配出错" );
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

		//增加HP
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的addHP数据错!\r\n" );
			GetErrorLog()->logString( "restore.slk中addHP数据错" );
			continue;
		}
		pItemRestore->dwAddHP = iValue;
		iCol ++;

		//增加MP
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的addMP数据错!\r\n" );
			GetErrorLog()->logString( "restore.slk中addMP数据错" );
			continue;
		}
		pItemRestore->dwAddMP = iValue;
		iCol ++;
		iCol++;
		////增加TP
		//if( !GetIntField( pReader, iCol, iValue ) )
		//{
		//	OutputSlkLoadingMessage( "\tError:药品的addTP数据错!\r\n" );
		//	assert( false && "restore.slk中addTP数据错" );
		//	continue;
		//}
		//pItemRestore->dwAddTP = iValue;
		//iCol++;

		//增加Exp
		if( !GetIntField( pReader,iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的addExp数据错!\r\n" );
			GetErrorLog()->logString( "restore.slk中addExp数据错" );
			continue;
		}
		pItemRestore->dwAddExp = iValue;
		iCol ++;

		//消除hunger
		/*if( !GetIntField( pReader,iCol,iValue ) )
		{
		OutputSlkLoadingMessage( "\tError:药品的消除hunger数据错!\r\n" );
		assert( false && "restore.slk中消除hunger数据错" );
		continue;
		}
		pItemRestore->stSubHunger = iValue;*/
		iCol ++;

		//解除状态	
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的解除状态没有!\r\n" );
			pItemRestore->ustSubStatusID = ArabicNights::ErrorUnsignedShortID;
		}
		else
		{
			pItemRestore->ustSubStatusID = iValue;
		}
		iCol++;

		//导致状态	
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的导致状态没有!\r\n" );
			pItemRestore->ustAddStatusID = ArabicNights::ErrorUnsignedShortID;
		}
		else
		{
			pItemRestore->ustAddStatusID = iValue;
		}
		iCol++;

		//导致状态等级
		if( !GetIntField( pReader, iCol, iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:药品的导致状态等级默认1!\r\n" );
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
			OutputSlkLoadingMessage( "\tError:ColdDown默认0!\r\n" );
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
			OutputSlkLoadingMessage( "\tError:type默认0!\r\n" );
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
		//添加到物品队列中
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
//	//ID号是否在规定范围内
//	if( common.ustItemID < StartID_Stone || common.ustItemID > EndID_Stone )
//	{
//		assert( false && "stone id error" );
//		return;
//	}
//
//	if( -1 == iLineNo )
//	{
//		OutputSlkLoadingMessage( "\tError:stone.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//		assert( false && "stone.slk中找不到ID" );
//		return;
//	}
//
//	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
//	{
//		OutputSlkLoadingMessage( "\tError:stone.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//		assert( false && "stone.slk中找不到ID" );
//		return;
//	}
//
//	//pItemStone = new SSymbolStone;//m_pMemAllocer->Malloc( sizeof(SSymbolStone) );
//	pItemStone = (SSymbolStone*)AllocItem( 0, sizeof(SSymbolStone) );
//
//	if(!pItemStone)
//	{
//		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//		assert( false && "stone.slk中内存分配出错" );
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
//		//符石类型
//		if( !GetIntField( pReader, iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\tError:符石类型数据错!\r\n" );
//			assert( false && "符石类型数据错" );
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
//		//添加到符石队列中
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

//装载动作数据
void CItemDetail::AddActionItem( CSlkReader *pReader, SItemCommon &common )
{
	//ID号是否在规定范围内
	if( common.ustItemID < StartID_GameAction || common.ustItemID > EndID_GameAction )
	{
		GetErrorLog()->logString( "game action id error" );
		return;
	}


	SItemAction *pItemAction;
	int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );


	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:gameaction.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gameaction.slk中找不到物品ID" );
		return;
	}

	if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:gameaction.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gameaction.slk中找不到物品ID" );
		return;
	}

	//pItemAction = new SItemAction;//m_pMemAllocer->Malloc( sizeof(SItemAction) );
	pItemAction = (SItemAction*)AllocItem( 0, sizeof( SItemAction ) );
	if(!pItemAction)
	{
		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
		GetErrorLog()->logString( "gameaction.slk中内存分配出错" );
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

		//动作ID
		if(!GetStringField( pReader, iCol, strTemp ))
		{
			OutputSlkLoadingMessage( "Error:读取动作名称出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取动作名称出错!" );
			continue;
		}
		pItemAction->ustActionID = ArabicNightsAction::FindActionIdByName( strTemp.c_str() );

		iCol++;

		//动作类型（0，基本动作 1，社群动作 2，社交动作）
		if(!GetStringField(pReader,iCol,strTemp))
		{
			OutputSlkLoadingMessage( "Error:读取动作类型出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取动作类型出错!" );
			continue;
		}
		pItemAction->stType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
			g_szActionType, sizeof(g_szActionType)/sizeof(char *) );

		if( -1 == pItemAction->stType )
		{
			OutputSlkLoadingMessage( "Error:读取动作类型出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取动作类型出错!" );
			continue;
		}
		iCol ++;

		//单次播放时间
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:读取单次播放时间出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取单次播放时间出错!" );
			continue;
		}
		pItemAction->stSinglePlayTime = iValue;
		iCol++;

		//持续播放时间
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:读取持续播放时间出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取持续播放时间出错!" );
			continue;
		}
		pItemAction->stLastingPlayTime = iValue;
		iCol++;

		//保留最后一帧
		if(!GetIntField(pReader,iCol,iValue))
		{
			OutputSlkLoadingMessage( "Error:读取保留最后一帧出错!\r\n" );
			GetErrorLog()->logString( "gameaction.slk中读取保留最后一帧出错!" );
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

		//添加到符石队列中
		AddToMap( pItemAction );
	}
	else
	{
		//		delete( pItemAction );
	}
}

//装载卷轴数据
/*void CItemDetail::AddReelItem( CSlkReader *pReader, SItemCommon &common )
{
SItemReel *pItemReel;
int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );

//ID号是否在规定范围内
if( (common.ustItemID < StartID_SkillReel || common.ustItemID > EndID_SkillReel)
&&  (common.ustItemID < StartID_StoneReel || common.ustItemID > EndID_StoneReel) )
{
assert( false && "reel id error" );
return;
}

if( -1==iLineNo )
{
OutputSlkLoadingMessage( "\tError:reel.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
assert( false && "reel.slk中找不到物品ID" );
return;
}

if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
{
OutputSlkLoadingMessage( "\tError:reel.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
assert( false && "reel.slk中找不到物品ID" );
return;
}

pItemReel = new SItemReel;//m_pMemAllocer->Malloc( sizeof(SItemReel) );
if(!pItemReel)
{
OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
assert( false && "reel.slk中内存分配出错" );
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

//增加符石ID
if(!GetIntField(pReader,iCol,iValue))
{
OutputSlkLoadingMessage( "Error:读取增加符石ID默认0xffff!\r\n" );
pItemReel->ustAddStoneID = 0xffff;
}
else
{
pItemReel->ustAddStoneID = iValue;
}
iCol++;

//增加技能ID
if(!GetIntField(pReader,iCol,iValue))
{
OutputSlkLoadingMessage( "Error:读取增加技能ID默认0xffff!\r\n" );
pItemReel->ustAddSkillID = 0xffff;
}
else
{
pItemReel->ustAddSkillID = iValue;
}
iCol++;

//增加使用职业的限制
int iLoop;
for( iLoop=0; iLoop < ArabicNights::Profession_Max; iLoop++ )
{
pItemReel->abEquipProfessionReq[iLoop] = false;
}

if( !pReader->GetStringField( iCol,strTemp) )
{
OutputSlkLoadingMessage( "\tWarning:卷轴没有定义需求，缺省所有职业都可以使用\r\n" );		
for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
pItemReel->abEquipProfessionReq[ iLoop ] = true;
}
else
{
//适用多个职业
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
//添加到卷轴队列中
AddToMap( pItemReel );
}
else
{
delete( pItemReel );
}
}*/

////加魔法材料
//void CItemDetail::AddMagicItem( CSlkReader *pReader, SItemCommon &common )
//{
//	SItemMagic *pItemMagic;
//	int iLineNo = pReader->FindLineByIntField( 1, common.ustItemID );
//
//	if( -1==iLineNo )
//	{
//		OutputSlkLoadingMessage( "\tError:magicitem.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//		assert( false && "magicitem.slk中找不到物品ID" );
//		return;
//	}
//
//	if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
//	{
//		OutputSlkLoadingMessage( "\tError:magicitem.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//		assert( false && "magicitem.slk中找不到物品ID" );
//		return; 
//	}
//
//	pItemMagic = new SItemMagic;
//	if(!pItemMagic)
//	{
//		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//		assert( false && "magicitem.slk中内存分配出错" );
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
//		//整个成功几率
//		if(!GetIntField(pReader,iCol,iValue))
//		{
//			OutputSlkLoadingMessage( "Error:读取成功几率默认1000!\r\n" );
//			pItemMagic->ustSuccessRate = 1000;
//		}
//		else
//		{
//			pItemMagic->ustSuccessRate = iValue;
//		}
//		iCol++;
//
//		//各个属性的具体数值
//		int i;
//		for( i=0;i<7;i++ )
//		{
//			//该属性的出现概率
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取成功几率默认0!\r\n" );
//				pItemMagic->ustSpecialRate[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustSpecialRate[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响武器的最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响武器的最小值默认0!\r\n" );
//				pItemMagic->ustAffectWeaponMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectWeaponMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响武器的最大值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响武器的最大值默认0!\r\n" );
//				pItemMagic->ustAffectWeaponMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectWeaponMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响衣服最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响衣服最小值默认0!\r\n" );
//				pItemMagic->ustAffectClothesMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectClothesMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响衣服最大值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响衣服最大值默认0!\r\n" );
//				pItemMagic->ustAffectClothesMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectClothesMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响鞋子最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响鞋子最小值默认0!\r\n" );
//				pItemMagic->ustAffectShoeMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectShoeMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响鞋子最大值	
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响鞋子最大值默认0!\r\n" );
//				pItemMagic->ustAffectShoeMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectShoeMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响手套最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响手套最小值默认0!\r\n" );
//				pItemMagic->ustAffectGloveMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectGloveMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响手套最大值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响手套最大值默认0!\r\n" );
//				pItemMagic->ustAffectGloveMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustAffectGloveMax[ i ] = iValue;
//			}
//			iCol++;
//
//
//			//该属性影响头盔最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响头盔最小值默认0!\r\n" );
//				pItemMagic->ustHeadPieceMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustHeadPieceMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响头盔最大值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响头盔最大值默认0!\r\n" );
//				pItemMagic->ustHeadPieceMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustHeadPieceMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响饰品最小值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响饰品最小值默认0!\r\n" );
//				pItemMagic->ustDecorateMin[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustDecorateMin[ i ] = iValue;
//			}
//			iCol++;
//
//			//该属性影响饰品最大值
//			if(!GetIntField(pReader,iCol,iValue))
//			{
//				OutputSlkLoadingMessage( "Error:读取属性影响饰品最大值默认0!\r\n" );
//				pItemMagic->ustDecorateMax[ i ] = 0;
//			}
//			else
//			{
//				pItemMagic->ustDecorateMax[ i ] = iValue;
//			}
//			iCol++;
//
//			//读取最后一个属性时,另外再读一个状态几率,这是专门针对武器的.
//			if(i==6)
//			{
//				//影响状态的几率
//				if(!GetIntField(pReader,iCol,iValue))
//				{
//					OutputSlkLoadingMessage( "Error:读取影响状态的几率默认0!\r\n" );
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
//		//添加到魔法材料队列中
//		AddToMap( pItemMagic );
//	}
//	else
//	{
//		delete( pItemMagic );
//	}
//}

//加原料
void CItemDetail::AddMaterialItem( CSlkReader *pReader, SItemCommon &common )
{
	SCreateMaterial *pItemMaterial = 0;
	//int iValue;
	//int iCol;

	//ID号是否在规定范围内
	if( common.ustItemID < StartID_Material || common.ustItemID > EndID_Material )
	{
		GetErrorLog()->logString( "material id error" );
		return;
	}

	/*int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID ); 

	if( -1 == iLineNo )
	{
	OutputSlkLoadingMessage( "\tError:material.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
	assert( false && "gem.slk中找不到物品ID" );
	return;
	}

	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
	OutputSlkLoadingMessage( "\tError:material.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
	assert( false && "gem.slk中找不到物品ID" );
	return;
	}*/
	//
	pItemMaterial = (SCreateMaterial*)AllocItem( 0, sizeof( SItemCommon ) );
	if( !pItemMaterial )
	{
		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
		GetErrorLog()->logString( "material.slk中内存分配出错" );
		return;	
	}

	CopyCommon( pItemMaterial, common );

	//iCol = 3;
	//
	//if (!pReader->GetIntFieldByName("增加PAtt",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usPAtt = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("增加MAtt",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usMAtt = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("增加PDef",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usPDef = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("增加MDef",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usMDef = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("普通附加攻击状态",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usStatusID = iValue;
	//iCol++;

	//if (!pReader->GetIntFieldByName("普通攻击状态等级",iValue))
	//{
	//	assert(false);
	//}
	//pItemMaterial->usStatusLevel = iValue;
	//iCol++;

	//添加到物品队列中
	AddToMap( pItemMaterial );
}

//加任务道具
void CItemDetail::AddTaskItem( CSlkReader *pReader, SItemCommon &common )
{
	//ID号是否在规定范围内
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
		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
		GetErrorLog()->logString( "task.slk中内存分配出错" );
		return;	
	}
	CopyCommon( pItemTask, common );

	//添加到物品队列中
	AddToMap( pItemTask );
}

//加工具
//void CItemDetail::AddToolItem( CSlkReader *pReader, SItemCommon &common )
//{
//	//ID号是否在规定范围内
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
//		OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//		assert( false && "tool.slk中内存分配出错" );
//		return;	
//	}
//	CopyCommon( pItemTool, common );
//
//	//添加到物品队列中
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

//根据宝石编码加入到正确的vector
bool CItemDetail::AddToGems( SItemGem *pGem )
{
	int iGemType,iGemSubID;
	if( !GetGemTypeAndSubID( pGem->ucGemID,iGemType,iGemSubID ) )
		return false;
	iGemSubID --;
	(m_vectorGems[ iGemType ])[iGemSubID] = pGem;
	return true;
}

//根据宝石编码得到结构
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
		OutputSlkLoadingMessage( "\tError:gem.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gem.slk中找不到物品ID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "gem.slk中找不到物品ID" );
		return;
	}

	//pItemGem = new SItemGem;
	pItemGem = (SItemGem*)AllocItem( 0, sizeof( SItemGem ) );

	if( !pItemGem )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,分配内存失败!\r\n",common.ustItemID );
		goto error_ret;
	}

	CopyCommon( pItemGem,common );

	//skip itemID 物品名字
	iCol = 3;

	//宝石ID
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取 宝石ID出错!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ucGemID = iValue;

	//+PhyAtt
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取 +PhyAtt错!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustAddPhyAtt = iValue;

	//+PhyDef
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取 +PhyDef错!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Physics] = iValue;

	//+MagAtt
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取 +MagAtt错!\r\n",common.ustItemID );
		goto error_ret;
	}
	pItemGem->ustAddMagAtt = iValue;

	//+攻击速度
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"+AttSpeed" );
		goto error_ret;
	}
	pItemGem->usAttSpeed = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"冰抗性" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Frost] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"火抗性" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Blaze] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"雷抗性" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Thunder] = iValue;

	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"毒抗性" );
		goto error_ret;
	}
	pItemGem->ustDef[ePlayDef_Poison] = iValue;

	//普通附加攻击状态
	if( !pReader->GetIntField( iCol++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"普通附加攻击状态" );
		goto error_ret;
	}
	pItemGem->ustNormalAttackStatusID = iValue;


	//普通附加攻击状态等级
	if( !pReader->GetIntField( iCol ++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"普通附加攻击状态等级" );
		goto error_ret;
	}
	pItemGem->ustNormalAttackStatusLevel = iValue;

	//是否能镶嵌
	if( !pReader->GetIntField( iCol ++,iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,读取%s错!\r\n",common.ustItemID,"普通附加攻击状态等级" );
		goto error_ret;
	}
	if (iValue == 0)
		pItemGem->bIn = false;
	else 
		pItemGem->bIn = true;



	if( !AddToGems( pItemGem ) )
	{
		OutputSlkLoadingMessage( "\tError:gem.slk中ID为:%d的物品,错误的GemID:%d!\r\n",common.ustItemID,pItemGem->ucGemID );
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
	//读入材料时，根据材料名字选择材料ID
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
		OutputSlkLoadingMessage( "\tError:createitemrule.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "createitemrule.slk中找不到物品ID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "createitemrule.slk中找不到物品ID" );
		return;
	}

	//pItemRule = new SItemCreateItemRule;
	pItemRule = (SItemCreateItemRule*)AllocItem( 0, sizeof( SItemCreateItemRule ) );
	if( !pItemRule )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,分配内存失败!\r\n",common.ustItemID );
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
	//合成目标物体
	if( pReader->GetStringField( iCol++,strTemp ) )
		//{
		//	/*OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取%s出错!\r\n",common.ustItemID,"合成目标物体" );
		//	goto error_ret;*/
		//	continue;
		//}
		//else
	{
		pItem = GetItemByName( (char*)strTemp.c_str() );
		if( !pItem )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,错误的%s:%s!\r\n",common.ustItemID,"合成目标物体",
				strTemp.c_str() );
			goto error_ret;
		}
		pItemRule->ustTargetItemID = pItem->ustItemID;
		pItemRule->pItemTarget = pItem;
	}

	for( iLoop = 0 ; iLoop < 4 ; iLoop ++ )
	{
		//合成原料iLoop
		if( !pReader->GetStringField( iCol++,strTemp ) )
		{
			if( 0 == iLoop )
			{
				//不能一个原料都没有
				OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取%s出错!\r\n",common.ustItemID,"原料1" );
				goto error_ret;
			}
			else
			{
				//skip 原料个数
				iCol ++;
				continue;
			}
		}
		pItem = GetItemByName( (char*)strTemp.c_str() );
		if( !pItem )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取%s:%s出错!\r\n",common.ustItemID,"原料",
				strTemp .c_str());
			goto error_ret;
		}

		pItemRule->material[ pItemRule->iMaterialNum ].pItem = pItem;
		pItemRule->material[ pItemRule->iMaterialNum ].ustItemID = pItem->ustItemID;

		if( !pReader->GetIntField( iCol ++,iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取原料%d个数出错!\r\n",common.ustItemID,iLoop );
			goto error_ret;
		}
		pItemRule->material[ pItemRule->iMaterialNum ].ustCount = iValue;

		pItemRule->iMaterialNum ++;
	}

	if( !pReader->GetFloatField( iCol ++,fValue ) )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取合成几率出错!\r\n",common.ustItemID );
		goto error_ret;
	}

	fValue *= 1000;
	pItemRule->iCreateSuccRate = fValue;
	iCol++;

	if( !pReader->GetIntFieldByName( "强化",iValue ) )
	{
		OutputSlkLoadingMessage( "\tError:createitemrule.slk中ID为:%d的物品,读取合成几率出错!\r\n",common.ustItemID );
		goto error_ret;
	}

	pItemRule->bIntensify = iValue;

	//OutputSlkLoadingMessage( "合成配方：%s 合成目标:%s 原料%d个\r\n",
	//	pItemRule->szItemName.c_str(),pItemRule->pItemTarget->szItemName.c_str(),pItemRule->iMaterialNum );

	AddToMap( pItemRule );
	m_vectorCreateItemRule.push_back(pItemRule);
	return;
error_ret:
	//if( pItemRule )
	//	delete pItemRule;
	return;
}


//性别
//职业
//等级
void CItemDetail::ReadEquipReq( CSlkReader *pReader,SItemCanEquip *pEquip,int &iCol )
{
	std::string strTemp;
	//if( !pReader->GetStringField( iCol,strTemp))
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备的性别需求缺省=-1\r\n" );
	//	pEquip->cEquipSexReq = -1;
	//}
	if( !pReader->GetStringFieldByName( "装备性别需求", strTemp ) )
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
	if( !pReader->GetStringFieldByName( "装备职业需求", strTemp ) )
	{
		for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
			pEquip->abEquipProfessionReq[ iLoop ] = true;
	}

	//if( !pReader->GetStringField( iCol,strTemp))
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备没有定义需求，缺省所有职业都可以装备\r\n" );		
	//	for( iLoop = 0 ; iLoop < ArabicNights::Profession_Max ; iLoop ++ )
	//		pEquip->abEquipProfessionReq[ iLoop ] = true;
	//}
	else
	{
		//pEquip->cEquipProfessionReq = HelperFunc::GetIDByConstString( szTmp
		//	,g_szProfessionType,sizeof( g_szProfessionType )/sizeof(char*) );
		//适用多个职业
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
	//	OutputSlkLoadingMessage( "\tWarning:装备的等级需求缺省=-1\r\n" );
	//	pEquip->stEquipLevelReq = -1;
	//}
	//else
	//{
	//	pEquip->stEquipLevelReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "装备级别需求", iValue ) )
	{
		pEquip->stEquipLevelReq = -1;
	}
	else
	{
		pEquip->stEquipLevelReq = iValue;
	}
	iCol ++;	

	////基本属性点需求
	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备的力量需求缺省=0\r\n" );
	//	pEquip->stStrengthReq = 0;
	//}
	//else
	//{
	//	pEquip->stStrengthReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "装备力量需求", iValue ) )
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
	//	OutputSlkLoadingMessage( "\tWarning:装备的体质需求缺省=0\r\n" );
	//	pEquip->stConstitutionReq = 0;
	//}
	//else
	//{
	//	pEquip->stConstitutionReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "装备体质需求", iValue ) )
	{
		pEquip->stConstitutionReq = 0;
	}
	else
	{
		pEquip->stConstitutionReq = iValue;
	}

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备的敏捷需求缺省=0\r\n" );
	//	pEquip->stAgilityReq = 0;
	//}
	//else
	//{
	//	pEquip->stAgilityReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "装备敏捷需求", iValue ) )
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
	//	OutputSlkLoadingMessage( "\tWarning:装备的智力需求缺省=0\r\n" );
	//	pEquip->stIntelligenceReq = 0;
	//}
	//else
	//{
	//	pEquip->stIntelligenceReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "装备智慧需求", iValue ) )
	{
		pEquip->stIntelligenceReq = 0;
	}
	else
	{
		pEquip->stIntelligenceReq = iValue;
	}



	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备的魔法需求缺省=0\r\n" );
	//	pEquip->stMagicReq = 0;
	//}
	//else
	//{
	//	pEquip->stMagicReq = iValue;
	//}
	iCol++;
	if( !pReader->GetIntFieldByName( "装备魔力需求", iValue ) )
	{
		pEquip->stMagicReq = 0;
	}
	else
	{
		pEquip->stMagicReq = iValue;
	}

	//if( !pReader->GetIntField( iCol, iValue ) )
	//{
	//	OutputSlkLoadingMessage( "\tWarning:装备的魅力需求缺省=0\r\n" );
	//	pEquip->stCharmReq = 0;
	//}
	//else
	//{
	//	pEquip->stCharmReq = iValue;
	//}
	if( !pReader->GetIntFieldByName( "装备魅力需求", iValue ) )
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

	//ID号是否在规定范围内
	if( common.ustItemID < StartID_Weapon || common.ustItemID > EndID_Weapon )
	{
		GetErrorLog()->logString( "weapon id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:weapon.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "weapon.slk中找不到物品ID" );
		return;
	}

	/*for (int loop = 0; loop <5;loop++)
	{*/
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:weapon.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "weapon.slk中找不到物品ID(loop)" );
		return;
	}

	//pItemWeapon = new SItemWeapon;
	pItemWeapon = (SItemWeapon*)AllocItem( 0, sizeof( SItemWeapon ) );
	//pItemWeapon = SLK_NEW(ITEM_WEAPON);
	//pItemWeapon = (WEAPON*)buffer[offset];
	//offset += sizeof(WEAPON);
	if( !pItemWeapon )
	{
		OutputSlkLoadingMessage( "\tError:分配内存出错!\r\n"  );
		GetErrorLog()->logString( "weapon.slk中分配内存出错" );
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
		OutputSlkLoadingMessage( "Error:读取Weapon.slk字段["msg"]出错" ); \
		GetErrorLog()->logString( "Error:读取Weapon.slk字段["msg"]出错" ); \
		continue; \
		} \
		p = iValue; \
		iCol++;

#define WeaponGetFieldBool( p, msg ) \
	if( !Get ( pReader, iCol, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "Error:读取Weapon.slk字段["msg"]出错" ); \
		GetErrorLog()->logString( "Error:读取Weapon.slk字段["msg"]出错" ); \
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

		//WeaponGetFieldInt(pItemWeapon->ustLevel ,             "武器等级"  );
		WeaponGetFieldInt(pItemWeapon->ustModelID[0],          "左手模型ID"  );
		WeaponGetFieldInt(pItemWeapon->ustModelID[1],          "右手模型ID"  );
		WeaponGetFieldInt(pItemWeapon->ustIdleModelID,          "收起ID"  );


		//if( !pReader->GetStringFieldByName( "武器类型(old)", strTemp ) )
		//{
		//	assert( false );
		//	continue;
		//}
		//pItemWeapon->ustWeaponType 
		//	= GetIDByConstString( strTemp.c_str(),g_szWeaponType,sizeof(g_szWeaponType)/sizeof(char*) );
		//iCol ++;

		if( !pReader->GetStringFieldByName( "可装备部位", strTemp ) )
		{
			assert( false );
			continue;
		}
		SetCanEquipByString( pItemWeapon->szCanEquip,strTemp.c_str() );
		iCol ++;


		if (!pReader->GetIntFieldByName("是否双手武器(0/1)",iValue))
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

		//WeaponGetFieldBool(pItemWeapon->bTwoHandWeapon,"是否双手武器(0/1)");



		if( !pReader->GetStringFieldByName( "武器挥动速度", strTemp ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->ustWeaponAttackRate
			= GetIDByConstString(strTemp.c_str(),g_szWeaponAttackRate,sizeof(g_szWeaponAttackRate)/sizeof(char*) );
		iCol ++;

		//装备称号需求
		iCol++;

		//配偶需求
		iCol++;



		//官衔需求（欲留）
		iCol++;
		//装备的需求
		ReadEquipReq( pReader,pItemWeapon,iCol );
		//装备类型
		//肯定是武器
		pItemWeapon->ustEquipType = equip_weapon;

		//////////////////////////////////////////////////////////////////////////

#define WeaponMacroGetInt( p, name ) \
	if( !pReader->GetIntFieldByName( name, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "\tError:读取["name"]失败\r\n" ); \
		GetErrorLog()->logString( "\tError:读取["name"]失败\r\n" ); \
		} \
		else \
		p = iValue;

		//////////////////////////////////////////////////////////////////////////
		WeaponMacroGetInt( pItemWeapon->stAtkRange,         "攻击范围" );
		WeaponMacroGetInt( pItemWeapon->stAddStatus,        "附加状态(敌人)" );
		WeaponMacroGetInt( pItemWeapon->stMyAddStatus,        "附加状态(我)" );
		WeaponMacroGetInt( pItemWeapon->stAddStatusLevel,   "状态等级(敌人)" );
		WeaponMacroGetInt( pItemWeapon->stMyAddStatusLevel,   "状态等级(我)" );
		std::string strWeaponType;
		if( !pReader->GetStringFieldByName( "武器类型", strWeaponType ) ) 
		{
			OutputSlkLoadingMessage( "\tError:读取[武器类型]失败\r\n" );
			GetErrorLog()->logString( "\tError:读取[武器类型]失败\r\n" );
		}
		else
		{
			pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Combat;
			if( strWeaponType == "Combat" )//拳头
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Combat;   
			else if( strWeaponType == "SingleHandBlade" )//单手剑
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_SingleHandBlade;
			//else if( strWeaponType == "LeftHandBlade" )//单手剑
			//	pItemWeapon->stWeaponType = XSanGuo::eWeaponType_LeftHandBlade;
			else if( strWeaponType == "DoubleHandBlade" )//双手剑
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_DoubleHandBlade;
			else if( strWeaponType == "LongBow" )//长弓
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_LongBow;	
			else if( strWeaponType == "Gun" )//枪，弩
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Gun;     
			else if( strWeaponType == "Stick" )//棍棒
				pItemWeapon->stWeaponType = XSanGuo::eWeaponType_Stick;
			else if (strWeaponType == "Dagger")//匕首
				pItemWeapon->stWeaponType = XSanGuo::eWeaponTyoe_Dagger;
			else
			{
				OutputSlkLoadingMessage( "\tError:[武器类型不存在]失败\r\n" );
				assert( false );
			}
		}

		if( pReader->GetIntFieldByName( "发射特效id",iValue ) )
			pItemWeapon->iShotEffectID = iValue;
		else
			pItemWeapon->iShotEffectID = -1;

		if (!pReader->GetFloatFieldByName("状态命中几率",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fStatusRate = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("攻击速度加成",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->stAtkSpeedAdd = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("武器命中系数",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fWeaponHitMod = fValue;
		iCol++;



		if (!pReader->GetIntFieldByName("耐久度",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->stHPMax = iValue;
		iCol++;



		if( !pReader->GetIntFieldByName( "修理价格/点", iValue ) )
		{
			OutputSlkLoadingMessage( "\tError:读取防具的修理价格/点默认0!\r\n" );
			pItemWeapon->stRepairPrice = 0;
		}
		else
		{
			pItemWeapon->stRepairPrice = iValue;
		}
		iCol++;

		if (!pReader->GetIntFieldByName("最大物理攻击",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustPhysicAttMax = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("最小物理攻击",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustPhysicAttMin = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("最大魔法攻击",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->ustMagicAttMax = iValue;
		iCol++;


		//if (!pReader->GetIntFieldByName("最小魔法攻击",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//pItemWeapon->ustMagicAttMin = iValue;
		//iCol++;



		///////属性攻击////////////////////////////////////////////////////////
		//冰
		if( !pReader->GetIntFieldByName( "冰攻击", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Frost = iValue;
		iCol ++;	

		//火
		if( !pReader->GetIntFieldByName( "火攻击", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Blaze = iValue;
		iCol ++;	


		//雷
		if( !pReader->GetIntFieldByName( "雷攻击", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Thunder = iValue;
		iCol ++;	

		//毒
		if( !pReader->GetIntFieldByName( "毒攻击", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemWeapon->stPlayAtt_Poison = iValue;
		iCol ++;

		if (!pReader->GetIntFieldByName("随机属性几率1",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->iRandRate1 = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("随机属性几率2",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->iRandRate2 = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("物理攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("魔法攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Magic] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("电攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("毒攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAtt[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("物理攻击增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("电攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("毒攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttPer[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰冻伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Frost] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火焰伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("雷电伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("巫毒伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sDam[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("命中增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sExact = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("暴击几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sCritical = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("暴击倍数增加",fValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->fCriticalmultiple = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("攻击速度",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sAttSpeed = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("吟唱速度",iValue))
		{
			assert(false);
			continue;
		}
		pItemWeapon->sIntonateSpeed = iValue;	
		iCol++;

		if (!pReader->GetIntFieldByName("幸运增加",iValue))
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

	//	//添加到物品队列中
	//	AddToMap( pItemWeapon );

	//	//建立一个状态数组
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
		//添加到物品队列中
		AddToMap( pItemWeapon );

		//增加一个专门的vector存放Weapon
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

	//ID号是否在规定范围内
	if( common.ustItemID < StartID_Armour || common.ustItemID > EndID_Armour )
	{
		GetErrorLog()->logString( "armour id error" );
		return;
	}

	int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "\tError:armour.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "armour.slk中找不到物品ID" );
		return;
	}

	//for (int loop = 0;loop <5;loop++)
	//{
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:armour.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "armour.slk中找不到物品ID" );
		return;
	}
	//pItemArmour = new SItemArmour;
	pItemArmour = (SItemArmour*)AllocItem( 0, sizeof( SItemArmour ) );
	if( !pItemArmour )
	{
		OutputSlkLoadingMessage( "\tError:分配内存失败!\r\n" );
		GetErrorLog()->logString( "armour.slk中分配内存失败" );
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
		if( !pReader->GetStringFieldByName( "可装备部位", strTemp ) )
		{
			assert( false );
			continue;
		}
		SetCanEquipByString( pItemArmour->szCanEquip,strTemp.c_str() );
		iCol ++;

		if( !pReader->GetIntFieldByName( "模型ID", iValue ) )
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

		if( !pReader->GetStringFieldByName( "装备类型", strTemp ) )
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

		//装备的需求
		ReadEquipReq( pReader,pItemArmour,iCol );

		//装备官衔需求
		iCol++;

		//装备称号需求
		iCol++;

		//装备配偶需求
		iCol++;

		//装备工会称号需求
		iCol++;



		//修理价格/点
		//if( !GetIntField( pReader, iCol, iValue ) )
		if( !pReader->GetIntFieldByName( "修理价格/点", iValue ) )
		{
			//OutputSlkLoadingMessage( "\tError:读取防具的修理价格/点默认0!\r\n" );
			pItemArmour->stRepairPrice = 0;
		}
		else
		{
			pItemArmour->stRepairPrice = iValue;
		}
		iCol++;

		//耐久度Max
		//if( !GetIntField( pReader, iCol, iValue ))
		if( !pReader->GetIntFieldByName( "耐久度", iValue ))
		{
			//	OutputSlkLoadingMessage( "\tError:读取防具的耐久度Max默认-1!\r\n" );
			pItemArmour->stHPMax = ITEMNO_HPMAX;
		}
		else
		{
			pItemArmour->stHPMax = iValue;
		}
		iCol++;


		if( !pReader->GetIntFieldByName( "附加状态(敌人)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stAddStatus  = iValue;
		iCol ++;	

		if( !pReader->GetIntFieldByName( "附加状态(我)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stMyAddStatus  = iValue;
		iCol ++;	


		if( !pReader->GetIntFieldByName( "附加状态等级(敌人)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stAddStatusLevel = iValue;
		iCol ++;	

		if( !pReader->GetIntFieldByName( "附加状态等级(我)", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stMyAddStatusLevel = iValue;
		iCol ++;	



		if( !pReader->GetFloatFieldByName( "状态命中几率", fValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->fStatusRate = fValue;
		iCol ++;	

		//最小物理防御
		if (!pReader->GetIntFieldByName("物理防御",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->ustPhysicDef = iValue;
		iCol++;

		/////////属性防御///////////////////////////////////

		//冰
		if( !pReader->GetIntFieldByName( "冰防御", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Frost = iValue;
		iCol ++;	

		//火
		if( !pReader->GetIntFieldByName( "火防御", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Blaze = iValue;
		iCol ++;	

		////风
		//if( !pReader->GetIntFieldByName( "风防御", iValue ) )
		//{
		//	assert( false );
		//	continue;
		//}
		//pItemArmour->stFengDef = iValue;
		//iCol ++;	

		//雷
		if( !pReader->GetIntFieldByName( "雷防御", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Thunder = iValue;
		iCol ++;	

		//毒
		if( !pReader->GetIntFieldByName( "毒防御", iValue ) )
		{
			assert( false );
			continue;
		}
		pItemArmour->stPlayDef_Poison = iValue;
		iCol ++;

#define ArmourMacroGetFieldInt( t, msg ) \
	if( !pReader->GetIntFieldByName( msg, iValue ) ) \
		{ \
		OutputSlkLoadingMessage( "Error:读取Armour.slk字段["msg"]出错\r\n" ); \
		GetErrorLog()->logString( "Error:读取Armour.slk字段["msg"]出错" ); \
		continue; \
		} \
		t = iValue; \
		iCol ++;

		//胸甲
		//eMaxEquip
		ArmourMacroGetFieldInt( pItemArmour->sPartCount,								"套装组成数量" );
		ArmourMacroGetFieldInt( pItemArmour->sSuitID,									"生成套装ID" );

		ArmourMacroGetFieldInt( pItemArmour->iRandRate1,								"随机属性几率1" );
		ArmourMacroGetFieldInt( pItemArmour->iRandRate2,								"随机属性几率2" );
		//////////////////////////////////////////////////////////////////////////////
		if (!pReader->GetIntFieldByName("物理攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("魔法攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Magic] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("电攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("毒攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAtt[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("物理攻击增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Physics] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("电攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("毒攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttPer[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("冰冻伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Frost] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("火焰伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("雷电伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("巫毒伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDam[ePlayDef_Poison] = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("命中增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sExact = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("闪避增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDodge = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("暴击增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sCritical = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("暴击倍数增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sCriticalmultiple = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("攻击速度",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sAttSpeed = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("吟唱速度",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sIntonateSpeed = iValue;
		iCol++;

		if (!pReader->GetFloatFieldByName("移动速度",fValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->fMoveSpeed = fValue;
		iCol++;

		if (!pReader->GetIntFieldByName("物理防御增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Max] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("冰冻抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Frost] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("火焰抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("雷电抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Thunder] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("巫毒抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDef[ePlayDef_Poison] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("物理防御改变增加%",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sDefPer[ePlayDef_Physics] = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("生命最大值增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpMax = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("魔法最大值增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpMax = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("生命最大值增加(%)",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpMaxPer = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("魔法最大值增加%",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpMaxPer = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("生命恢复增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sHpRestore = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("魔法恢复增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sMpRestore = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("物理反弹增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sReboundRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("合成几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sComposeRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("精炼几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sProficiencyRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("强化几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sStrengthenRate = iValue;
		iCol++;


		if (!pReader->GetIntFieldByName("镶嵌几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pItemArmour->sEnchaseRate = iValue;
		iCol++;

		if (!pReader->GetIntFieldByName("幸运增加",iValue))
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
		//添加到物品队列中
		AddToMap( pItemArmour );

		//增加一个专门的vector来存放aromour, glove, shoe
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

//取得技能领悟条件
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
		OutputSlkLoadingMessage( "\t查找职业的领悟条件或使用条件:找不到职业:%s\r\n",szProfession );
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
//		OutputSlkLoadingMessage( "\t查找职业的领悟条件：找不到技能:%s\r\n",szSkill );
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
//		//职业需求
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
//					OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
//				}
//			}
//		}
//		else
//		//技能使用需求
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
//					OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
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
//		//职业需求
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
//					OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
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

	//ID号是否在规定范围内
	if( common.ustItemID < StartID_Skill || common.ustItemID > EndID_Skill )
	{
		GetErrorLog()->logString( "skill id error" );
		return;
	}

	int iLineNo = pReader->FindFirstLineByIntField( 1,common.ustItemID );
	if( -1 == iLineNo )
	{
		OutputSlkLoadingMessage( "Error:在技能表中找不到物品:%d\r\n",common.ustItemID );
		char string[256];
		sprintf(string, "在技能表中找不到物品:%d",common.ustItemID);
		//
		return;
	}

	//每个技能都有十个等级
	for( int iLoop = 0;iLoop<10;iLoop++ )
	{
		if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo+iLoop ))
		{
			OutputSlkLoadingMessage( "Error:在技能表中找不到物品:%d\r\n",common.ustItemID );
			GetErrorLog()->logString( "skill.slk找不到物品ID" );
			return;
		}

		//pItemSkill = new SItemSkill;
		pItemSkill = (SItemSkill*)AllocItem( 0, sizeof( SItemSkill ) );
		if( !pItemSkill )
		{
			OutputSlkLoadingMessage( "Error:分配skill需要的内存出错\r\n",common.ustItemID );
			char string[256];
			sprintf(string, "分配skill需要的内存出错:%d",common.ustItemID);
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
			OutputSlkLoadingMessage( "Error:读取skill.slk字段["msg"]出错\r\n" ); \
			GetErrorLog()->logString( "Error:读取skill.slk字段["msg"]出错" ); \
			continue; \
			} \
			t = iValue; \
			iCol++;

#define SkillMacroGetFiledAction( t, msg ) \
	if( !pReader->GetStringFieldByName( msg, strTemp ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:读取skill.slk字段["msg"]出错\r\n" ); \
			char string[256]; \
			sprintf(string, "读取skill.slk字段["msg"]出错!%d",common.ustItemID); \
			MessageBox( NULL, string, "warning", MB_OK ); \
			assert( false ); \
			continue; \
			} \
			t = ArabicNightsAction::FindActionIdByName( strTemp.c_str() ); \
			iCol++;

			//////////////////////////////////////////////////////////////////////////
			if ( !pReader->GetStringFieldByName( "技能名字", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取skill.slk字段[技能名字]出错\r\n" );
				char string[256];
				sprintf(string, "读取skill.slk字段[技能名字]出错!%d",common.ustItemID);
				MessageBox( NULL, string, "warning", MB_OK );
				assert( false ); 
			}
			//pItemSkill->szSkillName = strTemp;
			pItemSkill->dwSkillNameAddr = AllocStringCopy( strTemp.c_str() );
			iCol++;

			//////////////////////////////////////////////////////////////////////////
			SkillMacroGetFiledAction( pItemSkill->ustIDSkillAction[0],      "技能动作名字1" );
			SkillMacroGetFiledAction( pItemSkill->ustIDSkillAction[1],      "技能动作名字2" );
			SkillMacroGetFieldInt( pItemSkill->ustLevel,                    "技能等级" );
			SkillMacroGetFieldInt( pItemSkill->ustPrepTime,                 "吟唱时间(ms)" );
			SkillMacroGetFiledAction( pItemSkill->ustIDPrepAction,          "吟唱动作名字" );
			SkillMacroGetFieldInt( pItemSkill->iIntonateEffect,             "吟唱特效" );
			SkillMacroGetFieldInt( pItemSkill->iAttackedEffect,             "玩家效果" );
			SkillMacroGetFieldInt( pItemSkill->ustSkillEffect,              "技能效果" );
			SkillMacroGetFieldInt( pItemSkill->iAttackedEffect,             "目标效果" );
			SkillMacroGetFiledAction( pItemSkill->ustIDTargetHitAction,     "目标被击动作" );
			SkillMacroGetFieldInt( pItemSkill->stTargetHitActionRate,       "被击动作机率" );
			SkillMacroGetFieldInt( pItemSkill->ustMeAddStatusID,            "附加状态(我)" );
			SkillMacroGetFieldInt( pItemSkill->ustMeAddStatusLevel,         "附加等级(我)" );
			SkillMacroGetFieldInt( pItemSkill->ustDstAddStatusID,           "附加状态(对方)" );
			SkillMacroGetFieldInt( pItemSkill->ustDstAddStatusLevel,        "附加等级(对方)" );
			SkillMacroGetFieldInt( pItemSkill->ustStatusHitRate,            "状态命中几率" );
			SkillMacroGetFieldInt( pItemSkill->dwSubComboStatus,            "解除状态" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_0],            "解除状态0" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_1],            "解除状态1" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_2],            "解除状态2" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_3],            "解除状态3" );
			SkillMacroGetFieldInt( pItemSkill->dwClearStatus[CLEAR_STATUS_4],            "解除状态4" );

			//SkillMacroGetFieldInt( pItemSkill->dwSubComboStatus,            "解除状态" );
			//            SkillMacroGetFieldInt( pItemSkill->ustPhysicAdd,                "物理攻击加成" );
			//          SkillMacroGetFieldInt( pItemSkill->ustMagicAdd,                 "魔法攻击加成" );
			//        SkillMacroGetFieldInt( pItemSkill->ustPhysicAtt,                "物理攻击力" );
			//      SkillMacroGetFieldInt( pItemSkill->ustMagicAtt,                 "魔法攻击力" );
			SkillMacroGetFieldInt( pItemSkill->ustHoldTime,                 "僵硬时间" );

			if( !pReader->GetStringFieldByName( "使用结算公式", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取使用结算公式出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中使用结算公式出错" );
				continue;
			}
			pItemSkill->ustDamageBalanceType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szBalanceType, sizeof(g_szBalanceType)/sizeof( char *) );

			if( -1==pItemSkill->ustDamageBalanceType )
			{
				OutputSlkLoadingMessage( "Error:读取使用结算公式出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中使用结算公式出错" );
				continue;
			}
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->ustSkillActionSpeed, "播放速度" );
			SkillMacroGetFieldInt( pItemSkill->ustCostHP,           "消耗HP" );
			SkillMacroGetFieldInt( pItemSkill->ustCostHPPer,        "消耗HP(%)" );
			SkillMacroGetFieldInt( pItemSkill->ustCostMP,           "消耗MP" );
			SkillMacroGetFieldInt( pItemSkill->ustCostMPPer,         "消耗MP(%)" );
			//SkillMacroGetFieldInt( pItemSkill->ustCostTP,           "消耗TP" );

			if( !pReader->GetStringFieldByName( "技能的类型", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取技能类型出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能类型出错" );
				continue;
			}
			pItemSkill->stSkillType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
				g_szSkillType,sizeof(g_szSkillType)/sizeof( char* ) );

			if( -1 == pItemSkill->stSkillType )
			{
				OutputSlkLoadingMessage( "Error:读取技能类型出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能类型出错" );
				continue;
			}
			iCol ++;

			if( !pReader->GetStringFieldByName( "技能所属类别", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取技能所属的总类出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能所属的总类出错" );
				continue;
			}
			pItemSkill->stGeneralType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
				g_szSkillGeneralType, sizeof(g_szSkillGeneralType)/sizeof( char* ) );

			if( -1 == pItemSkill->stGeneralType )
			{
				OutputSlkLoadingMessage( "Error:读取技能所属的总类出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能所属的总类出错" );
				continue;
			}
			iCol++;

			if( !pReader->GetStringFieldByName( "目标类型", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取技能作用对象出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能作用对象出错" );
				continue;
			}
			//从string得到作用类型
			iValue = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szTargetString,sizeof(g_szTargetString)/sizeof(char*) );		

			if( -1 == iValue )
			{
				OutputSlkLoadingMessage( "Error:读取技能作用类型出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能作用类型出错" );
				continue;
			}
			pItemSkill->stTargetType = iValue;		
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->iDurationTime,       "持续时间" );
			SkillMacroGetFieldInt( pItemSkill->iDamageBalanceDelay, "结算间隔" );

			if( !pReader->GetStringFieldByName( "持续中心类型", strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取技能持续中心类型出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能持续中心类型出错" );
				continue;
			}
			//从string得到持续中心类型 12
			iValue = GetIDByConstString( strTemp.c_str(),g_szEffectCenter,sizeof(g_szEffectCenter)/sizeof(char*) );

			if( -1 == iValue )
			{
				OutputSlkLoadingMessage( "Error:读取技能持续中心类型出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能持续中心类型出错" );
				continue;
			}
			pItemSkill->stEffectCenterType = iValue;		
			iCol ++;

			//SkillMacroGetFieldInt( pItemSkill->ustAttackInterval,                       "持续攻击间隔(ms)" );
			SkillMacroGetFieldInt( pItemSkill->cLearnProfessionReq,                     "学习职业需求" );
			SkillMacroGetFieldInt( pItemSkill->stLearnLevelReq,                         "学习等级需求" );
			SkillMacroGetFieldInt( pItemSkill->stStopSkillPrepRate,                     "打断吟唱几率(%)" );
			SkillMacroGetFieldInt( pItemSkill->stRangeCanCast,                          "施法距离" );
			SkillMacroGetFieldInt( pItemSkill->stDamageEffectDistance,                  "伤害有效距离" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.cRangeType,             "技能范围形状" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.radius,     "作用范围" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 0 ].x, "偏移坐标1x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 0 ].y, "偏移坐标1y" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 1 ].x, "偏移坐标2x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 1 ].y, "偏移坐标2y" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 2 ].x, "偏移坐标3x" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 2 ].y, "偏移坐标3y" );	
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 3 ].x, "偏移坐标4x" );
			SkillMacroGetFieldInt( pItemSkill->sEffectRangeData.sDetailData.ptCorner[ 3 ].y, "偏移坐标4y" );

			if(!pReader->GetIntFieldByName( "是否需要武器", iValue ))
			{
				OutputSlkLoadingMessage( "Error:读取是否需要武器出错!\r\n" );
				GetErrorLog()->logString( "skill.slk中技能是否需要武器出错" );
				continue;
			}
			pItemSkill->bNeedWeapon = iValue?true:false;
			iCol++;

			SkillMacroGetFieldInt( pItemSkill->stUseItem,								"道具要求" );
			if(!pReader->GetIntFieldByName( "是否维持技能", iValue ))
			{
				//缺省为false
				iValue = 0;
			}
			pItemSkill->bHoldSkill = iValue>0?true:false;
			iCol++;

			//维持动作
			if(!pReader->GetStringFieldByName( "维持动作", strTemp ))
			{
				OutputSlkLoadingMessage( "Error:读取技能维持动作出错!\r\n" );
				GetErrorLog()->logString( "skill.slk技能维持动作出错" );
				continue;
			}
			pItemSkill->ustIDHoldAction = ArabicNightsAction::FindActionIdByName( strTemp.c_str() );
			iCol ++;

			SkillMacroGetFieldInt( pItemSkill->ustHoldEffect,       "维持特效" );
			SkillMacroGetFieldInt( pItemSkill->dwSkillColddownTime, "技能冷却时间(Colddown)" );

			if(!pReader->GetStringFieldByName( "施法目标类型", strTemp ))
			{
error_casttarget:
				OutputSlkLoadingMessage( "Error:读取施放目标特性出错!\r\n" );
				GetErrorLog()->logString( "skill.slk施放目标特性出错" );				
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


			//分析easyusedata;
			pItemSkill->easyusedata.SEasyUseData::SEasyUseData();		

			if( target_friend == pItemSkill->stTargetType )
				pItemSkill->easyusedata.bApplyToFriend = true;

			//普通攻击的 作用目标肯定是敌人
			if (IsNormalAttack( pItemSkill->ustItemID ) )
				pItemSkill->easyusedata.bApplyToFriend = false;
			//判断是否是供给
			if (IsNormalAttack( pItemSkill->ustItemID ))
				pItemSkill->easyusedata.bSkillWithDamage = true;
			switch (pItemSkill->ustDamageBalanceType)
			{
			case balancetype_phydamage:// = 1,	//物理伤害结算
			case balancetype_magdamage:// = 2,	//魔法伤害结算
			case balancetype_addextrahp://= 5,//瞬间吸血
				pItemSkill->easyusedata.bSkillWithDamage = true;
				break;
			case balancetype_none:// = 0,		//没有任何结算
			case balancetype_restorehp:// = 3,	//回HP结算
			case balancetype_relive://	  = 4,	//复活结算
				//case balancetype_restoretp:// = 6,	//回TP结算
			case balancetype_damagemp:          // 伤害MP
			default:
				break;
			}

			//SkillMacroGetFieldInt( pItemSkill->stPassivePhyAtkAdd ,         "被物理攻击力附加" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveMPMaxAdd ,          "被魔法值上限" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveHPMaxAdd ,          "被生命上限" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveAutoRestoreHP ,     "被生命回复" );
			//SkillMacroGetFieldInt( pItemSkill->stPassiveHitAdd ,            "被命中率" );
			//SkillMacroGetFieldInt( pItemSkill->stCurHpSet ,                 "当前生命" );
			//SkillMacroGetFieldInt( pItemSkill->stCurMPSet ,                 "当前魔法值" );
			SkillMacroGetFieldInt( pItemSkill->stSkillNeed ,                "技能条件" );
			SkillMacroGetFieldInt( pItemSkill->stRankNeed ,                 "官阶条件" );
			SkillMacroGetFieldInt( pItemSkill->stMoneyNeed,                 "学习所需金钱" );
			SkillMacroGetFieldInt( pItemSkill->stSkillLevelNeed,            "学习牵制技能等级" );  


			SkillMacroGetFieldInt( pItemSkill->stSTRNeed,                   "力量要求" );
			SkillMacroGetFieldInt( pItemSkill->stVITNeed,                   "体力要求" );
			SkillMacroGetFieldInt( pItemSkill->stAGINeed,                   "敏捷要求" );
			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "智力要求" );

			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "魔力要求" );
			SkillMacroGetFieldInt( pItemSkill->stINTNeed,                   "运气要求" );

			if( !pReader->GetStringFieldByName( "武器类型需求", strTemp ) )
			{
				//assert( false && "skill.slk 武器类型要求" );
				pItemSkill->stWeaponNeed = -1;
			}
			pItemSkill->stWeaponNeed
				= GetIDByConstString( strTemp.c_str(),g_szWeaponType,sizeof(g_szWeaponType)/sizeof(char*) );


			SkillMacroGetFieldInt( pItemSkill->stEnmity,                   "仇恨值" );



			if( pReader->GetFloatFieldByName( "参数",fValue ) )
				pItemSkill->fBonusFactor = fValue;
			else
				pItemSkill->fBonusFactor = 1.0f;
			iCol++;

			bReadSucc = true;
			break;
		}
		if( bReadSucc )
		{
			//添加到物品队列中
			AddToMap( pItemSkill );

			//建立一个技能物品ID到技能序号的 转换
			m_mapSkillNO.insert( mapSkillNO::value_type( pItemSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
			m_vecSkill.push_back( pItemSkill->ustItemID );

			//建立一个技能数组(只限法术)
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

	//ID号是否在规定范围内
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
		OutputSlkLoadingMessage( "Error:在状态表中找不到物品:%d\r\n",common.ustItemID );
		GetErrorLog()->logString( "status.slk中找不到物品ID" );

		char buffer[128];
		sprintf(buffer,"itemid=%d",common.ustItemID);
		MessageBox(NULL,buffer,"test",MB_OK);

		return;
	}

	//每个状态都有十个等级
	for( int iLoop = 0;iLoop<10;iLoop++ )
	{
		if( CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo+iLoop ))
		{
			OutputSlkLoadingMessage( "Error:在状态表中找不到物品:%d\r\n",common.ustItemID );
			GetErrorLog()->logString( "status.slk中找不到物品ID(loop)" );
			return;
		}

		//pItemStatus =new SItemStatus;
		pItemStatus = (SItemStatus*)AllocItem( 0, sizeof( SItemStatus ) );
		if( !pItemStatus )
		{
			OutputSlkLoadingMessage( "Error:分配status需要的内存出错\r\n",common.ustItemID );
			GetErrorLog()->logString( "status.slk中分配需要的内存出错" );
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
			OutputSlkLoadingMessage( "Error:读取status.slk字段["msg"]出错" ); \
			GetErrorLog()->logString( "Error:读取status.slk字段["msg"]出错" ); \
			continue; \
			} \
			t = iValue; \
			iCol++;

#define MacroGetFieldBool( t, msg ) \
	if( !GetIntField( pReader, iCol, iValue ) ) \
			{ \
			OutputSlkLoadingMessage( "Error:读取status.slk字段["msg"]出错" ); \
			GetErrorLog()->logString( "Error:读取status.slk字段["msg"]出错" ); \
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
			OutputSlkLoadingMessage( "Error:读取status.slk字段["msg"]出错" ); \
			GetErrorLog()->logString( "Error:读取status.slk字段["msg"]出错" ); \
			continue; \
			} \
			t = fValue; \
			iCol++;

			//////////////////////////////////////////////////////////////////////////

			bReadSucc = false;
			iCol = 3;

			//状态等级
			if(!GetIntField( pReader, iCol, iValue ))
			{
				OutputSlkLoadingMessage( "Warning:本状态缺省等级=1!\r\n" );	
				pItemStatus->ustLevel = 1;
			}
			else
				pItemStatus->ustLevel = iValue;
			iCol++;		


			MacroGetFieldInt( pItemStatus->ustEffectID,             "状态模型ID" );
			MacroGetFieldInt( pItemStatus->iDurationTime,           "状态持续时间(ms)" );
			MacroGetFieldInt( pItemStatus->iBalanceDelayTime,       "影响间隔时间" );
			MacroGetFieldInt( pItemStatus->stType,                  "状态类型" );
			MacroGetFieldInt( pItemStatus->stPriority,              "优先级别" );

			//使用结算公式
			if( !GetStringField( pReader, iCol, strTemp ) )
			{
				OutputSlkLoadingMessage( "Error:读取使用结算公式出错!\r\n" );
				GetErrorLog()->logString( "status.slk中读取使用结算公式出错" );
				continue;
			}
			pItemStatus->stBalanceType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
				g_szStatusBalanceType, sizeof(g_szStatusBalanceType)/sizeof(char*) );
			iCol ++;

			MacroGetFieldInt( pItemStatus->stBalanceParam,						"结算使用的参数" );	//1
			MacroGetFieldBool( pItemStatus->bAttckedNoStatus,						"受到攻击的时候是否解除该状态" );			//2
			MacroGetFieldBool( pItemStatus->bAttckNoStatus,							"攻击的时候是否解除该状态" );			//2

			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_STRENGTH],			"改变强壮" );//3
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_CONSTITUTION],		"改变体质" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_AGILITY],			"改变敏捷" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_MAGIC],				"改变魔力" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_INTELLIGENCE],		"改变感知" );
			MacroGetFieldInt( pItemStatus->stChanged_Base[BATTR_CHARM],				"改变运气" );
			MacroGetFieldFloat( pItemStatus->fChanged_ExpMul,						"经验值改变" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Physics],		"物理攻击改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Magic],		"魔法强度改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Frost],		"冰冻攻击改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Blaze],		"火焰攻击改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Thunder],		"雷电攻击改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_AttPer[ePlayAtt_Poison],		"巫毒攻击改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Physics],		"物理攻击改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Magic],		"魔法强度改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Frost],		"冰冻攻击改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Blaze],		"火焰攻击改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Thunder],		"雷电攻击改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Att[ePlayAtt_Poison],		"巫毒攻击改变" );
			MacroGetFieldInt( pItemStatus->stChanged_PhysicsDefPer,				"物理防御改变%" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Physics],		"物理防御改变" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Frost],		"冰冻抗性" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Blaze],		"火焰抗性" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Thunder],		"雷电抗性" );
			MacroGetFieldInt( pItemStatus->stChanged_Def[ePlayDef_Poison],		"巫毒抗性" );
			MacroGetFieldInt( pItemStatus->stChangWeapon_Attribute,				"武器属性改变" );
			MacroGetFieldInt( pItemStatus->stChangWeapon_Only,					"武器专属状态" );
			MacroGetFieldInt( pItemStatus->stChanged_FianHurtPer,				"伤害改变(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_FianHurt,					"伤害改变" );			
			MacroGetFieldInt( pItemStatus->stMagic_FreeHurtPer,					"魔法值抵扣伤害(%)" );
			MacroGetFieldInt( pItemStatus->stMagic_FreeHurt,					"魔法值抵扣伤害" );	
			MacroGetFieldInt( pItemStatus->stChanged_HPMaxPer,					"生命最大值(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_HPMax,						"生命最大值" );
			MacroGetFieldInt( pItemStatus->stChanged_MPMaxPer,					"魔法最大值(%)" );
			MacroGetFieldInt( pItemStatus->stChanged_MPMax,						"魔法最大值" ); 
			MacroGetFieldInt( pItemStatus->stResume_HP,							"生命恢复" );
			MacroGetFieldInt( pItemStatus->stResume_MP,							"魔法恢复" ); 
			MacroGetFieldInt( pItemStatus->stChanged_HP,						"改变生命" );
			MacroGetFieldInt( pItemStatus->stChanged_MP,						"改变魔法" ); 
			MacroGetFieldInt( pItemStatus->stChanged_AttRect,					"改变攻击距离" );
			MacroGetFieldInt( pItemStatus->stChanged_Hit,						"命中能力" ); 
			MacroGetFieldInt( pItemStatus->stChanged_Hedge,						"躲闪能力" );
			MacroGetFieldInt( pItemStatus->stChanged_FrenzyPer,					"暴击几率" ); 
			MacroGetFieldFloat( pItemStatus->fChanged_FrenzyVal,					"暴击倍数" );
			MacroGetFieldInt( pItemStatus->stChanged_ReboundVal,				"伤害反弹" ); 
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Physics],	"物理伤害免疫" );	
			//MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Magic],	"物理伤害免疫" );	
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Frost],		"冰冻伤害免疫" );			
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Blaze],		"火焰伤害免疫" );
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Thunder],	"雷电伤害免疫" );		
			MacroGetFieldBool( pItemStatus->bHurtImmunity[ePlayAtt_Poison],		"巫毒伤害免疫" );		
			MacroGetFieldInt( pItemStatus->stStatusFree,							"状态免疫" ); 
			MacroGetFieldInt( pItemStatus->stChanged_StatusHitPer,					"状态抵抗" ); 
			MacroGetFieldBool( pItemStatus->bHedgeNull,								"无视回避" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraHPRate,						"吸血比例" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraHPVal,						"吸血值" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraMPRate,						"吸魔比例" ); 
			MacroGetFieldInt( pItemStatus->stAbsorbExtraMPVal,						"吸魔值" ); 
			MacroGetFieldFloat( pItemStatus->fMoveSpeedChanged,						"移动速度" ); 
			MacroGetFieldInt( pItemStatus->stAttSpeedChanged,						"攻击速度" ); 
			MacroGetFieldBool( pItemStatus->bIsMoveAtt,								"移动攻击" ); 
			MacroGetFieldInt( pItemStatus->stPrepSpeedChanged,						"吟唱速度" ); 
			MacroGetFieldBool( pItemStatus->bIsMove,								"不能移动" ); 
			MacroGetFieldBool( pItemStatus->bIsAtt,									"不能物理攻击" ); 
			MacroGetFieldBool( pItemStatus->bIsUsingMagic,							"不能使用法术" ); 
			MacroGetFieldBool( pItemStatus->bIsUsingTools,							"不能使用道具" ); 
			MacroGetFieldBool( pItemStatus->bIsRandWalk,							"随机乱跑" ); 
			MacroGetFieldBool( pItemStatus->bCanFindByMonster,						"怪物发现" ); 
			MacroGetFieldInt( pItemStatus->stChanged_MonsterView,					"怪物至盲" ); 
			MacroGetFieldInt( pItemStatus->stChanged_MonsterEnmity,					"产生怪物仇恨" ); 
			MacroGetFieldInt( pItemStatus->stAttNumFree,							"抗击打次数" ); 
			MacroGetFieldBool( pItemStatus->bConfusionMonster,						"使得怪物互击" ); 
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Frost],			"冰冻伤害" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Blaze],			"火焰伤害" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Thunder],		"雷电伤害" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Poison],			"巫毒伤害" );

			//MacroGetFieldInt( pItemStatus->stChangedSkill_Hurt[eElement_Frost],			"物理伤害" );

			MacroGetFieldInt( pItemStatus->stComposeOdds,	"合成几率" );
			MacroGetFieldInt( pItemStatus->stRefineOdds,	"精炼几率" );
			MacroGetFieldInt( pItemStatus->stIntensifyOdds,	"强化几率" );
			MacroGetFieldInt( pItemStatus->stInlayOdds,		"镶嵌几率" );

			MacroGetFieldInt( pItemStatus->stChangedPhy_Hurt,			"物理伤害" );
			MacroGetFieldInt( pItemStatus->stChangedPhy_HurtPer,			"物理伤害(%)" );

			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Frost],			"冰冻伤害(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Blaze],			"火焰伤害(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Thunder],		"雷电伤害(%)" );
			MacroGetFieldInt( pItemStatus->stChangedSkill_HurtPer[eElement_Poison],			"巫毒伤害(%)" );

			bReadSucc = true;
			break;
		}

		if( bReadSucc )
		{
			//添加到物品队列中
			AddToMap( pItemStatus );

			//建立一个状态数组
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

//取得对应道具的类型
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

//某个ITEM(不仅是物品)应该放在哪个背包
short CItemDetail::GetItemBelongBag( unsigned short ustItemID )
{
	GetErrorLog()->logString( "该函数不用!!!!!!" );

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

		//职业名字	
		std::string strProfessionName;
		//if( !reader.GetStringField( iCol,profession.szName) )
		if( !reader.GetStringField( iCol,strProfessionName) )
		{
			GetErrorLog()->logString( "职业名字缺失");
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
			OutputSlkLoadingMessage( "\t职业重名：%s\r\n", profession.GetName() );// profession.szName );
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
//获取状态的相关函数
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
//获取状态的相关函数
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
		//取新的slk资源
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

		//怪物名字

		//if( !reader.GetStringField( iCol,monster.strName) )
		if( !reader.GetStringField( iCol,strMonsterName) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物名字出错!\r\n" );
			GetErrorLog()->logString( " monster.slk 载入怪物名字出错");
			goto load_error;
		}
		monster.dwNameAddr = AllocStringCopy( strMonsterName.c_str() );
		iCol ++;

		//模型ID
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物模型ID出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物模型ID出错");
			goto load_error;
		}
		monster.iModelID = iValue;
		iCol ++;

		//怪物声音模板

		//if( !reader.GetStringField( iCol,monster.strCreatureSound ) )
		if( !reader.GetStringField( iCol, strCreatureSound ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物声音模板出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物声音模板出错");
			goto load_error;
		}
		monster.dwCreatureSoundAddr = AllocStringCopy( strCreatureSound.c_str() );

		iCol ++;

		//怪物类别
		if( !GetStringField( &reader, iCol, strTemp ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物类别出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物类别出错");
			goto load_error;
		}
		monster.stMonsterType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
			g_szMonsterType, sizeof(g_szMonsterType)/sizeof( char* ) );
		iCol ++;

		//体型修正
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入体型修正出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入体型修正出错");
			goto load_error;
		}
		monster.stBodySize = iValue;
		iCol ++;

		//级别
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入怪物级别出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物级别出错");
			goto load_error;
		}
		monster.stLevel = iValue;
		iCol ++;

		//经验值
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入经验值出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入经验值出错");
			goto load_error;
		}
		monster.stRewardExp = iValue;
		iCol ++;

		//力量
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入力量出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入力量值出错");
			goto load_error;
		}
		monster.stStrength = iValue;
		iCol ++;

		//体质
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入体质出错!\r\n" );
			GetErrorLog()->logString("monster.slk 载入体质出错");
			goto load_error;
		}
		monster.stConstitution = iValue;
		iCol ++;

		//敏捷
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入敏捷出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入敏捷出错");
			goto load_error;
		}
		monster.stAgility = iValue;
		iCol ++;

		//魔力
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入魔力出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入魔力出错");
			goto load_error;
		}
		monster.stMagic = iValue;
		iCol ++;

		//感知
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入感知出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入感知出错");
			goto load_error;
		}
		monster.stIntelligence = iValue;
		iCol ++;

		//运气
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t 载入运气出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入运气出错");
			goto load_error;
		}
		monster.stCharm = iValue;
		iCol ++;

		//最大HP
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物最大HP出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物最大HP出错!");
			goto load_error;
		}
		monster.stHPMax = iValue;
		iCol ++;

		//最大MP
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物最大MP出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物最大MP出错!");
			goto load_error;
		}
		monster.stMPMax = iValue;
		iCol ++;

		// HP恢复速度
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物回HP出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物回HP出错!");
			goto load_error;
		}
		monster.stHPRestore = iValue;
		iCol ++;

		// MP恢复速度
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物回MP出错!\r\n" );
			GetErrorLog()->logString( "monster.slk 载入怪物回MP出错!");
			goto load_error;
		}
		monster.stMPRestore = iValue;
		iCol ++;

		//精确值
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物命中率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物命中率出错!");
			goto load_error;
		}
		monster.stExact = iValue;
		iCol ++;

		//躲避率
		if( !reader.GetIntField( iCol,iValue ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物躲避率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物躲避率出错!");
			goto load_error;
		}
		monster.stDodge = iValue;
		iCol ++;

		//视野
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物视野出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物视野出错!");
			goto load_error;
		}
		monster.stView = iValue;
		iCol ++;

		//最小物理攻击
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入最小物理攻击出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入最小物理攻击出错!");
			goto load_error;
		}
		monster.stPhysicAttMin = iValue;
		iCol ++;

		//最大物理攻击
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入最大物理攻击出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入最大物理攻击出错!");
			goto load_error;
		}
		monster.stPhysicAttMax = iValue;
		iCol ++;

		//最小魔法攻击
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入最小魔法攻击出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入最小魔法攻击出错!");
			goto load_error;
		}
		monster.stMagicAttMin = iValue;
		iCol ++;

		//最大魔法攻击
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入最大魔法攻击出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入最大魔法攻击出错!");
			goto load_error;
		}
		monster.stMagicAttMax = iValue;
		iCol ++;

		//攻击速度
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入攻击速度出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入攻击速度出错!");
			goto load_error;
		}
		monster.stAttackRate = iValue;
		iCol ++;

		//暴击几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入暴击几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入暴击几率出错!");
			goto load_error;
		}
		monster.stCriticalRate = iValue;
		iCol ++;

		//物理防御
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入物理防御出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入物理防御出错!");
			goto load_error;
		}
		monster.stPhysicDef = iValue;
		iCol ++;

		//魔法防御
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入魔法防御出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入魔法防御出错!");
			goto load_error;
		}

		monster.stMagicDef = iValue;
		iCol ++;

		//冰攻
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入冰攻出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入冰攻出错!");
			goto load_error;
		}
		monster.stFrostAtt = iValue;
		iCol ++;

		//火攻
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入火攻出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入火攻出错!");
			goto load_error;
		}
		monster.stBlazeAtt = iValue;
		iCol ++;

		//雷攻
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入雷攻出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入雷攻出错!");
			goto load_error;
		}
		monster.stThunderAtt = iValue;
		iCol ++;

		//毒攻
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入毒攻出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入毒攻出错!");
			goto load_error;
		}
		monster.stPoisonAtt = iValue;
		iCol ++;

		//冰防
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入冰防出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入冰防出错!");
			goto load_error;
		}
		monster.stFrostDef = iValue;
		iCol ++;

		//火防
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入火防出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入火防出错!");
			goto load_error;
		}
		monster.stBlazeDef = iValue;
		iCol ++;

		//雷防
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入雷防出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入雷防出错!");
			goto load_error;
		}
		monster.stThunderDef = iValue;
		iCol ++;

		//毒防
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入毒防出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入毒防出错!");
			goto load_error;
		}
		monster.stPoisonDef = iValue;
		iCol ++;

		//怪物的追击时间
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入追击时间出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入追击时间出错!");
			goto load_error;
		}
		monster.dwCatchTime = iValue * 1000;
		iCol ++;

		//怪物的移动速度
		if( !reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入怪物移动速度出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物移动速度出错!");
			goto load_error;
		}
		monster.fMoveSpeed = fValue;
		iCol ++;

		//可能使用的技能1
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能使用的技能1出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能使用的技能1出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 0 ] = iValue;
		else
			monster.iSkillID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能使用的技能2
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能使用的技能2出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能使用的技能2出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 1 ] = iValue;
		else
			monster.iSkillID[ 1 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能使用的技能3
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能使用的技能3出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能使用的技能3出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.iSkillID[ 2 ] = iValue;
		else
			monster.iSkillID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//技能1等级
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能1等级出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能1等级出错!");
			goto load_error;
		}
		monster.stSkillLevel[ 0 ] = iValue;
		iCol ++;

		//技能2等级
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能2等级出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能2等级出错!");
			goto load_error;
		}
		monster.stSkillLevel[ 1 ] = iValue;
		iCol ++;

		//技能3等级
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能3等级出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能3等级出错!");
			goto load_error;
		}
		monster.stSkillLevel [ 2 ] = iValue;
		iCol ++;

		//技能1使用概率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能1使用概率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能1使用概率出错!");
			goto load_error;
		}
		monster.stSkillRate[ 0 ] = iValue;
		iCol ++;

		//技能2使用概率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能2使用概率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能2使用概率出错!");
			goto load_error;
		}
		monster.stSkillRate[ 1 ] = iValue;
		iCol ++;

		//技能3使用概率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入技能3使用概率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入技能3使用概率出错!");
			goto load_error;
		}
		monster.stSkillRate[ 2 ] = iValue;
		iCol ++;

		//可能掉落的物品1
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品1出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品1出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 0 ] = iValue;
		else
			monster.stGoodDropID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能掉落的物品1几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品1几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品1几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 0 ] = iValue;
		iCol ++;

		//可能掉落的物品2
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品2出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品2出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 1 ] = iValue;
		else
			monster.stGoodDropID[ 1 ] = ArabicNights::ErrorUnsignedShortID;

		iCol ++;

		//可能掉落的物品2几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品2几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品2几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 1 ] = iValue;
		iCol ++;

		//可能掉落的物品3
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品3出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品3出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 2 ] = iValue;
		else
			monster.stGoodDropID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能掉落的物品3几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品3几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品3几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 2 ] = iValue;
		iCol ++;

		//可能掉落的物品4
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品4出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品4出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 3 ] = iValue;
		else
			monster.stGoodDropID[ 3 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能掉落的物品4几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品4几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品4几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 3 ] = iValue;
		iCol++;

		//可能掉落的物品5
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品5出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品5出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 4 ] = iValue;
		else
			monster.stGoodDropID[ 4 ] = ArabicNights::ErrorUnsignedShortID;

		iCol ++;

		//可能掉落的物品5几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品5几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品5几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 4 ] = iValue;
		iCol ++;

		//可能掉落的物品6
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品6出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品6出错!");
			goto load_error;
		}
		if (iValue > 0)
			monster.stGoodDropID[ 5 ] = iValue;
		else
			monster.stGoodDropID[ 5 ] = ArabicNights::ErrorUnsignedShortID;
		iCol ++;

		//可能掉落的物品6几率
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入怪物可能掉落的物品6几率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入怪物可能掉落的物品6几率出错!");
			goto load_error;
		}
		monster.stGoodDropRate[ 5 ] = iValue;
		iCol ++;

		//掉落金钱最小
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入掉落金钱最小出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入掉落金钱最小出错!");
			goto load_error;
		}
		monster.stDropMinMoney = iValue;
		iCol ++;

		//掉落金钱最大
		if( !reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t  载入掉落金钱最大出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入掉落金钱最大出错!");
			goto load_error;
		}
		monster.stDropMaxMoney = iValue;
		iCol ++;

		//物品掉落倍率
		if( !reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t  载入物品掉落倍率出错!\r\n" );
			GetErrorLog()->logString( "monster.slk  载入物品掉落倍率出错!");
			goto load_error;
		}
		monster.fItemDropMultipleRate = fValue;
		iCol ++;

		//怪物皮肤
		if( !reader.GetStringField( iCol,strMonsterSkin ) )
		{
			OutputSlkLoadingMessage( "\t  载入怪物皮肤出错!\r\n" );
			GetErrorLog()->logString( " monster.slk 载入怪物皮肤出错");
			goto load_error;
		}
		monster.dwSkinAddr = AllocStringCopy( strMonsterSkin.c_str() );
		iCol ++;




		////Reset 
		//monster.stGoodDropID[ 6 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 7 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 8 ] = ArabicNights::ErrorUnsignedShortID;
		//monster.stGoodDropID[ 9 ] = ArabicNights::ErrorUnsignedShortID;

		////追击范围	
		//if( !reader.GetIntField( iCol, iValue ))
		//{
		//	OutputSlkLoadingMessage( "\t  载入怪物追击范围出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物追击范围出错!");
		//	goto load_error;
		//}
		//monster.stCatchArea = iValue;
		//iCol ++;

		//AI类型
		//if( !GetStringField( &reader, iCol, strTemp) )
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物AI类型出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物AI类型出错!");
		//	continue;
		//}
		//monster.stAI = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szAiType, sizeof(g_szAiType)/sizeof( char* ) );

		//if( monster.stAI == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物AI类型出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物AI类型出错!");
		//	continue;
		//}
		//iCol ++;

		//////怪物类型
		////if( !GetStringField( &reader, iCol, strTemp ))
		////{
		////	OutputSlkLoadingMessage( "Error:载入怪物类型出错!\r\n" );
		////	assert(false && "monster.slk  载入怪物类型出错!");
		////	continue;
		////}
		////monster.stMonsterType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		////	g_szMonsterType, sizeof(g_szMonsterType)/sizeof( char* ) );

		//if( monster.stMonsterType == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物类型出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物类型出错!");
		//	continue;
		//}
		//iCol++;

		////怪物世仇的职业
		//if( !GetStringField( &reader, iCol, strTemp ))
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物世仇的职业出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物世仇的职业出错!");
		//	continue;
		//}
		//monster.stHateProfession = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szMonsterHateEnemy, sizeof(g_szMonsterHateEnemy)/sizeof( char* ) );

		//if( monster.stHateProfession == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物世仇的职业出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物世仇的职业出错!");
		//	continue;
		//}
		//iCol ++;

		////怪物反攻的优先级别
		//if( !GetStringField( &reader, iCol, strTemp ))
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物反攻的优先级别出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物反攻的优先级别出错!");
		//	continue;
		//}
		//monster.stFightBackType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
		//	g_szMonsterFightBackEnemy, sizeof(g_szMonsterFightBackEnemy)/sizeof( char* ) );

		//if( monster.stFightBackType == -1 )
		//{
		//	OutputSlkLoadingMessage( "Error:载入怪物反攻的优先级别出错!\r\n" );
		//	assert(false && "monster.slk  载入怪物反攻的优先级别出错!");
		//	continue;
		//}
		//iCol ++;

		////TC级别
		//iCol ++;

		//if( !reader.GetIntFieldByName( "掉落金钱最小", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk 掉落金钱最小\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stDropMinMoney = iValue;

		//if( !reader.GetIntFieldByName( "掉落金钱最大", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk 掉落金钱最大\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stDropMaxMoney = iValue;

		//if( !reader.GetIntFieldByName( "会心几率", iValue ) )
		//{
		//	monster.stDropMinMoney = 0;
		//	assert( false && "monster.slk 会心几率\r\n" );
		//	continue;
		//}
		//iCol ++;
		//monster.stCriticalRate = iValue;

		//if( !reader.GetIntFieldByName( "BOSS与否", iValue ) )
		//{
		//	OutputSlkLoadingMessage( "Error:载入BOSS与否出错!\r\n" );
		//	assert(false && "monster.slk  载入BOSS与否出错!");
		//	continue;
		//}
		//iCol ++;
		//monster.bBoss = iValue == 1 ? true : false;

		//if( !reader.GetIntFieldByName( "显示名称类型", iValue ) )
		//{
		//	OutputSlkLoadingMessage( "Error:载入显示名称类型出错!\r\n" );
		//	assert(false && "monster.slk  载入显示名称类型出错!");
		//	continue;
		//}
		//iCol ++;
		//monster.stDisplayNameType = iValue;

		//if( !reader.GetStringFieldByName( "物品掉落模板", strTemp ) )
		//{
		//	monster.strItemDropTemplate = "<void>";
		//}
		//else
		//{
		//	monster.strItemDropTemplate = strTemp;
		//}
		//iCol ++;

		//if( !reader.GetFloatFieldByName( "物品掉落倍率", fValue) )
		//{
		//	monster.fItemDropMultipleRate = 0.0f;
		//}
		//else
		//{
		//	monster.fItemDropMultipleRate = fValue;
		//}
		//iCol ++;

		//if ( !reader.GetIntFieldByName( "最小物理攻击" ,iValue) )	
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicAttMin = iValue;
		//iCol++;

		//if(!reader.GetIntFieldByName( "最大物理攻击" , iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicAttMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最小物理防御",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicDefMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最大物理防御",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stPhysicDefMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最小魔法攻击",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicAttMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最大魔法攻击",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicAttMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最小魔法防御",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicDefMin = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("最大魔法防御",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stMagicDefMax = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("精准",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stExact = iValue;
		//iCol++;

		//if (!reader.GetIntFieldByName("闪避",iValue))
		//{
		//	assert(false);
		//	continue;
		//}
		//monster.stDodge = iValue;
		//iCol++;

		monster.iMonsterID = m_vecMonster.size();

		//加入查找
		//m_mapMonster.insert( mapMonster::value_type( monster.strName.c_str(),(short)m_vecMonster.size() ) );
		m_mapMonster.insert( mapMonster::value_type( monster.GetName(),(short)m_vecMonster.size() ) );
		//加入vector
		m_vecMonster.push_back( monster );
		continue;
load_error:
		OutputSlkLoadingMessage( "\tmonster.slk 第 %d 行载入失败!\r\n",iRow-1 );
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
	// 是否独占
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
		//取新的slk资源
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
			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk内存分配出错" );
			return false;
		}

		iCol = 1;
		std::string strProfessionName;
		//if(!reader.GetStringField( iCol, pCharModulus->szProfessionName))
		if(!reader.GetStringField( iCol, strProfessionName))
		{
			OutputSlkLoadingMessage( "\t  载入职业名字出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入职业名字出错" );
			goto load_error;
		}
		pCharModulus->dwProfessionNameAddr = AllocStringCopy( strProfessionName.c_str() );
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入职业命中初始值出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入职业命中初始值出错" );
			goto load_error;
		}
		pCharModulus->fHit = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入职业回避初始值出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入职业命中初始值出错" );
			goto load_error;
		}
		pCharModulus->fDodge = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入职业HP初始值出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入职业命中初始值出错" );
			goto load_error;
		}
		pCharModulus->fHp = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入职业MP初始值出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入职业命中初始值出错" );
			goto load_error;
		}
		pCharModulus->fMp = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理攻击系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理攻击系数1出错" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理攻击系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理攻击系数2出错" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理攻击系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理攻击系数3出错" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理攻击系数4出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理攻击系数4出错" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理攻击系数5出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理攻击系数5出错" );
			goto load_error;
		}
		pCharModulus->fPhyAttMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔法攻击系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔法攻击系数1出错" );
			goto load_error;
		}
		pCharModulus->fMagAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔法攻击系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔法攻击系数2出错" );
			goto load_error;
		}
		pCharModulus->fMagAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔法攻击系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔法攻击系数3出错" );
			goto load_error;
		}
		pCharModulus->fMagAttMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔法攻击系数4出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔法攻击系数4出错" );
			goto load_error;
		}
		pCharModulus->fMagAttMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔法攻击系数5出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔法攻击系数5出错" );
			goto load_error;
		}
		pCharModulus->fMagAttMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入元素攻击系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入元素攻击系数1出错" );
			goto load_error;
		}
		pCharModulus->fElementMod1 = fValue;
		iCol++;		

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理防御系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理防御系数1出错" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理防御系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理防御系数2出错" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理防御系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理防御系数3出错" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入物理防御系数4出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入物理防御系数4出错" );
			goto load_error;
		}
		pCharModulus->fPhyDefMod4 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中力系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中力系数1出错" );
			goto load_error;
		}
		pCharModulus->fExactMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中力系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中力系数2出错" );
			goto load_error;
		}
		pCharModulus->fExactMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中力系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中力系数3出错" );
			goto load_error;
		}
		pCharModulus->fExactMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中力系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中力系数3出错" );
			goto load_error;
		}
		pCharModulus->fExactMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入回避力系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入回避力系数1出错" );
			goto load_error;
		}
		pCharModulus->fDodgeMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入回避力系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入回避力系数2出错" );
			goto load_error;
		}
		pCharModulus->fDodgeMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入回避力系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入回避力系数3出错" );
			goto load_error;
		}
		pCharModulus->fDodgeMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入回避力系数4出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入回避力系数4出错" );
			goto load_error;
		}
		pCharModulus->fDodgeMod4 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入回避力系数5出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入回避力系数5出错" );
			goto load_error;
		}
		pCharModulus->fDodgeMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入等级抗性系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入系数1出错" );
			goto load_error;
		}
		pCharModulus->fLvDefMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP系数1出错" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP系数2出错" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP系数3出错" );
			goto load_error;
		}
		pCharModulus->fHpMaxMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入MP系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入MP系数1出错" );
			goto load_error;
		}
		pCharModulus->fMpMaxMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入MP系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入MP系数1出错" );
			goto load_error;
		}
		pCharModulus->fMpMaxMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP恢复系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP恢复系数1出错" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP恢复系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP恢复系数2出错" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod2 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入HP恢复系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入HP恢复系数2出错" );
			goto load_error;
		}
		pCharModulus->fHpRestoreMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入MP恢复系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入MP恢复系数1出错" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入MP恢复系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入MP恢复系数2出错" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod2 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入MP恢复系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入MP恢复系数2出错" );
			goto load_error;
		}
		pCharModulus->fMpRestoreMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数1出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数2出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数3出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数3出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数4出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数4出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod4 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数5出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数5出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod5 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数6出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数6出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod6 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击几率系数7出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击几率系数7出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttRateMod7 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入伤害系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入伤害系数1出错" );
			goto load_error;
		}
		pCharModulus->fDamMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入伤害系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入伤害系数2出错" );
			goto load_error;
		}
		pCharModulus->fDamMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中率系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中率系数1出错" );
			goto load_error;
		}
		pCharModulus->fHitRateMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入命中率系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入命中率系数2出错" );
			goto load_error;
		}
		pCharModulus->fHitRateMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击系数1出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入会心一击系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入会心一击系数2出错" );
			goto load_error;
		}
		pCharModulus->fCriticalAttMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入等级差系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入等级差系数1出错" );
			goto load_error;
		}
		pCharModulus->fLevelDisMod1 = fValue;
		iCol++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入经验系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入经验系数1出错" );
			goto load_error;
		}
		pCharModulus->fExpMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击速度系数1出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击速度系数1出错" );
			goto load_error;
		}
		pCharModulus->fAttSpeedMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击速度系数2出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击速度系数2出错" );
			goto load_error;
		}
		pCharModulus->fAttSpeedMod2 = fValue;
		iCol++;


		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t 载入力量出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入力量出错" );
			goto load_error;
		}
		pCharModulus->sStrength = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t 载入敏捷出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入敏捷出错" );
			goto load_error;
		}
		pCharModulus->sAgility = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t 载入体质出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入体质出错" );
			goto load_error;
		}
		pCharModulus->sConstitution = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t 载入感知出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入感知出错" );
			goto load_error;
		}
		pCharModulus->sIntelligence = iValue;
		iCol++;

		if(!reader.GetIntField( iCol, iValue ))
		{
			OutputSlkLoadingMessage( "\t 载入魔力出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入魔力出错" );
			goto load_error;
		}
		pCharModulus->sMagic = iValue;
		iCol++;


		if( !reader.GetIntFieldByName( "运气", iValue ) )
		{
			assert( false );
			continue;
		}
		pCharModulus->sCharm  = iValue;
		iCol ++;


		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入武器精确值（初始）出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入武器精确值（初始）出错" );
			goto load_error;
		}
		pCharModulus->fWeaponExact = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入右手攻击系数出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入右手攻击系数出错" );
			goto load_error;
		}
		pCharModulus->fRAttMod = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入左手攻击系数出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入左手攻击系数出错" );
			goto load_error;
		}
		pCharModulus->fLAttMod = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击时间系数4(d2)!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击时间系数4(d2)出错" );
			goto load_error;
		}
		pCharModulus->fTimeMod1 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击时间系数4(d2)出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击时间系数4(d2)出错" );
			goto load_error;
		}
		pCharModulus->fTimeMod2 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击时间系数4(d2)出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击时间系数4(d2)出错" );
			goto load_error;
		}
		pCharModulus->fTimeMod3 = fValue;
		iCol++;

		if(!reader.GetFloatField( iCol, fValue ))
		{
			OutputSlkLoadingMessage( "\t 载入攻击时间系数4(d2)出错!\r\n" );
			GetErrorLog()->logString( "charmodulus.slk 载入攻击时间系数4(d2)出错" );
			goto load_error;
		}
		pCharModulus->fTimeMod4 = fValue;
		iCol++;

		//加入查找
		//m_mapCharModulus.insert( mapCharModulus::value_type( pCharModulus->szProfessionName.c_str(), pCharModulus ) );
		m_mapCharModulus.insert( mapCharModulus::value_type( pCharModulus->GetProfessionName(), pCharModulus ) );
		//加入vector
		m_vecCharModulus.push_back( pCharModulus );
		continue;

load_error:
		OutputSlkLoadingMessage( "\tcharmodulus.slk 第 %d 行载入失败!\r\n",iRow-1 );
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
//		//缺新的slk资源
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
//			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//			assert( false && "stoneskill.slk内存分配出错" );
//			return false;
//		}
//
//		iCol = 1;
//
//		//技能ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID出错!\r\n" );
//			assert( false && "stoneskill.slk载入技能ID出错" );
//			goto load_error;
//		}
//		pStoneSkill->ustSkillID = iValue;
//		iCol++;		
//
//		//符石ID1
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入符石ID1出错!\r\n" );
//			assert( false && "stoneskill.slk载入符石ID1出错" );
//			goto load_error;
//		}
//		pStoneSkill->ustStoneID[ 0 ] = iValue;
//		iCol++;
//
//		//符石ID2
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入符石ID2出错!\r\n" );
//			assert( false && "stoneskill.slk载入符石ID2出错" );
//			goto load_error;
//		}
//		pStoneSkill->ustStoneID[ 1 ] = iValue;
//		iCol++;
//
//		//符石ID3
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 符石ID3默认0xffff!\r\n" );
//			pStoneSkill->ustStoneID[ 2 ] = 0xffff;
//		}
//		else
//		{
//			pStoneSkill->ustStoneID[ 2 ] = iValue;
//		}
//		//
//		{
//			//加入map
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
//		OutputSlkLoadingMessage( "\tstoneskill.slk 第 %d 行载入失败!\r\n",iRow-1 );
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
////存放基本技能片段到法术的对应关系
//bool CItemDetail::LoadSkillToSkill( char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//缺新的slk资源
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
//			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//			assert( false && "skilltoskill.slk 内存分配出错" );
//			return false;
//		}
//		iCol = 1;
//
//		//必杀技ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID出错!\r\n" );
//			assert( false && "skilltoskill.slk 载入技能ID出错" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSkillID = iValue;
//		iCol++;		
//
//		//技能ID1
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID1出错!\r\n" );
//			assert( false && "skilltoskill.slk 载入技能ID1出错" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSubSkillID[ 0 ] = iValue;
//		iCol++;
//
//		//技能ID2
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID2出错!\r\n" );
//			assert( false && "skilltoskill.slk 载入技能ID2出错" );
//			goto load_error;
//		}
//		pSkillToSkill->ustSubSkillID[ 1 ] = iValue;
//		iCol++;
//
//		//技能ID3
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID3默认0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 2 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//技能ID4
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID4默认0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 3 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 3 ] = iValue;
//		}
//		iCol++;
//
//		//技能ID5
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入技能ID5默认0xffff!\r\n" );
//			pSkillToSkill->ustSubSkillID[ 4 ] = 0xffff;
//		}
//		else
//		{
//			pSkillToSkill->ustSubSkillID[ 4 ] = iValue;
//		}
//
//		//加入map
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
//		OutputSlkLoadingMessage( "\tskilltoskill.slk 第 %d 行载入失败!\r\n",iRow-1 );
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
////装载制造物品,原料与产品的对应关系
//bool CItemDetail::LoadProduceItem( char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//缺新的slk资源
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
//			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//			assert( false && "produceitem.slk 内存分配出错" );
//			return false;
//		}
//		iCol = 1;
//
//		//最终产品ID（数量是1）
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 最终产品ID默认0xffff!\r\n" );
//			pProduceItem->ustResultGoodID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustResultGoodID = iValue;
//		}
//		iCol += 2;	//跳过名称
//
//		//原料1的ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料1的ID默认0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 0 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 0 ] = iValue;
//		}
//		iCol++;
//
//		//原料1的数目
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料1的数目默认0!\r\n" );
//			pProduceItem->ustMaterialNum[ 0 ] = 1;
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 0 ] = iValue;
//		}
//		iCol++;
//
//		//原料2的ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料2的ID默认0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 1 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 1 ] = iValue;
//		}
//		iCol++;
//
//		//原料2的数目
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料2的数目默认0!\r\n" );
//			pProduceItem->ustMaterialNum[ 1 ] = 1;
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 1 ] = iValue;
//		}
//		iCol++;
//
//		//原料3的ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料3的ID默认0xffff!\r\n" );
//			pProduceItem->ustMaterialID[ 2 ] = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustMaterialID[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//原料3的数目
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入原料3的数目默认0!\r\n" );
//			pProduceItem->ustMaterialNum[ 2 ] = 1;			
//		}
//		else
//		{
//			pProduceItem->ustMaterialNum[ 2 ] = iValue;
//		}
//		iCol++;
//
//		//使用的工具ID
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入工具的ID默认0xffff!\r\n" );
//			pProduceItem->ustToolID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustToolID = iValue;
//		}
//		iCol++;
//
//		//对小精灵技能的要求
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入小精灵技能的ID默认0xffff!\r\n" );
//			pProduceItem->ustSpriteSkillID = ArabicNights::ErrorUnsignedShortID;
//		}
//		else
//		{
//			pProduceItem->ustSpriteSkillID = iValue;
//		}
//		iCol++;
//
//		//对小精灵技能等级的要求
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入小精灵技能等级要求默认1!\r\n" );
//			pProduceItem->ustSpriteSkillLevel = 1;
//		}
//		else
//		{
//			pProduceItem->ustSpriteSkillLevel = iValue;
//		}
//		iCol++;
//
//		//制造的成功率
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入制造的成功率默认100!\r\n" );
//			pProduceItem->ustSuccessRate = 100;		
//		}
//		else
//		{
//			pProduceItem->ustSuccessRate = iValue;
//		}
//
//		//加入vector
//		m_vecProduceItem.push_back( pProduceItem );
//		continue;
//		//
//		OutputSlkLoadingMessage( "\tproduceitem.slk 第 %d 行载入失败!\r\n",iRow-1 );
//		continue;
//	}
//
//	return true;
//}
//
////获取物品制造,原料与产品的对应关系
//CItemDetail::SProduceItem* CItemDetail::GetProduceItem( int iIndex )
//{
//	return m_vecProduceItem[iIndex];
//}
//
////获取对应关系的数目
//int	CItemDetail::GetProduceItemSize( )
//{
//	return (int)m_vecProduceItem.size( );
//}

//获取技能的描述信息
int CItemDetail::CreateSkillDesc( unsigned short ustSkillID, unsigned short ustSkillLevel, 
								 char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
{
	//获取技能的信息
	CItemDetail::SItemSkill *pSkill;
	pSkill = theItemDetail.GetSkillByID( ustSkillID, ustSkillLevel );
	if(!pSkill)
		return 0;

	//记录行数
	int iLineCount = 0;

	//暂时的颜色
	for( int i=0;i<iDescLength;i++ )
	{
		pDescColor[ i ] = 0xff000000;
	}

	//技能名称
	sprintf( pDesc[iLineCount++], 
		g_CfgItemDesc.m_strSkillName, 
		//pSkill->szItemName.c_str() );
		GetString( pSkill->dwItemNameAddr ) );
	if( iLineCount == iDescLength )
		return iLineCount;

	return iLineCount;	
}

//获取状态的描述信息
int CItemDetail::CreateStatusDesc( unsigned short ustStatusID, unsigned short ustStatusLevel,
								  char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
{
	//获取状态的信息
	CItemDetail::SItemStatus *pStatus;
	pStatus = theItemDetail.GetStatusByID( ustStatusID, ustStatusLevel );
	if(!pStatus)
		return 0;

	//记录行数
	int iLineCount = 0;

	//暂时的颜色
	for( int i=0;i<iDescLength;i++ )
	{
		pDescColor[ i ] = 0xff000000;
	}

	//状态的描述
	sprintf( pDesc[iLineCount++], 
		g_CfgItemDesc.m_strStatusDesc, 
		//pStatus->szItemDesc.c_str() );
		GetString( pStatus->dwItemDescAddr ) );
	if( iLineCount == iDescLength )
		return iLineCount;

	return iLineCount;	
}
//随机取得一个等级范围的道具
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
		sprintf( szTemp, "需要等级:%ld\n", pSkill->stLearnLevelReq );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stMoneyNeed != 0 )
	{
		if ( pCharBaseInfo->dwMoney < pSkill->stMoneyNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "需要金钱:%ld\n", pSkill->stMoneyNeed );
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
		sprintf( szTemp, "需要官衔:%s\n",r->szOfficialTitle[nCountry] );
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
			sprintf( szTemp, "需要技能:%ld级%s\n",
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
		sprintf( szTemp, "需要体力:%d\n", pSkill->stVITNeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stSTRNeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_STRENGTH].ustValue < pSkill->stSTRNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "需要力量:%d\n", pSkill->stSTRNeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stAGINeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_AGILITY].ustValue < pSkill->stAGINeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "需要敏捷:%d\n", pSkill->stAGINeed );
		strcat( szInfo, szTemp );
	}
	if ( pSkill->stINTNeed != 0 )
	{
		if ( pCharBaseInfo->attrs[ArabicNights::BATTR_INTELLIGENCE].ustValue < pSkill->stINTNeed )
		{
			strcat( szInfo, "<#ffff0000=" );
			bResutl = false;
		}
		sprintf( szTemp, "需要智力:%d\n", pSkill->stINTNeed );
		strcat( szInfo, szTemp );
	}
	if( pCharBaseInfo->stSkillPoint <= 0 )
	{
		strcat( szInfo, "<#ffff0000=" );
		bResutl = false;
	}
	strcat( szInfo, "需要1点技能点" );
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
		//取新的slk资源
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
			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
			GetErrorLog()->logString( "WeaponRand.slk内存分配出错" );
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

		if (!pReader.GetIntFieldByName("级别",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->WeaponRandLevel = iValue;
		iCol++;

		if (!pReader.GetStringFieldByName("前缀",strTemp))
		{
			assert(false);
			continue;
		}
		//pWeaponRand->WeaponPrefix = strTemp;
		pWeaponRand->dwWeaponPrefixAddr = AllocStringCopy( strTemp.c_str() );
		iCol++;

		iCol++;

		iCol++;

		if (!pReader.GetIntFieldByName("物理攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("魔法攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Magic] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("火攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("冰攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("电攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("毒攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAtt[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("物理攻击增加％",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Physics] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("火攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Blaze] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("冰攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Frost] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("电攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("毒攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttPer[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("冰冻伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Frost] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("火焰伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Blaze] = iValue;
		iCol++;


		if (!pReader.GetIntFieldByName("雷电伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Thunder] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("巫毒伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sDam[ePlayAtt_Poison] = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("命中增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sExact = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("暴击几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sCritical = iValue;
		iCol++;

		if (!pReader.GetFloatFieldByName("暴击倍数增加",fValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->fCriticalmultiple = fValue;
		iCol++;

		if (!pReader.GetIntFieldByName("攻击速度",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sAttSpeed = iValue;
		iCol++;

		if (!pReader.GetIntFieldByName("吟唱速度",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sIntonateSpeed = iValue;	
		iCol++;

		if (!pReader.GetIntFieldByName("材料等级",iValue))
		{
			assert(false);
			continue;
		}
		pWeaponRand->sMaterialLevel = iValue;	

		//m_mapCharModulus.insert( mapCharModulus::value_type( pWeaponRand->WeaponRandID, pWeaponRand ) );
		//加入vector
		//m_vecCharModulus.push_back( pWeaponRand );
		//加入查找
		m_mapWeaponRand.insert( mapWeaponRand::value_type( pWeaponRand->WeaponRandID, pWeaponRand ) );
		//加入vector
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
		//取新的slk资源
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
			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
			GetErrorLog()->logString( "ArmourRand.slk内存分配出错" );
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

		if (!reader.GetIntFieldByName("级别",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->ArmourRandLevel = iValue;
		iCol++;

		if (!reader.GetStringFieldByName("前缀",strTemp))
		{
			assert(false);
			continue;
		}
		//pArmourRand->ArmourPrefix = strTemp;
		pArmourRand->dwArmourPrefixAddr = AllocStringCopy( strTemp.c_str() );
		iCol++;

		iCol++;

		iCol++;

		if (!reader.GetIntFieldByName("物理攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Physics] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("魔法攻击增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Magic] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("火攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("冰攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("电攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("毒攻增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAtt[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("物理攻击增加％",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Physics] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("火攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Blaze] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("冰攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("电攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("毒攻增加％",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttPer[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("冰冻伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Frost] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("火焰伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("雷电伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Thunder] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("巫毒伤害增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDam[ePlayDef_Poison] = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("命中增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sExact = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("闪避增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDodge = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("暴击增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sCritical = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("暴击倍数增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sCriticalmultiple = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("攻击速度",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sAttSpeed = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("吟唱速度",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sIntonateSpeed = iValue;
		iCol++;

		if (!reader.GetFloatFieldByName("移动速度",fValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->fMoveSpeed = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("物理防御增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Max] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("冰冻抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Frost] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("火焰抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Blaze] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("雷电抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Thunder] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("巫毒抗性增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDef[ePlayDef_Poison] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("物理防御改变增加%",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sDefPer[ePlayDef_Physics] = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("生命最大值增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpMax = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("魔法最大值增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpMax = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("生命最大值增加(%)",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpMaxPer = iValue;
		iCol++;

		if (!reader.GetIntFieldByName("魔法最大值增加%",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpMaxPer = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("生命恢复增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sHpRestore = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("魔法恢复增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMpRestore = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("物理反弹增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sReboundRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("合成几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sComposeRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("精炼几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sProficiencyRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("强化几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sStrengthenRate = iValue;
		iCol++;


		if (!reader.GetIntFieldByName("镶嵌几率增加",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sEnchaseRate = iValue;

		if (!reader.GetIntFieldByName("材料等级",iValue))
		{
			assert(false);
			continue;
		}
		pArmourRand->sMaterialLevel = iValue;


		//加入查找
		m_mapArmourRand.insert( mapArmourRand::value_type( pArmourRand->ArmourRandID, pArmourRand ) );
		//加入vector
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
		//取新的slk资源
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
			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
			GetErrorLog()->logString( "UpBaseAttr.slk内存分配出错" );
			return false;
		}

		iCol = 1;
		////////////////////////////////////////////////////////////
#define UpBaseAttrGetFieldInt( t, str ) \
	if( !reader.GetIntFieldByName( str.c_str(), iValue ) ) \
		{ \
		char szMem[256] = {0};	\
		strcpy( szMem, ("Error:读取UpBaseAttr.slk字段"+str+"出错\r\n").c_str() );	\
		OutputSlkLoadingMessage( szMem ); \
		GetErrorLog()->logString( ("Error:读取UpBaseAttr.slk字段"+str+"出错").c_str() ); \
		continue; \
		} \
		t = iValue; \
		iCol++;
		/////////////////////////////////////////////////////////////
		std::string szProInfo;
		szProInfo = "等级";
		UpBaseAttrGetFieldInt( pUpBaseAttr->sLevel, szProInfo );

		for( int i=0; i<=Profession_Wizard; i++)
		{
			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( i );
			if( !pProInfo )
				continue;
			szProInfo = pProInfo->m_strProShow;
			string szTemp = szProInfo+"力量";
			UpBaseAttrGetFieldInt( pUpBaseAttr->Str[i], szTemp);// szTemp.c_str() );
			szTemp = (szProInfo+"敏捷");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Agi[i], szTemp );
			szTemp = (szProInfo+"体质");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Con[i], szTemp );
			szTemp = (szProInfo+"感知");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Int[i], szTemp );
			szTemp = (szProInfo+"魔力");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Mag[i], szTemp );
			szTemp = (szProInfo+"运气");
			UpBaseAttrGetFieldInt( pUpBaseAttr->Charm[i], szTemp );
		}
		//加入查找
		m_mapUpBaseAttr.insert( mapUpBaseAttr::value_type( pUpBaseAttr->sLevel, pUpBaseAttr ) );
		//加入vector
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
		OutputSlkLoadingMessage( "\tError:Crystal.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "Crystal.slk中找不到物品ID" );
		return;
	}
	if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
	{
		OutputSlkLoadingMessage( "\tError:Crystal.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
		GetErrorLog()->logString( "Crystal.slk中找不到物品ID" );
		return;
	}

	pCrystal = (SItemCrystal*)AllocItem( 0, sizeof( SItemCrystal ) );

	if( !pCrystal )
	{
		OutputSlkLoadingMessage( "\tError:Crystal.slk中ID为:%d的物品,分配内存失败!\r\n",common.ustItemID );
		assert(false);
		return;
	}

	CopyCommon( pCrystal,common );


	bool bReadSucc = true;

	while( bReadSucc )
	{
		bReadSucc = false;
		iCon = 3;
		if (!pReader->GetIntFieldByName("等级",iValue))
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
		//添加到物品队列中
		AddToMap( pCrystal );

		m_vectorCrystalItem.push_back( pCrystal );
	}

}


//bool CItemDetail::LoadFormulamodulus(char *szFile )
//{
//	CSlkReader reader;
//	if(!reader.ReadFromFile( szFile ))
//	{
//		//缺新的slk资源
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
//			OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
//			assert( false && " Formulamodulus.slk 内存分配出错" );
//			return false;
//		}
//		iCol = 1;
//
//		if(!reader.GetStringField( iCol, pFormulaMod->szFormulaName))
//		{
//			OutputSlkLoadingMessage( "\t  载入公式名字出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入公式名字出错" );
//			goto load_error;
//		}
//		iCol++;
//       
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入系数1出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入系数1出错" );
//			goto load_error;
//		}
//		pFormulaMod->stMod1 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入系数2出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入系数2出错" );
//			goto load_error;
//		}
//		pFormulaMod->stMod2 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入系数3出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入系数3出错" );
//			goto load_error;
//		}
//		pFormulaMod->stMod3 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入系数4出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入系数4出错" );
//			goto load_error;
//		}
//		pFormulaMod->stMod4 = iValue;
//		iCol++;
//
//		if(!reader.GetIntField( iCol, iValue ))
//		{
//			OutputSlkLoadingMessage( "\t 载入系数5出错!\r\n" );
//			assert( false && "Formulamodulus.slk 载入系数5出错" );
//			goto load_error;
//		}
//		pFormulaMod->stMod5 = iValue;
//
//		//加入查找
//		m_mapFormulaModulus.insert( mapFormulaModulus::value_type( pFormulaMod->szFormulaName.c_str(), pFormulaMod ) );
//		//加入vector
//		m_vecFormulaModulus.push_back( pFormulaMod );
//		continue;
//
//load_error:
//		OutputSlkLoadingMessage( "\tFormulamodulus.slk 第 %d 行载入失败!\r\n",iRow-1 );
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
