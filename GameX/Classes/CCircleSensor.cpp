//
//  CCircleSensor.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#include "CCircleSensor.h"
#include "CVisibleObject.h"


CCircleSensor::CCircleSensor()
: m_radiusSquare(0.f)
, m_radius(0.f)
{
    
}



CCircleSensor::~CCircleSensor()
{
    
}




bool CCircleSensor::isCollsionWith(TFCollisionProtocol* object)
{
    CVisibleObject* pObj = dynamic_cast<CVisibleObject*>(object);
    if (nullptr == pObj)
    {
        return false;
    }
    
    Point b1 = getOwner()->getSpritePositionInWorldSpace();
    Point b2 = pObj->getSpritePositionInWorldSpace();
    
    float diffX = b2.x - b1.x;
    if (fabs(diffX) > m_radius) return false;
    
    float diffY = b2.y -  b1.y;
    if (fabs(diffY) > m_radius) return false;
    
    diffX *= diffX;
    diffY *= diffY;

    bool ret = ((diffX + diffY) <= m_radiusSquare);

    return ret;

}
