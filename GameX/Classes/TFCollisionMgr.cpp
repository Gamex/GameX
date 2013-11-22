//
//  TFCollisionMgr.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFCollisionMgr.h"
#include "TFCollisionProtocol.h"
#include "CCircleSensor.h"

IMPLEMENT_SINGLETON(TFCollisionMgr);





TFCollisionMgr::TFCollisionMgr()
{
    
}



TFCollisionMgr::~TFCollisionMgr()
{
    clearAll();
}


//                    Hero	Monster     Bullet
//Hero                1     1           1
//Monster/Item        1     0           0
//Bullet              0     1           0


bool TFCollisionMgr::init()
{
    const char* cp = "GameCollision.plist";    
    
    Array* pArray = Array::createWithContentsOfFile(cp);
    if (!pArray)
    {
        __CCLOGWITHFUNCTION("file can't be loaded: %s", cp);
        return false;
    }
    Object* pObj;
    CCARRAY_FOREACH(pArray, pObj)
    {
        String* mask = dynamic_cast<String*>(pObj);
        if (mask)
        {
            m_CollisionObjs.push_back(LRB());
            m_ToBeAdded.push_back(LRB());
            m_ToBeDeleted.push_back(LRB());
            m_collisionMask.push_back(mask->uintValue());
        }
    }
    return true;
}


bool TFCollisionMgr::registerCollisionObj(TFCollisionProtocol* pRB, int group)
{
    group--;        // group == 0 means no need to check collision
    if (group < 0 || group >= m_CollisionObjs.size())
    {
        return false;
    }
    
    m_ToBeAdded[group].insert(pRB);
    
    auto it = m_ToBeDeleted[group].find(pRB);
    if (it != m_ToBeDeleted[group].end())
    {
        m_ToBeDeleted[group].erase(it);
    }
    
    return true;
}



void TFCollisionMgr::unregisterCollisionObj(TFCollisionProtocol* pRB, int group)
{
    group--;        // group == 0 means no need to check collision
    if (group < 0 || group >= m_CollisionObjs.size())
    {
        return;
    }
    
    m_ToBeDeleted[group].insert(pRB);
    
    auto it = m_ToBeAdded[group].find(pRB);
    if (it != m_ToBeAdded[group].end())
    {
        m_ToBeAdded[group].erase(it);
    }
    return;
}



void TFCollisionMgr::update()
{
    updateToBeAdded();
    updateToBeDeleted();
    
//    timeval time1, time2;
//    CCTime::gettimeofdayCocos2d(&time1, nullptr);
    int i,j;
    int size = m_CollisionObjs.size();
    unsigned int obj_id = 1;
    for (i = 0; i < size; ++i)
    {
        for (j = i; j < size; ++j)
        {
            unsigned int mask = m_collisionMask[j];
            if (obj_id & mask)
            {
                LRB& group1 = m_CollisionObjs[i];
                LRB& group2 = m_CollisionObjs[j];
                checkCollisionOf2Groups(group1, group2);
            }
        }
        obj_id <<= 1;
    }
    
//    CCTime::gettimeofdayCocos2d(&time2, nullptr);
//    CCLog("total collision time is: %f", CCTime::timersubCocos2d(&time1, &time2));
}



void TFCollisionMgr::checkCollisionOf2Groups(LRB& group1, LRB& group2)
{
    auto it1 = group1.begin();
    
    for (; it1 != group1.end(); ++it1)
    {
        TFCollisionProtocol* c1 = *it1;

        if (!c1->isNeedCheckCollision())
        {
            continue;
        }
        
//        timeval time1, time2;
//        CCTime::gettimeofdayCocos2d(&time1, nullptr);
        auto it2 = group2.begin();
        for (; it2 != group2.end(); ++it2)
        {
            
            TFCollisionProtocol* c2 = *it2;
            if (c1 == c2)
            {
                continue;
            }
            
            if (!c2->isNeedCheckCollision())
            {
                continue;
            }


            bool ok = c1->isCollsionWith(c2);
            if (ok)
            {
                c1->checkCollision(c2);
                c2->checkCollision(c1);
            }
        }
        
//        CCTime::gettimeofdayCocos2d(&time2, nullptr);
//        CCLog("did check collision time: %f", CCTime::timersubCocos2d(&time1, &time2));
    }
}



void TFCollisionMgr::clearAll()
{
    m_CollisionObjs.clear();
    m_ToBeDeleted.clear();
    m_ToBeAdded.clear();
    m_collisionMask.clear();
}



void TFCollisionMgr::updateToBeAdded()
{
    for (int i = 0; i < m_ToBeAdded.size(); ++i)
    {
        m_CollisionObjs[i].insert(m_ToBeAdded[i].begin(), m_ToBeAdded[i].end());
        m_ToBeAdded[i].clear();
    }
}



void TFCollisionMgr::updateToBeDeleted()
{
    for (int i = 0; i < m_ToBeDeleted.size(); ++i)
    {
        auto it = m_ToBeDeleted[i].begin();
        for (; it != m_ToBeDeleted[i].end(); ++it)
        {
            auto co_it = m_CollisionObjs[i].find(*it);
            if (co_it != m_CollisionObjs[i].end())
            {
                m_CollisionObjs[i].erase(co_it);
            }
        }
        m_ToBeDeleted[i].clear();
    }
}
