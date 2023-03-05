#include "StdAfx.h"
#include "DataCleanThread.h"

static const wxString NeedDeleteDirs[3] =
{
	wxT("Log"),
	wxT("Client\\Log"),
	wxT("Client\\UserData")
};

/*
 * Author:	2012-8-31 wangshuai
 * Desc: 	删除文件夹及文件夹内的所有文件
 */
void DeleteFolder(LPCWSTR folder)
{
	SHFILEOPSTRUCT fo;
	ZeroMemory(&fo,sizeof(SHFILEOPSTRUCT));

	wchar_t path[MAX_PATH];
	wcscpy_s(path, MAX_PATH - 1, folder);
	int pos = wcslen(path);
	path[pos] = 0;
	path[pos + 1] = 0;

	fo.fFlags = FOF_NOCONFIRMATION;
	fo.hNameMappings = NULL;
	fo.hwnd = NULL;
	fo.lpszProgressTitle = NULL;
	fo.pFrom = path;
	fo.pTo = NULL;
	fo.wFunc = FO_DELETE;
	SHFileOperation(&fo);
}

DataCleanThread::DataCleanThread(const wxString &dir, wxButton *button, wxTextCtrl *textCtrl, wxGauge *gauge)
	: mClientDir(dir), mButton(button), mTextCtrl(textCtrl), mProgressCtrl(gauge)
{

}

void * DataCleanThread::Entry()
{
	wxDir dir;
	wxArrayString filesUnderClientDir;
	wxArrayString result;
	dir.GetAllFiles(mClientDir, &filesUnderClientDir);

	// 清理指定文件夹
	for (int i = 0; i < 3; ++i)
	{
		wxString folder = mClientDir + wxT("\\") + NeedDeleteDirs[i];
		if (wxDirExists(folder))
		{
			DeleteFolder(folder.wc_str());
		}
	}

	// 清理文件
	wxFileName fn;
	wxString ext;

	mTextCtrl->Clear();
	mProgressCtrl->SetRange(filesUnderClientDir.GetCount() + 1);
	for (int i = 0; i < filesUnderClientDir.GetCount(); ++i)
	{
		fn.Assign(filesUnderClientDir.Item(i));
		ext = fn.GetExt();
		ext.MakeLower();
		if (ext == wxT("bak") || ext == wxT("db") || ext == wxT("log")
			|| ext == wxT("dmp") || ext == wxT("pdb") || ext == wxT("tga")|| ext == wxT("slk"))
		{
			wxRemoveFile(fn.GetFullPath());
		}
		else
		{
			continue;
		}

		result.Add(filesUnderClientDir.Item(i) + wxT("\n"));
		mTextCtrl->AppendText(filesUnderClientDir.Item(i) + wxT("\n"));
		mProgressCtrl->SetValue(i + 1);
	}

	if (result.GetCount() > 0)
	{
		wxFileDialog dlg(NULL, wxT("清理结果另存为"), wxT("D:\\"), wxT("客户端清理结果.txt"),
			wxT("Text Files (*.txt)|*.txt"), wxFD_SAVE);
		if (dlg.ShowModal() == wxID_OK)
		{
			FILE *fp = fopen(dlg.GetPath().mb_str(), "wt");
			if (fp != NULL)
			{
				for (int i = 0; i < result.GetCount(); ++i)
					fputs(result.Item(i).mb_str(), fp);
				fclose(fp);
			}
		}
	}	

	mButton->Enable();
	return NULL;
}