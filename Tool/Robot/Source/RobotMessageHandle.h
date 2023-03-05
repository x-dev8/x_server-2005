
//////////////////////////////////////////////////////////////////////////
// MessageHandle ��Ӧ��Ϣ
//////////////////////////////////////////////////////////////////////////
virtual void OnMsgUseSkillHintMessage(Msg* pMsg);
virtual void OnMsg_AckLogin( Msg* pMsg );
virtual void OnMsg_SwitchGate( Msg* pMsg );
virtual void OnMsg_AckChar( Msg* pMsg );
virtual void OnMsgAckEnterWorld( Msg* pMsg );
virtual void OnMsg_VerifyPos( Msg* pMsg );
virtual void OnMsg_EndAckChar( Msg* pMsg );
virtual void OnMsg_CreateChar( Msg* pMsg );
virtual void OnMsg_LoginWait( Msg* pMsg );
virtual void OnMsg_InquireInvitee( Msg* pMsg );
virtual void OnMsg_Chat( Msg* pMsg );
virtual void OnMsg_AttrChanged( Msg* pMsg );
virtual void OnMsg_PlayerEnterSight( Msg* pMsg );
virtual void OnMsg_PlayerEnterSightPack( Msg* pMsg );
virtual void OnMsg_UnPlayerEnterSight( Msg* pMsg );
virtual void OnMsg_ExitSight( Msg* pMsg );
virtual void OnMsg_AckCharInfo( Msg* pMsg );
virtual void OnMsg_PlayerMovingPos( Msg* pMsg );
virtual void OnMsg_PlayerMovingPosAndDir( Msg* pMsg );
virtual void OnMsg_UnPlayerVerifyPos( Msg* pMsg );
virtual void OnMsg_PlayerVerifyPos( Msg* pMsg);
virtual void OnMsg_UnPlayerMovingToPos( Msg* pMsg );
virtual void OnMsg_UnPlayerClosingToLockTarget( Msg* pMsg );
virtual void OnMsg_PosChange( Msg* pMsg );
virtual void OnMsg_SawSomeOnDead( Msg* pMsg );
virtual void OnMsgSeeAttack3( Msg* pMsg );
virtual void OnMsg_GetItem( Msg* pMsg );
virtual void OnMsg_QueryBargaining( Msg* pMsg );
virtual void OnMsg_AckBargaining( Msg* pMsg );
virtual void OnMsgChangeMap( Msg* pMessage );
virtual void OnMsgChangeEquip(Msg* pMsg);
virtual void OnMsgDropItem(Msg* pMsg);
virtual void OnMsgLevelUp(Msg* pMsg);
virtual void OnMsgChangePKFlag(Msg *pMsg);
virtual void OnMsgExit(Msg *pMsg);
virtual void OnMsg_TellMap_NpcQuest(Msg* pMsg);
virtual void OnMsg_AllNpcInTheMap(Msg* pMsg);
virtual void OnMsgInviteeTeam(Msg* pMsg);
virtual void OnMsgConnectGateOverTime(Msg* pMsg);
virtual void OnMsgAckResult(Msg* pMsg);
//virtual void OnMsgMapInfoReady(Msg* pMsg);
virtual void OnMsgPackageitemAccessAck(Msg *pMsg);
virtual bool OnMsgPickPackageItemAck (Msg* pMsg);
virtual void OnMsg_Ping(Msg* pMsg);
virtual void OnMsgMoneyChange(Msg *pMsg);
virtual void OnMsgHitchMoveTargetPos(Msg *pMsg);
virtual void OnMsgCanControlMoving(Msg *pMsg);
virtual void OnMsgMoveGoods(Msg* pMsg);
virtual void OnMsgAckFriendList(Msg* pMsg);
virtual void OnMsgAckDelFriend(Msg* pMsg);
virtual void OnMsgInviteAddRelationReq(Msg* pMsg);
virtual void OnMsgAckAddFriend(Msg* pMsg);
virtual void OnDisconnectFromServer();
virtual void OnMsgItemEnterMySight( Msg* pMsg );
virtual void OnMsgPackageViewAck( Msg* pMsg );
virtual void OnMsgGetPet(Msg* pMsg);