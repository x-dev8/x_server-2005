#pragma once
#include <string>

class MexAnimCtrl;

class navigation : public MeCommonAllocObj<navigation>
{
public:
    navigation();
    virtual ~navigation();

    virtual bool create( const std::string& filename );
    virtual void setNavigationPoint( const D3DXVECTOR3& srcPos, const D3DXVECTOR3& destPos );

    MexAnimCtrl* getMexAnimCtrl();

protected:
    MexAnimCtrl* _pMexAnimCtrl;
};
