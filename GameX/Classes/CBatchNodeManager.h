//
//  CBatchNodeManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-19.
//
//

#ifndef __GameX__CBatchNodeManager__
#define __GameX__CBatchNodeManager__

#include "cocos2d.h"
#include "CSingleton.h"
#include <map>
#include <string>

using namespace std;
USING_NS_CC;


class CBatchNodeManager : public CSingleton<CBatchNodeManager>
{
    CC_SYNTHESIZE_RETAIN(CCNode*, m_pBatchNodeHolder, BatchNodeHolder);
public:
    CBatchNodeManager();
    virtual ~CBatchNodeManager();
    
    virtual bool initialize();
    
    virtual void attachToParent(CCNode* parent, int z);
    
    virtual CCNode* getNodeByName(const string& name, bool& isBatchNode);
protected:
    
    virtual bool loadBatchNodeInitData();
private:
    typedef map<string, CCSpriteBatchNode*> MSSBN;              // batch node name -> batch node object
    typedef map<string, CCSpriteBatchNode*>::iterator MSSBN_IT;
    typedef map<string, CCSpriteBatchNode*>::const_iterator MSSBN_CIT;
    
    MSSBN m_pBatchNodes;
};


#define BATCH_NODE_MANAGER      (CBatchNodeManager::getInstance())

#endif /* defined(__GameX__CBatchNodeManager__) */
