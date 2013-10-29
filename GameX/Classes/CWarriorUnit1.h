//
//  CWarriorUnit1.h
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#ifndef __GameX__CWarriorUnit1__
#define __GameX__CWarriorUnit1__

#include "CWarriorRole.h"

class CWarriorUnit1
: public CWarriorRole
{
public:
    FACTORY_CREATE_FUNC(CWarriorUnit1);
    virtual ~CWarriorUnit1();

    virtual bool init(const string& unitId, bool editorMode = false);
    virtual void think();
protected:
    CWarriorUnit1();

private:
};

#endif /* defined(__GameX__CWarriorUnit1__) */
