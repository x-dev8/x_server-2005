#include "NpcManager.h"
#include "SlkReader/SlkReader.h"
// #include "GameWorld.h"
// #include "ShareData.h"

NpcManager& GetNpcManager()
{
	static NpcManager s;
	return s;
}

NpcManager::NpcManager()
{
}

NpcManager::~NpcManager()
{
}
NpcManager::SNpc* NpcManager::FindNpcByStaticId(int id)
{
    if (id <= 0)
    {
        return NULL;
    }
    for(NpcInfoContainerItr iter = _NpcInfos.begin();iter != _NpcInfos.end();++iter)
    {
        if (iter->nID == id)
        {
            return &(*iter);
        }
    }
    return NULL;
}
NpcManager::SNpc* NpcManager::FindNpcByDynamicId(int id)
{
    if (id <= 0)
    {
        return NULL;
    }
    for(NpcInfoContainerItr iter = _NpcInfos.begin();iter != _NpcInfos.end();++iter)
    {
        if (iter->nDynamicid == id)
        {
            return &(*iter);
        }
    }
    return NULL;
}
NpcManager::SNpc* NpcManager::FindNpcByNpcName(const char* NpcName)
{
    if (NpcName == NULL||strlen(NpcName) == 0)
    {
        return NULL;
    }
    for(NpcInfoContainerItr iter = _NpcInfos.begin();iter != _NpcInfos.end();++iter)
    {
        if (iter->strName.compare(NpcName)==0)
        {
            return &(*iter);
        }
    }
    return NULL;
}
bool NpcManager::LoadNpcInfo( const char* szFileName )
{
	_NpcInfos.clear();

	CSlkReader reader;
	int iRet = 0;
	int iRow = 3;
    
	if( !reader.ReadFromFile( szFileName ) )
        return false;
	
    std::string strFileName;
    std::string strNpcName, strImgPath;
    std::string strWalkPath = "";
    int			nNpcId_for_storage = -1; //为仓库而建一个字段
    int			nLevel = 1;
    int			nModelId = 0;
    int			nMapId = 0;
    float		fX,fY = 0.0f;
    float		fDir = 0;
    float		fDirX = 0;
    float		fDirY = 0;
    int			nChangeDir, nShadow = 0;
    int			nNpcType = 0;
    INT			nMask = 0;
    
    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;
        if( !reader.GetIntFieldByName( "NpcID", nNpcId_for_storage ) )
        {
            return false;
        }

        if( !reader.GetStringFieldByName( "NpcName", strNpcName ) )
        {
            return false;
        }

        if( !reader.GetIntFieldByName( "Level", nLevel ) )
        {
            return false;
        }

        if( !reader.GetIntFieldByName( "ModelId", nModelId ) )
        {
            nModelId = -1;
        }

        if( !reader.GetIntFieldByName( "MapId", nMapId ) )
        {
            return false;
        }

        if( !reader.GetFloatFieldByName( "MapX", fX ) )
        {
            return false;
        }

        if( !reader.GetFloatFieldByName( "MapY", fY ) )
        {
            return false;
        }

        if( !reader.GetFloatFieldByName( "Dir", fDir ) )
        {
            return false;
        }

        if( !reader.GetIntFieldByName( "ChangeDir", nChangeDir ) )
        {
            return false;
        }

        if( !reader.GetIntFieldByName( "Shadow", nShadow ) )
        {
            nShadow = -1;
        }

        if( !reader.GetIntFieldByName( "NpcType", nNpcType ) )
        {
            return false;
        }

        if( !reader.GetStringFieldByName( "FileName", strFileName ) )
        {
            strFileName = "";
        }

        if( !reader.GetStringFieldByName( "ImgPath", strImgPath ) )
        {
            strImgPath = "";
        }

        if( !reader.GetStringFieldByName( "WalkPath", strWalkPath ) )
        {
            strWalkPath.clear();
        }

        if( !reader.GetIntFieldByName( "Mask", nMask ) )
        {
            nMask = 0;
        }

        SNpc stNpc;
        stNpc.nID			= nNpcId_for_storage;
        stNpc.strName		= strNpcName;
        stNpc.nLevel		= nLevel;
        stNpc.nModelId		= nModelId;
        stNpc.dwMapId		= nMapId;
        stNpc.fMapX			= fX;
        stNpc.fMapY			= fY;
        stNpc.fDir			= fDir;
        stNpc.strImgPath	= strImgPath;
        stNpc.strWalkPath	= strWalkPath;
        stNpc.bChangeDir	= (nChangeDir == 0);
        stNpc.bShadow		= (nShadow == 0);
        stNpc.nNpcType		= nNpcType;
        stNpc.strFileName	= strFileName;
        stNpc.bMask			= (nMask != 0);
        _NpcInfos.push_back( stNpc );
    }
	return true;
}
unsigned int NpcManager::GetNpcTotal()
{
    return (unsigned int)_NpcInfos.size();
}


/*
bool NpcManager::CreateNpcs( DWORD dwMapId, DWORD dwEctypeId )
{
	for ( unsigned int n=0; n<_NpcInfos.size(); ++n )
	{
		SNpc* pNpc = &_NpcInfos[n];
		if ( pNpc->dwMapId != dwMapId )
			continue;

        int nNpcId = RunTimeData::GetInstance().CreateObject(BaseCharacter::Object_Npc);
		NpcBaseCharacter* npc = (NpcBaseCharacter*)RunTimeData::GetInstance().GetCharacterByID( nNpcId );
		if ( !npc )
			continue;

		npc->SetPlayerName( pNpc->strName.c_str() );
		npc->SetNpcID( pNpc->nID );
		npc->SetLevel( pNpc->nLevel );
		npc->SetModelId( pNpc->nModelId );
		npc->SetMapID( dwEctypeId );
		npc->SetX( pNpc->fMapX );
		npc->SetY( pNpc->fMapY );
		npc->SetMask( pNpc->bMask );

		float fDir = pNpc->fDir;
		float fDirX = 0.0f, fDirY = 0.0f;
		if( fDir < 0 || fDir > 360 )
			fDir = 0;

		fDir = fDir/180*D3DX_PI;
		float fxtoy = tan(fDir);
		float fPosXOff = 0;
		float fPosYOff = 0;

		if( fxtoy == 0 )
		{
			fPosXOff = 1;
		}
		else
		{
			fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
			fPosYOff = fabs(fxtoy*fPosXOff);
		}
		if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
		{ // 第一象限
			fDirX = fPosXOff;
			fDirY = fPosYOff;
		}
        else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
		{ // 第二象限
			fDirX = -fPosXOff;
			fDirY = fPosYOff;
		}
        else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
		{ // 第三象限
			fDirX = -fPosXOff;
			fDirY = -fPosYOff;
		}
        else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
		{ // 第四象限
			fDirX = fPosXOff;
			fDirY = -fPosYOff;
		}

		npc->SetDirX( fDirX );
		npc->SetDirY( fDirY );
		npc->SetDir( 0 );

		npc->SET_VALUE( fMoveSpeed, fBase, 1.65f );
        npc->UPDATE_VALUE( fMoveSpeed );
		
		npc->SetLastMovingRate( npc->GetMoveSpeed() );
        npc->SET_VALUE( iHpMax, base, 10000 );
		npc->UPDATE_VALUE(iHpMax);
		npc->SetHP(60000);

		//short stX,stY;
		//stX = npc->GetX();
		//stY = npc->GetY();
		//int nNewArea = TestAreaNumber( stX, stY );
		//npc->SetCurArea( nNewArea );
		//npc->SetNpcImgPath( pNpc->strImgPath.c_str() );

		if( !pNpc->strWalkPath.empty())
		{
			if( npc->ReadMovePath( pNpc->strWalkPath.c_str() ) )
			{
				npc->SetMoveState( NpcBaseCharacter::eMoveWillMoveNext );
			}
			else
			{
				GetErrorLog()->logString("[Error] %s [MovePath] read failed \n", NPC_FILEPATH );
			}
		}

		if( pNpc->bChangeDir )
			npc->AddShowFlag( eNotChangeDir );
		if( pNpc->bShadow )
			npc->AddShowFlag( eNotShadow );

		if( !GettheWorld().OnAddCharacter( nNpcId ) )
		{
			GetErrorLog()->logString("[Error] CreateNpcs GettheWorld().OnAddCharacter( %d ) error", nNpcId );
			GettheWorld().OnDelCharacter( nNpcId );
			RunTimeData::GetInstance().ReleaseObject( nNpcId );
			continue;
		}

		if( pNpc->nNpcType >= 0 || pNpc->nNpcType < eNT_Max )
			npc->SetNpcType( (E_NpcType)pNpc->nNpcType );
        
        std::string strScriptPath = SCRIPT_ROOTDIRECTORY;
        strScriptPath += pNpc->strFileName;

		int nVMId = GetScriptMgr()->CreateVM( ST_NPC, strScriptPath.c_str(), nNpcId );
		CScriptVMThread thread;
		CScriptVM* pVM = GetScriptMgr()->GetScriptControl()->GetVM( nVMId );
		thread.SetVM( pVM );
		if( thread.SetEntrance( 0 ) )
		{
			thread.SetCharId( nNpcId );
			if ( !thread.Restore() )
			{
				GetErrorLog()->logString("[Error] CScriptMgr::InitScripts() thread.Restore() error \n" );
			}
		}
	}
	return true;
}
*/