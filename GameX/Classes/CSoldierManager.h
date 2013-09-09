//
//  CSoldierManager.h
//  GameX
//
//  Created by 马 俊 on 13-6-13.
//
//

#ifndef __GameX__CSoldierManager__
#define __GameX__CSoldierManager__
#include "CSingleton.h"
#include "CObjectBase.h"
#include "CBatchNodeObject.h"
#include "CNodeContainer.h"

#include <queue>
#include <string>
#include "CSoldierBuildTask.h"

using namespace std;

class CSoldier;

enum SOLDIER_TYPE
{
    SOLDIER_0,
    SOLDIER_TYPE_NUM,
};


class CSoldierManager :public CObjectBase, public CBatchNodeObject, public CSingleton<CSoldierManager>
{
public:
    CSoldierManager();
    virtual ~CSoldierManager();
    
    virtual void clearAll();
    
    virtual bool initialize();
    virtual void update(float dt);
    
    virtual void buildSoldier(int CampNo, const string& soldierName);
    
    virtual CSoldier* getSoldier(SOLDIER_TYPE type);
    
    int getNumOfCamps() {return m_numOfCamps;}
protected:
    void clearThis();
    virtual GameArts getBatchNodeName(){return GA_ACTORS;};
    
    static const char* m_sSoldierNames[SOLDIER_TYPE_NUM];
    static const int m_sSoldierCacheNum[SOLDIER_TYPE_NUM];
    
    virtual void updateSoldierCamps(float dt);
    virtual CSoldier* spawnSoldier(const string& name, const CCPoint& getherPosition);
    virtual CSoldier* spawnSoldier(SOLDIER_TYPE type, const CCPoint& getherPosition);

    
    typedef map<string, SOLDIER_TYPE> MSI;
    typedef map<string, SOLDIER_TYPE>::iterator MSI_IT;
    typedef map<string, SOLDIER_TYPE>::const_iterator MSI_CIT;
    MSI m_SoldierTypeNameTable;
private:
    CNodeContainer* m_pContainers;
    
    typedef queue<CSoldierBuildTask> QS;
    typedef vector<QS> VQS;
    typedef vector<QS>::iterator VQS_IT;
    typedef vector<QS>::const_iterator VQS_CIT;
    
    const int m_numOfCamps;
    VQS m_SoldierCamps;
};


#define SOLDIER_MANAGER     (CSoldierManager::getInstance())

#endif /* defined(__GameX__CSoldierManager__) */
