#pragma once

#include "GlobalDef.h"
#include "MeUi/IconManager.h"
#include "MeUi/ControlList.h"
#include "ItemDetail.h"
class S_IconInfoHero : public S_IconInfoBase
{
public:
	static void ReplaceSpecifiedName( unsigned short ustLevel, Common::_tstring& tstrName );
	static DWORD GetQualityColor( int nItemLevel );
	static DWORD GetPetShowColor(SPetItem *m_petItem);
	static const char* GetItemName( unsigned char* data );
	static int GetItemLevel( unsigned char* data );
	static void GlobalParseText( ControlList::S_List::STextData& kTextData, const std::wstring& wstrOutText, EKeyType eType, 
		int& nLineHeight, ControlList::S_List* pkThis);
	static void GlobalParseText_HighShout( ControlList::S_List::STextData& kTextData, const std::wstring& wstrOutText, EKeyType eType, 
		int& nLineHeight, ControlList::S_List* pkThis);
public:// Virtual Function
	unsigned short& Id();
	int& Count();
	bool& IsLocked();
	int& MaxCount();
	DWORD& SpareTime();
	DWORD GetSpareTime();
	bool& IsNextLvl();
	bool IsNull();
	bool SetData( IN void* pData, 
		const bool bShowCount = false, 
		const bool bNext = false, 
		IN bool bCompareData = false,
		IN int nPlayerID = -1 );
	bool SetData( const int nId, 
		const int nCount,
		const bool bShowCount = false,
		const bool bNext = false, 
		IN INT nCompareId = InvalidLogicNumber,
		IN int nPlayerID = -1,
		const bool bIsBound = false );

	bool SetSkillData(  );

	bool operator==( IN S_IconInfoBase& stIconInfoBase );
	bool PlaySound();
	void SetSpareTime(DWORD dwSpareTime, int nStartTime );
	void SetFlag( eTipFlag eFlag ){ m_eFlag = eFlag ; }
	eTipFlag GetFlag(){ return m_eFlag; }
	virtual stIconInfo* GetIconInfoByIndex( int nIndex ){
		if( nIndex >= 0 && nIndex < MAX_ICON_INFO_EX_LINE_COUNT )
			return &m_stInfo[nIndex];
		return 0;
	}
	virtual stIconInfo* GetOtherIconInfoByIndex( int nIndex ){
		if( nIndex >= 0 && nIndex < MAX_ICON_OTHER_INFO_EX_LINE_COUNT )
			return &m_stOtherInfo[nIndex];
		return 0;
	}

	virtual void DisplayIcon( IN RECT* prcDst, COLORREF col,
						int nFontIndex, int nFontSize,
						COLORREF colFont, eIconDrawState bEnable = eIcon_Enable,ControlFrame* pFatherFrame = NULL);

	void RefreshColorFrameType();

	virtual unsigned short GetItemId(){ return m_stItem.itembaseinfo.ustItemID; }
	virtual __int64 GetOnlyId(){ return m_stItem.itembaseinfo.nOnlyInt; }
	virtual void* GetData(){ return &m_stItem; }
	virtual void Clone( S_IconInfoBase* pkInfo );
	virtual void Clear();

public:
	static float GetAttributeWithLevel( int nEquipType, float fAttribute, short stLevel );
	static int GetAttributeWithLevel( int nEquipType, int nAttribute, short stLevel );	

public:// Virtual Function
	void SetInfoRightText();	
	std::string& IconFileName();
	std::string& DisableIconFileName();
	std::string& ShopIconFileName();
	int Cost();
	void SetCost( int nCost ){ m_nCost = nCost; }
	void SetOnlyId( __int64 nGuid ){ m_stItem.itembaseinfo.nOnlyInt = nGuid; }
    virtual void SetUsableEffEnable( bool bEnable ) { m_bEnableUsableEff = bEnable; }             // �Ƿ���ʾ����ʹ�õĺ�ɫ
	virtual int& IsItemLocked()    { return m_bItemLocked;}

	void ShowBaseInfo(	    void* pItemDetail, INT nType );                 // ��Ʒ�����ơ�Icon�� (����)

	void ShowEquipCommon(   void* pItemDetail, INT nType );                 // װ������
	void ShowWeapon(	    void* pItemDetail, INT nType );                 // ��������
	void ShowArmour(	    void* pItemDetail, INT nType );                 // ��������
    void ShowArmourSkill(	void* pItemDetail, INT nType, int nPlayerID );  // ���ߵ���װ���ܣ���ʱû��
    void ShowEquipRand(     void* pItemDetail, INT nType );                 // װ�����������
    void ShowEquipGemInlay( void* pItemDetail, INT nType );                 // װ���Ŀ׺ͱ�ʯ��Ƕ
    void ShowEquipSuit(	    void* pItemDetail, INT nType, int nPlayerID );  // װ������װ����
    void ShowEquipDescribe( void* pItemDetail, INT nType );                 // װ�����������ۼ�
    void ShowSuitAttribute( int nCount, INT nType, void* pItemDetail, DWORD dwColor );  // װ������װ����
	void ShowRandomEvaluateUI( unsigned short usValue, unsigned short usEvalType );     // װ����������ʱû��
	void ShowEquipScore(	void* pItemDetail, INT nType );					// װ������

	void ShowSuit(void* pItemDetail, INT nType,int nPlayerID);								// ��װ����
	void ShowSuitAtter(unsigned int ItemID,DWORD Color,int Count);
	void EquipBaseRand( void* pItemDetail, INT nType ,DWORD Color);

	void ShowSkill(		    void* pItemDetail, INT nType );                 // ����Tip
    void ShowGem(           void* pItemDetail, INT nType );                 // ��ʯTip
	void ShowMaterial(           void* pItemDetail, INT nType );                 // ����Tip
    void ShowRestore(       void* pItemDetail, INT nType );                 // ����ƷTip
    void ShowOthers(        void* pItemDetail, INT nType );
	void ShowPetEquip(SCharItem& pItem, void* pItemDetail, INT nType );

	void WriteSkillData( void* pSkillData, bool bIsNextLevel = false );
	void WriteProduceSkillData( void* pSkillData );
	void WriteSkillTreeData( void* pSkillData );
	void WriteStatusData( void* pStatusData, bool bIsNextLevel = false );
	void WriteSkillRestricData( void* pSkillData );

	static unsigned short GetEquipRandomEvaluate(unsigned short usItemID, unsigned short usEvalType, const std::vector<unsigned short>& vectorRandID);
	static unsigned short GetEquipRandomEvaluate( void* pItemDetail, INT nType, unsigned short usEvalType, const SCharItem& stItem );
	
    static int GetRandValueByType( ItemDefine::SRandAttribute* pArmourRand, int i );
    static std::string GetBaseAttrStringByType( int iType );
    static std::string GetRandStringByType( int iType );
    void ChangeToSoulStampTip( std::string& strDes, float fValue );     // ת����������̺������
    void MouseTipDrawLine();

public:
	stIconInfoEx	m_stInfo[MAX_ICON_INFO_EX_LINE_COUNT];
	stIconInfoEx	m_stOtherInfo[MAX_ICON_OTHER_INFO_EX_LINE_COUNT];

	SCharItem m_stItem;
	SCharItem m_stCompareItem;
	//
	int m_nCount;	
	bool m_bLocked;
	int m_bItemLocked;          //0:û�� 1:�� 2:����

	int m_nMaxCount;
	std::string m_strIconFileName;
	std::string m_strDisableIconFileName;
	std::string m_strShopIconFileName;
	std::string m_strSoundName;
	int m_nCost;

	//����icon��ʱ��  �߻�Ҫ�� > 999 m ����ʾ ��ʼ��Ϊ0, == 0 ʱҲ����ʾ
	DWORD m_dwSpareStartTime;
	DWORD m_dwSpareTime;	//bufʣ�µ�ʱ��

	bool m_bNextLvl;

	eTipFlag m_eFlag;
    int m_nProfession[5];

private:
    bool m_bItemCanTrade;       // �Ƿ�ɽ���           added by zhuomeng.hu		[11/9/2010]
    bool m_bItemCanBeUsed;      // �Ƿ����ʹ�û�װ��   added by zhuomeng.hu		[11/25/2010]
    bool m_bEnableUsableEff;    // �Ƿ���ʾ����ʹ�õĺ�ɫ   added by zhuomeng.hu		[11/25/2010]

public:
	S_IconInfoHero();
};