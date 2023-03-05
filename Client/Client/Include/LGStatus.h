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
	LGS_DEFAULT,			// ��ʼ״̬
	LGS_ROLLING_BEGIN,		// ���¡���ʼ���󣬿�ʼ����
	LGS_ROLLING_END,		// ���¡�ֹͣ���󣬻�������ֱ���������
	LGS_NEXTMISSION,		// ��һ��״̬
	LGS_HALF,				// һ�뽱��
	LGS_DOUBLE,				// ˫������
	LGS_FRONT,				// ��һ��
	LGS_STAY,				// ������
	LGS_JUMP,				// ��һ��
	LGS_LOST,				// ʧ��״̬
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
	/** ����uv����������������Ϊ���ͺ�·��
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

	/** ����ͼƬ���򣬸���ui�ľ���ߴ硣����Ϊ���ͺ�rect
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
	/**	��ʼ��uv����
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
		// ɫ�Ӳ����Ŷ���
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
	/** ����uv����������������Ϊ���ͺ�·��
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
	/** ��������
	*/
	virtual void Reset(){
		LGStatusBase::Reset();
		m_kFire.Reset();
		m_kMiddleDice.Reset();
	}
	/** ����ͼƬ���򣬸���ui�ľ���ߴ硣����Ϊ���ͺ�rect
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
	/** ���������µ�uv����
	*/
	virtual void PostUpdate( DWORD dwTime ){
		m_kMiddleDice.Update( dwTime );
		m_kFire.Update( dwTime );
	}

	/** �������uv����
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