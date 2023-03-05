#pragma once

#include "AniFunctor.h"
#include "MeUi/UiRender.h"
#include "MeUi/UiPicture.h"


class CSmartAnimation 
    {
public:
    enum EFunctorType
    {
        EFunctorType_X = 0 ,
        EFunctorType_Y,
        EFunctorType_Width,
        EFunctorType_Height,
        EFunctorType_SrcX,
        EFunctorType_SrcY,
        EFunctorType_SrcWidth,
        EFunctorType_SrcHeight,
        EFunctorType_Alpha,
        EFunctorType_Fade,
        EFunctorType_Total,
    };
	CSmartAnimation(UiRender* pRenderCurrFrame);
	~CSmartAnimation(void);

    bool Initialize(MeXmlElement* pElement);
    virtual bool Update(DWORD tickCount);
	virtual bool Redraw(DWORD tickCount);
    bool  StartAnimation(DWORD nTimeTick,DWORD nDeltaTick,bool bRepeat);
    bool  StartAnimation(DWORD nTimeTick,DWORD nDeltaTick);

    void    SetStartTick(DWORD nTime)
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
		m_nOffsetTime = 0;
        m_nTotalTime = 0;
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

	void    SetUiPicture(LPDIRECT3DTEXTURE9 pd3dTexture );
	LPDIRECT3DTEXTURE9 GetD3DTexture() const { return m_pd3dTexture; }


    void        SetWorkingArea(RECT& RectPara)
    {
        m_workingArea = RectPara;
        m_bWorkingAreaEnable = true;
    }
    virtual void        InitializeFunctor(EFunctorType eType, float fBaseValue, CAnimationFunctorBase* pFunctor)
    {
        mFunctor[eType].mBaseValue = fBaseValue;
        mFunctor[eType].m_pFunctor = pFunctor;
    }
	CAnimationFunctorBase*	GetFunctorType(int nFunctorType) const { return mFunctor[nFunctorType].m_pFunctor; }
    DWORD        GetTotalTime()
    {
        return m_nTotalTime;
    }
protected:
    typedef struct SAnimationCalculate 
    {
        float               mBaseValue;
        CAnimationFunctorBase*   m_pFunctor;
        DWORD Calculate(DWORD nTimeTick)
        {
            float fRet = 0;
            if (NULL == m_pFunctor)
            {
                fRet = mBaseValue;
            }
            else
                fRet = mBaseValue + m_pFunctor->Calculate(nTimeTick);
            return (int)floor(fRet);
        }
        SAnimationCalculate()
            :mBaseValue(0)
            ,m_pFunctor(NULL)
        {

        }
    }SAnimationCalculate;
    void        Slice(MeRect& BGRect,MeRect& SrcRect);
    protected:
    DWORD m_nTotalTime;   
    SAnimationCalculate     mFunctor[EFunctorType_Total];
    bool            m_bRepeat;

	int		m_nQuadId;
	LPDIRECT3DTEXTURE9 	m_pd3dTexture;
	RECT            m_workingArea;

    RECT            m_DesRect;
    RECT            m_SrcRect;
    int32			m_nAlpha;
    DWORD			m_nStartTick;
	DWORD			m_nOffsetTime;
    bool			m_bStop;
    bool            m_bWorkingAreaEnable;
    UiRender*       m_pRender;

};
class ControlFrame;
class CSmartAniManage 
    {
    public:
        CSmartAniManage(ControlFrame*		pFrame){m_pFrame = pFrame;}
        ~CSmartAniManage(){}

    public:
        bool AddAnimation(CSmartAnimation* pAnimation);
        virtual bool Update(DWORD tickCount);
        void StopAnimation(CSmartAnimation* pAnimation);
        void StopAllAnimation();
        ControlFrame* GetFrame() { return m_pFrame; }

    protected:
        typedef std::list<CSmartAnimation*> AnimationList;

    protected:
        AnimationList m_listAnimations;
		ControlFrame*		m_pFrame;
    };


