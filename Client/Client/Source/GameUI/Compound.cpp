/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Compound.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Compound.h"
#include "Pack.h"
#include "InputBox.h"
#include "GameMain.h"
#include "PlayerRole.h"

#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "SlkReader.h"
#include "Progress.h"
#include "../ShowScreenText.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "MessageBox.h"
// #include "help.h"
#include "Pack_Ex.h"

#include "ChatInfoBox.h"
// #include "ChatSystem.h"
#include "MeUi/ExpressionManager.h"
#include "core/Name.h"
#include "Cfg.h"
#include "Task.h"
#include "GroupPanel.h"
#include "Gang.h"
#include "color_config.h"
// #include "Corps.h"
#include "tstring.h"
#include "UserData.h"
// #include "Tinyxml/tinyxml.h"
#include "PreventWallow.h"
#include "Ui/InfoList.h"
#include "SoundConfig.h"
#include "PackItemEnableManager.h"

extern char* GetFullFileName(const char* filename);

extern CHeroGame* theApp;
extern bool UIPACK_MovePackItem( const char* szInputData, void *pData );
unsigned char s_ucProductType = 0;
// #define COMPOUND_UI_XML_FILENAME "Config\\GlobalConfig.xml"

CUICompoundMgr * GetUICompoundMgr()
{
	guardfunc;
	return &g_UICompoundMgr;
	unguard;
}

CUICompoundConfig::CUICompoundConfig()
:IOXMLObjectInstance( XML_GLOBALCONFIG_ROOT_NAME)
{
	guardfunc;
	unguard;

}

bool CUICompoundConfig::loadXMLSettings( const char *path  )
{
	guardfunc;
	m_UICompoundIconSet.clear();
	return IOXMLObjectInstance::loadXMLSettings( path );
	unguard;
}

//bool CUICompoundConfig::SetProfession( string szString )
//{
//	m_strProfession = szString;
//	return true;
//}

bool CUICompoundConfig::ReadUI( XMLElement *element )
{
	guardfunc;
	if( !element )
		return false;

	XMLElement  *child   = NULL;
	XMLElement  *values   = NULL;
	child = element->getChildByName( "UICompound" );
	child =	element->getChildByName("Compound");
	if( child )
	{
		AddPos( child );				
	}

	child = element->getChildByName( "ReFine" );
	if( child )
	{
		AddPos( child );	
	}
	child = element->getChildByName( "Intensify" );
	if( child )
	{
		AddPos( child );	
	}
	return true;
	unguard;
}

bool CUICompoundConfig::AddPos( XMLElement *element )
{
	guardfunc;
	XMLElement *child = NULL;
	XMLElement *values = NULL;
	CompoundPage		compoud;	
	//	SUISkillIconSet		iconset;
	values = element->getChildByName("bg");
	if( values )
	{
		compoud.szBgPath = values->getValue();
	}
	for( int i=0; i<element->getChildrenCount(); i++ )
	{			
		child = element->getChild(i);
		if( "icon" == child->getName() )
		{
			SUIIconSet::SIconSet pt;
			values = child->getChildByName("x");
			if( values )
			{
				/*values = child->getChildByName("y");*/
				pt.x = values->getValuei();
			}
			values = child->getChildByName("y");
			if( values )
			{
				pt.y = values->getValuei();
			}
			values = child->getChildByName("bVis");
			if( values )
			{
				pt.bVis = values->getValueb();
			}
			values = child->getChildByName("iconid");
			if( values )
			{
				pt.iconid = values->getValuei();
			}
			//values = child->getChildByName("disbled");
			//if( values )
			//{
			//	pt.m_szDisbled = "icon\\" + values->getValue();
			//}
			compoud.UICompoundIcons.AddAllPos( pt );
		}				
	}
	m_UICompoundIconSet.push_back( compoud );	
	return true;
	unguard;
}

bool CUICompoundConfig::loadXMLSettings( XMLElement *element )
{
	guardfunc;
	if( !isSuitable(element) )
		return false;

	// 		ReadUI( element );

	//for(size_t i = 0; i < element->getChildrenCount(); i++)
	//{
	//	child = element->getChild(i);

	//	if(child->getName() == "MediaFolder")
	//	{
	//		MediaPathManager::registerPath(child);
	//		continue;
	//	}
	//}
	return true;
	unguard;
}

CUICompoundMgr::CUICompoundMgr()
{

}

CUICompoundMgr::~CUICompoundMgr()
{
	guardfunc;
	Release();
	unguard;
}

void CUICompoundMgr::Release()
{
	guardfunc;
	m_vtCompoundicon.clear();
	unguard;
}

//void CUICompoundMgr::AddBgPic( ControlPicture* pPic )
//{
//	if( pPic )
//		m_vtBgPic.push_back( pPic );
//}

void CUICompoundMgr::AddBgCompoundicon( ControlListImage* pImg )
{
	guardfunc;
	if( pImg )
		m_vtCompoundicon.push_back( pImg );
	unguard;
}

void CUICompoundMgr::ChangeUI( int nCompound )
{
	guardfunc;
	if( nCompound < 0 || nCompound > eMaxCompound )
		return;

	string PicName = "NULL";
	CUICompoundConfig::CompoundPage* pPage = m_CompoudConfig.GetPage(nCompound);

	if( pPage )
	{
		string szBgPath = pPage->szBgPath;
		SUIIconSet*  pSkillIcon = &pPage->UICompoundIcons;


		if( m_pCompoundFrame)
			m_pCompoundFrame->SetPicName( szBgPath.c_str() );

		for( size_t i  = 0; i<eCompoundMaxGrid/*pIcons->GetLength()*/; i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if( pIcon )
			{
				if( m_vtCompoundicon[i] )
					m_vtCompoundicon[i]->SetPos( pIcon->x, pIcon->y, false );
			}
		}

	}	
	unguard;
}

void CUICompoundMgr::Init( ControlFrame* pCompoundFrame )
{
	guardfunc;
	m_pCompoundFrame = pCompoundFrame;
	if( m_CompoudConfig.loadXMLSettings( XML_GLOBALCONFIG_FILENAME ) )
	{
		ChangeUI(0);
	}
	else
	{
		assert( false && "CUICompoundMgr::Init" );
	}
	unguard;
}
void CUICompoundMgr::Destroy( )
{
	guardfunc;
	m_vtCompoundicon.clear();
	m_pCompoundFrame = NULL;
	m_nCompound = -1;
	unguard;
}

typedef struct _tagTargetItemControlGroup
{
	ControlListImage* m_pListImg;
	ControlText*	  m_pName;
	ControlText*	  m_pRate;
}TargetItemControlGroup;

static const int s_nMaxTargetItem = 1;
static TargetItemControlGroup s_TargetControlGroup[s_nMaxTargetItem];
static RecipeConfig::SProduct* s_pTargetProduct = 0;

static RecipeConfig::ComposeRecipeContainer s_mapCompoundRules;	
static CUICompoundMgr g_UICompoundMgr;
static DWORD g_dwSkillPoint = 0;
static bool bIsCan = false;

CUI_ID_FRAME_Compound s_CUI_ID_FRAME_Compound;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Compound, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Compound, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_CompoundOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_ManOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_StopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_BUTTON_DownOnButtonClick )
// 
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_ForgingOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_SewingOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_CookingOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_TeaOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_DrugOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_CHECKBOX_BrewingOnCheckBoxCheck )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_PrescriptionOnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_AimOnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M1OnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M2OnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M3OnIconDragOn )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M4OnIconDragOn )
//MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_EspecialOnIconDragOn )


MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_PrescriptionOnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_AimOnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M1OnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M2OnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M3OnIconLDBClick )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_M4OnIconLDBClick )
//MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_EspecialOnIconLDBClick )

MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Compound, ID_EDIT_InfoOnEditEnter )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LIST_ComNameOnListSelectChange )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_EspecialOnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Compound, ID_LISTIMG_EspecialOnIconRButtonUp ) 
CUI_ID_FRAME_Compound::CUI_ID_FRAME_Compound()
{
	// SGuildMember
	ResetMembers();
	_begin = 0;
	_end = 0;

	m_nRuleID = InvalidLogicNumber;

	m_bIsCando = false;
	m_nPrescriptionId = 0;
	m_dwLastTime = 0;
	m_nNpcId = -1;
	m_nSingTime = 0;

	m_nCompoundCount = 0;
	m_nCompoundMaxCount = 0;
	m_nCompoundCurrCount = 0;

	m_nSingleMoney = 0;
	m_nSingleEnergy = 0;
	m_stEspecialBagIndex = -1;

	m_bDirty = false;

	m_CurrRecipeType = ERT_CaoYao;
}

void CUI_ID_FRAME_Compound::ResetMembers()
{
	m_pID_FRAME_Compound = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LISTIMG_Prescription = NULL;
	m_pID_BUTTON_Compound = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Aim = NULL;
// 	m_pID_LISTIMG_Aim1 = NULL;
// 	m_pID_LISTIMG_Aim2 = NULL;
	m_pID_EDIT_Info = NULL;
	m_pID_TEXT_ResultInfo = NULL;
	m_pID_TEXT_Rate = NULL;
// 	m_pID_TEXT_Rate1 = NULL;
// 	m_pID_TEXT_Rate2 = NULL;
	m_pID_TEXT_AimName  = NULL;
// 	m_pID_TEXT_Aim1Name = NULL;
// 	m_pID_TEXT_Aim2Name = NULL;
// 	m_pID_TEXT_SkillLvl = NULL;
	m_pID_LISTIMG_M1 = NULL;
	m_pID_LISTIMG_M2 = NULL;
	m_pID_LISTIMG_M3 = NULL;
	m_pID_LISTIMG_M4 = NULL;
	m_pID_LIST_ComName = NULL;	//配方名字
	m_pID_TEXT_Info = NULL;		//
// 	m_pID_BUTTON_help = NULL;
	m_pID_TEXT_M1Name = NULL;
	m_pID_TEXT_M1Info = NULL;
	m_pID_TEXT_M2Name = NULL;
	m_pID_TEXT_M2Info = NULL;
	m_pID_TEXT_M3Name = NULL;
	m_pID_TEXT_M3Info = NULL;
	m_pID_TEXT_M4Name = NULL;
	m_pID_TEXT_M4Info = NULL;
// 	m_pID_TEXT_Jin = NULL;
	m_pID_TEXT_Ying = NULL;
	m_pID_EDIT_Number = NULL;
	m_pID_BUTTON_Man = NULL;
	m_pID_TEXT_NpcName = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	//m_pID_PICTURE_Forging = NULL;
	m_pID_BUTTON_Stop = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_ExpendEnergy = NULL;
	m_pID_TEXT_Energy = NULL;
// 	m_pID_CHECKBOX_Forging = NULL;
// 	m_pID_CHECKBOX_Sewing = NULL;
// 	m_pID_CHECKBOX_Cooking = NULL;
// 	m_pID_CHECKBOX_Tea;
// 	m_pID_CHECKBOX_Drug = NULL;
// 	m_pID_CHECKBOX_Brewing = NULL;
// 	m_pID_TEXT_EspecialName = NULL;
// 	m_pID_TEXT_Skill = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
//	m_pID_LISTIMG_Especial = NULL;
}

void CUI_ID_FRAME_Compound::SetDirty( bool bDirty )
{
	m_bDirty = bDirty;
}
void CUI_ID_FRAME_Compound::RefreshBagEnable()
{
	if( !m_pID_FRAME_Compound )
		return;
	if( m_bDirty )// 更新界面
	{
		SetDirty( false );
		if( m_stEspecialBagIndex != -1 )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stEspecialBagIndex, true );
			if( m_bEspecialBagEnable )//背包内可用，说明这里不用了
				m_stEspecialBagIndex = -1;
		}
		RefreshSelectRecipe();
	}
}
// Frame
bool CUI_ID_FRAME_Compound::OnFrameRun()
{
	guardfunc;
	if ( !IsVisable() )
	{
		return false;
	}

	CPlayer* pMe = NULL;
	pMe = theApp->GetPlayerMgr()->GetMe();
	if ( !pMe )
		return false;

	if (m_bIsCando)
	{
		if (pMe->IsMoving())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );				
			////m_pID_LISTIMG_M1->SetCanbePick(true);
			////m_pID_LISTIMG_M2->SetCanbePick(true);
			////m_pID_LISTIMG_M3->SetCanbePick(true);
			////m_pID_LISTIMG_M4->SetCanbePick(true);
			////m_pID_LISTIMG_Aim->SetCanbePick(true);
			//s_CUI_Progress.SetVisable( false );
			//m_bIsCando = false;
			//m_pID_LIST_ComName->SetEnable(true);
			//m_pID_BUTTON_Man->SetEnable(true);
			//m_pID_EDIT_Number->SetEnable(true);
			//m_pID_BUTTON_Compound->SetEnable(true);
			//RefreshSelectRecipe();
			///*return true;*/

			ID_BUTTON_StopOnButtonClick(0);
		}
		else
		{				
			if (m_nCompoundCurrCount > 0 /*&&
										 ( ( thePlayerRole.m_bag.GetNullItemCount() != 0  && s_ucProductType != ItemDefine::ITEMTYPE_MATERIAL ) ||
										 ( thePlayerRole.m_bagMaterial.GetNullItemCount() != 0  && s_ucProductType == ItemDefine::ITEMTYPE_MATERIAL))*/ )// added, jiayi, [2009/10/17], 这里判断包裹里面是否还有地方					
			{
				DWORD dwCurrTime = HQ_TimeGetTime();
				if (dwCurrTime - m_dwLastTime >= m_nSingTime)
				{
					// 						ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->GetItemByIndex( m_stEspecialBagIndex );
					// 						short sAssistId = -1;
					// 						if( pItemImg )
					// 							sAssistId = pItemImg->m_pkIconInfo->GetItemId();
					MsgQueryCompoundNew msg;
					msg.recipeId = m_nRuleID;
					msg.assistantItemBagIndex[0] = m_stEspecialBagIndex;						
					GettheNetworkInput().SendMsg( &msg );

					m_dwLastTime = dwCurrTime;
					--m_nCompoundCurrCount;
					if (m_nCompoundCurrCount > 0)
					{
						s_CUI_Progress.ShowByTime( m_dwLastTime, m_nSingTime, true, 1, true, true, theXmlString.GetString(eClinet_compound_string) );
					}
				}
			}
			else
			{
				//if( ( thePlayerRole.m_bag.GetNullItemCount() == 0 && s_ucProductType != ItemDefine::ITEMTYPE_MATERIAL ) ||
				//	( thePlayerRole.m_bagMaterial.GetNullItemCount() == 0 && s_ucProductType == ItemDefine::ITEMTYPE_MATERIAL ) )
				//{
				//	s_CUI_ID_FRAME_InfoList. AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_61), Color_Config.getColor( CC_SystemPromp ) );
				//}
				m_bIsCando = false;
				m_pID_LIST_ComName->SetEnable(true);
				m_pID_BUTTON_Man->SetEnable(true);
				m_pID_EDIT_Number->SetEnable(true);
				m_pID_BUTTON_Compound->SetEnable(true);
				RefreshSelectRecipe();
			}
		}
	}		
	RefreshBagEnable();

	return true;
	unguard;
}
bool CUI_ID_FRAME_Compound::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_Compound::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	SetVisable( false );
	return false; 
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	ID_LISTIMG_MaterialOnIconDragOn( pSender, pMe, pItemDrag, pItemSrc );
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M1OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	ID_LISTIMG_MaterialOnIconDragOn( pSender, pMe, pItemDrag, pItemSrc );
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M2OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;

	return false;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	ID_LISTIMG_MaterialOnIconDragOn( pSender, pMe, pItemDrag, pItemSrc );
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M3OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	ID_LISTIMG_MaterialOnIconDragOn( pSender, pMe, pItemDrag, pItemSrc );
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M4OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_M4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_PrescriptionOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if (!pItemDrag||!pItemSrc)
	{
		return false;
	}
	*m_pID_TEXT_ResultInfo = "";
	if ( pItemDrag->IsNull() || !pItemSrc->IsNull() )
		return false;
	if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
	{
		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
		if ( !pItemDetail )
			return false;
		if ( pItemDetail->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItemDetail->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
			return false;
		//
		int nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
		if ( nIndex == -1 )
			return false;
		//if( CItemBag2::MoveItem( &thePlayerRole.m_pCompound->stPrescription,
		//	&thePlayerRole.m_charinfo.ItemBagData.stPackItems[nIndex], NULL,NULL,"",1 ) != -1 )
		//{
		//	MsgMoveCompoundItem msg;
		//	msg.stMoveType = MsgMoveCompoundItem::ePackToPrescription;
		//	msg.stSrcIndex = nIndex;
		//	msg.stDstIndex = 0;
		//	GettheNetworkInput().SendMsg( &msg );
		//}
		Refeash();
	}
	return true;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_PrescriptionOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_PrescriptionOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Compound::ID_BUTTON_StopOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Compound )
		return true;

	m_bIsCando = false;
	m_pID_LIST_ComName->SetEnable(true);
	m_pID_BUTTON_Man->SetEnable(true);
	m_pID_EDIT_Number->SetEnable(true);
	m_pID_BUTTON_Compound->SetEnable(true);
	s_CUI_Progress.SetProgressComplete();
	RefreshSelectRecipe();
	return true;
}

//bool CUI_ID_FRAME_Compound::ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_Compound )
//		return false;
//
//	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
//	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL ) )
//	{
//		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
//		if( !pImageSender )
//			return false;
//
//		// 包裹里
//		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pImageSender) )
//		{			
//			ControlList::S_List *pstList = m_pID_LIST_ComName->GetCurSelItem();
//			if (!pstList)
//				return false;
//
//			RecipeConfig::SRecipe* pRule = GetCompoundRuleById( pstList->m_nID );
//			if ( !pRule )
//				return false;
//
//			bool bFound = false;
//			for( int i = 0 ; i < pRule->Products.size() ; ++ i )
//			{
//				RecipeConfig::SProduct* pProduct = &pRule->Products[i];
//				for( int j = 0 ; j < pProduct->SecondaryMaterials.size(); ++ j )
//				{
//					RecipeConfig::SMaterial* pSecMat = &pProduct->SecondaryMaterials[j];
//					if( pSecMat && ( pSecMat->MaterialId == pItemDrag->m_pkIconInfo->GetItemId() ) )
//					{
//						bFound = true;
//						break;
//					}
//				}
//				if( bFound )
//					break;
//			}
//			if( !bFound )
//				return false;
//
//			// 先剔除之前的
//			if( m_stEspecialBagIndex != -1 )
//			{
//				ID_LISTIMG_EspecialOnIconRButtonUp(0,0);
//				thePlayerRole.m_bagMaterial. m _bEnables[m_stEspecialBagIndex] = true;		
//				s_CUI_ID_FRAME_PACK.RefreshMaterialPackByIndex( m_stEspecialBagIndex );				
//			}
//			// 添加名字
//			Common::_tstring tstrName( pItemCommon->GetItemName() );
//			S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
//			m_pID_TEXT_EspecialName->SetText( tstrName.c_str(), S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ) );
//
//			m_stEspecialBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
//			m_pID_LISTIMG_Especial->SetItem( pItemDrag, 0 );
//			m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;//这里只放一个
//			m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
//
//			// 这里修改最大值窗口的数字						
//			m_pID_EDIT_Number->SetText( "1" );
//		}
//		else
//		{
//			return false;
//		}		
//		m_bEspecialBagEnable = false;
//
//		SetDirty( true );
//	}	
//	return false;
//}
//bool CUI_ID_FRAME_Compound::ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Compound::ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	return false;
//}
//bool CUI_ID_FRAME_Compound::ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	m_bEspecialBagEnable = true;			
//	m_pID_LISTIMG_Especial->Clear();
//	*m_pID_TEXT_EspecialName = "";		
//	SetDirty( true );
//	return false;
//}

bool CUI_ID_FRAME_Compound::CanCompound( const char bPressYesButton, void *pData  )
{
	if( !s_CUI_ID_FRAME_Compound.GetFrame() )
		return false;
	if ( bPressYesButton != 0 )
	{
		int nMaterialCount = 0;
		int nNeedMaterialCount = 0;
		ControlText* text = s_CUI_ID_FRAME_Compound.GetTextResultInfo();
		*text = "";
		//for ( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
		//{
		//	if ( thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemID != ErrorUnsignedShortID
		//		/*&&thePlayerRole.m_pCompound->stMaterial[n].guid !=GUID_NULL */)
		//	{
		//		nMaterialCount++;				
		//	}

		//}
		//if ( nMaterialCount == 0 )
		//{
		//	//请放入合成原料

		//	*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Set_Materials);
		//	return true;
		//}
		////
		//if ( thePlayerRole.m_pCompound->stAim.itembaseinfo.ustItemID != ErrorUnsignedShortID 
		//	/*&&thePlayerRole.m_pCompound->stAim.guid !=GUID_NULL*/)
		//{
		//	//请取出合成目标栏物品
		//	*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Take_CompItem);
		//	return true;
		//}

		//bool bIsCan = false;

		if ( s_pTargetProduct )
		{

			// 				ItemDefine::SItemCreateItemRule *pCreatRule = (ItemDefine::SItemCreateItemRule *)GettheItemDetail().GetItemByID(nCreatRoleID);
			// 				if (!pCreatRule)
			// 				{
			// 					char szTemp [512];
			// 					sprintf(szTemp, theXmlString.GetString(eClient_AddInfo_2slk_124));
			// 					*m_pID_TEXT_ResultInfo = szTemp;
			// 					return true;
			// 				}

			s_CUI_ID_FRAME_Compound.SetSingTime( s_pTargetProduct->CastTime );

			//	for (int loop = 0; loop < ITEM_COMPOUND_BAGMAX;loop ++)
			//	{
			//		if (pCreatRule->material[loop].ustItemID != ErrorUnsignedShortID)
			//		{
			//			nNeedMaterialCount++;					
			//		}
			//	}

			//	if (nNeedMaterialCount != nMaterialCount)
			//	{
			//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Material_Error_0);
			//		return true;
			//	}
			//	ItemDefine::SItemCommon *pCommon = NULL;
			//	for (int i = 0; i < ITEM_COMPOUND_BAGMAX;i++)
			//	{

			//		if (thePlayerRole.m_pCompound->stMaterial[i].itembaseinfo.ustItemID == ErrorUnsignedShortID)
			//		{
			//			continue;
			//		}

			//		for (int nloop = 0; nloop < pCreatRule->iMaterialNum;nloop++)
			//		{
			//			if (thePlayerRole.m_pCompound->stMaterial[i].itembaseinfo.ustItemID == pCreatRule->material[nloop].ustItemID)
			//			{
			//				pCommon = GettheItemDetail().GetItemByID(pCreatRule->material[nloop].ustItemID);
			//				if (!pCommon->IsExclusive())
			//				{
			//					if (pCreatRule->material[nloop].ustCount > thePlayerRole.m_pCompound->stMaterial[i].itembaseinfo.ustItemCount
			//						/*||pCreatRule->material[nloop].ustCount == thePlayerRole.m_pCompound->stMaterial[i].itembaseinfo.ustItemCount*/)
			//					{
			//						bIsCan = false;
			//						break;
			//					}
			//					else
			//					{
			//						bIsCan = true;
			//						break;
			//					}

			//				}
			//			}
			//			else
			//			{
			//				bIsCan = false;						
			//			}
			//		}
			//		if (!bIsCan)
			//		{
			//			break;
			//		}
			//	}			
			//}
			if (bIsCan && s_CUI_ID_FRAME_Compound.GetSingTime() > 0)
			{
				//m_pID_LISTIMG_M1->SetCanbePick(false);
				//m_pID_LISTIMG_M2->SetCanbePick(false);
				//m_pID_LISTIMG_M3->SetCanbePick(false);
				//m_pID_LISTIMG_M4->SetCanbePick(false);
				//m_pID_LISTIMG_Aim->SetCanbePick(false);


				s_CUI_ID_FRAME_Compound.HelpCanCompound();

				return true;
			}
		}
		else
		{
			ControlText* text = s_CUI_ID_FRAME_Compound.GetTextResultInfo();
			*text = theXmlString.GetString(eText_Material_Error_0);
		}

	}
	return false;
}
void CUI_ID_FRAME_Compound::HelpCanCompound()
{
	m_bIsCando = true;
	m_nPrescriptionId = m_nRuleID;
	m_dwLastTime = HQ_TimeGetTime();

	m_nCompoundCurrCount = m_nCompoundCount = atoi(m_pID_EDIT_Number->GetText());

	m_pID_BUTTON_Stop->SetEnable(true);
	m_pID_LIST_ComName->SetEnable(false);
	m_pID_BUTTON_Man->SetEnable(false);
	m_pID_EDIT_Number->SetEnable(false);
	m_pID_BUTTON_Compound->SetEnable(false);

	s_CUI_Progress.ShowByTime( m_dwLastTime, m_nSingTime, true, 1, true, true, theXmlString.GetString(eClinet_compound_string) );

}
// Button
bool CUI_ID_FRAME_Compound::ID_BUTTON_CompoundOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if (thePlayerRole.IsFighting())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return true;
	}

	if( CPreventWallow::Instance().IsFCMNotHealthy() )
		return true;

	if (m_nCompoundMaxCount <= 0)
		return true;

	int money = m_nSingleMoney * m_nCompoundCount;
	//if (money > thePlayerRole.GetData(CPlayerRole::TYPE_MONEY))
    if(!thePlayerRole.HaveEnoughMoney(money))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eExchange_NotMoney ) );
		return true;
	}

	int energy = m_nSingleEnergy * m_nCompoundCount;
	if (energy > thePlayerRole.GetData(CPlayerRole::TYPE_ENERGY))
	{
		//GetShowScreenText() ->AddInfo( theXmlString.GetString( eExchange_NotMoney ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
		return true;
	}

	char szBuff[256] = {0};
	if (s_pTargetProduct)
	{
		for (int i = 0; i < s_pTargetProduct->ProductItems.size(); ++i)
		{
			RecipeConfig::SItem* pItem = &s_pTargetProduct->ProductItems[i];
			// 添加名称，颜色根据品质
			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->ItemId );				
			if( !pItemCommon )
				continue;
			if( i == 0 )
				sprintf_s( szBuff, 256, theXmlString.GetString(eUI_IsCompound), pItemCommon->GetItemName() );

			switch (pItemCommon->ucItemType)
			{
			case ItemDefine::ITEMTYPE_MATERIAL:
				{
					int nPackEmptyIndex = thePlayerRole.m_bagMaterial.FindNullItemOffset();
					if (nPackEmptyIndex == -1)
					{
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
						return true;
					}
				}
				break;
			case ItemDefine::ITEMTYPE_TASK:
				{
					int nPackEmptyIndex = thePlayerRole.m_bagTask.FindNullItemOffset();
					if (nPackEmptyIndex == -1)
					{
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
						return true;
					}
				}
				break;
			default:
				{
					int nPackEmptyIndex = thePlayerRole.m_bag.FindNullItemOffset();
					if (nPackEmptyIndex == -1)
					{
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
						return true;
					}
				}
				break;
			}
		}
	}

	//
	s_CUI_ID_FRAME_MessageBox.Show( szBuff, theXmlString.GetString(eClient_AddInfo_2slk_16),
		CUI_ID_FRAME_MessageBox::eTypeYesNo, false,CUI_ID_FRAME_Compound::CanCompound);
	return true;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_BUTTON_ManOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	m_pID_EDIT_Number->SetText(m_nCompoundMaxCount);
	return true;
	unguard;
}
/*bool CUI_ID_FRAME_Compound::PackDragOnMaterial( const char* szInputData, void *pData )
{
	guardfunc;
	//int nCount = atoi( szInputData );
	//if ( nCount <= 0 )
	//	return false;
	//MsgMoveCompoundItem *pMsg = (MsgMoveCompoundItem*)pData;
	//if( CItemBag2::MoveItem( &thePlayerRole.m_pCompound->stMaterial[pMsg->stDstIndex],
	//	&thePlayerRole.m_charinfo.ItemBagData.stPackItems[pMsg->stSrcIndex], NULL,NULL,"",nCount ) != -1 )
	//{
	//	pMsg->stCount = nCount;
	//	GettheNetworkInput().SendMsg( pMsg );
	//}
	//Refeash();
	return true;
	unguard;
}*/
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	//if (!pItemDrag||!pItemSrc)
	//{
	//	return false;
	//}
	//*m_pID_TEXT_ResultInfo = "";
	//if ( pItemDrag->IsNull() )
	//	return false;
	//if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) || pSender == s_CUI_ID_FRAME_pack_ex.m_pID_LISTIMG_pack_ex )
	//{
	//	int nPackIndex = -1;
	//	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
	//	{
	//		nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
	//	}
	//	else if( pSender == s_CUI_ID_FRAME_pack_ex.m_pID_LISTIMG_pack_ex )
	//	{
	//		nPackIndex = ITEM_PACK_OLD + s_CUI_ID_FRAME_pack_ex.m_pID_LISTIMG_pack_ex->GetItemIndex( pItemDrag );
	//	}
	//	if ( nPackIndex == -1 )
	//		return false;
	//	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	//	if ( !pItemDetail )
	//		return false;
	//	if(!pItemDetail->bIsCanMove)
	//	{
	//		UI_MessageBox::Show(  theXmlString.GetString(eText_ItemCanNotBeenMoved) );
	//		return false;		
	//	}
	//	SCharItem *pMaterials = NULL;
	//	pMaterials = thePlayerRole.m_pCompound->stMaterial;
	//	if ( pItemDetail->IsExclusive() )
	//	{
	//		for (int nloop = 0;nloop < ITEM_COMPOUND_BAGMAX;nloop++)
	//		{
	//			if (pMaterials[nloop].itembaseinfo.ustItemID == pItemDrag->m_pkIconInfo->Id())
	//			{
	//				return false;
	//			}
	//		}
	//		for( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
	//		{
	//			if( pMaterials[n].itembaseinfo.ustItemID == ErrorUnsignedShortID )
	//			{
	//				MsgMoveCompoundItem msg;

	//				msg.stMoveType = MsgMoveCompoundItem::ePackToMaterial;
	//				msg.stSrcIndex = nPackIndex;
	//				msg.stDstIndex = n;

	//				if(pItemDrag->m_pkIconInfo->Count() == 1)
	//				{							
	//					if( CItemBag2::MoveItem( &pMaterials[n],
	//						&thePlayerRole.m_charinfo.ItemBagData.stPackItems[nPackIndex],NULL,NULL,"",1 ) != -1 )
	//					{
	//						////zizi add
	//						//if(pItemDetail->ucItemType != ItemDefine::ITEMTYPE_WEAPON)
	//						//	return false;

	//						msg.stCount = 1;
	//                              GettheNetworkInput().SendMsg( &msg );

	//                              ItemDefine::SItemCommon *pitemCommon = GettheItemDetail().GetItemByID(
	//                                  pMaterials[n].itembaseinfo.ustItemID);
	//                              if ( pitemCommon && pitemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
	//                              {
	//                                  ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pitemCommon;
	//                                  if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
	//                                  {
	//                                      thePlayerRole.refreshHotKey();
	//                                  }
	//                              }
	//					}
	//					break;
	//				}
	//				else
	//				{
	//					//请输入数量
	//					s_CUI_InputBox.Show( theXmlString.GetString(eText_Input_Cnt), true, true, PackDragOnMaterial,
	//						&msg, msg.GetLength() );
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		for( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
	//		{
	//			bool bIsSame = false;
	//			for (int nloop = 0;nloop < ITEM_COMPOUND_BAGMAX;nloop++)
	//			{
	//				if (pMaterials[nloop].itembaseinfo.ustItemID == pItemDrag->m_pkIconInfo->Id())
	//				{
	//					n = nloop;
	//					bIsSame = true;
	//				}
	//			}

	//			if( pMaterials[n].itembaseinfo.ustItemID == pItemDrag->m_pkIconInfo->Id() ||
	//				pMaterials[n].itembaseinfo.ustItemID == ErrorUnsignedShortID )
	//			{
	//				MsgMoveCompoundItem msg;
	//				msg.stMoveType = MsgMoveCompoundItem::ePackToMaterial;
	//				msg.stSrcIndex = nPackIndex;
	//				msg.stDstIndex = n;
	//				msg.stCount = 1;
	//				//
	//				if ( pItemDrag->m_pkIconInfo->Count() == 1 )
	//				{
	//					if( CItemBag2::MoveItem( &pMaterials[n],
	//						&thePlayerRole.m_charinfo.ItemBagData.stPackItems[nPackIndex],NULL,NULL,"", 1)
	//						!= -1 )
	//					{
	//						GettheNetworkInput().SendMsg( &msg );
	//					}
	//				}
	//				else
	//				{ 
	//					//"请输入数量"
	//					s_CUI_InputBox.Show( theXmlString.GetString(eText_Input_Cnt), true, true, PackDragOnMaterial,
	//						&msg, msg.GetLength() );
	//				}
	//				break;
	//			}
	//		}
	//	}			
	//}
	//Refeash();
	return false;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Compound::ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Compound::ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Edit
void CUI_ID_FRAME_Compound::ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData )
{
}
void CUI_ID_FRAME_Compound::ID_EDIT_NumberOnTextChanged( ControlObject* pSender, const char* szData )
{
	int v = /*atoi(szData)*/atoi( s_CUI_ID_FRAME_Compound.m_pID_EDIT_Number->GetText() );

	if ( v > s_CUI_ID_FRAME_Compound.m_nCompoundMaxCount )
	{
		v = s_CUI_ID_FRAME_Compound.m_nCompoundMaxCount;
		s_CUI_ID_FRAME_Compound.m_pID_EDIT_Number->SetText( s_CUI_ID_FRAME_Compound.m_nCompoundMaxCount );
	}

	s_CUI_ID_FRAME_Compound.SetCompoundCount( v );
	if( v == 0 )
		s_CUI_ID_FRAME_Compound.GetButton()->SetEnable( false );		
	else
		s_CUI_ID_FRAME_Compound.GetButton()->SetEnable( true );

	s_CUI_ID_FRAME_Compound.ChangeMoney(s_CUI_ID_FRAME_Compound.GetCompoundCount() > 0 ? s_CUI_ID_FRAME_Compound.GetCompoundCount() : 1);
}
// list of Name Select Change
void CUI_ID_FRAME_Compound::ID_LIST_ComNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
// 	ID_LISTIMG_EspecialOnIconRButtonUp(0,0);		
	*m_pID_TEXT_Info = "";
	*m_pID_TEXT_ResultInfo = "";
	*m_pID_TEXT_Rate = "";
// 	*m_pID_TEXT_Rate1 = "";
// 	*m_pID_TEXT_Rate2 = "";

	*m_pID_TEXT_AimName = "";
// 	*m_pID_TEXT_Aim1Name = "";
// 	*m_pID_TEXT_Aim2Name = "";
// 	*m_pID_TEXT_SkillLvl = "";

	*m_pID_TEXT_M1Name = "";
	*m_pID_TEXT_M1Info = "";
	*m_pID_TEXT_M2Name = "";
	*m_pID_TEXT_M2Info = "";
	*m_pID_TEXT_M3Name = "";
	*m_pID_TEXT_M3Info = "";
	*m_pID_TEXT_M4Name = "";
	*m_pID_TEXT_M4Info = "";

//	*m_pID_TEXT_Jin = "";
	*m_pID_TEXT_Ying = "";
	*m_pID_TEXT_ExpendEnergy = "";
	//*m_pID_TEXT_EspecialName = "";
// 	*m_pID_TEXT_Skill = "";
	//*m_pID_EDIT_Number = "1";

	m_pID_LISTIMG_M1->Clear();
	m_pID_LISTIMG_M2->Clear();
	m_pID_LISTIMG_M3->Clear();
	m_pID_LISTIMG_M4->Clear();
	m_pID_LISTIMG_Aim->Clear();
// 	m_pID_LISTIMG_Aim1->Clear();
// 	m_pID_LISTIMG_Aim2->Clear();

	m_nSingleMoney = 0;
	m_nSingleEnergy = 0;

	if (!m_bIsCando)
	{
		m_pID_BUTTON_Compound->SetEnable(false);
		m_pID_BUTTON_Stop->SetEnable(false);
	}

	RefreshPlayerProperty();

	m_nRuleID = 0;
	s_pTargetProduct = 0;

	if ( s_mapCompoundRules.size() == 0 )
	{
		return;
	}
	RefreshSelectRecipe();
	*m_pID_EDIT_Number = "1";
}

void CUI_ID_FRAME_Compound::RecordCollapseInfo()
{
	for(int i = 0; i < m_pID_LIST_ComName->GetListItemCnt(); ++i)
	{
		ControlList::S_List* pList = m_pID_LIST_ComName->GetListItem(i);
		if (pList->m_nHiberarchy == 0)
		{
			bool isExisted = false;
			for (int i = 0; i < m_RecordArr[m_CurrRecipeType].size(); ++i)
			{
				if (m_RecordArr[m_CurrRecipeType][i].m_nSubType == pList->m_nID)
				{
					m_RecordArr[m_CurrRecipeType][i].m_isCollapse = pList->m_bCollapse;
					isExisted = true;
				}
			}
			if (!isExisted)
			{
				m_RecordArr[m_CurrRecipeType].push_back(TreeStatusRecord(pList->m_nID,pList->m_bCollapse));
			}
		}
	}
}
static const char* CompoundFilename = "CompoundTreeStatus.config";
static const char* CompoundOldFilename = "CompoundTreeStatus.xml";
bool CUI_ID_FRAME_Compound::LoadCollapseInfo()
{
	for (int i = 0; i < ERT_MaxType; ++i)
	{
		m_RecordArr[i].clear();
	}
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += CompoundFilename;

	MeXmlDocument doc1;
	if( !doc1.LoadFile(filename.c_str()) )
	{
		filename = CUserData::Instance()->GetUserDataPath();
		filename += CompoundOldFilename;
	}
	if( doc1.LoadFile(filename.c_str()) )
	{
// 		MeXmlHandle	 hDoc1(&doc1);

		MeXmlElement* pHeader = doc1.FirstChildElement("Project");
		if (pHeader)
		{
			MeXmlElement* pElem = pHeader->FirstChildElement("TreeStatuses")->FirstChildElement("CompoundType");
			for( ; pElem; pElem = pElem->NextSiblingElement() )
			{
				int nType = 0;
				pElem->QueryIntAttribute("Type", &nType);

				if (nType < 0 || nType >= ERT_MaxType)
				{
					continue;
				}
				MeXmlElement* pStatus = pElem->FirstChildElement("TreeStatus");
				for( ; pStatus; pStatus = pStatus->NextSiblingElement() )
				{
					int nSubType = 0;
					pStatus->QueryIntAttribute("SubType", &nSubType);
					int nIsCollapse = 0;
					pStatus->QueryIntAttribute("IsCollapse", &nIsCollapse);
					m_RecordArr[nType].push_back(TreeStatusRecord(nSubType,nIsCollapse));
				}
			}
		}
	}

	return true;

}

bool CUI_ID_FRAME_Compound::SaveCollapseInfo()
{
	if (m_pID_FRAME_Compound == NULL)
	{
		return false;
	}
	RecordCollapseInfo();
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += CompoundFilename;

	SetFileAttributes( filename.c_str(), FILE_ATTRIBUTE_NORMAL );
	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "utf-8", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement* project = doc.InsertEndChild("Project");
	project->SetAttribute("Name", "HeroOnline");
	project->SetAttribute("Version", "");

	MeXmlElement *tracks = project->InsertEndChild("TreeStatuses");

	for (int i = 0; i < ERT_MaxType; ++i)
	{
		MeXmlElement *CompoundType = tracks->InsertEndChild("CompoundType");
		CompoundType->SetAttribute("Type", i);
		for (int z = 0; z < m_RecordArr[i].size();++z)
		{
			MeXmlElement *track = CompoundType->InsertEndChild("TreeStatus");
			track->SetAttribute("SubType", m_RecordArr[i][z].m_nSubType);
			track->SetAttribute("IsCollapse", m_RecordArr[i][z].m_isCollapse);
// 			CompoundType.InsertEndChild(track);
		}
// 		tracks.InsertEndChild(CompoundType);
	}
// 	project.InsertEndChild(tracks);

// 	doc.InsertEndChild(project);
	doc.SaveFile(filename.c_str());

	// 删除旧文件格式
	filename = CUserData::Instance()->GetUserDataPath();
	filename += CompoundOldFilename;
	::DeleteFile(filename.c_str());

	return true;
}

void CUI_ID_FRAME_Compound::ShowByType( int nType )
{   
    SetVisable( true );

    g_dwSkillPoint = thePlayerRole.GetData( ( CPlayerRole::enUpdataType )nType );
    RecordCollapseInfo();
    switch( nType )
    {
    case CPlayerRole::TYPE_CaoYao:
        m_CurrRecipeType = ERT_CaoYao;
        break;
    case CPlayerRole::TYPE_ZhuBao:
        m_CurrRecipeType = ERT_ZhuBao;
        break;
    case CPlayerRole::TYPE_DuanZao:
        m_CurrRecipeType = ERT_DuanZao;
        break;
    case CPlayerRole::TYPE_ZhuJia:
        m_CurrRecipeType = ERT_ZhuJia;
        break;
    case CPlayerRole::TYPE_GongYi:
        m_CurrRecipeType = ERT_GongYi;
        break;
    case CPlayerRole::TYPE_XunMa:
        m_CurrRecipeType = ERT_XunMa;
        break;
    case CPlayerRole::TYPE_CaiKuang:
        m_CurrRecipeType = ERT_CaiKuang;
        break;
    case CPlayerRole::TYPE_CaiYao:
        m_CurrRecipeType = ERT_CaiYao;
        break;
    case CPlayerRole::TYPE_BuChong:
        m_CurrRecipeType = ERT_BuChong;
        break;
    default:
        return;
        break;
    }
    UpdateCompoundItems();

    *m_pID_EDIT_Number = "1";
    m_nCompoundMaxCount = 0;
}

bool CUI_ID_FRAME_Compound::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_bIsCando )
	{
		int v = m_nCompoundCount;
		v++;
		if (v > m_nCompoundMaxCount)
			v = m_nCompoundMaxCount;
		if (v != m_nCompoundCount)
			m_pID_EDIT_Number->SetText(v);
	}
	return true;
	unguard;
}
bool CUI_ID_FRAME_Compound::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_bIsCando )
	{
		int v = m_nCompoundCount;
		v--;
		if (v < 0)
			v = 0;
		if (v != m_nCompoundCount)
			m_pID_EDIT_Number->SetText(v);
	}
	return true;
	unguard;
}

void CUI_ID_FRAME_Compound::Compound_OnVisiableChanged( ControlObject* pSender )
{
	if (!s_CUI_ID_FRAME_Compound.IsVisable())
	{
		s_CUI_ID_FRAME_Compound.ID_BUTTON_StopOnButtonClick(0);
		s_CUI_ID_FRAME_Compound.SetDirty( true );
		s_CUI_ID_FRAME_Compound.SetEspecialBagEnable( true );
		s_CUI_ID_FRAME_Compound.RefreshBagEnable();
		//s_CUI_ID_FRAME_Compound.ID_LISTIMG_EspecialOnIconRButtonUp(0,0);	
		s_CUI_ID_FRAME_Compound.RecordCollapseInfo();
	}
	else
	{
		s_CUI_ID_FRAME_Compound.UpdateCompoundItems();			
	}
}

// 装载UI
bool CUI_ID_FRAME_Compound::_LoadUI()
{
	guardfunc;
	LoadCollapseInfo();
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Compound.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Compound.UI]失败")
			return false;
	}
	// 		else if ( dwResult != 159490/*文件版本号*/ )
	// 		{
	// 			MESSAGE_BOX("读取文件[UI\\Compound.UI]与源代码版本不一样")
	// 		}
	return DoControlConnect();
	unguard;
}
// 获得配方列表
void CUI_ID_FRAME_Compound::RetrieveRuleList()
{	
	// 		RecipeConfig::ComposeRecipeContainer::iterator iter = theRecipeConfig.GetRecipes().begin();
	// 		for ( ; iter != theRecipeConfig.GetRecipes().end() ; ++ iter )
	// 		{	
	// 			RecipeConfig::SRecipe* pReceipRule = &(*iter).second;
	// 			if( pReceipRule )
	// 			{
	// 				s_mapCompoundRules[pReceipRule->RecipeId] = *pReceipRule;
	// 			}
	// 		}
	s_mapCompoundRules.clear();
	for( int i = 0 ; i < MAX_RECIPE_COUNT; ++i )
	{
		if( thePlayerRole.GetCharInfo2().otherdataclient.recipes[i] == 0 )
			continue;

		RecipeConfig::SRecipe* pReceipRule = theRecipeConfig.GetItemRuleByRuleId(
			thePlayerRole.GetCharInfo2().otherdataclient.recipes[i] );
		if( !pReceipRule || pReceipRule->Type != m_CurrRecipeType)
			continue;

		uint16 unSkillId = theRecipeConfig.GetSkillIdByRecipeType( m_CurrRecipeType );
		if ( unSkillId == InvalidLogicNumber )
			continue;
		SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID( unSkillId );
		if( !pCharSkill || pCharSkill->stSkillLevel < pReceipRule->SkillLevelLimit )
			continue;

		s_mapCompoundRules[pReceipRule->RecipeId] = *pReceipRule;
	}
}
// 关连控件
bool CUI_ID_FRAME_Compound::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Compound, s_CUI_ID_FRAME_CompoundOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Compound, s_CUI_ID_FRAME_CompoundOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_CompoundID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_Prescription, s_CUI_ID_FRAME_CompoundID_LISTIMG_PrescriptionOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_Prescription, s_CUI_ID_FRAME_CompoundID_LISTIMG_PrescriptionOnIconLDBClick );
	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_Compound, s_CUI_ID_FRAME_CompoundID_BUTTON_CompoundOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_Material, s_CUI_ID_FRAME_CompoundID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_Material, s_CUI_ID_FRAME_CompoundID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_Aim, s_CUI_ID_FRAME_CompoundID_LISTIMG_AimOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_Aim, s_CUI_ID_FRAME_CompoundID_LISTIMG_AimOnIconLDBClick );
	theUiManager.OnEditEnter( ID_FRAME_Compound, ID_EDIT_Info, s_CUI_ID_FRAME_CompoundID_EDIT_InfoOnEditEnter );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_M1, s_CUI_ID_FRAME_CompoundID_LISTIMG_M1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_M1, s_CUI_ID_FRAME_CompoundID_LISTIMG_M1OnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_M2, s_CUI_ID_FRAME_CompoundID_LISTIMG_M2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_M2, s_CUI_ID_FRAME_CompoundID_LISTIMG_M2OnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_M3, s_CUI_ID_FRAME_CompoundID_LISTIMG_M3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_M3, s_CUI_ID_FRAME_CompoundID_LISTIMG_M3OnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_M4, s_CUI_ID_FRAME_CompoundID_LISTIMG_M4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_M4, s_CUI_ID_FRAME_CompoundID_LISTIMG_M4OnIconLDBClick );
	theUiManager.OnListSelectChange( ID_FRAME_Compound, ID_LIST_ComName, s_CUI_ID_FRAME_CompoundID_LIST_ComNameOnListSelectChange);
	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_Man, s_CUI_ID_FRAME_CompoundID_BUTTON_ManOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_Stop, s_CUI_ID_FRAME_CompoundID_BUTTON_StopOnButtonClick);

	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_Up, s_CUI_ID_FRAME_CompoundID_BUTTON_UpOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_Compound, ID_BUTTON_Down, s_CUI_ID_FRAME_CompoundID_BUTTON_DownOnButtonClick);
// 	theUiManager.OnIconDragOn( ID_FRAME_Compound, ID_LISTIMG_Especial, s_CUI_ID_FRAME_CompoundID_LISTIMG_EspecialOnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_Compound, ID_LISTIMG_Especial, s_CUI_ID_FRAME_CompoundID_LISTIMG_EspecialOnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_Compound, ID_LISTIMG_Especial, s_CUI_ID_FRAME_CompoundID_LISTIMG_EspecialOnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_Compound, ID_LISTIMG_Especial, s_CUI_ID_FRAME_CompoundID_LISTIMG_EspecialOnIconRButtonUp );

	m_pID_FRAME_Compound = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Compound );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_CLOSE );
	m_pID_LISTIMG_Prescription = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Prescription );
	m_pID_BUTTON_Compound = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_Compound );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Material );
	m_pID_LISTIMG_Aim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Aim );
// 	m_pID_LISTIMG_Aim1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Aim1 );
// 	m_pID_LISTIMG_Aim2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Aim2 );
	m_pID_EDIT_Info = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Compound, ID_EDIT_Info );
	m_pID_TEXT_ResultInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_ResultInfo );
	m_pID_LISTIMG_M1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_M1 );
	m_pID_LISTIMG_M2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_M2 );
	m_pID_LISTIMG_M3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_M3 );
	m_pID_LISTIMG_M4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_M4 );
	m_pID_LIST_ComName = (ControlList*)theUiManager.FindControl( ID_FRAME_Compound, ID_LIST_ComName);
	
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Info );
	//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_help );
	m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Rate );
// 	m_pID_TEXT_Rate1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Rate1 );
// 	m_pID_TEXT_Rate2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Rate2 );

	m_pID_TEXT_M1Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M1Name );
	m_pID_TEXT_M1Info = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M1Info );

	m_pID_TEXT_M2Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M2Name );
	m_pID_TEXT_M2Info = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M2Info );

	m_pID_TEXT_M3Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M3Name );
	m_pID_TEXT_M3Info = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M3Info );

	m_pID_TEXT_M4Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M4Name );
	m_pID_TEXT_M4Info = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_M4Info );

//	m_pID_TEXT_Jin = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Jin );
	m_pID_TEXT_Ying = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Ying );

	m_pID_EDIT_Number = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Compound, ID_EDIT_Number );
	m_pID_EDIT_Number->SetTextChangedFun(ID_EDIT_NumberOnTextChanged);

	m_pID_BUTTON_Man = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_Man );
	m_pID_TEXT_NpcName = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_NpcName );

	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Compound, ID_PICTURE_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Compound, ID_PICTURE_Ying );
	//m_pID_PICTURE_Forging = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Compound, ID_PICTURE_Forging );

	m_pID_BUTTON_Stop = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_Stop );

	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Money );

	m_pID_TEXT_ExpendEnergy = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_ExpendEnergy );
	m_pID_TEXT_Energy = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Energy );

	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_Compound, ID_BUTTON_Down );
// 	m_pID_LISTIMG_Especial = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Compound, ID_LISTIMG_Especial );

	m_pID_TEXT_AimName  = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_AimName );
// 	m_pID_TEXT_Aim1Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Aim1Name);
// 	m_pID_TEXT_Aim2Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Aim2Name);
// 	m_pID_TEXT_SkillLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_SkillLvl);
// 	m_pID_TEXT_Skill = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_Skill);

	//m_pID_TEXT_EspecialName = (ControlText*)theUiManager.FindControl( ID_FRAME_Compound, ID_TEXT_EspecialName);

	assert( m_pID_FRAME_Compound );

	m_pID_FRAME_Compound->SetVisable(false);
	m_pID_FRAME_Compound->SetOnVisibleChangedFun(CUI_ID_FRAME_Compound::Compound_OnVisiableChanged);

	//theUiManager.SetFrameLayout(UI_LAYOUT_2, m_pID_FRAME_Compound);

	//CUILayout::GetInstance()->AddFrame( m_pID_FRAME_Compound);

// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_LISTIMG_Prescription );
// 	assert( m_pID_BUTTON_Compound );
// 	assert( m_pID_LISTIMG_Material );
// 	assert( m_pID_LISTIMG_Aim );
// 	assert( m_pID_EDIT_Info );
// 	assert( m_pID_TEXT_ResultInfo );
// 	assert( m_pID_LISTIMG_M1 );
// 	assert( m_pID_LISTIMG_M2 );
// 	assert( m_pID_LISTIMG_M3 );
// 	assert( m_pID_LISTIMG_M4 );
// 	assert( m_pID_LIST_ComName );
// 	assert( m_pID_TEXT_Info );
// 	assert(m_pID_TEXT_Rate);
// 	assert(m_pID_TEXT_Rate1);
// 	assert(m_pID_TEXT_Rate2);
// 	assert(m_pID_TEXT_Money);


	GetUICompoundMgr()->AddBgCompoundicon( m_pID_LISTIMG_M1 );
	GetUICompoundMgr()->AddBgCompoundicon( m_pID_LISTIMG_M2 );
	GetUICompoundMgr()->AddBgCompoundicon( m_pID_LISTIMG_M3 );
	GetUICompoundMgr()->AddBgCompoundicon( m_pID_LISTIMG_M4 );
	m_pID_LIST_ComName->SetCanLDB(false);

	//GetUICompoundMgr()->Init( m_pID_FRAME_Compound );

	m_pID_LISTIMG_Material->SetVisable( false );
	//GetUICompoundMgr()->AddBgCompoundicon( );
	USE_SCRIPT( eUI_OBJECT_Compound, this );

	//LoadCompound("..\\Data\\Config\\CreateItemRule.slk");

//	assert( m_pID_BUTTON_help );
	//m_pID_BUTTON_help->SetButtonClickFun( CUI_ID_FRAME_Compound::helpOnClick );

	m_pID_LISTIMG_M1->SetCanbePick(false);
	m_pID_LISTIMG_M1->ShowPressEffect(false);
	m_pID_LISTIMG_M2->SetCanbePick(false);
	m_pID_LISTIMG_M2->ShowPressEffect(false);
	m_pID_LISTIMG_M3->SetCanbePick(false);
	m_pID_LISTIMG_M3->ShowPressEffect(false);
	m_pID_LISTIMG_M4->SetCanbePick(false);
	m_pID_LISTIMG_M4->ShowPressEffect(false);
	m_pID_LISTIMG_Aim->SetCanbePick(false);
	m_pID_LISTIMG_Aim->ShowPressEffect(false);
// 	m_pID_LISTIMG_Aim1->SetCanbePick(false);
// 	m_pID_LISTIMG_Aim1->ShowPressEffect(false);
// 	m_pID_LISTIMG_Aim2->SetCanbePick(false);
// 	m_pID_LISTIMG_Aim2->ShowPressEffect(false);


	s_TargetControlGroup[0].m_pListImg = m_pID_LISTIMG_Aim;
	s_TargetControlGroup[0].m_pName = m_pID_TEXT_AimName;
	s_TargetControlGroup[0].m_pRate = m_pID_TEXT_Rate;
// 	s_TargetControlGroup[1].m_pListImg = m_pID_LISTIMG_Aim1;
// 	s_TargetControlGroup[1].m_pName = m_pID_TEXT_Aim1Name;
// 	s_TargetControlGroup[1].m_pRate = m_pID_TEXT_Rate1;
// 	s_TargetControlGroup[2].m_pListImg = m_pID_LISTIMG_Aim2;
// 	s_TargetControlGroup[2].m_pName = m_pID_TEXT_Aim2Name;
// 	s_TargetControlGroup[2].m_pRate = m_pID_TEXT_Rate2;

	//m_pID_EDIT_Number->SetNumberLimit(true, 0, 0);

	//ID_CHECKBOX_ForgingOnCheckBoxCheck(0, 0);
	return true;
	unguard;
}
bool CUI_ID_FRAME_Compound::helpOnClick( ControlObject* pSender )
{
	guardfunc;
	// 		s_CUI_ID_FRAME_Help.SetVisable( !s_CUI_ID_FRAME_Help.IsVisable() );
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Compound::_UnLoadUI()
{
	guardfunc;
	SaveCollapseInfo();
	theUiManager.RemoveFrameLayout(m_pID_FRAME_Compound);

	MapCompundInfo.clear();

	CLOSE_SCRIPT( eUI_OBJECT_Compound );
	GetUICompoundMgr()->Destroy();
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Compound.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Compound::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Compound )
		return false;
	return m_pID_FRAME_Compound->IsVisable();
	unguard;
}

void CUI_ID_FRAME_Compound::UpdateCompoundItems()
{
	if( !m_pID_FRAME_Compound )
		return;

	RetrieveRuleList();
	//ID_LISTIMG_EspecialOnIconRButtonUp(0,0);
	m_pID_LIST_ComName->Clear();
	m_pID_LIST_ComName->SetScrollValue( 0 );		
	*m_pID_TEXT_Info = "";
	*m_pID_TEXT_ResultInfo = "";
	*m_pID_TEXT_Rate = "";
// 	*m_pID_TEXT_Rate1 = "";
// 	*m_pID_TEXT_Rate2 = "";

	*m_pID_TEXT_AimName = "";
// 	*m_pID_TEXT_Aim1Name = "";
// 	*m_pID_TEXT_Aim2Name = "";
// 	*m_pID_TEXT_SkillLvl = "";

	*m_pID_TEXT_M1Name = "";
	*m_pID_TEXT_M1Info = "";
	*m_pID_TEXT_M2Name = "";
	*m_pID_TEXT_M2Info = "";
	*m_pID_TEXT_M3Name = "";
	*m_pID_TEXT_M3Info = "";
	*m_pID_TEXT_M4Name = "";
	*m_pID_TEXT_M4Info = "";

//	*m_pID_TEXT_Jin = "";
	*m_pID_TEXT_Ying = "";
	*m_pID_TEXT_ExpendEnergy = "";
// 	*m_pID_TEXT_EspecialName = "";		
// 	*m_pID_TEXT_Skill = "";
	*m_pID_EDIT_Number = "1";

	m_pID_LISTIMG_M1->Clear();
	m_pID_LISTIMG_M2->Clear();
	m_pID_LISTIMG_M3->Clear();
	m_pID_LISTIMG_M4->Clear();
	m_pID_LISTIMG_Aim->Clear();
// 	m_pID_LISTIMG_Aim1->Clear();
// 	m_pID_LISTIMG_Aim2->Clear();

	m_nSingleMoney = 0;
	m_nSingleEnergy = 0;

	if (!m_bIsCando)
	{
		m_pID_BUTTON_Compound->SetEnable(false);
		m_pID_BUTTON_Stop->SetEnable(false);
	}

	RefreshPlayerProperty();

	m_nRuleID = 0;
	s_pTargetProduct = 0;

	if ( s_mapCompoundRules.size() == 0 )
	{
		return;
	}
	// 0:炼药
	// 1:裁缝
	// 2:打造
	// 3:烹饪
	// 4:茶艺
	// 5:材料加工
	std::map< unsigned int, RecipeConfig::SRecipe >::iterator iter0 = s_mapCompoundRules.begin();
	for ( ; iter0 != s_mapCompoundRules.end(); ++ iter0 )
	{
		RecipeConfig::SRecipe* pRule  = &(*iter0).second;

		if ( pRule )
		{
			if(pRule->SubType != 0)
				continue;
			DWORD color = 0xffffffff;
			DWORD grayColor = 0xff757575;
			if( pRule->ProficiencyLimit < g_dwSkillPoint )//灰色，不加熟练度
				color = grayColor;
			ControlList::S_List sData;
			sData.SetData( pRule->Name.c_str(), pRule->RecipeId, 0, color );
			m_pID_LIST_ComName->AddItem(&sData,NULL,false);
		}
	}
	for (int i = 1; i <= ERT_MaxType; ++i)
	{
		bool isFirst = true;
		std::map< unsigned int, RecipeConfig::SRecipe >::iterator iter = s_mapCompoundRules.begin();
		for ( ; iter != s_mapCompoundRules.end(); ++ iter )
		{
			RecipeConfig::SRecipe* pRule  = &(*iter).second;

			if ( pRule )
			{
				if(pRule->SubType != i)
					continue;
				DWORD color = 0xffffffff;
				DWORD grayColor = 0xff757575;
				if( pRule->ProficiencyLimit < g_dwSkillPoint )//灰色，不加熟练度
					color = grayColor;
				ControlList::S_List sData;
				if (isFirst)
				{
					sData.m_nHiberarchy = 0;
					bool bCollapse = false;
					for(int z = 0; z < m_RecordArr[m_CurrRecipeType].size(); ++z )
					{
						if (m_RecordArr[m_CurrRecipeType][z].m_nSubType == pRule->SubType)
						{
							bCollapse = m_RecordArr[m_CurrRecipeType][z].m_isCollapse;
						}
					}
					sData.m_bCollapse = bCollapse;
					sData.SetData( pRule->SubTypeName.c_str(), pRule->SubType);
					m_pID_LIST_ComName->AddItem(&sData,NULL,false);						
					isFirst = false;
				}
				sData.m_nHiberarchy = 1;
				sData.SetData( pRule->Name.c_str(), pRule->RecipeId, 0, color );
				m_pID_LIST_ComName->AddItem(&sData,NULL,false);
			}
		}
	}

	RefreshSelectRecipe();
	if( m_pID_LIST_ComName->GetCurSelIndex() == -1 )			
		m_pID_LIST_ComName->SetCurSelIndex( 0 );
}

void CUI_ID_FRAME_Compound::OpenUI( int nType )
{
	guardfunc;
	if( nType < 0 || nType > GetUICompoundMgr()->eMaxCompound )
		return;

	UpdateCompoundItems();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Compound::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Compound )
		return;
	m_pID_FRAME_Compound->SetVisable( bVisable );

	// commneted out, jiayi, [2009/8/31]
	// boss liu
	// 		if (bVisable)
	// 			theHeroGame.GetPlayerMgr()->GetMe()->StopMoving();

	if ( bVisable )
	{
		m_nCompoundMaxCount = 0;
		m_nCompoundCurrCount = 0;
		UpdateCompoundItems();
		*m_pID_TEXT_ResultInfo = "";
		Refeash();
		if( m_bIsCando )
		{
			m_bIsCando = false;
			m_pID_BUTTON_Compound->SetEnable(false);
			m_pID_BUTTON_Stop->SetEnable(false);
		}
	}
	else
	{
		RecordCollapseInfo();
	}
	if (bVisable)
	{
		// 			s_CUI_ID_FRAME_Task.SetVisable(false);
		// 			s_CUI_ID_FRAME_GroupPanel.SetVisable(false);
		// 			s_CUI_ID_FRAME_Gang.SetVisable(false);			
	}
	unguard;
}

bool CUI_ID_FRAME_Compound::IsGrid(const ControlObject* pSender)
{
	guardfunc;
	if( !m_pID_FRAME_Compound )
		return false;
	if( pSender == m_pID_LISTIMG_M1 ||
		pSender == m_pID_LISTIMG_M2 ||
		pSender == m_pID_LISTIMG_M3 ||
		pSender == m_pID_LISTIMG_M4 )
	{
		return true;
	}
	else
	{
		return false;
	}
	unguard;
}

void CUI_ID_FRAME_Compound::Refeash()
{
	guardfunc;
	if( !m_pID_FRAME_Compound )
		return;
	s_CUI_ID_FRAME_PACK.RefreshMaterialPack();
	//if( m_pID_LISTIMG_Prescription )
	//	m_pID_LISTIMG_Prescription->Clear();
	//if( m_pID_LISTIMG_Material)
	//	m_pID_LISTIMG_Material->Clear();
	//if( m_pID_LISTIMG_Aim)
	//	m_pID_LISTIMG_Aim->Clear();
	//if( m_pID_LISTIMG_M1 )
	//	m_pID_LISTIMG_M1->Clear();
	//if( m_pID_LISTIMG_M2 )
	//	m_pID_LISTIMG_M2->Clear();
	//if( m_pID_LISTIMG_M3 )
	//	m_pID_LISTIMG_M3->Clear();
	//if( m_pID_LISTIMG_M4 )
	//	m_pID_LISTIMG_M4->Clear();

	//*m_pID_EDIT_Info = "";
	/**m_pID_TEXT_ResultInfo = "";*/
	//
	//ControlIconDrag::S_ListImg stListImg; 
	//stListImg.SetData( &thePlayerRole.m_pCompound->stPrescription );
	//m_pID_LISTIMG_Prescription->SetItem( &stListImg, 0 );
	//if ( thePlayerRole.m_pCompound->stPrescription.itembaseinfo.ustItemID == 
	//	ErrorUnsignedShortID )
	//{
	//	//*m_pID_EDIT_Info = "请放入3个同级别的宝石进行提炼";
	//}
	//
	//stListImg.SetData( &thePlayerRole.m_pCompound->stAim );
	//m_pID_LISTIMG_Aim->SetItem( &stListImg, 0 );
	////
	//for ( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
	//{
	//	stListImg.SetData( &thePlayerRole.m_pCompound->stMaterial[n] );
	//	m_pID_LISTIMG_Material->SetItem( &stListImg, n );
	//	if( n == 0 )
	//	{
	//		m_pID_LISTIMG_M1->SetItem( &stListImg, 0 );
	//	}
	//	if( n== 1)
	//		m_pID_LISTIMG_M2->SetItem( &stListImg, 0 );
	//	if( n==2 )
	//		m_pID_LISTIMG_M3->SetItem( &stListImg, 0 );
	//	if( n==3 )
	//		m_pID_LISTIMG_M4->SetItem( &stListImg, 0 );

	//}

	//
	//ControlIconDrag::S_ListImg *pListImg = m_pID_LISTIMG_Prescription->GetItemByIndex( 0 );
	//if ( pListImg && !pListImg->IsNull() )
	//{
	//	std::string strInfo;
	//	for( int n=0; n<pListImg->m_pkIconInfo->m_nIconInfoLine; n++ )
	//	{
	//		strInfo += pListImg->m_pkIconInfo->m_stInfo[n].m_strInfo + "\n";
	//	}
	//	*m_pID_EDIT_Info = strInfo;
	//}
	unguard;
}

int	CUI_ID_FRAME_Compound::GetItemIndexFromGrid( const ControlIconDrag::S_ListImg *pImg )
{
	guardfunc;
	int nSrcIndex = ErrorUnsignedLongID;
	if( !m_pID_FRAME_Compound )
		return nSrcIndex;

	nSrcIndex = m_pID_LISTIMG_M1->GetItemIndex( pImg );
	if( nSrcIndex == ErrorUnsignedLongID )
	{
		nSrcIndex = m_pID_LISTIMG_M2->GetItemIndex( pImg );
		if( nSrcIndex == ErrorUnsignedLongID )
		{
			nSrcIndex = m_pID_LISTIMG_M3->GetItemIndex( pImg );
			if( nSrcIndex == ErrorUnsignedLongID )
			{
				nSrcIndex = m_pID_LISTIMG_M4->GetItemIndex( pImg );
				if( nSrcIndex != ErrorUnsignedLongID )
				{
					nSrcIndex = 3;
				}
			}
			else
			{
				nSrcIndex = 2;
			}
		}
		else
		{
			nSrcIndex = 1;
		}
	}
	else
	{
		nSrcIndex = 0;
	}

	return nSrcIndex; 
	unguard;
}

void CUI_ID_FRAME_Compound::Compound( MsgAckCompound* pAckCompound )
{
	guardfunc;
	if( !m_pID_FRAME_Compound )
		return;

	if (!pAckCompound)
	{
		return;
	}
	switch( pAckCompound->stResult ) 
	{
	case MsgAckCompound::eResultSuccess:
		{
			//*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_CompSucess);
			//s_CUI_ID_FRAME_InfoList. AddInfo( theXmlString.GetString(eText_CompSucess), Color_Config.getColor( CC_SystemPromp ) );
			PlaySoundConfig( SoundConfig::EST_ForgingSuccess );
		}
		break;
	case MsgAckCompound::eResultFaild:
		{
			//*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_CompFail);//"合成失败";
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString(eText_CompFail) );
			PlaySoundConfig( SoundConfig::EST_ForgingFailed );			
		}
		break;
	case MsgAckCompound::eResultMaterialUnconformity:
		{
			//*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Material_Error_0);//"原料不符合";
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Produce_Belongs, theXmlString.GetString(eText_Material_Error_0) );
		}
		break;
	case MsgAckCompound::eResultGemIsMaxLevel:
		{
			//*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Material_error_1);//"宝石等级已是最高级";
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eText_Material_error_1) );
		}
		break;
	case MsgAckCompound::eResultNotEnoughMoney:
		{
			//*m_pID_TEXT_ResultInfo = theXmlString.GetString(eExchange_NotMoney);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eExchange_NotMoney) );
		}
		break;
	default:
		assert( false );
		break;
	}

	//m_pID_LISTIMG_M1->SetCanbePick(true);
	//m_pID_LISTIMG_M2->SetCanbePick(true);
	//m_pID_LISTIMG_M3->SetCanbePick(true);
	//m_pID_LISTIMG_M4->SetCanbePick(true);
	//m_pID_LISTIMG_Aim->SetCanbePick(true);

	//switch( pAckCompound->stResult ) 
	//{
	//case MsgAckCompound::eResultSuccess:
	//	{
	//		thePlayerRole.m_pCompound->stPrescription.itembaseinfo.ustItemID = ErrorUnsignedShortID;
	//		for( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
	//		{
	//			/*thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemID = ErrorUnsignedShortID;*/
	//			if (pAckCompound->nMaterialNum[n] <= 0)
	//			{
	//				thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemID = ErrorUnsignedShortID;
	//			}
	//			else
	//				thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemCount = pAckCompound->nMaterialNum[n];					
	//		}
	//		thePlayerRole.m_pCompound->stAim = pAckCompound->stAim;
	//		//
	//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_CompSucess);
	//	}
	//	break;
	//case MsgAckCompound::eResultFaild:
	//	{
	//		thePlayerRole.m_pCompound->stPrescription.itembaseinfo.ustItemID = ErrorUnsignedShortID;
	//		for( int n=0; n<ITEM_COMPOUND_BAGMAX; n++ )
	//		{
	//			/*thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemID = ErrorUnsignedShortID;*/
	//			if (pAckCompound->nMaterialNum[n] <= 0)
	//			{
	//				thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemID = ErrorUnsignedShortID;
	//			}
	//			else
	//				thePlayerRole.m_pCompound->stMaterial[n].itembaseinfo.ustItemCount = pAckCompound->nMaterialNum[n];					
	//		}
	//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_CompFail);//"合成失败";
	//	}
	//	break;
	//case MsgAckCompound::eResultMaterialUnconformity:
	//	{
	//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Material_Error_0);//"原料不符合";
	//	}
	//	break;
	//case MsgAckCompound::eResultGemIsMaxLevel:
	//	{
	//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eText_Material_error_1);//"宝石等级已是最高级";
	//	}
	//	break;
	//case MsgAckCompound::eResultNotEnoughMoney:
	//	{
	//		*m_pID_TEXT_ResultInfo = theXmlString.GetString(eExchange_NotMoney);
	//	}
	//	break;
	//default:
	//	assert( false );
	//	break;
	//}
	Refeash();
	unguard;
}

//--sbw add

void CUI_ID_FRAME_Compound::LoadCompound( const char *szName )	//load 配方slk文件
{
	if( !MapCompundInfo.empty() )
		return;
	//if (!m_vecCompundInfo.empty())
	//	return;

	CSlkReader reader;
	int iRet;
	int iRow = 2;
	if( !reader.ReadFromFile(szName))
	{
		assert(false && "NpcCoord::load 读取文件出错");
		return;
	}

	std::string strName;
	ComDescription info;

	while(CSlkReader::ret_readover != ( iRet = reader.GotoNextLine(iRow++)))
	{
		if(CSlkReader::ret_nothisline == iRet)
			continue;

		memset(&info, 0, sizeof(info));
		if( !reader.GetIntFieldByName("itemID", info._nID))
		{
			//assert()
		}
		if( !reader.GetStringFieldByName("ItemName", info._szItemName))
		{
			//assert()
		}
		if( !reader.GetStringFieldByName("Material1", info._szOneName))
		{
			//assert()
		}
		if( !reader.GetIntFieldByName("Material1Num", info._nOneCnt))
		{
			//assert()
		}
		if( !reader.GetStringFieldByName("Material2", info._szTwoName))
		{
			//assert()
		}
		if( !reader.GetIntFieldByName("Material2Num", info._nTwoCnt))
		{
			//assert()
		}
		if( !reader.GetStringFieldByName("Material3", info._szThreeName))
		{
			//assert()
		}
		if( !reader.GetIntFieldByName("Material3Num", info._nThreeCnt))
		{
			//assert()
		}
		if (!reader.GetIntFieldByName("NeedMoney",info._nMenoy))
		{
		}

		MapCompundInfo[info._szItemName] = info;
		/*m_vecCompundInfo.push_back(&info);*/

		//ControlList::S_List sData;
		//sData.SetData( strName.c_str());
		//m_pID_LIST_ComName->AddItem(&sData);

	}
}

CUI_ID_FRAME_Compound::ComDescription& CUI_ID_FRAME_Compound::GetComDescription( const char *szName )
{
	string strName = szName;
	map<string, ComDescription>::iterator iter = MapCompundInfo.find(strName);
	if(iter != MapCompundInfo.end())
		return iter->second;

	static ComDescription info;
	memset(&info, 0, sizeof(info));
	return info;
}

void CUI_ID_FRAME_Compound::SetBegin( int nBegin)
{
	_begin = nBegin;
}
void CUI_ID_FRAME_Compound::SetEnd(int nEnd)
{
	_end = nEnd;
}

int CUI_ID_FRAME_Compound::GetBegin()
{
	return _begin;
}
int CUI_ID_FRAME_Compound::GetEnd()
{
	return _end;
}

void CUI_ID_FRAME_Compound::SetCreatRuloId(int nCreatRoleID,int nCount)
{
	// 		if (nCount > MAX_ID)
	// 			nCount = MAX_ID;
	// 
	// 		m_nIDCount = nCount;
	// 
	// 		if (nCreatRoleID > 0)
	// 		{
	// 			for (int n = 0; n < nCount; n++)
	// 			{
	// 				if (m_nCreatID[n] == 0)
	// 				{
	// 					m_nCreatID[n] = nCreatRoleID;
	// 					return;
	// 				}
	// 			}
	// 		}
}
RecipeConfig::SRecipe* CUI_ID_FRAME_Compound::GetCompoundRuleById(int nId)
{
	if( s_mapCompoundRules.find( nId ) != s_mapCompoundRules.end() )
		return &s_mapCompoundRules[ nId ];		
	return 0;
}

void CUI_ID_FRAME_Compound::SetNpcId(int nNpcId)
{
	if( !m_pID_FRAME_Compound )
		return;

	m_nNpcId = nNpcId;

	CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
	if ( pNpc )
	{
		std::string title = pNpc->GetTitle();
		if (title.length() > 2)
			m_pID_TEXT_NpcName->SetText(title.substr(1, title.length() - 2));
		else
			m_pID_TEXT_NpcName->SetText(pNpc->GetName());
	}
}

/*void CUI_ID_FRAME_Compound::ClearSpr()
{
	*m_pID_TEXT_Info = NULL;
}*/

void CUI_ID_FRAME_Compound::FillMaterial( RecipeConfig::SMaterial* pMat, ControlListImage* pListImg, ControlText* pCtrlName, ControlText* pCtrlInfo )
{
	if(pMat->vecMaterailIDList.empty())
		return;

	int nHaveCount = 0;
	ItemDefine::SItemCommon *pItemCommon = NULL;
	for (int i = 0;i < pMat->vecMaterailIDList.size();++i)
	{
		pItemCommon = GettheItemDetail().GetItemByID( pMat->vecMaterailIDList[i]);
		if (!pItemCommon)
			continue;

		switch (pItemCommon->ucItemType)
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
			{
				nHaveCount += thePlayerRole.m_bagMaterial.GetItemCount(pItemCommon->ustItemID);
			}
			break;
		case ItemDefine::ITEMTYPE_TASK:
			{
				nHaveCount += thePlayerRole.m_bagTask.GetItemCount(pItemCommon->ustItemID);
			}
			break;
		default:
			{
				nHaveCount += thePlayerRole.m_bag.GetItemCount(pItemCommon->ustItemID);
			}
			break;
		}

		//nHaveCount += thePlayerRole.m_bagMaterial.GetItemCount(pItemCommon->ustItemID);
	}

	char buf[128] = {0};
	if (nHaveCount < pMat->Count )
	{
		bIsCan = false;
		MeSprintf_s(buf,sizeof(buf), "{#FFFF0000=%d / %d#}", nHaveCount, pMat->Count);
	}
	else
		MeSprintf_s(buf,sizeof(buf),"{#FF00FF00=%d / %d#}", nHaveCount, pMat->Count);

	if( m_nCompoundMaxCount == 0 )
		m_nCompoundMaxCount = nHaveCount / pMat->Count ;
	else
		m_nCompoundMaxCount = min( m_nCompoundMaxCount, nHaveCount / pMat->Count );

	Common::_tstring tstrName = "";
	if(pItemCommon)
	{
		tstrName = pItemCommon->GetItemName();
		S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
		pCtrlName->SetText( tstrName.c_str(), S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ) );
		ControlIconDrag::S_ListImg stItem;
		stItem.SetData(pItemCommon->ustItemID, 0);
		pListImg->SetItem(&stItem, 0);
	}
	else	
	{
		pCtrlName->SetText( tstrName.c_str() );
		pListImg->Clear();
	}
	*pCtrlInfo = buf;


	//s_ucProductType = pItemCommon->ucItemType;	
}

void CUI_ID_FRAME_Compound::RefreshPlayerProperty()
{
	if( !m_pID_FRAME_Compound )
		return;

	// money
	DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	if( m_pID_TEXT_Money )
	{
		std::string text = "";
        thePlayerRole.GetGSCStringFromMoney(dwMoney,text);
		ExpressionManager::GetInstance().AddExpressionAni(text);

		*m_pID_TEXT_Money = text;
	}

	// 活力
	m_pID_TEXT_Energy->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_ENERGY));

	// 熟练度
// 	DWORD skillPointType = 0;
// 	DWORD skillPointString = -1;
// 	if( m_pID_CHECKBOX_Forging->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_DuanZao;
// 		skillPointString = eText_DuanZao_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_DaZao));
// 	}
// 	else if( m_pID_CHECKBOX_Sewing->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_ZhuBao;
// 		skillPointString = eText_ZhuBao_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_HeCheng));
// 	}
// 	else if( m_pID_CHECKBOX_Cooking->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_ZhuJia;
// 		skillPointString = eText_ZhuJia_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_PengRen));
// 	}
// 	else if( m_pID_CHECKBOX_Tea->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_GongYi;
// 		skillPointString = eText_GongYi_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_ChaYi));
// 	}
// 	else if( m_pID_CHECKBOX_Drug->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_CaoYao;
// 		skillPointString = eText_CaoYao_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_LianYao));
// 	}
// 	else if( m_pID_CHECKBOX_Brewing->IsChecked() )
// 	{
// 		skillPointType = CPlayerRole::TYPE_XunMa;
// 		skillPointString = eText_XunMa_SkillPoint;
// 		m_pID_PICTURE_Forging->setTip(theXmlString.GetString(eText_CompoundMaterialTip_JiaGong));
// 	}
// 
// 	if( !m_pID_CHECKBOX_Forging->IsChecked() && !m_pID_CHECKBOX_Brewing->IsChecked() && !m_pID_CHECKBOX_Sewing->IsChecked() )
// 	{
// 		g_dwSkillPoint = thePlayerRole.GetData( (CPlayerRole::enUpdataType)skillPointType );
// 		m_pID_TEXT_SkillLvl->SetText( g_dwSkillPoint );
// 		char szBuff[255];
// 		sprintf_s( szBuff, 255, "%s", theXmlString.GetString( skillPointString ) );
// 		m_pID_TEXT_Skill->SetText( szBuff );
// 	}
}

void CUI_ID_FRAME_Compound::RefreshTargetItem( bool bHaveEspecial )
{
	ControlList::S_List *pstList = m_pID_LIST_ComName->GetCurSelItem();
	if (!pstList)
		return ;

	RecipeConfig::SRecipe* pRule = GetCompoundRuleById( pstList->m_nID );
	if ( !pRule )
		return;

	char szBuff[255];
	s_pTargetProduct = 0;

	//ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Especial->GetItemByIndex( 0 );		
	//if( bHaveEspecial && pItemImg )
	//{
	//	// ui上有icon，这里要判断对应的包里是否还有此件物品，没有则清空这个ui
	//	SCharItem stBagItem;
	//	if( thePlayerRole.m_bagMaterial.GetItemByItemID( pItemImg->m_pkIconInfo->GetItemId(), &stBagItem ) )
	//	{
	//		for( int i = 0 ; i < pRule->Products.size() ; ++ i )
	//		{
	//			RecipeConfig::SProduct* pProduct = &pRule->Products[i];
	//			for( int j = 0 ; j < pProduct->SecondaryMaterials.size(); ++ j )
	//			{
	//				RecipeConfig::SMaterial* pSecMat = &pProduct->SecondaryMaterials[j];
	//				if( pSecMat && ( pSecMat->MaterialId == pItemImg->m_pkIconInfo->GetItemId() ) )
	//				{
	//					s_pTargetProduct = pProduct;	
	//					// 这里更新最大产出值，根据辅助材料的数量
	//					int nAccessoryMatCount = thePlayerRole.m_bagMaterial.GetItemCount( pSecMat->MaterialId );
	//					// 因为辅助物品每次只消耗一个，所以这里可以指定为一
	//					if( m_nCompoundMaxCount != 0 )
	//						m_nCompoundMaxCount = min( m_nCompoundMaxCount, nAccessoryMatCount );
	//				}
	//			}

	//		}
	//	}	
	//	else // 清空ui
	//	{
	//		//ID_LISTIMG_EspecialOnIconRButtonUp( 0, 0 );
	//	}
	//}

	// 没有显示目标物品，原因可能是没有辅助材料或者不需要辅助材料
	// 所以这里显示不需要辅助材料的物品
	if( !s_pTargetProduct ) 
	{
		for( int i = 0 ; i < pRule->Products.size() ; ++ i )
		{
			RecipeConfig::SProduct* pProduct = &pRule->Products[i];
			if( !pProduct )
				continue;
			if( pProduct->IsHaveSecondaryMaterials() )
				continue;

			// 没有辅助材料的产品
			s_pTargetProduct = pProduct;
			break;
		}
	}
	// 这里显示ui部分，用挑选出来的product
	if( s_pTargetProduct )
	{
		// 记录id
		m_nRuleID = pRule->RecipeId;
		// 显示该目标物品
		for( int nTarget = 0 ; nTarget < s_nMaxTargetItem/*s_pTargetProduct->ProductItems.size()*/; ++ nTarget )
		{
			if( nTarget < s_pTargetProduct->ProductItems.size() )
			{
				RecipeConfig::SItem* pItem = &s_pTargetProduct->ProductItems[nTarget];			

				if ( s_pTargetProduct->ProductItems.size() == 1 )
				{
					// 添加名称，颜色根据品质
					ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->ItemId );				
					if( !pItemCommon )
						continue;
					DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
					Common::_tstring tstrName( pItemCommon->GetItemName() );
					S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
					s_TargetControlGroup[nTarget].m_pName->SetText( tstrName.c_str(), dwColor );	
					// 添加成功率				
					sprintf_s( szBuff, 255, "%s %d%s", theXmlString.GetString( eText_ProduceRate ), pItem->Probility, "%" );									
					*( s_TargetControlGroup[nTarget].m_pRate ) = szBuff;
					// 添加item
					ControlIconDrag::S_ListImg stItem;
					stItem.SetData( pItem->ItemId, pItem->Count, eIcon_Enable, true );
					s_TargetControlGroup[nTarget].m_pListImg->SetItem( &stItem, 0 );
				}
				else if ( s_pTargetProduct->ProductItems.size() > 1 )
				{
					ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( SID_UnKnowItem );				
					if( !pItemCommon )
						continue;
					DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
					Common::_tstring tstrName( pItemCommon->GetItemName() );
					S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
					s_TargetControlGroup[nTarget].m_pName->SetText( tstrName.c_str(), dwColor );
					// 添加成功率				
					sprintf_s( szBuff, 255, "%s %d%s", theXmlString.GetString( eText_ProduceRate ), 100, "%" );									
					*( s_TargetControlGroup[nTarget].m_pRate ) = szBuff;
					// 添加item
					ControlIconDrag::S_ListImg stItem;
					stItem.SetData( SID_UnKnowItem, 1, eIcon_Enable, true );
					s_TargetControlGroup[nTarget].m_pListImg->SetItem( &stItem, 0 );
				}
								
			}
			else
			{
				*( s_TargetControlGroup[nTarget].m_pName ) = "";
				*( s_TargetControlGroup[nTarget].m_pRate ) = "";					
				s_TargetControlGroup[nTarget].m_pListImg->Clear();
			}

		}
		// 显示消耗金钱，精力等信息
		m_nSingleMoney = s_pTargetProduct->NeedMoney;
		m_nSingleEnergy = s_pTargetProduct->NeedActivity;

        DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) + thePlayerRole.GetData(CPlayerRole::TYPE_JiaoZi);

		if (m_nSingleMoney > 0)
			m_nCompoundMaxCount = min(m_nCompoundMaxCount, dwMoney / m_nSingleMoney);			
		if (m_nSingleEnergy > 0)
			m_nCompoundMaxCount = min(m_nCompoundMaxCount, thePlayerRole.GetData(CPlayerRole::TYPE_ENERGY) / m_nSingleEnergy);

		if (bIsCan)
		{
			if (m_bIsCando)
			{
				*m_pID_EDIT_Number = m_nCompoundCurrCount;
				m_nCompoundCount = m_nCompoundCurrCount;
			}
			else
			{
				if (m_nCompoundMaxCount > 0)
				{
					//*m_pID_EDIT_Number = "1";
					//m_nCompoundCount = 1;
				}
				else
				{
					*m_pID_EDIT_Number = "0";
					m_nCompoundCount = 0;
				}
			}
		}
		else
		{
			*m_pID_EDIT_Number = "0";
			m_nCompoundCount = 0;
			m_nCompoundMaxCount = 0;
		}

		ChangeMoney(1);
	}

	//m_pID_EDIT_Number->SetNumberLimit(true, m_nCompoundCount, m_nCompoundMaxCount);
}

void CUI_ID_FRAME_Compound::RefreshSelectRecipe()
{		
	if( !m_pID_FRAME_Compound )
		return;
	ControlList::S_List *pstList = m_pID_LIST_ComName->GetCurSelItem();
	if (!pstList)
		return ;

	if(pstList->m_nHiberarchy == 0)
		return;

	RecipeConfig::SRecipe* pRule = GetCompoundRuleById( pstList->m_nID );
	if ( !pRule )
		return;

	//string strName = pstList->m_szText;
	//ComDescription info = GetComDescription(strName.c_str());

	char szTemp[512] = {0};
	char szInfo[256] = {0};
	char szRateTemp[128] = {0}; 

	bIsCan = true;
	m_nCompoundMaxCount = 0;
	s_ucProductType = 0;

	// 填写材料		
	if ( pRule->PrimaryMaterials.size() > 0)
	{
		FillMaterial( &pRule->PrimaryMaterials[0], m_pID_LISTIMG_M1, m_pID_TEXT_M1Name, m_pID_TEXT_M1Info );
	}

	if ( pRule->PrimaryMaterials.size() > 1)
	{
		FillMaterial( &pRule->PrimaryMaterials[1], m_pID_LISTIMG_M2, m_pID_TEXT_M2Name, m_pID_TEXT_M2Info );
	}

	if ( pRule->PrimaryMaterials.size() > 2)
	{
		FillMaterial( &pRule->PrimaryMaterials[2], m_pID_LISTIMG_M3, m_pID_TEXT_M3Name, m_pID_TEXT_M3Info );
	}

	if ( pRule->PrimaryMaterials.size() > 3)
	{
		FillMaterial( &pRule->PrimaryMaterials[3], m_pID_LISTIMG_M4, m_pID_TEXT_M4Name, m_pID_TEXT_M4Info );
	}		
	RefreshTargetItem( false );
	//RefreshTargetItem( ( m_pID_LISTIMG_Especial->GetNullItem() == -1 ) );

	// 		m_nSingleMoney = pCreateItem->nNeedMenoy;
	// 		m_nSingleEnergy = pCreateItem->nNeedEnergy;
	// 
	// 		if (m_nSingleMoney > 0)
	// 			m_nCompoundMaxCount = min(m_nCompoundMaxCount, dwMoney / m_nSingleMoney);
	// 		if (m_nSingleEnergy > 0)
	// 			m_nCompoundMaxCount = min(m_nCompoundMaxCount, thePlayerRole.GetData(CPlayerRole::TYPE_ENERGY) / m_nSingleEnergy);
	// 
	// 		if (bIsCan)
	// 		{
	// 			if (m_bIsCando)
	// 			{
	// 				*m_pID_EDIT_Number = m_nCompoundCurrCount;
	// 				m_nCompoundCount = m_nCompoundCurrCount;
	// 			}
	// 			else
	// 			{
	// 				if (m_nCompoundMaxCount > 0)
	// 				{
	// 					*m_pID_EDIT_Number = "1";
	// 					m_nCompoundCount = 1;
	// 				}
	// 				else
	// 				{
	// 					*m_pID_EDIT_Number = "0";
	// 					m_nCompoundCount = 0;
	// 				}
	// 			}
	// 		}
	// 		else
	// 		{
	// 			*m_pID_EDIT_Number = "0";
	// 			m_nCompoundCount = 0;
	// 		}
	// 
	// 		ChangeMoney(1);
	// 
	// 		// 目标物品		
	// 		if (pCreateItem->ustItemID != 0)
	// 		{
	// 			if (pCreateItem)
	// 			{
	// 				ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pCreateItem->ustTargetItemID);
	// 				if (pItem)
	// 				{
	// 					ControlIconDrag::S_ListImg stItem;
	// 					stItem.SetData(pItem->ustItemID, 0);
	// 					m_pID_LISTIMG_Aim->SetItem(&stItem, 0);
	// 				}
	// 
	// 				//pItem = GettheItemDetail().GetItemByID(pCreateItem->ustTargetItemID1);
	// 				//if (pItem)
	// 				//{
	// 				//	ControlIconDrag::S_ListImg stItem;
	// 				//	stItem.SetData(pItem->ustItemID, 0);
	// 				//	m_pID_LISTIMG_Aim1->SetItem(&stItem, 0);
	// 				//}
	// 
	// 				//pItem = GettheItemDetail().GetItemByID(pCreateItem->ustTargetItemID2);
	// 				//if (pItem)
	// 				//{
	// 				//	ControlIconDrag::S_ListImg stItem;
	// 				//	stItem.SetData(pItem->ustItemID, 0);
	// 				//	m_pID_LISTIMG_Aim2->SetItem(&stItem, 0);
	// 				//}
	// 
	// 				float fRateTemp = 0.0f;
	// 				fRateTemp = pCreateItem->iCreateSuccRate/100;
	// 				float fRateAdd = (float)thePlayerRole.m_nCompoundRateAdd/100.0f + 1.0f;				
	// 				fRateTemp *= fRateAdd;
	// 
	// 				_snprintf( szRateTemp, sizeof(szRateTemp) - 1, "%0.2f%%", fRateTemp );
	// 				*m_pID_TEXT_Rate = szRateTemp;
	// 			}
	// 		}
	// 		nCreatRoleID = pCreateItem->ustItemID;		

	if (!m_bIsCando)
	{
		int money = m_nSingleMoney * m_nCompoundCount;
		bool canCompound = thePlayerRole.HaveEnoughMoney(money) && m_nCompoundMaxCount > 0;			
		int energy = m_nSingleEnergy * m_nCompoundCount;
		canCompound = canCompound && energy <= thePlayerRole.GetData(CPlayerRole::TYPE_ENERGY);
		m_pID_BUTTON_Compound->SetEnable(canCompound);
		m_pID_BUTTON_Stop->SetEnable(false);
	}
}

void CUI_ID_FRAME_Compound::ClearResultInfo()
{
	*m_pID_TEXT_ResultInfo = "";
}

void CUI_ID_FRAME_Compound::ChangeMoney(int count)
{
	int money = m_nSingleMoney * count;
	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(money, text);
	//*m_pID_TEXT_Jin = text;

	int energy = m_nSingleEnergy * count;
	m_pID_TEXT_ExpendEnergy->SetText(energy);

	m_pID_PICTURE_Jin->SetVisable(false);
	m_pID_TEXT_Ying->SetVisable(false);
	m_pID_PICTURE_Ying->SetVisable(false);
	//m_pID_TEXT_Jin->SetVisable(money >= 0);
}

void CUI_ID_FRAME_Compound::ForgetRecipesByType( int nType )
{
    if( IsVisable() )
        SetVisable( false );

    for( int i = 0 ; i < MAX_RECIPE_COUNT; ++i )
    {
        int nRecipeId = thePlayerRole.GetCharInfo2().otherdataclient.recipes[i];
        if( nRecipeId != 0 )
        {
            RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRuleId( nRecipeId );
            if( pRecipe == NULL )
                continue;
            if( pRecipe->Type == nType )
                thePlayerRole.GetCharInfo2().otherdataclient.recipes[i] = 0;
        }
    }
    UpdateCompoundItems();
}
