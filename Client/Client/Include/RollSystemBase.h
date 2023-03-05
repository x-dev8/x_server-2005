#pragma once

#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>

#include "Me3d/Vector.h"
//----------------------------------------------------------------------
template <int v> struct Int2Type{ enum { value = v }; };
//----------------------------------------------------------------------
/** 动画基类
*/
class RollAnimCoreBase
{
public:

	RollAnimCoreBase(): m_uiCurrentAnim(0), m_uiStartAnim(0),
		m_uiTargetAnim(-1){}

	~RollAnimCoreBase(){}

	virtual void Reset(){
		m_uiTargetAnim = -1;
		m_bUpdated = false;
	}

	/** 动画的更新过程
	*/
	virtual void UpdateAnim() = 0;

	/** 返回当前位置
	*/
	virtual void SetCurrentAnim( unsigned int uiAnim ){
		m_uiCurrentAnim = uiAnim;
	}
	virtual unsigned int GetCurrentAnim(){
		return m_uiCurrentAnim;
	}

	/** 设置起始动画索引状态
	*/
	virtual void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;		
	}
	virtual unsigned int GetStartAnim() const{ return m_uiStartAnim; }

	/** 设置目标动画索引状态
	*/
	virtual void SetTargetAnim( unsigned int uiTargetAnim ){
		m_uiTargetAnim = uiTargetAnim;
	}
	virtual unsigned int GetTargetAnim() const{ return m_uiTargetAnim; }

	/** 获得目标区域，用来渲染，最终的目标区域根据不同的animcore来提供
	*/
	virtual const RECT& GetTargetRect() const = 0;

public:
	bool HaveUpdated() const{ return m_bUpdated; }
	void HaveUpdated( bool bUpdated ){ m_bUpdated = bUpdated; }

protected:
	// 图片中的位置
	RECT m_rcSrc;
	unsigned int m_uiCurrentAnim;
	unsigned int m_uiTargetAnim;
	unsigned int m_uiStartAnim;		
	bool m_bUpdated;
};
//----------------------------------------------------------------------
/** 色子的算法基类，计算变化曲线(速度值)，并根据某个
	给定的信号停止。
*/
class DiceAlgorithmBase
{
public:
	virtual ~DiceAlgorithmBase(){}

	/** 重置所有计算数据
	*/
	virtual void Reset() = 0;

	/** 设置速度初始值。
	*/
	virtual void SetInitDelay( float fDelay ) = 0;

	/** 取得当前曲线值。
	*/
	virtual void SetDelay( float fDelay ) = 0;
	virtual float GetDelay() const = 0;
};
//----------------------------------------------------------------------
/** 类赌博系统的状态基类
*/
class RollSystemStatusBase : public MeRollStateAlloc<RollSystemStatusBase>
{
public:	
	RollSystemStatusBase(){}
	virtual ~RollSystemStatusBase(){}

	/** 重置数据
	*/
	virtual void Reset() = 0;

	virtual void InitData() = 0;	

	/** 更新状态数据，如uv动画信息
	*/
	virtual void Update() = 0;

	/** 渲染
	*/
	virtual void Render() = 0;

	/** 操作当前状态信息
	*/
	virtual void SetState( unsigned int uiState ) = 0;
	virtual unsigned int GetState() const = 0;

	/** 设置起始uv动画索引，色子
	*/
	virtual void SetStartDiceAnimState( unsigned int uiStartState ) = 0;

	/** 设置目标uv动画索引，色子
	*/
	virtual void SetTargetDiceAnimState( unsigned int uiTargetState ) = 0;

	/** 设置/获得当前uv动画索引，色子
	*/
	virtual unsigned int GetCurrentDiceAnimState() = 0;
	virtual void SetCurrentDiceAnimState( unsigned int uiState ) = 0;

	/** 设置图片区域，根据ui的具体尺寸。参数为类型和rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, 
		int nExtraData = 0 ) = 0;

	/** 设置uv动画的声音。参数为类型和路径
	*/
	virtual bool SetUVSound( unsigned int uiType, const char* pcSound ) = 0;
};
//----------------------------------------------------------------------
enum RollSystemType
{
	RST_LuckyGame,
	RST_Lottery,
	RST_Count
};
//----------------------------------------------------------------------
template< RollSystemType eType >
class RollSystemStatusMan
{
public:
	static RollSystemStatusMan* Instance(){
		if( !ms_pkThis )
			Init();
		return ms_pkThis;
	}
	static void Init(){
		if( ms_pkThis )
			return;
		ms_pkThis = MeDefaultNew RollSystemStatusMan;
	}
	static void Destroy(){
		if( ms_pkThis )
			ms_pkThis->RemoveAll();
		MeDefaultDelete ms_pkThis;
		ms_pkThis = 0;
	}

public:	
	void RemoveAll(){
		RollSystemStatusMapIter iter = m_kStates.begin();
		for( ; iter != m_kStates.end(); ++ iter )
		{
			MeDelete (*iter).second;
			(*iter).second = 0;
		}
		m_kStates.clear();
	}
	void AddState( RollSystemStatusBase* pkState ){
		m_kStates[pkState->GetState()] = pkState;
	}
	void RemoveState( RollSystemStatusBase* pkState ){
		m_kStates.erase( pkState->GetState() );
	}
	RollSystemStatusBase* GetState( unsigned int uiState ){
		RollSystemStatusMapIter iter = m_kStates.find( uiState );
		if( iter == m_kStates.end() )
			return 0;
		return (*iter).second;
	}
	void ChangeState( unsigned int uiState ){
		RollSystemStatusMapIter iter = m_kStates.find( uiState );
		if( iter == m_kStates.end() )
			return;

		ChangeState( (*iter).second );
	}
	void ChangeState( RollSystemStatusBase* pkState ){
		RollSystemStatusBase* pkOldState = m_pkCurrentState;
		m_pkCurrentState = pkState;
		// 重置状态
		m_pkCurrentState->Reset();
		// 获得前一个色子的状态
		if( pkOldState )
			m_pkCurrentState->SetStartDiceAnimState( 
			pkOldState->GetCurrentDiceAnimState() );
	}	
	RollSystemStatusBase* GetCurrentState() const{ return m_pkCurrentState; }
	
protected:
	static RollSystemStatusMan* ms_pkThis;

	typedef	std::map< unsigned int, RollSystemStatusBase* > RollSystemStateMap;
	typedef std::map< unsigned int, RollSystemStatusBase* >::iterator RollSystemStatusMapIter;
	RollSystemStateMap m_kStates;

	RollSystemStatusBase* m_pkCurrentState;

private:
	RollSystemStatusMan() : m_pkCurrentState(0){}
};
//----------------------------------------------------------------------
