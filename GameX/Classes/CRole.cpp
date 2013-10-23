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
#include "CBattleFiledManager.h"
#include "CDataCenterManager.h"
#include "CWarriorDyingComp.h"

DEFINE_DICTFUNC_DICTIONARY(CRole, Gun);


CRole::CRole()
: m_pGun(NULL)
, m_faceTo(FACE_TO_RIGHT_DOWN)
, m_roleGroup(ROLE_GROUP_NA)
#ifdef DEBUG
, m_mark(false)
#endif
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

    enableAlphaTest(0.5);
    
    changeState(ROLE_STATE_MOVE);

	return true;
}



void CRole::loadRoleData(const string& unitName)
{
    setUnitName(unitName);
    
    CCDictionary* dict = DTUNIT->getData(unitName);
    setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
    setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());

    setSpeed(DTUNIT->get_speed_Value(dict)->floatValue());
    setMaxHP(DTUNIT->get_hp_Value(dict)->floatValue());
    setCurHP(getMaxHP());
    setATK(DTUNIT->get_atk_Value(dict)->floatValue());
    setDEF(DTUNIT->get_def_Value(dict)->floatValue());
    setAtkSpeed(DTUNIT->get_rate_Value(dict)->floatValue());
}




void CRole::addComponentsForStates()
{
    CMoveOnGridComp* moveComp = CMoveOnGridComp::create();
    addComponentForState(ROLE_STATE_MOVE, moveComp);
    
    CWarriorDyingComp* dyingComp = CWarriorDyingComp::create();
    addComponentForState(ROLE_STATE_DYING, dyingComp);
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



bool CRole::createGun(const std::string& name)
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




bool CRole::changeBullet(const std::string& name)
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



void CRole::setRoleGroup(ROLE_GROUP var)
{
    BF_MANAGER->removeRole(this);
    m_roleGroup = var;
    BF_MANAGER->addRole(this);
}



ROLE_GROUP CRole::getRoleGroup()
{
    return m_roleGroup;
}



void CRole::die()
{
    CBackgroundManager* bkg = getBackGround();
    if (bkg)
    {
        bkg->removeRoleFromGrid(this);
    }
    BF_MANAGER->removeRole(this);
    FIGHT_RELATION->removeAllRelation(dynamic_cast<IFightingRelation*>(this));
    CSpriteObject::die();
    
    setSpriteVisible(false);
}



void CRole::revive()
{
    CSpriteObject::revive();
    BF_MANAGER->addRole(this);
}


void CRole::onPlaceOnMap(const CCPoint& gridPos, const CCPoint& position)
{
    setSpritePosition(position);
}



void CRole::updateVertexZ()
{
    do
    {
        CBackgroundManager* bkg = getBackGround();
        BREAK_IF(NULL == bkg);
        CCTMXTiledMap* map = bkg->getTiledMap();
        BREAK_IF(NULL == map);
        const CCSize& szMap = map->getMapSize();
        float lowestZ = -(szMap.width + szMap.height);

        const CCPoint& tilePos = getLogicGrid()->getGridPos();
        float currentZ = tilePos.x + tilePos.y;
        
        
        setSpriteVertexZ(lowestZ + currentZ - 1);
        
//        setSpriteZOrder(lowestZ + currentZ - 1);
    } while (false);
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



bool CRole::playAnimation(const std::string& name)
{
    std::string s = m_faceToPrefix[m_faceTo];
    s += name;

    return CSpriteObject::playAnimation(s);
}



bool CRole::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    do
    {
        BREAK_IF(!CSpriteObject::attachSpriteTo(parent, zOrder, tag));
        updateVertexZ();
        
        return true;
    } while (false);
	return false;
}



void CRole::findPath(const CCPoint& startPos, const CCPoint& targetPos, IPathFinderDelegate* delegate)
{
    CBackgroundManager* bkg = getBackGround();
    CC_ASSERT(bkg);
    bkg->findPath(startPos, targetPos, this, delegate);
}



bool CRole::findPathBrief(const CCPoint& startPos, const CCPoint& targetPos, vector<CCPoint>& path)
{
    path.clear();
    CCPoint pt = startPos;
    CCPoint diff = targetPos - startPos;
    int xSign = FLT_GE(diff.x, 0) ? 1 : -1;
    int ySign = FLT_GE(diff.y, 0) ? 1 : -1;
    diff.x = fabsf(diff.x);
    diff.y = fabsf(diff.y);
    
    int delta = diff.x - diff.y;
    
    while (!pt.equals(targetPos))
    {
        path.push_back(pt);
        
        if (delta > 0)
        {
            pt.x += xSign;
            delta--;
        }
        else if (delta < 0)
        {
            pt.y += ySign;
            delta++;
        }
        else
        {
            pt.x += xSign;
            pt.y += ySign;
        }
    }
    std::reverse(path.begin(), path.end());
	return true;
}





void CRole::think()
{
}



void CRole::setFaceTo(CRole* role)
{
    do
    {
        CC_ASSERT(role);
        CBackgroundManager* bkg = getBackGround();
        CC_ASSERT(bkg);
        CLogicGrid* l1 = getLogicGrid();
        CLogicGrid* l2 = role->getLogicGrid();
        BREAK_IF(l1 == NULL || l2 == NULL);
        CCPoint p1 = l1->getGridPos();
        CCPoint p2 = l2->getGridPos();
        p1 = bkg->gridToWorldPoint(p1);
        p2 = bkg->gridToWorldPoint(p2);
        FACE_TO ft;

        if (p2.x > p1.x)
        {
            if (p2.y > p1.y)
            {
                ft = FACE_TO_RIGHT_UP;
            }
            else
            {
                ft = FACE_TO_RIGHT_DOWN;
            }
        }
        else
        {
            if (p2.y > p1.y)
            {
                ft = FACE_TO_LEFT_UP;
            }
            else
            {
                ft = FACE_TO_LEFT_DOWN;
            }
        }
        
        setFaceTo(ft);
    } while (false);
    
    return;
}



float CRole::getDistanceSqInGrid(IGridRole* role)
{
    CCPoint p1 = getPositionInGrid();
    CCPoint p2 = role->getPositionInGrid();
    
    int i,j,m,n;
    float smallest = FLT_MAX;
    
    for (i = 0; i < getGridWidth(); ++i)
    {
        for (j = 0; j < getGridHeight(); ++j)
        {
            CCPoint pos1(p1.x + i, p1.y + j);
            for (m = 0; m < role->getGridWidth(); ++m)
            {
                for (n = 0; n < role->getGridHeight(); ++n)
                {
                    CCPoint pos2(p2.x + m, p2.y + n);
                    float dist = pos1.getDistanceSq(pos2);
                    if (dist < smallest)
                    {
//                        CCLOG("(%f,%f --> %f, %f) %f", pos1.x, pos1.y, pos2.x, pos2.y, dist);
                        smallest = dist;
                    }
                }
            }
        }
    }
    
	return smallest;
}



bool CRole::checkInGridRadiusSq(IGridRole* role, float radiusInGrid)
{
	return FLT_LE(getDistanceSqInGrid(role), radiusInGrid);
}



CCPoint CRole::getPositionInGrid()
{
    CLogicGrid* lg = getLogicGrid();
    
    return lg->getGridPos();
    
    int w = getGridWidth();
    int h = getGridHeight();
    
    CCPoint pos = lg->getGridPos();
    pos.x += (w - 1) * 0.5f;
    pos.y += (h - 1) * 0.5f;
    
    return pos;
}

