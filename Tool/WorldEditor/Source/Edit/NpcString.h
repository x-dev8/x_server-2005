#pragma once
#include <map>
#include <string>


#define  theNpcString CNpcString::Instance()
#define  theNpcStringForMenu CNpcString::InstanceForMenu()

class CNpcString
{
protected:
	CNpcString(void);
public:
	~CNpcString(void);

	struct npcTalk
	{
		int m_Id;
		std::string  m_strTalk;
	};

	typedef std::map<unsigned int,npcTalk> NPCTALKSET;
public:
	bool LoadConfig(const char* pszPath);
    bool LoadConfigForMenu(const char* pszPath);
	bool SaveConfig(const char* pszPath);
    bool SaveConfigForMenu(const char* pszPath);

	npcTalk* GetDataByID(const int Id);
    npcTalk* GetDataByIDForMenu(const int Id);

	void InsertData(npcTalk cNpcTalk);
	void DelData(int nID);
	int  GetCount(){return static_cast<int>(m_TalkSet.size());}

	void Clear();

	static CNpcString& Instance()
	{
	   static CNpcString s_NpcString;
	   return s_NpcString;
	}
    static CNpcString& InstanceForMenu()
    {
        static CNpcString x_NpcStringForMenu;
        return x_NpcStringForMenu;
    }
public:
	NPCTALKSET m_TalkSet;
    NPCTALKSET m_TalkSetForNpcMenu;
};
