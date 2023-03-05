/********************************************************************
	Filename: 	StageDataLoader.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_STAGEDATALOADER_H__
#define __COMMON_STAGEDATALOADER_H__

#pragma once

#include <assert.h>
#include "IOXMLObject.h"

typedef unsigned char BYTE;

class CMapAreaManager;
class CMonsterConfig;

class CStageDataLoader : public IOXMLObjectInstance
{
public:
    CStageDataLoader();
    virtual ~CStageDataLoader();

    virtual bool loadXMLSettings( const char *path  );
    virtual bool loadXMLSettings( XMLElement *element );
    virtual bool exportXMLSettings( std::ofstream &xmlFile  );
    virtual bool exportXMLSettings( const char* xmlPath );

    virtual void loadXML( XMLElement* element, int nNumber ){};
    virtual void exportXML( CStageDataLoader* pStageDataLoader, int i ){};

    void GetValue( std::string& strValue, XMLElement* element );
    void GetValue( long &lValue, XMLElement* element );
    void GetValue( float &fValue, XMLElement* element );
    void GetValue( int &nValue, XMLElement* element );
    void GetValue( char* cValue, XMLElement* element, int nLength );
    void GetValue( const char* cValue, XMLElement* element );
    void GetValue( bool &bValue, XMLElement* element );
    void GetValue( BYTE &byValue, XMLElement* element );
    void GetValue( short &stValue, XMLElement* element );

    void NewMapAreaManager();
    void NewMonsterConfig();
    void SetMapAreaManager( CMapAreaManager* pMapAreaManager );
    void SetMonsterConfig( CMonsterConfig* pMonsterConfig );

    CMapAreaManager* GetMapAreaManager();
    CMonsterConfig* GetMonsterConfig();

    void Clear();

private:
    CMapAreaManager* m_pMapAreaManager;
    CMonsterConfig*  m_pMonsterConfig;
    bool m_bMapAreaManagerNew;
    bool m_bMonsterConfigNew;
};

#endif // __COMMON_STAGEDATALOADER_H__
