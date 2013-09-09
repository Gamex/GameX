//
//  CSoldier.h
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#ifndef __GameX__CSoldier__
#define __GameX__CSoldier__

#include "CWarriorRole.h"
#include "TFCollisionProtocol.h"


class CSoldier : public CWarriorRole
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
    CC_SYNTHESIZE(int, m_type, Type);
public:
    FACTORY_CREATE_FUNC(CSoldier);
    
    virtual ~CSoldier();
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void update(float dt);
    virtual void die();
    virtual void revive();
    virtual void clearAll();
    
    virtual void goStraightToTarget(CCPoint target);
    virtual void attack(CWarriorRole* pAt);
    
#ifdef DEBUG
    virtual string whoAmI(){return "Soldier";}
#endif

protected:
    CSoldier();
    void clearThis();
    
    virtual void castItems();
    virtual const char* getHPBarName();
    
    virtual void collideWithBullet(TFCollisionProtocol* obj);
    virtual void addComponentsForStates();
    
    virtual GBCollisionType getCollisionType();
    virtual void addCollisionHandlers();
    
    virtual void onSensor(CCObject* obj);
    virtual void setSensorType(CSensor* pSensor);
    virtual void findNearestMonsterToAttack();

private:
    CCArray m_monsterNearby;
};

#endif /* defined(__GameX__CSoldier__) */
