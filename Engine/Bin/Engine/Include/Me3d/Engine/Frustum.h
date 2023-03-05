#pragma once

#include "Me3d/Me3d.h"

//一个物体的包围盒
struct SBBox
{
	D3DXVECTOR3 vecMin,vecMax;
};

class FrustumEx : public MeCommonAllocObj<FrustumEx>
{
	D3DXVECTOR3 veFrustumEx[8];		// 视锥的8个顶点
	D3DXPLANE	planeFrustumEx[6];    // 视锥的6个平面
public:
	FrustumEx(void);
	~FrustumEx(void);

	bool operator==( FrustumEx & frustum )
	{
		int i;
		for( i = 0 ; i < 8 ; i ++ )
		{
			if( veFrustumEx[i] != frustum.veFrustumEx[i] )
				return false;
		}
		return true;
	}

	//构建视锥
	void BuildFrustum( D3DXMATRIX &matProj, D3DXMATRIX &matView );
	void BuildFrustum( D3DXVECTOR3 vecMin,D3DXVECTOR3 vecMax );

	//判定函数
	enum CrossRet
	{
		//不包含
		cross_exclude
		//包含
		,cross_include
		//交叉
		,cross_cross
	};
	int BBoxCrossFrustum( SBBox & bbox, bool bLeftHand = true);
};
