#pragma once

#include <tchar.h>
#include <map>

#include "DataDef.h"

class IConverter;

class CConverterManager
{
public:
	CConverterManager(void);
	~CConverterManager(void);

	bool AddFile(const TCHAR *fileName_, const TCHAR *converterName_);
	bool Convert(void);
	void Reset(void);

private:
	IConverter *FindConverter(const TCHAR *converterName_);
	IConverter *InsertConverter(const TCHAR *converterName_);
	void RemoveConverter(const TCHAR *converterName_);

private:
	typedef std::map<TString, IConverter *> TConverters;

private:
	TConverters m_converters;
};
