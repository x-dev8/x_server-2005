#pragma once

#include "MeUi/MeUi.h"
#include "MeUi/UiManager.h"
#include "Me3d/Camera.h"
// #define DECLARE_DLG_INST(cname)					\
// 	public:										\
// 		static cname* instance()				\
// 		{										\
// 			static cname* pDlg = NULL;			\
// 			if( NULL == pDlg )					\
// 			{									\
// 				pDlg = MeNew cname();				\
// 				assert(pDlg);					\
// 				pDlg->LoadUI();					\
// 				pDlg->SetVisable(false);		\
// 			}									\
// 			return pDlg;						\
// 		}

class CPlayer;
class CPlayerAnim;
class MeCamera;
class CUIBase : public MeCommonAllocObj<CUIBase>
{
public:
	CUIBase();
	CUIBase(int nType);
	virtual ~CUIBase();

public:
	virtual bool IsHoldInMemory() const { return false; }
	virtual bool LoadUI();
	virtual bool UnLoadUI();									// 卸载UI
	virtual bool IsVisable();									// 是否可见
	virtual void SetVisable( const bool bVisable );				// 设置是否可视

    virtual void InitializeAtEnterWorld() {}					// 每次登陆游戏调用的逻辑
	virtual void RefreshByItemChange() {}						// 物品改变导致的界面更新
	virtual void RefreshByMoneyChange() {}						// 金钱改变导致的界面更新
	virtual void ResetDevice() {}

public:
	void OnPoise( int x, int y );
	void OnMouseMove(int x, int y);
	void OnLButtonDown(int x, int y);
	void OnLButtonUp(int x, int y);
	void OnRButtonDown(int x, int y);
	void OnRButtonUp(int x, int y);
	void OnRDBClick(int x, int y);
	void OnLDBClick(int x, int y);
	bool OnKeyDown( WPARAM wParam, LPARAM lParam );
	bool OnKeyUp( WPARAM wParam, LPARAM lParam );

public:
	bool IsUILoad() const { return m_bUILoad; }

	void SetLastUiVisable(bool bValue) { m_bLastUiVisable = bValue; }
	bool IsLastUiVisable() { return m_bLastUiVisable; }

	DWORD GetLastVisibleTime() const { return m_LastVisibleTime; }
	void SetLastVisibleTime(DWORD val) { m_LastVisibleTime = val; }

protected:
	virtual bool _LoadUI() = 0;									// 载入UI
	virtual bool DoControlConnect() = 0;						// 关连控件
	virtual bool _UnLoadUI() = 0;								// 卸载UI
	virtual bool _IsVisable() = 0;								// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

protected:
	bool m_bUILoad;
	DWORD m_BornTime;
	DWORD m_LastVisibleTime;

private:
	bool m_bLastUiVisable;
};

class CUIRenderAnim
{
public:
	enum RenderToWhichUI
	{
		RTWUI_GUT_QUEST = 0,
		RTWUI_CHARACTER_PROPERTY,
		RTWUI_FUJIANG,
		RTWUI_MOUNT,
		RTWUI_TARGET_VIEW,
		RTWUI_SHOP_FASION
	};

public:
	CUIRenderAnim();

public:
	void RenderAnim_Create(RenderToWhichUI which, float rotate = 0.0);
	void RenderAnim_Destroy();
	void RenderAnim_SetModelID(int modelID);
	void RenderAnim_PlayAction(const char *action, int times, const char *nextAction);
	void RenderAnim_RotateReset();
	void RenderAnim_RotateZ(bool isClockwise, float step = 0.1);
	void RenderAnim_Update(
		DWORD x,  DWORD y, DWORD w, DWORD h,
		const D3DXVECTOR3 &eyePos);
	void RenderAnim(const D3DXVECTOR3 &modelPos, float scale = 0.05);

	CPlayer * RenderAnim_GetPlayer() { return mPlayer; }

private:
	void PreRender();
	void PostRender();

private:
	RenderToWhichUI mWhichUI;

	IRenderer *mRenderer;
	D3DVIEWPORT9 mViewport;
	MeCamera mCamera;

	CPlayer *mPlayer;
	float mRotateZ;

	float mOldLodBias;
	D3DLIGHT9 mOldLight;
	DWORD mOldRS[5];
};

class CUIIntonationUtility
{
public:
	typedef void (*AFTER_INTONATION) (void *data);
public:
	CUIIntonationUtility();
	virtual ~CUIIntonationUtility();

protected:
	void IntonationUtility_Start(DWORD duration, const char *name, AFTER_INTONATION callback = 0, void *data = 0, int dataLength = 0);
	void IntonationUtility_Tick();

private:
	void DestroyCallbackData();

private:
	bool mIntonating;

	DWORD mIntonateStartTime;
	DWORD mIntonatingDuration;

	AFTER_INTONATION mCallback;
	void *mCallbackData;
};

class CUINotManagedByUIMgr : public CUIBase
{
public:
	CUINotManagedByUIMgr() : CUIBase(0) {}
	virtual bool LoadUI() { return _LoadUI(); }
	virtual void SetVisable(const bool bVisable ) { _SetVisable(bVisable); }	// 重载这两个函数，为了不接受uimgr的管理
	virtual bool IsVisable() {return _IsVisable(); }							// 是否可见
};

//zizi add --窗体布局
//--目的:右下角界面，除系统界面外，先打开的界面Y轴居中，X轴靠左，离边界4个像素，
//--	  后打开的界面在先打开的界面右侧，间隔4个像素，同时只显示2个界面，若再打开新的界面，
//--	  最先打开的界面被替代，由于界面大小不同，位置需要重新排列。
// class CUILayout
// {
// public:
// 	static CUILayout* GetInstance()
// 	{
// 		static CUILayout dlg;
// 		return &dlg;
// 	}
// 	CUILayout() : _nShowCnt(0), _FristShow(NULL), _SecondShow(NULL)
// 	{
// 	}
// 	~CUILayout()
// 	{
// 	}
// 	void Restore()
// 	{
// 		_nShowCnt = 0;
// 		_vecFrame.clear();
// 		if(_FristShow)
// 		{
// 			_FristShow = NULL;
// 		}
// 		if(_SecondShow)
// 		{
// 			_SecondShow = NULL;
// 		}
// 	}
// 	void AddFrame(ControlFrame* pFrame)
// 	{
// 		if(pFrame)
// 			_vecFrame.push_back(pFrame);
// 	}
// 
// 	void SetVisable(ControlFrame* pFrame);
// 
// public:
// 	std::vector<ControlFrame*>		_vecFrame;	//保存需要布局的窗口frame
// 
// 	ControlFrame*	_FristShow;	//记录第一个显示的窗体
// 	ControlFrame*	_SecondShow;//记录第二个显示的窗体  最多显示2个
// 
// 	int	_nShowCnt;		//记录目前显示的窗体的个数
// };

class MexAnimCtrl;
#define UI_LAYOUT_1		1
#define UI_LAYOUT_2		2
#define UI_LAYOUT_3		3
#define UI_LAYOUT_4		4