/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwPublicFunc.h
* Create: 	10/06/06
* Desc:		һЩͨ�ú���
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWPUBLICFUNC_H__
#define __SWPUBLICFUNC_H__

#include <string>
#define NI_HALF_PI  1.5707963267948966f
// #ifndef PI
// #define PI 3.141592653589793f
// #endif
#include "Me3d/MathEx.h"
namespace SwPublicFunc
{
	// pChar�Ƿ���pEnd��β����Ҫ�����ж��ļ�����չ��
	// ע�⣺�ú������Դ�Сд
	bool IsEndof( const char* pChar, const char* pEnd );

	int  TChar2MutiChar( LPSTR outChar, int outSize, LPCTSTR inChar, int inSize );

	void RotationArc( Quaternion& quat, const Vector& pUnitFrom, const Vector& pUnitTo );

	void CullBaseDir( TCHAR* pszBuffer );

	int  String2WString(std::wstring& _dsc, const std::string& _src);
	int  WString2String(std::string& _dsc, const std::wstring& _src);

	bool IsFileExist(const char* filename);
	void			GetAlphaData( uInt8 * alphaData, uInt8 * kAlphaMap );

	//Path�Ĳ���
	std::string GetFileName( const std::string& strFilePath);			//���ļ���·�������ȡ�ļ���

	Vector			Spherical2Cartesian(Vector kSpherical);		// ��������ת���ɵѿ�������
	Vector			Cartesian2Spherical(Vector kCartesian);		// �ѿ�������ת������������

	template< class T > inline void Exchange(T& A, T& B)
	{
		const T Temp = A;
		A = B;
		B = Temp;
	}

	float NiFastATan2(float fY, float fX);

	inline float NiACos (float fValue)
	{
		if ( -1.0f < fValue )
		{
			if ( fValue < 1.0f )
				return float(acos(fValue));
			else
				return 0.0f;
		}
		else
		{
			return PI;
		}
	}
	//---------------------------------------------------------------------------
	inline float NiASin (float fValue)
	{
		if ( -1.0f < fValue )
		{
			if ( fValue < 1.0f )
				return float(asin(fValue));
			else
				return NI_HALF_PI;
		}
		else
		{
			return -NI_HALF_PI;
		}
	}
};

// ͨ�ú�
#ifndef SAFE_DELETE
#define SAFE_DELETE( p )				{ if( p ){ delete (p); (p) = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( p )			{ if( p ) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( p )				{ if( p ) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef SAFE_DESTROY
#define SAFE_DESTROY( p )				{ if( p ){ (p)->Destroy(); } }
#endif

#ifndef SAFE_DESTROY_AND_DELETE
#define SAFE_DESTROY_AND_DELETE( p )	{ if( p ){ (p)->Destroy(); delete (p); (p) = NULL; } }
#endif

#ifndef ASSERT_NULL
#define ASSERT_NULL( p )				{ Assert( ( p ) == NULL ); }
#endif

#ifndef ASSERT_NOTNULL
#define ASSERT_NOTNULL( p )				{ Assert( ( p ) != NULL ); }
#endif

#endif	// __SWPUBLICFUNC_H__
