#include "7zExtra.h"
#include "7zAlloc.h"
#include "7zFile.h"
#include "7zCrc.h"
#include <stdio.h>

SRes ExtraFile(const char* inFile, const char* outFile)
{
	try
	{
		if (!inFile || !outFile)
		{
			return SZ_ERROR_DATA;
		}

		ISzAlloc allocImp = {SzAlloc, SzFree};
		ISzAlloc allocTempImp = {SzAllocTemp, SzFreeTemp};

		CFileInStream archiveStream;
		CLookToRead lookStream;

		if (InFile_Open(&archiveStream.file, inFile))
		{
			return SZ_ERROR_INPUT_EOF;
		}

		FileInStream_CreateVTable(&archiveStream);
		LookToRead_CreateVTable(&lookStream, False);

		lookStream.realStream = &archiveStream.s;
		LookToRead_Init(&lookStream);

		lookStream.realStream = &archiveStream.s;
		LookToRead_Init(&lookStream);

		CrcGenerateTable();

		CSzArEx db;
		SzArEx_Init(&db);

		if (SzArEx_Open(&db, &lookStream.s, &allocImp, &allocTempImp) != SZ_OK)
		{
			return SZ_ERROR_INPUT_EOF;
		}

		UInt32 blockIndex = 0xFFFFFFFF;
		Byte *outBuffer = 0;
		size_t outBufferSize = 0;
		size_t offset = 0;
		size_t outSizeProcessed = 0;

		if (SzArEx_Extract(&db, &lookStream.s, 0, &blockIndex, &outBuffer, &outBufferSize, &offset, &outSizeProcessed, &allocImp, &allocTempImp))
		{
			return SZ_ERROR_PROGRESS;
		}

		FILE* fWriteExtraFile = NULL;
		if (fopen_s(&fWriteExtraFile, outFile, "wb") != 0)
		{
			return SZ_ERROR_OUTPUT_EOF;
		}

		fwrite(outBuffer, sizeof(Byte), outSizeProcessed, fWriteExtraFile);

		fclose(fWriteExtraFile);

		IAlloc_Free(&allocImp, outBuffer);

		SzArEx_Free(&db, &allocImp);

		File_Close(&archiveStream.file);

		return SZ_OK;
	}
	catch (...)
	{
		return SZ_OK;
	}
}