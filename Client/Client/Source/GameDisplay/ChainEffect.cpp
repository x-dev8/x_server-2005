#include "ChainEffect.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "Common.h"

CChainEffect::CChainEffect(void)
{

}

CChainEffect::~CChainEffect(void)
{

}


void CChainEffect::Update( DWORD dwTime, D3DXVECTOR3 vTargetPos, float fDistance )
{
	//获得目标玩家
	CPlayer* pTargetPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nPlayerID);
	if(!pTargetPlayer)
	{
		SetDead(); //销毁特效
		return;
	}

	//动态更新玩家位置
	switch(m_nTargetBind)
	{
	case CChainLightingEffect::eBindLeftHand:
		m_pTarget = pTargetPlayer->GetCharEffectContainer()->GetEffectHelper(eEffectBindPart_LeftHand);
		break;
	case CChainLightingEffect::eBindRightHand:
		m_pTarget = pTargetPlayer->GetCharEffectContainer()->GetEffectHelper(eEffectBindPart_RightHand);
		break;
	case CChainLightingEffect::eBindBody:
		m_pTarget = pTargetPlayer->GetCharEffectContainer()->GetEffectHelper(eEffectBindPart_Body);
		break;
	}

	if(!m_pTarget)
	{
		SetDead();
		return;
	}

	CChainLightingEffect::Update(dwTime,vTargetPos,fDistance);
}

BOOL CChainEffect::LoadSetting( const char* pszFilename, BOOL bMilti  /*= false*/ )
{
	if(!pszFilename)
		return FALSE;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszFilename))
	{
		return false; 
	}

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{
		return false; 
	}

	MeXmlElement* pConfig = pRoot->FirstChildElement("EffectConfig");
	if (pConfig == NULL) 
	{
		return false; 
	}

	const char* var = pConfig->Attribute("Texture");
	if (NULL != var)
		MeSprintf_s(m_texture.szPath,sizeof(m_texture.szPath),"%s",_tstring::toNarrowString(_tstring::UTF8towcs(var).c_str()).c_str());

	const char* pSoundVar = pConfig->Attribute("Sound");
	if(NULL != pSoundVar)
		MeSprintf_s(m_szSound,sizeof(m_szSound),"%s",_tstring::toNarrowString(_tstring::UTF8towcs(pSoundVar).c_str()).c_str());

	int nTemp = 0;
	if ( NULL == pConfig->Attribute("Life",&nTemp) )
		return false;

	m_dwLife = nTemp;

	if(NULL == pConfig->Attribute("FadeOutTime",&m_fFadeOutStart))
		return false;

	if(NULL == pConfig->Attribute("NoiseInterval",&nTemp))
		return false;

	m_dwNoiseInterval = nTemp;

	if(NULL == pConfig->Attribute("Thick",&m_fThick))
		return false;

	if(NULL == pConfig->Attribute("ThickVar",&m_fThickVar))
		return false;

	if(NULL == pConfig->Attribute("FloatSpeed",&m_fFlowSpeed))
		return false;

	if(NULL == pConfig->Attribute("Segment",&m_nNumSegment))
		return false;

	const char* pszAction = pConfig->Attribute("Action");
	if(NULL != pszAction)
	{
		std::string str = _tstring::toNarrowString(_tstring::UTF8towcs(pszAction).c_str());
		if(str.compare("flowin") == 0)
			m_nAction = eActionFlowIn;
		else if(str.compare("flowout") == 0)
			m_nAction = eActionFlowOut;		
	}

	const char* pszBind = pConfig->Attribute("Bind");
	if(NULL != pszBind)
	{
		std::string str = _tstring::toNarrowString(_tstring::UTF8towcs(pszBind).c_str());
		if(str.compare("RightHand") == 0)
			m_nBind = eBindRightHand;
		else if(str.compare("LeftHand") == 0)
			m_nBind = eBindLeftHand;
		else if(str.compare("Body") == 0)
			m_nBind = eBindBody;
	}

	const char* pszTargetBind = pConfig->Attribute("TargetBind");
	if(NULL != pszTargetBind)
	{
		std::string str = _tstring::toNarrowString(_tstring::UTF8towcs(pszTargetBind).c_str());
		if(str.compare("RightHand") == 0)
			m_nTargetBind = eBindRightHand;
		else if(str.compare("RightHand") == 0)
			m_nTargetBind = eBindLeftHand;
		else if(str.compare("Body") == 0)
			m_nTargetBind = eBindBody;
	}

	return TRUE;
}