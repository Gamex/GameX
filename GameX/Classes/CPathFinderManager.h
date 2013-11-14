//
//  CPathFinderManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#ifndef __GameX__CPathFinderManager__
#define __GameX__CPathFinderManager__

#include "Common.h"
#include "CBackgroundManager.h"
#include "CMemPool.h"


#define PATH_NODE_MEM_POOL_SIZE     5000

class IPathFinderDelegate
{
public:
    virtual void onPathReady(const vector<Point>& path) = 0;
};

class _PathNode
{
public:
    MEM_POOL_DECLARE(_PathNode, PATH_NODE_MEM_POOL_SIZE);
    
    _PathNode();
    
    CLogicGrid* grid;
    int H;
    int G;
    int F;      // F = G + H
    
    _PathNode* parent;
};

struct cmpF
{
    bool operator() ( _PathNode* a, _PathNode* b )
    {
        return a->F > b->F;
    }
};

class _HeapList : public std::priority_queue<_PathNode*, vector<_PathNode*>, cmpF>
{
private:
    class __IfNode
    {
    public:
        __IfNode(const Point& pos):m_pos(pos){}
        bool operator() (_PathNode* node)
        {
            return node->grid->getGridPos().equals(m_pos);
        }
        
    private:
        Point m_pos;
    };
public:
    _PathNode* getInList(const Point& pos)
    {
        vector<_PathNode*>::iterator it = find_if(c.begin(), c.end(), __IfNode(pos));
        if (c.end() != it)
        {
            return *it;
        }
        
        return nullptr;
    }
    
    void deleteVector()
    {
        for (int i = 0; i < c.size(); ++i)
        {
            delete c[i];
        }
    }
    
    virtual ~_HeapList()
    {
        deleteVector();
    }
protected:
};


class _FinderTask
{
public:
    _FinderTask() : delegate(nullptr), role(nullptr){}
    virtual ~_FinderTask();
    Point start;
    Point target;
    IGridRole* role;
    IPathFinderDelegate* delegate;
    CBackgroundManager* m_bkg;
    
    void doFind();
protected:
    void findSurround(_PathNode* parent);
    void checkF(const Point& gridPos, int G, _PathNode* parent);
private:
    _HeapList openList;
    _HeapList closeList;
};


class CPathFinderManager
{
public:
    CPathFinderManager();
    virtual ~CPathFinderManager();
    
    virtual void setBkg(CBackgroundManager* bkg)
    {
        m_bkg = bkg;
    }

    virtual void update(float dt);
    
    virtual void findPath(const Point& startPos, const Point& targetPos, IGridRole* role = nullptr, IPathFinderDelegate* delegate = nullptr);
protected:
        
    QFT m_finderTaskQueue;
    
    float m_cdTime;
private:
    CBackgroundManager* m_bkg;
};



#endif /* defined(__GameX__CPathFinderManager__) */
