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

DEFINE_DICTFUNC(CWarriorRole, float, MaxHP, 0);
DEFINE_DICTFUNC(CWarriorRole, float, AttackRange, 0);


CWarriorRole::CWarriorRole()
: m_pHPBar(NULL)
, m_speed(180)
{
    
}



CWarriorRole::~CWarriorRole()
{
}



bool CWarriorRole::init(CCDictionary* pObjectDict)
{
    do
    {
        BREAK_IF_FAILED(CRole::init(pObjectDict));

        return true;
    } while (false);
    
    return false;
}



SEL_CallFuncN CWarriorRole::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillHit", CWarriorRole::onSkillHit);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillOver", CWarriorRole::onSkillOver);
    return NULL;
}



#define LOAD_SKILL(__SKILL_IDX__)\
{\
CCString* str = DTUNIT->get_skill##__SKILL_IDX__##_Value(dict);\
CC_ASSERT(str);\
addSkillByName(str->getCString(), __SKILL_IDX__);\
}

void CWarriorRole::loadRoleData(const string& unitName)
{
    CRole::loadRoleData(unitName);
    
    CCDictionary* dict = DTUNIT->getData(unitName);
    setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
    setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());
    
    // load skills
    LOAD_SKILL(0);
    LOAD_SKILL(1);
    LOAD_SKILL(2);
    LOAD_SKILL(3);
    LOAD_SKILL(4);
    LOAD_SKILL(5);
}



void CWarriorRole::update(float dt)
{
    CRole::update(dt);
    
    updateSkipList(dt);
    
    m_enemyNearby.clear();
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



void CWarriorRole::onSensor(CCObject* obj)
{
    CWarriorRole* wr = (CWarriorRole*)obj;
    bool flag = false;
    if (wr->getRoleGroup() != getRoleGroup())
    {
        QSWR_IT it = m_skipList.begin();
        for (; it != m_skipList.end(); ++it)
        {
            if ((*it)->role == wr)
            {
                flag = true;
                break;
            }
        }
        
        if (!flag)
        {
            m_enemyNearby.insert(wr);
        }
    }
}



void CWarriorRole::onSetSensorType(CSensor* pSensor)
{
    pSensor->setSensorTargetType(CT_SOLDIER);
}



GBCollisionType CWarriorRole::getCollisionType()
{
    return CT_SOLDIER;
}

#pragma mark -- skills

void CWarriorRole::addSkillByName(const string& skillName, int skillIdx)
{
    do
    {
        CC_ASSERT(m_skillNames.find(skillName) == m_skillNames.end());
        CCString* s = DTSKILL->get_className_Value(skillName);
        BREAK_IF(NULL == s);
        CSkillComp* skill = CSkillComp::createObject(s->getCString());
        BREAK_IF(NULL == skill);
        BREAK_IF_FAILED(skill->loadSkill(skillName));
        
        skill->setStateId(WARRIOR_ROLE_STATE_SKILL_0 + skillIdx);
        m_skillNames.insert(skill->getName());
        
        addComponentForState(skill->getStateId(), skill);
        
    } while (false);
    
}



CSkillComp* CWarriorRole::getSkillCompByName(const string& skillName)
{
    return (CSkillComp*)getComponent(skillName.c_str());
}




void CWarriorRole::onSkillHit(CCNode* obj)
{
    SS_IT it = m_skillNames.begin();
    for (; it != m_skillNames.end(); ++it)
    {
        CSkillComp* skill = getSkillCompByName(*it);
        CC_ASSERT(skill);
        if (skill->isEnabled())
        {
            skill->onHit();
        }
    }
}



void CWarriorRole::onSkillOver(CCNode* obj)
{
    SS_IT it = m_skillNames.begin();
    for (; it != m_skillNames.end(); ++it)
    {
        CSkillComp* skill = getSkillCompByName(*it);
        CC_ASSERT(skill);
        if (skill->isEnabled())
        {
            skill->onOver();
        }
    }
}


#pragma mark -- SkipList

void CWarriorRole::addToSkipList(CWarriorRole* role)
{
    CSkipWarriorRole* swr = new CSkipWarriorRole;
    swr->role = role;
    swr->time = 5.f;
    m_skipList.push_back(swr);
}



void CWarriorRole::updateSkipList(float dt)
{
    QSWR_IT it = m_skipList.begin();
    for (; it != m_skipList.end(); )
    {
        (*it)->time -= dt;
        if ((*it)->time < 0.f)
        {
            delete *it;
            it = m_skipList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}



#pragma mark -- think

void CWarriorRole::thinkOfSkill()
{
    SS_IT it = m_skillNames.begin();
    for (; it != m_skillNames.end(); ++it)
    {
        const string& name = *it;
        CSkillComp* skill = getSkillCompByName(name);
        CC_ASSERT(skill);
        if (skill->checkDo())
        {
            changeState(skill->getStateId());
            break;
        }
    }
}



void CWarriorRole::thinkOfVisionField()
{
    // first check if there is new target to attack
    CCPoint myPos = getSpritePosition();
    CWarriorRole* target = NULL;
    float distance = FLT_MAX;
    
    SR_IT it = m_enemyNearby.begin();
    for(; it != m_enemyNearby.end(); ++it)
    {
        CWarriorRole* role = (CWarriorRole*)(*it);
        CCPoint pos = role->getSpritePosition();
        float dist = pos.getDistanceSq(myPos);
        if (dist < distance)
        {
            distance = dist;
            target = role;
        }
    }
    
    if (target)
    {
        CLogicGrid* lg = target->getLogicGrid();
        CC_ASSERT(lg);
        setMoveTarget(lg->getGridPos());
    }
}



void CWarriorRole::think()
{
    thinkOfSkill();
    if (getCurrentState() == ROLE_STATE_MOVE)
    {
        thinkOfVisionField();
    }
}