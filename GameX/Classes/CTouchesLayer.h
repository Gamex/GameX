//
//  CTouchesLayer.h
//  GingerBread
//
//  Created by Ming Zhao on 4/10/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef __GingerBread__CTouchesLayer__
#define __GingerBread__CTouchesLayer__

#include "cocos2d.h"
#include "CBaseLayer.h"

USING_NS_CC;

class CTouchesLayer : public CBaseLayer
{
    // Gesture settings
    CC_SYNTHESIZE(float, m_swipeThreshold, SwipeThreshold);
    CC_SYNTHESIZE(float, m_swipeTime, SwipeTime);
    CC_SYNTHESIZE(float, m_tapThreshold, TapThreshold);
    CC_SYNTHESIZE(float, m_tapTime, TapTime);
    CC_SYNTHESIZE(float, m_longTapThreshold, LongTapThreshold);
    CC_SYNTHESIZE(float, m_longTapTime, LongTapTime);
    CC_SYNTHESIZE(float, m_doubleTapTime, DoubleTapTime);
    
public:
    enum GBTouchDirection
    {
        TOUCH_DIRECTION_LEFT,
        TOUCH_DIRECTION_RIGHT,
        TOUCH_DIRECTION_UP,
        TOUCH_DIRECTION_DOWN
    };
    
    enum GBGesture
    {
        GESTURE_TAP,
        GESTURE_LONGTAP,
        GESTURE_SWIPE
    };
    
    CTouchesLayer();
    ~CTouchesLayer();
    
    
    // Override of touches
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    

    // Override for subclsss
    virtual void touchesBegan(CCSet* touches, CCEvent* event);
    virtual void touchesMoved(CCSet* touches, CCEvent* event);
    virtual void touchesEnded(CCSet* touches, CCEvent* event);
    
    // Easy touch callbacks
    virtual void touchBegan(CCPoint position);
    virtual void touchMoved(CCPoint position);
    virtual void touchEnded(CCPoint position);
    
    // Gesture Callbacks
    virtual void tapGesture(CCPoint position);
    virtual void doubleTapGesture(CCPoint position);
    virtual void longTapGesture(CCPoint position);
    virtual void swipeGesture(GBTouchDirection direction, float distance, float speed);
    
protected:
    
private:
    CCArray* allTouchesSet(CCSet* touches);
    void tapHandler(CCObject* caller);
    
    GBTouchDirection touchDirection_;
    // Touch positions
    CCPoint gestureStartPoint_;
    CCPoint gestureEndPoint_;
    CCPoint actualPoint_;
    CCPoint previousPoint_;

    bool touchHasMoved_;
    long touchStart_;
    bool swipeDone_;
    int  numberOfTaps_;
    
    long millisecondNow();
};

#endif /* defined(__GingerBread__CTouchesLayer__) */
