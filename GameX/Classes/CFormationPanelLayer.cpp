//
//  CFormationPanelLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-29.
//
//

#include "CFormationPanelLayer.h"
#include "CGameSceneManager.h"
#include "CGlobalConfigration.h"
#include "CSoldierManager.h"
#include "CSoldier.h"
#include "CFormationManager.h"

#define MENU_FRAME_TAG_START            100         // the tag is defined in cocosbuilder

static class CFormationPanelLayerRegister
{
public:
    CFormationPanelLayerRegister()
    {
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "CFormationPanelLayer", CFormationPanelLayerLoader::loader());
    }
} __reg;


CFormationPanelLayer::CFormationPanelLayer()
: m_firstShownIdx(0)
, m_delegate(NULL)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        m_frames[i] = NULL;
    }
}



CFormationPanelLayer::~CFormationPanelLayer()
{
    
}



bool CFormationPanelLayer::init()
{
    do
    {
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CFormationPanelLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBack", CFormationPanelLayer::onBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSave", CFormationPanelLayer::onSave);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUp", CFormationPanelLayer::onUp);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDown", CFormationPanelLayer::onDown);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF0", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF1", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF2", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF3", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF4", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF5", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF6", CFormationPanelLayer::onFrame);
    
    return NULL;
}

//函数定义类型为：void pressTitle(CCObject *pSender);
SEL_CCControlHandler CFormationPanelLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CFormationPanelLayer::controlButtonTest);
    return NULL;
}

bool CFormationPanelLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        char s[20];
        sprintf(s, "m_f%d", i);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, s, CCMenuItem*, m_frames[i]);
    }

    return false;
}


void CFormationPanelLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    return;
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        CSoldier* soldier = SOLDIER_MANAGER->getSoldier(static_cast<SOLDIER_TYPE>(i));
        if (soldier == NULL)
        {
            m_frames[i]->setEnabled(false);
        }
        else
        {
            CCSize sz = m_frames[i]->getContentSize();
            soldier->setSpritePosition(ccp(sz.width / 2.f, sz.height / 2.f));
            soldier->attachSpriteTo(m_frames[i]);
            m_frames[i]->setUserData((void*)i);
            soldier->changeState("EditPos");
//            soldier->setSpriteFlipX(true);
        }
    }
}



void CFormationPanelLayer:: onBack(CCObject *pSender)
{
    SCENE_MANAGER->go(ST_LOBBY);
}



void CFormationPanelLayer:: onSave(CCObject *pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->m_elements.clear();
    
    if (m_delegate)
    {
        m_delegate->onSave(fmt);
    }
}



void CFormationPanelLayer:: onUp(CCObject *pSender)
{
}



void CFormationPanelLayer:: onDown(CCObject *pSender)
{
}



void CFormationPanelLayer:: onFrame(CCObject *pSender)
{
    CCMenuItem* menu = dynamic_cast<CCMenuItem*>(pSender);
    CC_ASSERT(menu);
    m_curSel = menu->getTag() - MENU_FRAME_TAG_START;
    
    if (m_delegate)
    {
        m_delegate->onFrameSel(m_curSel);
    }
}





