#pragma once
#include "RollSystemBase.h"

//----------------------------------------------------------------------
/** ���㷨
*/
class NullDiceAlgorithm : public DiceAlgorithmBase
{
public:
	// ctor
	NullDiceAlgorithm() :
	  m_fDelay(0.f){}

	  /** ��ʼ��ֹͣ
	  */
	  virtual void Start(){}
	  virtual void Stop(){}

	  /** �������м�������
	  */
	  virtual void Reset(){
		  m_fDelay = m_fInitDelay;
	  }

	  /** �����ٶȳ�ʼֵ��
	  */
	  virtual void SetInitDelay( float fDelay ){
		  m_fInitDelay = fDelay;
		  m_fDelay = m_fInitDelay;
	  };

	  /** ȡ�õ�ǰ����ֵ��
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
/** �����ݼ��㻺���ݼ��ٶ�����
*/
class PowerDiceAlgorithm : public DiceAlgorithmBase
{
public:
	PowerDiceAlgorithm() : 
	  m_nSpeedFactor(0), m_fDelay(0.f), m_fInitDelay(0),
		  m_dwStartTime(0), m_bStartAlgorithm(0), m_bFinished(0){}

	  /** ��ʼ��ֹͣ
	  */
	  virtual void Start(){ m_bStartAlgorithm = true; }
	  virtual void Stop(){ m_bStartAlgorithm = false; m_dwStartTime = 0; }
	  virtual bool IsProcessing(){ return m_bStartAlgorithm; }

	  /** �Ƿ�����㷨�����˽��
	  */
	  void AlgorithmFinished( bool bFinished ){ m_bFinished = bFinished; }
	  bool AlgorithmFinished() const{ return m_bFinished; }

	  /** ֻ���ü����л�ı������
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
/** PowerDiceAlgorithm����չ������һЩ��������
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

	  /** �����Сֵ������
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