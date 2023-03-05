/********************************************************************
    Filename:    MonsterPet.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERPET_H__
#define __GAMESERVER_MONSTERPET_H__

#pragma once

#include "MonsterBaseEx.h"

class MonsterPet : public MonsterBaseEx, public TEnmity<EnmitySize>, 
                   INHERIT_POOL_PARAM( MonsterPet, 50 )
{
public:
    DECLARE_POOL_FUNC( MonsterPet )

    MonsterPet() {}
    virtual ~MonsterPet() {}

    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual bool OnThink();
    virtual bool OnMove( uint32 lapseTime );

    // �г�޵Ĺ��ﲻ�ܹر�AI��������Щ����֮���ս������Ϊ�Ա�û���˶��޷�����
    virtual bool MustOpenAI()    { return true;      }
    virtual void OnExitMySightNoPlayer(){}
    //////////////////////////////////////////////////////////////////////////
    // ������
    virtual int     GetEnmitySize() { return EnmityNum; }
    virtual SEnmity& EnmityList( int nNum );

    //��ȡĳ��ID�ĳ��ֵ
    virtual unsigned int GetEnmity( unsigned int nID );
    virtual bool         SetEnmity( unsigned int nID, unsigned int nEnmity );

    //���/�Ƴ�����б��ж���
    //���ID���б����Ѿ����ڣ��򲻻���ӡ�����false
    virtual bool         AddEnmityList(unsigned int nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList(unsigned int nID);
    virtual void         RemoveAllEnmityList(unsigned int nId);
    virtual bool         UpdateDecEnmityRate(unsigned int nID);

    //���/���ٳ��
    virtual bool         AddEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         DecEnmity(unsigned int nID, unsigned int nEnmity);
    
    //һ������DPS�Ĳο���� �˳�޲���Ӱ�����Ĺ���Ŀ��
    virtual unsigned int GetDamageEnmity(unsigned int nID);
    virtual bool         SetDamageEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity(unsigned int nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe(unsigned int nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity(unsigned int nEnmity);
    virtual void         DecAllEnmity(unsigned int nEnmity);

    
    virtual bool         IsHaveEnmity(); //��ǰ���йֶ���Ҵ��ڳ��    
    virtual short        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //��ǰ��ޱ������ɫ�����Char

    //��ǰ��ޱ��жԽ�ɫ�������Char
    virtual short GetMaxEnmityChar();
    virtual void  RefreshEnmity();    
    virtual void  OnEnmityNumChange(); // �е��˵������䶯
    virtual void  OnEnmityValueChanged( unsigned short id, unsigned int value); // ��ĳ�����˵ĳ��ֵ�䶯
    //////////////////////////////////////////////////////////////////////////
protected:
    void MoveAttackMoving( uint32 lapseTime ); // �й���Ŀ����ƶ�
    void MovePosMoving   ( uint32 lapseTime ); // һ��ĵ�Ŀ����ƶ�
};

#endif // __GAMESERVER_MONSTERPET_H__
