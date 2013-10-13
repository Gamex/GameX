//
//  TFGameObjectManager.h
//  TheForce
//
//  Created by Ray M on 13-3-6.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFGameObjectManager__
#define __TheForce__TFGameObjectManager__

#include "Common.h"
#include "CSingleton.h"


class TFGameObjectManager : public CSingleton<TFGameObjectManager>
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, pGameObjects_, GameObjects);
public:
    TFGameObjectManager();
    virtual ~TFGameObjectManager();
   
    bool init();
    void clearAll();
    
    CCDictionary* getObjectByName(const std::string& name);

protected:
private:

};

#define GAME_OJBECT_MANAGER (TFGameObjectManager::getInstance())

#endif /* defined(__TheForce__TFGameObjectManager__) */
