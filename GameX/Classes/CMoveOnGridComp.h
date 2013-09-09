//
//  CMoveOnGridComp.h
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#ifndef __GameX__CMoveOnGridComp__
#define __GameX__CMoveOnGridComp__

#include "CComponent.h"

class CRole;

class IMoveOnGridCompCallBack
{
public:
    virtual void onMoveEvent() = 0;
};

class CMoveOnGridComp : public CComponent
{
public:
    COMPONENT_CREATE_FUNC(CMoveOnGridComp);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual CRole* getOwner();
protected:
    CMoveOnGridComp();
    virtual ~CMoveOnGridComp();
private:

};

#endif /* defined(__GameX__CMoveOnGridComp__) */
