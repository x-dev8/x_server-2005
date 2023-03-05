#pragma once

#include "MeRTLibs.h"
#include "ErrorCode.h"

struct EventRewardType
{
    int         id;          // ����Id
    std::string description; // ����

    bool operator == (int id)
    { return this->id == id; }

    bool operator == (const string &des)
    { return description == des; }
};

struct EventPeriodType
{
    int         id;          // ����Id
    std::string description; // ����

    bool operator == (int id)
    { return this->id == id; }

    bool operator == (const string &des)
    { return description == des; }
};

struct EventActivityType
{
	int         id;          // ����Id
	std::string description; // ����

	bool operator == (int id)
	{ return this->id == id; }

	bool operator == (const string &des)
	{ return description == des; }
};
struct EventCategorys
{
	int			id;			 // ���ID
	std::string description; // ����
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
        int typeId; // ����������
		int id;     // �����������µ�ID
		int count;  // ����
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

	std::string name;         // �����
	std::string description;  // �����
    std::string totalCount;   // ����ͬ��������ܺ����������ڽ���ָ��
    std::string openTime;     // ����ʱ�䣬���ڽ���ָ��
    std::string formulation;  // ���飬���ڽ���ָ��
	std::string picPath;      // �ͼƬ·��
    int id;                   // �Id
    int category;             // ����
	uint8 country;			  // ��������ң�Ĭ��0��ʾ�޹�������

	int mActivityType;		  // �����

	int	needLevel;		      // ��Ҫ��ҵȼ�
	int quality;		      // �Ƽ�Ʒ��
	int	count;			      // ������ɵĴ���
	int completeTimeVarIndex; // ��ȡ���ɵĴ�������
	int isHot;		          // �Ƿ��ȵ�
    int isPivot;              // �Ƿ����ص�
	int isEveryday;	          // �Ƿ�ÿ��
    int npcId;                // ��Ӧ��NpcId

    short periodTypeId;       // ��������,��EventPeriodType��ȡֵ
    short periodParameter;    // ���ڵľ�������,����EventPeriodType�仯

	std::string period;	      // ��������

    int year;           // BaseTime
    int month;
    int day;
    int hour;
    int minute;
	int week;

	int duration;		             // ����ʱ��
    std::string durationDescription; // ����ʱ�������
	int endWeek;		             // ����ʱ��
	int endHour;
	int endMinute;

	std::string npc;    // NpcName
	std::string mapName;
	int mapId;
	float mapPosX;
	float mapPosY;
    short scriptId;
    unsigned short  eventItemId;      // �¼�IconId

    bool operator == (const std::string &otherName) // ����find
    { return name == otherName; }

	std::vector<Reward>    rewards;	  // ����
	std::vector<Broadcast> broadcast; // �㲥

    bool DeleteEventRewardByIndex(const int &IndexId);         // ɾ��һ��EventReward����IndexId
    bool DeleteEventRewardByRewardId(const int &RewardId);     // ɾ��һ��EventReward����RewardId
    bool DeleteEventBroadcast(const int &BroadcastOffsetTime); // ɾ��һ��EventBroadcast����ƫ��ʱ��

    bool AddEventReward(const Event::Reward &reward);          // ���һ��EventReward
    bool AddEventBroadcast(const Event::Broadcast &broadcast); // ���һ��EventBroadcast

    bool ModifyEventReward(int RewardId,const Event::Reward &reward);                     // �޸�һ��EventReward,����:��Ҫ�޸�RewardId,�޸ĵĽ��
    bool ModifyEventBroadcast(int BroadcastOffsetTime,const Event::Broadcast &broadcast); // �޸�һ��EventBroadcast,����:��Ҫ�޸�BroadcastOffsetTime,�޸ĵĽ��

    Event::Reward*    GetEventRewardByRewardId(const int &RewardId);                    
    Event::Broadcast* GetEventBroadcastByOffsetTime(const int &BroadcastOffsetTime); 
    Event::Reward*    GetEventRewardByIndex(const unsigned int &index);                 
    Event::Broadcast* GetEventBroadcastByIndex(const unsigned int &index);           
    void BaseCopy (const Event &otherEvent); // ���ڱ༭����������rewards��broadcast
};

typedef std::vector<Event>           EventContents;
typedef EventContents::iterator      ItrEventContents;
typedef std::map<int, EventContents> WeekEventContents;

class EventManager
{
public:
    enum EFilterType
    {
        EFT_None,     // ��
        EFT_TimeNode, // ʱ���
    };

    struct SFilter
    { // ɸѡ��
        struct STimeNode 
        { // ʱ��ڵ�
            char month;
            char day;
            char hour;
            char minute;
        };

        char type;  // ɸѡ����
        union       // ֵ
        {
            STimeNode     tn;
            unsigned long value;
        };
    };

public:
	virtual ~EventManager() {}

	static EventManager& Instance()
	{ static EventManager s; return s;}

    // ����
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

	// �õ�����event content
	void GetMonthEventContents(const struct tm& nowtime, EventContents& out);
    
    bool AddEvent(const Event &event);                                   // ���
    bool DeleteEvent(const std::string &eventName);                      // ɾ��
    bool ModifiyEvent(const std::string &EventName ,const Event &event); // �޸�

    // ��ѯ
    Event*           GetEventByName           ( const std::string  &eventName );
    Event*           GetEventByIndex          ( const unsigned int &index     );
    EventPeriodType* GetEventPeriodTypeById   ( const unsigned int &id        );
    EventPeriodType* GetEventPeriodTypeByIndex( const unsigned int &id        );
    EventRewardType* GetEventRewardType       ( const unsigned int &id        );
    EventPeriodType* GetEventPeriodTypeByDes  ( const std::string  &des       );

    // ����
    bool Save(const std::string& filename);

    // ȡ�ô�С
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