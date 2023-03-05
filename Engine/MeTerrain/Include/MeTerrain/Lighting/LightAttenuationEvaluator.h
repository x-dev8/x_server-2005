//-----------------------------------------------------------------------------
// File:	LightAttenuationEvaluator.h
// Desc:	����ƹ�˥���ĸ�����
// Create: 	01/20/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef LIGHT_ATTENUATION_EVALUATOR_H
#define LIGHT_ATTENUATION_EVALUATOR_H
#include "MeTerrain/stdafx.h"
#include "MeTerrain/Lighting/LightRes.h"

#define MaxTraceDistance 1000

class LightAttenuationEvaluator
{
public:
	LightAttenuationEvaluator(): m_pLightActor(NULL), m_fRecipLightRadiusSqr(0.f), m_fAngleXZ(0.f), m_fAngleYZ(0.f) {}

	LightAttenuationEvaluator(LightRes* pLightActor): m_fRecipLightRadiusSqr(0.f), m_fAngleXZ(0.f), m_fAngleYZ(0.f)
	{ SetLightActor(pLightActor); }

	inline void SetLightActor(LightRes* pLightActor)
	{
		m_pLightActor = pLightActor;
		
		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:	// ̫���⣬�����
			{
				// �⳯��
				DirectionLight* pDirLight = (DirectionLight*)pLightActor;
				m_vLightDirection = pDirLight->GetDir();
				m_fAngleXZ = atan(m_vLightDirection.x/m_vLightDirection.z);
				m_fAngleYZ = atan(m_vLightDirection.y/m_vLightDirection.z);
			}
			break;
		case LightRes::LT_POINTLIGHT:		// ���Դ
			{
				PointLight* pPointLight = (PointLight*)pLightActor;
				FLOAT Radius = pPointLight->GetDist() - pPointLight->GetNearDist();
				m_fRecipLightRadiusSqr = 1.f/max(1.f, Radius * Radius);
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			{
				// �⳯��ͬ����⣩
				// �뾶��ͬ���Դ��
				// �۹�Ƶ�ͶӰ����
			}
			break;
		default:
			break;
		}
	}

	inline LightRes* GetLightActor() { return m_pLightActor; }

	inline FLOAT AngleDistance_Attenuation(const Vector& Vertex_Pos, const Vector& Vertex_Normal)
	{
		return Angle_Attenuation(Vertex_Pos, Vertex_Normal) * Distance_Attenuation(Vertex_Pos);
	}

	inline FLOAT Distance_Attenuation(const Vector& Vertex_Pos)
	{
		assert(m_pLightActor);

		FLOAT fAttenuation = 0.f;
		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:	// ̫���⣬�����
			{
				fAttenuation = 1.f;
			}
			break;
		case LightRes::LT_POINTLIGHT:		// ���Դ
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				Vector v = pPointLight->GetPos() - Vertex_Pos;
				float fLength = v.length();
				if( fLength - pPointLight->GetNearDist() <= 0 )
					fAttenuation = 1.f;
				else if( fLength > pPointLight->GetDist() )
					fAttenuation = 0.f;
				else
				{
					fLength -= pPointLight->GetNearDist();
					FLOAT fDistanceSqr = fLength*fLength;
					fAttenuation = max(0.0f, 1.0f - (fDistanceSqr * m_fRecipLightRadiusSqr));
					fAttenuation *= fAttenuation;
				}
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			break;
		default:
			break;
		}
		return fAttenuation;
	}

	inline FLOAT Angle_Attenuation(const Vector& Vertex_Pos, const Vector& Vertex_Normal)
	{
		assert(m_pLightActor);

		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:
			{
				// ̫����Sunlight�����Directional light��ֻ�͹⳯���й�
				return max(0.f, (-m_vLightDirection).dot(Vertex_Normal));
			}
			break;
		case LightRes::LT_POINTLIGHT:
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				Vector vDir = pPointLight->GetPos() - Vertex_Pos;
				vDir.normalize();
				return max(0.f, vDir.dot(Vertex_Normal));
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			// ͬ���Դ
			break;
		default:
			break;
		}
		return 0.f;
	}

	inline BOOL Surface_Attenuated(const D3DXPLANE& FacePlane)
	{
		assert(m_pLightActor);

		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:
			{
				const D3DXPLANE* pPlane = (const D3DXPLANE*)&FacePlane;
				return D3DXPlaneDotNormal(pPlane, (D3DXVECTOR3*)&(-m_vLightDirection)) <= 0;
			}
			break;
		case LightRes::LT_POINTLIGHT:
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				const D3DXPLANE* pPlane = (const D3DXPLANE*)&FacePlane;
				return D3DXPlaneDotCoord(pPlane, (D3DXVECTOR3*)&(pPointLight->GetPos())) <= 0;
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			// ͬ���Դ
			break;
		default:
			break;
		}
		return FALSE;
	}

	inline Vector Raytrace_End(const Vector& Vertex_Pos)
	{
		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:
			{
				return Vertex_Pos - MaxTraceDistance * m_vLightDirection;
			}
			break;
		case LightRes::LT_POINTLIGHT:
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				return pPointLight->GetPos();
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			// ͬ���Դ
			break;
		default:
			break;
		}

		return Vector();
	}

	inline FLOAT GetLightXAxisLength()
	{
		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:
			{
				return sin(m_fAngleXZ) * MaxTraceDistance;
			}
			break;
		case LightRes::LT_POINTLIGHT:
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				return pPointLight->GetDist();
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			break;
		default:
			break;
		}
		return 0.f;
	}

	inline FLOAT GetLightYAxisLength()
	{
		switch( m_pLightActor->GetType() )
		{
		case LightRes::LT_DIRECTIONLIGHT:
			{
				return sin(m_fAngleYZ) * MaxTraceDistance;
			}
			break;
		case LightRes::LT_POINTLIGHT:
			{
				PointLight* pPointLight = (PointLight*)m_pLightActor;
				return pPointLight->GetDist();
			}
			break;
		case LightRes::LT_SPOTLIGHT:		// �۹��
			break;
		default:
			break;
		}
		return 0.f;
	}

protected:
	LightRes*		m_pLightActor;
	Vector			m_vLightDirection;
	FLOAT			m_fRecipLightRadiusSqr;	// �뾶ƽ��
	FLOAT			m_fAngleXZ;				// ����X��Z��н�
	FLOAT			m_fAngleYZ;				// ����Y��Z��н�
	//MeMatrix		m_matProjection;
};

#endif /* LIGHT_ATTENUATION_EVALUATOR_H */
