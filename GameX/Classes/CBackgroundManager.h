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
#include "cocos2d.h"
#include "CSingleton.h"
#include <vector>

using namespace std;
USING_NS_CC;


enum{
    DIRECTION_DOWN, // 搜索方向是朝下
    DIRECTION_RIGHT, // 搜索方向是朝右
    DIRECTION_UP, // 搜索方向是朝上
    DIRECTION_LEFT, // 搜索方向是朝左
};



class IGridRole
{
    CC_SYNTHESIZE(class CLogicGrid*, m_pLogicGird, LogicGrid);
    CC_SYNTHESIZE(int, m_gridWidth, GridWidth);
    CC_SYNTHESIZE(int, m_gridHeight, GridHeight);
    CC_SYNTHESIZE_PASS_BY_REF(CCPoint, m_moveTarget, MoveTarget);
public:
    IGridRole()
    : m_pLogicGird(NULL)
    , m_gridWidth(0)
    , m_gridHeight(0)
    {}
    virtual ~IGridRole(){}
    
    virtual bool placeOnGridPos(const CCPoint& gridPos, bool syncTargetPos = true) = 0;
    virtual void updateVertexZ() = 0;
};




class CLogicGrid
{
    friend class CBackgroundManager;
    
    CC_SYNTHESIZE_READONLY(CCPoint, m_gridPos, GridPos);
    CC_SYNTHESIZE_READONLY(IGridRole*, m_unit, Unit);
public:
    CLogicGrid(int x, int y);
    CLogicGrid(const CLogicGrid& obj);
    virtual ~CLogicGrid();
    
    CLogicGrid& operator = (const CLogicGrid& obj);
    
protected:

private:
};



class CBackgroundManager : public CSingleton<CBackgroundManager>
{
    CC_SYNTHESIZE_READONLY(CCTMXTiledMap*, m_tiledMap, TiledMap);
    CC_SYNTHESIZE_READONLY(CCTMXLayer*, m_groundLayer, GroundLayer)
    CC_SYNTHESIZE(float, m_mapScaleThresholdMax, MapScaleThresholdMax);
    CC_SYNTHESIZE(float, m_mapScaleThresholdMin, MapScaleThresholdMin);
public:
    CBackgroundManager();
    virtual ~CBackgroundManager();
    
    virtual bool initialize();
    
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
    
    virtual bool isRoleCanBePlacedOnPos(IGridRole* role, const CCPoint& gridPos);
    virtual bool isGridPosInGridRange(const CCPoint& gridPos, int width, int height, const CCPoint& testPos);
    virtual void addRoleToGrid(const CCPoint& gridPos, IGridRole* role);
    virtual void removeRoleFromGrid(IGridRole* role);
    virtual void removeRoleFromGrid(const CCPoint& gridPos);
    virtual void clearAllUnits();
    
    virtual void scaleMap(float s);
    virtual float getMapScale() const;
    virtual void addMapScale(float scaleDelta);

    virtual void moveMap(const CCPoint& offset);
    virtual void moveMapTo(const CCPoint& pos);
    
    virtual float getWidthInGrid() const;
    virtual float getHeightInGrid() const;
    virtual const CCSize& getSizeInGrid() const;
protected:
private:
    vector<CLogicGrid> m_grids;
    CCPoint m_origMapPos;           // store the position of map that not scaled.
};

#define BKG_MANAGER         (CBackgroundManager::getInstance())

#endif /* defined(__GameX__CBackgroundManager__) */
