
#include "Meui/UILoadMgrBase.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"




void CUILoadMgrBase::AddUI( CUIUnit *pObj )
{
	UIBaseList& UiList = GetUIList(pObj);
	for(UIBaseIter iter = UiList.begin(); iter!=UiList.end();++iter)
	{
		if (*iter == pObj)
		{
			return;
		}
	}
	UiList.push_front(pObj);
}

void CUILoadMgrBase::DelUI( CUIUnit *pObj )
{
	if (pObj)
	{
		UIBaseList& UiList = GetUIList(pObj);
		for(UIBaseIter iter = UiList.begin(); iter!=UiList.end();++iter)
		{
			if (*iter == pObj)
			{
				pObj->UnLoadUI();
				UiList.erase(iter);
				return;
			}
		}
	}
}
void CUILoadMgrBase::Init()
{
	m_UILifeTime = 300000;
}


extern int g_nTheRoleProfession;

void CUILoadMgrBase::loadUIs()
{
	guardfunc;
    
    // 加载常驻内存的UI，其他的为动态加载
    for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
    {
        if( ( *it )->IsHoldInMemory() )
            ( *it )->LoadUI();
    }

	unguard;
}

void CUILoadMgrBase::clearUIs()
{
	guardfunc;

    theIconDragManager.ClearDrag();
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		pUI->SetVisable(false);
	}

	for(UIBaseIter iter = m_OtherList.begin(); iter != m_OtherList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		if (pUI->IsUILoad())
		{
			pUI->UnLoadUI();
		}
	}
	m_OtherList.clear();
	unguard;
}


CUILoadMgrBase::UIBaseList			& CUILoadMgrBase::GetUIList( CUIUnit* pUi )
{
	if (pUi->IsHoldInMemory())
	{
		return m_HoldInMemoryList;
	}
	return m_OtherList;

}

void CUILoadMgrBase::ClearHideUI()
{
	DWORD nCurrtime = HQ_TimeGetTime();
	UIBaseIter iter = m_OtherList.begin();
	while(iter != m_OtherList.end())
	{
		CUIUnit* pUI = *iter;
		if (pUI->IsUILoad())
		{
			if (!pUI->IsVisable())
			{
				if (nCurrtime - pUI->GetLastVisibleTime() > m_UILifeTime)
				{
					pUI->UnLoadUI();
					iter = m_OtherList.erase(iter);
					continue;
				}
			}
			else
			{
				pUI->SetLastVisibleTime(nCurrtime);
			}
		}
		else
		{
			iter = m_OtherList.erase(iter);
			continue;
		}
		++iter;
	}
}

void CUILoadMgrBase::Destory()
{
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		pUI->UnLoadUI();
	}
	m_HoldInMemoryList.clear();
	
	for(UIBaseIter iter = m_UIList.begin(); iter != m_UIList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		if (pUI)
		{
			pUI->UnLoadUI();
		}
	}
	m_UIList.clear();
}

void CUILoadMgrBase::InitAtEnterWorld()
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if( ( *it )->IsHoldInMemory() )
			( *it )->SetVisable( true );
	}

	for( UIBaseIter iter = m_UIList.begin(); iter != m_UIList.end(); ++iter )
    {
        ( *iter )->InitializeAtEnterWorld();
    }
}

//-------------------------------------------------------------------------------------------------------------------------
const int OffsetX = 10;
inline void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs)
{
	if (lhs.left > rhs.left)
	{
		lhs.left = rhs.left;
	}
	if (lhs.right < rhs.right)
	{
		lhs.right = rhs.right;
	}
}

RECT GetBigRect(ControlFrame* pFrame)
{
	RECT rect = { 0, 0, 0, 0}, rectTemp;
	if (!pFrame)
	{
		return rect;
	}

	pFrame->GetRealRect(&rect);
	const std::vector<ControlFrame*> frameVector = pFrame->m_vtChildFrame;
	for (std::vector<ControlFrame*>::const_iterator iter = frameVector.begin(); iter != frameVector.end(); ++iter)
	{
		if (!(*iter))
		{
			continue;
		}
		(*iter)->GetRealRect(&rectTemp);
		SetContainRect(rect, rectTemp);
	}
	return rect;
}

void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight)
{
	if (!pLeft || !pRight)
	{
		return;
	}

	RECT leftRect = GetBigRect(pLeft);
	RECT rightRect = GetBigRect(pRight);

	RECT scrLeftRect;
	pLeft->GetRealRect(&scrLeftRect);
	int leftOffsetX = leftRect.left - scrLeftRect.left;

	RECT scrRightRect;
	pRight->GetRealRect(&scrRightRect);
	int rightOffsetX = rightRect.left - scrRightRect.left;

	int rightWidth = rightRect.right - rightRect.left;
	int leftWidth = leftRect.right - leftRect.left;
	if (leftRect.right + rightWidth + OffsetX> SCREEN_WIDTH)
	{
		rightRect.right = SCREEN_WIDTH;
		rightRect.left = rightRect.right - rightWidth;
		leftRect.right = rightRect.left - OffsetX;
		leftRect.left = leftRect.right - leftWidth;
	}
	else
	{
		rightRect.left = leftRect.right + OffsetX;
	}

	scrLeftRect.left = leftRect.left - leftOffsetX;
	scrRightRect.left = rightRect.left - rightOffsetX;

	pLeft->MoveTo(scrLeftRect.left, scrLeftRect.top);
	pRight->MoveTo(scrRightRect.left, scrLeftRect.top);
}

void CUILoadMgrBase::ResetDevice()
{
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		pUI->ResetDevice();
	}

	for(UIBaseIter iter = m_OtherList.begin(); iter != m_OtherList.end();++iter)
	{
		CUIUnit* pUI = *iter;
		if (pUI->IsUILoad())
		{
			pUI->ResetDevice();
		}
	}

}

void CUILoadMgrBase::RefreshByItemChange()
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if( ( *it )->IsVisable() )
			( *it )->RefreshByItemChange();
	}

}

void CUILoadMgrBase::RefreshByMoneyChange()
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if( ( *it )->IsVisable() )
			( *it )->RefreshByMoneyChange();
	}
}

