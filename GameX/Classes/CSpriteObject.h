//
//  CSpriteObject.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFSpriteObject__
#define __TheForce__TFSpriteObject__

#include "CVisibleObject.h"
#include "CSpriteActionDelegate.h"
#include "CCBReader/CCBReader.h"
#include <map>

USING_NS_CC;
USING_NS_CC_EXT;

class CSpriteObject
: public CVisibleObject
, public CCBAnimationManagerDelegate
, public CCBSelectorResolver
{
    CC_SYNTHESIZE_RETAIN(CCBReader*, pCCBReader_, CCBReader);
public:
    FACTORY_CREATE_FUNC(CSpriteObject);
	virtual ~CSpriteObject();

    virtual void update(float dt);
    
    virtual void clearAll();

    virtual void revive();
    
    virtual void setActionDelegate(CSpriteActionDelegate* pDelegate);

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
    { return nullptr; };
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
    { return nullptr; };
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
    { return nullptr; };

    virtual Node* getInnerSprite() const;
    virtual void setSpriteFlipX(bool f);
    virtual void setSpriteFlipY(bool f);
    virtual bool getSpriteFlipX();
    virtual bool getSpriteFlipY();

    virtual void endState();
    virtual bool playAnimation(const std::string& name, bool forceReplay = false);
//    virtual bool playAnimation(int id, bool forceReplay = false);

    
protected:
    CSpriteObject();
    void clearThis();
    
    virtual void setInnerSprite(Sprite* var);
    virtual void completedAnimationSequenceNamed(const char *name);
    
    bool setSpriteFromCcbi(const char* name);
    bool setSprite(const char* name);
    
    void setSpriteFlipXRecursive(Sprite* spr, bool f);
    void setSpriteFlipYRecursive(Sprite* spr, bool f);
    CSpriteActionDelegate* m_pActionDelegate;
private:
    Sprite* pSprite_;
    bool isAnimationLoopEnd_;
};

#endif /* defined(__TheForce__TFSpriteObject__) */
