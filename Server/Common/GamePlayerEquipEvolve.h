/********************************************************************
    Filename:    GamePlayerEquipEvolve.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

void OnEquipEvolve          ( Msg* pMsg );
void OnMsgItemComposeReq    ( Msg* pMsg ); // 5合一
void OnMsgItemComposeGem    ( Msg* pMsg ); // 宝石升级和洗石剂合成
void OnQueryNewCompound     ( Msg* pMsg ); // 合成配方 参考
void OnMsgRecipeCompoundItem( Msg* pMsg ); // 生活技能合成配方
void OnMsgEquipUpgradeReq   ( Msg* pMsg ); // 装备升阶
void OnMsgSuitLevelUpReq    ( Msg* pMsg ); // 套装升阶
void OnMsgSuitChangeReq     ( Msg* pMsg ); // 套装转换
void OnMsgSuitElementMoveReq( Msg* pMsg ); // 五行转移
void OnMsgItemReclaim       ( Msg* pMsg ); // 装备回收
void OnMsgZhuJiangCompose	( Msg* pMsg ); // 主将鉴图合成
void OnMsgTransferStar		( Msg* pMsg ); //转星

void _ProcessEquipLevelUp  ( MsgEquipEvolve* pEquipEvolve ); // 升星
void _ProcessEquipIdentify ( MsgEquipEvolve* pEquipEvolve ); // 鉴定
void _ProcessEquipUnknowIdentify ( MsgEquipEvolve* pEquipEvolve ); // 未知鉴定

void _ProcessStiletto      ( MsgEquipEvolve* pEquipEvolve ); // 打孔
void _ProcessGemInlay      ( MsgEquipEvolve* pEquipEvolve ); // 镶嵌
void _ProcessGemTakeDown   ( MsgEquipEvolve* pEquipEvolve ); // 拆卸
void _ProcessGemReplace    ( MsgEquipEvolve* pEquipEvolve ); // 替换
void _ProcessSoulStamp     ( MsgEquipEvolve* pEquipEvolve ); // 灵魂铭刻

void _ProcessEquipOpenLight  ( MsgEquipEvolve* pEquipEvolve ); // 鎏金
void _ProcessEquipReOpenLight( MsgEquipEvolve* pEquipEvolve ); // 鎏金回炉

void _ProcessEquipMaintain      ( MsgEquipEvolve* pEquipEvolve ); // 保值
void _ProcessEquipMaintainCross ( MsgEquipEvolve* pEquipEvolve ); // 跨级保值

void _ProcessEquipCharmAbsorb   ( MsgEquipEvolve* pEquipEvolve ); // 符文吸蓝
void _ProcessEquipAmuletAbsorb  ( MsgEquipEvolve* pEquipEvolve ); // 护身符上色

unsigned char ProcessSkillSuitLevelUp  ( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp );
unsigned char ProcessElementSuitLevelUp( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp );

unsigned char ProcessSkillSuitChange   ( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial );
unsigned char ProcessElementSuitChange ( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial );
