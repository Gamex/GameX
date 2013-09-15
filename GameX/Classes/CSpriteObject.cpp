//
//  CSpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CSpriteObject.h"
#include "CBatchNodeManager.h"

DEFINE_DICTFUNC(CSpriteObject, int, MaxLevel, 0);
DEFINE_DICTFUNC_STR(CSpriteObject, FileType);
DEFINE_DICTFUNC_STR(CSpriteObject, FileName);
DEFINE_DICTFUNC_STR(CSpriteObject, FileNameInFarm);
DEFINE_DICTFUNC_STR(CSpriteObject, InitState);
DEFINE_DICTFUNC_STR(CSpriteObject, FarmState);
DEFINE_DICTFUNC_ARRAY(CSpriteObject, States);

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



bool CSpriteObject::init(CCDictionary* pObjectDict)
{
    do {
        BREAK_IF(!CVisibleObject::init(pObjectDict));
        CCString* fileType = getFileTypeFromDict();
        BREAK_IF(NULL == fileType);
        CCString* fileName = getFileNameFromDict();
        BREAK_IF(NULL == fileName);
        
        if (getMaxLevelFromDict() > 0)
        {
            fileName = CCString::createWithFormat("%s%d", fileName->getCString(), getLevel() - 1);
        }
        
        if (fileType->compare("ccbi") == 0)
        {
            fileName = CCString::createWithFormat("%s.ccbi", fileName->getCString());
            BREAK_IF(!setSpriteFromCcbi(fileName->getCString()));
        }
        else
        {
            BREAK_IF(!setSprite(fileName->getCString()));
        }

        return true;
    } while (false);
    
    return false;
}


bool CSpriteObject::setSpriteFromCcbi(const char* name)
{
    // Create auto-release node loader
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

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


//void CSpriteObject::setContentSize(CCSize size)
//{
//    CVisibleObject::setContentSize(size);
//    
//    if (m_pSprite)
//    {
//        m_pSprite->setContentSize(size);
//    }
//}


//void CSpriteObject::setCCBReaderRootContainerSize(CCSize size)
//{
//    if (pCCBReader_)
//    {
////        pCCBReader_->getAnimationManager()->setRootContainerSize(size);
//    }
//}


void CSpriteObject::setActionDelegate(CSpriteActionDelegate* pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<CCObject*>(m_pActionDelegate));
    m_pActionDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<CCObject*>(m_pActionDelegate));
}


void CSpriteObject::clearAll()
{
    CObjectBase::clearAll();
 
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



bool CSpriteObject::playAnimation(const string& name, bool forceReplay)
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


//CCNode* CSpriteObject::getCCBReaderRootNode() const
//{
//    if (pCCBReader_)
//    {
//        return pCCBReader_->getAnimationManager()->getRootNode();
//    }
//    
//    return NULL;
//}




void CSpriteObject::revive()
{
    CVisibleObject::revive();
    
    CCString* initState = getInitStateFromDict();
    if (initState != NULL)
    {
        changeState(0);     // zero for default state
    }

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

