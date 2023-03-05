#include "GameStageDataCenter.h"

GameStageDataCenter& GetGameStageDataCenter()
{
    static GameStageDataCenter instance;
    return instance;
}

GameStageDataCenter::~GameStageDataCenter()
{
    CSALocker lock(_lock);
    ItrStageDataLoaderContainer it    = _stageDataLoaders.begin();
    ItrStageDataLoaderContainer itEnd = _stageDataLoaders.end();
    for ( ; it!=itEnd; ++it )
    {
        CStageDataLoader* pStageDataLoader = it->second;
        if ( pStageDataLoader == NULL)
        { continue;}
        
        delete pStageDataLoader;
    }
    _stageDataLoaders.clear();
}

long GameStageDataCenter::InitStageDataLoader( uint32 mapId , const std::string& strFileName )
{
    CSALocker lock(_lock);
    CStageDataLoader* pStageDataLoader = new CStageDataLoader;
    if ( pStageDataLoader == NULL )
    { return ER_NewNormalFail;}

    pStageDataLoader->Clear();

    bool bResult = pStageDataLoader->loadXMLSettings( strFileName.c_str() );
    if ( !bResult )
    { 
        delete pStageDataLoader;
        return ER_Failed; 
    }

    bResult = _stageDataLoaders.insert( StageDataLoaderContainer::value_type( mapId, pStageDataLoader )).second;
    if ( !bResult)
    { 
        delete pStageDataLoader;
        return ER_Failed; 
    }

    return ER_Success;
}

CStageDataLoader* GameStageDataCenter::GetStageDataLoader( uint32 mapId )
{
    CSALocker lock(_lock);
    ItrStageDataLoaderContainer it = _stageDataLoaders.find( mapId );
    if ( it != _stageDataLoaders.end() )
    { return it->second; }
    
    return NULL;
}