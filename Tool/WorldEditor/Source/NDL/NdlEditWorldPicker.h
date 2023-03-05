/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlWorldPicker.h
* Date: 	03/01/2007
* Desc:
*
*******************************************************************************/
#ifndef _NDL_NDLWORLDPICKER_H__
#define _NDL_NDLWORLDPICKER_H__

////////////////////////////////////////////////////////////////////////////////
class CWorld;
class CResEditMgr;
class CWorldChunk;
class CWorldBuffer;
class TObjectEditInfo;
////////////////////////////////////////////////////////////////////////////////
#include "MeTerrain/NdlWorldPickerBase.h"


////////////////////////////////////////////////////////////////////////////////
class CNdlEditWorldPicker : public CNdlWorldPickerBase
{
public:
	CNdlEditWorldPicker( CWorld* world );
	~CNdlEditWorldPicker();
	virtual bool IsNeedCheck( CWorldChunk* worldChunk )
	{
		return 									true;
	}
					
	virtual void CollideObjForEditer( sInt32 pickType, bool bPickResult, Vector& rayPt, Vector& rayDir, TPickResult& pickResult );
	virtual void CollideSupperFloor( TObjectInfo* obj, Vector& rayPt, Vector& rayDir, TPickResult &castResult, int id, bool& bPick );
	bool			CollideTransport(CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult);
	bool			CollideFlyRoute(CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult);
	bool			CollideNPCRoute(CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult);
	bool			CollideMonsterQuad(CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult);
	bool			CollideClick2Add(CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult);
	bool            CoolideNpc(CResMgr* resMgr,const Vector& rayPt,const Vector& rayDir,TPickResult& castResult);
	
protected:
	bool			CheckTile( sInt32* tileId );
	bool			CheckChunk( sInt32* chunkId );
	bool			CheckUnit( sInt32* unitId );
};
	
#endif	// _NDL_NDLWORLDPICKER_H__
