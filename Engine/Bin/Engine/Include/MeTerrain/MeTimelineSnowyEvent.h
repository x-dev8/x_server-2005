#pragma once

#include <MeFoundation/MeTimelineShadeEvent.h>

#define	ME_SNOWFLAKE_RES			"Data\\Texture\\snowflake.dds"

// ÅäÖÃÎÄ¼þÊ¾Àý
/*
	<Event Type="3"
		StartTime="3000" EndTime="3600000"
		ToFull="1000" ToEnd="100000"
		SnowSize="0.2857" SnowRange="30" SnowSpeed="0.09585"/>*/

class CHeightMapData;
class MEFOUNDATION_ENTRY MeTimelineSnowyEvent : public MeTimelineShadeEvent
{
public:
	struct SnowOcclusionBox
	{
		SnowOcclusionBox() : mMin(0, 0, 0), mMax(0, 0, 0)
		{

		}

		bool IsInside(const Vector &p)
		{
			if (p.x >= mMin.x && p.y >= mMin.y && p.z >= mMin.z
				&& p.x <= mMax.x && p.y <= mMax.y && p.z <= mMax.z)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void Update(const Vector &center, float range)
		{
			mMin = center;
			mMax = center;

			mMin += Vector(-range, -range, -range);
			mMax += Vector( range,  range,  range);

			mMax.z -= range * 0.5;
		}

		Vector mMin;
		Vector mMax;
	};

	struct MeSnowVertex
	{
		Vector Position;
		float Size;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_PSIZE;
	};

	struct MeSnowParticle
	{
		void Reset(const SnowOcclusionBox &sbb, float speed);

		Vector Position;
		Vector Velocity;
	};

public:
	MeTimelineSnowyEvent();
	virtual ~MeTimelineSnowyEvent();

public:
	void SetParams(float size, float speed, int count);

public:
	virtual void InitializeEvent();
	virtual void DestroyEvent();
	virtual void ResetEvent();
	virtual void RenderEvent(const Vector &playerPos);
	virtual void UpdateBeginToFull(const MeTimeValue &kTime);
	virtual void UpdateInFull(const MeTimeValue &kTime);
	virtual void UpdateFullToEnd(const MeTimeValue &kTime);

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

private:
	void PreRender();
	void PostRender();

	void UpdateSnowParticles(const Vector &playerPos);

private:
	typedef std::list<MeSnowParticle> SnowParticles;
	typedef SnowParticles::iterator SnowParticlesIter;

	RendererDx *mRDX;

	SnowOcclusionBox mBoundingBox;

	float mSnowFlakeSize;
	float mSpeed;

	int mSnowTexID;
	LPDIRECT3DVERTEXBUFFER9 mSnowVB;
	int mSnowPartPoolSize;
	int mSnowPartBatchSize;

	int mCurOffset;
	SnowParticles mSnowParticles;

	DWORD mOldRS[2];
};