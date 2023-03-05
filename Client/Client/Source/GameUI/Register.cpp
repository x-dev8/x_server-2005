/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Register.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Register.h"
#include "md5.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "CodeCheck.h"
#include "validate.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeUi/UiRender.h"
#include "Common.h"

#define GRAPHICCODE_WIDTH 160
#define GRAPHICCODE_HEIGHT 48
CUI_ID_FRAME_Register s_CUI_ID_FRAME_Register;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Register, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Register, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_AccountsOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_PasswordOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_Password2OnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_SuperPasswordOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_SuperPassword2OnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_EmailOnEditEnter )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Register, ID_CHECKBOX_AgreeOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_ResetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_RegisterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_Agreement1OnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_CardOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_Agreement2OnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Register, ID_EDIT_CodeCheckOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Register, ID_BUTTON_CodeCheckOnButtonClick )
CUI_ID_FRAME_Register::CUI_ID_FRAME_Register()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_Register::ResetMembers()
{
	m_pID_FRAME_Register = NULL;
	m_pID_PICTURE_BackGround = NULL;
	m_pID_TEXT_Accounts = NULL;
	m_pID_PICTURE_Accounts = NULL;
	m_pID_EDIT_Accounts = NULL;
	m_pID_TEXT_Password = NULL;
	m_pID_PICTURE_Password = NULL;
	m_pID_EDIT_Password = NULL;
	m_pID_TEXT_Password2 = NULL;
	m_pID_PICTURE_Password2 = NULL;
	m_pID_EDIT_Password2 = NULL;
	m_pID_TEXT_SuperPassword = NULL;
	m_pID_PICTURE_SuperPassword = NULL;
	m_pID_EDIT_SuperPassword = NULL;
	m_pID_TEXT_SuperPassword2 = NULL;
	m_pID_PICTURE_SuperPassword2 = NULL;
	m_pID_EDIT_SuperPassword2 = NULL;
	m_pID_TEXT_Email = NULL;
	m_pID_PICTURE_Email = NULL;
	m_pID_EDIT_Email = NULL;
	m_pID_CHECKBOX_Agree = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_BUTTON_Register = NULL;
	m_pID_BUTTON_Agreement1 = NULL;
	m_pID_TEXT_Agree = NULL;
	m_pID_TEXT_Card = NULL;
	m_pID_PICTURE_Card = NULL;
	m_pID_EDIT_Card = NULL;
	m_pID_PICTURE_AccountsExplain = NULL;
	m_pID_PICTURE_PasswordExplain = NULL;
	m_pID_PICTURE_SuperPasswordExplain = NULL;
	//m_pID_PICTURE_EmailExplain = NULL;
	m_pID_BUTTON_Agreement2 = NULL;
	m_pID_PICTURE_CardExplain = NULL;
	m_pID_TEXT_CodeCheck = NULL;
	m_pID_PICTURE_CodeCheckWall = NULL;
	m_pID_EDIT_CodeCheck = NULL;
	m_pID_PICTURE_CodeCheck = NULL;
	m_pID_BUTTON_CodeCheck = NULL;

	m_pCodeTexture = 0;
	m_CodeNumber = 0;

}
// Frame
bool CUI_ID_FRAME_Register::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Register::OnFrameRender()
{
	RECT rcDesRc, rcSrcRc;
	m_pID_PICTURE_CodeCheck->GetRealRect( &rcDesRc );
	rcSrcRc.left = 0;
	rcSrcRc.right = GRAPHICCODE_WIDTH;
	rcSrcRc.top = 0;
	rcSrcRc.bottom = GRAPHICCODE_HEIGHT;
	{
		CBaseGraphics::RenderTexture( (void*)m_pCodeTexture, &rcDesRc, &rcSrcRc, GRAPHICCODE_WIDTH, GRAPHICCODE_HEIGHT, 0, 0xffffffff );
	}
	return true;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_AccountsOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_PasswordOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_Password2OnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_SuperPasswordOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_SuperPassword2OnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_EmailOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// CheckBox
void CUI_ID_FRAME_Register::ID_CHECKBOX_AgreeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Button
bool CUI_ID_FRAME_Register::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Register )
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Register::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Register )
		return false;
	m_pID_EDIT_Accounts->SetText("");
	m_pID_EDIT_Password->SetText("");
	m_pID_EDIT_Password2->SetText("");
	m_pID_EDIT_SuperPassword->SetText("");
	m_pID_EDIT_SuperPassword2->SetText("");
	m_pID_EDIT_Email->SetText("");
	m_pID_EDIT_Card->SetText("");
	m_pID_EDIT_CodeCheck->SetText("");
	return true;
}

extern int RetrieveDataFromInternet(CHAR* pHttpAddress,CHAR* pBuffer,int nMaxSize);

// Button
bool CUI_ID_FRAME_Register::ID_BUTTON_RegisterOnButtonClick( ControlObject* pSender )
{
	return false;
	if( !m_pID_FRAME_Register )
		return false;
	if (NULL == m_pID_EDIT_Accounts->GetText() || '\0' == m_pID_EDIT_Accounts->GetText()[0])
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_EmptyPassport));
		return false;
	}
	else if (NULL == m_pID_EDIT_Password->GetText() || '\0' == m_pID_EDIT_Password->GetText()[0])
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_EmptyPassword));
		return false;
	}
	else
	{
		std::string ps0 = m_pID_EDIT_Password->GetText();
		if ((NULL == m_pID_EDIT_Password2->GetText())
			||ps0 != m_pID_EDIT_Password2->GetText())
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_NotSamePassword));
			return false;
		}
		else
		{
			if (ps0.length() < 6)
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorPassword1));
				return false;
			}
			else
			{
				if (!m_pID_CHECKBOX_Agree->IsChecked())
				{
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_Agreement));
					return false;
				}	
				else if (NULL == m_pID_EDIT_CodeCheck->GetText() || '\0' == m_pID_EDIT_CodeCheck->GetText()[0])
				{
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_CodeEmpty));
					return false;
				}
				else
				{
					std::string code = m_pID_EDIT_CodeCheck->GetText();
					int nCode = atoi(code.c_str());
					if (nCode != m_CodeNumber)
					{
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_CodeError));
						return false;
					}

				}
			}
		}
	}

	char buffer[2048] = {0};
	int nRet = -1;
	int nTryCount = 0;
	while(nRet == -1 && nTryCount < 10)
	{
		/*nRet = RetrieveDataFromInternet("http://event.tolez.com/reg/wsclient_getkey.php",buffer,2048);
		if (nRet == -1)
		{
			nTryCount++;
			Sleep(10);
		}*/
	}
	char* pCommaPos = strstr(buffer,",");
	if (nRet == -1 || NULL ==  pCommaPos)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eError_ServerBusy));
		return false;
	}
	pCommaPos[0] = '\0';
	std::string retkey = buffer;
	std::string retValue = pCommaPos + 1;
	retValue += "wsclient";
	MD5 md5Value(retValue.c_str());

	std::string strMd5Value = md5Value.toString();

	std::string strDynWebAdd = "http://event.tolez.com/reg/wsclient_sign.php?key=";
	strDynWebAdd += retkey;
	strDynWebAdd += "&value=";
	strDynWebAdd += strMd5Value;
	strDynWebAdd += "&passport=";
	strDynWebAdd += m_pID_EDIT_Accounts->GetText();
	strDynWebAdd += "&password=";
	strDynWebAdd += m_pID_EDIT_Password->GetText();
	strDynWebAdd += "&newcard=";
	if (m_pID_EDIT_Card->GetText() && '\0'!= m_pID_EDIT_Card->GetText()[0] )
	{
		strDynWebAdd += m_pID_EDIT_Card->GetText();
	}

	nRet = -1;
	nTryCount = 0;
	while(nRet == -1 && nTryCount < 10)
	{
		nRet = RetrieveDataFromInternet((char*)strDynWebAdd.c_str(),buffer,2048);
		if (nRet == -1)
		{
			nTryCount++;
			Sleep(10);
		}			
	}
	if (nRet == -1 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eError_ServerBusy));
		return false;
	}
	int nRetValue = atoi(buffer);
	switch(nRetValue)
	{
	case 1:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_OK));
			SetVisable(false);
		}
		break;
	case 101:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_EmptyPassport));
		}
		break;
	case 104:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_EmptySupperPassword));
		}
		break;
	case 106:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_EmptyEmail));
		}
		break;
	case 117:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorPassword1));
		}
		break;
	case 119:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorSupperPassword));
		}
		break;
	case 202:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorPassport));
		}
		break;
	case 203:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorEmail));
		}
		break;
	case 204:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorEmail1));
		}
		break;
	case 205:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorPassword));
		}
		break;
	case 296:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_ErrorNewerCard));
		}
		break;
	case 500:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eError_ServerBusy));
		}
		break;
	case 501:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_Fail));
		}
		break;
	case 502:
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eRegister_AlreadyExist));
		}
		break;
	}

	return true;
}
// Button
bool CUI_ID_FRAME_Register::ID_BUTTON_Agreement1OnButtonClick( ControlObject* pSender )
{
	return false;
	if( !m_pID_FRAME_Register )
		return false;
	ShellExecute( NULL, "open", "https://sso.tolez.com/agreement.php", NULL, NULL, 0 );
	return true;
}
// Edit
void CUI_ID_FRAME_Register::ID_EDIT_CardOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
// Button
bool CUI_ID_FRAME_Register::ID_BUTTON_Agreement2OnButtonClick( ControlObject* pSender )
{
	return false;
	if( !m_pID_FRAME_Register )
		return false;
	ShellExecute( NULL, "open", "https://sso.tolez.com/agreement2.php", NULL, NULL, 0 );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Register::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Register.MEUI",false,UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Register.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Register::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Register, s_CUI_ID_FRAME_RegisterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Register, s_CUI_ID_FRAME_RegisterOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_Accounts, s_CUI_ID_FRAME_RegisterID_EDIT_AccountsOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_Password, s_CUI_ID_FRAME_RegisterID_EDIT_PasswordOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_Password2, s_CUI_ID_FRAME_RegisterID_EDIT_Password2OnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_SuperPassword, s_CUI_ID_FRAME_RegisterID_EDIT_SuperPasswordOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_SuperPassword2, s_CUI_ID_FRAME_RegisterID_EDIT_SuperPassword2OnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_Email, s_CUI_ID_FRAME_RegisterID_EDIT_EmailOnEditEnter );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Register, ID_CHECKBOX_Agree, s_CUI_ID_FRAME_RegisterID_CHECKBOX_AgreeOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_RegisterID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_Reset, s_CUI_ID_FRAME_RegisterID_BUTTON_ResetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_Register, s_CUI_ID_FRAME_RegisterID_BUTTON_RegisterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_Agreement1, s_CUI_ID_FRAME_RegisterID_BUTTON_Agreement1OnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_Card, s_CUI_ID_FRAME_RegisterID_EDIT_CardOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_Agreement2, s_CUI_ID_FRAME_RegisterID_BUTTON_Agreement2OnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_Register, ID_EDIT_CodeCheck, s_CUI_ID_FRAME_RegisterID_EDIT_CodeCheckOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Register, ID_BUTTON_CodeCheck, s_CUI_ID_FRAME_RegisterID_BUTTON_CodeCheckOnButtonClick );

	m_pID_FRAME_Register = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Register );
	m_pID_PICTURE_BackGround = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_BackGround );
	m_pID_TEXT_Accounts = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Accounts );
	m_pID_PICTURE_Accounts = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_Accounts );
	m_pID_EDIT_Accounts = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_Accounts );
	m_pID_TEXT_Password = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Password );
	m_pID_PICTURE_Password = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_Password );
	m_pID_EDIT_Password = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_Password );
	m_pID_TEXT_Password2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Password2 );
	m_pID_PICTURE_Password2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_Password2 );
	m_pID_EDIT_Password2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_Password2 );
	m_pID_TEXT_SuperPassword = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_SuperPassword );
	m_pID_PICTURE_SuperPassword = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_SuperPassword );
	m_pID_EDIT_SuperPassword = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_SuperPassword );
	m_pID_TEXT_SuperPassword2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_SuperPassword2 );
	m_pID_PICTURE_SuperPassword2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_SuperPassword2 );
	m_pID_EDIT_SuperPassword2 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_SuperPassword2 );
	m_pID_TEXT_Email = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Email );
	m_pID_PICTURE_Email = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_Email );
	m_pID_EDIT_Email = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_Email );
	m_pID_CHECKBOX_Agree = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Register, ID_CHECKBOX_Agree );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_Reset );
	m_pID_BUTTON_Register = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_Register );
	m_pID_BUTTON_Agreement1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_Agreement1 );
	m_pID_TEXT_Agree = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Agree );
	m_pID_TEXT_Card = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_Card );
	m_pID_PICTURE_Card = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_Card );
	m_pID_EDIT_Card = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_Card );
	m_pID_PICTURE_AccountsExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_AccountsExplain );
	m_pID_PICTURE_PasswordExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_PasswordExplain );
	m_pID_PICTURE_SuperPasswordExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_SuperPasswordExplain );
	//m_pID_PICTURE_EmailExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_EmailExplain );
	m_pID_BUTTON_Agreement2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_Agreement2 );
	m_pID_PICTURE_CardExplain = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_CardExplain );
	m_pID_TEXT_CodeCheck = (ControlText*)theUiManager.FindControl( ID_FRAME_Register, ID_TEXT_CodeCheck );
	m_pID_PICTURE_CodeCheckWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_CodeCheckWall );
	m_pID_EDIT_CodeCheck = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Register, ID_EDIT_CodeCheck );
	m_pID_PICTURE_CodeCheck = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Register, ID_PICTURE_CodeCheck );
	m_pID_BUTTON_CodeCheck = (ControlButton*)theUiManager.FindControl( ID_FRAME_Register, ID_BUTTON_CodeCheck );
	assert( m_pID_FRAME_Register );
	assert( m_pID_PICTURE_BackGround );
	assert( m_pID_TEXT_Accounts );
	assert( m_pID_PICTURE_Accounts );
	assert( m_pID_EDIT_Accounts );
	assert( m_pID_TEXT_Password );
	assert( m_pID_PICTURE_Password );
	assert( m_pID_EDIT_Password );
	assert( m_pID_TEXT_Password2 );
	assert( m_pID_PICTURE_Password2 );
	assert( m_pID_EDIT_Password2 );
// 	assert( m_pID_TEXT_SuperPassword );
// 	assert( m_pID_PICTURE_SuperPassword );
// 	assert( m_pID_EDIT_SuperPassword );
// 	assert( m_pID_TEXT_SuperPassword2 );
// 	assert( m_pID_PICTURE_SuperPassword2 );
// 	assert( m_pID_EDIT_SuperPassword2 );
// 	assert( m_pID_TEXT_Email );
// 	assert( m_pID_PICTURE_Email );
// 	assert( m_pID_EDIT_Email );
	assert( m_pID_CHECKBOX_Agree );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Reset );
	assert( m_pID_BUTTON_Register );
	assert( m_pID_BUTTON_Agreement1 );
	assert( m_pID_TEXT_Agree );
	assert( m_pID_TEXT_Card );
	assert( m_pID_PICTURE_Card );
	assert( m_pID_EDIT_Card );
	assert( m_pID_PICTURE_AccountsExplain );
	assert( m_pID_PICTURE_PasswordExplain );
	//assert( m_pID_PICTURE_SuperPasswordExplain );
	//assert( m_pID_PICTURE_EmailExplain );
	assert( m_pID_BUTTON_Agreement2 );
	m_pID_FRAME_Register->SetOnTab( OnTab );
	m_pID_FRAME_Register->SetMsgProcFun( frame_msg );

	m_pID_EDIT_Accounts->SetMaxLength(32);
	assert( m_pID_PICTURE_CardExplain );
	assert( m_pID_TEXT_CodeCheck );
	assert( m_pID_PICTURE_CodeCheckWall );
	assert( m_pID_EDIT_CodeCheck );
	assert( m_pID_PICTURE_CodeCheck );
	m_pID_EDIT_Password->SetMaxLength(32);
	m_pID_EDIT_Password2->SetMaxLength(32);
	// ui commented out, [9/26/2010 zhangjiayi]
// 	m_pID_EDIT_SuperPassword->SetMaxLength(32);
// 	m_pID_EDIT_SuperPassword2->SetMaxLength(32);
// 	m_pID_EDIT_Email->SetMaxLength(64);
	m_pID_EDIT_Card->SetMaxLength(10);
	m_pID_EDIT_CodeCheck->SetMaxLength(4);
	m_pID_EDIT_CodeCheck->SetIsNumber(true);

	// ui commented out, [9/26/2010 zhangjiayi]
	/*m_pID_PICTURE_SuperPasswordExplain->setTip(theXmlString.GetString(eText_SuperPasswordExplain),DT_LEFT);*/
	m_pID_CHECKBOX_Agree->SetCheck(true);
	SetVisable(false);

	LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if (FAILED( pDevice->CreateTexture(
		GRAPHICCODE_WIDTH,
		GRAPHICCODE_HEIGHT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pCodeTexture,
		NULL)))
		return false;
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Register::_UnLoadUI()
{
	ResetMembers();
	if( m_pCodeTexture )
	{
		m_pCodeTexture->Release();
		m_pCodeTexture = 0;
	}
	return theUiManager.RemoveFrame( "Data\\UI\\Register.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Register::_IsVisable()
{
	if( !m_pID_FRAME_Register )
		return false;
	return m_pID_FRAME_Register && m_pID_FRAME_Register->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Register::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Register )
		return;
	m_pID_FRAME_Register->SetVisable( bVisable );
	m_pID_FRAME_Register->SetRedraw();
	if (bVisable)
	{
		ID_BUTTON_CodeCheckOnButtonClick(NULL);
	}

}

void CUI_ID_FRAME_Register::ID_EDIT_CodeCheckOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Register )
		return;
}
#define random(x) (rand() % (x))

bool CUI_ID_FRAME_Register::ID_BUTTON_CodeCheckOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Register )
		return false;
	unsigned char *background, *bitstream;

	//随机0-9999之间的一个整数,缓存,然后传给接口
	m_CodeNumber = random(10000);

	char strNumberName[MAX_PATH] = {0};
	MeSprintf_s(strNumberName,sizeof(strNumberName)/sizeof(char) - 1, "%s/data/Ui/Common/Pics/", SwGlobal::GetWorld()->GetAppDataCharDir());

	char backgroundPath[MAX_PATH] = {0};
	MeSprintf_s(backgroundPath,sizeof(backgroundPath)/sizeof(char) - 1, "%s/data/Ui/Common/Background/", SwGlobal::GetWorld()->GetAppDataCharDir());

	background = (unsigned char*)malloc(7680 * sizeof(char));
	bitstream = (unsigned char*)malloc(960 * sizeof(char));

	if(!validate(m_CodeNumber,backgroundPath,strNumberName,bitstream))
	{
		fprintf(stderr, "Error Validate.\n");
		free(background);
		free(bitstream);
		return 0;
	}

	s_CUI_ID_FRAME_CodeCheck.Uncompress(bitstream,background);

	D3DLOCKED_RECT dRect;
	if( D3D_OK == m_pCodeTexture->LockRect( 0, &dRect, 0, 0 ) )
	{
		for( DWORD y=0; y<GRAPHICCODE_HEIGHT; y++ )
		{
			for( DWORD x=0; x<GRAPHICCODE_WIDTH; x++ )
			{
				DWORD dwFactor = background[ y * GRAPHICCODE_WIDTH + x ];
				((DWORD*)dRect.pBits)[GRAPHICCODE_WIDTH*y+x] = 
					D3DCOLOR_ARGB( 255, dwFactor, dwFactor, dwFactor );
			}
		}
		m_pCodeTexture->UnlockRect( 0 );
	}

	free(background);
	free(bitstream);
	return true;
}
extern GAME_STATE g_GameState;
bool CUI_ID_FRAME_Register::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;

	if (  g_GameState != G_LOGIN )
		return false;
	if (!s_CUI_ID_FRAME_Register.IsVisable())
	{
		return false;
	}

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if ( !s_CUI_ID_FRAME_MessageBox.IsEnableOnButCancel() )
				break;
			{
				if( wParam == VK_ESCAPE )
				{
					s_CUI_ID_FRAME_Register.ID_BUTTON_CLOSEOnButtonClick( NULL );
					return true;
				}
				if( wParam == VK_RETURN )
				{
					s_CUI_ID_FRAME_Register.ID_BUTTON_RegisterOnButtonClick( NULL );
				}
			}
		}
		break;
	}

	return false;

	unguard;

}

void CUI_ID_FRAME_Register::OnTab()
{
	guardfunc;
	if( theUiManager.GetFocus() == s_CUI_ID_FRAME_Register.m_pID_EDIT_Accounts )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_Register.m_pID_EDIT_Password );
		s_CUI_ID_FRAME_Register.m_pID_EDIT_Password->SelectAllContext();
	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_Register.m_pID_EDIT_Password )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_Register.m_pID_EDIT_Password2 );
		s_CUI_ID_FRAME_Register.m_pID_EDIT_Password2->SelectAllContext();
	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_Register.m_pID_EDIT_Password2 )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_Register.m_pID_EDIT_Card );
		s_CUI_ID_FRAME_Register.m_pID_EDIT_Card->SelectAllContext();
	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_Register.m_pID_EDIT_Card )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_Register.m_pID_EDIT_CodeCheck );
		s_CUI_ID_FRAME_Register.m_pID_EDIT_CodeCheck->SelectAllContext();
	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_Register.m_pID_EDIT_CodeCheck )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_Register.m_pID_EDIT_Accounts );
		s_CUI_ID_FRAME_Register.m_pID_EDIT_Accounts->SelectAllContext();
	}
	unguard;

}