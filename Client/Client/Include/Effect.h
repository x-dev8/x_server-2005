#pragma once
#ifndef _effect_h
#define _effect_h
#include <windows.h>
#include "Me3d\include.h"
#include "Me3d\Decal.h"
#include "ActionQueue.h"
#include "globalvars.h"
class CPlayer;
class CPlayerAnim;
class CMagicAnim;
class Decal;
#define MAX_PLAYER_EFFECT 1024

//#define _3DMOVE 
class I_PlayerEffect 
{
public:
	enum
	{
		eMaxName = 32
	};
	enum
	{
		eOtherEffect,
		eMexEffect,
	};

public:
	I_PlayerEffect();
	virtual ~I_PlayerEffect();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual BOOL IsDead() = 0;
	virtual void Destroy(){};
	//   added 2004.02.10
	void	SetName( const char* pszName ){ strcpy( m_szName, pszName ); }
	const char* GetName(){ return m_szName; }
	//   added 2004.02.23
	DWORD	GetType(){ return m_dwType; }
	void	SetHitPoint( bool bHas ){ m_bHasHitPoint = bHas; }
protected:
	//   added 2004.02.10
	// һ���ڲ������֣�������ʹ��
	char		m_szName[eMaxName];
	DWORD		m_dwType;
	bool		m_bHasHitPoint;
};

class CFlyTextEffect:I_PlayerEffect, public MeCommonAllocObj<CFlyTextEffect>
{
public:
	enum
	{
		eMiss,
		eMonsterWard,			//�����м�
		eMonsterResist,			//����ֿ�
		eNumberWhite,
		eNumberYellow,
		eNumberRed,
		eNumberGreen,
		eNumberBlue,
		eDodge,					//���
		eBackAttck,				//����
		eDefence,				//�ֿ�
		eWard,					//�м�
		eCruelHit,				//����
		eDeathHit,				//��ɱ
		eResist,				//�ֿ�
        eNumberBeAttackYellow,   //����ҹ���
        eNumberAttackWhite,     //�������
        eNumberAddEXP,          //���Ӿ���
		eNumberBangGong,		// �ﹱ
		eNumberMingWang,		// ����
		eNumberGongXun,			// ��ѫ
		eNumberRongYu,			// ����
		eNumberAreaReputation,  // ��������
		eNumberAddSkillEXP,		//���Ӽ��ܾ���
	};

	enum AddType
	{
		eAddNone,
		eAddBackAttack,
		eAddCruelHit,
		eAddExp,
		eAddBangGong,
		eAddGongXun,
		eAddMingWang,
		eAddAreaReputation,
        eAddSkillExp,
		eAddRongYu
	};

	enum
	{
		eMaxParticle = 128
		,eMaxTextNode = 128
	};

	struct SChar
	{
		char	c;							// ��ĸ
		bool	bExplosive;					// ��ը����
		bool	bAddNumber;					// ������
		bool	bLinkMiddleBottomLine;		// �����м����
		int		x, y;						// λ��
		int		bottom;						// �ײ��ο�����
		int		nWidth, nHeight;			// ��С
		int		nBornWidth, nBornHeight;	// ԭʼ��С
		DWORD	dwBornTime;					// ����ʱ��
		DWORD	dwLife;						// ����
		float	fLastProgress;				// ��һ�����Ž���
		float	fScaleOffset;				//
		float	alpha;

        int     nXOffset;                   //���������x���ƫ�����֮꣬ǰû������ƫ�Ƶ�
        int     nYOffset;
		int     nXDistance;
		int     nYDistance;
		bool    bSecond;
		DWORD   dwSecondTime;
	};

	enum
	{
		eMaxChar = 32,
	};

	struct SParticle
	{
		int				nType;
		AddType			eAddType;
		int				x, y;
		int				nBottom;
		int				nCol;
		int				nWidth, nHeight;
		int				nSrcWidth, nSrcHeight;
		DWORD			dwColor;
		DWORD			dwStartTime;
		DWORD			dwLastUpdateTime;
		DWORD			dwLife;
		BOOL			bNeedUpdatePos;
		BOOL			bShowInLeftLine;
		BOOL			bShowInRightLine;
		BOOL			bLinkBottomLine;
		D3DXVECTOR3		vPos;
		float			fAlpha;
		int				nNumber;
		int				nNumChar;
		int				nMainNumChar;
		SChar			chars[eMaxChar];
		int             nXDistance;
		int             nYDistance;
	};

    struct SFlyConfig
    {
        int nFontType;         //��������
        int nXBaseOffset;     //x����ƫ��
        int nYBaseOffset;     //y����ƫ��
        int nXMaxMoveDis;     //x������ƶ�����
        int nYMaxMoveDis;     //y������ƶ�����
		float fMoveTime;      //�ƶ�ʱ��
		int   nLifeTime;      //����ʱ��
        
        float fInitAlpha;      //��ʼAlphaֵ
        float fOverAlpha;      //����Alphaֵ
        //������ű���
		float fNormalScale;  //��������
        float fMaxScale;     //�������0.3f
		int   nAccel;        //���ٶ�
		std::string strPicPath;  //ͼƬ·��

        void operator=(SFlyConfig &flyconfig)
        {
            nFontType    = flyconfig.nFontType;
            nXBaseOffset = flyconfig.nXBaseOffset;
            nYBaseOffset = flyconfig.nYBaseOffset;  
            nXMaxMoveDis = flyconfig.nXMaxMoveDis;  
            nYMaxMoveDis = flyconfig.nYMaxMoveDis;   
			fMoveTime    = flyconfig.fMoveTime;
			nLifeTime    = flyconfig.nLifeTime;
            fInitAlpha   = flyconfig.fInitAlpha;
            fOverAlpha   = flyconfig.fOverAlpha;
            fMaxScale    = flyconfig.fMaxScale;  //�������0.3f
			fNormalScale = flyconfig.fNormalScale;
			strPicPath   = flyconfig.strPicPath; 
			nAccel       = flyconfig.nAccel;
        }

        SFlyConfig()
        {
            nFontType  = 0;
            nXBaseOffset = 0;
            nYBaseOffset = 192;  
            nXMaxMoveDis = 128;  
            nYMaxMoveDis = 50;
			fMoveTime    = 2.0f;
			nLifeTime    = 0;

            fInitAlpha  = 1.0f;
            fOverAlpha  = 1.0f;

			fNormalScale = 0.0f;
            fMaxScale = 1.0f;  //�������0.3f
			strPicPath.clear();
			nAccel = 0;
        }
    };

	struct STextNode
	{
		int								nID;                        //���ID
		std::list<SParticle>			DynamicParticleList;		//��̬��������
		std::list<SParticle>			StaticParticleList;			//��̬��������
		D3DXVECTOR3						vPos;
	};

public:
	CFlyTextEffect();
    bool InitConfig(); //��ʼ�������ļ�
	void Update();
	void Render();
	BOOL IsDead(){ return FALSE; }

	std::list<STextNode>				m_TextNodeList;
	void	Create( int nType, int x, int y, int nNumber, int nTextNodeID = -1, BOOL bNeedUpdatePos = FALSE, D3DXVECTOR3 vPos = D3DXVECTOR3( 0, 0, 0 ), int nAddNumber = 0, int nWordType = 0);
	BOOL	CreateParticle( int nType, int x, int y, int nNumber, SParticle* pParticle, int nAddNumber = 0, int nWordType = 0);
	void	UpdateTextParticle( int x, int y, SParticle* pParticle);
	void	DrawParticle( SParticle* pParticle );
    void    DrawText(SParticle &Particle);
    void    Draw(RECT &rect,short textureID,DWORD dwColor);
    void    UpdateHpData( int x, int y, SParticle* pParticle);
	int     GetTextureId(std::string &strPic);
	void    CalMovePos(SFlyConfig &config,int nPosX,int nPosY,DWORD dwTime);
	float   GetAlpha(SFlyConfig &flyConfig,int nMoveX,int nMoveY);
protected:
    std::map<int,SFlyConfig> m_FlyEffectConfig;
};
extern CFlyTextEffect* g_pFlyTextEffect;


/*
    ӡ��ͼƬ��
	����Ļָ��λ�� ���Ƴ�һ�� ָ�����͵ı���ͼ���Ϸ���ʾ��Ӧ������ͼƬ��
	�������� 
	/testPrintText ���֣�������
*/
class CPrintTextEffect: public MeCommonAllocObj<CPrintTextEffect>
{
public:

//����һ֡ʱ�䡣
#define ONCEFRAMETIME 30 

	/*
	ӡ������ ָ������ͼ����
	Ŀ����һ֡�������ͬʱ��ʾ����
	*/
	enum PRINTTEXTYPE
	{
		KILLTARGET = 0,  //��ɱ
		PRINTMAX,
	};

	/*
	��ʾģʽ
	*/
	enum PRINTTEXTLOOPMODE
	{
		STATICPRINT = 0, //��̬��
		ONCEPLAYPRINT,   //һ�鲥�Ŷ�̬��
		LOOPPLAYPRINT,   //һֱѭ�����ŵ�
	};

	  

	/*
      ӡ��ͼƬ��Ϣ��	
	*/
	struct PRINTTEXT_INFO
	{
		//==================================
		//����
		DWORD BornTime;        
		DWORD LifeTime;
		bool  Dead; 
		DWORD dwColor;  //������ɫ
		int   Num;
		RECT  _DesRect; //Ŀ������
		POINT _NumOffsetXY;
		PRINTTEXTYPE PrintType; 
		PRINTTEXTLOOPMODE LoopTYpe;

		//======================================
		DWORD LastFrameTime; //��һ֡��ʱ��
		int   LastFrameRow;  //��һ֡���ڵ���
		int   LastFrameCol;  //��һ֡���ڵ���
		bool  bStopLoop;     //�Ƿ����ѭ�� ��ͣ�������һ֡
		bool  bRenderNum;


		void Reset()
		{
			Num = 0;
			BornTime = 0;
			LifeTime = 0;
			Dead = true;
			dwColor = 0xffffffff;
			memset(&_DesRect,0,sizeof(RECT));
			_NumOffsetXY.x = 0;
			_NumOffsetXY.y = 0;

			LastFrameTime = 0;
			LastFrameRow = 0;
			LastFrameCol = 0;
			bStopLoop = false;
			LoopTYpe = STATICPRINT;
			bRenderNum = false;

		}
	};


	
	struct PrintTextconfig 
	{	
		int  Type;               //ӡ������
		RECT  BackTextScreenPos; //��Ļλ��
		POINT NumOffsetByBackTextScreenPos;	
		std::string strBackPicPath;  //��ͼƬ·��
		std::string strNumPicPath;  //����Ƭ·��
		DWORD LifeTime;            //��������
		int NumCharW;             //���ֵĿ��
		int NumCharH;             //���ֵĸ߶�
		int NumCharOffset;        //�������ּ��
		int ColorRow;             //ͼƬ��ɫ��
		int AlphaChangeTime;      //͸���任ʱ��
        
		int PicRowCnt;   //ͼƬ����
		int PicColCnt;   //ͼƬ����
		int LoopType;   //һ��ѭ��
		int RnerNumFrameCnt; //��������֡
		int RenderSpeed;
		

      PrintTextconfig()
      {
        Type = KILLTARGET;
		PicRowCnt = 0;
		PicColCnt = 0;
		LoopType = STATICPRINT;
		AlphaChangeTime= 0;
		RnerNumFrameCnt = 0;
		RenderSpeed = 30;

      }

	};

  typedef std::vector<PRINTTEXT_INFO> TEXTNODELIST; 
 
public: 
	CPrintTextEffect();
	bool Create(int Num , PRINTTEXTYPE _type);
    void Update();
	void Render();

	bool InitConfig(); //��ʼ�������ļ�	


private:
    int  GetTextureId(std::string &strPic);
	void Sort();	
	void UpdateAlpha(); //����͸����
    void RenderNum(PRINTTEXTYPE _type);
	void RenderPrintLoop(PRINTTEXTYPE type ,std::string PicPtch ,bool Once = false);
	void  Draw(RECT &rect,short textureID,DWORD dwColor,int CurRow, int CurCol, int TotalRow, int TotalCol);

	
private:

	TEXTNODELIST m_PrintNodeList;  //�ܹ���
	typedef std::vector<PRINTTEXT_INFO> TYPEVEC; 
	TYPEVEC m_SortInfo[PRINTMAX];
	PRINTTEXT_INFO m_CurPrintInfo[PRINTMAX]; //��ǰ���ڻ��ƵĽڵ�
	std::map<int ,PrintTextconfig> m_PrintConfigVec;

};
extern CPrintTextEffect* g_pPrintTextEffect;


#endif
