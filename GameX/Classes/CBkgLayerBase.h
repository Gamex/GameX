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
    
    virtual void bkgLayerBaseTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void bkgLayerBaseTouchesMoved(CCSet* touches, CCEvent* event);
    virtual void bkgLayerBaseTouchesEnded(CCSet* touches, CCEvent* event);
private:
    CPathFinderManager* m_pathFinder;
    CCLayer* m_layer;
    
    float m_lastLength;
    CCPoint  m_tapStartPoint;
    CCPoint m_scaleCenterGridPos;
    
    CCArray* m_touches;
};

#endif /* defined(__GameX__CBkgLayerBase__) */
