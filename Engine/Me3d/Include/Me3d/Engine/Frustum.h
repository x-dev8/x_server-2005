#pragma once

#include "Me3d/Me3d.h"

//һ������İ�Χ��
struct SBBox
{
	D3DXVECTOR3 vecMin,vecMax;
};

class FrustumEx : public MeCommonAllocObj<FrustumEx>
{
	D3DXVECTOR3 veFrustumEx[8];		// ��׶��8������
	D3DXPLANE	planeFrustumEx[6];    // ��׶��6��ƽ��
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

	//������׶
	void BuildFrustum( D3DXMATRIX &matProj, D3DXMATRIX &matView );
	void BuildFrustum( D3DXVECTOR3 vecMin,D3DXVECTOR3 vecMax );

	//�ж�����
	enum CrossRet
	{
		//������
		cross_exclude
		//����
		,cross_include
		//����
		,cross_cross
	};
	int BBoxCrossFrustum( SBBox & bbox, bool bLeftHand = true);
};
