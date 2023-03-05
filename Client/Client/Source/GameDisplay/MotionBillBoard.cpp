#include "MotionBillBoard.h"
#include "ui\Guild_Pic.h"
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
// #include "Tinyxml/tinyxml.h"
#include "color_config.h"
#include "CRC32.h"
#include "MessageDefine.h"
#include "Common.h"
#include "RapidXml/MeRapidXml.h"

char* ValueName[] = {
	"FRIST_FIGHT_OPERATE",
	"FRIST_FIGHT_SKILLLINK",
	"FRIST_FIGHT_BACKATTACK",
	"FRIST_DUTY",
	"FRIST_DUTY_HELP",
	"FRIST_COLLECT",
	"FRIST_COMPOUND",
	"FRIST_SKILL",
	"FRIST_ECONOMY_SYSTEM",
	"BIRTHDAY"
};

CMotionBillBoard	TipBillBoard;

CMotionBillBoard* GetBillBoard()
{
	return &TipBillBoard;
}

SpriteIcon::SpriteIcon(const char* cImgPath,int iWidth,int iFrameCounts,int iSpeed)
{
	this->iPicImg = GetEngine()->GetTextureManager()->RegisterTexture(cImgPath,false,FALSE);
	this->_width = iWidth;
	this->_FrameCounts = iFrameCounts;
	this->_iSpeed = iSpeed;
	this->dwNowTime = 0;
	this->index = 0;
}

SpriteIcon::~SpriteIcon()
{
	if (this->iPicImg == -1)
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture(iPicImg);
		iPicImg = -1;
	}
}

RECT SpriteIcon::GetRectFromImg(int PicWidth,int idx,int lineCounts)
{
	RECT rt = {0,0,0,0};
	int iPerwidth = PicWidth/lineCounts;
	int lineidx = idx%lineCounts;
	int rowidx = idx/lineCounts;
	rt.left = lineidx*iPerwidth;
	rt.right = rt.left+iPerwidth;
	rt.top = rowidx*iPerwidth;
	rt.bottom = rt.top + iPerwidth;
	return rt;
}

void SpriteIcon::DrawSprite(POINT pt)
{
	RECT ImgRt = GetRectFromImg(_width,index);
	RECT rt = {0,0,0,0};
	rt.top = pt.y;
	rt.left = pt.x;
	rt.bottom = pt.y+(_width/4);
	rt.right = pt.x+(_width/4);
	GetDrawer()->Blt(this->iPicImg,&rt,&ImgRt,_width,_width,0,0xffffffff,0);
	if( ::GetTickCount() - dwNowTime > _iSpeed )
	{
		index = ( index == _FrameCounts-1)?0:++index;
		dwNowTime = ::GetTickCount();
	}
}

CMotionBillBoard::CMotionBillBoard(void)
{
	pSprite = NULL;
	bShow = false;
	bNeedtoSave = false;
	iSpeedStep = 1;
	memset(FirstEventArray, 0 ,sizeof(FirstEventArray));
	dwHelpFlag = 0;
	pBirthdaySprite = NULL;
	_bShowBirTip = false;
}

BOOL CMotionBillBoard::MouseInFirstTip()
{
	if (PtInRect(&DstRct,theUiManager.m_ptMoust) && bShow)
	{
		return	TRUE;
	}else{
		return	FALSE;
	}
}

BOOL CMotionBillBoard::MouseInFirstTip2()
{
	RECT Rect;

	if (PtInRect(&Rect,theUiManager.m_ptMoust) && bShow)
	{
		return	TRUE;
	}else{
		return	FALSE;
	}
}

BOOL CMotionBillBoard::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	guardfunc;
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{
			bMouseDown = true;
			break;
		}
	case WM_LBUTTONUP:
		{
			bMouseDown = false;
			break;
		}
	default:
		break;
	}
	return FALSE;
	unguard;
}

CMotionBillBoard::~CMotionBillBoard(void)
{

}

std::string	CMotionBillBoard::GetXML_string(const char* path,const char* value,const char* theData)
{
	MeXmlDocument doc;
	std::string szValue;

	if( !path )
		assert(false && "GetXML_string 读取文件失误");

	char fullname[MAX_PATH] = {0};
	if( path[1] == ':' )
	{
		strcpy( fullname, path  );
	}
	else
	{
		char lwrpath[MAX_PATH] = {0};
		strcpy(lwrpath, path);
		strlwr(lwrpath);
		if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
			|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
			|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), path );
		else
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\%s", GetRootPath(), path );
	}

	if( !doc.LoadFile( fullname ) )
	{
		assert(false && "GetXML_string 读取文件失误");
	}
	MeXmlElement* lpRoot = doc.FirstChildElement(value);
	if(lpRoot)
	{
		szValue = lpRoot->Attribute(theData);
	}
	return szValue;
}

int CMotionBillBoard::GetXML_int(const char* path,const char* value,const char* theData)
{
	int Ingter = 0;
	MeXmlDocument doc;
	std::string szValue;
	if( !path )
		assert(false && "GetXML_string 读取文件失误");

	char fullname[MAX_PATH] = {0};
	if( path[1] == ':' )
	{
		strcpy( fullname, path  );
	}
	else
	{
		char lwrpath[MAX_PATH] = {0};
		strcpy(lwrpath, path);
		strlwr(lwrpath);
		if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
			|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
			|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1 ,"%s\\data\\%s", GetRootPath(), path );
		else
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\%s", GetRootPath(), path );
	}

	if( !doc.LoadFile( fullname ) )
	{
		assert(false && "GetXML_int 读取文件失误");
	}
	MeXmlElement* lpRoot = doc.FirstChildElement(value);
	if(lpRoot)
	{
		szValue = lpRoot->Attribute(theData,&Ingter);
	}
	return Ingter;
}

double CMotionBillBoard::GetXML_double(const char* path,const char* value,const char* theData)
{
	double dble = 0;
	MeXmlDocument doc;
	std::string szValue;
	if( !path )
		assert(false && "GetXML_string 读取文件失误");

	char fullname[MAX_PATH] = {0};
	if( path[1] == ':' )
	{
		strcpy( fullname, path  );
	}
	else
	{
		char lwrpath[MAX_PATH] = {0};
		strcpy(lwrpath, path);
		strlwr(lwrpath);
		if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
			|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
			|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1 ,"%s\\data\\%s", GetRootPath(), path );
		else
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\%s", GetRootPath(), path );
	}

	if( !doc.LoadFile( fullname ) )
	{
		assert(false && "GetXML_int 读取文件失误");
	}
	MeXmlElement* lpRoot = doc.FirstChildElement(value);
	if(lpRoot)
	{
		szValue = lpRoot->Attribute(theData,&dble);
	}
	return dble;
}

void CMotionBillBoard::SetTipCounts(FirstEvent eFtet)
{
	if ( FirstEventArray[eFtet] == 0)
	{
		if (eFtet == FRIST_FIGHT_OPERATE)
		{
			if (thePlayerRole.GetLevel()>1)
			{
				return;
			}
		}
		FirstEventArray[eFtet] = 1;
		eNowEvent = eFtet;
		ptSrc = ptSrcBkup;
		bShow = true;
		SaveResult();

		MsgModifyHelpFlagC2S msg;
		dwHelpFlag |= 1 << eFtet;
		msg.dwHelpFlag = dwHelpFlag;
		GettheNetworkInput().SendMsg( &msg );
	}
}

void CMotionBillBoard::ShowBirthdayTip()
{
	bShow = true;
	_bShowBirTip = true;

	FirstEventArray[BIRTHDAY] = 1;
	eNowEvent = BIRTHDAY;
	ptSrc = ptSrcBkup;
	SaveResult();
}

void CMotionBillBoard::SetSpritePlay(bool bshow)
{
	if (bshow)
	{
		this->bShow = true;
	}else{
		ptSrc = ptSrcBkup;
		ptSrc.y = -100;				//放到屏幕外，当作计时器
	}
}

std::string CMotionBillBoard::GetTipString(FirstEvent eFtet)
{
	return TipString[eFtet];
}

void CMotionBillBoard::BillBoardProcess()
{
	return;
	if (!bShow)
	{
		return;
	}
	if ( pBirthdaySprite && _bShowBirTip )
	{
		pBirthdaySprite->DrawSprite(ptSrc);
	}
	else if (pSprite)
	{
		pSprite->DrawSprite(ptSrc);
	}
	if (bNeedtoSave)
	{
		if (::GetTickCount() - dwNowTime > iflySpeed) 
		{
			dwNowTime = ::GetTickCount();
			if (ptSrc.x - ptDst.x > 0)
			{
				ptSrc.x-=iSpeedStep;
			}else{
				if (ptSrc.y < 0)
				{
					bShow = false;
					_bShowBirTip = false;
				}
				ptSrc = ptDst;
			}
		}
	}
	DstRct.top = ptSrc.y;
	DstRct.left = ptSrc.x;
	DstRct.right = DstRct.left + 64;
	DstRct.bottom = DstRct.top + 64;
}

void	CMotionBillBoard::getFirstInfoFromServer(unsigned long firsInf)
{
	guardfunc;
	return;

	dwHelpFlag = firsInf;

	memset(FirstEventArray, 0 ,sizeof(FirstEventArray));
	if( firsInf & COM_1 )
	{
		FirstEventArray[FRIST_FIGHT_OPERATE] = 1;
	}
	if( firsInf & COM_2 )
	{
		FirstEventArray[FRIST_FIGHT_SKILLLINK] = 1;
	}
	if( firsInf & COM_3 )
	{
		FirstEventArray[FRIST_FIGHT_BACKATTACK] = 1;
	}
	if( firsInf & COM_4 )
	{
		FirstEventArray[FRIST_DUTY] = 1;
	}
	if( firsInf & COM_5 )
	{
		FirstEventArray[FRIST_DUTY_HELP] = 1;
	}
	if( firsInf & COM_6 )
	{
		FirstEventArray[FRIST_COLLECT] = 1;
	}
	if( firsInf & COM_7 )
	{
		FirstEventArray[FRIST_COMPOUND] = 1;
	}
	if( firsInf & COM_8 )
	{
		FirstEventArray[FRIST_SKILL] = 1;
	}
	if( firsInf & COM_9 )
	{
		FirstEventArray[FRIST_ECONOMY_SYSTEM] = 1;
	}

	bool bRead = false;
	for (int i = 0; i < FRIST_COUNT; i++)
	{
		if ( FirstEventArray[i] == 0)
		{
			bRead = true;
			break;
		}
	}

	FirstEventArray[BIRTHDAY] = 1;

	bNeedtoSave = true;

	char stringpath[256] = "data\\ui\\BillboardHelp\\billboardstring.xml";
	for (int x= 0; x < FRIST_COUNT; x++)
	{
		TipString[x] = GetXML_string(stringpath,"TIPSTRING",ValueName[x]);
	}
	ptSrc.x = (long)multiplication(SCREEN_WIDTH,GetXML_double(stringpath,"FLYICON","SrcPosX"));
	ptDst.x = (long)multiplication(SCREEN_WIDTH,GetXML_double(stringpath,"FLYICON","DstPosX"));

	ptDst.y = (long)multiplication(SCREEN_HEIGHT,GetXML_double(stringpath,"FLYICON","PosY"));
	ptSrc.y = ptDst.y;
	ptSrcBkup = ptSrc;
	str		= GetXML_string(stringpath,"FLYICON","ImagePath");
	std::string strBir = GetXML_string(stringpath,"FLYICON","BirthdayImagePath");
	int FrameCount	= GetXML_int(stringpath,"FLYICON","FrameCounts");
	int PictureWidth	= GetXML_int(stringpath,"FLYICON","PictureWidth");
	int FrameSpeed	= GetXML_int(stringpath,"FLYICON","FrameSpeed");
	iflySpeed			= GetXML_int(stringpath,"FLYICON","FlySpeed");
	iSpeedStep		= GetXML_int(stringpath,"FLYICON","SpeedStep");
	std::string color = GetXML_string(stringpath,"FLYICON","StringColor");
	ptTipPos.x = (long)multiplication(SCREEN_WIDTH,GetXML_double(stringpath,"FLYICON","TipPosX"));
	ptTipPos.y = (long)multiplication(SCREEN_WIDTH,GetXML_double(stringpath,"FLYICON","TipPosY"));
	ptVPos.x	= GetXML_double(stringpath,"FLYICON","VTipPosX");
	ptVPos.y	= GetXML_double(stringpath,"FLYICON","VTipPosY");
	int a,r,g,b;
	sscanf(color.c_str(),"%d, %d, %d, %d", &a, &r, &g, &b);
	dwStringColor = Color_Config.ARGBtoDWORD(a, r, g, b);

	if ( bRead )
	{
		char fullname[MAX_PATH] = {0};
		char lwrpath[MAX_PATH] = {0};
		strcpy(lwrpath, str.c_str());
		strlwr(lwrpath);
		if( lwrpath[1] != ':' )
		{
			if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
				|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
				|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
				MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), lwrpath );
			else
				MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\%s", GetRootPath(), lwrpath );
			str = fullname;
		}
		pSprite = MeNew SpriteIcon(str.c_str(),PictureWidth,FrameCount,FrameSpeed);
	}
	char fullname[MAX_PATH] = {0};
	char lwrpath[MAX_PATH] = {0};
	strcpy(lwrpath, strBir.c_str());
	strlwr(lwrpath);
	if( lwrpath[1] != ':' )
	{
		if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
			|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
			|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), lwrpath );
		else
			MeSprintf_s( fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\%s", GetRootPath(), lwrpath );
	}
	pBirthdaySprite = MeNew SpriteIcon(fullname,PictureWidth,FrameCount,FrameSpeed);

	unguard;
}

void CMotionBillBoard::SaveResult()
{
	unsigned short result = 0;
	for(unsigned short i = 0; i < FRIST_COUNT; i++)
	{

		if( FirstEventArray[i] == 1 )
		{
			result |= ( 1 << i );
		}
	}
	MsgAckFirstTip	msgFirstTip;
	msgFirstTip.header.stID = theHeroGame.GetPlayerMgr()->m_PlayerID;
	msgFirstTip.usFirstInfo = result;//sbw_add		first tip
	GettheNetworkInput().SendMsg(&msgFirstTip);
	//GettheNetworkInput().CheckSendReq();
	//将result发送到server
}

