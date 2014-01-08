//
//  CRole
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFRole__
#define __TheForce__TFRole__

#include "Common.h"
#include "CFightingRelationship.h"
#include "CSpriteObject.h"
#include "CBackgroundManager.h"
#include "ICCBAnimationDelegate.h"
#include "CHPBar.h"

#define ROLE_FACE_TO_LEFT_PREFIX        "FL_"
#define ROLE_FACE_TO_RIGHT_PREFIX       "FR_"
#define ROLE_BACK_TO_LEFT_PREFIX        "BL_"
#define ROLE_BACK_TO_RIGHT_PREFIX       "BR_"

#define ROLE_ANIMATION_IDLE         "Idle"
#define ROLE_ANIMATION_MOVE         "Move"
#define ROLE_ANIMATION_ATTACK       "Attack"
#define ROLE_ANIMATION_DYING        "Dying"
#define ROLE_ANIMATION_SELECTED     "Selected"

enum ROLE_STATE
{
    ROLE_STATE_MOVE,
    ROLE_STATE_DYING,
    ROLE_STATE_MAX,
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


enum ROLE_GROUP
{
    ROLE_GROUP_NA,
    ROLE_GROUP_ATTACK,
    ROLE_GROUP_DEFENCE,
    ROLE_GROUP_MAX,
};


class CRole
: public CSpriteObject
, public IFightingRelation
, public IGridRole
{
    friend class CObjectBase;
    
    CC_SYNTHESIZE_RETAIN(CHPBar*, m_pHPBar, HPBar);
    CC_SYNTHESIZE(FACE_TO, m_faceTo, FaceTo);
    CC_SYNTHESIZE_PASS_BY_REF(string, m_unitId, UnitId);
    CC_PROPERTY(ROLE_GROUP, m_roleGroup, RoleGroup);
    CC_SYNTHESIZE(float, m_speed, Speed);
    CC_SYNTHESIZE(float, m_maxHP, MaxHP);
    CC_SYNTHESIZE(float, m_curHP, CurHP);
    CC_SYNTHESIZE(float, m_ATK, ATK);
//    CC_SYNTHESIZE(float, m_DEF, DEF);
    CC_SYNTHESIZE(float, m_AtkSpeed, AtkSpeed);
#if DEBUG
    CC_SYNTHESIZE(bool, m_mark, Mark);
#endif
public:
    FACTORY_CREATE_FUNC(CRole);
    
	virtual ~CRole();

    virtual _FIGHTING_RELATION_TYPE getRelationType();
    
    virtual bool init(const string& unitId, bool editorMode = false);
    virtual bool init();
    virtual bool changeState(int state);
    virtual bool attachSpriteTo(Node* parent, int zOrder = 0, int tag = -1);
    
    virtual void die();
    virtual void revive();
    virtual bool isDying();
    
	virtual void update(float dt);
    virtual void clearAll();


    virtual void attack(CRole* pAt);
    virtual CRole* getAttackTarget();

    
    virtual bool createHPBar();
    
    virtual void updateVertexZ();
    virtual void onPlaceOnMap(const Point& gridPos, const Point& position);
    virtual void findPath(const Point& startPos, const Point& targetPos, IPathFinderDelegate* delegate = nullptr);
    virtual bool findPathBrief(const Point& startPos, const Point& targetPos, vector<Point>& path);
    
    virtual bool playAnimation(const std::string& name);
    
    virtual void setMoveTarget(const Point& gridPos);
    virtual const Point& getMovetarget();
    
    virtual void think();
    
    virtual void setFaceTo(CRole* role);
    
    virtual Point getPositionInGrid();
    virtual float getDistanceSqInGrid(IGridRole* role);
    virtual bool checkInGridRadiusSq(IGridRole* role, float radiusInGrid);

    virtual void addCCBAnimationDelegate(ICCBAnimationDelegate* delegate);

    virtual void damage(float damagePoint, CRole* attacker);     // damagePoint should be a positive value and this value while be minue from CurHp
    virtual void enterBattleState(){}
protected:
	CRole();
    void clearThis();
    
    virtual void setInnerSprite(Sprite* var);
    virtual void addComponentsForStates();

    VS m_faceToPrefix;
    SAD m_ccbAnimatonDelegates;
    
    bool m_isEditMode = true;
private:
};

#endif /* defined(__TheForce__TFRole__) */
