//
//  CWarriorRole.h
//  GameX
//
//  Created by 马 俊 on 13-6-17.
//
//

#ifndef __GameX__CWarriorRole__
#define __GameX__CWarriorRole__

#include "CRole.h"
#include "TFHPBar.h"


class CSkillComp;

#define WARRIOR_STATE_IDLE                              "Idle"
#define WARRIOR_STATE_POS_IN_EDITOR                     "PosInEditor"
#define WARRIOR_STATE_SEL_POS_IN_EDITOR                 "SelPosInEditor"

enum WARRIOR_ROLE_STATE
{
    WARRIOR_ROLE_STATE_ATTACK = ROLE_STATE_MAX,
    WARRIOR_ROLE_STATE_SKILL_0,
    WARRIOR_ROLE_STATE_SKILL_1,
    WARRIOR_ROLE_STATE_SKILL_2,
    WARRIOR_ROLE_STATE_SKILL_3,
    WARRIOR_ROLE_STATE_SKILL_4,
    WARRIOR_ROLE_STATE_SKILL_5,
    WARRIOR_ROLE_STATE_MAX,
};

class CSkipWarriorRole
{
public:
    float time;
    class CWarriorRole* role;
};

class CWarriorRole : public CRole
{
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
public:
    FACTORY_CREATE_FUNC(CWarriorRole);
    
    virtual ~CWarriorRole();

    virtual void loadRoleData(const string& unitName);
    virtual bool init(CCDictionary* pObjectDict);
    virtual void die();
    
    virtual void update(float dt);
    
    virtual const SR& getEnemyNearBy() const {return m_enemyNearby;};
    virtual const SS& getSkillNames() const {return m_skillNames;};
    
    virtual void addSkillByName(const string& skillName, int skillIdx);
    virtual CSkillComp* getSkillCompByName(const string& skillName);
    
    virtual int getNormalAttackStateId() const {return WARRIOR_ROLE_STATE_SKILL_0;}
    
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);

    virtual void addToSkipList(CWarriorRole* role);
    virtual void updateSkipList(float dt);
    
    DECLARE_DICTFUNC(float, MaxHP);
    DECLARE_DICTFUNC(float, AttackRange);
protected:
    CWarriorRole();

    virtual bool createHPBar();
    virtual void findNearestMonsterToAttack(){};
    
    virtual void onSensor(CCObject* obj);
    virtual void onSetSensorType(CSensor* pSensor);
    
    virtual GBCollisionType getCollisionType();
    
    virtual void think();
    virtual void thinkOfSkill();
    virtual void thinkOfVisionField();
    
    virtual void onSkillHit(CCNode* obj);
    virtual void onSkillOver(CCNode* obj);
    
    int m_hitPoint;
    int m_maxHitPoint;
    float m_hitTime;
    float m_speed;

    SR m_enemyNearby;
    SS m_skillNames;
    
    QSWR m_skipList;
private:

};

#endif /* defined(__GameX__CWarriorRole__) */
