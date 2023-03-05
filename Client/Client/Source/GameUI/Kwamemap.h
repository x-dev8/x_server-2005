#pragma once
#include <vector>
#include <map>

using namespace std;
class CKwamemap
{
public:
	//���͵�·��
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
	typedef vector<STransmitThrough*> vecTransmit;//�����ĵ�ͼID AND NPCID

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

	//����·��
	typedef vector<short> vecThroughid;//�����ĵ�ͼID
	struct SWalkLine
	{
		SWalkLine()
		{
			_vecThroughid.clear();
		}
		vecThroughid _vecThroughid;
	};
	//·�߼���
	struct SKwameMap
	{
		SKwameMap()
		{
			nTargetMap_id = -1;
		}
		int nTargetMap_id;		//Ŀ���ͼID
		SWalkLine _SWalkLine;
		STransmitLine _STransmitLine;
	};
	typedef map<int,SKwameMap*> mapSKwamemap;//Ŀ���NPC���о�����ͼ�ļ���

	struct SKwameMaps
	{
		SKwameMaps()
		{
			nStartMap_id = -1;
		}
		int nStartMap_id;		//��ʼ��ͼID
		mapSKwamemap _mapSKwamemap;
	};
	typedef map<int,SKwameMaps*> mapKwamemaps;//���е�ͼ·�ߵļ���
public:
	CKwamemap(void);
	~CKwamemap(void);

	static CKwamemap& Instance()
	{
		static CKwamemap ckm;
		return ckm;
	}

	bool LoadConfigFile(const char* file_name);

	//����Ŀ���ͼ����ʼ��ͼ,����·���ṹ
	SKwameMap* FindKwameMap(int start_id,int traget_id);

	void Destry();
private:
	mapKwamemaps _mapKwamemaps;
};

#define theKwamemap CKwamemap::Instance()                //ʵ���ӿ�