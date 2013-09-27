//
//  CPathFinderManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#include "CPathFinderManager.h"
#include "CBackgroundManager.h"
#include <queue>

IMPLEMENT_SINGLETON(CPathFinderManager);

CPathFinderManager::CPathFinderManager()
{
    
}



CPathFinderManager::~CPathFinderManager()
{
    while (m_finderTaskQueue.size() > 0)
    {
        delete m_finderTaskQueue.front();
        m_finderTaskQueue.pop();
    }
}



void CPathFinderManager::update(float dt)
{
    if (m_finderTaskQueue.size() > 0)
    {
        _FinderTask* ft = m_finderTaskQueue.front();
        m_finderTaskQueue.pop();
        
        ft->doFind();
        
        delete ft;
    }
}



void CPathFinderManager::findPath(const CCPoint& startPos, const CCPoint& targetPos, IGridRole* role, IPathFinderDelegate* delegate)
{
    _FinderTask* task = new _FinderTask;
    
    task->role = role;
    task->start = startPos;
    task->target = targetPos;
    task->delegate = delegate;

    m_finderTaskQueue.push(task);
}


// -------------- _PathNode
MEM_POOL_DEFINE(CPathFinderManager::_PathNode, 1200);

CPathFinderManager::_PathNode::_PathNode()
: grid(NULL)
, parent(NULL)
, H(0)
, G(0)
, F(0)
{
}



// ----------------- _FinderTask
void CPathFinderManager::_FinderTask::doFind()
{
    CLogicGrid* grid = BKG_MANAGER->getLogicGrid(start);
    if (grid)
    {
        _PathNode* pn = new _PathNode;
        pn->grid = grid;
        openList.push(pn);
    }

    vector<CCPoint> outPath;
    while (openList.size() > 0)
    {
        _PathNode* pn = openList.top();
        openList.pop();
        closeList.push(pn);
        findSurround(pn);
        
        pn = openList.getInList(target);
        if (pn)
        {
            while (pn)
            {
                outPath.push_back(pn->grid->getGridPos());
                pn = pn->parent;
            };
            break;
        }
    }
    
    if (delegate)
    {
        delegate->onPathReady(outPath);
    }
}



void CPathFinderManager::_FinderTask::checkF(const CCPoint& gridPos, int G, CPathFinderManager::_PathNode* parent)
{
    if (!closeList.getInList(gridPos))
    {
        _PathNode* pn = openList.getInList(gridPos);
        if (pn)
        {
            if (pn->G > G)
            {
                pn->G = G;
                pn->H = fabs(target.x - gridPos.x) + fabs(target.y - gridPos.y);
                pn->H *= 10;
                pn->F = pn->G + pn->H;
                pn->parent = parent;
            }
        }
        else
        {
            CLogicGrid* grid = BKG_MANAGER->getLogicGrid(gridPos);
            
            bool canBePlace = BKG_MANAGER->isRoleCanBePlacedOnPos(role, gridPos);
            if (!canBePlace && grid)
            {
                canBePlace = BKG_MANAGER->isGridPosInGridRange(gridPos, role->getGridWidth(), role->getGridHeight(), target);
            }

            if (canBePlace)
            {
                pn = new _PathNode;
                pn->parent = parent;
                pn->grid = grid;
                pn->G = G;
                pn->H = fabs(target.x - gridPos.x) + fabs(target.y - gridPos.y);
                pn->H *= 10;
                pn->F = pn->G + pn->H;
                
                openList.push(pn);
            }
        }
    }
}



void CPathFinderManager::_FinderTask::findSurround(CPathFinderManager::_PathNode* parent)
{
    const CCPoint& p = parent->grid->getGridPos();
    int G = parent->G;
    
    checkF(CCPoint(p.x - 1, p.y     ), G + 10, parent);   // Left
    checkF(CCPoint(p.x    , p.y - 1 ), G + 10, parent);   // Down
    checkF(CCPoint(p.x + 1, p.y     ), G + 10, parent);   // Right
    checkF(CCPoint(p.x    , p.y + 1 ), G + 10, parent);   // Up
    checkF(CCPoint(p.x + 1, p.y + 1 ), G + 14, parent);   // Right up
    checkF(CCPoint(p.x - 1, p.y + 1 ), G + 14, parent);   // Left up
    checkF(CCPoint(p.x - 1, p.y - 1 ), G + 14, parent);   // Left down
    checkF(CCPoint(p.x + 1, p.y - 1 ), G + 14, parent);   // Right down
}



CPathFinderManager::_FinderTask::~_FinderTask()
{
    
}

