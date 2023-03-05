#include "funcperformancelog.h"
#include "packagefactory.h"
#include <assert.h>

static CPackageFactory gs_PackageFactory;
CPackageFactory* GetPackageFactory()
{
	return &gs_PackageFactory;
}
BOOL LoadFileToMemory( const char* pszPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize )
{
	return gs_PackageFactory.LoadFileToMemory( pszPackage, pszFilename, ppBuffer, pnFileSize );
}

CPackageFactory::CPackageFactory()
{
	guardfunc;
	unguard;
}

CPackageFactory::~CPackageFactory()
{
	guardfunc;
	Destroy();
	unguard;
}

void CPackageFactory::Destroy()
{
	guardfunc;
	for( int nPack = 0; nPack < m_Packages.size(); nPack++ )
	{
		Package* pPackage = m_Packages[nPack];
		if( pPackage->bExist )
		{
			// 销毁vfs
		}
		delete pPackage;
	}
	m_Packages.clear();
	m_Finder.Destroy();
	unguard;
}
BOOL CPackageFactory::LoadFileToMemoryFromDisk( const char* pszFilename, BYTE** ppBuffer, int* pnFileSize )
{
	guardfunc;
	FILE* fp = fopen( pszFilename, "rb" );
	if( fp == 0 )
		return FALSE;
	fseek ( fp, 0, SEEK_END );
	DWORD dwFileSize = ftell( fp );
	if( dwFileSize == 0 )
	{
		fclose( fp );
		return FALSE;
	}
	BYTE* pBuffer = new BYTE[dwFileSize];
	rewind( fp );
	fread( pBuffer, dwFileSize, 1, fp );
	fclose( fp );
	*ppBuffer = pBuffer;
	if( pnFileSize )
		*pnFileSize = dwFileSize;
	return TRUE;;
	unguard;
}
int	CPackageFactory::OpenPackage( const char* pszPackage )
{
	if( !pszPackage )
	{
		assert( false );
		return -1;
	}
	// 查找
	Package* pPackage = (Package*)m_Finder.GetDstByName( pszPackage );
	if( pPackage )
		return pPackage->nId;
	// 如果之前没有打开过
	pPackage = new Package;
	strcpy( pPackage->szPath, pszPackage );
	pPackage->nId = m_Packages.size();
	m_Packages.push_back( pPackage );
	m_Finder.Register( pszPackage, pPackage );

	pPackage->bExist = pPackage->vfs.LoadVFS( pszPackage );
	return pPackage->nId;

}
BOOL CPackageFactory::LoadFileToMemory( int nPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize )
{
	if( nPackage == -1 ||
		nPackage >= m_Packages.size() )
	{
		assert( false );
		return FALSE;
	}
	Package* pPackage = m_Packages[nPackage];

	BYTE* pbyBuffer = NULL;
	int	nFileSize = 0;
	if( LoadFileToMemoryFromDisk( pszFilename, &pbyBuffer, &nFileSize ) )
	{
		if( ppBuffer )
			*ppBuffer = pbyBuffer;
		if( pnFileSize)
			*pnFileSize = nFileSize;
		return TRUE;
	}
	// 如果包不存在
	if( !pPackage ||
		!pPackage->bExist )
		return FALSE;
	size_t size;
	// 如果包中不存在该文件
	if( !pPackage->vfs.GetUnitLength( pszFilename, size ) )
		return FALSE;
	if( size == 0 )
		return FALSE;
	pbyBuffer = new BYTE[size];
	if( pPackage->vfs.GetUnit( pszFilename, pbyBuffer, size ) )
	{
		if( ppBuffer )
			*ppBuffer = pbyBuffer;
		if( pnFileSize )
			*pnFileSize = size;
		return TRUE;
	}
	delete[] pbyBuffer;

	return FALSE;
}
BOOL CPackageFactory::LoadFileToMemory( const char* pszPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize )
{
	int nPackage = OpenPackage( pszPackage );
	if( nPackage == -1 )
	{
		assert( false );
		return FALSE;
	}
	return LoadFileToMemory( nPackage, pszFilename, ppBuffer, pnFileSize );
	//Package* pPackage = m_Packages[nPackage];
	//// 查找
	////Package* pPackage = NULL;
	////// 如果要打开包
	////if( pszPackage )
	////{
	////	pPackage = (Package*)m_Finder.GetDstByName( pszPackage );
	////	// 如果之前没有打开过
	////	if( !pPackage )
	////	{
	////		pPackage = new Package;
	////		strcpy( pPackage->szPath, pszPackage );
	////		m_Packages.push_back( pPackage );
	////		m_Finder.Register( pszPackage, pPackage );

	////		pPackage->bExist = pPackage->vfs.LoadVFS( pszPackage );
	////	}
	////}

	//BYTE* pbyBuffer = NULL;
	//int	nFileSize = 0;
	//if( LoadFileToMemoryFromDisk( pszFilename, &pbyBuffer, &nFileSize ) )
	//{
	//	if( ppBuffer )
	//		*ppBuffer = pbyBuffer;
	//	if( pnFileSize)
	//		*pnFileSize = nFileSize;
	//	return TRUE;
	//}
	//// 如果包不存在
	//if( !pPackage ||
	//	!pPackage->bExist )
	//	return FALSE;
	//size_t size;
	//// 如果包中不存在该文件
	//if( !pPackage->vfs.GetUnitLength( pszFilename, size ) )
	//	return FALSE;
	//if( size == 0 )
	//	return FALSE;
	//pbyBuffer = new BYTE[size];
	//if( pPackage->vfs.GetUnit( pszFilename, pbyBuffer, size ) )
	//{
	//	if( ppBuffer )
	//		*ppBuffer = pbyBuffer;
	//	if( pnFileSize )
	//		*pnFileSize = size;
	//	return TRUE;
	//}
	//delete[] pbyBuffer;

	//return FALSE;
}