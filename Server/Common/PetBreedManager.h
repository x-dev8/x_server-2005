#ifndef __GAMESERVER_PETBREEDMANAGER_H__
#define __GAMESERVER_PETBREEDMANAGER_H__

/************************************************************************
            宠物繁殖管理
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "GameTimer.h"
#include "Singleton.h"
#include "Memory_Pool.h"
#include "GameDefinePet.h"

// 宠物繁殖信息
class PetBreedInfo : INHERIT_POOL_PARAM( PetBreedInfo, 10 )
{
public:
    static PetBreedInfo* Instace() { return CNewWithDebug< PetBreedInfo >::Alloc( 1, "创建PetBreedInfo实例" ); }
    virtual void Release() { CNewWithDebug< PetBreedInfo >::Free( this ); }

    // 获得ID号
    unsigned long GetID() const { return _breedID; }

    // 设置ID号
    void SetID( unsigned long nValue ) { _breedID = nValue; }
    
    unsigned long GetPlayerA() { return _playerA; }
    unsigned long GetPlayerB() { return _playerB; }

    unsigned char GetStatusA() { return _statusA; }
    unsigned char GetStatusB() { return _statusB; }

    void  SetPlayerA( unsigned long ID ) { _playerA = ID; }
    void  SetPlayerB( unsigned long ID ) { _playerB = ID; }

    void  SetStatusA( unsigned char status ) { _statusA = status; }
    void  SetStatusB( unsigned char status ) { _statusB = status; }

    SPetItem* GetPetA()
    {
        if (_petA.baseInfo.petId == InvalidLogicNumber)
        { return NULL; }

        if (_petA.baseInfo.guid  == InvalidLogicNumber)
        { return NULL; }

        return  &_petA;
    }

    SPetItem* GetPetB()
    {
        if (_petB.baseInfo.petId == InvalidLogicNumber)
        { return NULL; }

        if (_petB.baseInfo.guid  == InvalidLogicNumber)
        { return NULL; }

        return  &_petB;
    }

    void SetPetA( SPetItem& pet ) { _petA = pet; }
    void SetPetB( SPetItem& pet ) { _petB = pet; }

    void ClearPetBreedData(  unsigned char uchType );

    // 检查定时器
    bool CheckTimer() { return _timer.DoneTimer(); }

    // 开启定时器
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime );

protected:
    unsigned long   _breedID    ;
    unsigned long   _playerA    ;    // 玩家A
    unsigned long   _playerB    ;    // 玩家B
    unsigned char   _statusA    ;    // 玩家A状态
    unsigned char   _statusB    ;    // 玩家B状态
    SPetItem        _petA       ;    // 宠物A
    SPetItem        _petB       ;    // 宠物B
    GameTimerEx     _timer      ;    // 定时器
};


#define thePetBreedManager PetBreedManager::Instance()

// 宠物繁殖管理
class PetBreedManager : public ISingletion< PetBreedManager >
{
public:
    PetBreedManager();
    ~PetBreedManager();

    // 创建一个繁殖信息
    PetBreedInfo* CreatePetBreed( unsigned long nBreedID );

    // 获得一个繁殖信息
    PetBreedInfo* GetPetBreed( unsigned long nBreedID );

    // 删除一个繁殖信息
    void RemovePetBreed( unsigned long nBreedID, unsigned char nType );

    // 执行更新
    void RunUpdate( unsigned int nCurrentTime );

private:

    // 繁殖列表
    typedef std::map< unsigned int, PetBreedInfo* > PetBreedMap;
    typedef PetBreedMap::iterator PetBreedMapIter;

    PetBreedMap m_mapPetBreed;      // 繁殖列表
    GameTimerEx m_xUpdateTimer;     // 更新定时器
};

#endif