#include "RecipeManager.h"
#include "RecipeConfig.h"

RecipeManager::RecipeManager()
{
}

bool RecipeManager::CreateFromData( GamePlayer* pOwn, unsigned short* pRecipes, int recipeMaxCount )
{
    if ( pRecipes==NULL || recipeMaxCount<0 || pOwn==NULL)
    { return false; }

    _pGamePlayer    = pOwn;
    _pRecipes       = pRecipes;
    _recipeMaxCount = recipeMaxCount;

    if ( _recipeMaxCount > MAX_RECIPE_COUNT)
    { _recipeMaxCount = MAX_RECIPE_COUNT; }

    for ( int i=0; i<recipeMaxCount; ++i )
    {
        if ( pRecipes[i] == 0 )
        { break; }

        // ToDo 检查处方是否是有效的
        _recipes.insert( RecipeContainer::value_type( pRecipes[i] ) );
    }    
    return true;
}

void RecipeManager::UpdateDataToOwner()
{
    if ( _recipeMaxCount > MAX_RECIPE_COUNT)
    { _recipeMaxCount = MAX_RECIPE_COUNT; }

    memset( _pRecipes, 0, sizeof(unsigned short) * _recipeMaxCount);
    
    ItrRecipeContainer itEnd = _recipes.begin();
    if ( _recipes.size() > MAX_RECIPE_COUNT )
    { // 防错用
        std::advance( itEnd, MAX_RECIPE_COUNT );
    }
    else
    {
        itEnd = _recipes.end();
    }

    std::copy( _recipes.begin(), itEnd, &_pRecipes[0] );
}

bool RecipeManager::AddRecipe( unsigned short recipeId )
{   
    // ToDo 检查处方是否是有效的

    // 配方是否已经满了
    if ( _recipes.size()> MAX_RECIPE_COUNT)
    { return false; }

    return _recipes.insert( recipeId ).second;
}

void RecipeManager::RemoveRecipeByType( unsigned short nType )
{
    ItrRecipeContainer iter = _recipes.begin();
    for ( ; iter != _recipes.end(); )
    {
        RecipeConfig::SRecipe* pRecipe = theRecipeConfig.GetItemRuleByRuleId( *iter );
        if (pRecipe == NULL)
        { continue; }

        if (pRecipe->Type == nType)
        { _recipes.erase( iter++ ); }
        else
        { iter++; }
    }
}

void RecipeManager::RemoveRecipe( unsigned short recipeId )
{
    _recipes.erase( recipeId );
}

bool RecipeManager::IsExistRecipe( unsigned short recipeId )
{
    ItrRecipeContainer it = _recipes.find( recipeId );
    if ( it != _recipes.end())
    { return true; }

    return false;
}
