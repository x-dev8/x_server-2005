
#include "Storage.h"
#include "math.h"
#include "../../../ServerGui/NPC.h"
#include "../../../ServerGui/ShareData.h"

#define StorageRulePara_A  0.15
#define StorageRulePara_B  0
CStorage::CStorage(void)
{
}

CStorage::~CStorage(void)
{
}
float CStorage::Npcsdistance(int nNpcId1,int nNpcId2)
{
	C_Character* pChar1 = ShareData::GetCharacterByNpcID( nNpcId1 );
	C_Character* pChar2 = ShareData::GetCharacterByNpcID( nNpcId2 );
	if( pChar1 && pChar2 && pChar1->IsNpc() && pChar2->IsNpc() )
	{
		CNpc* pNpc1 = (CNpc*)pChar1;
		CNpc* pNpc2 = (CNpc*)pChar2;
		//get the positions of two NPC
		float fNpc1_x = pNpc1->GetX();
		float fNpc1_y = pNpc1->GetY();
		float fNpc2_x = pNpc2->GetX();
		float fNpc2_y = pNpc2->GetY();
		float fTemp1 = (fNpc1_x - fNpc2_x)*(fNpc1_x - fNpc2_x);
		float fTemp2 = fTemp1 + (fNpc1_y - fNpc2_y)*(fNpc1_y - fNpc2_y);
		//compute the distances between two npcs
		float fDistances = sqrtf(fTemp2);
		//the cost of fetching Items from other storage
		float fCost = StorageRulePara_A*fDistances + StorageRulePara_B;
		return fCost;
	}
}

