

#include "hotkeybag.h"
#include "ItemDetail.h"


CHotkeyBag::CHotkeyBag( )
{
	m_iBagSize = 0;
	m_pHotkeyData = NULL;
}

CHotkeyBag::~CHotkeyBag( )
{

}

//��ʼ��
void CHotkeyBag::CreateFromData( SMouseItem *pHotkeyData, int iBagSize )
{
	m_pHotkeyData = NULL;
	m_iBagSize    = 0;

	m_pHotkeyData = pHotkeyData;
	m_iBagSize    = iBagSize;
}

//��һ���յ�λ��
int  CHotkeyBag::FindNullHotkeyOffSet( )
{
	//int iLoop;
	//for( iLoop=0;iLoop<m_iBagSize;iLoop++ )
	//{
	//	if( m_pHotkeyData[iLoop].type==SMouseItem::TypeNull )
	//		return iLoop;
	//}

	return -1;
}

//���ÿ��
bool CHotkeyBag::PushItem( SMouseItem &item, short stIndex )
{
	int iOffset = stIndex;
	if( iOffset==-1 )
	{
		iOffset = FindNullHotkeyOffSet( );
		if( -1==iOffset )
			return false;
	}
	if (iOffset < 0 || iOffset >= m_iBagSize)
		return false;
	//
	m_pHotkeyData[iOffset] = item;
	return true;
}


bool CHotkeyBag::ClearItem( short stIndex )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;

	memset(&m_pHotkeyData[stIndex], 0x00, sizeof(m_pHotkeyData[stIndex]));
//	m_pHotkeyData[stIndex].type		 = SMouseItem::TypeNull;	//û�ж���
	m_pHotkeyData[stIndex].ItemData.itembaseinfo.ustItemID = ErrorUnsignedShortID;
	return true;
}

//����ָ��Hotkey�Ŀ����Ϣ
void CHotkeyBag::SetShortCut( int iHotKeyIndex, int iBagType, int iBagIndex )
{
	if( iHotKeyIndex<0||iHotKeyIndex>=m_iBagSize )
		return;
	
	m_pHotkeyData[iHotKeyIndex].ShortCut.BagType = iBagType;
	m_pHotkeyData[iHotKeyIndex].ShortCut.BagIndex= iBagIndex;
//	m_pHotkeyData[iHotKeyIndex].type = SMouseItem::TypeNotItem;
}

//��ȡָ����ݵ���Ϣ
bool CHotkeyBag::GetHotkey( short stIndex, SMouseItem *pHotkey )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;

	memcpy( pHotkey, &m_pHotkeyData[stIndex], sizeof(SMouseItem) );
	//switch (pHotkey->type)
	//{
	//case SMouseItem::TypeFactItem://��ʾ����ϼ�¼������ĵ�������
	//	break;
	//case SMouseItem::TypeNotItem://��ʾ����ϼ�¼�Ĳ�����ĵ������ݣ��Ǽ��ܣ��ȡ�����
	//case SMouseItem::TypeNull://��ʾ�����Ϊ�գ�û���κε���
	//default:
	//	pHotkey->ItemData.ustItemID = ErrorUnsignedShortID;
	//	break;
	//}
	return true;
}

//��ȡָ��������״��...�жϸ�λ������
bool CHotkeyBag::IsHaveHotkey( short stIndex )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;	

//	return (m_pHotkeyData[stIndex].type!=SMouseItem::TypeNull);
	return false;
}
//��ȡָ��������״��...�жϸ�λ������
bool CHotkeyBag::IsHaveFactItem( short stIndex )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;	
	//if (SMouseItem::TypeFactItem == m_pHotkeyData[stIndex].type)
	//	return true;
	//
	return false;
}
//�ж��Ƿ��п�ݷ�ʽ
bool CHotkeyBag::IsHaveShortCut( short stIndex )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;	
	//if (SMouseItem::TypeNotItem == m_pHotkeyData[stIndex].type)
	//	return true;
	//
	return false;
}
//���ָ�������Ŀ��
bool CHotkeyBag::ClearHotkey( short stIndex )
{
	if( stIndex<0||stIndex>=m_iBagSize )
		return false;	
	
	memset(&m_pHotkeyData[stIndex], 0x00, sizeof(m_pHotkeyData[stIndex]));
//	m_pHotkeyData[stIndex].type = SMouseItem::TypeNull;
	m_pHotkeyData[stIndex].ItemData.itembaseinfo.ustItemID = ErrorUnsignedShortID;

	return true;
}

//���ָ��ָ������,�����Ŀ��
void CHotkeyBag::ClearSpecialHotkey( int bag_type, int index )
{
	int iLoop;
	for( iLoop=0; iLoop<m_iBagSize; iLoop++ )
	{
		if( /*m_pHotkeyData[iLoop].type==SMouseItem::TypeNotItem
		&&*/  m_pHotkeyData[iLoop].ShortCut.BagType==bag_type
		&&  m_pHotkeyData[iLoop].ShortCut.BagIndex==index )
		{
			ClearHotkey(iLoop);
			break;
		}
	}
}

bool	CHotkeyBag::GetHotKeyCanClear( short stIndex, SMouseItem *pHotkey )
{
	bool ret ;
	ret = GetHotkey(stIndex, pHotkey);
	ClearHotkey(stIndex);
	//
	return ret;
}

//{ add by ^^
int CHotkeyBag::PopItem( SCharItem &item,unsigned short &ustCount )
{
	int		i;
	CItemDetail::SItemCommon *pItemDetail = NULL;
	//
	for( i = 0; i < m_iBagSize; i++ )
	{
		if( m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemID == item.itembaseinfo.ustItemID )
		{
			pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
			if( !pItemDetail )
				return ierr_unknown;

			if ( pItemDetail->ucItemType == CItemDetail::ITEMTYPE_RESTORE || 
				pItemDetail->ucItemType == CItemDetail::ITEMTYPE_MATERIAL )
			{
				if (m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemCount > 0)
				{
					m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemCount--;			
					if ( 0 == m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemCount )
						ClearItem( i );
				}
			}
			else ClearItem( i );
			//
			return ierr_Success;
		}
	}
	//
	return ierr_unknown;
}
//
int   CHotkeyBag::GetItemCount( int iItemID )
{
	int i,iNumber;
	CItemDetail::SItemCommon *pItemDetail = NULL;
	//
	iNumber = 0;
	for( i = 0; i < m_iBagSize; i++ )
	{
		if( m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemID == iItemID )
		{
			pItemDetail = GettheItemDetail().GetItemByID( iItemID );
			if( !pItemDetail )
				return ierr_unknown;

			if ( pItemDetail->ucItemType == CItemDetail::ITEMTYPE_RESTORE || 
				pItemDetail->ucItemType == CItemDetail::ITEMTYPE_MATERIAL )
				iNumber +=   m_pHotkeyData[ i ].ItemData.itembaseinfo.ustItemCount;
			else iNumber++;
		}
	}
	//
	return iNumber;
}
//} add by ^^

//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------

