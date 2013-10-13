//
//  TFCollisionMgr.h
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFCollisionMgr__
#define __TheForce__TFCollisionMgr__

#include "Common.h"
#include "CSingleton.h"


class TFCollisionProtocol;

enum CollisionGroup
{
    COLLISION_GROUP_INVALID = 0,
    COLLISION_GROUP_HERO = 1,
    COLLISION_GROUP_OBSTACLE,
    COLLISION_GROUP_BUFF,
    COLLISION_GROUP_RAT,
};

class TFCollisionMgr : public CSingleton<TFCollisionMgr>
{
public:
    TFCollisionMgr();
    virtual ~TFCollisionMgr();
    
    virtual bool init();

    virtual bool registerCollisionObj(TFCollisionProtocol* pRB, int group);
    virtual void unregisterCollisionObj(TFCollisionProtocol* pRB, int group);

    virtual void update();
    virtual void clearAll();
    
protected:
    MILRB m_ToBeAdded;
    MILRB m_ToBeDeleted;
    MILRB m_CollisionObjs;
    
    VUI m_collisionMask;
    
    virtual void updateToBeAdded();
    virtual void updateToBeDeleted();
    void checkCollisionOf2Groups(LRB& group1, LRB& group2);
    
private:
};

#define COLLISION_MANAGER (TFCollisionMgr::getInstance())

#endif /* defined(__TheForce__TFCollisionMgr__) */
