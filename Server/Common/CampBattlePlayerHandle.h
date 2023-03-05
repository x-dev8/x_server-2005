#ifndef __CAMPBATTLEPLAYERHANDLE_H__
#define __CAMPBATTLEPLAYERHANDLE_H__

private:

public:


    // ��Ϣ����
    bool ProcessCampBattleMsg( Msg* pMsg ); 

    // ������Ӫս�����������Ϣ
    void OnMsgCampBattlePlayerReq( Msg* pMsg );

    // �����뿪ս��
    void OnMsgLeaveCampBattleReq( Msg* pMsg );

    // ����ս��, ���͵�NPC��
    void OnMsgEnterCampBattleAck( Msg* pMsg );

    // ��������Ӫս��
    void OnMsgCampBattleSignUpReq( Msg* pMsg );

    // ���������Ӫս��
    void OnMsgEnterCampBattleReq( Msg* pMsg );

	void OnMsgGetGlobalDBBattleSumReq( Msg* pMsg );

    ////////////////////////////////////////////////
    void KillCampBattleMonster( int nMonsterID );

    // ��ѯ����ս������
    void QueryCampBattleSignUp( unsigned char uchBattleType ); 

#endif