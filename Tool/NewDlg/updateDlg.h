// updateDlg.h : header file
//

#pragma once
#include <vector>
#include "KbcButton.h"
#include <string>
#include <afxtempl.h>

#include "crc32.h"
using std::string;

#include "TE_Socket.h"
#include "httpdownload.h"
#include "INetDownload.h"

#include "ZipWrapper.h"
#include "vfs.h"




using std::vector;
using Crypto::CCRC32;

#define DRAGGING	0x01	// dragging flag
// CupdateDlg dialog

//单区所需的服务器IP地址
typedef struct tagAreaServerIpInfo
{
	_tstring strServerList;
	_tstring strServerOnlineInfo;
	std::vector<_tstring> DownLoadIPList;
}AREASERVERIPINFO;

struct VersionInfo
{
	std::string szCurVersion;
	std::string szNextVersion;
	std::string szPath;
	BOOL		bNeedPack;
};

struct progress_message
{
  int totallen;
  int downlen;
  int type;
};

struct	BtnInfo
{
	string	_szName;
	string	_szImg;
	RECT	_rc;
	string	_szTip;
	string	_szHref;
	string  _port;	
	string  _app;
};



typedef std::vector<BtnInfo> TipList;
extern TipList tiplist_;
class CupdateDlg 
{
// Construction
public:
	typedef std::vector<BtnInfo> IPList;
	IPList iplist_;

	
	TiXmlDocument	m_TiXmlDoc;	//保存xml用于写入文件
	TiXmlElement*	m_TiElemRoot;	//保存root节点 这个不用更改 


	typedef struct tagDownLoadFileInfo
	{
		tagDownLoadFileInfo()
		{
			bUseCompress = false;
			bVFSUnit = false;
			strSaveLocalFilePath="";
		};
		_tstring strHostFilePath;
		_tstring strLocalFilePath;
		_tstring strChangeTime;
		_tstring strFileName;
		_tstring strCRC;
		_tstring strPacketName;
		_tstring strSaveLocalFilePath;
		bool bUseCompress;
		bool bVFSUnit;
	}DOWNLOADFILEINFO;

	typedef std::vector<DOWNLOADFILEINFO> UpdateList;

	HANDLE hHandle;
	bool start(int idx = 0);
	//void update();
	bool static SetLocalVersion(const TCHAR* szVersion);   //设置本地版本
	static void UpdataFileToPacket(UpdateList& updatalist); 
	
	
    static UpdateList& GetUpdateFile(_tstring strVersionXML, _tstring strLocalPath,bool is_autopatch = true);       //分析需要下载的文件
	static bool CheckNeedUpdateSelf();


public:

	static int downpack1(IDownLoad	*s_httpdownload);//下载每个版本的函数
    static DWORD WINAPI UpdateThreadProc(LPVOID lpParam);//主线程
};
