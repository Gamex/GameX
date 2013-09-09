//
//  CSoldierManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#include "CSoldierManager.h"
#include "CSoldier.h"

IMPLEMENT_SINGLETON(CSoldierManager);

const char* CSoldierManager::m_sSoldierNames[SOLDIER_TYPE_NUM] =
{
    "2001",
    //    "Soldier1",
    //    "Soldier2",
};


const int CSoldierManager::m_sSoldierCacheNum[SOLDIER_TYPE_NUM] =
{
    50,     // for Soldier0
    //    1,     // for Soldier1
    //    1,     // for Soldier2
};


CSoldierManager::CSoldierManager()
: m_pContainers(NULL)
, m_numOfCamps(5)
{
}



CSoldierManager::~CSoldierManager()
{
    clearThis();
}



void CSoldierManager::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void CSoldierManager::clearThis()
{
    
    if (NULL != m_pContainers)
    {
        for (int i = 0; i < SOLDIER_TYPE_NUM; ++i)
        {
            m_pContainers[i].clear();
        }
    }
    CC_SAFE_DELETE_ARRAY(m_pContainers);
    
    m_SoldierTypeNameTable.clear();
    
//    CBatchNodeObject::clearAllBatchNode();
}




bool CSoldierManager::initialize()
{
    do
    {
        BREAK_IF(!CObjectBase::init(NULL));
//        BREAK_IF(!CBatchNodeObject::init());
        
        m_pContainers = new CNodeContainer[SOLDIER_TYPE_NUM];
        for (int i = 0; i < SOLDIER_TYPE_NUM; ++i)
        {
            m_SoldierTypeNameTable[string(m_sSoldierNames[i])] = (SOLDIER_TYPE)i;
            if (!m_pContainers[i].initCache(m_sSoldierNames[i], m_sSoldierCacheNum[i]))
            {
                return false;
            }
        }
        
        for (int i = 0; i < m_numOfCamps; ++i)
        {
            m_SoldierCamps.push_back(QS());
        }

        
        return true;
    } while (false);
    
    return false;
}



void CSoldierManager::update(float dt)
{
    CObjectBase::update(dt);
    
    updateSoldierCamps(dt);
    
    CCObject* pObj;
    CCArray needToCheckIn;
    
    for (int i = 0; i < SOLDIER_TYPE_NUM; ++i)
    {
        const CCArray* children = m_pContainers[i].getInUseArray();
        CCARRAY_FOREACH(children, pObj)
        {
            CSoldier* pSpr = dynamic_cast<CSoldier*>(pObj);
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
            m_pContainers[i].checkinElement(static_cast<CSoldier*>(pObj));
        }
        needToCheckIn.removeAllObjects();
    }
}


CSoldier* CSoldierManager::spawnSoldier(const string& name, const CCPoint& getherPosition)
{
    do
    {
        MSI_IT it = m_SoldierTypeNameTable.find(name);
        BREAK_IF(it == m_SoldierTypeNameTable.end());

        return spawnSoldier(SOLDIER_TYPE((*it).second), getherPosition);
    } while (false);
    
    return NULL;
}



CSoldier* CSoldierManager::spawnSoldier(SOLDIER_TYPE type, const CCPoint& getherPosition)
{
    do
    {
        CSoldier* soldier = getSoldier(type);
        soldier->setSpritePosition(ccp(128, CCRANDOM_0_1()*320));
        soldier->goStraightToTarget(ccp(240, CCRANDOM_0_1()*320));
        soldier->attachSpriteTo();
        addChild(soldier);
        
        return soldier;
    } while (false);
    
    return NULL;
}



CSoldier* CSoldierManager::getSoldier(SOLDIER_TYPE type)
{
    do
    {
        BREAK_IF(type < 0 || type >= SOLDIER_TYPE_NUM);
        CSoldier* soldier = dynamic_cast<CSoldier*>(m_pContainers[type].checkoutElement());
        BREAK_IF(NULL == soldier);
        soldier->setType(type);
        soldier->revive();
        return soldier;
    } while (false);
    
    return NULL;
}



void CSoldierManager::updateSoldierCamps(float dt)
{
    for (int i = 0; i < m_numOfCamps; ++i)
    {
        QS& qs = m_SoldierCamps[i];
        if (!qs.empty())
        {
            CSoldierBuildTask& bt = m_SoldierCamps[i].front();
            if (bt.m_buildTime > 0.f)
            {
                bt.m_buildTime -= dt;
            }
            else
            {
                spawnSoldier(bt.m_soldierName, bt.m_bothPosition);
                qs.pop();
            }
        }
    }
}



void CSoldierManager::buildSoldier(int CampNo, const string& soldierName)
{
    CC_ASSERT(CampNo >= 0 && CampNo < m_numOfCamps);
    
    QS& qs = m_SoldierCamps[CampNo];
    CSoldierBuildTask bt;
    bt.m_soldierName = soldierName;
    bt.m_buildTime = 2.f;
    bt.m_bothPosition = ccp(320, 240);
    qs.push(bt);
}


