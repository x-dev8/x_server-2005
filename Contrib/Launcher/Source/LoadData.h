#ifndef __LOAD_DATA_H__
#define __LOAD_DATA_H__
#include <string>
#include <map>
#include <vector>
#include <Windows.h>
#include "struct.h"
#include "ILoadData.h"
#include "Mutex.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//struct FileBlock
//{
//	size_t offset;
//	size_t size;
//};
//typedef std::map<std::string , FileBlock> STRFBMAP;
//typedef std::vector<PVOID> PVVEC;

//
namespace Launcher
{
	#define			VALIDATEFILE_MAX_LEN		1024
	const static std::string S_ConfigVersion	= "0.0.0.1";
	const static std::string IS_UPData			= "isupdata";

	typedef std::map<std::string, std::string>	UpdataPackageMap;

	enum GetMapErrorFile
	{
		Err_Client_Config = 0,
		Err_Data_Audio,
		Err_Data_Avatar,
		Err_Data_Character,
		Err_Data_Config,
		Err_Data_Effect,
		Err_Data_Magic,
		Err_Data_Quest,
		Err_Data_Scene,
		Err_Data_Shader,
		Err_Data_Terrain,
		Err_Data_Texture,
		Err_Data_Ui,
		Err_Data_World,
	};

	void ReplaceAll(std::string& Input,std::string Search,std::string Format);

	void ToLow(std::string& Input);

	bool GetFileInfo(std::string fileName, DWORD &fileLen, int &time);

	struct DHandle
	{
		HANDLE hrFile;
		HANDLE hrFileMap;
	};

	struct FileBlock 
	{
		size_t			offset;
		size_t			size;
		DHandle			dHandle;
	};
	typedef std::map<std::string , FileBlock> STRFBMAP;
	typedef std::vector<PVOID> PVVEC;

	typedef std::map<FILE*, std::string>	HANDLEMAP;
	typedef std::vector<DHandle>			DHVec;	
	//修改
	struct DChange
	{
		FILE* hFileHand;
		PVOID hrFileP;
	};
	typedef std::vector<DChange>				HANDLEVEC;
	//
	struct FileVecStruct
	{
		std::vector<std::string>	fileDirVec;
		DWORD						dirIndex;
		FileVecStruct(std::vector<std::string> dirVec, DWORD index)
			:fileDirVec(dirVec), dirIndex(index){}
	};
	typedef std::map<void *, FileVecStruct> FileVecMap;

	class LoadData : virtual public ILoadData
	{
	public:
		LoadData();
		~LoadData();
		virtual int SetMainDir(std::string mainDir, std::string tempPath, int& nRetErrorFile);
		virtual void* FindFirst(std::string resDir, std::string suffix, std::string &resStr);
		virtual bool FindNext(void *point,std::string &resStr);
		virtual void FindClose(void *point);
		virtual bool GetFileHandle(std::string resfile, FILE *&fileHand);

		void stripString( std::string &resfile ,std::string& subString);
		virtual bool IsInMap(FILE *fileHand);
		virtual void Close(FILE *fileHand);
		virtual void Clear();
		virtual void SetFlushTmpToDisk(bool bValue)
		{
			m_FlushTmpToDisk = bValue;
		}
		virtual bool IsFileExist(std::string &resfile);
		//static ILoadData* GetLoadDataInstance();
	protected:
		void* GetFileHandVec(std::string resDir, std::string suffix);
		bool GetData(std::string resfile,size_t& size,char*& filedata, DChange &dChange);
		int GetMAp(int &nErrFile);
		//产生Key,仅仅将Version翻转
		std::string CreatKey(std::string inKey);
		//添加验证
		int	CheckValidata(std::string mainDir, const std::vector<std::string> &resVec);
		int	ParseValue(std::string readData, UpdataPackageMap &updataPackageMap);
		int	CompareValue(std::vector<std::string> updataList, UpdataPackageMap &updataPackageMap);

	private:
		HANDLE			hrFile;
		HANDLE			hrFileMap;
		//PVOID			pvFile;
		STRFBMAP		mFBlckMap;
		DWORD			m_alignment;
        CSemiAutoIntLock m_Lock;
		//PVVEC			m_mappedfile;
		//
		//HANDLEMAP		m_handleMap;
		std::string		m_tempPath;
		DHVec			m_DHvec;
		static bool		m_locked;
		HANDLEVEC		m_fileHandVec;
		//存放一个目录文件下的文件名
		FileVecMap		m_fileVecMap;
		bool			m_FlushTmpToDisk;
		//std::vector<std::string> m_fileDirVec;
		//DWORD			m_dirIndex;
	};
}

#endif