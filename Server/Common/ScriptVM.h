/********************************************************************
    Filename:    ScriptVM.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTVM_H__
#define __COMMON_SCRIPTVM_H__

#pragma once

#include "ScriptCommand.h"
#include "MsgBase.h"

/*    Script VM控制流程
1.什么是Script VM
    Script VM->脚本虚拟机
    Script是一段文本，编译后在虚拟机上运行
2.为什么需要Script VM
    脚本是网络游戏控制的常用手段，
    把控制脚本和源代码分离，
    使得在不需要源代码的基础上，可以实现对游戏数据，流程，控制的访问，
3.Script VM的工作方法
    把整个服务器设想为一块cpu，
    cpu为每一个脚本创建一个vm，相当于进程，
    当游戏中的玩家触发事件后（同一时间玩家只能触发一个事件）
    vm创建一个thread（相当于线程），保存在玩家数据中，
    玩家进入脚本执行状态，
    服务器执行脚本，如果遇到阻塞型的脚本指令，
    比如等待玩家点击按钮，或者选择菜单，
    thread悬挂，直到玩家完成操作，
    vm载入thread，重复以上的流程，直到脚本执行全部完成。

    cpu在一个时刻只执行一个thread，直到thread结束或者挂起，
    这样就可以为cpu设置一些全局变量，
    比如当前npc，当前执行脚本的character等等，
    简化系统实现，
4.Script VM实现的一些细节
    Jump和Call，
    Jump无条件的跳转到指定编号的Proc
    Call调用指定编号的Proc，调用完返回
    这样就需要在vm中设置一个stack，用来保存当前的ip

    服务器只有一个全局变量接口
    操纵任何服务器变量全部通过服务器全局变量接口实现，

    proc 0 原来是脚本入口
    现在改为初始化入口，
    仅在脚本载入内存中的时刻才被调用
    执行入口设为proc 1
5.Script VM的管理机制
    服务器启动后，搜索指定目录下的所有script，
    为每一个合法的script建立一个vm，

    script分为初始化脚本，系统设置脚本，NPC脚本
    初始化脚本只在系统启动的时候调用，
    负责启动相关资源，检察系统状况，
    系统设置脚本配置系统运行时的一系列参数，
    比如刷怪周期，道具店配置，出口入口参数等等，
    也只执行一次
    NPC脚本配置游戏世界中的NPC，
    会被多次执行，

    为了简化系统实现，初始化脚本，系统配置脚本执行完成以后，
    立即删除其vm，因为他们只在系统启动的时候被调用，
    这样，就不必创建这两者的vm管理器，
    NPC的vm存储在npc内部，
*/

class CScriptVMThread;
class CScriptVMStack
{
public:
    enum
    {
        eMaxStackSize = 16
    };
public:
    CScriptVMStack();
    void Clear();
    BOOL Push( int n );
    BOOL Pop();
    BOOL Clone( CScriptVMStack* pStack );
    BOOL IsEmpty(){ return m_nStackSize == 0; }
    int  Top();

protected:
    int  m_nStackSize;
    int  m_nStack[eMaxStackSize];
};

class CScriptVM
{
public:
    enum EConstDefine
    {
        MAX_PROC = 16,
    };

    enum ERunState
    {
        ERunState_RETURN  , // 结束
        ERunState_READY   , // 准备好
        ERunState_HANGUP  , // 挂起
        ERunState_CONTINUE, // 运行
        ERunState_CRASH   , // 奔溃
    };
    
public:
    friend class CScriptCompiler;
    
    CScriptVM();
    ~CScriptVM();

    inline void AddCmd( CScriptCommand* cmd );
    void Execute();

    void Reset();
    inline void ResetIP();
    inline void SetIPAddr( DWORD dwIPAddr );
    inline void NextIP();
    inline void SetState( ERunState& state );
    inline void Continue();
    inline void Return();
    inline void Hangup();
    inline void Crash();

    inline void PushIPAddr();
    BOOL PopIPAddr();

    BOOL JumpToProc( int nProcId );

    void SaveThread( CScriptVMThread* thread );
    BOOL LoadThread( CScriptVMThread* thread );
    BOOL Execute( CScriptVMThread* thread );

    void Destroy();

    int GetProcAddr( int nProcId );
    BOOL ExcuteCmd( char* pszCmd );

    int GetCmdCount();
    inline CScriptCommand* GetCmd( int nIPAddr );

protected:
    std::vector<CScriptCommand*> m_vectorCmd;
    CScriptVMStack m_IPStack;
    
    int   m_anProcAddr[MAX_PROC];
    int   m_dwIPAddr;//标志脚本执行到第几行
    DWORD m_state;
};

class CScriptVMThread
{
public:
    CScriptVMThread(){ Reset(); }
    ~CScriptVMThread(){ Reset(); }

    void            SetVM( CScriptVM* vm )  { m_pVM = vm;         }
    CScriptVM*      GetVM()                 { return m_pVM;       }
    void            SetIdType( uint8 type ) { _callIdType = type; }
    uint8           GetIdType()             { return _callIdType; }
    void            SetCharId( GameObjectId nCharId ){ _callId = nCharId;  }
    GameObjectId    GetCharId()             { return _callId;     }
    void            SetDstId( int nId )     { _targetId = nId;    }
    int             GetDstId()              { return _targetId;   }
    void            Set( uint32 dwIPAddr, uint8 dwState ){ m_dwIPAddr = dwIPAddr; m_dwState = dwState; }
    DWORD           GetIPAddr() { return m_dwIPAddr; }
    DWORD           GetState()  { return m_dwState;  }
    CScriptVMStack* GetIPStack(){ return &m_IPStack; }
    BOOL            Restore();
    // thread现在只有return和huangup状态， return表示没有剩余的脚本需要运行，可以启动一个新的vm huangup表示此thread正处于挂起状态，还有剩余的脚本需要运行
    BOOL            IsHangup(){ return m_dwState == CScriptVM::ERunState_HANGUP; }
    BOOL            IsEnable(){ return m_pVM != 0; }
    BOOL            SetEntrance( int nProcId );
    void            CreateId();
    void            SetScriptType( uint8 type ) { _scriptType = type; }
    uint8           GetScriptType() { return _scriptType; }

    void Reset()
    {
        m_pVM      = NULL;
        _vmId      = -1;
        m_dwIPAddr = 0;
        m_dwState  = CScriptVM::ERunState_RETURN;
        m_IPStack.Clear();
        _callIdType    = 0;
        _callId    = 0;
        _targetId  = -1;
        _threadId  = -1;
        _scriptType = -1;
    }

protected:
    CScriptVM*     m_pVM      ; // VM地址便于快速查找 运行时 Reload后可能会变 所以要么重置 没么全清
    int            _vmId      ; // VMId 便于Reload时候的逻辑处理
    int32          _targetId  ; // 任务Id NpcId 等等
    uint8          _callIdType; // Id的类型
    GameObjectId   _callId    ; // 呼叫源的Id唯一标识 CharId 或 其他类型Id
    uint32         m_dwIPAddr ;
    uint8          m_dwState  ;
    CScriptVMStack m_IPStack  ;
    uint32         _threadId  ;
    int8           _scriptType;
};

//////////////////////////////////////////////////////////////////////////
// inline class function part
// inline class CScriptVM;

inline void CScriptVM::AddCmd( CScriptCommand* cmd )
{ 
    m_vectorCmd.push_back( cmd ); 
}

inline void CScriptVM::ResetIP()
{ 
    m_dwIPAddr = 0; 
}

inline void CScriptVM::SetIPAddr( DWORD dwIPAddr )
{ 
    m_dwIPAddr = dwIPAddr; 
}

inline void CScriptVM::NextIP()
{ 
    m_dwIPAddr++; 
}

inline void CScriptVM::SetState( ERunState& state )
{ 
    m_state = state; 
}

inline void CScriptVM::Continue()
{ 
    m_state = ERunState_CONTINUE; 
}

inline void CScriptVM::Return()
{ 
    m_state = ERunState_RETURN; 
}

inline void CScriptVM::Hangup()
{ 
    m_state = ERunState_HANGUP; 
}

inline void CScriptVM::Crash()
{ 
    m_state = ERunState_CRASH; 
}

inline void CScriptVM::PushIPAddr()
{ 
    //m_IPStack.push( m_dwIPAddr ); 
    m_IPStack.Push( m_dwIPAddr );
}

inline int    CScriptVM::GetCmdCount()
{ 
    return (int)(m_vectorCmd.size()); 
}

inline CScriptCommand* CScriptVM::GetCmd( int nIPAddr )
{ 
    return m_vectorCmd[nIPAddr]; 
}

#endif // __COMMON_SCRIPTVM_H__
