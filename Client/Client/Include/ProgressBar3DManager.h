#pragma once
#pragma warning(disable : 4005)
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDx.h"
#include "Me3d/Include.h"
#pragma warning(default : 4005)

#include <string>
#include <list>
#include "include/Billboard3D.h"

class ProgressBar3D : public MeCommonAllocObj<ProgressBar3D>
{
public:
	ProgressBar3D();
	virtual ~ProgressBar3D();

	virtual HRESULT Create(LPDIRECT3DDEVICE9 device, const std::string& texFilename,
		const D3DXVECTOR2 backgroundUV[]/*4*/, const D3DXVECTOR2 progressUV[]/*4*/,
		float widthRateBack, float heightRateBack, float widthRateBar, float heightRateBar,
		DWORD color, DWORD backColor);
	virtual void Render();
	virtual void Destroy();

	virtual void SetPosition(const D3DXVECTOR3& pos);
	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual void SetVisible(bool v);
	bool		 GetVisible() { return m_bVisible; }
	virtual void SetOffsetY(float offsetY);

	virtual void SetMaxValue(int v);
	virtual void SetValue(int v);

	void SetCamera(MeCamera* camera);

private:
	void GetBackgroundVertexData(BillboardBase::Vertex vs[]);
	void GetBarVertexData(BillboardBase::Vertex vs[]);

private:
	BillboardBase* m_pElements[2];
	D3DXVECTOR2 m_backgroundUV[4];
	D3DXVECTOR2 m_progressUV[4];
	float m_fWidthRateBack;
	float m_fHeightRateBack;
	float m_fWidthRateBar;
	float m_fHeightRateBar;
	float m_fOffsetY;
	int m_nMaxValue;
	int m_nValue;
	float m_fValueRate;
	short m_nTexId;
	bool m_bVisible;

	DWORD m_color;
	DWORD m_backColor;
};

class ProgressBar3DManager
{
public:
	ProgressBar3DManager();
	~ProgressBar3DManager();

	static ProgressBar3DManager& Get()
	{
		if (!s_pInst)
			s_pInst = new ProgressBar3DManager();
		return *s_pInst;
	}

	static void Shutdown()
	{
		if (s_pInst)
		{
			delete s_pInst;
			s_pInst = 0;
		}
	}

	void Render();
	void Destroy();

	void AddProgressBar3D(ProgressBar3D* v);
	void RemoveProgressBar3D(ProgressBar3D* v);

private:
	std::list<ProgressBar3D*> m_progressBar3Ds;
	static ProgressBar3DManager* s_pInst;
};