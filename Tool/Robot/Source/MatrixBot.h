#include "stdafx.h"
#include "MeRTLibsServer.h"
#include "AttackBot.h"
#include "LuaScriptManager.h" // LuaScript

#define POINT_ROW (30)
#define POINT_LINE (30)
class CMatrixBot:public CAttackBot
{
public:
    struct fPoint
    {
        fPoint()
        {
            x = 0.0;
            y = 0.0;
        }
        fPoint(float x,float y)
        {
            this->x = x;
            this->y = y;
        }
        float x;
        float y;
        void Clear()
        {
            x = 0.0;
            y = 0.0;
        }
    };
    typedef std::vector<fPoint> PointList;
    typedef PointList::iterator ItrPointList;

    CMatrixBot();
    ~CMatrixBot();
public:
    virtual void InitFirstPlayGame();			// 初始化飞行，装备，坐骑等
    void SetbInit(bool b) { bInit = b;}			// 设置初始化开关
    bool GetbInit(){ return bInit;}
    virtual void PlayGame();
    virtual bool Move2MatrixPoint();
    virtual void PlaySkill();//1808 1
    virtual void PlaySkillByID(int nSkillID);	// 通过nSkillID来释放技能
    virtual void InitPlayGame();
    virtual void LearnSkill(int id);
    virtual void EquipItem();
    virtual bool CheckWeapon();

    virtual PlayerInfo* GetLockPlayerInfo(GameObjectId shID);
    virtual GameObjectId LockTarget();
    virtual void PlayAttack();

    bool InitPoint();
    virtual void SetAreaInfo(SAreaInfo *pAreaInfo);
    fPoint GetPoint();
    fPoint GetBotPos();
	//获取固定区域内随机的BOT坐标 luo.qin 3.18
	bool GetRandBotPos( float &fPosX, float &fPosY, DWORD dwMapID, float fBeginPosX, float fBeginPosY);
    int  GetCurrentMap();
    //void FlyToMatrixPos();
    void AddHpTimer();
    void PlaySkillTimer();
    bool PlayBotMove();
    void PlayMountTimer();
    bool ergodicItemBag(int nItemID);	// 遍历背包，查看是否有nItemID的物品
    bool DecideVisualSuit();			// 判断时装位
    static ItrPointList itrPoint;
private:
    fPoint _Point[POINT_ROW][POINT_LINE];
    DWORD  RunTime;

	//DWORD  m_LastCreateTime;		// luo.qin 3.17
	//DWORD  m_ChangeEquipTime;		// luo.qin 3.21

    static PointList Points;
    static bool IsInitPoint;
    bool IsGetPoint;
    fPoint _CurPoint;  
    bool  IsLearnSkill;
    bool changemap;
    DWORD dwMapLoadTime;
    bool bIsInitPlayGame;
    int baseHp;
    DWORD ControlTime;
    bool bIsFly;					// 是否要飞行
    bool bGetPos;					// 是否要取得自己的坐标
    D3DXVECTOR3 selfPos;			// 自己的坐标
    bool bMoveBack;					// 是否往回移动
    GameTimerEx _addHpTime;			// 加血时间
    GameTimerEx _PlaySkillTime;		// 释放技能定时器
    D3DXVECTOR3 MoveTargetPos;		// 移动目标点的坐标
    bool bGetEquip;				    // 请求装备
    bool bIsEquip;					// 穿装备
    GameTimerEx _EquipTimer;		// 穿装备定时器
    bool bIsRide;					// 召唤坐骑
    GameTimerEx _RideTime;			// 骑马定时器
    //////////////////////////////////////////////////////////////////////////
#if defined(Lua_Bind)
    LuaBindManager luaScript;       // luabind脚本管理类对象
#elif defined(Lua_Plus)
    LuaPlusManager luaScript; //luaplus脚本管理类对象
#endif
    bool bInit;
public:
    typedef std::vector<SMountItem> SDromeContainer;
    typedef SDromeContainer::iterator ItrSDromeContainer;

    enum DromeOperation
    {
        EDO_Active   = 0,   // 出战
        EDO_UnActive = 1,   // 休息
        //EDO_Ride     = 2, // 骑马
        //EDO_UnRide   = 3, // 下马
        EDO_TotalOperation,
    };

    void GetDrome();
    void RemoveDrome(int Drome);
    void RandOperationDrome();
    virtual void OnMsgGetMount(Msg* pMsg);
    virtual void SwitchMsg(Msg* pMsg);
    virtual void OnMsgAckResult(Msg* pMsg);
    virtual void OnMsgChangeDrome( Msg* Msg);
    virtual void OnMsgAckEnterWorld( Msg* pMsg );
    SMountItem* FindMountByGuid(__int64 FindGuid);
    SMountItem* FindMountByIndex(int Index);
private:
    SDromeContainer  SDromes;
    DWORD   OperationTime;
};