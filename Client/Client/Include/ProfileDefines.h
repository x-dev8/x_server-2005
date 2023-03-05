#pragma once
#include <MeFoundation/MeFoundationPCH.h>

#ifdef CLIENT_PROFILE
typedef MeProfileCommon ProfileGameMain;
typedef MeProfileCommon ProfilePlayer;
#define ProfilePlayerFun ProfilePlayer( __FUNCTION__ );
typedef MeProfileCommon ProfilePlayerManager;
#else //_DEBUG
#define MeProfileCommon
#define MeProfileCommon
#define ProfilePlayerFun
#define MeProfileCommon
#endif // _DEBUG