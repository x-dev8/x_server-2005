#include "ScreenInfoManager.h"
#include "BullSystem.h"
#include "Tip.h"
#include "tstring.h"
#include "Me3d/Global.h"

extern int SCREEN_WIDTH;

CScreenInfoManager::CScreenInfoManager()
{
    m_nMapFrameY = 0;
    m_nMapTextY = 0;
    m_fMapFrameScale = 1.0f;
    m_fMapTextScale = 1.0f;
    m_dwMapStatyTime = 0;
    m_dwMapFadeinTime = 0;
    m_dwMapFadeoutTime = 0;
    m_dwMapNameBeginTime = 0;
    m_bShowMapNameBegin = false;

	m_dwRegionNameBeginTime = 0;
	m_bShowRegionName = false;
}

CScreenInfoManager::~CScreenInfoManager()
{
    m_infoAttrMap.clear();
}

void CScreenInfoManager::Render()
{
    RenderMapName();
	RenderRegionName();
	RenderSafeOrDangerName();
}

void CScreenInfoManager::ShowInfoByType( int nInfoType, const std::string& strText, char* szToName, char* szItemData, int cntHyber, int nBagType )
{
    if( nInfoType < eType_Old_NotProcess || nInfoType >= eType_Max )
    {
        assert( false && "Info type is out of range!" );
        return;
    }

    switch( nInfoType )
    {
    case eType_Old_NotProcess:
        break;
    case eType_OldScreen_BigTitle:
        GetShowScreenText()->_AddBigInfo( strText.c_str(), 0xffffffff, 5000 );
        break;
    case eType_OldScreen_NormalTitle:
        GetShowScreenText()->_AddSingleLineInfo( strText.c_str(), 0xffffffff, 5000 );
        break;
    case eType_OldScreen_Info:
        GetShowScreenText()->_AddMultiLineRiseInfo( strText.c_str(), 0xffffffff, 5000 );
        break;
    case eType_OldScreen_SmallInfo:
        GetShowScreenText()->_AddMultiLineUnRiseInfo( strText.c_str(), 0xffffffff, 5000 );
        break;
    case eType_OldList_Info:
        s_CUI_ID_FRAME_InfoList._AddInfo( strText, 0xffffffff );
        break;
    default:
        {
            if( m_infoAttrMap.count( nInfoType ) == 0 )
            {
                assert( false && "Type not found! Please check in ScreenInfo.config!" );
                return;
            }
            InfoAttribute infoAttr = m_infoAttrMap.find( nInfoType )->second;
            switch( infoAttr.nShowMode )
            {
            case Mode_BigTitle:
                GetShowScreenText()->_AddBigInfo( strText.c_str(), Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ),
                    infoAttr.dwTime );
                break;
            case Mode_SingleLineInfo:
                GetShowScreenText()->_AddSingleLineInfo( strText.c_str(), Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ),
                    infoAttr.dwTime );
                break;
            case Mode_RiseInfo:
                GetShowScreenText()->_AddMultiLineRiseInfo( strText.c_str(), Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ),
                    infoAttr.dwTime, infoAttr.nInfoIndex, infoAttr.bTopLevel, infoAttr.eShowState );
                break;
            case Mode_RightListInfo:
                s_CUI_ID_FRAME_InfoList._AddInfo( strText, Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ),
                    infoAttr.nChatType, szToName, szItemData, cntHyber, nBagType, infoAttr.bAutoReply );
                break;
            case Mode_MultiLineInfo:
                GetShowScreenText()->_AddMultiLineUnRiseInfo( strText.c_str(), Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ),
                    infoAttr.dwTime, infoAttr.nInfoIndex, infoAttr.bTopLevel, infoAttr.eShowState );
                break;
            case Mode_BottomInfo:
                // 待添加
                break;
            case Mode_MessageBoxInfo:
                s_CUI_ID_FRAME_MessageBox.Show( strText.c_str() );
                break;
            case Mode_BullSystem:
                ShowInfoByType( nInfoType, strText, 1 );
                break;
            case Mode_ChatChannel:
                s_CUI_ChatInfoBox.AddInfo( strText, Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ), infoAttr.nChatType );
                break;
            case Mode_RandomTip:
                s_CUI_ID_FRAME_Tip.ChangeTipInfo( true, strText );
                break;
            default:
                assert( false && "ShowMode error in ScreenInfo.config!" );
                break;
            }
        }
        break;
    }
}

void CScreenInfoManager::ShowInfoByType( int nInfoType, const std::string& strText, int nCount, const bool bPushFront )
{
    if( nInfoType < eType_Old_NotProcess || nInfoType >= eType_Max )
    {
        assert( false && "Info type is out of range!" );
        return;
    }
    if( m_infoAttrMap.count( nInfoType ) == 0 )
    {
        assert( false && "Type not found! Please check in ScreenInfo.config!" );
        return;
    }
    InfoAttribute infoAttr = m_infoAttrMap.find( nInfoType )->second;
    if( infoAttr.nShowMode != Mode_BullSystem )
        return;
    s_CUI_ID_FRAME_BullSystem.SetMoveText( strText.c_str(), nCount, Color_Config.getColor( ( ColorConfigure )infoAttr.nColorId ), bPushFront );
}

void CScreenInfoManager::ShowInfoByFormat( int nInfoType, const char* szFormat, ... )
{
    if( !szFormat || !szFormat[0] )
        return;

    va_list	va;
    char szTemp[MAX_PATH] = {0};
    va_start( va, szFormat );
    wvnsprintf( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, szFormat, va );
    va_end( va );

    ShowInfoByType( nInfoType, szTemp );
}

bool CScreenInfoManager::LoadScreenInfoConfig( const std::string& strPath )
{
    if( strPath.empty() )
        return false;

    MeXmlDocument xMeXml;
    if( !xMeXml.LoadFile( strPath.c_str(), 1 ) )
        return false;

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if( NULL == pRoot )
        return false;

    m_infoAttrMap.clear();
    MeXmlElement* pTypes = pRoot->FirstChildElement( "Types" );
    MeXmlElement* pType = pTypes->FirstChildElement( "Type" );
    while( NULL != pType )
    {
        InfoAttribute infoAttr;
        // 基本属性
        int _nId( -1 );
        if( pType->Attribute( "TypeId", &_nId ) == NULL )
            return false;
        if( pType->Attribute( "ShowMode", &infoAttr.nShowMode ) == NULL )
            return false;
        if( pType->Attribute( "ColorId", &infoAttr.nColorId ) == NULL )
            return false;
        int _nTmp( -1 );
        if( pType->Attribute( "Time", &_nTmp ) == NULL )
            return false;
        if( _nId < 0 || _nTmp < 0 || m_infoAttrMap.count( _nId ) > 0 )
            return false;
        infoAttr.dwTime = _nTmp;
        
        // 可选属性
        if( pType->Attribute( "IsTopLevel", &_nTmp ) != NULL )
            infoAttr.bTopLevel = _nTmp;
        if( pType->Attribute( "ShowState", &_nTmp ) != NULL )
            infoAttr.eShowState = _nTmp;
        if( pType->Attribute( "ChatType", &_nTmp ) != NULL )
            infoAttr.nChatType = _nTmp;
        if( pType->Attribute( "AutoReply", &_nTmp ) != NULL )
            infoAttr.bAutoReply = _nTmp;
        if( pType->Attribute( "InfoIndex", &_nTmp ) != NULL )
            infoAttr.nInfoIndex = _nTmp;

        m_infoAttrMap.insert( make_pair( _nId, infoAttr ) );

        pType = pType->NextSiblingElement();
    }
    if( m_infoAttrMap.count( eType_Tip_RandomTip ) > 0 )
        s_CUI_ID_FRAME_Tip.SetTipShowTime( m_infoAttrMap.find( eType_Tip_RandomTip )->second.dwTime );

    // 读场景名配置
    MeXmlElement* pMapNameSet = pRoot->FirstChildElement( "MapNameSetting" );
    if( NULL == pMapNameSet )
        return false;

    MeXmlElement* pPicture = pMapNameSet->FirstChildElement( "Picture" );
    if( NULL == pPicture )
        return false;
    
    const char* pPicPath = pPicture->Attribute( "PicPath" );
    if( NULL == pPicPath )
        return false;
    m_strMapPicPath = Common::_tstring::toNarrowString( Common::_tstring::UTF8towcs( pPicPath ).c_str() );

    if( pPicture->Attribute( "FrameY", &m_nMapFrameY ) == NULL )
        return false;

    if( pPicture->Attribute( "TextY", &m_nMapTextY ) == NULL )
        return false;
    
    if( pPicture->Attribute( "FrameScale", &m_fMapFrameScale ) == NULL )
        return false;

    if( pPicture->Attribute( "TextScale", &m_fMapTextScale ) == NULL )
        return false;

    float fStatyTime, fFadeinTime, fFadeoutTime;
    if( pPicture->Attribute( "StatyTime", &fStatyTime ) == NULL )
        return false;
    
    if( pPicture->Attribute( "FadeinTime", &fFadeinTime ) == NULL )
        return false;

    if( pPicture->Attribute( "FadeOutTime", &fFadeoutTime ) == NULL )
        return false;

    m_dwMapStatyTime = fStatyTime * 1000.0f;
    m_dwMapFadeinTime = fFadeinTime * 1000.0f;
    m_dwMapFadeoutTime = fFadeoutTime * 1000.0f;

	MeXmlElement* pArtFont = pMapNameSet->FirstChildElement( "ArtFont" );
	if (NULL == pArtFont)
	{
		return false;
	}
	
	const char* szArtFont = pArtFont->Attribute("PicPath");
	if (NULL == szArtFont)
	{
		return false;
	}
	m_strArtFont = Common::_tstring::toNarrowString( Common::_tstring::UTF8towcs( szArtFont ).c_str() );

    MeXmlElement* pFrames = pMapNameSet->FirstChildElement( "Frames" );
    if( NULL == pFrames )
        return false;
    m_frameRectMap.clear();
    MeXmlElement* pFrame = pFrames->FirstChildElement( "Frame" );
    while( NULL != pFrame )
    {
        int nId( 0 );
        RECT rc;
        int nTmp( 0 );
        if( pFrame->Attribute( "FrameId", &nId ) == NULL )
            return false;
        if( pFrame->Attribute( "Left", &nTmp ) == NULL )
            return false;
        rc.left = nTmp;
        if( pFrame->Attribute( "Right", &nTmp ) == NULL )
            return false;
        rc.right = nTmp;
        if( pFrame->Attribute( "Top", &nTmp ) == NULL )
            return false;
        rc.top = nTmp;
        if( pFrame->Attribute( "Bottom", &nTmp ) == NULL )
            return false;
        rc.bottom = nTmp;

        if( m_frameRectMap.count( nId ) == 0 )
            m_frameRectMap.insert( make_pair( nId, rc ) );

        pFrame = pFrame->NextSiblingElement();
    }

    MeXmlElement* pTexts = pMapNameSet->FirstChildElement( "Texts" );
    if( NULL == pTexts )
        return false;
    m_textRectMap.clear();
    MeXmlElement* pText = pTexts->FirstChildElement( "Text" );
    while( NULL != pText )
    {
        int nId( 0 );
        RECT rc;
        int nTmp( 0 );
        if( pText->Attribute( "TextId", &nId ) == NULL )
            return false;
        if( pText->Attribute( "Left", &nTmp ) == NULL )
            return false;
        rc.left = nTmp;
        if( pText->Attribute( "Right", &nTmp ) == NULL )
            return false;
        rc.right = nTmp;
        if( pText->Attribute( "Top", &nTmp ) == NULL )
            return false;
        rc.top = nTmp;
        if( pText->Attribute( "Bottom", &nTmp ) == NULL )
            return false;
        rc.bottom = nTmp;

        if( m_textRectMap.count( nId ) == 0 )
            m_textRectMap.insert( make_pair( nId, rc ) );

        pText = pText->NextSiblingElement();
    }

    MeXmlElement* pMaps = pMapNameSet->FirstChildElement( "Maps" );
    if( NULL == pMaps )
        return false;
    m_mapNameMap.clear();
    MeXmlElement* pMap = pMaps->FirstChildElement( "Map" );
    while( NULL != pMap )
    {
        int nId( 0 );
        MapNameSetting mapName;
        if( pMap->Attribute( "Id", &nId ) == NULL )
            return false;
        if( pMap->Attribute( "FrameId", &mapName.nFrameId ) == NULL )
            return false;
        if( pMap->Attribute( "TextId", &mapName.nTextId ) == NULL )
            return false;

        if( m_mapNameMap.count( nId ) == 0 )
            m_mapNameMap.insert( make_pair( nId, mapName ) );

        pMap = pMap->NextSiblingElement();
    }

    return true;
}

void CScreenInfoManager::SetUnRiseInfoBegin()
{
    GetShowScreenText()->SetUnRiseInfoBegin();
}

void CScreenInfoManager::SetUnRiseInfoEnd()
{
    GetShowScreenText()->SetUnRiseInfoEnd();
}

void CScreenInfoManager::ShowMapNameById( int nMapId )
{
    if( m_mapNameMap.count( nMapId ) == 0 )
        return;

    MapNameSetting mapNameSet = m_mapNameMap.find( nMapId )->second;
    if( m_frameRectMap.count( mapNameSet.nFrameId ) == 0 || m_textRectMap.count( mapNameSet.nTextId ) == 0 )
        return;

    m_rcSrcFrame = m_frameRectMap.find( mapNameSet.nFrameId )->second;
    m_rcSrcText = m_textRectMap.find( mapNameSet.nTextId )->second;
    m_dwMapNameBeginTime = HQ_TimeGetTime();
    m_bShowMapNameBegin = true;
}

void CScreenInfoManager::RenderMapName()
{
    if( !m_bShowMapNameBegin )
        return;

    // 时间错误直接返回
    DWORD dwCurrentTiem = HQ_TimeGetTime();
    if( dwCurrentTiem < m_dwMapNameBeginTime )
    {
        m_bShowMapNameBegin = false;
        return;
    }

    DWORD dwPassTime = dwCurrentTiem - m_dwMapNameBeginTime;
    int nAlpha( 0 );
    if( dwPassTime >= 0 && dwPassTime < m_dwMapFadeinTime )
    {
        // 淡入
        nAlpha = 255 * dwPassTime / m_dwMapFadeinTime;
    }
    else if( dwPassTime >= m_dwMapFadeinTime && dwPassTime <= m_dwMapFadeinTime + m_dwMapStatyTime )
    {
        // 正常
        nAlpha = 255;
    }
    else if( dwPassTime > m_dwMapFadeinTime + m_dwMapStatyTime && dwPassTime <= m_dwMapFadeinTime + m_dwMapStatyTime + m_dwMapFadeoutTime )
    {
        // 淡出
        DWORD dwTmp = m_dwMapFadeinTime + m_dwMapStatyTime + m_dwMapFadeoutTime - dwPassTime;
        nAlpha = 255 * dwTmp / m_dwMapFadeoutTime;
    }
    else
    {
        // 显示结束
        m_bShowMapNameBegin = false;
        return;
    }

    // 渲染
    D3DCOLOR dwColor = D3DCOLOR_ARGB( nAlpha, 255, 255, 255 );
    int nPicId = -1;
    RECT rcDestFrame, rcDestText;

    int nDestFrameWidth = ( float )( m_rcSrcFrame.right - m_rcSrcFrame.left ) * m_fMapFrameScale;
    int nDestFrameHeight = ( float )( m_rcSrcFrame.bottom - m_rcSrcFrame.top ) * m_fMapFrameScale;
    rcDestFrame.left = ( SCREEN_WIDTH - nDestFrameWidth ) / 2; 
    rcDestFrame.top = m_nMapFrameY;
    rcDestFrame.right = rcDestFrame.left + nDestFrameWidth;
    rcDestFrame.bottom = rcDestFrame.top + nDestFrameHeight;

    int nDestTextWidth = ( float )( m_rcSrcText.right - m_rcSrcText.left ) * m_fMapTextScale;
    int nDestTextHeight = ( float )( m_rcSrcText.bottom - m_rcSrcText.top ) * m_fMapTextScale;
    rcDestText.left = ( SCREEN_WIDTH - nDestTextWidth ) / 2; 
    rcDestText.top = m_nMapTextY;
    rcDestText.right = rcDestText.left + nDestTextWidth;
    rcDestText.bottom = rcDestText.top + nDestTextHeight;

    char szPicPath[MAX_PATH] = {0};
    MeSprintf_s( szPicPath, sizeof( szPicPath ) / sizeof( char ) - 1, "%s\\%s", GetRootPath(), m_strMapPicPath.c_str() );
    theControlPictureManager.BitBlt( &nPicId, szPicPath, &rcDestFrame, &m_rcSrcFrame, dwColor );
    theControlPictureManager.BitBlt( &nPicId, szPicPath, &rcDestText, &m_rcSrcText, dwColor );
}

void CScreenInfoManager::ShowRegionName(const RECT* pRectFontSrc)
{
	if (!pRectFontSrc)
	{
		return;
	}

	m_dwRegionNameBeginTime = HQ_TimeGetTime();
	m_bShowRegionName = true;
	m_rectArtFontSrc.left = pRectFontSrc->left;
	m_rectArtFontSrc.top = pRectFontSrc->top;
	m_rectArtFontSrc.right = pRectFontSrc->right;
	m_rectArtFontSrc.bottom = pRectFontSrc->bottom;
	CalcDestRect(m_rectArtFontDest, m_rectArtFontSrc, SCREEN_WIDTH / 2, CShowScreenText::m_nBigTitleYPos + (pRectFontSrc->bottom - pRectFontSrc->top) / 2);
}

void CScreenInfoManager::RenderRegionName()
{
	if(!m_bShowRegionName)
		return;

	// 时间错误直接返回
	DWORD dwCurrentTiem = HQ_TimeGetTime();
	if( dwCurrentTiem < m_dwRegionNameBeginTime )
	{
		m_bShowRegionName = false;
		return;
	}

	int nAlpha = 0;
	CalcAlpha(nAlpha, m_dwRegionNameBeginTime, m_bShowRegionName);
	if (!m_bShowRegionName)
	{
		return;
	}

	D3DCOLOR dwColor = D3DCOLOR_ARGB( nAlpha, 255, 255, 255 );
	int nPicId = -1;
	
	char szPicPath[MAX_PATH] = {0};
	MeSprintf_s( szPicPath, sizeof( szPicPath ) / sizeof( char ) - 1, "%s\\%s", GetRootPath(), m_strArtFont.c_str() );
	theControlPictureManager.BitBlt( &nPicId, szPicPath, &m_rectArtFontDest, &m_rectArtFontSrc, dwColor);
}

inline void CScreenInfoManager::CalcAlpha(int &nAlpha, DWORD nStartTime, bool& bShow)
{
	nAlpha = 0;
	DWORD dwCurrentTime = HQ_TimeGetTime();
	DWORD dwPassTime = dwCurrentTime - nStartTime;
	if( dwPassTime >= 0 && dwPassTime < m_dwMapFadeinTime )
	{
		// 淡入
		nAlpha = 255 * dwPassTime / m_dwMapFadeinTime;
	}
	else if( dwPassTime >= m_dwMapFadeinTime && dwPassTime <= m_dwMapFadeinTime + m_dwMapStatyTime )
	{
		// 正常
		nAlpha = 255;
	}
	else if( dwPassTime > m_dwMapFadeinTime + m_dwMapStatyTime && dwPassTime <= m_dwMapFadeinTime + m_dwMapStatyTime + m_dwMapFadeoutTime )
	{
		// 淡出
		DWORD dwTmp = m_dwMapFadeinTime + m_dwMapStatyTime + m_dwMapFadeoutTime - dwPassTime;
		nAlpha = 255 * dwTmp / m_dwMapFadeoutTime;
	}
	else
	{
		// 显示结束
		bShow = false;
		return;
	}
}

inline void CScreenInfoManager::CalcDestRect(IN OUT RECT& rectDest, const RECT& rectSrc, int CenterX, int CenterY)
{
	int nWidth = (float)(rectSrc.right - rectSrc.left) * m_fMapFrameScale;
	int nHeight = (float)(rectSrc.bottom - rectSrc.top) * m_fMapFrameScale;
	rectDest.left = CenterX - nWidth / 2; 
	rectDest.top = CenterY - nHeight / 2;
	rectDest.right = rectDest.left + nWidth;
	rectDest.bottom = rectDest.top + nHeight;		
}

void CScreenInfoManager::RenderSafeOrDangerName()
{
	if(!m_bShowSafeDangerName)
		return;

	// 时间错误直接返回
	DWORD dwCurrentTiem = HQ_TimeGetTime();
	if( dwCurrentTiem < m_dwSafeDangerNameBeginTime )
	{
		m_bShowSafeDangerName = false;
		return;
	}

	int nAlpha = 0;
	CalcAlpha(nAlpha, m_dwSafeDangerNameBeginTime, m_bShowSafeDangerName);
	if (!m_bShowSafeDangerName)
	{
		return;
	}

	D3DCOLOR dwColor = D3DCOLOR_ARGB( nAlpha, 255, 255, 255 );
	int nPicId = -1;

	char szPicPath[MAX_PATH] = {0};
	MeSprintf_s( szPicPath, sizeof( szPicPath ) / sizeof( char ) - 1, "%s\\%s", GetRootPath(), m_strArtFont.c_str() );
	theControlPictureManager.BitBlt( &nPicId, szPicPath, &m_rectDest, &m_rectSrc, dwColor);	
}

const int yOffset = 40;
void CScreenInfoManager::ShowSafeOrDangerName(const RECT* pRectFontSrc)
{
	if (!pRectFontSrc)
	{
		return;
	}

	m_dwSafeDangerNameBeginTime = HQ_TimeGetTime();
	m_bShowSafeDangerName = true;
	m_rectSrc.left = pRectFontSrc->left;
	m_rectSrc.top = pRectFontSrc->top;
	m_rectSrc.right = pRectFontSrc->right;
	m_rectSrc.bottom = pRectFontSrc->bottom;
	CalcDestRect(m_rectDest, m_rectSrc, SCREEN_WIDTH / 2, CShowScreenText::m_nSysInfoYPos + yOffset);	
}