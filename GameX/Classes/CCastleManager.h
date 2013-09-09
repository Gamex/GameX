//
//  CCastleManager.h
//  GameX
//
//  Created by 马 俊 on 13-6-10.
//
//

#ifndef __GameX__CCastleManager__
#define __GameX__CCastleManager__

#include "CSingleton.h"
#include "CObjectBase.h"
#include "CBatchNodeObject.h"
#include "CNodeContainer.h"
#include "CTower.h"

class CArchersGun;
class CRole;

enum CASTLE_ITEM_TYPE
{
    CIT_BASE_UNIT,
    CIT_GUARD_UNIT,
    
    CASTLE_ITEM_NUM,
};

#define GUARD_UNIT_NUM       5



class CCastleManager :public CObjectBase, public CBatchNodeObject, public CSingleton<CCastleManager>
{
public:
    CCastleManager();
    virtual ~CCastleManager();
    
    virtual void clearAll();
    
    virtual bool initialize();
    virtual void update(float dt);
    
    virtual bool spawnAll();
    virtual void setBaseGunAimTarget(const CCPoint& target);
    virtual void triggerBaseGunSkill();
protected:
    void clearThis();
    virtual GameArts getBatchNodeName(){return GA_ACTORS;};
    
    static const char* m_sCastleNames[CASTLE_ITEM_NUM];
    static const int m_sCastleCacheNum[CASTLE_ITEM_NUM];

    typedef map<string, int> MSI;
    typedef map<string, int>::iterator MSI_IT;
    typedef map<string, int>::const_iterator MSI_CIT;
    MSI m_castleTypeNameTable;
private:
    CNodeContainer* m_pContainers;
    
    CArchersGun* m_pBaseUnit;
    CArchersGun* m_pGuardUnit[GUARD_UNIT_NUM];
};


#define CASTLE_MANAGER     (CCastleManager::getInstance())


#endif /* defined(__GameX__CCastleManager__) */
