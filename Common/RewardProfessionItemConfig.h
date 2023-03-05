#ifndef __GIFT_ITEM_H__
#define __GIFT_ITEM_H__

#define theRewardProfessionItemConfig RewardProfessionItemConfig::Instance()   //ʵ���ӿ�

#include <vector>

#include "GlobalDef.h"

class RewardProfessionItemConfig
{
public:
    enum EConstDefine 
    {
        EConstDefine_RewardItemMaxSize = 10,    // �����10������
    };
protected:
    RewardProfessionItemConfig() { memset(m_nProfessionItem,0,sizeof(m_nProfessionItem)); };

public:
    inline static RewardProfessionItemConfig& Instance()
    {
        static RewardProfessionItemConfig s_Gift;
        return s_Gift;
    }

    bool LoadRewardProfessionItemConfig(const char* szFile);

    const uint16 * GetRewardProfessionItemList(uint16 nProfession) const
    { 
        if ( nProfession >= EArmType_MaxSize)
        { return NULL; }

        return m_nProfessionItem[nProfession];
    }

private:
    uint16 m_nProfessionItem[EArmType_MaxSize][EConstDefine_RewardItemMaxSize];
};



#endif