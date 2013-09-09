//
//  CBallisticGun.h
//  GameX
//
//  Created by 马 俊 on 13-6-29.
//
//

#ifndef __GameX__CBallisticGun__
#define __GameX__CBallisticGun__

// 抛物线子弹，用于弓箭等走上抛物线轨迹的。
// 点对点,需要CRole对象作为目标（ShootTarget）
// 只对目标造成伤害，忽略一切飞行过程中的碰撞物体

#include "CDirectionGun.h"
#include "CRole.h"


class CBallisticGun : public CGunBase
{
    friend class CObjectBase;
    CC_SYNTHESIZE(bool, m_isAutoGun, AutoGun);
//    CC_SYNTHESIZE(CRole*, m_shootTarget, ShootTarget);
public:
    FACTORY_CREATE_FUNC(CBallisticGun);
    virtual ~CBallisticGun();
    virtual bool init(CCDictionary* pObjectDict);

    virtual void shoot();
    virtual void update(float dt);
    
    DECLARE_DICTFUNC(float, Frequency);
protected:
    CBallisticGun();
    void clearThis();
    virtual void didShoot();
    
    float m_coolDownTime;
    float m_frequency;

private:
    bool m_prepareToShoot;
};

#endif /* defined(__GameX__CBallisticGun__) */
