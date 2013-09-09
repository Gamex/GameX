//
//  CBaseLayer.h
//  GingyBattle
//
//  Created by Ming Zhao on 3/1/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef __GingyBattle__GBBaseLayer__
#define __GingyBattle__GBBaseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Common.h"

class CCControlToggleButton;

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


class CBaseLayer : public CCLayer
{
public:
    CBaseLayer();
    ~CBaseLayer();
    
    static CCScale9Sprite* createTile(const char* spriteFrameName, CCSize size = CCSizeZero, CCPoint position = CCPointZero);
    static CCControlButton* createImageButton(const char* spriteFrameName, CCPoint position = CCPointZero);
    static CCControlButton* createImageButtonWithTitle(const char* title, GameFonts font, const char* spriteFrameName, CCPoint position = CCPointZero);
    static CCControlToggleButton* createToggleButton(const char* toggleOn, const char* toggleOff, CCPoint position = CCPointZero);
    static CCLabelBMFont* createLabelBMFont(const char* title, GameFonts font, CCTextAlignment alignment = kCCTextAlignmentCenter, CCPoint position = CCPointZero);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void unLoadTransitLayer();
    
    void go(LAYERS layer, bool needTransit = false);
    
    CC_SYNTHESIZE_RETAIN(CCArray*, m_popTargets, PopTargets);
    
protected:
    virtual CCScene* wrap(LAYERS layer);
    virtual void addPopTarget(CCNode* pNode);
    virtual void addCloseButton();
    virtual void menuCloseCallback(CCObject* pSender);
    
private:
};

#endif /* defined(__GingyBattle__GBBaseLayer__) */
