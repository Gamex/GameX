//
//  CNodeContainer.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-21.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CNodeContainer.h"
#include "CBattleFieldLayer.h"
#include "CObjectBase.h"


CNodeContainer::CNodeContainer()
{
    
}



CNodeContainer::~CNodeContainer()
{
    clear();
}



CObjectBase* CNodeContainer::checkoutElement()
{
    if (m_containerUnUseArray.size() == 0)
    {
        return nullptr;
    }
    
    SOB_IT it = m_containerUnUseArray.begin();
    CObjectBase* pObj = (CObjectBase*)*it;
    
    
    m_containerUnUseArray.erase(it);
    m_containerInUseArray.insert(pObj);

    return pObj;
}



void CNodeContainer::checkinElement(CObjectBase* elem)
{
    CC_ASSERT(nullptr != elem);
    
    SOB_IT it = m_containerInUseArray.find(elem);
    if (it == m_containerInUseArray.end())
    {
        return;
    }

    
    m_containerUnUseArray.insert(*it);
    m_containerInUseArray.erase(it);

}



void CNodeContainer::clear()
{
    SOB_IT it = m_containerInUseArray.begin();
    for (; it != m_containerInUseArray.end(); ++it)
    {
        CObjectBase* pTFObj = (CObjectBase*)*it;
        if (nullptr != pTFObj)
        {
            pTFObj->clearAll();
        }
    }

    it = m_containerUnUseArray.begin();
    for (; it != m_containerUnUseArray.end(); ++it)
    {
        CObjectBase* pTFObj = (CObjectBase*)*it;
        if (nullptr != pTFObj)
        {
            pTFObj->clearAll();
        }
    }
    m_containerInUseArray.clear();
    m_containerUnUseArray.clear();
}



bool CNodeContainer::initCache(const std::string& name, int num, Object* target, NODE_CONTAINER_INIT_CALL_BACK callback, void* pUserData)
{
    for (int i = 0; i < num; ++i)
    {
        CObjectBase* pObj = (CObjectBase*)OBJECT_FACTORY->createInstance(name);
        if (nullptr != pObj)
        {
            pObj->die();
            m_containerUnUseArray.insert(pObj);

            if (target)
            {
                if (!(target->*callback)(m_containerUnUseArray, pObj, pUserData))
                {
                    return false;
                }
            }
        }
        else
        {
            __CCLOGWITHFUNCTION("can't create %s", name.c_str());
            return false;
        }
    }
    
    return true;
}



const SOB& CNodeContainer::getInUseArray() const
{
    return m_containerInUseArray;
}



unsigned int CNodeContainer::getInUseCount()
{
    return m_containerInUseArray.size();
}




