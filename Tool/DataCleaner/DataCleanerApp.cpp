#include "StdAfx.h"
#include "DataCleanerApp.h"

#include "MainFrm.h"

wchar_t gExeFolder[MAX_PATH] = {0};

LONG WINAPI DataCleaner_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *lpExceptionFilter)
{
	SYSTEMTIME now;
	::GetLocalTime(&now);

	wchar_t fileName[MAX_PATH] = {0};
	wsprintf(fileName, L"%s\\DataCleanerCrush_%d_%d_%d-%d_%d_%d.dmp", gExeFolder,
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

IMPLEMENT_APP(DataCleanerApp)

BEGIN_EVENT_TABLE(DataCleanerApp, wxApp)
EVT_ACTIVATE_APP(DataCleanerApp::OnActiveApp)
END_EVENT_TABLE()

wxString DataCleanerApp::GetExeFolder()
{
	wchar_t szFilePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szFilePath, MAX_PATH - 1);
	(wcsrchr(szFilePath, L'\\'))[0] = 0;
	return wxString(szFilePath);
}

bool DataCleanerApp::OnInit()
{
	::SetUnhandledExceptionFilter(DataCleaner_UnhandledExceptionFilter);

	if (!wxApp::OnInit())
		return false;

	MainFrame *gMainFrame = new MainFrame(wxT("Èý¹ú-DataCleaner"));
	gMainFrame->Show(true);

	wcscpy_s(gExeFolder, MAX_PATH - 1, this->GetExeFolder());
	return true;
}

int DataCleanerApp::OnExit()
{
	return 0;
}

void DataCleanerApp::OnActiveApp(wxActivateEvent &event)
{

}