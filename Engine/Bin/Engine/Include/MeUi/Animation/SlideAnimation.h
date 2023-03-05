#pragma once

#include "MeUi/UiPicture.h"
#include "RapidXml/MeRapidXml.h"
class CSlideAnimation 
    {
public:
	CSlideAnimation(void);
	~CSlideAnimation(void);

    bool Initialize(MeXmlElement* pElement);
	bool Initialize(char* pBaseName,int nTotalFrame,RECT& DesRect,int nTotalTime);
    bool StartAnimation(DWORD nTimeTick,bool bRepeat);
    bool StartAnimation(DWORD nTimeTick);
	bool Update(DWORD tickCount,RECT* pDesRect = NULL);
	void UnRelativePicResource();



	void SetBaseName(const char* val) { m_baseName = val; }

    void    SetStartTick(int32 nTime)
    {
        m_nStartTick = nTime;
    }
    void    SetRepeat(bool bFlag)
    {
        m_bRepeat = bFlag;
    }

    void StopAnimation()
	{
        m_bStop = true;
        m_nStartTick = 0;
	}

    bool    IsInAnimation()
    {
        return !m_bStop;
    }

public:
    void    SetQuadId(	int quadIndex)
    {
        m_nQuadId = (quadIndex);
    }

	int32 GetTotalPicNumber() const { return m_nTotalPicNumber; }
	void SetTotalPicNumber(int32 val) { m_nTotalPicNumber = val; }

    int32        GetTotalTime()
    {
        return m_nTotalTime;
    }
protected:
    int32			m_nTotalTime;   
    bool            m_bRepeat;

	int				m_nQuadId;

    RECT            m_DesRect;
    int32			m_nAlpha;
    int32			m_nStartTick;
	int32			m_nTotalPicNumber;
	bool			m_bStop;
	std::string			m_baseName;
};

