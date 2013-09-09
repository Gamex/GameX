//
//  CBaseLayer.cpp
//  GingyBattle
//
//  Created by Ming Zhao on 3/1/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#include "CBaseLayer.h"
#include "CTransitLayer.h"
#include "Common.h"
//#include "GBTexturesCache.h"
//#include "CAnimationCache.h"
#include "CCControlToggleButton.h"
#include "CBattleFieldLayer.h"


CBaseLayer::CBaseLayer()
: m_popTargets(NULL)
{
    
}


CBaseLayer::~CBaseLayer()
{
    setPopTargets(NULL);
}


void CBaseLayer::onEnter()
{
    CCLayer::onEnter();
    
    if (m_popTargets)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_popTargets, pObject)
        {
            CCNode* pNode = dynamic_cast<CCNode*>(pObject);
            if (pNode)
            {
                pNode->stopAllActions();
//                pNode->runAction(ANIMATION_CACHE->createPopAction(1.5f));
            }
        }
    }
}


void CBaseLayer::onExit()
{
    CCLayer::onExit();
}


void CBaseLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}


void CBaseLayer::unLoadTransitLayer()
{
//    CCDirector* pDirector = CCDirector::sharedDirector();
    
//    CTransitLayer* pLayer = dynamic_cast<CTransitLayer*>(pDirector->getNotificationNode());
//    if (pLayer)
//    {
//        pLayer->unLoad();
//    }
}


CCScale9Sprite* CBaseLayer::createTile(const char* spriteFrameName, CCSize size, CCPoint position)
{
    CCScale9Sprite* tile = CCScale9Sprite::createWithSpriteFrameName(spriteFrameName);
    if (size.equals(CCSizeZero))
    {
        CCSprite* pSprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
        if (pSprite)
        {
            size = pSprite->getContentSize();
        }
    }
    
    tile->setPreferredSize(size);
    tile->setAnchorPoint(ccp(0.5f, 0.5f));
    tile->setPosition(position);
    return tile;
}


CCControlButton* CBaseLayer::createImageButton(const char* spriteFrameName, CCPoint position)
{
    CCAssert(spriteFrameName && strlen(spriteFrameName) > 0, "Invalid sprite frame name.");
    
    do
    {
        CCSprite* pSprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
        CC_BREAK_IF(NULL == pSprite);
        CCSize size = pSprite->getContentSize();
        
        CCControlButton* pButton = CCControlButton::create(CCScale9Sprite::createWithSpriteFrameName(spriteFrameName));
        CC_BREAK_IF(NULL == pButton);
        pButton->setPreferredSize(size);
        pButton->setPosition(position);
        
        return pButton;
    } while (false);
    
    return NULL;
}


CCControlButton* CBaseLayer::createImageButtonWithTitle(const char* title, GameFonts font, const char* spriteFrameName, CCPoint position)
{
    CCAssert(title && strlen(title) > 0, "Invalid title.");
    CCAssert(spriteFrameName && strlen(spriteFrameName) > 0, "Invalid sprite frame name.");

    do
    {
        // majun
//        CCLabelBMFont* pLabel = CCLabelBMFont::create(title,
//                                                      TEXTURE_CACHE->getFontFileName(font).c_str());
//        CC_BREAK_IF(NULL == pLabel);
//        CCScale9Sprite* pBackground = CCScale9Sprite::createWithSpriteFrameName(spriteFrameName);
//        CC_BREAK_IF(NULL == pBackground);
//        CCControlButton* pButton = CCControlButton::create(pLabel, pBackground);
//        CC_BREAK_IF(NULL == pButton);
//        CCSize size = pLabel->getContentSize();
//        CCSize backgroundSize = pBackground->getContentSize();
//        size.width = 2 + size.width > backgroundSize.width ? size.width : backgroundSize.width;
//        size.height = 2 + size.height > backgroundSize.height ? size.height : backgroundSize.height;
//        pButton->setPreferredSize(size);
//        pButton->setPosition(position);
//        
//        return pButton;
    } while (false);
    
    return NULL;
}


CCControlToggleButton* CBaseLayer::createToggleButton(const char* toggleOn, const char* toggleOff, CCPoint position)
{
    CCAssert(toggleOn && strlen(toggleOn) > 0, "Invalid sprite frame name.");
    CCAssert(toggleOff && strlen(toggleOff) > 0, "Invalid sprite frame name.");
    
    do
    {
        CCSprite* pSpriteOn = CCSprite::createWithSpriteFrameName(toggleOn);
        CC_BREAK_IF(NULL == pSpriteOn);
        CCScale9Sprite* pScale9SpriteOn = CCScale9Sprite::createWithSpriteFrameName(toggleOn);
        CC_BREAK_IF(NULL == pScale9SpriteOn);
        pScale9SpriteOn->setPreferredSize(pSpriteOn->getContentSize());

        CCSprite* pSpriteOff = CCSprite::createWithSpriteFrameName(toggleOff);
        CC_BREAK_IF(NULL == pSpriteOff);
        CCScale9Sprite* pScale9SpriteOff = CCScale9Sprite::createWithSpriteFrameName(toggleOff);
        CC_BREAK_IF(NULL == pScale9SpriteOff);
        pScale9SpriteOff->setPreferredSize(pSpriteOff->getContentSize());
        
        CCControlToggleButton* pButton = CCControlToggleButton::createWithToggles(pScale9SpriteOn, pScale9SpriteOff);
        CC_BREAK_IF(NULL == pButton);
        pButton->setPreferredSize(pSpriteOn->getContentSize());
        pButton->setPosition(position);
        
        return pButton;
    } while (false);
    
    return NULL;
}


CCLabelBMFont* CBaseLayer::createLabelBMFont(const char* title, GameFonts font, CCTextAlignment alignment, CCPoint position)
{
    CCAssert(title, "Invalid title.");
    
    do {
        // majun
//        CCLabelBMFont* pLabel = CCLabelBMFont::create(title, TEXTURE_CACHE->getFontFileName(font).c_str(), kCCLabelAutomaticWidth, alignment, ccp(0.5f, 0.5f));
//        CC_BREAK_IF(NULL == pLabel);
//        
//        switch (alignment) {
//            case kCCTextAlignmentLeft:
//                pLabel->setAnchorPoint(ccp(0.0f, 0.5f));
//                break;
//            case kCCTextAlignmentRight:
//                pLabel->setAnchorPoint(ccp(1.0f, 0.5f));
//                break;
//            case kCCTextAlignmentCenter:
//                pLabel->setAnchorPoint(ccp(0.5f, 0.5f));
//                break;
//            default:
//                break;
//        }
//        
//        pLabel->setPosition(position);
//        return pLabel;
    } while (false);

    return NULL;
}


void CBaseLayer::go(LAYERS layer, bool needTransit)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    if (needTransit && pDirector->getNotificationNode())
    {
        return;
    }
    
    if (needTransit && layer != LAYERS_NONE)
    {        
        TRANSIT_LAYER->setOutLayer(layer);
        pDirector->setNotificationNode(TRANSIT_LAYER);
        TRANSIT_LAYER->onEnter();
    }
    else
    {
        CCScene* pScene = this->wrap(layer);
        
        if (pScene)
        {
            if (pDirector->getRunningScene())
            {
                pDirector->replaceScene(pScene);
            }
            else
            {
                pDirector->runWithScene(pScene);
            }
        }
    }
}


CCScene* CBaseLayer::wrap(LAYERS layer)
{
    CBaseLayer* pLayer = NULL;
    
//    switch (layer) {
//        case LAYERS_NONE:
//            pLayer = this;
//            break;
//        case LAYERS_MAIN:
////            pLayer = MAIN_LAYER;
//            break;
//        case LAYERS_GAME_BATTLE_FIELD:
//            pLayer = BATTLE_FIELD_LAYER;
//            break;
//        case LAYERS_SETTINGS:
////            pLayer = SETTINGS_LAYER;
//            break;
//        case LAYERS_UPGRADE:
////            pLayer = UPGRADE_LAYER;
//        default:
//            break;
//    }
    
    CCScene *pScene = CCScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}


void CBaseLayer::addPopTarget(CCNode* pNode)
{
    if (NULL == m_popTargets)
    {
        setPopTargets(CCArray::create());
    }
    
    m_popTargets->addObject(pNode);
}


void CBaseLayer::addCloseButton()
{
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(CBaseLayer::menuCloseCallback) );
    pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
}


void CBaseLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
