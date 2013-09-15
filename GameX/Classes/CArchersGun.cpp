//
//  CArchersGun.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-6.
//
//

#include "CArchersGun.h"
#include "CGameTime.h"
#include "CSensor.h"


CArchersGun::CArchersGun()
: m_Direction(0.f, 1.f)
{
}



CArchersGun::~CArchersGun()
{
    
}



bool CArchersGun::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF_FAILED(CRole::init(pObjectDict));
        return true;
    } while (false);
    
    return false;
}



void CArchersGun::setSensorType(CSensor* pSensor)
{
    pSensor->setSensorTargetType(CT_MONSTER);
}



void CArchersGun::update(float dt)
{
    CRole::update(dt);
}



void CArchersGun::clearAll()
{
    CRole::clearAll();
    
    clearThis();
}



void CArchersGun::clearThis()
{
    
}



void CArchersGun::attack(CRole* pAt)
{
    CRole::attack(pAt);
    
    if (getAttackTarget())
    {
        if (getGun())
        {
            getGun()->shoot();
        }
    }
}


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
float  myACosf(float f)     // android 编译器这里会有bug，编译会失败，所以要这样写一下
{
    return acosf(f);
}
#else
#define myACosf(__f__) acosf(__f__)
#endif

void CArchersGun::setAimPoint(const CCPoint& point)
{
    do
    {
        CCSprite* pSpr = dynamic_cast<CCSprite*>(getInnerSprite());
        BREAK_IF(!pSpr);
        
        CCPoint originPos = getSpritePosition();
        CCPoint v(point.x - originPos.x, point.y - originPos.y);
        m_Direction = v.normalize();
        
        CCPoint vBase(0.f, 1.f);
        float dot = v.dot(vBase);
        float rad = myACosf(dot);
        if (point.x < originPos.x)
        {
            rad = -rad;
        }
        
//        pSpr->setRotation(kmRadiansToDegrees(rad));
    
    } while (false);
}



CCPoint CArchersGun::getShootDirection()
{
    return m_Direction;
}



void CArchersGun::onSensor(CCObject* obj)
{
    CRole* vo = dynamic_cast<CRole*>(obj);
    if (NULL != vo)
    {
        CCPoint pt = vo->getSpritePositionInWorldSpace();
        setAimPoint(pt);
        attack(vo);
    }
}



void CArchersGun::completedAnimationSequenceNamed(const char *name)
{
//    if (strcmp(name, ROLE_STATE_ATTACK) == 0)
//    {
//        changeState(ROLE_STATE_IDLE);
//    }
}
