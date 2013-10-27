//
//  CEffectManager.h
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#ifndef __GameX__CEffectManager__
#define __GameX__CEffectManager__

#include "Common.h"
#include "CGameEffect.h"
#include "CNodeContainer.h"


class CBackgroundManager;

class CEffectManager
: public CSingleton<CEffectManager>
, public CCObject
{
public:
    CEffectManager();
    virtual ~CEffectManager();
    
    virtual bool init(CBackgroundManager* bm);
    
    CGameEffect* createEffect(int eftNo, CRole* target);

    virtual void update(float dt);
    virtual void clear();
protected:
    virtual bool onCacheElemInit(SOB& unUseArrray, CObjectBase* curObj, void* pUserData);
    
    CBackgroundManager* m_bkgMgr;
    VNC m_caches;
};


#define EFFECT_MANAGER      (CEffectManager::getInstance())

#endif /* defined(__GameX__CEffectManager__) */
