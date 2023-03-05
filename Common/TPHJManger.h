#pragma once
#include <map>
#include <string>
#include <set>

class CTPHJManger
{
public:
	struct STPHJ
	{
		char rank;
		std::string rank_pic;
		std::string gray_pic;
		std::string tip;
		short		map_id;
		float		posX;
		float		posY;
		float		posZ;
		//STPHJ()
		//{
		//	memset(this,0,sizeof(STPHJ));
		//}
	};
	typedef std::map<char,STPHJ> mapTPHJ;
public:
	CTPHJManger();
	~CTPHJManger();

	bool LoadConifg(const char* szFileName,bool server_or_client=true);

	static CTPHJManger& Instance()
	{
		static CTPHJManger cTPHJ;
		return cTPHJ;
	}
	
	STPHJ* FindTPHJRankByRankID(const char cRankID);

public:
	short GetMapIdByRank(char rankid)
	{
		STPHJ* pRank = FindTPHJRankByRankID(rankid);
		if (pRank==NULL)
		{
			return 0;
		}
		return pRank->map_id;
	} 
	float GetPosXByRank(char rankid)
	{
		STPHJ* pRank = FindTPHJRankByRankID(rankid);
		if (pRank==NULL)
		{
			return 0;
		}
		return pRank->posX;;
	}
	float GetPosYByRank(char rankid)
	{
		STPHJ* pRank = FindTPHJRankByRankID(rankid);
		if (pRank==NULL)
		{
			return 0;
		}
		return pRank->posY;;
	}
	float GetPosZByRank(char rankid)
	{
		STPHJ* pRank = FindTPHJRankByRankID(rankid);
		if (pRank==NULL)
		{
			return 0;
		}
		return pRank->posZ;;
	}
	short GetMaxRank(){return m_max_rank;}
	std::string GetDefaultTip(){return m_tip;}
	bool MapCanEnterTphj(int nMapID);
private:
	//short m_mapid;
	//float m_posx;
	//float m_posy;
	//float m_direction;
	short m_max_rank;
	mapTPHJ _mapTPHJ; 
	std::string m_tip;
	std::set<int>	m_setMapNoEnter;
};

#define theTPHJManager CTPHJManger::Instance()
