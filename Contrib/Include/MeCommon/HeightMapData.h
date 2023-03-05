/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	HeightMapData.h
* Create: 	10/27/07
* Desc:		��ȡ�߳�ͼ������
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
	˵����GetZbyXY()
	���룺��ͼ��x,y���꼰����
	�������ͼ�ĸ߶�����
	*/
	float GetZbyXY(size_t x_, size_t y_, NineDirection_Key key_ = key_middle);
	float GetHeightbyXY(float x, float y);
	
	//member data
	TileHeightMapHeader* m_ptMapHeader;	//mapͷ�ļ�
	unsigned char* m_ptCharData;	//����߶�ͼ�������飬0-255

private:
	float m_fRate;
	float m_fHeight;

private:
	void DestoryData();
	float GetZbyXYHelp(size_t x_, size_t y_);
};

#endif