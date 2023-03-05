#ifndef __LEVELEXPERIENCECONFIG_H__
#define __LEVELEXPERIENCECONFIG_H__

#include <vector>

#define theLevelExperienceConfig LevelExperienceConfig::Instance()

class LevelExperienceConfig
{
public:
    enum LevelRange
    {
        MinLevel = 1,                //最小等级
    };

    struct LevelExperience
    {
        LevelExperience() : Level(0), Experience(0) {}

        unsigned short Level;
        unsigned long Experience;

        bool operator == (unsigned short nLevel) { return this->Level == nLevel; }

        LevelExperience& operator = (const LevelExperience& xLevelExperience)
        {
            if (this != &xLevelExperience)
            {
                Level = xLevelExperience.Level;
                Experience = xLevelExperience.Experience;
            }
            return *this;
        }
    };

protected:
    LevelExperienceConfig();

public:
    ~LevelExperienceConfig() {};

    static LevelExperienceConfig& Instance()
    {
        static LevelExperienceConfig s_xLevelExperienceConfig;
        return s_xLevelExperienceConfig;
    }

    bool LoadLevelExperienceConfig(const char* szFile);
    bool SaveLevelExperienceConfig(const char* szFile);

    bool IsEmpty() { return _characterLevelExperience.empty(); }
    void Clear() { _characterLevelExperience.clear(); }

    bool AddCharacterLevelExperience(LevelExperience& xLevelExperience, bool bReplace = false);
    LevelExperience* GetCharacterLevelExperienceByLevel(unsigned short nLevel);
    LevelExperience* GetCharacterLevelExperienceByExperience(unsigned long nExperience);
    unsigned int CharacterLevelExperienceCount() { return static_cast<unsigned int>(_characterLevelExperience.size()); }

    bool AddMountLevelExperience(LevelExperience& xLevelExperience, bool bReplace = false);
    LevelExperience* GetMountLevelExperienceByLevel(unsigned short nLevel);
    LevelExperience* GetMountLevelExperienceByExperience(unsigned long nExperience);
    unsigned int MountLevelExperienceCount() { return static_cast<unsigned int>(_mountLevelExperience.size()); }

    bool AddPetLevelExperience(LevelExperience& xLevelExperience, bool bReplace = false);
    LevelExperience* GetPetLevelExperienceByLevel(unsigned short nLevel);
    LevelExperience* GetPetLevelExperienceByExperience(unsigned long nExperience);
    unsigned int PetLevelExperienceCount() { return static_cast<unsigned int>(_petLevelExperience.size()); }

private:
    typedef std::vector<LevelExperience> LevelExperienceContainer;    
    typedef LevelExperienceContainer::iterator leiter;
    LevelExperienceContainer _characterLevelExperience; // 人物等级经验
    LevelExperienceContainer _mountLevelExperience;     // 坐骑等级经验
    LevelExperienceContainer _petLevelExperience;       // 宠物等级经验
};

#endif