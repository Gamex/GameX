//
//  CFightingRelationship.h
//  GameX
//
//  Created by 马 俊 on 13-7-24.
//
//

#ifndef __GameX__CFightingRelationship__
#define __GameX__CFightingRelationship__

#include "CSingleton.h"
#include "Common.h"

class IFightingRelation;


class IFightingRelation
{
    friend class CFightingRelationship;
public:
    enum _FIGHTING_RELATION_TYPE
    {
        RELATION_1v1,
        RELATION_1vN,
        RELATION_Nv1,
    };
    
    IFightingRelation(){}
    virtual ~IFightingRelation(){}
    
    virtual _FIGHTING_RELATION_TYPE getRelationType()=0;
private:
    int m_aggro;
    VR_IT m_fightingRelationIterator;
};


//受暴者:victim
//施暴者:villain

class CFightingRelationship : public CSingleton<CFightingRelationship>
{
public:
    CFightingRelationship();
    virtual ~CFightingRelationship();
    
    virtual void update(float dt);
    
    virtual void add(IFightingRelation* villain, IFightingRelation* victim);
    virtual void removeAllRelation(IFightingRelation* role);
    virtual void removeAllVictims(IFightingRelation* role);
    virtual void removeAllVillains(IFightingRelation* role);
    
    virtual IFightingRelation* getFirstVictim(IFightingRelation* role);
    virtual IFightingRelation* getNextVictim(IFightingRelation* role, IFightingRelation* preVictim);
    virtual IFightingRelation* getFirstVillain(IFightingRelation* role);
    virtual IFightingRelation* getNextVillain(IFightingRelation* role, IFightingRelation* preVillain);
protected:
    void removeObjFrom(MRVR& mrvr, IFightingRelation* key, IFightingRelation* toBeDel);
    
    MRVR m_villains;
    MRVR m_victims;

private:
};


#define FIGHT_RELATION (CFightingRelationship::getInstance())


#endif /* defined(__GameX__CFightingRelationship__) */
