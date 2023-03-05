#ifndef MODELSLK_20031112_INC
#define MODELSLK_20031112_INC

#include <Map>
#include <vector>
#include "MapContainer.h"

class CNpcVisualSlk
{
public:
	struct Record
	{
		int		nModelId;
		char	szPath[MAX_PATH];
		Record():nModelId(-1){szPath[0] = 0;}
	};
public:
	BOOL	Init( const char* pszFilename );
	CNpcVisualSlk();
	~CNpcVisualSlk();
	Record* Find( int nModelID );
protected:
	CMapContainer<int,Record*> m_records;
};
class CModelSlk
{
public:	
	struct SModelInfo
	{
		unsigned short	ustModelID;
		std::string		szModelFile;		
	};

	CModelSlk()
	{
	}

	~CModelSlk()
	{
	}

	bool LoadFromSlk( char *pszFile );
	CModelSlk::SModelInfo *FindByModelID( int iModelID );
	char *GetModelFildByModelID( int iModelID );
private:
	typedef std::map< int,SModelInfo* > mapModel;
	mapModel m_mapModel;

	void AddToMap( SModelInfo *pInfo );
};
extern CModelSlk theModelSlk;
extern CNpcVisualSlk theNpcVisual;
#endif