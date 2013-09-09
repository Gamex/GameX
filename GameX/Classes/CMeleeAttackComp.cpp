//
//  CMeleeAttackComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-15.
//
//

#include "CMeleeAttackComp.h"
#include "CRole.h"
#include "CMoveTowardComp.h"
#include "CMonster.h"

CMeleeAttackComp::CMeleeAttackComp() :
attackTime_(0.f)
{
}



CMeleeAttackComp::~CMeleeAttackComp()
{
}



void CMeleeAttackComp::setParameter(CComponentParameter* parameter)
{
}



void CMeleeAttackComp::update(float dt)
{
    do
    {
        CRole* role = this->getOwner();
        BREAK_IF(NULL == role);
        CRole* target = role->getAttackTarget();
        if (NULL == target)
        {
            role->changeState(ROLE_STATE_MOVE);
            return;
        }
        
        if (dynamic_cast<CMonster*>(target))
        {
            target->die();
            role->changeState(ROLE_STATE_MOVE);
        }
    } while (false);
    
    return;
}


CRole* CMeleeAttackComp::getOwner()
{
    return dynamic_cast<CRole*>(CComponent::getOwner());
}
