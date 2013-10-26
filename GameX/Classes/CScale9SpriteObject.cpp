//
//  CScale9SpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CScale9SpriteObject.h"



CScale9SpriteObject::CScale9SpriteObject() :
m_pSprite(NULL)
{
    
}



CScale9SpriteObject::~CScale9SpriteObject()
{
    clearThis();
}




bool CScale9SpriteObject::init(const std::string& name)
{
    if (!CVisibleObject::init())
    {
        return false;
    }
    
    if (!createScale9Sprite(name))
    {
        return false;
    }
    
    return true;
}



bool CScale9SpriteObject::createScale9Sprite(const std::string& name)
{
    std::string _name = name;
    std::string::size_type pos = name.find(".png", 0);
    if (pos != std::string::npos)
    {
        _name = name.substr(0, pos);
    }
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name.c_str());
    if (NULL == pFrame)
    {
        return false;
    }
//    OrigBarSize_ = pFrame->getRect().size;
    m_pSprite = CCScale9Sprite::createWithSpriteFrameName(_name.c_str(), pFrame->getRect());
    if (NULL == m_pSprite)
    {
        return false;
    }
    
    return true;
}



void CScale9SpriteObject::clearAll()
{
    CVisibleObject::clearAll();
    
    clearThis();
}



void CScale9SpriteObject::clearThis()
{
    if (m_pSprite)
    {
        m_pSprite->removeFromParentAndCleanup(true);
        m_pSprite = NULL;
    }
}



void CScale9SpriteObject::setSpritePreferredSize(const CCSize& size)
{
    if (NULL != m_pSprite)
    {
        m_pSprite->setPreferredSize(size);
    }
}



CCNode* CScale9SpriteObject::getInnerSprite() const
{
    return m_pSprite;
}



