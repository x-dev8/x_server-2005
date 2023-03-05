#pragma once

#include "MeRTLibs.h"
#include "RollSystemBase.h"
#include "DiceAlgorithm.h"
#include "RollSound.h"
#include "RollAnim.h"
#include "Me3d/Vector.h"
#include "MeAudio/MeAudio.h"

//----------------------------------------------------------------------
static const char* const s_pcBackgroundDefault 
= "./data/ui/common/HudLotteryBackground.dds";
static const char* const s_pcDice
= "./data/ui/icon/IconSelectFrame.dds";
static const char* const s_pcLight
= "./data/ui/common/HudLotteryLight.dds";
//----------------------------------------------------------------------
enum ELotteryGameStatus
{
	LOTTERYSTATUS_DEFAULT,		// ��
	LOTTERYSTATUS_ROLL_BEGIN,	// ��ʼҡ��
	LOTTERYSTATUS_ROLL_END,		// ��ֹͣ��
	LOTTERYSTATUS_READYGET,		// ��ȫֹͣ�ˣ��ȴ�ȡ��Ʒ
	LOTTERYSTATUS_COUNT
};
//----------------------------------------------------------------------
enum ELotteryGamePicRect
{
	LOTTERYGPR_BG,
	LOTTERYGPR_LIGHT,
	LOTTERYGPR_DICE,
	LOTTERYGPR_COUNT
};
//----------------------------------------------------------------------
enum ELotteryGameSound
{
	LOTTERYGS_BG,
	LOTTERYGS_DICE,
	LOTTERYGS_COUNT
};
//----------------------------------------------------------------------
enum ELotteryRenderFilename
{
	LOTTERYRF_BG,
	LOTTERYRF_COUNT
};
//----------------------------------------------------------------------
template< unsigned int uiStatus, typename Dice > 
class LotteryStatusBase : public RollAnimStatus< uiStatus, Dice >
{
public:
	/** ����uv����������������Ϊ���ͺ�·��
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ){
		if( uiType < LOTTERYGS_BG || uiType >= LOTTERYGS_COUNT )
			return false;
		ELotteryGameSound eType = ( ELotteryGameSound )uiType;
		switch( eType )
		{
		case LOTTERYGS_DICE:
			m_kDice.SetUVSoundPath( pcSound );
		}
		return true;
	}
	/** �������򣬸���ui�ľ���ߴ硣����Ϊ���ͺ�rect
	����dice��Ҫ�ر�����
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, int nExtraData = 0 ){
		if( uiType < LOTTERYGPR_BG || uiType >= LOTTERYGPR_COUNT )
			return false;
		ELotteryGamePicRect eType = ( ELotteryGamePicRect )uiType;
		switch( eType )
		{
		case LOTTERYGPR_DICE:
			m_kDice.SetInitTargetRect( kRect, nExtraData );
			break;
		case LOTTERYGPR_LIGHT:
			m_kLight.SetDestRect( kRect );
			break;
		}
		return true;
	}

	/** ������Ҫ��Ⱦ���ļ���
	*/
	virtual bool SetRenderFilename( unsigned int uiType, const char* pcFilename ){
		if( uiType < LOTTERYRF_BG || uiType >= LOTTERYRF_COUNT )
			return false;
		ELotteryRenderFilename eType = ( ELotteryRenderFilename )uiType;
		switch( eType )
		{
		case LOTTERYRF_BG:
			m_kBackground.SetRenderFilename( pcFilename );
			break;
		}
		return true;
	}
	
protected:
	/**	��ʼ��uv����
	*/
	virtual void InitUVData()
	{
		m_kDice.InitData( s_pcDice );			
		RECT rcSrc = { 0, 0, 39, 39 };		
		m_kDice.InitAnimData( 24, rcSrc );
		RollAnimStatus::InitUVData();
	}
};
//----------------------------------------------------------------------
template< unsigned int uiStatus > class LotteryStatus{};
//----------------------------------------------------------------------
template<> class LotteryStatus< LOTTERYSTATUS_DEFAULT >
: public LotteryStatusBase< LOTTERYSTATUS_DEFAULT, LimitAlgorithmSingleAnim >
{
protected:
	/**	��ʼ��uv����
	*/
	void InitUVData()
	{
		m_kDice.SetInitDelay( -1 );
		LotteryStatusBase::InitUVData();		
	}
};
//----------------------------------------------------------------------
template<> class LotteryStatus< LOTTERYSTATUS_ROLL_BEGIN >
: public LotteryStatusBase< LOTTERYSTATUS_ROLL_BEGIN, 
LimitAlgorithmReverseSingleAnim >
{
protected:
	void InitUVData()
	{
		LotteryStatusBase::InitUVData();		
		m_kDice.SetInitDelay( 300 );
		m_kDice.Start();	
// 		m_kLight.InitData( s_pcLight );
// 		m_kLight.InitAnimData( 251, 251, 0, Vector2( 0, 0 ), Vector2( 1024, 512 ) );
// 		m_kLight.SetInitDelay( 100 );
	}
	
};
//----------------------------------------------------------------------
template<> class LotteryStatus< LOTTERYSTATUS_ROLL_END >
: public LotteryStatusBase< LOTTERYSTATUS_ROLL_END, 
LimitAlgorithmSingleAnim >
{
protected:
	void InitUVData()
	{
		LotteryStatusBase::InitUVData();
		m_kDice.SetInitDelay( 100 );
		m_kDice.Start();
// 		m_kLight.InitData( s_pcLight );
// 		m_kLight.InitAnimData( 251, 251, 0, Vector2( 0, 0 ), Vector2( 1024, 512 ) );
// 		m_kLight.SetInitDelay( 100 );
			
	}
public:
	typedef void (*PostUpdateFuncPtr)();

	/** ÿ֡�������ʣ���󵽴�ѡ��ֵ
	*/	
	virtual void PostUpdate( DWORD dwTime ){
		if( m_kDice.AlgorithmFinished() && m_pfPostUpdate )
			m_pfPostUpdate();
	}

	void SetPostUpdateFunc( PostUpdateFuncPtr pfFunc ){
		m_pfPostUpdate = pfFunc;
	}
protected:
	PostUpdateFuncPtr m_pfPostUpdate;
};
//----------------------------------------------------------------------
template<> class LotteryStatus< LOTTERYSTATUS_READYGET >
: public LotteryStatusBase< LOTTERYSTATUS_READYGET, LimitAlgorithmSingleAnim >
{
protected:
	/**	��ʼ��uv����
	*/
	void InitUVData()
	{
		m_kDice.SetInitDelay( -1 );
		LotteryStatusBase::InitUVData();		
	}
};
//----------------------------------------------------------------------