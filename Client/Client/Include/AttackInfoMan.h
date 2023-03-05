/*
原因:攻击数值的延迟处理（扣血等到攻击命中才扣，显示很合理）	
接收到攻击消息
加入AttackInfo到AttackInfo管理器
加入攻击到动作队列
角色死亡
简单的进入死亡循环
只到被复活
角色退出（MsgExit,MsgExitMySight）
角色切换到保留队列，逻辑对象已经消失
清除运行动作队列（保证AttackInfo被处理或移交给效果）
切换地图			
运行所有保存的AttackInfo
清除所有的角色（主角除外）
主角清除动作队列
*/

#pragma  once

#include <map>
#include "MapContainer.h"
struct SAttackInfo;
class CAttackInfoMan
{
	CMapContainer<SAttackInfo*,SAttackInfo*> m_map;
public:
	CAttackInfoMan(void);
	~CAttackInfoMan( void );

	SAttackInfo* AddAttackInfo( SAttackInfo & attackinfo );
	//传入的是AddAttackInfo返回的
	void DeleteAttackInfo( SAttackInfo *pAttackInfo );
	//玩家切换地图时调用执行保存的所有AttackInfo
	void ExcuteAllAttackInfo( void );

	//退出游戏时调用
	void ClearAll( void );
};
extern CAttackInfoMan theAttackInfoMan;