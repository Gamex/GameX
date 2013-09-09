//
//  CPathMoveComp.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-5.
//
//

#ifndef __EliminationPlane__CPathMoveComp__
#define __EliminationPlane__CPathMoveComp__

#include "CComponent.h"
#include "CVisibleObject.h"

class CPath;

#define PARAM_PATH_NAME     "ParamPathName"

class CPathMoveComp : public CComponent
{
public:
    COMPONENT_CREATE_FUNC(CPathMoveComp);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual CVisibleObject* getOwner();
protected:
    CPathMoveComp();
    virtual ~CPathMoveComp();
private:
    CPath* path_;
    int splineIdx_;
    float elapse_;
};

#endif /* defined(__EliminationPlane__CPathMoveComp__) */
