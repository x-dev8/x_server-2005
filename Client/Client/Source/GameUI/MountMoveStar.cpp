/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\MountMoveStar.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MountMoveStar.h"
#include "GlobalDef.h"
#include "PlayerRole.h"
#include "MountMoveStarConfig.h"
#include "PackItemEnableManager.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "NetworkInput.h"
#include "pet.h"
#include "Pack.h"
#include "MountStrengthenConfig.h"
#include "UIMgr.h"
#include "MountStrengthen.h"
CUI_ID_FRAME_MountMoveStar s_CUI_ID_FRAME_MountMoveStar;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MountMoveStar, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MountMoveStar, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_OldMountOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_OldMountOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_OldMountOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_OldMountOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_NewMountOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_NewMountOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_NewMountOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_NewMountOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_MountItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_MountItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_MountItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_LISTIMG_MountItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_BUTTON_CanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MountMoveStar, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_MountMoveStar::CUI_ID_FRAME_MountMoveStar()
{
	// Member
	m_pID_FRAME_MountMoveStar = NULL;
	m_pID_LISTIMG_OldMount = NULL;
	m_pID_LISTIMG_NewMount = NULL;
	m_pID_LISTIMG_MountItem = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Canel = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Info = NULL;
	m_OldMountID = 0;
	m_NewMountID = 0;
}
// Frame
bool CUI_ID_FRAME_MountMoveStar::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_MountMoveStar::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_OldMountOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_OldMountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_OldMountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_OldMountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	SetMountData(NULL,true);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_NewMountOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_NewMountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_NewMountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_NewMountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	SetMountData(NULL,false);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_MountItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_MountItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_MountItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_MountMoveStar::ID_LISTIMG_MountItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_MountMoveStar::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!IsCanMoveStar(true))
		return true;
	//�����������������ȥ
	MsgMountMoveStar msg;
	msg.OldMountID = m_OldMountID;
	msg.NewMountID = m_NewMountID;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_MountMoveStar::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_MountMoveStar::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// װ��UI
bool CUI_ID_FRAME_MountMoveStar::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MountMoveStar.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\MountMoveStar.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_MountMoveStar::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MountMoveStar, s_CUI_ID_FRAME_MountMoveStarOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MountMoveStar, s_CUI_ID_FRAME_MountMoveStarOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_MountMoveStar, ID_LISTIMG_OldMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_OldMountOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountMoveStar, ID_LISTIMG_OldMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_OldMountOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountMoveStar, ID_LISTIMG_OldMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_OldMountOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountMoveStar, ID_LISTIMG_OldMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_OldMountOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MountMoveStar, ID_LISTIMG_NewMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_NewMountOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountMoveStar, ID_LISTIMG_NewMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_NewMountOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountMoveStar, ID_LISTIMG_NewMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_NewMountOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountMoveStar, ID_LISTIMG_NewMount, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_NewMountOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MountMoveStar, ID_LISTIMG_MountItem, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_MountItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MountMoveStar, ID_LISTIMG_MountItem, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_MountItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MountMoveStar, ID_LISTIMG_MountItem, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_MountItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MountMoveStar, ID_LISTIMG_MountItem, s_CUI_ID_FRAME_MountMoveStarID_LISTIMG_MountItemOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_MountMoveStar, ID_BUTTON_OK, s_CUI_ID_FRAME_MountMoveStarID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MountMoveStar, ID_BUTTON_Canel, s_CUI_ID_FRAME_MountMoveStarID_BUTTON_CanelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MountMoveStar, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MountMoveStarID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_MountMoveStar = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MountMoveStar );
	m_pID_LISTIMG_OldMount = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_LISTIMG_OldMount );
	m_pID_LISTIMG_NewMount = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_LISTIMG_NewMount );
	m_pID_LISTIMG_MountItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_LISTIMG_MountItem );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_BUTTON_OK );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_BUTTON_Canel );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_BUTTON_CLOSE );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_TEXT_Money );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_TEXT_Info );

	m_pID_TEXT_OldLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_TEXT_OldLevel );
	m_pID_TEXT_NewLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_MountMoveStar, ID_TEXT_NewLevel );
	assert( m_pID_FRAME_MountMoveStar );
	assert( m_pID_LISTIMG_OldMount );
	assert( m_pID_LISTIMG_NewMount );
	assert( m_pID_LISTIMG_MountItem );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_Info );
	assert( m_pID_TEXT_OldLevel );
	assert( m_pID_TEXT_NewLevel );
	return true;
}
// ж��UI
bool CUI_ID_FRAME_MountMoveStar::_UnLoadUI()
{
	m_pID_FRAME_MountMoveStar = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\MountMoveStar.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_MountMoveStar::_IsVisable()
{
	if(!m_pID_FRAME_MountMoveStar)
		return false;
	return m_pID_FRAME_MountMoveStar->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_MountMoveStar::_SetVisable( const bool bVisable )
{
	Clear();
	if (bVisable)
	{
		if (!s_CUI_ID_FRAME_PACK.IsVisable())
			s_CUI_ID_FRAME_PACK.SetVisable(true);
		if (!s_CUI_ID_FRAME_Pet.IsVisable())
			s_CUI_ID_FRAME_Pet.SetVisable(true);
		ResetWindowPositionEx(s_CUI_ID_FRAME_PACK.GetFrame(), m_pID_FRAME_MountMoveStar, s_CUI_ID_FRAME_Pet.GetFrame());
	}
	m_pID_FRAME_MountMoveStar->SetVisable( bVisable );
	m_pID_FRAME_MountMoveStar->SetCovered(false);
	if(!bVisable)
	{
		if(s_CUI_ID_FRAME_MountStrengthen.IsVisable())
			s_CUI_ID_FRAME_MountStrengthen.SetVisable(false);//����ǿ��Ҳһ��ر� ������ݲ�ͬ��
	}
}
void CUI_ID_FRAME_MountMoveStar::Clear()
{
	//���UI����ϵ�����
	SetMountData(0,false);
	SetMountData(0,true);
	m_OldMountID = 0;
	m_NewMountID = 0;
	m_pID_LISTIMG_OldMount->Clear();
	m_pID_LISTIMG_NewMount->Clear();
	m_pID_LISTIMG_MountItem->Clear();
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_Info->SetText("");
	m_pID_TEXT_OldLevel->SetText("");
	m_pID_TEXT_NewLevel->SetText("");
	m_pID_BUTTON_OK->SetEnable(false);
}
bool CUI_ID_FRAME_MountMoveStar::IsPackItemBeUsing( __int64 nGuid )
{
	if(!IsVisable())
        return false;
	//�ж�ָ����Ʒ�Ƿ�ʹ�õ�
	if(m_OldMountID == 0)
		return false;
	SMountItem* pMountItem = thePlayerRole.GetMountByGUID(m_OldMountID);
	if(!pMountItem)
		return false;
	MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pMountItem->baseInfo.level);
	if(!pConfig)
		return false;
	SCharItem  pItems;
	CItemBag2* pBag = NULL;
	thePlayerRole.GetBagByItemGUID(nGuid,pBag);
	if(!pBag)
		return false;
	pBag->GetItemByOnlyeID(nGuid,&pItems);
	if(!pConfig->ItemMap.empty())
	{
		std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
		for(;Iter != pConfig->ItemMap.end();++Iter)
		{
			unsigned int ItemID = Iter->first;
			if(pItems.itembaseinfo.ustItemID == ItemID)
				return true;
		}
		return false;
	}
	else
		return false;
}
bool CUI_ID_FRAME_MountMoveStar::IsCanMoveStar(bool IsShowCenterInfo)
{
	//��ǰUI�ϵ�״̬�Ƿ���Խ������ǲ���
	if(!m_pID_FRAME_MountMoveStar)
		return false;
	if(m_OldMountID == 0)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_OleMountNull));
		return false;
	}
	if(m_NewMountID == 0)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_NewMountNull));
		return false;
	}
	if(m_NewMountID == m_OldMountID)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_OneMount));
		return false;
	}
	SMountItem* pMountItem = thePlayerRole.GetMountByGUID( m_NewMountID);
	if(!pMountItem)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_NewMountNull));
		return false;
	}
	unsigned int NewLevel = pMountItem->baseInfo.level;
	bool NewIsCanUp = (theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id))?true:false;
	if(pMountItem == thePlayerRole.GetActivedMount())
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_NewMountActionError));
		return false;
	}
	pMountItem = thePlayerRole.GetMountByGUID(m_OldMountID );
	if(!pMountItem)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_OleMountNull));
		return false;
	}
	if(!NewIsCanUp)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_NewMountError));
		return false;
	}
	unsigned int OldLevel = pMountItem->baseInfo.level;
	bool OldIsCanUp = (theMountStrengthenConfig.GetMountStrengthenData(pMountItem->baseInfo.id))?true:false;
	if(pMountItem == thePlayerRole.GetActivedMount())
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_OldMountActionError));
		return false;
	}
	if(OldLevel <= NewLevel)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_Level));
		return false;
	}
	if(!OldIsCanUp)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_OldMountError));
		return false;
	}
	//������֤��Ϻ� �����ж��Ƿ��в��� �� �н�Ǯ�����������ǲ���
	MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pMountItem->baseInfo.level);
	if(!pConfig)
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_MountStarLevel));
		return false;
	}
	//������� �����жϽ�Ǯ������
	if(!thePlayerRole.HaveEnoughMoney(pConfig->Money))
	{
		if(IsShowCenterInfo)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_MoneyError));
		return false;
	}
	//�ж� Ŀ�� �� Դ�����Ƿ����ǿ��


	//�����Ƿ��㹻
	if(!pConfig->ItemMap.empty())
	{
		std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
		for(;Iter != pConfig->ItemMap.end();++Iter)
		{
			unsigned int ItemID = Iter->first;
			unsigned int ItemSum = Iter->second;
			CItemBag2* pbag = thePlayerRole.GetBagByItemID(ItemID);
			if(!pbag)
			{
				if(IsShowCenterInfo)
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_ItemError));
				return false;
			}
			if(pbag->GetItemCount(ItemID) < ItemSum)
			{
				if(IsShowCenterInfo)
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_ItemError));
				return false;
			}
		}
		return true;
	}
	else
		return true;
}
void CUI_ID_FRAME_MountMoveStar::EnableBagItem(CItemBag2* pBag,unsigned int ItemID)
{
	//����ָ����Ʒ��ʹ��
	if(!pBag)
		return;
	int BagSize = pBag->GetNowBagSize();
	for(int i =0;i<BagSize;++i)
	{
		SCharItem * pItem = pBag->GetCharItemFromIdx(i);
		if(!pItem || pItem->itembaseinfo.ustItemID !=ItemID || ItemID == 0) continue;
		CPackItemEnableManager::Instance()->RefreshBagItemEnable(pBag,i,true);
	}
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
}
void CUI_ID_FRAME_MountMoveStar::SetMountData(ControlIconDrag::S_ListImg* pItemDrag,bool IsOldMount)
{
	//Դ���� ���õ�UI�������ȥ ������Ҫ����UI�Ĳ��� ��ʾ �����ĵĽ�Ǯ �Ѿ��ɹ��ļ���
	if(!m_pID_FRAME_MountMoveStar)
		return;
	__int64 MountOnlyID =0;
	if(!pItemDrag)
		MountOnlyID = 0;
	else
	{
		int nIndex = s_CUI_ID_FRAME_Pet.PenIcon_GetIndexByItem( pItemDrag );
		if ( nIndex == -1 )
			return;
		SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( nIndex );
		if(!pMountItem)
			return;
		MountOnlyID = pMountItem->baseInfo.guid;
	}
	if(IsOldMount)
	{
		if(MountOnlyID == 0)
		{
			//��ղ������������
			m_pID_LISTIMG_OldMount->Clear();
			//�ñ����Ĳ���ȫ��������
			__int64 OldID = m_OldMountID;
			m_OldMountID = 0;
			if(OldID !=0)
			{
				SMountItem* pMountItem = thePlayerRole.GetMountByGUID( OldID );
				if(pMountItem)
				{
					MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pMountItem->baseInfo.level);
					if(pConfig)
					{
						//ϲ���������� �Ͳ�������
						if(!pConfig->ItemMap.empty())
						{
							std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
							for(;Iter != pConfig->ItemMap.end();++Iter)
							{
								//������Ʒ��ID ��ȡ����
								EnableBagItem(thePlayerRole.GetBagByItemID(Iter->first),Iter->first);
								//CPackItemEnableManager::Instance()->RefreshBagItemEnable(thePlayerRole.GetBagByItemID(Iter->first),ItemID,true);
							}
							//theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
						}
					}
				}	
			}
			m_pID_LISTIMG_MountItem->Clear();
			m_pID_TEXT_Money->SetText("");
			m_pID_TEXT_OldLevel->SetText("");
			m_pID_BUTTON_OK->SetEnable(false);
		}
		else
		{
			//���ò������������
			//1.����ǰ��ȫ���յ�
			m_pID_LISTIMG_OldMount->Clear();
			m_pID_LISTIMG_MountItem->Clear();
			//�ñ����Ĳ���ȫ��������
			unsigned int OldID = m_OldMountID;
			m_OldMountID = 0;
			if(OldID !=0)
			{
				SMountItem* pMountItem = thePlayerRole.GetMountByGUID( OldID );
				if(pMountItem)
				{
					MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pMountItem->baseInfo.level);
					if(pConfig)
					{
						//ϲ���������� �Ͳ�������
						if(!pConfig->ItemMap.empty())
						{
							std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
							for(;Iter != pConfig->ItemMap.end();++Iter)
							{
								//������Ʒ��ID ��ȡ����
								EnableBagItem(thePlayerRole.GetBagByItemID(Iter->first),Iter->first);
								//CPackItemEnableManager::Instance()->RefreshBagItemEnable(thePlayerRole.GetBagByItemID(Iter->first),Iter->first,true);
							}
							//theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
						}
					}
				}	
			}
			m_pID_TEXT_Money->SetText("");
			m_pID_TEXT_OldLevel->SetText("");
			//2.�������ڵ�����
			SMountItem* pMountItem = thePlayerRole.GetMountByGUID( MountOnlyID );
			if(!pMountItem)
				return;
			m_pID_LISTIMG_OldMount->Clear();
			m_pID_LISTIMG_MountItem->Clear();
			m_pID_LISTIMG_OldMount->SetItem(pItemDrag,0);
			//���ñ�����״̬
			m_OldMountID = MountOnlyID;
			MountMoveStatStruct* pConfig = MountMoveStarConfig::Instance().GetConfigStruct(pMountItem->baseInfo.level);
			if(pConfig)
			{
				//ϲ���������� �Ͳ�������
				if(!pConfig->ItemMap.empty())
				{
					std::map<unsigned int,unsigned int>::iterator Iter = pConfig->ItemMap.begin();
					ControlIconDrag::S_ListImg pItems;
					int Index = 0;
					for(;Iter != pConfig->ItemMap.end();++Iter,++Index)
					{
						//������Ʒ��ID ��ȡ����
						CItemBag2* pbag = thePlayerRole.GetBagByItemID(Iter->first);
						if(!pbag)
							continue;
						eIconDrawState eEnable=(pbag->GetItemCount(Iter->first) < Iter->second)?eIcon_Disable:eIcon_Enable;
						pItems.SetData(Iter->first,Iter->second,eEnable);
						m_pID_LISTIMG_MountItem->SetItem(&pItems,Index);
						EnableBagItem(thePlayerRole.GetBagByItemID(Iter->first),Iter->first);
					}
					//theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
				}
				string strMoney = "";
				thePlayerRole.GetGSCStringFromJiaoZi(pConfig->Money,strMoney);
				m_pID_TEXT_Money->SetText(strMoney.c_str());
			}
			char strLevel[8] = {0};
			sprintf_s(strLevel,8,"%d",pMountItem->baseInfo.level);
			m_pID_TEXT_OldLevel->SetText(strLevel);
			m_pID_BUTTON_OK->SetEnable(IsCanMoveStar(false));
		}
	}
	else
	{
		if(MountOnlyID == 0)
		{
			//���Ŀ�����������
			m_pID_LISTIMG_NewMount->Clear();
			m_pID_TEXT_NewLevel->SetText("");
			m_NewMountID = 0;
			m_pID_BUTTON_OK->SetEnable(false);
		}
		else
		{
			//����Ŀ�����������
			m_pID_LISTIMG_NewMount->Clear();
			m_pID_TEXT_NewLevel->SetText("");
			m_NewMountID = 0;
			SMountItem* pMountItem = thePlayerRole.GetMountByGUID( MountOnlyID );
			if(!pMountItem)
				return;
			m_pID_LISTIMG_NewMount->Clear();
			m_pID_LISTIMG_NewMount->SetItem(pItemDrag,0);
			//���ð�ť��״̬
			m_NewMountID = MountOnlyID;
			m_pID_BUTTON_OK->SetEnable(IsCanMoveStar(false));

			char strLevel[8] = {0};
			sprintf_s(strLevel,8,"%d",pMountItem->baseInfo.level);
			m_pID_TEXT_NewLevel->SetText(strLevel);
			
		}
	}
}
void CUI_ID_FRAME_MountMoveStar::SetMount(ControlIconDrag::S_ListImg* pItemDrag)
{
	//���������õ�UI����ȥ 
	if(m_OldMountID == 0)
	{
		SetMountData(pItemDrag,true);
	}
	else if(m_NewMountID == 0)
	{
		SetMountData(pItemDrag,false);
	}
	else
	{
		//��ʾ������Ϣ
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_MountMoveStar_SetMountError));
	}
}