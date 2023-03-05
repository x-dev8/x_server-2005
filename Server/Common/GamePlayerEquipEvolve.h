/********************************************************************
    Filename:    GamePlayerEquipEvolve.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

void OnEquipEvolve          ( Msg* pMsg );
void OnMsgItemComposeReq    ( Msg* pMsg ); // 5��һ
void OnMsgItemComposeGem    ( Msg* pMsg ); // ��ʯ������ϴʯ���ϳ�
void OnQueryNewCompound     ( Msg* pMsg ); // �ϳ��䷽ �ο�
void OnMsgRecipeCompoundItem( Msg* pMsg ); // ����ܺϳ��䷽
void OnMsgEquipUpgradeReq   ( Msg* pMsg ); // װ������
void OnMsgSuitLevelUpReq    ( Msg* pMsg ); // ��װ����
void OnMsgSuitChangeReq     ( Msg* pMsg ); // ��װת��
void OnMsgSuitElementMoveReq( Msg* pMsg ); // ����ת��
void OnMsgItemReclaim       ( Msg* pMsg ); // װ������
void OnMsgZhuJiangCompose	( Msg* pMsg ); // ������ͼ�ϳ�
void OnMsgTransferStar		( Msg* pMsg ); //ת��

void _ProcessEquipLevelUp  ( MsgEquipEvolve* pEquipEvolve ); // ����
void _ProcessEquipIdentify ( MsgEquipEvolve* pEquipEvolve ); // ����
void _ProcessEquipUnknowIdentify ( MsgEquipEvolve* pEquipEvolve ); // δ֪����

void _ProcessStiletto      ( MsgEquipEvolve* pEquipEvolve ); // ���
void _ProcessGemInlay      ( MsgEquipEvolve* pEquipEvolve ); // ��Ƕ
void _ProcessGemTakeDown   ( MsgEquipEvolve* pEquipEvolve ); // ��ж
void _ProcessGemReplace    ( MsgEquipEvolve* pEquipEvolve ); // �滻
void _ProcessSoulStamp     ( MsgEquipEvolve* pEquipEvolve ); // �������

void _ProcessEquipOpenLight  ( MsgEquipEvolve* pEquipEvolve ); // �̽�
void _ProcessEquipReOpenLight( MsgEquipEvolve* pEquipEvolve ); // �̽��¯

void _ProcessEquipMaintain      ( MsgEquipEvolve* pEquipEvolve ); // ��ֵ
void _ProcessEquipMaintainCross ( MsgEquipEvolve* pEquipEvolve ); // �缶��ֵ

void _ProcessEquipCharmAbsorb   ( MsgEquipEvolve* pEquipEvolve ); // ��������
void _ProcessEquipAmuletAbsorb  ( MsgEquipEvolve* pEquipEvolve ); // �������ɫ

unsigned char ProcessSkillSuitLevelUp  ( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp );
unsigned char ProcessElementSuitLevelUp( MsgSuitLevelUpReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp );

unsigned char ProcessSkillSuitChange   ( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial );
unsigned char ProcessElementSuitChange ( MsgSuitChangeReq* pReq, SCharItem* pCharEquip, ItemDefine::SItemArmour* pEquipArmour, ItemDefine::SItemCheckUp* pItemCheckUp, ItemDefine::SItemCommon* pItemMaterial );
