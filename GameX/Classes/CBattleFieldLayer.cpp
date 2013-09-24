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
: m_pGamePanelLayer(NULL)
, m_curSelRole(NULL)
, m_bMapMoved(false)
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
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesAllAtOnce);
    
    initListener();
    
    loadConfig();
    
    BKG_MANAGER->attachBackgroundTo(this);
    
//    setGamePanelLayer(CGamePanelLayer::create());
//    addChild(m_pGamePanelLayer, Z_ORDER_GAME_PANEL);

//    BATCH_NODE_MANAGER->attachToParent(BKG_MANAGER->getTiledMap(), 0);

    loadFormation();
    
    scheduleUpdate();
 
    return true;
}



void CBattleFieldLayer::update(float dt)
{
    GAME_TIME->update(dt);
        
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


void CBattleFieldLayer::touchesBegan(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            m_tapStartPoint = this->convertToNodeSpace(point1);
            break;
        }
        case 2:
        {
            
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCTouch* t2 = (CCTouch*)tch->objectAtIndex(1);
            
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint point2 = CCDirector::sharedDirector()->convertToUI(t2->getLocationInView());
            CCPoint location2 = this->convertToNodeSpace(point2);
            
            m_lastLength = (location2 - location1).getLengthSq();
            
            break;
        }
    }

}



void CBattleFieldLayer::touchesMoved(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint offset = location1 - m_tapStartPoint;
            BKG_MANAGER->moveMap(offset);
                
            m_tapStartPoint = location1;
            
            m_bMapMoved = true;
            break;
        }
        case 2:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCTouch* t2 = (CCTouch*)tch->objectAtIndex(1);
            
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint point2 = CCDirector::sharedDirector()->convertToUI(t2->getLocationInView());
            CCPoint location2 = this->convertToNodeSpace(point2);
            
            float len = (location2 - location1).getLengthSq();
            
            if (len > m_lastLength)
            {
                // zoom out
                BKG_MANAGER->addMapScale(0.05);
            }
            else if (len < m_lastLength)
            {
                // zoom in
                BKG_MANAGER->addMapScale(-0.05);
            }
            
            m_lastLength = len;
            break;
        }
        default:
            break;
    }

}



void CBattleFieldLayer::touchesEnded(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            if (m_bMapMoved)
            {
                m_bMapMoved = false;
            }
            else
            {
                CCArray* tch = allTouchesSet(touches);
                CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
                CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
                CCPoint location1 = this->convertToNodeSpace(point1);

                CCPoint gp = BKG_MANAGER->screenPointToGrid(location1);
                
                if (m_curSelRole == NULL)
                {
                    CLogicGrid* grid = BKG_MANAGER->getLogicGrid(gp);
                    m_curSelRole = dynamic_cast<CRole*>(grid->getUnit());
                    if (m_curSelRole)
                    {
                        BKG_MANAGER->hightlightGrid(grid->getGridPos());
                        m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                    }
                }
                else    // move it
                {
                    m_curSelRole->setMoveTarget(gp);
                    m_curSelRole = NULL;
                }
//            CLogicGrid* grid = BKG_MANAGER->getGridFromWorldPt(location1);
            }
            break;
        }
        case 2:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCTouch* t2 = (CCTouch*)tch->objectAtIndex(1);
            
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint point2 = CCDirector::sharedDirector()->convertToUI(t2->getLocationInView());
            CCPoint location2 = this->convertToNodeSpace(point2);
            
            break;
        }
    }
}


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
        role->attachSpriteTo();

        addChild(role);
    }
    
    return true;
}
