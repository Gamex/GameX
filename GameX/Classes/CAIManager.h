//
//  CAIManager.h
//  GameX
//
//  Created by 马 俊 on 13-10-8.
//
//

#ifndef __GameX__CAIManager__
#define __GameX__CAIManager__

#include "Common.h"
#include "CSingleton.h"

class CRole;

class CAIManager : public CSingleton<CAIManager>
{
    CC_SYNTHESIZE(float, m_maxLoopTime, MaxLoopTime);
public:
    CAIManager();
    virtual ~CAIManager();
    
//    virtual bool init();
    virtual void addAI(CRole* role);
    virtual void removeAI(CRole* role);
    virtual void removeAll();
    virtual void update(float dt);
protected:
    
    SR m_aiObjects;
    QR m_queue;
};

#define AI_MANAGER      (CAIManager::getInstance())

#endif /* defined(__GameX__CAIManager__) */
