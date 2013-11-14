//
//  CSkillComp.h
//  GameX
//
//  Created by 马 俊 on 13-10-10.
//
//

#ifndef __GameX__CSkillComp__
#define __GameX__CSkillComp__

#include "CWarriorRoleCompBase.h"


enum
{
    SKILL_SUB_STATE_READY,
    SKILL_SUB_STATE_PRE_CAST,
    SKILL_SUB_STATE_CASTING,
    SKILL_SUB_STATE_POST_CAST,
};


class CSkillComp
: public CWarriorRoleCompBase
{
    CC_SYNTHESIZE(int, m_stateId, StateId);
    CC_SYNTHESIZE_READONLY(float, m_CDTotalTime, CDTotalTime);
    CC_SYNTHESIZE_READONLY(float, m_CDLeftTime, CDLeftTime);
public:
    virtual bool init(const string& skillName);
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    virtual bool checkTarget(CRole* target, float distance);
    virtual void action();
    
    virtual void onSkillHit(Node* obj);
    virtual void onSkillOver(Node* obj);
protected:
    CSkillComp(void);
    
    virtual void updateCD(float dt);

    float m_attackRadiusSq;
    CRole* m_skillTarget;
    bool m_enableUpdateCD;
private:
};

#endif /* defined(__GameX__CSkillComp__) */
