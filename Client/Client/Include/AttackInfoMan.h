/*
ԭ��:������ֵ���ӳٴ�����Ѫ�ȵ��������вſۣ���ʾ�ܺ���	
���յ�������Ϣ
����AttackInfo��AttackInfo������
���빥������������
��ɫ����
�򵥵Ľ�������ѭ��
ֻ��������
��ɫ�˳���MsgExit,MsgExitMySight��
��ɫ�л����������У��߼������Ѿ���ʧ
������ж������У���֤AttackInfo��������ƽ���Ч����
�л���ͼ			
�������б����AttackInfo
������еĽ�ɫ�����ǳ��⣩
���������������
*/

#pragma  once

#include <map>
#include "MapContainer.h"
struct SAttackInfo;
class CAttackInfoMan
{
	CMapContainer<SAttackInfo*,SAttackInfo*> m_map;
public:
	CAttackInfoMan(void);
	~CAttackInfoMan( void );

	SAttackInfo* AddAttackInfo( SAttackInfo & attackinfo );
	//�������AddAttackInfo���ص�
	void DeleteAttackInfo( SAttackInfo *pAttackInfo );
	//����л���ͼʱ����ִ�б��������AttackInfo
	void ExcuteAllAttackInfo( void );

	//�˳���Ϸʱ����
	void ClearAll( void );
};
extern CAttackInfoMan theAttackInfoMan;