//
//  CSkillManager.h
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#ifndef __GameX__CSkillManager__
#define __GameX__CSkillManager__

#include "Common.h"
#include "CSingleton.h"


#pragma mark -- CSkill

class ISkillDelegate
{
public:
    virtual void onSkillOver() = 0;
};

class CSkill
{
    CC_SYNTHESIZE(ISkillDelegate*, m_delegate, Delegate);
public:
    CSkill();
    virtual ~CSkill();
protected:
    std::string m_skillAnimationName;            // the timeline's name in role's ccbi file.
    std::string m_effectName;
private:
};


#pragma mark -- CSkillManager

class CSkillManager
: public CSingleton<CSkillManager>
{
public:
    CSkillManager();
    virtual ~CSkillManager();
    
    virtual bool init();
protected:
private:
};


#define SKILL_MANAGER       (CSkillManager::getInstance())

#endif /* defined(__GameX__CSkillManager__) */
