//
//  TFItemInGame.h
//  TheForce
//
//  Created by Ray M on 13-2-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFItemInGame__
#define __TheForce__TFItemInGame__

#include "CSpriteObject.h"

class TFItemInGame : public CSpriteObject
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(TFItemInGame);
    virtual ~TFItemInGame();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual void clearAll();
    virtual void checkCollision(TFCollisionProtocol* rb);
    virtual void update(float dt);
    virtual void die();
    virtual void revive();
    
    void initListener();
    void removeAllListener();
    void onMagnetActive(CCObject* pObject);
    
protected:
    TFItemInGame();
    void clearThis();
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    bool m_isInMagneticField;
    CCPoint m_magnetPos;
    float m_timeToAttract;
#ifdef DEBUG
    string m_itemName;
#endif
private:
};

#endif /* defined(__TheForce__TFItemInGame__) */
