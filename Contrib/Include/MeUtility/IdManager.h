#pragma once
#include "arraycontainer.h"
//template<class ObjectType >
class CIdMgr 
{
public:
	CIdMgr( int nSize = 0 )
	{
		if( nSize != 0 )
			Create( nSize );
	}
	~CIdMgr()
	{
	}

	BOOL	Create( int nSize )
	{
		return m_ac.Create( nSize );
	}
	int		Alloc()
	{
		return m_ac.Add( 0 );
	}
	BOOL	Free( int nId )
	{
		return m_ac.Remove( nId );
	}
	CStaticArrayContainer<char>* GetAC(){ return &m_ac; }
protected:
	CStaticArrayContainer<char> m_ac;

};