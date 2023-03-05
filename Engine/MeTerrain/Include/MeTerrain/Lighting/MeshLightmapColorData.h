/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MeshLightmapColorData.h
* Create: 	02/16/2011
* Desc:		ģ�͵ƹ�ͼ����ɫ���ݣ�ÿ����ģ��һ��ColorData
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
		sInt32		m_nColorDataResolution;	// �ֱ���
		NiColorB*	m_pColorData;			// ��Сm_nColorDataResolution*m_nColorDataResolution*sizeof(NiColorB)
	};

	// ����
	MeshLightmapColorData(): m_nColorMapLastNo(-1) { m_mapColorData.clear(); }
	
	// ����
	virtual ~MeshLightmapColorData() { Clear(); }

	static MeshLightmapColorData* GetInstance() { return Instance(); }


	// ���ص�ͼ��ȡ
	sInt32 PushColorData(sInt32 id, LMColorData* pData, bool bReplace = false)
	{
		if( !pData )
			return -1;

		if( id < 0 )	// ������
		{
			++m_nColorMapLastNo;
			id = m_nColorMapLastNo;
		}

		std::map<sInt32, LMColorData*>::iterator iter = m_mapColorData.find(id);
		if( iter == m_mapColorData.end() )
			m_mapColorData.insert(std::map<sInt32, LMColorData*>::value_type(id, pData));
		else	// id�ظ�
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

	// �����ͷ�LMColorDataָ���LMColorData::m_pColorData
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
	sInt32							m_nColorMapLastNo;	// m_mapColorData���keyֵ
	std::map<sInt32, LMColorData*>	m_mapColorData;
};

#endif /* _MESH_LIGHTMAP_COLORDATA_H__ */