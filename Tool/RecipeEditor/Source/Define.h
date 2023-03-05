#pragma once
#include <vector>
#include <algorithm>
using namespace std;

#define ItemDetial_FilePath "..\\Data\\Config\\Item"
#define RecipeConfig_File "..\\Data\\Config\\Recipe.config"

#define DefaultSelect "«Î—°‘Ò"
#define DefineTrue " «"
#define DefineFalse "∑Ò"

enum Name_type
{
    PrimaryMaterial   = 0,
    SecondaryMaterial = 1,
    IsRandStar        = 2,
    IsBound           = 3,

    Enum_End,
};

struct SetInfo
{
    SetInfo()
    {
        strName.clear();
        nValue = -1;
    }
    string strName;
    int nValue;
};

typedef vector<SetInfo>::iterator setiter;