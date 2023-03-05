#ifndef _CARDACHIEVECONFIG_
#define _CARDACHIEVECONFIG_

#include "MeRTLibs.h"

#define MAX_CARDIDS 32
class CardAchieveConfig
{
public:
	struct SImage
	{
		SImage()
		{
			nWidth = 0;
			nHeight = 0;
			nRow = 0;
			nColumn = 0;
		}

		std::string strImg; //图片路径
		int nWidth;			//宽
		int nHeight;		//高
		int nRow;			//行
		int nColumn;		//列
	};

	struct SData
	{
		SData()
		{
			shID = -1;
			memset( shCardIDs, -1, sizeof( shCardIDs ) );
			unItemID = 0;
			shCardCount = 0;
		}

		short shID;			//卡牌成就ID
		short shCardIDs[ MAX_CARDIDS ];	//卡牌ID
		uint32 unItemID;	//奖励物品ID
		short shCardCount;	//卡牌数量

		SImage sBrightImg;			//亮的图片
		SImage sDarkImg;			//暗的图片
		std::string strName;		//名字
		std::string strScriptAddr;  //脚本
	};

	typedef std::vector< SData > CardAchieveVector;

public:
	CardAchieveConfig();
	virtual ~CardAchieveConfig();

	void AddData( SData data );

	bool LoadCardAchieveConfig( const char* pszConfig );

	static CardAchieveConfig& Instance()
	{
		static CardAchieveConfig s_xCardAchieve;
		return s_xCardAchieve;
	}

	std::vector< SData > GetCardVec() { return m_vecAchieve; }

private:
	CardAchieveVector m_vecAchieve;
};
#define theCardAchieveConfig CardAchieveConfig::Instance()

#endif //_CARDACHIEVECONFIG_