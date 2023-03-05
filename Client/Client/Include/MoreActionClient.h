#pragma once
#include "MeRTLibs.h"

class MoreActionClient
{
public:
	enum
	{
		Model
		,Idle1
		,Idle2			// 闲置
		,SpecialIdle
		,Walk1
		,WalkBackWards
		,Run1
		,Rush
		,Swim
		,SwimIdle
		,Sit
		,SitLoop
		,Drunk
		,Decline
		,Combat
		,Resist
		,Miss
		,Sway
		,BeatBack
		,Hold
		,Death
		,Stun

		,Pick,			//采药new
		Hack,			//砍伐new
		Dig,			//采矿new
		Recital,		//吟唱new
		Fire,			//师法 new
		Defend			//防御new

		// 魔法动作
		,MagicBorn
		,MagicDead
		,MagicRun
		,MagicExplode
		,MagicFire

		,Run			// 跑
		,Walk			// 走
		,Idle			// 待机
		,Dead			// 死亡
		,Tired			// 疲劳
		,Hurt			// 被击
		,Miss1			// 失效
		,Intonate		// 吟唱

		,walk_attack	//行走攻击  
		,run_attack		//奔跑攻击  

		,Attack_idle	//(战斗待机)new

		,Attack1		// 普通攻击1
		,Attack2		// 普通攻击2
		,Attack3,		// 普通攻击2

		//双手武器		
		double_attack_idle,// 战斗待机
		double_attack2,    //普通攻击2   897    934  (912
		//普通攻击3           941    988  (954
		//普通攻击4           1003   1047 (1023
		double_defend,	//防御                1159   1174
		double_recital,	//武器吟唱            1185   1215
		double_recital1,	//武器吟唱            1185   1215
		double_recital2,	//武器吟唱            1185   1215
		double_recital3,	//武器吟唱            1185   1215
		double_recital4,	//武器吟唱            1185   1215
		double_recital5,	//武器吟唱            1185   1215
		double_recital6,	//武器吟唱            1185   1215
		double_fire,		//武器师法            1217   1256
		double_hurt,		//被击                1261   1275
		double_dead,		//死亡                1282   1333
		double_attack1,	//普通攻击1    1337   1366  (1350
		double_scabbard,	//收武器          1383   1426
		double_draw,		//拔出武器         1433   1446
		double_run,			//拿双手剑跑

		//单手武器
		single_attack_idle,		//战斗待机       35      67
		single_idle,			//非战斗待机          75     132
		//		walk,					//走路              135     167
		//		run,					//跑步              180     199
		single_attackr1,		//右手普通攻击1     208     229  (218  
		single_attackl1,		//左手普通攻击2       238     260  (249  
		single_attackr2,		//右手普通攻击3       273     295 （283
		single_attackl2,		//左手普通攻击4       304     326 （313
		//右手重击            334     360 （344
		//防御                366     382 （371
		single_recital,			//武器吟唱            386     415
		single_recital1,			//武器吟唱            386     415
		single_recital2,			//武器吟唱            386     415
		single_recital3,			//武器吟唱            386     415
		single_recital4,			//武器吟唱            386     415
		single_recital5,			//武器吟唱            386     415
		single_recital6,			//武器吟唱            386     415
		single_fire,			//武器师法            417     454
		single_hurt,			//被击                456     470
		single_dead,			//死亡                475     520       
		//single_jump,			//跳起                604     618
		single_run,				//拿单手剑跑

		jump,					//跳起                604     618
		drop,			//落地                619     635
		glide,			//停空                647     666
		falltothegroundrun,	//落地跑                674     703

		jump1,
		drop1,
		glide1,
		falltothegroundrun1,

		single_double_draw,			//双手拔出武器             741     754
		single_double_scabbard,		//双手收起武器             710     740
		single_draw,				//单手收起武器             760     790 
		single_scabbard,			//单手拔出武器             791     804
		single_walk_attackr1,		//行走右手攻击            2141     2172  (2154
		single_walk_attackl1,		//行走左手攻击            2176     2207 （2185
		single_run_attackr1,		//跑步右手攻击            2212     2231 （2221
		single_run_attackl1,		//跑步右手攻击            2233     2252 （2243 
		run_fire,					//跑步施法                2275     2294 （2263
		walk_fire,					//行走施法                2298     2329

		//特殊动作
		strike,						//冲击              2341     2378 （2359，2367
		sting,						//刺甲               2401     2423 （2409
		brisance,					//震裂            2431     2455 （2443
		frenzy,						//狂暴              2461     2485
		temp2006,

		single_jump,                //单手武器跳起
		single_glide,               //单手武器滑行
		single_drop,                //单手武器落下
		single_falltothegroundrun,  //单手武器落地跑
		single_walkbackwards,       //单手武器后退
		single_walk,                //单手武器行走
		//single_stand,				//单手武器从坐下到站起
		single_specialidle,			//单手武器特殊待机

		// 战斗姿态拿武器
		single_attack_jump,
		single_attack_glide,
		single_attack_drop,
		single_attack_falltothegroundrun,
		single_attack_run,
		single_attack_walkbackwards,

		// 拿武器骑马
		single_mountdrive,
		single_mountwalk,		// 不用
		single_mountrun,
		single_mountjump,
		single_mountFalltothegroundrun,
		single_mountGlide,
		single_mountwalkbackwards,
		single_mountShuffleleft,
		single_mountShuffleright,
		single_mountneigh,
		single_mountbackattack,
		single_mountdrop,

		// 新增两套骑乘动作
		single_mountdrive2,
		single_mountrun2,
		single_mountjump2,
		single_mountFalltothegroundrun2,
		single_mountGlide2,
		single_mountwalkbackwards2,
		single_mountShuffleleft2,
		single_mountShuffleright2,
		single_mountneigh2,
		single_mountbackattack2,
		single_mountdrop2,

		single_mountdrive3,
		single_mountrun3,
		single_mountjump3,
		single_mountFalltothegroundrun3,
		single_mountGlide3,
		single_mountwalkbackwards3,
		single_mountShuffleleft3,
		single_mountShuffleright3,
		single_mountneigh3,
		single_mountbackattack3,
		single_mountdrop3,

		single_stun,

		single_run_scabbard,		//跑步中拔武器
		single_run_draw,			//跑步中收武器

		stand,						//从坐下到站起
		loot,						//采集
		single_flag_run,            //举旗马上奔跑
		single_flag_idle,           //举旗马上idle

		// 马动作
		neigh,
		shuffleleft,
		shuffleright,
		backattack,

		single_yanwu,               //选武器时特殊动作

		mountattackidle,
		mountattack_run,
		single_mountattackidle,
		single_mountattack_run,
		single_mountscabbard,
		single_mountdraw,

		// 互动动作
		yongbao,

		// 补充不拿武器骑马
		mountdrive,
		mountwalk,
		mountrun,
		mountjump,
		mountfalltothegroundrun,
		mountglide,
		mountwalkbackwards,
		mountshuffleleft,
		mountshuffleright,
		mountneigh,
		mountdrop,

		swimback,
		single_fallow,
		single_flag,
		single_shuffle,
		single_holding1,    // 格挡动作，只有霸王有

		picking,

		single_skill,		// 播军旗技能动作

		// 表情动作
		EmoteApplaud,
		EmoteBow,
		EmoteCheer,
		EmoteCry,
		EmoteKiss,
		EmoteLaugh,
		EmoteRoar,
		EmoteTalk,
		EmoteWave,
		EmoteNo,
		EmoteYes,
		EmoteLook,
		EmoteShy,
		EmoteStun,
		EmoteWin,
		EmoteBad,
		EmoteSurprise,
		EmoteAdmire,
		EmoteBrag,
		EmoteCool,
		EmoteGreet,
		EmoteKneelStart,
		EmoteKneelLoop,

		hurt01, //浮空
		dead2,  //击退
		
		single_shuffleleft,  //左转
		single_shuffleright, //右转
		single_falltothegroundwalkbackwards, //后跳落地动作

		single_revive,  //复活技能
		box_drop,		//宝箱掉落的四个动作
		box_stand,
		box_open,
		box_KeepOpen,

		PetCall, //宠物出战
		MaxAction
	};

	/// initialize
	static bool Initialize();
};
