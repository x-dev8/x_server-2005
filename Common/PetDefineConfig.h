#pragma once
#include <map>
class PetDefineConfig 
{
public:
	PetDefineConfig();
	~PetDefineConfig();

	static PetDefineConfig& Instance()
    {
        static PetDefineConfig s_xConfig;
        return s_xConfig;
    }

	bool LoadFileConfigPath(const char * FilePath);
	bool IsNeedChangeSkillSum(int Level);
	int  GetLevelSkillSum(int Level);
	int  GetTimeStep(){return TimeStep;}
	int  GetTimeExp(){return TimeExp;}
	int  GetAttChangeLevel(){return MinAttChangeLevel;}
	int	 GetMaxLevel(){return MaxLevel;}
private:
	int		TimeStep;
	int		TimeExp;
	int		MinAttChangeLevel;
	int		MaxLevel;
	std::map<int,int> PetSKillSum;
};
#define thePetDefineConfig PetDefineConfig::Instance()