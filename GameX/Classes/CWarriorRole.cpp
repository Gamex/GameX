//
//  CWarriorRole.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-17.
//
//

#include "CWarriorRole.h"
#include "CSkillComp.h"
#include "CDataCenterManager.h"
#include "CBattleFiledManager.h"


CWarriorRole::CWarriorRole()
: m_visionRadiusSq(0.f)
{
    
}



CWarriorRole::~CWarriorRole()
{
}



void CWarriorRole::setRoleGroup(ROLE_GROUP var)
{
    CRole::setRoleGroup(var);
    if (m_roleGroup == ROLE_GROUP_ATTACK)
    {
        m_visionRadiusSq = FLT_MAX;
    }
    else
    {
        Dictionary* dict = DTUNIT->getData(getUnitId());
        if (dict)
        {
            String* str = DTUNIT->get_radius_Value(dict);
            CC_ASSERT(str);
            m_visionRadiusSq = str->floatValue();

            m_visionRadiusSq *= m_visionRadiusSq;
        }
    }
}




SEL_CallFuncN CWarriorRole::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillHit", CWarriorRole::onSkillHit);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillOver", CWarriorRole::onSkillOver);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onDyingOver", CWarriorRole::onDyingOver);
    return nullptr;
}



#define LOAD_SKILL(__SKILL_IDX__)\
{\
String* str = DTUNIT->get_skill##__SKILL_IDX__##_Value(dict);\
CC_ASSERT(str);\
addSkillByName(str->getCString(), __SKILL_IDX__);\
}

bool CWarriorRole::init(const string& unitId, bool editorMode)
{
    do
    {
        BREAK_IF(!CRole::init(unitId, editorMode));
        
        Dictionary* dict = DTUNIT->getData(unitId);

        String* str = DTUNIT->get_radius_Value(dict);
        CC_ASSERT(str);
        m_visionRadiusSq = str->floatValue();

        // load skills
        if (!editorMode)
        {
            LOAD_SKILL(0);
            LOAD_SKILL(1);
            LOAD_SKILL(2);
            LOAD_SKILL(3);
            LOAD_SKILL(4);
            LOAD_SKILL(5);
        }
        return true;
    } while (false);
    
    return false;
}



void CWarriorRole::enterBattleState()
{
    CRole::enterBattleState();
    m_visionRadiusSq = FLT_MAX;
}


void CWarriorRole::update(float dt)
{
    CRole::update(dt);
    
    updateSkipList(dt);

}


void CWarriorRole::die()
{
    CRole::die();
    
    m_ccbAnimatonDelegates.clear();
}



void CWarriorRole::prepareToDie()
{
    playAnimation(ROLE_ANIMATION_DYING);
    CBackgroundManager* bkg = getBackGround();
    CC_ASSERT(bkg);
    bkg->removeRoleFromGrid(this);
    setRoleGroup(ROLE_GROUP_NA);
    
    setSpriteVertexZ(-900);
}


#pragma mark -- skills

void CWarriorRole::addSkillByName(const string& skillName, int skillIdx)
{
    do
    {
        CC_ASSERT(m_skillNames.find(skillName) == m_skillNames.end());
        String* s = DTSKILL->get_className_Value(skillName);
        BREAK_IF(nullptr == s);
        CSkillComp* skill = (CSkillComp*)OBJECT_FACTORY->createInstance(s->getCString());
        BREAK_IF(nullptr == skill);
        BREAK_IF_FAILED(skill->init(skillName));
        
        skill->setStateId(WARRIOR_ROLE_STATE_SKILL_0 + skillIdx);
        m_skillNames.insert(skill->getName());
        
        addComponentForState(skill->getStateId(), skill);
        
    } while (false);
    
}



CSkillComp* CWarriorRole::getSkillCompByName(const string& skillName)
{
    return (CSkillComp*)getComponent(skillName.c_str());
}



void CWarriorRole::onSkillHit(Node* obj)
{
    auto it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onSkillHit(this);
    }
}



void CWarriorRole::onSkillOver(Node* obj)
{
    auto it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onSkillOver(this);
    }
}



void CWarriorRole::onDyingOver(Node* obj)
{
    auto it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onDyingOver(this);
    }
}


#pragma mark -- SkipList

void CWarriorRole::addToSkipList(CWarriorRole* role)
{
    auto it = m_skipList.find(role);
    if (it == m_skipList.end())
    {
        m_skipList[role] = 5.f;
    }
    else
    {
        (*it).second = 5.f;
    }
}



void CWarriorRole::updateSkipList(float dt)
{
    vector<CRole*> toDel;
    auto it = m_skipList.begin();
    for (; it != m_skipList.end(); ++it)
    {
        (*it).second -= dt;
        if ((*it).second < 0.f)
        {
            toDel.push_back((*it).first);
        }
    }
    
    for (int i = 0; i < toDel.size(); ++i)
    {
        m_skipList.erase(toDel[i]);
    }
}



#pragma mark -- think

void CWarriorRole::thinkOfVisionField()
{
    CC_ASSERT(m_roleGroup != ROLE_GROUP_NA);
    float distance = m_visionRadiusSq;
    
    CWarriorRole* target = (CWarriorRole*)getAttackTarget();
    if (nullptr == target)
    {
        changeState(ROLE_STATE_MOVE);
        SR& roles = BF_MANAGER->getRoles(m_roleGroup == ROLE_GROUP_ATTACK ? ROLE_GROUP_DEFENCE : ROLE_GROUP_ATTACK);
        auto it = roles.begin();
        for (; it != roles.end(); ++it)
        {
            if (m_skipList.find((*it)) == m_skipList.end())
            {
                CWarriorRole* role = (CWarriorRole*)(*it);
                float dist = getDistanceSqInGrid((*it));
                if (dist < distance)
                {
                    distance = dist;
                    target = role;
                }
            }
        }
        if (target)
        {
            attack(target);
        }
    }
    
    if (target && !target->isDying() && !target->isDead())
    {
        distance = getDistanceSqInGrid(target);
        auto it = m_skillNames.begin();
        for (; it != m_skillNames.end(); ++it)
        {
            const string& name = *it;
            CSkillComp* skill = getSkillCompByName(name);
            CC_ASSERT(skill);
            if (skill->checkTarget(target, distance))
            {
                changeState(skill->getStateId());
                break;
            }
        }

        CLogicGrid* lg = target->getLogicGrid();
        CC_ASSERT(lg);
        setMoveTarget(lg->getGridPos());
    }
    else
    {
        setMoveTarget(Point(-1, -1));
    }
    
}



void CWarriorRole::think()
{
#ifdef DEBUG
    if (getMark())
    {
        thinkOfVisionField();
    }
    else
#endif
    {
        thinkOfVisionField();
    }
}