/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldRes.cpp
* Create: 	10/06/2006
* Desc:		数据资源基类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"


sInt32& CBaseRes::GetId() 
{
	return m_id;
}

void CBaseRes::SetId( sInt32 id )
{
	m_id		= id;
}

////////////////////////////////////////////////////////////////////////////////
CWorldRes::CWorldRes()
{
	m_isLoad	= false;
	m_refCount	= 0;
	memset(m_name,0,sizeof(char)*RES_NAME_LEN);
}

CWorldRes::~CWorldRes()
{
	m_isLoad	= false;
}


const char*	CWorldRes::GetName() const
{
	return m_name;
}
void CWorldRes::SetName( const char* name )
{
// 	CPathA workPath(CWorld::GetAppDataCharDir());
// 	workPath.RelativePathTo(CWorld::GetAppDataCharDir(),FILE_ATTRIBUTE_DIRECTORY,name,FILE_ATTRIBUTE_NORMAL);

#if _MSC_VER >= 1400
	if (strstr(name,".lex") != NULL)
	{
		int i = 0;
	}
	strcpy_s( m_name, RES_NAME_LEN, name );
#else
	strcpy( m_name, name );
#endif

//	strcpy_s( m_name, workPath.m_strPath.GetString() );
}

void CWorldRes::IncRefCount()
{
	++m_refCount;
}

void CWorldRes::DecRefCount()
{
	--m_refCount;

}