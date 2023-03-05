#ifndef __CAMPBATTLEPLAYERHANDLE_H__
#define __CAMPBATTLEPLAYERHANDLE_H__

private:

public:


    // 消息处理
    bool ProcessCampBattleMsg( Msg* pMsg ); 

    // 请求阵营战场所以玩家信息
    void OnMsgCampBattlePlayerReq( Msg* pMsg );

    // 请求离开战场
    void OnMsgLeaveCampBattleReq( Msg* pMsg );

    // 加入战场, 传送到NPC处
    void OnMsgEnterCampBattleAck( Msg* pMsg );

    // 请求报名阵营战场
    void OnMsgCampBattleSignUpReq( Msg* pMsg );

    // 请求进入阵营战场
    void OnMsgEnterCampBattleReq( Msg* pMsg );

	void OnMsgGetGlobalDBBattleSumReq( Msg* pMsg );

    ////////////////////////////////////////////////
    void KillCampBattleMonster( int nMonsterID );

    // 查询国家战场报名
    void QueryCampBattleSignUp( unsigned char uchBattleType ); 

#endif