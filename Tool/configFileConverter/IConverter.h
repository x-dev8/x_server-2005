/*------------------------------------------------------------------------
Desc		: 文件转换器接口类。
Author		: zilong
Version		: 1.0
Date		: 2011-03-08
Revision	:
-------------------------------------------------------------------------*/

#pragma once

#include "DataDef.h"
#include <tchar.h>
#include <list>

#include "MeRapidXml.h"
#include "ConverterFactory.h"

struct SXmlPropertyInfo
{
	TString name;

	SXmlPropertyInfo(const TString &name_):
	name(name_)
	{

	}

	~SXmlPropertyInfo()
	{

	}
};

struct SXmlPropertyValue
{
	TString value;

	SXmlPropertyValue(const TString &value_):
	value(value_)
	{

	}

	~SXmlPropertyValue()
	{

	}
};

struct SXmlElementInfo
{
	typedef std::list<SXmlPropertyInfo> TProperties;

	TString name;
	TProperties properties;
	SXmlElementInfo *pSibling;
	SXmlElementInfo *pChild;	//指向第一个子节点

	SXmlElementInfo():
	pSibling(NULL),
	pChild(NULL)
	{

	}

	~SXmlElementInfo()
	{
		Reset();
	}

	void Reset(void)
	{
		name.clear();
		properties.clear();

		if(pChild != NULL)
		{
			delete pChild;
			pChild = NULL;
		}

		if(pSibling != NULL)
		{
			delete pSibling;
			pSibling = NULL;
		}
	}
};

struct SXmlElementValue
{
	typedef std::list<SXmlPropertyValue> TProperties;

	TProperties properties;
	SXmlElementValue *pSibling;
	SXmlElementValue *pChild;

	SXmlElementValue():
	pSibling(NULL),
	pChild(NULL)
	{

	}

	~SXmlElementValue()
	{
		Reset();
	}

	void Reset(void)
	{
		properties.clear();

		if(pChild != NULL)
		{
			delete pChild;
			pChild = NULL;
		}

		if(pSibling != NULL)
		{
			delete pSibling;
			pSibling = NULL;
		}
	}
};

typedef std::list<SXmlElementValue *> TXmlElementValues;

class IConverter
{
public:
	IConverter(void);
	virtual ~IConverter(void);

	/*------------------------------------------------------
	Desc	: 初始化描述符信息。后面的转换过程要依赖这个描述符。
	------------------------------------------------------*/
	virtual bool InitElementInfo(const TCHAR *fileName_ = NULL) = 0;

	void Convert(void);
	bool AddFile(const TCHAR *fileName_);
	const TString &GetConverterName(void){return m_converterName;}

protected:
	virtual bool Convert(const TString &fileName_);
	virtual bool LoadFile(const TString &fileName_, TXmlElementValues &_elementValues);
	virtual bool LoadSlkFile(const TString &fileName_, TXmlElementValues &_elementValues) { return true; }
	virtual bool LoadXinFile(const TString &fileName_,TXmlElementValues &_elementValues)  {return true;  }
	virtual bool SaveFile(const TString &fileName_, const TXmlElementValues &elementValues_);
	virtual bool WriteHead(MeXmlDocument &_doc_, MeXmlElement *&_pElem);
	virtual bool GetResultFileName(const TString &fileName_, TString &_resultFileName);
	virtual bool GetStringFileName(const TString &fileName_, TString &_resultFileName);

protected:
	TString m_converterName;	//转换器的名字，没有特殊意义。

private:
	typedef std::list<TString> TFileNames;
protected:
	SXmlElementInfo m_xmlHeadInfo;		
	SXmlElementInfo m_xmlInfo;
	TFileNames m_fileNames; 
};

#define TheConverterFactory CObjectFactory<IConverter>::GetInstance()
