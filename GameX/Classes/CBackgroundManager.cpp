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


#define NORMAL_GID              1
#define HIGHTLITE_GID           2

#define TILE_MAP_NAME           "background.tmx"
#define GROUND_LAYER_NAME       "ground"



IMPLEMENT_SINGLETON(CBackgroundManager);


CBackgroundManager::CBackgroundManager()
: m_pBkg(NULL)
, m_tiledMap(NULL)
{
    
}



CBackgroundManager::~CBackgroundManager()
{
    if (m_pBkg)
    {
        m_pBkg->removeFromParentAndCleanup(true);
        setBkg(NULL);
    }
    
    CC_SAFE_RELEASE(m_tiledMap);
}


void CBackgroundManager::attachBackgroundTo(CCNode* parent)
{
    CC_ASSERT(m_tiledMap && parent);
    parent->addChild(m_tiledMap);
}



bool CBackgroundManager::initialize()
{
    do
    {
        m_tiledMap = CCTMXTiledMap::create(TILE_MAP_NAME);
        BREAK_IF_FAILED(m_tiledMap);
        CC_SAFE_RETAIN(m_tiledMap);
        CCSize sz = m_tiledMap->getContentSize();
        m_tiledMap->setPosition(-(CCPoint(sz) / 2));
        m_origMapPos = m_tiledMap->getPosition();

        m_groundLayer = m_tiledMap->layerNamed(GROUND_LAYER_NAME);
        
        CCSize layerSz = m_groundLayer->getLayerSize();
        
        m_grids.clear();
        m_grids.reserve(layerSz.width * layerSz.height);
        
        for (int y = 0; y < layerSz.width; ++y)
        {
            for (int x = 0 ; x < layerSz.height; ++x)
            {
                m_grids.push_back(CLogicGrid(x, y));
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
        CC_ASSERT(m_groundLayer);
        CCSize layerSz = m_groundLayer->getLayerSize();
        
        BREAK_IF(gridPos.x < 0 || FLT_GE(gridPos.x, layerSz.width));
        BREAK_IF(gridPos.y < 0 || FLT_GE(gridPos.y, layerSz.height));
        
        return &(m_grids[gridPos.x + gridPos.y * layerSz.width]);
    } while (false);
    
    return NULL;
}



CCPoint CBackgroundManager::gridToPoint(const CCPoint& gridPos)
{
    CC_ASSERT(m_groundLayer);
    return m_groundLayer->positionAt(gridPos) * m_tiledMap->getScale();
}



CLogicGrid* CBackgroundManager::getGridFromPt(const CCPoint& pt)
{
    const CCPoint& gridPos = pointToGrid(pt);
    
    return getLogicGrid(gridPos);
}



CCPoint CBackgroundManager::pointToGrid(const CCPoint& pt)
{
    float scale = m_tiledMap->getScale();
    CCPoint pos = pt - m_tiledMap->getPosition();
    const CCSize& mapSize = m_tiledMap->getMapSize();
    float halfMapWidth =  mapSize.width * 0.5f;
    float mapHeight =  mapSize.height;
    const CCSize& tileSize = m_tiledMap->getTileSize() * scale;
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;
    CCPoint tilePosDiv(pos.x / tileWidth, pos.y / tileHeight);
    float inverseTileY = mapHeight - tilePosDiv.y;
    
    // 将得到的计算结果转换成 int，以确保得到的是整数
    float posX = (int)(inverseTileY + tilePosDiv.x - halfMapWidth);
    float posY = (int)(inverseTileY - tilePosDiv.x + halfMapWidth);
    
    // 确保坐标在地图的边界之内 posX = MAX(0, posX);
    posX = MIN( mapSize.width - 1, posX);
    posY = MAX(0, posY);
    posY = MIN( mapSize.height - 1, posY);
     
    return CCPoint(posX, posY);
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
            if (NULL == tmp || tmp->getUnit())
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



void CBackgroundManager::clearAllHightlightGrids()
{
//    vector<CLogicGrid>::iterator it = m_grids.begin();
//    for (; it != m_grids.end(); ++it)
//    {
//        (*it).getGridBkg()->playAnimation("Ready");
//    }
}



void CBackgroundManager::hightlightGrid(const CCPoint& gridPos, bool onOff)
{
    const CCSize& sz = m_groundLayer->getLayerSize();
    if (gridPos.x >= 0 && gridPos.x < sz.width &&
        gridPos.y >= 0 && gridPos.y < sz.height)
    {
        m_groundLayer->setTileGID(onOff ? HIGHTLITE_GID : NORMAL_GID, gridPos);
    }
}



void CBackgroundManager::hightlightGridInPoint(const CCPoint& pt, bool onOff)
{
    hightlightGrid(pointToGrid(pt));
}



void CBackgroundManager::clearAllUnits()
{
//    int x, y;
//    for (y = 0; y < m_heightInGrid; ++y)
//    {
//        for (x = 0; x < m_widthInGrid; ++x)
//        {
//            CLogicGrid& grid = m_grids[x + y * m_widthInGrid];
//            CRole* role = dynamic_cast<CRole*>(grid.getUnit());
//            if (role)
//            {
//                role->die();        // 如何释放还没想清楚，直接调用die是不行的！！！
//            }
//            
//            grid.m_unit = NULL;
//        }
//    }
}


void CBackgroundManager::addRoleToGrid(const CCPoint& gridPos, IGridRole* role)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (role && lgrid)
    {
        role->setZ(10000 - gridPos.y * 100);
        
        int w = role->getGridWidth();
        int h = role->getGridHeight();
        CCPoint pt;
        int x, y;
        for (y = 0; y < h; ++y)
        {
            for (x = 0; x < w; ++x)
            {
                pt.x = gridPos.x + x;
                pt.y = gridPos.y + y;
                CLogicGrid* g = getLogicGrid(pt);
                if (g)
                {
                    CC_ASSERT(g->m_unit == NULL);
                    g->m_unit = role;
                }
            }
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
        IGridRole* role = lgrid->getUnit();
        if (role)
        {
            lgrid = role->getLogicGrid();
            CC_ASSERT(lgrid);
            role->setZ(0);
            role->setLogicGrid(NULL);
            int w = role->getGridWidth();
            int h = role->getGridHeight();
            CCPoint pt;
            int x, y;
            for (y = 0; y < h; ++y)
            {
                for (x = 0; x < w; ++x)
                {
                    pt.x = gridPos.x + x;
                    pt.y = gridPos.y + y;
                    CLogicGrid* g = BKG_MANAGER->getLogicGrid(pt);
                    if (g)
                    {
                        CC_ASSERT(g->m_unit != NULL);
                        g->m_unit = NULL;
                    }
                }
            }
        }
    }
}



bool CBackgroundManager::isRoleCanBePlacedOnPos(IGridRole* role, const CCPoint& gridPos)
{
    CC_ASSERT(role);
    int width = role->getGridWidth();
    int height = role->getGridHeight();

    CCPoint pt;
    int x, y;
    for (y = 0; y < height; ++y)
    {
        for (x = 0; x <width; ++x)
        {
            pt.x = gridPos.x + x;
            pt.y = gridPos.y + y;
            CLogicGrid* g = getLogicGrid(pt);

            bool condi = (g == NULL);
            condi = (condi || (g != NULL && g->m_unit != NULL && g->m_unit != role));
            if (condi)
            {
                return false;
            }
        }
    }

    
	return true;
}


bool CBackgroundManager::isGridPosInGridRange(const CCPoint& gridPos, int width, int height, const CCPoint& testPos)
{
    CCRect rect(gridPos.x, gridPos.y, width - 1, height - 1);
    
    return rect.containsPoint(testPos);
}



void CBackgroundManager::scaleMap(float s)
{
    m_tiledMap->setScale(s);
    CCPoint center = CCDirector::sharedDirector()->getWinSize() / 2;

    CCPoint offset = (center - m_origMapPos) * (1 - s);

    m_tiledMap->setPosition(m_origMapPos + offset);
}



// -------------------- CLogicGrid

CLogicGrid::CLogicGrid(int x, int y)
: m_unit(NULL)
, m_gridPos(x, y)
{
    
}



CLogicGrid::CLogicGrid(const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    m_unit = obj.getUnit();
}



CLogicGrid::~CLogicGrid()
{
    
}



CLogicGrid& CLogicGrid::operator = (const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    m_unit = obj.getUnit();
    return *this;
}


