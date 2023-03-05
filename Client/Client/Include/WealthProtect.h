//======================================================================
//
//	财产保护，玩家进入游戏后，有段财产保护时间；
//	在该时间内，禁止执行与财产有关的操作；
//
//	从CPlayerRole里移出作为单件使用
//======================================================================
#pragma once

class CWealthProtect
{
public:
	CWealthProtect(void);
	virtual ~CWealthProtect(void) {}

	static CWealthProtect&	Instance()
	{
		static CWealthProtect xWealthProtect;
		return xWealthProtect;
	}

	// 当前是否在财产保护时间内
	bool    			IsInProtectTime(bool bShowMsg = true);

	// 获取财产保护持续时间（分钟）
	short				GetProtectTime()			{ return m_shProtectTime; }

	// 设置财产保护持续时间（分钟）
	void    			SetProtectTime(short time)	{ if(time >= 0) m_shProtectTime = time; }

	// 获取财产保护结束时间（毫秒）
	unsigned int		GetProtectEndingTime()		{ return m_dwProtectEndingTime; }

	// 初始化财产保护结束时间
	void    			InitProtectEndingTime(unsigned int curTime);

	// 清除财产保护结束时间
	void    			ClearProtectEndintTime()	{m_dwProtectEndingTime = 0;}

	// 切地图时设置是否第一次进入游戏
	void    			SetFirstEnterMap(bool bFlag){ m_bFirstEnterMap = bFlag; }

	// 当前是否第一次进游戏
	bool    			IsFirstEnterMap()			{ return m_bFirstEnterMap; }

private:
	// 财产保护时间（分钟）
	short   			m_shProtectTime;

	// 财产保护结束时间（毫秒）
	unsigned int		m_dwProtectEndingTime;

	// 当前切地图是否第一次进游戏
	bool    			m_bFirstEnterMap;
};