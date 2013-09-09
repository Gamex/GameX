//
//  CDirectionBullet.h
//  GameX
//
//  Created by 马 俊 on 13-7-1.
//
//

#ifndef __GameX__CDirectionBullet__
#define __GameX__CDirectionBullet__

#include "CBulletBase.h"

#include "CSpriteObject.h"

USING_NS_CC;
using namespace std;

#define BULLET_STATE_MOVE       "Move"


class CDirectionBullet : public CBulletBase
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CDirectionBullet);
    virtual ~CDirectionBullet();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);
    
    virtual float getDamage();
    
    virtual void setShootDirection(const CCPoint& direction)
    {
        m_shootDirection = direction;
    }
    
    virtual void launch();
#ifdef DEBUG
    virtual string whoAmI(){return "CDirectionBullet";}
#endif
    
    DECLARE_DICTFUNC(float, Damage);
    DECLARE_DICTFUNC(float, Speed);
protected:
    CDirectionBullet();
    virtual void addCollisionHandlers();
    
    virtual void onCollideWithTarget(TFCollisionProtocol* obj);
    
    float m_speed;
    CCPoint m_shootDirection;
private:
    
};


#endif /* defined(__GameX__CDirectionBullet__) */
