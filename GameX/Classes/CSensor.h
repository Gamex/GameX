//
//  CSensor.h
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#ifndef __GameX__CSensor__
#define __GameX__CSensor__

#include "CObjectBase.h"

class CVisibleObject;

class CSensor : public CObjectBase
{
public:
    virtual ~CSensor();

    virtual void setOwnerAndTrigger(CVisibleObject* owner, SEL_CallFuncO trigger);
    virtual void setSensorTargetType(GBCollisionType type);
    virtual CVisibleObject* getOwner(){return m_pOwner;}
protected:
    CSensor();
    virtual void collideWithObject(TFCollisionProtocol* obj);
    virtual GBCollisionType getCollisionType();
    virtual int getCollisionGroup();
private:
    CVisibleObject* m_pOwner;
    SEL_CallFuncO m_TriggerHandler;
    int m_collisionGroup;
};

#endif /* defined(__GameX__CSensor__) */
