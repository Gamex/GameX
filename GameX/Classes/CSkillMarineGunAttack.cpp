//
//  CSkillMarineGunAttack.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#include "CSkillMarineGunAttack.h"
#include "CGameEffect.h"
#include "CEffectManager.h"

CSkillMarineGunAttack::CSkillMarineGunAttack()
{
    m_strName = "SkillMarineGunAttack";
}



CSkillMarineGunAttack::~CSkillMarineGunAttack()
{
}



void CSkillMarineGunAttack::onSkillHit(CCNode* obj)
{
    if (!isEnabled())
    {
        return;
    }
    
    CGameEffect* effect = EFFECT_MANAGER->createEffect(0, m_skillTarget);
    
    float damage = m_ownerRole->getATK() - m_skillTarget->getDEF();
    if (damage < 1.f)
    {
        damage = 1.f;
    }
    effect->setDamage(damage);
    effect->setEffectOwner(m_ownerRole);
    
    CC_ASSERT(effect);
}



