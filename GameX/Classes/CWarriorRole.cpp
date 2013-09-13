//
//  CWarriorRole.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-17.
//
//

#include "CWarriorRole.h"

DEFINE_DICTFUNC(CWarriorRole, float, MaxHP, 0);
DEFINE_DICTFUNC(CWarriorRole, float, AttackRange, 0);


CWarriorRole::CWarriorRole()
: m_pHPBar(NULL)
, m_speed(180)
, m_attackRange(0)
{
    
}



CWarriorRole::~CWarriorRole()
{
    
}


void CWarriorRole::die()
{
    CRole::die();
    
    if (m_pHPBar != NULL)
    {
        m_pHPBar->setSpriteVisible(false);
    }
}



bool CWarriorRole::createHPBar()
{
    do
    {
//        setHPBar(dynamic_cast<TFHPBar*>(CObjectBase::createObject(getHPBarName())));
//        BREAK_IF(NULL == getHPBar());
//        
//        float w = m_pHPBar->getSpriteContentSize().width;
//        m_pHPBar->setSpritePosition(ccp(w / 2.f + 2.f, 0));
//        addChild(m_pHPBar);
//        m_pHPBar->attachSpriteTo(getInnerSprite());
        return true;
    } while (false);
    
    return false;
}


