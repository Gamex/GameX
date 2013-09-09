//
//  CGameSceneManager.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-29.
//
//

#include "CGameSceneManager.h"
#include "CBattleFieldLayer.h"
#include "CLobbyLayer.h"
#include "CFormationLayer.h"
#include "CFormationLayer.h"


IMPLEMENT_SINGLETON(CGameSceneManager);


CGameSceneManager::CGameSceneManager()
: m_scenes(NULL)
{
    
}



CGameSceneManager::~CGameSceneManager()
{
    CC_SAFE_RELEASE(m_scenes);
}



bool CGameSceneManager::initialize()
{
    do
    {
        m_scenes = CCArray::createWithCapacity(ST_NUM);
        CC_SAFE_RETAIN(m_scenes);

        return true;
    } while (false);
    
    
    return false;
}


bool CGameSceneManager::go(SCENE_TYPE st)
{
    CCScene* scene = NULL;
    switch (st)
    {
        case ST_LOBBY:
        {
            CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
            scene = pReader->createSceneWithNodeGraphFromFile("lobby_layer.ccbi");
            delete pReader;
            break;
        }
        case ST_FORMATION:
        {
            scene = CCScene::create();
            scene->addChild(CFormationLayer::create());
            break;
        }
        case ST_BATTLE_FIELD:
        {
            scene = CCScene::create();
            scene->addChild(CBattleFieldLayer::create());       // call init in create()
            break;
        }
        case ST_SETTINGS:
            break;
        default:
            break;
    }
    if (scene)
    {
        CCDirector* pDirector = CCDirector::sharedDirector();
        if (pDirector->getRunningScene())
        {
            CCTransitionFade* trans = CCTransitionFade::create(1.f, scene, ccc3(255, 255, 255));
            pDirector->replaceScene(trans);
        }
        else
        {
            pDirector->runWithScene(scene);
        }
    }
    
    return true;
}
