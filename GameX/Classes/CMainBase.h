//
//  CMainBase.h
//  GameX
//
//  Created by 马 俊 on 13-12-11.
//
//

#ifndef __GameX__CMainBase__
#define __GameX__CMainBase__

#include "CBuildingRole.h"

class CMainBase
: public CBuildingRole
{
public:
    FACTORY_CREATE_FUNC(CBuildingRole);
    virtual ~CMainBase(){}
    
protected:
    CMainBase(){}
};

#endif /* defined(__GameX__CMainBase__) */
