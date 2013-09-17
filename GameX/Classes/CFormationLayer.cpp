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
        
        m_roleNode = CCNode::create();
        addChild(m_roleNode);

        m_curSelGrid.x = -1;
        m_curSelGrid.y = -1;
        
        BATCH_NODE_MANAGER->attachToParent(this, 0);
        
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



void CFormationLayer::touchBegan(CCPoint position)
{
    CCPoint gp = BKG_MANAGER->pointToGrid(position);
    if (!gp.equals(m_curSelGrid))
    {
        BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
        m_curSelGrid = gp;
        BKG_MANAGER->hightlightGrid(m_curSelGrid, true);
        
        if (m_curSelRole)
        {
            m_curSelRole->setSpritePosition(BKG_MANAGER->gridToPoint(gp));
        }
        else
        {
            CLogicGrid* grid = BKG_MANAGER->getLogicGrid(gp);

            m_curSelRole = dynamic_cast<CRole*>(grid->getGroundUnit());
            if (m_curSelRole)
            {
                m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
            }
            
        }
    }
}



void CFormationLayer::touchMoved(CCPoint position)
{
    CCPoint gp = BKG_MANAGER->pointToGrid(position);
    if (!gp.equals(m_curSelGrid))
    {
        BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
        m_curSelGrid = gp;
        BKG_MANAGER->hightlightGrid(m_curSelGrid, true);
        
        if (m_curSelRole)
        {
            CLogicGrid* grid = BKG_MANAGER->getLogicGrid(m_curSelGrid);
            CRole* role = dynamic_cast<CRole*>(grid->getGroundUnit());
            if (role == NULL)       // this grid is not occupied, so place in it
            {
                m_curSelRole->placeOnGridPos(m_curSelGrid);
            }
        }
    }
}



void CFormationLayer::touchEnded(CCPoint position)
{
    CLogicGrid* grid = BKG_MANAGER->getGridFromPt(position);
    if (m_curSelRole != NULL)
    {
        BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
        m_curSelGrid.x = -1;
        m_curSelGrid.y = -1;
        
        
        CRole* role = dynamic_cast<CRole*>(grid->getGroundUnit());

        if (role == NULL)       // this grid is not occupied, so place in it
        {
            m_curSelRole->placeOnGridPos(grid->getGridPos());
        }
        
        m_curSelRole->playAnimation(ROLE_ANIMATION_IDLE);
        m_curSelRole = NULL;
    }
}



void CFormationLayer::onFrameSel(const string& unitName)
{
    CLogicGrid* grid = BKG_MANAGER->getEmptyGridNearby(CCPoint(BKG_MANAGER->getWidthInGrid() >> 1, BKG_MANAGER->getHeightInGrid() >> 1));
    if (grid)
    {
        CCDictionary* dict = DTUNIT->getData(unitName);
        CCString* name = DTUNIT->get_resourceID_Value(dict);
        CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(name->getCString()));
        CC_ASSERT(role);
        role->setUnitName(unitName);
        role->setGridWidth(DTUNIT->get_gridWidth_Value(dict)->intValue());
        role->setGridHeight(DTUNIT->get_gridHeight_Value(dict)->intValue());
        role->placeOnGridPos(grid->getGridPos());
        role->attachSpriteTo(NULL, role->getZ());
        m_roleNode->addChild(role);
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
            CRole* role = dynamic_cast<CRole*>(grid->getGroundUnit());
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
            role->attachSpriteTo(NULL, role->getZ());
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



