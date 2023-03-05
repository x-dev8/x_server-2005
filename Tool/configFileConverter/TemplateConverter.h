/*------------------------------------------------------------------------
Desc		: 模板文件转换器类。
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
	Desc	: 根据提供的模版文件来读取描述符信息。
	--------------------------------------------------*/
	virtual bool InitElementInfo(const TCHAR *fileName_ = NULL);
};
