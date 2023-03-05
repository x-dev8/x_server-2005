#ifndef __PHYLE_CONFIG_H__
#define __PHYLE_CONFIG_H__

#include <vector>

#define MaxTotemNUM			8
#define MaxPhyleIntro     128
#define thePhyleChastenConfig PhyleChastenConfig::Instance()

class PhyleChastenConfig
{
public:

	struct SPhyleChasten
	{
		unsigned int  nTotemType;
		unsigned int  totemChastenDamage[MaxTotemNUM];

		SPhyleChasten()  
		{ memset(this,0,sizeof(SPhyleChasten)); }
	};

	struct IdentifyIntro
	{
		unsigned int  nPetType;
		std::string   szIdentifyIntro;
	};


public:
	static PhyleChastenConfig& Instance()
	{
		static PhyleChastenConfig instance;
		return instance;
	}

	unsigned int GetDamageByTotem( unsigned char attackerTotem, unsigned char targetTotem );
	bool LoadConfig( const char* szFile );

    std::string GetIdentifyIntroByPetType( unsigned int nPetType );

protected:
	PhyleChastenConfig() {}

	std::vector< SPhyleChasten >				 PhyleSettingContainer;
	typedef std::vector<SPhyleChasten>::iterator	 PhyleContainerItr;

	std::vector< IdentifyIntro >				 IdentifyIntroContainer;
	typedef std::vector<IdentifyIntro>::iterator	 IdentifyIntroContainerItr;

private:
};

#endif