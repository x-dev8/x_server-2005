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

		std::string strImg; //ͼƬ·��
		int nWidth;			//��
		int nHeight;		//��
		int nRow;			//��
		int nColumn;		//��
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

		short shID;			//���Ƴɾ�ID
		short shCardIDs[ MAX_CARDIDS ];	//����ID
		uint32 unItemID;	//������ƷID
		short shCardCount;	//��������

		SImage sBrightImg;			//����ͼƬ
		SImage sDarkImg;			//����ͼƬ
		std::string strName;		//����
		std::string strScriptAddr;  //�ű�
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