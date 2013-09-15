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

#define ROLE_FACE_TO_LEFT_PREFIX    "FL_"
#define ROLE_FACE_TO_RIGHT_PREFIX    "FR_"

#define ROLE_ANIMATION_IDLE         "Idle"
#define ROLE_ANIMATION_MOVE         "Move"
#define ROLE_ANIMATION_ATTACK       "Attack"

enum ROLE_STATE
{
    ROLE_STATE_MOVE,
    ROLE_STATE_ATTACK,
};

USING_NS_CC;

enum FACE_TO
{
    FACE_TO_LEFT,
    FACE_TO_RIGHT,
    FACE_TO_MAX,
};

class CRole : public CSpriteObject, public IFightingRelation
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CGunBase*, m_pGun, Gun);
    CC_SYNTHESIZE(class CLogicGrid*, m_pGird, Grid);
    CC_SYNTHESIZE(FACE_TO, m_faceTo, FaceTo);
public:
    FACTORY_CREATE_FUNC(CRole);
    
	virtual ~CRole();

    virtual _FIGHTING_RELATION_TYPE getRelationType();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual bool changeState(int state);
    
    virtual void die();

	virtual CCPoint getShootPoint();
	virtual void update(float dt);
    virtual void clearAll();
    virtual bool createGun(const string& name);
    virtual bool changeBullet(const string& name);

    virtual void attack(CRole* pAt);
    virtual CRole* getAttackTarget();
    
    virtual CCPoint getShootDirection();
    
    virtual void placeOnGridPos(const CCPoint& gridPos);
    
    virtual bool playAnimation(const string& name);
    
    virtual void setMoveTarget(const CCPoint& gridPos);
    virtual const CCPoint& getMovetarget();
    
    DECLARE_DICTFUNC(CCDictionary*, Gun);
protected:
	CRole();
    void clearThis();

    void updateShootPointInWorldSpace();
    
    virtual void addComponentsForStates();


	CCPoint m_shootPoint;
    CCPoint m_shootPointInWorldSpace;
    
    CCPoint m_moveTarget;

    vector<string> m_faceToPrefix;
private:
};

#endif /* defined(__TheForce__TFRole__) */
