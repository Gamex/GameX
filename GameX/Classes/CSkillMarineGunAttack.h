//
//  CSkillMarineGunAttack.h
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#ifndef __GameX__CSkillMarineGunAttack__
#define __GameX__CSkillMarineGunAttack__

#include "CSkillMeleeAttack.h"

class CGameEffect;

class CSkillMarineGunAttack
: public CSkillMeleeAttack
{
public:
    FACTORY_CREATE_FUNC(CSkillMarineGunAttack);
    virtual ~CSkillMarineGunAttack();
protected:
    CSkillMarineGunAttack();
    virtual void onSkillHit(CCNode* obj);
    
    CGameEffect* m_effect;
};

#endif /* defined(__GameX__CSkillMarineGunAttack__) */
