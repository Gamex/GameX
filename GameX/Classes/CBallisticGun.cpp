//
//  CBallisticGun.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-29.
//
//

#include "CBallisticGun.h"
#include "CBallisticBullet.h"

DEFINE_DICTFUNC(CBallisticGun, float, Frequency, 0);


CBallisticGun::CBallisticGun()
{
    
}



CBallisticGun::~CBallisticGun()
{
}



bool CBallisticGun::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF_FAILED(CGunBase::init(pObjectDict));
        
        m_frequency = getFrequencyFromDict();
        m_coolDownTime = m_frequency;
        
        return true;
    } while (false);
    
    return false;
}



void CBallisticGun::update(float dt)
{
    CGunBase::update(dt);
    
    // check target is alive
    
    m_coolDownTime -= dt;
    if (m_coolDownTime <= 0)
    {
        if (m_prepareToShoot || getAutoGun())
        {
            didShoot();
            m_coolDownTime = m_frequency;
            m_prepareToShoot = false;
        }
    }
}



void CBallisticGun::shoot()
{
    do
    {
        if (m_pRole->getAttackTarget())
        {
            m_prepareToShoot = true;
        }
        
    } while (false);
}



void CBallisticGun::didShoot()
{
    if (NULL == m_pRole)
    {
        __CCLOGWITHFUNCTION("make sure to call setOwner first!");
        return;
    }
    
    CRole* shootTarget = m_pRole->getAttackTarget();
    if (!shootTarget)
    {
        return;
    }
    
    CCPoint shootPoint = m_pRole->getShootPoint();
   
    CBallisticBullet* pBullet = dynamic_cast<CBallisticBullet*>(getContainer().checkoutElement());
    if (pBullet)
    {
        pBullet->revive();
        pBullet->setSpritePosition(ccpAdd(shootPoint, CCPointZero));
        pBullet->attachSpriteTo();
        
        pBullet->setShootTarget(shootTarget);
        pBullet->launch();
        
//        m_pRole->changeState(ROLE_STATE_ATTACK);
    }
}



