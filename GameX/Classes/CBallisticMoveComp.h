//
//  CBallisticMoveComp.h
//  GameX
//
//  Created by 马 俊 on 13-6-27.
//
//

#ifndef __GameX__CBallisticMoveComp__
#define __GameX__CBallisticMoveComp__

#include "CComponent.h"
#include "CVisibleObject.h"

#define PARAM_BALLISTIC_MOVE_TARGET         "ParamBallisticMoveTarget"
#define PARAM_BALLISTIC_MOVE_DURATION       "ParamBallisticMoveDuration"
#define PARAM_BALLISTIC_MOVE_HIT_CALLBACK   "ParamBallisticMoveHitCallBack"

class CBallisticMoveComp : public CComponent
{
    CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_hitCallBack, HitCallBack);
public:
    COMPONENT_CREATE_FUNC(CBallisticMoveComp);
    
    virtual void update(float dt);
    virtual void setParameter(CComponentParameter* parameter);
    
    virtual void onEnterComponent();
    virtual void onLeaveComponent();
    
    virtual CVisibleObject* getOwner();
protected:
    CBallisticMoveComp();
    virtual ~CBallisticMoveComp();
private:
    CCPoint m_moveTarget;
    CCPoint m_startPosition;

    float m_elapse;
    float m_duration;
    float m_inflectionTime;
    float m_speedX;
    float m_speedY;
    float m_AngleSpeed;
};

#endif /* defined(__GameX__CBallisticMoveComp__) */
