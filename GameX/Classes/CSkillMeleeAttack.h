//
//  CSkillMeleeAttack.h
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#ifndef __GameX__CSkillMeleeAttack__
#define __GameX__CSkillMeleeAttack__

#include "CSkillComp.h"

class CSkillMeleeAttack
: public CSkillComp
{
public:
    FACTORY_CREATE_FUNC(CSkillMeleeAttack);
    virtual ~CSkillMeleeAttack();
protected:
    CSkillMeleeAttack();
    virtual void onSkillHit(Node* obj);
};

#endif /* defined(__GameX__CSkillMeleeAttack__) */
