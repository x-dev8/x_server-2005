#ifndef __GUILDBOT_H__
#define __GUILDBOT_H__
#include "stdafx.h"

#include "NormalBot.h"
#include <string>
#include <vector>
#include <string>
#include "GameDefineBot.h"
//����.���Ż�����
// ����������Ҫ��Ǯ��
#define CreateGuildGold ( 500000 )

class CGuildBot : public CNormalBot
{
public:
    enum EGuildType
    {
        EGT_Init        = 0x0,				// δ��ʼ��
        EGT_Comment     = 0x1,				// ��ͨ��Ա
        EGT_TongMaster  = 0x2,				// ����
        EGT_CorpMaster	= 0x4,				// ���ɳ�
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

public: // ����
    void InitBotGuildType();    // ����GuildType
    void InitGuildData();       // ��ʼ����������

	void RunGuildCorps();       // Run���ɳ��߼�
	void RunGuildTong();        // Run�����߼�
	void RunGuildComment();     // Run��ͨ��Ա�߼�
    

    void ExitGuild();           // ��ɢ����
    void DisbandGuild();        // ��ɢ����
    void CessionGuildMaster();  // ת�û᳤
    bool CreateGuild(char* szGuildName);  // ��������
    void BanGuildMember(int MemberDBId);  // �߳�����Ա
    void InviteGuildMember(); // ���빫���Ա
    void ModifiyGuildManifesto(char* szManifesto); //�޸İ�������

    bool IsCorpMaster() {   return m_GuildInfo.m_nMasterID  == GetBotDBID(); } // 
    bool IsCorpMaster(unsigned int Id) {   return m_GuildInfo.m_nMasterID  == Id; } 
    bool IsHaveGuild()  {   return m_GuildInfo.m_nID != 0;  }
    char* GetGuildName(){   return m_GuildInfo.m_szName;    }
    bool IsMember(const char* name);
    bool HaveEnoughMoney(){ return GetBotMoney() < CreateGuildGold;}
    char* GetBotNameNum();
    bool IsGuildMaster();

public: // ��Ϣ����
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
	DWORD m_dwType;							//GuildType ����
private:
    SGuildInfo              m_GuildInfo;    // ������Ϣ
    GuildMemberContainer    m_GuildMembers; // �����Ա��Ϣ
    GuildMemberByNameContainer    m_GuildMemberByName; // �����Ա��Ϣ
    short                   m_InviteNumber;
    std::string             m_ApplicationGuildName; // ����Ĺ�����  
};

#endif



/************************************************************************

1. ������Ϸ,�жϻ������ʺ�,  �ܱ�20��������Ϊ���峤, �ܱ�100��������Ϊ���ų�
2. �ж��Լ����,
	���峤->�жϵ�ǰ����-> �ﵽ����ɢ �����������
	���ų�->�жϵ�ǰ�������->�ﵽ����ɢ,�����������
	��ͨ->Ӧ��������������Ĺ���
3. ת�ð�᳤�Ժ���Ҫ������������������ذ�᳤

************************************************************************/