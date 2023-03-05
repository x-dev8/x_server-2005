// UpdateMaker.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "vfs.h"
#include "MeRTLibs.h"
#include "tstring.h"
#include "FileSearch.h"
#include "tinyxml.h"
#include "crc32.h"

#include "ZipWrapper.h"
//#include <mbctype.h>
//#include <windows.h>
#include <direct.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <map>
#include <hash_map>
#include <process.h>

#pragma   comment(lib, "winmm.lib ") 

using Common::_tstring;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using FileIO::CFileSearch;
using Crypto::CCRC32;
using std::fstream;
using std::map;
using std::pair;
using FileIO::CZipWrapper;
using FileIO::CVFS;

const unsigned int MIN_COMPRESS_LENGTH = 0;        //��Сѹ����С
const unsigned int MAX_FILE_NAME       = 64;
typedef struct
{
	char szFolder[MAX_FILE_NAME];
	char szPacket[MAX_FILE_NAME];
}FolderToPacket;

std::vector<FolderToPacket>  g_PacketList;

#define  PacketConfig     "packetconfig.xml"
typedef struct tagDownLoadFileInfo
{
	tagDownLoadFileInfo()
	{
		bUseCompress = false;
		bVFSUnit = false;
	};
	_tstring strHostFilePath;
	_tstring strLocalFilePath;
	_tstring strChangeTime;
	_tstring strFileName;
	_tstring strCRC;
	_tstring strPacketName;
	bool bUseCompress;
	bool bVFSUnit;
}DOWNLOADFILEINFO;

typedef std::vector<DOWNLOADFILEINFO> UpdateList;

UpdateList s_downlist;
UpdateList& GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath);

void LoadPacketList()
{
	TiXmlDocument doc(_tANSICHAR(PacketConfig));

	if(!doc.LoadFile())
	{
		system(_tANSICHAR(PacketConfig));
		return ;
	}	
	TiXmlElement* pElement = doc.FirstChildElement("packet");
	if(pElement)
	{
		TiXmlElement*  pElement1 = pElement->FirstChildElement("Folder");
		while(pElement1)
		{
			FolderToPacket packet;
			strcpy(packet.szFolder,pElement1->Attribute("name"));
			strcpy(packet.szPacket,pElement1->Attribute("packetname"));
			g_PacketList.push_back(packet);
			pElement1 = pElement1->NextSiblingElement("Folder");
		}
	}	
}
bool FindPacketFromFileName(const char* pFileName,FolderToPacket& node)
{

	std::vector<FolderToPacket>::iterator itb = g_PacketList.begin();
    for (;itb !=g_PacketList.end();++itb)
    {
		const char* plast = strstr(pFileName,(*itb).szFolder);
		int nIndex = plast-pFileName;
		if(nIndex == 0)
		{
			node = (*itb);
			return true;
		}
    }
	return false;	
}
_tstring GetExtendName(_tstring& strFile)
{
    _tstring strExternName;
    if (strFile.empty())
    {
        return strExternName;
    }
    size_t nLength = strFile.length();
    for (size_t i = nLength-1; i>0; i--)
    {
        if (strFile[i] == _T('.'))
        {
            strExternName = strFile.substr(i+1, nLength-i-1);
            return strExternName;
        }
    }
    return strExternName;
}

//�������Ŀ¼
bool MakeEmbedFolder(_tstring& strFolderPath)
{
    _tstring strPath = strFolderPath;
    if (strPath[strPath.length()-1] != _T('\\'))
    {
        strPath += _T("\\");
    }
    size_t nLength = strPath.length();
    for (size_t i = 0; i<nLength; i++)
    {
        if (strPath[i] == _T('\\'))
        {
            _tstring strFolder = strPath.substr(0, i);
            if (_mkdir(strFolder.toNarrowString().c_str()) == ENOENT)
            {
                return false;
            }
        }
    }
    return true;
}

//��ȡ��Ŀ¼�����·���ļ�����
_tstring GetFolder(_tstring strPath, _tstring strFilePath)
{
    strFilePath.Replace(_T("/"), _T("\\"));
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
_tstring GetFileName(_tstring strFilePath)
{
    strFilePath.Replace(_T("/"), _T("\\"));
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

_tstring GetFileLength(_tstring& strFile)
{
    _tstring length = _T("0");
    fstream file(_tUNICODECHAR(strFile), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        return length;
    }

    file.seekg(0, std::ios::end);
    unsigned int nlength = file.tellg();
    if (nlength == 0)
    {
        return length;
    }
    else
    {
        length.Format(_T("%d"), nlength);
        return length;
    }
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

// updatemaker.exe c:\game		1.1		   Y				Y
//                  ���Ŀ¼    �汾��	�Ƿ�ѹ��	�Ƿ�ʹ�������ļ�ϵͳ

int _tmain(int argc, _TCHAR* argv[])
{
	LoadPacketList();
    bool bUseCompress = false;
    bool bUseVFS = false;
    map<_tstring, TiXmlNode*> nodelist;
	cout << _tANSICHAR(_T("�汾��Ϣ���ɹ��� 2009\n")) << endl;
	cout << _tANSICHAR(_T("������ͻ�������Ŀ¼:")) << endl;


	_tstring strPath;
	_tstring strVersion;
	_tstring strCompress;
	_tstring strUseVFS;

	if( argc >= 5 )
	{
		strPath = argv[1];
	}
	else
	{
		string Path;
		
		cin >> Path;
		strPath = Path;
	}
	//��·�����油��'\\'
    if (strPath[strPath.length()-1] != _T('\\'))
    {
        strPath += _T("\\");
    }


	if( argc >= 5 )
	{
		strVersion = argv[2];
	}
	else
	{
		string Version;


		cout << _tANSICHAR(_T("������汾�ţ��汾��ֻ��Ϊ���ּ�С���㣩��")) << endl;
		cin >> Version;
		strVersion = Version;
	}

    _tstring strXMLDoc;
    strXMLDoc.Format(_T("%s\\versioninfo_%s.xml"), strVersion.c_str(), strVersion.c_str());

    TiXmlDocument tmp(_tANSICHAR(strXMLDoc));
    if (tmp.LoadFile())
    {
        cout << _tANSICHAR(_T("�˰汾�Ѿ����ڣ�")) << endl;
        system(_tANSICHAR("pause"));
        return false;
    }
 
    cout << _tstring(_T("����ͳ��Ŀ¼���ļ���Ϣ������")).toNarrowString() << endl;
    CFileSearch search;
    size_t nCount = search.Find(strPath, _T(""), true);

    if (nCount == 0)
    {
        cout << _tANSICHAR(_T("Ŀ¼��δ�ҵ��κ��ļ����ļ��С�����")) << endl;
        system(_tANSICHAR(_T("pause")));
        return 0;
    }

    _tstring strFileInfo;
    strFileInfo.Format(_T("Ŀ¼�¹��ҵ�\n�ļ��й��� %d ��\n�ļ����� %d ��\n"), search.GetFolder().size(), search.GetFile().size());
    cout << strFileInfo.toNarrowString() << endl;

	if( argc >= 5 )
	{
		strCompress = argv[3];
		strCompress.MakeUpper();
	}
	else
	{
		string Compress;
		while (strCompress != _T("Y") && strCompress != _T("N"))
		{
			cout << _tANSICHAR(_T("�Ƿ�����ѹ���� Y/N")) << endl;
			cin >> Compress;
			strCompress = Compress;
			strCompress.MakeUpper();
		}
	}

    //�Ƿ�����ѹ��
    if (strCompress == _T("Y"))
    {
        bUseCompress = true;
    }
    else
    {
        bUseCompress = false;
    }

	if( argc >= 5 )
	{
		strUseVFS = argv[4];
		strUseVFS.MakeUpper();
	}
	else
	{
		string UseVFS;


		while (strUseVFS != _T("Y") && strUseVFS != _T("N"))
		{
			cout << _tANSICHAR(_T("�Ƿ�ɨ�������ļ�ϵͳ�ڲ��ļ��� Y/N")) << endl;
			cin >> UseVFS;
			strUseVFS = UseVFS;
			strUseVFS.MakeUpper();
		}
	}

    //�Ƿ�����ѹ��
    if (strUseVFS == _T("Y"))
    {
        bUseVFS = true;
    }
    else
    {
        bUseVFS = false;
    }
	//for( int k = 0; k < argc; k++ )
	//{
	//	MessageBox( 0, argv[k], (LPCWSTR)"", MB_OK );
	//}
    //���ڴ����汾����
    _mkdir(_tANSICHAR(strVersion));

    cout << _tANSICHAR(_T("��������XML�汾��Ϣ������")) << endl;

    TiXmlDocument doc(_tANSICHAR(strXMLDoc));

    _tstring strXMLHead = _T("<?xml version = 1.0 encoding=UTF-8 ?>");
    doc.Parse(strXMLHead.toUTF8().c_str());

    if (doc.Error())
    {
        cout << _tANSICHAR(_T("XML���ɴ���")) << doc.Value() << doc.ErrorDesc() << endl;
        system(_tANSICHAR(_T("pause")));
        return 0;
    }

    CFileSearch::FileList& file = search.GetFile();
    CFileSearch::FileList& folder = search.GetFolder();

    TiXmlElement root(_tUTF8CHAR(_T("VersionInfo")));
    TiXmlElement ver(_tUTF8CHAR(_T("Version")));
    ver.InsertEndChild(TiXmlText(_tUTF8CHAR(strVersion)));
    root.InsertEndChild(ver);

    //�������Ŀ¼�б�
    TiXmlElement folderlist(_tUTF8CHAR(_T("FileList")));
    size_t foldercount = folder.size();
    size_t strPathsize = strPath.size();
    for (size_t i=0; i<foldercount; i++)
    {
        folder[i].MakeLower();      //ȫ��ת����Сд
        TiXmlElement tmp(_tUTF8CHAR(_T("Folder")));
        _tstring strFolder = folder[i].substr(strPathsize, folder[i].length()-strPathsize-1);
        tmp.InsertEndChild(TiXmlText(_tUTF8CHAR(strFolder)));

		FolderToPacket packetinfo;
		if(FindPacketFromFileName(strFolder.c_str(),packetinfo))
		{
			TiXmlElement elemenPacket(_tUTF8CHAR(_T("packet")));
			elemenPacket.InsertEndChild(TiXmlText(_tUTF8CHAR(packetinfo.szPacket)));
			tmp.InsertEndChild(elemenPacket);
		}					
        TiXmlNode* p = folderlist.InsertEndChild(tmp);
        if (p != NULL)
        {
            nodelist.insert(std::pair<_tstring, TiXmlNode*>(_tstring(folder[i].substr(strPathsize, folder[i].length()-strPathsize-1)), p));
        }
        _tstring strVersionFolder = strVersion + _T("\\") + strFolder;
        MakeEmbedFolder(strVersionFolder);
    }

    size_t filecount = file.size();
    for (size_t i=0; i<filecount; i++)
    {
        file[i].MakeLower();
        _tstring& strFilePath = file[i];
        _tstring strFileName = GetFileName(strFilePath);
        _tstring strExtendName = GetExtendName(strFileName);

        //�ж��Ƿ������ļ�ϵͳ ����ǲ������������ļ�ϵͳ���ϵ�����ļ�ϵͳ�ڵ��ļ�
		CVFS vfs;
        if (bUseVFS && strExtendName.MakeLower() == _T("vfs") && vfs.LoadVFS(strFilePath.c_str()))
        {
            _tstring subfolder = strFilePath.substr(strPathsize, strFilePath.length()-strPathsize);
            TiXmlElement elementfolder(_tUTF8CHAR(_T("VFolder")));
            elementfolder.InsertEndChild(TiXmlText(_tUTF8CHAR(subfolder)));
            
            map<_tstring, TiXmlNode*> tmpmap;
            //ѭ����ȡVFS���ڵ��ļ�
            CVFS::UNITLIST list = vfs.GetUnitList();
            while (!list.empty())
            {
                CVFS::UNITLIST::iterator itr = list.begin();
                CVFS::UNITINFO& info = itr->second;
                _tstring strLength;
                strLength.Format(_T("%d"), info.nLength);
                _tstring strCRC;
                strCRC.Format(_T("%d"), info.nCrc);
                _tstring strVFSFile = info.strFile;
                _tstring strFolder = GetFolder(_T(""), strVFSFile);
                _tstring strFileName = GetFileName(strVFSFile);

                //************************************************
                //�����XML��

                TiXmlElement elementvfile(_tUTF8CHAR("File"));
                elementvfile.InsertEndChild(TiXmlText(_tUTF8CHAR(strFileName)));
                TiXmlElement elementcrc(_tUTF8CHAR(_T("Crc")));
                elementcrc.InsertEndChild(TiXmlText(_tUTF8CHAR(strCRC)));
                TiXmlElement elementsize(_tUTF8CHAR(_T("Size")));
                elementsize.InsertEndChild(TiXmlText(_tUTF8CHAR(strLength)));
                elementvfile.InsertEndChild(elementcrc);
                elementvfile.InsertEndChild(elementsize);

                _tstring strLocalSaveFile;
                strLocalSaveFile.Format(_T("%s\\%s\\%s"), strVersion.c_str(), subfolder.c_str(), strVFSFile.c_str());
                if (!vfs.SaveUnitToFile(strVFSFile.c_str(), strLocalSaveFile.c_str()))
                {
                    _tstring strErr;
                    strErr.Format(_T("�����ļ� %s ʧ�ܣ�"), strLocalSaveFile.c_str());
                    cout << _tANSICHAR(strErr) << endl;
                    system(_tANSICHAR(_T("pause")));
                    return 0;
                }
                //����ѹ��
                if (bUseCompress && info.nLength >= MIN_COMPRESS_LENGTH)
                {
                    elementvfile.SetAttribute(_tUTF8CHAR(_T("Compress")), _tUTF8CHAR(_T("1")));
                    _tstring strZipFile = strLocalSaveFile + _T(".zip");
                    CZipWrapper zip(strZipFile.c_str(), FileIO::WARP_APPEND_STATUS_CREATE);
                    if (!zip.IsOpen())
                    {
                        _tstring strErr;
                        strErr.Format(_T("�����ļ� %s ʧ�ܣ�"), strZipFile.c_str());
                        cout << _tANSICHAR(strErr) << endl;
                        system(_tANSICHAR(_T("pause")));
                        return 0;
                    }
                    if (!zip.AddFileFromLocalFile(strLocalSaveFile.c_str(), GetFileName(strLocalSaveFile).c_str()))
                    {
                        _tstring strErr;
                        strErr.Format(_T("ѹ���ļ� %s ʧ�ܣ�"), strZipFile.c_str());
                        cout << _tANSICHAR(strErr) << endl;
                        system(_tANSICHAR(_T("pause")));
                        return 0;
                    }
                    remove(_tANSICHAR(strLocalSaveFile));
                }

                if (strFolder.empty())
                {
                    //��ӵ���Ŀ¼��
                    elementfolder.InsertEndChild(elementvfile);
                }
                else
                {
                    strFolder.MakeLower();
                    strFolder.Replace(_T("/"), _T("\\"));
                    map<_tstring, TiXmlNode*>::iterator itr = tmpmap.find(strFolder);
                    if (itr != tmpmap.end())
                    {
                        itr->second->InsertEndChild(elementvfile);
                    }
                    else            //����һ��Ŀ¼
                    {
                        TiXmlElement elementtmp(_tUTF8CHAR(_T("Folder")));
						FolderToPacket packetinfo;
						if(FindPacketFromFileName(strFolder.c_str(),packetinfo))
						{
							TiXmlElement elemenPacket(_tUTF8CHAR(_T("packet")));
							elemenPacket.InsertEndChild(TiXmlText(_tUTF8CHAR(packetinfo.szPacket)));
							elementtmp.InsertEndChild(elemenPacket);
						}					
                        elementtmp.InsertEndChild(TiXmlText(_tUTF8CHAR(strFolder)));
                        TiXmlNode* p = elementfolder.InsertEndChild(elementtmp);
                        if (p != NULL)
                        {
                            tmpmap.insert(pair<_tstring, TiXmlNode*>(strFolder, p));
                            p->InsertEndChild(elementvfile);
                        }
                        else
                        {
                            _tstring strErr;
                            strErr.Format(_T("�����ڵ� %s ʧ�ܣ�"), strFolder.c_str());
                            cout << _tANSICHAR(strErr) << endl;
                            system(_tANSICHAR(_T("pause")));
                            return 0;
                        }
                    }
                }

                list.erase(itr);
            }

            folderlist.InsertEndChild(elementfolder);
        }
        else
        {
            _tstring strLength = GetFileLength(strFilePath);
            _tstring strCRC = GetFileCrc(strFilePath);
            _tstring strDate = GetFileDate(strFilePath);

            if (strDate.empty())
            {
                cout << _tANSICHAR(strFilePath) << _tANSICHAR("��ȡ�ļ�������Ϣʧ�ܣ�") << endl;
                system("pause");
            }
            unsigned int nLength = atoi(_tANSICHAR(strLength));

            TiXmlElement elementfile(_tUTF8CHAR(_T("File")));
            elementfile.InsertEndChild(TiXmlText(_tUTF8CHAR(strFileName)));

            //����ѹ��
            if (bUseCompress && nLength >= MIN_COMPRESS_LENGTH)
            {
                elementfile.SetAttribute(_tUTF8CHAR(_T("Compress")), _tUTF8CHAR(_T("1")));
            }

            TiXmlElement elementcrc(_tUTF8CHAR(_T("Crc")));
            elementcrc.InsertEndChild(TiXmlText(_tUTF8CHAR(strCRC)));

            TiXmlElement elementsize(_tUTF8CHAR(_T("Size")));
            elementsize.InsertEndChild(TiXmlText(_tUTF8CHAR(strLength)));

            TiXmlElement elementdate(_tUTF8CHAR(_T("Date")));
            elementdate.InsertEndChild(TiXmlText(_tUTF8CHAR(strDate)));

            _tstring strFolder = GetFolder(strPath, strFilePath);

            elementfile.InsertEndChild(elementsize);
            elementfile.InsertEndChild(elementcrc);
            elementfile.InsertEndChild(elementdate);

            //Ϊ��Ŀ¼
            if (strFolder == _T(""))
            {
                folderlist.InsertEndChild(elementfile);
            }
            else
            {
                map<_tstring, TiXmlNode*>::iterator itr = nodelist.find(strFolder);
                if (itr != nodelist.end())
                {
                    TiXmlNode& node = *itr->second;
                    node.InsertEndChild(elementfile);
                }
            }
            _tstring strNewPath = strVersion;
            strNewPath += _T("\\");
            strNewPath += strFolder;
            strNewPath += _T("\\");
            strNewPath += strFileName;
            
            //��ѡ��ѹ���������ļ�С��10K
            if (!bUseCompress || nLength < MIN_COMPRESS_LENGTH)
            {
                if (!CopyFile(strFilePath.c_str(), strNewPath.c_str(), FALSE))
                {
                    _tstring strErr;
                    strErr.Format(_T("�ļ� %s ���Ƶ� %s ʧ�ܣ�"), strFilePath.c_str(), strNewPath.c_str());
                    cout << _tANSICHAR(strErr) << endl;
                }
            }
            else
            {
                strNewPath += _T(".zip");
                CZipWrapper zip(strNewPath.c_str(), FileIO::WARP_APPEND_STATUS_CREATE);
                if (!zip.IsOpen())
                {
                    _tstring strErr;
                    strErr.Format(_T("ѹ���ļ� %s ����ʧ�ܣ�"), strNewPath.c_str());
                    cout << _tANSICHAR(strErr) << endl;
                }
                
                if (!zip.AddFileFromLocalFile(strFilePath.c_str(), strFileName.c_str()))
                {
                    _tstring strErr;
                    strErr.Format(_T("ѹ���ļ� %s ���ʧ�ܣ�"), strNewPath.c_str());
                    cout << _tANSICHAR(strErr) << endl;
                }
            }
        }
    }

    root.InsertEndChild(folderlist);



    doc.InsertEndChild(root);
    doc.SaveFile();

    _tstring strZipXml;
    strZipXml = strXMLDoc + _T(".zip");
    CZipWrapper zipxml(strZipXml.c_str(), FileIO::WARP_APPEND_STATUS_CREATE);
    if (!zipxml.AddFileFromLocalFile(strXMLDoc.c_str(), strXMLDoc.c_str()))
    {
        cout << _tANSICHAR(_T("ѹ���汾��Ϣ����")) << endl;
        system(_tANSICHAR(_T("pause")));
        return false;
    }

    zipxml.CloseZipFile();
    /*remove(_tANSICHAR(strXMLDoc));*/
    cout << _tANSICHAR(_T("�汾������ɣ�")) << endl;
    system(_tANSICHAR(_T("pause")));

	return 0;
}

UpdateList& GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath)
{
	
		if (!strLocalPath.empty() && strLocalPath[strLocalPath.length()-1] != _T('\\'))
		{
			strLocalPath += _T("\\");
		}


		TiXmlDocument doc(_tANSICHAR(strVersionXML));

		if (!doc.LoadFile())
		{
			return s_downlist;
		}
		TiXmlNode* nodeversioninfo = doc.FirstChild(_tUTF8CHAR(_T("VersionInfo")));
		if (nodeversioninfo == NULL)
		{
			return s_downlist;
		}

		TiXmlNode* nodefilelist = nodeversioninfo->FirstChild(_tUTF8CHAR(_T("FileList")));
		if (nodefilelist == NULL)
		{
			return s_downlist;
		}

		//�ȰѸ�Ŀ¼�µ��ļ�����һ��
		TiXmlElement* elementfile = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("File")));
		while (elementfile != NULL)
		{
			_tstring strFile;
			strFile.fromUTF8(elementfile->GetText());

			// 			//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
			// 			if (strFile == _T(g_szUpdateFile))
			// 			{
			// 				elementfile = elementfile->NextSiblingElement();
			// 				continue;
			// 			}
			// 			_tstring strTip;
			// 			strTip.Format(_T(m_mapStringSet[52].c_str()), strLocalPath.c_str(), strFile.c_str());
			// 			SetTip(strTip);

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
			info.strHostFilePath += strFile;
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
					;//SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);
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
		while (elementfolder != NULL /*!g_bIsEnd*/)
		{
			_tstring strFolder;
			strFolder.fromUTF8(elementfolder->GetText());
			if (strFolder[strFolder.length()-1] != _T('\\'))
			{
				strFolder += _T("\\");
			}
			MakeEmbedFolder(strFolder);

			_tstring strPacketName;
			TiXmlElement* pElementPacket = elementfolder->FirstChildElement(_tUTF8CHAR(_T("packet")));
			if(pElementPacket)
				strPacketName.fromUTF8(pElementPacket->GetText());//������

			TiXmlElement* elementfile = elementfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
			while (elementfile != NULL/*!g_bIsEnd*/)
			{
				_tstring strFile;
				strFile.fromUTF8(elementfile->GetText());

				//���ϴ�Ű汾�ŵ��ļ�update.xml���򲻸���
				// 				if (strFile == _T(g_szUpdateFile))
				// 				{
				// 					elementfile = elementfile->NextSiblingElement();
				// 					continue;
				// 				}
				// 
				// 				_tstring strTip;
				// 				strTip.Format(_T(m_mapStringSet[53].c_str()), strLocalPath.c_str(), strFolder.c_str(), strFile.c_str());
				// 				SetTip(strTip);

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

				if (strDate != GetFileDate(info.strLocalFilePath))
				{
					if  (strCrc != GetFileCrc(info.strLocalFilePath))
					{
						s_downlist.push_back(info);
					}
					else
					{
						;/*SetFileChangeTime(info.strLocalFilePath, info.strChangeTime);*/
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
			elementfolder = elementfolder->NextSiblingElement(_tUTF8CHAR(_T("Folder")));
		}

		//���ڷ��������ļ�ϵͳ
		TiXmlElement* elementvfolder = nodefilelist->FirstChildElement(_tUTF8CHAR(_T("VFolder")));
		while (elementvfolder != NULL /*&& !g_bIsEnd*/)
		{
			_tstring strVFSFile;
			strVFSFile.fromUTF8(elementvfolder->GetText());
			CVFS vfs;
			//����VFS�ļ���������������½���
			if (!vfs.LoadVFS(strVFSFile.c_str()))
			{
				if (!vfs.NewVFSFile(strVFSFile.c_str()))
				{
					return s_downlist;//throw Common::CException(0, _T(m_mapStringSet[54].c_str()), strVFSFile.c_str());
				}
			}
			CVFS::UNITLIST list = vfs.GetUnitList();
			//���������ļ�ϵͳ��Ŀ¼���ļ�
			TiXmlElement* elementvfile = elementvfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
			while (elementvfile != NULL /*&& !g_bIsEnd*/)
			{
				DOWNLOADFILEINFO info;
				info.bVFSUnit = true;
				info.strLocalFilePath = strVFSFile;
				info.strFileName.fromUTF8(elementvfile->GetText());

				// 				_tstring strTip;
				// 				strTip.Format(_T(m_mapStringSet[55].c_str()), info.strFileName.c_str());
				// 				SetTip(strTip);

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
			while (elementvsubfolder != NULL /*&& !g_bIsEnd*/)
			{
				_tstring strVsubfolder;
				strVsubfolder.fromUTF8(elementvsubfolder->GetText());
				//���������ļ�ϵ��Ŀ¼���ļ�
				TiXmlElement* elementvsubfile = elementvsubfolder->FirstChildElement(_tUTF8CHAR(_T("File")));
				while (elementvsubfile != NULL /*&& !g_bIsEnd*/)
				{
					DOWNLOADFILEINFO info;
					info.bVFSUnit = true;
					info.strLocalFilePath = strVFSFile;
					_tstring strFile;
					strFile.fromUTF8(elementvsubfile->GetText());
					info.strFileName.Format(_T("%s\\%s"), strVsubfolder.c_str(), strFile.c_str());

					// 					_tstring strTip;
					// 					strTip.Format(_T(m_mapStringSet[55].c_str()), info.strFileName.c_str());
					// 					SetTip(strTip);

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
			// 			if (!vfs.Save(ChangeProcCallBack))
			// 			{
			// 				throw Common::CException(0, _T(m_mapStringSet[56].c_str()), strVFSFile.c_str());
			// 			}
			elementvfolder = elementvfolder->NextSiblingElement(_tUTF8CHAR(_T("VFolder")));
		}
	

	return s_downlist;
}
