//
//  CGunBase.cpp
//  GameX
//
//  Created by 马 俊 on 13-7-1.
//
//

#include "CGunBase.h"
#include "CDirectionBullet.h"
#include "CRole.h"


DEFINE_DICTFUNC_STR(CGunBase, BulletName);
DEFINE_DICTFUNC(CGunBase, int, CacheNum, 0);



CGunBase::CGunBase()
{
}



CGunBase::~CGunBase()
{
    clearThis();
}



bool CGunBase::init(CCDictionary* pObjectDict)
{
    if (!CObjectBase::init(pObjectDict))
    {
        return false;
    }
    
//    if (!CBatchNodeObject::init())
//    {
//        return false;
//    }
    
    CCAssert(NULL != getBulletNameFromDict(), "BulletName must be set!");
    
    if (!m_container.initCache(getBulletNameFromDict()->getCString(), getCacheNumFromDict()))
    {
        __CCLOGWITHFUNCTION("Bullet cache init failed. Gun: %s; Bullet: %s",
                            getNameFromDict()->getCString(), getBulletNameFromDict()->getCString());
        return false;
    }
    
    return true;
}



void CGunBase::update(float dt)
{
    CCObject* pObj;
    const CCArray* children = m_container.getInUseArray();
    CCArray needToCheckin;
    CCARRAY_FOREACH(children, pObj)
    {
        CBulletBase* pBullet = dynamic_cast<CBulletBase*>(pObj);
        if (pBullet != NULL && pBullet->isDead())
        {
            pBullet->removeSpriteFromParentAndCleanup(false);
            needToCheckin.addObject(pBullet);
        }
        else
        {
            pBullet->update(dt);
        }
    }
    
    CCARRAY_FOREACH(&needToCheckin, pObj)
    {
        m_container.checkinElement(static_cast<CObjectBase*>(pObj));
    }
    needToCheckin.removeAllObjects();
}



void CGunBase::setOwner(CRole* role)
{
    CCAssert(role, "role is invalid.");
    
    if (role)
    {
        m_pRole = role;
    }
}



void CGunBase::clearAll()
{
    CObjectBase::clearAll();
    clearThis();
}



void CGunBase::clearThis()
{
    
}



GameArts CGunBase::getBatchNodeName()
{
    return GA_BULLETS;
}



bool CGunBase::changeBullet(const string& name)
{
    m_container.clear();
    if (!m_container.initCache(name, getCacheNumFromDict()))
    {
        return false;
    }
    
    return true;
}
