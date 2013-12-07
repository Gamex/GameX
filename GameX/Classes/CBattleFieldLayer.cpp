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
#include "TFCollisionMgr.h"

#include "CGameTime.h"
#include "CBatchNodeManager.h"
#include "CPathFinderManager.h"
#include "CFightingRelationship.h"
#include "CFormationManager.h"
#include "CRole.h"
#include "CDataCenterManager.h"
#include "CBattleFiledManager.h"
#include "CTimeProfile.h"
#include "CEffectManager.h"


#define BATCHNODE_LIST          "BatchNodes.plist"

#define Z_ORDER_GAME_PANEL          1000


CBattleFieldLayer::CBattleFieldLayer()
: m_pGamePanelLayer(nullptr)
, m_curSelRole(nullptr)
, m_bMapMoved(false)
{
}



CBattleFieldLayer::~CBattleFieldLayer()
{
    removeAllListener();
    
    delete COLLISION_MANAGER;

    delete BF_MANAGER;
}



bool CBattleFieldLayer::init()
{
    do
    {
        BREAK_IF_FAILED(CTouchesLayer::init());
        
        Director *pDirector = Director::getInstance();
        pDirector->setDepthTest(true);
        
        setTouchEnabled(true);
        
        initListener();
        
        loadConfig();

        BREAK_IF_FAILED(CBkgLayerBase::initBkgLayerBase(BATCHNODE_LIST));
        setGamePanelLayer(CGamePanelLayer::create());
        addChild(m_pGamePanelLayer, Z_ORDER_GAME_PANEL);

        BREAK_IF_FAILED(EFFECT_MANAGER->init(getBkgGrd()));
        
        BREAK_IF_FAILED(BF_MANAGER->init());

        loadFormation();
        scheduleUpdate();

        return true;
    } while (false);
    
    return false;
}



void CBattleFieldLayer::update(float dt)
{
    TP_LOG_BEGIN(0);
    TP_LOG("begin", 0);
    
    GAME_TIME->update(dt);
    
    BF_MANAGER->update(dt);
    
    EFFECT_MANAGER->update(dt);

    
    TP_LOG("1", 0);
    
    Array* children = getChildren();
    Object* obj;
    CCARRAY_FOREACH(children, obj)
    {
        obj->update(dt);
    }
    
    TP_LOG("2", 0);

    COLLISION_MANAGER->update();

    TP_LOG("3", 0);
    
    FIGHT_RELATION->update(dt);

    TP_LOG("4", 0);
    
    CBkgLayerBase::update(dt);
    
    TP_LOG("5", 0);
    
    TP_LOG_COMMIT(.005);
}


void CBattleFieldLayer::touchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    bool swallow = false;

    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesBegan(touches, event);
    }
}



void CBattleFieldLayer::touchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    bool swallow = false;
    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesMoved(touches, event);
    }
}



void CBattleFieldLayer::touchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    bool swallow = false;
    
    switch (touches.size())
    {
        case 1:
        {
            Touch* t1 = touches[0];
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            Point location1 = this->convertToNodeSpace(point1);
            
            CBackgroundManager* bkg = getBkgGrd();
            CC_ASSERT(bkg);
            Point gp = bkg->screenPointToGrid(location1);
            
            if (m_curSelRole == nullptr)
            {
                bkg->clearAllHightlightGrids();
                CLogicGrid* grid = bkg->getLogicGrid(gp);
                if (grid)
                {
                    m_curSelRole = dynamic_cast<CRole*>(grid->getUnit());
                    if (m_curSelRole)
                    {
                        bkg->hightlightGrid(grid->getGridPos());
//                        m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                        MARK_ROLE(m_curSelRole);
                        bkg->hightlightGrid(m_curSelRole->getMovetarget());
                    }
                }
            }
            else    // move it
            {
//                m_curSelRole->setMoveTarget(gp);
                UNMARK_ROLE(m_curSelRole);
                m_curSelRole = nullptr;
            }
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
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CBattleFieldLayer::onGameOver), NOTIFICATION_HERO_DEAD, nullptr);
}



void CBattleFieldLayer::removeAllListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_HERO_DEAD);
}



void CBattleFieldLayer::onGameOver(Object* obj)
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
    auto it = fmt->m_elements.begin();
    for (; it != fmt->m_elements.end(); ++it)
    {
        CFormationElement* fe = (*it);
        
        const DTUnit::_Data* unitData = DTUNIT->getData(fe->unitId);
        CC_ASSERT(unitData);
        CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
        CC_ASSERT(role);
        role->init(fe->unitId);
        bkgGrd->placeRole(role, fe->pos);
        role->setMoveTarget(fe->pos);
        role->attachSpriteTo(bkgGrd);
        role->setRoleGroup(ROLE_GROUP_ATTACK);
        addChild(role);
    }

    CFormation* fmt1 = FORMATION_MANAGER->getFormation1();
    fmt1->loadFromFile("f1.fmt");
    auto it1 = fmt1->m_elements.begin();
    for (; it1 != fmt1->m_elements.end(); ++it1)
    {
        CFormationElement* fe = (*it1);
        
        const DTUnit::_Data* unitData = DTUNIT->getData(fe->unitId);
        CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
        CC_ASSERT(role);
        role->init(fe->unitId);
        bkgGrd->placeRole(role, fe->pos);
        role->setMoveTarget(fe->pos);
        role->attachSpriteTo(bkgGrd);
        role->setRoleGroup(ROLE_GROUP_DEFENCE);
        addChild(role);
    }
    return true;
}
