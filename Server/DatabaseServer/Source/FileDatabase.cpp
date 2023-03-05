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

    // ��ʼ��Id
    _idManager.SetInvalidID( ErrorUnsignedLongID );
    if ( _idManager.AddIDResource( 0, CD_CHARSAVE_MAXSIZE - 1) == -1)
    { return ER_Failed; }
        
    // ��ʼ��FileMapping
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

    // ����δ�洢������
    bool bResult = theFileMappingCharSaveManager.LoadUnSaveCharacterDatas();
    if ( !bResult )
    { return ER_Failed; }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );
    // ����д��汾
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // �ж��Ƿ������ֵ��Ϣ
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }

    // ��������
    FlushRelease();

    return ER_Success;
}

uint32 FileMappingCharSaveManager::UnInit()
{
    CSALocker lock( _lock ); // ������Դ
    // �¼����ݿ� ��Ҫ���¼���
    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );    
    if ( pFileHeader == NULL )
    { return ER_Failed; }

    uint32 unitCount = pFileHeader->unitCount;

    RemoveMapping();
    Close();

    if ( unitCount == 0 )
    { // �޿��Ա���������ɾ������
        // ɾ���ļ�
        struct _stat info;
        int result = _stat( _strPath.c_str(), &info );    
        int count = 0;
        while ( result != -1 )
        {
            remove(_tANSICHAR(_strPath));
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "��δ������������ ����ɾ��FileCache[%d]",count );
            Sleep( 20 );
            result = _stat( _strPath.c_str(), &info );
            ++count;
        }

        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "��δ������������ ɾ��FileCache" );
    }
    return ER_Success;
}

uint32 FileMappingCharSaveManager::SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage )
{
    if ( pSqlMessage == NULL )
    { return ER_Failed;}

    CSALocker lock( _lock ); // ������Դ

    uint32 index = ErrorUnsignedLongID;
    bool   bNew  = false;

    ItrCharId2IndexContainer it = _charId2Indexs.find( pSqlMessage->msg.dwCharacterID );
    if ( it != _charId2Indexs.end())
    { // ����
        index = it->second;
    }
    else
    { // ������
        index = _idManager.GetUniqueID();
        bNew = true;
    }

    // �Ƿ�����Ч���±�
    if ( index == ErrorUnsignedLongID )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "account %u:%u:%s SaveDataToFile fail %u== ErrorUnsignedLongID", pSqlMessage->msg.accountId, pSqlMessage->msg.dwCharacterID, pSqlMessage->msg.dbInfo.baseinfo.aptotic.szCharacterName, index );
        return ER_Failed; 
    }

    // д����ļ�
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
    { // �¼����� ��Ҫ���¼���
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

    // ���Ҵ˽�ɫ���ڴ��ļ��е�Index
    ItrCharId2IndexContainer it = _charId2Indexs.find( charId );
    if ( it == _charId2Indexs.end())
    {
        assert( false );
        return ER_Failed;
    }

    // ��סIndex
    index = it->second;
    
    // �õ����ļ��е�����
    FileMappingCharSaveManager::SUnit* pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, index, __FUNCTION__, __LINE__ );
    if ( pUnit == NULL )
    { return ER_Failed; }

    if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_NotUse )
    {
        assert( false );
        return ER_Failed;
    }

    // �ɵĶ�Ӧ һ����ɫ���˼��� �ڶ��δ������Ϣ �������ǵ�һ�������Ϣ�Ļ���
    if ( pUnit->lifeId != msgtime )
    { return ER_Success; }

    // �ͷŴ��ļ�������
    pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

    // ˢ��
    FlushRelease();

    // ɾ����Ӧ��ϵ
    _charId2Indexs.erase( charId );

    // �黹Index
    _idManager.ReleaseUniqueID( index );

    // ɾ������ ��Ҫ���¼���
    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__);    
    if ( pFileHeader == NULL )
    { return ER_Failed; }

    if ( pFileHeader->unitCount == 0 )
    { return ER_Failed; }

    --pFileHeader->unitCount;

    // ˢ��
    FlushRelease();

    return ER_Success;
}

bool FileMappingCharSaveManager::LoadUnSaveCharacterDatas()
{
    if ( !_bHaveFileData )
    { return true; }

    CSALocker lock( _lock );

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );
    
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "��ʼ����δ������������version[%u:%u:%u:%u] count[%u:%u]", pFileHeader->version[0], pFileHeader->version[1], 
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
            // дData
            pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
            if ( pUnit == NULL )
            {
                assert(false);
                continue;
            }

            // ��ֵ
            pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

            // ˢ���
            FlushRelease();
        }

        return true;
    }

    // ��ǰ��������
    pFileHeader->unitCount = 0;

    // ��������
    FlushRelease();

    uint32 count = unitCount;
    for ( uint16 i=0; i<unintMaxCount; ++i )
    {
        // ��������
        FileMappingCharSaveManager::SUnit* pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
        if ( pUnit == NULL )
        {
            assert(false);
            continue;
        }

        // ����Ƿ��д�
        if ( pUnit->state == FileMappingCharSaveManager::SUnit::EUnitState_NotUse)
        {
            assert(false);
            FlushRelease();
            continue; 
        }

        // ����Ƿ�����
        Crypto::CCRC32 crc32;
        if (crc32.GetMemCRC32((const unsigned char*)&pUnit->data.dbMsgSaveChar, sizeof(DBMsgSaveCharacter)) != pUnit->data.crcCode )
        {   
            LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_ERROR,"account %u:%s:%d CRCУ��ֵ��ͬ���ļ������Ѿ����޸Ļ�����", pUnit->data.dbMsgSaveChar.accountId, pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, pUnit->data.dbMsgSaveChar.dwCharacterID );
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR,"account %u:%s:%d CRCУ��ֵ��ͬ���ļ������Ѿ����޸Ļ�����", pUnit->data.dbMsgSaveChar.accountId, pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, pUnit->data.dbMsgSaveChar.dwCharacterID );
            FlushRelease();
            continue;
        }

        // �ָ���Ϣ
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

        // ѭ������
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

    // �õ��ļ���С
    struct _stat info;
    int result = _stat( _strPath.c_str(), &info );    
    if ( result != -1 )
    { // ����ļ����ڱ���ԭ����С
        size = info.st_size;
        _bHaveFileData = true;
    }

    _hFile = ::CreateFile( _strPath.c_str(), access, share, &sa, create, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( _hFile == INVALID_HANDLE_VALUE)
    { return ER_CreateFileFail;}
    
    // ��ʼfilemapping
    _hFileMap = ::CreateFileMapping( _hFile, NULL, PAGE_READWRITE, 0, size, FILEDATABASE_DATA_FILENAME );
    if ( _hFileMap == NULL )
    { return ER_CreateFileMappingFail; }

    SYSTEM_INFO psi;
    GetSystemInfo(&psi);
    _allocationGranularity = psi.dwAllocationGranularity;
    
    if ( _bHaveFileData )
    {// ���汾
        FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );
        if ( !theApplicationConfig.IsCompatibleVersion( pFileHeader->version[0], pFileHeader->version[1], pFileHeader->version[2], pFileHeader->version[3]) )
        { 
            FlushRelease();
            return ER_Failed; 
        }

        FlushRelease();
    }
    else
    { // ������
        FileMappingCharSaveManager::SUnit* pUnit = NULL;       
        for ( uint16 i=0; i<FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; ++i )
        {
            // дData
            pUnit = (FileMappingCharSaveManager::SUnit*)GetMappedMemory( FileMappingCharSaveManager::EDataType_FileBody, i, __FUNCTION__, __LINE__ );
            if ( pUnit == NULL )
            {
                assert(false);
                continue;
            }

            // ��ֵ
            pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_NotUse;

            // ˢ���
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
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_pFileMap û��FlushRelease");
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
        { // ָ���Ļ�ַ���ļ�ƫ����û���ʵ����롣 1132
            // �õ���ʼƫ��
            uint32 dataOffset = sizeof( FileMappingCharSaveManager::SFileHeader ) + sizeof( FileMappingCharSaveManager::SUnit ) * index;

            // �õ����ȸ���
            uint32 allocationGranularityNum    = dataOffset / _allocationGranularity;

            // �õ���������
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
{// ��
    FileMappingCharSaveManager test;
    uint32 result = test.OpenMapping();
    if (  result != ER_Success )
    { 
        assert( false );
    }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader, 0, __FUNCTION__, __LINE__ );    
    // ����д��汾
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // �ж��Ƿ������ֵ��Ϣ
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }

    std::cout << "version:"<< pFileHeader->version[0] << ":" << pFileHeader->version[1] << ":" << pFileHeader->version[2] << ":" << pFileHeader->version[3] << "--" << " MaxCount:"<< pFileHeader->unitMaxCount << " Count:" << pFileHeader->unitCount <<std::endl;

    uint32 count = pFileHeader->unitCount;
    uint32 countMax = pFileHeader->unitMaxCount;
    if ( bReset )
    {
        pFileHeader->unitCount = 0;
    }
    // ��������
    test.FlushRelease();

    uint32 time = HQ_TimeGetTime();
    FileMappingCharSaveManager::SUnit* pUnit = NULL;
    
    for ( uint16 i=0; i<countMax; ++i )
    {
        // дData
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
    // �ڴ�ӳ����� 
    // д
    FileMappingCharSaveManager test;
    uint32 result = test.OpenMapping();
    if (  result != ER_Success )
    { 
        assert( false );
    }

    FileMappingCharSaveManager::SFileHeader* pFileHeader = (FileMappingCharSaveManager::SFileHeader*)test.GetMappedMemory( FileMappingCharSaveManager::EDataType_FileHeader,0, __FUNCTION__, __LINE__ );

    // ����д��汾
    pFileHeader->version[0] = theApplicationConfig.GetMajorVersion();
    pFileHeader->version[1] = theApplicationConfig.GetMinorVersion();
    pFileHeader->version[2] = theApplicationConfig.GetBuildVersion();
    pFileHeader->version[3] = theApplicationConfig.GetRevisionVersion();

    // �ж��Ƿ������ֵ��Ϣ
    if ( pFileHeader->unitMaxCount == 0 )
    { pFileHeader->unitMaxCount = FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; }
    pFileHeader->unitCount = 0;

    test.FlushRelease();
    uint32 time = HQ_TimeGetTime();
    char szName[64] = {0};

    FileMappingCharSaveManager::SUnit* pUnit = NULL;       
    for ( uint16 i=0; i<FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE; ++i )
    {
        // дData
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

        // ��ֵ
        pUnit->state = FileMappingCharSaveManager::SUnit::EUnitState_Use;
        sprintf_s( pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName, sizeof( pUnit->data.dbMsgSaveChar.dbInfo.baseinfo.aptotic.szCharacterName ), "Test[%d]", i);
        pUnit->lifeId = i;
            
        // ˢ���
        test.FlushRelease();

        // д��ͷ��Ϣ
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

        // �ȴ����ٴ򿪣�����ʹ��ios::appѡ�����Ϊ���뷽ʽ�����Ǹ��Ƿ�ʽд�ļ�
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
    info.crcCode = 0; // �ڶ��������ݽ���CRCУ��ʱ��������ֵ����Ϊ0  
    memcpy( &info.dbMsgSaveChar, &pSqlMessage->msg, sizeof(info.dbMsgSaveChar) );
    info.crcCode = crc32.GetMemCRC32((const unsigned char*)&info, sizeof(SFileCharSaveData));

    {
        CSALocker lock(_lockTime);
        ItrCharacterDataTimeContainer it = _charDataTimes.find( pSqlMessage->msg.dwCharacterID );
        if ( it != _charDataTimes.end())
        { // ����
            it->second = pSqlMessage->time;
        }
        else
        { // ������
            _charDataTimes.insert( CharacterDataTimeContainer::value_type( pSqlMessage->msg.dwCharacterID, pSqlMessage->time ));
        }

        std::fstream file;
        _tstring strPath;
        strPath.Format(_T("%s/%ld.data"), _strFileDBPath.c_str(), pSqlMessage->msg.dwCharacterID );

        // �ȴ����ٴ򿪣�����ʹ��ios::appѡ�����Ϊ���뷽ʽ�����Ǹ��Ƿ�ʽд�ļ�
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
    { // ����
        if ( it->second != msgtime)
        { return;}
    }

    //���ļ�ɾ��
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

        // ȡ��ID
        _tstring strID = strFullPath.substr(pos+1, strFullPath.length()-pos-6);
        uint32 dwID = ::atol(_tANSICHAR(strID));

        ItrCharacterDataContainer itr = needSaveCharcterData.find( dwID );
        if (itr != needSaveCharcterData.end())
        { 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��ȡ %s ��ɫ���� ID %ld �Ѵ���!", strFullPath.c_str(), dwID);
            continue; 
        }

        std::fstream file;
        file.open(_tUNICODECHAR(strFullPath), std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��ȡ %s �ļ�ʧ��", strFullPath.c_str());
            continue;
        }

        file.seekp(0, std::ios::end);
        size_t size = file.tellp();
        if (size != sizeof(SFileCharSaveData))
        {
            file.close();
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "%s��С�뵱ǰ�ṹ��С��һ�£����ܰ汾��ͬ�����ú��ʵİ汾������ԭ����", strFullPath.c_str());
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
        pInfo->crcCode = 0; // �ڶ��������ݽ���CRCУ��ʱ��������ֵ����Ϊ0
        if (crc32.GetMemCRC32((const unsigned char*)pInfo, sizeof(SFileCharSaveData)) != nCrc)
        {   
            ReleaseFileCharacterSaveInfo( pInfo );
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"%sCRCУ��ֵ��ͬ���ļ������Ѿ����޸Ļ����𻵣�", strFullPath.c_str());
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
