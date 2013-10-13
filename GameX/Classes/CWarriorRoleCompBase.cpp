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
, m_ownerRole(NULL)
{
}



CWarriorRoleCompBase::~CWarriorRoleCompBase()
{
}



bool CWarriorRoleCompBase::init()
{
    return CCComponent::init();
}



void CWarriorRoleCompBase::onEnter()
{
    CCComponent::onEnter();
    m_ownerRole = dynamic_cast<CWarriorRole*>(getOwner());
}



void CWarriorRoleCompBase::onExit()
{
    CCComponent::onExit();
}



void CWarriorRoleCompBase::update(float dt)
{
    CCComponent::update(dt);
}



