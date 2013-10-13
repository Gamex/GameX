//
//  CAIManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-8.
//
//

#include "CAIManager.h"
#include "CRole.h"

IMPLEMENT_SINGLETON(CAIManager);


CAIManager::CAIManager()
: m_maxLoopTime(1.f)
{
}



CAIManager::~CAIManager()
{
}



void CAIManager::addAI(CRole* role)
{
    m_aiObjects.insert(role);
}



void CAIManager::removeAI(CRole* role)
{
    m_aiObjects.erase(role);
}



void CAIManager::removeAll()
{
    m_aiObjects.clear();
}


void CAIManager::update(float dt)
{
    int count = (int)m_aiObjects.size();
    int times = (int)(m_maxLoopTime / dt);
    
    times = times < 1 ? 1 : times;

    count /= times;
    count = count < 1 ? 1 : count;
    
    if (m_queue.size() == 0)
    {
        SR_IT it = m_aiObjects.begin();
        for (; it != m_aiObjects.end(); ++it)
        {
            m_queue.push(*it);
        }
    }
    
    count = INT_MAX;
    for (int i = 0; i < count && m_queue.size() > 0; ++i)
    {
        m_queue.front()->think();
        m_queue.pop();
    }
}



