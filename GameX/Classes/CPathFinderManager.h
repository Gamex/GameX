//
//  CPathFinderManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#ifndef __GameX__CPathFinderManager__
#define __GameX__CPathFinderManager__

#include "CSingleton.h"
#include "CBackgroundManager.h"
#include "CMemPool.h"
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


class CPathFinderManager : public CSingleton<CPathFinderManager>
{
public:
    CPathFinderManager();
    virtual ~CPathFinderManager();

    virtual void update(float dt);
    
    virtual void findPath(const CGridPos& startPos, const CGridPos& targetPos);
protected:
    
    class _PathNode
    {
    public:
        MEM_POOL_DECLARE(_PathNode, 600);
        
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
            __IfNode(const CGridPos& pos):m_pos(pos){}
            bool operator() (_PathNode* node)
            {
                return node->grid->getGridPos() == m_pos;
            }
            
        private:
            CGridPos m_pos;
        };
    public:
        _PathNode* getInList(const CGridPos& pos)
        {
            vector<_PathNode*>::iterator it = find_if(c.begin(), c.end(), __IfNode(pos));
            if (c.end() != it)
            {
                return *it;
            }
            
            return NULL;
        }
    protected:
    };
    
    
    class _FinderTask
    {
    public:
        CGridPos start;
        CGridPos target;
        
        void doFind();
    protected:
        void findSurround(_PathNode* parent);
        void checkF(const CGridPos& gridPos, int G, _PathNode* parent);
    private:
        _HeapList openList;
        _HeapList closeList;
    };

    typedef queue<_FinderTask*> QFT;
    
    QFT m_finderTaskQueue;
private:

};


#define PATH_FINDER     (CPathFinderManager::getInstance())

#endif /* defined(__GameX__CPathFinderManager__) */
