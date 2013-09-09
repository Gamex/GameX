//
//  CTransitLayer.cpp
//  GingyBattle
//
//  Created by Ming Zhao on 3/1/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#include "CTransitLayer.h"
#include "CAnimationCache.h"

#define TAG_LOADING_SPRITE      100

IMPLEMENT_SINGLETON(CTransitLayer);


CTransitLayer::CTransitLayer()
{
    
}


CTransitLayer::~CTransitLayer()
{
}


bool CTransitLayer::init()
{  
    if (!this->addLayers())
    {
        return false;
    }
    
    return true;
}


void CTransitLayer::onEnter()
{
    CBaseLayer::onEnter();
    
    this->runLoadingAnimation(true);
}


void CTransitLayer::onExit()
{
    CBaseLayer::onExit();
    
    CCDirector::sharedDirector()->setNotificationNode(NULL);
}


void CTransitLayer::unLoad()
{
    this->runAction(ANIMATION_CACHE->createFadeToAction(1.0f, 255, CCCallFunc::create(this, callfunc_selector(CTransitLayer::onExit))));
}


bool CTransitLayer::addLayers()
{
    // Color layer
    if (!CCLayer::init())
    {
        return false;
    }
    
    // Background
    CCScale9Sprite* pBackground = CBaseLayer::createTile("background", m_obContentSize, ccp(m_obContentSize.width / 2, m_obContentSize.height / 2));
    this->addChild(pBackground, -100);
    
    // Add loading aniamtion
    CCSprite* loadingSprite = CCSprite::createWithSpriteFrameName("loading0");
    loadingSprite->setPosition(ccp(m_obContentSize.width / 2, m_obContentSize.height / 2));
    this->addChild(loadingSprite, 0, TAG_LOADING_SPRITE);
    
    return true;
}


void CTransitLayer::runLoadingAnimation(bool needCallback)
{
    CCAction* action = NULL;
    if (needCallback)
    {
        action = ANIMATION_CACHE->createActionByAnimationName("Loading",
                                                              false,
                                                              CCCallFunc::create(this, callfunc_selector(CTransitLayer::loadingAnimationDidFinished)));

    }
    else
    {
        action = ANIMATION_CACHE->createActionByAnimationName("Loading", true);
    }
    
    CCSprite* loadingSprite = static_cast<CCSprite*>(getChildByTag(TAG_LOADING_SPRITE));
    CCAssert(loadingSprite, "Invalid loading sprite.");
    loadingSprite->runAction(action);
}


void CTransitLayer::loadingAnimationDidFinished()
{
    go(m_outLayer, false);
}


