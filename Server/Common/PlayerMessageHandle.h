#ifndef __PLAYERMESSAGEHANDLE_H__
#define __PLAYERMESSAGEHANDLE_H__

public:
    virtual bool  ProcessMsg( Msg* pMsg );  // 处理命令

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
    void OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame ); // 退出
    void OnExitTeam                     ( Msg* pMsg ); // 客户端发过来的消息请求离开队伍
    bool OnGetCharacter         ( Msg* pMsg ); // 获取角色
    void OnEnterWorld           ( Msg* pMsg ); // 进入游戏世界
    void OnCreateChar           ( Msg* pMsg ); // 创建角色
    void OnMsgReqCreateCheckName( Msg* pMsg ); // 检测是否重名
	void OnMsgNewChangeNameReq( Msg* pMsg );
    void OnMsgAckCreateCheckName( Msg* pMsg ); // 返回检测是否重名
	void OnDBMsgChangeNameAck( Msg* pMsg );
    void OnDeleteChar           ( Msg* pMsg ); // 删除角色
    void OnCancelDelChar        ( Msg* pMsg ); // 取消删除角色
    void OnQueryCharInfo        ( Msg* pMsg ); // 查询角色数据
    void OnReqUpAttrLevel       ( Msg* pMsg ); // 请求升级基本属性
    void OnRefreshHotKey        ( Msg* pMsg ); // 更新角色快捷键
    void OnReqAttackGround      ( Msg* pMsg ); // 请求攻击地面  
    void OnReqUpSkill           ( Msg* pMsg ); // 请求升级技能
    void OnDBAckCharEnd         ( Msg* pMsg ); // 查询数据库，对应帐号的所有角色数据完成
    void OnDBAckStateCheck      ( Msg* pMsg ); // 回答检测帐号的游戏状态
    void OnDBAckLogin           ( Msg* pMsg ); // 回答数据库登录
    void OnDBAckChar            ( Msg *pMsg ); // 回答角色信息
    void OnDBAckCreateChar      ( Msg* pMsg ); // 回答创建角色
    void OnDBAckDeleteChar      ( Msg* pMsg ); // 回答删除角色
    void OnDBAckCancelDelChar   ( Msg* pMsg ); // 回答取消删除角色
    void OnMsgAckResult         ( Msg* pMsg ); // 响应结果
    void OnDBAckEnterWorld      ( Msg* pMsg ); // 回答进入游戏世界
    void OnMoveGoods            ( Msg* pMsg ); // 移动物品
    void OnUseGoods             ( Msg* pMsg ); // 使用物品    
    void OnBuyOrSellGoods       ( Msg *pMsg );
    void OnBuyGoods             ( Msg *pMsg );
    void OnSellGoods            ( Msg *pMsg );
    void OnRelive               ( Msg* pMsg ); // 请求复活
    void OnDropItem             ( Msg* pMsg ); // 丢弃物品
    void OnChatMsg              ( Msg* pMsg ); // chat msg
    void OnQueryServerInfo      ( Msg* pMsg ); // system query server information
    void OnMsgQueryContinuousSkill( Msg* pMsg ); // 请求某个角色身上的技能
    void OnMsgMapLoaded         ( Msg* pMsg ); // 客户端地图载入完毕
    void OnMsgQueryHPInfo       ( Msg* pMsg ); // 请求查询某个角色的血条
    void OnQueryScript          ( Msg* pMsg ); // 请求npc脚本
    void OnScriptCancel         ( Msg* pMsg ); // 取消脚本
	void OnLoadCampBattleData( Msg* pMsg );

	void OnCreateTeam				 ( Msg* pMsg ); // 创建单人队伍
    void OnRequestTeam               ( Msg* pMsg ); // 客户端发过来的请求加入队伍的消息
    void OnMsgTeamInvitee            ( Msg* pMsg );
    void OnKickFromTeam              ( Msg* pMsg ); // 客户端发过来的消息要把人丛队伍里面踢出去
    void OnAckMsgInquireInvitee      ( Msg* pMsg ); // 询问被邀请者的返回消息
    void OnAckMsgAssignTeam          ( Msg* pMsg ); // 返回的组队分配
    void OnReqChangeAssignMode       ( Msg* pMsg );
    void OnReqChangeAssignItemLevel  ( Msg* pMsg );
    void OnReqChangeAssignMode_Answer( Msg* pMsg );
    void OnReqUpgradeTeam            ( Msg* pMsg ); // 请求提升队长
	void OnReqTeamFollow             ( Msg* pMsg ); // 请求队伍更随
	void OnAckTeamFollow             ( Msg* pMsg ); // 回复队伍更随
	void OnHeaderCancelTeamFollow    ( Msg* pMsg ); // 队长取消队伍更随
	void OnCancelTeamFollow			 ( Msg* pMsg ); // 取消队伍更随
	void OnDisbandTeam				 ( Msg* pMsg ); // 解散队伍

    void OnChangeDir                 ( Msg* pMsg ); // 转身    
    void OnEquipNew                  ( Msg* pMsg ); // 装备
    void OnUnEquip                   ( Msg* pMsg ); // 卸装
    void OnEquipToWhere              ( Msg* pMsg );
    void OnSwitchSuit                ( Msg* pMsg ); // 切套装    

    //////////////////////////////////////////////////////////////////////////
    void OnMoveStorageItem           ( Msg* pMsg ); // 仓库    
    void MovePackToStorage           ( Msg* pMsg ); 
    void MoveStorageToPack           ( Msg* pMsg ); 
    void MoveStorageToStorage        ( Msg* pMsg ); 


    void OnMoveStorageMount          ( Msg* pMsg ); // 坐骑仓库  
    void MoveMountToStorage          ( Msg* pMsg ); 
    void MoveStorageToMount          ( Msg* pMsg ); 

    //////////////////////////////////////////////////////////////////////////

    void OnLearnSkill                ( Msg* pMsg ); // 学习技能
    void OnLearnAllSkill             ( Msg* pMsg ); // 学习技能    
    void OnQueryCompound             ( Msg* pMsg ); // 合成
    void OnChange_OwnAttribute       ( Msg* pMsg );    
    void OnMoveIntensifyItem         ( Msg* pMsg );
    void OnAckScriptShowQuestDlg     ( Msg* pMsg );
    void OnReqQuestInfo              ( Msg* pMsg );
    void OnGetShopCenter          ( Msg* pMsg );
    void OnGetShop                ( Msg* pMsg );
    void OnAbandonTask            ( Msg* pMsg );
    void OnQueryScriptVar         ( Msg* pMsg );
    void OnMsgMoveReduceItem      ( Msg* pMsg ); // 分解
    void OnMsgSplitItem           ( Msg* pMsg );
    void OnMsgUnSoulBound         ( Msg* pMsg );
    void OnMsgMoveUnSoulBound     ( Msg* pMsg );
    void OnLockItemReq            ( Msg* pMsg ); // 请求加密物品
    void OnUnLockItemReq          ( Msg* pMsg ); // 请求解密物品密码
    void OnCheckUnLockItemReq     ( Msg* pMsg ); // 确认物品解锁
    void OnMsgChangeItemPos       ( Msg* pMsg ); // 请求交换两个物品
    void OnReqEctypeMapInfo       ( Msg* pMsg );
    void OnReqFlytomap            ( Msg* pMsg );    
    void OnMsgModifyHelpFlag      ( Msg* pMsg ); // 泡泡
    void OnMsgAskExecuteScript    ( Msg* pMsg ); // 脚本消息
    void OnChangePKFlag           ( Msg* pMsg );
    void OnMsgReLive              ( Msg* pMsg );
    void OnMsgShowHelmet          ( Msg* pMsg );
    void OnMsgShowSignature       ( Msg* pMsg );

    void OnMsgSelectChannel          ( Msg* pMsg );
    void OnMsgRepairItem             ( Msg* pMsg ); // 修理装备
    void OnMsgSpecialRepairItem      ( Msg* pMsg );
    void OnMsgPeekPlayerEquip        ( Msg* pMsg );
    void OnMsgForSkillExpToSkill     ( Msg* pMsg );
    void OnMsgSetTipVar              ( Msg* pMsg );
    void OnMsgChangeDrome            ( Msg* pMsg );
    void OnMsgReqSkillAttack         ( Msg* pMsg );
    void OnMsgLockTarget             ( Msg* pMsg );  
    void OnMsgAttackLockTarget       ( Msg* pMsg );
    void OnMsgChangeTitle            ( Msg* pMsg ); // 称号
    void OnMsgAddTitleReq            ( Msg* pMsg );
    void OnMsgReqDuel                ( Msg* pMsg ); // 切磋
    void OnMsgAckDuel                ( Msg* pMsg );
    void OnMsgDuelStop               ( Msg* pMsg );
    void OnMsgDuelStart              ( Msg* pMsg );
    void OnShopCenterBuy             ( Msg* pMsg );
    void OnMsgReqRmbOp               ( Msg* pMsg );
    void OnResetItemTime             ( Msg* pMsg );
    void OnMsgReqChangeSubAction     ( Msg* pMsg );
    void OnMsgCostSilverRepair       ( Msg* pMsg ); // 远程修理
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
	void OnMsgDisDrome1              ( Msg* pMsg );//zhuxincong 上马
    void OnMsgDisHitch               ( Msg* pMsg );
    void OnReqCancelSkill            ( Msg* pMsg );

    //检包裹
    void OnMsgPackageViewReq         ( Msg* pMsg );
    void OnMsgPackageViewEnd         ( Msg* pMsg );
    void OnMsgPickPackageItemReq     ( Msg* pMsg );
    void OnMsgPackageItemBoultAck    ( Msg* pMsg );
    void OnMsgPackageItemAssignReq   ( Msg* pMsg );
    void OnMsgPackageItemAccessReq   ( Msg* pMsg );

    void OnMsgStorageMoneyReq        ( Msg* pMsg ); // 仓库存钱取钱
    bool OnMsgQueryTargetOfTargetReq ( Msg* pMsg );
    void OnMsgChangeProtectLockTimeReq( Msg* pMsg ); // 更改保护锁时间
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

    ////解析CenterServer发过来的消息
    void OnMsgSendMailReq             ( Msg* pMsg );
    void OnMsgOpMailReq               ( Msg* pMsg );

    void OnMsgMoveStarLevelUpReq      ( Msg* pMsg );

    ////////
    void OnMsgLeaveBattleReq          ( Msg* pMsg );
    void OnMsgQueryBattleTeamInfoReq  ( Msg* pMsg );
    void OnMsgQueryTeamRecordReq      ( Msg* pMsg );
    void OnMsgQueryBattleSignUpTimeReq( Msg* pMsg );

    //void OnMsgCharacterLevelUp        ( Msg* pMsg );    //人物升级
    void OnMsgMountPotential          ( Msg* pMsg );    //坐骑分配潜力点
    void OnMsgMountBreed              ( Msg* pMsg );    //坐骑繁殖
    void OnMsgSetOfflineHook          ( Msg* pMsg );    //离线挂机
    void OnMsgGetOfflineHookExp       ( Msg* pMsg );    //离线挂机经验
    void OnMsgReqDoubleExp            ( Msg* pMsg );    //请求双倍经验
	void OnMsgMountStrengthen		  ( Msg* pMsg );	//坐骑强化
    
    void OnMsgCharAssignPotential     ( Msg* pMsg );    //人物分配潜力点
    void OnMsgLearnXinFa              ( Msg* pMsg );    //人物学习心法

    void OnMsgReqGotOnDrome           ( Msg* pMsg );   
    void OnMsgReqGotOnDromeAck        ( Msg* pMsg );  
    void OnMsgReqGotOffDrome          ( Msg* pMsg );  
	void OnMsgRiderOffDrome           (Msg* pMsg);

    void OnMsgReqDoneQuest            ( Msg* pMsg ); 

    //////////////////////////////////////////////////////////////////////////
    // 宠物相关
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
    //  个人成就相关
    void OnMsgReqAchieveData          ( Msg* pMsg );
    void OnMsgReqAchieveReward        ( Msg* pMsg );
    
    void OnMsgUpdateGuideReq          ( Msg* pMsg );

    void OnMsgReqPressKeySuit         ( Msg* pMsg ); // 设置一键换装
    void OnMsgPressKeySuit            ( Msg* pMsg ); // 设置一键换装
    void OnMsgPressKeySuitName        ( Msg* pMsg ); // 更改一键换装名称
    void OnMsgEquipPressKeySuit       ( Msg* pMsg ); // 装备一键换装
    
    //M大地图
    void OnMsgRequestGotoResourcePos  ( Msg* pMsg );
    void OnMsgReqOffNpcShip           ( Msg* pMsg );
    void OnMsgOfflineFightOp          ( Msg* pMsg );

    //////////////////////////////////////////////////////////////////////////
    void OnMsgSawTalkReq              ( Msg* pMsg );
    void OnMsgPlayMovieAck            ( Msg* pMsg );    // 播放视频的回应消息，客户端准备好了，可以放CG了
    void OnMsgEndEventReq			  ( Msg* pMsg );

    void OnMsgMailListReq			  ( Msg* pMsg );
    void OnMsgReqIdentifyData		  ( Msg* pMsg );

    void OnMsgEquipTalisman           ( Msg* pMsg );
    void OnMsgUnEquipTalisman         ( Msg* pMsg );
	//////////////////////////////////////san guo add:////////////////////////////
	void OnMsgBianShen				  ( Msg* pMsg );			// 主将变身的客户端请求协议处理
	void OnMsgFlyToTPHJ				  ( Msg* pMsg );			// 太平幻境

	void OnMsgChangeToBiaocheReq	  ( Msg* pMsg );
	void OnMsgRestoreFromBiaocheReq   ( Msg* pMsg );
	void OnMsgChangeHeroType		  ( Msg* pMsg );
	void OnMsgAckLevelUp			  (	Msg* pMsg );
	void OnMsgAckActiveLimit		  (	Msg* pMsg );
	void OnMsgAckLimitInfo			  ( Msg* pMsg );

	//
	void OnDBMsgSetBillingMoney       ( Msg* pMsg );
	void OnMsgFlytoKingdom            ( Msg* pMsg );

	
	void OnDBMsgSetConsumeScore       ( Msg* pMsg );            //设置积分

	void OnMsgUnBindEquipReq		  ( Msg* pMsg );			//装备解绑定

	void OnMsgAskForPresent			  ( Msg* pMsg );		    //SN请求礼品
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