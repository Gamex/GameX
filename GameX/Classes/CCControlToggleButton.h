//
//  CCControlToggleButton.h
//  GingyBattle
//
//  Created by Ming Zhao on 4/24/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef __GingyBattle__CCControlToggleButton__
#define __GingyBattle__CCControlToggleButton__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCControlToggleButton : public CCControlButton
{
public:
    CCControlToggleButton();
    virtual ~CCControlToggleButton();
    
    static CCControlToggleButton* createWithToggles(CCScale9Sprite* toggleOn, CCScale9Sprite* toggleOff);
    virtual bool initWithToggles(CCScale9Sprite* toggleOn, CCScale9Sprite* toggleOff);

    //events
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
//    CC_SYNTHESIZE(bool, m_toggleValue, ToggleValue);
    CC_PROPERTY(bool, m_toggleValue, ToggleValue);
    CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, toggleOn_, ToggleOn);
    CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, toggleOff_, ToggleOff);
    
protected:
private:
};

#endif /* defined(__GingyBattle__CCControlToggleButton__) */
