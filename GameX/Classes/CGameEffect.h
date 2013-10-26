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

class CGameEffect
: public CSpriteObject
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CGameEffect);
    
    virtual ~CGameEffect();

//    virtual void loadEffectData(const string& effectName);
    virtual bool init(CCDictionary* pObjectDict);
    virtual bool attachSpriteTo(CCNode* parent, int zOrder = 0, int tag = -1);

    virtual void die();
    virtual void revive();
    virtual void update(float dt);
    virtual void clearAll();
protected:
    CGameEffect();

    void clearThis();
};

#endif /* defined(__GameX__CGameEffect__) */
