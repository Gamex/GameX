//
//  CBackgroundManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-26.
//
//

#include "CBackgroundManager.h"
#include "Common.h"
#include "CBatchNodeManager.h"
#include "CSpriteObject.h"
#include "CRole.h"

#define BKG_BATCH_NODE_NAME     "bn_scene"

#define LOGIC_WIDTH             15
#define LOGIC_HEIGHT            10
#define GRID_WIDTH_SIZE         ((int)D_TO_A(32))
#define GRID_HEIGHT_SIZE        ((int)D_TO_A(32))


IMPLEMENT_SINGLETON(CBackgroundManager);


CBackgroundManager::CBackgroundManager()
: m_pBkg(NULL)
{
    
}



CBackgroundManager::~CBackgroundManager()
{
    if (m_pBkg)
    {
        m_pBkg->removeFromParentAndCleanup(true);
        setBkg(NULL);
    }
}



bool CBackgroundManager::initialize()
{
    do
    {
        m_widthInGrid = LOGIC_WIDTH;
        m_heightInGrid = LOGIC_HEIGHT;
        
        m_grids.clear();
        m_grids.reserve(LOGIC_WIDTH * LOGIC_HEIGHT);
        
        
        for (int y = 0; y < LOGIC_HEIGHT; ++y)
        {
            for (int x = 0 ; x < LOGIC_WIDTH; ++x)
            {
                CSpriteObject* so = dynamic_cast<CSpriteObject*>(CObjectBase::createObject("BackgroundGrid"));
                so->attachSpriteTo();
                so->setSpritePosition(gridToPoint(CCPoint(x, y)));
                m_grids.push_back(CLogicGrid(x, y));
                m_grids.back().setGridBkg(so);
            }
        }
        
        
        return true;
    } while (false);
    
    return false;
}



//bool CBackgroundManager::attachBkgTo(CCNode* parent, int zOrder, int tag)
//{
//    do
//    {
//        if (!parent)
//        {
//            bool isBatchNode;
//            parent = BATCH_NODE_MANAGER->getNodeByName(BKG_BATCH_NODE_NAME, isBatchNode);
//        }
//        CC_ASSERT(parent);
//        
//        parent->addChild(m_pBkg, zOrder, tag);
//        
//        return true;
//    } while (false);
//    
//    return false;
//}



CLogicGrid* CBackgroundManager::getGrid(const CCPoint& gridPos)
{
    do
    {
        BREAK_IF_FAILED(gridPos.x >= 0 && gridPos.x < m_widthInGrid);
        BREAK_IF_FAILED(gridPos.y >= 0 && gridPos.y < m_heightInGrid);
        
        return &(m_grids[gridPos.x + gridPos.y * m_widthInGrid]);
    } while (false);
    
    return NULL;
}



CCPoint CBackgroundManager::gridToPoint(const CCPoint& gridPos)
{
    CCPoint pt;
    pt.x = gridPos.x * GRID_WIDTH_SIZE;
    pt.x += GRID_WIDTH_SIZE >> 1;
    
    pt.y = gridPos.y * GRID_HEIGHT_SIZE;
    pt.y += GRID_HEIGHT_SIZE >> 1;
    
    return pt;
}



CLogicGrid* CBackgroundManager::getGridFromPt(const CCPoint& pt)
{
    const CCPoint& gridPos = pointToGrid(pt);
    
    return getGrid(gridPos);
}



CCPoint CBackgroundManager::pointToGrid(const CCPoint& pt)
{
    return CCPoint(int(pt.x / GRID_WIDTH_SIZE), int(pt.y / GRID_HEIGHT_SIZE));
}



CLogicGrid* CBackgroundManager::getNeighborGrid(const CCPoint& gridPos, GRID_REL rel)
{
    int x = gridPos.x;
    int y = gridPos.y;
    switch (rel)
    {
        case REL_LEFT_DOWN:
            x--;
            y--;
            break;
        case REL_DOWN:
            y--;
            break;
        case REL_RIGHT_DOWN:
            x++;
            y--;
            break;
        case REL_RIGHT:
            x++;
            break;
        case REL_RIGHT_UP:
            x++;
            y++;
            break;
        case REL_UP:
            y++;
            break;
        case REL_LEFT_UP:
            x--;
            y++;
            break;
        case REL_LEFT:
            x--;
            break;
        default:
            CC_ASSERT(false);
    }
    
    return getGrid(CCPoint(x, y));
}



CLogicGrid* CBackgroundManager::getEmptyGridNearby(const CCPoint& gridPos)
{
    CLogicGrid* grid = NULL;

    
    for (int i = 0; i < REL_NUM; ++i)
    {
        grid = getNeighborGrid(gridPos, (GRID_REL)i);
        if (grid && NULL == grid->getGroundUnit()) return grid;
    }
    
    int x = gridPos.x;
    int y = gridPos.y;
    
    grid = getEmptyGridNearby(CCPoint(x - 1, y - 1));        // LEFT DOWN
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x, y - 1));            // DOWN
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x + 1, y - 1));        // RIGHT DOWN
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x + 1, y));            // RIGHT
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x + 1, y + 1));        // RIGHT UP
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x, y + 1));            // UP
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x - 1, y + 1));        // LEFT UP
    if (grid) return grid;
    
    grid = getEmptyGridNearby(CCPoint(x - 1, y));              // LEFT
    if (grid) return grid;
    
    
    return NULL;
}




void CBackgroundManager::hightlightGrid(const CCPoint& gridPos, bool onOff)
{
    CLogicGrid* grid = getGrid(gridPos);
    if (grid)
    {
        grid->getGridBkg()->playAnimation(onOff ? "Highlight" : "Ready");
    }
}



void CBackgroundManager::hightlightGridInPoint(const CCPoint& pt, bool onOff)
{
    hightlightGrid(pointToGrid(pt));
}



void CBackgroundManager::clearAllUnits()
{
    int x, y;
    for (y = 0; y < m_heightInGrid; ++y)
    {
        for (x = 0; x < m_widthInGrid; ++x)
        {
            CLogicGrid& grid = m_grids[x + y * m_widthInGrid];
            CRole* role = grid.getGroundUnit();
            if (role)
            {
                role->die();        // 如何释放还没想清楚，直接调用die是不行的！！！
            }
            role = grid.getAirUnit();
            if (role)
            {
                role->die();
            }
            grid.setGroundUnit(NULL);
            grid.setAirUnit(NULL);
        }
    }
}


// -------------------- CLogicGrid

CLogicGrid::CLogicGrid(int x, int y)
: m_groundUnit(NULL)
, m_airUnit(NULL)
, m_gridBkg(NULL)
, m_gridPos(x, y)
{
    
}



CLogicGrid::CLogicGrid(const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    setGroundUnit(obj.getGroundUnit());
    setAirUnit(obj.getAirUnit());
    setGridBkg(obj.getGridBkg());
}



CLogicGrid::~CLogicGrid()
{
    
}



CLogicGrid& CLogicGrid::operator = (const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    setGroundUnit(obj.getGroundUnit());
    setAirUnit(obj.getAirUnit());
    setGridBkg(obj.getGridBkg());
    return *this;
}


void CLogicGrid::setGroundUnit(CRole* var)
{
    if (var)
    {
        var->setSpriteZOrder(10000 - m_gridPos.y);
        var->setGrid(this);
    }
    m_groundUnit = var;
}


CRole* CLogicGrid::getGroundUnit() const
{
    return m_groundUnit;
}



void CLogicGrid::setAirUnit(CRole* var)
{
    if (var)
    {
        var->setSpriteZOrder(10000 - m_gridPos.y);
        var->setGrid(this);
    }
    m_airUnit = var;
}



CRole* CLogicGrid::getAirUnit() const
{
    return m_airUnit;
}


