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
: m_tiledMap(NULL)
, m_mapScaleThresholdMax(2.f)
, m_mapScaleThresholdMin(.5)
{
    
}



CBackgroundManager::~CBackgroundManager()
{
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
        
        for (int y = 0; y < layerSz.height; ++y)
        {
            for (int x = 0 ; x < layerSz.width; ++x)
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




CLogicGrid* CBackgroundManager::getGridFromWorldPt(const CCPoint& pt)
{
    const CCPoint& gridPos = worldPointToGrid(pt);
    
    return getLogicGrid(gridPos);
}



CCPoint CBackgroundManager::worldPointToScreen(const CCPoint& pt)
{
    return pt + m_tiledMap->getPosition();
}



CCPoint CBackgroundManager::screenPointToWorld(const CCPoint& pt)
{
    return pt - m_tiledMap->getPosition();
}



CCPoint CBackgroundManager::gridToWorldPoint(const CCPoint& gridPos)
{
    CC_ASSERT(m_groundLayer);
    CCPoint pt = m_groundLayer->positionAt(gridPos) + m_groundLayer->getMapTileSize() / 2;
    return pt;
}



CCPoint CBackgroundManager::screenPointToGrid(const CCPoint& pt)
{
    return worldPointToGrid(screenPointToWorld(pt));
}



CCPoint CBackgroundManager::worldPointToGrid(const CCPoint& pt)
{
    float scale = m_tiledMap->getScale();
    CCPoint pos = pt;
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
    const CCSize& sz = m_groundLayer->getLayerSize();
    CCPoint pt;
    for (pt.y = 0; pt.y < sz.height; ++pt.y)
    {
        for (pt.x = 0; pt.x < sz.width; ++pt.x)
        {
            m_groundLayer->setTileGID(NORMAL_GID, pt);
        }
    }
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



void CBackgroundManager::clearAllUnits()
{
    const CCSize& sz = m_groundLayer->getLayerSize();
    CCPoint pt;
    for (pt.y = 0; pt.y < sz.height; ++pt.y)
    {
        for (pt.x = 0; pt.x < sz.width; ++pt.x)
        {
            CLogicGrid& grid = m_grids[pt.x + pt.y * sz.width];
            CRole* role = dynamic_cast<CRole*>(grid.getUnit());
            if (role)
            {
                role->die();        // 如何释放还没想清楚，直接调用die是不行的！！！
            }
            
            grid.m_unit = NULL;
        }
    }
}


void CBackgroundManager::addRoleToGrid(const CCPoint& gridPos, IGridRole* role)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (role && lgrid)
    {
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
        role->updateVertexZ();
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
        for (x = 0; x < width; ++x)
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
    if (s < m_mapScaleThresholdMin)
    {
        s = m_mapScaleThresholdMin;
    }
    else if (s > m_mapScaleThresholdMax)
    {
        s = m_mapScaleThresholdMax;
    }
    m_tiledMap->setScale(s);
    CCPoint center = CCDirector::sharedDirector()->getWinSize() / 2;

    CCPoint offset = (center - m_origMapPos) * (1 - s);

    m_tiledMap->setPosition(m_origMapPos + offset);
}



float CBackgroundManager::getMapScale() const
{
	return m_tiledMap->getScale();
}



void CBackgroundManager::addMapScale(float scaleDelta)
{
    scaleMap(getMapScale() + scaleDelta);
}



void CBackgroundManager::moveMap(const CCPoint& offset)
{
    CCPoint pt = m_tiledMap->getPosition() + offset;
    m_origMapPos = m_origMapPos + offset;
    
    m_tiledMap->setPosition(pt);
    
}



void CBackgroundManager::moveMapTo(const CCPoint& pos)
{
}



float CBackgroundManager::getWidthInGrid() const
{
    CC_ASSERT(m_groundLayer);
	return static_cast<int>(m_groundLayer->getLayerSize().width);
}



float CBackgroundManager::getHeightInGrid() const
{
    CC_ASSERT(m_groundLayer);
	return static_cast<int>(m_groundLayer->getLayerSize().height);
}



const CCSize& CBackgroundManager::getSizeInGrid() const
{
    CC_ASSERT(m_groundLayer);
	return m_groundLayer->getLayerSize();
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


