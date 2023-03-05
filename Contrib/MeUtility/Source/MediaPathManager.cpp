#include "MediaPathManager.h"
#include "FuncPerformanceLog.h"

vector<NameToPath> MediaPathManager::pathStack;

const char*		MediaPathManager::GetMediaPath(int nIdx)
{
	guardfunc
	if( nIdx >= 0 && nIdx < getPathCount() )
		return pathStack[nIdx].szPath.c_str();
	return NULL;
	unguard;
}

const char* MediaPathManager::lookUpMediaPath(const char *path)
{
	guardfunc
  if(!path)
    return NULL;

  ifstream test;
  string   buffer;
	guard(test1);
  test.open(path);

  if(test.is_open())
  {
    test.close();
    return path;
  }
	unguard;
  size_t count = pathStack.size();
  size_t size = 256;
  char   *pathBuffer = new char[size];
  memset(pathBuffer, NULL, size);

  guard(test2);
  for(size_t i = 0; i < count; i++)
  {
    buffer  = pathStack[i].szPath;
    buffer += path;

    test.open(buffer.data());
    if(test.is_open())
    {
      strncpy_s(pathBuffer, size, buffer.data(), size-1);
      test.close();
      return pathBuffer;
    }
  }
  unguard;
  deleteArray(pathBuffer);
  return NULL;
  unguard;
}

bool MediaPathManager::registerPath( XMLElement *mediaPathNode)
{
	guardfunc
  XMLElement *child;
  NameToPath path;
  if(mediaPathNode)
  if(mediaPathNode->getName() == "MediaFolder")
  if(child = mediaPathNode->getChildByName("path"))
	  path.szPath = child->getValuec();
  if( child = mediaPathNode->getChildByName("name"))
	  path.szName = child->getValuec();

  return  registerPath( &path );
	unguard;
  //return false;
}

bool MediaPathManager::registerPath(NameToPath *p2 )
{
	guardfunc
  if(!p2 || !p2->szPath.size() )
    return Logger::writeErrorLog("Failed to register data path -> NULL");

  for(size_t i = 0; i < pathStack.size(); i++)
    if( (pathStack[i].szName == p2->szName) && (pathStack[i].szPath == p2->szPath ) )
      return true;

  string stringBuffer = p2->szPath;

  Logger::writeInfoLog(string("Registering data path -> ") + p2->szPath);
  pathStack.push_back(*p2);
  return true;
  unguard;
}

int MediaPathManager::getPathCount()
{
	guardfunc
  return int(pathStack.size());
  unguard;
}

void  MediaPathManager::printAllPaths()
{
	guardfunc
  cout << "List of registred Media Paths: \n";

  for(size_t i = 0; i < pathStack.size(); i++){
    if(pathStack[i].szPath.c_str()){
      cout << int(i) << "-" << pathStack[i].szPath << endl;
    }
  }

  cout << endl;
  unguard;
}