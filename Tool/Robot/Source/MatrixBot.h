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
    virtual void InitFirstPlayGame();			// ��ʼ�����У�װ���������
    void SetbInit(bool b) { bInit = b;}			// ���ó�ʼ������
    bool GetbInit(){ return bInit;}
    virtual void PlayGame();
    virtual bool Move2MatrixPoint();
    virtual void PlaySkill();//1808 1
    virtual void PlaySkillByID(int nSkillID);	// ͨ��nSkillID���ͷż���
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
	//��ȡ�̶������������BOT���� luo.qin 3.18
	bool GetRandBotPos( float &fPosX, float &fPosY, DWORD dwMapID, float fBeginPosX, float fBeginPosY);
    int  GetCurrentMap();
    //void FlyToMatrixPos();
    void AddHpTimer();
    void PlaySkillTimer();
    bool PlayBotMove();
    void PlayMountTimer();
    bool ergodicItemBag(int nItemID);	// �����������鿴�Ƿ���nItemID����Ʒ
    bool DecideVisualSuit();			// �ж�ʱװλ
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
    bool bIsFly;					// �Ƿ�Ҫ����
    bool bGetPos;					// �Ƿ�Ҫȡ���Լ�������
    D3DXVECTOR3 selfPos;			// �Լ�������
    bool bMoveBack;					// �Ƿ������ƶ�
    GameTimerEx _addHpTime;			// ��Ѫʱ��
    GameTimerEx _PlaySkillTime;		// �ͷż��ܶ�ʱ��
    D3DXVECTOR3 MoveTargetPos;		// �ƶ�Ŀ��������
    bool bGetEquip;				    // ����װ��
    bool bIsEquip;					// ��װ��
    GameTimerEx _EquipTimer;		// ��װ����ʱ��
    bool bIsRide;					// �ٻ�����
    GameTimerEx _RideTime;			// ����ʱ��
    //////////////////////////////////////////////////////////////////////////
#if defined(Lua_Bind)
    LuaBindManager luaScript;       // luabind�ű����������
#elif defined(Lua_Plus)
    LuaPlusManager luaScript; //luaplus�ű����������
#endif
    bool bInit;
public:
    typedef std::vector<SMountItem> SDromeContainer;
    typedef SDromeContainer::iterator ItrSDromeContainer;

    enum DromeOperation
    {
        EDO_Active   = 0,   // ��ս
        EDO_UnActive = 1,   // ��Ϣ
        //EDO_Ride     = 2, // ����
        //EDO_UnRide   = 3, // ����
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