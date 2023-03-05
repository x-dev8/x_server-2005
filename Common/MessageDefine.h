/********************************************************************
    Filename:     MessageDefine.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_MESSAGEDEFINE_H__
#define __COMMON_MESSAGEDEFINE_H__

#pragma once 

#include "MeRTLibs.h"
#include "GlobalDef.h"
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "Dxsdk/d3dx9math.h"
#include "ErrorCode.h"
#include "QuestDefine.h"
#include "RelationDefine.h"
#include "GameDefinePet.h"
#include "LevelLimitDefine.h"

#ifdef GAME_CLIENT
#include "NetworkInput.h"
#endif 

#define GOODS_INFO        64        // ��Ʒ������˵���ĳ���
#define GET_GOODS_NUM_MAX 50        // ÿ��ȡ����Ʒ���������
#define BARGAINING_GOODS_MAX_NUM 10 // ���׵������
#define BinaryFlag(x) (DWORD)( (x>0) ? 1 << (x-1) : 0 )

#pragma pack( push, 1 ) 

#define TAG(x) (((x>>24)&0xff) |((x>>8)&0xff00)|((x&0xff00)<<8) | ((x&0xff)<<24) )

//�������������꣬����ϵͳ�������߼�����

#define SINGLESTEPLOGIC

enum ES2SMessageDefine
{
    S2S_MSG_FIRST = S2S_MSG_BEGIN,
};

enum EMessageDefineUnUse
{
    MSGUU_FIRST = UU_MSG_BEGIN,
};

enum ECenterLoginMessageDefine
{
	TO_CENTER_LOGIN_ON = CENTER_LOGIN_SERVER_BEGIN,
	TO_LOGIN_LOGIN_OFF ,
	TO_CENTER_LOGIN_KICK,
};

// �µ���ÿ��ʾ��
// ��һλ : ���ܿ��ʶ����ķ���
// �ڶ�λ : ����,��ʶ�������﷢�͵� 
//          s �������� �ͻ���
//          c �ͻ����� ������
//            u ˫��(doUble)
//            b �������Ϳͻ���˫��
//          d ���ݿ��� ��Ϸ
//          g ��Ϸ�� ���ݿ�
// ����λ : С���ܱ�ʶ
// ����λ : �������

enum EClientServerMessageDefine
{ // ��Ϣ����
    GAME_FIRST_MSG = GAMEWORLD_MSG_BEGIN,
    MSG_LOGIN,
    MSG_ACKLOGIN,
    MSG_RIGHTCHECK,         // [û��]
    MSG_EXIT,
    MSG_QUERYMOVE,          // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_ACKMOVE,            // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_MOVEPATH,           // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_MOVETOTARGET,       // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_EXITMYSIGHT,
    MSG_CHANGEMAP,
    MSG_MAPLOADED,
    MSG_QUERYDISPLAYNAME,
    MSG_ACKDISPLAYNAME,
    MSG_ACKATTACK,          // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_SEEATTACK,          // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_REQSKILLATTACK,   // ���󷢶����ܹ���
    MSG_ACKQUERYATT2,     // ��Ӧ�������ܹ��� // [Server:û�� Client:OnMsgAckAttack3���õ�]
    MSG_ACKATT2,            // [û��]
    MSG_EXPRESSION,       // �ͻ��˷�������ĳ���������鶯��    
    MSG_ACKEXPRESSION,    // ����ĳ���������鶯��
    MSG_WHODIE,             // [Server:LogMsg��Ӧ�ã�û�ж�Ӧ�����ݽṹ Client:û��]
    MSG_QUERYGAMEPROPERTY,  // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_ACKGAMEPROPERTY,    // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_QUERYALLGAMEPROPERTY,
    MSG_ACKALLGAMEPROPERTY,   
    MSG_EVENTRANGE,         // [Server:LogMsg��Ӧ�� Client:û��]
    MSG_CHAT,
    MSG_ENDACKCHAR,           // ֪ͨ�ͻ��ˡ����˺����ݶ�ȡ���ˣ�// [Server:û�� Client:OnMsgEndGetCharacter��Ӧ��]
    MSG_ACKCHAR,
    MSG_ENTERWORLD,
    MSG_ACKENTERWORLD,
    MSG_CREATECHAR,
    MSG_ACKCREATECHAR,
    MSG_DELETECHAR,
    MSG_ACKDELETECHAR,    
    MSG_GETLAG,
    LOGMSG_ITEMLOG,      // ��Ҫ���ߵĲ��� // [û��]
    LOGMSG_CASHPOINT,    // �ʻ��㿨�Ĳ��� // [û��]
    LOGMSG_CHARACTER,    // ��ɫ�ʺŵĲ��� // [û��]
    MSG_CHARLEVELUP,     // ��ɫ������Ϣ
    MSG_SEECHARLEVELUP,  // ����ĳ������
    MSG_SHOWEFF,         // ������ɫ���ϳ���Ч��    // [û��]
    MSG_REQ_SCRIPT,      // script�����Ϣ
    MSG_ACK_SCRIPT,
    MSG_SCRIPTCANCEL,    // �ͻ���ȡ���ű�ִ��1045 // [Server:û�� Client:����]
    MSG_SCRIPTEND,       // �ű�����
    MSG_SCRIPTVARCLEAR,  // ������нű����� // [û��]
    MSG_SCRIPTSHOW,
    MSG_GETSHOP,         // ����鿴��Ʒ
    MSG_ACKGETSHOP,      // ����鿴��Ʒ(�ش�)
    MSG_BUYORSELLGOODS,  // ������Ʒ1050
    MSG_ACKBUYORSELLGOODS, // ������Ʒ(�ش�)
    MSG_REQRELIVE,        //Relive
    MSG_REFRESHCHAR,      // ˢ���û����� // [û��]
    MSG_ITEMENTERMYSIGHT, // ��Ʒ������Ұ
    MSG_QUERYITEMINFO,    // ȡ��Ʒ��Ϣ1055 // [û��]
    MSG_ACKDRAGINFO,      //����ҩƷ��Ϣ    // [û��]
    MSG_PICKITEM,         //����
    MSG_GETITEM,          //�����Ʒ    // [û��]
    MSG_GETMONEY,         //���Ǯ      // [û��]
    MSG_DROPITEM,         //������Ʒ1060
    MSG_ACKDROPITEM,      //ȷ�϶���
    MSG_MONEYCHANGE,            // 
    MSG_CALLPET,          // �ٻ����� ������    // [û��]
    MSG_FLYTOMAP,        //�ͻ���Ҫ���л���ͼ1080   // [û��]
    MSG_EQUIPCHANGED,    //װ���ı�
    MSG_MOVEASTEP,       
    //MSG_MOVEBLOCKED    
    //MSG_MOVETOPOS,                //�ƶ���Ŀ�������

    // ����ͻ���  
    MSG_QUERYCHARAROUND,            // ����õ���Χ��char
    MSG_ACKCHARAROUND,              // ��Ӧ
    MSG_QUERYCHARINFO,   
    MSG_ACKCHARINFO,
    MSG_VERIFYPOS,                  //У��λ��
    MSG_SYNCPOS,                    //�̶�ʱ�������ͬ����Ϣ    // [û��]
    MSG_REQMOVEASTEP,               //�����ƶ�λ��              // [û��]
    MSG_PERMITMOVE,                 //�ƶ����                  // [û��]
    
    //��ɫ��ֵ�ı�
    MSG_CHARATTRCHANGE,         //

    //������������
    //��:��ɫ�Ļ�������
    //ְҵ��Ԫ�صȡ���һ�п��������Ķ���
    MSG_REQ_UP_ATTR_LEVEL,      // [Server:OnReqUpAttrLevel������ע�͵� Client:û��]
    MSG_ACK_UP_ATTR_LEVEL,      // [Server:û�� Client:OnMsgAttrLevelUp]

    //MSG_VISUALCHANGE
    //�ͻ��˱����������趨
    MSG_REFRESHLINKEDSKILLS,    // [Server:OnRefreshLinedSkill������ע�͵� Client:û��]
    //�ͻ��˱����ȼ��趨
    MSG_REFRESHHOTKEY,

    //��ͼ������Ч��������Ұ
    MSG_EFFECTENTERMYSIGHT,
    //����Ч���������˺�
    MSG_DAMAGEOFEFFECT,     // [û��]
    
    MSG_REQATTACKGROUND, // ��ɫ��������
    MSG_SEEATTACKGROUND, // ȷ�� ������ɫ��������   // [û��]
    
    MSG_SEEDAMAGE,      // ���������ܵ����˺�    
    MSG_SEEATTACK3,     // �����������˻���˹���
    MSG_INTONATE,       // ����Ī�����ʳ�           // [û��]
    
    MSG_MAGIC_RELEASE,  // ������ĳ���ͷŷ���       // [û��]
    
    MSG_EQUIP,          // �ͻ�����װ����Ʒ
    MSG_EQUIPTOWHERE,   // [Server:OnEquipToWhereֱ��return Client:SendEquipMsgToWhere]
    MSG_ACKEQUIP,
    MSG_UNEQUIP,        //ж��װ��
    MSG_MOVEGOODS,              // [û��]
    MSG_CHANGEGOODSPOS,         // [û��]
    MSG_CHANGEITEMPOS,
    MSG_USEGOODS,       // ʹ����Ʒ1110
    MSG_NPC_ENTERMYSIGHT,              //������Ұ
    MSG_NPC_ENTERMYSIGHTMOVINGASTEP,   //�ƶ��н�����Ұ     // [Server:û�� Client:OnMsgNPCEnterMySightMovingAStep �޺���ʵ��]

    MSG_PLAYER_ENTERMYSIGHT,            //������Ұ
    MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP, // [Server:û�� Client:OnMsgPlayerEnterMySightMovingAStep]
    
    MSG_QUERYCONTINUOUSSKILL, // �����Ƽ���
    MSG_ACKCONTINUOUSSKILL,
    MSG_QUERYHPINFO,          // ����Ѫ����Ϣ
    MSG_ACKHPINFO,            // ����Ѫ����
    MSG_ADDMISSIONINTRO,      // ��������˵��   // [Server:û�� Client:OnMsgAddMissionIntro]
    MSG_DELMISSIONINTRO,      // ɾ������˵��   // [Server:û�� Client:OnMsgAddMissionIntro]
    MSG_REQDOACTION,          // ����������     // [û��]
    MSG_SEEACTION,            // ����������     // [Server:û�� Client:OnMsgSeeAction]

    //************��Ϸ����Ⱥ���������Ϣ
    MSG_GWDC_ISGWORLD,  //֪ͨ ���ӵķ������� ��Ϸ���������    // [û��]
    MSG_GWDC_ISGATE,    //�� Gate                               // [û��]
    MSG_GWDC_GWORLDINFO,//����Ϸ�������Ϣ                      // [û��]
    MSG_GWDC_GATEINFO,  //��GateInfo                            // [û��]

    //*************��Ϸ����Ⱥ��Ϳͻ��� ��Ϣ    
    MSG_GWDC2C_GWORLDINFO, // ���͵��ͻ��˵���Ϸ�������Ϣ      // [Server:û�� Client:GameLoginMsg]    
    MSG_GW2G_SYNCCHARINFO,    // ͬ�������Ϣ���ͻ���
    
    MSG_G2GW_ALLOCCLIENT,    // �������ͻ�����    
    MSG_GW2G_RETALLOCCLIENT, // ����    
    MSG_G2GW_DELETECLIENT,   // ɾ���ͻ�����
    MSG_GW2G_SYNCCHARPOS,    // Gate�յ���Ϣ�������ɫ�����ڣ�����һ�� S2S
    MSG_GW2G_NPCEXIT,        // ����ҽ�ɫ������Gate�ͷŸ�ID

    //�����������
    //MSG_UPDATECHARDATA, //= TAG('udcd')
    MSG_GETPLAYERINFO,    // ȡ����ҵ���Ϣ    
    MSG_ACKGETPLAYERINFO, // ����������������ҽ�ɫ����Ϣ     
    MSG_ACKFRIENDLEAVE,   // ���������͹�������Ϣ֪ͨ����������     // [û��]
    
    MSG_REQ_PLACESTONE,   // ������÷�ʯ   // [Server:û�� Client:�к����壬�޺���ʵ��]
    MSG_ACK_PLACESTONE,   // �ظ����÷�ʯ   // [û��]
    MSG_REQ_REMOVESTONE,  // �����Ƴ���ʯ   // [û��]
    MSG_ACK_REMOVESTONE,  // �ظ��Ƴ���ʯ   // [Server:û�� Client:OnMsgRemoveStone]
    
    MSG_REQ_PLACESUBSKILL,  // ���������ʽƬ��     // [û��]  
    MSG_ACK_PLACESUBSKILL,  // �ظ�������ʽƬ��     // [Server:û�� Client:OnMsgPlaceSubSkill]
    MSG_REQ_REMOVESUBSKILL, // �����Ƴ���ʽƬ��     // [û��]
    MSG_ACK_REMOVESUBSKILL, // �ظ��Ƴ���ʽƬ��     // [Server:û�� Client:OnMsgRemoveSubSkill]
    MSG_REQ_UPSKILL,        // ������������ [����]
    //MSG_ACK_UPSKILL,      // �ظ���������
    
    MSG_REQ_PRODUCEITEM,    //�����������          // [û��]
    MSG_ACK_PRODUCEITEM,    //�ظ����칤��          // [Server:û�� Client:OnMsgProduceItem]
    
    //MSG_REQ_UPGRADEEQUIP, ////�������װ��
    //MSG_ACK_UPGRADEEQUIP, ////�ظ�����װ��
    //MSG_ACK_LEARNSKILL  // ѧ�����µļ���    
    //MSG_ACK_GETSTONE    // ������µķ�ʯ
    
    MSG_GM_REQ_PLACE_CHAR, // gm��char�ڷŵ�ָ����λ��  // [û��]
    MSG_PING,              // �ͷ�����֮���PING.
    MSG_ALLNPCONTHEMAP,
    
    MSG_SWITCHFIGHTSTATUS,     // �ͻ��������л�ս״̬  // [û��]
    MSG_SWITCHSITSTATUS,       // �ͻ��������л�����״̬// [û��]
    MSG_ACK_SWITCHFIGHTSTATUS, // �л�ս��״̬    
    MSG_ACK_SWITCHSITSTATUS,   // �л�վ��
    MSG_UPDATEONLINE_LOGIN2ACCOUNT, //loginServer�Ͽ�����Account�� ���ʹ���Ϣ��LoginServer���������߽�ɫ����������  // [û��]

    //֪ͨ��ǰ���ӵ÷�����ID
    //����:GWorld���ӵ�LoginServer,
    //Login->Account
    MSG_SERVERID,
    MSG_QUERYSERVERID,          // [û��]

    MSG_QUERYSERVERINFO ,   //query server infomation example:current online player count   // [û��]
    MSG_ACK_QUERYSERVERINFO,// �����ѯ��������Ϣ
    
    MSG_HITITEMBAG,         // �ͻ��˷���������Ϣ��֪ͨ����౳������ĵ��� // [Server:û�� Client:MouseShortCutClear]
    MSG_RIGHTHITITEMBAG,    // �ͻ��˷���������Ϣ��֪ͨʹ�ñ�������ĵ���   // [û��]
    MSG_UPDATECHARABAG  ,   // ���±������ͻ���
    MSG_UPDATESHORTCUTBAG,  // ���¿�ݷ�ʽ���ͻ���                 // [Server:û�� Client:����û��ʵ�ִ���]

    MSG_UPDATEVISUALEQUIP,  // �������ϵ�װ�� �����á�
    MSG_UPDATEFIGHTDATA,    // ���¶�������   �����á�
    MSG_HITBODYITEM,        // ����Ϣ��������ϵĵ��ߡ����á�
    MSG_BUFFSUPDATE,        // ��ǰBuff list
    MSG_BUFFSCHANGED,        // buff�仯
    
    MSG_CHANGEDIR,          // ����Ϣ֪ͨ�����Ŀͻ��ˡ���ת��

    //sslenum
    MSG_SSLSendPublicKey,       // [û��]
    MSG_SSLSendSessionKey,      // [û��]
    MSG_SSLExchangKeyFinished,  // [û��]

    MSG_BUILDINGENTERMYSIGHT, // �����������Ұ     // [Server:û�� Client:OnMsgBuildingEnterMySight����û��ʵ��]
    MSG_BUILDING_REQBUILD ,   // ������           // [û��]
    MSG_BUILDING_BUILDFAILED, // ������ʧ��       // [Server:û�� Client:OnMsgBuildFailed����û��ʵ��]
    MSG_BUILDING_BUILDSTATUS, // ����״̬           // [Server:û�� Client:OnMsgBuildStatus����û��ʵ��]
    MSG_BUILDING_DESTROYED ,  // �������ݻ�         // [Server:û�� Client:OnMsgBuildDestroyed����û��ʵ��]
    MSG_BUILDING_SELFDESTROYED , //�����Ի٣����������ٺ󣬵���     // [Server:û�� Client:OnMsgBuildSelfDestroyed����û��ʵ��]

    // ���
    MSG_CREATETEAM,            //���       // [Server:û�� Client:OnMsgCreateTeam����û��ʵ��]
    MSG_ACKCREATETEAM,         //�������   // [Server:û�� Client:OnMsgCreateTeam����û��ʵ��]
    MSG_REQUESTTEAM,           // �ӳ�����������
    MSG_ACKJOINTEAM,           // ����������
    MSG_EXITTEAM,              // �˳�����
    MSG_KICKFROMTEAM,          // �Ӷ������ߵ�ĳ��
    MSG_INQUIRETEAMHEADER,     // �ӳ�ȡ������(�����Ա)    // [û��]
    MSG_ACKINQUIRETEAMHEADER,               // [Server:OnAckMsgInquireTeamHeader����û��ʵ�� Client:û��]
    MSG_INQUIREINVITEE,        //��Ա�յ������������Ϣ(����ȷ�����mssagebox)
    MSG_ACKINQUIREINVITEE,     //��Ա���ص��ȷ�������Ϣ(���Ƿ�ȷ�ϰ�ť)

    MSG_TEAMINFO,              //������Ϣ       // [Server:û�� Client:OnMsgTeamInfo����]
    MSG_ADDTEAMMEMBER,         //�������
    MSG_DELETETEAMMEMBER,      //ɾ����Ա�˳�����

    //����״̬(S->C)
    MSG_INTONATESTART ,       //������ʼ
    MSG_INTONATEEND ,         //��������
    //����ȡ������(C->S)
    MSG_REQCANCELSKILL ,
    //���ܱ�ȡ����(S->C) 
    MSG_SKILLCANCELD ,
    //����״̬��������Ұ���������������ά�ּ���
    MSG_SKILLSTATUS ,
    //ά�ּ��ܽ���
    MSG_HOLDSKILLEND ,
  

    MSG_SKILL_BEGINCOLDDOWN          // ��ʼ��ȴ[����]
    ,MSG_TEAM_PLAYERINFO             // ������Ϣ���� 
    ,MSG_CHANGE_SKILL                   // ��Ӽ���[����]
    

    ,MSG_TELLREPUTATION              // ֪ͨ����        // [Server:û�� Client:OnMsgTellReputation]
    ,MSG_REPUTATIONCHANGE            // �����ı���      // [û��]
    // ��ѫֵ
    ,MSG_EXPLOIT_CHANGE               // ��ѫֵ�ı���   // [Server:û�� Client:OnMsgExploitChange]
    ,MSG_TELL_EXPLOIT                 // ֪ͨ��ѫ       // [Server:û�� Client:OnMsgTellExploit]
    ,MSG_TELL_OFFICIALLEVEL           // ��֪��ְ�ȼ�   // [Server:û�� Client:OnMsgTellOfficialLevel]
    ,MSG_QUERY_CITYSINFO              // ��ѯ���г��е���Ϣ     // [û��]
    ,MSG_CITYINFO                     // ���µĳ�����Ϣ1230     // [û��]
    ,MSG_PLAYERNAME_CHANGED           // �û����ָı�           // [Server:û�� Client:OnMsgPlayerNameChanged]
    ,MSG_TEACHSKILL                 
    ,MSG_LEARNSKILL
    ,MSG_CHANGE_PKRECORD              // �ı�PK��¼         // [Server:û�� Client:OnMsgChangePKRecord]
    ,MSG_TELLMAP_NPCINFO              // ���߿ͻ��˵�ͼ�ϵ�npc�ֲ�1235  // [û��]
    ,MSG_TELLMAP_NPCQUEST             // ��֪��ͼ��npc���е�����        // [Server:û�� Client:OnMsgTellMapNpcQuest�޺���ʵ��]
    ,MSG_TELL_CHAR_VAR                // ��֪�ͻ�������״̬             // [Server:û�� Client:OnMsgTellCharVars]
    ,MSG_MOVE_COMPOUND_ITEM           // �ϳ�
    ,MSG_QUERY_COMPOUND               // ��ѯ�ϳ�
    ,MSG_ACK_COMPOUND                 // ����ϳ�   // [Server:û�� Client:OnMsgAckCompound]
    ,MSG_EQUIP_EVOLVE                 // װ������
    ,MSG_MINIGAME_GATE_ROOM_CREATED   // ���䴴��   // [û��]
    ,MSG_MINIGAME_GATE_ROOM_DESTROYED // ��������   // [û��]
    ,MSG_MINIGAME_GATE_ROOM_IN        // ���뷿��   // [û��]
    ,MSG_MINIGAME_GATE_ROOM_OUT       // �˳�����1245   // [û��]
    ,MSG_MINIGAME_ROOM_INFO           // ������Ϣ       // [û��]
    ,MSG_MINIGAME_ROOM_NOPCHANGED     // ���������������仯     // [û��]
    ,MSG_MINIGAME_PLAYERINFO          // �����Ϣ       // [û��]
    ,MSG_MINIGAME_REQ_INROOM          // ������뷿��   // [û��]
    ,MSG_MINIGAME_ACK_INROOM          // ���ؼ��뷿��   // [û��]
    ,MSG_MINIGAME_REQ_OUTROOM         // �����˳�����   // [û��]
    ,MSG_MINIGAME_ACK_OUTROOM         // �����˳�����   // [û��]

    ,MSG_MINIGAME_REQ_CREATEROOM      // ���󴴽�����   // [û��]
    ,MSG_MINIGAME_ACK_CREATEROOM      // ���ش�������   // [û��]

    //�����˳�����Ȼ���䱻Destroy
    ,MSG_MINIGAME_ROOM_DESTROYED      // ���䱻ɾ��1255     // [û��]

    ,MSG_MINIGAME_COMMAND             // ��Ϸ������Ϣ       // [û��]
    ,MSG_MINIGAME_GAMERESULT          // ��Ϸ���           // [û��]
    ,MSG_MINIGAME_START               // ��Ϸ��ʼ           // [û��]

    ,MSG_MINIGAME_TIMEFRAME           // ʱ��֡             // [û��]

    ,MSG_CONTAINER                          //1260          // [û��]
    ,MSG_ASKPLAYERINFO            // ��ѯ�����Ϣ �����á�
    //,MSG_CHANGEMONSTERMOVETYPE            //�ı������ƶ�����
    //,MSG_QUERY_INTENSIFY                  //�ش�ǿ��ITEM    
    //,MSG_ACK_INTENSIFY                    //����ǿ��ITEM    
    ,MSG_SCRIPT_PLAYERMUSIC
    ,MSG_SCRIPT_MAKEITEM
    ,MSG_SCRIPT_REQ_SHOW_QUEST_DLG
    ,MSG_SCRIPT_ACK_SHOW_QUEST_DLG
    ,MSG_REQ_QUEST_INFO
    ,MSG_ACK_QUEST_INFO
    ,MSG_QUERYMAPNPCLIST                    // ���󷵻ص�ǰ��ͼ��npc�б�  // [û��]
    ,MSG_POPMAPNPCLIST
    ,MSG_PROFESSIONCHANGE                   // ְҵ�ı�
    ,MSG_CHANGE_FIGHTSTATE                  // �ı�ս��״̬
    ,MSG_LOCKTARGET                         // ����Ŀ��
    ,MSG_ATTACKLOCKTARGET                   // ����������Ŀ��
    ,MSG_KEEPMOVINGTOPOS                    // ��ĳ������һֱ�ƶ�       // [û��]
    ,MSG_MOVINGTOPOS                        // �ƶ���ĳ������           // [û��]
    ,MSG_CHANGINGDIR                        // �ı䷽��
    ,MSG_PLAYERMOVING                       // ����������ͱ����ƶ�����Ϣ      // [Server:û�� Client:�õ�MsgPlayerMoving��Ϣ�е�ö��]
    ,MSG_MOVEDTOPOS                         // ��������������ƶ���ĳ�����Ϣ     // [û��]
    ,MSG_READYTOUSESPECIALSKILL             // ����������ͣ�׼��ʹ�ü��ܵ���Ϣ
    ,MSG_USESPECIALSKILL                    // ����������ͣ�ʹ�����⼼�ܵ���Ϣ
    ,MSG_AGREEUSESPECIALSKILL               // ��ͻ��˷��ͣ�ͬ��ʹ�����⼼�ܵ�֪ͨ
    ,MSG_DISABLEUSESPECIALSKILL             // ��ͻ��˷��ͣ�����ʹ�����⼼�ܵ�֪ͨ       // [û��]
    ,MSG_AGREEREADYTOUSESPECIALSKILL        // ��ͻ��˷��ͣ�ͬ��׼�����⼼�ܵ�֪ͨ
    ,MSG_GETBILLPOINT                       // ��ȡ��ҵ�������״̬�����á�
    ,MSG_SWITCHGATE                         // ��ȡ�������ӵ�GateServer
    ,MSG_GATEINFO                           // ���͸�GAMESERVER��GATESERVER��Ϣ
    ,MSG_ABANDON_TASK                       // ��������
    ,MSG_QUERY_SCRIPTVAR                    // ����鿴�ű�����(�Բ߻����Խű���)
    ,MSG_SHOWTEXT                           // ����Ļ����ʾ������Ϣ
    ,MSG_UPDATEBANK                         // ����������Ϣ         // [û��]
    ,MSG_REQ_BANKTRADE                      // �������н���
    ,MSG_ACK_BANKTRADE                      // �ظ���������         // [û��]

    ,MSG_UPDATESTORAGE                      // ���²ֿ���Ϣ
    ,MSG_MOVE_STORAGE_ITEM                  // ����ֿ���Ʒ�ƶ�
    ,MSG_ACK_MOVE_STORAGE_ITEM              // �ظ���������         // [û��]

    ,MSG_REQ_BACKCHARATERLIST               // ���������б�         // [û��]
    ,MSG_NPCPLAYANIM                        // NPC������
    ,MSG_LOGINWAIT                          // ��½�Ŷ���Ϣ         // [û��]
    ,MSG_CANCEL_LOGINWAIT                   // �ͻ���ȡ���Ŷ�       // [�ṹû��]
    ,MSG_CHARSKILLLEVELUP
    ,MSG_PINGSERVER                         // loginʱ������Ϣping�������� �����ӳ�   // [û��]
    ,MSG_CHANGEDROME                        // �ı��������Ϣ
    ,MSG_DISDROME                            // ���������Ϣ
    ,MSG_JUMP                 // ��Ծ��Ϣ ���С�
    ,MSG_CLIENTLOG            // Client Log.�ύ -
    ,MSG_USESKILLHINTMESSAGE  // ����ʹ�õ���ʾ��Ϣ

    ,MSG_GW2G_CREATESTAGE     // Server֪ͨGateServer��������
    ,MSG_GW2G_RELEASESTAGE    // Server֪ͨGateServer�ͷų���
    ,MSG_SETDIALOGNAME
    ,MSG_INTONATEINTERRUPT    // �ж�����
    ,MSG_CHARLIST             // ����б�
    ,MSG_SCRIPT_SETHOTKEY     // �ű������ȼ�

    ,MSG_TURNINTOHIDE                       // ��������״̬     // [û��]
    ,MSG_APPEARFROMHIDE                     // �뿪����״̬     // [û��]

    ,MSG_GMCOMMAND                          // GM����
    ,MSG_CHANGEQUIPHP                       // װ���;�
    ,MSG_CHARINFO                           // ��ɫ��Ϣ         // [û��]
    ,MSG_UNPLAYERMOVINGTOPOS                // ����ҽ�ɫ�ƶ���Ŀ�����Ϣ ���С�
    ,MSG_UNPLAYERMOVINGTOLOCKTARGET         // ����ҽ�ɫ�ƶ�������Ŀ��   ���С�
    ,MSG_UNPLAYERCLOSINGTOLOCKTARGET        // ����ҽ�ɫ������Ŀ��       ���С�
    ,MSG_GWORLDINFO                         // ����GateServer��ǰGWORLD״̬
    ,MSG_REMOVEITEM                         // �Ƴ���Ʒ
    ,MSG_UPDATETIME                         // ������Ϸ����ʱ��
    ,MSG_UNPLAYERVERIFYPOS                  // ����ҽ�ɫ��������
    ,MSG_PLAYERVERIFYPOS                    // ��ҽ�ɫ��������
    ,MSG_INTENSIFYEQUIP                     // ǿ��             [����]
    ,MSG_PLAYERCHANGEMOVINGTYPE             // ��Ҹı��ƶ���ʽ // [û��]
    ,MSG_PLAYERCHANGEMOVINGDIR              // ��Ҹı��ƶ����� // [û��]
    ,MSG_PLAYERCHANGEMOVINGDIRANDTYPE       // ��Ҹı��ƶ�������ƶ���ʽ   // [û��]
    ,MSG_PLAYERSTOPSOMEWHERE                // ���ͣ��ĳ��                 // [û��]
    ,MSG_PLAYERSTOPSOMEWHEREHAVEDIR         // ��ҳ���һ������ͣ��ĳ��     // [û��]
    ,MSG_LOCK_ITEM
    ,MSG_LOCK_ITEMACK
    ,MSG_UNLOCK_ITEM
    ,MSG_UNLOCK_ITEMACK
    ,MSG_CHECKUNLOCK_ITEMREQ
    ,MSG_CHECKUNLOCK_ITEMACK
    ,MSG_LOGININFO                          // ��ҵĵ�½��Ϣ������ѳɹ���½��������Ϣ��
	//,MSG_LOGININFO_NEW                          // ��ҵĵ�½��Ϣ������ѳɹ���½��������Ϣ���µĻ������
    ,MSG_GETCHARACTER                       // ��ȡ��ҽ�ɫ��Ϣ
    ,MSG_REPAIRITEM                         // ������Ʒ �����á�
    ,MSG_REPAIRITEMSERVERTOCLIENT           // ������Ʒ������-���ͻ���
    ,MSG_DRAWWEAPON                         // �γ�����
    ,MSG_DRAWINWEAPON                       // ��������
    //,MSG_FRIENDOFFLINE                    // ��������
    ,MSG_CASTINEFFICACYSKILL                // ʹ����һ����Ч�ļ���
    ,MSG_SHOWLEVELINFO                      // ������������Ϣ
    ,MSG_PETCOMMAND                         // ���������
    ,MSG_SAWSOMEONEDEAD                     // ����ĳ������

    ,MSG_PLAYERMOVINGPOS                    // �ƶ������λ�øı����Ϣ
    ,MSG_PLAYERMOVINGPOSANDDIR              // �ƶ������λ�úͳ���ı����Ϣ
    ,MSG_PLAYERPOS                          // ԭ�ز�����ҵ�λ����Ϣ
    ,MSG_PLAYERDIR                          // ԭ�ز�����ҵĳ�����Ϣ
    ,MSG_PLAYERPOSANDDIR                    // ԭ�ز�����ҵ�λ�úͳ�����Ϣ
    ,MSG_UPHPANDMP                          // ר��CLIENT�õĻָ�HP��MP��ֵ     // [Server:û�� Client:OnMsgHPMPModify]
    ,MSG_REQ_CREATECHECKNAME                // �ͻ��˴������﷢�͵������������Ƿ��ظ�
    ,MSG_ACK_CREATECHECKNAME                // ����
	,MSG_NEWCHANGENAMEREQ
	,MSG_NEWCHANGENAMEACK

    ,MSG_POSCHANGE                          // GateServer�Ż��ƶ�������Ϣ(�Ѷ���/�������ƶ���Ϣ���һ���������)
    ,MSG_ENTERMYSIGHTPACK                   // GateServer�Ż�������Ұ��Ϣ(�ѽ�ɫ������Ұ���д��ѹ������������������·�����)
    ,MSG_ACKENTERWORLDPACK                  // GateServer�Ż�������Ϸ��Ϣ(�����ݽ���ѹ��)
    ,MSG_MOVE_INTENSIFY_ITEM                // ǿ���ƶ�         // [Server:OnMoveIntensifyItemֱ��return Client:û��]
    ,MSG_CALLINTENSIFYUI                    // ǿ�����������!  // [Server:û�� Client:OnMsgShowIntensifyUI]
    ,MSG_PEEKOTHEREUIP                      // ������װ��
    ,MSG_WANTPEEK                           // �뿴

    ,MSG_DONE_QUEST                         // �������
    
    ,MSG_REQ_DUEL                           // -����-
    ,MSG_ACK_DUEL
    ,MSG_DUEL_START
    ,MSG_DUEL_END
    ,MSG_DUEL_STOP

    ,MSG_ACK_ECTYPEMAP_INFO                 // �ش𸱱���Ϣ
    ,MSG_REQ_ECTYPEMAP_INFO                 // ���󸱱���Ϣ         // [Server:OnReqEctypeMapInfo��ע�� Client:û��]
    ,MSG_REQ_FLYTOMAP                       // ����ɵ�ͼ

    ,MSG_REQ_ASSIGN_TEAM                    // ��������ʱ�� 2�����ϵ���Ʒ��������Ͷ��     // [Server:û�� Client:MsgReqAssginTeam]
    ,MSG_ACK_ASSIGN_TEAM                    // ����ÿ�������Աѡ�����Ϣ
    ,MSG_REQ_CHANGE_ASSIGNMODE              // �ӳ�����ı�������ģʽ
    ,MSG_ACK_CHANGE_ASSIGNMODE              // ���������ظı�������ģʽ
    ,MSG_ACK_CHANGE_ASSIGNMODE_ANSWER       // �ͻ���ÿ����Ա����ѡ���
    ,MSG_ACK_CHANGE_ASSIGNMODE_RESULT       // �ı����ģʽʧ���� ���߿ͻ��� ÿ����Ա���ص� ѡ�����    // [û��]

    ,MSG_REQ_BACKCHARATERLISTSUCESS         // BackCharaterList Success     // [û��]

    ,MSG_ADD_FIRSTLIST                      // ����GateServer�����б��� 
    ,MSG_REMOVE_FIRSTLIST                   // �Ƴ�GateServer�����б���

    ,MSG_REQ_UPGRADE_TEAM                   // ���������ӳ�

    ,MSG_2C_ITEM_ADSCRIPTION                // ���߿ͻ�����Ʒ����
    ,MSG_SKILLEXPTOSKILL                    // ���ܾ�����Ǹ�����
    ,MSG_SKILLEXPUP                         // ���ܾ�������
    ,MSG_REQ_SKILLEXPFORSKILLID             // ���������ͻ��˵ķ�����Ϣ
    ,MSG_KILLMONSTER                        // ɱ���������ľ���ͼ��ܾ���
    ,MSG_PKSTATE_CHANGE                     // ���PK״̬����(����/����/����/����)
    ,MSG_CANCELDELCHAR                      // ȡ��ɾ����ɫ
    ,MSG_ACK_CANCELDELCHAR                  // ��Ӧȡ��ɾ����ɫ
    ,MSG_CHANGE_PKFLAG                      // �ı�PKģʽ
    ,MSG_ACK_CHANGE_PKFLAG                  // ��Ӧ�ı�PKģʽ

    ,MSG_PLAY_EFFECT                        // ������Ч
    ,MSG_SHOW_INTONATE_BAR                  // ��ʾ������
    ,MSG_ISRELIVEYESORNO                    // �Ƿ�ͬ�⸴��

    ,MSG_ACK_FIRSTTIP                       // ��һ���¼���ʾ
    ,MSG_REQ_FIRSTTIP

    ,MSG_PLAYERMOVINGPOSTOSERVER            // �ͻ�����������˷����ƶ������λ�øı����Ϣ ���С�
    ,MSG_PLAYERMOVINGPOSANDDIRTOSERVER      // �ƶ������λ�úͳ���ı����Ϣ               ���С�
    ,MSG_PLAYERPOSTOSERVER                  // ԭ�ز�����ҵ�λ����Ϣ                       ���С�
    ,MSG_PLAYERDIRTOSERVER                  // ԭ�ز�����ҵĳ�����Ϣ
    ,MSG_PLAYERPOSANDDIRTOSERVER            // ԭ�ز�����ҵ�λ�úͳ�����Ϣ

    ,MSG_CHANGEPOWER                        // �ı�����     // [û��]
    ,MSG_CHANGEPOWERPOINT                   // �ı������   // [û��]
    ,MSG_HITCHMOVETARGETPOS                 // ����ƶ���Ŀ���
    ,MSG_CANCONTROLMOVING                   // ����ܷ���Ƶ��ƶ�
    ,MSG_NOTIFYMAIL                        // ˢ���ʼ��б�
    ,MSG_SENDMAILREQ                        // �����ʼ�����
    ,MSG_OPMAILREQ                          // �����ʼ�����
    ,MSG_DISHITCH                           // �´�˳������Ϣ
                                     
    ,MSG_SHOPCENTERBUY                      // �̳ǹ���RMB����
    ,MSG_RMBGOLDCHANGE                      // Ԫ�������仯
    ,MSG_GLODCOVSILVER                      // ���ת������
                                               
    ,MSG_ACKGLODCOVSILVER                   // �ش� ���ת������    // [û��]
                                              
    ,MSG_CHANGEMANIPLEFROMTEAM              // ChangeManipleFromTeam

    ,MSG_REQ_CHANGE_MEMBERTITLE             // �ı乫���Ա�ƺ�     // [û��]
    ,MSG_MOVEPLAYERFROMMANIPLE              // ��Ҹ���С��    

    ,MSG_S2CSENDSOFTKEYBOARD                // loginServer��������̶�Ӧ���и��ͻ���    // [Server:û�� Client:GameLoginMsg]

    ,MSG_REQGRAPHICCODE                     // ����ͻ��˼��ͼƬ��֤��
    ,MSG_ACKGRAPHICCODE                     // �ͻ���Ӧ��ͼƬ��֤��

    ,MSG_COVCORPS                           // ת��Ϊ��
    ,MSG_REQCOVCORPS                        // �Ŷ�ת���ɹ�     // [û��]

    ,MSG_TELLLUCKREWARD                     // ���߿ͻ��˱��ν�������
    ,MSG_LUCKREWARDREQ                      // ����15���������
    ,MSG_LUCKREWARDACK                      // �����Ӧ
    ,MSG_LUCKREWARDRESULT                   // ����15��ҡ�����

    ,MSG_SHOWTREASUREBOX                    // ֪ͨ�ͻ�����ʾ�������
    ,MSG_TREASUREBOXREQ                     // 
    ,MSG_TREASUREBOXACK                     // 
    ,MSG_TREASUREBOXRESULT                  // [Server:û�� Client:OnMsgTreasureBoxAck]

    ,MSG_OPEN_UI                            // ��client UI
    ,MSG_INTONATINGOVERTIME                 // �����б��������δ�

    ,MSG_REQFLAGHEADERFROMTEAM              //���С�Ӷӳ�          // [Server:OnReqFlagHeaderFromTeam���뱻ע�͵� Client:û��]
    ,MSG_RETFLAGHEADERFROMTEAM              //�ش���С�Ӷӳ�      // [Server:û�� Client:OnRetFlagHeaderFromTeam]

    ,MSG_CHANGE_BAGSIZE                     // �ı䱳����С
    ,MSG_CHANGE_INTEGRAL                    // ���ָı�             // [û��]
    
    ,MSG_REQEXIT                            // ��������˳���Ϸ     // [û��]
    ,MSG_ACKEXIT                            // ������֪ͨ��ҽ����˳��ȴ�       // [û��]
    ,MSG_REQCANCELEXIT                      // �������ȡ���˳�                 // [û��]
    ,MSG_ACKCANCELEXIT                      // ������֪ͨ����˳�ȡ��           // [û��]

    ,MSG_MOVE_REDUCE                        // �ֽ�UI���ƶ�
    ,MSG_ACKFORREDUCE                       // ����ֽ�
    ,MSG_REDUCEOFF                          // �ֽ���ˣ�����CLIENT���
    ,MSG_CALLREDUCEUI                       // �����ֽ�UI               // [Server:û�� Client:OnMsgShowReduceUI]

    ,MSG_ACKGETSHOPCENTER                   // ����鿴�̵���Ʒ(�ش�)
    ,MSG_GETSHOPCENTER                      // ����鿴�̵���Ʒ

    ,MSG_UNSOULBOUND                        // �����
    ,MSG_CALLUNSOULBOUND                    // ��������     // [Server:OnMsgUnSoulBoundֱ��return Client:OnMsgShowUnsoulBoundUI]
    ,MSG_MOVE_UNSOULBOUND                   // ������ƶ�     // [Server:OnMsgMoveUnSoulBound���뱻ע�͵��� Client:û��]

    ,MSG_RETSHOPCENTERCNT                   // ����sShop����Ʒ����
    ,MSG_RELIVENEEDSILVER                   // ��Ҫ����
    ,MSG_FARREPAIRCOSTRMB                   // ����Զ�������RMB
    ,MSG_GWBURTHEN                          // GAMEWORLD����������
    ,MSG_CLIENTSHOWMSG                      // �ÿͻ��˵����Ի���
    ,MSG_PLAYERMOVINGDATATOSERVER           // ��û�á�
    ,MSG_CLOSEITEMFORMIDX                   // ɾ���ͻ���ָ��λ����Ʒ �����á�

    ,MSG_REQ_RMB_OP                         // �������Ҳ���
    ,MSG_REQ_CHANGESUBACTION                // �ͻ�����������
    ,MSG_RET_CHANGESUBACTION                // ��������������

    ,MSG_SEND_REAL_TIME                     // ���Ϳͻ��˷�������ǰʱ��
    ,MSG_REQ_RESETTIME                      // Client��������Itemʱ��
    ,MSG_RET_RESETTIME                      // ����Itemʱ�䷵��
    ,MSG_TELLC_LOCKNUM                      // ����C��������        // ��Client���á�

    ,MSG_ALLOCGWID                          // �ͻ��˷�����������ID��Ϣ
    ,MSG_RECONNECT                          // �ͻ��˷��������������
    ,MSG_ASKYUANBAOCNT                      // ��ѯԪ������         // [Server:OnAskYuanBaoCnt���뱻ע���� Client:û��]
    ,MSG_REQYUANBAOCNT                      // ����Ԫ������         // ��Client���á�
    ,MSG_MOVE_LOCKINTENSIFY                 // �ƶ�LOCKINTENSIFY
    ,MSG_LOCKINTENSIFY                        // LOCKINTENSIFY      // ��Client���á�
    ,MSG_CALLLOCKINTENSIFYUI                // LOCKINTENSIFY        // ��Client���á�
    ,MSG_CALLLOCKINTENSIFY                     

    ,MSG_ACK_COMPOUND_NEW                   // �µ�����ϳ���Ϣ
    ,MSG_QUERY_COMPOUND_NEW                 // ���غϳ���Ϣ
                                               
    ,MSG_REQ_CHANGE_OWNATTRIBUTE            // ������ĸ���������������

    ,MSG_CHANGE_BATTLEFLAG                  // ֪ͨ����ս�����     // ��Client���á� 

    ,MSG_TELL_CompoundRateAdd
    ,MSG_TELL_IntensifyRateAdd
    ,MSG_RIGHTCHECK2                        // ��½���
                                               
    ,MSG_LOGIN2                             // ��½���
    ,MSG_TellShopCenterOffSet               // �����̳��ۿ�

    ,MSG_INVITE_INFO                        //������Ϣ
    ,MSG_REFER_INVITE_RESULT                //�ύ������

    ,MSG_MODIFY_PLAYER_HELP_FLAG            // ���������ʾ���
    ,MSG_REQ_DELREPUTENAME                  // ɾ���ƺ�         // [û��]

    ,MSG_ASK_EXECUTE_SCRIPT                 // ������нű�

    ,MSG_SWITCHSUIT                         // �л���װ
    ,MSG_USE_ANGELL                         // �ػ���ʹ
    ,MSG_SHOW_HELMET                        // ��ʾͷ��
    ,MSG_ACK_SWITCHSUIT                     // �л���װ
    ,MSG_SHOWTIMETOP                        // ��ʾ����ʱ
    ,MSG_SHUTDOWNTIMETOP                    // �رյ���ʱ
    ,MSG_Tell_LoginServer_GateOK            // ����loginserver gateserver�Ѿ��������   // ��û�á�
    ,MSG_ThunderLoginInfo                   // Ѹ�׵�½��Ϣ                             // ��û�á�
                                 
    ,MSG_CHANNELSINFO                       // Ƶ����Ϣ
    ,MSG_SELECTCHANNEL                      // ѡ��Ƶ�� �ͻ���
    ,MSG_SELECTCHANNEL_SS                   // ѡ��Ƶ�� ��������
    ,MSG_ACK_SWITCHGATE                     // Ӧ���з���

    ,MSG_CLEANUP_BAG                        // ������
    ,MSG_GETMOUNT                           // �������
    ,MSG_OUT_OF_LONGIN_TIME                 // ��¼��ʱ

    ,MSG_MOVEGOODSREQ
    ,MSG_MOVEGOODSACK                       // �ƶ���Ʒ�Ļ���
    ,MSG_CHECKCHEATREQ                      // ����Ƿ�����
    ,MSG_CHECKCHEATACK                      // ����Ƿ�����
    ,MSG_GETPROCESSLISTREQ                  // �����ÿͻ��˵Ľ����б�
    ,MSG_GETPROCESSLISTACK                  // ��Ӧ�����б�
    ,MSG_REQNUMBERCODE                      // ����ͻ��˼��ͼƬ��֤��
    ,MSG_ACKNUMBERCODE                      // �ͻ���Ӧ��ͼƬ��֤��

    // �ƺ�
    ,MSG_CHANGETITLEREQ                     // ����ı䵱ǰ�ƺ�
    ,MSG_TELLCURRENTTITLE                   // ֪ͨ��ǰ�ƺ�
    ,MSG_ADDTITLEREQ                        // ��ӳƺ�
    ,MSG_ADDTITLEACK
    ,MSG_REMOVETITLEREQ                     // ɾ���ƺ�     // [û��]
    ,MSG_REMOVETITLEACK
    ,MSG_TELLTITLELIST                      // ֪ͨ�ƺ��б�

    ,MSG_UPDATEMOUNT                        // �������
	,MSG_CHANGEMOUNTNAME					// ������������
    ,MSG_MAPINFOREADY						// ������ͼ��Ϣ��ȫ
	,MSG_ACK_RESULT							// ��Ӧ��Ϣ
    ,MSG_TEAMOUTLINE                        // ��Ա������
    ,MSG_RETURNTO_CHARACTERSERVER           // ����ѡ�˷�����

    ,MSG_TELLPACKAGEACCESS                  // ���߿ͻ��˰�����Ȩ��
    ,MSG_PACKAGEVIEWREQ                     // �ͻ�������鿴����
    ,MSG_PACKAGEVIEWACK                     // ��Ӧ��������
    ,MSG_PACKAGEVIEWEND                     // �����鿴����
    ,MSG_PICKPACKAGEITEMREQ                 // �ͻ�������ʰȡ���������Ʒ
    ,MSG_PICKPACKAGEITEMACK                 // ��Ӧʰȡ����
    ,MSG_PICKPACKAGEITEMBOULTREQ            // ���������͵Ķ�ɸ������
    ,MSG_PICKPACKAGEITEMBOULTACK            // �ͻ��˻�Ӧ�Ķ�ɸ��
    ,MSG_PICKPACKAGEITEMBOULTNUMBER         // �ش�ɸ�ӵ�����
    ,MSG_PICKPACKAGEITEMNEEDTOASSIGN        // ����Ϣ���ӳ� ��Ҫ������Ʒ
    ,MSG_TELLTEAMASSIGNINFO                 // �����¼���Ķ�Ա����ķ�����Ϣ
    ,MSG_PICKPACKAGEITEMASSIGNREQ           // �ӳ�������������
    ,MSG_PICKPACKAGEITEMASSIGNACK           // ����˻�Ӧ���������
    ,MSG_TEAMCHANGEASSIGNITEMLEVELREQ       // �ͻ������������Ʒ����ȼ�
    ,MSG_TEAMCHANGEASSIGNITEMLEVELACK       // ��Ӧ������Ʒ����ȼ�
    ,MSG_PACKAGEITEMACCESSREQ               // ������ƷʰȡȨ��
    ,MSG_PACKAGEITEMACCESSACK               // ��Ӧ��ƷʰȡȨ��
    ,MSG_TELLPICKPACKAGEITEM                // ���߶������ĳĳĳʰȡ��ĳ��Ʒ(ֻ��Ʒ��������Ʒ)
    ,MSG_STORAGEMONEYREQ                    // ����ֿ��Ǯ����ȡǮ
    ,MSG_STORAGEMONEYACK                    // ��Ӧ�ֿ��ǮȡǮ����
    ,MSG_USEGOODSTOMOUNT                    // ������ʹ����Ʒ

    ,MSG_ADDRECIPEACK                       // ���һ���䷽

    //����
    ,MSG_ACK_NOTARIZATION                   // Ѱ��֤         // [û��]

    ,MSG_GATEACKLOGININFO                   // GateServer����
    ,MSG_TELLTEAMINFO                       // ��֪����ڶ����е���Ϣ
    ,MSG_CHANGEPROTECTLOCKTIMEREQ           // ������ı�����ʱ��
    ,MSG_CHANGEPROTECTLOCKTIMEACK           // ���ظ��ı�����ʱ��Ľ��
    ,MSG_BEKICK                             // �㱻����
    ,MSG_TELLTEAMMEMBERLIST                 // ͬ�������Ա�б�
    ,MSG_TELLANTIADDICTIONACCOUNTINFO       // �����˺�������Ϣ
    ,MSG_ECTYPESTAGETIMEREMAIN              // ʱ�丱��ʣ��ʱ��
    ,MSG_CLEARSKILLCOLLDOWN                 // �������colldownʱ��
    ,MSG_TELLCLIENT                         // �ͻ�����ʾһ�仰
    ,MSG_ACCOUNTPOINT                       // �ʺŵ���
    ,MSG_RECEIVEQUESTREQ                    // �ͻ������������
    ,MSG_RETPUBQUESTREQ                     // ˢ�¾ƹ���������
    ,MSG_RETPUBQUESTACK                     // ˢ�¾ƹ�����ָ�
    ,MSG_CLIENTTEAMINFO                     // �ͻ��˷�����Ϣ�����������������֤
    ,MSG_TELLGAMESTAGE                      // ֪ͨ�ͻ��˷ֶ�ˢ��
    ,MSG_MOVESTARREQ                        // ��������
    ,MSG_MOVESTARACK                        // ���ǻ�Ӧ
    ,MSG_SUITELEMENTCHECKUPREQ              // ������װ��������
    ,MSG_SUITELEMENTCHECKUPACK              // ������װ������Ӧ
    ,MSG_SUITELEMENTMOVEREQ
    ,MSG_SUITELEMENTMOVEACK
    //,MSG_MONEYITEMEXCHANGEREQ               // ʵ��һ�����
    //,MSG_MONEYITEMEXCHANGEACK               // ʵ��һ�����
    ,MSG_SPECIALREPAIRITEMREQ               // ��������
    ,MSG_SPECIALREPAIRITEMACK               // ��������
    ,MSG_TELLREMOVETIMELIMITITEM            // [û��]
    ,MSG_EQUIPUPGRADEREQ                    // �ͻ�����������
    ,MSG_EQUIPUPGRADEACK                    // ���������׻�Ӧ���
    ,MSG_SUITLEVELUPREQ
    ,MSG_SUITLEVELUPACK
    ,MSG_SUITCHANGEREQ
    ,MSG_SUITCHANGEACK
    ,MSG_ONLINEREWARDREQ
    ,MSG_ONLINEREWARDACK
    ,MSG_MOVE_STORAGE_ITEMACK
    ,MSG_BUYBACKITEMREQ
    ,MSG_BUYBACKITEMACK
    ,MSG_BUYBACKITEMLISTREQ
    ,MSG_BUYBACKITEMLISTACK
    ,MSG_CHANGENAMEREQ
    ,MSG_SHOWBATTLESIGNUPDLG
    ,MSG_BATTLESIGNUPREQ
    ,MSG_BATTLESIGNUPACK
    ,MSG_TELLBATTLESIGNUPCOUNT
    ,MSG_WALLOWABOUT
    ,MSG_REGISTERSERVERREQ
    ,MSG_REGISTERSERVERACK
    ,MSG_SERVERSTATUSREQ
    ,MSG_SERVERSTATUSACK
    ,MSG_CANCELBUFF
	,MSG_DELLOGININFO                  // ɾ����¼���
    ,MSG_MAILLIST_ACK                  // �ʼ��б�
    ,MSG_SERVERVERSIONCHECKACK
    ,MSG_JIFENGSHOPITEMSLISTREQ        // �����̳ǵ��߲�ѯ
    ,MSG_JIFENGSHOPITEMSLISTACK        // �����̳ǵ����б�
    ,MSG_JIFENGSHOPITEMSGAIN           // �����̳ǵ�����ȡ

    ,MSG_TRADESHOPCONFIGREQ            // ���̳���������
    ,MSG_UPDATETRADESHOPCONFIG         // ���̳����ø���
    ,MSG_NOTIFYTRADESHOPCONFIGRECHANGE // ֪ͨ���̳����ð汾
    ,MSG_SERVERSHUTDOWN
    ,MSG_SENDMAILACK                   // �����ʼ�����
    ,MSG_OPMAILACK                     // �����ʼ�����
    ,MSG_MOVESTARLEVELUPREQ
    ,MSG_MOVESTARLEVELUPACK
    ,MSG_ITEMCOMPOSEREQ
    ,MSG_ITEMCOMPOSEACK
	//��Ӫս����Ϣ����
	,MSG_NOTIFY_BATTLE_KILLNUM     // ֪ͨ���ɱ�˹���

    ,MSG_TELLBATTLERECORD
    ,MSG_ENTERTEAMBATTLEREQ
    ,MSG_ENTERTEAMBATTLEACK
    ,MSG_TELLBATTLESIGNUPINFO
    ,MSG_LEAVEBATTLEREQ
    ,MSG_QUERYBATTLETEAMINFOREQ
    ,MSG_QUERYBATTLETEAMINFOACK
    ,MSG_QUERYTEAMRECORDREQ
    ,MSG_QUERYTEAMRECORDACK
    ,CS2CS_PRENTICEREPORTREQ

    ,MSG_SHOWVIEWUSEITEMTOPLAYER
    ,MSG_SHOWALLUSEITEMTOPLAYER
    ,MSG_JIAOZI_CHANGE             // ���Ӹı�
	,MSG_CONSUMESCORE_CHANGE             // �̳ǻ��ָı� ��s->c
    ,MSG_QUERYBATTLESIGNUPTIMEREQ
    ,MSG_QUERYBATTLESIGNUPTIMEACK

    ,MSG_TELLHIDESTATUS            // ֪ͨ����״̬
    ,MSG_MOUNTPOTENTIAL            // ����Ǳ�������
    ,MSG_MOUNTBREED                // ���ﷱֳ
    ,MSG_MOUNTACKBREED             // ���ﷱֳ
    ,MSG_SETOFFLINEHOOK            // �������߹һ�
    ,MSG_ACKOFFLINEHOOK            // �������߹һ���Ϣ
    ,MSG_GETOFFLINEHOOKEXP         // ��ȡ���߹һ�����
                                     
    ,MSG_TELLSERVEREXPMODULUS        
    ,MSG_EQUIPMAINTAINACK          // װ����ֵ������Ϣ
    ,MSG_ITEMRECLAIM               // װ������
    ,MSG_ITEMRECLAIMACK            // װ�����շ�����Ϣ
                                     
    ,MSG_ITEMCOMPOSEGEM            // ��ʯ������ϴʯ���ϳ�
    ,MSG_ITEMCOMPOSEGEMACK         // ��ʯ������ϴʯ���ϳɷ�����Ϣ
                                     
    ,MSG_REQPRESSKEYSUIT           // �ͻ�������һ����װ����
    ,MSG_ALLPRESSKEYSUIT           // ����ȫ��һ����װ����
    ,MSG_PRESSKEYSUIT              // ����һ����װ
    ,MSG_PRESSKEYSUITACK           // һ����װ��Ӧ
    ,MSG_PRESSKEYSUITRENAME        // ����һ����װ����
    ,MSG_PRESSKEYSUITRENAMEACK     // ����һ����װ���ƻ�Ӧ
    ,MSG_EQUIPPRESSKEYSUIT         // װ��һ����װ
                                     
    ,MSG_REQACHIEVEDATA            // �ͻ�����������ɾ�����
    ,MSG_ALLACHIEVEDATA            // �������гɾ�
    ,MSG_UPDATEACHIEVEVAR          // ���³ɾͽ���
    ,MSG_UPDATEACHIEVE             // ���³ɾ�
    ,MSG_REQACHIEVEREWARD          // ������
    ,MSG_REQACHIEVEREWARDACK       // ��������Ӧ
    ,MSG_REQOFFNPCSHIP             // ������npcship
    ,MSG_ONOFFNPCSHIP              // ����npcship��Ϣ
                                     
    ,MSG_LEARNALLSKILL             // ѧϰ���м���
                                     
    ,MSG_UPDATEMOUNTSTORAGE        // ��������ֿ���Ϣ
    ,MSG_MOVESTORAGEMOUNT          // ����ֿ����
    ,MSG_UPDATECHARMOUNT           // ��������������Ϣ
    ,MSG_UPDATEQUESTVAR            // ��ʾ����ļ������� �����á�
                                     
    ,MSG_PROTECTPETPOS             // ����Ŀ��λ��
                                     
    ,MSG_REQDOUBLEEXP              // ����˫������
    ,MSG_DOUBLEEXPACK              // ��Ӧ˫������
    ,MSG_OFFLINEFIGHTOPREQ         // �һ�ս����������
    ,MSG_OFFLINEFIGHTOPACK         // �һ�ս����������

    ,MSG_CHARASSIGNPOTENTIAL       // ����Ǳ�������
    ,MSG_CHARASSIGNPOTENTIALACK    // ����Ǳ����������

	,MSG_TELLLEAVEECTYPE           // �뿪����

    ,MSG_LEARNXINFA                // ѧϰ�ķ�
    ,MSG_CHANGEXINFA               // �ķ����ķ���

    ,MSG_REQGOTONDROME             // ����������
    ,MSG_REQGOTONDROMEACK          // ���������ﷴ��
    ,MSG_REQGOTOFFDROME            // ����������
    ,MSG_GOTONOFFDROME             // ���¶�������
	
	,MSG_UNPLAYERLOCKTARGET		   // ����ҽ�ɫ����Ŀ��

    ,MSG_TELLQUESTTIME             // ��������ʱ��
    ,MSG_REQDONEQUEST              // �����������

    ,MSG_SHOWSIGNATURE             // ��ʾ����
	
	,MSG_REQTEAMFOLLOW			   // ����������
	,MSG_ACKTEAMFOLLOW			   // �ظ��������
	,MSG_FOLLOWTEAMMEMBER		   // �����������
	,MSG_TEAMMEMBERACK			   // ���ظ��ͻ�����ʾ�ã��ܾ����棬ȡ�����棬ͬ����棩
	
	,MSG_HEADERCANCELTEAMFOLLOW		// �ӳ�ȡ���������
	,MSG_CANCELTEAMFOLLOW			// ȡ���������

    ,MSG_ADDUPDATEPET              // ��Ӹ��³���
	,MSG_PETCOMPOSE
	,MSG_ADDPETEQUIP
	,MSG_REMOVEPETEQUIP
    ,MSG_CHANGEPETNAME             // �������
    ,MSG_CHANGEPET                 // �ı����״̬
    ,MSG_PETPOTENTIAL              // �������Ǳ����
    ,MSG_USEGOODSTOPET             // �Գ���ʹ����Ʒ	
    ,MSG_PETSAVVYUP                // ��߳�������
    ,MSG_PETSAVVYUPACK             // ��߳������Է���
    ,MSG_UPDATEPETCHAR             // ���³������Ϣ
	,MSG_UPDATEPETMODE
	,MSG_SETPETMODE

    ,MSG_PETBREEDREQ               // ������ﷱֳ
    ,MSG_PETBREEDREQACK            // ���ﷱֳ��Ӧ
    ,MSG_PETBREEDCHOICE            // ѡ��ֳ����
    ,MSG_PETBREEDCHOICEACK         // ѡ��ֳ������Ӧ
    ,MSG_PETBREEDLOCK              // ��������
    ,MSG_PETBREEDCANCELLOCK        // ȡ����������
    ,MSG_PETBREEDCONFIRM           // ȷ�Ϸ�ֳ
    ,MSG_PETBREEDSTATUS            // ����״̬
    ,MSG_PETBREEDFINISH            // ��ɷ�ֳ����
    ,MSG_PETBREEDCANCELREQ         // ȡ����ֳ����
    ,MSG_PETBREEDACQUIRE           // ��ȡ����
    ,MSG_PETBREEDACQUIREACK        // ��ȡ���ﷴ��
    ,MSG_PETREGENERATE             // ��������

	,MSG_DISBANDTEAM				// ��ɢ����
	,MSG_MEMBERCOUNTINTEAMFOLLOW	// ֪ͨ�ӳ��м�����Ա�ڶ������

    ,MSG_PLAYMOVIEREQ              // ���͸��ͻ��˲�����Ƶ
    ,MSG_PLAYMOVIEACK              // �ͻ��˻�Ӧ�Ƿ�ʼ���ŷ���
    ,MSG_MONSTERTYPESTATUSCHANGE
    ,MSG_SAWTALKREQ                // �ύ�����Ի�
    ,MSG_ACHIEVEBROADCAST		   // �ɾ͹㲥

    ,MSG_STARTEVENT				   // ��ʼ�¼�
    ,MSG_ENDEVENTREQ			   // �����¼�����
    ,MSG_ENDEVENT				   // �����¼�

    ,MSG_MAILLISTREQ               // �����ʼ��б�
    ,MSG_RECONNECTACK              // �Զ���������

    ,MSG_REQIDENTIFYDATA           // ����ͼ������
    ,MSG_ALLIDENTIFYDATA           // ����ͼ������
    ,MSG_UPDATEPETIDENTIFY         // ���³���ͼ��

    ,MSG_EQUIPTALISMAN             // װ������
    ,MSG_EQUIPTALISMANACK          // װ����������
    ,MSG_UNEQUIPTALISMAN           // ж�ط���
    ,MSG_UNEQUIPTALISMANACK        // ж�ط�������
    ,MSG_TALISMANCHANGE            // �����ı�

	,MSG_TELLCLIENT_CANINVITE	   // ��Ҽ��𵽴�һ���̶ȵ�ʱ��֪ͨ�����峤���߰����������������Ҽ���

    ,MSG_PETLEARNSKILL             // ����ѧϰ����
    ,MSG_VIEWACTIVEPET             // �鿴Ŀ�����
    ,MSG_VIEWACTIVEPETACK          // �鿴Ŀ����ﷴ��

    ,MSG_UPDATEGUIDEREQ            // ��������ָ��
    ,MSG_UPDATEGUIDEACK            // ��������ָ������

    ,MSG_SCENEPLAY                 // ��ͷ����
    ,MSG_BLACKSCREEN               // ��ͷ��Ļ

    ,MSG_RIDEROFFDROME             // ����ʹĳ���¶�������
	,MSG_C2G_ASK_BIANSHEN          // �ͻ�����GAME SERVER�������
	,MSG_G2C_REQ_BIANSHEN          // game server���߿ͻ��˱�����
	,MSG_TELLHEROADDATTR		   // ���������߿ͻ��˱������������ӵ�����

	,MSG_REQ_FLYTOTPHJ			   // �ɵ�̫ƽ�þ�
	,MSG_TELLTPHJRANK			   // ֪̫ͨƽ�þ�rank
	,MSG_CHANGE_2_BIAOCHE_REQ	   // �����������ڳ�
	,MSG_CHANGE_2_BIAOCHE_ACK	   // ��ұ����ڳ���֪ͨ
	,MSG_RESTORE_FROM_BIAOCHE_REQ  // ���������ڳ��������
	,MSG_RESTORE_FROM_BIAOCHE_ACK  // ��ұ�����ε�֪ͨ
	,MSG_S2C_PlayerPlayAnim        //������֪ͨ�ͻ���player��ʲô����

	,MSG_TELLRELIVEBUFF			   // ֪ͨ�ͻ��˸������������buff
	//,MSG_TELLC_REASKGATE           // ֪ͨ�ͻ�����������
	,MSG_SHOW_HEROSUIT             // �Ƿ���ʾ�����������Ч��
	,MSG_REQ_FIRST_LIMITINFO       // ��һ������Ϸ����ȫ���ķ�ӡ��Ϣ
	,MSG_ACK_LEVELUP               // �ͻ�����������
	,MSG_ACK_ACTIVELIMIT           // �ͻ������󼤻��ӡ
	,MSG_ACK_LIMITINFO             // �ͻ��������ӡ��Ϣ
	,MSG_GS2C_LIMITDONE            // ֪ͨ�ͻ��˷�ӡ����

	///////////////////////////////////////////////////////
	,MSG_LOGIN_ACCOUNTINFO         // �ͻ��������¼,���Ͱ汾�Լ��ʺ�����
	///////////////////////////////////////////////////////
	,MSG_ZHUJIANGCOMPOSE            // ����ͼ���ϳ�
	,MSG_ZHUJIANGCOMPOSEACK         // ����ͼ���ϳɷ�����Ϣ
	,MSG_REQ_FLYTOKINGDOM           // ���������������
	,MSG_TRANSFER_STAR				// ת����Ϣ
	,MSG_TRANSFER_STAR_ACK			// ת�Ƿ�����Ϣ
	,MSG_MOUNT_STRENGTHEN			// ����ǿ��
	,MSG_MOUNT_STRENGTHEN_ACK		// ����ǿ������
	,MSG_UNBINDEQUIPREQ				// ���װ��
	,MSG_UNBINDEQUIPACK				// ���װ���ط�
	,MSG_KILLPLAYERNUM				//���ɱ����
	,MSG_CONKILLPLAYER				// �ͻ���ͨ�� %d��ɱ
	,MSG_REMOVEITEMBYBAGTYPE        // ���ݱ�������ɾ����Ʒ
	,MSG_ASKFORPRESENT              // �ͻ��˸���SN������Ʒ
	,MSG_PROCTIMESTEPACK
	,MSG_REPEATEDLY_PET             // �ظ�ע�ḱ��
	,MSG_PLATFORMERROR				// ƽ̨���ز�����������
	,MSG_MONSTERBELONGID
	,MSG_MONSTERNURTUREINFO
	,MSG_SENDMESSAGEEND				//��ʼ���������ݺ����Ϣ
	,MSG_CHANGEMAPTIMESTEPREQ
	,MSG_RANDATTRIBUTE_REQ			//��ϴװ���������
	,MSG_RANDATTRIBUTE_ACK
	,MSG_TELLCLIENTLEAVETEAM
	,MSG_CHANGEPETDURATION
	,MSG_USEITEM
	,MSG_UPDATECARD					//���¿���
	,MSG_RECARDACHIEVE				//���뿨�Ƴɾͽ���
	,MSG_RECARDACHIEVE_ACK			//���Ƴɾͽ�������
	,MSG_ENTERWORLDCHANGENAMEREQ
	,MSG_OPENBAGSTORAGE
	,MSG_ASKSEVENDAYSDATA			//��������������
	,MSG_ASKSEVENDAYSDATA_ACK		//��������������
	,MSG_FRESHSEVENDAYSTATE_VAR		//����������״̬
	,MSG_TRIGGERSEVENDAYS			//����������
	,MSG_ASKSEVENDAYSTASK			//��ȡ����������
	,MSG_ASKSEVENDAYSTASK_ACK		//��ȡ���������񷵻���Ϣ
	,MSG_ASKSEVENDAYSREWARD			//��ȡ����
	,MSG_CHANGECHANNEL_REQ			//�����л�����
	,MSG_CHANGECHANNEL_ACK			//�����л�����
	,MSG_CLEARTEAMMAPREQ
	,MSG_CLEARTEAMMAPACK
	,GS2CS_CLEARTEAMMAPREQ
	,CS2GS_CLEARTEAMMAPREQ
	,GS2CS_CLEARTEAMMAPACK
	,MSG_ASKGETSALARY				//�������ٺ»
	,MSG_ASKGETSALARY_ACK			//�����������ٺ»���
	,MSG_ASKADVANCEMENT				//��������
	,MSG_ASKADVANCEMENT_ACK			//�����������ٽ��
	,MSG_SHOWRANKTITLE				//��ʾ����
	,MSG_RECONNECT_RESETSTATE       //�Զ��������һЩ��Ҫ���õ�״̬
	,MSG_HUNTING_REFRESH			//ˢ����������
	,MSG_HUNTING_QUEST				//�������������б�
	,MSG_HUNTING_ACCEPT_QUEST		//��ȡ��������
	,MSG_HUNTING_ASKFORLIST			//��ȡ���������б�
	,MSG_FLYTOPOSITION
	,MSG_FLYTOPOSITIONACK
	,MSG_SHOWCENTERINFO
	,MSG_GETTHREEDAYITEM
	,MSG_GETTHREEDAYITEMACK
	,MSG_UPDATEYUANBAODATA
	,MSG_UPDATEYUANBAODATAREQ
	,MSG_MOUNTMOVESTAR
	,MSG_UPDATEPLAYERPOINT
	,MSG_REMOVEITEMBYGUID
	,MSG_PASSWORDCARDREQ
	,MSG_PASSWORDCARDACK
	,MSG_LEAVEEXPREQ
	,MSG_LEAVEEXPACK
	,MSG_GETLEAVEEXPREQ
	,MSG_PASSWORDCARDCANEL
    //------------------------------------------------------------------------
    // MSG_MAX��Ϣ����ͳ����Ϣ�������Լ����������ж�GetType()�Ƿ񳬳�����������Ϣ���ͷǷ��жϣ�
    // �������µ���Ϣ���������MSG_MAX��Ϣ����
    //------------------------------------------------------------------------
    ,MSG_MAX //�ܵ���Ϣ���� �����������
};

struct MsgReConnect : public Msg
{ // ��������
    MsgReConnect()
    {
        header.dwType = MSG_RECONNECT;
        header.stLength = sizeof( MsgReConnect );
        nAccountId = 0;
        //memset( szKey, 0, sizeof(szKey ));
		SessionKey = 0;
    }

    uint32 nAccountId;
    //char   szKey[32+1];
	__int64 SessionKey;
};

struct MsgReConnectAck : public Msg
{ // ��������
    enum EReconnectResult
    {
        ERR_Success   = 0,
        ERR_Invalid1  = 1, 
        ERR_Invalid2  = 2,
        ERR_ErrorPos1 = 3,
        ERR_ErrorPos2 = 4,
    };

    MsgReConnectAck()
    {
        header.dwType = MSG_RECONNECTACK;
        header.stLength = sizeof( MsgReConnectAck );
        nResult = 0;
    }
    uint16 nResult;
};

struct MsgAllocGWID : public Msg
{
    MsgAllocGWID()
    {
        header.dwType   = MSG_ALLOCGWID;
        header.stLength = sizeof(*this);
        memset( szAccount, 0, sizeof(szAccount));
		SessionKey = 0;
    }

    char         szAccount[ dr_MaxPlayerName ]; // �˺���

//#ifdef __NEW_LOGIN__
//    unsigned int nAccountID;
//    char         nIsSwitchGame;
//    char         SessionKey[40+1];
//#endif
	unsigned int nAccountID;
	char         nIsSwitchGame;
	//char         SessionKey[40+1];
	__int64      SessionKey;
};

struct MsgRetResetTime :public Msg
{
    enum
    {
        eRet_Sucess,
        eRet_Faild_ForNotMoney,
        eRet_Faild_NotOverdue,
    };
    MsgRetResetTime()
    {
        header.dwType = MSG_RET_RESETTIME;
        header.stLength = sizeof(*this);
    }
    BYTE    szMsg;
    unsigned short ustBagType;/*eBag_Type*/
    unsigned short ustIdx;
    __int64          n64UseTime;
    //unsigned short ustCount;
};

struct MsgReqResetTime :public Msg
{
    MsgReqResetTime()
    {
        header.dwType = MSG_REQ_RESETTIME;
        header.stLength = sizeof(*this);
    }
    unsigned short ustBagType;/*eBag_Type*/
    unsigned short ustIdx;
    //unsigned short ustCount;
};

struct MsgReqChangeSubAction : public Msg
{
    MsgReqChangeSubAction()
    {
        header.dwType = MSG_REQ_CHANGESUBACTION;
        header.stLength = sizeof(*this);
        targetid = -1; 
    }
    BYTE  action;   // ��Ϊ
    GameObjectId targetid; // Ŀ��
};

struct MsgRetChangeSubAction : public Msg
{
    enum EResult
    {
        ER_Success,
        ER_1_NotIdle,
        ER_2_NotIdle,
        ER_1_NotExist,
    };
    MsgRetChangeSubAction()
    {
        header.dwType   = MSG_RET_CHANGESUBACTION;
        header.stLength = sizeof(*this);
        stID1 = -1;
        stID2 = -2;
    }
    unsigned short result;
    GameObjectId  stID1;  // ������
    GameObjectId  stID2;  // ������
    BYTE           action; // ��Ϊ����
};

struct MsgAskYuanBaoCnt:public Msg      // [�ṹû��]
{
    MsgAskYuanBaoCnt()
    {
        header.dwType = MSG_ASKYUANBAOCNT;
        header.stLength = sizeof(*this);
    }
    //    INT nYuanBaoCnt;
};

struct MsgReqYuanBaoCnt:public Msg
{
    MsgReqYuanBaoCnt()
    {
        header.dwType = MSG_REQYUANBAOCNT;
        header.stLength = sizeof(*this);
        nYuanBaoCnt = 0;
    }
    INT nYuanBaoCnt;
};

struct MsgReqRmbOp : public Msg
{
    enum EOpType
    {
        ET_ExchangeJinDing, // �һ���
        ET_QueryPoint,      // ��ѯ����
    };

    MsgReqRmbOp()
    {
        header.dwType = MSG_REQ_RMB_OP;
        header.stLength = sizeof(*this);
        op    = ET_QueryPoint;
        value = 0;
    }

    uint8  op;
    uint32 value;
};

struct MsgClientShowMsg : public Msg
{
    enum
    {
        MAXLENGTH = 256,
    };
    MsgClientShowMsg()
    {
        header.dwType = MSG_CLIENTSHOWMSG;
        header.stLength = sizeof(*this);
        memset( szMsg,0, sizeof(char)*MAXLENGTH );
    }
    //    __int64 nSessionKey;
    //    unsigned int nAccountID;
    char szMsg[MAXLENGTH];     //�˺���
};
struct MsgGetCharacter : public Msg
{
    MsgGetCharacter()
    {
        header.dwType = MSG_GETCHARACTER;
        header.stLength = sizeof(*this);
		SessionKey = 0;
    }
//#ifdef __NEW_LOGIN__
//    char SessionKey[40+1];
//#else
//    __int64 SessionKey;
//#endif
	__int64 SessionKey;
    uint32 nAccountID;
    char   szAccount[dr_MaxPlayerName]; // �˺���
	uint32 dwCharacterId;
	short  stWitchSlot;
};

//��½ʱ��ͻ���log�ύ
struct MsgClientLog:public Msg
{
    MsgClientLog()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_CLIENTLOG;
        header.stLength = sizeof( MsgClientLog );

        memset( szLog,0, sizeof(char)*1024 );
        memset( szName,0, sizeof( szName ) );
    }
    char szLog[1024];
    char szName[dr_MaxPlayerName];
};

//��¼��Ϣ
struct MsgLogin:public Msg
{
    MsgLogin()
    {
        header.dwType = MSG_LOGIN;
        header.stLength = sizeof( MsgLogin );

        /*dwClientVersion = 0;*/
        dwGameVerSion[0]=1;
        dwGameVerSion[1]=0;
        dwGameVerSion[2]=0;
        dwGameVerSion[3]=1;
        memset( szUserName,0,dr_MaxPlayerName + dr_MaxPassword );
    }
    char szUserName[ dr_MaxPlayerName ];
    char szPassword[ dr_MaxPassword ];
    short stModelID;
    char szGameVersion[dr_MaxGameVersion];
    DWORD dwGameVerSion[4];
    /*DWORD dwClientVersion;*/
    char szIP[20];
    int isSoftKeboardChar;
};
struct MsgPingServer : public Msg       // LOGIN SERVER��CENTER SERVER֮���PINGͨѶ
{
    MsgPingServer()
    {
        header.uMsgLevel = level_low;
        header.dwType    = MSG_PINGSERVER;
        header.stLength    = sizeof( MsgPingServer );
    }
};

struct MsgLoginInfo : public Msg
{
    MsgLoginInfo()
    {
        header.dwType   = MSG_LOGININFO;
        header.stLength = sizeof(MsgLoginInfo);
        //IsForceLogin    = false;
        //memset(SessionKey,0,sizeof(SessionKey));
		SessionKey = 0;
        //memset(Password,0,sizeof(Password));
        //memset(Seed,0,sizeof(Seed));
        isWallow = 0;
    }

    char   szIP[16];
    uint32 nAccountID;
	char   szMac[MAC_LENGTH];
    /*char   SessionKey[40+1];*/
	__int64 SessionKey;
    //char   Password[50];
    /*char   Seed[50];*/
    //bool   IsForceLogin;
    char   szAccount[32]; // �˺���
    int8   isWallow;
};

//struct MsgLoginInfoNew : public Msg
//{
//	MsgLoginInfoNew()
//	{
//		header.dwType   = MSG_LOGININFO_NEW;
//		header.stLength = sizeof(MsgLoginInfoNew);
//		nAccountID    = 0;
//		memset(SessionKey,0,sizeof(SessionKey));
//		memset(szAccount,0,sizeof(szAccount));
//		isWallow = 0;
//	}
//	uint32 nAccountID;
//	char   SessionKey[32+1];
//	char   szAccount[32]; // �˺���
//	int8   isWallow;	  // ������
//};


struct MsgAckLoginInfo : public Msg
{
    MsgAckLoginInfo()
    {
        header.dwType = MSG_GATEACKLOGININFO;
        header.stLength = sizeof(MsgAckLoginInfo);
        //memset(SessionKey,0,sizeof(SessionKey));
		SessionKey = 0;
    }
    unsigned int nAccountID;
    //char         SessionKey[40+1];
	__int64 SessionKey;
};

//��ѯ�������Ƽ��ĵ�½GateServer
struct MsgSwitchGate : public Msg
{
    MsgSwitchGate()
    {
        header.dwType = MSG_SWITCHGATE;
        header.stLength = sizeof(MsgSwitchGate);

        ::memset(szGateIP, 0, sizeof(szGateIP));
        ::memset(szChannelName, 0, sizeof(szChannelName));
        uGatePort = 0;
        nResult = ER_Success;
        nServerType = ST_LoginServer;
    }    
    long nResult;
    unsigned short uGatePort;
    char szGateIP[60];
    char szChannelName[MAX_NAME_STRING];
    char nServerType; // ��Ϣ��Դ����������
};

struct MsgGateInfo : public Msg
{
    MsgGateInfo()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_GATEINFO;
        header.stLength = sizeof(MsgGateInfo);
        memset(szGateIP, 0, sizeof(szGateIP));
    }
    unsigned short nGatePort;
    char szGateIP[60];
    unsigned int nOnlineNum;
};

struct MsgGWorldInfo : public Msg
{
    MsgGWorldInfo()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_GWORLDINFO;
        header.stLength = sizeof(MsgGWorldInfo);
    }
    unsigned short nOnlineNum;
};

//��¼����
struct MsgAckLogin:public Msg
{
    enum enumErrorCode
    {
		//eLoginResult_succ = 1,//1���ɹ�
		//eLoginResult_noAccount,//2���˺Ų�����
		//eLoginResult_errorpasswords,//3���������
		//eLoginResult_servererror,//4����¼��֤�������쳣�����Ժ�����
		
		ret_succ = 1,					//1���ɹ�
		error_invaliduserorpass,		//������û�����������		
		ret_invalidpassword,            //���������
		ret_invalidusername,			//������û���
		error_invalidversion,            //�汾��ƥ��
		ret_alreadyaloginthisaccount,   //�Ѿ���һ������˺ŵ��û�����
		ret_loginfail,                  //��¼ʧ�ܣ��û��������벻ƥ�䣬����ϸ����
		ret_secondpwderror,             //������֤����
		ret_noactive,                   //�ʺ�δ����
		ret_noservice,                  //����δ����
		ret_blocked,                    //�ʺű�����
		ret_FullLoad,                   //���������� by cloud
		ret_FullMac,					
		ret_PwdCardError,				//�ܱ�����������
    };

    MsgAckLogin()
    {
        header.dwType = MSG_ACKLOGIN;
        header.stLength = sizeof( MsgAckLogin );
        stErrorCode = error_invaliduserorpass;
		dwAccountID = 0;
		SessionKey  = 0;
        /*memset(szJabberServerName,0,sizeof(szJabberServerName));
        dwJabberServerIP = 0;
        uiJabberServerPort = 0;
        dwAccountID = 0;
        dwSessionKey = 0;*/
    }
    short stErrorCode;                                //������
    //char  szJabberServerName[dr_MaxNameString];        //the jabber server name
    //DWORD  dwJabberServerIP;                        //the jabber server IP address
    //unsigned short uiJabberServerPort;                //the jabber server port
    DWORD dwAccountID;
    __int64 SessionKey;
	uint32 blocktime;//ʣ������ʱ��
};

struct MsgS2CSendSoftKeyboard : public Msg
{
    MsgS2CSendSoftKeyboard()
    {
        header.dwType = MSG_S2CSENDSOFTKEYBOARD;
        header.stLength = sizeof( *this );
    }
    BYTE    btList[100];
};
struct MsgLoginWait:public Msg      // [������¼״̬����ID�����Ļظ���]
{
    MsgLoginWait()
    {
        header.dwType = MSG_LOGINWAIT;
        header.stLength = sizeof( *this);

		getcharacter = false;
    }
    bool getcharacter;
    /*short stOnline;*/
};

struct MsgCancelLoginWait:public Msg        // [�ṹû��]
{
    MsgCancelLoginWait()
    {
        header.dwType = MSG_CANCEL_LOGINWAIT;
        header.stLength = sizeof( *this);
    }
};

//�ͷ���������ȷ��Ϣ��֤
struct MsgRightCheck:public Msg
{
    MsgRightCheck()
    {
        header.dwType = MSG_RIGHTCHECK;
        header.stLength = sizeof(MsgRightCheck);
        //
        /*dwClientVersion = 0;*/
        dwGameVerSion[0]=1;
        dwGameVerSion[1]=0;
        dwGameVerSion[2]=0;
        dwGameVerSion[3]=1;
    }
    char cGameVersion[dr_MaxGameVersion];
    DWORD dwGameVerSion[4];
};

//�˳�
struct MsgExit:public Msg
{
    MsgExit()
    {
        header.dwType = MSG_EXIT;
        header.stLength = sizeof( MsgExit );
		ExitType = ET_ExitGame; //lyh����˳����� 
    }    

	unsigned short ExitType;
};

//�����ƶ�
struct MsgQueryMove:public Msg
{
    MsgQueryMove()
    {
        header.dwType = MSG_QUERYMOVE;
        header.stLength = sizeof( MsgQueryMove );
		
    }
	
};

//�����ƶ�����
struct MsgAckMove:public Msg
{
    MsgAckMove()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_ACKMOVE;
        header.stLength = sizeof( MsgAckMove );
    }
    short x,y;
};

//�ͻ����ϴ��ƶ�·��
struct MsgMovePath:public Msg
{
    enum enumConst
    {
        const_iMaxPath = 255
    };
    MsgMovePath()
    {
        header.dwType = MSG_MOVEPATH;
        header.stLength = sizeof( MsgMovePath );
        byPathLen = 0;
    }
    BYTE byPathLen;
    BYTE byMovePath[const_iMaxPath];
    short stTargetX,stTargetY;
};

//ĳ���ƶ���ĳλ��
struct MsgMoveToTarget:public Msg
{
    MsgMoveToTarget()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_MOVETOTARGET;
        header.stLength = sizeof( MsgMoveToTarget );
    }
    short stTargetX,stTargetY;
};



//ĳ���뿪��Ұ
struct MsgExitMySight:public Msg
{
    MsgExitMySight()
    {
        header.uMsgLevel = level_high;
        header.dwType = MSG_EXITMYSIGHT;
        header.stLength = sizeof( MsgExitMySight );
    }
};

struct MsgChangeMap : public Msg
{ // �л���ͼ
    MsgChangeMap()
    {
        header.dwType   = MSG_CHANGEMAP;
        header.stLength = sizeof( MsgChangeMap );
    }

    DWORD dwMapId;
    short new_map_x,new_map_y;
    BYTE  byDir;
    DWORD nGameMapId;
    float fX,fY;
    float fDirX, fDirY;
};

//�ͻ��������ͼ���
struct MsgMapLoaded:public Msg
{
    MsgMapLoaded()
    {
        header.dwType = MSG_MAPLOADED;
        header.stLength = sizeof( MsgMapLoaded );
        memset( szMacAddress, 0, sizeof( szMacAddress ) );
    }

    char szMacAddress[21];      // �ͻ��˷���MAC��ַ��������
};

//������ʾ����
struct MsgQueryDisplayName:public Msg
{
    MsgQueryDisplayName()
    {
        header.dwType = MSG_QUERYDISPLAYNAME;
        header.stLength = sizeof( MsgQueryDisplayName );
    }
    GameObjectId nWhoId;
};

//����ĳ���û�������
struct MsgAckDisplayName:public Msg
{
    MsgAckDisplayName()
    {
        header.dwType = MSG_ACKDISPLAYNAME;
        header.stLength = sizeof( MsgAckDisplayName );

        memset( szDisplayName,0, sizeof(szDisplayName) );
    }
    char szDisplayName[dr_MaxPlayerName];
};


//�������棬�϶��ǳ����Լ���
struct MsgReqAttackGround:public Msg
{
    MsgReqAttackGround()
    {
        header.dwType = MSG_REQATTACKGROUND;
        header.stLength = sizeof( *this );
    }
    short stWhichSkill;
    short stTargetX,stTargetY;
    DWORD dwSerialNo;
};

//�����������棬�������˺����˺�����
//���� �˺�ʱ����
struct MsgSeeAttackGround:public Msg
{
    MsgSeeAttackGround()
    {
        header.dwType = MSG_SEEATTACKGROUND;
        header.stLength = sizeof( *this );
    }
    short stWhichSkill;
    short stTargetX,stTargetY;
};

//������������
/*struct MsgSeeAttackGround:public MsgSeeAttack
{
MsgSeeAttackGround()
{
}
short stWhichSkill;
};*/


//����������Ч������������������
struct MsgAckAttack:public Msg
{
    MsgAckAttack()
    {
        header.dwType = MSG_ACKATTACK;
        header.stLength = sizeof( MsgAckAttack );
        stHPDec = 0;
        dwState = eFIGHT_NOFLAG;
    }
    DWORD dwState;
    //λ��
    short x,y;
    short stWhichSkill;

    short stHPDec;
    //��õľ���ֵ
    short stExpInc;

    //DWORD dwSerialNo;        // ���кţ�
    // ���˾��룬����ڵ�ǰλ��
    // ����ʹ�û��˵�Ŀ��Ϊֵ������
    short stBeatBackTargetX, stBeatBackTargetY;
    short stAttackerX, stAttackerY;
    short stAttackerHand;
};

//�Թ��߿��������˹���
struct MsgSeeAttack:public Msg
{
    MsgSeeAttack()
    {
        header.dwType = MSG_SEEATTACK;
        header.stLength = sizeof( MsgSeeAttack );

        stTarget = -1;
        stWhichSkill = -1;
        stHPDec = 0;
        dwState = eFIGHT_NOFLAG;
    }
    DWORD dwState;
    short x,y;

    short stTarget;
    short stWhichSkill;
    short stHPDec;
    // ���˾��룬����ڵ�ǰλ��
    short stBeatBackTargetX, stBeatBackTargetY;
    short stAttackerX, stAttackerY;
    short stAttackerHand;
};

// ����������ͣ�����������Ŀ��
struct MsgAttackLockTarget:public Msg
{
    enum EAttackType
    {
        AT_Attack,
        AT_NotAttack,
    };

    MsgAttackLockTarget()
    {
        header.dwType = MSG_ATTACKLOCKTARGET;
        header.stLength = sizeof( MsgAttackLockTarget );
        cAttack = AT_Attack;
    }

    char cAttack;
};

// ����������ͣ�׼��ʹ�ü��ܵ���Ϣ
struct MsgReadytoUseSpecialSkill:public Msg
{
    MsgReadytoUseSpecialSkill()
    {
        header.dwType = MSG_READYTOUSESPECIALSKILL;
        header.stLength = sizeof( MsgReadytoUseSpecialSkill );
    }
};

// ����������ͣ�ʹ�����⼼�ܵ���Ϣ
struct MsgUseSpecialSkill:public Msg
{
    MsgUseSpecialSkill()
    {
        header.dwType = MSG_USESPECIALSKILL;
        header.stLength = sizeof( MsgUseSpecialSkill );
    }
};

// ��ͻ��˷��ͣ�ͬ��׼�����⼼�ܵ�֪ͨ
struct MsgAgreeReadytoUseSpecialSkill:public Msg
{
    MsgAgreeReadytoUseSpecialSkill()
    {
        header.dwType = MSG_AGREEREADYTOUSESPECIALSKILL;
        header.stLength = sizeof( MsgAgreeReadytoUseSpecialSkill );
    }
    short shCurPermillage;    //��ǰ��ǧ����
};

// ��ͻ��˷��ͣ�ͬ��ʹ�����⼼�ܵ�֪ͨ
struct MsgAgreeUseSpecialSkill:public Msg
{
    MsgAgreeUseSpecialSkill()
    {
        header.dwType = MSG_AGREEUSESPECIALSKILL;
        header.stLength = sizeof( MsgAgreeUseSpecialSkill );
    }
};

// ��ͻ��˷��ͣ�����ʹ�����⼼�ܵ�֪ͨ
struct MsgDisableUseSpecialSkill:public Msg     // [�ṹû��]
{
    MsgDisableUseSpecialSkill()
    {
        header.dwType = MSG_DISABLEUSESPECIALSKILL;
        header.stLength = sizeof( MsgDisableUseSpecialSkill );
    }
};

// ����������ͣ�����Ŀ��
struct MsgLockTarget:public Msg
{
    MsgLockTarget()
    {
        header.dwType = MSG_LOCKTARGET;
        header.stLength = sizeof( MsgLockTarget );
        stWho = -1;
    }
    GameObjectId    stWho;                // ������Ŀ��
};

struct MsgReqSkillAttack : public Msg
{
    MsgReqSkillAttack()
    {
        header.dwType   = MSG_REQSKILLATTACK;
        header.stLength = sizeof( MsgReqSkillAttack );
        chSkillCount    = 0;
        stWho           = -1;
        isAction        = false;
    }

    bool        bCharTarget;  // �ǽ�ɫĿ�껹��λ��Ŀ��
    GameObjectId     stWho;  // ������Ŀ��
    D3DXVECTOR3 vPos;         // Ŀ���λ��
    char        chSkillCount;
    short       stSkill;
    short       stSkillLevel;
    bool        isAction;
};

struct MsgAckQueryAttack2:public Msg
{
    enum
    {
        AckQueryAttack2Ok,
        AckQueryAttack2Fail
    };
    MsgAckQueryAttack2()
    {
        header.dwType = MSG_ACKQUERYATT2;
        header.stLength = sizeof( MsgReqSkillAttack );
        Msgid = AckQueryAttack2Fail;
    }
    short Msgid;
};
// ��ѯ��ҵ�����
#define MAX_QUERY_PROPERTY 16
struct MsgQueryGameProperty:public Msg
{
    MsgQueryGameProperty()
    {
        header.dwType = MSG_QUERYGAMEPROPERTY;
        //header.stLength = sizeof( MsgQueryGameProperty );
        header.stLength = 0;

        byPropertyCount = 0;
    }
    BYTE byPropertyCount;
    short stProperties[MAX_QUERY_PROPERTY];
    bool AddProperty( GamePropertyEnum property )
    {
        if( byPropertyCount >= MAX_QUERY_PROPERTY||byPropertyCount < 0 )
            return false;
        stProperties[byPropertyCount++] = property;
        header.stLength = sizeof(header)+byPropertyCount*sizeof(short);
        return true;
    }
};

struct MsgAckGameProperty:public Msg
{
    MsgAckGameProperty()
    {
        header.dwType = MSG_ACKGAMEPROPERTY;
        header.stLength = 0;
        byPropertyCount = 0;
    }
    BYTE byPropertyCount;
    short stProperties[MAX_QUERY_PROPERTY][2];
    bool AddProperty( GamePropertyEnum property, short stValue )
    {
        if( byPropertyCount >= MAX_QUERY_PROPERTY || byPropertyCount < 0)
            return false;
        stProperties[byPropertyCount][0] = property;
        stProperties[byPropertyCount][1] = stValue;
        byPropertyCount++;
        header.stLength = sizeof(header)+byPropertyCount*sizeof(short);
    }
};

// �������������Ϸ����
struct MsgQueryAllGameProperty:public Msg
{
    MsgQueryAllGameProperty()
    {
        header.dwType = MSG_QUERYALLGAMEPROPERTY;
        header.stLength = sizeof( MsgQueryAllGameProperty );
    }
    GameObjectId stTargetId;
};

// ȷ�Ϸ������������Ϸ����
struct MsgAckAllGameProperty:public Msg
{
    MsgAckAllGameProperty()
    {
        header.dwType = MSG_ACKALLGAMEPROPERTY;
        header.stLength = sizeof( MsgQueryAllGameProperty );
    }
    GameObjectId stTargetId;
    SGameProperty gp;
};

//������Ϣ�����������ж��¼�����Ϣ
struct MsgEventRange:public Msg
{
    MsgEventRange()
    {
        header.dwType = MSG_EVENTRANGE;
        header.stLength = sizeof( MsgEventRange );

        memset( szName,0, sizeof(szName) );
    }
    char  szName[ dr_MaxNameString ];
    short stType;
    short left,right,top,bottom;
    short stLife;
};

struct MsgSkillExpUp:public Msg
{
    MsgSkillExpUp()
    {
        header.dwType = MSG_SKILLEXPUP;
        header.stLength = sizeof(MsgSkillExpUp);
    }
    DWORD dwSkillExp;
    unsigned short ustSkillID;
    short stSkilllevel;
};

//��ɫ��������
struct MsgCharSkillLevelup:public Msg
{
    MsgCharSkillLevelup()
    {
        header.dwType = MSG_CHARSKILLLEVELUP;
        header.stLength = sizeof(MsgCharSkillLevelup);
    }
    unsigned short ustSkillNewLevel ;
    unsigned short ustSkillID       ;
    int64          nUnUsedExp       ;   //��ǰʣ��δʹ�þ���
};

struct MsgCharacterLevelup : public Msg
{ // �ͻ���������������
    MsgCharacterLevelup()
    {
        header.dwType   = MSG_CHARLEVELUP;
        header.stLength = sizeof( MsgCharacterLevelup );
    }
};

struct MsgSeeCharacterLevelup : public Msg
{ // ������������������
    MsgSeeCharacterLevelup()
    {
        header.dwType   = MSG_SEECHARLEVELUP;
        header.stLength = sizeof( MsgSeeCharacterLevelup );
    }
    uint16  nNewLevel   ;   //��ǰ�ȼ�
    int64   nUnUsedExp  ;   //��ǰδʹ�þ���
};

//����ĳ�����ϳ���Ч��
struct MsgCharacterShowEff:public Msg
{
    MsgCharacterShowEff()
    {
        header.dwType = MSG_SHOWEFF;
        header.stLength = sizeof(MsgCharacterShowEff);
    }
    int    iEffID;    //����Ч���ı��
};

// �������
struct MsgDoneQuest : public Msg 
{
    MsgDoneQuest()
    {
        header.dwType = MSG_DONE_QUEST;
        header.stLength = sizeof(*this);
        bAdditionalEncouragement = false;
    }
    GameObjectId playerId;
    int           nQuestId;
    bool          bAdditionalEncouragement;                // ���߿ͻ����Ƿ����˶���Ľ���
};

struct MsgGetShop : public Msg
{
    MsgGetShop()
    {
        header.dwType = MSG_GETSHOP;
        header.stLength = sizeof(*this);
    }
};

struct MsgGetShopCenter : public Msg
{
    MsgGetShopCenter()
    {
        header.dwType = MSG_GETSHOPCENTER;
        header.stLength = sizeof( *this );
    }
};

struct STradeItemInfo
{   
    uint16 id;
    uint16 count;
};

struct MsgAckGetShopCenter : public Msg
{
    enum EConstDefine
    {
        eMaxItem = 100
    };

    MsgAckGetShopCenter()
    {
        header.dwType   = MSG_ACKGETSHOPCENTER;
        header.stLength = sizeof(MsgAckGetShopCenter);
        Reset();
    }

    void CalcLength()
    { header.stLength = sizeof(MsgAckGetShopCenter) - sizeof(STradeItemInfo) * ( eMaxItem - nCount);}

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof(MsgAckGetShopCenter) - sizeof(STradeItemInfo) * ( eMaxItem - nCount);
        memset( info, 0, sizeof(info));
    }

    short          nCount;
    STradeItemInfo info[eMaxItem];
};

struct MsgAckGetShop : public Msg
{
    enum
    {
        eMaxItem = 32
    };
    MsgAckGetShop()
    {
        header.dwType = MSG_ACKGETSHOP;
        header.stLength = sizeof( *this );
		memset(bIsItemBound, 0, sizeof(bIsItemBound));
        nCount = 0;
    }
    BYTE byType;
    bool bIsBound;
    unsigned short nIds[eMaxItem];
    short nCounts[eMaxItem];
    DWORD dwSellPrices[eMaxItem];       // ���ۼ۸�
    DWORD dwBuyPrices[eMaxItem];        // �չ��۸�
    short nBuyCounts[eMaxItem];         // ÿ������ܳ��۵�����
	bool bIsItemBound[eMaxItem];		// �Ƿ�󶨣�ֻ�������̵���
    short nCount;
};

//----------------------------- ���ת��Ϊ���� -----------------------------
struct MsgGlodCovSilver : public Msg
{
    MsgGlodCovSilver()
    {
        header.dwType = MSG_GLODCOVSILVER;
        header.stLength = sizeof( MsgGlodCovSilver );
        ustCount = 0;
    }
    unsigned short ustCount;        // ��������
};


//----------------------------- ���ת��Ϊ���� Ack -----------------------------
struct MsgAckGlodCovSilver : public Msg     // [�ṹû��]
{
    MsgAckGlodCovSilver()
    {
        header.dwType = MSG_ACKGLODCOVSILVER;
        header.stLength = sizeof( MsgAckGlodCovSilver );
        ustCount = 0;
        ustSilver =0;
    }
    unsigned short ustCount;        // Ԫ������
    unsigned short ustSilver;
};

struct MsgShopCenterBuy : public Msg
{
    MsgShopCenterBuy()
    {
        header.dwType = MSG_SHOPCENTERBUY;
        header.stLength = sizeof( MsgShopCenterBuy );
        ustCount = 0;
    }
    unsigned short ustItemId;
    unsigned short ustCount; // ����
	int8           chType;
};

struct MsgTellShopCenterOffSet : public Msg
{
    MsgTellShopCenterOffSet()
    {
        header.dwType = MSG_TellShopCenterOffSet;
        header.stLength = sizeof( MsgShopCenterBuy );
        stOffSell = 100;
    }
    short stOffSell;
};

struct MsgBuyOrSellGoods : public Msg
{
    MsgBuyOrSellGoods()
    {
        header.dwType = MSG_BUYORSELLGOODS;
        header.stLength = sizeof( MsgBuyOrSellGoods );
        ustCount = 0;
		bIsPocketShop = false;
    }
    unsigned short ustItemId;
    unsigned short ustPackIndex;
    unsigned short ustCount; // ����
    bool           bIsBuy;   // �Ƿ�����
    unsigned char  ucItemBagType;
    __int64 nGuid;          // ��������ʱ���Ҫ���Ķ�����guid����������
	bool		   bIsPocketShop;	//�Ƿ��������̵꣬���ǵĻ��ڷ�����Ҫ�������
};

struct MsgRetShopCenterItemCnt : public Msg
{

    MsgRetShopCenterItemCnt()
    {
        header.dwType = MSG_RETSHOPCENTERCNT;
        header.stLength = sizeof( MsgRetShopCenterItemCnt );
    }    
    unsigned short ustItemId;
    unsigned short ustCount;    // ʣ������
};    

struct MsgAckBuyOrSellGoods : public Msg
{
    enum EResult
    {
        error_sucess = 0,
        error_centerbuysuccess,     // �̳ǹ�����߳ɹ�
        error_shop_no_this_item,
        error_you_no_this_item,
        error_game_no_this_item,
        error_no_stock_item,
        error_money_not_enough,
        error_system_busy,
        error_additem_fail,
    };

    MsgAckBuyOrSellGoods()
    {
        header.dwType   = MSG_ACKBUYORSELLGOODS;
        header.stLength = sizeof( MsgAckBuyOrSellGoods );        
        bCanUse         = TRUE;
        n64UseTime      = -1;
        nOnlyInt        = 0;
		flag			= 0;
    }
    unsigned short ustItemId;
    unsigned short ustPackIndex;
    unsigned short ustCount;     // ����
    bool           bIsBuy;
    unsigned short ustResult;
    bool           bCanUse;
    __int64        n64UseTime;    
    DWORD          dwCurMoney;
    unsigned char  ucItemBagType;
    __int64        nOnlyInt;     // ��Ʒ������ΨһID
	uint8		   flag;
};

// �ƶ���ɾ����Ʒ������ MsgMoveGoodsReq ��Ϣ
struct MsgMoveGoods : public Msg
{
    MsgMoveGoods()
    {
        header.dwType = MSG_MOVEGOODS;
        header.stLength = sizeof(MsgMoveGoods);
        ustSrcIndex = 0;
        ustDstIndex = 0;
    }    
    unsigned short ustSrcIndex;
    unsigned short ustDstIndex;
    unsigned short ustCount;
    unsigned char  ucItemBagType;
    unsigned long  ulResult;
};

struct MsgMoveGoodsReq : public MsgMoveGoods
{
    MsgMoveGoodsReq()
    {
        header.dwType = MSG_MOVEGOODSREQ;
        header.stLength = sizeof ( MsgMoveGoodsReq );
    }

    __int64 nGuID;
};

struct MsgMoveGoodsAck : public MsgMoveGoods
{
    MsgMoveGoodsAck()
    {
        header.dwType = MSG_MOVEGOODSACK;
        header.stLength = sizeof ( MsgMoveGoodsAck );
    }

    __int64 nGuID;
};

//-------------------------������Ʒ-----------------------------by ^^ at [23/10/2006]
struct MsgChangeItemPos : public Msg
{
    MsgChangeItemPos()
    {
        header.dwType = MSG_CHANGEITEMPOS;
        header.stLength = sizeof(MsgChangeItemPos);
        ustSrcIndex = 0;
        ustDstIndex = 0;
        nWhichIs = 0;
    }
    unsigned short ustSrcIndex;
    unsigned short ustDstIndex;
    int nWhichIs;//0:pack ,1:storage
    unsigned char  ucItemBagType;
};

struct MsgUseGoods : public Msg
{
    MsgUseGoods()
    {
        header.dwType = MSG_USEGOODS;
        header.stLength = sizeof(MsgUseGoods);
        ustItemIndex = 0;
        stItemCount = 0;
        stDstChar = -1;
        stSrcChar = -1;
        nRemainValue = -1;
    }
    unsigned short    ustItemIndex;
    unsigned short    stItemCount;
    GameObjectId     stDstChar;
    GameObjectId     stSrcChar;
    int               nRemainValue;
    unsigned char     ucItemBagType;
    __int64           nGuid;
};

struct MsgUseGoodsToMount : public MsgUseGoods
{
    MsgUseGoodsToMount()
    {
        header.dwType = MSG_USEGOODSTOMOUNT;
        header.stLength = sizeof(MsgUseGoodsToMount);
        nMountIndex = -1;
    }
    short nMountIndex; // ��������
};

struct MsgEquipToWhere:public Msg
{
    MsgEquipToWhere()
    {
        header.dwType = MSG_EQUIPTOWHERE;        
        header.stLength = sizeof( *this );
        ustWhere = 0;
        ustPackIndex = 0;
    }
    unsigned short ustPackIndex;
    unsigned short ustWhere;
};

struct MsgEquip:public Msg
{
    MsgEquip()
    {
        header.dwType = MSG_EQUIP;
        header.stLength = sizeof( *this );

        nEquipWhere = -1;
    }
    unsigned short ustPackIndex;
    int8           nEquipWhere ;    // -1Ϊ��������ѡ 
};

struct MsgAckEquip:public Msg
{
    enum
    {
        Result_Success = 0
        ,Result_Failed
        ,Result_HpNotEnough
    };
    MsgAckEquip()
    {
        header.dwType = MSG_ACKEQUIP;
        header.stLength = sizeof( *this );
    }
    short stResult;
    unsigned short ustWhere;
    unsigned short ustPackIndex;
};

struct MsgUnEquip : public Msg
{
    MsgUnEquip()
    {
        header.dwType = MSG_UNEQUIP;
        header.stLength = sizeof( *this );
        stPackIndex = -1;
    }
    uint8  ustWhere;
    uint16 stPackIndex;
};

struct MsgReqScript : public Msg
{
    MsgReqScript()
    {
        header.dwType = MSG_REQ_SCRIPT;
        header.stLength = sizeof(*this);
        stNpcId = -1;
        chSelItem = -1;
    }
    GameObjectId stNpcId;
    char          chSelItem; //����Ǹ�ѡ�������ǿͻ��˷���ѡ��ģ����
};

struct MsgAckScript : public Msg
{
    enum EScriptInterfaceType
    {
        eNpcDialog  ,   // Dlg      �ӿ�
        eAskQuestion,   // Ask      �ӿ�
        eCloseDlg   ,   // CloseDlg �ӿ�
        eNpcMainDialog, // MainDlg  �ӿ�
    };

    enum ENpcDialogType
    {
        eNDT_AcceptTask , // ��������
        eNDT_Description, // �����Ի��� ����
        eNDT_FinishTask , // �������
        eNDT_Close      , // �ر�       �رնԻ���
    };

    MsgAckScript()
    {
        header.dwType   = MSG_ACK_SCRIPT;
        header.stLength = sizeof( header );
        byType          = eNpcDialog;
        dlgType         = eNDT_Description;
        stNpcId         = -1;
        szString[0]     = 0;
    }

    uint8      byType ;
    uint8	   dlgType;
    GameObjectId stNpcId;
    int        iValue ;  // ����ID
    char       szString[dr_MaxChatString];

    void SetString( const char* pszChatString )
    {
        if( strlen( pszChatString ) < dr_MaxChatString-1 )
        {
            strncpy_s(szString, sizeof( szString ), pszChatString, sizeof(szString) - 1 );
            header.stLength = sizeof(header) + sizeof(byType)+ sizeof(dlgType)+ sizeof(stNpcId) + (short)strlen( pszChatString ) + sizeof(iValue) + 1;
        }
    }
};

struct MsgScriptEnd:public Msg
{
    MsgScriptEnd()
    {
        header.dwType = MSG_SCRIPTEND;
        header.stLength = sizeof(*this);
    }
    EScriptType type;
};

struct MsgScriptVarClear:public Msg
{
    MsgScriptVarClear()
    {
        header.dwType = MSG_SCRIPTVARCLEAR;
        header.stLength = sizeof( MsgScriptVarClear );
    }
};

struct MsgScriptShow:public Msg
{
    MsgScriptShow()
    {
        header.dwType = MSG_SCRIPTSHOW;
        header.stLength = sizeof( MsgScriptShow );
        byFlag = 0;
        stImageId = -1;
        x = 0;
        y = 0;
        stLife = 0;
        stFadeTime = 0;
    }
    BYTE byFlag;
    short stImageId;
    short x, y;
    short stLife;
    short stFadeTime;
};

struct MsgCallPet:public Msg
{
    MsgCallPet()
    {
        header.dwType = MSG_CALLPET;
        header.stLength = sizeof( MsgCallPet );
        stPetId = -1;
    }
    GameObjectId stPetId;
};

struct MsgQueryCharAround:public Msg
{
    MsgQueryCharAround()
    {
        header.dwType = MSG_QUERYCHARAROUND;
        header.stLength = sizeof( MsgQueryCharAround );
        stRadius = 4;
        dwFilter = 0;
    }
    short stRadius;
    DWORD dwFilter;
};
struct MsgAckCharAround:public Msg
{
#define MAX_ACKCHARAROUND 8
    MsgAckCharAround()
    {
        header.dwType = MSG_ACKCHARAROUND;
        header.stLength = sizeof( MsgAckCharAround );
        stCharCount = 0;
    }
    struct CharInfo
    {
        GameObjectId stId;
        short stType;
        short x, y;
        int nHp;
    };
    short stCharCount;
    CharInfo charInfos[MAX_ACKCHARAROUND];
};

struct MsgQueryCharInfo : public Msg
{
    MsgQueryCharInfo()
    {
        header.dwType = MSG_QUERYCHARINFO;
        header.stLength = sizeof( MsgQueryCharInfo );
    };
    GameObjectId stChar;
};

struct MsgQueryHPInfo:public Msg
{
    MsgQueryHPInfo()
    {
        header.dwType = MSG_QUERYHPINFO;
        header.stLength = sizeof( MsgQueryHPInfo );
    }
    GameObjectId sNpcID;
};

struct MsgAckHPInfo:public Msg
{
    MsgAckHPInfo()
    {
        header.dwType = MSG_ACKHPINFO;
        header.stLength = sizeof( MsgAckHPInfo );
    }
    GameObjectId sNpcID;
    int nHp, nHpMax;
    //unsigned short ustHP,ustHPMax;
};



#define MISSION_INTRO_LEN 256
// ��������˵��
struct MsgAddMissionIntro:public Msg
{
    MsgAddMissionIntro()
    {
        header.dwType = MSG_ADDMISSIONINTRO;
        header.stLength = sizeof( MsgAddMissionIntro );
    }
    char szName[64];
    char szIntro[MISSION_INTRO_LEN];
};

// ɾ������˵��
struct MsgDelMissionIntro:public Msg
{
    MsgDelMissionIntro()
    {
        header.dwType = MSG_DELMISSIONINTRO;
        header.stLength = sizeof( MsgDelMissionIntro );
    }
    char szName[64];
};

// ������
struct MsgReqDoAction:public Msg
{
    MsgReqDoAction()
    {
        header.dwType = MSG_REQDOACTION;
        header.stLength = sizeof( MsgReqDoAction );
        stActionId = -1;
        byHoldSeconds = 0;
    };
    short stActionId;            // ����id
    BYTE byHoldSeconds;            // ��������ʱ�䣬��λ��
};
struct MsgSeeAction:public Msg
{
    MsgSeeAction()
    {
        header.dwType = MSG_SEEACTION;
        header.stLength = sizeof( MsgSeeAction );
        stActionId = -1;
    };
    short stActionId;
};
//************��Ϸ����Ⱥ���������Ϣ
//֪ͨ ���ӵķ������� ��Ϸ���������
//MSG_GWDC_ISGWORLD
struct Msg_GWDC_IsGWorld:public Msg
{
    Msg_GWDC_IsGWorld()
    {
        header.dwType = MSG_GWDC_ISGWORLD;
        header.stLength = sizeof( *this );
    }
};
//�� Gate
//MSG_GWDC_ISGATE
struct Msg_GWDC_IsGate:public Msg
{
    Msg_GWDC_IsGate()
    {
        header.dwType = MSG_GWDC_ISGATE;
        header.stLength = sizeof( *this );
    }
};
//����Ϸ�������Ϣ
//MSG_GWDC_GWORLDINFO
struct Msg_GWDC_GWorldInfo:public Msg
{
    Msg_GWDC_GWorldInfo()
    {
        header.dwType = MSG_GWDC_GWORLDINFO;
        header.stLength = sizeof( *this );

        memset( szGWorldServerName,0,sizeof(szGWorldServerName) );
    }
    char    szGWorldServerName[ dr_MaxNameString ];
    //Ŀǰʹ����Ϸ���������IP��ΪGateIP
    //��ʵ����Gate��ȥ��dwGateIP
    //DWORD    dwGateIP;
    int        iOnlineNum;
    int        iOnlineMax;
};
//��GateInfo
//MSG_GWDC_GATEINFO
struct Msg_GWDC_GateInfo:public Msg
{
    Msg_GWDC_GateInfo()
    {
        header.dwType = MSG_GWDC_GATEINFO;
        header.stLength = sizeof( *this );
        header.uMsgLevel = level_high;
        memset( szGWorldServerName,0,sizeof(szGWorldServerName) );

    }
    //Gate������Ϸ���������������
    char    szGWorldServerName[ dr_MaxNameString ];
    DWORD    dwGateIP;
    int        iOnlineNum;
    int        iOnlineMax;
};
//*************��Ϸ����Ⱥ��Ϳͻ��� ��Ϣ
//���͵��ͻ��˵���Ϸ�������Ϣ
//MSG_GWDC2C_GWORLDINFO
//iOnlineNum = -1 ˵��������Ŀǰ�ر�
struct Msg_GWDC2C_GWorldInfo:public Msg
{
    Msg_GWDC2C_GWorldInfo()
    {
        header.dwType = MSG_GWDC2C_GWORLDINFO;
        header.stLength = sizeof( *this );

        memset( szServerName,0,sizeof(szServerName) );
    }
    char    szServerName[ dr_MaxNameString ];
    DWORD    dwGateIP;
    int        iOnlineNum;
    int        iOnlineMax;
};

struct Msg_GW2GSyncCharInfo:public Msg
{
    Msg_GW2GSyncCharInfo()
    {
        header.dwType = MSG_GW2G_SYNCCHARINFO;
        header.stLength = sizeof( *this );
    }

    uint8 uchCountryID;
    uint16 ustLevel;
};

struct Msg_G2GW_AllocClient:public Msg
{ // �������ͻ�����
    Msg_G2GW_AllocClient()
    {
        header.dwType = MSG_G2GW_ALLOCCLIENT;
        header.stLength = sizeof( *this );
        memset( szUserName, 0, sizeof(szUserName) );
        memset( ip, 0, sizeof(ip) );
    }
    char szUserName[ dr_MaxPlayerName ];
    char ip[IP_LENGTH];
    DWORD dwAccountID;
};

// header.stID��Gate�з������ʱID
struct MsgAllocClientAck : public Msg
{
    MsgAllocClientAck()
    {
        header.dwType   = MSG_GW2G_RETALLOCCLIENT;
        header.stLength = sizeof( *this );
    }
    GameObjectId stIDGW; //if( -1 == stIDGW )˵������ʧ��
};

//����Ҷ��ߣ�ɾ���ͻ�����
//MSG_G2GW_DELETECLIENT
struct MsgGateNotifyGameDeleteClient : public Msg
{
    enum EDeleteType
    {
        EDT_NetOffline, // 35����ʱ�������
        EDT_Exit      , // �˳�
    };

    MsgGateNotifyGameDeleteClient()
    {
        header.dwType = MSG_G2GW_DELETECLIENT;
        header.stLength = sizeof( *this );
        header.uMsgLevel = level_tiptop;
        nType = EDT_Exit;
        SetLevel( level_tiptop );
    }

    uint8 nType;
};

struct Msg_GW2G_SyncCharPos:public Msg
{
    Msg_GW2G_SyncCharPos()
    {
        header.dwType = MSG_GW2G_SYNCCHARPOS;
        header.stLength = sizeof( *this );
    }

    uint32 dwMapID;
    short stAreaID; // TileId ��ɫ����
};

struct MsgGW2GCreateStage : public Msg 
{
    MsgGW2GCreateStage()
    {
        header.dwType = MSG_GW2G_CREATESTAGE;
        header.stLength = sizeof( *this );
    }
    DWORD dwMapId;
    DWORD dwEctypeId;
};

struct MsgGW2GReleaseStage : public Msg 
{
    MsgGW2GReleaseStage()
    {
        header.dwType = MSG_GW2G_RELEASESTAGE;
        header.stLength = sizeof( *this );
    }
    DWORD dwEctypeId;
};

//MSG_GW2G_SYNCCHARPOS
//����ҽ�ɫ������Gate�ͷŸ�ID
//MSG_GW2G_NPCEXIT
struct Msg_GW2G_NPCExit:public Msg
{
    Msg_GW2G_NPCExit()
    {
        header.dwType = MSG_GW2G_NPCEXIT;
        header.stLength = sizeof( *this );
    }
};

struct LogMsg:public Msg
{
    DWORD    GameWorldId;       //��Ϸ�����id
};

struct LogMsg_ItemLogMsg:public LogMsg
{
    LogMsg_ItemLogMsg()
    {
        header.dwType = LOGMSG_ITEMLOG;
        header.stLength = sizeof( *this );
    }
    DWORD    ItemId;        //���ߵ�ΨһID
    int      MasterId;      //��ɫ��ID
    int      Position;     //�������ڵ�λ��
    DWORD    ItemEvent;    //���߾������¼�

};

//LOGMSG_CHARACTER
enum enumCharLogEvent
{
    CharLog_Login            =    0
    ,CharLog_Logout
    ,CharLog_CreateChar
    ,CharLog_DeleteChar
    ,CharLog_Enterworld
    ,CharLog_LeaveWorld
};
struct LogMsg_Character:public LogMsg
{
    LogMsg_Character()
    {        
        header.dwType = LOGMSG_CHARACTER;
        header.stLength = sizeof( *this );
    }
    DWORD    dwAccountId;
    DWORD    dwCharacterId;
    short    stEvent;         
};

//    �������������ҽ�ɫ������
struct MsgGetPlayerInfo:public Msg
{
    MsgGetPlayerInfo()
    {
        header.dwType = MSG_GETPLAYERINFO;
        header.stLength = sizeof(MsgGetPlayerInfo);
        szPlayerName[0] = 0;
    }
    char szPlayerName[dr_MaxPlayerName];
};

struct MsgAckGetPlayerInfo:public Msg
{
    MsgAckGetPlayerInfo()
    {
        header.dwType = MSG_ACKGETPLAYERINFO;
        header.stLength = sizeof(MsgAckGetPlayerInfo);
        szPlayerName[0] = 0;
        bOnline = false;
        stPlayerId = 0;
    }
    char szPlayerName[dr_MaxPlayerName];    //����
    bool bOnline;            //�ж��Ƿ�����
    GameObjectId stPlayerId;        //npc�ı��
};

//----
//    ���������͹�������Ϣ֪ͨ����������
//----
struct MsgAckFriendLeaveInfo:public Msg     // [�ṹû��]
{
    MsgAckFriendLeaveInfo()
    {
        header.dwType = MSG_ACKFRIENDLEAVE;
        header.stLength = sizeof(MsgAckFriendLeaveInfo);
        stFriendId = -1;
    }
    GameObjectId stFriendId; //���
};


struct SOperateStone
{
    short stStoneIndex;
    short stSkillIndex;
    short stPos;
    bool  bMakeSkillAvailable;
};

//������÷�ʯ
struct MsgReqPlaceStone:public Msg
{
    MsgReqPlaceStone( )
    {
        placestone.bMakeSkillAvailable = false;
        header.dwType = MSG_REQ_PLACESTONE;
        header.stLength = sizeof(MsgReqPlaceStone);
    }
    SOperateStone placestone;
};

//�ظ�����ʯͷ
struct MsgAckPlaceStone:public Msg
{
    MsgAckPlaceStone( )
    {
        bSuccess = false;
        placestone.bMakeSkillAvailable = false;
        header.dwType = MSG_ACK_PLACESTONE;
        header.stLength = sizeof(MsgAckPlaceStone);
    }
    bool bSuccess;
    SOperateStone placestone;
};

//�����Ƴ���ʯ
struct MsgReqRemoveStone:public Msg
{
    MsgReqRemoveStone( )
    {
        header.dwType = MSG_REQ_REMOVESTONE;
        header.stLength = sizeof(MsgReqRemoveStone);
    }
    SOperateStone removestone;
};

//�ظ��Ƴ���ʯ
struct MsgAckRemoveStone:public Msg
{
    MsgAckRemoveStone( )
    {
        bSuccess = false;
        header.dwType = MSG_ACK_REMOVESTONE;
        header.stLength = sizeof(MsgAckRemoveStone);
    }
    bool bSuccess;
    SOperateStone removestone;
};

struct SOperateSubSkill
{
    short stSubSkillIndex;
    short stSkillIndex;
    short stPos;
    bool  bMakeSkillAvailable;
};

//���������ʽƬ��
struct MsgReqPlaceSubSkill:public Msg
{
    MsgReqPlaceSubSkill( )
    {
        placesubskill.bMakeSkillAvailable = false;
        header.dwType = MSG_REQ_PLACESUBSKILL;
        header.stLength = sizeof(MsgReqPlaceSubSkill);
    }
    SOperateSubSkill placesubskill;
};

//�ظ�������ʽƬ��
struct MsgAckPlaceSubSkill:public Msg
{
    MsgAckPlaceSubSkill( )
    {
        bSuccess = false;
        placesubskill.bMakeSkillAvailable = false;
        header.dwType = MSG_ACK_PLACESUBSKILL;
        header.stLength = sizeof(MsgAckPlaceSubSkill);
    }
    bool bSuccess;
    SOperateSubSkill placesubskill;
};

//�����Ƴ���ʽƬ��
struct MsgReqRemoveSubSkill:public Msg
{
    MsgReqRemoveSubSkill( )
    {
        header.dwType = MSG_REQ_REMOVESUBSKILL;
        header.stLength = sizeof(MsgReqRemoveSubSkill);
    }
    SOperateSubSkill removesubskill;
};

//�ظ��Ƴ���ʽƬ��
struct MsgAckRemoveSubSkill:public Msg
{
    MsgAckRemoveSubSkill( )
    {
        bSuccess = false;
        header.dwType = MSG_ACK_REMOVESUBSKILL;
        header.stLength = sizeof(MsgAckRemoveSubSkill);
    }
    bool bSuccess;
    SOperateSubSkill removesubskill;
};


//struct SUpSkill
//{
//    short stSkillIndex;
//    short stLevelChanged;
//};

//������������
struct MsgReqUpSkill:public Msg
{
    MsgReqUpSkill( )
    {
        //        upskill.stLevelChanged = 1;
        header.dwType = MSG_REQ_UPSKILL;
        header.stLength = sizeof(MsgReqUpSkill);
    }
    //    SUpSkill upskill;
    short stSkillId;
};

struct MsgSkillExpForSkill:public Msg
{
    MsgSkillExpForSkill( )
    {
        header.dwType = MSG_SKILLEXPTOSKILL;
        header.stLength = sizeof(MsgSkillExpForSkill);
    }
    short stSkillId;
};

struct MsgREQSkillExpForSkillID:public Msg
{
    MsgREQSkillExpForSkillID( )
    {
        header.dwType = MSG_REQ_SKILLEXPFORSKILLID;
        header.stLength = sizeof(MsgSkillExpForSkill);
    }
    short stSkillId;
};

////�ظ���������
//struct MsgAckUpSkill:public Msg
//{
//    MsgAckUpSkill( )
//    {
//        bSuccess = false;
//        upskill.stLevelChanged = 1;
//        header.dwType = MSG_ACK_UPSKILL;
//        header.stLength = sizeof(MsgAckUpSkill);
//    }
//    bool bSuccess;
//    SUpSkill upskill;
//};

//��ͼ�������
struct MsgReqProduceItem : public Msg
{
    MsgReqProduceItem( )
    {
        header.dwType = MSG_REQ_PRODUCEITEM;
        header.stLength = sizeof(MsgReqProduceItem);
    }
};

//�ظ����칤��
struct MsgAckProduceItem : public Msg
{
    MsgAckProduceItem( )
    {
        bSuccess = false;
        header.dwType = MSG_ACK_PRODUCEITEM;
        header.stLength = sizeof(MsgAckProduceItem);
    }
    bool bSuccess;
};

////��ͼ����װ��
//struct MsgReqUpgradeEquip : public Msg
//{
//    MsgReqUpgradeEquip( )
//    {
//        header.dwType = MSG_REQ_UPGRADEEQUIP;
//        header.stLength = sizeof(MsgReqUpgradeEquip);
//    }
//};
//
////�ظ�����װ��
//struct MsgAckUpgradeEquip : public Msg
//{
//    MsgAckUpgradeEquip( )
//    {
//        bSuccess = false;
//        header.dwType = MSG_ACK_UPGRADEEQUIP;
//        header.stLength = sizeof(MsgAckUpgradeEquip);
//    }
//    bool bSuccess;
//};

/*
struct SLearnSkill
{
short stSkillID;
short stSkillLevel;
bool  bAvailable;
};

//ѧ�����µļ���
struct MsgAckLearnSkill:public Msg
{
    MsgAckLearnSkill( )
    {
        bSuccess = false;
        header.dwType = MSG_ACK_LEARNSKILL;
        header.stLength = sizeof(MsgAckLearnSkill);
    }
bool bSuccess;
SLearnSkill learnskill;
};

//������µķ�ʯ
struct MsgAckGetStone:public Msg
{
    MsgAckGetStone( )
    {
        bSuccess = false;
        header.dwType = MSG_ACK_GETSTONE;
        header.stLength = sizeof(MsgAckGetStone);
    }
bool  bSuccess;
short stStoneID;
};
*/
//MSG_LOG_ACCOUNTEVENT
// GM message start
struct Msg_GM_ReqPlaceChar:public Msg
{
    enum
    {
        eAroundGM = 1<<0,
        eFindAEmptyPlace = 1<<1,

    };
    Msg_GM_ReqPlaceChar()
    {
        header.dwType = MSG_GM_REQ_PLACE_CHAR;
        header.stLength = sizeof( Msg_GM_ReqPlaceChar );
        stCharId = -1;
        dwMapId = InvalidLogicNumber;
        x = 0;
        y = 0;
        dwFlag = 0;
    }
    GameObjectId stCharId;
    DWORD dwMapId;
    short x, y;
    DWORD dwFlag;
};
//---
struct MsgPingMsg:public Msg
{
    MsgPingMsg()
    {
        //PING��Ϣ����ȷ���������Ƿ�����������ȷ�Ϸ�����֮���Ƿ���Ҫ�����������ڱȽ���Ҫ���ͣ�������Ϊ�͵ȼ�
        //        header.uMsgLevel = level_low;
        dwTime = 0;
        header.dwType = MSG_PING;
        header.stLength = sizeof(MsgPingMsg);
    }
    DWORD    dwTime;
};

//MSG_SETONLINE_LOGIN2ACCOUNT

struct Msg_UpdateOnline_Login2Account:public Msg
{
    enum enumConst
    {
        const_iMaxAccount = 100
    };
    Msg_UpdateOnline_Login2Account( bool bOnline )
    {
        header.dwType = MSG_UPDATEONLINE_LOGIN2ACCOUNT;
        stAccountNum = 0;
        bSetOnline = bOnline;
    }
    bool AddAccountID( DWORD dwAccountID )
    {
        if( stAccountNum >= const_iMaxAccount|| stAccountNum < 0 )
            return false;
        dwAccountIDs[ stAccountNum ++ ] = dwAccountID;
        CaluLength();
        return true;
    }

    void CaluLength()
    {
        header.stLength = sizeof( Msg_UpdateOnline_Login2Account )
            + ( stAccountNum - 1 )*sizeof( DWORD );
    }
    //�������˺����� ���ǲ�����
    bool    bSetOnline;
    short    stAccountNum;
    DWORD    dwAccountIDs[1];
};

struct MsgQueryServerID:public Msg      // [�ṹû��]
{
    MsgQueryServerID()
    {
        header.dwType = MSG_QUERYSERVERID;
        header.stLength = sizeof( *this );
    }
};

struct MsgServerID:public Msg
{
    MsgServerID()
    {
        header.dwType = MSG_SERVERID;
        header.stLength = sizeof( *this );
    }
    DWORD dwServerID;
};

struct MsgAllNpcOnTheMap : public Msg
{
    enum
    {
        eMaxNpc = 256,
        eMaxNpcName = 16,
        eMaxAnimName = 16,
    };

    struct SNpcInfo
    {
        short stNpcId;
        BYTE  byNpcType;
        short x, y;
        float fx, fy;
        char  szName[eMaxNpcName];
        char  szAnimName[eMaxAnimName];
        //char szImgPath[eMaxName];
        //bool bMask;
    };

    MsgAllNpcOnTheMap()
    {
        header.dwType   = MSG_ALLNPCONTHEMAP;
        header.stLength = 0;
        Reset();
    };

    bool AddNpc( const SNpcInfo* pInfo )
    {
        if( wNpcCount >= eMaxNpc || !pInfo||wNpcCount < 0 )
            return false;
        infos[wNpcCount++] = *pInfo;
        header.stLength = sizeof( MsgAllNpcOnTheMap ) - (eMaxNpc - wNpcCount) * sizeof( SNpcInfo );
        return true;
    }

    void Reset()
    {
        wNpcCount = 0;
        memset(infos, 0, sizeof(infos));
        header.stLength = sizeof( MsgAllNpcOnTheMap ) - (eMaxNpc - wNpcCount) * sizeof( SNpcInfo );
    }

    WORD     wNpcCount;
    SNpcInfo infos[eMaxNpc];    
};

struct MsgQueryServerInfo:public Msg
{
    MsgQueryServerInfo()
    {
        header.dwType = MSG_QUERYSERVERINFO;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckQueryServerInfo:public Msg
{
    MsgAckQueryServerInfo()
    {
        header.dwType = MSG_ACK_QUERYSERVERINFO;
        header.stLength = sizeof(*this);
        dwOnlineCount = 0;
    }
    DWORD dwOnlineCount;
};


struct SSLMSGSendPublicKey:public Msg   // [�ṹû��]
{
    SSLMSGSendPublicKey()
    {
        header.dwType = MSG_SSLSendPublicKey;
        header.stLength = sizeof(*this);
    }
    DWORD bUseDigitalSignature;
    DWORD bEncrypt;
    DWORD bDecrypt;
    DWORD dwKeyLen;
    BYTE  KeyData[256];
};

struct SSLMSGSendSessionKey:public Msg      // [�ṹû��]
{
    SSLMSGSendSessionKey()
    {
        header.dwType = MSG_SSLSendSessionKey;
        header.stLength = sizeof(*this);
    }
    DWORD dwKeyLen;
    BYTE  KeyData[256];
};

struct SSLMSGFinished:public Msg            // [�ṹû��]
{
    SSLMSGFinished()
    {
        header.dwType = MSG_SSLExchangKeyFinished;
        header.stLength = sizeof(*this);
    }
};

struct MsgTellReputation : public Msg
{
    MsgTellReputation()
    {
        header.dwType = MSG_TELLREPUTATION;
        header.stLength = sizeof(*this);

        dwReputation = 0;
    }
    unsigned long dwReputation;
};

struct MsgReputationChange : public Msg
{
    MsgReputationChange()
    {
        header.dwType = MSG_REPUTATIONCHANGE;
        header.stLength = sizeof( MsgReputationChange );
        dwReputation = 0;
    };
    unsigned long dwReputation;
};

struct MsgTellExploit : public Msg
{
    MsgTellExploit()
    {
        header.dwType = MSG_TELL_EXPLOIT;
        header.stLength = sizeof(*this);
        dwExploit = 0;
    }
    unsigned long dwExploit;
};

struct MsgExploitChange:public Msg
{
    MsgExploitChange()
    {
        header.dwType = MSG_EXPLOIT_CHANGE;
        header.stLength = sizeof(*this);

        dwCurrentExploit = 0;
    }
    uint32 dwCurrentExploit;
};

//����ı䵱ǰ�ƺ�
struct MsgChangeTitleReq : public Msg
{
    MsgChangeTitleReq()
    {
        header.dwType = MSG_CHANGETITLEREQ;
        header.stLength = sizeof(*this);
    }

    short nTitleID;
};

//���߿ͻ��˵�ǰ�ƺ�
//����Χ��Ұ�ڵ���Ҷ��ᷢ�������Ϣ
struct MsgTellCurrentTitle : public Msg
{
    MsgTellCurrentTitle()
    {
        header.dwType = MSG_TELLCURRENTTITLE;
        header.stLength = sizeof(*this);

        nError = TellSuccess;
        memset( szTitleTargetName, 0, sizeof( szTitleTargetName ) );
    }

    enum TellError
    {
        TellSuccess = 0,
        TellNoThisTile,
    };

    short nTitleID;
    char szTitleTargetName[dr_MaxPlayerName];   // ���޹�ϵ( ��Ҫ���͸������ż������ )
    short nError;                 //������
};

//���߿ͻ��˳ƺ��б�
struct MsgTellTitleList : public Msg
{
    MsgTellTitleList()
    {
        header.dwType = MSG_TELLTITLELIST;
        header.stLength = sizeof(*this);
        memset(nTitleArray, 0, sizeof(nTitleArray));
    }

    short nCurrentTitleID;          //��ǰ�ĳƺ�Id
    short nTitleArray[MAX_TITLE_COUNT];
};

//���һ���ƺ�
struct MsgAddTitleReq : public Msg
{
    MsgAddTitleReq()
    {
        header.dwType = MSG_ADDTITLEREQ;
        header.stLength = sizeof(*this);
    }

    short nTitleID;
};

struct MsgAddTitleAck : public Msg
{
    MsgAddTitleAck()
    {
        header.dwType = MSG_ADDTITLEACK;
        header.stLength = sizeof(*this);

        nError = Add_Success;

        nActiveTime = 0;
    }

    enum AddResult
    {
        Add_Success = 0,
        Add_ErrorID,
        Add_NoThisTitle,
        Add_TitleFull,
        Add_AlreadyExist,
        Add_HasAdvancedTitle,           //�Ѿ����ڸ��߼��ĳƺ���(�Ѿ���ȡ����)
        Add_Unknow,
    };

    short nTitleID;
    __int64 n64AcquireTime; // ��óƺŵ�ʱ��
    uint32 nActiveTime;     // �ƺŵ���Чʱ��

    short nError;
};

//ɾ��һ���ƺ�
struct MsgRemoveTitleReq : public Msg       // [�ṹû��]
{
    MsgRemoveTitleReq()
    {
        header.dwType = MSG_REMOVETITLEREQ;
        header.stLength = sizeof(*this);
    }
    short nTitleID;
};

struct MsgRemoveTitleAck : public Msg
{
    MsgRemoveTitleAck()
    {
        header.dwType = MSG_REMOVETITLEACK;
        header.stLength = sizeof(*this);

        nError = Remove_Success;
    }

    enum RemoveResult
    {
        Remove_Success = 0,
        Remove_ErrorID,
        Remove_NoThisTitle,
        Remove_Unknow,
    };

    short nTitleID;
    short nError;
};


struct MsgTellOfficialLevel:public Msg
{
    MsgTellOfficialLevel()
    {
        header.dwType = MSG_TELL_OFFICIALLEVEL;
        header.stLength = sizeof(*this);

        stCharId = -1;
        byOfficialLevel = 0;
    }
    GameObjectId stCharId;
    BYTE  byOfficialLevel;
};

struct MsgTeachSkill : public Msg
{
    enum
    {
        MAXSKILL = 64
    };
    MsgTeachSkill()
    {
        header.dwType = MSG_TEACHSKILL;
        header.stLength = sizeof(*this);
        nNum = 0;
    }
    short        nId[MAXSKILL];
    short nNum;
};

struct MsgLearnSkill : public Msg
{
    MsgLearnSkill()
    {
        header.dwType = MSG_LEARNSKILL;
        header.stLength = sizeof(*this);
    }
    short stSkillId;
};


struct MsgChangePKRecord : public Msg
{
    MsgChangePKRecord()
    {
        header.dwType = MSG_CHANGE_PKRECORD;
        header.stLength = sizeof(*this);
    }
    short stWinTimes;
    short stLostTimes;
};

struct MsgTellMapNpcInfo:public Msg     //[�ṹû��]
{
    enum
    {
        eMaxNpc = 255
    };
    struct Info
    {
        short x, y;
        BYTE byFlag;
    };
    MsgTellMapNpcInfo()
    {
        header.dwType = MSG_TELLMAP_NPCINFO;
        header.stLength = sizeof(*this);
        byNpcCount = 0;
    }
    BYTE byNpcCount;
    Info infos[eMaxNpc];

};
struct MsgTellMapNpcQuest:public Msg
{
    enum 
    {
        eMaxQuest = 512
    };
    struct Info
    {
        short stQuestId;
        GameObjectId stNpcId;
        char chState;    // npc�������״̬��
    };
    MsgTellMapNpcQuest()
    {
        header.dwType = MSG_TELLMAP_NPCQUEST;
        header.stLength = sizeof(*this);
        byQuestCount = 0;
    };
    BOOL    AddInfo( short stQuestId, short stNpcId, char chState )
    {
        if( byQuestCount >= eMaxQuest|| byQuestCount < 0 )
            return FALSE;
        infos[byQuestCount].stQuestId = stQuestId;
        infos[byQuestCount].stNpcId = stNpcId;
        infos[byQuestCount].chState = chState;
        byQuestCount++;

        header.stLength = sizeof(header)+sizeof(byQuestCount)+byQuestCount*sizeof(Info);
        return TRUE;
    }
    BYTE byQuestCount;
    Info infos[eMaxQuest];
};


struct MessageContainer:public Msg      // [�ṹû��]
{
    MessageContainer()
    {
        header.dwType = MSG_CONTAINER;
        header.stLength = sizeof( *this );
    };
    void SetContent( char* pszBuffer, int nBufferSize )
    {
        memcpy( szContent, pszBuffer, nBufferSize );
        header.stLength = sizeof( *this ) + nBufferSize;
    }
    char szContent[1];
};

struct MsgScriptPlayerMusic :public Msg 
{
    MsgScriptPlayerMusic()
    {
        header.dwType = MSG_SCRIPT_PLAYERMUSIC;
        header.stLength = sizeof( *this );
    }

    void SetFileName( const char* szFile )
    {
        strncpy_s(szFileName, sizeof( szFileName ), szFile, sizeof(szFileName) - 1 );
    }

    short stParameter;
    char szFileName[256];
};

struct MsgScriptMakeItem :public Msg 
{ // ToCheck
    MsgScriptMakeItem()
    {
        header.dwType = MSG_SCRIPT_MAKEITEM;
        header.stLength = sizeof( *this );
    }
    enum
    {
        IDMaxCount = 8
    };
    enum
    {
        MT_COMPOUND = 0        // �ϳ�
        ,MT_REFINE            // ����
        ,MT_INTENSIFY        // ǿ��

        ,MT_MAX
    };
    enum
    {
        MAX_ITEMMAKE_ID = 32
    };

    enum CanEquip
    {
        eHair                //ͷ��
        ,eHelmet            //ͷ��
        ,eFace                //��
        ,eArmour            //����
        ,eGlove                //����
        ,eShoe                //Ь��
        ,elHandItem            //������Ʒ
        ,erHandItem            //������Ʒ
        ,eHeadWear            //ͷ��
        ,eLeftHandShieldPart//��
        ,eShoulderPart        //����
        ,eTrousersPart        //����
        //,eAccouterment        
        ,eRing                //��ָ
        //,elRing                //��ָ
        ,erBangle            //����
        ,eNecklace          //����
        ,eSash              //����
        ,eMaxEquip
    };
    struct S_Id
    {
        short stIdBegin;
        short stIdEnd;
    };
    BYTE        m_byNewOrOld;   //�ºϳɻ����ϵĺϳɣ�1 = NEW��0 = old��
    int            m_nRate;        // �ϳɼ���
    //BYTE        m_byMakeType;    // �ϳ�/����/ǿ��
    S_Id        m_stIDs[IDMaxCount];// ΪID������
    int         m_nCreatRuleId[MAX_ITEMMAKE_ID];    //�䷽ID
    BYTE        m_byCount;        // m_stItems����
    //float       m_X1;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //float       m_X2;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //float       m_X3;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //float       m_X4;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //float       m_Y;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //float       m_a;            //���ɺϳ���Ʒ��ֵ��ϵ��
    //BYTE        m_nItemType;   //������Ʒ��������
    //BYTE        m_byEquipType; //װ����������/װ��
    //float       m_fWaste;      //�ϳɵ���Ķ�
    //float       m_X;           //���ɺϳ���Ʒ��ֵ��ϵ��
};

struct MsgScriptReqShowQuestDlg : public Msg
{
    enum
    {
        eInfoLengthMax    = 256,

        ShowType_Normal   = 0,
        ShowType_Pub      = 1,       // ��ʾ�ƹ����񴰿�
        ShowType_Royal    = 2,       // �ʰ����񴰿�
        ShowType_ConQuest = 3,       // ��������
    };
    MsgScriptReqShowQuestDlg()
    {
        header.dwType = MSG_SCRIPT_REQ_SHOW_QUEST_DLG;
        header.stLength = sizeof( *this );

        chShowType = ShowType_Normal;
    }
    GameObjectId stNpcId;
    char    szInfo[eInfoLengthMax];


    char chShowType;
};


struct MsgScriptAckShowQuestDlg : public Msg
{
    MsgScriptAckShowQuestDlg()
    {
        header.dwType = MSG_SCRIPT_ACK_SHOW_QUEST_DLG;
        header.stLength = sizeof( *this );

        stQuestId = -1;
    }
    short stQuestId;
};
struct MsgQueryMapNpcList : public Msg      // [�ṹû��]
{
    MsgQueryMapNpcList()
    {
        header.dwType = MSG_QUERYMAPNPCLIST;
        header.stLength = sizeof( *this );
    }
};

struct MsgPopMapNpcList : public Msg
{
    MsgPopMapNpcList()
    {
        header.dwType = MSG_POPMAPNPCLIST;
        header.stLength = sizeof( *this );
    }
};

// �ͻ��������������
struct MsgReceiveQuestReq : public Msg
{
    MsgReceiveQuestReq()
    {
        header.dwType = MSG_RECEIVEQUESTREQ;
        header.stLength = sizeof( MsgReceiveQuestReq );
    }

    GameObjectId stNpcID;          // npc�Ķ�̬ID
    short        stQuestID;        // �ӵ�����ID
};

// �ͻ�������ˢ�¾ƹ�����
struct MsgResetPubQuestReq : public Msg
{
    MsgResetPubQuestReq()
    {
        header.dwType = MSG_RETPUBQUESTREQ;
        header.stLength = sizeof( MsgResetPubQuestReq );
    }

    GameObjectId stNpcID;          // npc�Ķ�̬ID
    char         chType;           // ˢ�µ���������
};

// ��������Ӧˢ�¾ƹ�����,�ͻ���ˢ�������б�
struct MsgResetPubQuestAck : public Msg
{
    MsgResetPubQuestAck()
    {
        header.dwType = MSG_RETPUBQUESTACK;
        header.stLength = sizeof( MsgResetPubQuestAck );
        stResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0, 
        ECD_Fail    = 1,
    };

    GameObjectId stNpcID;          // npc�Ķ�̬ID
    char chType;            // ˢ�µ���������
    short stResult;         // ���صĽ��          
};

struct MsgChangeFightState : public Msg
{
    MsgChangeFightState()
    {
        header.dwType = MSG_CHANGE_FIGHTSTATE;
        header.stLength = sizeof( *this );
    }
    bool        bFight;
    GameObjectId    playerId;
};

struct MsgSetDialogName : public Msg
{
    enum
    {
        NAME_MAXLENGTH = 32
    };
    MsgSetDialogName()
    {
        header.dwType = MSG_SETDIALOGNAME;
        header.stLength = sizeof(*this);

        memset( szName, 0, sizeof( szName ) );
    }
    char szName[NAME_MAXLENGTH];
};

struct MsgCharList : public Msg
{
    struct CharInfo
    {
        char szAccount[dr_MaxNameString];
        char szCharName[dr_MaxPlayerName];
        char szIP[dr_MaxNameString];
        WORD wLevel;
        WORD wProfession;
    };
    MsgCharList()
    {
        header.dwType = MSG_CHARLIST;
        header.stLength = sizeof( *this);
    }
    CharInfo charInfo;
};

struct MsgCharInfo : public Msg         // [�ṹû��]
{
    MsgCharInfo()
    {
        header.dwType = MSG_CHARINFO;
        header.stLength = sizeof( *this);
    }
};

struct MsgScriptSetHotkey : public Msg 
{
    MsgScriptSetHotkey()
    {
        header.dwType = MSG_SCRIPT_SETHOTKEY;
        header.stLength = sizeof(*this);
    }
    unsigned short    ustIndex;
    int        nID;
};

struct MsgGMCommand : public Msg
{
    MsgGMCommand()
    {
        header.dwType = MSG_GMCOMMAND;
        header.stLength = sizeof(*this);
    }
    char szCommand[300];
};

struct MsgUpdateTime : public Msg 
{
    enum
    {
        YEAR_NAME_LENGTH = 16
    };
    MsgUpdateTime()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_UPDATETIME;
        header.stLength = sizeof(*this);
    }
    char  szYearName[YEAR_NAME_LENGTH];
    short stYear;
    short stMonth;
    short stDay;
    short stHour;
    short stMinute;
};

struct MsgUpInfo : public Msg
{
    MsgUpInfo()
    {
        header.dwType = MSG_SHOWLEVELINFO;
        header.stLength = sizeof(MsgUpInfo);
    }

    float nInfo[EBaseAttr_MaxSize];
};

struct MsgReqFlyToMap : public Msg
{
    MsgReqFlyToMap()
    {
        header.dwType = MSG_REQ_FLYTOMAP;
        header.stLength = sizeof(*this);
    }
    DWORD dwMapId;
    DWORD dwX, dwY;
};

struct MsgReqEctypeMapInfo : public Msg     // [�ṹû��]
{
    MsgReqEctypeMapInfo()
    {
        header.dwType = MSG_REQ_ECTYPEMAP_INFO;
        header.stLength = sizeof(*this);
    }
};

struct MsgReqBackCharaterlistSucess : public Msg    // [�ṹû��]
{
    MsgReqBackCharaterlistSucess()
    {
        header.dwType = MSG_REQ_BACKCHARATERLISTSUCESS;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckEctypeMapInfo : public Msg 
{
    enum
    {
        eEctypeMaxCount = 10,
    };
    MsgAckEctypeMapInfo()
    {
        header.dwType = MSG_ACK_ECTYPEMAP_INFO;
        header.stLength = sizeof(*this);
        //
        ustEctypeCount = 0;
        dwLifeLimitTime = 0;
    }
    bool AddEctype( DWORD dwId )
    {
        if ( ustEctypeCount >= eEctypeMaxCount )
        {
            return false;
        }
        dwEctypeIds[ustEctypeCount++] = dwId;
        return true;
    }
    DWORD dwEctypeIds[eEctypeMaxCount];
    unsigned short ustEctypeCount;
    DWORD dwCurEctypeId;
    DWORD dwCurMapId;
    DWORD dwLifeLimitTime;
};

struct MsgAckFirstTip : public Msg
{
    MsgAckFirstTip()
    {
        header.dwType = MSG_ACK_FIRSTTIP;
        header.stLength = sizeof(*this);
    }
    unsigned short usFirstInfo;
};

struct MsgReqFirstTip : public Msg
{
    MsgReqFirstTip()
    {
        header.dwType = MSG_REQ_FIRSTTIP;
        header.stLength = sizeof(*this);
    }
    unsigned short usFirstInfo;
};

struct MsgSendRealTime : public Msg
{
    MsgSendRealTime()
    {
        header.dwType = MSG_SEND_REAL_TIME;
        header.stLength = sizeof(*this);
    }
    char       strTime[30];
    __time64_t time;
};

//�ı�����
struct MsgChangePower:public Msg    // [�ṹû��]
{
    MsgChangePower()
    {
        header.dwType = MSG_CHANGEPOWER;
        header.stLength = sizeof(*this);
    }

    short stPower;
    short stPowerMax;
};
//�ı������
struct MsgChangePowerPoint:public Msg       // [�ṹû��]
{
    MsgChangePowerPoint()
    {
        header.dwType = MSG_CHANGEPOWERPOINT;
        header.stLength = sizeof(*this);
    }
    short stPoint;
    short stPointMax;
};
//struct MsgFriendOnExit:public Msg
//{
//    MsgFriendOnExit()
//    {
//        header.dwType = MSG_FRIENDOFFLINE;
//        header.stLength = sizeof(*this);
//    }    
//    short stMemberID;
//};


struct MsgCovCorps:public Msg
{
    MsgCovCorps()
    {
        header.dwType = MSG_COVCORPS;
        header.stLength = sizeof( MsgCovCorps );
    }
    unsigned char    AssignMode;
};

struct MsgReqCovCorps:public Msg        // [�ṹû��]
{
    MsgReqCovCorps()
    {
        header.dwType = MSG_REQCOVCORPS;
        header.stLength = sizeof( MsgReqCovCorps );
    }
};

struct MsgChangeBagSize : public Msg 
{
    MsgChangeBagSize()
    {
        header.dwType = MSG_CHANGE_BAGSIZE;
        header.stLength = sizeof(*this);
    }
    unsigned short ustCurSize;
    unsigned char  ucItemBagType;
};

struct MsgUnSoulBound : public Msg
{
    enum
    {
        eSuc = 0,
        eNotBound,
        eNotEnoughMoney,
        eMax
    };
    MsgUnSoulBound()
    {
        header.dwType = MSG_UNSOULBOUND;
        header.stLength = sizeof(*this);
    }
    short stRec;
};

struct MsgCallUnSoulBound : public Msg
{
    MsgCallUnSoulBound()
    {
        header.dwType = MSG_CALLUNSOULBOUND;
        header.stLength = sizeof(*this);
    }
};

struct MsgMoveUnSoulBound : public Msg
{
    enum
    {
        eIconToPack = 0,
        ePackToIcon,
        eMax
    };
    MsgMoveUnSoulBound()
    {
        header.dwType = MSG_MOVE_UNSOULBOUND;
        header.stLength = sizeof(*this);
    }
    short stMoveType;
    unsigned short stSrcIndex;
    unsigned short stDstIndex;
    unsigned short stCount;
};

struct MsgReliveNeedSilver:public Msg
{
    MsgReliveNeedSilver()
    {
        header.dwType = MSG_RELIVENEEDSILVER;
        header.stLength = sizeof(*this);
    }
    short stSilver;
    short stSilverAllMpHp;
};

struct MsgRepairCostRmb : public Msg
{
    MsgRepairCostRmb()
    {
        header.dwType = MSG_FARREPAIRCOSTRMB;
        header.stLength = sizeof( *this );
    }
    int nSilver;
};

struct MsgTellCLockNum : public Msg
{
    MsgTellCLockNum()
    {
        header.dwType = MSG_TELLC_LOCKNUM;
        header.stLength = sizeof( *this );
    }
    int nLockNum;
    int nLockNumMax;
    bool bIsShow;
};

struct MsgMoveLockIntensify : public Msg
{
    enum
    {
        eIconToPack = 0,
        ePackToIcon,
        eMax
    };
    MsgMoveLockIntensify()
    {
        header.dwType = MSG_MOVE_LOCKINTENSIFY;
        header.stLength = sizeof(*this);
    }
    short stMoveType;
    unsigned short stSrcIndex;
    unsigned short stDstIndex;
    unsigned short stCount;
};

struct MsgLockIntensify : public Msg
{
    enum
    {
        eSuc = 0,        
        eNotEnoughMoney,
        eLocked,
        eIntensifyMax,
        eMax
    };
    MsgLockIntensify()
    {
        header.dwType = MSG_LOCKINTENSIFY;
        header.stLength = sizeof(*this);
    }
    short stRec;
};
struct MsgCallLockIntensifyUI : public Msg
{
    MsgCallLockIntensifyUI()
    {
        header.dwType = MSG_CALLLOCKINTENSIFYUI;
        header.stLength = sizeof(*this);
    }
};
struct MsgCallLockIntensify : public Msg
{
    MsgCallLockIntensify()
    {
        header.dwType = MSG_CALLLOCKINTENSIFY;
        header.stLength = sizeof(*this);
    }
};

struct MsgChangeBattleFlag : public Msg     // ��Client���á�
{
    MsgChangeBattleFlag()
    {
        header.dwType = MSG_CHANGE_BATTLEFLAG;
        header.stLength = sizeof(*this);
    }
    GameObjectId shCharID;
    short		 shFlag;
};

struct MsgCompoundRateAdd : public Msg
{
    MsgCompoundRateAdd()
    {
        header.dwType = MSG_TELL_CompoundRateAdd;
        header.stLength = sizeof(*this);
    }
    short stRates;
};

struct MsgIntensifyRateAdd : public Msg
{
    MsgIntensifyRateAdd()
    {
        header.dwType = MSG_TELL_IntensifyRateAdd;
        header.stLength = sizeof(*this);
    }
    short stRates;
};

struct MsgCheckPlayerEnterWorld
{
    enum eMaxMsgSize
    {
        e_iMaxNum = 20
    };

    MsgCheckPlayerEnterWorld()    
    {
        nNum = 2;
        nInstead = 2;
        for(int n = 0;n<e_iMaxNum;n++)
        {
            fCheckNum[n] = 0;
        }
    }

    bool AddResult(int nSum,int nRe)
    {
        if (nSum > e_iMaxNum||nSum < 0)
        {
            return false;
        }
        if (nSum == 0)
        {
            fCheckNum[0] = 1.0f;
        }
        else
        {            

            float  fTemp1 = 1.0f;

            for (int n = 0; n < nSum;n++)
            {
                fTemp1 = 1.0f/(n+1);
                fTemp1 = 1 + fTemp1;

                fCheckNum[n] = fTemp1*fTemp1;
            }
            int nP = 0;
            if (nRe > 0)
            {
                nP = nSum%nRe;
            }
            for(int nloop = 0; nloop < nP;nloop++)
            {
                if (nloop*nRe > nSum||(nloop*nRe + 1) > nSum)
                {
                    continue;
                }
                float fTemp2 = fCheckNum[nloop*nRe];
                float fTemp3 = fCheckNum[nloop*nRe + 1];

                fCheckNum[nloop*nRe] = fTemp3;
                fCheckNum[nloop*nRe+1] = fTemp2;
            }
        }
        return true;
    }

    int nInstead;
    int nNum;
    float fCheckNum[e_iMaxNum];
};

struct MsgRightCheck2:public Msg    // ��Server:û�� Client:ʹ�ô���ע�͵��ˡ�
{
    MsgRightCheck2()
    {
        header.dwType = MSG_RIGHTCHECK2;
        header.stLength = sizeof(MsgRightCheck2);
        strncpy_s(szGameVersion, sizeof( szGameVersion ), "1.0.0.0", sizeof( szGameVersion ) - 1 );        
        dwGameVerSion[0]=1;
        dwGameVerSion[1]=0;
        dwGameVerSion[2]=0;
        dwGameVerSion[3]=1;
    }

    /*sDWORD dwClientVersion;*/
    DWORD dwGameVerSion[4];
    char  szGameVersion[dr_MaxGameVersion];
    char  szUserName[dr_MaxPlayerName];
    MsgCheckPlayerEnterWorld checkplayer;
};

//��¼��Ϣ2
struct MsgLogin2:public Msg     // ���ͻ������á�
{
    MsgLogin2()
    {
        header.dwType = MSG_LOGIN2;
        header.stLength = sizeof( MsgLogin2 );
        strncpy_s( szGameVersion, sizeof( szGameVersion ), "1.0.0.0", sizeof( szGameVersion ) - 1 );

        memset( szUserName,0,dr_MaxPlayerName + dr_MaxPassword );
        dwGameVerSion[0]=1;
        dwGameVerSion[1]=0;
        dwGameVerSion[2]=0;
        dwGameVerSion[3]=1;
        IsForceLogin = false;
    }
    char szUserName[ dr_MaxPlayerName ];
    char szPassword[ dr_MaxPassword ];
    short stModelID;
    char szGameVersion[dr_MaxGameVersion];
    char szIP[20];
    int isSoftKeboardChar;
    DWORD dwGameVerSion[4];
    char checkkey[64];//һ���Ը����ĳ���
    bool IsForceLogin;
    MsgCheckPlayerEnterWorld checkplayer;
};

// �޸����������ʾ���λ
struct MsgModifyHelpFlagC2S : public Msg
{
    MsgModifyHelpFlagC2S()
    {
        header.dwType = MSG_MODIFY_PLAYER_HELP_FLAG;
        header.stLength = sizeof( MsgModifyHelpFlagC2S );
        dwHelpFlag = 0;
    }

    DWORD dwHelpFlag;
};

// ������нű�
struct MsgAskExecuteScript : public Msg
{
    MsgAskExecuteScript()
    {
        header.dwType = MSG_ASK_EXECUTE_SCRIPT;
        header.stLength = sizeof( MsgAskExecuteScript );
        scriptId = 0;
    }

    DWORD scriptId;
};

struct MsgTellLS_GS_OK : public Msg     // ���ṹû�á�
{
    MsgTellLS_GS_OK()
    {
        header.dwType = MSG_Tell_LoginServer_GateOK;
        header.stLength = sizeof( MsgTellLS_GS_OK );
    }
    short stGwId;
    char szUserName[ dr_MaxPlayerName ];
};

// �л��Զ�����װ
struct MsgSwitchSuit : public Msg
{
    MsgSwitchSuit()
    {
        header.dwType = MSG_SWITCHSUIT;
        header.stLength = sizeof( MsgSwitchSuit );
        nSuitIndex = 0;
    }
    uint8 nSuitIndex;
};

// ʹ���ػ���ʹ
struct MsgAckUseAngell : public Msg
{
    MsgAckUseAngell()
    {
        header.dwType = MSG_USE_ANGELL;
        header.stLength = sizeof( MsgAckUseAngell );
    }
};

struct MsgChannelInfo : public Msg
{
    enum
    {
        MAX_CHANNEL_COUNT = 10,
    };

    MsgChannelInfo()
    {
        header.dwType   = MSG_CHANNELSINFO;
        header.stLength = sizeof( MsgChannelInfo );
        Reset();
    }
    
    bool AddChannelInfo( const SChannelInfo& sci )
    {
        if ( nChannelsCount >= MAX_CHANNEL_COUNT)
            return false;

        channels[nChannelsCount] = sci;        
        ++nChannelsCount;
        return true;
    }

    SChannelInfo* GetChannelInfo( int nIndex )
    {
        if ( nIndex >= nChannelsCount || nIndex >= MAX_CHANNEL_COUNT )
            return NULL;
        
        return &(channels[nIndex]);
    }

    void Reset()
    {
        memset( channels, 0, sizeof(SChannelInfo)*MAX_CHANNEL_COUNT);
        nChannelsCount = 0;
    }

    SChannelInfo channels[MAX_CHANNEL_COUNT];
    char nChannelsCount;
    unsigned long nMapId;
};

// C2S
struct MsgSelectChannel : public Msg
{
    MsgSelectChannel()
    {
        header.dwType   = MSG_SELECTCHANNEL;
        header.stLength = sizeof( MsgChannelInfo );

        memset( &channel, 0, sizeof(channel));
    }

    SChannelInfo channel;
    unsigned long nAccountId;
};

// S2S
struct MsgS2SSelectChannel : public MsgSelectChannel
{
    MsgS2SSelectChannel()
    {
        header.dwType   = MSG_SELECTCHANNEL_SS;
        header.stLength = sizeof( MsgS2SSelectChannel );
    }
    
    char nServerType;        // ����������
    unsigned long nServerId; // ������Id
};

struct MsgAckSwitchGate : public Msg
{
    MsgAckSwitchGate()
    {
        header.dwType   = MSG_ACK_SWITCHGATE;
        header.stLength = sizeof( MsgAckSwitchGate );
    }
};

struct SEquipment
{
    short stHair;
    short stHelmet;
    short stFace;
    short stArmour;
    short stGlove;
    short stShoe;
    short stCape;
    short stWeapon;
    short stShield;
};

//��Ϸ������ص�����
struct SCharInWorld
{
    DWORD dwMapID;
    short stX,stY;
    BYTE  byDir;
};

// (Client->Login->Center) || (GameServer->Center)
struct MsgEnterWorld : public Msg
{
    MsgEnterWorld()
    {
        header.dwType    = MSG_ENTERWORLD;
        header.stLength  = sizeof( MsgEnterWorld );
        nSwitchStageType = 0;
    }
    short stWhichSlot;
    DWORD dwCharacterID;
    DWORD dwEnterWorldTime;
    DWORD dwAccountId;
    char  nSwitchStageType;
};

struct MsgAckCreateChar:public Msg
{
    MsgAckCreateChar()
    {
        header.dwType = MSG_ACKCREATECHAR;
        header.stLength = sizeof( MsgAckCreateChar );
    }
    bool   bCreateSucc;
	int16  stWhichSlot;
};
struct MsgAckCreateCheckName : public Msg
{
    MsgAckCreateCheckName()
    {
        header.dwType = MSG_ACK_CREATECHECKNAME;
        header.stLength = sizeof( MsgAckCreateCheckName );
    }
    bool bResult;
};
struct MsgDeleteChar:public Msg
{
    MsgDeleteChar()
    {
        header.dwType = MSG_DELETECHAR;
        header.stLength = sizeof( MsgDeleteChar );
    }
    short stWhichSlot;
};

struct MsgAckDeleteChar:public Msg
{
    enum
    {
        eYouAreGuildMaster = 1<<16,    // ����᳤������ѡ�˽���ɾ��
    };
    MsgAckDeleteChar()
    {
        header.dwType = MSG_ACKDELETECHAR;
        header.stLength = sizeof( MsgAckDeleteChar );
        dwReason    = 0;
        dwDelTimes  = 0;
    }
    DWORD   dwReason;
    bool    bDeleteSucc;
    uint32  dwDelTimes;     // ʣ��ʱ��(��λ��)
};

struct MsgGetLag:public Msg
{
    MsgGetLag()
    {
        header.dwType = MSG_GETLAG;
        header.stLength = sizeof( MsgGetLag );
    }
};

//
struct MsgReqRelive:public Msg
{
    MsgReqRelive()
    {
        header.dwType = MSG_REQRELIVE;
        header.stLength = sizeof( MsgReqRelive );
		byAddtion = 0;
    }
	enum EReliveWay
	{
		ENoAddtion  = 0,
		EFreeRelive = 1,
		EFullHPMP   = 1<<1,
		EAddBuff1	= 1<<2,
		EAddBuff2	= 1<<3
	};
	BYTE byAddtion;		//�Ƿ񻨷ѽ�Ǯ���Ӹ�buf���������������������ʱ
    BYTE byBornPos;
};

//���������Ұ
struct MsgItemEnterMySight : public Msg
{
    MsgItemEnterMySight()
    {
        header.dwType = MSG_ITEMENTERMYSIGHT;
        header.stLength = sizeof( MsgItemEnterMySight ) - sizeof(dwPickPlayerID);

        //
        byClientDisplayDelaySecond = 0;
        nCount = 0;
        memset(&dwPickPlayerID, 0, sizeof(dwPickPlayerID));
		m_bFirstEnterSight = true;
    }
    unsigned int nMapID;
    float fX, fY;
    BYTE byClientDisplayDelaySecond;
    unsigned short ustItemId;           //����id
    unsigned short ustItemCount;

    ////����������Ԥ��
    //int nHoldType;                      // ����, ����, ���� , ���߹���, �Ժ���ܻ��и���
    //int nHoldID;                        // id
    //bool bCheckByHoldID;                // �Ƿ������õ�ID���ж�

    int nCount; 
    uint32 dwPickPlayerID[MaxPackageAccessCount];
	bool m_bFirstEnterSight;
    void AddPackageAccessInfo(uint32 dwID)
    {
        if (nCount >= MaxPackageAccessCount)
        {
            return;
        }

        dwPickPlayerID[nCount++] = dwID;
        header.stLength += sizeof(uint32);
    }
};

//Ч��������Ұ
struct MsgEffectEnterMySight:public Msg
{
    MsgEffectEnterMySight()
    {
        header.dwType = MSG_EFFECTENTERMYSIGHT;
        header.stLength = sizeof( MsgEffectEnterMySight );
    }
    unsigned int nMapID;
    float x,y;    
    unsigned short ustSkillID;    //ʹ�õļ���
    unsigned short ustSkillLevel;    //���ܵĵȼ�
    DWORD dwLastTime;            //������ʱ��
	long  MasterID;          //����id
};

//���������ҵ���Ұ
struct MsgBuildingEnterMySight:public Msg
{
    MsgBuildingEnterMySight()
    {
        header.dwType = MSG_BUILDINGENTERMYSIGHT;
        header.stLength = sizeof( *this );
    }
    short x,y;
    char    cDir;
    //����ID
    unsigned short ustBuildingTypeID;
    //��������
    char    cCountry;
    //������� [0,100] 100Ϊ��ɵĽ���
    char    cBuildingPercent;
};

struct MsgPickItem:public Msg
{
    MsgPickItem()
    {
        header.dwType = MSG_PICKITEM;
        header.stLength = sizeof( MsgPickItem );
    };
    //λ��
    short x,y;
    //��Ʒ�Ľ�ɫID
    GameObjectId stItemCharID;
};

struct MsgGetItem:public Msg    // [�ṹû��,MsgGetItem2]
{
    MsgGetItem()
    {
        header.dwType = MSG_GETITEM;
        header.stLength = sizeof( MsgGetItem );
    };
    //SItemBaseInfo item;
    unsigned short ustItemID;
    DWORD dwItemCount;
};

struct MsgGetMoney:public Msg
{
    MsgGetMoney()
    {
        header.dwType = MSG_GETMONEY;
        header.stLength = sizeof( MsgGetMoney );
    };
    DWORD dwMoney;
};

// �������˶���
struct MsgCreateTeam:public Msg
{
    MsgCreateTeam()
    {
        header.dwType = MSG_CREATETEAM;
        header.stLength = sizeof( MsgCreateTeam );

        memset( szTeamName,0,sizeof(szTeamName) );
		AssignMode = 0;
		AssignItemLevel = 0;
    }

    char szTeamName[ dr_MaxPlayerName ];// ��������
	uint8 AssignMode;					// �������ģʽ
	uint8 AssignItemLevel;				// �������ȼ�
};

struct MsgAckCreateTeam:public Msg
{
    enum
    {
        error_alreadyinTeam
        ,error_targetnotinsamestage
        ,error_sys                
    };

    MsgAckCreateTeam()
    {
        header.dwType = MSG_ACKCREATETEAM;
        header.stLength = sizeof( MsgAckCreateTeam );
    };

    short stError;
};

//-----------------------------------------------------------------
//    ������ص���Ϣ
//-----------------------------------------------------------------
//�ͻ��˷�����Ϣ��������,��������ĳ���
struct MsgRequestTeam : public Msg
{
    MsgRequestTeam()
    {
        header.dwType = MSG_REQUESTTEAM;
        header.stLength = sizeof( MsgRequestTeam );
    };
    //char szNewbie[ dr_MaxNameString ];
    DWORD dwNewbieID;                      //��Ҫ��������Ŀ��id ..���������˵�id����head.stID
    char szNewbieName[dr_MaxPlayerName];   //���Զ����� �������� ͨ������
    uint8 AssignMode;
    uint8 AssignItemLevel;                 // �������ȼ�
};

struct MsgAckJoinTeam : public Msg
{
    enum EConstDefine
    {
        error_targetalreadyinTeam          //Ŀ���Ѿ��ڶ����� ���ʧ��
        ,error_cannotfindtarget            //û���ҵ�Ŀ�� Ҳ��Ŀ���Ѿ�����
        ,error_Corpsisfull                 //�Ŷ��Ѿ����� 
        ,error_Teamisfull                  //�����Ѿ�����
        ,error_sys                         //���ʧ��
        ,error_assignmode                  //����ģʽ�Ըģ����ʧ�� 
        ,error_targetcancel                //Ŀ��ܾ�
         ,error_targetrequesting           //Ŀ�����ڱ�������..
        ,error_RequestOnlyHeader
        ,error_succeed
        ,error_people_jointeam             //���߶ӳ� %s �������
        ,succeed_upgrade                   //�����ӳ��ɹ�
        ,error_upgrade                      
        ,error_inPlayerBlacklist           //�ڶԷ���������
        ,error_teamnoexist                 // �����Ѿ�������
        ,error_headerischange              // �ӳ��Ѿ��ı���
        ,error_inMyBlacklsit               // ���Լ���������
        ,error_notsamecountry              // ��ͬ���Ҳ������
		,error_notonline				   // ��������߰�̯
		,success_addTeam				   // �ɹ��������
    };

    MsgAckJoinTeam()
    {
        header.dwType = MSG_ACKJOINTEAM;
        header.stLength = sizeof( MsgAckJoinTeam );
        memset( name, 0, sizeof(name) );
    }

    short stError;
    char  name[dr_MaxPlayerName];          //�����Ա������
};

struct MsgInquireTeamHeader : public Msg   // [�ṹû��]
{
    MsgInquireTeamHeader()
    {
        header.dwType = MSG_INQUIRETEAMHEADER;
        header.stLength = sizeof( MsgInquireTeamHeader );

        memset( szJoinMenName,0, sizeof(szJoinMenName) );
    }
    DWORD dwJoinMenID;
    char  szJoinMenName[dr_MaxPlayerName];
};

struct MsgAckInquireTeamHeader : public Msg     // [�ṹû��]
{
    MsgAckInquireTeamHeader()
    {
        header.dwType = MSG_ACKINQUIRETEAMHEADER;
        header.stLength = sizeof( MsgAckInquireTeamHeader );

        memset( szJoinMenName,0,sizeof(szJoinMenName) );
    }
    bool    bAgree; //�Ƿ�ͬ��
    DWORD   dwJoinMenID;
    char    szJoinMenName[dr_MaxPlayerName];
};

//�����Ա���
struct MsgInquireInvitee : public Msg
{
    MsgInquireInvitee()
    {
        header.dwType = MSG_INQUIREINVITEE;
        header.stLength = sizeof( MsgInquireInvitee );

        memset( szReqName,0,sizeof(szReqName) );
    }
    DWORD dwReqID;                        //������id
    char  szReqName[dr_MaxPlayerName];    //�����ߵ�����
    
    uint8 chProfession;                   // ������ְҵ
    uint16 stLevel;                       // �ȼ�

    uint8 AssignMode;
    uint8 AssignItemLevel;           // �������ȼ�
    bool  IsCorps;
	uint8 nSex;							// �Ա�
};

//�������Ա�Ļش�
struct MsgAckInquireInvitee : public Msg
{
    enum
    {
        result_nonAgree = 0,
        result_agree,
        result_inBlacklist,
		result_notfind,
        error_targetalreadyinTeam,
        error_targetrequesting,
        result_teamisfull,              //����Ķ�������
    };
    MsgAckInquireInvitee()
    {
        header.dwType = MSG_ACKINQUIREINVITEE;
        header.stLength = sizeof( MsgAckInquireInvitee );

        memset( name, 0, sizeof(name) );
    }
    uint8 bAgree;                                
	DWORD dwReqID;                //�������ʱ�Ƕӳ���id, ����������������˵�id
    char  name[dr_MaxPlayerName];    //�������ʱ�Ƕӳ�������,�����������˵�����

    uint8 AssignMode;
    uint8 AssignItemLevel;           // �������ȼ�
};

//c->s ��ʾ�˳�����
//s->c ��ʾ�ͻ��˳�����
struct MsgExitTeam : public Msg
{
    MsgExitTeam()
    {
        header.dwType = MSG_EXITTEAM;
        header.stLength = sizeof( MsgExitTeam );
        bIsDisband = false;
    }
    bool bIsDisband;                // ture = �����ɢ
};

struct MsgChangeManipleFromTeamRet:public Msg
{
    MsgChangeManipleFromTeamRet()
    {
        header.dwType = MSG_CHANGEMANIPLEFROMTEAM;
        header.stLength = sizeof( MsgChangeManipleFromTeamRet );
    }
    BOOL        bSrcess;
    DWORD       dwSrc;
    short       stSrcManiple;
    DWORD       dwDest;
    short       stDestManiple;
};

struct MsgMovePlayerFromManiple:public Msg
{
    MsgMovePlayerFromManiple()
    {
        header.dwType = MSG_MOVEPLAYERFROMMANIPLE;
        header.stLength = sizeof( MsgMovePlayerFromManiple );
    }
    DWORD  dwSrc;
    short  stSrcManiple;
    //GameCharID stDest;
};

struct MsgRetFlagHeaderFromTeam:public Msg
{
    MsgRetFlagHeaderFromTeam()
    {
        header.dwType = MSG_RETFLAGHEADERFROMTEAM;
        header.stLength = sizeof( MsgRetFlagHeaderFromTeam );
    }
    BOOL bSrcess;
    DWORD dwSrcID;
    DWORD dwDestID;
};

struct MsgReqFlagHeaderFromTeam:public Msg
{
    MsgReqFlagHeaderFromTeam()
    {
        header.dwType = MSG_REQFLAGHEADERFROMTEAM;
        header.stLength = sizeof( MsgReqFlagHeaderFromTeam );
    }
    DWORD stFlagCaptain;
    //GameCharID stDest;    
};

struct MsgChangeManipleFromTeam:public Msg
{
    MsgChangeManipleFromTeam()
    {
        header.dwType = MSG_CHANGEMANIPLEFROMTEAM;
        header.stLength = sizeof( MsgChangeManipleFromTeam );
    }
    DWORD dwSrc;
    DWORD dwDest;
};

struct MsgKickFromTeam:public Msg
{
    MsgKickFromTeam()
    {
        header.dwType = MSG_KICKFROMTEAM;
        header.stLength = sizeof( MsgKickFromTeam );
    }
    //char szPlayerName[ dr_MaxNameString ];
    //short stWhichTeamSlot;
    DWORD dwWho;
};

// ��ɢ����
struct MsgDisbandTeam:public Msg
{
	MsgDisbandTeam()
	{
		header.dwType = MSG_DISBANDTEAM;
		header.stLength = sizeof( MsgDisbandTeam );
	}
};

struct MsgTeamOutLine : public Msg
{
    MsgTeamOutLine()
    {
        header.dwType = MSG_TEAMOUTLINE;
        header.stLength = sizeof(MsgTeamOutLine);
    }

    DWORD dwID;
};

struct MsgTeamInfo:public Msg
{
    MsgTeamInfo()
    {
        header.dwType = MSG_TEAMINFO;
        header.stLength = sizeof( MsgTeamInfo );

        memset( szHostName,0,sizeof(szHostName) );
    }
    char szHostName[ dr_MaxPlayerName ];    //�ӳ�������
};

struct MsgAddTeamMember:public Msg
{
    MsgAddTeamMember()
    {
        header.dwType = MSG_ADDTEAMMEMBER;
        header.stLength = sizeof( MsgAddTeamMember );
        memset( szName,0, sizeof(szName) );
        bIsNewAdd = false;
        bOnline = true;
        nFaceId = 0;
        nHairId = 0;
        nHeadPicId = 0;
    }
    DWORD dwMemberID;
    int nHp;
    int nMp;
    int nHpMax;
    int nMpMax;
    short stLvl;
    unsigned char Profession;
    DWORD    dwGroupId;
    short stManiple;
    bool bHeader2;
    bool bHeader;
    //for Team;
    int     nFaceId;    //Ԥ��������Id
	int		nHairId;	//ͷ��Id
    int     nHeadPicId; //ͷ��ͼ��
    short   shSex;
    char szName[ dr_MaxPlayerName ];        //����

    bool bIsNewAdd;                 //�Ƿ��¼���Ķ�Ա
    bool bOnline;                   // �Ƿ�����
};

struct MsgClientTeamInfo : public Msg       // �ͻ������������������Ϣͬ��
{
    MsgClientTeamInfo()
    {
        header.dwType = MSG_CLIENTTEAMINFO;
        header.stLength = sizeof( MsgClientTeamInfo );
        nCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 10,
    };

    int nCount;
    unsigned int dwTeamMemberID[ECD_MaxCount];          // �Լ���ID���÷��͹���
    void AddTeamMemberID( unsigned int dwID )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        dwTeamMemberID[nCount++] = dwID; 
    }
};

struct MsgDeleteTeamMember:public Msg        //����������������˳�����
{
    MsgDeleteTeamMember()
    {
        header.dwType = MSG_DELETETEAMMEMBER;
        header.stLength = sizeof( MsgDeleteTeamMember );
    }
    //short stWhichTeamSlot;        //�Ǹ���Ա��ܵĳ�Ա�˳�
    DWORD dwMemberID;
};

struct MsgTellTeamMemberList : public Msg
{
    MsgTellTeamMemberList()
    {
        header.dwType = MSG_TELLTEAMMEMBERLIST;
        header.stLength = sizeof( MsgTellTeamMemberList ) - sizeof( xMemberInfo );
        nCount = 0;
    }

    struct TeamMemberInfo
    {
        char szName[dr_MaxPlayerName];
        uint32 dwDataBaseID;
        int nHp;
        int nMp;
        int nHpMax;
        int nMpMax;
        short stLevel;
        uint8 chProfession;
        int nFaceId;    //Ԥ��������Id
        int nHairId;
        int nHeadPicId;
        short stSex;
    };

    unsigned int dwTeamHeaderID;        // �ӳ�ID
    int nCount;                         // �м�����Ա
    TeamMemberInfo xMemberInfo[TeamMaxManipleMember];

    void AddTeamMemberInfo( TeamMemberInfo& xMember )
    {
        if ( nCount >= TeamMaxManipleMember )
        { return; }

        xMemberInfo[nCount++] = xMember; 

        header.stLength += sizeof( TeamMemberInfo ); 
    }
};

// �ӳ�����������
struct MsgReqTeamFollow : public Msg
{
	MsgReqTeamFollow()
	{
		header.dwType = MSG_REQTEAMFOLLOW;
		header.stLength = sizeof( MsgReqTeamFollow );
	}
};

// ��Ա�ظ��������
struct MsgAckTeamFollow : public Msg
{
	MsgAckTeamFollow()
	{
		header.dwType = MSG_ACKTEAMFOLLOW;
		header.stLength = sizeof( MsgAckTeamFollow );

		blAccept = true;
	}

	bool	blAccept;
};

struct MsgTeamMemberAck : public Msg
{
	MsgTeamMemberAck()
	{
		SetType( MSG_TEAMMEMBERACK );
		SetLength( sizeof( MsgTeamMemberAck ) );
	}

	enum EnumAckType
	{
		ECD_AgreeFollow = 0,
		ECD_RefuseFollow,
		ECD_CancelFollow,
		ECD_LeaderCancelFollow,
	};
	char  strMemberName[ dr_MaxPlayerName ];
	unsigned int nType;
};


// ֪ͨ�ͻ��˸���Ķ���
struct MsgFollowTeamMember : public Msg
{
	MsgFollowTeamMember()
	{
		header.dwType = MSG_FOLLOWTEAMMEMBER;
		header.stLength = sizeof( MsgFollowTeamMember );

		nMemberID = 0;
	}

	short nMemberID;
};

// �ӳ�ȡ���������
struct MsgHeaderCancelTeamFollow : public Msg
{
	MsgHeaderCancelTeamFollow()
	{
		header.dwType = MSG_HEADERCANCELTEAMFOLLOW;
		header.stLength = sizeof( MsgHeaderCancelTeamFollow );
	}
};

// ȡ���������
struct MsgCancelTeamFollow : public Msg
{
	MsgCancelTeamFollow()
	{
		header.dwType = MSG_CANCELTEAMFOLLOW;
		header.stLength = sizeof( MsgCancelTeamFollow );
	}
};

// ֪ͨ�ӳ��м�����Ա�ڶ������
struct MsgMemberCountInTeamFollow : public Msg
{
	MsgMemberCountInTeamFollow()
	{
		header.dwType = MSG_MEMBERCOUNTINTEAMFOLLOW;
		header.stLength = sizeof( MsgMemberCountInTeamFollow );

		nMemberCountInTeamFollow = 0;
	}

	unsigned char nMemberCountInTeamFollow;
};

//--

struct MsgAckCharInfo : public Msg
{
    MsgAckCharInfo()
    {
        header.dwType = MSG_ACKCHARINFO;
        header.stLength = sizeof( MsgAckCharInfo );

        memset( szDisplayName,0,sizeof(szDisplayName) );
        dwSpecialID      = 0;
    };

    GameObjectId stChar;
    char  szDisplayName[dr_MaxPlayerName];
    DWORD  dwSpecialID;

    int nMp, nMpMax;
    unsigned short stModelID;   // ģ�͵ı��
};


//�л���ͼ
struct MsgFlyToMap:public Msg
{
    MsgFlyToMap()
    {
        header.dwType = MSG_FLYTOMAP;
        header.stLength = sizeof( MsgFlyToMap );
    }
    DWORD dwMapID;
    short x,y;
};

//װ���ı� // [�ṹû��]
struct MsgEquipChanged:public Msg
{
    MsgEquipChanged()
    {
        header.dwType = MSG_EQUIPCHANGED;
        header.stLength = sizeof( MsgEquipChanged );
    }
    SCharVisual visual;
};

struct MsgNPCEnterMySight:public Msg
{ // ĳNPC������Ұ
    MsgNPCEnterMySight()
    {
        header.dwType = MSG_NPC_ENTERMYSIGHT;
        header.stLength = sizeof( MsgNPCEnterMySight );
        Reset();
    }

    void Reset()
    {
        memset( szDisplayName, 0, sizeof(szDisplayName) );
        memset( szTitleName,   0, sizeof(szTitleName)   );
        fZ = 40000.f;
        bShow = true;
        npcId = 0;
		bIsCanRide = false;

		BelongID  = 0;
		ModeID = 0;
    }

    unsigned int  nMapID        ;
    float         fX, fY, fZ    ;
    float         fDirX,fDirY   ;
    BYTE          byDir         ;
    unsigned char ucCountry     ;
    int           stId          ;
    short         stCharType    ;
    GameObjectId  stMasterId    ;
    DWORD         dwShowFlag    ;    
    float         fMoveRate     ;
    float         fMoveStep     ;
    float         fNormalAttackRate;
    short         stDodge       ;
    short         stLuck        ;
    short         stLevel       ;
    short         stMonsterType ;
    uint8         nSubMonsterType;
    BYTE          bySubAction   ;    
    int           nHp           ;
    int           nHpMax        ;    
    short         stPhysicDef   ;
    bool          bMask         ;    
    char          szDisplayName[dr_MaxPlayerName];
	uint8		  influence     ;
    bool          bShow         ;   // �Ƿ�����ʾ״̬
    char          szTitleName  [dr_MaxPlayerName];
    int           npcId         ;
    uint8         nTypeStatus   ;   // ���������״̬
	bool		  bIsCanRide    ;   // �Ƿ�����
	uint32		  BelongID		;
	uint32		  ModeID		;   // ��ǰ��ģ��ID �������ȼ� 0��ʱ�򲻶�ȡ
};

////ĳNPC������Ұ  ����ĳ�������ƶ���
//struct MsgNPCEnterMySightMovingAStep:public MsgNPCEnterMySight
//{
//    MsgNPCEnterMySightMovingAStep()
//    {
//        header.dwType = MSG_NPC_ENTERMYSIGHTMOVINGASTEP;
//        header.stLength = sizeof( MsgNPCEnterMySightMovingAStep );
//    }    
//};

////�ı������ƶ�ģʽ
//struct MsgChangeMonsterMoveType:public Msg
//{
//    MsgChangeMonsterMoveType()
//    {
//        header.dwType = MSG_CHANGEMONSTERMOVETYPE;
//        header.stLength = sizeof( MsgChangeMonsterMoveType );
//    }
//    //GameCharID    stMonsterID;
//    bool bIdleMove;
//    float fNormalMoveRate;
//    //short stMonsterType;
//};

//ĳ��ɫ������Ұ
struct MsgPlayerEnterMySight : public Msg
{
    MsgPlayerEnterMySight()
    {
        header.dwType   = MSG_PLAYER_ENTERMYSIGHT;
        header.stLength = sizeof( MsgPlayerEnterMySight );

        stX=0; stY=0;
        byDir=0;
        fX=0;fY=0;fZ=WORLD_HEIGHT;
        stModelID=0;
        stCharType=0;
        bigShipId=InvalidGameObjectId;
        dwGuildId=0;
		nGuildPosition = 0;
		nFamilyID = 0;
        dwPlayerCharacterID=0;
        fMoveRate=0.0f;
        fNormalAttackRate=0.0f;
        stAction=0;
        shDromeId=0;
		nMountLevel=0;
        nDromePos=0;
        nDriverId=InvalidGameObjectId;
        bySubAction=0;
        nActionPlayTime=0;
        nHp=0; nHpMax=0;
        nMp=0; nMpMax=0;
        fight_status = 0;
        sex=0;
        profession=0;
        stLevel=0;
        ucCharStatus=0;
        nCurrentTitleID=0;
        memset( szTitleTargetName, 0, sizeof( szTitleTargetName ) );
        teamId          = 0;
        teamPosition    = ETP_None;
        nPKValue        = 0;
        nPKMode         = PKMode_Normal;
        nMapID=0;
        influence       = enumBattleInfluence_Max;
        uchCountryID    = 0;
        uchCountryTitle = 0;

        memset( stVisualItemID, 0 , sizeof(stVisualItemID) );
        memset( equipIntensifyTime, 0 , sizeof(equipIntensifyTime) );
        memset( equipLevel, 0 , sizeof(equipLevel) );
        memset( equipElements, 0 , sizeof(equipElements) );
        hairId=0;
        faceId=0;
        headPicId=0;
        talismanId=0;
        showFlag=0;
        fModelPercent=0;
        npcShipPos   = 0;
        bIsFlyMoving = false;
        memset( szSignature, 0, sizeof( szSignature ) );
		hero_id = INVALID_HERO_ID;
		//isBiaocheState = false;
		shRankTitleId = -1;
    }

    //��ɫ��һЩ����״̬����:
    //���������µ�
    enum ECharStatus
    {   
        charstatus_normal_drawin, // ��ͨ�յ�״̬
        charstatus_normal_draw  , // ��ͨ�ε�״̬
        charstatus_sitdown      , // ����
        charstatus_death        , // ����
    };

    int16      stX,stY;
    uint8      byDir;
    float      fX,fY,fZ;
    float      fDirX,fDirY;
    int16      stModelID;
    int16      stCharType;
    uint16     bigShipId;
    uint32     dwGuildId;
	uint8	   nGuildPosition;
	uint32	   nFamilyID;
	int8       familyPosition;		// �ڼ����е�λ��
    uint32     dwPlayerCharacterID; // ��ҵ���Ϸ��ɫID
    float      fMoveRate;
    float      fNormalAttackRate;
    int16      shDromeId;
	uint16	   nMountLevel;
    uint8      nDromePos;
    uint16     nDriverId;
    int16      stAction;
    uint8      bySubAction;
    uint32     nActionPlayTime;     // �������Ž���ʱ��
    int32      nHp, nHpMax;
    int32      nMp, nMpMax;
    uint8      fight_status;        // ս��ģʽ
    uint8      sex;                 // �Ա�
    uint8      profession;          // ְҵ
    int16      stLevel;             // �ȼ�
    uint8      ucCharStatus;
    uint16     nCurrentTitleID;                     // ��ǰ�ĳƺ�
    int8       szTitleTargetName[dr_MaxPlayerName]; // ��ϵ�ƺŸ���������
    uint32     teamId;                              // ����Id
    int8       teamPosition;                        // ����ְλ
    uint8      nPKMode;                             // ��ҵ�ģʽ
    int32      nPKValue;                            // ��ҵ�PKֵ
    uint32     nMapID;                              // ��ҵĵ�ͼID
    uint8      influence;                           // ��Ӫ
    uint8      uchCountryID;                        // ����
    uint8      uchCountryTitle;                     // ���ҳƺ�
               
    // VisualInfo
    uint16     stVisualItemID    [ EEquipPartType_MaxEquitPart ];
    uint8      equipIntensifyTime[ EEquipPartType_MaxEquitPart ];
    uint8      equipLevel        [ EEquipPartType_MaxEquitPart ];
    uint8      equipElements     [ EEquipPartType_MaxEquitPart ];
    uint16     hairId;              // ͷ��ģ��Id
    uint16     faceId;              // ����ģ��Id
	uint8	   defaultModelIndex;   // ����ģ������
    uint16     headPicId;           // ͷ��ͼ��Id
    uint16     talismanId;          // ����ID
    uint8      showFlag;            // EShowFlagType
    float      fModelPercent;       // ģ�ͱ���
    uint8      npcShipPos;          // �ڴ������ϵ�λ��
    bool       bIsFlyMoving ;       // �Ƿ����
    char       szSignature      [RelationDefine::MaxSignLength];    // ����ǩ��
	uint16     hero_id;				//��������ID
	//bool       isBiaocheState;		//�Ƿ��Ǳ����ڳ�״̬
	short	   shRankTitleId;		//����Id
};

struct MsgTellTeamInfo : public Msg
{
    MsgTellTeamInfo()
    {   
        header.dwType = MSG_TELLTEAMINFO;
        header.stLength = sizeof( MsgTellTeamInfo );
    }
    GameObjectId	 charId;
    uint32			 teamId;
    char       teamPosition;
};

////ĳNPC������Ұ  ����ĳ�������ƶ���
//struct MsgPlayerEnterMySightMovingAStep:public MsgPlayerEnterMySight
//{
//    MsgPlayerEnterMySightMovingAStep()
//    {
//        header.dwType = MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP;
//        header.stLength = sizeof( MsgPlayerEnterMySightMovingAStep );
//    }    
//    //BYTE byDir;    
//};

//��ĳ�������ƶ�
struct MsgMoveAStep:public Msg
{
    MsgMoveAStep()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_MOVEASTEP;
        header.stLength = sizeof( MsgMoveAStep );
    }
    GameObjectId    sNpcID;
    BYTE			 byDir;
    //short stX,stY;
};

//////////////////////////////////////new MovingProject
// �ƶ������λ�øı����Ϣ
struct MsgPlayerMovingPos:public Msg
{
    MsgPlayerMovingPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOS;
        header.stLength = sizeof(MsgPlayerMovingPos);
    }
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};

// �ͻ�����������˷����ƶ������λ�øı����Ϣ
struct MsgPlayerMovingPosToServer:public Msg
{
    MsgPlayerMovingPosToServer()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOSTOSERVER;
        header.stLength = sizeof(MsgPlayerMovingPosToServer);
        bNeedChangeMap = 0;
    }
    DWORD        dwSendTime;
    // �������ڵ�����
    D3DXVECTOR3 vPos;

    char bNeedChangeMap; // 0 1
};

///////////////////////////////////////////////////
// �ƶ������λ�úͳ���ı����Ϣ
struct MsgPlayerMovingPosAndDir:public Msg
{
    MsgPlayerMovingPosAndDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOSANDDIR;
        header.stLength = sizeof(MsgPlayerMovingPosAndDir);
    }
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};

// �ͻ�����������˷����ƶ������λ�úͳ���ı����Ϣ
struct MsgPlayerMovingPosAndDirToServer:public Msg
{
    MsgPlayerMovingPosAndDirToServer()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOSANDDIRTOSERVER;
        header.stLength = sizeof(MsgPlayerMovingPosAndDirToServer);        
        bNeedChangeMap = 0;

    }
    DWORD        dwSendTime;
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
    char bNeedChangeMap; // 0 1
};

///////////////////////////////////////////////////////////////
// ԭ�ز�����ҵ�λ����Ϣ
struct MsgPlayerPos:public Msg
{
    MsgPlayerPos()
    {
        header.dwType = MSG_PLAYERPOS;
        header.stLength = sizeof(MsgPlayerPos);
    }
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};

// �ͻ�����������˷���ԭ�ز�����ҵ�λ����Ϣ
struct MsgPlayerPosToServer:public Msg
{
    MsgPlayerPosToServer()
    {
        header.dwType = MSG_PLAYERPOSTOSERVER;
        header.stLength = sizeof(MsgPlayerPosToServer);
    }
    DWORD        dwSendTime;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};

//////////////////////////////////////////////////
// ԭ�ز�����ҵĳ�����Ϣ
struct MsgPlayerDir:public Msg
{
    MsgPlayerDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERDIR;
        header.stLength = sizeof(MsgPlayerDir);
    }
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;

    //���ﴫ��λ����Ϣ�Ǹ�Gate�������ж�ת����Ϣ�ķ�Χ��
    D3DXVECTOR3 vPos;
};

// �ͻ�����������˷���ԭ�ز�����ҵĳ�����Ϣ
struct MsgPlayerDirToServer:public Msg
{
    MsgPlayerDirToServer()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERDIRTOSERVER;
        header.stLength = sizeof(MsgPlayerDirToServer);
    }
    DWORD        dwSendTime;
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;

    //���ﴫ��λ����Ϣ�Ǹ�Gate�������ж�ת����Ϣ�ķ�Χ��
    D3DXVECTOR3 vPos;
};

//////////////////////////////////////////////////////////////////////
// ԭ�ز�����ҵ�λ�úͳ�����Ϣ
struct MsgPlayerPosAndDir:public Msg
{
    MsgPlayerPosAndDir()
    {
        header.dwType = MSG_PLAYERPOSANDDIR;
        header.stLength = sizeof(MsgPlayerPosAndDir);
    }
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};

// �ͻ�����������˷���ԭ�ز�����ҵ�λ�úͳ�����Ϣ
struct MsgPlayerPosAndDirToServer:public Msg
{
    MsgPlayerPosAndDirToServer()
    {
        header.dwType = MSG_PLAYERPOSANDDIRTOSERVER;
        header.stLength = sizeof(MsgPlayerPosAndDirToServer);
    }
    DWORD        dwSendTime;
    // ������泯����
    char chDirX;
    char chDirY;
    char chDirZ;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
};


///////////////////////////////////////////////////////////////
// ����ƶ���Ŀ���
struct MsgHitchMoveTargetPos:public Msg
{
    MsgHitchMoveTargetPos()
    {
        header.dwType = MSG_HITCHMOVETARGETPOS;
        header.stLength = sizeof(MsgHitchMoveTargetPos);
    }
    D3DXVECTOR3 vTargetPos;
};

// ����ܷ���Ƶ��ƶ�
struct MsgCanControlMoving:public Msg
{
    MsgCanControlMoving()
    {
        header.dwType = MSG_CANCONTROLMOVING;
        header.stLength = sizeof(MsgCanControlMoving);
    }

    bool bCanControlMoving;
    bool bIsFlyMoving;
};

// ���������ҵ��ƶ���Ϣ
struct MsgPlayerMoving:public Msg
{
    enum
    {
        eNotMoving = 0,                        // �����ƶ�
        eMovingForward,                        // ֱ����ǰ�ƶ�
        eMovingForwardLeft,                    // �����ǰ�ƶ�
        eMovingForwardRight,                // �Ҳ���ǰ�ƶ�
        eMovingLeft,                        // ����ƽ��
        eMovingRight,                        // ����ƽ��
        eMovingCountermarchLeft,            // �������ƶ�
        eMovingCountermarchRight,            // �Ҳ�����ƶ�
        eMovingCountermarch,                // �����ƶ�
        eMovingTypeMax                        // �����ƶ���Ϣ������
    };

    MsgPlayerMoving()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVING;
        header.stLength = sizeof(MsgPlayerMoving);
    }
    // ������泯����
    D3DXVECTOR3 vDir;

    // �������ڵ�����
    D3DXVECTOR3 vPos;

    // �����ƶ��ķ�ʽ
    short shMovingType;
};

// ��������������ƶ���ĳ�����Ϣ
struct MsgMovedToPos:public Msg         // [�ṹû��]
{
    MsgMovedToPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_MOVEDTOPOS;
        header.stLength = sizeof(MsgMovedToPos);
    }
    float    DirX;
    float    DirY;
    float    X;
    float    Y;
};

// ��������״̬
struct MsgTurnIntoHide:public Msg       // [�ṹû��]
{
    MsgTurnIntoHide()
    {
        header.dwType = MSG_TURNINTOHIDE;
        header.stLength = sizeof(MsgTurnIntoHide);
    }
};

// �뿪����״̬
struct MsgAppearFromHide:public Msg         // [�ṹû��]
{
    MsgAppearFromHide()
    {
        header.dwType = MSG_APPEARFROMHIDE;
        header.stLength = sizeof(MsgAppearFromHide);
    }
};

// ���ͼ�����ʾ��Ϣ
struct MsgUseSkillHintMessage:public Msg
{
    enum
    {
        eOutAttackRangeHint = 0            // û���ڹ���������
        ,eUnfaceToTarget                   // û���泯Ŀ��
        ,eNoEnoughHpToUseSkill             // û���㹻��Hp��ʹ�ü���
        ,eNoEnoughMpToUseSkill             // û���㹻��Mp��ʹ�ü���
        ,eNoEnoughItemToUseSkill           // û��Я����Ӧ�ĵ�����ʹ�ü���
        ,eNoEnoughWeaponToUseSkill         // û��װ����Ӧ��������ʹ��
        ,eCannotUsePassivitySkill          // ����ʹ�ñ�������
        ,eCannotUseSkillInCurStatus        // �����ڵ�ǰ״̬��ʹ�ü���
        ,eSkillIsInCoolDown                // ������CoolDown��
        ,eBannedPK                         // ��������ֹPK
        ,eServerCannotFindSkill            // ���������Ҳ�����Ӧ�ļ���
        ,eSkillTargetNotExist              // ���ܵ�Ŀ�겻����
        ,eSkillTargetWrong                 // ����ļ���Ŀ��
        ,eTargetNumIsZero                  // Ŀ��ĸ���Ϊ0
        ,eCannotUseSkillWhenMounting       // �����в���ʹ�ü���
        ,eCannotUseSkillWhenPrivateShop    // �������̵��в���ʹ�ü���
        ,eCannotUseSkillInSkillAvailable   // ��SkillAvailable�ж����ܲ���ʹ��
        ,eCannotUseSkillWhenTaskIsnotEmpty // Task��Ϊ�գ����Բ���ʹ�ü���
        ,eCannotUsePhysicsSkill            // ��ǰ״̬����ʹ��������
        ,eCannotUseMagicSkill              // ��ǰ״̬����ʹ��ħ������
        ,eCancelSkill                      // ȡ����ǰʹ�õļ���
        ,eNormal                           // ����
        ,eNoEnoughFpToUseSkill             // û���㹻��FP��ʹ�ü���
        ,eMustInFightState                 // ���ܱ�����ս��״̬
        ,eMustOutFightState                // ���ܱ��벻��ս��״̬
        ,eHpLimitError                     // Ѫ������
        ,eNoInTargetBack
        ,eNotEnoughVigorToUseSkill         // û���㹻�ľ���ʹ�ü���
        ,eNotEnoughActivityToUseSkill      // û���㹻�Ļ���ʹ�ü���
        ,eHaveCapturePet                   // �Ѿ��в������
        ,eCapturePetFail                   // �������ʧ��
        ,eSkillTargetCountError            // ����Ŀ���������
        ,eFormulaResultNotExist            // ������������
        ,eSuitNoRight
        ,eTeamSkillCanNotUse               // ���鼼�ܲ���ʹ��
        ,eTeamSkillInCoolDown              // ���鼼�ܻ���CD��
        ,ePetMonsterIsFull                 // ���ֻ���ٻ�3ֻ��
        ,eHurtImmunity                     // �˺�����
        ,eHintMax
    };

    MsgUseSkillHintMessage()
    {
        header.dwType = MSG_USESKILLHINTMESSAGE;
        header.stLength = sizeof(MsgUseSkillHintMessage);
        isAction = false;
    }

    short			shHintId;
    GameObjectId    TargetID;
    int				nSkillID;
    short			shSkillLevel;
    bool			isAction;
};

// ���Ϳ���ĳChar��������Ϣ
struct MsgSawSomeoneDead:public Msg
{
    MsgSawSomeoneDead()
    {
        header.dwType   = MSG_SAWSOMEONEDEAD;
        header.stLength = sizeof(MsgSawSomeoneDead);
        bHaveDieAni = true;
		shReliveCnt =0xffff;
    }
    bool bHaveDieAni;
	unsigned short shReliveCnt;
};

struct MsgChangeDrome : public Msg
{ // ����ı����Ϣ
    enum EOpType
    {
        EOT_Active,   // ��ս
        EOT_UnActive, // ��Ϣ
        EOT_Ride,     // ����
        EOT_Discard,  // ����
    };

    MsgChangeDrome()
    {
        header.dwType = MSG_CHANGEDROME;
        header.stLength = sizeof(MsgChangeDrome);
        ucOpType = EOT_Ride;
        guid = 0;
		nMountLevel = 0;
    }

    union
    {
        int nDromeID;
        int nIndex;
    };

    uint8     ucOpType;
    int64     guid    ;
	uint16	  nMountLevel;	//����ȼ�
};

// ���������Ϣ
struct MsgDisDrome:public Msg
{
    MsgDisDrome()
    {
        header.dwType = MSG_DISDROME;
        header.stLength = sizeof(MsgDisDrome);
    }
};

// �´�˳������Ϣ
struct MsgDisHitch:public Msg
{
    MsgDisHitch()
    {
        header.dwType = MSG_DISHITCH;
        header.stLength = sizeof(MsgDisHitch);
    }
};

// ��ҽ�ɫ�Ľ���������Ϣ
struct MsgPlayerVerifyPos:public Msg
{
    MsgPlayerVerifyPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERVERIFYPOS;
        header.stLength = sizeof(MsgPlayerVerifyPos);
    }
    //// ������泯����
    //D3DXVECTOR3 vDir;
    // �������ڵ�����
    D3DXVECTOR3 vPos;
    //// �����ƶ��ķ�ʽ
    //short shMovingType;
};

// ��ҽ�ɫ�ĸı��ƶ���ʽ����Ϣ
struct MsgPlayerChangeMovingType:public Msg     // [�ṹû��]
{
    MsgPlayerChangeMovingType()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGTYPE;
        header.stLength = sizeof(MsgPlayerChangeMovingType);
    }
    BYTE ucMovingType;
};

// ��Ҹı��ƶ�����
struct MsgPlayerChangeMovingDir:public Msg      // [�ṹû��]
{
    MsgPlayerChangeMovingDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGDIR;
        header.stLength = sizeof(MsgPlayerChangeMovingDir);
    }
    D3DXVECTOR3 vDir;
};

// ��Ҹı��ƶ�������ƶ���ʽ
struct MsgPlayerChangeMovingDirAndType:public Msg
{
    MsgPlayerChangeMovingDirAndType()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGDIRANDTYPE;
        header.stLength = sizeof(MsgPlayerChangeMovingDirAndType);
    }
    D3DXVECTOR3 vDir;
    BYTE ucMovingType;
};

// ���ͣ��ĳ��
struct MsgPlayerStopSomeWhere:public Msg            // [�ṹû��]
{
    MsgPlayerStopSomeWhere()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERSTOPSOMEWHERE;
        header.stLength = sizeof(MsgPlayerStopSomeWhere);
    }
    D3DXVECTOR3 vPos;
};

// ��ҳ���һ������ͣ��ĳ��
struct MsgPlayerStopSomeWhereAndDir:public Msg      // [�ṹû��]
{
    MsgPlayerStopSomeWhereAndDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGDIRANDTYPE;
        header.stLength = sizeof(MsgPlayerStopSomeWhereAndDir);
    }
    D3DXVECTOR3 vPos;
    D3DXVECTOR3 vDir;
};

// ����ҽ�ɫ�����������Ϣ(�������ƶ�ʱ�������)
struct MsgUnPlayerVerifyPos:public Msg
{
    MsgUnPlayerVerifyPos()
    {
        //header.uMsgLevel = level_low;
        header.dwType = MSG_UNPLAYERVERIFYPOS;
        header.stLength = sizeof(MsgUnPlayerVerifyPos);
    }
    // ����ҽ�ɫ������
    D3DXVECTOR3 vPos;

    // ����ҽ�ɫ�ĳ���
    //D3DXVECTOR3 vDir;

    // ����ҽ�ɫ�ĳ���
    char chDirX;
    char chDirY;
    char chDirZ;
};

// ������ƶ���ĳ�����Ϣ
struct MsgUnPlayerMovingToPos:public Msg
{
    MsgUnPlayerMovingToPos()
    {
        //header.uMsgLevel = level_low;
        header.dwType = MSG_UNPLAYERMOVINGTOPOS;
        header.stLength = sizeof(MsgUnPlayerMovingToPos);
    }
    D3DXVECTOR3 vStartPos;
    D3DXVECTOR3 vEndPos;
};

//// ����ҽ�ɫ�ƶ�������Ŀ��
//struct MsgUnPlayerMovingToLockTarget:public Msg
//{
//    MsgUnPlayerMovingToLockTarget()
//    {
//        header.dwType = MSG_UNPLAYERMOVINGTOLOCKTARGET;
//        header.stLength = sizeof(MsgUnPlayerMovingToLockTarget);
//    }
//    GameCharID LockTargetID;//Ŀ���ID
//    float fKeepDistance;//��Ŀ�걣�ֵľ���
//};

// ����ҽ�ɫ������Ŀ��
struct MsgUnPlayerClosingToLockTarget:public Msg
{
    MsgUnPlayerClosingToLockTarget()
    {
        //header.uMsgLevel = level_low;
        header.dwType = MSG_UNPLAYERCLOSINGTOLOCKTARGET;
        header.stLength = sizeof(MsgUnPlayerClosingToLockTarget);
    }
    // ����ҽ�ɫ������
    D3DXVECTOR3 vPos;

    //Ŀ���ID
    GameObjectId LockTargetID;
};

//����ҽ�ɫ����Ŀ��
struct MsgUnPlayerLockTarget:public Msg
{
	MsgUnPlayerLockTarget()
	{
		header.dwType = MSG_UNPLAYERLOCKTARGET;
		header.stLength = sizeof(MsgUnPlayerLockTarget);
	}

	//Ŀ���ID
	GameObjectId LockTargetID;
};

//// �����ƶ�״̬���ƶ���ָ����
//struct MsgKeepMovingToPos:public Msg
//{
//    MsgKeepMovingToPos()
//    {
//        header.uMsgLevel = level_low;
//        header.dwType = MSG_KEEPMOVINGTOPOS;
//        header.stLength = sizeof(MsgKeepMovingToPos);
//    }
//    float    DirX;
//    float    DirY;
//    float    X;
//    float    Y;
//};

//// �ƶ���ָ���㲢ͣ����
//struct MsgMovingToPos:public Msg
//{
//    MsgMovingToPos()
//    {
//        header.dwType = MSG_MOVINGTOPOS;
//        header.stLength = sizeof(MsgMovingToPos);
//    }
//    float    DirX;
//    float    DirY;
//    float    X;
//    float    Y;
//};

//������Ծ��Ϣ
struct MsgJump:public Msg
{
    MsgJump()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_JUMP;
        header.stLength = sizeof(MsgJump);
    }
    short shJumpActionId;
};

//���ͳ���������Ϣ
struct MsgPetCommand:public Msg
{
    enum EPetCommandType
    {
        eAttackTarget = 0  //����Ŀ��
        ,eFollowMe         //�����Լ�
        ,eDismiss          //��ɢ
        ,eAttackAI         //��������AI
        ,eDefendAI         //��������AI
        ,eCommandAI        //��������AI
        ,eUseSkill         //ʹ�ü���
        ,eCommandMax
    };

    MsgPetCommand()
    {
        header.dwType   = MSG_PETCOMMAND;
        header.stLength = sizeof(MsgPetCommand);
        shPetCommandIndex = eAttackTarget;
        skillId         = 0;
        skillLevel      = 0;
    }

    short   shPetCommandIndex   ;
    uint16  skillId             ;
    uint8   skillLevel          ;
};

//���Ͱε���Ϣ
struct MsgDrawWeapon:public Msg
{
    MsgDrawWeapon()
    {
        header.dwType = MSG_DRAWWEAPON;
        header.stLength = sizeof(MsgDrawWeapon);
    }
};

//�����յ���Ϣ
struct MsgDrawInWeapon:public Msg
{
    MsgDrawInWeapon()
    {
        header.dwType = MSG_DRAWINWEAPON;
        header.stLength = sizeof(MsgDrawInWeapon);
    }
};

//���͸ı䷽�����Ϣ
struct MsgChangingDir:public Msg
{
    MsgChangingDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_CHANGINGDIR;
        header.stLength = sizeof(MsgChangingDir);
    }
    float    DirX;
    float    DirY;
};

//struct MsgMoveToPos:public Msg
//{
//    MsgMoveToPos()
//    {
//        header.dwType = MSG_MOVETOPOS;
//        header.stLength = sizeof( MsgMoveToPos );
//    }
//    GameCharID    sNpcID;
//    BYTE    byDir;
//    short stX,stY;
//};
struct MsgReqMoveAStep:public Msg
{
    MsgReqMoveAStep()
    {
        header.dwType = MSG_REQMOVEASTEP;
        header.stLength = sizeof( MsgReqMoveAStep );
        dwReason = eREASON_NOFLAG;
    }
    BYTE byDir;
    char cMoveSerial;
    DWORD dwReason;
    float X;
    float Y;
};

struct MsgPermitMove:public Msg
{
    MsgPermitMove()
    {
        header.dwType = MSG_PERMITMOVE;
        header.stLength = sizeof( MsgPermitMove );

        dwReason = eREASON_NOFLAG;
        cMoveSerial = 0;
    }
    DWORD dwReason;
    char cMoveSerial;
};

struct MsgVerifyPos:public Msg
{
    MsgVerifyPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_VERIFYPOS;
        header.stLength = sizeof( MsgVerifyPos );
        dwReason = eREASON_NOFLAG;
    }
    GameObjectId sNpcID;
    float x,y;
    char cMoveSerial;
    DWORD dwReason;
    
};
//�̶�ʱ�������ͬ����Ϣ
struct MsgSyncPos:public Msg
{
    MsgSyncPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_SYNCPOS;
        header.stLength = sizeof(MsgSyncPos);
    }
    GameObjectId sNpcID;
    short x,y;
};

///////////////////////////////////������Ϣ/////////////////////////////
//������
struct Msg_Building_ReqBuild:public Msg
{
    Msg_Building_ReqBuild()
    {
        header.dwType = MSG_BUILDING_REQBUILD;
        header.stLength = sizeof( *this );
    }
    GameObjectId stBuildingCharID;                        //������ɫID
    unsigned short ustTargetBuildingTypeID;        //������Ŀ�꽨������ID
};

//������ʧ��
struct Msg_Building_BuildFailed:public Msg
{
    enum enumErrCode
    {
        //δ֪����
        err_unknown
        //��������ĳ������
        ,err_musthascountryfirst
        //���ܽ���Ŀ�꽨��        
        ,err_errtarget
        //���Ҳ�ƥ��
        ,err_countrymismatch
        //ûǮ
        ,err_notenoughmoney
        //������޽���
        ,err_alreadybuilding
        //û�г��н������1������ʱ
        ,err_hasnotcitytoken
        //���л�û�н���
        ,err_isnotacitybuilding
    };
    Msg_Building_BuildFailed()
    {
        header.dwType = MSG_BUILDING_BUILDFAILED;
        header.stLength = sizeof( *this );
    }
    char cErrCode;                    //�������
};

//��������
struct Msg_Building_BuildStatus:public Msg
{
    //stID;                            //������ɫID
    Msg_Building_BuildStatus()
    {
        header.dwType = MSG_BUILDING_BUILDSTATUS;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //������Ŀ�꽨������ID
    char cBuildingPercent;            //������ɶ�
};

//����������
struct Msg_Building_Destroyed:public Msg
{
    Msg_Building_Destroyed()
    {
        header.dwType = MSG_BUILDING_DESTROYED;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //�������
};

struct Msg_Building_SelfDestroyed:public Msg
{
    Msg_Building_SelfDestroyed ()
    {
        header.dwType = MSG_BUILDING_SELFDESTROYED;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //�������
};

struct Msg_IntonateStart : public Msg
{ // ��ʼ������
    Msg_IntonateStart()
    {
        header.dwType = MSG_INTONATESTART;
        header.stLength = sizeof( *this );
        usType = 0;
    }
    unsigned short ustSkillID;    
    char           cSkillLevel;
    //������Ŀ���Ƿ��ɫ
    bool bCharTarget;
    union unionTarget
    {
        GameObjectId ustTargetID;
        struct SPos
        {
            short x,y;
        }pos;
    }target;

    unsigned char usType; // ������ 0:�ٵ��� 1:�ൽ��
};

//�������
struct Msg_IntonateEnd:public Msg
{
	struct EmissionTarget
	{
		DWORD dwEmissionFlyTime;
		union unionTarget
		{
			GameObjectId ustTargetID;
			struct SPos
			{
				short x,y;
			}pos;
		}target;
	};

    Msg_IntonateEnd()
    {
        header.dwType = MSG_INTONATEEND;
        header.stLength = sizeof( *this );

		ustSkillID = 0;
		ustSkillLevel = 0;
		nTargetCount = 0;
		memset( targetList, 0, sizeof(targetList ) );
    }

    unsigned short ustSkillID;
    unsigned short ustSkillLevel;
	unsigned short nTargetCount;
	EmissionTarget targetList[ MAXEMISSIONNUM ];
};

//�����ж�
struct Msg_IntonateInterrupt:public Msg
{
    Msg_IntonateInterrupt()
    {
        header.dwType = MSG_INTONATEINTERRUPT;
        header.stLength = sizeof( *this );
        nSkillID = -1;
    }

    int nSkillID;
};

//�����б��������δ�
struct Msg_IntonatingOverTime:public Msg
{
    Msg_IntonatingOverTime()
    {
        header.dwType = MSG_INTONATINGOVERTIME;
        header.stLength = sizeof( *this );
    }
    char cInterruptPercent;
};

struct Msg_ReqCancelSkill:public Msg
{
    Msg_ReqCancelSkill()
    {
        header.dwType = MSG_REQCANCELSKILL;
        header.stLength = sizeof( *this );
    }
};

struct Msg_SkillCanceld  :public Msg
{
    enum enumReason
    {
        //δ֪
        reason_unknown
        //�Ҳ���Ŀ��
        ,reason_invalidtarget
        //����ʹ�øü���
        ,reason_cannotuseskill
        //Ŀ�곬����Χ
        ,reason_targetoutofrange
        //����ļ���
        ,reason_invalidskill
    };

    Msg_SkillCanceld()
    {
        header.dwType = MSG_SKILLCANCELD;
        header.stLength = sizeof( *this );
    }
    short stReason;
};

struct Msg_SkillStatus :public Msg
{
    Msg_SkillStatus()
    {
        header.dwType = MSG_SKILLSTATUS ;
        header.stLength = sizeof( *this );
    }
    enum enumType
    {
        skillstatus_intonate
        ,skillstatus_hold
    };
    //�����Ǹ�״̬
    char            cSkillStatusType;
    //��ǰ�������������̶ȣ�ά��
    char            cPercent;
    unsigned short    ustSkillID;
    char            cSkillLevel;
};

struct Msg_HoldSkillEnd : public Msg
{
    Msg_HoldSkillEnd()
    {
        header.dwType   = MSG_HOLDSKILLEND;
        header.stLength = sizeof( *this );
    }
};

struct Msg_Skill_BeginCoolDown : public Msg
{ // ���ܿ�ʼ��ȴ
    Msg_Skill_BeginCoolDown()
    {
        header.dwType   = MSG_SKILL_BEGINCOLDDOWN;
        header.stLength = sizeof( *this );
    }

    unsigned short ustSkillID;
    unsigned short ustSkillLevel;

    uint32 dwColdTime; // ������ȴʱ��= ������ȴʱ�� - ״̬������ȴʱ�� 
};

struct Msg_Team_PlayerInfo : public Msg
{
    Msg_Team_PlayerInfo()
    {
        header.dwType = MSG_TEAM_PLAYERINFO;
        header.stLength = sizeof( Msg_Team_PlayerInfo );
    }
	DWORD dwDataBaseId;
    int nHp, nHpMax;
    int nMp, nMpMax;    
    short stLvl;
    short stManiple;
    DWORD dwMapID;
    short x,y;
    float fx,fy;
    bool bHeader2;//С�Ӷӳ�
    bool bHeader;
    unsigned char Profession;
	unsigned char    AssignMode; //����ģʽ lrt
};

//MSG_QUERY_CITYSINFO
struct MsgQueryCitysInfo:public Msg     // [�ṹû��]
{
    MsgQueryCitysInfo()
    {
        header.dwType = MSG_QUERY_CITYSINFO;
        header.stLength = sizeof( *this );
    }
};

struct MsgCityInfo:public Msg       // [�ṹû��]
{
    MsgCityInfo()
    {
        header.dwType = MSG_CITYINFO;
        header.stLength = sizeof( *this );
    }
    //����ID
    short stCityID;
    //�г�����
    char  szCityNO1[ dr_MaxNameString ];
    //��������
    char  cCountry;
};

struct MsgPlayerNameChanged:public Msg
{
    MsgPlayerNameChanged()
    {
        header.dwType = MSG_PLAYERNAME_CHANGED;
        header.stLength = sizeof( *this );
    }
    char szPlayerName[ dr_MaxPlayerName ];
};

struct MsgAbandonTask : public Msg 
{
    MsgAbandonTask()
    {
        header.dwType = MSG_ABANDON_TASK;
        header.stLength = sizeof(*this);
    }
    short stTaskId;
};

struct MsgQueryScriptVar : public Msg
{
    enum
    {
        STRING_LEGTH = 32
    };
    MsgQueryScriptVar()
    {
        header.dwType = MSG_QUERY_SCRIPTVAR;
        header.stLength = sizeof(*this);
    }
    char szVar[STRING_LEGTH];
};

struct MsgShowText : public Msg 
{
    enum
    {
        STRING_LEGTH = 256
    };
    enum
    {
        eAlignLeftTop = 0
        ,eAlignTop
        ,eAlignRightTop
        ,eAlignLeft
        ,eAlignMiddle
        ,eAlignRight
        ,eAlignLeftBottom
        ,eAlignBottom
        ,eAlignRightBottom

        ,eAlignMax
    };

    MsgShowText()
    {
        header.dwType = MSG_SHOWTEXT;
        header.stLength = sizeof(*this);
    }
    bool    bTile;
    //DWORD    dwTime; //��Ϊ�ڱ������ã��˴�ɾ��
    int     nShowInfoType;
    BYTE    byAlign;
    char szText[STRING_LEGTH];
};

struct MsgUpdateQuestVar : public Msg   // ���������������
{
    MsgUpdateQuestVar()
    {
        header.dwType = MSG_UPDATEQUESTVAR;
        header.stLength = sizeof(*this);
    }
    unsigned int ustQuestId;
    unsigned int ustMonsterId;
    int nVar;
    int nMaxVar;
};

struct MsgUpdateBank : public Msg       // [�ṹû��]
{
    MsgUpdateBank()
    {
        header.dwType = MSG_UPDATEBANK;
        header.stLength = sizeof(*this);
    }
    DWORD dwCurMoney;    // ���е�ǰ���
    DWORD dwMaxMoney;    // �������
    DWORD dwUpgrade;    // ��������Ҫ��Ǯ,��Ϊ0��������߼�
    DWORD dwPlayerMoney;// ������ϵ�Ǯ
};

struct MsgReqBankTrade : public Msg
{
    enum EOperate
    {
        ePushMoney = 0    // ��Ǯ
        ,ePopMoney        // ȡǮ
        ,eUpgradeBank    // ��������
    };
    MsgReqBankTrade()
    {
        header.dwType = MSG_REQ_BANKTRADE;
        header.stLength = sizeof(*this);
    }
    BYTE    byOperate;
    DWORD    dwMoney;
};

struct MsgAckBankTrade : public Msg     // [�ṹû��]
{
    MsgAckBankTrade()
    {
        header.dwType = MSG_ACK_BANKTRADE;
        header.stLength = sizeof(*this);
    }
    BYTE    byResult;    // EBankTradeResult
};
/*
@added by ^^ at 29/06/2006
DSC:����ֿ����Ϣ�ṹ
*/
struct MsgUpdateStorage : public Msg
{
    MsgUpdateStorage()
    {
        header.dwType = MSG_UPDATESTORAGE;
        header.stLength = sizeof(*this);
    }
    GameObjectId nNpcId;
    SCharStorageData stStorage;
};

struct MsgMoveStorageItem : public Msg
{
    enum E_MoveType
    {
        Type_StorageToPack = 0
        ,Type_PackToStorage
        ,Type_StorageToStorage
    };
    MsgMoveStorageItem()
    {
        header.dwType = MSG_MOVE_STORAGE_ITEM;
        header.stLength = sizeof(*this);
    }
    E_MoveType    enMoveType;
    GameObjectId   nNpcID;
    unsigned short ustDstIndex;
    unsigned short ustSrcIndex;
    unsigned short ustCount;
    DWORD    dwMoney;
    unsigned char ucItemBagType;
    __int64 nGuid;          // Ҫ�ƶ�����Ʒ��GUID
};

// �����Ӳֿ����ó���Ʒ ͬ��GUID
struct MsgMoveStorageItemAck : public Msg
{
    MsgMoveStorageItemAck()
    {
        header.dwType = MSG_MOVE_STORAGE_ITEMACK;
        header.stLength = sizeof(*this);
    }

    unsigned char ucItemBagType;
    unsigned short ustItemIndex;
    unsigned short ustItemID;
    __int64 nGuid;
};

struct MsgAckStorageMoveItem : public Msg       // [�ṹû��]
{
    MsgAckStorageMoveItem()
    {
        header.dwType   = MSG_ACK_MOVE_STORAGE_ITEM;
        header.stLength = sizeof(*this);
    }
    BYTE    byResult;    // StorageTradeResult
};

//�ֿ��Ǯ����ȡǮ
struct MsgStorageMoneyReq : public Msg
{
    MsgStorageMoneyReq()
    {
        header.dwType = MSG_STORAGEMONEYREQ;
        header.stLength = sizeof(*this);
    }

    enum Operation
    {
        Save = 0,                 // ��Ǯ
        TakeOut,                  // ȡǮ
    };
    
    GameObjectId nNpcID;                   // ��Ǯ��npcid (�ж����npc�ľ���, ��ֹ�������,ֱ����Ұ���ǮȡǮ)
    uint8        chOperation;              // ��Ǯ����ȡǮ����
    int          dwMoney;                  // �����Ǯ������
};

//���ش�Ǯ����ȡǮ�������
struct MsgStorageMoneyAck : public Msg
{
    MsgStorageMoneyAck()
    {
        header.dwType = MSG_STORAGEMONEYACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwStorageMoney;              // ��ǰ�ֿ����Ǯ
    uint32 dwPackageMoney;              // ��ǰ�������Ǯ
};

//  ��Ʒ����
struct MsgLockItemReq : public Msg
{
    MsgLockItemReq()
    {
        header.dwType = MSG_LOCK_ITEM;
        header.stLength = sizeof( *this );
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid
};

// �����ɹ��Ż������Ϣ, ���򲻻���Ϣ
struct MsgLockItemAck : public Msg
{
    MsgLockItemAck()
    {
        header.dwType = MSG_LOCK_ITEMACK;
        header.stLength = sizeof( *this );
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid
};

// ��Ʒ���� �������������, �����Ϣֻ������һ������ʱ��
struct MsgUnLockItemReq : public Msg
{
    MsgUnLockItemReq()
    {
        header.dwType = MSG_UNLOCK_ITEM;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid
};

// ��������ɹ��Ż������Ϣ, ���򲻻���Ϣ
struct MsgUnLockItemAck : public Msg
{
    MsgUnLockItemAck()
    {
        header.dwType = MSG_UNLOCK_ITEMACK;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid

    __int64 n64UnLockTime;  // �����Ժ󷵻ؽ����ĵ���ʱ�� ��ֵ�� StorageInfo::n64UnLockTime
    uint32  nUnLockLeftTime;    // ����ʣ��ʱ�� ��ֵ�� StorageInfo::nUnLockLeftTime
};

// ʱ�䵽��, �ͻ��˷�����Ϣ��������, Ҫ�������������
struct MsgCheckUnLockItemReq : public Msg
{
    MsgCheckUnLockItemReq()
    {
        header.dwType = MSG_CHECKUNLOCK_ITEMREQ;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid
};

// �����ɹ��Ż������Ϣ, ���򲻻���Ϣ
struct MsgCheckUnLockItemAck : public Msg
{
    MsgCheckUnLockItemAck()
    {
        header.dwType = MSG_CHECKUNLOCK_ITEMACK;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // �������� ( ���������� ,Ҳ�����ǲֿⱳ�� )
    uint16 ustItemIndex;     // ��������
    __int64 nGuID;          // guid
};

struct MsgNpcPlayAnim : public Msg
{
    enum
    {
        eActionNameLength = 32
    };

    MsgNpcPlayAnim()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_NPCPLAYANIM;
        header.stLength = sizeof(*this);
    }
    GameObjectId     nNpcId;
    char szActionName[eActionNameLength];
    char szEndActionName[eActionNameLength];
    int  nLoopTimes;
};

struct MsgScriptCancel : public Msg 
{
    MsgScriptCancel()
    {
        header.dwType = MSG_SCRIPTCANCEL;
        header.stLength = sizeof(*this);
    }
};

struct MsgOpenUI : public Msg
{
    MsgOpenUI()
    {
        header.dwType = MSG_OPEN_UI;
        header.stLength = sizeof(*this);
    }

    int    UIFlag   ;
    int    openType ;
    int    openParam;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
struct MsgChangEquipHp:public Msg
{   
    MsgChangEquipHp()
    {
        header.dwType = MSG_CHANGEQUIPHP;
        header.stLength = sizeof(*this);
    }
    short stIndex;
    __int64 nGuid;
    float nEquipHp;
    float nEquipMaxHp;
};

struct MsgOpenBagStorage:public Msg
{   
    MsgOpenBagStorage()
    {
        header.dwType = MSG_OPENBAGSTORAGE;
        header.stLength = sizeof(MsgOpenBagStorage);
    }
};

struct MsgRepairItem : public Msg
{
    enum RepairType
    {
        RT_Pack,
        RT_Equip,
        RT_All
    };

    MsgRepairItem()
    {
        header.dwType   = MSG_REPAIRITEM;
        header.stLength = sizeof(*this);
        eType           = RT_Pack;
        stIndex         = 0;
        bIsCostRmb      = false;
    }
    RepairType eType;
    short      stIndex;
    __int64    nGuid;
    bool       bIsCostRmb;
};

struct MsgRepairItemAck:public Msg
{
    enum
    {
        error_noMoney,
        success,
    };
    MsgRepairItemAck()
    {
        header.dwType = MSG_REPAIRITEMSERVERTOCLIENT;
        header.stLength = sizeof(*this);
        eType = MsgRepairItem::RT_Pack;
        stIndex = 0;
        nHp = 0.0f;
        result = error_noMoney;
    }
    MsgRepairItem::RepairType eType;
    short stIndex;
    __int64 nGuid;
    float nHp;
    int result;
    float fMaxHp;   // ���������װ���־�
};

// ��������
struct MsgSpecialRepairItemReq : public Msg
{
    MsgSpecialRepairItemReq()
    {
        header.dwType = MSG_SPECIALREPAIRITEMREQ;
        header.stLength = sizeof( MsgSpecialRepairItemReq );
    }

    short stEquipIndex;
    __int64 nEquipGuid;
};

// ��������
struct MsgSpecialRepairItemAck : public Msg
{
    MsgSpecialRepairItemAck()
    {
        header.dwType = MSG_SPECIALREPAIRITEMACK;
        header.stLength = sizeof( MsgSpecialRepairItemAck );

        chResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,         // �ɹ�
        ECD_NotItem,             // û��ָ�������޵���
        ECD_NotEnoughMoney,      // û���㹻��Ǯ
        ECD_NotEnoughExploit,    // û���㹻�Ĺ�ѫ
        ECD_NotEnoughReputation, // û���㹻������
        ECD_NotEnoughGuildOffer, // û���㹻�İﹱ
    };

    uint8 chResult;     // ���ؽ��

    short stEquipIndex;
    __int64 nEquipGuid;

    float fEquipHp;         // �������Ժ�װ���־�
    uint32 nLeftMoney;      // ʣ�����Ǯ
};

//////////////////////////////////////////////////////////////////////////

// λ�øı���Ϣ ����Χ�Ľ�ɫ�ƶ��ճ�һ���������
struct MsgPosChange : public Msg
{
    enum MaxCharacter
    {
        MAX_CHARACTER = 100 //���һ���Ը���50����ɫ��������Ϣ
    };

    MsgPosChange()
    {
        header.dwType = MSG_POSCHANGE;
        header.stLength = 0; //����һ��ʼֻ���ó���Ϊ0
        nCharNum = 0;
        nIsCompress = 0;
    }
    unsigned char nIsCompress;              // ���Ƿ�ѹ��
    unsigned char nCharNum;                 // �����������ƶ���Ϣ�Ľ�ɫ����
    unsigned char szBuff[MAX_CHARACTER*40]; // ������������buffer��Ϊÿ����ɫԤ��30���ֽڴ洢ID�����ͣ�λ�ã��Լ�����֮�����Ϣ
};

struct MsgEnterMySightPack : public Msg
{
    enum MaxCharacter
    {
        MAX_CHARACTER = 40 //���һ���Է���40��������Ұ��Ϣ
    };

    MsgEnterMySightPack()
    {
        header.dwType = MSG_ENTERMYSIGHTPACK;
        header.stLength = 0;
    }

    unsigned char nIsCompress;                  //���Ƿ�ѹ��
    unsigned char nCharNum;                     //����������EnterMySight�Ľ�ɫ����
    unsigned char szBuff[MAX_CHARACTER*sizeof(MsgPlayerEnterMySight)];     //������������buffer�������ѹ���Ļ������Ĵ�С
};

struct  MsgCallIntensify:public Msg
{
    MsgCallIntensify()
    {
        header.dwType = MSG_CALLINTENSIFYUI;
        header.stLength = sizeof(*this);
    }
};

struct  MsgCallReduce:public Msg
{
    MsgCallReduce()
    {
        header.dwType = MSG_CALLREDUCEUI;
        header.stLength = sizeof(*this);
    }
};

struct MsgPeekEquip : public Msg
{
    MsgPeekEquip()
    {
        header.dwType = MSG_PEEKOTHEREUIP;
        header.stLength = sizeof(MsgPeekEquip);
        playerId    = 0;
        hairId      = 0;     
        faceId      = 0;      
        showFlag    = 0;    
        fModelPercent = 0;
        memset( playerequipitem, 0, sizeof(playerequipitem));
    }

    GameObjectId    playerId;
    uint16			 hairId;           // ͷ��ģ��Id
    uint16			 faceId;           // ����ģ��Id    
    uint8			 showFlag;         // EShowFlagType
    float		     fModelPercent;    // ģ�����Űٷֱ�
    SCharItem		 playerequipitem[EEquipPartType_MaxEquitPart];

    // ������Ϣ����
    PersonalInfo xPersonalInfo;
};

struct MsgWantPeek : public Msg
{
    enum EPeekType
    {
        EPT_Char,
        EPT_Mount,
    };

    MsgWantPeek()
    {
        header.dwType = MSG_WANTPEEK;
        header.stLength = sizeof(*this);
        type = EPT_Char;
    }
    GameObjectId          stTargetID;
    unsigned short type;
};

//---����-------------------------------------------------------------
struct MsgReqDuel : public Msg
{
    MsgReqDuel()
    {
        header.dwType = MSG_REQ_DUEL;
        header.stLength = sizeof(*this);
        shTargetID = -1;
    }
    GameObjectId shTargetID;
};

struct MsgAckDuel : public Msg
{
    enum
    {
        ResultAgree,
        ResultRefuse,
        ResultInBlackList    //�Է��Ѿ�����Ϊ��������
    };
    MsgAckDuel()
    {
        header.dwType = MSG_ACK_DUEL;
        header.stLength = sizeof(*this);
    }
    GameObjectId shDuelID;
    short		  shResult;
};

struct MsgDuelStart : public Msg
{
    MsgDuelStart()
    {
        header.dwType = MSG_DUEL_START;
        header.stLength = sizeof(*this);
        shTargetID = -1;
    }
    GameObjectId shTargetID;
    D3DXVECTOR3	  vFlagPos;
};

struct MsgDuelReady : public Msg
{
    MsgDuelReady()
    {
        header.dwType = MSG_DUEL_START;
        header.stLength = sizeof(*this);
    }
};

struct MsgDuelEnd : public Msg
{
    MsgDuelEnd()
    {
        header.dwType = MSG_DUEL_END;
        header.stLength = sizeof(*this);
        shWinCharID = -1;
        shLostCharID = -1;
    }
    GameObjectId shWinCharID;
    GameObjectId shLostCharID;
};

struct MsgDuelStop : public Msg
{
    MsgDuelStop()
    {
        header.dwType = MSG_DUEL_STOP;
        header.stLength = sizeof(*this);
        shStopCharID = -1;
    }
    GameObjectId shStopCharID;
};

struct MsgReqAssginTeam : public Msg
{
    MsgReqAssginTeam()
    {
        header.dwType = MSG_REQ_ASSIGN_TEAM;
        header.stLength = sizeof( *this );
    }
    int itemid;
    int npcid;
};

struct MsgAckAssginTeam : public Msg
{
    enum
    {
        AN_MAAT_NONE = 0,
        AN_MAAT_chooseComeDown,    //��ȡ 
        AN_MAAT_chooseGiveUp,    //����
    };
    MsgAckAssginTeam()
    {
        header.dwType = MSG_ACK_ASSIGN_TEAM;
        header.stLength = sizeof( *this );
    }
    int itemid;
    int npcid;
    int choose;        //��ȡ ���� ����
};

//���͸��¼���Ķ�Ա��ǰ����ķ���ģʽ
struct MsgTellTeamAssignInfo : public Msg
{
    MsgTellTeamAssignInfo()
    {
        header.dwType = MSG_TELLTEAMASSIGNINFO;
        header.stLength = sizeof( *this );
    }
    uint8 chAssignMode;
    uint8 chAssignItemLevel;
};

//�ͻ�������ı���������Ʒ�ȼ�
struct MsgChangeAssignItemLevelReq : public Msg
{
    MsgChangeAssignItemLevelReq()
    {
        header.dwType = MSG_TEAMCHANGEASSIGNITEMLEVELREQ;
        header.stLength = sizeof( *this );
    }

    uint8 chAssignItemLevel;
};

//��������Ӧ������Ʒ����ȼ����ͻ���
struct MsgChangeAssignItemLevelAck : public Msg
{
    MsgChangeAssignItemLevelAck()
    {
        header.dwType = MSG_TEAMCHANGEASSIGNITEMLEVELACK;
        header.stLength = sizeof( *this );
    }

    uint8 chAssignItemLevel;
};

struct MsgReqChangeAssignMode : public Msg
{
    MsgReqChangeAssignMode()
    {
        header.dwType = MSG_REQ_CHANGE_ASSIGNMODE;
        header.stLength = sizeof( *this );
    }
    
    unsigned char AssignMode;
};

struct MsgAckChangeAssignMode : public Msg
{
    MsgAckChangeAssignMode()
    {
        header.dwType = MSG_ACK_CHANGE_ASSIGNMODE;
        header.stLength = sizeof( *this );
    }
    unsigned char    AssignMode;
};

//���ڶӳ�ֱ���޸�ģʽ,����Ҫ��Աͬ��,��������Э����ʱ����
struct MsgAckChangeAssignModeAnswer : public Msg
{
    enum
    {
        Result_None = 0,
        ResultAgree,
        ResultRefuse
    };
    MsgAckChangeAssignModeAnswer()
    {
        header.dwType = MSG_ACK_CHANGE_ASSIGNMODE_ANSWER;
        header.stLength = sizeof( *this );
    }

    unsigned char    answer;
};

struct MsgAckChangeAssignModeResult : public Msg        // [�ṹû��]
{
    enum
    {
        Result_succeed,
        Result_failed
    };
    MsgAckChangeAssignModeResult()
    {
        header.dwType = MSG_ACK_CHANGE_ASSIGNMODE_RESULT;
        header.stLength = sizeof( *this );
    }
    unsigned char    result;
    unsigned char    AssignMode;
};

struct MsgReqUpgradeTeam : public Msg
{
    MsgReqUpgradeTeam()
    {
        header.dwType = MSG_REQ_UPGRADE_TEAM;
        header.stLength = sizeof( *this );
    }
    DWORD dwID;
};
struct Msg2CItemAdscription : public Msg
{
    Msg2CItemAdscription()
    {
        header.dwType = MSG_2C_ITEM_ADSCRIPTION;
        header.stLength = sizeof( *this );
    }
    GameObjectId npcid;

    int    adscriptionPlayerId;
    int    adscriptionGroupId;
    bool bAdscription_TeamHeader;
    bool bHold_Groupid;
};

//���߿ͻ��˸ð�����Ȩ�����
struct MsgTellPackageAccess : public Msg
{
    MsgTellPackageAccess()
    {
        header.dwType = MSG_TELLPACKAGEACCESS;
        header.stLength = sizeof( *this ) - sizeof(dwPickPlayerID);

        nCount = 0;
        memset(dwPickPlayerID, 0, sizeof(dwPickPlayerID));
    }
    
    GameObjectId nItemPackageID;                 //������id

    ////����������Ԥ��
    //int nHoldType;                      // ����, ����, ���� , ���߹���, �Ժ���ܻ��и���
    //int nHoldID;                        // id
    //bool bCheckByHoldID;                // �Ƿ������õ�ID���ж�

    int nCount;                         // SPickLevelInfo �ṹ����
    uint32 dwPickPlayerID[MaxPackageAccessCount];

    void AddPackageAccessInfo(uint32 dwID)
    {
        if (nCount >= MaxPackageAccessCount)
        {
            return;
        }

        dwPickPlayerID[nCount++] = dwID;
        header.stLength += sizeof(uint32);
    }
};

// �������Աʰȡ��������Ʒ,�رհ����Ժ�, ����յ� MsgTellPackageAccess ��Ϣ����д򿪰���,�ͷ���Ϣ��������ƷʰȡȨ��
struct MsgPackageItemAccessReq : public Msg 
{
    MsgPackageItemAccessReq()
    {
        header.dwType   = MSG_PACKAGEITEMACCESSREQ;
        header.stLength = sizeof(*this);
    }

    int nItemPackageID;         // ����ID
};

// ��Ӧ������������ƷʰȡȨ��
struct MsgPackageitemAccessAck : public Msg
{
    MsgPackageitemAccessAck()
    {
        header.dwType = MSG_PACKAGEITEMACCESSACK;
        header.stLength = sizeof(*this) - sizeof(xItemInfo);
        nCount = 0;
    }
    
    struct PackageItemInfo
    {
        __int64 nItemID;
        uint8 chPickLevel;         //ʰȡȨ��
    };

    GameObjectId nItemPackageID;
    int nCount;

    PackageItemInfo xItemInfo[MaxPackageItemCount];

    void AddPackageItem(__int64 nItemID, uint8 chPickLevel)
    {
        if (nCount >= MaxPackageItemCount)
        {
            return;
        }

        xItemInfo[nCount].nItemID = nItemID;
        xItemInfo[nCount++].chPickLevel = chPickLevel;
        header.stLength += sizeof(PackageItemInfo);
    }
};


//�ͻ�������鿴����
struct MsgPackageViewReq : public Msg
{
    MsgPackageViewReq()
    {
        header.dwType = MSG_PACKAGEVIEWREQ;
        header.stLength = sizeof( *this );
    }

    GameObjectId nItemPackageID;             //������ID
};

//��������Ӧ�İ����е���Ʒ�б�
struct MsgPackageViewAck : public Msg

{
    MsgPackageViewAck()
    {
        header.dwType = MSG_PACKAGEVIEWACK;
        header.stLength = sizeof( *this ) - sizeof(xPackItem);

        nItemCount = 0;
        bSendViewEnd = false;
    }

    struct PackageItemInfo
    {
        SCharItem xItem;
        uint8 chPickLevel;         //ʰȡȨ��
    };

    GameObjectId nItemPackageID;             // ������ID
    bool bSendViewEnd;              // �����ͻ��˵ı���, ture == ���رղ鿴��������ʱ,��Ҫ����һ��MsgPackageViewEnd�������� (������û�����˲��û�)

    int nItemCount;
    PackageItemInfo xPackItem[MaxPackageItemCount];                          // ��������Ʒ
    
    void AddPackageItem(SCharItem& item, uint8 chPickLevel)
    {
        if (nItemCount >= MaxPackageItemCount)
        {
            return;
        }

        xPackItem[nItemCount].xItem = item;
        xPackItem[nItemCount++].chPickLevel = chPickLevel;
        header.stLength += sizeof(PackageItemInfo);
    }
};

//���ǿͻ��˷�������˵�, ��������û����ƷҪ��ʧ��ʱ��,�ͻ����Զ��ر�,����˾Ͳ����ر���Ϣ��
struct MsgPackageViewEnd : public Msg
{
    MsgPackageViewEnd()
    {
        header.dwType = MSG_PACKAGEVIEWEND;
        header.stLength = sizeof( *this );
    }

    GameObjectId nItemPackageID;
};

//�ڰ���������ʰȡһ����Ʒ
struct MsgPickPackageItemReq : public Msg
{
    MsgPickPackageItemReq()
    {
        header.dwType = MSG_PICKPACKAGEITEMREQ;
        header.stLength = sizeof( *this );

        bAllPick = false;
    }
    
    GameObjectId nItemPackageID;
    __int64 nItemID;
    bool bAllPick;                      // �Ƿ�ȫ��ʰȡ
};

//���͸��ͻ���ʰȡ��ĳ����Ʒ,�����б���ɾ������Ʒ (��Ʒ��ӵ�����������һ����Ϣ)
struct MsgPickPackageItemAck : public Msg
{
    MsgPickPackageItemAck()
    {
        header.dwType = MSG_PICKPACKAGEITEMACK;
        header.stLength = sizeof( *this );

        nResult = Result_Success;
    }

    enum PackageItemAckResult
    {
        Result_Success = 0,         // ʰȡ�ɹ�
        Result_AlreadyPick,         // �Ѿ���ʰȡ
        Result_NoPurview,           // ��Ʒ��������,��Ȩ��ʰȡ
    };

    GameObjectId nItemPackageID;
    __int64 nItemID;
    uint16 nItemCount;              // ʰȡ�˶��ٸ�(�п���û�м���);
    int nResult;
};

// ֪ͨ�����е���Ч��Ա,ĳĳĳ���ʰȡ��ĳ��Ʒ, (ֻ��Ʒ��������Ʒ�Ź㲥)
struct MsgTellPickPackageItem : public Msg
{
    MsgTellPickPackageItem()
    {
        header.dwType = MSG_TELLPICKPACKAGEITEM;
        header.stLength = sizeof(*this);

        memset(szPlayerName, 0, sizeof(szPlayerName));
    }

    char szPlayerName[dr_MaxPlayerName];              // �������
    SCharItem xItem;                                  // ��Ʒ
};

//���������͸��ͻ���,Ҫ��ͻ����涪ɸ����Ϸ
struct MsgPackageItemBoultReq : public Msg
{
    MsgPackageItemBoultReq()
    {
        header.dwType = MSG_PICKPACKAGEITEMBOULTREQ;
        header.stLength = sizeof(*this) - sizeof(xItem);

        nCount = 0;
    }

    GameObjectId nItemPackageID;
    
    int nTimeOut;           // ��ʱʱ�� һ��Ϊ30��
    
    int nCount;
    SCharItem xItem[MaxPackageItemCount];

    void AddPackageItemBoult(SCharItem& item)
    {
        if (nCount >= MaxPackageItemCount)
        {
            return;
        }
        xItem[nCount++] = item;
        header.stLength += sizeof(SCharItem);
    }
};

//�ͻ��˻�Ӧ�Ķ�ɸ����Ϣ
struct MsgPackageItemBoultAck : public Msg
{
    MsgPackageItemBoultAck()
    {
        header.dwType = MSG_PICKPACKAGEITEMBOULTACK;
        header.stLength = sizeof(*this);
        nResult = Boult_Choose;
    }

    enum BoultResult
    {
        Boult_Choose = 0,           // ѡ��
        Boult_Abandon,              // ����
    };

    int nItemPackageID;
    __int64 nItemID;

    int nResult;
};

//ɸ�ӵĵ��� (���ɸ�ӵ�����ͬ���������,˭�ȶ�����,˭�õ���Ʒ)
struct MsgPackageItemBoultNumber : public Msg
{
    MsgPackageItemBoultNumber()
    {
        header.dwType = MSG_PICKPACKAGEITEMBOULTNUMBER;
        header.stLength = sizeof(*this) - sizeof(xPackageItemBoult);

        memset(xPackageItemBoult, 0, sizeof(xPackageItemBoult));
        nCount = 0;
        bRemove = false;
    }

    struct PackageItemBoult
    {
        uint32 dwPlayerID;
        uint16 nBoultNumber;   //  == 0 ˵�����˷���, �ͻ�����ʾӦ��˵��ĳĳĳ��������Ʒ, ��ʱҲ�����
    };

    GameObjectId nItemPackageID;
    __int64 nItemID;                        // ��ǰ�������Ʒ
    int32 dwHoldPlayerID;                   // ��Ʒ������� -1ʱ,˵�������˶�������,������ʰȡ
    bool bRemove;                           // �Ƿ���Ҫ�ڿͻ��˰�����ɾ������Ʒ
    int nCount;
    PackageItemBoult xPackageItemBoult[MaxPackageAccessCount];           //������ҵ�ɸ�ӵ���

    void AddPackageItemBoultNumber(uint32 dwID, uint16 nNumber)
    {
        if (nCount >= MaxPackageAccessCount)
        {
            return;
        }
        xPackageItemBoult[nCount].dwPlayerID     = dwID;
        xPackageItemBoult[nCount++].nBoultNumber = nNumber;

        header.stLength += sizeof(PackageItemBoult);
    }
};

//����Ϣ���ӳ�,��Ҫ����������Ʒ����
struct MsgPackageItemNeedToAssign : public Msg
{
    MsgPackageItemNeedToAssign()
    {
        header.dwType = MSG_PICKPACKAGEITEMNEEDTOASSIGN;
        header.stLength = sizeof(*this) - sizeof(nItemIDArray);

        nCount = 0;
        nPlayerCount = 0;
    }

    GameObjectId nItemPackageID;
    int nPlayerCount;
    uint32 dwPlayerID[MaxPackageAccessCount];
    int nCount;
    __int64 nItemIDArray[MaxPackageItemCount];

    void AddPackageItemAssignToPlayer(uint32 dwID)
    {
        if (nPlayerCount >= MaxPackageAccessCount)
        {
            return;
        }
        dwPlayerID[nPlayerCount++] = dwID;
    }

    void AddPackageItemNeedToAssign(__int64 nItemID)
    {
        if (nCount >=  MaxPackageItemCount)
        {
            return;
        }

        nItemIDArray[nCount++] = nItemID;

        header.stLength += sizeof(__int64);
    }
};

//����Ϣ�������� ��������
struct MsgPackageItemAssignReq : public Msg
{
    MsgPackageItemAssignReq()
    {
        header.dwType = MSG_PICKPACKAGEITEMASSIGNREQ;
        header.stLength = sizeof (*this);
    }

    int nItemPackageID;
    __int64 nItemID;

    uint32 dwPlayerID;              // �����˭(db id)
};

//��������Ӧ���ͻ���������Ա,����ʾ��
struct MsgPackageItemAssignAck : public Msg
{
    MsgPackageItemAssignAck()
    {
        header.dwType = MSG_PICKPACKAGEITEMASSIGNACK;
        header.stLength = sizeof (*this);
        bRemove = false;
        memset(szPlayerName, 0, sizeof(szPlayerName));
        chAssignResult = Result_Success;
    }
    
    enum AssignResult
    {
        Result_Success = 0,     // �ɹ�
        Result_Fail,            // ������,���, ���߲�����Ч��Χ�� ,��ʧ��
    };

    uint8 chAssignResult;
    GameObjectId nItemPackageID;
    uint32 dwPlayerID;                     // �������˭(db id)
    char szPlayerName[dr_MaxPlayerName];   // �������˭(����)
    bool bRemove;                          // �Ƿ���Ҫ�ڿͻ��˰�����ɾ������Ʒ
    SCharItem xItem;

    void SetAssignResult(uint8 chResult)
    {
        chAssignResult = chResult;

        if (chAssignResult == Result_Fail)
        {
            header.stLength = sizeof(*this) - sizeof(SCharItem);
        }
    }
};

//--------------------------------------------------------------------
////////////////////////////////������Ϣend///////////////////////////

struct MsgAddFirstList : public Msg
{
    MsgAddFirstList()
    {
        header.dwType = MSG_ADD_FIRSTLIST;
        header.stLength = sizeof(*this);
    }
    GameObjectId shCharID;
};

struct MsgRemoveFirstList : public Msg
{
    MsgRemoveFirstList()
    {
        header.dwType = MSG_REMOVE_FIRSTLIST;
        header.stLength = sizeof(*this);
    }
    GameObjectId shCharID;
};

struct MsgKillMonster:public Msg
{
    MsgKillMonster()
    {
        header.dwType = MSG_KILLMONSTER;
        header.stLength = sizeof(*this);
    }
    GameObjectId stMonsterID;
    int nExp;
    int nSkillExp;
};

struct MsgPKStateChange : public Msg
{
    MsgPKStateChange()
    {
        header.dwType = MSG_PKSTATE_CHANGE;
        header.stLength = sizeof(*this);
        shCharID = -1;
        nPKMode = PKMode_Normal;
        nPKValue = 0;
    }

    GameObjectId shCharID;
    uint8		  nPKMode;
    int16		  nPKValue;

};

struct MsgCancelDelChar : public Msg
{
    MsgCancelDelChar()
    {
        header.dwType = MSG_CANCELDELCHAR;
        header.stLength = sizeof(*this);
        stWhichSlot = -1;
    }
    short stWhichSlot;
};

struct MsgAckCancelDelChar : public Msg
{
    MsgAckCancelDelChar()
    {
        header.dwType = MSG_ACK_CANCELDELCHAR;
        header.stLength = sizeof(*this);
        stWhichSlot = 0;
    }
    bool bSucc;
    short stWhichSlot;
};

struct MsgChangePKFlag : public Msg
{
    MsgChangePKFlag()
    {
        header.dwType = MSG_CHANGE_PKFLAG;
        header.stLength = sizeof(*this);
    }
    short shFlag;
};

struct MsgAckChangePKFlag : public Msg
{
    MsgAckChangePKFlag()
    {
        header.dwType = MSG_ACK_CHANGE_PKFLAG;
        header.stLength = sizeof(*this);
    }
    short shFlag;
};

struct MsgPlayEffect : public Msg 
{
    enum
    {
        eMaxFileName = 128
    };
    MsgPlayEffect()
    {
        header.dwType = MSG_PLAY_EFFECT;
        header.stLength = sizeof(*this);
    }
    GameObjectId    nPlayerId;
    char			 szFileName[eMaxFileName];
    float fX;
    float fY;
    float fZ;
};

struct MsgShowIntonateBar : public Msg 
{
    MsgShowIntonateBar()
    {
        header.dwType = MSG_SHOW_INTONATE_BAR;
        header.stLength = sizeof(*this);

        nType = IntonateType_UnKnow;
        nID   = 0;
    }

    DWORD  dwTime   ;
    uint8  nType    ;      //��������������
    uint16 nID      ;      //������������ƷID
    int nActionID   ;      //����ID
    int nStringID   ;      //�������м���ʾ����
};

struct MsgAgRelive : public Msg
{
    enum relivetype
    {
        useskill = 0,
        usegoods,
        max
    };

    MsgAgRelive()
    {
        header.dwType = MSG_ISRELIVEYESORNO;
        header.stLength = sizeof(MsgAgRelive);
    }
    
    short			sttype;
    GameObjectId	activeid;   // ʹ�ü���( ������Ʒ )�����
};

struct MsgNotifyMail : public Msg
{
    MsgNotifyMail()
    {
        header.dwType = MSG_NOTIFYMAIL;
        header.stLength = sizeof( MsgNotifyMail );
    }

    int8 fromAddressName[ EM_AddressNameSize ]; // ��ɫ��
};

struct MsgSendMailReq : public Msg
{
    enum EConstDefine
    {
        ECD_ToIndex    = 0, // ��һĿ����targets�����е���ʼ�±�λ��
        ECD_OtherIndex = 1, // ����������targets�����е���ʼ�±�λ��
    };

    MsgSendMailReq()
    {
        header.dwType   = MSG_SENDMAILREQ;
        header.stLength = sizeof(MsgSendMailReq);
        Reset();
    }

    void Reset()
    {
        memset( title,   0, sizeof(title)   );
        memset( targets, 0, sizeof(targets) );
        memset( content, 0, sizeof(content) );
        money     = 0;
        bagType   = 0;
        bagIndex  = ErrorUnsignedShortID;
        itemBigId = 0;
        timeStamp = 0;
		mailType  = 0;
    }

    int8             title  [EM_TileMaxCount];   // ����
    SMail::SAddress  targets[EM_TargetMaxCount]; // �����˵ĵ�ַ
    int8             content[EM_MailContentMax]; // �ʼ�����
    uint32           money;                      // Ǯ        ����
    uint8            bagType;                    // ��������  ����
    uint16           bagIndex;                   // ����λ��  ����
    __int64          itemBigId;                  // ����BigId ����
    uint32           timeStamp;                  // ʱ���
	uint8			 mailType;					 //�ʼ����� Ϊ1�Ļ���ϵͳ�ʼ� 0�Ļ������֮��������ʼ�
};

struct MsgSendMailAck : public Msg
{
    enum EResult
    {
        ER_Success,           // �ɹ�
        ER_SystemException,   // ϵͳ��æ
        ER_TargetNotRelation, // �޹�ϵ����
        ER_TargetNameInvalid, // Ŀ��������Ч
        ER_AddressError,      // Ŀ�겻����
        ER_MoneyNotEnough,    // Ǯ����
        ER_MoneyTooMuch,      // �ʼĵ�Ǯ̫��
        ER_AccessoryInvalid,  // ������Ч
        ER_MailProcessing,    // ���ʼ��ڴ���
        ER_TileInvalid,       // title���Ϸ�
        ER_ContentInvalid,    // Content���Ϸ�
		ER_InProtectLockTime, //�Ʋ�����ʱ��
    };

    MsgSendMailAck()
    {
        header.dwType   = MSG_SENDMAILACK;
        header.stLength = sizeof( MsgSendMailAck );
        result          = ER_Success;
    }
    
    uint32  result;
    uint32  timeStamp;    // ʱ���
    uint32  currentMoney; // ��ǰʱ��
    uint8   bagType;      // ��������  ����
    uint16  bagIndex;     // ����λ��  ����
    __int64 itemBigId;    // ����BigId ����
};

struct MsgOpMailReq : public Msg
{
	MsgOpMailReq():bagType(0)
    {
        header.dwType = MSG_OPMAILREQ;
        header.stLength = sizeof( MsgOpMailReq );
        op = EMO_None;
        mailId = 0;
    }
    uint8  op;
    uint32 mailId;		// �ʼ�Id
    uint8  accessory;   // ��������
	uint8  bagType;		// ��������	
};

struct MsgOpMailAck : public Msg
{
    MsgOpMailAck()
    {
        header.dwType = MSG_OPMAILACK;
        header.stLength = sizeof( MsgOpMailAck ) - sizeof(accessory.content);
        result = ER_Success;
        op     = EMO_None;
        mailId = 0;
        money  = 0;
    }

    void RecalLength()
    { header.stLength = sizeof( MsgOpMailAck );}

    uint32 result;
    uint8  op;
    uint32 mailId; // �ʼ�Id
    uint32 money;
    SMail::SAccessory accessory; // ��������
};

struct MsgMailListAck : public Msg
{
    MsgMailListAck()
    {
        header.dwType = MSG_MAILLIST_ACK;
        header.stLength = sizeof(MsgMailListAck) - sizeof(mails);
        count = 0;
        memset( mails, 0, sizeof(mails));
    }

    bool AddMail( const SMail& mail )
    {
        if ( count >= EM_MailMaxCount )
        { return false; }

        mails[count++] = mail;
        header.stLength = sizeof(MsgMailListAck) - sizeof(SMail) * ( EM_MailMaxCount - count );
        return true;
    }

    bool IsFull()
    {
        if ( count >= EM_MailMaxCount )
        { return true; }
        return false;
    }

    uint8 count;
    SMail mails[EM_MailMaxCount];
};

struct MsgReqGraphicCode : public Msg
{
    enum EConstDefine
    {
        ECD_BisstreamMaxSize = 960,
        ECD_GlyphBufMaxSize  = 48,
    };

    MsgReqGraphicCode()
    {
        header.dwType   = MSG_REQGRAPHICCODE;
        header.stLength = sizeof(MsgReqGraphicCode); // ��ʼ����Ϊ0
        memset( bitsstream, 0, sizeof(bitsstream));
        memset( glyphBuf, 0, sizeof(glyphBuf));
        dwTime          = 0;                         // ���ͻ��˷�ӳ��ʱ��
    }
    
    uint8  bitsstream[ECD_BisstreamMaxSize];
    int8   glyphBuf[ECD_GlyphBufMaxSize];
    uint32 dwTime;
};

struct MsgAckGraphicCode : public Msg
{
    MsgAckGraphicCode()
    {
        header.dwType = MSG_ACKGRAPHICCODE;
        header.stLength = sizeof(*this);
    }

    int index;
};

struct MsgReqNumberCode : public Msg
{
    enum EConstDefine
    {
        ECD_BisstreamMaxSize = 960,
    };

    MsgReqNumberCode()
    {
        header.dwType   = MSG_REQNUMBERCODE;
        header.stLength = sizeof(MsgReqNumberCode); // ��ʼ����Ϊ0
        memset( bitsstream, 0, sizeof(bitsstream));
        dwTime          = 0;                         // ���ͻ��˷�ӳ��ʱ��
    }

    uint8  bitsstream[ECD_BisstreamMaxSize];
    uint32 dwTime;
};

struct MsgAckNumberCode : public Msg
{
    MsgAckNumberCode()
    {
        header.dwType   = MSG_ACKNUMBERCODE;
        header.stLength = sizeof(MsgAckNumberCode);
    }
    int index;
};

struct MsgChangeIntegral:public Msg     // [�ṹû��]
{
    MsgChangeIntegral()
    {
        header.dwType = MSG_CHANGE_INTEGRAL;
        header.stLength = sizeof(*this);
    }
    short stValue;
    short stValueMax;
};

struct MsgReqExit : public Msg      // [�ṹû��]
{
    MsgReqExit()
    {
        header.dwType = MSG_REQEXIT;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckExit : public Msg      // [�ṹû��]
{
    MsgAckExit()
    {
        header.dwType = MSG_ACKEXIT;
        header.stLength = sizeof(*this);
        nWaitExitTime = 0;
    }
    unsigned int nWaitExitTime;         //������֪ͨ�ͻ�����Ҫ�ȴ���ʱ��
};

struct MsgReqCancelExit : public Msg        // [�ṹû��]
{
    MsgReqCancelExit()
    {
        header.dwType = MSG_REQCANCELEXIT;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckCancelExit : public Msg        // [�ṹû��]
{
    MsgAckCancelExit()
    {
        header.dwType = MSG_ACKCANCELEXIT;
        header.stLength = sizeof(*this);
    }
};

struct MsgGWBurthen : public Msg
{
    MsgGWBurthen()
    {
        header.dwType = MSG_GWBURTHEN;
        header.stLength = sizeof(*this);
    }
    unsigned int nCurrOnline;
    unsigned int nMaxOnline;
    unsigned int nGateCount;
};

struct MsgInviteInfo : public Msg
{
    MsgInviteInfo()
    {
        header.dwType = MSG_INVITE_INFO;
        header.stLength = sizeof(*this);
        nSn = 0;
    };

    enum InviteType
    {
        IT_ORGANISETEAM,
        IT_LEAGUE,
        IT_DISADVERSE,
        IT_ADDFRIEND,
        IT_EMBRACE,
    };

    uint32 nInviteId;   // ������id
    char cInviteType; // ��������
    char szMasterName[dr_MaxPlayerName]; // ������
    int  nSn; // ��ʾ��

    union
    {
        char szbuffer[20];
        char szGuildName[33];   // �����˹���
    };
};


struct MsgReferInviteResult : public Msg
{
    MsgReferInviteResult()
    {
        header.dwType = MSG_REFER_INVITE_RESULT;
        header.stLength = sizeof(*this);
    };

    int  nInviteId;
    int  nSn;
    char cResult;
    char cInviteType;     // ��������
    union 
    {
        char szBuffer[4];
        char cAlsoAddInviter; // �Ƿ�Ҳ��������Ϊ����
    };
};

struct MsgShowHelmet : public Msg
{
    MsgShowHelmet()
    {
        header.dwType = MSG_SHOW_HELMET;
        header.stLength = sizeof(MsgShowHelmet);
        showHelmet = 0;
    }

    bool showHelmet;
};

struct MsgShowTimeTop:public Msg
{
    MsgShowTimeTop()
    {
        header.dwType = MSG_SHOWTIMETOP;
        header.stLength = sizeof(*this);
        showtime = 0;
    }
    DWORD showtime;
};

struct MsgShutDownTimeTop : public Msg
{
    MsgShutDownTimeTop()
    {
        header.dwType = MSG_SHUTDOWNTIMETOP;
        header.stLength = sizeof(*this);
    }
};

enum eMaxInfo
{
    MAXCHECKINFO =  120
};

struct MsgThunderLogininfo : public Msg     // ���ṹû�á�
{
    MsgThunderLogininfo()
    {
        header.dwType = MSG_ThunderLoginInfo;
        header.stLength = sizeof(*this);
        dwGameVerSion[0]=1;
        dwGameVerSion[1]=0;
        dwGameVerSion[2]=0;
        dwGameVerSion[3]=1;
    }
    DWORD dwGameVerSion[4];
    char checkinfo[MAXCHECKINFO];
};

//���߿ͻ��ˡ��ʺŵĽ�ɫ���ݶ�ȡ�ɹ�
struct MsgEndAckChar:public Msg
{
    MsgEndAckChar()
    {
        header.dwType = MSG_ENDACKCHAR;
        header.stLength = sizeof(MsgEndAckChar);
    }
};

//���ؽ�ɫ���ݣ�S->C��
struct MsgAckChar:public Msg
{
    MsgAckChar()
    {
        header.dwType = MSG_ACKCHAR;
        header.stLength = sizeof( MsgAckChar );
    }

    //�ڼ�����ɫ
    short           stWhichSlot;
    byte            bIsDel;
    SCharBaseInfo   baseinfo;
    SCharVisual     visual;
    DWORD           dwCharacterID;
    uint32          dwDelTimes;     // ʣ��ʱ��(��λ��)
};

struct MsgCreateHeroChar:public Msg
{
    struct SCreateData
    {
        int8    szCharacterName[ dr_MaxPlayerName ];
        uint8   ucHairColorIndex; // ͷ����ɫ������        
        uint8   ucHairModelIndex; // ͷ��ģ�͵�����        
        uint8   ucModelIndex;     // ����ģ�͵�����
        uint8   ucFaceIndex;      // ��ɫ����
        uint8   ucSex;            // ��ɫ�Ա�
        uint8   ucHeadPic;        // ��ɫ��ͷ��
        uint8   usProfession;     // ��ɫְҵ
        uint8   ucCountry;        // ����
        uint8   byMonth;          // ������
        uint8   byDay  ;          // ������
    };

    MsgCreateHeroChar()
    {
        header.dwType = MSG_CREATECHAR;
        header.stLength = sizeof( MsgCreateHeroChar );
        fModelPercent = 1.0f;
    }

    short       stWhichSlot;
    short       shModelId;
    float       fModelPercent;
    SCreateData create;
};

//Luoz add �ͻ��� �������� ������ ����Ƿ�ͬ����Ϣ
struct MsgReqCreateCheckName : public Msg
{
    MsgReqCreateCheckName()
    {
        header.dwType = MSG_REQ_CREATECHECKNAME;
        header.stLength = sizeof( MsgReqCreateCheckName );
    }
    char szName[ dr_MaxPlayerName ];
};

struct MsgNewChangeNameReq : public Msg
{
    MsgNewChangeNameReq()
    {
        header.dwType = MSG_NEWCHANGENAMEREQ;
        header.stLength = sizeof( MsgNewChangeNameReq );
    }
	int	 PlayerID;
    char szName[ dr_MaxPlayerName ];
};

struct MsgNewChangeNameAck : public Msg
{
    MsgNewChangeNameAck()
    {
        header.dwType = MSG_NEWCHANGENAMEACK;
        header.stLength = sizeof( MsgNewChangeNameAck );
    }
    bool Result;
};


struct MsgAckEnterWorld : public Msg
{
    MsgAckEnterWorld()
    {
        header.dwType   = MSG_ACKENTERWORLD;
        header.stLength = sizeof( MsgAckEnterWorld );
        nIsSwitchGame   = 0;
		dwAccountYuanBaoStates = 0;
		dwAccountYuanBaoTotle = 0;
    }
    unsigned short  nResult; // ��Ҫ��Ϊunsigned long ��ʶ��ͬ�ķ��������
    char            cMoveSerial;
    SCharInfoClient charinfo;
    DWORD           dwCurrentTime;
    DWORD           dwStartTime;
    DWORD           dwPlayerCharacterID;
    DWORD           dwPlayerDBID;
    unsigned int    nGameMapId;    
    char            nIsSwitchGame;
	unsigned int	dwAccountYuanBaoTotle;
	unsigned int    dwAccountYuanBaoStates;
};

//��MsgAckEnterWorld��Ϣ�������
struct MsgAckEnterWorldPack : public Msg
{
    MsgAckEnterWorldPack()
    {
        header.dwType = MSG_ACKENTERWORLDPACK;
        header.stLength = 0;
    }
    unsigned char szBuff[sizeof(MsgAckEnterWorld)];
};

struct MsgAckBackCharaterList:public Msg        // [�ṹû��]
{
    MsgAckBackCharaterList()
    {
        header.dwType = MSG_REQ_BACKCHARATERLIST;
        header.stLength = sizeof(MsgAckBackCharaterList);
    }
    //DBMsgOffline2* MsgOffLine;
    //DWORD dwAccountId;
    //short stWhichSlot;
    /*MsgAckChar MsgCharList[More_iCharPerAccount];*/        
};

struct MsgCharAttrChanged : public Msg
{
    enum EConstDefine
    {
        const_iMaxChangeThisMsg = 500//(MSGMAXSIZE-100-sizeof(Msg))/sizeof( SValueChanged )
    };

    MsgCharAttrChanged()
    {
        header.dwType = MSG_CHARATTRCHANGE;
        iChangeCount = 0;
    }

    void CaluLength()
    {
        header.stLength = (int)(sizeof( MsgCharAttrChanged ) - (const_iMaxChangeThisMsg - iChangeCount)*sizeof(SValueChanged));
    }

    bool AddAttrInt64Change( unsigned short ustWhichAttr,__int64 dwNewValue )
    {
        if( iChangeCount >= const_iMaxChangeThisMsg||iChangeCount < 0 )
            return false;

        pAttrChanged[ iChangeCount ].data.n64Value = dwNewValue;
        pAttrChanged[ iChangeCount ].ustWhichAttr = ustWhichAttr;

        iChangeCount++;
        return true;
    }

    bool AddAttrDWORDChange( unsigned short ustWhichAttr,DWORD dwNewValue )
    {
        if( iChangeCount >= const_iMaxChangeThisMsg||iChangeCount < 0 )
            return false;

        pAttrChanged[ iChangeCount ].data.dwValue = dwNewValue;
        pAttrChanged[ iChangeCount ].ustWhichAttr = ustWhichAttr;

        iChangeCount++;
        return true;
    }

    bool AddAttrIntChange( unsigned short ustWhichAttr,int nNewValue )
    {
        if( iChangeCount >= const_iMaxChangeThisMsg||iChangeCount < 0 )
            return false;

        pAttrChanged[ iChangeCount ].data.nValue  = nNewValue;
        pAttrChanged[ iChangeCount ].ustWhichAttr = ustWhichAttr;

        iChangeCount ++;
        return true;
    }

    bool AddAttrFloatChange( unsigned short ustWhichAttr,float fValue )
    {
        if( iChangeCount >= const_iMaxChangeThisMsg||iChangeCount < 0 )
            return false;

        pAttrChanged[ iChangeCount ].data.fValue  = fValue;
        pAttrChanged[ iChangeCount ].ustWhichAttr = ustWhichAttr;

        iChangeCount ++;
        return true;
    }

    bool AddAttrShortChange( unsigned short ustWhichAttr,short stValue )
    {
        if( iChangeCount >= const_iMaxChangeThisMsg||iChangeCount < 0 )
            return false;

        pAttrChanged[ iChangeCount ].data.stValue = stValue;
        pAttrChanged[ iChangeCount ].ustWhichAttr = ustWhichAttr;

        iChangeCount ++;
        return true;
    }

    int           iChangeCount;
    SValueChanged pAttrChanged[const_iMaxChangeThisMsg]; // ���ֻ�ܷ������
};

struct MsgReqUpAttrLevel:public Msg
{
    MsgReqUpAttrLevel()
    {
        header.dwType = MSG_REQ_UP_ATTR_LEVEL;
        header.stLength = sizeof( MsgReqUpAttrLevel );            
    }
    SAttrUp attrup;
};

struct MsgAckUpAttrLevel:public Msg
{        
    MsgAckUpAttrLevel()
    {
        header.dwType = MSG_ACK_UP_ATTR_LEVEL;
        header.stLength = sizeof( MsgAckUpAttrLevel );
    }
    SAttrUp attrup;
};

/*    struct MsgRefreshLinkedSkills:public Msg
{
MsgRefreshLinkedSkills()
{
header.dwType = MSG_REFRESHLINKEDSKILLS;
header.stLength = sizeof( *this );
}
SCharLinkedSkills linkedskills;
};*/

struct MsgRefreshHotkey:public Msg
{
    MsgRefreshHotkey()
    {
        header.dwType = MSG_REFRESHHOTKEY;
        header.stLength = sizeof( MsgRefreshHotkey );
    }
    SCharHotKeys hotkeys;
    //unsigned short ustHotkeyId[More_iHotkey];
};

struct MsgQueryCompoundNew : public Msg
{
    enum EConstDefine
    {
        ECD_MaxAssistantItemCount = 3, // ����������
    };

    MsgQueryCompoundNew()
    {
        header.dwType = MSG_QUERY_COMPOUND_NEW;
        header.stLength = sizeof( MsgQueryCompoundNew );

        recipeId = 0;
        for ( int i=0; i<ECD_MaxAssistantItemCount; ++i)
        { assistantItemBagIndex[i] = -1;}
    }

    unsigned int recipeId;
    short assistantItemBagIndex[ECD_MaxAssistantItemCount]; // ���������ڲ��ϱ����е�λ��
};

struct MsgAckCompoundNew : public Msg
{ 
    enum EConstDefine
    {
        ECD_MaxAssistantItemCount = 3, // ����������
    };

    enum EResult
    {
        eResultSuccess = 0           // �ɹ�
        ,eResultFaild                // ʧ��
        ,eResultMaterialUnconformity // ԭ�ϲ�����
        ,eResultGemIsMaxLevel        // ��ʯ�ȼ�������߼�
        ,eResultNotEnoughMoney       // û���㹻�Ľ�Ǯ
        ,eResultBagFull              // ��������
        ,eResultNotInvalidProduct    // ���в���û�ж�Ӧ�Ĳ���
        ,eResultNotEnoughEnergy      // û���㹻�ľ���
        ,eResultSystemBusy           // ϵͳ��æ
        ,eResultItemNotExistByIndex  // �ƶ���Index��Ʒ������
        ,eResultItemConfigInvalid    // ��Ʒ��Config������ 
        ,eResultItemTypeError        // ��Ʒ���ʹ��� [�ù�]
        ,eResultRepeatedIndex        // �ظ����±�   [�ù�]
        ,eResultPopItem              // ɾ����Ʒʧ��
        ,eResultFindItemException    // ����Ʒ�쳣
        ,Max
    };

    MsgAckCompoundNew()
    {
        header.dwType = MSG_ACK_COMPOUND_NEW;
        header.stLength = sizeof( MsgAckCompoundNew );
        for ( int i=0; i<ECD_MaxAssistantItemCount; ++i)
        { assistantItemBagIndex[i] = -1;}
    }

    long          stResult;
    unsigned int  recipeId;
    short         assistantItemBagIndex[ECD_MaxAssistantItemCount]; // ���������ڲ��ϱ����е�λ��
    SCharItem     item;

    bool AddConsumeAssistantItemIndex( short index )
    {
        for ( int i=0; i<ECD_MaxAssistantItemCount; ++i)
        { 
            if ( assistantItemBagIndex[i] == -1)
            {
                assistantItemBagIndex[i] = index;
                return true;
            }
        }
        return false;
    }
};

struct MsgReqChangeOwnAttribute : public Msg
{
    MsgReqChangeOwnAttribute()
    {
        header.dwType = MSG_REQ_CHANGE_OWNATTRIBUTE;
        header.stLength = sizeof( MsgReqChangeOwnAttribute );
    }
    
    EOwnAttribute type;
};

// ��Ӧ�л��Զ�����װ
struct MsgAckSwitchSuit : public Msg
{
    MsgAckSwitchSuit()
    {
        header.dwType = MSG_ACK_SWITCHSUIT;
        header.stLength = sizeof( MsgAckSwitchSuit );
        nSuitIndex = 0;
    }

    uint8 nSuitIndex;
};

//׼��һ��const_iMaxMsgSeeDamage��buf��������Ϣ
//����Ϣ֪ͨ�ͻ��������ܵ����˺�
struct MsgSeeDamage : public Msg
{
    enum EMaxDamageNum
    {
        const_iMaxMsgSeeMDamage = 6000,
        const_iMaxResultNum = 2000//(const_iMaxMsgSeeMDamage-100-sizeof(Msg))/sizeof( SAttTargetResult )
    };

    MsgSeeDamage()
    {
        header.dwType = MSG_SEEDAMAGE;
        stResultNum = 0;
    }

    struct TargetResult
    {
        short stStatusID;   // ״̬id
        short stLevel;      // ״̬�ȼ�
        SAttTargetResult xResult;   // ״̬����Ч��
    };

    bool AddResult( TargetResult* pResult )
    {
        if( pResult == NULL|| stResultNum < 0 || stResultNum >= const_iMaxResultNum )
        { return false; }

        memcpy( &results[ stResultNum ], pResult, sizeof(TargetResult) );

        ++stResultNum;
        return true;
    }

    bool AddResult( short stStatusID, short stLevel, GameObjectId stWho, GameObjectId stAttacker, short stTag, short stSrc, char cBalanceType, unsigned char ucStatus,int nTagHp, int nSrcHp,int nTagMp,int nSrcMp)
    {
        if( stResultNum < 0 || stResultNum >= const_iMaxResultNum )
        { return false; }
        
        results[ stResultNum ].stStatusID            = stStatusID;
        results[ stResultNum ].stLevel               = stLevel;
        results[ stResultNum ].xResult.stTargetWho   = stWho;
        results[ stResultNum ].xResult.stAttackerWho = stAttacker;
        results[ stResultNum ].xResult.stTagHpNum    = stTag;
        results[ stResultNum ].xResult.stSrcHpNum    = stSrc;
        results[ stResultNum ].xResult.cBalanceType  = cBalanceType;
        results[ stResultNum ].xResult.nStatusFlag      = ucStatus;
        results[ stResultNum ].xResult.nTagHp        = nTagHp;
        results[ stResultNum ].xResult.nSrcHp        = nSrcHp;
        results[ stResultNum ].xResult.nTagMp        = nTagMp;
        results[ stResultNum ].xResult.nSrcMp        = nSrcMp;
        stResultNum ++;
        return true;
    }
    void CaluLength()
    { header.stLength = sizeof(MsgSeeDamage)  - (const_iMaxResultNum - stResultNum) * sizeof(TargetResult);}

    short            stResultNum;
    TargetResult results[const_iMaxResultNum];
};

//׼��һ��const_iMaxMsgSeeMAttSize��buf��������Ϣ
//һ�����󹥻�ֻ����һ��MsgSeeMAtt
struct MsgSeeAttack3 : public Msg
{
    enum enumMaxDamageNum
    {
        const_iMaxMsgSeeMAttSize = 6000
        ,const_iMaxResultNum = 2000//(const_iMaxMsgSeeMAttSize-100-sizeof(Msg))/sizeof( SAttTargetResult )
    };

    MsgSeeAttack3()
    {
        header.dwType = MSG_SEEATTACK3;
        stResultNum = 0;
    }

    enum eAttackHand
    {
        e_Rhand = HT_RightHand,
        e_Lhand = HT_LeftHand,
        e_max
    };

    bool AddResult( SAttTargetResult* pResult )
    {
        if( pResult == NULL ||stResultNum < 0 || stResultNum >= const_iMaxResultNum )
        { return false; }
        
        memcpy( &results[ stResultNum ], pResult, sizeof(SAttTargetResult) );
        ++stResultNum;
        return true;
    }

    // false: ��Ϣ��
    bool AddResult( GameObjectId stWho, GameObjectId stAttacker, short stTag, short stSrc, char cBalanceType, unsigned char ucStatus,int nTagHp, int nSrcHp)
    {
        if( stResultNum < 0 || stResultNum >= const_iMaxResultNum )
        { return false; }

        results[ stResultNum ].stTargetWho = stWho;
        results[ stResultNum ].stAttackerWho = stAttacker;
        results[ stResultNum ].stTagHpNum = stTag;
        results[ stResultNum ].stSrcHpNum  = stSrc;
        results[ stResultNum ].cBalanceType = cBalanceType;
        results[ stResultNum ].nStatusFlag = ucStatus;
        results[ stResultNum ].nTagHp = nTagHp;
        results[ stResultNum ].nSrcHp = nSrcHp;
        ++stResultNum;
        return true;
    }

    void CaluLength()
    { header.stLength = sizeof( MsgSeeAttack3 ) - ( const_iMaxResultNum - stResultNum )*sizeof( SAttTargetResult );}
    
    short stAttackerX, stAttackerY; // ����������
    unsigned short ustSkillID;      // ����˺��ļ��ܵ�ID
    unsigned short ustSkillLevel;
    DWORD          dwActionTime;    // ʱ����ص�����
    DWORD          dwHoldTime;
    bool           bIsCharTarget;   // �ü����Ƿ��й�����Ŀ��
    union unionData
    {
        GameObjectId stID;
        FPos3		  pos;
    }target;
    
    short stResultNum;    
    short stAttackerHand; // �����ֹ���
    SAttTargetResult results[const_iMaxResultNum];
};

//������֪ͨ�ͻ��ˣ�����ʩ����һ��û�����õ�Ŀ��ļ���
struct MsgCastInefficacySkill:public Msg
{
    MsgCastInefficacySkill()
    {
        header.dwType = MSG_CASTINEFFICACYSKILL;
        header.stLength = sizeof(MsgCastInefficacySkill);
    }

    ////����������
    //short stAttackerX, stAttackerY;

    //ʹ�õļ���ID
    unsigned short ustSkillID;
    unsigned short ustSkillLevel;

    //ʱ����ص�����
    DWORD    dwActionTime;
    DWORD    dwHoldTime;

    bool bIsCharTarget;//�ü����Ƿ��й�����Ŀ��
    union unionData
    {
        GameObjectId stID;
        FPos3 pos;
    }target;
};

//������֪ͨ�ͻ��ˣ�����Ī��������  // [�ṹû��]
struct MsgIntonate:public Msg
{
    MsgIntonate()
    {
        header.dwType = MSG_INTONATE;
        header.stLength = sizeof(MsgIntonate);
        //
        stSkillID = -1;; //ʹ�õļ���
        stSkillLevel = 0; //ʹ�õļ��ܼ���
        stTagNpcID = -1;        //���ܵ��ͷ�Ŀ��
    }
    //
    short stSkillID;    //ʹ�õļ���
    short stSkillLevel; //ʹ�õļ��ܼ���
    GameObjectId stTagNpcID;    //���ܵ��ͷ�Ŀ��
    //
    DWORD dwTime;        //�ʳ�ʱ��
};
//����ĳ���ͷŷ���
struct MsgSeeMagicRelease:public Msg
{
    MsgSeeMagicRelease()
    {
        header.dwType = MSG_MAGIC_RELEASE;
        header.stLength = sizeof( *this );
    }
    //
    GameObjectId    stReleaseNpcID;    //�����ͷ��ߵ�ID
    short    stMagicNo;        //�ͷŵķ����ı��
    short    stMagicLevel;    //�ͷŵķ����ĵȼ�
    //�������Ҫ�ͻ���ģ��ķ���Ч������Ҫ����һ������Ŀ����ɵĽ��
    SAttTargetResult    result;
};

// �ͻ���������ĳ�����鶯��
struct MsgQueryExpression : public Msg
{
    MsgQueryExpression()
    {
        header.dwType = MSG_EXPRESSION;
        header.stLength = sizeof( MsgQueryExpression );
        stTargetID = -1;
    }
    
    uint16 ustActionID;
    GameObjectId stTargetID;      //  Ŀ��ID
};

//����ĳ������һ������
struct MsgAckExpression : public Msg
{
    MsgAckExpression()
    {
        header.dwType = MSG_ACKEXPRESSION;
        header.stLength = sizeof( MsgAckExpression );
        stTargetID = -1;
    }

    // �ͷ��ߵ�ID��header.stID��
    uint16  ustActionID;      //���鶯���ı��
    GameObjectId stTargetID;   //  Ŀ��ID
};

////���������Ұ
//struct MsgItemEnterMySight2:public Msg
//{
//    MsgItemEnterMySight2()
//    {
//        header.dwType = MSG_ITEMENTERMYSIGHT;
//        header.stLength = sizeof( MsgItemEnterMySight2 );
//    }
//    short x,y;
//    //short stItemID;
//    //unsigned short ustItemID,ustItemCount;
//    //SItemBaseInfo item;
//    SCharItem item;
//};
// ��Ǯ
struct MsgMoneyChange:public Msg
{
    MsgMoneyChange()
    {
        header.dwType = MSG_MONEYCHANGE;
        header.stLength = sizeof( MsgMoneyChange );

        dwNumber = 0;
        dwRMBGold = 0;
    };
    DWORD dwNumber;
    DWORD dwRMBGold;
};

// �۽���
struct MsgJiaoZiChange:public Msg
{
    MsgJiaoZiChange():dwNumber(0), dwJiaoZi(0)
    {
        header.dwType = MSG_JIAOZI_CHANGE;
        header.stLength = sizeof( MsgJiaoZiChange );
    };
    DWORD dwNumber;
    DWORD dwJiaoZi;
};

struct MsgRMBGoldChange:public Msg
{ // ��Ǯ
    MsgRMBGoldChange()
    {
        header.dwType   = MSG_RMBGOLDCHANGE;
        header.stLength = sizeof( MsgRMBGoldChange );
        jinDing = 0;
        jinPiao = 0;
		/*jifen = 0;*/
    };

    uint32 jinDing;
    uint32 jinPiao;
	/*uint32 jifen;*/
};

//�̳ǻ��� ���·����ͻ���
struct MsgRMBConsumeScore:public Msg
{ // ��Ǯ
	MsgRMBConsumeScore()
	{
		header.dwType   = MSG_CONSUMESCORE_CHANGE;
		header.stLength = sizeof( MsgRMBConsumeScore );
		jifen = 0;
	};

	uint32 jifen;
	
};

struct MsgAccountPoint : public Msg
{ 
    MsgAccountPoint()
    {
        header.dwType   = MSG_ACCOUNTPOINT;
        header.stLength = sizeof( MsgAccountPoint );
        point   = 0;
    };

    uint32 point;
};

//�õ���Ʒ
struct MsgGetItem2 : public Msg
{
    MsgGetItem2()
    {
        header.dwType = MSG_GETITEM;
        header.stLength = sizeof( MsgGetItem2 );
    };
    enum EResult
    {
        RESULT_SUCCESS,   // �ɹ�
        RESULT_NOSPACE,   // û�пռ�
        RESULT_ITEMLOCKED,// ��Ʒ����
        RESULT_UNKNOW
    };

    SCharItem  item;
    EResult    enResult;    // ���
    uint8      itemSource;  // װ����Դ
};

struct MsgGetMount : public Msg
{
    MsgGetMount()
    {
        header.dwType = MSG_GETMOUNT;
        header.stLength = sizeof( MsgGetMount );
    };
	enum EnumResult
	{
		ER_Success,
		ER_MountFull
	};
    unsigned short usResult;
    SMountItem     mount;
};

struct MsgUpdateMount : public Msg
{
    MsgUpdateMount()
    {
        header.dwType   = MSG_UPDATEMOUNT;
        header.stLength = sizeof( MsgUpdateMount );
    };
    SMountItem mount;
};

struct MsgChangeMountName : public Msg
{
	MsgChangeMountName()
	{
		header.dwType   = MSG_CHANGEMOUNTNAME;
		header.stLength = sizeof( MsgChangeMountName );
	};
	unsigned short usIndex;
	char szName[dr_MaxPlayerName];
};

//�����������ĵ���
struct MsgDropItem2:public Msg
{
    MsgDropItem2()
    {
        header.dwType = MSG_DROPITEM;
        header.stLength = sizeof( MsgDropItem2 );
    }
    //��������Ʒ������
    float fX, fY;
    unsigned short ustPackIndex;
    unsigned char  ucItemBagType;
};

//���ض�����Ʒ
struct MsgAckDropItem2:public Msg
{
    enum
    {
        Result_Success = 0
        ,Result_Failed
        ,Result_CanNotDrop
    };
    MsgAckDropItem2()
    {
        header.dwType = MSG_ACKDROPITEM;
        header.stLength = sizeof( MsgAckDropItem2 );
    }
    short stResut;
    unsigned short ustPackIndex;
};

struct MsgEquipChanged2:public Msg
{
    MsgEquipChanged2()
    {
        header.dwType = MSG_EQUIPCHANGED;
        header.stLength = sizeof( MsgEquipChanged2 );
        nSuitIndex = 0;
    }
    int8      cWhere;
    SCharItem equip;
    uint8     nSuitIndex;
};
//
struct MsgQueryContinuousSkill:public Msg
{
    MsgQueryContinuousSkill()
    {
        header.dwType = MSG_QUERYCONTINUOUSSKILL;
        header.stLength = sizeof( *this );
    }
};

struct MsgAckContinuousSkill:public Msg
{
    enum enumConst
    {
        const_iMaxSkill = 500//(MSGMAXSIZE-100-sizeof(Msg))/sizeof( short )
    };
    MsgAckContinuousSkill()
    {
        stSkillNum = 0;
        header.dwType = MSG_ACKCONTINUOUSSKILL;
    }
    bool AddSkill( unsigned short ustSkill )
    {
        if( stSkillNum < 0 || stSkillNum >= const_iMaxSkill )
            return false;
        ustSkills[ stSkillNum ] = ustSkill;
        stSkillNum ++;
        return true;
    }
    void CaluLength()
    {
        header.stLength = sizeof( MsgAckContinuousSkill ) - ( const_iMaxSkill - stSkillNum )*sizeof(unsigned short );
    }
    short stSkillNum;
    unsigned short ustSkills[const_iMaxSkill];
};
//
struct MsgAckSwitchFightStatus:public Msg
{
    MsgAckSwitchFightStatus()
    {
        header.dwType = MSG_ACK_SWITCHFIGHTSTATUS;
        header.stLength = sizeof( *this );
    }
    GameObjectId  NpcID;
    unsigned char  cFightStatus;
};
//
struct MsgAckSwitchSitStatus:public Msg
{
    MsgAckSwitchSitStatus()
    {
        header.dwType = MSG_ACK_SWITCHSITSTATUS;
        header.stLength = sizeof( MsgAckSwitchSitStatus );
    }
    GameObjectId  NpcID;
    unsigned char  cSitStatus;
};
//
struct MsgSwitchFightStatus:public Msg
{
    MsgSwitchFightStatus()
    {
        header.dwType = MSG_SWITCHFIGHTSTATUS;
        header.stLength = sizeof( MsgAckSwitchSitStatus );
        //
        FightStatus = 0;
    }
    unsigned char  FightStatus;
};
struct MsgSwitchSitStatus:public Msg
{
    MsgSwitchSitStatus()
    {
        header.dwType = MSG_SWITCHSITSTATUS;
        header.stLength = sizeof( MsgSwitchSitStatus );
        //
        SitStatus = 0;
    }
    unsigned char  SitStatus;
};
//
struct MsgHitItemBag:public Msg
{
    MsgHitItemBag()
    {
        bOverlap = false;
        header.dwType = MSG_HITITEMBAG;
        header.stLength = sizeof( MsgHitItemBag );
    }
    short BagType;    //��������
    short BagIndex;    //�������������
    bool  bOverlap; //�Ƿ�Ҫ�����
    short stItemNum;//ת����Ʒ������
}; 

struct MsgRightHitItemBag:public Msg
{
    MsgRightHitItemBag( )
    {
        header.dwType = MSG_RIGHTHITITEMBAG;
        header.stLength = sizeof( MsgRightHitItemBag );
    }
    short BagType;    //��������
    short BagIndex;    //�������������
};

//
struct MsgHitBodyItem:public Msg
{
    MsgHitBodyItem()
    {
        header.dwType = MSG_HITBODYITEM;
        header.stLength = sizeof( MsgHitBodyItem );
    }
    short BodyIndex;    //�������������
};

struct MsgChangeSkill : public Msg
{
    enum EOpType
    {
        OT_Add,
        OT_Update,
        OT_Delete,
    };

    MsgChangeSkill()
    {
        header.dwType   = MSG_CHANGE_SKILL;
        header.stLength = sizeof( MsgChangeSkill );
        op              = OT_Add;
        bMessageDialog  = true;
    }

    SCharSkill    skill;
    uint8         op;
    bool          bMessageDialog;   // �Ƿ񵯴���ʾ
    //int64         nUnUsedExp;       // ʣ�������δʹ�þ���
};

//���½�ɫ������������ݵ��ͻ���
struct MsgUpdateBag : public Msg
{
    MsgUpdateBag()
    {
        header.dwType = MSG_UPDATECHARABAG;
        header.stLength = sizeof( MsgUpdateBag ) - sizeof(SCharItem) * ITEM_BAGMAX ;
        ucItemBagType = BT_NormalItemBag;
        stNum = 0;        
        stBagIndexBegin = 0;
    }

    unsigned char ucItemBagType; // ����
    short     stNum;             // ʵ���ϱ�������Ʒ��Ŀ
    short     stBagIndexBegin;   // ������ʼ����
    SCharItem stPackItems[ITEM_BAGMAX];

    bool AddItem( const SCharItem& charItem)
    {   
        if( stNum < 0 || stNum >= ITEM_BAGMAX )
            return false;

        stPackItems[stNum] = charItem;
        ++stNum;
        header.stLength = sizeof( *this) - sizeof(SCharItem) * ( ITEM_BAGMAX - stNum);
        return true;
    }

    //short  type;    
    //short  num;
    //union sUpdateItem
    //{
    //    SCharItem         item;
    //    SCharSkill         status;
    //    SCharSymbolStone stone;    
    //    SCharAction         action;
    //}UpdateItem[ITEM_BAG_MAX_SIZE];
    //DWORD dwMoney;

    //void AddMoney( DWORD dwAddMoney )
    //{
    //    dwMoney = dwAddMoney;
    //}
    //void AddItem( SCharItem *pItem )
    //{
    //    if( num >= ITEM_BAG_MAX_SIZE )
    //        return;

    //    memcpy( &UpdateItem[num].item, pItem, sizeof(*pItem) );
    //    num++;
    //    header.stLength = (short)(sizeof(*this)-(ITEM_BAG_MAX_SIZE-num)*sizeof(SCharItem));
    //}
    //void AddItem( SCharSkill *pSkill )
    //{
    //    if( num >= ITEM_BAG_MAX_SIZE )
    //        return;

    //    memcpy( &UpdateItem[num].status, pSkill, sizeof(*pSkill) );
    //    num++;
    //    header.stLength = (short)(sizeof(*this)-(ITEM_BAG_MAX_SIZE-num)*sizeof(SCharSkill));
    //}
    //void AddItem( SCharSymbolStone *pStone )
    //{
    //    if( num >= ITEM_BAG_MAX_SIZE )
    //        return;

    //    memcpy( &UpdateItem[num].stone, pStone, sizeof(*pStone) );
    //    num++;
    //    header.stLength = (short)(sizeof(*this)-(ITEM_BAG_MAX_SIZE-num)*sizeof(SCharSymbolStone));
    //}
    //void AddItem( SCharAction *pAction )
    //{
    //    if( num >= ITEM_BAG_MAX_SIZE )
    //        return;

    //    memcpy( &UpdateItem[num].action, pAction, sizeof(*pAction) );
    //    num++;
    //    header.stLength = (short)(sizeof(*this)-(ITEM_BAG_MAX_SIZE-num)*sizeof(SCharAction));
    //}
};

//���½�ɫ��ݷ�ʽ��
struct MsgUpdateShortCutBag:public Msg
{
    MsgUpdateShortCutBag()
    {
        header.dwType = MSG_UPDATESHORTCUTBAG;
        header.stLength = sizeof( MsgUpdateShortCutBag );
        type = 0; // ����������
        num = 0;  // ʵ���ϵ��ߵ���Ŀ
    }

    short      type; // ����������
    short      num;  // ʵ���ϵ��ߵ���Ŀ
    SMouseItem item[More_iHotkey];

    void AddItem(SMouseItem *pItem)
    {
        if (num >= More_iHotkey)
            return;
        memcpy(&item[num], pItem, sizeof(item[num]));
        num++;
        header.stLength = (short)(sizeof(*this)- (More_iHotkey - num) * sizeof(SCharItem));
    }
};

struct MsgUpdateVisualEquip:public Msg
{ // ���½�ɫ���ϵ�װ�����ݵ��ͻ���
    MsgUpdateVisualEquip()
    {
        header.dwType = MSG_UPDATEVISUALEQUIP;
        header.stLength = sizeof( MsgUpdateVisualEquip );
    }

    SCharItem item[EEquipPartType_MaxEquitPart];
    
    void AddItem( uint8 index, SCharItem* pItem)
    {
        if ( index>=EEquipPartType_MaxEquitPart || NULL == pItem )
        { return; }
            
        item[index] = *pItem;
    }
};

struct MsgUpdateFightData : public Msg
{ //���½�ɫ���ϵĿͻ�����Ҫ֪���Ķ������ݵ��ͻ���
    MsgUpdateFightData( )
    {
        header.dwType = MSG_UPDATEFIGHTDATA;
        header.stLength = sizeof( MsgUpdateFightData );
    }

    SCharAttributeUpdate fightData;
};

// �������״̬���ݸ��ͻ��ˡ�
struct SUpdateBuffInfo
{
    uint8  index;          // �±�
    uint16 stStatusID;     // ״̬������
    uint8  cStatusLevel;   // ״̬�ĵȼ�
    bool   bIsLast;        // �Ƿ����һ����ӵ�״̬
    uint32 dwDurationTime; // ״̬����ʱ��
    bool   bStop;          // �Ƿ���ֹͣ
    uint8  lapoverNum   ;  // ���Ӵ���
};

struct MsgBuffsUpdate : public Msg
{
    MsgBuffsUpdate( )
    {
        header.dwType = MSG_BUFFSUPDATE;
        header.stLength = sizeof(MsgBuffsUpdate) - sizeof(data);
        count = 0;
        memset( data, 0, sizeof(data) );        
    }

    uint8 count; // ��Ч��Buff����
    SUpdateBuffInfo data[BodyStatusType_Max];

    void AddStatus( uint8 index, int8 iLevel, uint16 iStatusID, bool bIsNew, uint32 dwDurationTime, bool bStop, uint8 lapoverNum )
    {
        if ( count >= BodyStatusType_Max )
        { return; }

        data[count].index          = index;
        data[count].stStatusID     = iStatusID;
        data[count].cStatusLevel   = iLevel;     
        data[count].bIsLast        = bIsNew;
        data[count].dwDurationTime = dwDurationTime;
        data[count].bStop          = bStop;
        data[count].lapoverNum     = lapoverNum;
        ++count;
        header.stLength = sizeof(*this) - ( BodyStatusType_Max - count ) * sizeof(SUpdateBuffInfo);
    }
};

struct MsgBuffsChanged : public Msg
{
    MsgBuffsChanged( )
    {
        header.dwType = MSG_BUFFSCHANGED;
        header.stLength = sizeof(MsgBuffsChanged) - sizeof(data);
        count = 0;
        memset( data, 0, sizeof(data) );
    }

    uint8 count;
    SUpdateBuffInfo data[BodyStatusType_Max];
    void AddStatus( uint8 index, int8 iLevel, uint16 iStatusID, bool bIsNew, uint32 dwDurationTime, bool bStop, uint8 lapoverNum )
    {
        if ( count >= BodyStatusType_Max )
        { return; }

        data[count].index          = index;
        data[count].stStatusID     = iStatusID;
        data[count].cStatusLevel   = iLevel;     
        data[count].bIsLast        = bIsNew;
        data[count].dwDurationTime = dwDurationTime;
        data[count].bStop          = bStop;
        data[count].lapoverNum     = lapoverNum;
        ++count;
        header.stLength = sizeof(*this) - ( BodyStatusType_Max - count ) * sizeof(SUpdateBuffInfo);
    }
};
struct MsgChangeDir:public Msg
{
    MsgChangeDir()
    {
        header.dwType = MSG_CHANGEDIR;
        header.stLength = sizeof( MsgChangeDir );
        fChangeDir = 0.0f;
    }
    GameObjectId   stNpcID;    //
    float       fChangeDir;    //ת�� 
};
//
//
struct MsgMoveCompoundItem : public Msg         // [�ṹû��]
{
    enum
    {
        ePackToPrescription = 0,
        ePackToMaterial,
        ePrescriptionToPack,
        eMaterialToPack,
        eAimToPack
    };
    MsgMoveCompoundItem()
    {
        header.dwType = MSG_MOVE_COMPOUND_ITEM;
        header.stLength = sizeof( *this );
    }
    short stMoveType;
    unsigned short stSrcIndex;
    unsigned short stDstIndex;
    unsigned short stCount;
    unsigned char  ucItemBagType;
};

struct MsgQueryCompound : public Msg
{
    MsgQueryCompound()
    {
        header.dwType = MSG_QUERY_COMPOUND;
        header.stLength = sizeof( MsgQueryCompound );
    }
    short stPrescriptionId;
};
struct MsgAckCompound : public Msg
{
    enum
    {
        eResultSuccess = 0                // �ɹ�
        ,eResultFaild                    // ʧ��
        ,eResultMaterialUnconformity    // ԭ�ϲ�����
        ,eResultGemIsMaxLevel            // ��ʯ�ȼ�������߼�
        ,eResultNotEnoughMoney          //û���㹻�Ľ�Ǯ
    };
    MsgAckCompound()
    {
        header.dwType = MSG_ACK_COMPOUND;
        header.stLength = sizeof( MsgAckCompound );
    }
    int nMaterialNum[ITEM_COMPOUND_BAGMAX];
    short stResult;
    SCharItem stAim;
};
struct MsgEquipEvolve : public Msg
{
    enum EConstDefine
    {
        EConstDefine_MaxMaterialCount      = 4,  // ����ĸ���������

        EConstDefine_DefaultMaterialIndex  = 0, 
        EConstDefine_SecondMaterialIndex   = 1,
        EConstDefine_ThirdMaterialIndex    = 2,
        EConstDefine_FourthMaterialIndex   = 3,
    };

    enum EEvolveType
    {
        ET_LevelUp      , // ����
        ET_Identify     , // ����
        ET_ReIdentify   , // ������¯
        ET_Stiletto     , // ���
        ET_Inlay        , // ��Ƕ
        ET_Replace      , // �滻
        ET_TakeDown     , // ��ж
        ET_OpenLight    , // �̽�
        ET_ReOpenLight  , // �̽��¯
        ET_SoulStamp    , // �������
        ET_Maintain     , // ��ֵ
        ET_MaintainCross, // �缶��ֵ
        ET_Charm        , // ��������
        ET_Amulet       , // �������ɫ
		ET_UnknowIdentify, // װ��δ֪����
        ET_Max          ,
    };

    struct SMaterial
    { // ��������
        uint8   bagType ; // ���ڱ���������
        uint16  bagIndex; // ���ڱ�����Indexλ��
        int64   guid    ; // ���ϵ�guid
        uint16  value   ; // ���ϵĸ��� || ��жʱ����±�
		uint8	protectStar; //�������Ǽ�
    };

    MsgEquipEvolve()
    {
        header.dwType = MSG_EQUIP_EVOLVE;
        header.stLength = sizeof( MsgEquipEvolve );

        for ( uint8 i=0; i<EConstDefine_MaxMaterialCount; ++i )
        {
            materials[i].bagIndex = -1;
            materials[i].guid     = 0;
            materials[i].value    = 1;
			materials[i].protectStar = 0;
        }
    }

    uint8              nEvolveType     ; // װ����������
    uint16             nNormalBagIndex ; // װ���ڱ����е�Index
    int64              nNormalGuid     ; // װ����GUID

    SMaterial materials[ EConstDefine_MaxMaterialCount ];    // ԭ������

    // ���������ʹ������� ��ͻ��˼�ʱ�޸�
    //uint8   uchLevelupMaterialBagType; // ��������
    //uint16  stLevelupMaterialIndex;    // ���Ǳ�ʯIndex
    //__int64 n64LevelupMaterialGuid;    // ���Ǳ�ʯguid

    //uint8   uchRateMaterialBagType1; // ������Ʒ��������
    //short   stRateMaterialIndex1;    // ��߼��ʵ�Index
    //__int64 n64RateMaterialGuid1;    // guid
    //uint16  ustRateMaterialCount1;   // ��Ʒ����

    //uint8   uchRateMaterialBagType2; // ������Ʒ��������  
    //int16   stRateMaterialIndex2;    // ʧ�ܱ��׵ļ��ʵ�Index
    //__int64 n64RateMaterialGuid2;    // guid
	static bool EquipMaterialSendMsg(char bSend, void *pData )
	{
		#ifdef GAME_CLIENT
			if( !bSend )
			{
				CloseUI();
				return false;
			}
			Msg* pMsg = static_cast<Msg*>(pData);
			GettheNetworkInput().SendMsg( pMsg );	
			return true;
		#endif 
		return true;
	}
	static void CloseUI();
	void SendEquipMsg();
	bool IsNeedChangeBound(unsigned int PlayerID = 0);
};    

struct MsgBaseIntensifyEquip : public Msg
{
    enum EResult
    {
        e_Succeed               , // �ɹ�
        e_Lost                  , // ʧ��
        e_ItemNotMatch          , // װ����ƥ��
        e_ErrorLevelRep         , // ����ʹ�õȼ�����ȷ
        e_IntensifyMax          , // ǿ��������ߵȼ�
        e_ItemNotExist          , // ��Ʒ������
        e_NotEnoughMoney        , // û���㹻��Ǯ
        e_NotEnoughQuality      , // Ʒ�ʲ���
        e_ErrorMaterialItem     , // ����Ĳ���
        e_ErrorGemItem          , // ����ı�ʯ
        e_HaveIdentify          , // �Ѿ���������
        e_ItemCantIdentify      , // Ŀ������޷�����
        e_BaseRandNotOpen       , // ������������Ի�û�п�
        e_HaveLiuJin            , // �Ѿ��̽�
        e_NoLiuJin              , // û���̽�
        e_MaterialItemLevel     , // �������ϵȼ�����
        e_FashionCanNotEvolve   , // ʱװ����ǿ��
        e_NotHaveRateMaterial   , // ȱ�ٲ���
        e_ErrorRateMaterialCount, // ������������ȷ
        e_FullHole              , // ����
        e_PreHoleIsExist        , // ǰ�ÿ׻�û�п�
        e_HoleNotEnough         , // �ײ���
        e_HoleIndexError        , // Ŀ��ײ���
        e_GemIsNotExist         , // ��ʯ������
        e_BagIsFull             , // ��������
        e_GemTakeDownFail       , // ��ʯж��ʧ��
        e_HaveSoulStamp         , // �Ѿ��������
        e_AmuletRandIsFull      , // �������ɫ��������
        e_HaveSameBaseRand      , // ������ͬ��ɫ�������
		e_InlayIsNotExist       , // ��Ƕ��������
		e_ErrorInlayItem        , // �������Ƕ��
		e_RateBollNotExist		, // ���ʱ��鲻����
		e_ErrorRateBoll			, // ����ļ��ʱ���
		e_InlaySameTypeGem		, // ������Ƕͬ���ͱ�ʯ
		e_ErrorUnknowIdentify	, // δ֪��������
        e_Max                   ,
    };

    uint8     nEvolveType     ;
    uint16    nResult         ;
};

struct MsgIntensifyEquip : public MsgBaseIntensifyEquip
{
    MsgIntensifyEquip()
    {
        header.dwType = MSG_INTENSIFYEQUIP;
        header.stLength = sizeof( MsgIntensifyEquip ) - sizeof( SCharItem ) ;
    }
    
    uint16    nNormalBagIndex ;
    uint8     value           ; // ��ж��ʱ���ʾ����ж�ı�ʯλ
    SCharItem item            ; // e_Succeed �� e_Lost �᷵�ص��ߵ����� ,��������������ṹ

    void AddCharItem( SCharItem& xItem )
    {
        item = xItem;
        header.stLength +=  sizeof( SCharItem ) ;
    }
};

struct MsgTellCharVar : public Msg
{ // 0~3000Ϊ����������� 3000~6000Ϊ����״̬���� ������varId��ʱû�� �������δ�����
    struct SCharVar
    {
        short varId   ; // ����Id
        short varValue; // ������ֵ
    };

    MsgTellCharVar()
    {
        header.dwType   = MSG_TELL_CHAR_VAR;
        header.stLength = sizeof( MsgTellCharVar );
        SetLevel( level_tiptop );
        varCount = 0;
        memset( charVars, 0, sizeof(SCharVar) * More_iMaxVars );
    };

    bool AddValue( short varId, short varValue )
    {
        if( varCount >= More_iMaxVars || varCount < 0 )
        { return false; }

        charVars[varCount].varId       = varId;
        charVars[varCount].varValue    = varValue;
        varCount++;

        header.stLength = sizeof( MsgTellCharVar ) - sizeof( SCharVar ) * ( More_iMaxVars - varCount);
        return true;
    }

    uint16   varCount               ; // ������ʵ�ʸ���
    SCharVar charVars[More_iMaxVars]; // ������ֵ
};


struct MsgTellQuestTime : public Msg
{
    MsgTellQuestTime()
    {
        header.dwType   = MSG_TELLQUESTTIME;
        header.stLength = sizeof( MsgTellQuestTime );
        SetLevel( level_tiptop );
        count = 0;
    };

    bool AddValue( uint16 questId, __int64 time )
    {
        if( count >= QuestLimitTimeMaxCount )
        { return false; }

        questTimes[count].id   = questId;
        questTimes[count].time = time;
        count++;

        header.stLength = sizeof( MsgTellQuestTime ) - sizeof( SQuestTimeRecord ) * ( QuestLimitTimeMaxCount - count );
        return true;
    }

    uint8            count; // ������ʵ�ʸ���
    SQuestTimeRecord questTimes[ QuestLimitTimeMaxCount]; // ������ֵ
};

struct MsgReqQuestInfo : public Msg
{
    MsgReqQuestInfo()
    {
        header.dwType = MSG_REQ_QUEST_INFO;
        header.stLength = sizeof(MsgReqQuestInfo);
    }
    short stQuestId;
};
struct MsgAckQuestInfo : public Msg
{
    MsgAckQuestInfo()
    {
        header.dwType = MSG_ACK_QUEST_INFO;
        header.stLength = sizeof(MsgAckQuestInfo);
    }
    SQuest stQuest;
};

struct MsgProfessionChangeInfo : public Msg
{
    MsgProfessionChangeInfo()
    {
        header.dwType = MSG_PROFESSIONCHANGE;
        header.stLength = sizeof(MsgProfessionChangeInfo);
    }
    short stProfession;
};

struct MsgCloseItemFormIdx : public Msg 
{

    MsgCloseItemFormIdx()
    {
        header.dwType = MSG_CLOSEITEMFORMIDX;
        header.stLength = sizeof(MsgCloseItemFormIdx);
    }
    /*SCharItem stItem;*/
    unsigned short ustBagType;
    unsigned short ustIdx;
    unsigned short ustCount;
};

struct MsgRemoveItemByBagType : public Msg 
{
	MsgRemoveItemByBagType()
    {
        header.dwType = MSG_REMOVEITEMBYBAGTYPE;
        header.stLength = sizeof(MsgRemoveItemByBagType);
    } 
	unsigned char  ucItemBagType;//ָ����������
	unsigned char  ucIndex;//ָ��λ��
	unsigned short ustItemID;
};

struct MsgRemoveItem : public Msg 
{
    MsgRemoveItem()
    {
        header.dwType = MSG_REMOVEITEM;
        header.stLength = sizeof(MsgRemoveItem);
    }    
    unsigned short ustItemID;
    unsigned short ustCount;
    unsigned char  ucItemBagType;
};

struct MsgRemoveItemByGuID : public Msg 
{
    MsgRemoveItemByGuID()
    {
        header.dwType = MSG_REMOVEITEMBYGUID;
        header.stLength = sizeof(MsgRemoveItemByGuID);
    }    
    __int64 GuID;
    unsigned short ustCount;
    unsigned char  ucItemBagType;
};


struct MsgUpHpAndMp:public Msg
{
    MsgUpHpAndMp()
    {
        header.dwType = MSG_UPHPANDMP;
        header.stLength = sizeof(MsgUpHpAndMp);
    }
    int nHpUp;
    int nMpUp;
};

struct MsgMoveIntensifyItem : public Msg    // [�ṹ��ʱû��]
{
    enum
    {
        ePackToGem = 0,
        eGemToPack,
        ePackToEquip,
        eEquipToPack,
        ePackToLuck,
        eLuckToPack

    };
    MsgMoveIntensifyItem()
    {
        header.dwType = MSG_MOVE_INTENSIFY_ITEM;
        header.stLength = sizeof( MsgMoveIntensifyItem );
    }
    short stMoveType;
    unsigned short stSrcIndex;
    unsigned short stDstIndex;
    unsigned short stCount;
    unsigned char  ucItemBagType;
};

struct MsgMoveReduceItem:public Msg
{
    enum
    {
        ePackToReduce = 0,
        eReduceToPack,
        eAimToPack
    };
    MsgMoveReduceItem()
    {
        header.dwType = MSG_MOVE_REDUCE;
        header.stLength = sizeof( MsgMoveReduceItem );
    }
    short stMoveType;
    unsigned short stSrcIndex;
    unsigned short stDstIndex;
    unsigned short stCount;
};

struct MsgAckReduceItem : public Msg
{
    MsgAckReduceItem()
    {
        header.dwType   = MSG_ACKFORREDUCE;
        header.stLength = sizeof( MsgAckReduceItem );
    }
    uint16 index; // �������Ʒλ��
    int64  guid;  // �������Ʒguid
};

struct MsgReqReduceItem : public Msg
{ // �ȼ���ɾ
    enum EResult
    {
        eSuc = 0,
        eFail,
        eMax
    };

    MsgReqReduceItem()
    {
        header.dwType = MSG_REDUCEOFF;
        header.stLength = sizeof( MsgReqReduceItem );
    }
    uint32    result;
    uint16    index; // �������Ʒλ��
    int64     guid;  // �������Ʒguid    
    uint8     itemBagType;
    SCharItem product;
};

// ������Ϣ
struct MsgChat:public Msg
{
    enum EConstDefine
    {
        Item_Hyber_Cnt_Max = 3
    };

    enum CHAT_TYPE
    {
        CHAT_TYPE_NORMAL			= 1 << 1,    //��ͨ����
        CHAT_TYPE_GUILD				= 1 << 2,    //��������
        CHAT_TYPE_TERM				= 1 << 3,    //С������
        CHAT_TYPE_PRIVATE			= 1 << 4,    //˽��
        CHAT_TYPE_MS				= 1 << 5,    //����
        CHAT_TYPE_GAMEPROMPT		= 1 << 6,    //��Ϸ��ʾ CHAT_TYPE_GAMEPROMPT
        CHAT_TYPE_BULL				= 1 << 7,    //ȫ������ GM ��ά
        CHAT_TYPE_SHOUT				= 1 << 8,    //���� ����������Ź���
        CHAT_TYPE_HIGHSHOUT			= 1 << 9,    //�ߺ� ����
        CHAT_TYPE_GM				= 1 << 10,   //GM �����GM����������Ϣ
        CHAT_TYPE_SHOUT_VIP			= 1 << 11,   //���� ����������Ź��� ����vip�� ����С����
        CHAT_TYPE_HIGHSHOUT_VIP		= 1 << 12,   //�ߺ� ����ͬȫ��--     ����vip�� С����
        CHAT_TYPE_BULL_VIP			= 1 << 13,   //ȫ������--            ����vip�� ��˷�

        CHAT_TYPE_PARTICAL1_VIP		= 1 << 14,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL2_VIP		= 1 << 15,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL3_VIP		= 1 << 16,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL4_VIP		= 1 << 17,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL5_VIP		= 1 << 18,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL6_VIP		= 1 << 19,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL7_VIP		= 1 << 20,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL8_VIP		= 1 << 21,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL9_VIP		= 1 << 22,   //�����С����Ϣ ����vip
        CHAT_TYPE_PARTICAL10_VIP	= 1 << 23,   //�����С����Ϣ ����vip
        CHAT_TYPE_LEAGUE			= 1 << 24,   //��������
        CHAT_TYPE_PROGRAM_SYSTEM	= 1 << 25,   //����ϵͳ֪ͨ
        CHAT_TYPE_FIGHTINFO         = 1 << 26,   //ս����Ϣ
        CHAT_TYPE_BATTLE            = 1 << 27,   // ս����ӪƵ��
        CHAT_TYPE_COUNTRY           = 1 << 28,   // ����Ƶ��
		CHAT_TYPE_FAMILY			= 1 << 29,	 // ����Ƶ��
		CHAT_TYPE_COUNTRYOFFICIAL	= 1 << 30,  // ���ҹ�ԱƵ��
        //CHAT_MAX
    };

    // ˵���˹��һ���
    enum ESpeakerType
    {
        EST_None,            // ��
        EST_ZhiZunHuangGuan, // ����ʹ��û�
    };

    enum HYBERTYPE
    {
        HYBERTYPE_ITEM = 0,		//��Ʒ������
        HYBERTYPE_SKILL,		//���ܳ�����
        HYBERTYPE_TASK,			//��������
        HYBERTYPE_MAX,
    };

    MsgChat()
    {
        //header.uMsgLevel = level_normal;
        header.dwType     = MSG_CHAT;
        header.stLength   = 0;
        nHyberItemCnt = 0;
        nStringLen    = 0;
        bIsRreply     = false;
        type          = BT_All;
        memset( ehyberType, 0, sizeof(ehyberType) );
        memset( onlyId, 0, sizeof(onlyId) );
        memset( itemId, 0, sizeof(itemId) );
    };

    MsgChat( MsgChat::CHAT_TYPE stType )
    {
        header.dwType   = MSG_CHAT;
        header.stLength = 0;
        nHyberItemCnt   = 0;
        bIsRreply       = false;
        nStringLen      = 0;
        type            = BT_All;
        memset( ehyberType, 0, sizeof(ehyberType) );
        memset( onlyId, 0, sizeof(onlyId) );
        memset( itemId, 0, sizeof(itemId) );

        chatHeader.stType = stType;
    };

    struct ChatHeader   // ������Ϣͷ
    { 
        ChatHeader()
        {
            stType            = CHAT_TYPE_NORMAL;
            stExpressionId    = -1;
            dwSpeakPlayerDBID = InvalidLogicNumber;
            dwToPlayerDBID    = InvalidLogicNumber;
            speakerPlayerType = EST_None;
            dwGuildID         = InvalidLogicNumber;
            memset( szToName, 0, sizeof( szToName ) );
            memset( szSpeakName, 0, sizeof( szSpeakName ) );
        }

        int    stType;                         // �����������
        uint8  uchSpeakCountry;                // ˵���˹���ID
        uint8  uchSpeakerTitle;                // ˵���˵Ĺ���ְλ
        uint32 dwSpeakPlayerDBID;              // ˵����DBID
        char   szSpeakName[dr_MaxPlayerName];  // ˵��������
        uint32 dwGuildID;                      // ˵���˰��ID
        char   szToName[dr_MaxPlayerName];     // ��˭˵(����)
        uint32 dwToPlayerDBID;                 // ��˭˵(dbid)
        short  stExpressionId;                 // ����ID
        uint8  speakerPlayerType;              // ��������
    };

    ChatHeader chatHeader;
    bool       bIsRreply;     // �Ƿ��ǻظ���Ϣ
    int        nHyberItemCnt;
    int        nStringLen;
    uint8      ehyberType[Item_Hyber_Cnt_Max];
    __int64    onlyId[Item_Hyber_Cnt_Max];
    int        itemId[Item_Hyber_Cnt_Max];
    uint8      type;          // ��������
    char       szString[dr_MaxChatString];

    void SetExpressionId( short nID )
    {    
        chatHeader.stExpressionId = nID;
    }

    void SetString( const char* pszChatString, const char* data = NULL, int cnt=0)
    {
        memset( szString, 0, sizeof(char)*dr_MaxChatString );

        if( strlen(pszChatString)+1+sizeof(SCharItem)*cnt < dr_MaxChatString)
        {
            if( NULL != data && cnt > 0 )
            {
                nHyberItemCnt = cnt;
                nStringLen = (int)strlen(pszChatString)+1;

                memcpy( szString, pszChatString, min(strlen(pszChatString)+1, sizeof(szString)) );

                if (type == BT_MountBag)
                {
                    memcpy( szString+strlen(pszChatString)+1, data,  min(sizeof(SMountItem)*cnt, sizeof(szString)-(strlen(pszChatString)+1)) );

                    header.stLength = sizeof(header) + sizeof(ChatHeader) + sizeof(bIsRreply) + sizeof(nHyberItemCnt) + sizeof(nStringLen) + sizeof(ehyberType) + sizeof(onlyId) + sizeof(itemId) +
                        (int)strlen(szString)+1 + sizeof(SMountItem)*cnt + sizeof(type);
                }
                else if(type == BT_PetBag)
                {
                    memcpy( szString+strlen(pszChatString)+1, data,  min(sizeof(SPetItem)*cnt, sizeof(szString)-(strlen(pszChatString)+1)) );

                    header.stLength = sizeof(header) + sizeof(ChatHeader) + sizeof(bIsRreply) + sizeof(nHyberItemCnt) + sizeof(nStringLen) + sizeof(ehyberType) + sizeof(onlyId) + sizeof(itemId) +
                        (int)strlen(szString)+1 + sizeof(SPetItem)*cnt + sizeof(type);
                }
                else
                {
                    memcpy( szString+strlen(pszChatString)+1, data,  min(sizeof(SCharItem)*cnt, sizeof(szString)-(strlen(pszChatString)+1)) );

                    header.stLength = sizeof(header) + sizeof(ChatHeader) + sizeof(bIsRreply) + sizeof(nHyberItemCnt) + sizeof(nStringLen) + sizeof(ehyberType) + sizeof(onlyId) + sizeof(itemId) +
                        (int)strlen(szString)+1 + sizeof(SCharItem)*cnt + sizeof(type);
                }
            }
            else
            {
                //nHyberItemCnt = cnt;
                nStringLen = (int)strlen(pszChatString)+1;
                memcpy( szString, pszChatString, min(strlen(pszChatString)+1, sizeof(szString)) );
                header.stLength = sizeof(header) + sizeof(ChatHeader) + sizeof(bIsRreply) + sizeof(nHyberItemCnt) + sizeof(nStringLen) + sizeof(ehyberType) + sizeof(onlyId) + sizeof(itemId) + (int)strlen(szString)+ 1 + sizeof(type);;
            }
        }
    }
};

struct MsgDamageOfEffect:public Msg
{
    enum enumMaxDamageNum
    {
        const_iMaxDamageNum = 500//(MSGMAXSIZE-100-sizeof(Msg))/sizeof( SEffectDamage )
    };

    MsgDamageOfEffect()
    {
        header.dwType = MSG_DAMAGEOFEFFECT;
        iDamageNum = 0;
    }

    //false: ��Ϣ��
    bool AddDamage( GameObjectId stWho,short stDamage,DWORD dwFlag = 0 )
    {
        if( iDamageNum < 0 || iDamageNum >= const_iMaxDamageNum )
            return false;
        damages[ iDamageNum ].stWho = stWho;
        damages[ iDamageNum ].stDamage = stDamage;
        damages[ iDamageNum ].dwState  = dwFlag;

        iDamageNum ++;
        return true;
    }

    void CaluLength()
    {
        header.stLength = int(sizeof( MsgDamageOfEffect ) 
            - (const_iMaxDamageNum - iDamageNum)*sizeof(SEffectDamage));
    }

    int iDamageNum;
    //����˺��ļ��ܵ�ID
    unsigned short ustSkillID;
    //
    SEffectDamage damages[const_iMaxDamageNum];
};

//�����½�
struct Msg_MiniGame_Gate_Room_Created : public Msg      // [�ṹû��]
{
    Msg_MiniGame_Gate_Room_Created()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_CREATED;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Created );
    }
    short        stRoomID;    
};

//��������
struct Msg_MiniGame_Gate_Room_Destroyed : public Msg        // [�ṹû��]
{
    Msg_MiniGame_Gate_Room_Destroyed()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_DESTROYED ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Destroyed );
    }
    short        stRoomID;
};

//���뷿��
struct Msg_MiniGame_Gate_Room_In : public Msg       // [�ṹû��]
{
    Msg_MiniGame_Gate_Room_In()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_IN ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_In );
    }
    short        stRoomID;
};

//�뿪����
struct Msg_MiniGame_Gate_Room_Out : public Msg      // [�ṹû��]
{
    Msg_MiniGame_Gate_Room_Out()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_OUT ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Out );
    }
    short        stRoomID;
};

//������Ϣ
//�䳤��Ϣ
//����ֱ�Ӷ�����Ϣ������
//Ҫʹ��һ���ϴ��buffer����������Ϣ
struct Msg_MiniGame_Room_Info : public Msg      // [û��]
{
    Msg_MiniGame_Room_Info()
    {
        header.dwType = MSG_MINIGAME_ROOM_INFO ;
        header.stLength = sizeof( Msg_MiniGame_Room_Info );
        stRuleInfoSize = 0;
    }

    void    SetRuleInfo( char *szInRuleInfo,int iSize )
    {
        memcpy( szRuleInfo,szInRuleInfo,iSize );
        stRuleInfoSize = iSize;
        header.stLength = sizeof( *this ) + iSize;
    }
    char    cNumberOfPeopleInRoom;
    char    szCreator[ dr_MaxNameString ];

    short    stRuleInfoSize;
    //��Ϸ��صĹ�����Ϣ
    char    szRuleInfo[1];
};

//���������ı�
struct Msg_MiniGame_Room_NOPChanged : public Msg        // [�ṹû��]
{
    Msg_MiniGame_Room_NOPChanged()
    {
        header.dwType = MSG_MINIGAME_ROOM_NOPCHANGED;
        header.stLength = sizeof( Msg_MiniGame_Room_NOPChanged );
    }
    char    cNumberOfPeopleInRoom;
};

//�����Ϣ
struct Msg_MiniGame_PlayerInfo : public Msg         // [�ṹû��]
{
    Msg_MiniGame_PlayerInfo()
    {
        header.dwType = MSG_MINIGAME_PLAYERINFO ;
        header.stLength = sizeof( Msg_MiniGame_PlayerInfo );
    }
    char    szPlayerName[ dr_MaxPlayerName ];
};

//������뷿��
struct Msg_MiniGame_Req_InRoom : public Msg         // [�ṹû��]
{
    Msg_MiniGame_Req_InRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_INROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_InRoom );
    }
    short        stRoomID;
};

//���ؼ��뷿��
struct Msg_MiniGame_Ack_InRoom : public Msg     // [�ṹû��]
{
    Msg_MiniGame_Ack_InRoom()
    {
        header.dwType = MSG_MINIGAME_ACK_INROOM ;
        header.stLength = sizeof( Msg_MiniGame_Ack_InRoom );
    }
    enum enumErrorCode
    {
        err_succ = 0
        ,err_full
        ,err_cannotfindroom
    };
    short        stRoomID;
    char        cErrorCode;
};

//�����˳�����
struct Msg_MiniGame_Req_OutRoom : public Msg        // [�ṹû��]
{    
    Msg_MiniGame_Req_OutRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_OUTROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_OutRoom );
    }
    //short        stRoomID;
};
//�����˳�����
struct Msg_MiniGame_Ack_OutRoom : public Msg        // [�ṹû��]
{
    Msg_MiniGame_Ack_OutRoom()
    {
        header.dwType = MSG_MINIGAME_ACK_OUTROOM ;
        header.stLength = sizeof( Msg_MiniGame_Ack_OutRoom );
    }
    enum enumErrCode
    {
        err_succ        = 0
        //
        ,err_cannotfindroom
        //
        ,err_cannotoutmainroom
        ,err_unknown
    };
    short        stRoomID;
    char        cErrCode;
};

//����
//����ֱ�Ӷ�����Ϣ������
//Ҫʹ��һ���ϴ��buffer����������Ϣ
struct Msg_MiniGame_Req_CreateRoom : public Msg     // [�ṹû��]
{
    Msg_MiniGame_Req_CreateRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_CREATEROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_CreateRoom );

        stRuleInfoSize = 0;
    }
    //��������
    char        cMaxPlayer;
    //short        stRoomID;

    void    SetRuleInfo( char *szInRuleInfo,int iSize )
    {
        memcpy( szRuleInfo,szInRuleInfo,iSize );
        stRuleInfoSize = iSize;
        header.stLength = sizeof( Msg_MiniGame_Req_CreateRoom ) + iSize;
    }

    short    stRuleInfoSize;
    //��Ϸ��صĹ�����Ϣ
    char    szRuleInfo[1];
};

//���ش���
struct Msg_MiniGame_Ack_CreateRoom : public Msg     // [�ṹû��]
{
    Msg_MiniGame_Ack_CreateRoom()
    {
        header.dwType = MSG_MINIGAME_ACK_CREATEROOM ;
        header.stLength = sizeof( Msg_MiniGame_Ack_CreateRoom );
    }
    enum enumErrCode
    {
        err_succ
        ,err_fail
    };
    char        cErrCode;
};

//��������
struct Msg_MiniGame_Room_Destroyed : public Msg     // [�ṹû��]
{
    Msg_MiniGame_Room_Destroyed()
    {
        header.dwType = MSG_MINIGAME_ROOM_DESTROYED ;
        header.stLength = sizeof( Msg_MiniGame_Room_Destroyed );
    }
    short        stRoomID;
};


//������
//�䳤
struct Msg_MiniGame_Command : public Msg        // [�ṹû��]
{
    Msg_MiniGame_Command()
    {
        header.dwType = MSG_MINIGAME_COMMAND ;        
        header.stLength = sizeof( Msg_MiniGame_Command );
    }

    void SetCmd( char *szInCmd,int iDataSize )
    {
        memcpy( szCmd,szInCmd,iDataSize );
        header.stLength = sizeof( Msg_MiniGame_Command ) + iDataSize;
    }

    char    szCmd[1];
};

//��Ϸ��ʼ
struct Msg_MiniGame_Start : public Msg      // [�ṹû��]
{
    Msg_MiniGame_Start()
    {
        header.dwType = MSG_MINIGAME_START;
        header.stLength = sizeof( Msg_MiniGame_Start );
    }
};

struct Msg_MiniGame_TimeFrame : public Msg      // [�ṹû��]
{
    Msg_MiniGame_TimeFrame()
    {
        header.dwType = MSG_MINIGAME_TIMEFRAME;
        header.stLength = sizeof( Msg_MiniGame_TimeFrame );
    }
};

struct MsgCleanUpBag : public Msg
{
    MsgCleanUpBag()
    {
        header.dwType = MSG_CLEANUP_BAG;
        header.stLength = sizeof( MsgCleanUpBag );
        ucItemBagType = BT_NormalItemBag;
        stBagIndexBegin = 0;
        stBagIndexEnd = 0;
    }

    unsigned char ucItemBagType; // ����
    short stBagIndexBegin;       // �����Ŀ�ʼ����
    short stBagIndexEnd;         // �����Ľ�������
};


struct MsgConnectGateOverTime : public Msg
{
    MsgConnectGateOverTime()
    {
        header.dwType   = MSG_OUT_OF_LONGIN_TIME;
        header.stLength = sizeof(MsgConnectGateOverTime);
        accountId       = 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey ) );
		Sessionkey = 0;
    }

    unsigned int accountId;
    //char         szSessionKey[40+1];
	__int64 Sessionkey;
};

struct MsgMapInfoReady : Msg
{
    MsgMapInfoReady()
    {
        header.dwType   = MSG_MAPINFOREADY;
        header.stLength = sizeof(MsgMapInfoReady);
    }
};

struct MsgAckResult : Msg
{
	MsgAckResult()
	{
		header.dwType   = MSG_ACK_RESULT;
		header.stLength = sizeof(MsgAckResult);
		
        result = 0;
        value  = 0;
	}

	unsigned short result;
    int32 value;
};

struct MsgEnterWorldChangeNameReq : Msg
{
	MsgEnterWorldChangeNameReq()
	{
		header.dwType   = MSG_ENTERWORLDCHANGENAMEREQ;
		header.stLength = sizeof(MsgEnterWorldChangeNameReq);
	}
};

struct MsgReturnToCharacterServer : Msg
{
	MsgReturnToCharacterServer()
	{
		header.dwType   = MSG_RETURNTO_CHARACTERSERVER;
		header.stLength = sizeof(MsgReturnToCharacterServer);
	}
};

struct MsgAddRecipeAck : public Msg
{
    MsgAddRecipeAck()
    {
        header.dwType   = MSG_ADDRECIPEACK;
        header.stLength = sizeof(MsgAddRecipeAck);
        chResult = Result_Success;
    }

    enum AddRecipeResult
    {
        Result_Success = 0,     // ѧϰ�ɹ�
        Result_AlreadyExist,    // �Ѿ�ѧ��
        Result_Full,            // ѧ����
        Result_NoThisRecipe,    // û������䷽
        Result_Unknow,          // ��֪����
    };

    unsigned char chResult;
    unsigned short ustRecipeID;
};

struct MsgChangeProtectLockTimeReq : public Msg
{
    MsgChangeProtectLockTimeReq()
    {
        header.dwType = MSG_CHANGEPROTECTLOCKTIMEREQ;
        header.stLength = sizeof( MsgChangeProtectLockTimeReq );
        chTime = 1;
    }
    unsigned char chTime;               // ��λ:����
};

struct MsgChangeProtectLockTimeAck : public Msg
{
    MsgChangeProtectLockTimeAck()
    {
        header.dwType = MSG_CHANGEPROTECTLOCKTIMEACK;
        header.stLength = sizeof( MsgChangeProtectLockTimeAck );
        chResult = Result_Success;
    }

    enum Change_Result          // ���ؽ��
    {
        Result_Success = 0,
        Result_Fail,
    };

    unsigned char chResult;
};

struct MsgNotifyBeKick : public Msg
{
    MsgNotifyBeKick()
    {
        header.dwType = MSG_BEKICK;
        header.stLength = sizeof( MsgNotifyBeKick );
        kickType = EKT_None;
    }

    enum EKickType
    { // ���ؽ��
        EKT_None,                 // None
        EKT_AccountKick,          // �������˺���
        EKT_GraphicCodeErrorKick, // ��֤������
        EKT_SystemKick,           // ϵͳ����
		EKT_GraphicCodeTimeOut,	  // ��֤�볬ʱ
        EKT_Hook,                 // ʹ�����
        EKT_Ban,                  // GM
        EKT_ChangeNameKick,       // ��������
    };

    uint8  kickType;
};

struct MsgTellAntiAddictionAccountInfo : public Msg
{
    MsgTellAntiAddictionAccountInfo()
    {
        header.dwType   = MSG_TELLANTIADDICTIONACCOUNTINFO;
        header.stLength = sizeof( MsgTellAntiAddictionAccountInfo );
    }
    unsigned long onlineMinuteTime; // ����ʱ��
    unsigned long offMinuteTime;    // ����ʱ��
};


struct MsgEctypeStageTimeRemain : public Msg
{
    MsgEctypeStageTimeRemain()
    {
        header.dwType   = MSG_ECTYPESTAGETIMEREMAIN;
        header.stLength = sizeof( MsgEctypeStageTimeRemain );
    }

    unsigned long dwTimeRemain;         // ����Ϊ��λ
};

// ������еļ���cooldownʱ��
struct MsgClearSkillCollDown : public Msg
{
    MsgClearSkillCollDown()
    {
        header.dwType   = MSG_CLEARSKILLCOLLDOWN;
        header.stLength = sizeof( MsgClearSkillCollDown );

        ustSkillID = InvalidLogicNumber;
    }

    unsigned short ustSkillID;        // ���� ErrorUnsignedShortID ����������м��ܵ�cdʱ��
};


struct MsgTellClient : public Msg
{
    MsgTellClient()
    {
        header.dwType = MSG_TELLCLIENT;
        header.stLength = sizeof( MsgTellClient ) - sizeof( xParam );
        nCount = 0;
        chType = ECD_TellClient;
    }
    enum EConstDefine
    {
        ECD_TellClient = 0,     
        ECD_ShowInfo   = 1,

        
        ECD_MaxCount   = 8,
    };

    unsigned char chType;            // ��ʾ����
    unsigned short ustStringID;      // ��ʾ�ִ���ID
    bool bTile;                      // showinfo ����
    //unsigned short ustTime;        // showinfo ����
    unsigned long dwShowInfoType;    // showinfo ����
    int nCount;                      // ��������
    UnionParam xParam[ECD_MaxCount]; // ����ֵ
    
    void CopyParamData( UnionParam* pParam, int count )
    {
        if ( count >= ECD_MaxCount || pParam == NULL || count == 0 )
        { return; }

        nCount = count;
        memcpy( xParam, pParam, sizeof( UnionParam) * count );
        header.stLength += sizeof( UnionParam ) * count;
    }
};

// ������֪ͨ�ͻ�����صĽ���, �ͻ��˶˵�������
struct MsgTellLuckReward : public Msg
{
    MsgTellLuckReward()
    {
        header.dwType = MSG_TELLLUCKREWARD;
        header.stLength = sizeof( MsgTellLuckReward );

        memset( uchIndex, -1, sizeof( uchIndex ) );
        nCount        = 0;
        uchOperator   = ECD_Operator_ShowLuck;
        uchRewardType = 0;
    }
    enum EConstDefine
    {
        ECD_MaxNumber           = 15,   // ���������
        ECD_Operator_ShowLuck   = 0,    // ��ʾҡ������
        ECD_Operator_ShowReward = 1,    // ��ʾ�콱����
    };
    
    unsigned char uchLevel;             // �ڼ���
    unsigned char uchOperator;          // ����
    unsigned char uchRewardType;        // ����������( ��˫�� ���� �뱶  ���߳�ʼֵ )
    int nCount;                         // ��������
    uint8 uchIndex[ECD_MaxNumber];      // ������Ʒ������
    void AddRewardIndex( uint8 chIndex )
    {
        if ( nCount >= ECD_MaxNumber )
        { return; }

        uchIndex[nCount] = chIndex;
        ++nCount;
    }
};

// �ͻ��˷��͹����Ƿ���ȡ��Ʒ����ҡ�� ( ��ȷ���رս�����Ƿ� ����ECD_Get ,���������״̬ )
struct MsgLuckRewardReq : public Msg 
{
    MsgLuckRewardReq()
    {
        header.dwType = MSG_LUCKREWARDREQ;
        header.stLength = sizeof( MsgLuckRewardReq );
        uchType = ECD_Luck;
    }

    enum EConstDefine
    {
        ECD_Start = 0,        // �ͻ��˿�ʼ
        ECD_Luck  = 1,        // ҡ��
        ECD_Get   = 2,        // ��ȡ��Ʒ
        ECD_Close = 3,        // �ͻ��˹رմ���
    };

    unsigned char uchType;
};

struct MsgLuckRewardAck : public Msg 
{
    MsgLuckRewardAck()
    {
        header.dwType = MSG_LUCKREWARDACK;
        header.stLength = sizeof( MsgLuckRewardAck );
    }

    enum EConstDefine
    {
        ECD_Start = 0,          // �ͻ��˿�ʼת
        ECD_Close = 1,          // �رս���
    };

    unsigned char uchResult;
};

// ������֪ͨҡ�����
struct MsgLuckRewardResult : public Msg
{
    MsgLuckRewardResult()
    {
        header.dwType = MSG_LUCKREWARDRESULT;
        header.stLength = sizeof( MsgLuckRewardResult );
    }

    unsigned char uchLevel;                 // �ڼ���
    unsigned char uchRewardType;            // ҡ���Ľ������  �� LuckRewardConfig.h���ж���
};


///////////////////////////////////////////////////////////////////////////
// �������
struct MsgShowTreasureBox : public Msg      // �ͻ�����ʾ�������
{
    MsgShowTreasureBox()
    {
        header.dwType = MSG_SHOWTREASUREBOX;
        header.stLength = sizeof( MsgShowTreasureBox );

        uchOperate = ECD_Type_Init;
    }

    enum EConstDefine
    {
        ECD_Type_Init = 0,      // ��ʼ״̬
        ECD_Type_Receive,       // ��ȡ״̬
    };

    unsigned char uchOperate;    // ��������

    unsigned char ucItemBagType; // ��������
    short stIndex;               // ��������
    __int64 nGuid;               // ��Ʒguid
    unsigned char uchLevel;      // ����ȼ�
    unsigned char nResultIndex;  // ҡ���ı��佱�������� 

};

struct MsgTreasureBoxReq : public Msg      // �ͻ�������ҡ��
{
    MsgTreasureBoxReq()
    {
        header.dwType = MSG_TREASUREBOXREQ;
        header.stLength = sizeof( MsgTreasureBoxReq );
    }

    enum EConstDefine
    {
        ECD_Type_Luck = 0,      // ҡ��
        ECD_Type_Receive,       // ��ȡ
    };

    unsigned char uchOperate;           // ��������

    unsigned char ucBoxItemBagType;     // ��������
    short stBoxIndex;                   // ��������
    __int64 nBoxGuid;                   // ��Ʒguid

    unsigned char ucKeyItemBagType;     // ��������
    short stKeyIndex;                   // ��������
    __int64 nKeyGuid;                   // ��Ʒguid
    
};

struct MsgTreasureBoxAck : public Msg      // �������ظ���һЩ������Ϣ
{
    MsgTreasureBoxAck()
    {
        header.dwType = MSG_TREASUREBOXACK;
        header.stLength = sizeof( MsgTreasureBoxAck );
    }

    unsigned char uchError;     // ������Ϣ
};

struct MsgTreasureBoxResult : public Msg      // ҡ�����
{
    MsgTreasureBoxResult()
    {
        header.dwType = MSG_TREASUREBOXRESULT;
        header.stLength = sizeof( MsgTreasureBoxResult );
    }

    unsigned char ucItemBagType;  // ��������
    short stIndex;                // ��������
    __int64 nGuid;                // ��Ʒguid

    unsigned char uchLevel;       // ����ȼ�
    unsigned char uchResultIndex; // ����ĵڼ�������

    short nNewItemID;            // �µ���Ʒid
};
///////////////////////////////////////////////////////////////////////////
struct MsgCheckCheatReq : public Msg
{
    MsgCheckCheatReq()
    {
        SetLevel( level_tiptop );
        header.dwType = MSG_CHECKCHEATREQ;
        header.stLength = sizeof( MsgCheckCheatReq ) - sizeof( szCode );
        nLength = 0;
        memset( szCode, 0, sizeof( szCode ) );
    }
    enum EConstDefine
    {
        ECD_MaxLength = 4096,
    };

    int nLength;
    char szCode[ECD_MaxLength];

    bool AddCode( const char* szBuff, int nSize )
    {
        if ( nSize == 0 || nSize > ECD_MaxLength )
        { return false; }

        memcpy_s( szCode, sizeof( szCode ), szBuff, nSize );
        nLength = nSize;
        header.stLength += nSize;
        return true;
    }
};

struct MsgCheckCheatAck : public Msg
{
    MsgCheckCheatAck()
    {
        SetLevel( level_tiptop );
        header.dwType = MSG_CHECKCHEATACK;
        header.stLength = sizeof( MsgCheckCheatAck );

        nResult = 0;
    }

    uint32 nResult;
};

struct MsgGetProcessListReq : public Msg
{
    MsgGetProcessListReq()
    {
        SetLevel( level_tiptop );
        header.dwType = MSG_GETPROCESSLISTREQ;
        header.stLength = sizeof( MsgGetProcessListReq ) - sizeof( szCode );
        nLength = 0;
        memset( szCode, 0, sizeof( szCode ) );
    }
    enum EConstDefine
    {
        ECD_MaxLength = 4096,
    };

    int nLength;    // nLength == 0ʱ Ҫ��ͻ����Լ�����
    unsigned char szCode[ECD_MaxLength]; 

    bool AddCode( const char* szBuff, int nSize )
    {
        if ( nSize == 0 || nSize > ECD_MaxLength )
        { return false; }

        memcpy_s( szCode, sizeof( szCode ), szBuff, nSize );
        nLength = nSize;
        header.stLength += nSize;
        return true;
    }

};

struct MsgGetProcessListAck : public Msg
{
    MsgGetProcessListAck()
    {
        SetLevel( level_tiptop );
        header.dwType = MSG_GETPROCESSLISTACK;
        header.stLength = sizeof( MsgGetProcessListAck );
        memset( szList, 0, sizeof( szList ) );
    }
    enum EConstDefine
    {
        ECD_MaxLength = 4096,
    };

    int nResult;                         // ���ؽ������ִ�д���ĳ���
    float fSpeed;                        // ����ٶ�
    bool bRideMount;                     // �Ƿ���������
    char szList[ECD_MaxLength];          // ����ģ���б�ͽ����б�, ��;�Ÿ���
};

struct MsgTellGameStage : public Msg
{
    MsgTellGameStage()
    {
        header.dwType = MSG_TELLGAMESTAGE;
        header.stLength = sizeof( MsgTellGameStage );
    }

    short stStage;      // ��һ��ִ�н׶�  -1 ��ʾ������,û���´�
    short stTotalStage; // �ܹ����ٲ�
    uint32 dwTime;      // �ý׶γ���ʱ�� ��λ: ��

};

struct MsgMoveStarReq : public Msg
{
    MsgMoveStarReq()
    {
        header.dwType = MSG_MOVESTARREQ;
        header.stLength = sizeof( MsgMoveStarReq );
    }

    enum EConstDefine
    {
        ECD_MoveToItem  = 0,  // ת�Ƶ����ǵ�����
        ECD_MoveToEquip = 1,  // ת�Ƶ�װ����
    };

    char chOperate;         // ת������
    char chItemBagType;     // ���ǵ��߱�������
    short stItemIndex;      // ���ǵ��߱�������
    __int64 nItemGuid;      // ���ǵ���guid

    char chEquipBagType;    // װ����������
    short stEquipIndex;     // װ����������
    __int64 nEquipGuid;     // װ��guid
};


struct MsgMoveStarAck : public Msg
{
    MsgMoveStarAck()
    {
        header.dwType = MSG_MOVESTARACK;
        header.stLength = sizeof( MsgMoveStarAck );
    }

    enum EConstDefine
    {
        ECD_SuccessToItem = 0,  // ת�Ƶ����ǵ����ϳɹ�
        ECD_SuccessToEquip,     // ת�Ƶ�װ���ϳɹ�
        ECD_IsNotEquip,         // ����װ����������
        ECD_IsNotMoveStarItem,  // �������ǵ���
        ECD_LessEquipStar,      // ���ǵ����Ǽ�С��װ���Ǽ�
        ECD_LessEquipLevel,     // ���ǵ���С��װ���ȼ�
        ECD_EquipNotStar,       // װ��������Ʒû����,����ת��
        ECD_MoveStarItemError,  // �Ѿ�ת�ƹ������ǵ��߲����������ǲ���
        ECD_LessItemLevel,      // װ��С�����ǵ��ߵȼ�
        ECD_ItemNotStar,        // ���ǵ���û����, ����ת��
    };

    char chResult;      // �������
    char chStarLevel;   // �����ɹ��Ժ�, ��ǰ���Ǽ�
    bool bBound;        // �����ɹ��Ժ�, �Ƿ�Ϊ��װ��
};

struct MsgMoveStarLevelUpReq : public Msg
{
    MsgMoveStarLevelUpReq()
    {
        header.dwType = MSG_MOVESTARLEVELUPREQ;
        header.stLength = sizeof( MsgMoveStarLevelUpReq );
    }

    uint16 ustItemIndex;            // ����ʯ��������
    __int64 n64ItemGuid;            // ����ʯGUID

    uint8 uchItemBagType1;          // ����ʹ�õĲ��ϱ�������
    uint16 ustMaterialIndex1;       // ����ʹ�õĲ��ϵ�����
    __int64 n64MaterialGuid1;
    uint16 ustMaterialCount;        // ʹ�õĲ��ϸ���

};

struct MsgMoveStarLevelUpAck : public Msg
{
    MsgMoveStarLevelUpAck()
    {
        header.dwType = MSG_MOVESTARLEVELUPACK;
        header.stLength = sizeof( MsgMoveStarLevelUpAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_Failed,              // ����ʧ��
        ECD_ErrorMoveStarItem,   // ���������ʯ����
        ECD_ErrorMaterial,       // ����Ĳ���
        ECD_CanNotLevelUp,       // ������ʯ��������
        ECD_NotEnoughMoney,      // û���㹻��Ǯ
        ECD_ErrorMaterialCount,  // ����Ĳ��ϸ���
    };

    uint8 uchResult;

    uint16 ustItemIndex;        // ԭʼ����ʯ������
    __int64 n64ItemGuid;        // ԭʼ����ʯ��GUID

    uint32 dwCurrentMoney;      // ʣ�����Ǯ
    uint16 ustNewItemID;        // ���ɵ��µ�����ʯ��ID
};

// ������װ����
struct MsgSuitElementCheckupReq : public Msg
{
    MsgSuitElementCheckupReq()
    {
        header.dwType = MSG_SUITELEMENTCHECKUPREQ;
        header.stLength = sizeof( MsgSuitElementCheckupReq );
        chOperate = ECD_Checkup;
    }

    enum EConstDefine
    {
        ECD_Checkup = 0,        // ����
        ECD_Clear   = 1,        // ���
    };

    uint8 chOperate;

    uint8 chArmourBagType;      // ��������
    short stArmourIndex;        // ��������
    __int64 nArmourGuid;        // guid

    uint8 chItemBagType;        // �������߱�������
    short stItemIndex;          // �������߱�������
    __int64 nItemGuid;          // ��������guid
};

// �������, 
struct MsgSuitElementCheckupAck : public Msg
{
    MsgSuitElementCheckupAck()
    {
        header.dwType = MSG_SUITELEMENTCHECKUPACK;
        header.stLength = sizeof( MsgSuitElementCheckupAck );
    }

    enum EConstDefine
    {
        ECD_CheckupSuccess = 0,    // �����ɹ�
        ECD_ClearSuccess,       // �����ɹ�
        ECD_NotElement,     // ����������װ
        ECD_ElementAlready, // �Ѿ��������Ĳ��ܼ���
        ECD_NotEnoughMoney, // û���㹻��Ǯ
        ECD_HaveNotElement, // û����������, �������
        ECD_ClearCountLimit, // һ��ֻ�����%d�� ö����Globaldef.h => ClearElementCount
        ECD_NotCheckupItem,  // ���Ǽ������е���Ʒ
        ECD_NotClearItem,    // ����������е���Ʒ
        ECD_LevelError,      // ��Ʒ��װ���ȼ�����
    };

    uint8 chResult;             // ���ؽ��

    uint8 chArmourBagType;      // ��������
    short stArmourIndex;        // ��������
    __int64 nArmourGuid;        // guid

    uint8 chElement;            // �����Ľ��( ��ľˮ�����е�һ�� )  ���ֵ��SCharItem �е� itembase �е�value1 ���� ( value1 | chElement )
    uint32 nLeftMoney;          // ʣ�¶���Ǯ
};

struct MsgSuitElementMoveReq : public Msg
{
    MsgSuitElementMoveReq()
    {
        header.dwType = MSG_SUITELEMENTMOVEREQ;
        header.stLength = sizeof( MsgSuitElementMoveReq );

        stModulusIndex = -1;
    }

    short stSrcArmourIndex;      // Դװ����������
    __int64 n64SrcArmourGuid;    // Դװ��guid

    short stDestArmourIndex;     // Ŀ��װ����������
    __int64 n64DestArmourGuid;   // Ŀ��װ��guid

    uint8 chCheckUpBagType;      // ����ʯ��������
    short stCheckUpIndex;        // ����ʯ��������
    __int64 n64CheckUpGuid;      // ����ʯguid

    uint8 chModulusBagType;       // ���ʵ��߱�������
    short stModulusIndex;         // ���ʵ��߱�������
    __int64 n64ModulusGuid;       // ���ʵ���guid
    uint16 ustModulusCount;       // ���ʵ�������
};

struct MsgSuitElementMoveAck : public Msg
{
    MsgSuitElementMoveAck()
    {
        header.dwType = MSG_SUITELEMENTMOVEACK;
        header.stLength = sizeof( MsgSuitElementMoveAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,           // �ɹ�
        ECD_Failed,                // ʧ��
        ECD_EquipNotExist,         // װ��������
        ECD_NotHaveElement,        // û����������, ����ת��
        ECD_NotElement,            // ����������װ
        ECD_CanEquipIndexError,    // ����װ��װ����λ��һ��, ����ת��
        ECD_EquipLevelError,       // ����װ���ȼ����̫��( ������50->70װ����ת�� )
        ECD_ErrorElementItem,      // ��������м���ʯ
        ECD_ErrorElementItemLevel, // ��������м���ʯ�ȼ�
        ECD_NotEnoughMoney,        // û���㹻��Ǯ
        ECD_ErrorModulusItem,      // ����ĸ��ʼӳɲ���
        ECD_ErrorModulusItemCount, // ����ĸ��ʼӳɲ�������
    };

    uint8 uchResult;               // ���ؽ�� ( �ɹ��Ժ�, ת��Դ���������Ժ������ȼ� ��Ŀ��װ���� , ʧ��ʱ, ֻ���Դװ�� )
    
    uint32 dwCurrentMoney;         // ��ǰ��ʣ����Ǯ
    short stSrcArmourIndex;        // Դװ����������
    __int64 n64SrcArmourGuid;      // Դװ��guid
                                 
    short stDestArmourIndex;       // Ŀ��װ����������
    __int64 n64DestArmourGuid;     // Ŀ��װ��guid
};


//struct MsgMoneyItemExchangeReq : public Msg
//{ // ʵ��һ�
//    MsgMoneyItemExchangeReq()
//    {
//        header.dwType   = MSG_MONEYITEMEXCHANGEREQ;
//        header.stLength = sizeof( MsgMoneyItemExchangeReq );
//        index    = 0;
//        itemguid = 0;
//        memset( linkman, 0, sizeof(linkman));
//        memset( telephone, 0, sizeof(telephone));
//        memset( email, 0, sizeof(email));
//        memset( identityCard, 0, sizeof(identityCard));
//    }
//
//    uint16  index;
//    __int64 itemguid;
//    int8    linkman[17];
//    int8    telephone[13];
//    int8    email[50];
//    int8    identityCard[19];
//};
//
//struct MsgMoneyItemExchangeAck : public Msg
//{ // ʵ��һ�
//    MsgMoneyItemExchangeAck()
//    {
//        header.dwType   = MSG_MONEYITEMEXCHANGEACK;
//        header.stLength = sizeof( MsgMoneyItemExchangeAck );        
//    }
//
//    uint32  result;
//    uint16  index;
//    uint16  itemId;
//    __int64 itemguid;
//    uint16  count;
//};

struct MsgTellRemoveTimeLimitItem : public Msg      // [�ṹû��]
{
    MsgTellRemoveTimeLimitItem()
    {
        header.dwType   = MSG_TELLREMOVETIMELIMITITEM;
        header.stLength = sizeof( MsgTellRemoveTimeLimitItem ) - sizeof( szItemName ); 
        nCount = 0;
        memset( szItemName, 0, sizeof( szItemName ) );
    }

    enum EConstDefine
    {
        ECD_MaxCount = 20,
    };

    int nCount;
    char szItemName[ECD_MaxCount][41];

    void AddItemName( const char* szName )
    {
        if ( szName == NULL || *szName == 0 )
        { return; }

        if ( nCount >= ECD_MaxCount )
        { return; }

        strncpy_s( szItemName[nCount], sizeof( szItemName[nCount] ), szName, sizeof( szItemName[nCount] ) - 1 );
        header.stLength += sizeof( szItemName[nCount] );
        ++nCount;
    }

    void Reset()
    {
        header.stLength = sizeof( MsgTellRemoveTimeLimitItem ) - sizeof( szItemName ); 
        nCount = 0;
        memset( szItemName, 0, sizeof( szItemName ) );
    }
};

// �ͻ�����������
struct MsgEquipUpgradeReq : public Msg
{
    MsgEquipUpgradeReq()
    {
        header.dwType = MSG_EQUIPUPGRADEREQ;
        header.stLength = sizeof( MsgEquipUpgradeReq ) - sizeof( xMaterialID );
        ustCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 10,
    };

    uint16 ustEquipIndex;            // ԭʼװ���ı�������
    __int64 nEquipGuid;              // ԭʼװ����guid
    
    uint16 ustUpToEquipID;           // ���׵�װ��ID    

    uint16 ustCount;                 // ���ϵ�����
    uint16 xMaterialID[ECD_MaxCount];  // �����õ������в���

    void AddMaterial( uint16 ustID )       // �ͻ������һ������,����������� ( ����ʹ�õĲ��Ͽ��Բ��÷��͹��� )
    {
        if ( ustCount >= ECD_MaxCount )
        { return; }

        xMaterialID[ustCount] = ustID;

        ++ustCount;
        header.stLength += sizeof( uint16 );
    }
};

struct MsgEquipUpgradeAck : public Msg
{
    MsgEquipUpgradeAck()
    {
        header.dwType = MSG_EQUIPUPGRADEACK;
        header.stLength = sizeof( MsgEquipUpgradeAck );

        chResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // �ɹ�
        ECD_ErrorEquip,     // �����װ����������
        ECD_CanNotUpgrade,  // �������׵���װ��
        ECD_LackMaterial,   // ȱ�ٲ���
        ECD_ErrorMaterial,  // ����Ĳ���
        ECD_NotEnoughMoney, // û���㹻��Ǯ
        ECD_PackageFull,    // ��������
        ECD_IsLocked,       // ��������
        ECD_Unkown,
    };

    uint8 chResult;                                 // ���ؽ��, �ɹ��Ժ�,������ɾ�����Ϻ�ԭʼװ��,������װ��
    __int64 nNewEquipGuid;                          // ��װ����GUID, ��normal�������ҵ�����װ��,���渽��������
    bool bIsSoulBounded;                            // ���׺��Ƿ��
    uint16 ustRand[SCharItem::EConstDefine_BaseRandMaxCount];      // ���׺� װ�������� memcpy_s ����װ����equipdata.baseRands ����
    uint32 nElemenet;                               // ���׺����������     ֱ�Ӹ�ֵ��itembaseinfo��value1
};

// ��װ��������, ����������װ��������װ
struct MsgSuitLevelUpReq : public Msg
{
    MsgSuitLevelUpReq()
    {
        header.dwType = MSG_SUITLEVELUPREQ;
        header.stLength = sizeof( MsgSuitLevelUpReq );
        memset( xItemInfo, 0, sizeof( xItemInfo ) );
    }
    enum EConstDefine
    {
        ECD_ItemCount = 3,

        ECD_SkillSuitLevelUp = 0,    // ������װ��������
        ECD_ElementSuitLevelUp = 1,  // ������װ�ᴿ����
    };

    struct ItemInfo
    {
        uint8 chItemBagType;     // ��������
        uint16 stItemIndex;      // ���ߵ�����
        __int64 nItemGuid;      // ���ߵ�GUID
    };

    uint8 chOperate;            // ��������

    uint16 stEquipIndex;        // ��ͨ������װ��������
    __int64 nEquipGuid;         // װ��GUID

    ItemInfo xItemInfo[ECD_ItemCount]; // ������װ����ʹ��1����װ��������, ������װ�ᴿʹ��3����������( ��1�����ᴿ���� ��2�������м���ʯ, ��3���ǹ�ѫ�������� )
};

struct MsgSuitLevelUpAck : public Msg
{
    MsgSuitLevelUpAck()
    {
        header.dwType = MSG_SUITLEVELUPACK;
        header.stLength = sizeof( MsgSuitLevelUpAck );
        stAttriID = InvalidLogicNumber; 
    }

    enum EConstDefine
    {
        ECD_SuccessSkillSuit = 0,  // ������װ�����ɹ�
        ECD_SuccessElementSuit,    // ������װ�����ɹ�
        ECD_CheckUpFailed,         // ��װ����ʧ��
        ECD_NotSuitEquip,          // ������װװ��
        ECD_NotSkillSuitEquip,     // ���Ǽ�����װװ��
        ECD_NotElementuitEquip,    // ����������װװ��
        ECD_ErrorCheckUpItem,      // ����ĵ���
        ECD_NotCheckUpItem,        // û�е���
        ECD_ErrorItemLevel,        // ���ߵĵȼ�����
        ECD_NotEnoughMoney,        // û���㹻��Ǯ
        ECD_AlreadMaxLevel,        // �Ѿ������ȼ���
        ECD_Unkown,
    };

    uint8 uchResult;

    uint32 nLeftMoney;  // ʣ�����Ǯ
    uint32 nValue;      // �ɹ��Ժ�, ���ֱֵ�Ӹ���itembaseinfo �����value1
    unsigned short stAttriID;    // ������װ�����ɹ��Ժ�, ���ӵ����Ե�ID, ����equipdata��specials��Ӧλ��, �� e_SkillSuitIndex ���� ( ������װ�����Ҫ�� )
};

// ��װת������, ����������װ��������װ
struct MsgSuitChangeReq : public Msg
{
    MsgSuitChangeReq()
    {
        header.dwType = MSG_SUITCHANGEREQ;
        header.stLength = sizeof( MsgSuitChangeReq );
    }

    enum EConstDefine
    {
        ECD_ItemCount = 2,

        ECD_SkillSuitChange = 0,    // ������װת������
        ECD_ElementSuitChange = 1,  // ������װת������
    };

    struct ItemInfo
    {
        uint8 chItemBagType;     // ��������
        uint16 stItemIndex;      // ���ߵ�����
        __int64 nItemGuid;      // ���ߵ�GUID
    };

    uint8 chOperate;

    uint16 stEquipIndex;                // ��ͨ������װ��������
    __int64 nEquipGuid;                 // װ��GUID

    ItemInfo xItemInfo[ECD_ItemCount];  // ��������, ������װת��( ��һ����ת������, ��2���ǹ�ѫ�������� ), ������װת�� ( ��һ����ת������, ��2�������м���ʯ )
};

struct MsgSuitChangeAck : public Msg
{
    MsgSuitChangeAck()
    {
        header.dwType = MSG_SUITCHANGEACK;
        header.stLength = sizeof( MsgSuitChangeAck );
    }

    enum EConstDefine
    {
        ECD_SuccessChagneSkillSuit = 0,  // ������װת���ɹ�
        ECD_SuccessChagneElementSuit,    // ������װת���ɹ�
        ECD_ChangeFailed,                // ��װת��ʧ��
        ECD_NotSuitEquip,                // ������װװ��
        ECD_NotSkillSuitEquip,           // ���Ǽ�����װװ��
        ECD_NotElementuitEquip,          // ����������װװ��
        ECD_NotCheckUpItem,              // û�е���
        ECD_ErrorCheckUpItem,            // �����ת������
        ECD_ErrorMaterialItem,           // ����Ĺ�ѫ����
        ECD_NotEnoughMoney,              // û���㹻��Ǯ
        ECD_LessEquipLevel,              // С��װ���ȼ�
        ECD_LessSuitLevel,               // ��װ�����ȼ�����, ����ת��
        ECD_LessItemLevel,               // ת�����ߵȼ�����, ����ת��
        ECD_Unkown,
    };

    uint8 uchResult;
    uint32 nLeftMoney;  // ʣ�����Ǯ
    uint32 nValue;      // ���������װת���ɹ��Ժ�, ���ֵ���µ�װ��ItemID( װ����itembaseinfo.ustItemID = nValue ) , ���������װת���ɹ��Ժ�, ���ֵ���µ�����Ԫ��( ֱ�Ӹ���itembaseinfo.value1  = nValue )
};

struct MsgOnLineRewardReq : public Msg
{
    MsgOnLineRewardReq()
    {
        header.dwType = MSG_ONLINEREWARDREQ;
        header.stLength = sizeof( MsgOnLineRewardReq );
    }

    uint8 nIndex;     // �ڼ��εĽ���
};

struct MsgOnLineRewardAck : public Msg
{
    MsgOnLineRewardAck()
    {
        header.dwType = MSG_ONLINEREWARDACK;
        header.stLength = sizeof( MsgOnLineRewardAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // �ɹ���
        ECD_TimeLess,       // ����ʱ�䲻��
        ECD_Already,        // �Ѿ�����˲�����
        ECD_NormalPageFull,       // ��������
		EDC_MaterialPageFull,
		EDC_TaskBagFull,
        ECD_NotReward,      // û���������
    };

    uint8 uchResult;
    uint8 nIndex;     // �ڼ��εĽ��� �ɹ��Ժ�ͻ����Լ�����BitValue::SetBitValue���� SCharLiveInfo::dwRewardItemInfo��ֵ
};

struct MsgBuyBackItemReq : public Msg
{
    MsgBuyBackItemReq()
    {
        header.dwType = MSG_BUYBACKITEMREQ;
        header.stLength = sizeof( MsgBuyBackItemReq );
    }

    uint8 uchIndex;         // ����
    __int64 n64Guid;        // guid
};

struct MsgBuyBackItemAck : public Msg
{
    MsgBuyBackItemAck()
    {
        header.dwType = MSG_BUYBACKITEMACK;
        header.stLength = sizeof( MsgBuyBackItemAck );
        uchResult = Success;   
    }

    enum EConstDefine
    {
        Success = 0,    // �ɹ�
        PackError,      // �ͻ��˻ع������д�   �ͻ����յ�������� ����һ�� MsgBuyBackItemListReq ��Ϣ�������������ˢһ�»ع���Ʒ�б�
        PackFull,       // ��������
        NotEnoughMoney, // û���㹻��Ǯ
    };

    uint8 uchResult;                // ���ؽ�� ��ɹ��� �ͻ���ɾ���ع���������Ӧ����Ʒ
    uint8 uchBuyBackPackIndex;      // ����
    __int64 n64BuyBackPackGuid;     // guid

    uint16 ustBagIndex;             // ���ڱ���������
    uint32 nLeftMoney;              // ʣ�����Ǯ
};

struct MsgBuyBackItemListReq : public Msg
{
    MsgBuyBackItemListReq()
    {
        header.dwType = MSG_BUYBACKITEMLISTREQ;
        header.stLength = sizeof( MsgBuyBackItemListReq );
    }
};

// �ع���Ʒ�б�
struct MsgBuyBackItemListAck : public Msg
{
    MsgBuyBackItemListAck()
    {
        header.dwType = MSG_BUYBACKITEMLISTACK;
        header.stLength = sizeof( MsgBuyBackItemListAck ) - sizeof( xItemList );
        nCount = 0;
    }

    enum EConstDefine
    {
        MaxItemCount = 20,
    };

    int nCount;
    SCharItem xItemList[MaxItemCount];

    void CalcLength()
    {
        header.stLength = sizeof( MsgBuyBackItemListAck ) - ( MaxItemCount - nCount ) * sizeof ( SCharItem );
    }
};

struct MsgChangeNameReq : public Msg
{
    MsgChangeNameReq()
    {
        header.dwType = MSG_CHANGENAMEREQ;
        header.stLength = sizeof( MsgChangeNameReq );
        memset( name, 0, sizeof(name) );
    }
    int8 name[dr_MaxPlayerName];
};

// ��ʾ��̨�ı�������
struct MsgShowBattleSignUpDlg : public Msg
{
    MsgShowBattleSignUpDlg()
    {
        header.dwType = MSG_SHOWBATTLESIGNUPDLG;
        header.stLength = sizeof( *this );
    }

    enum EConstDefine
    {
        eInfoLengthMax    = 256,

        ShowType_Player = 1,    // ��� 1 v 1 ��̨
        ShowType_Team   = 2,    // ���� 1 v 1 ��̨
        ShowType_Guild  = 3,    // ���� 1 v 1 ��̨

        MaxCount = 10,
    };

    struct SignUpInfo   // ��̨�ı�����Ϣ
    {
        SignUpInfo() : ustMapID( ErrorUnsignedShortID ), ustLevel( 0 ), ustCount( 0 ), ustMaxCount( 0 ), nSignUpLeftTime( 0 ) {}

        uint16 ustMapID;            // ��̨��ͼ
        uint16 ustLevel;            // ��̨�ȼ�
        uint32 nSignUpLeftTime;     // ����ʣ��ʱ�� ( ��λ : �� )
        uint16 ustCount;            // ��ǰ��������
        uint16 ustMaxCount;         // �������ı�������
    };

    GameObjectId stNpcId;                  // npcid
    char    szInfo[eInfoLengthMax];      // ��ʾ����
    uint8 uchShowType;                   // ��̨������
    SignUpInfo xSignUpInfo[MaxCount];    // ���ustMapIDΪ-1, ����ѭ��
};

// ��������̨��
struct MsgBattleSignUpReq : public Msg
{
    MsgBattleSignUpReq()
    {
        header.dwType = MSG_BATTLESIGNUPREQ;
        header.stLength = sizeof( *this );
    }

    uint8 ustType;          // ��̨������ 1 = ����  2 = ����, 3 = ����
    uint16 ustMapID;        // ��������ս����ͼid( Ԥ�� �Ժ�Ҳ��Ҫ�� )
    uint16 ustLevel;        // ����������̨�ȼ�
};

struct MsgBattleSignUpAck : public Msg
{
    MsgBattleSignUpAck()
    {
        header.dwType = MSG_BATTLESIGNUPACK;
        header.stLength = sizeof( *this );
        uchResult = Success;
    }

    enum EConstDefine
    {
        Success        = 0,      // �����ɹ�
        ErrorTime      = 1,      // ����ʱ��δ��
        AlreadySignUp  = 2,      // �Ѿ�������
        SignUpFull     = 3,      // ���������Ѿ�����
        BattleClosed   = 4,      // ս���Ѿ��ر���
        SignUpLimit    = 5,      // ÿ��ֻ�ܲμ�3����̨��
        LevelLimit     = 6,      // �ȼ�����

        MustHaveTeam   = 7,      // �����ж�����ܱ���
        MustTeamHeader = 8,      // �����Ƕӳ�
    };

    uint8 uchResult;        // ���صĽ��, �ɹ��Ļ�, ֱ�Ӵ���ȴ���ͼ
    uint8 uchType;          // ��̨������ 1 = ����  2 = ����, 3 = ����
};

// ֪ͨ�ͻ���, ��ǰ�μӵ���̨��ұ���������
struct MsgTellBattleSignUpCount : public Msg
{
    MsgTellBattleSignUpCount()
    {
        header.dwType = MSG_TELLBATTLESIGNUPCOUNT;
        header.stLength = sizeof( *this );

        nStartLeftTime = 0;
    }

    uint32 nStartLeftTime;   // ս����ʼ��ʣ��ʱ��

    uint8 uchType;          // ��̨������ 1 = ����  2 = ����, 3 = ����
    uint16 ustMapID;         // ĳ����̨
    uint16 ustCount;         // �������
};

struct MsgTellBattleSignUpInfo : public Msg
{
    MsgTellBattleSignUpInfo()
    {
        header.dwType = MSG_TELLBATTLESIGNUPINFO;
        nCount = 0;
        header.stLength = sizeof( MsgTellBattleSignUpInfo ) - sizeof( xTeamInfo );
    }

    enum EConstDefine
    {
        MaxCount = 100,
    };

    struct TeamInfo
    {
        uint32 dwTeamID;
        char szName[dr_MaxPlayerName];
    };

    uint8 uchType;           // ��̨������ 1 = ����  2 = ����, 3 = ����

    int nCount;
    TeamInfo xTeamInfo[ MaxCount ];
    void AddTeamInfo( uint32 dwTeamID, const char* szValue )
    {
        if ( nCount >= MaxCount )
        { return; }

        xTeamInfo[nCount].dwTeamID = dwTeamID;
        strncpy_s( xTeamInfo[nCount].szName, dr_MaxPlayerName, szValue, dr_MaxPlayerName - 1 );

        ++nCount;
        header.stLength += sizeof( TeamInfo );
    }
};

// �ͻ�����������Ҫ�ȴ����ʱ��
struct MsgQueryBattleSignUpTimeReq : public Msg
{
    MsgQueryBattleSignUpTimeReq()
    {
        header.dwType = MSG_QUERYBATTLESIGNUPTIMEREQ;
        header.stLength = sizeof( MsgQueryBattleSignUpTimeReq );
    }

    uint8 uchType;           // ��̨������ 1 = ����  2 = ����, 3 = ����
    uint16 ustMapID;
    bool bIsPassSignTime;    // true = �Ƿ���˱���ʱ��  false = �Ƿ��˱���ʱ��
};

struct MsgQueryBattleSignUpTimeAck : public Msg
{
    MsgQueryBattleSignUpTimeAck()
    {
        header.dwType = MSG_QUERYBATTLESIGNUPTIMEACK;
        header.stLength = sizeof( MsgQueryBattleSignUpTimeAck );
        bIsAlreadlySignUp = false;
    }

    uint8 uchType;           // ��̨������ 1 = ����  2 = ����, 3 = ����
    uint16 ustMapID;
    bool bIsAlreadlySignUp;     // �Ƿ��Ѿ��ڱ����׶���
    uint32 dwLeftTime;      // �Ѿ��Ǳ����׶�, ���ֵ�Ǳ���ʣ��ʱ�� ������ ���ж���ʱ����ܱ���
};

struct MsgQueryBattleTeamInfoReq : public Msg
{
    MsgQueryBattleTeamInfoReq()
    {
        header.dwType = MSG_QUERYBATTLETEAMINFOREQ;
        header.stLength = sizeof( MsgQueryBattleTeamInfoReq );
    }

    uint16 ustMapID;         // ĳ����̨
    uint32 dwTeamID;        // ��Ҫ����Ķ���ID
};

struct MsgQueryBattleTeamInfoAck : public Msg
{
    MsgQueryBattleTeamInfoAck()
    {
        header.dwType = MSG_QUERYBATTLETEAMINFOACK;
        header.stLength = sizeof( MsgQueryBattleTeamInfoAck ) - sizeof( xMemberInfo );
        nCount = 0;
    }

    struct MemberInfo 
    {
        char szName[dr_MaxPlayerName];           // ����
        uint8 uchProfession;                     // ְҵ
        uint16 ustLevel;                         // �ȼ�
    };

    int nCount;
    MemberInfo xMemberInfo[TeamMaxManipleMember];

    void AddMemberInfo( MemberInfo& xInfo )
    {
        if ( nCount >= TeamMaxManipleMember )
        { return; }

        xMemberInfo[nCount] = xInfo;
        ++nCount;
        header.stLength += sizeof( MemberInfo );
    }
};

struct MsgEnterTeamBattleReq : public Msg
{
    MsgEnterTeamBattleReq()
    {
        header.dwType = MSG_ENTERTEAMBATTLEREQ;
        header.stLength = sizeof( MsgEnterTeamBattleReq );
    }

    uint32 dwMapID;     // Ҫ����ĵ�ͼ
};

struct MsgEnterTeamBattleAck : public Msg
{
    MsgEnterTeamBattleAck()
    {
        header.dwType = MSG_ENTERTEAMBATTLEACK;
        header.stLength = sizeof( MsgEnterTeamBattleAck );
    }

    bool bEnterStage;           // �Ƿ����
};

struct MsgLeaveBattleReq : public Msg
{
    MsgLeaveBattleReq()
    {
        header.dwType = MSG_LEAVEBATTLEREQ;
        header.stLength = sizeof( MsgLeaveBattleReq );
    }
    
    uint8 uchType;           // ��̨������ 1 = ����  2 = ����, 3 = ����
};

// ֪ͨ�ͻ���, ս���ɼ�
struct MsgTellBattleRecord : public Msg
{
    MsgTellBattleRecord()
    {
        header.dwType = MSG_TELLBATTLERECORD;
        header.stLength = sizeof( MsgTellBattleRecord );
    }

    enum EConstDefine
    {
        Status_Fighting = 1,    // ս����
        Status_FightEnd = 2,    // ս��������

        MaxTeamCount = 6,
    };

    struct RecordInfo
    {
        RecordInfo() : dwID( 0 ), nIntegral( 0 ), nKillCount( 0 ), nDeathCount( 0 )
        {
            memset( szName, 0, sizeof( szName ) );
        }
        uint32 dwID;
        char szName[dr_MaxPlayerName];

        int nIntegral;      // ����;
        int nKillCount;     // ɱ�˸���
        int nDeathCount;    // ��������
    };

    uint8 uchType;          // ս������
    uint8 uchStatus;        // ս��״̬

    uint32 dwMapID;         // �ͻ����жϴ�mapid, �����������ڿͻ��˲�һ��, ����ʾ
    RecordInfo xRecord[ MaxTeamCount ]; // ս���ɼ�
};

// ��ѯ�������ϸ����
struct MsgQueryTeamRecordReq : public Msg
{
    MsgQueryTeamRecordReq()
    {
        header.dwType = MSG_QUERYTEAMRECORDREQ;
        header.stLength = sizeof( MsgQueryTeamRecordReq );
    }

     uint16 ustMapID; 
};

// �ظ��������ϸ����
struct MsgQueryTeamRecordAck : public Msg
{
    MsgQueryTeamRecordAck()
    {
        header.dwType = MSG_QUERYTEAMRECORDACK;
        header.stLength = sizeof( MsgQueryTeamRecordAck ) - sizeof( xRecord );
        nCount = 0;
    }

    struct RecordInfo
    {
        RecordInfo() : nIntegral( 0 ), nKillCount( 0 ), nDeathCount( 0 )
        {
            memset( szName, 0, sizeof( szName ) );
        }
        char szName[dr_MaxPlayerName];

        int nIntegral;      // ����;
        int nKillCount;     // ɱ�˸���
        int nDeathCount;    // ��������
    };

    int nCount;
    RecordInfo xRecord[ TeamMaxManipleMember ];

    void AddRecord( RecordInfo& xInfo )
    {
        if ( nCount >= TeamMaxManipleMember )
        { return; }

        xRecord[ nCount ] = xInfo;
        ++nCount;

        header.stLength += sizeof( RecordInfo );
    }
};

struct MsgNotifyBattleKillNum: public Msg
{
    MsgNotifyBattleKillNum(): killNum(0), beKillNum(0)
    {
        memset(killer, 0, sizeof(killer));
        memset(beKiller, 0, sizeof(beKiller));
        header.dwType = MSG_NOTIFY_BATTLE_KILLNUM;
        header.stLength = sizeof(MsgNotifyBattleKillNum);
    }
    uint16 killNum;			//ɱ�˴���
    uint16 beKillNum;		//��ɱ�� ��֮ǰ ɱ�˴���
    char killer[dr_MaxPlayerName];//ɱ����
    char beKiller[dr_MaxPlayerName];//��ɱ��
};


struct MsgWallowAbout: public Msg
{
	enum ENotifyType
	{
		ENotifyType_Init        , // ��ʼ��
		ENotifyType_StatusChange, // ״̬�仯
		ENotifyType_TimerNotify , // ��ʱ��ʾ
	};

	MsgWallowAbout()
	{
		header.dwType   = MSG_WALLOWABOUT;
		header.stLength = sizeof( MsgWallowAbout );
		nStatus = 0;
		nOnlineTime = 0;
		nLimitTime = 0;
		nType = ENotifyType_StatusChange;
	}
	uint8  nStatus    ; // ��ǰ������״̬ ֵΪö��AntiAddictionState�е�ֵ
	uint32 nOnlineTime; // ����ʱ��
	uint32 nLimitTime ; // ����ʱ��
	uint8  nType      ; // �Ƿ��Ǳ仯
};

struct MsgRegisterServerReq : public Msg
{
    MsgRegisterServerReq()
    {
        header.dwType   = MSG_REGISTERSERVERREQ;
        header.stLength = sizeof( *this );
    }
};

struct MsgRegisterServerAck : public Msg
{
    MsgRegisterServerAck()
    {
        header.dwType   = MSG_REGISTERSERVERACK;
        header.stLength = sizeof( *this );

        memset( szName, 0, sizeof( szName ) );
    }

    uint8 uchParentType;
    uint32 nParentID;

    uint8 uchType;
    uint32 nID;

    char szName[101];        // ����������
    uint16 ustVersion;       // �������汾��ID ����ֻ�ж� VERSION_BUILD
};

struct MsgServerStatusReq : public Msg
{
    MsgServerStatusReq()
    {
        header.dwType   = MSG_SERVERSTATUSREQ;
        header.stLength = sizeof( *this );
    }
};

struct MsgServerStatusAck : public Msg
{
    MsgServerStatusAck()
    {
        header.dwType   = MSG_SERVERSTATUSACK;
        header.stLength = sizeof( *this );
    }

    uint8 uchParentType;
    uint32 nParentID;

    uint8 uchType;
    uint32 nID;
};

struct MsgServerVersionCheckAck : public Msg
{
    MsgServerVersionCheckAck()
    {
        header.dwType   = MSG_SERVERVERSIONCHECKACK;
        header.stLength = sizeof( *this );
    }
};

//// �ͻ�����������2������
//struct MsgSetSecondPasswordReq : public Msg
//{
//    MsgSetSecondPasswordReq()
//    {
//        header.dwType   = MSG_SETSECONDPASSWORDREQ;
//        header.stLength = sizeof( *this );
//        memset( szPassword, 0, sizeof( szPassword ) );
//    }
//
//    char szPassword[ Password::MaxLength + 1 ];
//};
//
//// �ͻ���������������2������
//struct MsgReSetSecondPasswordReq : public Msg
//{
//    MsgReSetSecondPasswordReq()
//    {
//        header.dwType   = MSG_RESETSECONDPASSWORDREQ;
//        header.stLength = sizeof( *this );
//        memset( szOldPassword, 0, sizeof( szOldPassword ) );
//        memset( szNewPassword, 0, sizeof( szNewPassword ) );
//    }
//
//    char szOldPassword[ Password::MaxLength + 1 ];
//    char szNewPassword[ Password::MaxLength + 1 ];
//};
//
//// �޸�������
//struct MsgSetSecondPasswordAck : public Msg
//{
//    MsgSetSecondPasswordAck()
//    {
//        header.dwType   = MSG_SETSECONDPASSWORDACK;
//        header.stLength = sizeof( *this );
//    }
//
//    enum EConstDefine
//    {
//        SetPasswordSuccess = 0,         // ��������ɹ�
//        ReSetPasswordSuccess,           // ��������ɹ�
//        OldPasswordError,               // ԭʼ�������
//        PasswordFormatError,            // �����ʽ����
//        AlreadyHavePassword,            // �Ѿ���������
//        Unknow,
//    };
//
//    uint8 uchResult;     // ���ؽ��
//};
//
//// �ͻ�������ǿ���������
//struct MsgClearSecondPasswordReq : public Msg
//{
//    MsgClearSecondPasswordReq()
//    {
//        header.dwType   = MSG_CLEARSECONDEPASSWORDREQ;
//        header.stLength = sizeof( *this );
//    }
//};
//
//// ��������Ӧǿ���������
//struct MsgClearSecondPasswordAck : public Msg
//{
//    MsgClearSecondPasswordAck()
//    {
//        header.dwType   = MSG_CLEARSECONDEPASSWORDACK;
//        header.stLength = sizeof( *this );
//        uchResult = ClearSuccess;
//    }
//
//    enum EConstDefine
//    {
//        ClearSuccess = 0,       // ǿ�����2����������ɹ�, 3����Զ�����
//    };
//
//    uint8 uchResult;     // ���ؽ��
//};
//
//// ��������������ͻ�����֤2������
//struct MsgCheckSecondPasswordReq : public Msg
//{
//    MsgCheckSecondPasswordReq()
//    {
//        header.dwType   = MSG_CHECKSECONDPASSWORDREQ;
//        header.stLength = sizeof( *this );
//        nClearPasswordLeftTime = 0;
//    };
//
//    enum EConstDefine
//    {
//        OP_InitAction  = 0,     // �������ж�
//        OP_OpenStorage = 1,    // �򿪲ֿ�
//        OP_DelRelation = 2,	   //ɾ������
//		OP_HandleAuction = 3,  //�򿪽𶧽��׽���
//    };
//
//    uint8 uchOperator;      // �ͻ��˰�����ش���������
//
//    uint32 nClearPasswordLeftTime;  // �ֿ�����ǿ�ƽ��ʣ��ʱ��
//};
//
//// �ͻ�������������֤
//struct MsgCheckSecondPasswordAck : public Msg
//{
//    MsgCheckSecondPasswordAck()
//    {
//        header.dwType   = MSG_CHECKSECONDPASSWORDACK;
//        header.stLength = sizeof( *this );
//        memset( szPassword, 0, sizeof( szPassword ) );
//    };
//
//    uint8 uchOperator;      // ��MsgCheckSecondPasswordReq��Ϣ��� uchOperator�ش�
//    char szPassword[ Password::MaxLength + 1 ]; 
//};
//
//// ���벻�ԲŻط���
//struct MsgCheckSecondPasswordResult : public Msg
//{
//    MsgCheckSecondPasswordResult()
//    {
//        header.dwType   = MSG_CHECKSECONDPASSWORDRESULT;
//        header.stLength = sizeof( *this );
//        uchResult = Success;
//    }
//
//    enum EConstDefine
//    {
//        Success = 0,        
//        SecondPasswordError,       // �������2�����벻��ȷ
//        SuccessAndClear,           // ��֤�ɹ�,���ǿ�ƽ�������Ѿ�ȡ��
//    };
//
//    uint8 uchResult;     // ���ؽ��
//};

struct MsgCancelBuff : public Msg
{
    MsgCancelBuff()
    {
        header.dwType   = MSG_CANCELBUFF;
        header.stLength = sizeof( MsgCancelBuff );
        index = 0;
        buffId = 0;
    }
    uint8  index;
    uint16 buffId;
};

struct MsgDelLoginInfo : public Msg
{
    MsgDelLoginInfo()
    {
        header.dwType   = MSG_DELLOGININFO;
        header.stLength = sizeof( MsgDelLoginInfo );
        //memset( szSessionKey, 0, sizeof(szSessionKey));
    }

    uint32 accountId;
    //char   szSessionKey[40+1];
	__int64 SessionKey;
};

struct MsgJiFengShopItemsListReq : public Msg
{ // �����̳ǵ��߲�ѯ
    MsgJiFengShopItemsListReq()
    {
        header.dwType   = MSG_JIFENGSHOPITEMSLISTREQ;
        header.stLength = sizeof( MsgJiFengShopItemsListReq );
    }
};

struct MsgJiFengShopItemsListAck : public Msg
{ // �����̳ǵ����б�
    enum EConstDefine
    {
        ECD_MaxJiFengItemCount = 200,
    };

    MsgJiFengShopItemsListAck()
    {
        isNew = 1;
        Reset();
        header.dwType   = MSG_JIFENGSHOPITEMSLISTACK;
        header.stLength = sizeof( MsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordClient) * ( ECD_MaxJiFengItemCount - count );
    }

    void Reset()
    {
        count = 0;
        memset( items, 0, sizeof(items));        
    }

    bool AddItem( const SJiFengItemRecordClient& itemRecord )
    {
        if ( count >= ECD_MaxJiFengItemCount )
        { return false; }
        
        items[count++] = itemRecord;
        header.stLength = sizeof( MsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordClient) * ( ECD_MaxJiFengItemCount - count );
        return true;
    }

    bool IsFull()
    { return count >= ECD_MaxJiFengItemCount; }

    uint8                   isNew; // �Ƿ����µ�
    uint16                  count;
    SJiFengItemRecordClient items[ ECD_MaxJiFengItemCount ];
};

struct MsgJiFengShopItemsGain : public Msg
{ // �����̳ǵ�����ȡ
    struct SRecordGain
    {
        uint32 id;
        uint32 itemId;
    };

    MsgJiFengShopItemsGain()
    {
        Reset();
        header.dwType   = MSG_JIFENGSHOPITEMSGAIN;
        header.stLength = sizeof( MsgJiFengShopItemsGain ) - sizeof(SRecordGain) * ( gJiFengGainMaxCount - count );
    }

    void Reset()
    {
        count = 0;
        memset( record, 0, sizeof(record));
    }

    bool AddRecord( uint32 recordId, uint32 itemId )
    {
        if ( count >= gJiFengGainMaxCount )
        { return false; }

        record[count].id     = recordId;
        record[count].itemId = itemId;

        ++count;
        header.stLength = sizeof( MsgJiFengShopItemsGain ) - sizeof(SRecordGain) * ( gJiFengGainMaxCount - count );
        return true;
    }

    bool IsFull()
    { return count >= gJiFengGainMaxCount; }

    uint16      count;
    SRecordGain record[gJiFengGainMaxCount];
};

struct MsgUpdateTradeShopConfigReq : public Msg
{ // ������̳����ø���
    MsgUpdateTradeShopConfigReq()
    {
        header.dwType   = MSG_TRADESHOPCONFIGREQ;
        header.stLength = sizeof( MsgUpdateTradeShopConfigReq );
    }
};

struct MsgNotifyTradeShopChange : public Msg
{
    MsgNotifyTradeShopChange()
    {
        header.dwType   = MSG_NOTIFYTRADESHOPCONFIGRECHANGE;
        header.stLength = sizeof( MsgNotifyTradeShopChange );
    }
    uint32 timeStamp;
};

struct MsgUpdateTradeShopConfig : public Msg
{ 
    enum EConstDefine
    {
        ECD_ConfigBufferMaxSize = 50 * 1024,
    };

    MsgUpdateTradeShopConfig()
    {
        Reset();
        header.dwType   = MSG_UPDATETRADESHOPCONFIG;
        header.stLength = sizeof( MsgUpdateTradeShopConfig ) - sizeof( buffer );
    }

    void Reset()
    {
        zip = 0;
        bufferSize = 0;
        memset( buffer, 0, sizeof(buffer));
    }

    bool Clone( const uint8* inBuffer, uint32 size, bool bZip  )
    {
        if ( size >= ECD_ConfigBufferMaxSize)
        { return false; }

        zip = bZip;
        bufferSize = size;
        memcpy_s( buffer, ECD_ConfigBufferMaxSize, inBuffer, size );
        header.stLength = sizeof( MsgUpdateTradeShopConfig ) - sizeof( buffer ) + size;
        return true;
    }

    uint8  zip;
    uint32 bufferSize;
    uint8  buffer[ECD_ConfigBufferMaxSize];
};

////////////////////////////////////////////////////////////////////////////////////

struct MsgShutdownServer : public Msg
{
    MsgShutdownServer()
    {
        header.dwType   = MSG_SERVERSHUTDOWN;
        header.stLength = sizeof( MsgShutdownServer );
        nowTime = 0;
        delayTime = 0;
    }

    __time64_t nowTime;
    uint32     delayTime; // ��
};

struct MsgItemComposeReq : public Msg
{
    MsgItemComposeReq()
    {
        header.dwType   = MSG_ITEMCOMPOSEREQ;
        header.stLength = sizeof( MsgItemComposeReq );
        count = 0;
    }

    enum EConstDefine
    {   
        ECD_MaxCount         = 6,
		ECD_PlusItemIndex	 = 5,
        ECD_PrimaryItemIndex = 0,
    };

    struct ComposeItem
    {
        ComposeItem() : uchItemBagType( 0 ), stItemIndex( -1 ), n64ItemGuid( 0 )
        {}
        uint8 uchItemBagType;
        int16 stItemIndex;
        __int64 n64ItemGuid;
    };

    uint8       count;                  // count - 1��λ���Ǹ��ӵĲ���
    ComposeItem xItem[ ECD_MaxCount ];  // 5���ϳ�ԭ���ϼ�һ�����Ӳ���

    bool AddComposeItem( const ComposeItem& item )
    {
        if ( count >= ECD_MaxCount)
        { return false; }
        
        xItem[count++] = item;
        return true;
    }

    bool TestCountLength()
    {   
        if ( count < 1 || count > ECD_MaxCount )
        { return false; }

        uint32 length = sizeof( MsgItemComposeReq ) - sizeof(ComposeItem) * ( ECD_MaxCount - count );
        if ( length != header.stLength )
        { return false; }

        return true;
    }

    // ���������ʹ������� ��ͻ��˼�ʱ�޸�
    // ��Ҫ�Ĳ���
    //uint8   uchMaterialBagType;
    //int16   stMaterialIndex;
    //__int64 n64MaterialGuid;
};

struct MsgItemComposeAck : public Msg
{
    MsgItemComposeAck()
    {
        header.dwType   = MSG_ITEMCOMPOSEACK;
        header.stLength = sizeof( MsgItemComposeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,            // �ɹ�
        ECD_Failed,                 // ʧ��
        ECD_NotEnoughMoney,         // û���㹻��Ǯ
        ECD_ErrorMaterialItem,      // ����Ĳ���
        ECD_ErrorComposeItem,       // ����ĺϳɲ��ϲ���ȷ
        ECD_CanNotCompose,          // ����Ʒ���ܱ��ϳ�
        ECD_ItemPackFull,           // �����Ѿ�����
    };

    uint16 uchResult;
    uint32 dwCurrentMoney;          // ��ǰʣ�����Ǯ
};

// ֪ͨ�������, ĳ�˸�ĳ��ʹ����ĳ����Ʒ( ����Χ�ڿͻ�����ʾ��Ч�� )
struct MsgShowViewUseItemToPlayer : public Msg
{
    MsgShowViewUseItemToPlayer()
    {
        header.dwType   = MSG_SHOWVIEWUSEITEMTOPLAYER;
        header.stLength = sizeof( MsgShowViewUseItemToPlayer );
    }

    GameObjectId stSrcPlayerID;       // ʹ���߶�̬ID
    GameObjectId stDestPlayerID;      // ʹ�ö���
    uint16 ustItemID;
};

// ȫ������, ĳ�˸�ĳ��ʹ����ĳ��Ʒ���ٸ�
struct MsgShowAllUseItemToPlayer : public Msg
{
    MsgShowAllUseItemToPlayer()
    {
        header.dwType   = MSG_SHOWALLUSEITEMTOPLAYER;
        header.stLength = sizeof( MsgShowAllUseItemToPlayer );
    }

    char szSrcPlayerName[dr_MaxPlayerName];     // ʹ����
    char szDestPlayerName[dr_MaxPlayerName];    // ʹ�ö���
    SCharItem xCharItem;
};

struct MsgTellHideStatus : public Msg
{
    MsgTellHideStatus()
    {
        header.dwType   = MSG_TELLHIDESTATUS;
        header.stLength = sizeof( MsgTellHideStatus );
    }
    
    GameObjectId stID;    // �����ID
    bool bShow;         // true = ��ʾ  false = ����
};

struct MsgMountPotential : public Msg
{
    MsgMountPotential()
    {
        header.dwType   = MSG_MOUNTPOTENTIAL;
        header.stLength = sizeof( MsgMountPotential );
    }

    uint8 index ;       //���������±�
    int64 guid  ;       //����guid
    int16 value[EBaseAttr_MaxSize];     //�����Ǳ����  
};

struct MsgMountBreed : public Msg
{
    MsgMountBreed()
    {
        header.dwType   = MSG_MOUNTBREED;
        header.stLength = sizeof( MsgMountBreed );
    }

    int64 masterGuid ;       //������Guid
    int64 assistantGuid ;    //������Guid
};

struct MsgMountAckBreed : public Msg
{
    MsgMountAckBreed()
    {
        header.dwType   = MSG_MOUNTACKBREED;
        header.stLength = sizeof( MsgMountAckBreed );
    }
};

struct MsgSetOfflineHook : public Msg
{
    MsgSetOfflineHook()
    {
        header.dwType   = MSG_SETOFFLINEHOOK;
        header.stLength = sizeof( MsgSetOfflineHook );
    }

    bool bSetOfflineHook;   //�Ƿ����߹һ�
};

struct MsgAckOfflineHook : public Msg
{
    MsgAckOfflineHook()
    {
        header.dwType   = MSG_ACKOFFLINEHOOK;
        header.stLength = sizeof( MsgAckOfflineHook );
    }

    bool bIsOfflineHook;   //�Ƿ����߹һ�
};

struct MsgGetOfflineHookExp : public Msg
{
    MsgGetOfflineHookExp()
    {
        header.dwType   = MSG_GETOFFLINEHOOKEXP;
        header.stLength = sizeof( MsgGetOfflineHookExp );
    }

    uint8 nHookLevel;   //��ȡ����
};

struct MsgTellServerExpModulus : public Msg
{
    MsgTellServerExpModulus()
    {
        header.dwType   = MSG_TELLSERVEREXPMODULUS;
        header.stLength = sizeof( MsgTellServerExpModulus );
    }

    int nExpModulus;        // ���鱶��( 100Ϊ��λ )     ��Ӧ�ִ�9074
    int nSkillExpModulus;   // ���ܾ��鱶��( 100Ϊ��λ ) ��Ӧ�ִ�9075
};

struct MsgEquipMaintainAck : public MsgBaseIntensifyEquip
{
    MsgEquipMaintainAck()
    {
        header.dwType = MSG_EQUIPMAINTAINACK;
        header.stLength = sizeof( MsgEquipMaintainAck ) - 2 * sizeof( SCharItem )  ;
    }
    
    uint16    nTargetBagIndex ;
    uint16    nSourceBagIndex ;

    SCharItem targetEquip   ;   // Ŀ��װ��
    SCharItem sourceEquip   ;   // Դװ��

    void AddTargetCharItem( SCharItem& xItem )
    {
        targetEquip = xItem;
        header.stLength +=  sizeof( SCharItem ) ;
    }

    void AddSourcCharItem( SCharItem& xItem )
    {
        sourceEquip = xItem;
        header.stLength +=  sizeof( SCharItem ) ;
    }
};

struct MsgItemReclaim : public Msg
{
    MsgItemReclaim()
    {
        header.dwType = MSG_ITEMRECLAIM;
        header.stLength = sizeof( MsgItemReclaim );

        nCount  = 0;
        nGuid   = 0;
        nPackIndex   = 0;
        nItemBagType = 0;
    }

    uint8  nItemBagType;
    uint16 nPackIndex;
    int64  nGuid;
    uint16 nCount;
};

struct MsgItemReclaimAck : public Msg
{
    enum EResult
    {
        error_sucess = 0,
        error_reclaim_fail  ,
        error_notfind_item  ,   //û���ҵ�װ��
        error_item_is_lock  ,   //װ������
        error_item_not_equip,   //��Ʒ����װ��
        error_item_not_reclaim, //װ���޷�����
    };

    MsgItemReclaimAck()
    {
        header.dwType = MSG_ITEMRECLAIMACK;
        header.stLength = sizeof( MsgItemReclaimAck );
    }

    uint16 nResult      ;
    uint8  nItemBagType ;
    uint16 nPackIndex   ;
    uint16 nCostType    ;
    uint32 nCostReturn  ;
};

struct MsgItemComposeGem : public Msg
{
	MsgItemComposeGem()
	{
		header.dwType   = MSG_ITEMCOMPOSEGEM;
		header.stLength = sizeof( MsgItemComposeGem );

		composeType = 0;
		nMaterialCount = 0;
		nSelectGemNum = 0;
		memset( materials, 0, sizeof(materials) );
		memset( &composeRune, 0, sizeof(composeRune) );
	}

    enum EConstDefine
    {   
        ECD_MaterialMaxCount = 5,
        ECD_PrimaryItemIndex = 0,
    };

    enum EComposeType
    {
        ECT_GEM         =   0,  // ��ʯ����
        ECT_MATERIAL    =   1,  // ϴʯ���ϳ�
    };

    struct SMaterial
    {
        uint8 nItemBagType  ;
        int16 nItemIndex    ;
        int64 nItemGuid     ;
        uint8 nCount        ;
    };

    uint8       composeType;                            // ����
    uint8       nMaterialCount;                         // ���ϸ���
    SMaterial   materials[ ECD_MaterialMaxCount ];      // ��������
	SMaterial	composeRune;							//��ʯ�ϳɷ�
	uint8		nSelectGemNum;							//ѡ��ı�ʯ����

    bool AddMaterial( const SMaterial& xMaterial )
    {
        if ( nMaterialCount >= ECD_MaterialMaxCount)
        { return false; }

        materials[nMaterialCount++] = xMaterial;
        return true;
    }
};

struct MsgItemComposeGemAck : public Msg
{
    MsgItemComposeGemAck()
    {
        header.dwType   = MSG_ITEMCOMPOSEGEMACK;
        header.stLength = sizeof( MsgItemComposeGemAck ) - sizeof(SCharItem) ;
        nResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,            // �ɹ�
        ECD_Failed,                 // ʧ��
        ECD_NotEnoughMoney,         // û���㹻��Ǯ
        ECD_ErrorMaterialItem,      // ����Ĳ���
        ECD_ErrorComposeItem,       // ����ĺϳɲ��ϲ���ȷ
        ECD_CanNotCompose,          // ����Ʒ���ܱ��ϳ�
        ECD_ItemPackFull,           // �����Ѿ�����
		ECD_ErrorComposeRune,       // ����ĺϳɷ�����ȷ
    };

    uint8  composeType  ; 
    uint8  nResult      ;
    uint8  nItemBagType ;
    uint16 nPackIndex   ;
    SCharItem xCharItem ;

    void AddCharItem(SCharItem item)
    {
        xCharItem = item;
        header.stLength += sizeof(SCharItem);
    }
};

struct MsgZhuJiangCompose : public Msg
{
	MsgZhuJiangCompose()
	{
		header.dwType   = MSG_ZHUJIANGCOMPOSE;
		header.stLength = sizeof( MsgZhuJiangCompose );

		nMaterialCount = 0;
		memset( materials, 0, sizeof(materials) );
		memset( &composeRune, 0, sizeof(composeRune) );
	}

	enum EConstDefine
	{   
		ECD_MaterialMaxCount = 5,
	};

	struct SMaterial
	{
		uint8 nItemBagType  ;
		int16 nItemIndex    ;
		int64 nItemGuid     ;
		uint16 nItemId      ;
		uint8 nItemCount	;
	};

	uint8       nMaterialCount;                         // ���ϸ���
	SMaterial   materials[ ECD_MaterialMaxCount ];      // ������ͼ����
	SMaterial	composeRune;							//����

	bool AddMaterial( const SMaterial& xMaterial )
	{
		if ( nMaterialCount >= ECD_MaterialMaxCount)
		{ return false; }

		materials[nMaterialCount++] = xMaterial;
		return true;
	}
};

struct MsgZhuJiangComposeAck : public Msg
{
	MsgZhuJiangComposeAck()
	{
		header.dwType   = MSG_ZHUJIANGCOMPOSEACK;
		header.stLength = sizeof( MsgZhuJiangComposeAck ) - sizeof(SCharItem) ;
		nResult = ECD_Success;
	}

	enum EConstDefine
	{
		ECD_Success = 0,            // �ɹ�
		ECD_Failed,                 // ʧ��
		ECD_NotEnoughMoney,         // û���㹻��Ǯ
		ECD_ErrorMaterialItem,      // ����Ĳ���
		ECD_ErrorComposeItem,       // ����ĺϳɲ��ϲ���ȷ
		ECD_CanNotCompose,          // ����Ʒ���ܱ��ϳ�
		ECD_ItemPackFull,           // �����Ѿ�����
		ECD_ErrorComposeRune,       // ����ĺϳɷ�����ȷ
	};

	uint8  nResult       ;
	uint8  nItemBagType  ;
	uint16 nPackIndex    ;
	SCharItem xCharItem  ;
	//uint16 nMaterialIndex;

	void AddCharItem(SCharItem item)
	{
		xCharItem = item;
		header.stLength += sizeof(SCharItem);
	}
};

struct MsgReqPressKeySuit : public Msg
{
    MsgReqPressKeySuit()
    {
        header.dwType   = MSG_REQPRESSKEYSUIT ;
        header.stLength = sizeof( MsgReqPressKeySuit ) ;
    }
};

struct MsgAllPressKeySuit : public Msg
{
    MsgAllPressKeySuit()
    {
        header.dwType   = MSG_ALLPRESSKEYSUIT ;
        header.stLength = sizeof( MsgAllPressKeySuit ) ;
    }

    SPressKeySuit xPressKeySuit[MAX_PRESSKEYSUIT_COUNT];    // ����һ����װ��Ϣ
};

struct MsgPressKeySuit : public Msg
{
    MsgPressKeySuit()
    {
        header.dwType   = MSG_PRESSKEYSUIT ;
        header.stLength = sizeof( MsgPressKeySuit ) ;
    }

    uint8 nIndex;       //�ļ���װ
    int64 equipitem   [ EEquipPartType_MaxEquitPart ];      //װ��GUID
};

struct MsgPressKeySuitAck : public Msg
{
    enum EConstDefine
    {
        ECD_Success = 0,            // �ɹ�
        ECD_Failed,                 // ʧ��
        ECD_NotFoundEquip,          // û���ҵ�װ��
    };

    MsgPressKeySuitAck()
    {
        header.dwType   = MSG_PRESSKEYSUITACK ;
        header.stLength = sizeof( MsgPressKeySuitAck ) - EEquipPartType_MaxEquitPart * sizeof(int64) ;

        nResult = ECD_Success;
    }

    uint8 nResult   ;
    uint8 nIndex    ;
    int64 equipitem [ EEquipPartType_MaxEquitPart ];  //װ��GUID

    void AddEquipItem( int64* pEquipItem )
    {
        memcpy(&equipitem, pEquipItem, EEquipPartType_MaxEquitPart);
        header.stLength += EEquipPartType_MaxEquitPart * sizeof(int64);
    }
};

struct MsgPressKeySuitName : public Msg
{
    MsgPressKeySuitName()
    {
        header.dwType   = MSG_PRESSKEYSUITRENAME ;
        header.stLength = sizeof( MsgPressKeySuitName ) ;
    }

    uint8 nIndex;
    char  keySuitName [ dr_MaxPlayerName ];  //��װ����
};

struct MsgPressKeySuitNameAck : public Msg
{
    MsgPressKeySuitNameAck()
    {
        header.dwType   = MSG_PRESSKEYSUITRENAMEACK ;
        header.stLength = sizeof( MsgPressKeySuitNameAck ) ;
    }

    uint8 nIndex;
    char  keySuitName [ dr_MaxPlayerName ];  //��װ����
};

struct MsgEquipPressKeySuit : public Msg
{
    MsgEquipPressKeySuit()
    {
        header.dwType   = MSG_EQUIPPRESSKEYSUIT ;
        header.stLength = sizeof( MsgEquipPressKeySuit ) ;
    }
    
    uint8 nIndex;
};

struct MsgReqAchieveData : public Msg
{
    MsgReqAchieveData()
    {
        header.dwType   = MSG_REQACHIEVEDATA ;
        header.stLength = sizeof( MsgReqAchieveData ) ;
    }
};

struct MsgAllAchieveData : public Msg
{
    MsgAllAchieveData()
    {
        header.dwType   = MSG_ALLACHIEVEDATA ;
        header.stLength = sizeof( MsgAllAchieveData ) ;
    }

    SAchieveData  achieveData;
};


struct MsgUpdateAchieveVar : public Msg
{
    MsgUpdateAchieveVar()
    {
        header.dwType   = MSG_UPDATEACHIEVEVAR ;
        header.stLength = sizeof( MsgUpdateAchieveVar ) ;
    }

    uint16 nValueType;
    uint32 nValue;
};

struct MsgUpdateAchieve : public Msg
{
    MsgUpdateAchieve()
    {
        header.dwType   = MSG_UPDATEACHIEVE ;
        header.stLength = sizeof( MsgUpdateAchieve ) ;
    }

    uint16  nIndex;
    uint32  nAchievePoint;      // �����������еĳɾ͵���
    SCharAchieve xCharAchieve;
};

struct MsgReqAchieveReward : public Msg
{
    MsgReqAchieveReward()
    {
        header.dwType   = MSG_REQACHIEVEREWARD ;
        header.stLength = sizeof( MsgReqAchieveReward ) ;
    }

    uint16  nIndex;
};

struct MsgReqAchieveRewardAck : public Msg
{
    MsgReqAchieveRewardAck()
    {
        header.dwType   = MSG_REQACHIEVEREWARDACK ;
        header.stLength = sizeof( MsgReqAchieveRewardAck ) ;
    }

    uint16  nIndex;
    uint32  nAchievePoint;      // �����������еĳɾ͵���
    SCharAchieve xCharAchieve;
};

struct MsgReqOffNpcShip : public Msg
{
    MsgReqOffNpcShip()
    {
        header.dwType   = MSG_REQOFFNPCSHIP ;
        header.stLength = sizeof( MsgReqOffNpcShip ) ;
    }
};

struct MsgOnOffNpcShip : public Msg
{
    enum EOnOffType
    {
        EOnOffType_On,
        EOnOffType_Off,
    };

    MsgOnOffNpcShip()
    {
        header.dwType   = MSG_ONOFFNPCSHIP ;
        header.stLength = sizeof( MsgOnOffNpcShip ) ;
        npcObjectId = 0;
        type        = EOnOffType_On;
        pos          = 0;
    }
    uint8  type;
	GameObjectId npcObjectId;
    uint8  pos;
};

struct MsgLearnAllSkill : public Msg
{
    MsgLearnAllSkill()
    {
        header.dwType   = MSG_LEARNALLSKILL ;
        header.stLength = sizeof( MsgLearnAllSkill ) ;
    }
};

struct MsgUpdateMountStorage : public Msg
{
    MsgUpdateMountStorage()
    {
        header.dwType = MSG_UPDATEMOUNTSTORAGE;
        header.stLength = sizeof(*this);
    }

    SMountItem  xStorageMounts[STORAGE_MOUNTGRID_MAX];
};

struct MsgMoveStorageMount : public Msg
{
    enum E_MoveType
    {
        Type_StorageToChar = 0  ,
        Type_CharToStorage      ,
        Type_StorageToStorage   
    };

    MsgMoveStorageMount()
    {
        header.dwType   = MSG_MOVESTORAGEMOUNT ;
        header.stLength = sizeof( MsgMoveStorageMount ) ;
    }

    uint8    nMoveType  ;
    uint16   nDstIndex  ;
    uint16   nSrcIndex  ;
    int64    nGuid      ;
};

struct MsgUpdateCharMount : public Msg
{
    MsgUpdateCharMount()
    {
        header.dwType   = MSG_UPDATECHARMOUNT;
        header.stLength = sizeof(*this);
    }

    SMountItem xMounts[ITEM_MOUNT_MAXCOUNT];
};

struct MsgProtectPetPos : public Msg
{
    MsgProtectPetPos()
    {
        header.dwType   = MSG_PROTECTPETPOS;
        header.stLength = sizeof(MsgProtectPetPos);
    }

    GameObjectId      nPetID  ;   // ���͹�ID
    uint32			   nMapID  ;   // ��ͼID 
    D3DXVECTOR3		   pos     ;   // ��ͼλ��
};

struct MsgReqDoubleExp : public Msg
{
    MsgReqDoubleExp()
    {
        header.dwType   = MSG_REQDOUBLEEXP;
        header.stLength = sizeof(MsgReqDoubleExp);
    }
    
    bool  bState; // false Ϊ�ر� ture Ϊ��
};

struct MsgDoubleExpAck : public Msg
{
    MsgDoubleExpAck()
    {
        header.dwType   = MSG_DOUBLEEXPACK;
        header.stLength = sizeof(MsgDoubleExpAck);
    }
    
    bool    bState;
    uint32  nSysDoubleExpTime;      // ϵͳ���͵�˫������ʱ�� ��λ ����
    uint32  nItemDoubleExpTime;     // ����˫������ʱ��       ��λ ����
};

enum EOfflineFightOP
{
    EOfflineFightOP_Begin, // ��ʼ�һ�
    EOfflineFightOP_End  , // �����һ�
};

struct MsgOfflineFightOpReq : public Msg
{
    MsgOfflineFightOpReq()
    {
        header.dwType   = MSG_OFFLINEFIGHTOPREQ;
        header.stLength = sizeof( MsgOfflineFightOpReq );
        op = EOfflineFightOP_End;
    }
    uint8 op;
};

struct MsgOfflineFightOpAck : public Msg
{
    MsgOfflineFightOpAck()
    {
        header.dwType   = MSG_OFFLINEFIGHTOPACK;
        header.stLength = sizeof( MsgOfflineFightOpAck );
        op = EOfflineFightOP_End;
        result = ER_Success;
    }

    uint16 result;
    uint8  op;
};

struct MsgCharAssignPotential : public Msg
{
    MsgCharAssignPotential()
    {
        header.dwType   = MSG_CHARASSIGNPOTENTIAL;
        header.stLength = sizeof(MsgCharAssignPotential);
    }
    
    int16 nValue[EBaseAttr_MaxSize];     //�����Ǳ����  
};

struct MsgCharAssignPotentialAck : public Msg
{
    MsgCharAssignPotentialAck()
    {
        header.dwType   = MSG_CHARASSIGNPOTENTIALACK;
        header.stLength = sizeof(MsgCharAssignPotentialAck);
    }

    uint16 basePotential   ;            //ʣ��Ǳ����
    uint16 nValue[EBaseAttr_MaxSize];   //�����Ǳ����  
};

struct MsgTellLeaveEctype : public Msg
{
    MsgTellLeaveEctype()
    {
        header.dwType   = MSG_TELLLEAVEECTYPE;
        header.stLength = sizeof( MsgTellLeaveEctype );
    }

    int nStringID;
};

struct MsgLearnXinFa : public Msg
{
    MsgLearnXinFa()
    {
        header.dwType   = MSG_LEARNXINFA;
        header.stLength = sizeof( MsgLearnXinFa );
    }
    
    int16  nXinFaID     ;   // �ķ�ID
    uint8  nXinFaLevel  ;   // �ķ��ȼ�
};

struct MsgChangeXinFa : public Msg
{
    enum EOpType
    {
        OT_Add   ,
        OT_Update,
        OT_Delete,
    };

    MsgChangeXinFa()
    {
        header.dwType   = MSG_CHANGEXINFA;
        header.stLength = sizeof( MsgChangeXinFa );
        op              = OT_Add;
        bMessageDialog  = true;
    }

    SCharXinFa    xinfa;
    uint8         op;
    bool          bMessageDialog;   // �Ƿ񵯴���ʾ
    int64         nUnUsedExp;       // ʣ��δʹ�ü��ܾ���
};

struct MsgReqGotOnDrome : public Msg
{
    enum EOperateType
    {
        EOperateType_Request,   // ����
        EOperateType_Invite ,   // ����
    };

    MsgReqGotOnDrome()
    {
        header.dwType   = MSG_REQGOTONDROME ;
        header.stLength = sizeof( MsgReqGotOnDrome ) ;
        driverId        = InvalidGameObjectId;
        riderId         = InvalidGameObjectId;
        type            = EOperateType_Request;
    }

    uint8  type     ;   
    uint16 driverId ;   // ��ʻԱ
    uint16 riderId  ;   // �˿�
};

struct MsgReqGotOnDromeAck : public Msg
{
    enum EOperateType
    {
        EOperateType_Agree  ,   // ͬ��
        EOperateType_Reject ,   // �ܾ�
    };


    MsgReqGotOnDromeAck()
    {
        header.dwType   = MSG_REQGOTONDROMEACK ;
        header.stLength = sizeof( MsgReqGotOnDromeAck ) ;
        driverId        = InvalidGameObjectId;
        riderId         = InvalidGameObjectId;
        type            = EOperateType_Agree;
    }

    uint8  type     ;   
    uint16 driverId ;   // ��ʻԱ
    uint16 riderId  ;   // �˿�
};

struct MsgReqGotOffDrome : public Msg
{
    MsgReqGotOffDrome()
    {
        header.dwType   = MSG_REQGOTOFFDROME ;
        header.stLength = sizeof( MsgReqGotOffDrome ) ;
        driverId        = InvalidGameObjectId;
        riderId         = InvalidGameObjectId;
    }

    uint16 driverId ;   // ��ʻԱ
    uint16 riderId  ;   // �˿�
};

struct MsgGotOnOffDrome : public Msg
{
    enum EOnOffType
    {
        EOnOffType_On   ,
        EOnOffType_Off  ,
        EOnOffType_ForceOff,
    };

    MsgGotOnOffDrome()
    {
        header.dwType   = MSG_GOTONOFFDROME ;
        header.stLength = sizeof( MsgGotOnOffDrome ) ;
        type            = EOnOffType_On;
        driverId        = InvalidGameObjectId;
        riderId         = InvalidGameObjectId;
        pos             = 0;
    }

    uint8		  type     ;   // ����
    GameObjectId  driverId ;   // ��ʻԱ
    GameObjectId  riderId  ;   // �˿�
    uint8		  pos      ;   // λ��
};

struct MsgRiderOffDrome : public Msg
{
    MsgRiderOffDrome()
    {
        header.dwType   = MSG_RIDEROFFDROME ;
        header.stLength = sizeof( MsgRiderOffDrome ) ;
        riderId         = InvalidGameObjectId;
    }

    GameObjectId  riderId  ;   // ������ĳ˿�
	GameObjectId  driverId;    //˾��
};

// �����������
struct MsgReqDoneQuest : public MsgReqScript 
{
    enum EReqDoneQuestConstDefine
    {
        EDoneQuest_CommitItemMax = 4,   //����ύ4����Ʒ 
    };

    MsgReqDoneQuest()
    {
        header.dwType   = MSG_REQDONEQUEST;
        header.stLength = sizeof(MsgReqDoneQuest);
        nQuestId        = 0;
        memset(nGuid, 0, sizeof(int64) * EDoneQuest_CommitItemMax);
    }

    int           nQuestId;
    int64         nGuid[EDoneQuest_CommitItemMax];
};

struct MsgShowSignature : public Msg
{
    MsgShowSignature()
    {
        header.dwType = MSG_SHOWSIGNATURE;
        header.stLength = sizeof(MsgShowSignature);
        showSignature = false;
        memset( szSignature, 0, sizeof( szSignature ) );
    }

    bool showSignature;
    char szSignature[RelationDefine::MaxSignLength];    // ����ǩ��
};

struct MsgPetCompose : public Msg
{
	MsgPetCompose()
    {
        header.dwType = MSG_PETCOMPOSE;
        header.stLength = sizeof( MsgPetCompose );
    };
	__int64	MainPetGuid;
	__int64 SecPetGuid;
};

struct MsgAddUpdatePet : public Msg
{
    enum EOpType
    {
        OT_Add,
        OT_Update,
    };

    MsgAddUpdatePet()
    {
        header.dwType = MSG_ADDUPDATEPET;
        header.stLength = sizeof( MsgAddUpdatePet );
        type = OT_Add;
        source = EPetSource_Other;
    };

    uint8 	  type  ;   // ���� ����
    uint8     source;   // ������Դ
    SPetItem  pet   ;   // 
};

struct MsgAddPetEquip : public Msg
{
    MsgAddPetEquip()
    {
        header.dwType   = MSG_ADDPETEQUIP;
        header.stLength = sizeof( MsgAddPetEquip );
    };

    __int64		PetGuID;//������ID
	__int64		ItemOnlyID;//װ����ΨһID
};

struct MsgRemovePetEquip : public Msg
{
    MsgRemovePetEquip()
    {
        header.dwType   = MSG_REMOVEPETEQUIP;
        header.stLength = sizeof( MsgRemovePetEquip );
    };

    __int64		PetGuID;//������ID
	int			BagIndex;//δָ��Ϊ -1
	__int64		PetEquipOnlyID;
};

struct MsgChangePetName : public Msg
{
    MsgChangePetName()
    {
        header.dwType   = MSG_CHANGEPETNAME;
        header.stLength = sizeof( MsgChangePetName );
    };

    unsigned short index;
    char   szName[dr_MaxPlayerName];
};

struct MsgChangePet : public Msg
{ // ����ı����Ϣ
    enum EOpType
    {
        EOT_Active      ,   // ��ս
        EOT_UnActive    ,   // ��Ϣ
        EOT_Disappear   ,   // ��ʧ
		EOT_CallButNoActive, // �ٻ������ǲ���ս
		EOT_Recall			//�ٻ�
    };

    MsgChangePet()
    {
        header.dwType = MSG_CHANGEPET;
        header.stLength = sizeof(MsgChangePet);
        ucOpType = EOT_Active;
        guid     = 0;
        source   = EDS_Discard;
    }

    union
    {
        int nPetId;
        int nIndex;
    };

    uint8     ucOpType;
    int64     guid    ;
    uint8     source  ;
};

struct MsgPetPotential : public Msg
{
    MsgPetPotential()
    {
        header.dwType   = MSG_PETPOTENTIAL;
        header.stLength = sizeof( MsgPetPotential );
        index = 0;
        guid  = 0;
        memset( value , 0 , sizeof( int16 ) * EBaseAttr_MaxSize );
    }

    uint8 index ;       //���������±�
    int64 guid  ;       //����guid
    int16 value[EBaseAttr_MaxSize];     //�����Ǳ����  
};

struct MsgUseGoodsToPet : public MsgUseGoods
{
    MsgUseGoodsToPet()
    {
        header.dwType = MSG_USEGOODSTOPET;
        header.stLength = sizeof(MsgUseGoodsToPet);
        nPetIndex = 0;
    }

    uint8 nPetIndex; //��������
};

struct MsgPetSavvyUp  : public Msg
{
    MsgPetSavvyUp()
    {
        header.dwType = MSG_PETSAVVYUP;
        header.stLength = sizeof(MsgPetSavvyUp);
        nSrcPetIndex = 0;
        nSrcPetGuid  = 0;
        nDstPetIndex = 0;
        nDstPetGuid  = 0;
    }

    uint8 nSrcPetIndex; // ���ϳ�������
    int64 nSrcPetGuid ; // ���ϳ���GUID
    uint8 nDstPetIndex; // Ŀ���������
    int64 nDstPetGuid ; // Ŀ�����GUID
};

struct MsgPetSavvyUpAck  : public Msg
{
    enum EResult
    {
        ER_Success  ,
        ER_Failed   ,
    };

    MsgPetSavvyUpAck()
    {
        header.dwType = MSG_PETSAVVYUPACK;
        header.stLength = sizeof(MsgPetSavvyUpAck);
    }

    unsigned char index ;
    unsigned char result;
};

struct MsgUpdatePetChar : public Msg
{
    MsgUpdatePetChar()
    {
        header.dwType = MSG_UPDATEPETCHAR;
        header.stLength = sizeof(MsgUpdatePetChar);
        memset( szTitleName, 0, sizeof(szTitleName) );
    }

    uint8   petLevel;
    uint32  hpMax   ;
    int     hp      ;
    char    szTitleName  [dr_MaxPlayerName];
};

struct MsgUpdatePetMode : public Msg
{
    MsgUpdatePetMode()
    {
        header.dwType = MSG_UPDATEPETMODE;
        header.stLength = sizeof(MsgUpdatePetMode);
    }
	uint32	ModeID;
};

struct MsgSetPetMode : public Msg
{
    MsgSetPetMode()
    {
        header.dwType = MSG_SETPETMODE;
        header.stLength = sizeof(MsgSetPetMode);
    }
	__int64 PetGuID;
	uint32	ModeID;
	__int64 EndTime;
};

struct MsgPetBreedReq : public Msg
{
    MsgPetBreedReq()
    {
        header.dwType = MSG_PETBREEDREQ;
        header.stLength = sizeof(MsgPetBreedReq);
    }
};

struct MsgPetBreedReqAck : public Msg
{
    enum EResult
    {
        ER_Success  ,   // ��ʼ��ֳ����
        ER_Failed   ,
        ER_NoTeam   ,   // ��û�д��ڶ����� 
        ER_TeamMember,  // ���Ķ��鳬����2��
        ER_TeamHeader,  // �����Ƕ���Ķӳ�
        ER_TeamRange,   // ���Ѳ����Ա�
        ER_HaveBreed,   // �Ѿ��г����ڷ�ֳ��
    };

    MsgPetBreedReqAck()
    {
        header.dwType = MSG_PETBREEDREQACK;
        header.stLength = sizeof(MsgPetBreedReqAck);
        result = 0;
    }

    unsigned char result;
};

struct MsgPetBreedChoice : public Msg
{
    MsgPetBreedChoice()
    {
        header.dwType = MSG_PETBREEDCHOICE;
        header.stLength = sizeof(MsgPetBreedChoice);
    }

    unsigned char index;    
};

struct MsgPetBreedChoiceAck : public Msg
{
    enum EResult
    {
        ER_Success  ,   
        ER_Failed   ,
    };

    MsgPetBreedChoiceAck()
    {
        header.dwType = MSG_PETBREEDCHOICEACK;
        header.stLength = sizeof(MsgPetBreedChoiceAck);
    }

    unsigned char result;
    SPetItem pet; 
};

struct MsgPetBreedLock : public Msg
{
    MsgPetBreedLock()
    {
        header.dwType = MSG_PETBREEDLOCK;
        header.stLength = sizeof(MsgPetBreedLock);
    }
};

struct MsgPetBreedCancelLock : public Msg
{
    MsgPetBreedCancelLock()
    {
        header.dwType = MSG_PETBREEDCANCELLOCK;
        header.stLength = sizeof(MsgPetBreedCancelLock);
    }
};

struct MsgPetBreedConfirm : public Msg
{
    MsgPetBreedConfirm()
    {
        header.dwType = MSG_PETBREEDCONFIRM;
        header.stLength = sizeof(MsgPetBreedConfirm);
    }
};

struct MsgPetBreedStatus : public Msg
{
    MsgPetBreedStatus()
    {
        header.dwType = MSG_PETBREEDSTATUS;
        header.stLength = sizeof(MsgPetBreedStatus);
    }

    unsigned char status;
};

struct MsgPetBreedCancelReq : public Msg
{
    MsgPetBreedCancelReq()
    {
        header.dwType = MSG_PETBREEDCANCELREQ;
        header.stLength = sizeof(MsgPetBreedCancelReq);
    }
};

struct MsgPetBreedFinish : public Msg
{
    MsgPetBreedFinish()
    {
        header.dwType = MSG_PETBREEDFINISH;
        header.stLength = sizeof(MsgPetBreedFinish);
        nType = 0;
    }

    unsigned char nType;
};

struct MsgPetBreedAcquire : public Msg
{
    MsgPetBreedAcquire()
    {
        header.dwType = MSG_PETBREEDACQUIRE;
        header.stLength = sizeof(MsgPetBreedAcquire);
    }
};

struct MsgPetBreedAcquireAck : public Msg
{
    enum EResult
    {
        ER_Success  ,
        ER_Failed   ,
        ER_NoBreedPet,      // û�з�ֳ����
        ER_Interval ,       // ʱ����δ��
        ER_PetFull  ,       // �������Ѿ���
        ER_PetLost  ,       // �������Ĺ�������
        ER_TeamMember,      // �����Ա����ȷ
        ER_TeamHeader,      // ���Ƕӳ��޷���ȡ
        ER_NeedMoney ,      // ������ȡ��Ҫ����   
        ER_NoMoney   ,      // ��Ǯ�����޷���ȡ
        ER_BreedTime ,      // ���ﷱֳʱ�䵽�˿�ȥ��ȡ
        ER_TargetAcquired,  // �Է�������ȡ�˷�ֳ����
    };

    MsgPetBreedAcquireAck()
    {
        header.dwType = MSG_PETBREEDACQUIREACK;
        header.stLength = sizeof(MsgPetBreedAcquireAck);
        result = ER_Success;
        value  = 0;
    }

    unsigned char result;
    int64         value ;
    SPetItem      pet   ;
    char          szName[ dr_MaxPlayerName ];   // ��������
};

// ���͸��ͻ������󲥷���Ƶ
struct MsgPlayMovieReq : public Msg
{
    MsgPlayMovieReq()
    {
        header.dwType = MSG_PLAYMOVIEREQ;
        header.stLength = sizeof( MsgPlayMovieReq );
    }
    uint16 nMovieId;        // ��ӰID
    DWORD dwPlayTime;       // ����ʱ��
};

// �ͻ��˻�Ӧ�Ƿ���Բ�����Ƶ��
struct MsgPlayMovieAck : public Msg
{
    MsgPlayMovieAck()
    {
        header.dwType = MSG_PLAYMOVIEACK;
        header.stLength = sizeof( MsgPlayMovieAck );
    }

    DWORD dwPlayTime;   // ����ʱ��
};

// ��������״̬�ı�
struct MsgMonsterTypeStatusChange : public Msg
{
    MsgMonsterTypeStatusChange()
    {
        header.dwType = MSG_MONSTERTYPESTATUSCHANGE;
        header.stLength = sizeof( MsgMonsterTypeStatusChange );
    }

    GameObjectId nMonsterID;      // ���ﶯ̬ID
    uint8 nTypeStatus;          // ��ǰ״̬
};

struct MsgSawTalkReq: public Msg
{
    MsgSawTalkReq()
    {
        header.dwType   = MSG_SAWTALKREQ;
        header.stLength = sizeof( MsgSawTalkReq );
        questId = 0;
        talkType = 0;
    }

    uint16 questId;
    uint8  talkType;
};

// �ɾ͹㲥
struct MsgAchieveBroadcast : public Msg
{
    MsgAchieveBroadcast()
    {
        header.dwType = MSG_ACHIEVEBROADCAST;
        header.stLength = sizeof( MsgAchieveBroadcast );
    }

    uint16 usID;						// �ɾ�ID
    char   szName[dr_MaxPlayerName];	// ��óɾ͵����
};

struct MsgStartEvent : public Msg
{
    enum NeedBroadcast
    {
        ENB_NoBroadcast = 0,	// ��Ҫ�㲥
        ENB_Broadcast,			// �㲥
    };

    MsgStartEvent()
    {
        header.dwType = MSG_STARTEVENT;
        header.stLength = sizeof( MsgStartEvent );
    }
    uint16	usEventID;	// �¼�ID
    uint8	ucBroadcast;// �Ƿ�㲥

};

struct MsgEndEventReq : public Msg
{
    MsgEndEventReq()
    {
        header.dwType = MSG_ENDEVENTREQ;
        header.stLength = sizeof( MsgEndEventReq );
    }
};

struct MsgEndEvent : public Msg
{
    MsgEndEvent()
    {
        header.dwType = MSG_ENDEVENT;
        header.stLength = sizeof( MsgEndEvent );
    }
};

struct MsgMailListReq : public Msg
{
    MsgMailListReq()
    {
        header.dwType = MSG_MAILLISTREQ;
        header.stLength = sizeof( MsgMailListReq );
    }
};

struct MsgReqIdentifyData  : public Msg
{
    MsgReqIdentifyData()
    {
        header.dwType = MSG_REQIDENTIFYDATA;
        header.stLength = sizeof( MsgReqIdentifyData );
    }
};

struct MsgAllIdentifyData  : public Msg
{
    MsgAllIdentifyData()
    {
        header.dwType = MSG_ALLIDENTIFYDATA;
        header.stLength = sizeof( MsgAllIdentifyData );
    }

    SIdentifyData    identifyData;  // ͼ������
};

struct MsgUpdatePetIdentify : public Msg
{
    MsgUpdatePetIdentify()
    {
        header.dwType = MSG_UPDATEPETIDENTIFY;
        header.stLength = sizeof( MsgUpdatePetIdentify );
    }

    SPetIdentify petIdentify;   // ����ͼ��
};

struct MsgEquipTalisman:public Msg
{
    MsgEquipTalisman()
    {
        header.dwType = MSG_EQUIPTALISMAN;
        header.stLength = sizeof( *this );
        ustPackIndex = 0;
    }
    unsigned short ustPackIndex;
};

struct MsgEquipTalismanAck:public Msg
{
    enum
    {
        Result_Success = 0      ,
        Result_Failed           ,
        Result_DaoxingNotEnough ,
    };

    MsgEquipTalismanAck()
    {
        header.dwType = MSG_EQUIPTALISMANACK;
        header.stLength = sizeof( *this );
    }

    short stResult;
    unsigned short ustPackIndex;
};

struct MsgUnEquipTalisman : public Msg
{
    MsgUnEquipTalisman()
    {
        header.dwType = MSG_UNEQUIPTALISMAN;
        header.stLength = sizeof( *this );
        stPackIndex = 0;
    }
    uint16 stPackIndex;
};

struct MsgUnEquipTalismanAck : public Msg
{
    enum
    {
        Result_Success = 0      ,
        Result_Failed           ,
    };

    MsgUnEquipTalismanAck()
    {
        header.dwType = MSG_UNEQUIPTALISMANACK;
        header.stLength = sizeof( *this );
        stPackIndex = 0;
    }
    
    uint8  result     ;
    uint16 stPackIndex;
    SCharItem talisman;
};

struct MsgTalismanChange : public Msg
{
    enum
    {
        EOT_Equip   ,
        EOT_UnEquip ,
    };

    MsgTalismanChange()
    {
        header.dwType = MSG_TALISMANCHANGE;
        header.stLength = sizeof( *this );
        opType  = EOT_Equip;
        nItemID = InvalidLogicNumber;
    }

    uint8    opType ;
    uint16   nItemID; 
};

struct MsgPetRegenerate : public Msg
{
    MsgPetRegenerate()
    {
        header.dwType = MSG_PETREGENERATE;
        header.stLength = sizeof( *this );
    }
    
    uint8   index;
    uint16  regenerateTime; // ��λ��
};

//�������һ������֪ͨ�������峤������������������߰���
struct MsgTellClientCanInvite : public Msg
{
	enum
	{
		Guild_Invite,
		Family_Invite,
	};

	MsgTellClientCanInvite()
	{
		header.dwType = MSG_TELLCLIENT_CANINVITE;
		header.stLength = sizeof( MsgTellClientCanInvite );
	}

	uint8						 opType;
	unsigned int			  nPlayerID;
	unsigned int			  nPlayerLv;
	char szPlayerName[dr_MaxPlayerName];

};

struct MsgPetLearnSkill : public Msg
{
    enum ELearnSource  
    {
        ESource_Realize ,   // ��������
        ESource_Item    ,   // ����ѧϰ
    };

    MsgPetLearnSkill()
    {
        header.dwType = MSG_PETLEARNSKILL;
        header.stLength = sizeof( *this );
    }

    uint8   source      ;
    uint8   index       ;
    uint16  skillId     ;
    uint8   skillLevel  ;
    uint16  replaceSkillId      ;
    uint8   replaceSkillLevel   ;
};

struct MsgViewActivePet : public Msg
{
    MsgViewActivePet()
    {
        header.dwType = MSG_VIEWACTIVEPET;
        header.stLength = sizeof( *this );
    }
    
    GameObjectId masterId;  // ����ID
};

struct MsgViewActivePetAck : public Msg
{
    MsgViewActivePetAck()
    {
        header.dwType = MSG_VIEWACTIVEPETACK;
        header.stLength = sizeof( *this );
    }

    GameObjectId masterId;  // ����ID
    SPetItem     pet;       // ����
};

struct MsgUpdateGuideReq : public Msg
{
    MsgUpdateGuideReq()
    {
        header.dwType = MSG_UPDATEGUIDEREQ;
        header.stLength = sizeof( *this );
        nGuidId = 0;
        nState  = EGuideState_UnFinish;
    }
    int16  nGuidId;
    uint8  nState ;
};

struct MsgUpdateGuideAck : public Msg
{
    MsgUpdateGuideAck()
    {
        header.dwType = MSG_UPDATEGUIDEACK;
        header.stLength = sizeof( *this );
        nGuidId = 0;
        nState  = EGuideState_UnFinish;
    }
    int16  nGuidId;
    uint8  nState ;
};

struct MsgScenePlay : public Msg 
{
    MsgScenePlay()
    {
        header.uMsgLevel = level_low;
        header.dwType    = MSG_SCENEPLAY;
        header.stLength  = sizeof(*this);
    }

    short stSceneId;    // ���ų���ID
};

struct MsgBlackScreen : public Msg
{
    MsgBlackScreen()
    {
        header.uMsgLevel = level_low;
        header.dwType    = MSG_BLACKSCREEN;
        header.stLength  = sizeof(*this);
    }

    uint32 dwTime;      // ����ʱ��
};

struct MsgC2GAskBianShen:public Msg
{
	MsgC2GAskBianShen()
	{
		header.dwType = MSG_C2G_ASK_BIANSHEN;
		header.stLength = sizeof(*this);
	}
	uint16 hero_id;
	uint16 nItemIndex;
};

struct MsgG2CReqBianShen:public Msg
{
	enum eResult
	{
		eResult_succ = 0,//�ɹ�
		eResult_fail,//ʧ��
		eResult_NoHero,//����������
		eResult_NoMataril,//���ϲ���
		eResult_NoMoney,//��Ǯ����
		eResult_NoLevel,//�ȼ�����
		eResult_popItemFail,//ɾ����Ʒʧ��
		eResult_diffSex,	//�Ա�ͬ
		eResult_Max
	};

	MsgG2CReqBianShen()
	{
		header.dwType = MSG_G2C_REQ_BIANSHEN;
		header.stLength = sizeof(*this);
	}
	uint16 result;			//������
	uint16 hero_id;			//����ID
	uint16 nItemIndex;		//��Ʒindex
	//SCharDBInfo charInfo;	//���������
};

struct MsgTellHeroAddAttr:public Msg
{
	MsgTellHeroAddAttr()
	{
		header.dwType = MSG_TELLHEROADDATTR;
		header.stLength = sizeof(*this);
	}
	SCharHeroInfo heroAttr;
};

struct MsgC2GReqFLYTOTPHJ:public Msg
{
	MsgC2GReqFLYTOTPHJ()
	{
		header.dwType = MSG_REQ_FLYTOTPHJ;
		header.stLength = sizeof(*this);
	}
	bool in_or_out;//��������˳�̫ƽ�þ�
};
 
struct MsgTellTPHJRank:public Msg
{
	MsgTellTPHJRank()
	{
		header.dwType = MSG_TELLTPHJRANK;
		header.stLength = sizeof(*this);
	}
	char rank;				//̫ƽ�þ��ȼ�
};

// ����������Ϊ�ڳ�
struct MsgChangeToBiaocheReq : public Msg
{
	MsgChangeToBiaocheReq()
	{
		header.dwType = MSG_CHANGE_2_BIAOCHE_REQ;
		header.stLength = sizeof(*this);
	}

	int monsterID;				// �ڳ���monsterID
	//float scale;				// �ڳ������ű�
	//float moveSpeed;			// �ڳ����ƶ��ٶ�
};

// ��ұ����ڳ���֪ͨ
struct MsgChangeToBiaocheAck : public Msg
{
	MsgChangeToBiaocheAck()
	{
		header.dwType = MSG_CHANGE_2_BIAOCHE_ACK;
		header.stLength = sizeof(*this);
	}

	int monsterID;				// �ڳ���monsterID
};

// ���������ڳ��������
struct MsgRestoreFromBiaocheReq : public Msg
{
	MsgRestoreFromBiaocheReq()
	{
		header.dwType = MSG_RESTORE_FROM_BIAOCHE_REQ;
		header.stLength = sizeof(*this);
	}

	//int monsterID;		// �ڳ���monsterID
	//float scale;				// �ڳ������ű�
	//float moveSpeed;			// �ڳ����ƶ��ٶ�
};

struct MsgRestoreFromBiaocheAck : public Msg
{
	MsgRestoreFromBiaocheAck()
	{
		header.dwType = MSG_RESTORE_FROM_BIAOCHE_ACK;
		header.stLength = sizeof(*this);
	}

	//int monsterID;		// �ڳ���monsterID
	//float scale;				// �ڳ������ű�
	//float moveSpeed;			// �ڳ����ƶ��ٶ�
};

struct MsgPlayerPlayAnim : public Msg
{
	enum
	{
		eActionNameLength = 32
	};

	MsgPlayerPlayAnim()
	{
		header.uMsgLevel = level_low;
		header.dwType = MSG_S2C_PlayerPlayAnim;
		header.stLength = sizeof(*this);
	}
	char szActionName[eActionNameLength];
	char szEndActionName[eActionNameLength];
	int  nLoopTimes;
};

struct MsgTellReliveBuff : public Msg
{
	MsgTellReliveBuff()
	{
		header.dwType = MSG_TELLRELIVEBUFF;
		header.stLength = sizeof(*this);
		byBuff = 0;
	}
	BYTE byBuff;
};

//struct MsgGateTellClientReAsk:public Msg
//{
//	MsgGateTellClientReAsk()
//	{
//		header.dwType = MSG_TELLC_REASKGATE;
//		header.stLength = sizeof(*this);
//	}	
//};

struct MsgShowHeroSuit:public Msg
{
	enum eHeroSuitFlag
	{
		eHeroSuitFlag_show = 0,//��ʾ
		eHeroSuitFlag_notshow,//����ʾ
		eHeroSuitFlag_max
	};
	MsgShowHeroSuit()
	{
		header.dwType = MSG_SHOW_HEROSUIT;
		header.stLength = sizeof(*this);
		flag = eHeroSuitFlag_max;
	}
	short flag;
};

struct MsgFIRSTLIMITINFO:public Msg
{
	MsgFIRSTLIMITINFO()
	{
		header.dwType = MSG_REQ_FIRST_LIMITINFO;
		header.stLength = sizeof(*this);
	}
	//SLevelLimitInfo sllinfo;
	short max_lv;
};

struct MsgAckLevelUp:public Msg
{
	MsgAckLevelUp()
	{
		header.dwType = MSG_ACK_LEVELUP;
		header.stLength = sizeof(*this);
	}
};

struct MsgAckActiveLimit:public Msg
{
	MsgAckActiveLimit()
	{
		header.dwType = MSG_ACK_ACTIVELIMIT;
		header.stLength = sizeof(*this);
	}
};

struct MsgAckLimitInfo:public Msg
{
	MsgAckLimitInfo()
	{
		header.dwType = MSG_ACK_LIMITINFO;
		header.stLength = sizeof(*this);
	}
};

struct MsgGS2CLimitDone:public Msg
{
	MsgGS2CLimitDone()
	{
		header.dwType = MSG_GS2C_LIMITDONE;
		header.stLength = sizeof(*this);
	}
};

///////////////////////////////////////
struct MsgLoginAccountInfo:public Msg
{
	enum
	{
		eVersionMax = 20,
		eMacMax		= 64,
		eAccountMax = 128,
		ePwdsMax    = 128,
	};
	MsgLoginAccountInfo()
	{
		header.dwType = MSG_LOGIN_ACCOUNTINFO;
		header.stLength = sizeof(*this);
		
		memset(szFullVersion,0,20);
		memset(szAccount,0,eAccountMax);
		memset(szPwds,0,ePwdsMax);
	}
	char szFullVersion[eVersionMax];
	char szMac[eMacMax];			 // ����������
	char szAccount[eAccountMax];
	char szPwds[ePwdsMax];
	int  nSecondVersion;
	bool isEncryp;                   //�Ƿ����
};


struct MsgFlytoKindom:public Msg
{
	MsgFlytoKindom()
	{
		header.dwType = MSG_REQ_FLYTOKINGDOM;
		header.stLength = sizeof(*this);
	}
	unsigned int map_id;
	float map_x;
	float map_y;
};

struct MsgTransferStar:public Msg
{
	MsgTransferStar()
	{
		header.dwType = MSG_TRANSFER_STAR;
		header.stLength = sizeof(MsgTransferStar);
		memset( &sTargetEquip, 0, sizeof(sTargetEquip) );
		memset( &sSourceEquip, 0, sizeof(sSourceEquip) );
		memset( &sMaterial, 0, sizeof(sMaterial) );
	}

	struct SMaterial
	{
		uint8 nItemBagType  ;
		int16 nItemIndex    ;
		int64 nItemGuid     ;
	};

	SMaterial sTargetEquip; //Ŀ��װ��
	SMaterial sSourceEquip; //Դװ��
	SMaterial sMaterial;	//����
};

struct MsgTransferStarAck:public Msg
{
	MsgTransferStarAck()
	{
		header.dwType = MSG_TRANSFER_STAR_ACK;
		header.stLength = sizeof( MsgTransferStarAck ) - 2 * sizeof( SCharItem )  ;
	}

	enum eResult
	{
		eR_Success,
		eR_Fail,
		eR_DropOne,
		eR_DropTwo,
		eR_DropThree,
	};

	uint16    nTargetBagIndex ;
	uint16    nSourceBagIndex ;

	SCharItem targetEquip   ;   // Ŀ��װ��
	SCharItem sourceEquip   ;   // Դװ��

	uint8	  eresult;

	void AddTargetCharItem( SCharItem& xItem )
	{
		targetEquip = xItem;
		header.stLength +=  sizeof( SCharItem ) ;
	}

	void AddSourcCharItem( SCharItem& xItem )
	{
		sourceEquip = xItem;
		header.stLength +=  sizeof( SCharItem ) ;
	}
};

struct MsgMountStrengthen : public Msg
{
	MsgMountStrengthen()
	{
		header.dwType   = MSG_MOUNT_STRENGTHEN;
		header.stLength = sizeof( MsgMountStrengthen );

		mountIndex = -1;
		mountGuid = 0;
		materialIndex = -1;
		materialGuid = 0;
		protectNum = 0;
	}

	int8 mountIndex ;       //���������±�
	int64 mountGuid  ;       //����guid
	
	int8 materialIndex;		//����Index
	int64 materialGuid;		//����Guid

	uint8 protectNum;		//�����ĵȼ�
};

struct MsgMountStrengthenAck : public Msg
{
	MsgMountStrengthenAck()
	{
		header.dwType   = MSG_MOUNT_STRENGTHEN_ACK;
		header.stLength = sizeof( MsgMountStrengthenAck );

		loselevel = 0;
	};
	enum eResult
	{
		eR_Success,
		eR_Fail,
	};

	uint8 result;

	uint8 loselevel;	//���ĵȼ�
	SMountItem mount;
	bool   IsMoveLevel;
};


struct MsgUnBindEquipReq : public Msg
{
    MsgUnBindEquipReq()
    {
        header.dwType = MSG_UNBINDEQUIPREQ;
        header.stLength = sizeof( MsgUnBindEquipReq );
    }
    __int64 nEquipGuid;     // װ��guid
};
struct MsgUnBindEquipAck : public Msg
{
    MsgUnBindEquipAck()
    {
        header.dwType = MSG_UNBINDEQUIPACK;
        header.stLength = sizeof( MsgUnBindEquipAck );
    }
    __int64 nEquipGuid;     // װ��guid
};

struct MsgProcTimeStepAck : public Msg
{
    MsgProcTimeStepAck()
    {
        header.dwType = MSG_PROCTIMESTEPACK;
        header.stLength = sizeof( MsgProcTimeStepAck );
    }
    uint32 StringID;
	uint32 TimeStep;
};


struct MsgKillPlayerNumAck : public Msg
{
    MsgKillPlayerNumAck()
    {
        header.dwType = MSG_KILLPLAYERNUM;
        header.stLength = sizeof( MsgKillPlayerNumAck );
		nAllKillNum = 0;
		nWeekKillNum =0;
    }
    uint32		nAllKillNum;//��ɱ����
	uint32		nWeekKillNum;//����ɱ����
};
struct MsgConKillPlayerAck : public Msg
{
    MsgConKillPlayerAck()
    {
        header.dwType = MSG_CONKILLPLAYER;
        header.stLength = sizeof( MsgKillPlayerNumAck );
		KillNum = 0;
    }
    uint32			KillNum;
};

struct MsgAskForPresent:public Msg
{
	MsgAskForPresent()
	{
		header.dwType = MSG_ASKFORPRESENT;
		header.stLength = sizeof( MsgAskForPresent );
	}
	char sn[33];
};

struct MsgRepeatedlyPet:public Msg
{
	MsgRepeatedlyPet()
	{
		header.dwType = MSG_REPEATEDLY_PET;
		header.stLength = sizeof( MsgRepeatedlyPet );
	}
	uint16 petType;
};

struct MsgPlatformError:public Msg
{
	MsgPlatformError()
	{
		header.dwType = MSG_PLATFORMERROR;
		header.stLength = sizeof( MsgPlatformError );
	}
	int16 _result;
};


struct MsgMonsterBeLongID:public Msg
{
    MsgMonsterBeLongID()
    {
        header.dwType   = MSG_MONSTERBELONGID;
        header.stLength = sizeof(MsgMonsterBeLongID);

		MonsterID = 0;
		BeLongID = 0;
    }
	uint32 MonsterID;
	uint32 BeLongID;
};

struct MsgMonsterNurtureInfo:public Msg
{
	enum InfoStates
	{
		IS_BuffFiled = 0,
	};
    MsgMonsterNurtureInfo()
    {
        header.dwType   = MSG_MONSTERNURTUREINFO;
        header.stLength = sizeof(MsgMonsterNurtureInfo);
    }
	uint8 InfoID;
};

struct MsgSendMessageEnd: public Msg
{
	MsgSendMessageEnd()
	{
		header.dwType = MSG_SENDMESSAGEEND;
		header.stLength = sizeof(MsgSendMessageEnd);
	}
};

struct MsgChangeMapTimeStepReq : public Msg
{
	MsgChangeMapTimeStepReq()
    {
        header.dwType = MSG_CHANGEMAPTIMESTEPREQ;
        header.stLength = sizeof(MsgChangeMapTimeStepReq);
    }
	bool	IsOpen;//�Ƿ�򿪵���ʱ�� ���߹رյ�ǰ����ʱ��
	uint32	TimeStep;
};//���������л���ͼ�ĵ���ʱ

struct MsgRandAttrReq : public Msg
{
	MsgRandAttrReq()
	{
		header.dwType = MSG_RANDATTRIBUTE_REQ;
		header.stLength = sizeof(MsgTransferStar);
		memset( &sArmour, 0, sizeof(sArmour) );
		memset( &sMaterial, 0, sizeof(sMaterial) );
	}

	struct SMaterial
	{
		uint8 nItemBagType  ;
		int16 nItemIndex    ;
		int64 nItemGuid     ;
	};

	SMaterial sArmour; //Ŀ��װ��
	SMaterial sMaterial;	//����
};

struct MsgRandAttrAck : public Msg
{
	MsgRandAttrAck()
	{
		header.dwType = MSG_RANDATTRIBUTE_ACK;
		header.stLength = sizeof( MsgIntensifyEquip ) - sizeof( SCharItem ) ;
	}

	uint16    nNormalBagIndex ;
	SCharItem item            ; // e_Succeed �� e_Lost �᷵�ص��ߵ����� ,��������������ṹ

	void AddCharItem( SCharItem& xItem )
	{
		item = xItem;
		header.stLength +=  sizeof( SCharItem ) ;
	}
};

struct MsgTellClientLeaveTeam : public Msg
{
    MsgTellClientLeaveTeam()
    {
        header.dwType = MSG_TELLCLIENTLEAVETEAM;
        header.stLength = sizeof (MsgTellClientLeaveTeam);
    }

	uint32 TeamID;
	uint32  TimeStep;
	bool   Result;
};

struct MsgChangePetDuration : public Msg
{
    MsgChangePetDuration()
    {
        header.dwType = MSG_CHANGEPETDURATION;
        header.stLength = sizeof (MsgChangePetDuration);
    }
	
	unsigned int Value;
};

struct MsgTellUseItem : public Msg
{
	MsgTellUseItem()
	{
		header.dwType = MSG_USEITEM;
		header.stLength = sizeof( MsgTellUseItem );

		ustItemId = 0;
	}

	unsigned short ustItemId;
};

struct MsgUpdateCard : public Msg
{
	MsgUpdateCard()
	{
		header.dwType = MSG_UPDATECARD;
		header.stLength = sizeof( MsgUpdateCard );

		stCardID = -1;
		stLevel = -1;
	}

	short stCardID;
	short stLevel;
};

struct MsgCardAchieve : public Msg
{
	MsgCardAchieve()
	{
		header.dwType = MSG_RECARDACHIEVE;
		header.stLength = sizeof( MsgCardAchieve );

		stAchieveId = -1;
	}

	short stAchieveId;
};

struct MsgCardAchieveAck : public Msg
{
	MsgCardAchieveAck()
	{
		header.dwType = MSG_RECARDACHIEVE_ACK;
		header.stLength = sizeof( MsgCardAchieveAck );

		stAchieveId = -1;
	}

	short stAchieveId;
};

struct MsgAskSevenDaysData : public Msg
{
	MsgAskSevenDaysData()
	{
		header.dwType = MSG_ASKSEVENDAYSDATA;
		header.stLength = sizeof( MsgAskSevenDaysData );
	}
};

struct MsgSevenDaysDataAck : public Msg
{
	enum DataLength
	{
		DL_Max = 7,
	};

	MsgSevenDaysDataAck()
	{
		header.dwType = MSG_ASKSEVENDAYSDATA_ACK;
		header.stLength = sizeof( MsgSevenDaysDataAck );

		memset(taskState, 0, sizeof(taskState));
		memset(taskVar, 0, sizeof(taskVar));
	}

	short taskState[DL_Max];
	short taskVar[DL_Max];
};

struct MsgFreshSevenDayState : public Msg
{
	MsgFreshSevenDayState()
	{
		header.dwType = MSG_FRESHSEVENDAYSTATE_VAR;
		header.stLength = sizeof( MsgFreshSevenDayState );

		stateIndex = -1;
		varIndex = -1;
		state = 0;
		var = 0;
	}

	short stateIndex;
	short varIndex;
	short state;
	short var;
};

struct MsgTriggerSevenDays : public Msg
{
	MsgTriggerSevenDays()
	{
		header.dwType = MSG_TRIGGERSEVENDAYS;
		header.stLength = sizeof( MsgTriggerSevenDays );

		triggerTime = 0;
	}
	__int64 triggerTime;
};

struct MsgAskSevenDaysTask : public Msg
{
	MsgAskSevenDaysTask()
	{
		header.dwType = MSG_ASKSEVENDAYSTASK;
		header.stLength = sizeof( MsgAskSevenDaysTask );

		index = -1;
	}

	int index;
};

struct MsgAskSevenDaysTaskAck : public Msg
{
	enum EResult
	{
		R_Sucess,
		R_Fail,
	};

	MsgAskSevenDaysTaskAck()
	{
		header.dwType = MSG_ASKSEVENDAYSTASK_ACK;
		header.stLength = sizeof( MsgAskSevenDaysTaskAck );

		result = R_Sucess;
	}

	EResult result;
};

struct MsgAskSevenDaysReward : public Msg
{
	MsgAskSevenDaysReward()
	{
		header.dwType = MSG_ASKSEVENDAYSREWARD;
		header.stLength = sizeof( MsgAskSevenDaysReward );

		index = -1;
	}
	int index;
};

struct MsgChangeChannelREQ:public Msg
{
	MsgChangeChannelREQ()
	{
		header.dwType = MSG_CHANGECHANNEL_REQ;
		header.stLength = sizeof( MsgChangeChannelREQ );
		nTargetServerId = -1;
	}
	int32 nTargetServerId;
};

enum eChangeChannelRet
{
	eChangeChannelRet_Succ = 0,//�ɹ�
	eChangeChannelRet_Error = 1,//ѡ��ķ��ߴ���
	eChangeChannelRet_Same = 2,//�뵱ǰ������ͬ
	eChangeChannelRet_Dead = 3,//�������
	eChangeChannelRet_Fight = 4,//ս��״̬
	eChangeChannelRet_Max	//δ֪����!
};

struct MsgChangeChannelACK : public Msg
{
	MsgChangeChannelACK()
	{
		header.dwType = MSG_CHANGECHANNEL_ACK;
		header.stLength = sizeof( MsgChangeChannelACK );
	}
	uint16 uResult;
};

struct MsgClearTeamMapAck : public Msg
{
	MsgClearTeamMapAck()
	{
		header.dwType = MSG_CLEARTEAMMAPACK;
		header.stLength = sizeof(MsgClearTeamMapAck);
	}
	bool Result;
};

struct MsgClearTeamMapReq : public Msg
{
	MsgClearTeamMapReq()
	{
		header.dwType = MSG_CLEARTEAMMAPREQ;
		header.stLength = sizeof( MsgClearTeamMapReq );
	}
};
struct GS2CSClearTeamMapReq:public Msg
{
	GS2CSClearTeamMapReq()
	{
		header.dwType = GS2CS_CLEARTEAMMAPREQ;
		header.stLength = sizeof( GS2CSClearTeamMapReq );
	}
	unsigned int TeamID;
	unsigned int PlayerID;
};
struct CS2GSClearTeamMapReq:public Msg
{
	CS2GSClearTeamMapReq()
	{
		header.dwType = CS2GS_CLEARTEAMMAPREQ;
		header.stLength = sizeof( CS2GSClearTeamMapReq );
	}
	unsigned int TeamID;
	unsigned int PlayerID;
};
struct GS2CSClearTeamMapAck:public Msg
{
	GS2CSClearTeamMapAck()
	{
		header.dwType = GS2CS_CLEARTEAMMAPACK;
		header.stLength = sizeof( GS2CSClearTeamMapAck );
	}
	unsigned int PlayerID;
	bool Result;
};

struct MsgAskGetSalary : public Msg
{
	MsgAskGetSalary()
	{
		header.dwType = MSG_ASKGETSALARY;
		header.stLength = sizeof( MsgAskGetSalary );
	}
};

struct MsgAskGetSalaryAck : public Msg
{
	MsgAskGetSalaryAck()
	{
		header.dwType = MSG_ASKGETSALARY_ACK;
		header.stLength = sizeof( MsgAskGetSalaryAck );

		bGet = 0;
	}

	uint8 bGet;
};

struct MsgAskAdvancement : public Msg
{
	MsgAskAdvancement()
	{
		header.dwType = MSG_ASKADVANCEMENT;
		header.stLength = sizeof( MsgAskAdvancement );

		shTitleId = -1;
	}

	short shTitleId;
};

struct MsgAskAdvancementAck : public Msg
{
	MsgAskAdvancementAck()
	{
		header.dwType = MSG_ASKADVANCEMENT_ACK;
		header.stLength = sizeof( MsgAskAdvancementAck );

		shCurTitleId = -1;
		bResult = false;
	}

	short shCurTitleId;
	bool bResult; 
};

struct MsgShowRankTitle : public Msg
{
	MsgShowRankTitle()
	{
		header.dwType = MSG_SHOWRANKTITLE;
		header.stLength = sizeof ( MsgShowRankTitle );

		bshowTitle = false;
		shCurTitleId = -1;
	}

	bool bshowTitle;
	short shCurTitleId;
};

struct MsgReconnectResetState:public Msg
{
	enum eResetState
	{
		eResetState_death,//����״̬
		eResetState_max
	};
	MsgReconnectResetState()
	{
		header.dwType = MSG_RECONNECT_RESETSTATE;
		header.stLength = sizeof(MsgReconnectResetState);
	}
	uint16 reset_state;
};

struct MsgReFreshHunting : public Msg
{
	enum eFreshType
	{
		eFreshType_Free,
		eFreshType_Gold,
		eFreshType_Money
	};

	MsgReFreshHunting()
	{
		header.dwType = MSG_HUNTING_REFRESH;
		header.stLength = sizeof( MsgReFreshHunting );

		eType = eFreshType_Free;
	}

	eFreshType eType;
};

struct MsgHuntingQuestList : public Msg
{
	MsgHuntingQuestList()
	{
		header.dwType = MSG_HUNTING_QUEST;
		header.stLength = sizeof( MsgHuntingQuestList );

		memset( nIds, 0, sizeof( nIds ) );
		dwTime = 0;
		nCount = 0;
		nLeftTime = 0;
	}

	int nIds[MaxCount_Show];
	DWORD dwTime;
	int nCount;
	int nLeftTime;
};

struct MsgHuntingAcceptQuest : public Msg
{
	MsgHuntingAcceptQuest()
	{
		header.dwType = MSG_HUNTING_ACCEPT_QUEST;
		header.stLength = sizeof( MsgHuntingAcceptQuest );

		nId = 0;
	}

	int nId;
};

struct MsgHuntingAskForList : public Msg
{
	MsgHuntingAskForList()
	{
		header.dwType = MSG_HUNTING_ASKFORLIST;
		header.stLength = sizeof( MsgHuntingAskForList );
	}
};

struct MsgFlyToPosition : public Msg
{
	MsgFlyToPosition()
	{
		header.dwType = MSG_FLYTOPOSITION;
		header.stLength = sizeof( MsgFlyToPosition );
	}
	unsigned int MapID;
	float Pos_X;
	float Pos_Y;
	unsigned int Type;
};
struct MsgFlyToPositionAck : public Msg
{
	MsgFlyToPositionAck()
	{
		header.dwType = MSG_FLYTOPOSITIONACK;
		header.stLength = sizeof( MsgFlyToPositionAck );
	}
	unsigned int MapID;
	float Pos_X;
	float Pos_Y;
};
struct MsgShowCenterInfo : public Msg
{
	MsgShowCenterInfo()
	{
		header.dwType = MSG_SHOWCENTERINFO;
		header.stLength = sizeof( MsgShowCenterInfo );
	}
	unsigned int ID;
};

struct MsgGetThreeDayItem : public Msg
{
	MsgGetThreeDayItem()
	{
		header.dwType = MSG_GETTHREEDAYITEM;
		header.stLength = sizeof( MsgGetThreeDayItem );
	}
};
struct MsgGetThreeDayItemAck : public Msg
{
	MsgGetThreeDayItemAck()
	{
		header.dwType = MSG_GETTHREEDAYITEMACK;
		header.stLength = sizeof( MsgGetThreeDayItemAck );
	}
	unsigned int vision;
	unsigned int value;
};

struct MsgUpdateYuanBaoData : public Msg
{
    MsgUpdateYuanBaoData()
    {
        header.dwType   = MSG_UPDATEYUANBAODATA;
        header.stLength = sizeof( MsgUpdateYuanBaoData );

		dwAccountYuanBaoStates = 0;
		dwAccountYuanBaoTotle = 0;
    }
	unsigned int	dwAccountYuanBaoTotle;
	unsigned int    dwAccountYuanBaoStates;
};

struct MsgUpdateYuanBaoDataReq : public Msg
{
    MsgUpdateYuanBaoDataReq()
    {
        header.dwType   = MSG_UPDATEYUANBAODATAREQ;
        header.stLength = sizeof( MsgUpdateYuanBaoDataReq );
		ChangeYuanBaoStatesValue = 0;
    }
	unsigned int ChangeYuanBaoStatesValue;
};

struct MsgMountMoveStar : public Msg
{
	MsgMountMoveStar()
	{
		header.dwType = MSG_MOUNTMOVESTAR;
		header.stLength = sizeof( MsgMountMoveStar );
	}
	__int64 OldMountID;
	__int64 NewMountID;
};

struct MsgUpdatePlayerPoint : public Msg
{
	MsgUpdatePlayerPoint()
    {
        header.dwType   = MSG_UPDATEPLAYERPOINT;
        header.stLength = sizeof( MsgUpdatePlayerPoint );
		ID = 0;
		States = 0;
		Op = 0;
		Value = 0;
		PlayerID = 0;
		ChangeValue = 0;
    }
	unsigned int PlayerID;
	unsigned int ID;
	unsigned int States;
	unsigned int Op;
	unsigned int Value;
	unsigned int ChangeValue;
};


struct MsgPassWordCardReq : public Msg
{
	MsgPassWordCardReq()
    {
        header.dwType   = MSG_PASSWORDCARDREQ;
        header.stLength = sizeof( MsgPassWordCardReq );
		memset(PwdCardSerialNumber,0,PwdCardSerialLength);
		memset(A,0,PwdCardLength);
		memset(B,0,PwdCardLength);
		memset(C,0,PwdCardLength);
    }
	char PwdCardSerialNumber[PwdCardSerialLength];//���к�
	char A[PwdCardLength];
	char B[PwdCardLength];
	char C[PwdCardLength];
};
struct MsgPassWordCardAck : public Msg
{
	MsgPassWordCardAck()
    {
        header.dwType   = MSG_PASSWORDCARDACK;
        header.stLength = sizeof( MsgPassWordCardAck );
		memset(A,0,PwdCardLength);
		memset(B,0,PwdCardLength);
		memset(C,0,PwdCardLength);
    }
	char A[PwdCardLength];
	char B[PwdCardLength];
	char C[PwdCardLength];
};
struct MsgLeaveExpReq : public Msg
{
    MsgLeaveExpReq()
    {
        header.dwType = MSG_LEAVEEXPREQ;
        header.stLength = sizeof( MsgLeaveExpReq );
    }
};
struct MsgLeaveExpAck : public Msg
{
    MsgLeaveExpAck()
    {
        header.dwType = MSG_LEAVEEXPACK;
        header.stLength = sizeof( MsgLeaveExpAck );
		PlayerID = 0;
		KillSum = 0;
		MaxKillSum = 0;
		RadExp = 0;
		Hour = 0;
		Exp = 0;
    }	
	unsigned int PlayerID;
	unsigned int KillSum;
	unsigned int MaxKillSum;
	float RadExp;
	unsigned int Hour;
	unsigned int Exp;
};
struct MsgGetLeaveExpReq : public Msg
{
    MsgGetLeaveExpReq()
    {
        header.dwType = MSG_GETLEAVEEXPREQ;
        header.stLength = sizeof( MsgGetLeaveExpReq );
    }
};
struct MsgPassWordCardCanel : public Msg
{
	MsgPassWordCardCanel()
    {
        header.dwType   = MSG_PASSWORDCARDCANEL;
        header.stLength = sizeof( MsgPassWordCardCanel );
    }
};

///////////////////////////////////////

#pragma pack( pop )

//�����Ǳ䳤��Ϣ�ļ��
#ifdef _DO_CHECK_MSG_
    #define CHECK_MSGLEN_BOOL( pMsg, msg) if ( !pMsg ) { return false;} if( pMsg->GetLength() != sizeof(msg) ){ return false; }
    #define CHECK_MSGLEN_NULL( pMsg, msg) if ( !pMsg ) { return NULL;}  if( pMsg->GetLength() != sizeof(msg) ){ return NULL; }
    #define CHECK_MSGLEN( pMsg, msg )     if ( !pMsg ) { return;}  if( pMsg->GetLength() != sizeof(msg) ){ return; }
#else
    #define CHECK_MSGLEN_NULL( pMsg, msg ) 
    #define CHECK_MSGLEN_BOOL( pMsg, msg )
    #define CHECK_MSGLEN( pMsg, msg )
#endif

#endif // __COMMON_MESSAGEDEFINE_H__
