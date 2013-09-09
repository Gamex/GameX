//
//  CApproachToAttackArea.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-16.
//
//

#include "CApproachToAttackArea.h"
#include "CMoveTowardComp.h"
#include "CRole.h"

CApproachToAttackArea::CApproachToAttackArea()
{
    
}



CApproachToAttackArea::~CApproachToAttackArea()
{
    
}



void CApproachToAttackArea::update(float dt)
{
    do
    {
        CRole* role = this->getOwner();
        BREAK_IF(NULL == role);
        CRole* target = role->getAttackTarget();
        if (NULL == target)
        {
//            role->changeState(ROLE_STATE_MOVE);
            return;
        }
        
        CCPoint rolePosition = role->getSpritePositionInWorldSpace();
        CCPoint targetPosition = target->getSpritePositionInWorldSpace();
        CCSize szRole = role->getSpriteContentSize();
        CCSize szTarget = target->getSpriteContentSize();
        float minX = szRole.width / 2.f + szTarget.width / 2.f;
        
        float diffX = fabsf(rolePosition.x - targetPosition.x);
        float diffY = fabsf(rolePosition.y - targetPosition.y);
        
        if (FLT_LE(diffX, minX))
        {
            if (FLT_GE(diffY, 2.f ))
            {
                CCPoint* pos = new CCPoint(rolePosition.x,
                                           targetPosition.y);
                pos->autorelease();
                CComponentParameter* param = CComponentParameter::create();
                param->addObjectParameter(PARAM_MOVE_TOWARD_TARGET, pos);
                param->addBoolParameter(PARAM_MOVE_INFINITE, false);
                role->setComponentParameter(param);
            }
            else
            {
                // do attack
                role->changeState(ROLE_STATE_ATTACK);
            }
        }
        else
        {
            CCPoint* pos = new CCPoint(rolePosition.x < targetPosition.x ?
                                       targetPosition.x - szTarget.width / 2.f :
                                       targetPosition.x + szTarget.width / 2.f,
                                       targetPosition.y);
            pos->autorelease();
            CComponentParameter* param = CComponentParameter::create();
            param->addObjectParameter(PARAM_MOVE_TOWARD_TARGET, pos);
            param->addBoolParameter(PARAM_MOVE_INFINITE, false);
            role->setComponentParameter(param);

        }
    } while (false);
    
}


void CApproachToAttackArea::setParameter(CComponentParameter* parameter)
{
    
}



CRole* CApproachToAttackArea::getOwner()
{
    return dynamic_cast<CRole*>(CComponent::getOwner());
}

