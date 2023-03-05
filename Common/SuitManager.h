#ifndef __SUITMANAGER_H__
#define __SUITMANAGER_H__
/********************************************************************
        Filename:    SuitManager.h
        MaintenanceMan Mail: lori227@live.cn

        ��װ������, 
        ������߼���ServerSuitManager.cpp��ʵ�� 
        �ͻ����߼���ClientSuitManger.cpp��ʵ��
*********************************************************************/
#include "ItemDetail.h"
#include "ArmourElementsConfig.h"
#include "GlobalDef.h"
#include "StarLevelUpConfig.h"

template< class T >
class SuitManager
{
protected:
    struct SuitPart
    {
        short stPartCount;
        short sSuitID;
    };

    struct EquipSuitID
    {
        short sEquipSuitID;
        bool bEquiped;
    };

    typedef std::map< unsigned short, unsigned char > SuitCounter;
    typedef SuitCounter::iterator                     ItrSuitCounter;

    typedef std::map< unsigned char, unsigned char  > StarLevelCounter;
    typedef StarLevelCounter::iterator                StarLevelCounterItr;
    typedef StarLevelCounter::reverse_iterator        StarLevelCounterReItr;

    typedef std::vector< unsigned short >            SuitContainer;
    typedef SuitContainer::iterator                  ItrSuitContainer;

public:
    SuitManager() : m_pGamePlayer( NULL ), m_uchSkillSuitLevel( 100 )
    { 
        m_vecSuitID.clear();
    }
    ~SuitManager() { }

    void SetPlayer( T* pPlayer );
    bool ApplyToPlayer();                                                   // �������Ե�����
    bool IsSuitHaveSkill( unsigned short skillId, unsigned short level );   // �жϼ�����װ�����Ƿ�����

protected:
    void ClearSuitInfo(); // �����װ���Եļӳ�����
    SCharItem* GetAttriSuitEquipItem( int nIndex );
    void AddEquipAttribute( unsigned short ustItemID );
    void AddStarActivationAttribute ( SStarActivation::SEffect* pEffect  );
    void AddStampActivationAttribute( SStampActivation::SEffect* pEffect );
	void ClearSuitEquipSkill(bool IsCheckEmpty = false);
private:
    T*  m_pGamePlayer;

    SuitContainer m_vecSuitID;              // �����������ϴ������е���װID
    unsigned char m_uchSkillSuitLevel;      // ������װ����װ����ǿ���ȼ�

	std::vector<unsigned short> SuitEquipSkillVec;
};

#endif