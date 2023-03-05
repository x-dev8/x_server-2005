#include "MoreActionClient.h"
#include "Me3d/MoreAction.h"
#include "MapStrToId.h"

#define ADD_ACTION_RECORD(a) {	MoreAction::g_mapActionName[a] = #a;			\
	static DWORD AA##a = a;				\
	g_actionMapStrToIdMgr.Register( #a, &AA##a );	\
								}

extern CMapStrToIDMgr g_actionMapStrToIdMgr;

bool MoreActionClient::Initialize()
{

	ADD_ACTION_RECORD( Model );
	ADD_ACTION_RECORD( Idle1 );
	ADD_ACTION_RECORD( SpecialIdle );
	ADD_ACTION_RECORD( Walk1 );
	ADD_ACTION_RECORD( WalkBackWards );
	ADD_ACTION_RECORD( Swim );
	ADD_ACTION_RECORD( SwimIdle );

	ADD_ACTION_RECORD( Sit						);
	ADD_ACTION_RECORD( SitLoop					);
	ADD_ACTION_RECORD( Run1                       );
	ADD_ACTION_RECORD( Rush                       );

	ADD_ACTION_RECORD( Drunk                      );
	ADD_ACTION_RECORD( Decline                    );
	ADD_ACTION_RECORD( Combat                     );

	ADD_ACTION_RECORD( Resist                     );
	ADD_ACTION_RECORD( Miss                       );
	ADD_ACTION_RECORD( Sway                       );
	ADD_ACTION_RECORD( BeatBack                   );
	ADD_ACTION_RECORD( Hold                       );
	ADD_ACTION_RECORD( Death                      );

	ADD_ACTION_RECORD( Attack_idle                 );

	ADD_ACTION_RECORD( Attack1                    );
	ADD_ACTION_RECORD( Attack2                    );

	ADD_ACTION_RECORD( Pick                        );
	ADD_ACTION_RECORD( Hack							);
	ADD_ACTION_RECORD( Dig                       );
	ADD_ACTION_RECORD( Recital                       );
	ADD_ACTION_RECORD( Fire                      );
	ADD_ACTION_RECORD( Defend                       );

	ADD_ACTION_RECORD( Run );
	ADD_ACTION_RECORD( Walk );
	ADD_ACTION_RECORD( Idle );
	ADD_ACTION_RECORD( Dead );
	ADD_ACTION_RECORD( Tired );
	ADD_ACTION_RECORD( Hurt );
	ADD_ACTION_RECORD( Miss1 );
	ADD_ACTION_RECORD( Intonate );
	ADD_ACTION_RECORD( Stun );

	// 魔法动作
	ADD_ACTION_RECORD( MagicBorn                  );
	ADD_ACTION_RECORD( MagicDead                  );
	ADD_ACTION_RECORD( MagicRun                   );
	ADD_ACTION_RECORD( MagicExplode               );
	ADD_ACTION_RECORD( MagicFire                  );

	ADD_ACTION_RECORD( Idle2                  );

	//双手武器		
	//Human
	ADD_ACTION_RECORD( walk_attack                  );
	ADD_ACTION_RECORD( run_attack                  );

	ADD_ACTION_RECORD( Attack_idle                  );
	ADD_ACTION_RECORD( Attack1                  );
	ADD_ACTION_RECORD( Attack2                  );
	ADD_ACTION_RECORD( Attack3                  );
	ADD_ACTION_RECORD( double_attack_idle                  );
	ADD_ACTION_RECORD( double_attack2                  );
	ADD_ACTION_RECORD( double_defend                  );
	ADD_ACTION_RECORD( double_recital );
	ADD_ACTION_RECORD( double_recital1 );
	ADD_ACTION_RECORD( double_recital2 );
	ADD_ACTION_RECORD( double_recital3 );
	ADD_ACTION_RECORD( double_recital4 );
	ADD_ACTION_RECORD( double_recital5 );
	ADD_ACTION_RECORD( double_recital6 );

	ADD_ACTION_RECORD( double_fire                  );
	ADD_ACTION_RECORD( double_hurt                  );

	ADD_ACTION_RECORD( double_dead                  );
	ADD_ACTION_RECORD( double_attack1                  );
	ADD_ACTION_RECORD( double_scabbard                  );
	ADD_ACTION_RECORD( double_draw                  );
	ADD_ACTION_RECORD( double_run					);
	//单手武器
	ADD_ACTION_RECORD( single_attack_idle                  );
	ADD_ACTION_RECORD( single_idle                  );
	ADD_ACTION_RECORD( single_attackr1                  );
	ADD_ACTION_RECORD( single_attackl1                  );
	ADD_ACTION_RECORD( single_attackr2                  );
	ADD_ACTION_RECORD( single_attackl2                  );
	ADD_ACTION_RECORD( single_recital );
	ADD_ACTION_RECORD( single_recital1 );
	ADD_ACTION_RECORD( single_recital2 );
	ADD_ACTION_RECORD( single_recital3 );
	ADD_ACTION_RECORD( single_recital4 );
	ADD_ACTION_RECORD( single_recital5 );
	ADD_ACTION_RECORD( single_recital6 );
	ADD_ACTION_RECORD( single_fire                  );
	ADD_ACTION_RECORD( single_hurt                  );
	ADD_ACTION_RECORD( single_dead                  );
	ADD_ACTION_RECORD( single_run					);
	ADD_ACTION_RECORD( jump );
	ADD_ACTION_RECORD( drop );
	ADD_ACTION_RECORD( glide );
	ADD_ACTION_RECORD( falltothegroundrun );
	ADD_ACTION_RECORD( jump1 );
	ADD_ACTION_RECORD( drop1 );
	ADD_ACTION_RECORD( glide1 );
	ADD_ACTION_RECORD( falltothegroundrun1 );
	ADD_ACTION_RECORD( single_double_draw                  );
	ADD_ACTION_RECORD( single_double_scabbard                  );

	ADD_ACTION_RECORD( single_draw                  );
	ADD_ACTION_RECORD( single_scabbard                  );
	ADD_ACTION_RECORD( single_walk_attackr1                  );
	ADD_ACTION_RECORD( single_walk_attackl1                  );
	ADD_ACTION_RECORD( single_run_attackr1                  );
	ADD_ACTION_RECORD( single_run_attackl1                  );
	ADD_ACTION_RECORD( run_fire                  );
	ADD_ACTION_RECORD( walk_fire                  );
	ADD_ACTION_RECORD( strike                  );
	ADD_ACTION_RECORD( sting                  );
	ADD_ACTION_RECORD( brisance                  );
	ADD_ACTION_RECORD( frenzy                  );
	ADD_ACTION_RECORD( temp2006 );
	ADD_ACTION_RECORD( single_jump );
	ADD_ACTION_RECORD( single_glide );
	ADD_ACTION_RECORD( single_drop );
	ADD_ACTION_RECORD( single_falltothegroundrun );
	ADD_ACTION_RECORD( single_walkbackwards );
	ADD_ACTION_RECORD( single_walk );
	ADD_ACTION_RECORD( single_specialidle );
	ADD_ACTION_RECORD( single_attack_drop );
	ADD_ACTION_RECORD( single_attack_falltothegroundrun );
	ADD_ACTION_RECORD( single_attack_run );
	ADD_ACTION_RECORD( single_attack_walkbackwards );
	ADD_ACTION_RECORD( single_mountdrive );
	ADD_ACTION_RECORD( single_mountwalk );
	ADD_ACTION_RECORD( single_mountrun );
	ADD_ACTION_RECORD( single_mountjump );
	ADD_ACTION_RECORD( single_mountFalltothegroundrun );
	ADD_ACTION_RECORD( single_mountGlide );
	ADD_ACTION_RECORD( single_mountwalkbackwards );
	ADD_ACTION_RECORD( single_mountShuffleleft );
	ADD_ACTION_RECORD( single_mountShuffleright );
	ADD_ACTION_RECORD( single_mountneigh );
	ADD_ACTION_RECORD( single_mountbackattack );
	ADD_ACTION_RECORD( single_mountdrop );
	ADD_ACTION_RECORD( single_stun );
	ADD_ACTION_RECORD( single_run_scabbard );
	ADD_ACTION_RECORD( single_run_draw );
	ADD_ACTION_RECORD( stand );
	ADD_ACTION_RECORD( loot );
	ADD_ACTION_RECORD( single_flag_run );
	ADD_ACTION_RECORD( single_flag_idle );
	ADD_ACTION_RECORD( neigh );
	ADD_ACTION_RECORD( shuffleleft );
	ADD_ACTION_RECORD( shuffleright );
	ADD_ACTION_RECORD( backattack );
	ADD_ACTION_RECORD( single_yanwu );
	ADD_ACTION_RECORD(mountattackidle);
	ADD_ACTION_RECORD(mountattack_run);
	ADD_ACTION_RECORD(single_mountattackidle);
	ADD_ACTION_RECORD(single_mountattack_run);
	ADD_ACTION_RECORD(single_mountscabbard);
	ADD_ACTION_RECORD(single_mountdraw);
	ADD_ACTION_RECORD(single_walk);
	ADD_ACTION_RECORD(single_walkbackwards);
	ADD_ACTION_RECORD(yongbao);
	ADD_ACTION_RECORD(mountdrive);
	ADD_ACTION_RECORD(mountwalk);
	ADD_ACTION_RECORD(mountrun);
	ADD_ACTION_RECORD(mountjump);
	ADD_ACTION_RECORD(mountfalltothegroundrun);
	ADD_ACTION_RECORD(mountglide);
	ADD_ACTION_RECORD(mountwalkbackwards);
	ADD_ACTION_RECORD(mountshuffleleft);
	ADD_ACTION_RECORD(mountshuffleright);
	ADD_ACTION_RECORD(mountneigh);
	ADD_ACTION_RECORD(mountdrop);
	ADD_ACTION_RECORD(swimback);
	ADD_ACTION_RECORD(single_fallow);
	ADD_ACTION_RECORD(single_flag);
	ADD_ACTION_RECORD(single_shuffle);
	ADD_ACTION_RECORD(single_holding1);
	ADD_ACTION_RECORD( single_mountdrive2 );
	ADD_ACTION_RECORD( single_mountrun2 );
	ADD_ACTION_RECORD( single_mountjump2 );
	ADD_ACTION_RECORD( single_mountFalltothegroundrun2 );
	ADD_ACTION_RECORD( single_mountGlide2 );
	ADD_ACTION_RECORD( single_mountwalkbackwards2 );
	ADD_ACTION_RECORD( single_mountShuffleleft2 );
	ADD_ACTION_RECORD( single_mountShuffleright2 );
	ADD_ACTION_RECORD( single_mountneigh2 );
	ADD_ACTION_RECORD( single_mountbackattack2 );
	ADD_ACTION_RECORD( single_mountdrop2 );
	ADD_ACTION_RECORD( single_mountdrive3 );
	ADD_ACTION_RECORD( single_mountrun3 );
	ADD_ACTION_RECORD( single_mountjump3 );
	ADD_ACTION_RECORD( single_mountFalltothegroundrun3 );
	ADD_ACTION_RECORD( single_mountGlide3 );
	ADD_ACTION_RECORD( single_mountwalkbackwards3 );
	ADD_ACTION_RECORD( single_mountShuffleleft3 );
	ADD_ACTION_RECORD( single_mountShuffleright3 );
	ADD_ACTION_RECORD( single_mountneigh3 );
	ADD_ACTION_RECORD( single_mountbackattack3 );
	ADD_ACTION_RECORD( single_mountdrop3 );
	ADD_ACTION_RECORD( single_skill );
	ADD_ACTION_RECORD( EmoteApplaud );
	ADD_ACTION_RECORD( EmoteBow );
	ADD_ACTION_RECORD( EmoteCheer );
	ADD_ACTION_RECORD( EmoteCry );
	ADD_ACTION_RECORD( EmoteKiss );
	ADD_ACTION_RECORD( EmoteLaugh );
	ADD_ACTION_RECORD( EmoteRoar );
	ADD_ACTION_RECORD( EmoteTalk );
	ADD_ACTION_RECORD( EmoteWave );
	ADD_ACTION_RECORD( EmoteNo );
	ADD_ACTION_RECORD( EmoteYes );
	ADD_ACTION_RECORD( EmoteLook );
	ADD_ACTION_RECORD( EmoteShy );
	ADD_ACTION_RECORD( EmoteStun );
	ADD_ACTION_RECORD( EmoteWin );
	ADD_ACTION_RECORD( EmoteBad );
	ADD_ACTION_RECORD( EmoteSurprise );
	ADD_ACTION_RECORD( EmoteAdmire );
	ADD_ACTION_RECORD( EmoteBrag );
	ADD_ACTION_RECORD( EmoteCool );
	ADD_ACTION_RECORD( EmoteGreet );
	ADD_ACTION_RECORD( EmoteKneelStart );
	ADD_ACTION_RECORD( EmoteKneelLoop );
	ADD_ACTION_RECORD( hurt01 )
	ADD_ACTION_RECORD( dead2  );
	ADD_ACTION_RECORD( single_shuffleleft  );
	ADD_ACTION_RECORD( single_shuffleright  );
	ADD_ACTION_RECORD( single_falltothegroundwalkbackwards );
	ADD_ACTION_RECORD( single_revive );

	ADD_ACTION_RECORD(box_drop);
	ADD_ACTION_RECORD(box_stand);
	ADD_ACTION_RECORD(box_open);
	ADD_ACTION_RECORD(box_KeepOpen);
	ADD_ACTION_RECORD(PetCall);
	return true;
}