//
//  CMoveOnGridComp.h
//  GameX
//
//  Created by 马 俊 on 13-9-15.
//
//

#ifndef __GameX__CMoveOnGridComp__
#define __GameX__CMoveOnGridComp__

#include "cocos2d.h"
#include "CPathFinderManager.h"

class CRole;

USING_NS_CC;

enum
{
    SUB_STATE_IDLE,
    SUB_STATE_PATH_FINDING,
    SUB_STATE_PATH_FOUND,
    SUB_STATE_MOVING,
};

class CMoveOnGridComp
: public CCComponent
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
    virtual void findPathIfNeeded();
private:
    vector<CCPoint> m_paths;
    CRole* m_ownerRole;
    
    CCPoint m_moveFrom;
    CCPoint m_moveTo;
    float m_moveTotalTime;
    float m_moveElapseTime;
    int m_subState;
};

#endif /* defined(__GameX__CMoveOnGridComp__) */
