#pragma once

#include <string>
#include "MeRTLibs.h"
#include "Singleton.h"
#include "CountryDefine.h"

class CountryFunction : public Singleton<CountryFunction>
{
public:
// 公共接口
    // 根据国家Id取阵营名
    static std::string GetDefaultCountryNameById( int Id );

    // 根据国家Id取国号
	static std::string GetCountryNameById( int Id );

    // 根据阵营名取Id
    static short GetCountryIdByDefaultName( const char * pCountry );

    // 根据国号名取Id
	static short GetCountryIdByName( const char * pCountry );

    // 根据国家称号 ID 取称号名
    static std::string GetCountryTitleNameById( int Id );

    // 根据公会称号Id取公会名
	static std::string GetGuildTitleNameById( int Id );

    // 根据国家职位 ID 取职位名
	static std::string GetCountryOfficialNameById( int id );

    // 根据国家职位 ID 取称号名
    static std::string GetCountryTitleNameByOfficialId( int id );

    // 根据国家战场类型取名字
    static std::string GetCountryBattleNameByType( int nType );

    // 根据时间取时间字串
    static std::string GetTimeStringBySeconds( DWORD dwSecond );

    // 根据职业取攻击方式描述
    static std::string GetAttackStringByProfession( int nProfession );

    // 检测是否为国家称号
	static bool CheckIsCountryTitle( int nTitle );

    // 检测是否为公会称号
	static bool CheckIsGuildTitle( int nTitle );

	// 得到有颜色的国家职位字串
	static std::string GetOfficialForChat( int id );

    // 根据职业ID取职业名
    static std::string GetProfessionByID( int nProfessionID );

public:
// 逻辑接口
    ~CountryFunction();
    void UpdateCountryName( int nCountryId, char* szName );
    void ClearCountryName();
    const std::string* GetCountryNameArray();

private:
    CountryFunction();
    friend class Singleton<CountryFunction>;

private:
    std::string m_nCountryName[CountryDefine::Country_Max];

};
