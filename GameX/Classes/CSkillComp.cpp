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
        m_attackRadiusSq *= m_attackRadiusSq;

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
        
        switch (m_subState)
        {
            case SKILL_SUB_STATE_READY:
                break;
            case SKILL_SUB_STATE_PRE_CAST:
                m_ownerRole->setFaceTo(m_skillTarget);
                m_ownerRole->playAnimation(ROLE_ANIMATION_ATTACK);
                m_subState = SKILL_SUB_STATE_CASTING;
                break;
            case SKILL_SUB_STATE_CASTING:
                break;
            case SKILL_SUB_STATE_POST_CAST:
                setEnabled(false);
                m_subState = SKILL_SUB_STATE_READY;
                break;
            default:
                break;
        }

    } while (false);
}



void CSkillComp::scanTarget()
{
    do
    {
        const SR& enemies = m_ownerRole->getEnemyNearBy();

        CCPoint ownerPos = m_ownerRole->getSpritePosition();
        float shortestLen = FLT_MAX;
        CWarriorRole* target = NULL;
        
        SR_IT it = enemies.begin();
        for(; it != enemies.end(); ++it)
        {
            CWarriorRole* wr = (CWarriorRole*)(*it);
            CCPoint pt = wr->getSpritePosition();
            
            float dist = pt.getDistanceSq(ownerPos);
            if (dist < shortestLen)
            {
                shortestLen = dist;
                target = wr;
            }
        }
    } while (false);
        
}



bool CSkillComp::checkDo()
{
    do
    {
        BREAK_IF(isEnabled());      // enable means the skill is casting.So no need to check again.
        BREAK_IF(getCDLeftTime() > 0);      // CDing...
        
        CCPoint ownerPos = m_ownerRole->getSpritePosition();
        
        SR enemies = m_ownerRole->getEnemyNearBy();
        m_skillTarget = NULL;
        float nearest_dist = FLT_MAX;
        SR_IT it = enemies.begin();
        for (; it != enemies.end(); ++it)
        {
            float dist = m_ownerRole->getDistanceSqInGrid(*it);
            if (dist < nearest_dist)
            {
                nearest_dist = dist;
                m_skillTarget = (CRole*)(*it);
            }
        }
        BREAK_IF(nearest_dist > m_attackRadiusSq);
        
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
}



void CSkillComp::onOver()
{
    m_subState = SKILL_SUB_STATE_POST_CAST;
}




