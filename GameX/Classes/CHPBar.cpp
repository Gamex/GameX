//
//  CHPBar.cpp
//  TheForce
//
//  Created by Ray M on 13-2-19.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "Common.h"
#include "CHPBar.h"



CHPBar::CHPBar() :
m_percentage(1.f)
,m_pBar(nullptr)
{

}



CHPBar::~CHPBar()
{
    clearThis();
}



void CHPBar::setPercentage(float percentage)
{
    m_percentage = percentage;
//    if (m_percentage < .5f)
//    {
//        m_percentage = .5f;
//    }
    updateBar();
}



bool CHPBar::init(const char* foregroundName, const char* backgroundName)
{
    do
    {
        BREAK_IF_FAILED(CSpriteObject::init());
        BREAK_IF_FAILED(setSprite(backgroundName));
        
        setBar((CScale9SpriteObject*)OBJECT_FACTORY->createInstance("CScale9SpriteObject"));
        BREAK_IF_FAILED(getBar());
        BREAK_IF_FAILED(m_pBar->init(foregroundName));
       
        OrigBarSize_ = m_pBar->getSpriteContentSize();
        
        addChild(m_pBar);

        updateBar();
        return true;
    } while (false);
    
    return false;
}



bool CHPBar::attachSpriteTo(Node* parent, int zOrder, int tag)
{
    do
    {
        BREAK_IF_FAILED(CSpriteObject::attachSpriteTo(parent, zOrder, tag));
        m_pBar->attachSpriteTo(parent, zOrder);

        return true;
    } while (false);
    
    return false;
}



void CHPBar::clearAll()
{
    CSpriteObject::clearAll();
    clearThis();
}



void CHPBar::clearThis()
{
    if (getBar())
    {
        getBar()->clearAll();
        getBar()->removeFromParentAndCleanup(true);
        setBar(nullptr);
    }
}



void CHPBar::updateBar()
{
    if (nullptr == getInnerSprite() || nullptr == m_pBar)
    {
        return;
    }
    
    if (FLT_EQUAL(m_percentage, 0.f))
    {
        m_pBar->setSpriteVisible(false);
    }
    else
    {
        m_pBar->setSpriteVisible(true);
        
        Size sz = OrigBarSize_;
        sz.width = OrigBarSize_.width * m_percentage;

        m_pBar->setSpritePreferredSize(sz);
    }
}



void CHPBar::update(float dt)
{
    CSpriteObject::update(dt);
    
    Point pt = getSpritePosition();
    Size sz = m_pBar->getSpriteContentSize();

    
    Size bkgSize = getSpriteContentSize();
    pt.x -= (bkgSize.width - sz.width) * .5f - 2;

    m_pBar->setSpritePosition(pt);

}



void CHPBar::setSpriteVisible(bool visible)
{
    CSpriteObject::setSpriteVisible(visible);
    m_pBar->setSpriteVisible(visible);
}
