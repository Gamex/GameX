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

#define BATCHNODE_LIST          "BatchNodes.plist"
#define TILE_MAP_NAME           "homeTile.tmx"
#define BACKGROUND_MAP_NAME       "home.tmx"


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
    
    const char *route = "gameplay.gameplayHandler.getHomeInfo";;
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
            //            Point location1 = this->convertToNodeSpace(point1);
            
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
                    m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
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
    createShops();
}


void CHomeLayer::createShops()
{
    
}
