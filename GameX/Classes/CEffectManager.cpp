//
//  CEffectManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-27.
//
//

#include "CEffectManager.h"
#include "CRole.h"
#include "CDataCenterManager.h"

IMPLEMENT_SINGLETON(CEffectManager);

CEffectManager::CEffectManager()
: m_bkgMgr(NULL)
{
}



CEffectManager::~CEffectManager()
{
    clear();
}



void CEffectManager::clear()
{
    VNC_IT it = m_caches.begin();
    for (; it != m_caches.end(); ++it)
    {
        delete *it;
    }
    m_caches.clear();
}



bool CEffectManager::init(CBackgroundManager* bm)
{
    do
    {
        CC_ASSERT(bm);
        m_bkgMgr = bm;
        
        clear();
        
        int eftCount = DTEFFECT->getArrayCount();
        CC_ASSERT(eftCount > 0);
        m_caches.reserve(eftCount);
        
        for (int i = 0; i < eftCount; ++i)
        {
            CCString* s = DTEFFECT->get_cacheNum_Value(i);
            CC_ASSERT(s);
            int cacheNum = s->intValue();
            
            s = DTEFFECT->get_className_Value(i);
            CC_ASSERT(s);
            
            
            CNodeContainer* nc = new CNodeContainer[eftCount];
            bool res = nc->initCache(s->getCString(), cacheNum, this,
                                         (NODE_CONTAINER_INIT_CALL_BACK)&CEffectManager::onCacheElemInit,
                                         (void*)i);
            CC_ASSERT(res);
            m_caches.push_back(nc);
        }
        return true;
    } while (false);
    
	return false;
}



void CEffectManager::update(float dt)
{
    VNC_IT it = m_caches.begin();
    for (; it != m_caches.end(); ++it)
    {
        SOB toDel;
        const SOB& sob = (*it)->getInUseArray();
        SOB_IT sob_it = sob.begin();
        for (; sob_it != sob.end(); ++sob_it)
        {
            if ((*sob_it)->isDead())
            {
                toDel.insert(*sob_it);
            }
        }
        
        sob_it = toDel.begin();
        for (; sob_it != toDel.end(); ++sob_it)
        {
            (*it)->checkinElement(*sob_it);
        }
        toDel.clear();
    }
}



CGameEffect* CEffectManager::createEffect(int eftNo, CRole* target)
{
    do
    {
        CC_ASSERT(eftNo >= 0 && eftNo < m_caches.size());
        CGameEffect* effect = (CGameEffect*)m_caches[eftNo]->checkoutElement();
        CC_ASSERT(effect);

        effect->revive();
        CCPoint pt = target->getSpritePosition();
        effect->setSpritePosition(pt);
        
        effect->playAnimation(EFFECT_ANIMATION_RUN);
        
        effect->setEffectTarget(target);
        return effect;

    } while (false);
    
	return NULL;
}




bool CEffectManager::onCacheElemInit(SOB& unUseArrray, CObjectBase* curObj, void* pUserData)
{
    do
    {
        int idx = (int)pUserData;

        CCString* s = DTEFFECT->get_resourceID_Value(idx);
        CGameEffect* gf = (CGameEffect*)curObj;
        BREAK_IF_FAILED(gf->init(s->getCString()));
        curObj->die();
        
        gf->attachSpriteTo(m_bkgMgr);
        return true;
    } while (false);
    
    return false;
}

