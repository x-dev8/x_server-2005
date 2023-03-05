#ifndef __PLAYERMESSAGEHANDLE_H__
#define __PLAYERMESSAGEHANDLE_H__

public:
    virtual bool  ProcessMsg( Msg* pMsg );  // ��������

	void SendMessageToClient( Msg* pMessage );
    void SendErrorToClient( uint16 nErrorCode, int32 nValue = 0 );
    template< class T >
    void SendOperateAckToClient( uint8 nResult )
    {
        T xAck;
        xAck.uchResult = nResult;
        SendMessageToClient( &xAck );
    }
	template< class T >
	void SendOperateAckToClient( uint8 nResult ,uint8 nWarxishu,uint8 nGuildxishu)
	{
		T xAck;
		xAck.uchResult = nResult;
		xAck.uchWarxishu = nWarxishu;
		xAck.unhGuildxishu = nGuildxishu;

		SendMessageToClient( &xAck );
	}

    void SendQuestFail          ( int16 questID );
    void OnMsgAckJinDing                ( Msg* pMsg );
    void OnMsgAckSwitchStage( const CS2GSSwitchStageAck* pMsg );
    void OnMsgS2SSwitchGate( const S2SSwitchGate* pMsg );
    void OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame ); // �˳�
    void OnExitTeam                     ( Msg* pMsg ); // �ͻ��˷���������Ϣ�����뿪����
    bool OnGetCharacter         ( Msg* pMsg ); // ��ȡ��ɫ
    void OnEnterWorld           ( Msg* pMsg ); // ������Ϸ����
    void OnCreateChar           ( Msg* pMsg ); // ������ɫ
    void OnMsgReqCreateCheckName( Msg* pMsg ); // ����Ƿ�����
	void OnMsgNewChangeNameReq( Msg* pMsg );
    void OnMsgAckCreateCheckName( Msg* pMsg ); // ���ؼ���Ƿ�����
	void OnDBMsgChangeNameAck( Msg* pMsg );
    void OnDeleteChar           ( Msg* pMsg ); // ɾ����ɫ
    void OnCancelDelChar        ( Msg* pMsg ); // ȡ��ɾ����ɫ
    void OnQueryCharInfo        ( Msg* pMsg ); // ��ѯ��ɫ����
    void OnReqUpAttrLevel       ( Msg* pMsg ); // ����������������
    void OnRefreshHotKey        ( Msg* pMsg ); // ���½�ɫ��ݼ�
    void OnReqAttackGround      ( Msg* pMsg ); // ���󹥻�����  
    void OnReqUpSkill           ( Msg* pMsg ); // ������������
    void OnDBAckCharEnd         ( Msg* pMsg ); // ��ѯ���ݿ⣬��Ӧ�ʺŵ����н�ɫ�������
    void OnDBAckStateCheck      ( Msg* pMsg ); // �ش����ʺŵ���Ϸ״̬
    void OnDBAckLogin           ( Msg* pMsg ); // �ش����ݿ��¼
    void OnDBAckChar            ( Msg *pMsg ); // �ش��ɫ��Ϣ
    void OnDBAckCreateChar      ( Msg* pMsg ); // �ش𴴽���ɫ
    void OnDBAckDeleteChar      ( Msg* pMsg ); // �ش�ɾ����ɫ
    void OnDBAckCancelDelChar   ( Msg* pMsg ); // �ش�ȡ��ɾ����ɫ
    void OnMsgAckResult         ( Msg* pMsg ); // ��Ӧ���
    void OnDBAckEnterWorld      ( Msg* pMsg ); // �ش������Ϸ����
    void OnMoveGoods            ( Msg* pMsg ); // �ƶ���Ʒ
    void OnUseGoods             ( Msg* pMsg ); // ʹ����Ʒ    
    void OnBuyOrSellGoods       ( Msg *pMsg );
    void OnBuyGoods             ( Msg *pMsg );
    void OnSellGoods            ( Msg *pMsg );
    void OnRelive               ( Msg* pMsg ); // ���󸴻�
    void OnDropItem             ( Msg* pMsg ); // ������Ʒ
    void OnChatMsg              ( Msg* pMsg ); // chat msg
    void OnQueryServerInfo      ( Msg* pMsg ); // system query server information
    void OnMsgQueryContinuousSkill( Msg* pMsg ); // ����ĳ����ɫ���ϵļ���
    void OnMsgMapLoaded         ( Msg* pMsg ); // �ͻ��˵�ͼ�������
    void OnMsgQueryHPInfo       ( Msg* pMsg ); // �����ѯĳ����ɫ��Ѫ��
    void OnQueryScript          ( Msg* pMsg ); // ����npc�ű�
    void OnScriptCancel         ( Msg* pMsg ); // ȡ���ű�
	void OnLoadCampBattleData( Msg* pMsg );

	void OnCreateTeam				 ( Msg* pMsg ); // �������˶���
    void OnRequestTeam               ( Msg* pMsg ); // �ͻ��˷��������������������Ϣ
    void OnMsgTeamInvitee            ( Msg* pMsg );
    void OnKickFromTeam              ( Msg* pMsg ); // �ͻ��˷���������ϢҪ���˴Զ��������߳�ȥ
    void OnAckMsgInquireInvitee      ( Msg* pMsg ); // ѯ�ʱ������ߵķ�����Ϣ
    void OnAckMsgAssignTeam          ( Msg* pMsg ); // ���ص���ӷ���
    void OnReqChangeAssignMode       ( Msg* pMsg );
    void OnReqChangeAssignItemLevel  ( Msg* pMsg );
    void OnReqChangeAssignMode_Answer( Msg* pMsg );
    void OnReqUpgradeTeam            ( Msg* pMsg ); // ���������ӳ�
	void OnReqTeamFollow             ( Msg* pMsg ); // ����������
	void OnAckTeamFollow             ( Msg* pMsg ); // �ظ��������
	void OnHeaderCancelTeamFollow    ( Msg* pMsg ); // �ӳ�ȡ���������
	void OnCancelTeamFollow			 ( Msg* pMsg ); // ȡ���������
	void OnDisbandTeam				 ( Msg* pMsg ); // ��ɢ����

    void OnChangeDir                 ( Msg* pMsg ); // ת��    
    void OnEquipNew                  ( Msg* pMsg ); // װ��
    void OnUnEquip                   ( Msg* pMsg ); // жװ
    void OnEquipToWhere              ( Msg* pMsg );
    void OnSwitchSuit                ( Msg* pMsg ); // ����װ    

    //////////////////////////////////////////////////////////////////////////
    void OnMoveStorageItem           ( Msg* pMsg ); // �ֿ�    
    void MovePackToStorage           ( Msg* pMsg ); 
    void MoveStorageToPack           ( Msg* pMsg ); 
    void MoveStorageToStorage        ( Msg* pMsg ); 


    void OnMoveStorageMount          ( Msg* pMsg ); // ����ֿ�  
    void MoveMountToStorage          ( Msg* pMsg ); 
    void MoveStorageToMount          ( Msg* pMsg ); 

    //////////////////////////////////////////////////////////////////////////

    void OnLearnSkill                ( Msg* pMsg ); // ѧϰ����
    void OnLearnAllSkill             ( Msg* pMsg ); // ѧϰ����    
    void OnQueryCompound             ( Msg* pMsg ); // �ϳ�
    void OnChange_OwnAttribute       ( Msg* pMsg );    
    void OnMoveIntensifyItem         ( Msg* pMsg );
    void OnAckScriptShowQuestDlg     ( Msg* pMsg );
    void OnReqQuestInfo              ( Msg* pMsg );
    void OnGetShopCenter          ( Msg* pMsg );
    void OnGetShop                ( Msg* pMsg );
    void OnAbandonTask            ( Msg* pMsg );
    void OnQueryScriptVar         ( Msg* pMsg );
    void OnMsgMoveReduceItem      ( Msg* pMsg ); // �ֽ�
    void OnMsgSplitItem           ( Msg* pMsg );
    void OnMsgUnSoulBound         ( Msg* pMsg );
    void OnMsgMoveUnSoulBound     ( Msg* pMsg );
    void OnLockItemReq            ( Msg* pMsg ); // ���������Ʒ
    void OnUnLockItemReq          ( Msg* pMsg ); // ���������Ʒ����
    void OnCheckUnLockItemReq     ( Msg* pMsg ); // ȷ����Ʒ����
    void OnMsgChangeItemPos       ( Msg* pMsg ); // ���󽻻�������Ʒ
    void OnReqEctypeMapInfo       ( Msg* pMsg );
    void OnReqFlytomap            ( Msg* pMsg );    
    void OnMsgModifyHelpFlag      ( Msg* pMsg ); // ����
    void OnMsgAskExecuteScript    ( Msg* pMsg ); // �ű���Ϣ
    void OnChangePKFlag           ( Msg* pMsg );
    void OnMsgReLive              ( Msg* pMsg );
    void OnMsgShowHelmet          ( Msg* pMsg );
    void OnMsgShowSignature       ( Msg* pMsg );

    void OnMsgSelectChannel          ( Msg* pMsg );
    void OnMsgRepairItem             ( Msg* pMsg ); // ����װ��
    void OnMsgSpecialRepairItem      ( Msg* pMsg );
    void OnMsgPeekPlayerEquip        ( Msg* pMsg );
    void OnMsgForSkillExpToSkill     ( Msg* pMsg );
    void OnMsgSetTipVar              ( Msg* pMsg );
    void OnMsgChangeDrome            ( Msg* pMsg );
    void OnMsgReqSkillAttack         ( Msg* pMsg );
    void OnMsgLockTarget             ( Msg* pMsg );  
    void OnMsgAttackLockTarget       ( Msg* pMsg );
    void OnMsgChangeTitle            ( Msg* pMsg ); // �ƺ�
    void OnMsgAddTitleReq            ( Msg* pMsg );
    void OnMsgReqDuel                ( Msg* pMsg ); // �д�
    void OnMsgAckDuel                ( Msg* pMsg );
    void OnMsgDuelStop               ( Msg* pMsg );
    void OnMsgDuelStart              ( Msg* pMsg );
    void OnShopCenterBuy             ( Msg* pMsg );
    void OnMsgReqRmbOp               ( Msg* pMsg );
    void OnResetItemTime             ( Msg* pMsg );
    void OnMsgReqChangeSubAction     ( Msg* pMsg );
    void OnMsgCostSilverRepair       ( Msg* pMsg ); // Զ������
    void OnMsgAckGraphiccode         ( Msg* pMsg );
    void OnMsgAckNumberCode          ( Msg* pMsg );
    bool OnMsgInviterResult          ( Msg* pMsg );
    bool OnMsgCleanUpBag             ( Msg* pMsg );
    void OnS2STransmitResult         ( Msg* pMsg );
    void OnMsgChangeMountName        ( Msg* pMsg );
    void OnMsgReturnToCharacterServer( Msg* pMsg );
    void OnMsgPetCommand             ( Msg* pMsg );
    void OnMsgRemovePublishMessage   ( Msg* pMsg );
    void OnMsgAckApplySAndT          ( Msg* pMsg );
    void OnMsgRetSandT               ( Msg* pMsg );
    void OnMsgDisDrome               ( Msg* pMsg );
	void OnMsgDisDrome1              ( Msg* pMsg );//zhuxincong ����
    void OnMsgDisHitch               ( Msg* pMsg );
    void OnReqCancelSkill            ( Msg* pMsg );

    //�����
    void OnMsgPackageViewReq         ( Msg* pMsg );
    void OnMsgPackageViewEnd         ( Msg* pMsg );
    void OnMsgPickPackageItemReq     ( Msg* pMsg );
    void OnMsgPackageItemBoultAck    ( Msg* pMsg );
    void OnMsgPackageItemAssignReq   ( Msg* pMsg );
    void OnMsgPackageItemAccessReq   ( Msg* pMsg );

    void OnMsgStorageMoneyReq        ( Msg* pMsg ); // �ֿ��ǮȡǮ
    bool OnMsgQueryTargetOfTargetReq ( Msg* pMsg );
    void OnMsgChangeProtectLockTimeReq( Msg* pMsg ); // ���ı�����ʱ��
    void OnMsgLuckRewardReq           ( Msg* pMsg );
    void OnDrawFromPlatformAck        ( Msg* pMsg );
    void OnMsgTreasureBoxReq          ( Msg* pMsg );
    void OnS2SCallGraphic             ( Msg* pMsg );
    void OnMsgCheckCheatAck           ( Msg* pMsg );
    void OnMsgGetProcesslistAck       ( Msg* pMsg );
    void OnMsgReceiveQuestReq         ( Msg* pMsg );
    void OnMsgResetPubQuestReq        ( Msg* pMsg );
    void OnMsgClientTeamInfo          ( Msg* pMsg );
    void OnMsgMoveStarReq             ( Msg* pMsg );
    void OnMsgSuitElementCheckupReq   ( Msg* pMsg );
    //void OnMsgMoneyItemExchange       ( Msg* pMsg );    
    void OnMsgOnLineRewardReq         ( Msg* pMsg );
    void OnMsgBuyBackItemReq          ( Msg* pMsg );
    void OnMsgBuyBackItemListReq      ( Msg* pMsg );
    void OnMsgBattleSignUpReq         ( Msg* pMsg );
    void OnMsgChangeNameReq           ( Msg* pMsg );
	void OnGS2CSUpdateAntiaddictionInfoAck( Msg* pMsg );
    void OnMsgCancelBuff              ( Msg* pMsg );
    void OnMsgJiFengShopItemsListReq  ( Msg* pMsg );
    void OnMsgJiFengShopItemsGain     ( Msg* pMsg );
    void OnDBMsgJiFengShopItemsListAck( Msg* pMsg );
    void OnDBMsgJiFengShopItemsGainAck( Msg* pMsg );
    void OnMsgUpdateTradeShopConfigReq( Msg* pMsg );
    void OnMsgEnterTeamBattleAck      ( Msg* pMsg );    
    void OnMsgQueryExpression         ( Msg* pMsg );

    ////����CenterServer����������Ϣ
    void OnMsgSendMailReq             ( Msg* pMsg );
    void OnMsgOpMailReq               ( Msg* pMsg );

    void OnMsgMoveStarLevelUpReq      ( Msg* pMsg );

    ////////
    void OnMsgLeaveBattleReq          ( Msg* pMsg );
    void OnMsgQueryBattleTeamInfoReq  ( Msg* pMsg );
    void OnMsgQueryTeamRecordReq      ( Msg* pMsg );
    void OnMsgQueryBattleSignUpTimeReq( Msg* pMsg );

    //void OnMsgCharacterLevelUp        ( Msg* pMsg );    //��������
    void OnMsgMountPotential          ( Msg* pMsg );    //�������Ǳ����
    void OnMsgMountBreed              ( Msg* pMsg );    //���ﷱֳ
    void OnMsgSetOfflineHook          ( Msg* pMsg );    //���߹һ�
    void OnMsgGetOfflineHookExp       ( Msg* pMsg );    //���߹һ�����
    void OnMsgReqDoubleExp            ( Msg* pMsg );    //����˫������
	void OnMsgMountStrengthen		  ( Msg* pMsg );	//����ǿ��
    
    void OnMsgCharAssignPotential     ( Msg* pMsg );    //�������Ǳ����
    void OnMsgLearnXinFa              ( Msg* pMsg );    //����ѧϰ�ķ�

    void OnMsgReqGotOnDrome           ( Msg* pMsg );   
    void OnMsgReqGotOnDromeAck        ( Msg* pMsg );  
    void OnMsgReqGotOffDrome          ( Msg* pMsg );  
	void OnMsgRiderOffDrome           (Msg* pMsg);

    void OnMsgReqDoneQuest            ( Msg* pMsg ); 

    //////////////////////////////////////////////////////////////////////////
    // �������
    void OnMsgChangePetName           ( Msg* pMsg );
    void OnMsgPetPotential            ( Msg* pMsg );
    void OnMsgChangePet               ( Msg* pMsg );
    void OnMsgPetSavvyUp              ( Msg* pMsg );

    void OnMsgPetBreedReq             ( Msg* pMsg );
    void OnMsgPetBreedChoice          ( Msg* pMsg );
    void OnMsgPetBreedLock            ( Msg* pMsg );
    void OnMsgPetBreedCancelLock      ( Msg* pMsg );
    void OnMsgPetBreedConfirm         ( Msg* pMsg );
    void OnMsgPetBreedCancelReq       ( Msg* pMsg );
    void OnMsgPetBreedAcquire         ( Msg* pMsg );

    void OnMsgViewActivePet           ( Msg* pMsg );

    void OnDBMsgPetBreedQueryAck      ( Msg* pMsg );

    //////////////////////////////////////////////////////////////////////////
    //  ���˳ɾ����
    void OnMsgReqAchieveData          ( Msg* pMsg );
    void OnMsgReqAchieveReward        ( Msg* pMsg );
    
    void OnMsgUpdateGuideReq          ( Msg* pMsg );

    void OnMsgReqPressKeySuit         ( Msg* pMsg ); // ����һ����װ
    void OnMsgPressKeySuit            ( Msg* pMsg ); // ����һ����װ
    void OnMsgPressKeySuitName        ( Msg* pMsg ); // ����һ����װ����
    void OnMsgEquipPressKeySuit       ( Msg* pMsg ); // װ��һ����װ
    
    //M���ͼ
    void OnMsgRequestGotoResourcePos  ( Msg* pMsg );
    void OnMsgReqOffNpcShip           ( Msg* pMsg );
    void OnMsgOfflineFightOp          ( Msg* pMsg );

    //////////////////////////////////////////////////////////////////////////
    void OnMsgSawTalkReq              ( Msg* pMsg );
    void OnMsgPlayMovieAck            ( Msg* pMsg );    // ������Ƶ�Ļ�Ӧ��Ϣ���ͻ���׼�����ˣ����Է�CG��
    void OnMsgEndEventReq			  ( Msg* pMsg );

    void OnMsgMailListReq			  ( Msg* pMsg );
    void OnMsgReqIdentifyData		  ( Msg* pMsg );

    void OnMsgEquipTalisman           ( Msg* pMsg );
    void OnMsgUnEquipTalisman         ( Msg* pMsg );
	//////////////////////////////////////san guo add:////////////////////////////
	void OnMsgBianShen				  ( Msg* pMsg );			// ��������Ŀͻ�������Э�鴦��
	void OnMsgFlyToTPHJ				  ( Msg* pMsg );			// ̫ƽ�þ�

	void OnMsgChangeToBiaocheReq	  ( Msg* pMsg );
	void OnMsgRestoreFromBiaocheReq   ( Msg* pMsg );
	void OnMsgChangeHeroType		  ( Msg* pMsg );
	void OnMsgAckLevelUp			  (	Msg* pMsg );
	void OnMsgAckActiveLimit		  (	Msg* pMsg );
	void OnMsgAckLimitInfo			  ( Msg* pMsg );

	//
	void OnDBMsgSetBillingMoney       ( Msg* pMsg );
	void OnMsgFlytoKingdom            ( Msg* pMsg );

	
	void OnDBMsgSetConsumeScore       ( Msg* pMsg );            //���û���

	void OnMsgUnBindEquipReq		  ( Msg* pMsg );			//װ�����

	void OnMsgAskForPresent			  ( Msg* pMsg );		    //SN������Ʒ
	void OnMsgRandAttribute			  ( Msg* pMsg );

	void OnMsgAddPetEquip			  ( Msg* pMsg );
	void OnMsgRemovePetEquip		  ( Msg* pMsg );
	void OnMsgPetCompose			 ( Msg* pMsg );

	void OnMsgCardAchieve			  ( Msg* pMsg );

	void OnMsgOpenBagStorage			( Msg* pMsg );

	void OnMsgSevenDaysData			  ( Msg* pMsg );

	void OnMsgAskSevenDaysTask		  ( Msg* pMsg );
	void OnMsgAskSevenDaysReward	  ( Msg* pMsg );

	void OnMsgChangeChannel			  ( Msg* pMsg );

	void OnMsgClearTeamMapReq		  ( Msg* pMsg );

	void OnMsgAskGetSalary			  ( Msg* pMsg );
	void OnAskAdvancement		      ( Msg* pMsg );
	void OnMsgShowRankTitle			  ( Msg* pMsg );
	void OnMsgReConnect				  ( Msg* pMsg );

	void OnMsgAskHuntingList		  ( Msg* pMsg );
	void OnMsgHuntingReFresh		  ( Msg* pMsg );
	void OnMsgAcceptHuntingQuest	  ( Msg* pMsg );
	void OnMsgFlyToPositionAck		  ( Msg* pMsg );
	void OnMsgGetThreeDayItem		   ( Msg* pMsg );

	void OnMsgUpdateYuanBaoDataReq ( Msg* pMsg );

	void OnDB2GSUpdateYuanBaoData( Msg* pMsg );

	void OnMsgMountMoveStar( Msg* pMsg );

	void OnDB2GSUpdatePlayerPoint( Msg* pMsg );

	void OnMsgLeaveExpReq( Msg* pMsg );
	void OnMsgGetLeaveExpReq( Msg* pMsg );
#endif