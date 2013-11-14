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
    setName("WarriorDyingComp");
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
        {
            m_ownerRole->prepareToDie();
            m_subState = DYING_SUB_STATE_DYING;
            break;
        }
        case DYING_SUB_STATE_DYING:
            break;
        case DYING_SUB_STATE_OVER:
            m_ownerRole->die();
            break;
        default:
            break;
    }
}



void CWarriorDyingComp::onDyingOver(Node* obj)
{
    if (!isEnabled())
    {
        return;
    }
    m_subState = DYING_SUB_STATE_OVER;
}

