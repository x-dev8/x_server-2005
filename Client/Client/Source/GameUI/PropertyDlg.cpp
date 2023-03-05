/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\PropertyDlg.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PropertyDlg.h"
#include "Me3d/Engine/Engine.h"
#include "PlayerRole.h"
#include "SystemConfig.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "XmlStringLanguage.h"
#include "Player.h"
#include "Common.h"
#include "baseProperty.h"
CUI_ID_FRAME_PropertyDlg s_CUI_ID_FRAME_PropertyDlg;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PropertyDlg, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PropertyDlg, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_MinJieAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_MinJieMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaMinusOnButtonClick )
CUI_ID_FRAME_PropertyDlg::CUI_ID_FRAME_PropertyDlg()
{
	// Member
	m_pID_FRAME_PropertyDlg = NULL;
	ResetObjects();
}
void CUI_ID_FRAME_PropertyDlg::ResetObjects()
{
	m_pID_PROGRESS_Hp = NULL;
	m_pID_TEXT_SHp = NULL;
	m_pID_TEXT_SMp = NULL;
	m_pID_TEXT_MingZi = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_Job = NULL;
    m_pID_TEXT_ShuFa = NULL;
    m_pID_TEXT_TiZhi = NULL;
    m_pID_TEXT_MinJie = NULL;
    m_pID_TEXT_LiLiang = NULL;
    m_pID_TEXT_HPHuiFu = NULL;
    m_pID_TEXT_MPHuiFu = NULL;
	m_pID_TEXT_JinChengGongJi = NULL;
	m_pID_TEXT_YuanChengGongJi = NULL;
	m_pID_TEXT_MoFaGongJi = NULL;
	m_pID_TEXT_JinChengFangYu = NULL;
	m_pID_TEXT_YuanChengFangYu = NULL;
	m_pID_TEXT_MoFaFangYu = NULL;
    m_pID_TEXT_MoFaJianMian = NULL;
    m_pID_TEXT_YuanChenJianMian = NULL;
    m_pID_TEXT_JinChenJianMian = NULL;
	m_pID_TEXT_BaoJiKang = NULL;
	m_pID_TEXT_ShanBi = NULL;
    m_pID_TEXT_BaoJi = NULL;
    m_pID_TEXT_BaoJiBei = NULL;
    m_pID_TEXT_MingZhong = NULL;
	m_pID_PICTURE_State1 = NULL;
	m_pID_PICTURE_State2 = NULL;
	m_pID_PICTURE_State3 = NULL;
	m_pID_PICTURE_State4 = NULL;
    m_pID_PROGRESS_Mp = NULL;
    m_pID_TEXT_MpText = NULL;
    m_pID_TEXT_FuryText = NULL;
    m_pID_TEXT_EnergyText = NULL;
    m_pID_TEXT_ArrowText = NULL;
    m_pID_TEXT_BulletText = NULL;
    m_pID_TEXT_JinChengGongJiText = NULL;
	m_pID_TEXT_YuanChengGongJiText = NULL;
	m_pID_TEXT_MoFaGongJiText = NULL;
	m_pID_TEXT_MPHuiFuText = NULL;
	m_pID_TEXT_FuryHuiFuText = NULL;
	m_pID_TEXT_EnergyHuiFuText = NULL;
	m_pID_TEXT_ArrowHuiFuText = NULL;
	m_pID_TEXT_BulletHuiFuText = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_LiLiangAdd = NULL;
	m_pID_BUTTON_LiLiangMinus = NULL;
	m_pID_BUTTON_MinJieAdd = NULL;
	m_pID_BUTTON_MinJieMinus = NULL;
	m_pID_BUTTON_TiZhiAdd = NULL;
	m_pID_BUTTON_TiZhiMinus = NULL;
	m_pID_BUTTON_ShuFaAdd = NULL;
	m_pID_BUTTON_ShuFaMinus = NULL;
	m_pID_PICTURE_State5 = NULL;
	m_pID_TEXT_DaoHang = NULL;
	m_pID_TEXT_YiDong = NULL;
	m_pID_TEXT_BeiXi = NULL;
	m_pID_TEXT_BeiXiKang = NULL;

	m_fLiLiangRate = 0.0f;
	m_fMinJieRate = 0.0f;
	m_fTiZhiRate = 0.0f;
	m_fShuFaRate = 0.0f;
	m_nMaxValue = 0;
}

void CUI_ID_FRAME_PropertyDlg::InitializeAtEnterWorld()
{
    ResetAccordToJob();
}

// Frame
bool CUI_ID_FRAME_PropertyDlg::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PropertyDlg::OnFrameRender()
{
	if ( m_fLiLiangRate <= 0.0f && m_fMinJieRate <= 0.0f &&	m_fTiZhiRate <= 0.0f && m_fShuFaRate <= 0.0f )
		return true;

	struct Vertex2D
	{
		D3DXVECTOR4 p;
		DWORD color;
	};

	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

// 	RECT rc;
// 	//m_pID_PICTURE_Ceshi->GetRealRect(&rc);
// 	int radius = rc.bottom - rc.top;
// 
// 	D3DXVECTOR2 center;
// 	center.x = rc.left;
// 	center.y = rc.top;
// 
// 	Vertex2D v[6];
// 
// 	float x18 = cos(D3DXToRadian(18));
// 	float y18 = sin(D3DXToRadian(18));
// 
// 	float x54 = cos(D3DXToRadian(54));
// 	float y54 = sin(D3DXToRadian(54));
// 
// 	// 力量
// 	float l = radius * m_fLiLiangRate;
// 	v[1].p = D3DXVECTOR4( center.x, center.y - l, 0, 1 );
// 	v[1].color = D3DCOLOR_ARGB(185, 255, 0, 0);
// 
// 	// 敏捷
// 	l = radius * m_fMinJieRate;
// 	float x = x18 * l;
// 	float y = y18 * l;
// 	v[2].p = D3DXVECTOR4( center.x - x, center.y - y, 0, 1 );
// 	v[2].color = D3DCOLOR_ARGB(185, 255, 255, 0);
// 
// 	// 体质
// 	l = radius * m_fTiZhiRate;
// 	x = x54 * l;
// 	y = y54 * l;
// 	v[3].p = D3DXVECTOR4( center.x - x, center.y + y, 0, 1 );
// 	v[3].color = D3DCOLOR_ARGB(185, 0, 255, 0);
// 
// 	// 智力
// 	l = radius * m_fShuFaRate;
// 	x = x54 * l;
// 	y = y54 * l;
// 	v[4].p = D3DXVECTOR4( center.x + x, center.y + y, 0, 1 );
// 	v[4].color = D3DCOLOR_ARGB(185, 255, 255, 255);
// 
// 	// 最后一个顶点
// 	l = radius * m_fLiLiangRate;
// 	v[5].p = v[1].p;
// 	v[5].color = v[1].color;
// 
// 	// 中点 
// 	v[0].p = D3DXVECTOR4( center.x, center.y, 0, 1 );
// 	if (m_fLiLiangRate == 1.0f) v[0].color = v[1].color;
// 	else if (m_fMinJieRate == 1.0f) v[0].color = v[2].color;
// 	else if (m_fTiZhiRate == 1.0f) v[0].color = v[3].color;
// 	else if (m_fShuFaRate == 1.0f) v[0].color = v[4].color;
// 
// 	DWORD dwColorOp = D3DTOP_MODULATE;
// 	DWORD dwColor1Arg1 = D3DTA_DIFFUSE;
// 	DWORD dwColor1Arg2 = D3DTA_CURRENT;
// 
// 	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
// 	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
// 	DWORD dwAlphaBlendEnable = TRUE;
// 	DWORD dwAlphaOp = D3DTOP_MODULATE;
// 	DWORD dwAlphaArg1 = D3DTA_DIFFUSE;
// 	DWORD dwAlphaArg2 = D3DTA_CURRENT;
// 
// 	DWORD dwZWriteEnable = FALSE;
// 
// 	r->SetRenderState( D3DRS_LIGHTING, FALSE );
// 	r->SetRenderState( D3DRS_ZENABLE, TRUE );
// 	r->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
// 	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
// 	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
// 	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
// 	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );
// 	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColor1Arg1 );
// 	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColor1Arg2 );
// 	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );
// 	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );
// 	r->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
// 
// 
// 	r->SetTexture( 0, NULL );
// 	r->SetFVF( D3DFVF_XYZRHW|D3DFVF_DIFFUSE );
// 	r->Commit();
// 
// 	r->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 4, v, sizeof( Vertex2D ) );
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if(thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential) <= 0)
		return true;

	MsgCharAssignPotential msg;
	for (int i = 0;i < (int)EBaseAttr_MaxSize;++i)
		msg.nValue[i] = m_nValue[i];

	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_LiLiangAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
	   ++m_nValue[EBaseAttr_Strength];  
	   Refresh();
	}
	
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_LiLiangMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Strength] >0)
	{
		--m_nValue[EBaseAttr_Strength];
	   Refresh();
	}

	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_MinJieAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Agility];  
	   Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_MinJieMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Agility] > 0)
	{
		--m_nValue[EBaseAttr_Agility];
	   Refresh();
	}

	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_TiZhiAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Stamina];  
	   Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_TiZhiMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Stamina] > 0)
	{
		--m_nValue[EBaseAttr_Stamina];  
	   Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_ShuFaAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Intelligence];  
		Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_PropertyDlg::ID_BUTTON_ShuFaMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Intelligence] > 0)
	{
		--m_nValue[EBaseAttr_Intelligence];  
	   Refresh();
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PropertyDlg::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PropertyDlg.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PropertyDlg.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PropertyDlg::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PropertyDlg, s_CUI_ID_FRAME_PropertyDlgOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PropertyDlg, s_CUI_ID_FRAME_PropertyDlgOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_Sure, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangAdd, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_LiLiangAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangMinus, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_LiLiangMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_MinJieAdd, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_MinJieAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_MinJieMinus, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_MinJieMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiAdd, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_TiZhiAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiMinus, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_TiZhiMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaAdd, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_ShuFaAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaMinus, s_CUI_ID_FRAME_PropertyDlgID_BUTTON_ShuFaMinusOnButtonClick );

	m_pID_FRAME_PropertyDlg = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PropertyDlg );
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PROGRESS_Hp );
	m_pID_PROGRESS_Mp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PROGRESS_Mp );
	m_pID_TEXT_SHp = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_SHp );
	m_pID_TEXT_SMp = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_SMp );
	m_pID_TEXT_MingZi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MingZi );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_Level );
	m_pID_TEXT_Job = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_Job );
	m_pID_TEXT_JinChengGongJi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_JinChengGongJi );
	m_pID_TEXT_YuanChengGongJi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_YuanChengGongJi );
	m_pID_TEXT_MoFaGongJi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MoFaGongJi );
	m_pID_TEXT_BaoJi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BaoJi );
	m_pID_TEXT_BaoJiBei = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BaoJiBei );
	m_pID_TEXT_MingZhong = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MingZhong );
	m_pID_TEXT_ShuFa = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_ShuFa );
	m_pID_TEXT_TiZhi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_TiZhi );
	m_pID_TEXT_MinJie = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MinJie );
	m_pID_TEXT_LiLiang = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_LiLiang );
	m_pID_TEXT_JinChengFangYu = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_JinChengFangYu );
	m_pID_TEXT_YuanChengFangYu = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_YuanChengFangYu );
	m_pID_TEXT_MoFaFangYu = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MoFaFangYu );
	m_pID_TEXT_BaoJiKang = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BaoJiKang );
	m_pID_TEXT_ShanBi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_ShanBi );

	m_pID_PICTURE_State1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PICTURE_State1 );
	m_pID_PICTURE_State2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PICTURE_State2 );
	m_pID_PICTURE_State3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PICTURE_State3 );
	m_pID_PICTURE_State4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PICTURE_State4 );

    m_pID_TEXT_JinChengGongJiText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_JinChengGongJiText );
	m_pID_TEXT_YuanChengGongJiText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_YuanChengGongJiText );
	m_pID_TEXT_MoFaGongJiText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MoFaGongJiText );
	m_pID_TEXT_MoFaJianMian = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MoFaJianMian );
	m_pID_TEXT_YuanChenJianMian = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_YuanChenJianMian );
	m_pID_TEXT_JinChenJianMian = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_JinChenJianMian );
	m_pID_TEXT_MPHuiFuText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MPHuiFuText );
	m_pID_TEXT_MPHuiFu = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MPHuiFu );
	m_pID_TEXT_HPHuiFu = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_HPHuiFu );
	m_pID_TEXT_MpText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_MpText );
	m_pID_TEXT_BulletText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BulletText );
	m_pID_TEXT_BulletHuiFuText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BulletHuiFuText );
	m_pID_TEXT_FuryHuiFuText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_FuryHuiFuText );
	m_pID_TEXT_EnergyHuiFuText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_EnergyHuiFuText );
	m_pID_TEXT_ArrowHuiFuText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_ArrowHuiFuText );
	m_pID_TEXT_FuryText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_FuryText );
	m_pID_TEXT_EnergyText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_EnergyText );
	m_pID_TEXT_ArrowText = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_ArrowText );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_Sure );
	m_pID_BUTTON_LiLiangAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangAdd );
	m_pID_BUTTON_LiLiangMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_LiLiangMinus );
	m_pID_BUTTON_MinJieAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_MinJieAdd );
	m_pID_BUTTON_MinJieMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_MinJieMinus );
	m_pID_BUTTON_TiZhiAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiAdd );
	m_pID_BUTTON_TiZhiMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_TiZhiMinus );
	m_pID_BUTTON_ShuFaAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaAdd );
	m_pID_BUTTON_ShuFaMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_BUTTON_ShuFaMinus );
	m_pID_PICTURE_State5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_PICTURE_State5 );
	m_pID_TEXT_DaoHang = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_DaoHang );
	m_pID_TEXT_YiDong = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_YiDong );
	m_pID_TEXT_BeiXi = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BeiXi );
	m_pID_TEXT_BeiXiKang = (ControlText*)theUiManager.FindControl( ID_FRAME_PropertyDlg, ID_TEXT_BeiXiKang );
	m_pID_TEXT_DianShu  = (ControlText*)theUiManager.FindControl(ID_FRAME_PropertyDlg,ID_TEXT_DianShu);

	assert( m_pID_FRAME_PropertyDlg );
	assert( m_pID_PROGRESS_Hp );
	assert( m_pID_TEXT_SHp );
	assert( m_pID_TEXT_SMp );
	assert( m_pID_TEXT_MingZi );
	assert( m_pID_TEXT_Level );
	assert( m_pID_TEXT_Job );
	assert( m_pID_TEXT_JinChengGongJi );
	assert( m_pID_TEXT_YuanChengGongJi );
	assert( m_pID_TEXT_MoFaGongJi );
	assert( m_pID_TEXT_BaoJi );
	assert( m_pID_TEXT_BaoJiBei );
	assert( m_pID_TEXT_MingZhong );
	assert( m_pID_TEXT_ShuFa );
	assert( m_pID_TEXT_TiZhi );
	assert( m_pID_TEXT_MinJie );
	assert( m_pID_TEXT_LiLiang );
	assert( m_pID_TEXT_BaoJiKang );
	assert( m_pID_TEXT_ShanBi );
	assert( m_pID_PICTURE_State1 );
	assert( m_pID_PICTURE_State2 );
	assert( m_pID_PICTURE_State3 );
	assert( m_pID_PICTURE_State4 );
    assert( m_pID_TEXT_JinChengGongJiText );
	assert( m_pID_TEXT_YuanChengGongJiText );
	assert( m_pID_TEXT_MoFaGongJiText );
    assert( m_pID_TEXT_JinChengFangYu );
    assert( m_pID_TEXT_YuanChengFangYu );
    assert( m_pID_TEXT_MoFaFangYu );
	assert( m_pID_TEXT_MoFaJianMian );
	assert( m_pID_TEXT_YuanChenJianMian );
	assert( m_pID_TEXT_JinChenJianMian );
	assert( m_pID_TEXT_MPHuiFu );
	assert( m_pID_TEXT_HPHuiFu );
    assert( m_pID_PROGRESS_Mp );
	assert( m_pID_TEXT_MpText );
    assert(	m_pID_TEXT_FuryText );
    assert(	m_pID_TEXT_EnergyText );
    assert(	m_pID_TEXT_ArrowText );
	assert( m_pID_TEXT_BulletText );
    assert( m_pID_TEXT_MPHuiFuText );
    assert( m_pID_TEXT_FuryHuiFuText );
    assert( m_pID_TEXT_EnergyHuiFuText );
    assert( m_pID_TEXT_ArrowHuiFuText );
	assert( m_pID_TEXT_BulletHuiFuText );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_BUTTON_LiLiangAdd );
	assert( m_pID_BUTTON_LiLiangMinus );
	assert( m_pID_BUTTON_MinJieAdd );
	assert( m_pID_BUTTON_MinJieMinus );
	assert( m_pID_BUTTON_TiZhiAdd );
	assert( m_pID_BUTTON_TiZhiMinus );
	assert( m_pID_BUTTON_ShuFaAdd );
	assert( m_pID_BUTTON_ShuFaMinus );
	assert( m_pID_PICTURE_State5 );
	assert( m_pID_TEXT_DaoHang );
	assert( m_pID_TEXT_YiDong);
	assert( m_pID_TEXT_BeiXi );
	assert( m_pID_TEXT_BeiXiKang );

	m_pID_PICTURE_State1->setShowTip( true );
	m_pID_PICTURE_State2->setShowTip( true );
	m_pID_PICTURE_State3->setShowTip( true );
	m_pID_PICTURE_State4->setShowTip( true );
    m_pID_PROGRESS_Hp->setShowTip( true );
    m_pID_PROGRESS_Mp->setShowTip( true );

	m_pID_FRAME_PropertyDlg->SetFather( s_CUI_ID_FRAME_BaseProperty.GetFrame() );
    ResetAccordToJob();
	ResetTipsByProfession();

    CreateProgressAni();

	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PropertyDlg::_UnLoadUI()
{
	m_pID_FRAME_PropertyDlg = NULL;
	ResetObjects();
	return theUiManager.RemoveFrame( "Data\\UI\\PropertyDlg.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PropertyDlg::_IsVisable()
{
	if( !m_pID_FRAME_PropertyDlg )
		return false;
	return m_pID_FRAME_PropertyDlg->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PropertyDlg::_SetVisable( const bool bVisable )
{
	if( m_pID_FRAME_PropertyDlg )
	{
		m_pID_FRAME_PropertyDlg->SetVisable( bVisable );
		if( bVisable  )
		{
			ClearValue();
			Refresh();
		}
	}
}

void CUI_ID_FRAME_PropertyDlg::Refresh()
{
	// 人名 等级 职业
	if( !m_pID_FRAME_PropertyDlg )
		return;
	*m_pID_TEXT_MingZi = thePlayerRole.GetName();
	*m_pID_TEXT_Level = thePlayerRole.GetLevel();
	
	CProfessionInfo *pInfo = GetSystemConfig()->GetProessionInfoFromID( thePlayerRole.GetProfession() );
    if (pInfo)
    {
        *m_pID_TEXT_Job = pInfo->m_strProShow;
    }

	const SCharBaseInfo	*pBaseInfo = thePlayerRole.m_pBaseInfo;
	char szTemp[eMAX_TEMP_BUFF] = {0};

    // 生命和魔法值
    __int64 nHp = thePlayerRole.GetData( CPlayerRole::TYPE_HP );
    __int64 nMaxHp = thePlayerRole.GetData( CPlayerRole::TYPE_HPMAX );
    __int64 nMp = thePlayerRole.GetData( CPlayerRole::TYPE_MP );
    __int64 nMaxMp = thePlayerRole.GetData( CPlayerRole::TYPE_MPMAX );

	// 生命上限
 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%I64u / %I64u", nHp, nMaxHp );
 	*m_pID_TEXT_SHp = szTemp;
	m_pID_PROGRESS_Hp->SetMaxValue( nMaxHp );
	m_pID_PROGRESS_Hp->SetValue( nHp );
	// 法力上限
 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%I64u / %I64u", nMp, nMaxMp );
 	*m_pID_TEXT_SMp = szTemp;

	m_pID_PROGRESS_Mp->SetMaxValue( nMaxMp );
	m_pID_PROGRESS_Mp->SetValue( nMp );
    // 换成Tip显示了。 2小时后，又改回来了……
    //std::stringstream tipInfoAllInOne;
    //tipInfoAllInOne << theXmlString.GetString(eTip_sAddHPMax) << ":" << nHp << "/" << nMaxHp << "\n";
    switch( thePlayerRole.GetProfession() )
    {
    case EArmType_Warrior:
        //tipInfoAllInOne << theXmlString.GetString( eText_Fp ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Fury->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    case EArmType_Mage:
        //tipInfoAllInOne << theXmlString.GetString( eTip_sAddMPMax ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Mp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    case EArmType_Taoist:
        //tipInfoAllInOne << theXmlString.GetString( eTip_sAddMPMax ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Mp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    case EArmType_Assassin:
        //tipInfoAllInOne << theXmlString.GetString( eText_Ep ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Energy->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    case EArmType_Hunter:
        //tipInfoAllInOne << theXmlString.GetString( eText_Ap ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Arrow->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    case EArmType_Sniper:
        //tipInfoAllInOne << theXmlString.GetString( eText_Bp ) << ":" << nMp << "/" << nMaxMp << "\n";
        //m_pID_PROGRESS_Arrow->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
        break;
    default:
        break;
    }
    //m_pID_PROGRESS_Hp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );

	// 四围
	float fFactor = 0.0f;
	int nLiLiang = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Strength) + fFactor) + m_nValue[EBaseAttr_Strength];
	int nMinJie = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Agility) + fFactor) + m_nValue[EBaseAttr_Agility];
	int nTiZhi = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Stamina) + fFactor) + m_nValue[EBaseAttr_Stamina];
	int nShuFa = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Intelligence) + fFactor) + m_nValue[EBaseAttr_Intelligence];
	*m_pID_TEXT_LiLiang = nLiLiang;
	*m_pID_TEXT_MinJie = nMinJie;
	*m_pID_TEXT_TiZhi = nTiZhi;
	*m_pID_TEXT_ShuFa = nShuFa;

	*m_pID_TEXT_JinChengGongJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_ATTACKPHYSICS);  //物理攻击
	*m_pID_TEXT_JinChengFangYu = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_DefendPhysics);  //物理防御
	*m_pID_TEXT_MoFaGongJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_AttackMagic);        //魔法攻击
	*m_pID_TEXT_MoFaFangYu = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_DefendMagic);        //魔法防御

	// 闪避
	m_pID_TEXT_ShanBi->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_DODGE));
	//移动速度
	m_pID_TEXT_YiDong->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_MOVESPEED));
	//背袭强度
	m_pID_TEXT_BeiXi->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrike));
	//背袭抗性
	m_pID_TEXT_BeiXiKang->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrikeResist));
	//m_pID_TEXT_BulletText->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_BackStrikeResist));
	// 命中
	m_pID_TEXT_MingZhong->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_EXACT));
	// 暴击
	*m_pID_TEXT_BaoJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLE);
	// 暴击伤害
	*m_pID_TEXT_BaoJiBei = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLEINTENSITY);
	// 韧性或暴击抗性
	*m_pID_TEXT_BaoJiKang = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_TENACITY);
	//道行
	*m_pID_TEXT_DaoHang = (int)thePlayerRole.GetData(CPlayerRole::TYPE_Daoxing);

	//剩余点数
	*m_pID_TEXT_DianShu = (int)GetNoUseSkillPoint();

// 	*m_pID_TEXT_YuanChengGongJi = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.attackMagic.final;
// 	*m_pID_TEXT_YuanChengFangYu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.defendMagic.final;




	// 3免
// 	*m_pID_TEXT_JinChenJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateShort.final;
// 	*m_pID_TEXT_YuanChenJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateLong.final;
// 	*m_pID_TEXT_MoFaJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateMagic.final;
	// 回血
	//*m_pID_TEXT_HPHuiFu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.hpRestore.final;
	// 回魔
//*m_pID_TEXT_MPHuiFu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.energyRestore.final;
	// 移动速度
	//MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%.1f", thePlayerRole.m_pBaseInfo->baseProperty.fight.moveSpeed.final);

	// 4抗
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Coma ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistComa.final );
// 	m_pID_PICTURE_State1->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Dread ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistDread.final );
// 	m_pID_PICTURE_State2->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Silence ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSilence.final );
// 	m_pID_PICTURE_State3->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Slow ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSlow.final );
// 	m_pID_PICTURE_State4->setTip( szTemp );



	// 图形 暂无此功能
	m_nMaxValue = max( nLiLiang, 0 );
	m_nMaxValue = max( nMinJie, m_nMaxValue );
	m_nMaxValue = max( nTiZhi, m_nMaxValue );
	m_nMaxValue = max( nShuFa, m_nMaxValue );

	if (m_nMaxValue > 0)
	{
		m_fLiLiangRate = ( float )( nLiLiang / m_nMaxValue );
		m_fMinJieRate = ( float )( nMinJie / m_nMaxValue );
		m_fTiZhiRate = ( float )( nTiZhi / m_nMaxValue );
		m_fShuFaRate = ( float )( nShuFa / m_nMaxValue );
	}
	else
	{
		m_fLiLiangRate = 0.0f;
		m_fMinJieRate = 0.0f;
		m_fTiZhiRate = 0.0f;
		m_fShuFaRate = 0.0f;
	}

	// 暂无此功能
    //char szBuff[eMAX_TEMP_BUFF] = {0};
 	// 精力
	//MeSprintf_s( szBuff, eMAX_TEMP_BUFF -1, "%d/%d", 
	//	thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR ),
	//	thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR_MAX ) );

	// 活力
	//MeSprintf_s( szBuff, eMAX_TEMP_BUFF -1, "%d/%d", 
	//	thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY ),
	//	thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY_MAX ) );
}

bool CUI_ID_FRAME_PropertyDlg::SetFrameFather( ControlObject* pFather )
{
	if( !m_pID_FRAME_PropertyDlg || !pFather )
		return false;
	m_pID_FRAME_PropertyDlg->SetFather(pFather);
	return true;
}

void CUI_ID_FRAME_PropertyDlg::ResetAccordToJob()
{
    if( !m_pID_FRAME_PropertyDlg )
        return;

// 	m_pID_TEXT_JinChengGongJiText->SetVisable( false );
// 	m_pID_TEXT_YuanChengGongJiText->SetVisable( false );
// 	m_pID_TEXT_MoFaGongJiText->SetVisable( false );
// 	m_pID_TEXT_JinChengGongJi->SetVisable( false );
// 	m_pID_TEXT_MoFaGongJi->SetVisable( false );
// 	m_pID_TEXT_YuanChengGongJi->SetVisable( false );
// 		
// 	m_pID_TEXT_MpText->SetVisable( false );
// 	m_pID_TEXT_FuryText->SetVisable( false );
// 	m_pID_TEXT_EnergyText->SetVisable( false );
// 	m_pID_TEXT_ArrowText->SetVisable( false );
// 	m_pID_TEXT_BulletText->SetVisable( false );
// 	m_pID_PROGRESS_Mp->SetVisable( false );
// 	m_pID_PROGRESS_Fury->SetVisable( false );
// 	m_pID_PROGRESS_Energy->SetVisable( false );
// 	m_pID_PROGRESS_Arrow->SetVisable( false );
// 
// 	m_pID_TEXT_MPHuiFuText->SetVisable( false );
// 	m_pID_TEXT_FuryHuiFuText->SetVisable( false );
// 	m_pID_TEXT_EnergyHuiFuText->SetVisable( false );
// 	m_pID_TEXT_ArrowHuiFuText->SetVisable( false );
// 	m_pID_TEXT_BulletHuiFuText->SetVisable( false );
//     
// 	switch( thePlayerRole.GetProfession() )
// 	{
// 	case EArmType_Warrior:
//         m_pID_TEXT_JinChengGongJiText->SetVisable( true );
//         m_pID_TEXT_JinChengGongJi->SetVisable( true );
//         m_pID_TEXT_FuryText->SetVisable( true );
//         m_pID_PROGRESS_Fury->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_FuryHuiFuText->SetVisable( true );
//         break;
//     case EArmType_Mage:
//         m_pID_TEXT_MoFaGongJiText->SetVisable( true );	
//         m_pID_TEXT_MoFaGongJi->SetVisable( true );
//         m_pID_TEXT_MpText->SetVisable( true );
//         m_pID_PROGRESS_Mp->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_MPHuiFuText->SetVisable( true );
//         break;
//     case EArmType_Taoist:
//         m_pID_TEXT_MoFaGongJiText->SetVisable( true );	
//         m_pID_TEXT_MoFaGongJi->SetVisable( true );
//         m_pID_TEXT_MpText->SetVisable( true );
//         m_pID_PROGRESS_Mp->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_MPHuiFuText->SetVisable( true );
//         break;
//     case EArmType_Assassin:
//         m_pID_TEXT_JinChengGongJiText->SetVisable( true );
//         m_pID_TEXT_JinChengGongJi->SetVisable( true );
//         m_pID_TEXT_EnergyText->SetVisable( true );
//         m_pID_PROGRESS_Energy->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_EnergyHuiFuText->SetVisable( true );
//         break;
//     case EArmType_Hunter:
//         m_pID_TEXT_YuanChengGongJiText->SetVisable( true );
//         m_pID_TEXT_YuanChengGongJi->SetVisable( true );
//         m_pID_TEXT_ArrowText->SetVisable( true );
//         m_pID_PROGRESS_Arrow->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_ArrowHuiFuText->SetVisable( true );
//         break;
//     case EArmType_Sniper:
//         m_pID_TEXT_YuanChengGongJiText->SetVisable( true );
//         m_pID_TEXT_YuanChengGongJi->SetVisable( true );
//         m_pID_TEXT_BulletText->SetVisable( true );
//         m_pID_PROGRESS_Arrow->SetVisable( true );
//         m_pID_TEXT_SMp->SetVisable( false );
//         m_pID_TEXT_SMp->SetVisable( true );
//         m_pID_TEXT_BulletHuiFuText->SetVisable( true );
// 		break;
// 	default:
// 		break;
// 	}
}

void CUI_ID_FRAME_PropertyDlg::ResetTipsByProfession()
{
	switch( thePlayerRole.GetProfession() )
	{
	case EArmType_Warrior:
		{
			SetCtlTip(m_pID_TEXT_MPHuiFu, theXmlString.GetString(eText_PropertyDlg_Tip_MPHuiFu_Warrior));
			SetCtlTip(m_pID_TEXT_MinJie, theXmlString.GetString(eText_PropertyDlg_Tip_MinJie_ExceptHunter));
			SetCtlTip(m_pID_TEXT_LiLiang, theXmlString.GetString(eText_PropertyDlg_Tip_LiLiang_Warrior));
			SetCtlTip(m_pID_TEXT_SMp, theXmlString.GetString(/*eText_PropertyDlg_Tip_Luqi*/eText_PropertyDlg_Tip_Magic));
		}
		break;
	case EArmType_Mage:
		{
			SetCtlTip(m_pID_TEXT_ShuFa, theXmlString.GetString(eText_PropertyDlg_Tip_ShuFa_Mage));
			SetCtlTip(m_pID_TEXT_MPHuiFu, theXmlString.GetString(eText_PropertyDlg_Tip_MPHuiFu_MageTaoist));
			SetCtlTip(m_pID_TEXT_MinJie, theXmlString.GetString(eText_PropertyDlg_Tip_MinJie_ExceptHunter));
			SetCtlTip(m_pID_TEXT_LiLiang, theXmlString.GetString(eText_PropertyDlg_Tip_LiLiang_HunterTaoistMage));
			SetCtlTip(m_pID_TEXT_SMp, theXmlString.GetString(eText_PropertyDlg_Tip_Magic));
		}
		break;
	case EArmType_Taoist:
		{
			SetCtlTip(m_pID_TEXT_ShuFa, theXmlString.GetString(eText_PropertyDlg_Tip_ShuFa_Taoist));
			SetCtlTip(m_pID_TEXT_MPHuiFu, theXmlString.GetString(eText_PropertyDlg_Tip_MPHuiFu_MageTaoist));
			SetCtlTip(m_pID_TEXT_MinJie, theXmlString.GetString(eText_PropertyDlg_Tip_MinJie_ExceptHunter));
			SetCtlTip(m_pID_TEXT_LiLiang, theXmlString.GetString(eText_PropertyDlg_Tip_LiLiang_HunterTaoistMage));
			SetCtlTip(m_pID_TEXT_SMp, theXmlString.GetString(eText_PropertyDlg_Tip_Magic));
		}
		break;
	case EArmType_Assassin:
		{
			SetCtlTip(m_pID_TEXT_MPHuiFu, theXmlString.GetString(eText_PropertyDlg_Tip_MPHuiFu_Assassin));
			SetCtlTip(m_pID_TEXT_MinJie, theXmlString.GetString(eText_PropertyDlg_Tip_MinJie_ExceptHunter));
			SetCtlTip(m_pID_TEXT_LiLiang, theXmlString.GetString(eText_PropertyDlg_Tip_LiLiang_Assassin));
			SetCtlTip(m_pID_TEXT_SMp, theXmlString.GetString(/*eText_PropertyDlg_Tip_Power*/eText_PropertyDlg_Tip_Magic));
		}
		break;
	case EArmType_Hunter:
		{
			SetCtlTip(m_pID_TEXT_MPHuiFu, theXmlString.GetString(eText_PropertyDlg_Tip_MPHuiFu_Hunter));
			SetCtlTip(m_pID_TEXT_MinJie, theXmlString.GetString(eText_PropertyDlg_Tip_MinJie_Hunter));
			SetCtlTip(m_pID_TEXT_LiLiang, theXmlString.GetString(eText_PropertyDlg_Tip_LiLiang_HunterTaoistMage));
			SetCtlTip(m_pID_TEXT_SMp, theXmlString.GetString(/*eText_PropertyDlg_Tip_Arrow*/eText_PropertyDlg_Tip_Magic));
		}
		break;
	default:
		break;
	}
}

inline void CUI_ID_FRAME_PropertyDlg::SetCtlTip(ControlText* pCtl, const char* szText)
{
	if (!pCtl || !szText)
	{
		return;
	}

	pCtl->setTip(szText);
	pCtl->setShowTip(true);
}

void CUI_ID_FRAME_PropertyDlg::CreateProgressAni()
{
    if( !IsUILoad() )
        return;

    char fullname[MAX_PATH] = {0};
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerHp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Hp->CreateAnimation( fullname );
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerMp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Mp->CreateAnimation( fullname );
}

int CUI_ID_FRAME_PropertyDlg::GetNoUseSkillPoint()
{
	int nTotoal = 0;
	for (int i = 0;i < (int)EBaseAttr_MaxSize;++i)
		nTotoal += m_nValue[i];

	return thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential) - nTotoal; 
}