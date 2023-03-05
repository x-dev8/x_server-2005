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

#define GOODS_INFO        64        // 物品名称与说明的长度
#define GET_GOODS_NUM_MAX 50        // 每次取得物品的最大数量
#define BARGAINING_GOODS_MAX_NUM 10 // 交易的最大量
#define BinaryFlag(x) (DWORD)( (x>0) ? 1 << (x-1) : 0 )

#pragma pack( push, 1 ) 

#define TAG(x) (((x>>24)&0xff) |((x>>8)&0xff00)|((x&0xff00)<<8) | ((x&0xff)<<24) )

//如果定义了这个宏，整个系统按单步逻辑运行

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

// 新的字每表示法
// 第一位 : 功能块标识，大的分类
// 第二位 : 流向,标识是向哪里发送的 
//          s 服务器向 客户端
//          c 客户端向 服务器
//            u 双向(doUble)
//            b 服务器和客户端双向
//          d 数据库向 游戏
//          g 游戏向 数据库
// 第三位 : 小功能标识
// 第四位 : 功能序号

enum EClientServerMessageDefine
{ // 消息定义
    GAME_FIRST_MSG = GAMEWORLD_MSG_BEGIN,
    MSG_LOGIN,
    MSG_ACKLOGIN,
    MSG_RIGHTCHECK,         // [没用]
    MSG_EXIT,
    MSG_QUERYMOVE,          // [Server:LogMsg中应用 Client:没用]
    MSG_ACKMOVE,            // [Server:LogMsg中应用 Client:没用]
    MSG_MOVEPATH,           // [Server:LogMsg中应用 Client:没用]
    MSG_MOVETOTARGET,       // [Server:LogMsg中应用 Client:没用]
    MSG_EXITMYSIGHT,
    MSG_CHANGEMAP,
    MSG_MAPLOADED,
    MSG_QUERYDISPLAYNAME,
    MSG_ACKDISPLAYNAME,
    MSG_ACKATTACK,          // [Server:LogMsg中应用 Client:没用]
    MSG_SEEATTACK,          // [Server:LogMsg中应用 Client:没用]
    MSG_REQSKILLATTACK,   // 请求发动技能攻击
    MSG_ACKQUERYATT2,     // 响应发动技能攻击 // [Server:没用 Client:OnMsgAckAttack3中用到]
    MSG_ACKATT2,            // [没用]
    MSG_EXPRESSION,       // 客户端发过来，某人在作表情动作    
    MSG_ACKEXPRESSION,    // 看到某人在作表情动作
    MSG_WHODIE,             // [Server:LogMsg中应用，没有对应的数据结构 Client:没用]
    MSG_QUERYGAMEPROPERTY,  // [Server:LogMsg中应用 Client:没用]
    MSG_ACKGAMEPROPERTY,    // [Server:LogMsg中应用 Client:没用]
    MSG_QUERYALLGAMEPROPERTY,
    MSG_ACKALLGAMEPROPERTY,   
    MSG_EVENTRANGE,         // [Server:LogMsg中应用 Client:没用]
    MSG_CHAT,
    MSG_ENDACKCHAR,           // 通知客户端。。账号数据读取好了！// [Server:没用 Client:OnMsgEndGetCharacter中应用]
    MSG_ACKCHAR,
    MSG_ENTERWORLD,
    MSG_ACKENTERWORLD,
    MSG_CREATECHAR,
    MSG_ACKCREATECHAR,
    MSG_DELETECHAR,
    MSG_ACKDELETECHAR,    
    MSG_GETLAG,
    LOGMSG_ITEMLOG,      // 重要道具的操作 // [没用]
    LOGMSG_CASHPOINT,    // 帐户点卡的操作 // [没用]
    LOGMSG_CHARACTER,    // 角色帐号的操作 // [没用]
    MSG_CHARLEVELUP,     // 角色升级消息
    MSG_SEECHARLEVELUP,  // 看到某人升级
    MSG_SHOWEFF,         // 看到角色身上出现效果    // [没用]
    MSG_REQ_SCRIPT,      // script相关消息
    MSG_ACK_SCRIPT,
    MSG_SCRIPTCANCEL,    // 客户端取消脚本执行1045 // [Server:没用 Client:有用]
    MSG_SCRIPTEND,       // 脚本结束
    MSG_SCRIPTVARCLEAR,  // 清除所有脚本变量 // [没用]
    MSG_SCRIPTSHOW,
    MSG_GETSHOP,         // 请求查看物品
    MSG_ACKGETSHOP,      // 请求查看物品(回答)
    MSG_BUYORSELLGOODS,  // 买卖物品1050
    MSG_ACKBUYORSELLGOODS, // 买卖物品(回答)
    MSG_REQRELIVE,        //Relive
    MSG_REFRESHCHAR,      // 刷新用户数据 // [没用]
    MSG_ITEMENTERMYSIGHT, // 物品进入视野
    MSG_QUERYITEMINFO,    // 取物品信息1055 // [没用]
    MSG_ACKDRAGINFO,      //返回药品信息    // [没用]
    MSG_PICKITEM,         //捡东西
    MSG_GETITEM,          //获得物品    // [没用]
    MSG_GETMONEY,         //获得钱      // [没用]
    MSG_DROPITEM,         //丢弃物品1060
    MSG_ACKDROPITEM,      //确认丢弃
    MSG_MONEYCHANGE,            // 
    MSG_CALLPET,          // 召唤宠物 宠物类    // [没用]
    MSG_FLYTOMAP,        //客户端要求切换地图1080   // [没用]
    MSG_EQUIPCHANGED,    //装备改变
    MSG_MOVEASTEP,       
    //MSG_MOVEBLOCKED    
    //MSG_MOVETOPOS,                //移动到目标坐标点

    // 虚拟客户端  
    MSG_QUERYCHARAROUND,            // 请求得到周围的char
    MSG_ACKCHARAROUND,              // 响应
    MSG_QUERYCHARINFO,   
    MSG_ACKCHARINFO,
    MSG_VERIFYPOS,                  //校正位置
    MSG_SYNCPOS,                    //固定时间的坐标同步消息    // [没用]
    MSG_REQMOVEASTEP,               //请求移动位置              // [没用]
    MSG_PERMITMOVE,                 //移动许可                  // [没用]
    
    //角色数值改变
    MSG_CHARATTRCHANGE,         //

    //升级各种属性
    //如:角色的基本属性
    //职业，元素等。。一切可以升级的东西
    MSG_REQ_UP_ATTR_LEVEL,      // [Server:OnReqUpAttrLevel函数被注释掉 Client:没用]
    MSG_ACK_UP_ATTR_LEVEL,      // [Server:没用 Client:OnMsgAttrLevelUp]

    //MSG_VISUALCHANGE
    //客户端保存连续技设定
    MSG_REFRESHLINKEDSKILLS,    // [Server:OnRefreshLinedSkill函数被注释掉 Client:没用]
    //客户端保存热键设定
    MSG_REFRESHHOTKEY,

    //地图持续性效果进入视野
    MSG_EFFECTENTERMYSIGHT,
    //持续效果产生的伤害
    MSG_DAMAGEOFEFFECT,     // [没用]
    
    MSG_REQATTACKGROUND, // 角色攻击地面
    MSG_SEEATTACKGROUND, // 确认 看见角色攻击地面   // [没用]
    
    MSG_SEEDAMAGE,      // 看到多人受到了伤害    
    MSG_SEEATTACK3,     // 看见发出单人或多人攻击
    MSG_INTONATE,       // 看到莫人在呤唱           // [没用]
    
    MSG_MAGIC_RELEASE,  // 看到了某人释放法术       // [没用]
    
    MSG_EQUIP,          // 客户请求装备物品
    MSG_EQUIPTOWHERE,   // [Server:OnEquipToWhere直接return Client:SendEquipMsgToWhere]
    MSG_ACKEQUIP,
    MSG_UNEQUIP,        //卸下装备
    MSG_MOVEGOODS,              // [没用]
    MSG_CHANGEGOODSPOS,         // [没用]
    MSG_CHANGEITEMPOS,
    MSG_USEGOODS,       // 使用物品1110
    MSG_NPC_ENTERMYSIGHT,              //进入视野
    MSG_NPC_ENTERMYSIGHTMOVINGASTEP,   //移动中进入视野     // [Server:没用 Client:OnMsgNPCEnterMySightMovingAStep 无函数实现]

    MSG_PLAYER_ENTERMYSIGHT,            //进入视野
    MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP, // [Server:没用 Client:OnMsgPlayerEnterMySightMovingAStep]
    
    MSG_QUERYCONTINUOUSSKILL, // 请求环绕技能
    MSG_ACKCONTINUOUSSKILL,
    MSG_QUERYHPINFO,          // 请求血条信息
    MSG_ACKHPINFO,            // 返回血条信
    MSG_ADDMISSIONINTRO,      // 增加任务说明   // [Server:没用 Client:OnMsgAddMissionIntro]
    MSG_DELMISSIONINTRO,      // 删除任务说明   // [Server:没用 Client:OnMsgAddMissionIntro]
    MSG_REQDOACTION,          // 请求做动作     // [没用]
    MSG_SEEACTION,            // 看见做动作     // [Server:没用 Client:OnMsgSeeAction]

    //************游戏世界群组服务器消息
    MSG_GWDC_ISGWORLD,  //通知 连接的服务器是 游戏世界服务器    // [没用]
    MSG_GWDC_ISGATE,    //是 Gate                               // [没用]
    MSG_GWDC_GWORLDINFO,//是游戏世界的信息                      // [没用]
    MSG_GWDC_GATEINFO,  //是GateInfo                            // [没用]

    //*************游戏世界群组和客户端 消息    
    MSG_GWDC2C_GWORLDINFO, // 发送到客户端的游戏世界的信息      // [Server:没用 Client:GameLoginMsg]    
    MSG_GW2G_SYNCCHARINFO,    // 同步玩家信息给客户端
    
    MSG_G2GW_ALLOCCLIENT,    // 请求分配客户数据    
    MSG_GW2G_RETALLOCCLIENT, // 返回    
    MSG_G2GW_DELETECLIENT,   // 删除客户数据
    MSG_GW2G_SYNCCHARPOS,    // Gate收到消息后，如果角色不存在，分配一个 S2S
    MSG_GW2G_NPCEXIT,        // 非玩家角色死亡，Gate释放该ID

    //更新玩家数据
    //MSG_UPDATECHARDATA, //= TAG('udcd')
    MSG_GETPLAYERINFO,    // 取得玩家的信息    
    MSG_ACKGETPLAYERINFO, // 服务器，发来得玩家角色的信息     
    MSG_ACKFRIENDLEAVE,   // 服务器发送过来的消息通知有人下线了     // [没用]
    
    MSG_REQ_PLACESTONE,   // 请求放置符石   // [Server:没用 Client:有函数体，无函数实现]
    MSG_ACK_PLACESTONE,   // 回复放置符石   // [没用]
    MSG_REQ_REMOVESTONE,  // 请求移除符石   // [没用]
    MSG_ACK_REMOVESTONE,  // 回复移除符石   // [Server:没用 Client:OnMsgRemoveStone]
    
    MSG_REQ_PLACESUBSKILL,  // 请求放置招式片段     // [没用]  
    MSG_ACK_PLACESUBSKILL,  // 回复放置招式片段     // [Server:没用 Client:OnMsgPlaceSubSkill]
    MSG_REQ_REMOVESUBSKILL, // 请求移除招式片段     // [没用]
    MSG_ACK_REMOVESUBSKILL, // 回复移除招式片段     // [Server:没用 Client:OnMsgRemoveSubSkill]
    MSG_REQ_UPSKILL,        // 请求升级技能 [有用]
    //MSG_ACK_UPSKILL,      // 回复升级技能
    
    MSG_REQ_PRODUCEITEM,    //请求制造道具          // [没用]
    MSG_ACK_PRODUCEITEM,    //回复制造工具          // [Server:没用 Client:OnMsgProduceItem]
    
    //MSG_REQ_UPGRADEEQUIP, ////请求打造装备
    //MSG_ACK_UPGRADEEQUIP, ////回复打造装备
    //MSG_ACK_LEARNSKILL  // 学会了新的技能    
    //MSG_ACK_GETSTONE    // 获得了新的符石
    
    MSG_GM_REQ_PLACE_CHAR, // gm把char摆放到指定的位置  // [没用]
    MSG_PING,              // 和服务器之间的PING.
    MSG_ALLNPCONTHEMAP,
    
    MSG_SWITCHFIGHTSTATUS,     // 客户端请求切换战状态  // [没用]
    MSG_SWITCHSITSTATUS,       // 客户端请求切换坐下状态// [没用]
    MSG_ACK_SWITCHFIGHTSTATUS, // 切换战斗状态    
    MSG_ACK_SWITCHSITSTATUS,   // 切换站立
    MSG_UPDATEONLINE_LOGIN2ACCOUNT, //loginServer断开重连Account后 发送此消息将LoginServer上所有在线角色发到服务器  // [没用]

    //通知当前连接得服务器ID
    //比如:GWorld连接到LoginServer,
    //Login->Account
    MSG_SERVERID,
    MSG_QUERYSERVERID,          // [没用]

    MSG_QUERYSERVERINFO ,   //query server infomation example:current online player count   // [没用]
    MSG_ACK_QUERYSERVERINFO,// 请求查询服务器信息
    
    MSG_HITITEMBAG,         // 客户端发过来的消息，通知点击类背包上面的道具 // [Server:没用 Client:MouseShortCutClear]
    MSG_RIGHTHITITEMBAG,    // 客户端发过来的消息，通知使用背包上面的道具   // [没用]
    MSG_UPDATECHARABAG  ,   // 更新背包到客户端
    MSG_UPDATESHORTCUTBAG,  // 更新快捷方式到客户端                 // [Server:没用 Client:函数没有实现代码]

    MSG_UPDATEVISUALEQUIP,  // 更新身上的装备 【有用】
    MSG_UPDATEFIGHTDATA,    // 更新二级属性   【有用】
    MSG_HITBODYITEM,        // 发消息点击了身上的道具【有用】
    MSG_BUFFSUPDATE,        // 当前Buff list
    MSG_BUFFSCHANGED,        // buff变化
    
    MSG_CHANGEDIR,          // 发消息通知其他的客户端。在转身

    //sslenum
    MSG_SSLSendPublicKey,       // [没用]
    MSG_SSLSendSessionKey,      // [没用]
    MSG_SSLExchangKeyFinished,  // [没用]

    MSG_BUILDINGENTERMYSIGHT, // 建筑物进入视野     // [Server:没用 Client:OnMsgBuildingEnterMySight函数没有实现]
    MSG_BUILDING_REQBUILD ,   // 请求建造           // [没用]
    MSG_BUILDING_BUILDFAILED, // 请求建造失败       // [Server:没用 Client:OnMsgBuildFailed函数没有实现]
    MSG_BUILDING_BUILDSTATUS, // 建造状态           // [Server:没用 Client:OnMsgBuildStatus函数没有实现]
    MSG_BUILDING_DESTROYED ,  // 建筑被摧毁         // [Server:没用 Client:OnMsgBuildDestroyed函数没有实现]
    MSG_BUILDING_SELFDESTROYED , //建筑自毁，主塔被击毁后，调用     // [Server:没用 Client:OnMsgBuildSelfDestroyed函数没有实现]

    // 组队
    MSG_CREATETEAM,            //组队       // [Server:没用 Client:OnMsgCreateTeam函数没有实现]
    MSG_ACKCREATETEAM,         //请求组队   // [Server:没用 Client:OnMsgCreateTeam函数没有实现]
    MSG_REQUESTTEAM,           // 队长提出邀请组队
    MSG_ACKJOINTEAM,           // 请求加入队伍
    MSG_EXITTEAM,              // 退出队伍
    MSG_KICKFROMTEAM,          // 从队伍中踢掉某人
    MSG_INQUIRETEAMHEADER,     // 队长取消邀请(踢离队员)    // [没用]
    MSG_ACKINQUIRETEAMHEADER,               // [Server:OnAckMsgInquireTeamHeader函数没有实现 Client:没用]
    MSG_INQUIREINVITEE,        //队员收到被邀请组队消息(弹出确认组队mssagebox)
    MSG_ACKINQUIREINVITEE,     //队员返回点击确认组队消息(点是否确认按钮)

    MSG_TEAMINFO,              //队伍信息       // [Server:没用 Client:OnMsgTeamInfo函数]
    MSG_ADDTEAMMEMBER,         //加入队伍
    MSG_DELETETEAMMEMBER,      //删除成员退出队伍

    //吟唱状态(S->C)
    MSG_INTONATESTART ,       //吟唱开始
    MSG_INTONATEEND ,         //吟唱结束
    //请求取消技能(C->S)
    MSG_REQCANCELSKILL ,
    //技能被取消了(S->C) 
    MSG_SKILLCANCELD ,
    //技能状态，进入视野后，如果在吟唱或者维持技能
    MSG_SKILLSTATUS ,
    //维持技能结束
    MSG_HOLDSKILLEND ,
  

    MSG_SKILL_BEGINCOLDDOWN          // 开始冷却[有用]
    ,MSG_TEAM_PLAYERINFO             // 队友信息更新 
    ,MSG_CHANGE_SKILL                   // 添加技能[有用]
    

    ,MSG_TELLREPUTATION              // 通知声望        // [Server:没用 Client:OnMsgTellReputation]
    ,MSG_REPUTATIONCHANGE            // 声望改变了      // [没用]
    // 功勋值
    ,MSG_EXPLOIT_CHANGE               // 功勋值改变了   // [Server:没用 Client:OnMsgExploitChange]
    ,MSG_TELL_EXPLOIT                 // 通知功勋       // [Server:没用 Client:OnMsgTellExploit]
    ,MSG_TELL_OFFICIALLEVEL           // 告知官职等级   // [Server:没用 Client:OnMsgTellOfficialLevel]
    ,MSG_QUERY_CITYSINFO              // 查询所有城市的信息     // [没用]
    ,MSG_CITYINFO                     // 更新的城市信息1230     // [没用]
    ,MSG_PLAYERNAME_CHANGED           // 用户名字改变           // [Server:没用 Client:OnMsgPlayerNameChanged]
    ,MSG_TEACHSKILL                 
    ,MSG_LEARNSKILL
    ,MSG_CHANGE_PKRECORD              // 改变PK记录         // [Server:没用 Client:OnMsgChangePKRecord]
    ,MSG_TELLMAP_NPCINFO              // 告诉客户端地图上的npc分布1235  // [没用]
    ,MSG_TELLMAP_NPCQUEST             // 告知地图上npc带有的任务        // [Server:没用 Client:OnMsgTellMapNpcQuest无函数实现]
    ,MSG_TELL_CHAR_VAR                // 告知客户端任务状态             // [Server:没用 Client:OnMsgTellCharVars]
    ,MSG_MOVE_COMPOUND_ITEM           // 合成
    ,MSG_QUERY_COMPOUND               // 查询合成
    ,MSG_ACK_COMPOUND                 // 请求合成   // [Server:没用 Client:OnMsgAckCompound]
    ,MSG_EQUIP_EVOLVE                 // 装备进化
    ,MSG_MINIGAME_GATE_ROOM_CREATED   // 房间创建   // [没用]
    ,MSG_MINIGAME_GATE_ROOM_DESTROYED // 房间销毁   // [没用]
    ,MSG_MINIGAME_GATE_ROOM_IN        // 进入房间   // [没用]
    ,MSG_MINIGAME_GATE_ROOM_OUT       // 退出房间1245   // [没用]
    ,MSG_MINIGAME_ROOM_INFO           // 房间信息       // [没用]
    ,MSG_MINIGAME_ROOM_NOPCHANGED     // 房间中人数发生变化     // [没用]
    ,MSG_MINIGAME_PLAYERINFO          // 玩家信息       // [没用]
    ,MSG_MINIGAME_REQ_INROOM          // 请求加入房间   // [没用]
    ,MSG_MINIGAME_ACK_INROOM          // 返回加入房间   // [没用]
    ,MSG_MINIGAME_REQ_OUTROOM         // 请求退出房间   // [没用]
    ,MSG_MINIGAME_ACK_OUTROOM         // 返回退出房间   // [没用]

    ,MSG_MINIGAME_REQ_CREATEROOM      // 请求创建房间   // [没用]
    ,MSG_MINIGAME_ACK_CREATEROOM      // 返回创建房间   // [没用]

    //屋主退出，自然房间被Destroy
    ,MSG_MINIGAME_ROOM_DESTROYED      // 房间被删除1255     // [没用]

    ,MSG_MINIGAME_COMMAND             // 游戏控制信息       // [没用]
    ,MSG_MINIGAME_GAMERESULT          // 游戏结果           // [没用]
    ,MSG_MINIGAME_START               // 游戏开始           // [没用]

    ,MSG_MINIGAME_TIMEFRAME           // 时间帧             // [没用]

    ,MSG_CONTAINER                          //1260          // [没用]
    ,MSG_ASKPLAYERINFO            // 查询玩家信息 【不用】
    //,MSG_CHANGEMONSTERMOVETYPE            //改变怪物的移动类型
    //,MSG_QUERY_INTENSIFY                  //回答强化ITEM    
    //,MSG_ACK_INTENSIFY                    //请求强化ITEM    
    ,MSG_SCRIPT_PLAYERMUSIC
    ,MSG_SCRIPT_MAKEITEM
    ,MSG_SCRIPT_REQ_SHOW_QUEST_DLG
    ,MSG_SCRIPT_ACK_SHOW_QUEST_DLG
    ,MSG_REQ_QUEST_INFO
    ,MSG_ACK_QUEST_INFO
    ,MSG_QUERYMAPNPCLIST                    // 请求返回当前地图的npc列表，  // [没用]
    ,MSG_POPMAPNPCLIST
    ,MSG_PROFESSIONCHANGE                   // 职业改变
    ,MSG_CHANGE_FIGHTSTATE                  // 改变战斗状态
    ,MSG_LOCKTARGET                         // 锁定目标
    ,MSG_ATTACKLOCKTARGET                   // 攻击锁定的目标
    ,MSG_KEEPMOVINGTOPOS                    // 向某个坐标一直移动       // [没用]
    ,MSG_MOVINGTOPOS                        // 移动到某个坐标           // [没用]
    ,MSG_CHANGINGDIR                        // 改变方向
    ,MSG_PLAYERMOVING                       // 向服务器发送保持移动的信息      // [Server:没用 Client:用到MsgPlayerMoving消息中的枚举]
    ,MSG_MOVEDTOPOS                         // 向服务器发送曾移动到某点的信息     // [没用]
    ,MSG_READYTOUSESPECIALSKILL             // 向服务器发送，准备使用技能的消息
    ,MSG_USESPECIALSKILL                    // 向服务器发送，使用特殊技能的消息
    ,MSG_AGREEUSESPECIALSKILL               // 向客户端发送，同意使用特殊技能的通知
    ,MSG_DISABLEUSESPECIALSKILL             // 向客户端发送，不能使用特殊技能的通知       // [没用]
    ,MSG_AGREEREADYTOUSESPECIALSKILL        // 向客户端发送，同意准备特殊技能的通知
    ,MSG_GETBILLPOINT                       // 获取玩家点数可玩状态【不用】
    ,MSG_SWITCHGATE                         // 获取建议连接的GateServer
    ,MSG_GATEINFO                           // 发送给GAMESERVER的GATESERVER信息
    ,MSG_ABANDON_TASK                       // 放弃任务
    ,MSG_QUERY_SCRIPTVAR                    // 请求查看脚本变量(对策划调试脚本用)
    ,MSG_SHOWTEXT                           // 在屏幕上显示文字信息
    ,MSG_UPDATEBANK                         // 更新银行信息         // [没用]
    ,MSG_REQ_BANKTRADE                      // 请求银行交易
    ,MSG_ACK_BANKTRADE                      // 回复交易请求         // [没用]

    ,MSG_UPDATESTORAGE                      // 更新仓库信息
    ,MSG_MOVE_STORAGE_ITEM                  // 请求仓库物品移动
    ,MSG_ACK_MOVE_STORAGE_ITEM              // 回复交易请求         // [没用]

    ,MSG_REQ_BACKCHARATERLIST               // 返回人物列表         // [没用]
    ,MSG_NPCPLAYANIM                        // NPC做动作
    ,MSG_LOGINWAIT                          // 登陆排队消息         // [没用]
    ,MSG_CANCEL_LOGINWAIT                   // 客户端取消排队       // [结构没用]
    ,MSG_CHARSKILLLEVELUP
    ,MSG_PINGSERVER                         // login时候发送消息ping服务器的 网络延迟   // [没用]
    ,MSG_CHANGEDROME                        // 改变坐骑的消息
    ,MSG_DISDROME                            // 下坐骑的消息
    ,MSG_JUMP                 // 跳跃信息 【有】
    ,MSG_CLIENTLOG            // Client Log.提交 -
    ,MSG_USESKILLHINTMESSAGE  // 技能使用的提示消息

    ,MSG_GW2G_CREATESTAGE     // Server通知GateServer创建场景
    ,MSG_GW2G_RELEASESTAGE    // Server通知GateServer释放场景
    ,MSG_SETDIALOGNAME
    ,MSG_INTONATEINTERRUPT    // 中断吟唱
    ,MSG_CHARLIST             // 玩家列表
    ,MSG_SCRIPT_SETHOTKEY     // 脚本设置热键

    ,MSG_TURNINTOHIDE                       // 进入隐形状态     // [没用]
    ,MSG_APPEARFROMHIDE                     // 离开隐形状态     // [没用]

    ,MSG_GMCOMMAND                          // GM命令
    ,MSG_CHANGEQUIPHP                       // 装备耐久
    ,MSG_CHARINFO                           // 角色信息         // [没用]
    ,MSG_UNPLAYERMOVINGTOPOS                // 非玩家角色移动到目标点消息 【有】
    ,MSG_UNPLAYERMOVINGTOLOCKTARGET         // 非玩家角色移动到锁定目标   【有】
    ,MSG_UNPLAYERCLOSINGTOLOCKTARGET        // 非玩家角色贴近其目标       【有】
    ,MSG_GWORLDINFO                         // 告诉GateServer当前GWORLD状态
    ,MSG_REMOVEITEM                         // 移除物品
    ,MSG_UPDATETIME                         // 更新游戏世界时间
    ,MSG_UNPLAYERVERIFYPOS                  // 非玩家角色矫正坐标
    ,MSG_PLAYERVERIFYPOS                    // 玩家角色矫正坐标
    ,MSG_INTENSIFYEQUIP                     // 强化             [有用]
    ,MSG_PLAYERCHANGEMOVINGTYPE             // 玩家改变移动方式 // [没用]
    ,MSG_PLAYERCHANGEMOVINGDIR              // 玩家改变移动方向 // [没用]
    ,MSG_PLAYERCHANGEMOVINGDIRANDTYPE       // 玩家改变移动方向和移动方式   // [没用]
    ,MSG_PLAYERSTOPSOMEWHERE                // 玩家停在某处                 // [没用]
    ,MSG_PLAYERSTOPSOMEWHEREHAVEDIR         // 玩家朝着一个方向停在某处     // [没用]
    ,MSG_LOCK_ITEM
    ,MSG_LOCK_ITEMACK
    ,MSG_UNLOCK_ITEM
    ,MSG_UNLOCK_ITEMACK
    ,MSG_CHECKUNLOCK_ITEMREQ
    ,MSG_CHECKUNLOCK_ITEMACK
    ,MSG_LOGININFO                          // 玩家的登陆信息（玩家已成功登陆，返回信息）
	//,MSG_LOGININFO_NEW                          // 玩家的登陆信息（玩家已成功登陆，返回信息）新的机制添加
    ,MSG_GETCHARACTER                       // 获取玩家角色消息
    ,MSG_REPAIRITEM                         // 修理物品 【有用】
    ,MSG_REPAIRITEMSERVERTOCLIENT           // 修理物品服务器-》客户端
    ,MSG_DRAWWEAPON                         // 拔出武器
    ,MSG_DRAWINWEAPON                       // 收起武器
    //,MSG_FRIENDOFFLINE                    // 好友下线
    ,MSG_CASTINEFFICACYSKILL                // 使用了一个无效的技能
    ,MSG_SHOWLEVELINFO                      // 人物升级的信息
    ,MSG_PETCOMMAND                         // 宠物的命令
    ,MSG_SAWSOMEONEDEAD                     // 看见某人死亡

    ,MSG_PLAYERMOVINGPOS                    // 移动中玩家位置改变的消息
    ,MSG_PLAYERMOVINGPOSANDDIR              // 移动中玩家位置和朝向改变的消息
    ,MSG_PLAYERPOS                          // 原地不动玩家的位置消息
    ,MSG_PLAYERDIR                          // 原地不动玩家的朝向消息
    ,MSG_PLAYERPOSANDDIR                    // 原地不动玩家的位置和朝向消息
    ,MSG_UPHPANDMP                          // 专门CLIENT用的恢复HP和MP的值     // [Server:没用 Client:OnMsgHPMPModify]
    ,MSG_REQ_CREATECHECKNAME                // 客户端创建人物发送的请求检测名字是否重复
    ,MSG_ACK_CREATECHECKNAME                // 返回
	,MSG_NEWCHANGENAMEREQ
	,MSG_NEWCHANGENAMEACK

    ,MSG_POSCHANGE                          // GateServer优化移动发送消息(把多人/多类型移动消息打成一个大包发送)
    ,MSG_ENTERMYSIGHTPACK                   // GateServer优化进入视野消息(把角色进入视野进行打包压缩，并根据情况决定下发内容)
    ,MSG_ACKENTERWORLDPACK                  // GateServer优化进入游戏消息(对数据进行压缩)
    ,MSG_MOVE_INTENSIFY_ITEM                // 强化移动         // [Server:OnMoveIntensifyItem直接return Client:没用]
    ,MSG_CALLINTENSIFYUI                    // 强化界面出来吧!  // [Server:没用 Client:OnMsgShowIntensifyUI]
    ,MSG_PEEKOTHEREUIP                      // 看别人装备
    ,MSG_WANTPEEK                           // 想看

    ,MSG_DONE_QUEST                         // 任务完成
    
    ,MSG_REQ_DUEL                           // -决斗-
    ,MSG_ACK_DUEL
    ,MSG_DUEL_START
    ,MSG_DUEL_END
    ,MSG_DUEL_STOP

    ,MSG_ACK_ECTYPEMAP_INFO                 // 回答副本信息
    ,MSG_REQ_ECTYPEMAP_INFO                 // 请求副本信息         // [Server:OnReqEctypeMapInfo被注掉 Client:没用]
    ,MSG_REQ_FLYTOMAP                       // 请求飞地图

    ,MSG_REQ_ASSIGN_TEAM                    // 队伍分配的时候 2级以上的物品进行塞子投掷     // [Server:没用 Client:MsgReqAssginTeam]
    ,MSG_ACK_ASSIGN_TEAM                    // 返回每个队伍成员选择的信息
    ,MSG_REQ_CHANGE_ASSIGNMODE              // 队长申请改变队伍分配模式
    ,MSG_ACK_CHANGE_ASSIGNMODE              // 服务器返回改变队伍分配模式
    ,MSG_ACK_CHANGE_ASSIGNMODE_ANSWER       // 客户端每个队员返回选择答案
    ,MSG_ACK_CHANGE_ASSIGNMODE_RESULT       // 改变分配模式失败了 告诉客户端 每个队员都关掉 选择界面    // [没用]

    ,MSG_REQ_BACKCHARATERLISTSUCESS         // BackCharaterList Success     // [没用]

    ,MSG_ADD_FIRSTLIST                      // 增加GateServer优先列表项 
    ,MSG_REMOVE_FIRSTLIST                   // 移除GateServer优先列表项

    ,MSG_REQ_UPGRADE_TEAM                   // 请求提升队长

    ,MSG_2C_ITEM_ADSCRIPTION                // 告诉客户端物品归属
    ,MSG_SKILLEXPTOSKILL                    // 技能经验给那个技能
    ,MSG_SKILLEXPUP                         // 技能经验增加
    ,MSG_REQ_SKILLEXPFORSKILLID             // 服务器给客户端的返回消息
    ,MSG_KILLMONSTER                        // 杀死怪物他的经验和技能经验
    ,MSG_PKSTATE_CHANGE                     // 玩家PK状态更改(红名/蓝名/白名/灰名)
    ,MSG_CANCELDELCHAR                      // 取消删除角色
    ,MSG_ACK_CANCELDELCHAR                  // 回应取消删除角色
    ,MSG_CHANGE_PKFLAG                      // 改变PK模式
    ,MSG_ACK_CHANGE_PKFLAG                  // 回应改变PK模式

    ,MSG_PLAY_EFFECT                        // 播放特效
    ,MSG_SHOW_INTONATE_BAR                  // 显示吟唱条
    ,MSG_ISRELIVEYESORNO                    // 是否同意复活

    ,MSG_ACK_FIRSTTIP                       // 第一次事件提示
    ,MSG_REQ_FIRSTTIP

    ,MSG_PLAYERMOVINGPOSTOSERVER            // 客户端向服务器端发送移动中玩家位置改变的消息 【有】
    ,MSG_PLAYERMOVINGPOSANDDIRTOSERVER      // 移动中玩家位置和朝向改变的消息               【有】
    ,MSG_PLAYERPOSTOSERVER                  // 原地不动玩家的位置消息                       【有】
    ,MSG_PLAYERDIRTOSERVER                  // 原地不动玩家的朝向消息
    ,MSG_PLAYERPOSANDDIRTOSERVER            // 原地不动玩家的位置和朝向消息

    ,MSG_CHANGEPOWER                        // 改变能量     // [没用]
    ,MSG_CHANGEPOWERPOINT                   // 改变聚气点   // [没用]
    ,MSG_HITCHMOVETARGETPOS                 // 搭乘移动的目标点
    ,MSG_CANCONTROLMOVING                   // 玩家能否控制的移动
    ,MSG_NOTIFYMAIL                        // 刷新邮件列表
    ,MSG_SENDMAILREQ                        // 发送邮件请求
    ,MSG_OPMAILREQ                          // 操作邮件请求
    ,MSG_DISHITCH                           // 下搭乘宠物的消息
                                     
    ,MSG_SHOPCENTERBUY                      // 商城购买，RMB道具
    ,MSG_RMBGOLDCHANGE                      // 元宝发生变化
    ,MSG_GLODCOVSILVER                      // 金币转换银子
                                               
    ,MSG_ACKGLODCOVSILVER                   // 回答 金币转换银子    // [没用]
                                              
    ,MSG_CHANGEMANIPLEFROMTEAM              // ChangeManipleFromTeam

    ,MSG_REQ_CHANGE_MEMBERTITLE             // 改变公会会员称号     // [没用]
    ,MSG_MOVEPLAYERFROMMANIPLE              // 玩家更改小队    

    ,MSG_S2CSENDSOFTKEYBOARD                // loginServer发送软件盘对应序列给客户端    // [Server:没用 Client:GameLoginMsg]

    ,MSG_REQGRAPHICCODE                     // 请求客户端检测图片验证码
    ,MSG_ACKGRAPHICCODE                     // 客户端应答图片验证码

    ,MSG_COVCORPS                           // 转换为团
    ,MSG_REQCOVCORPS                        // 团队转换成功     // [没用]

    ,MSG_TELLLUCKREWARD                     // 告诉客户端本次奖励内容
    ,MSG_LUCKREWARDREQ                      // 幸运15关请求操作
    ,MSG_LUCKREWARDACK                      // 错误回应
    ,MSG_LUCKREWARDRESULT                   // 幸运15关摇奖结果

    ,MSG_SHOWTREASUREBOX                    // 通知客户端显示宝箱界面
    ,MSG_TREASUREBOXREQ                     // 
    ,MSG_TREASUREBOXACK                     // 
    ,MSG_TREASUREBOXRESULT                  // [Server:没用 Client:OnMsgTreasureBoxAck]

    ,MSG_OPEN_UI                            // 打开client UI
    ,MSG_INTONATINGOVERTIME                 // 吟唱中被攻击进段打降

    ,MSG_REQFLAGHEADERFROMTEAM              //标记小队队长          // [Server:OnReqFlagHeaderFromTeam代码被注释掉 Client:没用]
    ,MSG_RETFLAGHEADERFROMTEAM              //回答标记小队队长      // [Server:没用 Client:OnRetFlagHeaderFromTeam]

    ,MSG_CHANGE_BAGSIZE                     // 改变背包大小
    ,MSG_CHANGE_INTEGRAL                    // 积分改变             // [没用]
    
    ,MSG_REQEXIT                            // 玩家请求退出游戏     // [没用]
    ,MSG_ACKEXIT                            // 服务器通知玩家进行退出等待       // [没用]
    ,MSG_REQCANCELEXIT                      // 玩家请求取消退出                 // [没用]
    ,MSG_ACKCANCELEXIT                      // 服务器通知玩家退出取消           // [没用]

    ,MSG_MOVE_REDUCE                        // 分解UI的移动
    ,MSG_ACKFORREDUCE                       // 请求分解
    ,MSG_REDUCEOFF                          // 分解好了，告诉CLIENT结果
    ,MSG_CALLREDUCEUI                       // 呼出分解UI               // [Server:没用 Client:OnMsgShowReduceUI]

    ,MSG_ACKGETSHOPCENTER                   // 请求查看商店物品(回答)
    ,MSG_GETSHOPCENTER                      // 请求查看商店物品

    ,MSG_UNSOULBOUND                        // 解除绑定
    ,MSG_CALLUNSOULBOUND                    // 请求解除绑定     // [Server:OnMsgUnSoulBound直接return Client:OnMsgShowUnsoulBoundUI]
    ,MSG_MOVE_UNSOULBOUND                   // 解除绑定移动     // [Server:OnMsgMoveUnSoulBound代码被注释掉了 Client:没用]

    ,MSG_RETSHOPCENTERCNT                   // 返回sShop的物品个数
    ,MSG_RELIVENEEDSILVER                   // 需要的银
    ,MSG_FARREPAIRCOSTRMB                   // 请求远程修理的RMB
    ,MSG_GWBURTHEN                          // GAMEWORLD服务器负荷
    ,MSG_CLIENTSHOWMSG                      // 让客户端弹出对话框
    ,MSG_PLAYERMOVINGDATATOSERVER           // 【没用】
    ,MSG_CLOSEITEMFORMIDX                   // 删除客户端指定位置物品 【有用】

    ,MSG_REQ_RMB_OP                         // 玩家人民币操作
    ,MSG_REQ_CHANGESUBACTION                // 客户端请求坐下
    ,MSG_RET_CHANGESUBACTION                // 服务器返回坐下

    ,MSG_SEND_REAL_TIME                     // 发送客户端服务器当前时间
    ,MSG_REQ_RESETTIME                      // Client请求重置Item时间
    ,MSG_RET_RESETTIME                      // 重置Item时间返回
    ,MSG_TELLC_LOCKNUM                      // 告诉C锁的数量        // 【Client有用】

    ,MSG_ALLOCGWID                          // 客户端发送请求连接ID消息
    ,MSG_RECONNECT                          // 客户端发送请求断线重连
    ,MSG_ASKYUANBAOCNT                      // 查询元宝数量         // [Server:OnAskYuanBaoCnt代码被注释了 Client:没用]
    ,MSG_REQYUANBAOCNT                      // 返回元宝数量         // 【Client有用】
    ,MSG_MOVE_LOCKINTENSIFY                 // 移动LOCKINTENSIFY
    ,MSG_LOCKINTENSIFY                        // LOCKINTENSIFY      // 【Client有用】
    ,MSG_CALLLOCKINTENSIFYUI                // LOCKINTENSIFY        // 【Client有用】
    ,MSG_CALLLOCKINTENSIFY                     

    ,MSG_ACK_COMPOUND_NEW                   // 新的请求合成消息
    ,MSG_QUERY_COMPOUND_NEW                 // 返回合成消息
                                               
    ,MSG_REQ_CHANGE_OWNATTRIBUTE            // 请求更改个人特殊属性设置

    ,MSG_CHANGE_BATTLEFLAG                  // 通知更改战场标记     // 【Client有用】 

    ,MSG_TELL_CompoundRateAdd
    ,MSG_TELL_IntensifyRateAdd
    ,MSG_RIGHTCHECK2                        // 登陆检测
                                               
    ,MSG_LOGIN2                             // 登陆检测
    ,MSG_TellShopCenterOffSet               // 告诉商城折扣

    ,MSG_INVITE_INFO                        //邀请信息
    ,MSG_REFER_INVITE_RESULT                //提交邀请结果

    ,MSG_MODIFY_PLAYER_HELP_FLAG            // 玩家泡泡提示标记
    ,MSG_REQ_DELREPUTENAME                  // 删除称号         // [没用]

    ,MSG_ASK_EXECUTE_SCRIPT                 // 请求进行脚本

    ,MSG_SWITCHSUIT                         // 切换套装
    ,MSG_USE_ANGELL                         // 守护天使
    ,MSG_SHOW_HELMET                        // 显示头盔
    ,MSG_ACK_SWITCHSUIT                     // 切换套装
    ,MSG_SHOWTIMETOP                        // 显示倒计时
    ,MSG_SHUTDOWNTIMETOP                    // 关闭倒计时
    ,MSG_Tell_LoginServer_GateOK            // 告诉loginserver gateserver已经分配好了   // 【没用】
    ,MSG_ThunderLoginInfo                   // 迅雷登陆信息                             // 【没用】
                                 
    ,MSG_CHANNELSINFO                       // 频道信息
    ,MSG_SELECTCHANNEL                      // 选择频道 客户端
    ,MSG_SELECTCHANNEL_SS                   // 选择频道 服务器间
    ,MSG_ACK_SWITCHGATE                     // 应答切服了

    ,MSG_CLEANUP_BAG                        // 整理背包
    ,MSG_GETMOUNT                           // 获得坐骑
    ,MSG_OUT_OF_LONGIN_TIME                 // 登录超时

    ,MSG_MOVEGOODSREQ
    ,MSG_MOVEGOODSACK                       // 移动物品的回馈
    ,MSG_CHECKCHEATREQ                      // 检查是否作弊
    ,MSG_CHECKCHEATACK                      // 检查是否作弊
    ,MSG_GETPROCESSLISTREQ                  // 请求获得客户端的进程列表
    ,MSG_GETPROCESSLISTACK                  // 回应进程列表
    ,MSG_REQNUMBERCODE                      // 请求客户端检测图片验证码
    ,MSG_ACKNUMBERCODE                      // 客户端应答图片验证码

    // 称号
    ,MSG_CHANGETITLEREQ                     // 请求改变当前称号
    ,MSG_TELLCURRENTTITLE                   // 通知当前称号
    ,MSG_ADDTITLEREQ                        // 添加称号
    ,MSG_ADDTITLEACK
    ,MSG_REMOVETITLEREQ                     // 删除称号     // [没用]
    ,MSG_REMOVETITLEACK
    ,MSG_TELLTITLELIST                      // 通知称号列表

    ,MSG_UPDATEMOUNT                        // 坐骑更新
	,MSG_CHANGEMOUNTNAME					// 更改坐骑名字
    ,MSG_MAPINFOREADY						// 场景地图信息发全
	,MSG_ACK_RESULT							// 回应信息
    ,MSG_TEAMOUTLINE                        // 队员下线了
    ,MSG_RETURNTO_CHARACTERSERVER           // 返回选人服务器

    ,MSG_TELLPACKAGEACCESS                  // 告诉客户端包裹的权限
    ,MSG_PACKAGEVIEWREQ                     // 客户端请求查看包裹
    ,MSG_PACKAGEVIEWACK                     // 回应包裹内容
    ,MSG_PACKAGEVIEWEND                     // 结束查看包裹
    ,MSG_PICKPACKAGEITEMREQ                 // 客户端请求拾取包裹里的物品
    ,MSG_PICKPACKAGEITEMACK                 // 回应拾取包裹
    ,MSG_PICKPACKAGEITEMBOULTREQ            // 服务器发送的丢筛子请求
    ,MSG_PICKPACKAGEITEMBOULTACK            // 客户端回应的丢筛子
    ,MSG_PICKPACKAGEITEMBOULTNUMBER         // 回传筛子的数量
    ,MSG_PICKPACKAGEITEMNEEDTOASSIGN        // 发消息给队长 需要分配物品
    ,MSG_TELLTEAMASSIGNINFO                 // 告诉新加入的队员队伍的分配信息
    ,MSG_PICKPACKAGEITEMASSIGNREQ           // 队长发出分配请求
    ,MSG_PICKPACKAGEITEMASSIGNACK           // 服务端回应给其他玩家
    ,MSG_TEAMCHANGEASSIGNITEMLEVELREQ       // 客户端请求更换物品分配等级
    ,MSG_TEAMCHANGEASSIGNITEMLEVELACK       // 回应更换物品分配等级
    ,MSG_PACKAGEITEMACCESSREQ               // 请求物品拾取权限
    ,MSG_PACKAGEITEMACCESSACK               // 回应物品拾取权限
    ,MSG_TELLPICKPACKAGEITEM                // 告诉队伍玩家某某某拾取了某物品(只发品质以上物品)
    ,MSG_STORAGEMONEYREQ                    // 请求仓库存钱或者取钱
    ,MSG_STORAGEMONEYACK                    // 回应仓库存钱取钱操作
    ,MSG_USEGOODSTOMOUNT                    // 对坐骑使用物品

    ,MSG_ADDRECIPEACK                       // 添加一个配方

    //好友
    ,MSG_ACK_NOTARIZATION                   // 寻求公证         // [没用]

    ,MSG_GATEACKLOGININFO                   // GateServer回馈
    ,MSG_TELLTEAMINFO                       // 告知玩家在队伍中的信息
    ,MSG_CHANGEPROTECTLOCKTIMEREQ           // 请求更改保护锁时间
    ,MSG_CHANGEPROTECTLOCKTIMEACK           // 返回更改保护锁时间的结果
    ,MSG_BEKICK                             // 你被踢了
    ,MSG_TELLTEAMMEMBERLIST                 // 同步队伍成员列表
    ,MSG_TELLANTIADDICTIONACCOUNTINFO       // 告诉账号在线信息
    ,MSG_ECTYPESTAGETIMEREMAIN              // 时间副本剩余时间
    ,MSG_CLEARSKILLCOLLDOWN                 // 清除技能colldown时间
    ,MSG_TELLCLIENT                         // 客户端显示一句话
    ,MSG_ACCOUNTPOINT                       // 帐号点数
    ,MSG_RECEIVEQUESTREQ                    // 客户端请求接任务
    ,MSG_RETPUBQUESTREQ                     // 刷新酒馆任务请求
    ,MSG_RETPUBQUESTACK                     // 刷新酒馆任务恢复
    ,MSG_CLIENTTEAMINFO                     // 客户端发送消息给服务器请求队伍验证
    ,MSG_TELLGAMESTAGE                      // 通知客户端分段刷怪
    ,MSG_MOVESTARREQ                        // 移星请求
    ,MSG_MOVESTARACK                        // 移星回应
    ,MSG_SUITELEMENTCHECKUPREQ              // 五行套装鉴定请求
    ,MSG_SUITELEMENTCHECKUPACK              // 五行套装鉴定回应
    ,MSG_SUITELEMENTMOVEREQ
    ,MSG_SUITELEMENTMOVEACK
    //,MSG_MONEYITEMEXCHANGEREQ               // 实物兑换请求
    //,MSG_MONEYITEMEXCHANGEACK               // 实物兑换回馈
    ,MSG_SPECIALREPAIRITEMREQ               // 特殊修理
    ,MSG_SPECIALREPAIRITEMACK               // 特殊修理
    ,MSG_TELLREMOVETIMELIMITITEM            // [没用]
    ,MSG_EQUIPUPGRADEREQ                    // 客户端升阶请求
    ,MSG_EQUIPUPGRADEACK                    // 服务器升阶回应结果
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
	,MSG_DELLOGININFO                  // 删除登录许可
    ,MSG_MAILLIST_ACK                  // 邮件列表
    ,MSG_SERVERVERSIONCHECKACK
    ,MSG_JIFENGSHOPITEMSLISTREQ        // 积分商城道具查询
    ,MSG_JIFENGSHOPITEMSLISTACK        // 积分商城道具列表
    ,MSG_JIFENGSHOPITEMSGAIN           // 积分商城道具领取

    ,MSG_TRADESHOPCONFIGREQ            // 金锭商城配置请求
    ,MSG_UPDATETRADESHOPCONFIG         // 金锭商城配置更新
    ,MSG_NOTIFYTRADESHOPCONFIGRECHANGE // 通知金锭商城配置版本
    ,MSG_SERVERSHUTDOWN
    ,MSG_SENDMAILACK                   // 发送邮件回馈
    ,MSG_OPMAILACK                     // 操作邮件回馈
    ,MSG_MOVESTARLEVELUPREQ
    ,MSG_MOVESTARLEVELUPACK
    ,MSG_ITEMCOMPOSEREQ
    ,MSG_ITEMCOMPOSEACK
	//阵营战场消息定义
	,MSG_NOTIFY_BATTLE_KILLNUM     // 通知玩家杀人公告

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
    ,MSG_JIAOZI_CHANGE             // 交子改变
	,MSG_CONSUMESCORE_CHANGE             // 商城积分改变 ，s->c
    ,MSG_QUERYBATTLESIGNUPTIMEREQ
    ,MSG_QUERYBATTLESIGNUPTIMEACK

    ,MSG_TELLHIDESTATUS            // 通知隐身状态
    ,MSG_MOUNTPOTENTIAL            // 坐骑潜力点分配
    ,MSG_MOUNTBREED                // 坐骑繁殖
    ,MSG_MOUNTACKBREED             // 坐骑繁殖
    ,MSG_SETOFFLINEHOOK            // 设置离线挂机
    ,MSG_ACKOFFLINEHOOK            // 返回离线挂机消息
    ,MSG_GETOFFLINEHOOKEXP         // 获取离线挂机经验
                                     
    ,MSG_TELLSERVEREXPMODULUS        
    ,MSG_EQUIPMAINTAINACK          // 装备保值返回消息
    ,MSG_ITEMRECLAIM               // 装备回收
    ,MSG_ITEMRECLAIMACK            // 装备回收返回消息
                                     
    ,MSG_ITEMCOMPOSEGEM            // 宝石升级和洗石剂合成
    ,MSG_ITEMCOMPOSEGEMACK         // 宝石升级和洗石剂合成返回消息
                                     
    ,MSG_REQPRESSKEYSUIT           // 客户端请求一键换装数据
    ,MSG_ALLPRESSKEYSUIT           // 发送全部一键换装数据
    ,MSG_PRESSKEYSUIT              // 设置一键换装
    ,MSG_PRESSKEYSUITACK           // 一键换装回应
    ,MSG_PRESSKEYSUITRENAME        // 更改一键换装名称
    ,MSG_PRESSKEYSUITRENAMEACK     // 更改一键换装名称回应
    ,MSG_EQUIPPRESSKEYSUIT         // 装备一键换装
                                     
    ,MSG_REQACHIEVEDATA            // 客户端请求人物成就数据
    ,MSG_ALLACHIEVEDATA            // 发送所有成就
    ,MSG_UPDATEACHIEVEVAR          // 更新成就进度
    ,MSG_UPDATEACHIEVE             // 更新成就
    ,MSG_REQACHIEVEREWARD          // 请求奖励
    ,MSG_REQACHIEVEREWARDACK       // 请求奖励回应
    ,MSG_REQOFFNPCSHIP             // 请求下npcship
    ,MSG_ONOFFNPCSHIP              // 上下npcship信息
                                     
    ,MSG_LEARNALLSKILL             // 学习所有技能
                                     
    ,MSG_UPDATEMOUNTSTORAGE        // 更新坐骑仓库信息
    ,MSG_MOVESTORAGEMOUNT          // 坐骑仓库操作
    ,MSG_UPDATECHARMOUNT           // 更新人物坐骑信息
    ,MSG_UPDATEQUESTVAR            // 显示队伍的计数变量 【有用】
                                     
    ,MSG_PROTECTPETPOS             // 护送目标位置
                                     
    ,MSG_REQDOUBLEEXP              // 请求双倍经验
    ,MSG_DOUBLEEXPACK              // 响应双倍经验
    ,MSG_OFFLINEFIGHTOPREQ         // 挂机战斗操作请求
    ,MSG_OFFLINEFIGHTOPACK         // 挂机战斗操作回馈

    ,MSG_CHARASSIGNPOTENTIAL       // 人物潜力点分配
    ,MSG_CHARASSIGNPOTENTIALACK    // 人物潜力点分配回馈

	,MSG_TELLLEAVEECTYPE           // 离开副本

    ,MSG_LEARNXINFA                // 学习心法
    ,MSG_CHANGEXINFA               // 心法更改反馈

    ,MSG_REQGOTONDROME             // 请求上坐骑
    ,MSG_REQGOTONDROMEACK          // 请求上坐骑反馈
    ,MSG_REQGOTOFFDROME            // 请求下坐骑
    ,MSG_GOTONOFFDROME             // 上下多人坐骑
	
	,MSG_UNPLAYERLOCKTARGET		   // 非玩家角色锁定目标

    ,MSG_TELLQUESTTIME             // 告诉任务时间
    ,MSG_REQDONEQUEST              // 请求完成任务

    ,MSG_SHOWSIGNATURE             // 显示心情
	
	,MSG_REQTEAMFOLLOW			   // 请求队伍更随
	,MSG_ACKTEAMFOLLOW			   // 回复队伍更随
	,MSG_FOLLOWTEAMMEMBER		   // 跟随这个队友
	,MSG_TEAMMEMBERACK			   // 返回给客户端提示用（拒绝跟随，取消跟随，同意跟随）
	
	,MSG_HEADERCANCELTEAMFOLLOW		// 队长取消队伍跟随
	,MSG_CANCELTEAMFOLLOW			// 取消队伍跟随

    ,MSG_ADDUPDATEPET              // 添加更新宠物
	,MSG_PETCOMPOSE
	,MSG_ADDPETEQUIP
	,MSG_REMOVEPETEQUIP
    ,MSG_CHANGEPETNAME             // 宠物改名
    ,MSG_CHANGEPET                 // 改变宠物状态
    ,MSG_PETPOTENTIAL              // 宠物分配潜力点
    ,MSG_USEGOODSTOPET             // 对宠物使用物品	
    ,MSG_PETSAVVYUP                // 提高宠物悟性
    ,MSG_PETSAVVYUPACK             // 提高宠物悟性反馈
    ,MSG_UPDATEPETCHAR             // 更新宠物的信息
	,MSG_UPDATEPETMODE
	,MSG_SETPETMODE

    ,MSG_PETBREEDREQ               // 请求宠物繁殖
    ,MSG_PETBREEDREQACK            // 宠物繁殖响应
    ,MSG_PETBREEDCHOICE            // 选择繁殖宠物
    ,MSG_PETBREEDCHOICEACK         // 选择繁殖宠物响应
    ,MSG_PETBREEDLOCK              // 锁定宠物
    ,MSG_PETBREEDCANCELLOCK        // 取消锁定宠物
    ,MSG_PETBREEDCONFIRM           // 确认繁殖
    ,MSG_PETBREEDSTATUS            // 操作状态
    ,MSG_PETBREEDFINISH            // 完成繁殖操作
    ,MSG_PETBREEDCANCELREQ         // 取消繁殖操作
    ,MSG_PETBREEDACQUIRE           // 领取宠物
    ,MSG_PETBREEDACQUIREACK        // 领取宠物反馈
    ,MSG_PETREGENERATE             // 宠物重生

	,MSG_DISBANDTEAM				// 解散队伍
	,MSG_MEMBERCOUNTINTEAMFOLLOW	// 通知队长有几个队员在队伍跟随

    ,MSG_PLAYMOVIEREQ              // 发送给客户端播放视频
    ,MSG_PLAYMOVIEACK              // 客户端回应是否开始播放反馈
    ,MSG_MONSTERTYPESTATUSCHANGE
    ,MSG_SAWTALKREQ                // 提交看过对话
    ,MSG_ACHIEVEBROADCAST		   // 成就广播

    ,MSG_STARTEVENT				   // 开始事件
    ,MSG_ENDEVENTREQ			   // 结束事件请求
    ,MSG_ENDEVENT				   // 结束事件

    ,MSG_MAILLISTREQ               // 请求邮件列表
    ,MSG_RECONNECTACK              // 自动重连回馈

    ,MSG_REQIDENTIFYDATA           // 请求图鉴数据
    ,MSG_ALLIDENTIFYDATA           // 所有图鉴数据
    ,MSG_UPDATEPETIDENTIFY         // 更新宠物图鉴

    ,MSG_EQUIPTALISMAN             // 装备法宝
    ,MSG_EQUIPTALISMANACK          // 装备法宝反馈
    ,MSG_UNEQUIPTALISMAN           // 卸载法宝
    ,MSG_UNEQUIPTALISMANACK        // 卸载法宝反馈
    ,MSG_TALISMANCHANGE            // 法宝改变

	,MSG_TELLCLIENT_CANINVITE	   // 玩家级别到达一定程度的时候通知家族族长或者帮主，其可以邀请玩家加入

    ,MSG_PETLEARNSKILL             // 宠物学习技能
    ,MSG_VIEWACTIVEPET             // 查看目标宠物
    ,MSG_VIEWACTIVEPETACK          // 查看目标宠物反馈

    ,MSG_UPDATEGUIDEREQ            // 更新新手指导
    ,MSG_UPDATEGUIDEACK            // 更新新手指导反馈

    ,MSG_SCENEPLAY                 // 镜头播放
    ,MSG_BLACKSCREEN               // 镜头黑幕

    ,MSG_RIDEROFFDROME             // 主人使某人下多人坐骑
	,MSG_C2G_ASK_BIANSHEN          // 客户端向GAME SERVER请求变身
	,MSG_G2C_REQ_BIANSHEN          // game server告诉客户端变身结果
	,MSG_TELLHEROADDATTR		   // 服务器告诉客户端变身主将所增加的属性

	,MSG_REQ_FLYTOTPHJ			   // 飞到太平幻境
	,MSG_TELLTPHJRANK			   // 通知太平幻境rank
	,MSG_CHANGE_2_BIAOCHE_REQ	   // 玩家请求变身镖车
	,MSG_CHANGE_2_BIAOCHE_ACK	   // 玩家变身镖车的通知
	,MSG_RESTORE_FROM_BIAOCHE_REQ  // 玩家请求从镖车变回人形
	,MSG_RESTORE_FROM_BIAOCHE_ACK  // 玩家变回人形的通知
	,MSG_S2C_PlayerPlayAnim        //服务器通知客户端player做什么动作

	,MSG_TELLRELIVEBUFF			   // 通知客户端复活随机奖励的buff
	//,MSG_TELLC_REASKGATE           // 通知客户端重新请求
	,MSG_SHOW_HEROSUIT             // 是否显示变身后主将的效果
	,MSG_REQ_FIRST_LIMITINFO       // 第一进入游戏更新全部的封印信息
	,MSG_ACK_LEVELUP               // 客户端请求升级
	,MSG_ACK_ACTIVELIMIT           // 客户端请求激活封印
	,MSG_ACK_LIMITINFO             // 客户端请求封印信息
	,MSG_GS2C_LIMITDONE            // 通知客户端封印结束

	///////////////////////////////////////////////////////
	,MSG_LOGIN_ACCOUNTINFO         // 客户端请求登录,发送版本以及帐号密码
	///////////////////////////////////////////////////////
	,MSG_ZHUJIANGCOMPOSE            // 主将图鉴合成
	,MSG_ZHUJIANGCOMPOSEACK         // 主将图鉴合成返回消息
	,MSG_REQ_FLYTOKINGDOM           // 请求飞往国家主城
	,MSG_TRANSFER_STAR				// 转星消息
	,MSG_TRANSFER_STAR_ACK			// 转星返回消息
	,MSG_MOUNT_STRENGTHEN			// 坐骑强化
	,MSG_MOUNT_STRENGTHEN_ACK		// 坐骑强化返回
	,MSG_UNBINDEQUIPREQ				// 解绑装备
	,MSG_UNBINDEQUIPACK				// 解绑装备回发
	,MSG_KILLPLAYERNUM				//玩家杀人数
	,MSG_CONKILLPLAYER				// 客户端通告 %d连杀
	,MSG_REMOVEITEMBYBAGTYPE        // 根据背包类型删除物品
	,MSG_ASKFORPRESENT              // 客户端根据SN请求礼品
	,MSG_PROCTIMESTEPACK
	,MSG_REPEATEDLY_PET             // 重复注册副将
	,MSG_PLATFORMERROR				// 平台返回操作错误类型
	,MSG_MONSTERBELONGID
	,MSG_MONSTERNURTUREINFO
	,MSG_SENDMESSAGEEND				//初始化所有数据后的消息
	,MSG_CHANGEMAPTIMESTEPREQ
	,MSG_RANDATTRIBUTE_REQ			//清洗装备随机属性
	,MSG_RANDATTRIBUTE_ACK
	,MSG_TELLCLIENTLEAVETEAM
	,MSG_CHANGEPETDURATION
	,MSG_USEITEM
	,MSG_UPDATECARD					//更新卡牌
	,MSG_RECARDACHIEVE				//申请卡牌成就奖励
	,MSG_RECARDACHIEVE_ACK			//卡牌成就奖励返回
	,MSG_ENTERWORLDCHANGENAMEREQ
	,MSG_OPENBAGSTORAGE
	,MSG_ASKSEVENDAYSDATA			//请求七天乐数据
	,MSG_ASKSEVENDAYSDATA_ACK		//返回七天乐数据
	,MSG_FRESHSEVENDAYSTATE_VAR		//更新七天乐状态
	,MSG_TRIGGERSEVENDAYS			//触发七天乐
	,MSG_ASKSEVENDAYSTASK			//接取七天乐任务
	,MSG_ASKSEVENDAYSTASK_ACK		//接取七天乐任务返回消息
	,MSG_ASKSEVENDAYSREWARD			//领取奖励
	,MSG_CHANGECHANNEL_REQ			//请求切换分线
	,MSG_CHANGECHANNEL_ACK			//返回切换分线
	,MSG_CLEARTEAMMAPREQ
	,MSG_CLEARTEAMMAPACK
	,GS2CS_CLEARTEAMMAPREQ
	,CS2GS_CLEARTEAMMAPREQ
	,GS2CS_CLEARTEAMMAPACK
	,MSG_ASKGETSALARY				//请求军阶俸禄
	,MSG_ASKGETSALARY_ACK			//返回请求军阶俸禄结果
	,MSG_ASKADVANCEMENT				//请求升官
	,MSG_ASKADVANCEMENT_ACK			//返回请求升官结果
	,MSG_SHOWRANKTITLE				//显示军阶
	,MSG_RECONNECT_RESETSTATE       //自动重连后的一些需要设置的状态
	,MSG_HUNTING_REFRESH			//刷新狩猎任务
	,MSG_HUNTING_QUEST				//发送狩猎任务列表
	,MSG_HUNTING_ACCEPT_QUEST		//接取狩猎任务
	,MSG_HUNTING_ASKFORLIST			//索取狩猎任务列表
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
    // MSG_MAX消息用于统计消息总量，以及可以用于判断GetType()是否超出此数进行消息类型非法判断，
    // 如果添加新的消息，则添加在MSG_MAX消息上面
    //------------------------------------------------------------------------
    ,MSG_MAX //总的消息条数 这条放在最后
};

struct MsgReConnect : public Msg
{ // 申请重连
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
{ // 申请重连
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

    char         szAccount[ dr_MaxPlayerName ]; // 账号名

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
    BYTE  action;   // 行为
    GameObjectId targetid; // 目标
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
    GameObjectId  stID1;  // 主动方
    GameObjectId  stID2;  // 被动方
    BYTE           action; // 行为动作
};

struct MsgAskYuanBaoCnt:public Msg      // [结构没用]
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
        ET_ExchangeJinDing, // 兑换金锭
        ET_QueryPoint,      // 查询点数
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
    char szMsg[MAXLENGTH];     //账号名
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
    char   szAccount[dr_MaxPlayerName]; // 账号名
	uint32 dwCharacterId;
	short  stWitchSlot;
};

//登陆时候客户端log提交
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

//登录消息
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
struct MsgPingServer : public Msg       // LOGIN SERVER和CENTER SERVER之间的PING通讯
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
    char   szAccount[32]; // 账号名
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
//	char   szAccount[32]; // 账号名
//	int8   isWallow;	  // 防沉迷
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

//查询服务器推荐的登陆GateServer
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
    char nServerType; // 消息来源服务器类型
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

//登录返回
struct MsgAckLogin:public Msg
{
    enum enumErrorCode
    {
		//eLoginResult_succ = 1,//1、成功
		//eLoginResult_noAccount,//2、账号不存在
		//eLoginResult_errorpasswords,//3、密码错误
		//eLoginResult_servererror,//4、登录验证服务器异常，请稍后再试
		
		ret_succ = 1,					//1、成功
		error_invaliduserorpass,		//错误的用户名或者密码		
		ret_invalidpassword,            //错误的密码
		ret_invalidusername,			//错误的用户名
		error_invalidversion,            //版本不匹配
		ret_alreadyaloginthisaccount,   //已经有一个这个账号得用户在线
		ret_loginfail,                  //登录失败，用户名和密码不匹配，请仔细输入
		ret_secondpwderror,             //二次验证错误
		ret_noactive,                   //帐号未激活
		ret_noservice,                  //服务未开启
		ret_blocked,                    //帐号被锁定
		ret_FullLoad,                   //服务器爆满 by cloud
		ret_FullMac,					
		ret_PwdCardError,				//密保卡输入有误
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
    short stErrorCode;                                //错误码
    //char  szJabberServerName[dr_MaxNameString];        //the jabber server name
    //DWORD  dwJabberServerIP;                        //the jabber server IP address
    //unsigned short uiJabberServerPort;                //the jabber server port
    DWORD dwAccountID;
    __int64 SessionKey;
	uint32 blocktime;//剩余锁定时间
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
struct MsgLoginWait:public Msg      // [当作登录状态分配ID结束的回复用]
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

struct MsgCancelLoginWait:public Msg        // [结构没用]
{
    MsgCancelLoginWait()
    {
        header.dwType = MSG_CANCEL_LOGINWAIT;
        header.stLength = sizeof( *this);
    }
};

//和服务器的正确消息验证
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

//退出
struct MsgExit:public Msg
{
    MsgExit()
    {
        header.dwType = MSG_EXIT;
        header.stLength = sizeof( MsgExit );
		ExitType = ET_ExitGame; //lyh添加退出类型 
    }    

	unsigned short ExitType;
};

//请求移动
struct MsgQueryMove:public Msg
{
    MsgQueryMove()
    {
        header.dwType = MSG_QUERYMOVE;
        header.stLength = sizeof( MsgQueryMove );
		
    }
	
};

//请求移动返回
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

//客户端上传移动路径
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

//某人移动到某位置
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



//某人离开视野
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
{ // 切换地图
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

//客户端载入地图完成
struct MsgMapLoaded:public Msg
{
    MsgMapLoaded()
    {
        header.dwType = MSG_MAPLOADED;
        header.stLength = sizeof( MsgMapLoaded );
        memset( szMacAddress, 0, sizeof( szMacAddress ) );
    }

    char szMacAddress[21];      // 客户端发送MAC地址给服务器
};

//请求显示名字
struct MsgQueryDisplayName:public Msg
{
    MsgQueryDisplayName()
    {
        header.dwType = MSG_QUERYDISPLAYNAME;
        header.stLength = sizeof( MsgQueryDisplayName );
    }
    GameObjectId nWhoId;
};

//返回某个用户的名字
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


//攻击地面，肯定是持续性技能
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

//看见攻击地面，不传回伤害，伤害将在
//计算 伤害时传回
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

//看见攻击地面
/*struct MsgSeeAttackGround:public MsgSeeAttack
{
MsgSeeAttackGround()
{
}
short stWhichSkill;
};*/


//攻击产生的效果，发给攻击发起者
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
    //位置
    short x,y;
    short stWhichSkill;

    short stHPDec;
    //获得的经验值
    short stExpInc;

    //DWORD dwSerialNo;        // 序列号，
    // 击退距离，相对于当前位置
    // 决定使用击退到目标为值的语义
    short stBeatBackTargetX, stBeatBackTargetY;
    short stAttackerX, stAttackerY;
    short stAttackerHand;
};

//旁观者看到发生了攻击
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
    // 击退距离，相对于当前位置
    short stBeatBackTargetX, stBeatBackTargetY;
    short stAttackerX, stAttackerY;
    short stAttackerHand;
};

// 向服务器发送，攻击锁定的目标
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

// 向服务器发送，准备使用技能的消息
struct MsgReadytoUseSpecialSkill:public Msg
{
    MsgReadytoUseSpecialSkill()
    {
        header.dwType = MSG_READYTOUSESPECIALSKILL;
        header.stLength = sizeof( MsgReadytoUseSpecialSkill );
    }
};

// 向服务器发送，使用特殊技能的消息
struct MsgUseSpecialSkill:public Msg
{
    MsgUseSpecialSkill()
    {
        header.dwType = MSG_USESPECIALSKILL;
        header.stLength = sizeof( MsgUseSpecialSkill );
    }
};

// 向客户端发送，同意准备特殊技能的通知
struct MsgAgreeReadytoUseSpecialSkill:public Msg
{
    MsgAgreeReadytoUseSpecialSkill()
    {
        header.dwType = MSG_AGREEREADYTOUSESPECIALSKILL;
        header.stLength = sizeof( MsgAgreeReadytoUseSpecialSkill );
    }
    short shCurPermillage;    //当前的千分率
};

// 向客户端发送，同意使用特殊技能的通知
struct MsgAgreeUseSpecialSkill:public Msg
{
    MsgAgreeUseSpecialSkill()
    {
        header.dwType = MSG_AGREEUSESPECIALSKILL;
        header.stLength = sizeof( MsgAgreeUseSpecialSkill );
    }
};

// 向客户端发送，不能使用特殊技能的通知
struct MsgDisableUseSpecialSkill:public Msg     // [结构没用]
{
    MsgDisableUseSpecialSkill()
    {
        header.dwType = MSG_DISABLEUSESPECIALSKILL;
        header.stLength = sizeof( MsgDisableUseSpecialSkill );
    }
};

// 向服务器发送，锁定目标
struct MsgLockTarget:public Msg
{
    MsgLockTarget()
    {
        header.dwType = MSG_LOCKTARGET;
        header.stLength = sizeof( MsgLockTarget );
        stWho = -1;
    }
    GameObjectId    stWho;                // 攻击的目标
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

    bool        bCharTarget;  // 是角色目标还是位置目标
    GameObjectId     stWho;  // 攻击的目标
    D3DXVECTOR3 vPos;         // 目标的位置
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
// 查询玩家的数据
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

// 请求玩家所有游戏数据
struct MsgQueryAllGameProperty:public Msg
{
    MsgQueryAllGameProperty()
    {
        header.dwType = MSG_QUERYALLGAMEPROPERTY;
        header.stLength = sizeof( MsgQueryAllGameProperty );
    }
    GameObjectId stTargetId;
};

// 确认返回玩家所有游戏数据
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

//调试信息。。。返回判断事件的信息
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

//角色技能升级
struct MsgCharSkillLevelup:public Msg
{
    MsgCharSkillLevelup()
    {
        header.dwType = MSG_CHARSKILLLEVELUP;
        header.stLength = sizeof(MsgCharSkillLevelup);
    }
    unsigned short ustSkillNewLevel ;
    unsigned short ustSkillID       ;
    int64          nUnUsedExp       ;   //当前剩余未使用经验
};

struct MsgCharacterLevelup : public Msg
{ // 客户端请求人物升级
    MsgCharacterLevelup()
    {
        header.dwType   = MSG_CHARLEVELUP;
        header.stLength = sizeof( MsgCharacterLevelup );
    }
};

struct MsgSeeCharacterLevelup : public Msg
{ // 服务器反馈人物升级
    MsgSeeCharacterLevelup()
    {
        header.dwType   = MSG_SEECHARLEVELUP;
        header.stLength = sizeof( MsgSeeCharacterLevelup );
    }
    uint16  nNewLevel   ;   //当前等级
    int64   nUnUsedExp  ;   //当前未使用经验
};

//看到某人身上出现效果
struct MsgCharacterShowEff:public Msg
{
    MsgCharacterShowEff()
    {
        header.dwType = MSG_SHOWEFF;
        header.stLength = sizeof(MsgCharacterShowEff);
    }
    int    iEffID;    //法术效果的编号
};

// 完成任务
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
    bool          bAdditionalEncouragement;                // 告诉客户端是否获得了额外的奖励
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
    DWORD dwSellPrices[eMaxItem];       // 出售价格
    DWORD dwBuyPrices[eMaxItem];        // 收购价格
    short nBuyCounts[eMaxItem];         // 每次最多能出售的数量
	bool bIsItemBound[eMaxItem];		// 是否绑定，只在随身商店用
    short nCount;
};

//----------------------------- 金币转换为银子 -----------------------------
struct MsgGlodCovSilver : public Msg
{
    MsgGlodCovSilver()
    {
        header.dwType = MSG_GLODCOVSILVER;
        header.stLength = sizeof( MsgGlodCovSilver );
        ustCount = 0;
    }
    unsigned short ustCount;        // 更换数量
};


//----------------------------- 金币转换为银子 Ack -----------------------------
struct MsgAckGlodCovSilver : public Msg     // [结构没用]
{
    MsgAckGlodCovSilver()
    {
        header.dwType = MSG_ACKGLODCOVSILVER;
        header.stLength = sizeof( MsgAckGlodCovSilver );
        ustCount = 0;
        ustSilver =0;
    }
    unsigned short ustCount;        // 元宝数量
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
    unsigned short ustCount; // 数量
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
    unsigned short ustCount; // 数量
    bool           bIsBuy;   // 是否是买
    unsigned char  ucItemBagType;
    __int64 nGuid;          // 卖东西的时候把要卖的东西的guid发给服务器
	bool		   bIsPocketShop;	//是否是随身商店，不是的话在服务器要检测距离等
};

struct MsgRetShopCenterItemCnt : public Msg
{

    MsgRetShopCenterItemCnt()
    {
        header.dwType = MSG_RETSHOPCENTERCNT;
        header.stLength = sizeof( MsgRetShopCenterItemCnt );
    }    
    unsigned short ustItemId;
    unsigned short ustCount;    // 剩余数量
};    

struct MsgAckBuyOrSellGoods : public Msg
{
    enum EResult
    {
        error_sucess = 0,
        error_centerbuysuccess,     // 商城购买道具成功
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
    unsigned short ustCount;     // 数量
    bool           bIsBuy;
    unsigned short ustResult;
    bool           bCanUse;
    __int64        n64UseTime;    
    DWORD          dwCurMoney;
    unsigned char  ucItemBagType;
    __int64        nOnlyInt;     // 物品的世界唯一ID
	uint8		   flag;
};

// 移动或删除物品都是用 MsgMoveGoodsReq 消息
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

//-------------------------交换物品-----------------------------by ^^ at [23/10/2006]
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
    short nMountIndex; // 坐骑索引
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
    int8           nEquipWhere ;    // -1为服务器自选 
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
    char          chSelItem; //如果是个选择框，这个是客户端返回选择的，编号
};

struct MsgAckScript : public Msg
{
    enum EScriptInterfaceType
    {
        eNpcDialog  ,   // Dlg      接口
        eAskQuestion,   // Ask      接口
        eCloseDlg   ,   // CloseDlg 接口
        eNpcMainDialog, // MainDlg  接口
    };

    enum ENpcDialogType
    {
        eNDT_AcceptTask , // 接受任务
        eNDT_Description, // 继续对话框 描述
        eNDT_FinishTask , // 完成任务
        eNDT_Close      , // 关闭       关闭对话框
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
    int        iValue ;  // 任务ID
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
// 增加任务说明
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

// 删除任务说明
struct MsgDelMissionIntro:public Msg
{
    MsgDelMissionIntro()
    {
        header.dwType = MSG_DELMISSIONINTRO;
        header.stLength = sizeof( MsgDelMissionIntro );
    }
    char szName[64];
};

// 做动作
struct MsgReqDoAction:public Msg
{
    MsgReqDoAction()
    {
        header.dwType = MSG_REQDOACTION;
        header.stLength = sizeof( MsgReqDoAction );
        stActionId = -1;
        byHoldSeconds = 0;
    };
    short stActionId;            // 动作id
    BYTE byHoldSeconds;            // 动作持续时间，单位秒
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
//************游戏世界群组服务器消息
//通知 连接的服务器是 游戏世界服务器
//MSG_GWDC_ISGWORLD
struct Msg_GWDC_IsGWorld:public Msg
{
    Msg_GWDC_IsGWorld()
    {
        header.dwType = MSG_GWDC_ISGWORLD;
        header.stLength = sizeof( *this );
    }
};
//是 Gate
//MSG_GWDC_ISGATE
struct Msg_GWDC_IsGate:public Msg
{
    Msg_GWDC_IsGate()
    {
        header.dwType = MSG_GWDC_ISGATE;
        header.stLength = sizeof( *this );
    }
};
//是游戏世界的信息
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
    //目前使用游戏世界服务器IP作为GateIP
    //等实现完Gate后，去掉dwGateIP
    //DWORD    dwGateIP;
    int        iOnlineNum;
    int        iOnlineMax;
};
//是GateInfo
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
    //Gate所属游戏世界服务器的名字
    char    szGWorldServerName[ dr_MaxNameString ];
    DWORD    dwGateIP;
    int        iOnlineNum;
    int        iOnlineMax;
};
//*************游戏世界群组和客户端 消息
//发送到客户端的游戏世界的信息
//MSG_GWDC2C_GWORLDINFO
//iOnlineNum = -1 说明服务器目前关闭
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
{ // 请求分配客户数据
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

// header.stID是Gate中分配的临时ID
struct MsgAllocClientAck : public Msg
{
    MsgAllocClientAck()
    {
        header.dwType   = MSG_GW2G_RETALLOCCLIENT;
        header.stLength = sizeof( *this );
    }
    GameObjectId stIDGW; //if( -1 == stIDGW )说明分配失败
};

//该玩家断线，删除客户数据
//MSG_G2GW_DELETECLIENT
struct MsgGateNotifyGameDeleteClient : public Msg
{
    enum EDeleteType
    {
        EDT_NetOffline, // 35秒暂时网络掉线
        EDT_Exit      , // 退出
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
    short stAreaID; // TileId 角色区块
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
//非玩家角色死亡，Gate释放该ID
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
    DWORD    GameWorldId;       //游戏世界的id
};

struct LogMsg_ItemLogMsg:public LogMsg
{
    LogMsg_ItemLogMsg()
    {
        header.dwType = LOGMSG_ITEMLOG;
        header.stLength = sizeof( *this );
    }
    DWORD    ItemId;        //道具的唯一ID
    int      MasterId;      //角色的ID
    int      Position;     //道具所在的位置
    DWORD    ItemEvent;    //道具经历的事件

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

//    向服务器请求玩家角色的数据
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
    char szPlayerName[dr_MaxPlayerName];    //名字
    bool bOnline;            //判定是否在线
    GameObjectId stPlayerId;        //npc的编号
};

//----
//    服务器发送过来的消息通知有人下线了
//----
struct MsgAckFriendLeaveInfo:public Msg     // [结构没用]
{
    MsgAckFriendLeaveInfo()
    {
        header.dwType = MSG_ACKFRIENDLEAVE;
        header.stLength = sizeof(MsgAckFriendLeaveInfo);
        stFriendId = -1;
    }
    GameObjectId stFriendId; //编号
};


struct SOperateStone
{
    short stStoneIndex;
    short stSkillIndex;
    short stPos;
    bool  bMakeSkillAvailable;
};

//请求放置符石
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

//回复放置石头
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

//请求移除符石
struct MsgReqRemoveStone:public Msg
{
    MsgReqRemoveStone( )
    {
        header.dwType = MSG_REQ_REMOVESTONE;
        header.stLength = sizeof(MsgReqRemoveStone);
    }
    SOperateStone removestone;
};

//回复移除符石
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

//请求放置招式片段
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

//回复放置招式片段
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

//请求移除招式片段
struct MsgReqRemoveSubSkill:public Msg
{
    MsgReqRemoveSubSkill( )
    {
        header.dwType = MSG_REQ_REMOVESUBSKILL;
        header.stLength = sizeof(MsgReqRemoveSubSkill);
    }
    SOperateSubSkill removesubskill;
};

//回复移除招式片段
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

//请求升级技能
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

////回复升级技能
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

//试图制造道具
struct MsgReqProduceItem : public Msg
{
    MsgReqProduceItem( )
    {
        header.dwType = MSG_REQ_PRODUCEITEM;
        header.stLength = sizeof(MsgReqProduceItem);
    }
};

//回复制造工具
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

////试图升级装备
//struct MsgReqUpgradeEquip : public Msg
//{
//    MsgReqUpgradeEquip( )
//    {
//        header.dwType = MSG_REQ_UPGRADEEQUIP;
//        header.stLength = sizeof(MsgReqUpgradeEquip);
//    }
//};
//
////回复升级装备
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

//学会了新的技能
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

//获得了新的符石
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
        //PING消息用于确定服务器是否正常，用于确认服务器之间是否需要重连。是属于比较重要类型，不能设为低等级
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
    //是设置账号在线 还是不在线
    bool    bSetOnline;
    short    stAccountNum;
    DWORD    dwAccountIDs[1];
};

struct MsgQueryServerID:public Msg      // [结构没用]
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


struct SSLMSGSendPublicKey:public Msg   // [结构没用]
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

struct SSLMSGSendSessionKey:public Msg      // [结构没用]
{
    SSLMSGSendSessionKey()
    {
        header.dwType = MSG_SSLSendSessionKey;
        header.stLength = sizeof(*this);
    }
    DWORD dwKeyLen;
    BYTE  KeyData[256];
};

struct SSLMSGFinished:public Msg            // [结构没用]
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

//请求改变当前称号
struct MsgChangeTitleReq : public Msg
{
    MsgChangeTitleReq()
    {
        header.dwType = MSG_CHANGETITLEREQ;
        header.stLength = sizeof(*this);
    }

    short nTitleID;
};

//告诉客户端当前称号
//给周围视野内的玩家都会发送这个消息
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
    char szTitleTargetName[dr_MaxPlayerName];   // 夫妻关系( 需要发送给玩家配偶的名字 )
    short nError;                 //错误码
};

//告诉客户端称号列表
struct MsgTellTitleList : public Msg
{
    MsgTellTitleList()
    {
        header.dwType = MSG_TELLTITLELIST;
        header.stLength = sizeof(*this);
        memset(nTitleArray, 0, sizeof(nTitleArray));
    }

    short nCurrentTitleID;          //当前的称号Id
    short nTitleArray[MAX_TITLE_COUNT];
};

//添加一个称号
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
        Add_HasAdvancedTitle,           //已经存在更高级的称号了(已经被取代的)
        Add_Unknow,
    };

    short nTitleID;
    __int64 n64AcquireTime; // 获得称号的时间
    uint32 nActiveTime;     // 称号的有效时间

    short nError;
};

//删除一个称号
struct MsgRemoveTitleReq : public Msg       // [结构没用]
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

struct MsgTellMapNpcInfo:public Msg     //[结构没用]
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
        char chState;    // npc任务相关状态，
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


struct MessageContainer:public Msg      // [结构没用]
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
        MT_COMPOUND = 0        // 合成
        ,MT_REFINE            // 精炼
        ,MT_INTENSIFY        // 强化

        ,MT_MAX
    };
    enum
    {
        MAX_ITEMMAKE_ID = 32
    };

    enum CanEquip
    {
        eHair                //头发
        ,eHelmet            //头盔
        ,eFace                //脸
        ,eArmour            //盔甲
        ,eGlove                //手套
        ,eShoe                //鞋子
        ,elHandItem            //左手物品
        ,erHandItem            //右手物品
        ,eHeadWear            //头饰
        ,eLeftHandShieldPart//盾
        ,eShoulderPart        //护肩
        ,eTrousersPart        //护腿
        //,eAccouterment        
        ,eRing                //戒指
        //,elRing                //戒指
        ,erBangle            //手镯
        ,eNecklace          //项链
        ,eSash              //腰带
        ,eMaxEquip
    };
    struct S_Id
    {
        short stIdBegin;
        short stIdEnd;
    };
    BYTE        m_byNewOrOld;   //新合成还是老的合成（1 = NEW，0 = old）
    int            m_nRate;        // 合成几率
    //BYTE        m_byMakeType;    // 合成/精炼/强化
    S_Id        m_stIDs[IDMaxCount];// 为ID或类型
    int         m_nCreatRuleId[MAX_ITEMMAKE_ID];    //配方ID
    BYTE        m_byCount;        // m_stItems数量
    //float       m_X1;            //生成合成物品数值的系数
    //float       m_X2;            //生成合成物品数值的系数
    //float       m_X3;            //生成合成物品数值的系数
    //float       m_X4;            //生成合成物品数值的系数
    //float       m_Y;            //生成合成物品数值的系数
    //float       m_a;            //生成合成物品数值的系数
    //BYTE        m_nItemType;   //生成物品具体类型
    //BYTE        m_byEquipType; //装备类型武器/装备
    //float       m_fWaste;      //合成的损耗度
    //float       m_X;           //生成合成物品数值的系数
};

struct MsgScriptReqShowQuestDlg : public Msg
{
    enum
    {
        eInfoLengthMax    = 256,

        ShowType_Normal   = 0,
        ShowType_Pub      = 1,       // 显示酒馆任务窗口
        ShowType_Royal    = 2,       // 皇榜任务窗口
        ShowType_ConQuest = 3,       // 征伐任务
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
struct MsgQueryMapNpcList : public Msg      // [结构没用]
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

// 客户端器请求接任务
struct MsgReceiveQuestReq : public Msg
{
    MsgReceiveQuestReq()
    {
        header.dwType = MSG_RECEIVEQUESTREQ;
        header.stLength = sizeof( MsgReceiveQuestReq );
    }

    GameObjectId stNpcID;          // npc的动态ID
    short        stQuestID;        // 接的任务ID
};

// 客户端请求刷新酒馆任务
struct MsgResetPubQuestReq : public Msg
{
    MsgResetPubQuestReq()
    {
        header.dwType = MSG_RETPUBQUESTREQ;
        header.stLength = sizeof( MsgResetPubQuestReq );
    }

    GameObjectId stNpcID;          // npc的动态ID
    char         chType;           // 刷新的任务类型
};

// 服务器响应刷新酒馆任务,客户端刷新任务列表
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

    GameObjectId stNpcID;          // npc的动态ID
    char chType;            // 刷新的任务类型
    short stResult;         // 返回的结果          
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

struct MsgCharInfo : public Msg         // [结构没用]
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

struct MsgReqEctypeMapInfo : public Msg     // [结构没用]
{
    MsgReqEctypeMapInfo()
    {
        header.dwType = MSG_REQ_ECTYPEMAP_INFO;
        header.stLength = sizeof(*this);
    }
};

struct MsgReqBackCharaterlistSucess : public Msg    // [结构没用]
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

//改变能量
struct MsgChangePower:public Msg    // [结构没用]
{
    MsgChangePower()
    {
        header.dwType = MSG_CHANGEPOWER;
        header.stLength = sizeof(*this);
    }

    short stPower;
    short stPowerMax;
};
//改变聚气点
struct MsgChangePowerPoint:public Msg       // [结构没用]
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

struct MsgReqCovCorps:public Msg        // [结构没用]
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

struct MsgChangeBattleFlag : public Msg     // 【Client有用】
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

struct MsgRightCheck2:public Msg    // 【Server:没用 Client:使用处被注释掉了】
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

//登录消息2
struct MsgLogin2:public Msg     // 【客户端有用】
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
    char checkkey[64];//一次性给最大的长度
    bool IsForceLogin;
    MsgCheckPlayerEnterWorld checkplayer;
};

// 修改玩家泡泡提示标记位
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

// 请求进行脚本
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

struct MsgTellLS_GS_OK : public Msg     // 【结构没用】
{
    MsgTellLS_GS_OK()
    {
        header.dwType = MSG_Tell_LoginServer_GateOK;
        header.stLength = sizeof( MsgTellLS_GS_OK );
    }
    short stGwId;
    char szUserName[ dr_MaxPlayerName ];
};

// 切换自定义套装
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

// 使用守护天使
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
    
    char nServerType;        // 服务器类型
    unsigned long nServerId; // 服务器Id
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

//游戏世界相关的数据
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
        eYouAreGuildMaster = 1<<16,    // 公会会长不能在选人界面删除
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
    uint32  dwDelTimes;     // 剩余时间(单位秒)
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
	BYTE byAddtion;		//是否花费金钱并加个buf，用于随机奖励完美复活时
    BYTE byBornPos;
};

//物体进入视野
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
    unsigned short ustItemId;           //包裹id
    unsigned short ustItemCount;

    ////这两个先做预留
    //int nHoldType;                      // 类型, 个人, 队伍 , 或者公会, 以后可能会有更多
    //int nHoldID;                        // id
    //bool bCheckByHoldID;                // 是否由有用的ID来判断

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

//效果进入视野
struct MsgEffectEnterMySight:public Msg
{
    MsgEffectEnterMySight()
    {
        header.dwType = MSG_EFFECTENTERMYSIGHT;
        header.stLength = sizeof( MsgEffectEnterMySight );
    }
    unsigned int nMapID;
    float x,y;    
    unsigned short ustSkillID;    //使用的技能
    unsigned short ustSkillLevel;    //技能的等级
    DWORD dwLastTime;            //持续的时间
	long  MasterID;          //主人id
};

//建筑进入我的视野
struct MsgBuildingEnterMySight:public Msg
{
    MsgBuildingEnterMySight()
    {
        header.dwType = MSG_BUILDINGENTERMYSIGHT;
        header.stLength = sizeof( *this );
    }
    short x,y;
    char    cDir;
    //建筑ID
    unsigned short ustBuildingTypeID;
    //所属国家
    char    cCountry;
    //建设进度 [0,100] 100为完成的建筑
    char    cBuildingPercent;
};

struct MsgPickItem:public Msg
{
    MsgPickItem()
    {
        header.dwType = MSG_PICKITEM;
        header.stLength = sizeof( MsgPickItem );
    };
    //位置
    short x,y;
    //物品的角色ID
    GameObjectId stItemCharID;
};

struct MsgGetItem:public Msg    // [结构没用,MsgGetItem2]
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

// 创建单人队伍
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

    char szTeamName[ dr_MaxPlayerName ];// 队伍名称
	uint8 AssignMode;					// 队伍分配模式
	uint8 AssignItemLevel;				// 队伍分配等级
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
//    队伍相关的消息
//-----------------------------------------------------------------
//客户端发送消息给服务器,请求邀请某玩家
struct MsgRequestTeam : public Msg
{
    MsgRequestTeam()
    {
        header.dwType = MSG_REQUESTTEAM;
        header.stLength = sizeof( MsgRequestTeam );
    };
    //char szNewbie[ dr_MaxNameString ];
    DWORD dwNewbieID;                      //需要加入队伍的目标id ..加入队伍的人的id。在head.stID
    char szNewbieName[dr_MaxPlayerName];   //如果远程组队 如好友组队 通过名字
    uint8 AssignMode;
    uint8 AssignItemLevel;                 // 队伍分配等级
};

struct MsgAckJoinTeam : public Msg
{
    enum EConstDefine
    {
        error_targetalreadyinTeam          //目标已经在队伍中 组队失败
        ,error_cannotfindtarget            //没有找到目标 也许目标已经掉线
        ,error_Corpsisfull                 //团队已经满了 
        ,error_Teamisfull                  //队伍已经满了
        ,error_sys                         //组队失败
        ,error_assignmode                  //分配模式以改，组队失败 
        ,error_targetcancel                //目标拒绝
         ,error_targetrequesting           //目标正在被邀请中..
        ,error_RequestOnlyHeader
        ,error_succeed
        ,error_people_jointeam             //告诉队长 %s 加入队伍
        ,succeed_upgrade                   //提升队长成功
        ,error_upgrade                      
        ,error_inPlayerBlacklist           //在对方黑名单中
        ,error_teamnoexist                 // 队伍已经不存在
        ,error_headerischange              // 队长已经改变了
        ,error_inMyBlacklsit               // 在自己黑名单中
        ,error_notsamecountry              // 不同国家不能组队
		,error_notonline				   // 玩家在离线摆摊
		,success_addTeam				   // 成功加入队伍
    };

    MsgAckJoinTeam()
    {
        header.dwType = MSG_ACKJOINTEAM;
        header.stLength = sizeof( MsgAckJoinTeam );
        memset( name, 0, sizeof(name) );
    }

    short stError;
    char  name[dr_MaxPlayerName];          //邀请队员的名字
};

struct MsgInquireTeamHeader : public Msg   // [结构没用]
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

struct MsgAckInquireTeamHeader : public Msg     // [结构没用]
{
    MsgAckInquireTeamHeader()
    {
        header.dwType = MSG_ACKINQUIRETEAMHEADER;
        header.stLength = sizeof( MsgAckInquireTeamHeader );

        memset( szJoinMenName,0,sizeof(szJoinMenName) );
    }
    bool    bAgree; //是否同意
    DWORD   dwJoinMenID;
    char    szJoinMenName[dr_MaxPlayerName];
};

//邀请队员组队
struct MsgInquireInvitee : public Msg
{
    MsgInquireInvitee()
    {
        header.dwType = MSG_INQUIREINVITEE;
        header.stLength = sizeof( MsgInquireInvitee );

        memset( szReqName,0,sizeof(szReqName) );
    }
    DWORD dwReqID;                        //请求者id
    char  szReqName[dr_MaxPlayerName];    //请求者的名字
    
    uint8 chProfession;                   // 请求者职业
    uint16 stLevel;                       // 等级

    uint8 AssignMode;
    uint8 AssignItemLevel;           // 队伍分配等级
    bool  IsCorps;
	uint8 nSex;							// 性别
};

//被邀请队员的回答
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
        result_teamisfull,              //申请的队伍已满
    };
    MsgAckInquireInvitee()
    {
        header.dwType = MSG_ACKINQUIREINVITEE;
        header.stLength = sizeof( MsgAckInquireInvitee );

        memset( name, 0, sizeof(name) );
    }
    uint8 bAgree;                                
	DWORD dwReqID;                //邀请组队时是队长的id, 申请入队是是申请人的id
    char  name[dr_MaxPlayerName];    //邀请组队时是队长的名字,否则是申请人的名字

    uint8 AssignMode;
    uint8 AssignItemLevel;           // 队伍分配等级
};

//c->s 表示退出队伍
//s->c 表示客户退出队伍
struct MsgExitTeam : public Msg
{
    MsgExitTeam()
    {
        header.dwType = MSG_EXITTEAM;
        header.stLength = sizeof( MsgExitTeam );
        bIsDisband = false;
    }
    bool bIsDisband;                // ture = 队伍解散
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

// 解散队伍
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
    char szHostName[ dr_MaxPlayerName ];    //队长的名字
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
    int     nFaceId;    //预留脸部的Id
	int		nHairId;	//头发Id
    int     nHeadPicId; //头像图标
    short   shSex;
    char szName[ dr_MaxPlayerName ];        //名字

    bool bIsNewAdd;                 //是否新加入的队员
    bool bOnline;                   // 是否在线
};

struct MsgClientTeamInfo : public Msg       // 客户端请求服务器队伍信息同步
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
    unsigned int dwTeamMemberID[ECD_MaxCount];          // 自己的ID不用发送过来
    void AddTeamMemberID( unsigned int dwID )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        dwTeamMemberID[nCount++] = dwID; 
    }
};

struct MsgDeleteTeamMember:public Msg        //告诉其他玩家有人退出退伍
{
    MsgDeleteTeamMember()
    {
        header.dwType = MSG_DELETETEAMMEMBER;
        header.stLength = sizeof( MsgDeleteTeamMember );
    }
    //short stWhichTeamSlot;        //那个成员插曹的成员退出
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
        int nFaceId;    //预留脸部的Id
        int nHairId;
        int nHeadPicId;
        short stSex;
    };

    unsigned int dwTeamHeaderID;        // 队长ID
    int nCount;                         // 有几个队员
    TeamMemberInfo xMemberInfo[TeamMaxManipleMember];

    void AddTeamMemberInfo( TeamMemberInfo& xMember )
    {
        if ( nCount >= TeamMaxManipleMember )
        { return; }

        xMemberInfo[nCount++] = xMember; 

        header.stLength += sizeof( TeamMemberInfo ); 
    }
};

// 队长请求队伍更随
struct MsgReqTeamFollow : public Msg
{
	MsgReqTeamFollow()
	{
		header.dwType = MSG_REQTEAMFOLLOW;
		header.stLength = sizeof( MsgReqTeamFollow );
	}
};

// 队员回复队伍更随
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


// 通知客户端跟随的队友
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

// 队长取消队伍跟随
struct MsgHeaderCancelTeamFollow : public Msg
{
	MsgHeaderCancelTeamFollow()
	{
		header.dwType = MSG_HEADERCANCELTEAMFOLLOW;
		header.stLength = sizeof( MsgHeaderCancelTeamFollow );
	}
};

// 取消队伍跟随
struct MsgCancelTeamFollow : public Msg
{
	MsgCancelTeamFollow()
	{
		header.dwType = MSG_CANCELTEAMFOLLOW;
		header.stLength = sizeof( MsgCancelTeamFollow );
	}
};

// 通知队长有几个队员在队伍跟随
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
    unsigned short stModelID;   // 模型的编号
};


//切换地图
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

//装备改变 // [结构没用]
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
{ // 某NPC进入视野
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
    bool          bShow         ;   // 是否是显示状态
    char          szTitleName  [dr_MaxPlayerName];
    int           npcId         ;
    uint8         nTypeStatus   ;   // 怪物的类型状态
	bool		  bIsCanRide    ;   // 是否能上
	uint32		  BelongID		;
	uint32		  ModeID		;   // 当前的模型ID 具有优先级 0的时候不读取
};

////某NPC进入视野  （向某个方向移动）
//struct MsgNPCEnterMySightMovingAStep:public MsgNPCEnterMySight
//{
//    MsgNPCEnterMySightMovingAStep()
//    {
//        header.dwType = MSG_NPC_ENTERMYSIGHTMOVINGASTEP;
//        header.stLength = sizeof( MsgNPCEnterMySightMovingAStep );
//    }    
//};

////改变怪物的移动模式
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

//某角色进入视野
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

    //角色的一些持续状态，如:
    //死亡，坐下等
    enum ECharStatus
    {   
        charstatus_normal_drawin, // 普通收刀状态
        charstatus_normal_draw  , // 普通拔刀状态
        charstatus_sitdown      , // 坐下
        charstatus_death        , // 死亡
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
	int8       familyPosition;		// 在家族中的位置
    uint32     dwPlayerCharacterID; // 玩家的游戏角色ID
    float      fMoveRate;
    float      fNormalAttackRate;
    int16      shDromeId;
	uint16	   nMountLevel;
    uint8      nDromePos;
    uint16     nDriverId;
    int16      stAction;
    uint8      bySubAction;
    uint32     nActionPlayTime;     // 动作播放结束时间
    int32      nHp, nHpMax;
    int32      nMp, nMpMax;
    uint8      fight_status;        // 战斗模式
    uint8      sex;                 // 性别
    uint8      profession;          // 职业
    int16      stLevel;             // 等级
    uint8      ucCharStatus;
    uint16     nCurrentTitleID;                     // 当前的称号
    int8       szTitleTargetName[dr_MaxPlayerName]; // 关系称号附带的名字
    uint32     teamId;                              // 队伍Id
    int8       teamPosition;                        // 队伍职位
    uint8      nPKMode;                             // 玩家的模式
    int32      nPKValue;                            // 玩家的PK值
    uint32     nMapID;                              // 玩家的地图ID
    uint8      influence;                           // 阵营
    uint8      uchCountryID;                        // 国家
    uint8      uchCountryTitle;                     // 国家称号
               
    // VisualInfo
    uint16     stVisualItemID    [ EEquipPartType_MaxEquitPart ];
    uint8      equipIntensifyTime[ EEquipPartType_MaxEquitPart ];
    uint8      equipLevel        [ EEquipPartType_MaxEquitPart ];
    uint8      equipElements     [ EEquipPartType_MaxEquitPart ];
    uint16     hairId;              // 头发模型Id
    uint16     faceId;              // 脸部模型Id
	uint8	   defaultModelIndex;   // 裸体模型索引
    uint16     headPicId;           // 头像图标Id
    uint16     talismanId;          // 法宝ID
    uint8      showFlag;            // EShowFlagType
    float      fModelPercent;       // 模型比例
    uint8      npcShipPos;          // 在大坐骑上的位置
    bool       bIsFlyMoving ;       // 是否飞行
    char       szSignature      [RelationDefine::MaxSignLength];    // 个性签名
	uint16     hero_id;				//变身主将ID
	//bool       isBiaocheState;		//是否是变身镖车状态
	short	   shRankTitleId;		//军阶Id
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

////某NPC进入视野  （向某个方向移动）
//struct MsgPlayerEnterMySightMovingAStep:public MsgPlayerEnterMySight
//{
//    MsgPlayerEnterMySightMovingAStep()
//    {
//        header.dwType = MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP;
//        header.stLength = sizeof( MsgPlayerEnterMySightMovingAStep );
//    }    
//    //BYTE byDir;    
//};

//向某个方向移动
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
// 移动中玩家位置改变的消息
struct MsgPlayerMovingPos:public Msg
{
    MsgPlayerMovingPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOS;
        header.stLength = sizeof(MsgPlayerMovingPos);
    }
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};

// 客户端向服务器端发送移动中玩家位置改变的消息
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
    // 人物所在的坐标
    D3DXVECTOR3 vPos;

    char bNeedChangeMap; // 0 1
};

///////////////////////////////////////////////////
// 移动中玩家位置和朝向改变的消息
struct MsgPlayerMovingPosAndDir:public Msg
{
    MsgPlayerMovingPosAndDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVINGPOSANDDIR;
        header.stLength = sizeof(MsgPlayerMovingPosAndDir);
    }
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};

// 客户端向服务器端发送移动中玩家位置和朝向改变的消息
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
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
    char bNeedChangeMap; // 0 1
};

///////////////////////////////////////////////////////////////
// 原地不动玩家的位置消息
struct MsgPlayerPos:public Msg
{
    MsgPlayerPos()
    {
        header.dwType = MSG_PLAYERPOS;
        header.stLength = sizeof(MsgPlayerPos);
    }
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};

// 客户端向服务器端发送原地不动玩家的位置消息
struct MsgPlayerPosToServer:public Msg
{
    MsgPlayerPosToServer()
    {
        header.dwType = MSG_PLAYERPOSTOSERVER;
        header.stLength = sizeof(MsgPlayerPosToServer);
    }
    DWORD        dwSendTime;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};

//////////////////////////////////////////////////
// 原地不动玩家的朝向消息
struct MsgPlayerDir:public Msg
{
    MsgPlayerDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERDIR;
        header.stLength = sizeof(MsgPlayerDir);
    }
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;

    //这里传的位置信息是给Gate上用来判定转发消息的范围的
    D3DXVECTOR3 vPos;
};

// 客户端向服务器端发送原地不动玩家的朝向消息
struct MsgPlayerDirToServer:public Msg
{
    MsgPlayerDirToServer()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERDIRTOSERVER;
        header.stLength = sizeof(MsgPlayerDirToServer);
    }
    DWORD        dwSendTime;
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;

    //这里传的位置信息是给Gate上用来判定转发消息的范围的
    D3DXVECTOR3 vPos;
};

//////////////////////////////////////////////////////////////////////
// 原地不动玩家的位置和朝向消息
struct MsgPlayerPosAndDir:public Msg
{
    MsgPlayerPosAndDir()
    {
        header.dwType = MSG_PLAYERPOSANDDIR;
        header.stLength = sizeof(MsgPlayerPosAndDir);
    }
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};

// 客户端向服务器端发送原地不动玩家的位置和朝向消息
struct MsgPlayerPosAndDirToServer:public Msg
{
    MsgPlayerPosAndDirToServer()
    {
        header.dwType = MSG_PLAYERPOSANDDIRTOSERVER;
        header.stLength = sizeof(MsgPlayerPosAndDirToServer);
    }
    DWORD        dwSendTime;
    // 人物的面朝方向
    char chDirX;
    char chDirY;
    char chDirZ;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
};


///////////////////////////////////////////////////////////////
// 搭乘移动的目标点
struct MsgHitchMoveTargetPos:public Msg
{
    MsgHitchMoveTargetPos()
    {
        header.dwType = MSG_HITCHMOVETARGETPOS;
        header.stLength = sizeof(MsgHitchMoveTargetPos);
    }
    D3DXVECTOR3 vTargetPos;
};

// 玩家能否控制的移动
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

// 向服务器玩家的移动消息
struct MsgPlayerMoving:public Msg
{
    enum
    {
        eNotMoving = 0,                        // 不在移动
        eMovingForward,                        // 直线向前移动
        eMovingForwardLeft,                    // 左侧向前移动
        eMovingForwardRight,                // 右侧向前移动
        eMovingLeft,                        // 向左平移
        eMovingRight,                        // 向右平移
        eMovingCountermarchLeft,            // 左侧后退移动
        eMovingCountermarchRight,            // 右侧后退移动
        eMovingCountermarch,                // 后退移动
        eMovingTypeMax                        // 最大的移动消息类型数
    };

    MsgPlayerMoving()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERMOVING;
        header.stLength = sizeof(MsgPlayerMoving);
    }
    // 人物的面朝方向
    D3DXVECTOR3 vDir;

    // 人物所在的坐标
    D3DXVECTOR3 vPos;

    // 人物移动的方式
    short shMovingType;
};

// 向服务器发送曾移动到某点的信息
struct MsgMovedToPos:public Msg         // [结构没用]
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

// 进入隐形状态
struct MsgTurnIntoHide:public Msg       // [结构没用]
{
    MsgTurnIntoHide()
    {
        header.dwType = MSG_TURNINTOHIDE;
        header.stLength = sizeof(MsgTurnIntoHide);
    }
};

// 离开隐形状态
struct MsgAppearFromHide:public Msg         // [结构没用]
{
    MsgAppearFromHide()
    {
        header.dwType = MSG_APPEARFROMHIDE;
        header.stLength = sizeof(MsgAppearFromHide);
    }
};

// 发送技能提示消息
struct MsgUseSkillHintMessage:public Msg
{
    enum
    {
        eOutAttackRangeHint = 0            // 没有在攻击距离内
        ,eUnfaceToTarget                   // 没有面朝目标
        ,eNoEnoughHpToUseSkill             // 没有足够的Hp来使用技能
        ,eNoEnoughMpToUseSkill             // 没有足够的Mp来使用技能
        ,eNoEnoughItemToUseSkill           // 没有携带相应的道具来使用技能
        ,eNoEnoughWeaponToUseSkill         // 没有装备相应的武器来使用
        ,eCannotUsePassivitySkill          // 不能使用被动技能
        ,eCannotUseSkillInCurStatus        // 不能在当前状态下使用技能
        ,eSkillIsInCoolDown                // 技能在CoolDown中
        ,eBannedPK                         // 服务器禁止PK
        ,eServerCannotFindSkill            // 服务器上找不到对应的技能
        ,eSkillTargetNotExist              // 技能的目标不存在
        ,eSkillTargetWrong                 // 错误的技能目标
        ,eTargetNumIsZero                  // 目标的个数为0
        ,eCannotUseSkillWhenMounting       // 骑马中不能使用技能
        ,eCannotUseSkillWhenPrivateShop    // 开个人商店中不能使用技能
        ,eCannotUseSkillInSkillAvailable   // 在SkillAvailable判定技能不能使用
        ,eCannotUseSkillWhenTaskIsnotEmpty // Task不为空，所以不能使用技能
        ,eCannotUsePhysicsSkill            // 当前状态不能使用物理技能
        ,eCannotUseMagicSkill              // 当前状态不能使用魔法技能
        ,eCancelSkill                      // 取消当前使用的技能
        ,eNormal                           // 正常
        ,eNoEnoughFpToUseSkill             // 没有足够的FP来使用技能
        ,eMustInFightState                 // 技能必须在战斗状态
        ,eMustOutFightState                // 技能必须不在战斗状态
        ,eHpLimitError                     // 血量限制
        ,eNoInTargetBack
        ,eNotEnoughVigorToUseSkill         // 没有足够的精力使用技能
        ,eNotEnoughActivityToUseSkill      // 没有足够的活力使用技能
        ,eHaveCapturePet                   // 已经有捕获宠物
        ,eCapturePetFail                   // 捕获宠物失败
        ,eSkillTargetCountError            // 技能目标个数错误
        ,eFormulaResultNotExist            // 结算结果不存在
        ,eSuitNoRight
        ,eTeamSkillCanNotUse               // 队伍技能不能使用
        ,eTeamSkillInCoolDown              // 队伍技能还在CD中
        ,ePetMonsterIsFull                 // 最多只能召唤3只怪
        ,eHurtImmunity                     // 伤害免疫
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

// 发送看见某Char死亡的消息
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
{ // 坐骑改变的信息
    enum EOpType
    {
        EOT_Active,   // 出战
        EOT_UnActive, // 休息
        EOT_Ride,     // 上马
        EOT_Discard,  // 放生
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
	uint16	  nMountLevel;	//坐骑等级
};

// 下坐骑的消息
struct MsgDisDrome:public Msg
{
    MsgDisDrome()
    {
        header.dwType = MSG_DISDROME;
        header.stLength = sizeof(MsgDisDrome);
    }
};

// 下搭乘宠物的消息
struct MsgDisHitch:public Msg
{
    MsgDisHitch()
    {
        header.dwType = MSG_DISHITCH;
        header.stLength = sizeof(MsgDisHitch);
    }
};

// 玩家角色的矫正坐标信息
struct MsgPlayerVerifyPos:public Msg
{
    MsgPlayerVerifyPos()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERVERIFYPOS;
        header.stLength = sizeof(MsgPlayerVerifyPos);
    }
    //// 人物的面朝方向
    //D3DXVECTOR3 vDir;
    // 人物所在的坐标
    D3DXVECTOR3 vPos;
    //// 人物移动的方式
    //short shMovingType;
};

// 玩家角色的改变移动方式的消息
struct MsgPlayerChangeMovingType:public Msg     // [结构没用]
{
    MsgPlayerChangeMovingType()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGTYPE;
        header.stLength = sizeof(MsgPlayerChangeMovingType);
    }
    BYTE ucMovingType;
};

// 玩家改变移动方向
struct MsgPlayerChangeMovingDir:public Msg      // [结构没用]
{
    MsgPlayerChangeMovingDir()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERCHANGEMOVINGDIR;
        header.stLength = sizeof(MsgPlayerChangeMovingDir);
    }
    D3DXVECTOR3 vDir;
};

// 玩家改变移动方向和移动方式
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

// 玩家停在某处
struct MsgPlayerStopSomeWhere:public Msg            // [结构没用]
{
    MsgPlayerStopSomeWhere()
    {
        header.uMsgLevel = level_low;
        header.dwType = MSG_PLAYERSTOPSOMEWHERE;
        header.stLength = sizeof(MsgPlayerStopSomeWhere);
    }
    D3DXVECTOR3 vPos;
};

// 玩家朝着一个方向停在某处
struct MsgPlayerStopSomeWhereAndDir:public Msg      // [结构没用]
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

// 非玩家角色矫正坐标的消息(矫正不移动时候的坐标)
struct MsgUnPlayerVerifyPos:public Msg
{
    MsgUnPlayerVerifyPos()
    {
        //header.uMsgLevel = level_low;
        header.dwType = MSG_UNPLAYERVERIFYPOS;
        header.stLength = sizeof(MsgUnPlayerVerifyPos);
    }
    // 非玩家角色的坐标
    D3DXVECTOR3 vPos;

    // 非玩家角色的朝向
    //D3DXVECTOR3 vDir;

    // 非玩家角色的朝向
    char chDirX;
    char chDirY;
    char chDirZ;
};

// 非玩家移动到某点的消息
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

//// 非玩家角色移动到锁定目标
//struct MsgUnPlayerMovingToLockTarget:public Msg
//{
//    MsgUnPlayerMovingToLockTarget()
//    {
//        header.dwType = MSG_UNPLAYERMOVINGTOLOCKTARGET;
//        header.stLength = sizeof(MsgUnPlayerMovingToLockTarget);
//    }
//    GameCharID LockTargetID;//目标的ID
//    float fKeepDistance;//和目标保持的距离
//};

// 非玩家角色贴近其目标
struct MsgUnPlayerClosingToLockTarget:public Msg
{
    MsgUnPlayerClosingToLockTarget()
    {
        //header.uMsgLevel = level_low;
        header.dwType = MSG_UNPLAYERCLOSINGTOLOCKTARGET;
        header.stLength = sizeof(MsgUnPlayerClosingToLockTarget);
    }
    // 非玩家角色的坐标
    D3DXVECTOR3 vPos;

    //目标的ID
    GameObjectId LockTargetID;
};

//非玩家角色锁定目标
struct MsgUnPlayerLockTarget:public Msg
{
	MsgUnPlayerLockTarget()
	{
		header.dwType = MSG_UNPLAYERLOCKTARGET;
		header.stLength = sizeof(MsgUnPlayerLockTarget);
	}

	//目标的ID
	GameObjectId LockTargetID;
};

//// 保持移动状态并移动到指定点
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

//// 移动到指定点并停下来
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

//发送跳跃信息
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

//发送宠物命令消息
struct MsgPetCommand:public Msg
{
    enum EPetCommandType
    {
        eAttackTarget = 0  //攻击目标
        ,eFollowMe         //跟随自己
        ,eDismiss          //解散
        ,eAttackAI         //主动攻击AI
        ,eDefendAI         //主动防御AI
        ,eCommandAI        //听从命令AI
        ,eUseSkill         //使用技能
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

//发送拔刀信息
struct MsgDrawWeapon:public Msg
{
    MsgDrawWeapon()
    {
        header.dwType = MSG_DRAWWEAPON;
        header.stLength = sizeof(MsgDrawWeapon);
    }
};

//发送收刀信息
struct MsgDrawInWeapon:public Msg
{
    MsgDrawInWeapon()
    {
        header.dwType = MSG_DRAWINWEAPON;
        header.stLength = sizeof(MsgDrawInWeapon);
    }
};

//发送改变方向的信息
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
//固定时间的坐标同步信息
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

///////////////////////////////////建筑消息/////////////////////////////
//请求建造
struct Msg_Building_ReqBuild:public Msg
{
    Msg_Building_ReqBuild()
    {
        header.dwType = MSG_BUILDING_REQBUILD;
        header.stLength = sizeof( *this );
    }
    GameObjectId stBuildingCharID;                        //建筑角色ID
    unsigned short ustTargetBuildingTypeID;        //升级的目标建筑类型ID
};

//请求建造失败
struct Msg_Building_BuildFailed:public Msg
{
    enum enumErrCode
    {
        //未知错误
        err_unknown
        //必须属于某个国家
        ,err_musthascountryfirst
        //不能建造目标建筑        
        ,err_errtarget
        //国家不匹配
        ,err_countrymismatch
        //没钱
        ,err_notenoughmoney
        //早就在修建中
        ,err_alreadybuilding
        //没有城市建造令，造1级主塔时
        ,err_hasnotcitytoken
        //城市还没有建立
        ,err_isnotacitybuilding
    };
    Msg_Building_BuildFailed()
    {
        header.dwType = MSG_BUILDING_BUILDFAILED;
        header.stLength = sizeof( *this );
    }
    char cErrCode;                    //错误代码
};

//建筑进度
struct Msg_Building_BuildStatus:public Msg
{
    //stID;                            //建筑角色ID
    Msg_Building_BuildStatus()
    {
        header.dwType = MSG_BUILDING_BUILDSTATUS;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //升级的目标建筑类型ID
    char cBuildingPercent;            //建筑完成度
};

//建筑被击毁
struct Msg_Building_Destroyed:public Msg
{
    Msg_Building_Destroyed()
    {
        header.dwType = MSG_BUILDING_DESTROYED;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //建筑变成
};

struct Msg_Building_SelfDestroyed:public Msg
{
    Msg_Building_SelfDestroyed ()
    {
        header.dwType = MSG_BUILDING_SELFDESTROYED;
        header.stLength = sizeof( *this );
    }
    unsigned short ustTargetBuildingTypeID;        //建筑变成
};

struct Msg_IntonateStart : public Msg
{ // 开始吟唱条
    Msg_IntonateStart()
    {
        header.dwType = MSG_INTONATESTART;
        header.stLength = sizeof( *this );
        usType = 0;
    }
    unsigned short ustSkillID;    
    char           cSkillLevel;
    //吟唱的目标是否角色
    bool bCharTarget;
    union unionTarget
    {
        GameObjectId ustTargetID;
        struct SPos
        {
            short x,y;
        }pos;
    }target;

    unsigned char usType; // 吟唱条 0:少到多 1:多到少
};

//吟唱完毕
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

//吟唱中断
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

//吟唱中被攻击进段打降
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
        //未知
        reason_unknown
        //找不到目标
        ,reason_invalidtarget
        //不能使用该技能
        ,reason_cannotuseskill
        //目标超出范围
        ,reason_targetoutofrange
        //错误的技能
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
    //处于那个状态
    char            cSkillStatusType;
    //当前服务器的吟唱程度，维持
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
{ // 技能开始冷却
    Msg_Skill_BeginCoolDown()
    {
        header.dwType   = MSG_SKILL_BEGINCOLDDOWN;
        header.stLength = sizeof( *this );
    }

    unsigned short ustSkillID;
    unsigned short ustSkillLevel;

    uint32 dwColdTime; // 最终冷却时间= 技能冷却时间 - 状态减少冷却时间 
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
    bool bHeader2;//小队队长
    bool bHeader;
    unsigned char Profession;
	unsigned char    AssignMode; //分配模式 lrt
};

//MSG_QUERY_CITYSINFO
struct MsgQueryCitysInfo:public Msg     // [结构没用]
{
    MsgQueryCitysInfo()
    {
        header.dwType = MSG_QUERY_CITYSINFO;
        header.stLength = sizeof( *this );
    }
};

struct MsgCityInfo:public Msg       // [结构没用]
{
    MsgCityInfo()
    {
        header.dwType = MSG_CITYINFO;
        header.stLength = sizeof( *this );
    }
    //城市ID
    short stCityID;
    //市长名字
    char  szCityNO1[ dr_MaxNameString ];
    //所属国家
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
    //DWORD    dwTime; //改为在表中配置，此处删除
    int     nShowInfoType;
    BYTE    byAlign;
    char szText[STRING_LEGTH];
};

struct MsgUpdateQuestVar : public Msg   // 更新任务计数变量
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

struct MsgUpdateBank : public Msg       // [结构没用]
{
    MsgUpdateBank()
    {
        header.dwType = MSG_UPDATEBANK;
        header.stLength = sizeof(*this);
    }
    DWORD dwCurMoney;    // 银行当前金额
    DWORD dwMaxMoney;    // 金额上限
    DWORD dwUpgrade;    // 升级所需要的钱,如为0则已是最高级
    DWORD dwPlayerMoney;// 玩家身上的钱
};

struct MsgReqBankTrade : public Msg
{
    enum EOperate
    {
        ePushMoney = 0    // 存钱
        ,ePopMoney        // 取钱
        ,eUpgradeBank    // 升级银行
    };
    MsgReqBankTrade()
    {
        header.dwType = MSG_REQ_BANKTRADE;
        header.stLength = sizeof(*this);
    }
    BYTE    byOperate;
    DWORD    dwMoney;
};

struct MsgAckBankTrade : public Msg     // [结构没用]
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
DSC:定义仓库的消息结构
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
    __int64 nGuid;          // 要移动的物品的GUID
};

// 用来从仓库里拿出物品 同步GUID
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

struct MsgAckStorageMoveItem : public Msg       // [结构没用]
{
    MsgAckStorageMoveItem()
    {
        header.dwType   = MSG_ACK_MOVE_STORAGE_ITEM;
        header.stLength = sizeof(*this);
    }
    BYTE    byResult;    // StorageTradeResult
};

//仓库存钱或者取钱
struct MsgStorageMoneyReq : public Msg
{
    MsgStorageMoneyReq()
    {
        header.dwType = MSG_STORAGEMONEYREQ;
        header.stLength = sizeof(*this);
    }

    enum Operation
    {
        Save = 0,                 // 存钱
        TakeOut,                  // 取钱
    };
    
    GameObjectId nNpcID;                   // 存钱的npcid (判断与该npc的距离, 防止外挂作弊,直接在野外存钱取钱)
    uint8        chOperation;              // 存钱或者取钱操作
    int          dwMoney;                  // 具体的钱的数量
};

//返回存钱或者取钱操作结果
struct MsgStorageMoneyAck : public Msg
{
    MsgStorageMoneyAck()
    {
        header.dwType = MSG_STORAGEMONEYACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwStorageMoney;              // 当前仓库里的钱
    uint32 dwPackageMoney;              // 当前背包里的钱
};

//  物品加锁
struct MsgLockItemReq : public Msg
{
    MsgLockItemReq()
    {
        header.dwType = MSG_LOCK_ITEM;
        header.stLength = sizeof( *this );
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
    __int64 nGuID;          // guid
};

// 加锁成功才回这个消息, 否则不回消息
struct MsgLockItemAck : public Msg
{
    MsgLockItemAck()
    {
        header.dwType = MSG_LOCK_ITEMACK;
        header.stLength = sizeof( *this );
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
    __int64 nGuID;          // guid
};

// 物品解锁 请求服务器开锁, 这个消息只是设置一个解锁时间
struct MsgUnLockItemReq : public Msg
{
    MsgUnLockItemReq()
    {
        header.dwType = MSG_UNLOCK_ITEM;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
    __int64 nGuID;          // guid
};

// 请求解锁成功才回这个消息, 否则不回消息
struct MsgUnLockItemAck : public Msg
{
    MsgUnLockItemAck()
    {
        header.dwType = MSG_UNLOCK_ITEMACK;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
    __int64 nGuID;          // guid

    __int64 n64UnLockTime;  // 解锁以后返回解锁的到期时间 赋值给 StorageInfo::n64UnLockTime
    uint32  nUnLockLeftTime;    // 解锁剩余时间 赋值给 StorageInfo::nUnLockLeftTime
};

// 时间到了, 客户端发送消息给服务器, 要求服务器把锁打开
struct MsgCheckUnLockItemReq : public Msg
{
    MsgCheckUnLockItemReq()
    {
        header.dwType = MSG_CHECKUNLOCK_ITEMREQ;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
    __int64 nGuID;          // guid
};

// 解锁成功才回这个消息, 否则不回消息
struct MsgCheckUnLockItemAck : public Msg
{
    MsgCheckUnLockItemAck()
    {
        header.dwType = MSG_CHECKUNLOCK_ITEMACK;
        header.stLength = sizeof(*this);
    }

    uint8 uchBagType;       // 背包类型 ( 可以是马背包 ,也可以是仓库背包 )
    uint16 ustItemIndex;     // 背包索引
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
    float fMaxHp;   // 修理后的最大装备持久
};

// 特殊修理
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

// 特殊修理
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
        ECD_Success = 0,         // 成功
        ECD_NotItem,             // 没有指定的特修道具
        ECD_NotEnoughMoney,      // 没有足够的钱
        ECD_NotEnoughExploit,    // 没有足够的功勋
        ECD_NotEnoughReputation, // 没有足够的声望
        ECD_NotEnoughGuildOffer, // 没有足够的帮贡
    };

    uint8 chResult;     // 返回结果

    short stEquipIndex;
    __int64 nEquipGuid;

    float fEquipHp;         // 修理完以后装备持久
    uint32 nLeftMoney;      // 剩余多少钱
};

//////////////////////////////////////////////////////////////////////////

// 位置改变信息 将周围的角色移动凑成一个大包发送
struct MsgPosChange : public Msg
{
    enum MaxCharacter
    {
        MAX_CHARACTER = 100 //最多一次性更新50个角色的坐标信息
    };

    MsgPosChange()
    {
        header.dwType = MSG_POSCHANGE;
        header.stLength = 0; //这里一开始只设置长度为0
        nCharNum = 0;
        nIsCompress = 0;
    }
    unsigned char nIsCompress;              // 包是否被压缩
    unsigned char nCharNum;                 // 在这个包里的移动信息的角色数量
    unsigned char szBuff[MAX_CHARACTER*40]; // 整个包的数据buffer，为每个角色预留30个字节存储ID，类型，位置，以及方向之类的信息
};

struct MsgEnterMySightPack : public Msg
{
    enum MaxCharacter
    {
        MAX_CHARACTER = 40 //最多一次性发送40个进入视野消息
    };

    MsgEnterMySightPack()
    {
        header.dwType = MSG_ENTERMYSIGHTPACK;
        header.stLength = 0;
    }

    unsigned char nIsCompress;                  //包是否被压缩
    unsigned char nCharNum;                     //在这个包里的EnterMySight的角色数量
    unsigned char szBuff[MAX_CHARACTER*sizeof(MsgPlayerEnterMySight)];     //整个包的数据buffer，如果不压缩的话，最多的大小
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
    uint16			 hairId;           // 头发模型Id
    uint16			 faceId;           // 脸部模型Id    
    uint8			 showFlag;         // EShowFlagType
    float		     fModelPercent;    // 模型缩放百分比
    SCharItem		 playerequipitem[EEquipPartType_MaxEquitPart];

    // 个人信息资料
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

//---决斗-------------------------------------------------------------
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
        ResultInBlackList    //对方已经加你为黑名单了
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
        AN_MAAT_chooseComeDown,    //索取 
        AN_MAAT_chooseGiveUp,    //放弃
    };
    MsgAckAssginTeam()
    {
        header.dwType = MSG_ACK_ASSIGN_TEAM;
        header.stLength = sizeof( *this );
    }
    int itemid;
    int npcid;
    int choose;        //索取 或者 放弃
};

//发送给新加入的队员当前队伍的分配模式
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

//客户端请求改变队伍分配物品等级
struct MsgChangeAssignItemLevelReq : public Msg
{
    MsgChangeAssignItemLevelReq()
    {
        header.dwType = MSG_TEAMCHANGEASSIGNITEMLEVELREQ;
        header.stLength = sizeof( *this );
    }

    uint8 chAssignItemLevel;
};

//服务器回应队伍物品分配等级给客户端
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

//现在队长直接修改模式,不需要队员同意,下面两条协议暂时不用
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

struct MsgAckChangeAssignModeResult : public Msg        // [结构没用]
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

//告诉客户端该包裹的权限情况
struct MsgTellPackageAccess : public Msg
{
    MsgTellPackageAccess()
    {
        header.dwType = MSG_TELLPACKAGEACCESS;
        header.stLength = sizeof( *this ) - sizeof(dwPickPlayerID);

        nCount = 0;
        memset(dwPickPlayerID, 0, sizeof(dwPickPlayerID));
    }
    
    GameObjectId nItemPackageID;                 //包裹的id

    ////这两个先做预留
    //int nHoldType;                      // 类型, 个人, 队伍 , 或者公会, 以后可能会有更多
    //int nHoldID;                        // id
    //bool bCheckByHoldID;                // 是否由有用的ID来判断

    int nCount;                         // SPickLevelInfo 结构数量
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

// 当分配队员拾取包裹中物品,关闭包裹以后, 玩家收到 MsgTellPackageAccess 消息如果有打开包裹,就发消息来请求物品拾取权限
struct MsgPackageItemAccessReq : public Msg 
{
    MsgPackageItemAccessReq()
    {
        header.dwType   = MSG_PACKAGEITEMACCESSREQ;
        header.stLength = sizeof(*this);
    }

    int nItemPackageID;         // 包裹ID
};

// 回应玩家请求包裹物品拾取权限
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
        uint8 chPickLevel;         //拾取权限
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


//客户端请求查看包裹
struct MsgPackageViewReq : public Msg
{
    MsgPackageViewReq()
    {
        header.dwType = MSG_PACKAGEVIEWREQ;
        header.stLength = sizeof( *this );
    }

    GameObjectId nItemPackageID;             //包裹的ID
};

//服务器回应的包裹中的物品列表
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
        uint8 chPickLevel;         //拾取权限
    };

    GameObjectId nItemPackageID;             // 包裹的ID
    bool bSendViewEnd;              // 传给客户端的变量, ture == 当关闭查看包裹界面时,需要发送一个MsgPackageViewEnd给服务器 (包裹中没东西了不用回)

    int nItemCount;
    PackageItemInfo xPackItem[MaxPackageItemCount];                          // 包裹的物品
    
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

//这是客户端发给服务端的, 当包裹中没有物品要消失的时候,客户端自动关闭,服务端就不发关闭消息了
struct MsgPackageViewEnd : public Msg
{
    MsgPackageViewEnd()
    {
        header.dwType = MSG_PACKAGEVIEWEND;
        header.stLength = sizeof( *this );
    }

    GameObjectId nItemPackageID;
};

//在包裹中请求拾取一个物品
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
    bool bAllPick;                      // 是否全部拾取
};

//发送给客户端拾取了某个物品,包裹列表中删除该物品 (物品添加到包裹有另外一个消息)
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
        Result_Success = 0,         // 拾取成功
        Result_AlreadyPick,         // 已经被拾取
        Result_NoPurview,           // 物品不属于你,无权限拾取
    };

    GameObjectId nItemPackageID;
    __int64 nItemID;
    uint16 nItemCount;              // 拾取了多少个(有可能没有检完);
    int nResult;
};

// 通知队伍中的有效成员,某某某玩家拾取了某物品, (只有品质以上物品才广播)
struct MsgTellPickPackageItem : public Msg
{
    MsgTellPickPackageItem()
    {
        header.dwType = MSG_TELLPICKPACKAGEITEM;
        header.stLength = sizeof(*this);

        memset(szPlayerName, 0, sizeof(szPlayerName));
    }

    char szPlayerName[dr_MaxPlayerName];              // 玩家名字
    SCharItem xItem;                                  // 物品
};

//服务器发送给客户端,要求客户端玩丢筛子游戏
struct MsgPackageItemBoultReq : public Msg
{
    MsgPackageItemBoultReq()
    {
        header.dwType = MSG_PICKPACKAGEITEMBOULTREQ;
        header.stLength = sizeof(*this) - sizeof(xItem);

        nCount = 0;
    }

    GameObjectId nItemPackageID;
    
    int nTimeOut;           // 超时时间 一般为30秒
    
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

//客户端回应的丢筛子消息
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
        Boult_Choose = 0,           // 选择
        Boult_Abandon,              // 放弃
    };

    int nItemPackageID;
    __int64 nItemID;

    int nResult;
};

//筛子的点数 (如果筛子点数相同的两个最大,谁先丢出来,谁得到物品)
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
        uint16 nBoultNumber;   //  == 0 说明此人放弃, 客户端显示应该说是某某某放弃该物品, 超时也算放弃
    };

    GameObjectId nItemPackageID;
    __int64 nItemID;                        // 当前分配的物品
    int32 dwHoldPlayerID;                   // 物品归属玩家 -1时,说明所有人都放弃了,都可以拾取
    bool bRemove;                           // 是否需要在客户端包裹中删除此物品
    int nCount;
    PackageItemBoult xPackageItemBoult[MaxPackageAccessCount];           //所有玩家的筛子点数

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

//发消息给队长,需要他来分配物品归属
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

//发消息给服务器 分配请求
struct MsgPackageItemAssignReq : public Msg
{
    MsgPackageItemAssignReq()
    {
        header.dwType = MSG_PICKPACKAGEITEMASSIGNREQ;
        header.stLength = sizeof (*this);
    }

    int nItemPackageID;
    __int64 nItemID;

    uint32 dwPlayerID;              // 分配给谁(db id)
};

//服务器回应给客户端其他队员,做显示用
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
        Result_Success = 0,     // 成功
        Result_Fail,            // 不在线,跨服, 或者不在有效范围内 ,都失败
    };

    uint8 chAssignResult;
    GameObjectId nItemPackageID;
    uint32 dwPlayerID;                     // 分配给了谁(db id)
    char szPlayerName[dr_MaxPlayerName];   // 分配给了谁(名字)
    bool bRemove;                          // 是否需要在客户端包裹中删除此物品
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
////////////////////////////////建筑消息end///////////////////////////

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
    uint8  nType    ;      //引发吟唱的类型
    uint16 nID      ;      //引发吟唱的物品ID
    int nActionID   ;      //动作ID
    int nStringID   ;      //吟唱条中间显示的字
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
    GameObjectId	activeid;   // 使用技能( 或者物品 )的玩家
};

struct MsgNotifyMail : public Msg
{
    MsgNotifyMail()
    {
        header.dwType = MSG_NOTIFYMAIL;
        header.stLength = sizeof( MsgNotifyMail );
    }

    int8 fromAddressName[ EM_AddressNameSize ]; // 角色名
};

struct MsgSendMailReq : public Msg
{
    enum EConstDefine
    {
        ECD_ToIndex    = 0, // 第一目标在targets数组中的起始下标位置
        ECD_OtherIndex = 1, // 其他抄送在targets数组中的起始下标位置
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

    int8             title  [EM_TileMaxCount];   // 标题
    SMail::SAddress  targets[EM_TargetMaxCount]; // 所有人的地址
    int8             content[EM_MailContentMax]; // 邮件内容
    uint32           money;                      // 钱        附件
    uint8            bagType;                    // 背包类型  附件
    uint16           bagIndex;                   // 背包位置  附件
    __int64          itemBigId;                  // 道具BigId 附件
    uint32           timeStamp;                  // 时间搓
	uint8			 mailType;					 //邮件类型 为1的话是系统邮件 0的话是玩家之间的正常邮件
};

struct MsgSendMailAck : public Msg
{
    enum EResult
    {
        ER_Success,           // 成功
        ER_SystemException,   // 系统繁忙
        ER_TargetNotRelation, // 无关系的人
        ER_TargetNameInvalid, // 目标名字无效
        ER_AddressError,      // 目标不存在
        ER_MoneyNotEnough,    // 钱不够
        ER_MoneyTooMuch,      // 邮寄的钱太多
        ER_AccessoryInvalid,  // 附件无效
        ER_MailProcessing,    // 有邮件在处理
        ER_TileInvalid,       // title不合法
        ER_ContentInvalid,    // Content不合法
		ER_InProtectLockTime, //财产保护时间
    };

    MsgSendMailAck()
    {
        header.dwType   = MSG_SENDMAILACK;
        header.stLength = sizeof( MsgSendMailAck );
        result          = ER_Success;
    }
    
    uint32  result;
    uint32  timeStamp;    // 时间搓
    uint32  currentMoney; // 当前时间
    uint8   bagType;      // 背包类型  附件
    uint16  bagIndex;     // 背包位置  附件
    __int64 itemBigId;    // 道具BigId 附件
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
    uint32 mailId;		// 邮件Id
    uint8  accessory;   // 附件类型
	uint8  bagType;		// 道具类型	
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
    uint32 mailId; // 邮件Id
    uint32 money;
    SMail::SAccessory accessory; // 附件类型
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
        header.stLength = sizeof(MsgReqGraphicCode); // 初始长度为0
        memset( bitsstream, 0, sizeof(bitsstream));
        memset( glyphBuf, 0, sizeof(glyphBuf));
        dwTime          = 0;                         // 给客户端反映的时间
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
        header.stLength = sizeof(MsgReqNumberCode); // 初始长度为0
        memset( bitsstream, 0, sizeof(bitsstream));
        dwTime          = 0;                         // 给客户端反映的时间
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

struct MsgChangeIntegral:public Msg     // [结构没用]
{
    MsgChangeIntegral()
    {
        header.dwType = MSG_CHANGE_INTEGRAL;
        header.stLength = sizeof(*this);
    }
    short stValue;
    short stValueMax;
};

struct MsgReqExit : public Msg      // [结构没用]
{
    MsgReqExit()
    {
        header.dwType = MSG_REQEXIT;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckExit : public Msg      // [结构没用]
{
    MsgAckExit()
    {
        header.dwType = MSG_ACKEXIT;
        header.stLength = sizeof(*this);
        nWaitExitTime = 0;
    }
    unsigned int nWaitExitTime;         //服务器通知客户端需要等待的时间
};

struct MsgReqCancelExit : public Msg        // [结构没用]
{
    MsgReqCancelExit()
    {
        header.dwType = MSG_REQCANCELEXIT;
        header.stLength = sizeof(*this);
    }
};

struct MsgAckCancelExit : public Msg        // [结构没用]
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

    uint32 nInviteId;   // 邀请人id
    char cInviteType; // 邀请类型
    char szMasterName[dr_MaxPlayerName]; // 邀请人
    int  nSn; // 标示码

    union
    {
        char szbuffer[20];
        char szGuildName[33];   // 邀请人公会
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
    char cInviteType;     // 邀请类型
    union 
    {
        char szBuffer[4];
        char cAlsoAddInviter; // 是否也加申请者为好友
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

struct MsgThunderLogininfo : public Msg     // 【结构没用】
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

//告诉客户端。帐号的角色数据读取成功
struct MsgEndAckChar:public Msg
{
    MsgEndAckChar()
    {
        header.dwType = MSG_ENDACKCHAR;
        header.stLength = sizeof(MsgEndAckChar);
    }
};

//返回角色数据（S->C）
struct MsgAckChar:public Msg
{
    MsgAckChar()
    {
        header.dwType = MSG_ACKCHAR;
        header.stLength = sizeof( MsgAckChar );
    }

    //第几个角色
    short           stWhichSlot;
    byte            bIsDel;
    SCharBaseInfo   baseinfo;
    SCharVisual     visual;
    DWORD           dwCharacterID;
    uint32          dwDelTimes;     // 剩余时间(单位秒)
};

struct MsgCreateHeroChar:public Msg
{
    struct SCreateData
    {
        int8    szCharacterName[ dr_MaxPlayerName ];
        uint8   ucHairColorIndex; // 头发颜色的索引        
        uint8   ucHairModelIndex; // 头发模型的索引        
        uint8   ucModelIndex;     // 身体模型的索引
        uint8   ucFaceIndex;      // 角色脸型
        uint8   ucSex;            // 角色性别
        uint8   ucHeadPic;        // 角色的头像
        uint8   usProfession;     // 角色职业
        uint8   ucCountry;        // 国家
        uint8   byMonth;          // 出生月
        uint8   byDay  ;          // 出生日
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

//Luoz add 客户端 创建人物 发来的 检测是否同名消息
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
    unsigned short  nResult; // 需要改为unsigned long 标识不同的服务器情况
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

//把MsgAckEnterWorld消息打包发送
struct MsgAckEnterWorldPack : public Msg
{
    MsgAckEnterWorldPack()
    {
        header.dwType = MSG_ACKENTERWORLDPACK;
        header.stLength = 0;
    }
    unsigned char szBuff[sizeof(MsgAckEnterWorld)];
};

struct MsgAckBackCharaterList:public Msg        // [结构没用]
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
    SValueChanged pAttrChanged[const_iMaxChangeThisMsg]; // 这个只能放在最后
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
        ECD_MaxAssistantItemCount = 3, // 先来三个的
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
    short assistantItemBagIndex[ECD_MaxAssistantItemCount]; // 辅助材料在材料背包中的位置
};

struct MsgAckCompoundNew : public Msg
{ 
    enum EConstDefine
    {
        ECD_MaxAssistantItemCount = 3, // 先来三个的
    };

    enum EResult
    {
        eResultSuccess = 0           // 成功
        ,eResultFaild                // 失败
        ,eResultMaterialUnconformity // 原料不符合
        ,eResultGemIsMaxLevel        // 宝石等级已是最高级
        ,eResultNotEnoughMoney       // 没有足够的金钱
        ,eResultBagFull              // 背包满了
        ,eResultNotInvalidProduct    // 所有材料没有对应的产出
        ,eResultNotEnoughEnergy      // 没有足够的精力
        ,eResultSystemBusy           // 系统繁忙
        ,eResultItemNotExistByIndex  // 制定的Index物品不存在
        ,eResultItemConfigInvalid    // 物品的Config不存在 
        ,eResultItemTypeError        // 物品类型错误 [用挂]
        ,eResultRepeatedIndex        // 重复的下标   [用挂]
        ,eResultPopItem              // 删除物品失败
        ,eResultFindItemException    // 找物品异常
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
    short         assistantItemBagIndex[ECD_MaxAssistantItemCount]; // 辅助材料在材料背包中的位置
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

// 回应切换自定义套装
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

//准备一个const_iMaxMsgSeeDamage的buf来处理消息
//发消息通知客户端有人受到了伤害
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
        short stStatusID;   // 状态id
        short stLevel;      // 状态等级
        SAttTargetResult xResult;   // 状态作用效果
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

//准备一个const_iMaxMsgSeeMAttSize的buf来处理消息
//一个请求攻击只产生一个MsgSeeMAtt
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

    // false: 消息满
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
    
    short stAttackerX, stAttackerY; // 攻击者坐标
    unsigned short ustSkillID;      // 造成伤害的技能的ID
    unsigned short ustSkillLevel;
    DWORD          dwActionTime;    // 时间相关的数据
    DWORD          dwHoldTime;
    bool           bIsCharTarget;   // 该技能是否有攻击的目标
    union unionData
    {
        GameObjectId stID;
        FPos3		  pos;
    }target;
    
    short stResultNum;    
    short stAttackerHand; // 左右手攻击
    SAttTargetResult results[const_iMaxResultNum];
};

//服务器通知客户端，有人施放了一个没有作用到目标的技能
struct MsgCastInefficacySkill:public Msg
{
    MsgCastInefficacySkill()
    {
        header.dwType = MSG_CASTINEFFICACYSKILL;
        header.stLength = sizeof(MsgCastInefficacySkill);
    }

    ////攻击者坐标
    //short stAttackerX, stAttackerY;

    //使用的技能ID
    unsigned short ustSkillID;
    unsigned short ustSkillLevel;

    //时间相关的数据
    DWORD    dwActionTime;
    DWORD    dwHoldTime;

    bool bIsCharTarget;//该技能是否有攻击的目标
    union unionData
    {
        GameObjectId stID;
        FPos3 pos;
    }target;
};

//服务器通知客户端，看到莫人在吟唱  // [结构没用]
struct MsgIntonate:public Msg
{
    MsgIntonate()
    {
        header.dwType = MSG_INTONATE;
        header.stLength = sizeof(MsgIntonate);
        //
        stSkillID = -1;; //使用的技能
        stSkillLevel = 0; //使用的技能级别
        stTagNpcID = -1;        //技能的释放目标
    }
    //
    short stSkillID;    //使用的技能
    short stSkillLevel; //使用的技能级别
    GameObjectId stTagNpcID;    //技能的释放目标
    //
    DWORD dwTime;        //呤唱时间
};
//看到某人释放法术
struct MsgSeeMagicRelease:public Msg
{
    MsgSeeMagicRelease()
    {
        header.dwType = MSG_MAGIC_RELEASE;
        header.stLength = sizeof( *this );
    }
    //
    GameObjectId    stReleaseNpcID;    //法术释放者的ID
    short    stMagicNo;        //释放的法术的编号
    short    stMagicLevel;    //释放的法术的等级
    //如果是需要客户端模拟的法术效果，需要增加一个，对目标造成的结果
    SAttTargetResult    result;
};

// 客户端请求作某个表情动作
struct MsgQueryExpression : public Msg
{
    MsgQueryExpression()
    {
        header.dwType = MSG_EXPRESSION;
        header.stLength = sizeof( MsgQueryExpression );
        stTargetID = -1;
    }
    
    uint16 ustActionID;
    GameObjectId stTargetID;      //  目标ID
};

//看到某人在作一个动作
struct MsgAckExpression : public Msg
{
    MsgAckExpression()
    {
        header.dwType = MSG_ACKEXPRESSION;
        header.stLength = sizeof( MsgAckExpression );
        stTargetID = -1;
    }

    // 释放者的ID在header.stID中
    uint16  ustActionID;      //表情动作的编号
    GameObjectId stTargetID;   //  目标ID
};

////物体进入视野
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
// 扣钱
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

// 扣交子
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
{ // 扣钱
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

//商城积分 ，下发给客户端
struct MsgRMBConsumeScore:public Msg
{ // 扣钱
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

//得到物品
struct MsgGetItem2 : public Msg
{
    MsgGetItem2()
    {
        header.dwType = MSG_GETITEM;
        header.stLength = sizeof( MsgGetItem2 );
    };
    enum EResult
    {
        RESULT_SUCCESS,   // 成功
        RESULT_NOSPACE,   // 没有空间
        RESULT_ITEMLOCKED,// 物品加密
        RESULT_UNKNOW
    };

    SCharItem  item;
    EResult    enResult;    // 结果
    uint8      itemSource;  // 装备来源
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

//丢掉鼠标上面的道具
struct MsgDropItem2:public Msg
{
    MsgDropItem2()
    {
        header.dwType = MSG_DROPITEM;
        header.stLength = sizeof( MsgDropItem2 );
    }
    //丢弃的物品的坐标
    float fX, fY;
    unsigned short ustPackIndex;
    unsigned char  ucItemBagType;
};

//返回丢弃物品
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
    short BagType;    //背包类型
    short BagIndex;    //背包里面的索引
    bool  bOverlap; //是否要求叠加
    short stItemNum;//转移物品的数量
}; 

struct MsgRightHitItemBag:public Msg
{
    MsgRightHitItemBag( )
    {
        header.dwType = MSG_RIGHTHITITEMBAG;
        header.stLength = sizeof( MsgRightHitItemBag );
    }
    short BagType;    //背包类型
    short BagIndex;    //背包里面的索引
};

//
struct MsgHitBodyItem:public Msg
{
    MsgHitBodyItem()
    {
        header.dwType = MSG_HITBODYITEM;
        header.stLength = sizeof( MsgHitBodyItem );
    }
    short BodyIndex;    //背包里面的索引
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
    bool          bMessageDialog;   // 是否弹窗提示
    //int64         nUnUsedExp;       // 剩余的人物未使用经验
};

//更新角色背包里面的数据到客户端
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

    unsigned char ucItemBagType; // 类型
    short     stNum;             // 实际上背包的物品数目
    short     stBagIndexBegin;   // 背包开始索引
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

//更新角色快捷方式到
struct MsgUpdateShortCutBag:public Msg
{
    MsgUpdateShortCutBag()
    {
        header.dwType = MSG_UPDATESHORTCUTBAG;
        header.stLength = sizeof( MsgUpdateShortCutBag );
        type = 0; // 背包的类型
        num = 0;  // 实际上道具的数目
    }

    short      type; // 背包的类型
    short      num;  // 实际上道具的数目
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
{ // 更新角色身上的装备数据到客户端
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
{ //更新角色身上的客户端需要知道的二级数据到客户端
    MsgUpdateFightData( )
    {
        header.dwType = MSG_UPDATEFIGHTDATA;
        header.stLength = sizeof( MsgUpdateFightData );
    }

    SCharAttributeUpdate fightData;
};

// 更新玩家状态数据给客户端。
struct SUpdateBuffInfo
{
    uint8  index;          // 下标
    uint16 stStatusID;     // 状态的索引
    uint8  cStatusLevel;   // 状态的等级
    bool   bIsLast;        // 是否最后一个添加的状态
    uint32 dwDurationTime; // 状态持续时间
    bool   bStop;          // 是否是停止
    uint8  lapoverNum   ;  // 叠加次数
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

    uint8 count; // 有效的Buff个数
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
    float       fChangeDir;    //转身 
};
//
//
struct MsgMoveCompoundItem : public Msg         // [结构没用]
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
        eResultSuccess = 0                // 成功
        ,eResultFaild                    // 失败
        ,eResultMaterialUnconformity    // 原料不符合
        ,eResultGemIsMaxLevel            // 宝石等级已是最高级
        ,eResultNotEnoughMoney          //没有足够的金钱
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
        EConstDefine_MaxMaterialCount      = 4,  // 最多四个辅助材料

        EConstDefine_DefaultMaterialIndex  = 0, 
        EConstDefine_SecondMaterialIndex   = 1,
        EConstDefine_ThirdMaterialIndex    = 2,
        EConstDefine_FourthMaterialIndex   = 3,
    };

    enum EEvolveType
    {
        ET_LevelUp      , // 升星
        ET_Identify     , // 鉴定
        ET_ReIdentify   , // 鉴定回炉
        ET_Stiletto     , // 打孔
        ET_Inlay        , // 镶嵌
        ET_Replace      , // 替换
        ET_TakeDown     , // 拆卸
        ET_OpenLight    , // 鎏金
        ET_ReOpenLight  , // 鎏金回炉
        ET_SoulStamp    , // 灵魂铭刻
        ET_Maintain     , // 保值
        ET_MaintainCross, // 跨级保值
        ET_Charm        , // 符文吸蓝
        ET_Amulet       , // 护身符上色
		ET_UnknowIdentify, // 装备未知鉴定
        ET_Max          ,
    };

    struct SMaterial
    { // 辅助材料
        uint8   bagType ; // 所在背包的类型
        uint16  bagIndex; // 所在背包的Index位置
        int64   guid    ; // 材料的guid
        uint16  value   ; // 材料的个数 || 拆卸时候的下标
		uint8	protectStar; //保护的星级
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

    uint8              nEvolveType     ; // 装备操作类型
    uint16             nNormalBagIndex ; // 装备在背包中的Index
    int64              nNormalGuid     ; // 装备的GUID

    SMaterial materials[ EConstDefine_MaxMaterialCount ];    // 原料数组

    // 下面的作废使用上面的 请客户端及时修改
    //uint8   uchLevelupMaterialBagType; // 背包类型
    //uint16  stLevelupMaterialIndex;    // 升星宝石Index
    //__int64 n64LevelupMaterialGuid;    // 升星宝石guid

    //uint8   uchRateMaterialBagType1; // 几率物品背包类型
    //short   stRateMaterialIndex1;    // 提高几率的Index
    //__int64 n64RateMaterialGuid1;    // guid
    //uint16  ustRateMaterialCount1;   // 物品数量

    //uint8   uchRateMaterialBagType2; // 几率物品背包类型  
    //int16   stRateMaterialIndex2;    // 失败保底的几率的Index
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
        e_Succeed               , // 成功
        e_Lost                  , // 失败
        e_ItemNotMatch          , // 装备不匹配
        e_ErrorLevelRep         , // 材料使用等级不正确
        e_IntensifyMax          , // 强化到了最高等级
        e_ItemNotExist          , // 物品不存在
        e_NotEnoughMoney        , // 没有足够的钱
        e_NotEnoughQuality      , // 品质不足
        e_ErrorMaterialItem     , // 错误的材料
        e_ErrorGemItem          , // 错误的宝石
        e_HaveIdentify          , // 已经鉴定过了
        e_ItemCantIdentify      , // 目标道具无法鉴定
        e_BaseRandNotOpen       , // 基本的随机属性还没有开
        e_HaveLiuJin            , // 已经鎏金
        e_NoLiuJin              , // 没有鎏金
        e_MaterialItemLevel     , // 辅助材料等级不够
        e_FashionCanNotEvolve   , // 时装不能强化
        e_NotHaveRateMaterial   , // 缺少材料
        e_ErrorRateMaterialCount, // 材料数量不正确
        e_FullHole              , // 满孔
        e_PreHoleIsExist        , // 前置孔还没有开
        e_HoleNotEnough         , // 孔不够
        e_HoleIndexError        , // 目标孔不对
        e_GemIsNotExist         , // 宝石不存在
        e_BagIsFull             , // 背包已满
        e_GemTakeDownFail       , // 宝石卸载失败
        e_HaveSoulStamp         , // 已经灵魂铭刻
        e_AmuletRandIsFull      , // 护身符蓝色属性已满
        e_HaveSameBaseRand      , // 已有相同蓝色随机属性
		e_InlayIsNotExist       , // 镶嵌符不存在
		e_ErrorInlayItem        , // 错误的镶嵌符
		e_RateBollNotExist		, // 几率宝珠不存在
		e_ErrorRateBoll			, // 错误的几率宝珠
		e_InlaySameTypeGem		, // 不能镶嵌同类型宝石
		e_ErrorUnknowIdentify	, // 未知鉴定错误
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
    uint8     value           ; // 拆卸的时候表示被拆卸的宝石位
    SCharItem item            ; // e_Succeed 和 e_Lost 会返回道具的属性 ,其他不返回这个结构

    void AddCharItem( SCharItem& xItem )
    {
        item = xItem;
        header.stLength +=  sizeof( SCharItem ) ;
    }
};

struct MsgTellCharVar : public Msg
{ // 0~3000为任务计数变量 3000~6000为任务状态变量 其他的varId暂时没有 公会计数未来会加
    struct SCharVar
    {
        short varId   ; // 变量Id
        short varValue; // 变量的值
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

    uint16   varCount               ; // 变量的实际个数
    SCharVar charVars[More_iMaxVars]; // 变量的值
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

    uint8            count; // 变量的实际个数
    SQuestTimeRecord questTimes[ QuestLimitTimeMaxCount]; // 变量的值
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
	unsigned char  ucItemBagType;//指定背包类型
	unsigned char  ucIndex;//指定位置
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

struct MsgMoveIntensifyItem : public Msg    // [结构暂时没用]
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
    uint16 index; // 被拆分物品位置
    int64  guid;  // 被拆分物品guid
};

struct MsgReqReduceItem : public Msg
{ // 先加先删
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
    uint16    index; // 被拆分物品位置
    int64     guid;  // 被拆分物品guid    
    uint8     itemBagType;
    SCharItem product;
};

// 聊天信息
struct MsgChat:public Msg
{
    enum EConstDefine
    {
        Item_Hyber_Cnt_Max = 3
    };

    enum CHAT_TYPE
    {
        CHAT_TYPE_NORMAL			= 1 << 1,    //普通聊天
        CHAT_TYPE_GUILD				= 1 << 2,    //公会聊天
        CHAT_TYPE_TERM				= 1 << 3,    //小队聊天
        CHAT_TYPE_PRIVATE			= 1 << 4,    //私聊
        CHAT_TYPE_MS				= 1 << 5,    //短信
        CHAT_TYPE_GAMEPROMPT		= 1 << 6,    //游戏提示 CHAT_TYPE_GAMEPROMPT
        CHAT_TYPE_BULL				= 1 << 7,    //全服公告 GM 运维
        CHAT_TYPE_SHOUT				= 1 << 8,    //喊话 区域服务器九宫格
        CHAT_TYPE_HIGHSHOUT			= 1 << 9,    //高喊 世界
        CHAT_TYPE_GM				= 1 << 10,   //GM 玩家向GM发送求助信息
        CHAT_TYPE_SHOUT_VIP			= 1 << 11,   //喊话 区域服务器九宫格 用于vip的 迷你小喇叭
        CHAT_TYPE_HIGHSHOUT_VIP		= 1 << 12,   //高喊 区域同全服--     用于vip的 小喇叭
        CHAT_TYPE_BULL_VIP			= 1 << 13,   //全服公告--            用于vip的 麦克风

        CHAT_TYPE_PARTICAL1_VIP		= 1 << 14,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL2_VIP		= 1 << 15,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL3_VIP		= 1 << 16,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL4_VIP		= 1 << 17,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL5_VIP		= 1 << 18,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL6_VIP		= 1 << 19,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL7_VIP		= 1 << 20,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL8_VIP		= 1 << 21,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL9_VIP		= 1 << 22,   //特殊的小道消息 用于vip
        CHAT_TYPE_PARTICAL10_VIP	= 1 << 23,   //特殊的小道消息 用于vip
        CHAT_TYPE_LEAGUE			= 1 << 24,   //联盟聊天
        CHAT_TYPE_PROGRAM_SYSTEM	= 1 << 25,   //程序系统通知
        CHAT_TYPE_FIGHTINFO         = 1 << 26,   //战斗信息
        CHAT_TYPE_BATTLE            = 1 << 27,   // 战场阵营频道
        CHAT_TYPE_COUNTRY           = 1 << 28,   // 国家频道
		CHAT_TYPE_FAMILY			= 1 << 29,	 // 家族频道
		CHAT_TYPE_COUNTRYOFFICIAL	= 1 << 30,  // 国家官员频道
        //CHAT_MAX
    };

    // 说话人国家或者
    enum ESpeakerType
    {
        EST_None,            // 无
        EST_ZhiZunHuangGuan, // 至尊皇冠用户
    };

    enum HYBERTYPE
    {
        HYBERTYPE_ITEM = 0,		//物品超链接
        HYBERTYPE_SKILL,		//技能超链接
        HYBERTYPE_TASK,			//任务超链接
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

    struct ChatHeader   // 聊天信息头
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

        int    stType;                         // 聊天对象类型
        uint8  uchSpeakCountry;                // 说话人国家ID
        uint8  uchSpeakerTitle;                // 说话人的国家职位
        uint32 dwSpeakPlayerDBID;              // 说话人DBID
        char   szSpeakName[dr_MaxPlayerName];  // 说话人名字
        uint32 dwGuildID;                      // 说话人帮会ID
        char   szToName[dr_MaxPlayerName];     // 对谁说(名字)
        uint32 dwToPlayerDBID;                 // 对谁说(dbid)
        short  stExpressionId;                 // 表情ID
        uint8  speakerPlayerType;              // 聊天类型
    };

    ChatHeader chatHeader;
    bool       bIsRreply;     // 是否是回复消息
    int        nHyberItemCnt;
    int        nStringLen;
    uint8      ehyberType[Item_Hyber_Cnt_Max];
    __int64    onlyId[Item_Hyber_Cnt_Max];
    int        itemId[Item_Hyber_Cnt_Max];
    uint8      type;          // 背包类型
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

    //false: 消息满
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
    //造成伤害的技能的ID
    unsigned short ustSkillID;
    //
    SEffectDamage damages[const_iMaxDamageNum];
};

//房间新建
struct Msg_MiniGame_Gate_Room_Created : public Msg      // [结构没用]
{
    Msg_MiniGame_Gate_Room_Created()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_CREATED;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Created );
    }
    short        stRoomID;    
};

//房间销毁
struct Msg_MiniGame_Gate_Room_Destroyed : public Msg        // [结构没用]
{
    Msg_MiniGame_Gate_Room_Destroyed()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_DESTROYED ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Destroyed );
    }
    short        stRoomID;
};

//进入房间
struct Msg_MiniGame_Gate_Room_In : public Msg       // [结构没用]
{
    Msg_MiniGame_Gate_Room_In()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_IN ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_In );
    }
    short        stRoomID;
};

//离开房间
struct Msg_MiniGame_Gate_Room_Out : public Msg      // [结构没用]
{
    Msg_MiniGame_Gate_Room_Out()
    {
        header.dwType = MSG_MINIGAME_GATE_ROOM_OUT ;
        header.stLength = sizeof( Msg_MiniGame_Gate_Room_Out );
    }
    short        stRoomID;
};

//房间信息
//变长消息
//不能直接定义消息来发送
//要使用一个较大的buffer来组合这个消息
struct Msg_MiniGame_Room_Info : public Msg      // [没用]
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
    //游戏相关的规则信息
    char    szRuleInfo[1];
};

//房间人数改变
struct Msg_MiniGame_Room_NOPChanged : public Msg        // [结构没用]
{
    Msg_MiniGame_Room_NOPChanged()
    {
        header.dwType = MSG_MINIGAME_ROOM_NOPCHANGED;
        header.stLength = sizeof( Msg_MiniGame_Room_NOPChanged );
    }
    char    cNumberOfPeopleInRoom;
};

//玩家信息
struct Msg_MiniGame_PlayerInfo : public Msg         // [结构没用]
{
    Msg_MiniGame_PlayerInfo()
    {
        header.dwType = MSG_MINIGAME_PLAYERINFO ;
        header.stLength = sizeof( Msg_MiniGame_PlayerInfo );
    }
    char    szPlayerName[ dr_MaxPlayerName ];
};

//请求加入房间
struct Msg_MiniGame_Req_InRoom : public Msg         // [结构没用]
{
    Msg_MiniGame_Req_InRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_INROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_InRoom );
    }
    short        stRoomID;
};

//返回加入房间
struct Msg_MiniGame_Ack_InRoom : public Msg     // [结构没用]
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

//请求退出房间
struct Msg_MiniGame_Req_OutRoom : public Msg        // [结构没用]
{    
    Msg_MiniGame_Req_OutRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_OUTROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_OutRoom );
    }
    //short        stRoomID;
};
//返回退出房间
struct Msg_MiniGame_Ack_OutRoom : public Msg        // [结构没用]
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

//创建
//不能直接定义消息来发送
//要使用一个较大的buffer来组合这个消息
struct Msg_MiniGame_Req_CreateRoom : public Msg     // [结构没用]
{
    Msg_MiniGame_Req_CreateRoom()
    {
        header.dwType = MSG_MINIGAME_REQ_CREATEROOM ;
        header.stLength = sizeof( Msg_MiniGame_Req_CreateRoom );

        stRuleInfoSize = 0;
    }
    //最多玩家数
    char        cMaxPlayer;
    //short        stRoomID;

    void    SetRuleInfo( char *szInRuleInfo,int iSize )
    {
        memcpy( szRuleInfo,szInRuleInfo,iSize );
        stRuleInfoSize = iSize;
        header.stLength = sizeof( Msg_MiniGame_Req_CreateRoom ) + iSize;
    }

    short    stRuleInfoSize;
    //游戏相关的规则信息
    char    szRuleInfo[1];
};

//返回创建
struct Msg_MiniGame_Ack_CreateRoom : public Msg     // [结构没用]
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

//房间销毁
struct Msg_MiniGame_Room_Destroyed : public Msg     // [结构没用]
{
    Msg_MiniGame_Room_Destroyed()
    {
        header.dwType = MSG_MINIGAME_ROOM_DESTROYED ;
        header.stLength = sizeof( Msg_MiniGame_Room_Destroyed );
    }
    short        stRoomID;
};


//命令行
//变长
struct Msg_MiniGame_Command : public Msg        // [结构没用]
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

//游戏开始
struct Msg_MiniGame_Start : public Msg      // [结构没用]
{
    Msg_MiniGame_Start()
    {
        header.dwType = MSG_MINIGAME_START;
        header.stLength = sizeof( Msg_MiniGame_Start );
    }
};

struct Msg_MiniGame_TimeFrame : public Msg      // [结构没用]
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

    unsigned char ucItemBagType; // 类型
    short stBagIndexBegin;       // 背包的开始索引
    short stBagIndexEnd;         // 背包的结束索引
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
        Result_Success = 0,     // 学习成功
        Result_AlreadyExist,    // 已经学了
        Result_Full,            // 学满了
        Result_NoThisRecipe,    // 没有这个配方
        Result_Unknow,          // 不知道的
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
    unsigned char chTime;               // 单位:分钟
};

struct MsgChangeProtectLockTimeAck : public Msg
{
    MsgChangeProtectLockTimeAck()
    {
        header.dwType = MSG_CHANGEPROTECTLOCKTIMEACK;
        header.stLength = sizeof( MsgChangeProtectLockTimeAck );
        chResult = Result_Success;
    }

    enum Change_Result          // 返回结果
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
    { // 返回结果
        EKT_None,                 // None
        EKT_AccountKick,          // 被其他账号踢
        EKT_GraphicCodeErrorKick, // 验证错误被踢
        EKT_SystemKick,           // 系统被踢
		EKT_GraphicCodeTimeOut,	  // 验证码超时
        EKT_Hook,                 // 使用外挂
        EKT_Ban,                  // GM
        EKT_ChangeNameKick,       // 改名被踢
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
    unsigned long onlineMinuteTime; // 在线时间
    unsigned long offMinuteTime;    // 线下时间
};


struct MsgEctypeStageTimeRemain : public Msg
{
    MsgEctypeStageTimeRemain()
    {
        header.dwType   = MSG_ECTYPESTAGETIMEREMAIN;
        header.stLength = sizeof( MsgEctypeStageTimeRemain );
    }

    unsigned long dwTimeRemain;         // 以秒为单位
};

// 清空所有的技能cooldown时间
struct MsgClearSkillCollDown : public Msg
{
    MsgClearSkillCollDown()
    {
        header.dwType   = MSG_CLEARSKILLCOLLDOWN;
        header.stLength = sizeof( MsgClearSkillCollDown );

        ustSkillID = InvalidLogicNumber;
    }

    unsigned short ustSkillID;        // 等于 ErrorUnsignedShortID 代表清除所有技能的cd时间
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

    unsigned char chType;            // 显示类型
    unsigned short ustStringID;      // 显示字串的ID
    bool bTile;                      // showinfo 参数
    //unsigned short ustTime;        // showinfo 参数
    unsigned long dwShowInfoType;    // showinfo 参数
    int nCount;                      // 参数数量
    UnionParam xParam[ECD_MaxCount]; // 参数值
    
    void CopyParamData( UnionParam* pParam, int count )
    {
        if ( count >= ECD_MaxCount || pParam == NULL || count == 0 )
        { return; }

        nCount = count;
        memcpy( xParam, pParam, sizeof( UnionParam) * count );
        header.stLength += sizeof( UnionParam ) * count;
    }
};

// 服务器通知客户端这关的奖励, 客户端端弹出界面
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
        ECD_MaxNumber           = 15,   // 最大奖励个数
        ECD_Operator_ShowLuck   = 0,    // 显示摇奖界面
        ECD_Operator_ShowReward = 1,    // 显示领奖界面
    };
    
    unsigned char uchLevel;             // 第几关
    unsigned char uchOperator;          // 操作
    unsigned char uchRewardType;        // 奖励的类型( 是双倍 还是 半倍  或者初始值 )
    int nCount;                         // 奖励个数
    uint8 uchIndex[ECD_MaxNumber];      // 奖励物品的索引
    void AddRewardIndex( uint8 chIndex )
    {
        if ( nCount >= ECD_MaxNumber )
        { return; }

        uchIndex[nCount] = chIndex;
        ++nCount;
    }
};

// 客户端发送过来是否领取奖品还是摇奖 ( 点确定关闭界面的是否 发送ECD_Get ,服务器清除状态 )
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
        ECD_Start = 0,        // 客户端开始
        ECD_Luck  = 1,        // 摇奖
        ECD_Get   = 2,        // 领取奖品
        ECD_Close = 3,        // 客户端关闭窗口
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
        ECD_Start = 0,          // 客户端开始转
        ECD_Close = 1,          // 关闭界面
    };

    unsigned char uchResult;
};

// 服务器通知摇奖结果
struct MsgLuckRewardResult : public Msg
{
    MsgLuckRewardResult()
    {
        header.dwType = MSG_LUCKREWARDRESULT;
        header.stLength = sizeof( MsgLuckRewardResult );
    }

    unsigned char uchLevel;                 // 第几关
    unsigned char uchRewardType;            // 摇奖的结果类型  在 LuckRewardConfig.h里有定义
};


///////////////////////////////////////////////////////////////////////////
// 宝箱相关
struct MsgShowTreasureBox : public Msg      // 客户端显示宝箱界面
{
    MsgShowTreasureBox()
    {
        header.dwType = MSG_SHOWTREASUREBOX;
        header.stLength = sizeof( MsgShowTreasureBox );

        uchOperate = ECD_Type_Init;
    }

    enum EConstDefine
    {
        ECD_Type_Init = 0,      // 初始状态
        ECD_Type_Receive,       // 领取状态
    };

    unsigned char uchOperate;    // 操作类型

    unsigned char ucItemBagType; // 背包类型
    short stIndex;               // 背包索引
    __int64 nGuid;               // 物品guid
    unsigned char uchLevel;      // 宝箱等级
    unsigned char nResultIndex;  // 摇到的宝箱奖励的索引 

};

struct MsgTreasureBoxReq : public Msg      // 客户端请求摇奖
{
    MsgTreasureBoxReq()
    {
        header.dwType = MSG_TREASUREBOXREQ;
        header.stLength = sizeof( MsgTreasureBoxReq );
    }

    enum EConstDefine
    {
        ECD_Type_Luck = 0,      // 摇奖
        ECD_Type_Receive,       // 领取
    };

    unsigned char uchOperate;           // 操作类型

    unsigned char ucBoxItemBagType;     // 背包类型
    short stBoxIndex;                   // 背包索引
    __int64 nBoxGuid;                   // 物品guid

    unsigned char ucKeyItemBagType;     // 背包类型
    short stKeyIndex;                   // 背包索引
    __int64 nKeyGuid;                   // 物品guid
    
};

struct MsgTreasureBoxAck : public Msg      // 服务器回复的一些错误信息
{
    MsgTreasureBoxAck()
    {
        header.dwType = MSG_TREASUREBOXACK;
        header.stLength = sizeof( MsgTreasureBoxAck );
    }

    unsigned char uchError;     // 错误信息
};

struct MsgTreasureBoxResult : public Msg      // 摇奖结果
{
    MsgTreasureBoxResult()
    {
        header.dwType = MSG_TREASUREBOXRESULT;
        header.stLength = sizeof( MsgTreasureBoxResult );
    }

    unsigned char ucItemBagType;  // 背包类型
    short stIndex;                // 背包索引
    __int64 nGuid;                // 物品guid

    unsigned char uchLevel;       // 宝箱等级
    unsigned char uchResultIndex; // 宝箱的第几个奖励

    short nNewItemID;            // 新的物品id
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

    int nLength;    // nLength == 0时 要求客户端自己计算
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

    int nResult;                         // 返回结果就是执行代码的长度
    float fSpeed;                        // 玩家速度
    bool bRideMount;                     // 是否在坐骑上
    char szList[ECD_MaxLength];          // 返回模块列表和进程列表, 用;号隔开
};

struct MsgTellGameStage : public Msg
{
    MsgTellGameStage()
    {
        header.dwType = MSG_TELLGAMESTAGE;
        header.stLength = sizeof( MsgTellGameStage );
    }

    short stStage;      // 下一次执行阶段  -1 表示结束了,没有下次
    short stTotalStage; // 总共多少波
    uint32 dwTime;      // 该阶段持续时间 单位: 秒

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
        ECD_MoveToItem  = 0,  // 转移到移星道具上
        ECD_MoveToEquip = 1,  // 转移到装备上
    };

    char chOperate;         // 转移类型
    char chItemBagType;     // 移星道具背包类型
    short stItemIndex;      // 移星道具背包索引
    __int64 nItemGuid;      // 移星道具guid

    char chEquipBagType;    // 装备背包类型
    short stEquipIndex;     // 装备背包索引
    __int64 nEquipGuid;     // 装备guid
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
        ECD_SuccessToItem = 0,  // 转移到移星道具上成功
        ECD_SuccessToEquip,     // 转移到装备上成功
        ECD_IsNotEquip,         // 不是装备或者武器
        ECD_IsNotMoveStarItem,  // 不是移星道具
        ECD_LessEquipStar,      // 移星道具星级小于装备星级
        ECD_LessEquipLevel,     // 移星道具小于装备等级
        ECD_EquipNotStar,       // 装备或者物品没有星,不能转移
        ECD_MoveStarItemError,  // 已经转移过的移星道具不能再做移星操作
        ECD_LessItemLevel,      // 装备小于移星道具等级
        ECD_ItemNotStar,        // 移星道具没有星, 不能转移
    };

    char chResult;      // 操作结果
    char chStarLevel;   // 操作成功以后, 当前的星级
    bool bBound;        // 操作成功以后, 是否为绑定装备
};

struct MsgMoveStarLevelUpReq : public Msg
{
    MsgMoveStarLevelUpReq()
    {
        header.dwType = MSG_MOVESTARLEVELUPREQ;
        header.stLength = sizeof( MsgMoveStarLevelUpReq );
    }

    uint16 ustItemIndex;            // 移星石背包索引
    __int64 n64ItemGuid;            // 移星石GUID

    uint8 uchItemBagType1;          // 必须使用的材料背包类型
    uint16 ustMaterialIndex1;       // 必须使用的材料的索引
    __int64 n64MaterialGuid1;
    uint16 ustMaterialCount;        // 使用的材料个数

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
        ECD_Failed,              // 升级失败
        ECD_ErrorMoveStarItem,   // 错误的移星石道具
        ECD_ErrorMaterial,       // 错误的材料
        ECD_CanNotLevelUp,       // 该移星石不能升级
        ECD_NotEnoughMoney,      // 没有足够的钱
        ECD_ErrorMaterialCount,  // 错误的材料个数
    };

    uint8 uchResult;

    uint16 ustItemIndex;        // 原始移星石的索引
    __int64 n64ItemGuid;        // 原始移星石的GUID

    uint32 dwCurrentMoney;      // 剩余多少钱
    uint16 ustNewItemID;        // 生成的新的移星石的ID
};

// 五行套装鉴定
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
        ECD_Checkup = 0,        // 鉴定
        ECD_Clear   = 1,        // 清除
    };

    uint8 chOperate;

    uint8 chArmourBagType;      // 背包类型
    short stArmourIndex;        // 背包索引
    __int64 nArmourGuid;        // guid

    uint8 chItemBagType;        // 鉴定道具背包类型
    short stItemIndex;          // 鉴定道具背包索引
    __int64 nItemGuid;          // 鉴定道具guid
};

// 鉴定结果, 
struct MsgSuitElementCheckupAck : public Msg
{
    MsgSuitElementCheckupAck()
    {
        header.dwType = MSG_SUITELEMENTCHECKUPACK;
        header.stLength = sizeof( MsgSuitElementCheckupAck );
    }

    enum EConstDefine
    {
        ECD_CheckupSuccess = 0,    // 鉴定成功
        ECD_ClearSuccess,       // 净化成功
        ECD_NotElement,     // 不是五行套装
        ECD_ElementAlready, // 已经鉴定过的不能鉴定
        ECD_NotEnoughMoney, // 没有足够的钱
        ECD_HaveNotElement, // 没有五行属性, 不能清除
        ECD_ClearCountLimit, // 一天只能清除%d次 枚举在Globaldef.h => ClearElementCount
        ECD_NotCheckupItem,  // 不是鉴定五行的物品
        ECD_NotClearItem,    // 不是清除五行的物品
        ECD_LevelError,      // 物品和装备等级不符
    };

    uint8 chResult;             // 返回结果

    uint8 chArmourBagType;      // 背包类型
    short stArmourIndex;        // 背包索引
    __int64 nArmourGuid;        // guid

    uint8 chElement;            // 鉴定的结果( 金木水火土中的一种 )  这个值和SCharItem 中的 itembase 中的value1 相与 ( value1 | chElement )
    uint32 nLeftMoney;          // 剩下多少钱
};

struct MsgSuitElementMoveReq : public Msg
{
    MsgSuitElementMoveReq()
    {
        header.dwType = MSG_SUITELEMENTMOVEREQ;
        header.stLength = sizeof( MsgSuitElementMoveReq );

        stModulusIndex = -1;
    }

    short stSrcArmourIndex;      // 源装备背包索引
    __int64 n64SrcArmourGuid;    // 源装备guid

    short stDestArmourIndex;     // 目标装备背包索引
    __int64 n64DestArmourGuid;   // 目标装备guid

    uint8 chCheckUpBagType;      // 五行石背包类型
    short stCheckUpIndex;        // 五行石背包索引
    __int64 n64CheckUpGuid;      // 五行石guid

    uint8 chModulusBagType;       // 概率道具背包类型
    short stModulusIndex;         // 概率道具背包索引
    __int64 n64ModulusGuid;       // 概率道具guid
    uint16 ustModulusCount;       // 概率道具数量
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
        ECD_Success = 0,           // 成功
        ECD_Failed,                // 失败
        ECD_EquipNotExist,         // 装备不存在
        ECD_NotHaveElement,        // 没有五行属性, 不能转移
        ECD_NotElement,            // 不是五行套装
        ECD_CanEquipIndexError,    // 两个装备装备部位不一样, 不能转移
        ECD_EquipLevelError,       // 两个装备等级相差太多( 不能由50->70装备上转移 )
        ECD_ErrorElementItem,      // 错误的五行鉴定石
        ECD_ErrorElementItemLevel, // 错误的五行鉴定石等级
        ECD_NotEnoughMoney,        // 没有足够的钱
        ECD_ErrorModulusItem,      // 错误的概率加成材料
        ECD_ErrorModulusItemCount, // 错误的概率加成材料数量
    };

    uint8 uchResult;               // 返回结果 ( 成功以后, 转移源的五行属性和提炼等级 到目标装备上 , 失败时, 只清除源装备 )
    
    uint32 dwCurrentMoney;         // 当前还剩多少钱
    short stSrcArmourIndex;        // 源装备背包索引
    __int64 n64SrcArmourGuid;      // 源装备guid
                                 
    short stDestArmourIndex;       // 目标装备背包索引
    __int64 n64DestArmourGuid;     // 目标装备guid
};


//struct MsgMoneyItemExchangeReq : public Msg
//{ // 实物兑换
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
//{ // 实物兑换
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

struct MsgTellRemoveTimeLimitItem : public Msg      // [结构没用]
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

// 客户端升阶请求
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

    uint16 ustEquipIndex;            // 原始装备的背包索引
    __int64 nEquipGuid;              // 原始装备的guid
    
    uint16 ustUpToEquipID;           // 升阶到装备ID    

    uint16 ustCount;                 // 材料的种类
    uint16 xMaterialID[ECD_MaxCount];  // 升阶用到的所有材料

    void AddMaterial( uint16 ustID )       // 客户端添加一个材料,调用这个函数 ( 必须使用的材料可以不用发送过来 )
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
        ECD_Success = 0,    // 成功
        ECD_ErrorEquip,     // 错误的装备不能升阶
        ECD_CanNotUpgrade,  // 不能升阶到此装备
        ECD_LackMaterial,   // 缺少材料
        ECD_ErrorMaterial,  // 错误的材料
        ECD_NotEnoughMoney, // 没有足够的钱
        ECD_PackageFull,    // 包裹满了
        ECD_IsLocked,       // 被锁定了
        ECD_Unkown,
    };

    uint8 chResult;                                 // 返回结果, 成功以后,服务器删除材料和原始装备,生成新装备
    __int64 nNewEquipGuid;                          // 新装备的GUID, 在normal背包里找到该新装备,下面附上新属性
    bool bIsSoulBounded;                            // 升阶后是否绑定
    uint16 ustRand[SCharItem::EConstDefine_BaseRandMaxCount];      // 升阶后 装备的属性 memcpy_s 给新装备的equipdata.baseRands 数组
    uint32 nElemenet;                               // 升阶后的五行属性     直接赋值给itembaseinfo的value1
};

// 套装提炼请求, 包裹技能套装和五行套装
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

        ECD_SkillSuitLevelUp = 0,    // 技能套装精炼请求
        ECD_ElementSuitLevelUp = 1,  // 五行套装提纯请求
    };

    struct ItemInfo
    {
        uint8 chItemBagType;     // 背包类型
        uint16 stItemIndex;      // 道具的索引
        __int64 nItemGuid;      // 道具的GUID
    };

    uint8 chOperate;            // 操作类型

    uint16 stEquipIndex;        // 普通背包中装备的索引
    __int64 nEquipGuid;         // 装备GUID

    ItemInfo xItemInfo[ECD_ItemCount]; // 技能套装精炼使用1个套装精炼道具, 五行套装提纯使用3个辅助道具( 第1个是提纯道具 第2个是五行鉴定石, 第3个是功勋名望道具 )
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
        ECD_SuccessSkillSuit = 0,  // 技能套装精炼成功
        ECD_SuccessElementSuit,    // 五行套装精炼成功
        ECD_CheckUpFailed,         // 套装精炼失败
        ECD_NotSuitEquip,          // 不是套装装备
        ECD_NotSkillSuitEquip,     // 不是技能套装装备
        ECD_NotElementuitEquip,    // 不是五行套装装备
        ECD_ErrorCheckUpItem,      // 错误的道具
        ECD_NotCheckUpItem,        // 没有道具
        ECD_ErrorItemLevel,        // 道具的等级不足
        ECD_NotEnoughMoney,        // 没有足够的钱
        ECD_AlreadMaxLevel,        // 已经到最大等级了
        ECD_Unkown,
    };

    uint8 uchResult;

    uint32 nLeftMoney;  // 剩余多少钱
    uint32 nValue;      // 成功以后, 这个值直接赋给itembaseinfo 里面的value1
    unsigned short stAttriID;    // 技能套装级联成功以后, 附加的属性的ID, 赋给equipdata的specials对应位置, 看 e_SkillSuitIndex 定义 ( 五行套装这个不要用 )
};

// 套装转化请求, 包裹技能套装和五行套装
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

        ECD_SkillSuitChange = 0,    // 技能套装转化请求
        ECD_ElementSuitChange = 1,  // 五行套装转化请求
    };

    struct ItemInfo
    {
        uint8 chItemBagType;     // 背包类型
        uint16 stItemIndex;      // 道具的索引
        __int64 nItemGuid;      // 道具的GUID
    };

    uint8 chOperate;

    uint16 stEquipIndex;                // 普通背包中装备的索引
    __int64 nEquipGuid;                 // 装备GUID

    ItemInfo xItemInfo[ECD_ItemCount];  // 辅助材料, 技能套装转化( 第一个是转化材料, 第2个是功勋名望道具 ), 五行套装转化 ( 第一个是转化材料, 第2个事五行鉴定石 )
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
        ECD_SuccessChagneSkillSuit = 0,  // 技能套装转化成功
        ECD_SuccessChagneElementSuit,    // 五行套装转化成功
        ECD_ChangeFailed,                // 套装转化失败
        ECD_NotSuitEquip,                // 不是套装装备
        ECD_NotSkillSuitEquip,           // 不是技能套装装备
        ECD_NotElementuitEquip,          // 不是五行套装装备
        ECD_NotCheckUpItem,              // 没有道具
        ECD_ErrorCheckUpItem,            // 错误的转化道具
        ECD_ErrorMaterialItem,           // 错误的功勋材料
        ECD_NotEnoughMoney,              // 没有足够的钱
        ECD_LessEquipLevel,              // 小于装备等级
        ECD_LessSuitLevel,               // 套装精炼等级不够, 不能转化
        ECD_LessItemLevel,               // 转换道具等级不够, 不能转化
        ECD_Unkown,
    };

    uint8 uchResult;
    uint32 nLeftMoney;  // 剩余多少钱
    uint32 nValue;      // 如果技能套装转化成功以后, 这个值是新的装备ItemID( 装备的itembaseinfo.ustItemID = nValue ) , 如果五行套装转化成功以后, 这个值是新的五行元素( 直接赋给itembaseinfo.value1  = nValue )
};

struct MsgOnLineRewardReq : public Msg
{
    MsgOnLineRewardReq()
    {
        header.dwType = MSG_ONLINEREWARDREQ;
        header.stLength = sizeof( MsgOnLineRewardReq );
    }

    uint8 nIndex;     // 第几次的奖励
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
        ECD_Success = 0,    // 成功了
        ECD_TimeLess,       // 在线时间不够
        ECD_Already,        // 已经领过了不能领
        ECD_NormalPageFull,       // 包裹满了
		EDC_MaterialPageFull,
		EDC_TaskBagFull,
        ECD_NotReward,      // 没有这个奖励
    };

    uint8 uchResult;
    uint8 nIndex;     // 第几次的奖励 成功以后客户端自己调用BitValue::SetBitValue设置 SCharLiveInfo::dwRewardItemInfo的值
};

struct MsgBuyBackItemReq : public Msg
{
    MsgBuyBackItemReq()
    {
        header.dwType = MSG_BUYBACKITEMREQ;
        header.stLength = sizeof( MsgBuyBackItemReq );
    }

    uint8 uchIndex;         // 索引
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
        Success = 0,    // 成功
        PackError,      // 客户端回购包裹有错   客户端收到这个错误 发送一次 MsgBuyBackItemListReq 消息请求服务器重新刷一下回购物品列表
        PackFull,       // 包裹满了
        NotEnoughMoney, // 没有足够的钱
    };

    uint8 uchResult;                // 返回结果 买成功了 客户端删除回购背包中相应的物品
    uint8 uchBuyBackPackIndex;      // 索引
    __int64 n64BuyBackPackGuid;     // guid

    uint16 ustBagIndex;             // 放在背包的索引
    uint32 nLeftMoney;              // 剩余多少钱
};

struct MsgBuyBackItemListReq : public Msg
{
    MsgBuyBackItemListReq()
    {
        header.dwType = MSG_BUYBACKITEMLISTREQ;
        header.stLength = sizeof( MsgBuyBackItemListReq );
    }
};

// 回购物品列表
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

// 显示擂台的报名窗口
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

        ShowType_Player = 1,    // 玩家 1 v 1 擂台
        ShowType_Team   = 2,    // 队伍 1 v 1 擂台
        ShowType_Guild  = 3,    // 公会 1 v 1 擂台

        MaxCount = 10,
    };

    struct SignUpInfo   // 擂台的报名信息
    {
        SignUpInfo() : ustMapID( ErrorUnsignedShortID ), ustLevel( 0 ), ustCount( 0 ), ustMaxCount( 0 ), nSignUpLeftTime( 0 ) {}

        uint16 ustMapID;            // 擂台地图
        uint16 ustLevel;            // 擂台等级
        uint32 nSignUpLeftTime;     // 报名剩余时间 ( 单位 : 秒 )
        uint16 ustCount;            // 当前报名人数
        uint16 ustMaxCount;         // 最大允许的报名人数
    };

    GameObjectId stNpcId;                  // npcid
    char    szInfo[eInfoLengthMax];      // 显示内容
    uint8 uchShowType;                   // 擂台的类型
    SignUpInfo xSignUpInfo[MaxCount];    // 如果ustMapID为-1, 跳出循环
};

// 请求报名擂台赛
struct MsgBattleSignUpReq : public Msg
{
    MsgBattleSignUpReq()
    {
        header.dwType = MSG_BATTLESIGNUPREQ;
        header.stLength = sizeof( *this );
    }

    uint8 ustType;          // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
    uint16 ustMapID;        // 请求报名的战场地图id( 预留 以后也许要用 )
    uint16 ustLevel;        // 请求报名的擂台等级
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
        Success        = 0,      // 报名成功
        ErrorTime      = 1,      // 报名时间未到
        AlreadySignUp  = 2,      // 已经报名了
        SignUpFull     = 3,      // 报名人数已经满了
        BattleClosed   = 4,      // 战场已经关闭了
        SignUpLimit    = 5,      // 每天只能参加3次擂台赛
        LevelLimit     = 6,      // 等级不够

        MustHaveTeam   = 7,      // 必须有队伍才能报名
        MustTeamHeader = 8,      // 必须是队长
    };

    uint8 uchResult;        // 返回的结果, 成功的话, 直接传入等待地图
    uint8 uchType;          // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
};

// 通知客户端, 当前参加的擂台玩家报名的数量
struct MsgTellBattleSignUpCount : public Msg
{
    MsgTellBattleSignUpCount()
    {
        header.dwType = MSG_TELLBATTLESIGNUPCOUNT;
        header.stLength = sizeof( *this );

        nStartLeftTime = 0;
    }

    uint32 nStartLeftTime;   // 战场开始的剩余时间

    uint8 uchType;          // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
    uint16 ustMapID;         // 某个擂台
    uint16 ustCount;         // 玩家数量
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

    uint8 uchType;           // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会

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

// 客户端请求报名还要等待多久时间
struct MsgQueryBattleSignUpTimeReq : public Msg
{
    MsgQueryBattleSignUpTimeReq()
    {
        header.dwType = MSG_QUERYBATTLESIGNUPTIMEREQ;
        header.stLength = sizeof( MsgQueryBattleSignUpTimeReq );
    }

    uint8 uchType;           // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
    uint16 ustMapID;
    bool bIsPassSignTime;    // true = 是否过了报名时间  false = 是否到了报名时间
};

struct MsgQueryBattleSignUpTimeAck : public Msg
{
    MsgQueryBattleSignUpTimeAck()
    {
        header.dwType = MSG_QUERYBATTLESIGNUPTIMEACK;
        header.stLength = sizeof( MsgQueryBattleSignUpTimeAck );
        bIsAlreadlySignUp = false;
    }

    uint8 uchType;           // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
    uint16 ustMapID;
    bool bIsAlreadlySignUp;     // 是否已经在报名阶段了
    uint32 dwLeftTime;      // 已经是报名阶段, 这个值是报名剩余时间 否则是 还有多少时间才能报名
};

struct MsgQueryBattleTeamInfoReq : public Msg
{
    MsgQueryBattleTeamInfoReq()
    {
        header.dwType = MSG_QUERYBATTLETEAMINFOREQ;
        header.stLength = sizeof( MsgQueryBattleTeamInfoReq );
    }

    uint16 ustMapID;         // 某个擂台
    uint32 dwTeamID;        // 需要请求的队伍ID
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
        char szName[dr_MaxPlayerName];           // 姓名
        uint8 uchProfession;                     // 职业
        uint16 ustLevel;                         // 等级
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

    uint32 dwMapID;     // 要进入的地图
};

struct MsgEnterTeamBattleAck : public Msg
{
    MsgEnterTeamBattleAck()
    {
        header.dwType = MSG_ENTERTEAMBATTLEACK;
        header.stLength = sizeof( MsgEnterTeamBattleAck );
    }

    bool bEnterStage;           // 是否进入
};

struct MsgLeaveBattleReq : public Msg
{
    MsgLeaveBattleReq()
    {
        header.dwType = MSG_LEAVEBATTLEREQ;
        header.stLength = sizeof( MsgLeaveBattleReq );
    }
    
    uint8 uchType;           // 擂台的类型 1 = 个人  2 = 队伍, 3 = 公会
};

// 通知客户端, 战场成绩
struct MsgTellBattleRecord : public Msg
{
    MsgTellBattleRecord()
    {
        header.dwType = MSG_TELLBATTLERECORD;
        header.stLength = sizeof( MsgTellBattleRecord );
    }

    enum EConstDefine
    {
        Status_Fighting = 1,    // 战斗中
        Status_FightEnd = 2,    // 战斗结束了

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

        int nIntegral;      // 积分;
        int nKillCount;     // 杀人个数
        int nDeathCount;    // 死亡次数
    };

    uint8 uchType;          // 战场类型
    uint8 uchStatus;        // 战场状态

    uint32 dwMapID;         // 客户端判断此mapid, 如果与玩家所在客户端不一样, 不显示
    RecordInfo xRecord[ MaxTeamCount ]; // 战场成绩
};

// 查询队伍的详细积分
struct MsgQueryTeamRecordReq : public Msg
{
    MsgQueryTeamRecordReq()
    {
        header.dwType = MSG_QUERYTEAMRECORDREQ;
        header.stLength = sizeof( MsgQueryTeamRecordReq );
    }

     uint16 ustMapID; 
};

// 回复队伍的详细积分
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

        int nIntegral;      // 积分;
        int nKillCount;     // 杀人个数
        int nDeathCount;    // 死亡次数
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
    uint16 killNum;			//杀人次数
    uint16 beKillNum;		//被杀者 死之前 杀人次数
    char killer[dr_MaxPlayerName];//杀人者
    char beKiller[dr_MaxPlayerName];//被杀者
};


struct MsgWallowAbout: public Msg
{
	enum ENotifyType
	{
		ENotifyType_Init        , // 初始化
		ENotifyType_StatusChange, // 状态变化
		ENotifyType_TimerNotify , // 定时提示
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
	uint8  nStatus    ; // 当前防沉迷状态 值为枚举AntiAddictionState中的值
	uint32 nOnlineTime; // 在线时间
	uint32 nLimitTime ; // 限制时间
	uint8  nType      ; // 是否是变化
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

    char szName[101];        // 服务器名字
    uint16 ustVersion;       // 服务器版本号ID 这里只判断 VERSION_BUILD
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

//// 客户端请求设置2级密码
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
//// 客户端请求重新设置2级密码
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
//// 修改密码结果
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
//        SetPasswordSuccess = 0,         // 设置密码成功
//        ReSetPasswordSuccess,           // 重置密码成功
//        OldPasswordError,               // 原始密码错误
//        PasswordFormatError,            // 密码格式错误
//        AlreadyHavePassword,            // 已经有密码了
//        Unknow,
//    };
//
//    uint8 uchResult;     // 返回结果
//};
//
//// 客户端请求强制清除密码
//struct MsgClearSecondPasswordReq : public Msg
//{
//    MsgClearSecondPasswordReq()
//    {
//        header.dwType   = MSG_CLEARSECONDEPASSWORDREQ;
//        header.stLength = sizeof( *this );
//    }
//};
//
//// 服务器回应强制清除密码
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
//        ClearSuccess = 0,       // 强制清除2级密码请求成功, 3天后自动解锁
//    };
//
//    uint8 uchResult;     // 返回结果
//};
//
//// 服务器发送请求客户端验证2级密码
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
//        OP_InitAction  = 0,     // 无类型判断
//        OP_OpenStorage = 1,    // 打开仓库
//        OP_DelRelation = 2,	   //删除好友
//		OP_HandleAuction = 3,  //打开金锭交易界面
//    };
//
//    uint8 uchOperator;      // 客户端把这个回传给服务器
//
//    uint32 nClearPasswordLeftTime;  // 仓库密码强制解除剩余时间
//};
//
//// 客户端输入密码验证
//struct MsgCheckSecondPasswordAck : public Msg
//{
//    MsgCheckSecondPasswordAck()
//    {
//        header.dwType   = MSG_CHECKSECONDPASSWORDACK;
//        header.stLength = sizeof( *this );
//        memset( szPassword, 0, sizeof( szPassword ) );
//    };
//
//    uint8 uchOperator;      // 将MsgCheckSecondPasswordReq消息里的 uchOperator回传
//    char szPassword[ Password::MaxLength + 1 ]; 
//};
//
//// 密码不对才回返回
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
//        SecondPasswordError,       // 你输入的2级密码不正确
//        SuccessAndClear,           // 验证成功,你的强制解除密码已经取消
//    };
//
//    uint8 uchResult;     // 返回结果
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
{ // 积分商城道具查询
    MsgJiFengShopItemsListReq()
    {
        header.dwType   = MSG_JIFENGSHOPITEMSLISTREQ;
        header.stLength = sizeof( MsgJiFengShopItemsListReq );
    }
};

struct MsgJiFengShopItemsListAck : public Msg
{ // 积分商城道具列表
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

    uint8                   isNew; // 是否是新的
    uint16                  count;
    SJiFengItemRecordClient items[ ECD_MaxJiFengItemCount ];
};

struct MsgJiFengShopItemsGain : public Msg
{ // 积分商城道具领取
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
{ // 请求金锭商城配置更新
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
    uint32     delayTime; // 秒
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

    uint8       count;                  // count - 1的位置是附加的材料
    ComposeItem xItem[ ECD_MaxCount ];  // 5个合成原材料加一个附加材料

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

    // 下面的作废使用上面的 请客户端及时修改
    // 需要的材料
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
        ECD_Success = 0,            // 成功
        ECD_Failed,                 // 失败
        ECD_NotEnoughMoney,         // 没有足够的钱
        ECD_ErrorMaterialItem,      // 错误的材料
        ECD_ErrorComposeItem,       // 放入的合成材料不正确
        ECD_CanNotCompose,          // 该物品不能被合成
        ECD_ItemPackFull,           // 背包已经满了
    };

    uint16 uchResult;
    uint32 dwCurrentMoney;          // 当前剩余多少钱
};

// 通知其他玩家, 某人给某人使用了某种物品( 区域范围内客户端显示特效用 )
struct MsgShowViewUseItemToPlayer : public Msg
{
    MsgShowViewUseItemToPlayer()
    {
        header.dwType   = MSG_SHOWVIEWUSEITEMTOPLAYER;
        header.stLength = sizeof( MsgShowViewUseItemToPlayer );
    }

    GameObjectId stSrcPlayerID;       // 使用者动态ID
    GameObjectId stDestPlayerID;      // 使用对象
    uint16 ustItemID;
};

// 全服公告, 某人给某人使用了某物品多少个
struct MsgShowAllUseItemToPlayer : public Msg
{
    MsgShowAllUseItemToPlayer()
    {
        header.dwType   = MSG_SHOWALLUSEITEMTOPLAYER;
        header.stLength = sizeof( MsgShowAllUseItemToPlayer );
    }

    char szSrcPlayerName[dr_MaxPlayerName];     // 使用者
    char szDestPlayerName[dr_MaxPlayerName];    // 使用对象
    SCharItem xCharItem;
};

struct MsgTellHideStatus : public Msg
{
    MsgTellHideStatus()
    {
        header.dwType   = MSG_TELLHIDESTATUS;
        header.stLength = sizeof( MsgTellHideStatus );
    }
    
    GameObjectId stID;    // 隐身的ID
    bool bShow;         // true = 显示  false = 隐身
};

struct MsgMountPotential : public Msg
{
    MsgMountPotential()
    {
        header.dwType   = MSG_MOUNTPOTENTIAL;
        header.stLength = sizeof( MsgMountPotential );
    }

    uint8 index ;       //坐骑数组下标
    int64 guid  ;       //坐骑guid
    int16 value[EBaseAttr_MaxSize];     //分配的潜力点  
};

struct MsgMountBreed : public Msg
{
    MsgMountBreed()
    {
        header.dwType   = MSG_MOUNTBREED;
        header.stLength = sizeof( MsgMountBreed );
    }

    int64 masterGuid ;       //主坐骑Guid
    int64 assistantGuid ;    //副坐骑Guid
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

    bool bSetOfflineHook;   //是否离线挂机
};

struct MsgAckOfflineHook : public Msg
{
    MsgAckOfflineHook()
    {
        header.dwType   = MSG_ACKOFFLINEHOOK;
        header.stLength = sizeof( MsgAckOfflineHook );
    }

    bool bIsOfflineHook;   //是否离线挂机
};

struct MsgGetOfflineHookExp : public Msg
{
    MsgGetOfflineHookExp()
    {
        header.dwType   = MSG_GETOFFLINEHOOKEXP;
        header.stLength = sizeof( MsgGetOfflineHookExp );
    }

    uint8 nHookLevel;   //领取档次
};

struct MsgTellServerExpModulus : public Msg
{
    MsgTellServerExpModulus()
    {
        header.dwType   = MSG_TELLSERVEREXPMODULUS;
        header.stLength = sizeof( MsgTellServerExpModulus );
    }

    int nExpModulus;        // 经验倍数( 100为单位 )     对应字串9074
    int nSkillExpModulus;   // 技能经验倍数( 100为单位 ) 对应字串9075
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

    SCharItem targetEquip   ;   // 目标装备
    SCharItem sourceEquip   ;   // 源装备

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
        error_notfind_item  ,   //没有找到装备
        error_item_is_lock  ,   //装备锁定
        error_item_not_equip,   //物品不是装备
        error_item_not_reclaim, //装备无法回收
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
        ECT_GEM         =   0,  // 宝石升级
        ECT_MATERIAL    =   1,  // 洗石剂合成
    };

    struct SMaterial
    {
        uint8 nItemBagType  ;
        int16 nItemIndex    ;
        int64 nItemGuid     ;
        uint8 nCount        ;
    };

    uint8       composeType;                            // 类型
    uint8       nMaterialCount;                         // 材料个数
    SMaterial   materials[ ECD_MaterialMaxCount ];      // 材料数组
	SMaterial	composeRune;							//宝石合成符
	uint8		nSelectGemNum;							//选择的宝石个数

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
        ECD_Success = 0,            // 成功
        ECD_Failed,                 // 失败
        ECD_NotEnoughMoney,         // 没有足够的钱
        ECD_ErrorMaterialItem,      // 错误的材料
        ECD_ErrorComposeItem,       // 放入的合成材料不正确
        ECD_CanNotCompose,          // 该物品不能被合成
        ECD_ItemPackFull,           // 背包已经满了
		ECD_ErrorComposeRune,       // 放入的合成符不正确
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

	uint8       nMaterialCount;                         // 材料个数
	SMaterial   materials[ ECD_MaterialMaxCount ];      // 主将鉴图数组
	SMaterial	composeRune;							//材料

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
		ECD_Success = 0,            // 成功
		ECD_Failed,                 // 失败
		ECD_NotEnoughMoney,         // 没有足够的钱
		ECD_ErrorMaterialItem,      // 错误的材料
		ECD_ErrorComposeItem,       // 放入的合成材料不正确
		ECD_CanNotCompose,          // 该物品不能被合成
		ECD_ItemPackFull,           // 背包已经满了
		ECD_ErrorComposeRune,       // 放入的合成符不正确
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

    SPressKeySuit xPressKeySuit[MAX_PRESSKEYSUIT_COUNT];    // 所有一键换装信息
};

struct MsgPressKeySuit : public Msg
{
    MsgPressKeySuit()
    {
        header.dwType   = MSG_PRESSKEYSUIT ;
        header.stLength = sizeof( MsgPressKeySuit ) ;
    }

    uint8 nIndex;       //哪件套装
    int64 equipitem   [ EEquipPartType_MaxEquitPart ];      //装备GUID
};

struct MsgPressKeySuitAck : public Msg
{
    enum EConstDefine
    {
        ECD_Success = 0,            // 成功
        ECD_Failed,                 // 失败
        ECD_NotFoundEquip,          // 没有找到装备
    };

    MsgPressKeySuitAck()
    {
        header.dwType   = MSG_PRESSKEYSUITACK ;
        header.stLength = sizeof( MsgPressKeySuitAck ) - EEquipPartType_MaxEquitPart * sizeof(int64) ;

        nResult = ECD_Success;
    }

    uint8 nResult   ;
    uint8 nIndex    ;
    int64 equipitem [ EEquipPartType_MaxEquitPart ];  //装备GUID

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
    char  keySuitName [ dr_MaxPlayerName ];  //套装名称
};

struct MsgPressKeySuitNameAck : public Msg
{
    MsgPressKeySuitNameAck()
    {
        header.dwType   = MSG_PRESSKEYSUITRENAMEACK ;
        header.stLength = sizeof( MsgPressKeySuitNameAck ) ;
    }

    uint8 nIndex;
    char  keySuitName [ dr_MaxPlayerName ];  //套装名称
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
    uint32  nAchievePoint;      // 人物身上所有的成就点数
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
    uint32  nAchievePoint;      // 人物身上所有的成就点数
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

    GameObjectId      nPetID  ;   // 护送怪ID
    uint32			   nMapID  ;   // 地图ID 
    D3DXVECTOR3		   pos     ;   // 地图位置
};

struct MsgReqDoubleExp : public Msg
{
    MsgReqDoubleExp()
    {
        header.dwType   = MSG_REQDOUBLEEXP;
        header.stLength = sizeof(MsgReqDoubleExp);
    }
    
    bool  bState; // false 为关闭 ture 为打开
};

struct MsgDoubleExpAck : public Msg
{
    MsgDoubleExpAck()
    {
        header.dwType   = MSG_DOUBLEEXPACK;
        header.stLength = sizeof(MsgDoubleExpAck);
    }
    
    bool    bState;
    uint32  nSysDoubleExpTime;      // 系统赠送的双倍经验时间 单位 毫秒
    uint32  nItemDoubleExpTime;     // 道具双倍经验时间       单位 毫秒
};

enum EOfflineFightOP
{
    EOfflineFightOP_Begin, // 开始挂机
    EOfflineFightOP_End  , // 结束挂机
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
    
    int16 nValue[EBaseAttr_MaxSize];     //分配的潜力点  
};

struct MsgCharAssignPotentialAck : public Msg
{
    MsgCharAssignPotentialAck()
    {
        header.dwType   = MSG_CHARASSIGNPOTENTIALACK;
        header.stLength = sizeof(MsgCharAssignPotentialAck);
    }

    uint16 basePotential   ;            //剩余潜力点
    uint16 nValue[EBaseAttr_MaxSize];   //分配的潜力点  
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
    
    int16  nXinFaID     ;   // 心法ID
    uint8  nXinFaLevel  ;   // 心法等级
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
    bool          bMessageDialog;   // 是否弹窗提示
    int64         nUnUsedExp;       // 剩余未使用技能经验
};

struct MsgReqGotOnDrome : public Msg
{
    enum EOperateType
    {
        EOperateType_Request,   // 请求
        EOperateType_Invite ,   // 邀请
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
    uint16 driverId ;   // 驾驶员
    uint16 riderId  ;   // 乘客
};

struct MsgReqGotOnDromeAck : public Msg
{
    enum EOperateType
    {
        EOperateType_Agree  ,   // 同意
        EOperateType_Reject ,   // 拒绝
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
    uint16 driverId ;   // 驾驶员
    uint16 riderId  ;   // 乘客
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

    uint16 driverId ;   // 驾驶员
    uint16 riderId  ;   // 乘客
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

    uint8		  type     ;   // 操作
    GameObjectId  driverId ;   // 驾驶员
    GameObjectId  riderId  ;   // 乘客
    uint8		  pos      ;   // 位置
};

struct MsgRiderOffDrome : public Msg
{
    MsgRiderOffDrome()
    {
        header.dwType   = MSG_RIDEROFFDROME ;
        header.stLength = sizeof( MsgRiderOffDrome ) ;
        riderId         = InvalidGameObjectId;
    }

    GameObjectId  riderId  ;   // 下坐骑的乘客
	GameObjectId  driverId;    //司机
};

// 请求完成任务
struct MsgReqDoneQuest : public MsgReqScript 
{
    enum EReqDoneQuestConstDefine
    {
        EDoneQuest_CommitItemMax = 4,   //最多提交4个物品 
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
    char szSignature[RelationDefine::MaxSignLength];    // 个性签名
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

    uint8 	  type  ;   // 增加 更新
    uint8     source;   // 宠物来源
    SPetItem  pet   ;   // 
};

struct MsgAddPetEquip : public Msg
{
    MsgAddPetEquip()
    {
        header.dwType   = MSG_ADDPETEQUIP;
        header.stLength = sizeof( MsgAddPetEquip );
    };

    __int64		PetGuID;//副将的ID
	__int64		ItemOnlyID;//装备的唯一ID
};

struct MsgRemovePetEquip : public Msg
{
    MsgRemovePetEquip()
    {
        header.dwType   = MSG_REMOVEPETEQUIP;
        header.stLength = sizeof( MsgRemovePetEquip );
    };

    __int64		PetGuID;//副将的ID
	int			BagIndex;//未指定为 -1
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
{ // 宠物改变的信息
    enum EOpType
    {
        EOT_Active      ,   // 出战
        EOT_UnActive    ,   // 休息
        EOT_Disappear   ,   // 消失
		EOT_CallButNoActive, // 召唤，但是不出战
		EOT_Recall			//召回
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

    uint8 index ;       //宠物数组下标
    int64 guid  ;       //宠物guid
    int16 value[EBaseAttr_MaxSize];     //分配的潜力点  
};

struct MsgUseGoodsToPet : public MsgUseGoods
{
    MsgUseGoodsToPet()
    {
        header.dwType = MSG_USEGOODSTOPET;
        header.stLength = sizeof(MsgUseGoodsToPet);
        nPetIndex = 0;
    }

    uint8 nPetIndex; //宠物索引
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

    uint8 nSrcPetIndex; // 材料宠物索引
    int64 nSrcPetGuid ; // 材料宠物GUID
    uint8 nDstPetIndex; // 目标宠物索引
    int64 nDstPetGuid ; // 目标宠物GUID
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
        ER_Success  ,   // 开始繁殖操作
        ER_Failed   ,
        ER_NoTeam   ,   // 您没有处于队伍中 
        ER_TeamMember,  // 您的队伍超过了2名
        ER_TeamHeader,  // 您不是队伍的队长
        ER_TeamRange,   // 队友不在旁边
        ER_HaveBreed,   // 已经有宠物在繁殖中
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
        ER_NoBreedPet,      // 没有繁殖宠物
        ER_Interval ,       // 时间间隔未到
        ER_PetFull  ,       // 宠物栏已经满
        ER_PetLost  ,       // 宠物伤心过度走了
        ER_TeamMember,      // 队伍队员不正确
        ER_TeamHeader,      // 不是队长无法领取
        ER_NeedMoney ,      // 单人领取需要花费   
        ER_NoMoney   ,      // 金钱不足无法领取
        ER_BreedTime ,      // 宠物繁殖时间到了快去领取
        ER_TargetAcquired,  // 对方独自领取了繁殖宠物
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
    char          szName[ dr_MaxPlayerName ];   // 队友名称
};

// 发送给客户端请求播放视频
struct MsgPlayMovieReq : public Msg
{
    MsgPlayMovieReq()
    {
        header.dwType = MSG_PLAYMOVIEREQ;
        header.stLength = sizeof( MsgPlayMovieReq );
    }
    uint16 nMovieId;        // 电影ID
    DWORD dwPlayTime;       // 播放时间
};

// 客户端回应是否可以播放视频了
struct MsgPlayMovieAck : public Msg
{
    MsgPlayMovieAck()
    {
        header.dwType = MSG_PLAYMOVIEACK;
        header.stLength = sizeof( MsgPlayMovieAck );
    }

    DWORD dwPlayTime;   // 播放时间
};

// 怪物类型状态改变
struct MsgMonsterTypeStatusChange : public Msg
{
    MsgMonsterTypeStatusChange()
    {
        header.dwType = MSG_MONSTERTYPESTATUSCHANGE;
        header.stLength = sizeof( MsgMonsterTypeStatusChange );
    }

    GameObjectId nMonsterID;      // 怪物动态ID
    uint8 nTypeStatus;          // 当前状态
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

// 成就广播
struct MsgAchieveBroadcast : public Msg
{
    MsgAchieveBroadcast()
    {
        header.dwType = MSG_ACHIEVEBROADCAST;
        header.stLength = sizeof( MsgAchieveBroadcast );
    }

    uint16 usID;						// 成就ID
    char   szName[dr_MaxPlayerName];	// 获得成就的玩家
};

struct MsgStartEvent : public Msg
{
    enum NeedBroadcast
    {
        ENB_NoBroadcast = 0,	// 不要广播
        ENB_Broadcast,			// 广播
    };

    MsgStartEvent()
    {
        header.dwType = MSG_STARTEVENT;
        header.stLength = sizeof( MsgStartEvent );
    }
    uint16	usEventID;	// 事件ID
    uint8	ucBroadcast;// 是否广播

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

    SIdentifyData    identifyData;  // 图鉴数据
};

struct MsgUpdatePetIdentify : public Msg
{
    MsgUpdatePetIdentify()
    {
        header.dwType = MSG_UPDATEPETIDENTIFY;
        header.stLength = sizeof( MsgUpdatePetIdentify );
    }

    SPetIdentify petIdentify;   // 宠物图鉴
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
    uint16  regenerateTime; // 单位秒
};

//玩家升到一定级别，通知帮主或族长可以邀请其加入家族或者帮派
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
        ESource_Realize ,   // 升级领悟
        ESource_Item    ,   // 道具学习
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
    
    GameObjectId masterId;  // 主人ID
};

struct MsgViewActivePetAck : public Msg
{
    MsgViewActivePetAck()
    {
        header.dwType = MSG_VIEWACTIVEPETACK;
        header.stLength = sizeof( *this );
    }

    GameObjectId masterId;  // 主人ID
    SPetItem     pet;       // 宠物
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

    short stSceneId;    // 播放场景ID
};

struct MsgBlackScreen : public Msg
{
    MsgBlackScreen()
    {
        header.uMsgLevel = level_low;
        header.dwType    = MSG_BLACKSCREEN;
        header.stLength  = sizeof(*this);
    }

    uint32 dwTime;      // 持续时间
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
		eResult_succ = 0,//成功
		eResult_fail,//失败
		eResult_NoHero,//主将不存在
		eResult_NoMataril,//材料不足
		eResult_NoMoney,//金钱不足
		eResult_NoLevel,//等级不够
		eResult_popItemFail,//删除物品失败
		eResult_diffSex,	//性别不同
		eResult_Max
	};

	MsgG2CReqBianShen()
	{
		header.dwType = MSG_G2C_REQ_BIANSHEN;
		header.stLength = sizeof(*this);
	}
	uint16 result;			//变身结果
	uint16 hero_id;			//主将ID
	uint16 nItemIndex;		//物品index
	//SCharDBInfo charInfo;	//变身后属性
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
	bool in_or_out;//进入或者退出太平幻境
};
 
struct MsgTellTPHJRank:public Msg
{
	MsgTellTPHJRank()
	{
		header.dwType = MSG_TELLTPHJRANK;
		header.stLength = sizeof(*this);
	}
	char rank;				//太平幻境等级
};

// 玩家请求变身为镖车
struct MsgChangeToBiaocheReq : public Msg
{
	MsgChangeToBiaocheReq()
	{
		header.dwType = MSG_CHANGE_2_BIAOCHE_REQ;
		header.stLength = sizeof(*this);
	}

	int monsterID;				// 镖车的monsterID
	//float scale;				// 镖车的缩放比
	//float moveSpeed;			// 镖车的移动速度
};

// 玩家变身镖车的通知
struct MsgChangeToBiaocheAck : public Msg
{
	MsgChangeToBiaocheAck()
	{
		header.dwType = MSG_CHANGE_2_BIAOCHE_ACK;
		header.stLength = sizeof(*this);
	}

	int monsterID;				// 镖车的monsterID
};

// 玩家请求从镖车变回人形
struct MsgRestoreFromBiaocheReq : public Msg
{
	MsgRestoreFromBiaocheReq()
	{
		header.dwType = MSG_RESTORE_FROM_BIAOCHE_REQ;
		header.stLength = sizeof(*this);
	}

	//int monsterID;		// 镖车的monsterID
	//float scale;				// 镖车的缩放比
	//float moveSpeed;			// 镖车的移动速度
};

struct MsgRestoreFromBiaocheAck : public Msg
{
	MsgRestoreFromBiaocheAck()
	{
		header.dwType = MSG_RESTORE_FROM_BIAOCHE_ACK;
		header.stLength = sizeof(*this);
	}

	//int monsterID;		// 镖车的monsterID
	//float scale;				// 镖车的缩放比
	//float moveSpeed;			// 镖车的移动速度
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
		eHeroSuitFlag_show = 0,//显示
		eHeroSuitFlag_notshow,//不显示
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
	char szMac[eMacMax];			 // 这个必须加密
	char szAccount[eAccountMax];
	char szPwds[ePwdsMax];
	int  nSecondVersion;
	bool isEncryp;                   //是否加密
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

	SMaterial sTargetEquip; //目标装备
	SMaterial sSourceEquip; //源装备
	SMaterial sMaterial;	//材料
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

	SCharItem targetEquip   ;   // 目标装备
	SCharItem sourceEquip   ;   // 源装备

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

	int8 mountIndex ;       //坐骑数组下标
	int64 mountGuid  ;       //坐骑guid
	
	int8 materialIndex;		//材料Index
	int64 materialGuid;		//材料Guid

	uint8 protectNum;		//保护的等级
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

	uint8 loselevel;	//掉的等级
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
    __int64 nEquipGuid;     // 装备guid
};
struct MsgUnBindEquipAck : public Msg
{
    MsgUnBindEquipAck()
    {
        header.dwType = MSG_UNBINDEQUIPACK;
        header.stLength = sizeof( MsgUnBindEquipAck );
    }
    __int64 nEquipGuid;     // 装备guid
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
    uint32		nAllKillNum;//总杀人数
	uint32		nWeekKillNum;//本周杀人数
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
	bool	IsOpen;//是否打开倒计时框 或者关闭当前倒计时框
	uint32	TimeStep;
};//服务器端切换地图的倒计时

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

	SMaterial sArmour; //目标装备
	SMaterial sMaterial;	//材料
};

struct MsgRandAttrAck : public Msg
{
	MsgRandAttrAck()
	{
		header.dwType = MSG_RANDATTRIBUTE_ACK;
		header.stLength = sizeof( MsgIntensifyEquip ) - sizeof( SCharItem ) ;
	}

	uint16    nNormalBagIndex ;
	SCharItem item            ; // e_Succeed 和 e_Lost 会返回道具的属性 ,其他不返回这个结构

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
	eChangeChannelRet_Succ = 0,//成功
	eChangeChannelRet_Error = 1,//选择的分线错误
	eChangeChannelRet_Same = 2,//与当前分线相同
	eChangeChannelRet_Dead = 3,//玩家死亡
	eChangeChannelRet_Fight = 4,//战斗状态
	eChangeChannelRet_Max	//未知错误!
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
		eResetState_death,//死亡状态
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
	char PwdCardSerialNumber[PwdCardSerialLength];//序列号
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

//用作非变长消息的检测
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
