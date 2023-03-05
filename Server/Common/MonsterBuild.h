/********************************************************************
    Filename:    MonsterBuild.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MONSTERBUILD_H__
#define __COMMON_MONSTERBUILD_H__

#include "MonsterBase.h"

const uint32 gMonsterBuildPoolBatchSize = 10;

class MonsterBuild : public MonsterBase, public TEnmity<EnmitySize>, 
                     INHERIT_POOL_PARAM( MonsterBuild, gMonsterBuildPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterBuild )

    MonsterBuild();
    virtual ~MonsterBuild();

    virtual void Run( DWORD dwCostTime ); // ����ִ��,������
    virtual void ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue );
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual void OnDeath();    
    virtual bool OnThink(){ return true; }                  // ��˼��ʱ��
    virtual bool OnMove( uint32 lapseTime ){ return true; } // ���ƶ�ʱ��

    //////////////////////////////////////////////////////////////////////////
    // ������
    virtual int     GetEnmitySize() { return EnmityNum; }
    virtual SEnmity& EnmityList( int nNum );

    //��ȡĳ��ID�ĳ��ֵ
    virtual unsigned int GetEnmity( GameObjectId nID );
    virtual bool         SetEnmity( GameObjectId nID, unsigned int nEnmity );

    //���/�Ƴ�����б��ж���
    //���ID���б����Ѿ����ڣ��򲻻���ӡ�����false
    virtual bool         AddEnmityList(GameObjectId nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList(GameObjectId nID);
    virtual void         RemoveAllEnmityList(GameObjectId nId);
    virtual bool         UpdateDecEnmityRate(GameObjectId nID);

    //���/���ٳ��
    virtual bool         AddEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecEnmity(GameObjectId nID, unsigned int nEnmity);

    //һ������DPS�Ĳο���� �˳�޲���Ӱ�����Ĺ���Ŀ��
    virtual unsigned int GetDamageEnmity(GameObjectId nID);
    virtual bool         SetDamageEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity(GameObjectId nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity(unsigned int nEnmity);
    virtual void         DecAllEnmity(unsigned int nEnmity);


    virtual bool         IsHaveEnmity(); //��ǰ���йֶ���Ҵ��ڳ��    
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //��ǰ��ޱ������ɫ�����Char

    //��ǰ��ޱ��жԽ�ɫ�������Char
    virtual GameObjectId		 GetMaxEnmityChar();
    virtual void  RefreshEnmity();    
    virtual void  OnEnmityNumChange(); // �е��˵������䶯
    virtual void  OnEnmityValueChanged( GameObjectId id, unsigned int value); // ��ĳ�����˵ĳ��ֵ�䶯
    //////////////////////////////////////////////////////////////////////////
protected:
    void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // ���ָ���Ŀ��ĳ��ֵ
};

#endif // __COMMON_MONSTERBUILD_H__
