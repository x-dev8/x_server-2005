#ifndef __FAMILY_MANAGER_H__
#define __FAMILY_MANAGER_H__

#include "Singleton.h"
#include "GameTimer.h"
#include "Family.h"


template < class TFamily >
class FamilyManager : public ISingletion< FamilyManager< TFamily > >
{
public:
	FamilyManager();
	~FamilyManager();

	// 添加一个家族
	bool AddFamily( TFamily* pFamily );

	// 删除一个家族
	bool RemoveFamily( unsigned int nFamilyID );

	// 获得家族信息
	TFamily* GetFamilyByID( unsigned int nFamilyID );

	// 检测家族同名
	bool CheckFamilyName( const char* szFamilyName );

	// 产生一个新的家族ID
	unsigned int MakeFamilyID();

	TFamily* GetFamilyByPlayerID( unsigned int nPlayerID );

	// 发送所有家族信息给玩家 or 所有服务器
	void SendAllFamiliesToClient( unsigned int nID );

	// 发送家族信息结束
	void SendAllFamiliesEnd( unsigned int nID );

	// 将玩家升到10级的消息发给所有家族的族长
	void SendPlayerLvUpToMaster( unsigned int nID, unsigned int nLv, char * szSpeakName );

	// 执行自动更新
	void RunUpdate( unsigned int nCurrentTime );

	// 开启加载数据定时器
	void StartLoadTimer();

	// 停止加载数据定时器
	void StopLoadTimer();

	// 是否加载完成
	bool GetLoadSuccess() const;

	// 设置是否加载完成
	void SetLoadSuccess( bool bValue );

	// 初始化家族列表
	void InitFamily( FamilyDefine::ServerFamilyInfo* pList, int nCount );

	// 初始化家族成员列表
	void InitFamilyMember( FamilyDefine::FamilyMember* pList, int nCount );
	
	// 是否存在任何家族
	bool IsExistFamily();

	// 无条件保存家族信息
	void SaveFamilyInfo();

	// 是否有玩家刚退出家族
	__int64 GetLeaveFamilyTime( unsigned int nMemberID );

private:
	typedef std::map< unsigned int, TFamily* >	FamilyContainer;
	typedef typename FamilyContainer::iterator	FamilyContainerItr;

	typedef std::map< std::string, unsigned int >	FamilyNameIDMapping;
	typedef FamilyNameIDMapping::iterator			FamilyNameIDMappingItr;

	// 添加一个家族名字关联
	void AddFamilyName( TFamily* pFamily );

	// 删除一个家族名字关联
	void RemoveFamilyName( TFamily* pFamily );

	// 发送加载家族信息请求
	void ProcessLoadFamilyData( unsigned int nCurrentTime );

	FamilyContainer		_familyContainer;
	FamilyNameIDMapping	_familyNameIDMapping;
	GameTimerEx			_updateTimer;

	bool _bLoadSuccess;        // 是否加载成功
	bool _bLoadTimerStart;     // 是否启动加载定时器
	GameTimerEx _loadTimer;   // 加载定时器
};

//////////////////////////////////////////////////////////////////////////
template < class TFamily >
FamilyManager<TFamily>::FamilyManager()
{
	_bLoadSuccess = false;
	_bLoadTimerStart = false;
	_updateTimer.StartTimer( 1, FamilyDefine::UpdateSpace );
}

template < class TFamily >
FamilyManager<TFamily>::~FamilyManager()
{
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{ itr->second->Release(); }
}

template < class TFamily >
void FamilyManager<TFamily>::AddFamilyName( TFamily* pFamily )
{
	if ( NULL == pFamily )
	{ return; }

	_familyNameIDMapping[ pFamily->GetFamilyName() ] = pFamily->GetFamilyID();
}

template < class TFamily >
void FamilyManager<TFamily>::RemoveFamilyName( TFamily* pFamily )
{
	if ( NULL == pFamily )
	{ return; }

	FamilyNameIDMappingItr itr = _familyNameIDMapping.find( pFamily->GetFamilyName() );
	if ( itr == _familyNameIDMapping.end() )
	{ return; }

	_familyNameIDMapping.erase( itr );
}

template < class TFamily >
bool FamilyManager<TFamily>::AddFamily( TFamily* pFamily )
{
	if ( NULL == pFamily )
	{ return false; }

	AddFamilyName(pFamily);

	return _familyContainer.insert( std::make_pair( pFamily->GetFamilyID(), pFamily ) ).second;
}

template < class TFamily >
bool FamilyManager<TFamily>::RemoveFamily( unsigned int nFamilyID )
{
	if ( FamilyDefine::InitFamilyID == nFamilyID )
	{ return false; }

	FamilyContainerItr itr = _familyContainer.find( nFamilyID );
	if ( itr == _familyContainer.end() )
	{ return false; }

	RemoveFamilyName( itr->second );

	itr->second->Release();
	_familyContainer.erase( itr );
	return true;
}

template < class TFamily >
TFamily* FamilyManager<TFamily>::GetFamilyByID( unsigned int nFamilyID )
{
	if ( FamilyDefine::InitFamilyID == nFamilyID )
	{ return NULL; }

	FamilyContainerItr itr = _familyContainer.find( nFamilyID );
	if ( itr == _familyContainer.end() )
	{ return NULL; }

	return itr->second;
}

template < class TFamily >
bool FamilyManager<TFamily>::CheckFamilyName( const char* szFamilyName )
{
	if ( _familyNameIDMapping.empty() )
	{ return true; }

	FamilyNameIDMappingItr itr = _familyNameIDMapping.find( szFamilyName );
	return itr == _familyNameIDMapping.end();
}

template < class TFamily >
unsigned int FamilyManager<TFamily>::MakeFamilyID()
{
	if ( _familyContainer.empty() )
	{ return FamilyDefine::FirstFamilyID; }

	return _familyContainer.rbegin()->first + 1;
}

template < class TFamily >
TFamily* FamilyManager<TFamily>::GetFamilyByPlayerID( unsigned int nPlayerID )
{
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->second->GetMemberByID( nPlayerID ) )
		{ return itr->second;}
	}
	return NULL;
}

template < class TFamily >
void FamilyManager<TFamily>::StartLoadTimer()
{
	if ( _bLoadTimerStart )
	{ return; }     // 已经开启

	_bLoadTimerStart = true;
	_loadTimer.StartTimer( 1, FamilyDefine::LoadSpaceTime );
}

template < class TFamily >
void FamilyManager<TFamily>::StopLoadTimer()
{
	_loadTimer.StopTimer();
}

template < class TFamily >
bool FamilyManager<TFamily>::GetLoadSuccess() const
{
	return _bLoadSuccess;
}

template < class TFamily >
void FamilyManager<TFamily>::SetLoadSuccess( bool bValue )
{
	_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadFamilySuccess);
	}
}

template < class TFamily >
void FamilyManager<TFamily>::InitFamily( FamilyDefine::ServerFamilyInfo* pList, int nCount )
{
	if ( NULL == pList || GetLoadSuccess() )
	{ return; }

	StopLoadTimer();

	for ( int i = 0; i < nCount; ++i )
	{
		TFamily* pFamily = TFamily::CreateFamily();
		if ( NULL == pFamily )
		{ continue; }

		pFamily->InitFamilyInfo( pList[i] );
		AddFamily( pFamily );
	}
}

template < class TFamily >
void FamilyManager<TFamily>::InitFamilyMember( FamilyDefine::FamilyMember* pList, int nCount )
{
	if ( pList == NULL || nCount == 0 )
	{ return; }

	for ( int i = 0; i < nCount; ++i )
	{
		TFamily* pFamily = GetFamilyByID( pList[i].GetFamilyID() );
		if ( pFamily == NULL )
		{ continue; }

		pFamily->AddMember( pList[i] );
	}
}

template< class TFamily >   // 无条件保存帮派信息
void FamilyManager<TFamily>::SaveFamilyInfo()
{
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		itr->second->SaveFamilyAndMemberData();
	}
}

template< class TFamily >
__int64 FamilyManager<TFamily>::GetLeaveFamilyTime( unsigned int nMemberID )
{
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		__int64 nTime = itr->second->GetMemberLeaveRecord( nMemberID );

		if ( nTime != 0 )
		{ return nTime; }
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////

#define theGameFamilyManager FamilyManager< GameFamily >::Instance()
#define theCenterFamilyManager FamilyManager< CenterFamily >::Instance()
//////////////////////////////////////////////////////////////////////////

#endif // __FAMILY_MANAGER_H__