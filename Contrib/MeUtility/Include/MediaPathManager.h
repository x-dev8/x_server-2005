#ifndef MEDIAPATHMANAGER_H
#define MEDIAPATHMANAGER_H

#include "Logger.h"
#include <vector>

using namespace std;

struct NameToPath
{
	NameToPath()
	{
		szName = "NULL";
		szPath = "NULL";
	}
	string szName;
	string szPath;	
};

class MediaPathManager
{
public:
	enum
	{
		eMediaPathMap = 0,
		eMediaPathTerrain,
		eMediaWorldPath,
		eMediaPathUI,		
		eMediaPathData,
		eMediaPathNpcHead,
		eMediaSlkPath,
		eMediaPathMax
	};
public:
	static int          getPathCount();
	static bool         registerPath(XMLElement *MediaPathNode);
	static bool         registerPath(NameToPath *path);
	static void         printAllPaths();
	static const char*  lookUpMediaPath(const char *path);
	static const char*	GetMediaPath(int nIdx);
private:
	static vector<NameToPath> pathStack;
};

#endif