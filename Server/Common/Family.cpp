#include "Family.h"

bool Family::AddMember( const FamilyDefine::FamilyMember& member )
{
	return _memberContainer.insert( std::make_pair( member.GetID(), member ) ).second;
}

bool Family::IsFamilyLeader( unsigned int nPlayerID ) const
{
	return nPlayerID == GetLeaderID();
}

FamilyDefine::FamilyMember* Family::GetMemberByID( unsigned int nPlayerID )
{
	MemberContainerItr itr = _memberContainer.find(nPlayerID);
	if ( itr == _memberContainer.end() )
	{ return NULL; }
	return &itr->second;
}

bool Family::HaveRight( unsigned int nPlayerID, unsigned int nRight )
{
	FamilyDefine::FamilyMember* pMember = GetMemberByID(nPlayerID);
	if ( NULL == pMember )
	{ return false; }

	return ( FamilyDefine::GetRightByPositon( pMember->GetPosition() ) & nRight ) != 0;
}

void Family::AddInviteRecord( unsigned int nInviterID, unsigned int nInviteeID, unsigned int nTime )
{
	FamilyDefine::FamilyInvite invite;
	invite.SetInviterID( nInviterID );
	invite.SetInviteeID( nInviteeID );
	invite.SetInviteTime( nTime );
	_inviteRecords.insert( std::make_pair( nInviteeID, invite ) );
}

FamilyDefine::FamilyInvite* Family::GetInviteRecord( unsigned int nInviteeID )
{
	InviteRecordsContainerItr itr = _inviteRecords.find( nInviteeID );
	if ( itr == _inviteRecords.end() )
	{ return NULL; }
	return &itr->second;
}

void Family::RemoveInviteRecord( unsigned int nInviteeID )
{
	InviteRecordsContainerItr itr = _inviteRecords.find( nInviteeID );
	if ( itr != _inviteRecords.end() )
	{ _inviteRecords.erase( itr ); }
}

void Family::AddRequestRecord( FamilyDefine::FamilyMember& requester, unsigned int nTime )
{
	FamilyDefine::FamilyRequest request;
	request.SetMember( requester );
	request.SetRequestTime( nTime );
	_requestRecords.insert( std::make_pair( requester.GetID(), request ) );
}

void Family::RemoveRequestRecord( unsigned int nRequesterID )
{
	RequestRecordsContainerItr itr = _requestRecords.find( nRequesterID );
	if ( itr != _requestRecords.end() )
	{ _requestRecords.erase( itr ); }
}

FamilyDefine::FamilyRequest* Family::GetRequestRecord( unsigned int nRequesterID )
{
	RequestRecordsContainerItr itr = _requestRecords.find( nRequesterID );
	if ( itr == _requestRecords.end() )
	{ return NULL; }
	return &itr->second;
}

void Family::AddMemberLeaveRecord( unsigned int nMemberID, __int64 nTime )
{
	_leaveTimeRecords.insert( std::make_pair( nMemberID, nTime ) );
}

void Family::RemoveMemberLeaveRecord( unsigned int nMemberID )
{
	MemberLeaveContainerItr itr = _leaveTimeRecords.find( nMemberID );
	if ( itr != _leaveTimeRecords.end() )
	{ _leaveTimeRecords.erase( itr ); }
}

__int64 Family::GetMemberLeaveRecord( unsigned int nMemberID )
{
	MemberLeaveContainerItr itr = _leaveTimeRecords.find( nMemberID );
	if ( itr == _leaveTimeRecords.end() )
	{ return 0; }
	return itr->second;
}

bool Family::RemoveMember( unsigned int nPlayerID )
{
	MemberContainerItr itr = _memberContainer.find( nPlayerID );
	if ( itr == _memberContainer.end() )
	{ return false; }

	_memberContainer.erase( itr );
	return true;
}

void Family::InitFamilyInfo( const FamilyDefine::ServerFamilyInfo& info )
{
	SetFamilyID( info.GetFamilyID() );
	SetFamilyLevel( info.GetFamilyLevel() );
	SetFamilyName( info.GetFamilyName() );
	SetFamilyTotem( info.GetFamilyTotem() );
	SetFamilyAim( info.GetFamilyAim() );
	SetProsperity( info.GetProsperity() );
	SetMoney( info.GetMoney() );
	SetLeaderID( info.GetLeaderID() );
	SetDisbandTime( info.GetDisbandTime() );
}

void Family::ProcessDonateMoney( FamilyDefine::FamilyMember& donater, unsigned int nDonateMoney )
{
	SetMoney( GetMoney() + nDonateMoney );
	donater.SetDonateMoney( donater.GetDonateMoney() + nDonateMoney );
}

void Family::ProcessMemberOffline( FamilyDefine::FamilyMember& member )
{
	member.SetOnline( false );;
}
