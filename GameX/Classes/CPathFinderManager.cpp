//
//  CPathFinderManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#include "CPathFinderManager.h"
#include "CBackgroundManager.h"

#define CD_TIME        0.1f


CPathFinderManager::CPathFinderManager()
: m_cdTime(0)
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
    m_cdTime -= dt;
    
    if (m_finderTaskQueue.size() > 0 && m_cdTime < 0)
    {
        m_cdTime = CD_TIME;
        
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
    task->m_bkg = m_bkg;

    m_finderTaskQueue.push(task);
}


#pragma mark -- _PathNode
MEM_POOL_DEFINE(_PathNode, PATH_NODE_MEM_POOL_SIZE);

_PathNode::_PathNode()
: grid(NULL)
, parent(NULL)
, H(0)
, G(0)
, F(0)
{
}



#pragma mark -- _FinderTask
void _FinderTask::doFind()
{
    CLogicGrid* grid = m_bkg->getLogicGrid(start);
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



void _FinderTask::checkF(const CCPoint& gridPos, int G, _PathNode* parent)
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
            CLogicGrid* grid = m_bkg->getLogicGrid(gridPos);
            
            bool canBePlace = m_bkg->isRoleCanBePlacedOnPos(role, gridPos);
            if (!canBePlace && grid)
            {
                canBePlace = m_bkg->isGridPosInGridRange(gridPos, role->getGridWidth(), role->getGridHeight(), target);
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



void _FinderTask::findSurround(_PathNode* parent)
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



_FinderTask::~_FinderTask()
{
    
}

