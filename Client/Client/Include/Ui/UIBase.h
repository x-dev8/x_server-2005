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
	virtual bool UnLoadUI();									// ж��UI
	virtual bool IsVisable();									// �Ƿ�ɼ�
	virtual void SetVisable( const bool bVisable );				// �����Ƿ����

    virtual void InitializeAtEnterWorld() {}					// ÿ�ε�½��Ϸ���õ��߼�
	virtual void RefreshByItemChange() {}						// ��Ʒ�ı䵼�µĽ������
	virtual void RefreshByMoneyChange() {}						// ��Ǯ�ı䵼�µĽ������
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
	virtual bool _LoadUI() = 0;									// ����UI
	virtual bool DoControlConnect() = 0;						// �����ؼ�
	virtual bool _UnLoadUI() = 0;								// ж��UI
	virtual bool _IsVisable() = 0;								// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

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
	virtual void SetVisable(const bool bVisable ) { _SetVisable(bVisable); }	// ����������������Ϊ�˲�����uimgr�Ĺ���
	virtual bool IsVisable() {return _IsVisable(); }							// �Ƿ�ɼ�
};

//zizi add --���岼��
//--Ŀ��:���½ǽ��棬��ϵͳ�����⣬�ȴ򿪵Ľ���Y����У�X�῿����߽�4�����أ�
//--	  ��򿪵Ľ������ȴ򿪵Ľ����Ҳ࣬���4�����أ�ͬʱֻ��ʾ2�����棬���ٴ��µĽ��棬
//--	  ���ȴ򿪵Ľ��汻��������ڽ����С��ͬ��λ����Ҫ�������С�
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
// 	std::vector<ControlFrame*>		_vecFrame;	//������Ҫ���ֵĴ���frame
// 
// 	ControlFrame*	_FristShow;	//��¼��һ����ʾ�Ĵ���
// 	ControlFrame*	_SecondShow;//��¼�ڶ�����ʾ�Ĵ���  �����ʾ2��
// 
// 	int	_nShowCnt;		//��¼Ŀǰ��ʾ�Ĵ���ĸ���
// };

class MexAnimCtrl;
#define UI_LAYOUT_1		1
#define UI_LAYOUT_2		2
#define UI_LAYOUT_3		3
#define UI_LAYOUT_4		4