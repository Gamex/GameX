//
//  CGameSceneManager.h
//  GameX
//
//  Created by 马 俊 on 13-8-29.
//
//

#ifndef __GameX__CGameSceneManager__
#define __GameX__CGameSceneManager__

#include "Common.h"
#include "CSingleton.h"
#include "CCBReader.h"

enum SCENE_TYPE
{
    ST_LOBBY,
    ST_FORMATION,
    ST_BATTLE_FIELD,
    ST_SETTINGS,
    ST_NUM,
};


class CGameSceneManager : public CSingleton<CGameSceneManager>
{
public:
    CGameSceneManager();
    virtual ~CGameSceneManager();
    
    virtual bool initialize();
    
    virtual bool go(SCENE_TYPE st);

protected:
private:
    CCArray* m_scenes;
};

#define SCENE_MANAGER           (CGameSceneManager::getInstance())

#endif /* defined(__GameX__CGameSceneManager__) */
