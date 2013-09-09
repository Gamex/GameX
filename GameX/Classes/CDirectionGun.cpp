//
//  CDirectionGun.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CDirectionGun.h"
#include "CDirectionBullet.h"
#include "CRole.h"
#include "CComponentParameter.h"
#include "CMoveTowardComp.h"

DEFINE_DICTFUNC(CDirectionGun, float, Frequency, 0);

CDirectionGun::CDirectionGun()
: m_coolDownTime(0)
,m_frequency(0.f)
,m_isAutoGun(false)
,m_prepareToShoot(false)
{
}



CDirectionGun::~CDirectionGun()
{
    clearThis();
}



bool CDirectionGun::init(CCDictionary* pObjectDict)
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



void CDirectionGun::update(float dt)
{
    CGunBase::update(dt);
    
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



void CDirectionGun::didShoot()
{

    if (NULL == m_pRole)
    {
        __CCLOGWITHFUNCTION("make sure to call setOwner first!");
        return;
    }

    CCPoint shootPoint = m_pRole->getShootPoint();
    CCPoint direction = m_pRole->getShootDirection();

    CDirectionBullet* pBullet = dynamic_cast<CDirectionBullet*>(getContainer().checkoutElement());
    if (pBullet)
    {
        pBullet->revive();
        pBullet->setSpritePosition(ccpAdd(shootPoint, CCPointZero));
        pBullet->attachSpriteTo();
        pBullet->setShootDirection(direction);
        pBullet->launch();
    }
}



void CDirectionGun::shoot()
{
    m_prepareToShoot = true;
}



void CDirectionGun::clearAll()
{
    CObjectBase::clearAll();
    clearThis();
}



void CDirectionGun::clearThis()
{
    
}


