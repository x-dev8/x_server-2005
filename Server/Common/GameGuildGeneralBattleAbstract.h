#pragma once
//公会约战的专用脚本
//1.进入公会约战的战场
virtual int EnterGameGuildGeneralBattle()=0;
//2.获取当前玩家是否在公会约战战场里面
virtual bool IsInGameGuildGeneralBattle()=0;
//3.判断玩家在公会约战战场里的阵营
virtual int GetPlayerGameGuildGeneralBattleFigh()=0;
//4.获取当前公会约战战场的状态
virtual int GetGameGuildGeneralBattleStates()=0;
//5.获取当前战场的积分
virtual int GetGameGuildGeneralBattleSource(unsigned int Fight)=0;
//6.修改当前战场的积分
virtual void ChangeGameGuildGeneralBattleSource(unsigned int Fight,int Value)=0;
virtual void SetGameGuildGeneralBattleSource(unsigned int Fight,int Value)=0;
//7.创建公会约战的阵营怪物
virtual void CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFight, float fRadius, float fBodySize, int nRouteID )=0;
virtual void CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID )=0;