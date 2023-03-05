#pragma once

#include <string>
#include "MeRTLibs.h"
#include "Singleton.h"
#include "CountryDefine.h"

class CountryFunction : public Singleton<CountryFunction>
{
public:
// �����ӿ�
    // ���ݹ���Idȡ��Ӫ��
    static std::string GetDefaultCountryNameById( int Id );

    // ���ݹ���Idȡ����
	static std::string GetCountryNameById( int Id );

    // ������Ӫ��ȡId
    static short GetCountryIdByDefaultName( const char * pCountry );

    // ���ݹ�����ȡId
	static short GetCountryIdByName( const char * pCountry );

    // ���ݹ��ҳƺ� ID ȡ�ƺ���
    static std::string GetCountryTitleNameById( int Id );

    // ���ݹ���ƺ�Idȡ������
	static std::string GetGuildTitleNameById( int Id );

    // ���ݹ���ְλ ID ȡְλ��
	static std::string GetCountryOfficialNameById( int id );

    // ���ݹ���ְλ ID ȡ�ƺ���
    static std::string GetCountryTitleNameByOfficialId( int id );

    // ���ݹ���ս������ȡ����
    static std::string GetCountryBattleNameByType( int nType );

    // ����ʱ��ȡʱ���ִ�
    static std::string GetTimeStringBySeconds( DWORD dwSecond );

    // ����ְҵȡ������ʽ����
    static std::string GetAttackStringByProfession( int nProfession );

    // ����Ƿ�Ϊ���ҳƺ�
	static bool CheckIsCountryTitle( int nTitle );

    // ����Ƿ�Ϊ����ƺ�
	static bool CheckIsGuildTitle( int nTitle );

	// �õ�����ɫ�Ĺ���ְλ�ִ�
	static std::string GetOfficialForChat( int id );

    // ����ְҵIDȡְҵ��
    static std::string GetProfessionByID( int nProfessionID );

public:
// �߼��ӿ�
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
