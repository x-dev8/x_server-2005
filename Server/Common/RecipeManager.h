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
public: // ����
    RecipeManager();
    ~RecipeManager(){}

    bool CreateFromData( GamePlayer* pOwn, unsigned short* pRecipes, int recipeMaxCount ); // ��ʼ������
    void UpdateDataToOwner(); // ����

    bool AddRecipe( unsigned short recipeId );     // �����µĴ���
    void RemoveRecipe( unsigned short recipeId );  // ɾ������
    bool IsExistRecipe( unsigned short recipeId ); // �����Ƿ����
    void RemoveRecipeByType( unsigned short nType );

protected: // ����

private: // ����
    friend class GamePlayer;
    typedef std::set<unsigned short>  RecipeContainer;
    typedef RecipeContainer::iterator ItrRecipeContainer;

    GamePlayer*     _pGamePlayer;    // ָ������
    unsigned short* _pRecipes;       // ָ�����˴�������
    int             _recipeMaxCount; // ���˴����������
    RecipeContainer _recipes;        // ����
};

#endif // __SERVERCOMMON_RECIPEMANAGER_H__
