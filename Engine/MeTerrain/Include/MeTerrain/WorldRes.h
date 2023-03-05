/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldRes.h
* Create: 	10/06/2006
* Desc:		数据资源基类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_WORLDRES_H__
#define _MAP_WORLDRES_H__


class CResMgr;
////////////////////////////////////////////////////////////////////////////////
class CWorldRes;
// NiSmartPointer(CWorldRes);
class CBaseRes : public MeCommonAllocObj<CBaseRes>
{
public:
	CBaseRes(){	m_id		= RES_INVALID_ID;}
	virtual			~CBaseRes(){;}				
	sInt32&			GetId() ;
	void			SetId( sInt32 id );
protected:
	sInt32			m_id;

};
class CWorldRes : public CBaseRes
{
public:
					CWorldRes();
	virtual			~CWorldRes();				

	bool			IsLoad() const { return m_isLoad; } ;
	void			SetLoad(bool val) { m_isLoad = val; }

	
	const char*		GetName() const;
	void			SetName( const char* name );
	sInt32&			RefCount() { return m_refCount; }
	void			SetRefCount(sInt32 val) { m_refCount = val; }
	// For use with NiSmartPointers
	virtual	void			IncRefCount();
	virtual	void			DecRefCount();
protected:
	bool			m_isLoad;
	sInt32			m_refCount;
	char			m_name[RES_NAME_LEN];


};


#endif	// _MAP_WORLDRES_H__

