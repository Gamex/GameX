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


class CRole;

enum GRID_REL
{
    REL_LEFT_DOWN,
    REL_DOWN,
    REL_RIGHT_DOWN,
    REL_RIGHT,
    REL_RIGHT_UP,
    REL_UP,
    REL_LEFT_UP,
    REL_LEFT,
    REL_NUM,
};


class CLogicGrid
{
    CC_SYNTHESIZE_READONLY(CCPoint, m_gridPos, GridPos);
    CC_SYNTHESIZE(class CSpriteObject*, m_gridBkg, GridBkg);
public:
    CLogicGrid(int x, int y);
    CLogicGrid(const CLogicGrid& obj);
    virtual ~CLogicGrid();
    
    CLogicGrid& operator = (const CLogicGrid& obj);
    bool operator < (const CLogicGrid& obj);
    
    virtual CRole* getGroundUnit() const;
    virtual CRole* getAirUnit() const;
    
    virtual void setGroundUnit(CRole* var);
    virtual void setAirUnit(CRole* var);
protected:
private:
    CRole* m_groundUnit;
    CRole* m_airUnit;
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
    
    // all param of CCPoint means in grid cooridnate. CPoint means position in screen coordinate.
    virtual CLogicGrid* getGrid(const CCPoint& gridPos);
    virtual CLogicGrid* getGridFromPt(const CCPoint& pt);
    virtual CCPoint gridToPoint(const CCPoint& gridPos);
    virtual CCPoint pointToGrid(const CCPoint& pt);
    
    virtual CLogicGrid* getNeighborGrid(const CCPoint& gridPos, GRID_REL rel);
    virtual CLogicGrid* getEmptyGridNearby(const CCPoint& gridPos);
    
    virtual void hightlightGrid(const CCPoint& gridPos, bool onOff = true);
    virtual void hightlightGridInPoint(const CCPoint& pt, bool onOff = true);
    
    virtual void clearAllUnits();
protected:

private:
    vector<CLogicGrid> m_grids;
};

#define BKG_MANAGER         (CBackgroundManager::getInstance())

#endif /* defined(__GameX__CBackgroundManager__) */
