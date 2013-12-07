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
: m_bkgMgr(nullptr)
, m_batchNode(nullptr)
{
}



CEffectManager::~CEffectManager()
{
    clear();
}



void CEffectManager::clear()
{
    auto it = m_caches.begin();
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
        
        m_allEffects = DTEFFECT->getAllKeys();
        int eftCount = m_allEffects.size();
        CC_ASSERT(eftCount > 0);
        m_caches.reserve(eftCount);
        
        for (int i = 0; i < eftCount; ++i)
        {
            auto effectData = DTEFFECT->getData(m_allEffects[i]);
            CC_ASSERT(nullptr != effectData);
            int cacheNum = effectData->cacheNum;

            CNodeContainer* nc = new CNodeContainer;
            bool res = nc->initCache(effectData->className, cacheNum, this,
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
    auto it = m_caches.begin();
    for (; it != m_caches.end(); ++it)
    {
        SOB toDel;
        const SOB& sob = (*it)->getInUseArray();
        auto sob_it = sob.begin();
        for (; sob_it != sob.end(); ++sob_it)
        {
            CGameEffect* gf = (CGameEffect*)(*sob_it);
            if (gf->isDead())
            {
                toDel.insert(gf);
                CRole* et = gf->getEffectTarget();
                CC_ASSERT(et);
                et->removeSlot(gf);
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
        Point pt = target->getSpritePosition();
        effect->setSpritePosition(pt);
        
        if (!target->addSlot(effect, effect->getTag()))
        {
            effect->setSpriteVisible(false);
        }
        
        effect->playAnimation(EFFECT_ANIMATION_RUN);

        effect->setEffectTarget(target);
        return effect;

    } while (false);
    
	return nullptr;
}




bool CEffectManager::onCacheElemInit(SOB& unUseArrray, CObjectBase* curObj, void* pUserData)
{
    do
    {
        int idx = (int)pUserData;
        auto effectData = DTEFFECT->getData(m_allEffects[idx]);
        CGameEffect* gf = (CGameEffect*)curObj;
        BREAK_IF_FAILED(gf->init(effectData->resourceID));
        gf->die();
        gf->setTag(idx);
        gf->attachSpriteTo(m_bkgMgr);
        return true;
    } while (false);
    
    return false;
}

