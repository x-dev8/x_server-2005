#pragma once
#include <string>

//#define GAME_WORLD_TIME_UPDATE_RATE		(4*60000)		// ÿ4����ˢһ��
class C_Character;

class CGameWorldTimer
{
public:
	enum ETimeType
	{
		eYear = 0,		// ��
		eMonth,			// ��
		eWeek,			// ����
		eDay,			// ��
		eHour,			// ʱ
		eMinute,		// ��
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
	int		m_nGameYear;		// ��
	int		m_nGameMonth;		// ��
	int		m_nGameDay;			// ��
	int		m_nGameHour;		// ʱ
	int		m_nGameMinute;		// ��(����Ϊ��)
	int		m_nRate;			// ��Ϸ��������ʵ����ļ�����
	std::string m_strGameYear;
	int		m_nCurGameYear;		// ��ǰ����Ϸ��
	bool	m_bInit;

public:
	CGameWorldTimer(void);
	~CGameWorldTimer(void);
};

CGameWorldTimer* GetGameWorldTimer();