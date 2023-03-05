/*******************************************************************************
*  Copyright ShenWang 2008 - All Rights Reserved
*
* File: 	MonsterFile.h
* Date: 	10/06/06
* Desc:		怪物文件数据格式
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
struct TMONHead					// 公共头
{
	sInt8	segment[4];			// 
	uInt32	version;
	static const int MAPVRSION = 1;
	uInt32  nQuadCount;
};

////////////////////////////////////////////////////////////////////////////////
// 怪物区域记录
struct TMONQuadHead 
{
	float							m_fLeft;			//怪物区域是一个矩形, TopLeft的坐标		
	float							m_fTop;
	float							m_fRight;			//BottomRight的坐标
	float							m_fBottom;
	sInt32							m_monsterNumber;	//区域内怪物点的数量
	float							m_monsterRadio;		//单位是%，比如1.3%，这里就是1.3
	sInt32							m_monsterInterval;	//单位是ms
	sInt32							m_monsterType[3];
	bool							m_bpointInstanced;	//monster point 实例化了吗？
	bool							m_bvisible;
};

struct TMONPoint 
{
	float		x;				
	float		y;
};


#pragma pack(pop)

#endif //__MONSTER_FILE_H__