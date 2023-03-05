#pragma once

#include "MiddleWindow.h"
#include "MexViewerCamera.h"

#define GRID_SIZE					800
#define RH_MAX_CACHE_MODEL_OBJ		200

/*
* ��Ⱦ������
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
	 * ��Ⱦ
	 */
	void Render();

	/*
	* ��ȡ��ǰ��ʾ��ģ��
	*/
	ModelObj * GetCurrentModel() { return mModelObj; }

	/*
	 * ���õ�ǰ��ʾ��ģ��
	 */
	ModelObj * SetCurrentModel(const wxString &path);

	/*
	 * ��ȡ������ɫ
	 */
	D3DCOLOR GetBackgroundColor() const { return mBackgroundColor; }

	/*
	 * ���ñ�����ɫ
	 */
	void SetBackgroundColor(D3DCOLOR bg) { mBackgroundColor = bg; }

	/*
	 * ���ģʽ��Cache����
	 */
	ModelObj * AppendModelToCacheLink(const wxString &path);

	/*
	 * �����������Ŷ���
	 */
	void PlayCurrentModelByAnimName(const char *anim);

	/*
	 * ��Z����ת��ǰģ�ͼ���������
	 */
	void RotateCurrentModelAndGrid(const wxPoint &delta);

	/*
	 * �ƶ���ǰģ��
	 */
	void MoveCurrentModel(const wxPoint &delta);

	/*
	 * ���¼��ص�ǰģ��
	 */
	void ReloadCurrentModel();

	/*
	 * ���������Զ��
	 */
	void AdjustCameraFarAwayOrComeClose(const wxMouseEvent &evt);

	/*
	 * ���������λ�û���ת
	 */
	void AdjustCamera(const wxPoint &delta, bool rotate);

	/*
	 * ��ȡ�ƹ����
	 */
	D3DLIGHT9 & GetLightParam() { return mLight; }

	/*
	 * ���õƹ�
	 */
	void SetLighting(bool useDefault = false);

protected:
	/*
	 * �����豸
	 */
	bool CreateHardwareDevice(HWND hWnd);

	/*
	 * ����
	 */
	void Setup();

	/*
	 * ���������
	 */
	void CameraSetup();

	/*
	 * ����Ӳ��֧�ֵ�MultiSample��Ѽ���
	 */
	D3DMULTISAMPLE_TYPE GetBestAvailableMultiSampleType(LPDIRECT3D9 d3d9, D3DFORMAT fmt);

	/*
	 * ����Ĭ�ϵƹ�����
	 */
	void GetDefaultLightParam(D3DLIGHT9 &light);

	/*
	 * ����
	 */
	void Update();

	/*
	 * ��Ⱦ������Ϣ, ��FPS
	 */
	void RenderInfo();

	/*
	 * ��Ⱦ10 x 10�ĸ�������
	 */
	void RenderGrid10x10();

protected:
	D3DPRESENT_PARAMETERS mPP;
	LPDIRECT3DDEVICE9 mDevice;

	D3DXMATRIX mWorldMatrix;
	MexViewerCamera mCamera;
	IRenderer *mRenderer;

	/* ��Ⱦ�ռ��� */
	MeCollectorPtr mShimmerCollector;
	MeCollectorPtr mAlphaCollector;
	MeSorterPtr mBitSorter;

	/* ��� */
	float mWidth;
	float mHeight;

	/* ������ɫ */
	D3DCOLOR mBackgroundColor;

	/* �����ƹ� */
	D3DLIGHT9 mLight;

	/* ��ǰѡ�е�ģ�� */
	ModelObj *mModelObj;
	
	/* ģ�ͻ������� */
	std::list<ModelObj *> mModelCacheLink;

	/* ������� */
	LPD3DXFONT mFont;

	/* fps */
	DWORD mLastTime;
	DWORD mFramesPerSec;

	std::wstring mVideoCard;
};