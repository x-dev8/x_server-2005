/********************************************************************
    Filename:    SuitManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"

#ifndef GAME_CLIENT
class GamePlayer;
#endif

class SuitManager
{
protected:

    struct SuitPart
    {
        short stPartCount;
        short sSuitID;
    };

    struct ArmourSuitID
    {
        short sArmourSuitID;
        bool bEquiped;
    };

    struct ElementInfo
    {
        ElementInfo() : uchElement( 0 ), uchLevel( 0 ) {};
        ElementInfo( unsigned char element, unsigned char level ) : uchElement( element ), uchLevel( level ) { }

        unsigned char uchElement;   // 元素属性
        unsigned char uchLevel;     // 元素提纯等级      
    };

    typedef std::map<unsigned short, unsigned char> SuitCounter;
    typedef SuitCounter::iterator                   ItrSuitCounter;

    typedef std::vector<unsigned short> SuitContainer;
    typedef SuitContainer::iterator     ItrSuitContainer;

    typedef std::map< unsigned char, unsigned char > MapElementsCount;
    typedef MapElementsCount::iterator MapElementsCountIter;

    typedef std::vector < unsigned short > RandVector;
    typedef RandVector::iterator RandVectorIter;

    typedef std::vector< ElementInfo > ElementInfoVertor;
    typedef ElementInfoVertor::iterator ElementInfoVertorIter;

public:
    SuitManager();
    ~SuitManager();

#ifndef GAME_CLIENT
    void  SetPlayer( GamePlayer* pPlayer );
#else
	void GetElementInfo( int& rMainElement, int& rMaxCount, bool& rHaveNoMain )
	{
		rMainElement = static_cast<int>(m_nMainElement);
		rMaxCount = m_nMaxElementCount;
		rHaveNoMain = m_bHaveNoMainElement;
	}
#endif

    void ClearSuitInfo(); // 清空套装属性的加成属性
    bool ApplyToPlayer(); // 作用属性到人物
    bool IsSuitHaveSkill( unsigned short skillId, unsigned short level );

    unsigned short GetExtendAttack() { return m_ustExtendAttack; }
    void CalcElementAttribute( unsigned short ustEquipLevel, unsigned char uchMainElement, unsigned char uchMaxCount, ElementInfoVertor& vecElementInfo );

	// 通过装备部件nSuitID得到技能套装Id
	unsigned short GetSkillSuitIdByPartSuitId(unsigned short id);

private:
#ifndef GAME_CLIENT
	GamePlayer*  _pGamePlayer;
#else
	uint8 m_nMainElement;//主属性元素
	int m_nMaxElementCount;//主属性的最大个数
	bool m_bHaveNoMainElement;//没有主属性
#endif

    SuitContainer _suits;
    unsigned char m_uchSkillSuitLevel;      // 技能套装的套装整体强化等级
    RandVector m_vecRand;                   // 保存五行套装获得的2级属性
    unsigned short m_ustExtendAttack;       // 保存五行套装附加的总伤害
};
