//
//  CBallisticBullet.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-23.
//
//

#include "CBallisticBullet.h"


DEFINE_DICTFUNC(CBallisticBullet, float, Damage, 0.f);
DEFINE_DICTFUNC(CBallisticBullet, float, Speed, 0.f);


CBallisticBullet::CBallisticBullet()
{
    
}



CBallisticBullet::~CBallisticBullet()
{
    
}



bool CBallisticBullet::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF_FAILED(CBulletBase::init(pObjectDict));

        return true;
    } while (false);
    
    return false;
}



void CBallisticBullet::update(float dt)
{
    CSpriteObject::update(dt);
    
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    CCRect rect = CCRectMake(0, 0, winSz.width, winSz.height);
    CCRect bx = getSpriteBoundingBoxInWorldSpace();

}



float CBallisticBullet::getDamage()
{
    return 0.f;
}



GBCollisionType CBallisticBullet::getCollisionType()
{
    return CT_BULLET;
}



void CBallisticBullet::addCollisionHandlers()
{
    addCollisionHandler(CT_MONSTER, collision_handler_selector(CBallisticBullet::onCollideWithTarget));
}



void CBallisticBullet::onCollideWithTarget(TFCollisionProtocol* obj)
{
    CRole* monster = getShootTarget();
    if (monster && monster == dynamic_cast<CRole*>(obj) && !monster->isDead())
    {
        monster->die();
        die();
    }

}



void CBallisticBullet::launch()
{
}



void CBallisticBullet::onHitTarget()
{
    die();
}


