//
//  CMonsterManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-8.
//
//

#include "CMonsterManager.h"
#include "CMonster.h"
#include "CDataCenterManager.h"


IMPLEMENT_SINGLETON(CMonsterManager);
MEM_POOL_DEFINE(CMonsterSpawnInfo, MONSTER_SPAWN_INFO_MEM_POOL_SIZE);

const char* CMonsterManager::m_sMonsterNames[MONSTER_TYPE_NUM] =
{
    "1001",
//    "Monster1",
//    "Monster2",
};


const int CMonsterManager::m_sMonsterCacheNum[MONSTER_TYPE_NUM] =
{
    100,     // for Monster0
//    1,     // for Monster1
//    1,     // for Monster2
};


CMonsterManager::CMonsterManager()
: m_lastMonsterSpawnedTime(2.f)
, m_pContainers(NULL)
, m_curLevelIdx(0)
, m_timeLine(0.f)
{

}



CMonsterManager::~CMonsterManager()
{
    clearThis();
}



void CMonsterManager::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void CMonsterManager::clearThis()
{

    if (NULL != m_pContainers)
    {
        for (int i=0; i<MONSTER_TYPE_NUM; ++i)
        {
            m_pContainers[i].clear();
        }
    }
    CC_SAFE_DELETE_ARRAY(m_pContainers);
    
    m_monsterTypeNameTable.clear();
    
//    CBatchNodeObject::clearAllBatchNode();
}




bool CMonsterManager::initialize()
{
    do
    {
        BREAK_IF_FAILED(CObjectBase::init(NULL));
        
        m_pContainers = new CNodeContainer[MONSTER_TYPE_NUM];
        for (int i=0; i<MONSTER_TYPE_NUM; ++i)
        {
            m_monsterTypeNameTable[string(m_sMonsterNames[i])] = (MONSTER_TYPE)i;
            if (!m_pContainers[i].initCache(m_sMonsterNames[i], m_sMonsterCacheNum[i]))
            {
                return false;
            }
        }
        
        return true;
    } while (false);
    
    return false;
}



void CMonsterManager::update(float dt)
{
    CObjectBase::update(dt);
    
    m_timeLine += dt;
    
    spawnMonsterOnTimer(dt);
    
    CCObject* pObj;
    CCArray needToCheckIn;
    
    for (int i=0; i<MONSTER_TYPE_NUM; ++i)
    {
        const CCArray* children = m_pContainers[i].getInUseArray();
        CCARRAY_FOREACH(children, pObj)
        {
            CMonster* pSpr = dynamic_cast<CMonster*>(pObj);
            if (pSpr)
            {
                if (pSpr->isDead())
                {
                    pSpr->removeSpriteFromParentAndCleanup(false);
                    pSpr->removeFromParentAndCleanup(false);
                    needToCheckIn.addObject(pSpr);
                    removeChild(pSpr, false);
                }
                else
                {
                    float y = pSpr->getSpritePositionInWorldSpace().y;
                    pSpr->getInnerSprite()->getParent()->
                    reorderChild(pSpr->getInnerSprite(), (int)(1000-y));
                }
            }
        }
        
        CCARRAY_FOREACH(&needToCheckIn, pObj)
        {
            m_pContainers[i].checkinElement(static_cast<CMonster*>(pObj));
        }
        needToCheckIn.removeAllObjects();
    }
}



void CMonsterManager::spawnMonster(CMonsterSpawnInfo* info)
{
    CC_ASSERT(info);

    CMonster* monster = dynamic_cast<CMonster*>(m_pContainers[0].checkoutElement());
    if (monster)
    {
        monster->revive();
        monster->setSpritePosition(info->position);
        monster->goStraightToTarget(ccp(0, rand() % 320));
        monster->attachSpriteTo();
        addChild(monster);
    }
}



void CMonsterManager::spawnMonsterOnTimer(float dt)
{
    // construct spawn list
    CCDictionary* level = DTLEVEL->getData(m_curLevelIdx);
    while (level)
    {
        CCString* s = DTLEVEL->get_time_Value(level);
        if (s->floatValue() <= m_timeLine)
        {
            s = DTLEVEL->get_num_Value(level);
            int num = s->intValue();
            
            s = DTLEVEL->get_duration_Value(level);
            float duration = s->floatValue();
            
            CCString* monsterId = DTLEVEL->get_monsterID_Value(level);

            for (int i = 0; i < num; ++i)
            {
                CMonsterSpawnInfo* info = new CMonsterSpawnInfo;
                CC_ASSERT(info);
                info->countDown = CCRANDOM_0_1() * duration;
                info->monsterId = monsterId->getCString();
                
                s = DTLEVEL->get_positionID_Value(level);
                CCDictionary* sceneDict = DTSCENE->getData(s->getCString());
                CC_ASSERT(sceneDict);
                s = DTSCENE->get_positionx_Value(sceneDict);
                info->position.x = s->floatValue();

                s = DTSCENE->get_positiony_Value(sceneDict);
                info->position.y = s->floatValue();
                
                s = DTSCENE->get_length_Value(sceneDict);
                info->position.x += CCRANDOM_MINUS1_1() * s->floatValue() / 2.f;
                
                s = DTSCENE->get_width_Value(sceneDict);
                info->position.y += CCRANDOM_MINUS1_1() * s->floatValue() / 2.f;
                
                m_spawnInfo.push_back(info);
            }
            m_curLevelIdx++;
            level = DTLEVEL->getData(m_curLevelIdx);
        }
        else
        {
            break;
        }
    };
    
    // check spawn list
    VMSI_IT it = m_spawnInfo.begin();
    while (it != m_spawnInfo.end())
    {
        CMonsterSpawnInfo* info = *it;
        info->countDown -= dt;
        if (FLT_LE(info->countDown, 0))
        {
            spawnMonster(info);
            it = m_spawnInfo.erase(it);
            delete info;
        }
        else
        {
            ++it;
        }
    }
    
//    m_lastMonsterSpawnedTime -= dt;
//    if (m_lastMonsterSpawnedTime <= 0)
//    {
////        if (rand() % 100 > 50)
//        {
//            spawnMonster();
//        }
//        m_lastMonsterSpawnedTime = 1.f;
//    }
}



void CMonsterManager::setMonsterSpawnPosition(CMonster* pMonster)
{
    CC_ASSERT(pMonster);
    
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    
    int edge = rand() % 3;
    CCPoint position;
    switch (edge)
    {
        case 0:             // top
            position.x = CCRANDOM_0_1() * (winSz.width / 2.f);
            position.x += winSz.width / 2.f;
            position.y = winSz.height + m_obContentSize.height / 2.f;
            break;
        case 1:             // right
            position.x = winSz.width + m_obContentSize.width / 2.f;
            position.y = CCRANDOM_0_1() * winSz.height;
            break;
        case 2:             // buttom
            position.x = CCRANDOM_0_1() * (winSz.width / 2.f);
            position.x += winSz.width / 2.f;
            position.y = -m_obContentSize.height / 2.f;
            break;
//        case 3:             // left
//            position.x = -m_tContentSize.width / 2.f;
//            position.y = CCRANDOM_0_1() * winSz.height;
//            break;
        default:
            break;
    }

    // for debug: place monster at a special position
#if 0
    position.x = 200;
    position.y = 100;
#endif
    pMonster->setSpritePosition(position);
}


void CMonsterManager::reset()
{
    m_curLevelIdx = 0;
}
