#pragma once

#include "MeRTLibs.h"
#include "ErrorCode.h"

struct EventRewardType
{
    int         id;          // 类型Id
    std::string description; // 描述

    bool operator == (int id)
    { return this->id == id; }

    bool operator == (const string &des)
    { return description == des; }
};

struct EventPeriodType
{
    int         id;          // 周期Id
    std::string description; // 描述

    bool operator == (int id)
    { return this->id == id; }

    bool operator == (const string &des)
    { return description == des; }
};

struct EventActivityType
{
	int         id;          // 周期Id
	std::string description; // 描述

	bool operator == (int id)
	{ return this->id == id; }

	bool operator == (const string &des)
	{ return description == des; }
};
struct EventCategorys
{
	int			id;			 // 类别ID
	std::string description; // 描述
	bool operator == (int id)
	{ return this->id == id; }

	bool operator == (const string &des)
	{ return description == des; }
};

typedef std::vector<EventPeriodType>       PeriodTypeContainer;
typedef PeriodTypeContainer::iterator      ItrPeriodTypeContainer;

typedef std::vector<EventRewardType>       EventRewardTypeContainer;
typedef EventRewardTypeContainer::iterator ItrEventRewardTypeContainer;

typedef std::vector<EventActivityType>		EventActivityTypeSet_t;
typedef EventActivityTypeSet_t::iterator	EventActivityTypeIt_t;

typedef std::vector<EventCategorys>			EventCategorysSet_t;
typedef EventCategorysSet_t::iterator		EventCategorysIt_t;

struct Event
{
	struct Reward 
	{
        int typeId; // 奖励的类型
		int id;     // 奖励的类型下的ID
		int count;  // 个数
        bool operator ==(const int &RewardId)
        { return typeId == RewardId;}
	};

	struct Broadcast
	{
		int         offsetTime;
		std::string content;
        bool operator ==(const int &Time)
        { return Time == offsetTime; }
	};

	std::string name;         // 活动名字
	std::string description;  // 活动描述
    std::string totalCount;   // 本日同个活动次数总和描述，用于今日指引
    std::string openTime;     // 开放时间，用于今日指引
    std::string formulation;  // 活动简介，用于今日指引
	std::string picPath;      // 活动图片路径
    int id;                   // 活动Id
    int category;             // 活动类别
	uint8 country;			  // 活动所属国家，默认0表示无国家限制

	int mActivityType;		  // 活动类型

	int	needLevel;		      // 需要玩家等级
	int quality;		      // 推荐品质
	int	count;			      // 可以完成的次数
	int completeTimeVarIndex; // 读取活动完成的次数索引
	int isHot;		          // 是否热点活动
    int isPivot;              // 是否是重点活动
	int isEveryday;	          // 是否每天
    int npcId;                // 对应的NpcId

    short periodTypeId;       // 周期类型,在EventPeriodType中取值
    short periodParameter;    // 周期的具体数字,更具EventPeriodType变化

	std::string period;	      // 周期描述

    int year;           // BaseTime
    int month;
    int day;
    int hour;
    int minute;
	int week;

	int duration;		             // 持续时间
    std::string durationDescription; // 持续时间的描述
	int endWeek;		             // 结束时间
	int endHour;
	int endMinute;

	std::string npc;    // NpcName
	std::string mapName;
	int mapId;
	float mapPosX;
	float mapPosY;
    short scriptId;
    unsigned short  eventItemId;      // 事件IconId

    bool operator == (const std::string &otherName) // 用于find
    { return name == otherName; }

	std::vector<Reward>    rewards;	  // 奖励
	std::vector<Broadcast> broadcast; // 广播

    bool DeleteEventRewardByIndex(const int &IndexId);         // 删除一个EventReward根据IndexId
    bool DeleteEventRewardByRewardId(const int &RewardId);     // 删除一个EventReward根据RewardId
    bool DeleteEventBroadcast(const int &BroadcastOffsetTime); // 删除一个EventBroadcast根据偏移时间

    bool AddEventReward(const Event::Reward &reward);          // 添加一个EventReward
    bool AddEventBroadcast(const Event::Broadcast &broadcast); // 添加一个EventBroadcast

    bool ModifyEventReward(int RewardId,const Event::Reward &reward);                     // 修改一个EventReward,参数:需要修改RewardId,修改的结果
    bool ModifyEventBroadcast(int BroadcastOffsetTime,const Event::Broadcast &broadcast); // 修改一个EventBroadcast,参数:需要修改BroadcastOffsetTime,修改的结果

    Event::Reward*    GetEventRewardByRewardId(const int &RewardId);                    
    Event::Broadcast* GetEventBroadcastByOffsetTime(const int &BroadcastOffsetTime); 
    Event::Reward*    GetEventRewardByIndex(const unsigned int &index);                 
    Event::Broadcast* GetEventBroadcastByIndex(const unsigned int &index);           
    void BaseCopy (const Event &otherEvent); // 用于编辑器，不拷贝rewards，broadcast
};

typedef std::vector<Event>           EventContents;
typedef EventContents::iterator      ItrEventContents;
typedef std::map<int, EventContents> WeekEventContents;

class EventManager
{
public:
    enum EFilterType
    {
        EFT_None,     // 无
        EFT_TimeNode, // 时间点
    };

    struct SFilter
    { // 筛选器
        struct STimeNode 
        { // 时间节点
            char month;
            char day;
            char hour;
            char minute;
        };

        char type;  // 筛选类型
        union       // 值
        {
            STimeNode     tn;
            unsigned long value;
        };
    };

public:
	virtual ~EventManager() {}

	static EventManager& Instance()
	{ static EventManager s; return s;}

    // 载入
	bool Load(const std::string& filename, const struct tm& nowtime);
    bool Load( const std::string& fileName );
    
    virtual long GetEventContents( const SFilter& filter, EventContents& output ){ return ER_Success; }

	// week event content
	const WeekEventContents& GetWeekEventContents() { return m_weekEventContents; }
	const EventContents&     GetEventContentsByWeek(int week) { return m_weekEventContents[week]; }

	// hot event content
	const EventContents& GetHotEventContents() { return m_hotEventContents; }

	// everyday event content
	const EventContents& GetEverydayEventContents() { return m_everydayEventContents; }

	// 得到本月event content
	void GetMonthEventContents(const struct tm& nowtime, EventContents& out);
    
    bool AddEvent(const Event &event);                                   // 添加
    bool DeleteEvent(const std::string &eventName);                      // 删除
    bool ModifiyEvent(const std::string &EventName ,const Event &event); // 修改

    // 查询
    Event*           GetEventByName           ( const std::string  &eventName );
    Event*           GetEventByIndex          ( const unsigned int &index     );
    EventPeriodType* GetEventPeriodTypeById   ( const unsigned int &id        );
    EventPeriodType* GetEventPeriodTypeByIndex( const unsigned int &id        );
    EventRewardType* GetEventRewardType       ( const unsigned int &id        );
    EventPeriodType* GetEventPeriodTypeByDes  ( const std::string  &des       );

    // 保存
    bool Save(const std::string& filename);

    // 取得大小
	int GetEverydayEventSize()   { return (int)m_hotEventContents.size(); }
    int GetAllEventSize()        { return (int)m_AllEventContents.size(); }
    int GetEventPeriodTypeSize() { return (int)EventPeriodTypes.size();   }
    int GetEventRewardTypeSize() { return (int)EventRewardTypes.size();   }
    int GetWeekdayEventSize(const unsigned short& week)
    { if (week > 7) return 0; return (int)m_weekEventContents[week].size(); }

    int GetRewardTypeByDes(const std::string &des);
    int GetPeriodTypeByDes(const std::string &des);

	const char* GetActivityTypeStr( int typeId );

	EventCategorysSet_t GetEventCategory(){return m_AllCategory;}

protected:
    EventManager(){}

protected:
	WeekEventContents        m_weekEventContents;
	EventContents            m_everydayEventContents;
	EventContents            m_hotEventContents;
    PeriodTypeContainer      EventPeriodTypes;
    EventRewardTypeContainer EventRewardTypes;

    EventContents            m_AllEventContents;

	EventActivityTypeSet_t	 m_AllActivityType;
	EventCategorysSet_t		 m_AllCategory;
};

#define theEventManager EventManager::Instance()