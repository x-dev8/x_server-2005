#pragma once
#include "Dxsdk/D3D9.h"
#include "Dxsdk/D3DX9Math.h"
#include "Me3d/Camera.h"
#include <MeFoundation/MeSmartPointer.h>

class BillboardBase : public MeRefObject
{
public:
	struct Vertex
	{
		D3DXVECTOR3 p;
		DWORD c;
		D3DXVECTOR2 uv;
	};

	BillboardBase() : device_(0), tex_(0), vb_(0), ib_(0)
	{
		D3DXMatrixIdentity(&world_);
	}

	virtual ~BillboardBase()
	{
	}

	virtual DWORD GetFVF() = 0;

	virtual bool CreateVBIB() = 0;

	virtual void Render() = 0;

	virtual HRESULT Create(LPDIRECT3DDEVICE9 device)
	{
		device_ = device;

		HRESULT hr;
		if (FAILED( hr = device->CreateVertexBuffer(
			4*sizeof(Vertex),
			D3DUSAGE_WRITEONLY, GetFVF(),
			D3DPOOL_MANAGED, &vb_, NULL)))
			goto Err_End;

		if (FAILED( hr = device->CreateIndexBuffer(
			6*sizeof(WORD),
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_MANAGED, &ib_, NULL)))
			goto Err_End;

		if( !CreateVBIB() )
			goto Err_End;

		return S_OK;

Err_End:
		Destroy();
		return hr;
	}

	virtual HRESULT Create(LPDIRECT3DDEVICE9 device, Vertex vertices[])
	{
		device_ = device;

		HRESULT hr;
		if (FAILED( hr = device->CreateVertexBuffer(
			4*sizeof(Vertex),
			D3DUSAGE_WRITEONLY, GetFVF(),
			D3DPOOL_MANAGED, &vb_, NULL)))
			goto Err_End;

		if (FAILED( hr = device->CreateIndexBuffer(
			6*sizeof(WORD),
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_MANAGED, &ib_, NULL)))
			goto Err_End;

		Vertex* vs = 0;
		if (FAILED(hr = vb_->Lock(0, 0, (void**)&vs, 0)))
			goto Err_End;
		{
			memcpy(vs, vertices, 4*sizeof(Vertex));
		}
		vb_->Unlock();

		WORD* is = 0;
		if (FAILED(hr = ib_->Lock(0, 0, (void**)&is, 0)))
			goto Err_End;
		{
			is[0] = 0; is[1] = 1; is[2] = 2;
			is[3] = 0; is[4] = 2; is[5] = 3;
		}
		ib_->Unlock();

		return S_OK;

Err_End:
		Destroy();
		return hr;
	}

	virtual HRESULT UpdateVB(Vertex vertices[])
	{
		if (!vb_)
			return S_FALSE;

		HRESULT hr;
		Vertex* vs = 0;
		if (FAILED(hr = vb_->Lock(0, 0, (void**)&vs, 0)))
			return hr;

		memcpy(vs, vertices, 4*sizeof(Vertex));
		vb_->Unlock();
		return hr;
	}

	virtual void Destroy()
	{
		if (vb_)
		{
			vb_->Release();
			vb_ = 0;
		}
		if (ib_)
		{
			ib_->Release();
			ib_ = 0;
		}
	}

	virtual void SetTexture(LPDIRECT3DTEXTURE9 tex)
	{
		tex_ = tex;
	}

	virtual void SetCamera(MeCamera* camera)
	{
		camera_ = camera;
	}

	virtual MeCamera* GetCamera()
	{
		return camera_;
	}

	virtual void SetPosition(const D3DXVECTOR3& pos)
	{
		position_ = pos;
	}

	virtual const D3DXVECTOR3& GetPosition()
	{
		return position_;
	}

	virtual void SetScale(const D3DXVECTOR3& scale)
	{
		scale_ = scale;
	}
	virtual const D3DXMATRIXA16& GetWorld() const { return world_; }

protected:

	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DTEXTURE9 tex_;
	LPDIRECT3DVERTEXBUFFER9 vb_;
	LPDIRECT3DINDEXBUFFER9 ib_;
	D3DXMATRIXA16 world_;
	MeCamera* camera_;

	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
};

MeSmartPointer( BillboardItem );
class BillboardItem : public MeRefObject
{
public:
	bool m_bUseable;
	int m_nIndex;
	BillboardBase* m_pkBillboard;
	BillboardItem() : m_bUseable( true ),
		m_nIndex( -1 ),
		m_pkBillboard( NULL ){}

	~BillboardItem(){
		m_bUseable = true;
		m_nIndex = -1;
		MeDelete m_pkBillboard;
	}
};

/**
@desc: bb的缓冲管理类，不支持多线程。
*/
template< class T >
class BillboardManager: public Singleton< BillboardManager<T> >
{
public:

	/**
	@desc:init & destroy
	*/
	void Initialize( LPDIRECT3DDEVICE9 pkDevice );
	void Destroy();

	/**
	@desc: 不真正删除，重新放回池去使用
	*/
	void DeleteBillboard( BillboardItem* pkItem );

	/**
	@desc: 获得bb，如果没有cache可用，创建新的
	*/
	BillboardItem* CreateBillboard();

public:
	friend Singleton< BillboardManager >;

protected:
	/**
	@desc:
	*/
	BillboardItem* CreateBillboardItem();

protected:
	BillboardManager() : m_pkDevice( 0 ){}

	LPDIRECT3DDEVICE9 m_pkDevice;

	/// 根据实际值扩大这个数量
	static int ms_cnBillboardCachCount;
	
	typedef std::vector<BillboardItemPtr> Billboards;
	typedef Billboards::iterator BillboardsIter;
	Billboards m_Boards;

	typedef std::vector<int> UseableIndexs;
	typedef UseableIndexs::iterator UseableIndexsIter;
	UseableIndexs m_UseableIndexs;

};

#include "BillboardManager.h"