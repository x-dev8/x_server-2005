#ifndef	SOCIALITY_H
#define	SOCIALITY_H
#include <vector>
#include <math.h>
#include <assert.h>
#include <list>
#include <map>
#include "Me3d\include.h"
#include "player.h"
#include "playermgr.h"
#include "../Resource/Resource.h"
#include "GameMain.h"
#include "NetworkInput.h"
#include "Effect.h"
#include "PlayerRole.h"

#include "PlayerAnimCtrl.h"
#include "itemdetail.h"
#include "Me3d/MoreAction.h"
#include "XmlStringLanguage.h"
#include "QuestManager.h"
#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "MeUi/UiManager.h"
#include "ui/Pack.h"
#include "ui/UIStorage.h"
#include "ui/MessageBox.h"
#include "ui/ChatInfoBox.h"
#include "ui/Shop.h"
#include "ui/LoadMap.h"
#include "ui/Target.h"
#include "ui/Group.h"
#include "ui/PlayerPrivateShop.h"  
#include "ui/Property.h"
#include "ui/Bargaining.h"
#include "ui/Compound.h"
#include "UI\SelectBox.h"
#include "ui/baseProperty.h"
#include "ui/Task.h"
#include "UI\NpcChatDialogBox.h"
#include "ui/Main.h"
#include "ui/FriendDlg.h"
#include "ui/SelfRbtnMenu.h"  
#include "AttackInfoMan.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "MeUi/MouseManager.h"
#include "ui\FriendDlg.h"
#include "ui\rbtnmenu.h"
#include "MiniMap.h"
#include "ui/Progress.h"
#include "ShowScreenText.h"
#include "MeAudio/MeAudio.h"
#include "ui/topinfo.h"
#include "ui/Gang.h"
#include "GlobalDef.h"
#include "ActionManager.h"
#include "ItemDetail.h"
#include "GlobalDef.h"

#define	NAME_LENGTH	16
#define	BROTHER_AGE	25
#define TEACHER_AGE	50
#define	MAX_SIZE_PLAYER1	1
#define MAX_SIZE_PLAYER2	4
#define	SOCIALITY_COUNTS	10
using namespace std;


enum eSocialityType
{
	eSTP_HaveRelation = 0,  // ����
	eSTP_Marriage,          // ���
	eSTP_Brother,           // �ֵ�
	eSTP_Teacher,           // ʦ��
	eSTP_Student,           // ͽ��
	eSTP_BlackList,         // ������
	eSTP_VendettaList,      // ����
	eSTP_TempFriend,        // ��ʱ����

	eSTP_PLAYER_SIZE,    
};

//,eSTP_Marriage		//���
//,eSTP_Brother			//�ֵ�
//,eSTP_Teacher		//ʦ��
//,eSTP_Student			//ͽ��
//,eSTP_BlackList		//������


struct BinaryList					//�˽ṹ��server�˵�C_Character::SReputeFlag���Ӧ����������27���ƺ�
{
	DWORD a:6;					//��ǰ�ĳƺŵ�ID��(��Ϊ2��5�η�����32���㹻��ʾ27����������)
	DWORD b:26;				//�򿪵ĳƺŵ����
};

struct BeNamed
{
	eSocialityType	type;
	char	ClanName[GuildDefine::MaxNameLength ];
};

class HeroSocial
{
public:
	HeroSocial();
	
	void	InitClanBuffer();
	void SetCurrceDisplay(eSocialityType sotye){eCurrseDisplay = sotye;};
	const char* GetClanNames(eSocialityType sotye);
	std::string GetClanNamedOf();
	void AddBrotherName(const char* name);
	void AddClanName(DWORD sotyp,const char* clanname);
	void DrawClanTitle(int x,int y,eSocialityType textype,DWORD dwColor,BOOL bShow = TRUE);
public://���Ϻ���Ϊ�ɰ汾���룬���µĳƺ�ϵͳ��û�е��ã�ֻ����û��ɾ��
	const char* SetRepute(const char* szName,DWORD type,short playerid,SRankManager rkmgr, bool isMan);//�������ÿͻ��˵����
	const char* SetReputeRank(const char* szName,DWORD type,short playerid);
	void CallForRepute2Server(char* name = NULL);

	const char* DelRepute(DWORD type,short playerid,bool isman,DWORD delrepIndex);

	DWORD	dwFlag;
public://rank
	void GetRankName(WORD x,WORD y,std::string& rankname, bool bDescription = false);
protected:	
	std::string rankname;
	std::string reputename;
	eSocialityType	eCurrseDisplay;
	BeNamed	PlayerClan[SOCIALITY_COUNTS];
private:
};

extern HeroSocial* GetSocial();
#endif