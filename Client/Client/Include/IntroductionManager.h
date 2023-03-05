#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationLibType.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
#include "Dxsdk/D3DX9Math.h"
#include "GlobalDef.h"
#include "Singleton.h"
#include "RapidXml/MeRapidXml.h"

//��������������
#define INTRO_MOVEPLAYER 235	//�������ø�guide.config ��Ӧ
#define INTRO_LMOUSEOPT 236
#define INTRO_RMOUSEOPT 237
#define INTRO_SPACEOPT 238
#define INTRO_MOVEPLAYER_UP 239
#define INTRO_MOVEPLAYER_DOWN 240
#define INTRO_MOVEPLAYER_LEFT 241
#define INTRO_MOVEPLAYER_RIGHT 242

//������ʾ
#define INTRO_MONSTER_KILL	243		//��ʾ���
#define INTRO_USESKILL		244		//��ʾʹ�ü��ܹ�������
#define INTRO_DROPBAG_OPEN	245		//��ʾ�򿪵������
#define INTRO_RELIVE		246		//��ʾ�������ָ��
#define INTRO_DRINK_DRUG	247		//��ҩ
//�ȼ�����ÿһ���ȼ������Լ�����ʾ��ʽ��ֱ������һ���ȼ��ֶΣ�Ȼ��������ɨ��





class CPlayer;

class CIntroductionManager : public Singleton<CIntroductionManager>
{
public:
	enum eIntroType
	{
		eAboveNpcHeader = 0		// NPCͷ��ð��
		,eUITip					// UIָ��
		,ePopUpIntro			// ����ָ��
		,eOperationIntro		// ����ָ��
		,eUIShowOperator		// UI��ʾָ��
		,eShowUI		// UI��ʾָ��
		,eTotalIntroType
	};
	struct SIntroductionBase : public MeCommonAllocObj<SIntroductionBase>
	{
		SIntroductionBase()
		{
			nIntroId = -1;
			nIntroType = -1;
			nStringId = -1;
			nLevel = -1;
		}
		virtual ~SIntroductionBase(){;}
		virtual bool Show() = 0;
		virtual eIntroType GetIntroductionType() = 0;
		int			nIntroId;
		int			nIntroType;
		int			nStringId;
		int			nLevel;		//����ʱ�ȼ���������
	};
	struct SAboveNpcHeader : public SIntroductionBase
	{
		SAboveNpcHeader()
		{
			nLifeTime = 10;
			nRepeatTime = 1;
		}
		virtual ~SAboveNpcHeader(){;}
		virtual bool Show() ;
		virtual eIntroType GetIntroductionType(){return eAboveNpcHeader;}
		void ShowEx( CPlayer* player );
		string		npcName;
		int			nLifeTime;
		int			nRepeatTime;		//�ظ�����,����ǿͻ�����Ϊ�����������Ч
	};
	struct SUITip : public SIntroductionBase
	{
		SUITip()
		{
			nFrameType = -1;
			nLastTime = 0;			//added by ZhuoMeng.Hu		[9/17/2010]
            nInnerLeft = 0;
            nInnerTop = 0;
            nInnerRight = 0;
            nInnerBottom = 0;
		}
		virtual ~SUITip(){;}
		virtual bool Show() ;
		virtual eIntroType GetIntroductionType(){return eUITip;}
		string		strUIName;
		string		strControlName;
		int			nFrameType;
		int			nLastTime;		// ����ʱ��	added by ZhuoMeng.Hu		[9/17/2010]
        int         nInnerLeft;     // �ڲ����� added by zhuomeng.hu		[10/25/2010]
        int         nInnerTop;
        int         nInnerRight;
        int         nInnerBottom;
	};
	struct OperationIntro : public SIntroductionBase	// ����ָ��
	{
		OperationIntro()
		{
			strDescription = "";
		}
		virtual ~OperationIntro(){;}
		virtual bool Show() {return false;}
		virtual eIntroType GetIntroductionType(){return eOperationIntro;}

		std::string strDescription;
	};
	struct SPopUpIntro : public SIntroductionBase
	{
		SPopUpIntro()
		{
			nTitleStringId = -1;
            nPopType = -1;
		}
		virtual ~SPopUpIntro(){;}
		virtual bool Show() ;
		virtual eIntroType GetIntroductionType(){return ePopUpIntro;}
		int			nTitleStringId;
        int         nPopType;
		virtual bool ShowPopTip() ;
	};

	struct UIShowOperater : public SIntroductionBase
	{
		UIShowOperater()
		{
			strUIName.clear();
			strControlName.clear();
			bShow = false;
		}

		virtual ~UIShowOperater(){;}
		virtual bool Show();
		virtual eIntroType GetIntroductionType(){return eUIShowOperator;}

		std::string strUIName;
		std::string strControlName;
		bool        bShow;
	};


	//=====================================================
	struct UIShow : public SIntroductionBase
	{
		UIShow()
		{
           UI_ID = -1;
		}

		virtual ~UIShow(){;}
		virtual bool Show(){ return false ;}
		virtual eIntroType GetIntroductionType(){return eShowUI;}
        
		int UI_ID;
	};



	enum eFrameType
	{
		eLeftBottom = 0
		,eLeftTop
		,eRightBottom
		,eRightTop
		,eTotalFrameType
	};
	~CIntroductionManager(void);
	CIntroductionManager(void);

	void						ShowTip(int tipId);
	void						ShowTipWithPlayer(int tipId, CPlayer* player );
	void						ShowTipWithLevel( int lvl );
	int							RetrieveIntroductionId(const string& str);
	void						Update();							
	void						ClearStack();			
	int							GetPopUpCount() const { return m_nPopUpCount; }
	void						ShowPopUpTip(int index);
	void						EraseUITipById( int introId );			        // added by ZhuoMeng.Hu		[9/17/2010]
	std::list<SIntroductionBase*>& GetIntroStack() { return m_IntroStack; }

	int							GetRepeatTime( int introId );			//���ִ���

protected:
	bool						LoadTipConfig( );
	SIntroductionBase*			CreateIntro(int id,int type,MeXmlElement* pIntro);
	SIntroductionBase*			FindIntro(int id);
    void                        DirectShowPopUpTip( SPopUpIntro* pPopUp );      // added by zhuomeng.hu		[11/9/2010]

	std::vector<SIntroductionBase*>					m_IntroList;
	std::list<SIntroductionBase*>					m_IntroStack;
	int							m_nPopUpCount;
};