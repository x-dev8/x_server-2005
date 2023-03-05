#include "IntroductionManager.h"
#include "FuncPerformanceLog.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include <stdio.h>
#include <errno.h>
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "Ui/PopIntro.h"
#include "InfoTips.h"			//added by zhuomeng.hu		[9/11/2010]
#include "UINoobTipManager.h"	//added by ZhuoMeng.Hu		[9/16/2010]
#include "GuideTip.h"
#include "PopIntro5.h"
#include "PopIntro4.h"
#include "PopIntro3.h"
#include "StoryTip.h"
#include "Epic.h"

extern DWORD HQ_TimeGetTime();

CIntroductionManager::CIntroductionManager()
{
	guardfunc;
	m_nPopUpCount = 0;
	LoadTipConfig();
	CUINoobTipManager::Instance()->InitNoobTips( m_IntroList );		//初始化 UITip 表		added by ZhuoMeng.Hu		[9/16/2010]
	unguard;
}

CIntroductionManager::~CIntroductionManager()
{
	guardfunc;
	for (int i = 0; i < m_IntroList.size(); ++i)
	{
		delete m_IntroList[i];
	}
	m_IntroList.clear();
	unguard;
}

bool CIntroductionManager::LoadTipConfig()
{
	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile("..\\Data\\Config\\Guide.config", 1))
	{	
		return false;
	}


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return false;


	MeXmlElement* pIntroductions = pRoot->FirstChildElement("Introductions");
	if ( NULL == pIntroductions ) return false;

	MeXmlElement* pIntroduction = pIntroductions->FirstChildElement("Introduction");
	while (pIntroduction != NULL)
	{
		int id;
		if (pIntroduction->Attribute("Id", &id) == NULL)
		{
			continue;
		}
		int tipType;
		if (pIntroduction->Attribute("Type", &tipType) == NULL)
		{
			continue;
		}

		SIntroductionBase* pNewIntro = CreateIntro(id,tipType,pIntroduction);
		if (pNewIntro)
		{
			m_IntroList.push_back(pNewIntro);
		}
		pIntroduction = pIntroduction->NextSiblingElement();
	}
	return true;
}
const char* eFrameTypeString[CIntroductionManager::eTotalFrameType] =
{
	"LeftBottom",
	"LeftTop",
	"RightBottom",
	"RightTop",

};
CIntroductionManager::SIntroductionBase* CIntroductionManager::CreateIntro( int id,int type,MeXmlElement* pIntro )
{
	SIntroductionBase* pRet = NULL;
	Common::_tstring sTemp;			
	switch(type)
	{
	case eAboveNpcHeader:
		{
			SAboveNpcHeader* pNew = MeNew SAboveNpcHeader;

			sTemp.fromUTF8(pIntro->Attribute("NpcName"));
			pNew->npcName = sTemp;
			pIntro->Attribute("LifeTime", &pNew->nLifeTime);
			pIntro->Attribute("RepeatTime", &pNew->nRepeatTime);
			pRet = pNew;
			break;
		}
	case eUITip:
		{
			SUITip* pNew = MeNew SUITip;
			sTemp.fromUTF8(pIntro->Attribute("UIName"));
			pNew->strUIName = sTemp;
			sTemp.fromUTF8(pIntro->Attribute("ControlName"));
			pNew->strControlName = sTemp;
			sTemp.fromUTF8(pIntro->Attribute("FrameType"));
			for ( int i = 0; i < eTotalFrameType; ++i)
			{
				if (sTemp == eFrameTypeString[i])
				{
					pNew->nFrameType = i;
				}
			}
			pIntro->Attribute( "Time", &pNew->nLastTime );	//added by ZhuoMeng.Hu		[9/17/2010]
            pIntro->Attribute( "InnerLeft", &pNew->nInnerLeft );
            pIntro->Attribute( "InnerTop", &pNew->nInnerTop );
            pIntro->Attribute( "InnerRight", &pNew->nInnerRight );
            pIntro->Attribute( "InnerBottom", &pNew->nInnerBottom );
			pRet = pNew;
			break;
		}
	case ePopUpIntro:
		{
			SPopUpIntro* pNew = MeNew SPopUpIntro;
			pIntro->Attribute("Title", &pNew->nTitleStringId);
            pIntro->Attribute("Direct", &pNew->nPopType );
			pRet = pNew;
			break;
		}
	case eOperationIntro:
		{
			OperationIntro* pOptIntro = MeNew OperationIntro();
			sTemp.fromUTF8(pIntro->Attribute("Description"));
			pOptIntro->strDescription = sTemp;
			pRet = pOptIntro;
			break;
		}
	case eUIShowOperator:
		{
			UIShowOperater *pOpt  = MeNew UIShowOperater();

			sTemp.fromUTF8(pIntro->Attribute("UIName"));
			pOpt->strUIName = sTemp;

			sTemp.fromUTF8(pIntro->Attribute("ControlName"));
			pOpt->strControlName = sTemp;
			
			int nValue = 0;
			pIntro->Attribute("Show",&nValue);
			pOpt->bShow = (bool)nValue;
			pRet = pOpt;
			break;
		}
	case eShowUI:
		{
			//lyh新手引导挂机
			UIShow* pUIShow = MeNew UIShow;
			pIntro->Attribute("UI_ID", &pUIShow->UI_ID);
			pRet = pUIShow;
			break;
		}
		
	}
	pRet->nIntroId = id;
	pRet->nIntroType = type;
	pIntro->Attribute("String", &pRet->nStringId);
	pIntro->Attribute( "Level", &pRet->nLevel );

	return pRet;
}

void CIntroductionManager::ShowTip( int tipId )
{
	SIntroductionBase* pIntro = FindIntro(tipId);
	if (!pIntro)
	{
		return;
	}
	if (!pIntro->Show())
	{
		// UITip		added by ZhuoMeng.Hu		[9/17/2010]
		if( pIntro->GetIntroductionType() == eUITip )
		{
			std::list<SIntroductionBase*>::iterator iter = m_IntroStack.begin();
			for( ; iter != m_IntroStack.end(); ++iter )
			{
				if( ( *iter )->nIntroId == pIntro->nIntroId )
					break;
			}
			// 不重复则入栈
			if( iter == m_IntroStack.end() )
			{
				m_IntroStack.push_back( pIntro );
				CUINoobTipManager::Instance()->RefreshTipList();
				return;
			}
			else
			{
				return;
			}
		}

        // PopUpTip 支持直接弹出    modified by zhuomeng.hu		[10/25/2010]
        if( pIntro->GetIntroductionType() == ePopUpIntro )
        {
            if( ( ( SPopUpIntro* )pIntro )->nPopType > 0 )
            {
                DirectShowPopUpTip( ( SPopUpIntro* )pIntro );
                return;
            }

            m_IntroStack.push_back(pIntro);
            ++m_nPopUpCount;
            s_CUI_ID_FRAME_InfoTips.UpdateHelpRemend();
            return;
        }

		if ( pIntro->GetIntroductionType() == eOperationIntro )
		{
			return;
		}

		//打开ui
		if ( pIntro->GetIntroductionType() == eShowUI )
		{	
			MsgOpenUI msg;
			msg.UIFlag = (( UIShow* )pIntro)->UI_ID; //lyh新手引导挂机
			theHeroGame.GetPlayerMgr()->OnOpenUI(&msg);
			return;
		}

        // NPC头顶泡泡则直接入栈
		m_IntroStack.push_back(pIntro);
	}
}

void CIntroductionManager::ShowTipWithPlayer(int tipId, CPlayer* player )
{
	SIntroductionBase* pIntro = FindIntro(tipId);
	if (!pIntro)
	{
		return;
	}

	if ( pIntro->GetIntroductionType() == eAboveNpcHeader )
	{
		SAboveNpcHeader* headIntro = (SAboveNpcHeader*)pIntro;
		headIntro->ShowEx( player );
	}
}

void CIntroductionManager::ShowTipWithLevel( int lvl )
{
	for (int i = 0; i < m_IntroList.size(); ++i)
	{
		if (m_IntroList[i]->nLevel == lvl)
		{
			ShowTip( m_IntroList[i]->nIntroId );
		}
	}
}

int CIntroductionManager::RetrieveIntroductionId(const string& str)
{
	if (str.length() > 255)
	{
		return -1;
	}
	char pStr[256];
	strcpy(pStr,str.c_str());
	if (pStr && pStr[0] == '$' && pStr[1] == '('&& pStr[str.length() - 1] == ')')
	{//match
		pStr[str.length() - 1] = '\0';
		int nRet = atoi(&pStr[2]);
		if (errno == ERANGE || errno == EINVAL )
		{
			return -1;
		}
		return nRet;
	}
	return -1;
}

CIntroductionManager::SIntroductionBase* CIntroductionManager::FindIntro( int id )
{
	for (int i = 0; i < m_IntroList.size(); ++i)
	{
		if (m_IntroList[i]->nIntroId == id)
		{
			return m_IntroList[i];
		}
	}
	return NULL;
}

void CIntroductionManager::Update()
{
	for (std::list<SIntroductionBase*>::iterator iter = m_IntroStack.begin();iter != m_IntroStack.end();++iter)
	{
		if ((*iter)->Show())
		{
			m_IntroStack.erase(iter);
			break;
		}
	}
}

void CIntroductionManager::ClearStack()
{
// 	s_CUI_ID_FRAME_POPINTRO.SetVisable(false);
	m_IntroStack.clear();
	m_nPopUpCount = 0;
}

void CIntroductionManager::ShowPopUpTip( int index )
{
	int nCount = 0;
	for (std::list<SIntroductionBase*>::iterator iter = m_IntroStack.begin();iter != m_IntroStack.end();++iter)
	{
		if ((*iter)->GetIntroductionType() == ePopUpIntro)
		{
			if (nCount == index)
			{
				SPopUpIntro* pPopUp = (SPopUpIntro*)(*iter);
				pPopUp->ShowPopTip();
				m_IntroStack.erase(iter);
				--m_nPopUpCount;
				break;
			}
			++nCount;
		}

	}

	//modified by zhuomeng.hu		[9/11/2010]
	s_CUI_ID_FRAME_InfoTips.UpdateHelpRemend();
}

//added by ZhuoMeng.Hu		[9/17/2010]
void CIntroductionManager::EraseUITipById( int introId )
{
	for( std::list<SIntroductionBase*>::iterator iter = m_IntroStack.begin(); iter != m_IntroStack.end(); ++iter )
	{
		if( ( ( *iter )->nIntroId == introId ) && ( ( *iter )->GetIntroductionType() == eUITip ) )
		{
			m_IntroStack.erase( iter );
			break;
		}
	}
}

int CIntroductionManager::GetRepeatTime( int introId )
{
	SIntroductionBase* pIntro = FindIntro(introId);

	if ( pIntro && pIntro->GetIntroductionType() == eAboveNpcHeader )
	{
		return ((SAboveNpcHeader*)pIntro)->nRepeatTime;
	}
	return 1;	//默认指引操作只要一次就可以了
}

// 直接弹出的新手帮助       added by zhuomeng.hu		[11/9/2010]
void CIntroductionManager::DirectShowPopUpTip( SPopUpIntro* pPopUp )
{
    if( pPopUp->GetIntroductionType() != ePopUpIntro )
        return;

    switch( pPopUp->nPopType )
    {
    case 1:
        // 小泡泡没有 Title
        s_CUI_ID_FRAME_GuideTip.ShowPopInfo( pPopUp->nStringId );
        break;
    case 2:
		{
			s_CUI_ID_FRAME_StoryTip.SetVisable(true);
		    s_CUI_ID_FRAME_StoryTip.ShowAnim(pPopUp->nTitleStringId,pPopUp->nStringId);
		}
        break;
	case 3:
		{
			s_CUI_ID_FRAME_PopIntro3.SetVisable(true);
			s_CUI_ID_FRAME_PopIntro3.ShowInfo(pPopUp->nTitleStringId,pPopUp->nStringId);
		}
		break;
	case 4:
		{
			s_CUI_ID_FRAME_PopIntro4.SetVisable(true);
			s_CUI_ID_FRAME_PopIntro4.ShowInfo(pPopUp->nTitleStringId,pPopUp->nStringId);
		}
		break;
	case 5:
		{
			s_CUI_ID_FRAME_PopIntro5.SetVisable(true);
		    s_CUI_ID_FRAME_PopIntro5.ShowItemInfo(std::string(theXmlString.GetString(pPopUp->nStringId)));
		}
		break;
	case 6:	// 
		{
			theUiManager.SetFocus(NULL);
			s_CUI_ID_FRAME_Epic.SetSelectIndex(pPopUp->nTitleStringId);
			s_CUI_ID_FRAME_Epic.SetVisable(true);
			theUiManager.ToTop(s_CUI_ID_FRAME_Epic.GetFrame());
			s_CUI_ID_FRAME_Epic.InitAnim();
		}
		break;
    default:
        break;
    }
}

bool CIntroductionManager::SAboveNpcHeader::Show()
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName(npcName.c_str());
	if (!pPlayer)
	{
		return false;
	}
	string strIntro = theXmlString.GetString(nStringId);
	pPlayer->SetChatInfo(strIntro,nLifeTime*1000);
	return true;
}

void CIntroductionManager::SAboveNpcHeader::ShowEx( CPlayer* player )
{
	if (!player)
	{
		return;
	}
	string strIntro = theXmlString.GetString(nStringId);
	player->SetChatInfo(strIntro,nLifeTime*1000);
}

bool CIntroductionManager::SUITip::Show()
{
	return false;
}

bool CIntroductionManager::SPopUpIntro::Show()
{
	return false;
}

bool CIntroductionManager::SPopUpIntro::ShowPopTip()
{
	s_CUI_ID_FRAME_POPINTRO.SetVisable(true
		,theXmlString.GetString(nTitleStringId)
		,theXmlString.GetString(nStringId));
	return true;
}

bool CIntroductionManager::UIShowOperater::Show()
{
	if(strUIName.empty() || strControlName.empty())
		return false;

	ControlFrame* pFrame = (ControlFrame*)theUiManager.FindFrame(strUIName.c_str());
	if(!pFrame)
		return false;

	if(!pFrame->IsVisable())
		return false;

	ControlObject *pObject = pFrame->FindControl(strControlName.c_str());
	if(!pObject)
		return false;


	pObject->SetVisable(bShow);
	return true;
}
