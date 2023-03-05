/*----------------------------------------------------------
desc	: �й��ķ���һЩ�����Խӿڡ�
author	: zilong
version	: 1.0
date	: 2011-02-17
revision:
----------------------------------------------------------*/

#pragma once
#include "XinFaConfig.h"

/*-------------------------------------------------------
desc	: �����ķ��Ƿ���Ч��
--------------------------------------------------------*/
bool IsValidXinFa(const SCharXinFa *pXinFa_);
bool IsValidXinFa(const XinFaConfig::STalentXinFa *pXinFa_);

/*--------------------------------------------------------
desc	: �����ķ������Ƿ���Ч��
--------------------------------------------------------*/
bool IsValidXinFaSkill(const SCharSkill *pSkill_);
bool IsValidXinFaSkill(const XinFaConfig::SXinFaSkill *pSkill_);

/*--------------------------------------------------------
desc	: ��itemIconID�ֶεõ��ķ���id��
		  ��ǰ�ļ��㹫ʽΪ: itemIconID = baseID + xinFaID * maxIndex + index,
		  index����[0, maxIndex);
--------------------------------------------------------*/
int GetXinFaIDByItemIconID(int itemIconID_);
/*--------------------------------------------------------
desc	: ��itemIconID�ֶεõ��ķ��Ķ�Ӧ��icon��imageList�ؼ��е�λ����š�
--------------------------------------------------------*/
int GetXinFaImageIndexByItemIconID(int itemIconID_);

/*-------------------------------------------------------
desc	: �����Ƿ��Ǹ��ķ�Ҫ���ְҵ
--------------------------------------------------------*/
bool IsValidProfession(const XinFaConfig::STalentXinFa *pXinFa_, unsigned char jobID_);