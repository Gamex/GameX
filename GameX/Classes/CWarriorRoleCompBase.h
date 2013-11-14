//
//  CWarriorRoleCompBase.h
//  GameX
//
//  Created by 马 俊 on 13-10-10.
//
//

#ifndef __GameX__CWarriorRoleCompBase__
#define __GameX__CWarriorRoleCompBase__

#include "Common.h"
#include "CWarriorRole.h"
#include "ICCBAnimationDelegate.h"


#define THINK_AND_BREAK()\
m_ownerRole->think();\
if (this->isEnabled() == false)\
{ break;}

class CWarriorRoleCompBase
: public Component
, public ICCBAnimationDelegate
{
public:
    virtual ~CWarriorRoleCompBase();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
protected:
    CWarriorRoleCompBase(int subState);

    CWarriorRole* m_ownerRole;
    int m_subState;
private:
    
};

#endif /* defined(__GameX__CWarriorRoleCompBase__) */
