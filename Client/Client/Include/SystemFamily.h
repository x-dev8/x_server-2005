#pragma once

#include "MsgBase.h"
#include "Singleton.h"
#include "FamilyDefine.h"
class CSystemFamily : public Singleton<CSystemFamily>
{
public:
	//家族列表,当前服务器的所有家族的基本信息
	void OnMsgAllFamilyInfoList( Msg* pMsg );
	void OnMsgTellCreateFmily( Msg *pMsg );

	void OnMsgTellClientProsperity(Msg *pMsg);
	//家族成员列表
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

	//公告相关
	void OnMsgTellFamilyNoticeUpdate(Msg *pMsg);
	void OnMsgFamilyNoticeAck(Msg *pMsg);

	//家族捐金
	void OnMsgFamilyDonateAck(Msg *pMsg);
	void OnMsgTellFamilyDonate(Msg *pMsg);

	//家族升级
	void OnMsgFamilyUpgradeAck(Msg *pMsg);
	void OnMsgTellFamilyUpgrade(Msg *pMsg);

	//家族解散，目前解散的时候不可能有家族成员在线了的
	void OnMsgTellFamilyDisband(Msg *pMsg);

	//回复申请加入
	void OnMsgJoinFamilyAck(Msg *pMsg);

	void OnMsgTellClientCanInvite(Msg *pMsg);
	

public:
	//家族列表
	FamilyDefine::FamilySimpleInfo* GetFamilySimpleInfo( unsigned int familyID );
	void GetAllInfo( std::vector<FamilyDefine::FamilySimpleInfo>& infoList );


	const char* GetLeaderName();

public:
	//家族成员相关
	void ClearFamilyInfo();
	bool IsMeHaveFamily();	//是否加入家族
	bool IsMeFamilyLeader( unsigned int dbid ); //自己是否是族长

	FamilyDefine::FamilyInfo* GetFamilyInfo(){ return &m_FamilyInfo; }
	void GetAllMemberInfo( std::vector<FamilyDefine::FamilyMember>& members ); //这里采用vector可以作为UI后台数据缓冲
	const FamilyDefine::FamilyMember* GetMember( unsigned int dbid );

	unsigned int GetMemeberCount();
	
private:
	//家族列表
	typedef std::map<unsigned int, FamilyDefine::FamilySimpleInfo> FamilySimpleInfoSet_t;
	typedef FamilySimpleInfoSet_t::iterator FamilySimpleInfoSetIt_t;
	FamilySimpleInfoSet_t m_mapFamilySimpleInfo;
private:
	//家族成员列表
	typedef std::map<unsigned int, FamilyDefine::FamilyMember> FamilyMemberSet_t;
	typedef FamilyMemberSet_t::iterator FamilyMemberSetIt_t;
	FamilyDefine::FamilyInfo	m_FamilyInfo;
	FamilyMemberSet_t			m_FamilyMembers;
};