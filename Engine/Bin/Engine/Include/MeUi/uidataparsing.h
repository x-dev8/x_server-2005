/*****************************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 		UiDataParsing.h
* Create: 	10/10/08
* Desc:		The class is are used in the syntax parsing in ControlList and ControlText.
* Author:	yanli
*****************************************************************************************/
#pragma once
#include "UiParseData.h"
#include "Singleton.h"
#include <vector>

/*********************************************************************************************
*前置处理函数FunPreProcess：将前后缀之间的str解析出来，存入_strText，同时计算出离_strString首的偏移量_nOff
*后置处理函数FunPostProcess：验证数据正确性\将_strText存入_rfSText中\设置_rfSText的type等
*********************************************************************************************/

//typedefs
typedef bool (*FunTextParse)(const std::wstring& strText, UiCallbackDataBase* pData);
typedef bool (*FunTextNormalParse)(const std::wstring& strText);
typedef void (*FunClick)( ControlObject* pSender, const char* szString, UiCallbackDataBase* pData);

struct ParseFuntion
{
	ParseFuntion(EKeyType type, FunTextParse funTextParse, FunClick funClickCallback,bool bUseData): m_key(type), m_funParse(funTextParse), m_CallbackAfterClicked(funClickCallback),m_bUseData(bUseData) {}

	//members
	EKeyType				m_key;
	FunTextParse		m_funParse;
	FunClick				m_CallbackAfterClicked;
	bool						m_bUseData;
};

class UiDataParsing: public Singleton<UiDataParsing>
{
public:
	UiDataParsing();
	~UiDataParsing();

public:
	bool IsStartNewParse() { return m_bParseTextNew; }
	bool IsCallbackFunEnable() const { return m_bCallbackEnable; }
	void SetCallbackEnable(bool val) { m_bCallbackEnable = val; }

public:
	void RegisterParse(ParseFuntion);
	void BeginParse(size_t nSize, DWORD dwFlag);
	bool Parsing(const std::wstring& strText, UiCallbackDataBase* pUiCallbackDataBase, bool& bUseData);
	void EndParse();

public:
	FunClick GetCallback(EKeyType eType);

public:
	void SetOffset(size_t nOffset) { m_nOffset = nOffset;}
	size_t GetOffset() { return m_nOffset; }
	void SetMin(size_t nMin) { m_nMin = nMin; }
	size_t& GetMin() { return m_nMin; }
	void SetParsingData(UiParseData& xParsingData) { m_xParsingData = xParsingData; }
	UiParseData& GetParsingData() { return m_xParsingData; }
	void SetNormalParse(FunTextNormalParse funNormalParse) { m_funNormalParse = funNormalParse;}

protected:
	std::vector<ParseFuntion> m_vcParser;
	size_t m_nMin;
	DWORD m_dwflag;
	unsigned int m_nOffset;
	bool m_bParseTextNew;	 //开关变量，是否使用新的解析方式
	bool m_bCallbackEnable;	 //开关变量，是否使用注册的callback
	UiParseData m_xParsingData; 
	FunTextNormalParse m_funNormalParse;
};
