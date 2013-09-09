//
//  CCControlToggleButton.cpp
//  GingyBattle
//
//  Created by Ming Zhao on 4/24/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#include "CCControlToggleButton.h"

CCControlToggleButton::CCControlToggleButton()
: m_toggleValue(false)
, toggleOn_(NULL)
, toggleOff_(NULL)
{
    
}


CCControlToggleButton::~CCControlToggleButton()
{
    setToggleOn(NULL);
    setToggleOff(NULL);
}


CCControlToggleButton* CCControlToggleButton::createWithToggles(CCScale9Sprite* toggleOn, CCScale9Sprite* toggleOff)
{
    CCControlToggleButton *pRet = new CCControlToggleButton();

    if (pRet && pRet->initWithToggles(toggleOn, toggleOff))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool CCControlToggleButton::initWithToggles(CCScale9Sprite* toggleOn, CCScale9Sprite* toggleOff)
{
    CCAssert(toggleOn && toggleOff, "Invalid CCScale9Sprite.");
    
    do
    {
        CC_BREAK_IF(!initWithBackgroundSprite(toggleOn));
        setToggleOn(toggleOn);
        setToggleOff(toggleOff);
        m_toggleValue = true;
        
        return true;
    } while (false);
    
    return false;
}


bool CCControlToggleButton::getToggleValue()
{
    return m_toggleValue;
}


void CCControlToggleButton::setToggleValue(bool val)
{
    m_toggleValue = val;
    
    if (m_toggleValue)
    {
        setBackgroundSpriteForState(toggleOn_, CCControlStateNormal);
    }
    else
    {
        setBackgroundSpriteForState(toggleOff_, CCControlStateNormal);
    }
}


bool CCControlToggleButton::ccTouchBegan(CCTouch* pTouch, CCEvent *pEvent)
{    
    return CCControlButton::ccTouchBegan(pTouch, pEvent);
}


void CCControlToggleButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCControlButton::ccTouchMoved(pTouch, pEvent);
}


void CCControlToggleButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isTouchInside(pTouch))
    {
//        m_toggleValue = !m_toggleValue;
//        if (m_toggleValue)
//        {
//            setBackgroundSpriteForState(toggleOn_, CCControlStateNormal);
//        }
//        else
//        {
//            setBackgroundSpriteForState(toggleOff_, CCControlStateNormal);
//        }
        setToggleValue(!m_toggleValue);
    }
    
    CCControlButton::ccTouchEnded(pTouch, pEvent);
}


void CCControlToggleButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCControlButton::ccTouchCancelled(pTouch, pEvent);
}

