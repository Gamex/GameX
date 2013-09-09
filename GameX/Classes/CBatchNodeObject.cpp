//
//  CBatchNodeObject.cpp
//  TheForce
//
//  Created by 马 俊 on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CBatchNodeObject.h"


//CBatchNodeObject::CBatchNodeObject() :
//pBatchNode_(NULL)
//{
//    
//}
//
//
//
//CBatchNodeObject::~CBatchNodeObject()
//{
//    clearAllBatchNode();
//}
//
//
//
//bool CBatchNodeObject::init()
//{
//    setBatchNode(TEXTURE_CACHE->createSpriteBatchNode(getBatchNodeName()));
//    if (NULL == getBatchNode())
//    {
//        return false;
//    }
//    
//    return true;
//}
//
//
//
//void CBatchNodeObject::clearAllBatchNode()
//{
//    if (getBatchNode())
//    {
//        getBatchNode()->removeFromParentAndCleanup(true);
//    }
//    setBatchNode(NULL);
//}
//
//
//
//bool CBatchNodeObject::attachBatchNodeToParent(CCNode* parent, int zOrder, int tag)
//{
//    if (NULL == parent)
//    {
//        __CCLOGWITHFUNCTION("parent can't be NULL");
//        return false;
//    }
//    
//    parent->addChild(getBatchNode(), zOrder, tag);
//    return true;
//}
