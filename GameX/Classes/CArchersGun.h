//
//  CArchersGun.h
//  GameX
//
//  Created by 马 俊 on 13-6-6.
//
//

#ifndef __GameX__CBaseGun__
#define __GameX__CBaseGun__

#include "CRole.h"


class CArchersGun : public CRole
{
public:
    FACTORY_CREATE_FUNC(CArchersGun);
    
    virtual ~CArchersGun();
    
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void update(float dt);
    virtual void clearAll();
    
    virtual void setAimPoint(const CCPoint& point);

    virtual void attack(CRole* pAt);

    virtual CCPoint getShootDirection();
#ifdef DEBUG
    virtual std::string whoAmI(){return "CArchersGun";}
#endif
    
protected:
    CArchersGun();
    
    void clearThis();
    virtual void onSensor(CCObject* obj);
    virtual void onSetSensorType(CSensor* pSensor);
    
    virtual void completedAnimationSequenceNamed(const char *name);
private:
    CCPoint m_Direction;

};

#endif /* defined(__GameX__CBaseGun__) */
