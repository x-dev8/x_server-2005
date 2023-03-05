//工会标志
#pragma once
#include <windows.h>
#include <string>
#include "FileSearch.h"
#include "MessageDefine.h"
#include "GuildMessage.h"

#include "MotionBillBoard.h"

#define	TGA_SIZE_INLOW	32
#define	TGA_SIZE_DRAW	16
#define	FOLDER_NAME	"\\GuildPic\\"

enum LOADRESULT		//载入图片的结果
{
	LR_FALSE,					//失败
	LR_TYPE_WRONG,		//格式错误
	LR_SIZE_WRONG,		//尺寸错误
	LR_BPP_WRONG,		//色深错误
	LR_SUCCESS				//成功
};

struct BaseInfo
{
	BaseInfo()
	{
		bIsTga	=	FALSE;
		dwWidth = 0;
		dwHeight = 0;
		dwSize = 0;
	}
	BOOL	bIsTga;
	DWORD dwBpp;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwSize;
};

struct SizeInfo
{
	SizeInfo()
	{
		off_x = 0;
		off_y = 0;
		usDrawSize = 0;
	}
	short off_x;
	short off_y;
	WORD	usDrawSize;
};

class CTgaManager
{
public:
	FileIO::CFileSearch::FileList	 FindTgaFile();
	std::string FindTgaPath();
	void		SaveTgaToLocal(const char* path);
	LPBYTE	GetByteFromFile_NeedReleaseMem(const char* filePath,BaseInfo* pbaseinf = NULL);				//读取文件，这里未释放内存
	LOADRESULT	LoadAndCheckIconFromLocal(const char* LocalPath,const char* GuildName = NULL);										//给出文件路径，载入成功则上传到server
	ULONG	GetCRCCodeOfTga(const char* fileName);
	/*BOOL	GetTgaByteAndSaveLocal(MsgReqTgaIcon* pMrti);*/
	static CTgaManager* GetTgaManager()
	{
		static CTgaManager tgaInstance;
		return &tgaInstance;
	}
};

class GuildIcon
{
public:
	GuildIcon();
	~GuildIcon ();
	void		SetShowIcon(BOOL bShowIcon);
	void		GetGuildCRC(WORD ID,const char* GuildName,ULONG ulCRCcode);
	void		DrawGuildIcon(int x,int y,DWORD dwColor);																				//画ICON
	BOOL	RegisterIconFromLocal(ULONG ulCrcCode);																	//查找并检测本地是否有所需并合法的icon图片
	BOOL	RegisterIconFromServer(ULONG ulCrcCode, LPBYTE pbyte,DWORD dwSize = 4140);		//从server接收文件数据流,并且在本地储存一份
protected:
	int				ICIdx;
	BOOL		bShow;
	static		std::string	LocalPath;
	static		SizeInfo		m_sizeinf;
};