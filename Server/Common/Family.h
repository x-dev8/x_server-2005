#ifndef __FAMILY_H__
#define __FAMILY_H__

#include "FamilyDefine.h"
#include <map>


class Family : public FamilyDefine::ServerFamilyInfo
{
public:
	void InitFamilyInfo( const FamilyDefine::ServerFamilyInfo& info );

	// 添加成员
	bool AddMember( const FamilyDefine::FamilyMember& member );

	// 删除成员
	bool RemoveMember( unsigned int nPlayerID );

	// 成员数
	unsigned int GetMemberCount() const { return static_cast< unsigned int >( _memberContainer.size() ); }

	// 查找成员
	FamilyDefine::FamilyMember* GetMemberByID( unsigned int nPlayerID );

	// 获得家族长
	FamilyDefine::FamilyMember* GetFamilyLeader() const;

	// 是否家族长
	bool IsFamilyLeader( unsigned int nPlayerID ) const;

	bool HaveRight( unsigned int nPlayerID, unsigned int nRight );

	// 添加邀请
	void AddInviteRecord( unsigned int nInviterID, unsigned int nInviteeID, unsigned int nTime );

	// 查找邀请记录
	FamilyDefine::FamilyInvite* GetInviteRecord( unsigned int nInviteeID );

	// 删除邀请
	void RemoveInviteRecord( unsigned int nInviteeID );

	// 添加申请
	void AddRequestRecord( FamilyDefine::FamilyMember& requester, unsigned int nTime );

	// 删除申请
	void RemoveRequestRecord( unsigned int nRequesterID );

	// 查找申请记录
	FamilyDefine::FamilyRequest* GetRequestRecord( unsigned int nRequesterID );

	// 添加成员离开家族的信息
	void AddMemberLeaveRecord( unsigned int nMemberID, __int64 nTime );

	// 删除成员离开家族的信息
	void RemoveMemberLeaveRecord( unsigned int nMemberID );

	// 查找成员离开家族的信息
	__int64 GetMemberLeaveRecord( unsigned int nMemberID );

protected:
	void ProcessDonateMoney( FamilyDefine::FamilyMember& donater, unsigned int nDonateMoney );

	void ProcessMemberOffline( FamilyDefine::FamilyMember& member );

protected:
	typedef std::map< unsigned int, FamilyDefine::FamilyMember >	MemberContainer;
	typedef MemberContainer::iterator								MemberContainerItr;

	typedef std::map< unsigned int, FamilyDefine::FamilyInvite >	InviteRecordsContainer;
	typedef InviteRecordsContainer::iterator						InviteRecordsContainerItr;

	typedef std::map< unsigned int, FamilyDefine::FamilyRequest >	RequestRecordsContainer;
	typedef RequestRecordsContainer::iterator						RequestRecordsContainerItr;

	typedef std::map< unsigned int, __int64 >		MemberLeaveContainer;
	typedef MemberLeaveContainer::iterator		MemberLeaveContainerItr;

	MemberContainer		_memberContainer;

	InviteRecordsContainer	_inviteRecords;
	RequestRecordsContainer	_requestRecords;

	MemberLeaveContainer	_leaveTimeRecords;
};

#endif