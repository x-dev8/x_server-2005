#include "StdAfx.h"
#include "ItemHero.h"
#include "IConverter.h"
#include "SlkReader.h"
#include "stringUtility.h"
#include "Logger.h"
#include "tstring.h"


/*------------------------------------------------------
In	: pElem_， 父节点
------------------------------------------------------*/
bool WriteFile(MeXmlElement *_pElem_, const SXmlElementInfo &info_, const SXmlElementValue &value_)
{
	assert(_pElem_ != NULL);
	if(NULL == _pElem_)
		return false;

	//插入自身节点
	MeXmlElement* pMyElem = _pElem_->InsertEndChild(info_.name.c_str())->ToElement();
	if(NULL == pMyElem)
	{
		return false;
	}

	//保存自身属性信息
	{
		SXmlElementInfo::TProperties::const_iterator itInfo = info_.properties.begin();
		SXmlElementValue::TProperties::const_iterator itValue = value_.properties.begin();

		for(; itInfo != info_.properties.end() && itValue != value_.properties.end(); ++itInfo, ++itValue)
		{
			if(itInfo->name.empty())
			{
				return false;
			}

#ifdef _UNICODE
			std::wstring &strValue = itValue->value;
#else
			std::wstring strValue = Common::_tstring::toWideString(itValue->value.c_str());
#endif
			
			pMyElem->SetAttribute(itInfo->name.c_str(), Common::_tstring::wcstoUTF8(strValue.c_str()).c_str());
		}

		if(itInfo != info_.properties.end() || itValue != value_.properties.end())
			return false;
	}


	//保存child节点信息
	if(value_.pChild != NULL)
	{
		if(info_.pChild != NULL)
		{
			if(!WriteFile(pMyElem, *info_.pChild, *value_.pChild))
				return false;
		}
		else
		{
			return false;
		}
	}

	//保存sibling节点信息
	if(value_.pSibling != NULL)
	{
		if(info_.pSibling != NULL)
		{
			if(!WriteFile(_pElem_, *info_.pSibling, *value_.pSibling))
				return false;
		}
		else
		{
			return false;
		}
	}

	return true;
}

IConverter::IConverter(void)
{
}

IConverter::~IConverter(void)
{
}

void IConverter::Convert(void)
{
	for(TFileNames::const_iterator it = m_fileNames.begin(); it != m_fileNames.end(); ++it)
	{
		Log_outputLine(_T("开始转换文件%s........"), it->c_str());
		if(!Convert(*it))
		{
			Log_outputLine(_T("转换文件%s失败！"), it->c_str());
		}
		else
		{
			Log_outputLine(_T("转换文件%s完成！"), it->c_str());
		}
	}
}

bool IConverter::AddFile(const TCHAR *fileName_)
{
	m_fileNames.push_back(fileName_);

	return true;
}




bool IConverter::Convert(const TString &fileName_)
{

	TString CharacterBaseSecondAttributepath = _T("CharacterBaseSecondAttribute.slk");
	TXmlElementValues element;
	if (fileName_ == CharacterBaseSecondAttributepath)
	{
		if(!LoadSlkFile(fileName_, element))
		{//如果是单节点，就把这行注视掉
			return false;
		}
		return true;//如果是单节点，就把这行注视掉
	}

	TString resultFileName1;
	TString resultFileName2;
	TString HeroPath = _T("SanGuoLord.slk");
	if (fileName_ == HeroPath)
	{


		if (!theItemHero.LoadHeroItemSlk(fileName_.c_str()))
		{
			return false;
		}
		
		if(!GetResultFileName(fileName_, resultFileName1))
			return false;
		if (!GetStringFileName(fileName_,resultFileName2))
		{
			return false;
		}

		if (!theItemHero.SaveHeroConfig(resultFileName1.c_str(),resultFileName2.c_str()))
		{
			return false;
		}


		if (!theItemHero.LoadHeroConfig(resultFileName1.c_str(),resultFileName2.c_str()))
		{
			return false;
		}
		
		return true;
	}


	TString XinFaPath = _T("XinFa.slk");
	if (fileName_ == XinFaPath)
	{
		if (!LoadXinFile(fileName_,element))
		{
			return false;
		}

		return true;
	}
		
	if (!LoadFile(fileName_, element)) //单节点 就恢复下面注释掉的内容。
		return false;

	
	TString resultFileName;
	if(!GetResultFileName(fileName_, resultFileName))
		return false;

	if(!SaveFile(resultFileName, element))
		return false;

	for(TXmlElementValues::iterator it = element.begin(); it != element.end(); ++it)
	{
		if(*it)
		{
			delete *it;
		}
	}
	element.clear();
	

	return true;
}

bool IConverter::LoadFile(const TString &fileName_, TXmlElementValues &_elementValues)
{
	return false;
}

bool IConverter::SaveFile(const TString &fileName_, const TXmlElementValues &elementValues_)
{
	MeXmlDocument doc;
	
	//写头部信息
	MeXmlElement *pElem = NULL;
	if(!WriteHead(doc, pElem))
	{
		return false;
	}

	//写本体信息
	if(pElem != NULL)
	{
		for(TXmlElementValues::const_iterator it = elementValues_.begin(); it != elementValues_.end(); ++it)
		{
			if(NULL == *it || !WriteFile(pElem, m_xmlInfo, **it))
				return false;
		}
	}
	else
	{//无头部信息

// 		SXmlElementInfo *pElemInfo = &m_xmlInfo;
// 		const SXmlElementValue *pElemValue = &elementValue_;
// 		//插入自身节点
// 		MeXmlElement *pRootElem = doc.InsertEndChild(pElemInfo->name.c_str())->ToElement();
// 		if(NULL == pRootElem)
// 		{
// 			return false;
// 		}
// 
// 		//保存自身属性信息
// 		{
// 			SXmlElementInfo::TProperties::const_iterator itInfo = pElemInfo->properties.begin();
// 			SXmlElementValue::TProperties::const_iterator itValue = pElemValue->properties.begin();
// 
// 			for(; itInfo != pElemInfo->properties.end() && itValue != pElemValue->properties.end(); ++itInfo, ++itValue);
// 			{
// 				if(itInfo->name.empty())
// 				{
// 					return false;
// 				}
// 
// 				pRootElem->SetAttribute(itInfo->name.c_str(), itValue->value.c_str());
// 			}
// 
// 			if(itInfo != pElemInfo->properties.end() || itValue != pElemValue->properties.end())
// 				return false;
// 		}
// 
// 		//保存child节点信息
// 		if(pElemInfo->pChild != NULL)
// 		{
// 			if(!WriteFile(pRootElem, *pElemInfo->pChild, *elementValue_.pChild))
// 				return false;
// 		}
// 
// 		//保存sibling节点信息
// 		//根节点不应该有sibling
// 		if(pElemInfo->pSibling != NULL)
// 		{
// 			assert(false);
// 
// 			return false;
// 		}

		return false;
	}

	std::string name = ToAnsi(fileName_);
	return doc.SaveFile(name.c_str());
}

bool IConverter::WriteHead(MeXmlDocument &_doc_, MeXmlElement *&_pElem)
{
	_doc_.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

	if(!m_xmlHeadInfo.name.empty())
	{
		//插入自身节点
		MeXmlElement *pRootElem = _doc_.InsertEndChild(m_xmlHeadInfo.name.c_str())->ToElement();
		if(NULL == pRootElem)
		{
			return false;
		}

		SXmlElementInfo *pMe = m_xmlHeadInfo.pChild;
		MeXmlElement *pFatherElem = pRootElem;
		MeXmlElement *pMeElem = NULL;
		while(pMe != NULL)
		{
			if(pMe->name.empty())
				return false;

			pMeElem = pFatherElem->InsertEndChild(pMe->name.c_str())->ToElement();
			if(NULL == pMeElem)
				return false;

			pMe = pMe->pChild;
			pFatherElem = pMeElem;
		}

		_pElem = pMeElem;
	}

	return true;
}

 bool IConverter::GetResultFileName(const TString &fileName_, TString &_resultFileName)
 {
	const TCHAR ext[] = _T("slk");
	const TCHAR resultExt[] = _T("config");

	TString::size_type pos = fileName_.rfind(ext);
	if(pos == TString::npos)
		return false;

	_resultFileName.assign(fileName_, 0, pos);
	_resultFileName += resultExt;

	return true;
 }

 bool IConverter::GetStringFileName(const TString &fileName_, TString &_resultFileName)
 {
	const TCHAR ext[] = _T("slk");
	const TCHAR resultExt[] = _T("string");

	TString::size_type pos = fileName_.rfind(ext);
	if (pos == TString::npos)
	{
		return false;
	}

	_resultFileName.assign(fileName_,0,pos);
	_resultFileName += resultExt;

	return true;

 }