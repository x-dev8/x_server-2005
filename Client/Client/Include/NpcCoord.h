//读取客户端npc坐标信息 
#ifndef NPC_COORD_H
#define NPC_COORD_H

#include <vector>
#include <map>
#include "tstring.h"

struct NpcCoordInfo
{
	int				_nID;			//npcID
	std::wstring		_szName;		//npc名字
	std::string		_szPinyin;		//拼音
	float			_mapX;			//地图x坐标
	float			_mapY;			//y坐标
	float			_pfMapX;		//地图x坐标
	float			_pfMapY;		//y坐标
	int				_mapId;			//npc所在map
	int				_nType;			//npcType	
	bool			_bNpc;			//用来区分是npc 还是 怪物 因为两个用的图片不一样
    bool			_bPFPossible;	//能否寻路
	bool			_bMask;			//是否挡路
    std::string     _title;         //称号
	float			_scale;			//模型缩放
	int				_modelId;		//模型ID
	bool			_worldShow;		//显示模型
    int             _level;         //等级      added by zhuomeng.hu		[11/8/2010]
	unsigned char	uchCountryID; // 国家
	bool			_miniShow;		//小地图是否显示
	int			_campType; //阵营，主要用于帮会战地图
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
		NONE = 0,	//没有找到
		ONE,		//找到 只有一个
		REPEAT,		//有重复的 
	};
	const NpcCoordInfo*	getNpcCoordInPrimaryMap(const char* szNpcName);
	const NpcCoordInfo*	getNpcCoordInPrimaryMap(int npcId);
	const NpcCoordInfo*	getNpcCoord(const char* szNpcName,int mapId = -1);
	const NpcCoordInfo*	getNpcCoord(int nMapId,int nPFX,int PFY);
	const NpcCoordInfo*	getNpcCoord(int npcId,int mapId = -1);
	const NpcCoordInfo*	getNpcCoordInCurrTile(int nNpcID);
	FINDRESAULT_TYPE	checkNpcRepeat(const char* szNpcName, bool bigmap=false);	//检测是否有同名npc 里面如果没有读取npccoord.xml 则读取之
	void				addNpcHyber(std::string& szString, const char* hyberLeft = "<", const char* hyberRight = ">",NpcCoordInfo** ppInfo = NULL);	//改变szString 如果有npc名字 加入超链接 <.... >
	enum ETextDataType
	{
		eQuestId = 0,
		eMapId
	};
	void				addNpcHyberForText(std::string& szString,ETextDataType eDataType,int nDataValue,int npcId,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName = false,bool bInserHyper = true);	//改变szString 如果有npcID名字 加入超链接 <.... >,
	void				addNpcHyberForTextName(std::string& szString,ETextDataType eDataType,int nDataValue,std::vector<UiCallbackDataBase*>* pCallBackDataArr ,bool bInsertMapName = false,bool bInserHyper = true);	//改变szString 如果有npc名字 加入超链接 <.... >,
	bool				clickHyberToMiniMapForText(const char* szData, UiCallbackDataBase* pBase = NULL);//text控件传回的callback专用


	bool				clickHyberToMiniMap(const char* szData, int mapId = -1);//电击超链接相对小地图的处理 npc指引统一在这里处理

	bool				clickHyberToMiniMap(const NpcCoordInfo* pInfo);//

	const char*			GetNpcName(int nID);		//在客户端slk表格 通过id得到name
	const std::string	FindFirstNpcName(const std::string& text); // 查找text，并返回第一个Npc的名字

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
	// 是否处于半个汉字
	bool IsHalfChar( const char* pStr, unsigned int nOff );

private:
	std::vector<NpcCoordInfo>	_vecNpcCoord;
	bool _initialized; /// 是否已经初始化.

	std::string		_CurHyberName;	//当前指引的名字

	typedef std::multimap< int,const NpcCoordInfo*>                      CoordContainerById;
	typedef CoordContainerById::iterator                              ItrCoordContainerById;    
	typedef std::pair<ItrCoordContainerById, ItrCoordContainerById> CoordPairResultById;
	CoordContainerById			m_mapById;


	typedef std::multimap< std::wstring,const NpcCoordInfo*>                      CoordContainerByName;
	typedef CoordContainerByName::iterator                              ItrCoordContainerByName;    
	typedef std::pair<ItrCoordContainerByName, ItrCoordContainerByName> CoordPairResultByName;
	CoordContainerByName			m_mapByName;

	// 半身像
	bool	m_bDialogPic;
};

#endif