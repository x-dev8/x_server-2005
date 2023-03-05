#include "BaseState.h"

StateManager::StateManager() : _pCurrentState( NULL )
{

}

StateManager::~StateManager()
{

}

uint32 StateManager::RegisterBeginState( EBotState bs )
{
    return ER_Success;
}

uint32 StateManager::Update()
{
    if ( NULL == _pCurrentState )
    { return ER_Failed; }

    _pCurrentState->Run();
    return ER_Success;
}
