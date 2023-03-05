#ifndef __TITLE_H__
#define __TITLE_H__

/************************************************************************
	Id				�ƺ�Id�����߼������ã�����Ϊ��  
    Type			�ƺ�����, ����:1 ��ְ:2 �ٸ�:3 �:4 ���:5 ��ϵ:6 ����:7 ����:8  ����:9  ��λ:10
  	Name			�ƺ����ƣ�������ʾ������Ϊ��
    Quality           �ƺ�Ʒ��
	Description		�ƺ�������������ʾ������Ϊ��	
	nStatusId		�ƺŹ��ص�״̬Id������Ϊ��    
    TimeLimit       ʱЧ�Գƺ�          //����Ϊ0, ����Ϊ����ʱ�� (��)
    Displace        �ƺű�ȡ��          //����Ϊ0, ����Ϊ�ƺ�id
    NextTitleID     // ��һ���ƺ�
    bIsScript        //�Ƿ�ű����ƻ�øóƺ�
    nConditionType   ��ø�������������� ɱ��:1  ����:2 �ȼ�:3 ��Ǯ:4 ����:5 ��ѫֵ:6
    nParameter1      ����1
    nParameter2      ����2
    
************************************************************************/

#define theTitleConfig TitleConfig::Instance()   //ʵ���ӿ�

#include <string>
#include <vector>
#include <map>

class TitleConfig
{
public:
    enum TitleType		//�ƺ�����
    {
        Title_Init = 0,

        Title_Gut,              //����
        Title_Official,			//��ְ
        Title_Feudal,		    //�ٸ�
        Title_Campaign,         //�
        Title_Folklore,         //���
        Title_Marriage,         //���޹�ϵ
        Title_Fame,             //����
        Title_Legend,           //����
        Title_Especial,         //����
        Title_Knight,           //��λ
        Title_Teacher,          // ʦ���ƺ�
        Title_Student,          // ͽ�ܳƺ�

        Title_End,
    };

    enum TitleConditionType         //��óƺŵķ�ʽ
    {
        Condition_Init = 0,

        Condition_KillEnemy,            //ɱ��
        Condition_Quest,                //����
        Condition_Level,                //�ȼ�
        Condition_Money,                //��Ǯ
        Condition_Friend,               //����
        Condition_Exploit,              //��ѫֵ
        Condition_Reputation,           //����

        Condition_End,
    };

    enum TitleValue
    {
        Init_ID = 0,			// ��Ч��id
		Max_ID  = 32767,		// ����Id
        Status_Level = 1,		// �ƺŶ�Ӧ��״̬�ȼ���Ĭ�� = 1
        Init_Param = 0,			// ��Ч�Ĳ���
		Title_Max_Displace = 10 // ���ɶ����ĳƺ�����
    };

public:
	struct Title 
	{
		typedef std::map< short, Title > TitleSet;
		typedef std::map< short, Title >::iterator TitleSetIter;
		typedef std::map< short, Title >::const_iterator TitleSetConstIter;

		short nID;		//0Ϊ��Ч
		unsigned char nType;
		unsigned short nStatusID;
        unsigned short nStatusLevel;
		std::string strName;
		std::string strDescription;
        unsigned short nQuality;
        unsigned short nTimeLimit;      // �ƺŵ�ʱ������ ��λ: Сʱ( nTimeLimit = 0 һֱ��Ч ) 
        unsigned short nDisplaceIds[Title_Max_Displace];
        bool bIsScript;
        unsigned char nConditionType;
		bool bInvisible;
        unsigned int nParameter1;
        unsigned int nParameter2;
		unsigned long dwColor;
		unsigned short nBuffId;
		unsigned short nBuffLevel;
		//int nBeDisplaced;//�кܶ�ƺſ��Զ����˳ƺ�, ����		
		TitleSet BeDisplaced;

        Title() : nID(Init_ID), strName(""), strDescription(""), nType(Title_Init), nStatusID(0), nQuality(1), nStatusLevel(Status_Level), nTimeLimit(0),
            bIsScript(false), nConditionType(Title_Init), nParameter1(Init_Param), nParameter2(Init_Param), dwColor(0xffffffff)
        { 
			for( int i = 0 ; i < Title_Max_Displace ; ++ i )
				nDisplaceIds[i] = 0;

			nBuffId = 0;
			nBuffLevel = 0;
        }

        Title(const Title& xTitle)
        {
            *this = xTitle;
        }

        Title& operator = (const Title& xTitle)
		{
			if (this != &xTitle)
			{
                nID             = xTitle.nID;
                nType           = xTitle.nType;
                strName         = xTitle.strName;
                strDescription  = xTitle.strDescription;
                nStatusID       = xTitle.nStatusID;
                nQuality        = xTitle.nQuality;
                nStatusLevel    = xTitle.nStatusLevel;
                nTimeLimit		= xTitle.nTimeLimit;
                //nDisplaceIds    = xTitle.nDisplaceIds;
				for( int i = 0 ; i < Title_Max_Displace ; ++ i )
					nDisplaceIds[i] = xTitle.nDisplaceIds[i];
                bIsScript       = xTitle.bIsScript;
                nConditionType  = xTitle.nConditionType;
				bInvisible		= xTitle.bInvisible;
                nParameter1     = xTitle.nParameter1;
                nParameter2     = xTitle.nParameter2;
				dwColor			= xTitle.dwColor;
				nBuffId			= xTitle.nBuffId;
				nBuffLevel		= xTitle.nBuffLevel;
				BeDisplaced.clear();
				for( TitleSetConstIter iter = xTitle.BeDisplaced.begin(); iter != xTitle.BeDisplaced.end(); ++ iter )
					BeDisplaced.insert( std::make_pair( (*iter).first, (*iter).second ) );

			}

			return *this;
		}

        bool operator == (const int Id) { return (this->nID == Id); }
        bool operator < (const Title& xTitle) { return (this->nID < xTitle.nID); }
        
        const unsigned short GetID() const { return nID; }
        const unsigned char GetType() const { return nType; } 
        const unsigned short GetStatusID() const { return nStatusID; }
        const unsigned short GetQuality() const { return nQuality; }
        const unsigned short GetStatusLevel() const { return nStatusLevel; }
        const char* GetName() const { return strName.c_str(); }
        const char* GetDescription() const { return strDescription.c_str(); }
        const unsigned short GetTimeLimit() const { return nTimeLimit; } 
        const bool CanDisplace( int nTitleId ) const;
		const unsigned short* GetDisplaceIds() const{ return nDisplaceIds; }
        const unsigned short GetDisplaceId( int nIndex) const
        { 
            if ( nIndex < 0 || nIndex >= Title_Max_Displace )
            {
                return Init_ID;
            }

            return nDisplaceIds[nIndex];
        }
        const unsigned short GetPrevTitleId( bool bOnly = false ) const
		{
			if( bOnly && nDisplaceIds[1] != 0 )// ��ֹһ����ʱ�򣬷���0
				return 0;
			return nDisplaceIds[0]; 
		}
		const unsigned short GetNextTitleId( bool bOnly = false ) const;
        const bool IsScript() const { return bIsScript; }
        const unsigned char GetConditionType() const { return nConditionType; }
		const bool GetInvisible() const{ return bInvisible; }
        const unsigned int GetParameter1() const { return nParameter1; }
        const unsigned int GetParameter2() const { return nParameter2; }
		const bool IsMultiDisplaced() const { return BeDisplaced.size() > 1; }				
		const TitleSet& GetBeDisplaceds() const{ return BeDisplaced; }

		unsigned short GetBuffId() { return nBuffId; }
		unsigned short GetBuffLevel() { return nBuffLevel; }
	};

protected:
	TitleConfig();
public:
	~TitleConfig();

	inline static TitleConfig& Instance()
	{
		static TitleConfig s_xTitle;
		return s_xTitle;
	}

	bool LoadTitleConfig(const char* szFile);

	bool AddTitle(Title &xTitle, bool bReplace = false);
	bool RemoveTitle(short ID);

	unsigned int GetTitleCount() { return static_cast<unsigned int>(m_vecTitle.size()); }

	Title* GetTitleByIndex(unsigned int nIndex);
	Title* GetTitleByTitleID(short nID);
    
    Title* GetTitleByTitleName(const char* szName);
    short GetTitleIDByTitleName(const char* szName);

    Title* GetTitleByConditionType(short nConditionType, unsigned int nParameter1, unsigned int nParameter2);

    unsigned short GetTitleTimeLimit(short nID);
    bool IsScriptTitle(short nID);

	bool SaveTitleConfig(const char* szFile);

	const std::vector<Title>& GetTitleList() const{ return m_vecTitle; }

private:
	std::vector<Title> m_vecTitle;
    std::map<std::string, short> m_mapNameToID;

public:
	typedef std::vector<Title>::iterator titleiter;
    typedef std::map<std::string, short>::iterator mapiter;
};


#endif
