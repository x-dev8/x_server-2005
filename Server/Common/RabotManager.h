#ifndef __GAMEPROTECTMANAGER_H__
#define __GAMEPROTECTMANAGER_H__
/************************************************************************
                    防外挂系统
        Filename:     RabotManager.h
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include <string>
#include <vector>
#include "MeRTLibsServer.h"
#include "Memory_pool.h"
#include "Singleton.h"
#include "GameTimer.h"

namespace RabotDefine
{
    enum EGameProtectConstDefine
    {
        EGP_MaxSystemErrorCount = 2,        // 返回的系统级别错误次数,超过此次数认为作弊,T下线( 如果以后确定是作弊,则封号处理 )
        EGP_ResultTimeOutCount  = 2,        // 超时未回应服务器次数
        EGP_ResultTimeOut       = 12010,    // 发送检测函数以后,超过该时间未响应,累计次数超过 EGP_ResultTimeOutCount 认为作弊
        EGP_CheckSpaceTime      = 300000,   // 进入游戏后, 4分钟后开始检测
        EGP_UpdateSpaceTime     = 5000,     // 5秒update一次
        EGP_FuncNameLength      = 41,       // 执行函数名的长度

        EGP_DoNothing           = 0,
        EGP_SendCheckCode       = 1,
        EGP_KickPlayer          = 2,

        EGP_Delete              = 0,
        EGP_Success             = 1,
        EGP_Failed              = 2,

        EGP_InitResult          = 0,
        EGP_MaxCodeLength       = 4096,     // 检测代码最大长度
        EGP_ChangeCodeSpaceTime = 60 * 60 * 1000,  // 两小时切换一次检测代码

        EGP_CheckCode           = 1,
        EGP_GetProcessList      = 2,
        EGP_NotResult           = 0xFFFF,

        EGP_CheckFirstTime      = 0,
        EGP_CheckStatusInit     = 1,
        EGP_WaitSendCode        = 2,
        EGP_WaitCheckResult     = 3,
    };
}

#define CheckCheatConfigFile "..\\CheckCheat\\CheckCheat.dll"
#define CheckCheatConfigPath "..\\CheckCheat"
#define ProcessListFilePath  "..\\Output\\Processlist\\"

class CheckData : INHERIT_POOL(CheckData)
{
public:
    DECLARE_POOL_FUNC(CheckData)

    CheckData() { Initialize(); }
    CheckData( unsigned int nPlayerID )
    {
        Initialize(); 
        SetPlayerID( nPlayerID );
    }

    void Initialize()
    {
        m_uchCheckStatus = RabotDefine::EGP_CheckStatusInit;
        m_nRightResult = RabotDefine::EGP_InitResult;
        m_uchSystemErrorCount = 0;
        m_uchTimeOutCount = 0;
    }

    unsigned int GetPlayerID() const { return m_dwPlayerID; }
    unsigned int GetRightResult() const { return m_nRightResult; }
    unsigned char GetSystemErrorCount() const { return m_uchSystemErrorCount; }
    unsigned char GetTimeOutCount() const { return m_uchTimeOutCount; }
    unsigned char GetCheckStatus() const { return m_uchCheckStatus; }

    void SetPlayerID( unsigned int nValue ) { m_dwPlayerID = nValue; }
    void SetRightResult( unsigned int nValue ) { m_nRightResult = nValue; }
    void SetSystemErrorCount( unsigned char uchValue ) { m_uchSystemErrorCount = uchValue; }
    void SetTimeOutCount( unsigned char uchValue ) { m_uchTimeOutCount = uchValue; }
    void SetCheckStatus( unsigned char uchValue ) { m_uchCheckStatus = uchValue; }
    void StartOperateTimer( unsigned int nCurrentTime, unsigned int nSpaceTime )
    { m_xOperateTimer.StartTimer( nCurrentTime, nSpaceTime ); }

    unsigned short Update( unsigned int dwCurrentTime );

protected:
    unsigned int m_dwPlayerID;           // 玩家的dbid
    unsigned int m_nRightResult;         // 保存检测函数的正确值
    unsigned char m_uchSystemErrorCount; // 系统错误次数
    unsigned char m_uchTimeOutCount;     // 超时次数
    unsigned char m_uchCheckStatus;
    GameTimerEx m_xOperateTimer;         // 定时器
};

// 检测代码信息结构
class CodeData
{
public:
    CodeData() : m_nRightResult( 0 ) , m_nCodeLength( 0 ) 
    {
        memset( m_szCheckCode, 0, sizeof( m_szCheckCode ) );
        memset( m_szCodeFuncName, 0, sizeof( m_szCodeFuncName ) );
    }

    CodeData( unsigned int nResult, void* pAddress, unsigned short ustLength, const char* pszFunc )
    {
        m_nRightResult = nResult;
        SetCheckCode( pAddress, ustLength );
        SetCodeFuncName( pszFunc );
    }

    void SetRightResult( unsigned int nValue ) { m_nRightResult = nValue; }
    void SetCheckCode( void* pValue, int nLength )
    {
        memcpy_s( m_szCheckCode, sizeof( m_szCheckCode ), pValue, nLength );
        m_nCodeLength = nLength;
    }
    void SetCodeFuncName( const char* szName ) { strncpy_s( m_szCodeFuncName, sizeof( m_szCodeFuncName ), szName, sizeof( m_szCodeFuncName ) - 1 ); }

    unsigned int GetRightResult() const { return m_nRightResult; }      // 获得正确答案
    const char* GetCheckCode() const { return m_szCheckCode; }          // 获得检测代码地址
    unsigned short GetCodeLength() const { return m_nCodeLength; }      // 获得检测代码长度
    const char* GetCodeFuncName() const { return m_szCodeFuncName; }    // 获得检测代码函数名

private:
    unsigned int m_nRightResult;                              // 正确的答案
    char m_szCheckCode[ RabotDefine::EGP_MaxCodeLength ];     // 执行代码
    unsigned short m_nCodeLength;                             // 函数长度
    char m_szCodeFuncName[ RabotDefine::EGP_FuncNameLength ]; // 函数名称
};

template< class T >
class RabotManager : public ISingletion< RabotManager< T > >
{
public:
    RabotManager();
    ~RabotManager();

    bool AddCheckPlayer( unsigned int nPlayerID );          // 添加玩家
    void RemoveCheckPlayer( unsigned int nPlayerID );       // 删除玩家
    CheckData* GetCheckPlayer( unsigned int nPlayerID );    // 获得玩家

    T* GetPlayerByID( unsigned int nPlayerID );             // 获得玩家指针 ( 这个函数在不同游戏里需要特化 )
    unsigned short SendCheckCodeToPlayer( CheckData* xCheckData, CodeData* pCodeData, unsigned int dwSendTime ); // 发送检测代码
    unsigned short SendGetProcessListToPlayer( unsigned int nPlayerID, unsigned int dwSendTime );        // 发送检测代码, 获得客户端进程列表和客户端加载的模块
    unsigned short KickPlayerByErrorResult( unsigned int nPlayerID, unsigned int dwErrorResult );        // T掉玩家

    bool LoadCheckCheatConfig( const char* pszFileName );       // 加载资源 ( 注意内存的释放 )
    void ReleaseCheckCodeAddress();
    CodeData* GetCodeDataByIndex( int nIndex );                 // 获得检测代码信息
    CodeData* GetCodeDataByRand(); 
    bool IsHaveCodeData() { return !m_vecCodeData.empty(); }    // 是否有检测代码
    unsigned int GetCodeDataCount() { return static_cast< unsigned int >( m_vecCodeData.size() ); }
    void RunCheckCheatUpdate( unsigned int dwCurrentTime );      // 自动更新
    void ProcessChangeCheckCode( unsigned int dwCurrentTime );      // 更换检测代码
    void ProcessResult( unsigned int nPlayerID, unsigned int nResult );     // 处理回传的结果

    void SetMaxSystemError( unsigned int nValue ) { m_nMaxSystemError = nValue; }
    unsigned int GetMaxSystemError() { return m_nMaxSystemError; }

    void SetCheckOpen( bool bValue ){ m_bCheckOpen = bValue; }
    bool GetCheckOpen() { return m_bCheckOpen; }

    void SetConfigVersion( unsigned int nValue ) { m_nConfigVersion = nValue; }
    unsigned int GetConfigVersion() { return m_nConfigVersion; }

    void DoneChangeConfigTimer() { m_xChangeConfigTimer.NextTimer( 1 ); }
    const char* GetLoadFileName() const { return m_strLoadFile.c_str(); }

private:

    typedef std::map< unsigned int, CheckData* > MapCheckData;
    typedef MapCheckData::iterator MapCheckDataIter;

    typedef std::vector< CodeData > CodeDataVector;
    typedef CodeDataVector::iterator CodeDataVecIter;
    typedef CodeDataVector::const_iterator CodeDataVecConstIter;
    
    MapCheckData m_mapPlayerCheckData;          // 保存的玩家检测信息
    CodeDataVector m_vecCodeData;               // 检测代码信息容器
    int m_nCodeDataIndex;
    CodeData m_xGetProcessList;                 // 获得进程列表的代码信息
    bool m_bCheckOpen;                          // 是否开启检测外挂
    unsigned int m_nMaxSystemError;             // 从配置外间最大系统级错误码
    unsigned int m_nConfigVersion;              // 从配置文件里面获得的版本号
    std::string m_strLoadFile;                  // 当前加载的文件
    GameTimerEx m_xUpdateTimer;                 // 更新Timer
    GameTimerEx m_xChangeConfigTimer;           // 更换资源的Timer
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
RabotManager< T >::RabotManager() : m_nMaxSystemError( 0xFF ), m_bCheckOpen( false ), m_nConfigVersion( 0 ), m_nCodeDataIndex( 0 )
{
    m_mapPlayerCheckData.clear();
    m_vecCodeData.clear();
    m_strLoadFile.clear();
    m_xUpdateTimer.StartTimer( 1, RabotDefine::EGP_UpdateSpaceTime );
    m_xChangeConfigTimer.StartTimer( 1, RabotDefine::EGP_ChangeCodeSpaceTime );
}

template< class T >
RabotManager< T >::~RabotManager()
{
    ReleaseCheckCodeAddress();
    for ( MapCheckDataIter iter = m_mapPlayerCheckData.begin(); iter != m_mapPlayerCheckData.end(); ++iter )
    {
        iter->second->Release();
    }

    m_mapPlayerCheckData.clear();
}

template< class T >
bool RabotManager< T >::AddCheckPlayer( unsigned int nPlayerID )
{
    MapCheckDataIter iter = m_mapPlayerCheckData.find( nPlayerID );
    if ( iter != m_mapPlayerCheckData.end() )
    { return false; }
    
    CheckData* pCheckData = NEW_POOL(CheckData);
    if ( pCheckData == NULL )
    { return false; }

    pCheckData->SetPlayerID( nPlayerID );
    pCheckData->SetCheckStatus( RabotDefine::EGP_CheckFirstTime );        // 设置第一次验证
    return m_mapPlayerCheckData.insert( make_pair( nPlayerID, pCheckData ) ).second;
};

template< class T >
inline void RabotManager< T >::RemoveCheckPlayer( unsigned int nPlayerID )
{
    MapCheckDataIter iter = m_mapPlayerCheckData.find( nPlayerID );
    if ( iter == m_mapPlayerCheckData.end() )
    { return; }

    iter->second->Release();
    m_mapPlayerCheckData.erase( iter );
}

template< class T >
CheckData* RabotManager< T >::GetCheckPlayer( unsigned int nPlayerID )
{
    MapCheckDataIter iter = m_mapPlayerCheckData.find( nPlayerID );
    if ( iter == m_mapPlayerCheckData.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
unsigned short RabotManager< T >::SendCheckCodeToPlayer( CheckData* pCheckData, CodeData* pCodeData, unsigned int dwSendTime )
{
    if ( pCheckData == NULL )
    { return RabotDefine::EGP_Delete; }

    T* pPlayer = GetPlayerByID( pCheckData->GetPlayerID() );
    if ( pPlayer == NULL )
    { return RabotDefine::EGP_Delete; }

    // 需要实现ProcessSendCheckCheatData函数
    if ( pPlayer->ProcessSendCheckCheatData( pCodeData, RabotDefine::EGP_CheckCode ) )
    {
        pCheckData->SetRightResult( pCodeData->GetRightResult() );
        pCheckData->SetCheckStatus( RabotDefine::EGP_WaitCheckResult );
        pCheckData->StartOperateTimer( dwSendTime, RabotDefine::EGP_ResultTimeOut );

        return RabotDefine::EGP_Success;
    }

    pCheckData->Initialize();
    return RabotDefine::EGP_Failed;
}

template< class T >
unsigned short RabotManager< T >::SendGetProcessListToPlayer( unsigned int nPlayerID, unsigned int dwSendTime )
{
    // 如果正在等待验证,就不发送消息
    CheckData* pCheckData = GetCheckPlayer( nPlayerID );
    if ( pCheckData == NULL || pCheckData->GetCheckStatus() == RabotDefine::EGP_WaitCheckResult )
    { return RabotDefine::EGP_Failed; }

    T* pPlayer = GetPlayerByID( nPlayerID );
    if ( pPlayer == NULL )
    { return RabotDefine::EGP_Delete; }

    if ( pPlayer->ProcessSendCheckCheatData( &m_xGetProcessList, RabotDefine::EGP_GetProcessList ) )
    {
        pCheckData->SetRightResult( m_xGetProcessList.GetRightResult() );
        pCheckData->SetCheckStatus( RabotDefine::EGP_WaitCheckResult );
        pCheckData->StartOperateTimer( dwSendTime, RabotDefine::EGP_ResultTimeOut );
        pCheckData->SetTimeOutCount( RabotDefine::EGP_ResultTimeOutCount - 1 );           // 设置超时次数, 没有回消息 直接干掉

        return RabotDefine::EGP_Success;
    }

    pCheckData->Initialize();
    return RabotDefine::EGP_Failed;
}

template< class T >
unsigned short RabotManager< T >::KickPlayerByErrorResult( unsigned int nPlayerID, unsigned int dwErrorResult )
{
    T* pPlayer = GetPlayerByID( nPlayerID );
    if ( pPlayer == NULL )
    { return RabotDefine::EGP_Delete; }

    // 需要实现ProcessKickByCheckCheat函数,具体策略实现
    // 不能直接Exit, 否则循环中迭代器失效
    if ( pPlayer->ProcessKickByCheckCheat( dwErrorResult ) )
    {
        return RabotDefine::EGP_Success;
    }

    return RabotDefine::EGP_Failed;
}

template< class T >
void RabotManager< T >::ReleaseCheckCodeAddress()
{
    m_vecCodeData.clear();
}

typedef int ( * __GetCheckFuncCount )();                                  // 得到检测函数数量
typedef char* ( * __GetCheckFuncName )( int nIndex );                     // 得到检测函数的名字
typedef int ( * __GetCheckFuncLength )( void* pFunc, int nMaxLength );    // 得到检测函数长度
typedef unsigned int ( * __GetFuncRightResult )( const char* pszFunc );   // 得到检测函数的正确答案
typedef int ( * __GetMaxSystemError )();                                  // 最大系统错误
typedef int ( * __GetVersion )();                                         // 获得版本号

template< class T >
bool RabotManager< T >::LoadCheckCheatConfig( const char* pszFileName )
{
    if ( pszFileName == NULL || pszFileName[0] == 0 )
    { return false; }

    HMODULE hHandle = ::LoadLibraryA( pszFileName );
    if ( hHandle == NULL )
    { return false; }

    __GetVersion MyGetVersion = ( __GetVersion )::GetProcAddress( hHandle, "GetCheckVersion" );
    if ( MyGetVersion == NULL )
    { 
        FreeLibrary( hHandle );
        return false;
    }

    //if ( MyGetVersion() == GetConfigVersion() )         // 版本没变就不读取了
    //{ 
    //    FreeLibrary( hHandle );
    //    return true;
    //}
    
    __GetMaxSystemError MyGetMaxSystemError = ( __GetMaxSystemError )::GetProcAddress( hHandle, "GetMaxSystemError" );
    if ( MyGetMaxSystemError == NULL )
    { 
        FreeLibrary( hHandle );
        return false;
    }

    __GetCheckFuncCount MyGetCheckFuncCount = ( __GetCheckFuncCount )::GetProcAddress( hHandle, "GetCheckFuncCount" );
    if ( MyGetCheckFuncCount == NULL )
    { 
        FreeLibrary( hHandle );
        return false;
    }

    __GetCheckFuncName MyGetCheckFuncName = ( __GetCheckFuncName )::GetProcAddress( hHandle, "GetCheckFuncName" );
    if ( MyGetCheckFuncName == NULL )
    { 
        FreeLibrary( hHandle );
        return false;
    }

    __GetCheckFuncLength MyGetCheckFuncLength = ( __GetCheckFuncLength )::GetProcAddress( hHandle, "GetCheckFuncLength" );
    if ( MyGetCheckFuncLength == NULL )
    {
        FreeLibrary( hHandle );
        return false;
    }

    __GetFuncRightResult MyGetFuncRightResult = ( __GetFuncRightResult )::GetProcAddress( hHandle, "GetFuncRightResult" );
    if ( MyGetFuncRightResult == NULL )
    { 
        FreeLibrary( hHandle );
        return false;
    }

    // 还要把所有的错误码对应的外挂名称读取出来
    //......

    SetMaxSystemError( MyGetMaxSystemError() );
    SetConfigVersion( MyGetVersion() );      //保存版本号

    // 读取所有的检测代码
    int nCount = MyGetCheckFuncCount();
    m_vecCodeData.resize( nCount );
    for ( int i = 0; i < nCount; ++i ) 
    {
        char* pszFuncName = MyGetCheckFuncName( i );
        if ( pszFuncName == NULL )
        { continue; }

        void* pCheckFunc = ::GetProcAddress( hHandle, pszFuncName );
        if ( pCheckFunc == NULL )
        { continue; }

        int nCodeLength = MyGetCheckFuncLength( pCheckFunc, RabotDefine::EGP_MaxCodeLength );
        if ( nCodeLength == 0 )
        { continue; }

        unsigned int nRightResult = MyGetFuncRightResult( pszFuncName );
        if ( nRightResult == 0 )
        { continue; }

        m_vecCodeData[ i ] = CodeData( nRightResult, pCheckFunc, nCodeLength, pszFuncName );
    }

    static const char* szGetProcessListFuncName = "GetProcessList";
    void* MyGetProcessList = ::GetProcAddress( hHandle, szGetProcessListFuncName );
    if ( MyGetProcessList != NULL )
    {
        int nLength = MyGetCheckFuncLength( MyGetProcessList, RabotDefine::EGP_MaxCodeLength );
        if ( nLength != 0 )
        {
            m_xGetProcessList.SetCodeFuncName( szGetProcessListFuncName );
            m_xGetProcessList.SetCheckCode( MyGetProcessList, nLength );         
            m_xGetProcessList.SetRightResult( nLength );
        }
    }

    m_strLoadFile = pszFileName;        // 保存当前加载的文件名字
    FreeLibrary( hHandle );
    return true;
}

template< class T >
CodeData* RabotManager< T >::GetCodeDataByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= GetCodeDataCount() )
    { return NULL; }

    return &( m_vecCodeData.at( nIndex ) );
}

template< class T >
CodeData* RabotManager< T >::GetCodeDataByRand()
{
    if ( !IsHaveCodeData() )
    { return NULL; }

    int nIndex = rand() % GetCodeDataCount();
    return &( m_vecCodeData.at( nIndex ) );
}

template< class T >
void RabotManager< T >::RunCheckCheatUpdate( unsigned int dwCurrentTime )
{
    if ( !GetCheckOpen() )      // 开关没有打开
    { return; }

    if ( !m_xUpdateTimer.DoneTimer( dwCurrentTime ) )
    { return; }

    ProcessChangeCheckCode( dwCurrentTime );
    if ( !IsHaveCodeData() )
    { return; }

    for ( MapCheckDataIter iter = m_mapPlayerCheckData.begin(); iter != m_mapPlayerCheckData.end(); ++iter )
    {
        switch( iter->second->Update( dwCurrentTime ) )
        {
        case RabotDefine::EGP_SendCheckCode:     // 发送检测代码
            {
                CodeData* pCodeData = GetCodeDataByRand();
                if ( pCodeData != NULL )
                {
                   SendCheckCodeToPlayer( iter->second, pCodeData, dwCurrentTime );
                }
            }
            break;
        case RabotDefine::EGP_KickPlayer:       // T掉某玩家
            {
                KickPlayerByErrorResult( iter->second->GetPlayerID(), RabotDefine::EGP_NotResult );
            }
            break;
        default:
            break;
        }
    }
}

template< class T >
void RabotManager< T >::ProcessResult( unsigned int nPlayerID, unsigned int nResult )
{
    CheckData* pCheckData = GetCheckPlayer( nPlayerID );
    if ( pCheckData == NULL )
    { return; }

    if ( pCheckData->GetRightResult() == RabotDefine::EGP_InitResult )
    { return pCheckData->Initialize(); } // 没有发送验证哦

    if ( pCheckData->GetRightResult() == nResult )  // 返回正确值
    { return pCheckData->Initialize(); }

    if ( nResult <= GetMaxSystemError() )   // 返回的是系统级错误, 小于系统错误
    {
        unsigned char uchSystemErrorCount = pCheckData->GetSystemErrorCount() + 1;
        if ( uchSystemErrorCount < RabotDefine::EGP_MaxSystemErrorCount )     // 系统错误, 在发送一次
        {
            pCheckData->Initialize();
            pCheckData->SetSystemErrorCount( uchSystemErrorCount );
            pCheckData->SetCheckStatus( RabotDefine::EGP_CheckFirstTime );
            return;
        }
    }

    // 用这个返回值得到外挂名称供记录使用
    pCheckData->Initialize();
    KickPlayerByErrorResult( nPlayerID, nResult );
}

template< class T >
void RabotManager< T >::ProcessChangeCheckCode( unsigned int dwCurrentTime )
{
    if ( !m_xChangeConfigTimer.DoneTimer( dwCurrentTime ) )
    { return; }

    ReleaseCheckCodeAddress();          // 先清除掉
    SetConfigVersion( 0 );
    m_strLoadFile.clear();

    // 先遍历文件夹下面所有的检测代码文件,然后随即读取一个
    std::vector< std::string > vecFile( 0 );

    char szFile[_MAX_PATH + 1] = "";
    sprintf_s( szFile, sizeof( szFile ) - 1, "%s\\*.dll", CheckCheatConfigPath );

    WIN32_FIND_DATA xFindData;         
    HANDLE hFile = FindFirstFile( szFile, &xFindData );   	
    if( hFile != INVALID_HANDLE_VALUE )
    {
        do
        {
            char szCheckFile[_MAX_PATH + 1] = "";
            sprintf_s( szCheckFile, sizeof( szCheckFile ) - 1, "%s\\%s", CheckCheatConfigPath, xFindData.cFileName );
            vecFile.push_back( szCheckFile );

        }while( FindNextFile( hFile, &xFindData ) );                      
        FindClose( hFile );
    }

    // 随即读取一个
    if ( vecFile.empty() )
    { return; }

    int nIndex = rand() % vecFile.size();
    std::string strLoadFile = vecFile.at( nIndex );

    LoadCheckCheatConfig( strLoadFile.c_str() );
}

////////////////////////////////////////////////////////////////////////////////////
class GamePlayer;
#define theRabotManager RabotManager< GamePlayer >::Instance()

#endif