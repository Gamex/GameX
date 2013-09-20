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
    CC_SYNTHESIZE(int, m_Z, Z);
public:
    IGridRole()
    : m_pLogicGird(NULL)
    , m_gridWidth(0)
    , m_gridHeight(0)
    {}
    virtual ~IGridRole(){}
    
    virtual bool placeOnGridPos(const CCPoint& gridPos, bool syncTargetPos = true) = 0;
};




class CLogicGrid
{
    friend class CBackgroundManager;
    
    CC_SYNTHESIZE_READONLY(CCPoint, m_gridPos, GridPos);
    CC_SYNTHESIZE(class CSpriteObject*, m_gridBkg, GridBkg);
public:
    CLogicGrid(int x, int y);
    CLogicGrid(const CLogicGrid& obj);
    virtual ~CLogicGrid();
    
    CLogicGrid& operator = (const CLogicGrid& obj);
    
    virtual IGridRole* getGroundUnit() const;
    virtual IGridRole* getAirUnit() const;
    
protected:

private:
    IGridRole* m_groundUnit;
    IGridRole* m_airUnit;
};



class CBackgroundManager : public CSingleton<CBackgroundManager>
{
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pBkg, Bkg);
    CC_SYNTHESIZE_READONLY(int, m_widthInGrid, WidthInGrid);
    CC_SYNTHESIZE_READONLY(int, m_heightInGrid, HeightInGrid);
public:
    CBackgroundManager();
    virtual ~CBackgroundManager();
    
    virtual bool initialize();

    virtual CLogicGrid* getLogicGrid(const CCPoint& gridPos);
    virtual CLogicGrid* getGridFromPt(const CCPoint& pt);
    virtual CCPoint gridToPoint(const CCPoint& gridPos);
    virtual CCPoint pointToGrid(const CCPoint& pt);
    
    virtual CLogicGrid* getEmptyGridNearby(const CCPoint& gridPos, int width = 1, int height = 1,
                                           int level = 1, int step = 0, int count = 0, int dir = DIRECTION_DOWN);
    
    virtual void clearAllHightlightGrids();
    virtual void hightlightGrid(const CCPoint& gridPos, bool onOff = true);
    virtual void hightlightGridInPoint(const CCPoint& pt, bool onOff = true);
    
    virtual bool isRoleCanBePlacedOnPos(IGridRole* role, const CCPoint& gridPos);
    virtual bool isGridPosInGridRange(const CCPoint& gridPos, int width, int height, const CCPoint& testPos);
    virtual void addRoleToGrid(const CCPoint& gridPos, IGridRole* role);
    virtual void removeRoleFromGrid(IGridRole* role);
    virtual void removeRoleFromGrid(const CCPoint& gridPos);
    virtual void clearAllUnits();
protected:

private:
    vector<CLogicGrid> m_grids;
};

#define BKG_MANAGER         (CBackgroundManager::getInstance())

#endif /* defined(__GameX__CBackgroundManager__) */
