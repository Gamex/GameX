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
#include <map>
#include <string>

using namespace std;
USING_NS_CC;


class CBatchNodeManager
: public CCNode
{
public:
    CREATE_FUNC(CBatchNodeManager);
    
    CBatchNodeManager();
    virtual ~CBatchNodeManager();
    
    virtual bool init();
    virtual bool loadBatchNodeInitData(const char* filename);
    
    virtual void attachToParent(CCNode* parent, int z);
    
    virtual CCNode* getNodeByName(const string& name, bool& isBatchNode);
    
    virtual void clearAllChildren();
    
    virtual void attachToMe(class CVisibleObject* vo, int zOrder = 0, int tag = -1);
protected:
    
private:
    typedef map<string, CCSpriteBatchNode*> MSSBN;              // batch node name -> batch node object
    typedef map<string, CCSpriteBatchNode*>::iterator MSSBN_IT;
    typedef map<string, CCSpriteBatchNode*>::const_iterator MSSBN_CIT;
    
    MSSBN m_pBatchNodes;
};


#endif /* defined(__GameX__CBatchNodeManager__) */
