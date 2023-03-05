#pragma once
#include "RollSystemBase.h"

//----------------------------------------------------------------------
/** 空算法
*/
class NullDiceAlgorithm : public DiceAlgorithmBase
{
public:
	// ctor
	NullDiceAlgorithm() :
	  m_fDelay(0.f){}

	  /** 开始，停止
	  */
	  virtual void Start(){}
	  virtual void Stop(){}

	  /** 重置所有计算数据
	  */
	  virtual void Reset(){
		  m_fDelay = m_fInitDelay;
	  }

	  /** 设置速度初始值。
	  */
	  virtual void SetInitDelay( float fDelay ){
		  m_fInitDelay = fDelay;
		  m_fDelay = m_fInitDelay;
	  };

	  /** 取得当前曲线值。
	  */
	  virtual void SetDelay( float fDelay ){
		  m_fDelay = fDelay;
	  }
	  virtual float GetDelay() const{
		  return m_fDelay;
	  }

protected:
	float m_fInitDelay;
	float m_fDelay;
};
//----------------------------------------------------------------------
/** 根据幂计算缓慢递减速度曲线
*/
class PowerDiceAlgorithm : public DiceAlgorithmBase
{
public:
	PowerDiceAlgorithm() : 
	  m_nSpeedFactor(0), m_fDelay(0.f), m_fInitDelay(0),
		  m_dwStartTime(0), m_bStartAlgorithm(0), m_bFinished(0){}

	  /** 开始，停止
	  */
	  virtual void Start(){ m_bStartAlgorithm = true; }
	  virtual void Stop(){ m_bStartAlgorithm = false; m_dwStartTime = 0; }
	  virtual bool IsProcessing(){ return m_bStartAlgorithm; }

	  /** 是否根据算法产生了结果
	  */
	  void AlgorithmFinished( bool bFinished ){ m_bFinished = bFinished; }
	  bool AlgorithmFinished() const{ return m_bFinished; }

	  /** 只重置计算中会改变的数据
	  */
	  virtual void Reset(){		  
		  m_fDelay = m_fInitDelay;		  
		  m_dwStartTime = 0;
		  m_bFinished = false;
		  m_bStartAlgorithm = false;
	  }

	  virtual void UpdateAlgorithm( DWORD dwTime );

	  virtual void SetSpeedFactor( int nSpeedFactor ){ 
		  m_nSpeedFactor = nSpeedFactor; }

	  virtual void SetInitDelay( float fDelay ){ 
		  m_fInitDelay = fDelay;
		  m_fDelay = m_fInitDelay;
	  }

	  virtual void SetDelay( float fDelay ){
		  m_fDelay = fDelay;
	  }
	  virtual float GetDelay() const{ return m_fDelay; }

	  DWORD GetStartTime() const{ return m_dwStartTime; }

protected:
	DWORD m_dwStartTime;
	int m_nSpeedFactor;
	float m_fDelay;
	float m_fInitDelay;
	bool m_bStartAlgorithm;
	bool m_bFinished;

};
//----------------------------------------------------------------------
/** PowerDiceAlgorithm的扩展，增加一些条件限制
*/
template< int nSpeedFactor = 1, int nDuration = 5000, 
int nMinDelay = 100, int nMaxDelay = 1000 >
class LimitPowerDiceAlgorithm : public PowerDiceAlgorithm
{
public:
	LimitPowerDiceAlgorithm() : 
	  PowerDiceAlgorithm(){
		  m_nSpeedFactor = nSpeedFactor;
	  }


	  int GetDuration(){ return nDuration; }

	  /** 最大最小值的限制
	  */
	  virtual float GetDelay() const{
		  if( m_fDelay == -1.f )
			  return -1.f;

		  short stSign = m_fDelay / abs( m_fDelay );
		  float fResult = 0.f;
		  if( stSign > 0 )//positive number
			  fResult = max( nMinDelay, min( nMaxDelay, m_fDelay ) );
		  else 
			  fResult = min( nMaxDelay, max( nMinDelay, m_fDelay ) );
		  return fResult;
	  }
};