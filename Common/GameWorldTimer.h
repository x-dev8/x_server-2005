#pragma once
#include <string>

//#define GAME_WORLD_TIME_UPDATE_RATE		(4*60000)		// 每4分钟刷一次
class C_Character;

class CGameWorldTimer
{
public:
	enum ETimeType
	{
		eYear = 0,		// 年
		eMonth,			// 月
		eWeek,			// 星期
		eDay,			// 日
		eHour,			// 时
		eMinute,		// 分
	};

public:
	bool	Init( int year, int month, int day, int hour, int minute,
				int rate, const char* szYear, int nGameYear );
	void	Run();

	int		GetGameTime( ETimeType type );
	int		GetRealTime( ETimeType type );

	const char* GetYearName(){ return m_strGameYear.c_str(); }
	int		GetCurGameYear(){ return m_nCurGameYear; }
	void	UpdateTimeToClient( C_Character* pChar );

private:
	int		m_nGameYear;		// 年
	int		m_nGameMonth;		// 月
	int		m_nGameDay;			// 日
	int		m_nGameHour;		// 时
	int		m_nGameMinute;		// 分(现在为刻)
	int		m_nRate;			// 游戏世界是真实世界的几倍快
	std::string m_strGameYear;
	int		m_nCurGameYear;		// 当前的游戏年
	bool	m_bInit;

public:
	CGameWorldTimer(void);
	~CGameWorldTimer(void);
};

CGameWorldTimer* GetGameWorldTimer();