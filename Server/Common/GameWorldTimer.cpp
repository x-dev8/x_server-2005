#include "GameWorldTimer.h"
#include "ScriptMgr.h"
#include "Helper.h"
#include "FuncPerformanceLog.h"
#include "Errorlog.h"
#include "MessageDefine.h"
#include "GameServer.h"
#include "Configure.h"

CGameWorldTimer* GetGameWorldTimer()
{
	static CGameWorldTimer s_GameWorldTimer;
	return &s_GameWorldTimer;
}

CGameWorldTimer::CGameWorldTimer(void)
{
	m_nGameYear = 1;
	m_nCurGameYear = 1;
	m_nGameMonth = 1;
	m_nGameDay = 1;
	m_nGameHour = 0;
	m_nGameMinute = 0;
	m_nRate = 1;
	m_bInit = false;
}

CGameWorldTimer::~CGameWorldTimer(void)
{
}

bool CGameWorldTimer::Init( int year, int month, int day, int hour, int minute,
						   int rate, const char* szYear, int nGameYear )
{
	m_nGameYear = year;
	m_nGameMonth = month;
	m_nGameDay = day;
	m_nGameHour = hour;
	m_nGameMinute = minute;
	if( rate >= 1 )
		m_nRate = rate;
	m_strGameYear = szYear;
	m_nCurGameYear = nGameYear;
	m_bInit = true;
	return true;
}

//void CGameWorldTimer::Run()
//{
//	// ToLog( m_bInit );
//	static DWORD dwLastTime = 0;
//	if ( HQ_TimeGetTime() - dwLastTime < GAME_WORLD_TIME_UPDATE_RATE )
//		return;
//	dwLastTime = HQ_TimeGetTime();
//	//
//	std::time_t t = std::time( NULL );
//	std::tm *tme = std::localtime( &t );
//	int nYear = tme->tm_year + 1900;
//	int nMonth = tme->tm_mon + 1;
//	int nDay = tme->tm_mday;
//	int nHour = tme->tm_hour;
//	int nMinute = tme->tm_min;
//	// ����=INT(((ʵ����-1)*24+ʵ��ʱ)/6)
//	int nGene = ((nDay-1)*24+nHour)/6;
//	// ��Ϸ��=INT(((ʵ����-Ԫ��)*12+Ԫ��-3)/3)
//	m_nGameYear = ((nYear-m_nStartRealYear)*12+m_nStartRealMonth-3)/3;
//	// ��Ϸ��=MOD((ʵ����-1)*4+INT(����/31),12)+1
//	m_nGameMonth = ((nMonth-1)*4+nGene/31)%12+1;
//	// ��Ϸ��=MOD(����,31)+1
//	m_nGameDay = nGene%31+1;
//	// ��Ϸʱ��=MOD(INT(((ʵ��ʱ+1)*60+ʵ�ʷ�)/30)-2,12)+1
//	m_nGameHour = ((((nHour+1)*60+nMinute)/30)-2)%12+1;
//	// ��Ϸ��=MOD(INT(ʵ�ʷ�/15*4),8)+1
//	m_nGameMinute = (nMinute*4/15)%8+1;
//
//	// ��Ϸʱ��ű�
//	BYTE byYear = m_nGameYear - 2000;
//	BYTE byMonth = m_nGameMonth;
//	BYTE byDay = m_nGameDay;
//	BYTE byHour = m_nGameHour;
//	BYTE byMinute = m_nGameMinute;
//	GetScriptMgr()->RunTimeScript( ST_GAME_TIME, byYear, byMonth, byDay, byHour, byMinute );
//	
//	MsgChat chat;
//	char szBuf[128];
//	sprintf( szBuf, "%d��%d��%d��%dʱ%d��",
//				m_nGameYear,
//				m_nGameMonth,
//				m_nGameDay,
//				m_nGameHour,
//				m_nGameMinute );
//	chat.SetString( szBuf );	
//	GettheServer().SendMsgToWorld( &chat );
//}

void CGameWorldTimer::UpdateTimeToClient( BaseCharacter* pChar )
{
	MsgUpdateTime msg;
	HelperFunc::SafeNCpy( msg.szYearName, m_strGameYear.c_str(), MsgUpdateTime::YEAR_NAME_LENGTH );
	msg.stYear = m_nCurGameYear;
	msg.stMonth = m_nGameMonth;
	msg.stDay = m_nGameDay;
	msg.stHour = m_nGameHour;
	msg.stMinute = m_nGameMinute;
	if ( pChar != NULL )
	{
		msg.header.uMsgLevel = level_high;
		GettheServer().SendMsgToSingle( &msg, pChar );
	}
	else
	{
		msg.header.uMsgLevel = level_low;
		GettheServer().SendMsgToWorld( &msg );
	}
}

void CGameWorldTimer::Run()
{
	// ToLog( m_bInit );
	static DWORD dwLastTime = 0;
	const int nRate = 60000/m_nRate;
	if ( HQ_TimeGetTime() - dwLastTime < nRate )
		return;
	dwLastTime = HQ_TimeGetTime();
	//
	if ( ++m_nGameMinute >= 60 )
	{
		m_nGameMinute = 0;
		m_nGameHour++;
	}
	if ( m_nGameHour >= 24 )
	{
		m_nGameHour = 0;
		m_nGameDay++;
	}
	if ( m_nGameDay > 30 )
	{
		m_nGameDay = 1;
		m_nGameMonth++;
	}
	if ( m_nGameMonth > 12 )
	{
		m_nGameMonth = 1;
		m_nGameYear++;
		m_nCurGameYear++;
	}
	// ��Ϸʱ��ű�,��Ϸʱ��ÿСʱ����һ��
	if ( m_nGameMinute == 0 )
	{
		BYTE byYear = m_nGameYear;
		BYTE byMonth = m_nGameMonth;
		BYTE byDay = m_nGameDay;
		BYTE byHour = m_nGameHour;
		BYTE byMinute = m_nGameMinute;
		GetScriptMgr()->RunTimeScript( ST_GAME_TIME, byYear, byMonth, byDay, byHour, byMinute );
		// Ϊ�ͻ��˸���ʱ��
		UpdateTimeToClient( NULL );
		// ����ʱ��
		g_Cfg.m_nYear = m_nGameYear;
		g_Cfg.m_nMonth = m_nGameMonth;
		g_Cfg.m_nDay = m_nGameDay;
		g_Cfg.m_nHour = m_nGameHour;
		g_Cfg.m_nMinute = m_nGameMinute;
		HelperFunc::SafeNCpy( g_Cfg.m_szYearName, m_strGameYear.c_str(), sizeof( g_Cfg.m_szYearName ) );
		g_Cfg.m_nGameYear = m_nCurGameYear;
		// g_Cfg.Save();
	}

	////
	//// �ַ���
	//// HeroԪ��һ��һ����ʱһ��
	//char szBuf[128];
	//m_strGameTime = m_strGameYear;	// Hero
	//if ( m_nGameYear == 1 )	m_strGameTime += "Ԫ";
	//else					m_strGameTime += itoa( m_nGameYear, szBuf, 10 );
	//m_strGameTime += "��";		// ��
	//m_strGameTime += itoa( m_nGameMonth, szBuf, 10 );	// 1
	//m_strGameTime += "��";		// ��
	//m_strGameTime += itoa( m_nGameDay, szBuf, 10 );	// 1
	//m_strGameTime += "��";		// ��
	//// �ӡ�������î�������ȡ��硢δ���ꡢ�ϡ��硢��
	//switch( m_nGameHour/2 )
	//{
	//case 0:	m_strGameTime += "��";	break;
	//case 1:	m_strGameTime += "��";	break;
	//case 2:	m_strGameTime += "��";	break;
	//case 3:	m_strGameTime += "î";	break;
	//case 4:	m_strGameTime += "��";	break;
	//case 5:	m_strGameTime += "��";	break;
	//case 6:	m_strGameTime += "��";	break;
	//case 7:	m_strGameTime += "δ";	break;
	//case 8:	m_strGameTime += "��";	break;
	//case 9:	m_strGameTime += "��";	break;
	//case 10:m_strGameTime += "��";	break;
	//case 11:m_strGameTime += "��";	break;
	//default:	// ToLog(false);	break;
	//}
	//m_strGameTime += "ʱ";		// ʱ
	//m_strGameTime += itoa( (m_nGameMinute/15), szBuf, 10 );	// 0
	//m_strGameTime += "��";		// ��
}

int CGameWorldTimer::GetGameTime( ETimeType type )
{
	switch( type ) 
	{
	case eYear:
		return m_nGameYear;
	case eMonth:
		return m_nGameMonth;
	case eDay:
		return m_nGameDay;
	case eHour:
		return m_nGameHour;
	case eMinute:
		return m_nGameMinute;
	default:
		{
			GetErrorLog()->logString("Failed: CGameWorldTimer::GetGameTime()");
		}
		break;
	}
	return 0;
}

int CGameWorldTimer::GetRealTime( ETimeType type )
{
	time_t t = time( NULL );
	std::tm *tme = localtime( &t );
	switch( type ) 
	{
	case eYear:
		return tme->tm_year + 1900;
	case eMonth:
		return tme->tm_mon + 1;
	case eWeek:
		return tme->tm_wday;
	case eDay:
		return tme->tm_mday;
	case eHour:
		return tme->tm_hour;
	case eMinute:
		return tme->tm_min;
	default:
		{	
		}
		break;
	}
	return 0;
}

