#include "FileDatabase.h"
#include "CRC32.h"
#include "ResourcePath.h"
#include "DatabaseServerApp.h"
#include <sys\stat.h>
#include "application_config.h"
//#include "NetApi.h"

//////////////////////////////////////////////////////////////////////////
FileMappingCharSaveManager::FileMappingCharSaveManager()
{
    _hFile    = INVALID_HANDLE_VALUE;
    _hFileMap = NULL;
    _pFileMap = NULL;
    _bHaveFileData = false;
    _bHaveInit     = false;
}

FileMappingCharSaveManager::~FileMappingCharSaveManager()
{ 
}

bool FileMappingCharSaveManager::Close()
{
    if (IsClosed())
    { return true; }

    bool ok = ::CloseHandle( _hFile ) == TRUE;
    _hFile = INVALID_HANDLE_VALUE;
    return ok;
}

uint32 FileMappingCharSaveManager::CreateMapping()
{
    if (!IsClosed())
    { Close(); }

    uint32 access = GENERIC_READ | GENERIC_WRITE;
    uint32 share  = FILE_SHARE_READ | FILE_SHARE_WRITE;
    uint32 create = OPEN_ALWAYS;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    
    size_t size = 480 * 1024*1024;//sizeof(SFileHeader)+sizeof(SFileBody); //  
    for ( int i=0; i<60; ++i)
    {
        _strPath.Format(_T("%s/%d%s"), FILEDATABASE_DIRECTORY,i, FILEDATABASE_DATA_FILENAME );

        _hFile = ::CreateFile( _strPath.c_str(), access, share, &sa, create, FILE_ATTRIBUTE_NORMAL, NULL);
        if ( _hFile == INVALID_HANDLE_VALUE)
        { return ER_CreateFileFail;}

        char szBuffer[255] = {0};
        sprintf_s( szBuffer, "%d%s",i,FILEDATABASE_DATA_FILENAME);
        _hFileMap = ::CreateFileMapping( _hFile, NULL, PAGE_READWRITE, 0, size, szBuffer );
        if ( _hFileMap == NULL )
        { return ER_CreateFileMappingFail; }

        _pFileMap = ::MapViewOfFile( _hFileMap, FILE_MAP_WRITE, 0, 0, 0);
        if ( _pFileMap != NULL )
        { return ER_MapViewOfFileFail;}
    }

    return ER_Success;
}

uint32 FileMappingCharSaveManager::Init()
{
    if ( _bHaveInit )
    { return ER_Success; }

    //system( "pause ");
    _bHaveInit = true;

    // 初始化Id
    _idManager.SetInvalidID( ErrorUnsignedLongID );
    if ( _idManager.AddIDResource( 0, CD_CHARSAVE_MAXSIZE - 1) == -1)
    { return ER_Failed; }
        
    // 初始化FileMapping
    if ( _mkdir( FILEDATABASE_DIRECTORY ) != 0 )
    {
        int error = 0;
        _get_errno( &error );

        if ( error != EEXIST )
        {
            char errorString[ MAX_PATH ] ={};
            switch ( error )
            {
            case ENOENT:
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "FilePath Error: directory path error %s", FILEDATABASE_DIRECTORY );
                }
                break;
            default:
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "FilePath Error: unknown error %s", FILEDATABASE_DIRECTORY );
                }
                break;
            }
            return ER_Failed;
        }
    }

    uint32 result = OpenMapping();
    if ( result != ER_Success )
    { return result; }

    // 载入未存储的数据
    bool bResult = theFileMappingCharSaveManager.LoadUnSaveCharacterDatas();
    if ( !bResult )
    { return ER_Failed; }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );
    // 重新写入版本
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // 判断是否有最大值信息
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }

    // 输入数据
    FlushRelease();

    return ER_Success;
}

uint32 FileMappingCharSaveManager::UnInit()
{
    CSALocker lock( _lock ); // 锁定资源
    // 新加数据库 需要更新计数
    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );    
    if ( pFileHeader == NULL )
    { return ER_Failed; }

    uint32 unitCount = pFileHeader->unitCount;

    RemoveMapping();
    Close();

    if ( unitCount == 0 )
    { // 无可以保留的数据删除数据
        // 删除文件
        struct _stat info;
        int result = _stat( _strPath.c_str(), &info );    
        int count = 0;
        while ( result != -1 )
        {
            remove(_tANSICHAR(_strPath));
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "无未入库的人物数据 尝试删除FileCache[%d]",count );
            Sleep( 20 );
            result = _stat( _strPath.c_str(), &info );
            ++count;
        }

        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "无未入库的人物数据 删除FileCache" );
    }
    return ER_Success;
}

uint32 FileMappingCharSaveManager::SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage )
{
    if ( pSqlMessage == NULL )
    { return ER_Failed;}

    CSALocker lock( _lock ); // 锁定资源

    uint32 index = ErrorUnsignedLongID;
    bool   bNew  = false;

    ItrCharId2IndexContainer it = _charId2Indexs.find( pSqlMessage->msg.dwCharacterID );
    if ( it != _charId2Indexs.end())
    { // 存在
        index = it->second;
    }
    else
    { // 不存在
        index = _idManager.GetUniqueID();
        bNew = true;
    }

    // 是否有有效的下标
    if ( index == ErrorUnsignedLongID )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "account %u:%u:%s SaveDataToFile fail %u== ErrorUnsignedLongID", pSqlMessage->msg.accountId, pSqlMessage->msg.dwCharacterID, pSqlMessage->msg.dbInfo.baseinfo.aptotic.szCharacterName, index );
        return ER_Failed; 
    }

    // 写入大文件
    FileMappingCharSaveManager::SUnit* pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, index, __FUNCTION__, __LINE__ );
    if ( pUnit == NULL )
    { return ER_MapViewOfFileFail; }

    if ( bNew && pUnit->state != FileMappingCharSaveManager::SUnit::EUnitState_NotUse )
    {
        assert( false );
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "account %u:%u:%s SaveDataToFile fail pUnit->state %u", pSqlMessage->msg.accountId, pSqlMessage->msg.dwCharacterID, pSqlMessage->msg.dbInfo.baseinfo.aptotic.szCharacterName , pUnit->state);
        return ER_Failed;
    }

    // Todo try
    pUnit->state  = FileMappingCharSaveManager::SUnit::EUnitState_Use;
    pUnit->lifeId = pSqlMessage->time;
    Crypto::CCRC32 crc32;
    pUnit->data.crcCode = crc32.GetMemCRC32((const unsigned char*)&pSqlMessage->msg, sizeof(DBMsgSaveCharacter));
    memcpy_s( &pUnit->data.dbMsgSaveChar, sizeof(pUnit->data.dbMsgSaveChar), &pSqlMessage->msg, sizeof(pUnit->data.dbMsgSaveChar) );

    FlushRelease();

    if ( bNew )
    { // 新加数据 需要更新计数
        bool bResult = _charId2Indexs.insert( CharId2IndexContainer::value_type( pSqlMessage->msg.dwCharacterID, index )).second;
        if ( !bResult )
        { return ER_Failed; }

        FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0 , __FUNCTION__, __LINE__ );    
        if ( pFileHeader == NULL )
        { return ER_Failed; }

        if ( pFileHeader->unitCount == pFileHeader->unitMaxCount )
        {
            FlushRelease();
            return ER_Failed; 
        }

        ++pFileHeader->unitCount;

        FlushRelease();
    }
    
    return ER_Success;
}

uint32 FileMappingCharSaveManager::RemoveDataFile( uint32 charId, uint32 msgtime )
{
    uint32 index = ErrorUnsignedLongID;
    CSALocker lock( _lock );

    // 查找此角色的在大文件中的Index
    ItrCharId2IndexContainer it = _charId2Indexs.find( charId );
    if ( it == _charId2Indexs.end())
    {
        assert( false );
        return ER_Failed;
    }

    // 存住Index
    index = it->second;
    
    // 拿到大文件中的数据
    FileMappingCharSaveManager::SUnit* pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, index, __FUNCTION__, __LINE__ );
    if ( pUnit == NULL )
    { return ER_Failed; }

    if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_NotUse )
    {
        assert( false );
        return ER_Failed;
    }

    // 旧的对应 一个角色存了几次 第二次存入的信息 回来的是第一个存好信息的回馈
    if ( pUnit->lifeId != msgtime )
    { return ER_Success; }

    // 释放大文件中数据
    pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

    // 刷入
    FlushRelease();

    // 删除对应关系
    _charId2Indexs.erase( charId );

    // 归还Index
    _idManager.ReleaseUniqueID( index );

    // 删除数据 需要更新计数
    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__);    
    if ( pFileHeader == NULL )
    { return ER_Failed; }

    if ( pFileHeader->unitCount == 0 )
    { return ER_Failed; }

    --pFileHeader->unitCount;

    // 刷入
    FlushRelease();

    return ER_Success;
}

bool FileMappingCharSaveManager::LoadUnSaveCharacterDatas()
{
    if ( !_bHaveFileData )
    { return true; }

    CSALocker lock( _lock );

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );
    
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "开始载入未入库的人物数据version[%u:%u:%u:%u] count[%u:%u]", pFileHeader->version[0], pFileHeader->version[1], 
                                                                                                               pFileHeader->version[2], pFileHeader->version[3],
                                                                                                               pFileHeader->unitCount,  pFileHeader->unitMaxCount );

    uint32 unitCount     = pFileHeader->unitCount;
    uint32 unintMaxCount = pFileHeader->unitMaxCount;
    if ( unitCount == 0)
    {
        FlushRelease();

        FileMappingCharSaveManager::SUnit* pUnit = NULL;       
        for ( uint16 i=0; i<FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; ++i )
        {
            // 写Data
            pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
            if ( pUnit == NULL )
            {
                assert(false);
                continue;
            }

            // 赋值
            pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

            // 刷入包
            FlushRelease();
        }

        return true;
    }

    // 提前更新数据
    pFileHeader->unitCount = 0;

    // 输入数据
    FlushRelease();

    uint32 count = unitCount;
    for ( uint16 i=0; i<unintMaxCount; ++i )
    {
        // 查找数据
        FileMappingCharSaveManager::SUnit* pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
        if ( pUnit == NULL )
        {
            assert(false);
            continue;
        }

        // 检查是否有错
        if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_NotUse)
        {
            assert(false);
            FlushRelease();
            continue; 
        }

        // 检查是否有损坏
        Crypto::CCRC32 crc32;
        if (crc32.GetMemCRC32((const unsigned char*)&pUnit->data.dbMsgSaveChar, sizeof(DBMsgSaveCharacter)) != pUnit->data.crcCode )
        {   
            LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_ERROR,"account %u:%s:%d CRC校验值不同，文件可能已经被修改或是损坏", pUnit->data.dbMsgSaveChar.accountId, pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, pUnit->data.dbMsgSaveChar.dwCharacterID );
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR,"account %u:%s:%d CRC校验值不同，文件可能已经被修改或是损坏", pUnit->data.dbMsgSaveChar.accountId, pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, pUnit->data.dbMsgSaveChar.dwCharacterID );
            FlushRelease();
            continue;
        }

        // 恢复消息
        DBMsgSaveCharacter msg;
        memcpy_s( &msg, sizeof(DBMsgSaveCharacter), &pUnit->data.dbMsgSaveChar, sizeof( DBMsgSaveCharacter ) );
        msg.shServerId = DiskServerId;

        if ( theMysqlCommunication.PushReqMessage( &msg, -1 ) != ER_Success )
        {
            LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_WARNING, "account %u:%s:%u LoadUnsaveDatasFromFiles Fail MessageId[%d] Size[%d]",msg.accountId, msg.dbInfo.baseinfo.aptotic.szCharacterName, msg.dwCharacterID, msg.GetType(), msg.GetLength());
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "account %u:%s:%u LoadUnsaveDatasFromFiles Fail MessageId[%d] Size[%d]",msg.accountId, msg.dbInfo.baseinfo.aptotic.szCharacterName, msg.dwCharacterID, msg.GetType(), msg.GetLength());
        }

        pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;
        FlushRelease();

        // 循环计数
        --count;
        if ( count == 0)
        { break; }
    }
    
    return true;
}

uint32 FileMappingCharSaveManager::OpenMapping()
{
    if (!IsClosed())
    { Close(); }

    uint32 access = GENERIC_READ | GENERIC_WRITE;
    uint32 share  = FILE_SHARE_READ | FILE_SHARE_WRITE;
    uint32 create = OPEN_ALWAYS;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    _strPath.Format(_T("%s/%s"), FILEDATABASE_DIRECTORY, FILEDATABASE_DATA_FILENAME );

    size_t size = sizeof(SFileHeader)+sizeof(SFileBody);

    // 得到文件大小
    struct _stat info;
    int result = _stat( _strPath.c_str(), &info );    
    if ( result != -1 )
    { // 如果文件存在保持原来大小
        size = info.st_size;
        _bHaveFileData = true;
    }

    _hFile = ::CreateFile( _strPath.c_str(), access, share, &sa, create, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( _hFile == INVALID_HANDLE_VALUE)
    { return ER_CreateFileFail;}
    
    // 开始filemapping
    _hFileMap = ::CreateFileMapping( _hFile, NULL, PAGE_READWRITE, 0, size, FILEDATABASE_DATA_FILENAME );
    if ( _hFileMap == NULL )
    { return ER_CreateFileMappingFail; }

    SYSTEM_INFO psi;
    GetSystemInfo(&psi);
    _allocationGranularity = psi.dwAllocationGranularity;
    
    if ( _bHaveFileData )
    {// 检查版本
        FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );
        if ( !theApplicationConfig.IsCompatibleVersion( pFileHeader->version[0], pFileHeader->version[1], pFileHeader->version[2], pFileHeader->version[3]) )
        { 
            FlushRelease();
            return ER_Failed; 
        }

        FlushRelease();
    }
    else
    { // 清数据
        FileMappingCharSaveManager::SUnit* pUnit = NULL;       
        for ( uint16 i=0; i<FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; ++i )
        {
            // 写Data
            pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
            if ( pUnit == NULL )
            {
                assert(false);
                continue;
            }

            // 赋值
            pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

            // 刷入包
            FlushRelease();
        }
    }

    return ER_Success;
}

uint8* FileMappingCharSaveManager::GetMappedMemory( uint8 type, uint32 index, const char* szFunc, const uint32 szLine )
{
    if ( _pFileMap )
    {
        assert( false );
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_pFileMap 没有FlushRelease");
        FlushRelease();
    }

    size_t byteNumber = 0;
    uint32 offset     = 0;
    switch ( type )
    {
    case EDataType_FileHeader:
        {
            byteNumber = sizeof( FileMappingCharSaveManager::SFileHeader );
            offset     = 0;

            _pFileMap = ::MapViewOfFile( _hFileMap, FILE_MAP_WRITE, 0, offset, byteNumber);   
        }
    	break;
    case EDataType_FileBody:
        { // 指定的基址或文件偏移量没有适当对齐。 1132
            // 得到开始偏移
            uint32 dataOffset = sizeof( FileMappingCharSaveManager::SFileHeader ) + sizeof( FileMappingCharSaveManager::SUnit ) * index;

            // 得到粒度个数
            uint32 allocationGranularityNum    = dataOffset / _allocationGranularity;

            // 得到粒度余数
            uint32 allocationGranularityOffset = dataOffset % _allocationGranularity;

            offset     = _allocationGranularity * allocationGranularityNum;
            byteNumber = sizeof( FileMappingCharSaveManager::SUnit ) + allocationGranularityOffset;

            _pFileMap = ::MapViewOfFile( _hFileMap, FILE_MAP_WRITE, 0, offset, byteNumber); 

            if ( _pFileMap == NULL )
            { return NULL; }

            _pFileMap = (uint8*)_pFileMap + allocationGranularityOffset;
        }
        break;
    default:
        { return NULL; }
    }
#pragma warning( push )
#pragma warning( disable : 4311 )
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_DEBUG, "%s:%u GetMappedMemory(%u)", szFunc, szLine, (DWORD)_pFileMap );
#pragma warning( pop )
    return (uint8*)_pFileMap;
}

void FileMappingCharSaveManager::FlushRelease()
{
    if ( _pFileMap )
    {   
        UnmapViewOfFile( _pFileMap );
        _pFileMap = NULL;
    }
}

void FileMappingCharSaveManager::RemoveMapping()
{
    if ( _pFileMap )
    {
        UnmapViewOfFile( _pFileMap );
        _pFileMap = NULL;
    }

    if ( _hFileMap )
    {
        CloseHandle(_hFileMap);
        _hFileMap = NULL;
    }
}

void FileMappingCharSaveManager::TestRead( bool bReset )
{// 读
    FileMappingCharSaveManager test;
    uint32 result = test.OpenMapping();
    if (  result != ER_Success )
    { 
        assert( false );
    }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );    
    // 重新写入版本
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // 判断是否有最大值信息
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }

    std::cout << "version:"<< pFileHeader->version[0] << ":" << pFileHeader->version[1] << ":" << pFileHeader->version[2] << ":" << pFileHeader->version[3] << "--" << " MaxCount:"<< pFileHeader->unitMaxCount << " Count:" << pFileHeader->unitCount <<std::endl;

    uint32 count = pFileHeader->unitCount;
    uint32 countMax = pFileHeader->unitMaxCount;
    if ( bReset )
    {
        pFileHeader->unitCount = 0;
    }
    // 输入数据
    test.FlushRelease();

    uint32 time = HQ_TimeGetTime();
    FileMappingCharSaveManager::SUnit* pUnit = NULL;
    
    for ( uint16 i=0; i<countMax; ++i )
    {
        // 写Data
        pUnit = (FileMappingCharSaveManager::SUnit*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
        if ( pUnit == NULL )
        {
            assert(false);
            continue;
        }

        if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_NotUse)
        { 
            assert(false);
            continue; 
        }

        if ( bReset )
        {
            pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;
        }

        std::cout << "--[" << pUnit->lifeId << "]--" << "--[" << pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName << "]--" << std::endl;
        
        test.FlushRelease();

        --count;
        if ( count == 0)
        { break; }
    }

    test.RemoveMapping();
    test.Close();
    std::cout << "------------- " << HQ_TimeGetTime() - time << std::endl;
    system("pause");
}

void FileMappingCharSaveManager::TestWrite()
{
    // 内存映射测试 
    // 写
    FileMappingCharSaveManager test;
    uint32 result = test.OpenMapping();
    if (  result != ER_Success )
    { 
        assert( false );
    }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );

    // 重新写入版本
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // 判断是否有最大值信息
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }
    pFileHeader->unitCount = 0;

    test.FlushRelease();
    uint32 time = HQ_TimeGetTime();
    char szName[64] = {0};

    FileMappingCharSaveManager::SUnit* pUnit = NULL;       
    for ( uint16 i=0; i<FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; ++i )
    {
        // 写Data
        pUnit = (FileMappingCharSaveManager::SUnit*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
        if ( pUnit == NULL )
        {
            assert(false);
            continue;
        }

        if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_Use )
        {
            assert(false);
            continue;
        }

        // 赋值
        pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_Use;
        sprintf_s( pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, sizeof( pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName ), "Test[%d]", i);
        pUnit->lifeId = i;
            
        // 刷入包
        test.FlushRelease();

        // 写包头信息
        pFileHeader = (FileMappingCharSaveManager::SFileHeader*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0 , __FUNCTION__, __LINE__ );
        if ( pFileHeader == NULL )
        {
            assert(false);
            continue;
        }
        ++pFileHeader->unitCount;
        test.FlushRelease();
    }

    test.RemoveMapping();
    test.Close();
    std::cout << "------------- " << HQ_TimeGetTime() - time << std::endl;
    system("pause");
}

void FileMappingCharSaveManager::TestNormalWrite()
{
    FileMappingCharSaveManager::SUnit unit;
    uint32 time = HQ_TimeGetTime();
    for ( uint16 i=0; i<10000; ++i )
    {
        std::fstream file;
        _tstring strPath;
        strPath.Format(_T("../FileDatabase/%ld.data"),  i );

        // 先创建再打开，否则使用ios::app选项会作为插入方式而不是覆盖方式写文件
        file.open(_tUNICODECHAR(strPath), std::ios::trunc | std::ios::out | std::ios::binary);
        if (!file.is_open())
        { 
            assert(false);
            continue;
        }
        file.seekp(0, std::ios::beg);
        file.write((const char*)&unit, sizeof(unit));
        file.flush();
        file.close();
    }
    std::cout << "+++++++++++++ " << HQ_TimeGetTime() - time << std::endl;
    system("pause");
}

//////////////////////////////////////////////////////////////////////////
FileDatabase::FileDatabase()
{
}

FileDatabase::~FileDatabase()
{   
}

bool FileDatabase::SetRootPath(const char* path)
{
	if ( _mkdir( path ) != 0 )
	{
		int error = 0;
		_get_errno( &error );

		if ( error != EEXIST )
		{
			char errorString[ MAX_PATH ] ={};
			switch ( error )
			{
			case ENOENT:
				{
					sprintf_s( errorString, sizeof( errorString ) - 1, "FilePath Error: directory path error %s", path );
				}
				break;

			default:
				{
					sprintf_s( errorString, sizeof( errorString ) - 1, "FilePath Error: unknown error %s", path );
				}
				break;
			}

			MessageBox( NULL, errorString, "Database Server", MB_OK | MB_ICONERROR );
			return false;
		}
	}
	_strFileDBPath = path;
	return true;
}

uint32 FileDatabase::SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage )
{   
    if ( pSqlMessage == NULL )
    { return ER_Failed;}

    SFileCharSaveData info;
    Crypto::CCRC32        crc32;
    info.crcCode = 0; // 在对整块数据进行CRC校验时，将它的值先置为0  
    memcpy( &info.dbMsgSaveChar, &pSqlMessage->msg, sizeof(info.dbMsgSaveChar) );
    info.crcCode = crc32.GetMemCRC32((const unsigned char*)&info, sizeof(SFileCharSaveData));

    {
        CSALocker lock(_lockTime);
        ItrCharacterDataTimeContainer it = _charDataTimes.find( pSqlMessage->msg.dwCharacterID );
        if ( it != _charDataTimes.end())
        { // 存在
            it->second = pSqlMessage->time;
        }
        else
        { // 不存在
            _charDataTimes.insert( CharacterDataTimeContainer::value_type( pSqlMessage->msg.dwCharacterID, pSqlMessage->time ));
        }

        std::fstream file;
        _tstring strPath;
        strPath.Format(_T("%s/%ld.data"), _strFileDBPath.c_str(), pSqlMessage->msg.dwCharacterID );

        // 先创建再打开，否则使用ios::app选项会作为插入方式而不是覆盖方式写文件
        file.open(_tUNICODECHAR(strPath), std::ios::trunc | std::ios::out | std::ios::binary);
        if (!file.is_open())
        { return false; }

        file.seekp(0, std::ios::beg);
        file.write((const char*)&info, sizeof(SFileCharSaveData));
        file.flush();
        file.close();
    }

    return ER_Success;
}

void FileDatabase::RemoveDataFile( uint32 charId, uint32 msgtime )
{
    CSALocker lock(_lockTime);
    ItrCharacterDataTimeContainer it = _charDataTimes.find( charId );
    if ( it != _charDataTimes.end())
    { // 存在
        if ( it->second != msgtime)
        { return;}
    }

    //将文件删除
    _tstring strFile;
    strFile.Format(_T("%s/%ld.data"), _strFileDBPath.c_str(), charId);
    remove(_tANSICHAR(strFile));
    _charDataTimes.erase( charId );
}

bool FileDatabase::LoadUnSaveCharacterDatas()
{
    CharacterDataContainer needSaveCharcterData;

    FileIO::CFileSearch search;
    search.Find(_strFileDBPath, "*.data");

    FileIO::CFileSearch::FileList& filelist = search.GetFile();
    while (!filelist.empty())
    {
        _tstring strFullPath = filelist.back();
        strFullPath.Replace(_T("\\"), _T("/"));
        filelist.pop_back();

        size_t pos = strFullPath.ReverseFind(_T('/'));

        // 取得ID
        _tstring strID = strFullPath.substr(pos+1, strFullPath.length()-pos-6);
        uint32 dwID = ::atol(_tANSICHAR(strID));

        ItrCharacterDataContainer itr = needSaveCharcterData.find( dwID );
        if (itr != needSaveCharcterData.end())
        { 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "读取 %s 角色数据 ID %ld 已存在!", strFullPath.c_str(), dwID);
            continue; 
        }

        std::fstream file;
        file.open(_tUNICODECHAR(strFullPath), std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "读取 %s 文件失败", strFullPath.c_str());
            continue;
        }

        file.seekp(0, std::ios::end);
        size_t size = file.tellp();
        if (size != sizeof(SFileCharSaveData))
        {
            file.close();
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s大小与当前结构大小不一致，可能版本不同，请用合适的版本启动还原数据", strFullPath.c_str());
            continue;
        }

        SFileCharSaveData* pInfo = AllocFileCharacterSaveInfo();
        if ( pInfo == NULL )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AllocFileCharacterSaveInfo Fail" );
            continue;
        }

        file.seekg( 0, std::ios::beg );
        file.read((char*)pInfo, sizeof(SFileCharSaveData));
        uint32 nCrc = pInfo->crcCode;
        Crypto::CCRC32 crc32;
        pInfo->crcCode = 0; // 在对整块数据进行CRC校验时，将它的值先置为0
        if (crc32.GetMemCRC32((const unsigned char*)pInfo, sizeof(SFileCharSaveData)) != nCrc)
        {   
            ReleaseFileCharacterSaveInfo( pInfo );
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"%sCRC校验值不同，文件可能已经被修改或是损坏！", strFullPath.c_str());
            continue;
        }

        file.close();
        pInfo->crcCode = nCrc;
    }

    ItrCharacterDataContainer it    = needSaveCharcterData.begin();
    ItrCharacterDataContainer itEnd = needSaveCharcterData.end();
    for ( ; it!=itEnd; ++it )
    {
        SFileCharSaveData* pSaveInfo = it->second;
        if ( pSaveInfo == NULL )
        { continue; }

        DBMsgSaveCharacter msg;
        memcpy_s( &msg, sizeof(msg), &pSaveInfo->dbMsgSaveChar, sizeof( msg ) );
        msg.shServerId = DiskServerId;

        BOOL bResult = TRUE;
        if ( GetDatabaseServerApp()->useSqlType == DatabaseServerApp::ST_MSSql )
        { bResult = GetDatabaseInterface()->PushMessage( &msg, -1 ); }
        else
        { bResult = theMysqlCommunication.PushReqMessage( &msg, -1 ); }

        if ( !bResult )
        { 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "LoadUnsaveDatasFromFiles Fail MessageId[%d] Size[%d]", msg.GetType(), msg.GetLength());
        }
        ReleaseFileCharacterSaveInfo( pSaveInfo );
    }
    return true;
}

FileDatabase& GetFileDatabase()
{
    static FileDatabase instance;
    return instance;
}

FileMappingCharSaveManager& GetFileMappingCharSaveManager()
{
    static FileMappingCharSaveManager instance;
    return instance;
}
