#pragma once
#include <string>
#include "Group_Me.h"

#include "..\PlayerRole.h"
#define GROUP_MAX_PLAYER	20

class CUI_Group
{
public:
	struct S_Player
	{
		S_Player()
		{
			nId = -1;
			nHp = nMaxHp = 0;
		}
		std::string strName;
		int		nId;
		int		nHp;
		int		nMp;
		int		nMaxHp;
		int		nMaxMp;
		int		nLvl;
		int		iMapID;
		int		x,y;
	};
	CUI_Group();
	void LoadUI();				// 载入UI
	void UnLoadUI();

	void	Refeash();
	void	RefeashGroup();
	void	RefeashGroupMemberHP( TeamInfo &InInfo );
	void	updataTeamerHP( int id, int hp);
	void	updateGroupSelect( int id );
	//显示队伍聊天 tip
	void	show_talktip(const char* talk, int id);
	void	ProcessHotKey(int nKey);

	void    UpdatePetInfo(GameObjectId PetID);

private:

	bool	AddPlayer( const int nId, const std::string& strName,
				const int nHp, const int nMaxHp, const int nMp, const int nMaxMp, const int nLvl);
	bool	UpdatePlayer( const int nId ,const int nHp, const int nMaxHp, const int nMp, const int nMaxMp, const int nLvl
				,const int iMapID,const int x,const int y );
	bool	IsTeammate( int iID );
	bool	RemovePlayer( const int nId );
	bool	RemoveAllPlayer();


	void	RenderMiniMap( void );

	void	InitGroupDlg(bool bVisable = false);
	//显示 分配选择的 
	void	show_assignMode_select(int headerid, unsigned char ucAssignMode);


	int	m_nCurSelPalyerId;
	S_Player	vecPlayer[GROUP_MAX_PLAYER];
	int	m_nPlayerCnt;
};
extern CUI_Group s_CUI_Group;