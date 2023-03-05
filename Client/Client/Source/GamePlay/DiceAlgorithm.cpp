#include <math.h>
#include "DiceAlgorithm.h"

//----------------------------------------------------------------------
void PowerDiceAlgorithm::UpdateAlgorithm( DWORD dwTime )
{
	if( !IsProcessing() )
		return;
	if( m_dwStartTime == 0 )
		m_dwStartTime = dwTime;
	DWORD dwDeltaTimeMilliSecond = dwTime - m_dwStartTime;
	float fDeltaFactor = (float)dwDeltaTimeMilliSecond / 100.f;
	short stSign = m_nSpeedFactor / abs( m_nSpeedFactor );	
	m_fDelay +=	( fDeltaFactor * m_nSpeedFactor );
}
//----------------------------------------------------------------------