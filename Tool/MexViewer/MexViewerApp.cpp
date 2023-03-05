#include "StdAfx.h"
#include "MexViewerApp.h"

#include "MainFrame.h"

wchar_t gExeFolder[MAX_PATH] = {0};

LONG WINAPI MexViewer_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *lpExceptionFilter)
{
	SYSTEMTIME now;
	::GetLocalTime(&now);

	wchar_t fileName[MAX_PATH] = {0};
	wsprintf(fileName, L"%s\\MV_%d_%d_%d-%d_%d_%d.dmp", gExeFolder,
		now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

	HANDLE hDumpFile = ::CreateFile(fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	MINIDUMP_EXCEPTION_INFORMATION info;
	ZeroMemory(&info, sizeof(MINIDUMP_EXCEPTION_INFORMATION));
	info.ThreadId = ::GetCurrentThreadId();
	info.ExceptionPointers = lpExceptionFilter;
	info.ClientPointers = TRUE;

	::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hDumpFile,
		MiniDumpNormal, &info, NULL, NULL);
	::CloseHandle(hDumpFile);

	return EXCEPTION_EXECUTE_HANDLER;
}

IMPLEMENT_APP(MexViewerApp)

BEGIN_EVENT_TABLE(MexViewerApp, wxApp)
	EVT_ACTIVATE_APP(MexViewerApp::OnActiveApp)
END_EVENT_TABLE()

wxString MexViewerApp::GetExeFolder()
{
	wchar_t szFilePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szFilePath, MAX_PATH - 1);
	(wcsrchr(szFilePath, L'\\'))[0] = 0;
	return wxString(szFilePath);
}

bool MexViewerApp::OnInit()
{
	::SetUnhandledExceptionFilter(MexViewer_UnhandledExceptionFilter);

	if (!wxApp::OnInit())
		return false;

	MainFrame *gMainFrame = new MainFrame(wxT("Mex模型查看器"));
	gMainFrame->Show(true);

	wcscpy_s(gExeFolder, MAX_PATH - 1, this->GetExeFolder());
	return true;
}

int MexViewerApp::OnExit()
{
	return 0;
}

void MexViewerApp::OnActiveApp(wxActivateEvent &event)
{
	bool active = event.GetActive();
}