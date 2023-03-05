#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Platform.h"
#include "FuncPerformanceLog.h"
#include <sstream>
#include "navigation.h"

navigation::navigation()
{
    _pMexAnimCtrl = MeNew MexAnimCtrl();
}

navigation::~navigation()
{
    _pMexAnimCtrl->Destroy();
    delete _pMexAnimCtrl;
}

bool navigation::create(const std::string& filename )
{
    int nModelID = GetMexResMgr()->AddExternalFile( filename.c_str() );
    if( nModelID != -1 )
    {
        bool ret = _pMexAnimCtrl->ChangeModel( nModelID,FALSE,NULL );
        return ret;
    }
    return false;
}

void navigation::setNavigationPoint( const D3DXVECTOR3& srcPos, const D3DXVECTOR3& destPos )
{
    D3DXVECTOR3 up( 0, 0, 1 ), front( 1, 0, 0 ), right( 0, 1, 0 );
    D3DXVECTOR2 s( front.x, front.y );
    D3DXVECTOR2 d( destPos.x - srcPos.x, destPos.y - srcPos.y );
    D3DXVec2Normalize( &s, &s );
    D3DXVec2Normalize( &d, &d );
    float angle = acosf( D3DXVec2Dot( &s, &d ) );
    bool positive = D3DXVec2Dot( &D3DXVECTOR2( right.x, right.y ), &d ) > 0.0f;
    angle = positive ? angle : -angle;

    _pMexAnimCtrl->SetPosition( srcPos.x, srcPos.y, srcPos.z);
    _pMexAnimCtrl->SetScale( GetMe3dConfig()->m_fMdlSpaceScale );
    _pMexAnimCtrl->SetRotationZ( angle );
    _pMexAnimCtrl->UpdateByParam( HQ_TimeGetTime() );

}

MexAnimCtrl* navigation::getMexAnimCtrl()
{
    return _pMexAnimCtrl;
}
