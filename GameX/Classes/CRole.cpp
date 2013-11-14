//
//  CRole.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//
#include "CRole.h"
#include "CBackgroundManager.h"
#include "CMoveOnGridComp.h"
#include "CBattleFiledManager.h"
#include "CDataCenterManager.h"
#include "CWarriorDyingComp.h"
#include "CHPBar.h"


#define TAG_HUD_HPBAR   1000


CRole::CRole()
: m_faceTo(FACE_TO_RIGHT_DOWN)
, m_roleGroup(ROLE_GROUP_NA)
#ifdef DEBUG
, m_mark(false)
#endif
, m_pHPBar(nullptr)
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



void CRole::setInnerSprite(Sprite* var)
{
    CSpriteObject::setInnerSprite(var);
    if (var)
    {
        _enableAlphaTestR(var, 0.5f);
    }
}


bool CRole::init(const string& unitId, bool editorMode)
{
    do
    {
        BREAK_IF(!CSpriteObject::init());
        
        m_faceToPrefix.resize(FACE_TO_MAX);
        m_faceToPrefix[FACE_TO_LEFT_DOWN] = ROLE_FACE_TO_LEFT_PREFIX;
        m_faceToPrefix[FACE_TO_RIGHT_DOWN] = ROLE_FACE_TO_RIGHT_PREFIX;
        m_faceToPrefix[FACE_TO_LEFT_UP] = ROLE_BACK_TO_LEFT_PREFIX;
        m_faceToPrefix[FACE_TO_RIGHT_UP] = ROLE_BACK_TO_RIGHT_PREFIX;

        
        changeState(ROLE_STATE_MOVE);

        setUnitId(unitId);
        
        Dictionary* dict = DTUNIT->getData(unitId);
        setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
        setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());
        
        setSpeed(DTUNIT->get_speed_Value(dict)->floatValue());
        setMaxHP(DTUNIT->get_hp_Value(dict)->floatValue());
        setCurHP(getMaxHP());
        setATK(DTUNIT->get_atk_Value(dict)->floatValue());
        setDEF(DTUNIT->get_def_Value(dict)->floatValue());
        setAtkSpeed(DTUNIT->get_rate_Value(dict)->floatValue());
        
        BREAK_IF_FAILED(CSpriteObject::setSpriteFromCcbi(DTUNIT->get_resourceID_Value(dict)->getCString()));
        
        if (!editorMode)
        {
            BREAK_IF_FAILED(createHPBar());
            m_pHPBar->setPercentage(1.f);
            Size sz = getSpriteContentSize();
            m_pHPBar->setPosition(0, sz.height);
        }
        return true;
    } while (false);
    
    return false;
}



void CRole::addCCBAnimationDelegate(ICCBAnimationDelegate* delegate)
{
    m_ccbAnimatonDelegates.insert(delegate);
}



bool CRole::init()
{
    CCAssert(false, "Use --> CRole::init(const string& unitId) <-- instead");
    return false;
}




void CRole::addComponentsForStates()
{
    CMoveOnGridComp* moveComp = CMoveOnGridComp::create();
    addComponentForState(ROLE_STATE_MOVE, moveComp);
    
    CWarriorDyingComp* dyingComp = CWarriorDyingComp::create();
    addComponentForState(ROLE_STATE_DYING, dyingComp);
}



void CRole::update(float dt)
{
    CSpriteObject::update(dt);
}



void CRole::clearAll()
{
    CSpriteObject::clearAll();
    
    clearThis();
}



void CRole::clearThis()
{
    setHPBar(nullptr);
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
    
    
    if (m_pHPBar != nullptr)
    {
        m_pHPBar->setSpriteVisible(false);
    }
}



void CRole::revive()
{
    CSpriteObject::revive();
    BF_MANAGER->addRole(this);
    
    if (m_pHPBar != nullptr)
    {
        m_pHPBar->setSpriteVisible(true);
    }
}


bool CRole::isDying()
{
    return getCurrentState() == ROLE_STATE_DYING;
}


void CRole::onPlaceOnMap(const Point& gridPos, const Point& position)
{
    setSpritePosition(position);
}



void CRole::updateVertexZ()
{
    do
    {
        CBackgroundManager* bkg = getBackGround();
        BREAK_IF(nullptr == bkg);
        TMXTiledMap* map = bkg->getTiledMap();
        BREAK_IF(nullptr == map);
        const Size& szMap = map->getMapSize();
        float lowestZ = -(szMap.width + szMap.height);

        const Point& tilePos = getLogicGrid()->getGridPos();
        float currentZ = tilePos.x + tilePos.y;
        
        
        setSpriteVertexZ(lowestZ + currentZ - 1);
        
//        setSpriteZOrder(lowestZ + currentZ - 1);
    } while (false);
}




bool CRole::changeState(int state)
{    
	return CSpriteObject::changeState(state);
}



void CRole::setMoveTarget(const Point& gridPos)
{
    m_moveTarget = gridPos;
}



const Point& CRole::getMovetarget()
{
    return m_moveTarget;
}



bool CRole::playAnimation(const std::string& name)
{
    std::string s = m_faceToPrefix[m_faceTo];
    s += name;

    return CSpriteObject::playAnimation(s);
}



bool CRole::attachSpriteTo(Node* parent, int zOrder, int tag)
{
    do
    {
        BREAK_IF(!CSpriteObject::attachSpriteTo(parent, zOrder, tag));
        updateVertexZ();
        
        
        if (m_pHPBar)
        {
            m_pHPBar->attachSpriteTo(parent, zOrder);
        }
        return true;
    } while (false);
	return false;
}



void CRole::findPath(const Point& startPos, const Point& targetPos, IPathFinderDelegate* delegate)
{
    CBackgroundManager* bkg = getBackGround();
    CC_ASSERT(bkg);
    bkg->findPath(startPos, targetPos, this, delegate);
}



bool CRole::findPathBrief(const Point& startPos, const Point& targetPos, vector<Point>& path)
{
    path.clear();
    Point pt = startPos;
    Point diff = targetPos - startPos;
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
        BREAK_IF(l1 == nullptr || l2 == nullptr);
        Point p1 = l1->getGridPos();
        Point p2 = l2->getGridPos();
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
    Point p1 = getPositionInGrid();
    Point p2 = role->getPositionInGrid();
    
    int i,j,m,n;
    float smallest = FLT_MAX;
    
    for (i = 0; i < getGridWidth(); ++i)
    {
        for (j = 0; j < getGridHeight(); ++j)
        {
            Point pos1(p1.x + i, p1.y + j);
            for (m = 0; m < role->getGridWidth(); ++m)
            {
                for (n = 0; n < role->getGridHeight(); ++n)
                {
                    Point pos2(p2.x + m, p2.y + n);
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



Point CRole::getPositionInGrid()
{
    CLogicGrid* lg = getLogicGrid();
    
    return lg->getGridPos();
    
    int w = getGridWidth();
    int h = getGridHeight();
    
    Point pos = lg->getGridPos();
    pos.x += (w - 1) * 0.5f;
    pos.y += (h - 1) * 0.5f;
    
    return pos;
}



void CRole::damage(float damagePoint, CRole* attacker)
{
    float curHP = getCurHP();
    curHP = curHP - damagePoint;
    if (FLT_LE(curHP, 0.f))
    {
        setCurHP(0.f);
        FIGHT_RELATION->removeAllRelation(dynamic_cast<IFightingRelation*>(this));
        changeState(ROLE_STATE_DYING);
    }
    else
    {
        setCurHP(curHP);
        
        if (attacker)
        {
            if (getMovetarget().equals(Point(-1.f, -1.f)))
            {
                setMoveTarget(attacker->getLogicGrid()->getGridPos());
            }
        }
    }
    
    m_pHPBar->setPercentage(getCurHP() / getMaxHP());
    
    BF_MANAGER->wakeUpAllDefender();
}



bool CRole::createHPBar()
{
    do
    {
        setHPBar((CHPBar*)(OBJECT_FACTORY->createInstance("CHPBar")));
        BREAK_IF_FAILED(getHPBar());

        BREAK_IF_FAILED(m_pHPBar->init("huds/hp_bar_fg0.png", "huds/hp_bar_bg0.png"));
        float w = m_pHPBar->getSpriteContentSize().width;
        m_pHPBar->setSpritePosition(Point(w / 2.f + 2.f, 0));
        addSlot(m_pHPBar, TAG_HUD_HPBAR);
//        addChild(m_pHPBar);
//        m_pHPBar->attachSpriteTo(getInnerSprite());

        return true;
    } while (false);
    
    return false;
}
