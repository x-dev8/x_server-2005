#pragma once

#include "MeRTLibs.h"
#include "RollSystemBase.h"
#include "DiceAlgorithm.h"
#include "RollSound.h"
#include "RollAnim.h"
#include "Me3d/Vector.h"
#include "MeAudio/MeAudio.h"
//----------------------------------------------------------------------
static const char* const s_pcBgDefault = "./data/ui/common/HudLuckDefaultState.dds";
static const char* const s_pcBgRolling = "./data/ui/common/HudLuckLostState.dds";
static const char* const s_pcBgNextMission = "./data/ui/common/HudLuckNextMissionState.dds";
static const char* const s_pcBgLost = "./data/ui/common/HudLuckLostState.dds";
static const char* const s_pcOtherSource = "./data/ui/common/HudLuckButton.dds";
static const char* const s_pcGetAwards = "./data/ui/common/HudLuckGetAwardsState.dds";
static const char* const s_pcFire = "./data/ui/common/LuckGameFire.dds";
static const char* const s_pcCards = "./data/ui/common/HudLuckAward.dds";
//----------------------------------------------------------------------
enum ELuckyGameStatus
{
	LGS_DEFAULT,			// 开始状态
	LGS_ROLLING_BEGIN,		// 按下‘开始’后，开始滚动
	LGS_ROLLING_END,		// 按下‘停止’后，缓慢滚动直到产生结果
	LGS_NEXTMISSION,		// 下一关状态
	LGS_HALF,				// 一半奖励
	LGS_DOUBLE,				// 双倍奖励
	LGS_FRONT,				// 退一关
	LGS_STAY,				// 留本关
	LGS_JUMP,				// 跳一关
	LGS_LOST,				// 失败状态
	LGS_COUNT
};
//----------------------------------------------------------------------
enum ELuckyGamePicRect
{
	LGPR_BG,
	LGPR_LIGHT,
	LGPR_DICE,
	LGPR_FIRE,
	LGPR_MIDDLEDICE,
	LGPR_COUNT
};
//----------------------------------------------------------------------
enum ELuckyGameSound
{
	LGSD_BG,
	LGSD_DICE,
	LGSD_FIRE,
	LGSD_COUNT
};
//----------------------------------------------------------------------
template< unsigned int uiStatus, typename Dice = NormalUVAnim > class LGStatusBase : 
public RollAnimStatus< uiStatus, Dice >
{
public:
	/** 设置uv动画的声音。参数为类型和路径
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ){
		if( uiType < LGSD_BG || uiType >= LGSD_COUNT )
			return false;
		ELuckyGameSound eType = ( ELuckyGameSound )uiType;
		switch( eType )
		{
		case LGSD_BG:
			m_kBackground.SetUVSoundPath( pcSound );
			break;
		case LGSD_DICE:
			m_kDice.SetUVSoundPath( pcSound );
			break;
		}
		return true;
	}

	/** 设置图片区域，根据ui的具体尺寸。参数为类型和rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, int nExtraData = 0 ){
		if( uiType < LGPR_BG || uiType >= LGPR_COUNT )
			return false;
		ELuckyGamePicRect eType = ( ELuckyGamePicRect )uiType;
		switch( eType )
		{
		case LGPR_BG:
			m_kBackground.SetDestRect( kRect );
			break;
		case LGPR_LIGHT:
			m_kLight.SetDestRect( kRect );
			break;
		case LGPR_DICE:
			m_kDice.SetDestRect( kRect );
			break;
		}
		return true;
	}
protected:
	/**	初始化uv数据
	*/
	virtual void InitUVData()
	{
		m_kLight.InitData( s_pcOtherSource );
		m_kLight.InitAnimData( 304, 229, 0, Vector2( 0, 477 ), Vector2( 608, 935 ) );
		m_kLight.SetInitDelay( 100 );
		m_kDice.InitData( s_pcOtherSource );
		m_kDice.InitAnimData( 272, 182, 0,Vector2( 610, 478 ), Vector2( 881, 1024 ) );
		m_kDice.SetInitDelay( 100 );
		RollAnimStatus::InitUVData();		
	}

};
//----------------------------------------------------------------------
template< unsigned int uiStatus > class LGState : 
public LGStatusBase< uiStatus, NormalUVAnim >{};
//----------------------------------------------------------------------
template<> class LGState< LGS_DEFAULT > : 
public LGStatusBase< LGS_DEFAULT, NormalUVAnim >
{
public:
	virtual void InitUVData(){
		LGStatusBase::InitUVData();
		m_kBackground.InitData( s_pcBgDefault );
		m_kBackground.InitAnimData( 512, 666, 0, Vector2( 0, 0 ), Vector2( 1024, 700 ) );
		m_kBackground.SetInitDelay( 100 );
		// 色子不播放动画
		m_kDice.SetInitDelay( -1 );
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_ROLLING_BEGIN > : 
	public LGStatusBase< LGS_ROLLING_BEGIN, LimitAlgorithmReverseUVAnim >
{
public:	
	virtual void InitUVData(){
		LGStatusBase::InitUVData();
		m_kDice.SetInitDelay( 300 );
		m_kBackground.InitData( s_pcBgRolling );
		m_kBackground.InitAnimData( 512, 666, 0, Vector2( 0, 0 ), Vector2( 1024, 700 ) );
		m_kBackground.SetInitDelay( -1 );
		m_kDice.Start();
	}

};
//----------------------------------------------------------------------
template<> 
class LGState< LGS_ROLLING_END > : 
	public LGStatusBase< LGS_ROLLING_END, LimitAlgorithmUVAnim >
{
public:
	typedef void (*PostUpdateFuncPtr)();
public:	
	virtual void InitUVData(){
		LGStatusBase::InitUVData();
		m_kBackground.InitData( s_pcBgRolling );
		m_kBackground.InitAnimData( 512, 666, 0, Vector2( 0, 0 ), Vector2( 1024, 700 ) );
		m_kBackground.SetInitDelay( -1 );
		m_kDice.Start();
	}

	/** 每帧减慢速率，最后到达选定值
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
template<> class LGState< LGS_NEXTMISSION > : 
public LGStatusBase< LGS_NEXTMISSION, NormalUVAnim >
{
public:	
	virtual void InitUVData(){
		LGStatusBase::InitUVData();
		m_kBackground.InitData( s_pcBgNextMission );
		m_kBackground.InitAnimData( 512, 666, 0, Vector2( 0, 0 ), Vector2( 1024, 700 ) );
		m_kBackground.SetInitDelay( 100 );
		m_kDice.SetInitDelay( -1 );
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_LOST > : 
public LGStatusBase< LGS_LOST, NormalUVAnim >
{
public:	
	virtual void InitUVData(){
		LGStatusBase::InitUVData();
		m_kBackground.InitData( s_pcBgLost );
		m_kBackground.InitAnimData( 512, 666, 0, 
			Vector2( 0, 0 ), Vector2( 512, 700 ) );		
		m_kBackground.SetInitDelay( -1 );
		
		m_kLight.SetInitDelay( -1 );		
		m_kDice.SetStartAnim( 2 );
		m_kDice.SetInitDelay( -1 );
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_HALF > :
public LGStatusBase< LGS_HALF, NormalUVAnim >
{
public:
	virtual void InitUVData(){
		LGStatusBase::InitUVData();

		m_kBackground.InitData( s_pcBgDefault );
		m_kBackground.InitAnimData( 512, 666, 0, Vector2( 0, 0 ), Vector2( 1024, 700 ) );
		m_kBackground.SetInitDelay( 100 );
		
		m_kLight.InitData( s_pcOtherSource );
		m_kLight.InitAnimData( 304, 229, 0, Vector2( 0, 477 ), Vector2( 608, 935 ) );
		m_kLight.SetInitDelay( -1 );
		
		m_kDice.SetInitDelay( -1 );

		m_kFire.InitData( s_pcFire );
		m_kFire.InitAnimData( 82, 168, 0, Vector2( 0, 0 ), Vector2( 512, 512 ) );
		m_kFire.SetInitDelay( 100 );
		m_kFire.SetSoundFunc( PlayUVSound );		

		m_kMiddleDice.InitData( s_pcCards );
		m_kMiddleDice.InitAnimData( 81, 173, 0, Vector2( 514, 1 ), Vector2( 595, 174 ) );
		m_kMiddleDice.SetInitDelay( -1 );		
		
	}
	/** 设置uv动画的声音。参数为类型和路径
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ){

		if( !LGStatusBase::SetUVSound( uiType, pcSound ) )
			return false;

		switch( uiType )
		{
		case LGSD_FIRE:
			m_kFire.SetUVSoundPath( pcSound );
		}
		return true;
	}
	/** 重置数据
	*/
	virtual void Reset(){
		LGStatusBase::Reset();
		m_kFire.Reset();
		m_kMiddleDice.Reset();
	}
	/** 设置图片区域，根据ui的具体尺寸。参数为类型和rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, int nExtraData = 0 ){

		if( !LGStatusBase::SetPicRect( uiType, kRect, nExtraData ) )
			return false;
		
		switch( uiType )
		{
		case LGPR_FIRE:
			m_kFire.SetDestRect( kRect );
			break;
		case LGPR_MIDDLEDICE:
			m_kMiddleDice.SetDestRect( kRect );
			break;
		}
		return true;
	}
	/** 用来更新新的uv动画
	*/
	virtual void PostUpdate( DWORD dwTime ){
		m_kMiddleDice.Update( dwTime );
		m_kFire.Update( dwTime );
	}

	/** 添加新增uv动画
	*/
	virtual void Render(){
		LGStatusBase::Render();
		m_kMiddleDice.Render();
		m_kFire.Render();
	}
protected:
	NormalSoundNPlayOnceUVAnim m_kFire;
	NormalUVAnim m_kMiddleDice;
};
//----------------------------------------------------------------------
template<> class LGState< LGS_DOUBLE > :
public LGState< LGS_HALF >
{
public:
	virtual void InitUVData(){
		LGState< LGS_HALF >::InitUVData();
		m_kMiddleDice.InitAnimData( 81, 173, 0, Vector2( 595, 1 ), Vector2( 676, 174 ) );		
		m_uiStatus = LGS_DOUBLE;
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_FRONT > :
public LGState< LGS_HALF >
{
public:
	virtual void InitUVData(){
		LGState< LGS_HALF >::InitUVData();
		m_kMiddleDice.InitAnimData( 81, 173, 0, Vector2( 838, 1 ), Vector2( 919, 174 ) );		
		m_uiStatus = LGS_FRONT;
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_STAY > :
public LGState< LGS_HALF >
{
public:
	virtual void InitUVData(){
		LGState< LGS_HALF >::InitUVData();
		m_kMiddleDice.InitAnimData( 81, 173, 0, Vector2( 676, 1 ), Vector2( 757, 174 ) );		
		m_uiStatus = LGS_STAY;
	}
};
//----------------------------------------------------------------------
template<> class LGState< LGS_JUMP > :
public LGState< LGS_HALF >
{
public:
	virtual void InitUVData(){
		LGState< LGS_HALF >::InitUVData();
		m_kMiddleDice.InitAnimData( 81, 173, 0, Vector2( 757, 1 ), Vector2( 838, 174 ) );		
		m_uiStatus = LGS_JUMP;
	}
};