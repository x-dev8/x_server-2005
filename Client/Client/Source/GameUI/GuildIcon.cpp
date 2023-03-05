#include "GuildIcon.h"
#include <assert.h>
#include "MiniMap.h"
#include "tga.h"
#include "ui/MiniMapUI.h"
#include "MeUi/UIPicture.h"
#include "gamemain.h"
#include "Player.h"
#include "playermgr.h"
#include "MeUi/UiManager.h"
#include "CfgFileLoader.h"
#include "ui/NpcChatDialogBox.h"
#include "ui/LoadMap.h"
#include <math.h>
#include "ui/BillBoard.h"
#include "tga.h"
#include "globaldef.h"
#include "GlobalDef.h"
#include "NpcCoord.h"
#include <vector>
#include "IOXMLObject.h"
#include "RapidXml/MeRapidXml.h"
#include "color_config.h"
#include "CRC32.h"
#include "Cfg.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"

std::string	GuildIcon::LocalPath;
SizeInfo		GuildIcon::m_sizeinf;

#define GUILDICON_XML_ROOT "GuildIcon"

GuildIcon::GuildIcon()
{
	ICIdx = -1;
	bShow = FALSE;
	if (GuildIcon::LocalPath.empty())
	{
		char buffer[256] = {0};
		::GetCurrentDirectory(256,buffer);
		GuildIcon::LocalPath.clear();
		GuildIcon::LocalPath = buffer;
		GuildIcon::LocalPath += FOLDER_NAME;
		GuildIcon::m_sizeinf.off_x = 0;
		GuildIcon::m_sizeinf.off_y = 0;
		GuildIcon::m_sizeinf.usDrawSize = TGA_SIZE_DRAW;
	}
}


GuildIcon::~GuildIcon()
{
	if (ICIdx != -1)
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture(ICIdx);
		ICIdx = -1;
	}
}

void GuildIcon::SetShowIcon(BOOL bShowIcon)
{
	this->bShow = bShowIcon;
	int Ingter = 0;
	MeXmlDocument doc;
	if( !doc.LoadFile( XML_GLOBALCONFIG_FILENAME ) )
	{
		assert(false && "GuildIcon 读取文件失误");
	}
	MeXmlElement* pGlobalRoot = doc.FirstChildElement( XML_GLOBALCONFIG_ROOT_NAME );
	MeXmlElement* pRoot = pGlobalRoot->FirstChildElement( GUILDICON_XML_ROOT );
	MeXmlElement* lpRoot = pRoot->FirstChildElement("DRAWICON");
	if(lpRoot)
	{
		lpRoot->Attribute("OFFX",&Ingter);
		GuildIcon::m_sizeinf.off_x = (short)Ingter;
		lpRoot->Attribute("OFFY",&Ingter);
		GuildIcon::m_sizeinf.off_y = (short)Ingter;
		lpRoot->Attribute("Size",&Ingter);
		GuildIcon::m_sizeinf.usDrawSize = (WORD)Ingter;
	}
}

BOOL GuildIcon::RegisterIconFromLocal(ULONG ulCrcCode)
{
    char szBuf[128] = {0};
	std::string	PathAndName = LocalPath;
	PathAndName += itoa(ulCrcCode, szBuf, 10);
	PathAndName += ".tga";

	BaseInfo	baseinf;
	LPBYTE	pdata = CTgaManager::GetTgaManager()->GetByteFromFile_NeedReleaseMem(PathAndName.c_str(),&baseinf);
	if ( pdata && baseinf.bIsTga && ICIdx == -1 && baseinf.dwWidth == TGA_SIZE_INLOW && baseinf.dwHeight == TGA_SIZE_INLOW)
	{
		ICIdx =	GetEngine()->GetTextureManager()->RegisterTexture(
		szBuf,
		baseinf.dwWidth,
		baseinf.dwHeight,
		pdata,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED
		);
		delete[]	pdata;
		if (ICIdx != -1)
		{
			return TRUE;
		}
	}
	return	FALSE;
}

BOOL GuildIcon::RegisterIconFromServer(ULONG ulCrcCode, LPBYTE pbyte,DWORD dwSize)
{
	Tga tga;
	tga.ReadInfo( pbyte, dwSize );
	DWORD m_dwSrcImageWidth = tga.GetWidth();
	DWORD m_dwSrcImageHeight = tga.GetHeight();

    char szBuf[128] = {0};
    itoa(ulCrcCode, szBuf, 10);

	if (ICIdx != -1)
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture(ICIdx);
		ICIdx = -1;
	}
	if (ICIdx == -1)
	{
		ICIdx =	GetEngine()->GetTextureManager()->RegisterTexture(
			szBuf,
			m_dwSrcImageWidth,
			m_dwSrcImageHeight,
			pbyte,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED
			);
		if (ICIdx != -1)
		{
			std::string	PathAndName = LocalPath;
			PathAndName += szBuf;
			PathAndName += ".tga";
			SetFileAttributes(PathAndName.c_str(),FILE_ATTRIBUTE_NORMAL );
			FILE* pfw = NULL;
			pfw = fopen(PathAndName.c_str(),"wb");
			if (pfw)
			{
				fwrite(pbyte,1,dwSize,pfw);
				fclose(pfw);
			}
			this->SetShowIcon(TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

void GuildIcon::DrawGuildIcon(int x,int y,DWORD dwColor)
{
	if (bShow && ICIdx != -1)
	{
		for (int i =0; i < 24; i++)
		{
			dwColor |= 1<<i;
		}
		x+=GuildIcon::m_sizeinf.off_x;
		y+=GuildIcon::m_sizeinf.off_y;
		RECT	 rt;
		RECT ImgRt;
		rt.left = x;
		rt.top = y;
		rt.right = x + GuildIcon::m_sizeinf.usDrawSize;
		rt.bottom = y + GuildIcon::m_sizeinf.usDrawSize;
		ImgRt.top = 0;
		ImgRt.left = 0;
		ImgRt.right = TGA_SIZE_INLOW;
		ImgRt.bottom = TGA_SIZE_INLOW;
		GetDrawer()->Blt(ICIdx,&rt,&ImgRt,TGA_SIZE_INLOW,TGA_SIZE_INLOW,0,dwColor,0);
	}
}

void GuildIcon::GetGuildCRC(WORD ID,const char* GuildName,ULONG ulCRCcode)
{
	if(ulCRCcode == 0)
	{
		return;
	}
	std::string TgaName = GuildIcon::LocalPath;
	TgaName += GuildName;
	TgaName += ".tga";
	ULONG ulLocalCrc = CTgaManager::GetTgaManager()->GetCRCCodeOfTga(TgaName.c_str());

	if (ulCRCcode == ulLocalCrc)
	{
		if(RegisterIconFromLocal(ulCRCcode))
		{
			SetShowIcon(true);
		}
	}else{
		//MsgAckAskForIcon	msgNeedSend;
		/*msgNeedSend.shCharID = ID;
		GettheNetworkInput().SendMsg(&msgNeedSend);
		GettheNetworkInput().CheckSendReq();*/
	}
}

ULONG CTgaManager::GetCRCCodeOfTga(const char* fileName)
{
	Crypto::CCRC32	crc;
	return crc.GetFileCRC32(fileName);
}

LOADRESULT	CTgaManager::LoadAndCheckIconFromLocal(const char* LocalPath,const char* GuildName)
{
	BaseInfo		baseinf;
	LOADRESULT	result = LR_FALSE;
	LPBYTE	pdata = GetByteFromFile_NeedReleaseMem(LocalPath,&baseinf);
	if (pdata)
	{
		if (baseinf.bIsTga)
		{
			if (baseinf.dwWidth == TGA_SIZE_INLOW && baseinf.dwHeight == TGA_SIZE_INLOW)
			{
				if (baseinf.dwBpp == 32)
				{
					//发送到server
					//MsgAckTgaIcon	Msg2Server;
					//Msg2Server.ulCrCcode	= CTgaManager::GetTgaManager()->GetCRCCodeOfTga(LocalPath);
					//Msg2Server.header.stID	=	theHeroGame.GetPlayerMgr()->GetMyID();
					//if( !theHeroGame.GetPlayerMgr()->GetMe() )
					//{
					//	result = LR_FALSE;
					//}
					//else
					//{
					//	strcpy(Msg2Server.GuildName,theHeroGame.GetPlayerMgr()->GetMe()->GetGuildName());
					//	::CopyMemory(Msg2Server.stFlag.bFlagData,pdata,baseinf.dwSize);
					//	GettheNetworkInput().SendMsg(&Msg2Server);
					//	GettheNetworkInput().CheckSendReq();
					//	result = LR_SUCCESS;
					//}
				}else{
					result = LR_BPP_WRONG;
				}
			}else{
				result = LR_SIZE_WRONG;
			}
		}else{
			result = LR_TYPE_WRONG;
		}
		delete[]	pdata;
	}
	return result;
}

LPBYTE	CTgaManager::GetByteFromFile_NeedReleaseMem(const char* filePath,BaseInfo* pbaseinf)
{
	LPBYTE	pdata = NULL;
	f_Handle*		pfile   = NULL;
	pfile = packet_namespace::w_fopen(filePath,"rb");
	if (pfile)
	{
		packet_namespace::w_fseek(pfile,0,SEEK_END);
		DWORD dwSize = packet_namespace::w_ftell(pfile);
		pdata = MeDefaultNew BYTE[dwSize];
		packet_namespace::w_rewind(pfile);
		packet_namespace::w_fread(pdata,1,dwSize,pfile);
		packet_namespace::w_fclose(pfile);
		Tga tga;
		if ( tga.ReadInfo( pdata, dwSize ) )
		{
			if (pbaseinf)
			{
				pbaseinf->bIsTga = TRUE;
				pbaseinf->dwSize = dwSize;
				pbaseinf->dwBpp = tga.GetBPP();
				pbaseinf->dwWidth = tga.GetWidth();
				pbaseinf->dwHeight = tga.GetHeight();
			}
			return pdata;
		}else{
			return NULL;
		}
	}else{
		return NULL;
	}
}

std::string CTgaManager::FindTgaPath()
{
	char buffer[256] = {0};
	::GetCurrentDirectory(256,buffer);
	std::string path = buffer;
	path += FOLDER_NAME;
	return path;
}

FileIO::CFileSearch::FileList CTgaManager::FindTgaFile()
{
	FileIO::CFileSearch findfile;
	size_t nCount = findfile.Find(_T(FindTgaPath()), _T(".tga"));
	FileIO::CFileSearch::FileList	 flst;
	flst = findfile.GetFile();
	return flst;
}

//BOOL CTgaManager::GetTgaByteAndSaveLocal(MsgReqTgaIcon* pMrti)
//{
//	std::string str1ng = FindTgaPath();
//	str1ng+=pMrti->GuildName;
//	str1ng+=".tga";
//	FILE* pf = NULL;
//	pf = fopen(str1ng.c_str(),"wb");
//	if (pf)
//	{
//		fwrite(pMrti->stFlag.bFlagData,1,4140,pf);
//		fclose(pf);
//	}
//	return TRUE;
//}
