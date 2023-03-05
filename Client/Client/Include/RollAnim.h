#pragma once

#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
#include "Me3d/Vector.h"
#include "MeUi/UiPicture.h"

//----------------------------------------------------------------------
/** ���ද���Ǹ����⴫��Ŀ������ȥ����ͼƬ��λ��
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

	/** ��ʼλ��
	*/
	void SetInitTargetRect( const RECT& rcTargetRect, int nGap = 0 ){
		m_rcInitTargetRect = rcTargetRect;
		m_nGap = nGap;
		// ��ʼ����䶯�����¼�������������Ϣ
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

	/** ������ʼ��������״̬
	*/
	void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;
		m_uiCurrentAnim = m_uiStartAnim;
	}

protected:
	/** ͨ����������ʼλ�ã�Ԥ�������и���λ��
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
		/*Ŀ�����������������У�������Ҫ�ж�����λ��*/
		for( int i = 2 ; i < m_uiTotalPositionCnt + 1 ; ++ i )
		{
			if( i - uiCorner == 0 * uiFac ){//��һ��ת��
				nW = 0;
				nH = m_rcInitTargetRect.bottom - m_rcInitTargetRect.top + m_nGap;
			}
			else if( i - uiCorner == 1 * uiFac ){//�ڶ���ת��
				nW = m_rcInitTargetRect.left - m_rcInitTargetRect.right - m_nGap;
				nH = 0;
			}
			else if( i - uiCorner == 2 * uiFac ){//������ת��
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
	/* �����ܹ���ѡ���������ʼ����λ��
	   �ʹ�С�Ϳ��Լ������������λ�� */
	unsigned int m_uiTotalPositionCnt;
	RECT m_rcInitTargetRect;
	// ����ͼԪ֮��ļ��
	int m_nGap;

	typedef std::vector< RECT > TargetRectContainer;
	TargetRectContainer m_TargetRects;
};
//----------------------------------------------------------------------
/** uv����������Ĳ��֣�������RollAnimģ��
*/
class RollUVAnimCore : public RollAnimCoreBase
{
public:
	RollUVAnimCore(){}

	/** ��ʼ��uv����
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

	/** ���㵱ǰuv������״̬�������������������������ң�
	�����µ��Ⱥ�˳����㡣
	*/
	void UpdateAnim(){

		// ����src rect
		m_rcSrc.left += m_nWidth;
		m_rcSrc.right = m_rcSrc.left + m_nWidth;
		if( m_rcSrc.right > m_kEndPt.x )
		{
			m_rcSrc.left = m_kStartPt.x;
			m_rcSrc.right = m_rcSrc.left + m_nWidth;
			// ������Ҫ
			m_rcSrc.top += m_nHeight;
			m_rcSrc.bottom = m_rcSrc.top + m_nHeight;
			if( m_rcSrc.bottom > m_kEndPt.y )
			{
				// ���¿�ʼ
				m_rcSrc.top = m_kStartPt.y;
				m_rcSrc.bottom = m_rcSrc.top + m_nHeight;
				HaveUpdated( true );
			}
		}
	}

	/** ���ص�ǰλ��
	*/
	unsigned int GetCurrentAnim(){

		// ���µ�ǰanim
		Vector2 vIndex = Vector2( ( m_rcSrc.left - m_kStartPt.x ) / m_nWidth, 
			( m_rcSrc.top - m_kStartPt.y ) / m_nHeight );
		int nColCount = ( m_kEndPt.x - m_kStartPt.x ) / m_nWidth;
		m_uiCurrentAnim = vIndex.x * nColCount + vIndex.y;
		return m_uiCurrentAnim;
	}

	/** ������ʼ��������״̬
	*/
	void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;
		CaclAnimStartRectByAnimStartStatus();
	}	

	/** ����Ŀ����������Ƕ�̬�仯������
	��Ӧ�÷���init����
	*/	
	void SetDestRect( const RECT& rcDest ){ m_rcDest = rcDest; }

	/** ���Ŀ������������Ⱦ���ⲿ�����ļ���
	*/
	const RECT& GetTargetRect() const{ return m_rcDest; }

private:

	/** ���㵱ǰ����ʼλ�ã�������ʼ������
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
	// ��֡�Ŀ�/��
	int m_nWidth;
	int m_nHeight;
	// Ŀ��λ��
	RECT m_rcDest;

private:
	Vector2 m_kStartPt;
	Vector2 m_kEndPt;
};
//----------------------------------------------------------------------
/** RollAnim,�಩��ϵͳ�Ķ����ࡣ����ͼƬ��Ϣ��һЩ���õ�
	������Ϣ��ģ��AnimAlgorithm�������ƶ������ٶȣ�ģ��animcore
	�������ƶ����Ĺ켣�ͱ��֡�
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

	/** ����
	*/
	void Reset();

	/** ���¶����ٶȡ��켣
	*/
	void Update( DWORD dwTime ){
		Update( dwTime, Int2Type<bNullAlgorithm>() );
	}

	/** ��Ⱦ
	*/
	void Render(){
		Render( Int2Type< bPlayOnce >() );
	}

	/** �ı���ͼ
	*/
	void SetRenderFilename( const char* pcFilename ){
		memset( m_acFilename, 0, MAX_PATH );
		memcpy_s( m_acFilename, MAX_PATH, pcFilename, MAX_PATH -1 );		
	}

protected:
	/** �Ƿ��������
	*/
	bool ContinueUpdate( DWORD dwTime ){
		return ContinueUpdate( dwTime, Int2Type< bPlayOnce >() );
	}

private:
	/** ֻ����һ��
	*/
	bool ContinueUpdate( DWORD dwTime, Int2Type< true > );
	void Render( Int2Type< true > );

	/** ��ֻ����һ��
	*/
	bool ContinueUpdate( DWORD dwTime, Int2Type< false > );
	void Render( Int2Type< false > );

	/** ���㷨ʱ��update
	*/
	void Update( DWORD dwTime, Int2Type<true> );

	/** �ǿ��㷨ʱ��update
	*/
	void Update( DWORD dwTime, Int2Type<false> );

protected:
	// ͼƬ�ļ���
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
	// �ٶȵļ�����ÿ�����ú��Զ���ʼ
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
		// �ж��Ƿ�ֹͣ���£�����������
		// 1���Ƿ��������ʱ��
		// 2���Ƿ�����Ŀ��Ķ�������
		if( dwTime - AnimAlgorithm::GetStartTime() >= 
			AnimAlgorithm::GetDuration() &&
			AnimCore::GetCurrentAnim() == AnimCore::GetTargetAnim() )
		{
			AnimAlgorithm::Stop();
			// ֹͣ��������
			AnimAlgorithm::SetDelay( -1 );
			// �������ս��
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
	/// ���ö���
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

	/** ��������
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

	/** ������ʼuv��������
	*/
	virtual void SetStartDiceAnimState( unsigned int uiStartState ){
		m_kDice.SetStartAnim( uiStartState );
	}

	/** ����Ŀ��uv��������
	*/
	virtual void SetTargetDiceAnimState( unsigned int uiTargetState ){
		m_kDice.SetTargetAnim( uiTargetState );
	}

	/** ���û�õ�ǰuv����������ɫ��
	*/
	virtual unsigned int GetCurrentDiceAnimState(){
		return m_kDice.GetCurrentAnim();
	}
	virtual void SetCurrentDiceAnimState( unsigned int uiState ){
		m_kDice.SetCurrentAnim( uiState );
	}


	/** ����uv����������������Ϊ���ͺ�·��
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ){
		return true;
	}

	/** ����ͼƬ���򣬸���ui�ľ���ߴ硣����Ϊ���ͺ�rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, 
		int nExtraData = 0 ){
		return true;
	}

	/** ������Ҫ��Ⱦ���ļ���
	*/
	virtual bool SetRenderFilename( unsigned int uiType, const char* pcFilename ){
		return true;
	}

protected:
	/**	��ʼ��uv����
	*/
	virtual void InitUVData()
	{
		// ��������
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