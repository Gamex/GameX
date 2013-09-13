//
//  CWarriorRole.h
//  GameX
//
//  Created by 马 俊 on 13-6-17.
//
//

#ifndef __GameX__CWarriorRole__
#define __GameX__CWarriorRole__

#include "CRole.h"
#include "TFHPBar.h"

#define WARRIOR_STATE_IDLE                              "Idle"
#define WARRIOR_STATE_POS_IN_EDITOR                     "PosInEditor"
#define WARRIOR_STATE_SEL_POS_IN_EDITOR                 "SelPosInEditor"


class CWarriorRole : public CRole
{
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
public:
    FACTORY_CREATE_FUNC(CWarriorRole);
    
    virtual ~CWarriorRole();

    virtual void die();
    
    DECLARE_DICTFUNC(float, MaxHP);
    DECLARE_DICTFUNC(float, AttackRange);
protected:
    CWarriorRole();

    virtual bool createHPBar();
    virtual void findNearestMonsterToAttack(){};
    
    int m_hitPoint;
    int m_maxHitPoint;
    float m_hitTime;
    float m_speed;
    float m_attackRange;
private:

};

#endif /* defined(__GameX__CWarriorRole__) */
