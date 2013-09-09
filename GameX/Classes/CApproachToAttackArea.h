//
//  CApproachToAttackArea.h
//  GameX
//
//  Created by 马 俊 on 13-6-16.
//
//

#ifndef __GameX__CApproachToAttackArea__
#define __GameX__CApproachToAttackArea__

#include "CComponent.h"

class CRole;

class CApproachToAttackArea : public CComponent
{
public:
    COMPONENT_CREATE_FUNC(CApproachToAttackArea);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual CRole* getOwner();
protected:
    CApproachToAttackArea();
    virtual ~CApproachToAttackArea();
private:
};

#endif /* defined(__GameX__CApproachToAttackArea__) */
