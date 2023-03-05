#ifndef __SUITMANAGER_H__
#define __SUITMANAGER_H__
/********************************************************************
        Filename:    SuitManager.h
        MaintenanceMan Mail: lori227@live.cn

        套装管理类, 
        服务端逻辑在ServerSuitManager.cpp中实现 
        客户端逻辑在ClientSuitManger.cpp中实现
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
    bool ApplyToPlayer();                                                   // 作用属性到人物
    bool IsSuitHaveSkill( unsigned short skillId, unsigned short level );   // 判断技能套装技能是否能用

protected:
    void ClearSuitInfo(); // 清空套装属性的加成属性
    SCharItem* GetAttriSuitEquipItem( int nIndex );
    void AddEquipAttribute( unsigned short ustItemID );
    void AddStarActivationAttribute ( SStarActivation::SEffect* pEffect  );
    void AddStampActivationAttribute( SStampActivation::SEffect* pEffect );
	void ClearSuitEquipSkill(bool IsCheckEmpty = false);
private:
    T*  m_pGamePlayer;

    SuitContainer m_vecSuitID;              // 保存人物身上穿的所有的套装ID
    unsigned char m_uchSkillSuitLevel;      // 技能套装的套装整体强化等级

	std::vector<unsigned short> SuitEquipSkillVec;
};

#endif