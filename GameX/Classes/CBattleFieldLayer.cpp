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
#include "CDataCenterManager.h"

#define Z_ORDER_GAME_PANEL          1000


CBattleFieldLayer::CBattleFieldLayer()
: m_isGameOver(false)
, m_pGamePanelLayer(NULL)
, m_hero(NULL)
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
    
    BKG_MANAGER->attachBackgroundTo(this);
//    setGamePanelLayer(CGamePanelLayer::create());
//    addChild(m_pGamePanelLayer, Z_ORDER_GAME_PANEL);

//    BATCH_NODE_MANAGER->attachToParent(this, 10);

//    loadFormation();
    
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
    
    PATH_FINDER->update(dt);
}


void CBattleFieldLayer::touchBegan(CCPoint position)
{
    if (m_hero)
    {
        CCPoint gridPt = BKG_MANAGER->pointToGrid(position);
        m_hero->setMoveTarget(gridPt);
    }
}



void CBattleFieldLayer::touchMoved(CCPoint position)
{
}



void CBattleFieldLayer::touchEnded(CCPoint position)
{
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
        CFormationElement* fe = (*it);
        
        CCDictionary* dict = DTUNIT->getData(fe->unitName);
        CCString* objName = DTUNIT->get_resourceID_Value(dict);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(objName->getCString()));
        CC_ASSERT(role);
        role->setUnitName(fe->unitName);
        role->setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
        role->setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());
        role->placeOnGridPos(fe->pos);
        role->attachSpriteTo(NULL, role->getZ());

        if (role->getNameFromDict()->compare("Unit0") == 0)
        {
            m_hero = role;
        }
        addChild(role);
    }
    
    return true;
}
