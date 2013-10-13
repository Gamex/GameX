//
//  CWarriorUnit0.h
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#ifndef __GameX__CWarriorUnit0__
#define __GameX__CWarriorUnit0__

#include "CWarriorRole.h"

//enum WARRIOR_UNIT0_STATE
//{
//    WARRIOR_UNIT0_STATE_ATTACK = WARRIOR_ROLE_STATE_MAX,
//    WARRIOR_UNIT0_STATE_MAX,
//};


class CWarriorUnit0
: public CWarriorRole
{
public:
    FACTORY_CREATE_FUNC(CWarriorUnit0);
    virtual ~CWarriorUnit0();

protected:
    CWarriorUnit0();

private:
};

#endif /* defined(__GameX__CWarriorUnit0__) */
