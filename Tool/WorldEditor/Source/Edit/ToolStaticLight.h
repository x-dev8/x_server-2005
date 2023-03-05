/*******************************************************************************
* Copyright ShenWang 2011 - All Rights Reserved
* 
* File: 	ToolStaticLight.h
* Create: 	02/22/2011
* Desc:		静态光源场景控制
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef TOOL_STATIC_LIGHT_H
#define TOOL_STATIC_LIGHT_H
#include "BaseTool.h"
#include "ui/ToolsWnd/ToolStaticLightDlg.h"

////////////////////////////////////////////////////////////////////////////////
class CToolStaticLight	: public CBaseTool
{
	friend class CToolStaticLightDlg;
public:
	enum optMode {
		optMode_PutLight = 0,
		optMode_Pick
	};

	CToolStaticLight();
	virtual					~CToolStaticLight();

	virtual ToolID			GetToolId()	{ return TOOL_STATICLIGHT; };
	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();

	bool					Create( CToolManager* toolMgr );

	void					Bind( CToolStaticLightDlg* bindDlg );
	void					Reset();

	void					SetOptMode(optMode);

	bool					PushLightModel(float fDist, const Vector& pos, const NiColorB& color);
	void					ClearAllLightModel();
	bool					RemoveLightModel(int index);
	void					DoSelect(int select);
	void					UnSelect(int select);
	void					UnSelectAll() { m_vSelected.clear(); }

	bool					UpdatePosX(int index, float v);
	bool					UpdatePosY(int index, float v);
	bool					UpdatePosZ(int index, float v);
	bool					UpdateDistance(int index, float v);
	bool					UpdateColor(int index, const NiColorB& color);

protected:
	bool					LoadLightModel();

	TObjectEditInfo			m_lightNode;
	CToolStaticLightDlg*	m_bindDlg;

	optMode					m_eOptMode;
	std::vector<TObjectEditInfo*> m_vecLightModels;	// 列表对应光源辅助模型
	std::vector<int>		m_vSelected;
};
#endif /*TOOL_STATIC_LIGHT_H*/