#include "defines.h"

#include <math.h>
#include <CommDlg.h>

std::string GetOpenOrSaveFileNameEx(bool openFile, const char *szFilter)
{
	std::string filePath;

	char szFilePath[MAX_PATH] = {0};

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;

	if (openFile)
		ofn.lpstrTitle = "导入文件";
	else
		ofn.lpstrTitle = "导出文件";

	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = szFilePath;

	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST;
	if (!openFile)
		ofn.Flags |= OFN_FILEMUSTEXIST;

	if (openFile)
	{
		if (GetOpenFileName(&ofn))
			filePath = szFilePath;
	}
	else
	{
		if (GetSaveFileName(&ofn))
		{
			filePath = szFilePath;

			if (strnicmp(&filePath[filePath.size() - 4], ".mex", 4) != 0)
				filePath += ".mex";
		}
	}

	return filePath;
}

int FloatCmp( float a, float b)
{
	static const float PRECISION = 0.0001f;

	if (fabsf(a - b) < PRECISION)
		return 0;
	if (a < b)
		return -1;
	return 1;
}