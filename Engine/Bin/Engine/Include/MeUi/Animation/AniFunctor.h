#pragma once
#include "RapidXml/MeRapidXml.h"
#include "MeRTLibs.h"
//--------------------------------------------------------------------------
// Represents a rectangle in a 2D coordinate system (integer coordinates)
//--------------------------------------------------------------------------

class MeRect
{
public:

	MeRect()
	{
		X = Y = Width = Height = 0;
	}

	MeRect(IN INT x,
		IN INT y,
		IN INT width,
		IN INT height)
	{
		X = x;
		Y = y;
		Width = width;
		Height = height;
	}


	MeRect* Clone() const
	{
		return new MeRect(X, Y, Width, Height);
	}


	VOID GetBounds(OUT MeRect* rect) const
	{
		rect->X = X;
		rect->Y = Y;
		rect->Width = Width;
		rect->Height = Height;
	}

	INT GetLeft() const
	{
		return X;
	}

	INT GetTop() const
	{
		return Y;
	}

	INT GetRight() const
	{
		return X+Width;
	}

	INT GetBottom() const
	{
		return Y+Height;
	}

	BOOL IsEmptyArea() const
	{
		return (Width <= 0) || (Height <= 0);
	}

	BOOL Equals(IN const MeRect & rect) const
	{
		return X == rect.X &&
			Y == rect.Y &&
			Width == rect.Width &&
			Height == rect.Height;
	}

	BOOL Contains(IN INT x,
		IN INT y) const
	{
		return x >= X && x < X+Width &&
			y >= Y && y < Y+Height;
	}


	BOOL Contains(IN MeRect& rect) const
	{
		return (X <= rect.X) && (rect.GetRight() <= GetRight()) &&
			(Y <= rect.Y) && (rect.GetBottom() <= GetBottom());
	}

	VOID Inflate(IN INT dx,
		IN INT dy)
	{
		X -= dx;
		Y -= dy;
		Width += 2*dx;
		Height += 2*dy;
	}


	BOOL Intersect(IN const MeRect& rect)
	{
		return Intersect(*this, *this, rect);
	}

	static BOOL Intersect(OUT MeRect& c,
		IN const MeRect& a,
		IN const MeRect& b)
	{
		INT right = min(a.GetRight(), b.GetRight());
		INT bottom = min(a.GetBottom(), b.GetBottom());
		INT left = max(a.GetLeft(), b.GetLeft());
		INT top = max(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	BOOL IntersectsWith(IN const MeRect& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
			GetTop() < rect.GetBottom() &&
			GetRight() > rect.GetLeft() &&
			GetBottom() > rect.GetTop());
	}

	static BOOL Union(OUT MeRect& c,
		IN const MeRect& a,
		IN const MeRect& b)
	{
		INT right = max(a.GetRight(), b.GetRight());
		INT bottom = max(a.GetBottom(), b.GetBottom());
		INT left = min(a.GetLeft(), b.GetLeft());
		INT top = min(a.GetTop(), b.GetTop());

		c.X = left;
		c.Y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	VOID Offset(IN INT dx,
		IN INT dy)
	{
		X += dx;
		Y += dy;
	}

public:

	INT X;
	INT Y;
	INT Width;
	INT Height;
};


    class CAnimationFunctorBase
    {
    public:
        CAnimationFunctorBase()
            :m_nStartTime(0)
            ,m_nTotalTime(0)
        {
        }
        virtual float Calculate(int32 nTimeTick) = 0;
        virtual void  InitializeParam(MeXmlElement* pElement);  

        void    SetTotalTime(int32 nTime)
        {
            m_nTotalTime = nTime;
        }
        int32    GetTotalTime()
        {
            return m_nTotalTime;
        }
        void    SetStartTime(int32 nTime)
        {
            m_nStartTime = nTime;
        }
        int32    GetStartTime()
        {
            return m_nStartTime;
        }

    protected:
        int32 m_nTotalTime;   
        int32 m_nStartTime;   
    };

    class CConstFunctor : public CAnimationFunctorBase
    {
    public:
        CConstFunctor(void)
            :mfA(0)
        {
        }
        virtual float Calculate(int32 nDeltaTime)
        {
            return mfA;
        }
        virtual void  InitializeParam(MeXmlElement* pElement);
        void            SetParamA(float fParam)
        {
            mfA = fParam;
        }
    protected:
        //X = A
        float             mfA;
    };
    class CLinearFunctor : public CConstFunctor
	{
	public:
		CLinearFunctor(void)
		{
		}

        virtual float Calculate(int32 nDeltaTime);
        virtual void  InitializeParam(MeXmlElement* pElement);  
        void        Initialize(float fStart,float fSpeed,int32 nTime )
        {
            mfA = fStart;
            mfB = fSpeed;
            SetTotalTime(nTime);
        }
        void        InitializeBySpeed(float fStart,float fSpeed,float fEnd )
        {
            mfA = fStart;
            mfB = fSpeed;
            if (abs(fEnd - fStart) > 0 && abs(fSpeed) > 0)
            {
                SetTotalTime((fEnd - fStart)/fSpeed);
            }
            else
                SetTotalTime(0);
        }
        void    InitializeByTime(float fStart,int32 nTime,float fEnd )
        {
            mfA = fStart;
            SetTotalTime(nTime);

            if (abs(nTime) > 0 )
            {
                mfB = (fEnd - fStart)/ nTime;
            }
            else
                mfB = 0;
        }
		~CLinearFunctor()
		{
		}

        void            SetParamB(float fParam)
        {
            mfB = fParam;
        }
    protected:
        //X = A + BT
        float   mfB;
	};

    class CQuadraticFunctor : public CLinearFunctor
    {
    public:
        virtual float Calculate(int32 nDeltaTime);
        virtual void  InitializeParam(MeXmlElement* pElement);  
        void        Initialize(float fStart,float fSpeed,float fAcc,int32 nTime)
        {
            mfA = fStart;
            mfB = fSpeed;
            mfC = fAcc;
            SetTotalTime(nTime);
        }
        void       InitializeByEnd(float fStart,float fSpeed,float fAcc, float fEnd);
        void            SetParamC(float fParam)
        {
            mfC = fParam;
        }
    protected:
        //X = A + BT + CT2
        float   mfC;
    private:
    };


    class CSinFunctor : public CQuadraticFunctor
    {
    public:
        virtual float Calculate(int32 nDeltaTime);
        virtual void  InitializeParam(MeXmlElement* pElement);  
        void        Initialize(float fA,float fB,float fC,float fD, int32 nTime );
    protected:
        //X = A*Sin(BT + C) + D
        float   mfD;
    private:
    };

    class CIntervalFunctor: public CQuadraticFunctor
    {
    public:
        virtual float Calculate(int32 nDeltaTime);
    protected:
        //X = A + B* T/C
    private:
    };

    class CRandomIntervalFunctor: public CIntervalFunctor
    {
    public:
        virtual float Calculate(int32 nDeltaTime);
    private:
        //X = A + B* Randome() % C
    };

    class CSegmentFunctor: public CAnimationFunctorBase
    {
    public:
        virtual float Calculate(int32 nDeltaTime);
        virtual void  InitializeParam(MeXmlElement* pElement);  
		void AddAnimationFunctor(CAnimationFunctorBase* pAniFun); 
		void ClearFunctor(); 

    protected:
        std::vector<CAnimationFunctorBase*>         m_arrAniFunctor;
    private:
    };


    class CFunctorMaker
    {
    public:
        ~CFunctorMaker();
        static CFunctorMaker*	GetInstance();
        CAnimationFunctorBase*	CreateFunctor(MeXmlElement* pElement);
		CAnimationFunctorBase*	CreateFunctor(const char* pElementType);
		void					DestoryFunctor(CAnimationFunctorBase* pFunctor);
    protected:
        CFunctorMaker(){}
        
    private:
        std::list<CAnimationFunctorBase*>      m_arrFunctor;
    };
