#include "UiParseFunction.h"
#include "MeUi/UiDataParsing.h"
#include "MeUi/ExpressionManager.h"
#include "GameMain.h"
#include "color_config.h"
#include "ItemDetail.h"
#include "PlayerMgr.h"
#include "Ui/Task.h"
#include "Ui/Task_Track.h"
#include "Ui/EspecialTask.h"
#include "Ui/EspecialTask2.h"
#include "Ui/CommonChatFrame.h"
#include "Ui/SkillProduce.h"
#include "Ui/ActivityList.h"
#include "Ui/ChatInfoBox.h"
#include "NpcInfo.h"
#include "InfoList.h"
#include "ExitTip.h"
#include "CountryFunction.h"
#include "TextHyberOtherConfig.h"
extern CHeroGame theHeroGame;
bool g_bVipDisplay = false;


//----------------------------------------------------------------------------------------------------------------------------------------------------------
inline void UpdataMin(size_t nMin)
{
	size_t nLastMin = UiDataParsing::Instance()->GetMin();
	UiDataParsing::Instance()->SetMin(nLastMin > nMin? nMin : nLastMin);
}

inline void UpdataOffsetAndMin(const std::wstring& strText, size_t nOffset)
{
	UiDataParsing::Instance()->SetOffset(nOffset);
	UiDataParsing::Instance()->SetMin(strText.size());
}

bool PreParse(const std::wstring& strInput, const WCHAR* szPreFix, const WCHAR* szPostFix, unsigned int& nOffset, size_t& nMin, std::wstring& strOutput)
{
	size_t nPreFixLen = wcslen(szPreFix);
	size_t nPostFixLen = wcslen(szPostFix);

	//前缀不存在，直接返回
	size_t nStart = strInput.find(szPreFix, nOffset);
	if (std::wstring::npos == nStart)
	{
		return false;
	}

	size_t nEnd = strInput.find(szPostFix, nOffset + nPreFixLen);
	if (std::wstring::npos == nEnd)
	{
		return false;
	}

	if (nStart != nOffset)
	{
		UpdataMin(nStart);
		return false;
	}

	size_t nTextLength = nEnd - (nOffset + nPreFixLen); 

	if (!nTextLength)
	{
		return false;
	}

	strOutput = strInput.substr(nOffset + nPreFixLen, nTextLength);
	nOffset = nEnd + nPostFixLen;
	return true;
}

bool PostParseVipPlayer(const std::wstring& strText)
{
	Common::_tstring strPlayerName = Common::_tstring::toNarrowString(strText.c_str());
	if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->IsVipPlayer(strPlayerName.c_str()) )
	{
		UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
		char szVipName[256] = {0};
		sprintf_s(szVipName, 256, "%s(VIP)", strPlayerName.c_str());
		xParseData.m_str = Common::_tstring::toWideString(szVipName);
		xParseData.m_col = Color_Config.getColor(CC_CHAT_VIP_PLAYERNAME);
	}

	return true;
}

namespace MeSyntaxParser
{
	//------------------------------------------------------------------------------------------------normal
	bool PreParseNormal(const std::wstring& strText, size_t& nOffset, size_t nMin, std::wstring& strOutput)
	{
		if (nMin <= nOffset)
		{
			return false;
		}

		if (nMin == std::wstring::npos)
		{
			strOutput = strText.substr(nOffset);
			nOffset = strText.length();
		}
		else
		{
			strOutput = strText.substr(nOffset, nMin - nOffset);
			nOffset = nMin;
		}

		return true;
	}

	bool PostParseNormal(std::wstring& strText)
	{
		UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
		xParseData.m_str = strText;
		xParseData.m_type = eKeyNormal;
		return true;
	}

	bool NormalParse(const std::wstring& strText)
	{
		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParseNormal(strText, nOffset, nMin, strOutput) && PostParseNormal(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}
		else
		{
			return false;
		}
	}

	//ParseColor---------------------------------------------------------------------------------
	bool PostParseColor(std::wstring& strText)
	{	
		size_t nColBeginDefLen = wcslen(L"ffffffff=");
		if (strText.at(nColBeginDefLen - 1) != L'=')
		{
			return false;
		}

		DWORD dwColor = 0;
		swscanf_s(&strText[0], L"%x=", &dwColor);
		UiParseData& xOutData = UiDataParsing::Instance()->GetParsingData();
		xOutData.m_col = dwColor;
		xOutData.m_str = strText.substr(nColBeginDefLen, strText.length() - nColBeginDefLen);
		xOutData.m_type = eKeyColor;
		return true;
	}

	bool ParseColor(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		if (nOffset > strText.size())
		{
			return false;
		}

		const WCHAR* szPrefix = L"{#";
		const WCHAR* szPostfix = L"#}";
		
		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseColor(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}
		else
		{
			return false;
		}
	}

	//ParseItem-------------------------------------------------------------------------------------
	bool PostParseItem(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		UiParseData& xOutData = UiDataParsing::Instance()->GetParsingData();
		xOutData.m_type = eKeyItem;
		xOutData.m_str = L"[" + strText + L"]";

		if (!pData)
		{
			return true;
		}

		switch( pData->GetType() )
		{
		case eMore_UI_Callback:
			{
				CUI_ID_FRAME_ExitTip::ChangeCol(pData->GetData(), &xOutData.m_col);
				xOutData.m_str = strText;
			}			
			break;
		case eItem_UI_Callback:
		case eMount_UI_Callback:
			{
				void* pCallBackData = pData->GetData();
				if (!pCallBackData)
				{
					return true;
				}

				SCharItem stItem;
				memcpy_s(&stItem, sizeof(stItem), pCallBackData, sizeof(stItem));
				ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
				if(pItemCommon)
				{
					Common::_tstring tstrName(pItemCommon->GetItemName());					
					S_IconInfoHero::ReplaceSpecifiedName(pItemCommon->ustLevel, tstrName);
					xOutData.m_str = L"[";
					xOutData.m_str += Common::_tstring::toWideString(tstrName.c_str());
					xOutData.m_str += L"]";
					xOutData.m_col = S_IconInfoHero::GetQualityColor(pItemCommon->ustLevel);			
				}
			}
			break;	
		}

		return true;
	}

	bool ParseItem(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"[";
		const WCHAR* szPostfix = L"]";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseItem(strOutput, pData))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}
		
		return false;
	}

	//ParseHyper-------------------------------------------------------------------------------------
	void PostParseHyper(const std::wstring& strText)
	{
		UiParseData& xOutData = UiDataParsing::Instance()->GetParsingData();
		xOutData.m_type = eKeyHyper;
		xOutData.m_str = strText;
		xOutData.m_col = Color_Config.getColor((ColorConfigure)(CC_MapName));
	}

	bool ParseHyper(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"$";
		const WCHAR* szPostfix = L"$";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput))
		{
			PostParseHyper(strOutput);
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;
	}

	//ParseImg-------------------------------------------------------------------------------------
	bool PostParseImg(std::wstring& strText)
	{
		char szText[64] = {0};
		WideCharToMultiByte(CP_ACP, 0, strText.c_str(), -1, szText, sizeof(strText) - 1, NULL, NULL);
		ExpressionManager::ExpressionData* pInfo = ExpressionManager::GetInstance().GetExpressionInfo(szText);
		if (pInfo)
		{
			if (pInfo->GetTextureId() == -1)
			{
				return false;
			}

			UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
			xParseData.m_type = eKeyImg;
			xParseData.m_rc.right = pInfo->m_nWidth * ControlObject::GetSCALE(0);
			xParseData.m_rc.left = 0;
			xParseData.m_rc.bottom = pInfo->m_nHeight * ControlObject::GetSCALE(0);
			xParseData.m_rc.top = 0;
			xParseData.m_pInfo = (void*)pInfo;
			xParseData.m_nTextureID = pInfo->GetTextureId();
			return true;
		}

		return false;
	}

	bool ParseImg(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"{";
		const WCHAR* szPostfix = L"}";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseImg(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;
	}

	//ParseChatExp-------------------------------------------------------------------------------------
	bool PostParseChatExp(std::wstring& strText)
	{
		char szText[64] = {0};
		WideCharToMultiByte(CP_ACP, 0, strText.c_str(), -1, szText, sizeof(strText) - 1, NULL, NULL);
		ExpressionManager::ExpressionData* pInfo = ExpressionManager::GetInstance().GetExpressionInfo(szText, true);
		if (pInfo)
		{
			if (pInfo->GetTextureId() == -1)
			{
				return false;
			}

			UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
			xParseData.m_type = eKeyChatExp;
			xParseData.m_rc.right = pInfo->m_nWidth * ControlObject::GetSCALE(0);
			xParseData.m_rc.left = 0;
			xParseData.m_rc.bottom = pInfo->m_nHeight * ControlObject::GetSCALE(0);
			xParseData.m_rc.top = 0;
			xParseData.m_pInfo = (void*)pInfo;
			xParseData.m_nTextureID = pInfo->GetTextureId();
			return true;
		}

		return false;
	}

	bool ParseChatExp(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"{";
		const WCHAR* szPostfix = L"}";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseChatExp(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;
	}

	//ParseAddress-------------------------------------------------------------------------------------
	bool PostParseAddress(const std::wstring& strText)
	{
		size_t nLeftBracket = strText.find(L'(');
		size_t nCommaPos =  strText.find(L',');
		size_t nRightBracket = strText.find(L')');

		if (wstring::npos == nLeftBracket || wstring::npos == nRightBracket || wstring::npos == nCommaPos)
		{
			return false;
		}

		size_t nLeftLength = nCommaPos - nLeftBracket;
		size_t nRightLength = nRightBracket - nCommaPos;
		if (nLeftLength <= 1 || nRightLength <= 1)
		{
			return false;
		}

		for (int i = nLeftBracket + 1; i < nRightBracket; ++i)
		{
			if (i != nCommaPos)
			{
				if (strText.c_str()[i] < L'0' || strText.c_str()[i] > L'9')
				{
					return false;
				}
			}
		}

		UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
		xParseData.m_type = eKeyAddress;
		xParseData.m_str = strText;
		xParseData.m_col = Color_Config.getColor((ColorConfigure)(CC_PathFindLinker));

		return true;
	}

	bool ParseAddress(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"<";
		const WCHAR* szPostfix = L">";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseAddress(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;
	}

	//ParseNpc-------------------------------------------------------------------------------------
	bool PostParseNpc(const std::wstring& strText)
	{
		size_t nLeftBracket = strText.find(L'(');
		size_t nCommaPos =  strText.find(L',');
		size_t nRightBracket = strText.find(L')');

		if (wstring::npos != nLeftBracket || wstring::npos != nRightBracket || wstring::npos != nCommaPos)
		{
			return false;
		}

		UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
		xParseData.m_type = eKeyNpc;
		xParseData.m_str = strText;
		xParseData.m_col = Color_Config.getColor((ColorConfigure)(CC_PathFindLinker));
		return true;
	}

	bool ParseNpc(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"<";
		const WCHAR* szPostfix = L">";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParseNpc(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;	
	}

	//ParsePlayer-------------------------------------------------------------------------------------
	bool PostParsePlayer(const std::wstring& strText)
	{
		if (g_bVipDisplay)
		{
			return PostParseVipPlayer(strText);
		}

		UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
		xParseData.m_type = eKeyPlayer;
		xParseData.m_str = strText;
		xParseData.m_col = ControlList::s_CHAT_PLAYERNAME_COLOR;
		return true;
	}

	bool ParsePlayer(const std::wstring& strText, UiCallbackDataBase* pData)
	{
		const WCHAR* szPrefix = L"~";
		const WCHAR* szPostfix = L"_";

		size_t nOffset = UiDataParsing::Instance()->GetOffset();
		size_t& nMin = UiDataParsing::Instance()->GetMin();

		std::wstring strOutput;
		if (PreParse(strText, szPrefix, szPostfix, nOffset, nMin, strOutput) && PostParsePlayer(strOutput))
		{
			UpdataOffsetAndMin(strText, nOffset);
			return true;
		}

		return false;	
	}

    // Parse Country ---------------------------------------------------------------------------------------
    bool PostParseCountry( std::wstring& strText )
    {
        char szText[ MAX_PATH ] = { 0 };
        WideCharToMultiByte( CP_ACP, 0, strText.c_str(), -1, szText, sizeof( strText ) - 1, NULL, NULL );
        int nCountryId = atoi( szText );
        char szCountryId[ MAX_PATH ] = { 0 };
        MeSprintf_s( szCountryId, sizeof( szCountryId ) / sizeof( char ) - 1, "%d", nCountryId );
        if( std::string( szText ) != std::string( szCountryId ) )
        {
            return false;
        }
        std::string strCountry = CountryFunction::GetCountryNameById( nCountryId );
        if( strCountry.empty() )
        {
            return false;
        }

        UiParseData& xParseData = UiDataParsing::Instance()->GetParsingData();
        Common::_tstring strTmp = strCountry;
        xParseData.m_str = strTmp.toWideString();

        return true;
    }

    bool ParseCountry( const std::wstring& strText, UiCallbackDataBase* pData )
    {
        const WCHAR* szPrefix = L"&!";
        const WCHAR* szPostfix = L"!&";

        size_t nOffset = UiDataParsing::Instance()->GetOffset();
        size_t& nMin = UiDataParsing::Instance()->GetMin();

        std::wstring strOutput;
        if( PreParse( strText, szPrefix, szPostfix, nOffset, nMin, strOutput ) && PostParseCountry( strOutput ) )
        {
            UpdataOffsetAndMin( strText, nOffset );
            return true;
        }

        return false;
    }


	//---------------------------------------------------------------------------------------------------------------------------
	void PlayerCallback( ControlObject* pSender, const char* szString, UiCallbackDataBase* pData )
	{
		CUI_ChatInfoBox::HyberClickPrivateChat(pSender,szString);
	}

	void NpcCallback( ControlObject* pSender, const char* szString, UiCallbackDataBase* pData )
	{
		if( szString )
		{
			int UID = TextHyberOtherConfig::Instance().GetUIID(szString);
			if(UID != 0)
			{
				MsgOpenUI msg;
				msg.UIFlag = UID;
				theHeroGame.GetPlayerMgr()->OnOpenUI(&msg);
			}
			else if (pData  && pData->GetType() == eExipTip_UI_Callback )
			{
				const char* npcName = (const char*)pData->GetData();
				if ( npcName )
				{
					NpcCoord::getInstance()->clickHyberToMiniMap( npcName );
				}
				else
				{
					NpcCoord::getInstance()->clickHyberToMiniMapForText(szString,(UiCallbackDataBase*)pData);
				}
			}
			else
			{
				NpcCoord::getInstance()->clickHyberToMiniMapForText(szString,(UiCallbackDataBase*)pData);
			}
		}

	}

	void AddressCallback( ControlObject* pSender, const char* szString, UiCallbackDataBase* pData )
	{
		int nTemp = 0;
		if (pData)
		{
			nTemp = *(int*)pData;
		}
        if (pSender && pSender->GetFrameFather() )
        {
            if(pSender->GetFrameFather() == s_CUI_ID_FRAME_InfoList.GetFrame())
            {
                s_CUI_ID_FRAME_InfoList.Task_HyberOtherClick( pSender,szString );
				return;
            }
        }
		CommonChatFrame::Task_HyberOtherClick(pSender,szString,nTemp);
	}

	void ItemCallback( ControlObject* pSender, const char* szString, UiCallbackDataBase* pData )
	{
		if (pData )
		{//水浒的聊天框
			switch( pData->GetType() )
			{
			case eMore_UI_Callback:
				CUI_ID_FRAME_ExitTip::ClickMore( pData->GetData() );
				break;
			case eItem_UI_Callback:
				CommonChatFrame::HyberItemClick(pSender,(unsigned char*)pData->GetData());
				break;
			case eMount_UI_Callback:
				CommonChatFrame::HyberMountClick(pSender,pData);
				break;
			case eSkill_UI_Callback:
				CommonChatFrame::HyberSkillClick( pSender,pData );
				break;
			case eTask_UI_Callback:
				CommonChatFrame::HyberTaskClick( pSender, (unsigned char*)pData);
				break;
			case ePet_UI_Callback:
				CommonChatFrame::HyberPetClick( pSender, pData );
				break;
			}			
		}
	}
}

void SetAllParseFuntion()
{
	UiDataParsing::Instance()->SetCallbackEnable(true);//武神关闭，水浒打开
	UiDataParsing::Instance()->SetNormalParse(MeSyntaxParser::NormalParse);
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyImg, MeSyntaxParser::ParseImg, NULL, false));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyColor, MeSyntaxParser::ParseColor, NULL, false));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyItem, MeSyntaxParser::ParseItem, MeSyntaxParser::ItemCallback, true));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyAddress, MeSyntaxParser::ParseAddress, MeSyntaxParser::AddressCallback, false));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyNpc, MeSyntaxParser::ParseNpc, MeSyntaxParser::NpcCallback, true));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyPlayer, MeSyntaxParser::ParsePlayer, MeSyntaxParser::PlayerCallback, false));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyHyper, MeSyntaxParser::ParseHyper, NULL, false));
	UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyChatExp, MeSyntaxParser::ParseChatExp, NULL, false));
    UiDataParsing::Instance()->RegisterParse(ParseFuntion(eKeyCountry, MeSyntaxParser::ParseCountry, NULL, false));
}