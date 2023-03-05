/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	ToolMonsterQuad.h
* Create: 	11/04/08
* Desc:
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __TOOL_MONSTER_QUAD_H__
#define __TOOL_MONSTER_QUAD_H__

#include "BaseTool.h"

#include "rollback\RecoveryManager.h"
#include <vector>

class CWorldChunk;
class CToolMonsterQuad	: public CBaseTool
{
protected:
    class IVisitor
    {
    public:
        IVisitor(): m_pObject(NULL) {};
        virtual ~IVisitor() {};
        void SetToolObject(CToolMonsterQuad *pObject_)
        {
            m_pObject = pObject_;
        }

    protected:
        CToolMonsterQuad *m_pObject;
    };

    class CPickingVisitor: public IVisitor
    {
        friend class CToolMonsterQuad;

    public:
        CPickingVisitor();
        ~CPickingVisitor();

        /*----------------------------------------------
        desc	: 拾取地图上选择的models。
        ----------------------------------------------*/
        bool PickModels(CMonsterQuadRes *pModels_, UINT size_);
        bool PasteModels(CPoint point_);

        void Render();

        void Reset();

        void SetPaste();
        bool IsToPaste();

        bool OnMouseMove( UINT nFlags, CPoint point );
        bool OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags);

        void UpdateModels(CPoint point_);

        bool Empty(void)
        {
            return m_pickedModels.empty();
        }

    protected:
        typedef std::vector<CMonsterQuadRes *> TPickModels;
    protected:
        TPickModels m_pickedModels;		//鼠标拿着的models，这些models会跟随鼠标的移动
        bool m_bToPaste;	//标志是否粘帖，每当粘帖完就要重置该标志，选择粘帖命令后再置位;
    };

    friend class			CToolMonsterQuadDlg;
public:
    enum optMode
    {
        optMode_Pick = 0,
        optMode_AddMonsterQuad

    };
    CToolMonsterQuad();
    virtual					~CToolMonsterQuad();

    virtual ToolID			GetToolId()
    {
        return TOOL_MONSTERQUAD;
    };
    virtual bool Create( CToolManager *toolMgr );
    virtual	void SetActive( bool isActive = true );
    void Bind( CToolMonsterQuadDlg *dlg );
    void Reset();

    virtual bool OnLMouseDown( UINT nFlags, CPoint point );

    virtual bool OnLMouseUp( UINT nFlags, CPoint point );
    virtual bool OnLMouseDblClk( UINT nFlags, CPoint point );
    virtual bool OnRMouseDown( UINT nFlags, CPoint point );
    virtual bool OnRMouseUp( UINT nFlags, CPoint point );
    virtual bool OnMouseMove( UINT nFlags, CPoint point );
    virtual bool OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
    virtual bool OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void Render();


    void SetOptMode(optMode eMode);
    void ShowPmpModel(  );
    void ShowDirArrow();

    CMonsterQuadRes *GetCurrQuad() const
    {
        return mCurQuadRes;
    }
    const unsigned char	*GetReachableData() const
    {
        return m_reachableData;
    }

//operations
public:
    virtual void Redo(void);
    virtual void Undo(void);
    virtual bool CanRedo(void);
    virtual bool CanUndo(void);

    bool DoDeleteMonsterQuad();
    bool DeleteMonsterQuad(CMonsterQuadRes *pRes);

    bool DoAddMonsterQuad(float top, float left, float right, float bottom);
    bool AddMonsterQuad(CMonsterQuadRes *pRes);

    bool DoPasteMonsterQuad(CMonsterQuadRes *pRes_);

    //bool DoUpdateMonsQuad(CMonsterQuadRes *_pRes_, float x, float y, float w, float h);
    bool UpdateMonsQuad(CMonsterQuadRes *_pRes_, float x, float y, float w, float h);

    bool DoRefreshMonsterPoint(CMonsterQuadRes *_pRes_);
    bool RefreshMonsterPoint(CMonsterQuadRes *_pRes_);
    bool RevertMonsterPoint(CMonsterQuadRes *_pRes_, const Vector2 *points_, UINT size_);

    bool DoSetMonsterType(CMonsterQuadRes *_pRes_, sInt32 type_, int index_);
    bool SetMonsterType(CMonsterQuadRes *_pRes_, sInt32 type_, int index_);

    bool DoSetMonsterCount(CMonsterQuadRes *_pRes_, UINT count_);
    bool SetMonsterCount(CMonsterQuadRes *_pRes_, UINT count_);

    bool DoSetMonterRatio(CMonsterQuadRes *_pRes_, float ratio_);
    bool SetMonterRatio(CMonsterQuadRes *_pRes_, float ratio_);

    bool DoSetMonsterInterval(CMonsterQuadRes *_pRes_, sInt32 interval_);
    bool SetMonsterInterval(CMonsterQuadRes *_pRes_, sInt32 interval_);

    bool DoSetEnterScript(CMonsterQuadRes *_pRes_, const char *script_);
    bool DoSetLeaveScript(CMonsterQuadRes *_pRes_, const char *script_);
    bool SetScript(CMonsterQuadRes *_pRes_, const char *script_, bool bEnter_);

    bool DoAddAutoTalk(CMonsterQuadRes *_pRes_, int id_, int time_, int nextTimeId_);
    bool AddAutoTalk(CMonsterQuadRes *_pRes_, const CMonsterQuadRes::AutoTalk &talk_);

    bool DoDeleteAutoTalk(CMonsterQuadRes *_pRes_, int index_);
    bool DeleteAutoTalk(CMonsterQuadRes *_pRes_, int index_);

    bool DoModifyAutoTalk(CMonsterQuadRes *_pRes_, int index_, int id_, int time_, int nextTimeId_);
    bool ModifyAutoTalk(CMonsterQuadRes *_pRes_, int index_, int id_, int time_, int nextTimeId_);

    bool DoAddTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int stringId_, int probability_);
    bool AddTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int stringId_, int probability_);

    bool DoDeleteTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_);
    bool DeleteTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_);

    bool DoModifyTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_, int stringId_, int probability_);
    bool ModifyTalk(CMonsterQuadRes *_pRes_, int ownerIndex_, int index_, int stringId_, int probability_);

    bool DoSetMonsterVisible(CMonsterQuadRes *_pRes_, bool bVisible);
    bool SetMonsterVisible(CMonsterQuadRes *_pRes_, bool bVisible);

protected:
    CResEditMgr *GetResMgr();
    void DeleteModel();

protected:
	optMode m_eoptMode;

	CToolMonsterQuadDlg *mMonsQuadDlg;

    CMonsterQuadRes *mCurQuadRes;
	CMonsterQuadRes mTempQuadRes;

protected:
    TObjectEditInfo *m_selPmpBox;
    TObjectEditInfo *m_dirArrow;				// 单点怪朝向箭头

    float m_maxRayCastDistanceBak;
    const unsigned char *m_reachableData;

    CRecoveryManager m_opManager;
    CPickingVisitor m_pickingVisitor;
};

#endif //__TOOL_MONSTER_QUAD_H__