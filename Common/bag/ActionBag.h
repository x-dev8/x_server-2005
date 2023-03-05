//
//#pragma once
//#include "GlobalDef.h"
//#include "..\ItemDetail.h"
//
//class CActionBag
//{
//public:
//	CActionBag( );
//	~CActionBag( );
//
//	//��ʼ��
//	void CreateFromData( SCharAction *pBaseAction, 
//						 SCharAction *pCommunityAction,
//						 SCharAction *pSocialAction,
//						 int iBagSize );
//
//	//���Ӷ���
//	bool AddAction( unsigned short ustActionID, short stIndex = -1 );
//
//	//�Ƴ�����
//	bool RemoveAction( unsigned short ustActionID );
//	bool RemoveAction( short stWhichActionBag, short stIndex );
//
//	//��ȡ��λ����
//	int  FindNullActionOffSet( short stWhichActionBag );
//
//	//��ȡָ������,��������Ϣ
//	bool GetAction( short stWhichActionBag, short stIndex, SCharAction *pAction );
//
//	//���ָ������,��������Ϣ
//	bool ClearAction( short stWhichActionBag, short stIndex );
//
//	//��ȡָ������,������״��...�жϸ�λ������
//	bool IsHaveAction( short stWhichActionBag, short stIndex );
//
//	int GetBaseActionNum( ) 
//	{
//		return m_iBaseActionCount;
//	}
//
//	int GetCommunityActionNum( ) 
//	{
//		return m_iCommunityActionCount;
//	} 
//
//	int GetSocialActionNum( )
//	{
//		return m_iSocialActionCount;
//	}
//
//private:
//	int  m_iBagSize;
//
//	int  m_iBaseActionCount;
//	int	 m_iCommunityActionCount;
//	int  m_iSocialActionCount;
//
//	SCharAction *m_pBaseAction;
//	SCharAction *m_pCommunityAction;
//	SCharAction *m_pSocialAction;
//};
