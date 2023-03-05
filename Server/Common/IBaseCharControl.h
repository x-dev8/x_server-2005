/********************************************************************
    Filename:     IBaseCharControl.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_IBASECHARCONTROL_H__
#define __COMMON_IBASECHARCONTROL_H__

#pragma once

#include "MeRTLibsServer.h"
#include "IBaseControl.h"

class IBaseCharControl
{
public:
    IBaseCharControl() : _pControl( NULL ){}
    virtual ~IBaseCharControl(){}

    virtual bool   ProcessMsg( Msg* pMsg ){ return true; }
    virtual void   Run( DWORD dwCostTime ) = 0;
    virtual void   Release()               = 0;

    void           SetControl( IBaseControl* pControl ){ _pControl = pControl; }
    IBaseControl*  GetControl(){ return _pControl; }
    void           SetLifeCode( uint16 ustLifeCode ){ m_ustLifeCode = ustLifeCode; }
    unsigned short GetLifeCode(void){ return m_ustLifeCode; }
    GameObjectId   GetID(){ return _pControl->GetID(); } //Waring0    
    bool           IsSameCharacter( GameObjectId stID, uint16 ustLifeCode );

protected:
    IBaseControl* _pControl;
    uint16    m_ustLifeCode;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline bool IBaseCharControl::IsSameCharacter( GameObjectId stID, uint16 ustLifeCode )
{
    if ( _pControl == NULL )
    { return false; }

    if( _pControl->GetID() == stID && m_ustLifeCode == ustLifeCode )
    { return true; }
    return false;
}
#endif // __COMMON_IBASECHARCONTROL_H__
