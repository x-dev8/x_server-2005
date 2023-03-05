/***********************************************************
		Create by ZhuoMeng.Hu		[9/16/2010]			
					UI新手帮助Tip
***********************************************************/

#pragma once
#include "MeUi/MeUi.h"
#include "IntroductionManager.h"

class CUINoobTipManager : public Singleton<CUINoobTipManager>
{
public:
	struct NoobTip
	{
		NoobTip();
		void SetTipFormat( int type );		//设置对齐方式
		void AdjustTipFormat();				//调整对齐方式

		ControlFrame*	pFrame;				// 控件框架
		ControlText*	pText;				// 文本控件
		ControlObject*	pFather;			// 被描述的控件
        std::string     strUIFrameName;     // 被描述的控件Frame名
        std::string     strUIControlName;   // 被描述的控件名
		int				nIntroId;			// 对应 Guide 表中 ID
		bool			bShow;				// 是否显示
		int				nFrameType;			// 对齐方式
		int				nStrId;				// 文本描述对应 String ID
		DWORD			nBeginTime;			// 显示时间(秒)
		int				nLastTime;			// 持续时间(秒)		0 = 永久
        int             nInnerLeft;         // 内部坐标
        int             nInnerTop;
        int             nInnerRight;
        int             nInnerBottom;
	};

	typedef std::vector<CIntroductionManager::SIntroductionBase*>	IntroductionList;
	typedef IntroductionList::const_iterator						IntroductionListIterator;
	typedef std::list<CIntroductionManager::SIntroductionBase*>		IntroductionStack;
	typedef IntroductionStack::iterator								IntroductionStackIterator;
	typedef std::vector<NoobTip>									NoobTipList;
	typedef NoobTipList::iterator									NoobTipListIterator;

public:	
	~CUINoobTipManager();

	void		InitNoobTips( const IntroductionList& introVec );       // 初始化
	void		RefreshTipList();                                       // 同步 Introduction 栈
	void		Render();                                               // 渲染

protected:
	bool		CreateControl( int introId );
    void        DestroyControls();
	NoobTip*	FindNoobTipById( int introId );

private:
	NoobTipList		m_noobTipVec;

private:
	friend class Singleton<CUINoobTipManager>;
	CUINoobTipManager();

};
