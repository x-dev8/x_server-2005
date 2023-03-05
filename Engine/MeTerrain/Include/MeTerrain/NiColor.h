
#ifndef NICOLOR_H
#define NICOLOR_H


class NiColorA;

class  NiColor 
{
public:
    float r, g, b;

    inline NiColor (float fR = 0.0f, float fG = 0.0f, float fB = 0.0f);

    inline NiColor& operator= (float fScalar);
    inline bool operator== (const NiColor& c) const;
    inline bool operator!= (const NiColor& c) const;

    inline NiColor operator+ (const NiColor& c) const;
    inline NiColor operator- (const NiColor& c) const;
    inline NiColor operator* (float fScalar) const;
    inline NiColor operator* (const NiColor& c) const;
    inline NiColor operator/ (float fScalar) const;
    inline NiColor operator/ (const NiColor& c) const;
    inline NiColor operator- () const;
     friend NiColor operator* (float fScalar, const NiColor& c);

    inline NiColor& operator+= (const NiColor& c);
    inline NiColor& operator-= (const NiColor& c);
    inline NiColor& operator*= (float fScalar);
    inline NiColor& operator*= (const NiColor& c);
    inline NiColor& operator/= (float fScalar);
    inline NiColor& operator/= (const NiColor& c);

    // map to unit cube
    inline void Clamp();
    inline void Scale();


    static const NiColor WHITE; // (1,1,1) 
    static const NiColor BLACK; // (0,0,0) 

};

class  NiColorA 
{
public:
    float r, g, b, a;

    inline NiColorA (float fR = 0.0f, float fG = 0.0f, 
              float fB = 0.0f, float fA = 0.0f);

    inline NiColorA& operator= (float fScalar);
    inline bool operator== (const NiColorA& c) const;
    inline bool operator!= (const NiColorA& c) const;

    inline NiColorA operator+ (const NiColorA& c) const;
    inline NiColorA operator- (const NiColorA& c) const;
    inline NiColorA operator* (float fScalar) const;
    inline NiColorA operator* (const NiColorA& c) const;
    inline NiColorA operator/ (float fScalar) const;
    inline NiColorA operator/ (const NiColorA& c) const;
    inline NiColorA operator- () const;
     friend NiColorA operator* (float fScalar, const NiColorA& c);

    inline NiColorA& operator+= (const NiColorA& c);
    inline NiColorA& operator-= (const NiColorA& c);
    inline NiColorA& operator*= (float fScalar);
    inline NiColorA& operator*= (const NiColorA& c);
    inline NiColorA& operator/= (float fScalar);
    inline NiColorA& operator/= (const NiColorA& c);

    // map (r,g,b,a) to unit hypercube
    inline void Clamp();
    inline void Scale();


    static const NiColorA WHITE;  // (1,1,1,1) 
    static const NiColorA BLACK;  // (0,0,0,1) 

} ;

class NiColorB	// BYTE
{
public:
	BYTE a, r, g, b;

	DWORD& DWColor(void) {return *((DWORD*)this);}
	const DWORD& DWColor(void) const {return *((DWORD*)this);}

	// Constructors.
	NiColorB(): a(255), r(0), g(0), b(0) {}
	NiColorB( BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255 )
		:	a(InA), r(InR), g(InG), b(InB) {}
	NiColorB( const NiColorB &C )
		:	a(C.a),	r(C.r),	g(C.g),	b(C.b) {}

	explicit NiColorB( DWORD InColor )
	{ DWColor() = InColor; }

	// Operators.
	BOOL operator==( const NiColorB &C ) const
	{
		return DWColor() == C.DWColor();
	}
	BOOL operator!=( const NiColorB& C ) const
	{
		return DWColor() != C.DWColor();
	}
	void operator+=(const NiColorB& C)
	{
		r = (BYTE) min((INT) r + (INT) C.r,255);
		g = (BYTE) min((INT) g + (INT) C.g,255);
		b = (BYTE) min((INT) b + (INT) C.b,255);
		a = (BYTE) min((INT) a + (INT) C.a,255);
	}
	void operator=( const NiColorB &C )
	{
		a = C.a;
		r = C.r;
		g = C.g;
		b = C.b;
	}
};


//---------------------------------------------------------------------------
//  Inline include
#include "NiColor.inl"

//---------------------------------------------------------------------------

#endif
