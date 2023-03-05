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

	// ���һ������
	bool AddFamily( TFamily* pFamily );

	// ɾ��һ������
	bool RemoveFamily( unsigned int nFamilyID );

	// ��ü�����Ϣ
	TFamily* GetFamilyByID( unsigned int nFamilyID );

	// ������ͬ��
	bool CheckFamilyName( const char* szFamilyName );

	// ����һ���µļ���ID
	unsigned int MakeFamilyID();

	TFamily* GetFamilyByPlayerID( unsigned int nPlayerID );

	// �������м�����Ϣ����� or ���з�����
	void SendAllFamiliesToClient( unsigned int nID );

	// ���ͼ�����Ϣ����
	void SendAllFamiliesEnd( unsigned int nID );

	// ���������10������Ϣ�������м�����峤
	void SendPlayerLvUpToMaster( unsigned int nID, unsigned int nLv, char * szSpeakName );

	// ִ���Զ�����
	void RunUpdate( unsigned int nCurrentTime );

	// �����������ݶ�ʱ��
	void StartLoadTimer();

	// ֹͣ�������ݶ�ʱ��
	void StopLoadTimer();

	// �Ƿ�������
	bool GetLoadSuccess() const;

	// �����Ƿ�������
	void SetLoadSuccess( bool bValue );

	// ��ʼ�������б�
	void InitFamily( FamilyDefine::ServerFamilyInfo* pList, int nCount );

	// ��ʼ�������Ա�б�
	void InitFamilyMember( FamilyDefine::FamilyMember* pList, int nCount );
	
	// �Ƿ�����κμ���
	bool IsExistFamily();

	// ���������������Ϣ
	void SaveFamilyInfo();

	// �Ƿ�����Ҹ��˳�����
	__int64 GetLeaveFamilyTime( unsigned int nMemberID );

private:
	typedef std::map< unsigned int, TFamily* >	FamilyContainer;
	typedef typename FamilyContainer::iterator	FamilyContainerItr;

	typedef std::map< std::string, unsigned int >	FamilyNameIDMapping;
	typedef FamilyNameIDMapping::iterator			FamilyNameIDMappingItr;

	// ���һ���������ֹ���
	void AddFamilyName( TFamily* pFamily );

	// ɾ��һ���������ֹ���
	void RemoveFamilyName( TFamily* pFamily );

	// ���ͼ��ؼ�����Ϣ����
	void ProcessLoadFamilyData( unsigned int nCurrentTime );

	FamilyContainer		_familyContainer;
	FamilyNameIDMapping	_familyNameIDMapping;
	GameTimerEx			_updateTimer;

	bool _bLoadSuccess;        // �Ƿ���سɹ�
	bool _bLoadTimerStart;     // �Ƿ��������ض�ʱ��
	GameTimerEx _loadTimer;   // ���ض�ʱ��
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
	{ return; }     // �Ѿ�����

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

template< class TFamily >   // ���������������Ϣ
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