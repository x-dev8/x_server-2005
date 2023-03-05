#pragma once
#include <Windows.h>
#include <deque>
#include "Dxsdk/D3DX9Math.h"
#include "GlobalDef.h"

class CCameraStuntManager
{
public:
	CCameraStuntManager(void);
	~CCameraStuntManager(void);

public:
	enum LookatPosOffsetType
	{
		LPOT_NORMAL = 0,
		LPOT_HORIZONTAL,
		LPOT_VERTICAL,
		LPOT_VIEWDIR //�ӷ�������
	};

private:
	D3DXVECTOR3		m_vTheRolePos;					//��Ϸ�����ǵ�����
	D3DXVECTOR3     m_vViewDir;                     //��Ϸ�еĹ۲췽��
	float           m_fDistance;                    //������ɫ�ľ���
	float           m_fLastDistance;                //�ϴ�������ɫ�ľ���
	DWORD           m_dwStartMovingCameraTime;      //��ʼ�ƶ������ʱ��
	DWORD           m_dwMovingElapse;               //�ƶ����

public:
	void			UpdateRolePos( D3DXVECTOR3 vRolePos,D3DXVECTOR3 vDir);
	void            RecordLastDistance(float fLen){m_fLastDistance = fLen;}
	void            ProcessSmothMove(float &fLen);
	int             GetDistance(){return m_fDistance;}
	int             GetLookType(){return m_nLookatPosOffsetType;}
	bool            IsCameraMoving();

private:
	int				m_nLookatPosOffsetType;			//�ۿ���ƫ������
	float			m_fLookatPosMaxOffset;			//�ۿ�������ƫ��
	float			m_fLookatPosMinOffset;			//�ۿ������Сƫ��
	float			m_fLookatPosShakeCorrect;		//�ۿ����������
	DWORD			m_dwLookatPosStartShakeTime;	//�ۿ��㿪ʼ�񶯵�ʱ��
	DWORD			m_dwLookatPosShakeKeepTime;		//�ۿ����񶯵�ά��ʱ��

public:
	//�õ��ۿ����ƫ��
	D3DXVECTOR3		GetLookatPosOffset();

	//��ʼ�����
	void			StartRandShake( D3DXVECTOR3 vShakePos,		//�𶯵�
		float fMaxShakeWaveRange,	//��Ӱ�������ķ�Χ
		float fMinShakeWaveRange,	//��Ӱ����ǿ�ķ�Χ
		float fMaxShakeRange,		//������
		float fMinShakeRange,		//��С���
		DWORD dwShakeKeepTime,		//��ά��ʱ��
		int	  nShakeType = LPOT_NORMAL,int nCurZoom = 0 );//������

	void			StartRandShake(	float fMaxShakeRange,		//������
		float fMinShakeRange,		//��С���
		DWORD dwShakeKeepTime,		//��ά��ʱ��
		int	  nShakeType = LPOT_NORMAL,int nCurZoom = 0 );//������
};