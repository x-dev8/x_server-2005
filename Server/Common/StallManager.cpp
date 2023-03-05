#include "GamePlayer.h"
#include "StallMessage.h"

template<>
void StallEx::ShowStallDataToPlayer( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }

    MsgShowStallData xShow;

    for ( int i = 0 ; i < StallDefine::MaxStallCount; ++i )
    {
        if ( m_xStallData[i].IsEmpty() )
        { continue; }

        switch( m_xStallData[i].GetStallType() )
        {
        case StallDefine::StallSell:
            {
                SellDataToClient xSell;
                xSell.SetIndex( i );
                xSell.SetBagType( m_xStallData[i].GetBagType() );
                xSell.SetGameMoneyPrice( m_xStallData[i].GetGameMoneyPrice() );
                xSell.SetRMBMoneyPrice( m_xStallData[i].GetRMBMoneyPrice() );
                m_pStaller->GetSellDataToClient( m_xStallData[i], xSell );

                xShow.AddSellData( xSell );
            }
            break;
        case StallDefine::StallBuy:
            {
                BuyDataToClient xBuy;
                xBuy.SetIndex( i );
                xBuy.SetItemID( m_xStallData[i].GetItemID() );
                xBuy.SetGameMoneyPrice( m_xStallData[i].GetGameMoneyPrice() );
                xBuy.SetRMBMoneyPrice( m_xStallData[i].GetRMBMoneyPrice() );
                xBuy.SetCount( m_xStallData[i].GetCount() );

                xShow.AddBuyData( xBuy );
            }
            break;
        default:
            break;
        }
    }

	xShow.IsOffLineStall = m_pStaller->GetStallOpenOffline();

    pPlayer->SendMessageToClient( &xShow );
}