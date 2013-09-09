//
//  CVisibleObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CVisibleObject.h"
#include "CBatchNodeManager.h"


DEFINE_DICTFUNC(CVisibleObject, int, CollisionGroup, 0);
DEFINE_DICTFUNC_STR(CVisibleObject, Sensor);
DEFINE_DICTFUNC_STR(CVisibleObject, BatchNodeName);

CVisibleObject::CVisibleObject() :
m_isCachePosition(false)
, m_pSensor(NULL)
{
    
}



CVisibleObject::~CVisibleObject()
{
    clearThis();
}



bool CVisibleObject::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF(!CObjectBase::init(pObjectDict));
        
        CCString* sensorName = getSensorFromDict();
        if (sensorName)
        {
            setSensor(dynamic_cast<CSensor*>(CObjectBase::createObject(sensorName->getCString())));
            BREAK_IF(m_pSensor == NULL)

            m_pSensor->setOwnerAndTrigger(this, callfuncO_selector(CVisibleObject::onSensor));
            setSensorType(m_pSensor);
        }

        return true;
    } while (false);
    
    return false;
}



void CVisibleObject::update(float dt)
{
    CObjectBase::update(dt);
    
    updateBoundingBoxInWorldSpace();
}



void CVisibleObject::updateBoundingBoxInWorldSpace()
{
    if (!m_isCachePosition)
    {
        return;
    }

    CCNode* pInnerSprite = getInnerSprite();
    if (pInnerSprite)
    {
        m_boundingBoxInWorldSpace = getSpriteBoundingBox();
        m_positionInWorldSpace = getSpritePosition();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
            m_positionInWorldSpace = pInnerSprite->getParent()->convertToWorldSpaceAR(m_positionInWorldSpace);
        }
    }
}



bool CVisibleObject::isNeedCheckCollision()
{
    return CObjectBase::isNeedCheckCollision() && isSpriteVisible();
}



bool CVisibleObject::isCollsionWith(TFCollisionProtocol* object)
{
    CVisibleObject* pObj = dynamic_cast<CVisibleObject*>(object);
    if (NULL == pObj)
    {
        return false;
    }
    
    CCRect b1 = getSpriteBoundingBoxInWorldSpace();
    CCRect b2 = pObj->getSpriteBoundingBoxInWorldSpace();
    
    return b1.intersectsRect(b2);
}




CCRect CVisibleObject::getSpriteBoundingBox() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->boundingBox();
    }
    
    return CCRectZero;
}



CCRect CVisibleObject::getSpriteBoundingBoxInWorldSpace()
{ 
    if (!m_isCachePosition)
    {
        CCNode* pInnerSprite = getInnerSprite();
        
        m_boundingBoxInWorldSpace = getSpriteBoundingBox();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
        }
    }
    
    return m_boundingBoxInWorldSpace;
}



CCPoint CVisibleObject::getSpritePositionInWorldSpace()
{
    if (!m_isCachePosition)
    {
        CCNode* pInnerSprite = getInnerSprite();
        
        m_positionInWorldSpace = getSpritePosition();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_positionInWorldSpace = pInnerSprite->getParent()->convertToWorldSpaceAR(m_positionInWorldSpace);
        }
    }
    
    return m_positionInWorldSpace;
}


CCPoint CVisibleObject::getSpritePosition() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getPosition();
    }
    
    return CCPointZero;
}



void CVisibleObject::setSpritePosition(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setPosition(point);
        updateBoundingBoxInWorldSpace();
    }
}



void CVisibleObject::setSpriteVisible(bool visible)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setVisible(visible);
    }
}



bool CVisibleObject::isSpriteVisible()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->isVisible();
    }
    
    return false;
}




CCSize CVisibleObject::getSpriteContentSize()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getContentSize();
    }
    
    return CCSizeZero;
}



void CVisibleObject::setSpriteZOrder(int z)
{
    if (NULL != getInnerSprite())
    {
        CCNode* pParent = getInnerSprite()->getParent();
        if (NULL != pParent)
        {
            getInnerSprite()->retain();
            pParent->removeChild(getInnerSprite(), false);
            pParent->addChild(getInnerSprite(), z);
            getInnerSprite()->release();
        }
    }
}



bool CVisibleObject::isSpriteInScreen()
{
    if (NULL != getInnerSprite())
    {
        CCRect screen;
        screen.origin = CCPointZero;
        screen.size = CCDirector::sharedDirector()->getWinSize();
        if (screen.intersectsRect(getInnerSprite()->boundingBox()))
        {
            return true;
        }
    }
    
    return false;
}



void CVisibleObject::setSpriteScaleX(float sx)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleX(sx);
    }
}



void CVisibleObject::setSpriteScaleY(float sy)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleY(sy);
    }
}



void CVisibleObject::setSpriteScale(float s)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScale(s);
    }
}



void CVisibleObject::removeSpriteFromParentAndCleanup(bool cleanup)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->removeFromParentAndCleanup(cleanup);
    }
}



bool CVisibleObject::runSpriteAction(CCAction* action)
{
    CCAssert(NULL != action, "action can't be NULL!");
    if (NULL == getInnerSprite())
    {
        return false;
    }

    getInnerSprite()->runAction(action);
    
    m_runningActions.addObject(action);
    return true;
}



void CVisibleObject::stopSpriteAllActions()
{
    CCNode* node = getInnerSprite();
    
    if (node)
    {
        node->stopAllActions();
    }
}



void CVisibleObject::setSpriteAnchorPoint(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setAnchorPoint(point);
    }
}



bool CVisibleObject::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    if (parent == NULL)
    {
        CCString* batchNodeName = getBatchNodeNameFromDict();
        string name;
        if (batchNodeName)
        {
            name = batchNodeName->getCString();
        }

        bool isBatchNode;
        parent = BATCH_NODE_MANAGER->getNodeByName(name, isBatchNode);

    }
    if (NULL != getInnerSprite())
    {
        parent->addChild(getInnerSprite(), zOrder, tag);
        return true;
    }
    return false;
}



int CVisibleObject::getCollisionGroup()
{
    return getCollisionGroupFromDict();
}




void CVisibleObject::turnOffCollision()
{
    CObjectBase::turnOffCollision();
    m_isCachePosition = false;
}



void CVisibleObject::turnOnCollision()
{
    CObjectBase::turnOnCollision();
    m_isCachePosition = true;
    updateBoundingBoxInWorldSpace();
}



void CVisibleObject::die()
{
    CObjectBase::die();

    CCObject* pObj;
    CCARRAY_FOREACH(&m_runningActions, pObj)
    {
        if (NULL != getInnerSprite())
        {
            getInnerSprite()->stopAction(dynamic_cast<CCAction*>(pObj));
        }
    }
    m_runningActions.removeAllObjects();
}



void CVisibleObject::revive()
{
    CObjectBase::revive();
}



void CVisibleObject::clearThis()
{
    m_runningActions.removeAllObjects();
    setSensor(NULL);
}



void CVisibleObject::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void CVisibleObject::onSensor(CCObject* obj)
{
    
}


void CVisibleObject::setSensorType(CSensor* pSensor)
{
    
}



void CVisibleObject::setSpriteRotation(float degree)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setRotation(degree);
    }
}



float CVisibleObject::getSpriteRatatioin()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getRotation();
    }
    
    return 0.f;
}



void CVisibleObject::setSpriteFlipX(bool f)
{
    CC_ASSERT(false);
}



void CVisibleObject::setSpriteFlipY(bool f)
{
    CC_ASSERT(false);
}


bool CVisibleObject::getSpriteFlipX()
{
    CC_ASSERT(false);
}



bool CVisibleObject::getSpriteFlipY()
{
    CC_ASSERT(false);
}
