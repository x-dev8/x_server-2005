/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolEnvironment.cpp
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "edit/BaseTool.h"
#include "Edit/ToolLight.h"
#include "Edit/ToolManager.h"
#include "ToolWorldLight.h"

float Hue2RGB(float v1,float v2,float vH)
{
	if(vH<0) vH+=1;
	if(vH>1) vH-=1;

	if(6.0f*vH<1) return v1+(v2-v1)*6.0*vH;
	if(2.0f*vH<1) return v2;
	if(3.0f*vH<2) return v1+(v2-v1)*((2.0f/3.0f)-vH)*6.0f;

	return v1;
}
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolWorldLightDlg, CDialog)

CToolWorldLightDlg::CToolWorldLightDlg(CToolWorldLightDlg* pParent)
: CDialog(CToolWorldLightDlg::IDD, pParent)
{
	m_curSel				= -1;
	m_ptSphericalPos		= Vector::UNIT_X;

	m_colorAmbientLight		= RGB(0xaa,0xaa,0xaa);
	m_colorDiffuseLight		= RGB(0x52,0x52,0x52);
	m_colorSpecularLight	= RGB(0x33,0x33,0x33);
	m_colorSunless			= RGB(0xbb,0xbb,0xbb);

}

CToolWorldLightDlg::~CToolWorldLightDlg()
{

}

void CToolWorldLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolWorldLightDlg)	
	DDX_Control(pDX, IDC_SLIDER_COLOR_H, m_sliderH);
	DDX_Control(pDX, IDC_SLIDER_COLOR_S, m_sliderS);
	DDX_Control(pDX, IDC_SLIDER_COLOR_L, m_sliderL);
	DDX_Control(pDX, IDC_LIST_LIGHT_PARAM, mLightsLB);

	DDX_Control(pDX, IDC_BTN_LIGHT_AMBIENT, m_cpAmbientLight);
	DDX_Control(pDX, IDC_BTN_LIGHT_DIFFUSE, m_cpDiffuseLight);
	DDX_Control(pDX, IDC_BTN_LIGHT_SPECULAR, m_cpSpecularLight);
	DDX_Control(pDX, IDC_BTN_LIGHT_SUNLESS, m_cpSunlessColor);

	DDX_XTColorPicker(pDX, IDC_BTN_LIGHT_AMBIENT, m_colorAmbientLight);
	DDX_XTColorPicker(pDX, IDC_BTN_LIGHT_DIFFUSE, m_colorDiffuseLight);
	DDX_XTColorPicker(pDX, IDC_BTN_LIGHT_SPECULAR, m_colorSpecularLight);
	DDX_XTColorPicker(pDX, IDC_BTN_LIGHT_SUNLESS, m_colorSunless);

	DDX_Control(pDX, IDC_EDT_LIGHT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_LIGHT_DIR_X, m_editLightLongitude);
	DDX_Control(pDX, IDC_EDIT_LIGHT_DIR_Y, m_editLightLatitude);
	DDX_Control(pDX, IDC_SPIN_LONGITUDE, m_spinLongitude);
	DDX_Control(pDX, IDC_SPIN_LATITUDE, m_spinLatitude);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolWorldLightDlg, CDialog)
	//{{AFX_MSG_MAP(CToolWorldLightDlg)
	ON_BN_CLICKED(IDC_BTN_LIGHT_ADD, OnClickAddBtn)
	ON_BN_CLICKED(IDC_BTN_LIGHT_DEL, OnClickDelBtn)
	ON_CPN_XT_SELENDOK(IDC_BTN_LIGHT_AMBIENT, OnSelEndOkAmbientLight)
	ON_CPN_XT_SELENDOK(IDC_BTN_LIGHT_DIFFUSE, OnSelEndOkDiffuseLight)
	ON_CPN_XT_SELENDOK(IDC_BTN_LIGHT_SPECULAR, OnSelEndOkSpecularLight)
	ON_CPN_XT_SELENDOK(IDC_BTN_LIGHT_SUNLESS, OnSelEndOkSunLess)
	ON_LBN_SELCHANGE(IDC_LIST_LIGHT_PARAM, OnLightChange)
	ON_EN_KILLFOCUS(IDC_EDIT_LIGHT_DIR_X, OnKillfocusLightLongitude)
	ON_EN_KILLFOCUS(IDC_EDIT_LIGHT_DIR_Y, OnKillfocusLightLatitude)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LIGHT_SET, &CToolWorldLightDlg::OnBnClickedBtnLightModify)
	ON_BN_CLICKED(IDC_RADIO_AMBIENT, &CToolWorldLightDlg::OnBnClickedRadioAmbient)
	ON_BN_CLICKED(IDC_RADIO_DIFFUSE, &CToolWorldLightDlg::OnBnClickedRadioDiffuse)
	ON_BN_CLICKED(IDC_RADIO_SPECULAR, &CToolWorldLightDlg::OnBnClickedRadioSpecular)
	ON_BN_CLICKED(IDC_RADIO_SUNLESS, &CToolWorldLightDlg::OnBnClickedRadioSunless)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CToolWorldLightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cpAmbientLight.SetDefaultColor( RGB(0xaa,0xaa,0xaa) );
	m_cpAmbientLight.ShowText(true);
	m_cpDiffuseLight.SetDefaultColor( RGB(0x33,0x33,0x33) );
	m_cpDiffuseLight.ShowText(true);
	m_cpSpecularLight.SetDefaultColor( RGB(0x33,0x33,0x33) );
	m_cpSpecularLight.ShowText(true);
	m_cpSunlessColor.SetDefaultColor( RGB(0xbb,0xbb,0xbb) );
	m_cpSunlessColor.ShowText(true);

	m_spinLongitude.SetBuddy( &m_editLightLongitude);
	m_spinLongitude.SetRange( 0x0, 360 );  
	m_spinLongitude.SetPos( 0 );

	m_spinLatitude.SetBuddy( &m_editLightLatitude);
	m_spinLatitude.SetRange( 0x0, 360 );  
	m_spinLatitude.SetPos( 90 );
	m_sliderH.SetRange(0,255);
	m_sliderS.SetRange(0,255);
	m_sliderL.SetRange(0,255);

	Reset();

	UpdateData( FALSE );

	return TRUE;
}

void CToolWorldLightDlg::SetActive( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LIGHT );
	CToolLight* toolLight = (CToolLight*)( toolManager->GetActiveTool() );
	Assert( NULL != toolLight );
	toolLight->Bind( this );

	UpdateLightsLB();

	m_curSel	= -1;
	m_editName.SetWindowText( _T("") );
	theApp.SetLightDir( SwPublicFunc::Spherical2Cartesian(m_ptSphericalPos) );
	NiColor color;
	ConvertRGB2NiColor( m_colorAmbientLight, color );
	theApp.SetLightAmbientColor( color );
	ConvertRGB2NiColor( m_colorDiffuseLight, color );
	theApp.SetLightDiffuseColor( color );
	ConvertRGB2NiColor( m_colorSpecularLight, color );
	theApp.SetLightSpecularColor( color );
	ConvertRGB2NiColor( m_colorSunless, color );
	theApp.SetSunLessColor( color );

	updateHSL();
}

void CToolWorldLightDlg::OnLightChange()
{
	m_curSel = mLightsLB.GetCurSel();
	if( -1 != m_curSel ) {
		CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
		if (NULL == resMgr)
		{
			return;
		}

		CNdlLightRes* lightRes = resMgr->GetLightRes( m_curSel );
		if( NULL != lightRes ) { 
			SetLight( lightRes );

			CNdlLightRes* p = (CNdlLightRes*)(resMgr->GetLightList()[m_curSel]);

			theApp.SetLightDir( p->m_lightDir );
			NiColor color;
			ConvertRGB2NiColor( p->m_lightAmbient, color );
			theApp.SetLightAmbientColor( color );
			ConvertRGB2NiColor( p->m_lightDiffuse, color );
			theApp.SetLightDiffuseColor( color );
			ConvertRGB2NiColor( p->m_lightSpecular, color );
			theApp.SetLightSpecularColor( color );
			ConvertRGB2NiColor( lightRes->m_colorSunless, color );
			theApp.SetSunLessColor( color );

			CToolLight*	toolLight = GetLightTool();
			toolLight->SetLightDir(p->m_lightDir);
		}
	}
	updateHSL();
}


void CToolWorldLightDlg::OnSelEndOkAmbientLight()
{
	UpdateData();

	NiColor color;
	ConvertRGB2NiColor( m_colorAmbientLight, color );
	theApp.SetLightAmbientColor( color );

	updateHSL();
}

void CToolWorldLightDlg::OnSelEndOkDiffuseLight()
{

	UpdateData();

	NiColor color;
	ConvertRGB2NiColor( m_colorDiffuseLight, color );
	theApp.SetLightDiffuseColor( color );

	updateHSL();
}

void CToolWorldLightDlg::OnSelEndOkSunLess()
{
	UpdateData();

	NiColor color;
	ConvertRGB2NiColor( m_colorSunless, color );
	theApp.SetSunLessColor( color );

	updateHSL();
}

void CToolWorldLightDlg::OnSelEndOkSpecularLight()
{

	UpdateData();

	NiColor color;
	ConvertRGB2NiColor( m_colorSpecularLight, color );
	theApp.SetLightSpecularColor( color );
}

void CToolWorldLightDlg::OnKillfocusLightLongitude()
{
	CString strValue;
	m_editLightLongitude.GetWindowText( strValue );
	m_ptSphericalPos.y		= StringToAngle(strValue);

	short nPos = atoi(strValue.GetString());
	nPos %= 360;
	m_spinLongitude.SetPos(nPos);

	RefreshLight();
}

void CToolWorldLightDlg::OnKillfocusLightLatitude()
{
	CString strValue;
	m_editLightLatitude.GetWindowText( strValue );
	short nPos = atoi(strValue.GetString());
	nPos %= 360;
	m_spinLatitude.SetPos(nPos);

	m_ptSphericalPos.z		= StringToAngle( strValue );

	RefreshLight();

}

void CToolWorldLightDlg::SetLight( CNdlLightRes* lightRes )
{
	m_colorAmbientLight		= lightRes->m_lightAmbient;
	m_colorDiffuseLight		= lightRes->m_lightDiffuse;
	m_colorSpecularLight	= lightRes->m_lightSpecular;
	m_colorSunless	= lightRes->m_colorSunless;

	CString strValue;
	strValue = lightRes->GetName();
	m_editName.SetWindowText( strValue );

	m_ptSphericalPos = SwPublicFunc::Cartesian2Spherical(lightRes->m_lightDir);

	m_ptSphericalPos.x = 1.0;
	AngleToString(m_ptSphericalPos.y,strValue);
	m_editLightLongitude.SetWindowText( strValue );
	AngleToString(m_ptSphericalPos.z,strValue);
	m_editLightLatitude.SetWindowText( strValue );

	UpdateData( FALSE );
}

bool CToolWorldLightDlg::GetLight( CNdlLightRes* lightRes )
{
	UpdateData();

	CString strValue;
	m_editName.GetWindowText( strValue );
	if( strValue.GetLength() >= (RES_NAME_LEN>>1) )
		return false;
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return false;
	}
	char strName[RES_NAME_LEN];
	if( strValue.GetLength() > 0 ) {
		SwPublicFunc::TChar2MutiChar( strName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
		lightRes->SetName( strName );
	}
	else {
		sprintf_s( strName, "没有名字_%d", resMgr->GetLightList().size() );
		lightRes->SetName( strName );		
	}
	for( sInt32 i=0; i<resMgr->GetLightList().size(); i++ ) {
		CNdlLightRes* p = (CNdlLightRes*)(resMgr->GetLightList()[i]);
		if( 0 == strcmp( p->GetName(), strName ) ) {
			AfxMessageBox( _T("已经有相同名字!") );
			return false;
		}
	}

	lightRes->m_lightAmbient	= m_colorAmbientLight;
	lightRes->m_lightDiffuse	= m_colorDiffuseLight;
	lightRes->m_lightSpecular	= m_colorSpecularLight;
	lightRes->m_colorSunless	= m_colorSunless;

	m_editLightLongitude.GetWindowText( strValue );
	m_ptSphericalPos.y		= StringToAngle(strValue);
	m_editLightLatitude.GetWindowText( strValue );
	m_ptSphericalPos.z		= StringToAngle( strValue );

	lightRes->m_lightDir = SwPublicFunc::Spherical2Cartesian(m_ptSphericalPos);
	lightRes->m_lightDir.normalize();
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);

	return true;
}


void CToolWorldLightDlg::OnClickAddBtn()
{
	UpdateData();

	CString strValue;
	m_editName.GetWindowText( strValue );
	if( strValue.GetLength() >= (RES_NAME_LEN>>1) )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	char strName[RES_NAME_LEN];
	if( strValue.GetLength() > 0 ) {
		SwPublicFunc::TChar2MutiChar( strName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		sprintf_s( strName, "没有名字_%d", resMgr->GetLightList().size() );
	}

	for( sInt32 i=0; i<resMgr->GetLightList().size(); i++ ) {
		CNdlLightRes* p = (CNdlLightRes*)(resMgr->GetLightList()[i]);
		if( 0 == strcmp( p->GetName(), strName ) ) {
			AfxMessageBox( _T("已经有相同名字!") );
			return;
		}
	}

	CNdlLightRes *lightRes = MeNew CNdlLightRes();
	if (!GetLight(lightRes))
	{
		SAFE_DELETE( lightRes );
		return;
	}
	lightRes->SetId(resMgr->GetLightList().size());

	if (mLightsLB.GetCurSel() != -1)
	{
		CNdlLightRes *curSelLightRes = resMgr->GetLightRes(m_curSel);
		if (curSelLightRes != NULL)
		{
			// 如果当前有选中某个灯光, 则克隆灯光数据
			lightRes->m_lightAmbient = curSelLightRes->m_lightAmbient;
			lightRes->m_lightDiffuse = curSelLightRes->m_lightDiffuse;
			lightRes->m_lightSpecular = curSelLightRes->m_lightSpecular;
			lightRes->m_colorSunless = curSelLightRes->m_colorSunless;
			lightRes->m_lightDir = curSelLightRes->m_lightDir;
		}
	}
	resMgr->GetLightList().push_back(lightRes);

	mLightsLB.SetCurSel(resMgr->GetLightList().size() - 1);
	m_curSel = mLightsLB.GetCurSel();

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);

	UpdateLightsLB();
	UpdateData(FALSE);
}

void CToolWorldLightDlg::OnClickDelBtn()
{
	if( -1 == m_curSel )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	if( m_curSel >= resMgr->GetLightList().size() )
		return;

	CString strPmt;
	strPmt.Format( _T("是否删除？") );
	int sel = ::AfxMessageBox( strPmt, MB_YESNO );
	if( sel == IDYES ) 
	{
		resMgr->DeleteLightRes(m_curSel);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
		UpdateLightsLB();
		UpdateData( FALSE );
		Reset();

		if (m_curSel != 0)
			--m_curSel;
		else
			m_curSel = -1;
		mLightsLB.SetCurSel(m_curSel);
	}
}

void CToolWorldLightDlg::UpdateLightsLB()
{
	mLightsLB.ResetContent();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	
	for (int i = 0; i < resMgr->GetLightList().size(); ++i)
	{
		CWorldRes *p = resMgr->GetLightList()[i];
		mLightsLB.AddString(p->GetName());
	}
}


void CToolWorldLightDlg::UpdateDirLight( const Vector& kSphericalDelta )
{
	CString strValue;
	m_ptSphericalPos += kSphericalDelta;

	m_ptSphericalPos.x = 1.0;
	AngleToString(m_ptSphericalPos.y,strValue);
	m_editLightLongitude.SetWindowText( strValue );

	short nPos = atoi(strValue.GetString());
	nPos %= 360;
	m_spinLongitude.SetPos(nPos);

	AngleToString(m_ptSphericalPos.z,strValue);
	m_editLightLatitude.SetWindowText( strValue );

	nPos = atoi(strValue.GetString());
	nPos %= 360;
	m_spinLatitude.SetPos(nPos);

	RefreshLight();

	UpdateData( FALSE );
}

void CToolWorldLightDlg::Reset()
{
	m_editName.SetWindowText( _T("") );

	m_colorAmbientLight		= RGB(0x0, 0x0, 0x0);
	m_colorDiffuseLight		= RGB(0x33,0x33,0x33);
	m_colorSpecularLight	= RGB(0x33,0x33,0x33);
	m_colorSunless			= RGB(0xbb,0xbb,0xbb);


	m_cpAmbientLight.SetColor(m_colorAmbientLight);
	m_cpDiffuseLight.SetColor(m_colorDiffuseLight);
	m_cpSpecularLight.SetColor(m_colorSpecularLight);
	m_cpSunlessColor.SetColor(m_colorSunless);


	m_editLightLongitude.SetWindowText( _T("0") );
	m_editLightLatitude.SetWindowText( _T("10") );

	m_curSel = -1;
}

CToolLight* CToolWorldLightDlg::GetLightTool() const
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	CToolLight* toolLight = (CToolLight*)( toolManager->GetActiveTool() );
	Assert( NULL != toolLight );
	return toolLight;
}

void CToolWorldLightDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if (nSBCode==SB_THUMBPOSITION) 
	{
		if(pScrollBar->GetDlgCtrlID()==IDC_SPIN_LONGITUDE) 
		{
			UpdateData();
			CString strLongitude;
			strLongitude.Format( _T("%d"), nPos );
			m_editLightLongitude.SetWindowText( strLongitude );
			OnKillfocusLightLongitude();

			UpdateData( FALSE );
		}
		else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_LATITUDE)
		{
			UpdateData();
			CString strLatitude;
			strLatitude.Format( _T("%d"), nPos );
			m_editLightLatitude.SetWindowText( strLatitude );			
			OnKillfocusLightLatitude();


			UpdateData( FALSE );
		}
	}
	CDialog::OnVScroll( nSBCode, nPos, pScrollBar );

}

float CToolWorldLightDlg::StringToAngle( CString& sAngle )
{
	int nAngle = atoi(sAngle.GetString());
	nAngle %= 360;
	return	 nAngle * PI/ 180;
}

void CToolWorldLightDlg::AngleToString(float angle, CString& sAngle )
{
	int nAngle = angle*180/PI;
	nAngle %= 360;
	if (nAngle < 0)
	{
		nAngle+= 360;
	}
	sAngle.Format(_T("%d"),nAngle);

}


void CToolWorldLightDlg::RefreshLight()
{
	Vector lightDir = SwPublicFunc::Spherical2Cartesian(m_ptSphericalPos);
	lightDir.normalize();
	theApp.SetLightDir( lightDir );

	CToolLight*	toolLight =		GetLightTool();
	toolLight->SetLightDir(lightDir);
}

void CToolWorldLightDlg::OnBnClickedBtnLightModify()
{
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (resMgr == NULL)
		return;
	if (m_curSel == -1 || m_curSel >= resMgr->GetLightList().size())
		return;

	// 更新灯光名字
	CString strValue;
	m_editName.GetWindowText(strValue);
	mLightsLB.LockWindowUpdate();
	mLightsLB.DeleteString(m_curSel);
	mLightsLB.InsertString(m_curSel, strValue);
	mLightsLB.UnlockWindowUpdate();
	mLightsLB.SetCurSel(m_curSel);

	// 保存灯光参数
	CNdlLightRes *lightRes = (CNdlLightRes *) (resMgr->GetLightList()[m_curSel]);
	lightRes->SetName(strValue);
	lightRes->m_lightAmbient	= m_colorAmbientLight;
	lightRes->m_lightDiffuse	= m_colorDiffuseLight;
	lightRes->m_lightSpecular	= m_colorSpecularLight;
	lightRes->m_colorSunless	= m_colorSunless;

	m_editLightLongitude.GetWindowText( strValue );
	m_ptSphericalPos.y		= StringToAngle(strValue);
	m_editLightLatitude.GetWindowText( strValue );
	m_ptSphericalPos.z		= StringToAngle( strValue );

	// 保存灯光方向
	lightRes->m_lightDir = SwPublicFunc::Spherical2Cartesian(m_ptSphericalPos);
	lightRes->m_lightDir.normalize();

	// 设置Tile的Dirty标记
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
}

void CToolWorldLightDlg::OnBnClickedRadioAmbient()
{
	updateHSL();
}	

void CToolWorldLightDlg::OnBnClickedRadioDiffuse()
{
	updateHSL();
}

void CToolWorldLightDlg::OnBnClickedRadioSpecular()
{
	updateHSL();
}

void CToolWorldLightDlg::OnBnClickedRadioSunless()
{
	updateHSL();
}

void CToolWorldLightDlg::updateHSL()
{
	int i1 = IsDlgButtonChecked(IDC_RADIO_AMBIENT);
	int i2 = IsDlgButtonChecked(IDC_RADIO_DIFFUSE);
	int i3 = IsDlgButtonChecked(IDC_RADIO_SPECULAR);
	int i4 = IsDlgButtonChecked(IDC_RADIO_SUNLESS);

	NiColor color;

	if(i1)
	{
		ConvertRGB2NiColor( m_colorAmbientLight, color );
	}
	else if(i2)
	{
		ConvertRGB2NiColor( m_colorDiffuseLight, color );
	}
	else if(i3)
	{
		ConvertRGB2NiColor( m_colorSpecularLight, color );
	}
	else if(i4)
	{
		ConvertRGB2NiColor( m_colorSunless, color );
	}

	color = RGBToHSL(color);

	m_sliderH.SetPos(color.r);
	m_sliderS.SetPos(color.g);
	m_sliderL.SetPos(color.b);
}

void CToolWorldLightDlg::setHSL()
{
	int h = m_sliderH.GetPos();
	int s = m_sliderS.GetPos();
	int l = m_sliderL.GetPos();

	int i1 = IsDlgButtonChecked(IDC_RADIO_AMBIENT);
	int i2 = IsDlgButtonChecked(IDC_RADIO_DIFFUSE);
	int i3 = IsDlgButtonChecked(IDC_RADIO_SPECULAR);
	int i4 = IsDlgButtonChecked(IDC_RADIO_SUNLESS);

	NiColor color;

	color.r = h;
	color.g = s;
	color.b = l;

	color = HSLToRGB(color);

	if(i1)
	{
		m_colorAmbientLight	= RGB(color.r,color.g,color.b);
		m_cpAmbientLight.SetColor( m_colorAmbientLight );
		theApp.SetLightAmbientColor( color/255.0 );

	}
	else if(i2)
	{
		m_colorDiffuseLight = RGB(color.r,color.g,color.b);
		m_cpDiffuseLight.SetColor( m_colorDiffuseLight );
		theApp.SetLightDiffuseColor( color/255.0 );
	}
	else if(i3)
	{
		m_colorSpecularLight = RGB(color.r,color.g,color.b);
		m_cpSpecularLight.SetColor( m_colorSpecularLight );
		theApp.SetLightSpecularColor( color/255.0 );
	}
	else if(i4)
	{
		m_colorSunless = RGB(color.r,color.g,color.b);
		m_cpSunlessColor.SetColor( m_colorSunless );
		theApp.SetSunLessColor( color/255.0 );
	}


	//LineTo();
	//SetActive(true);
}

void CToolWorldLightDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_COLOR_H ) )
	{
		OnNMReleaseSliderColorH( NULL, NULL );
	}
	else if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_COLOR_S ) )
	{
		OnNMReleaseSliderColorS( NULL, NULL );
	}
	else if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_COLOR_L ) )
	{
		OnNMReleaseSliderColorL( NULL, NULL );
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CToolWorldLightDlg::OnNMReleaseSliderColorH(NMHDR *pNMHDR, LRESULT *pResult)
{
	setHSL();
}

void CToolWorldLightDlg::OnNMReleaseSliderColorS(NMHDR *pNMHDR, LRESULT *pResult)
{
	setHSL();
}

void CToolWorldLightDlg::OnNMReleaseSliderColorL(NMHDR *pNMHDR, LRESULT *pResult)
{
	setHSL();
}

NiColor CToolWorldLightDlg::RGBToHSL(NiColor color)
{
	float hue,sat,lum;

	float maxVal = max(max(color.r,color.g),color.b);
	float minVal = min(min(color.r,color.g),color.b);

	float del_max = maxVal - minVal;

	lum = (maxVal+minVal)/2.0f;

	if(del_max == 0)
	{
		hue = 0;
		sat = 0;
	}
	else
	{
		if(lum<0.5f) sat = del_max/(maxVal+minVal);
		else sat = del_max/(2.0f - maxVal - minVal);

		float del_R = (((maxVal - color.r)/6.0f) + (del_max/2.0f))/del_max;
		float del_G = (((maxVal - color.g)/6.0f) + (del_max/2.0f))/del_max;
		float del_B = (((maxVal - color.b)/6.0f) + (del_max/2.0f))/del_max;

		if(color.r == maxVal) hue = del_B-del_G;
		else if(color.g == maxVal) hue = (1.0f/3.0f) + del_R - del_B;
		else if(color.b == maxVal) hue = (2.0f/3.0f) + del_G - del_B;

		if( hue < 0 ) hue += 1;
		if( hue > 1 ) hue -= 1;
	}

	NiColor colorhsl;

	colorhsl.r = hue*255.0f;
	colorhsl.g = sat*255.0f;
	colorhsl.b = lum*255.0f;

	return colorhsl;

	/*if( maxVal == minVal )
	{
	hue = 0;
	}
	else if( maxVal == color.r && color.g>=color.b )
	{
	hue = 60.0f*(color.g-color.b)/(maxVal-minVal);
	}
	else if( maxVal == color.r && color.g<color.b )
	{
	hue = 60.0f*(color.g-color.b)/(maxVal-minVal)+360;
	}
	else if( maxVal == color.g )
	{
	hue = 60.0f*(color.b-color.r)/(maxVal-minVal)+120;
	}
	else if( maxVal == color.b )
	{
	hue = 60.0f*(color.b-color.r)/(maxVal-minVal)+240;
	}

	lum = (maxVal+minVal)/2.0f;

	if( (lum==0||maxVal==minVal) )
	{
	sat = 0;
	}
	else if( 0<lum && lum <=0.5f )
	{
	sat = (maxVal-minVal)/(maxVal+minVal);
	}
	else if( lum>0.5f )
	{
	sat = (maxVal-minVal)/(2-(maxVal+minVal));
	}

	hue = ((hue>360)?360:((hue<0)?0:hue))/360.0f*255.0f;
	sat = ((sat>1)?1:((sat<0)?0:sat))*255;
	lum = ((lum>1)?1:((lum<0)?0:lum))*255;

	NiColor colorhsl;

	colorhsl.r = hue;
	colorhsl.g = sat;
	colorhsl.b = lum;

	return colorhsl;*/
}

NiColor CToolWorldLightDlg::HSLToRGB(NiColor color)
{
	float hue,sat,lum;
	float r,g,b;
	float var_1,var_2;

	hue = color.r/255.0f;
	sat = color.g/255.0f;
	lum = color.b/255.0f;

	if(lum<0.5) var_2 = lum*(1+sat);
	else var_2 = (lum + sat)-(sat*lum);

	var_1 = 2.0*lum - var_2;

	r = 255*Hue2RGB(var_1,var_2,hue+(1.0f/3.0f));
	g = 255*Hue2RGB(var_1,var_2,hue);
	b = 255*Hue2RGB(var_1,var_2,hue-(1.0f/3.0f));

	NiColor colorRGB;

	colorRGB.r = r;
	colorRGB.g = g;
	colorRGB.b = b;

	return colorRGB;

	/*if( sat == 0 )
	{
	r=g=b=lum*255.0f;
	}
	else
	{
	float q = (lum<0.5f)?(lum*(1.0f+sat)):(lum+sat-lum*sat);
	float p = (2.0f*lum)-q;

	float HK = hue/255.0f;
	float T[3];

	T[0] = HK+0.33333333f;
	T[1] = HK;
	T[2] = HK-0.33333333f;//0.66666666

	for(int i=0;i<3; ++i)
	{
	if(T[i]<0)
	T[i]+=1.0f;
	if(T[i]>1)
	T[i]-=1.0f;

	if(T[i]*6<1)
	T[i]=p+((q-p)*6.0f+T[i]);
	else if((T[i]*2.0f)<1)
	T[i]=q;
	else if((T[i]+3.0f)<2.0f)
	T[i]=p+(q-p)*((2.0/3.0f)-T[i])*6.0f;
	else
	T[i]=p;
	}

	r = T[0]*255;
	g = T[1]*255;
	b = T[2]*255;
	}

	r = (r>255)?255:((r<0)?0:r);
	g = (g>255)?255:((g<0)?0:g);
	b = (b>255)?255:((b<0)?0:b);

	NiColor colorRGB;

	colorRGB.r = r;
	colorRGB.g = g;
	colorRGB.b = b;

	return colorRGB;*/
}
void CToolWorldLightDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}
