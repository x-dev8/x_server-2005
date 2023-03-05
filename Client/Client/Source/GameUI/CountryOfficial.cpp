/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryOfficial.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MeTerrain/stdafx.h"
#include "wsCamera.h"
#include "wsRender.h"

#include "CountryOfficial.h"
#include "CountryBaseInfo.h"
#include "CountryInput.h"
#include "GameMain.h"
#include "PlayerMgr.h"

#include "SystemConfig.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDx.h"
#include "XmlStringLanguage.h"
#include "RbtnMenu.h"
#include "AboutPeople.h"
#include "Target.h"
#include "MessageBox.h"
#include "AddFriend.h"
#include "SelfRbtnMenu.h"
#include "InfoTips.h"
#include "ScreenInfoManager.h"
#include "CrowdCarryMainMore.h"
#include "GameDefineChar.h"
CUI_ID_FRAME_Official s_CUI_ID_FRAME_Official;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Official, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Official, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_CouncilorRightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_CaptorRightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_CaptorLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_GeneralOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_QueenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_KingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_CouncilorLeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Official, ID_BUTTON_DelOffOnButtonClick )
CUI_ID_FRAME_Official::CUI_ID_FRAME_Official()
{
	// Member
	m_pID_FRAME_Official = NULL;
	m_pID_TEXT_CouncilorLeft = NULL;
	m_pID_TEXT_CaptorRight = NULL;
	m_pID_TEXT_CaptorLeft = NULL;
	m_pID_TEXT_General = NULL;
	m_pID_TEXT_Queen = NULL;
	m_pID_TEXT_King = NULL;
	m_pID_TEXT_CouncilorRight = NULL;
	m_pID_BUTTON_CouncilorRight = NULL;
	m_pID_BUTTON_CaptorRight = NULL;
	m_pID_BUTTON_CaptorLeft = NULL;
	m_pID_BUTTON_General = NULL;
	m_pID_BUTTON_Queen = NULL;
	m_pID_BUTTON_King = NULL;
	m_pID_BUTTON_CouncilorLeft = NULL;

	m_pID_PICTURE_CouncilorLeft = NULL;
	m_pID_PICTURE_CouncilorRight = NULL;
	m_pID_PICTURE_King = NULL;
	m_pID_PICTURE_Queen = NULL;
	m_pID_PICTURE_General = NULL;
	m_pID_PICTURE_CaptorLeft = NULL;
	m_pID_PICTURE_CaptorRight = NULL;
	m_pID_BUTTON_DelOff = NULL;

	m_pID_PICTURE_28124=NULL;
	m_pID_PICTURE_21540 = NULL;

	for(int i=0;i<CountryDefine::Position_Max;++i)
	{
		m_PlayerAnims[i] = NULL;
		m_pPlayers[i] = NULL;
	}

	ResetProperties();

}
void CUI_ID_FRAME_Official::ResetProperties()
{
	for( int i = 0; i < Position_Max; i++ )
	{
		m_CountryOfficialDisPlayer[i].sex = Sex_Male;
		m_CountryOfficialDisPlayer[i].face = 0;
		m_CountryOfficialDisPlayer[i].header= 0;
	}
}
bool CUI_ID_FRAME_Official::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Official::OnFrameRender()
{
	//渲染 国家的官员模型
	for(int i =0; i<CountryDefine::Position_Max;++i)
	{
		//获得每个官员的绘制状态 
		if(s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[i].empty()) continue;
		GetEngine()->GetRenderer()->EndScene();
		//渲染指定官员
		switch(i)
		{
		case Position_CaptorLeft:
			RenderPlayers(m_pID_PICTURE_CaptorLeft,i);
			break;
		case Position_CaptorRight:
			RenderPlayers(m_pID_PICTURE_CaptorRight,i);
			break;
		case Position_CouncilorLeft:
			RenderPlayers(m_pID_PICTURE_CouncilorLeft,i);
			break;
		case Position_CouncilorRight:
			RenderPlayers(m_pID_PICTURE_CouncilorRight,i);
			break;
		case Position_General:
			RenderPlayers(m_pID_PICTURE_General,i);
			break;
		case Position_Queen:
			RenderPlayers(m_pID_PICTURE_Queen,i);
			break;
		case Position_King:
			RenderPlayers(m_pID_PICTURE_King,i);
			break;
		}
		GetEngine()->GetRenderer()->BeginScene();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_CouncilorRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( CUI_ID_FRAME_BaseInfo:: eShowType_AppointChengXiang);
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_CaptorRightOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( CUI_ID_FRAME_BaseInfo::eShowType_AppointYouJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_CaptorLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( CUI_ID_FRAME_BaseInfo::eShowType_AppointZuoJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_GeneralOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( CUI_ID_FRAME_BaseInfo::eShowType_AppointJiangJun );
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_QueenOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_KingOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Official::ID_BUTTON_CouncilorLeftOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
    s_CUI_ID_FRAME_CountryInput.SetVisable( true );
	s_CUI_ID_FRAME_CountryInput.SetShowType( CUI_ID_FRAME_BaseInfo:: eShowType_AppointSiMa);
	return true;
}
bool CUI_ID_FRAME_Official::ID_BUTTON_DelOffOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Official )
	{
		assert( false && "ui error" );
		return false;
	}
	thePlayerRole.DelCountryOfficial();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Official::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CountryOfficial.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CountryOfficial.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Official::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Official, s_CUI_ID_FRAME_OfficialOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Official, s_CUI_ID_FRAME_OfficialOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_CouncilorRight, s_CUI_ID_FRAME_OfficialID_BUTTON_CouncilorRightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_CaptorRight, s_CUI_ID_FRAME_OfficialID_BUTTON_CaptorRightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_CaptorLeft, s_CUI_ID_FRAME_OfficialID_BUTTON_CaptorLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_General, s_CUI_ID_FRAME_OfficialID_BUTTON_GeneralOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_Queen, s_CUI_ID_FRAME_OfficialID_BUTTON_QueenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_King, s_CUI_ID_FRAME_OfficialID_BUTTON_KingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_CouncilorLeft, s_CUI_ID_FRAME_OfficialID_BUTTON_CouncilorLeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Official, ID_BUTTON_DelOff, s_CUI_ID_FRAME_OfficialID_BUTTON_DelOffOnButtonClick);

	m_pID_FRAME_Official = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Official );
	m_pID_TEXT_CouncilorLeft = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_CouncilorLeft );
	m_pID_TEXT_CaptorRight = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_CaptorRight );
	m_pID_TEXT_CaptorLeft = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_CaptorLeft );
	m_pID_TEXT_General = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_General );
	m_pID_TEXT_Queen = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_Queen );
	m_pID_TEXT_King = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_King );
	m_pID_TEXT_CouncilorRight = (ControlText*)theUiManager.FindControl( ID_FRAME_Official, ID_TEXT_CouncilorRight );
	m_pID_BUTTON_CouncilorRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_CouncilorRight );
	m_pID_BUTTON_CaptorRight = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_CaptorRight );
	m_pID_BUTTON_CaptorLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_CaptorLeft );
	m_pID_BUTTON_General = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_General );
	m_pID_BUTTON_Queen = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_Queen );
	m_pID_BUTTON_King = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_King );
	m_pID_BUTTON_CouncilorLeft = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_CouncilorLeft );

	m_pID_PICTURE_CouncilorLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_CouncilorLeft );
	m_pID_PICTURE_CouncilorRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_CouncilorRight );
	m_pID_PICTURE_King = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_King );
	m_pID_PICTURE_Queen = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_Queen );
	m_pID_PICTURE_General = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_General );
	m_pID_PICTURE_CaptorLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_CaptorLeft );
	m_pID_PICTURE_CaptorRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_CaptorRight );

	m_pID_PICTURE_28124 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_28124 );
	m_pID_PICTURE_21540 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Official, ID_PICTURE_21540 );

	m_pID_BUTTON_DelOff = (ControlButton*)theUiManager.FindControl( ID_FRAME_Official, ID_BUTTON_DelOff );

	assert( m_pID_FRAME_Official );
	assert( m_pID_TEXT_CouncilorLeft );
	assert( m_pID_TEXT_CaptorRight );
	assert( m_pID_TEXT_CaptorLeft );
	assert( m_pID_TEXT_General );
	assert( m_pID_TEXT_Queen );
	assert( m_pID_TEXT_King );
	assert( m_pID_TEXT_CouncilorRight );
	assert( m_pID_BUTTON_CouncilorRight );
	assert( m_pID_BUTTON_CaptorRight );
	assert( m_pID_BUTTON_CaptorLeft );
	assert( m_pID_BUTTON_General );
	assert( m_pID_BUTTON_Queen );
	assert( m_pID_BUTTON_King );
	assert( m_pID_BUTTON_CouncilorLeft );

	assert( m_pID_PICTURE_CouncilorLeft );
	assert( m_pID_PICTURE_CouncilorRight );
	assert( m_pID_PICTURE_King );
	assert( m_pID_PICTURE_Queen );
	assert( m_pID_PICTURE_General );
	assert( m_pID_PICTURE_CaptorLeft );
	assert( m_pID_PICTURE_CaptorRight );

	assert( m_pID_PICTURE_28124 );
	assert( m_pID_PICTURE_21540 );

	assert( m_pID_BUTTON_DelOff );

	ResetProperties();

	m_pID_PICTURE_28124->SetVisable(false);
	m_pID_PICTURE_21540->SetVisable(true);

	m_pID_FRAME_Official->SetFather(s_CUI_ID_FRAME_BaseInfo.GetFrame());
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_Official::_UnLoadUI()
{
	m_pID_FRAME_Official = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CountryOfficial.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Official::_IsVisable()
{
	return m_pID_FRAME_Official->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Official::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnInitUIInfo();
	m_pID_FRAME_Official->SetVisable( bVisable );
}
void CUI_ID_FRAME_Official::OnInitUIInfo()
{
	//显示职位 
	//1.显示所有官员名称
	// 官员
	for( int i = 0; i < Position_Max; i++ )
	{
		switch( i )
		{
		case Position_None:
			break;
		case Position_King:
			m_pID_TEXT_King->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_King ].c_str() );
			break;
		case Position_Queen:
			m_pID_TEXT_Queen->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_Queen ].c_str() );
			break;
		case Position_CouncilorLeft:
			m_pID_TEXT_CouncilorLeft->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_CouncilorLeft ].c_str() );
			break;
		case Position_General:
			m_pID_TEXT_General->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_General ].c_str() );
			break;
		case Position_CouncilorRight:
			m_pID_TEXT_CouncilorRight->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_CouncilorRight ].c_str() );
			break;
		case Position_CaptorLeft:
			m_pID_TEXT_CaptorLeft->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_CaptorLeft ].c_str() );
			break;
		case Position_CaptorRight:
			m_pID_TEXT_CaptorRight->SetText( s_CUI_ID_FRAME_BaseInfo.m_strOfficalName[ Position_CaptorRight ].c_str() );
			break;
		default:
			break;
		}
	}
	//判断权限
	// 任免权
	if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & Right_AppointKing )
	{
		// 国王的任免权
		m_pID_BUTTON_CouncilorRight->SetEnable( true );
		m_pID_BUTTON_CouncilorLeft->SetEnable( true );
		m_pID_BUTTON_General->SetEnable( true );
		m_pID_BUTTON_CaptorLeft->SetEnable( false );
		m_pID_BUTTON_CaptorRight->SetEnable( false );
	}
	else if( s_CUI_ID_FRAME_BaseInfo.m_nCountryRight & Right_AppointGeneral )
	{
		// 大将军的任免权
		m_pID_BUTTON_CouncilorRight->SetEnable( false );
		m_pID_BUTTON_CouncilorLeft->SetEnable( false );
		m_pID_BUTTON_General->SetEnable( false );
		m_pID_BUTTON_CaptorLeft->SetEnable( true );
		m_pID_BUTTON_CaptorRight->SetEnable( true );
	}
	else
	{
		// 其他人无任免权
		m_pID_BUTTON_CouncilorRight->SetEnable( false );
		m_pID_BUTTON_CouncilorLeft->SetEnable( false );
		m_pID_BUTTON_General->SetEnable( false );
		m_pID_BUTTON_CaptorLeft->SetEnable( false );
		m_pID_BUTTON_CaptorRight->SetEnable( false );
	}
	UpdateCountryOfficialDisPlayer();

	//判断国王是否存在 存在的话 是否为男的
	if((m_CountryOfficialDisPlayer[Position_King].sex ==0 &&
			m_CountryOfficialDisPlayer[Position_King].face ==0 &&
			m_CountryOfficialDisPlayer[Position_King].header ==0 &&
			m_CountryOfficialDisPlayer[Position_King].profession ==0))
	{
		m_pID_PICTURE_28124->SetVisable(false);
		m_pID_PICTURE_21540->SetVisable(true);
	}
	else if(m_CountryOfficialDisPlayer[Position_King].sex ==ESexType::Sex_Female)
	{
		m_pID_PICTURE_28124->SetVisable(true);
		m_pID_PICTURE_21540->SetVisable(false);
	}
	else if(m_CountryOfficialDisPlayer[Position_King].sex ==ESexType::Sex_Male)
	{
		m_pID_PICTURE_28124->SetVisable(false);
		m_pID_PICTURE_21540->SetVisable(true);
	}
	//判断按钮是否更新
	if(thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition == CountryDefine::Right_None ||
		thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition == CountryDefine::Position_King ||
		thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition == CountryDefine::Position_Queen
		)
	{
		m_pID_BUTTON_DelOff->SetEnable(false);
	}
	else
		m_pID_BUTTON_DelOff->SetEnable(true);
}
void CUI_ID_FRAME_Official::UpdateCountryOfficialDisPlayer()
{
	//更新官员的状态
	for( int i = 0; i < Position_Max; i++ )
	{
		if(m_CountryOfficialDisPlayer[i].sex != s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].sex
			|| m_CountryOfficialDisPlayer[i].face != s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].face
			|| m_CountryOfficialDisPlayer[i].header != s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].header
			|| m_CountryOfficialDisPlayer[i].profession != s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].profession
			)
		{
			//不同的值
			m_CountryOfficialDisPlayer[i].sex = s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].sex;
			m_CountryOfficialDisPlayer[i].face = s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].face;
			m_CountryOfficialDisPlayer[i].header = s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].header;
			m_CountryOfficialDisPlayer[i].profession = s_CUI_ID_FRAME_BaseInfo.m_OfficialDisPlayer[i].profession;

			if(m_CountryOfficialDisPlayer[i].sex == 0xFF || 
				m_CountryOfficialDisPlayer[i].face ==0xFFFF || 
				m_CountryOfficialDisPlayer[i].header == 0xFFFF || 
				m_CountryOfficialDisPlayer[i].profession == 0xFFFF)
				continue;//当前官员模型出错误无法显示

			uint32 EquipID = 0;
			ESexType SexType = ESexType::Sex_Max;
			if(m_CountryOfficialDisPlayer[i].sex  == ESexType::Sex_Male)
			{
				EquipID= s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[i].MaleModeID;
				SexType = ESexType::Sex_Male;
			}
			else if(m_CountryOfficialDisPlayer[i].sex  == ESexType::Sex_Female)
			{
				EquipID = s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[i].FeMaleModeID;
				SexType = ESexType::Sex_Female;
			}
			else
				continue;
				

			switch(i)
			{
			case Position_CaptorLeft:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_CaptorLeft);
				break;
			case Position_CaptorRight:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_CaptorRight);
				break;
			case Position_CouncilorLeft:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_CouncilorLeft);
				break;
			case Position_CouncilorRight:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_CouncilorRight);
				break;
			case Position_General:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_General);
				break;
			case Position_Queen:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_Queen);
				break;
			case Position_King:
				RanderPlayerMode(i,SexType,m_CountryOfficialDisPlayer[i].face,m_CountryOfficialDisPlayer[i].header,EquipID,m_CountryOfficialDisPlayer[i].profession,m_pID_PICTURE_King);
				break;
			}
		}
	}
}
void CUI_ID_FRAME_Official::RanderPlayerMode(int idx,ESexType sex,uint16 faceID,uint16 headerID,uint32 equipID,uint16 professionID,ControlObject* pSender)
{
	//根据指定数据 在指定UI内绘制玩家的模型
	//if(equipID == 0 ) return;
	uint16 stVisualItemID[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipLevel[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipElements[EEquipPartType_MaxEquitPart] = {0};

	m_pPlayers[idx]->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
	m_pPlayers[idx]->UpdateBones();
	m_pPlayers[idx]->SetSex(sex);

	//m_pPlayers[idx]->SetEquipPart(eKeyAll_Face,faceID);
	//m_pPlayers[idx]->SetEquipPart(eKeyAll_Hair,headerID);

	CPlayer_SEquipment equip[eKeyAll_Max];
	equip[eKeyAll_AecorativeClothing].iModelID = equipID;//时装ID
	equip[eKeyAll_Hair].iModelID = headerID;
	equip[eKeyAll_Face].iModelID = faceID;

	m_PlayerAnims[idx]->ChangeSkeletonAndEquipAll(&equip,sex,professionID,0xFFFFFFFF,true, true,0,headerID);
	m_PlayerAnims[idx]->UpdateHardItem( false,(void*)equip );
	
	
	//设置指定模型的 旋转角度 Y轴旋转 并且设置坐标 缩放比例
	if(sex  == ESexType::Sex_Male)
	{
		m_PlayerAnims[idx]->SetScale(s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].ScaleMale);
	}
	else if(sex  == ESexType::Sex_Female)
	{
		m_PlayerAnims[idx]->SetScale(s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].ScaleFeMale);
	}

	m_PlayerAnims[idx]->SetPosition( s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].X,  s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].Y, s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].Z );
	m_PlayerAnims[idx]->SetRotationZ(s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].RotationZ );
	m_PlayerAnims[idx]->SetUpperRot( s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].RotationZ );
	m_pPlayers[idx]->SetPos(s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].X,  s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].Y, s_CUI_ID_FRAME_BaseInfo.m_ModeInfo[idx].Z);
	

	m_PlayerAnims[idx]->PlayAnim2(	MoreActionClient::Idle1,MexAnimCtrl::eNormalPlay, 0,MexAnimCtrl::eMaxLoopTimes, MexAnimCtrl::eMaxTimeout, MoreActionClient::Idle1,MexAnimCtrl::eNormalPlay );
}
void CUI_ID_FRAME_Official::InitializeAtEnterWorld()
{
	Reset();
	DestroyAnimCtrl();

	for ( int i = 0; i < CountryDefine::Position_Max; i ++ )
	{
		m_pPlayers[i] = MeNew CPlayer();
		int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
		if( nIndex >= 0 )
		{
			m_pPlayers[i]->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
		}

	}

	for ( int i = 0; i < CountryDefine::Position_Max; i ++ )
	{
		m_PlayerAnims[i] = MeNew CPlayerAnim();

		m_pPlayers[i]->SetAnim(m_PlayerAnims[i]);
		m_PlayerAnims[i]->SetPlayer( m_pPlayers[i] );

		theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayers[i] );
	}

	InitCamera();

	if ( !m_pID_FRAME_Official )
		return;
	this->SetVisable(false);
}
BOOL CUI_ID_FRAME_Official::InitCamera()
{
	FLOAT fAspect = ((FLOAT)200.0f) / 300.0f;
	m_Camera.SetProjParams( D3DX_PI*(30/45.0f)/4, fAspect, 1.0f, 220.0f );

	m_ViewPort.X = 0;
	m_ViewPort.Y = 0;
	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinZ = 0;
	m_ViewPort.MaxZ = 1;

	return TRUE;
}
void CUI_ID_FRAME_Official::DestroyAnimCtrl()
{
	for ( int i = 0; i < CountryDefine::Position_Max; i ++ )
	{
		if (m_pPlayers[i])
		{
			theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayers[i] );
			m_pPlayers[i]->Destroy();	
			delete m_pPlayers[i];
			m_pPlayers[i] = 0;
			m_PlayerAnims[i] = 0;
		}
	}
}
void CUI_ID_FRAME_Official::Reset()
{
	m_fRotateZ = 0;
	m_bRotate = false;
	DestroyAnimCtrl();

	m_fLightTry1 = 0.6f;
	m_fLightTry2 = 1.0f;
	m_fLightTry3 = 1.0f;
}
void CUI_ID_FRAME_Official::RenderPlayers( ControlPicture* checkBox, const int idx )
{
	RECT rc;
	checkBox->GetRealRect(&rc);

	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	m_ViewPort.X = rc.left;
	m_ViewPort.Y = rc.top;
	m_ViewPort.Width = rc.right - rc.left;
	m_ViewPort.Height = rc.bottom - rc.top;
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;

	r->SetViewport( &m_ViewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	D3DLIGHT9 light = GetSystemConfig()->m_PackRoleLight;
	light.Direction.y = -1*light.Direction.y;

	RECT rcDst = 
	{
		m_ViewPort.X, m_ViewPort.Y, m_ViewPort.X+m_ViewPort.Width, m_ViewPort.Y + m_ViewPort.Height
	};

	RECT rcSrc =
	{
		0, 0, m_ViewPort.Width, m_ViewPort.Height
	};

	GetDrawer()->FillRect2D(rcDst, 0);

	FLOAT fAspect = ((FLOAT)m_ViewPort.Width) / (float)m_ViewPort.Height;
	m_Camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );

	D3DXMATRIX matView;
	D3DXMATRIX matWorld, matOldWorld;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matTransform1;

	//pd3dDevice->GetTransform( D3DTS_WORLD, &matOldWorld );

	//float x = 0, y = -14, z = 0;
	CPlayerAnim* pAnim = m_PlayerAnims[idx];
	/*if(theHeroGame.GetPlayerMgr()->GetMe())
		pAnim->SetPlayer(theHeroGame.GetPlayerMgr()->GetMe());*/
	DWORD dwTime = HQ_TimeGetTime();
	if( pAnim )
	{
		//pAnim->SetPosition( x, y, z );
		//if ( m_pPlayers[idx]->GetSex() == Sex_Male )
		//	pAnim->SetScale( 0.06f/*Config::m_fMdlSpaceScale* pViewport->m_fRoleScaleMale*/ );
		//else
			//pAnim->SetScale( 0.07f/*Config::m_fMdlSpaceScale* pViewport->m_fRoleScaleFemale*/ );

		pAnim->CalcTransformMatrix( (MeMatrix*)&matTransform1 );
		pAnim->Update( dwTime, (MeMatrix*)&matTransform1 );
		pAnim->UpdateComponents( dwTime, (MeMatrix*)&matTransform1 );
	}

	static float fDist = 22.79f;
	static float fRotate = 0.0f;
	static float fRotateX = 0.98199f;
	static D3DXVECTOR3 vEyePt( 0,-1.2f,3.3f );
	static D3DXVECTOR3 vLookatPt( 0.0f,0.0f,0.0f );

	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
	D3DXVec3Normalize( &vDist, &vDist );

	D3DXVECTOR3 vXAxis( 1, 0, 0 );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis(
		&matRotX,
		&vXAxis,
		fRotateX );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );

	D3DXVECTOR3 vZAxis( 0, 0, -1 );
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis(
		&matRotZ,
		&vZAxis,
		fRotate );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );

	D3DXVECTOR3 vPos( 0, 0, 0 );
	m_Camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&m_Camera.GetViewMatrix() );
	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_Camera.GetProjMatrix() );
	float oldLodBias = GetMe3dConfig()->GetMipLodBais();
	GetMe3dConfig()->SetMipLodBais(-1.2);

	r->SetEyePt( (float*)&vEyePt );	
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	r->SetRenderState( D3DRS_LIGHTING, TRUE );	
	r->SetRenderState( D3DRS_FOGENABLE , false );	

	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();
	
	RendererDx* pRendererDx = (RendererDx*)r;
	D3DXVECTOR3 vOldLightDir = pRendererDx->GetLightDir( LIGHT_INDEX_TERRAIN );
	D3DXVECTOR3 vNewLightDir = vOldLightDir;	
	vNewLightDir = vDist;
	D3DXVec3Normalize( &vNewLightDir, &vNewLightDir );
	D3DLIGHT9 kOldLight = SwGlobal::GetRender()->GetD9Light();
	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( m_fLightTry1, m_fLightTry1, m_fLightTry1, 1.0f );
	kLight.Diffuse = D3DXCOLOR( m_fLightTry2, m_fLightTry2, m_fLightTry2, 1.0f );
	kLight.Specular = D3DXCOLOR( m_fLightTry3, m_fLightTry3, m_fLightTry3, 1.0f );
	kLight.Direction = vNewLightDir;	
    pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );

	Config::SetCamera(&m_Camera);

	//pAnim->SetRotationZ( m_fRotateZ );
	//pAnim->SetUpperRot( m_fRotateZ );

	//m_pPlayers[idx]->SetPos(x, y, z);

	// update effect
	m_pPlayers[idx]->UpdateEffectHelper();
	m_pPlayers[idx]->_UpdateFullStarEffect(pAnim->GetPosition().x, pAnim->GetPosition().y, true, pAnim->GetScale());
	m_pPlayers[idx]->_UpdateFiveElementEffect(true, pAnim->GetScale());

	pAnim->Render( 1.0f );

	GetEffectMgr()->SetTheLookerPos( m_Camera.GetEyePt() );
	GetEffectMgr()->SetTheLookerViewDistance( 50 );
	GetEffectMgr()->Update(dwTime);

	m_pPlayers[idx]->_RenderFullStarEffect();
	m_pPlayers[idx]->_RenderFiveElement();

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(false);
	MeRenderManager::Instance()->DoRender(true);

	Config::SetCamera(getwsCamera()->GetMeCamera());	
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kOldLight );

	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix()  );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix()  );
	GetMe3dConfig()->SetMipLodBais(oldLodBias);

	r->EndScene();
	RECT ViewportRect; 
	SetRect( &ViewportRect, m_ViewPort.X, m_ViewPort.Y, 
		m_ViewPort.X + m_ViewPort.Width,
		m_ViewPort.Y + m_ViewPort.Height );

	getwsCamera()->ResetViewport();
}