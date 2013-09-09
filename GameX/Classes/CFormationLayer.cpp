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
#include "CSoldierManager.h"
#include "CSoldier.h"
#include "CFormationManager.h"

#define Z_ORDER_PANEL           1000

CFormationLayer::CFormationLayer()
: m_curSelRole(NULL)
{
    
}



CFormationLayer::~CFormationLayer()
{
    
}



bool CFormationLayer::init()
{
    do
    {
        setTouchEnabled(true);

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
    CGridPos gp = BKG_MANAGER->pointToGrid(position);
    if (gp != m_curSelGrid)
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
            CLogicGrid* grid = BKG_MANAGER->getGrid(gp);

            m_curSelRole = grid->getGroundUnit();
            if (m_curSelRole)
            {
                m_curSelRole->changeState("EditSel");
            }
            
        }
    }
}



void CFormationLayer::touchMoved(CCPoint position)
{
    CGridPos gp = BKG_MANAGER->pointToGrid(position);
    if (gp != m_curSelGrid)
    {
        BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
        m_curSelGrid = gp;
        BKG_MANAGER->hightlightGrid(m_curSelGrid, true);
        
        if (m_curSelRole)
        {
            m_curSelRole->setSpritePosition(BKG_MANAGER->gridToPoint(gp));
        }
    }
}



void CFormationLayer::touchEnded(CCPoint position)
{
    CLogicGrid* grid = BKG_MANAGER->getGrid(position);
    if (m_curSelRole != NULL)
    {
        BKG_MANAGER->hightlightGrid(m_curSelGrid, false);
        m_curSelGrid.x = -1;
        m_curSelGrid.y = -1;
        
        CLogicGrid* oldGrid = m_curSelRole->getGrid();
        
        CRole* role = grid->getGroundUnit();
        if (role == NULL)       // this grid is not occupied, so place in it
        {
            if (oldGrid)
            {
                oldGrid->setGroundUnit(NULL);
            }
            grid->setGroundUnit(m_curSelRole);
            m_curSelRole->setSpritePosition(BKG_MANAGER->gridToPoint(grid->getGridPos()));
        }
        else
        {
            if (oldGrid)
            {
                m_curSelRole->setSpritePosition(BKG_MANAGER->gridToPoint(oldGrid->getGridPos()));
            }
        }
        
        m_curSelRole->changeState("Idle");
        m_curSelRole = NULL;
    }
}



void CFormationLayer::onFrameSel(int sel)
{
    CLogicGrid* grid = BKG_MANAGER->getEmptyGridNearby(CGridPos(BKG_MANAGER->getWidthInGrid() >> 1, BKG_MANAGER->getHeightInGrid() >> 1));
    if (grid)
    {
        CCPoint pt = BKG_MANAGER->gridToPoint(grid->getGridPos());
        CRole* role = SOLDIER_MANAGER->getSoldier(static_cast<SOLDIER_TYPE>(sel));
        role->setSpritePosition(pt);
        role->attachSpriteTo();
        grid->setGroundUnit(role);
    }
}



void CFormationLayer::onSave(CFormation* fmt)
{
    int x, y;
    CBackgroundManager* bkg = BKG_MANAGER;
    CGridPos pos;
    for (y = 0; y < bkg->getHeightInGrid(); ++y)
    {
        for (x = 0; x < bkg->getWidthInGrid(); ++x)
        {
            pos.x = x;
            pos.y = y;
            CLogicGrid* grid = bkg->getGrid(pos);
            CSoldier* soldier = dynamic_cast<CSoldier*>(grid->getGroundUnit());
            if (soldier)
            {
                CFormationElement* fe = new CFormationElement;
                fe->pos = pos;
                fe->type = soldier->getType();
                
                fmt->m_elements.push_back(fe);
            }
        }
    }
}