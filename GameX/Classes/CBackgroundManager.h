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
    CC_SYNTHESIZE_PASS_BY_REF(CCPoint, m_moveTarget, MoveTarget);
public:
    IGridRole()
    : m_pLogicGird(NULL)
    , m_background(NULL)
    , m_gridWidth(0)
    , m_gridHeight(0)
    , m_moveTarget(-1.f, -1.f)
    {}
    virtual ~IGridRole(){}
    
    virtual void updateVertexZ() = 0;
    virtual void onPlaceOnMap(const CCPoint& gridPos, const CCPoint& position) = 0;
    virtual void findPath(const CCPoint& startPos, const CCPoint& targetPos, IPathFinderDelegate* delegate = NULL) = 0;
    virtual bool findPathBrief(const CCPoint& startPos, const CCPoint& targetPos, vector<CCPoint>& path) = 0;
    virtual CCPoint getPositionInGrid() = 0;
    virtual float getDistanceSqInGrid(IGridRole* role) = 0;
    virtual bool checkInGridRadiusSq(IGridRole* role, float radiusInGrid) = 0;
};




class CLogicGrid
{
    friend class CBackgroundManager;
    
    CC_SYNTHESIZE_READONLY(CCPoint, m_gridPos, GridPos);
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
: public CCLayer
{
    CC_SYNTHESIZE_READONLY(CCTMXTiledMap*, m_tiledMap, TiledMap);
    CC_SYNTHESIZE_READONLY(CCTMXLayer*, m_groundLayer, GroundLayer);
    CC_SYNTHESIZE_READONLY(CCTMXLayer*, m_objectLayer, ObjectLayer);
    CC_SYNTHESIZE(float, m_mapScaleThresholdMax, MapScaleThresholdMax);
    CC_SYNTHESIZE(float, m_mapScaleThresholdMin, MapScaleThresholdMin);
    
    CC_SYNTHESIZE_READONLY(CCTMXTiledMap*, m_bkgMap, BkgMap);
public:
    CREATE_FUNC(CBackgroundManager);
    
    CBackgroundManager();
    virtual ~CBackgroundManager();
    
    virtual bool init();
    
    virtual void update(float dt);
    
    virtual void attachBackgroundTo(CCNode* parent);

    virtual CLogicGrid* getLogicGrid(const CCPoint& gridPos);
    virtual CLogicGrid* getGridFromWorldPt(const CCPoint& pt);
    
    virtual CCPoint gridToWorldPoint(const CCPoint& gridPos);
    virtual CCPoint worldPointToGrid(const CCPoint& pt);
    virtual CCPoint screenPointToGrid(const CCPoint& pt);
    virtual CCPoint worldPointToScreen(const CCPoint& pt);
    virtual CCPoint screenPointToWorld(const CCPoint& pt);
    
    virtual CLogicGrid* getEmptyGridNearby(const CCPoint& gridPos, int width = 1, int height = 1,
                                           int level = 1, int step = 0, int count = 0, int dir = DIRECTION_DOWN);
    
    virtual void clearAllHightlightGrids();
    virtual void hightlightGrid(const CCPoint& gridPos, bool onOff = true);
    
    virtual bool isRoleCanBePlacedOnPos(IGridRole* role, const CCPoint& gridPos, bool lock = false);
    virtual bool isGridPosInGridRange(const CCPoint& gridPos, int width, int height, const CCPoint& testPos);
    virtual void addRoleToGrid(const CCPoint& gridPos, IGridRole* role);
    virtual void removeRoleFromGrid(IGridRole* role);
    virtual void removeRoleFromGrid(const CCPoint& gridPos);
    virtual void clearAllUnits();
    
    virtual void scaleMap(float s, CCPoint centerTilePos);
    virtual float getMapScale();
    virtual void addMapScale(float scaleDelta, CCPoint centerTilePos);
    
    void centerTileMapOnTileCoord(CCPoint tilePos);

    virtual void moveMap(const CCPoint& offset);
    virtual void moveMapTo(const CCPoint& pos);
    
    virtual float getWidthInGrid() const;
    virtual float getHeightInGrid() const;
    virtual const CCSize& getSizeInGrid() const;

    virtual bool placeRole(IGridRole* role, const CCPoint& gridPos);
    
    virtual void findPath(const CCPoint& startPos, const CCPoint& targetPos, IGridRole* role = NULL, IPathFinderDelegate* delegate = NULL);

protected:
private:
    std::vector<CLogicGrid> m_grids;
    CPathFinderManager* m_pathFinder;
};

#endif /* defined(__GameX__CBackgroundManager__) */
