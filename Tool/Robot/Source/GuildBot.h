#ifndef __GUILDBOT_H__
#define __GUILDBOT_H__
#include "stdafx.h"

#include "NormalBot.h"
#include <string>
#include <vector>
#include <string>
#include "GameDefineBot.h"
//结义.军团机器人
// 创建工会需要的钱财
#define CreateGuildGold ( 500000 )

class CGuildBot : public CNormalBot
{
public:
    enum EGuildType
    {
        EGT_Init        = 0x0,				// 未初始化
        EGT_Comment     = 0x1,				// 普通成员
        EGT_TongMaster  = 0x2,				// 堂主
        EGT_CorpMaster	= 0x4,				// 帮派长
    };
    enum EMasterOperation
    {
        EMO_Disband = 0,
        EMO_ModifiyManifesto = 1,
        EMO_Exit = 2,
        EMO_Invite = 3,
        EMO_Ban = 4,
        EMO_Cession = 5,
        EMO_SetTongMaster = 6,
    };
    enum ETongMasterOperation
    {
        ETMO_Invite = 0,
        ETMO_CessionTongMaster = 1,
        ETMO_ModifiyTongManifesto = 2,
    };

    typedef std::map<unsigned int,SGuildMember>  GuildMemberContainer;
    typedef GuildMemberContainer::iterator       ItrGuildMemberContainer;

    typedef std::map<std::string, SGuildMember*> GuildMemberByNameContainer;
    typedef GuildMemberByNameContainer::iterator ItrGuildMemberByNameContainer;
public:
	CGuildBot();
	virtual ~CGuildBot();

	virtual void InitPlayGame(UINT mapid = 0);
	virtual void PlayGame();
	virtual void PlayGuild(DWORD dwTime);
	virtual void SwitchMsg(Msg* pMsg);

public: // 方法
    void InitBotGuildType();    // 计算GuildType
    void InitGuildData();       // 初始化帮派数据

	void RunGuildCorps();       // Run帮派长逻辑
	void RunGuildTong();        // Run堂主逻辑
	void RunGuildComment();     // Run普通成员逻辑
    

    void ExitGuild();           // 解散帮派
    void DisbandGuild();        // 解散帮派
    void CessionGuildMaster();  // 转让会长
    bool CreateGuild(char* szGuildName);  // 创建帮派
    void BanGuildMember(int MemberDBId);  // 踢出帮会成员
    void InviteGuildMember(); // 邀请公会成员
    void ModifiyGuildManifesto(char* szManifesto); //修改帮派宣言

    bool IsCorpMaster() {   return m_GuildInfo.m_nMasterID  == GetBotDBID(); } // 
    bool IsCorpMaster(unsigned int Id) {   return m_GuildInfo.m_nMasterID  == Id; } 
    bool IsHaveGuild()  {   return m_GuildInfo.m_nID != 0;  }
    char* GetGuildName(){   return m_GuildInfo.m_szName;    }
    bool IsMember(const char* name);
    bool HaveEnoughMoney(){ return GetBotMoney() < CreateGuildGold;}
    char* GetBotNameNum();
    bool IsGuildMaster();

public: // 消息函数
    void OnMsgAckGuildInfo(Msg *pMsg);
    void OnMsgGuildTellDismiss(Msg *pMsg);
    void OnMsgAckGuildManifestoInfo(Msg* pMsg);
    void OnMsgGuildTellLeave(Msg* pMsg);
    void OnMsgGuildReqInvite(Msg* pMsg);
    void OnMsgGuildTellLevel(Msg* pMsg);
    void OnMsgGuildTellJoin(Msg* pMsg);
    void OnMsgAckGuildCreate(Msg* pMsg);
protected:
	DWORD m_dwRunTimeSpace;
	DWORD m_dwType;							//GuildType 类型
private:
    SGuildInfo              m_GuildInfo;    // 公会信息
    GuildMemberContainer    m_GuildMembers; // 公会成员信息
    GuildMemberByNameContainer    m_GuildMemberByName; // 公会成员信息
    short                   m_InviteNumber;
    std::string             m_ApplicationGuildName; // 申请的公会名  
};

#endif



/************************************************************************

1. 进入游戏,判断机器人帐号,  能被20整除的作为结义长, 能被100整除的作为军团长
2. 判断自己身份,
	结义长->判断当前人数-> 达到最大解散 否则邀请加入
	军团长->判断当前结义个数->达到最大解散,否则申请加入
	普通->应该有申请加入结义的功能
3. 转让帮会长以后需要被邀请回来，重新做回帮会长

************************************************************************/