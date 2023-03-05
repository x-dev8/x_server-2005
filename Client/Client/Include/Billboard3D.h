#pragma once
#include "BillboardBase.h"


MeSmartPointer( Billboard3D );
class Billboard3D : public BillboardBase
{
public:
	enum 
	{
		FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1
	};


	virtual DWORD GetFVF(){ return FVF; };

	virtual bool CreateVBIB()
	{
		Vertex* vs = 0;
		HRESULT hr = 0;
		if (FAILED(hr = vb_->Lock(0, 0, (void**)&vs, 0)))
			return false ;
		{
			vs[0].p = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
			vs[0].c = 0xffffffff;
			vs[0].uv = D3DXVECTOR2(0.0f, 0.0f);

			vs[1].p = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
			vs[1].c = 0xffffffff;
			vs[1].uv = D3DXVECTOR2(1.0f, 0.0f);

			vs[2].p = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
			vs[2].c = 0xffffffff;
			vs[2].uv = D3DXVECTOR2(1.0f, 1.0f);

			vs[3].p = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
			vs[3].c = 0xffffffff;
			vs[3].uv = D3DXVECTOR2(0.0f, 1.0f);
		}
		vb_->Unlock();

		WORD* is = 0;
		if (FAILED(hr = ib_->Lock(0, 0, (void**)&is, 0)))
			return false;
		{
			is[0] = 0; is[1] = 1; is[2] = 2;
			is[3] = 0; is[4] = 2; is[5] = 3;
		}
		ib_->Unlock();

		return true;
	}

    virtual void Render()
    {
        _UpdateMatrix();

        device_->SetTransform(D3DTS_WORLD, &world_);
        device_->SetTexture(0, tex_);
        device_->SetStreamSource(0, vb_, 0, sizeof(Vertex));
        device_->SetIndices(ib_);
        //device_->SetFVF( GetFVF() );
		device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		device_->SetTransform(D3DTS_WORLD, &matWorld );
    }

protected:
    void _UpdateMatrix()
    {
        D3DXMATRIXA16 s, iv(camera_->GetViewMatrix());
        iv._41 = iv._42 = iv._43 =
            iv._14 = iv._24 = iv._34 = 0.0f;
        iv._44 = 1.0f;
        //D3DXMatrixInverse(&iv, 0, &view);
        D3DXMatrixTranspose(&iv, &iv);
        D3DXMatrixScaling(&s, scale_.x, scale_.y, scale_.z);
        D3DXMatrixTranslation(&world_, position_.x, position_.y, position_.z);

        world_ = s * iv * world_;
    }
};

