#include "PlayerInfoMgr.h"
#include "../Cfg.h"
#include "Common.h"
#include "Player.h"
//#include "Launcher/DataLauncher.h"
#include "../filepacket/packet_interface.h"
PlayerInfoMgr::PlayerInfoMgr()
{

}

PlayerInfoMgr::~PlayerInfoMgr()
{

}

float PlayerInfoMgr::GetScale4CreateUI(int gender, float scale)
{
	return GetScale(gender, scale) * 0.018f;
}

float PlayerInfoMgr::GetScale4SelectUI(int gender, float scale)
{
	return GetScale(gender, scale) * 0.01f;
}

float PlayerInfoMgr::GetScaleForPlayer(CPlayer *player, bool isEffect)
{
	float scaleForPlayer = 1.0;
	if (player != NULL)
	{
		if (player->GetAnim() != NULL && player->GetAnim()->GetMexCfg() != NULL)
		{
			if (isEffect)
				scaleForPlayer = player->GetAnim()->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber();
			else
				scaleForPlayer = player->GetAnim()->GetMexCfg()->m_mdlScale.m_npScale.GetNumber() / 100.0f;
		}

		// 乘以身高缩放比
		scaleForPlayer *= Config::m_fMdlSpaceScale * player->GetPlayerScale();
		scaleForPlayer *= (player->GetBodySize() + 0.1);

		if (player->GetHeroID() != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(player->GetHeroID());
			if (itemHero != NULL && player->IsPlayer())
				scaleForPlayer *= itemHero->hero_rate;
		}
	}
	return scaleForPlayer;
}

float PlayerInfoMgr::GetScaleForMounting(CPlayer *player)
{
	float scaleForMounting = 1.0;
	if (player != NULL)
	{
		if (player->GetAnim() != NULL && player->GetAnim()->GetMexCfg() != NULL)
			scaleForMounting = player->GetAnim()->GetMexCfg()->m_mdlScale.m_npScale.GetNumber() / 100.0f;

		scaleForMounting *= Config::m_fMdlSpaceScale;
		scaleForMounting *= player->GetMountScaleFix();
		if (player->IsPlayer() && player->GetClass() < EArmType_MaxSize)
		{
			scaleForMounting *= gCfg.m_fMountScales[player->GetClass()];
			scaleForMounting *= player->GetPlayerScale();
		}

		CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(player->GetHeroID());
		if (itemHero != NULL && player->IsPlayer())
			scaleForMounting *= itemHero->hero_rate;
	}
	return scaleForMounting;
}

float PlayerInfoMgr::GetScale(int gender, float scale)
{
#ifdef _OLD_LOGIN_SCENE_
	float defaultScale = 1.f;
#else
	float defaultScale = 1.2f;

	if (gender == Sex_Male)
		defaultScale = gCfg.m_fCreateRoleManScale;
	else if (gender == Sex_Female)
		defaultScale = gCfg.m_fCreateRoleWomenScale;
#endif

	return scale * defaultScale;
}

void PlayerInfoMgr::GetPlayerHeadPic(CPlayer *player, char *headPic)
{
	if (player == NULL)
		return;

	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(player->GetHeroID());
	if (itemHero == NULL)
		return;

	sprintf_s(headPic, MAX_PATH - 1, "%s/%s", GetRootPath(), itemHero->Pic_Head.c_str());

	f_Handle *fp = packet_namespace::w_fopen(headPic, "r");
	if (fp != NULL)
	{
		packet_namespace::w_fclose(fp);
	}
	else
	{
		if (player->GetSex() == Sex_Male)
			strcpy_s(headPic, MAX_PATH - 1, "Data/Ui/HeadPicture/Player/DefaultMale.dds");
		else
			strcpy_s(headPic, MAX_PATH - 1, "Data/Ui/HeadPicture/Player/DefaultFemale.dds");
	}
}

const char * PlayerInfoMgr::GetPlayerHeadPic(const CItemHero::SItemHero *itemHero)
{
	return itemHero->Pic_Head.c_str();
}

void PlayerInfoMgr::SetPlayerFaceAndHair(CPlayer *player, int noHeroFaceID, int noHeroHairID, int &faceModelID, int &hairModelID)
{
	if (player == NULL)
		return;

	CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(player->GetHeroID());
	if (noHeroFaceID != -1 && faceModelID != -1)
		faceModelID = (itemHero != NULL&& player->IsSHowHero() ? itemHero->hero_lianxing : noHeroFaceID);

	if (noHeroHairID != -1 && hairModelID != -1 )
		hairModelID = (itemHero != NULL&& player->IsSHowHero() ? itemHero->hero_faxing : noHeroHairID);
}