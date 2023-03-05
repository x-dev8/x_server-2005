#include "MeUi/ControlEdit.h"
//#include <assert.h>
#include "FuncPerformanceLog.h"
//#include "MeUi/UiManager.h"
#include "Me3d/BaseGraphics.h"
//#include "../../client/client/Common.h"
//#include "../../client/client/Include/shortcutkey_configure.h"
#include "tstring.h"
#include "MeFont/MeFontSystem.h"  //##
#include "MeUi/ControlFrame.h"
//
#define MAX_CHAR_COUNT 300

#pragma comment(lib,"Usp10.lib")

ControlEdit::ControlEdit(void)
{
	m_dwFlashBar = 0;
	m_bDrawFlashBar = false;
	m_nStartIndex= 0;
	m_nCurIndex = 0;
	m_pCurLineData = 0;
	m_pOnEnter = NULL;
	_funOnTab = NULL;
	_funOnLBtnDown = NULL;
	_funOnLBtnUp = NULL;
	_funOnDelByte = NULL;
	_funOnTextChanged = NULL;
	m_nMaxLength = MAX_CHAR_COUNT;
	m_dwDefaultColor = 0;

	_luaTableName.clear();
	_funOnEnterName.clear();
	_funOnTabName.clear();
	_funOnLBtnDownName.clear();
	_funOnLBtnUpName.clear();
	_funDelByteName.clear();

	m_bSelectAllAfterTab = false;

	m_bRightAlign = false;
	m_bForceNewLine = true;
	SetNumberLimit(false, 0, 0);
	SetOnVisibleChangedFun(editVisibleChange);
	m_nSyntaxFlag = 0x0;
	m_bEnableSelected = true;
	m_bHyberLimit = false;
}

ControlEdit::~ControlEdit(void)
{
}

// 初始化UI
void ControlEdit::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlText::InitUIData( pFather, pData );

	S_EditData* pEditData = (S_EditData*)pData;
	m_dwDrawFlags = DT_LEFT|DT_TOP;
 	if (pEditData->m_nTextAlign == AlignMode_Right)
 		SetRightAlign(true);
}

// 渲染
void ControlEdit::Render()
{
	if ( !IsNeedRender() )
	{
		return;
	}

	if (IsSingleLine())
	{
		ControlObject::Render();
		RECT rcScreen;
		GetRealRect( &rcScreen );
		DWORD dwColoer;
		if( m_dwDefaultColor != 0 )
		{
			dwColoer = m_dwDefaultColor;
		}
		else
		{
			dwColoer = m_pstData->m_colFont;
		}
		if ( GetCharacterCount() > m_nStartIndex )
		{
			RECT rc = rcScreen;
			if( !FontSystem::IsUseNewFont() )
			{
				rc.top -= FontSystem::GetFontHeight(m_nFontIndex) / 8;
				rc.bottom += m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) / 2;
			}			

			if (IsRightAlign())
			{
				rc.left = rcScreen.right - ( ( ( rcScreen.right - rcScreen.left ) + FontSystem::GetFontHeight(m_nFontIndex) / 2 ) );
			}
			else
			{
				rc.left += 1;	
				rc.right += ( ( rcScreen.right - rcScreen.left ) + FontSystem::GetFontHeight(m_nFontIndex) / 2 );
			}

			GetFrameFather()->GetFrameRender()->PushWorkingArea(rcScreen);
			//rc.top += 1;
			if ( IsPassword() )
			{
				int nCount = GetCharacterCount() - m_nStartIndex;
				std::wstring strPwd;
				strPwd.insert( 0, nCount, '*' );
				//##
				FontSystem::DrawTextW( strPwd.c_str(), &rc, ( IsRightAlign() ? DT_RIGHT : DT_LEFT ) | DT_VCENTER,
					dwColoer, m_nFontIndex );
			}
			else
			{
				//##
				FontSystem::DrawTextW( &GetTextWString().c_str()[m_nStartIndex], &rc, ( IsRightAlign() ? DT_RIGHT : DT_LEFT ) | DT_VCENTER,
					dwColoer, m_nFontIndex );
				
			}
			GetFrameFather()->GetFrameRender()->PopWorkingArea();
		}
	}
	else
	{
		ControlText::Render();
	}

}

// 鼠标左键按下消息
bool ControlEdit::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( !IsVisable() || IsReadOnly() )
	{
		return false;
	}
	bool bUsed = false;
	if ( PtInObject( nX, nY ,true) )
	{
		if (IsSingleLine())
		{
			m_bDraging = true;
			const int nLen = 10240;
			char szChar[nLen];
			WideCharToMultiByte( CP_ACP, 0, GetTextW(), -1,
				szChar, nLen-1, NULL, NULL );
			szChar[nLen-1] = 0;
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnLBtnDownName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnLBtnDownName.c_str()] );
						function_( szChar );
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnLBtnDownName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
			}
			else
			{
				if( _funOnLBtnDown )
				{
					_funOnLBtnDown( this, szChar );
				}
			}

			if (!IsRightAlign())
			{
				RECT rcScreen;
				GetRealRect( &rcScreen );
				int start;
				CPtoX( GetTextWString(),m_nStartIndex, FALSE, &start );
				int x = start + (nX - rcScreen.left );
				int nCP = 0;
				BOOL bTrail = FALSE;
				BOOL bEnd;
				XtoCP(GetTextWString(), x, &nCP, &bTrail,&bEnd );
				SetCurIndex( nCP + (bTrail?1:0),GetLastTextData() );
			}

			m_bDrawFlashBar = true;
			//
			m_stSelect.pEndLine = m_stSelect.pStartLine = GetLastTextData();
			m_stSelect.nEndIndex =m_stSelect.nStartIndex = m_nCurIndex;
			int nStartX = 0;
			CPtoX( GetTextWString(),m_nCurIndex, FALSE, &nStartX );
			m_stSelect.nStartPos = m_stSelect.nEndPos = nStartX;
		}
		bUsed = true;
		SetActivate();
	}
	else
	{
		m_bDraging = false;
	}
	if (!IsSingleLine())
	{
		bUsed = ControlText::OnLButtonDown(nFlags,nX,nY) || bUsed;
	}

	return bUsed;
}

bool ControlEdit::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( !IsVisable() || IsReadOnly())
	{
		return false;
	}
	if (m_bDraging == true)
	{
		m_bDraging = false;
		return true;
	}
	if ( PtInObject( nX, nY ,true) )
	{
		if (m_PtInTextData)
		{
			const int nLen = 10240;
			char szChar[nLen];
			WideCharToMultiByte( CP_ACP, 0, m_PtInTextData->str.c_str(), -1,
				szChar, nLen-1, NULL, NULL );
			szChar[nLen-1] = 0;
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnLBtnUpName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnLBtnUpName.c_str()] );
						function_( szChar );
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnLBtnUpName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
			}
			else
			{
				if( _funOnLBtnUp )
				{
					_funOnLBtnUp( this, szChar );
				}
			}
		}

	}
	return false;
}

void ControlEdit::SetCurIndex( int nIndex ,STextData* pCurLineData)
{
	m_pCurLineData = pCurLineData;
// 	if (IsSingleLine())
// 	{
// 		const std::wstring& strSrcText = GetTextWString();
// 		if (IsRightAlign())
// 			m_nCurIndex = strSrcText.length();
// 		else
// 		{
// 			m_nCurIndex = nIndex;
// 			if ( m_nCurIndex < 0 || strSrcText.length() <= 0 )
// 			{
// 				m_nCurIndex = 0;
// 			}
// 			else if ( m_nCurIndex >= (int)strSrcText.length() )
// 			{
// 				m_nCurIndex = (int)strSrcText.length();
// 			}
// 		}
// 	}
// 	else
	{
		if (m_pCurLineData)
		{
			const std::wstring& strSrcText = pCurLineData->str;
			if (IsRightAlign())
				m_nCurIndex = strSrcText.length();
			else
			{
				m_nCurIndex = nIndex;
				if ( m_nCurIndex < 0 || strSrcText.length() <= 0 )
				{
					m_nCurIndex = 0;
				}
				else if ( m_nCurIndex >= (int)strSrcText.length() )
				{
					m_nCurIndex = (int)strSrcText.length();
				}
				else
				{	//如果在[]之间，则把位置放到'['左边，lrt
					if ( m_bHyberLimit )
					{
						size_t pos1 = strSrcText.rfind( L'[', m_nCurIndex-1 );
						size_t pos2 = strSrcText.rfind( L']', m_nCurIndex-1 );
						if ( ( pos2 == std::wstring::npos || pos2 < pos1 ) && pos1 != std::wstring::npos )
							m_nCurIndex = pos1;
					}
				}
			}
		}
		ReCalStartIndex();
		ReCalStartShowLine();
	}

}

bool ControlEdit::DelByte( bool bBack )
{
	if ( !m_stSelect.IsEmpty() )
	{
		int nCurrIndex = 0;
		bool bSelectStart = false;
		bool bSelectEnd = false;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			for ( size_t i=0; i<pText->vtTextData.size(); i++ )
			{
				STextData* pTextData = &pText->vtTextData[i];
				if (!bSelectStart)
				{
					if (m_stSelect.IsStartLine(pTextData))
					{
						bSelectStart = true;
						nCurrIndex += m_stSelect.GetStart();
					}
					else
					{
						nCurrIndex += pTextData->str.length();
					}
				}
				if (bSelectStart && !bSelectEnd)
				{
					int nStart = 0;
					int nEnd = pTextData->str.length();
					if (m_stSelect.IsStartLine(pTextData))
					{
						nStart = m_stSelect.GetStart();
					}
					if (m_stSelect.IsEndLine(pTextData))
					{
						bSelectEnd = true;
						nEnd =m_stSelect.GetEnd();
					}
					if (nStart == 0 && nEnd == pTextData->str.length())
					{
						pTextData->str.clear();
					}
					else
					{
						pTextData->str = pTextData->str.erase(nStart, nEnd - nStart);
					}
				}
			}
		}
		DataChanged();
		STextData* pCurrTextData = NULL;
		int nIndex = -1;
		GetTextPosByTotalIndex(pCurrTextData,nIndex,nCurrIndex);
		SetCurIndex(nIndex,pCurrTextData  );
		return true;
	}
	int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
	if (m_pCurLineData == NULL)
	{
		return false;
	}
	if ( bBack )
	{
		if ( m_nCurIndex >= 1 )
		{
			//如果发现[]，把整个[]都删了 lrt
			int removePos = 1;
			if ( m_bHyberLimit && m_pCurLineData->str[m_nCurIndex-1] == L']' )
			{
				size_t pos = m_pCurLineData->str.rfind( L'[', m_nCurIndex-1 );
				if ( pos != std::wstring::npos )
				{
					m_pCurLineData->str.erase( pos, m_nCurIndex - pos );
					removePos = m_nCurIndex - pos;
				}
				else
					m_pCurLineData->str.erase( m_nCurIndex-1, 1 );
			}
			else
				m_pCurLineData->str.erase( m_nCurIndex-1, 1 );
			DataChanged();
			if(IsSingleLine())
			{
				if ( m_nStartIndex > removePos - 1 )
				{
					m_nStartIndex-=removePos;
				}
			}
			SetCurIndex1(nTotalIndex - removePos );
		}
	}
	else
	{
		if ( m_nCurIndex >= (int)m_pCurLineData->str.length() )
		{
			STextData* pNextData = GetNextTextData(m_pCurLineData);
			if (pNextData && pNextData->str.length() > 0)
			{
				//如果发现[]，把整个[]都删了 lrt
				if ( m_bHyberLimit && pNextData->str[0] == L'[' )
				{
					size_t pos = pNextData->str.find( L']' );
					if ( pos != std::wstring::npos )
					{
						pNextData->str.erase( 0, pos );
					}
					else
						pNextData->str.erase( 0, 1 );
				}
				else
					pNextData->str.erase( 0, 1 );
			}
		}
		else
		{
			if ( m_bHyberLimit && m_pCurLineData->str[m_nCurIndex] == L'[' )
			{
				size_t pos = m_pCurLineData->str.find( L']', m_nCurIndex );
				if ( pos != std::wstring::npos )
				{
					m_pCurLineData->str.erase( m_nCurIndex, pos - m_nCurIndex + 1 );
				}
				else
					m_pCurLineData->str.erase( m_nCurIndex, 1 );
			}
			else
				m_pCurLineData->str.erase( m_nCurIndex, 1 );
		}
		DataChanged();
		SetCurIndex1(nTotalIndex);
	}
	return true;
}

void ControlEdit::DataChanged()
{
	// 输入数据范围限制
	if( FontSystem::IsUseNewFont() &&
		GetFrameFather() )
	{
		GetFrameFather()->SetRedraw();
	}
	if (m_bNumberLimit && GetLastTextData())
	{
		std::wstring& strSrcText = GetLastTextData()->str;
		if (m_nMinValue == 0 && m_nMaxValue == 0 && GetTextWString() != L"0" && GetLastTextData())
			GetLastTextData()->str = L"0";
		else
		{
			int v = _wtoi(strSrcText.c_str());
			if (v < m_nMinValue)
			{
				wchar_t buf[128];
				_itow(m_nMinValue, buf, 10);
				strSrcText = buf;
			}
			else if (v > m_nMaxValue)
			{
				wchar_t buf[128];
				_itow(m_nMaxValue, buf, 10);
				strSrcText = buf;
			}
		}
	}
	{
		ReCalculatePoint();
	}
// 	m_strMBText = szChar;

	if (_funOnTextChanged)
	{
		const int nLen = 10240;
		char szChar[nLen];
		WideCharToMultiByte( CP_ACP, 0, GetTextWString().c_str(), -1,
			szChar, nLen-1, NULL, NULL );
		szChar[nLen-1] = 0;
		_funOnTextChanged( this, szChar );
	}

// 	if ( m_strMBText.length() <= 0 )
// 	{
// 		return;
// 	}

	if (IsSingleLine())
	{
		if ( IsPassword() )
		{
			std::wstring strText;
			strText.insert( 0, GetTextWString().length(), '*' );
			RetriveAnalysis(strText);
		}
		else
		{
			RetriveAnalysis(GetTextWString());
		}
	}
// 	else
// 	{
// 		strText = m_strSrcText;
// 	}
}

bool ControlEdit::addChar( WCHAR wChar )
{
	//char szCharnum[128];
	//_snprintf(szCharnum,sizeof(szCharnum)-1,"%ld",(DWORD)wChar);
	//FILE* fp;
	//fp = fopen( "charnum.txt", "w" );
	//fwrite(szCharnum,sizeof(char),128,fp);
	//fclose(fp);

	if (((S_EditData*)m_pstData)->m_bIsNumber &&
		(wChar < L'0' || wChar > L'9'))
	{
		return false;
	}
	//std::string strText = Common::_tstring::toNarrowString( m_strText.c_str() );

	if( GetCharacterCount() >= m_nMaxLength )
	{
		return false;
	}
	if (GetLastTextData() == NULL)
	{
		std::wstring wsTemp;
		wsTemp = wChar;
		Clear();
		ParseText(wsTemp);
		DataChanged();
		SetCurIndex1(1);
	}
	else
	{
		int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
		m_pCurLineData->str.insert( m_nCurIndex, 1, wChar );
		DataChanged();
		SetCurIndex1( nTotalIndex+1 );
	}
	return true;
}

// 字符消息
bool ControlEdit::OnChar( UINT nChar )
{
	if ( !IsVisable() || !IsEnable() )
	{
		return false;
	}
	bool bUsed = false;
	if ( IsActivated() )
	{
		switch( nChar ) 
		{
		case VK_BACK:
			{
// 				if (IsRightAlign())
// 				{
// 					if (!m_strSrcText.empty())
// 					{
// 						m_strSrcText.erase(m_strSrcText.length() - 1);
// 						DataChanged();
// 					}
// 				}
// 				else
					DelByte( true );

				bUsed = true;
			}
			break;
		case VK_RETURN:
			{
                OnEnter(  );
                bUsed = true;
			}
			break;
			// Ctrl + C
		case 0x03:
			{
				if (IsRightAlign())
					break;

				if (((S_EditData*)m_pstData)->m_bIsNumber)
					break;

				if ( !m_stSelect.IsEmpty() )
				{
					const int nLen = 10240;
					char szChar[nLen];
					WideCharToMultiByte( CP_ACP, 0, GetSelectString().c_str(), -1,
						szChar, nLen-1, NULL, NULL );
					szChar[nLen-1] = 0;
					CopyToClipboard( szChar );
					bUsed = true;
				}
			}
			break;
			// Ctrl + X
		case 0x18:
			{
				if (IsRightAlign())
					break;

				if (((S_EditData*)m_pstData)->m_bIsNumber)
					break;

				if ( !m_stSelect.IsEmpty() )
				{
					const int nLen = 10240;
					char szChar[nLen];
					WideCharToMultiByte( CP_ACP, 0,  GetSelectString().c_str(), -1,
						szChar, nLen-1, NULL, NULL );
					szChar[nLen-1] = 0;
					CopyToClipboard( szChar );
					DelByte( true );
					bUsed = true;
				}
			}
			break;
			// Ctrl + V
		case 0x16:
			{
				if (IsRightAlign())
					break;

				if (((S_EditData*)m_pstData)->m_bIsNumber)
					break;

				if ( !m_stSelect.IsEmpty() )
				{
					DelByte( true );
				}
				const char* pszText = GetTextFromClipboard();
				if ( pszText )
				{
					const int nWLen = 10240;
					WCHAR wChar[nWLen];
					MultiByteToWideChar( CP_ACP, 0, pszText, -1, wChar, nWLen-1 );
					wChar[nWLen-1] = 0;
					std::wstring wstr(wChar);

					//输入[]变成* lrt
					if ( m_bHyberLimit )
					{
						for (int i = 0; i < wstr.length(); i++)
						{
							if ( wstr[i] == L'[' || wstr[i] == L']' )
								wstr[i] =  L'*' ;
						}
					}
					
					if (IsSingleLine())
					{
						if (wstr[0] == '\n' || wstr[0] == '\r')
							wstr = wstr.substr(1);
						size_t pos = wstr.find(L'\n');
						if (pos != std::wstring::npos)
							wstr = wstr.substr(0, pos);
						pos = wstr.find(L'\r');
						if (pos != std::wstring::npos)
							wstr = wstr.substr(0, pos);
					}
					if (GetLastTextData() == NULL)
					{
						Clear();
						ParseText(wstr);
						DataChanged();
						SetCurIndex1(wstr.length());
					}
					else
					{
						int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
						m_pCurLineData->str.insert( m_nCurIndex, wstr);
						DataChanged();
						SetCurIndex1( nTotalIndex+wstr.length() );
					}
				}
				bUsed = true;
			}
			break;
		default:
			{
				if ( nChar >= VK_SPACE )
				{
// 					if (IsRightAlign())
// 					{
// 						m_nCurIndex = m_strSrcText.length();
// 					}
// 					else 
					if ( !m_stSelect.IsEmpty() )
					{
						DelByte( true );
					}

					//输入[]变成* lrt
					if ( m_bHyberLimit )
					{
						if ( nChar == L'[' || nChar == L']' )
							nChar =  L'*' ;
					}

					addChar( nChar );
					bUsed = true;
				}
			}
			break;
		}
	}
	return bUsed;
}

void ControlEdit::_setTextW(std::wstring& strSrcText,UiCallbackDataArr* pBase)
{
	if( strSrcText.length() > m_nMaxLength )
	{
		int nRedundant = strSrcText.length() - m_nMaxLength ;
		strSrcText.erase(m_nMaxLength,nRedundant);
	}
	std::wstring strText;
	WordBreak( &strText, strSrcText.c_str() );
	ParseText(strText);
	DataChanged();
	m_nStartIndex = 0;
	if (GetLastTextData())
	{
		SetCurIndex( GetLastTextData()->str.length(),GetLastTextData() );
	}
	else
	{
		m_nCurIndex = 0;
		m_pCurLineData = NULL;
		m_nTextHeight = 0;
	}
	m_stSelect.Empty();

}





// 键盘按下消息
bool ControlEdit::OnKeyDown( UINT nChar )
{
	if ( !IsVisable() )
	{
		return false;
	}
	bool bUsed = false;
	if ( IsActivated() )
	{
		switch( nChar ) 
		{
		case VK_LEFT:
			{
				if (IsRightAlign())
					break;

				//发现[]，移动特殊处理 lrt
				int removePos = 1;
				if ( m_bHyberLimit && m_nCurIndex >= 1 )
				{
					if ( m_pCurLineData->str[m_nCurIndex-1] == L']' )
					{
						size_t pos = m_pCurLineData->str.rfind( L'[', m_nCurIndex-1 );
						if ( pos != std::wstring::npos )
						{
							removePos = m_nCurIndex - pos;
						}
					}
				}

				if ( m_nStartIndex > removePos - 1 )
				{
					m_nStartIndex-=removePos;
				}
				int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
				SetCurIndex1( nTotalIndex-removePos );
				m_bDrawFlashBar = true;
				m_stSelect.Empty();
				bUsed = true;
			}
			break;
		case VK_RIGHT:
			{
				if (IsRightAlign())
					break;

				//发现[]，移动特殊处理 lrt
				int removePos = 1;
				if ( m_bHyberLimit && m_pCurLineData->str[m_nCurIndex] == L'[' )
				{
					size_t pos = m_pCurLineData->str.find( L']', m_nCurIndex );
					if ( pos != std::wstring::npos )
					{
						removePos =  pos - m_nCurIndex + 1;
					}
				}

				int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
				SetCurIndex1( nTotalIndex+removePos );
				m_bDrawFlashBar = true;
				m_stSelect.Empty();
				bUsed = true;
			}
			break;
		case VK_UP:
			{
				if (IsRightAlign()|| IsSingleLine())
					break;
				if (m_pCurLineData == NULL)
				{
					break;
				}
				if (m_pCurLineData->nLine == 0)
				{
					break;
				}
				int nCurrPos = 0;
				if (!GetCurrPos(nCurrPos))
				{
					break;
				}
				STextData* pNextTextData = NULL;
				int nNextPos = 0;
				RetriveTextDataFromLinePos(pNextTextData,nNextPos,m_pCurLineData->nLine -1,nCurrPos);
				SetCurIndex(nNextPos,pNextTextData);
				m_bDrawFlashBar = true;
				m_stSelect.Empty();
				ReCalStartShowLine();
				bUsed = true;
			}
			break;
		case VK_DOWN:
			{
				if (IsRightAlign()|| IsSingleLine())
					break;

				if (m_pCurLineData == NULL)
				{
					break;
				}
				if (m_pCurLineData->nLine == m_nMaxLines)
				{
					break;
				}
				int nCurrPos = 0;
				if (!GetCurrPos(nCurrPos))
				{
					break;
				}
				STextData* pNextTextData = NULL;
				int nNextPos = 0;
				RetriveTextDataFromLinePos(pNextTextData,nNextPos,m_pCurLineData->nLine + 1,nCurrPos);
				SetCurIndex(nNextPos,pNextTextData);
				m_bDrawFlashBar = true;
				m_stSelect.Empty();
				ReCalStartShowLine();
				bUsed = true;
			}
			break;
		case VK_DELETE:
			{
// 				if (IsRightAlign())
// 				{
// 					m_strSrcText = L"";
// 					DataChanged();
// 					m_stSelect.Empty();
// 				}
// 				else
					DelByte( false );
				bUsed = true;
			}
			break;
		case VK_HOME:
			{
				if (IsRightAlign())
					break;

				SetCurIndex1( 0 );
				m_stSelect.Empty();
				bUsed = true;
			}
			break;
		case VK_END:
			{
				STextData* pLastData = GetLastTextData();
				if (pLastData)
				{
					SetCurIndex(pLastData->str.length(), pLastData );
				}
				else
				{
					SetCurIndex1(0);
				}
				m_stSelect.Empty();
				bUsed = true;
			}
			break;
		}
		//if(  nChar == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiChangeChatChanel) )
		//{
		//	if( ((S_EditData*)m_pstData)->m_bMultiline == false )
		//	{
		//		if( OnTab( m_strMBText.c_str() ) )
		//			return true;	//这里结掉消息 不处理下面的tab键切换控件焦点.
		//	}
		//}
	}
	return bUsed;
}

// 鼠标左键双击消息
bool ControlEdit::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	if ( !IsVisable() )
	{
		return false;
	}
	bool bUsed = false;
	if (IsSingleLine() && PtInObject( nX, nY ,true) )
	{
		if (GetLastTextData())
		{
			m_stSelect.nStartIndex = 0;
			m_stSelect.nEndIndex = (int)GetLastTextData()->str.length();
		}
		bUsed = true;
	}
	return bUsed;
}

// 鼠标移动消息
bool ControlEdit::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	if ( !IsVisable() )
	{
		return false;
	}

	if (IsSingleLine())
	{
		if ( ControlObject::PtInObject( nX, nY ,false) && _bIsShowTip)
		{
			theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
				nX, nY, false,
				m_nFontIndex, FontSystem::GetFontHeight(m_nFontIndex) ,  //m_pstData->m_nFontSize
				m_pstData->m_colFont,
				false );
		}

		bool bUsed = false;
		if( m_bDraging && !IsRightAlign() )
		{	
			RECT rcScreen;
			GetRealRect( &rcScreen );
			int start;
			CPtoX( GetTextWString(),m_nStartIndex, FALSE, &start );
			int x = start + (nX - rcScreen.left );
			int nCP = 0;
			BOOL bTrail = FALSE;
			BOOL bEnd;
			XtoCP(GetTextWString(), x, &nCP, &bTrail ,&bEnd);
			SetCurIndex( nCP + (bTrail?1:0),GetLastTextData() );
			m_stSelect.nEndIndex = m_nCurIndex;
			int nEndX = 0;
			CPtoX( GetTextWString(),m_nCurIndex, FALSE, &nEndX );
			m_stSelect.nEndPos = nEndX;
			bUsed = true;
		}
		return bUsed;
	}
	return ControlText::OnMouseMove(nFlags,nX,nY);
}

void ControlEdit::CopyToClipboard( const char *szText )
{
	if( !szText || szText[0] == 0 )
		return;

	if( !OpenClipboard(0) )
		return;
	EmptyClipboard();
	HGLOBAL clipbuffer;
	clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(szText)+1);
	char* buffer = (char*)GlobalLock(clipbuffer);
	strcpy_s(buffer, strlen(szText)+1, szText );
	GlobalUnlock(clipbuffer);
	SetClipboardData(CF_TEXT, clipbuffer);
	CloseClipboard();
}

char* ControlEdit::GetTextFromClipboard()
{
	if( !OpenClipboard(NULL) )
		return 0;
	char* buffer = 0;
	HANDLE hData = GetClipboardData( CF_TEXT );
	buffer = (char*)GlobalLock( hData );
	GlobalUnlock( hData );
	CloseClipboard();
	return buffer;
}


// bool ControlEdit::XtoCP( int nX, int *pCP, int *pnTrail )
// {
// 	if ( !pCP || !pnTrail )
// 	{
// 		return false;
// 	}
// 	float fScale = ControlObject::ControlObjectGetREAL_SCALE(this);
// 	//fScale = max( 0.8f, fScale );
// 	nX /= fScale;
// 
// 	*pCP = 0;
// 	*pnTrail = FALSE;
// 	HRESULT hr = S_FALSE;
// 	if ( m_Analysis )
// 	{
// 		hr = ScriptStringXtoCP( m_Analysis, nX, pCP, pnTrail );
// 		if( *pCP == -1 && *pnTrail == TRUE )
// 		{
// 			*pCP = 0;
// 			*pnTrail = FALSE;
// 		}
// 		else if( *pCP > (int)m_strSrcText.length() && *pnTrail == FALSE )
// 		{
// 			*pCP = (int)m_strSrcText.length();
// 			*pnTrail = TRUE;
// 		}
// 	}
// 	return SUCCEEDED( hr );
// }

void ControlEdit::OnEnter(  )
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnEnterName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnEnterName.c_str()] );
// 				function_( szData );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnEnterName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if (!IsSingleLine() && IsForceNewLine())
		{//换行
			addChar(L'\n');
		}
		if ( m_pOnEnter )
		{
			const int nLen = 10240;
			char szChar[nLen];
			WideCharToMultiByte( CP_ACP, 0, GetTextWString().c_str(), -1,
				szChar, nLen-1, NULL, NULL );
			szChar[nLen-1] = 0;
			m_pOnEnter( this, szChar );
		}
	}

}

const std::string& ControlEdit::operator=( const std::string& stText )
{
	SetText( stText );
	return stText;
}

const int& ControlEdit::operator=( const int& nNum )
{
	SetText( nNum );
	return nNum;
}
void ControlEdit::SelectAllContext()
{
	m_stSelect.Empty();
	if (m_vtText.size() > 0 && m_vtText[0].vtTextData.size() > 0)
	{
		m_stSelect.pStartLine = &m_vtText[0].vtTextData[0];
		m_stSelect.pEndLine = GetLastTextData();
		m_stSelect.nEndIndex = GetLastTextData()->str.length();
		if (IsPassword())
		{
			int nCount = GetCharacterCount() - m_nStartIndex;
			int nStartX = 0;
			CPtoX( GetTextWString(),nCount, FALSE, &nStartX );
			m_stSelect.nEndPos	 = nStartX;
		}
		else
		{
			m_stSelect.nEndPos	 = GetLastTextData()->rc.right;
		}
	}

}
bool ControlEdit::OnTab( IN const char* szData )
{
	if (m_bSelectAllAfterTab)
	{
		SelectAllContext();
	}
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnTabName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnTabName.c_str()] );
				function_( szData );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnTabName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
		return true;
	}
	else
	{
		if( _funOnTab )
		{
			_funOnTab( this, szData );
			return true;
		}
	}

	return false;
}

void ControlEdit::addText( const char* text )
{
	if( text )
	{
		const int nWLen = 10240;
		WCHAR wChar[nWLen];
		MultiByteToWideChar( CP_ACP, 0, text, -1, wChar, nWLen-1 );
		wChar[nWLen-1] = 0;

		std::wstring wsTemp;
		wsTemp = wChar;
		if (GetLastTextData() == NULL)
		{
			Clear();
			ParseText(wsTemp);
			DataChanged();
			SetCurIndex(GetLastTextData()->str.length(),GetLastTextData());
		}
		else
		{
			int nTotalIndex = GetTolalIndex(m_nCurIndex,m_pCurLineData);
			m_pCurLineData->str.insert( m_nCurIndex, wsTemp );
			DataChanged();
			SetCurIndex1( nTotalIndex+wsTemp.length() );
		}

// 		if( m_strSrcText.length() + strlen(text) >= m_nMaxLength )
// 			return;
// 
// 		m_strMBText += text;
// 		SetText( m_strMBText );
	}
}

void ControlEdit::Create( IN const RECT* pRect, const D3DCOLOR colText,
						 const bool bSingleLine, const bool bReadOnly,
						 const D3DCOLOR colBack,
						IN funOnEnter pCallbackFun )
{
	assert( pRect );
	ReleaseUI();
	S_EditData *pEdit = MeNew S_EditData;
	m_bNeedRelease = true;
	pEdit->m_nType = Type_Edit;
	pEdit->m_bSingleLine = bSingleLine;
	pEdit->m_bReadOnly = bReadOnly;
	pEdit->m_nTextAlign = AlignMode_Left;
	sprintf( pEdit->m_szID, "ID_EDIT_AUTO_%d", rand() );
	pEdit->m_rcRealSize = *pRect;
	InitUIData( NULL, pEdit );
	m_colBackColor = colBack;
	m_pstData->m_colFont = colText;

	m_pOnEnter = pCallbackFun;
}

void ControlEdit::editVisibleChange( ControlObject* pUIObject )
{
	{
		ControlEdit* pEdit = (ControlEdit*)pUIObject;
		pEdit->ClearSelected();
	}
}

void ControlEdit::ClearSelected()
{
	m_stSelect.Empty();
	m_bDraging = false;
}

void ControlEdit::DrawFlashBar()
{
	if ( IsActivated() && !IsRightAlign())
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		DWORD dwColoer;
		if( m_dwDefaultColor != 0 )
		{
			dwColoer = m_dwDefaultColor;
		}
		else
		{
			dwColoer = m_pstData->m_colFont;
		}
		if ( m_bDrawFlashBar )
		{
			RECT rc;
			if (IsSingleLine())
			{   //##    FontSystem::GetFontHeight(m_nFontIndex)
				int nHeight = 0, nTop = 0;
				if( !FontSystem::IsUseNewFont() )
				{
					nHeight = min( m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this), rcScreen.bottom-rcScreen.top ) ;
					nTop = rcScreen.top + (GetHeight()-nHeight)/2 + 2;
				}
				else
				{
					nHeight = FontSystem::GetFontHeight(m_nFontIndex) ;
					nTop = rcScreen.top + (GetHeight()-nHeight)/2  - 1/*+ 2*/;
				}
				if (IsRightAlign())
					rc.left = rcScreen.right;
				else
				{
					if( IsPassword() )
					{
						int nPassW = 0;
						static const std::wstring cs_wstrPass = L"*";
						CPtoX( cs_wstrPass, 1, FALSE, &nPassW );
						nPassW *= m_nCurIndex;
						rc.left = rcScreen.left + nPassW - 1;
					}
					else
					{
						int start;
						int cur;
						CPtoX( GetTextWString(),m_nStartIndex, FALSE, &start );
						CPtoX( GetTextWString(),m_nCurIndex, FALSE, &cur );
						rc.left = rcScreen.left + (cur-start) - 1/* + 1*/;
					}					
				}
				rc.top = nTop;
				rc.right = rc.left + 2;
				rc.bottom = rc.top + nHeight;
				GetDrawer()->FillRect2D( rc, dwColoer&0xdfffffff );
			}
			else 
			{
				int nHeight = 0;
				if( !FontSystem::IsUseNewFont() )
				{
					nHeight = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this);
				}
				else
				{
					nHeight = FontSystem::GetFontHeight(m_nFontIndex) ;
				}
				if (m_pCurLineData)
				{
					int cur = 0;
					GetCurrPos(cur);
					int nDrawHeight = m_pCurLineData->rc.bottom-m_pCurLineData->rc.top ;
					nHeight = min( nHeight, nDrawHeight) ;
					rc.left = rcScreen.left + m_pCurLineData->rc.left + (cur) + 1;
					rc.top = rcScreen.top + m_pCurLineData->rc.top + (nDrawHeight-nHeight)/2 + 2 - m_nCurLineYPos;
				}
				else
				{
					nHeight = min( nHeight, rcScreen.bottom - rcScreen.top) ;
					rc.left = rcScreen.left + 1;
					rc.top = rcScreen.top + 2 - m_nCurLineYPos;
				}
				{
					rc.right = rc.left + 2;
					rc.bottom = rc.top + nHeight;
					if ((rc.top >= rcScreen.top) && (rc.bottom <= rcScreen.bottom))
					{
						GetDrawer()->FillRect2D( rc, dwColoer&0xdfffffff );
					}
				}
			}
		}
		DWORD dwCurTime = HQ_TimeGetTime();
		if ( dwCurTime - m_dwFlashBar >= 500 )
		{
			m_dwFlashBar = dwCurTime;
			m_bDrawFlashBar = !m_bDrawFlashBar;
		}
	}
}

bool ControlEdit::GetCurrPos(int& nCurrPos)
{
	if (NULL == m_pCurLineData && m_pCurLineData->str.length() == 0)
	{
		return false;
	}
	if(!RetriveAnalysis(m_pCurLineData->str))
	{
		return false;
	}
	CPtoX( m_pCurLineData->str,m_nCurIndex, FALSE, &nCurrPos);
	return true;
// 	SCRIPT_STRING_ANALYSIS localAnalysis;
// 	SCRIPT_CONTROL ScriptControl; // For uniscribe
// 	SCRIPT_STATE   ScriptState;   // For uniscribe
// 	ZeroMemory( &ScriptControl, sizeof(ScriptControl) );
// 	ZeroMemory( &ScriptState, sizeof(ScriptState) );
// 	ScriptApplyDigitSubstitution ( NULL, &ScriptControl, &ScriptState );
// 	ScriptStringAnalyse( m_hDC,
// 		m_pCurLineData->str.c_str(),
// 		(int)m_pCurLineData->str.length() + 1,  // NULL is also analyzed.
// 		(int)m_pCurLineData->str.length() * 3 / 2 + 16,
// 		-1,
// 		SSA_BREAK | SSA_GLYPHS | SSA_FALLBACK | SSA_LINK,
// 		0,
// 		&ScriptControl,
// 		&ScriptState,
// 		NULL,
// 		NULL,
// 		NULL,
// 		&localAnalysis );
// 	if( localAnalysis )
// 	{
// 		int nDrawHeight = m_pCurLineData->rc.bottom-m_pCurLineData->rc.top ;
// 		int nHeight = min( m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this), nDrawHeight) ;
// 		int nTop = rcScreen.top + m_pCurLineData->rc.top + (nDrawHeight-nHeight)/2 + 2;
// 		int cur;
// 		CPtoX( m_nCurIndex, FALSE, &cur ,&localAnalysis);
// 		rc.left = rcScreen.left + m_pCurLineData->rc.left + (cur) + 1;
// 		rc.top = nTop;
// 		rc.right = rc.left + 2;
// 		rc.bottom = rc.top + nHeight;
// 
// 		ScriptStringFree( &localAnalysis );
// 	}

}

bool ControlEdit::GetTextPosByTotalIndex( STextData*& pRetTextData,int& nRetIndex,int nTotalIndex )
{
	int nLocalCharIndex = nTotalIndex;
	if (nLocalCharIndex < 0)
	{
		nLocalCharIndex = 0;
	}
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if (nLocalCharIndex > pTextData->str.length() )
			{
				nLocalCharIndex -= pTextData->str.length();
			}
			else
			{
				if (nLocalCharIndex == pTextData->str.length())
				{
					STextData* pNextData = GetNextTextData(pTextData);
					if (pNextData && (pNextData->nLine == pTextData->nLine + 1))
					{
						pRetTextData = pNextData;
						nRetIndex = 0;
						return true;
					}
				}
				pRetTextData = pTextData;
				nRetIndex = nLocalCharIndex;
				return true;
			}
		}
	}
	if (GetLastTextData())
	{
		pRetTextData = GetLastTextData();
		nRetIndex = pRetTextData->str.length();
		return true;
	}
	return false;
}

int ControlEdit::GetTolalIndex( int nIndex,STextData* pCurLineData )
{
	int nCount = 0;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if (pTextData == pCurLineData)
			{
				nCount += nIndex;
				return nCount;
			}
			else
			{
				nCount += pTextData->str.length();
			}
		}
	}
	return nCount;
}

void ControlEdit::SetCurIndex1( int nTotalIndex )
{
// 	if (IsSingleLine())
// 	{
// 		m_nCurIndex = nTotalIndex;
// 		int index = 0;
// 		GetTextPosByTotalIndex(m_pCurLineData,index,nTotalIndex);
// 	}
// 	else
	{
		m_pCurLineData = NULL;
		m_nCurIndex = 0;
		GetTextPosByTotalIndex(m_pCurLineData,m_nCurIndex,nTotalIndex);
		ReCalStartIndex();
		ReCalStartShowLine();
	}
}

void ControlEdit::ReCalStartShowLine()
{
	if (!IsSingleLine())
	{
		if( FontSystem::IsUseNewFont() &&
			GetFrameFather() )
		{
			GetFrameFather()->SetRedraw();
		}
		if (m_pCurLineData == NULL)
		{
			SetCurShowBeginLine(0);
		}
		else if (m_pCurLineData->nLine < m_nCurShowStartLine)
		{
			SetCurShowBeginLine(m_pCurLineData->nLine);
			RECT rcScreen;
			GetRealRect(&rcScreen);

			//## pyj test, 不要忘了,当重新计算了文字的区域之后将这个注释打开
			while (m_pCurLineData->rc.bottom - m_nCurLineYPos > rcScreen.bottom - rcScreen.top )
			{
				SetCurShowBeginLine(m_nCurShowStartLine + 1);
			}
		}
	}
}

void ControlEdit::ReCalStartIndex()
{
	if (IsSingleLine())
	{
		if( FontSystem::IsUseNewFont() &&
			GetFrameFather() )
		{
			GetFrameFather()->SetRedraw();
		}
		int nStartX = 0;
		int nCurX = 0;
		if ( m_nStartIndex > m_nCurIndex )
		{
			m_nStartIndex = m_nCurIndex;
		}
		CPtoX( GetTextWString(),m_nStartIndex, FALSE, &nStartX );
		CPtoX( GetTextWString(),m_nCurIndex, FALSE, &nCurX );
		int w = nCurX - nStartX;
		if ( w > GetWidth() )
		{
			int cp;
			BOOL bTrail;
			BOOL bEnd;
			XtoCP(GetTextWString(), nCurX-GetWidth(), &cp, &bTrail ,&bEnd);
			m_nStartIndex = cp + (bTrail?1:0) + 1;
		}
		else if ( w < 0 )
		{
			m_nStartIndex = m_nCurIndex;
		}
		if ( m_nStartIndex > m_nCurIndex )
		{
			m_nStartIndex = m_nCurIndex;
		}
	}
}

ControlEdit::STextData* ControlEdit::GetNextTextData( STextData* pCurLineData )
{
	if (pCurLineData == NULL)
	{
		return NULL;
	}
	bool bFound = false;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if (bFound)
			{
				return pTextData;
			}
			if (pTextData == pCurLineData)
			{
				bFound = true;
			}
		}
	}
	return NULL;
}

bool ControlEdit::ReCalculatePoint()
{
	int nCount = 0;
	int nMaxLengthTextIndex = -1;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		if (pText->vtTextData.size() > 0)
		{
			STextData *pTextData = &pText->vtTextData[0];
			pTextData->nLine = -1;
			std::wstring& wsTextData0Str = pTextData->str;
			if (nCount + wsTextData0Str.length() < m_nMaxLength)
			{
				nCount += wsTextData0Str.length();
				for (int j = 1; j < pText->vtTextData.size();++j)
				{
					std::wstring& wsTextDatajStr = pText->vtTextData[j].str;
					if (nCount + wsTextDatajStr.length() < m_nMaxLength)
					{
						pTextData->str += wsTextDatajStr;
					}
					else
					{
						wsTextDatajStr.erase(m_nMaxLength - nCount,wsTextDatajStr.length() - (m_nMaxLength - nCount));
						pTextData->str += wsTextDatajStr;
						nMaxLengthTextIndex = n;
					}
				}
			}
			else
			{
				wsTextData0Str.erase(m_nMaxLength - nCount,wsTextData0Str.length() - (m_nMaxLength - nCount));
				nMaxLengthTextIndex = n;
			}
			if (nMaxLengthTextIndex != -1)
			{
				break;
			}
		}
	}
	if (nMaxLengthTextIndex != -1)
	{
		std::vector<SText>::iterator iter = m_vtText.begin();
		for (int i = 0; i <= nMaxLengthTextIndex;++i)
		{
			++iter;
		}
		m_vtText.erase(iter,m_vtText.end());
	}
	if (!IsSingleLine())
	{
		m_nTextHeight = 0;
		CalculatePoint();
		m_nCurIndex = 0;
		m_pCurLineData = NULL;
	}
	m_stSelect.Empty();
	return true;
}

std::wstring& ControlEdit::GetSelectString()
{
	static std::wstring wsSelectString;
	wsSelectString.clear();
	if (m_stSelect.IsEmpty())
	{
		return wsSelectString;
	}
	if (IsSingleLine())
	{
		int start = min(m_stSelect.nStartIndex,m_stSelect.nEndIndex);
		int end = max(m_stSelect.nStartIndex,m_stSelect.nEndIndex);
		wsSelectString = GetTextWString().substr(start,end - start);
	}
	else
	{
		bool bSelectStart = false;
		bool bSelectEnd = false;
		for ( size_t n=0; n<m_vtText.size(); n++ )
		{
			SText *pText = &m_vtText[n];
			for ( size_t i=0; i<pText->vtTextData.size(); i++ )
			{
				STextData* pTextData = &pText->vtTextData[i];
				if (!bSelectStart)
				{
					if (m_stSelect.IsStartLine(pTextData))
					{
						bSelectStart = true;
					}
				}
				if (bSelectStart && !bSelectEnd)
				{
					int nStart = 0;
					int nEnd = pTextData->str.length();
					if (m_stSelect.IsStartLine(pTextData))
					{
						nStart = m_stSelect.GetStart();
					}
					if (m_stSelect.IsEndLine(pTextData))
					{
						bSelectEnd = true;
						nEnd =m_stSelect.GetEnd();
					}
					if (nStart == 0 && nEnd == pTextData->str.length())
					{
						wsSelectString += pTextData->str;
					}
					else
					{
						wsSelectString += pTextData->str.substr(nStart, nEnd - nStart);
					}
				}
			}
		}
	}
	return wsSelectString;

}

bool ControlEdit::RetriveTextDataFromLinePos( STextData*& pRetTextData,int& nRetIndex,int nLine, int nPosX )
{
	bool bFound = false;
	STextData* pLastMatchData = NULL;
	for ( size_t n=0; n<m_vtText.size(); n++ )
	{
		SText *pText = &m_vtText[n];
		bool bLineOver = false;
		for ( size_t i=0; i<pText->vtTextData.size(); i++ )
		{
			STextData* pTextData = &pText->vtTextData[i];
			if (pTextData->nLine < nLine)
			{
				continue;
			}
			if (pTextData->nLine == nLine)
			{
				if (pTextData->rc.left > nPosX)
				{
					pRetTextData = pTextData;
					nRetIndex = i;
					return true;
				}
				if (pTextData->rc.left <= nPosX && pTextData->rc.right > nPosX)
				{
					pRetTextData = pTextData;
					if(!RetriveAnalysis(pRetTextData->str))
					{
						return false;
					}
					int x = (nPosX  - pRetTextData->rc.left );
					int nCP = 0;
					BOOL bTrail = FALSE;
					BOOL bEnd;
					XtoCP(pRetTextData->str, x, &nCP, &bTrail,&bEnd );
					nRetIndex = nCP;
					return true;
				}
				pLastMatchData = pTextData;
			}
			if (pTextData->nLine > nLine)
			{
				bLineOver = true;
				break;
			}
		}
		if (bLineOver)
		{
			break;
		}
	}
	if (pRetTextData == NULL && pLastMatchData)
	{
		pRetTextData = pLastMatchData;
		if (pRetTextData)
		{
			nRetIndex = pRetTextData->str.length();
			return true;
		}
	}
	return false;
}

void ControlEdit::ParseText( std::wstring &strText )
{
	if (IsSingleLine())
	{
		SText stText;
		stText.type = eKeyNormal;
		stText.col = m_dwDefaultColor;
		STextData stTextData;
		stTextData.nLine = 0;
		stTextData.str = strText;
		stText.vtTextData.push_back( stTextData );
		m_vtText.push_back( stText );
		return;
	}
	ControlText::ParseText(strText);
}

void ControlEdit::DrawSelectTextForeGround()
{
	if (m_stSelect.IsEmpty() || IsRightAlign() || !IsActivated())
	{
		return;
	}
	if (IsSingleLine())
	{
		RECT rcScreen;
		GetRealRect( &rcScreen );
		int nHeight = min( FontSystem::GetFontHeight(m_nFontIndex) , rcScreen.bottom-rcScreen.top ) ;
		int nTop = rcScreen.top + (GetHeight()-nHeight)/2 - 1;
		RECT rc;
		rc.top = nTop;
		rc.bottom = rc.top + nHeight;
		int startIndex = min(m_stSelect.nStartIndex,m_stSelect.nEndIndex);
		int endIndex = max(m_stSelect.nStartIndex,m_stSelect.nEndIndex);
		int nBegin = 0;
		int nStartX = 0;
		int nEndX = 0;
		CPtoX( GetTextWString(),m_nStartIndex, FALSE, &nBegin );
		CPtoX( GetTextWString(),startIndex, FALSE, &nStartX );
		CPtoX( GetTextWString(),endIndex, FALSE, &nEndX );
		rc.left = rcScreen.left + (nStartX-nBegin);
		rc.right = rcScreen.left + (nEndX-nBegin);
		if ( rc.left < rcScreen.left )
		{
			rc.left = rcScreen.left+1;
		}
		if ( rc.right > rcScreen.right )
		{
			rc.right = rcScreen.right;
		}
		GetDrawer()->FillRect2D( rc, GetDefaultColor()&0xBF316AC5 );
	}
	else
	{
		ControlText::DrawSelectTextForeGround();
	}

}

void ControlEdit::Clear()
{
    ControlText::Clear();
}

void ControlEdit::SetEnterFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnEnterName = funName;
	unguard;
}
void ControlEdit::SetTabFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnTabName = funName;
	unguard;
}
void ControlEdit::SetLBtnDownFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnLBtnDownName = funName;
	unguard;
}
void ControlEdit::SetLBtnUpFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnLBtnUpName = funName;
	unguard;
}
void ControlEdit::SetDelByteFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funDelByteName = funName;
	unguard;
}