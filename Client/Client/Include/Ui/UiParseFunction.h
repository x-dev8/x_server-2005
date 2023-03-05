/*****************************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 		UiParseFunction.h
* Create: 	10/10/08
* Author:	yanli
*****************************************************************************************/
#pragma once
#include <string>
struct UiCallbackDataBase;

namespace MeSyntaxParser
{
	// {#X#}
	bool ParseColor(const std::wstring& strText, UiCallbackDataBase* pData);
	// [X]
	bool ParseItem(const std::wstring& strText, UiCallbackDataBase* pData);
	// {X}
	bool ParseImg(const std::wstring& strText, UiCallbackDataBase* pData);	
	// {X}
	bool ParseChatExp(const std::wstring& strText, UiCallbackDataBase* pData);	
	// <X>
	bool ParseAddress(const std::wstring& strText, UiCallbackDataBase* pData);
	// <X>
	bool ParseNpc(const std::wstring& strText, UiCallbackDataBase* pData);
	// $X$
	bool ParseHyper(const std::wstring& strText, UiCallbackDataBase* pData);
	// ~X_
	bool ParsePlayer(const std::wstring& strText, UiCallbackDataBase* pData);
	// &!X!&
	bool ParseCountry( const std::wstring& strText, UiCallbackDataBase* pData );
}

void SetAllParseFuntion();