// updateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "updateDlg.h"
#include "tstring.h"
#include "filepacket/packet_interface.h"
#include "filepacket/datafile.h"
#include <map>
#include "ZipWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::map<int, std::string>	m_mapStringSet;
using FileIO::CVFS;
using FileIO::CZipWrapper;
map<_tstring, CVFS*> vfslist;

CHttpDownload GHttpDownload;
CINetDownLoad GInetDownload;
char g_szUpdateFile[MAX_PATH] = ".\\UpData\\update.xml";//��ǰ�汾���ļ�
volatile bool g_bIsEnd = false;//�жϸ��µı�־

bool isDownCancel()
{
	return g_bIsEnd;
}

void setDownCancel(bool b)
{
	GHttpDownload.StopDownload();
	g_bIsEnd=true;
}
string urlAera;
int    url_Index;
std::string g_szCurPath;
_tstring s_strVersion;//��ǰ�汾���ļ�

vector<AREASERVERIPINFO> s_iplist;
vector<AREASERVERIPINFO> s_backupiplist;		//����IP

_tstring strVersion_LOC;
_tstring strVersion_NEW;

TipList tiplist_;

CWnd * wndNotify;

void SetTip(_tstring strInfo,_tstring strInfo2="")
{	
	_tstring strNew;
	strNew=strInfo;

	for(int i=0;i<tiplist_.size();i++)
	{
		BtnInfo& info = tiplist_[i];
		if(strcmp(info._szName.c_str(),strInfo.c_str())==0)  //info._szName==strInfo)
		{
			//strNew.clear();
			strNew=info._szTip;
			break;
		}
	}
	strNew+=strInfo2;
	CString cstringText(strNew.c_str());
	CWnd * dlg=       wndNotify;
	::SendMessage(dlg->m_hWnd,WM_DRAW_TEXT,(WPARAM)strNew.c_str(),0);
};

void SetProgress(int type,int downlen,int totallen)
{
	if(type==0)
	{
		progress_message mess;
		mess.downlen=downlen;
		mess.totallen=totallen;
		mess.type=0;
		CWnd * dlg=     wndNotify;
		::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);
	}
	if(type==1)
	{
		progress_message mess;
		mess.downlen=downlen;
		mess.totallen=totallen;
		mess.type=1;
		CWnd * dlg=      wndNotify;
		::SendMessage(dlg->m_hWnd,WM_DRAW_PROGRESS,(WPARAM)&mess,0);
	}
}
void SetGetVer()
{
	CWnd * dlg=      wndNotify;
	::SendMessage(dlg->m_hWnd,WM_GET_VER,NULL,0);
}
void SetFinish()
{
	CWnd * dlg=      wndNotify;
	::SendMessage(dlg->m_hWnd,WM_UPDATE_FINISH,NULL,0);
}

void DeleteDir(const char* strDir)
{
	_tstring path = strDir;

	//���·�������û�и���"\\"�����
	if (path.size() > 0 && '\\' != path[path.size() - 1])
	{
		path.append("\\");
	}

	////string file = fext;
	_tstring file = _T("*.*");
	_tstring s = path + file;
	WIN32_FIND_DATA fileinfo ={0};
	HANDLE handle = FindFirstFile(s.c_str(),&fileinfo);

	if(NULL !=handle && INVALID_HANDLE_VALUE != handle)
	{
		do 
		{
			if (_T('.') != fileinfo.cFileName[0])
				if ((FILE_ATTRIBUTE_DIRECTORY & fileinfo.dwFileAttributes)
					== FILE_ATTRIBUTE_DIRECTORY)	//--Ŀ¼
				{
					_tstring filedir;
					filedir = path+fileinfo.cFileName;
					DeleteDir(filedir.c_str());

				}else
				{
					_tstring filename;
					filename=path+fileinfo.cFileName;
					remove(filename.c_str());
				}
		} while (FindNextFile(handle, &fileinfo));

		FindClose(handle);
		RemoveDirectory(strDir);
	}
}
bool SetFileChangeTime(_tstring strFilePath, _tstring strFileTime)
{
	FILETIME filetime;

	size_t nPos = strFileTime.find(_T("|"));
	_tstring strHighTime = strFileTime.substr(0, nPos);
	_tstring strLowTime = strFileTime.substr(nPos+1, strFileTime.length()-nPos);
	filetime.dwHighDateTime = atol(_tANSICHAR(strHighTime));
	filetime.dwLowDateTime = atol(_tANSICHAR(strLowTime));

	HANDLE fileHandle = CreateFile(strFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		SetFileTime(fileHandle, (LPFILETIME)NULL, (LPFILETIME)NULL, &filetime);
	}
	else
	{
		return false;
	}
	CloseHandle(fileHandle);
	return true;
}


_tstring GetFileDate(_tstring& strFilePath)
{
	_tstring strDate;
	HANDLE fileHandle = CreateFile(strFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if( fileHandle == INVALID_HANDLE_VALUE )
	{
		CloseHandle(fileHandle);
		return strDate;
	}
	_BY_HANDLE_FILE_INFORMATION fileInfo;
	if(!GetFileInformationByHandle(fileHandle, &fileInfo))
	{
		CloseHandle(fileHandle);
		return strDate;
	}

	CloseHandle(fileHandle);
	strDate.Format(_T("%d|%d"), fileInfo.ftLastWriteTime.dwHighDateTime, fileInfo.ftLastWriteTime.dwLowDateTime);
	return strDate;
}

_tstring GetFileCrc(_tstring& strFilePath)
{
	_tstring strCrc;
	unsigned long nCrc = CCRC32().GetFileCRC32(strFilePath.toNarrowString().c_str());
	strCrc.Format(_T("%d"), nCrc);
	return strCrc;
}

//��ȡ��Ŀ¼�����·���ļ�����
_tstring GetFolder(_tstring strPath, _tstring strFilePath)
{
	if (!strPath.empty() && strPath[strPath.length()-1] != _T('\\'))
	{
		strPath += _T("\\");
	}
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
	if (nPos == strPath.length())
	{
		return _T("");
	}

	_tstring strFolder = strFilePath.substr(strPath.length(), nPos-strPath.length()-1);

	return strFolder;
}

//�����ļ���
_tstring GetFileName(_tstring& strFilePath)
{
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
	_tstring strFileName = strFilePath.substr(nPos, strFilePath.length()-nPos);
	return strFileName;
}


using Common::_tstring;
void FTPDownLoadProc(unsigned int nFileSize, unsigned int nCurrDownLoadSize)
{
	SetProgress(0,nCurrDownLoadSize,nFileSize);
}

using FileIO::CVFS;
BOOL CheckVersionIsNeedPack(_tstring szCmpFile, _tstring strCmpVersion, _tstring& strNextVersion )
{
	TiXmlDocument versiondoc( szCmpFile.c_str() );
	if (!versiondoc.LoadFile())
	{
		//throw Common::CException(0, _T(m_mapStringSet[74].c_str()));
		return FALSE;
	}		
	//GetCur Version
	TiXmlElement* elementversion = versiondoc.FirstChildElement(_tUTF8CHAR(_T("NewVersion")));
	if (elementversion == NULL)
	{
		//throw Common::CException(0, _T(m_mapStringSet[75].c_str()));
	}

	_tstring strVersion;
	strVersion.fromUTF8(elementversion->GetText());

	//versiondoc.Get
	std::vector<VersionInfo> vtVI;
	//--------------
	const char* szValue;
	TiXmlElement* lpOldVer = versiondoc.FirstChildElement("OldVersion");
	if( lpOldVer )
	{
		TiXmlElement* lpVersion = lpOldVer->FirstChildElement("Version");
		while(lpVersion)
		{
			VersionInfo VI;
			szValue = lpVersion->Attribute("Cur");
			if( szValue )
			{
				VI.szCurVersion = szValue;
			}
			szValue = lpVersion->Attribute("Next");
			if(szValue)
			{
				VI.szNextVersion = szValue;
			}
			szValue = lpVersion->Attribute("NextPath");
			if(szValue)
			{
				VI.szPath = szValue;
			}
			szValue = lpVersion->Attribute("NeedPack");
			if(szValue)
			{
				if( stricmp( szValue, "TRUE") == 0 )
				{
					VI.bNeedPack = TRUE;
				}
				else
				{
					VI.bNeedPack = FALSE;
				}
			}
			else
			{
				VI.bNeedPack = FALSE;
			}

			vtVI.push_back( VI );
			lpVersion = lpVersion->NextSiblingElement("Version");
		}
	}

	for( int i=0; i<vtVI.size(); i++ )
	{
		if( vtVI[i].szCurVersion == strCmpVersion )
		{
			strNextVersion = vtVI[i].szNextVersion;
			return vtVI[i].bNeedPack;
		}
	}

	strNextVersion = strVersion;
	return TRUE;
}



bool CupdateDlg::start(int idx)
{
	if (iplist_.empty()||idx < 0 || idx >= iplist_.size())
	{
		return false;
	}
	url_Index = idx;
	BtnInfo& info = iplist_[idx];
	urlAera=info._szName;
	hHandle=CreateThread(NULL,0,UpdateThreadProc,this,0,NULL);
}

//void CupdateDlg::update()
//{
//	if (iplist_.empty())
//	{
//		return;
//	}
//	BtnInfo& info = iplist_[0];
//	urlAera=info._szName;
//	hHandle=CreateThread(NULL,0,UpdateThreadProc,NULL,0,NULL);
//}

void CupdateDlg::UpdataFileToPacket(UpdateList& updatalist)
{
	size_t nFileCount = updatalist.size();
	packet* pPacket = NULL;
	_tstring strTip;
	for (size_t i=0; i<nFileCount && !isDownCancel(); i++)
	{
		DOWNLOADFILEINFO& info = updatalist[i];
		if(info.strPacketName.size()>0)
		{
			_tstring strPacket = "CLIENT\\";
			strPacket+=info.strPacketName.c_str();

			DWORD dwAttrs = GetFileAttributes(strPacket.c_str());

			if(dwAttrs != INVALID_FILE_ATTRIBUTES)
			{
				if(dwAttrs & FILE_ATTRIBUTE_READONLY)
					SetFileAttributes(strPacket.c_str(),dwAttrs&~FILE_ATTRIBUTE_READONLY);
			}

			pPacket =packet_namespace::getpacket(strPacket.c_str());
			if(!pPacket)
			{
				strTip.Format(_T(m_mapStringSet[139].c_str()), info.strFileName.c_str());
				SetTip(strTip);
				continue;
			}
			char fileName[256];
			strcpy(fileName,info.strSaveLocalFilePath.c_str());
			char filedir[20];
			memcpy(filedir,fileName,4);
			filedir[4]='\0';
			if(!strcmp(filedir,"bin\\"))
			{
				strcpy(fileName,fileName+4);
			}
			for (int i=strlen(fileName);i>=0;--i)
			{
				if(fileName[i]=='\\' || fileName[i]=='/')
				{
					fileName[i+1]='0';
					strcpy(fileName+i+1,info.strFileName.c_str());
					break;
				}

			}
			SetTip(fileName);
			if(!pPacket->UpdateFile(info.strLocalFilePath.c_str(),fileName))
			{
				pPacket->AddFile(info.strLocalFilePath.c_str(),fileName);
			}
		}
		SetProgress(1,i+1,nFileCount);	
	}
	SetTip("update_res_pack");
	packet_namespace::SavePacket();
	packet_namespace::AfreshAllPacket();
	packet_namespace::release();
}

int CupdateDlg::downpack1(IDownLoad	*s_httpdownload)
{
	//���ؽ�ѹ
	s_httpdownload->SetCallBackDownProc( FTPDownLoadProc );
	_tstring  strSavePath;
	_tstring strDownLoadHostURL;//���������ط�������ַ
	_tstring strLocalVersionFile;//�������汾��
	AREASERVERIPINFO& ipinfo = s_iplist[0];
	strDownLoadHostURL = ipinfo.DownLoadIPList[0];

	_tstring szDestVersion = g_szCurPath+ "Version.xml";
	_tstring strNextVersion;      
	BOOL bNeedPack = CheckVersionIsNeedPack( szDestVersion, s_strVersion, strNextVersion );
	if(s_strVersion==strNextVersion)return 0;

	SetTip(_T("start_down_pack"));Sleep(500);
	//��������·��http://192.168.1.2/0.91/VersionInfo_0.91.xml.zip
	strLocalVersionFile.Format(_T("%s\\VersionInfo_%s.xml"), strNextVersion.c_str(), strNextVersion.c_str());

	_tstring strPackSavePath;
	{
		_tstring strURL;
		//������ʱ�ļ��������������Ŀ¼��
		strSavePath=g_szCurPath+"PatchTemp\\";
		_mkdir(_tANSICHAR(g_szCurPath+_T("PatchTemp")));
		_mkdir(_tANSICHAR(g_szCurPath+_T("Cache")));

		strPackSavePath.Format(_T("%s"), strNextVersion.c_str());
		strURL = strDownLoadHostURL +"\/" +strPackSavePath + _T(".zip");
		strURL.MakeLower(); 
		strPackSavePath.Format(_T("Cache\\%s_Pack.zip"), strNextVersion.c_str());
		strPackSavePath=g_szCurPath+strPackSavePath;
		CFile myFile;UINT len=0;
		if(myFile.Open(strPackSavePath.c_str(), CFile::modeRead | CFile::typeBinary))
		{
			len=myFile.GetLength();myFile.Close();
		}
		int result=s_httpdownload->Download(strURL.c_str(), strPackSavePath.c_str(),"",len,0);

		
		
		if(isDownCancel())return  0;
	}
	FileIO::CZipWrapper zippack(strPackSavePath.c_str());
	strSavePath += _T("VersionInfo.zip");
	_tstring strUnitFileInZipPack=strLocalVersionFile + _T(".zip");
	strUnitFileInZipPack.Format(_T("%s\\VersionInfo_%s.xml.zip"), strNextVersion.c_str(), strNextVersion.c_str());
	if (!zippack.SaveUnitToFile(strUnitFileInZipPack.c_str(), strSavePath.c_str()))
	{
		AREASERVERIPINFO& ipinfo1 = s_backupiplist[0];
		strDownLoadHostURL = ipinfo1.DownLoadIPList[0];

		_tstring strURL;
		strPackSavePath.Format(_T("%s"), strNextVersion.c_str());
		strURL = strDownLoadHostURL +"\/" +strPackSavePath + _T(".zip");
		strURL.MakeLower(); 
		strPackSavePath.Format(_T("Cache\\%s_Pack.zip"), strNextVersion.c_str());
		strPackSavePath=g_szCurPath+strPackSavePath;
		CFile myFile;int len=0;
		if(myFile.Open(strPackSavePath.c_str(), CFile::modeRead | CFile::typeBinary))
		{
			len=myFile.GetLength();myFile.Close();
		}
		s_httpdownload->Download(strURL.c_str(), strPackSavePath.c_str(),"",len,0);
		zippack.OpenZipFile(strPackSavePath.c_str());
		if (!zippack.SaveUnitToFile(strUnitFileInZipPack.c_str(), strSavePath.c_str()))
		{
			DeleteFile(strPackSavePath.c_str());
			AfxMessageBox("��ѹʧ��");
			return 0;
		}
	}
	//�õ����°�xml�ļ��б�
	FileIO::CZipWrapper zipxml(strSavePath.c_str());

	strSavePath += _T(".tmp");
	SetFileAttributes(strSavePath.c_str(), FILE_ATTRIBUTE_NORMAL);
	remove(_tANSICHAR(strSavePath));
	if (!zipxml.SaveUnitToFile(strLocalVersionFile.c_str(), strSavePath.c_str()))
	{
		// throw Common::CException(0, _T(m_mapStringSet[125].c_str()));
	}
	zipxml.CloseZipFile();

	//����xml�ĵ�������Ҫ���ص��ļ��б���UpdateList�ṹ�洢
	//ע�⣺_T("C:\\update\\debug\\PatchTemp")��Ҫд��_T("C:\update\debug\PatchTemp")

	string ss=g_szCurPath+"PatchTemp";
	UpdateList& downlist = GetUpdateFile(strSavePath, ss);//��Ϊ����Ҫ�������ļ�ȫ������ʱ�ļ�����

	//�ܽ��ȣ���ǰ�����ļ����/�ļ���������ǰ���ȣ��ļ������س���/�ļ��ܳ���
	//����Ϣ�޳�ʼ��ʱ����
	int nRet;
	size_t nFileCount = downlist.size();
	for (size_t i=0; i<nFileCount && !isDownCancel(); i++)
	{
		Sleep(500);
		DOWNLOADFILEINFO& info = downlist[i];
		_tstring strDownLoadURL = strDownLoadHostURL +_T("/") +strNextVersion + _T("/") + info.strHostFilePath;
		//����ַURL�е� \ ת���� /
		size_t URLLength = strDownLoadURL.length();
		for (size_t j=0; j<URLLength; j++)
		{
			if (strDownLoadURL[j] == _T('\\'))
			{
				strDownLoadURL[j] = _T('/');
			}
		}
		//���Ϊ�����ļ�ϵͳ�ļ�
		if (info.bVFSUnit)
		{
			CVFS* pvfs = NULL;
			map<_tstring, CVFS*>::iterator itr = vfslist.find(info.strLocalFilePath);
			if (itr != vfslist.end())
			{
				pvfs = itr->second;
			}
			else
			{
				pvfs = new CVFS;
				vfslist.insert(std::pair<_tstring, CVFS*>(info.strLocalFilePath, pvfs));

				if (!pvfs->LoadVFS(info.strLocalFilePath.c_str()))
				{
					if (!pvfs->NewVFSFile(info.strLocalFilePath.c_str()))
					{
					}
				}
			}
			CVFS& vfs = *pvfs;

			_tstring strTmp = g_szCurPath+_T("PatchTemp\\tmp.tmp");
			_tstring strUnCompressFile;
			SetFileAttributes(strTmp.c_str(), FILE_ATTRIBUTE_NORMAL);
			remove(_tANSICHAR(strTmp));
			remove(_tANSICHAR(strTmp + _T(".temp")));
			remove(_tANSICHAR(strTmp.c_str()));

			strDownLoadURL.MakeLower();
			if (strDownLoadURL.Left(6) != _T("ftp://"))
			{
				_tstring strUnPackFile;
				strUnPackFile.Format("%s\\%s",strNextVersion.c_str(),info.strHostFilePath.c_str());
				zippack.SaveUnitToFile(strUnPackFile.c_str(), strTmp.c_str());
				//	nRet = s_httpdownload->Download(strDownLoadURL.c_str(), strTmp.c_str(), _tANSICHAR(info.strCRC));
				if (nRet != DOWNLOAD_RESULT_SUCCESS &&
					nRet != DOWNLOAD_RESULT_SAMEAS)
				{
				}
			}
			if (info.bUseCompress)
			{
				CZipWrapper zip(strTmp.c_str());
				if (!zip.IsOpen())
				{
				}
				_tstring strFileName = GetFileName(info.strFileName);
				strUnCompressFile = _T("PatchTemp\\");
				strUnCompressFile += strFileName;

				SetFileAttributes(strUnCompressFile.c_str(), FILE_ATTRIBUTE_NORMAL);
				remove(_tANSICHAR(strUnCompressFile));

				_tstring strUnCompressfilepath ;

				if(info.strPacketName.size() <= 0)
				{
					strUnCompressfilepath= strFileName;
				}else
				{
					strUnCompressfilepath = _T("PatchTemp\\");
					strUnCompressfilepath+=strFileName;
				}				
				if (!zip.SaveUnitToFile(strFileName.c_str(), strUnCompressFile.c_str()))//���ǽ�ѹ����ʱ�ļ���
				{
				}
				zip.CloseZipFile();

				remove(_tANSICHAR(strTmp));
				strTmp = strUnCompressFile;
			}
			if (!vfs.AddUnit(info.strFileName.c_str(), strTmp.c_str()) || !vfs.Save(NULL))
			{
			}
			remove(_tANSICHAR(strTmp));
		}
		else
		{
			remove(_tANSICHAR(info.strLocalFilePath + _T(".temp")));
			SetFileAttributes(info.strLocalFilePath.c_str(), FILE_ATTRIBUTE_NORMAL);
			_tstring strTmp = g_szCurPath+_T("PatchTemp\\tmp.tmp");
			SetFileAttributes(strTmp.c_str(), FILE_ATTRIBUTE_NORMAL);
			remove(_tANSICHAR(strTmp));
			remove(_tANSICHAR(strTmp + _T(".temp")));

			strDownLoadURL.MakeLower();
			if (strDownLoadURL.Left(6) != _T("ftp://"))
			{
				_tstring strUnPackFile;
				strUnPackFile.Format("%s\\%s",strNextVersion.c_str(),info.strHostFilePath.c_str());
				zippack.SaveUnitToFile(strUnPackFile.c_str(), strTmp.c_str());
				SetTip(strUnPackFile.c_str());
			}

			if (info.bUseCompress)
			{
				CZipWrapper zip(strTmp.c_str());
				if (!zip.IsOpen())
				{
				}

				_tstring strUnZipTmpFile = g_szCurPath+_T("PatchTemp\\unziptmp.tmp");
				SetFileAttributes(strUnZipTmpFile.c_str(), FILE_ATTRIBUTE_NORMAL);
				remove(_tANSICHAR(strUnZipTmpFile));
				_tstring strUnCompressfilepath ;
				if(info.strPacketName.size() <= 0)
				{
					strUnCompressfilepath= info.strFileName;
				}
				else
				{
					strUnCompressfilepath = g_szCurPath+_T("PatchTemp\\");
					strUnCompressfilepath+=info.strFileName;
				}
				char nfileflage[]=".zip";
				char nCurrFileFlage[5];
				char nFilepath[MAX_PATH];
				int nFlageOffset = strlen(info.strHostFilePath.c_str())-4;
				strcpy(nCurrFileFlage,info.strHostFilePath.c_str()+nFlageOffset);
				if(strcmp(nfileflage,nCurrFileFlage) == 0)
				{
					strcpy(nFilepath,info.strHostFilePath.c_str());
					nFilepath[nFlageOffset] = '\0';
					info.strSaveLocalFilePath = nFilepath;
				}else
				{
					info.strSaveLocalFilePath = info.strHostFilePath.c_str();
				}

				if(info.strPacketName == "")//���û�а�ʱ����ֱ�ӽ⵽��ӦĿ¼��
				{    
					_tstring strFilename ;
					strFilename+=info.strSaveLocalFilePath;
					if(!zip.SaveUnitToFile(info.strFileName.c_str(),strUnZipTmpFile.c_str()))
					{
					}
					else
					{
						DWORD dwAttrs = GetFileAttributes(strFilename.c_str());
						if(dwAttrs != INVALID_FILE_ATTRIBUTES)
						{
							if(dwAttrs & FILE_ATTRIBUTE_READONLY);

							SetFileAttributes(strFilename.c_str(),dwAttrs&~FILE_ATTRIBUTE_READONLY);
						}

						remove(_tANSICHAR(strFilename));
						rename(_tANSICHAR(strUnZipTmpFile), _tANSICHAR(strFilename));
						if(GetLastError() == ERROR_PATH_NOT_FOUND)
						{
							if(!zip.SaveUnitToFile(info.strFileName.c_str(),strFilename.c_str()))
							{
							}
						}
					}
				}
				else{//�а�
					if (!zip.SaveUnitToFile(info.strFileName.c_str(), info.strLocalFilePath.c_str()))
					{
					}
				}                  
				zip.CloseZipFile();
			}
			else
			{
				remove(_tANSICHAR(info.strLocalFilePath));
				rename(_tANSICHAR(strTmp), _tANSICHAR(info.strLocalFilePath));
			}

			SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
		}
		SetProgress(1,i+1,nFileCount);
	}
	//���д��������PatchTemp���ص��ļ������_T("\\bin\\res\\")��
	_mkdir(_tANSICHAR(g_szCurPath+_T("DATA\\")));
	UpdataFileToPacket(downlist);

	// �ر����д򿪵�vfs�ļ�
	while (!vfslist.empty())
	{
		CVFS* p = vfslist.begin()->second;
		if (p != NULL)
		{
			delete p;
		}
		vfslist.erase(vfslist.begin());
	}
	//��������û��ֶ���Ԥ��ֹ���������汾��
	if (!isDownCancel())
	{
		remove(_tANSICHAR(strLocalVersionFile));
	}
	//��������Ժ󽫰汾����������
	zippack.CloseZipFile();
	DeleteFile(strPackSavePath.c_str());
	s_strVersion=strNextVersion;
	SetLocalVersion(s_strVersion.c_str());
	strVersion_LOC=s_strVersion;
	return 0;
}



CupdateDlg::UpdateList& CupdateDlg::GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath,bool is_autopatch)
{
	if (!strLocalPath.empty() && strLocalPath[strLocalPath.length()-1] != _T('\\'))
	{
		strLocalPath += _T("\\");
	}
	static UpdateList s_downlist;
	s_downlist.clear();
	TiXmlDocument doc(_tANSICHAR(strVersionXML));

	if (!doc.LoadFile())
	{
		CString err;
		err.Format("load version xml error!,%s",strVersionXML.c_str());
		::MessageBox(NULL,err,"error",MB_OK);
		goto ret;
	}
	TiXmlNode* nodeversioninfo = doc.FirstChild(_tUTF8CHAR(_T("VersionInfo")));
	if (nodeversioninfo == NULL)
	{
		::MessageBox(NULL,"error","load version xml VersionInfo error!",MB_OK);
		goto ret;
	}

	TiXmlNode* nodefilelist = nodeversioninfo->FirstChild(_tUTF8CHAR(_T("FileList")));
	if (nodefilelist == NULL)
	{
		::MessageBox(NULL,"error","load version xml FileList error!",MB_OK);
		goto ret;
	}

	//�ȰѸ�Ŀ¼�µ��ļ�����һ��
	TiXmlElement* elementfile = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("File")));
	while (elementfile != NULL && !isDownCancel())
	{
		_tstring strFile;
		strFile.fromUTF8(elementfile->GetText());
		//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
		if (strFile == _T(g_szUpdateFile))
		{
			elementfile = elementfile->NextSiblingElement();
			continue;
		}

		_tstring strSize;
		TiXmlElement* elementsize = elementfile->FirstChildElement(_tUTF8CHAR(_T("Size")));
		strSize.fromUTF8(elementsize->GetText());

		if (strSize == _T("0"))
		{
			_tstring strfile = strLocalPath + strFile;
			DeleteFile(strfile.c_str());
			elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
			fstream file(_tUNICODECHAR(strfile), std::ios::app);
			continue;
		}

		_tstring strDate;
		TiXmlElement* elementdate = elementfile->FirstChildElement(_tUTF8CHAR(_T("Date")));
		strDate.fromUTF8(elementdate->GetText());

		_tstring strCrc;
		TiXmlElement* elementcrc = elementfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
		strCrc.fromUTF8(elementcrc->GetText());

		DOWNLOADFILEINFO info;
		info.bVFSUnit = false;
		info.strHostFilePath += strFile;//�ļ���
		info.strLocalFilePath = strLocalPath + strFile;
		info.strChangeTime = strDate;
		info.strFileName = strFile;
		info.strCRC = strCrc;

		if (elementfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
		{
			info.bUseCompress = true;
			info.strHostFilePath += _T(".zip");
		}
		else
		{
			info.bUseCompress = false;
		}

		if (strDate != GetFileDate(info.strLocalFilePath))
		{
			if (strCrc != GetFileCrc(info.strLocalFilePath))
			{
				s_downlist.push_back(info);
			}
			else
			{
				SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
			}
		}
		else
		{
			//��ʹ�ļ��������ҲҪ����CRCУ������
			if (strCrc != GetFileCrc(info.strLocalFilePath))
			{
				s_downlist.push_back(info);
			}
		}
		elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
	}

	//���ڷ�����Ŀ¼�µ�
	TiXmlElement* elementfolder = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("Folder")));
	while (elementfolder != NULL && !isDownCancel())
	{
		_tstring strFolder;
		strFolder.fromUTF8(elementfolder->GetText());
		if (strFolder[strFolder.length()-1] != _T('\\'))
		{
			strFolder += _T("\\");
		}
		_tstring strPacketName;
		TiXmlElement* pElementPacket = elementfolder->FirstChildElement(_tUTF8CHAR(_T("packet")));
		if(pElementPacket)
			strPacketName.fromUTF8(pElementPacket->GetText());//������
	//	    MakeEmbedFolder(strFolder);

		TiXmlElement* elementfile = elementfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
		while (elementfile != NULL && !isDownCancel())
		{
			_tstring strFile;
			strFile.fromUTF8(elementfile->GetText());

			//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
			if (strFile == _T(g_szUpdateFile))
			{
				elementfile = elementfile->NextSiblingElement();
				continue;
			}

			_tstring strSize;
			TiXmlElement* elementsize = elementfile->FirstChildElement(_tUTF8CHAR(_T("Size")));
			strSize.fromUTF8(elementsize->GetText());

			if (strSize == _T("0"))
			{
				_tstring strfile = strLocalPath + strFolder + strFile;
				DeleteFile(strfile.c_str());
				elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
				fstream file(_tUNICODECHAR(strfile), std::ios::app);
				continue;
			}

			_tstring strDate;
			TiXmlElement* elementdate = elementfile->FirstChildElement(_tUTF8CHAR(_T("Date")));
			strDate.fromUTF8(elementdate->GetText());

			_tstring strCrc;
			TiXmlElement* elementcrc = elementfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
			strCrc.fromUTF8(elementcrc->GetText());

			DOWNLOADFILEINFO info;
			info.bVFSUnit = false;
			info.strHostFilePath = strFolder + strFile;
			info.strLocalFilePath = strLocalPath + strFolder + strFile;
			info.strChangeTime = strDate;
			info.strFileName = strFile;
			info.strCRC = strCrc;
			info.strPacketName = strPacketName;
			

			if (elementfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
			{
				info.bUseCompress = true;
				info.strHostFilePath += _T(".zip");
			}
			else
			{
				info.bUseCompress = false;
			}

			if (is_autopatch)
			{
				if (strDate != GetFileDate(info.strLocalFilePath))
				{
					if  (strCrc != GetFileCrc(info.strLocalFilePath))
					{
						s_downlist.push_back(info);
					}
					else
					{
						SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
					}
				}
				else
				{
					//��ʹ�ļ��������ҲҪ����CRCУ������
					if (strCrc != GetFileCrc(info.strLocalFilePath))
					{
						s_downlist.push_back(info);
					}
				}
			}
			else
			{//����Ǳ��ظ��£��ֶ����£������ܱ����ļ�����Ҫ���³ɰ��е��ļ�
				s_downlist.push_back(info);
			}

			elementfile = elementfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
		}
		elementfolder = elementfolder->NextSiblingElement(_tUTF8CHAR(_T("Folder")));
	}

	//���ڷ��������ļ�ϵͳ
	TiXmlElement* elementvfolder = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("VFolder")));
	while (elementvfolder != NULL && !isDownCancel())
	{
		_tstring strVFSFile;
		strVFSFile.fromUTF8(elementvfolder->GetText());
		CVFS vfs;
		//����VFS�ļ���������������½���
		if (!vfs.LoadVFS(strVFSFile.c_str()))
		{
			if (!vfs.NewVFSFile(strVFSFile.c_str()))
			{
				//					throw Common::CException(0, _T(m_mapStringSet[54].c_str()), strVFSFile.c_str());
			}
		}
		CVFS::UNITLIST list = vfs.GetUnitList();
		//���������ļ�ϵͳ��Ŀ¼���ļ�
		TiXmlElement* elementvfile = elementvfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
		while (elementvfile != NULL && !isDownCancel())
		{
			DOWNLOADFILEINFO info;
			info.bVFSUnit = true;
			info.strLocalFilePath = strVFSFile;
			info.strFileName.fromUTF8(elementvfile->GetText());

			_tstring strCrc;
			TiXmlElement* elementcrc = elementvfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
			strCrc.fromUTF8(elementcrc->GetText());
			info.strCRC = strCrc;

			_tstring strFileName = info.strFileName;
			strFileName.Replace(_T("/"), _T("\\"));
			strFileName.MakeLower();

			CVFS::UNITLIST::iterator itr = list.find(strFileName);
			if (itr != list.end())
			{
				if (itr->second.nCrc == static_cast<unsigned long>(atol(_tANSICHAR(strCrc))))
				{
					elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
					continue;
				}
				else        //���vfs�д��ڴ��ļ�����ɾ��
				{
					vfs.DelUnit(info.strFileName.c_str());
				}
			}

			//CRCֵΪ0�����ʾ����ҲΪ0
			if (strCrc == _T("0"))
			{
				vfs.AddUnit(info.strFileName.c_str(), NULL, 0);
				vfs.Save(NULL);
				elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
				continue;
			}

			info.strHostFilePath = info.strLocalFilePath + _T("/") + info.strFileName;
			if (elementvfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
			{
				info.bUseCompress = true;
				info.strHostFilePath += _T(".zip");
			}
			else
			{
				info.bUseCompress = false;
			}
			s_downlist.push_back(info);
			elementvfile = elementvfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
		}
		//���������ļ�ϵͳ��Ŀ¼���ļ�
		TiXmlElement* elementvsubfolder = elementvfolder->FirstChildElement(_tUTF8CHAR(_T("Folder")));
		while (elementvsubfolder != NULL && !isDownCancel())
		{
			_tstring strVsubfolder;
			strVsubfolder.fromUTF8(elementvsubfolder->GetText());
			//���������ļ�ϵ��Ŀ¼���ļ�
			TiXmlElement* elementvsubfile = elementvsubfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
			while (elementvsubfile != NULL && !isDownCancel())
			{
				DOWNLOADFILEINFO info;
				info.bVFSUnit = true;
				info.strLocalFilePath = strVFSFile;
				_tstring strFile;
				strFile.fromUTF8(elementvsubfile->GetText());
				info.strFileName.Format(_T("%s\\%s"), strVsubfolder.c_str(), strFile.c_str());

				_tstring strCrc;
				TiXmlElement* elementcrc = elementvsubfile->FirstChildElement(_tUTF8CHAR(_T("Crc")));
				strCrc.fromUTF8(elementcrc->GetText());
				info.strCRC = strCrc;

				_tstring strFileName = info.strFileName;
				strFileName.Replace(_T("/"), _T("\\"));
				strFileName.MakeLower();

				CVFS::UNITLIST::iterator itr = list.find(strFileName);
				if (itr != list.end())
				{
					if (itr->second.nCrc == static_cast<unsigned long>(atol(_tANSICHAR(strCrc))))
					{
						elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
						continue;
					}
					else        //���vfs�д��ڴ��ļ�����ɾ��
					{
						vfs.DelUnit(info.strFileName.c_str());
					}
				}
				//CRCֵΪ0�����ʾ����ҲΪ0
				if (strCrc == _T("0"))
				{
					vfs.AddUnit(info.strFileName.c_str(), NULL, 0);
					elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
					continue;
				}

				info.strHostFilePath = info.strLocalFilePath + _T("/") + info.strFileName;
				if (elementvsubfile->Attribute(_tUTF8CHAR("Compress")) != NULL)
				{
					info.bUseCompress = true;
					info.strHostFilePath += _T(".zip");
				}
				else
				{
					info.bUseCompress = false;
				}
				s_downlist.push_back(info);
				elementvsubfile = elementvsubfile->NextSiblingElement(_tUTF8CHAR(_T("File")));
			}

			elementvsubfolder = elementvsubfolder->NextSiblingElement(_tUTF8CHAR(_T("Folder")));
		}
		//			if (!vfs.Save(ChangeProcCallBack))
		{
			//				throw Common::CException(0, _T(m_mapStringSet[56].c_str()), strVFSFile.c_str());
		}
		elementvfolder = elementvfolder->NextSiblingElement(_tUTF8CHAR(_T("VFolder")));
	}
ret:
	return s_downlist;
}

bool CupdateDlg::SetLocalVersion(const TCHAR* szVersion)
{
	_tstring strErr;
	TiXmlDocument doc;
	if (!doc.LoadFile(_tANSICHAR(_T(g_szUpdateFile))))
	{
		return false;
	}
	TiXmlElement* elementupdate = doc.FirstChildElement(_tUTF8CHAR(_T("Update")));
	if (elementupdate == NULL)
	{
		return false;
	}

	TiXmlElement* elementversion = elementupdate->FirstChildElement(_tUTF8CHAR(_T("Version")));
	if (elementversion != NULL)
	{
		elementupdate->RemoveChild(elementversion);
	}
	TiXmlElement newversion(_tUTF8CHAR(_T("Version")));
	newversion.InsertEndChild(TiXmlText(_tUTF8CHAR(szVersion)));
	elementupdate->InsertEndChild(newversion);
	doc.SaveFile();
	return true;
}


void cleandir()
{
	DeleteFile("server.zip");DeleteFile("serverip.xml");DeleteFile("slist_1.zip");DeleteFile("Version.xml");
	DeleteDir("PatchTemp");
}

bool bGetNewVer=true;
DWORD WINAPI  CupdateDlg::UpdateThreadProc(LPVOID p)
{
	SetTip(_T("id_read_config"));
	CupdateDlg* pUpdateDlg = (CupdateDlg*)p;
	if (!pUpdateDlg)
	{
		return 0;
	}
	TiXmlDocument doc;
	//��ȡ��ǰ�汾����
	{
		if (!doc.LoadFile(_tANSICHAR(_T(g_szUpdateFile))))
		{
			SetTip(_T("id_read_config_error"));
			return -1;
		}
		TiXmlElement* elementupdate = doc.FirstChildElement(_tUTF8CHAR(_T("Update")));
		if (elementupdate == NULL)
		{
			SetTip(_T("id_read_config_error"));
			return -1;
		}

		TiXmlElement* elementversion = elementupdate->FirstChildElement(_tUTF8CHAR(_T("Version")));
		if (elementversion == NULL)
		{
			SetTip(_T("id_read_config_error"));
			return -1;
		}
		s_strVersion.fromUTF8(elementversion->GetText());
		doc.Clear();
	}
	
	GHttpDownload.Init();
	static IDownLoad	*s_httpdownload= &GHttpDownload;
	Sleep(500);
	SetTip(_T("downing_file_list"));
	//1.1����http://60.191.34.89/serverip2.zip�ļ�,�õ�area serverlist������slist_1.zip�ļ�
	{
		
		TCHAR szFilePath[MAX_PATH + 1]; 
		GetModuleFileName(NULL, szFilePath, MAX_PATH); 
		(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
		g_szCurPath=szFilePath;
		
		_tstring strURL = urlAera;// _T("http://192.168.1.2/serverip2_test.zip");
		_tstring strSavePath = g_szCurPath+_T("server.zip");
		_tstring strXMLFile = _T("serverip.xml");
		strURL.MakeLower();
		unsigned int nRet = s_httpdownload->Download(strURL.c_str(), strSavePath.c_str());

		if(nRet!=DOWNLOAD_RESULT_SUCCESS)
		{
			if (!pUpdateDlg->start(url_Index+1))
			{
				SetTip(_T("downing_file_list_error"));
			}
			return 0;
		}
		FileIO::CZipWrapper zip(strSavePath.c_str());
		if (!zip.IsOpen())
		{
			SetTip(_T("downing_file_list_error"));
			cleandir();
			return 0;
		}

		if (!zip.SaveUnitToFile(strXMLFile.c_str(), _T(".\\serverip.xml")))
		{
			SetTip(_T("downing_file_list_format_error"));
			return 0;
		}

		s_iplist.clear();s_backupiplist.clear();

		TiXmlDocument ipdoc(_T(".\\serverip.xml"));
		if (!ipdoc.LoadFile())
		{
			cleandir();
			SetTip(_T("downing_file_list_format_error"));
			return 0;
		}

		TiXmlElement* elementbigareaip = ipdoc.FirstChildElement(_tUTF8CHAR(_T("bigareaips")));
		if (elementbigareaip == NULL)
		{
			SetTip(_T("downing_file_list_format_error"));
			return 0;
		}

		TiXmlElement* elementsinglearea = elementbigareaip->FirstChildElement(_tUTF8CHAR(_T("area")));
		while (elementsinglearea != NULL&& !isDownCancel())
		{
			AREASERVERIPINFO ip;
			ip.strServerList.fromUTF8(elementsinglearea->Attribute(_tUTF8CHAR(_T("serverlist"))));
			ip.strServerOnlineInfo.fromUTF8(elementsinglearea->Attribute(_tUTF8CHAR(_T("serveronlineinfo"))));
			TiXmlElement* elementip = elementsinglearea->FirstChildElement(_tUTF8CHAR(_T("ip")));

			while (elementip != NULL)
			{
				_tstring strip;
				strip.fromUTF8(elementip->Attribute(_tUTF8CHAR(_T("value"))));
				ip.DownLoadIPList.push_back(strip);

				elementip = elementip->NextSiblingElement(_tUTF8CHAR(_T("ip")));
			}

			s_iplist.push_back(ip);
			//��ӱ���IP
			AREASERVERIPINFO backupip;
			TiXmlElement* elementbackupip = elementsinglearea->FirstChildElement(_tUTF8CHAR(_T("backupip")));

			while (elementbackupip != NULL)
			{
				_tstring strip;
				strip.fromUTF8(elementbackupip->Attribute(_tUTF8CHAR(_T("value"))));
				backupip.DownLoadIPList.push_back(strip);

				elementbackupip = elementbackupip->NextSiblingElement(_tUTF8CHAR(_T("backupip")));
			}
			s_backupiplist.push_back(backupip);
			elementsinglearea = elementsinglearea->NextSiblingElement(_tUTF8CHAR(_T("area")));
		}
		zip.CloseZipFile();
		ipdoc.Clear();
	}

	if(isDownCancel()){SetTip(_T("update_task_cancel"));return 0;}

	std::vector<VersionInfo> vtVI;
	//2.���ذ汾����http://192.168.1.2/slist_1.zip�ļ��汾�ŶԱ�
	{
		_tstring s_strServerListURL;
		_tstring s_strSavePath;
		s_strSavePath=_T(".\\slist_1.zip");
		AREASERVERIPINFO& ipinfo = s_iplist[0];
		s_strServerListURL = ipinfo.strServerList;
		int result = s_httpdownload->Download(s_strServerListURL.c_str(), s_strSavePath.c_str());
		if (result == DOWNLOAD_RESULT_FAIL)
		{
			SetTip(_T("download file error"));
			return 0;
		}

		FileIO::CZipWrapper ZipDocVer( s_strSavePath.c_str());
		std::string szDestVersion = g_szCurPath + "Version.xml";
		ZipDocVer.SaveUnitToFile( "version_test.xml", szDestVersion.c_str()	 );
		TiXmlDocument versiondoc( szDestVersion.c_str() );
		if (!versiondoc.LoadFile())
		{
			cleandir();
			SetTip(_T("version_file_format_error"));
			return 0;
		}		
		TiXmlElement* elementversionNew = versiondoc.FirstChildElement(_tUTF8CHAR(_T("NewVersion")));
		if (elementversionNew == NULL)
		{
			SetTip(_T("version_file_format_error"));
			return 0;
		}
	
		extern _tstring strVersion_LOC;
		extern _tstring strVersion_NEW;
		strVersion_LOC=s_strVersion;
		strVersion_NEW.fromUTF8(elementversionNew->GetText());

		const char* szValue;
		TiXmlElement* lpOldVer = versiondoc.FirstChildElement("OldVersion");
		if( lpOldVer )
		{
			TiXmlElement* lpVersion = lpOldVer->FirstChildElement("Version");
			while(lpVersion)
			{
				VersionInfo VI;
				szValue = lpVersion->Attribute("Cur");
				if( szValue )
				{
					VI.szCurVersion = szValue;
				}
				szValue = lpVersion->Attribute("Next");
				if(szValue)
				{
					VI.szNextVersion = szValue;
				}
				szValue = lpVersion->Attribute("NextPath");
				if(szValue)
				{
					VI.szPath = szValue;
				}
				vtVI.push_back( VI );
				lpVersion = lpVersion->NextSiblingElement("Version");
			}
		}

		ZipDocVer.CloseZipFile();
		versiondoc.Clear();

	}

	//��������ذ汾��
	if(bGetNewVer)
	{
		cleandir();
		SetTip(_T(""));
		SetGetVer();
		bGetNewVer=false;
		
		return 0;
	}
	
	//��Ȳ��ø���
	if (strVersion_NEW == s_strVersion)
	{
        SetTip(_T("file_exist_is_most_new"));
		vtVI.clear();
		s_iplist.clear();
		cleandir();
		SetFinish();
		return 0;
	}


	for ( int i=0; i< vtVI.size()&& !isDownCancel(); i++ )
	{	
		if( vtVI[i].szCurVersion == s_strVersion )
		{
			downpack1(s_httpdownload);
		}
	}
	
	if(isDownCancel())
	{
		SetTip(_T("update_task_cancel"));
		cleandir();
		return 0;
	}
    
	//�������һ�����°�
	if(s_strVersion!=strVersion_NEW)downpack1(s_httpdownload);
	if (!isDownCancel())
	{
		SetLocalVersion(s_strVersion.c_str());
	}

	cleandir();
	SetTip(_T("update_over"));
	FILE * pf =fopen(NEW_LAUNCHER_TEMP_NAME,"r");
	if(pf)
	{
		fclose(pf);
		extern void RENANE_APP();		
		RENANE_APP();

		extern bool bRebootApp	;
		bRebootApp=true;

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		BOOL ret = CreateProcess(NEW_LAUNCHER_TEMP_NAME,
			NULL,
			NULL, 
			NULL, 
			FALSE, 
			0, 
			NULL, 
			NULL, 
			&si,
			&pi );	

		CWnd * dlg=         AfxGetApp()-> GetMainWnd();
		::SendMessage(dlg->m_hWnd,WM_CLOSE,NULL,0);
		return 0;
	}
	SetFinish();
	return 0;
}
