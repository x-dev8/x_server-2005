/***********************************************************
		Create by ZhuoMeng.Hu		[9/16/2010]			
					UI���ְ���Tip
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
		void SetTipFormat( int type );		//���ö��뷽ʽ
		void AdjustTipFormat();				//�������뷽ʽ

		ControlFrame*	pFrame;				// �ؼ����
		ControlText*	pText;				// �ı��ؼ�
		ControlObject*	pFather;			// �������Ŀؼ�
        std::string     strUIFrameName;     // �������Ŀؼ�Frame��
        std::string     strUIControlName;   // �������Ŀؼ���
		int				nIntroId;			// ��Ӧ Guide ���� ID
		bool			bShow;				// �Ƿ���ʾ
		int				nFrameType;			// ���뷽ʽ
		int				nStrId;				// �ı�������Ӧ String ID
		DWORD			nBeginTime;			// ��ʾʱ��(��)
		int				nLastTime;			// ����ʱ��(��)		0 = ����
        int             nInnerLeft;         // �ڲ�����
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

	void		InitNoobTips( const IntroductionList& introVec );       // ��ʼ��
	void		RefreshTipList();                                       // ͬ�� Introduction ջ
	void		Render();                                               // ��Ⱦ

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
