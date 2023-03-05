/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MeshLightmapColorData.h
* Create: 	02/16/2011
* Desc:		模型灯光图的颜色数据，每个子模型一个ColorData
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MESH_LIGHTMAP_COLORDATA_H__
#define _MESH_LIGHTMAP_COLORDATA_H__
#include "MeUtility/Singleton.h"

#define INVALID_LIGHTMAP_DATA -1

class MeshLightmapColorData: public Singleton<MeshLightmapColorData>
{
public:
	struct LMColorData
	{
		sInt32		m_nColorDataResolution;	// 分辨率
		NiColorB*	m_pColorData;			// 大小m_nColorDataResolution*m_nColorDataResolution*sizeof(NiColorB)
	};

	// 构造
	MeshLightmapColorData(): m_nColorMapLastNo(-1) { m_mapColorData.clear(); }
	
	// 析构
	virtual ~MeshLightmapColorData() { Clear(); }

	static MeshLightmapColorData* GetInstance() { return Instance(); }


	// 加载地图读取
	sInt32 PushColorData(sInt32 id, LMColorData* pData, bool bReplace = false)
	{
		if( !pData )
			return -1;

		if( id < 0 )	// 新数据
		{
			++m_nColorMapLastNo;
			id = m_nColorMapLastNo;
		}

		std::map<sInt32, LMColorData*>::iterator iter = m_mapColorData.find(id);
		if( iter == m_mapColorData.end() )
			m_mapColorData.insert(std::map<sInt32, LMColorData*>::value_type(id, pData));
		else	// id重复
		{
			if( bReplace )
			{
				LMColorData* pOldData = iter->second;
				if( pOldData->m_pColorData )
					delete[] pOldData->m_pColorData;
				delete pOldData;

				m_mapColorData.erase(iter);	
				m_mapColorData.insert(std::map<sInt32, LMColorData*>::value_type(id, pData));
			}
			else
			{
				char msg[256] = {0};
				sprintf_s(msg, sizeof(msg)-1, "WARNING: Mesh Lightmap Color Data duplicated id: %d .\n", id);
				OutputDebugString(msg);
				return -1;
			}
		}
		if( id > m_nColorMapLastNo )
			m_nColorMapLastNo = id;

		return id;
	}

	// 负责释放LMColorData指针和LMColorData::m_pColorData
	void Clear()
	{
		std::map<sInt32, LMColorData*>::iterator iter = m_mapColorData.begin();
		for( ; iter != m_mapColorData.end(); ++iter )
		{
			if( iter->second )
			{
				LMColorData* pData = iter->second;
				if( pData->m_pColorData )
					delete[] pData->m_pColorData;
				delete pData;
			}
		}
		m_mapColorData.clear();
		m_nColorMapLastNo = -1;
	}

	const std::map<sInt32, LMColorData*>& GetColorDataMap() { return m_mapColorData; }

protected:
	sInt32							m_nColorMapLastNo;	// m_mapColorData最大key值
	std::map<sInt32, LMColorData*>	m_mapColorData;
};

#endif /* _MESH_LIGHTMAP_COLORDATA_H__ */