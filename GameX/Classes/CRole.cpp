//
//  CRole.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//
#include "CRole.h"
#include "CBulletBase.h"
#include "TFGameObjectManager.h"
#include "CBackgroundManager.h"
#include "CMoveOnGridComp.h"

DEFINE_DICTFUNC_DICTIONARY(CRole, Gun);


CRole::CRole()
: m_pGun(NULL)
, m_faceTo(FACE_TO_RIGHT_DOWN)
{

}



CRole::~CRole()
{
    clearThis();
}



IFightingRelation::_FIGHTING_RELATION_TYPE CRole::getRelationType()
{
    return RELATION_1v1;
}


bool CRole::init(CCDictionary* pObjectDict)
{
    if (!CSpriteObject::init(pObjectDict))
    {
        return false;
    }
    
    m_faceToPrefix.resize(FACE_TO_MAX);
    m_faceToPrefix[FACE_TO_LEFT_DOWN] = ROLE_FACE_TO_LEFT_PREFIX;
    m_faceToPrefix[FACE_TO_RIGHT_DOWN] = ROLE_FACE_TO_RIGHT_PREFIX;
    m_faceToPrefix[FACE_TO_LEFT_UP] = ROLE_BACK_TO_LEFT_PREFIX;
    m_faceToPrefix[FACE_TO_RIGHT_UP] = ROLE_BACK_TO_RIGHT_PREFIX;

    CCDictionary* pGunDict = getGunFromDict();
    if (NULL != pGunDict )
    {
        CCString* str = dynamic_cast<CCString*>(pGunDict->objectForKey("ShootPoint"));
        if (NULL == str)
        {
            __CCLOGWITHFUNCTION("ShootPoint not found in Gun of GameObject: %s", getNameFromDict()->getCString());
            return false;
        }
        m_shootPoint = CCPointFromString(str->getCString());
        
        str = dynamic_cast<CCString*>(pGunDict->objectForKey("GunName"));
        if (NULL == str)
        {
            __CCLOGWITHFUNCTION("GunName not found in Gun of GameObject: %s", getNameFromDict()->getCString());
            return false;
        }
        
        if (!createGun(str->getCString()))
        {
            __CCLOGWITHFUNCTION("create default gun failed");
            return false;
        }
    }
    
	return true;
}



void CRole::addComponentsForStates()
{
    CMoveOnGridComp* moveComp = CMoveOnGridComp::create();
    addComponent(moveComp);
    addComponentForState(ROLE_STATE_MOVE, moveComp->getName());
}



CCPoint CRole::getShootPoint()
{
//    return ccpAdd(getSpritePosition(), m_shootPoint);
    return m_shootPointInWorldSpace;
}



void CRole::update(float dt)
{
    CSpriteObject::update(dt);
    updateShootPointInWorldSpace();
}



void CRole::clearAll()
{
    CSpriteObject::clearAll();
    
    clearThis();
}



void CRole::clearThis()
{
    if (m_pGun)
    {
        m_pGun->clearAll();
        setGun(NULL);
    }
}



bool CRole::createGun(const string& name)
{
    if (NULL != getGun())
    {
        m_pGun->removeFromParentAndCleanup(true);
        m_pGun->clearAll();
        setGun(NULL);
    }
    
    setGun(dynamic_cast<CGunBase*>(CObjectBase::createObject(name)));
    if (NULL == getGun())
    {
        return false;
    }
    m_pGun->setOwner(this);
    addChild(m_pGun);
    
    return true;
}




bool CRole::changeBullet(const string& name)
{
    if (NULL == m_pGun)
    {
        return false;
    }
    
    return m_pGun->changeBullet(name);
}



void CRole::updateShootPointInWorldSpace()
{
    CCNode* pSpr = getInnerSprite();
    if (NULL != pSpr && NULL != pSpr->getParent())
    {
        m_shootPointInWorldSpace = pSpr->getParent()->convertToWorldSpace(ccpAdd(getSpritePosition(), m_shootPoint));
    }
}


CCPoint CRole::getShootDirection()
{
    return CCPoint(0.f, 1.f);
}



void CRole::attack(CRole* pAt)
{
    FIGHT_RELATION->add(dynamic_cast<IFightingRelation*>(this), dynamic_cast<IFightingRelation*>(pAt));
}



CRole* CRole::getAttackTarget()
{
    IFightingRelation* fr = FIGHT_RELATION->getFirstVictim(dynamic_cast<IFightingRelation*>(this));
    return dynamic_cast<CRole*>(fr);
}



void CRole::die()
{
    FIGHT_RELATION->removeAllRelation(dynamic_cast<IFightingRelation*>(this));
    CSpriteObject::die();
}



bool CRole::placeOnGridPos(const CCPoint& gridPos, bool syncTargetPos)
{
    do
    {
        BREAK_IF(!BKG_MANAGER->isRoleCanBePlacedOnPos(this, gridPos));
        
        BKG_MANAGER->removeRoleFromGrid(this);
        BKG_MANAGER->addRoleToGrid(gridPos, this);
        
        CLogicGrid* grid = getLogicGrid();
        CC_ASSERT(grid);
        const CCPoint& gridPos = grid->getGridPos();
        if (syncTargetPos)
        {
            m_moveTarget = gridPos;
        }
        CCPoint pt = BKG_MANAGER->gridToWorldPoint(gridPos);

        setSpritePosition(pt);

        return true;
    } while (false);
    
    return false;
}



void CRole::updateVertexZ()
{
    CCTMXTiledMap* map = BKG_MANAGER->getTiledMap();
    const CCSize& szMap = map->getMapSize();
    float lowestZ = -(szMap.width + szMap.height);
    
    const CCPoint& tilePos = getLogicGrid()->getGridPos();
    float currentZ = tilePos.x + tilePos.y;
    
    setSpriteVertexZ(lowestZ + currentZ - 1);
}



bool CRole::changeState(int state)
{    
	return CSpriteObject::changeState(state);
}



void CRole::setMoveTarget(const CCPoint& gridPos)
{
    m_moveTarget = gridPos;
}



const CCPoint& CRole::getMovetarget()
{
    return m_moveTarget;
}



bool CRole::playAnimation(const string& name)
{
    string s = m_faceToPrefix[m_faceTo];
    s += name;
    
    return CSpriteObject::playAnimation(s);
}




