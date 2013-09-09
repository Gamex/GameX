//
//  CMoveTowardComp.h
//  GameX
//
//  Created by 马 俊 on 13-6-7.
//
//

#ifndef __GameX__CMoveTowardComp__
#define __GameX__CMoveTowardComp__

#include "CComponent.h"
#include "CBulletBase.h"


#define PARAM_MOVE_TOWARD_TARGET        "ParamMoveTowardTarget"
#define PARAM_MOVE_SPEED                "ParamMoveTowardSpeed"
#define PARAM_MOVE_ROTATE               "ParamMoveRotate"
#define PARAM_MOVE_INFINITE             "ParamMoveInfinite"


class CMoveTowardComp : public CComponent
{
    CC_SYNTHESIZE(float, m_Speed, Speed);
public:
    COMPONENT_CREATE_FUNC(CMoveTowardComp);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual CVisibleObject* getOwner();
protected:
    CMoveTowardComp();
    virtual ~CMoveTowardComp();
private:
    CCPoint m_Direction;
    CCPoint m_targetPosition;
    float m_targetLength;
    bool m_needRotate;
    bool m_moveInfinite;        // if false, stop on target position
};

#endif /* defined(__GameX__CMoveTowardComp__) */
