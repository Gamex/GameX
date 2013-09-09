//
//  CBallisticAOEBullet.h
//  GameX
//
//  Created by 马 俊 on 13-7-18.
//
//

#ifndef __GameX__CBallisticAOEBullet__
#define __GameX__CBallisticAOEBullet__

#include "CBallisticBullet.h"

#define BALLISTIC_AOE_BULLET_STATE_BOMB     "Bomb"

class CBallisticAOEBullet : public CBallisticBullet
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CBallisticAOEBullet);
    virtual ~CBallisticAOEBullet();
    
    virtual void update(float dt);
    
    DECLARE_DICTFUNC(float, DamageArea);
protected:
    CBallisticAOEBullet();
    
    virtual void onHitTarget();
    virtual void onCollideWithTarget(TFCollisionProtocol* obj);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    virtual void updateBoundingBoxInWorldSpace();
    
    bool m_startBomb;
    bool m_isBombed;
private:
};

#endif /* defined(__GameX__CBallisticAOEBullet__) */
