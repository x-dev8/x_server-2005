/*****************************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 		UiParseData.h
* Create: 	10/10/08
* Desc:		The class is are used in the syntax parsing in ControlList and ControlText.
* Author:	yanli
*****************************************************************************************/
#pragma once
#include "MeUi/ControlObject.h"
enum EKeyType
{
	eKeyNormal			= 0,
	eKeyColor			= 0x1,
	eKeyItem			= 0x2,
	eKeyImg				= 0x4,
	eKeyAddress			= 0x8,
	eKeyNpc				= 0x10,
	eKeyPlayer			= 0x20,
	eKeyHyper			= 0x40,
	eKeyChatExp			= 0x80,
    eKeyCountry         = 0x100,
	eKeyEnd
};

struct UiParseData
{
	EKeyType 		m_type;		// 类型
	unsigned long	m_col;		// 颜色
	std::wstring	m_str;		// 文本内容
	void*				m_pInfo;		// 表情动画数据
	int					m_nTextureID;	// 贴图ID
	RECT				m_rc;			// 有效区域

	void InitAndSetColor(const DWORD col = 0)
	{
		Init();
		m_col = col;
	}

	void Init()
	{
		m_col = 0;
		m_str.clear();
		m_type = eKeyNormal; 
		m_pInfo = NULL; 
		m_nTextureID = -1;
		m_rc.bottom = m_rc.left = m_rc.right = m_rc.top = 0;
	}
};

#include "IconManager.h"
typedef struct UiCallbackDataBase : public MeCommonAllocObj<UiCallbackDataBase>  
{
	UiCallbackDataBase() { m_pTipInfo = NULL; }
	virtual ~UiCallbackDataBase()
	{
		if (m_pTipInfo != NULL)
		{
			delete m_pTipInfo;
		}
	};

	virtual int			GetType() =0;
	virtual void*		GetData() =0;
	virtual void		Destory()
	{
		if( m_pTipInfo == theIconInfoMouseTip.GetIconInfo() )
			theIconInfoMouseTip.Clear();
		delete this;
	}

	void SetTip(const char* tip,DWORD dwAlign = DT_CENTER | DT_VCENTER)
	{
		if( NULL == tip )
			return;

		if (!m_pTipInfo)
		{
			m_pTipInfo = MeNew S_TextTipInfo();
		}
			
		m_pTipInfo->SetInfo( tip ,dwAlign);
	}

	S_TextTipInfo* m_pTipInfo;
} UiCallbackDataBase;

typedef std::vector<UiCallbackDataBase*> UiCallbackDataArr;