
#include <assert.h>
#include "Helper/XinFaHelper.h"

bool IsValidXinFa(const SCharXinFa *pXinFa_)
{
	assert(pXinFa_ != NULL);

	return pXinFa_->nXinFaID != InvalidLogicNumber && pXinFa_->nXinFaLevel != 0;
}

bool IsValidXinFa(const XinFaConfig::STalentXinFa *pXinFa_)
{
	assert(pXinFa_ != NULL);

	return pXinFa_->nId != InvalidLogicNumber && pXinFa_->nLevel != 0;
}

bool IsValidXinFaSkill(const SCharSkill *pSkill_)
{
	assert(pSkill_ != NULL);

	return pSkill_->ustSkillID != InvalidLogicNumber && pSkill_->stSkillLevel != 0;
}

bool IsValidXinFaSkill(const XinFaConfig::SXinFaSkill *pSkill_)
{
	assert(pSkill_ != NULL);

	return pSkill_->nId != InvalidLogicNumber && pSkill_->nLevel != 0;
}

namespace NXinFaHelper
{
	const int baseID = 50000;
	const int maxIndex = 10;
}

int GetXinFaIDByItemIconID(int itemIconID_)
{
	return (itemIconID_ - NXinFaHelper::baseID) / NXinFaHelper::maxIndex; 
}

int GetXinFaImageIndexByItemIconID(int itemIconID_)
{
	return itemIconID_ % NXinFaHelper::maxIndex; 
}

bool IsValidProfession(const XinFaConfig::STalentXinFa *pXinFa_, unsigned char jobID_)
{
	assert(pXinFa_ != NULL);

	//if(jobID_ < pXinFa_->arrayProfessionReq.GetSize() && pXinFa_->arrayProfessionReq[jobID_])	//编译会出错，不知道为什么
	if(jobID_ < EArmType_MaxSize && pXinFa_->arrayProfessionReq[jobID_])
		return true;

	return false;
}

