#pragma once

#include "ItemHero.h"

/*
* Author:	2012-7-30 wangshuai
* Desc: 	Player�����Ϣ������
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

	// ��ȡPlayer������ֵ
	float GetScaleForPlayer(CPlayer *player, bool isEffect = false);

	// ��ȡ��������ֵ
	float GetScaleForMounting(CPlayer *player);

	// ��ȡ���ͷ��
	void GetPlayerHeadPic(CPlayer *player, char *headPic);

	// ��ȡ���ͷ��
	const char * GetPlayerHeadPic(const CItemHero::SItemHero *itemHero);
	
	// ����Player��Face��Hair
	void SetPlayerFaceAndHair(CPlayer *player, int noHeroFaceID, int noHeroHairID, int &faceModelID, int &hairModelID);

protected:
	float GetScale(int gender, float scale);
};