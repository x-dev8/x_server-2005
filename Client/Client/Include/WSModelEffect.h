#pragma once
#include "Me3d/Effect/ModelEffect.h"
class MexAnimCtrl;
class CMexEffectCtrl;
/*
	һ��instance���ڻ�������Ⱦһ�Σ�
	���е�instance������ͬ�����ԣ�����̳���ͬ���ԣ�
*/
class CWSModelEffect:public CModelEffect
{
public:

public:
	CWSModelEffect(void);

public:
	virtual ~CWSModelEffect(void);

public:
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );//keep
	virtual void Release();//keep
	virtual void	Start();//keep
	virtual void	TryStart();//keep
	void			SetModelID(int val);

protected:
	int	m_nModelID ;
};

class CWSModelEffectReader 
{
public:
	static void PreLoadWSModelEffectSetting(bool isCipher);
};