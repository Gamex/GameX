//
//  CAnimationCache.h
//  GingyBattle
//
//  Created by Ming Zhao on 4/1/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef __GingyBattle__GBAnimationCache__
#define __GingyBattle__GBAnimationCache__

#include "Common.h"


class CAnimationCache
{
public:
    static CAnimationCache* getInstance();
    
    virtual void addAnimations(const char* pFileName);
    virtual CCAnimate* getAnimateByAnimationName(const char* name);
    virtual CCAnimation* getAnimationByName(const char* name);
    virtual CCAction* createActionByAnimationName(const char* name, bool repeated = true, CCCallFunc* callback = NULL);
    virtual CCAction* createMoveToAction(float duration, CCPoint pos, CCCallFunc* callback = NULL);
    virtual CCAction* createPopAction(float duration, CCCallFunc* callback = NULL);
    virtual CCAction* createVibrateAction(float duration, CCCallFunc* callback = NULL);
    virtual CCAction* createMovePauseAction(float moveDuration, float pauseDuration, CCPoint pausePosition, CCCallFunc* callback);
    virtual CCAction* createFadeToAction(float duration, GLubyte fadeTo, CCCallFunc* callback = NULL);
    
protected:
    
private:
    CAnimationCache();
    ~CAnimationCache();
    
    static CAnimationCache* spInstance_;
    
};

#define ANIMATION_CACHE (CAnimationCache::getInstance())

#endif /* defined(__GingyBattle__GBAnimationCache__) */
