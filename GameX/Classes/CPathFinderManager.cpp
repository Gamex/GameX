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



void CPathFinderManager::findPath(const CGridPos& startPos, const CGridPos& targetPos)
{
    _FinderTask* task = new _FinderTask;
    
    task->start = startPos;
    task->target = targetPos;
    
    // for test
    int i;
    for (i = 5; i < 30; ++i)
    {
        BKG_MANAGER->getGrid(CGridPos(18, i))->setGroundUnit((CRole*)1);
    }
    // end for test
    task->doFind();
//    m_finderTaskQueue.push(task);
}


// -------------- _PathNode
MEM_POOL_DEFINE(CPathFinderManager::_PathNode, 600);

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
    CLogicGrid* grid = BKG_MANAGER->getGrid(start);
    if (grid)
    {
        _PathNode* pn = new _PathNode;
        pn->grid = grid;
        openList.push(pn);
    }

    
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
                CCLOG("%d, %d", pn->grid->getGridPos().x, pn->grid->getGridPos().y);
                pn = pn->parent;
            };
            break;
        }
    }
}



void CPathFinderManager::_FinderTask::checkF(const CGridPos& gridPos, int G, CPathFinderManager::_PathNode* parent)
{
    if (!closeList.getInList(gridPos))
    {
        _PathNode* pn = openList.getInList(gridPos);
        if (pn)
        {
            if (pn->G > G)
            {
                pn->G = G;
                pn->H = abs(target.x - gridPos.x) + abs(target.y - gridPos.y);
                pn->H *= 10;
                pn->F = pn->G + pn->H;
                pn->parent = parent;
            }
        }
        else
        {
            CLogicGrid* grid = BKG_MANAGER->getGrid(gridPos);
            if (grid && grid->getGroundUnit() == NULL)
            {
                pn = new _PathNode;
                pn->parent = parent;
                pn->grid = grid;
                pn->G = G;
                pn->H = abs(target.x - gridPos.x) + abs(target.y - gridPos.y);
                pn->H *= 10;
                pn->F = pn->G + pn->H;
                
                openList.push(pn);
            }
        }
    }
}



void CPathFinderManager::_FinderTask::findSurround(CPathFinderManager::_PathNode* parent)
{
    const CGridPos& p = parent->grid->getGridPos();
    int G = parent->G;
    
    checkF(CGridPos(p.x - 1, p.y     ), G + 10, parent);   // Left
    checkF(CGridPos(p.x    , p.y - 1 ), G + 10, parent);   // Down
    checkF(CGridPos(p.x + 1, p.y     ), G + 10, parent);   // Right
    checkF(CGridPos(p.x    , p.y + 1 ), G + 10, parent);   // Up
    checkF(CGridPos(p.x + 1, p.y + 1 ), G + 14, parent);   // Right up
    checkF(CGridPos(p.x - 1, p.y + 1 ), G + 14, parent);   // Left up
    checkF(CGridPos(p.x - 1, p.y - 1 ), G + 14, parent);   // Left down
    checkF(CGridPos(p.x + 1, p.y - 1 ), G + 14, parent);   // Right down
}


