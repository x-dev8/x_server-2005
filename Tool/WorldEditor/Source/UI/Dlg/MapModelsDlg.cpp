#include "stdafx.h"
#include "MapModelsDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "Utility.h"

IMPLEMENT_DYNAMIC(CMapModelsDlg, CDialog)

BEGIN_MESSAGE_MAP(CMapModelsDlg, CDialog)
	ON_BN_CLICKED(IDB_MAP_MODELS_DEL, &CMapModelsDlg::OnBtnClickedDel)
	ON_BN_CLICKED(IDB_MAP_MODEL_CLEAN_UNUSED, &CMapModelsDlg::OnBtnClickedCleanUnused)
	ON_BN_CLICKED(IDB_MAP_MODELS_EXPORT, &CMapModelsDlg::OnBtnClickedExport)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MAP_MODEL, CMapModelsDlg::OnNotifyCustomDraw)
END_MESSAGE_MAP()

CMapModelsDlg::CMapModelsDlg(CWnd *lpParent /* = NULL */) : CDialog(CMapModelsDlg::IDD, lpParent)
{

}

CMapModelsDlg::~CMapModelsDlg()
{

}

BOOL CMapModelsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LONG dwStyle = ::GetWindowLong(mList.m_hWnd, GWL_STYLE);
	dwStyle |= LVS_REPORT;
	::SetWindowLong(mList.m_hWnd, GWL_STYLE, dwStyle);
	mList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	mList.InsertColumn(0, "路径", LVCFMT_LEFT, 452);
	mList.InsertColumn(1, "版本", LVCFMT_CENTER, 42);

	CWorldTile *tile = CURRENTTILE;
	if (tile != NULL && strlen(tile->GetPathName()) > 0)
	{
		CString szMew = tile->GetPathName();
		szMew.MakeLower();

		int nIndex = szMew.Find(".mew");
		if (nIndex != -1)
		{
			CString szMap = szMew.Left(nIndex);

			CString szCaption;
			szCaption.Format("地图：%s 的模型列表", szMap);
			SetWindowText(szCaption);
		}
	}

	CString szWorldFolder = CWorldEditDoc::GetActiveMapDoc()->GetPathName();
	int nIndex = szWorldFolder.Find("Data");
	mClientFolder = szWorldFolder.Left(nIndex - 1);

	Refresh();

	return TRUE;
}

void CMapModelsDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAP_MODEL, mList);
}

void CMapModelsDlg::OnBtnClickedDel()
{
	int nCurSel = mList.GetSelectionMark();
	if (nCurSel == -1 || CURRENTTILE == NULL)
	{
		::MessageBox(NULL, "请选择一个模型!", "确认删除", MB_OK);
		return;
	}

	std::vector<TObjectInfo *> &models = CURRENTTILE->GetCResMgr()->GetStaticModelList();
	if (nCurSel < 0 || nCurSel >= models.size())
		return;

	TObjectInfo *obj = models[nCurSel];
	theApp.GetWorldEditor()->DeleteStaticModel(nCurSel, true);
	theApp.GetWorldEditor()->CleanUnusedModel(CURRENTTILE->GetMapId());

	Refresh();
}

void CMapModelsDlg::OnBtnClickedCleanUnused()
{
	CWorldTile *tile = CURRENTTILE;
	if (tile != NULL)
	{
		std::vector<TObjectInfo *> &models = tile->GetCResMgr()->GetStaticModelList();
		for (int i = 0; i < models.size(); ++i)
		{
			TObjectInfo *obj = models[i];
			if (IsModelLoadFailed(obj))
			{
				theApp.GetWorldEditor()->DeleteStaticModel(i, true);
			}
			else
			{
				if (IsModelVersionUnder105(obj))
				{
					theApp.GetWorldEditor()->DeleteStaticModel(i, true);
				}
			}
		}
	}
	theApp.GetWorldEditor()->CleanUnusedModel(CURRENTTILE->GetMapId());

	Refresh();
}

void CMapModelsDlg::OnBtnClickedExport()
{
	CWorldTile *tile = CURRENTTILE;
	if (tile == NULL)
		return;

	CString szFileName;
	szFileName.Format("%s 中的所有物件", tile->GetPathName());

	CFileDialog dlg(FALSE, "(*.txt)|*.txt", szFileName, 4|2, "(*.txt)|*.txt", NULL);
	if (dlg.DoModal() != IDOK)
		return;

	FILE *fp = NULL;
	if (fopen_s(&fp, dlg.GetPathName(), "wt") != 0)
		return;

	char buffer[MAX_PATH] = {0};
	std::vector<TObjectInfo *> &models = tile->GetCResMgr()->GetStaticModelList();
	for (int i = 0; i < models.size(); ++i)
	{
		TObjectEditInfo *obj = dynamic_cast<TObjectEditInfo *>(models[i]);
		CWorldRes *obj_res = tile->GetCResMgr()->GetStaticModelRefList()[obj->id];
		if (IsModelLoadFailed(obj))
		{
			sprintf_s(buffer, MAX_PATH - 1, "%s\\%s   --->模型文件不存在\n", mClientFolder.c_str(), obj_res->GetName());
			fputs(buffer, fp);
		}
		else
		{
			if (IsModelVersionUnder105(obj))
			{
				sprintf_s(buffer, MAX_PATH - 1, "%s\\%s   --->模型版本太老, 需要重新导出\n", mClientFolder.c_str(), obj_res->GetName());
				fputs(buffer, fp);
			}
			else
			{
				sprintf_s(buffer, MAX_PATH - 1, "%s\\%s   --->正常\n", mClientFolder.c_str(), obj_res->GetName());
				fputs(buffer, fp);
			}
		}
	}

	fclose(fp);
}

void CMapModelsDlg::OnNotifyCustomDraw(NMHDR *pNmHdr, LRESULT *pResult)
{
	NMLVCUSTOMDRAW *lpNMLVCD = reinterpret_cast<NMLVCUSTOMDRAW *>(pNmHdr);

	int nItem = lpNMLVCD->nmcd.dwItemSpec;
	if (nItem < 0 || nItem >= mMapModelStates.size())
		return;

	if (lpNMLVCD->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT)
	{
		if (mList.GetItemState(nItem, CDIS_SELECTED))
			lpNMLVCD->nmcd.uItemState &= ~CDIS_SELECTED;
	}

	COLORREF clrText;
	switch (mMapModelStates[nItem])
	{
	case MapModelState::MMS_OK:
		clrText = RGB(0, 0, 255);
		break;

	case MapModelState::MMS_VERSION_UNDER_105:
		clrText = RGB(155, 155, 155);
		break;

	case MapModelState::MMS_LOAD_FAILED:
		clrText = RGB(255, 0, 0);
		break;
	}

	lpNMLVCD->clrText = clrText;

	*pResult = CDRF_NOTIFYITEMDRAW;
}

bool CMapModelsDlg::IsModelLoadFailed(TObjectInfo *obj)
{
	CWorldRes *obj_res = CURRENTTILE->GetCResMgr()->GetStaticModelRefList()[obj->id];
	std::string path = mClientFolder + std::string("\\") + obj_res->GetName();
	return !Utility::IsFileExists(path.c_str());
}

bool CMapModelsDlg::IsModelVersionUnder105(TObjectInfo *obj)
{
	return obj->model->GetMex() != NULL && obj->model->GetMex()->GetVersion() < 105;
}

void CMapModelsDlg::Refresh()
{
	mList.DeleteAllItems();

	CWorldTile *tile = CURRENTTILE;
	if (tile != NULL)
	{
		std::vector<TObjectInfo *> &models = tile->GetCResMgr()->GetStaticModelList();
		char szItem[MAX_PATH] = {0};
		mMapModelStates.resize(models.size());
		for (int i = 0; i < models.size(); ++i)
		{
			mList.InsertItem(i, "");

			TObjectInfo *obj = models[i];
			IMex *mex = obj->model->GetMex();
			CWorldRes *obj_res = tile->GetCResMgr()->GetStaticModelRefList()[obj->id];

			// 设置模型状态
			if (IsModelLoadFailed(obj))
			{
				mMapModelStates[i] = MapModelState::MMS_LOAD_FAILED;
			}
			else
			{
				if (IsModelVersionUnder105(obj))
					mMapModelStates[i] = MapModelState::MMS_VERSION_UNDER_105;
				else
					mMapModelStates[i] = MapModelState::MMS_OK;
			}

			for (int j = 0; j < 2; ++j)
			{
				if (j == 0)
				{
					sprintf_s(szItem, MAX_PATH - 1, "%s", obj_res->GetName());
				}
				else if (j == 1)
				{
					sprintf_s(szItem, MAX_PATH - 1, "%d", mex != NULL ? mex->GetVersion() : -1);
				}

				mList.SetItemText(i, j, szItem);
			}
		}
	}
}