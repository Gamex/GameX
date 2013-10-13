//
//  CBallisticBullet.h
//  GameX
//
//  Created by 马 俊 on 13-6-23.
//
//

#ifndef __GameX__CBulletBallistic__
#define __GameX__CBulletBallistic__

#include "CBulletBase.h"
#include "CRole.h"

class CBallisticBullet : public CBulletBase
{
    friend class CObjectBase;
    CC_SYNTHESIZE(CRole*, m_shootTarget, ShootTarget);
public:
    FACTORY_CREATE_FUNC(CBallisticBullet);
    virtual ~CBallisticBullet();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);
    
    virtual float getDamage();
    
    virtual void launch();
#ifdef DEBUG
    virtual std::string whoAmI(){return "CBallisticBullet";}
#endif

    DECLARE_DICTFUNC(float, Damage);
    DECLARE_DICTFUNC(float, Speed);
protected:
    CBallisticBullet();
    virtual GBCollisionType getCollisionType();
    virtual void addCollisionHandlers();
    
    virtual void onCollideWithTarget(TFCollisionProtocol* obj);
    
    virtual void onHitTarget();

private:
};



#endif /* defined(__GameX__CBulletBallistic__) */
