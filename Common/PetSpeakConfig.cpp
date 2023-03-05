#include "PetSpeakConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "Mertlibs.h"
#include "tstring.h"
PetSpeakConfig::PetSpeakConfig()
{
	m_Info.clear();
}
PetSpeakConfig::~PetSpeakConfig()
{
	m_Info.clear();
}
bool PetSpeakConfig::LoadPetSpeakConfig(const char* FilePath)
{
	//加载配置文件
	//读取配置文件
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pThreeDay = xMeXml.FirstChildElement( "PetSpeaks" );
    if ( pThreeDay == NULL )
    { return false; }

	MeXmlElement* pOnce = pThreeDay->FirstChildElement( "PetSpeak" );
    while ( pOnce != NULL )
    {
		PetSpeak p;
		int nValue = 0;
		if ( pOnce->Attribute( "PetID", &nValue ) == NULL )
			return false;
		p.PetID = nValue;

		if ( pOnce->Attribute( "UpdateTime", &nValue ) == NULL )
			return false;
		p.UpdateTime = nValue;

		MeXmlElement* pSpeak = pOnce->FirstChildElement( "Speak" );
		while(pSpeak != NULL)
		{
			Common::_tstring strScriptAddr;
			strScriptAddr.fromUTF8( pSpeak->Attribute("Str") );
			std::string strspeak = strScriptAddr.c_str();
			p.vecStr.push_back(strspeak);

			pSpeak = pSpeak->NextSiblingElement();
		}
		m_Info.insert(std::map<unsigned int,PetSpeak>::value_type(p.PetID,p));
		pOnce = pOnce->NextSiblingElement();
	}
	return true;
}
bool PetSpeakConfig::GetNowPetSpeakStr(unsigned int PetID,unsigned int LogTime,std::string& str)
{
	//根据副将获取当前应该说的话
	if(m_Info.count(PetID) != 1)
	{
		if(PetID == 0)
			return false;
		return GetNowPetSpeakStr(0,LogTime,str);
	}
	PetSpeak p= m_Info[PetID];
	if(p.PetID != PetID)
		return false;
	if(HQ_TimeGetTime() - LogTime < p.UpdateTime)
		return false;//时间没到
	//时间到了随机一句
	if( p.vecStr.size() == 0)
		return false;
	str = p.vecStr[rand() % p.vecStr.size()];
	return true;
}