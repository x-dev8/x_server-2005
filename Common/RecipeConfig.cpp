#include "RecipeConfig.h"
#include "tstring.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "ItemDetail.h"
#include "LogFileObjectNameEx.h"

RecipeConfig::RecipeConfig(void)
{
}

RecipeConfig::~RecipeConfig(void)
{
}

bool RecipeConfig::SaveFile(const char* FilePath)
{
    if (NULL == FilePath)
        return false;
    // 遍历结构,保存

    MeXmlDocument xMeXmlDoc;
    xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));
    MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL) { return false; }

    Common::_tstring strName = "HeroOnline";
    pRoot->SetAttribute("Name", strName.toUTF8().c_str());

    //     Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();
    //     pRoot->SetAttribute("Version", strVersion.toUTF8().c_str()); //version	
    pRoot->SetAttribute("Version", "");
    // 类型信息
    MeXmlElement* pTypes = pRoot->InsertEndChild("Types")->ToElement();
    if (pTypes == NULL)
    { return false;}

    ItrTypeContainer iterTypeBegin = m_vecSkillAddValue.begin();
    ItrTypeContainer iterTypeEnd   = m_vecSkillAddValue.end();
    for (; iterTypeBegin != iterTypeEnd; ++iterTypeBegin)
    {
        if (iterTypeBegin->nType == -1)
        { continue;}
        MeXmlElement* pType = pTypes->InsertEndChild("Type")->ToElement();
        if (pType == NULL)
        { continue;}

        pType->SetAttribute("Type", iterTypeBegin->nType);
        pType->SetAttribute("AddValue", iterTypeBegin->AddValue);

        Common::_tstring strTypeName = iterTypeBegin->TypeName.c_str();
        pType->SetAttribute("Name", strTypeName.toUTF8().c_str());

        MeXmlElement* pSubTypes = pType->InsertEndChild("SubTypes")->ToElement();
        if (pSubTypes == NULL)
        { return false;}

        ItrSubTypeContainer itSubTypeBegin = iterTypeBegin->m_SubTypeVec.begin();
        ItrSubTypeContainer itSubTypeEnd   = iterTypeBegin->m_SubTypeVec.end();
        for (; itSubTypeBegin != itSubTypeEnd; ++itSubTypeBegin)
        {
            MeXmlElement* pSubType = pSubTypes->InsertEndChild("SubType")->ToElement();
            if (pSubType == NULL)
            { continue;}

            pSubType->SetAttribute("Type", itSubTypeBegin->nType);

            Common::_tstring strSubTypeName = itSubTypeBegin->subTypeName.c_str();
            pSubType->SetAttribute("Name", strSubTypeName.toUTF8().c_str());
        }
    }
    // 配方信息
    Common::_tstring strComment = "Recipe ID 为配方的编号\
                                  Name      为配方的中文名称\
                                  Type      配方的类型.\
                                  PrimaryMaterials 主要的配方\
                                  Material Id 主要配方里材料的编号\
                                  Count      主要配方需要的材料数量\
                                  CastTime   合成的吟唱时间\
                                  NeedEnergy 消耗的活力值\
                                  NeedMoney  消耗的金钱\
                                  Probility  产出的概率\
                                  ProficiencyLimit 生产物品能提升到的熟练度上限";

    pRoot->append_node(xMeXmlDoc.RetriveCommentElement(strComment.toUTF8().c_str()));
    MeXmlElement* pRecipes = pRoot->InsertEndChild(("Recipes"))->ToElement();
    if(pRecipes == NULL) { return false; }

    ItrComposeRecipeContainer Itr = Recipes.begin();
    ItrComposeRecipeContainer EndItr = Recipes.end();
    for(;Itr!=EndItr;++Itr)
    {
        //Recipe 
        MeXmlElement* pRecipe = pRecipes->InsertEndChild(("Recipe"))->ToElement();
        pRecipe->SetAttribute("Id",Itr->second.RecipeId);
        Common::_tstring _tStrName = Itr->second.Name.c_str();
        Common::_tstring _tStrSubTypeName = Itr->second.SubTypeName.c_str();
        pRecipe->SetAttribute("Name",_tStrName.toUTF8().c_str());
        pRecipe->SetAttribute("Type",Itr->second.Type);
        pRecipe->SetAttribute("SubType",Itr->second.SubType);
        pRecipe->SetAttribute("SubName",_tStrSubTypeName.toUTF8().c_str());
        pRecipe->SetAttribute("ProficiencyLimit",Itr->second.ProficiencyLimit);
        pRecipe->SetAttribute("SkillLevelLimit",Itr->second.SkillLevelLimit);
        MeXmlElement* pPrimaryMaterial = pRecipe->InsertEndChild(("PrimaryMaterials"))->ToElement();

        ItrMaterialContainer ItrMaterial = Itr->second.PrimaryMaterials.begin();
        ItrMaterialContainer ItrEndMaterial = Itr->second.PrimaryMaterials.end();
        for (;ItrMaterial != ItrEndMaterial;++ItrMaterial)
        {
            MeXmlElement* pMaterial = pPrimaryMaterial->InsertEndChild(("Material"))->ToElement();
            //pMaterial->SetAttribute("Id",ItrMaterial->MaterialId);
			char szVal[8];
			Common::_tstring strIDList;
			for ( int i=0; i< ItrMaterial->vecMaterailIDList.size(); ++i)
			{
				sprintf_s(szVal, sizeof(szVal), "%d", ItrMaterial->vecMaterailIDList[i]);
				if( i == (ItrMaterial->vecMaterailIDList.size() - 1) )
					strIDList = strIDList + string(szVal);
				else
					strIDList = strIDList + string(szVal) +",";
			}
			pMaterial->SetAttribute("IDList", strIDList.c_str());
            pMaterial->SetAttribute("Count",ItrMaterial->Count);
        }

        MeXmlElement* pProducts = pRecipe->InsertEndChild(("Products"))->ToElement();
        ItrProductContainer ItrProduct = Itr->second.Products.begin();
        ItrProductContainer ItrEndProduct = Itr->second.Products.end();
        for (;ItrProduct != ItrEndProduct;++ItrProduct)
        {
            MeXmlElement* pProduct = pProducts->InsertEndChild(("Product"))->ToElement();
            pProduct->SetAttribute("CastTime",ItrProduct->CastTime);
            pProduct->SetAttribute("NeedEnergy",ItrProduct->NeedActivity);
            pProduct->SetAttribute("NeedMoney",ItrProduct->NeedActivity);

            if (!ItrProduct->SecondaryMaterials.empty())
            {
                MeXmlElement* pSecondaryMaterials =  pProduct->InsertEndChild(("SecondaryMaterials"))->ToElement();
                ItrMaterialContainer ItrMaterial = ItrProduct->SecondaryMaterials.begin();
                ItrMaterialContainer ItrEndMaterial = ItrProduct->SecondaryMaterials.end();
                for (;ItrMaterial!=ItrEndMaterial;++ItrMaterial)
                {
                    MeXmlElement* pSecondaryMaterial = pSecondaryMaterials->InsertEndChild(("Material"))->ToElement();
                    //pSecondaryMaterial->SetAttribute("Id",ItrMaterial->MaterialId);
					char szVal[8];
					Common::_tstring strIDList;
					for ( int i=0; i< ItrMaterial->vecMaterailIDList.size(); ++i)
					{
						sprintf_s(szVal, sizeof(szVal), "%d", ItrMaterial->vecMaterailIDList[i]);
						if( i == (ItrMaterial->vecMaterailIDList.size() - 1) )
							strIDList = strIDList + string(szVal);
						else
							strIDList = strIDList + string(szVal) +",";
					}
					pSecondaryMaterial->SetAttribute("IDList", strIDList.c_str());
                }
            }
            MeXmlElement* pItems = pProduct->InsertEndChild(("Items"))->ToElement();
            ItrItemContainer ItrItem = ItrProduct->ProductItems.begin();
            ItrItemContainer ItrEndItem = ItrProduct->ProductItems.end();
            int TotalProbility = 0;
            for (;ItrItem != ItrEndItem;++ItrItem)
            {
                MeXmlElement* pItem = pItems->InsertEndChild(("Item"))->ToElement();
                pItem->SetAttribute("Id",ItrItem->ItemId);
                pItem->SetAttribute("Probility",ItrItem->Probility);
                TotalProbility += ItrItem->Probility;
                pItem->SetAttribute("Count",ItrItem->Count);
                pItem->SetAttribute("IsBound",ItrItem->bIsBound);               // 是否绑定
                pItem->SetAttribute("IsStarRandom", ItrItem->bIsStarRandom);    // 随机星级
                if (ItrItem->bIsStarRandom == false)    // 如果随机星级是0 则最大星级为0
                { ItrItem->nStarLevel = 0;}

                pItem->SetAttribute("StarLevel", ItrItem->nStarLevel);  // 最大星级
            }
            if ( 100 != TotalProbility || TotalProbility == 0)
            {
#ifndef _CLIENT_
                LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"RecipeId = %d TotalProbility unequal to 100 Or TotalProbility equal to 0. TotalProbility = %d",Itr->second.RecipeId,TotalProbility);
#endif
                return false;
            }
        }
    }

    if (!xMeXmlDoc.SaveFile(FilePath))
    {
#ifndef _CLIENT_
        LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"SaveFileError！Please Check File Path");
#endif
        return false;
    }
    return true;
}

bool RecipeConfig::LoadData(const char* FilePath)
{
    if(NULL == FilePath)
        return false;

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(FilePath, 1))
        return false;

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL) 
        return false;

    m_vecSkillAddValue.clear();
    m_vecSkillAddValue.resize( ERT_MaxType );

    MeXmlElement* pTypes = pRoot->FirstChildElement("Types");
    if (pTypes == NULL)
    { return false; }

    MeXmlElement* pType = pTypes->FirstChildElement("Type");
    if (pType == NULL)
    { return false; }

    while ( pType != NULL )
    {
        SType TempType;
        int nType;
        if ( pType->Attribute( "Type", &nType ) == NULL )
        { return false; }
        TempType.nType = nType;

        int nAddValue;
        if ( pType->Attribute( "AddValue", &nAddValue ) == NULL )
        { return false; }
        TempType.AddValue = nAddValue;

        Common::_tstring strTypeName;
        strTypeName.fromUTF8( pType->Attribute("Name") );
        TempType.TypeName = strTypeName;

        MeXmlElement* pSubTypes = pType->FirstChildElement("SubTypes");
        if (pSubTypes == NULL){ continue;}
        MeXmlElement* pSubType = pSubTypes->FirstChildElement("SubType");
        while (pSubType != NULL)
        {
            SSubType TempSubType;
            int nSubType;
            pSubType->Attribute("Type", &nSubType);
            TempSubType.nType = nSubType;

            Common::_tstring strSubTypeName;
            strSubTypeName.fromUTF8( pSubType->Attribute("Name") );
            TempSubType.subTypeName = strSubTypeName;
            TempType.m_SubTypeVec.push_back(TempSubType);
            pSubType = pSubType->NextSiblingElement();
        }

        if ( !AddSkillAddValue( nType, TempType ) )
        { return false; }

        pType = pType->NextSiblingElement();
    }

    //配方
    //////////////////////////////////////////////////////////
    MeXmlElement* pRecipes = pRoot->FirstChildElement("Recipes");
    if (pRecipes == NULL)
        return false;
    MeXmlElement* pRecipe = pRecipes->FirstChildElement("Recipe");
    if (pRecipe == NULL)
        return false;

    while (pRecipe != NULL)
    {
        SRecipe ComposeItemRule;

        int nId;
        if (pRecipe->Attribute("Id", &nId) == NULL || nId < 0 )
            return false;
        ComposeItemRule.RecipeId = nId;

        Common::_tstring tStrRecipeName = "";
        tStrRecipeName.fromUTF8(pRecipe->Attribute("Name"));
        if ( tStrRecipeName.empty() )
            return false;
        ComposeItemRule.Name = tStrRecipeName.toNarrowString();

        tStrRecipeName.fromUTF8(pRecipe->Attribute("SubName"));
        ComposeItemRule.SubTypeName = tStrRecipeName.toNarrowString();

        int nRuleType;
        if (pRecipe->Attribute("Type", &nRuleType) == NULL || nRuleType >= ERT_MaxType)
        {
#ifndef _CLIENT_
            LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Recipe Id = %d Type Error!Type = %d",ComposeItemRule.RecipeId,nRuleType);
#endif
            return false;
        }
        ComposeItemRule.Type = nRuleType;
        if (pRecipe->Attribute("SubType", &nRuleType) == NULL )
        {
            nRuleType = 0;
        }
        ComposeItemRule.SubType = nRuleType;

        int ProficiencyLimit;
        if (pRecipe->Attribute("ProficiencyLimit", &ProficiencyLimit) == NULL || ProficiencyLimit < 0 ) 
            return false;
        ComposeItemRule.ProficiencyLimit = (unsigned short)ProficiencyLimit;

        int SkillLevelLimit ;
        if (pRecipe->Attribute("SkillLevelLimit", &SkillLevelLimit ) == NULL || SkillLevelLimit  < 0 ) 
            return false;
        ComposeItemRule.SkillLevelLimit  = (unsigned short)SkillLevelLimit ;

        int AddPointValue = 1;
        pRecipe->Attribute("AddPointValue", &AddPointValue );
        ComposeItemRule.AddPointValue  = (unsigned short)AddPointValue ;

        MeXmlElement* pMeXmlPrimaryMaterials = pRecipe->FirstChildElement("PrimaryMaterials");
        if (NULL == pMeXmlPrimaryMaterials)
            return false;
        MeXmlElement* pPriMaterial =  pMeXmlPrimaryMaterials->FirstChildElement("Material");
        //         if (NULL == pPriMaterial)
        //             return false;
        while (NULL != pPriMaterial)
        {
            SMaterial sMaterial;

//             int nMaterialId;
//             if (pPriMaterial->Attribute("Id", &nMaterialId) == NULL || nMaterialId < 0 ) 
//                 return false;
//             sMaterial.MaterialId = nMaterialId;
			Common::_tstring strIDList;
			strIDList.fromUTF8( pPriMaterial->Attribute("IDList") );
			if ( !strIDList.empty() )
			{
				char *szSpn = ",";
				char *szStr;
				int i = 0;

				szStr = strtok( const_cast<char*>(strIDList.c_str()), szSpn );
				while( szStr )
				{
					if ( atoi(szStr) > 0 )
					{
						sMaterial.vecMaterailIDList.push_back( atoi(szStr) );
					}
					szStr = strtok( NULL, szSpn );
					++i;
				}
			}

            int nCount;
            if (pPriMaterial->Attribute("Count", &nCount) == NULL || nCount < 0 )
                return false;
            sMaterial.Count = nCount;

            ComposeItemRule.PrimaryMaterials.push_back(sMaterial);
            pPriMaterial = pPriMaterial->NextSiblingElement();
        }

        MeXmlElement* pProducts = pRecipe->FirstChildElement("Products");
        if (NULL == pProducts)
            return false;

        MeXmlElement* pProduct = pProducts->FirstChildElement("Product");
        //if (NULL == pProduct){return false;}

        while (NULL != pProduct)
        {
            SProduct sProduct;

            int CastTime;
            if (pProduct->Attribute("CastTime", &CastTime) == NULL || CastTime < 0 )
                return false;
            sProduct.CastTime = CastTime;

            int NeedActivity;
            if (pProduct->Attribute("NeedEnergy", &NeedActivity) == NULL || NeedActivity < 0 )
                return false;
            sProduct.NeedActivity = NeedActivity;

            int NeedMoney;
            if (pProduct->Attribute("NeedMoney", &NeedMoney) == NULL || NeedMoney < 0 )
                return false;
            sProduct.NeedMoney = NeedMoney;

            MeXmlElement* pSecondaryMaterials = pProduct->FirstChildElement("SecondaryMaterials");
            if (NULL != pSecondaryMaterials)
            {
                MeXmlElement* pMeXmlSecondaryMaterial =  pSecondaryMaterials->FirstChildElement("Material");
                while (NULL != pMeXmlSecondaryMaterial)
                {
                    SMaterial sMaterial;

//                     int nMaterialId;
//                     if (pMeXmlSecondaryMaterial->Attribute("Id", &nMaterialId) == NULL || nMaterialId < 0 ) 
//                         return false;
//                     sMaterial.MaterialId = nMaterialId;
					Common::_tstring strIDList;
					strIDList.fromUTF8( pSecondaryMaterials->Attribute("IDList") );
					if ( !strIDList.empty() )
					{
						char *szSpn = ",";
						char *szStr;
						int i = 0;

						szStr = strtok( const_cast<char*>(strIDList.c_str()), szSpn );
						while( szStr )
						{
							if ( atoi(szStr) > 0 )
							{
								sMaterial.vecMaterailIDList.push_back( atoi(szStr) );
							}
							szStr = strtok( NULL, szSpn );
							++i;
						}
					}

                    sProduct.SecondaryMaterials.push_back(sMaterial);

                    pMeXmlSecondaryMaterial = pMeXmlSecondaryMaterial->NextSiblingElement();
                }
            }

            MeXmlElement* pMeXmlItems = pProduct->FirstChildElement("Items");
            if(NULL == pMeXmlItems)
                return false;
            MeXmlElement* pMeXmlItem = pMeXmlItems->FirstChildElement("Item");
            if (NULL == pMeXmlItem)
                return false;

            unsigned short TotalProbility = 0;
            while (NULL != pMeXmlItem)
            {
                SItem sItem;

                int ItemId;
                if (pMeXmlItem->Attribute("Id", &ItemId) == NULL || nId < 0 ) { return false; }
                sItem.ItemId = ItemId;

                int nCount;
                if (pMeXmlItem->Attribute("Count", &nCount) == NULL || nCount < 0 ) { return false; }
                sItem.Count = nCount;

                int nProbility;
                if (pMeXmlItem->Attribute("Probility", &nProbility) == NULL || nProbility < 0 ) { return false; }
                sItem.Probility = nProbility;

                int nIsBound;
                if (pMeXmlItem->Attribute( "IsBound", &nIsBound ) == NULL ) { }
                sItem.bIsBound = nIsBound;

                int nIsStarRandom;
                if (pMeXmlItem->Attribute( "IsStarRandom", &nIsStarRandom ) == NULL ) { }
                sItem.bIsStarRandom = nIsStarRandom;

                int nStarLevel;
                if (pMeXmlItem->Attribute( "StarLevel", &nStarLevel ) == NULL ) { }
                sItem.nStarLevel = nStarLevel;

                TotalProbility += nProbility;

                sProduct.ProductItems.push_back(sItem);
                pMeXmlItem = pMeXmlItem->NextSiblingElement();
            }

            if ( 100 != TotalProbility || TotalProbility == 0)
            {
#ifndef _CLIENT_
                LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"RecipeId = %d TotalProbility unequal to 100 Or TotalProbility equal to 0. TotalProbility = %d",ComposeItemRule.RecipeId,TotalProbility);
#endif
                return false;
            }

            ComposeItemRule.Products.push_back(sProduct);
            pProduct = pProduct->NextSiblingElement();
        }// end Products

        ItrComposeRecipeContainer itr = Recipes.find(ComposeItemRule.RecipeId);
        if (itr != Recipes.end())
        {
#ifndef _CLIENT_
            LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Recipe Id = %d Recipe Name = 存在相同的Id请检查config文件",ComposeItemRule.RecipeId,ComposeItemRule.Name.c_str());
#endif
            return false; 
        }
        else
        {
            ItrComposeRecipeContainer Itr = Recipes.insert(ComposeRecipeContainer::value_type(ComposeItemRule.RecipeId,ComposeItemRule)).first;
            RecipesByNames.insert(ItrComposeRecipeByNameContainer::value_type(ComposeItemRule.Name,&(Itr->second)));
        }

        pRecipe = pRecipe->NextSiblingElement();
    }// end Recipe
    return true;
}

RecipeConfig::SRecipe* RecipeConfig::GetItemRuleByRuleId(unsigned int Id)
{
    if (Id <= 0)
    {
        return NULL;
    }
    ItrComposeRecipeContainer itr = Recipes.find(Id);
    if (itr == Recipes.end())
        return NULL;
    return &(itr->second);
}

RecipeConfig::SRecipe* RecipeConfig::GetItemRuleByRecipeName(const char* RecipeName)
{
    if (NULL == RecipeName )
    {
        return NULL;
    }
    ItrComposeRecipeByNameContainer Itr = RecipesByNames.find(RecipeName);
    if (Itr != RecipesByNames.end())
    {
        return Itr->second;
    }
    return NULL;
}

bool RecipeConfig::SetItemRuleByRecipe(RecipeConfig::SRecipe* result)
{
    if (NULL == result)
        return false;

    ItrComposeRecipeContainer itr = Recipes.find(result->RecipeId);
    if (itr == Recipes.end())
        Recipes.insert(ComposeRecipeContainer::value_type(result->RecipeId,*result));
    else
    {
        itr->second = *result;
    }

    return true;
}

RecipeConfig& RecipeConfig::Instance()
{
    static RecipeConfig InstanceItemRule;
    return InstanceItemRule;
}

short RecipeConfig::SRecipe::CheckMaterial(const MaterialContainer& Material)
{
    if (PrimaryMaterials.size() < Material.size())
        return EMR_MaterialNoEnough;

    RecipeConfig::ItrMaterialContainer Itr = PrimaryMaterials.begin();
    RecipeConfig::ItrMaterialContainer EndItr = PrimaryMaterials.end();

    RecipeConfig::ItrConstMaterialContainer CheckItr = Material.begin();
    RecipeConfig::ItrConstMaterialContainer CheckEndItr = Material.end();

    for (;Itr != EndItr;++Itr)
    {
        bool IsFind = false;
        for (;CheckItr != CheckEndItr;++CheckItr)
        {
//             if (Itr->MaterialId == CheckItr->MaterialId)
//             {
//                 IsFind = true;
//                 break;
//             }
			if ( Itr->vecMaterailIDList.size() == CheckItr->vecMaterailIDList.size() )
			{
				int i = 0;
				for ( ; i < Itr->vecMaterailIDList.size(); ++i )
				{
					if ( Itr->vecMaterailIDList[i] != CheckItr->vecMaterailIDList[i] )
					{ break; }
				}
				if ( i == Itr->vecMaterailIDList.size() )
				{
					IsFind = true;
					break;
				}
			}
        }
        if (!IsFind)
            return EMR_MaterialNoMatch;
    }

    return EMR_OK;
}

long RecipeConfig::SRecipe::GetProduct(const RecipeConfig::MaterialContainer& InputSecondaryMaterials,RecipeConfig::SProduct& result)
{
    //传进来的是辅助材料
    ItrProductContainer Itr = Products.begin();
    ItrProductContainer EndItr = Products.end();
    bool Find = false;

    bool bHaveNotNeedSecondaryMaterialProduct = false; // 是否含有不需要辅助材料的产品

    for ( ;Itr != EndItr;++Itr)
    {
        if ( Itr->SecondaryMaterials.empty() )
        { // 如果是空的
            result = *Itr;
            bHaveNotNeedSecondaryMaterialProduct = true;
        }
        else
        { // 需要辅助材料
            RecipeConfig::ItrConstMaterialContainer ItrInputMaterials    = InputSecondaryMaterials.begin();
            RecipeConfig::ItrConstMaterialContainer ItrEndInputMaterials = InputSecondaryMaterials.end();

            RecipeConfig::ItrMaterialContainer ItrSelfMaterial    = Itr->SecondaryMaterials.begin();
            RecipeConfig::ItrMaterialContainer ItrEndSelfMaterial = Itr->SecondaryMaterials.end();

            for (;ItrSelfMaterial != ItrEndSelfMaterial;++ItrSelfMaterial)
            { // 遍历辅助材料列表
                Find = false;
                // 是否在输入的辅助材料中

                for(;ItrInputMaterials!=ItrEndInputMaterials;++ItrInputMaterials)
                {
//                     if (ItrSelfMaterial->MaterialId == ItrInputMaterials->MaterialId)
//                     {
//                         Find = true;
//                         break;
//                     }
					for ( int input = 0; input < ItrInputMaterials->vecMaterailIDList.size(); ++input )
					{
						for ( int self = 0; self < ItrSelfMaterial->vecMaterailIDList.size(); ++self )
						{
							if ( ItrInputMaterials->vecMaterailIDList[input] == ItrSelfMaterial->vecMaterailIDList[self] )
							{
								Find = true;
								break;
							}
						}
						if (Find)
						{ break; }
					}
                }
                // 有一个没有找到就跳出
                if (!Find)
                { break; }
            }

            //找到了材料
            if ( Find )
            {
                result = *Itr;
                return EMR_OK;
            }
        }
    }

    if ( bHaveNotNeedSecondaryMaterialProduct )
    {  return EMR_OK; }

    return EMR_NoFindRecipe;
}


bool RecipeConfig::SProduct::AddSecondaryMaterial(const SMaterial& Material)
{
    SecondaryMaterials.push_back(Material);
    return true;
}

// bool RecipeConfig::SProduct::DelSecondaryMaterial(const int MaterialId)
// {
//     if (MaterialId < 0)
//         return false;
// 
//     ItrMaterialContainer Itr = find(SecondaryMaterials.begin(),SecondaryMaterials.end(),MaterialId);
//     if (Itr != SecondaryMaterials.end())
//     {
//         SecondaryMaterials.erase(Itr);
//     }
//     return true;
// }

bool RecipeConfig::SProduct::AddProductItem(const SItem &Item)
{
    ProductItems.push_back(Item);
    return true;
}

bool RecipeConfig::SProduct::DelProductItem(const int ItemId)
{
    if (ItemId < 0)
        return false;

    ItrItemContainer Itr = find(ProductItems.begin(),ProductItems.end(),ItemId);
    if (Itr != ProductItems.end())
    {
        ProductItems.erase(Itr);
    }
    return true;
}

bool RecipeConfig::SRecipe::AddPrimaryMaterial(const SMaterial& Material)
{
    PrimaryMaterials.push_back(Material);
    return true;
}

// bool RecipeConfig::SRecipe::DelPrimaryMaterial(const int MaterialId)
// {
//     if (MaterialId < 0)
//         return false;
// 
//     ItrMaterialContainer Itr = find(PrimaryMaterials.begin(),PrimaryMaterials.end(),MaterialId);
//     if (Itr != PrimaryMaterials.end())
//     {
//         PrimaryMaterials.erase(Itr);
//     }
//     return true;
// }

bool RecipeConfig::SRecipe::AddProducts(const SProduct& Product)
{
    Products.push_back(Product);
    return true;
}

bool RecipeConfig::SRecipe::DelProducts(const int ProductId)
{
    if ((ProductId<0)||(ProductId>Products.size()))
    {
        return false;
    }
    int DelId = 0 ;
    for (RecipeConfig::ItrProductContainer Itr = Products.begin();Itr!= Products.end();++Itr)
    {
        if (DelId == ProductId)
        {
            Products.erase(Itr);
            break;
        }
    }
    return true;
}

bool RecipeConfig::DelRecipe(const int RecipeId)
{
    ItrComposeRecipeContainer Itr = Recipes.find(RecipeId);
    if (Itr != Recipes.end())
    {
        ItrComposeRecipeByNameContainer NameItr = RecipesByNames.find (Itr->second.Name);
        if (NameItr!= RecipesByNames.end())
        {
            RecipesByNames.erase(NameItr);
        }
        Recipes.erase(Itr);
        return true;
    }
    return false;
}

bool RecipeConfig::DelRecipe(const char* RecipeName)
{
    if (NULL == RecipeName)
    {
        return false;
    }
    ItrComposeRecipeByNameContainer NameItr = RecipesByNames.find (RecipeName);
    if (NameItr!= RecipesByNames.end())
    {
        ItrComposeRecipeContainer Itr = Recipes.find( NameItr->second->RecipeId );
        if (Itr != Recipes.end())
        {
            Recipes.erase(Itr);
        }
        RecipesByNames.erase(NameItr);
    }
    return true;
}

bool RecipeConfig::SProduct::SetSecondaryMaterial(const int Num,const RecipeConfig::SMaterial& Material)//设置第几个
{
    if (Num < 0 || Num > SecondaryMaterials.size())
        return false;

    SecondaryMaterials[Num] = Material;

    return true;
}

bool RecipeConfig::SProduct::SetProductItem(const int Num,const RecipeConfig::SItem& Item)
{
    if (Num < 0 || Num > ProductItems.size())
        return false;

    ProductItems[Num] = Item;

    return true;
}

bool RecipeConfig::SRecipe::SetPrimaryMaterial(const int Num,const RecipeConfig::SMaterial& Material)
{
    if (Num < 0 || Num > PrimaryMaterials.size())
        return false;

    PrimaryMaterials[Num] = Material;

    return true;
}

bool RecipeConfig::SRecipe::SetProduct(const int Num,const SProduct& Product)
{
    if (Num < 0 || Num > Products.size())
        return false;

    Products[Num] = Product;

    return true;
}

bool RecipeConfig::AddRecipe(const RecipeConfig::SRecipe& Recipe)
{
    ItrComposeRecipeContainer FindItr = Recipes.find(Recipe.RecipeId);
    if (FindItr != Recipes.end())
        return false;
    ItrComposeRecipeByNameContainer FindNameItr = RecipesByNames.find(Recipe.Name.c_str());
    if (FindNameItr != RecipesByNames.end())
        return false;

    ItrComposeRecipeContainer Itr = Recipes.insert(ComposeRecipeContainer::value_type(Recipe.RecipeId,Recipe)).first;
    RecipesByNames.insert(ComposeRecipeByNameContainer::value_type(Recipe.Name,&(Itr->second)));
    return true;
}

uint16 RecipeConfig::GetSkillIdByRecipeType(int16 nType)
{
    switch (nType)
    {
    case ERT_CaoYao:           // 草药
        return ItemDefine::eCSI_LianYao;
        break;
    case ERT_ZhuBao:           // 珠宝
        return ItemDefine::eCSI_ZhuBao;
        break;
    case ERT_DuanZao:          // 锻造
        return ItemDefine::eCSI_DuanZao;
        break;
    case ERT_ZhuJia:           // 铸甲
        return ItemDefine::eCSI_ZhuJia;
        break;
    case ERT_GongYi:           // 工艺
        return ItemDefine::eCSI_GongYi;
        break;
    case ERT_XunMa:            // 驯马
        return ItemDefine::eCSI_XunMa;
        break;
    case ERT_CaiKuang:         // 采矿
        return ItemDefine::eCSI_CaiKuang;
        break;
    case ERT_CaiYao:           // 采药
        return ItemDefine::eCSI_CaiYao;
        break;
    case ERT_BuZhuo:           // 捕捉
        return ItemDefine::eCSI_BuZhuo;
        break;
    case ERT_BuChong:           // 捕虫
        return ItemDefine::eCSI_BuChong;
        break;
    }

    return InvalidLogicNumber;
}

int16  RecipeConfig::GetRecipeTypeBySkillId(uint16 skillId )
{
    switch (skillId)
    {
    case ItemDefine::eCSI_LianYao:           // 草药
        return ERT_CaoYao;
        break;
    case  ItemDefine::eCSI_ZhuBao:           // 珠宝
        return ERT_ZhuBao;
        break;
    case ItemDefine::eCSI_DuanZao:          // 锻造
        return ERT_DuanZao;
        break;
    case ItemDefine::eCSI_ZhuJia:           // 铸甲
        return ERT_ZhuJia;
        break;
    case ItemDefine::eCSI_GongYi:           // 工艺
        return ERT_GongYi;
        break;
    case ItemDefine::eCSI_XunMa:            // 驯马
        return ERT_XunMa;
        break;
    case ItemDefine::eCSI_CaiKuang:         // 采矿
        return ERT_CaiKuang;
        break;
    case ItemDefine::eCSI_CaiYao:           // 采药
        return ERT_CaiYao;
        break;
    case ItemDefine::eCSI_BuZhuo:           // 捕捉
        return ERT_BuZhuo;
        break;
    case ItemDefine::eCSI_BuChong:          // 捕虫
        return ERT_BuChong;
        break;
    case ItemDefine::eCSI_CatchPet:
        return ERT_CatchPet;                 // 捕宠
        break;
    }

    return -1;
}

bool RecipeConfig::SetRecipe(const RecipeConfig::SRecipe& Recipe,bool IndexName)
{
    if (IndexName)
    {
        ItrComposeRecipeByNameContainer Itr = RecipesByNames.find(Recipe.Name);
        if (Itr != RecipesByNames.end())
        {
            if(Recipe.RecipeId != Itr->second->RecipeId)
            {
#ifndef _CLIENT_
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"已经存在同样的配方名%s",Recipe.Name.c_str());
#endif
                return false;
            }
            Itr->second->OnlySetRecipeValue(Recipe);
            return true;
        }
        return false;
    }

    ItrComposeRecipeContainer Itr = Recipes.find(Recipe.RecipeId);
    if (Itr != Recipes.end())
    {
        Itr->second.OnlySetRecipeValue(Recipe);
        return true;
    }
    return false;
}

void RecipeConfig::SRecipe::OnlySetRecipeValue(const RecipeConfig::SRecipe& ModifiyRecipe)
{
    Name = ModifiyRecipe.Name;
    RecipeId = ModifiyRecipe.RecipeId;
    Type = ModifiyRecipe.Type;
    ProficiencyLimit = ModifiyRecipe.ProficiencyLimit;
    SkillLevelLimit  = ModifiyRecipe.SkillLevelLimit ;
}