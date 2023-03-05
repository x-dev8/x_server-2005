/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	HeightMapData.h
* Create: 	10/27/07
* Desc:		读取高程图数据类
* Author:	yanli
*******************************************************************************/
#ifndef __COMMON_HEIGHTMAPDATA_H__
#define __COMMON_HEIGHTMAPDATA_H__

struct TileHeightMapHeader;

enum NineDirection_Key
{
	key_northWest = 0,
	key_north,
	key_northEast,
	key_west,
	key_middle,
	key_east,
	key_southWest,
	key_south,
	key_southEast,
};

class CHeightMapData
{
public:
	CHeightMapData();
	~CHeightMapData();

	//member function
	bool ReadDataFromFile(const char* pszFileName);
	
	/*	
	说明：GetZbyXY()
	输入：地图的x,y坐标及方向
	输出：地图的高度数据
	*/
	float GetZbyXY(size_t x_, size_t y_, NineDirection_Key key_ = key_middle);
	float GetHeightbyXY(float x, float y);
	
	//member data
	TileHeightMapHeader* m_ptMapHeader;	//map头文件
	unsigned char* m_ptCharData;	//保存高度图数据数组，0-255

private:
	float m_fRate;
	float m_fHeight;

private:
	void DestoryData();
	float GetZbyXYHelp(size_t x_, size_t y_);
};

#endif