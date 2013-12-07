//
//  CFormationLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#include "CFormationLayer.h"
#include "CFormationPanelLayer.h"
#include "CGameSceneManager.h"
#include "CFormationManager.h"
#include "CRole.h"
#include "CDataCenterManager.h"


#define BATCHNODE_LIST          "BatchNodes.plist"

#define Z_ORDER_PANEL           1000

CFormationLayer::CFormationLayer()
: m_curSelRole(nullptr)
{
    
}



CFormationLayer::~CFormationLayer()
{
    clearAll();
}



bool CFormationLayer::init()
{
    do
    {
        BREAK_IF_FAILED(CTouchesLayer::init());
        
        Director *pDirector = Director::getInstance();
        pDirector->setDepthTest(true);
        
        setTouchEnabled(true);
        
        CCBReader* pReader = new CCBReader(NodeLoaderLibrary::getInstance());
        m_panel = dynamic_cast<CFormationPanelLayer*>(pReader->readNodeGraphFromFile("formation_layer.ccbi"));
        delete pReader;
        
        m_panel->setDelegate(this);
        addChild(m_panel, Z_ORDER_PANEL);

        BREAK_IF_FAILED(initBkgLayerBase(BATCHNODE_LIST));
        
        m_roleNode = Node::create();
        addChild(m_roleNode);

        m_curSelGrid.x = -1;
        m_curSelGrid.y = -1;

        this->scheduleUpdate();

        return true;
    } while (false);
    
    return false;
}



void CFormationLayer::update(float dt)
{
    CBaseLayer::update(dt);
    CBkgLayerBase::update(dt);
}



void CFormationLayer::onFrameSel(const std::string& unitId)
{
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
        m_roleNode->addChild(role);

        bkgGrd->hightlightGrid(grid->getGridPos());
    }
}



void CFormationLayer::touchesBegan(const std::vector<Touch*>& touches, Event* event)
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



void CFormationLayer::touchesMoved(const std::vector<Touch*>& touches, Event* event)
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



void CFormationLayer::touchesEnded(const std::vector<Touch*>& touches, Event* event)
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



void CFormationLayer::onSave(CFormation* fmt)
{
    int x, y;
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    Point pos;
    for (y = 0; y < bkgGrd->getHeightInGrid(); ++y)
    {
        for (x = 0; x < bkgGrd->getWidthInGrid(); ++x)
        {
            pos.x = x;
            pos.y = y;
            CLogicGrid* grid = bkgGrd->getLogicGrid(pos);
            CRole* role = dynamic_cast<CRole*>(grid->getUnit());
            if (role && grid->getIsPrimary())
            {
                CFormationElement* fe = new CFormationElement;
                fe->pos = pos;
                fe->unitId = role->getUnitId();
                
                fmt->m_elements.push_back(fe);
            }
        }
    }
    
    fmt->saveToFile();
}



void CFormationLayer::onLoad(CFormation* fmt)
{
    
    if (fmt->loadFromFile())
    {
        clearFormation();
        CBackgroundManager* bkgGrd = getBkgGrd();
        CC_ASSERT(bkgGrd);
        
        int sz = fmt->m_elements.size();
        for (int i = 0; i < sz; ++i)
        {
            CFormationElement* fe = fmt->m_elements[i];
            
            const DTUnit::_Data* unitData = DTUNIT->getData(fe->unitId);
            CC_ASSERT(unitData);
            CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
            CC_ASSERT(role);
            role->init(fe->unitId, true);
            bkgGrd->placeRole(role, fe->pos);
            role->attachSpriteTo(bkgGrd);
            m_roleNode->addChild(role);
        }
    }
    
}



void CFormationLayer::clearAll()
{
    clearFormation();
    removeAllChildrenWithCleanup(true);
}


void CFormationLayer::clearFormation()
{
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    bkgGrd->clearAllUnits();
    Array* roles = m_roleNode->getChildren();
    Object* obj;
    CCARRAY_FOREACH(roles, obj)
    {
        CRole* role = (CRole*)obj;
        role->clearAll();
    }
    
    m_roleNode->removeAllChildrenWithCleanup(true);
}



