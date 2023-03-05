#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "MessageDefine.h"
#include "bag/ItemBag2.h"
#include "Pack.h"
#include "playerrole.h"
#include "XmlStringLanguage.h"
#include "MeUI/ExpressionManager.h"
#include "color_config.h"
#include "ShowScreenText.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "script_manager.h"
#include "PackItemEnableManager.h"

//
//  static assert.
//
#ifndef BOOST_STATIC_ASSERT
namespace boost{

	// HP aCC cannot deal with missing names for template value parameters
	template <bool x> struct STATIC_ASSERTION_FAILURE;

	template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

	// HP aCC cannot deal with missing names for template value parameters
	template<int x> struct static_assert_test{};

}

#define BOOST_STATIC_ASSERT( B ) \
	typedef ::boost::static_assert_test<\
	sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
	> boost_static_assert_typedef_

#endif

#define EquipUIHelper_DeclareMaterialFun(index)	\
public: \
	bool CanSetMaterial##index(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag) {	\
	return _CanSetMaterialT(pSender, pItemDrag,	\
	&EquipUIHelper::_CanSetMaterial##index##Callback);	\
}	\
	\
	bool SetMaterial##index(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag) {	\
	return _SetMaterialT(pSender, pItemDrag, index,	\
	&EquipUIHelper::CanSetMaterial##index,	\
	&EquipUIHelper::SetMaterial##index##Index,	\
	&EquipUIHelper::_SetMaterial##index##Callback);	\
}	\
	void SetMaterial##index##Index(int bagIndex) { \
	_SetMaterialIndex(index, bagIndex);	\
}	\
	void ClearMaterial##index##() { \
	SetMaterial##index##Index(-1);	\
	m_pMaterialBag[index] = NULL;	\
	m_pMaterialBagListImg[index] = NULL;	\
	m_material[index].itembaseinfo.ustItemID = InvalidLogicNumber;	\
	_ClearMaterial##index##Callback();	\
} \
	\
protected: \
	virtual bool _CanSetMaterial##index##Callback(ControlObject* pSender, \
	ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCommon* pDragItemCommon) { return true; } \
	virtual void _SetMaterial##index##Callback(ControlIconDrag::S_ListImg& item) {}	\
	virtual void _ClearMaterial##index##Callback() {}



template <class T, class Func>
struct SeachMaterialFunc
{
	SeachMaterialFunc(T* _Obj, Func _Func) : obj(_Obj), func(_Func)
	{
	}

	bool seach(ControlIconDrag* pPack)
	{
		if( !pPack )
			return false;
		std::map<unsigned short, ControlIconDrag::S_ListImg*> materials0;
		for (int i = 0; i < pPack->GetItemCnt(); ++i)
		{
			ControlIconDrag::S_ListImg* pListImg = pPack->GetItemByIndex(i);
			if (!pListImg || pListImg->m_pkIconInfo->IsNull())
				continue;

			bool ret = (obj->*func)(pPack, pListImg);
			if (ret)
				materials0[pListImg->m_pkIconInfo->Id()] = pListImg;
		}

		if (!materials0.empty())
			return (obj->*func)(pPack, materials0.begin()->second);

		return false;
	}

	bool operator()()
	{
		if (seach(s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)))
			return true;
		if (seach(s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag)))
			return true;
		return false;
	}

	T* obj;
	Func func;
};

template <class T, class Func>
static bool SeachMaterialAndSetMaterial(T* obj, Func func)
{
	SeachMaterialFunc<T, Func> seach(obj, func);
	return seach();
}

template <const unsigned int MaxMaterialCount = 2>
class EquipUIHelper
{
	BOOST_STATIC_ASSERT( MaxMaterialCount >= 1 && MaxMaterialCount <= 3 );

public:
	EquipUIHelper()
	{
		m_equipBagIndex = -1;
		memset(m_materialBagIndex, -1, sizeof(m_materialBagIndex));
		m_bShowError = true;
		m_bNeedUpdate = false;
	}

	virtual ~EquipUIHelper()
	{

	}

	bool CanSetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
	{
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
		if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
			pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
		{
			ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
			if( !pImageSender )
				return false;

			// 包裹里
			if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
			{
				ItemDefine::SItemCanEquip* pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
				return _CanSetEquipCallback(pSender, pItemDrag, pCanEquip);
			}
		}	
		return false;
	}

	bool SetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
	{
		if (!CanSetEquip(pSender, pItemDrag))
			return false;

		int index = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
		if (index == -1)
			return false;

		SetEquipIndex(index);

		// 刷新装备ICON
		ControlIconDrag::S_ListImg item = *pItemDrag;
		item.m_eEnable = eIcon_Enable;
		m_equip = *(SCharItem*)(item.m_pkIconInfo->GetData());

		m_equipEnable = false;
		m_bNeedUpdate = true;

		_SetEquipCallback(item);

		// 搜索背包材料自动填充
		_SeachMaterial();
		return true;
	}

	void SetEquipIndex(int index)
	{
		if (m_equipBagIndex != -1)
		{
			m_equipEnable = true;
			RefreshEquipIconEnable();
		}

		m_equipBagIndex = index;
	}

	void Clear()
	{
		ClearEquip();
		m_bNeedUpdate = false;
	}

	void ClearEquip()
	{
		SetEquipIndex(-1);
		m_equip.itembaseinfo.ustItemID = InvalidLogicNumber;

		ClearMaterial0();
		if (MaxMaterialCount > 1) ClearMaterial1();
		if (MaxMaterialCount > 2) ClearMaterial2();

		_ClearEquipCallback();
	}

	void Update()
	{
		if (!m_bNeedUpdate)
			return;

		RefreshBagIconEnable();
		m_bNeedUpdate = false;
	}

	SCharItem* GetEquipItem()
	{
		if (m_equipBagIndex != -1)
			return &thePlayerRole.m_bag.m_pPackItem[m_equipBagIndex];
		return 0;
	}

	void ShowError(const int id)
	{
		if (m_bShowError)
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Mail_Receive, theXmlString.GetString(id) );
	}

	void SetShowError(bool b) { m_bShowError = b; }
	bool GetShowError() { return m_bShowError; }

	EquipUIHelper_DeclareMaterialFun(0);
	EquipUIHelper_DeclareMaterialFun(1);
	EquipUIHelper_DeclareMaterialFun(2);

protected:

	template <class CanSetMaterialCallbackFun>
	bool _CanSetMaterialT(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, CanSetMaterialCallbackFun canSetMaterialCallbackFun)
	{
		if (m_equip.itembaseinfo.ustItemID == InvalidLogicNumber)
			return false;

		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
		if( pItemCommon )
		{
			ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
			if( !pImageSender )
				return false;

			return (this->*canSetMaterialCallbackFun)(pSender, pItemDrag, pItemCommon);
		}	
		return false;
	}

	template <class CanSetMaterialFun, class SetMaterialIndexFun, class SetMaterialCallbackFun>
	bool _SetMaterialT(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, int index,
		CanSetMaterialFun canSetMaterialFun, SetMaterialIndexFun setMaterialIndexFun, SetMaterialCallbackFun setMaterialCallbackFun)
	{
		if (!(this->*canSetMaterialFun)(pSender, pItemDrag))
			return false;

		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
		ItemDefine::SItemCommon* pRepairItem = GettheItemDetail().GetItemByID( pItemCommon->ustItemID );
		switch (pRepairItem->ucItemType)
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
			m_pMaterialBagListImg[index] = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
			m_pMaterialBag[index] = &thePlayerRole.m_bagMaterial;
			m_bagTypeMateral[index] = BT_MaterialBag;
			break;
		case ItemDefine::ITEMTYPE_TASK:
			m_pMaterialBagListImg[index] = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
			m_pMaterialBag[index] = &thePlayerRole.m_bagTask;
			m_bagTypeMateral[index] = BT_TaskBag;
			break;
		default:
			m_pMaterialBagListImg[index] = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
			m_pMaterialBag[index] = &thePlayerRole.m_bag;
			m_bagTypeMateral[index] = BT_NormalItemBag;
			break;
		}

		int idx = m_pMaterialBagListImg[index]->GetItemIndex( pItemDrag );
		if (idx == -1)
			return false;

		(this->*setMaterialIndexFun)(idx);

		// 刷新修理道具ICON
		ControlIconDrag::S_ListImg item = *pItemDrag;
		item.m_eEnable = eIcon_Enable;
		item.m_pkIconInfo->m_bShowCount = false;
		m_material[index] = *(SCharItem*)(item.m_pkIconInfo->GetData());

		m_materialEnable[index] = false;
		m_bNeedUpdate = true;

		(this->*setMaterialCallbackFun)(item);
		return true;
	}

	void _SetMaterialIndex(int index, int bagIndex) {
		if (m_materialBagIndex[index] != -1)
		{
			m_materialEnable[index] = true;
			RefreshMaterialIconEnable();
		}

		m_materialBagIndex[index] = bagIndex;
	}

	void RefreshBagIconEnable()
	{
		RefreshEquipIconEnable();
		RefreshMaterialIconEnable();
	}

	void RefreshEquipIconEnable()
	{
		if( m_equipBagIndex != -1 )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_equipBagIndex, true );
		}
	}

	void EquipUIHelper::RefreshMaterialIconEnable()
	{
		for (int i = 0; i < MaxMaterialCount; ++i)
		{
			if( m_materialBagIndex[i] != -1 )
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( m_pMaterialBag[i], m_materialBagIndex[i], true );
			}
		}
	}

	// 搜索背包材料自动填充
	void _SeachMaterial()
	{
		SetShowError(false);

		SeachMaterialAndSetMaterial(this, &EquipUIHelper::SetMaterial0);
		if (MaxMaterialCount > 1)
			SeachMaterialAndSetMaterial(this, &EquipUIHelper::SetMaterial1);
		if (MaxMaterialCount > 2)
			SeachMaterialAndSetMaterial(this, &EquipUIHelper::SetMaterial2);

		SetShowError(true);
	}

	virtual bool _CanSetEquipCallback(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag, ItemDefine::SItemCanEquip* pDragItemCanEquip) { return true; }
	virtual void _SetEquipCallback(ControlIconDrag::S_ListImg& item) {}
	virtual void _ClearEquipCallback() {}

protected:
	SCharItem m_equip;
	int m_equipBagIndex;
	bool m_equipEnable;

	int m_materialBagIndex[MaxMaterialCount];
	bool m_materialEnable[MaxMaterialCount];
	SCharItem m_material[MaxMaterialCount];
	ControlListImage* m_pMaterialBagListImg[MaxMaterialCount];
	CItemBag2* m_pMaterialBag[MaxMaterialCount];
	int m_bagTypeMateral[MaxMaterialCount];

	int m_needMoney;

	Vector m_vVisiblePos;

	bool m_bNeedUpdate;
	bool m_bShowError;
};

// template <class T>
// class ResultViewer
// {
// public:
// 	ResultViewer() : m_obj(0),
// 		m_rectObj(0), m_hasAck(false), m_isStart(false), m_result(0) {}
// 	virtual ~ResultViewer() {}
// 
// 	void Initialize(T* obj, void (T::*_PmShowResultRunc)(unsigned short),
// 		const char* frameName)
// 	{
// 		m_obj = obj;
// 		_PmemShowResultRunc = _PmShowResultRunc;
// 		m_frameName = frameName;
// 
// 		char buf[256];
// 		MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1, "%s/Data/Config/Ui.string", GetRootPath());
// 		m_luaFilename = buf;
// 
// 		try
// 		{
// 			ScriptManager::instance().executeFileDefault( m_luaFilename );
// 
// 			LuaFunction<const char*> AnimFilename( ScriptManager::instance().getLuaStateOwner(),
// 				(m_frameName + "_AnimFilename").c_str() );
// 			const char* szAnimFilename = AnimFilename();
// 
// 			LuaFunction<int> AnimFrameNumer( ScriptManager::instance().getLuaStateOwner(),
// 				(m_frameName + "_AnimFrameNumber").c_str() );
// 			int nAnimFrameNumber = AnimFrameNumer();
// 
// 			LuaFunction<int> AnimTime( ScriptManager::instance().getLuaStateOwner(),
// 				(m_frameName + "_AnimTime").c_str() );
// 			int nAnimTime = AnimTime();
// 
// 			LuaFunction<const char*> AreaControlId( ScriptManager::instance().getLuaStateOwner(),
// 				(m_frameName + "_AreaControlId").c_str() );
// 			const char* szAreaCtrlId = AreaControlId();
// 
// 			RECT rc;
// 			m_rectObj = (ControlObject*)theUiManager.FindControl(frameName, szAreaCtrlId);
// 			if (m_rectObj)
// 				m_rectObj->GetRealRect(&rc);
// 
// 			m_slideAnim.Initialize((char*)szAnimFilename, nAnimFrameNumber, rc, nAnimTime);
// 		}
// 		catch ( const LuaPlus::LuaException& )
// 		{
// 		}
// 	}
// 
// 	void InitStatus()
// 	{
// 		try
// 		{
// 			ScriptManager::instance().executeFileDefault( m_luaFilename );
// 
// 			LuaFunction<void> func( ScriptManager::instance().getLuaStateOwner(),
// 				_GetInitFuncName().c_str() );
// 			func();
// 		}
// 		catch ( const LuaPlus::LuaException& )
// 		{
// 		}
// 	}
// 
// 	void Start()
// 	{
// 		m_slideAnim.StartAnimation(HQ_TimeGetTime());
// 		m_isStart = true;
// 
// 		try
// 		{
// 			ScriptManager::instance().executeFileDefault( m_luaFilename );
// 
// 			LuaFunction<void> func( ScriptManager::instance().getLuaStateOwner(),
// 				_GetStartFuncName().c_str() );
// 			func();
// 		}
// 		catch ( const LuaPlus::LuaException& )
// 		{
// 		}
// 	}
// 
// 	void Update()
// 	{
// 		if (m_isStart)
// 		{
// 			RECT rc;
// 			if (m_rectObj)
// 				m_rectObj->GetRealRect(&rc);
// 			m_slideAnim.Update(HQ_TimeGetTime(), &rc);
// 			if (!m_slideAnim.IsInAnimation())
// 			{
// 				_ShowResult();
// 			}
// 		}
// 	}
// 
// 	void ProcessResult(unsigned short result)
// 	{
// 		m_result = result;
// 		m_hasAck = true;
// 
// 		// 火焰停止了
// 		if (!m_slideAnim.IsInAnimation())
// 		{
// 			_ShowResult();
// 		}
// 	}
// 
// 	bool IsStart() const { return m_isStart; }
// 
// protected:
// 	void _ShowResult()
// 	{
// 		if (m_hasAck)
// 		{
// 			(m_obj->*_PmemShowResultRunc)(m_result);
// 
// 			try
// 			{
// 				ScriptManager::instance().executeFileDefault( m_luaFilename );
// 
// 				LuaFunction<void> func( ScriptManager::instance().getLuaStateOwner(),
// 					_GetShowResultFuncName().c_str() );
// 				func();
// 			}
// 			catch ( const LuaPlus::LuaException& )
// 			{
// 			}
// 		}
// 
// 		if (m_isStart)
// 		{
// 			m_isStart = false;
// 			m_slideAnim.UnRelativePicResource();
// 		}
// 	}
// 
// 	std::string _GetStartFuncName()
// 	{
// 		return m_frameName + "_Start";
// 	}
// 
// 	std::string _GetShowResultFuncName()
// 	{
// 		return m_frameName + "_ShowResult";
// 	}
// 
// 	std::string _GetInitFuncName()
// 	{
// 		return m_frameName + "_Init";
// 	}
// 
// protected:
// 	T* m_obj;
// 	void (T::*_PmemShowResultRunc)(unsigned short);
// 	CSlideAnimation m_slideAnim;
// 	ControlObject* m_rectObj;
// 
// 	bool m_hasAck;
// 	bool m_isStart;
// 	unsigned short m_result;
// 
// 	std::string m_frameName;
// 	std::string m_luaFilename;
// };
// 
