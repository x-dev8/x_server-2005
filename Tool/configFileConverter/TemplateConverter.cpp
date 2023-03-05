#include "StdAfx.h"
#include "TemplateConverter.h"
#include "MeRapidXml.h"

CTemplateConverter::CTemplateConverter(void)
{
	m_converterName = _T("template converter");
}

CTemplateConverter::~CTemplateConverter(void)
{
}

bool CTemplateConverter::InitElementInfo(const TCHAR *fileName_ /*= NULL*/)
{

	return true;
}

//----------------------
namespace 
{
	IConverter *CreateTemplateConverter(void)
	{
		return new CTemplateConverter;
	}

	const bool ret_TemplateConverter = TheConverterFactory.Register(_T("templateConverter"), CreateTemplateConverter);
}

