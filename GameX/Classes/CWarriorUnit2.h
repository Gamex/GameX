//
//  CWarriorUnit2.h
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#ifndef __GameX__CWarriorUnit2__
#define __GameX__CWarriorUnit2__

#include "CWarriorRole.h"

class CWarriorUnit2
: public CWarriorRole
{
public:
    FACTORY_CREATE_FUNC(CWarriorUnit2);
    virtual ~CWarriorUnit2();
    

    virtual bool playAnimation(const std::string& name);
    virtual void think();
protected:
    CWarriorUnit2();
    
private:
};

#endif /* defined(__GameX__CWarriorUnit2__) */
