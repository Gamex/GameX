//
//  CMonster.h
//  TheForce
//
//  Created by 马 俊 on 13-2-4.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFMonster__
#define __TheForce__TFMonster__

#include "CWarriorRole.h"
#include "TFCollisionProtocol.h"

class CPath;

class CMonster : public CWarriorRole
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CMonster);
    
    virtual ~CMonster();
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void update(float dt);
    virtual void die();
    virtual void revive();
    virtual void clearAll();
    
    virtual void goStraightToTarget(CCPoint target);
    virtual void goWithRandomPath(CCPoint target);
    virtual void attack(CWarriorRole* pAt);
#ifdef DEBUG
    virtual string whoAmI(){return "Monster";}
#endif

protected:
    CMonster();
    void clearThis();

    virtual void addComponentsForStates();
    virtual void castItems();
    virtual const char* getHPBarName();
    
    virtual GBCollisionType getCollisionType();
    virtual void addCollisionHandlers();

private:
    string m_tempPathName;
};

#endif /* defined(__TheForce__TFMonster__) */
