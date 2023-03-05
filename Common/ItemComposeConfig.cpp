#include "ItemComposeConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"


bool ItemComposeConfig::LoadItemComposeConfig( const char* szFile )
{
    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    m_mapComposeData.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pComposeItems = pRoot->FirstChildElement( "ComposeItems" );
    if ( pComposeItems == NULL )
    { return false; }

    MeXmlElement* pCompose = pComposeItems->FirstChildElement( "Compose" );
    while ( pCompose != NULL )
    {
        ComposeData xData;

        int nItemID;
        if ( pCompose->Attribute( "ItemID" , &nItemID ) == NULL || nItemID == 0 )
        { return false; }
        xData.SetItemID( nItemID );

        int nMaterialID;
        if ( pCompose->Attribute( "MaterialID" , &nMaterialID ) == NULL || nMaterialID == 0 )
        { return false; }
        xData.SetMaterialID( nMaterialID );

        int nNewItemID;
        if ( pCompose->Attribute( "NewItemID" , &nNewItemID ) == NULL || nNewItemID == 0 )
        { return false; }
        xData.SetNewItemID( nNewItemID );

        int nCostMoney;
        if ( pCompose->Attribute( "CostMoney" , &nCostMoney ) == NULL )
        { return false; }
        xData.SetCostMoney( nCostMoney );

        MeXmlElement* pItem = pCompose->FirstChildElement( "Item" );
        while ( pItem != NULL )
        {
            int nCount;
            if ( pItem->Attribute( "Count" , &nCount ) == NULL || nCount == 0 )
            { return false; }

            double fModulus;
            if ( pItem->Attribute( "Modulus", &fModulus ) == NULL )
            { return false; }

            xData.AddModulus( nCount, static_cast< float >( fModulus ) );
 
            pItem = pItem->NextSiblingElement();
        }

        if ( !AddItemComposeData( xData ) )
        { return false; }

        pCompose = pCompose->NextSiblingElement();
    }

    return true;
}

bool ItemComposeConfig::LoadItemComposeConfig2( const char* szFile )
{
    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    m_mapComposeData.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pComposeItems = pRoot->FirstChildElement( "ComposeItems" );
    if ( pComposeItems == NULL )
    { return false; }

    MeXmlElement* pCompose = pComposeItems->FirstChildElement( "Compose" );
    while ( pCompose != NULL )
    {
        ComposeData2 xData;

        int nItemID;
        if ( pCompose->Attribute( "ItemID" , &nItemID ) == NULL || nItemID == 0 )
        { return false; }
        xData.SetItemID( nItemID );

        int nNewItemID;
        if ( pCompose->Attribute( "NewItemID" , &nNewItemID ) == NULL || nNewItemID == 0 )
        { return false; }
        xData.SetNewItemID( nNewItemID );

        int nCostMoney;
        if ( pCompose->Attribute( "CostMoney" , &nCostMoney ) == NULL )
        { return false; }
        xData.SetCostMoney( nCostMoney );

        int nProbility;
        if ( pCompose->Attribute( "Probility" , &nProbility ) == NULL )
        { return false; }
        xData.SetProbility( nProbility );

        MeXmlElement* pMaterial = pCompose->FirstChildElement( "Material" );
        while ( pMaterial != NULL )
        {
            ComposeData2::SMaterial xMaterial;

            int nMaterialID;
            if ( pMaterial->Attribute( "MaterialID" , &nMaterialID ) == NULL || nMaterialID == 0 )
            { return false; }
            xMaterial.nMaterialID = nMaterialID;

			int nMaterialID2;
			if ( pMaterial->Attribute( "MaterialID2" , &nMaterialID2 ) == NULL || nMaterialID2 == 0 )
			{ return false; }
			xMaterial.nMaterialID2 = nMaterialID2;

			int nMaterialID3;
			if ( pMaterial->Attribute( "MaterialID3" , &nMaterialID3 ) )
				xMaterial.nMaterialID3 = nMaterialID3;
			else
				xMaterial.nMaterialID3 = 0;

            int nCount;
            if ( pMaterial->Attribute( "Count" , &nCount ) == NULL || nCount == 0 )
            { return false; }
            xMaterial.nCount = nCount;

            int nModulus;
            if ( pMaterial->Attribute( "Modulus", &nModulus ) == NULL )
            { return false; }

            xMaterial.nModulus = nModulus;

            xData.AddMaterial( xMaterial );

            pMaterial = pMaterial->NextSiblingElement();
        }

        if ( !AddItemComposeData2( xData ) )
        { return false; }

        pCompose = pCompose->NextSiblingElement();
    }

    return true;
}

const ComposeData2* ItemComposeConfig::GetComposeData( SCharItem* pCharItem[], int nItemCount )
{
	if ( NULL == pCharItem || nItemCount <= 0 )
	{ return NULL; }

	// calc total item count
	int nTotalItemCount = 0;
	for ( int i = 0; i < nItemCount; ++i )
	{
		if (pCharItem[i] != NULL && pCharItem[i]->itembaseinfo.ustItemID != 0)
		{ nTotalItemCount += pCharItem[i]->GetItemCount(); }
	}

	for ( int i = 0; i < nItemCount; ++i )
	{
		if (pCharItem[i])
		{
			std::pair<ComposeData2MapConstIter, ComposeData2MapConstIter> itrPair = m_mapComposeData2.equal_range( pCharItem[i]->GetItemID() );
			ComposeData2MapConstIter iter = itrPair.first;
			for ( ; iter != itrPair.second; ++iter )
			{
				//copy list for matching
				std::vector<ComposeData2::SMaterial> vecMaterial = iter->second.GetMaterialList();

				//matching
				int nTotalMaterailCount = 0;
				std::vector<ComposeData2::SMaterial>::iterator itVec = vecMaterial.begin();
				for ( ; itVec != vecMaterial.end(); ++itVec )
				{ nTotalMaterailCount += itVec->nCount; }
				if ( nTotalMaterailCount != nTotalItemCount )
				{ continue; }

				for ( int matchingIndex = 0; matchingIndex < nItemCount; ++matchingIndex )
				{
					if (pCharItem[matchingIndex])
					{
						for ( int configIndex = 0; configIndex < vecMaterial.size(); ++configIndex )
						{
							if ( pCharItem[matchingIndex]->GetItemID() == vecMaterial[configIndex].nMaterialID ||
								 pCharItem[matchingIndex]->GetItemID() == vecMaterial[configIndex].nMaterialID2 )
							{
								vecMaterial[configIndex].nCount -= pCharItem[matchingIndex]->GetItemCount();
							}
						}
					}
				}

				//check result
				bool result = true;
				for ( int configIndex = 0; configIndex < vecMaterial.size(); ++configIndex )
				{
					if ( vecMaterial[configIndex].nCount != 0 )
					{
						result = false;
						break;
					}
				}
				if (result)
				{
					return &(iter->second);
				}
			}
		}
	}
	return NULL;
}

const ComposeData2* ItemComposeConfig::GetComposeDataNew(uint16 itemid, int nCount)
{
	if (!itemid || nCount <= 0)
		return NULL;

	std::pair<ComposeData2MapConstIter, ComposeData2MapConstIter> itrPair = m_mapComposeData2.equal_range( itemid );
	ComposeData2MapConstIter iter = itrPair.first;

	for ( ; iter != itrPair.second; ++iter )
	{
		//copy list for matching
		std::vector<ComposeData2::SMaterial> vecMaterial = iter->second.GetMaterialList();

		//matching
		int nTotalMaterailCount = 0;
		std::vector<ComposeData2::SMaterial>::iterator itVec = vecMaterial.begin();
		for ( ; itVec != vecMaterial.end(); ++itVec )
			nTotalMaterailCount = itVec->nCount;

		if ( nTotalMaterailCount != nCount )
			continue;

		return &(iter->second);
	}

	return NULL;
}