#pragma once

/// Profiling
//#ifdef MEPROFILE
#if 0

typedef MeProfileCommon MeScopeProfileCommon;
#define MeScopeProfileCommonFun MeScopeProfileCommon( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileMex;
#define MeScopeProfileMexFun MeScopeProfileMex( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileMexAnimCtrl;
#define MeScopeProfileMexAnimCtrlFun MeScopeProfileMexAnimCtrl( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileMexGeoChunk;
#define MeScopeProfileMexGeoChunkFun MeScopeProfileMexGeoChunk( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileMexRes;
#define MeScopeProfileMexResFun MeScopeProfileMexRes( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileAlphaCollector;
#define MeScopeProfileAlphaCollectorFun MeScopeProfileAlphaCollector( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileRenderManager;
#define MeScopeProfileRenderManagerFun MeScopeProfileRenderManager( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileCombineRenderManager;
#define MeScopeProfileCombineRenderManagerFun MeScopeProfileCombineRenderManager( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileShimmerCollector;
#define MeScopeProfileShimmerCollectorFun MeScopeProfileShimmerCollector( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileSorter;
#define MeScopeProfileSorterFun MeScopeProfileSorter( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileTextureManager;
#define MeScopeProfileTextureManagerFun MeScopeProfileTextureManager( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileRenderObject;
#define MeScopeProfileRenderObjectFun MeScopeProfileRenderObject( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileAudio;
#define MeScopeProfileAudioFun MeScopeProfileAudio( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileFont;
#define MeScopeProfileFontFun MeScopeProfileFont( __FUNCTION__ );

typedef MeProfileCommon MeScopeProfileUiManager;
#define MeScopeProfileUiManagerFun MeScopeProfileUiManager( __FUNCTION__ );

#else
#define MeScopeProfileCommon( message )
#define MeScopeProfileCommonFun
#define MeScopeProfileMex( message )
#define MeScopeProfileMexFun
#define MeScopeProfileMexAnimCtrl ( message )
#define MeScopeProfileMexAnimCtrlFun
#define MeScopeProfileMexGeoChunk ( message )
#define MeScopeProfileMexGeoChunkFun
#define MeScopeProfileMexRes ( message )
#define MeScopeProfileMexResFun
#define MeScopeProfileAlphaCollector ( message )
#define MeScopeProfileAlphaCollectorFun
#define MeScopeProfileRenderManager ( message )
#define MeScopeProfileRenderManagerFun
#define MeScopeProfileCombineRenderManager ( message )
#define MeScopeProfileCombineRenderManagerFun
#define MeScopeProfileShimmerCollector ( message )
#define MeScopeProfileShimmerCollectorFun
#define MeScopeProfileSorter ( message )
#define MeScopeProfileSorterFun
#define MeScopeProfileTextureManager ( message )
#define MeScopeProfileTextureManagerFun
#define MeScopeProfileRenderObject( message );
#define MeScopeProfileRenderObjectFun 
#define MeScopeProfileAudio( message );
#define MeScopeProfileAudioFun
#define MeScopeProfileFont( message );
#define MeScopeProfileFontFun
#define MeScopeProfileUiManager( message );
#define MeScopeProfileUiManagerFun
#endif

//#ifdef MEPROFILE
#if 0
#define MeFreeProfileStart( message ) MeFreeProfile< FPS_Start, MeLog, MPT_Common, MeClockTimer >( message )
#define MeFreeProfileEnd( message ) MeFreeProfile< FPS_End, MeLog, MPT_Common, MeClockTimer >( message )
#else // MEPROFILE
#define MeFreeProfileStart( message )
#define MeFreeProfileEnd( message )
#endif // MEPROFILE

/**
* @EH staff.
*/
#ifdef _DEBUG
#define BeginGuard // try{
#define EndGuard //}catch(...){}
#else //_DEBUG
#define BeginGuard
#define EndGuard
#endif //_DEBUG

#define FLOAT_TOLERANCE (1e-6)
#define FLOAT_EQUAL( a, b ) ( fabs( a - b ) < 1e-6 )
#define MeAssert assert

/**
* @brief 一些常用函数。 
*/
class MEFOUNDATION_ENTRY MeUtilityStaff
{
public:
	static float GetRandValueF( float dRangeMin, float dRangeMax ){
		unsigned int uiRandValue = 0;
		uiRandValue = rand();		
		return ( float )( ( float )uiRandValue / ( float )RAND_MAX * dRangeMax + dRangeMin ); 
	}

	static int GetRandValueI( int dRangeMin, int dRangeMax ){
		unsigned int uiRandValue = 0;
		uiRandValue = rand();		
		return ( uiRandValue / RAND_MAX * dRangeMax + dRangeMin ); 
	}
};

