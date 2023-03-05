#include "TitleConfig.h"
#include "tstring.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "application_config.h"
#include "GlobalDef.h"
#ifdef GAME_CLIENT
#include "IconManagerClient.h"
#endif


//////////////////////////////////////////////////////////////////////////
// 传入id是否可被当前title顶掉
const bool TitleConfig::Title::CanDisplace( int nTitleId ) const
{
	for( int i = 0 ; i < Title_Max_Displace ; ++ i )
	{
		if( nDisplaceIds[i] != 0 && nDisplaceIds[i] == nTitleId )
			return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
TitleConfig::TitleConfig()
{
	m_vecTitle.clear();
    m_mapNameToID.clear();
}

TitleConfig::~TitleConfig()
{

}

bool TitleConfig::AddTitle(TitleConfig::Title &xTitle, bool bReplace /* = false*/)
{
	titleiter iter = find(m_vecTitle.begin(), m_vecTitle.end(), xTitle.nID);
	if (iter != m_vecTitle.end())
	{
		if (bReplace)
		{
			*iter = xTitle;
		}
		return bReplace;
	}

    m_mapNameToID.insert(make_pair(xTitle.strName, xTitle.nID));

	m_vecTitle.push_back(xTitle);

	return true;
}

bool TitleConfig::RemoveTitle(short nID)
{
	titleiter iter = find(m_vecTitle.begin(), m_vecTitle.end(), nID);
	if (iter != m_vecTitle.end())
	{
		m_vecTitle.erase(iter);
		return true;
	}
	
	return false;
}

TitleConfig::Title* TitleConfig::GetTitleByIndex(unsigned int nIndex)
{
	if (nIndex < 0 || nIndex >= m_vecTitle.size()) { return NULL; }

	return &m_vecTitle[nIndex];
}

TitleConfig::Title* TitleConfig::GetTitleByTitleID(short nID)
{
    if (nID < Init_ID) { return NULL; }

	titleiter iter = find(m_vecTitle.begin(), m_vecTitle.end(), nID);
	if (iter != m_vecTitle.end())
	{
		return &(*iter);
	}

	return NULL;
}

short TitleConfig::GetTitleIDByTitleName(const char* szName)
{
    if (szName == NULL || *szName == 0)
    {
        return Init_ID;
    }

    mapiter iter = m_mapNameToID.find(szName);
    if (iter != m_mapNameToID.end())
    {
        return iter->second;
    }

    return Init_ID;
}

TitleConfig::Title* TitleConfig::GetTitleByTitleName(const char* szName)
{
    short nTitleID = GetTitleIDByTitleName(szName);

    return GetTitleByTitleID(nTitleID);
}

unsigned short TitleConfig::GetTitleTimeLimit(short nID)
{
    Title* pTitle = GetTitleByTitleID(nID);
    return (pTitle == NULL ? 0 : pTitle->GetTimeLimit());
}

bool TitleConfig::IsScriptTitle(short nID)
{
    Title* pTitle = GetTitleByTitleID(nID);
    return (pTitle == NULL ? false : pTitle->IsScript());
}

//传入条件和 完成条件的参数来获得称号属性
//时效性的,排行的称号, 规则 1 1  2 10  11  11
TitleConfig::Title* TitleConfig::GetTitleByConditionType(short nConditionType, unsigned int nParameter1, unsigned int nParameter2)
{
    if (nConditionType <= Condition_Init || nConditionType >= Condition_End)
    {
        return NULL;
    }

    titleiter iter = m_vecTitle.begin();
    titleiter end = m_vecTitle.end();

    for (; iter != end; ++iter)
    {
        if(iter->GetConditionType() == nConditionType)
        {
            switch (nConditionType)
            {
            case Condition_Money:
            case Condition_Level:
                if (nParameter1 >= iter->GetParameter1() && nParameter2 <= iter->GetParameter2())
                {
                    return &(*iter);
                }
            	break;
            }
        }
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
#define Root_Key		    "Project"
#define Titles_Key		    "Titles"
#define Title_Key		    "Title"
#define Id_Key			    "Id"
#define Type_Key		    "Type"
#define Quality_Key         "Quality"
#define StatusId_Key	    "StatusId"
#define StatusLevel_Key     "StatusLevel"
#define Name_Key		    "Name"
#define Description_Key	    "Description"
#define TimeLimit_Key       "TimeLimit"
#define Displace_Key        "Displace"
#define IsScript_Key        "IsScript"
#define ConditionType_Key   "ConditionType"
#define Invisible_Key		"Invisible"
#define Parameter1_Key      "Parameter1"
#define Parameter2_Key      "Parameter2"
#define Color_Key			"Color"
#define BuffId_Key			"BuffId"
#define BuffLevel_Key		"BuffLevel"
//////////////////////////////////////////////////////////////////////////////////////////


bool TitleConfig::LoadTitleConfig(const char *szFile)
{
	if (szFile == NULL || *szFile == 0)
    { return false;	}

	m_vecTitle.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement(Root_Key);
	if (pRoot == NULL )
    { return false; }

	//版本(是否需要检查)
	//////////////////////////////////////////////////////////
	MeXmlElement* pTitles = pRoot->FirstChildElement(Titles_Key);
	if (pTitles == NULL) 
    { return false; }

	MeXmlElement* pTitle = pTitles->FirstChildElement(Title_Key);
	while (pTitle != NULL)
	{	
		Title xTitle;


		//id
		int nID;
		if (pTitle->Attribute(Id_Key, &nID) == NULL || nID <= Init_ID || nID >= Max_ID ) 
        { return false; }
		xTitle.nID = nID;

		//Type
		int nType;
		if (pTitle->Attribute(Type_Key, &nType) == NULL || nType <= Title_Init || nType >= Title_End) 
        { return false; }
		xTitle.nType = nType;

		//StatusId
		int nStatusId;
		if (pTitle->Attribute(StatusId_Key, &nStatusId) == NULL || nStatusId < 0 || nStatusId >=  ErrorUnsignedShortID )//65535
        { return false; }
		xTitle.nStatusID = nStatusId;

        int nStatusLevel;
        if (pTitle->Attribute(StatusLevel_Key, &nStatusLevel) == NULL || nStatusLevel < 0 ) 
        { return false; }
        xTitle.nStatusLevel = nStatusLevel;

		//Name
		Common::_tstring strName = "";			
		strName.fromUTF8(pTitle->Attribute(Name_Key));
		if (strName.empty()) { return false; }
		xTitle.strName = strName;

        //Quality
        int nQuality;
		bool nNeedReadColor = false;
        pTitle->Attribute( Quality_Key, &nQuality );
        if ( nQuality < 0 )
		{
			nQuality = 1;
			// 如果品质为-1，则颜色从Color值读取
			nNeedReadColor = true;
		}
        xTitle.nQuality = nQuality;

		//Description
		Common::_tstring strDescription;			
		strDescription.fromUTF8(pTitle->Attribute(Description_Key));
		if (strDescription.empty())	
        { return false; }
		xTitle.strDescription = strDescription;

        //TimeLimit
        int nTimeLimit;
        if (pTitle->Attribute(TimeLimit_Key, &nTimeLimit) == NULL || nTimeLimit < 0) 
        { return false; }
        xTitle.nTimeLimit = nTimeLimit;

        //Displace
        int nDisplace;
		for( int i = 0 ; i < Title_Max_Displace ; ++ i )
		{
			char acDisplaceIdName[256] = {0};
			sprintf_s( acDisplaceIdName, 256, "%s%d", Displace_Key, i );//like "Displace[0-9]"
			if( pTitle->Attribute(acDisplaceIdName, &nDisplace) == NULL )
				break;
			xTitle.nDisplaceIds[i] = nDisplace;
		}        

        //bIsScript
        int nScript;
        if (pTitle->Attribute(IsScript_Key, &nScript) == NULL || nScript < 0 || nScript > 1) 
        { return false; }
        xTitle.bIsScript = nScript;

        //ConditionType
        int nConditionType;
        if (pTitle->Attribute(ConditionType_Key, &nConditionType) == NULL || nConditionType < Condition_Init || nConditionType > Condition_End)
        { return false; }
        xTitle.nConditionType = nConditionType;

		//Invisible
		int nInvisible;
		if (pTitle->Attribute(Invisible_Key, &nInvisible) == NULL || nInvisible < 0) 
        { return false; }
		xTitle.bInvisible = (bool)nInvisible;

        //Parameter1
        int nParameter1;
        if (pTitle->Attribute(Parameter1_Key, &nParameter1) == NULL || nParameter1 < Init_Param) 
        { return false; }
        xTitle.nParameter1 = nParameter1;

        //Parameter2
        int nParameter2;
        if (pTitle->Attribute(Parameter2_Key, &nParameter2) == NULL || nParameter2 < Init_Param)
        { return false; }
        xTitle.nParameter2 = nParameter2;

#ifdef GAME_CLIENT
		if( nNeedReadColor )	// 读"Color"字段颜色
		{
			const char* color = pTitle->Attribute(Color_Key);
			if (color)
			{
				std::string temp(color);
				size_t findPos = temp.find(',');
				int r = 0xff;
				int g = 0xff;
				int b = 0xff;
				if (findPos != std::string::npos)
				{
					r = atoi(temp.substr(0,findPos).c_str());
					size_t findPos2 = temp.find(',',findPos+1);
					if (findPos != std::string::npos)
					{
						g = atoi(temp.substr(findPos+1,findPos2-findPos-1).c_str());
						b = atoi(temp.substr(findPos2+1,temp.length()-findPos2-1).c_str());
						xTitle.dwColor = D3DCOLOR_XRGB(r, g, b);
					}
				}
			}
		}
		else
			xTitle.dwColor = S_IconInfoHero::GetQualityColor( xTitle.nQuality );
#endif

		int nBuffId = 0;
		pTitle->Attribute(BuffId_Key, &nBuffId);
		xTitle.nBuffId = nBuffId;

		int nBuffLevel = 0;
		pTitle->Attribute(BuffLevel_Key, &nBuffLevel);
		xTitle.nBuffLevel = nBuffLevel;

		if (!AddTitle(xTitle)) 
        { return false; }

		//next
		pTitle = pTitle->NextSiblingElement();
	}
	// 刷新每个title的nBeDisplaced变量
	for( int i = 0 ; i < theTitleConfig.GetTitleCount() ; ++ i )
	{
		TitleConfig::Title* pTitle = theTitleConfig.GetTitleByIndex( i );
		const unsigned short* const aDisplaceIds = pTitle->GetDisplaceIds();
		for( int j = 0 ; j < Title_Max_Displace ; ++ j )
		{
			if( aDisplaceIds[j] == -1 )
				continue;

			TitleConfig::Title* pDisplaceTitle = theTitleConfig.GetTitleByTitleID( aDisplaceIds[j] );
			if( !pDisplaceTitle )
				continue;

			pDisplaceTitle->BeDisplaced[pTitle->nID] = *pTitle;
		}
	}
	return true;
}

bool TitleConfig::SaveTitleConfig(const char *szFile)
{
	if (szFile == NULL || *szFile == 0) { return false;	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));

	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild((Root_Key))->ToElement();
	if (pRoot == NULL) { return false; }

	Common::_tstring strName = "HeroOnline";
	pRoot->SetAttribute("Name", strName.toUTF8().c_str());

	//Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();		
	pRoot->SetAttribute("Version", ""/*strVersion.toUTF8().c_str()*/); //version	

	MeXmlElement* pTitles = pRoot->InsertEndChild((Titles_Key))->ToElement();
	if(pTitles == NULL) { return false; }

	//按Id排序
	sort(m_vecTitle.begin(), m_vecTitle.end());

	titleiter iter = m_vecTitle.begin();
	titleiter end = m_vecTitle.end();
	for (; iter != end; ++iter)
	{
		MeXmlElement* pTitle = pTitles->InsertEndChild((Title_Key))->ToElement();
		if (pTitle == NULL) { return false; }

		pTitle->SetAttribute(Id_Key, iter->nID);		
		pTitle->SetAttribute(Type_Key, iter->nType);
		pTitle->SetAttribute(StatusId_Key, iter->nStatusID);
        pTitle->SetAttribute(StatusLevel_Key, iter->nStatusLevel);
        pTitle->SetAttribute(Quality_Key, iter->nQuality);
		//name
		Common::_tstring strName = iter->strName;		
		pTitle->SetAttribute(Name_Key, strName.toUTF8().c_str());

		//description
		Common::_tstring strDescription = iter->strDescription;		
		pTitle->SetAttribute(Description_Key, strDescription.toUTF8().c_str());

        pTitle->SetAttribute(TimeLimit_Key, iter->nTimeLimit);
		for( int i = 0 ; i < Title_Max_Displace ; ++ i )
		{
			char acDisplaceIdName[256] = {0};
			sprintf_s( acDisplaceIdName, 256, "%s%d", Displace_Key, i );//like "Displace[0-9]"			
			if( iter->nDisplaceIds[i] != 0 )
				pTitle->SetAttribute(acDisplaceIdName, iter->nDisplaceIds[i]);
		} 
        //pTitle->SetAttribute(Displace_Key, iter->nDisplaceIds);
        pTitle->SetAttribute(IsScript_Key, iter->bIsScript);
        pTitle->SetAttribute(ConditionType_Key, iter->nConditionType);
		pTitle->SetAttribute(Invisible_Key, iter->bInvisible );
        pTitle->SetAttribute(Parameter1_Key, iter->nParameter1);
        pTitle->SetAttribute(Parameter2_Key, iter->nParameter2);
	}

	return xMeXmlDoc.SaveFile(szFile);
}


const unsigned short TitleConfig::Title::GetNextTitleId( bool bOnly /* = false */ ) const
{
	// added, jiayi, [2010/3/18]
	// 如果此称号可被多个称号顶掉，则不查找
	if( IsMultiDisplaced() && bOnly )
		return 0;

	for( int i = 0 ; i < theTitleConfig.GetTitleCount() ; ++ i )
	{
		TitleConfig::Title* pTitle = theTitleConfig.GetTitleByIndex( i );
		if( !pTitle )
			continue;		
		if( pTitle->CanDisplace( GetID() ) )
			return pTitle->GetID();
	}
	return 0;
}

