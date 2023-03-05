/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\����\RankList.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_RankList
#define ID_FRAME_RankList		"ID_FRAME_RankList"
#endif  ID_FRAME_RankList
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_PICTURE_TitleLeftMiddle
#define ID_PICTURE_TitleLeftMiddle		"ID_PICTURE_TitleLeftMiddle"
#endif  ID_PICTURE_TitleLeftMiddle
#ifndef ID_PICTURE_TitleRightMiddle
#define ID_PICTURE_TitleRightMiddle		"ID_PICTURE_TitleRightMiddle"
#endif  ID_PICTURE_TitleRightMiddle
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_CHECKBOX_Type0
#define ID_CHECKBOX_Type0		"ID_CHECKBOX_Type0"
#endif  ID_CHECKBOX_Type0
#ifndef ID_CHECKBOX_Type1
#define ID_CHECKBOX_Type1		"ID_CHECKBOX_Type1"
#endif  ID_CHECKBOX_Type1
#ifndef ID_CHECKBOX_Type2
#define ID_CHECKBOX_Type2		"ID_CHECKBOX_Type2"
#endif  ID_CHECKBOX_Type2
#ifndef ID_CHECKBOX_Type3
#define ID_CHECKBOX_Type3		"ID_CHECKBOX_Type3"
#endif  ID_CHECKBOX_Type3
#ifndef ID_CHECKBOX_Type4
#define ID_CHECKBOX_Type4		"ID_CHECKBOX_Type4"
#endif  ID_CHECKBOX_Type4
#ifndef ID_CHECKBOX_Type5
#define ID_CHECKBOX_Type5		"ID_CHECKBOX_Type5"
#endif  ID_CHECKBOX_Type5
#ifndef ID_PICTURE_TypeWall
#define ID_PICTURE_TypeWall		"ID_PICTURE_TypeWall"
#endif  ID_PICTURE_TypeWall
#ifndef ID_PICTURE_ExplainWall
#define ID_PICTURE_ExplainWall		"ID_PICTURE_ExplainWall"
#endif  ID_PICTURE_ExplainWall
#ifndef ID_LIST_SubTypeList
#define ID_LIST_SubTypeList		"ID_LIST_SubTypeList"
#endif  ID_LIST_SubTypeList
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_TEXT_Wait
#define ID_TEXT_Wait		"ID_TEXT_Wait"
#endif  ID_TEXT_Wait
#ifndef ID_BUTTON_LeftHead
#define ID_BUTTON_LeftHead		"ID_BUTTON_LeftHead"
#endif  ID_BUTTON_LeftHead
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_BUTTON_RightHead
#define ID_BUTTON_RightHead		"ID_BUTTON_RightHead"
#endif  ID_BUTTON_RightHead
#ifndef ID_TEXT_TypeText
#define ID_TEXT_TypeText		"ID_TEXT_TypeText"
#endif  ID_TEXT_TypeText
#ifndef ID_TEXT_Page
#define ID_TEXT_Page "ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_TEXT_Information
#define ID_TEXT_Information "ID_TEXT_Information"
#endif  ID_TEXT_Information

#include "UiBase.h"
class CUI_ID_FRAME_RankList :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_RankList();
private:
	void ResetMembers();

	ControlFrame*	m_pID_FRAME_RankList;
	//ControlPicture*	m_pID_PICTURE_TitleDi;
	//ControlText*	m_pID_TEXT_Title;
	ControlPicture*	m_pID_PICTURE_TitleLeftMiddle;
	ControlPicture*	m_pID_PICTURE_TitleRightMiddle;
	ControlPicture*	m_pID_PICTURE_TitleLeft;
	ControlPicture*	m_pID_PICTURE_TitleRight;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_Help;
	//ControlPicture*	m_pID_PICTURE_Wall;
	ControlCheckBox*	m_pID_CHECKBOX_Type0;
	ControlCheckBox*	m_pID_CHECKBOX_Type1;
	ControlCheckBox*	m_pID_CHECKBOX_Type2;
	ControlCheckBox*	m_pID_CHECKBOX_Type3;
	ControlCheckBox*	m_pID_CHECKBOX_Type4;
	ControlCheckBox*	m_pID_CHECKBOX_Type5;
	ControlPicture*	m_pID_PICTURE_TypeWall;
	ControlPicture*	m_pID_PICTURE_ExplainWall;
	ControlList*	m_pID_LIST_SubTypeList;
	ControlText*	m_pID_TEXT_Explain;
	ControlText*	m_pID_TEXT_Wait;
	ControlText*	m_pID_TEXT_TypeText;
	ControlText*	m_pID_TEXT_Page;
	ControlText*	m_pID_TEXT_Information;
	ControlButton*	m_pID_BUTTON_LeftHead;
	ControlButton*	m_pID_BUTTON_Left;
	ControlButton*	m_pID_BUTTON_Right;
	ControlButton*	m_pID_BUTTON_RightHead;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	void ID_LIST_SubTypeListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_TypeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_LeftHeadOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightHeadOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	//--------------------------------------------------------

	struct RankInfo 
	{
		typedef std::string RankType;
		typedef std::map<std::string, std::string> ValueSet;
		ValueSet values;
		RankType type;
	};

	struct RankSortFuncInfo 
	{
		std::string luaFunc;	// lua������
		std::string key;		// RankInfo.values��key����Rank��PlayerName
		bool isUpperSort;		// �Ƿ���������
		ControlText* arrow;		// ������ͼ��
		ControlButton* button;  // ����ť

		RankSortFuncInfo() : isUpperSort(false), arrow(0), button(0) {}
	};

	/*bool LoadRank(const std::string& filename);*/

	void LoadFrame(const std::string& filename, const char* frameName);
	void UnLoadFrame(const std::string& filename);

	void SetFrameVisible(const char* frameName, bool visible);

	// ����������
	void SetRankSortFunc(const char* frameName, const char* relativeControlId, const char* relativeArrowControlId, const char* luaFunc, const char* key);

	// �����ı�����
	void SetControlCheckBoxText(const char* frameName, const char* controlId, const char* text);
	void SetControlText(const char* frameName, const char* controlId, const char* text);
	void SetControlButtonText(const char* frameName, const char* controlId, const char* text);

	/* ����List���ӹ�ϵ������ID_FRAME_RankChild1��Ķ���List(��)��Ӧһ��List(��)��
	   �����������¼���ѡ��ʱ��ֻ�и�List���У�Ȼ�󴫸�ÿһ����List
	*/
	void AssociateList(const char* frameName, const char* fatherControlId, const char* childControlId, int drawFormat);
	
	void AssociateListImg(const char* frameName, const char* fatherControlId, const char* controlId, int drawFormat);

	// ���һ��List����
	void AddListItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data, bool bLeftModle);
	//������ݵ�ListImage
	void AddListImageItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data/*, int nRow, int nCol*/);
	//������ݵ�ListImage
	void AddListImageCharItem(const char* frameName, const char* controlId, const char* text, unsigned int color, const char* data/*, int nRow, int nCol*/);
	// ɾ��List����
	void ClearList(const char* frameName, const char* controlId);
	//ɾ��ListImage����
	void ClearListImage(const char* frameName, const char* controlId);

	// �õ�type���͵����а�����
	int GetRankRowSize(const char* type);
	// �õ�type���͵�row�У���column�У�Rank.config��Ӧ�����ݣ���columnΪRank��PlayerName�ȵȣ�����
	const char* GetRankContent(const char* type, int row,  const char* column);

	// �õ�ְҵ����
	const char* GetProfessionName(int type);

	// �õ��������
	const char* GetMeName();

	// �õ���������
	const char* GetGuildName();

	// ���а�����
	static bool ID_BUTTON_SortOnButtonClick( ControlObject* pSender );
	static bool _RankSortFunc(const RankInfo* v1, const RankInfo* v2);

	void Log(const std::string& log);
	void Log(const std::string& log, int priority);

	//��õ�ǰ��ҳ��
	int GetCurrentPageIndex() { return m_nCurrentPage; }

	//���ÿҳ��ʾ����
	int GetShowNumPerPage() { return m_nShowNumPerPage; }

	//����˵������
	void SetExplain(int);

	//�����Լ��ȼ�˵��
	void SetInfomation(const char*);

	//�������ͱ���
	void SetTileText(const char* szText);

	//��ù�������
	const char* GetCountryName(int nCountryId) const;

	// �Ҽ�
	static void ListRBClick( ControlObject* pSender, ControlList::S_List* pItem );

	ControlFrame* GetFrame() { return m_pID_FRAME_RankList; }

private:
	std::string m_luaFilename;

	long m_bNeedUpdate;

	time_t m_loadTime;

	std::vector<ControlCheckBox*> m_pageCheckBoxs;
	ControlCheckBox* m_pActivedCheckBox;
	ControlFrame*	 m_pActivedFrame;

	typedef std::map<ControlList*, ControlListImage* > RelativeImgSet;
	RelativeImgSet m_relativeImgSet;

	typedef std::map<ControlList*, std::vector<ControlList*> > RelativeSet;
	RelativeSet m_relativeSet;

	typedef std::map<RankInfo::RankType, std::vector<RankInfo*> > RankInfoSet;
	RankInfoSet m_rankInfoSets;	// �������а���Ϣ

	std::vector<RankInfo*>* m_pCurrRankInfos;	//ָ��ǰ��ʾ������

	typedef std::list<RankInfo> RankInfoList;
	RankInfoList m_allRankInfos;			// �����������а���Ϣ��m_rankInfoSets::iterator.secondͨ��ָ��ָ����Щ����
	RankInfoList m_allBackgroupRankInfos;	// ��̨����ʹ�ã���װ���´����m_allRankInfos��Ȼ�����m_rankInfoSets

	typedef std::map<std::string, std::map<std::string, RankSortFuncInfo> > RankSortInfoSet;
	RankSortInfoSet m_rankSortInfos; // ����������Ϣ

	// ����
	void _SortRank();

	// ��ǰ��������
	std::map<std::string, RankSortFuncInfo> m_currPageSortFuncInfos;

	// ��̨�������ݵ�m_allBackgroupRankInfos�У�Ȼ��ͨ��m_bNeedUpdate�����߳��и���m_allRankInfos��m_rankInfoSets
	static DWORD WINAPI _BackgroupLoadRank(LPVOID lpParam);
	HANDLE m_hThread;

	void _ReadRankInfos();

	void _RefreshRankInfos();
	void _SortAndRefreshRankInfos();

private:
	void SetSort();
	void RefreshPageInfo();
	void SetCurrentPageText();

	int m_nCurrentRow;
	int m_nCurrentPage;
	int m_nShowNumPerPage;

	mutable std::string m_strCountryName;
};
extern CUI_ID_FRAME_RankList s_CUI_ID_FRAME_RankList;

namespace Rank
{
	CUI_ID_FRAME_RankList* GetRank();
}
