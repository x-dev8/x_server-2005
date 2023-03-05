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

        unsigned char uchElement;   // Ԫ������
        unsigned char uchLevel;     // Ԫ���ᴿ�ȼ�      
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

    void ClearSuitInfo(); // �����װ���Եļӳ�����
    bool ApplyToPlayer(); // �������Ե�����
    bool IsSuitHaveSkill( unsigned short skillId, unsigned short level );

    unsigned short GetExtendAttack() { return m_ustExtendAttack; }
    void CalcElementAttribute( unsigned short ustEquipLevel, unsigned char uchMainElement, unsigned char uchMaxCount, ElementInfoVertor& vecElementInfo );

	// ͨ��װ������nSuitID�õ�������װId
	unsigned short GetSkillSuitIdByPartSuitId(unsigned short id);

private:
#ifndef GAME_CLIENT
	GamePlayer*  _pGamePlayer;
#else
	uint8 m_nMainElement;//������Ԫ��
	int m_nMaxElementCount;//�����Ե�������
	bool m_bHaveNoMainElement;//û��������
#endif

    SuitContainer _suits;
    unsigned char m_uchSkillSuitLevel;      // ������װ����װ����ǿ���ȼ�
    RandVector m_vecRand;                   // ����������װ��õ�2������
    unsigned short m_ustExtendAttack;       // ����������װ���ӵ����˺�
};
