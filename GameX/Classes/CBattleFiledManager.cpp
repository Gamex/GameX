//
//  CBattleFiledManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-8.
//
//

#include "CBattleFiledManager.h"
#include "CRole.h"

IMPLEMENT_SINGLETON(CBattleFiledManager);


CBattleFiledManager::CBattleFiledManager()
: m_defenderInBattle(false)
{
}



CBattleFiledManager::~CBattleFiledManager()
{
    removeAll();
}



bool CBattleFiledManager::init()
{
    do
    {
        m_defenderInBattle = false;
        return true;
    } while (false);
    
    return false;
}


void CBattleFiledManager::addRole(CRole* role)
{
    CC_ASSERT(role);
    ROLE_GROUP group = role->getRoleGroup();
    CC_ASSERT(group >= 0 && group < ROLE_GROUP_MAX);
    m_roleByGroups[group].insert(role);
}



void CBattleFiledManager::removeRole(CRole* role)
{
    CC_ASSERT(role);
    ROLE_GROUP group = role->getRoleGroup();
    CC_ASSERT(group >= 0 && group < ROLE_GROUP_MAX);
    m_roleByGroups[group].erase(role);
}



void CBattleFiledManager::removeAll()
{
    int i;
    for (i = 0; i < ROLE_GROUP_MAX; ++i)
    {
        m_roleByGroups[i].clear();
    }
}


void CBattleFiledManager::update(float dt)
{

}



SR& CBattleFiledManager::getRoles(ROLE_GROUP group)
{
    CC_ASSERT(group >= 0 && group < ROLE_GROUP_MAX);
    return m_roleByGroups[group];
}



void CBattleFiledManager::wakeUpAllDefender()
{
    if (!m_defenderInBattle)
    {
        SR& df = m_roleByGroups[ROLE_GROUP_DEFENCE];
        auto it = df.begin();
        for (; it != df.end(); ++it)
        {
            (*it)->enterBattleState();
        }
    }
}
