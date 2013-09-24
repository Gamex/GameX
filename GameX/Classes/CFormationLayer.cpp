//
//  CFormationLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#include "CFormationLayer.h"
#include "CBackgroundManager.h"
#include "CFormationPanelLayer.h"
#include "CGameSceneManager.h"
#include "CBatchNodeManager.h"
#include "CFormationManager.h"
#include "CRole.h"
#include "CDataCenterManager.h"

#define Z_ORDER_PANEL           1000

CFormationLayer::CFormationLayer()
: m_curSelRole(NULL)
, m_lastLength(0.f)
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
        setTouchMode(kCCTouchesAllAtOnce);
        
        m_roleNode = CCNode::create();
        addChild(m_roleNode);

        m_curSelGrid.x = -1;
        m_curSelGrid.y = -1;
        
        BKG_MANAGER->attachBackgroundTo(this);
        BATCH_NODE_MANAGER->attachToParent(BKG_MANAGER->getTiledMap(), 0);
        
        CCBReader* pReader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
        m_panel = dynamic_cast<CFormationPanelLayer*>(pReader->readNodeGraphFromFile("formation_layer.ccbi"));
        delete pReader;
        
        m_panel->setDelegate(this);
        addChild(m_panel, Z_ORDER_PANEL);
        
        this->scheduleUpdate();

        return true;
    } while (false);
    
    return false;
}



void CFormationLayer::update(float dt)
{
    CBaseLayer::update(dt);
}



void CFormationLayer::onFrameSel(const string& unitName)
{
    CCDictionary* dict = DTUNIT->getData(unitName);
    int gridWidth = DTUNIT->get_gridWidth_Value(dict)->intValue();
    int gridHeight = DTUNIT->get_gridHeight_Value(dict)->intValue();
    
    CCPoint screenCenter = CCDirector::sharedDirector()->getWinSize() / 2;
    CCPoint gridPos = BKG_MANAGER->screenPointToGrid(screenCenter);
    CLogicGrid* grid = BKG_MANAGER->getEmptyGridNearby(gridPos, gridWidth, gridHeight);
    if (grid)
    {
        CCString* name = DTUNIT->get_resourceID_Value(dict);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(name->getCString()));
        CC_ASSERT(role);
        role->setUnitName(unitName);
        role->setGridWidth(gridWidth);
        role->setGridHeight(gridHeight);
        role->placeOnGridPos(grid->getGridPos());
        role->attachSpriteTo();
        m_roleNode->addChild(role);
        
        BKG_MANAGER->hightlightGrid(grid->getGridPos());
    }
}



void CFormationLayer::touchesBegan(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);

            CCPoint gp = BKG_MANAGER->screenPointToGrid(location1);
            BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
            m_curSelGrid = gp;
            BKG_MANAGER->hightlightGrid(m_curSelGrid, true);
            
            CLogicGrid* grid = BKG_MANAGER->getLogicGrid(gp);
            m_curSelRole = dynamic_cast<CRole*>(grid->getUnit());
            if (m_curSelRole)
            {
                m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
            }
            else
            {
                m_tapStartPoint = location1;
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
            
            m_lastLength = (location2 - location1).getLengthSq();
            
            break;
        }
    }
}



void CFormationLayer::touchesMoved(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);
            
            CCPoint gp = BKG_MANAGER->screenPointToGrid(location1);

            BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
            m_curSelGrid = gp;
            BKG_MANAGER->hightlightGrid(m_curSelGrid, true);
            
            if (m_curSelRole)
            {
                CLogicGrid* grid = BKG_MANAGER->getLogicGrid(m_curSelGrid);
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                if (role == NULL)       // this grid is not occupied, so place in it
                {
                    m_curSelRole->placeOnGridPos(m_curSelGrid);
                }
            }
            else
            {
                CCPoint offset = location1 - m_tapStartPoint;
                BKG_MANAGER->moveMap(offset);
                
                m_tapStartPoint = location1;
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



void CFormationLayer::touchesEnded(CCSet* touches, CCEvent* event)
{
    switch (touches->count())
    {
        case 1:
        {
            CCArray* tch = allTouchesSet(touches);
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = this->convertToNodeSpace(point1);

            location1 = BKG_MANAGER->screenPointToWorld(location1);
            CLogicGrid* grid = BKG_MANAGER->getGridFromWorldPt(location1);
            if (m_curSelRole != NULL)
            {
                BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
                m_curSelGrid.x = -1;
                m_curSelGrid.y = -1;
                
                
                CRole* role = dynamic_cast<CRole*>(grid->getUnit());
                
                if (role == NULL)       // this grid is not occupied, so place in it
                {
                    m_curSelRole->placeOnGridPos(grid->getGridPos());
                }
                
                m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
                m_curSelRole = NULL;
            }
            else        // move map
            {
                
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



void CFormationLayer::onSave(CFormation* fmt)
{
    int x, y;
    CBackgroundManager* bkg = BKG_MANAGER;
    CCPoint pos;
    for (y = 0; y < bkg->getHeightInGrid(); ++y)
    {
        for (x = 0; x < bkg->getWidthInGrid(); ++x)
        {
            pos.x = x;
            pos.y = y;
            CLogicGrid* grid = bkg->getLogicGrid(pos);
            CRole* role = dynamic_cast<CRole*>(grid->getUnit());
            if (role)
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
            role->placeOnGridPos(fe->pos);
            role->attachSpriteTo();
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
    BKG_MANAGER->clearAllUnits();
    CCArray* roles = m_roleNode->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(roles, obj)
    {
        CRole* role = (CRole*)obj;
        role->clearAll();
    }
    
    m_roleNode->removeAllChildrenWithCleanup(true);
}



