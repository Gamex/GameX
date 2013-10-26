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
    if (containerUnUseArray_.count() == 0)
    {
        return NULL;
    }
    
    CObjectBase* pObj = static_cast<CObjectBase*>(containerUnUseArray_.lastObject());
    
    containerInUseArray_.addObject(pObj);
    containerUnUseArray_.removeLastObject();
    
//    if (dynamic_cast<TFItemInGame*>(pObj))
//    {
//        CCLOG("checkout: Sprite:0x%X, 0x%X",(void*)pObj, (void*)(pObj->getSprite()));
//    }
    
    return pObj;
}



void CNodeContainer::checkinElement(CObjectBase* elem)
{
    CC_ASSERT(NULL != elem);
    
    unsigned int idx = containerInUseArray_.indexOfObject(elem);
    if (CC_INVALID_INDEX == idx)
    {
        return;
    }
    
//    if (dynamic_cast<TFItemInGame*>(elem))
//    {
//        CCLOG("checkin: Sprite:0x%X, 0x%X",(void*)elem, (void*)(elem->getSprite()));
//    }

    containerUnUseArray_.addObject(elem);
    containerInUseArray_.removeObjectAtIndex(idx);
}



void CNodeContainer::clear()
{
    CCObject* pObj;
    CCARRAY_FOREACH(&containerInUseArray_, pObj)
    {
        CObjectBase* pTFObj = dynamic_cast<CObjectBase*>(pObj);
        if (NULL != pTFObj)
        {
            pTFObj->clearAll();
        }
    }
    CCARRAY_FOREACH(&containerUnUseArray_, pObj)
    {
        CObjectBase* pTFObj = dynamic_cast<CObjectBase*>(pObj);
        if (NULL != pTFObj)
        {
            pTFObj->clearAll();
        }
    }
    containerInUseArray_.removeAllObjects();
    containerUnUseArray_.removeAllObjects();
}



bool CNodeContainer::initCache(const std::string& name, int num)
{
    for (int i = 0; i < num; ++i)
    {
        CObjectBase* pObj = (CObjectBase*)OBJECT_FACTORY->createInstance(name);
        if (NULL != pObj)
        {
            pObj->die();
            containerUnUseArray_.addObject(pObj);
        }
        else
        {
            __CCLOGWITHFUNCTION("can't create %s", name.c_str());
            return false;
        }
    }
    
    return true;
}



const CCArray* CNodeContainer::getInUseArray() const
{
    return &containerInUseArray_;
}



unsigned int CNodeContainer::getInUseCount()
{
    return containerInUseArray_.count();
}




