//
//  CDirectionBullet.cpp
//  GameX
//
//  Created by 马 俊 on 13-7-1.
//
//

#include "CDirectionBullet.h"
#include "CRole.h"

#include "TFPListReaderHelper.h"
#include "Common.h"

DEFINE_DICTFUNC(CDirectionBullet, float, Damage, 0.f);
DEFINE_DICTFUNC(CDirectionBullet, float, Speed, 0.f);

CDirectionBullet::CDirectionBullet()
: m_speed(0.f)
{
    
}



CDirectionBullet::~CDirectionBullet()
{
    
}



bool CDirectionBullet::init(CCDictionary* pObjectDict)
{
    if (!CBulletBase::init(pObjectDict))
    {
        return false;
    }
    
    m_speed = getSpeedFromDict();
    if (FLT_EQUAL(m_speed, 0.f))
    {
        __CCLOGWITHFUNCTION("Bullet's speed is not set or set to 0.bulletname: %s", getNameFromDict()->getCString());
        return false;
    }

    return true;
}




void CDirectionBullet::addCollisionHandlers()
{
    addCollisionHandler(CT_MONSTER, collision_handler_selector(CDirectionBullet::onCollideWithTarget));
}



void CDirectionBullet::onCollideWithTarget(TFCollisionProtocol* obj)
{
    die();
}



void CDirectionBullet::update(float dt)
{
    CSpriteObject::update(dt);
    
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    CCRect rect = CCRectMake(0, 0, winSz.width, winSz.height);
    CCRect bx = getSpriteBoundingBoxInWorldSpace();
    
    if (!rect.intersectsRect(bx))
    {
        die();
    }
}



float CDirectionBullet::getDamage()
{
    return getDamageFromDict();
}



void CDirectionBullet::launch()
{
}

