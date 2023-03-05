/********************************************************************
    Filename:    FlyMemAllocer.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_FLYMEMALLOCER_H__
#define __UTILITY_FLYMEMALLOCER_H__

#pragma once

#include <windows.h>

class CFlyMemAllocer
{
public:
	virtual void* Malloc( DWORD dwSize ) = 0;
	virtual void  Free( void* lpMem ) = 0;
};

class CFlyNormalAllocer : public CFlyMemAllocer
{
public:
	virtual void* Malloc( DWORD dwSize )
	{
		return new char[ dwSize ];
	}
	virtual void  Free( void* lpMem )
	{
		if( lpMem )
		delete lpMem;
	}
};

#endif // __UTILITY_FLYMEMALLOCER_H__
