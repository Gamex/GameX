//
//  CMeleeAttackComp.h
//  GameX
//
//  Created by 马 俊 on 13-6-15.
//
//

#ifndef __GameX__CMeleeAttackComp__
#define __GameX__CMeleeAttackComp__

#include "CComponent.h"

class CRole;

class CMeleeAttackComp : public CComponent
{
public:
    COMPONENT_CREATE_FUNC(CMeleeAttackComp);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual CRole* getOwner();
protected:
    CMeleeAttackComp();
    virtual ~CMeleeAttackComp();
private:
    float attackTime_;
};

#endif /* defined(__GameX__CMeleeAttackComp__) */
