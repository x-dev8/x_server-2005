#pragma once

#include "ItemHero.h"

/*
* Author:	2012-7-30 wangshuai
* Desc: 	Player相关信息辅助类
*/
class CPlayer;
class PlayerInfoMgr
{
private:
	PlayerInfoMgr();
	virtual ~PlayerInfoMgr();
	
	PlayerInfoMgr(const PlayerInfoMgr &obj) {}
	PlayerInfoMgr & operator = (const PlayerInfoMgr &rhs) { return *this; }

public:
	static PlayerInfoMgr * Instance()
	{
		static PlayerInfoMgr theInstance;
		return &theInstance;
	}

public:
	float GetScale4CreateUI(int gender, float scale);
	float GetScale4SelectUI(int gender, float scale);

	// 获取Player的缩放值
	float GetScaleForPlayer(CPlayer *player, bool isEffect = false);

	// 获取坐骑缩放值
	float GetScaleForMounting(CPlayer *player);

	// 获取玩家头像
	void GetPlayerHeadPic(CPlayer *player, char *headPic);

	// 获取玩家头像
	const char * GetPlayerHeadPic(const CItemHero::SItemHero *itemHero);
	
	// 设置Player的Face和Hair
	void SetPlayerFaceAndHair(CPlayer *player, int noHeroFaceID, int noHeroHairID, int &faceModelID, int &hairModelID);

protected:
	float GetScale(int gender, float scale);
};