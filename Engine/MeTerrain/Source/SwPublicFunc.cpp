/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwPublicFunc.cpp
* Create: 	10/06/06
* Desc:		一些通用函数
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/SwPublicFunc.h"
#include <string.h>
#include <tchar.h>
#include <io.h>

using namespace std;

bool SwPublicFunc::IsEndof(const char* pChar, const char* pEnd )
{
	if ( 0==pChar || 0==pEnd )
	{
		return false;
	}

	size_t nChar = strlen(pChar);
	size_t nEnd  = strlen(pEnd);
	if ( nChar < nEnd )
	{
		return false;
	}

	pChar += nChar-nEnd;

	return( _strnicmp( pChar, pEnd, nEnd ) == 0 );
}

void SwPublicFunc::RotationArc( Quaternion& quat, const Vector& pUnitFrom, const Vector& pUnitTo )
{
	Vector pUnit = pUnitFrom;
	Vector c	= pUnit.cross( pUnitTo );
	float    d	= pUnit.dot( pUnitTo );
	float    s	= Sqrt( (1.0f + d) * 2.0f );

	if( s < 0.0001f )
		s = 0.0001f;

	quat.x = c.x / s;
	quat.y = c.y / s;
	quat.z = c.z / s;
	quat.w = s	/ 2.0f;
}

void SwPublicFunc::CullBaseDir( TCHAR* pszBuffer )
{
	size_t j	= _tcslen( pszBuffer );
	TCHAR* pBuffer = NULL;
	pBuffer = _tcsrchr( pszBuffer, _T('\\') );
	if ( pBuffer ) 
	{
		*(pBuffer+1) = _T('\0');
	}

	j		= _tcslen( pszBuffer );
	if( j > 0 )
	{
		if ( ( pszBuffer[j-1] == _T('\\') ) || ( pszBuffer[j-1] == _T('/') ) ) 
		{
			pszBuffer[j-1] = 0;
		}
	}
}
void SwPublicFunc::GetAlphaData( uInt8 * alphaData, uInt8 *kAlphaMap )
{
	uInt8* alphaPtr		= alphaData;
	uInt8* mapPtr		= kAlphaMap;
	for( sInt32 y = 0; y < 64; ++y) 
	{
		for( sInt32 x = 0; x < 32; ++x) 
		{
			uInt8 c		= *mapPtr++;						// 这里为什么要这么处理？？
			*alphaPtr++	= ((c & 0x0f) << 4)|( c & 0x0f);
			*alphaPtr++	= ( c & 0xf0 )|(( c & 0xf0 ) >> 4);
		}
	}
}

static TCHAR s_charBuffer[MAX_PATH*2+1];

int SwPublicFunc::TChar2MutiChar( LPSTR outChar, int outSize, LPCTSTR inChar, int inSize )
{	
	int err = 0;
#ifdef  UNICODE     
	if( _tcslen( inChar ) < 1 )	{
#if _MSC_VER >= 1400
		strcpy_s( outChar, outSize, "" );
#else
		strcpy( outChar, "" );
#endif
	}
	else {
		try	{
#if _MSC_VER >= 1400
			_tcscpy_s( s_charBuffer, inChar );
#else
			_tcscpy( s_charBuffer, inChar );
#endif

			int len=WideCharToMultiByte(  // 第一次调用，计算所需 MBCS 字符串字节长度
				CP_ACP,
				0,
				s_charBuffer, // 宽字符串指针
				inSize, // 字符长度
				NULL,
				0,		// 参数0表示计算转换后的字符空间
				NULL,
				NULL);

			if( len>=outSize )
				return 1;

			WideCharToMultiByte( CP_ACP, 0,	s_charBuffer, len, outChar, len, NULL, NULL );
		}
		catch (...) {
			Trace("================转换字符串[%s]失败========================\n");
			return 1;		
		}
	}
#else
#if _MSC_VER >= 1400
	strcpy_s( outChar, outSize, inChar );
#else
	strcpy( outChar, inChar );
#endif
#endif	// UNICODE	

	return err;
}

int SwPublicFunc::WString2String(string& _dsc, const wstring& _src)
{
	//计算字符串 wstring 转成 char 之后占用的内存字节数
	int nBufSize = WideCharToMultiByte(GetACP(), 0, _src.c_str(),-1, NULL, 0, 0, FALSE);

	//为 char 分配内存 nBufSize 个字节
	char *szBuf = MeDefaultNew char[nBufSize];

	//转化为 char 的 string
	WideCharToMultiByte(GetACP(), 0, _src.c_str(),-1, szBuf, nBufSize, 0, FALSE);
	_dsc = szBuf;

	delete []szBuf;
	szBuf = NULL;

	return nBufSize;
}

int SwPublicFunc::String2WString(wstring& _dsc, const string& _src)
{
	//计算字符串 string 转成 wchar_t 之后占用的内存字节数
	int nBufSize = MultiByteToWideChar(GetACP(),0,_src.c_str(),-1,NULL,0); 

	//为 wsbuf 分配内存 nBufSize 个字节
	wchar_t *wsBuf = MeDefaultNew wchar_t[nBufSize];

	//转化为 unicode 的 WideString
	MultiByteToWideChar(GetACP(),0,_src.c_str(),-1,wsBuf,nBufSize); 
	_dsc = wsBuf;

	delete []wsBuf;
	wsBuf = NULL;

	return nBufSize;
}

bool SwPublicFunc::IsFileExist(const char* filename)
{
	if(_access(filename,0) == 0)   
	{
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------
std::string SwPublicFunc::GetFileName( const std::string& strFilePath )
{
	size_t nPos = strFilePath.rfind( '\\');
	if( nPos == std::string::npos)
		nPos = strFilePath.rfind( '/');

	size_t nLength = strFilePath.length();
	if( nPos != std::string::npos && nPos < nLength )
	{
		return strFilePath.substr( nPos + 1, nLength - nPos -1 );	
	}

	return "";
}

// 根据球坐标计算笛卡尔坐标
Vector SwPublicFunc::Spherical2Cartesian(Vector kSpherical)
{
	Vector Position;
	float fAngle = kSpherical.z + PI * 0.5f;

	Position.x = kSpherical.x * cos(kSpherical.y) * sin(fAngle);
	Position.y = kSpherical.x * sin(kSpherical.y) * sin(fAngle);
	Position.z = kSpherical.x * cos(fAngle);

	return Position;
}

Vector SwPublicFunc::Cartesian2Spherical( Vector kSpherical )
{
	Vector Position;
	Position.x = Sqrt(kSpherical.x*kSpherical.x + kSpherical.y*kSpherical.y + kSpherical.z*kSpherical.z);
	Position.y = atan(kSpherical.y/Position.x);
	Position.z = acos(kSpherical.z / Position.x) - PI * 0.5f;

	return Position;
}

float SwPublicFunc::NiFastATan2(float fY, float fX)
{
	// Poly approximation valid for |z| <= 1.  To compute ATAN(z)
	// for z > 1, use ATAN(z) = PI/2 - ATAN(1/z).  For z < -1, use
	// ATAN(z) = -PI/2 - ATAN(1/z).

	if (fX == 0.0f && fY == 0.0f)
		return 0.0f;

	float fOffset = 0.0f;
	float fZ;
	if (abs(fY) > abs(fX))
	{
		//  |fY/fX| > 1 so use 1/z identities.
		fZ = fX / fY;
		if (fZ > 0.0f)
		{
			fOffset = NI_HALF_PI;
		}
		else if (fZ < 0.0f)
		{
			fOffset = -NI_HALF_PI;
		}
		else // fZ == 0.0f
		{
			// special case for 90deg and -90deg
			return (fY > 0.0f) ? NI_HALF_PI : -NI_HALF_PI;
		}
	}
	else
	{
		fZ = fY / fX;

		if (fZ == 0.0f)
		{
			// special case for 0deg and 180deg
			return (fX > 0.0f) ? 0.0f : PI;
		}
	}

	float fZ2 = fZ * fZ;

	// Polynomial approximation of degree 9, P(z).
	// |ATAN(z)-P(z)| <= 1e-05

	float fResult;
	fResult = 0.0208351f;
	fResult *= fZ2;
	fResult -= 0.0851330f;
	fResult *= fZ2;
	fResult += 0.1801410f;
	fResult *= fZ2;
	fResult -= 0.3302995f;
	fResult *= fZ2;
	fResult += 0.9998660f;
	fResult *= fZ;

	if (fOffset)
		fResult = fOffset - fResult;

	// find proper solution to two arg arctan
	if (fY < 0.0f && fX < 0.0f)  // quadrant IV
		fResult -= PI;
	if (fY > 0.0f && fX < 0.0f)  // quadrant II
		fResult += PI;

	// NIASSERT(NiAbs(fResult - NiATan2(fY, fX)) <= 1e-05);

	return fResult;
}