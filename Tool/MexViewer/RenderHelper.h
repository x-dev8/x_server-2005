#pragma once

#include "MiddleWindow.h"
#include "MexViewerCamera.h"

#define GRID_SIZE					800
#define RH_MAX_CACHE_MODEL_OBJ		200

/*
* 渲染辅助类
*/
class ModelObj;
class MexViewerCamera;
class RenderHelper
{
public:
	friend ModelObj;

public:
	RenderHelper(HWND hWnd, int w, int h);
	virtual ~RenderHelper();

public:
	/*
	 * 渲染
	 */
	void Render();

	/*
	* 获取当前显示的模型
	*/
	ModelObj * GetCurrentModel() { return mModelObj; }

	/*
	 * 设置当前显示的模型
	 */
	ModelObj * SetCurrentModel(const wxString &path);

	/*
	 * 获取背景颜色
	 */
	D3DCOLOR GetBackgroundColor() const { return mBackgroundColor; }

	/*
	 * 设置背景颜色
	 */
	void SetBackgroundColor(D3DCOLOR bg) { mBackgroundColor = bg; }

	/*
	 * 添加模式到Cache链表
	 */
	ModelObj * AppendModelToCacheLink(const wxString &path);

	/*
	 * 按动作名播放动画
	 */
	void PlayCurrentModelByAnimName(const char *anim);

	/*
	 * 绕Z轴旋转当前模型及辅助网格
	 */
	void RotateCurrentModelAndGrid(const wxPoint &delta);

	/*
	 * 移动当前模型
	 */
	void MoveCurrentModel(const wxPoint &delta);

	/*
	 * 重新加载当前模型
	 */
	void ReloadCurrentModel();

	/*
	 * 调整摄像机远近
	 */
	void AdjustCameraFarAwayOrComeClose(const wxMouseEvent &evt);

	/*
	 * 调整摄像机位置或旋转
	 */
	void AdjustCamera(const wxPoint &delta, bool rotate);

	/*
	 * 获取灯光参数
	 */
	D3DLIGHT9 & GetLightParam() { return mLight; }

	/*
	 * 设置灯光
	 */
	void SetLighting(bool useDefault = false);

protected:
	/*
	 * 创建设备
	 */
	bool CreateHardwareDevice(HWND hWnd);

	/*
	 * 设置
	 */
	void Setup();

	/*
	 * 设置摄像机
	 */
	void CameraSetup();

	/*
	 * 返回硬件支持的MultiSample最佳级别
	 */
	D3DMULTISAMPLE_TYPE GetBestAvailableMultiSampleType(LPDIRECT3D9 d3d9, D3DFORMAT fmt);

	/*
	 * 返回默认灯光设置
	 */
	void GetDefaultLightParam(D3DLIGHT9 &light);

	/*
	 * 更新
	 */
	void Update();

	/*
	 * 渲染帮助信息, 如FPS
	 */
	void RenderInfo();

	/*
	 * 渲染10 x 10的辅助网格
	 */
	void RenderGrid10x10();

protected:
	D3DPRESENT_PARAMETERS mPP;
	LPDIRECT3DDEVICE9 mDevice;

	D3DXMATRIX mWorldMatrix;
	MexViewerCamera mCamera;
	IRenderer *mRenderer;

	/* 渲染收集器 */
	MeCollectorPtr mShimmerCollector;
	MeCollectorPtr mAlphaCollector;
	MeSorterPtr mBitSorter;

	/* 宽高 */
	float mWidth;
	float mHeight;

	/* 背景颜色 */
	D3DCOLOR mBackgroundColor;

	/* 场景灯光 */
	D3DLIGHT9 mLight;

	/* 当前选中的模型 */
	ModelObj *mModelObj;
	
	/* 模型缓冲链表 */
	std::list<ModelObj *> mModelCacheLink;

	/* 字体对象 */
	LPD3DXFONT mFont;

	/* fps */
	DWORD mLastTime;
	DWORD mFramesPerSec;

	std::wstring mVideoCard;
};