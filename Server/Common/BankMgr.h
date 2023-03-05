/********************************************************************
	created:	2006/05/10
	created:	10:5:2006   14:28
	filename: 	e:\Hero\game_server\BankMgr.h
	file path:	e:\Hero\ServerGui
	file base:	BankMgr
	file ext:	h
	author:		Luo_157
	
	purpose:
				��������Ҵ洢��Ǯ,�һ�Ǯ�ҵĳ���
				����Ǯ��:
					Ĭ�ϸ����һ��Ǯ��
					ÿ����������10��Ǯ��
					ÿ��Ǯ����Ҫ����1��Ԫ��*(10-N),N=��ʣ��Ǯ������
					ÿ��Ǯ����Դ�ŵ�ͭ������=1��Ԫ��*N,N=����Ǯ������
				�һ�����:��Ϸ�л��ҷ�Ϊͭ��,��Ԫ����������
					1000ͭ��=1��Ԫ��
					ս��ֻ�ܻ��ͭ��
					�㿨���Զһ�Ϊ��Ԫ��
*********************************************************************/
#pragma once

#include "MeRTLibsServer.h"

class GamePlayer;

class CBankMgr
{
public:
	struct SBank
	{
		DWORD dwAccountID;		// ��ɫ�ʺ�
		DWORD dwCurMoney;		// ��ǰ���
		DWORD dwMaxMoney;		// �ɱ���Ľ������
	};

public:
	bool LoadData();
	bool SaveData();

public:
	// ������������Ϣ
	SBank*			GetBank( GamePlayer* pPlayer );
	// ��Ǯ
	EBankTradeResult PushMoney( GamePlayer* pPlayer, DWORD dwMoney, SBank *pBank = NULL );
	// ȡǮ
	EBankTradeResult PopMoney( GamePlayer* pPlayer, DWORD dwMoney, SBank *pBank = NULL );
	// ����������Ҫ��Ǯ
	EBankTradeResult UpgradeNeedMoney( GamePlayer* pPlayer, DWORD& dwMoney );
	// ��������
	EBankTradeResult UpgradeBank( GamePlayer* pPlayer, SBank *pBank = NULL );

private:
	// �½�һǮ��
	SBank*	AddBank( SBank& bank );
	// ���Ǯ��
	SBank*	GetBank( DWORD dwAccountID );

private:
	struct SSaveDataChunk
	{
		DWORD dwVersion;
		DWORD dwCount;
		SBank stBanks[1];
	};

private:
	// <��ɫ�ʺ�,SBank>
	std::map<DWORD,SBank> m_mapBank;

public:
	CBankMgr(void);
	~CBankMgr(void);
};

CBankMgr* GetBankMgr();
