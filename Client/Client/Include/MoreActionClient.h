#pragma once
#include "MeRTLibs.h"

class MoreActionClient
{
public:
	enum
	{
		Model
		,Idle1
		,Idle2			// ����
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

		,Pick,			//��ҩnew
		Hack,			//����new
		Dig,			//�ɿ�new
		Recital,		//����new
		Fire,			//ʦ�� new
		Defend			//����new

		// ħ������
		,MagicBorn
		,MagicDead
		,MagicRun
		,MagicExplode
		,MagicFire

		,Run			// ��
		,Walk			// ��
		,Idle			// ����
		,Dead			// ����
		,Tired			// ƣ��
		,Hurt			// ����
		,Miss1			// ʧЧ
		,Intonate		// ����

		,walk_attack	//���߹���  
		,run_attack		//���ܹ���  

		,Attack_idle	//(ս������)new

		,Attack1		// ��ͨ����1
		,Attack2		// ��ͨ����2
		,Attack3,		// ��ͨ����2

		//˫������		
		double_attack_idle,// ս������
		double_attack2,    //��ͨ����2   897    934  (912
		//��ͨ����3           941    988  (954
		//��ͨ����4           1003   1047 (1023
		double_defend,	//����                1159   1174
		double_recital,	//��������            1185   1215
		double_recital1,	//��������            1185   1215
		double_recital2,	//��������            1185   1215
		double_recital3,	//��������            1185   1215
		double_recital4,	//��������            1185   1215
		double_recital5,	//��������            1185   1215
		double_recital6,	//��������            1185   1215
		double_fire,		//����ʦ��            1217   1256
		double_hurt,		//����                1261   1275
		double_dead,		//����                1282   1333
		double_attack1,	//��ͨ����1    1337   1366  (1350
		double_scabbard,	//������          1383   1426
		double_draw,		//�γ�����         1433   1446
		double_run,			//��˫�ֽ���

		//��������
		single_attack_idle,		//ս������       35      67
		single_idle,			//��ս������          75     132
		//		walk,					//��·              135     167
		//		run,					//�ܲ�              180     199
		single_attackr1,		//������ͨ����1     208     229  (218  
		single_attackl1,		//������ͨ����2       238     260  (249  
		single_attackr2,		//������ͨ����3       273     295 ��283
		single_attackl2,		//������ͨ����4       304     326 ��313
		//�����ػ�            334     360 ��344
		//����                366     382 ��371
		single_recital,			//��������            386     415
		single_recital1,			//��������            386     415
		single_recital2,			//��������            386     415
		single_recital3,			//��������            386     415
		single_recital4,			//��������            386     415
		single_recital5,			//��������            386     415
		single_recital6,			//��������            386     415
		single_fire,			//����ʦ��            417     454
		single_hurt,			//����                456     470
		single_dead,			//����                475     520       
		//single_jump,			//����                604     618
		single_run,				//�õ��ֽ���

		jump,					//����                604     618
		drop,			//���                619     635
		glide,			//ͣ��                647     666
		falltothegroundrun,	//�����                674     703

		jump1,
		drop1,
		glide1,
		falltothegroundrun1,

		single_double_draw,			//˫�ְγ�����             741     754
		single_double_scabbard,		//˫����������             710     740
		single_draw,				//������������             760     790 
		single_scabbard,			//���ְγ�����             791     804
		single_walk_attackr1,		//�������ֹ���            2141     2172  (2154
		single_walk_attackl1,		//�������ֹ���            2176     2207 ��2185
		single_run_attackr1,		//�ܲ����ֹ���            2212     2231 ��2221
		single_run_attackl1,		//�ܲ����ֹ���            2233     2252 ��2243 
		run_fire,					//�ܲ�ʩ��                2275     2294 ��2263
		walk_fire,					//����ʩ��                2298     2329

		//���⶯��
		strike,						//���              2341     2378 ��2359��2367
		sting,						//�̼�               2401     2423 ��2409
		brisance,					//����            2431     2455 ��2443
		frenzy,						//��              2461     2485
		temp2006,

		single_jump,                //������������
		single_glide,               //������������
		single_drop,                //������������
		single_falltothegroundrun,  //�������������
		single_walkbackwards,       //������������
		single_walk,                //������������
		//single_stand,				//�������������µ�վ��
		single_specialidle,			//���������������

		// ս����̬������
		single_attack_jump,
		single_attack_glide,
		single_attack_drop,
		single_attack_falltothegroundrun,
		single_attack_run,
		single_attack_walkbackwards,

		// ����������
		single_mountdrive,
		single_mountwalk,		// ����
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

		// ����������˶���
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

		single_run_scabbard,		//�ܲ��а�����
		single_run_draw,			//�ܲ���������

		stand,						//�����µ�վ��
		loot,						//�ɼ�
		single_flag_run,            //�������ϱ���
		single_flag_idle,           //��������idle

		// ����
		neigh,
		shuffleleft,
		shuffleright,
		backattack,

		single_yanwu,               //ѡ����ʱ���⶯��

		mountattackidle,
		mountattack_run,
		single_mountattackidle,
		single_mountattack_run,
		single_mountscabbard,
		single_mountdraw,

		// ��������
		yongbao,

		// ���䲻����������
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
		single_holding1,    // �񵲶�����ֻ�а�����

		picking,

		single_skill,		// �����켼�ܶ���

		// ���鶯��
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

		hurt01, //����
		dead2,  //����
		
		single_shuffleleft,  //��ת
		single_shuffleright, //��ת
		single_falltothegroundwalkbackwards, //������ض���

		single_revive,  //�����
		box_drop,		//���������ĸ�����
		box_stand,
		box_open,
		box_KeepOpen,

		PetCall, //�����ս
		MaxAction
	};

	/// initialize
	static bool Initialize();
};
