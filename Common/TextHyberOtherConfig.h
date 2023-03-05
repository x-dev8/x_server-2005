#pragma once
#include <map>
#include <string>
class TextHyberOtherConfig
{
public:
	TextHyberOtherConfig();
	~TextHyberOtherConfig();
	bool LoadTextHyberOtherConfig(const char* FilePath);
	static TextHyberOtherConfig& Instance()
    {
        static TextHyberOtherConfig s_xConfig;
        return s_xConfig;
    }
	int GetUIID(std::string Name);
private:
	std::map<std::string,int> m_Info;
};