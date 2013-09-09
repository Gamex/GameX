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


class CWarriorRole : public CRole
{
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
public:
    virtual ~CWarriorRole();

    virtual void goStraightToTarget(CCPoint target) = 0;

    virtual void die();
    
    DECLARE_DICTFUNC(float, MaxHP);
    DECLARE_DICTFUNC(float, AttackRange);
protected:
    CWarriorRole();
    
    virtual void castItems() = 0;
    virtual const char* getHPBarName() = 0;
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
