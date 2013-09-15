//
//  CBulletBase.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#include "CBulletBase.h"
#include "CRole.h"

#include "TFPListReaderHelper.h"
#include "Common.h"


CBulletBase::CBulletBase()
{
    
}



CBulletBase::~CBulletBase()
{
    
}




GBCollisionType CBulletBase::getCollisionType()
{
    return CT_BULLET;
}




void CBulletBase::update(float dt)
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

