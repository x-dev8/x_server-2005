#include "XinFaConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"
#include "ItemDetail.h"

XinFaConfig::XinFaConfig()
{
}

XinFaConfig::~XinFaConfig()
{
    m_XinFaArray.Clear();
}
int XinFaConfig::GetSkillNeedXinFaLevel(unsigned short nXinFaID, unsigned short nSkillID)
{
	if (nXinFaID >= EXCD_XinFaMaxNum )
		return -1;
	
	for (int i = 0; i < EXCD_XinFaMaxLevel; ++i)
	{
		XinFaConfig::STalentXinFa* pXinFa = &(m_XinFaArray[nXinFaID][i]);
		if (pXinFa->nId == 0 || pXinFa->nLevel == 0)
			continue;
		if (pXinFa->IsActiveSkill(nSkillID))
		{
			return pXinFa->nLevel;
		}
	}


	return -1;
}
XinFaConfig::STalentXinFa* XinFaConfig::GetXinFaByID(unsigned short nID,  unsigned short nLevel)
{
    if (nID >= EXCD_XinFaMaxNum )
        return NULL;

    if (nLevel == 0 || nLevel>= EXCD_XinFaMaxLevel)
        return NULL;

    XinFaConfig::STalentXinFa* pXinFa = &(m_XinFaArray[nID][nLevel]);
    if (pXinFa->nId == 0 || pXinFa->nLevel == 0)
        return NULL;
    
    return pXinFa;
}
XinFaConfig::STalentXinFa* XinFaConfig::GetXinFaByProfession(unsigned short nProfessionID,  unsigned short index)
{
	if (nProfessionID >= EArmType_MaxSize )
		return NULL;

	if (index>= EXCD_XinFaMaxNum)
		return NULL;

	XinFaConfig::STalentXinFa* pXinFa;
	
	pXinFa = &(m_XinFaArray[index][EXCD_XinFaMaxLevel - 1]);
	if (pXinFa->nId == 0 || pXinFa->nLevel == 0 || !pXinFa ->arrayProfessionReq[nProfessionID])
		return NULL;
	
	return pXinFa;
}
bool XinFaConfig::LoadXinFaConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pTalents = pRoot->FirstChildElement("Talents");
    if (pTalents == NULL) 
    { return false; }

    int iValue = 0;

    MeXmlElement* pXinFaElement = pTalents->FirstChildElement("XinFa");
    while (pXinFaElement != NULL)
    {	
        STalentXinFa xTalentXinFa;

        pXinFaElement->Attribute("ID", &iValue);
        xTalentXinFa.nId = iValue;

        pXinFaElement->Attribute("Level", &iValue);
        xTalentXinFa.nLevel = iValue;

        pXinFaElement->Attribute("IconID", &iValue);
        xTalentXinFa.nIconId = iValue;

        Common::_tstring strName;
        strName.fromUTF8( pXinFaElement->Attribute("Name") );
        xTalentXinFa.strName = strName;

        Common::_tstring strDesc;
        strDesc.fromUTF8( pXinFaElement->Attribute("Desc") );
        xTalentXinFa.strDesc = strDesc;

        pXinFaElement->Attribute("PrevXinFa", &iValue);
        xTalentXinFa.nPrevXinFa = iValue;

        pXinFaElement->Attribute("NeedLevel", &iValue);
        xTalentXinFa.nNeedLevel = iValue;

        pXinFaElement->Attribute("NeedMoney", &iValue);
        xTalentXinFa.nNeedMoney = iValue;

        pXinFaElement->Attribute("NeedExp", &iValue);
        xTalentXinFa.nNeedExp   = iValue;

        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        {
            xTalentXinFa.arrayProfessionReq[ iLoop ] = false;
        }

        Common::_tstring strProfessionReq;
        strProfessionReq.fromUTF8( pXinFaElement->Attribute("NeedProfession") );
        if ( strProfessionReq.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                xTalentXinFa.arrayProfessionReq[ iLoop ] = true;
            }
        }
        else
        {  
            //适用多个职业
            char *szSpn = ",";
            char *szStr;
            int iIndex;
            szStr = strtok( const_cast<char*>(strProfessionReq.c_str()),szSpn );
            while( szStr )
            {

                iIndex = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iIndex >= 0 && iIndex < EArmType_MaxSize )
                {
                    xTalentXinFa.arrayProfessionReq[ iIndex ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        for (int i = 0; i< EXCD_EffectCharAttrMax ; ++i)
        {
            char szTmpAttr[21] = {0};
            sprintf_s(szTmpAttr, sizeof(szTmpAttr) - 1, "CharAttrType%d", i+1);

            Common::_tstring strAttrType;
            strAttrType.fromUTF8( pXinFaElement->Attribute(szTmpAttr) );
            xTalentXinFa.charAttrType[i] = HelperFunc::GetIDByConstString( (char*)strAttrType.c_str(),
                g_szCharAttributeType,sizeof(g_szCharAttributeType)/sizeof(char*) ); 

            char szTmpVal[21] = {0};
            sprintf_s(szTmpVal, sizeof(szTmpVal) - 1, "CharAttrValue%d", i+1);

            pXinFaElement->Attribute(szTmpVal, &iValue);
            xTalentXinFa.charAttrValue[i].fValue = iValue;
        }

        int nSkillIndex = 0;
        MeXmlElement* pSkillElement = pXinFaElement->FirstChildElement("Skill");
        while (pSkillElement != NULL)
        {
            if (nSkillIndex >= EXCD_SkillMaxCount)
            { break; }

            SXinFaSkill skill;
            
            pSkillElement->Attribute("ID", &iValue);
            skill.nId = iValue;

            pSkillElement->Attribute("Level", &iValue);
            skill.nLevel = iValue;

            for (int i = 0; i< EXCD_EffectSkillAttr ; ++i)
            {
                char szTmpAttr[21] = {0};
                sprintf_s(szTmpAttr, sizeof(szTmpAttr) - 1, "AttrType%d", i+1);

                Common::_tstring strAttrType;
                strAttrType.fromUTF8( pSkillElement->Attribute(szTmpAttr) );
                skill.attrType[i] = HelperFunc::GetIDByConstString( (char*)strAttrType.c_str(),
                    g_szSkillStatusAttrType,sizeof(g_szSkillStatusAttrType)/sizeof(char*) ); 

                char szTmpVal[21] = {0};
                sprintf_s(szTmpVal, sizeof(szTmpVal) - 1, "AttrValue%d", i+1);

                pSkillElement->Attribute(szTmpVal, &iValue);
                skill.attrValue[i] = iValue;
            }

            xTalentXinFa.skills[nSkillIndex] = skill;
            ++nSkillIndex;

            pSkillElement = pSkillElement->NextSiblingElement();
        }

        m_XinFaArray[xTalentXinFa.nId][xTalentXinFa.nLevel] = xTalentXinFa;

        pXinFaElement = pXinFaElement->NextSiblingElement();
    }

    return true;
}
