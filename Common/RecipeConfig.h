#pragma once
#include "MeRTLibs.h"

class RecipeConfig
{

public: // 结果体
    struct SSubType  // 小类型
    {
        SSubType()
        {
            nType = -1;
        }

        int nType;  // 小类ID
        std::string subTypeName;
    };

    typedef std::vector<SSubType> SubTypeContainer;
    typedef SubTypeContainer::iterator ItrSubTypeContainer;

    struct SType    // 大类
    {
        SType()
        {
            nType = -1;
            AddValue = 0;
        }
        int nType;      //  大类ID
        int AddValue;   // 增加的活力值
        std::string TypeName;
        SubTypeContainer m_SubTypeVec;
    };

    typedef std::vector<SType> TypeContainer;
    typedef TypeContainer::iterator ItrTypeContainer;

    TypeContainer& GetTypeContainer(){ return m_vecSkillAddValue;}
    SType* GetTypeById(int nId)
    {
        if ( nId < 0 || nId > m_vecSkillAddValue.size() )
        { return NULL;}

        return &m_vecSkillAddValue[nId];
    }

    struct SMaterial
    {
        SMaterial()
        {
            //MaterialId = -1;
			vecMaterailIDList.clear();
            Count = 1;
        }
        //int MaterialId;
		typedef std::vector<int>				MaterialIDContainer;
		typedef MaterialIDContainer::iterator	ItMaterialIDContainer;
		MaterialIDContainer vecMaterailIDList;
        unsigned short Count;
        //bool operator == (unsigned short MaterialId){  return this->MaterialId == MaterialId; }
// 		bool operator == (const MaterialIDContainer & list)
// 		{
// 			if ( list.size() == vecMaterailIDList.size() )
// 			{ return false; }
// 			for ( int i = 0; i < list.size(); ++i )
// 			{
// 				if ( list[i] != vecMaterailIDList[i] )
// 				{
// 					return false;
// 				}
// 			}
// 			return true;
// 		}
    };

    struct SItem //生产的产品
    {
        SItem()
        {
            ItemId = 0;
            Probility = 0;
            Count = 0;
            bIsBound = true;
            bIsStarRandom = false;
            nStarLevel = 0;
        }

        unsigned int    ItemId      ; // 产品的ID
        unsigned short  Probility   ; // 产出的概率
        unsigned short  Count       ; // 产品的数量
        bool bIsBound               ;
        bool bIsStarRandom          ; // 是否随机星级
        unsigned char   nStarLevel  ; // 最大星级


        bool operator == (unsigned int ItemId){  return this->ItemId == ItemId; }

    };

    struct SProduct;
    struct SRecipe;
    typedef std::vector<SMaterial>            MaterialContainer;
    typedef MaterialContainer::const_iterator ItrConstMaterialContainer;
    typedef MaterialContainer::iterator       ItrMaterialContainer;
    typedef std::vector<SItem>                ItemContainer;
    typedef ItemContainer::iterator           ItrItemContainer;
    typedef std::map<unsigned int,SRecipe>    ComposeRecipeContainer;
    typedef ComposeRecipeContainer::iterator  ItrComposeRecipeContainer;
    typedef std::map<std::string,SRecipe*>     ComposeRecipeByNameContainer;
    typedef ComposeRecipeByNameContainer::iterator  ItrComposeRecipeByNameContainer;
    typedef std::vector<SProduct>             ProductsContainer;
    typedef ProductsContainer::iterator       ItrProductContainer;

    typedef std::vector< SType >     SkillAddValueContainer;

    struct SProduct
    {
        SProduct()
        {
            CastTime = 0;
            NeedActivity = 0;
            NeedMoney = 0;
        }
        unsigned long CastTime;   // 合成的吟唱时间
        unsigned long NeedActivity; // 消耗的活力值
        unsigned long NeedMoney;  // 消耗的金钱

        MaterialContainer SecondaryMaterials;
        ItemContainer ProductItems;

        bool IsHaveSecondaryMaterials(){return !SecondaryMaterials.empty();}

        SMaterial& GetFirstSecondaryMaterials(){return SecondaryMaterials.front();}

        bool AddSecondaryMaterial(const SMaterial& Material);
        //bool DelSecondaryMaterial(const int MaterialId);

        bool AddProductItem(const SItem &Item);
        bool DelProductItem(const int ItemId);

        bool SetSecondaryMaterial(const int Num,const RecipeConfig::SMaterial& Material);//设置第几个
        bool SetProductItem(const int Num,const RecipeConfig::SItem& Item);
    };

    struct SRecipe
    {
        enum EMaterialResult
        {
            EMR_OK = 0,           // OK
            EMR_MaterialNoEnough, // 材料不够
            EMR_MaterialNoMatch,  // 材料不匹配
            EMR_NoFindRecipe,     // 辅材料种类数不对
        };
        unsigned int      RecipeId;         // 配方Id
        short             Type;             // 配方的类型
        short             SubType;          // 配方的子类型
        std::string       SubTypeName;      // 配方子类型名
        std::string       Name;             // 配方中文名
        unsigned short    ProficiencyLimit; // 生产物品能提升到的熟练度上限
        unsigned short    SkillLevelLimit;  // 生产物品能提升到的等级上限
        unsigned short    AddPointValue;    // 增加熟练度
        MaterialContainer PrimaryMaterials; // 主材料
        ProductsContainer Products;         // 产品

        short CheckMaterial(const MaterialContainer& Material); // 检查主材料是否

        long  GetProduct( IN const RecipeConfig::MaterialContainer& InputSecondaryMaterials,
            OUT RecipeConfig::SProduct& product ); // 通过辅材料拿到对应的产品

        int GetPrimaryMaterialNum(){return (int)PrimaryMaterials.size();}

        bool AddPrimaryMaterial(const SMaterial& Material);
        //bool DelPrimaryMaterial(const int MaterialId);

        bool AddProducts(const SProduct&);
        bool DelProducts(const int ProductId);

        bool SetPrimaryMaterial(const int Num,const RecipeConfig::SMaterial& Material);
        bool SetProduct(const int Num,const RecipeConfig::SProduct& Product);

        void OnlySetRecipeValue(const RecipeConfig::SRecipe& ModifiyRecipe); // 只修改配方的基本属性
    };

public: // 方法
    static RecipeConfig& Instance();

    ~RecipeConfig();

    bool LoadData(const char* FilePath);

    RecipeConfig::SRecipe* GetItemRuleByRuleId(unsigned int Id);
    RecipeConfig::SRecipe* GetItemRuleByRecipeName(const char* Name);
    bool SetItemRuleByRecipe(RecipeConfig::SRecipe* result);
    bool SaveFile(const char* FilePath);

    ComposeRecipeContainer& GetRecipes(){return Recipes;}

    bool DelRecipe(const int RecipeId);
    bool DelRecipe(const char* RecipeName);

    bool AddRecipe(const RecipeConfig::SRecipe& Recipe);
    bool SetRecipe(const RecipeConfig::SRecipe& Recipe,bool IndexName);

    uint16 GetSkillIdByRecipeType(int16 nType);
    int16  GetRecipeTypeBySkillId(uint16 skillId );

    unsigned short GetSkillAddValue( unsigned char uchType ) const
    {
        if ( uchType >= m_vecSkillAddValue.size() )
        { return 0; }

        return (unsigned int)uchType;
    }

private: // 方法
    RecipeConfig();
    RecipeConfig( const RecipeConfig& );
    RecipeConfig& operator = (const RecipeConfig&);

    bool AddSkillAddValue( unsigned char uchType, SType& type )
    {
        if ( uchType >= m_vecSkillAddValue.size() )
        { return false; }

        m_vecSkillAddValue[ uchType ] = type;
        return true;
    }

private: // 变量
    ComposeRecipeContainer Recipes;
    ComposeRecipeByNameContainer RecipesByNames;

    SkillAddValueContainer m_vecSkillAddValue;
};

#define theRecipeConfig RecipeConfig::Instance()