//
//  CBattleFiledManager.h
//  GameX
//
//  Created by 马 俊 on 13-10-8.
//
//

#ifndef __GameX__CBattleFiledManager__
#define __GameX__CBattleFiledManager__

#include "Common.h"
#include "CSingleton.h"
#include "CRole.h"

class CBattleFiledManager : public CSingleton<CBattleFiledManager>
{
    CC_SYNTHESIZE(float, m_maxLoopTime, MaxLoopTime);
public:
    CBattleFiledManager();
    virtual ~CBattleFiledManager();
    
//    virtual bool init();
    virtual void addRole(CRole* role);
    virtual void removeRole(CRole* role);
    virtual SR& getRoles(ROLE_GROUP group);
    virtual void removeAll();
    virtual void update(float dt);
protected:
    
    SR m_roleByGroups[ROLE_GROUP_MAX];
};

#define BF_MANAGER      (CBattleFiledManager::getInstance())

#endif /* defined(__GameX__CBattleFiledManager__) */
