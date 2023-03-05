/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\邮件\MailReceive2.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MailReceive2.h"
#ifdef _DEBUG
#include "MeUi/FontManager.h"
#include "MeFont\MeFont.h"
#include "Common.h"
#endif
#include "MailReceive.h"
#include "MailMain.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "MeFont/MeFontSystem.h"

#pragma warning(disable:4482)

bool ProcessMessageInMail(const char bPressYesButton, void *pData)
{
    guardfunc;
    if( bPressYesButton )
    {
        s_CUI_ID_FRAME_MailReceive2.DeleteMail();
    }
    return true;
    unguard;
}


CUI_ID_FRAME_MailReceive2 s_CUI_ID_FRAME_MailReceive2;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MailReceive2, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MailReceive2, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_HelpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_LISTIMG_MailMoneyOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_LISTIMG_MailMoneyOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_LISTIMG_MailMoneyOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_LISTIMG_MailMoneyOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_DeleteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_TransOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_ReOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive2, ID_BUTTON_ReturnOnButtonClick )
CUI_ID_FRAME_MailReceive2::CUI_ID_FRAME_MailReceive2()
{
	// Member
	ResetMembers();

    m_mailId = -1;
}

void CUI_ID_FRAME_MailReceive2::ResetMembers()
{
	m_pID_FRAME_MailReceive2 = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_MailContent = NULL;
	m_pID_TEXT_Content = NULL;
	m_pID_LISTIMG_MailMoney = NULL;
	m_pID_TEXT_From = NULL;
	m_pID_TEXT_MailTitle = NULL;
	m_pID_TEXT_MailTitleName = NULL;
	m_pID_TEXT_FromName = NULL;
	m_pID_BUTTON_Delete = NULL;
	m_pID_BUTTON_Trans = NULL;
	m_pID_BUTTON_Re = NULL;
	m_pID_BUTTON_Return = NULL;
	m_pID_TEXT_SendTarget = NULL;
	m_pID_TEXT_SendTargetName = NULL;
	m_pID_TEXT_CopyTarget = NULL;
	m_pID_TEXT_CopyTargetName = NULL;
}

// Frame
bool CUI_ID_FRAME_MailReceive2::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_MailReceive2::OnFrameRender()
{
#ifdef _DEBUG
    char szWord[32];
    MeSprintf_s(szWord,sizeof(szWord) - 1,"%d",m_mailId);
    FontSystem::DrawText(szWord,300,150 + 18 * 3,DT_NOCLIP,0xffff0000,2);
#endif
	return true;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
	s_CUI_ID_FRAME_MailReceive.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MailReceive2::ID_LISTIMG_MailMoneyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    
	return false;
}
bool CUI_ID_FRAME_MailReceive2::ID_LISTIMG_MailMoneyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    ProcessMail(pItem);
	return false;
}
bool CUI_ID_FRAME_MailReceive2::ID_LISTIMG_MailMoneyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    ProcessMail(pItem);
	return false;
}
bool CUI_ID_FRAME_MailReceive2::ID_LISTIMG_MailMoneyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    ProcessMail(pItem);
	return false;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    if(m_bShow)
         s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MailItemNotify)," ",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,ProcessMessageInMail);
    else
        DeleteMail();

	s_CUI_ID_FRAME_MailReceive.SetVisable(true);

	return true;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_TransOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    if(m_mailId == -1)
        return false;
	SetVisable(false);
	s_CUI_ID_FRAME_MailMain.SetVisable(true);
    s_CUI_ID_FRAME_MailMain.TranslateMail(m_mailId);

	return true;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_ReOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;
    if(m_mailId == -1)
        return false;
	SetVisable(false);
	s_CUI_ID_FRAME_MailMain.SetVisable(true);
    s_CUI_ID_FRAME_MailMain.ResponseMail(m_mailId);

	return true;
}
// Button
bool CUI_ID_FRAME_MailReceive2::ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive2)
		return false;

	GetAllItem();
    SetVisable(false);

	s_CUI_ID_FRAME_MailReceive.SetVisable(true);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_MailReceive2::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MailReceive2.MEUI", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MailReceive2.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MailReceive2::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MailReceive2, s_CUI_ID_FRAME_MailReceive2OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MailReceive2, s_CUI_ID_FRAME_MailReceive2OnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_CLOSEOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_Help, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_HelpOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_MailReceive2, ID_LISTIMG_MailMoney, s_CUI_ID_FRAME_MailReceive2ID_LISTIMG_MailMoneyOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_MailReceive2, ID_LISTIMG_MailMoney, s_CUI_ID_FRAME_MailReceive2ID_LISTIMG_MailMoneyOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_MailReceive2, ID_LISTIMG_MailMoney, s_CUI_ID_FRAME_MailReceive2ID_LISTIMG_MailMoneyOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_MailReceive2, ID_LISTIMG_MailMoney, s_CUI_ID_FRAME_MailReceive2ID_LISTIMG_MailMoneyOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_Delete, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_DeleteOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_Trans, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_TransOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_Re, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_ReOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive2, ID_BUTTON_Return, s_CUI_ID_FRAME_MailReceive2ID_BUTTON_ReturnOnButtonClick );

	m_pID_FRAME_MailReceive2 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MailReceive2 );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_PICTURE_Title );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_Help );
	m_pID_PICTURE_MailContent = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_PICTURE_MailContent );
	m_pID_TEXT_Content = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_Content );
	m_pID_LISTIMG_MailMoney = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_LISTIMG_MailMoney );
	m_pID_TEXT_From = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_From );
	m_pID_TEXT_MailTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_MailTitle );
	m_pID_TEXT_MailTitleName = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_MailTitleName );
	m_pID_TEXT_FromName = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_FromName );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_Delete );
	m_pID_BUTTON_Trans = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_Trans );
	m_pID_BUTTON_Re = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_Re );
	m_pID_BUTTON_Return = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_BUTTON_Return );
	m_pID_TEXT_SendTarget = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_SendTarget );
	m_pID_TEXT_SendTargetName = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_SendTargetName );
	m_pID_TEXT_CopyTarget = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_CopyTarget );
	m_pID_TEXT_CopyTargetName = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive2, ID_TEXT_CopyTargetName );
	assert( m_pID_FRAME_MailReceive2 );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Help );
	assert( m_pID_PICTURE_MailContent );
	assert( m_pID_TEXT_Content );
	assert( m_pID_LISTIMG_MailMoney );
	assert( m_pID_TEXT_From );
	assert( m_pID_TEXT_MailTitle );
	assert( m_pID_TEXT_MailTitleName );
	assert( m_pID_TEXT_FromName );
	assert( m_pID_BUTTON_Delete );
	assert( m_pID_BUTTON_Trans );
	assert( m_pID_BUTTON_Re );
	assert( m_pID_BUTTON_Return );
	assert( m_pID_TEXT_SendTarget );
	assert( m_pID_TEXT_SendTargetName );
	assert( m_pID_TEXT_CopyTarget );
	assert( m_pID_TEXT_CopyTargetName );

	//m_pID_FRAME_MailReceive2->SetFather(s_CUI_ID_FRAME_MailMain.GetFrame());
    SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MailReceive2::_UnLoadUI()
{
    m_pID_FRAME_MailReceive2 = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\MailReceive2.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MailReceive2::_IsVisable()
{
    if(!m_pID_FRAME_MailReceive2)
        return false;
	return m_pID_FRAME_MailReceive2->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MailReceive2::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_MailReceive2)
    {
	    m_pID_FRAME_MailReceive2->SetVisable( bVisable );
        if(bVisable)
            ClearControlData();
    }
}

void CUI_ID_FRAME_MailReceive2::UpdateMail(SMail &mail)
{
    if(!m_pID_FRAME_MailReceive2)
        return;

    //theUiManager.ToTop(m_pID_FRAME_MailReceive2);

    m_bShow = false;

    m_mailId = mail.id;

    m_pID_TEXT_FromName->SetText(mail.owners[EM_FromIndex].addressName);
    m_pID_TEXT_SendTargetName->SetText(mail.owners[EM_ToIndex].addressName);
    std::string  strName;
    for (int i = EM_OtherIndex ;i < EM_OtherSendMaxCount;++i)
    {
        if(mail.owners[i].charDbId != 0)
        {
            strName += mail.owners[i].addressName;
            strName += ";";
        }
    }
    
    m_pID_TEXT_CopyTargetName->SetText(strName.c_str());
    m_pID_TEXT_MailTitleName->SetText(mail.title);
    m_pID_TEXT_Content->SetText(mail.content);

    //发送邮件给服务器
    if(mail.state == SMail::EMS_NotOpen)//未打开才发
         OpenMailMsg();

    //设置钱
    if(mail.money > 0)
    {
        ControlListImage::S_ListImg img;
        //img.SetData(58,1,eIcon_Enable,false,eTipFlag_Event);
		img.SetData(1, 1/*,eIcon_Enable,false,eTipFlag_Event*/);

        std::stringstream sstr;
        DWORD inputMoney = mail.money;      
        int gold = 0,silver = 0,copper = 0;
        thePlayerRole.GetGSCFromMoney(inputMoney,gold,silver,copper);

        if (gold > 0)
            sstr << gold << theXmlString.GetString(eText_Money_Gold);
        if (silver > 0)
            sstr << silver << theXmlString.GetString(eText_Money_Silver);
        if (copper > 0)
            sstr << copper << theXmlString.GetString(eText_Money_Copper);

        img.SetOtherInfo(sstr.str().c_str());

        m_pID_LISTIMG_MailMoney->SetItem(&img,0);

        m_bShow = true;
    }

    if(mail.accessory.type == SMail::EAT_None)
        return;

    if(mail.state  == SMail::EMS_HaveGetItem)  //已经取出来就不显示
        return;

    m_MailAccessory = mail.accessory.type;

    //设置附件
    ControlListImage::S_ListImg pImg;

    if(mail.accessory.type == SMail::EAT_Item) //设置附件类型
    {
        SCharItem *pItem = NULL;
        pItem = (SCharItem*)(mail.accessory.content);
        if(!pItem)
            return;

        pImg.SetData(/*pItem->GetItemID(),pItem->GetItemCount()*/pItem);
    }
    else if(mail.accessory.type == SMail::EAT_Mount)
    {
        SMountItem *pMount = NULL;
        pMount = (SMountItem*)(mail.accessory.content);
        if(!pMount)
            return;

        pImg.SetData(pMount->baseInfo.id,1);
    }

    m_bShow = true;
    m_pID_LISTIMG_MailMoney->SetItem(&pImg,1);
}

void CUI_ID_FRAME_MailReceive2::ClearControlData()
{
    m_pID_LISTIMG_MailMoney->Clear();

    m_pID_TEXT_MailTitleName->Clear();
    m_pID_TEXT_FromName->Clear();
    m_pID_TEXT_SendTargetName->Clear();
    m_pID_TEXT_CopyTargetName->Clear();
    m_pID_TEXT_Content->Clear();
}

void CUI_ID_FRAME_MailReceive2::GetMoneyByMailMsg()
{
    MsgOpMailReq msg;

    msg.op = (uint8)EMailOp::EMO_GetMoney;
    msg.mailId = m_mailId;

    GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_MailReceive2::GetItemByMailMsg(ControlListImage::S_ListImg* pImgItem)
{
    if(!pImgItem)
        return;

    int nBagType = BT_NormalItemBag;
    if(m_MailAccessory == SMail::EAT_Mount)
    {
        if(!thePlayerRole.HasMountSpace())
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString( eText_MountBag_NotSpace ) );
            return;
        }
    }
    else if(m_MailAccessory == SMail::EAT_Item)
    {
        ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(pImgItem->m_pkIconInfo->GetItemId());
        if(!pCommon)
            return;

        //是否存放在材料背包，只有这一种类型是在普通背包的,这里不需要判断是否在任务背包中
        if(pCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL || pCommon->ucItemType == ItemDefine::ITEMTYPE_GEM )
        {
            if(thePlayerRole.m_bagMaterial.GetNullItemCount() <= 0)
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString( eText_MaterialPackFull ) );
                return;
            }
            nBagType = BT_MaterialBag;
        }
        else
        {//在普通背包当中
            if(thePlayerRole.m_bag.GetNullItemCount() <= 0)
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString( eText_ItemNoPlace ) );
                return;
            }
            nBagType = BT_NormalItemBag;
        }            
    }


    MsgOpMailReq msg;

    msg.op = (uint8)EMailOp::EMO_GetAccessory;
    msg.mailId = m_mailId;
    msg.accessory = m_MailAccessory;
    msg.bagType  = nBagType;

    GettheNetworkInput().SendMsg(&msg);

}

void CUI_ID_FRAME_MailReceive2::OpenMailMsg()
{
    MsgOpMailReq msg;

    msg.op = (uint8)EMailOp::EMO_Open;
    msg.mailId = m_mailId;

    GettheNetworkInput().SendMsg(&msg);
}

bool CUI_ID_FRAME_MailReceive2::IsExistItem(ControlListImage* pListImg)
{
    if(!m_pID_FRAME_MailReceive2)
        return false;

    if(!pListImg)
        return false;

    return pListImg == m_pID_LISTIMG_MailMoney;
}

void CUI_ID_FRAME_MailReceive2::ProcessMail(ControlListImage::S_ListImg* pImgItem)
{
    if(!m_pID_FRAME_MailReceive2)
        return;

    if(!pImgItem)
        return;

    int nIndex = m_pID_LISTIMG_MailMoney->GetItemIndex(pImgItem);
    if(nIndex < 0)
        return;

    if(nIndex == 0)
        GetMoneyByMailMsg();
    else if(nIndex == 1)
        GetItemByMailMsg(pImgItem);
    else
        assert(0&&"邮件数据有错");
}

void CUI_ID_FRAME_MailReceive2::ClearItem(int nIndex)
{
    if(!IsVisable())
        return;

    int nCount = m_pID_LISTIMG_MailMoney->GetItemCnt();
    if(nIndex < 0 || nIndex >= nCount)
        return;

    ControlListImage::S_ListImg item;
    m_pID_LISTIMG_MailMoney->SetItem(&item,nIndex);

	for(int i =0;i<thePlayerRole.GetCurrentMailSize();++i)
	{
		SMail *pMail = thePlayerRole.ReadMail(i);
		if(!pMail)
			continue;
		if(pMail->id == m_mailId)
		{
			UpdateMail(*pMail);
			return;
		}
	}
}

void CUI_ID_FRAME_MailReceive2::DeleteMail()
{
    if(m_mailId != -1)
    {
        MsgOpMailReq msg;
        msg.op      = EMO_Delete;
        msg.mailId  = m_mailId;

        GettheNetworkInput().SendMsg(&msg);

        m_mailId = -1;
        SetVisable(false);
    }
}

void CUI_ID_FRAME_MailReceive2::GetAllItem()
{
	if (thePlayerRole.GetMailSys().IsHaveMoney(m_mailId))
	{
		GetMoneyByMailMsg();
	}
	if (thePlayerRole.GetMailSys().IsHaveItem(m_mailId))
	{
		ControlListImage::S_ListImg* p_ListImg = m_pID_LISTIMG_MailMoney->GetItemByIndex(1);
		GetItemByMailMsg(p_ListImg);
	}
}