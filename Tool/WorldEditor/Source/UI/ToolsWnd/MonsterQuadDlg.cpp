#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolMonsterQuad.h"
#include "Edit/ToolManager.h"
#include "MonsterQuadDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/NdlResMgr.h"
#include "EditRes/NdlEditRes.h"
#include "ItemDetailConfig.h"
#include "tstring.h"

static const char *MAP_PK_MODES[] =
{
	"无PK模式",
	"禁止所有PK",
	"狂暴PK",
	"狂暴PK + 正常PK",
	"狂暴PK + 正常PK + 国家PK",
	"阵营PK",
	"公会PK",
	"任意PK",
	"小队混战PK",
	"个人擂台PK",
	"争夺战PK"
	/*"跨服PK"*/
};

IMPLEMENT_DYNAMIC(CToolMonsterQuadDlg, CDialog)

BEGIN_MESSAGE_MAP(CToolMonsterQuadDlg, CDialog)
	//{{AFX_MSG_MAP(CToolMonsterQuadDlg)
	ON_BN_CLICKED(IDC_RADIO_MONSTERQUAD, &CToolMonsterQuadDlg::OnBnClickedRadioZoneAdd)
	ON_BN_CLICKED(IDC_RADIO_PICK_MONSTERQUAD, &CToolMonsterQuadDlg::OnBnClickedRadioZonePick)

	ON_CBN_SELCHANGE(IDC_COMBO_MONSTERQUAD_PK, &CToolMonsterQuadDlg::OnCbnSelchangeComboZonePKMode)
	ON_CBN_SELCHANGE(IDC_COMBO_MONSTERQUAD_Stall, &CToolMonsterQuadDlg::OnCbnSelchangeComboZoneCanStall)
	ON_CBN_SELCHANGE(IDC_COMBO_MONSTER, &CToolMonsterQuadDlg::OnCbnSelchangeComboMonster)

	ON_CBN_SELCHANGE(IDC_COMBO_MONSTERQUAD_Stall2, &CToolMonsterQuadDlg::OnCbnSelchangeComboZoneCanDuel)

	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_ZONE_NAME, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneName)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_AISTEP, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneAIStep)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_X, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneX)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_Y, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneY)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_X_SCALE, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneXScale)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_Y_SCALE, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneYScale)
	ON_EN_KILLFOCUS(IDC_EDT_ENTERSCRIPT, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneEnterScript)
	ON_EN_KILLFOCUS(IDC_EDT_LEAVESCRIPT, &CToolMonsterQuadDlg::OnEnKillfocusEditZoneLeaveScript)

	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_AISCRIPT, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAiscript)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_AIVALUE, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAivalue)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_DEADSCRIPT, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadDeadscript)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_DIR, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadDir)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_NUM, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadNum)
	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_RELIFE, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadRelife)

	ON_EN_KILLFOCUS(IDC_EDT_MONSTERQUAD_COUNTY, &CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAiCounty) //lyh++ 怪物国家edit

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONSTERQUAD_X, &CToolMonsterQuadDlg::OnDeltaposSpinZoneX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONSTERQUAD_Y, &CToolMonsterQuadDlg::OnDeltaposSpinZoneY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONSTERQUAD_X_SCALE, &CToolMonsterQuadDlg::OnDeltaposSpinZoneXScale)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONSTERQUAD_Y_SCALE, &CToolMonsterQuadDlg::OnDeltaposSpinZoneYScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CToolMonsterQuadDlg::CToolMonsterQuadDlg(CToolMonsterQuadDlg *pParent)
    : CDialog(CToolMonsterQuadDlg::IDD, pParent)
{

}

CToolMonsterQuadDlg::~CToolMonsterQuadDlg()
{
	for (int i = 0; i < mMonsterInfo.size(); ++i)
	{
		SAFE_DELETE(mMonsterInfo[i]);
	}
}

void CToolMonsterQuadDlg::SetActive( bool isModify )
{
    CToolManager *toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
    toolManager->SetActiveTool(TOOL_MONSTERQUAD);

    CToolMonsterQuad *toolMonsterQuad = GetToolMonsterQuad();
    Assert(NULL != toolMonsterQuad);

    toolMonsterQuad->Bind(this);
    toolMonsterQuad->Reset();

    mBtnEditMonster.SetCheck(BST_CHECKED);
    mBtnAddMonster.SetCheck(BST_UNCHECKED);

    UpdateData(FALSE);
}

CToolMonsterQuad *CToolMonsterQuadDlg::GetToolMonsterQuad()
{
    if (CWorldEditDoc::GetActiveMapDoc()->GetWorldView() != NULL)
    {
        CToolManager *toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
        return (CToolMonsterQuad *) (toolManager->GetActiveTool());
    }
    else
        return NULL;
}

void CToolMonsterQuadDlg::Update(CMonsterQuadRes *res)
{
    CToolMonsterQuad *toolMonsterQuad = GetToolMonsterQuad();
    if (toolMonsterQuad == NULL)
        return;

    CString strValue;

	// 更新: 区域名
	mEditZoneName.SetWindowText(res == NULL ? "" : res->GetZoneName());

	// 设置AIStep
	strValue.Format("%d", res == NULL ? 0 : res->m_nAIStep);
	mEditAIStep.SetWindowText(res == NULL ? "" : strValue);

	// 更新: 能否Pk
	mComboPK.SetCurSel(res == NULL ? 0 : res->m_nPKMode + 1);
		
	// 更新: 能否摆摊
	mComboStall.SetCurSel(res == NULL ? 0 : (int) res->m_bCanStall);

	// 更新: 能否摆摊
	mComboDuel.SetCurSel(res == NULL ? 0 : (int) res->m_bCanDuel);

    // 更新: X
	strValue.Format("%6.2f", res == NULL ? 0 : res->GetPosX());
	mEditWorldPosX.SetWindowText(res == NULL ? "" : strValue);

    // 更新: Y
    strValue.Format("%6.2f", res == NULL ? 0 : res->GetPosY());
	mEditWorldPosY.SetWindowText(res == NULL ? "" : strValue);

    // 更新: 缩放X
    float scale_x = ((res == NULL) ? 1 : res->m_fRight - res->m_fLeft);
    strValue.Format("%6.2f", scale_x);
	mEditScaleX.SetWindowText(res == NULL ? "" : strValue);

    // 更新: 缩放Y
    float scale_y = ((res == NULL) ? 1 : res->m_fTop - res->m_fBottom);
    strValue.Format("%6.2f", scale_y);
	mEditScaleY.SetWindowText(res == NULL ? "" : strValue);

    // 更新: 脚本
	mEditEnterScript.SetWindowText(res == NULL ? "" : res->GetEnterScript());
	mEditLeaveScript.SetWindowText(res == NULL ? "" : res->GetLeaveScript());

	{
		SetDlgItemInt(IDC_EDT_MONSTERQUAD_RELIFE, res == NULL ? 0 : res->m_nRelife);
		SetDlgItemInt(IDC_EDT_MONSTERQUAD_NUM, res == NULL ? 1 : res->m_nNumber);
		SetDlgItemInt(IDC_EDT_MONSTERQUAD_DIR, res == NULL ? 0 : res->m_nDir);
		SetDlgItemInt(IDC_EDT_MONSTERQUAD_AIVALUE, res == NULL ? 0 : res->m_nAIValue);

		SetDlgItemText(IDC_EDT_MONSTERQUAD_DEADSCRIPT, res == NULL ? "" : res->m_szDeadScript);
		SetDlgItemText(IDC_EDT_MONSTERQUAD_AISCRIPT, res == NULL ? "" : res->m_szAIScript); 
		SetDlgItemInt(IDC_EDT_MONSTERQUAD_COUNTY, res == NULL ? 0 : res->m_nCountry); //更新的地方  国家 
	}

	// 更新怪物: ComboBox当前选中为指定Monster
	if (res == NULL)
	{
		mComboMonster.SetCurSel(0);
	}
	else
	{
		MonsterIdsIter finder = std::find(mMonsterIds.begin(), mMonsterIds.end(), res->m_nMonsterId);
		if (finder != mMonsterIds.end())
		{
			mComboMonster.SetCurSel(std::distance(mMonsterIds.begin(), finder));
		}
		else
		{
			mComboMonster.SetCurSel(0);
			res->m_nMonsterId = mMonsterIds[0];
		}
	}
}

void CToolMonsterQuadDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CToolMonsterQuadDlg)
    DDX_Control(pDX, IDC_RADIO_PICK_MONSTERQUAD, mBtnEditMonster);
    DDX_Control(pDX, IDC_RADIO_MONSTERQUAD, mBtnAddMonster);

	DDX_Control(pDX, IDC_EDT_MONSTERQUAD_ZONE_NAME, mEditZoneName);
    DDX_Control(pDX, IDC_EDT_MONSTERQUAD_AISTEP, mEditAIStep);
    DDX_Control(pDX, IDC_COMBO_MONSTERQUAD_PK, mComboPK);
    DDX_Control(pDX, IDC_COMBO_MONSTERQUAD_Stall, mComboStall);
	 DDX_Control(pDX, IDC_COMBO_MONSTERQUAD_Stall2, mComboDuel);

	DDX_Control(pDX, IDC_EDT_MONSTERQUAD_X, mEditWorldPosX);
    DDX_Control(pDX, IDC_SPIN_MONSTERQUAD_X, mSpinWorldPosX);

    DDX_Control(pDX, IDC_EDT_MONSTERQUAD_Y, mEditWorldPosY);
    DDX_Control(pDX, IDC_SPIN_MONSTERQUAD_Y, mSpinWorldPosY);

    DDX_Control(pDX, IDC_EDT_MONSTERQUAD_X_SCALE, mEditScaleX);
    DDX_Control(pDX, IDC_SPIN_MONSTERQUAD_X_SCALE, mSpinScaleX);

    DDX_Control(pDX, IDC_EDT_MONSTERQUAD_Y_SCALE, mEditScaleY);
    DDX_Control(pDX, IDC_SPIN_MONSTERQUAD_Y_SCALE, mSpinScaleY);

    DDX_Control(pDX, IDC_EDT_ENTERSCRIPT, mEditEnterScript);
    DDX_Control(pDX, IDC_EDT_LEAVESCRIPT, mEditLeaveScript);

	DDX_Control(pDX, IDC_COMBO_MONSTER, mComboMonster);
    //}}AFX_DATA_MAP
}

BOOL CToolMonsterQuadDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetDlgItemInt(IDC_EDT_MONSTERQUAD_AISTEP, 0);

	CString szTemp;
	for (int i = -1; i < 10; ++i)
	{
		szTemp.Format("%d-%s", i, MAP_PK_MODES[i + 1]);
		mComboPK.AddString(szTemp);
	}
    mComboPK.SetCurSel(0);

    mComboStall.SetCurSel(0);

//	mComboDuel.AddString("禁止");
//	mComboDuel.AddString("允许");
	mComboDuel.SetCurSel(1);

    mSpinWorldPosX.SetBuddy(&mEditWorldPosX);
    mSpinWorldPosY.SetBuddy(&mEditWorldPosY);

    mSpinScaleX.SetBuddy(&mEditScaleX);
    mSpinScaleY.SetBuddy(&mEditScaleY);

    if (!theItemDetailConfig.LoadXmlMonster("..\\Data\\Config\\Monster.config"))
    {
        CString strMsg;
        strMsg.Format( _T("加载Monster.config失败！") );
        ::MessageBox( NULL, strMsg, _T("错误"), MB_OK );
        return FALSE;
    }

    CItemDetail::SMonster *monster = NULL;
    CString strItem;

	std::vector<CItemDetail::SMonster *> monsters = theItemDetailConfig.GetMonsterInfo();
    for (int i = 0; i < monsters.size(); ++i)
    {
		monster = new CItemDetail::SMonster;
        *monster = *monsters[i];
		mMonsterInfo.push_back(monster);
		mMonsterIds.push_back(monster->stMonsterId);

        strItem.Format("%s(%d)", monster->GetName(), monster->stMonsterId);
        mComboMonster.AddString(strItem);
    }
	mComboMonster.SetCurSel(0);
    return TRUE;
}

void CToolMonsterQuadDlg::DataEditHandler(int flag)
{
    CToolMonsterQuad *toolMonster = GetToolMonsterQuad();
    if (toolMonster == NULL)
        return;

    CMonsterQuadRes *res = toolMonster->GetCurrQuad();
    if (res == NULL)
        return;

    float x = res->GetPosX();
    float y = res->GetPosY();
    float w = res->m_fRight - res->m_fLeft;
    float h = res->m_fTop - res->m_fBottom;

    CString strValue;
	int curSel;
	switch (flag)
	{
	// Zone Edit
	case MonsQuad_Edit_ZoneName:
		{
			mEditZoneName.GetWindowText(strValue);
			if (!strValue.IsEmpty())
			{
				res->SetZoneName(strValue);
			}
		}
		break;

	case MonsQuad_Edit_AIStep:
		{
			mEditAIStep.GetWindowText(strValue);
			int step = atoi(strValue);

			res->m_nAIStep = step;
		}
		break;

	case MonsQuad_Edit_Pk:
		{
			curSel = mComboPK.GetCurSel();
			if (curSel == CB_ERR)
				return;

			res->m_nPKMode = curSel - 1;
		}
		break;

	case MonsQuad_Edit_Stall:
		{
			curSel = mComboStall.GetCurSel();
			if (curSel == CB_ERR)
				return;

			res->m_bCanStall = curSel;
		}
		break;
	case MonsQuad_Edit_Duel:
		{

			curSel = mComboDuel.GetCurSel();
			if (curSel == CB_ERR)
				return;
            if(curSel == 0)
			res->m_bCanDuel = false;
			else
			res->m_bCanDuel = true;


		}
		break;

	case MonsQuad_Edit_PosX:
	case MonsQuad_Edit_PosY:
	case MonsQuad_Edit_W:
	case MonsQuad_Edit_H:
		{
			int CURRENT_TILE_W = CURRENTTILE->GetRowColumn()[0] * WORLD_CHUNKSIZE;
			int CURRENT_TILE_H = CURRENTTILE->GetRowColumn()[1] * WORLD_CHUNKSIZE;

			if (flag == MonsQuad_Edit_PosX)
			{
				mEditWorldPosX.GetWindowText(strValue);
				{
					x = atof(strValue);
					x = ZnClamp<flt32>(x, w / 2, CURRENT_TILE_W - w / 2);
					strValue.Format(DECIMAL_STR_FORMAT, x);
				}
				mEditWorldPosX.SetWindowText(strValue);
			}
			else if (flag == MonsQuad_Edit_PosY)
			{
				mEditWorldPosY.GetWindowText(strValue);
				{
					y = atof(strValue);
					y = ZnClamp<flt32>(y, h / 2, CURRENT_TILE_H - h / 2);
					strValue.Format(DECIMAL_STR_FORMAT, y);
				}
				mEditWorldPosY.SetWindowText(strValue);
			}
			else if (flag == MonsQuad_Edit_W)
			{
				float toLeft = x;
				float toRight = CURRENT_TILE_W - x;
				float maxScaleX = ZnMax<float>(toLeft, toRight);

				mEditScaleX.GetWindowText(strValue);
				{
					w = atof(strValue);
					w = ZnClamp<flt32>(w, 0, maxScaleX * 2);
					strValue.Format(DECIMAL_STR_FORMAT, w);
				}
				mEditScaleX.SetWindowText(strValue);
			}
			else if (flag == MonsQuad_Edit_H)
			{
				float toBottom = y;
				float toTop = CURRENT_TILE_H - y;
				float maxScaleY = ZnMax<float>(toBottom, toTop);

				mEditScaleY.GetWindowText(strValue);
				{
					h = atof(strValue);
					h = ZnClamp<flt32>(h, 0, maxScaleY * 2);
					strValue.Format(DECIMAL_STR_FORMAT, h);
				}
				mEditScaleY.SetWindowText(strValue);
			}

			toolMonster->UpdateMonsQuad(toolMonster->mCurQuadRes, x, y, w, h);
			//toolMonster->ShowPmpModel();
		}
		break;

	case MonsQuad_Edit_EnterScript:
		{
			mEditEnterScript.GetWindowText(strValue);
			toolMonster->DoSetEnterScript(res, strValue);
		}
		break;

	case MonsQuad_Edit_LeaveScript:
		{
			mEditLeaveScript.GetWindowText(strValue);
			toolMonster->DoSetLeaveScript(res, strValue);
		}
		break;

	// Monster Edit
	case MonsQuad_Edit_Monster:
		{			
			curSel = mComboMonster.GetCurSel();
			if (curSel == CB_ERR)
				return;

			int id = mMonsterIds[curSel];
			if (id == res->m_nMonsterId)
			{
				// 没有改变, 直接返回
				return;
			}

			// MonsterId已改变, 需要保存
			res->m_nMonsterId = id;

			// 更新Model
			res->UpdateMonsterModel();
			//toolMonster->DoSetMonsterType(res, id, 0);
		}
		break;

	case MonsQuad_Edit_Relife:
		res->m_nRelife = GetDlgItemInt(IDC_EDT_MONSTERQUAD_RELIFE);
		break;
	
	case MonsQuad_Edit_Number:
		res->m_nNumber = GetDlgItemInt(IDC_EDT_MONSTERQUAD_NUM);
		break;

	case MonsQuad_Edit_Dir:
		res->m_nDir = GetDlgItemInt(IDC_EDT_MONSTERQUAD_DIR);
		break;

	case MonsQuad_Edit_AIValue:
		res->m_nAIValue = GetDlgItemInt(IDC_EDT_MONSTERQUAD_AIVALUE);
		break;

	case MonsQuad_Edit_DeadScript:
		{
			GetDlgItemText(IDC_EDT_MONSTERQUAD_DEADSCRIPT, strValue);
			strcpy(res->m_szDeadScript, strValue);
		}
		break;

	case MonsQuad_Edit_AIScript:
		{
			GetDlgItemText(IDC_EDT_MONSTERQUAD_AISCRIPT, strValue);
			strcpy(res->m_szAIScript, strValue);
		}
		break;
	case MonsQuad_Edit_AICounty: //lyh++ 国家
		res->m_nCountry = GetDlgItemInt(IDC_EDT_MONSTERQUAD_COUNTY);

		break;

	default:
		assert(false && "invalid monster edit flag");
	}

    // 设置Dirty标记
    CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
}

void CToolMonsterQuadDlg::SpinUpDownHandler(CEdit &edit, LPNMUPDOWN pNMUpDown, LRESULT *pResult)
{
	CString strValue;
	edit.GetWindowText(strValue);

	float v = atof(strValue);
	if (pNMUpDown->iDelta == -1)
		v -= 1;
	else
		v += 1;

	if (edit == mEditScaleX || edit == mEditScaleY)
	{
		if (v < 0.1)
			v = 0.1;
	}

	strValue.Format(DECIMAL_STR_FORMAT, v);
	edit.SetWindowText(strValue);

	// Return nonzero to prevent the change in the control's position, or zero to allow the change
	*pResult = 1;
}

void CToolMonsterQuadDlg::SetOperationModeHandler(int mode)
{
	CToolMonsterQuad *toolMonster = GetToolMonsterQuad();
	if (toolMonster == NULL)
		return;

	toolMonster->SetOptMode((CToolMonsterQuad::optMode) mode);
}

void CToolMonsterQuadDlg::OnCbnSelchangeComboMonster()
{
	DataEditHandler(MonsQuad_Edit_Monster);
}

void CToolMonsterQuadDlg::OnCbnSelchangeComboZonePKMode()
{
	DataEditHandler(MonsQuad_Edit_Pk);
}

void CToolMonsterQuadDlg::OnCbnSelchangeComboZoneCanStall()
{
	DataEditHandler(MonsQuad_Edit_Stall);
}

void CToolMonsterQuadDlg::OnCbnSelchangeComboZoneCanDuel()
{
	DataEditHandler(MonsQuad_Edit_Duel);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneName()
{
	DataEditHandler(MonsQuad_Edit_ZoneName);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneAIStep()
{
	DataEditHandler(MonsQuad_Edit_AIStep);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneX()
{
	DataEditHandler(MonsQuad_Edit_PosX);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneY()
{
	DataEditHandler(MonsQuad_Edit_PosY);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneXScale()
{
	DataEditHandler(MonsQuad_Edit_W);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneYScale()
{
	DataEditHandler(MonsQuad_Edit_H);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneEnterScript()
{
	DataEditHandler(MonsQuad_Edit_EnterScript);
}

void CToolMonsterQuadDlg::OnEnKillfocusEditZoneLeaveScript()
{
	DataEditHandler(MonsQuad_Edit_LeaveScript);
}

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadRelife()
{
	DataEditHandler(MonsQuad_Edit_Relife);
}

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadNum()
{
	DataEditHandler(MonsQuad_Edit_Number);
}

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadDir()
{
	DataEditHandler(MonsQuad_Edit_Dir);
}

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAivalue()
{
	DataEditHandler(MonsQuad_Edit_AIValue);
}

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadDeadscript()
{
	DataEditHandler(MonsQuad_Edit_DeadScript);
}

   void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAiCounty()
   {
    DataEditHandler(MonsQuad_Edit_AICounty);
   }

void CToolMonsterQuadDlg::OnEnKillfocusEdtMonsterquadAiscript()
{
	DataEditHandler(MonsQuad_Edit_AIScript);
}

void CToolMonsterQuadDlg::OnDeltaposSpinZoneX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	SpinUpDownHandler(mEditWorldPosX, pNMUpDown, pResult);
	OnEnKillfocusEditZoneX();
}

void CToolMonsterQuadDlg::OnDeltaposSpinZoneY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SpinUpDownHandler(mEditWorldPosY, pNMUpDown, pResult);
	OnEnKillfocusEditZoneY();
}

void CToolMonsterQuadDlg::OnDeltaposSpinZoneXScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SpinUpDownHandler(mEditScaleX, pNMUpDown, pResult);
	OnEnKillfocusEditZoneXScale();
}

void CToolMonsterQuadDlg::OnDeltaposSpinZoneYScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SpinUpDownHandler(mEditScaleY, pNMUpDown, pResult);
	OnEnKillfocusEditZoneYScale();
}

void CToolMonsterQuadDlg::OnBnClickedRadioZoneAdd()
{
	SetOperationModeHandler(CToolMonsterQuad::optMode_AddMonsterQuad);
	Update(NULL);
}

void CToolMonsterQuadDlg::OnBnClickedRadioZonePick()
{
	SetOperationModeHandler(CToolMonsterQuad::optMode_Pick);
}