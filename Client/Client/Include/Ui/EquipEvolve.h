/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Soul.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "GlobalDef.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "GlobalDef.h"
#include "MessageDefine.h"
#include "ItemDetail.h"
#include "Ui/UIBase.h"
#include "ItemEnableChangeSysBase.h"


#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_TEXT_Effect
#define ID_TEXT_Effect			"ID_TEXT_Effect"
#endif	ID_TEXT_Effect
#ifndef ID_TEXT_Success
#define ID_TEXT_Success			"ID_TEXT_Success"
#endif	ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail			"ID_TEXT_Fail"
#endif	ID_TEXT_Fail
class EquipEvolveUI : public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Start,
		EffectStatus_Fail,
		EffectStatus_Success
	};
	 EquipEvolveUI();
	 ControlFrame* GetFrame() const { return m_pID_FRAME_EquipEvolve; }

	 ControlFrame*	m_pID_FRAME_EquipEvolve;
	 ControlText*	m_pID_TEXT_Money;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlPicture*	m_pID_PICTURE_Begin;
	 ControlListImage*	m_pID_LISTIMG_Equip;
	 ControlPicture*	m_pID_PICTURE_StarEffect;
	 ControlText*	m_pID_TEXT_TipAllDone;
	 ControlText* m_pID_TEXT_SuccessRatio;
	 ControlText*	m_pID_TEXT_Effect;
	 ControlText*	m_pID_TEXT_Success;
	 ControlText*	m_pID_TEXT_Fail;

	 ControlCheckBox*	m_pID_CHECKBOX_X1;
	 ControlCheckBox*	m_pID_CHECKBOX_X2;
	 ControlCheckBox*	m_pID_CHECKBOX_X3;
	 ControlCheckBox*	m_pID_CHECKBOX_X4;

	 ControlText*	m_pID_TEXT_MaterialNum;
	 ControlText*	m_pID_TEXT_ProtectMaterial;
	 
	 ControlCheckBox*	m_pID_CHECKBOX_Protect_NoUse;
	 ControlCheckBox*	m_pID_CHECKBOX_Protect_SixStar;
	 ControlCheckBox*	m_pID_CHECKBOX_Protect_NineStar;
	 ControlCheckBox*	m_pID_CHECKBOX_Protect_TwelStar;
	 ControlCheckBox*	m_pID_CHECKBOX_Protect_FiftStar;
	 ControlCheckBox*	m_pID_CHECKBOX_Never_Prompt;
	 ControlText*		m_pID_TEXT_T3;
	 ControlText*		m_pID_TEXT_T4;

private://from CUIBase	

	virtual void	RefreshByItemChange();						// 物品改变导致的界面更新
	virtual void	RefreshByMoneyChange();			        // 金钱改变导致的界面更新

public:
	virtual bool UpdateGem();
	void RefreshEquipInfo();
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	virtual void RefreshOkButton();

    // 会改变背包的 Enable 态的系统需要的接口       added by zhuomeng.hu		[12/30/2010]
    virtual bool IsPackItemBeUsing( __int64 nGuid );
	//添加一个标志表示是否通过背包中的快捷按钮打开UI
	void SetIsPocket(bool bValue){m_bIsPocket = bValue;}
	bool GetIsPocket(){return m_bIsPocket;}
	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}
protected:

	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	DWORD dwBeginTime;
	EffectStatus m_status;
	bool m_bSendMsg;
	bool  m_bIsPocket;					//是不是通过背包打开升星UI
	static const int				m_nsMaxMaterialNum = MsgEquipEvolve::EConstDefine_MaxMaterialCount;
	virtual int			GetEvolveType() = 0;
	virtual int			GetEvolveMaterialType() = 0;
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg) = 0;
	virtual int			GetEvolveMoneyCost();
	virtual float		GetEvolveProbability();
	virtual char*		GetSlideEffectPath() {return NULL;}
	virtual void		TipVisible(bool IsMaterialExist) = 0;
	virtual bool		IsMatchOther(ItemDefine::SCreateMaterial* pMaterial){return true;}
	virtual bool		IsMatchEquipType(ItemDefine::SItemCommon* pItemCommon);
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);


	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual void		RefreshAllBagEnable();
	virtual void		ClearEquip();
	virtual void		SetAtomVisible( bool bVisible );
	virtual void		ResetUIObjects();

	virtual void		RefreshBeginPic();


	virtual bool		OnDirty();
	virtual void		OnRender();
	virtual bool		OnOkClick();
	virtual bool		OnEquipDragOn( ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender ,short	stEquipBagType = BT_NormalItemBag);
	virtual bool		OnMaterialDragOn( ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender ,short	stEquipBagType = BT_MaterialBag);

	virtual void		SendEvolveMsg();

	void				ResetEquipEvolve();
	void				OnSetVisable( const bool bVisable );
	void				EquipEvolveIntialize();
	void				SetDirty( bool bDirty ){ m_bNeedUpdate = bDirty; }
	bool				IsDirty(){ return m_bNeedUpdate; }
	virtual void				RefreshNeedMoney();
	virtual void				RefreshProbability();

	ControlIconDrag::S_ListImg * RetriveMaterialImg(short itemId,int& nIndex);
	virtual bool		MatchMaterialOption(SCharItem* pItem){return true;}

	void				SetTip3Show(SCharItem* pEquipItem, unsigned short usMaterialId);

	short			m_stEquipBagType;			//作用物品背包
	short			m_stEquipBagIndex;			// 作用物品Index
	__int64			m_stEquipBagGuid;			//作用物品Guid
	bool			m_bEquipBagEnable;

	short			m_shMaterialBagType[m_nsMaxMaterialNum];    //宝石背包类型
	short			m_stMaterialIndex[m_nsMaxMaterialNum];		// 宝石Index
	__int64			m_n64MaterialGuid[m_nsMaxMaterialNum];	// 宝石Guid
	bool			m_bMaterialBagEnable[m_nsMaxMaterialNum];

	std::vector<short>				m_MatchMaterialArray;


	int							m_nSelectMaterialIndex;
	ControlIconDrag::S_ListImg* m_pSelectItem;
	void				SetSelectItem(ControlIconDrag::S_ListImg* pItem);



	bool			m_bNeedUpdate;			 // 刷新界面

	Vector			m_vVisiblePos;			 // 升星界面打开时的人物位置,用来自动关闭时使用

	CSlideAnimation m_slideAnim;			//序列帧动画
	bool			m_bStartAnim;

	short			m_stMaterialUseNum;		//使用材料的数量
	uint8			m_unProtectStarNum;		//保护的星级


	bool					IsNearAttackAttribute(ItemDefine::SItemCanEquip* pCanEquip);
	bool					IsLongAttackAttribute(ItemDefine::SItemCanEquip* pCanEquip);
	bool					IsMagicAttackAttribute(ItemDefine::SItemCanEquip* pCanEquip);
	void					AddAttackString( ItemDefine::SItemCanEquip* pWeapon, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul);

	void					AddDefendString( ItemDefine::SItemArmour* pWeapon, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul);

	void					AddHpMpString( ItemDefine::SItemArmour* pWeapon, SCharItem* pItem, ControlList* pList, bool bNextLevel ,bool bSoul);

	int						GetItemLevel(unsigned short ustItemID );
	short					GetItemMaterialType( unsigned short ustId );

	void					FillBlueAttriList( ControlIconDrag::S_ListImg* pEquipImg ,ControlList* pLIST_Attribute);

	void					SetCheckNumBox(int num);
	void					SetProtectStarBox(uint8 unstar);
	bool					HasMaterialItem(unsigned short usID);

};

//#ifndef ID_TEXT_Effect
//#define ID_TEXT_Effect			"ID_TEXT_Effect"
//#endif	ID_TEXT_Effect
//#ifndef ID_TEXT_Success
//#define ID_TEXT_Success			"ID_TEXT_Success"
//#endif	ID_TEXT_Success
//#ifndef ID_TEXT_Fail
//#define ID_TEXT_Fail			"ID_TEXT_Fail"
//#endif	ID_TEXT_Fail
//class UiEffectBase
//{
//public:
//	enum EffectStatus
//	{
//		EffectStatus_No,
//		EffectStatus_Start,
//		EffectStatus_Fail,
//		EffectStatus_Success
//	};
//	ControlText*	m_pID_TEXT_Effect;
//	ControlText*	m_pID_TEXT_Fail;
//	ControlText*	m_pID_TEXT_Success;
//	UiEffectBase();
//	~UiEffectBase();
//	bool DoControlConnect(IN const char* szFrameID);
//	void Render();
//	void SetStatus(EffectStatus status)
//	{
//		m_eStatus = status;
//	}
//	void SetStartTime(DWORD dwTime){m_StartTime = dwTime;}
//private:
//	DWORD m_StartTime;
//	EffectStatus m_eStatus;
//};