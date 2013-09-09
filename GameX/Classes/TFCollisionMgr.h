//
//  TFCollisionMgr.h
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFCollisionMgr__
#define __TheForce__TFCollisionMgr__

#include "cocos2d.h"
#include "CSingleton.h"

#include <map>
#include <set>

USING_NS_CC;
using namespace std;


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
    typedef set<TFCollisionProtocol*> LRB;
    typedef set<TFCollisionProtocol*>::iterator LRB_IT;
    typedef set<TFCollisionProtocol*>::const_iterator LRB_CIT;
    
    typedef vector<LRB> MILRB;
    typedef vector<LRB>::iterator MILRB_IT;
    typedef vector<LRB>::const_iterator MILRB_CIT;

    typedef vector<unsigned int> VUI;
    typedef vector<unsigned int>::iterator VUI_IT;
    typedef vector<unsigned int>::const_iterator VUI_CIT;

    
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
