//
//  CHomeLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-12-8.
//
//

#include "CHomeLayer.h"
#include "CRole.h"
#include "CShopManager.h"
#include "CGameSceneManager.h"
#include "CCPomelo.h"
#include "CDataCenterManager.h"
#include "CShopManager.h"
#include "CPlayerInfo.h"

#define BATCHNODE_LIST          "BatchNodes.plist"
#define TILE_MAP_NAME           "homeTile.tmx"
#define BACKGROUND_MAP_NAME       "home.tmx"

#define TAG_BUILD_OK            1001
#define TAG_BUILD_CANCEL            1002

static class CHomeLayerRegister
{
public:
    CHomeLayerRegister()
    {
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CHomeLayer", CHomeLayerLoader::loader());
    }
} __reg;



CHomeLayer::CHomeLayer()
{
}



CHomeLayer::~CHomeLayer()
{
}



bool CHomeLayer::init()
{
    do
    {
        BREAK_IF_FAILED(CTouchesLayer::init());
        
        Director *pDirector = Director::getInstance();
        pDirector->setDepthTest(true);
        
        setTouchEnabled(true);
        
        BREAK_IF_FAILED(CBkgLayerBase::initBkgLayerBase(BATCHNODE_LIST, BACKGROUND_MAP_NAME, TILE_MAP_NAME));
        
        scheduleUpdate();
        
        
        reqHomeInfo();
        
        refreshMainMenu();
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CHomeLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
    return nullptr;
}



void CHomeLayer::reqHomeInfo()
{
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    bkgGrd->clearAllUnits();
    
    const char *route = "gameplay.home.getHomeInfo";;
    json_t *msg = json_object();
    POMELO->request(route, msg, [&, bkgGrd](Node* node, void* resp)
                    {
                        CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                        json_t* code = json_object_get(ccpomeloresp->docs, "code");
                        if (json_integer_value(code) != 200)
                        {
                            CCLOG("get home info failed");
                        }
                        else
                        {
                            json_t* homeInfoArr = json_object_get(ccpomeloresp->docs, "info");
                            int count = json_array_size(homeInfoArr);
                            for (int i = 0; i < count; ++i)
                            {
                                json_t* info = json_array_get(homeInfoArr, i);
                                string bname = json_string_value(json_object_get(info, "bname"));
                                Point pos{json_integer_value(json_object_get(info, "x")),
                                        json_integer_value(json_object_get(info, "y"))};
                                
                                auto unitData = DTUNIT->getData(bname);
                                CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
                                CC_ASSERT(role);
                                role->init(bname);
                                bkgGrd->placeRole(role, pos);
                                role->attachSpriteTo(bkgGrd);
                                role->playAnimation("Idle");
                            }
                        }
                    });
}


Control::Handler CHomeLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMenu", CHomeLayer::onMenu);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBack", CHomeLayer::onBack);
    return nullptr;
}



bool CHomeLayer::onAssignCCBMemberVariable(Object * pTarget, const char* pMemberVariableName, Node * pNode)
{
	return false;
}



void CHomeLayer::onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader)
{
}



void CHomeLayer::update(float dt)
{
}


void CHomeLayer::touchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    
    bool swallow = false;
    
    
    switch (touches.size())
    {
        case 1:
        {
            Touch* t1 = touches[0];
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            
            CBackgroundManager* bkgGrd = getBkgGrd();
            CC_ASSERT(bkgGrd);
            
            Point gp = bkgGrd->screenPointToGrid(point1);
            bkgGrd->hightlightGrid(m_curSelGrid, false);
            m_curSelGrid = gp;
            bkgGrd->hightlightGrid(m_curSelGrid, true);
            
            CLogicGrid* grid = bkgGrd->getLogicGrid(gp);
            if (grid)
            {
                m_curSelRole = dynamic_cast<CRole*>(grid->getUnit());
                if (m_curSelRole)
                {
                    m_curSelRole->playAnimation(ROLE_ANIMATION_SELECTED);
                    swallow = true;
                }
            }
            
            break;
        }
    }
    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesBegan(touches, event);
    }
}



void CHomeLayer::touchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    bool swallow = false;
    
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    switch (touches.size())
    {
        case 1:
        {
            Touch* t1 = touches[0];
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            Point location1 = this->convertToNodeSpace(point1);
            
            Point gp = bkgGrd->screenPointToGrid(location1);
            
            bkgGrd->hightlightGrid(m_curSelGrid, false);
            m_curSelGrid = gp;
            bkgGrd->hightlightGrid(m_curSelGrid, true);
            
            if (m_curSelRole)
            {
                CLogicGrid* grid = bkgGrd->getLogicGrid(m_curSelGrid);
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                if (role == nullptr && bkgGrd->isRoleCanBePlacedOnPos(m_curSelRole, m_curSelGrid))      // this grid is not occupied, so place in it
                {
                    bkgGrd->placeRole(m_curSelRole, m_curSelGrid);
                }
                
                swallow = true;
            }
            break;
        }
        default:
            break;
    }
    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesMoved(touches, event);
    }
}



void CHomeLayer::touchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    bool swallow = false;
    
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    switch (touches.size())
    {
        case 1:
        {
            Touch* t1 = touches[0];
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            Point location1 = this->convertToNodeSpace(point1);
            
            location1 = bkgGrd->screenPointToWorld(location1);
            CLogicGrid* grid = bkgGrd->getGridFromWorldPt(location1);
            if (m_curSelRole != nullptr)
            {
                bkgGrd->hightlightGrid(m_curSelGrid, false);
                m_curSelGrid.x = -1;
                m_curSelGrid.y = -1;
                
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                
                if (role == nullptr)       // this grid is not occupied, so place in it
                {
                    bkgGrd->placeRole(m_curSelRole, grid->getGridPos());
                }
                
                m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                m_curSelRole = nullptr;
                
                swallow = true;
            }
            break;
        }
    }
    
    if (!swallow)
    {
        CBkgLayerBase::bkgLayerBaseTouchesEnded(touches, event);
    }
}



void CHomeLayer::onBack(Object* sender, Control::EventType event)
{
    SCENE_MANAGER->go(ST_LOBBY);
}



void CHomeLayer::onMenu(Object* sender, Control::EventType event)
{
    toggleMainMenu();
}



void CHomeLayer::refreshMainMenu()
{
    if (m_mainMenuRoot)
    {
        m_mainMenuRoot->removeFromParent();
    }
    
    m_mainMenuRoot = CCNode::create();
    m_mainMenuRoot->setPosition(0, 0);
    m_mainMenuRoot->setVisible(false);
    addChild(m_mainMenuRoot);
    
    auto sl = SHOP->getShopListByLevel(PLAYER_INFO->getLevel());
    
    for (int i = 0; i < sl.size(); ++i)
    {
        ControlButton* btn = ControlButton::create(sl[i].c_str(), "Helvetica", 16);
        btn->setPosition(100 + i * 50, 50);
        btn->addTargetWithActionForControlEvents(this, static_cast<Control::Handler>(&CHomeLayer::onShopItemClicked), Control::EventType::TOUCH_UP_INSIDE);
        btn->setTag(i);
        m_mainMenuRoot->addChild(btn);
    }
}



void CHomeLayer::onBuildCommitClicked(Object* obj, Control::EventType type)
{
    do
    {
        BREAK_IF(nullptr == m_buildingRole);
        Control* btn = static_cast<Control*>(obj);
        if (btn->getTag() == TAG_BUILD_OK)
        {
            const char *route = "gameplay.home.buildInHome";
            json_t *msg = json_object();
            json_object_set(msg, "bname", json_string(m_buildingRole->getUnitId().c_str()));
            CLogicGrid* lg = m_buildingRole->getLogicGrid();
            CC_ASSERT(lg);
            Point pt = lg->getGridPos();
            
            json_object_set(msg, "x", json_integer(pt.x));
            json_object_set(msg, "y", json_integer(pt.y));
            
            POMELO->request(route, msg, [&](Node* node, void* resp)
                            {
                                CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                json_t* code = json_object_get(ccpomeloresp->docs, "code");
                                if (json_integer_value(code) != 200)
                                {
                                    CCLOG("build in home failed");
                                    m_buildingRole->clearAll();
                                 }
                                else
                                {
                                    m_buildingRole->getInnerSprite()->removeChildByTag(TAG_BUILD_OK);
                                    m_buildingRole->getInnerSprite()->removeChildByTag(TAG_BUILD_CANCEL);
                                    m_buildingRole->playAnimation("Idle");
                                    m_buildingRole = nullptr;
                                }
                            });
        }
        else
        {
            m_buildingRole->clearAll();
            m_buildingRole = nullptr;
        }

    } while(false);
}



void CHomeLayer::onShopItemClicked(Object* obj, Control::EventType type)
{
    Control* btn = static_cast<Control*>(obj);
    auto sl = SHOP->getShopListByLevel(PLAYER_INFO->getLevel());
    const string& unitId = sl[btn->getTag()];
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    const DTUnit::_Data* unitData = DTUNIT->getData(unitId);
    CC_ASSERT(unitData);
    Point screenCenter {Director::getInstance()->getWinSize() / 2};
    Point gridPos = bkgGrd->screenPointToGrid(screenCenter);
    CLogicGrid* grid = bkgGrd->getEmptyGridNearby(gridPos, unitData->gridWidth, unitData->gridHeight);
    if (grid)
    {
        CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
        CC_ASSERT(role);
        role->init(unitId, true);
        bkgGrd->placeRole(role, grid->getGridPos());
        role->attachSpriteTo(bkgGrd);
        addChild(role);
        
        bkgGrd->hightlightGrid(grid->getGridPos());
        
        m_buildingRole = role;
        
        Size szRole = role->getSpriteContentSize();
        ControlButton* btnY = ControlButton::create("Y", "Helvetica", 16);
        Size sz = btnY->getContentSize();
        btnY->setPosition(szRole.width * 0.5f + sz.width, szRole.height);
        btnY->addTargetWithActionForControlEvents(this, static_cast<Control::Handler>(&CHomeLayer::onBuildCommitClicked), Control::EventType::TOUCH_UP_INSIDE);
        btnY->setTag(TAG_BUILD_OK);
        
        ControlButton* btnN = ControlButton::create("N", "Helvetica", 16);
        sz = btnN->getContentSize();
        btnN->setPosition(szRole.width * 0.5f - sz.width, szRole.height);
        btnN->addTargetWithActionForControlEvents(this, static_cast<Control::Handler>(&CHomeLayer::onBuildCommitClicked), Control::EventType::TOUCH_UP_INSIDE);
        btnN->setTag(TAG_BUILD_CANCEL);
        
        m_buildingRole->getInnerSprite()->addChild(btnY);
        m_buildingRole->getInnerSprite()->addChild(btnN);
        m_buildingRole->playAnimation("Selected");
    }
    
    toggleMainMenu();
}



void CHomeLayer::toggleMainMenu()
{
    if (m_mainMenuRoot)
    {
        m_mainMenuRoot->setVisible(m_mainMenuRoot->isVisible() ? false : true);
    }
}
