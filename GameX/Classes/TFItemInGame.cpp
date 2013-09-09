//
//  TFItemInGame.cpp
//  TheForce
//
//  Created by Ray M on 13-2-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFItemInGame.h"
#include <cmath>

TFItemInGame::TFItemInGame() :
m_isInMagneticField(false)
{
    
}



TFItemInGame::~TFItemInGame()
{
    clearThis();
}



void TFItemInGame::checkCollision(TFCollisionProtocol* rb)
{
//    TFHero* pHero = dynamic_cast<TFHero*>(rb);
//    if (pHero)
//    {
//        die();
//    }
}



void TFItemInGame::update(float dt)
{
    CSpriteObject::update(dt);
    
    if (!isDead())
    {
        if (getSpritePosition().y <= -getSpriteBoundingBox().size.height/2.f)
        {
//            changeState(string("Dead"), string());
            die();
        }
        

        if (m_isInMagneticField)
        {
            m_timeToAttract -= dt;
            
            if (m_timeToAttract <= 0)
            {
                m_timeToAttract = .01;
            }
            
            CCPoint pt = getSpritePosition();
            float diffX = pt.x - m_magnetPos.x;
            float diffY = pt.y - m_magnetPos.y;
            
            float xStep = (abs(diffX) / m_timeToAttract) * dt;
            float yStep = (abs(diffY) / m_timeToAttract) * dt * 2.f;
            
            if (diffX >= 0.f && diffY >= 0.f)
            {
                pt.x -= xStep;
                pt.y -= yStep;
                pt.x = pt.x < m_magnetPos.x ? m_magnetPos.x : pt.x;
                pt.y = pt.y < m_magnetPos.y ? m_magnetPos.y : pt.y;
            }
            else if (diffX <= 0.f && diffY >= 0.f)
            {
                pt.x += xStep;
                pt.y -= yStep;
                pt.x = pt.x > m_magnetPos.x ? m_magnetPos.x : pt.x;
                pt.y = pt.y < m_magnetPos.y ? m_magnetPos.y : pt.y;
            }
            else if (diffX >= 0.f && diffY <= 0.f)
            {
                pt.x -= xStep;
                pt.y += yStep;
                pt.x = pt.x < m_magnetPos.x ? m_magnetPos.x : pt.x;
                pt.y = pt.y > m_magnetPos.y ? m_magnetPos.y : pt.y;
            }
            else if (diffX <= 0.f && diffY <= 0.f)
            {
                pt.x += xStep;
                pt.y += yStep;
                pt.x = pt.x > m_magnetPos.x ? m_magnetPos.x : pt.x;
                pt.y = pt.y > m_magnetPos.y ? m_magnetPos.y : pt.y;
            }
            setSpritePosition(pt);
        }
    }
}



void TFItemInGame::initListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TFItemInGame::onMagnetActive), NOTIFICATION_MAGNET_ON, NULL);
}



void TFItemInGame::removeAllListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_MAGNET_ON);
}



void TFItemInGame::onMagnetActive(CCObject* pObject)
{
    CCRect* rect = dynamic_cast<CCRect*>(pObject);
    if (NULL == rect)
    {
        return;
    }
    
    CCPoint thisPt = getSpritePosition();
    if (!m_isInMagneticField)
    {
        if (abs(thisPt.x - rect->origin.x) < rect->size.width &&
            abs(thisPt.y - rect->origin.y) < rect->size.height)
        {
            m_isInMagneticField = true;
            m_timeToAttract = 0.3f;
            getInnerSprite()->stopAllActions();
        }
    }
    else
    {
        m_magnetPos = rect->origin;
    }
}



bool TFItemInGame::init(CCDictionary* pObjectDict)
{
    if (!CSpriteObject::init(pObjectDict))
    {
        return false;
    }

#ifdef DEBUG
    m_itemName = getNameFromDict()->getCString();
#endif
    
    initListener();
    return true;
}



void TFItemInGame::clearAll()
{
    CSpriteObject::clearAll();
    clearThis();
}



void TFItemInGame::clearThis()
{
    removeAllListener();
    m_isInMagneticField = false;
}



void TFItemInGame::die()
{
    CSpriteObject::die();
    
    m_isInMagneticField = false;
    
    removeAllListener();
}



void TFItemInGame::revive()
{
    CSpriteObject::revive();
    
    initListener();
}



void TFItemInGame::completedAnimationSequenceNamed(const char *name)
{
    CSpriteObject::completedAnimationSequenceNamed(name);
}


