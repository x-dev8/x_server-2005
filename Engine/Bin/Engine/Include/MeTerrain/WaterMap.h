/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WaterMap.h
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __WATER_MAP_H__
#define __WATER_MAP_H__

class CxImage;
class CToolWorld;
struct THeightResult;
////////////////////////////////////////////////////////////////////////////////
class CWaterMap 
{
public:	
					CWaterMap(const char* fileName);
					~CWaterMap();

	void			Reset();
		
	
	bool			IsInWater(float x,float y);
	
protected:

	int						GameCoordToMap( float x) { return (int)( x/m_fRate);}


	int						m_nWidth;		// ��ͼ�Ŀ��
	int						m_nHeight;		// ��ͼ�ĸ߶�
	float					m_fRate;		// ��ͼ�����ű���
	unsigned char*					m_pkMapData;			
};







#endif //__WATER_MAP_H__