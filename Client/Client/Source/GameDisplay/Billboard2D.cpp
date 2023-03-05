#include "Billboard2D.h"
#include "wsCamera.h"

void Billboard2D::Render()
{
	_UpdateMatrix();

	D3DXMATRIX mat;
	D3DXVECTOR2 v2Pos( position_.x, position_.y );
	D3DXMatrixTransformation2D( &mat, 0, 0, 0, 0, 0, &v2Pos );

	if (getwsCamera()->GetLock45DegreeCameraMode())
	{
		sprite_->Begin( 0 );
	}
	else
	{
		RendererDx* pRendererDx = ( RendererDx* )GetEngine()->GetRenderer();
		D3DXMATRIXA16 mView, mWorld;
		mView = getwsCamera()->GetMeCamera()->GetViewMatrix();
		mWorld = pRendererDx->GetWorldMatrix();
		sprite_->SetWorldViewRH( &mWorld, &mView );

		mat._43 = position_.z;

		sprite_->Begin( D3DXSPRITE_SORT_DEPTH_BACKTOFRONT );
	}
	sprite_->SetTransform( &mat );

	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	sprite_->Draw( tex_, NULL, NULL, NULL, 0xffffffff );

	sprite_->End();
}