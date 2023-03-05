#pragma once

#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
#include "Me3d/Vector.h"
#include "MeUi/UiPicture.h"

//----------------------------------------------------------------------
/** 该类动画是根据外传的目标区域去更新图片的位置
*/
class RollSingleAnimCore : public RollAnimCoreBase
{
public:
	RollSingleAnimCore() : m_uiTotalPositionCnt(0), m_nGap(0){}

	void InitAnimData( unsigned int uiTotalPosCnt, const RECT& rcSrc, int nGap = 0 ){
		m_uiTotalPositionCnt = uiTotalPosCnt;
		m_rcSrc = rcSrc;
		m_nGap = nGap;
	}

	/** 初始位置
	*/
	void SetInitTargetRect( const RECT& rcTargetRect, int nGap = 0 ){
		m_rcInitTargetRect = rcTargetRect;
		m_nGap = nGap;
		// 起始坐标变动后，重新计算所有区域信息
		CalTargetRects();
	}

	void UpdateAnim(){
		//SetTargetAnim( GetCurrentAnim() + 1 );
		++m_uiCurrentAnim;
		if( m_uiCurrentAnim == m_uiTotalPositionCnt )
			m_uiCurrentAnim = 0;
	}
	
	const RECT& GetTargetRect() const{ 
		if( m_uiCurrentAnim < m_TargetRects.size() &&
			m_uiCurrentAnim >= 0 )
		{
			return m_TargetRects[m_uiCurrentAnim];			
		}
		return m_rcInitTargetRect;
	}

	/** 设置起始动画索引状态
	*/
	void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;
		m_uiCurrentAnim = m_uiStartAnim;
	}

protected:
	/** 通过总数和起始位置，预计算所有格子位置
	*/
	void CalTargetRects(){
		if( m_uiTotalPositionCnt == 0 )
			return;
		RECT rcTempTarget = m_rcInitTargetRect;
		unsigned int uiFac = m_uiTotalPositionCnt / 4;
		unsigned int uiCorner = uiFac + 2;
		int nW = m_rcInitTargetRect.right - m_rcInitTargetRect.left + m_nGap;
		int nH = 0;
		m_TargetRects.clear();
		m_TargetRects.push_back( rcTempTarget );
		/*目标区域按照正方形排列，所以需要判断三次位置*/
		for( int i = 2 ; i < m_uiTotalPositionCnt + 1 ; ++ i )
		{
			if( i - uiCorner == 0 * uiFac ){//第一个转弯
				nW = 0;
				nH = m_rcInitTargetRect.bottom - m_rcInitTargetRect.top + m_nGap;
			}
			else if( i - uiCorner == 1 * uiFac ){//第二个转弯
				nW = m_rcInitTargetRect.left - m_rcInitTargetRect.right - m_nGap;
				nH = 0;
			}
			else if( i - uiCorner == 2 * uiFac ){//第三个转弯
				nW = 0;
				nH = m_rcInitTargetRect.top - m_rcInitTargetRect.bottom - m_nGap;
			}
			rcTempTarget.left += nW;
			rcTempTarget.right += nW;
			rcTempTarget.top += nH;
			rcTempTarget.bottom += nH;
			m_TargetRects.push_back( rcTempTarget );
		}
	}

protected:
	/* 根据总共的选择个数和起始区域位置
	   和大小就可以计算给定索引的位置 */
	unsigned int m_uiTotalPositionCnt;
	RECT m_rcInitTargetRect;
	// 两个图元之间的间距
	int m_nGap;

	typedef std::vector< RECT > TargetRectContainer;
	TargetRectContainer m_TargetRects;
};
//----------------------------------------------------------------------
/** uv动画计算核心部分，被用作RollAnim模参
*/
class RollUVAnimCore : public RollAnimCoreBase
{
public:
	RollUVAnimCore(){}

	/** 初始化uv数据
	*/
	void InitAnimData( 
		int nWidth,
		int nHeight,
		unsigned int uiStartAnimState = 0,
		const Vector2& kStartPt = Vector2( 0.f, 0.f ),
		const Vector2& kEndPt = Vector2( 0.f, 0.f )
		){
			m_nWidth = nWidth;
			m_nHeight = nHeight;
			m_kStartPt = kStartPt;
			m_kEndPt = kEndPt;
			SetStartAnim( uiStartAnimState );
	}

	/** 计算当前uv动画的状态，返回索引。索引按照左至右，
	上至下的先后顺序计算。
	*/
	void UpdateAnim(){

		// 更新src rect
		m_rcSrc.left += m_nWidth;
		m_rcSrc.right = m_rcSrc.left + m_nWidth;
		if( m_rcSrc.right > m_kEndPt.x )
		{
			m_rcSrc.left = m_kStartPt.x;
			m_rcSrc.right = m_rcSrc.left + m_nWidth;
			// 换行需要
			m_rcSrc.top += m_nHeight;
			m_rcSrc.bottom = m_rcSrc.top + m_nHeight;
			if( m_rcSrc.bottom > m_kEndPt.y )
			{
				// 从新开始
				m_rcSrc.top = m_kStartPt.y;
				m_rcSrc.bottom = m_rcSrc.top + m_nHeight;
				HaveUpdated( true );
			}
		}
	}

	/** 返回当前位置
	*/
	unsigned int GetCurrentAnim(){

		// 更新当前anim
		Vector2 vIndex = Vector2( ( m_rcSrc.left - m_kStartPt.x ) / m_nWidth, 
			( m_rcSrc.top - m_kStartPt.y ) / m_nHeight );
		int nColCount = ( m_kEndPt.x - m_kStartPt.x ) / m_nWidth;
		m_uiCurrentAnim = vIndex.x * nColCount + vIndex.y;
		return m_uiCurrentAnim;
	}

	/** 设置起始动画索引状态
	*/
	void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;
		CaclAnimStartRectByAnimStartStatus();
	}	

	/** 设置目标区域，这个是动态变化，所以
	不应该放在init里面
	*/	
	void SetDestRect( const RECT& rcDest ){ m_rcDest = rcDest; }

	/** 获得目标区域，用来渲染。外部传来的即可
	*/
	const RECT& GetTargetRect() const{ return m_rcDest; }

private:

	/** 计算当前的起始位置，根据起始索引。
	*/
	void CaclAnimStartRectByAnimStartStatus(){
		int nColCount = ( m_kEndPt.x - m_kStartPt.x ) / m_nWidth;
		Vector2 vIndex = Vector2( nColCount == 0 ? 0 : m_uiStartAnim / nColCount, 
			m_uiStartAnim - ( nColCount == 0 ? 0 : m_uiStartAnim 
			/ nColCount * nColCount ) );
		m_rcSrc.left = m_nWidth * vIndex.x + m_kStartPt.x;
		m_rcSrc.right = m_rcSrc.left + m_nWidth;
		m_rcSrc.top = m_nHeight * vIndex.y + m_kStartPt.y;
		m_rcSrc.bottom = m_rcSrc.top + m_nHeight;
	}

protected:
	// 单帧的宽/高
	int m_nWidth;
	int m_nHeight;
	// 目标位置
	RECT m_rcDest;

private:
	Vector2 m_kStartPt;
	Vector2 m_kEndPt;
};
//----------------------------------------------------------------------
/** RollAnim,类博彩系统的动画类。包含图片信息和一些常用的
	坐标信息。模参AnimAlgorithm用来控制动画的速度，模参animcore
	用来控制动画的轨迹和表现。
*/
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce = false,
	bool bNullAlgorithm = true
>
class RollAnim : public AnimAlgorithm, public AnimCore, public AnimSound
{
public:	
	RollAnim() : m_dwLastUpdateTime(0){
		memset( m_acFilename, 0, sizeof( char ) * MAX_PATH );
	}
	~RollAnim(){}

	void InitData( const char* pcFilename ){
		if( pcFilename )
		{
			SetRenderFilename( pcFilename );
		}
	}

	/** 重置
	*/
	void Reset();

	/** 更新动画速度、轨迹
	*/
	void Update( DWORD dwTime ){
		Update( dwTime, Int2Type<bNullAlgorithm>() );
	}

	/** 渲染
	*/
	void Render(){
		Render( Int2Type< bPlayOnce >() );
	}

	/** 改变贴图
	*/
	void SetRenderFilename( const char* pcFilename ){
		memset( m_acFilename, 0, MAX_PATH );
		memcpy_s( m_acFilename, MAX_PATH, pcFilename, MAX_PATH -1 );		
	}

protected:
	/** 是否继续更新
	*/
	bool ContinueUpdate( DWORD dwTime ){
		return ContinueUpdate( dwTime, Int2Type< bPlayOnce >() );
	}

private:
	/** 只更新一次
	*/
	bool ContinueUpdate( DWORD dwTime, Int2Type< true > );
	void Render( Int2Type< true > );

	/** 不只更新一次
	*/
	bool ContinueUpdate( DWORD dwTime, Int2Type< false > );
	void Render( Int2Type< false > );

	/** 空算法时的update
	*/
	void Update( DWORD dwTime, Int2Type<true> );

	/** 非空算法时的update
	*/
	void Update( DWORD dwTime, Int2Type<false> );

protected:
	// 图片文件名
	char m_acFilename[MAX_PATH];
	// last update time
	DWORD m_dwLastUpdateTime;
};
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
void RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
Reset()
{
	AnimAlgorithm::Reset();
	AnimCore::Reset();
	AnimSound::Reset();
	// 速度的计算在每次重置后自动开始
	AnimAlgorithm::Start();
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
bool RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
ContinueUpdate( DWORD dwTime, Int2Type<false> )
{
	if( m_acFilename[0] == '\0' )
		return false;

	if( AnimAlgorithm::GetDelay() == -1 )
		return false;

	if( dwTime - m_dwLastUpdateTime < AnimAlgorithm::GetDelay() )
		return false;

	return true;
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
bool RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
ContinueUpdate( DWORD dwTime, Int2Type<true> )
{
	if( bPlayOnce && AnimCore::HaveUpdated() )
		return false;

	return ContinueUpdate( dwTime, Int2Type< false >() );
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
void RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
Update( DWORD dwTime, Int2Type<true> )
{
	if( !ContinueUpdate( dwTime ) )
		return;
	
	AnimCore::UpdateAnim();
	AnimSound::PlaySound();

	m_dwLastUpdateTime = dwTime;
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
void RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
Update( DWORD dwTime, Int2Type<false> )
{
	if( !ContinueUpdate( dwTime ) )
		return;

	AnimAlgorithm::UpdateAlgorithm( dwTime );
	AnimCore::UpdateAnim();
	AnimSound::PlaySound();

	if( AnimAlgorithm::IsProcessing() )
	{
		// 判断是否停止更新，共两个条件
		// 1。是否满足持续时间
		// 2。是否满足目标的动画索引
		if( dwTime - AnimAlgorithm::GetStartTime() >= 
			AnimAlgorithm::GetDuration() &&
			AnimCore::GetCurrentAnim() == AnimCore::GetTargetAnim() )
		{
			AnimAlgorithm::Stop();
			// 停止动画更新
			AnimAlgorithm::SetDelay( -1 );
			// 产生最终结果
			AnimAlgorithm::AlgorithmFinished( true );
		}
	}	

	m_dwLastUpdateTime = dwTime;	
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
void RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
Render( Int2Type< false > )
{
	if( m_acFilename[0] == '\0' )
		return;
	int nfoo = -1;
	DWORD dwColor = 0xffffffff;
	RECT rcDest = GetTargetRect();
	theControlPictureManager.BitBlt( &nfoo,
		m_acFilename, &rcDest, &m_rcSrc, dwColor );
}
//----------------------------------------------------------------------
template
< 
	class AnimAlgorithm, 	
	class AnimCore, 
	class AnimSound, 
	bool bPlayOnce,
	bool bNullAlgorithm
>
void RollAnim< AnimAlgorithm, AnimCore, AnimSound, bPlayOnce, bNullAlgorithm >::
Render( Int2Type< true > )
{
	if( bPlayOnce && AnimCore::HaveUpdated() )
		return;

	if( m_acFilename[0] == '\0' )
		return;

	int nfoo = -1;
	DWORD dwColor = 0xffffffff;
	RECT rcDest = GetTargetRect();
	theControlPictureManager.BitBlt( &nfoo,
		m_acFilename, &rcDest, &m_rcSrc, dwColor );
}
//----------------------------------------------------------------------
	/// 常用定义
	typedef RollAnim
		< 
		NullDiceAlgorithm,
		RollUVAnimCore, 
		RollSound<false>, 
		false, 
		true 
		> NormalUVAnim;
	typedef RollAnim
		< 
		NullDiceAlgorithm,
		RollUVAnimCore, 
		RollSound<true>, 
		false, 
		true 
		> NormalSoundOnceUVAnim;
	typedef RollAnim
		< 
		NullDiceAlgorithm,
		RollUVAnimCore, 
		RollSound<true>, 
		true, 
		true 
		> NormalSoundNPlayOnceUVAnim;
	typedef RollAnim
		< 
		LimitPowerDiceAlgorithm<>,
		RollUVAnimCore, 
		RollSound<false>, 
		false, 
		false 
		> LimitAlgorithmUVAnim;
	typedef RollAnim
		< 
		LimitPowerDiceAlgorithm< -5, 5000, 100, 1000 >,
		RollUVAnimCore, 
		RollSound<false>, 
		false, 
		false
		> LimitAlgorithmReverseUVAnim;
	typedef RollAnim
		< 
		LimitPowerDiceAlgorithm< 1, 1000, 10, 100 >,
		RollSingleAnimCore, 
		RollSound<false>, 
		false, 
		false 
		> LimitAlgorithmSingleAnim;
	typedef RollAnim
		< 
		LimitPowerDiceAlgorithm< -5, 2000, 10, 1000 >,
		RollSingleAnimCore, 
		RollSound<false>, 
		false, 
		false
		> LimitAlgorithmReverseSingleAnim;
//----------------------------------------------------------------------
template< unsigned int uiStatus, typename Dice = NormalUVAnim >
class RollAnimStatus : public RollSystemStatusBase
{
public:
	RollAnimStatus() : m_uiStatus( uiStatus ){}
	virtual ~RollAnimStatus(){}
	virtual void InitData(){
		InitUVData();
	}

	/** 重置数据
	*/
	virtual void Reset(){
		m_kBackground.Reset();
		m_kLight.Reset();
		m_kDice.Reset();
	}

	virtual void PreUpdate( DWORD dwTime ){}
	virtual void PostUpdate( DWORD dwTime ){}

	virtual void Update(){
		DWORD dwTime = HQ_TimeGetTime();
		PreUpdate( dwTime );		
		m_kBackground.Update( dwTime );
		m_kLight.Update( dwTime );
		m_kDice.Update( dwTime );
		PostUpdate( dwTime );		
	}

	virtual void Render(){
		m_kBackground.Render();
		m_kDice.Render();
		m_kLight.Render();
	}

	virtual void SetState( unsigned int uiState ){ 
		m_uiStatus = uiState; }
	virtual unsigned int GetState() const { return m_uiStatus; }

	/** 设置起始uv动画索引
	*/
	virtual void SetStartDiceAnimState( unsigned int uiStartState ){
		m_kDice.SetStartAnim( uiStartState );
	}

	/** 设置目标uv动画索引
	*/
	virtual void SetTargetDiceAnimState( unsigned int uiTargetState ){
		m_kDice.SetTargetAnim( uiTargetState );
	}

	/** 设置获得当前uv动画索引，色子
	*/
	virtual unsigned int GetCurrentDiceAnimState(){
		return m_kDice.GetCurrentAnim();
	}
	virtual void SetCurrentDiceAnimState( unsigned int uiState ){
		m_kDice.SetCurrentAnim( uiState );
	}


	/** 设置uv动画的声音。参数为类型和路径
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ){
		return true;
	}

	/** 设置图片区域，根据ui的具体尺寸。参数为类型和rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, 
		int nExtraData = 0 ){
		return true;
	}

	/** 设置需要渲染的文件名
	*/
	virtual bool SetRenderFilename( unsigned int uiType, const char* pcFilename ){
		return true;
	}

protected:
	/**	初始化uv数据
	*/
	virtual void InitUVData()
	{
		// 设置声音
		m_kBackground.SetSoundFunc( PlayUVSound );
		m_kDice.SetSoundFunc( PlayUVSound );
	}

protected:
	static bool PlayUVSound( const char* szName, D3DXVECTOR3* vPos,bool bLoop )
	{
		GSound.PlaySound( szName,bLoop, vPos );
		return true;
	}

protected:
	NormalSoundOnceUVAnim m_kBackground;
	NormalUVAnim m_kLight;
	Dice m_kDice;
	unsigned int m_uiStatus;
};
//----------------------------------------------------------------------