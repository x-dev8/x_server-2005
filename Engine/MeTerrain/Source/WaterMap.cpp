/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WaterMap.cpp
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "Me3d/Global.h"
#include "WaterMap.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CWaterMap::CWaterMap( const char* pszFileName )
:m_pkMapData(0)
{
	DWORD dwWidthByteCount = 0;
	BOOL bReadMapSuccess = FALSE;

	FILE* stream = fopen( pszFileName, "rb");
	TileDataMapHeader mapHeader;
	if( stream != 0)
	{
		fread(&mapHeader,sizeof( TileDataMapHeader ),1,stream);

		dwWidthByteCount = mapHeader.width;
		m_nWidth = mapHeader.width;
		m_nHeight = mapHeader.height;
		int nRateM = mapHeader.rate_M;
		int nRateR = mapHeader.rate_R;
		m_fRate = (float)nRateR / (float)nRateM;
		DWORD  dwWidthByteCount = ( mapHeader.width + 7) >> 3;
		m_pkMapData = new unsigned char[ dwWidthByteCount * mapHeader.height];
		fread(m_pkMapData,sizeof(unsigned char)*dwWidthByteCount * mapHeader.height,1,stream);

		fclose( stream);
	}

}
CWaterMap::~CWaterMap()
{
	Reset();
}


void CWaterMap::Reset()
{

	if(m_pkMapData )
	{
		delete m_pkMapData;
		m_pkMapData = NULL;
	}
}

bool CWaterMap::IsInWater( float x,float y )
{
	if (!m_pkMapData)
	{
		return false;
	}
	int posx = GameCoordToMap(x);
	int posy = GameCoordToMap(y);
	DWORD  dwWidthByteCount = ( m_nWidth + 7) >> 3;
	return (m_pkMapData[posy* dwWidthByteCount + (posx >> 3)] & (1 << (7 - posx%8))) != 0;
}

