#include <MeFoundation/MeFoundationPCH.h>
#include "MeTerrain/WorldPrecompiled.hpp"
#include <MeCommon/HeightMapData.h>
#include "Me3d/Me3d.h"
#include "Me3d/Global.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDX.h"
#include "Me3d/Config.h"
#include "Me3d/Camera.h"
#include "MeTerrain/MeTimelineSnowyEvent.h"

inline DWORD FloatToDWord(float f)
{
	return *((DWORD *) &f);
}

inline float GetRandomFloat(float min, float max)
{
	float diff = max - min;
	float r = rand() / (float) RAND_MAX;
	return (r * diff) + min; 
}

inline void GetRandomVector( Vector* out, const Vector* min, const Vector* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

void MeTimelineSnowyEvent::MeSnowParticle::Reset(const SnowOcclusionBox &sbb, float speed)
{
	GetRandomVector(&Position, &sbb.mMin, &sbb.mMax);
	Position.z = sbb.mMax.z;

	Velocity.x = GetRandomFloat( -0.8,   0.8);
	Velocity.y = GetRandomFloat( -0.8,   0.8);
	Velocity.z = GetRandomFloat(-speed, -0.001);
}

MeTimelineSnowyEvent::MeTimelineSnowyEvent()
{
	mRDX = NULL;

	mSnowFlakeSize = 0;
	mSpeed = 0;

	mSnowTexID = -1;
	mSnowVB = NULL;
	mSnowPartPoolSize = 0;
	mSnowPartBatchSize = 0;

	mCurOffset = 0;
}

MeTimelineSnowyEvent::~MeTimelineSnowyEvent()
{
	DestroyEvent();

	mSnowParticles.clear();
}

void MeTimelineSnowyEvent::SetParams(float size, float speed, int count)
{
	mSnowFlakeSize = size * 0.008;
	if (mSnowFlakeSize < 0)
		mSnowFlakeSize = 0.002;
	mSnowFlakeSize = 5;

	mSpeed = speed;
	if (mSpeed < 0)
		mSpeed = 0.1;

	// 限制雪花总数量
	if (count < 1024)
		count = 1024;
	if (count > 6144)
		count = 6144;

	int ratio = count / 2048;
	mSnowPartPoolSize = ratio * 1024;
	mSnowPartBatchSize = ratio * 512;
	// 限制最小渲染批次
	if (mSnowPartPoolSize < 1024)
		mSnowPartPoolSize = 1024;
	if (mSnowPartBatchSize < 512)
		mSnowPartBatchSize = 512;

	mSnowParticles.resize(count);
	SnowParticlesIter iter = mSnowParticles.begin();
	SnowParticlesIter end = mSnowParticles.end();
	for ( ; iter != end; ++iter)
	{
		iter->Reset(mBoundingBox, mSpeed);
	}
}

void MeTimelineSnowyEvent::InitializeEvent()
{
	MeTimelineShadeEvent::InitializeEvent();

	if (mSnowTexID != -1)
		return;

	mRDX = (RendererDx *) GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) mRDX->GetRealDevice();

	char fileFullPath[MAX_PATH] = {0};
	sprintf_s(fileFullPath, MAX_PATH - 1, "%s%s", GetRootPath(), ME_SNOWFLAKE_RES);
	mSnowTexID = GetEngine()->GetTextureManager()->RegisterTexture(fileFullPath, NULL, NULL);

	//D3DCAPS9 caps;
	//device->GetDeviceCaps(&caps);
	//if (caps.FVFCaps & D3DFVFCAPS_PSIZE)

	OnDeviceReset();
}

void MeTimelineSnowyEvent::DestroyEvent()
{
	if (mSnowVB != NULL)
	{
		mSnowVB->Release();
		mSnowVB = NULL;
	}
}

void MeTimelineSnowyEvent::ResetEvent()
{
	MeTimelineShadeEvent::ResetEvent();
}

void MeTimelineSnowyEvent::RenderEvent(const Vector &playerPos)
{
	if (GetEventState() != EES_Running)
		return;

	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) mRDX->GetRealDevice();

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	device->SetTransform(D3DTS_WORLD, &mat);
	
	UpdateSnowParticles(playerPos);
	if (!mSnowParticles.empty() && mSnowVB != NULL)
	{
		PreRender();

		if (mCurOffset >= mSnowPartPoolSize)
			mCurOffset = 0;

		MeSnowVertex *v = NULL;
		mSnowVB->Lock(mCurOffset * sizeof(MeSnowVertex), mSnowPartBatchSize * sizeof(MeSnowVertex),
			(void **) &v, mCurOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		int batchCounter = 0;

		SnowParticlesIter iter = mSnowParticles.begin();
		SnowParticlesIter iterEnd = mSnowParticles.end();
		for ( ; iter != iterEnd; ++iter)
		{
			v->Position = iter->Position;
			v->Size = mSnowFlakeSize;

			++v;
			++batchCounter;

			if (batchCounter == mSnowPartBatchSize)
			{
				mSnowVB->Unlock();
				device->DrawPrimitive(D3DPT_POINTLIST, mCurOffset, mSnowPartBatchSize);

				mCurOffset += mSnowPartBatchSize;
				if (mCurOffset >= mSnowPartPoolSize)
					mCurOffset = 0;

				mSnowVB->Lock(mCurOffset * sizeof(MeSnowVertex), mSnowPartBatchSize * sizeof(MeSnowVertex),
					(void **) &v, mCurOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				batchCounter = 0;
			}
		}
		mSnowVB->Unlock();

		if (batchCounter > 0)
		{
			device->DrawPrimitive(D3DPT_POINTLIST, mCurOffset, batchCounter);
		}

		mCurOffset += mSnowPartBatchSize;

		PostRender();
	}
}

void MeTimelineSnowyEvent::UpdateBeginToFull( const MeTimeValue& kTime )
{

}

void MeTimelineSnowyEvent::UpdateInFull( const MeTimeValue& kTime )
{

}

void MeTimelineSnowyEvent::UpdateFullToEnd( const MeTimeValue& kTime )
{

}

void MeTimelineSnowyEvent::OnDeviceLost()
{
	DestroyEvent();
}

void MeTimelineSnowyEvent::OnDeviceReset()
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) mRDX->GetRealDevice();

	device->CreateVertexBuffer(mSnowPartPoolSize * sizeof(MeSnowVertex), D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		MeSnowVertex::FVF, D3DPOOL_DEFAULT, &mSnowVB, 0);
}

void MeTimelineSnowyEvent::PreRender()
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) mRDX->GetRealDevice();

	// save old renderstates
	device->GetRenderState(D3DRS_LIGHTING, &mOldRS[0]);
	device->GetRenderState(D3DRS_ALPHABLENDENABLE, &mOldRS[1]);

	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	device->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	//device->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	//device->SetRenderState(D3DRS_POINTSIZE, FloatToDWord(mSnowFlakeSize));
	//device->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDWord(0.0));

	// 使用贴图中的Alpha值
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	device->SetFVF(MeSnowVertex::FVF);
	device->SetStreamSource(0, mSnowVB, 0, sizeof(MeSnowVertex));
	device->SetIndices(NULL);

	TextureDx8 *texturedx8 = (TextureDx8 *) GetEngine()->GetTextureManager()->GetTextureNoLock(mSnowTexID);
	if (texturedx8 != NULL)
	{
		LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9) texturedx8->GetTexture();
		if (tex != NULL)
		{
			device->SetTexture(0, tex);
		}
	}
}

void MeTimelineSnowyEvent::PostRender()
{
	mRDX->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	mRDX->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	// restore renderstates
	mRDX->SetRenderState(D3DRS_LIGHTING, mOldRS[0]);
	mRDX->SetRenderState(D3DRS_ALPHABLENDENABLE, mOldRS[1]);
}

void MeTimelineSnowyEvent::UpdateSnowParticles(const Vector &playerPos)
{
	SnowParticlesIter iter = mSnowParticles.begin();
	SnowParticlesIter iterEnd = mSnowParticles.end();
	for ( ; iter != iterEnd; ++iter)
	{
		iter->Position += iter->Velocity * 0.05156;

		mBoundingBox.Update(playerPos, 50);
		if (!mBoundingBox.IsInside(iter->Position))
		{
			iter->Reset(mBoundingBox, mSpeed);
		}
	}
}