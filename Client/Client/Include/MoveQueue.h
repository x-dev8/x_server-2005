#pragma once
#include <windows.h>
#include <deque>
#include "Dxsdk/D3DX9Math.h"


class CPlayer;
// class CWalkPath;
class CPlayerAnim;

class CMoveQueue
{
public:
	enum enumMove
	{
		//M_CONTINUEMOVING				// �����ƶ�
		M_KEEPMOVINGTOPOS				// �����ƶ�״̬�ƶ���Ŀ���
		,M_MOVINGTOPOS					// �ƶ���Ŀ���ͣ����
		,M_MOVINGTOLOCKTARGET			// �ƶ�������Ŀ��

		//,M_PLAYERMOVINGTOPOS			// ����ƶ���ĳ��
		,M_PLAYERMOVINGTYPE				// ����ƶ���ʽ�ı仯
		,M_PLAYERMOVINGDIRANDTYPE		// ��ҷ�����ƶ���ʽ�ı仯

		,M_PLAYERKEEPMOVINGPOS			// ��ҳ����ƶ�ͨ��ĳ��
		,M_PLAYERKEEPMOVINGPOSANDDIR	// �����ĳ��������ƶ�ͨ��ĳ��
		,M_PLAYERPOS					// ���ԭ�ز��������ڵ�
		,M_PLAYERDIR					// ���ԭ�ز������泯����
		,M_PLAYERPOSANDDIR				// ���ԭ�ز��������ڵ���泯����
        ,M_PLAYERKEEPMOVINGPOSANDDIR_FINDPATH // �����ĳ��������ƶ�ͨ��ĳ�㣬��Ҫ�Զ�Ѱ·
	};

	struct SMove
	{
		// ����
		short stType;

		// �Ƿ��Ѿ�ʧЧ,,��bSkip = TRUE��ʾ����Ϊ��Ч�������ΪΪ�յ�
		bool bSkip;

		// 0ʱ��ִ�У�������ִ�У�
		bool bZeroTimeExec;

		// ָ�����б�ţ����ڼ򵥵���ʱ������ʾ
		// ������ָ��һ������ֵ�ϴ�����ǰ��ָ��
		DWORD dwSerialNo;

		//��������ʱ��
		DWORD dwPushTime;

		int nTargetID; // Ŀ���ID
		float fKeepDistance; // ��Ŀ�걣�ֵľ���

		short shX;// Ŀ���X
		short shY;// Ŀ���Y

		D3DXVECTOR3 vTargetPos; // Ŀ���
		D3DXVECTOR3 vDir; // ��ǰ�ĳ���

		short shMovingType;// �ƶ�����

		SMove():bSkip(false),
			bZeroTimeExec(false){}
	};

private:
	std::deque<SMove> m_veMove;
	BOOL Push_Move( SMove &move );

public:
	CMoveQueue(void);
	~CMoveQueue(void);

	int Size();
	void Clear();

	BOOL PopNextMove( SMove &move );
	BOOL Push_KeepMovingToPos( float x, float y, float dx, float dy );

	BOOL Push_MovingToPos( float x, float y, float dx, float dy );
	BOOL Push_MovingToTarget( int nTargetID, float fKeepDistance );

	BOOL Push_PlayerMovingType( short shMovingType);
	BOOL Push_PlayerMovingDirAndType( D3DXVECTOR3 vDir, short shMovingType );

	// ��ұ����ƶ�״̬ͨ��ĳ��
	BOOL PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos );
	// �����ĳ���򱣳��ƶ�״̬ͨ��ĳ��
	// WOWֻ���Ե����˻ῴ����������ԭ�ش�ת����������Ϊ�����ƶ��л�����ʲô:���ڳ�ʲô����ת����Ϣ��
	// ������Ϊ���ƶ�ͨ����һ���㣬��ͨ��������·�����ò�ֵ�������һ�����ߣ������ղ����¸�Ҫͨ���ĵ��
	// ��Ȼ�����·�����ƶ����ͳ�����ԭ�ش�ת�����
	BOOL PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );
	// �����ĳ���򱣳��ƶ�״̬ͨ��ĳ�㣬�Զ�Ѱ·
    BOOL PushPlayerKeepMovingPassPos_TargetDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );

	// ���ԭ�ز��������ڵ�
	BOOL PushPlayerPos( D3DXVECTOR3 vPos );
	// ���ԭ�ز������泯����
	BOOL PushPlayerDir( D3DXVECTOR3 vDir );
	// ���ԭ�ز��������ڵ���泯����
	BOOL PushPlayerPosAndDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );
};