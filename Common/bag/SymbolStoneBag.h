//
//#pragma once
//#include "GlobalDef.h"
//#include "..\ItemDetail.h"
//
//class CSkillBag;
//class CSymbolStoneBag
//{
//public:
//	CSymbolStoneBag( );
//	~CSymbolStoneBag( );
//
//	//��ʼ��
//	void SetSkillBagPoint( CSkillBag *pSkillBag );
//	void CreateFromData( SCharSymbolStone *pStoneData, int iBagSize );
//
//	//���÷�ʯ(�����ó����Զ�ָ��λ��,���Ҳ����ָ��λ��)
//	bool AddStone( unsigned short ustStoneID, short stIndex=-1 );
//	//�Ƴ���ʯ(ֻ�ܴ�������,��Ϊ��ʯ�п���һ��)
//	bool RemoveStone( short stStoneIndex );
//	//��һ���յ�λ��
//	int  FindNullStoneOffSet( );
//
//	//��ȡָ�������ķ�ʯ��Ϣ
//	bool GetStone( short stIndex, SCharSymbolStone *pStone );
//	//��ȡָ��������״��...�жϸ�λ������
//	bool IsHaveStone( short stIndex );
//	//���ָ�������ķ�ʯ
//	bool ClearStone( short stIndex );
//
//	//���ӵ�������
//	void AttachToSkill( short stStoneIndex, short stSkillIndex );	
//	//�Ӽ�������
//	void DetachFromSkill( short stStoneIndex );						
//
//	//��Ч��ʯ�ĸ���
//	int GetStoneNum( )
//	{
//		return m_iBagSize;
//	}
//
//	//��ȡָ��������ʯ��ID
//	unsigned short GetStoneIDByIndex( int iIndex )
//	{
//		return m_pStoneData[iIndex].ustStoneID;
//	}
//
//private:
//	//�����������Ŀ
//	int	 m_iBagSize;
//
//	//��ʯ������ָ��
//	SCharSymbolStone *m_pStoneData;
//	
//	//���ܱ�����ָ��(��ȡ�����������)
//	CSkillBag *m_pSkillBag;
//};
