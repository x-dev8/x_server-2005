#include <assert.h>
#include "itemcompound.h"
#include "slkReader.h"
#include "Helper.h"
#include "FuncPerformanceLog.h"
CItemCompound g_itemCompound;
CItemCompound::CItemCompound(void)
{

	guardfunc;
	unguard;
}

CItemCompound::~CItemCompound(void)
{
	guardfunc;
	unguard;
}

#define GetIntFromField( t, msg ) \
		if( !r.GetIntFieldByName( msg, iValue ) ) \
{ \
	HelperFunc::Output( "Error:��ȡskill.slk�ֶ�["msg"]����\r\n" ); \
	assert( false && "Error:��ȡskill.slk�ֶ�["msg"]����" ); \
	continue; \
} \
	t = iValue; 

BOOL CItemCompound::LoadFromSlk( const char* pszFilename )
{
	guardfunc;
	CSlkReader r;
	if( !r.ReadFromFile( (char*)pszFilename ) )
		return FALSE;
	int nLine = 3;
	int iRet;
	int iValue;
	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
	{
		Record record;
		GetIntFromField( record.stId,			"CompoundId" );
		GetIntFromField( record.nSuccRate,		"SuccessRate" );
		GetIntFromField( record.dwCostMoney,	"MoneySpent" );
		
		GetIntFromField( record.res[0].stId,	"material1ID" );
		GetIntFromField( record.res[0].nCount,	"material1Num" );
		GetIntFromField( record.res[1].stId,	"material2ID" );
		GetIntFromField( record.res[1].nCount,	"material2Num" );
		GetIntFromField( record.res[2].stId,	"material3ID" );
		GetIntFromField( record.res[2].nCount,	"material3Num" );
		GetIntFromField( record.res[0].stId,	"material4ID" );
		GetIntFromField( record.res[0].nCount,	"material4Num" );
		/*GetIntFromField( record.res[1].stId,	"ԭ��5ID" );
		GetIntFromField( record.res[1].nCount,	"ԭ��5����" );
		GetIntFromField( record.res[2].stId,	"ԭ��6ID" );
		GetIntFromField( record.res[2].nCount,	"ԭ��6����" );
		GetIntFromField( record.res[0].stId,	"ԭ��7ID" );
		GetIntFromField( record.res[0].nCount,	"ԭ��7����" );
		GetIntFromField( record.res[1].stId,	"ԭ��8ID" );
		GetIntFromField( record.res[1].nCount,	"ԭ��8����" );*/

		
		m_vectorRecord.push_back( record );
	}
	return TRUE;
	unguard;
}
CItemCompound::Record* CItemCompound::GetRecordById( short stId )
{
	guardfunc;
	for( int i = 0; i < m_vectorRecord.size(); i++ )
	{
		if( stId == m_vectorRecord[i].stId )
			return &m_vectorRecord[i];
	}
	return NULL;
	unguard;
}

short CItemCompound::MakeFromRes( std::vector<Resource>* pvectorRes )
{
	guardfunc;
	Record* pRecord = GetRecordById( 3201 );
	if( !pRecord )
	{
		assert( false );
		return -1;
	}
	bool bResOk[eMaxCompoundRes];
	memset( bResOk, 0x00, sizeof( bResOk ) );
	int nResOkCount = 0;
	for( int i = 0; i < eMaxCompoundRes; i++ )
	{
		if( pRecord->res[i].stId == -1 )
		{
			bResOk[nResOkCount++] = true;
			continue;
		}

		for( int j = 0; j < pvectorRes->size(); j++ )
		{
			Resource* res = &(*pvectorRes)[j];
			if( pRecord->res[i].stId == res->stId &&
				pRecord->res[i].nCount == res->nCount )
			{
				bResOk[nResOkCount++] = true;
				continue;
			}
		}
	}
	if( nResOkCount == eMaxCompoundRes )
		return pRecord->stId;
	return -1;
	unguard;
}