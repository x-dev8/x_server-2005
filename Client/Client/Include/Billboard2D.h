#pragma once
#include "BillboardBase.h"
#include "RTTFont.h"
#include "Font3DManager.h"

MeSmartPointer( Billboard2D );
class Billboard2D : public BillboardBase
{
public:
	enum 
	{
		FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1
	};

	virtual DWORD GetFVF(){ return FVF; };

	virtual HRESULT Create(LPDIRECT3DDEVICE9 device)
	{
		device_ = device;
		sprite_ = Font3DManager::Instance()->GetD3DXSprite();
		return S_OK;
	}

	virtual bool CreateVBIB(){ return S_OK; }

	virtual void Render();

	virtual void SetPosition(const D3DXVECTOR3& pos)
	{
		position_ = pos;
		position_.x = position_.x - (float)( RTTFont::RTT_TEX_WIDTH / 2 );
		position_.y = position_.y;// - (float)( RTTFont::RTT_TEX_WIDTH / 2 );
	}

protected:
	void _UpdateMatrix()
	{
	}

	ID3DXSprite* sprite_;
};

