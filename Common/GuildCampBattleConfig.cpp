#include "GuildCampBattleConfig.h"
#include "RapidXml/MeRapidXml.h"
GuildCampBattleConfig::GuildCampBattleConfig()
{

}
bool GuildCampBattleConfig::OnLoadFilePath(const char* FilePath)
{
	//加载配置文件
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Guild");
	if(pRoot == NULL)
		return false;
	int Profession = 0;
	int Open = 0;
	//1.加载工会战的设置
	MeXmlElement* pGuild = pRoot->FirstChildElement("CampGuildBattle");
	if(!pGuild)
		return false;
	if (pGuild->Attribute("MaxSum",&m_GuildSetting.MaxSum) == NULL)
		return false;
	if (pGuild->Attribute("MinLevel",&m_GuildSetting.MinLevel) == NULL)
		return false;
	if (pGuild->Attribute("Offer",&m_GuildSetting.Offer) == NULL)
		return false;
	Open = 0;
	if (pGuild->Attribute("IsOpen",&Open) == NULL)
		return false;
	m_GuildSetting.IsOpen = Open==0?false:true;

	Profession=0;
	if (pGuild->Attribute("Profession",&Profession) == NULL)
		return false;
	m_GuildSetting.Profession = Profession;
	//2.国家战
	MeXmlElement* pCountry = pRoot->FirstChildElement("CampCountrydBattle");
	if(!pCountry)
		return false;
	if (pCountry->Attribute("MaxSum",&m_CountrySetting.MaxSum) == NULL)
		return false;
	if (pCountry->Attribute("MinLevel",&m_CountrySetting.MinLevel) == NULL)
		return false;
	if (pCountry->Attribute("Offer",&m_CountrySetting.Offer) == NULL)
		return false;
	Open = 0;
	if (pGuild->Attribute("IsOpen",&Open) == NULL)
		return false;
	m_GuildSetting.IsOpen = Open==0?false:true;
	Profession=0;
	if (pCountry->Attribute("Profession",&Profession) == NULL)
		return false;
	m_CountrySetting.Profession = Profession;
	//3.公会联合站
	MeXmlElement* pGuildUnion = pRoot->FirstChildElement("CampGuildUnionBattle");
	if(!pGuildUnion)
		return false;
	if (pGuildUnion->Attribute("MaxSum",&m_GuildUnionSetting.MaxSum) == NULL)
		return false;
	if (pGuildUnion->Attribute("MinLevel",&m_GuildUnionSetting.MinLevel) == NULL)
		return false;
	if (pGuildUnion->Attribute("Offer",&m_GuildUnionSetting.Offer) == NULL)
		return false;
	Open = 0;
	if (pGuild->Attribute("IsOpen",&Open) == NULL)
		return false;
	m_GuildSetting.IsOpen = Open==0?false:true;
	Profession=0;
	if (pGuildUnion->Attribute("Profession",&Profession) == NULL)
		return false;
	m_GuildUnionSetting.Profession = Profession;
	//1.加载工会约战的设置
	MeXmlElement* pGuildGeneral = pRoot->FirstChildElement("GameGuildGeneralBattle");
	if(!pGuildGeneral)
		return false;
	if (pGuildGeneral->Attribute("MaxSum",&m_GuildGeneralSetting.MaxSum) == NULL)
		return false;
	if (pGuildGeneral->Attribute("MinLevel",&m_GuildGeneralSetting.MinLevel) == NULL)
		return false;
	if (pGuildGeneral->Attribute("Offer",&m_GuildGeneralSetting.Offer) == NULL)
		return false;
	Open = 0;
	if (pGuildGeneral->Attribute("IsOpen",&Open) == NULL)
		return false;
	m_GuildGeneralSetting.IsOpen = Open==0?false:true;

	Profession=0;
	if (pGuildGeneral->Attribute("Profession",&Profession) == NULL)
		return false;
	m_GuildGeneralSetting.Profession = Profession;
	return true;
}