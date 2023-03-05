#include "HeightMapData.h"
#include "TileDataMapHeader.h"
#include <stdio.h>
#include <string>
#include "filepacket/packet_interface.h"
const float error_height = -100000;

//------------------------------------------------------------------
CHeightMapData::CHeightMapData():
m_ptMapHeader(NULL),
m_ptCharData(NULL),
m_fRate(0),
m_fHeight(0) {}

CHeightMapData::~CHeightMapData()
{
	DestoryData();
}

//------------------------------------------------------------------
void CHeightMapData::DestoryData()
{
	if (m_ptMapHeader != NULL)
	{
		delete m_ptMapHeader;
		m_ptMapHeader = NULL;
	}

	if (m_ptCharData != NULL)
	{
		delete [] m_ptCharData;
		m_ptCharData = NULL;
	}
}

//------------------------------------------------------------------
bool CHeightMapData::ReadDataFromFile(const char* pszFileName)
{
	f_Handle* stream = packet_namespace::w_fopen( pszFileName, "rb");

	if( stream == NULL)
	{
		return false;
	}

	m_ptMapHeader = new TileHeightMapHeader;
	std::memset(m_ptMapHeader, 0, sizeof(TileHeightMapHeader));
	packet_namespace::w_fread(m_ptMapHeader, sizeof(TileHeightMapHeader), 1, stream);

	m_ptCharData = new unsigned char[m_ptMapHeader->width * m_ptMapHeader->height];
	packet_namespace::w_fread(m_ptCharData, sizeof(unsigned char)* m_ptMapHeader->width * m_ptMapHeader->height, 1, stream);

	packet_namespace::w_fclose( stream);

	m_fRate = (double)m_ptMapHeader->rate_M / (double)m_ptMapHeader->rate_R;
	m_fHeight = (m_ptMapHeader->maxHeight - m_ptMapHeader->minHeight) / 255;
	return true;
}

//------------------------------------------------------------------
float CHeightMapData::GetZbyXY(size_t x_, size_t y_, NineDirection_Key key_)
{
	if (!m_ptMapHeader || !m_ptCharData)
	{
		return error_height;
	}
	
	if (key_ == key_northWest)
	{
		return GetZbyXYHelp(x_ - 1, y_ - 1);
	}
	if (key_ == key_north)
	{
		return GetZbyXYHelp(x_, y_ - 1);
	}
	if (key_ == key_northEast)
	{
		return GetZbyXYHelp(x_ + 1, y_ - 1);
	}
	if (key_ == key_west)
	{
		return GetZbyXYHelp(x_ - 1, y_);
	}
	if (key_ == key_middle)
	{
		return GetZbyXYHelp(x_, y_);
	}
	if (key_ == key_east)
	{
		return GetZbyXYHelp(x_ + 1, y_);
	}
	if (key_ == key_southWest)
	{
		return GetZbyXYHelp(x_ - 1, y_ + 1);
	}
	if (key_ == key_south)
	{
		return GetZbyXYHelp(x_, y_ + 1);
	}
	if (key_ == key_southEast)
	{
		return GetZbyXYHelp(x_ + 1, y_ + 1);
	}

	return error_height;
}

//-------------------------------------------------------------------------
//原本的地图中(0,0)代表左下，而输入中(0,0)代表左上，需要注意倒置一下
float CHeightMapData::GetZbyXYHelp(size_t x_, size_t y_)//服务器用
{
	float fHeight_ = m_ptMapHeader->maxHeight - m_ptMapHeader->minHeight;

	if (x_ < 0 || x_ >= m_ptMapHeader->width || y_ < 0 || y_ >= m_ptMapHeader->height)
	{
		return error_height;
	}
	
	return static_cast<float>(m_ptCharData[(m_ptMapHeader->height - y_ - 1) * m_ptMapHeader->width + x_]) * fHeight_ / 255.0f + m_ptMapHeader->minHeight; 	
}

float CHeightMapData::GetHeightbyXY(float xCoord, float yCoord)//传入真实坐标
{
	if (!m_ptMapHeader || !m_ptCharData)
	{
		return error_height;
	}

	size_t x = xCoord * m_fRate;
	size_t y = yCoord * m_fRate;

	if ( x >= m_ptMapHeader->width || y >= m_ptMapHeader->height)
	{
		return error_height;
	}

	return m_ptCharData[y * m_ptMapHeader->width + x] * m_fHeight + m_ptMapHeader->minHeight;
}
