#ifndef __ROBOT_BASESTATE_H__
#define __ROBOT_BASESTATE_H__

// ������״̬
enum EBotState
{
    State_TryLogin = 0,
    State_WaitSwitchGate = 1,
    State_SwitchGate = 2,
    State_WaitCloseToNewGateServer = 3,
    State_GetChar = 4,
    State_WaitGetChar = 5,
    State_CreateChar = 6,
    State_EnterWorld = 7,
    State_Play = 8,
    State_Wait = 9,
    State_Idle = 10, // �ȴ���Ϣ
    State_ViewPackage = 11,// �鿴����
    State_EnterWorldQueue = 12, //�Ŷӵȴ�����ENTERWORLD
    State_ReLogin,
    State_End,
};

class StateManager;

class BaseState
{
public:
    BaseState( StateManager* pOwn) : _pStateManager( pOwn ){}
    virtual ~BaseState(){}    
    virtual void Run(){};
private:
    StateManager* _pStateManager;
};

class StateManager
{
public:
    StateManager();
    ~StateManager();

    uint32 RegisterBeginState( EBotState bs );
    uint32 ChangeState( EBotState bs );
    uint32 Update();
    //BaseState* GetBaseState
private:
    BaseState* _pCurrentState;
};
#endif // __ROBOT_BASESTATE_H__
