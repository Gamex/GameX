//
//  CGameEffect.h
//  GameX
//
//  Created by 马 俊 on 13-10-23.
//
//

#ifndef __GameX__CGameEffect__
#define __GameX__CGameEffect__

#include "Common.h"
#include "CSpriteObject.h"

#define EFFECT_ANIMATION_RUN        "Run"

class CGameEffect
: public CSpriteObject
{
    CC_SYNTHESIZE(float, m_damage, Damage);
    CC_SYNTHESIZE(CRole*, m_effectOwner, EffectOwner);
public:
    FACTORY_CREATE_FUNC(CGameEffect);
    
    virtual ~CGameEffect();

    virtual bool init(const string& ccbi_name);
    virtual bool attachSpriteTo(CCNode* parent, int zOrder = 0, int tag = -1);

    virtual void die();
    virtual void revive();
    virtual void update(float dt);
    virtual void clearAll();
    
    virtual void setEffectTarget(CRole* target);
    virtual CRole* getEffectTarget();
    
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);

protected:
    CGameEffect();

    void clearThis();
    
    virtual void onEffectHit(CCNode* obj);
    virtual void onEffectOver(CCNode* obj);
    
    CRole* m_effectTarget;
};

#endif /* defined(__GameX__CGameEffect__) */
