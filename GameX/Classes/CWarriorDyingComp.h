//
//  CWarriorDyingComp.h
//  GameX
//
//  Created by 马 俊 on 13-10-16.
//
//

#ifndef __GameX__CWarriorDyingComp__
#define __GameX__CWarriorDyingComp__

#include "CWarriorRoleCompBase.h"


enum
{
    DYING_SUB_STATE_START,
    DYING_SUB_STATE_DYING,
    DYING_SUB_STATE_OVER,
};


class CWarriorDyingComp
: public CWarriorRoleCompBase
{
    CC_SYNTHESIZE(int, m_stateId, StateId);
public:
    CREATE_FUNC(CWarriorDyingComp);

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);

    virtual void onDyingOver(Node* obj);
protected:
    CWarriorDyingComp(void);
private:
};

#endif /* defined(__GameX__CWarriorDyingComp__) */
