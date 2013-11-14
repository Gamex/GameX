//
//  CWarriorRoleCompBase.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-10.
//
//

#include "CWarriorRoleCompBase.h"

CWarriorRoleCompBase::CWarriorRoleCompBase(int subState)
: m_subState(subState)
, m_ownerRole(nullptr)
{
}



CWarriorRoleCompBase::~CWarriorRoleCompBase()
{
}



bool CWarriorRoleCompBase::init()
{
    return Component::init();
}



void CWarriorRoleCompBase::onEnter()
{
    Component::onEnter();
    m_ownerRole = dynamic_cast<CWarriorRole*>(getOwner());
    m_ownerRole->addCCBAnimationDelegate(this);
}



void CWarriorRoleCompBase::onExit()
{
    Component::onExit();
}



void CWarriorRoleCompBase::update(float dt)
{
    Component::update(dt);
}



