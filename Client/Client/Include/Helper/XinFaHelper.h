/*----------------------------------------------------------
desc	: 有关心法的一些辅助性接口。
author	: zilong
version	: 1.0
date	: 2011-02-17
revision:
----------------------------------------------------------*/

#pragma once
#include "XinFaConfig.h"

/*-------------------------------------------------------
desc	: 检验心法是否有效。
--------------------------------------------------------*/
bool IsValidXinFa(const SCharXinFa *pXinFa_);
bool IsValidXinFa(const XinFaConfig::STalentXinFa *pXinFa_);

/*--------------------------------------------------------
desc	: 检验心法技能是否有效。
--------------------------------------------------------*/
bool IsValidXinFaSkill(const SCharSkill *pSkill_);
bool IsValidXinFaSkill(const XinFaConfig::SXinFaSkill *pSkill_);

/*--------------------------------------------------------
desc	: 从itemIconID字段得到心法的id。
		  当前的计算公式为: itemIconID = baseID + xinFaID * maxIndex + index,
		  index属于[0, maxIndex);
--------------------------------------------------------*/
int GetXinFaIDByItemIconID(int itemIconID_);
/*--------------------------------------------------------
desc	: 从itemIconID字段得到心法的对应的icon在imageList控件中的位置序号。
--------------------------------------------------------*/
int GetXinFaImageIndexByItemIconID(int itemIconID_);

/*-------------------------------------------------------
desc	: 检验是否是该心法要求的职业
--------------------------------------------------------*/
bool IsValidProfession(const XinFaConfig::STalentXinFa *pXinFa_, unsigned char jobID_);