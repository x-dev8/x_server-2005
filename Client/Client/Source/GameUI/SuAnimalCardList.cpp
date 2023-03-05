/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetCardList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalCardList.h"
#include "SuAnimalCard.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "baseProperty.h"
#include "Rename.h"
#include "Dxsdk/dinput.h"
#include "ui/PrivateShop.h"
#include "Me3d/ShaderManager.h"
#include "color_config.h"
#include "PrivateShop.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "exmain.h"
#include "Main.h"
#include "ActionUI.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "WealthProtect.h"
#include "MessageBox.h"
#include "ItemDetail.h"
#include "SoundConfig.h"
#include "SystemStallage.h"
#include "PetSettingConfig.h"
#include "MessageDefine.h"
#include "objbase.h"
#include "color_config.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "color_config.h"
#include "ItemDetailConfig.h"
#include "Create.h"
bool   CUI_ID_FRAME_SuAnimalCardList::m_IsClicked = false;
CUI_ID_FRAME_SuAnimalCardList s_CUI_ID_FRAME_SuAnimalCardList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalCardList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalCardList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_CLOSEOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_COMBOBOX_DistributeOnComboBoxChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_EDIT_ContentOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_LookupOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_LIST_PetNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_PageDownOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_FullOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_RenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_ShenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_XianOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_JiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_MoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_GuiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_YaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_CHECKBOX_ShouOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_PageUpFristOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalCardList, ID_BUTTON_PageDownLastOnButtonClick )

CUI_ID_FRAME_SuAnimalCardList::CUI_ID_FRAME_SuAnimalCardList()
{
	// Member
	m_pID_FRAME_PetCardList = NULL;
	m_pID_TEXT_PetTitle = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_COMBOBOX_Distribute = NULL;
	m_pID_EDIT_Content = NULL;
	m_pID_BUTTON_Lookup = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_CHECKBOX_Full = NULL;
	m_pID_CHECKBOX_Ren = NULL;
	m_pID_CHECKBOX_Shen = NULL;
	m_pID_CHECKBOX_Xian = NULL;
	m_pID_CHECKBOX_Ji = NULL;
	m_pID_CHECKBOX_Mo = NULL;
	m_pID_CHECKBOX_Gui = NULL;
	m_pID_CHECKBOX_Yao = NULL;
	m_pID_CHECKBOX_Shou = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Info = NULL;
	CurrentSelectPhyle= 0;
	CurrentPetNum = 0;
	m_pID_LIST_CardAmount = NULL;
	m_pID_PICTURE_ZhongZu = NULL;
	m_pID_PICTURE_Ren = NULL;
	m_pID_PICTURE_Shen = NULL;
	m_pID_PICTURE_Ji = NULL;
	m_pID_PICTURE_Xian = NULL;
	m_pID_PICTURE_Mo = NULL;
	m_pID_PICTURE_Gui = NULL;
	m_pID_PICTURE_Yao = NULL;
	m_pID_PICTURE_Shou = NULL;
	m_pID_PICTURE_Full = NULL;
// 	MsgReqIdentifyData msg;
// 	GettheNetworkInput().SendMsg(&msg);
}
// Frame
bool CUI_ID_FRAME_SuAnimalCardList::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if (m_pID_FRAME_PetCardList == NULL ) return false;
	int nSroollBarHeight = 0;
	if (m_pID_FRAME_PetCardList->IsVisable())
	{
		m_nLastHeight  = m_pID_LIST_PetName->GetShowStartHeight();
		if (m_pID_LIST_PetName->GetScrollBar())
		{
			nSroollBarHeight = m_pID_LIST_PetName->GetScrollBar()->GetValue();
		}		
		m_pID_LIST_PetName->SetShowStartHeight(m_nLastHeight);
		m_pID_LIST_PetName->SetScrollValue(nSroollBarHeight);
		m_pID_LIST_CardAmount->SetShowStartHeight(m_nLastHeight);
		m_pID_LIST_CardAmount->SetScrollValue(nSroollBarHeight);
	}
	return true;
}
bool CUI_ID_FRAME_SuAnimalCardList::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	return true;
}
// ComboBox
void CUI_ID_FRAME_SuAnimalCardList::ID_COMBOBOX_DistributeOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_PetCardList )	return;
	m_nCurPage = 0;
}
// Edit
void CUI_ID_FRAME_SuAnimalCardList::ID_EDIT_ContentOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
}
// Button
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_LookupOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	std::string words = m_pID_EDIT_Content->GetText();
	if ( !words.empty() )
	{
		m_vecPetAllInfo.clear();
		m_vecPetResult.clear();

		PetInfoMap::iterator itor;
		itor = m_petInfoMap.begin();
		std::map<int ,ItemDefine::SPetMonster*> temp;  //key:怪物类型，value:怪物数据
		std::map<int ,ItemDefine::SPetMonster*>::iterator temp_itor;
		temp.clear();
		while (itor != m_petInfoMap.end())
		{
			for (int i = 0; i< itor->second.size(); i++)
			{
				temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
			}
			++itor;
		}
		temp_itor = temp.begin();
		while(temp_itor != temp.end())
		{
			m_vecPetAllInfo.push_back(temp_itor->second);
			++temp_itor;
		}
		for (int i = 0; i<m_vecPetAllInfo.size(); i++ )
		{
			std::string m_petName = m_vecPetAllInfo[i]->GetName();
			size_t idx = m_petName.find(words.c_str());
			if (idx != std::string::npos)
			{
				m_vecPetResult.push_back(m_vecPetAllInfo[i]);
			}
		}
		m_pID_LIST_PetName->Clear();
		m_pID_LIST_CardAmount->Clear();
		int m_size =m_vecPetResult.size();
		int nPrePage = m_pID_LIST_PetName->GetItemShowCount();
		int nStartCount = m_size;// - (m_nCurPage)*nPrePage;
		int nEnd = 0;
		if (nStartCount > nPrePage)
		{
			nEnd = nStartCount - nPrePage;
		}
		else
		{
			nEnd = 0;
		}
		ControlList::S_List sData;
		for (int n = nStartCount-1;n>=nEnd;--n)
		{
			if (n <0)  continue;
			int m_cardNum = 0;
			DWORD m_color= Color_Config.getColor(CC_PetColor_Taupe);
			if (m_identifyData.GetPetIdentify(m_vecPetResult[n]->petType) != NULL)
			{
				m_color = Color_Config.getColor(CC_PetColor_White); 
				m_cardNum = m_identifyData.GetPetIdentify(m_vecPetResult[n]->petType)->identifyTotal;
			}
			sData.clear();
			const char* PetName = m_vecPetResult[n]->GetName();
			sData.SetData(PetName, m_vecPetResult[n]->stMonsterId,0,m_color);
			sData.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
			m_pID_LIST_PetName->AddItem(&sData);
			sData.clear();
			char temp[8];
			MeSprintf_s(temp,sizeof(temp),"%d",m_cardNum);
			sData.SetData(temp, m_vecPetResult[n]->stMonsterId,0,m_color);
			sData.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
			m_pID_LIST_CardAmount->AddItem(&sData);
		}
	}
	else
	{
		RefreshPetList(0);
	}
	return true;
}
void OnSearchPetTextChanged( ControlObject* pSender, const char *szData )
{
	s_CUI_ID_FRAME_SuAnimalCardList.ID_BUTTON_LookupOnButtonClick(pSender);
}
// List
void CUI_ID_FRAME_SuAnimalCardList::ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	int n_index = m_pID_LIST_PetName->GetCurSelIndex();
	ControlList::S_List  *m_data = m_pID_LIST_PetName->GetListItem(n_index);
	if (m_data != NULL)
	{
		int petID = m_data->m_nID;
		ItemDefine::SPetMonster*  m_pet = GettheItemDetail().GetPetById(petID);
		//没有图鉴也让查看 
		/*if (m_pet != NULL && m_identifyData.GetPetIdentify(m_pet->petType) == NULL)
		{
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_HaveNonePetCard));
			return;
		}*/
		s_CUI_ID_FRAME_SuAnimalCard.SetVisable(true);
		RECT m_rect;
		m_pID_FRAME_PetCardList->GetRealRect(&m_rect);
		if (s_CUI_ID_FRAME_SuAnimalCard.GetFrame())
		{
			s_CUI_ID_FRAME_SuAnimalCard.GetFrame()->SetPos(m_rect.left,m_rect.top);
		}		
		if (s_CUI_ID_FRAME_SuAnimalCard.IsVisable())
		{
			PetInfoMap::iterator itor;
			itor = m_petInfoMap.begin();
			std::map<int ,ItemDefine::SPetMonster*> temp;  //key:怪物类型，value:怪物数据
			std::map<int ,ItemDefine::SPetMonster*>::iterator temp_itor;
			temp.clear();
			while (itor != m_petInfoMap.end())
			{
				for (int i = 0; i< itor->second.size(); i++)
				{
					if (itor->second[i]->phyle == m_pet->phyle)
					{
						temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
					}
				}
				++itor;
			}
			temp_itor = temp.begin();
			std::vector<ItemDefine::SPetMonster*> m_petinfo;
			m_petinfo.clear();
			while (temp_itor != temp.end())
			{
				m_petinfo.push_back(temp_itor->second);
				++temp_itor;
			}
			s_CUI_ID_FRAME_SuAnimalCard.SetCurrentPhyle(m_petinfo);
			s_CUI_ID_FRAME_SuAnimalCard.RefreshPage(m_pet,CurrentSelectPhyle);
		}
		s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(false);
	}	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_FullOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList();
	RefreshCheckBoxStatus(EPhyle_MaxCount);
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_RenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Human);
	RefreshCheckBoxStatus(EPhyle_Human);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_ShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Deity);
	RefreshCheckBoxStatus(EPhyle_Deity);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_XianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Immortal);
	RefreshCheckBoxStatus(EPhyle_Immortal);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Machine);
	RefreshCheckBoxStatus(EPhyle_Machine);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Demon);
	RefreshCheckBoxStatus(EPhyle_Demon);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_GuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Ghost);
	RefreshCheckBoxStatus(EPhyle_Ghost);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_YaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Bogey);
	RefreshCheckBoxStatus(EPhyle_Bogey);
	
}
// CheckBox
void CUI_ID_FRAME_SuAnimalCardList::ID_CHECKBOX_ShouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PetCardList )
		return;
	m_nCurPage = 0;
	RefreshPetList(EPhyle_Beast);
	RefreshCheckBoxStatus(EPhyle_Beast);
}

// Button
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	if (m_nCurPage > 0)
	{
		--m_nCurPage;
		RefreshPetList(CurrentSelectPhyle);
		RefreshPage(CurrentSelectPhyle);
	}
	return true;
}
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_PageUpFristOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	m_nCurPage = 0;
	RefreshPetList(CurrentSelectPhyle);
	RefreshPage(CurrentSelectPhyle);
	return true;
}
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_PageDownLastOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )   
		return false;
	SetCurrentPetNum(CurrentSelectPhyle);
	int ncount =CurrentPetNum;
	int nNum  = m_pID_LIST_PetName->GetItemShowCount();//每页的数量
	m_nCurPage = (ncount%nNum == 0)?(ncount/nNum -1):(ncount/nNum);
	RefreshPetList(CurrentSelectPhyle);
	RefreshPage(CurrentSelectPhyle);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalCardList::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetCardList )    return false;
	SetCurrentPetNum(CurrentSelectPhyle);
	int ncount =CurrentPetNum;
	int nNum  = m_pID_LIST_PetName->GetItemShowCount();//每页的数量
	if (ncount -(m_nCurPage+1)*nNum > 0)
	{
		++m_nCurPage;
		RefreshPetList(CurrentSelectPhyle);
		RefreshPage(CurrentSelectPhyle);
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalCardList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalCardList.MEUI", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalCardList.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalCardList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetCardList, s_CUI_ID_FRAME_SuAnimalCardListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetCardList, s_CUI_ID_FRAME_SuAnimalCardListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_HELP, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_PetCardList, ID_COMBOBOX_Distribute, s_CUI_ID_FRAME_SuAnimalCardListID_COMBOBOX_DistributeOnComboBoxChange );
	theUiManager.OnEditEnter( ID_FRAME_PetCardList, ID_EDIT_Content, s_CUI_ID_FRAME_SuAnimalCardListID_EDIT_ContentOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_Lookup, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_LookupOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_PetCardList, ID_LIST_PetName, s_CUI_ID_FRAME_SuAnimalCardListID_LIST_PetNameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_PageUp, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_PageDown, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Full, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_FullOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Ren, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_RenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Shen, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_ShenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Xian, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_XianOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Ji, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_JiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Mo, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_MoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Gui, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_GuiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Yao, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_YaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PetCardList, ID_CHECKBOX_Shou, s_CUI_ID_FRAME_SuAnimalCardListID_CHECKBOX_ShouOnCheckBoxCheck );

	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_PageUpFrist, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_PageUpFristOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetCardList, ID_BUTTON_PageDownLast, s_CUI_ID_FRAME_SuAnimalCardListID_BUTTON_PageDownLastOnButtonClick );

	m_pID_FRAME_PetCardList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetCardList );
	m_pID_TEXT_PetTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_TEXT_PetTitle );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_CLOSE );
	m_pID_COMBOBOX_Distribute = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_COMBOBOX_Distribute );
	m_pID_EDIT_Content = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_EDIT_Content );
	m_pID_BUTTON_Lookup = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_Lookup );
	m_pID_LIST_PetName = (ControlList*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_LIST_PetName );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_PageDown );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_TEXT_Page );
	m_pID_CHECKBOX_Full = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Full );
	m_pID_CHECKBOX_Ren = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Ren );
	m_pID_CHECKBOX_Shen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Shen );
	m_pID_CHECKBOX_Xian = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Xian );
	m_pID_CHECKBOX_Ji = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Ji );
	m_pID_CHECKBOX_Mo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Mo );
	m_pID_CHECKBOX_Gui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Gui );
	m_pID_CHECKBOX_Yao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Yao );
	m_pID_CHECKBOX_Shou = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_CHECKBOX_Shou );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_TEXT_Name );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_TEXT_Info );
	m_pID_LIST_CardAmount= (ControlList *)theUiManager.FindControl(ID_FRAME_PetCardList,ID_LIST_CardAmount);
	m_pID_PICTURE_ZhongZu = (ControlPicture*)theUiManager.FindControl(ID_FRAME_PetCardList,ID_PICTURE_ZhongZu);
	m_pID_PICTURE_Ren = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Ren );
	m_pID_PICTURE_Shen = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Shen );
	m_pID_PICTURE_Ji = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Ji );
	m_pID_PICTURE_Xian = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Xian );
	m_pID_PICTURE_Mo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Mo );
	m_pID_PICTURE_Gui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Gui );
	m_pID_PICTURE_Yao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Yao );
	m_pID_PICTURE_Shou = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Shou );
	m_pID_PICTURE_Full = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_PICTURE_Full );

	m_pID_BUTTON_PageUpFrist = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_PageUpFrist );
	m_pID_BUTTON_PageDownLast = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetCardList, ID_BUTTON_PageDownLast );

	assert( m_pID_FRAME_PetCardList );
	assert( m_pID_TEXT_PetTitle );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_COMBOBOX_Distribute );
	assert( m_pID_EDIT_Content );
	assert( m_pID_BUTTON_Lookup );
	assert( m_pID_LIST_PetName );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_TEXT_Page );
	assert( m_pID_CHECKBOX_Full );
	assert( m_pID_CHECKBOX_Ren );
	assert( m_pID_CHECKBOX_Shen );
	assert( m_pID_CHECKBOX_Xian );
	assert( m_pID_CHECKBOX_Ji );
	assert( m_pID_CHECKBOX_Mo );
	assert( m_pID_CHECKBOX_Gui );
	assert( m_pID_CHECKBOX_Yao );
	assert( m_pID_CHECKBOX_Shou );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Info );
	assert(m_pID_LIST_CardAmount);
	assert(m_pID_PICTURE_ZhongZu);
	assert( m_pID_PICTURE_Ren );
	assert( m_pID_PICTURE_Shen );
	assert( m_pID_PICTURE_Ji );
	assert( m_pID_PICTURE_Xian );
	assert( m_pID_PICTURE_Mo );
	assert( m_pID_PICTURE_Gui );
	assert( m_pID_PICTURE_Yao );
	assert( m_pID_PICTURE_Shou );
	assert( m_pID_PICTURE_Full );
	assert( m_pID_BUTTON_PageUpFrist );
	assert( m_pID_BUTTON_PageDownLast );
	m_pID_BUTTON_Lookup->SetVisable(false);	//采用实时搜索，所以将按钮隐藏
	m_pID_EDIT_Content->SetTextChangedFun( OnSearchPetTextChanged );
	m_pID_LIST_CardAmount->SetItemShowCount(10);
	m_pID_LIST_PetName->SetItemShowCount(10);
	m_pID_PICTURE_Ren->SetVisable(false);
	m_pID_PICTURE_Shen->SetVisable(false);
	m_pID_PICTURE_Ji->SetVisable(false);
	m_pID_PICTURE_Xian->SetVisable(false);
	m_pID_PICTURE_Mo->SetVisable(false);
	m_pID_PICTURE_Gui->SetVisable(false);
	m_pID_PICTURE_Yao->SetVisable(false);
	m_pID_PICTURE_Shou->SetVisable(false);
	m_pID_PICTURE_Full->SetVisable(false);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalCardList::_UnLoadUI()
{
	m_pID_FRAME_PetCardList = NULL;
	m_pID_TEXT_PetTitle = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_COMBOBOX_Distribute = NULL;
	m_pID_EDIT_Content = NULL;
	m_pID_BUTTON_Lookup = NULL;
	m_pID_LIST_PetName = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_nCurPage = 0;
	m_pID_CHECKBOX_Full = NULL;
	m_pID_CHECKBOX_Ren = NULL;
	m_pID_CHECKBOX_Shen = NULL;
	m_pID_CHECKBOX_Xian = NULL;
	m_pID_CHECKBOX_Ji = NULL;
	m_pID_CHECKBOX_Mo = NULL;
	m_pID_CHECKBOX_Gui = NULL;
	m_pID_CHECKBOX_Yao = NULL;
	m_pID_CHECKBOX_Shou = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_LIST_CardAmount = NULL;
	m_pID_PICTURE_ZhongZu = NULL;
	m_pID_PICTURE_Ren = NULL;
	m_pID_PICTURE_Shen = NULL;
	m_pID_PICTURE_Ji = NULL;
	m_pID_PICTURE_Xian = NULL;
	m_pID_PICTURE_Mo = NULL;
	m_pID_PICTURE_Gui = NULL;
	m_pID_PICTURE_Yao = NULL;
	m_pID_PICTURE_Shou = NULL;
	m_pID_PICTURE_Full = NULL;
	m_pID_BUTTON_PageUpFrist = NULL;
	m_pID_BUTTON_PageDownLast = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalCardList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalCardList::_IsVisable()
{
	if ( !m_pID_FRAME_PetCardList )
		return false;
	return m_pID_FRAME_PetCardList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalCardList::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetCardList )
		return ;
	m_pID_FRAME_PetCardList->SetVisable( bVisable );

	if(bVisable)
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	else
		ImmAssociateContext( g_hWnd, NULL );

	
	//CurrentPetNum = 0;
	if (bVisable)
	{
		std::map< int, std::vector< ItemDefine::SPetMonster* > >& m_MonsterInfo =GettheItemDetail().GetPetMonsterList();
		std::map< int, std::vector< ItemDefine::SPetMonster* > >::iterator  m_itor= m_MonsterInfo.begin();
		while (m_itor != m_MonsterInfo.end())
		{
			m_petInfoMap.insert(std::make_pair(m_itor->first,m_itor->second));
			++m_itor;
		}	
		CurrentSelectPhyle = EPhyle_MaxCount;
		RefreshCheckBoxStatus(EPhyle_MaxCount);
		RefreshPetList(CurrentSelectPhyle);
		theUiManager.ToTop(m_pID_FRAME_PetCardList);
	}
	m_IsClicked = false;
}

void CUI_ID_FRAME_SuAnimalCardList::RefreshPage(int phyle)
{
	if(m_pID_FRAME_PetCardList == NULL)  return ;
	SetCurrentPetNum(phyle);
	int nPage =CurrentPetNum;
	int nPerPage = m_pID_LIST_PetName->GetItemShowCount();
	if(nPerPage == 0)
		nPerPage = 1;

	//int nTotalPage = 0;

	nTotalPage = nPage/nPerPage;
	if(nPage%nPerPage != 0)
		++nTotalPage;

	if(nTotalPage == 0)
	{
		nTotalPage = 1;
		m_nCurPage = 0;
	}
		
	char szWord[64];
	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%d/%d",m_nCurPage + 1,nTotalPage);
	m_pID_TEXT_Page->SetText(szWord);
}
bool CUI_ID_FRAME_SuAnimalCardList::sortPetMonster(std::vector<ItemDefine::SPetMonster*>::iterator itor1,std::vector<ItemDefine::SPetMonster*>::iterator itor2)
{
	//return ((m_identifyData.GetPetIdentify(itor1.petType))->identifyTotal) > ((m_identifyData.GetPetIdentify(itor2.petType))->identifyTotal);
	return false;
}
void CUI_ID_FRAME_SuAnimalCardList::RefreshPetList(int petPhyle)
{
	if ( !m_pID_FRAME_PetCardList )
		return ;
	CurrentSelectPhyle= petPhyle;
	RefreshPage(CurrentSelectPhyle);
	SetCurrentPetNum(CurrentSelectPhyle);
	ShowPetPhyleInfo(CurrentSelectPhyle);
	int nPrePage = m_pID_LIST_PetName->GetItemShowCount();
	PetInfoMap::iterator itor;
	itor = m_petInfoMap.begin();
	std::map<int ,ItemDefine::SPetMonster*> temp;  //key:怪物类型，value:怪物数据
	std::map<int ,ItemDefine::SPetMonster*>::iterator temp_itor;
	temp.clear();
	if (petPhyle == EPhyle_MaxCount)
	{
		while (itor != m_petInfoMap.end())
		{
			for (int i = 0; i< itor->second.size(); i++)
			{
				temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
			}
			++itor;
		}
	}
	else
	{
		while (itor != m_petInfoMap.end())
		{
			for (int i = 0; i< itor->second.size(); i++)
			{
				if (itor->second[i]->phyle == petPhyle)
				{
					temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
				}
			}
			++itor;
		}
	}
	
	temp_itor = temp.begin();
	std::vector<ItemDefine::SPetMonster*> m_petinfo;
	m_petinfo.clear();
	m_pID_LIST_PetName->Clear();
	m_pID_LIST_CardAmount->Clear();
	while (temp_itor != temp.end())
	{
		m_petinfo.push_back(temp_itor->second);
		++temp_itor;
	}
	//std::sort(m_petinfo.begin(),m_petinfo.end,sortPetMonster);
	int m_size =m_petinfo.size();
	int nStartCount = m_size - (m_nCurPage)*nPrePage;
	int nEnd = 0;
	if (nStartCount > nPrePage)
	{
		nEnd = nStartCount - nPrePage;
	}
	else
	{
		nEnd = 0;
	}
	ControlList::S_List sData;
	for (int n = nStartCount-1;n>=nEnd;--n)
	{
		if (n <0)  return ;
		const char* PetName = m_petinfo[n]->GetName();
		int m_cardNum=0;
		int m_AllNum=0;
		m_AllNum = m_petinfo[n]->identifyTotal;

		DWORD m_color= Color_Config.getColor(CC_PetColor_Taupe);
		if (m_identifyData.GetPetIdentify(m_petinfo[n]->petType) != NULL)
		{
			m_color = Color_Config.getColor(CC_PetColor_White); 
			m_cardNum = m_identifyData.GetPetIdentify(m_petinfo[n]->petType)->identifyTotal;
		}
		sData.clear();
		sData.SetData(PetName, m_petinfo[n]->stMonsterId,0,m_color);
		sData.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
		m_pID_LIST_PetName->AddItem(&sData);

		sData.clear();
		char temp[8];
		MeSprintf_s(temp,sizeof(temp),"%d/%d",m_cardNum,m_AllNum);
		sData.SetData(temp,m_petinfo[n]->stMonsterId,0,m_color);
		sData.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
		m_pID_LIST_CardAmount->AddItem(&sData);
	}

	return ;
}

void CUI_ID_FRAME_SuAnimalCardList::SetCurrentPetNum(int phyle)
{
	PetInfoMap::iterator itor;
	itor = m_petInfoMap.begin();
	std::map<int ,ItemDefine::SPetMonster*> temp;  //key:怪物类型，value:怪物数据
	std::map<int ,ItemDefine::SPetMonster*>::iterator temp_itor;
	temp.clear();
	if (phyle == EPhyle_MaxCount)
	{
		while (itor != m_petInfoMap.end())
		{
			for (int i = 0; i< itor->second.size(); i++)
			{
				temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
			}
			++itor;
		}
	}
	else
	{
		while (itor != m_petInfoMap.end())
		{
			for (int i = 0; i< itor->second.size(); i++)
			{
				if (itor->second[i]->phyle == phyle)
				{
					temp.insert(std::make_pair(itor->second[i]->petType,itor->second[i]));
				}
			}
			++itor;
		}
	}
	
	temp_itor = temp.begin();
	std::vector<ItemDefine::SPetMonster*> m_petinfo;
	m_petinfo.clear();
	while (temp_itor != temp.end())
	{
		m_petinfo.push_back(temp_itor->second);
		++temp_itor;
	}
	CurrentPetNum=m_petinfo.size();
}

void CUI_ID_FRAME_SuAnimalCardList::ShowPetPhyleInfo(int phyle)
{
	m_pID_TEXT_Name->SetText(GetPhyleInfo(phyle));	
}

const char*  CUI_ID_FRAME_SuAnimalCardList::GetPhyleInfo(int phyle)
{
	switch (phyle)
	{
	case EPhyle_Human:
		return theXmlString.GetString(eText_PhyleHuman);
	case EPhyle_Machine:
		return theXmlString.GetString(eText_PhyleMachine);
	case EPhyle_Beast:
		return theXmlString.GetString(eText_PhyleBeast);
	case EPhyle_Immortal:
		return theXmlString.GetString(eText_PhyleImmortal);
	case EPhyle_Ghost:
		return  theXmlString.GetString(eText_PhyleGhost);
	case EPhyle_Bogey:
		return theXmlString.GetString(eText_PhyleBogey);
	case EPhyle_Deity:
		return theXmlString.GetString(eText_PhyleDeity);
	case EPhyle_Demon:
		return theXmlString.GetString(eText_PhyleDemon);
	default :
		return theXmlString.GetString(eText_PhyleAll);
	}
	return NULL;
}

void CUI_ID_FRAME_SuAnimalCardList::RefreshCheckBoxStatus(int m_currentPhyle)
{
	m_pID_CHECKBOX_Full->SetCheck(false);
	m_pID_CHECKBOX_Ren->SetCheck(false);
	m_pID_CHECKBOX_Shen->SetCheck(false);
	m_pID_CHECKBOX_Xian->SetCheck(false);
	m_pID_CHECKBOX_Ji->SetCheck(false);
	m_pID_CHECKBOX_Mo->SetCheck(false);
	m_pID_CHECKBOX_Gui->SetCheck(false);
	m_pID_CHECKBOX_Yao->SetCheck(false);
	m_pID_CHECKBOX_Shou->SetCheck(false);
	switch(m_currentPhyle)
	{
	case EPhyle_Human:
			m_pID_CHECKBOX_Ren->SetCheck(true);
		break;
	case EPhyle_Machine:
		m_pID_CHECKBOX_Ji->SetCheck(true);
		break;
	case EPhyle_Beast:
		m_pID_CHECKBOX_Shou->SetCheck(true);
		break;
	case EPhyle_Immortal:
		m_pID_CHECKBOX_Xian->SetCheck(true);
		break;
	case EPhyle_Ghost:
		m_pID_CHECKBOX_Gui->SetCheck(true);
		break;
	case EPhyle_Bogey:
		m_pID_CHECKBOX_Yao->SetCheck(true);
		break;
	case EPhyle_Deity:
		m_pID_CHECKBOX_Shen->SetCheck(true);
		break;
	case EPhyle_Demon:
		m_pID_CHECKBOX_Mo->SetCheck(true);
		break;
	case EPhyle_MaxCount:
		m_pID_CHECKBOX_Full->SetCheck(true);
		break;
	}
	SetPhylePic(m_currentPhyle);
}

bool CUI_ID_FRAME_SuAnimalCardList::EditInputIsVisable()
{
	if(m_pID_FRAME_PetCardList == NULL)  return false;
	if(m_pID_EDIT_Content )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_Content);
	}
	return FALSE;
}
//更新所有数据，只在初始化时调用
void CUI_ID_FRAME_SuAnimalCardList::UpdateAllIdentify(Msg *msg)
{
	MsgAllIdentifyData  *m_data = static_cast<MsgAllIdentifyData*>(msg);
	if (m_data != NULL)
	{
		m_identifyData = m_data->identifyData;
	}
	
}
//更新特定数据，数据改变时调用
void CUI_ID_FRAME_SuAnimalCardList::UpdateIdentify(Msg *msg)
{
	MsgUpdatePetIdentify *m_data = static_cast<MsgUpdatePetIdentify*>(msg);
	if (m_data != NULL)
	{
		if (m_identifyData.AddPetIdentify(m_data->petIdentify))
		{
			char szInfo[256];
			MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_REGEDIT_PET),theItemDetailConfig.GetPetTypeName(m_data->petIdentify.petType));
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo);
		}
	}
}

void CUI_ID_FRAME_SuAnimalCardList::SetPhylePic(int petPhyle)
{
	if(m_pID_FRAME_PetCardList == NULL)  return ;
	char temp[256];
	MeSprintf_s(temp,sizeof(temp),"%s/Data/ui/PetPicture/PetPhyle%d.dds",GetRootPath(),petPhyle);
	f_Handle *fp = packet_namespace::w_fopen(temp,"r");
	if (fp == NULL)
	{
		MeSprintf_s(temp,sizeof(temp),"ui\\PetPicture\\PetPhyle9.dds");
	}
	
	m_pID_PICTURE_ZhongZu->SetPicName(temp);

	m_pID_PICTURE_Ren->SetVisable(false);
	m_pID_PICTURE_Shen->SetVisable(false);
	m_pID_PICTURE_Ji->SetVisable(false);
	m_pID_PICTURE_Xian->SetVisable(false);
	m_pID_PICTURE_Mo->SetVisable(false);
	m_pID_PICTURE_Gui->SetVisable(false);
	m_pID_PICTURE_Yao->SetVisable(false);
	m_pID_PICTURE_Shou->SetVisable(false);
	m_pID_PICTURE_Full->SetVisable(false);
	switch(petPhyle)
	{
	case EPhyle_Human:
		m_pID_PICTURE_Ren->SetVisable(true);
		break;
	case EPhyle_Machine:
		m_pID_PICTURE_Ji->SetVisable(true);
		break;
	case EPhyle_Beast:
		m_pID_PICTURE_Shou->SetVisable(true);
		break;
	case EPhyle_Immortal:
		m_pID_PICTURE_Xian->SetVisable(true);
		break;
	case EPhyle_Ghost:
		m_pID_PICTURE_Gui->SetVisable(true);
		break;
	case EPhyle_Bogey:
		m_pID_PICTURE_Yao->SetVisable(true);
		break;
	case EPhyle_Deity:
		m_pID_PICTURE_Shen->SetVisable(true);
		break;
	case EPhyle_Demon:
		m_pID_PICTURE_Mo->SetVisable(true);
		break;
	case EPhyle_MaxCount:
		m_pID_PICTURE_Full->SetVisable(true);
		break;

	}
}