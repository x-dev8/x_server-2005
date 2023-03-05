#pragma once
#include <vector>
#include <map>

using namespace std;
class CKwamemap
{
public:
	//传送的路线
	struct STransmitThrough
	{
		STransmitThrough()
		{
			mapid = -1;
			npc_id = -1;
		}
		short mapid;
		int npc_id;
	};
	typedef vector<STransmitThrough*> vecTransmit;//经过的地图ID AND NPCID

	struct STransmitLine
	{
		STransmitLine()
		{
			npc_id = -1;
			_vecTransmit.clear();
		}
		int npc_id;
		vecTransmit _vecTransmit;
	};

	//行走路线
	typedef vector<short> vecThroughid;//经过的地图ID
	struct SWalkLine
	{
		SWalkLine()
		{
			_vecThroughid.clear();
		}
		vecThroughid _vecThroughid;
	};
	//路线集合
	struct SKwameMap
	{
		SKwameMap()
		{
			nTargetMap_id = -1;
		}
		int nTargetMap_id;		//目标地图ID
		SWalkLine _SWalkLine;
		STransmitLine _STransmitLine;
	};
	typedef map<int,SKwameMap*> mapSKwamemap;//目标和NPC还有经过地图的集合

	struct SKwameMaps
	{
		SKwameMaps()
		{
			nStartMap_id = -1;
		}
		int nStartMap_id;		//开始地图ID
		mapSKwamemap _mapSKwamemap;
	};
	typedef map<int,SKwameMaps*> mapKwamemaps;//所有地图路线的集合
public:
	CKwamemap(void);
	~CKwamemap(void);

	static CKwamemap& Instance()
	{
		static CKwamemap ckm;
		return ckm;
	}

	bool LoadConfigFile(const char* file_name);

	//根据目标地图和起始地图,查找路径结构
	SKwameMap* FindKwameMap(int start_id,int traget_id);

	void Destry();
private:
	mapKwamemaps _mapKwamemaps;
};

#define theKwamemap CKwamemap::Instance()                //实例接口