/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwType.h
* Create: 	10/06/06
* Desc:		基本类型定义
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWTYPE_H__
#define __SWTYPE_H__


typedef signed char			sInt8;
typedef unsigned char		uInt8;
typedef signed short		sInt16;
typedef unsigned short		uInt16;
typedef signed int			sInt32;
typedef unsigned long		uInt32;
 typedef unsigned char		uAlphaBit;
// typedef unsigned int		uAlphaBit;
typedef __int64				sInt64;
typedef unsigned __int64	uInt64;

typedef float				flt32;		// 32-bit IEEE floating point.
typedef double				flt64;		// 64-bit IEEE double.


#ifdef _UNICODE
typedef wchar_t				swChar;
#else  
typedef char				swChar;
#endif

////////////////////////////////////////////////////////////////////////////////
struct						swRect
{
	sInt32	x;
	sInt32	y;
	sInt32	w;
	sInt32	h;
};


struct						swPoint3
{
	float	x;
	float	y;
	float	z;

	inline const swPoint3& operator= (const swPoint3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	inline bool operator== (const swPoint3& v)
	{
		return(x==v.x && y==v.y && z==v.z);
	}
	inline bool operator!= (const swPoint3& v)
	{
		return(!(*this==v));
	}
};

// Define
#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

#endif	// __SWTYPE_H__