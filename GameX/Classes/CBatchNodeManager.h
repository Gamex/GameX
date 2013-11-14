//
//  CBatchNodeManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-19.
//
//

#ifndef __GameX__CBatchNodeManager__
#define __GameX__CBatchNodeManager__

#include "Common.h"



class CBatchNodeManager
: public Node
{
public:
    CREATE_FUNC(CBatchNodeManager);
    
    CBatchNodeManager();
    virtual ~CBatchNodeManager();
    
    virtual bool init();
    virtual bool loadBatchNodeInitData(const char* filename);
    
    virtual void attachToParent(Node* parent, int z);
    
    virtual Node* getNodeByName(const std::string& name, bool& isBatchNode);
    
    virtual void clearAllChildren();
    
    virtual void attachToMe(class CVisibleObject* vo, int zOrder = 0, int tag = -1);
protected:
    
private:
    MSSBN m_pBatchNodes;
};


#endif /* defined(__GameX__CBatchNodeManager__) */
