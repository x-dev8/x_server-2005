#pragma once

#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>

#include "Me3d/Vector.h"
//----------------------------------------------------------------------
template <int v> struct Int2Type{ enum { value = v }; };
//----------------------------------------------------------------------
/** ��������
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

	/** �����ĸ��¹���
	*/
	virtual void UpdateAnim() = 0;

	/** ���ص�ǰλ��
	*/
	virtual void SetCurrentAnim( unsigned int uiAnim ){
		m_uiCurrentAnim = uiAnim;
	}
	virtual unsigned int GetCurrentAnim(){
		return m_uiCurrentAnim;
	}

	/** ������ʼ��������״̬
	*/
	virtual void SetStartAnim( unsigned int uiStartAnim ){
		m_uiStartAnim = uiStartAnim;		
	}
	virtual unsigned int GetStartAnim() const{ return m_uiStartAnim; }

	/** ����Ŀ�궯������״̬
	*/
	virtual void SetTargetAnim( unsigned int uiTargetAnim ){
		m_uiTargetAnim = uiTargetAnim;
	}
	virtual unsigned int GetTargetAnim() const{ return m_uiTargetAnim; }

	/** ���Ŀ������������Ⱦ�����յ�Ŀ��������ݲ�ͬ��animcore���ṩ
	*/
	virtual const RECT& GetTargetRect() const = 0;

public:
	bool HaveUpdated() const{ return m_bUpdated; }
	void HaveUpdated( bool bUpdated ){ m_bUpdated = bUpdated; }

protected:
	// ͼƬ�е�λ��
	RECT m_rcSrc;
	unsigned int m_uiCurrentAnim;
	unsigned int m_uiTargetAnim;
	unsigned int m_uiStartAnim;		
	bool m_bUpdated;
};
//----------------------------------------------------------------------
/** ɫ�ӵ��㷨���࣬����仯����(�ٶ�ֵ)��������ĳ��
	�������ź�ֹͣ��
*/
class DiceAlgorithmBase
{
public:
	virtual ~DiceAlgorithmBase(){}

	/** �������м�������
	*/
	virtual void Reset() = 0;

	/** �����ٶȳ�ʼֵ��
	*/
	virtual void SetInitDelay( float fDelay ) = 0;

	/** ȡ�õ�ǰ����ֵ��
	*/
	virtual void SetDelay( float fDelay ) = 0;
	virtual float GetDelay() const = 0;
};
//----------------------------------------------------------------------
/** ��Ĳ�ϵͳ��״̬����
*/
class RollSystemStatusBase : public MeRollStateAlloc<RollSystemStatusBase>
{
public:	
	RollSystemStatusBase(){}
	virtual ~RollSystemStatusBase(){}

	/** ��������
	*/
	virtual void Reset() = 0;

	virtual void InitData() = 0;	

	/** ����״̬���ݣ���uv������Ϣ
	*/
	virtual void Update() = 0;

	/** ��Ⱦ
	*/
	virtual void Render() = 0;

	/** ������ǰ״̬��Ϣ
	*/
	virtual void SetState( unsigned int uiState ) = 0;
	virtual unsigned int GetState() const = 0;

	/** ������ʼuv����������ɫ��
	*/
	virtual void SetStartDiceAnimState( unsigned int uiStartState ) = 0;

	/** ����Ŀ��uv����������ɫ��
	*/
	virtual void SetTargetDiceAnimState( unsigned int uiTargetState ) = 0;

	/** ����/��õ�ǰuv����������ɫ��
	*/
	virtual unsigned int GetCurrentDiceAnimState() = 0;
	virtual void SetCurrentDiceAnimState( unsigned int uiState ) = 0;

	/** ����ͼƬ���򣬸���ui�ľ���ߴ硣����Ϊ���ͺ�rect
	*/
	virtual bool SetPicRect( unsigned int uiType, const RECT& kRect, 
		int nExtraData = 0 ) = 0;

	/** ����uv����������������Ϊ���ͺ�·��
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
		// ����״̬
		m_pkCurrentState->Reset();
		// ���ǰһ��ɫ�ӵ�״̬
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
