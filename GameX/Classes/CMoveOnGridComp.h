//
//  CMoveOnGridComp.h
//  GameX
//
//  Created by 马 俊 on 13-9-15.
//
//

#ifndef __GameX__CMoveOnGridComp__
#define __GameX__CMoveOnGridComp__

#include "CWarriorRoleCompBase.h"
#include "CPathFinderManager.h"

class CRole;

USING_NS_CC;

enum
{
    MOVE_SUB_STATE_IDLE,
    MOVE_SUB_STATE_PATH_FIND,
    MOVE_SUB_STATE_PATH_FINDING,
    MOVE_SUB_STATE_PATH_FOUND,
    MOVE_SUB_STATE_MOVING,
    MOVE_SUB_STATE_ROLL_BACK,
};

class CMoveOnGridComp
: public CWarriorRoleCompBase
, public IPathFinderDelegate
{
public:
    CREATE_FUNC(CMoveOnGridComp);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);

protected:
    CMoveOnGridComp(void);
    
    virtual void onPathReady(const vector<CCPoint>& path);
    virtual void findPathIfNeeded(bool briefFind);
private:
    vector<CCPoint> m_paths;
    
    CCPoint m_moveTarget;
    CCPoint m_moveFrom;
    CCPoint m_moveTo;
    float m_moveTotalTime;
    float m_moveElapseTime;
    
    float m_idleSleepTime;
};

#endif /* defined(__GameX__CMoveOnGridComp__) */
