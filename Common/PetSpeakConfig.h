#pragma once
#include <vector>
#include <map>
#include <string>
struct PetSpeak
{
	unsigned int PetID;
	unsigned int UpdateTime;
	std::vector<std::string> vecStr;
	PetSpeak()
	{
		PetID = 0;
		UpdateTime = 0;
		vecStr.clear();
	}
};
class PetSpeakConfig
{
public:
	PetSpeakConfig();
	~PetSpeakConfig();
	bool LoadPetSpeakConfig(const char* FilePath);
	static PetSpeakConfig& Instance()
    {
        static PetSpeakConfig s_xConfig;
        return s_xConfig;
    }
	bool GetNowPetSpeakStr(unsigned int PetID,unsigned int LogTime,std::string& str);
private:
	std::map<unsigned int,PetSpeak> m_Info;
};