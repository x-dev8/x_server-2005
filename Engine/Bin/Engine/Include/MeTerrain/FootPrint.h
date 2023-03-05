/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	FootPrint.h
* Create: 	10/06/2006
* Desc:		数据资源基类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_FOOT_PRINT_H__
#define _MAP_FOOT_PRINT_H__


class CNdlDecalRes;
////////////////////////////////////////////////////////////////////////////////
struct CFootDecalRes : public MeCommonAllocObj<CFootDecalRes>
{
	CFootDecalRes(int texture);
	~CFootDecalRes();
	void			DecreaseAlpha();
	CNdlDecalRes*	m_pRes;
	BYTE			mcAlpha;
	bool			m_bEnble;
	static BYTE		alphaDelta;
};
typedef std::list<CFootDecalRes*	> decalResArr;
class CFootPrintMgr : public Singleton<CFootPrintMgr>
{
public:
	CFootDecalRes* RetriveFootDecelByTextureId(int texture);
	void			AddToCache(CFootDecalRes* pRes)
	{
		m_ResCachePool.push_front(pRes);
	}
	void			Render();
	~CFootPrintMgr();

	void			clear();

	bool Empty() const;

	CFootPrintMgr();
protected:
	std::vector<int> m_TextureTypeArr;
	decalResArr m_ResCachePool; 
	decalResArr m_ResPool; 
};
class CFootPrint : public MeCommonAllocObj<CFootPrint>
{
public:
	enum eFootPrintType
	{
		eTwoFoot = 0,
		eFourFoot
	};
	enum ePlayerFootPrintType
	{
		SnowPrint = 0
		,SandPrint
		,TotalPlayerPrintType
	};
					CFootPrint(bool val);
	virtual			~CFootPrint();				
	void			Update();
	void			Render();
	void			Reset();
	void			AddFootPrint(D3DVECTOR pos,flt32 m_angle);
	void			SetDeltaForBody(float val) { m_fdeltaForBody = val; }
	void			SetFootPrintType(int val) { m_footPrintType = val; }
	float			GetStepLength() const { return m_stepLength; }
	void			SetStepLength(float val) { m_stepLength = val; }
	void			SetScale(float val) { m_scale = val; }
	void			SetFootTex(int leftBackTex,int rightFrontTex)
	{
		m_leftOrBackFootId = leftBackTex;
		m_rightOrFrontFootId = rightFrontTex;
	}

	int GetCurrTexture( int printType );
	bool GetPrintInfo( CWorldChunk* pChunk, CResMgr* pMgr, int &printType, int &printLevel ,bool* bPrintExistArr);
	bool GetMonster() const { return m_isMonster; }
	void SetMonster(bool val) { m_isMonster = val; }
protected:
	bool			m_bRightOrFront;
	bool			m_isMonster;
	int			m_leftOrBackFootId;
	int			m_rightOrFrontFootId;
	int				m_footPrintType;
	float			m_fdeltaForBody;
	float			m_stepLength;
	float			m_scale;
	decalResArr		m_renderRes;

	DWORD		m_oldTime;
	static	DWORD	m_timeInterval;
	static  bool	m_intialize;
	static	char*	m_TypeIdentify[TotalPlayerPrintType];
	static  int		m_texId[TotalPlayerPrintType][2];
};


#endif	// _MAP_FOOT_PRINT_H__

