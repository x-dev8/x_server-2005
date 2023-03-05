#include "ChatCheck.h"
#include "RapidXml/MeRapidXml.h"
#include <algorithm>
#include "FuncPerformanceLog.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"

#include "tstring.h"
using namespace Common;

bool CChatCheck::LoadUndueString(const char* slkname)
{
	MeXmlDocument doc;
	if( !doc.LoadFile( slkname ) )
	{
		assert(false && "CChatCheck.cpp::LoadUndueString 读取文件失败");
		return false;
	}

	std::string szValue;
	MeXmlElement* lpRoot = doc.FirstChildElement("Project")->FirstChildElement("FilterString");
	if(lpRoot)
	{
		MeXmlElement* lpWord = lpRoot->FirstChildElement("String");
		while( lpWord )
		{
			szValue = lpWord->Attribute("Value");
			if( !szValue.empty() )
			{
				/*szValue = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(szValue.c_str()).c_str());*/
				CChatCheck::vecUndueStringList.push_back( Common::_tstring::UTF8towcs(szValue.c_str()).c_str() );					
			}
			lpWord = lpWord->NextSiblingElement("String");
		}
	}
	MeXmlElement* lpForbit = doc.FirstChildElement("Project")->FirstChildElement("DefendString");
	if(lpForbit)
	{
		MeXmlElement* lpWord = lpForbit->FirstChildElement("String");
		while(lpWord)
		{
			szValue = lpWord->Attribute("Value");
			if(!szValue.empty())
			{
				CChatCheck::vecForbitStringList.push_back(Common::_tstring::UTF8towcs(szValue.c_str()).c_str());
			}
			lpWord = lpWord->NextSiblingElement("String");
		}
	}
	return true;
}

bool CChatCheck::LoadSpecialCharFilterString(const char* filename)
{
    MeXmlDocument doc;
    if( !doc.LoadFile( filename ) )
    {
        assert(false && "CChatCheck.cpp::LoadSpecialCharFilterString 读取文件失败");
        return false;
    }

    std::string szValue;
    MeXmlElement* lpRoot = doc.FirstChildElement("Project")->FirstChildElement("FilterString");
    if(lpRoot)
    {
        MeXmlElement* lpWord = lpRoot->FirstChildElement("String");
        while( lpWord )
        {
            szValue = lpWord->Attribute("Value");
            if( !szValue.empty() )
            {
                CChatCheck::vecUndueStringList.push_back( Common::_tstring::toWideString(szValue.c_str()).c_str() );					
            }
            lpWord = lpWord->NextSiblingElement("String");
        }
    }


    return true;
}

bool CChatCheck::CheckStringInLow(const char* szStr)
{
	std::wstring strBuffer = _tstring::toWideString(szStr);
    if (strBuffer.find(L' ') != std::wstring::npos ||
        strBuffer.find(L':') != std::wstring::npos ||
        strBuffer.find(Common::_tstring::toWideString(theXmlString.GetString(eClient_Chat_Begin))) != std::wstring::npos ||
        strBuffer.find(L'{') != std::wstring::npos ||
        strBuffer.find(L'}') != std::wstring::npos ||
        strBuffer.find(L'<') != std::wstring::npos ||
        strBuffer.find(L'>') != std::wstring::npos ||
        strBuffer.find(L'[') != std::wstring::npos ||
        strBuffer.find(L']') != std::wstring::npos ||
        strBuffer.find(L'\n') != std::wstring::npos ||
        strBuffer.find(L'\r') != std::wstring::npos ||
        strBuffer.find(L'\t') != std::wstring::npos ||
        strBuffer.find(L"\\n") != std::wstring::npos ||
        strBuffer.find(L"\\r") != std::wstring::npos ||
        strBuffer.find(L"\\t") != std::wstring::npos ||
        strBuffer.find(L'~') != std::wstring::npos ||
        strBuffer.find(L'!') != std::wstring::npos ||
        strBuffer.find(L'@') != std::wstring::npos ||
        strBuffer.find(L'#') != std::wstring::npos ||
        strBuffer.find(L'$') != std::wstring::npos ||
        strBuffer.find(L'%') != std::wstring::npos ||
        strBuffer.find(L'^') != std::wstring::npos ||
        strBuffer.find(L'&') != std::wstring::npos ||
        strBuffer.find(L'*') != std::wstring::npos ||
        strBuffer.find(L'(') != std::wstring::npos ||
        strBuffer.find(L')') != std::wstring::npos ||
        strBuffer.find(L'"') != std::wstring::npos ||
        strBuffer.find(L'\\') != std::wstring::npos ||
        strBuffer.find(L'/') != std::wstring::npos ||
        strBuffer.find(L'?') != std::wstring::npos ||
        strBuffer.find(L'.') != std::wstring::npos ||
        strBuffer.find(L',') != std::wstring::npos ||
        strBuffer.find(L'_') != std::wstring::npos ||
        strBuffer.find(L'+') != std::wstring::npos ||
        strBuffer.find(L'\'') != std::wstring::npos ||
        strBuffer.find(L'|') != std::wstring::npos)
        return false;

	for( int i = 0; ; i++ )
	{
		if( strBuffer[i] == 0 )
			break;
		if( strBuffer[i] >= L'A' && strBuffer[i] <= L'Z' )
			strBuffer[i] += 32;
	}
	int ipos = 0;
	bool bPass = true;
	for( int i=0; i<vecUndueStringList.size(); ++i)
	{
		if( ipos = strBuffer.find(vecUndueStringList[i].c_str()) != -1 )
		{
		    return false;
		}
	}
	return true;

}

bool CChatCheck::CheckPosationInLow(const std::string& str, int nOff )
{
    int icnt = 0;
    //str[pVec->at(0)] = '*';
    for (int i = 0; i < nOff; i++)
    {
        if ( str[i] < 0 )
        {
            ++icnt;
        }
    }
    if (icnt%2 && icnt)
    {
        //pVec->clear();
        return true;
    }
    return false;
}

bool CChatCheck::CheckPosationInLow(const std::wstring& str, int nOff )
{
    int icnt = 0;
    //str[pVec->at(0)] = '*';
    for (int i = 0; i < nOff; i++)
    {
        if ( str[i] < 0 )
        {
            ++icnt;
        }
    }
    if (icnt%2 && icnt)
    {
        //pVec->clear();
        return true;
    }
    return false;
}

std::string CChatCheck::CheckStringInLowMark(char* szStr,char cMark)
{
	std::wstring strTemp = _tstring::toWideString(szStr);
	std::wstring strBuffer = strTemp;

    //转化为小写
    for( int i = 0; ; i++ )
    {
        if( strBuffer[i] == 0 )
            break;
        if( strBuffer[i] >= L'A' && strBuffer[i] <= L'Z' )
            strBuffer[i] += 32;
    }

    for( int i=0; i<vecUndueStringList.size(); ++i)
    {
        int ipos = 0;
        int bPass = false;
        //do
        //{
        while( (ipos = strBuffer.find(vecUndueStringList[i].c_str(), ipos)) != -1)
        {
            //ipos = strBuffer.find(vecUndueStringList[i].c_str());
            //if( ipos != -1)
            //{
            //std::vector<int> flag;
            //for ( int x = 0; x < vecUndueStringList[i].size(); x++)
            //{
            //	flag.push_back(ipos+x);
            //}
            bPass = CChatCheck::CheckPosationInLow(strBuffer, ipos);
            if (bPass)
            {
                break;
            }

            for( int y = ipos; y < ipos + vecUndueStringList[i].length(); ++y)
            {
                //unsigned int nPos = flag.at(y);
                //if (nPos >= 0 && nPos < strBuffer.length() )
                //{
                strBuffer[y] = cMark;
                //}
            }
            //}
            //if (bPass)
            //{
            //	break;
            //}
            //else{
            //	ipos = 0;
            //}
        }
        //while(strBuffer.find(vecUndueStringList[i].c_str()) != -1);
    }

    for (int x = 0; x < strTemp.size(); x++)		
    {
        if (strTemp[x] > 64)						//保留合法的大小写区别
        {
            if ( (strBuffer[x] - strTemp[x] == 0) || (strBuffer[x] - strTemp[x] == 32) || (strBuffer[x] - strTemp[x] == -32) )
            {
                strBuffer[x] = strTemp[x];
            }
        }
    }

    return _tstring::toNarrowString(strBuffer.c_str());
}

//添加新函数
bool CChatCheck::CheckStringInForbit(const char* pszStr)
{
    std::wstring strBuffer = _tstring::toWideString(pszStr);

    for( int i = 0; i < vecForbitStringList.size(); ++i)
    {
        if(strBuffer.find(vecForbitStringList[i].c_str()) != std::wstring::npos)
        {
            return true;
        }
    }
    return false;
}