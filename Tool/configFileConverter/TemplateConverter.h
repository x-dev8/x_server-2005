/*------------------------------------------------------------------------
Desc		: ģ���ļ�ת�����ࡣ
Author		: zilong
Version		: 1.0
Date		: 2011-03-08
Revision	:
-------------------------------------------------------------------------*/

#pragma once
#include "iconverter.h"

class CTemplateConverter: public IConverter
{
public:
	CTemplateConverter(void);
	virtual ~CTemplateConverter(void);

	/*--------------------------------------------------
	Desc	: �����ṩ��ģ���ļ�����ȡ��������Ϣ��
	--------------------------------------------------*/
	virtual bool InitElementInfo(const TCHAR *fileName_ = NULL);
};
