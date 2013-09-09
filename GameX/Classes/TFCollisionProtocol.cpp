//
//  TFCollisionProtocol.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFCollisionProtocol.h"
#include "TFCollisionMgr.h"
#include "CObjectBase.h"

void TFCollisionProtocol::turnOnCollision()
{
    if (COLLISION_MANAGER)
    {
        COLLISION_MANAGER->registerCollisionObj(dynamic_cast<TFCollisionProtocol*>(this), getCollisionGroup());
    }
}



void TFCollisionProtocol::turnOffCollision()
{
    if (COLLISION_MANAGER)
    {
        COLLISION_MANAGER->unregisterCollisionObj(dynamic_cast<TFCollisionProtocol*>(this), getCollisionGroup());
    }
}



int TFCollisionProtocol::getCollisionGroup()
{
    return 0;
}



bool TFCollisionProtocol::isCollsionWith(TFCollisionProtocol* rb)
{
    return false;
}



bool TFCollisionProtocol::isNeedCheckCollision()
{
    return false;
}



void TFCollisionProtocol::checkCollision(TFCollisionProtocol* rb)
{
    GBCollisionType type = rb->getCollisionType();
    MICH_IT it = m_handlers.find(type);
    if (it != m_handlers.end())
    {
        CObjectBase* _this = dynamic_cast<CObjectBase*>(this);
        COLLISION_HANDLER handler = (*it).second;
        (_this->*handler)(rb);
    }
}



GBCollisionType TFCollisionProtocol::getCollisionType()
{
    return CT_INVALID;
}



void TFCollisionProtocol::addCollisionHandler(GBCollisionType type, COLLISION_HANDLER handler)
{
    m_handlers[type] = handler;
}

