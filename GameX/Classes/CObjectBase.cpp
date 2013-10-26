//
//  CObjectBase.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CObjectBase.h"
#include "TFGameObjectManager.h"


CObjectBase::CObjectBase()
: m_isDead(false)
{
    
}



CObjectBase::~CObjectBase()
{
    clearThis();
}



bool CObjectBase::init()
{
    clearAll();

    addCollisionHandlers();
    
    addComponentsForStates();
    
    revive();
    return true;
}



void CObjectBase::clearAll()
{
    clearThis();
}




void CObjectBase::clearThis()
{
    die();
    removeAllChildrenWithCleanup(true);
    clearState();
}



void CObjectBase::die()
{
    m_isDead = true;
    turnOffCollision();
}



void CObjectBase::revive()
{
    m_isDead = false;
    turnOnCollision();
}



bool CObjectBase::isDead() const
{
    return m_isDead;
}



void CObjectBase::update(float dt)
{
    CCNode::update(dt);
    
    if (checkDead())
    {
        die();
        return;
    }
    
    CCArray* children = getChildren();
    CCObject* pObj;
    CCARRAY_FOREACH(children, pObj)
    {
        pObj->update(dt);
    }
}



bool CObjectBase::isNeedCheckCollision()
{
    return !isDead();
}



bool CObjectBase::checkDead()
{
    return false;
}


void CObjectBase::addCollisionHandlers()
{
    return;
}



void CObjectBase::addComponentsForStates()
{
    
}



void CObjectBase::addComponentForState(int state, CCComponent* comp)
{
    do
    {
        BREAK_IF(state < 0);
        
        CC_ASSERT(comp);
        
        comp->setEnabled(getCurrentState() == state);

        m_stateComponentTable[state].insert(comp->getName());
        
        addComponent(comp);
    } while (false);
}




void CObjectBase::onEnterState(int state)
{
    do
    {
        VSS_IT it = m_stateComponentTable.find(state);
        BREAK_IF(it == m_stateComponentTable.end());
        SS& ss = (*it).second;
        SS_IT ss_it = ss.begin();
        for (; ss_it != ss.end(); ++ss_it)
        {
            CCComponent* comp = getComponent((*ss_it).c_str());
            CC_ASSERT(comp);
            comp->setEnabled(true);
            comp->onEnter();
        }
    } while (false);
}



void CObjectBase::onLeaveState(int state)
{
    do
    {
        VSS_IT it = m_stateComponentTable.find(state);
        BREAK_IF(it == m_stateComponentTable.end());
        SS& ss = (*it).second;
        SS_IT ss_it = ss.begin();
        for (; ss_it != ss.end(); ++ss_it)
        {
            CCComponent* comp = getComponent((*ss_it).c_str());
            CC_ASSERT(comp);
            comp->setEnabled(false);
            comp->onExit();
        }
    } while (false);
}




