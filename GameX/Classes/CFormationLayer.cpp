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
#include "UtilityFunction.h"

#define BATCHNODE_LIST          "BatchNodes.plist"

#define Z_ORDER_PANEL           1000

CFormationLayer::CFormationLayer()
: m_curSelRole(NULL)
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
        setTouchEnabled(true);
        CCDirector::sharedDirector()->setDepthTest(true);
        
        CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
        m_panel = dynamic_cast<CFormationPanelLayer*>(pReader->readNodeGraphFromFile("formation_layer.ccbi"));
        delete pReader;
        
        m_panel->setDelegate(this);
        addChild(m_panel, Z_ORDER_PANEL);

        BREAK_IF_FAILED(initBkgLayerBase(BATCHNODE_LIST));
        
        m_roleNode = CCNode::create();
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



void CFormationLayer::onFrameSel(const string& unitName)
{
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    CCDictionary* dict = DTUNIT->getData(unitName);
    int gridWidth = DTUNIT->get_gridWidth_Value(dict)->intValue();
    int gridHeight = DTUNIT->get_gridHeight_Value(dict)->intValue();
    
    CCPoint screenCenter = CCDirector::sharedDirector()->getWinSize() / 2;
    CCPoint gridPos = bkgGrd->screenPointToGrid(screenCenter);
    CLogicGrid* grid = bkgGrd->getEmptyGridNearby(gridPos, gridWidth, gridHeight);
    if (grid)
    {
        CCString* name = DTUNIT->get_resourceID_Value(dict);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(name->getCString()));
        CC_ASSERT(role);
        role->setUnitName(unitName);
        role->setGridWidth(gridWidth);
        role->setGridHeight(gridHeight);
        bkgGrd->placeRole(role, grid->getGridPos());
        role->attachSpriteTo(bkgGrd);
        m_roleNode->addChild(role);

        bkgGrd->hightlightGrid(grid->getGridPos());
    }
}



void CFormationLayer::touchesBegan(CCSet* touches, CCEvent* event)
{
    
    bool swallow = false;
    
    
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = utility::allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);

            CBackgroundManager* bkgGrd = getBkgGrd();
            CC_ASSERT(bkgGrd);
            
            CCPoint gp = bkgGrd->screenPointToGrid(point1);
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



void CFormationLayer::touchesMoved(CCSet* touches, CCEvent* event)
{
    bool swallow = false;
    
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = utility::allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint gp = bkgGrd->screenPointToGrid(location1);

            bkgGrd->hightlightGrid(m_curSelGrid, false);
            m_curSelGrid = gp;
            bkgGrd->hightlightGrid(m_curSelGrid, true);
            
            if (m_curSelRole)
            {
                CLogicGrid* grid = bkgGrd->getLogicGrid(m_curSelGrid);
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                if (role == NULL)       // this grid is not occupied, so place in it
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



void CFormationLayer::touchesEnded(CCSet* touches, CCEvent* event)
{
    bool swallow = false;
    
    CBackgroundManager* bkgGrd = getBkgGrd();
    CC_ASSERT(bkgGrd);
    
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = utility::allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);

            location1 = bkgGrd->screenPointToWorld(location1);
            CLogicGrid* grid = bkgGrd->getGridFromWorldPt(location1);
            if (m_curSelRole != NULL)
            {
                bkgGrd->hightlightGrid(m_curSelGrid, false);
                m_curSelGrid.x = -1;
                m_curSelGrid.y = -1;
                
                
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                
                if (role == NULL)       // this grid is not occupied, so place in it
                {
                    bkgGrd->placeRole(m_curSelRole, grid->getGridPos());
                }
                
                m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                m_curSelRole = NULL;
                
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
    CCPoint pos;
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
                fe->unitName = role->getUnitName();
                
                fmt->m_elements.push_back(fe);
            }
        }
    }
    
    fmt->saveToFile("f.fmt");
}



void CFormationLayer::onLoad(CFormation* fmt)
{
    
    if (fmt->loadFromFile("f.fmt"))
    {
        clearFormation();
        CBackgroundManager* bkgGrd = getBkgGrd();
        CC_ASSERT(bkgGrd);
        
        int sz = fmt->m_elements.size();
        for (int i = 0; i < sz; ++i)
        {
            CFormationElement* fe = fmt->m_elements[i];
            CCDictionary* dict = DTUNIT->getData(fe->unitName);
            CCString* objName = DTUNIT->get_resourceID_Value(dict);
            CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(objName->getCString()));
            CC_ASSERT(role);
            role->setUnitName(fe->unitName);
            role->setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
            role->setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());
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
    CCArray* roles = m_roleNode->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(roles, obj)
    {
        CRole* role = (CRole*)obj;
        role->clearAll();
    }
    
    m_roleNode->removeAllChildrenWithCleanup(true);
}



