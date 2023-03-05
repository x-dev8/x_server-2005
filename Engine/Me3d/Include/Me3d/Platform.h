
#ifndef _platform_h
#define _platform_h

#include <MeRTLibs.h>
#include <Dxsdk/D3D9.h>
#include <Dxsdk/d3dx9.h>
#include <MeFoundation/MeFoundationLibType.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>

//#define MeMatrix	D3DXMATRIX

//#define MeMatrix __declspec(align(16)) _Matrix
class Vector;
class Vector4;
class MeMatrix : public MeCommonAllocObj<MeMatrix>
{
public:
	float m[4][4];

public:
	inline MeMatrix operator*( float fScalar ) const
	{	
		static MeMatrix result;
		result.m[0][0] = m[0][0] * fScalar;
		result.m[0][1] = m[0][1] * fScalar;
		result.m[0][2] = m[0][2] * fScalar;
		result.m[0][3] = m[0][3] * fScalar;
		result.m[1][0] = m[1][0] * fScalar;
		result.m[1][1] = m[1][1] * fScalar;
		result.m[1][2] = m[1][2] * fScalar;
		result.m[1][3] = m[1][3] * fScalar;
		result.m[2][0] = m[2][0] * fScalar;
		result.m[2][1] = m[2][1] * fScalar;
		result.m[2][2] = m[2][2] * fScalar;
		result.m[2][3] = m[2][3] * fScalar;
		result.m[3][0] = m[3][0] * fScalar;
		result.m[3][1] = m[3][1] * fScalar;
		result.m[3][2] = m[3][2] * fScalar;
		result.m[3][3] = m[3][3] * fScalar;
		return result;
	}

	inline MeMatrix& operator*=( float fScalar )
	{	
		m[0][0] *= fScalar;
		m[0][1] *= fScalar;
		m[0][2] *= fScalar;
		m[0][3] *= fScalar;
		m[1][0] *= fScalar;
		m[1][1] *= fScalar;
		m[1][2] *= fScalar;
		m[1][3] *= fScalar;
		m[2][0] *= fScalar;
		m[2][1] *= fScalar;
		m[2][2] *= fScalar;
		m[2][3] *= fScalar;
		m[3][0] *= fScalar;
		m[3][1] *= fScalar;
		m[3][2] *= fScalar;
		m[3][3] *= fScalar;
		return *this;
	}

	inline MeMatrix operator+( const MeMatrix& mat ) const
	{	
		static MeMatrix result;
		result.m[0][0] = m[0][0] + mat.m[0][0];
		result.m[0][1] = m[0][1] + mat.m[0][1];
		result.m[0][2] = m[0][2] + mat.m[0][2];
		result.m[0][3] = m[0][3] + mat.m[0][3];
		result.m[1][0] = m[1][0] + mat.m[1][0];
		result.m[1][1] = m[1][1] + mat.m[1][1];
		result.m[1][2] = m[1][2] + mat.m[1][2];
		result.m[1][3] = m[1][3] + mat.m[1][3];
		result.m[2][0] = m[2][0] + mat.m[2][0];
		result.m[2][1] = m[2][1] + mat.m[2][1];
		result.m[2][2] = m[2][2] + mat.m[2][2];
		result.m[2][3] = m[2][3] + mat.m[2][3];
		result.m[3][0] = m[3][0] + mat.m[3][0];
		result.m[3][1] = m[3][1] + mat.m[3][1];
		result.m[3][2] = m[3][2] + mat.m[3][2];
		result.m[3][3] = m[3][3] + mat.m[3][3];
		return result;
	}

	inline MeMatrix& operator+=( const MeMatrix& mat ) 
	{	
		m[0][0] += mat.m[0][0];
		m[0][1] += mat.m[0][1];
		m[0][2] += mat.m[0][2];
		m[0][3] += mat.m[0][3];
		m[1][0] += mat.m[1][0];
		m[1][1] += mat.m[1][1];
		m[1][2] += mat.m[1][2];
		m[1][3] += mat.m[1][3];
		m[2][0] += mat.m[2][0];
		m[2][1] += mat.m[2][1];
		m[2][2] += mat.m[2][2];
		m[2][3] += mat.m[2][3];
		m[3][0] += mat.m[3][0];
		m[3][1] += mat.m[3][1];
		m[3][2] += mat.m[3][2];
		m[3][3] += mat.m[3][3];
		return *this;
	}

	inline MeMatrix concatenate(const MeMatrix &m2) const
	{
		MeMatrix r;
		r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
		r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
		r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
		r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

		r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
		r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
		r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
		r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

		r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
		r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
		r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
		r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

		r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
		r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
		r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
		r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

		return r;
	}

	/** Matrix concatenation using '*'.
	*/
	inline MeMatrix operator * ( const MeMatrix &m2 ) const
	{
		return concatenate( m2 );
	}

	inline Vector4 operator * (const Vector4& v) const;
};

//#define MeMatrix __declspec(align(16)) _Matrix
//
//typedef MeMatrix *LPMatrix;
//
//typedef __declspec(align(16)) _Matrix MeMatrix, *LPMatrix;

//typedef __declspec(align(16)) _Matrix MeMatrix;

//typedef D3DXMATRIXA16 MeMatrix;
//#define MeMatrix D3DXMATRIXA16


//****************************************************************************//
// Defines Win32                                                              //
//****************************************************************************//

/*#ifdef _WIN32

#pragma warning(disable : 4251)
#pragma warning(disable : 4786)
  



#ifdef EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

#endif*/
#define ENGINEAPI
//****************************************************************************//
// Defines Linux and Cygwin                                                   //
//****************************************************************************//

#if defined(__linux__) || (__CYGWIN__)

#define ENGINEAPI

#endif

ENGINEAPI extern DWORD GPhysicalMemory;
ENGINEAPI extern DOUBLE GSecondsPerCycle;
//API extern DOUBLE GSecondsPerCycle;
ENGINEAPI extern DWORD GPageSize;
ENGINEAPI extern DWORD GProcessorCount;

enum
{
	eMemory_Low,
	eMemory_High
};
//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The platform class.
  *****************************************************************************/

class ENGINEAPI Platform
{
// constructors/destructor
public:
	Platform();
	virtual ~Platform();
	
public:
	VOID Init();
	DWORD GetPhysicalMemory()	{ return GPhysicalMemory; }

	BYTE	GetMemoryLvl()		{ return MemoryLvl; }
// member functions	
public:
	BYTE	MemoryLvl;
};

Platform *GetPlatform();

#endif