template< class T >
int BillboardManager< T >::ms_cnBillboardCachCount = 100;
//////////////////////////////////////////////////////////////////////////
template< class T >
void BillboardManager<T>::Initialize( LPDIRECT3DDEVICE9 pkDevice )
{
	m_pkDevice = pkDevice;

	for( int i = 0 ; i < ms_cnBillboardCachCount ; ++ i )
	{
		CreateBillboardItem();

		m_UseableIndexs.push_back( i );
	}	
}
//////////////////////////////////////////////////////////////////////////
template< class T >
void BillboardManager<T>::Destroy()
{
	for( int i = 0 ; i < (int)m_Boards.size(); ++ i )	
		m_Boards[i] = NULL;
}
//////////////////////////////////////////////////////////////////////////
template< class T >
BillboardItem* BillboardManager<T>::CreateBillboard()
{
	if( m_UseableIndexs.empty() )
		return CreateBillboardItem();

	int nUseable = m_UseableIndexs.back();
	m_UseableIndexs.pop_back();
	assert( nUseable < m_Boards.size() );
	return m_Boards[nUseable];	
}
//////////////////////////////////////////////////////////////////////////
template< class T >
void BillboardManager<T>::DeleteBillboard( BillboardItem* pkItem )
{
	if( !pkItem )
		return;

	if( pkItem->m_nIndex >= (int)m_Boards.size() && 
		pkItem->m_nIndex < 0 )
		return;

	m_UseableIndexs.push_back( pkItem->m_nIndex );
}
//////////////////////////////////////////////////////////////////////////
template< class T >
BillboardItem* BillboardManager<T>::CreateBillboardItem()
{
	BillboardBase* pkBB = MeNew T;
	pkBB->Create( m_pkDevice );

	BillboardItem* pkItem = 
		MeNew BillboardItem;
	pkItem->m_nIndex = (int)m_Boards.size();		
	pkItem->m_pkBillboard = pkBB;
	m_Boards.push_back( pkItem );

	if(  (int)m_Boards.size() > ms_cnBillboardCachCount )
		ms_cnBillboardCachCount = m_Boards.size();

	return pkItem;
}
