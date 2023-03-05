#ifndef __TITLE_H__
#define __TITLE_H__

/************************************************************************
	Id				称号Id，做逻辑索引用，不可为空  
    Type			称号类型, 剧情:1 官职:2 官府:3 活动:4 民间:5 关系:6 名望:7 传奇:8  特殊:9  爵位:10
  	Name			称号名称，用于显示，不可为空
    Quality           称号品质
	Description		称号描述，用于显示，不可为空	
	nStatusId		称号挂载的状态Id，可以为空    
    TimeLimit       时效性称号          //不是为0, 否则为具体时间 (天)
    Displace        称号被取代          //不是为0, 否则为称号id
    NextTitleID     // 下一级称号
    bIsScript        //是否脚本控制获得该称号
    nConditionType   获得该任务的条件类型 杀怪:1  任务:2 等级:3 金钱:4 好友:5 功勋值:6
    nParameter1      参数1
    nParameter2      参数2
    
************************************************************************/

#define theTitleConfig TitleConfig::Instance()   //实例接口

#include <string>
#include <vector>
#include <map>

class TitleConfig
{
public:
    enum TitleType		//称号类型
    {
        Title_Init = 0,

        Title_Gut,              //剧情
        Title_Official,			//官职
        Title_Feudal,		    //官府
        Title_Campaign,         //活动
        Title_Folklore,         //民间
        Title_Marriage,         //夫妻关系
        Title_Fame,             //名望
        Title_Legend,           //传奇
        Title_Especial,         //特殊
        Title_Knight,           //爵位
        Title_Teacher,          // 师傅称号
        Title_Student,          // 徒弟称号

        Title_End,
    };

    enum TitleConditionType         //获得称号的方式
    {
        Condition_Init = 0,

        Condition_KillEnemy,            //杀怪
        Condition_Quest,                //任务
        Condition_Level,                //等级
        Condition_Money,                //金钱
        Condition_Friend,               //好友
        Condition_Exploit,              //功勋值
        Condition_Reputation,           //声望

        Condition_End,
    };

    enum TitleValue
    {
        Init_ID = 0,			// 无效的id
		Max_ID  = 32767,		// 最大的Id
        Status_Level = 1,		// 称号对应的状态等级　默认 = 1
        Init_Param = 0,			// 无效的参数
		Title_Max_Displace = 10 // 最大可顶掉的称号数量
    };

public:
	struct Title 
	{
		typedef std::map< short, Title > TitleSet;
		typedef std::map< short, Title >::iterator TitleSetIter;
		typedef std::map< short, Title >::const_iterator TitleSetConstIter;

		short nID;		//0为无效
		unsigned char nType;
		unsigned short nStatusID;
        unsigned short nStatusLevel;
		std::string strName;
		std::string strDescription;
        unsigned short nQuality;
        unsigned short nTimeLimit;      // 称号的时间限制 单位: 小时( nTimeLimit = 0 一直有效 ) 
        unsigned short nDisplaceIds[Title_Max_Displace];
        bool bIsScript;
        unsigned char nConditionType;
		bool bInvisible;
        unsigned int nParameter1;
        unsigned int nParameter2;
		unsigned long dwColor;
		unsigned short nBuffId;
		unsigned short nBuffLevel;
		//int nBeDisplaced;//有很多称号可以顶掉此称号, 个数		
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
			if( bOnly && nDisplaceIds[1] != 0 )// 不止一个的时候，返回0
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
