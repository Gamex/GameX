//
//  CSoldier.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#include "CSoldier.h"
#include "CBulletBase.h"
#include "TFHPBar.h"
#include "CBattleFieldLayer.h"
#include "CPathMoveComp.h"
#include "CPathManager.h"
#include "CMoveTowardComp.h"
#include "UtilityFunction.h"
#include "CMeleeAttackComp.h"
#include "CApproachToAttackArea.h"


CSoldier::CSoldier()
{
    
}



CSoldier::~CSoldier()
{
    clearThis();
}



void CSoldier::clearAll()
{
    CWarriorRole::clearAll();
    clearThis();
}



void CSoldier::clearThis()
{
}


bool CSoldier::init(CCDictionary* pObjectDict)
{
    if (!CWarriorRole::init(pObjectDict))
    {
        return false;
    }
    
    m_maxHitPoint = getMaxHPFromDict();
    m_hitPoint = m_maxHitPoint;
    
    //    this->addComponentForState("Ready", CPathMoveComp::create(this));
    this->addComponentForState("Ready", CMoveTowardComp::create(this));
    
    //    if (!createHPBar())
    //    {
    //        return false;
    //    }
    //
    //    m_pHPBar->setPercentage(1.f);
    //    m_pHPBar->setSpriteVisible(false);
    
    return true;
}



void CSoldier::update(float dt)
{
    CWarriorRole::update(dt);
    
    findNearestMonsterToAttack();
    
    return;
}



void CSoldier::die()
{
    CWarriorRole::die();

}



void CSoldier::revive()
{
    CWarriorRole::revive();
    m_hitPoint = m_maxHitPoint;
}



void CSoldier::castItems()
{
}



void CSoldier::goStraightToTarget(CCPoint target)
{
    CCPoint* t = new CCPoint(target);
    t->autorelease();

    CComponentParameter* cp = CComponentParameter::create();
    cp->addObjectParameter(PARAM_MOVE_TOWARD_TARGET, t);
    cp->addFloatParameter(PARAM_MOVE_SPEED, 40.f);
    cp->addBoolParameter(PARAM_MOVE_ROTATE, false);
    cp->addBoolParameter(PARAM_MOVE_INFINITE, false);
    
    changeState(ROLE_STATE_MOVE, cp, true);
}



GBCollisionType CSoldier::getCollisionType()
{
    return CT_SOLDIER;
}



void CSoldier::addCollisionHandlers()
{
    addCollisionHandler(CT_BULLET, collision_handler_selector(CSoldier::collideWithBullet));
}



void CSoldier::collideWithBullet(TFCollisionProtocol* obj)
{
    die();
    return;
}


void CSoldier::onSensor(CCObject* obj)
{
    if(!getAttackTarget())
    {
        CWarriorRole* pMonster = dynamic_cast<CWarriorRole*>(obj);
        if (NULL != pMonster && !pMonster->getAttackTarget())
        {
            m_monsterNearby.addObject(obj);
        }
    }
}



void CSoldier::setSensorType(CSensor* pSensor)
{
    pSensor->setSensorTargetType(CT_MONSTER);
}



void CSoldier::findNearestMonsterToAttack()
{
    CCObject* obj;
    float distance = FLT_MAX;
    CWarriorRole* pNearestMonster = NULL;

    CCARRAY_FOREACH(&m_monsterNearby, obj)
    {
        CWarriorRole* pMonster = dynamic_cast<CWarriorRole*>(obj);
        if (NULL != pMonster && !pMonster->getAttackTarget())
        {
            float dist = utility::computeDistanceSquare(this, pMonster);
            if (dist < distance)
            {
                pNearestMonster = pMonster;
                distance = dist;
            }
        }
    }
    
    if (NULL != pNearestMonster)
    {
        attack(pNearestMonster);
        pNearestMonster->attack(this);
    }
    
    m_monsterNearby.removeAllObjects();
}



void CSoldier::attack(CWarriorRole* pAt)
{
    CWarriorRole::attack(pAt);
}



void CSoldier::addComponentsForStates()
{
    CMoveTowardComp* moveComp = CMoveTowardComp::create(this);
    CMeleeAttackComp* meleeAttack = CMeleeAttackComp::create(this);
    CApproachToAttackArea* approachComp = CApproachToAttackArea::create(this);
    
    this->addComponentForState(ROLE_STATE_MOVE, moveComp);
    this->addComponentForState(ROLE_STATE_MOVE, approachComp);
    this->addComponentForState(ROLE_STATE_ATTACK, meleeAttack);
}



const char* CSoldier::getHPBarName()
{
    return "";
}
