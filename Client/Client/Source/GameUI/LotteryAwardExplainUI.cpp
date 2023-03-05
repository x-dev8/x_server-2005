/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\盒子\LotteryAwardExplain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "LotteryAwardExplainUI.h"
#include "RapidXml/MeRapidXml.h"
#include "Cfg.h"

CUI_ID_FRAME_LotteryAwardExplain s_CUI_ID_FRAME_LotteryAwardExplain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LotteryAwardExplain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LotteryAwardExplain, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryAwardExplain, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryAwardExplain, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LotteryAwardExplain, ID_BUTTON_CLOSEOnButtonClick )

static int s_nIndex = 0;
CUI_ID_FRAME_LotteryAwardExplain::CUI_ID_FRAME_LotteryAwardExplain()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_LotteryAwardExplain::ResetMembers()
{
	m_pID_FRAME_LotteryAwardExplain = NULL;
	m_pID_PICTURE_LotteryBackground1 = NULL;
	m_pID_PICTURE_LotteryBackground2 = NULL;
	m_pID_PICTURE_LotteryBackground3 = NULL;
	m_pID_PICTURE_LotteryBackground4 = NULL;
	m_pID_PICTURE_LotteryBackground5 = NULL;
	m_pID_PICTURE_LotteryBackground6 = NULL;
	m_pID_LISTIMG_Item1 = NULL;
	m_pID_LISTIMG_Item2 = NULL;
	m_pID_LISTIMG_Item3 = NULL;
	m_pID_LISTIMG_Item4 = NULL;
	m_pID_LISTIMG_Item5 = NULL;
	m_pID_LISTIMG_Item6 = NULL;
	m_pID_LISTIMG_Item7 = NULL;
	m_pID_LISTIMG_Item8 = NULL;
	m_pID_LISTIMG_Item9 = NULL;
	m_pID_LISTIMG_Item10 = NULL;
	m_pID_LISTIMG_Item11 = NULL;
	m_pID_LISTIMG_Item12 = NULL;
	m_pID_LISTIMG_Item13 = NULL;
	m_pID_LISTIMG_Item14 = NULL;
	m_pID_LISTIMG_Item15 = NULL;
	m_pID_LISTIMG_Item16 = NULL;
	m_pID_LISTIMG_Item17 = NULL;
	m_pID_LISTIMG_Item18 = NULL;
	m_pID_LISTIMG_Item19 = NULL;
	m_pID_LISTIMG_Item20 = NULL;
	m_pID_LISTIMG_Item21 = NULL;
	m_pID_LISTIMG_Item22 = NULL;
	m_pID_LISTIMG_Item23 = NULL;
	m_pID_LISTIMG_Item24 = NULL;
//	m_pID_PICTURE_GetAwardLight = NULL;
	m_pID_PICTURE_FinallyAward = NULL;
	m_pID_LISTIMG_Chest = NULL;
	m_pID_LISTIMG_Key = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_CLOSE = NULL;

}
// Frame
bool CUI_ID_FRAME_LotteryAwardExplain::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_LotteryAwardExplain::OnFrameRender()
{
	SetCurrentBg( s_nIndex );
	if( s_nIndex >=0 && s_nIndex < m_kBoxKeys.size() )
		UpdateRewards( m_kBoxKeys[s_nIndex] );
	return true;
}
// Button
bool CUI_ID_FRAME_LotteryAwardExplain::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryAwardExplain)
		return false;
	s_nIndex --;
	s_nIndex = max( 0, s_nIndex );
	return true;
}
// Button
bool CUI_ID_FRAME_LotteryAwardExplain::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryAwardExplain)
		return false;
	s_nIndex ++;
	//减2是去掉了第7个等级
	s_nIndex = min( ECD_Max_BoxLevel - 2, s_nIndex );
	return true;
}
// Button
bool CUI_ID_FRAME_LotteryAwardExplain::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_LotteryAwardExplain)
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_LotteryAwardExplain::_LoadUI()
{
	LoadConfig();

	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\LotteryAwardExplain.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\LotteryAwardExplain.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_LotteryAwardExplain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_LotteryAwardExplain, s_CUI_ID_FRAME_LotteryAwardExplainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LotteryAwardExplain, s_CUI_ID_FRAME_LotteryAwardExplainOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_LotteryAwardExplain, ID_BUTTON_Left, s_CUI_ID_FRAME_LotteryAwardExplainID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LotteryAwardExplain, ID_BUTTON_Right, s_CUI_ID_FRAME_LotteryAwardExplainID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LotteryAwardExplain, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_LotteryAwardExplainID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_LotteryAwardExplain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LotteryAwardExplain );
	m_pID_PICTURE_LotteryBackground1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground1 );
	m_pID_PICTURE_LotteryBackground2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground2 );
	m_pID_PICTURE_LotteryBackground3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground3 );
	m_pID_PICTURE_LotteryBackground4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground4 );
	m_pID_PICTURE_LotteryBackground5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground5 );
	m_pID_PICTURE_LotteryBackground6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_LotteryBackground6 );
	m_pID_LISTIMG_Item1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item1 );
	m_pID_LISTIMG_Item2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item2 );
	m_pID_LISTIMG_Item3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item3 );
	m_pID_LISTIMG_Item4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item4 );
	m_pID_LISTIMG_Item5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item5 );
	m_pID_LISTIMG_Item6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item6 );
	m_pID_LISTIMG_Item7 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item7 );
	m_pID_LISTIMG_Item8 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item8 );
	m_pID_LISTIMG_Item9 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item9 );
	m_pID_LISTIMG_Item10 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item10 );
	m_pID_LISTIMG_Item11 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item11 );
	m_pID_LISTIMG_Item12 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item12 );
	m_pID_LISTIMG_Item13 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item13 );
	m_pID_LISTIMG_Item14 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item14 );
	m_pID_LISTIMG_Item15 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item15 );
	m_pID_LISTIMG_Item16 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item16 );
	m_pID_LISTIMG_Item17 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item17 );
	m_pID_LISTIMG_Item18 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item18 );
	m_pID_LISTIMG_Item19 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item19 );
	m_pID_LISTIMG_Item20 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item20 );
	m_pID_LISTIMG_Item21 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item21 );
	m_pID_LISTIMG_Item22 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item22 );
	m_pID_LISTIMG_Item23 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item23 );
	m_pID_LISTIMG_Item24 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Item24 );
	//m_pID_PICTURE_GetAwardLight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_GetAwardLight );
	m_pID_PICTURE_FinallyAward = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_PICTURE_FinallyAward );
	m_pID_LISTIMG_Chest = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Chest );
	m_pID_LISTIMG_Key = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_LISTIMG_Key );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_BUTTON_Left );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_BUTTON_Right );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_LotteryAwardExplain, ID_BUTTON_CLOSE );
	assert( m_pID_FRAME_LotteryAwardExplain );
	assert( m_pID_PICTURE_LotteryBackground1 );
	assert( m_pID_PICTURE_LotteryBackground2 );
	assert( m_pID_PICTURE_LotteryBackground3 );
	assert( m_pID_PICTURE_LotteryBackground4 );
	assert( m_pID_PICTURE_LotteryBackground5 );
	assert( m_pID_PICTURE_LotteryBackground6 );
	assert( m_pID_LISTIMG_Item1 );
	assert( m_pID_LISTIMG_Item2 );
	assert( m_pID_LISTIMG_Item3 );
	assert( m_pID_LISTIMG_Item4 );
	assert( m_pID_LISTIMG_Item5 );
	assert( m_pID_LISTIMG_Item6 );
	assert( m_pID_LISTIMG_Item7 );
	assert( m_pID_LISTIMG_Item8 );
	assert( m_pID_LISTIMG_Item9 );
	assert( m_pID_LISTIMG_Item10 );
	assert( m_pID_LISTIMG_Item11 );
	assert( m_pID_LISTIMG_Item12 );
	assert( m_pID_LISTIMG_Item13 );
	assert( m_pID_LISTIMG_Item14 );
	assert( m_pID_LISTIMG_Item15 );
	assert( m_pID_LISTIMG_Item16 );
	assert( m_pID_LISTIMG_Item17 );
	assert( m_pID_LISTIMG_Item18 );
	assert( m_pID_LISTIMG_Item19 );
	assert( m_pID_LISTIMG_Item20 );
	assert( m_pID_LISTIMG_Item21 );
	assert( m_pID_LISTIMG_Item22 );
	assert( m_pID_LISTIMG_Item23 );
	assert( m_pID_LISTIMG_Item24 );
	//assert( m_pID_PICTURE_GetAwardLight );
	assert( m_pID_PICTURE_FinallyAward );
	assert( m_pID_LISTIMG_Chest );
	assert( m_pID_LISTIMG_Key );
	assert( m_pID_BUTTON_Left );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_CLOSE );

	memset( m_apBackground, 0, sizeof( m_apBackground ) );
	m_apBackground[0] = m_pID_PICTURE_LotteryBackground1;
	m_apBackground[1] = m_pID_PICTURE_LotteryBackground2;
	m_apBackground[2] = m_pID_PICTURE_LotteryBackground3;
	m_apBackground[3] = m_pID_PICTURE_LotteryBackground4;
	m_apBackground[4] = m_pID_PICTURE_LotteryBackground5;
	m_apBackground[5] = m_pID_PICTURE_LotteryBackground6;

	memset( m_apRewardControl, 0, sizeof( m_apRewardControl ) );
	m_apRewardControl[0] = m_pID_LISTIMG_Item1;
	m_apRewardControl[1] = m_pID_LISTIMG_Item2;
	m_apRewardControl[2] = m_pID_LISTIMG_Item3;
	m_apRewardControl[3] = m_pID_LISTIMG_Item4;
	m_apRewardControl[4] = m_pID_LISTIMG_Item5;
	m_apRewardControl[5] = m_pID_LISTIMG_Item6;
	m_apRewardControl[6] = m_pID_LISTIMG_Item7;
	m_apRewardControl[7] = m_pID_LISTIMG_Item8;
	m_apRewardControl[8] = m_pID_LISTIMG_Item9;
	m_apRewardControl[9] = m_pID_LISTIMG_Item10;
	m_apRewardControl[10] = m_pID_LISTIMG_Item11;
	m_apRewardControl[11] = m_pID_LISTIMG_Item12;
	m_apRewardControl[12] = m_pID_LISTIMG_Item13;
	m_apRewardControl[13] = m_pID_LISTIMG_Item14;
	m_apRewardControl[14] = m_pID_LISTIMG_Item15;
	m_apRewardControl[15] = m_pID_LISTIMG_Item16;
	m_apRewardControl[16] = m_pID_LISTIMG_Item17;
	m_apRewardControl[17] = m_pID_LISTIMG_Item18;
	m_apRewardControl[18] = m_pID_LISTIMG_Item19;
	m_apRewardControl[19] = m_pID_LISTIMG_Item20;
	m_apRewardControl[20] = m_pID_LISTIMG_Item21;
	m_apRewardControl[21] = m_pID_LISTIMG_Item22;
	m_apRewardControl[22] = m_pID_LISTIMG_Item23;
	m_apRewardControl[23] = m_pID_LISTIMG_Item24;	
	for( int i = 0 ; i < ECD_Max_TreasureCount ; ++ i )
	{
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->SetEnableDrag( false );
	}
		SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_LotteryAwardExplain::_UnLoadUI()
{
	m_kBoxKeys.clear();
	m_pID_FRAME_LotteryAwardExplain = NULL;
	memset( m_apBackground, 0, sizeof( m_apBackground ) );
	memset( m_apRewardControl, 0, sizeof( m_apRewardControl ) );
    ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\LotteryAwardExplain.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_LotteryAwardExplain::_IsVisable()
{
    if(!m_pID_FRAME_LotteryAwardExplain)
        return false;

	return m_pID_FRAME_LotteryAwardExplain->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_LotteryAwardExplain::_SetVisable( const bool bVisable )
{
	s_nIndex = 0;
    if(m_pID_FRAME_LotteryAwardExplain)
	    m_pID_FRAME_LotteryAwardExplain->SetVisable( bVisable );
}
void CUI_ID_FRAME_LotteryAwardExplain::UpdateRewards( const BoxKey& bk )
{
	m_pID_LISTIMG_Chest->Clear();
	m_pID_LISTIMG_Key->Clear();

	for( int i = 0 ; i < ECD_Max_TreasureCount; ++ i )
	{	
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->Clear();
	}

	//set chest and key item
	ControlListImage::S_ListImg kImg;
	kImg.SetData( bk.nOriginalBoxId, 1 );
	m_pID_LISTIMG_Chest->SetItem( &kImg );
	kImg.Clear();
	kImg.SetData( bk.nKeyId, 1 );
	m_pID_LISTIMG_Key->SetItem( &kImg );
	
	// set treasure
	for( int i = 0 ; i < ECD_Max_TreasureCount; ++ i )
	{
		const TreasureData* pData = theTreasureBoxConfig.GetTreasureData( bk.nLevel, bk.nBoxId, i );
		if( !pData )
			continue;
		ControlListImage::S_ListImg kImg;
		kImg.SetData( pData->GetItemID(), pData->GetCount(), eIcon_Enable, true );
		if( m_apRewardControl[i] )
			m_apRewardControl[i]->SetItem( &kImg );
	}
}
void CUI_ID_FRAME_LotteryAwardExplain::SetCurrentBg( int nIndex )
{
	for( int i = 0 ; i < ECD_Max_BoxLevel ; ++ i )
	{
		if( m_apBackground[i] )
			m_apBackground[i]->SetVisable( false );
	}
	if( nIndex < 0 )
		return;
	nIndex = min( nIndex, ECD_Max_BoxLevel - 1 );
	if( m_apBackground[nIndex] )
		m_apBackground[nIndex]->SetVisable( true );
}
void CUI_ID_FRAME_LotteryAwardExplain::LoadConfig()
{
	m_kBoxKeys.clear();
	MeXmlDocument	doc;
	if( !doc.LoadFile(XML_GLOBALCONFIG_FILENAME) )
	{
		assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
		return;
	}

// 	MeXmlHandle hDoc(&doc);

	const char* szValue = NULL;	

	MeXmlElement* pElem = doc.FirstChildElement(XML_GLOBALCONFIG_ROOT_NAME)->FirstChildElement("TreasureSetting")->FirstChildElement("BoxKey");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{	
		BoxKey bk;
		pElem->QueryIntAttribute("Level", &bk.nLevel );		
		pElem->QueryIntAttribute("OriginalBox", &bk.nOriginalBoxId );
		pElem->QueryIntAttribute("Box", &bk.nBoxId );			
		pElem->QueryIntAttribute("Key", &bk.nKeyId );			
		m_kBoxKeys.push_back( bk );
	}
}