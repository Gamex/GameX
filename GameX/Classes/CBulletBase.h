//
//  CBulletBase.h
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFBulletBase__
#define __TheForce__TFBulletBase__

#include "Common.h"

#include "CSpriteObject.h"


#define BULLET_STATE_MOVE       "Move"

class CRole;

class CBulletBase : public CSpriteObject
{
public:
    virtual ~CBulletBase();
    virtual void update(float dt);
    virtual float getDamage() = 0;
    virtual void launch() = 0;

protected:
    CBulletBase();
    virtual GBCollisionType getCollisionType();
    virtual void addCollisionHandlers() = 0;

private:

};


#endif /* defined(__TheForce__TFBulletBase__) */
