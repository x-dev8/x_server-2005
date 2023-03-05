/********************************************************************
    Filename:    PetManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_PETMANAGER_H__
#define __GAMESERVER_PETMANAGER_H__

#pragma once

#include "GlobalDef.h"
#include "bag\SkillBag.h"

class GamePlayer;
class MonsterBaseEx;

class PetManager
{
public:
    enum EConstDefine
    {

    };

    enum EActionType
    {
        AT_NotActive, // ����ս
        AT_Active,    // ��ս
    };

public: // ����
    PetManager();
    ~PetManager(){}

    bool          CreateFromData( GamePlayer* pOwner, SPetItem* pPetItems, int nPetCount ); // ��ʼ������

    bool          InitPetAttribute ( SPetItem& pet );
    bool          InitPetSkill     ( SPetItem& pet );
    bool          UpdateTalentSkill( uint16 petType, uint8 skillLevel   );
    //bool          UpdatePetAttribute ( SPetItem& pet );
    bool          RealizePetSkill  ( SPetItem& pet , std::vector<uint16>& vecNewSkill, bool bInit = false );                // ��������

    int64         GetNewBigID();                                     // �õ����õ�BigId
    int           GetActivePetIndex()     { return _activeIndex; }
    unsigned long GetAccumulateActionTime() { return _accumulateActionTime; }
    int           GetActivePetId();                                  // �õ���ս�����Id
    int           GetPetEmptyCount();                                // �õ���λ��
    int           GetPetNumber();                                    // ��ó�������
    int           GetPetMaxLevel();                                  // ��ó�����ߵȼ�
    bool          IsHavePet( int petId );                            // �Ƿ��г���
    bool          IsHavePetType( int petType );                      // �Ƿ��г�������

    SPetItem*     GetPetByGuid( __int64 nBigId );                    // ����guid�õ�����
    int           GetPetIndexByGuid( __int64 nBigId );               // ����guid�õ�����λ��

    SPetItem*     GetActivePet();                                    // �õ���ս�ĳ���
    SPetItem*     GetPetByIndex( int nIndex ) ;                      // �õ�ָ��Index�ĳ���

    void          SetAccumulateActionTime(unsigned long dwTime);     // �����ۼƼ���ʱ��
    long          ProcessSetPetActive( int nIndex );                 // ���ó�ս
                  
    long          PushPet( const SPetItem& PetItem );                // ����һֻ����
    long          PopPet ( int nIndex, bool& isActiveIndex );        // ɾ��һֻ����
    long          PopPetByBigId( __int64 nBigId, bool& bActive );    // ɾ��һ������

    void          AddActivePetExp( int iRewardExp );                 // ���Ӿ���ֵ
    bool          AddPetExp( int nIndex, int iRewardExp );           // ���Ӿ���ֵ

    bool          AddPetSavvy( int nIndex );                         // ��������

    void          UpdateActiveIndex();                               // ���³�ս��Index
    void          UpdatePetHP(short nIndex);                         // ���³��������  
    void          UpdateActiveSkillBag();                            // ���³�ս�ĳ���ļ���
    //void          ApplyPassiveSkillToPet( SPetItem* pPetItem );      

    void          RefreshPetData( unsigned long elapsTime );

    void          LostActivePetMonster();
    void          LostActivePet( bool bIsBeKilled = false );

    void          ApplyBaseAttrToFight   ( SPetItem& pet );         // ���³�ս��������
    void          ApplyPetAttrToPlayer   ( bool bInit = false, bool bSendMessage = true ); // ���³�ս�������Ե���������
	
	

    void          CalcBattleEffectiveness( SPetItem& pet );         // �������ս����

    int           GetPetCount() { return _nPetCount; }
    void          SetPetCount(int nValue) { _nPetCount = nValue; }

    bool          IsPetFull();
    bool          IsSelfPet( GameObjectId petCharId );
    bool          HaveActivePet();
    int           GetActivePetCharId() { return _activePetCharId; }

    MonsterBaseEx*  GetMonsterNurturePet();

    bool          AddPetHp( int nIndex, int hp );
    bool          AddPetLife( int nIndex, int life );
    bool          AddPetLoyalty( int nIndex, int loyalty );

    SPetItem*     GetBreedPet();
    bool          SetBreedPet( SPetItem *pPet );
    void          ClearBreedPet();

    SkillBag*     GetActiveSkillBag() { return &_activeSkillBag; }
	bool		  ClearPetPotential(int index);

private: // ����
    friend class GamePlayer;
    typedef std::set<unsigned long>  PetIdentifyContainer;
    typedef PetIdentifyContainer::iterator ItrPetIdentifyContainer;

    int           _nPetCount ;              // �����������
    SPetItem*     _pPetItems ;              // ָ��ʵ�ʵ�����
    GamePlayer*   _pGamePlayer  ;           // ָ����������
    int           _activeIndex  ;           // ��ս������±�λ��
    GameObjectId  _activePetCharId;         // ��ս�����ɫID
    SkillBag      _activeSkillBag;          // ��ս�ĳ���ļ��ܱ���
    unsigned long _accumulateActionTime;    // ��ս�����ۻ���ʱ��
    unsigned long _refreshLifeTime;         // ˢ�³�������
    unsigned long _refreshLoyaltyTime;      // ˢ�³�����ֶ�

public:
	//������װ������ ����ֻ�д��ڳ�ս״̬�ſ��Ի�װ��
	bool          ChangePetEquip(__int64 nBigId,__int64 ItemOnlyID,int Index);//��������װ�� ��ָ��λ�������װ�� ���� �������Ļ� ��ʾ��װ��ʧ��
	bool		  RemovePetEquip(__int64 nBigId,int Index,int bagIndex=-1);//����ָ��λ�õ�װ�� �Ű�����ȥ ���漰װ����ɾ��	
	void		  UpdatePetInfo();
	bool		  ChangePetMode(uint32 ModeID,__int64 Time);//�޸ĸ�����ģ�� ��ָ��ʱ������

	void		  ChangePetAtterValue(__int64 nBigId,__int64 TargetPetID);
private:
	void		  UpdateActionPetInfo(SPetItem * pPet);
	void		  OnUpdateActionPetMode();//���³�ս�ĸ�����ģ�� ����ڳ�ս�ڼ䷢��ģ�͵��ھ�ǿ���޸ĸ���ģ�� ���Ҹ��߾Ź���
	void		  UpdatePetEquipTime();
};

#endif // __GAMESERVER_PETMANAGER_H__
