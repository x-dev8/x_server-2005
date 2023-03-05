/********************************************************************
	Filename: 	FileDatabase.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASESERVER_FILEDATABASE_H__
#define __DATABASESERVER_FILEDATABASE_H__

#pragma once

#include "SqlMessages.h"
#include "Mutex.h"
#include "NewWithDebug.h"
#include "FileSearch.h"
#include "StaticArray.h"
#include "UniqueIDManager.h"

#pragma pack( push, 1 ) 

struct SFileCharSaveData
{
    SFileCharSaveData() : crcCode(0)
    {}

    uint32             crcCode;       // �ļ�ͷ�������������ݿ��CRCУ��ֵ��֤���ļ���ʱ��д��������
    DBMsgSaveCharacter dbMsgSaveChar; // ����
};

#pragma pack(pop) 

//////////////////////////////////////////////////////////////////////////
class FileMappingCharSaveManager
{
public:
    enum EConstDefine
    {
        CD_VERSONBUFFERSIZE = 32,
        CD_CHARSAVE_MAXSIZE = 12000, // 15000 
    };

    enum EDataType
    {
        EDataType_FileHeader,
        EDataType_FileBody  ,
    };

#pragma pack( push, 1 ) 
    struct SFileHeader
    {
        enum EConstDefine
        {
            EConstDefine_VersionCount = 4,
        };

        uint32 version[ EConstDefine_VersionCount ]; // �汾��
        uint16 unitCount;                            // ��Ԫ��
        uint16 unitMaxCount;                         // ���Ԫ��

        SFileHeader()
        { memset( this, 0, sizeof( SFileHeader ) ); }
    };

    struct SUnit
    {
        uint8             state;  // ״̬
        uint32            lifeId; // ʱ���
        SFileCharSaveData data;   // ����

        enum EUnitState
        {
            EUnitState_NotUse, // δ��ʹ��
            EUnitState_Use   , // ʹ����
        };

        SUnit()
        { Reset(); }

        void Reset()
        {
            state = EUnitState_NotUse;
            lifeId = 0;
            memset( &data, 0, sizeof(data) );
        }
    };

    struct SFileBody
    {
        SUnit units[CD_CHARSAVE_MAXSIZE];
    };

#pragma pack(pop)

public:
    FileMappingCharSaveManager();
    ~FileMappingCharSaveManager();
    
    uint32 Init();
    uint32 UnInit();
    uint32 SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage ); // �ѽ�ɫ����д����ļ�
    uint32 RemoveDataFile( uint32 charId, uint32 msgtime );                   // �ͷŴ��ļ��е�����
    bool   LoadUnSaveCharacterDatas();                                        // ����һ��δ������ϵ����н�ɫ�б���ļ�������    

    static void TestRead( bool bReset );
    static void TestWrite();
    static void TestNormalWrite();
	//tool
	int	   GetPlayerNumInFileMapping(){return _charId2Indexs.size();}

protected:
    bool   IsClosed(){ return _hFile == INVALID_HANDLE_VALUE;}
    bool   Close();
    uint32 CreateMapping();                               // �������ļ�
    uint32 OpenMapping();                                 // ���� �� ��
    uint8* GetMappedMemory( uint8 type, uint32 index, const char* szFunc, const uint32 szLine ); // �õ�ӳ��ָ��
    void   FlushRelease();                                       // ˢ���ļ�
    void   RemoveMapping();                               // �ͷ�mapping

protected:
    typedef std::map<uint32,uint32>         CharId2IndexContainer;
    typedef CharId2IndexContainer::iterator ItrCharId2IndexContainer;

    uint32                _allocationGranularity; // ��������
    HANDLE                _hFile                ; // �ļ����
    HANDLE                _hFileMap             ; // �ļ�Mapping���
    LPVOID                _pFileMap             ; // �ļ�ָ���ַ
    _tstring              _strPath              ; // ���Ŀ¼
    UniqueIDManager       _idManager            ; // Id������
    CharId2IndexContainer _charId2Indexs        ; // ��ɫid��ӦIndex
    CSemiAutoIntLock      _lock                 ; // lock������
    bool                  _bHaveFileData        ; // �Ƿ����ļ����ݴ���
    bool                  _bHaveInit            ; // �Ƿ��Ѿ���ʼ����
};

FileMappingCharSaveManager& GetFileMappingCharSaveManager();
#define theFileMappingCharSaveManager GetFileMappingCharSaveManager()

//////////////////////////////////////////////////////////////////////////
class FileDatabase
{
public:
    FileDatabase();
    virtual ~FileDatabase();

    static SFileCharSaveData* AllocFileCharacterSaveInfo()                 { return MES_NEW(SFileCharSaveData);}
    static void ReleaseFileCharacterSaveInfo( SFileCharSaveData* pointer ) { MES_DELETE_P( SFileCharSaveData, pointer);}

    // ��Ҫ��ΪShareMemory
    uint32 SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage ); // �ѽ�ɫ����д����
    void   RemoveDataFile( uint32 charId, uint32 msgtime );
    bool   SetRootPath(const char* szPath);
    bool   LoadUnSaveCharacterDatas();      // ����һ��δ������ϵ����н�ɫ�б���ļ�������

protected:
    FileDatabase(const FileDatabase&);
    const FileDatabase& operator = (const FileDatabase&);

protected:
    typedef std::map<uint32, SFileCharSaveData*> CharacterDataContainer;
    typedef CharacterDataContainer::iterator     ItrCharacterDataContainer;

    typedef std::map<uint32, uint32>             CharacterDataTimeContainer;
    typedef CharacterDataTimeContainer::iterator ItrCharacterDataTimeContainer;
    CharacterDataTimeContainer _charDataTimes;  // ʱ��ꡣ��֤ɾ�����Ƕ�Ӧ��data
    CSemiAutoIntLock           _lockTime;       // ʱ���������
    std::string                _strFileDBPath;  // �ļ����ݿ�洢·��
};

FileDatabase& GetFileDatabase();

#endif //__DATABASESERVER_FILEDB_H__
