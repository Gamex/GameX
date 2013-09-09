//
//  CRole
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFRole__
#define __TheForce__TFRole__

#include "cocos2d.h"
#include "CFightingRelationship.h"
#include "CSpriteObject.h"
#include "CGunBase.h"
#include "CMoveOnGridComp.h"


#define ROLE_STATE_IDLE         "Idle"
#define ROLE_STATE_MOVE         "Move"
#define ROLE_STATE_ATTACK        "Attack"

USING_NS_CC;

class CRole : public CSpriteObject, public IFightingRelation, public IMoveOnGridCompCallBack
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CGunBase*, m_pGun, Gun);
    CC_SYNTHESIZE(class CLogicGrid*, m_pGird, Grid);
public:
    FACTORY_CREATE_FUNC(CRole);
    
	virtual ~CRole();

    virtual _FIGHTING_RELATION_TYPE getReationType();
    
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void die();

	virtual CCPoint getShootPoint();
	virtual void update(float dt);
    virtual void clearAll();
    virtual bool createGun(const string& name);
    virtual bool changeBullet(const string& name);
    
    virtual bool attachSpriteTo(CCNode* parent=NULL, int zOrder=0, int tag=-1);
    
    virtual void attack(CRole* pAt);
    virtual CRole* getAttackTarget();
    
    virtual CCPoint getShootDirection();
    
    virtual void setOnGridPos(int x, int y);
    
    DECLARE_DICTFUNC(CCDictionary*, Gun);
protected:
	CRole();
    void clearThis();

    void updateShootPointInWorldSpace();
    
    virtual void onMoveEvent();

	CCPoint m_shootPoint;
    CCPoint m_shootPointInWorldSpace;

private:
};

#endif /* defined(__TheForce__TFRole__) */
