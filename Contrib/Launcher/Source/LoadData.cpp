// #include "stdafx.h"
#include "MeRTLibs.h"
#include "shlwapi.h"
#include "LoadData.h"
#include <io.h>
#include "Cipher/cipher_factory.h"		//TO:袁丁 这里需要修改为你们自己的Cipher头文件
#include "fcntl.h"
#include "sys/stat.h"
#include "log4cpp/log4cpp_logger.h"

#define  ME_SET_CRT_DEBUG_FIELD(a) \
	_CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  ME_CLEAR_CRT_DEBUG_FIELD(a) \
	_CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#define ME_BEGIN_MEMORY_CHECK ME_SET_CRT_DEBUG_FIELD( _CRTDBG_DELAY_FREE_MEM_DF )
#define ME_END_MEMORY_CHECK ME_CLEAR_CRT_DEBUG_FIELD( _CRTDBG_DELAY_FREE_MEM_DF )
#define ME_MEMORY_CHECK if ( !_CrtCheckMemory() ) { LOG_MESSAGE( "ErrorInfo.log", LOG_PRIORITY_ERROR, "file:%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__); MessageBox( NULL, L"找程序", L"异常", MB_OKCANCEL );    }
namespace Launcher
{
	using namespace Cipher;
	static const std::string AudioName =		"\\Audio.package";
	static const std::string AvatarName =		"\\Avatar.package";
	static const std::string CharacterName =	"\\Character.package";
	static const std::string ConfigName =		"\\Config.package";
	static const std::string EffectName =		"\\Effect.package";
	static const std::string MagicName =		"\\Magic.package";
	static const std::string QuestName =		"\\Quest.package";
	static const std::string SceneName =		"\\Scene.package";
	static const std::string ShaderName =		"\\Shader.package";
	static const std::string TerrainName =		"\\Terrain.package";
	static const std::string TextureName =		"\\Texture.package";
	static const std::string UiName =			"\\Ui.package";
	static const std::string WorldName =		"\\World.package";

	void ReplaceAll(std::string& Input,std::string Search,std::string Format)
	{
		//先将 "/"替换为 "\",然后提放出现两个 "\\",再替换一下
		while (true)
		{
			int pos = Input.find(Search.c_str());
			if (pos == std::string::npos)
			{
				break;
			}
			Input = Input.replace(Input.find(Search.c_str()),Format.length(),Format);
		}
		while (true)
		{
			int pos = Input.find("\\\\");
			if (pos == std::string::npos)
			{
				break;
			}
			std::string temp = Input.substr(0, pos);
			temp += Input.substr(pos + 1);
			Input = temp;
			//Input = Input.replace(Input.find("\\\\"),Format.length(),Format);
		}
	}

	char MyToLower(char ch)
	{
		if(ch - 'A' < 26u)
			ch += 'a' - 'A';
		return ch;
	}

	void ToLow(std::string& Input)
	{
		char* temp = new char[Input.size() + 1];
		if(temp == NULL)
		{
			temp = new char[Input.size() + 1];
			if(temp == NULL)
				temp = new char[Input.size() + 1];
		}
		temp[Input.size()] = '\0';
		ZeroMemory(temp,Input.size());
		int num = Input.size();
		for (size_t i = 0 ; i < Input.size(); ++i)
		{
			temp[i] = MyToLower(Input[i]);
		}
		//Input.clear();
		Input = temp;
		Input = Input.substr(0,num);
		delete [] temp;
	}

	int FindFileOfDir(std::string respath, std::vector<std::string> &resVec)
	{
		if (!::PathFileExistsA(respath.c_str()))
		{
			//throw;
			return 1;
		}
// 		struct _finddata_t filefind;
// 		std::string  curr = respath + "\\*.package";
// 		int done = 0, handle; 
// 		if((handle = _findfirst(curr.c_str(),&filefind)) == -1)
// 			return;
// 		std::string fileName = filefind.name;
// 		curr = respath + "\\" + fileName;
// 		resVec.push_back(curr);
// 		while(!(done=_findnext(handle, &filefind)))
// 		{
// 			if(!strcmp(filefind.name,".."))
// 				continue;
// 			std::string fileName = filefind.name;
// 			curr = respath + "\\" + fileName;
// 			if((_A_SUBDIR == filefind.attrib))
// 			{
// 				//表示为文件夹,理论上不会出现该情况
// 				//FindFileOfDir(curr);
// 			}
// 			else
// 			{
// 				resVec.push_back(curr);
// 				//表示为文件
// 			}
// 		}
// 		_findclose(handle);
		std::string	name1 = respath + AudioName;
		std::string	name2 = respath + AvatarName;
		std::string	name3 = respath + CharacterName;
		std::string	name4 = respath + ConfigName;
		std::string	name5 = respath + EffectName;
		std::string	name6 = respath + MagicName;
		std::string	name7 = respath + QuestName;
		std::string	name8 = respath + SceneName;
		std::string	name9 = respath + ShaderName;
		std::string	name10 = respath + TerrainName;
		std::string	name11 = respath + TextureName;
		std::string	name12 = respath + UiName;
		std::string	name13 = respath + WorldName;
		resVec.push_back(name1);
		resVec.push_back(name2);
		resVec.push_back(name3);
		resVec.push_back(name4);
		resVec.push_back(name5);
		resVec.push_back(name6);
		resVec.push_back(name7);
		resVec.push_back(name8);
		resVec.push_back(name9);
		resVec.push_back(name10);
		resVec.push_back(name11);
		resVec.push_back(name12);
		resVec.push_back(name13);
		return 0;
	}

	ILoadData* GetLoadDataInstance()
	{
		static LoadData instance;
		return &instance;
	}

	bool GetFileInfo(std::string fileName, DWORD &fileLen, int &time)
	{
		HANDLE hDir = CreateFileA(fileName.c_str(), GENERIC_READ,FILE_SHARE_READ,NULL, OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS, NULL);
		if(hDir == INVALID_HANDLE_VALUE)
			return false;
		fileLen = GetFileSize(hDir, NULL);
		FILETIME lpCreationTime;	// 文件夹的创建时间
		FILETIME lpLastAccessTime;	// 对文件夹的最近访问时间
		FILETIME lpLastWriteTime;	// 文件夹的最近修改时间
		SYSTEMTIME stime;
		// 获取文件夹时间属性信息
		if(GetFileTime(hDir, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime))
		{
			FILETIME ftime;
			FileTimeToLocalFileTime(&lpLastWriteTime, &ftime);	// 转换成本地时间
			FileTimeToSystemTime(&ftime, &stime);				// 转换成系统时间格式
		}
		CloseHandle(hDir);
		time = stime.wDay * 10000 + stime.wHour * 100 + stime.wMinute;
		return true;
	}

	int	LoadData::CheckValidata(std::string mainDir, const std::vector<std::string> &resVec)
	{
		std::string validata_file = mainDir + "\\Launcher\\Validate.dat";
		if(!::PathFileExistsA(validata_file.c_str()))
			return 1;
		FILE *file = fopen(validata_file.c_str(), "r+b");
		if(file == NULL)
			return 2;
		fseek(file, 0, SEEK_END);
		long fileLen = ftell(file);
		if(fileLen > VALIDATEFILE_MAX_LEN)
		{
			fclose(file);
			return 3;
		}
		fseek(file, 0, SEEK_SET);
		char *readBuff = new char[fileLen];
		if(readBuff == NULL)
		{
			readBuff = new char[fileLen];
			if(readBuff == NULL)
			{
				fclose(file);
				return 4;
			}
		}
		fread(readBuff, 1, fileLen, file);
		fclose(file);
		//这里要多传入一个字节,作为结束标记
		unsigned char *outBuff = new unsigned char[fileLen + 1];
		if(outBuff == NULL)
		{
			outBuff = new unsigned char[fileLen + 1];
			if(outBuff == NULL)
			{
				delete []readBuff;
				return 5;
			}
		}
		ZeroMemory(outBuff, fileLen + 1);

		//Encrypt_File encrypt(0, S_ConfigVersion);
		//std::string key = encrypt.CreatKey(S_ConfigVersion);
		//encrypt.Decrypt((const unsigned char *)readBuff, fileLen, (unsigned char *)outBuff, key);

		DecoderInterface* decoder = CipherFactory::Instance().CreateDecoder(CIPHERTYPE_XOR, (const unsigned char*)S_ConfigVersion.c_str(), S_ConfigVersion.length());
		try
		{
			decoder->Decode((const unsigned char*)S_ConfigVersion.c_str(), S_ConfigVersion.length(),outBuff, (const unsigned char*)readBuff, fileLen);
		}
		catch(...)
		{
			delete []readBuff;
			delete []outBuff;
			CipherFactory::Instance().ReleaseDecoder(&decoder);
			return 6;
		}
		CipherFactory::Instance().ReleaseDecoder(&decoder);

		//开始读取解析数据
		UpdataPackageMap updataPackageMap;
		int ret = ParseValue((char*)outBuff, updataPackageMap);
		delete []readBuff;
		delete []outBuff;
		if(ret != 0)
			return ret;
		ret = CompareValue(resVec, updataPackageMap);
		return ret;
	}

	int	LoadData::ParseValue(std::string readData, UpdataPackageMap &updataPackageMap)
	{
		int num = 0;
		std::string readDataTemp = readData;
		if(readDataTemp.find("\n") == std::string::npos || readDataTemp.find("|") == std::string::npos)
			return 1;
		std::string fileName;
		try
		{
			while(readDataTemp.length() > 1)
			{
				std::string subString = readDataTemp.substr(0, readDataTemp.find("\n"));
				if(subString.find("|") == std::string::npos)
					return 2;
				fileName = subString.substr(0, subString.find("|"));
				updataPackageMap.insert(UpdataPackageMap::value_type(fileName, subString.substr(fileName.length() + 1)));
				readDataTemp = readDataTemp.substr(subString.length() + 1);
			}
		}
		catch(std::exception &e)
		{
			e.what();
			return 2;
		}
		return 0;
	}

	int	LoadData::CompareValue(std::vector<std::string> updataList, UpdataPackageMap &updataPackageMap)
	{
		UpdataPackageMap::iterator firstit = updataPackageMap.find(IS_UPData);
		if(firstit == updataPackageMap.end())
			return 1;

		std::string fileName;
		DWORD		fileLen = 0;
		int			time = 0;
		char		outBuff[100] = {0};
		//Launcher的验证没有验证Client\config.package
		for(unsigned int i = 1; i < updataList.size(); i++)
		{
			ZeroMemory(outBuff, 100);
			fileName = updataList[i];
			GetFileInfo(fileName, fileLen, time);
			sprintf(outBuff, "%d|%d", fileLen, time);
			ToLow(fileName);
			if(fileName.find("data") == std::string::npos)
				return 2;
			std::string subFileName = fileName.substr(fileName.rfind("data"));
			UpdataPackageMap::iterator fileit = updataPackageMap.find(subFileName);
			if(fileit == updataPackageMap.end())
				return 3;
			if((*fileit).second.compare(outBuff) != 0)
				return 4;
		}
		return 0;
	}
	
	/************************************************************************/
	/* to:袁丁
		原来定义的mainDIr是带 Data目录的,例如 F:\\HeroClient\\Data
		现在由于需要将Client目录下的Config文家打包后的Config.package文件也添加到Map里面去
		所以现在将传入的 mainDir修改为不带 Data的,例如 F:\\HeroClient
		现在 Config.package放入到Map中后, 你调用 GetFileHandle时候,传入的名称格式为 : iLoad->GetFileHandle("config\filterstring.configc", fp1);等
		void LoadData::stripString( std::string &resfile ,std::string& subString )函数也修改了
	*/
	/************************************************************************/
	int LoadData::SetMainDir(std::string mainDir, std::string tempPath, int& nRetErrorFile)
	{
		CSALocker lock(m_Lock);
		m_tempPath = tempPath;
		m_tempPath = tempPath;
		std::string openfile = mainDir + "\\Data";
		std::string configFile = mainDir + "\\Client\\Config.package";
		//测试
		// 		openfile += "\\data\\";
		//应该是遍历该目录下的package文件
		std::vector<std::string> resVec;
		//把这个提前,想最早验证Client\\Config.package,如果这个发生错误,可以当做附件发回
		int nRet = 0;
		//将nErrFile提前,如果返回-1,表示为验证错误,并且还可以判断CreateFileA时候的错误
		int nErrFile = -1;
		if(PathFileExistsA(configFile.c_str()))
			resVec.push_back(configFile);
		if(resVec.size() == 0)
		{
			nRet = 100;
			goto MainDir_End;
		}
		if(FindFileOfDir(openfile, resVec) != 0)
		{
			nRet = 101;
			goto MainDir_End;
		}
		//在这里添加验证的代码,因为只做简单验证,所以不需要将ValidateFile.cpp添加进来
		if(CheckValidata(mainDir, resVec) != 0)
		{
			nRet = 99;
			goto MainDir_End;
		}
		for(unsigned int i = 0; i < resVec.size(); i++)
		{
			nErrFile = i;
			hrFile = CreateFileA(resVec[i].c_str(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hrFile == INVALID_HANDLE_VALUE)
			{
				nRet = 102;
				goto MainDir_End;
			}
			hrFileMap = CreateFileMappingA(hrFile,NULL,PAGE_READONLY,0,0,NULL);
			if(hrFileMap == NULL)
			{
				CloseHandle(hrFile);
				nRet = 103;
				goto MainDir_End;
			}
			DHandle tempDH;
			tempDH.hrFile = hrFile;
			tempDH.hrFileMap = hrFileMap;
			m_DHvec.push_back(tempDH);
		}
		//openfile += "\\data\\UI.afx";
		//hrFile = CreateFileA(openfile.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		//if(hrFile == INVALID_HANDLE_VALUE)
		//{
		//	return false;
		//}
		//hrFileMap = CreateFileMappingA(hrFile,NULL,PAGE_READONLY,0,0,NULL);
		//if(hrFileMap == NULL)
		//{
		//	CloseHandle(hrFile);
		//	return false;
		//}
		//DHandle tempDH;
		//tempDH.hrFile = hrFile;
		//tempDH.hrFileMap = hrFileMap;
		//m_DHvec.push_back(tempDH);
		nErrFile = 0;
		nRet = GetMAp(nErrFile);
MainDir_End:
		if(nRet != 0)
		{
			char temp[2048] = {0};
			sprintf(temp,"加载数据包出错（%d），建议重新下载客户端并安装在一个全新的目录下！",nRet);

			::MessageBoxA(NULL,temp,"一骑当千",MB_OK);
			//这里可以根据返回值记录错误,是发邮件,或客户端处理,这里需要你们配合
			//现在又添加了一个错误的值,就是nErrFile...返回值0,1,2,3...分别对应着enum GetMapErrorFile里面说明的文件,现在把Client//Config特意放到第一的位置,为了发生附件
			nRetErrorFile = nErrFile;
			return nRet;
		}
		return 0;
	}
	
	void* LoadData::FindFirst(std::string resDir, std::string suffix, std::string &resStr)
	{
		CSALocker lock(m_Lock);
		std::string subString;
		stripString(resDir,subString);
		if(subString.length() == 0)
			return false;
		void *handle = GetFileHandVec(subString, suffix);
		if(handle == NULL)
			return NULL;
		FileVecMap::iterator fileit = m_fileVecMap.find(handle);
		if(fileit == m_fileVecMap.end())
		{
			return NULL;
		}
		std::vector<std::string> fileDirVec = (*fileit).second.fileDirVec;
		DWORD dirIndex = (*fileit).second.dirIndex;
		if(fileDirVec.size())
		{
			resStr = fileDirVec[dirIndex];
			(*fileit).second.dirIndex++;
		}
		else
			return NULL;
		return handle;
	}

	bool LoadData::FindNext(void *point,std::string &resStr)
	{
		CSALocker lock(m_Lock);
		FileVecMap::iterator fileit = m_fileVecMap.find(point);
		if(fileit == m_fileVecMap.end())
		{
			return false;
		}
		std::vector<std::string> fileDirVec = (*fileit).second.fileDirVec;
		DWORD dirIndex = (*fileit).second.dirIndex;
		if(fileDirVec.size())
		{
			if(fileDirVec.size() == dirIndex)
				return false;
			resStr = fileDirVec[dirIndex];
			(*fileit).second.dirIndex++;
		}
		else
			return false;
		return true;
	}
	
	void LoadData::FindClose(void*point)
	{
		CSALocker lock(m_Lock);
		FileVecStruct* pFileVecS = (FileVecStruct*)point;
		FileVecMap::iterator fileit = m_fileVecMap.find(pFileVecS);
		if(fileit == m_fileVecMap.end())
		{
			return;
		}
		m_fileVecMap.erase(fileit);
		//释放内存
		delete pFileVecS;
		point = NULL;
	}

	void* LoadData::GetFileHandVec(std::string resDir, std::string suffix)
	{
		std::vector<std::string> fileDirVec;
		DWORD dirIndex = 0;
		ReplaceAll(resDir,"/","\\");
		ToLow(resDir);
		STRFBMAP::iterator it1 = mFBlckMap.upper_bound(resDir);
		for(; it1 != mFBlckMap.end(); it1++)
		{
			std::string pathName = (*it1).first;
			//如果名字匹配不正确,返回
			if(pathName.find(resDir) == std::string::npos)
				break;
			//如果后缀名相同,插于到vector内
			std::string suffixTemp = pathName.substr(pathName.rfind("."));
			if(suffixTemp.compare(suffix) == 0)
				fileDirVec.push_back((*it1).first);
		}
		if(fileDirVec.size() == 0)
			return NULL;
		FileVecStruct *fileVec = new FileVecStruct(fileDirVec, dirIndex);
		m_fileVecMap.insert(FileVecMap::value_type(fileVec, *fileVec));
		return fileVec;
	}

	bool LoadData::GetFileHandle(std::string resfile, FILE *&fileHand)
	{
// 		ME_BEGIN_MEMORY_CHECK;
		CSALocker lock(m_Lock);
		size_t fileSize = 0;
		char *fileData = NULL;
		//在调用GetData时候,要将 resfile先转换为相当路径
		std::string subString;
		stripString(resfile,subString);
		if(subString.length() == 0)
			return false;
		//
		DChange dChange;
		if(!GetData(subString, fileSize, fileData, dChange))
		{
			// 			OutputDebugStringA(subString.c_str());
			// 			OutputDebugStringA("            LOAD FAIL!");
			// 			OutputDebugStringA("\n");
			return false;
		}
		if(m_tempPath.size())
		{
			char* name2 = NULL;
			if((name2 = _tempnam(m_tempPath.c_str(), "stq" ) ) != NULL )  //这里创建临时文件可能失败，比如管理权限不够
			{
//  				fh = _sopen(name2,_O_CREAT|_O_SHORT_LIVED, _SH_DENYWR ,
//  					_S_IREAD | _S_IWRITE );
  				fileHand = fopen(name2, "wb+D");
  				if(!fileHand)
  					return false;
//  				fileHand = fdopen(fh, "wb+DT");
				free(name2);
			}
		}
		if(!fileHand)
			return false;

		//fileHand = tmpfile();
		if (m_FlushTmpToDisk)
		{
			fwrite(fileData, 1, fileSize, fileHand);
			fseek ( fileHand, 0, SEEK_SET );
		}
		else
		{
			setvbuf(fileHand,fileData,_IOFBF,fileSize + 1 );
			fileHand->_cnt = fileSize;
//  			fwrite(fileData, 1, fileSize, fileHand);
			fileHand->_ptr = fileHand->_base;
			fseek ( fileHand, 0, SEEK_SET );
			fileHand->_cnt = fileSize;
		}
		dChange.hFileHand = fileHand;
		m_fileHandVec.push_back(dChange);
// 		ME_MEMORY_CHECK
// 			ME_END_MEMORY_CHECK;
		return true;
	}

	bool LoadData::IsInMap(FILE *fileHand)
	{
		CSALocker lock(m_Lock);
		HANDLEVEC::const_iterator handIte = m_fileHandVec.begin();
		for(; handIte != m_fileHandVec.end(); ++handIte)
		{
			if((*handIte).hFileHand == fileHand)
				return true;
		}
		//HANDLEMAP::iterator it = m_handleMap.find(fileHand);
		//if (it == m_handleMap.end())
		//{
		//	return false;
		//}
		return false;
	}
#define _IOYOURBUF 0x0100
	void LoadData::Close(FILE *fileHand)
	{
		//HANDLEMAP::iterator it = m_handleMap.find(fileHand);
		//if (it == m_handleMap.end())
		//{
		//	return;
		//}
		//fclose(it->first);
		//m_handleMap.erase(it);
// 		ME_BEGIN_MEMORY_CHECK;
		CSALocker lock(m_Lock);
		HANDLEVEC::iterator handIte;
		for(handIte = m_fileHandVec.begin(); handIte != m_fileHandVec.end(); ++handIte)
		{
			if((*handIte).hFileHand == fileHand)
			{
				PVOID hrFileP = (*handIte).hrFileP;
				m_fileHandVec.erase(handIte);
				UnmapViewOfFile(hrFileP);
				fclose(fileHand);
// 				if (fileHand->_flag&_IOYOURBUF)
// 				{
// 					if (fileHand->_base)
// 					{
// 						delete [] fileHand->_base;
// 					}
// 				}
				break;
			}
			//return true;
		}
// 		ME_MEMORY_CHECK
// 			ME_END_MEMORY_CHECK;
	}

	void LoadData::Clear()
	{
		CSALocker lock(m_Lock);
		//for (size_t i = 0 ; i < m_mappedfile.size() ; ++i)
		//{
		//	UnmapViewOfFile(m_mappedfile[i]);
		//}
		//m_mappedfile.clear();
		for(size_t i = 0 ; i < m_DHvec.size() ; ++i)
		{
			CloseHandle(m_DHvec[i].hrFileMap);
			CloseHandle(m_DHvec[i].hrFile);
		}
		m_DHvec.clear();
		//删除m_fileHandVec
		HANDLEVEC::iterator handIte;
		for(handIte = m_fileHandVec.begin(); handIte != m_fileHandVec.end(); ++handIte)
		{
			FILE *fileHand = (*handIte).hFileHand;
			fclose(fileHand);
			UnmapViewOfFile((*handIte).hrFileP);
		}
		m_fileHandVec.clear();
		//删除FileVecMap
		FileVecMap::iterator fileit;
		for(fileit = m_fileVecMap.begin(); fileit != m_fileVecMap.end(); ++fileit)
		{
			delete (*fileit).first;
		}
		m_fileVecMap.clear();
	}

	//主要修改了GetMap这个函数,同时阅读代码后,在MapViewOfFile的时候,也加入了重试的机制,还有就是在我这边Launcher升级过程中发现的一些可能出现异常的地方加了异常处理
	//对异常的处理方法,已经对错误信息的弹出,你们那边可以加以修改
	int LoadData::GetMAp(int &nErrFile)
	{
		SYSTEM_INFO psi;
		GetSystemInfo(&psi);
		m_alignment = psi.dwAllocationGranularity;
		for(size_t i = 0; i < m_DHvec.size(); ++i)
		{
			nErrFile = i;
			int nCount = 0;
			PVOID pvFile = NULL;
			while(pvFile == NULL && nCount < 10)
			{
				++nCount;
				pvFile = MapViewOfFile(m_DHvec[i].hrFileMap,FILE_MAP_READ,0,0,sizeof(AfxFileHead));
				if (pvFile == NULL)
				{
					Sleep(1);
				}
			}
			if(pvFile == NULL)
			{
				return 1;
			}
			AfxFileHead newHead;
			ZeroMemory(&newHead, sizeof(AfxFileHead));
			int alignum = 0;
			int aligoff = 0;
			//这个地方的memcpy有可能发生异常,Launcher里面发现个类似的问题,并且这里的循环次数就13次,用try catch不会造成效率问题.
			try
			{
				memcpy(&newHead,pvFile, sizeof(AfxFileHead));
			}
			catch(...)
			{
				UnmapViewOfFile(pvFile);
				return 2;
			}
			alignum = newHead.TableOffset / m_alignment;
			aligoff = newHead.TableOffset % m_alignment;

			UnmapViewOfFile(pvFile);
			/************************************************************************/
			/*
			TO:袁丁
			这里为主要修改地方,需要将加密的文件索引解析处理,存放到Map里面
			需要使用Chiper库,加解密的方法是异或 xor算法,解密的 key的算法已经定义

			*/
			/************************************************************************/
			if(newHead.EncryptType == '1')
			{
				PVOID pvFile_ = NULL;
				nCount = 0;
				while(pvFile_ == NULL && nCount < 10)
				{
					++nCount;
					pvFile_ = MapViewOfFile(m_DHvec[i].hrFileMap,FILE_MAP_READ,0,alignum * m_alignment,aligoff + newHead.FileCount * sizeof(AfxFileItem));
					if (pvFile_ == NULL)
					{
						Sleep(1);
					}
				}
				if(pvFile_ == NULL)
				{
					return 3;
				}

				DWORD fileItemsLen = sizeof(AfxFileItem) * newHead.FileCount;
				unsigned char *outBuff = new unsigned char[fileItemsLen];
				if(outBuff == NULL)
				{
					outBuff = new unsigned char[fileItemsLen];
					if(outBuff == NULL)
					{
						outBuff = new unsigned char[fileItemsLen];
						if(outBuff == NULL)
						{
							UnmapViewOfFile(pvFile_);
							return 4;
						}
					}
				}
				std::string key = CreatKey(newHead.Version);
				if(key.length() < 2)
				{
					delete []outBuff;
					outBuff = NULL;
					UnmapViewOfFile(pvFile_);
					return 5;
				}
				DecoderInterface* decoder = CipherFactory::Instance().CreateDecoder(CIPHERTYPE_XOR, (const unsigned char*)key.c_str(), key.length());
				//我上面的解密也是可行的,但还是用你们改的先,解密理论上讲可能会碰到异常的,不知道你们那边碰到过没.
				try
				{
					decoder->Decode((const unsigned char*)key.c_str(), key.length(),outBuff, (const unsigned char*)pvFile_ + aligoff, fileItemsLen);
					//decoder->Decode(outBuff, (const unsigned char*)pvFile_ + aligoff, fileItemsLen);
				}
				catch(...)
				{
					delete []outBuff;
					outBuff = NULL;
					UnmapViewOfFile(pvFile_);
					CipherFactory::Instance().ReleaseDecoder(&decoder);
					return 6;
				}
				//在这里就能 UnmapViewOfFile
				UnmapViewOfFile(pvFile_);
				//const AfxFileItem* ptr = (const AfxFileItem*)((char*)pvFile_ + aligoff);
				const AfxFileItem* ptr = (const AfxFileItem*)outBuff;
				//这里就是你们说的报错的地方了.加入异常处理吧
				try
				{
					for(DWORD j = 0; j < newHead.FileCount; ++j)
					{
						//构建Map的时候,先将没有被使用的去除
						if(ptr[j].WeaUse == '0')
							continue;
						FileBlock newBlock;
						memset(&newBlock,0,sizeof(FileBlock));
						newBlock.offset		= ptr[j].FileOffset;
						newBlock.size		= ptr[j].FileSize;
						newBlock.dHandle    = m_DHvec[i];
						std::string tempstring = ptr[j].FileName;
						if(tempstring.length() == 0 || tempstring.length() > 260)
						{
							delete []outBuff;
							outBuff = NULL;
							CipherFactory::Instance().ReleaseDecoder(&decoder);
							return 7;
						}
						ToLow(tempstring);
						mFBlckMap.insert(STRFBMAP::value_type(tempstring,newBlock));
					}
				}
				catch(...)
				{
					delete []outBuff;
					outBuff = NULL;
					CipherFactory::Instance().ReleaseDecoder(&decoder);
					return 8;
				}
				CipherFactory::Instance().ReleaseDecoder(&decoder);
				delete []outBuff;
				outBuff = NULL;
			}
			else
			{

				//const AfxFileItem* ptr = (const AfxFileItem*)((char*)pvFile_ + aligoff);
				//for(DWORD j = 0; j < newHead.FileCount; ++j)
				//{
				//	//构建Map的时候,先将没有被使用的去除
				//	if(ptr[j].WeaUse == '0')
				//		continue;
				//	FileBlock newBlock;
				//	memset(&newBlock,0,sizeof(FileBlock));
				//	newBlock.offset		= ptr[j].FileOffset;
				//	newBlock.size		= ptr[j].FileSize;
				//	newBlock.dHandle    = m_DHvec[i];
				//	std::string tempstring = ptr[j].FileName;
				//	ToLow(tempstring);
				//	mFBlckMap.insert(STRFBMAP::value_type(tempstring,newBlock));
				//}
				//这里应该用不到,这是为了兼容很久以前的不加密的版本..现在都是加密的版本,除非认为修改
				return 9;
			}
		}
		return 0;
	}

	bool LoadData::GetData(std::string resfile, size_t &size, char *&filedata, DChange &dChange)
	{
		//ReplaceAll(resfile,"/","\\");
		//ToLow(resfile);
		//GetMAp();
		STRFBMAP::iterator it = mFBlckMap.find(resfile);
		if (it == mFBlckMap.end())
		{
			return false;
		}
		int alignum = it->second.offset / m_alignment;
		int aligoff = it->second.offset % m_alignment;

		size = it->second.size;
		
		PVOID pvFile = NULL;
		int nCount = 0;
		while(pvFile == NULL && nCount < 10)
		{
			++nCount;
			pvFile = MapViewOfFile(it->second.dHandle.hrFileMap,FILE_MAP_READ,0,alignum * m_alignment,aligoff + it->second.size);
			if (pvFile == NULL)
			{
				Sleep(1);
			}
		}
		if (pvFile == NULL)
		{
			return false;
		}
		filedata = ((char*)pvFile + aligoff);
		dChange.hrFileP = pvFile;
		//m_mappedfile.push_back(pvFile);
		return true;
	}
	bool LoadData::m_locked = false;
	LoadData::LoadData()
	{
		hrFile = NULL;
		hrFileMap = NULL;
		m_alignment = 0;
	}

	LoadData::~LoadData()
	{
		Clear();
	}
	
	void LoadData::stripString( std::string &resfile ,std::string& subString )
	{
		ReplaceAll(resfile,"/","\\");
		//PathRelativePathTo
		ToLow(resfile);
		std::string::size_type indexCh;
		indexCh = resfile.rfind("data\\");
		if (indexCh != std::string::npos )
		{
			subString = resfile.substr(indexCh);
			return;
		}
		else
		{
			indexCh = resfile.rfind("config\\");
			if (indexCh != std::string::npos )
			{
				subString = resfile.substr(indexCh);
			}
		}
	}

	std::string LoadData::CreatKey(std::string inKey)
	{
		int strLen = inKey.length();
		const char *key = inKey.c_str();
		char *temp = new char[strLen + 1];
		if(temp == NULL)
		{
			temp = new char[strLen + 1];
			if(temp == NULL)
			{
				temp = new char[strLen + 1];
				if(temp == NULL)
					return "";
			}
		}
		temp[strLen] = '\0';
		for(int i = strLen - 1; i >= 0; i--)
			temp[i] = *key++;
		std::string ret = temp;
		delete []temp;
		return ret;
	}

	bool LoadData::IsFileExist( std::string &resfile )
	{
		CSALocker lock(m_Lock);
		//在调用GetData时候,要将 resfile先转换为相当路径
		std::string subString;
		stripString(resfile,subString);
		if(subString.length() == 0)
			return false;
		STRFBMAP::iterator it = mFBlckMap.find(subString);
		if (it == mFBlckMap.end())
		{
			return false;
		}
		return true;
	}
}
