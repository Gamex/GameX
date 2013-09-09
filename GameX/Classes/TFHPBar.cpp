//
//  TFHPBar.cpp
//  TheForce
//
//  Created by Ray M on 13-2-19.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFHPBar.h"

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Common.h"

USING_NS_CC;


DEFINE_DICTFUNC_STR(TFHPBar, BarFileName);


TFHPBar::TFHPBar() :
m_percentage(.25f)
,m_pBar(NULL)
{

}



TFHPBar::~TFHPBar()
{
    clearThis();
}



void TFHPBar::setPercentage(float percentage)
{
    m_percentage = percentage;
    updateBar();
}



bool TFHPBar::init(CCDictionary* pObjectDict)
{
    if (!CSpriteObject::init(pObjectDict))
    {
        return false;
    }
    
    CCString* barFileName = getBarFileNameFromDict();
    
    setBar(dynamic_cast<CScale9SpriteObject*>(OBJECT_FACTORY->createInstance("CScale9SpriteObject")));
    if (!getBar() || !m_pBar->init(barFileName->getCString()))
    {
        return false;
    }
    
    OrigBarSize_ = m_pBar->getSpriteContentSize();
    m_pBar->setSpriteAnchorPoint(ccp(0.f, 0.5f));
  
    addChild(m_pBar);
    m_pBar->attachSpriteTo(m_pBar);

    updateBar();
    return true;
}



void TFHPBar::clearAll()
{
    CSpriteObject::clearAll();
    clearThis();
}



void TFHPBar::clearThis()
{
    if (getBar())
    {
        getBar()->clearAll();
        getBar()->removeFromParentAndCleanup(true);
        setBar(NULL);
    }
}



void TFHPBar::updateBar()
{
    if (NULL == getInnerSprite() || NULL == m_pBar)
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
        
        CCSize sz = m_pBar->getSpriteContentSize();
        sz.width = OrigBarSize_.width * m_percentage;

        m_pBar->setSpritePreferredSize(sz);
    }
}



void TFHPBar::update(float dt)
{
    CSpriteObject::update(dt);
    
    CCPoint pt(1, -3);
    // rewrite later!!
    pt = getInnerSprite()->convertToWorldSpace(pt);
    pt = m_pBar->convertToNodeSpace(pt);
    m_pBar->setSpritePosition(pt);
}



void TFHPBar::setSpriteVisible(bool visible)
{
    this->setVisible(visible);
    
    CSpriteObject::setSpriteVisible(visible);
}
