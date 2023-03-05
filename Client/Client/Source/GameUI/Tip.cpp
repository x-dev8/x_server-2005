/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\Tip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Tip.h"
#include "tstring.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"

#define  TIPCONFIG_PATH   "..\\Data\\Config\\Guide.config"

CUI_ID_FRAME_Tip s_CUI_ID_FRAME_Tip;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Tip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Tip, OnFrameRender )

CUI_ID_FRAME_Tip::CUI_ID_FRAME_Tip()
{
    m_bConfigLoaded = false;
    m_bShowTip = true;
    m_dwShowTime = 0;
    ResetMembers();    
}

void CUI_ID_FRAME_Tip::ResetMembers()
{
    m_pID_FRAME_Tip = NULL;
    m_pID_TEXT_SmallTip = NULL;
}

// Frame
bool CUI_ID_FRAME_Tip::OnFrameRun()
{
    UpdateTipShow();
	return true;
}

bool CUI_ID_FRAME_Tip::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Tip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Tip.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Tip.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Tip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Tip, s_CUI_ID_FRAME_TipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Tip, s_CUI_ID_FRAME_TipOnFrameRender );

	m_pID_FRAME_Tip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Tip );
	m_pID_TEXT_SmallTip = (ControlText*)theUiManager.FindControl( ID_FRAME_Tip, ID_TEXT_SmallTip );

	assert( m_pID_FRAME_Tip );
	assert( m_pID_TEXT_SmallTip );

	m_pID_FRAME_Tip->SetMsgHoldup( false );
	m_pID_TEXT_SmallTip->SetSkipAllMsg( true );

	return true;
}

// 卸载UI
bool CUI_ID_FRAME_Tip::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Tip.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Tip::_IsVisable()
{
	if ( !m_pID_FRAME_Tip )
		return false;
	return m_pID_FRAME_Tip->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Tip::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Tip )
		return;
	m_pID_FRAME_Tip->SetVisable( bVisable );
}

//-------------------   游戏逻辑   --------------------------
void CUI_ID_FRAME_Tip::InitializeAtEnterWorld()
{
    if( LoadTipConfig( TIPCONFIG_PATH ) )
        m_bConfigLoaded = true;
    ResetTips();
    SetVisable( m_bShowTip );
}

void CUI_ID_FRAME_Tip::ResetTips()
{
    std::vector<TipEntrance>::iterator _it = m_entranceVec.begin();
    for( ; _it != m_entranceVec.end(); ++_it )
    {
        _it->nCurrentId = -1;
        _it->nLastId = -1;
        _it->dwNextTime = 0;
        _it->dwLastTime = 0;
        _it->bBegin = false;
        _it->bShow = false;
        _it->nLoopRemain = _it->nLoopCount;
    }
}

void CUI_ID_FRAME_Tip::SetTipShowTime( DWORD dwTime )
{
    m_dwShowTime = dwTime;
}

void CUI_ID_FRAME_Tip::UpdateTipShow()
{
    if( !IsVisable() || !m_bShowTip || !m_bConfigLoaded )
        return;

    DWORD _dwCurTime = HQ_TimeGetTime();
    std::vector<TipEntrance>::iterator _it = m_entranceVec.begin();
    for( ; _it != m_entranceVec.end(); ++_it )
    {
        if( _it->nBeginId < 0 )
        {
            continue;
        }
        else
        {
            if( m_tipMap.count( _it->nBeginId ) == 0 )
                continue;
            if( m_tipMap.find( _it->nBeginId )->second.nDisplayType == CScreenInfoManager::eType_Tip_RandomTip && m_dwShowTime <= 0 )
                continue;
        }

        // 开始此线Tip
        if( !_it->bBegin && _it->nLoopRemain > 0 )
        {
            _it->nCurrentId = _it->nBeginId;
            _it->dwLastTime = _dwCurTime;
            _it->dwNextTime = _it->dwBeginTime;
            _it->bBegin = true;
        }

        // 此线已开始
        if( _it->bBegin && _it->nLoopRemain > 0 ) 
        {
            Tip lastTip;
            if( _it->nLastId >= 0 )
                lastTip = m_tipMap.find( _it->nLastId )->second;

            // 用此UI显示时，此条Tip隐藏
            if( _it->bShow && lastTip.nDisplayType == CScreenInfoManager::eType_Tip_RandomTip
                && _dwCurTime > _it->dwLastTime + m_dwShowTime )
            {
                _it->bShow = false;
                ChangeTipInfo( false );
            }

            // 显示下一条Tip
            if( _it->bBegin && _it->nLoopRemain > 0 && _dwCurTime > _it->dwLastTime + _it->dwNextTime )
            {
                if( _it->nCurrentId == -1 )
                {
                    // 此线下一轮循环
                    _it->nLoopRemain--;
                    if( _it->nLoopRemain <= 0 )
                        continue;
                    _it->nCurrentId = _it->nBeginId;
                    Tip curTip = m_tipMap.find( _it->nCurrentId )->second;
                    _it->bShow = true;
                    _it->dwLastTime = _dwCurTime;
                    _it->dwNextTime = curTip.dwIntervalTime;
                    CScreenInfoManager::Instance()->ShowInfoByType( curTip.nDisplayType, theXmlString.GetString( curTip.nStringId ) );
                    _it->nLastId = _it->nCurrentId;
                    _it->nCurrentId = curTip.nNextTipId;
                }
                else
                {
                    // 此线下一条
                    Tip curTip = m_tipMap.find( _it->nCurrentId )->second;
                    _it->bShow = true;
                    _it->dwLastTime = _dwCurTime;
                    _it->dwNextTime = curTip.dwIntervalTime;
                    CScreenInfoManager::Instance()->ShowInfoByType( curTip.nDisplayType, theXmlString.GetString( curTip.nStringId ) );
                    _it->nLastId = _it->nCurrentId;
                    _it->nCurrentId = curTip.nNextTipId;
                }
            }
        }
    }
}

bool CUI_ID_FRAME_Tip::LoadTipConfig( std::string strFilePath )
{
    if( m_bConfigLoaded )
        return false;

    if( strFilePath.empty() )
        return false;

    MeXmlDocument xMeXml;
    if( !xMeXml.LoadFile( strFilePath.c_str(), 1 ) )
        return false;

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if( NULL == pRoot )
        return false;

    MeXmlElement* pGameTip = pRoot->FirstChildElement( "GameTip" );
    if( NULL == pGameTip )
        return false;

    // 读取 Tip 入口
    MeXmlElement* pEntrances = pGameTip->FirstChildElement( "Entrances" );
    if( NULL == pEntrances )
        return false;
    m_entranceVec.clear();
    MeXmlElement* pEntrance = pEntrances->FirstChildElement( "Entrance" );
    while( NULL != pEntrance )
    {
        TipEntrance tipEtr;
        if( pEntrance->Attribute( "BeginId", &tipEtr.nBeginId ) == NULL )
            return false;
        int _nTime( -1 );
        if( pEntrance->Attribute( "BeginTime", &_nTime ) == NULL )
            return false;
        tipEtr.dwBeginTime = ( DWORD )_nTime * 1000;
        if( pEntrance->Attribute( "LoopCount", &tipEtr.nLoopCount ) == NULL )
            return false;

        if( tipEtr.nBeginId >= 0 && _nTime >= 0 && tipEtr.nLoopCount >= 0 )
            m_entranceVec.push_back( tipEtr );

        pEntrance = pEntrance->NextSiblingElement();
    }
    
    // 读取 Tip
    MeXmlElement* pTips = pGameTip->FirstChildElement( "Tips" );
    if( NULL == pTips )
        return false;
    m_tipMap.clear();
    MeXmlElement* pTip = pTips->FirstChildElement( "Tip" );
    while( NULL != pTip )
    {
        int _nId( -1 );
        if( pTip->Attribute( "Id", &_nId ) == NULL )
            return false;
        Tip tip;
        if( pTip->Attribute( "DisplayType", &tip.nDisplayType ) == NULL )
            return false;
        int _nTime( -1 );
        if( pTip->Attribute( "IntervalTime", &_nTime ) == NULL )
            return false;
        tip.dwIntervalTime = ( DWORD )_nTime * 1000;
        if( pTip->Attribute( "StringId", &tip.nStringId ) == NULL )
            return false;
        if( pTip->Attribute( "NextTipId", &tip.nNextTipId ) == NULL )
            return false;

        if( _nId >= 0 && _nTime >= 0 )
            m_tipMap.insert( make_pair( _nId, tip ) );

        pTip = pTip->NextSiblingElement();
    }

    m_bConfigLoaded = true;
    return true;
}

void CUI_ID_FRAME_Tip::SetShowTip( bool bShow )
{
    if( !bShow )
    {
        ChangeTipInfo( true );
    }
    m_bShowTip = bShow;
    SetVisable( bShow );
}

//------------------    控件逻辑    --------------------
bool CUI_ID_FRAME_Tip::ChangeTipInfo( bool bShow, const std::string& strText )
{
    if( !IsUILoad() || !m_bConfigLoaded )
        return false;

    if( !bShow )
    {
        m_pID_TEXT_SmallTip->SetText( "" );
        return true;
    }

    if( !IsVisable() )
        return false;

    m_pID_TEXT_SmallTip->SetText( strText.c_str() );

    return true;
}
