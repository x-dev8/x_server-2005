#pragma once

#include "MsgBase.h"
#include "Singleton.h"
#include "FamilyDefine.h"
class CSystemFamily : public Singleton<CSystemFamily>
{
public:
	//�����б�,��ǰ�����������м���Ļ�����Ϣ
	void OnMsgAllFamilyInfoList( Msg* pMsg );
	void OnMsgTellCreateFmily( Msg *pMsg );

	void OnMsgTellClientProsperity(Msg *pMsg);
	//�����Ա�б�
	void OnMsgTellFamilyInfo(Msg *pMsg);
	void OnMsgTellJoinFamilyToFamily(Msg *pMsg);
	void OnMsgTellLeaveFamilyToFamily(Msg *pMsg);
	void OnMsgQuitFamilyAck(Msg *pMsg);
	void OnMsgFamilyTransferAck(Msg *pMsg);
	void OnMsgTellFamilyTransfer(Msg *pMsg);
	void OnMsgFamilyMemberDataUpdate(Msg *pMsg);

	void OnMsgTellViewPositionChange(Msg *pMsg);
	void OnMsgTellLeaveFamilyToView(Msg *pMsg);
	void OnMsgTellJoinFamilyToView(Msg *pMsg);

	//�������
	void OnMsgTellFamilyNoticeUpdate(Msg *pMsg);
	void OnMsgFamilyNoticeAck(Msg *pMsg);

	//������
	void OnMsgFamilyDonateAck(Msg *pMsg);
	void OnMsgTellFamilyDonate(Msg *pMsg);

	//��������
	void OnMsgFamilyUpgradeAck(Msg *pMsg);
	void OnMsgTellFamilyUpgrade(Msg *pMsg);

	//�����ɢ��Ŀǰ��ɢ��ʱ�򲻿����м����Ա�����˵�
	void OnMsgTellFamilyDisband(Msg *pMsg);

	//�ظ��������
	void OnMsgJoinFamilyAck(Msg *pMsg);

	void OnMsgTellClientCanInvite(Msg *pMsg);
	

public:
	//�����б�
	FamilyDefine::FamilySimpleInfo* GetFamilySimpleInfo( unsigned int familyID );
	void GetAllInfo( std::vector<FamilyDefine::FamilySimpleInfo>& infoList );


	const char* GetLeaderName();

public:
	//�����Ա���
	void ClearFamilyInfo();
	bool IsMeHaveFamily();	//�Ƿ�������
	bool IsMeFamilyLeader( unsigned int dbid ); //�Լ��Ƿ����峤

	FamilyDefine::FamilyInfo* GetFamilyInfo(){ return &m_FamilyInfo; }
	void GetAllMemberInfo( std::vector<FamilyDefine::FamilyMember>& members ); //�������vector������ΪUI��̨���ݻ���
	const FamilyDefine::FamilyMember* GetMember( unsigned int dbid );

	unsigned int GetMemeberCount();
	
private:
	//�����б�
	typedef std::map<unsigned int, FamilyDefine::FamilySimpleInfo> FamilySimpleInfoSet_t;
	typedef FamilySimpleInfoSet_t::iterator FamilySimpleInfoSetIt_t;
	FamilySimpleInfoSet_t m_mapFamilySimpleInfo;
private:
	//�����Ա�б�
	typedef std::map<unsigned int, FamilyDefine::FamilyMember> FamilyMemberSet_t;
	typedef FamilyMemberSet_t::iterator FamilyMemberSetIt_t;
	FamilyDefine::FamilyInfo	m_FamilyInfo;
	FamilyMemberSet_t			m_FamilyMembers;
};