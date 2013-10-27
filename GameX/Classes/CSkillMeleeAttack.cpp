//
//  CSkillMeleeAttack.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#include "CSkillMeleeAttack.h"



CSkillMeleeAttack::CSkillMeleeAttack()
{
    m_strName = "SkillMeleeAttack";
}



CSkillMeleeAttack::~CSkillMeleeAttack()
{
}



void CSkillMeleeAttack::onSkillHit(CCNode* obj)
{
    CSkillComp::onSkillHit(obj);
    
    if (!isEnabled())
    {
        return;
    }
    
    float damage = m_ownerRole->getATK() - m_skillTarget->getDEF();
    if (damage < 1.f)
    {
        damage = 1.f;
    }
    
    m_skillTarget->damage(damage, m_ownerRole);
}



