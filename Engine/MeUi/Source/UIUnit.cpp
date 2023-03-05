#include "Meui/UIUnit.h"
#include "FuncPerformanceLog.h"
#include "ErrorLog.h"
#include "Meui/UILoadMgrBase.h"
//////////////////////////////////////////////////////////////////////////
//

CUILoadMgrBase* CUIUnit::m_uiLoadMgr = NULL;
CUIUnit::CUIUnit()
{
	guardfunc;
	m_bUILoad = false;
	m_BornTime = 0;
	m_LastVisibleTime = 0;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
//
CUIUnit::~CUIUnit()
{
	guardfunc;
	unguard;
}


//////////////////////////////////////////////////////////////////////////
//// 设置是否可视
void CUIUnit::_SetVisable( const bool bVisable )
{
	guardfunc;

	return;
	unguard;
}


void CUIUnit::SetVisable( const bool bVisable )
{
	if (bVisable)
	{
		if (!m_bUILoad)
		{
			m_bUILoad = true;
			m_BornTime = HQ_TimeGetTime();
			if (GetUIMgr())
			{
				GetUIMgr()->AddUI(this);
			}
			_LoadUI();
		}
	}
	if (m_bUILoad)
	{
		_SetVisable(bVisable);
	}
}

bool CUIUnit::LoadUI()
{
	bool ret = false;
	if (IsHoldInMemory())
	{
		if (!m_bUILoad)
		{
			m_bUILoad = true;
			m_BornTime = HQ_TimeGetTime();
			if (GetUIMgr())
			{
				GetUIMgr()->AddUI(this);
			}
			ret = _LoadUI();
		}
	}
	return ret;
}

bool CUIUnit::UnLoadUI()
{
	if (m_bUILoad)
	{
		m_bUILoad = false;
		return _UnLoadUI();
	}
	return false;
}

bool CUIUnit::IsVisable()
{
	if (!m_bUILoad)
	{
		return false;
	}
	return _IsVisable();
}
