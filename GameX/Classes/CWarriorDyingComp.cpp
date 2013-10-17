//
//  CWarriorDyingComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-16.
//
//

#include "CWarriorDyingComp.h"

CWarriorDyingComp::CWarriorDyingComp(void)
: CWarriorRoleCompBase(DYING_SUB_STATE_START)
{
    m_strName = "WarriorDyingComp";
}



bool CWarriorDyingComp::init()
{
    do
    {
        BREAK_IF_FAILED(CWarriorRoleCompBase::init());
        
        return true;
    } while (false);
	return false;
}



void CWarriorDyingComp::onEnter()
{
    CWarriorRoleCompBase::onEnter();
    m_subState = DYING_SUB_STATE_START;
}



void CWarriorDyingComp::onExit()
{
    CWarriorRoleCompBase::onExit();
}



void CWarriorDyingComp::update(float dt)
{
    if (!isEnabled()) return;
    
    switch (m_subState)
    {
        case DYING_SUB_STATE_START:
            m_ownerRole->playAnimation(ROLE_ANIMATION_DYING);
            m_ownerRole->die();
            m_subState = DYING_SUB_STATE_DYING;
            break;
        case DYING_SUB_STATE_DYING:
            break;
        case DYING_SUB_STATE_OVER:
            break;
        default:
            break;
    }
}



