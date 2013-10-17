//
//  CSkillComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-10.
//
//

#include "CSkillComp.h"
#include "Common.h"
#include "CDataCenterManager.h"


CSkillComp* CSkillComp::createObject(const std::string& name)
{
    CSkillComp* pObject;
    
    pObject = (CSkillComp*)OBJECT_FACTORY->createInstance(name);
    
    if (pObject)
    {
        pObject->init();
    }
    return pObject;
}



CSkillComp::CSkillComp(void)
: CWarriorRoleCompBase(SKILL_SUB_STATE_READY)
, m_CDTotalTime(0.f)
, m_CDLeftTime(0.f)
, m_stateId(-1)
, m_skillTarget(NULL)
{
    m_strName = "SkillComp";
}



bool CSkillComp::init()
{
    do
    {
        BREAK_IF_FAILED(CWarriorRoleCompBase::init());
        
        return true;
    } while (false);
    
	return false;
}



bool CSkillComp::loadSkill(const string& skillName)
{
    do
    {
        CCDictionary* skillDict = DTSKILL->getData(skillName);
        CC_ASSERT(skillDict);
        
        CCString* str = DTSKILL->get_range_Value(skillDict);
        CC_ASSERT(str);
        m_attackRadiusSq = str->floatValue();

        str = DTSKILL->get_cd_Value(skillDict);
        CC_ASSERT(str);
        m_CDTotalTime = str->floatValue();
        m_CDLeftTime = m_CDTotalTime;
        
        m_strName = skillName;
        return true;
    } while (false);
	return false;
}




void CSkillComp::onEnter()
{
    CWarriorRoleCompBase::onEnter();
    do
    {
        CC_BREAK_IF(isEnabled() == false);

        action();
    } while (false);
}



void CSkillComp::onExit()
{
    CWarriorRoleCompBase::onExit();
    m_subState = SKILL_SUB_STATE_READY;
}



void CSkillComp::update(float dt)
{
    do
    {
        CWarriorRoleCompBase::update(dt);
        
        if (m_CDLeftTime > 0)
        {
            m_CDLeftTime -= dt;
            if (FLT_LE(m_CDLeftTime, 0.f))
            {
                m_CDLeftTime = 0.f;
            }
        }
        
        if (!isEnabled()) return;
        
        switch (m_subState)
        {
            case SKILL_SUB_STATE_READY:
                m_ownerRole->think();
                break;
            case SKILL_SUB_STATE_PRE_CAST:
                m_ownerRole->setFaceTo(m_skillTarget);
                m_ownerRole->playAnimation(ROLE_ANIMATION_ATTACK);
                m_subState = SKILL_SUB_STATE_CASTING;
                break;
            case SKILL_SUB_STATE_CASTING:
                break;
            case SKILL_SUB_STATE_POST_CAST:
                m_subState = SKILL_SUB_STATE_READY;
                break;
            default:
                break;
        }

    } while (false);
}




bool CSkillComp::checkTarget(CRole* target, float distance)
{
    do
    {
        BREAK_IF(m_subState != SKILL_SUB_STATE_READY);
        BREAK_IF(getCDLeftTime() > 0);      // CDing...

        BREAK_IF(distance > m_attackRadiusSq);
        m_skillTarget = target;
        return true;
    } while (false);
    
    return false;
}



void CSkillComp::action()
{
    m_subState = SKILL_SUB_STATE_PRE_CAST;
    m_CDLeftTime = m_CDTotalTime;
    
    m_ownerRole->setMoveTarget(m_skillTarget->getLogicGrid()->getGridPos());
}



void CSkillComp::onHit()
{
    float damage = m_ownerRole->getATK() - m_skillTarget->getDEF();
    if (damage < 1.f)
    {
        damage = 1.f;
    }
    float curHP = m_skillTarget->getCurHP();
    curHP = curHP - damage;
    if (FLT_LE(curHP, 0.f))
    {
        m_skillTarget->setCurHP(0.f);
        m_skillTarget->changeState(ROLE_STATE_DYING);
    }
    else
    {
        m_skillTarget->setCurHP(curHP);
    }
}



void CSkillComp::onOver()
{
    m_subState = SKILL_SUB_STATE_POST_CAST;
    if (m_skillTarget->isDead())
    {
        m_ownerRole->changeState(ROLE_STATE_MOVE);
    }
}




