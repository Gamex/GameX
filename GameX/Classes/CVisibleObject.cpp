//
//  CVisibleObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CVisibleObject.h"
#include "CBatchNodeManager.h"



CVisibleObject::CVisibleObject() :
m_isCachePosition(false)
, m_pSensor(NULL)
{
    m_runningActions.init();
}



CVisibleObject::~CVisibleObject()
{
    clearThis();
}



void CVisibleObject::update(float dt)
{
    CObjectBase::update(dt);

    updateSlots(dt);
    
    updateBoundingBoxInWorldSpace();
}



void CVisibleObject::updateBoundingBoxInWorldSpace()
{
    if (!m_isCachePosition)
    {
        return;
    }

    Node* pInnerSprite = getInnerSprite();
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
    
    Rect b1 = getSpriteBoundingBoxInWorldSpace();
    Rect b2 = pObj->getSpriteBoundingBoxInWorldSpace();
    
    return b1.intersectsRect(b2);
}




Rect CVisibleObject::getSpriteBoundingBox() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getBoundingBox();
    }
    
    return Rect::ZERO;
}



Rect CVisibleObject::getSpriteBoundingBoxInWorldSpace()
{ 
    if (!m_isCachePosition)
    {
        Node* pInnerSprite = getInnerSprite();
        
        m_boundingBoxInWorldSpace = getSpriteBoundingBox();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
        }
    }
    
    return m_boundingBoxInWorldSpace;
}



Point CVisibleObject::getSpritePositionInWorldSpace()
{
    if (!m_isCachePosition)
    {
        Node* pInnerSprite = getInnerSprite();
        
        m_positionInWorldSpace = getSpritePosition();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_positionInWorldSpace = pInnerSprite->getParent()->convertToWorldSpaceAR(m_positionInWorldSpace);
        }
    }
    
    return m_positionInWorldSpace;
}


Point CVisibleObject::getSpritePosition() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getPosition();
    }
    
    return Point::ZERO;
}



void CVisibleObject::setSpritePosition(const Point& point)
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




Size CVisibleObject::getSpriteContentSize()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getContentSize();
    }
    
    return Size::ZERO;
}



void CVisibleObject::setSpriteZOrder(int z)
{
    if (NULL != getInnerSprite())
    {
        Node* pParent = getInnerSprite()->getParent();
        if (NULL != pParent)
        {
            getInnerSprite()->setZOrder(z);
        }
    }
}



bool CVisibleObject::isSpriteInScreen()
{
    if (NULL != getInnerSprite())
    {
        Rect screen;
        screen.origin = Point::ZERO;
        screen.size = Director::getInstance()->getWinSize();
        if (screen.intersectsRect(getInnerSprite()->getBoundingBox()))
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



bool CVisibleObject::runSpriteAction(Action* action)
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
    Node* node = getInnerSprite();
    
    if (node)
    {
        node->stopAllActions();
    }
}



void CVisibleObject::setSpriteAnchorPoint(const Point& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setAnchorPoint(point);
    }
}



void CVisibleObject::setSpriteVertexZ(float z)
{
    CC_ASSERT(getInnerSprite());
    _setSpriteVertexZ_R(getInnerSprite(), z);
}



void CVisibleObject::_setSpriteVertexZ_R(Node* node, float z)
{
    Sprite* spr = (Sprite*)node;
    if (spr->getAtlasIndex() != Sprite::INDEX_NOT_INITIALIZED)
    {
        spr->setVertexZ(z);
        spr->setDirty(true);
        spr->updateTransform();
        Array* children = node->getChildren();
        Object* obj;
        CCARRAY_FOREACH(children, obj)
        {
            CC_ASSERT(obj);
            _setSpriteVertexZ_R((Node*)obj, z);
        }
    }
    else
    {
        node->setVertexZ(z);
    }
}



float CVisibleObject::getSpriteVertexZ() const
{
    CC_ASSERT(getInnerSprite());
    return getInnerSprite()->getVertexZ();
}



bool CVisibleObject::attachSpriteTo(Node* parent, int zOrder, int tag)
{
    CC_ASSERT(parent);
    CC_ASSERT(getInnerSprite());

    parent->addChild(getInnerSprite(), zOrder, tag);
    
    return true;
}



bool CVisibleObject::dettachSpriteFrom(bool cleanup)
{
    Node* node = getInnerSprite();
    CC_ASSERT(node);
    node->removeFromParentAndCleanup(cleanup);
    
    return true;
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

    Object* pObj;
    CCARRAY_FOREACH(&m_runningActions, pObj)
    {
        if (NULL != getInnerSprite())
        {
            getInnerSprite()->stopAction(dynamic_cast<Action*>(pObj));
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
    if (m_pSensor)
    {
        m_pSensor->clearAll();
        setSensor(NULL);
    }
}



void CVisibleObject::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void CVisibleObject::onSensor(Object* obj)
{
    
}


void CVisibleObject::onSetSensorType(CSensor* pSensor)
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
    return false;
}



bool CVisibleObject::getSpriteFlipY()
{
    CC_ASSERT(false);
    return false;
}


void CVisibleObject::_enableAlphaTestR(Node* node, float value)
{
    CC_ASSERT(node);
    GLProgram* program = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    node->setShaderProgram(program);
        program->use();
    
    GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
    
    // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
    program->setUniformLocationWith1f(alphaValueLocation, value);


    Array* children = node->getChildren();
    Object* obj;
    CCARRAY_FOREACH(children, obj)
    {
        _enableAlphaTestR((Node*)obj, value);
    }
}



void CVisibleObject::enableAlphaTest(float value)
{
    _enableAlphaTestR(getInnerSprite(), value);
}



bool CVisibleObject::addSlot(CVisibleObject* vo, int tag)
{
    auto it = m_slots.find(tag);
    if (it == m_slots.end())
    {
        vo->setTag(tag);
        m_slots[tag] = vo;
        
        return true;
    }
    
    
    return false;
}



void CVisibleObject::removeSlot(CVisibleObject* vo)
{
    auto it = m_slots.find(vo->getTag());
    if (it != m_slots.end())
    {
        m_slots.erase(it);
    }
}



void CVisibleObject::removeSlotByTag(int tag)
{
    auto it = m_slots.find(tag);
    if (it != m_slots.end())
    {
        m_slots.erase(it);
    }
}



void CVisibleObject::updateSlots(float dt)
{
    Point pt = getSpritePosition();
    auto it = m_slots.begin();
    for (; it != m_slots.end(); ++it)
    {
        CVisibleObject* vo = (*it).second;
        vo->setSpritePosition(pt + vo->getPosition());
        
        vo->update(dt);
    }
}





