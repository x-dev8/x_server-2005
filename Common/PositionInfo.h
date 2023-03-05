#ifndef __POSITION_INFO_H__
#define __POSITION_INFO_H__

#include <string>
#include <map>


#define thePositionInfo PositionInfo::Instance()   //实例接口


#define PositionErrorId 0xffff

#define File_Success 0		//加载成功
#define File_Error 1		//加载文件错误
#define Param_Error 2		//参数错误	
#define Attribute_Error 3	//字段属性错误

class PositionInfo
{
/// typedef and structure.
public:
    struct Position
    {  
		enum
		{
			Type_Null = 0,		//无类型
			Type_Npc,			//npc
			Type_Monster,		//怪物
			Type_Collection,	//采集怪
			Type_Waypoint,		//寻路点

			Type_End,
		};

        Position() : type(0), name(""), id(-1), x(0.0f), y(0.0f), mapId(PositionErrorId), isShow(0) {}
        
		int			type;	//类型
		int			id;		//id
        std::string name;    //名称
		float       x;		
        float       y;
        int         mapId;   //地图ID;
        bool        isShow;  //是否显示
		bool        needMount;//是否需要马
		int		campType;

        void operator=(const Position& pos)
        {
            type = pos.type;
            name = pos.name;
            id   = pos.id;
            x    = pos.x;
            y    = pos.y;
            mapId = pos.mapId;
            isShow = pos.isShow;
			campType = pos.campType;
        }
    };
    
    typedef std::map<int, Position> Positions;
    typedef Positions::iterator PositionsIter;

/// Constructor.
protected:
	PositionInfo() { positions_.clear(); }
    
public:
	inline static PositionInfo& Instance()
	{
		static PositionInfo s_xPositionInfo;

		return s_xPositionInfo;
	}

/// Function.
public:
	~PositionInfo() {}

    int LoadConfig( const char* path ); 

	void InsertPos(const Position &pos_);

	Position *GetPositionById(int id);   //id查找
	Position *GetPositionByName(std::string name);  //名字查找

	bool DeletePositionById(int id);
	bool DeletePositionByName(std::string name);

	inline int GetPositonCount() { return static_cast<int>(positions_.size()); }

    
    int SaveConfig( const char* path ) { return File_Success; }

/// Attribute
public:
    Positions positions_;
    
};

#endif // __POSITION_INFO_H__

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


