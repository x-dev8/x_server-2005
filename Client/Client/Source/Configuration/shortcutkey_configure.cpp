
#include "shortcutkey_configure.h"
#include "FuncPerformanceLog.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "ui/customShortcutKey.h"
#include "Dxsdk/dinput.h"
#include "tstring.h"
#include "UserData.h"
#include "ui/TutorialBox.h"
#include "RapidXml/MeRapidXml.h"

extern short GetKeyboardInput(int iKey);

using namespace Common;

#define	SHORTCUTKEY_CONFIGURE_PATH	"..\\Data\\ClientConfig\\UserSetting.config"

CShortCutKey_Configure g_shortcutKey_configure;

extern CActionManager g_ActionManager;
extern int g_nKeydownGameAction[DIK_MEDIASELECT+1];

using namespace AN_Configure_ShortcutKey;

const std::string CShortCutKey_Configure::version("0.3.0.0");

CShortCutKey_Configure::CShortCutKey_Configure()
{
	customKeyMap.clear();

	memset( hotkeyState, ON_KEY_NONE, sizeof(hotkeyState) );
}

CShortCutKey_Configure::~CShortCutKey_Configure()
{

}
void CShortCutKey_Configure::setHotkeyState(int actionId, HotkeyState state )
{
	guardfunc;

	if( actionId < 0 || actionId >= AN_SCKC_MAX )
		return;

	hotkeyState[actionId] = state;
	unguard;
}
void CShortCutKey_Configure::hasChangeCustomKey()
{
	guardfunc;

	std::map<int, shortcutKeyValue> keyInfo = s_CUI_ID_FRAME_custom.getTempSaveKeyInfo();
	if( keyInfo.empty() )
		return;

	customKeyMap.clear();
	std::map<int, shortcutKeyValue>::iterator iter = keyInfo.begin();
	for( ; iter != keyInfo.end(); ++iter )
	{
		customKeyMap[iter->first] = iter->second;
	}

	initHotkey();
	write();

	unguard;
}
const char* CShortCutKey_Configure::getValueString(ShortCutKey_Configure type)
{
	guardfunc;

	if( type < 0 || type >= AN_SCKC_MAX)
		return "";

	std::map<int, shortcutKeyValue>::iterator iter = customKeyMap.find( type );
	if( iter != customKeyMap.end() )
	{
		if( iter->first == type)
		{
			static std::string str;
			str = "";
			if (iter->second._ctrl)
				str = "C-";
			else if (iter->second._alt)
				str = "Alt-";
			else if (iter->second._shift)
				str = "Shift-";
			str += iter->second._szValue;
			return str.c_str();
		}
	}

	return "";

	unguard;
}
const char* CShortCutKey_Configure::getDiscription( ShortCutKey_Configure type )
{
	guardfunc;
	if( type < 0 || type >= AN_SCKC_MAX)
		return NULL;

	std::map<int, shortcutKeyValue>::iterator iter = customKeyMap.find( type );
	if( iter != customKeyMap.end() )
	{
		if( iter->first == type)
			return iter->second._szDiscription.c_str();
	}

	return NULL;
	unguard;
}
void CShortCutKey_Configure::dealwithHotkey(CActionManager::SGameActionOperation action)
{
	guardfunc;
	switch( action.nActionID )
	{
	case AN_SCKC_jump:
		{
			if( !theHeroGame.GetPlayerMgr()->DoJumpAction() )
			{
				g_ActionManager.Push_ActionBackToDeque( action );
			}
			else
			{
				s_CUI_ID_FRAME_TutorialBox.OnSapcePress();
			}
		}
		break;
	case AN_SCKC_useSkill_operator:
		{
			CActionManager::SUseSkillOperation* pOperation = (CActionManager::SUseSkillOperation*)action.szOperationData;

			if( !pOperation )
			{
				break;
			}

			if( !theHeroGame.GetPlayerMgr()->DoUseSkillOperation( pOperation->SkillTargetID, pOperation->nSkillID, pOperation->nSkillLevel ) )
			{
				g_ActionManager.Push_OperationBackToDeque( action );
			}
		}
		break;
	}
	unguard;
}
void CShortCutKey_Configure::initHotkey()
{
	guardfunc;

	if( customKeyMap.empty() )
		return;

	memset( &g_nKeydownGameAction, 0, sizeof(g_nKeydownGameAction) );

	std::map<int, shortcutKeyValue>::iterator iter = customKeyMap.begin();
	for( ; iter != customKeyMap.end(); ++iter )
	{
		int nKeyDIK = getValueCharInput( (ShortCutKey_Configure)iter->first );
		if( nKeyDIK > 0 )
		{
			g_nKeydownGameAction[nKeyDIK] = iter->first;
		}
	}

	unguard;
}
int CShortCutKey_Configure::getValueCharInput(ShortCutKey_Configure type)
{
	guardfunc;
	if( _stricmp( getValueString(type), "mouseleft") == 0 )
		return DIMOFS_BUTTON0;
	if( _stricmp( getValueString(type), "mouseright") == 0 )
		return DIMOFS_BUTTON1;
	if( _stricmp( getValueString(type), "backspace") == 0 )
		return DIK_BACK;
	if( _stricmp( getValueString(type), "tab") == 0 )
		return DIK_TAB;
	if( _stricmp( getValueString(type), "enter") == 0 )
		return DIK_RETURN;
	if( _stricmp( getValueString(type), "pause") == 0 )
		return DIK_PAUSE;
	if( _stricmp( getValueString(type), "capslock") == 0 )
		return DIK_CAPITAL;
	if( _stricmp( getValueString(type), "esc") == 0 )
		return DIK_ESCAPE;
	if( _stricmp( getValueString(type), "space") == 0 )
		return DIK_SPACE;
	if( _stricmp( getValueString(type), "pageup") == 0 )
		return DIK_PRIOR;
	if( _stricmp( getValueString(type), "pagedown") == 0 )
		return DIK_NEXT;
	if( _stricmp( getValueString(type), "end") == 0 )
		return DIK_END;
	if( _stricmp( getValueString(type), "home") == 0 )
		return DIK_HOME;
	if( _stricmp( getValueString(type), "left") == 0 )
		return DIK_LEFT;
	if( _stricmp( getValueString(type), "up") == 0 )
		return DIK_UP;
	if( _stricmp( getValueString(type), "right") == 0 )
		return DIK_RIGHT;
	if( _stricmp( getValueString(type), "down") == 0 )
		return DIK_DOWN;
	if( _stricmp( getValueString(type), "insert") == 0 )
		return DIK_INSERT;
	if( _stricmp( getValueString(type), "delete") == 0 )
		return DIK_DELETE;
	if( _stricmp( getValueString(type), "0") == 0 )
		return DIK_0;
	if( _stricmp( getValueString(type), "1") == 0 )
		return DIK_1;
	if( _stricmp( getValueString(type), "2") == 0 )
		return DIK_2;
	if( _stricmp( getValueString(type), "3") == 0 )
		return DIK_3;
	if( _stricmp( getValueString(type), "4") == 0 )
		return DIK_4;
	if( _stricmp( getValueString(type), "5") == 0 )
		return DIK_5;
	if( _stricmp( getValueString(type), "6") == 0 )
		return DIK_6;
	if( _stricmp( getValueString(type), "7") == 0 )
		return DIK_7;
	if( _stricmp( getValueString(type), "8") == 0 )
		return DIK_8;
	if( _stricmp( getValueString(type), "9") == 0 )
		return DIK_9;
	if( _stricmp( getValueString(type), "a") == 0 )
		return DIK_A;
	if( _stricmp( getValueString(type), "b") == 0 )
		return DIK_B;
	if( _stricmp( getValueString(type), "c") == 0 )
		return DIK_C;
	if( _stricmp( getValueString(type), "d") == 0 )
		return DIK_D;
	if( _stricmp( getValueString(type), "e") == 0 )
		return DIK_E;
	if( _stricmp( getValueString(type), "f") == 0 )
		return DIK_F;
	if( _stricmp( getValueString(type), "g") == 0 )
		return DIK_G;
	if( _stricmp( getValueString(type), "h") == 0 )
		return DIK_H;
	if( _stricmp( getValueString(type), "i") == 0 )
		return DIK_I;
	if( _stricmp( getValueString(type), "j") == 0 )
		return DIK_J;
	if( _stricmp( getValueString(type), "k") == 0 )
		return DIK_K;
	if( _stricmp( getValueString(type), "l") == 0 )
		return DIK_L;
	if( _stricmp( getValueString(type), "m") == 0 )
		return DIK_M;
	if( _stricmp( getValueString(type), "n") == 0 )
		return DIK_N;
	if( _stricmp( getValueString(type), "o") == 0 )
		return DIK_O;
	if( _stricmp( getValueString(type), "p") == 0 )
		return DIK_P;
	if( _stricmp( getValueString(type), "q") == 0 )
		return DIK_Q;
	if( _stricmp( getValueString(type), "r") == 0 )
		return DIK_R;
	if( _stricmp( getValueString(type), "s") == 0 )
		return DIK_S;
	if( _stricmp( getValueString(type), "t") == 0 )
		return DIK_T;
	if( _stricmp( getValueString(type), "u") == 0 )
		return DIK_U;
	if( _stricmp( getValueString(type), "v") == 0 )
		return DIK_V;
	if( _stricmp( getValueString(type), "w") == 0 )
		return DIK_W;
	if( _stricmp( getValueString(type), "x") == 0 )
		return DIK_X;
	if( _stricmp( getValueString(type), "y") == 0 )
		return DIK_Y;
	if( _stricmp( getValueString(type), "z") == 0 )
		return DIK_Z;
	if( _stricmp( getValueString(type), "numeric0") == 0 )
		return DIK_NUMPAD0;
	if( _stricmp( getValueString(type), "numeric1") == 0 )
		return DIK_NUMPAD1;
	if( _stricmp( getValueString(type), "numeric2") == 0 )
		return DIK_NUMPAD2;
	if( _stricmp( getValueString(type), "numeric3") == 0 )
		return DIK_NUMPAD3;
	if( _stricmp( getValueString(type), "numeric4") == 0 )
		return DIK_NUMPAD4;
	if( _stricmp( getValueString(type), "numeric5") == 0 )
		return DIK_NUMPAD5;
	if( _stricmp( getValueString(type), "numeric6") == 0 )
		return DIK_NUMPAD6;
	if( _stricmp( getValueString(type), "numeric7") == 0 )
		return DIK_NUMPAD7;
	if( _stricmp( getValueString(type), "numeric8") == 0 )
		return DIK_NUMPAD8;
	if( _stricmp( getValueString(type), "numeric9") == 0 )
		return DIK_NUMPAD9;
	if( _stricmp( getValueString(type), "numeric*") == 0 )
		return DIK_MULTIPLY;
	if( _stricmp( getValueString(type), "numeric+") == 0 )
		return DIK_ADD;
	if( _stricmp( getValueString(type), "numeric-") == 0 )
		return DIK_SUBTRACT;
	if( _stricmp( getValueString(type), "numeric/") == 0 )
		return DIK_DIVIDE;
	if( _stricmp( getValueString(type), "numeric.") == 0 )
		return DIK_DECIMAL;
	if( _stricmp( getValueString(type), "numericenter") == 0 )
		return DIK_NUMPADENTER;
	if( _stricmp( getValueString(type), "f1") == 0 )
		return DIK_F1;
	if( _stricmp( getValueString(type), "f2") == 0 )
		return DIK_F2;
	if( _stricmp( getValueString(type), "f3") == 0 )
		return DIK_F3;
	if( _stricmp( getValueString(type), "f4") == 0 )
		return DIK_F4;
	if( _stricmp( getValueString(type), "f5") == 0 )
		return DIK_F5;
	if( _stricmp( getValueString(type), "f6") == 0 )
		return DIK_F6;
	if( _stricmp( getValueString(type), "f7") == 0 )
		return DIK_F7;
	if( _stricmp( getValueString(type), "f8") == 0 )
		return DIK_F8;
	if( _stricmp( getValueString(type), "f9") == 0 )
		return DIK_F9;
	if( _stricmp( getValueString(type), "f10") == 0 )
		return DIK_F10;
	if( _stricmp( getValueString(type), "f11") == 0 )
		return DIK_F11;
	if( _stricmp( getValueString(type), "f12") == 0 )
		return DIK_F12;
	if( _stricmp( getValueString(type), "numlock") == 0 )
		return DIK_NUMLOCK;
	if( _stricmp( getValueString(type), "leftshift") == 0 )
		return DIK_LSHIFT;
	if( _stricmp( getValueString(type), "rightshift") == 0 )
		return DIK_RSHIFT;
	if( _stricmp( getValueString(type), "leftctrl") == 0 )
		return DIK_LCONTROL;
	if( _stricmp( getValueString(type), "rightctrl") == 0 )
		return DIK_RCONTROL;
	if( _stricmp( getValueString(type), "leftmenu") == 0 )
		return DIK_LMENU;
	if( _stricmp( getValueString(type), "rightmenu") == 0 )
		return DIK_RMENU;
	if( _stricmp( getValueString(type), ";") == 0 )
		return DIK_SEMICOLON;
	if( _stricmp( getValueString(type), "=") == 0 )
		return DIK_EQUALS;
	if( _stricmp( getValueString(type), ",") == 0 )
		return DIK_COMMA;
	if( _stricmp( getValueString(type), "-") == 0 )
		return DIK_MINUS;
	if( _stricmp( getValueString(type), ".") == 0 )
		return DIK_PERIOD;
	if( _stricmp( getValueString(type), "/") == 0 )
		return DIK_SLASH;
	if( _stricmp( getValueString(type), "~") == 0 )
		return DIK_GRAVE;
	if( _stricmp( getValueString(type), "[") == 0 )
		return DIK_LBRACKET;
	if( _stricmp( getValueString(type), "|") == 0 )
		return DIK_BACKSLASH;
	if( _stricmp( getValueString(type), "]") == 0 )
		return DIK_RBRACKET;
	if( _stricmp( getValueString(type), "'") == 0 )
		return DIK_APOSTROPHE;
	if( _stricmp( getValueString(type), "prtscn") == 0 )
		return DIK_SYSRQ;

	return 0x00;
	unguard;
}
int CShortCutKey_Configure::getValueCharWin32(ShortCutKey_Configure type)
{
	guardfunc;

	std::map<int, win32String>::iterator iter = shortcutMap.begin();
	for( ; iter != shortcutMap.end(); ++iter )
	{
		if( _stricmp(iter->second._szValue.c_str(), getValueString(type)) == 0 )
		{
			return iter->first;
		}
	}

	return 0x00;
	unguard;
}
const char* CShortCutKey_Configure::getStringKeyWin32( int key )
{
	guardfunc;
	std::map<int, win32String>::iterator iter = shortcutMap.find( key );
	if( iter != shortcutMap.end() )
	{
		return iter->second._szValue.c_str();
	}

	return NULL;
	unguard;
}

void CShortCutKey_Configure::load()
{
	guardfunc;

	customKeyMap = defaultCustomKeyMap;

	std::string customFilename = CUserData::Instance()->GetUserDataPath();
	customFilename += "ShortcutKey.config";

	int nId = -1;
	const char* szValue = NULL;
	const char* szDiscription = NULL;
	const char* szHex = NULL;
	shortcutKeyValue info;

	MeXmlDocument doc1;
// 	if( !doc1.LoadFile(customFilename.c_str()) )
// 	{
// 		// 读旧的文件
// 		customFilename = CUserData::Instance()->GetUserDataPath();
// 		customFilename += "ShortcutKey.xml";
// 	}
	if( doc1.LoadFile(customFilename.c_str()) )
	{
// 		MeXmlHandle	 hDoc1(&doc1);

		MeXmlElement* pHeader = doc1.FirstChildElement("Project");
		if (pHeader)
		{
			const char* v = pHeader->Attribute("Version");
			if (v && v == version)
			{
				MeXmlElement* pElemCustom = pHeader->FirstChildElement("Custom");
				if (pElemCustom)
				{
					MeXmlElement* pElem = pElemCustom->FirstChildElement("Key");
					for( ; pElem; pElem = pElem->NextSiblingElement() )
					{
						pElem->QueryIntAttribute("Id", &nId);
						szValue = pElem->Attribute("Value");
						szDiscription = pElem->Attribute("Description");

						int value = 0;
						pElem->QueryIntAttribute("Alt", &value);
						info._alt = value;
						pElem->QueryIntAttribute("Ctrl", &value);
						info._ctrl = value;
						pElem->QueryIntAttribute("Shift", &value);
						info._shift = value;

						if( nId != -1 && szValue && szDiscription )
						{
							info._szValue = szValue;
							info._szDiscription = _tstring::toNarrowString(_tstring::UTF8towcs(szDiscription).c_str());

							customKeyMap[nId] = info;
						}
					}
				}
			}
			else
				write();
		}
		else
			write();
	}
	else
	{
		write();
	}

	s_CUI_ID_FRAME_custom.load();
	initHotkey();

	unguard;
}

void CShortCutKey_Configure::loadDefault()
{
	customKeyMap.clear();
	shortcutMap.clear();
	defaultCustomKeyMap.clear();
	typeIdMap.clear();
	types.clear();

	MeXmlDocument	doc;
	if( !doc.LoadFile(SHORTCUTKEY_CONFIGURE_PATH) )
	{
		assert(false && "shortcutkey_configure.cpp::load 读取文件不错");
		return;
	}

// 	MeXmlHandle		hDoc(&doc);

	int nId = -1;
	const char* szValue = NULL;
	const char* szDiscription = NULL;
	const char* szHex = NULL;
	shortcutKeyValue info;

	MeXmlElement* pType = doc.FirstChildElement("Project")->FirstChildElement("KeyboardSetting")->FirstChildElement("DefaultCustom")->FirstChildElement("Type");
	for( ; pType; pType = pType->NextSiblingElement() )
	{
		std::string type = _tstring::toNarrowString(_tstring::UTF8towcs(pType->Attribute("Name")).c_str());

		types.push_back(type);

		MeXmlElement* pElem = pType->FirstChildElement("Key");
		for( ; pElem; pElem = pElem->NextSiblingElement() )
		{
			pElem->QueryIntAttribute("Id", &nId);
			szValue = pElem->Attribute("Value");
			szDiscription = pElem->Attribute("Description");

			int value = 0;
			pElem->QueryIntAttribute("Alt", &value);
			info._alt = value;
			pElem->QueryIntAttribute("Ctrl", &value);
			info._ctrl = value;
			pElem->QueryIntAttribute("Shift", &value);
			info._shift = value;

			if( nId != -1 && szValue && szDiscription )
			{
				info._szValue = szValue;
				info._szDiscription = _tstring::toNarrowString(_tstring::UTF8towcs(szDiscription).c_str());

				defaultCustomKeyMap[nId] = info;
				customKeyMap[nId] = info;

				typeIdMap[type].push_back(nId);
			}
		}
	}

	win32String infoWin32String;
	MeXmlElement* pElem = doc.FirstChildElement("Project")->FirstChildElement("KeyboardSetting")->FirstChildElement("Shortcut")->FirstChildElement("Key");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		pElem->QueryIntAttribute("Id", &nId );
		szValue = pElem->Attribute("Value");
		szHex = pElem->Attribute("Hex");
		szDiscription = pElem->Attribute("Tip");

		if( nId != -1 && szValue && szHex && szDiscription )
		{
			infoWin32String._szValue = szValue;
			infoWin32String._szHex = szHex;
			infoWin32String._szTip = szDiscription;

			shortcutMap[nId] = infoWin32String;
		}
	}
}

void CShortCutKey_Configure::write()
{
	guardfunc;

	std::string customFilename = CUserData::Instance()->GetUserDataPath();
	customFilename += "ShortcutKey.config";

	SetFileAttributes( customFilename.c_str(), FILE_ATTRIBUTE_NORMAL );

	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "utf-8", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement* project = doc.InsertEndChild("Project");
	project->SetAttribute("Name", "HeroOnline");
	project->SetAttribute("Version", version.c_str());

	MeXmlElement* custom = project->InsertEndChild("Custom");
	custom->SetAttribute("Description", _description.c_str());
	std::map<int, shortcutKeyValue>::iterator iterCustom = customKeyMap.begin();
	for( ; iterCustom != customKeyMap.end(); ++iterCustom )
	{
		std::string str = _tstring::wcstoUTF8(
			_tstring::toWideString(iterCustom->second._szDiscription.c_str()).c_str());
		MeXmlElement *key = custom->InsertEndChild("Key");
		key->SetAttribute("Id", iterCustom->first);
		key->SetAttribute("Value", iterCustom->second._szValue.c_str());
		key->SetAttribute("Alt", iterCustom->second._alt);
		key->SetAttribute("Ctrl", iterCustom->second._ctrl);
		key->SetAttribute("Shift", iterCustom->second._shift);
		key->SetAttribute("Description", str.c_str());

	}
	

	doc.SaveFile(customFilename.c_str());

	// 删除旧文件格式ShortcutKey.xml
	customFilename = CUserData::Instance()->GetUserDataPath();
	customFilename += "ShortcutKey.xml";
	::DeleteFile(customFilename.c_str());

	unguard;
}

bool CShortCutKey_Configure::hasKey(int key, AN_Configure_ShortcutKey::ShortCutKey_Configure type)
{
	if( type < 0 || type >= AN_SCKC_MAX)
		return false;

	std::map<int, shortcutKeyValue>::iterator iterCu = customKeyMap.find( type );
	if( iterCu == customKeyMap.end() )
		return false;

	bool ctrl = false;
	bool alt = false;
	bool shift = false;

	if (GetKeyboardInput(DIK_LCONTROL) || GetKeyboardInput(DIK_RCONTROL))
		ctrl = true;
	else if (GetKeyboardInput(DIK_LALT) || GetKeyboardInput(DIK_RALT))
		alt = true;
	else if (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT))
		shift = true;

	std::map<int, win32String>::iterator iter = shortcutMap.begin();
	for( ; iter != shortcutMap.end(); ++iter )
	{
		if (_stricmp(iter->second._szValue.c_str(), iterCu->second._szValue.c_str()) == 0 &&
			iter->first == key &&
			iterCu->second._alt == alt &&
			iterCu->second._ctrl == ctrl &&
			iterCu->second._shift == shift)
			return true;
	}
	return false;
}
