#pragma once

#include "MeRTLibs.h"

// 静态数组容器，不能动态增长
template<class ObjectType >
class CStaticArrayContainer
{
public:
	CStaticArrayContainer( int nMaxObject = 0 ):
	  m_nMaxObject(0),
	  m_pObjects(NULL),
	  m_ppObjectsUsed(NULL),
	  m_pnUnusedIds(NULL),
	  m_nUnusedIp(0),
	  m_pbUsedFlags(NULL),
	  m_nUsedCount(0)
	{
		if( nMaxObject != 0 )
			Create( nMaxObject );
	}
	~CStaticArrayContainer(void)
	{
		m_nMaxObject = 0;
		if( m_pObjects )
		{
			delete[] m_pObjects;
			m_pObjects = NULL;
		}
		if( m_ppObjectsUsed )
		{
			delete [] m_ppObjectsUsed;
			m_ppObjectsUsed = NULL;
		}
		if( m_pnUnusedIds )
		{
			delete[] m_pnUnusedIds;
			m_pnUnusedIds = NULL;
		}
		if( m_pbUsedFlags )
		{
			delete[] m_pbUsedFlags;
			m_pbUsedFlags = NULL;
		}
	}
	BOOL	Create( int nMaxObject )
	{
		if( m_pObjects )
		{
			assert( false && "array has alread create" );
			return FALSE;
		}
		m_nMaxObject = nMaxObject;
		if( m_nMaxObject == 0 )
		{
			assert( false );
			return FALSE;
		}
		m_pObjects = new ObjectType[m_nMaxObject];
		m_ppObjectsUsed = new ObjectType*[m_nMaxObject];
#ifdef _DEBUG			
		memset( m_pObjects, 0x00, sizeof( ObjectType )*m_nMaxObject );
#endif
		memset( m_ppObjectsUsed, 0x00, sizeof( ObjectType* )*m_nMaxObject );

		m_pnUnusedIds = new int[m_nMaxObject];
		for( int i = 0; i < m_nMaxObject-1; i++ )
		{
			m_pnUnusedIds[i] = i+1;
		}
		m_pnUnusedIds[m_nMaxObject-1] = -1;
		m_pbUsedFlags = new unsigned char[m_nMaxObject];
		memset( m_pbUsedFlags, 0x00, sizeof(unsigned char)*m_nMaxObject );
		return TRUE;
	}
	int	Add( ObjectType obj )
	{
		// 如果已经没有可用的空间了
		if( m_nUnusedIp == -1 )
		{
			assert( false && "array is full, add element failed" );
			return -1;
		}
		// 冗余的做法，测试一下，更加保险，起到调试的作用
		assert( m_nUsedCount < m_nMaxObject );
		
		// 返回当前未用的单元id
		int nId = m_nUnusedIp;
		m_pObjects[m_nUnusedIp] = obj;
		assert( m_pbUsedFlags[m_nUnusedIp] == false );
		m_pbUsedFlags[m_nUnusedIp] = true;
		// 得到下一个未用单元的id
		m_nUnusedIp = m_pnUnusedIds[m_nUnusedIp];
		
		m_nUsedCount++;
		return nId;
	}
	BOOL	Remove( int nId )
	{
		if( nId < 0 || nId >= m_nMaxObject )
			return FALSE;
		if( !m_pbUsedFlags[nId] )
		{
			assert( false && "remove unused element" );
			return FALSE;
		}
#ifdef _DEBUG
		memset( &m_pObjects[nId], 0x00, sizeof( ObjectType ) );
#endif
		m_pnUnusedIds[nId] = m_nUnusedIp;
		m_pbUsedFlags[nId] = false;
		m_nUnusedIp = nId;

		m_nUsedCount--;
		return TRUE;
	}
	ObjectType	Get( int nId )
	{
		if( !IsUsed( nId ) )
		{
			assert( false && "get unused element" );
			static ObjectType s;
			return s;
		}
		return m_pObjects[nId];
	}
	BOOL IsUsed( int nId )
	{
		if( nId < 0 || nId >= m_nMaxObject )
			return FALSE;
		if( m_pbUsedFlags[nId] )
			return TRUE;
		return FALSE;
	}
	// 得到使用了的元素
	int			GetUsed( ObjectType* pObjects = NULL, int nSize = 0 )
	{
		// 如果nSize==0，则认为要使用container内部的缓冲
		if( pObjects != NULL &&
			nSize < m_nUsedCount )
			return 0;
		
		int nCount = 0;
		for( int i = 0; i < m_nMaxObject; i++ )
		{
			if( m_pbUsedFlags[i] )
			{
				if( pObjects )
					pObjects[nCount] = m_pObjects[i];
				m_ppObjectsUsed[nCount] = &m_pObjects[i];
				nCount++;
			}
		}
		assert( nCount == m_nUsedCount );
		return m_nUsedCount;
	}
	// 得到使用了的元素指针
	//int			GetUsed( ObjectType* pObjects[], int nSize )
	//{
	//	if( nSize < m_nUsedCount )
	//		return 0;

	//	int nCount = 0;
	//	for( int i = 0; i < m_nMaxObject; i++ )
	//	{
	//		if( m_pbUsedFlags[i] )
	//			objects[nCount++] = &m_pObjects[i];
	//	}
	//	assert( nCount == m_nUsedCount );
	//	return m_nUsedCount;
	//}
	int			GetUsedCount(){ return m_nUsedCount; }
	//int			GetUsedObjects(){ return m_ppObjectsUsed; }

protected:
	int		m_nMaxObject;
	ObjectType* m_pObjects;
	ObjectType** m_ppObjectsUsed;
	
	//int*		m_pnUsedIds;
	//int			m_nUsedIp;
	int			m_nUnusedIp;
	int*		m_pnUnusedIds;
	
	
	unsigned char* m_pbUsedFlags;

	int			m_nUsedCount;
};
