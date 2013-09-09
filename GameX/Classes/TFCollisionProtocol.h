//
//  TFCollisionProtocol.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFCollisionProtocol__
#define __TheForce__TFCollisionProtocol__
#include <map>

using namespace std;

class CObjectBase;
class TFCollisionProtocol;

typedef void (CObjectBase::*COLLISION_HANDLER)(TFCollisionProtocol*);
#define collision_handler_selector(_SELECTOR) (COLLISION_HANDLER)(&_SELECTOR)

enum GBCollisionType {
    CT_INVALID = -1,
    CT_HERO = 0,
    CT_MONSTER,
    CT_COIN,
    CT_BULLET,
    CT_SENSOR,
    CT_SOLDIER,
};

class TFCollisionProtocol
{
public:
    virtual void checkCollision(TFCollisionProtocol* rb);
    
    virtual bool isCollsionWith(TFCollisionProtocol* rb);
    virtual bool isNeedCheckCollision();
    virtual int getCollisionGroup();
    virtual void turnOffCollision();
    virtual void turnOnCollision();
protected:
    typedef map<GBCollisionType, COLLISION_HANDLER> MICH;
    typedef map<GBCollisionType, COLLISION_HANDLER>::iterator MICH_IT;
    typedef map<GBCollisionType, COLLISION_HANDLER>::const_iterator MICH_CIT;
    
    virtual void addCollisionHandler(GBCollisionType type, COLLISION_HANDLER handler);
    
    virtual GBCollisionType getCollisionType();
    
    
    MICH m_handlers;
private:
};

#endif /* defined(__TheForce__TFCollisionProtocol__) */
