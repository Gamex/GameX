//
//  CBattleFieldLayer.cpp
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright Tencent 2013. All rights reserved.
//
#include "Common.h"

#include "CBattleFieldLayer.h"
//#include "SimpleAudioEngine.h"
#include "TFGameObjectManager.h"
#include "TFCollisionMgr.h"

#include "CGameTime.h"
#include "CBatchNodeManager.h"
#include "CPathFinderManager.h"
#include "CFightingRelationship.h"
#include "CFormationManager.h"
#include "CRole.h"

#define Z_ORDER_GAME_PANEL          1000


CBattleFieldLayer::CBattleFieldLayer()
: m_isGameOver(false)
, m_pGamePanelLayer(NULL)
{
}



CBattleFieldLayer::~CBattleFieldLayer()
{
    removeAllListener();
    
    delete COLLISION_MANAGER;

}



bool CBattleFieldLayer::init()
{
    CTouchesLayer::init();

    m_isGameOver = false;
    
    setTouchEnabled(true);
    
    initListener();
    
    loadConfig();
    
    setGamePanelLayer(CGamePanelLayer::create());
    addChild(m_pGamePanelLayer, Z_ORDER_GAME_PANEL);

    BATCH_NODE_MANAGER->attachToParent(this, 0);
    
//    CASTLE_MANAGER->spawnAll();
//
//    addChild(CASTLE_MANAGER);

    loadFormation();
    
    scheduleUpdate();
 
    return true;
}



void CBattleFieldLayer::update(float dt)
{
    GAME_TIME->update(dt);
    
    if (m_isGameOver)
    {
        return;
    }
        
    CCArray* children = getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj)
    {
        obj->update(dt);
    }

    COLLISION_MANAGER->update();

    FIGHT_RELATION->update(dt);
}


 void CBattleFieldLayer::gbTouchesBegan(CCPoint position)
{
}



void CBattleFieldLayer::gbTouchesMoved(CCPoint position)
{
}



void CBattleFieldLayer::gbTouchesEnded(CCPoint position)
{
    PATH_FINDER->findPath(CGridPos(10, 10), CGridPos(25, 25));
}


//void CBattleFieldLayer::gbTapGesture(CCPoint position)
//{
//    m_pBaseGun->setAimPoint(position);
//}


void CBattleFieldLayer::initListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CBattleFieldLayer::onGameOver), NOTIFICATION_HERO_DEAD, NULL);
}



void CBattleFieldLayer::removeAllListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_HERO_DEAD);
}



void CBattleFieldLayer::onGameOver(CCObject* obj)
{
    m_isGameOver = true;
    removeAllListener();
}



bool CBattleFieldLayer::loadConfig()
{
    do
    {
        return true;
    } while (false);
    
    return false;
}



bool CBattleFieldLayer::loadFormation()
{
    BKG_MANAGER->clearAllUnits();
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    CFormation::VFE_IT it = fmt->m_elements.begin();
    for (; it != fmt->m_elements.end(); ++it)
    {
        CFormationElement* elem = (*it);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(elem->objName));
        CC_ASSERT(role);

        CLogicGrid* grid = BKG_MANAGER->getGrid(elem->pos);
        grid->setGroundUnit(role);
        role->setSpritePosition(BKG_MANAGER->gridToPoint(elem->pos));
        role->attachSpriteTo();

    }
    
    return true;
}
