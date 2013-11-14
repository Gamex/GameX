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
#include "CPathFinderManager.h"

#define BKG_BATCH_NODE_NAME     "bn_scene"


#define NORMAL_GID              0
#define HIGHTLITE_GID           1

#define TILE_MAP_NAME           "background.tmx"
#define GROUND_LAYER_NAME       "ground"
#define OBJECT_LAYER_NAME       "object"

#define TILE_BKG_MAP_NAME       "bkg1.tmx"



CBackgroundManager::CBackgroundManager()
: m_tiledMap(nullptr)
, m_pathFinder(nullptr)
, m_mapScaleThresholdMax(2.f)
, m_mapScaleThresholdMin(.5)
{
    
}



CBackgroundManager::~CBackgroundManager()
{
    CC_SAFE_RELEASE(m_tiledMap);
    CC_SAFE_DELETE(m_pathFinder);
}


void CBackgroundManager::attachBackgroundTo(Node* parent)
{
    parent->addChild(this);
}


void CBackgroundManager::centerTileMapOnTileCoord(Point tilePos)
{
    // 获取屏幕大小和屏幕中心点
    Size screenSize = Director::getInstance()->getWinSize();
    Point screenCenter(screenSize.width * 0.5f, screenSize.height * 0.5f);

    // 仅在内部使用：瓷砖的Y坐标要减去1
    tilePos.y -= 1;
    // 获取瓷砖坐标处以像素表示的坐标信息
    Point scrollPosition =  m_groundLayer->getPositionAt(tilePos);
    // 考虑到地图移动的情况，我将像素坐标信息乘以 -1，从而得到负值
    scrollPosition = scrollPosition * -1;
    // 为屏幕中央坐标添加位移值
    scrollPosition = scrollPosition + screenCenter;
    
    // 移动瓷砖地图
    setPosition(scrollPosition * getScale());
//    Action* move = [CCMoveTo actionWithDuration:0.2f position:scrollPosition];
//    [tileMap stopAllActions];
//    [tileMap runAction:move];
}


bool CBackgroundManager::init()
{
    do
    {
        BREAK_IF_FAILED(Layer::init());
        
        m_tiledMap = TMXTiledMap::create(TILE_MAP_NAME);
        BREAK_IF_FAILED(m_tiledMap);
        CC_SAFE_RETAIN(m_tiledMap);
        
        m_bkgMap = TMXTiledMap::create(TILE_BKG_MAP_NAME);
        CC_SAFE_RETAIN(m_bkgMap);
        
        m_groundLayer = m_tiledMap->getLayer(GROUND_LAYER_NAME);
        m_objectLayer = m_tiledMap->getLayer(OBJECT_LAYER_NAME);
        
        Point centerTile{m_tiledMap->getMapSize()};
        centerTile = centerTile * 0.5f;
        centerTileMapOnTileCoord(centerTile);
        
        Point bkgCenterPoint{m_bkgMap->getContentSize() * 0.5f};
        Point tileCenterPoint{m_groundLayer->getPositionAt(centerTile)};

        m_bkgMap->setPosition(tileCenterPoint - bkgCenterPoint);
        

        Size layerSz = m_groundLayer->getLayerSize();
        
        m_grids.clear();
        m_grids.reserve(layerSz.width * layerSz.height);
        
        for (int y = 0; y < layerSz.height; ++y)
        {
            for (int x = 0 ; x < layerSz.width; ++x)
            {
                m_grids.push_back(CLogicGrid(x, y));
            }
        }

        addChild(m_bkgMap, -2);
        addChild(m_tiledMap, -1);
        
        m_pathFinder = new CPathFinderManager;
        m_pathFinder->setBkg(this);
        
        return true;
    } while (false);
    
    return false;
}



CLogicGrid* CBackgroundManager::getLogicGrid(const Point& gridPos)
{
    do
    {
        CC_ASSERT(m_groundLayer);
        Size layerSz = m_groundLayer->getLayerSize();
        
        BREAK_IF(gridPos.x < 0 || FLT_GE(gridPos.x, layerSz.width));
        BREAK_IF(gridPos.y < 0 || FLT_GE(gridPos.y, layerSz.height));
        
        return &(m_grids[gridPos.x + gridPos.y * layerSz.width]);
    } while (false);
    
    return nullptr;
}




CLogicGrid* CBackgroundManager::getGridFromWorldPt(const Point& pt)
{
    const Point& gridPos = worldPointToGrid(pt);
    
    return getLogicGrid(gridPos);
}



Point CBackgroundManager::worldPointToScreen(const Point& pt)
{
    return convertToWorldSpace(pt);
//    return pt + getPosition();
}



Point CBackgroundManager::screenPointToWorld(const Point& pt)
{
    return convertToNodeSpace(pt);
    return pt - getPosition();
}



Point CBackgroundManager::gridToWorldPoint(const Point& gridPos)
{
    CC_ASSERT(m_groundLayer);
    Point pt{m_groundLayer->getPositionAt(gridPos) + Point{m_groundLayer->getMapTileSize() / 2}};
    return pt;
}



Point CBackgroundManager::screenPointToGrid(const Point& pt)
{
    return worldPointToGrid(screenPointToWorld(pt));
}



Point CBackgroundManager::worldPointToGrid(const Point& pt)
{
    Point pos = pt;
    const Size& mapSize = m_tiledMap->getMapSize();
    float halfMapWidth =  mapSize.width * 0.5f;
    float mapHeight =  mapSize.height;
    const Size& tileSize = m_tiledMap->getTileSize();
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;
    Point tilePosDiv(pos.x / tileWidth, pos.y / tileHeight);
    float inverseTileY = mapHeight - tilePosDiv.y;
    
    // 将得到的计算结果转换成 int，以确保得到的是整数
    float posX = (int)(inverseTileY + tilePosDiv.x - halfMapWidth);
    float posY = (int)(inverseTileY - tilePosDiv.x + halfMapWidth);
    
    // 确保坐标在地图的边界之内 posX = MAX(0, posX);
    posX = MIN( mapSize.width - 1, posX);
    posY = MAX(0, posY);
    posY = MIN( mapSize.height - 1, posY);
     
    return Point(posX, posY);
}



CLogicGrid* CBackgroundManager::getEmptyGridNearby(const Point& gridPos, int width, int height,
                                                   int level, int step, int count, int dir)
{
    CLogicGrid* grid = nullptr;
    
    int x, y;
    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            CLogicGrid* tmp = getLogicGrid(Point(gridPos.x + x, gridPos.y + y));
            if (grid == nullptr)
            {
                grid = tmp;
            }
            if (nullptr == tmp || tmp->getUnit())
            {
                grid = nullptr;
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
    
    return getEmptyGridNearby(Point(x, y), width, height, level, step, count, dir);

}



void CBackgroundManager::clearAllHightlightGrids()
{
    const Size& sz = m_groundLayer->getLayerSize();
    Point pt;
    for (pt.y = 0; pt.y < sz.height; ++pt.y)
    {
        for (pt.x = 0; pt.x < sz.width; ++pt.x)
        {
            m_groundLayer->setTileGID(NORMAL_GID, pt);
        }
    }
}



void CBackgroundManager::hightlightGrid(const Point& gridPos, bool onOff)
{
    const Size& sz = m_groundLayer->getLayerSize();
    if (gridPos.x >= 0 && gridPos.x < sz.width &&
        gridPos.y >= 0 && gridPos.y < sz.height)
    {
        m_groundLayer->setTileGID(onOff ? HIGHTLITE_GID : NORMAL_GID, gridPos);
    }
}



void CBackgroundManager::clearAllUnits()
{
    const Size& sz = m_groundLayer->getLayerSize();
    Point pt;
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
            
            grid.m_unit = nullptr;
        }
    }
}


void CBackgroundManager::addRoleToGrid(const Point& gridPos, IGridRole* role)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (role && lgrid)
    {
        int w = role->getGridWidth();
        int h = role->getGridHeight();
        Point pt;
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
                    CC_ASSERT(g->m_unit == nullptr);
                    g->m_unit = role;
                    g->m_isPrimary = false;
                    g->m_locked = false;
                }
            }
        }
        
        lgrid->m_isPrimary = true;
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



void CBackgroundManager::removeRoleFromGrid(const Point& gridPos)
{
    CLogicGrid* lgrid = getLogicGrid(gridPos);
    if (lgrid)
    {
        IGridRole* role = lgrid->getUnit();
        if (role)
        {
            lgrid = role->getLogicGrid();
            CC_ASSERT(lgrid);
            role->setLogicGrid(nullptr);
            int w = role->getGridWidth();
            int h = role->getGridHeight();
            Point pt;
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
                        CC_ASSERT(g->m_unit != nullptr);
                        g->m_unit = nullptr;
                    }
                }
            }
        }
    }
}



bool CBackgroundManager::isRoleCanBePlacedOnPos(IGridRole* role, const Point& gridPos, bool lock)
{
    CC_ASSERT(role);
    int width = role->getGridWidth();
    int height = role->getGridHeight();

    Point pt;
    int x, y;
    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            pt.x = gridPos.x + x;
            pt.y = gridPos.y + y;
            CLogicGrid* g = getLogicGrid(pt);

            bool condi = (g == nullptr);
            condi = (condi || g->m_locked == true || (g != nullptr && g->m_unit != nullptr && g->m_unit != role));
            if (condi)
            {
                return false;
            }
        }
    }

    if (lock)
    {
        for (y = 0; y < height; ++y)
        {
            for (x = 0; x < width; ++x)
            {
                pt.x = gridPos.x + x;
                pt.y = gridPos.y + y;
                CLogicGrid* g = getLogicGrid(pt);
                
                g->setLock(true);
            }
        }
    }
    
	return true;
}


bool CBackgroundManager::isGridPosInGridRange(const Point& gridPos, int width, int height, const Point& testPos)
{
    Rect rect(gridPos.x, gridPos.y, width - 1, height - 1);
    
    return rect.containsPoint(testPos);
}



void CBackgroundManager::scaleMap(float s, Point centerTilePos)
{
    if (s < m_mapScaleThresholdMin)
    {
        s = m_mapScaleThresholdMin;
    }
    else if (s > m_mapScaleThresholdMax)
    {
        s = m_mapScaleThresholdMax;
    }
    
    setScale(s);
    
    centerTileMapOnTileCoord(centerTilePos);
}



float CBackgroundManager::getMapScale()
{
	return getScale();
}



void CBackgroundManager::addMapScale(float scaleDelta, Point centerTilePos)
{
    scaleMap(getMapScale() + scaleDelta, centerTilePos);
}



void CBackgroundManager::moveMap(const Point& offset)
{
    Point pt = getPosition() + offset;
   
    setPosition(pt);
}



void CBackgroundManager::moveMapTo(const Point& pos)
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



const Size& CBackgroundManager::getSizeInGrid() const
{
    CC_ASSERT(m_groundLayer);
	return m_groundLayer->getLayerSize();
}



bool CBackgroundManager::placeRole(IGridRole* role, const Point& gridPos)
{
    do
    {
        role->setBackGround(this);
        
        Point pt = gridToWorldPoint(gridPos);
        
        role->onPlaceOnMap(gridPos, pt);

        removeRoleFromGrid(role);
        addRoleToGrid(gridPos, role);

        return true;
    } while (false);
    
    return false;
}



void CBackgroundManager::findPath(const Point& startPos, const Point& targetPos, IGridRole* role, IPathFinderDelegate* delegate)
{
    CC_ASSERT(m_pathFinder);
    m_pathFinder->findPath(startPos, targetPos, role, delegate);
}




void CBackgroundManager::update(float dt)
{
    Layer::update(dt);
    
    m_pathFinder->update(dt);
}


#pragma mark  -- CLogicGrid

CLogicGrid::CLogicGrid(int x, int y)
: m_unit(nullptr)
, m_gridPos(x, y)
, m_locked(false)
{
    
}



CLogicGrid::CLogicGrid(const CLogicGrid& obj)
{
    m_gridPos = obj.getGridPos();
    m_unit = obj.getUnit();
    m_locked = obj.getLock();
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


