#ifndef __POSITION_INFO_H__
#define __POSITION_INFO_H__

#include <string>
#include <map>


#define thePositionInfo PositionInfo::Instance()   //ʵ���ӿ�


#define PositionErrorId 0xffff

#define File_Success 0		//���سɹ�
#define File_Error 1		//�����ļ�����
#define Param_Error 2		//��������	
#define Attribute_Error 3	//�ֶ����Դ���

class PositionInfo
{
/// typedef and structure.
public:
    struct Position
    {  
		enum
		{
			Type_Null = 0,		//������
			Type_Npc,			//npc
			Type_Monster,		//����
			Type_Collection,	//�ɼ���
			Type_Waypoint,		//Ѱ·��

			Type_End,
		};

        Position() : type(0), name(""), id(-1), x(0.0f), y(0.0f), mapId(PositionErrorId), isShow(0) {}
        
		int			type;	//����
		int			id;		//id
        std::string name;    //����
		float       x;		
        float       y;
        int         mapId;   //��ͼID;
        bool        isShow;  //�Ƿ���ʾ
		bool        needMount;//�Ƿ���Ҫ��
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

	Position *GetPositionById(int id);   //id����
	Position *GetPositionByName(std::string name);  //���ֲ���

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


