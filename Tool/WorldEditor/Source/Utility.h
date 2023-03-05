#pragma once

#pragma auto_inline (off)

#include <DbgHelp.h>
#pragma comment( lib, "DbgHelp.lib")

namespace Utility
{
	/*
	 * 文件是否存在
	 */
	BOOL IsFileExists(LPCTSTR file);

	/*
	 * 文件是否存在于指定目录中,
	 * 注意: 本函数不搜索子目录
	 */
	BOOL IsFileExistsInFolder(LPCTSTR fileToFind);

	/*
	 * 调整摄像机远近
	 */
	void AdjustCameraComeCloseOrFaraway(UINT nFlags, short zDelta);

	/*
	 * 未处理异常过滤
	 */
	LONG WINAPI WorldEditor_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *lpExceptionFilter);
}