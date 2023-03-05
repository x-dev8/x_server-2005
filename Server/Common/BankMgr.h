/********************************************************************
	created:	2006/05/10
	created:	10:5:2006   14:28
	filename: 	e:\Hero\game_server\BankMgr.h
	file path:	e:\Hero\ServerGui
	file base:	BankMgr
	file ext:	h
	author:		Luo_157
	
	purpose:
				银行是玩家存储金钱,兑换钱币的场所
				储存钱币:
					默认给玩家一个钱柜
					每个玩家最多有10个钱柜
					每个钱柜需要花费1金元宝*(10-N),N=还剩的钱柜数量
					每个钱柜可以存放的铜板数量=1金元宝*N,N=已有钱柜数量
				兑换货币:游戏中货币分为铜板,金元宝两个币种
					1000铜板=1金元宝
					战斗只能获得铜板
					点卡可以兑换为金元宝
*********************************************************************/
#pragma once

#include "MeRTLibsServer.h"

class GamePlayer;

class CBankMgr
{
public:
	struct SBank
	{
		DWORD dwAccountID;		// 角色帐号
		DWORD dwCurMoney;		// 当前金额
		DWORD dwMaxMoney;		// 可保存的金额上限
	};

public:
	bool LoadData();
	bool SaveData();

public:
	// 获得玩家银行信息
	SBank*			GetBank( GamePlayer* pPlayer );
	// 存钱
	EBankTradeResult PushMoney( GamePlayer* pPlayer, DWORD dwMoney, SBank *pBank = NULL );
	// 取钱
	EBankTradeResult PopMoney( GamePlayer* pPlayer, DWORD dwMoney, SBank *pBank = NULL );
	// 升级银行所要的钱
	EBankTradeResult UpgradeNeedMoney( GamePlayer* pPlayer, DWORD& dwMoney );
	// 升级银行
	EBankTradeResult UpgradeBank( GamePlayer* pPlayer, SBank *pBank = NULL );

private:
	// 新建一钱柜
	SBank*	AddBank( SBank& bank );
	// 获得钱柜
	SBank*	GetBank( DWORD dwAccountID );

private:
	struct SSaveDataChunk
	{
		DWORD dwVersion;
		DWORD dwCount;
		SBank stBanks[1];
	};

private:
	// <角色帐号,SBank>
	std::map<DWORD,SBank> m_mapBank;

public:
	CBankMgr(void);
	~CBankMgr(void);
};

CBankMgr* GetBankMgr();
