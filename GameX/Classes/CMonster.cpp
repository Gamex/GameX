//
//  CMonster.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-4.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CMonster.h"
#include "CBulletBase.h"
#include "TFHPBar.h"
#include "CBattleFieldLayer.h"
#include "CPathMoveComp.h"
#include "CPathManager.h"
#include "CMoveTowardComp.h"
#include "CMeleeAttackComp.h"
#include "CApproachToAttackArea.h"



CMonster::CMonster()
{
    
}



CMonster::~CMonster()
{
    clearThis();
}



void CMonster::clearAll()
{
    CWarriorRole::clearAll();
    clearThis();
}



void CMonster::clearThis()
{
    if (getHPBar())
    {
        getHPBar()->clearAll();
        setHPBar(NULL);
    }
}


bool CMonster::init(CCDictionary* pObjectDict)
{
    if (!CWarriorRole::init(pObjectDict))
    {
        return false;
    }
    
    m_maxHitPoint = getMaxHPFromDict();
    m_hitPoint = m_maxHitPoint;

//    if (!createHPBar())
//    {
//        return false;
//    }
//    
//    m_pHPBar->setPercentage(1.f);
//    m_pHPBar->setSpriteVisible(false);

    return true;
}



void CMonster::update(float dt)
{    
    CWarriorRole::update(dt);

//    if (!isDead())
//    {
//        CCSize winSz = CCDirector::sharedDirector()->getWinSize();
//        CCRect rect = CCRectMake(0, 0, winSz.width, winSz.height);
//        CCRect bx = getSpriteBoundingBoxInWorldSpace();
//        
//        if (!rect.intersectsRect(bx))
//        {
//            die();
//        }
//    }
    
    if (this->getCurrentState() == "Damage")
    {
        m_hitTime += dt;
        if (m_hitTime >= 0.1)
        {
            changeState("Fly");
            m_hitTime = 0;
        }
    }


    return;
}



void CMonster::die()
{
    CWarriorRole::die();
    
    PATH_MANAGER->removePath(m_tempPathName);
}



void CMonster::revive()
{
    CWarriorRole::revive();
    m_hitPoint = m_maxHitPoint;
}



void CMonster::castItems()
{

}



const char* CMonster::getHPBarName()
{
    return "MonsterHPBar";
}



void CMonster::goWithRandomPath(CCPoint target)
{
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    
    int edge = rand() % 4;
    CCPoint position;
    switch (edge)
    {
        case 0:             // top
            position.x = CCRANDOM_0_1() * winSz.width;
            position.y = winSz.height + m_obContentSize.height / 2.f;
            break;
        case 1:             // right
            position.x = winSz.width + m_obContentSize.width / 2.f;
            position.y = CCRANDOM_0_1() * winSz.height;
            break;
        case 2:             // buttom
            position.x = CCRANDOM_0_1() * winSz.width;
            position.y = -m_obContentSize.height / 2.f;
            break;
        case 3:             // left
            position.x = -m_obContentSize.width / 2.f;
            position.y = CCRANDOM_0_1() * winSz.height;
            break;
        default:
            break;
    }
    
    m_tempPathName = PATH_MANAGER->makeRandomPath(position, target);
    CComponentParameter* cp = CComponentParameter::create();
    cp->addStringParameter(PARAM_PATH_NAME, m_tempPathName);
    
    changeState("Ready", cp, true);
}



void CMonster::goStraightToTarget(CCPoint target)
{
    CCPoint* t = new CCPoint(target);
    t->autorelease();
    
    CComponentParameter* cp = CComponentParameter::create();
    cp->addObjectParameter(PARAM_MOVE_TOWARD_TARGET, t);
    cp->addFloatParameter(PARAM_MOVE_SPEED, 40.f);
    cp->addBoolParameter(PARAM_MOVE_ROTATE, false);
    
    changeState(ROLE_STATE_MOVE, cp, true);
}



GBCollisionType CMonster::getCollisionType()
{
    return CT_MONSTER;
}



void CMonster::addCollisionHandlers()
{
}



void CMonster::attack(CWarriorRole* pAt)
{
    CWarriorRole::attack(pAt);
}



void CMonster::addComponentsForStates()
{
    CMoveTowardComp* moveComp = CMoveTowardComp::create(this);
    CMeleeAttackComp* meleeAttack = CMeleeAttackComp::create(this);
    CApproachToAttackArea* approachComp = CApproachToAttackArea::create(this);
    
    this->addComponentForState(ROLE_STATE_MOVE, moveComp);
    this->addComponentForState(ROLE_STATE_MOVE, approachComp);
    this->addComponentForState(ROLE_STATE_ATTACK, meleeAttack);

}
