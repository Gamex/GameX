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



CLogicGrid* CBackgroundManager::getLogicGrid(const CCPoint& gridPos)
{
    do
    {
        BREAK_IF(gridPos.x < 0 || gridPos.x >= m_widthInGrid);
        BREAK_IF(gridPos.y < 0 || gridPos.y >= m_heightInGrid);
        
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
    
    return getLogicGrid(gridPos);
}



CCPoint CBackgroundManager::pointToGrid(const CCPoint& pt)
{
    return CCPoint(int(pt.x / GRID_WIDTH_SIZE), int(pt.y / GRID_HEIGHT_SIZE));
}



CLogicGrid* CBackgroundManager::getEmptyGridNearby(const CCPoint& gridPos, int width, int height,
                                                   int level, int step, int count, int dir)
{
    CLogicGrid* grid = NULL;
    
    int x, y;
    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            CLogicGrid* tmp = getLogicGrid(CCPoint(gridPos.x + x, gridPos.y + y));
            if (grid == NULL)
            {
                grid = tmp;
            }
            if (NULL == tmp || tmp->getGroundUnit())
            {
                grid = NULL;
                break;
            }
        }
        if (!grid)
        {
            break;
        }
    }
    if (grid)
    {
        return grid;
    }
    

    x = gridPos.x;
    y = gridPos.y;
    switch (dir)
    {
        case DIRECTION_DOWN:
            y--;
            break;
        case DIRECTION_RIGHT:
            x++;
            break;
        case DIRECTION_UP:
            y++;
            break;
        case DIRECTION_LEFT:
            x--;
            break;
        default:
            break;
    }
    
    // clac next dir
    count++;
    if (count >= level)
    {
        count = 0;
        dir++;
        if (dir > DIRECTION_LEFT) dir = DIRECTION_DOWN;
        
        if (step > 0)
        {
            level++;
            step = 0;
        }
        else
        {
            step++;
        }

    }
    
    return getEmptyGridNearby(CCPoint(x, y), width, height, level, step, count, dir);

}



void CBackgroundManager::hightlightGrid(const CCPoint& gridPos, bool onOff)
{
    CLogicGrid* grid = getLogicGrid(gridPos);
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
            CRole* role = dynamic_cast<CRole*>(grid.getGroundUnit());
            if (role)
            {
                role->die();        // 如何释放还没想清楚，直接调用die是不行的！！！
            }
            role = dynamic_cast<CRole*>(grid.getAirUnit());
            if (role)
            {
                role->die();
            }
            
            grid.m_groundUnit = NULL;
            grid.m_airUnit = NULL;
        }
    }
}


void CBackgroundManager::addRoleToGrid(const CCPoint& gridPos, IGridRole* role)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (role && lgrid)
    {
        role->setZ(10000 - gridPos.y * 100);
        
        int w = role->getGridWidth();
        int h = role->getGridHeight();
        CCPoint pt = gridPos;
        int x, y;
        for (y = 0; y < h; ++y)
        {
            
            for (x = 0; x < w; ++x)
            {
                CLogicGrid* g = getLogicGrid(pt);

                if (g)
                {
                    CC_ASSERT(g->m_groundUnit == NULL);
                    g->m_groundUnit = role;
                }
                pt.x++;
            }
            
            pt.y++;
        }
        
        role->setLogicGrid(lgrid);
    }
}



void CBackgroundManager::removeRoleFromGrid(IGridRole* role)
{
    CC_ASSERT(role);
    CLogicGrid* grid = role->getLogicGrid();
    if (grid)
    {
        removeRoleFromGrid(grid->getGridPos());
    }
}



void CBackgroundManager::removeRoleFromGrid(const CCPoint& gridPos)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (lgrid)
    {
        IGridRole* role = lgrid->getGroundUnit();
        if (role)
        {
            lgrid = role->getLogicGrid();
            CC_ASSERT(lgrid);
            role->setZ(0);
            role->setLogicGrid(NULL);
            int w = role->getGridWidth();
            int h = role->getGridHeight();
            CCPoint pt = gridPos;
            int x, y;
            for (y = 0; y < h; ++y)
            {
                for (x = 0; x < w; ++x)
                {
                    CLogicGrid* g = BKG_MANAGER->getLogicGrid(pt);
                    
                    if (g)
                    {
                        CC_ASSERT(g->m_groundUnit != NULL);
                        g->m_groundUnit = NULL;
                    }
                    pt.x++;
                }
                
                pt.y++;
            }
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
    m_groundUnit = obj.getGroundUnit();
    m_airUnit = obj.getAirUnit();
    setGridBkg(obj.getGridBkg());
}



CLogicGrid::~CLogicGrid()
{
    
}



CLogicGrid& CLogicGrid::operator = (const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    m_groundUnit = obj.getGroundUnit();
    m_airUnit = obj.getAirUnit();
    setGridBkg(obj.getGridBkg());
    return *this;
}




IGridRole* CLogicGrid::getGroundUnit() const
{
    return m_groundUnit;
}



IGridRole* CLogicGrid::getAirUnit() const
{
    return m_airUnit;
}


