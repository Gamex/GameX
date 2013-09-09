//
//  CAnimationCache.cpp
//  GingyBattle
//
//  Created by Ming Zhao on 4/1/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#include "CAnimationCache.h"
#include <stdio.h>

#define ANIMATION_TYPE                      "Type"
#define ANIMATION_FRAME_NAME                "FrameName"
#define ANIMATION_FRAME_NUM                 "FrameNum"
#define ANIMATION_DELAY_PER_UNIT            "DelayPerUnit"
#define ANIMATION_RESTORE_ORIGINAL_FRAME    "RestoreOriginalFrame"
#define ANIMATION_LOOP                      "Loop"

CAnimationCache* CAnimationCache::spInstance_ = NULL;


CAnimationCache::CAnimationCache()
{
    
}


CAnimationCache::~CAnimationCache()
{
    
}


CAnimationCache* CAnimationCache::getInstance()
{
    if (!spInstance_)
    {
        spInstance_ = new CAnimationCache();
    }
    
    return spInstance_;
}


void CAnimationCache::addAnimations(const char* pFileName)
{
    CCAssert(pFileName && (strlen(pFileName) > 0), "Invalid file name.");
    
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(pFileName);
    if (NULL == dict)
    {
        __CCLOGWITHFUNCTION("Failed to retrieve file: %s", pFileName);
        return ;
    }
    
    
    CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
    CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        do
        {
            const char* key = pElement->getStrKey();
            CC_BREAK_IF(NULL == key || strlen(key) <= 0);
            CCDictionary* entry = dynamic_cast<CCDictionary*>(pElement->getObject());
            CC_BREAK_IF(NULL == entry);

            do
            {
                CCString* type = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_TYPE));
                CC_BREAK_IF(NULL == type || type->compare("SequenceFrame") != 0);
                CCString* frameName = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_FRAME_NAME));
                CC_BREAK_IF(NULL == frameName);
                CCString* frameNum = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_FRAME_NUM));
                CC_BREAK_IF(NULL == frameNum);
                CCString* delayPerUnit = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_DELAY_PER_UNIT));
                CC_BREAK_IF(NULL == delayPerUnit);
                CCString* restoreOriginalFrame = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_RESTORE_ORIGINAL_FRAME));
                CC_BREAK_IF(NULL == restoreOriginalFrame);
                CCString* loop = dynamic_cast<CCString*>(entry->objectForKey(ANIMATION_LOOP));
                CC_BREAK_IF(NULL == loop);
                
                CCArray* frames = CCArray::createWithCapacity(frameNum->intValue());
                char buffer[256] = {'\0'};
                
                for (int i = 0; i < frameNum->intValue(); i++) {
                    sprintf(buffer, "%s%d", frameName->getCString(), i);
                    CCSpriteFrame* frame = spriteFrameCache->spriteFrameByName(buffer);
                    frames->addObject(frame);
                }
                
                CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames);
                animation->setDelayPerUnit(delayPerUnit->floatValue());
                animation->setRestoreOriginalFrame(restoreOriginalFrame->boolValue());
                animation->setLoops(loop->intValue());
                
                animationCache->addAnimation(animation, key);
            } while (false);
        } while (false);
    }
}


CCAnimate* CAnimationCache::getAnimateByAnimationName(const char* name)
{
    do {
        CC_BREAK_IF(NULL == name || strlen(name) <= 0);
        CCAnimationCache* animationCache = CCAnimationCache::sharedAnimationCache();
        CCAnimation* animation = animationCache->animationByName(name);
        CC_BREAK_IF(NULL == animation);
        CCAnimate* animate = CCAnimate::create(animation);

        return animate;
    } while (false);

    return NULL;
}


CCAnimation* CAnimationCache::getAnimationByName(const char* name)
{
    do {
        CC_BREAK_IF(NULL == name || strlen(name) <= 0);
        CCAnimationCache* animationCache = CCAnimationCache::sharedAnimationCache();
        CCAnimation* animation = animationCache->animationByName(name);
        
        return animation;
    } while (false);
    
    return NULL;
}


CCAction* CAnimationCache::createActionByAnimationName(const char* name, bool repeated, CCCallFunc* callback)
{
    do
    {
        CCAnimate* animate = getAnimateByAnimationName(name);
        CC_BREAK_IF(NULL == animate);
        
        if (repeated)
        {
            return CCRepeatForever::create(animate);
        }
        else
        {
            if (callback)
            {
                return CCSequence::create(animate, callback, NULL);
            }
            else
            {
                return CCSequence::create(animate, NULL);
            }
        }
    } while (false);
    
    return NULL;
}


CCAction* CAnimationCache::createMoveToAction(float duration, CCPoint pos, CCCallFunc* callback)
{
    if (callback)
    {
        return CCSequence::create(CCMoveTo::create(duration, pos), callback, NULL);
    }
    else
    {
        return CCSequence::create(CCMoveTo::create(duration, pos), NULL);
    }
}


CCAction* CAnimationCache::createPopAction(float duration, CCCallFunc* callback)
{
    CCActionInterval* scale = CCScaleTo::create(0.0f, 0.2f);
    CCActionInterval* scaleBack = CCEaseElasticOut::create(CCScaleTo::create(duration, 1.0f));

    if (callback)
    {
        return CCSequence::create(scale, scaleBack, callback, NULL);
    }
    else
    {
        return CCSequence::create(scale, scaleBack, NULL);
    }
}



CCAction* CAnimationCache::createVibrateAction(float duration, CCCallFunc* callback)
{
//    CCFiniteTimeAction* scale1 = GBScale::create(1.05f);
//    CCFiniteTimeAction* vibrate = GBVibrate::create(duration);
//    CCFiniteTimeAction* scale2 = GBScale::create(1.f);
//    CCFiniteTimeAction* place = CCPlace::create(ccp(0.f, 0.f));
//  
//    if (callback)
//    {
//        return CCSequence::create(scale1, vibrate, scale2, place, callback, NULL);
//    }
//    else
//    {
//        return CCSequence::create(scale1, vibrate, scale2, place, NULL);
//    }
    
    return NULL;
}



CCAction* CAnimationCache::createMovePauseAction(float moveDuration, float pauseDuration, CCPoint pausePosition,  CCCallFunc* callback)
{
    do {
        CCFiniteTimeAction* move = dynamic_cast<CCFiniteTimeAction*>(createMoveToAction(moveDuration, pausePosition));
        CC_BREAK_IF(NULL == move);
        CCFiniteTimeAction* pause = CCDelayTime::create(pauseDuration);
        CC_BREAK_IF(NULL == pause);
        
        if (callback)
        {
            return CCSequence::create(move, pause, callback, NULL);
        }
        else
        {
            return CCSequence::create(move, pause, NULL);
        }
        
    } while (false);
    return NULL;
}



CCAction* CAnimationCache::createFadeToAction(float duration, GLubyte fadeTo, CCCallFunc* callback)
{
    do {
        CCFiniteTimeAction* fade = CCFadeTo::create(duration, fadeTo);
        CC_BREAK_IF(NULL == fade);
        if (callback)
        {
            return CCSequence::create(fade, callback, NULL);
        }
        else
        {
            return fade;
        }
        
    } while (false);
    
    return NULL;
}
