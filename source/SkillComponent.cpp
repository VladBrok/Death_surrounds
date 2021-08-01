#include "precompiled.h"
#include "SkillComponent.h"


void SkillComponent::addSkill(const SkillType skill)
{
    skills[skill];
}


int SkillComponent::getSkillLevel(const SkillType skill)
{
    try
    {
        return this->skills.at(skill).level;
    }
    catch(std::out_of_range&)
    {
        std::cout << "ERROR in SkillComponent::getSkillLevel: there is no skill with such type.";
    }
    return -1;
}


void SkillComponent::gainSkillExp(const SkillType skill, const int exp)
{
    assert(exp >= 0);

    try
    {
        skills.at(skill).exp += exp;
        skills[skill].updateLevel();
    }
    catch(std::out_of_range&)
    {
        std::cout << "ERROR in SkillComponent::gainSkillExp: there is no skill with such type.";
    }
}