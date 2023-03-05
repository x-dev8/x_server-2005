/********************************************************************
    Filename:    Enmity.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_ENMITY_H__
#define __GAMESERVER_ENMITY_H__

#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk/d3dx9math.h"

#define ENMITY_NOTINLIST 0xFFFFFFFF
#define NULLID           0xFFFF
#define EnmitySize       150

struct SEnmity
{
    GameObjectId nID;
    unsigned int nEnmity;
    unsigned int nDecEnmityRate;

    SEnmity()
    { Reset(); }

    void ClearEnmity();
    void Reset();
};

//////////////////////////////////////////////////////////////////////////
//inline
inline void SEnmity::ClearEnmity()
{
    nEnmity        = 0;
    nDecEnmityRate = 0;
}

inline void SEnmity::Reset()
{
    nID            = NULLID;
    nEnmity        = 0;
    nDecEnmityRate = 0;
}

template<int Num> 
class TEnmity
{ // ����̫�� ��Ҫ��Ϊmap
public:
    static const int EnmityNum = Num;

    TEnmity()
    { m_dwLastDecEnmityTime = 0; }

    virtual ~TEnmity()
    {}

public:
	uint32  m_dwLastDecEnmityTime;
    SEnmity m_enmityList[Num];
};

template <int Num>
class TPlayerEnmity : public TEnmity<Num>
{
public:
    TPlayerEnmity()
    {}

public:
    SEnmity m_damageenmityList[Num]; // ����ӵ��˺�ֵ��ɵĳ���б����б�Ӱ����﹥��Ŀ�꣬����DPS����һ������
};

class IEnmityChar
{
public:
    IEnmityChar() {}
    virtual ~IEnmityChar() {}
    
    virtual int          GetEnmitySize()             { return 0; }
    virtual SEnmity&     EnmityList(int nNum)        { static SEnmity e; return e;}
    virtual unsigned int GetEnmity(GameObjectId nID) { return 0;}
    virtual bool         SetEnmity(GameObjectId nID, unsigned int nEnmity) { return false;}
    virtual bool         AddEnmityList(GameObjectId nID, unsigned int nEnmity = 0) { return false;} // �������/�Ƴ�����б��ж��� ���ID���б����Ѿ����ڣ��򲻻���ӡ�����false
    virtual bool         RemoveEnmityList(GameObjectId nID) { return false; }
    virtual void         RemoveAllEnmityList(GameObjectId nId) { }
    virtual bool         UpdateDecEnmityRate(GameObjectId nID) { return false; }
    virtual bool         AddEnmity(GameObjectId nID, unsigned int nEnmity) { return false; } // �������/���ٳ��
    virtual bool         DecEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual unsigned int GetDamageEnmity(GameObjectId nID) { return -1; }                    // ����һ������DPS�Ĳο���� �˳�޲���Ӱ�����Ĺ���Ŀ��
    virtual bool         SetDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         AddDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         DecDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity) { return false; }
    virtual void         ClearAllEnmity() {}
    virtual void         AddAllEnmity(unsigned int nEnmity) {}
    virtual void         DecAllEnmity(unsigned int nEnmity) {}
    virtual bool         IsHaveEnmity() { return false; }                                              // ��ǰ���йֶ���Ҵ��ڳ��
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ) { return -1; } // ��ǰ��ޱ������ɫ�����Char
    virtual GameObjectId        GetMaxEnmityChar()  { return -1; }                                            // ��ǰ��ޱ��жԽ�ɫ�������Char

protected:
    virtual void         OnEnmityNumChange() {} // �е��˵������䶯
    virtual void         OnEnmityValueChanged( GameObjectId id, unsigned int value ) {}// ��ĳ�����˵ĳ��ֵ�䶯
};

#endif
