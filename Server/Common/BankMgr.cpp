#include "GamePlayer.h"
#include "BankMgr.h"
#include <assert.h>
#include "DataChunkMgr.h"

#define DCSID_BANKMGR		0x58ab403e, 0x5d2f7f10
#define DCID_BANK			0x335a2e73, 0x2cda4201

#define BANK_DATACHUNK_VER	2006051016

#define BANK_MAXMONEY_PRE	(100*1000)
#define BANK_MAX_LEVEL		10
#define UPGRAED_MONEY_PRE	1000

CBankMgr* GetBankMgr()
{
	static CBankMgr s;
	return &s;
}

CBankMgr::CBankMgr(void)
{
	LoadData();
}

CBankMgr::~CBankMgr(void)
{
}

bool CBankMgr::LoadData()
{
	CDataChunkMgr *pDataMgr = NULL;
	CAppDataChunk* pDataChunk =  NULL;
	pDataMgr = GetDataChunkMgr();
	pDataChunk = pDataMgr->GetAppDataChunk( CAppDataChunkClassID(DCID_BANK), 
											CAppDataChunkClassID(DCSID_BANKMGR),
											0 );
	if ( !pDataChunk )
		return false;
	SSaveDataChunk *pData = NULL;
	pData = (SSaveDataChunk*)pDataChunk->m_pbyData;
	if ( pData->dwVersion == BANK_DATACHUNK_VER )
	{
		// ToLog( pData->dwCount > 0 );
		for ( DWORD n=0; n < pData->dwCount; n++ )
		{
			SBank *pBank = AddBank( pData->stBanks[n] );
			// ToLog( pBank );
		}
	}
	else
	{
		MessageBox( NULL,"Bank data structure version not matching.","Warning", MB_OK | MB_ICONWARNING );
	}
	return true;
}

bool CBankMgr::SaveData()
{
	if ( m_mapBank.size() <= 0 )
		return false;
	int nBufSize = sizeof(SSaveDataChunk) +
					sizeof(SBank)*m_mapBank.size();
    BYTE *pBufs = CNewWithDebug<BYTE>::Alloc(nBufSize, "CBankMgr::SaveData中创建pBufs");
	SSaveDataChunk* pData = NULL;
	pData = (SSaveDataChunk*)pBufs;
	pData->dwVersion = BANK_DATACHUNK_VER;
	pData->dwCount = m_mapBank.size();
	std::map<DWORD,SBank>::iterator it;
	int nIndex = 0;
	for ( it=m_mapBank.begin(); it!=m_mapBank.end(); it++ )
	{
#pragma message ("此处注意会越界")
		pData->stBanks[nIndex++] = it->second;
	}
	CDataChunkMgr *pDataMgr = NULL;
	pDataMgr = GetDataChunkMgr();
	pDataMgr->RemoveAppDataChunk( CAppDataChunkClassID(DCID_BANK), 
									CAppDataChunkClassID(DCSID_BANKMGR), 
									0 );
	pDataMgr->AddAppDataChunk( CAppDataChunkClassID(DCID_BANK), 
								CAppDataChunkClassID(DCSID_BANKMGR), 
								0,
								nBufSize,
								pBufs );
    CNewWithDebug<BYTE>::Free(pBufs);
	return true;
}

CBankMgr::SBank* CBankMgr::AddBank( SBank& bank )
{
	SBank *pBank = NULL;
	pBank = GetBank( bank.dwAccountID );
	// ToLog( !pBank );
	if ( pBank )
	{
		*pBank = bank;
	}
	else
	{
		m_mapBank[bank.dwAccountID] = bank;
		pBank = &m_mapBank[bank.dwAccountID];
	}
	return pBank;
}

CBankMgr::SBank* CBankMgr::GetBank( DWORD dwAccountID )
{
	std::map<DWORD,SBank>::iterator it;
	it = m_mapBank.find( dwAccountID );
	if ( it == m_mapBank.end() )
		return NULL;
	return &it->second;
}

CBankMgr::SBank* CBankMgr::GetBank( GamePlayer* pPlayer )
{
	// ToLog( pPlayer );
	if ( !pPlayer )
		return NULL;
	SBank *pBank = NULL;
	DWORD dwAccountID = pPlayer->GetDBCharacterID();
	// ToLog( dwAccountID != 0 );
	pBank = GetBank( dwAccountID );
	if ( !pBank )
	{
		SBank stBank;
		stBank.dwAccountID = dwAccountID;
		stBank.dwCurMoney = 0;
		stBank.dwMaxMoney = BANK_MAXMONEY_PRE;
		pBank = AddBank( stBank );
	}
	// ToLog( pBank );
	return pBank;
}

EBankTradeResult CBankMgr::PushMoney( GamePlayer* pPlayer, DWORD dwMoney,
									  SBank *pBank )
{
	// ToLog( pPlayer );
	if ( !pPlayer )
		return eBankTradeResultFalied;
	if ( dwMoney == 0 )
		return eBankTradeResultFalied;
	if ( dwMoney > pPlayer->GetMoney() )
		return eBankTradeResultPlayerNotMoney;
	SBank *pPlayerBank = NULL;
	pPlayerBank = GetBank( pPlayer );
	// ToLog( pPlayerBank );
	if ( !pPlayerBank )
		return eBankTradeResultFalied;
	if ( dwMoney + pPlayerBank->dwCurMoney > pPlayerBank->dwMaxMoney )
		return eBankTradeResultBankFull;
	pPlayer->SetMoney( pPlayer->GetMoney() - dwMoney );
	pPlayerBank->dwCurMoney += dwMoney;
	if ( pBank )
	{
		*pBank = *pPlayerBank;
	}
	return eBankTradeResultSuccess;
}

EBankTradeResult CBankMgr::PopMoney( GamePlayer* pPlayer, DWORD dwMoney,
									 SBank *pBank )
{
	// ToLog( pPlayer );
	if ( !pPlayer )
		return eBankTradeResultFalied;
	if ( dwMoney == 0 )
		return eBankTradeResultFalied;
	SBank *pPlayerBank = NULL;
	pPlayerBank = GetBank( pPlayer );
	// ToLog( pPlayerBank );
	if ( !pPlayerBank )
		return eBankTradeResultFalied;
	if ( dwMoney > pPlayerBank->dwCurMoney )
		return eBankTradeResultBankNotMoney;
	pPlayerBank->dwCurMoney -= dwMoney;
	pPlayer->SetMoney( pPlayer->GetMoney() + dwMoney );
	if ( pBank )
	{
		*pBank = *pPlayerBank;
	}
	return eBankTradeResultSuccess;
}

EBankTradeResult CBankMgr::UpgradeNeedMoney( GamePlayer* pPlayer, DWORD& dwMoney )
{
	// ToLog( pPlayer );
	if ( !pPlayer )
		return eBankTradeResultFalied;
	SBank *pPlayerBank = NULL;
	pPlayerBank = GetBank( pPlayer );
	// ToLog( pPlayerBank );
	if ( !pPlayerBank )
		return eBankTradeResultFalied;
	int nLevel = pPlayerBank->dwMaxMoney/BANK_MAXMONEY_PRE;
	// ToLog( nLevel > 0 );
	if ( nLevel >= BANK_MAX_LEVEL )
		return eBankTradeResultUpgradeMax;
	dwMoney = nLevel*UPGRAED_MONEY_PRE;
	return eBankTradeResultSuccess;
}

EBankTradeResult CBankMgr::UpgradeBank( GamePlayer* pPlayer, SBank *pBank )
{
	EBankTradeResult eResult;
	DWORD dwMoney = 0;
	eResult = UpgradeNeedMoney( pPlayer, dwMoney );
	if ( eResult != eBankTradeResultSuccess )
		return eResult;
	SBank *pPlayerBank = NULL;
	pPlayerBank = GetBank( pPlayer );
	// ToLog( pPlayerBank );
	if ( !pPlayerBank )
		return eBankTradeResultFalied;
	if ( dwMoney > pPlayer->GetMoney() )
		return eBankTradeResultPlayerNotMoney;
	pPlayer->SetMoney( pPlayer->GetMoney() - dwMoney );
	pPlayerBank->dwMaxMoney += BANK_MAXMONEY_PRE;
	if ( pBank )
	{
		*pBank = *pPlayerBank;
	}
	return eBankTradeResultSuccess;
}

