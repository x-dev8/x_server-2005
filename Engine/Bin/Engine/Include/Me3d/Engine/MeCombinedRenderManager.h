#pragma once

#include "Me3d/Engine/MeRenderObject.h"
#include "MeUtility/Singleton.h"
struct SEmitterVertex;

class MeCombinedAdapter 
{
public:
	virtual						~MeCombinedAdapter(){}
	virtual		void			OnDeviceLost() = 0;
	virtual		bool			IsMyCombinedType(SortRenderable* pRenderable) = 0;
	virtual     void			RenderAndReset(MeRenderObjectPtr pRenderObject) = 0;
	virtual     void			CombinedRender(SortRenderable* pRenderable,bool bPost) = 0;
	static const int			m_nMaxVertexCount = 1024 * 4;
};

class MeEffectAdapter : public MeCombinedAdapter
{
public:
	MeEffectAdapter();
	~MeEffectAdapter();
	virtual		void			OnDeviceLost();
	virtual		bool			IsMyCombinedType(SortRenderable* pRenderable) ;
	virtual     void			RenderAndReset(MeRenderObjectPtr pRenderObject) ;
	virtual     void			CombinedRender(SortRenderable* pRenderable,bool bPost) ;
protected:
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	int							m_VertexCount;
	int							m_FaceCount;
	SEmitterVertex*				m_VertexMem;
	SEmitterVertex*				m_aVertexMem;
	MeRenderObjectPtr			m_CurrEffectObject;
	bool						m_bUseVB;
	void						_DoEffectRender();
};

class MeBillboardAdapter : public MeCombinedAdapter
{
public:
	MeBillboardAdapter();
	~MeBillboardAdapter();
	virtual		void			OnDeviceLost();
	virtual		bool			IsMyCombinedType(SortRenderable* pRenderable) ;
	virtual     void			RenderAndReset(MeRenderObjectPtr pRenderObject) ;
	virtual     void			CombinedRender(SortRenderable* pRenderable,bool bPost) ;
protected:
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	LPDIRECT3DVERTEXBUFFER9		m_NormalsBuffer;
	LPDIRECT3DVERTEXBUFFER9		m_DiffusesBuffer;
	LPDIRECT3DVERTEXBUFFER9		m_UvsBuffer;

// 	LPDIRECT3DINDEXBUFFER9			m_pIB;

	int							m_VertexCount;
	int							m_FaceCount;
	Vector*						m_VertexMem;
	Vector*						m_NormalMem;
	DWORD*						m_DiffuseMem;
	Vector2*					m_UvsMem;
// 	unsigned short*				m_shIBMem;
	MeRenderObjectPtr			m_CurrEffectObject;
	void						_DoEffectRender();
};


class MeCombinedRenderManager : public Singleton<MeCombinedRenderManager>
{
public:
	MeCombinedRenderManager();
	virtual ~MeCombinedRenderManager();

	void			OnDeviceLost();

	bool						TryCombinedRender(SortRenderable* pRenderable,bool bPost);

	void						DoCombinedRender()
	{
		if (!m_AdapterArr.empty())
		{
			m_AdapterArr[0]->RenderAndReset(NULL);
			m_AdapterArr[1]->RenderAndReset(NULL);
		}
	}

	void						AddAdapter(MeCombinedAdapter* pAdapter)
	{
		m_AdapterArr.push_back(pAdapter); 
	}
protected:
	std::vector<MeCombinedAdapter*>				m_AdapterArr;
	bool										m_bInitialize;
	void										Initialize();
};