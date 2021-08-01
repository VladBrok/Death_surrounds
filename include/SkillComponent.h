#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H


enum SkillType
{
    ENDURANCE
};


class SkillComponent
{
public:

    void addSkill(const SkillType skill);
    int  getSkillLevel(const SkillType skill);
    void gainSkillExp(const SkillType skill, const int exp);

private:


    class Skill
    {
    public:

        int level;
        int levelMax;
        int exp;
        int expForNextLevel;


        Skill()
            : level(1),
              levelMax(100),
              exp(0),
              expForNextLevel(100)
        {
        }


        void updateLevel()
        {
            while (exp >= expForNextLevel && level < levelMax)
            {
                ++level;
                exp -= expForNextLevel;
                expForNextLevel = (int)std::powf((float)level, 2.f) + level * 12;
            }
        }
    };


    std::unordered_map<SkillType, Skill> skills;
};


#endif // SKILLCOMPONENT_H
