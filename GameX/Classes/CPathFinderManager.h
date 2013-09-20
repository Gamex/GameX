//
//  CPathFinderManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#ifndef __GameX__CPathFinderManager__
#define __GameX__CPathFinderManager__

#include "cocos2d.h"
#include "CSingleton.h"
#include "CBackgroundManager.h"
#include "CMemPool.h"
#include <queue>
#include <vector>
#include <algorithm>

USING_NS_CC;
using namespace std;


class IPathFinderDelegate
{
public:
    virtual void onPathReady(const vector<CCPoint>& path) = 0;
};

class CPathFinderManager : public CSingleton<CPathFinderManager>
{
public:
    CPathFinderManager();
    virtual ~CPathFinderManager();

    virtual void update(float dt);
    
    virtual void findPath(const CCPoint& startPos, const CCPoint& targetPos, IGridRole* role = NULL, IPathFinderDelegate* delegate = NULL);
protected:
    
    class _PathNode
    {
    public:
        MEM_POOL_DECLARE(_PathNode, 1200);
        
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
            __IfNode(const CCPoint& pos):m_pos(pos){}
            bool operator() (_PathNode* node)
            {
                return node->grid->getGridPos().equals(m_pos);
            }
            
        private:
            CCPoint m_pos;
        };
    public:
        _PathNode* getInList(const CCPoint& pos)
        {
            vector<_PathNode*>::iterator it = find_if(c.begin(), c.end(), __IfNode(pos));
            if (c.end() != it)
            {
                return *it;
            }
            
            return NULL;
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
        _FinderTask() : delegate(NULL), role(NULL){}
        virtual ~_FinderTask();
        CCPoint start;
        CCPoint target;
        IGridRole* role;
        IPathFinderDelegate* delegate;
        
        void doFind();
    protected:
        void findSurround(_PathNode* parent);
        void checkF(const CCPoint& gridPos, int G, _PathNode* parent);
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
