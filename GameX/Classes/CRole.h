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
#include "CBackgroundManager.h"

#define ROLE_FACE_TO_LEFT_PREFIX        "FL_"
#define ROLE_FACE_TO_RIGHT_PREFIX       "FR_"
#define ROLE_BACK_TO_LEFT_PREFIX        "BL_"
#define ROLE_BACK_TO_RIGHT_PREFIX       "BR_"

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
    FACE_TO_LEFT_DOWN,
    FACE_TO_RIGHT_DOWN,
    FACE_TO_LEFT_UP,
    FACE_TO_RIGHT_UP,
    FACE_TO_MAX,
};

class CRole
: public CSpriteObject
, public IFightingRelation
, public IGridRole
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CGunBase*, m_pGun, Gun);
    CC_SYNTHESIZE(FACE_TO, m_faceTo, FaceTo);
    CC_SYNTHESIZE_PASS_BY_REF(string, m_unitName, UnitName);
public:
    FACTORY_CREATE_FUNC(CRole);
    
	virtual ~CRole();

    virtual _FIGHTING_RELATION_TYPE getRelationType();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual bool changeState(int state);
    virtual bool attachSpriteTo(CCNode* parent, int zOrder = 0, int tag = -1);
    
    virtual void die();

	virtual CCPoint getShootPoint();
	virtual void update(float dt);
    virtual void clearAll();
    virtual bool createGun(const string& name);
    virtual bool changeBullet(const string& name);

    virtual void attack(CRole* pAt);
    virtual CRole* getAttackTarget();
    
    virtual CCPoint getShootDirection();
    
    virtual void updateVertexZ();
    virtual void onPlaceOnMap(const CCPoint& gridPos, const CCPoint& position);
    virtual void findPath(const CCPoint& startPos, const CCPoint& targetPos, IPathFinderDelegate* delegate = NULL);
    
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

    vector<string> m_faceToPrefix;
private:
};

#endif /* defined(__TheForce__TFRole__) */
