/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	TileDataMapHeader.h
* Create: 	10/27/07
* Desc:		map头文件
* Author:	yanli
*******************************************************************************/
#ifndef __COMMON_TILEDATAMAPHEADER_H__
#define __COMMON_TILEDATAMAPHEADER_H__

// Map文件头
struct TileDataMapHeader
{
	unsigned long version;				//地图版本号
	unsigned long size;					//文件大小,可以做为文件是否损坏的标识,暂时不做文件crc的较验,因为没什么必要
	unsigned long rate_R;
	unsigned long rate_M;				//实际坐标对地图坐标的比率	如果是 1:2 的含义代表着实际的坐标1 10*10的场景 用20*20的地图来表示
	unsigned long width;			//地图宽度, 并非坐标
	unsigned long height;				//地图高度, 并非坐标
};

struct TileHeightMapHeader : public TileDataMapHeader
{
	float minHeight;				//地图高度最小值  yanli
	float maxHeight;				//地图高度最大值 yanli
};

#endif