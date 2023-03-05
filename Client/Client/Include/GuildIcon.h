//�����־
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

enum LOADRESULT		//����ͼƬ�Ľ��
{
	LR_FALSE,					//ʧ��
	LR_TYPE_WRONG,		//��ʽ����
	LR_SIZE_WRONG,		//�ߴ����
	LR_BPP_WRONG,		//ɫ�����
	LR_SUCCESS				//�ɹ�
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
	LPBYTE	GetByteFromFile_NeedReleaseMem(const char* filePath,BaseInfo* pbaseinf = NULL);				//��ȡ�ļ�������δ�ͷ��ڴ�
	LOADRESULT	LoadAndCheckIconFromLocal(const char* LocalPath,const char* GuildName = NULL);										//�����ļ�·��������ɹ����ϴ���server
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
	void		DrawGuildIcon(int x,int y,DWORD dwColor);																				//��ICON
	BOOL	RegisterIconFromLocal(ULONG ulCrcCode);																	//���Ҳ���Ȿ���Ƿ������貢�Ϸ���iconͼƬ
	BOOL	RegisterIconFromServer(ULONG ulCrcCode, LPBYTE pbyte,DWORD dwSize = 4140);		//��server�����ļ�������,�����ڱ��ش���һ��
protected:
	int				ICIdx;
	BOOL		bShow;
	static		std::string	LocalPath;
	static		SizeInfo		m_sizeinf;
};