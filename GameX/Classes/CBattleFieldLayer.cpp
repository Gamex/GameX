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
#include "CAIManager.h"


#define BATCHNODE_LIST          "BatchNodes.plist"

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
    do
    {
        BREAK_IF_FAILED(CTouchesLayer::init());
        
        setTouchEnabled(true);
        
        initListener();
        
        loadConfig();
        
        // ccbi和tmx地图有冲突，所以必须在创建tmx之前先创建一次ccbi，否则真机上release版本会出错！！
        CObjectBase* ob = CObjectBase::createObject("Unit0");
        ob->clearAll();

        BREAK_IF_FAILED(CBkgLayerBase::initBkgLayerBase(BATCHNODE_LIST));
//        setGamePanelLayer(CGamePanelLayer::create());
//        addChild(m_pGamePanelLayer, Z_ORDER_GAME_PANEL);


        loadFormation();
        scheduleUpdate();

        return true;
    } while (false);
    
    return false;
}



void CBattleFieldLayer::update(float dt)
{
    GAME_TIME->update(dt);
    
    AI_MANAGER->update(dt);
        
    CCArray* children = getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj)
    {
        obj->update(dt);
    }

    COLLISION_MANAGER->update();

    FIGHT_RELATION->update(dt);

    CBkgLayerBase::update(dt);
}


void CBattleFieldLayer::touchesBegan(CCSet* touches, CCEvent* event)
{
    bool swallow = false;

    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesBegan(touches, event);
    }
}



void CBattleFieldLayer::touchesMoved(CCSet* touches, CCEvent* event)
{
    bool swallow = false;
    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesMoved(touches, event);
    }
}



void CBattleFieldLayer::touchesEnded(CCSet* touches, CCEvent* event)
{
    bool swallow = false;
    
    switch (touches->count())
    {
        case 1:
        {
            CCTouch* t1 = (CCTouch*)touches->anyObject();
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CBackgroundManager* bkg = getBkgGrd();
            CC_ASSERT(bkg);
            CCPoint gp = bkg->screenPointToGrid(location1);
            
            if (m_curSelRole == NULL)
            {
                bkg->clearAllHightlightGrids();
                CLogicGrid* grid = bkg->getLogicGrid(gp);
                m_curSelRole = dynamic_cast<CRole*>(grid->getUnit());
                if (m_curSelRole)
                {
                    bkg->hightlightGrid(grid->getGridPos());
//                    m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                    
                    bkg->hightlightGrid(m_curSelRole->getMovetarget());
                }
                
                m_curSelRole = NULL;
            }
//            else    // move it
//            {
//                m_curSelRole->setMoveTarget(gp);
//                m_curSelRole = NULL;
//            }
            break;
        }
    }

    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesEnded(touches, event);
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
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    bkgGrd->clearAllUnits();
    

    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->loadFromFile("f.fmt");
    VFE_IT it = fmt->m_elements.begin();
    for (; it != fmt->m_elements.end(); ++it)
    {
        CFormationElement* fe = (*it);
        
        CCDictionary* dict = DTUNIT->getData(fe->unitName);
        CCString* objName = DTUNIT->get_resourceID_Value(dict);
        
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(objName->getCString()));
        CC_ASSERT(role);
        role->loadRoleData(fe->unitName);
        bkgGrd->placeRole(role, fe->pos);
        role->setMoveTarget(fe->pos);
        role->attachSpriteTo(bkgGrd);
        role->setRoleGroup(ROLE_GROUP_ATTACK);
        addChild(role);
    }

    CFormation* fmt1 = FORMATION_MANAGER->getFormation1();
    fmt1->loadFromFile("f1.fmt");
    VFE_IT it1 = fmt1->m_elements.begin();
    for (; it1 != fmt1->m_elements.end(); ++it1)
    {
        CFormationElement* fe = (*it1);
        
        CCDictionary* dict = DTUNIT->getData(fe->unitName);
        CCString* objName = DTUNIT->get_resourceID_Value(dict);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(objName->getCString()));
        CC_ASSERT(role);
        role->loadRoleData(fe->unitName);
        bkgGrd->placeRole(role, fe->pos);
        role->setMoveTarget(fe->pos);
        role->attachSpriteTo(bkgGrd);
        role->setRoleGroup(ROLE_GROUP_DEFENDCE);
        addChild(role);
    }
    return true;
}
