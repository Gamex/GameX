//
//  CBallisticMoveComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-27.
//
//

#include "CBallisticMoveComp.h"

#define BALLISTIC_DROP_THRESHOLD    30.f
#define START_ANGLE                 45.f
#define END_ANGLE                   135.f

CBallisticMoveComp::CBallisticMoveComp()
: m_speedX(0.f)
, m_speedY(0.f)
, m_AngleSpeed(0.f)
, m_elapse(0.f)
, m_inflectionTime(0.f)
, m_hitCallBack(NULL)
{
    
}



CBallisticMoveComp::~CBallisticMoveComp()
{
    setHitCallBack(NULL);
}



void CBallisticMoveComp::update(float dt)
{
    CVisibleObject* owner = getOwner();
    CC_ASSERT(owner);

    
    if (m_elapse < m_duration)
    {
        m_elapse += dt;

        float angle = owner->getSpriteRatatioin();
        
        angle += dt * m_AngleSpeed;
        
        CCPoint newPos = owner->getSpritePosition();//m_startPosition;
        newPos.x += dt * m_speedX;
        if (m_elapse < m_inflectionTime)
        {
            newPos.y += dt * m_speedY;
        }
        else
        {
            newPos.y -= dt * m_speedY;
        }
        
        owner->setSpriteRotation(angle);
        owner->setSpritePosition(newPos);

    }
    else
    {
        if (m_hitCallBack)
        {
            m_hitCallBack->execute();
        }
    }
}



void CBallisticMoveComp::setParameter(CComponentParameter* parameter)
{
    CCObject* object;
    if(parameter->getObjectParameter(PARAM_BALLISTIC_MOVE_TARGET, &object))
    {
        CCPoint* pt = dynamic_cast<CCPoint*>(object);
        if (pt)
        {
            m_moveTarget = *pt;
        }
    }
    
    parameter->getFloatParameter(PARAM_BALLISTIC_MOVE_DURATION, m_duration);
    if (parameter->getObjectParameter(PARAM_BALLISTIC_MOVE_HIT_CALLBACK, &object))
    {
        setHitCallBack(dynamic_cast<CCCallFunc*>(object));
    }
    
    onEnterComponent();
}



CVisibleObject* CBallisticMoveComp::getOwner()
{
    return dynamic_cast<CVisibleObject*>(CComponent::getOwner());
}




void CBallisticMoveComp::onEnterComponent()
{
    CVisibleObject* target = getOwner();
    CC_ASSERT(target);
    m_startPosition = target->getSpritePositionInWorldSpace();

    m_elapse = 0.f;
    
    float distanceX = m_moveTarget.x - m_startPosition.x;
    
    float ballisticTop = MAX(m_startPosition.y, m_moveTarget.y) + BALLISTIC_DROP_THRESHOLD;
    float inflectionDistance = fabsf(m_startPosition.y - ballisticTop);
    float distanceY = inflectionDistance + fabsf(m_moveTarget.y - ballisticTop);

    m_speedX = distanceX / m_duration;
    m_speedY = distanceY / m_duration;

    m_inflectionTime = inflectionDistance / m_speedY;
    
    m_AngleSpeed = (END_ANGLE - START_ANGLE) / m_duration;
    
    target->setSpriteRotation(START_ANGLE);
    
}




void CBallisticMoveComp::onLeaveComponent()
{
}
