//
//  CMoveTowardComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-7.
//
//

#include "CMoveTowardComp.h"



CMoveTowardComp::CMoveTowardComp()
: m_Speed(0.f)
, m_needRotate(true)
, m_moveInfinite(true)
, m_Direction(0.f, 0.f)
{
}



CMoveTowardComp::~CMoveTowardComp()
{
    
}



void CMoveTowardComp::setParameter(CComponentParameter* parameter)
{
    CCPoint* pt;
    if (parameter->getObjectParameter(PARAM_MOVE_TOWARD_TARGET, reinterpret_cast<CCObject**>(&pt)))
    {
        CCPoint pos = getOwner()->getSpritePosition();
        m_Direction.setPoint(pt->x - pos.x, pt->y - pos.y);
        m_targetLength = m_Direction.getLength();
        if (m_targetLength > 0)
        {
            m_Direction = m_Direction.normalize();
        }
        m_targetPosition = *pt;
    }
    
    parameter->getBoolParameter(PARAM_MOVE_ROTATE, m_needRotate);
    parameter->getBoolParameter(PARAM_MOVE_INFINITE, m_moveInfinite);
    parameter->getFloatParameter(PARAM_MOVE_SPEED, m_Speed);

}



void CMoveTowardComp::update(float dt)
{
    do
    {
        if (!m_moveInfinite)
        {
            if (FLT_LE(m_targetLength, 0))
            {
                break;
            }
        }
        
        if (m_Direction.x == 0 && m_Direction.y == 0)
        {
            break;
        }
        
        BREAK_IF(getOwner() == NULL);
        CVisibleObject* target = getOwner();
        
        CCPoint pt = target->getSpritePosition();
        
        float len = dt * getSpeed();
        m_targetLength -= len;
        
        CCPoint distance = m_Direction * len;
        
        pt.x += distance.x;
        pt.y += distance.y;
        
        target->setSpritePosition(pt);

        CCPoint vBase(0.f, 1.f);
        
        float dot = m_Direction.dot(vBase);
        float rad = acosf(dot);
        if (m_Direction.x < 0)
        {
            rad = -rad;
        }

        float degree = kmRadiansToDegrees(rad);
        
        if (m_needRotate)
        {
            target->setSpriteRotation(degree);
        }
        else
        {
            if (!FLT_EQUAL(degree, 0) && !FLT_EQUAL(degree, 180.f))
            {
                target->setSpriteFlipX(!(degree > 0 && degree < 180.f));
            }
        }


    } while (false);
}


CVisibleObject* CMoveTowardComp::getOwner()
{
    return dynamic_cast<CVisibleObject*>(CComponent::getOwner());
}


