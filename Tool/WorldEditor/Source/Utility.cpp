#include "stdafx.h"
#include "Utility.h"

BOOL Utility::IsFileExists(LPCTSTR file)
{
	WIN32_FIND_DATAA data;
	HANDLE hFinder = ::FindFirstFile(file, &data);
	if (hFinder != INVALID_HANDLE_VALUE)
	{
		::FindClose(hFinder);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL Utility::IsFileExistsInFolder(LPCTSTR fileToFind)
{
	CFileFind finder;
	BOOL found = finder.FindFile(fileToFind);
	finder.Close();
	return found;
}

void Utility::AdjustCameraComeCloseOrFaraway(UINT nFlags, short zDelta)
{
	Vector2 viewSize;
	CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return;

	Vector deltaPos;
	deltaPos.x	= zDelta / 32.0f;
	deltaPos.y  = 0.0f;
	deltaPos.z	= 0.0f;

	if (nFlags & MK_CONTROL)
	{
		deltaPos = deltaPos * 3;
	}

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
	Vector pos = camera->GetPos();
	D3DXVECTOR3 dDir = camera->GetDir();
	Vector kDir;
	kDir.x = dDir.x;
	kDir.y = dDir.y;
	kDir.z = dDir.z;
	pos	+= kDir * deltaPos.x;

	camera->SetPos( pos );
	camera->Update( 0.0f, 0.0f );
}

LONG WINAPI Utility::WorldEditor_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *lpExceptionFilter)
{
	SYSTEMTIME now;
	::GetLocalTime(&now);

	CString fileName;
	fileName.Format("WE_%d_%d_%d-%d_%d_%d.dmp", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

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