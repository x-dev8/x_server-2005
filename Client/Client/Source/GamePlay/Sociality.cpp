#include "Sociality.h"
#include "MeFont/MeFont.h"
#include "PlayerRole.h"
#include "SlkReader.h"
//  
//#include "ui/TitleB.h"
#include "ItemDetail.h"

HeroSocial	__HeroSocial;

HeroSocial* GetSocial()
{
	return &__HeroSocial;
}

HeroSocial::HeroSocial()
{
	dwFlag = 0;
	eCurrseDisplay = eSTP_Brother;
	ZeroMemory(PlayerClan,sizeof(BeNamed)*SOCIALITY_COUNTS);
}

void	HeroSocial::InitClanBuffer()
{
	ZeroMemory(PlayerClan,sizeof(BeNamed)*SOCIALITY_COUNTS);
}

void HeroSocial::AddBrotherName(const char* name)
{
	if (strcmp(name,"") == 0)
	{
		return;
	}
	::CopyMemory(PlayerClan[eSTP_Brother].ClanName,name,GuildDefine::MaxNameLength );
}

void HeroSocial::AddClanName(DWORD sotyp,const char* clanname)
{
	guardfunc;
	for (int i = 0; i < SOCIALITY_COUNTS; i++)
	{
		if ( sotyp & BinaryFlag(i) )
		{
			CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
			if (pPlayer
				&&
				strcmp(pPlayer->GetName(),clanname)
				)
			{
				PlayerClan[i].type = (eSocialityType)i;
				strcpy(PlayerClan[i].ClanName,clanname);		
			}
		}
	}
	unguard;
}

const char* HeroSocial::GetClanNames(eSocialityType sotye)
{
	guardfunc;
	return PlayerClan[sotye].ClanName;
	unguard;
}

std::string HeroSocial::GetClanNamedOf()
{
	guardfunc;
	std::string szShowNameOf;
	return szShowNameOf;
	unguard;
}


void	HeroSocial::DrawClanTitle(int x,int y,eSocialityType textype,DWORD dwColor,BOOL bShow)
{
	guardfunc;
	unguard;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////



const char* HeroSocial::SetRepute(const char* szName,DWORD type,short playerid,SRankManager rkmgr, bool isMan)
{
	return "";
}

const char* HeroSocial::SetReputeRank(const char* szName,DWORD type,short playerid)
{	
	return	NULL;
}


void HeroSocial::CallForRepute2Server(char* name)
{

}


void HeroSocial::GetRankName(WORD x,WORD y,std::string& rankname, bool bDescription )
{
	CSlkReader reader;
	if (!reader.ReadFromFile("..\\Data\\Config\\ranklist.slk"))
	{
		assert(false && "HeroSocial::GetRankName	读取文件出错");
		return;
	}
	int iRet = x+1;
	int iRow = y+1;
	if (iRet> 31 || iRow > 15)
	{
		return;
	}
	rankname.clear();
	std::string szAll;
	reader.GotoNextLine(iRow);
	reader.GetStringField(iRet,szAll);

	int nOff = szAll.find("*");
	if( nOff != -1 )
	{
		if( bDescription )
		{
			rankname = szAll.substr( nOff, szAll.length() - nOff );
		}
		else
		{
			rankname = szAll.substr( 0, nOff );
		}
	}
	else
	{
		rankname = szAll;
	}
}

const char* HeroSocial::DelRepute(DWORD type,short playerid,bool isman,DWORD delrepIndex)
{
	BinaryList	bl;
	::CopyMemory(&bl,&type,sizeof(DWORD));
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(playerid);
	if (bl.a < 32)
	{
		if (pPlayer)
		{
			if (playerid == theHeroGame.GetPlayerMgr()->GetMyID())
			{	
				//寻找一下新加入的棋标是否已经添加过了
				for (int x = 0; x < pPlayer->PlayerOwnList.size(); x++)
				{
					if (pPlayer->PlayerOwnList[x].usReputeID == delrepIndex)
					{
						pPlayer->PlayerOwnList.erase(pPlayer->PlayerOwnList.begin()+x);
						reputename.clear();
						if (s_CUI_ID_FRAME_BaseProperty.IsVisable())
						{
							s_CUI_ID_FRAME_BaseProperty.Refresh();
						}						
						return reputename.c_str();							
					}
				}				
			}
		}		
	}
	return reputename.c_str();
}