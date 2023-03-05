#include "StdAfx.h"
#include "AttackBot.h"
#include "FightBot.h"
#include "BotAppDataCenter.h"
#include "ScriptManager.h"
#include "CountryDefine.h"
#include "MapConfig.h"
#include "ItemDetailConfig.h"
extern bool g_bCountryFight;			// ȫ�ֻ����˹�ս���� luo.qin 3.28
extern bool g_PlaySkill;				// ȫ�ּ��ܿ��ƿ��� luo.qin 3.28

extern bool g_bCreateMonster;			// ȫ�ֻ����˴������￪�� luo.qin 3.18
extern bool g_bChangeEquip;				// ȫ�ֻ����˻�װ���� luo.qin 3.21
extern bool g_bRandRide;				// ȫ�ֻ�������������� luo.qin 3.21	

CFightBot::CFightBot() : CAttackBot(),LastMapId(-1)
{
	m_BotType = Bot_Fight;
}

CFightBot::~CFightBot()
{

}

void CFightBot::InitPlayGame(UINT mapid)
{
	//�л���PK ģʽ

	MsgChangePKFlag xMsg;
	xMsg.shFlag = PKMode_Fight;
	SendMsg(&xMsg);

	CAttackBot::InitPlayGame(mapid);
}

void CFightBot::PlayGame()
{
	std::string FullPath = theBotDataCenter.ScriptFilePath;
	FullPath += theBotDataCenter.ScriptFileName;
	uint32 result = theScriptManager.LoadScript(FullPath.c_str());
	if (ER_Success == result)
	{
		theScriptManager.ScriptFunctionVoid("PlayGame",this);
	}


	//ÿ3�����Ӧ�Ļ����˴���һ��Monster luo.qin 3.17
	if ( GameTime::IsPassCurrentTime( m_LastCreateTime, Monster_Create_TimeSpace ) && g_bCreateMonster )//��֤�������Ѿ��ɵ�ָ����ͼ
	{
		if (  m_MonsterNum < Monster_Num_Total )
		{		

			BotCreateMonster( (DWORD)GetBotDBID(), 100011 , GetPosX() , GetPosY(), Monster_Num_PerSecond );
			m_MonsterNum += Monster_Num_PerSecond;
			//m_xMsgStatistician.SetMonsterNum( m_MonsterNum );
			m_LastCreateTime = HQ_TimeGetTime();

		}
	}
	if (g_bCountryFight)
	{
		PlayFight();
	}

	Say("�񹦸����������޵У��������Ҿ�һ��ս��");

	if (LastMapId == -1)
		LastMapId = GetMapID();

	if (LastMapId != GetMapID())
	{
		MsgChangePKFlag xMsg;
		xMsg.shFlag = PKMode_Normal;
		SendMsg(&xMsg);
		LastMapId = GetMapID();
	}
	PlayFight();
}

void CFightBot::PlayFight()
{
	CAttackBot::PlayAttack();
}

GameObjectId CFightBot::LockTarget()
{
	return CAttackBot::LockTarget();
	short shTarget = -1;

	vector<PlayerInfo*> vecPlayer;

	list<PlayerInfo>::iterator iter = m_listPlayerList.begin();
	list<PlayerInfo>::iterator end = m_listPlayerList.end();
	for ( ; iter != end; ++iter)
	{
		if (IsInArea(GetMapID(), (*iter).m_vPos) && (*iter).nHP > 0 && IsNotSameCountry((*iter)))
		{
			vecPlayer.push_back(&(*iter));
		}
	}

	if (vecPlayer.empty())
	{
		return shTarget;
	}

	//�漴һ��Ŀ��
	int nRand = rand() % vecPlayer.size();
	shTarget = vecPlayer[nRand]->shPlayerID;

	//���������Ϣ
	MsgQueryCharInfo query;
	query.stChar = shTarget;
	SendMsg(&query);  		

	return shTarget;
}


PlayerInfo* CFightBot::GetLockPlayerInfo(GameObjectId shID)
{
	//return GetPlayer(shID);
	return CAttackBot::GetLockPlayerInfo(shID);
}

void CFightBot::RandReqCharInfo(GameObjectId shID)
{
	///////ս�������˶�Ҫ����
	MsgQueryCharInfo query;
	query.stChar = shID;
	SendMsg(&query); 
	CAttackBot::RandReqCharInfo(shID);
}

//ͨ���������ж�, �����˷�T �� H ��ͷ��~  T �� H ���ǵжԷ�
bool CFightBot::IsEnemyPlayer(PlayerInfo &xpPlayer)
{
	string strPlayerName = xpPlayer.szName;					//��ҵ�����
	string strSelfName = GetBotRoleName();					//�Լ�������

	//�ж��׸��ַ�, ����Ҫ�ǻ�����, �Լ�����ȥ�Ĳ��ܹ���
	string strFirstName = "";
	for (int i = 0; i < s_nNameCount; ++i)
	{
		if (strPlayerName.find(s_pszName[i]) != string::npos)
		{
			strFirstName.assign(strPlayerName.c_str(), 1);
			break;
		}
	}

	if (strFirstName.empty())								//���ǻ�����
	{
		return false;
	}

	return (strSelfName.find(strFirstName) == string::npos);
}

extern bool g_bCountryFight;								// ȫ�ֻ����˹�ս���� luo.qin 3.28
extern bool g_PlaySkill;									// ȫ�ּ��ܿ��ƿ��� luo.qin 3.28

//��ȡ�ַ����е������������ַ���ת����luo.qin 3.28
int CFightBot::StrToInt( char *strPlayerName )
{

	char temchar[10] = {0};
	int  nPos = 0;
	int  nNameLen = strlen( strPlayerName );
	for ( int i = 0; i < nNameLen; ++i )
	{
		if ( strPlayerName[i] >=48 && strPlayerName[i] <= 57)
		{
			temchar[nPos] = strPlayerName[i]; 
			++nPos;
		}
	}
	temchar[nPos] = '\0';

	int nPlayerID = atoi( temchar );
	return nPlayerID;
}
//��ù��ҵ�ö��ֵluo.qin 3.28
int CFightBot::GetCountry( char *strPlayerName )
{
	int nPlayerID = StrToInt( strPlayerName );

	if ( 0 < nPlayerID && nPlayerID < 1000 )							//��������ң����ڹ۲������
	{
		return -1;
	}
	else if (1000 < nPlayerID && nPlayerID <= 6000)						// ����
	{
		return CountryDefine::Country_LouLan;
	}
	else if ( 6000 < nPlayerID && nPlayerID <= 11000 )					// ����
	{
		return CountryDefine::Country_KunLun;
	}
	else if ( 11000 < nPlayerID && nPlayerID <= 16000 )					// �ӱ�
	{
		return CountryDefine::Country_DunHuang;
	}
	else
	{
		return CountryDefine::Country_Init;
	}


}
//ͨ���˺ŷֲ����ж��Ƿ��ǵжԷ�
bool CFightBot::IsNotSameCountry(PlayerInfo &xpPlayer)
{
	if ( StrToInt( xpPlayer.szName ) < 1000 )							//����˺�,����Ҵ�������Ӫ״̬����ֹ��ұ������˴���
	{
		return false;
	}
	return ( GetCountry( this->GetBotRoleName() ) != GetCountry( xpPlayer.szName ) );
}