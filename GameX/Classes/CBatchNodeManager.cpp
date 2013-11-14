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
#include "CVisibleObject.h"


CBatchNodeManager::CBatchNodeManager()
{
    
}



CBatchNodeManager::~CBatchNodeManager()
{
    
}


bool CBatchNodeManager::init()
{
    do
    {
        BREAK_IF_FAILED(Node::init());
        
        return true;
    } while(false);
    
    return false;
}


bool CBatchNodeManager::loadBatchNodeInitData(const char* filename)
{
    do
    {
        Array* array = Array::createWithContentsOfFile(filename);
        
        BREAK_IF_FAILED(array && array->data);
        
        Object* obj;
        
        std::string name;
        std::string texture;
        int z;
        String* s;
        const std::string& suffix = GLOBAL_CONFIG->getTextureSuffix();
        char buffer[260] = {0};
        
        CCARRAY_FOREACH(array, obj)
        {
            Dictionary* sub_dict = dynamic_cast<Dictionary*>(obj);
            CC_ASSERT(sub_dict);
            
            s = dynamic_cast<String*>(sub_dict->objectForKey("Name"));
            CC_ASSERT(s);
            name = s->getCString();
            
            CC_ASSERT(m_pBatchNodes.find(name) == m_pBatchNodes.end());
            
            s = dynamic_cast<String*>(sub_dict->objectForKey("Texture"));
            CC_ASSERT(s);
            texture = s->getCString();
            
            s = dynamic_cast<String*>(sub_dict->objectForKey("Z"));
            CC_ASSERT(s);
            z = s->intValue();
            
            SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
            sprintf(buffer, "%s%s.plist", texture.c_str(), suffix.c_str());
            sfc->addSpriteFramesWithFile(buffer);
            
            sprintf(buffer, "%s%s.pvr.ccz", texture.c_str(), suffix.c_str());
            SpriteBatchNode* sbn = SpriteBatchNode::create(buffer);
            CC_ASSERT(sbn);
            
            m_pBatchNodes[name] = sbn;
            
            GLProgram* program = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
            sbn->setShaderProgram(program);
            
            GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
            
            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            program->setUniformLocationWith1f(alphaValueLocation, 0.5);
            
            this->addChild(sbn, z);
        }
        
        return true;
    } while (false);
    
    return false;
}



void CBatchNodeManager::attachToParent(Node* parent, int z)
{
    CC_ASSERT(parent);
    parent->addChild(this, z);
}



Node* CBatchNodeManager::getNodeByName(const std::string& name, bool& isBatchNode)
{
    MSSBN_IT it = m_pBatchNodes.find(name);
    if (it == m_pBatchNodes.end())
    {
        isBatchNode = false;
        
        return this;
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
    this->removeAllChildrenWithCleanup(true);
    
    it = m_pBatchNodes.begin();
    for (; it != m_pBatchNodes.end(); ++it)
    {
        this->addChild((*it).second);
        (*it).second->release();
    }
}



void CBatchNodeManager::attachToMe(CVisibleObject* vo, int zOrder, int tag)
{
    CC_ASSERT(vo);
    // to be modifed...
    String* batchNodeName = nullptr;// vo->getBatchNodeNameFromDict();
    std::string name;
    if (batchNodeName)
    {
        name = batchNodeName->getCString();
    }
    
    bool isBatchNode;
    vo->attachSpriteTo(getNodeByName(name, isBatchNode), zOrder, tag);
}


