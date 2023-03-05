/********************************************************************
    Filename:    RecipeManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __SERVERCOMMON_RECIPEMANAGER_H__
#define __SERVERCOMMON_RECIPEMANAGER_H__

#pragma once

#include "GlobalDef.h"

class GamePlayer;

class RecipeManager
{
public: // 方法
    RecipeManager();
    ~RecipeManager(){}

    bool CreateFromData( GamePlayer* pOwn, unsigned short* pRecipes, int recipeMaxCount ); // 初始化数据
    void UpdateDataToOwner(); // 更新

    bool AddRecipe( unsigned short recipeId );     // 加入新的处方
    void RemoveRecipe( unsigned short recipeId );  // 删除处方
    bool IsExistRecipe( unsigned short recipeId ); // 处方是否存在
    void RemoveRecipeByType( unsigned short nType );

protected: // 方法

private: // 变量
    friend class GamePlayer;
    typedef std::set<unsigned short>  RecipeContainer;
    typedef RecipeContainer::iterator ItrRecipeContainer;

    GamePlayer*     _pGamePlayer;    // 指向主人
    unsigned short* _pRecipes;       // 指向主人处方数组
    int             _recipeMaxCount; // 主人处方的最大数
    RecipeContainer _recipes;        // 处方
};

#endif // __SERVERCOMMON_RECIPEMANAGER_H__
