#ifndef _CARDICONCONFIG_
#define _CARDICONCONFIG_

#include "MeRTLibs.h"

class CardIconConfig
{
public:
	enum ECardType
	{
		ECT_Pet,		//����
		ECT_Hero,		//����
		ECT_Mount,		//����
		ECT_TypeNull,	//��
		ECT_MaxID = 5,	//���ID����
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

		std::string strImg; //ͼƬ·��
		int nWidth;			//��
		int nHeight;		//��
		int nRow;			//��
		int nColumn;		//��
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

		short shID;					//����ID
		uint32 unTypeID[ECT_MaxID];	//����or����or�����ID
		int nLevel;					//Ʒ��or�ȼ�
		ECardType type;
		SImage sBrightImg;			//����ͼƬ
		SImage sDarkImg;			//����ͼƬ
		std::string strName;		//����
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