//======================================================================
//
//	�Ʋ���������ҽ�����Ϸ���жβƲ�����ʱ�䣻
//	�ڸ�ʱ���ڣ���ִֹ����Ʋ��йصĲ�����
//
//	��CPlayerRole���Ƴ���Ϊ����ʹ��
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

	// ��ǰ�Ƿ��ڲƲ�����ʱ����
	bool    			IsInProtectTime(bool bShowMsg = true);

	// ��ȡ�Ʋ���������ʱ�䣨���ӣ�
	short				GetProtectTime()			{ return m_shProtectTime; }

	// ���òƲ���������ʱ�䣨���ӣ�
	void    			SetProtectTime(short time)	{ if(time >= 0) m_shProtectTime = time; }

	// ��ȡ�Ʋ���������ʱ�䣨���룩
	unsigned int		GetProtectEndingTime()		{ return m_dwProtectEndingTime; }

	// ��ʼ���Ʋ���������ʱ��
	void    			InitProtectEndingTime(unsigned int curTime);

	// ����Ʋ���������ʱ��
	void    			ClearProtectEndintTime()	{m_dwProtectEndingTime = 0;}

	// �е�ͼʱ�����Ƿ��һ�ν�����Ϸ
	void    			SetFirstEnterMap(bool bFlag){ m_bFirstEnterMap = bFlag; }

	// ��ǰ�Ƿ��һ�ν���Ϸ
	bool    			IsFirstEnterMap()			{ return m_bFirstEnterMap; }

private:
	// �Ʋ�����ʱ�䣨���ӣ�
	short   			m_shProtectTime;

	// �Ʋ���������ʱ�䣨���룩
	unsigned int		m_dwProtectEndingTime;

	// ��ǰ�е�ͼ�Ƿ��һ�ν���Ϸ
	bool    			m_bFirstEnterMap;
};