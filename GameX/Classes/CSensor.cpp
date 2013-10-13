//
//  CSensor.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#include "CSensor.h"
#include "CVisibleObject.h"

CSensor::CSensor()
: m_pOwner(NULL)
, m_TriggerHandler(NULL)
, m_collisionGroup(0)
{
    
}



CSensor::~CSensor()
{
    
}



bool CSensor::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF(!CObjectBase::init(pObjectDict));
        return true;
    } while (false);
    
    return false;
}



void CSensor::collideWithObject(TFCollisionProtocol* obj)
{
    if (m_pOwner && m_TriggerHandler)
    {
        (m_pOwner->*m_TriggerHandler)(dynamic_cast<CCObject*>(obj));
    }
}



GBCollisionType CSensor::getCollisionType()
{
    return CT_SENSOR;
}



void CSensor::setSensorTargetType(GBCollisionType type)
{
    addCollisionHandler(type, collision_handler_selector(CSensor::collideWithObject));
}



void CSensor::setOwnerAndTrigger(CVisibleObject* owner, SEL_CallFuncO trigger)
{
    m_pOwner = owner;
    m_TriggerHandler = trigger;
    
    if (m_pOwner)
    {
        m_collisionGroup = m_pOwner->getCollisionGroup();
    }
    turnOnCollision();
}



int CSensor::getCollisionGroup()
{
    return m_collisionGroup;
}


