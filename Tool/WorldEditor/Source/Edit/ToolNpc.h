#pragma once

#include "BaseTool.h"
#include "rollback\RecoveryManager.h"

class CWorldChunk;
#include "ui/ToolsWnd/DlgNpcEditor.h"
class CToolNpc :public CBaseTool
{
	friend class CDlgNpcEditor;
public:
	enum optMode {
		optMode_NPC = 0,
		optMode_Pick

	};
	//Npc寻路点
	struct NpcPointer
	{
		enum optPointer
		{
			optMode_None  = -1,
			optMode_AddPointer = 0,
		};

		optPointer              m_PointerMode;
		NpcPointer()
		{
			m_PointerMode = optMode_None;
		}

		void SetMode(optPointer eMode){m_PointerMode = eMode;}
		
	};

	CToolNpc(void);
	~CToolNpc(void);

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );

	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );


	virtual ToolID			GetToolId()	{ return TOOL_NPC; };
	virtual bool			Create( CToolManager* toolMgr );
	virtual	void			SetActive( bool isActive = true );
	virtual void			Render();

    void                    Bind( CDlgNpcEditor* dlg );
	void                    Reset();

	void                    SetOptMode( optMode eMode );
	CResEditMgr*					GetResMgr();

	void                    AttachAllModel();
	void                    DetalAllModel();

	void                    DeleteModel();

	void                    SetCameraByNpcId(sInt32 npcId);

	bool                    UpdateNpcPointer(int nType,float x,float y,bool bShow);
	void                    DelNpcPointer();

	void                    ShowLine(bool bShow){m_bShowLine = bShow;}

	void SetSelectedNpc(bool bRefreshUI = true);
	void ClearSelectedNpc();

//operations
public:
	virtual void Redo(void);
	virtual void Undo(void);
	virtual bool CanRedo(void);
	virtual bool CanUndo(void);

	//更改模型的外界入口
	bool DoChangeNpcModel(int modelId_);
	//更改模型的原子模型，供CRecoveryManager使用
	//bool ChangeNpcModel(CNpcRes *_pRes_, int modelId_);
	bool ChangeNpcModel(int npcId_, int modelId_);

	//更改模型的position、orientation & scale
	bool DoChangeNpcPos(float x_, float y_, float z_, int dir_, float scale_);
	//bool ChangeNpcPos(CNpcRes *_res_, float x_, float y_, float z_, int dir_, float scale_);
	bool ChangeNpcPos(int npcId_, float x_, float y_, float z_, int dir_, float scale_);

	bool DoDeleteNpc();
	bool DeleteNpc(/*int resId_, */int npcId_);

	bool DoAddNpc(float x_, float y_, float z_);
	bool AddNpc(NpcInfo::Npc *pNpc_, PositionInfo::Position *pPos_);

	bool DoAddNpcPostion(float x, float y);
	bool AddNpcPostion(int npcId_, const PositionInfo::Position &pos_);

	bool DoDeleteNpcPosition();
	bool DeleteNpcPosition(int npcId_);

	bool DoChangeNpcPosition(int nType,flt32 x,flt32 y,bool bShow);
	bool ChangeNpcPosition(int npcId_, const PositionInfo::Position &pos_);

// 	bool DoModifyNpcs(int npcId_, const NpcInfo::Npc &npc_);
// 	bool ModifyNpcs();


public:
	NpcPointer             m_npcPointer;
private:
	optMode						m_eoptMode;

	CDlgNpcEditor *m_transportDlg;

	CNpcRes                *m_CurrNpc;
	bool                   m_bShowLine;

	CRecoveryManager m_opManager;

};
