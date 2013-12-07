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


CSkillComp::CSkillComp(void)
: CWarriorRoleCompBase(SKILL_SUB_STATE_READY)
, m_CDTotalTime(0.f)
, m_CDLeftTime(0.f)
, m_stateId(-1)
, m_skillTarget(nullptr)
, m_enableUpdateCD(false)
{
    setName("SkillComp");
}



bool CSkillComp::init(const string& skillName)
{
    do
    {
        BREAK_IF_FAILED(CWarriorRoleCompBase::init());
        
        const DTSkill::_Data* skillData = DTSKILL->getData(skillName);
        CC_ASSERT(skillData);

        m_attackRadiusSq = skillData->range;
        
        m_CDTotalTime = skillData->cd;
        m_CDLeftTime = 0.f;
        
        setName(skillName.c_str());
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

#ifdef DEBUG
        if (m_ownerRole->getMark())
        {
            action();
        }
        else
#endif
        {
            action();
        }
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
#ifdef DEBUG
        if (m_ownerRole->getMark())
        {
            CWarriorRoleCompBase::update(dt);
        }
        else
#endif
        {
            CWarriorRoleCompBase::update(dt);
        }

        updateCD(dt);
        
        if (!isEnabled()) return;
        
        switch (m_subState)
        {
            case SKILL_SUB_STATE_READY:
                THINK_AND_BREAK();
                m_ownerRole->playAnimation(ROLE_ANIMATION_IDLE);
                if (FLT_EQUAL(m_CDLeftTime, 0.f))
                {
                    m_subState = SKILL_SUB_STATE_PRE_CAST;
                    m_enableUpdateCD = false;
                }
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

        if (distance > m_attackRadiusSq)
        {
            break;
        }
        m_skillTarget = target;
        return true;
    } while (false);
    
    return false;
}



void CSkillComp::action()
{
    m_subState = SKILL_SUB_STATE_PRE_CAST;
    m_CDLeftTime = 0.f;
    
    m_ownerRole->setMoveTarget(m_skillTarget->getLogicGrid()->getGridPos());
}



void CSkillComp::onSkillHit(Node* obj)
{
}



void CSkillComp::onSkillOver(Node* obj)
{
    if (!isEnabled())
    {
        return;
    }
#ifdef DEBUG
    if (m_ownerRole->getMark())
    {
        m_subState = SKILL_SUB_STATE_POST_CAST;
    }
    else
#endif
    {
        m_subState = SKILL_SUB_STATE_POST_CAST;
        m_CDLeftTime = m_CDTotalTime;
        m_enableUpdateCD = true;
    }

}



void CSkillComp::updateCD(float dt)
{
    if (m_enableUpdateCD)
    {
        if (FLT_GE(m_CDLeftTime, 0))
        {
            m_CDLeftTime -= dt;
            if (FLT_LE(m_CDLeftTime, 0.f))
            {
                m_CDLeftTime = 0.f;
            }
        }
    }
}




