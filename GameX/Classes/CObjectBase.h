//
//  CObjectBase.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFObject__
#define __TheForce__TFObject__


#include "Common.h"

#include "CObjectFactory.h"
#include "CState.h"
#include "TFCollisionProtocol.h"
#include "TFPListReaderHelper.h"

class TFRoleData;

class CObjectBase : public CCNode, public CState, public TFCollisionProtocol
{
public:
	virtual ~CObjectBase();
	
    //
	virtual bool init();
	virtual void update(float dt);

    virtual void onEnterState(int state);
	virtual void onLeaveState(int state);
    
    virtual void die();
    virtual void revive();
    virtual bool isDead() const;
    virtual bool checkDead();   // if return ture, then die() will be called in CObjectBase::update()
    
    virtual void clearAll();
    
    virtual bool isNeedCheckCollision();
    
    ////////////////////
    virtual void addComponentForState(int state, CCComponent* comp);

#ifdef DEBUG
    virtual std::string whoAmI(){return "CObjectBase";}
#endif
protected:
    CObjectBase();
    void clearThis();
    virtual void addCollisionHandlers();
    virtual void addComponentsForStates();
    
    bool m_isDead;
private:
    VSS m_stateComponentTable;
};

#endif /* defined(__TheForce__TFObject__) */
