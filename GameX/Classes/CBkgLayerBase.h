//
//  CBkgLayerBase.h
//  GameX
//
//  Created by 马 俊 on 13-10-5.
//
//

#ifndef __GameX__CBkgLayerBase__
#define __GameX__CBkgLayerBase__

#include "Common.h"
#include "CBackgroundManager.h"
#include "CBatchNodeManager.h"
#include "CPathFinderManager.h"

class CBkgLayerBase
{
    CC_SYNTHESIZE_RETAIN(CBackgroundManager*, m_bkgGrd, BkgGrd);
    CC_SYNTHESIZE_RETAIN(CBatchNodeManager*, m_batchNode, BatchNode);
public:
    CBkgLayerBase();
    virtual ~CBkgLayerBase();

    virtual void update(float dt);
protected:
    virtual bool initBkgLayerBase(const char* batchNodeName);
    
    virtual void bkgLayerBaseTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    virtual void bkgLayerBaseTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    virtual void bkgLayerBaseTouchesEnded(const std::vector<Touch*>& touches, Event* event);
private:
    CPathFinderManager* m_pathFinder;
    Layer* m_layer;
    
    float m_lastLength;
    Point  m_tapStartPoint;
    Point m_scaleCenterGridPos;
    
    std::vector<Touch*> m_touches;
};

#endif /* defined(__GameX__CBkgLayerBase__) */
