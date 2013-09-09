//
//  CCastleManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#include "CCastleManager.h"
#include "CRole.h"
#include "CArchersGun.h"

IMPLEMENT_SINGLETON(CCastleManager);

const char* CCastleManager::m_sCastleNames[CASTLE_ITEM_NUM] =
{
    "unit1",
    "unit2",
};


const int CCastleManager::m_sCastleCacheNum[CASTLE_ITEM_NUM] =
{
    1,
    GUARD_UNIT_NUM,
};


CCastleManager::CCastleManager()
: m_pContainers(NULL)
, m_pBaseUnit(NULL)
{
    for (int i = 0 ; i < GUARD_UNIT_NUM; ++i)
    {
        m_pGuardUnit[i] = NULL;
    }
}



CCastleManager::~CCastleManager()
{
    clearThis();
}



void CCastleManager::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void CCastleManager::clearThis()
{
    
    if (NULL != m_pContainers)
    {
        for (int i=0; i<CASTLE_ITEM_NUM; ++i)
        {
            m_pContainers[i].clear();
        }
    }
    CC_SAFE_DELETE_ARRAY(m_pContainers);
    
    m_castleTypeNameTable.clear();
    
    // majun
//    CBatchNodeObject::clearAllBatchNode();
    
    m_pBaseUnit = NULL;
    for (int i = 0 ; i < GUARD_UNIT_NUM; ++i)
    {
        m_pGuardUnit[i] = NULL;
    }
}




bool CCastleManager::initialize()
{
    do
    {
        BREAK_IF_FAILED(CObjectBase::init(NULL));
//        BREAK_IF_FAILED(CBatchNodeObject::init());
        
        m_pContainers = new CNodeContainer[CASTLE_ITEM_NUM];
        for (int i=0; i<CASTLE_ITEM_NUM; ++i)
        {
            m_castleTypeNameTable[string(m_sCastleNames[i])] = i;
            if (!m_pContainers[i].initCache(m_sCastleNames[i], m_sCastleCacheNum[i]))
            {
                return false;
            }
        }
        
        return true;
    } while (false);
    
    return false;
}



void CCastleManager::update(float dt)
{
    CObjectBase::update(dt);

    
    CCObject* pObj;
    CCArray needToCheckIn;
    
    for (int i=0; i<CASTLE_ITEM_NUM; ++i)
    {
        const CCArray* children = m_pContainers[i].getInUseArray();
        CCARRAY_FOREACH(children, pObj)
        {
            CRole* pSpr = dynamic_cast<CRole*>(pObj);
            if (pSpr)
            {
                if (pSpr->isDead())
                {
                    pSpr->removeSpriteFromParentAndCleanup(false);
                    pSpr->removeFromParentAndCleanup(false);
                    needToCheckIn.addObject(pSpr);
                    removeChild(pSpr, false);
                }
            }
        }
        
        CCARRAY_FOREACH(&needToCheckIn, pObj)
        {
            m_pContainers[i].checkinElement(static_cast<CRole*>(pObj));
        }
        needToCheckIn.removeAllObjects();
    }
}



bool CCastleManager::spawnAll()
{
    return true;
    do
    {
        CCSize winSz = CCDirector::sharedDirector()->getWinSize();
        
        m_pBaseUnit = dynamic_cast<CArchersGun*>(m_pContainers[CIT_BASE_UNIT].checkoutElement());
        CCSize btSz = m_pBaseUnit->getSpriteContentSize();
        BREAK_IF(!m_pBaseUnit);
        m_pBaseUnit->setSpritePosition(ccp(btSz.width / 2.f, winSz.height / 2.f));
        m_pBaseUnit->revive();
        m_pBaseUnit->attachSpriteTo();
        
        addChild(m_pBaseUnit);
        
        float gap = winSz.height / GUARD_UNIT_NUM;
        for (int i = 0; i < GUARD_UNIT_NUM; ++i)
        {
            m_pGuardUnit[i] = dynamic_cast<CArchersGun*>(m_pContainers[CIT_GUARD_UNIT].checkoutElement());
            BREAK_IF(NULL == m_pGuardUnit[i]);
            CCSize atSz = m_pGuardUnit[i]->getSpriteContentSize();
            CCPoint archerTowerPosition = ccp(btSz.width + atSz.width / 2.f + 50,
                                              gap * i + gap / 2.f );
            m_pGuardUnit[i]->setSpritePosition(archerTowerPosition);
            m_pGuardUnit[i]->revive();
            m_pGuardUnit[i]->attachSpriteTo();
            addChild(m_pGuardUnit[i]);
        }
        return false;
    } while (false);
    
    return true;
}



void CCastleManager::setBaseGunAimTarget(const CCPoint& target)
{
    CC_ASSERT(m_pBaseUnit);
    
    m_pBaseUnit->setAimPoint(target);
}



void CCastleManager::triggerBaseGunSkill()
{
    CC_ASSERT(m_pBaseUnit);
    
//    m_pBaseGun->triggerSkill();
}



