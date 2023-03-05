#ifndef __I_LOAD_DATA_H__
#define __I_LOAD_DATA_H__
#include <string>
namespace Launcher
{
	class ILoadData
	{
	public:
		virtual int SetMainDir(std::string mainDir, std::string tempPath, int& nRetErrorFile) =0;
		virtual void* FindFirst(std::string resDir, std::string suffix, std::string &resStr)=0;
		virtual bool FindNext(void*point,std::string &resStr)=0;
		virtual void FindClose(void*point)=0;
		virtual bool GetFileHandle(std::string resfile, FILE *&fileHand)=0;
		virtual bool IsInMap(FILE *fileHand)=0;
		virtual void Close(FILE *fileHand)=0;
		virtual void Clear()=0;
		virtual void SetFlushTmpToDisk(bool bValue)=0;
		virtual bool IsFileExist(std::string &resfile) = 0;
	};

	extern ILoadData* GetLoadDataInstance();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#endif