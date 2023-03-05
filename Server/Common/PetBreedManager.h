#ifndef __GAMESERVER_PETBREEDMANAGER_H__
#define __GAMESERVER_PETBREEDMANAGER_H__

/************************************************************************
            ���ﷱֳ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "GameTimer.h"
#include "Singleton.h"
#include "Memory_Pool.h"
#include "GameDefinePet.h"

// ���ﷱֳ��Ϣ
class PetBreedInfo : INHERIT_POOL_PARAM( PetBreedInfo, 10 )
{
public:
    static PetBreedInfo* Instace() { return CNewWithDebug< PetBreedInfo >::Alloc( 1, "����PetBreedInfoʵ��" ); }
    virtual void Release() { CNewWithDebug< PetBreedInfo >::Free( this ); }

    // ���ID��
    unsigned long GetID() const { return _breedID; }

    // ����ID��
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

    // ��鶨ʱ��
    bool CheckTimer() { return _timer.DoneTimer(); }

    // ������ʱ��
    void StartTimer( unsigned int nStartTime, unsigned int nKeepTime );

protected:
    unsigned long   _breedID    ;
    unsigned long   _playerA    ;    // ���A
    unsigned long   _playerB    ;    // ���B
    unsigned char   _statusA    ;    // ���A״̬
    unsigned char   _statusB    ;    // ���B״̬
    SPetItem        _petA       ;    // ����A
    SPetItem        _petB       ;    // ����B
    GameTimerEx     _timer      ;    // ��ʱ��
};


#define thePetBreedManager PetBreedManager::Instance()

// ���ﷱֳ����
class PetBreedManager : public ISingletion< PetBreedManager >
{
public:
    PetBreedManager();
    ~PetBreedManager();

    // ����һ����ֳ��Ϣ
    PetBreedInfo* CreatePetBreed( unsigned long nBreedID );

    // ���һ����ֳ��Ϣ
    PetBreedInfo* GetPetBreed( unsigned long nBreedID );

    // ɾ��һ����ֳ��Ϣ
    void RemovePetBreed( unsigned long nBreedID, unsigned char nType );

    // ִ�и���
    void RunUpdate( unsigned int nCurrentTime );

private:

    // ��ֳ�б�
    typedef std::map< unsigned int, PetBreedInfo* > PetBreedMap;
    typedef PetBreedMap::iterator PetBreedMapIter;

    PetBreedMap m_mapPetBreed;      // ��ֳ�б�
    GameTimerEx m_xUpdateTimer;     // ���¶�ʱ��
};

#endif