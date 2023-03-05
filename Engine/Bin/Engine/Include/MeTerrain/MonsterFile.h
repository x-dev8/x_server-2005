/*******************************************************************************
*  Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	MonsterFile.h
* Date: 	10/06/06
* Desc:		�����ļ����ݸ�ʽ
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __MONSTER_FILE_H__
#define __MONSTER_FILE_H__

////////////////////////////////////////////////////////////////////////////////
#pragma pack(push,1)

////////////////////////////////////////////////////////////////////////////////
struct TMONHead					// ����ͷ
{
	sInt8	segment[4];			// 
	uInt32	version;
	static const int MAPVRSION = 1;
	uInt32  nQuadCount;
};

////////////////////////////////////////////////////////////////////////////////
// ���������¼
struct TMONQuadHead 
{
	float							m_fLeft;			//����������һ������, TopLeft������		
	float							m_fTop;
	float							m_fRight;			//BottomRight������
	float							m_fBottom;
	sInt32							m_monsterNumber;	//�����ڹ���������
	float							m_monsterRadio;		//��λ��%������1.3%���������1.3
	sInt32							m_monsterInterval;	//��λ��ms
	sInt32							m_monsterType[3];
	bool							m_bpointInstanced;	//monster point ʵ��������
	bool							m_bvisible;
};

struct TMONPoint 
{
	float		x;				
	float		y;
};


#pragma pack(pop)

#endif //__MONSTER_FILE_H__