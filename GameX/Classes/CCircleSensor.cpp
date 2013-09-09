//
//  CCircleSensor.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#include "CCircleSensor.h"
#include "CVisibleObject.h"


DEFINE_DICTFUNC(CCircleSensor, float, Radius, 0);



CCircleSensor::CCircleSensor()
: m_radiusSquare(0.f)
, m_radius(0.f)
{
    
}



CCircleSensor::~CCircleSensor()
{
    
}



bool CCircleSensor::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF_FAILED(CSensor::init(pObjectDict));
        m_radius = getRadiusFromDict();
        m_radiusSquare = m_radius * m_radius;
        
        return true;
    } while (false);
    
    return false;
}




bool CCircleSensor::isCollsionWith(TFCollisionProtocol* object)
{
    CVisibleObject* pObj = dynamic_cast<CVisibleObject*>(object);
    if (NULL == pObj)
    {
        return false;
    }
    
    CCPoint b1 = getOwner()->getSpritePositionInWorldSpace();
    CCPoint b2 = pObj->getSpritePositionInWorldSpace();
    
    float diffX = b2.x - b1.x;
    if (fabs(diffX) > m_radius) return false;
    
    float diffY = b2.y -  b1.y;
    if (fabs(diffY) > m_radius) return false;
    
    diffX *= diffX;
    diffY *= diffY;

    bool ret = ((diffX + diffY) <= m_radiusSquare);

    return ret;

}
