#include "IdleBot.h"

class CommondBot:public OnlineBot
{
public:
    struct CommondStruct
    {
        enum ECommondType
        {
            ECT_Chat = 0,   // 聊天
            ECT_Attack = 1, // 打斗
            ECT_FlyMap = 2,    // 飞地图
            ECT_ErrorCommond,
        };
        enum ECommondPriority
        {
            ECP_High = 2,
            ECP_Middle = 1,
            ECP_Low = 0,
        };
        //////////////////////////////////////////////////////////////////////////
        CommondStruct():
        CommondType(ECT_ErrorCommond),
        Param1(0),
        Param2(""),
        ProcessTime(0),
        Priority(ECP_Middle)
        {

        }

        bool operator ==(const CommondStruct &cmp)
        {
            if ( 
                (CommondType == cmp.CommondType)
                && (Param1 == cmp.Param1)
                && (Param2 == cmp.Param2)
                && (ProcessTime == cmp.ProcessTime)
                && (Priority == cmp.Priority)
                )
                return true;
            
            return false;
        }

        bool operator <(const CommondStruct &cmp)
        {
            if ( Priority < cmp.Priority )
                return true;

            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        unsigned int    CommondType; // 命令类型
        unsigned int    Param1;      // 参数1
        std::string     Param2;      // 参数2
        DWORD           ProcessTime; // 处理的时间
        unsigned short  Priority;    // 处理的优先级
        //////////////////////////////////////////////////////////////////////////
        CommondStruct(const CommondBot::CommondStruct& cp)
        {
            CommondType = cp.CommondType;
            Param1      = cp.Param1;
            Param2      = cp.Param2;
            ProcessTime = cp.ProcessTime;
            Priority    = cp.Priority;
        }

//         CommondStruct& operator =(const CommondBot::CommondStruct& cp)
//         {
//             CommondType = cp.CommondType;
//             Param1      = cp.Param1;
//             Param2      = cp.Param2;
//             ProcessTime = cp.ProcessTime;
//             Priority    = cp.Priority;
//         }
    };

public:
    typedef std::vector<CommondBot::CommondStruct> CommondStructContainer;
    typedef CommondStructContainer::iterator ItrCommondStructContainer;
public:
    CommondBot();
    ~CommondBot();

    void InitPlayGame();
    void PlayGame();
    void RunOperation(DWORD time);

    void AddCommond(const CommondBot::CommondStruct &_CommondStruct);
    void SubCommond(const CommondBot::CommondStruct &_CommondStruct);
    CommondStructContainer& operator = (const CommondStructContainer &CommondStructs)
    {
        _CommondStructs.clear();
        _CommondStructs = CommondStructs;
        IsReplaceCommond = true;
        return _CommondStructs;
    }
    //void SettingSameCommond(const CommondStructContainer &CommondStructs);

    CommondBot::CommondStructContainer& GetBotCommondStructs(){return _CommondStructs;}
private:
    CommondBot(const CommondBot& ojb);

    CommondStructContainer _CommondStructs;
    bool            IsReplaceCommond;
    DWORD           CurRunnTime;
    ItrCommondStructContainer CurRunItr;
    bool            AutoMove;
};