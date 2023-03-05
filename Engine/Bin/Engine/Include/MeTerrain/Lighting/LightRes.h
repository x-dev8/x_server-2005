//-----------------------------------------------------------------------------
// File:	LightRes.h
// Desc:	��̬������Դ����
// Create: 	02/21/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef LIGHT_RES_H
#define LIGHT_RES_H
#include "Me3d/include.h"
#include "MeUtility/Singleton.h"
#include "MeTerrain/NiColor.h"

#define INVALID_STATIC_LIGHT_DATA -1

class CWorldTile;
class TObjectInfo;
////////////////////////////////////////////////////////////////////////////////////////////
// �ƹ���Դ
class LightRes: public MeCommonAllocObj<LightRes>
{
public:
	enum ELightType
	{
		LT_POINTLIGHT = 0,
		LT_DIRECTIONLIGHT,
		LT_SPOTLIGHT,
		LT_MAX
	};
	LightRes() {}
	LightRes( const NiColorB& color ): m_Color(color) {}
	virtual ~LightRes() {}

	virtual unsigned char GetType() = 0;

	// ����
	const NiColorB&	GetColor() const { return m_Color; }

	// ����
	void			SetColor(NiColorB color) { m_Color = color; }

	// ��ȡ
	virtual bool	Read(FILE* stream);
	virtual bool	SaveToFile(FILE* stream);

protected:
	NiColorB		m_Color;	//ARGB
};

// ���Դ
class PointLight: public LightRes
{
public:
	PointLight(): m_fNearDist(0.f), m_fDist(1.f) {}
	PointLight( float neardist, float dist, const Vector& pos, const NiColorB& color )
		: LightRes(color) 
		, m_fNearDist(neardist)
		, m_fDist(dist)
		, m_vPos(pos)
	{}
	virtual ~PointLight() {}

	virtual unsigned char GetType() { return LightRes::LT_POINTLIGHT; }

	// ��ȡ
	virtual bool	Read(FILE* stream);
	virtual bool	SaveToFile(FILE* stream);

	float			GetNearDist() const { return m_fNearDist; }
	float			GetDist() const { return m_fDist; }
	const Vector&	GetPos() const { return m_vPos; }

	void			SetNearDist(float d) { m_fNearDist = d; }
	void			SetDist(float d) { m_fDist = d; }
	void			SetPos(Vector pos) { m_vPos = pos; }
	void			SetPosX(float x) { m_vPos.x = x; }
	void			SetPosY(float y) { m_vPos.y = y; }
	void			SetPosZ(float z) { m_vPos.z = z; }
protected:
	Vector			m_vPos;
	float			m_fNearDist;	// �ӽ��࿪ʼ˥��
	float			m_fDist;		// ����Ӱ��뾶
};

// �����
class DirectionLight: public LightRes
{
public:
	DirectionLight(): m_bIsChunkLight(false) {}
	DirectionLight( const Vector& dir, const NiColorB& color )
		: LightRes(color)
		, m_vDir(dir)
		, m_bIsChunkLight(false)
	{}
	virtual ~DirectionLight() {}

	virtual unsigned char GetType() { return LightRes::LT_DIRECTIONLIGHT; }

	// ��ȡ
	virtual bool	Read(FILE* stream);
	virtual bool	SaveToFile(FILE* stream);

	const Vector&	GetDir() const { return m_vDir; }

	void			SetDir(const Vector& dir) { m_vDir = dir; m_vDir.normalize(); }

	bool			IsChunkLight() const { return m_bIsChunkLight; }
	void			SetChunkLight(bool flag) { m_bIsChunkLight = flag; }

protected:
	Vector			m_vDir;
	bool			m_bIsChunkLight;	// �ǵر�����Ĺ�Դ
};

//////////////////////////////////////////////////////////////////////////////////////////
// ȫ�־�̬�ƹ�����
class StaticLightsContainer: public Singleton<StaticLightsContainer>
{
public:
	// ����
	StaticLightsContainer(): m_usMaxKey(0) { m_mapStaticLights.clear(); m_mapObjectAffectLight.clear(); }

	// ����
	virtual ~StaticLightsContainer() { Clear(); }

	static StaticLightsContainer* GetInstance() { return Instance(); }

	bool			InsertLight(unsigned short id, LightRes* pLight);
	bool			InsertLight(LightRes* pLight, unsigned short& usOutId);
	bool			RemoveLight(unsigned short key);

	// �ͷ�
	void			Clear();	// �����ͷ�LightResָ��

	const std::map<unsigned short, LightRes*>& GetStaticLights() { return m_mapStaticLights; }

	// �������Щ��ԴӰ��
	bool			GetAffectLights(TObjectInfo* pObject, CWorldTile* pTile, std::vector<LightRes*>& outLights, BOOL bReCalculate = TRUE);
	// ͳ������ܹ�
	void			RetrieveAllObjectsAffectLights(CWorldTile* pTile);

protected:
	bool			RetrieveAffectObjects(unsigned short key, CWorldTile* pTile, std::vector<TObjectInfo*>& outObjects);
	bool			RetrieveAffectObjects(LightRes* pLightRes, CWorldTile* pTile, std::vector<TObjectInfo*>& outObjects);

	std::map<unsigned short, LightRes*> m_mapStaticLights;	// ��󱣴�65535����̬��Դ
	unsigned short	m_usMaxKey;	// ��ǰ���keyֵ
	std::map<TObjectInfo*, std::vector<unsigned short>> m_mapObjectAffectLight;	// �������Щ��̬��Ӱ��
};

#endif /*LIGHT_RES_H*/