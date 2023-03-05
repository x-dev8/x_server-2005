#include "MeUi/UiDataParsing.h"
#include <process.h>

static CRITICAL_SECTION gs_DataParsingCS;

//-----------------------------------------------------------------------------------------------
UiDataParsing::UiDataParsing():
m_nMin(std::wstring::npos),
m_nOffset(0),
m_dwflag(0),
m_bParseTextNew(true),
m_bCallbackEnable(false),
m_funNormalParse(NULL)
{ 
	InitializeCriticalSection( &gs_DataParsingCS );
}

//-----------------------------------------------------------------------------------------------
void UiDataParsing::RegisterParse(ParseFuntion parseFunction)
{
	m_vcParser.push_back(parseFunction);
}

//-----------------------------------------------------------------------------------------------
void UiDataParsing::BeginParse(size_t nSize, DWORD dwFlag)
{
	EnterCriticalSection( &gs_DataParsingCS );
	m_dwflag = dwFlag;
	m_nMin = nSize;
	m_nOffset = 0;
}

//-----------------------------------------------------------------------------------------------
void UiDataParsing::EndParse()
{
	m_dwflag = 0;
	m_nMin = std::wstring::npos;
	m_nOffset = 0;
	LeaveCriticalSection( &gs_DataParsingCS );
}

//-----------------------------------------------------------------------------------------------
bool UiDataParsing::Parsing(const std::wstring& strText, UiCallbackDataBase* pUiCallbackDataBase, bool& bUseData)
{
	for (std::vector<ParseFuntion>::iterator it = m_vcParser.begin(); it != m_vcParser.end(); ++it)
	{
		if (m_dwflag & it->m_key)
		{
			if (it->m_funParse && it->m_funParse(strText, pUiCallbackDataBase))
			{
				bUseData = it->m_bUseData;
				return true;
			}
		}
	}

	if (m_funNormalParse && m_funNormalParse(strText))
	{
		return true;
	}

	return false;	
}

UiDataParsing::~UiDataParsing()
{
	DeleteCriticalSection(&gs_DataParsingCS);
}

FunClick UiDataParsing::GetCallback(EKeyType eType)
{
	if (!m_bCallbackEnable)
	{
		return NULL;
	}

	for (std::vector<ParseFuntion>::iterator it = m_vcParser.begin(); it != m_vcParser.end(); ++it)
	{
		if (it->m_key == eType)
		{
			return it->m_CallbackAfterClicked;
		}
	}

	return NULL;
}