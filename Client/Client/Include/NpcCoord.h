//��ȡ�ͻ���npc������Ϣ 
#ifndef NPC_COORD_H
#define NPC_COORD_H

#include <vector>
#include <map>
#include "tstring.h"

struct NpcCoordInfo
{
	int				_nID;			//npcID
	std::wstring		_szName;		//npc����
	std::string		_szPinyin;		//ƴ��
	float			_mapX;			//��ͼx����
	float			_mapY;			//y����
	float			_pfMapX;		//��ͼx����
	float			_pfMapY;		//y����
	int				_mapId;			//npc����map
	int				_nType;			//npcType	
	bool			_bNpc;			//����������npc ���� ���� ��Ϊ�����õ�ͼƬ��һ��
    bool			_bPFPossible;	//�ܷ�Ѱ·
	bool			_bMask;			//�Ƿ�·
    std::string     _title;         //�ƺ�
	float			_scale;			//ģ������
	int				_modelId;		//ģ��ID
	bool			_worldShow;		//��ʾģ��
    int             _level;         //�ȼ�      added by zhuomeng.hu		[11/8/2010]
	unsigned char	uchCountryID; // ����
	bool			_miniShow;		//С��ͼ�Ƿ���ʾ
	int			_campType; //��Ӫ����Ҫ���ڰ��ս��ͼ
};
struct UiCallbackDataBase;
class CWorldTile;
class NpcCoord
{
public:
	NpcCoord(): _initialized(false), m_bDialogPic(false) {}

	~NpcCoord();

public:
	static NpcCoord* getInstance()
	{
		static NpcCoord _npcCoord;
		return &_npcCoord;
	}

	enum FINDRESAULT_TYPE
	{
		NONE = 0,	//û���ҵ�
		ONE,		//�ҵ� ֻ��һ��
		REPEAT,		//���ظ��� 
	};
	const NpcCoordInfo*	getNpcCoordInPrimaryMap(const char* szNpcName);
	const NpcCoordInfo*	getNpcCoordInPrimaryMap(int npcId);
	const NpcCoordInfo*	getNpcCoord(const char* szNpcName,int mapId = -1);
	const NpcCoordInfo*	getNpcCoord(int nMapId,int nPFX,int PFY);
	const NpcCoordInfo*	getNpcCoord(int npcId,int mapId = -1);
	const NpcCoordInfo*	getNpcCoordInCurrTile(int nNpcID);
	FINDRESAULT_TYPE	checkNpcRepeat(const char* szNpcName, bool bigmap=false);	//����Ƿ���ͬ��npc �������û�ж�ȡnpccoord.xml ���ȡ֮
	void				addNpcHyber(std::string& szString, const char* hyberLeft = "<", const char* hyberRight = ">",NpcCoordInfo** ppInfo = NULL);	//�ı�szString �����npc���� ���볬���� <.... >
	enum ETextDataType
	{
		eQuestId = 0,
		eMapId
	};
	void				addNpcHyberForText(std::string& szString,ETextDataType eDataType,int nDataValue,int npcId,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName = false,bool bInserHyper = true);	//�ı�szString �����npcID���� ���볬���� <.... >,
	void				addNpcHyberForTextName(std::string& szString,ETextDataType eDataType,int nDataValue,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName = false,bool bInserHyper = true);	//�ı�szString �����npc���� ���볬���� <.... >,
	bool				clickHyberToMiniMapForText(const char* szData, UiCallbackDataBase* pBase = NULL);//text�ؼ����ص�callbackר��


	bool				clickHyberToMiniMap(const char* szData, int mapId = -1);//������������С��ͼ�Ĵ��� npcָ��ͳһ�����ﴦ��

	bool				clickHyberToMiniMap(const NpcCoordInfo* pInfo);//

	const char*			GetNpcName(int nID);		//�ڿͻ���slk��� ͨ��id�õ�name
	const std::string	FindFirstNpcName(const std::string& text); // ����text�������ص�һ��Npc������

	static	bool		lt_sort(NpcCoordInfo s1, NpcCoordInfo s2)
	{
		if (s1._szName.length() == s2._szName.length())
		{
			return s1._bPFPossible - s2._bPFPossible>0;
		}
		return (s1._szName.length() > s2._szName.length());
	}

	std::vector<NpcCoordInfo>& getNpcVec();
	bool			hasName( const char* name );
	const char*		getCurHyberName() const 
	{
		return _CurHyberName.c_str();
	}
	void				MarkNpcOnReachableMap(CWorldTile* pTile);
	void				GetNpcListInMap(int mapId, std::vector<int>* pNpcList);
	static int			RetriveMapIdFromQuest( int nQuestId, const std::string& content );
	static int			GetMyCountryMapId( int nMapId, bool isNpc );

	void load();

	char*		GetNpcDialogPicture(const char* headpic, char* dialogpic, short headid);

private:
	// �Ƿ��ڰ������
	bool IsHalfChar( const char* pStr, unsigned int nOff );

private:
	std::vector<NpcCoordInfo>	_vecNpcCoord;
	bool _initialized; /// �Ƿ��Ѿ���ʼ��.

	std::string		_CurHyberName;	//��ǰָ��������

	typedef std::multimap< int,const NpcCoordInfo*>                      CoordContainerById;
	typedef CoordContainerById::iterator                              ItrCoordContainerById;    
	typedef std::pair<ItrCoordContainerById, ItrCoordContainerById> CoordPairResultById;
	CoordContainerById			m_mapById;


	typedef std::multimap< std::wstring,const NpcCoordInfo*>                      CoordContainerByName;
	typedef CoordContainerByName::iterator                              ItrCoordContainerByName;    
	typedef std::pair<ItrCoordContainerByName, ItrCoordContainerByName> CoordPairResultByName;
	CoordContainerByName			m_mapByName;

	// ������
	bool	m_bDialogPic;
};

#endif