/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ReachableMapGenerate.h
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __REACHABLE_MAP_GENERATE_H__
#define __REACHABLE_MAP_GENERATE_H__

class CxImage;
class CToolWorld;
struct THeightResult;
////////////////////////////////////////////////////////////////////////////////
class CReachableMapGenerate : public Singleton<CReachableMapGenerate>
{
public:	
					CReachableMapGenerate();
					~CReachableMapGenerate();

	void			Reset();
		
	
	bool			GenerateFile(sInt32 tileId,sInt32 mapScale,const char* fileName);
	bool			GenerateWaterMap(sInt32 tileId,sInt32 mapScale,const char* fileName);
	bool			GenerateHeightMap(sInt32 tileId,sInt32 mapScale,const char* fileName);
	char			IsRealPosReachable(flt32 posX, flt32 posY,flt32 angle, THeightResult* pheightResult = NULL,bool* bSlopeCheck = NULL);
	char			IsRealPosWater(flt32 posX, flt32 posY);
	
	bool			VerifyReachableMap(sInt32 width,sInt32 height,unsigned char* pData,CWorldTile* tile);
	void			MarkBorder(sInt32 width,sInt32 height,unsigned char* pData);
	bool			ReadInReachableData( CWorldTile* pTile );
	bool			IsRealPosReachableInData( flt32 posX,flt32 posY, sInt32 width, flt32 interval,const unsigned char* pData );

protected:
	float			GetZbyXY(flt32 posX, flt32 posY);
	bool			IsPickObj( flt32 posX, flt32 posY, THeightResult* pheightResult, TPickResult &pickResult );
	bool			IsReachable( sInt32 posX,sInt32 posY, sInt32 width,const unsigned char* pData );
	
public:
	flt32			m_interval;

public:
	void			SlopeCheck();
	bool			IsErrorSlope(CWorldChunk* chunk);
	void			ClearSlopeCheck();
protected:
	std::vector<CWorldChunk*>			m_SlopeCheckChunkArr;
};

extern		sInt32 g_reachableMapScale;			






#endif //__REACHABLE_MAP_GENERATE_H__