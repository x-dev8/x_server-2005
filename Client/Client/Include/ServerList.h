#pragma once
#include <string>
#include <vector>
class CServerList
{
public:
    struct ServerData
    {
		ServerData()
		{
			nPing = -1;
		}
        std::string strServer;
        std::string strStatus;
        DWORD dwStatusColor;
        std::string strCommon;
        std::string strIpAddr;
        WORD wPort;
		std::string strHttpAddr;

		int unStatus;
		int unIsNew;
		int unIsRecommend;
		int unIsVehemence;
		int nPing;
    };

    struct AreaData
    {
        std::string strArea;
        std::vector<ServerData> vctServerList;
    };

    struct BigAreaData
    {
        std::string strBigArea;
        std::string strBroadCast; //公告的设置
        std::vector<AreaData> vctAreaList;
    };
public:
	CServerList(void);
	~CServerList(void);


public:
	bool	LoadFromGlobalConfig();

    std::vector<BigAreaData>* GetBigAreaList() { return &m_vctBigAreaList; }
    std::vector<AreaData>* GetAreaList(const char* strBigArea);
    std::vector<ServerData>* GetServerList(const char* strBigArea, const char* strArea);
    ServerData* GetServerData(const char* strBigArea, const char* strArea, const char* strServer);
    const char* GetBigAreaName(int id);
    const char* GetBigAreaBroadcast(int id);

	void RefreshPing();

protected:
    std::vector<BigAreaData> m_vctBigAreaList;
	bool	bLoad;
};
