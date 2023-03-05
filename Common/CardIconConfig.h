#ifndef _CARDICONCONFIG_
#define _CARDICONCONFIG_

#include "MeRTLibs.h"

class CardIconConfig
{
public:
	enum ECardType
	{
		ECT_Pet,		//宠物
		ECT_Hero,		//主将
		ECT_Mount,		//坐骑
		ECT_TypeNull,	//无
		ECT_MaxID = 5,	//最大ID个数
	};

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

	struct SCard
	{
		SCard()
		{
			shID = -1;
			memset(unTypeID, 0, sizeof(unTypeID));
			nLevel = -1;
			type = ECT_TypeNull;
		}

		short shID;					//卡牌ID
		uint32 unTypeID[ECT_MaxID];	//主将or宠物or坐骑的ID
		int nLevel;					//品质or等级
		ECardType type;
		SImage sBrightImg;			//亮的图片
		SImage sDarkImg;			//暗的图片
		std::string strName;		//名字
	};

	typedef std::vector< SCard > CardVector;

public:
	CardIconConfig();
	virtual ~CardIconConfig();

	void AddData( SCard card );

	bool LoadCardIconConfig( const char* pszConfig );

	short GetCardIdByTypeId( uint32 typeId );

	static CardIconConfig& Instance()
	{
		static CardIconConfig s_xCardIcon;
		return s_xCardIcon;
	}

	std::vector< SCard > GetCardVec() { return m_vecCard; }

private:
	CardVector m_vecCard;
};
#define theCardIconConfig CardIconConfig::Instance()

#endif //_CARDICONCONFIG_