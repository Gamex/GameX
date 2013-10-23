//
//  TFGameObjectManager.cpp
//  TheForce
//
//  Created by Ray M on 13-3-6.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFGameObjectManager.h"


IMPLEMENT_SINGLETON(TFGameObjectManager);



TFGameObjectManager::TFGameObjectManager() :
pGameObjects_(NULL)
{

}



TFGameObjectManager::~TFGameObjectManager()
{
    clearAll();
}



void TFGameObjectManager::clearAll()
{
    setGameObjects(NULL);
}



bool TFGameObjectManager::init()
{
    clearAll();
    
    const char* cp = "GameObject.plist";
    
	setGameObjects(CCDictionary::createWithContentsOfFile(cp));
    if (!getGameObjects())
    {
        __CCLOGWITHFUNCTION("file can't be loaded: %s", cp);
        return false;
    }

    return true;
}



CCDictionary* TFGameObjectManager::getObjectByName(const std::string& name)
{
    if (NULL == pGameObjects_)
    {
        __CCLOGWITHFUNCTION("has not initialized!");
        return NULL;
    }
    
    return  dynamic_cast<CCDictionary*>(pGameObjects_->objectForKey(name));
}
