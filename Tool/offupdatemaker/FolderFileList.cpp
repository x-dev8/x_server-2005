#include "StdAfx.h"
#include "md5.h"
#include "FolderFileList.h"
#include <direct.h>
#include "ZipWrapper.h"


#define  ID_RESOURCE_LIST 1
extern void SetError(CString str);
extern void SetTip(CString str);
extern void SetProgress(int pos);

using FileIO::CZipWrapper;
FILE *stream;

bool MakeEmbedFolder(string strFolderPath)
{
	string  strPath = strFolderPath;
	if (strPath[strPath.length()-1] != _T('\\'))
	{
		strPath += _T("\\");
	}
	size_t nLength = strPath.length();
	for (size_t i = 0; i<nLength; i++)
	{
		if (strPath[i] == _T('\\'))
		{
			string strFolder = strPath.substr(0, i);
			if (_mkdir(strFolder.c_str()) == ENOENT)
			{
				return false;
			}
		}
	}
	return true;
}

//分离文件名
string GetFileName(string strFilePath)
{
//	strFilePath.Replace(_T("/"), _T("\\"));
	size_t nLength = strFilePath.length();
	size_t nPos = 0;
	for (size_t i = nLength; i>0; i--)
	{
		if (strFilePath[i-1] == _T('\\'))
		{
			nPos = i;
			break;
		}
	}
	string strFileName = strFilePath.substr(nPos, strFilePath.length()-nPos);
	return strFileName;
}
BOOL ResourceOUT(string strFileName,WORD wResID,CString strFileType,bool log=true) 
{ 
	// 资源大小 
	DWORD        dwWrite=0;                
	// 创建文件 
	HANDLE        hFile = CreateFile(strFileName.c_str(), GENERIC_WRITE,FILE_SHARE_WRITE,NULL, 
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
	if ( hFile == INVALID_HANDLE_VALUE ) 
	{ 
		return FALSE; 
	} 

	// 查找资源文件中、加载资源到内存、得到资源大小 
	HRSRC        hrsc =  FindResource(NULL, MAKEINTRESOURCE(wResID), strFileType); 
	if(log){if(!hrsc)fprintf( stream,"找不到资源文件","\n");}
	HGLOBAL hG = LoadResource(NULL, hrsc); 
	
	//锁定资源

	LPVOID pBuffer = LockResource(hG); 

	if (NULL == pBuffer)
        return FALSE;
	if(log){if(!hG)fprintf( stream,"加载资源失败","\n");}
	DWORD        dwSize = SizeofResource( NULL,  hrsc); 

	// 写入文件 
	WriteFile(hFile,hG,dwSize,&dwWrite,NULL);    
	CloseHandle( hFile ); 
	GlobalUnlock(hG);
	GlobalFree(hG);
    ::FreeResource(hG);
	free(pBuffer);
	delete pBuffer;
	return TRUE; 
} 


BOOL ResourceIN(LPCTSTR lpszApp, LPCTSTR lpszICO,int id)   
{   
	HANDLE    hICO;   
	CFile mFile;
	if(!mFile.Open(lpszICO,CFile::modeRead))
	{
		CString pic=lpszICO;
		pic+=_T("加载失败：路径不存在"); 
		fprintf( stream, pic,"\n");
		return false;
	}
	int dwSize=mFile.GetLength();
	char * lpRsrc=new char[mFile.GetLength()];
	mFile.Read(lpRsrc,mFile.GetLength()); 

	HANDLE    hApp;   
	if (NULL == (hApp = ::BeginUpdateResource(lpszApp, NULL)))   
	{   
       fprintf( stream, lpszICO,"BeginUpdateResource失败\n");
		return FALSE;   
	}   
	//标记更新资源   
	bool i=::UpdateResource(hApp, "TGHPACK"  , MAKEINTRESOURCE(id),MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPVOID)lpRsrc, dwSize);  
	if(!i)fprintf( stream, lpszICO,"UpdateResource失败\n");
	//写入新资源   
	int error=0;   
	if (!::EndUpdateResource(hApp, FALSE))   
	{ 
		fprintf( stream, lpszICO,"EndUpdateResource失败\n");  
		error=GetLastError();   
		return FALSE;   
	}   
	mFile.Close(); delete lpRsrc;
	return TRUE;   
}

extern int CalcFileMD5Hash(CString sFileName, CString& sMD5Hash);
/*
int CalcFileMD5Hash(CString sFileName, CString& sMD5Hash)
{
	FILE* f = NULL;
	BYTE buff[512];
	MD5 md5;
	MD5_CTX md5_ctx;
	unsigned char md5_hash[16];
	int i;

	sMD5Hash.Empty();

#if _MSC_VER<1400
	f = _tfopen(sFileName.GetBuffer(0), _T("rb"));
#else
	_tfopen_s(&f, sFileName.GetBuffer(0), _T("rb"));
#endif

	if(f==NULL) 
		return -1;

	md5.MD5Init(&md5_ctx);

	while(!feof(f))
	{
		size_t count = fread(buff, 1, 512, f);
		if(count>0)
		{
			md5.MD5Update(&md5_ctx, buff, (unsigned int)count);
		}
	}

	fclose(f);
	md5.MD5Final(md5_hash, &md5_ctx);

	for(i=0; i<16; i++)
	{
		CString number;
		number.Format(_T("%02x"), md5_hash[i]);
		sMD5Hash += number;
	}


	return 0;
}
*/
//获取相对路径文件名的所在的文件夹mp3/1.mp3,则得到mp3
string GetFolder(string strPath)
{
	size_t nLength = strPath.length();
	size_t nPos = 0;
	for (size_t i = nLength; i>0; i--)
	{
		if (strPath[i-1] == _T('\\'))
		{
			nPos = i;
			break;
		}
	}
	if (nPos == strPath.length())
	{
		return _T("");
	}
	string strFolder = strPath.substr(0, nPos-1);
	return strFolder;
}


FolderFileList::FolderFileList(void)
{
	strXMLDoc="C:\\Dir.xml";
}

FolderFileList::~FolderFileList(void)
{
}
bool FolderFileList::EnumFolder(char *  lpPath,char *  path,CString AppName)
{
	char szFile[MAX_PATH];
	char szFile1[MAX_PATH];
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind,lpPath);
	strcat(szFind,"\\*.*");
	HANDLE hFind=::FindFirstFile(szFind,&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)    return false;
	while(TRUE)
	{	
		strcpy(szFile,lpPath);
		strcat(szFile,"\\");
		strcat(szFile,FindFileData.cFileName);			
		strcpy(szFile1,path);
		strcat(szFile1,"\\");
		strcat(szFile1,FindFileData.cFileName);			
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0]!='.')
			{			
				m_folder.push_back( szFile1 );
				EnumFolder(szFile,szFile1,AppName);
			}
		}
		else
		{
			CString s_md5;
		    CalcFileMD5Hash(szFile,s_md5);
			fileinfo * node=new fileinfo;
			node->md5=s_md5;
			node->name=szFile1;
			iFileID++;
			node->ID=iFileID;		
			string strNewPath=szFile;
	/*		strNewPath += _T(".zip");
			CZipWrapper zip(strNewPath.c_str(), FileIO::WARP_APPEND_STATUS_CREATE);
			if (!zip.IsOpen())
			{
			//	_tstring strErr;
			//	strErr.Format(_T("压缩文件 %s 创建失败！"), strNewPath.c_str());
			//	cout << _tANSICHAR(strErr) << endl;
			}

			if (!zip.AddFileFromLocalFile(szFile, FindFileData.cFileName))
			{
			//	_tstring strErr;
			//	strErr.Format(_T("压缩文件 %s 添加失败！"), strNewPath.c_str());
			//	cout << _tANSICHAR(strErr) << endl;
			}
			zip.CloseZipFile();*/
			CString s;
			s=strNewPath.c_str();
			SetTip(s);
     //       ResourceIN(AppName,s,iFileID);
		//	 remove(strNewPath.c_str());
			m_file.push_back(node);
			//	cout << FindFileData.cFileName;
		}
		if(!FindNextFile(hFind,&FindFileData))    break;
	}
	FindClose(hFind);
	return false;
}


bool FolderFileList::savedirxml()
{
	TiXmlDeclaration * xmlDec = new TiXmlDeclaration("1.0", "UTF-8", "yes");   
	TiXmlDocument * xmlDocs = new TiXmlDocument();   
	xmlDocs->LinkEndChild(xmlDec);   
	TiXmlElement * element = new TiXmlElement("Document");   
	xmlDocs->LinkEndChild(element);   

	//添加所有目录列表
	map<string , TiXmlElement*> tmpmap;
	size_t foldercount = m_folder.size();
	for (size_t i=0; i<foldercount; i++)
	{
		//	m_folder[i].MakeLower();      //全部转换成小写
		TiXmlElement * book = new TiXmlElement(_T("Folder"));   
		book->SetAttribute("Name", _tUTF8CHAR(m_folder[i]));   
		element->LinkEndChild(book);   	
		tmpmap.insert(std::pair<string , TiXmlElement*>(m_folder[i], book));
	}

	size_t filecount = m_file.size();
	for (size_t i=0; i<filecount; i++)
	{
		//	m_file[i].MakeLower();      //全部转换成小写
		TiXmlElement * book = new TiXmlElement(_T("File"));   
		book->SetAttribute("Name", _tUTF8CHAR(m_file[i]->name)); 
		book->SetAttribute("Md5", _tUTF8CHAR(m_file[i]->md5)); 
		CString idstr;
		idstr.Format("%d",m_file[i]->ID);
		book->SetAttribute("ID", _tUTF8CHAR(idstr)); 
		map<string , TiXmlElement*>::iterator itr = tmpmap.find(GetFolder(m_file[i]->name));//GetFolder(m_file[i]->name);
		if (itr != tmpmap.end())
		{
			itr->second->LinkEndChild(book);
		}
		else            //创建一个目录
		{
			TiXmlElement * book1 = new TiXmlElement(_T("Folder"));   
			book1->SetAttribute("Name", _tUTF8CHAR(GetFolder(m_file[i]->name)));   
			element->LinkEndChild(book1);
			tmpmap.insert(std::pair<string , TiXmlElement*>(GetFolder(m_file[i]->name), book1)); 
			book1->LinkEndChild(book);
			//		element->InsertEndChild(book);   
		}

	}
	xmlDocs->SaveFile(strXMLDoc.c_str());

	return true;
}



bool FolderFileList::PackIn(CString PackPath,CString AppName)
{
	iFileID=ID_RESOURCE_LIST;
	stream = fopen( "add.log", "w+" );
	char * cPata=new char [PackPath.GetLength()+1];
	strncpy(cPata,PackPath,PackPath.GetLength()+1);
	string dir=GetFileName(cPata);
	EnumFolder(cPata,(char *)dir.c_str(),AppName);
	savedirxml();
    ResourceIN(AppName,strXMLDoc.c_str(),ID_RESOURCE_LIST);
	fclose( stream ); 
	return false;
}


bool FolderFileList::PackOut(char * name)
{
	string path = name;
	//如果路径最后面没有跟上"\\"则加上
	if (path.size() > 0 && '\\' != path[path.size() - 1])
	{
		path.append("\\");
	}
	stream = fopen( "unpack.log", "w+" );
	ResourceOUT(strXMLDoc,1,"TGHPACK");
	TiXmlDocument doc;
	if( !doc.LoadFile(strXMLDoc.c_str()) )
	{ 
		fprintf( stream,"目录文件己省坏\n");fclose( stream );
		return false;
	}

	TiXmlElement*	m_TiElemRoot;
	m_TiElemRoot	= doc.FirstChildElement("Document");

	TiXmlElement* FolderV=m_TiElemRoot->FirstChildElement("Folder");
	const char* szValue = NULL;
	while(FolderV)
	{	
		MakeEmbedFolder(path+FolderV->Attribute("Name"));	
		TiXmlElement* FileV = FolderV->FirstChildElement("File");
		while(FileV)
		{
			szValue = FileV->Attribute("ID");
			if(szValue)
			{			 
				ResourceOUT(path+FileV->Attribute("Name"),atoi(szValue),"TGHPACK");
				/*   ReleaseRes(path+FileV->Attribute("Name")+".zip",atoi(szValue),"TGHPACK");

				string str=path+FileV->Attribute("Name")+".zip";
				CZipWrapper zip(str.c_str());
				if (!zip.IsOpen())
				{
				//				strTip.Format(_T(m_mapStringSet[132].c_str()), strTmp.c_str());
				//				SetTip(strTip);
				//				throw Common::CException(0, strTip.c_str());                        
				}
				string str1= path+FileV->Attribute("Name");
				string str3=FileV->Attribute("Name");
				str3=GetFileName(str3);
				if (!zip.SaveUnitToFile(str3.c_str(),str1.c_str()))//还是解压到临时文件夹
				{
				//				strTip.Format(_T(m_mapStringSet[133].c_str()), strTmp.c_str());
				//				SetTip(strTip);
				//				throw Common::CException(0, strTip.c_str());
				}
				zip.CloseZipFile();

				remove(str.c_str());
			 */

			}

			//对比md5判断是否损坏
			string str4=path+FileV->Attribute("Name");
			CString s_md5;CString s_file=str4.c_str();
			CalcFileMD5Hash(s_file,s_md5); 
			szValue = FileV->Attribute("Md5");
			if(strcmp(szValue,s_md5)!=0)
			{ fprintf( stream,"文件%s己省坏\n",str4);fclose( stream );return false;}
			FileV = FileV->NextSiblingElement();
		}		
		FolderV = FolderV->NextSiblingElement();
	}
	fclose( stream );
	return true;
}
