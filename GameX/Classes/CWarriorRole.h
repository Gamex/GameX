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
#include "ICCBAnimationDelegate.h"

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

class CWarriorRole : public CRole
{
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
public:
    FACTORY_CREATE_FUNC(CWarriorRole);
    
    virtual ~CWarriorRole();

    virtual bool init(const string& unitId);
    virtual void die();
    
    virtual void update(float dt);
    
    virtual void setRoleGroup(ROLE_GROUP var);

    virtual const SS& getSkillNames() const {return m_skillNames;};
    
    virtual void addSkillByName(const string& skillName, int skillIdx);
    virtual CSkillComp* getSkillCompByName(const string& skillName);
    
    virtual int getNormalAttackStateId() const {return WARRIOR_ROLE_STATE_SKILL_0;}
    
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);

    virtual void addToSkipList(CWarriorRole* role);
    virtual void updateSkipList(float dt);
    
    virtual void prepareToDie();
    
    virtual void think();
    
protected:
    CWarriorRole();

    virtual bool createHPBar();
    virtual void findNearestMonsterToAttack(){};

    virtual void thinkOfVisionField();
    
    virtual void onSkillHit(CCNode* obj);
    virtual void onSkillOver(CCNode* obj);
    virtual void onDyingOver(CCNode* obj);

    float m_visionRadiusSq;

    SS m_skillNames;
    
    MRF m_skipList;
    
private:

};

#endif /* defined(__GameX__CWarriorRole__) */
