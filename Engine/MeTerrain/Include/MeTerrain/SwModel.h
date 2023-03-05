/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwModel.h
* Create: 	10/16/2006
* Desc:		从NIF或KFM加载模型的类，不支持渲染
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWMODEL_H__
#define __SWMODEL_H__
#include <vector>


//class NiCamera;
//class NiVisibleArray;

class SwModel	: public NiRefObject
{
public:
	SwModel();
	virtual						~SwModel();

	virtual bool				Create( const char* pFileName );
	virtual void				Destroy();

	virtual void				Update( float pTime, float pDeltaTime );
	virtual void				Render( NiCamera* pCamera );

	virtual NiNode*				GetRootNode(){ return m_rootNode; };
	virtual NiActorManager*		GetActorMgr(){ return m_actorMgr; };

	virtual NiCamera*			GetCamera( int idx = 0 );
	virtual int					GetCameraCount() { return (int)m_cameraList.size(); };

	virtual void				SetScale( float scale );

protected:
	bool						LoadByFileName( const char* pName );
	bool						LoadNif( const char* pName );
	bool						LoadKfm( const char* pName );

protected:
	NiActorManagerPtr			m_actorMgr;
	NiSwitchNodePtr				m_rootNode;

	std::vector< NiCamera* >	m_cameraList;
};
#endif //__SWMODEL_H__