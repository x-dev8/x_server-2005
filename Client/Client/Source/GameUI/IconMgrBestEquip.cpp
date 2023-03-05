#include "IconMgrBestEquip.h"
#include "PlayerRole.h"
#include "../GamePlay/FindBestEquip.h"
#include "GlobalDef.h"
#include "GameDefineChar.h"
#include "color_config.h"
#include "MeFont/MeFontSystem.h"
#include "tstring.h"
#include "CommonChatFrame.h"
#include "IconManagerClient.h"
#include "XmlStringLanguage.h"


class S_IconInfoBase;

IconMgrBestEquip::IconMgrBestEquip():
mCurLine( -1 ),
mIsShow( false ),
mFlag( FLAG_HIDEING )
{
	mRenderPt.x = 500;
	mRenderPt.y = 500;
}

IconMgrBestEquip::~IconMgrBestEquip()
{

}

void IconMgrBestEquip::Clear()
{
	for ( int idx = 0; idx < mCurLine; ++idx )
	{
		mAllStr[idx].Clear();
	}
	mCurLine = -1;
}

bool IconMgrBestEquip::FullOneLine( const char* info, DWORD align, DWORD col )
{
	++mCurLine;

	if ( !Check( mCurLine ) )
	{
		return false;
	}

	mAllStr[mCurLine].mColor	= col;
	mAllStr[mCurLine].mAlign	= align;
	mAllStr[mCurLine].mStr		= info;

	return true;
}

bool IconMgrBestEquip::ParseInfo( std::string& info, DWORD col )
{
	std::wstring::size_type begin = 0;
	std::wstring::size_type pos = 0;

	std::wstring tempWString = Common::_tstring::toWideString( info.c_str() );

	while( ( pos = tempWString.find(L"\\n", begin) ) != std::wstring::npos )
	{
		mCurLine++;
		if ( !Check( mCurLine ) )
		{
			return false;
		}

		std::wstring temp = tempWString.substr( begin, pos - begin );
		mAllStr[mCurLine].mStr = Common::_tstring::toNarrowString( temp.c_str() );
		mAllStr[mCurLine].mColor = col;
		mAllStr[mCurLine].mAlign = DT_NOCLIP;
		begin = pos + 1;
	}

	return true;
}

void IconMgrBestEquip::RenderMakeup( int fontIdx )
{
	int maxCount = 0;
	int maxIdx = 0;
	for ( int idx = 0; idx <= mCurLine; ++idx )
	{
		int len = mAllStr[idx].mStr.length();

		if ( maxCount < len )
		{
			maxIdx = idx;
			maxCount = len;
		}
	}


	std::wstring tempWString = Common::_tstring::toWideString( mAllStr[maxIdx].mStr.c_str() );

	int fMaxWidth = FontSystem::GetTextWidth( fontIdx, tempWString, 0, tempWString.length(), false );
	int fMaxHeight = FontSystem::GetFontHeight( fontIdx );

	int beginX = mRenderPt.x + OFFSET_W;
	int beginY = mRenderPt.y + OFFSET_H;

	for ( int idx = 0; idx <= mCurLine; ++idx )
	{
		mAllStr[idx].mRect.left		= beginX;
		mAllStr[idx].mRect.top		= beginY + ( fMaxHeight + OFFSET_LINE) *idx ;
		mAllStr[idx].mRect.right	= mAllStr[idx].mRect.left + fMaxWidth;
		mAllStr[idx].mRect.bottom	= mAllStr[idx].mRect.top + fMaxHeight*( idx + 1 );
	}

	mRect.left	= mRenderPt.x;
	mRect.top	= mRenderPt.y;
	mRect.right	= mRect.left + fMaxWidth + 2 * OFFSET_W;
	mRect.bottom= mRect.top + ( fMaxHeight + OFFSET_LINE ) * ( mCurLine + 1 ) + 2 * OFFSET_H;
}

void IconMgrBestEquip::Render()
{
	if ( !mIsShow || mCurLine == -1 )
	{
		return ;
	}

	FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
	if( FontSystem::IsUseNewFont() )
	{
		eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
		FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_FIRST );	
		FontRender::getFontRender()->ClearRender( FontRender::EFR_FIRST );
	}
	
	for ( int idx = 0; idx <= mCurLine; idx++ )
	{
		FontSystem::DrawText( mAllStr[idx].mStr.c_str(), &mAllStr[idx].mRect, mAllStr[idx].mAlign, mAllStr[idx].mColor, mFontId );
	}

	int temp = -1;
	theControlPictureManager.RenderNineGrid( temp, TIP_FRAME_FILENAME,
												TIP_FRAME_TOTALWIDTH, TIP_FRAME_TOTALHEIGHT,
												TIP_FRAME_GRIDWIDTH, TIP_FRAME_GRIDHEIGHT,
												&mRect );

	if( FontSystem::IsUseNewFont() )
	{
		FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
		FontSystem::DoRender( FontRender::EFR_FIRST );
	}	
}

void IconMgrBestEquip::SetData( EArmType CareerId, EEquipPartType PartId, int Level )
{
	//================================
	// ²âÊÔ´úÂë
	//CareerId = EArmType_Warrior;
	//PartId = EEquipPartType_Weapon;
	//Level = 2;
	//================================

	EquipInfo info;
	int itemId = FindBestEquip::Instance()->FindEquipInfo( CareerId, PartId, Level, info );

	ItemDefine::SItemCommon* pCommon = (ItemDefine::SItemCommon*)GettheItemDetail().GetItemByID( itemId );

	if ( pCommon == NULL )
	{
		Clear();
		return ;
	}

	Clear();

	// 
	DWORD qualityColor = S_IconInfoHero::GetQualityColor( pCommon->ustLevel );

	FullOneLine( theXmlString.GetString(eText_BestEquip1), DT_CENTER|DT_NOCLIP, qualityColor );

	FullOneLine( pCommon->GetItemName(), DT_NOCLIP, qualityColor );

	ItemDefine::SItemCanEquip* pEquip = (ItemDefine::SItemCanEquip*)pCommon;
	char temp[256] = {0};
	sprintf( temp, theXmlString.GetString(eText_BestEquip2), pCommon->ustLevel, pEquip->stEquipLevelReq );

	FullOneLine( temp, DT_NOCLIP, qualityColor );

	memset( temp, 0, sizeof(temp) );
	sprintf( temp, theXmlString.GetString(eText_BestEquip3), pCommon->GetItemName() );

	FullOneLine( temp, DT_NOCLIP, Color_Config.getColor(CC_BESTEQUIP_GETMODE) );


	for ( int idx = 0; idx < MAX_INFOCOUNT; ++idx )
	{
		ParseInfo( info.mAllInfo[idx], Color_Config.getColor( (ColorConfigure)( CC_BESTEQUIP_INFO + idx ) ) );
	}

	mFontId = CommonChatFrame::GetActiveChatFrame()->GetFontIndex();
	
	RenderMakeup( mFontId );
}


