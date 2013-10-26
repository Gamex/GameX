//
//  CSpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CSpriteObject.h"
#include "CBatchNodeManager.h"



CSpriteObject::CSpriteObject()
: pSprite_(NULL)
, pCCBReader_(NULL)
, m_pActionDelegate(NULL)
, isAnimationLoopEnd_(false)
{
    
}



CSpriteObject::~CSpriteObject()
{
    clearThis();
}



bool CSpriteObject::setSpriteFromCcbi(const char* name)
{
    // Create auto-release node loader
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    // Create a CCBReader, auto release.
    CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    // Read a ccbi file, return a CCNode instance.
    setInnerSprite(dynamic_cast<CCSprite*>(ccbReader->readNodeGraphFromFile(name, this)));

    if (NULL == getInnerSprite())
    {
        return false;
    }

    ccbReader->getAnimationManager()->setDelegate(this);
    
    setCCBReader(ccbReader);
    return true;
}


bool CSpriteObject::setSprite(const char* name)
{
    setInnerSprite(CCSprite::createWithSpriteFrameName(name));
    
    if (NULL == getInnerSprite())
    {
        return false;
    }
    setCCBReader(NULL);
    return true;
}



void CSpriteObject::setActionDelegate(CSpriteActionDelegate* pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<CCObject*>(m_pActionDelegate));
    m_pActionDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<CCObject*>(m_pActionDelegate));
}


void CSpriteObject::clearAll()
{
    CVisibleObject::clearAll();
 
    clearThis();
}



void CSpriteObject::clearThis()
{
    CCBReader* pCCBReader = getCCBReader();
    if (pCCBReader)
    {
        pCCBReader->getAnimationManager()->setDelegate(NULL);
    }
    setCCBReader(NULL);
    setActionDelegate(NULL);
    
    if (pSprite_ != NULL)
    {
        pSprite_->removeFromParentAndCleanup(true);
        setInnerSprite(NULL);
    }
}



bool CSpriteObject::playAnimation(const std::string& name, bool forceReplay)
{
    do
    {
        if (getCCBReader())
        {
            CCBAnimationManager* am = getCCBReader()->getAnimationManager();
            
            const char* runningAnimName = am->getRunningSequenceName();
            if (runningAnimName)
            {
                BREAK_IF(name.compare(am->getRunningSequenceName()) == 0 && !forceReplay);
            }
            CCArray* seq = am->getSequences();
            CCObject* pObj;
            CCARRAY_FOREACH(seq, pObj)
            {
                CCBSequence *seq = (CCBSequence*)pObj;
                if (name.compare(seq->getName()) == 0)
                {
                    am->runAnimationsForSequenceIdTweenDuration(seq->getSequenceId(), 0);
                }
            }
        }
        return true;
    } while (false);
    
    return false;
}




//bool CSpriteObject::playAnimation(int id, bool forceReplay)
//{
//    do
//    {
//        if (getCCBReader())
//        {
//            CCBAnimationManager* am = getCCBReader()->getAnimationManager();
//            am->runAnimationsForSequenceIdTweenDuration(id, 0);
//        }
//        return true;
//    } while (false);
//    
//    return false;
//}
//


void CSpriteObject::endState()
{
    this->changeState(STATE_NONE);
}


CCNode* CSpriteObject::getInnerSprite() const
{
    return pSprite_;
}



void CSpriteObject::setInnerSprite(CCSprite* var)
{
    if (pSprite_ != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(pSprite_);
        pSprite_ = var;
    } 
}



void CSpriteObject::revive()
{
    CVisibleObject::revive();
    
    changeState(STATE_NONE);
}

void CSpriteObject::completedAnimationSequenceNamed(const char *name)
{
    if (m_pActionDelegate)
    {
        m_pActionDelegate->completedAction(this, name);
    }
    
    isAnimationLoopEnd_ = true;
    
}




void CSpriteObject::update(float dt)
{
    CVisibleObject::update(dt);
}



void CSpriteObject::setSpriteFlipX(bool f)
{
    CC_ASSERT(pSprite_);
    setSpriteFlipXRecursive(pSprite_, f);
}



void CSpriteObject::setSpriteFlipY(bool f)
{
    CC_ASSERT(pSprite_);
    setSpriteFlipYRecursive(pSprite_, f);
}


void CSpriteObject::setSpriteFlipXRecursive(CCSprite* spr, bool f)
{
    spr->setFlipX(f);
    
    CCArray* children = spr->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj)
    {
        setSpriteFlipXRecursive(dynamic_cast<CCSprite*>(obj), f);
    }
}


void CSpriteObject::setSpriteFlipYRecursive(CCSprite* spr, bool f)
{
    spr->setFlipY(f);
    
    CCArray* children = spr->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj)
    {
        setSpriteFlipYRecursive(dynamic_cast<CCSprite*>(obj), f);
    }
}




bool CSpriteObject::getSpriteFlipX()
{
    CC_ASSERT(pSprite_);
    return pSprite_->isFlipX();
}



bool CSpriteObject::getSpriteFlipY()
{
    CC_ASSERT(pSprite_);
    return pSprite_->isFlipY();
}


