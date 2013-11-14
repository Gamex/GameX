//
//  CBackgroundManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-26.
//
//

#ifndef __GameX__CBackgroundManager__
#define __GameX__CBackgroundManager__

#include "Common.h"


class CPathFinderManager;
class IPathFinderDelegate;

enum{
    DIRECTION_DOWN, // 搜索方向是朝下
    DIRECTION_RIGHT, // 搜索方向是朝右
    DIRECTION_UP, // 搜索方向是朝上
    DIRECTION_LEFT, // 搜索方向是朝左
};


class CBackgroundManager;

class IGridRole
{
    CC_SYNTHESIZE(CBackgroundManager*, m_background, BackGround);
    CC_SYNTHESIZE(class CLogicGrid*, m_pLogicGird, LogicGrid);
    CC_SYNTHESIZE(int, m_gridWidth, GridWidth);
    CC_SYNTHESIZE(int, m_gridHeight, GridHeight);
    CC_SYNTHESIZE_PASS_BY_REF(Point, m_moveTarget, MoveTarget);
public:
    IGridRole()
    : m_pLogicGird(nullptr)
    , m_background(nullptr)
    , m_gridWidth(0)
    , m_gridHeight(0)
    , m_moveTarget(-1.f, -1.f)
    {}
    virtual ~IGridRole(){}
    
    virtual void updateVertexZ() = 0;
    virtual void onPlaceOnMap(const Point& gridPos, const Point& position) = 0;
    virtual void findPath(const Point& startPos, const Point& targetPos, IPathFinderDelegate* delegate = nullptr) = 0;
    virtual bool findPathBrief(const Point& startPos, const Point& targetPos, vector<Point>& path) = 0;
    virtual Point getPositionInGrid() = 0;
    virtual float getDistanceSqInGrid(IGridRole* role) = 0;
    virtual bool checkInGridRadiusSq(IGridRole* role, float radiusInGrid) = 0;
};




class CLogicGrid
{
    friend class CBackgroundManager;
    
    CC_SYNTHESIZE_READONLY(Point, m_gridPos, GridPos);
    CC_SYNTHESIZE_READONLY(IGridRole*, m_unit, Unit);
    CC_SYNTHESIZE(bool, m_isPrimary, IsPrimary);
    CC_SYNTHESIZE(bool, m_locked, Lock);
public:
    CLogicGrid(int x, int y);
    CLogicGrid(const CLogicGrid& obj);
    virtual ~CLogicGrid();
    
    CLogicGrid& operator = (const CLogicGrid& obj);
    
protected:

private:
};



class CBackgroundManager
: public Layer
{
    CC_SYNTHESIZE_READONLY(TMXTiledMap*, m_tiledMap, TiledMap);
    CC_SYNTHESIZE_READONLY(TMXLayer*, m_groundLayer, GroundLayer);
    CC_SYNTHESIZE_READONLY(TMXLayer*, m_objectLayer, ObjectLayer);
    CC_SYNTHESIZE(float, m_mapScaleThresholdMax, MapScaleThresholdMax);
    CC_SYNTHESIZE(float, m_mapScaleThresholdMin, MapScaleThresholdMin);
    
    CC_SYNTHESIZE_READONLY(TMXTiledMap*, m_bkgMap, BkgMap);
public:
    CREATE_FUNC(CBackgroundManager);
    
    CBackgroundManager();
    virtual ~CBackgroundManager();
    
    virtual bool init();
    
    virtual void update(float dt);
    
    virtual void attachBackgroundTo(Node* parent);

    virtual CLogicGrid* getLogicGrid(const Point& gridPos);
    virtual CLogicGrid* getGridFromWorldPt(const Point& pt);
    
    virtual Point gridToWorldPoint(const Point& gridPos);
    virtual Point worldPointToGrid(const Point& pt);
    virtual Point screenPointToGrid(const Point& pt);
    virtual Point worldPointToScreen(const Point& pt);
    virtual Point screenPointToWorld(const Point& pt);
    
    virtual CLogicGrid* getEmptyGridNearby(const Point& gridPos, int width = 1, int height = 1,
                                           int level = 1, int step = 0, int count = 0, int dir = DIRECTION_DOWN);
    
    virtual void clearAllHightlightGrids();
    virtual void hightlightGrid(const Point& gridPos, bool onOff = true);
    
    virtual bool isRoleCanBePlacedOnPos(IGridRole* role, const Point& gridPos, bool lock = false);
    virtual bool isGridPosInGridRange(const Point& gridPos, int width, int height, const Point& testPos);
    virtual void addRoleToGrid(const Point& gridPos, IGridRole* role);
    virtual void removeRoleFromGrid(IGridRole* role);
    virtual void removeRoleFromGrid(const Point& gridPos);
    virtual void clearAllUnits();
    
    virtual void scaleMap(float s, Point centerTilePos);
    virtual float getMapScale();
    virtual void addMapScale(float scaleDelta, Point centerTilePos);
    
    void centerTileMapOnTileCoord(Point tilePos);

    virtual void moveMap(const Point& offset);
    virtual void moveMapTo(const Point& pos);
    
    virtual float getWidthInGrid() const;
    virtual float getHeightInGrid() const;
    virtual const Size& getSizeInGrid() const;

    virtual bool placeRole(IGridRole* role, const Point& gridPos);
    
    virtual void findPath(const Point& startPos, const Point& targetPos, IGridRole* role = nullptr, IPathFinderDelegate* delegate = nullptr);

protected:
private:
    std::vector<CLogicGrid> m_grids;
    CPathFinderManager* m_pathFinder;
};

#endif /* defined(__GameX__CBackgroundManager__) */
