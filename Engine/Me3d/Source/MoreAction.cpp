#include "Me3d/MoreAction.h"
#include "MapStrToId.h"
#include "FuncPerformanceLog.h"

#define CASE_RETURN_STR(a)	case(a):			\
							return #a;			\
							break;

// #define ADD_ACTION_RECORD(a) {	g_mapActionName[a] = #a;			\
// 								static DWORD AA##a = a;				\
// 								g_actionMapStrToIdMgr.Register( #a, &AA##a );	\
// 								}

std::map< DWORD, char* > MoreAction::g_mapActionName;
std::map< DWORD, MoreAction::SRecord > MoreAction::g_mapActionRecord;



//int		g_ArabicNightAction[2][2][2][More_Profession_Max][MoreAction_Action_Max]; // fight  sex weapon profession  action
// Luo_157 added 2004.05.17
CMapStrToIDMgr g_actionMapStrToIdMgr;

void (*MoreAction::g_pfnLoadingCallBack)( const char* pszName ) = NULL;
BOOL MoreAction::InitializeRecords()
{
	guardfunc;
	return TRUE;
	unguard;
}
// BOOL MoreAction::Initialize()
// {
// 	guardfunc;
// 
// 	ADD_ACTION_RECORD( Model );
// 	ADD_ACTION_RECORD( Idle1 );
// 	ADD_ACTION_RECORD( SpecialIdle );
// 	ADD_ACTION_RECORD( Walk1 );
// 	ADD_ACTION_RECORD( WalkBackWards );
// 	ADD_ACTION_RECORD( Swim );
// 	ADD_ACTION_RECORD( SwimIdle );
// 
// 	ADD_ACTION_RECORD( Sit						);
// 	ADD_ACTION_RECORD( SitLoop					);
// 	ADD_ACTION_RECORD( Run1                       );
// 	ADD_ACTION_RECORD( Rush                       );
// 	
// 	//ADD_ACTION_RECORD( Singlescabbard              );
// 	//ADD_ACTION_RECORD( Singledraw				  );
// 
// 	//ADD_ACTION_RECORD( Doubledraw				  );
// 	//ADD_ACTION_RECORD( Doublescabbard              );
// 
// 	ADD_ACTION_RECORD( Drunk                      );
// 	ADD_ACTION_RECORD( Decline                    );
// 	ADD_ACTION_RECORD( Combat                     );
// 
// 	ADD_ACTION_RECORD( Resist                     );
// 	ADD_ACTION_RECORD( Miss                       );
// 	ADD_ACTION_RECORD( Sway                       );
// 	ADD_ACTION_RECORD( BeatBack                   );
// 	ADD_ACTION_RECORD( Hold                       );
// 	ADD_ACTION_RECORD( Death                      );
// 
// 	ADD_ACTION_RECORD( Attack_idle                 );
// 	
// 	// old
// 	ADD_ACTION_RECORD( Attack1                    );
// 	ADD_ACTION_RECORD( Attack2                    );
// 
// 	//ADD_ACTION_RECORD( Attackl1                    );
// 	//ADD_ACTION_RECORD( Attackl2                    );
// 
// 	//ADD_ACTION_RECORD( Attackd1                    );
// 	//ADD_ACTION_RECORD( Attackd2                    );
// 
// 	ADD_ACTION_RECORD( Pick                        );
// 	ADD_ACTION_RECORD( Hack							);
// 	ADD_ACTION_RECORD( Dig                       );
// 	ADD_ACTION_RECORD( Recital                       );
// 	ADD_ACTION_RECORD( Fire                      );
// 	ADD_ACTION_RECORD( Defend                       );
// 
// 	ADD_ACTION_RECORD( Run );
// 	ADD_ACTION_RECORD( Walk );
// 	ADD_ACTION_RECORD( Idle );
// 	ADD_ACTION_RECORD( Dead );
// 	ADD_ACTION_RECORD( Tired );
// 	ADD_ACTION_RECORD( Hurt );
// 	ADD_ACTION_RECORD( Miss1 );
// 	ADD_ACTION_RECORD( Intonate );
// 	ADD_ACTION_RECORD( Stun );
// 
// 	// ħ������
// 	ADD_ACTION_RECORD( MagicBorn                  );
// 	ADD_ACTION_RECORD( MagicDead                  );
// 	ADD_ACTION_RECORD( MagicRun                   );
// 	ADD_ACTION_RECORD( MagicExplode               );
// 	ADD_ACTION_RECORD( MagicFire                  );
// 
// 	// Luo_157 added 2004.12.15
// 	ADD_ACTION_RECORD( Idle2                  );
// 
// 	//˫������		
// 	//Human
// 	ADD_ACTION_RECORD( walk_attack                  );
// 	ADD_ACTION_RECORD( run_attack                  );
// 
// 	ADD_ACTION_RECORD( Attack_idle                  );
// 	ADD_ACTION_RECORD( Attack1                  );
// 	ADD_ACTION_RECORD( Attack2                  );
// 	ADD_ACTION_RECORD( Attack3                  );
// 	ADD_ACTION_RECORD( double_attack_idle                  );
// 	ADD_ACTION_RECORD( double_attack2                  );
// 	ADD_ACTION_RECORD( double_defend                  );
// 	ADD_ACTION_RECORD( double_recital );
// 	ADD_ACTION_RECORD( double_recital1 );
// 	ADD_ACTION_RECORD( double_recital2 );
// 	ADD_ACTION_RECORD( double_recital3 );
// 	ADD_ACTION_RECORD( double_recital4 );
// 	ADD_ACTION_RECORD( double_recital5 );
// 	ADD_ACTION_RECORD( double_recital6 );
// 
// 	ADD_ACTION_RECORD( double_fire                  );
// 	ADD_ACTION_RECORD( double_hurt                  );
// 
// 	ADD_ACTION_RECORD( double_dead                  );
// 	ADD_ACTION_RECORD( double_attack1                  );
// 	ADD_ACTION_RECORD( double_scabbard                  );
// 	ADD_ACTION_RECORD( double_draw                  );
// 	ADD_ACTION_RECORD( double_run					);
// 	//��������
// 	ADD_ACTION_RECORD( single_attack_idle                  );
// 	ADD_ACTION_RECORD( single_idle                  );
// 	ADD_ACTION_RECORD( single_attackr1                  );
// 	ADD_ACTION_RECORD( single_attackl1                  );
// 	ADD_ACTION_RECORD( single_attackr2                  );
// 	ADD_ACTION_RECORD( single_attackl2                  );
// 	ADD_ACTION_RECORD( single_recital );
// 	ADD_ACTION_RECORD( single_recital1 );
// 	ADD_ACTION_RECORD( single_recital2 );
// 	ADD_ACTION_RECORD( single_recital3 );
// 	ADD_ACTION_RECORD( single_recital4 );
// 	ADD_ACTION_RECORD( single_recital5 );
// 	ADD_ACTION_RECORD( single_recital6 );
// 	ADD_ACTION_RECORD( single_fire                  );
// 	ADD_ACTION_RECORD( single_hurt                  );
// 	ADD_ACTION_RECORD( single_dead                  );
// 	ADD_ACTION_RECORD( single_run					);
// 	ADD_ACTION_RECORD( jump );
// 	ADD_ACTION_RECORD( drop );
// 	ADD_ACTION_RECORD( glide );
// 	ADD_ACTION_RECORD( falltothegroundrun );
// 	ADD_ACTION_RECORD( jump1 );
// 	ADD_ACTION_RECORD( drop1 );
// 	ADD_ACTION_RECORD( glide1 );
// 	ADD_ACTION_RECORD( falltothegroundrun1 );
// 	ADD_ACTION_RECORD( single_double_draw                  );
// 	ADD_ACTION_RECORD( single_double_scabbard                  );
// 
// 	ADD_ACTION_RECORD( single_draw                  );
// 	ADD_ACTION_RECORD( single_scabbard                  );
// 	//ADD_ACTION_RECORD( single_walk_attackr1                  );
// 	ADD_ACTION_RECORD( single_walk_attackr1                  );
// 	ADD_ACTION_RECORD( single_walk_attackl1                  );
// 	ADD_ACTION_RECORD( single_run_attackr1                  );
// 	ADD_ACTION_RECORD( single_run_attackl1                  );
// 	ADD_ACTION_RECORD( run_fire                  );
// 	ADD_ACTION_RECORD( walk_fire                  );
// 	ADD_ACTION_RECORD( strike                  );
// 	ADD_ACTION_RECORD( sting                  );
// 	ADD_ACTION_RECORD( brisance                  );
// 	ADD_ACTION_RECORD( frenzy                  );
// 	ADD_ACTION_RECORD( temp2006 );
// 	ADD_ACTION_RECORD( single_jump );
// 	ADD_ACTION_RECORD( single_glide );
// 	ADD_ACTION_RECORD( single_drop );
// 	ADD_ACTION_RECORD( single_falltothegroundrun );
// 	ADD_ACTION_RECORD( single_walkbackwards );
// 	ADD_ACTION_RECORD( single_walk );
// 	//ADD_ACTION_RECORD( single_stand );
// 	ADD_ACTION_RECORD( single_specialidle );
// 	ADD_ACTION_RECORD( single_attack_drop );
// 	ADD_ACTION_RECORD( single_attack_falltothegroundrun );
// 	ADD_ACTION_RECORD( single_attack_run );
// 	ADD_ACTION_RECORD( single_attack_walkbackwards );
// 	ADD_ACTION_RECORD( single_mountdrive );
// 	ADD_ACTION_RECORD( single_mountwalk );
// 	ADD_ACTION_RECORD( single_mountrun );
// 	ADD_ACTION_RECORD( single_mountjump );
// 	ADD_ACTION_RECORD( single_mountFalltothegroundrun );
// 	ADD_ACTION_RECORD( single_mountGlide );
// 	ADD_ACTION_RECORD( single_mountwalkbackwards );
// 	ADD_ACTION_RECORD( single_mountShuffleleft );
// 	ADD_ACTION_RECORD( single_mountShuffleright );
// 	ADD_ACTION_RECORD( single_mountneigh );
// 	ADD_ACTION_RECORD( single_mountbackattack );
// 	ADD_ACTION_RECORD( single_mountdrop );
// 	ADD_ACTION_RECORD( single_stun );
// 	ADD_ACTION_RECORD( single_run_scabbard );
// 	ADD_ACTION_RECORD( single_run_draw );
// 	ADD_ACTION_RECORD( stand );
// 	ADD_ACTION_RECORD( loot );
//     ADD_ACTION_RECORD( single_flag_run );
//     ADD_ACTION_RECORD( single_flag_idle );
//     ADD_ACTION_RECORD( neigh );
//     ADD_ACTION_RECORD( shuffleleft );
//     ADD_ACTION_RECORD( shuffleright );
//     ADD_ACTION_RECORD( backattack );
//     ADD_ACTION_RECORD( single_yanwu );
//     ADD_ACTION_RECORD(mountattackidle);
//     ADD_ACTION_RECORD(mountattack_run);
//     ADD_ACTION_RECORD(single_mountattackidle);
//     ADD_ACTION_RECORD(single_mountattack_run);
//     ADD_ACTION_RECORD(single_mountscabbard);
//     ADD_ACTION_RECORD(single_mountdraw);
//     ADD_ACTION_RECORD(single_walk);
//     ADD_ACTION_RECORD(single_walkbackwards);
//     ADD_ACTION_RECORD(yongbao);
//     ADD_ACTION_RECORD(mountdrive);
//     ADD_ACTION_RECORD(mountwalk);
//     ADD_ACTION_RECORD(mountrun);
//     ADD_ACTION_RECORD(mountjump);
//     ADD_ACTION_RECORD(mountfalltothegroundrun);
//     ADD_ACTION_RECORD(mountglide);
//     ADD_ACTION_RECORD(mountwalkbackwards);
//     ADD_ACTION_RECORD(mountshuffleleft);
//     ADD_ACTION_RECORD(mountshuffleright);
//     ADD_ACTION_RECORD(mountneigh);
//     ADD_ACTION_RECORD(mountdrop);
//     ADD_ACTION_RECORD(swimback);
//     ADD_ACTION_RECORD(single_fallow);
//     ADD_ACTION_RECORD(single_flag);
//     ADD_ACTION_RECORD(single_shuffle);
//     ADD_ACTION_RECORD(single_holding1);
// 	ADD_ACTION_RECORD( single_mountdrive2 );
// 	ADD_ACTION_RECORD( single_mountrun2 );
// 	ADD_ACTION_RECORD( single_mountjump2 );
// 	ADD_ACTION_RECORD( single_mountFalltothegroundrun2 );
// 	ADD_ACTION_RECORD( single_mountGlide2 );
// 	ADD_ACTION_RECORD( single_mountwalkbackwards2 );
// 	ADD_ACTION_RECORD( single_mountShuffleleft2 );
// 	ADD_ACTION_RECORD( single_mountShuffleright2 );
// 	ADD_ACTION_RECORD( single_mountneigh2 );
// 	ADD_ACTION_RECORD( single_mountbackattack2 );
// 	ADD_ACTION_RECORD( single_mountdrop2 );
// 	ADD_ACTION_RECORD( single_mountdrive3 );
// 	ADD_ACTION_RECORD( single_mountrun3 );
// 	ADD_ACTION_RECORD( single_mountjump3 );
// 	ADD_ACTION_RECORD( single_mountFalltothegroundrun3 );
// 	ADD_ACTION_RECORD( single_mountGlide3 );
// 	ADD_ACTION_RECORD( single_mountwalkbackwards3 );
// 	ADD_ACTION_RECORD( single_mountShuffleleft3 );
// 	ADD_ACTION_RECORD( single_mountShuffleright3 );
// 	ADD_ACTION_RECORD( single_mountneigh3 );
// 	ADD_ACTION_RECORD( single_mountbackattack3 );
// 	ADD_ACTION_RECORD( single_mountdrop3 );
// 	ADD_ACTION_RECORD( single_skill );
// 
// 	return TRUE;
// 	unguard;
// }
// int   MoreAction::FindActionIdByName( const char* pszName )
// {
// 	guardfunc;
// 	static char str_action[][32] = 
// 	{
// 		"idle",//(����)   
// 
// 		"idle1",//(����)   new
// 		"idle2",//(����)   new
// 		"specialidle",//(�������)
// 		"attack_idle", //(ս������)new
// 		"hurt",			//(����)	new
// 		"run",//(����)
// 		"walk",//(����)
// 		"stun",
// 
// 		"sit",//(����)    
// 		"stup",//(վ��)
// 		"dead",		//(ԭ�ص���)
// 		"dead1",	//(���w�˄�)  
// 		"pick",		//��ҩnew
// 		"hack",		//����new
// 		"dig",		//�ɿ�new
// 		"recital",	//����new
// 		"fire",		//ʦ�� new
// 		"defend",	//����new
// 		"sway",
// 
// 		"attack1",//��ͨ����
// 		"attack2",//��ͨ����
// 		"attack3",//��ͨ����
// 
// 		"walk_attack",
// 		"run_attack",
// 		
// 		//˫������		
// 		"double_attack_idle",// ս������
// 		"double_attack2",    //��ͨ����2   897    934  (912
// 		//��ͨ����3           941    988  (954
// 		//��ͨ����4           1003   1047 (1023
// 		"double_defend",	//����                1159   1174
// 		"double_recital",	//��������            1185   1215
// 		"double_recital1",	//��������            1185   1215
// 		"double_recital2",	//��������            1185   1215
// 		"double_recital3",	//��������            1185   1215
// 		"double_recital4",	//��������            1185   1215
// 		"double_recital5",	//��������            1185   1215
// 		"double_recital6",	//��������            1185   1215
// 		"double_fire",		//����ʦ��            1217   1256
// 		"double_hurt",		//����                1261   1275
// 		"double_dead",		//����                1282   1333
// 		"double_attack1",	//��ͨ����1    1337   1366  (1350
// 		"double_scabbard",	//������          1383   1426
// 		"double_draw",		//�γ�����         1433   1446
// 		"double_run",		//��˫�������ܲ�
// 
// 		//��������
// 		"single_attack_idle",		//ս������       35      67
// 		"single_idle"	,			//��ս������		75     132
// 		//		walk,				//��·              135     167
// 		//		run,				//�ܲ�              180     199
// 		"single_attackr1",		//������ͨ����1     208     229  (218  
// 		"single_attackl1",		//������ͨ����2       238     260  (249  
// 		"single_attackr2",		//������ͨ����3       273     295 ��283
// 		"single_attackl2",		//������ͨ����4       304     326 ��313
// 		//�����ػ�            334     360 ��344
// 		//����                366     382 ��371
// 		"single_recital",			//��������            386     415
// 		"single_recital1",			//��������            386     415
// 		"single_recital2",			//��������            386     415
// 		"single_recital3",			//��������            386     415
// 		"single_recital4",			//��������            386     415
// 		"single_recital5",			//��������            386     415
// 		"single_recital6",			//��������            386     415
// 		"single_fire",			//����ʦ��            417     454
// 		"single_hurt",			//����                456     470
// 		"single_dead",			//����                475     520       
// 		"jump",			//����                604     618
// 		"drop",			//���                619     635
// 		"glide",			//ͣ��                647     666
// 		"falltothegroundrun",//�����                674     703
// 		"single_double_draw",		//˫�ְγ�����             741     754
// 		"single_double_scabbard",	//˫����������             710     740
// 		"single_draw",				//������������             760     790 
// 		"single_scabbard",			//���ְγ�����             791     804
// 		"single_walk_attackr1",		//�������ֹ���            2141     2172  (2154
// 		"single_walk_attackl1",		//�������ֹ���            2176     2207 ��2185
// 		"single_run",				//�õ��������ܲ�
// 		"single_run_attackr1",		//�ܲ����ֹ���            2212     2231 ��2221
// 		"single_run_attackl1",		//�ܲ����ֹ���            2233     2252 ��2243 
// 		"run_fire",					//�ܲ�ʩ��                2275     2294 ��2263
// 		"walk_fire",				//����ʩ��                2298     2329
// 
// 		//���⶯��
// 		"strike",					//���              2341     2378 ��2359��2367
// 		"sting",					//�̼�               2401     2423 ��2409
// 		"brisance",					//����            2431     2455 ��2443
// 		"frenzy",					//��              2461     2485
// 
// 		"single_run_scabbard",		// �ܲ��аγ�����
// 		"single_run_draw",			// �ܲ�����������
//         "single_flag_run",          // ����run
//         "single_flag_idle",          // ����idle
//         "neigh",
//         "shuffleleft",
//         "shuffleright",
//         "backattack",
//         "single_yanwu",
//         "mountattackidle",
//         "mountattack_run",
//         "single_mountattackidle",
//         "single_mountattack_run",
//         "single_mountscabbard",
//         "single_mountdraw",
//         "single_walk",
//         "single_walkbackwards",
//         "yongbao"
// 	};	
// 
// 	for (int i=0; i<Action_Max; i++)
// 	{
// 		if (0 == strcmp(str_action[i], pszName))
// 			return i;
// 	}
// 	//
// 	return -1;
// 	unguard;
// }

int   MoreAction::FindIdByName( const char* pszName )
{
	guardfunc;
	/*std::map<DWORD, char*>::iterator it;
	for( it = g_mapActionName.begin(); it != g_mapActionName.end(); it++ )
	{
		char* name = it->second;
		if( 0 == stricmp( pszName, name ) )
			return it->first;
	}
	std::map<DWORD, SRecord>::iterator it2;
	for( it2 = g_mapActionRecord.begin(); it2 != g_mapActionRecord.end(); it2++ )
	{
		SRecord* r = &it2->second;
		if( 0 == stricmp( pszName, r->szName ) )
			return r->dwId;
	}*/
	// Luo_157 added 2004.05.17
	DWORD* pdwId = (DWORD*)g_actionMapStrToIdMgr[pszName];
	if( pdwId )
		return *pdwId;

	return -1;
	unguard;

}
const MoreAction::SRecord* MoreAction::GetRecordById( DWORD dwId )
{
	guardfunc;
	std::map<DWORD,SRecord>::const_iterator it2 = g_mapActionRecord.find( dwId );
	if( it2 != g_mapActionRecord.end() )
	{
		return &it2->second;
	}
	return NULL;
	unguard;
}
const char* MoreAction::FindNameById( DWORD dwId )
{
	guardfunc;
	std::map<DWORD,char*>::const_iterator it = g_mapActionName.find( dwId );
	// Luo_157 added //  [4/7/2004]
	/*if( it == g_mapActionName.end() )
		return NULL;
	return it->second;*/
	if( it != g_mapActionName.end() )
		return it->second;

	std::map<DWORD,SRecord>::const_iterator it2 = g_mapActionRecord.find( dwId );
	if( it2 != g_mapActionRecord.end() )
	{
		return it2->second.szName;
	}
	return NULL;
	unguard;
}

//void	MoreAction::CreateActionTable()
//{
//	static	char str_status[][16] = 
//	{
//		"peace",
//		"fight",
//	};
//	static	char str_sex[][16] =
//	{
//		"male",
//		"female",
//	};
//	static char str_profession[][16] = 
//	{
//		"nowe", //(����)
//		"swer", //(��ʿ)
//		"pala", //(��ʿ)
//		"hunt", //(����)
//		"fashi",//(��ʦ)
//		"mushi",//(��ʦ)
//		"wushi",//(��ʦ)
//	};
//	static char str_weapon[][16] = 
//	{
//		"nowe",
//		"swer",
//		"pala",
//		"hunt",
//		"fashi",
//		"mushi",
//		"wushi",
//	};
//	static char str_action[][16] = 
//	{
//		"idle",//(����)   
//		"run",//(����)     
//		"bawe",//(�յ�)   
//		"ouwe",//(�ε�)   
//		"sit",//(����)    
//		"stup",//(վ��)
//		"resist",//(��) 
//		"miss",//(����)    
//		"sway",//(�p��)   
//		"beatback",//(�ؓ�)     
//		"dead",//(ԭ�ص���)
//		"dead1",//(���w�˄�)  
//		"attack1_1",//(��������1��1)    
//		"attack1_2",//(��������1��2)
//		"attack2_1",//(��������2��1)    
//		"attack2_2",//(��������2��2)         
//		"attack3_1",//(��������3��1)
//		"attack3_2",//(��������3��2)    
//		"attack4_1",//(��������4��1)         
//		"attack4_2",//(��������4��2)
//		"attack5_1",//(��������5��1)    
//		"attack5_2",//(��������5��2)
//		"limit001",//(��ɱ001)  
//		"limit002",//(��ɱ002)  
//		"limit003",//(��ɱ003)
//		"limit004",//(��ɱ004)  
//		"limit005",//(��ɱ005)  
//		"limit006",//(��ɱ006)  
//		"limit007",//(��ɱ007)
//		"limit008",//(��ɱ008)  
//		"limit009",//(��ɱ009)  
//		"limit010",//(��ɱ010)  
//		"limit011",//(��ɱ011)
//		"limit012",//(��ɱ012)  
//		"limit013",//(��ɱ013)  
//		"limit014",//(��ɱ014)  
//		"limit015",//(��ɱ015)
//		"limit016",//(��ɱ016)  
//		"limit017",//(��ɱ017)  
//		"limit018",//(��ɱ018)  
//		"limit019",//(��ɱ019)
//		"limit020",//(��ɱ020)
//		"limit021",//(��ɱ021)
//		"limit022",//(��ɱ022)
//		"limit023",//(��ɱ023)
//		"limit024",//(��ɱ024)
//		"limit025",//(��ɱ025)
//		"limit026",//(��ɱ026)
//		"limit027",//(��ɱ027)
//		"limit028",//(��ɱ028)
//		"limit029",//(��ɱ029)
//		"limit030",//(��ɱ030)
//		"lijie1",//(���1)
//		"lijie2",//(���2)
//		"lijie3",//(���3)
//		"lijie4",//(���4)
//		"lijie5",//(���5)
//		"lijie6",//(���6)
//		"lijie7",//(���7)
//		"lijie8",//(���8)
//		"lijie9",//(���9)
//		"lijie10",//(���10)
//		"lijie11",//(���11)
//		"eyi1",//(����1)
//		"wudao1",//(�赸1)
//		"wudao2",//(�赸2)
//		"wudao3",//(�赸3)
//		"wudao4",//(�赸4)
//		"wudao5",//(�赸5)
//		"wudao6",//(�赸6)
//		"wudao7",//(�赸7)
//		"wudao8",//(�赸8)
//		"cool1",//(ˣ��1)	
//		"cool2",//(ˣ��2)	
//		"cool3",//(ˣ��3)	
//		"cool4",//(ˣ��4)
//	};	
//	char string[256];
//	//
//	int id=0;
//	int weapon_type;
//	for (int a=0; a<2; a++)
//	{
//		for (int b=0; b<2; b++)
//		{
//			for (int c=0; c<2; c++)
//			{
//				//for (int d=0; d<More_Profession_Max; d++)
//				for (int d=0; d<7; d++)
//				{
//					for (int e=0; e<Action_Max; e++)
//					{
//						if (c)
//							weapon_type = d;
//						else 
//							weapon_type = 0;
//						//
//						sprintf(string, "%s\\%s\\%s\\%s\\%s", 
//							//str_status[a], str_sex[b], str_profession[d],
//							str_status[a], str_sex[b], str_profession[d],
//							str_weapon[weapon_type], str_action[e]);
//						//
//						id = MoreAction::FindIdByName(string);
//						g_ArabicNightAction[a][b][c][d][e] = 0;
//						if (id > 0)
//							g_ArabicNightAction[a][b][c][d][e] = id; // fight  sex profession  action
//					}
//				}
//			}
//		}
//	}
//}
int MoreAction::GetActionType( DWORD dwActionType )
{
	guardfunc;
	return -1;
	unguard;
}

BOOL MoreAction::LoadRecordFromSLK( const char* pszFilename )
{
// 	CSlkReader r;
// 	if( !r.ReadFromFile( (char*)pszFilename ) )
// 	{
// 		return FALSE;
// 	}
// 
// 	int nLine = 2;
// 	int iRet;
// 
// 	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
// 	{
// 		if( CSlkReader::ret_nothisline == iRet )
// 			continue;
// 		SRecord	record;
// 		CSlkReader::SField* field;
// 		field = r.GetFieldOfLine( 1 );
// 		if( !field )
// 			continue;
// 		DWORD dwId = field->data.iValue;
// 		field = r.GetFieldOfLine( 2 );
// 		if( field )
// 		{
// 			strncpy_s(record.szIntro, sizeof(record.szIntro), field->data.szValue, sizeof(record.szIntro)-1);
// 		}
// 		field = r.GetFieldOfLine( 3 );
// 		if( !field )
// 		{
// 			// ToLog( false && "actionex.slk has empty name" );
// 			continue;
// 		}
// 		strncpy_s(record.szName, sizeof(record.szName), field->data.szValue, sizeof(record.szName)-1);
// 
// 		std::map<DWORD,SRecord>::const_iterator it2 = g_mapActionRecord.find( dwId );
// 		if( it2 != g_mapActionRecord.end() )
// 		{
// 			// ToLog( false && "actionex.slk has dup id" );
// 		}
// 		record.dwId = dwId;
// 		field = r.GetFieldOfLine( 4 );
// 		if( !field )
// 		{
// 			continue;
// 		}
// 		record.stModelId = field->data.iValue;
// 
// 		g_mapActionRecord[dwId] = record;
// 
// 		// Luo_157 added 2004.05.17
// 		g_actionMapStrToIdMgr.Register( record.szName, &g_mapActionRecord[dwId].dwId );
// 
// 		if( g_pfnLoadingCallBack )
// 		{
// 			//char s[MAX_PATH];
// 			//sprintf( s, "Loading Action Records %s.", record.szName );
// 			//g_pfnLoadingCallBack( s );
// 			g_pfnLoadingCallBack( record.szName );
// 		}
// 	}
	//
	//CreateActionTable();
	//
	//DWORD* a = (DWORD*)g_actionMapStrToIdMgr.GetDstByName( "Attack1" );
	return TRUE;
}