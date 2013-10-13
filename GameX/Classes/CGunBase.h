//
//  CGunBase.h
//  GameX
//
//  Created by 马 俊 on 13-7-1.
//
//

#ifndef __GameX__CGunBase__
#define __GameX__CGunBase__

#include "Common.h"

#include "CNodeContainer.h"
#include "CObjectBase.h"
#include "CBatchNodeObject.h"

class CRole;

class CGunBase : public CObjectBase, public CBatchNodeObject
{
public:
    virtual ~CGunBase();
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void setOwner(CRole* role);
    virtual void update(float dt);
    virtual void shoot() = 0;
    virtual void clearAll();
    
    virtual bool changeBullet(const std::string& name);
    
    DECLARE_DICTFUNC(CCString*, BulletName);
    DECLARE_DICTFUNC(int, CacheNum);
protected:
    CGunBase();
    void clearThis();
    virtual GameArts getBatchNodeName();
    
    CRole* m_pRole;

    CNodeContainer& getContainer()
    {
        return m_container;
    }
private:
    CNodeContainer m_container;
};


#endif /* defined(__GameX__CGunBase__) */
