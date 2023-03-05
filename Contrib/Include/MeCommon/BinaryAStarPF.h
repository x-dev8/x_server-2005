#ifndef __BINARY_ASTAR_PF_H__
#define __BINARY_ASTAR_PF_H__
#define TILESIZE	1	// 每个格子宽高都为1
typedef short PFINT;
struct						swVec2f
{
	float  x;
	float  y;

	swVec2f()
		:x(0.f),y(0.f)
	{

	}
	swVec2f(float fx,float fy)
		:x(fx),y(fy)
	{
	}
	inline const swVec2f& operator= (const swVec2f& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
};

struct						swVec2I
{
	int    x;
	int    y;

	inline const swVec2I& operator= (const swVec2I& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	inline bool operator== (const swVec2I& v)
	{
		return(x==v.x && y==v.y);
	}
	inline bool operator!= (const swVec2I& v)
	{
		return(!(*this==v));
	}
};

class BinaryAStarPF 
{
private:

// 	struct NODE {     // node structure
// 		bool bInOpen;	// 是否在OPEN链表里
// 		long Fcost, Hcost;
// 		long Gcost;		// 已走步数的代价用float表示，因为走斜45°方向时代价为sqrt(2)，否则为1
// 		long delta_g;	// 从parent到当前node的代价，为1或sqrt(2)
// 		PFINT x, y;
// 		PFINT NodeNum;
// 		NODE *Parent;
// 		NODE *Child[8]; // a node may have upto 8+(NULL) children.
// 		NODE *NextNode;  // for filing purposes
// 	};
// 	NODE *OPEN;    // the node list pointers
// 	NODE *CLOSED;
// 	NODE *PATH; // pointer to the best path
// 
// 	struct STACK {      // the stack structure
// 		NODE *NodePtr;
// 		STACK *NextStackPtr;
// 	};
// 	STACK *Stack;
// 
 	bool isPath;   
// 
// 	PFINT ROWS,			// tilemap data members, need to be initialisize
// 		COLS,			// with current map's width and height
// 		TOTAL_TILES;	// to allocate memory for the
// 	unsigned char *walkability;		// pointer to the A* own tilemap data array
	char** walkability ;
	int GetOpenListSize();
	int* openList; //1 dimensional array holding ID# of open list items
	PFINT** whichList;  //2 dimensional array used to record 
	// 		whether a cell is on the open list or on the closed list.
	PFINT* openX; //1d array stores the x location of an item on the open list
	PFINT* openY; //1d array stores the y location of an item on the open list
	PFINT** parentX; //2d array to store parent of each cell (x)
	PFINT** parentY; //2d array to store parent of each cell (y)
	PFINT* Fcost;	//1d array to store F cost of a cell on the open list
	PFINT** Gcost; 	//2d array to store G cost for each cell.
	PFINT* Hcost;	//1d array to store H cost of a cell on the open list
	
	
	
	PFINT pathLength;     //stores length of the found path for critter
	PFINT pathLocation;   //stores current position along the chosen path for critter		
	PFINT* pathBank ;


public:

	// Modify only these 3 public member functions to support Your favorite Map
	BinaryAStarPF(const unsigned char* pMap, int width, int height, bool bBitValue = false);
	~BinaryAStarPF();
	void InitAstarTileMap();                

	char ** GetTileMap()  { return (char **)walkability; }
	bool IsReachable(int block_x,int block_y)  { return walkability[block_x][block_y]; }
	bool NewPath(int start_x, int start_y, int dest_x, int dest_y);  // start pos: start_x, start_y; dest pos: dest_x, dest_y
	bool ValidLine(swVec2I& firstPoint,swVec2I& secondPoint,swVec2f* kCollisionPosition = NULL);
	bool FindReachablePosOnLine(swVec2I& firstPoint,swVec2I& secondPoint,swVec2f* kReachablePosition = NULL);
	// Must be called and be true
	// before getting the node entries. It frees the lists,
	// calls ::Findpath() and returns true if path is accessible

	bool ReachedGoal(void); // Call and check this function before using these 3 following
	void PathNextNode(void) { ++pathLocation; }
 	PFINT NodeGetX(void)      { return pathBank[pathLocation*2-2]; }
 	PFINT NodeGetY(void)      { return pathBank[pathLocation*2-1]; }

	// other usefull functions (do not change them they are used by the A* algorithm)
	int GetSpaceComplexity() {return m_spaceComplexity;}
	bool ToggleTile(int x, int y);	// 转换x, y所在Tile的值
	std::vector <swVec2I>&		GetPath(){return vecAStarPath;}
	bool GetUseWeight() const { return m_bUseWeight; }
	void SetUseWeight(bool val) { m_bUseWeight = val; }
	int GetMapWidth() const { return mapWidth; }
	int GetMapHeight() const { return mapHeight; }
private:

	void CutShortPath(std::vector <swVec2I>& vecPath,int nShortPath);

	void CutshortLine( std::vector<swVec2I> &vecFirstStage, int nShortPath );
	void RemoveMiddlePoint( std::vector<swVec2I> &vecFirstStage, std::vector<swVec2I> &vecOrig );
	int FindPath(int start_x, int start_y, int dest_x, int dest_y);

	int TileNum(int x, int y); // returns tilenum

	const unsigned char* m_Map;
	int mapWidth;
	int mapHeight;
	int m_spaceComplexity;		// 空间复杂度，即所有insert到OPEN链表的node个数
	PFINT onClosedList ;
	static const int notfinished = 0, notStarted = 0;// path-related constants
	static const int found = 1, nonexistent = 2; 
	static const int walkable = 1, unwalkable = 0;// walkability array constants
	static const int nForceBreak = 3;
	std::vector <swVec2I> vecAStarPath;
// 	NODE* m_FreeNodeList;		// 预分配好所有需要的节点，需要使用时再获取
// 	int	m_FreeNodeIndex;		// 指向m_FreeNodeList的下标

 	bool m_bitValue;
	bool m_bUseWeight;
};
extern volatile  bool g_bNewPathRequest;
#endif //__BINARY_ASTAR_PF_H__