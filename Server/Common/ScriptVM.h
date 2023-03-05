/********************************************************************
    Filename:    ScriptVM.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SCRIPTVM_H__
#define __COMMON_SCRIPTVM_H__

#pragma once

#include "ScriptCommand.h"
#include "MsgBase.h"

/*    Script VM��������
1.ʲô��Script VM
    Script VM->�ű������
    Script��һ���ı���������������������
2.Ϊʲô��ҪScript VM
    �ű���������Ϸ���Ƶĳ����ֶΣ�
    �ѿ��ƽű���Դ������룬
    ʹ���ڲ���ҪԴ����Ļ����ϣ�����ʵ�ֶ���Ϸ���ݣ����̣����Ƶķ��ʣ�
3.Script VM�Ĺ�������
    ����������������Ϊһ��cpu��
    cpuΪÿһ���ű�����һ��vm���൱�ڽ��̣�
    ����Ϸ�е���Ҵ����¼���ͬһʱ�����ֻ�ܴ���һ���¼���
    vm����һ��thread���൱���̣߳�����������������У�
    ��ҽ���ű�ִ��״̬��
    ������ִ�нű���������������͵Ľű�ָ�
    ����ȴ���ҵ����ť������ѡ��˵���
    thread���ң�ֱ�������ɲ�����
    vm����thread���ظ����ϵ����̣�ֱ���ű�ִ��ȫ����ɡ�

    cpu��һ��ʱ��ִֻ��һ��thread��ֱ��thread�������߹���
    �����Ϳ���Ϊcpu����һЩȫ�ֱ�����
    ���統ǰnpc����ǰִ�нű���character�ȵȣ�
    ��ϵͳʵ�֣�
4.Script VMʵ�ֵ�һЩϸ��
    Jump��Call��
    Jump����������ת��ָ����ŵ�Proc
    Call����ָ����ŵ�Proc�������귵��
    ��������Ҫ��vm������һ��stack���������浱ǰ��ip

    ������ֻ��һ��ȫ�ֱ����ӿ�
    �����κη���������ȫ��ͨ��������ȫ�ֱ����ӿ�ʵ�֣�

    proc 0 ԭ���ǽű����
    ���ڸ�Ϊ��ʼ����ڣ�
    ���ڽű������ڴ��е�ʱ�̲ű�����
    ִ�������Ϊproc 1
5.Script VM�Ĺ������
    ����������������ָ��Ŀ¼�µ�����script��
    Ϊÿһ���Ϸ���script����һ��vm��

    script��Ϊ��ʼ���ű���ϵͳ���ýű���NPC�ű�
    ��ʼ���ű�ֻ��ϵͳ������ʱ����ã�
    �������������Դ�����ϵͳ״����
    ϵͳ���ýű�����ϵͳ����ʱ��һϵ�в�����
    ����ˢ�����ڣ����ߵ����ã�������ڲ����ȵȣ�
    Ҳִֻ��һ��
    NPC�ű�������Ϸ�����е�NPC��
    �ᱻ���ִ�У�

    Ϊ�˼�ϵͳʵ�֣���ʼ���ű���ϵͳ���ýű�ִ������Ժ�
    ����ɾ����vm����Ϊ����ֻ��ϵͳ������ʱ�򱻵��ã�
    �������Ͳ��ش��������ߵ�vm��������
    NPC��vm�洢��npc�ڲ���
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
        ERunState_RETURN  , // ����
        ERunState_READY   , // ׼����
        ERunState_HANGUP  , // ����
        ERunState_CONTINUE, // ����
        ERunState_CRASH   , // ����
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
    int   m_dwIPAddr;//��־�ű�ִ�е��ڼ���
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
    // thread����ֻ��return��huangup״̬�� return��ʾû��ʣ��Ľű���Ҫ���У���������һ���µ�vm huangup��ʾ��thread�����ڹ���״̬������ʣ��Ľű���Ҫ����
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
    CScriptVM*     m_pVM      ; // VM��ַ���ڿ��ٲ��� ����ʱ Reload����ܻ�� ����Ҫô���� ûôȫ��
    int            _vmId      ; // VMId ����Reloadʱ����߼�����
    int32          _targetId  ; // ����Id NpcId �ȵ�
    uint8          _callIdType; // Id������
    GameObjectId   _callId    ; // ����Դ��IdΨһ��ʶ CharId �� ��������Id
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
