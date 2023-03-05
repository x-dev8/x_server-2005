// #include "MeTerrain/stdafx.h"
#include <vector>
// #include "MeTerrain/SwType.h"
//#include "atltypes.h"
#include "BinaryAStarPF.h"
#include "SwMap.h"
volatile bool g_bNewPathRequest = false;
BinaryAStarPF::BinaryAStarPF(const unsigned char* pMap, int width, int height, bool bBitValue)
:onClosedList(10),pathBank(NULL)
{
	m_Map = pMap;
	mapWidth = width;
	mapHeight = height;
	openList = (int *)calloc(GetOpenListSize(),sizeof(int));
	openX = (PFINT *)calloc(GetOpenListSize(),sizeof(PFINT));
	openY = (PFINT *)calloc(GetOpenListSize(),sizeof(PFINT));
	Fcost = (PFINT *)calloc(GetOpenListSize(),sizeof(PFINT));
	Hcost = (PFINT *)calloc(GetOpenListSize(),sizeof(PFINT));

	whichList = (PFINT**)calloc((mapWidth+1),sizeof(PFINT*));
	parentX = (PFINT**)calloc((mapWidth+1),sizeof(PFINT*));
	parentY = (PFINT**)calloc((mapWidth+1),sizeof(PFINT*));
	Gcost = (PFINT**)calloc((mapWidth+1),sizeof(PFINT*));

	for (PFINT y = 0 ; y < mapWidth+1; y++)
	{
		whichList[y] = (PFINT*)calloc((mapHeight+1),sizeof(PFINT));
		parentX[y] = (PFINT*)calloc((mapHeight+1),sizeof(PFINT));
		parentY[y] = (PFINT*)calloc((mapHeight+1),sizeof(PFINT));
		Gcost[y] = (PFINT*)calloc((mapHeight+1),sizeof(PFINT));
	}
	// Sets the A* Tilemap append on CDXMap
	m_spaceComplexity = 0;
 	m_bitValue	= bBitValue;
	m_bUseWeight = true;
	InitAstarTileMap();
}

////////////////////////////////////////////////////////////////////////////////

BinaryAStarPF::~BinaryAStarPF()
{
	for (int x = 0 ; x < mapWidth+1; x++)
	{
		free(whichList[x]) ;
		free(parentX[x]) ;
		free(parentY[x]) ;
		free(Gcost[x]) ;
	}
	free(whichList) ;
	free(parentX) ;
	free(parentY) ;
	free(Gcost) ;


	free(openList) ;
	free(openX) ;
	free(openY) ;
	free(Fcost) ;
	free(Hcost) ;

	for (int x = 0 ; x < mapWidth; x++)
	{
		free(walkability[x]) ;
	}
	free(walkability) ;

	free(pathBank);
}

////////////////////////////////////////////////////////////////////////////////
//                             Public SGuildMember Functions                        //
////////////////////////////////////////////////////////////////////////////////

void BinaryAStarPF::InitAstarTileMap()
{
	walkability = (char**)calloc((mapWidth),sizeof(char*));

	for (int x = 0 ; x < mapWidth; x++)
	{
		walkability[x] = (char*)calloc((mapHeight),sizeof(char));
	}
	int nMapIndex = 0;


	for (int i = 0; i < mapHeight; i++)       // fill up the area with current map data
	{                                      // 1 = obstacle
		for (int j = 0; j < mapWidth; j++)    // 0 = free
		{
			if (m_bitValue)
			{
				//				Assert(0 == m_mapWidth%8);
				size_t charIndex = (i*mapWidth + j )>>3;
				walkability[j][i] = (m_Map[charIndex] & (1 << (j%8))) == 0?0:1;
			}
			else
			{
				walkability[j][i] = m_Map[nMapIndex];
			}
			nMapIndex++;                                // reachable
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

bool BinaryAStarPF::NewPath(int start_x, int start_y, int dest_x, int dest_y)
{
	m_spaceComplexity = 0;
	{
		if (start_x <0 || start_x > mapWidth 
			||dest_x <0 || dest_x > mapWidth
			||start_y <0 || start_y > mapHeight 
			||dest_y <0 || dest_y > mapHeight )
		{
			return false;
		}
		int ret = FindPath(start_x,start_y,dest_x,dest_y);
		if( ret == found || ret == nForceBreak)
			isPath = true;
		else
			isPath = false;
		return isPath;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool BinaryAStarPF::ReachedGoal(void) // check it's return value before getting
{                                      // the node entries
	if ( !isPath ) return true;  // this looks a little bit strange
	return ( pathLocation == pathLength );  // but prevents illegal calls of ::PathNextNode()
}

////////////////////////////////////////////////////////////////////////////////

int BinaryAStarPF::TileNum(int x, int y)	// x,y是m_Map的位置索引，所以针对TileMap需要加上列数以及1
{
	return(y*mapWidth+ x); // The reason I add COLS+1 to
}

////////////////////////////////////////////////////////////////////////////////
//								      Private SGuildMember Functions                        //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                               A* Algorithm                                 //
////////////////////////////////////////////////////////////////////////////////

int BinaryAStarPF::FindPath(int startingX, int startingY, int targetX, int targetY)
{
	PFINT onOpenList=0;
	int parentXval=0, parentYval=0,
		a=0, b=0, m=0, u=0, v=0, temp=0, corner=0, numberOfOpenListItems=0,
		addedGCost=0, tempGcost = 0, path = 0,
		tempx, pathX, pathY, cellPosition,
		newOpenListItemID=0;

	//1. Convert location data (in pixels) to coordinates in the walkability array.
	targetX = targetX;
	targetY = targetY;

	//2.Quick Path Checks: Under the some circumstances no path needs to
	//	be generated ...

	//	If starting location and target are in the same location...
	if (startingX == targetX && startingY == targetY && pathLocation > 0)
		return found;
	if (startingX == targetX && startingY == targetY && pathLocation == 0)
		return nonexistent;

	if (g_bNewPathRequest)
	{
		return nForceBreak;
	}
	//	If target square is unwalkable, return that it's a nonexistent path.
	if (walkability[targetX][targetY] == unwalkable)
		goto noPath;

	//3.Reset some variables that need to be cleared
	if (onClosedList > 30000) //reset whichList occasionally
	{
		for (int x = 0; x < mapWidth;x++) {
			for (int y = 0; y < mapHeight;y++)
				whichList [x][y] = 0;
		}
		onClosedList = 10;	
	}
	if (g_bNewPathRequest)
	{
		return nForceBreak;
	}
	onClosedList = onClosedList+2; //changing the values of onOpenList and onClosed list is faster than redimming whichList() array
	onOpenList = onClosedList-1;
	pathLength  = notStarted;//i.e, = 0
	pathLocation  = notStarted;//i.e, = 0
	Gcost[startingX][startingY] = 0; //reset starting square's G value to 0

	//4.Add the starting location to the open list of squares to be checked.
	numberOfOpenListItems = 1;
	openList[1] = 1;//assign it as the top (and currently only) item in the open list, which is maintained as a binary heap (explained below)
	openX[1] = startingX ; openY[1] = startingY;

	//5.Do the following until a path is found or deemed nonexistent.
	do
	{

		//6.If the open list is not empty, take the first cell off of the list.
		//	This is the lowest F cost cell on the open list.
		if (g_bNewPathRequest)
		{
			return nForceBreak;
		}
		if (numberOfOpenListItems != 0)
		{

			//7. Pop the first item off the open list.
			parentXval = openX[openList[1]];
			parentYval = openY[openList[1]]; //record cell coordinates of the item
			whichList[parentXval][parentYval] = onClosedList;//add the item to the closed list

			//	Open List = Binary Heap: Delete this item from the open list, which
			//  is maintained as a binary heap. For more information on binary heaps, see:
			//	http://www.policyalmanac.org/games/binaryHeaps.htm
			numberOfOpenListItems = numberOfOpenListItems - 1;//reduce number of open list items by 1	

			//	Delete the top item in binary heap and reorder the heap, with the lowest F cost item rising to the top.
			openList[1] = openList[numberOfOpenListItems+1];//move the last item in the heap up to slot #1
			v = 1;

			//	Repeat the following until the MeNew item in slot #1 sinks to its proper spot in the heap.
			do
			{
				u = v;		
				if (2*u+1 <= numberOfOpenListItems) //if both children exist
				{
					//Check if the F cost of the parent is greater than each child.
					//Select the lowest of the two children.
					if (Fcost[openList[u]] >= Fcost[openList[2*u]]) 
						v = 2*u;
					if (Fcost[openList[v]] >= Fcost[openList[2*u+1]]) 
						v = 2*u+1;		
				}
				else
				{
					if (2*u <= numberOfOpenListItems) //if only child #1 exists
					{
						//Check if the F cost of the parent is greater than child #1	
						if (Fcost[openList[u]] >= Fcost[openList[2*u]]) 
							v = 2*u;
					}
				}

				if (u != v) //if parent's F is > one of its children, swap them
				{
					temp = openList[u];
					openList[u] = openList[v];
					openList[v] = temp;			
				}
				else
					break; //otherwise, exit loop

			}
			while (1);//reorder the binary heap


			//7.Check the adjacent squares. (Its "children" -- these path children
			//	are similar, conceptually, to the binary heap children mentioned
			//	above, but don't confuse them. They are different. Path children
			//	are portrayed in Demo 1 with grey pointers pointing toward
			//	their parents.) Add these adjacent child squares to the open list
			//	for later consideration if appropriate (see various if statements
			//	below).
			for (b = parentYval-1; b <= parentYval+1; b++){
				if (g_bNewPathRequest)
				{
					return nForceBreak;
				}
				for (a = parentXval-1; a <= parentXval+1; a++){

					//	If not off the map (do this first to avoid array out-of-bounds errors)
					if (a != -1 && b != -1 && a != mapWidth && b != mapHeight){

						//	If not already on the closed list (items on the closed list have
						//	already been considered and can now be ignored).			
						if (whichList[a][b] != onClosedList) { 

							//	If not a wall/obstacle square.
							if (walkability [a][b] != unwalkable) { 

								//	Don't cut across corners
								corner = walkability [a][b];	
								if (a == parentXval-1) 
								{
									if (b == parentYval-1)
									{
										if (walkability[parentXval-1][parentYval] == unwalkable
											|| walkability[parentXval][parentYval-1] == unwalkable) \
											corner = unwalkable;
									}
									else if (b == parentYval+1)
									{
										if (walkability[parentXval][parentYval+1] == unwalkable
											|| walkability[parentXval-1][parentYval] == unwalkable) 
											corner = unwalkable; 
									}
								}
								else if (a == parentXval+1)
								{
									if (b == parentYval-1)
									{
										if (walkability[parentXval][parentYval-1] == unwalkable 
											|| walkability[parentXval+1][parentYval] == unwalkable) 
											corner = unwalkable;
									}
									else if (b == parentYval+1)
									{
										if (walkability[parentXval+1][parentYval] == unwalkable 
											|| walkability[parentXval][parentYval+1] == unwalkable)
											corner = unwalkable; 
									}
								}	
								if (corner != unwalkable) {

									//	If not already on the open list, add it to the open list.			
									if (whichList[a][b] != onOpenList) 
									{	

										//Create a MeNew open list item in the binary heap.
										newOpenListItemID = newOpenListItemID + 1; //each MeNew item has a unique ID #
										if (newOpenListItemID >= GetOpenListSize())
										{
											goto noPath;
										}
										m = numberOfOpenListItems+1;
										openList[m] = newOpenListItemID;//place the MeNew open list item (actually, its ID#) at the bottom of the heap
										openX[newOpenListItemID] = a;
										openY[newOpenListItemID] = b;//record the x and y coordinates of the MeNew item

										//Figure out its G cost
										if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
										{
											//cost of going to diagonal squares
											if (m_bUseWeight)
											{
												switch(corner)
												{
												case SwMap::MAIN_ROAD:
													addedGCost = SwMap::MAIN_ROAD_DIAGONAL;
													break;
												case SwMap::SUB_ROAD:
													addedGCost = SwMap::SUB_ROAD_DIAGONAL;
													break;
												case SwMap::OTHERS:
													addedGCost = SwMap::OTHERS_DIAGONAL;
													break;
												case SwMap::CORNER_AREA:
													addedGCost = SwMap::CORNER_AREA_DIAGONAL;
													break;

												}
											}
											else
											{
												addedGCost = SwMap::MAIN_ROAD_DIAGONAL;
											}
										}
										else	
										{
											//cost of going to non-diagonal squares	
											if (m_bUseWeight)
											{
												addedGCost = corner;	
											}
											else
											{
												addedGCost = SwMap::MAIN_ROAD;
											}
										}
										Gcost[a][b] = Gcost[parentXval][parentYval] + addedGCost;

										//Figure out its H and F costs and parent
										Hcost[openList[m]] = 10*(abs(a - targetX) + abs(b - targetY));
										Fcost[openList[m]] = Gcost[a][b] + Hcost[openList[m]];
										parentX[a][b] = parentXval ; parentY[a][b] = parentYval;	

										//Move the MeNew open list item to the proper place in the binary heap.
										//Starting at the bottom, successively compare to parent items,
										//swapping as needed until the item finds its place in the heap
										//or bubbles all the way to the top (if it has the lowest F cost).
										while (m != 1) //While item hasn't bubbled to the top (m=1)	
										{
											//Check if child's F cost is < parent's F cost. If so, swap them.	
											if (Fcost[openList[m]] <= Fcost[openList[m/2]])
											{
												temp = openList[m/2];
												openList[m/2] = openList[m];
												openList[m] = temp;
												m = m/2;
											}
											else
												break;
										}
										numberOfOpenListItems = numberOfOpenListItems+1;//add one to the number of items in the heap

										//Change whichList to show that the MeNew item is on the open list.
										whichList[a][b] = onOpenList;
									}

									//8.If adjacent cell is already on the open list, check to see if this 
									//	path to that cell from the starting location is a better one. 
									//	If so, change the parent of the cell and its G and F costs.	
									else //If whichList(a,b) = onOpenList
									{

										//Figure out the G cost of this possible MeNew path
										if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
										{
											//cost of going to diagonal squares
											if (m_bUseWeight)
											{
												switch(corner)
												{
												case SwMap::MAIN_ROAD:
													addedGCost = SwMap::MAIN_ROAD_DIAGONAL;
													break;
												case SwMap::SUB_ROAD:
													addedGCost = SwMap::SUB_ROAD_DIAGONAL;
													break;
												case SwMap::OTHERS:
													addedGCost = SwMap::OTHERS_DIAGONAL;
													break;
												case SwMap::CORNER_AREA:
													addedGCost = SwMap::CORNER_AREA_DIAGONAL;
													break;

												}
											}
											else
											{
												addedGCost = SwMap::MAIN_ROAD_DIAGONAL;
											}

										}
										else	
										{
											//cost of going to non-diagonal squares	
											if (m_bUseWeight)
											{
												addedGCost = corner;	
											}
											else
											{
												addedGCost = SwMap::MAIN_ROAD;
											}
										}
										tempGcost = Gcost[parentXval][parentYval] + addedGCost;

										//If this path is shorter (G cost is lower) then change
										//the parent cell, G cost and F cost. 		
										if (tempGcost < Gcost[a][b]) //if G cost is less,
										{
											parentX[a][b] = parentXval; //change the square's parent
											parentY[a][b] = parentYval;
											Gcost[a][b] = tempGcost;//change the G cost			

											//Because changing the G cost also changes the F cost, if
											//the item is on the open list we need to change the item's
											//recorded F cost and its position on the open list to make
											//sure that we maintain a properly ordered open list.
											for (int x = 1; x <= numberOfOpenListItems; x++) //look for the item in the heap
											{
												if (openX[openList[x]] == a && openY[openList[x]] == b) //item found
												{
													Fcost[openList[x]] = Gcost[a][b] + Hcost[openList[x]];//change the F cost

													//See if changing the F score bubbles the item up from it's current location in the heap
													m = x;
													while (m != 1) //While item hasn't bubbled to the top (m=1)	
													{
														//Check if child is < parent. If so, swap them.	
														if (Fcost[openList[m]] < Fcost[openList[m/2]])
														{
															temp = openList[m/2];
															openList[m/2] = openList[m];
															openList[m] = temp;
															m = m/2;
														}
														else
															break;
													} 
													break; //exit for x = loop
												} //If openX(openList(x)) = a
											} //For x = 1 To numberOfOpenListItems
										}//If tempGcost < Gcost(a,b)

									}//else If whichList(a,b) = onOpenList	
								}//If not cutting a corner
							}//If not a wall/obstacle square.
						}//If not already on the closed list 
					}//If not off the map
				}//for (a = parentXval-1; a <= parentXval+1; a++){
			}//for (b = parentYval-1; b <= parentYval+1; b++){

		}//if (numberOfOpenListItems != 0)

		//9.If open list is empty then there is no path.	
		else
		{
			path = nonexistent; break;
		}  

		//If target is added to open list then path has been found.
		if (whichList[targetX][targetY] == onOpenList)
		{
			path = found; break;
		}

	}
	while (1);//Do until path is found or deemed nonexistent

	//10.Save the path if it exists.
	if (path == found)
	{

		//a.Working backwards from the target to the starting location by checking
		//	each cell's parent, figure out the length of the path.
		pathX = targetX; pathY = targetY;
		do
		{
			//Look up the parent of the current cell.	
			tempx = parentX[pathX][pathY];		
			pathY = parentY[pathX][pathY];
			pathX = tempx;

			//Figure out the path length
			pathLength = pathLength + 1;
		}
		while (pathX != startingX || pathY != startingY);
		if (g_bNewPathRequest)
		{
			return nForceBreak;
		}

		//b.Resize the data bank to the right size in bytes
// 		pathBank = (int*) realloc (pathBank,
// 			pathLength*8);
		std::vector<swVec2I> vecPath;
		//c. Now copy the path information over to the databank. Since we are
		//	working backwards from the target to the start location, we copy
		//	the information to the data bank in reverse order. The result is
		//	a properly ordered set of path data, from the first step to the
		//	last.
		pathX = targetX ; pathY = targetY;
		cellPosition = pathLength*2;//start at the end	
		do
		{
			cellPosition = cellPosition - 2;//work backwards 2 integers
			swVec2I point;
			point.x = pathX;
			point.y = pathY;
			vecPath.insert(vecPath.begin(),point);
// 			pathBank [cellPosition] = pathX;
// 			pathBank [cellPosition+1] = pathY;

			//d.Look up the parent of the current cell.	
			tempx = parentX[pathX][pathY];		
			pathY = parentY[pathX][pathY];
			pathX = tempx;

			//e.If we have reached the starting square, exit the loop.	
		}
		while (pathX != startingX || pathY != startingY);	

		//11.Read the first path step into xPath/yPath arrays
// 		ReadPath(pathfinderID,startingX,startingY,1);
		if (g_bNewPathRequest)
		{
			return nForceBreak;
		}

		//12.optimize
		CutShortPath(vecPath,20);

	}
	return path;


	//13.If there is no path to the selected target, set the pathfinder's
	//	xPath and yPath equal to its current location and return that the
	//	path is nonexistent.
noPath:
	return nonexistent;
}

bool BinaryAStarPF::ToggleTile( int x, int y )
{
		if( x < mapWidth && y < mapHeight )
		{
			if( walkability[x][y] != unwalkable )
				walkability[x][y] = unwalkable;
			else
				walkability[x][y] = SwMap::OTHERS;
			return true;
		}
		else
			return false;
}

void BinaryAStarPF::CutShortPath(std::vector <swVec2I>& vecOrig ,int nShortPath)
{
	vecAStarPath.clear();
	if(vecOrig.size() < 3)
	{
		for (int i = 0; i < (int)vecOrig.size(); ++i)
		{
			vecAStarPath.push_back(vecOrig[i]);
		}
		return;
	}
// 	if (m_bUseWeight)
// 	{
// 		RemoveMiddlePoint(vecAStarPath, vecOrig);
// 	}
// 	else
	{
		//remove the middle point in a line
		std::vector <swVec2I> vecFirstStage;
		RemoveMiddlePoint(vecFirstStage, vecOrig);

		//cut the short line
		CutshortLine(vecFirstStage, nShortPath);
	}

	//加入目标点
	vecAStarPath.push_back(vecOrig[vecOrig.size() - 1]);
}

//验证直线是否经过不可走区域
bool BinaryAStarPF::ValidLine( swVec2I& firstPoint,swVec2I& secondPoint, swVec2f* kCollisionPosition)
{
	long x = firstPoint.x ;
	long y = firstPoint.y ;
	if (firstPoint.x == secondPoint.x )
	{
		int deltay = (secondPoint.y - firstPoint.y)/abs(secondPoint.y - firstPoint.y);
		while (y != secondPoint.y + deltay)
		{
			if (walkability[x][y] == unwalkable)
			{
				return false;				
			}
			y += deltay;
		}
		return true;
	}
	if (firstPoint.y == secondPoint.y)
	{
		int deltax = (secondPoint.x - firstPoint.x)/abs(secondPoint.x - firstPoint.x);
		while (x != secondPoint.x + deltax)
		{
			if (walkability[x][y] == unwalkable)
			{
				return false;				
			}
			x += deltax;
		}
		return true;
	}
	//直线斜率

	float t = (firstPoint.y - secondPoint.y)/(float)(firstPoint.x - secondPoint.x);
	//直线方程 y = t*(x - firstPoint.x) + firstPoint.y
#define LineEquation(x0,y0) (t *(x0 -firstPoint.x) + firstPoint.y - y0)

	int deltax = (secondPoint.x - firstPoint.x)/abs(secondPoint.x - firstPoint.x);
	int deltay = (secondPoint.y - firstPoint.y)/abs(secondPoint.y - firstPoint.y);
	while (x != secondPoint.x + deltax)
	{
		while (y != secondPoint.y + deltay)
		{
			if (walkability[x][y] == unwalkable)
			{
				float LeftBottomValue = LineEquation((float)x - 0.5,(float)y - 0.5);
				if (LeftBottomValue * LineEquation((float)x - 0.5,(float)y + 0.5) < 0.001f
					||LeftBottomValue * LineEquation((float)x + 0.5,(float)y - 0.5) < 0.001f
					||LeftBottomValue * LineEquation((float)x + 0.5,(float)y + 0.5) < 0.001f)
					//如果正方形的四个顶点都在直线的同一侧，那么这个正方形与直线不相交,否则，其他三个顶点和一个顶点的积至少有一个小于等于零
				{
					if (kCollisionPosition)
					{
						kCollisionPosition->x = x;
						kCollisionPosition->y = y;
					}
					return false;
				}
			}
			y += deltay;
		}
		x += deltax;
		y = firstPoint.y;
	}
	return true;
#undef LineEquation
}

void BinaryAStarPF::RemoveMiddlePoint( std::vector<swVec2I> &vecFirstStage, std::vector<swVec2I> &vecOrig )
{
	long fNewXDiff = 0;
	long fNewYDiff = 0;

	vecFirstStage.push_back(vecOrig[0]);
	long fXDiff = vecOrig[1].x - vecOrig[0].x;
	long fYDiff = vecOrig[1].y - vecOrig[0].y;
	for (int i = 2; i < (int)vecOrig.size() - 1 ; ++i)
	{
		fNewXDiff = vecOrig[i].x - vecOrig[i - 1].x;
		fNewYDiff = vecOrig[i].y - vecOrig[i - 1].y;
		if (fNewXDiff != fXDiff || fNewYDiff != fYDiff)
		{
			fXDiff = fNewXDiff;
			fYDiff = fNewYDiff;
			vecFirstStage.push_back(vecOrig[i - 1]);
		}
	}
	//如果倒数第二个点被优化掉了，此处要加上。
	if(vecFirstStage.back() != vecOrig[vecOrig.size() - 2])
	{
		vecFirstStage.push_back(vecOrig[vecOrig.size() - 2]);
	}
}

void BinaryAStarPF::CutshortLine( std::vector<swVec2I> &vecFirstStage, int nShortPath )
{
// 	long fNewXDiff = 0;
// 	long fNewYDiff = 0;
	vecAStarPath.push_back(vecFirstStage[0]);
	int index = 2;
	while (index < (int)vecFirstStage.size() )
	{
		int startPoint = index - 2;
		int count = 0;
		int maxNum = 4 + rand()%4;
		while(ValidLine(vecFirstStage[index],vecFirstStage[startPoint]))
		{
			++count;
			if (count == maxNum )
			{
				break;
			}
			if (index == (int)vecFirstStage.size() - 1)
			{
				break;
			}
			++index;
		}
		vecAStarPath.push_back(vecFirstStage[index - 1]);
		++index;
// 		fNewXDiff = vecFirstStage[index].x - vecFirstStage[index - 1].x;
// 		fNewYDiff = vecFirstStage[index].y - vecFirstStage[index - 1].y;
// 		if (fNewXDiff*fNewXDiff + fNewYDiff*fNewYDiff < nShortPath*nShortPath*2 + 1 
// 			&& ValidLine(vecFirstStage[index],vecFirstStage[index - 2]))
// 		{
// 			vecAStarPath.push_back(vecFirstStage[index]);
// 			index += 2;
// 		}
// 		else
// 		{
// 			vecAStarPath.push_back(vecFirstStage[index - 1]);
// 			++index;
// 		}
	}
	//如果最后一个点被跳过了，此处要加上。
	if(vecAStarPath.back() != vecFirstStage[vecFirstStage.size() - 1])
	{
		vecAStarPath.push_back(vecFirstStage[vecFirstStage.size() - 1]);
	}
}

int BinaryAStarPF::GetOpenListSize()
{
	return (mapWidth*mapHeight+2)/2;
}

bool BinaryAStarPF::FindReachablePosOnLine( swVec2I& firstPoint,swVec2I& secondPoint,swVec2f* kReachablePosition /*= NULL*/ )
{
	long x = firstPoint.x ;
	long y = firstPoint.y ;
	if (firstPoint.x == secondPoint.x )
	{
		int deltay = (secondPoint.y - firstPoint.y)/abs(secondPoint.y - firstPoint.y);
		while (y != secondPoint.y + deltay)
		{
			if (walkability[x][y] != unwalkable)
			{
				if (kReachablePosition)
				{
					kReachablePosition->x = x;
					kReachablePosition->y = y;
				}
				return true;				
			}
			y += deltay;
		}
		return false;
	}
	if (firstPoint.y == secondPoint.y)
	{
		int deltax = (secondPoint.x - firstPoint.x)/abs(secondPoint.x - firstPoint.x);
		while (x != secondPoint.x + deltax)
		{
			if (walkability[x][y] != unwalkable)
			{
				if (kReachablePosition)
				{
					kReachablePosition->x = x;
					kReachablePosition->y = y;
				}
				return true;				
			}
			x += deltax;
		}
		return false;
	}
	//直线斜率

	float t = (firstPoint.y - secondPoint.y)/(float)(firstPoint.x - secondPoint.x);
	//直线方程 y = t*(x - firstPoint.x) + firstPoint.y
#define LineEquation(x0,y0) (t *(x0 -firstPoint.x) + firstPoint.y - y0)

	int deltax = (secondPoint.x - firstPoint.x)/abs(secondPoint.x - firstPoint.x);
	int deltay = (secondPoint.y - firstPoint.y)/abs(secondPoint.y - firstPoint.y);
	while (x != secondPoint.x + deltax)
	{
		while (y != secondPoint.y + deltay)
		{
			if (walkability[x][y] != unwalkable)
			{
				float LeftBottomValue = LineEquation((float)x - 0.5,(float)y - 0.5);
				if (LeftBottomValue * LineEquation((float)x - 0.5,(float)y + 0.5) < 0.001f
					||LeftBottomValue * LineEquation((float)x + 0.5,(float)y - 0.5) < 0.001f
					||LeftBottomValue * LineEquation((float)x + 0.5,(float)y + 0.5) < 0.001f)
					//如果正方形的四个顶点都在直线的同一侧，那么这个正方形与直线不相交,否则，其他三个顶点和一个顶点的积至少有一个小于等于零
				{
					if (kReachablePosition)
					{
						kReachablePosition->x = x;
						kReachablePosition->y = y;
					}
					return true;
				}
			}
			y += deltay;
		}
		x += deltax;
		y = firstPoint.y;
	}
	return false;
#undef LineEquation

}