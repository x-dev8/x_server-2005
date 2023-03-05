#pragma once

#pragma auto_inline (off)

#include <DbgHelp.h>
#pragma comment( lib, "DbgHelp.lib")

namespace Utility
{
	/*
	 * �ļ��Ƿ����
	 */
	BOOL IsFileExists(LPCTSTR file);

	/*
	 * �ļ��Ƿ������ָ��Ŀ¼��,
	 * ע��: ��������������Ŀ¼
	 */
	BOOL IsFileExistsInFolder(LPCTSTR fileToFind);

	/*
	 * ���������Զ��
	 */
	void AdjustCameraComeCloseOrFaraway(UINT nFlags, short zDelta);

	/*
	 * δ�����쳣����
	 */
	LONG WINAPI WorldEditor_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *lpExceptionFilter);
}