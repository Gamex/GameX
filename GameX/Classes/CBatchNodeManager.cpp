//
//  CBatchNodeManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-19.
//
//

#include "CBatchNodeManager.h"
#include "Common.h"
#include "CGlobalConfigration.h"

IMPLEMENT_SINGLETON(CBatchNodeManager);


CBatchNodeManager::CBatchNodeManager()
: m_pBatchNodeHolder(NULL)
{
    
}



CBatchNodeManager::~CBatchNodeManager()
{
    
}


bool CBatchNodeManager::initialize()
{
    do
    {
        BREAK_IF_FAILED(loadBatchNodeInitData());
        return true;
    } while(false);
    
    return false;
}


bool CBatchNodeManager::loadBatchNodeInitData()
{
    do
    {
        setBatchNodeHolder(CCNode::create());
        CC_ASSERT(m_pBatchNodeHolder);
        
        const char* cp = "BatchNodes.plist";

        CCArray* array = CCArray::createWithContentsOfFile(cp);
        
        BREAK_IF_FAILED(array && array->data);
        
        CCObject* obj;
        
        string name;
        string texture;
        int z;
        CCString* s;
        const string& suffix = GLOBAL_CONFIG->getTextureSuffix();
        char buffer[260] = {0};
        
        CCARRAY_FOREACH(array, obj)
        {
            CCDictionary* sub_dict = dynamic_cast<CCDictionary*>(obj);
            CC_ASSERT(sub_dict);
            
            s = dynamic_cast<CCString*>(sub_dict->objectForKey("Name"));
            CC_ASSERT(s);
            name = s->getCString();
            
            CC_ASSERT(m_pBatchNodes.find(name) == m_pBatchNodes.end());
            
            s = dynamic_cast<CCString*>(sub_dict->objectForKey("Texture"));
            CC_ASSERT(s);
            texture = s->getCString();
            
            s = dynamic_cast<CCString*>(sub_dict->objectForKey("Z"));
            CC_ASSERT(s);
            z = s->intValue();
            
            CCSpriteFrameCache* sfc = CCSpriteFrameCache::sharedSpriteFrameCache();
            sprintf(buffer, "%s%s.plist", texture.c_str(), suffix.c_str());
            sfc->addSpriteFramesWithFile(buffer);
            
            sprintf(buffer, "%s%s.pvr.ccz", texture.c_str(), suffix.c_str());
            CCSpriteBatchNode* sbn = CCSpriteBatchNode::create(buffer);
            CC_ASSERT(sbn);
            
            m_pBatchNodes[name] = sbn;
            
            m_pBatchNodeHolder->addChild(sbn, z);
        }
        
        return true;
    } while (false);
    
    return false;
}



void CBatchNodeManager::attachToParent(CCNode* parent, int z)
{
    CC_ASSERT(parent);
    parent->addChild(m_pBatchNodeHolder, z);
}



CCNode* CBatchNodeManager::getNodeByName(const string& name, bool& isBatchNode)
{
    MSSBN_IT it = m_pBatchNodes.find(name);
    if (it == m_pBatchNodes.end())
    {
        isBatchNode = false;
        
        return m_pBatchNodeHolder;
    }
    
    isBatchNode = true;
    
    return (*it).second;
}



void CBatchNodeManager::clearAllChildren()
{
    MSSBN_IT it = m_pBatchNodes.begin();
    for (; it != m_pBatchNodes.end(); ++it)
    {
        (*it).second->retain();
        (*it).second->removeAllChildrenWithCleanup(true);
    }
    m_pBatchNodeHolder->removeAllChildrenWithCleanup(true);
    
    it = m_pBatchNodes.begin();
    for (; it != m_pBatchNodes.end(); ++it)
    {
        m_pBatchNodeHolder->addChild((*it).second);
        (*it).second->release();
    }
}


