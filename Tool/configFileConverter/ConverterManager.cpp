#include "StdAfx.h"
#include <assert.h>
#include "ConverterManager.h"
#include "IConverter.h"
#include "Logger.h"

CConverterManager::CConverterManager(void)
{
}

CConverterManager::~CConverterManager(void)
{
}

bool CConverterManager::AddFile(const TCHAR *fileName_, const TCHAR *converterName_)
{
	assert(fileName_ != NULL && converterName_ != NULL);

	IConverter *pConverter = FindConverter(converterName_);
	if(NULL == pConverter)
	{
		pConverter = InsertConverter(converterName_);
		if(!pConverter->InitElementInfo())
		{
			Log_outputLine(_T("��ʼ��ת����%sʧ��"), converterName_);
			RemoveConverter(converterName_);
		}
	}

	if(NULL == pConverter)
		return false;

	return pConverter->AddFile(fileName_);
}	

bool CConverterManager::Convert(void)
{
	for(TConverters::iterator it = m_converters.begin(); it != m_converters.end(); ++it)
	{
		IConverter *pConverter = it->second;
		if(pConverter != NULL)
		{
			Log_outputLine(_T("��������ת������%s"), pConverter->GetConverterName().c_str());
			pConverter->Convert();
		}
	}

	Log_outputLine(_T("---------�����ļ�ת������-----------"));

	return true;
}

void CConverterManager::Reset(void)
{
	m_converters.clear();
}

IConverter *CConverterManager::FindConverter(const TCHAR *converterName_)
{
	TConverters::iterator it = m_converters.find(converterName_);
	if(it != m_converters.end())
	{
		return it->second;
	}

	return NULL;
}

IConverter *CConverterManager::InsertConverter(const TCHAR *converterName_)
{
	assert(converterName_ != NULL);

	IConverter *ret = TheConverterFactory.CreateObject(converterName_);
	if(ret != NULL)
	{
		m_converters.insert(TConverters::value_type(converterName_, ret));
	}

	return ret;
}

void CConverterManager::RemoveConverter(const TCHAR *converterName_)
{
	assert(converterName_ != NULL);

	TConverters::iterator it = m_converters.find(converterName_);
	if(it != m_converters.end())
	{
		m_converters.erase(it);
	}
}
