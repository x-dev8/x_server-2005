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

    uint32             crcCode;       // 文件头部保存整个数据块的CRC校验值保证当文件损坏时不写错误数据
    DBMsgSaveCharacter dbMsgSaveChar; // 数据
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

        uint32 version[ EConstDefine_VersionCount ]; // 版本号
        uint16 unitCount;                            // 单元数
        uint16 unitMaxCount;                         // 最大单元数

        SFileHeader()
        { memset( this, 0, sizeof( SFileHeader ) ); }
    };

    struct SUnit
    {
        uint8             state;  // 状态
        uint32            lifeId; // 时间搓
        SFileCharSaveData data;   // 数据

        enum EUnitState
        {
            EUnitState_NotUse, // 未被使用
            EUnitState_Use   , // 使用中
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
    uint32 SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage ); // 把角色数据写入大文件
    uint32 RemoveDataFile( uint32 charId, uint32 msgtime );                   // 释放大文件中的数据
    bool   LoadUnSaveCharacterDatas();                                        // 将上一次未保存完毕的所有角色列表从文件中载入    

    static void TestRead( bool bReset );
    static void TestWrite();
    static void TestNormalWrite();
	//tool
	int	   GetPlayerNumInFileMapping(){return _charId2Indexs.size();}

protected:
    bool   IsClosed(){ return _hFile == INVALID_HANDLE_VALUE;}
    bool   Close();
    uint32 CreateMapping();                               // 创建大文件
    uint32 OpenMapping();                                 // 创建 或 打开
    uint8* GetMappedMemory( uint8 type, uint32 index, const char* szFunc, const uint32 szLine ); // 得到映射指针
    void   FlushRelease();                                       // 刷如文件
    void   RemoveMapping();                               // 释放mapping

protected:
    typedef std::map<uint32,uint32>         CharId2IndexContainer;
    typedef CharId2IndexContainer::iterator ItrCharId2IndexContainer;

    uint32                _allocationGranularity; // 分配粒度
    HANDLE                _hFile                ; // 文件句柄
    HANDLE                _hFileMap             ; // 文件Mapping句柄
    LPVOID                _pFileMap             ; // 文件指针地址
    _tstring              _strPath              ; // 输出目录
    UniqueIDManager       _idManager            ; // Id生成器
    CharId2IndexContainer _charId2Indexs        ; // 角色id对应Index
    CSemiAutoIntLock      _lock                 ; // lock整个类
    bool                  _bHaveFileData        ; // 是否有文件数据存盘
    bool                  _bHaveInit            ; // 是否已经初始化过
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

    // 需要改为ShareMemory
    uint32 SaveDataToFile( const SqlMessageDBMsgSaveCharacter* pSqlMessage ); // 把角色数据写磁盘
    void   RemoveDataFile( uint32 charId, uint32 msgtime );
    bool   SetRootPath(const char* szPath);
    bool   LoadUnSaveCharacterDatas();      // 将上一次未保存完毕的所有角色列表从文件中载入

protected:
    FileDatabase(const FileDatabase&);
    const FileDatabase& operator = (const FileDatabase&);

protected:
    typedef std::map<uint32, SFileCharSaveData*> CharacterDataContainer;
    typedef CharacterDataContainer::iterator     ItrCharacterDataContainer;

    typedef std::map<uint32, uint32>             CharacterDataTimeContainer;
    typedef CharacterDataTimeContainer::iterator ItrCharacterDataTimeContainer;
    CharacterDataTimeContainer _charDataTimes;  // 时间搓。保证删除的是对应的data
    CSemiAutoIntLock           _lockTime;       // 时间搓容器锁
    std::string                _strFileDBPath;  // 文件数据库存储路径
};

FileDatabase& GetFileDatabase();

#endif //__DATABASESERVER_FILEDB_H__
