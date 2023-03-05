#ifndef __FAMILY_H__
#define __FAMILY_H__

#include "FamilyDefine.h"
#include <map>


class Family : public FamilyDefine::ServerFamilyInfo
{
public:
	void InitFamilyInfo( const FamilyDefine::ServerFamilyInfo& info );

	// ��ӳ�Ա
	bool AddMember( const FamilyDefine::FamilyMember& member );

	// ɾ����Ա
	bool RemoveMember( unsigned int nPlayerID );

	// ��Ա��
	unsigned int GetMemberCount() const { return static_cast< unsigned int >( _memberContainer.size() ); }

	// ���ҳ�Ա
	FamilyDefine::FamilyMember* GetMemberByID( unsigned int nPlayerID );

	// ��ü��峤
	FamilyDefine::FamilyMember* GetFamilyLeader() const;

	// �Ƿ���峤
	bool IsFamilyLeader( unsigned int nPlayerID ) const;

	bool HaveRight( unsigned int nPlayerID, unsigned int nRight );

	// �������
	void AddInviteRecord( unsigned int nInviterID, unsigned int nInviteeID, unsigned int nTime );

	// ���������¼
	FamilyDefine::FamilyInvite* GetInviteRecord( unsigned int nInviteeID );

	// ɾ������
	void RemoveInviteRecord( unsigned int nInviteeID );

	// �������
	void AddRequestRecord( FamilyDefine::FamilyMember& requester, unsigned int nTime );

	// ɾ������
	void RemoveRequestRecord( unsigned int nRequesterID );

	// ���������¼
	FamilyDefine::FamilyRequest* GetRequestRecord( unsigned int nRequesterID );

	// ��ӳ�Ա�뿪�������Ϣ
	void AddMemberLeaveRecord( unsigned int nMemberID, __int64 nTime );

	// ɾ����Ա�뿪�������Ϣ
	void RemoveMemberLeaveRecord( unsigned int nMemberID );

	// ���ҳ�Ա�뿪�������Ϣ
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