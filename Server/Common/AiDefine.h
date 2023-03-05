#ifndef __MONSTERSERVERDEFINE_H__
#define __MONSTERSERVERDEFINE_H__

/************************************************************************
                �������Զ���

************************************************************************/
#include <map>
#include <set>
#include <functional>
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
#include "MsgBase.h"
#include "MonsterDefine.h"

#define ENMITY_RATE           0.2f // �ȼ���޲����

struct SPetItem;
namespace AiDefine
{
    enum EServerDefine
    {
        NoneEnmity = 0,                 // �޳��ֵ
        EnmityReductionRate = 100,      // ������˥������
        EnmityBaseRate = 1000,          // ������˥������
        MinEnmityViewSight = 4,         // ��С�����Ұ

        MonsterMaxTaskCount  = 10,      // �����������г���
        MonsterMaxSkillCount = 3 ,      // ���＼�ܵĸ���
        PetMonsterSkillIndex = 2 ,      // ����ʹ�ü���

        MonsterThinkTime = 1000,        // ����˼������ʱ�䷶Χ
        BaseThinkTime = 200,            // ����˼��ʱ��

        RefeshEnmitySpaceTime = 1000,   // ������ˢ�¶�ʱ��
        MonsterIdleMoveRand =  10000,   // �����漴�ƶ����ʻ���

        VerifyPointSpaceTime = 2000,    // 2��ͬ������λ��

        MonsterDeathScriptEnter = 1,    // �����ű����
        MonsterDefaultScriptEnter = 2,  // ״̬�ı�Ĭ�Ͻű����

        LostMasterKeepTime = 300000,    // �����ֶ�ʧ���˺�5���Ӻ���ʧ

        AiTalkTimeOut = 2 * 60000,      // npcͣ�����Ի���ʱʱ��

        MonsterMoveRadius = 2,
		MonsterUpdateBeLongTime=1000,	// ��������ĸ��¼��

        ////////////////////////////////////////////////////////////////
        ProjectCharDistance = 10,       // 10 ��ʾ
        ProtectCharStopDistance = 20,   // 20 ֹͣ
        TellClientDisPerTime = 5000,    // 
        //////////////////////////////////////////////////////////
        // ����AI��������ȼ�
        LowAiTaskPriority = 0,
        NormalAiTaskPriority,
        HighAiTaskPriority,

        /////////////////////////////////////////////////////////
        // ���ﴴ����ʽ
        NormalCreateType = 0,

        ////////////////////////////////////////////////////////////
        ThinkingDoNothing = 0   ,       // ɶҲ����
        ThinkingMoveToBorn      ,       // �ص�������
        ThinkingMoveAround      ,       // ��Χ�漴�ƶ�
        ThinkingMoveToTarget    ,       // �ƶ�������Ŀ��
        ThinkingAttackTarget    ,       // ����Ŀ��
        ThinkingMoveToRoute     ,       // �ƶ���·��
        ThinkingMoveToLastIdle  ,       // �ƶ������û�б�����������
        ThinkingMoveToMaster    ,       // �ƶ����������
        ThinkingFollowMaster    ,       // ��������
        ThinkingWaitRelive      ,       // �����ȴ�����
        ThinkingStopToTalk      ,       // ֹͣ�ƶ�����ҶԻ�
        ThinkingMoveToPoint     ,       // �ƶ���ĳһ��
        ThinkingMoveEscape      ,       // ����
        ThinkingIdle            ,       // ����״̬
        ThinkingRandRun         ,       // �漴����( ��������״̬ )

        /////////////////////////////////////////////////////////////
        LuaTimerCount = 3,              // Lua�ű���ʱ��������
        LuaValueArrayCount = 10,  
    };

    enum EAiTimer
    {
        AiTimer_Thinking        = 0 ,   // AI˼��
        AiTimer_IdleView            ,   // ����ָ���ս����Ұ
        AiTimer_Disappear           ,   // ��������
        AiTimer_Restore             ,   // �����Ѫ, ��ħ
        AiTimer_Move                ,   // ���͹���λ����Ϣ
        AiTimer_Relive              ,   // ��������
        AiTimer_Talk                ,   // ͣ�����Ի�
        AiTimer_StatusChange        ,   // ����״̬�ı�
        AiTimer_KeepAttack          ,   // ����׷��
        AiTimer_RouteMove           ,   // ·���ƶ�ͣ��

        AiTimer_MaxCount             
    };
}

// ������
class EnmityData
{
public:
    EnmityData() : m_nEnmity( 0 ), m_nReduction( 0 ), m_nDamage( 0 ){}

    unsigned int GetEnmity() const { return m_nEnmity; }
    unsigned int GetReduction() const { return m_nReduction; }
    unsigned int GetDamage() const { return m_nDamage; }

    void SetEnmity( unsigned int nValue ) { m_nEnmity = nValue; }
    void SetReduction( unsigned int nValue ) { m_nReduction = nValue; }
    void SetDamage( unsigned int nValue ) { m_nDamage = nValue; }

    void AddEnmity( unsigned int nValue ) { m_nEnmity += nValue; }
    void AddDamage( unsigned int nValue ) { m_nDamage += nValue; }

    void DecEnmity( unsigned int nValue )
    {
        if ( m_nEnmity <= nValue )
        { m_nEnmity = 0; }
        else
        { m_nEnmity -= nValue; }
    }

    void ClearEnmity() { m_nEnmity = 0; m_nReduction = 0; m_nDamage = 0; }
    void ClearDamage() { m_nDamage = 0; }

    bool HaveEnmity() const { return m_nEnmity != AiDefine::NoneEnmity; }

private:
    // ���ﵱǰ���
    unsigned int m_nEnmity;          

     // ���˥������( ÿ��˥������ֵ )
    unsigned int m_nReduction;      

    // ��¼��ҶԹ�����˺���ֵ ��Ӱ�����Ĺ���Ŀ��
    unsigned int m_nDamage; 
};


class AiEnmity
{
public:
    // ��ó������
    int GetEnmityCount() const { return static_cast< int >( m_mapTargetEnmity.size() ); }

    // ��ӳ��
    unsigned int AddEnmity( GameObjectId nID, unsigned int nEnmity, unsigned int nDamage, int nReductionRate = AiDefine::EnmityReductionRate );

    // ���ó��
    unsigned int SetEnmity( GameObjectId nID, unsigned int nEnmity, int nReductionRate = AiDefine::EnmityReductionRate );

    // ���ٳ��( ���ص�ǰ���ֵ )
    unsigned int DecEnmity( GameObjectId nID, unsigned int nEnmity );

    // ɾ������б�
    void RemoveEnmity( GameObjectId nID );

    // ������
    void ClearEnmity( bool bClearList );

    // �Ƿ��г��
    bool HaveEnmity();

    // ��ó������
    EnmityData* GetEnmity( GameObjectId nID );

    // ��ó��ֵ���Ľ�ɫ
    GameObjectId GetMaxEnmityID();
         
    // ����˺����Ľ�ɫ
    GameObjectId GetMaxDamageID();

    // ɾ���Լ���Ŀ��ĳ���б�
    void RemoveAttackTarget( GameObjectId nID ) { m_setAttackTarget.erase( nID ); }

    // ����Լ���Ŀ��ĳ���б�
    void AddAttackTarget( GameObjectId nID ) { m_setAttackTarget.insert( nID ); }

    // �Ƿ��ǹ���Ŀ��
    bool IsAttackTarget( GameObjectId nID ) { return m_setAttackTarget.find( nID ) != m_setAttackTarget.end(); }

	// �³��Ŀ��ӿ�
	virtual void OnNewEnmityTarget( GameObjectId nID ) {}

protected:
    typedef std::map< GameObjectId, EnmityData > TargetEnmityMap;
    typedef TargetEnmityMap::iterator TargetEnmityMapIter;

    typedef std::set< GameObjectId > AttackTargetSet;
    typedef AttackTargetSet::iterator AttackTargetSetIter;

    // �Լ��Ա��˲����ĳ���б�
    TargetEnmityMap m_mapTargetEnmity;   

    // �Լ�������Ŀ��
    AttackTargetSet m_setAttackTarget;
};


///////////////////////////////////////////////
// ����AI����
class AiSkill
{
public:

    AiSkill() : m_nID( 0 ), m_nLevel( 0 ), m_nUseRate( 0 ), m_nCostHP( 0 ), m_nCostMP( 0 ),
        m_nStartColdDownTime( 0 ), m_nColdDownTime( 0 ), m_nAttackDistance( 10 ){}

    unsigned short GetID() const { return m_nID; }
    unsigned char GetLevel() const { return m_nLevel; }
    unsigned short GetCostHP() const { return m_nCostHP; }
    unsigned short GetCostMP() const { return m_nCostMP; }
    unsigned int GetAttackDistance() const { return m_nAttackDistance; }
    unsigned char GetUseRate() const { return m_nUseRate; }
    unsigned int GetStartColdDownTime() const { return m_nStartColdDownTime; }
    unsigned int GetColdDownTime() const { return m_nColdDownTime; }

    void SetID( unsigned short nValue ) { m_nID = nValue; }
    void SetLevel( unsigned char nValue ) { m_nLevel = nValue; }
    void SetCostHP( unsigned short nValue ) { m_nCostHP = nValue; }
    void SetCostMP( unsigned short nValue ) { m_nCostMP = nValue; }
    void SetAttackDistance( unsigned int nValue ) { m_nAttackDistance = nValue; }
    void SetUseRate( unsigned char nValue ) { m_nUseRate = nValue; }
    void SetStartColdDownTime( unsigned int nValue ) { m_nStartColdDownTime = nValue; }
    void SetColdDownTime( unsigned int nValue ) { m_nColdDownTime = nValue; }

    bool CanUseAiSkill( uint32 nHP, uint32 nMP ) const;

private:
    // ����ID
    unsigned short m_nID;

    // ���ܵȼ�
    unsigned char m_nLevel;    

    // �������HP
    unsigned short m_nCostHP;

    // �������MP
    unsigned short m_nCostMP;

    // ��������
    unsigned int m_nAttackDistance;

    // ���ܴ����ĸ���
    unsigned char m_nUseRate;

    // ����CD��ʼʱ��
    unsigned int m_nStartColdDownTime;

    // ���ܵ�CDʱ��
    unsigned int m_nColdDownTime;
};

// ����AI�������
class AiTask : INHERIT_POOL_PARAM( AiTask, 100 )
{
public:
    DECLARE_POOL_FUNC( AiTask )

    AiTask() : m_nPriority( AiDefine::NormalAiTaskPriority ), m_nAttackID( -1 ), m_nSkillID( 0 ), m_nSkillLevel( 0 ){}
    virtual ~AiTask(){};

    unsigned char GetPriority() const { return m_nPriority; }
    GameObjectId GetAttackID() const { return m_nAttackID; }
    unsigned short GetSkillID() const { return m_nSkillID; }
    unsigned char GetSkillLevel() const { return m_nSkillLevel; }

    void SetPriority( unsigned char nValue ) { m_nPriority = nValue; }
    void SetAttackID( GameObjectId nValue ) { m_nAttackID = nValue; }
    void SetSkillID( unsigned short nValue ) { m_nSkillID = nValue; }
    void SetSkillLevel( unsigned char nValue ) { m_nSkillLevel = nValue; }

private:
    // �������ȼ�
    unsigned char m_nPriority;

    // Ҫ������Ŀ��
    GameObjectId m_nAttackID;

    // ����ID
    unsigned short m_nSkillID;

    // ���ܵȼ�
    unsigned char m_nSkillLevel;
};

// ��AITask���ȼ�����
inline bool SortAITaskPriority( const AiTask* pLeft, const AiTask* pRight )
{
    if ( pLeft == NULL || pRight == NULL )
    { return false; }

    return (pLeft -> GetPriority() >= pRight -> GetPriority());
}

////////////////////////////////////////////////////////////////////////
class MonsterCreateData
{
public:
    MonsterCreateData() 
    {
        memset( this, 0, sizeof( MonsterCreateData ) ); 
        m_nRouteID = -1;
        m_nMonsterIndex = -1;
        m_nCount = 1;
        m_pPetData = NULL;
    }

    unsigned int GetMapID() const { return m_nMapID; }
    float GetPostionX() const { return m_fX; }
    float GetPostionY() const { return m_fY; }
    float GetDirX() const { return m_fDirX; }
    float GetDirY() const { return m_fDirY; }
    int GetDirection() const { return m_nDirection; }
    float GetRadius() const { return m_fRadius; }
    float GetBodySize() const { return m_fBodySize; }
    int GetMonsterIndex() const { return m_nMonsterIndex; }
    int GetMonsterID() const { return m_nMonsterID; }
    short GetCount() const { return m_nCount; }
    short GetCreateType() const { return m_nCreateType; }
    short GetFightCamp() const { return m_nFightCamp; }
    short GetCountry() const { return m_nCountry; }
    short GetForce() const { return m_nForce; }
    short GetSpecialType() const { return m_nSpecialType; }
    unsigned int GetSpecialValue() const { return m_nSpecialValue; }
    int GetRouteID() const { return m_nRouteID; }
    const RECT& GetCanMoveZone() const { return m_xCanMoveZone; }
    int GetThinkingTime() const { return m_nThinkingTime; }
    int GetReliveTime() const { return m_nReliveTime; }
    SPetItem* GetPetItem() const { return m_pPetData; }
	bool IsCanRide() const { return m_bIsCanRide; }

    void SetMapID( unsigned int nValue ) { m_nMapID = nValue; }
    void SetPostionX( float fValue ) { m_fX = fValue; }
    void SetPostionY( float fValue ) { m_fY = fValue; }
    void SetDirection( int nValue ) { m_nDirection = nValue; }
    void SetDirX( float fValue ) { m_fDirX = fValue; }
    void SetDirY( float fValue ) { m_fDirY = fValue; }
    void SetRadius( float fValue ) { m_fRadius = fValue; }
    void SetBodySize( float fValue ){ m_fBodySize = fValue; }
    void SetMonsterIndex( int nValue ) { m_nMonsterIndex = nValue; }
    void SetMonsterID( int nValue ) { m_nMonsterID = nValue; }
    void SetCount( short nValue ) { m_nCount = nValue; }
    void SetCreateType( short nValue ) { m_nCreateType = nValue; }
    void SetFightCamp( short nValue ) { m_nFightCamp = nValue; }
    void SetCountry( short nValue ) { m_nCountry = nValue; }
    void SetForce( short nValue ) { m_nForce = nValue; }
    void SetSpecialType( short nValue ) { m_nSpecialType = nValue; }
    void SetSpecialValue( unsigned int nValue ) { m_nSpecialValue = nValue; }
    void SetRouteID( int nValue ) { m_nRouteID = nValue; }
    void SetCanMoveZone( RECT& xValue ) { m_xCanMoveZone = xValue; }
    void SetThinkingTime( int nValue ) { m_nThinkingTime = nValue; }
    void SetReliveTime( int nValue ) { m_nReliveTime = nValue; }
    void SetPetItem( SPetItem* pPetData ) { m_pPetData = pPetData; }
	void SetCanRide( bool b ) { m_bIsCanRide = b; }

private:
    unsigned int m_nMapID;
    float m_fX;
    float m_fY;
    float m_fDirX;
    float m_fDirY;
    int m_nDirection;       // ����Ƕ�
    float m_fRadius;        // ��Χ
    float m_fBodySize;      // ����
    int m_nMonsterIndex;    // �������к�
    int m_nMonsterID;       // ����ID
    short m_nCount;         // ����
    short m_nCreateType;    // ��������
    short m_nFightCamp;     // ��Ӫ
    short m_nCountry;       // ����
    short m_nForce;         // ����
    short m_nSpecialType;   // ר������
    unsigned int m_nSpecialValue;  // ר��ID
    int m_nRouteID;                // ·��ID
    RECT m_xCanMoveZone;           // �����ƶ��ķ���
    int m_nThinkingTime;           // ˼��ʱ��
    int m_nReliveTime;             // �������ø���
    SPetItem* m_pPetData;     // ��������
	bool m_bIsCanRide;		// �ܷ���
};

#endif