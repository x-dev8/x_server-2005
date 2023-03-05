/*******************************************************************************
* Copyright ShenWang 2011 - All Rights Reserved
* 
* File: 	ToolStaticLightDlg.cpp
* Create: 	02/21/2011
* Desc:		静态光源控制面板
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "ToolStaticLightDlg.h"
#include "Edit/ToolManager.h"
#include "Edit/ToolStaticLight.h"
#include "MeTerrain/Lighting/LightRes.h"

IMPLEMENT_DYNAMIC(CToolStaticLightDlg, CDialog)

#define LIST_LIGHTNAME "Light%d"

extern float Hue2RGB(float v1,float v2,float vH);

CToolStaticLightDlg::CToolStaticLightDlg( CToolStaticLightDlg* pParent /*= NULL*/ )
: CDialog(CToolStaticLightDlg::IDD, pParent)
, m_nLastLightNo(0)
, m_nSelectedNum(0)
{
	m_vecLightRef.clear();
}

CToolStaticLightDlg::~CToolStaticLightDlg()
{
}

void CToolStaticLightDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATIC_LIGHT, m_listStaticLights);

	DDX_Control(pDX, IDC_EDIT_SL_WORLD_X, m_editWorldPosX);
	DDX_Control(pDX, IDC_EDIT_SL_WORLD_Y, m_editWorldPosY);
	DDX_Control(pDX, IDC_EDIT_SL_WORLD_Z, m_editWorldPosZ);
	DDX_Control(pDX, IDC_EDIT_SL_DISTANCE, m_editDistance);
	DDX_Control(pDX, IDC_EDIT_SL_NEARDIST, m_editNearDistance);

	DDX_Control(pDX, IDC_SPIN_SL_WORLD_X, m_spinWorldPosX);
	DDX_Control(pDX, IDC_SPIN_SL_WORLD_Y, m_spinWorldPosY);
	DDX_Control(pDX, IDC_SPIN_SL_WORLD_Z, m_spinWorldPosZ);
	DDX_Control(pDX, IDC_SPIN_SL_DISTANCE, m_spinDistance);
	DDX_Control(pDX, IDC_SPIN_SL_NEARDIST, m_spinNearDistance);

	DDX_Control(pDX, IDC_BTN_SL_COLOR, m_cpLightColor);
	DDX_XTColorPicker(pDX, IDC_BTN_SL_COLOR, m_colorLightColor);
	DDX_Control(pDX, IDC_SLIDER_SL_H, m_sliderH);
	DDX_Control(pDX, IDC_SLIDER_SL_S, m_sliderS);
	DDX_Control(pDX, IDC_SLIDER_SL_L, m_sliderL);

	DDX_Control(pDX, IDC_BUTTON_SL_DELETE, m_btnRemoveLight);
	DDX_Control(pDX, IDC_BUTTON_MOVETO_LIGHT, m_btnMoveToLight);
}
BEGIN_MESSAGE_MAP(CToolStaticLightDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_SL_WORLD_X, OnEnKillfocusEditSLWorldX)
	ON_EN_KILLFOCUS(IDC_EDIT_SL_WORLD_Y, OnEnKillfocusEditSLWorldY)
	ON_EN_KILLFOCUS(IDC_EDIT_SL_WORLD_Z, OnEnKillfocusEditSLWorldZ)
	ON_EN_KILLFOCUS(IDC_EDIT_SL_DISTANCE, OnEnKillfocusEditSLDistance)
	ON_EN_KILLFOCUS(IDC_EDIT_SL_NEARDIST, OnEnKillfocusEditSLNearDist)
	ON_LBN_SELCHANGE(IDC_LIST_STATIC_LIGHT, OnLbnSelchangeListStaticLight)
	ON_CPN_XT_SELENDOK(IDC_BTN_SL_COLOR, OnSelEndOkLightColor)
	ON_BN_CLICKED(IDC_BUTTON_SL_DELETE, OnBnClickedDeleteLight)
	ON_BN_CLICKED(IDC_BUTTON_MOVETO_LIGHT, OnBnClickedMoveToLight)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CToolStaticLightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_spinWorldPosX.SetBuddy( &m_editWorldPosX );
	m_spinWorldPosX.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinWorldPosX.SetPos( 0 );
	m_spinWorldPosY.SetBuddy( &m_editWorldPosY );
	m_spinWorldPosY.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinWorldPosY.SetPos( 0 );
	m_spinWorldPosZ.SetBuddy( &m_editWorldPosZ );
	m_spinWorldPosZ.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinWorldPosZ.SetPos( 0 );
	m_spinDistance.SetBuddy( &m_editDistance );
	m_spinDistance.SetRange32( 0, 0xfffffff);  
	m_spinDistance.SetPos( 0 );
	m_spinNearDistance.SetBuddy( &m_editNearDistance );
	m_spinNearDistance.SetRange32( 0, 0xfffffff);  
	m_spinNearDistance.SetPos( 0 );
	m_sliderH.SetRange(0,255);
	m_sliderS.SetRange(0,255);
	m_sliderL.SetRange(0,255);

	m_colorLightColor = RGB(0xaa,0xaa,0xaa);
	m_cpLightColor.SetColor(m_colorLightColor);
	m_cpLightColor.SetDefaultColor( RGB(0xaa,0xaa,0xaa) );
	m_cpLightColor.ShowText(true);

	m_listStaticLights.ResetContent();
	EnableControls(FALSE);

	return TRUE;
}

void CToolStaticLightDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( nSBCode==SB_THUMBPOSITION )
	{
		switch( pScrollBar->GetDlgCtrlID() )
		{
		case IDC_SPIN_SL_WORLD_X:
			UpdateWorldPosX();
			break;
		case IDC_SPIN_SL_WORLD_Y:
			UpdateWorldPosY();
			break;
		case IDC_SPIN_SL_WORLD_Z:
			UpdateWorldPosZ();
			break;
		case IDC_SPIN_SL_DISTANCE:
			UpdateDistance();
			break;
		case IDC_SPIN_SL_NEARDIST:
			UpdateNearDist();
			break;
		default:
			break;
		}
	}
	CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}

void CToolStaticLightDlg::SetActive( bool isModify /*= false */ )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_STATICLIGHT );
	CToolStaticLight* toolStaticLight = (CToolStaticLight*)( toolManager->GetActiveTool() );

	assert( NULL != toolStaticLight );
	toolStaticLight->Bind( this );
	toolStaticLight->Reset();

	InitData();	// 填充灯光列表
}

void CToolStaticLightDlg::InitData()
{
	m_listStaticLights.ResetContent();
	m_nLastLightNo = 0;
	m_vecLightRef.clear();
	m_nSelectedNum = 0;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( !pToolStaticLight )
		return;

	CString strName;
	if( StaticLightsContainer::GetInstance()->GetStaticLights().size() )
	{
		const std::map<unsigned short, LightRes*>& mapStaticLights = StaticLightsContainer::GetInstance()->GetStaticLights();
		std::map<unsigned short, LightRes*>::const_iterator iter = mapStaticLights.begin();
		int light=0;
		for( ; iter != mapStaticLights.end(); ++iter, ++light )
		{
			if( !iter->second )
				continue;

			LightRes* pLightRes = iter->second;
			if( pLightRes->GetType() == LightRes::LT_POINTLIGHT )
			{
				PointLight* pLight = (PointLight*)iter->second;

				strName.Format(LIST_LIGHTNAME, light+1);
				m_listStaticLights.AddString(strName);
				m_vecLightRef.push_back(iter->first);

				// 创建光源模型
				pToolStaticLight->PushLightModel(pLight->GetDist(), pLight->GetPos(), pLight->GetColor());
			}
			else if( pLightRes->GetType() == LightRes::LT_DIRECTIONLIGHT )
			{
				DirectionLight* pDirLight = (DirectionLight*)pLightRes;
				if( pDirLight->IsChunkLight() )
					continue;

				// TODO: 创建方向光......
			}
			else
			{
				continue;
			}
		}
		m_nLastLightNo = light;
	}
	strName.Format("新建");
	int sel = m_listStaticLights.AddString(strName);
	EnableControls(FALSE);
	pToolStaticLight->SetOptMode(CToolStaticLight::optMode_Pick);
}

void CToolStaticLightDlg::OnEnKillfocusEditSLWorldX()
{
	UpdateWorldPosX();
}

void CToolStaticLightDlg::OnEnKillfocusEditSLWorldY()
{
	UpdateWorldPosY();
}

void CToolStaticLightDlg::OnEnKillfocusEditSLWorldZ()
{
	UpdateWorldPosZ();
}

void CToolStaticLightDlg::OnEnKillfocusEditSLDistance()
{
	UpdateDistance();
}

void CToolStaticLightDlg::OnEnKillfocusEditSLNearDist()
{
	UpdateNearDist();
}

bool CToolStaticLightDlg::UpdateWorldPosX()
{
	if( m_nSelectedNum < 0 || m_nSelectedNum > 1 )
		return false;

	UpdateData();

	CString strValue;
	m_editWorldPosX.GetWindowText(strValue);
	float x = _tstof( strValue );

	int index = -1;
	LightRes* pLightRes = GetLightResFromCurSel(index);
	if( pLightRes )
	{
		PointLight* pLight = (PointLight*)pLightRes;
		pLight->SetPosX(x);

		CToolStaticLight* toolStaticLight = GetTool();
		if( toolStaticLight )
		{
			toolStaticLight->UpdatePosX(index, x);
		}
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	}
	else
		return false;

	return true;
}

bool CToolStaticLightDlg::UpdateWorldPosY()
{
	if( m_nSelectedNum < 0 || m_nSelectedNum > 1 )
		return false;

	UpdateData();

	CString strValue;
	m_editWorldPosY.GetWindowText(strValue);
	float y = _tstof( strValue );

	int index = -1;
	LightRes* pLightRes = GetLightResFromCurSel(index);
	if( pLightRes )
	{
		PointLight* pLight = (PointLight*)pLightRes;
		pLight->SetPosY(y);

		CToolStaticLight* toolStaticLight = GetTool();
		if( toolStaticLight )
		{
			toolStaticLight->UpdatePosY(index, y);
		}
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	}
	else
		return false;

	return true;
}

bool CToolStaticLightDlg::UpdateWorldPosZ()
{
	if( m_nSelectedNum < 0 || m_nSelectedNum > 1 )
		return false;

	UpdateData();

	CString strValue;
	m_editWorldPosZ.GetWindowText(strValue);
	float z = _tstof( strValue );

	int index = -1;
	LightRes* pLightRes = GetLightResFromCurSel(index);
	if( pLightRes )
	{
		PointLight* pLight = (PointLight*)pLightRes;
		pLight->SetPosZ(z);

		CToolStaticLight* toolStaticLight = GetTool();
		if( toolStaticLight )
		{
			toolStaticLight->UpdatePosZ(index, z);
		}
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	}
	else
		return false;

	return true;
}

bool CToolStaticLightDlg::UpdateDistance()
{
	UpdateData();

	CString strValue;
	m_editDistance.GetWindowText(strValue);
	float v = _tstof( strValue );

	std::vector<int> vecSelect;
	if( !GetSelectedList(vecSelect) )
		return false;

	for( int i=0; i<vecSelect.size(); ++i )
	{
		LightRes* pLightRes = GetLightRes(vecSelect[i]);
		if( pLightRes )
		{
			PointLight* pLight = (PointLight*)pLightRes;
			if( v <= 0 )
			{
				v = pLight->GetDist();
				m_spinDistance.SetPos( ZnFloat2Int(v) );
				strValue.Format(_T("%.3f"), v);
				m_editDistance.SetWindowText(strValue);
			}
			else
			{
				pLight->SetDist(v);

				CToolStaticLight* toolStaticLight = GetTool();
				if( toolStaticLight )
				{
					toolStaticLight->UpdateDistance(vecSelect[i], v);
				}

				// 检查NearDist
				if( pLight->GetNearDist() > v )
				{
					pLight->SetNearDist(v);
					m_spinNearDistance.SetPos( ZnFloat2Int(v) );
					strValue.Format(_T("%.3f"), v);
					m_editNearDistance.SetWindowText(strValue);
				}
			}
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	return true;
}

bool CToolStaticLightDlg::UpdateNearDist()
{
	UpdateData();

	CString strValue;
	m_editNearDistance.GetWindowText(strValue);
	float v = _tstof( strValue );

	std::vector<int> vecSelect;
	if( !GetSelectedList(vecSelect) )
		return false;

	for( int i=0; i<vecSelect.size(); ++i )
	{
		LightRes* pLightRes = GetLightRes(vecSelect[i]);
		if( pLightRes )
		{
			PointLight* pLight = (PointLight*)pLightRes;
			if( v <= 0 )
			{
				v = pLight->GetNearDist();
				m_spinNearDistance.SetPos( ZnFloat2Int(v) );
				strValue.Format(_T("%.3f"), v);
				m_editNearDistance.SetWindowText(strValue);
			}
			else
			{
				// 不能超过光照距离
				if( v > pLight->GetDist() )
				{
					v = pLight->GetDist();
					m_spinNearDistance.SetPos( ZnFloat2Int(v) );
					strValue.Format(_T("%.3f"), v);
					m_editNearDistance.SetWindowText(strValue);
				}
				pLight->SetNearDist(v);
			}
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	return true;
}

void CToolStaticLightDlg::OnLbnSelchangeListStaticLight()
{
	int count = m_listStaticLights.GetCount();
	if( count <= 0 )
		return;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( !pToolStaticLight )
		return;

	if( m_listStaticLights.GetSel(count-1) > 0 )	// 选中“新建”
	{
		CancelSelect();
		m_listStaticLights.SetSel(count-1, TRUE);
		pToolStaticLight->SetOptMode(CToolStaticLight::optMode_PutLight);
	}
	else	// 灯光
	{
		pToolStaticLight->SetOptMode(CToolStaticLight::optMode_Pick);
		pToolStaticLight->UnSelectAll();
		for( int i=0; i<count-1; ++i )	// 最后一个不判断
		{
			bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
			if( bSeletcted )
			{
				pToolStaticLight->DoSelect(i);
			}
		}
		UpdateProperties();
	}
}

bool CToolStaticLightDlg::AddLight( const Vector& pos )
{
	NiColorB color(0xaa, 0xaa, 0xaa);	// 默认灰色光
	float fNearDist = 0.f;
	float fDist = 1.f;
	PointLight* pLight = MeNew PointLight(fNearDist, fDist, pos, color);
	if( !pLight )
		return false;

	unsigned short getId = 0;
	if( StaticLightsContainer::GetInstance()->InsertLight(pLight, getId) )
	{
		// 添加到列表
		char szName[32] = {0};
		CString strName;
		int light = ++m_nLastLightNo;
		assert( light > 0 );	// 默认会添加“新建”进去
		strName.Format(LIST_LIGHTNAME, light);
		int cursel = m_listStaticLights.InsertString(m_listStaticLights.GetCount()-1, strName);	// 插到“新建”之前
		m_vecLightRef.push_back(getId);

		CToolStaticLight* pToolStaticLight = GetTool();
		if( pToolStaticLight )
		{
			pToolStaticLight->PushLightModel(fDist, pos, color);
		}
		// 选中
		UnSelectAll();
		SelectOneLight(cursel, FALSE);
		UpdateProperty(fNearDist, fDist, pos, color);
		EnableControls();
		return true;
	}
	else
	{
		delete pLight;
		pLight = NULL;
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );

	return false;
}

bool CToolStaticLightDlg::UpdatePropertyByIndex(int index, BOOL bUpdatePos)
{
	if( index < 0 || index >= m_vecLightRef.size() )
		return false;

	LightRes* pLightRes = GetLightRes(index);
	if( pLightRes )
	{
		PointLight* pLight = (PointLight*)pLightRes;
		CString strText;

		if( bUpdatePos )
		{
			m_spinWorldPosX.SetPos( ZnFloat2Int( pLight->GetPos().x ) );
			strText.Format(_T("%.3f"), pLight->GetPos().x);
			m_editWorldPosX.SetWindowText(strText);

			m_spinWorldPosY.SetPos( ZnFloat2Int( pLight->GetPos().y ) );
			strText.Format(_T("%.3f"), pLight->GetPos().y);
			m_editWorldPosY.SetWindowText(strText);

			m_spinWorldPosZ.SetPos( ZnFloat2Int( pLight->GetPos().z ) );
			strText.Format(_T("%.3f"), pLight->GetPos().z);
			m_editWorldPosZ.SetWindowText(strText);
		}

		m_spinNearDistance.SetPos( ZnFloat2Int( pLight->GetNearDist() ) );
		strText.Format(_T("%.3f"), pLight->GetNearDist());
		m_editNearDistance.SetWindowText(strText);

		m_spinDistance.SetPos( ZnFloat2Int( pLight->GetDist() ) );
		strText.Format(_T("%.3f"), pLight->GetDist());
		m_editDistance.SetWindowText(strText);

		// 颜色
		const NiColorB& color = pLight->GetColor();
		m_colorLightColor = RGB(color.r,color.g,color.b);
		updateHSL();

		UpdateData(FALSE);

		return true;
	}
	return false;
}

bool CToolStaticLightDlg::UpdateProperty( float fNearDist, float fDist, const Vector& pos, const NiColorB& color )
{
	CString strText;
	m_spinWorldPosX.SetPos( ZnFloat2Int( pos.x ) );
	strText.Format(_T("%.3f"), pos.x);
	m_editWorldPosX.SetWindowText(strText);

	m_spinWorldPosY.SetPos( ZnFloat2Int( pos.y ) );
	strText.Format(_T("%.3f"), pos.y);
	m_editWorldPosY.SetWindowText(strText);

	m_spinWorldPosZ.SetPos( ZnFloat2Int( pos.z ) );
	strText.Format(_T("%.3f"), pos.z);
	m_editWorldPosZ.SetWindowText(strText);

	m_spinNearDistance.SetPos( ZnFloat2Int( fNearDist ) );
	strText.Format(_T("%.3f"), fNearDist);
	m_editNearDistance.SetWindowText(strText);

	m_spinDistance.SetPos( ZnFloat2Int( fDist ) );
	strText.Format(_T("%.3f"), fDist);
	m_editDistance.SetWindowText(strText);

	// 颜色
	m_colorLightColor = RGB(color.r,color.g,color.b);
	updateHSL();

	UpdateData(FALSE);

	return true;
}

bool CToolStaticLightDlg::UpdateProperties()
{
	// 统计选中几个
	CalSelectNum();
	int count = m_listStaticLights.GetCount();
	int iFirstSel = -1;
	for( int i=0; i<count-1; ++i )	// 最后一个“新建”不判断
	{
		bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
		if( bSeletcted )
		{
			if( iFirstSel == -1 )
				iFirstSel = i;
		}
	}
	if( m_nSelectedNum <= 0 || iFirstSel < 0 )	// 未选中
	{
		EnableControls(FALSE);
	}
	if( m_nSelectedNum == 1 )	// 单选
	{
		UpdatePropertyByIndex(iFirstSel, TRUE);
		EnableControls(TRUE);
	}
	else						// 多选
	{
		UpdatePropertyByIndex(iFirstSel, FALSE);
		EnableControls(TRUE);
	}
	return true;
}

void CToolStaticLightDlg::EnableControls( BOOL bEnable /*= TRUE*/ )
{
	if( m_nSelectedNum > 1 && bEnable )	// 多选
	{
		m_editWorldPosX.EnableWindow(FALSE);
		m_editWorldPosY.EnableWindow(FALSE);
		m_editWorldPosZ.EnableWindow(FALSE);
		m_spinWorldPosX.EnableWindow(FALSE);
		m_spinWorldPosY.EnableWindow(FALSE);
		m_spinWorldPosZ.EnableWindow(FALSE);

		m_editDistance.EnableWindow(bEnable);
		m_spinDistance.EnableWindow(bEnable);
		m_editNearDistance.EnableWindow(bEnable);
		m_spinNearDistance.EnableWindow(bEnable);

		m_cpLightColor.EnableWindow(bEnable);
		m_sliderH.EnableWindow(bEnable);
		m_sliderS.EnableWindow(bEnable);
		m_sliderL.EnableWindow(bEnable);

		m_btnRemoveLight.EnableWindow(FALSE);
		m_btnMoveToLight.EnableWindow(bEnable);
	}
	else
	{
		m_editWorldPosX.EnableWindow(bEnable);
		m_editWorldPosY.EnableWindow(bEnable);
		m_editWorldPosZ.EnableWindow(bEnable);
		m_spinWorldPosX.EnableWindow(bEnable);
		m_spinWorldPosY.EnableWindow(bEnable);
		m_spinWorldPosZ.EnableWindow(bEnable);

		m_editDistance.EnableWindow(bEnable);
		m_spinDistance.EnableWindow(bEnable);
		m_editNearDistance.EnableWindow(bEnable);
		m_spinNearDistance.EnableWindow(bEnable);

		m_cpLightColor.EnableWindow(bEnable);
		m_sliderH.EnableWindow(bEnable);
		m_sliderS.EnableWindow(bEnable);
		m_sliderL.EnableWindow(bEnable);

		m_btnRemoveLight.EnableWindow(bEnable);
		m_btnMoveToLight.EnableWindow(bEnable);
	}
}

CToolStaticLight* CToolStaticLightDlg::GetTool()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	if( toolManager->GetActiveTool() )
		return (CToolStaticLight*)toolManager->GetActiveTool();

	return NULL;
}

LightRes* CToolStaticLightDlg::GetLightRes(int index)
{
	if( index < 0 || index >= m_vecLightRef.size() )
		return NULL;

	int key = m_vecLightRef[index];
	const std::map<unsigned short, LightRes*>& mapStaticLights = StaticLightsContainer::GetInstance()->GetStaticLights();
	std::map<unsigned short, LightRes*>::const_iterator iter = mapStaticLights.find(key);
	if( iter != mapStaticLights.end() && NULL != iter->second )
	{
		return iter->second;
	}
	return NULL;
}

LightRes* CToolStaticLightDlg::GetLightResFromCurSel(int& index)
{
	if( m_listStaticLights.GetSelCount() != 1 )
		return NULL;

	LightRes* pLightRes = NULL;
	int count = m_listStaticLights.GetCount();
	for( int i=0; i<count-1; ++i )	// 最后一个“新建”不判断
	{
		bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
		if( bSeletcted )
		{
			pLightRes = GetLightRes(i);
			index = i;
			break;
		}
	}
	return pLightRes;
}

void CToolStaticLightDlg::OnSelEndOkLightColor()
{
	UpdateData();
	updateHSL();
	UpdateLightColor();
}

void CToolStaticLightDlg::OnNMReleaseSliderColor( NMHDR *pNMHDR, LRESULT *pResult )
{
	UpdateData();
	setHSL();
	UpdateLightColor();
}

void CToolStaticLightDlg::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_SL_H ) )
	{
		OnNMReleaseSliderColor( NULL, NULL );
	}
	else if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_SL_S ) )
	{
		OnNMReleaseSliderColor( NULL, NULL );
	}
	else if( pScrollBar == (CScrollBar*)GetDlgItem( IDC_SLIDER_SL_L ) )
	{
		OnNMReleaseSliderColor( NULL, NULL );
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CToolStaticLightDlg::updateHSL()
{
	NiColor color;
	ConvertRGB2NiColor( m_colorLightColor, color );
	color = RGBToHSL(color);

	m_sliderH.SetPos(color.r);
	m_sliderS.SetPos(color.g);
	m_sliderL.SetPos(color.b);
}

void CToolStaticLightDlg::setHSL()
{
	int h = m_sliderH.GetPos();
	int s = m_sliderS.GetPos();
	int l = m_sliderL.GetPos();

	NiColor color;
	color.r = h;
	color.g = s;
	color.b = l;

	color = HSLToRGB(color);

	m_colorLightColor = RGB(color.r,color.g,color.b);
	m_cpLightColor.SetColor( m_colorLightColor );
}

NiColor CToolStaticLightDlg::RGBToHSL( NiColor color )
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
}

NiColor CToolStaticLightDlg::HSLToRGB( NiColor color )
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
}

bool CToolStaticLightDlg::UpdateLightColor()
{
	std::vector<int> vecSelect;
	if( !GetSelectedList(vecSelect) )
		return false;

	for( int i=0; i<vecSelect.size(); ++i )
	{
		LightRes* pLightRes = GetLightRes(vecSelect[i]);

		if( pLightRes )
		{
			PointLight* pLight = (PointLight*)pLightRes;
			BYTE r = m_colorLightColor & 0xFF;
			BYTE g = (m_colorLightColor >>  8) & 0xFF;
			BYTE b = (m_colorLightColor >> 16) & 0xFF;
			NiColorB colorB = NiColorB(r, g, b);
			pLight->SetColor(colorB);

			CToolStaticLight* toolStaticLight = GetTool();
			if( toolStaticLight )
			{
				toolStaticLight->UpdateColor(vecSelect[i], colorB);
			}
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	return true;
}

void CToolStaticLightDlg::SelectLight( int index, BOOL bMulti )
{
	if( index < 0 || index >= m_listStaticLights.GetCount()-1 )
		return;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( !pToolStaticLight )
		return;

	if( !bMulti )
	{
		UnSelectAll();
		pToolStaticLight->UnSelectAll();
	}
	SelectOneLight(index, TRUE);
	pToolStaticLight->DoSelect(index);

	pToolStaticLight->SetOptMode(CToolStaticLight::optMode_Pick);
}

void CToolStaticLightDlg::UnSelectLight( int index )
{
	if( index < 0 || index >= m_listStaticLights.GetCount()-1 )
		return;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( !pToolStaticLight )
		return;

	UnSelectOneLight(index, TRUE);
	pToolStaticLight->UnSelect(index);

	pToolStaticLight->SetOptMode(CToolStaticLight::optMode_Pick);
}

void CToolStaticLightDlg::OnBnClickedDeleteLight()
{
	CalSelectNum();
	if( m_nSelectedNum != 1 )	// 单选
		return;

	std::vector<int> vecSelect;
	if( !GetSelectedList(vecSelect) || vecSelect.size() > 1 )
		return;

	//删除光源
	int cursel = vecSelect[0];
	if( cursel < 0 || cursel >= m_vecLightRef.size() )
		return;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( !pToolStaticLight )
		return;

	int key = m_vecLightRef[cursel];
	const std::map<unsigned short, LightRes*>& mapStaticLights = StaticLightsContainer::GetInstance()->GetStaticLights();
	std::map<unsigned short, LightRes*>::const_iterator iter = mapStaticLights.find(key);
	if( iter != mapStaticLights.end() )
	{
		StaticLightsContainer::GetInstance()->RemoveLight(key);
		m_vecLightRef.erase(m_vecLightRef.begin() + cursel );

		bool bNeedCalLastNo = false;
		if( cursel == m_listStaticLights.GetCount() - 2 )	// 删除最后一个灯光，需要重新计算m_nLastLightNo
			bNeedCalLastNo = true;
		m_listStaticLights.DeleteString(cursel);
		if( bNeedCalLastNo )
		{
			if( m_listStaticLights.GetCount() <= 1 )
				m_nLastLightNo = 0;
			else
			{
				CString strText;
				int nValue = -1;
				int index = m_listStaticLights.GetCount()-2;
				m_listStaticLights.GetText(index, strText);
				if( _sntscanf_s(strText.GetBuffer(),strText.GetLength(),LIST_LIGHTNAME,&nValue) == 1 )
				{
					m_nLastLightNo = nValue;
				}
			}
		}
		
		// 删除模型
		pToolStaticLight->RemoveLightModel(cursel);

		// 不选中
		CalSelectNum();
		if( m_nSelectedNum > 0 )
		{
			assert(0);
		}
		else
		{
			CancelSelect();
		}

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
	}
}

void CToolStaticLightDlg::CancelSelect()
{
	EnableControls(FALSE);
	UnSelectAll();
	CToolStaticLight* pToolStaticLight = GetTool();
	if( pToolStaticLight )
		pToolStaticLight->SetOptMode(CToolStaticLight::optMode_Pick);
}

void CToolStaticLightDlg::UnSelectAll()
{
	for( int i=0; i<m_listStaticLights.GetCount(); ++i )
	{
		m_listStaticLights.SetSel(i, FALSE);
	}
	m_nSelectedNum = 0;

	CToolStaticLight* pToolStaticLight = GetTool();
	if( pToolStaticLight )
		pToolStaticLight->UnSelectAll();
}

void CToolStaticLightDlg::SelectOneLight( int index, BOOL bUpdateProp )
{
	if( index < 0 || index >= m_listStaticLights.GetCount()-1 )	// 非“新建”
		return;

	m_listStaticLights.SetSel(index, TRUE);
	CalSelectNum();
	CToolStaticLight* pToolStaticLight = GetTool();
	if( pToolStaticLight )
	{
		pToolStaticLight->DoSelect(index);
	}
	if( bUpdateProp )
		UpdateProperties();
}

void CToolStaticLightDlg::UnSelectOneLight( int index, BOOL bUpdateProp )
{
	if( index < 0 || index >= m_listStaticLights.GetCount()-1 )	// 非“新建”
		return;

	if( m_nSelectedNum <= 0 )
	{
		UnSelectAll();
		return;
	}

	m_listStaticLights.SetSel(index, FALSE);
	CalSelectNum();
	CToolStaticLight* pToolStaticLight = GetTool();
	if( pToolStaticLight )
	{
		pToolStaticLight->UnSelect(index);
	}
	if( bUpdateProp )
		UpdateProperties();
}

bool CToolStaticLightDlg::GetSelectedList( std::vector<int>& vecSelected )
{
	vecSelected.clear();
	int count = m_listStaticLights.GetCount();
	for( int i=0; i<count-1; ++i )	// 最后一个“新建”不判断
	{
		bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
		if( bSeletcted )
		{
			vecSelected.push_back(i);
		}
	}
	return (vecSelected.size() > 0);
}

void CToolStaticLightDlg::OnBnClickedMoveToLight()
{
	if( m_nSelectedNum <= 0 )
		return;

	int iFirstSel = -1;
	int count = m_listStaticLights.GetCount();
	for( int i=0; i<count-1; ++i )	// 最后一个“新建”不判断
	{
		bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
		if( bSeletcted )
		{
			iFirstSel = i;
			break;
		}
	}
	if( iFirstSel >= 0 )
	{
		// 移动相机到灯前面
		LightRes* pLightRes = GetLightRes(iFirstSel);
		if( pLightRes )
		{
			PointLight* pLight = (PointLight*)pLightRes;
			Vector pos = pLight->GetPos();

			SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
			if( !camera )
				return;

			D3DXVECTOR3 cameraDir = camera->GetDir();
			Vector dir(cameraDir.x, cameraDir.y, cameraDir.z);
			dir.normalize();
			pos -= dir * (pLight->GetDist() + 10.f);
			camera->SetPos(pos);
		}
	}
}

void CToolStaticLightDlg::CalSelectNum()
{
	m_nSelectedNum = 0;
	int count = m_listStaticLights.GetCount();
	for( int i=0; i<count-1; ++i )	// 最后一个“新建”不判断
	{
		bool bSeletcted = m_listStaticLights.GetSel(i) > 0; 
		if( bSeletcted )
		{
			++m_nSelectedNum;
		}
	}
}