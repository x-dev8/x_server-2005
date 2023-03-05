#include "CampBattle.h"
class BaseCampBattleManager
{
public:
	BaseCampBattleManager(){}
	~BaseCampBattleManager(){}
	virtual CampBattle* GetCampBattleByPlayerID( unsigned int nPlayerID ) =0;

	unsigned char GetBattleType() const { return m_uchBattleType; }
	void SetBattleType( unsigned char uchValue ) { m_uchBattleType = uchValue; }
    bool IsCountryBattle() const { return m_uchBattleType == CampDefine::BattleTypeKing || m_uchBattleType == CampDefine::BattleTypeDragon || m_uchBattleType == CampDefine::BattleTypeRosefinch; }
protected:
	unsigned char m_uchBattleType;
};