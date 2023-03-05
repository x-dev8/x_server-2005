#pragma once
#include "MeRTLibs.h"

class RecipeConfig
{

public: // �����
    struct SSubType  // С����
    {
        SSubType()
        {
            nType = -1;
        }

        int nType;  // С��ID
        std::string subTypeName;
    };

    typedef std::vector<SSubType> SubTypeContainer;
    typedef SubTypeContainer::iterator ItrSubTypeContainer;

    struct SType    // ����
    {
        SType()
        {
            nType = -1;
            AddValue = 0;
        }
        int nType;      //  ����ID
        int AddValue;   // ���ӵĻ���ֵ
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

    struct SItem //�����Ĳ�Ʒ
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

        unsigned int    ItemId      ; // ��Ʒ��ID
        unsigned short  Probility   ; // �����ĸ���
        unsigned short  Count       ; // ��Ʒ������
        bool bIsBound               ;
        bool bIsStarRandom          ; // �Ƿ�����Ǽ�
        unsigned char   nStarLevel  ; // ����Ǽ�


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
        unsigned long CastTime;   // �ϳɵ�����ʱ��
        unsigned long NeedActivity; // ���ĵĻ���ֵ
        unsigned long NeedMoney;  // ���ĵĽ�Ǯ

        MaterialContainer SecondaryMaterials;
        ItemContainer ProductItems;

        bool IsHaveSecondaryMaterials(){return !SecondaryMaterials.empty();}

        SMaterial& GetFirstSecondaryMaterials(){return SecondaryMaterials.front();}

        bool AddSecondaryMaterial(const SMaterial& Material);
        //bool DelSecondaryMaterial(const int MaterialId);

        bool AddProductItem(const SItem &Item);
        bool DelProductItem(const int ItemId);

        bool SetSecondaryMaterial(const int Num,const RecipeConfig::SMaterial& Material);//���õڼ���
        bool SetProductItem(const int Num,const RecipeConfig::SItem& Item);
    };

    struct SRecipe
    {
        enum EMaterialResult
        {
            EMR_OK = 0,           // OK
            EMR_MaterialNoEnough, // ���ϲ���
            EMR_MaterialNoMatch,  // ���ϲ�ƥ��
            EMR_NoFindRecipe,     // ����������������
        };
        unsigned int      RecipeId;         // �䷽Id
        short             Type;             // �䷽������
        short             SubType;          // �䷽��������
        std::string       SubTypeName;      // �䷽��������
        std::string       Name;             // �䷽������
        unsigned short    ProficiencyLimit; // ������Ʒ��������������������
        unsigned short    SkillLevelLimit;  // ������Ʒ���������ĵȼ�����
        unsigned short    AddPointValue;    // ����������
        MaterialContainer PrimaryMaterials; // ������
        ProductsContainer Products;         // ��Ʒ

        short CheckMaterial(const MaterialContainer& Material); // ����������Ƿ�

        long  GetProduct( IN const RecipeConfig::MaterialContainer& InputSecondaryMaterials,
            OUT RecipeConfig::SProduct& product ); // ͨ���������õ���Ӧ�Ĳ�Ʒ

        int GetPrimaryMaterialNum(){return (int)PrimaryMaterials.size();}

        bool AddPrimaryMaterial(const SMaterial& Material);
        //bool DelPrimaryMaterial(const int MaterialId);

        bool AddProducts(const SProduct&);
        bool DelProducts(const int ProductId);

        bool SetPrimaryMaterial(const int Num,const RecipeConfig::SMaterial& Material);
        bool SetProduct(const int Num,const RecipeConfig::SProduct& Product);

        void OnlySetRecipeValue(const RecipeConfig::SRecipe& ModifiyRecipe); // ֻ�޸��䷽�Ļ�������
    };

public: // ����
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

private: // ����
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

private: // ����
    ComposeRecipeContainer Recipes;
    ComposeRecipeByNameContainer RecipesByNames;

    SkillAddValueContainer m_vecSkillAddValue;
};

#define theRecipeConfig RecipeConfig::Instance()