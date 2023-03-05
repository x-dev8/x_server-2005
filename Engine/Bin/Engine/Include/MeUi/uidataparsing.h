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
*ǰ�ô�����FunPreProcess����ǰ��׺֮���str��������������_strText��ͬʱ�������_strString�׵�ƫ����_nOff
*���ô�����FunPostProcess����֤������ȷ��\��_strText����_rfSText��\����_rfSText��type��
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
	bool m_bParseTextNew;	 //���ر������Ƿ�ʹ���µĽ�����ʽ
	bool m_bCallbackEnable;	 //���ر������Ƿ�ʹ��ע���callback
	UiParseData m_xParsingData; 
	FunTextNormalParse m_funNormalParse;
};
