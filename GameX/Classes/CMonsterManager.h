//
//  CMonsterManager.h
//  GameX
//
//  Created by 马 俊 on 13-6-8.
//
//

#ifndef __GameX__CMonsterManager__
#define __GameX__CMonsterManager__

#include "CSingleton.h"
#include "CObjectBase.h"
#include "CBatchNodeObject.h"
#include "CNodeContainer.h"
#include "CMemPool.h"
#include <vector>

using namespace std;

enum MONSTER_TYPE
{
    MONSTER_0,
//    MONSTER_1,
//    MONSTER_2,
    
    MONSTER_TYPE_NUM,
};

class CMonster;

#define MONSTER_SPAWN_INFO_MEM_POOL_SIZE        100

class CMonsterSpawnInfo
{
public:
    float countDown;
    CCPoint position;
    string monsterId;
    string firstTarget;
    string secondTarget;
    
    MEM_POOL_DECLARE(CMonsterSpawnInfo, MONSTER_SPAWN_INFO_MEM_POOL_SIZE);
};


class CMonsterManager :public CObjectBase, public CBatchNodeObject, public CSingleton<CMonsterManager>
{
public:
    CMonsterManager();
    virtual ~CMonsterManager();
    
    virtual void clearAll();
    
    virtual bool initialize();
    virtual void update(float dt);
    
    void spawnMonster(CMonsterSpawnInfo* info);
    
    void reset();
protected:
    void clearThis();
    virtual GameArts getBatchNodeName(){return GA_ACTORS;};

    static const char* m_sMonsterNames[MONSTER_TYPE_NUM];
    static const int m_sMonsterCacheNum[MONSTER_TYPE_NUM];
    
    void spawnMonsterOnTimer(float dt);
    void setMonsterSpawnPosition(CMonster* pMonster);
    
    typedef map<string, MONSTER_TYPE> MSI;
    typedef map<string, MONSTER_TYPE>::iterator MSI_IT;
    typedef map<string, MONSTER_TYPE>::const_iterator MSI_CIT;
    MSI m_monsterTypeNameTable;
private:
    typedef vector<CMonsterSpawnInfo*> VMSI;
    typedef vector<CMonsterSpawnInfo*>::iterator VMSI_IT;
    typedef vector<CMonsterSpawnInfo*>::const_iterator VMSI_CIT;
    
    CNodeContainer* m_pContainers;
    float m_lastMonsterSpawnedTime;
    float m_timeLine;
    
    int m_curLevelIdx;
    
    VMSI m_spawnInfo;
};


#define MONSTER_MANAGER     (CMonsterManager::getInstance())

#endif /* defined(__GameX__CMonsterManager__) */
