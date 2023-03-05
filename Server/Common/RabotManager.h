#ifndef __GAMEPROTECTMANAGER_H__
#define __GAMEPROTECTMANAGER_H__
/************************************************************************
                    �����ϵͳ
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
        EGP_MaxSystemErrorCount = 2,        // ���ص�ϵͳ����������,�����˴�����Ϊ����,T����( ����Ժ�ȷ��������,���Ŵ��� )
        EGP_ResultTimeOutCount  = 2,        // ��ʱδ��Ӧ����������
        EGP_ResultTimeOut       = 12010,    // ���ͼ�⺯���Ժ�,������ʱ��δ��Ӧ,�ۼƴ������� EGP_ResultTimeOutCount ��Ϊ����
        EGP_CheckSpaceTime      = 300000,   // ������Ϸ��, 4���Ӻ�ʼ���
        EGP_UpdateSpaceTime     = 5000,     // 5��updateһ��
        EGP_FuncNameLength      = 41,       // ִ�к������ĳ���

        EGP_DoNothing           = 0,
        EGP_SendCheckCode       = 1,
        EGP_KickPlayer          = 2,

        EGP_Delete              = 0,
        EGP_Success             = 1,
        EGP_Failed              = 2,

        EGP_InitResult          = 0,
        EGP_MaxCodeLength       = 4096,     // ��������󳤶�
        EGP_ChangeCodeSpaceTime = 60 * 60 * 1000,  // ��Сʱ�л�һ�μ�����

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
    unsigned int m_dwPlayerID;           // ��ҵ�dbid
    unsigned int m_nRightResult;         // �����⺯������ȷֵ
    unsigned char m_uchSystemErrorCount; // ϵͳ�������
    unsigned char m_uchTimeOutCount;     // ��ʱ����
    unsigned char m_uchCheckStatus;
    GameTimerEx m_xOperateTimer;         // ��ʱ��
};

// ��������Ϣ�ṹ
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

    unsigned int GetRightResult() const { return m_nRightResult; }      // �����ȷ��
    const char* GetCheckCode() const { return m_szCheckCode; }          // ��ü������ַ
    unsigned short GetCodeLength() const { return m_nCodeLength; }      // ��ü����볤��
    const char* GetCodeFuncName() const { return m_szCodeFuncName; }    // ��ü����뺯����

private:
    unsigned int m_nRightResult;                              // ��ȷ�Ĵ�
    char m_szCheckCode[ RabotDefine::EGP_MaxCodeLength ];     // ִ�д���
    unsigned short m_nCodeLength;                             // ��������
    char m_szCodeFuncName[ RabotDefine::EGP_FuncNameLength ]; // ��������
};

template< class T >
class RabotManager : public ISingletion< RabotManager< T > >
{
public:
    RabotManager();
    ~RabotManager();

    bool AddCheckPlayer( unsigned int nPlayerID );          // ������
    void RemoveCheckPlayer( unsigned int nPlayerID );       // ɾ�����
    CheckData* GetCheckPlayer( unsigned int nPlayerID );    // ������

    T* GetPlayerByID( unsigned int nPlayerID );             // ������ָ�� ( ��������ڲ�ͬ��Ϸ����Ҫ�ػ� )
    unsigned short SendCheckCodeToPlayer( CheckData* xCheckData, CodeData* pCodeData, unsigned int dwSendTime ); // ���ͼ�����
    unsigned short SendGetProcessListToPlayer( unsigned int nPlayerID, unsigned int dwSendTime );        // ���ͼ�����, ��ÿͻ��˽����б�Ϳͻ��˼��ص�ģ��
    unsigned short KickPlayerByErrorResult( unsigned int nPlayerID, unsigned int dwErrorResult );        // T�����

    bool LoadCheckCheatConfig( const char* pszFileName );       // ������Դ ( ע���ڴ���ͷ� )
    void ReleaseCheckCodeAddress();
    CodeData* GetCodeDataByIndex( int nIndex );                 // ��ü�������Ϣ
    CodeData* GetCodeDataByRand(); 
    bool IsHaveCodeData() { return !m_vecCodeData.empty(); }    // �Ƿ��м�����
    unsigned int GetCodeDataCount() { return static_cast< unsigned int >( m_vecCodeData.size() ); }
    void RunCheckCheatUpdate( unsigned int dwCurrentTime );      // �Զ�����
    void ProcessChangeCheckCode( unsigned int dwCurrentTime );      // ����������
    void ProcessResult( unsigned int nPlayerID, unsigned int nResult );     // ����ش��Ľ��

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
    
    MapCheckData m_mapPlayerCheckData;          // �������Ҽ����Ϣ
    CodeDataVector m_vecCodeData;               // ��������Ϣ����
    int m_nCodeDataIndex;
    CodeData m_xGetProcessList;                 // ��ý����б�Ĵ�����Ϣ
    bool m_bCheckOpen;                          // �Ƿ���������
    unsigned int m_nMaxSystemError;             // ������������ϵͳ��������
    unsigned int m_nConfigVersion;              // �������ļ������õİ汾��
    std::string m_strLoadFile;                  // ��ǰ���ص��ļ�
    GameTimerEx m_xUpdateTimer;                 // ����Timer
    GameTimerEx m_xChangeConfigTimer;           // ������Դ��Timer
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
    pCheckData->SetCheckStatus( RabotDefine::EGP_CheckFirstTime );        // ���õ�һ����֤
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

    // ��Ҫʵ��ProcessSendCheckCheatData����
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
    // ������ڵȴ���֤,�Ͳ�������Ϣ
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
        pCheckData->SetTimeOutCount( RabotDefine::EGP_ResultTimeOutCount - 1 );           // ���ó�ʱ����, û�л���Ϣ ֱ�Ӹɵ�

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

    // ��Ҫʵ��ProcessKickByCheckCheat����,�������ʵ��
    // ����ֱ��Exit, ����ѭ���е�����ʧЧ
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

typedef int ( * __GetCheckFuncCount )();                                  // �õ���⺯������
typedef char* ( * __GetCheckFuncName )( int nIndex );                     // �õ���⺯��������
typedef int ( * __GetCheckFuncLength )( void* pFunc, int nMaxLength );    // �õ���⺯������
typedef unsigned int ( * __GetFuncRightResult )( const char* pszFunc );   // �õ���⺯������ȷ��
typedef int ( * __GetMaxSystemError )();                                  // ���ϵͳ����
typedef int ( * __GetVersion )();                                         // ��ð汾��

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

    //if ( MyGetVersion() == GetConfigVersion() )         // �汾û��Ͳ���ȡ��
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

    // ��Ҫ�����еĴ������Ӧ��������ƶ�ȡ����
    //......

    SetMaxSystemError( MyGetMaxSystemError() );
    SetConfigVersion( MyGetVersion() );      //����汾��

    // ��ȡ���еļ�����
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

    m_strLoadFile = pszFileName;        // ���浱ǰ���ص��ļ�����
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
    if ( !GetCheckOpen() )      // ����û�д�
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
        case RabotDefine::EGP_SendCheckCode:     // ���ͼ�����
            {
                CodeData* pCodeData = GetCodeDataByRand();
                if ( pCodeData != NULL )
                {
                   SendCheckCodeToPlayer( iter->second, pCodeData, dwCurrentTime );
                }
            }
            break;
        case RabotDefine::EGP_KickPlayer:       // T��ĳ���
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
    { return pCheckData->Initialize(); } // û�з�����֤Ŷ

    if ( pCheckData->GetRightResult() == nResult )  // ������ȷֵ
    { return pCheckData->Initialize(); }

    if ( nResult <= GetMaxSystemError() )   // ���ص���ϵͳ������, С��ϵͳ����
    {
        unsigned char uchSystemErrorCount = pCheckData->GetSystemErrorCount() + 1;
        if ( uchSystemErrorCount < RabotDefine::EGP_MaxSystemErrorCount )     // ϵͳ����, �ڷ���һ��
        {
            pCheckData->Initialize();
            pCheckData->SetSystemErrorCount( uchSystemErrorCount );
            pCheckData->SetCheckStatus( RabotDefine::EGP_CheckFirstTime );
            return;
        }
    }

    // ���������ֵ�õ�������ƹ���¼ʹ��
    pCheckData->Initialize();
    KickPlayerByErrorResult( nPlayerID, nResult );
}

template< class T >
void RabotManager< T >::ProcessChangeCheckCode( unsigned int dwCurrentTime )
{
    if ( !m_xChangeConfigTimer.DoneTimer( dwCurrentTime ) )
    { return; }

    ReleaseCheckCodeAddress();          // �������
    SetConfigVersion( 0 );
    m_strLoadFile.clear();

    // �ȱ����ļ����������еļ������ļ�,Ȼ���漴��ȡһ��
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

    // �漴��ȡһ��
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