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
: m_pHPBar(NULL)
, m_visionRadiusSq(0.f)
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
        CCDictionary* dict = DTUNIT->getData(getUnitId());
        if (dict)
        {
            CCString* str = DTUNIT->get_radius_Value(dict);
            CC_ASSERT(str);
            m_visionRadiusSq = str->floatValue();

            m_visionRadiusSq *= m_visionRadiusSq;
        }
    }
}




SEL_CallFuncN CWarriorRole::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillHit", CWarriorRole::onSkillHit);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSkillOver", CWarriorRole::onSkillOver);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onDyingOver", CWarriorRole::onDyingOver);
    return NULL;
}



#define LOAD_SKILL(__SKILL_IDX__)\
{\
CCString* str = DTUNIT->get_skill##__SKILL_IDX__##_Value(dict);\
CC_ASSERT(str);\
addSkillByName(str->getCString(), __SKILL_IDX__);\
}

bool CWarriorRole::init(const string& unitId)
{
    do
    {
        BREAK_IF(!CRole::init(unitId));
        
        CCDictionary* dict = DTUNIT->getData(unitId);

        CCString* str = DTUNIT->get_radius_Value(dict);
        CC_ASSERT(str);
        m_visionRadiusSq = str->floatValue();

        // load skills
        LOAD_SKILL(0);
        LOAD_SKILL(1);
        LOAD_SKILL(2);
        LOAD_SKILL(3);
        LOAD_SKILL(4);
        LOAD_SKILL(5);
        
        return true;
    } while (false);
    
    return false;
}



void CWarriorRole::update(float dt)
{
    CRole::update(dt);
    
    updateSkipList(dt);

}


void CWarriorRole::die()
{
    CRole::die();
    
    if (m_pHPBar != NULL)
    {
        m_pHPBar->setSpriteVisible(false);
    }
    
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



//void CWarriorRole::onSensor(CCObject* obj)
//{
//    CWarriorRole* wr = (CWarriorRole*)obj;
//    bool flag = false;
//    if (wr->getRoleGroup() != getRoleGroup())
//    {
//        QSWR_IT it = m_skipList.begin();
//        for (; it != m_skipList.end(); ++it)
//        {
//            if ((*it)->role == wr)
//            {
//                flag = true;
//                break;
//            }
//        }
//        
//        if (!flag)
//        {
//            m_enemyNearby.insert(wr);
//        }
//    }
//}



//void CWarriorRole::onSetSensorType(CSensor* pSensor)
//{
//    pSensor->setSensorTargetType(CT_SOLDIER);
//}
//
//
//
//GBCollisionType CWarriorRole::getCollisionType()
//{
//    return CT_SOLDIER;
//}

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



void CWarriorRole::addCCBAnimationDelegate(ICCBAnimationDelegate* delegate)
{
    m_ccbAnimatonDelegates.insert(delegate);
}



void CWarriorRole::onSkillHit(CCNode* obj)
{
//    SS_IT it = m_skillNames.begin();
//    for (; it != m_skillNames.end(); ++it)
//    {
//        CSkillComp* skill = getSkillCompByName(*it);
//        CC_ASSERT(skill);
//        if (skill->isEnabled())
//        {
//            skill->onHit();
//        }
//    }
    
    SAD_IT it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onSkillHit(obj);
    }
}



void CWarriorRole::onSkillOver(CCNode* obj)
{
//    SS_IT it = m_skillNames.begin();
//    for (; it != m_skillNames.end(); ++it)
//    {
//        CSkillComp* skill = getSkillCompByName(*it);
//        CC_ASSERT(skill);
//        if (skill->isEnabled())
//        {
//            skill->onOver();
//        }
//    }
    
    SAD_IT it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onSkillOver(obj);
    }
}



void CWarriorRole::onDyingOver(CCNode* obj)
{
    SAD_IT it = m_ccbAnimatonDelegates.begin();
    for ( ;it != m_ccbAnimatonDelegates.end(); ++it)
    {
        (*it)->onDyingOver(obj);
    }
}


#pragma mark -- SkipList

void CWarriorRole::addToSkipList(CWarriorRole* role)
{
    MRF_IT it = m_skipList.find(role);
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
    MRF_IT it = m_skipList.begin();
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
    CWarriorRole* target = NULL;
    float distance = m_visionRadiusSq;

    SR& roles = BF_MANAGER->getRoles(m_roleGroup == ROLE_GROUP_ATTACK ? ROLE_GROUP_DEFENDCE : ROLE_GROUP_ATTACK);
    SR_IT it = roles.begin();
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
        SS_IT it = m_skillNames.begin();
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
        setMoveTarget(CCPoint(-1, -1));
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