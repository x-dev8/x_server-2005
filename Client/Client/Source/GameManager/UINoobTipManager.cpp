/***********************************************************
		Create by ZhuoMeng.Hu		[9/16/2010]			
					UI新手帮助Tip
***********************************************************/

#include "UINoobTipManager.h"
#include "ChatInfoBox.h"
#include "XmlStringLanguage.h"
#include "GameSetting.h"
#include "meui/ExpressionManager.h"

extern DWORD HQ_TimeGetTime();

/***********************	Public		***************************/
const char* ePicName[ CIntroductionManager::eTotalFrameType ] =
{
	"common\\HelpTipLeftBottom.tga",
	"common\\HelpTipLeftTop.tga",
	"common\\HelpTipRightBottom.tga",
	"common\\HelpTipRightTop.tga",
};

const RECT cstRcFrame				= {  0,  0, 200, 130 };
const RECT cstRcText				= {  0,  0, 180, 70 };
const RECT cstRcOutPic				= {  0,  0,  61, 100 };
const RECT cstRcInLeftTopPic		= { 10, 10,  30,  30 };
const RECT cstRcInLeftBottomPic		= { 10, 70,  30,  90 };
const RECT cstRcInRightTopPic		= { 30, 10,  50,  30 };
const RECT cstRcInRightBottomPic	= { 30, 70,  50,  90 };

/***********************	NoobTip		***************************/
CUINoobTipManager::NoobTip::NoobTip()
{
	pFrame = NULL;
	pText = NULL;
	pFather = NULL;
    strUIFrameName.clear();
    strUIControlName.clear();
	nIntroId = 0;
	bShow = false;
	nFrameType = CIntroductionManager::eLeftTop;
	nStrId = -1;
	nBeginTime = 0;
	nLastTime = 0;
    nInnerLeft = 0;
    nInnerTop = 0;
    nInnerRight = 0;
    nInnerBottom = 0;
}

void CUINoobTipManager::NoobTip::SetTipFormat( int type )
{
	if( !pFather || !pFrame || !pText )
		return;
	
	RECT rcFather;
	pFather->GetRealRect( &rcFather );
	int nFrameWidth = pFrame->GetWidth(),nFrameHeight = pFrame->GetHeight();
	int nTextWidth  = pText->GetWidth(),nTextHeight = pText->GetHeight();

	int nMargin = (nFrameWidth - nTextWidth)/2;
	int nFrameX, nFrameY, nTextX, nTextY;
	S_BaseData::S_Pic pic;
	
	// 以下 RECT 常量的	right = 宽,  bottom = 高
	switch( type )
	{
	case CIntroductionManager::eLeftTop:
		nFrameX = rcFather.left - nFrameWidth + this->nInnerLeft;
		nFrameY = rcFather.top - nFrameHeight + this->nInnerTop;
		nTextX = nFrameX + nMargin;
		nTextY = nFrameY + nMargin;
		pic.SetPicStruct( ePicName[type], &cstRcOutPic, &cstRcInLeftTopPic );
		break;
	case CIntroductionManager::eLeftBottom:
		nFrameX = rcFather.left - nFrameWidth + this->nInnerLeft;
		nFrameY = rcFather.bottom - this->nInnerBottom;
		nTextX = nFrameX + nMargin;
		nTextY = nFrameY + nFrameHeight - nTextHeight - nMargin;
		pic.SetPicStruct( ePicName[type], &cstRcOutPic, &cstRcInLeftBottomPic );
		break;
	case CIntroductionManager::eRightTop:
		nFrameX = rcFather.right - this->nInnerRight;
		nFrameY = rcFather.top - nFrameHeight + this->nInnerTop;
		nTextX = nFrameX + nMargin;
		nTextY = nFrameY + nMargin;
		pic.SetPicStruct( ePicName[type], &cstRcOutPic, &cstRcInRightTopPic );
		break;
	case CIntroductionManager::eRightBottom:
		nFrameX = rcFather.right - this->nInnerRight;
		nFrameY = rcFather.bottom - this->nInnerBottom;
		nTextX = nFrameX + nMargin;
		nTextY = nFrameY + nFrameHeight - nTextHeight - nMargin;
		pic.SetPicStruct( ePicName[type], &cstRcOutPic, &cstRcInRightBottomPic );
		break;
	default:
		nFrameX = rcFather.left - nFrameWidth + this->nInnerLeft;
		nFrameY = rcFather.top - nFrameHeight + this->nInnerTop;
		nTextX = nFrameX + nMargin;
		nTextY = nFrameY + nMargin;
		pic.SetPicStruct( ePicName[type], &cstRcOutPic, &cstRcInLeftTopPic );
		break;
	}
	
	pFrame->SetPos( nFrameX, nFrameY );
	pFrame->SetPic( &pic, true );
	pText->SetPos( nTextX, nTextY );
	S_BaseData* pData = pFrame->GetData();
	for( int i = 0; i < S_BaseData::Mode_Max; i++ )
	{
		pData->m_nDrawMode[i] = DrawModeStrectch;
	}
}

void CUINoobTipManager::NoobTip::AdjustTipFormat()
{
	if( !pFather || !pFrame || !pText )
		return;

	RECT rc;
	pFrame->GetRealRect( &rc );
	if( rc.left < 0 )
	{
		if( rc.top < 0 )
			SetTipFormat( CIntroductionManager::eRightBottom );
		else if( rc.bottom > SCREEN_HEIGHT )
			SetTipFormat( CIntroductionManager::eRightTop );
		else if( nFrameType == CIntroductionManager::eLeftTop )
			SetTipFormat( CIntroductionManager::eRightTop );
		else if( nFrameType == CIntroductionManager::eLeftBottom )
			SetTipFormat( CIntroductionManager::eRightBottom );
	}
	else if( rc.right > SCREEN_WIDTH )
	{
		if( rc.top < 0 )
			SetTipFormat( CIntroductionManager::eLeftBottom );
		else if( rc.bottom > SCREEN_HEIGHT )
			SetTipFormat( CIntroductionManager::eLeftTop );
		else if( nFrameType == CIntroductionManager::eRightTop )
			SetTipFormat( CIntroductionManager::eLeftTop );
		else if( nFrameType == CIntroductionManager::eRightBottom )
			SetTipFormat( CIntroductionManager::eLeftBottom );
	}
	else if( rc.top < 0 )
	{
		if( nFrameType == CIntroductionManager::eLeftTop )
			SetTipFormat( CIntroductionManager::eLeftBottom );
		else if( nFrameType == CIntroductionManager::eRightTop )
			SetTipFormat( CIntroductionManager::eRightBottom );
	}
	else if( rc.bottom > SCREEN_HEIGHT )
	{
		if( nFrameType == CIntroductionManager::eLeftBottom )
			SetTipFormat( CIntroductionManager::eLeftTop );
		else if( nFrameType == CIntroductionManager::eRightBottom )
			SetTipFormat( CIntroductionManager::eRightTop );
	}
}

/***********************	CUINoobTipManager	***********************/
CUINoobTipManager::CUINoobTipManager()
{
}

CUINoobTipManager::~CUINoobTipManager()
{
    DestroyControls();
    m_noobTipVec.clear();
}

void CUINoobTipManager::InitNoobTips( const IntroductionList& introVec )
{
	m_noobTipVec.clear();
	for( IntroductionListIterator it = introVec.begin(); it != introVec.end(); it++ )
	{
		if( ( *it )->GetIntroductionType() != CIntroductionManager::eUITip )
			continue;
		
		NoobTip nbTip;
		CIntroductionManager::SUITip* pUITip = static_cast<CIntroductionManager::SUITip*>( *it );
		nbTip.strUIFrameName = pUITip->strUIName;
        nbTip.strUIControlName = pUITip->strControlName;
		nbTip.nIntroId = pUITip->nIntroId;
		nbTip.nStrId = pUITip->nStringId;
		nbTip.nFrameType = pUITip->nFrameType;
		nbTip.nLastTime = pUITip->nLastTime;
        nbTip.nInnerLeft = pUITip->nInnerLeft;
        nbTip.nInnerTop = pUITip->nInnerTop;
        nbTip.nInnerRight = pUITip->nInnerRight;
        nbTip.nInnerBottom = pUITip->nInnerBottom;
		m_noobTipVec.push_back( nbTip );
	}
}

bool CUINoobTipManager::CreateControl( int introId )
{
	NoobTip* pNbTip = FindNoobTipById( introId );
	if( !pNbTip )
		return false;
	if( pNbTip->pFrame && pNbTip->pText )
		return false;

	pNbTip->pFrame = MeNew ControlFrame;
	pNbTip->pFrame->Create( &cstRcFrame );
	pNbTip->pText = MeNew ControlText;
	pNbTip->pText->Create( &cstRcText, 0xFFFFFFFF );
	pNbTip->SetTipFormat( pNbTip->nFrameType );
	pNbTip->pText->SetFont( s_CUI_ChatInfoBox.GetEditInput() );
    std::string strInfo = theXmlString.GetString( pNbTip->nStrId );
    ExpressionManager::GetInstance().AddExpressionAni( strInfo );
	pNbTip->pText->SetText( strInfo );
	pNbTip->pFrame->AppendChild( pNbTip->pText );
	return true;
}

void CUINoobTipManager::DestroyControls()
{
    for( NoobTipListIterator it = m_noobTipVec.begin(); it != m_noobTipVec.end(); ++it )
    {
        it->bShow = false;
        it->nBeginTime = 0;
        if( it->pFrame )
        {
            SAFE_DELETE( it->pFrame );
            it->pFrame = NULL;
            it->pText = NULL;
        }
    }
}

CUINoobTipManager::NoobTip* CUINoobTipManager::FindNoobTipById( int introId )
{
	for( NoobTipListIterator it = m_noobTipVec.begin(); it != m_noobTipVec.end(); ++it )
	{
		if( it->nIntroId == introId )
			return &( *it );
	}
	return NULL;
}

void CUINoobTipManager::RefreshTipList()
{
    if( false == GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ) )
        return;

    IntroductionStack& IntroStack = CIntroductionManager::Instance()->GetIntroStack();
    IntroductionStackIterator stackIt = IntroStack.begin();
    for( ; stackIt != IntroStack.end(); stackIt++ )
    {
        if( CIntroductionManager::eUITip != ( *stackIt )->GetIntroductionType() )
            continue;

        for( NoobTipListIterator nbIt = m_noobTipVec.begin(); nbIt != m_noobTipVec.end(); nbIt++ )
        {
            if( ( ( *stackIt )->nIntroId == nbIt->nIntroId ) && ( nbIt->bShow == false ) )
            {
                nbIt->bShow = true;
                break;
            }
        }
    }
}

void CUINoobTipManager::Render()
{
	DWORD currentTime = HQ_TimeGetTime();
	for( NoobTipListIterator it = m_noobTipVec.begin(); it != m_noobTipVec.end(); ++it )
	{
		if( it->bShow == true )
		{
            it->pFather = theUiManager.FindControl( it->strUIFrameName.c_str(), it->strUIControlName.c_str() );
            if( !it->pFather || ( it->pFather && it->pFather->GetFrameFather() && !it->pFather->GetFrameFather()->IsVisable() ) )
            {
                //界面关闭
                if( it->nBeginTime != 0 )
                {
                    it->bShow = false;
                    it->nBeginTime = 0;
                    CIntroductionManager::Instance()->EraseUITipById( it->nIntroId );
                }
                continue;
            }

			if( !it->pFather->GetFrameFather() )
				continue;

			if( it->pFather->GetFrameFather()->IsVisable() && it->pFather->IsVisable() )
			{
				if( it->nBeginTime == 0 )
				{
					//界面打开，计时开始
					if( !it->pFrame || !it->pText )
						CreateControl( it->nIntroId );
					it->bShow = true;
					it->nBeginTime = currentTime;
				}
				else
				{
					//是否到时
					if( ( it->nLastTime != 0 ) && ( it->nBeginTime + static_cast<DWORD>( it->nLastTime * 1000 ) < currentTime ) )
					{
						it->bShow = false;
						it->nBeginTime = 0;
						CIntroductionManager::Instance()->EraseUITipById( it->nIntroId );
					}
				}

				if( !it->pFrame || !it->pText )
					continue;

                // 渲染
				it->SetTipFormat( it->nFrameType );
				it->AdjustTipFormat();
				it->pFrame->Render();
			}
		}
	}
}
