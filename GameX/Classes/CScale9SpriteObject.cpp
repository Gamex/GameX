//
//  CScale9SpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CScale9SpriteObject.h"



CScale9SpriteObject::CScale9SpriteObject() :
m_pSprite(nullptr)
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
//    std::string _name = name;
//    std::string::size_type pos = name.find(".png", 0);
//    if (pos != std::string::npos)
//    {
//        _name = name.substr(0, pos);
//    }
    
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name.c_str());
    if (nullptr == pFrame)
    {
        return false;
    }
    Size sz = pFrame->getRect().size;
    m_pSprite = Scale9Sprite::createWithSpriteFrameName(name.c_str(), Rect(1, 1, sz.width-2, sz.height-2));
    if (nullptr == m_pSprite)
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
        m_pSprite = nullptr;
    }
}



void CScale9SpriteObject::setSpritePreferredSize(const Size& size)
{
    if (nullptr != m_pSprite)
    {
        m_pSprite->setPreferredSize(size);
    }
}



Node* CScale9SpriteObject::getInnerSprite() const
{
    return m_pSprite;
}



