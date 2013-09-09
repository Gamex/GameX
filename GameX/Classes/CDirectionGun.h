//
//  CDirectionGun.h
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFGun__
#define __TheForce__TFGun__

// 直线子弹
// 需要发射方向作为参数（shootDirection）
// 会与飞行过程中一切敌方做碰撞，并且造成伤害。


#include "CGunBase.h"


class CBulletBase;

class CDirectionGun : public CGunBase
{
    friend class CObjectBase;
    CC_SYNTHESIZE(bool, m_isAutoGun, AutoGun);
public:
    FACTORY_CREATE_FUNC(CDirectionGun);
    virtual ~CDirectionGun();
    virtual bool init(CCDictionary* pObjectDict);

    virtual void update(float dt);
    virtual void shoot();
    virtual void clearAll();

    DECLARE_DICTFUNC(float, Frequency);
protected:
    CDirectionGun();
    void clearThis();
    virtual void didShoot();

    float m_coolDownTime;
    float m_frequency;

    CCPoint m_direction;
private:
    bool m_prepareToShoot;

};


#endif /* defined(__TheForce__TFGun__) */
