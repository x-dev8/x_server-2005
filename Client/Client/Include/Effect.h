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
	// 一个内部的名字，供查找使用
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
		eMonsterWard,			//怪物招架
		eMonsterResist,			//怪物抵抗
		eNumberWhite,
		eNumberYellow,
		eNumberRed,
		eNumberGreen,
		eNumberBlue,
		eDodge,					//躲避
		eBackAttck,				//背击
		eDefence,				//抵抗
		eWard,					//招架
		eCruelHit,				//暴击
		eDeathHit,				//必杀
		eResist,				//抵抗
        eNumberBeAttackYellow,   //被玩家攻击
        eNumberAttackWhite,     //攻击玩家
        eNumberAddEXP,          //增加经验
		eNumberBangGong,		// 帮贡
		eNumberMingWang,		// 名望
		eNumberGongXun,			// 功勋
		eNumberRongYu,			// 荣誉
		eNumberAreaReputation,  // 地区声望
		eNumberAddSkillEXP,		//增加技能经验
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
		char	c;							// 字母
		bool	bExplosive;					// 爆炸性字
		bool	bAddNumber;					// 附加字
		bool	bLinkMiddleBottomLine;		// 紧贴中间底线
		int		x, y;						// 位置
		int		bottom;						// 底部参考坐标
		int		nWidth, nHeight;			// 大小
		int		nBornWidth, nBornHeight;	// 原始大小
		DWORD	dwBornTime;					// 出生时间
		DWORD	dwLife;						// 生命
		float	fLastProgress;				// 上一个播放进度
		float	fScaleOffset;				//
		float	alpha;

        int     nXOffset;                   //这里添加在x轴的偏移坐标，之前没有左右偏移的
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
        int nFontType;         //字体类型
        int nXBaseOffset;     //x坐标偏移
        int nYBaseOffset;     //y坐标偏移
        int nXMaxMoveDis;     //x轴最大移动距离
        int nYMaxMoveDis;     //y轴最大移动距离
		float fMoveTime;      //移动时间
		int   nLifeTime;      //生命时间
        
        float fInitAlpha;      //初始Alpha值
        float fOverAlpha;      //最终Alpha值
        //最大缩放比例
		float fNormalScale;  //正常缩放
        float fMaxScale;     //必须大于0.3f
		int   nAccel;        //加速度
		std::string strPicPath;  //图片路径

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
            fMaxScale    = flyconfig.fMaxScale;  //必须大于0.3f
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
            fMaxScale = 1.0f;  //必须大于0.3f
			strPicPath.clear();
			nAccel = 0;
        }
    };

	struct STextNode
	{
		int								nID;                        //玩家ID
		std::list<SParticle>			DynamicParticleList;		//动态的数字组
		std::list<SParticle>			StaticParticleList;			//静态的数字组
		D3DXVECTOR3						vPos;
	};

public:
	CFlyTextEffect();
    bool InitConfig(); //初始化配置文件
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
    印章图片类
	在屏幕指定位置 绘制出一张 指定类型的背景图，上方显示对应的数字图片。
	测试命令 
	/testPrintText 数字，数量。
*/
class CPrintTextEffect: public MeCommonAllocObj<CPrintTextEffect>
{
public:

//定义一帧时间。
#define ONCEFRAMETIME 30 

	/*
	印章类型 指定背景图类型
	目的在一帧的情况下同时显示多种
	*/
	enum PRINTTEXTYPE
	{
		KILLTARGET = 0,  //击杀
		PRINTMAX,
	};

	/*
	显示模式
	*/
	enum PRINTTEXTLOOPMODE
	{
		STATICPRINT = 0, //静态的
		ONCEPLAYPRINT,   //一遍播放动态的
		LOOPPLAYPRINT,   //一直循环播放的
	};

	  

	/*
      印章图片信息。	
	*/
	struct PRINTTEXT_INFO
	{
		//==================================
		//公用
		DWORD BornTime;        
		DWORD LifeTime;
		bool  Dead; 
		DWORD dwColor;  //数字颜色
		int   Num;
		RECT  _DesRect; //目标区域
		POINT _NumOffsetXY;
		PRINTTEXTYPE PrintType; 
		PRINTTEXTLOOPMODE LoopTYpe;

		//======================================
		DWORD LastFrameTime; //上一帧的时间
		int   LastFrameRow;  //上一帧所在的行
		int   LastFrameCol;  //上一帧所在的列
		bool  bStopLoop;     //是否结束循环 并停留在最后一帧
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
		int  Type;               //印章类型
		RECT  BackTextScreenPos; //屏幕位置
		POINT NumOffsetByBackTextScreenPos;	
		std::string strBackPicPath;  //底图片路径
		std::string strNumPicPath;  //数字片路径
		DWORD LifeTime;            //生命周期
		int NumCharW;             //数字的宽度
		int NumCharH;             //数字的高度
		int NumCharOffset;        //两个数字间距
		int ColorRow;             //图片颜色行
		int AlphaChangeTime;      //透明变换时间
        
		int PicRowCnt;   //图片行数
		int PicColCnt;   //图片列数
		int LoopType;   //一次循环
		int RnerNumFrameCnt; //播放数字帧
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

	bool InitConfig(); //初始化配置文件	


private:
    int  GetTextureId(std::string &strPic);
	void Sort();	
	void UpdateAlpha(); //更新透明度
    void RenderNum(PRINTTEXTYPE _type);
	void RenderPrintLoop(PRINTTEXTYPE type ,std::string PicPtch ,bool Once = false);
	void  Draw(RECT &rect,short textureID,DWORD dwColor,int CurRow, int CurCol, int TotalRow, int TotalCol);

	
private:

	TEXTNODELIST m_PrintNodeList;  //总管线
	typedef std::vector<PRINTTEXT_INFO> TYPEVEC; 
	TYPEVEC m_SortInfo[PRINTMAX];
	PRINTTEXT_INFO m_CurPrintInfo[PRINTMAX]; //当前正在绘制的节点
	std::map<int ,PrintTextconfig> m_PrintConfigVec;

};
extern CPrintTextEffect* g_pPrintTextEffect;


#endif
