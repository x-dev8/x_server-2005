#include "ExpActionConfig.h"
#include "tstring.h"

bool ExpActionConfig::LoadExpActionConfig( const char* szFile )
{
	if ( szFile == NULL || *szFile == 0 )
	{ return false; }

	m_mapExpAction.clear();
	m_nMaleExpActionNum = 0;
	m_nFemaleExpActionNum = 0;

	MeXmlDocument xMeXml;
	if ( !xMeXml.LoadFile( szFile, 1 ) )
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
	if ( pRoot == NULL )
	{ return false; }

	MeXmlElement* pExpAction = pRoot->FirstChildElement( "ExpAction" );
	if ( pExpAction == NULL )
	{ return false; }

	int nCD = 0;
	if ( pExpAction->Attribute( "CD", &nCD ) == NULL )
	{ return false; }

	m_nExpActionCD = nCD;

	int nTargetMaxDist = 0;
	if ( pExpAction->Attribute( "TargetDistanceMax", &nTargetMaxDist ) == NULL || nTargetMaxDist < 0 )
	{ return false; }

	m_ustTargetMaxDist = (unsigned short)nTargetMaxDist;

	MeXmlElement* pExpActions = pRoot->FirstChildElement( "ExpActions" );
	if ( pExpActions == NULL )
	{ return false; }

	int nValue = 0;
	const char* szValue = NULL;
	std::wstring wstr;
	std::string str;

	MeXmlElement* pAction = pExpActions->FirstChildElement( "Action" );
	while ( pAction != NULL )
	{
		ExpAction xAction;
		if( pAction->Attribute( "Id", &nValue ) == NULL || nValue < 0 )
		{ return false;	}
		xAction.SetId( (unsigned short)nValue );

		// 兼容旧格式，如果Sex字段没，默认为男女通用
		ExpAction::ESex sex = ExpAction::SAll;
		if( pAction->Attribute( "Sex", &nValue ) )
		{
			if( nValue < ExpAction::SAll || nValue > ExpAction::Female )
			{
#ifdef _CLIENT_ 
				char strErrorMsg[MAX_PATH] = {0};
				sprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "LoadExpActionConfig Action ID:%d WRONG Sex!", xAction.GetId());
				MessageBox(NULL, strErrorMsg, "Error", MB_OK);
#endif
				assert(0);
				pAction = pAction->NextSiblingElement();
				continue;
			}
			else
				sex = (ExpAction::ESex)nValue;
		}
		xAction.SetSex(sex);

		if( pAction->Attribute( "ItemId", &nValue ) == NULL || nValue < 0 )
		{ return false;	}
		xAction.SetItemId( (unsigned short)nValue );

		szValue = pAction->Attribute( "ActionName" );
		if( szValue == NULL )
		{ return false;	}
		xAction.SetActionName( szValue );

		szValue = pAction->Attribute( "LoopActionName" );
		if( szValue != NULL )
			xAction.SetLoopActionName( szValue );

		szValue = pAction->Attribute( "Command" );
		if( szValue == NULL )
		{ return false;	}
		wstr = Common::_tstring::UTF8towcs(szValue);
		str = Common::_tstring::toNarrowString(wstr.c_str());
		xAction.SetCommand( str.c_str() );

		szValue = pAction->Attribute( "StringNoTarget" );
		if( szValue != NULL )
		{
			wstr = Common::_tstring::UTF8towcs(szValue);
			str = Common::_tstring::toNarrowString(wstr.c_str());
			xAction.SetNoTargetChat( str.c_str() );
		}

		szValue = pAction->Attribute( "StringSelfTarget" );
		if( szValue != NULL )
		{
			wstr = Common::_tstring::UTF8towcs(szValue);
			str = Common::_tstring::toNarrowString(wstr.c_str());
			xAction.SetSelfTargetChat( str.c_str() );
		}

		szValue = pAction->Attribute( "StringOtherTarget" );
		if( szValue != NULL )
		{
			wstr = Common::_tstring::UTF8towcs(szValue);
			str = Common::_tstring::toNarrowString(wstr.c_str());
			xAction.SetOtherTargetChat( str.c_str() );
		}

		if( pAction->Attribute( "SelfFront", &nValue ) == NULL || nValue < 0 )
		{ return false;	}
		xAction.SetOtherTargetSelfFront( (bool)(nValue > 0) );

		szValue = pAction->Attribute( "Sound" );
		if( szValue != NULL )
			xAction.SetSound( szValue );

		if( !AddExpAction( xAction.GetId(), xAction ) )
		{
#ifdef _CLIENT_
			char strErrorMsg[MAX_PATH] = {0};
			sprintf_s(strErrorMsg, sizeof(strErrorMsg)-1, "LoadExpActionConfig Action ID:%d duplicated，load failed!", xAction.GetId());
			MessageBox(NULL, strErrorMsg, "Error", MB_OK);
#endif
			assert(0);
		}
		else
		{
			if( sex == ExpAction::Male )
			{
				++m_nMaleExpActionNum;
			}
			else if( sex == ExpAction::Female )
			{
				++m_nFemaleExpActionNum;
			}
			else
			{
				++m_nMaleExpActionNum;
				++m_nFemaleExpActionNum;
			}
		}

		pAction = pAction->NextSiblingElement();
	}
	return true;
}
